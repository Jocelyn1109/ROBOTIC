/* 
 * File:   FrameManager.cpp
 * Author: Jocelyn Girod
 * 
 * Created on 13 décembre 2023, 08:58
 */

#include "FrameManager.h"

FrameManager::FrameManager() {
}

FrameManager::FrameManager(const FrameManager& orig) {
}

FrameManager::~FrameManager() {
}

/**
 * Get the device.
 * @return the device as character or null character in case of error.
 */
char FrameManager::getDevice() {

    char device = '\0';
    if (pFrame_ != nullptr && frameSize_ > 0) {
        device = *pFrame_;
    }

    return device;
}

/**
 * Get the sub-device.
 * @return the sub-device as character or null character in case of error.
 */
char FrameManager::getSubDevice() {

    char sub_device = '\0';
    if (pFrame_ != nullptr && frameSize_ >= 3) {
        sub_device = pFrame_[2];
    }

    return sub_device;
}

/**
 * Get the function.
 * @return the function as character or null character in case of error.
 */
char FrameManager::getFunction() {

    char function = '\0';
    if (pFrame_ != nullptr && frameSize_ >= 5) {
        function = pFrame_[4];
    }

    return function;
}

/**
 * Get the function value.
 * @return the function value as character or null character in case of error.
 */
char FrameManager::getFunctionValue() {

    char functionValue = '\0';
    if (pFrame_ != nullptr && frameSize_ >= 7) {
        functionValue = pFrame_[6];
    }

    return functionValue;
}
