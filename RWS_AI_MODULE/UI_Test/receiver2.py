import socket
import cv2
import numpy as np

class VideoReceiver:
    def __init__(self, ip="127.0.0.1", port=12345):
        self.socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        self.socket.bind((ip, port))
        self.buffer = b''
        self.frameID = None

    def receive_video(self):
        while True:
            data, addr = self.socket.recvfrom(65507)  # Receive the UDP datagram
            if not data:
                continue
            
            newFrameID = data[1]  # Extract frameID (2nd byte of the datagram)
            data = data[2:]  # Remove the first 2 bytes (frame index and ID)
            
            if newFrameID != self.frameID:  # If it's a new frame
                if len(self.buffer) > 0:  # Decode the previous frame from the buffer
                    frame = cv2.imdecode(np.frombuffer(self.buffer, np.uint8), cv2.IMREAD_COLOR)

                    if frame is not None and not frame.empty():  # If the frame is valid
                        self.handle_frame(frame)  # Process and display the frame

                # Clear buffer for the new frame
                self.frameID = newFrameID
                self.buffer = data  # Start a new buffer with the current chunk

            else:
                self.buffer += data  # Append the current chunk to the buffer

            # Exit on 'q' key press
            if cv2.waitKey(1) & 0xFF == ord('q'):
                break

        self.socket.close()
        cv2.destroyAllWindows()

    def handle_frame(self, frame):
        # Display the frame
        cv2.imshow('Received Video', frame)

# Example usage
if __name__ == "__main__":
    receiver = VideoReceiver()
    receiver.receive_video()
