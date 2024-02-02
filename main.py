#!/bin/python3

import cv2 as cv
import time
import os

os.system("make")
cam = cv.VideoCapture(0)
while(True):
    result, img = cam.read()
    if (result):
        img = cv.flip(img, 1)
        cv.imwrite("test.png",img)
        os.system("clear")
        os.system("./img_to_ascii test.png")
