#ifndef _MOTOR_DRIVER8834_H_
#define _MOTOR_DRIVER8834_H_

#include <stdint.h>

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
     * Default constructor
     */
    MotorDriver8834();

    /**
     * Copy constructor
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
     * @return -1 in case of error, otherwise 0.
     */
    uint8_t goForward(int nbStep, int speed);

    /**
     * Go backward.
     * @param nbStep: steps number.
     * @param speed: delay between steps (in ms).
     * @return -1 in case of error, otherwise 0.
     */
    uint8_t goBackward(int nbStep, int speed);

    /**
     * Define the microstep resolution.
     * @param res: resolution as enum.
     * @return -1 in case of error, otherwise 0.
     */
    uint8_t defineMicrostepResolution(microstep_resolution res);

private:
    uint8_t stepPin_;
    uint8_t dirPin_;
    uint8_t sleepPin_;
    uint8_t M0_Pin_;
    uint8_t M1_Pin_;

};

#endif //_MOTOR_DRIVER8834_H_
