from lib.test.evaluation.tracker import Tracker
import os, time, threading
import sys
import argparse
import cv2
from vidstab import VidStab

prj_path = os.path.join(os.path.dirname(__file__), '..')
if prj_path not in sys.path:
    sys.path.append(prj_path)
from logger import tracker_logger as logger
from utils import calculate_iou

class RWSTracker(Tracker):
    def __init__(self, tracker_name, tracker_param, model_path, alpha=0.02, hist_diff_threshold=0.7, iou_threshold=0.5):
        """
            rws single tracker
        args:
            tracker_name: name of tracker (ex: artrack, artrack_seq, odtrack)
            tracker_param: param file (ex: artrack_256_full, arttrack_seq_256_full, baseline). see: RWS_Tracker/experments/tracker/*.yaml
        """
        super().__init__(tracker_name, tracker_param)

        self.model_path = model_path
        self.tracker = None
        self.init_tracker()
        
        self.source = None
        self.class_ids = None  # Initialize class_ids as None to detect all classes by default
        self.tracking_thread = None
        self.stop_event = threading.Event()  # Event to control thread stopping
        self.cap : cv2.VideoCapture = None
        
        self.confirmed = True # confirmed that this bbox is tracking object
        self.current_result = None  # Stores the latest tracking results
        self.current_frame = None # Stores the last frame
        self.frame_update = False
        self.tracker_conf = 0.0

        # detect anormally using iou
        self.iou_threshold = iou_threshold
        
        # detect anormally using histogram
        self.alpha = alpha # adapt histogram rate
        self.hist_diff_threshold = hist_diff_threshold # detect anormally 
        self.baseline_hist = None 
        
        # video stabilizer
        self.stabilizer = VidStab()
        self.enable_stabilizer = False # default false
        self.stabilizer_smoothing_window = 5 # default 5   
        
    def init_tracker(self):
        params = self.get_parameters()
        params.debug = 0
        
        params.tracker_name = self.name
        params.param_name = self.parameter_name
        params.cfg.MODEL.PRETRAIN_PTH = self.model_path
        # params.cfg.MODEL.PRETRAIN_PTH
        
        logger.info(f'Initalize tracker: {self.name} - {self.parameter_name} - {self.model_path}')
        self.tracker = self.create_tracker(params)
        
    def set_videocapture(self, cap):
        logger.debug('Video capture source set.')
        self.cap = cap
        
    def initialize_baseline_histogram(self, frame, bbox):
        x, y, w, h = bbox
        roi = frame[y:y+h, x:x+w]
        roi_hsv = cv2.cvtColor(roi, cv2.COLOR_BGR2HSV)
        self.baseline_hist = cv2.calcHist([roi_hsv], [0, 1, 2], None, [8, 8, 8], [0, 256, 0, 256, 0, 256])
        cv2.normalize(self.baseline_hist, self.baseline_hist)
        
    def detect_histogram_anomaly(self, frame, bbox):
        x, y, w, h = bbox
        roi = frame[y:y+h, x:x+w]
        roi_hsv = cv2.cvtColor(roi, cv2.COLOR_BGR2HSV)
        current_hist = cv2.calcHist([roi_hsv], [0, 1, 2], None, [8, 8, 8], [0, 256, 0, 256, 0, 256])
        cv2.normalize(current_hist, current_hist)
        
        # Calculate similarity (Bhattacharyya distance)
        similarity = cv2.compareHist(self.baseline_hist, current_hist, cv2.HISTCMP_CORREL)
        
        # Check for anomaly
        is_anomaly = similarity < self.hist_diff_threshold
        # if is_anomaly:
        # print(f'Similarity: {similarity:2f} - anormal: {is_anomaly}')

        # Update baseline histogram if no anomaly detected
        if not is_anomaly:
            self.baseline_hist = (1 - self.alpha) * self.baseline_hist + self.alpha * current_hist
        
        return is_anomaly, similarity
        
    def detect_iou_anomaly(self, pre_iou, cur_iou):
        iou = calculate_iou(cur_iou, pre_iou)
        is_anormal_iou = iou < self.iou_threshold
        return is_anormal_iou, iou
        
    def start_tracking(self, frame, box, show=False):
        """
        Start tracking object in video stream, init with bounding box
        MUST initalize track object before start tracking it
        params:
            box: bounding box of object
            frame: frame contain object (in bounding box)
            show: show tracking video result or not
        """
        
        if self.tracker is None:
            logger.error("Tracker not initalized!")
                
        self.initalize_track_object(frame, box)
        
        if self.tracking_thread is None or not self.tracking_thread.is_alive():
            self.stop_event.clear()  # Clear any previous stop event
            self.tracking_thread = threading.Thread(target=self._track_video, args=(show,))
            self.tracking_thread.start()
        
    def _track_video(self, show=False):
        """
        Internal method to process the video and track objects using single object tracker function.
        This method runs in a separate thread and continuously processes video frames.
        """
        logger.debug(f'Start tracking object from videosource')
        
        if self.cap is None:
            logger.error("Video capcutre is not set.")
            return
        
        # cap = cv2.VideoCapture(self.source)
        if not self.cap.isOpened():
            logger.error("Video capture not opened.")
            return
        
        
        
        # window_name = 'Object tracking: ' + self.tracker.params.tracker_name
        # cv2.namedWindow(window_name, cv2.WINDOW_NORMAL | cv2.WINDOW_KEEPRATIO)
        # cv2.resizeWindow(window_name, 960, 720)
        # Loop over frames
        
        feed_stablizer_frame_index = 0
        
        while True:
            # stop tracking when stop event set
            if self.stop_event.is_set():
                break
            
            ret, frame = self.cap.read()
            
            # Break the loop if no frame is returned (end of video)
            if not ret:
                break
            
            # stablilze frame
            if self.enable_stabilizer:
                if feed_stablizer_frame_index < self.stabilizer_smoothing_window:
                    # warming up, this will return black frame
                    self.stabilizer.stabilize_frame(frame, smoothing_window=self.stabilizer_smoothing_window) 
                    feed_stablizer_frame_index += 1
                else:
                    frame = self.stabilizer.stabilize_frame(frame, smoothing_window=self.stabilizer_smoothing_window)
            
                if frame is None:
                    logger.debug('Stablize frame return None')
                    continue

            confirmed, result = self.frame_track(frame) # predict bounding box of tracking object, format: [x,y,w,h]
            self.confirmed = confirmed
            self.current_result = result
            self.update_current_frame(frame) # let drawing task for parent module
            
            # logger.debug(f'Current tracking result: {self.current_result}')

            if show and self.current_result is not None:
                # Get the bounding boxes, confidences, and tracking IDs from each result
                cv2.rectangle(frame, (self.current_result[0], self.current_result[1]), (self.current_result[2] + self.current_result[0], self.current_result[3] + self.current_result[1]),
                         (0, 255, 0), 2)
        
                cv2.imshow(f'Object tracking: {self.name}', frame)

                # Press 'q' to exit the loop
                if cv2.waitKey(1) & 0xFF == ord('q'):
                    break
                
        # Release the video capture and close all OpenCV windows
        # cap.release() # let release task for parent
        cv2.destroyAllWindows()
        
    def update_current_frame(self, frame):
        self.current_frame = frame
        self.frame_update = True
        
    def stop_tracking(self):
        """
        Stop the single tracking thread.
        """
        if self.tracking_thread is not None and self.tracking_thread.is_alive():
            self.stop_event.set()  # Signal the thread to stop
            self.tracking_thread.join()  # Wait for the thread to finish
            self.tracking_thread = None
            logger.info("Tracking single object stopped.")
        
    def initalize_track_object(self, frame, box): 
        """
            Initalize object to track
            args: 
                frame: current frame
                box: bounding box of object need to track, format:  [x, y, w, h]
        """
        def _build_init_info(box):
            return {'init_bbox': box}
        logger.debug(f'Initialize tracked object with bounding box: {box}')
        self.tracker.initialize(frame, _build_init_info(box))
        
        self.initialize_baseline_histogram(frame, box) # init base hist for detect anormaly
        self.current_result = box
        
        
    def frame_track(self, frame):
        """
            Track object in continous frame
            args:
                frame: current frame
            return:
                bounding box of object [x,y,w,h]
        """
        previous_bbox = self.current_result
        
        out = self.tracker.track(frame)
        state = [int(s) for s in out['target_bbox']]
        x, y, w, h = state
        
        is_anormal_hist, similarity = self.detect_histogram_anomaly(frame, state)
        # if is_anormal_hist:
        #     logger.debug(f'Anormal hist - {similarity} - {self.hist_diff_threshold} - {self.alpha}')        
        
        if previous_bbox is None:
            is_anormal_iou = False
        else:
            # iou = calculate_iou(state, previous_bbox)
            # is_anormal_iou = iou < self.iou_threshold
            is_anormal_iou, iou = self.detect_iou_anomaly(state, previous_bbox)

        # if is_anormal_iou:
        #     logger.debug(f'Anormal iou - {iou} - {self.iou_threshold}')            
        
        # confirmed it is right object
        confirmed = not is_anormal_hist and not is_anormal_iou
    
        return confirmed,(x, y, w, h)
    

    def get_current_result_string(self):
        """
        Parse the current tracking results into a string format:
        TFT,conf,bbx,bby,bbw,bbh

        Returns:
            str: A formatted string containing the tracking results.
        """
        if not self.current_result:
            return "TFT,0,0,0,0"  # Return the header with no targets if no results are available

        result_parts = ["TFT"]  # Start with the header
        x,y,w,h = self.current_result
        confirm_value = 1 if self.confirmed else 0
        result_parts.append(f"{confirm_value},{int(x)},{int(y)},{int(w)},{int(h)}")
        
        return ",".join(result_parts)
        
        
    def test_tracker(self, videofilepath, optional_box=None):
        assert os.path.isfile(videofilepath), "Invalid param {}".format(videofilepath)
        ", videofilepath must be a valid videofile"

        output_boxes = []

        cap = cv2.VideoCapture(videofilepath)
        display_name = 'Display: ' + self.tracker.params.tracker_name
        cv2.namedWindow(display_name, cv2.WINDOW_NORMAL | cv2.WINDOW_KEEPRATIO)
        cv2.resizeWindow(display_name, 960, 720)
        success, frame = cap.read()
        cv2.imshow(display_name, frame)

        def _build_init_info(box):
            return {'init_bbox': box}

        if success is not True:
            print("Read frame from {} failed.".format(videofilepath))
            exit(-1)
        if optional_box is not None:
            assert isinstance(optional_box, (list, tuple))
            assert len(optional_box) == 4, "valid box's foramt is [x,y,w,h]"
            self.tracker.initialize(frame, _build_init_info(optional_box))
            output_boxes.append(optional_box)
        else:
            while True:
                # cv2.waitKey()
                frame_disp = frame.copy()

                cv2.putText(frame_disp, 'Select target ROI and press ENTER', (20, 30), cv2.FONT_HERSHEY_COMPLEX_SMALL,
                           1.5, (0, 0, 0), 1)

                x, y, w, h = cv2.selectROI(display_name, frame_disp, fromCenter=False)
                init_state = [x, y, w, h]
                self.tracker.initialize(frame, _build_init_info(init_state))
                output_boxes.append(init_state)
                break
                
        while True:
            t = time.time()
            ret, frame = cap.read()

            if frame is None:
                break

            frame_disp = frame.copy()

            # Draw box
            out = self.tracker.track(frame)
            state = [int(s) for s in out['target_bbox']]
            output_boxes.append(state)

            cv2.rectangle(frame_disp, (state[0], state[1]), (state[2] + state[0], state[3] + state[1]),
                         (0, 255, 0), 5)

            font_color = (0, 0, 0)
            cv2.putText(frame_disp, 'Tracking!', (20, 30), cv2.FONT_HERSHEY_COMPLEX_SMALL, 1.5,
                       font_color, 1)
            cv2.putText(frame_disp, 'Press r to reset', (20, 60), cv2.FONT_HERSHEY_COMPLEX_SMALL, 1.5,
                       font_color, 1)
            cv2.putText(frame_disp, 'Press q to quit', (20, 100), cv2.FONT_HERSHEY_COMPLEX_SMALL, 1.5,
                       font_color, 1)
            cv2.putText(frame_disp, f'FPS: {1/(time.time()-t)}', (20, 140), cv2.FONT_HERSHEY_COMPLEX_SMALL, 2,
                       (0,255,0), 2)
            
            t = time.time()

            # Display the resulting frame
            cv2.imshow(display_name, frame_disp)
            key = cv2.waitKey(1)
            if key == ord('q'):
                break
            elif key == ord('r'):
                ret, frame = cap.read()
                frame_disp = frame.copy()

                cv2.putText(frame_disp, 'Select target ROI and press ENTER', (20, 30), cv2.FONT_HERSHEY_COMPLEX_SMALL, 1.5,
                           (0, 0, 0), 1)

                cv2.imshow(display_name, frame_disp)
                x, y, w, h = cv2.selectROI(display_name, frame_disp, fromCenter=False)
                init_state = [x, y, w, h]
                self.tracker.initialize(frame, _build_init_info(init_state))
                output_boxes.append(init_state)

        # When everything done, release the capture
        cap.release()
        cv2.destroyAllWindows()
        
    def get_current_tracking_result(self):
        """
        Get the current tracking result, which is updated by the tracking thread.
        Returns the latest result if tracking is active.
        """
        if self.tracking_thread is not None and self.tracking_thread.is_alive():
            return self.current_result
        else:
            logger.info("Tracking thread is not running.")
            return None
        
    def test_tracker_v2(self, videofilepath, optional_box=None):
        assert os.path.isfile(videofilepath), "Invalid param {}".format(videofilepath)
        ", videofilepath must be a valid videofile"

        cap = cv2.VideoCapture(videofilepath)
        display_name = 'Display: ' + self.tracker.params.tracker_name
        cv2.namedWindow(display_name, cv2.WINDOW_NORMAL | cv2.WINDOW_KEEPRATIO)
        cv2.resizeWindow(display_name, 960, 720)
        success, frame = cap.read()
        cv2.imshow(display_name, frame)


        if success is not True:
            print("Read frame from {} failed.".format(videofilepath))
            exit(-1)
        if optional_box is not None:
            assert isinstance(optional_box, (list, tuple))
            assert len(optional_box) == 4, "valid box's foramt is [x,y,w,h]"
            self.initalize_track_object(frame, optional_box)
        else:
            while True:
                # cv2.waitKey()
                frame_disp = frame.copy()

                cv2.putText(frame_disp, 'Select target ROI and press ENTER', (20, 30), cv2.FONT_HERSHEY_COMPLEX_SMALL,
                           1.5, (0, 0, 0), 1)

                x, y, w, h = cv2.selectROI(display_name, frame_disp, fromCenter=False)
                init_state = [x, y, w, h]
                self.initalize_track_object(frame, init_state)
                break
                
        while True:
            t = time.time()
            ret, frame = cap.read()

            if frame is None:
                break

            frame_disp = frame.copy()

            # Draw box
            # out = self.tracker.track(frame)
            # state = [int(s) for s in out['target_bbox']]
            # output_boxes.append(state)
            
            confirmed, state = self.frame_track(frame)
            self.confirmed = confirmed
            self.current_result = state

            cv2.rectangle(frame_disp, (state[0], state[1]), (state[2] + state[0], state[3] + state[1]),
                         (0, 255, 0), 5)

            font_color = (0, 0, 0)
            cv2.putText(frame_disp, 'Tracking!', (20, 30), cv2.FONT_HERSHEY_COMPLEX_SMALL, 1.5,
                       font_color, 1)
            cv2.putText(frame_disp, 'Press r to reset', (20, 60), cv2.FONT_HERSHEY_COMPLEX_SMALL, 1.5,
                       font_color, 1)
            cv2.putText(frame_disp, 'Press q to quit', (20, 100), cv2.FONT_HERSHEY_COMPLEX_SMALL, 1.5,
                       font_color, 1)
            
            anormal_sign = "" if confirmed else "LOST TRACK"
            cv2.putText(frame_disp, f'FPS: {1/(time.time()-t):.2f} {anormal_sign}', (20, 140), cv2.FONT_HERSHEY_COMPLEX_SMALL, 2,
                       (0,255,0), 2)
            
            t = time.time()

            # Display the resulting frame
            cv2.imshow(display_name, frame_disp)
            key = cv2.waitKey(1)
            if key == ord('q'):
                break
            elif key == ord('c'): # confirm track
                print('Confirm track')
                self.initialize_baseline_histogram(frame, self.current_result)
            elif key == ord('r'):
                ret, frame = cap.read()
                frame_disp = frame.copy()

                cv2.putText(frame_disp, 'Select target ROI and press ENTER', (20, 30), cv2.FONT_HERSHEY_COMPLEX_SMALL, 1.5,
                           (0, 0, 0), 1)

                cv2.imshow(display_name, frame_disp)
                x, y, w, h = cv2.selectROI(display_name, frame_disp, fromCenter=False)
                init_state = [x, y, w, h]
                self.initalize_track_object(frame, init_state)

        # When everything done, release the capture
        cap.release()
        cv2.destroyAllWindows()
        
        
def test_tracker_thread():
    vid_path = '/media/hoc/WORK/remote/AnhPhuong/TRACKING_CONTROL_SYSTEM/Projects/RWS_CU/RWS_AI_MODULE/videos/test_tau.avi'
    model_path = '/media/hoc/WORK/remote/AnhPhuong/TRACKING_CONTROL_SYSTEM/Projects/RWS_CU/RWS_AI_MODULE/models/odtrack/odtrack_base_full/ODTrack_ep0300.pth.tar'
    cap = cv2.VideoCapture(vid_path)
    
    rws_tracker = RWSTracker('odtrack', 'baseline', model_path)
    _, frame = cap.read()
    
    ## Dont know why there is a bug that select roi make _start_tracking function (while loop) not worked as expect
    ## TODO: Fix it (if have time)
    # while True:
    #     frame_disp = frame.copy()

    #     cv2.putText(frame_disp, 'Select target ROI and press ENTER', (20, 30), cv2.FONT_HERSHEY_COMPLEX_SMALL,
    #                 1.5, (0, 0, 0), 1)

    #     x, y, w, h = cv2.selectROI('Select roi', frame_disp, fromCenter=False)
    #     box = [x, y, w, h]
    #     print(box)
    #     break
    # cv2.destroyAllWindows()
    
    
    # box = [614, 344, 37, 29]
    box = [230, 240, 46, 195]
    rws_tracker.set_videocapture(cap)
    rws_tracker.start_tracking(frame, box, show=True)
    time.sleep(10)
    logger.debug(f'Current tracking result: {rws_tracker.get_current_tracking_result()}')
    rws_tracker.stop_tracking()
    

if __name__ == "__main__":
    model_path = '/media/hoc/WORK/remote/AnhPhuong/TRACKING_CONTROL_SYSTEM/Projects/RWS_CU/RWS_AI_MODULE/models/artrack/artrack_seq_base_256_full/ARTrackSeq_ep0060.pth.tar'
    tracker = RWSTracker('artrack_seq', 'artrack_seq_256_full', model_path)
    
    # model_path = '/media/hoc/WORK/remote/AnhPhuong/TRACKING_CONTROL_SYSTEM/Projects/RWS_CU/RWS_AI_MODULE/models/odtrack/odtrack_base_full/ODTrack_ep0300.pth.tar'    
    # tracker = RWSTracker('odtrack', 'baseline', model_path)
    tracker.test_tracker_v2('/media/hoc/WORK/remote/AnhPhuong/TRACKING_CONTROL_SYSTEM/Projects/RWS_CU/RWS_AI_MODULE/videos/test_tau.avi')
    # test_tracker_thread()