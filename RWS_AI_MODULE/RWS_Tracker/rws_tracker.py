from lib.test.evaluation.tracker import Tracker
import os, time
import sys
import argparse
import cv2 as cv

prj_path = os.path.join(os.path.dirname(__file__), '..')
if prj_path not in sys.path:
    sys.path.append(prj_path)
from logger import tracker_logger as logger

class RWSTracker(Tracker):
    def __init__(self, tracker_name, tracker_param, model_path):
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
        
    def init_tracker(self):
        params = self.get_parameters()
        params.debug = 0
        
        params.tracker_name = self.name
        params.param_name = self.parameter_name
        params.cfg.MODEL.PRETRAIN_PTH = self.model_path
        # params.cfg.MODEL.PRETRAIN_PTH
        
        logger.info(f'Initalize tracker: {self.name} - {self.parameter_name} - {self.model_path}')
        self.tracker = self.create_tracker(params)
        
    def initalize_track_object(self, frame, box): 
        """
            Initalize object to track
            args: 
                frame: current frame
                box: bounding box of object need to track, format:  [x, y, w, h]
        """
        def _build_init_info(box):
            return {'init_bbox': box}
        
        self.tracker.initialize(frame, _build_init_info(box))
        
    def frame_track(self, frame):
        """
            Track object in continous frame
            args:
                frame: current frame
            return:
                bounding box of object [x,y,w,h]
        """
        
        out = self.tracker.track(frame)
        state = [int(s) for s in out['target_bbox']]
        x, y, w, h = state        
        return (x, y, w, h)
    
    
        
    def test_tracker(self, videofilepath, optional_box=None):
        assert os.path.isfile(videofilepath), "Invalid param {}".format(videofilepath)
        ", videofilepath must be a valid videofile"

        output_boxes = []

        cap = cv.VideoCapture(videofilepath)
        display_name = 'Display: ' + self.tracker.params.tracker_name
        cv.namedWindow(display_name, cv.WINDOW_NORMAL | cv.WINDOW_KEEPRATIO)
        cv.resizeWindow(display_name, 960, 720)
        success, frame = cap.read()
        cv.imshow(display_name, frame)

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
                # cv.waitKey()
                frame_disp = frame.copy()

                cv.putText(frame_disp, 'Select target ROI and press ENTER', (20, 30), cv.FONT_HERSHEY_COMPLEX_SMALL,
                           1.5, (0, 0, 0), 1)

                x, y, w, h = cv.selectROI(display_name, frame_disp, fromCenter=False)
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

            cv.rectangle(frame_disp, (state[0], state[1]), (state[2] + state[0], state[3] + state[1]),
                         (0, 255, 0), 5)

            font_color = (0, 0, 0)
            cv.putText(frame_disp, 'Tracking!', (20, 30), cv.FONT_HERSHEY_COMPLEX_SMALL, 1.5,
                       font_color, 1)
            cv.putText(frame_disp, 'Press r to reset', (20, 60), cv.FONT_HERSHEY_COMPLEX_SMALL, 1.5,
                       font_color, 1)
            cv.putText(frame_disp, 'Press q to quit', (20, 100), cv.FONT_HERSHEY_COMPLEX_SMALL, 1.5,
                       font_color, 1)
            cv.putText(frame_disp, f'FPS: {1/(time.time()-t)}', (20, 140), cv.FONT_HERSHEY_COMPLEX_SMALL, 2,
                       (0,255,0), 2)
            
            t = time.time()

            # Display the resulting frame
            cv.imshow(display_name, frame_disp)
            key = cv.waitKey(1)
            if key == ord('q'):
                break
            elif key == ord('r'):
                ret, frame = cap.read()
                frame_disp = frame.copy()

                cv.putText(frame_disp, 'Select target ROI and press ENTER', (20, 30), cv.FONT_HERSHEY_COMPLEX_SMALL, 1.5,
                           (0, 0, 0), 1)

                cv.imshow(display_name, frame_disp)
                x, y, w, h = cv.selectROI(display_name, frame_disp, fromCenter=False)
                init_state = [x, y, w, h]
                self.tracker.initialize(frame, _build_init_info(init_state))
                output_boxes.append(init_state)

        # When everything done, release the capture
        cap.release()
        cv.destroyAllWindows()
        
    def test_tracker_v2(self, videofilepath, optional_box=None):
        assert os.path.isfile(videofilepath), "Invalid param {}".format(videofilepath)
        ", videofilepath must be a valid videofile"

        output_boxes = []

        cap = cv.VideoCapture(videofilepath)
        display_name = 'Display: ' + self.tracker.params.tracker_name
        cv.namedWindow(display_name, cv.WINDOW_NORMAL | cv.WINDOW_KEEPRATIO)
        cv.resizeWindow(display_name, 960, 720)
        success, frame = cap.read()
        cv.imshow(display_name, frame)


        if success is not True:
            print("Read frame from {} failed.".format(videofilepath))
            exit(-1)
        if optional_box is not None:
            assert isinstance(optional_box, (list, tuple))
            assert len(optional_box) == 4, "valid box's foramt is [x,y,w,h]"
            self.initalize_track_object(frame, optional_box)
            output_boxes.append(optional_box)
        else:
            while True:
                # cv.waitKey()
                frame_disp = frame.copy()

                cv.putText(frame_disp, 'Select target ROI and press ENTER', (20, 30), cv.FONT_HERSHEY_COMPLEX_SMALL,
                           1.5, (0, 0, 0), 1)

                x, y, w, h = cv.selectROI(display_name, frame_disp, fromCenter=False)
                init_state = [x, y, w, h]
                self.initalize_track_object(frame, init_state)
                output_boxes.append(init_state)
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
            
            state = self.frame_track(frame)
            output_boxes.append(state)

            cv.rectangle(frame_disp, (state[0], state[1]), (state[2] + state[0], state[3] + state[1]),
                         (0, 255, 0), 5)

            font_color = (0, 0, 0)
            cv.putText(frame_disp, 'Tracking!', (20, 30), cv.FONT_HERSHEY_COMPLEX_SMALL, 1.5,
                       font_color, 1)
            cv.putText(frame_disp, 'Press r to reset', (20, 60), cv.FONT_HERSHEY_COMPLEX_SMALL, 1.5,
                       font_color, 1)
            cv.putText(frame_disp, 'Press q to quit', (20, 100), cv.FONT_HERSHEY_COMPLEX_SMALL, 1.5,
                       font_color, 1)
            cv.putText(frame_disp, f'FPS: {1/(time.time()-t)}', (20, 140), cv.FONT_HERSHEY_COMPLEX_SMALL, 2,
                       (0,255,0), 2)
            
            t = time.time()

            # Display the resulting frame
            cv.imshow(display_name, frame_disp)
            key = cv.waitKey(1)
            if key == ord('q'):
                break
            elif key == ord('r'):
                ret, frame = cap.read()
                frame_disp = frame.copy()

                cv.putText(frame_disp, 'Select target ROI and press ENTER', (20, 30), cv.FONT_HERSHEY_COMPLEX_SMALL, 1.5,
                           (0, 0, 0), 1)

                cv.imshow(display_name, frame_disp)
                x, y, w, h = cv.selectROI(display_name, frame_disp, fromCenter=False)
                init_state = [x, y, w, h]
                self.initalize_track_object(frame, init_state)
                output_boxes.append(init_state)

        # When everything done, release the capture
        cap.release()
        cv.destroyAllWindows()
        
    
if __name__ == "__main__":
    # model_path = '/media/hoc/WORK/remote/AnhPhuong/TRACKING_CONTROL_SYSTEM/Projects/RWS_CU/RWS_AI_MODULE/models/artrack/artrack_seq_base_256_full/ARTrackSeq_ep0060.pth.tar'
    # tracker = RWSTracker('artrack_seq', 'artrack_seq_256_full', model_path)
    
    model_path = '/media/hoc/WORK/remote/AnhPhuong/TRACKING_CONTROL_SYSTEM/Projects/RWS_CU/RWS_AI_MODULE/models/odtrack/odtrack_base_full/ODTrack_ep0300.pth.tar'    
    tracker = RWSTracker('odtrack', 'baseline', model_path)
    tracker.test_tracker_v2('/media/hoc/WORK/remote/AnhPhuong/TRACKING_CONTROL_SYSTEM/Projects/RWS_CU/RWS_AI_MODULE/videos/car.mp4')