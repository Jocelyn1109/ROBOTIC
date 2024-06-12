/**
 * Jocelyn GIROD - 27/06/2023
 * L9910 motor driver class.
 */

#include <Arduino.h>
#include <avr/pgmspace.h>
#include "MotorDriverL9110.h"

const char PROGMEM STOP_MOTOR_LOG_MESSAGE[] = "DRVL9110 - STOP MOTOR";
const char PROGMEM STOP_ACCDEC_LOG_MESSAGE[] = "DRVL9110 - STOP ACCELERATION/DECELERATION";
const char PROGMEM GO_FORWARD_LOG_MESSAGE[] = "DRVL9110 - GO FORWARD";
const char PROGMEM GO_BACKWARD_LOG_MESSAGE[] = "DRVL9110 - GO BACKWARD";
const char PROGMEM ACCELERATE_FORWARD_LOG_MESSAGE[] = "DRVL9110 - ACCELERATE FORWARD";
const char PROGMEM ACCELERATE_BACKWARD_LOG_MESSAGE[] = "DRVL9110 - ACCELERATE BACKWARD";
const char PROGMEM DECELERATE_FORWARD_LOG_MESSAGE[] = "DRVL9110 - DECELERATE FORWARD";
const char PROGMEM DECELERATE_BACKWARD_LOG_MESSAGE[] = "DRVL9110 - DECELERATE BACKWARD";
const char PROGMEM TURN_RIGHT_LOG_MESSAGE[] = "DRVL9110 - TURN RIGHT";
const char PROGMEM TURN_LEFT_LOG_MESSAGE[] = "DRVL9110 - TURN LEFT";

/**
 * Default constructor.
 * @param pinA1A: pin A1A.
 * @param pinA1B: pin A1B.
 * @param pinB1A: pin B1A.
 * @param pinB1B: pin B1B.
 */
MotorDriverL9110::MotorDriverL9110(uint8_t pinA1A, uint8_t pinA1B, uint8_t pinB1A, uint8_t pinB1B, Logger *logger) {
    pinA1A_ = pinA1A;
    pinA1B_ = pinA1B;
    pinB1A_ = pinB1A;
    pinB1B_ = pinB1B;
    logger_ = logger;
    initPin();
}

/**
 * Copy constructor.
 *
 * @param other MotorDriverL9110 object.
 */
MotorDriverL9110::MotorDriverL9110(const MotorDriverL9110 &other) {}

/**
 * Destructor
 */
MotorDriverL9110::~MotorDriverL9110() = default;

/**
 * Initialize pins.
 */
void MotorDriverL9110::initPin() {
    pinMode(pinA1A_, OUTPUT);
    pinMode(pinA1B_, OUTPUT);
    pinMode(pinB1A_, OUTPUT);
    pinMode(pinB1B_, OUTPUT);
}

/**
 * Stop the motor.
 * @return 1 in case of error, otherwise 0.
 */
uint8_t MotorDriverL9110::stopMotor() const {

    if (logger_ != nullptr) {
        uint8_t resW = logger_->writeInfoMessage(String((const __FlashStringHelper *) STOP_MOTOR_LOG_MESSAGE));
        if (resW == 1) {
            return 1;
        }
    }
    digitalWrite(pinA1A_, HIGH);
    digitalWrite(pinA1B_, HIGH);
    digitalWrite(pinB1A_, HIGH);
    digitalWrite(pinB1B_, HIGH);

    return 0;
}

/**
 * Go backward.
 * @param speed: speed between 0 and 255 (0 <= speed <= 255).
 */
uint8_t MotorDriverL9110::goBackward(uint8_t speed) const {

    if (logger_ != nullptr) {
        uint8_t resW = logger_->writeInfoMessage(String((const __FlashStringHelper *) GO_BACKWARD_LOG_MESSAGE));
        if (resW == 1) {
            return 1;
        }
    }

    digitalWrite(pinA1A_, 0);
    digitalWrite(pinB1B_, 0);

    digitalWrite(pinA1A_, 0);
    analogWrite(pinA1B_, speed);
    digitalWrite(pinB1A_, 0);
    analogWrite(pinB1B_, speed);

    return 0;
}

/**
 * Go forward.
 * @param speed: speed between 0 and 255 (0 <= speed <= 255).
 */
uint8_t MotorDriverL9110::goForward(int speed) const {

    if (logger_ != nullptr) {
        uint8_t resW = logger_->writeInfoMessage(String((const __FlashStringHelper *) GO_FORWARD_LOG_MESSAGE));
        if (resW == 1) {
            return 1;
        }
    }

    digitalWrite(pinA1A_, 0);
    digitalWrite(pinB1B_, 0);

    analogWrite(pinA1A_, speed);
    digitalWrite(pinA1B_, 0);
    analogWrite(pinB1A_, speed);
    digitalWrite(pinB1B_, 0);

    return 0;
}

/**
 * Accelerate forward.
 * @param fromSpeed: start speed (0 <= fromSpeed <= 255 & fromSpeed < toSpeed).
 * @param toSpeed: end speed (0 <= toSpeed <= 255 & toSpeed > fromSpeed).
 * @param accelerateSpeed: acceleration speed (the smaller accelerateSpeed the faster the acceleration because in fact accelerateSpeed is a "delay").
 * @return 1 in case of error ( if fromSpeed >= toSpeed or logger error), otherwise 0.
 */
uint8_t MotorDriverL9110::accelerateForward(uint8_t fromSpeed, uint8_t toSpeed, int accelerateSpeed) {

    if (fromSpeed >= toSpeed) {
        return 1;
    }

    if (logger_ != nullptr) {
        uint8_t resW = logger_->writeInfoMessage(String((const __FlashStringHelper *) ACCELERATE_FORWARD_LOG_MESSAGE));
        if (resW == 1) {
            return 1;
        }
    }

    digitalWrite(pinA1B_, 0);
    digitalWrite(pinB1B_, 0);
    isAccelerateDecelerate_ = true;
    for (int i = fromSpeed; i <= toSpeed; i++) {

        // avoid the stop during acceleration
        if (stopAccelerateDecelerate_) {
            isAccelerateDecelerate_ = false;
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
 * @return 1 in case of error ( if fromSpeed >= toSpeed or logger error), otherwise 0.
 */
uint8_t MotorDriverL9110::accelerateBackward(uint8_t fromSpeed, uint8_t toSpeed, int accelerateSpeed) {

    if (fromSpeed >= toSpeed) {
        return 1;
    }

    if (logger_ != nullptr) {
        uint8_t resW = logger_->writeInfoMessage(String((const __FlashStringHelper *) ACCELERATE_BACKWARD_LOG_MESSAGE));
        if (resW == 1) {
            return 1;
        }
    }

    digitalWrite(pinA1A_, 0);
    digitalWrite(pinB1A_, 0);
    isAccelerateDecelerate_ = true;
    for (int i = fromSpeed; i <= toSpeed; i++) {

        // avoid the stop during acceleration
        if (stopAccelerateDecelerate_) {
            isAccelerateDecelerate_ = false;
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
 * @param decelerateSpeed: deceleration speed (the smaller decelerateSpeed the faster the deceleration because in fact decelerateSpeed is a "delay").
 * @return 1 in case of error ( if fromSpeed <= toSpeed or logger error), otherwise 0.
 */
uint8_t MotorDriverL9110::decelerateForward(uint8_t fromSpeed, uint8_t toSpeed, int decelerateSpeed) {

    if (fromSpeed <= toSpeed) {
        return 1;
    }

    if (logger_ != nullptr) {
        uint8_t resW = logger_->writeInfoMessage(String((const __FlashStringHelper *) DECELERATE_FORWARD_LOG_MESSAGE));
        if (resW == 1) {
            return 1;
        }
    }

    digitalWrite(pinA1B_, 0);
    digitalWrite(pinB1B_, 0);
    isAccelerateDecelerate_ = true;
    for (int i = fromSpeed; i >= toSpeed; i--) {

        // avoid the stop during decceleration
        if (stopAccelerateDecelerate_) {
            isAccelerateDecelerate_ = false;
            this->stopMotor();
            stopAccelerateDecelerate_ = false;
            return 0;
        }

        analogWrite(pinA1A_, i);
        analogWrite(pinB1A_, i);
        delay(decelerateSpeed);
    }

    return 0;
}

/**
 * Deccelerate backward.
 * @param fromSpeed: start speed (0 <= fromSpeed <= 255 & fromSpeed > toSpeed).
 * @param toSpeed: end speed (0 <= toSpeed <= 255 & toSpeed < fromSpeed).
 * @param decelerateSpeed: deceleration speed (the smaller decelerateSpeed the faster the deceleration because in fact decelerateSpeed is a "delay").
 * @return 1 in case of error ( if fromSpeed <= toSpeed or logger error), otherwise 0.
 */
uint8_t MotorDriverL9110::decelerateBackward(uint8_t fromSpeed, uint8_t toSpeed, int decelerateSpeed) {

    if (fromSpeed <= toSpeed) {
        return 1;
    }

    if (logger_ != nullptr) {
        uint8_t resW = logger_->writeInfoMessage(String((const __FlashStringHelper *) DECELERATE_BACKWARD_LOG_MESSAGE));
        if (resW == 1) {
            return 1;
        }
    }

    digitalWrite(pinA1A_, 0);
    digitalWrite(pinB1A_, 0);
    isAccelerateDecelerate_ = true;
    for (int i = fromSpeed; i >= toSpeed; i--) {

        // avoid the stop during decceleration
        if (stopAccelerateDecelerate_) {
            isAccelerateDecelerate_ = false;
            this->stopMotor();
            stopAccelerateDecelerate_ = false;
            return 0;
        }

        analogWrite(pinA1B_, i);
        analogWrite(pinB1B_, i);
        delay(decelerateSpeed);
    }

    return 0;
}

/**
 * Turn to the right.
 * @param speed: the speed of rotation.
 * @return 1 in case of error, otherwise 0.
 */
uint8_t MotorDriverL9110::turnRight(int speed) const {

    if (logger_ != nullptr) {
        uint8_t resW = logger_->writeInfoMessage(String((const __FlashStringHelper *) TURN_RIGHT_LOG_MESSAGE));
        if (resW == 1) {
            return 1;
        }
    }

    digitalWrite(pinA1A_, 0);
    analogWrite(pinA1B_, speed);
    digitalWrite(pinB1B_, 0);
    analogWrite(pinB1A_, speed);

    return 0;
}

/**
 * Turn to the left.
 * @param speed: the speed of rotation.
 * @return 1 in case of error, otherwise 0.
 */
uint8_t MotorDriverL9110::turnLeft(int speed) const {

    if (logger_ != nullptr) {
        uint8_t resW = logger_->writeInfoMessage(String((const __FlashStringHelper *) TURN_LEFT_LOG_MESSAGE));
        if (resW == 1) {
            return 1;
        }
    }

    digitalWrite(pinA1B_, 0);
    analogWrite(pinA1A_, speed);
    digitalWrite(pinB1A_, 0);
    analogWrite(pinB1B_, speed);

    return 0;
}

/**
 * Stop motor during acceleration or deceleration.
 * @return 1 in case of error, otherwise 0.
 */
uint8_t MotorDriverL9110::stopMotorAccelerationDeceleration() {

    if (logger_ != nullptr) {
        uint8_t resW = logger_->writeInfoMessage(String((const __FlashStringHelper *) STOP_ACCDEC_LOG_MESSAGE));
        if (resW == 1) {
            return 1;
        }
    }

    stopAccelerateDecelerate_ = true;
    return 0;
}
