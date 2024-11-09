import cv2
import threading, os, json
from ultralytics import YOLO
from vidstab import VidStab
from deep_sort_realtime.deepsort_tracker import DeepSort


import logging
logging.getLogger('ultralytics').setLevel(logging.ERROR)

import sys
prj_path = os.path.join(os.path.dirname(__file__), '..')
if prj_path not in sys.path:
    sys.path.append(prj_path)
from logger import detector_logger as logger

class YOLODetector:
    def __init__(self, model_path=None, detect_conf=0.2, class_ids=None, conf=0.2, max_iou_distance=0.7, max_age=30, n_init=3, nms_max_overlap=1.0, track_conf=0.5):
        self.model = None
        self.source = None # video source path, parent assign if needed
        self.class_ids = None  # Initialize class_ids as None to detect all classes by default
        self.tracking_thread = None
        self.stop_event = threading.Event()  # Event to control thread stopping
        self.cap : cv2.VideoCapture = None # for parent assign
        
        self.current_result = None  # Stores the latest tracking results
        self.current_frame = None # Stores the last frame
        self.frame_update = False
        self.class_ids = class_ids
        self.detect_conf = detect_conf
        self.track_conf = track_conf
        
        self.process_video_width = 1024 
        self.process_video_height = 768
        
        self.deepsort_tracker = DeepSort(max_age=max_age, max_iou_distance=max_iou_distance, n_init=n_init, nms_max_overlap=nms_max_overlap)
        
        # video stabilizer
        self.stabilizer = VidStab()
        self.enable_stabilizer = False # default false
        self.stabilizer_smoothing_window = 5 # default 5
        self.feed_stablizer_frame_index = 0

        self.model_path = model_path
        if model_path:
            self.set_model(model_path)
            
    def set_videocapture(self, cap):
        logger.debug('Video capture source set.')
        self.cap = cap
        # refresh vidstab because frame size maybe changed, will got error
        self.stabilizer = VidStab()
        self.feed_stablizer_frame_index = 0
        
    def set_process_video_size(self, process_w, process_h):
        self.process_video_width = process_w
        self.process_video_height = process_h
        self.stabilizer = VidStab()
        self.feed_stablizer_frame_index = 0

        
    def set_enable_stabilizer(self, enable):
        self.enable_stabilizer = enable
        if enable:
            logger.debug(f'Enabled video stabilizer')
            self.feed_stablizer_frame_index = 0
        else:
            logger.debug(f'Disabled video stabilizer')
            
    def set_model(self, model_path):
        """
        Load a YOLO model from the specified path.
        """
        try:
            self.model = YOLO(model_path)
            self.model_path = model_path
            logger.info(f"Model loaded from {model_path}")
        except Exception as e:
            logger.error(f"Error loading model: {e}")

    def set_detect_conf(self, conf):
        """
        Set detect conf.
        """
        self.detect_conf = conf
        logger.debug(f'Set yolo detection conf to: {self.detect_conf}')
    
    def set_deepsort_tracking_conf(self, conf):
        """
        Set tracking conf.
        """
        self.track_conf = conf
        logger.debug(f'Set yolo deepsort tracking conf to: {self.track_conf}')

    def set_class_ids(self, class_ids):
        """
        Set specific class IDs to track. If class_ids is None, all classes will be detected.
        """
        self.class_ids = class_ids
        if self.class_ids is not None:
            logger.debug(f"Tracking will be limited to class IDs: {self.class_ids}")
        else:
            logger.debug("Tracking will include all class IDs.")

    def detect_frame(self, frame):
        """
        Detect objects in a single frame and return filtered results based on the class IDs.
        """
        if self.model is None:
            logger.error("Model is not set. Use set_model() to load a YOLO model.")
            return None

        # Detect objects in the frame using `model()`
        results = self.model(frame, classes=self.class_ids, stream=True, conf=self.detect_conf)

        detections = []
        for result in results:
            detections.append(result)
        return detections

    def start_tracking(self, show=False):
        """
        Start tracking the objects from the video source in a separate thread using the YOLO `track()` method.
        Only objects matching the specified class IDs will be tracked.
        """
        if self.model is None:
            logger.error("Model is not set. Use set_model() to load a YOLO model.")
            return
        
        if self.deepsort_tracker is None:
            logger.error("Tracker of yolo detector is not set")
            return
        
        if self.tracking_thread is None or not self.tracking_thread.is_alive():
            self.stop_event.clear()  # Clear any previous stop event
            self.tracking_thread = threading.Thread(target=self._track_video, args=(show,))
            self.tracking_thread.start()

    def _track_video(self, show=False):
        """
        Internal method to process the video and track objects using YOLOv8's `model.track()` function.
        This method runs in a separate thread and continuously processes video frames.
        """
        logger.debug(f'Start detect and tracking from videosource')
        
        if self.cap is None:
            logger.error("Video capcutre is not set.")
            return
        
        # cap = cv2.VideoCapture(self.source)
        if not self.cap.isOpened():
            logger.error("Video capture not opened.")
            return
        
        # Loop over frames
        while True:
            # stop tracking when stop event set
            if self.stop_event.is_set():
                break
            
            ret, frame = self.cap.read()
            
            # Break the loop if no frame is returned (end of video)
            if not ret:
                break
            
            # resize if need
            if frame.shape[1] != self.process_video_width or frame.shape[0] != self.process_video_height:
                frame = cv2.resize(frame, (self.process_video_width, self.process_video_height), interpolation=cv2.INTER_AREA)
            
            # stablilze frame
            if self.enable_stabilizer:
                if self.feed_stablizer_frame_index < self.stabilizer_smoothing_window:
                    # warming up, this will return black frame
                    self.stabilizer.stabilize_frame(frame, smoothing_window=self.stabilizer_smoothing_window) 
                    self.feed_stablizer_frame_index += 1
                else:
                    frame = self.stabilizer.stabilize_frame(frame, smoothing_window=self.stabilizer_smoothing_window)
                
                if frame is None:
                    logger.debug('Stablize frame return None')
                    continue
                
            # Use YOLO model to detect and track objects in the current frame
            # logger.debug('Inference model....')
            # results = self.model.track(frame, conf=self.conf, classes=self.class_ids)
            results = self.model(frame, save=False, conf=self.detect_conf)[0]
            
            detections = []
            for det in results.boxes:
                label, confidence, bbox = det.cls, det.conf, det.xyxy[0]
                x1, y1, x2, y2 = map(int, bbox)
                class_id = int(label)

                detections.append([[x1, y1, x2 - x1, y2 - y1], confidence, class_id])
                
            tracks = self.deepsort_tracker.update_tracks(detections, frame=frame)

            
            self.current_result = tracks
            self.update_current_frame(frame) # let drawing task for parent module
            
            # logger.debug(f'Tracking result: {self.get_current_result_json()}')
            # print('Tracks: ', self.get_current_result_json())
            
            if show:
                # Get the results for the current frame
                for track in tracks:
                    if not track.is_confirmed():
                        continue
                    track_id = track.track_id  # Unique ID for the object
                    x1, y1, w, h = track.to_ltwh()  # Bounding box (left, top, width, height)

                    # Draw bounding box and object ID on the frame
                    cv2.rectangle(frame, (int(x1), int(y1)), (int(x1 + w), int(y1 + h)), (0, 255, 0), 2)
                    cv2.putText(frame, f'ID: {track_id}', (int(x1), int(y1) - 10), cv2.FONT_HERSHEY_SIMPLEX, 0.6, (0, 255, 0), 2)
                    cv2.imshow("Yolo detect and tracking preview", cv2.resize(frame, (frame.shape[1]//2, frame.shape[0]//2)))

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
        Stop the tracking thread.
        """
        if self.tracking_thread is not None and self.tracking_thread.is_alive():
            self.stop_event.set()  # Signal the thread to stop
            self.tracking_thread.join()  # Wait for the thread to finish
            self.tracking_thread = None
            self.deepsort_tracker.delete_all_tracks() # delete all current tracks, reset all ids
            logger.info("Tracking stopped.")

    def get_current_tracking_result(self):
        """
        Get the current tracking result, which is updated by the tracking thread.
        Returns the latest result if tracking is active.
        """
        if self.tracking_thread is not None and self.tracking_thread.is_alive():
            return self.current_result
        else:
            logger.info("Yolo Tracking thread is not running.")
            return None
        
    def get_current_result_string(self):
        """
        Parse the current tracking results into a string format:
        TTM,n_target, bb1id, bb1x,bb1y,bb1w,bb1h, ..., bbnid,bbnx,bbny,bbnw,bbnh

        Returns:
            str: A formatted string containing the tracking results for each object.
        """
        if not self.current_result:
            return "TTM,0"  # Return the header with no targets if no results are available

        result_parts = ["TTM"]  # Start with the header
        n_target = 0  # Counter for the number of valid tracks

        # Iterate through the tracking results
        for track in self.current_result:
            if not track.is_confirmed():
                continue  # Skip unconfirmed tracks

            # Extract track details
            track_id = track.track_id  # Unique ID for the object
            x1, y1, w, h = track.to_ltwh()  # Bounding box (left, top, width, height)
            conf = track.get_det_conf()
            if conf is None:
                conf = 0  # If there's no associated detection, set confidence to 0
            
            # Increment the valid track counter
            n_target += 1

            # Append the bounding box and ID info to the result
            result_parts.append(f"{track_id},{int(x1)},{int(y1)},{int(w)},{int(h)}")

        # Add the target count at the second position
        result_parts.insert(1, str(n_target))

        # Join the result parts into a comma-separated string
        return ",".join(result_parts)
    
    def get_current_result_string_v2(self):
        """
        Parse the current tracking results into a string format:
        TTM,n_target, bb1id, bb1centerx, bb1centery, bb1w, bb1h, ..., bbnid, bbncenterx, bbncentery, bbnw, bbnw

        Returns:
            str: A formatted string containing the tracking results for each object.
        """
        if not self.current_result:
            return "TTM,0"  # Return the header with no targets if no results are available

        result_parts = ["TTM"]  # Start with the header
        n_target = 0  # Counter for the number of valid tracks

        # Iterate through the tracking results
        for track in self.current_result:
            if not track.is_confirmed():
                continue  # Skip unconfirmed tracks

            # Extract track details
            track_id = track.track_id  # Unique ID for the object
            x1, y1, w, h = track.to_ltwh()  # Bounding box (left, top, width, height)
            conf = track.get_det_conf()
            if conf is None:
                conf = 0  # If there's no associated detection, set confidence to 0
                
            # Convert to center and normalize width/height
            center_x = (x1 + w / 2) / self.process_video_width  # Normalize center x to [0, 1]
            center_y = (y1 + h / 2) / self.process_video_height  # Normalize center y to [0, 1]
            norm_w = w / self.process_video_width  # Normalize width to [0, 1]
            norm_h = h / self.process_video_height  # Normalize height to [0, 1]
            
            # Increment the valid track counter
            n_target += 1

            # Append the bounding box and ID info to the result
            # result_parts.append(f"{track_id},{int(x1)},{int(y1)},{int(w)},{int(h)}")
            result_parts.append(f"{track_id},{center_x:.6f},{center_y:.6f},{norm_w:.6f},{norm_h:.6f}")

        # Add the target count at the second position
        result_parts.insert(1, str(n_target))

        # Join the result parts into a comma-separated string
        return ",".join(result_parts)
        
    def get_current_result_json(self):
        """
        Parse the current tracking results into a JSON format.

        Returns:
            str: A JSON string containing the tracking results for each object.
        """
        if not self.current_result:
            return json.dumps([])  # Return an empty JSON array if no results are available

        parsed_results = []

        for track in self.current_result:
            if not track.is_confirmed():
                continue  # Skip unconfirmed tracks
            
            # Extract track details
            track_id = track.track_id  # Unique ID for the object
            x1, y1, w, h = track.to_ltwh()  # Bounding box (left, top, width, height)
            conf = track.get_det_conf()
            if conf is None: # there are no associated detection the round of this track
                conf = 0
            class_id = track.get_det_class()

            # Prepare the result entry
            parsed_results.append({
                "id": int(track_id),
                "bounding_box": {
                    "x1": int(x1),
                    "y1": int(y1),
                    "w": int(w),
                    "h": int(h)
                },
                "conf": float(conf),  # Assuming confidence is an attribute
                "class_id": class_id  # Get class ID if available
            })

        return json.dumps(parsed_results)  # Convert the list of dicts to a JSON string

# Example usage
if __name__ == "__main__":
    detector = YOLODetector()
    
    current_dir = os.path.dirname(os.path.abspath(__file__))  # This is your Project Root
    yolo_model_path = os.path.join(current_dir, '../models/yolo/yolov10l.pt')
    test_video_path = os.path.join(current_dir, '../videos/car2.mp4')
    
    cap = cv2.VideoCapture(test_video_path)
    
    
    detector.set_model(yolo_model_path)  # Set the YOLO model
    detector.set_videocapture(cap)
    # detector.set_class_ids([7])  # Set specific class IDs to track (e.g., 2 for cars, 7 for trucks)
    detector.start_tracking(show=True)  # Start tracking in a separate thread

    # Example: Get current tracking result
    import time
    # time.sleep(5)  # Allow tracking to run for a bit
    # print("Current tracking result:", detector.get_current_result_json())

    # Stop tracking after some time
    time.sleep(10)
    detector.stop_tracking()



