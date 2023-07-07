/**
 * Jocelyn GIROD - 21/05/2023
 * DRV8834 motor driver class.
 */

#ifndef _MOTOR_DRIVER8834_H_
#define _MOTOR_DRIVER8834_H_

#include <stdint.h>
#include "Logger.h"

enum class microstep_resolution : uint8_t {
    FULL_STEP, /* 200 steps per revolution */
    HALF_STEP,
    ONE_FOUR_STEP, /* 1/4 step */
    ONE_HEIGHT_STEP, /* 1/8 step */
    ONE_SIXTEEN_STEP, /* 1/16 step */
    ONE_THIRTY_TWO_STEP /* 1/32 step */
};

class MotorDriver8834 {

public:

    /**
     * Default constructor.
     * @param logger (let NULL for no log).
     */
    explicit MotorDriver8834(Logger *logger);

    /**
     * Copy constructor.
     *
     * @param other MotorDriver8834 object.
     */
    MotorDriver8834(const MotorDriver8834 &other);

    /**
     * Destructor
     */
    ~MotorDriver8834();

    /**
     * Initialize driver's pins.
     * M0 and M1 are used for microstep resolution.
     * @param stepPin: STEP pin.
     * @param dirPin: DIR pin.
     * @param sleepPin: SLEEP pin (not mandatory).
     * @param M0_Pin: M0 pin (not mandatory).
     * @param M1_Pin: M1 pin (not mandatory).
     */
    void initPins(uint8_t stepPin, uint8_t dirPin, uint8_t sleepPin = 255, uint8_t M0_Pin = 255, uint8_t M1_Pin = 255);

    /**
     * Go forward.
     * @param nbStep: steps number.
     * @param speed: delay between steps (in ms).
     * @return 1 in case of error, otherwise 0.
     */
    uint8_t goForward(int nbStep, int speed);

    /**
     * Go backward.
     * @param nbStep: steps number.
     * @param speed: delay between steps (in ms).
     * @return 1 in case of error, otherwise 0.
     */
    uint8_t goBackward(int nbStep, int speed);

    /**
     * Define the microstep resolution.
     * @param res: resolution as enum.
     * @return -1 in case of error, otherwise 0.
     */
    uint8_t defineMicrostepResolution(microstep_resolution res) const;

    /**
     * Enable the driver (put the PIN SLEEP to HIGH).
     * @return 1 if sleep pin is not initialized, otherwise 0.
     */
    uint8_t enableDriver();

    /**
     * Disable the driver (put the PIN SLEEP to LOW).
     * @return 1 if sleep pin is not initialized, otherwise 0.
     */
    uint8_t disbableDriver();

    /**
     * Set the forward direction.
     * @return 1 if dir pin is not initialized, otherwise 0.
     */
    uint8_t setForwadDirection();

    /**
     * Set the backward direction.
     * @return 1 if dir pin is not initialized, otherwise 0.
     */
    uint8_t setBackwardDirection();

    /**
     * One step.
     * @param speed: step speed (in ms).
     * @return 1 if step pin is not initialized, otherwise 0.
     */
    uint8_t oneStep(int speed) const;

private:
    uint8_t stepPin_;
    uint8_t dirPin_;
    uint8_t sleepPin_;
    uint8_t M0_Pin_;
    uint8_t M1_Pin_;

    Logger *logger_;

};

#endif //_MOTOR_DRIVER8834_H_
