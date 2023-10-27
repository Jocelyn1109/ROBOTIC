#include <math.h> // NOLINT(*-deprecated-headers)
#include "ServoDriverPCA9685.h"

/**
 * Constructor
 * @param addr address of the PCA9685 on the I2C bus.
 */
ServoDriverPCA9685::ServoDriverPCA9685(const uint8_t addr) {
    pwmPCA9685 = Adafruit_PWMServoDriver(addr);
    frequence = 50;
    pwmPCA9685.setPWMFreq(frequence);
}

/**
 * Copy constructor
 * @param other ServoDriverPCA9685 object.
 */
ServoDriverPCA9685::ServoDriverPCA9685(const ServoDriverPCA9685 &other) {
}

/**
 * Set degrees
 * @param numServo servo number.
 * @param degrees degrees value.
 * @param maxDegree the maximum degree value of the servo (ex: 180°, 360°...).
 * @param servoMin the corresponding minimum pulse width on 4096 (2^12, 12bits) or in microseconds.
 * @param servoMax the corresponding maximum pulse width on 4096 (2^12, 12bits) or in microseconds.
 * @param is4096 is true servoMin and servoMax must be on 4096 (2^12, 12bits) otherwise in microseconds.
 */
void ServoDriverPCA9685::setDegrees(const uint8_t numServo, long degrees, long maxDegree, uint16_t servoMin, uint16_t servoMax, bool is4096) {

    if(is4096){
        const uint16_t servoMin_4096 = convertePulseMicroSecondTo4096(servoMin);
        const uint16_t servoMax_4096 = convertePulseMicroSecondTo4096(servoMax);
        long pulseLen = map(degrees, 0, maxDegree, servoMin_4096, servoMax_4096);
        pwmPCA9685.setPWM(numServo, 0, pulseLen);
    }else{
        long pulseLen = map(degrees, 0, maxDegree, servoMin, servoMax);
        pwmPCA9685.writeMicroseconds(numServo,pulseLen);
    }

}

/***
 * Converte pulse in microseconds to the corresponding pulse value width on 4096 (2^12, 12bits).
 * @param pulse pulse value in microseconds.
 * @return the corresponding pulse value width on 4096 (2^12, 12bits).
 */
uint16_t ServoDriverPCA9685::convertePulseMicroSecondTo4096(uint16_t pulse) {

    double pulse4096 = 0;
    //period in second
    double periode = 1/frequence;
    //periode in microseconds
    periode = periode * pow(10,6);
    pulse4096 = (pulse/periode) * 4096;

    // the precision to the comma is not necessary.
    return (uint16_t)pulse4096;

}
