# -*- coding: utf-8 -*-
"""
Created on Thu Dec 14 09:05:36 2023

@author: Jocelyn Girod

Service for the Arm.

"""

import RPi.GPIO as GPIO
from time import sleep
from service import Service

from serial_communication.serial_communication import SerialCommunication

class ArmService(Service):
    
    # Init arm service
    def initService(self,serial, output_pin):
        self.outputPin = output_pin
        self.serial_ = serial
        GPIO.setmode(GPIO.BOARD)
        GPIO.setup(self.outputPin, GPIO.OUT, initial=GPIO.LOW) # outpu setting (LOW by default)


    # Stop
    def stop(self):
        GPIO.output(self.outputPin, GPIO.HIGH)
        sleep(0.500) # sleep 500 ms
        GPIO.output(self.outputPin, GPIO.LOW)
        
    # Move left servo
    def move_left_servo(self,num_servo):
        if isinstance(self.serial_, SerialCommunication):
            frame = "A:" + num_servo + ":L: "
            answer = self.serial_.sendData(frame)
            print(answer)
            
    # Move right servo
    def move_right_servo(self,num_servo):
        if isinstance(self.serial_, SerialCommunication):
            frame = "A:" + num_servo + ":R: "
            answer = self.serial_.sendData(frame)
            print(answer)
            
    # Increase the servo speed
    def increase_speed(self):
        if isinstance(self.serial_, SerialCommunication):
            answer = self.serial_.sendData("T: :S:+")
            print(answer)
            
    # Decrease the servo speed
    def decrease_speed(self):
        if isinstance(self.serial_, SerialCommunication):
            answer = self.serial_.sendData("T: :S:-")
            print(answer)
    