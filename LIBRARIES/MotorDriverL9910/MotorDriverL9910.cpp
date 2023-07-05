/**
 * Jocelyn GIROD - 27/06/2023
 * L9910 motor driver class.
 */

#include <Arduino.h>
#include "MotorDriverL9910.h"

/**
 * Default constructor.
 * @param pinA1A: pin A1A.
 * @param pinA1B: pin A1B.
 * @param pinB1A: pin B1A.
 * @param pinB1B: pin B1B.
 */
MotorDriverL9910::MotorDriverL9910(uint8_t pinA1A, uint8_t pinA1B, uint8_t pinB1A, uint8_t pinB1B) {
    pinA1A_ = pinA1A;
    pinA1B_ = pinA1B;
    pinB1A_ = pinB1A;
    pinB1B_ = pinB1B;
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
    pinMode(pinA1A_, OUTPUT);
    pinMode(pinA1B_, OUTPUT);
    pinMode(pinB1A_, OUTPUT);
    pinMode(pinB1B_, OUTPUT);
}

/**
 * Stop the motor.
 */
void MotorDriverL9910::stopMotor() const {
    digitalWrite(pinA1A_, HIGH);
    digitalWrite(pinA1B_, HIGH);
    digitalWrite(pinB1A_, HIGH);
    digitalWrite(pinB1B_, HIGH);
}

/**
 * Go backward.
 * @param speed: speed between 0 and 255 (0 <= speed <= 255).
 */
void MotorDriverL9910::goBackward(uint8_t speed) const {
    digitalWrite(pinA1A_, 0);
    digitalWrite(pinB1B_, 0);

    digitalWrite(pinA1A_, 0);
    analogWrite(pinA1B_, speed);
    digitalWrite(pinB1A_, 0);
    analogWrite(pinB1B_, speed);
}

/**
 * Go forward.
 * @param speed: speed between 0 and 255 (0 <= speed <= 255).
 */
void MotorDriverL9910::goForward(int speed) const {
    digitalWrite(pinA1A_, 0);
    digitalWrite(pinB1B_, 0);

    analogWrite(pinA1A_, speed);
    digitalWrite(pinA1B_, 0);
    analogWrite(pinB1A_, speed);
    digitalWrite(pinB1B_, 0);
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

    digitalWrite(pinA1B_, 0);
    digitalWrite(pinB1B_, 0);
    for (int i = fromSpeed; i <= toSpeed; i++) {

        // avoid the stop during acceleration
        if (stopAccelerateDecelerate_) {
            this->stopMotor();
            stopAccelerateDecelerate_ = false;
            return 0;
        }

        analogWrite(pinA1A_, i);
        analogWrite(pinB1A_, i);
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

    digitalWrite(pinA1A_, 0);
    digitalWrite(pinB1A_, 0);
    for (int i = fromSpeed; i <= toSpeed; i++) {

        // avoid the stop during acceleration
        if (stopAccelerateDecelerate_) {
            this->stopMotor();
            stopAccelerateDecelerate_ = false;
            return 0;
        }

        analogWrite(pinA1B_, i);
        analogWrite(pinB1B_, i);
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

    digitalWrite(pinA1B_, 0);
    digitalWrite(pinB1B_, 0);
    for (int i = fromSpeed; i >= toSpeed; i--) {

        // avoid the stop during decceleration
        if (stopAccelerateDecelerate_) {
            this->stopMotor();
            stopAccelerateDecelerate_ = false;
            return 0;
        }

        analogWrite(pinA1A_, i);
        analogWrite(pinB1A_, i);
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

    digitalWrite(pinA1A_, 0);
    digitalWrite(pinB1A_, 0);
    for (int i = fromSpeed; i >= toSpeed; i--) {

        // avoid the stop during decceleration
        if (stopAccelerateDecelerate_) {
            this->stopMotor();
            stopAccelerateDecelerate_ = false;
            return 0;
        }

        analogWrite(pinA1B_, i);
        analogWrite(pinB1B_, i);
        delay(deccelerateSpeed);
    }

    return 0;
}

/**
 * Turn to the right.
 * @param speed: the speed of rotation.
 */
void MotorDriverL9910::turnRight(int speed) const {

    digitalWrite(pinA1A_, 0);
    analogWrite(pinA1B_, speed);
    digitalWrite(pinB1B_, 0);
    analogWrite(pinB1A_, speed);
}

/**
 * Turn to the left.
 * @param speed: the speed of rotation.
 */
void MotorDriverL9910::turnLeft(int speed) const {

    digitalWrite(pinA1B_, 0);
    analogWrite(pinA1A_, speed);
    digitalWrite(pinB1A_, 0);
    analogWrite(pinB1B_, speed);
}

/**
 * Stop motor during acceleration or deceleration.
 */
void MotorDriverL9910::stopMotorAccelerationDeceleration() {
    stopAccelerateDecelerate_ = true;
}
