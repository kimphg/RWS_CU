import cv2

def draw_tracking_result(frame, box, confirmed, tracker_name):
    
    if box is None:
        return frame
    
    # Unpack the box coordinates
    x, y, w, h = box
    
    # Calculate the center point of the bounding box
    center_x = x + w // 2
    center_y = y + h // 2
    
    # Draw the corners of the rectangle
    if w > 50:
        corner_length = 15  # Length of the corner lines
    else: 
        corner_length = 10
        
    
    cv2.line(frame, (x, y), (x + corner_length, y), (0, 255, 0), 2)  # Top side
    cv2.line(frame, (x, y), (x, y + corner_length), (0, 255, 0), 2)  # Left side
    cv2.line(frame, (x + w, y), (x + w - corner_length, y), (0, 255, 0), 2)  # Top right
    cv2.line(frame, (x + w, y), (x + w, y + corner_length), (0, 255, 0), 2)  # Right side
    cv2.line(frame, (x, y + h), (x + corner_length, y + h), (0, 255, 0), 2)  # Bottom left
    cv2.line(frame, (x, y + h), (x, y + h - corner_length), (0, 255, 0), 2)  # Bottom side
    cv2.line(frame, (x + w, y + h), (x + w - corner_length, y + h), (0, 255, 0), 2)  # Bottom right
    cv2.line(frame, (x + w, y + h), (x + w, y + h - corner_length), (0, 255, 0), 2)  # Bottom right
    
    # Draw a cross in the center
    cv2.line(frame, (center_x - 10, center_y), (center_x + 10, center_y), (0, 0, 255), 2)  # Horizontal line
    cv2.line(frame, (center_x, center_y - 10), (center_x, center_y + 10), (0, 0, 255), 2)  # Vertical line
    
    cv2.putText(frame, f'TRACKING - {tracker_name} {"- OCCLUTIONS" if not confirmed else ""}', (20, 50), cv2.FONT_HERSHEY_COMPLEX_SMALL, 1.5, (0, 255, 0), 2)
    return frame

def draw_yolo_deepsort_results(frame, tracks):
    """
    Draws bounding boxes and labels from DeepSort tracking results on the provided frame.

    Parameters:
        frame (numpy.ndarray): The frame on which to draw the results.
        tracks (list): List of tracking results from DeepSort.

    Returns:
        numpy.ndarray: The frame with bounding boxes and labels drawn.
    """
    if tracks is None:
        return frame
    
    # Loop through each track in the current frame
    for track in tracks:
        if not track.is_confirmed():  # Skip unconfirmed tracks
            continue
        
        # Extract track details
        track_id = track.track_id  # Unique ID for the object
        x1, y1, w, h = track.to_ltwh()  # Bounding box (left, top, width, height)
        confidence = track.get_det_conf() if hasattr(track, 'get_det_conf') else None
        if confidence is None:
            confidence = 0.0
        class_id = track.get_det_class() if hasattr(track, 'get_det_class') else None

        # Prepare label
        label = f"ID: {track_id}, Conf: {confidence:.2f}, Class: {class_id}"

        # Draw the bounding box and label on the frame
        cv2.rectangle(frame, (int(x1), int(y1)), (int(x1 + w), int(y1 + h)), (0, 255, 0), 2)
        cv2.putText(frame, label, (int(x1), int(y1) - 10), cv2.FONT_HERSHEY_SIMPLEX, 0.6, (0, 255, 0), 2)

    # Optionally add a title or indicator for exploration mode
    cv2.putText(frame, 'EXPLORATION', (20, 50), cv2.FONT_HERSHEY_COMPLEX_SMALL, 1.5, (0, 255, 0), 2)
    
    return frame

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
            cv2.putText(frame, label, (x1, y1 - 10), cv2.FONT_HERSHEY_SIMPLEX, 2, (0, 255, 0), 2)

    cv2.putText(frame, 'EXPLORATION', (20, 50), cv2.FONT_HERSHEY_COMPLEX_SMALL, 1.5,
                       (0,255,0), 2)
    return frame

if __name__ == "__main__":
    img = cv2.imread('/media/hoc/WORK/remote/AnhPhuong/TRACKING_CONTROL_SYSTEM/Projects/RWS_CU/TaiLieu/app_logo.png')
    img = draw_tracking_result(img, [100,100, 120, 65])
    cv2.imshow('img', img)
    cv2.waitKey(0)