import socket
import numpy as np
import cv2

class FrameReceiver:
    def __init__(self, ip="127.0.0.1", port=12345):
        self.socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        self.socket.bind((ip, port))
        self.buffer = b''  # Buffer to hold incoming data
        self.expected_frame_counter = None
        self.max_package_size = 65450

    def receive_frame(self):
        while True:
            # Receive data from socket
            data, addr = self.socket.recvfrom(65507)  # Maximum UDP packet size
            if not data:
                continue

            # Extract chunk header (first 2 bytes)
            chunk_index = data[0]  # First byte is the chunk index
            frame_counter = data[1]  # Second byte is the frame counter

            # print(f'Frame counter {frame_counter} - index: {chunk_index}')
            # Extract chunk data
            chunk_data = data[2:]  # Remaining bytes are the chunk data

            # if chunk_index == 5:
                # print(f'Frame counter {frame_counter} - index: {chunk_index}')
            
            # If this is the first chunk of a new frame, reset the buffer
            if self.expected_frame_counter is None or self.expected_frame_counter != frame_counter:
                # print(f'Expected: {self.expected_frame_counter} - Frame: {frame_counter} ==> reset')
                
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

                print(frame.shape)
                if frame is not None:
                    cv2.imshow('Received Frame', cv2.resize(frame, (600,800)))
                
                # Clear the buffer after processing the frame
                self.buffer = b''
                self.expected_frame_counter = None
           
            # Exit condition for demonstration purposes (press 'q' to quit)
            if cv2.waitKey(1) & 0xFF == ord('q'):
                break

        self.socket.close()
        cv2.destroyAllWindows()

# Example usage
if __name__ == "__main__":
    receiver = FrameReceiver()
    receiver.receive_frame()
