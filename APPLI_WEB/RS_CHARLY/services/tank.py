# -*- coding: utf-8 -*-
"""
Created on 8/12/2023

@author: Jocelyn Girod

Service for the Tank.

"""

import RPi.GPIO as GPIO
from time import sleep

from serial_communication.serial_communication import SerialCommunication

class TankService(SerialCommunication):
    
    outputPin = 2
    
    """
    :param serial_port: the serial port (like: /dev/ttyACM0)
    :param baud_rate: the baud rate of the serial port
    """
    def __init__(self, serial_port, baud_rate, output_pin=2):
        self.outputPin = output_pin
        GPIO.setmode(GPIO.BOARD)
        GPIO.setup(self.outputPin, GPIO.OUT, initial=GPIO.LOW) # output 2 setting (LOW by default)
        self.serialComm = SerialCommunication(serial_port, baud_rate, timeout=1)
    
    
    # Move forward
    def move_forward(self):
        answer = self.serialComm.sendData("T: :F: ")
        print(answer)
        
    # Move backward
    def move_backward(self):
        answer = self.serialComm.sendData("T: :B: ")
        print(answer)
        
    # Turn right
    def turn_right(self):
        answer = self.serialComm.sendData("T: :R: ")
        print(answer)
        
    # Turn left
    def turn_left(self):
        answer = self.serialComm.sendData("T: :L: ")
        print(answer)

    # Stop tank
    def stop_tank(self):
        GPIO.output(self.outputPin, GPIO.HIGH)
        sleep(0.500) # sleep 500 ms
        GPIO.output(2, GPIO.LOW)

        
