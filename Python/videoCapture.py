import cv2, time

from cv2 import WINDOW_AUTOSIZE
from cv2 import WINDOW_NORMAL
from cv2 import resizeWindow


first_frame = None
video = cv2.VideoCapture(0)
thr = 30

trackbarWindow = "threshWindow"
cv2.namedWindow(trackbarWindow, WINDOW_AUTOSIZE)

def on_trackbar(val):
    pass

#trackbars = cv2.namedWindow("Trackbars", (640,200))
#trackbars = cv2.createTrackbar("threshold", thr, 0)
#resizeWindow(trackbarWindow, 640,480)
cv2.createTrackbar("Threshold", trackbarWindow, 30, 100, on_trackbar)

while True:
    key=cv2.waitKey(1)
    check, frame = video.read()
    gray = cv2.cvtColor(frame,cv2.COLOR_BGR2GRAY)
    gray = cv2.GaussianBlur(gray, (21,21),0)
    if first_frame is None:
        first_frame = gray
        continue
    
    thr = int(cv2.getTrackbarPos("Threshold",trackbarWindow))

    delta_frame = cv2.absdiff(gray, first_frame)
    delta_threshold = cv2.threshold(delta_frame,thr,255,cv2.THRESH_BINARY)[1]

    cv2.imshow("video", gray)
    cv2.imshow("delta", delta_frame)
    cv2.imshow("normal", frame)
    cv2.imshow("Thresh", delta_threshold)
    if key==ord('q'):
        break


    
    
    
video.release()

cv2.destroyAllWindows()

