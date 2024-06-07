# -*- coding: utf-8 -*-
"""
Created on 8/12/2023

@author: Jocelyn Girod

Service for the Tank.

"""

import RPi.GPIO as GPIO
from time import sleep
from .service import Service

from ..serialcom.serial_communication import SerialCommunication

class TankService(Service):
    
    # Init tank service
    def initService(self,serial, output_pin):
        self.outputPin = output_pin
        self.serial_ = serial
        GPIO.setmode(GPIO.BCM)
        GPIO.setup(self.outputPin, GPIO.OUT)
    
    # Move forward
    def move_forward(self):
        if isinstance(self.serial_, SerialCommunication):
            answer = self.serial_.sendData("T: :F: ")
            print(answer)
        
    # Move backward
    def move_backward(self):
        if isinstance(self.serial_, SerialCommunication):
            answer = self.serial_.sendData("T: :B: ")
            print(answer)
            
    # Accelerate forward
    def accelerate_forward(self):
        if isinstance(self.serial_, SerialCommunication):
            answer = self.serial_.sendData("T: :A:F")
            print(answer)
            
    # Accelerate backward
    def accelerate_backward(self):
        if isinstance(self.serial_, SerialCommunication):
            answer = self.serial_.sendData("T: :A:B")
            print(answer)
            
    # Decelerate forward
    def decelerate_forward(self):
        if isinstance(self.serial_, SerialCommunication):
            answer = self.serial_.sendData("T: :D:F")
            print(answer)
            
    # Decelerate backward
    def decelerate_backward(self):
        if isinstance(self.serial_, SerialCommunication):
            answer = self.serial_.sendData("T: :D:B")
            print(answer)
            
    # Increase speed
    def increase_speed(self):
        if isinstance(self.serial_, SerialCommunication):
            answer = self.serial_.sendData("T: :S:+")
            print(answer)
            
    # Decrease speed
    def decrease_speed(self):
        if isinstance(self.serial_, SerialCommunication):
            answer = self.serial_.sendData("T: :S:-")
            print(answer)
        
    # Turn right
    def move_right(self):
        if isinstance(self.serial_, SerialCommunication):
            answer = self.serial_.sendData("T: :R: ")
            print(answer)
        
    # Turn left
    def move_left(self):
        if isinstance(self.serial_, SerialCommunication):
            answer = self.serial_.sendData("T: :L: ")
            print(answer)

    # Stop tank
    def stop(self):
        GPIO.output(self.outputPin, GPIO.HIGH)
        sleep(0.500) # sleep 500 ms
        GPIO.output(self.outputPin, GPIO.LOW)
        
        
    # Move servo right
    def move_right_servo(self,num_servo):
        pass
    
    # Move servo left
    def move_left_servo(self,num_servo):
        pass

        
