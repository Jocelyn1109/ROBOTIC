/* 
 * File:   FrameManager.h
 * Author: Jocelyn Girod
 *
 * Created on 13 décembre 2023, 08:58
 * 
 * Frame manager for the communication between the Raspberry and the Arduino.
 * Frame example:'T: :F: '
 * - first character: device,
 * - second character: separator,
 * - third character: sub-device,
 * - fourth character: separator,
 * - fifth character: function,
 * - sixth character: separator,
 * - seventh character: function value.
 */

#ifndef FRAMEMANAGER_H
#define FRAMEMANAGER_H

#include <stdint.h>

class FrameManager {
public:
    explicit FrameManager();
    FrameManager(const FrameManager& orig);
    virtual ~FrameManager();

    /**
     * Setter for the frame.
     * @param pFrame a pointer to the frame.
     * @param frameSize the size of the frame.
     */
    void setFrame(const char* pFrame, uint8_t frameSize) {
        pFrame_ = pFrame;
        frameSize_ = frameSize;
    }

    /**
     * Get the device.
     * @return the device as character or null character in case of error.
     */
    char getDevice();
    
    /**
     * Get the sub-device.
     * @return the sub-device as character or null character in case of error.
     */
    char getSubDevice();
    
    /**
     * Get the function.
     * @return the function as character or null character in case of error.
     */
    char getFunction();
    
    /**
     * Get the function value.
     * @return the function value as character or null character in case of error.
     */
    char getFunctionValue();
    
private:
    uint8_t frameSize_;
    const char* pFrame_;

};

#endif /* FRAMEMANAGER_H */

