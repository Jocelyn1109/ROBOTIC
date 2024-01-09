#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on 11/12/2023

@author: wells
source: https://github.com/miguelgrinberg/flask-video-streaming
"""

import io
import time
import picamera
from camera.base_camera import BaseCamera


class CameraPi(BaseCamera):
    @staticmethod
    def frames():
        with picamera.PiCamera() as camera:
            '''camera.resolution = (640, 480)'''
            camera.resolution = (320, 240)
            # let camera warm up
            time.sleep(2)

            stream = io.BytesIO()
            for _ in camera.capture_continuous(stream, format='jpeg', use_video_port=True):
                # return current frame
                stream.seek(0)
                yield stream.read()

                # reset stream for next frame
                stream.seek(0)
                stream.truncate()
