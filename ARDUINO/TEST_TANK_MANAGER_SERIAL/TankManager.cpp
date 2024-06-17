/*
 * File:   TankManager.h
 * Author: Jocelyn Girod
 *
 * Created on 03 June 2024
 *
 * Tank manager.
 */

#include "TankManager.h"

/**
 * Default constructor.
 * @param logger (let NULL for no log).
 * @param pinA1A: pin A1A.
 * @param pinA1B: pin A1B.
 * @param pinB1A: pin B1A.
 * @param pinB1B: pin B1B.
*/
TankManager::TankManager(Logger *logger, uint8_t pinA1A, uint8_t pinA1B, uint8_t pinB1A, uint8_t pinB1B) {
    _motorDriverL9110 = MotorDriverL9110(pinA1A, pinA1B, pinB1A, pinB1B, logger);
}

/**
 * Destructor
 */
TankManager::~TankManager() = default;

/**
 * Stop the tank.
 * @return 1 in case of error, otherwise 0.
 */
uint8_t TankManager::stopTank() const {
    return _motorDriverL9110.stopMotor();
}

/**
 * Go backward.
 * @param speed: speed between 0 and 255 (0 <= speed <= 255).
 * @return 1 in case of error, otherwise 0.
 */
uint8_t TankManager::goBackward(uint8_t speed) const {
    return _motorDriverL9110.goBackward(speed);
}

/**
 * Go forward.
 * @param speed: speed between 0 and 255 (0 <= speed <= 255).
 * @return 1 in case of error, otherwise 0.
 */
uint8_t TankManager::goForward(int speed) const {
    return _motorDriverL9110.goForward(speed);
}

/**
  * Accelerate forward.
  * @param fromSpeed: start speed (0 <= fromSpeed <= 255 & fromSpeed < toSpeed).
  * @param toSpeed: end speed (0 <= toSpeed <= 255 & toSpeed > fromSpeed).
  * @param accelerateSpeed: acceleration speed (the smaller accelerateSpeed the faster the acceleration because in fact accelerateSpeed is a "delay").
  * @return 1 in case of error ( if fromSpeed >= toSpeedor or logger error), otherwise 0.
  */
uint8_t TankManager::accelerateForward(uint8_t fromSpeed, uint8_t toSpeed, int accelerateSpeed) {
    return _motorDriverL9110.accelerateForward(fromSpeed, toSpeed, accelerateSpeed);
}

/**
  * Accelerate backward.
  * @param fromSpeed: start speed (0 <= fromSpeed <= 255 & fromSpeed < toSpeed).
  * @param toSpeed: end speed (0 <= toSpeed <= 255 & toSpeed > fromSpeed).
  * @param accelerateSpeed: acceleration speed (the smaller accelerateSpeed the faster the acceleration because in fact accelerateSpeed is a "delay").
  * @return 1 in case of error ( if fromSpeed >= toSpeed or logger error), otherwise 0.
  */
uint8_t TankManager::accelerateBackward(uint8_t fromSpeed, uint8_t toSpeed, int accelerateSpeed) {
    return _motorDriverL9110.accelerateBackward(fromSpeed, toSpeed, accelerateSpeed);
}

/**
  * Decelerate forward.
  * @param fromSpeed: start speed (0 <= fromSpeed <= 255 & fromSpeed > toSpeed).
  * @param toSpeed: end speed (0 <= toSpeed <= 255 & toSpeed < fromSpeed).
  * @param decelerateSpeed: deceleration speed (the smaller decelerateSpeed the faster the deceleration because in fact decelerateSpeed is a "delay").
  * @return 1 in case of error ( if fromSpeed <= toSpeed or logger error), otherwise 0.
  */
uint8_t TankManager::decelerateForward(uint8_t fromSpeed, uint8_t toSpeed, int decelerateSpeed) {
    return _motorDriverL9110.decelerateForward(fromSpeed, toSpeed, decelerateSpeed);
}

/**
 * Decelerate backward.
 * @param fromSpeed: start speed (0 <= fromSpeed <= 255 & fromSpeed > toSpeed).
 * @param toSpeed: end speed (0 <= toSpeed <= 255 & toSpeed < fromSpeed).
 * @param decelerateSpeed: decceleration speed (the smaller decelerateSpeed the faster the deceleration because in fact decelerateSpeed is a "delay").
 * @return 1 in case of error ( if fromSpeed <= toSpeed or logger error), otherwise 0.
 */
uint8_t TankManager::decelerateBackward(uint8_t fromSpeed, uint8_t toSpeed, int decelerateSpeed) {
    return _motorDriverL9110.decelerateBackward(fromSpeed, toSpeed, decelerateSpeed);
}

/**
 * Turn to the right.
 * @param speed: the speed of rotation.
 * @return 1 in case of error, otherwise 0.
 */
uint8_t TankManager::turnRight(int speed) const {
    return _motorDriverL9110.turnRight(speed);
}

/**
 * Turn to the left.
 * @param speed: the speed of rotation.
 * @return 1 in case of error, otherwise 0.
 */
uint8_t TankManager::turnLeft(int speed) const {
    return _motorDriverL9110.turnLeft(speed);
}

/**
 * Stop motor during acceleration or deceleration.
 * @return 1 in case of error, otherwise 0.
 */
uint8_t TankManager::stopAccelerationDeceleration() {
    return _motorDriverL9110.stopMotorAccelerationDeceleration();
}