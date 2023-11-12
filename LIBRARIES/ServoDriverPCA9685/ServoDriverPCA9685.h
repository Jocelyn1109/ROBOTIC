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
     * @param addr address of the PCA9685 on the I2C bus - 0x40 by default.
     * @param frequence PWM frequency for the entire chip - by default 50.0.
     * @param oscillatorFrequency the internally tracked oscillator used for freq calculations - by default 25000000.
     */
    explicit ServoDriverPCA9685(uint8_t addr = 0x40, float frequence = 50.0, uint32_t oscillatorFrequency = 25000000);

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

    /**
     * Sets the PWM output of one of the PCA9685 pins.
     * @param servoNum one of the servo (PWM output pins), from 0 to 15.
     * @param on at what point in the 4096-part cycle to turn the PWM output ON.
     * @param off at what point in the 4096-part cycle to turn the PWM output OFF.
     * @return 0 if successful, otherwise 1.
     */
    uint8_t setPWMOutput(int8_t servoNum, uint16_t on, uint16_t off);

    /**
     * Sets the PWM output of one of the PCA9685 pins based on the input microseconds, output is not precise.
     * @param servoNum one of the servo (PWM output pins), from 0 to 15.
     * @param Microseconds the number of Microseconds to turn the PWM output ON.
     * @return 0 if successful, otherwise 1.
     */
    uint8_t writeMicroseconds(uint8_t servoNum, uint16_t Microseconds);

private:
    Adafruit_PWMServoDriver pwmPCA9685;
    float frequence_;

    /***
     * Converte pulse in microseconds to the corresponding pulse value width on 4096 (2^12, 12bits).
     * @param pulse pulse value in microseconds.
     * @return the corresponding pulse value width on 4096 (2^12, 12bits).
     */
    uint16_t convertePulseMicroSecondTo4096(uint16_t pulse) const;

};

#endif //_SERVO_DRIVER_PCA9685_H_
