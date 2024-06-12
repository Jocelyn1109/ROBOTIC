# -*- coding: utf-8 -*-
"""
Created on 11/12/2023

@author: Jocelyn Girod

Class for streaming generation.

"""

from .camera_pi import CameraPi
import cv2 # opencv
from time import sleep

class StreamingGeneration():

    vs = None

    def __init__(self, num_cam):
        self.vs = cv2.VideoCapture(num_cam)
        sleep(2.0)

    # Generate streaming for the PI Camera
    def gen_pi_cam():
        #Video streaming generator function.
        while True:
            camera = CameraPi()
            frame = camera.get_frame()
            yield (b'--frame\r\n'b'Content-Type: image/jpeg\r\n\r\n' + frame + b'\r\n')

    
    #  Generate video stream for the usb cam
    def gen_usb_cam():
        #Video streaming generator function.
        while True:
            ret, frame = vs.read()
            frame = cv2.resize(frame, (640, 480))

            # if frame is read correctly ret is True
            if not ret:
                print("Can't receive frame (stream end?). Exiting ...")
                break
        
            # encode the frame in JPEG format
            data = cv2.imencode('.jpg', frame)[1].tobytes()
        
            yield (b'--frame\r\n'b'Content-Type: image/jpeg\r\n\r\n' + data + b'\r\n')