from vidstab import VidStab
import cv2

# Initialize the stabilizer
stabilizer = VidStab()

# Open the input video
# input_video_path = "/media/hoc/WORK/remote/AnhPhuong/TRACKING_CONTROL_SYSTEM/Projects/RWS_CU/RWS_AI_MODULE/videos/test_tau.avi"  # Replace with your input video path
input_video_path = 0
cap = cv2.VideoCapture(input_video_path)

while True:
    ret, frame = cap.read()
    if not ret:
        break

    # Stabilize the current frame
    stabilized_frame = stabilizer.stabilize_frame(input_frame=frame, smoothing_window=10)

    # Stack the original and stabilized frames horizontally for side-by-side comparison
    # combined_frame = cv2.hconcat([frame[50:frame.shape[0]-50,50:frame.shape[1]-50], stabilized_frame[50:frame.shape[0]-50,50:frame.shape[1]-50]])

    # Display the combined frame
    cv2.imshow("Original vs Stabilized", stabilized_frame)

    # Press 'q' to exit
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

# Release resources
cap.release()
cv2.destroyAllWindows()
