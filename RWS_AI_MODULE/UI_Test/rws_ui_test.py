import sys
import socket
import numpy as np
import cv2
from PyQt5.QtWidgets import QApplication, QMainWindow, QLabel, QVBoxLayout, QWidget
from PyQt5.QtGui import QImage, QPixmap
from PyQt5.QtCore import Qt, pyqtSignal, QPoint

class ClickableLabel(QLabel):
    # Custom signal to send the click coordinates
    doubleClicked = pyqtSignal(QPoint)

    def mouseDoubleClickEvent(self, event):
        # Emit signal with the mouse click position when a double-click happens
        self.doubleClicked.emit(event.pos())

class FrameReceiver(QMainWindow):
    def __init__(self, ip="127.0.0.1", port=12345):
        super().__init__()

        self.socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        self.socket.bind((ip, port))
        self.buffer = b''  # Buffer to hold incoming data
        self.expected_frame_counter = None
        self.max_package_size = 65450

        # Setup PyQt5 window and QLabel for displaying video
        self.setWindowTitle("Video Stream Receiver")
        self.video_label = ClickableLabel(self)
        self.video_label.setAlignment(Qt.AlignCenter)
        self.video_label.setFixedSize(960, 720)

        # Connect the double-click signal to a handler function
        self.video_label.doubleClicked.connect(self.on_double_click)

        # Layout setup
        layout = QVBoxLayout()
        layout.addWidget(self.video_label)
        container = QWidget()
        container.setLayout(layout)
        self.setCentralWidget(container)

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
        
if __name__ == "__main__":
    app = QApplication(sys.argv)
    
    receiver = FrameReceiver()
    receiver.show()

    # Run the frame receiving in a background thread (not blocking the UI)
    import threading
    thread = threading.Thread(target=receiver.receive_frame, daemon=True)
    thread.start()

    sys.exit(app.exec_())
