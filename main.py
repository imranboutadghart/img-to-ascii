#!/bin/python3

import cv2 as cv
import time
import os


os.system("make")
cam = cv.VideoCapture(0)
while(True):
    result, img = cam.read()
    if (result):
        cv.namedWindow("cam-test")
        cv.moveWindow("cam-test", 1000,1000)
        cv.imshow("cam-test",img)
        cv.imwrite("test.png",img)
        os.system("clear")
        os.system("./img_to_ascii test.png")
        os.system("rm test.png")
        #cv.waitKey(0)
        #cv.destroyWindow("cam-test")
