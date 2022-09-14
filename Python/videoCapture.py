import cv2, time


first_frame = None
video = cv2.VideoCapture(0)


while True:
    key=cv2.waitKey(1)
    check, frame = video.read()
    gray = cv2.cvtColor(frame,cv2.COLOR_BGR2GRAY)

    if first_frame == None:
        first_frame = gray
    
    cv2.imshow("video", frame)
    if key==ord('q'):
        break


    
    
    
video.release()

cv2.destroyAllWindows()

