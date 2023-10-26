#include "ServoDriverPCA9685.h"

/**
 * Constructor
 * @param addr address of the PCA9685 on the I2C bus.
 */
ServoDriverPCA9685::ServoDriverPCA9685(const uint8_t addr) {
    pwmPCA9685 = Adafruit_PWMServoDriver(addr);
}

/**
 * Copy constructor
 * @param other ServoDriverPCA9685 object.
 */
ServoDriverPCA9685::ServoDriverPCA9685(const ServoDriverPCA9685 &other) {

}
