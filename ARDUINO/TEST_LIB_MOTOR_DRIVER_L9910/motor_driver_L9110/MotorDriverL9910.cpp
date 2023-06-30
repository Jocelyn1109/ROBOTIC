/**
 * Jocelyn GIROD - 27/06/2023
 * L9910 motor driver class.
 */

#include <Arduino.h>
#include "MotorDriverL9910.h"

/**
 * Default constructor.
 * @param pinAIA: pin AIA.
 * @param pinAIB: pin AIB.
 * @param pinBIA: pin BIA.
 * @param pinBIB: pin BIB.
 */
MotorDriverL9910::MotorDriverL9910(uint8_t pinAIA, uint8_t pinAIB, uint8_t pinBIA, uint8_t pinBIB) {
    pinAIA_ = pinAIA;
    pinAIB_ = pinAIB;
    pinBIA_ = pinBIA;
    pinBIB_ = pinBIB;
    initPin();
}

/**
 * Copy constructor.
 *
 * @param other MotorDriverL9910 object.
 */
MotorDriverL9910::MotorDriverL9910(const MotorDriverL9910 &other) {}

/**
 * Destructor
 */
MotorDriverL9910::~MotorDriverL9910() = default;

/**
 * Initialize pins.
 */
void MotorDriverL9910::initPin() {
    pinMode(pinAIA_, OUTPUT);
    pinMode(pinAIB_, OUTPUT);
    pinMode(pinBIA_, OUTPUT);
    pinMode(pinBIB_, OUTPUT);
}

/**
 * Stop the motor.
 */
void MotorDriverL9910::stopMotor() const {
    digitalWrite(pinAIA_, HIGH);
    digitalWrite(pinAIB_, HIGH);
    digitalWrite(pinBIA_, HIGH);
    digitalWrite(pinBIB_, HIGH);
}

/**
 * Go backward.
 * @param speed: speed between 0 and 255 (0 <= speed <= 255).
 */
void MotorDriverL9910::goBackward(uint8_t speed) const {
    analogWrite(pinAIA_, 0);
    analogWrite(pinBIA_, 0);
    analogWrite(pinAIB_, speed);
    analogWrite(pinBIB_, speed);
}

/**
 * Go forward.
 * @param speed: speed between 0 and 255 (0 <= speed <= 255).
 */
void MotorDriverL9910::goForward(int speed) const {
    analogWrite(pinAIB_, 0);
    analogWrite(pinBIB_, 0);
    analogWrite(pinAIA_, speed);
    analogWrite(pinBIA_, speed);
}

/**
 * Accelerate forward.
 * @param fromSpeed: start speed (0 <= fromSpeed <= 255 & fromSpeed < toSpeed).
 * @param toSpeed: end speed (0 <= toSpeed <= 255 & toSpeed > fromSpeed).
 * @param accelerateSpeed: acceleration speed (the smaller accelerateSpeed the faster the acceleration because in fact accelerateSpeed is a "delay").
 * @return 1 in case of error ( if fromSpeed >= toSpeed), otherwise 0.
 */
uint8_t MotorDriverL9910::accelerateForward(uint8_t fromSpeed, uint8_t toSpeed, int accelerateSpeed) {

    if (fromSpeed >= toSpeed) {
        return 1;
    }

    analogWrite(pinAIB_, 0);
    analogWrite(pinBIB_, 0);
    for (int i = fromSpeed; i <= toSpeed; i++) {

        // avoid the stop during acceleration
        if (stopAccelerateDecelerate_) {
            this->stopMotor();
            stopAccelerateDecelerate_ = false;
            return 0;
        }

        analogWrite(pinAIA_, i);
        analogWrite(pinBIA_, i);
        delay(accelerateSpeed);
    }

    return 0;
}


/**
 * Accelerate backward.
 * @param fromSpeed: start speed (0 <= fromSpeed <= 255 & fromSpeed < toSpeed).
 * @param toSpeed: end speed (0 <= toSpeed <= 255 & toSpeed > fromSpeed).
 * @param accelerateSpeed: acceleration speed (the smaller accelerateSpeed the faster the acceleration because in fact accelerateSpeed is a "delay").
 * @return 1 in case of error ( if fromSpeed >= toSpeed), otherwise 0.
 */
uint8_t MotorDriverL9910::accelerateBackward(uint8_t fromSpeed, uint8_t toSpeed, int accelerateSpeed) {

    if (fromSpeed >= toSpeed) {
        return 1;
    }

    analogWrite(pinAIA_, 0);
    analogWrite(pinBIA_, 0);
    for (int i = fromSpeed; i <= toSpeed; i++) {

        // avoid the stop during acceleration
        if (stopAccelerateDecelerate_) {
            this->stopMotor();
            stopAccelerateDecelerate_ = false;
            return 0;
        }

        analogWrite(pinAIB_, i);
        analogWrite(pinBIB_, i);
        delay(accelerateSpeed);
    }

    return 0;
}

/**
 * Deccelerate forward.
 * @param fromSpeed: start speed (0 <= fromSpeed <= 255 & fromSpeed > toSpeed).
 * @param toSpeed: end speed (0 <= toSpeed <= 255 & toSpeed < fromSpeed).
 * @param deccelerateSpeed: decceleration speed (the smaller deccelerateSpeed the faster the decceleration because in fact deccelerateSpeed is a "delay").
 * @return 1 in case of error ( if fromSpeed <= toSpeed), otherwise 0.
 */
uint8_t MotorDriverL9910::deccelerateForward(uint8_t fromSpeed, uint8_t toSpeed, int deccelerateSpeed) {

    if (fromSpeed <= toSpeed) {
        return 1;
    }

    analogWrite(pinAIB_, 0);
    analogWrite(pinBIB_, 0);
    for (int i = fromSpeed; i >= toSpeed; i--) {

        // avoid the stop during decceleration
        if (stopAccelerateDecelerate_) {
            this->stopMotor();
            stopAccelerateDecelerate_ = false;
            return 0;
        }

        analogWrite(pinAIA_, i);
        analogWrite(pinBIA_, i);
        delay(deccelerateSpeed);
    }

    return 0;
}

/**
 * Deccelerate backward.
 * @param fromSpeed: start speed (0 <= fromSpeed <= 255 & fromSpeed > toSpeed).
 * @param toSpeed: end speed (0 <= toSpeed <= 255 & toSpeed < fromSpeed).
 * @param deccelerateSpeed: decceleration speed (the smaller deccelerateSpeed the faster the decceleration because in fact deccelerateSpeed is a "delay").
 * @return 1 in case of error ( if fromSpeed <= toSpeed), otherwise 0.
 */
uint8_t MotorDriverL9910::deccelerateBackward(uint8_t fromSpeed, uint8_t toSpeed, int deccelerateSpeed) {

    if (fromSpeed <= toSpeed) {
        return 1;
    }

    analogWrite(pinAIA_, 0);
    analogWrite(pinBIA_, 0);
    for (int i = fromSpeed; i >= toSpeed; i--) {

        // avoid the stop during decceleration
        if (stopAccelerateDecelerate_) {
            this->stopMotor();
            stopAccelerateDecelerate_ = false;
            return 0;
        }

        analogWrite(pinAIB_, i);
        analogWrite(pinBIB_, i);
        delay(deccelerateSpeed);
    }

    return 0;
}

/**
 * Turn to the right.
 * @param speed: the speed of rotation.
 */
void MotorDriverL9910::turnRight(int speed) const {

    analogWrite(pinAIA_, 0);
    analogWrite(pinAIB_, speed);
    analogWrite(pinBIB_, 0);
    analogWrite(pinBIA_, speed);
}

/**
 * Turn to the left.
 * @param speed: the speed of rotation.
 */
void MotorDriverL9910::turnLeft(int speed) const {

    analogWrite(pinAIB_, 0);
    analogWrite(pinAIA_, speed);
    analogWrite(pinBIA_, 0);
    analogWrite(pinBIB_, speed);
}

/**
 * Stop motor during acceleration or deceleration.
 */
void MotorDriverL9910::stopMotorAccelerationDeceleration() {
    stopAccelerateDecelerate_ = true;
}
