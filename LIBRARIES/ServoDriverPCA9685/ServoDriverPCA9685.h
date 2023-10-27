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
    explicit ServoDriverPCA9685(uint8_t addr = 0x40);

    /**
     * Copy constructor
     * @param other ServoDriverPCA9685 object.
     */
    ServoDriverPCA9685(const ServoDriverPCA9685 &other);

    /**
     * Set degrees
     * @param numServo servo number.
     * @param degrees degrees value.
     * @param maxDegree the maximum degree value of the servo (ex: 180°, 360°...).
     * @param servoMin the corresponding minimum pulse width on 4096 (2^12, 12bits) or in microseconds.
     * @param servoMax the corresponding maximum pulse width on 4096 (2^12, 12bits) or in microseconds.
     * @param is4096 is true servoMin and servoMax must be on 4096 (2^12, 12bits) otherwise in microseconds.
     */
    void setDegrees(uint8_t numServo, long degrees, long maxDegree, uint16_t servoMin, uint16_t servoMax, bool is4096);

private:
    Adafruit_PWMServoDriver pwmPCA9685;
    float frequence;

    /***
     * Converte pulse in microseconds to the corresponding pulse value width on 4096 (2^12, 12bits).
     * @param pulse pulse value in microseconds.
     * @return the corresponding pulse value width on 4096 (2^12, 12bits).
     */
    uint16_t convertePulseMicroSecondTo4096(uint16_t pulse);

};

#endif //_SERVO_DRIVER_PCA9685_H_
