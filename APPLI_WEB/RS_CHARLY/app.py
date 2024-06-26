#!/usr/bin/env python3
# -*- coding: utf-8 -*-

# Created on 11/12/2023
# 
# @author: wells
# 
# Portail RS CHARLY
# 
# Voir: https://pyimagesearch.com/2019/09/02/opencv-stream-video-to-web-browser-html-page/
# pour le streaming dans une page html avec une caméra usb
    

import serial

from flask import Flask, render_template
#from flask import Flask, render_template, Response
from .services.tank_service import TankService
from .services.light_service import LightService
# from .services.arm_service import ArmService
# from .camera.streaming_generation import StreamingGeneration
from .serialcom.serial_communication import SerialCommunication

app = Flask(__name__)
serialComm = None
tankService = TankService()
lightService = LightService()
# armService = ArmService()
# streamingGeneration = StreamingGeneration(0)
bauderate_19200 = int(serial.SerialBase().BAUDRATES[13])

#app.run(host='127.0.0.1', port=5000, debug=True)

@app.route('/scripts_js')
def scripts_js():
    return render_template('app.js')

@app.route('/jquery_js')
def jquery_js():
    return render_template('jquery-3.7.1.js')

@app.route('/')
def index():
    try:
        #serialComm = SerialCommunication("/dev/ttyACM0", 19200, timeout=1)
        serialComm = SerialCommunication("/dev/ttyACM0", bauderate_19200, timeout=1, write_timeout=1)
        tankService.initService(serialComm, 2)
        lightService.initService(serialComm)
        print('Init OK !')
    except serial.SerialException:
        print('/dev/ttyACM not found')
    except serial.ValueError:
            print('/dev/ttyACM parameter value error')

    #return render_template('index.html')
    return render_template('index_new.html')

# Move the tank
# Return empty response
@app.route('/move_tank/<string:function>')
def move_tank(function):
    if function == 'move forward':
        tankService.move_forward()
        return('', 204)
    elif function == 'move backward':
        tankService.move_backward()
        return('', 204)
    elif function == 'turn right':
        tankService.move_right()
        return('', 204)
    elif function == 'accelerate forward':
        tankService.accelerate_forward()
        return('', 204)
    elif function == 'accelerate backward':
        tankService.accelerate_backward()
        return('', 204)
    elif function == 'decelerate forward':
        tankService.decelerate_forward()
        return('', 204)
    elif function == 'decelerate backward':
        tankService.decelerate_backward()
        return('', 204)
    elif function == 'increase speed':
        tankService.increase_speed()
        return('', 204)
    elif function == 'decrease speed':
        tankService.decrease_speed()
        return('', 204)
    elif function == 'turn left':
        tankService.move_left()
        return('', 204)
    else:
        print("Unknown function") 
        return('', 403)

# Switch on/off light
# Return empty response
@app.route('/on_off_light/<string:function>')
def on_off_light(function):
    if function == 'switch on':
        lightService.switch_on()
        return('', 204)
    elif function == 'switch off':
        lightService.switch_off()
        return('', 204)
    else:
        print("Unknown function") 
        return('', 403)


#Move arm servo right
@app.route('/arm_servo_right/<string:num_servo>')
def arm_servo_right(num_servo):
    print("arm servo right")
    #armService.move_right_servo(num_servo)
    return('', 204)

#Move arm servo left
@app.route('/arm_servo_left/<string:num_servo>')
def arm_servo_left(num_servo):
    print("arm servo left")
    #armService.move_left_servo(num_servo)
    return('', 204)
            
# Stop the tank
# Return empty response
@app.route('/stop_tank')
def stop_tank():
    print("Stop tank !")
    tankService.stop()
    return ('', 204)

# Stop the arm
# Return empty response
@app.route('/stop_arm')
def stop_arm():
    print("Stop arm !")
    #armService.stop()
    return ('', 204)

# Get streaming for the PI Camera
@app.route('/video_feed_pi_cam')
def video_feed_pi_cam():
    #Video streaming route. Put this in the src attribute of an img tag.
    #return Response(streamingGeneration.gen_pi_cam(), mimetype='multipart/x-mixed-replace; boundary=frame')
    return ('', 204)

# Get video streaming for USB camera
@app.route('/video_feed_usb_cam')
def video_feed_usb_cam():
    #return Response(streamingGeneration.gen_usb_cam(), mimetype='multipart/x-mixed-replace; boundary=frame')
    return ('', 204)


