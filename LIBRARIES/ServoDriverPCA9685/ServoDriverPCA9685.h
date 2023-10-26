/**
 * Jocelyn GIROD - 26/10/2023
 * PCA9685 servo driver class.
 */

#ifndef _SERVO_DRIVER_PCA9685_H_
#define _SERVO_DRIVER_PCA9685_H_

#include "Adafruit_PWMServoDriver.h"

class ServoDriverPCA9685 {

public:

    /**
     * Constructor
     * @param addr address of the PCA9685 on the I2C bus.
     */
    explicit ServoDriverPCA9685(const uint8_t  	addr = 0x40);

    /**
     * Copy constructor
     * @param other ServoDriverPCA9685 object.
     */
    ServoDriverPCA9685(const ServoDriverPCA9685 &other);

private:
    Adafruit_PWMServoDriver pwmPCA9685;

};

#endif //_SERVO_DRIVER_PCA9685_H_
