import sys
import socket
import numpy as np
import cv2
from PyQt5.QtWidgets import QApplication, QMainWindow, QLabel, QVBoxLayout, QWidget, QHBoxLayout, QPushButton
from PyQt5.QtGui import QImage, QPixmap
from PyQt5.QtCore import Qt, pyqtSignal, QPoint

from PyQt5.QtWidgets import QLabel
from PyQt5.QtCore import pyqtSignal, QPoint

class ClickableLabel(QLabel):
    # Custom signal to send the click coordinates
    doubleClicked = pyqtSignal(QPoint)

    def __init__(self, parent=None):
        super().__init__(parent)
        # Set size policy to be expandable
        self.setSizePolicy(self.sizePolicy().Expanding, self.sizePolicy().Expanding)

    def mouseDoubleClickEvent(self, event):
        # Emit signal with the mouse click position when a double-click happens
        self.doubleClicked.emit(event.pos())


class FrameReceiver(QMainWindow):
    def __init__(self, frame_ip="127.0.0.1", frame_port=12345, data_ip="127.0.0.1", data_port=4000, cmd_ip="127.0.0.1", cmd_port=5000):
        super().__init__()

        self.statusBar().showMessage('Ready')
        self.socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        self.socket.bind((frame_ip, frame_port))
        
        self.data_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        self.data_socket.bind((data_ip, data_port))
        
        self.cmd_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        self.cmd_ip = cmd_ip
        self.cmd_port = cmd_port
        
        self.buffer = b''  # Buffer to hold incoming data
        self.expected_frame_counter = None
        self.max_package_size = 65450
        self.setMinimumSize(800,600)

        # Setup PyQt5 window and QLabel for displaying video
        self.setWindowTitle("Video Stream Receiver")
        self.video_label = ClickableLabel(self)
        self.video_label.setAlignment(Qt.AlignCenter)
        # self.video_label.setFixedSize(960, 720)

        # Connect the double-click signal to a handler function
        self.video_label.doubleClicked.connect(self.on_double_click)
        
        self.current_detection = []
        self.current_frame = None

        # Layout setup
        layout = QVBoxLayout()
        
        tools_layout = QHBoxLayout()
        start_track_button = QPushButton('Start track (First object)')
        stop_track_button = QPushButton('Stop track')
        select_target_to_track = QPushButton('Select target to track')
        
        tools_layout.addWidget(start_track_button)
        tools_layout.addWidget(stop_track_button)
        tools_layout.addWidget(select_target_to_track)
        
        start_track_button.clicked.connect(self.start_track)
        start_track_button.setVisible(False)
        stop_track_button.clicked.connect(self.stop_track)
        select_target_to_track.clicked.connect(self.select_target_to_track)
        
        layout.addLayout(tools_layout)
        layout.addWidget(self.video_label)
        container = QWidget()
        container.setLayout(layout)
        self.setCentralWidget(container)
        
    def start_track(self):
        print('start tracking')
        
    def send_stop_track_command(self):
        print(f'Sending stop tracking command')
        cmd = f'CTC,0,1'
        self.cmd_socket.sendto(cmd.encode('utf-8'), (self.cmd_ip, self.cmd_port))
        
    def send_track_command(self, target_id):
        if target_id is None:
            return
        print(f'Sending tracking command object id: {target_id}')
        cmd = f'CTC,{target_id},0'
        self.cmd_socket.sendto(cmd.encode('utf-8'), (self.cmd_ip, self.cmd_port))
    
    def stop_track(self):
        print('stop tracking')
        self.send_stop_track_command()
        
    def select_target_to_track(self):
        print('select target to track')
        

    def receive_frame(self):
        while True:
            # Receive data from socket
            data, addr = self.socket.recvfrom(65507)  # Maximum UDP packet size
            if not data:
                continue

            # Extract chunk header (first 2 bytes)
            chunk_index = data[0]  # First byte is the chunk index
            frame_counter = data[1]  # Second byte is the frame counter

            # Extract chunk data
            chunk_data = data[2:]  # Remaining bytes are the chunk data

            # If this is the first chunk of a new frame, reset the buffer
            if self.expected_frame_counter is None or self.expected_frame_counter != frame_counter:
                self.buffer = b''  # Reset buffer for a new frame
                self.expected_frame_counter = frame_counter

            # Append the received chunk data to the buffer
            self.buffer += chunk_data

            # If the last chunk is received, decode and display the frame
            if chunk_index == (len(self.buffer) // self.max_package_size):
                # Convert byte data to numpy array
                np_array = np.frombuffer(self.buffer, np.uint8)

                # Decode the image from the array
                frame = cv2.imdecode(np_array, cv2.IMREAD_COLOR)

                if frame is not None:
                    self.display_frame(frame)

                # Clear the buffer after processing the frame
                self.buffer = b''
                self.expected_frame_counter = None

    def display_frame(self, frame):
        """Convert the frame (numpy array) to QImage and display it in QLabel."""
        self.current_frame = frame
        
        height, width, channel = frame.shape
        bytes_per_line = 3 * width
        
                # Convert from BGR (OpenCV format) to RGB (for QImage)
        frame_rgb = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)

        # Convert the RGB frame to QImage
        q_image = QImage(frame_rgb.data, width, height, bytes_per_line, QImage.Format_RGB888)
        # q_image = QImage(frame.data, width, height, bytes_per_line, QImage.Format_BGR888)
        pixmap = QPixmap.fromImage(q_image)
        scaled_pixmap = pixmap.scaled(self.video_label.size(), Qt.KeepAspectRatio)

        # Set the QImage to the QLabel
        self.video_label.setPixmap(scaled_pixmap)

    def on_double_click(self, position):
        """Handle the double-click event and get the position of the mouse."""
        print(f"Double-click at: {position.x()}, {position.y()}")

        if self.current_frame is not None and self.current_detection:
            # Get the dimensions of the current frame
            frame_height, frame_width, _ = self.current_frame.shape
            
            # Get the dimensions of the QLabel (displayed size)
            label_height = self.video_label.height()
            label_width = self.video_label.width()

            # Calculate the scaling factors
            scale_x = label_width / frame_width
            scale_y = label_height / frame_height

            # Adjust the click position according to the scaling factor
            adjusted_x = position.x() / scale_x
            adjusted_y = position.y() / scale_y

            # Check if the adjusted coordinates are inside any detection bounding boxes
            print(self.current_detection)
            for detection in self.current_detection:
                detection_id, x1, y1, w, h = detection  # Assuming detection is in the format [id, x1, y1, w, h]
                # Check if the adjusted coordinates are within the bounding box
                if x1 <= adjusted_x <= x1 + w and y1 <= adjusted_y <= y1 + h:
                    print(f"Clicked inside bounding box of detection ID: {detection_id}")
                    # send tracking object command to tracker
                    self.send_track_command(detection_id)
                    return detection_id  # Return the ID of the detection found

        print("Click is outside any detection bounding box.")
        return None  # Return None if no detection is found
        
    def receive_data(self):
        while True:
            # Receive data from socket
            data, addr = self.data_socket.recvfrom(65507)  # Maximum UDP packet size
            if not data:
                continue
            
            data_str = data.decode('utf-8')
            # Split the string by commas
            parts = data_str.split(",")

            # Check if the string starts with the expected header "TTM"
            # if not parts or parts[0] != "TTM":

            if not parts:
                print('invalid data received.')
                continue
            
            if parts[0] == "TTM": # detection data
                # Get the number of targets
                n_target = int(parts[1])

                # Initialize an empty list to hold the parsed results
                parsed_results = []

                # Iterate through the parts, starting from index 2 (after the header and n_target)
                index = 2
                for _ in range(n_target):
                    # Parse each track's information and append it as a list [id, x1, y1, w, h]
                    track_id = int(parts[index])
                    x1 = int(parts[index + 1])
                    y1 = int(parts[index + 2])
                    w = int(parts[index + 3])
                    h = int(parts[index + 4])

                    # Append the parsed object as a list [id, x1, y1, w, h] to the results
                    parsed_results.append([track_id, x1, y1, w, h])

                    # Move to the next set of track data (each track has 5 parts: id, x1, y1, w, h)
                    index += 5
                self.current_detection = parsed_results
                # print('detection data: ', parsed_results)
                
            elif parts[0] == "TNO":
                notify_str = parts[1]
                print(f'Get notify: {notify_str}')
                self.statusBar().showMessage(notify_str)

        # return parsed_results
        
if __name__ == "__main__":
    app = QApplication(sys.argv)
    
    receiver = FrameReceiver()
    receiver.show()

    # Run the frame receiving in a background thread (not blocking the UI)
    import threading
    receive_frame_thread = threading.Thread(target=receiver.receive_frame, daemon=True)
    receive_frame_thread.start()
    
    receive_data_thread = threading.Thread(target=receiver.receive_data, daemon=True)
    receive_data_thread.start()

    sys.exit(app.exec_())
