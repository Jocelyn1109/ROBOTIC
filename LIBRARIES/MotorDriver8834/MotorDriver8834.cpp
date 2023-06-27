/**
 * Jocelyn GIROD - 21/05/2023
 * DRV8834 motor driver class.
 */
#include <Arduino.h>
#include <avr/pgmspace.h>
#include "MotorDriver8834.h"

const char PROGMEM GO_FORWARD_LOG_MESSAGE[] = "GO FORWARD\0";
const char PROGMEM GO_BACKWARD_LOG_MESSAGE[] = "GO BACKWARD";
const char PROGMEM ENABLE_DRIVER_LOG_MESSAGE[] = "ENABLE DRIVER";
const char PROGMEM DISABLE_DRIVER_LOG_MESSAGE[] = "DISABLE DRIVER";
const char PROGMEM SET_FORWARD_DIR_LOG_MESSAGE[] = "SET FORWARD DIRECTION";
const char PROGMEM SET_BACKWARD_DIR_LOG_MESSAGE[] = "SET BACKWARD DIRECTION";

/**
 * Default constructor.
 * @param logger (let NULL for no log).
 */
MotorDriver8834::MotorDriver8834(Logger *logger) {
    stepPin_ = 255;
    dirPin_ = 255;
    sleepPin_ = 255;
    M0_Pin_ = 255;
    M1_Pin_ = 255;
    logger_ = logger;
}

/**
 * Copy constructor.
 *
 * @param other MotorDriver8834 object.
 */
MotorDriver8834::MotorDriver8834(const MotorDriver8834 &other) {}

/**
 * Destructor
 */
MotorDriver8834::~MotorDriver8834() = default;

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

    stepPin_ = stepPin;
    dirPin_ = dirPin;
    pinMode(stepPin_, OUTPUT);
    pinMode(dirPin_, OUTPUT);

    if (sleepPin != 255) {
        sleepPin_ = sleepPin;
        pinMode(sleepPin_, OUTPUT);
    }

    if (M0_Pin != 255) {
        M0_Pin_ = M0_Pin;
        pinMode(M0_Pin_, OUTPUT);
    }

    if (M1_Pin != 255) {
        M1_Pin_ = M1_Pin;
        pinMode(M1_Pin_, OUTPUT);
    }
}

/**
 * Go forward.
 * @param nbStep: steps number.
 * @param speed: delay between steps (in ms).
 * @return 1 in case of error, otherwise 0.
 */
uint8_t MotorDriver8834::goForward(int nbStep, int speed) {

    if (stepPin_ == 255 || dirPin_ == 255) {
        return 1;
    }

    if (logger_ != nullptr) {
        uint8_t resW = logger_->writeInfoMessage(String((const __FlashStringHelper *) GO_FORWARD_LOG_MESSAGE));
        if (resW == 1) {
            return 1;
        }
    }

    digitalWrite(dirPin_, HIGH);  // forward
    digitalWrite(stepPin_, LOW);  // init step pin

    for (int i = 0; i < nbStep; i++) {
        digitalWrite(stepPin_, HIGH);
        delay(speed);
        digitalWrite(stepPin_, LOW);
        delay(speed);
    }

    return 0;
}

/**
 * Go backward.
 * @param nbStep: steps number.
 * @param speed: delay between steps (in ms).
 * @return 1 in case of error, otherwise 0.
 */
uint8_t MotorDriver8834::goBackward(int nbStep, int speed) {

    if (stepPin_ == 255 || dirPin_ == 255) {
        return 1;
    }

    if (logger_ != nullptr) {
        uint8_t resW = logger_->writeInfoMessage(String((const __FlashStringHelper *) GO_BACKWARD_LOG_MESSAGE));
        if (resW == 1) {
            return 1;
        }
    }

    digitalWrite(dirPin_, LOW);  // backward
    digitalWrite(stepPin_, LOW); // init step pin

    for (int i = 0; i < nbStep; i++) {
        digitalWrite(stepPin_, HIGH);
        delay(speed);
        digitalWrite(stepPin_, LOW);
        delay(speed);
    }

    return 0;
}

/**
 * Define the microstep resolution.
 * @param res: resolution as enum.
 * @return 1 in case of error, otherwise 0.
 */
uint8_t MotorDriver8834::defineMicrostepResolution(microstep_resolution res) const {

    if (M0_Pin_ == 255 || M1_Pin_ == 255) {
        return 1;
    }

    switch (res) {
        case microstep_resolution::FULL_STEP:
            pinMode(M0_Pin_, OUTPUT);
            digitalWrite(M0_Pin_, LOW);
            digitalWrite(M1_Pin_, LOW);
            break;

        case microstep_resolution::HALF_STEP:
            pinMode(M0_Pin_, OUTPUT);
            digitalWrite(M0_Pin_, HIGH);
            digitalWrite(M1_Pin_, LOW);
            break;

        case microstep_resolution::ONE_FOUR_STEP:
            pinMode(M0_Pin_, INPUT_PULLUP);
            digitalWrite(M0_Pin_, LOW);
            digitalWrite(M1_Pin_, LOW);
            break;

        case microstep_resolution::ONE_HEIGHT_STEP:
            pinMode(M0_Pin_, OUTPUT);
            digitalWrite(M0_Pin_, LOW);
            digitalWrite(M1_Pin_, HIGH);
            break;

        case microstep_resolution::ONE_SIXTEEN_STEP:
            pinMode(M0_Pin_, OUTPUT);
            digitalWrite(M0_Pin_, HIGH);
            digitalWrite(M1_Pin_, HIGH);
            break;

        case microstep_resolution::ONE_THIRTY_TWO_STEP:
            pinMode(M0_Pin_, INPUT_PULLUP);
            digitalWrite(M0_Pin_, LOW);
            digitalWrite(M1_Pin_, HIGH);
            break;

        default:
            return 1;
    }

    return 0;
}

/**
 * Enable the driver (put the PIN SLEEP to HIGH).
 * @return 1 if sleep pin is not initialized, otherwise 0.
 */
uint8_t MotorDriver8834::enableDriver() {

    if (sleepPin_ == 255) {
        return 1;
    }

    if (logger_ != nullptr) {
        uint8_t resW = logger_->writeInfoMessage(String((const __FlashStringHelper *) ENABLE_DRIVER_LOG_MESSAGE));
        if (resW == 1) {
            return 1;
        }
    }

    digitalWrite(sleepPin_, HIGH);

    return 0;

}

/**
 * Enable the driver (put the PIN SLEEP to HIGH).
 * @return 1 if sleep pin is not initialized, otherwise 0.
 */
uint8_t MotorDriver8834::disbableDriver() {

    if (sleepPin_ == 255) {
        return -1;
    }

    if (logger_ != nullptr) {
        uint8_t resW = logger_->writeInfoMessage(String((const __FlashStringHelper *) DISABLE_DRIVER_LOG_MESSAGE));
        if (resW == 1) {
            return 1;
        }
    }

    digitalWrite(sleepPin_, LOW);

    return 0;

}

/**
 * Set the forward direction.
 * @return 1 if dir pin is not initialized, otherwise 0.
 */
uint8_t MotorDriver8834::setForwadDirection() {

    if (dirPin_ == 255) {
        return 1;
    }

    if (logger_ != nullptr) {
        uint8_t resW = logger_->writeInfoMessage(String((const __FlashStringHelper *) SET_FORWARD_DIR_LOG_MESSAGE));
        if (resW == 1) {
            return 1;
        }
    }

    digitalWrite(dirPin_, HIGH);  // forward

    return 0;
}

/**
 * Set the backward direction.
 * @return 1 if dir pin is not initialized, otherwise 0.
 */
uint8_t MotorDriver8834::setBackwardDirection() {

    if (dirPin_ == 255) {
        return 1;
    }

    if (logger_ != nullptr) {
        uint8_t resW = logger_->writeInfoMessage(String((const __FlashStringHelper *) SET_BACKWARD_DIR_LOG_MESSAGE));
        if (resW == 1) {
            return 1;
        }

    }

    digitalWrite(dirPin_, LOW);  // backward

    return 0;
}

/**
 * One step.
 * @param speed: step speed (in ms).
 * @return 1 if step pin is not initialized, otherwise 0.
 */
uint8_t MotorDriver8834::oneStep(int speed) const {

    if (stepPin_ == 255) {
        return 1;
    }

    digitalWrite(stepPin_, HIGH);
    delay(speed);
    digitalWrite(stepPin_, LOW);
    delay(speed);

    return 0;
}