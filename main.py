#!/bin/python3

import cv2 as cv
import time
import os
import sys

os.system("make")
noArgv = len(sys.argv) < 2
if (noArgv):
    cam = cv.VideoCapture(0)
else:
    cam = cv.VideoCapture(sys.argv[1])
result = True
while(result):
    result, img = cam.read()
    if (result):
        if (noArgv):
            img = cv.flip(img, 1)
        cv.imwrite("test.png",img)
        os.system("./img_to_ascii test.png 1")
