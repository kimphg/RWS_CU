import cv2

def compare_histograms(imgA, imgB):
    # Resize images to the same size if they differ
    if imgA.shape != imgB.shape:
        imgB = cv2.resize(imgB, (imgA.shape[1], imgA.shape[0]))

    # Convert images to HSV color space for better color comparison
    imgA_hsv = cv2.cvtColor(imgA, cv2.COLOR_BGR2HSV)
    imgB_hsv = cv2.cvtColor(imgB, cv2.COLOR_BGR2HSV)

    # Calculate histograms for each image
    histA = cv2.calcHist([imgA_hsv], [0, 1, 2], None, [8, 8, 8], [0, 256, 0, 256, 0, 256])
    histB = cv2.calcHist([imgB_hsv], [0, 1, 2], None, [8, 8, 8], [0, 256, 0, 256, 0, 256])

    # Normalize histograms to make them comparable
    cv2.normalize(histA, histA)
    cv2.normalize(histB, histB)

    # Compare histograms using correlation
    similarity = cv2.compareHist(histA, histB, cv2.HISTCMP_CORREL)
    
    # Convert similarity to percentage (optional)
    similarity_percentage = similarity * 100
    # print(f"Similarity: {similarity_percentage:.2f}%")
    
    return similarity_percentage

def calculate_iou(boxA, boxB):
    """
    Calculate the Intersection over Union (IoU) between two bounding boxes.

    Parameters:
    - boxA: tuple or list of (x, y, w, h) for the first box, where:
        - (x, y) are the top-left coordinates,
        - w is the width, and
        - h is the height.
    - boxB: tuple or list of (x, y, w, h) for the second box.

    Returns:
    - iou: float, the Intersection over Union (IoU) between the two boxes, a value between 0 and 1, 
      where 1 means a perfect overlap.
    """
    
    # Extract the (x, y, width, height) values for both boxes
    xA1, yA1, wA, hA = boxA
    xB1, yB1, wB, hB = boxB
    
    # Convert from (x, y, w, h) to (x1, y1, x2, y2) format:
    # (x2, y2) represents the bottom-right corner of each box
    xA2, yA2 = xA1 + wA, yA1 + hA
    xB2, yB2 = xB1 + wB, yB1 + hB

    # Calculate coordinates for the intersection rectangle
    # Intersection coordinates: top-left (xI1, yI1) and bottom-right (xI2, yI2)
    xI1 = max(xA1, xB1)  # Max of the top-left x-coordinates
    yI1 = max(yA1, yB1)  # Max of the top-left y-coordinates
    xI2 = min(xA2, xB2)  # Min of the bottom-right x-coordinates
    yI2 = min(yA2, yB2)  # Min of the bottom-right y-coordinates

    # Compute the area of intersection
    # If there is no overlap, max(0, xI2 - xI1) or max(0, yI2 - yI1) will be zero
    interArea = max(0, xI2 - xI1) * max(0, yI2 - yI1)

    # Calculate the area of both bounding boxes
    boxAArea = wA * hA
    boxBArea = wB * hB

    # Compute the Intersection over Union (IoU) by dividing the intersection area
    # by the sum of the areas minus the intersection area
    iou = interArea / float(boxAArea + boxBArea - interArea)

    return iou

# Custom boolean function 
def is_float(string):
    try:
    # Return true if float
        float(string)
        return True
    except ValueError:
    # Return False if Error
        return False
    
def is_int(string):
    try:
    # Return true if float
        int(string)
        return True
    except ValueError:
    # Return False if Error
        return False
    
import ipaddress

def is_valid_ip(ip):
    try:
        ipaddress.ip_address(ip)
        return True
    except ValueError:
        return False