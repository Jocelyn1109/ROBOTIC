#include <math.h> // NOLINT(*-deprecated-headers)
#include "ServoDriverPCA9685.h"

/**
 * Constructor
 * @param addr address of the PCA9685 on the I2C bus.
 */
ServoDriverPCA9685::ServoDriverPCA9685(const uint8_t addr, float frequence, uint32_t oscillatorFrequency): addr_(addr), frequence_(frequence), oscillatorFrequency_(oscillatorFrequency) {
}

/**
 * Copy constructor
 * @param other ServoDriverPCA9685 object.
 */
ServoDriverPCA9685::ServoDriverPCA9685(const ServoDriverPCA9685 &other) {
}

/**
 * Destructor
 */
ServoDriverPCA9685::~ServoDriverPCA9685() = default;

/**
 * Initialize the driver.
 * Setups the I2C interface and hardware.
 * @return true if successful, otherwise false.
 */
bool ServoDriverPCA9685::initDriver(uint8_t prescale) {

    if (addr_ != 0x40) {
        pwmPCA9685 = Adafruit_PWMServoDriver(addr_);
    } else {
        pwmPCA9685 = Adafruit_PWMServoDriver();
    }

    bool resInit = pwmPCA9685.begin(prescale);
    if (resInit) {
        pwmPCA9685.setPWMFreq(frequence_);
        pwmPCA9685.setOscillatorFrequency(oscillatorFrequency_);
    }
    return resInit;
}

/**
 * Sleep or wakeup the board.
 * @param isSleep true for sleep and false for wakeup.
 */
void ServoDriverPCA9685::sleepWakeUp(bool isSleep) {
    if (isSleep) {
        pwmPCA9685.sleep();
    } else {
        pwmPCA9685.wakeup();
    }
}

/**
 * Set degrees with using PWM.
 * @param numServo servo number.
 * @param degrees degrees value.
 * @param maxDegree the maximum degree value of the servo (ex: 180°, 360°...).
 * @param servoMin the corresponding minimum pulse width on 4096 (2^12, 12bits) or in microseconds.
 * @param servoMax the corresponding maximum pulse width on 4096 (2^12, 12bits) or in microseconds.
 * @param is4096 is true servoMin and servoMax must be on 4096 (2^12, 12bits) otherwise in microseconds.
 */
void ServoDriverPCA9685::setDegreesWithPWM(uint8_t numServo, long degrees, long maxDegree, long servoMin,
                                           long servoMax, bool is4096) {

    if(numServo > 15){
        return;
    }

    if (is4096) {
        long pulseLen = map(degrees, 0, maxDegree, servoMin, servoMax);
        pwmPCA9685.setPWM(numServo, 0, pulseLen);
    } else {
        const uint16_t servoMin_4096 = convertePulseMicroSecondTo4096(servoMin);
        const uint16_t servoMax_4096 = convertePulseMicroSecondTo4096(servoMax);
        long pulseLen = map(degrees, 0, maxDegree, servoMin_4096, servoMax_4096);
        pwmPCA9685.setPWM(numServo, 0, pulseLen);
    }
}

/**
 * Set degrees with using microseconds
 * @param numServo servo number.
 * @param degrees degrees value.
 * @param maxDegree the maximum degree value of the servo (ex: 180°, 360°...).
 * @param servoMin the corresponding minimum pulse width in microseconds.
 * @param servoMax the corresponding maximum pulse width in microseconds.
 */
void ServoDriverPCA9685::setDegreesWithMicroseconds(uint8_t numServo, long degrees, long maxDegree, long servoMin, long servoMax) {

    if(numServo <= 15){
        long pulseLen = map(degrees, 0, maxDegree, servoMin, servoMax);
        pwmPCA9685.writeMicroseconds(numServo,pulseLen);
    }
}

/**
 * Get the current degrees of the servo with using PWM.
 * @param servoNum servo number.
 * @param maxDegree the maximum degree value of the servo (ex: 180°, 360°...).
 * @param servoMin the corresponding minimum pulse width on 4096 (2^12, 12bits).
 * @param servoMax the corresponding maximum pulse width on 4096 (2^12, 12bits).
 * @return the current degrees (position of the servo) otherwise -1;
 */
float ServoDriverPCA9685::getCurrentDegreesWithPWM(uint8_t servoNum, long maxDegree, long servoMin, long servoMax) {

    if (servoNum <= 15) {
        uint16_t currentPWM = pwmPCA9685.getPWM(servoNum, true);
        float currentDegrees = map(currentPWM, servoMin, servoMax, 0.0, maxDegree);
        return (float) currentDegrees;
    } else {
        return -1;
    }
}

/**
 * Get the current degrees of the servo with using microseconds.
 * @param servoNum servo number.
 * @param maxDegree the maximum degree value of the servo (ex: 180°, 360°...).
 * @param servoMin the corresponding minimum pulse width in microseconds.
 * @param servoMax the corresponding maximum pulse width in microseconds.
 * @return the current degrees (position of the servo) otherwise -1;
 */
float ServoDriverPCA9685::getCurrentDegreesWithMicroseconds(uint8_t servoNum, long maxDegree, long servoMin, long servoMax) {

    if (servoNum <= 15) {
        uint16_t currentPWM = pwmPCA9685.getPWM(servoNum, true);
        const uint16_t servoMin_4096 = convertePulseMicroSecondTo4096(servoMin);
        const uint16_t servoMax_4096 = convertePulseMicroSecondTo4096(servoMax);
        float currentDegrees = map(currentPWM, servoMin_4096, servoMax_4096, 0.0, maxDegree);
        return (float) currentDegrees;
    }else{
        return -1;
    }
}

/**
 * Sets the PWM output of one of the PCA9685 pins.
 * @param servoNum one of the servo (PWM output pins), from 0 to 15.
 * @param on at what point in the 4096-part cycle to turn the PWM output ON.
 * @param off at what point in the 4096-part cycle to turn the PWM output OFF.
 * @return 0 if successful, otherwise 1.
 */
uint8_t ServoDriverPCA9685::setPWMOutput(int8_t servoNum, uint16_t on, uint16_t off) {

    if (servoNum <= 15) {
        pwmPCA9685.setPWM(servoNum, on, off);
        return 0;
    } else {
        return 1;
    }
}

/**
 * Sets the PWM output of one of the PCA9685 pins based on the input microseconds, output is not precise.
 * @param servoNum one of the servo (PWM output pins), from 0 to 15.
 * @param Microseconds the number of Microseconds to turn the PWM output ON.
 * @return 0 if successful, otherwise 1.
 */
uint8_t ServoDriverPCA9685::writeMicroseconds(uint8_t servoNum, uint16_t Microseconds) {

    if (servoNum <= 15) {
        pwmPCA9685.writeMicroseconds(servoNum, Microseconds);
        return 0;
    } else {
        return 1;
    }
}

/***
 * Converte pulse in microseconds to the corresponding pulse value width on 4096 (2^12, 12bits).
 * @param pulse pulse value in microseconds.
 * @return the corresponding pulse value width on 4096 (2^12, 12bits).
 */
uint16_t ServoDriverPCA9685::convertePulseMicroSecondTo4096(long pulse) const {

    long pulse4096;
    //period in second
    double period = 1 / frequence_;
    period = floor(period * 1000) / 1000; // 3 digits after comma
    //periode in microseconds
    period = period * pow(10, 6);
    pulse4096 = (pulse / (long) period) * 4096;

    // the precision to the comma is not necessary.
    return (uint16_t) pulse4096;
}
