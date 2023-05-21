/**
 * Jocelyn GIROD - 21/05/2023
 * DRV8834 motor driver class.
 */

#include <Arduino.h>
#include "MotorDriver8834.h"

MotorDriver8834::MotorDriver8834() {
    stepPin_ = 255;
    dirPin_ = 255;
    sleepPin_ = 255;
    M0_Pin_ = 255;
    M1_Pin_ = 255;
}

MotorDriver8834::MotorDriver8834(const MotorDriver8834 &other) {}

MotorDriver8834::~MotorDriver8834() {}

/**
     * Initialize driver's pins.
     * M0 and M1 are used for microstep resolution.
     * @param stepPin: STEP pin.
     * @param dirPin: DIR pin.
     * @param sleepPin: SLEEP pin (not mandatory).
     * @param M0_Pin: M0 pin (not mandatory).
     * @param M1_Pin: M1 pin (not mandatory).
     */
void MotorDriver8834::initPins(uint8_t stepPin, uint8_t dirPin, uint8_t sleepPin, uint8_t M0_Pin, uint8_t M1_Pin) {

    stepPin_ = sleepPin;
    dirPin_ = dirPin;
    pinMode ( stepPin_, OUTPUT );
    pinMode ( dirPin_, OUTPUT );

    if(sleepPin != 255){
        sleepPin_ = sleepPin;
        pinMode ( sleepPin_, OUTPUT );
    }

    if(M0_Pin != 255){
        M0_Pin_ = M0_Pin;
        pinMode ( M0_Pin_, OUTPUT );
    }

    if(M1_Pin != 255){
        M1_Pin_ = M1_Pin;
        pinMode ( M1_Pin_, OUTPUT );
    }
}