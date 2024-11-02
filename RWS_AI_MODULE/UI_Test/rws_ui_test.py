import sys
import socket
import numpy as np
import cv2
from PyQt5.QtWidgets import QApplication, QMainWindow, QLabel, QVBoxLayout, QWidget, \
    QHBoxLayout, QPushButton, QMessageBox, QGridLayout, QLineEdit, QDialog, QTextEdit, QPlainTextEdit
from PyQt5.QtGui import QImage, QPixmap
from PyQt5.QtCore import Qt, pyqtSignal, QPoint

from PyQt5.QtWidgets import QLabel
from PyQt5.QtCore import pyqtSignal, QPoint
import random, time

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
        
class ControlCenter(QDialog):
    def __init__(self, parent, cmd_ip="127.0.0.1", cmd_port=5000):
        super().__init__(parent)
        self.setWindowTitle("CONTROL CENTER")
        self.cmd_ip = cmd_ip
        self.cmd_port = cmd_port
        self.cmd_addr = (cmd_ip, cmd_port)
        self.socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        
        main_layout = QGridLayout()
        
        # Row 0: Video Source
        self.set_vidsrc_lineedit = QLineEdit()
        self.set_vidsrc_button = QPushButton("Set Video source")
        main_layout.addWidget(QLabel("Set videosource"), 0,0)
        main_layout.addWidget(self.set_vidsrc_lineedit, 0,1)
        main_layout.addWidget(self.set_vidsrc_button, 0,2)
        self.set_vidsrc_button.clicked.connect(self.set_videosrc)
        
        # Row 1: Detection Confidence
        self.dconf_lineedit = QLineEdit()
        self.dconf_button = QPushButton("Set Detection Confidence")
        main_layout.addWidget(QLabel("Detection Confidence"), 1, 0)
        main_layout.addWidget(self.dconf_lineedit, 1, 1)
        main_layout.addWidget(self.dconf_button, 1, 2)
        self.dconf_button.clicked.connect(self.set_dconf)

        # Row 2: Tracking Confidence
        self.tconf_lineedit = QLineEdit()
        self.tconf_button = QPushButton("Set Tracking Confidence")
        main_layout.addWidget(QLabel("Tracking Confidence"), 2, 0)
        main_layout.addWidget(self.tconf_lineedit, 2, 1)
        main_layout.addWidget(self.tconf_button, 2, 2)
        self.tconf_button.clicked.connect(self.set_tconf)

        # Row 3: Detection Model
        self.dmodel_lineedit = QLineEdit()
        self.dmodel_button = QPushButton("Set Detection Model")
        main_layout.addWidget(QLabel("Detection Model"), 3, 0)
        main_layout.addWidget(self.dmodel_lineedit, 3, 1)
        main_layout.addWidget(self.dmodel_button, 3, 2)
        self.dmodel_button.clicked.connect(self.set_dmodel)

        # Row 4: Tracking Model
        self.tmodel_lineedit = QLineEdit()
        self.tmodel_button = QPushButton("Set Tracking Model")
        main_layout.addWidget(QLabel("Tracking Model"), 4, 0)
        main_layout.addWidget(self.tmodel_lineedit, 4, 1)
        main_layout.addWidget(self.tmodel_button, 4, 2)
        self.tmodel_button.clicked.connect(self.set_tmodel)

        # Row 5: Show FPS
        self.showfps_lineedit = QLineEdit()
        self.showfps_button = QPushButton("Set Draw FPS")
        main_layout.addWidget(QLabel("Draw FPS (1: Yes, 0: No)"), 5, 0)
        main_layout.addWidget(self.showfps_lineedit, 5, 1)
        main_layout.addWidget(self.showfps_button, 5, 2)
        self.showfps_button.clicked.connect(self.set_showfps)

        # Row 6: Show Detection/Tracking Result
        self.showresult_lineedit = QLineEdit()
        self.showresult_button = QPushButton("Set Draw Result")
        main_layout.addWidget(QLabel("Draw Result (1: Yes, 0: No)"), 6, 0)
        main_layout.addWidget(self.showresult_lineedit, 6, 1)
        main_layout.addWidget(self.showresult_button, 6, 2)
        self.showresult_button.clicked.connect(self.set_showresult)

        # Row 7: Reconnect Video Source
        self.recvid_button = QPushButton("Reconnect Video Source")
        main_layout.addWidget(QLabel("Reconnect Video"), 7, 0)
        main_layout.addWidget(self.recvid_button, 7, 1)
        self.recvid_button.clicked.connect(self.reconnect_video)
        
        # Row 8: Confirm track
        self.confirm_track_button = QPushButton("Confirm track")
        main_layout.addWidget(QLabel("Confirm track"), 8, 0)
        main_layout.addWidget(self.confirm_track_button, 8, 1)
        self.confirm_track_button.clicked.connect(self.confirm_track)
        
        # Row 9: Tracking IOU Thresh
        self.tiou_lineedit = QLineEdit()
        self.tiou_button = QPushButton("Set Tracking IOU")
        main_layout.addWidget(QLabel("Tracking IOU threshold"), 9, 0)
        main_layout.addWidget(self.tiou_lineedit, 9, 1)
        main_layout.addWidget(self.tiou_button, 9, 2)
        self.tiou_button.clicked.connect(self.set_tiou)
        
        
        # Row 10: Tracking ALPHA (Histogram adapt rate)
        self.talpha_lineedit = QLineEdit()
        self.talpha_button = QPushButton("Set Tracking Alpha")
        main_layout.addWidget(QLabel("Tracking Alpha"), 10, 0)
        main_layout.addWidget(self.talpha_lineedit, 10, 1)
        main_layout.addWidget(self.talpha_button, 10, 2)
        self.talpha_button.clicked.connect(self.set_talpha)
        
        # Row 11: Tracking hist (Histogram diff thresh)
        self.thist_lineedit = QLineEdit()
        self.thist_button = QPushButton("Set Tracking Hist")
        main_layout.addWidget(QLabel("Tracking Histogram Threshold"), 11, 0)
        main_layout.addWidget(self.thist_lineedit, 11, 1)
        main_layout.addWidget(self.thist_button, 11, 2)
        self.thist_button.clicked.connect(self.set_thist)
        
        # Row 12: Video stabilizer enable
        self.vidstab_enable_lineedit = QLineEdit()
        self.vidstab_enable_button = QPushButton("Set vidstab")
        main_layout.addWidget(QLabel("Enable Video stable (1: Yes, 0: No)"), 12, 0)
        main_layout.addWidget(self.vidstab_enable_lineedit, 12, 1)
        main_layout.addWidget(self.vidstab_enable_button, 12, 2)
        self.vidstab_enable_button.clicked.connect(self.set_vidstab_enable)
        
        # Row 13: Video stabilizer smoothing window
        self.vidstab_sm_lineedit = QLineEdit()
        self.vidstab_sm_button = QPushButton("Set vidstab sm")
        main_layout.addWidget(QLabel("Vidstab smoothing window"), 13, 0)
        main_layout.addWidget(self.vidstab_sm_lineedit, 13, 1)
        main_layout.addWidget(self.vidstab_sm_button, 13, 2)
        self.vidstab_sm_button.clicked.connect(self.set_vidstab_sm)

        
        self.setLayout(main_layout)

    def set_vidstab_enable(self):
        cmd = f'CCS,VIDSTAB,{self.vidstab_enable_lineedit.text()}'
        self.send_command(cmd)
        
    def set_vidstab_sm(self):
        cmd = f'CCS,VIDSTABSM,{self.vidstab_sm_lineedit.text()}'
        self.send_command(cmd)

    def send_command(self, command):
        print(f'Sending command: {command}')
        self.socket.sendto(command.encode('utf-8'), (self.cmd_ip, self.cmd_port))
    
    # Video Source
    def set_videosrc(self):
        cmd = f'CCS,VIDSRC,{self.set_vidsrc_lineedit.text()}'
        self.send_command(cmd)

    # Detection Confidence
    def set_dconf(self):
        cmd = f'CCS,DCONF,{self.dconf_lineedit.text()}'
        self.send_command(cmd)

    # Tracking Confidence
    def set_tconf(self):
        cmd = f'CCS,TCONF,{self.tconf_lineedit.text()}'
        self.send_command(cmd)
        
    def set_tiou(self):
        cmd = f'CCS,TIOU,{self.tiou_lineedit.text()}'
        self.send_command(cmd)
    
    def set_talpha(self):
        cmd = f'CCS,TALPHA,{self.talpha_lineedit.text()}'
        self.send_command(cmd)
    
    def set_thist(self):
        cmd = f'CCS,THIST,{self.thist_lineedit.text()}'
        self.send_command(cmd)

    # Detection Model
    def set_dmodel(self):
        cmd = f'CCS,DMODEL,{self.dmodel_lineedit.text()}'
        self.send_command(cmd)

    # Tracking Model
    def set_tmodel(self):
        cmd = f'CCS,TMODEL,{self.tmodel_lineedit.text()}'
        self.send_command(cmd)

    # Show FPS
    def set_showfps(self):
        cmd = f'CCS,DRAWFPS,{self.showfps_lineedit.text()}'
        self.send_command(cmd)

    # Show Detection/Tracking Result
    def set_showresult(self):
        cmd = f'CCS,DRAWRESULT,{self.showresult_lineedit.text()}'
        self.send_command(cmd)

    # Reconnect Video Source
    def reconnect_video(self):
        cmd = 'CCS,RECVID'
        self.send_command(cmd)
        
    def confirm_track(self):
        cmd = 'CCS,CONFIRMTRACK'
        self.send_command(cmd)
        
    
            

class RWSController(QMainWindow):
    log_signal = pyqtSignal(str)
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
        self.max_chunks = 10
        self.setMinimumSize(800,600)

        # Setup PyQt5 window and QLabel for displaying video
        self.setWindowTitle("Video Stream Receiver")
        self.video_label = ClickableLabel(self)
        self.video_label.setAlignment(Qt.AlignCenter)
        # self.video_label.setFixedSize(960, 720)

        # Connect the double-click signal to a handler function
        self.video_label.doubleClicked.connect(self.on_double_click)
        
        # detection
        self.current_detection = [] # list of objects [id,x,y,w,h]
        # tracking
        self.current_tracking = [] # current tracking result [conf,x,y,w,h]
        
        self.current_frame = None

        # Layout setup
        layout = QVBoxLayout()
        
        tools_layout = QHBoxLayout()
        start_track_button = QPushButton('Start track (First object)')
        stop_track_button = QPushButton('Stop track')
        select_target_to_track = QPushButton('Select target to track')
        control_center = QPushButton('Control center')
        
        
        tools_layout.addWidget(start_track_button)
        tools_layout.addWidget(stop_track_button)
        tools_layout.addWidget(select_target_to_track)
        tools_layout.addWidget(control_center)
        
        start_track_button.clicked.connect(self.start_track)
        start_track_button.setVisible(False)
        stop_track_button.clicked.connect(self.stop_track)
        select_target_to_track.clicked.connect(self.select_target_to_track)
        control_center.clicked.connect(self.open_control_center)
        
        self.result_label = QLabel("Received result")
        # self.log_area = QPlainTextEdit(None)
        # self.log_area.setMaximumHeight(100)
        # self.log_area.setPlaceholderText("Log from tracker should be displayed here...")
        
        layout.addLayout(tools_layout)
        layout.addWidget(self.result_label)
        layout.addWidget(self.video_label)
        # layout.addWidget(self.log_area)
        container = QWidget()
        container.setLayout(layout)
        self.setCentralWidget(container)
        
    def open_control_center(self):
        widget = ControlCenter(self, self.cmd_ip, self.cmd_port)
        widget.show()
        
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
        if self.current_frame is None:
            QMessageBox.information(self, "Error", "No stream!")
            print('No stream!')
            return
        
        # select target
        frame_select = self.current_frame.copy()
        while True:
            cv2.putText(frame_select, 'Select target ROI and press ENTER', (20, 30), cv2.FONT_HERSHEY_COMPLEX_SMALL,
                        1.5, (0, 0, 0), 1)

            x, y, w, h = cv2.selectROI("Select frame", frame_select, fromCenter=False)
            bbox_selected = [x, y, w, h]
            break
        cv2.destroyAllWindows()
        
        print('Selected: ', bbox_selected)
        # send tracking command CCT,bbx,bby,bbw,bbh
        assign_target_id = random.randint(0,255)
        cmd = f'CCT,{x},{y},{w},{h}'
        self.cmd_socket.sendto(cmd.encode('utf-8'), (self.cmd_ip, self.cmd_port))
        
        # send tracking frame
        ret, buffer = cv2.imencode('.jpeg', frame_select, [cv2.IMWRITE_JPEG_QUALITY, 90])
        if not ret:
            print("Failed to encode image")
            return
        
        data = buffer.tobytes()
        num_chunks = (len(data) // self.max_package_size) + 1

        if num_chunks > self.max_chunks:
            return  # Frame too large to send, skip

        for i in range(num_chunks):
            chunk_header = bytes([0x46, 0x52, i, num_chunks])
            chunk = data[i * self.max_package_size:(i + 1) * self.max_package_size]
            self.cmd_socket.sendto(chunk_header + chunk, (self.cmd_ip, self.cmd_port))
            
            # print(f'send {len(chunk_header + chunk)} bytes - index: {i}')
            # need to sleep, dont know why last UDP package loss when num_chunks >= 5
            # TODO: Fix it
            if num_chunks >= 5: 
                time.sleep(0.0005) 
            print(f'Send frame part to tracker index: {i} - total {num_chunks}, length: {len(chunk_header) + len(chunk)}')
        

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
                self.result_label.setText(", ".join([str(item) for sublist in self.current_detection for item in sublist]))
                
            elif parts[0] == "TFT": # tracker focus target - bouding box of current tracking target
                confirm = int(parts[1])
                x = int(parts[2])
                y = int(parts[3])
                w = int(parts[4])
                h = int(parts[5])
                self.current_tracking = [confirm, x, y, w, h]
                self.result_label.setText(", ".join(map(str, self.current_tracking)))
            
            elif parts[0] == "TNO":
                notify_str = ",".join(parts[1:])
                print(f'Get notify: {notify_str}')
                self.statusBar().showMessage(notify_str)
                # self.log_area.append(notify_str) # got crash
                # self.log_signal.emit(notify_str)
                
        # return parsed_results
    # def update_log_area(self, message):
    #     self.log_area.append(message)
        # print(message)
        
if __name__ == "__main__":
    app = QApplication(sys.argv)
    
    receiver = RWSController(frame_ip="127.0.0.1", frame_port=12345, data_ip="127.0.0.1", data_port=4000, cmd_ip="127.0.0.1", cmd_port=5000)
    receiver.show()

    # Run the frame receiving in a background thread (not blocking the UI)
    import threading
    receive_frame_thread = threading.Thread(target=receiver.receive_frame, daemon=True)
    receive_frame_thread.start()
    
    receive_data_thread = threading.Thread(target=receiver.receive_data, daemon=True)
    receive_data_thread.start()

    sys.exit(app.exec_())
