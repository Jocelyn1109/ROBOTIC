#ifndef _MOTOR_DRIVER8834_H_
#define _MOTOR_DRIVER8834_H_

#include <stdint.h>

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
    MotorDriver8834 ( const MotorDriver8834& other );

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

private:
    uint8_t stepPin_;
    uint8_t dirPin_;
    uint8_t sleepPin_;
    uint8_t M0_Pin_;
    uint8_t M1_Pin_;

};

#endif //_MOTOR_DRIVER8834_H_
