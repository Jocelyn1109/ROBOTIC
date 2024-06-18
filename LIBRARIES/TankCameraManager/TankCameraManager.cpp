/**
 * Jocelyn GIROD - 17/06/2024
 * Tank camera manager.
 */

#include "TankCameraManager.h"

/**
 * Default constructor
 * @param servoDriverPca9685 the PCA9685 servo driver.
 */
TankCameraManager::TankCameraManager(const ServoDriverPCA9685 &servoDriverPca9685): servoDriverPca9685_(servoDriverPca9685) {
}

/**
 * Copy constructor.
 * @param other TankCameraManager object.
 */
TankCameraManager::TankCameraManager(const TankCameraManager &other) {

}

/**
 * Destructor
 */
TankCameraManager::~TankCameraManager() {
}
