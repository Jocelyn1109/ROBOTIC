#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Tue Apr 27 08:48:43 2021

@author: wells
"""

import serial, time
from datetime import datetime

class SerialCommunication():
    
    serialComm = None
    logsFile = None
    
    def __init__(self, serial_port, baudrate, timeout):
        self.serialComm = serial.Serial(port=serial_port, baudrate=baudrate, timeout=timeout)
        time.sleep(0.1) #wait for serial to open
        self.logsFile = open("/home/wells/Dev/APPLI_WEB/RS_CHARLY/serialcom/logs/logs.txt", "w")
        dt_string = datetime.now().strftime("%d/%m/%Y %H:%M:%S")
        self.logsFile.write(dt_string + ": opening serial port"+'\n')
        self.logsFile.close()
        
    
    # Send data to the serial port
    def sendData(self,data):
        answer = ""
        if self.serialComm.isOpen():
            self.logsFile = open("/home/wells/Dev/APPLI_WEB/RS_CHARLY/serialcom/logs/logs.txt","w")
            dt_string = datetime.now().strftime("%d/%m/%Y %H:%M:%S")
            self.logsFile.write(dt_string + ": sending data -> " + data + '\n')
            print('data sent:')
            print(data)
            nbBytes = self.serialComm.write(data.encode())
            dt_string = datetime.now().strftime("%d/%m/%Y %H:%M:%S")
            self.logsFile.write(dt_string + ": write " + str(nbBytes) + " bytes"+'\n')
            time.sleep(0.5) #wait for arduino to answer
            #if  self.serialComm.inWaiting()>0: 
                #answer=self.serialComm.readline()
                #dt_string = datetime.now().strftime("%d/%m/%Y %H:%M:%S")
                #self.logsFile.write(dt_string + ": answer -> " + str(answer) + '\n')
                #self.serialComm.flushInput() #remove data after reading
        
            self.logsFile.close()
        return answer