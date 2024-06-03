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
 * Stop the tank.
 * @return 1 in case of error, otherwise 0.
 */
uint8_t TankManager::stopTank() const {
    _motorDriverL9110.stopMotor();
}