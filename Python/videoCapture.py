import cv2, time

video = cv2.VideoCapture(0)


while True:
    key=cv2.waitKey(1)
    check, frame = video.read()
    cv2.imshow("video", frame)
    if key==ord('q'):
        break


    
    
    
video.release()

cv2.destroyAllWindows()

