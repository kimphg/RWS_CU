import cv2

# Open input video
cap = cv2.VideoCapture(0)
stabilizer = cv2.videostab.createOnePassStabilizer()
stabilizer.setInput(cap)

# Stabilize and display video
while True:
    stabilized_frame = stabilizer.nextFrame()
    if stabilized_frame is None:
        break
    cv2.imshow("Stabilized Video", stabilized_frame)
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break
cap.release()
cv2.destroyAllWindows()