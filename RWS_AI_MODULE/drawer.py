import cv2

def draw_yolo_result(frame, results):
    """
    Draws bounding boxes and labels from YOLO detection/tracking results on the provided frame.

    Parameters:
        frame (numpy.ndarray): The frame on which to draw the results.
        results (list): List of detection/tracking results from the YOLO model.

    Returns:
        numpy.ndarray: The frame with bounding boxes and labels drawn.
    """
    if results is None:
        return frame
    
    # Loop through each result in the current frame
    for result in results:
        # Get the bounding boxes, confidences, class IDs, and tracking IDs from each result
        boxes = result.boxes.xyxy if result.boxes is not None else []
        confidences = result.boxes.conf if result.boxes is not None else []
        class_ids = result.boxes.cls if result.boxes is not None else []
        track_ids = result.boxes.id if result.boxes is not None else []

        # If any of the lists are empty, skip to the next result
        if boxes is None or confidences is None or class_ids is None or track_ids is None:
            continue

        # Loop through the detected objects
        for box, confidence, class_id, track_id in zip(boxes, confidences, class_ids, track_ids):
            x1, y1, x2, y2 = map(int, box)
            label = f"ID: {track_id}, Conf: {confidence:.2f}, Class: {class_id}"

            # Draw the bounding box and label on the frame
            cv2.rectangle(frame, (x1, y1), (x2, y2), (0, 255, 0), 2)
            cv2.putText(frame, label, (x1, y1 - 10), cv2.FONT_HERSHEY_SIMPLEX, 0.5, (0, 255, 0), 2)

    return frame