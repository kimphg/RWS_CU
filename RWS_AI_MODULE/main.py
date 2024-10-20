
from RWS_Detection.yolo_detector import YOLODetector
import os, threading, sys
import cv2
import socket
from module_config import ModuleConfig
from logger import logger, detector_logger, tracker_logger
import logging
import configparser
import numpy as np
import time
from drawer import *

prj_path = os.path.join(os.path.dirname(__file__), 'RWS_Tracker')
if prj_path not in sys.path:
    sys.path.append(prj_path)
from RWS_Tracker.rws_tracker import RWSTracker

class RWSModule():
    def __init__(self, config_path='config.ini'):
        self.config = configparser.ConfigParser()
        self.config.read(config_path) 
        
        # set log level
        logger.setLevel(self.config.get('settings', 'log_level', fallback=logging.INFO))
        detector_logger.setLevel(self.config.get('detector', 'log_level', fallback=logging.INFO))
        tracker_logger.setLevel(self.config.get('tracker', 'log_level', fallback=logging.INFO))
        
        # general settings
        self.video_source = self.config.get('settings', 'video_source', fallback=0)
        self.frame_counter = 0 # index of frame for seding via UDP
        
        self.exploration_mode_stop_event = threading.Event()
        self.exploration_thread = None
        
        if self.video_source is not None:
            logger.info(f'Connecting to video source: {self.video_source}')
            self.cap = cv2.VideoCapture(self.video_source)
            if not self.cap.isOpened():
                logger.warning(f'Cannot connect to video source: {self.video_source}')
            else:
                logger.info(f'Succeed connect to video source: {self.video_source}')
        else:
            self.cap = None
    
        # detector settings
        self.detector = None
        if self.config.get('detector', 'type', fallback='yolo') == 'yolo':
            logger.info('Initializing moduule detector...')
            self.detector = YOLODetector()
            self.detector.set_model(self.config.get('detector','model_path', fallback=''))
            self.detector.set_class_ids(self.config.get('detector','class_ids', fallback=None))
            self.detector.set_videocapture(self.cap)
        else:
            logger.warning('Detector config is not set!')
        
        
        # tracker settings
        self.tracker_name = self.config.get('tracker', 'name',fallback='artrack')
        self.tracker_param = self.config.get('tracker', 'param',fallback='artrack_seq_256_full')
        self.tracker_model = self.config.get('tracker', 'model_path',fallback='models/artrack/artrack_seq_base_256_full/ARTrackSeq_ep0060.pth.tar')
        self.tracker = RWSTracker(self.tracker_name, self.tracker_param, self.tracker_model)
        
        
        # socket settings
        ## setting for seding a frame
        self.max_package_size = int(self.config.get('socket', 'max_package_size', fallback=65507))
        self.max_chunks = int(self.config.get('socket', 'max_chunks', fallback=10))
        self.dest_frame_ip = self.config.get('socket', 'dest_frame_ip', fallback='127.0.0.1')
        self.dest_frame_port = int(self.config.get('socket', 'dest_frame_port', fallback=12345))
        self.dest_detection_ip = self.config.get('socket', 'dest_detection_ip', fallback='127.0.0.1')
        self.dest_detection_port = int(self.config.get('socket', 'dest_detection_port', fallback=4000))
        self.recv_command_ip = self.config.get('socket', 'recv_command_ip', fallback='127.0.0.1')
        self.recv_command_port = int(self.config.get('socket', 'recv_command_port', fallback=4001))
        
        logger.debug("Configuration Values:")
        logger.debug(f"Max Package Size: {self.max_package_size}")
        logger.debug(f"Max Chunks: {self.max_chunks}")
        logger.debug(f"Destination Frame IP: {self.dest_frame_ip}")
        logger.debug(f"Destination Frame Port: {self.dest_frame_port}")
        logger.debug(f"Destination Detection IP: {self.dest_detection_ip}")
        logger.debug(f"Destination Detection Port: {self.dest_detection_port}")
        logger.debug(f"Receive Command IP: {self.recv_command_ip}")
        logger.debug(f"Receive Command Port: {self.recv_command_port}")
        
        ## init socket
        self.send_frame_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        
    def send_frame(self, frame, frame_counter, address):
        ret, buffer = cv2.imencode('.jpeg', frame, [cv2.IMWRITE_JPEG_QUALITY, 90])
        if not ret:
            logger.error("Failed to encode image")
            return
        
        data = buffer.tobytes()
        num_chunks = (len(data) // self.max_package_size) + 1

        if num_chunks > self.max_chunks:
            return  # Frame too large to send, skip

        for i in range(num_chunks):
            chunk_header = bytes([i, frame_counter])
            chunk = data[i * self.max_package_size:(i + 1) * self.max_package_size]
            self.send_frame_socket.sendto(chunk_header + chunk, address)
            
            # print(f'send {len(chunk_header + chunk)} bytes - index: {i}')
            # need to sleep, dont know why last UDP package loss when num_chunks >= 5
            # TODO: Fix it
            if num_chunks >= 5: 
                time.sleep(0.0005) 
            # time.sleep(0.001)

    def start_exploration_mode(self):
        # TODO: stop the current tracker if need
        
        if self.detector is None:
            logger.error('Module tracker is not initalized')
            # TODO: send error to Controller
            return
        if not self.cap.isOpened():
            logger.error('Video source is not activate')
            # TODO: send error to Controller
            return
        
        self.detector.stop_tracking() # stop current tracking if running
        self.detector.set_videocapture(self.cap)
        self.detector.start_tracking(show=False) # start exploration objects and send result to Controller
            
        if self.exploration_thread is None or not self.exploration_thread.is_alive():
            self.exploration_mode_stop_event.clear()
            self.exploration_thread = threading.Thread(target=self._start_send_exploration_result, args=())
            self.exploration_thread.start()

    def _start_send_exploration_result(self):
        logger.info('Start sendding exploration data to Controller...')
        # get the result and send frame via socket
        import time
        
        t = time.time()
        while True:
            if self.exploration_mode_stop_event.is_set():
                break
            
            if self.detector.frame_update == True:
                frame_send = np.copy(self.detector.current_frame) # copy new frame to send for prevent long time access to self.detector.current_frame, allow detector conituosly update frame
                frame_send = draw_yolo_result(frame_send, self.detector.get_current_tracking_result()) # draw frame
                
                self.send_frame(frame_send, self.frame_counter, (self.dest_frame_ip, self.dest_frame_port))
                
                logger.debug(f'Frame sent with id: {self.frame_counter} - FPS: {1/(time.time()-t)}')
                t = time.time()
                
                self.frame_counter = (self.frame_counter + 1)%255
                # TODO: send current detection result
                self.detector.frame_update = False
                
                # drawn frame
                
                cv2.imshow('FRAME', cv2.resize(frame_send, (600,800)))
                cv2.waitKey(20)
                
                # print(f'FPS: {1/(time.time()-t)}')
                # t = time.time()

            # MUST wait a bit for prevent thread resource blocking between rws module and detector
            cv2.waitKey(1)
            
        self.detector.stop_tracking()
                
def test_exploration_mode():
    rws_module = RWSModule()
    # rws_module.test_exploration_mode()
    rws_module.start_exploration_mode()
    time.sleep(10)
    # print('Stop tracking')
    rws_module.exploration_mode_stop_event.set()
    
def test_tracker():
    rws_module = RWSModule()
    rws_module.tracker.test_tracker_v2('videos/car2.mp4')
        
def test_detector():
    module = RWSModule()
    
    # current_dir = os.path.dirname(os.path.abspath(__file__))  # This is your Project Root
    # yolo_model_path = os.path.join(current_dir, './models/yolo/yolov10l.pt')
    # test_video_path = os.path.join(current_dir, './videos/car2.mp4')
    
    # module.detector.set_model(yolo_model_path)
    # module.video_source = test_video_path
    # module.cap = cv2.VideoCapture(module.video_source)
    # module.detector.set_videocapture(module.cap)
    
    # start tracking in video source
    # module.detector.start_tracking()
    
    namedwindow = "YOLO Detection & Tracking"
    cv2.namedWindow(namedwindow)
    cv2.resizeWindow(namedwindow, 600, 800) 
    
    import numpy as np
    wait_update_frame = np.zeros((800, 600, 3), dtype=np.uint8)  # Create a black frame
    cv2.putText(wait_update_frame, "WAIT FOR UPDATE", (250, 300), cv2.FONT_HERSHEY_SIMPLEX, 1, (255, 255, 255), 2, cv2.LINE_AA)
    module.detector.start_tracking(False)
    
    while True:
        if module.detector.frame_update == True:
            cv2.imshow(namedwindow, cv2.resize(module.detector.current_frame, (600,800)))
            
            # test send frame
            logger.debug(f'Send the frame with id: {module.frame_counter}')
            frame_send = np.copy(module.detector.current_frame)
            module.send_frame(frame_send, module.frame_counter, (module.dest_frame_ip, module.dest_frame_port))
            
            module.frame_counter = (module.frame_counter + 1) % 255
            module.detector.frame_update = False
        else: 
            cv2.imshow(namedwindow, wait_update_frame)
            # print('Waiting for update...')
        
        key = cv2.waitKey(30)
        if key == ord('s'):
            module.detector.stop_tracking()
        elif key == ord('r'):
            module.detector.start_tracking(False)
        elif key == ord('q'):
            module.detector.stop_tracking()
            break        
        
if __name__ == "__main__":
    # test_detector()
    # test_exploration_mode()
    test_tracker()
    
    
    
        