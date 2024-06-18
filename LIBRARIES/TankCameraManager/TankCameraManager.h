/**
 * Jocelyn GIROD - 17/06/2024
 * Tank camera manager.
 */

#ifndef TANKCAMERAMANAGER_TANKCAMERAMANAGER_H
#define TANKCAMERAMANAGER_TANKCAMERAMANAGER_H

#include <ServoDriverPCA9685.h>

class TankCameraManager {

public:

    /**
     * Default constructor
     * @param servoDriverPca9685 the PCA9685 servo driver.
     */
    explicit TankCameraManager(const ServoDriverPCA9685 &servoDriverPca9685);

    /**
     * Copy constructor.
     * @param other TankCameraManager object.
     */
    TankCameraManager(const TankCameraManager &other);

    /**
     * Destructor
     */
    virtual ~TankCameraManager();

private:

    ServoDriverPCA9685 servoDriverPca9685_;

};


#endif //TANKCAMERAMANAGER_TANKCAMERAMANAGER_H
