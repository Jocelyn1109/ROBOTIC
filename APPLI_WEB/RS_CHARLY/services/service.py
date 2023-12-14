# -*- coding: utf-8 -*-
"""
Created on Thu Dec 14 09:13:04 2023

@author: Jocelyn Girod
"""

from abc import ABC, abstractmethod

class Service(ABC):
    
    outputPin = 0
    serial_ = None
    
    """
    :param seria: SerialCommunication
    :param output_pin: the output pin in GPIO
    """
    @abstractmethod
    def initService(self,serial, output_pin):
        pass
    
    # Move servo right
    @abstractmethod
    def move_right_servo(self,num_servo):
        pass
    
    # Move servo left
    @abstractmethod
    def move_left_servo(self,num_servo):
        pass
    
    # Stop
    @abstractmethod
    def stop(self):
        pass