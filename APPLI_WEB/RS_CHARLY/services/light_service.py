#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on 13/06/2024

@author: Jocelyn Girod

Service for the light.

"""

from ..serialcom.serial_communication import SerialCommunication

class LightService:
    
    serial_ = None
    
    # Init light service
    def initService(self,serial):
        self.serial_ = serial
        
    # Switch on light
    def switch_on(self):
        if isinstance(self.serial_, SerialCommunication):
            answer = self.serial_.sendData("L: :O:1")
            print(answer)
        
    # Switch off light
    def switch_off(self):
        if isinstance(self.serial_, SerialCommunication):
            answer = self.serial_.sendData("L: :O:0")
            print(answer)
