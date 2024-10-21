import cv2
import threading, os, json
from ultralytics import YOLO
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
        
        self.deepsort_tracker = DeepSort(max_age=max_age, max_iou_distance=max_iou_distance, n_init=n_init, nms_max_overlap=nms_max_overlap)

        if model_path:
            self.set_model(model_path)
            
    def set_videocapture(self, cap):
        logger.debug('Video capture source set.')
        self.cap = cap

    def set_model(self, model_path):
        """
        Load a YOLO model from the specified path.
        """
        try:
            self.model = YOLO(model_path)
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
            logger.info("Tracking thread is not running.")
            return None
        
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



