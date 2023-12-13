/* 
 * File:   main.cpp
 * Author: JocelynGirod
 *
 * Created on 13 décembre 2023, 08:44
 */

#include <cstdlib>
#include <iostream>
#include <assert.h>
#include <string.h>
#include "class/FrameManager.h"

using namespace std;

/*
 * 
 */
int main() {

    FrameManager frameManager;
    char frame[7] = {'T', ':', ' ', ':', 'F', ':', ' '};
    uint8_t frameSize = sizeof(frame)/sizeof(char);
    
    frameManager.setFrame(&frame[0], frameSize);
    char device = frameManager.getDevice();
    cout << "Device: " << device << endl;
    
    frame[2] = '2';
    char sub_device = frameManager.getSubDevice();
    cout << "Sub-device: " << sub_device << endl;
    
    char function = frameManager.getFunction();
    cout << "Function: " << function << endl;
    
    frame[6] = '+';
    char functionValue = frameManager.getFunctionValue();
    cout << "Function value: " << functionValue << endl;
    
    //Test with null pointer
    frameManager.setFrame(nullptr, frameSize);
    char device_1 = frameManager.getDevice();
    assert(device_1 == '\0');
    
    //Test with index that exceeds frame size
    frameManager.setFrame(&frame[0], 4);
    char functionValue_1 = frameManager.getFunctionValue();
    assert(functionValue_1 == '\0');
    
    //Test with string
    string frameStr = "A:1:R:+";
    frameManager.setFrame(frameStr.c_str(),frameStr.size());
    cout << "Frame string: " << frameStr << endl;
    device = frameManager.getDevice();
    cout << "Device: " << device << endl;
    sub_device = frameManager.getSubDevice();
    cout << "Sub-device: " << sub_device << endl;
    function = frameManager.getFunction();
    cout << "Function: " << function << endl;
    functionValue = frameManager.getFunctionValue();
    cout << "Function value: " << functionValue << endl;
    
    return 0;
}

