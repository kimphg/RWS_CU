import cv2
import threading, os, json
from ultralytics import YOLO


import logging
logging.getLogger('ultralytics').setLevel(logging.ERROR)

from logger import detector_logger as logger

class YOLODetector:
    def __init__(self, model_path=None):
        self.model = None
        self.source = None
        self.class_ids = None  # Initialize class_ids as None to detect all classes by default
        self.tracking_thread = None
        self.stop_event = threading.Event()  # Event to control thread stopping
        self.cap : cv2.VideoCapture = None
        
        
        self.current_result = None  # Stores the latest tracking results
        self.current_frame = None # Stores the last frame
        self.frame_update = False
        self.lock = threading.Lock()
        
        self.conf = 0.2
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

    def set_tracking_conf(self, conf):
        """
        Set tracking conf.
        """
        self.conf = conf
        logger.debug(f'Set yolo tracking conf to: {self.conf}')

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
        results = self.model(frame, classes=self.class_ids, stream=True, conf=self.conf)

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
            results = self.model.track(frame, conf=self.conf, classes=self.class_ids)
            
            self.current_result = results
            self.update_current_frame(frame) # let drawing task for parent module
            
            # logger.debug(f'Tracking result: {self.get_current_result_json()}')
            
            if show:
                # Get the results for the current frame
                for result in results:
                    # Get the bounding boxes, confidences, and tracking IDs from each result
                    boxes = result.boxes.xyxy if result.boxes is not None else []
                    confidences = result.boxes.conf if result.boxes is not None else []
                    class_ids = result.boxes.cls if result.boxes is not None else []
                    track_ids = result.boxes.id if result.boxes is not None else []
                    
                    # track_ids will be None when none of object is tracked
                    if boxes is None or confidences is None or class_ids is None or track_ids is None:
                        continue
                    
                    # Loop through the detected objects
                    for box, confidence, class_id, track_id in zip(boxes, confidences, class_ids, track_ids):
                        x1, y1, x2, y2 = map(int, box)
                        label = f"ID: {track_id}, Conf: {confidence:.2f}, Class: {class_id}"

                        # print(f'Tracking =============={label}==================')
                        # Draw the bounding box and label on the frame
                        cv2.rectangle(frame, (x1, y1), (x2, y2), (0, 255, 0), 2)
                        cv2.putText(frame, label, (x1, y1 - 10), cv2.FONT_HERSHEY_SIMPLEX, 0.5, (0, 255, 0), 2)
            
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

        for result in self.current_result:
            # Get the bounding boxes, confidences, and tracking IDs from each result
            boxes = result.boxes.xyxy if result.boxes is not None else []
            confidences = result.boxes.conf if result.boxes is not None else []
            class_ids = result.boxes.cls if result.boxes is not None else []
            track_ids = result.boxes.id if result.boxes is not None else []
            
            # Loop through the detected objects
            if boxes is not None and track_ids is not None:
                for box, conf, class_id, track_id in zip(boxes, confidences, class_ids, track_ids):
                    x1, y1, x2, y2 = map(int, box)  # Convert to integers
                    parsed_results.append({
                        "id": int(track_id),
                        "class_id": int(class_id),
                        "conf" : float(conf),
                        "bounding_box": {
                            "x1": x1,
                            "y1": y1,
                            "x2": x2,
                            "y2": y2
                        }
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
    time.sleep(5)  # Allow tracking to run for a bit
    print("Current tracking result:", detector.get_current_result_json())

    # Stop tracking after some time
    time.sleep(10)
    detector.stop_tracking()



