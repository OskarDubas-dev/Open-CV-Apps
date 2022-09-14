import cv2, time


first_frame = None
video = cv2.VideoCapture(0)


while True:
    key=cv2.waitKey(1)
    check, frame = video.read()
    gray = cv2.cvtColor(frame,cv2.COLOR_BGR2GRAY)
    gray = cv2.GaussianBlur(gray, (21,21),0)
    if first_frame is None:
        first_frame = gray
        continue
    
    delta_frame = cv2.absdiff(gray, first_frame)

    cv2.imshow("video", gray)
    cv2.imshow("delta", delta_frame)
    cv2.imshow("normal", frame)
    if key==ord('q'):
        break


    
    
    
video.release()

cv2.destroyAllWindows()

