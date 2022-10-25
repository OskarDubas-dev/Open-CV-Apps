import cv2, time, pandas

#from cv2 import WINDOW_AUTOSIZE
#from cv2 import WINDOW_NORMAL
#from cv2 import resizeWindow

from datetime import datetime




first_frame = None
video = cv2.VideoCapture(0)
thr = 30

times = []
df = pandas.DataFrame(columns = ["Start", "End"])




status = 0
switch = 0



while True:
    
    key=cv2.waitKey(1)
    check, frame = video.read()
    gray = cv2.cvtColor(frame,cv2.COLOR_BGR2GRAY)
    gray = cv2.GaussianBlur(gray, (21,21),0)
    if first_frame is None:
        first_frame = gray
        continue
    


    #thr = int(cv2.getTrackbarPos("Threshold",trackbarWindow))

    delta_frame = cv2.absdiff(gray, first_frame)
    delta_threshold = cv2.threshold(delta_frame,thr,255,cv2.THRESH_BINARY)[1]


    (cnts,_) = cv2.findContours(delta_threshold.copy(),cv2.RETR_EXTERNAL,cv2.CHAIN_APPROX_SIMPLE)    

    for contour in cnts:
        if cv2.contourArea(contour) < 10000:  
            continue    
        (x,y,w,h) = cv2.boundingRect(contour)
        cv2.rectangle(frame, (x,y), (x+h, y+h), (0,255,0), 3)
        status = 1      
         
        
         
   

  

    if status == 1 and switch == 0:
        switch = 1
        print ("start")
        times.append(datetime.now())
    if status == 0 and switch == 1:
        switch = 0
        print ("end")
        times.append(datetime.now())


    status = 0

    cv2.imshow("video", gray)
    cv2.imshow("delta", delta_frame)
    cv2.imshow("normal", frame)
    cv2.imshow("Thresh", delta_threshold)
    if key==ord('q'):
        if status == 1:
            times.append(datetime.now())
        break

end = None
if len(times) % 2 != 0:
    end = len(times) -1
else:
    end = len(times)
for i in range(0, end,2):
    df = df.append({"Start":times[i], "End":times[i+1]}, ignore_index=True)

df.to_csv("Times.csv")
    



    
video.release()

cv2.destroyAllWindows()

