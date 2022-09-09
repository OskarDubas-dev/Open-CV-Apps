import cv2
import os
import glob

def resize(img):
    resized_img = cv2.resize(img, (100,100))
    return resized_img

img=cv2.imread("space.jpg", 1)


filelist = glob.glob('sample_images/*.jpg')
print(filelist)


for file in filelist:
    img=cv2.imread(file, 1)
    imgResized=resize(img)
    cv2.imshow("new",imgResized)
    cv2.waitKey(0)
    


