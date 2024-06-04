/*
 * File:   TankManager.h
 * Author: Jocelyn Girod
 *
 * Created on 03 June 2024
 *
 * Tank manager.
 */

#ifndef TANKMANAGER_TANKMANAGER_H
#define TANKMANAGER_TANKMANAGER_H

#include <stdint.h>
#include "Logger.h"
#include "MotorDriverL9110.h"

class TankManager {

public:

    /**
     * Default constructor.
     * @param logger (let NULL for no log).
     * @param pinA1A: pin A1A.
     * @param pinA1B: pin A1B.
     * @param pinB1A: pin B1A.
     * @param pinB1B: pin B1B.
     */
    explicit TankManager(Logger *logger, uint8_t pinA1A, uint8_t pinA1B, uint8_t pinB1A, uint8_t pinB1B);

    /**
     * Copy constructor.
     *
     * @param other TankManager object.
     */
    TankManager(const TankManager &other);

    /**
     * Destructor
     */
    virtual ~TankManager();


    /**
     * Stop the tank.
     * @return 1 in case of error, otherwise 0.
     */
    uint8_t stopTank() const;

    /**
     * Go backward.
     * @param speed: speed between 0 and 255 (0 <= speed <= 255).
     */
    uint8_t goBackward(uint8_t speed) const;

    /**
     * Go forward.
     * @param speed: speed between 0 and 255 (0 <= speed <= 255).
     */
    uint8_t goForward(int speed) const;

    /**
     * Accelerate forward.
     * @param fromSpeed: start speed (0 <= fromSpeed <= 255 & fromSpeed < toSpeed).
     * @param toSpeed: end speed (0 <= toSpeed <= 255 & toSpeed > fromSpeed).
     * @param accelerateSpeed: acceleration speed (the smaller accelerateSpeed the faster the acceleration because in fact accelerateSpeed is a "delay").
     * @return 1 in case of error ( if fromSpeed >= toSpeed or logger error), otherwise 0.
     */
    uint8_t accelerateForward(uint8_t fromSpeed, uint8_t toSpeed, int accelerateSpeed);

    /**
     * Accelerate backward.
     * @param fromSpeed: start speed (0 <= fromSpeed <= 255 & fromSpeed < toSpeed).
     * @param toSpeed: end speed (0 <= toSpeed <= 255 & toSpeed > fromSpeed).
     * @param accelerateSpeed: acceleration speed (the smaller accelerateSpeed the faster the acceleration because in fact accelerateSpeed is a "delay").
     * @return 1 in case of error ( if fromSpeed >= toSpeed or logger error), otherwise 0.
     */
    uint8_t accelerateBackward(uint8_t fromSpeed, uint8_t toSpeed, int accelerateSpeed);


    /**
     * Deccelerate forward.
     * @param fromSpeed: start speed (0 <= fromSpeed <= 255 & fromSpeed > toSpeed).
     * @param toSpeed: end speed (0 <= toSpeed <= 255 & toSpeed < fromSpeed).
     * @param decelerateSpeed: deceleration speed (the smaller decelerateSpeed the faster the deceleration because in fact decelerateSpeed is a "delay").
     * @return 1 in case of error ( if fromSpeed <= toSpeed or logger error), otherwise 0.
     */
    uint8_t decelerateForward(uint8_t fromSpeed, uint8_t toSpeed, int decelerateSpeed);


    /**
     * Deccelerate backward.
     * @param fromSpeed: start speed (0 <= fromSpeed <= 255 & fromSpeed > toSpeed).
     * @param toSpeed: end speed (0 <= toSpeed <= 255 & toSpeed < fromSpeed).
     * @param decelerateSpeed: deceleration speed (the smaller decelerateSpeed the faster the deceleration because in fact decelerateSpeed is a "delay").
     * @return 1 in case of error ( if fromSpeed <= toSpeed or logger error), otherwise 0.
     */
    uint8_t decelerateBackward(uint8_t fromSpeed, uint8_t toSpeed, int decelerateSpeed);

    /**
     * Turn to the right.
     * @param speed: the speed of rotation.
     * @return 1 in case of error, otherwise 0.
     */
    uint8_t turnRight(int speed) const;

    /**
     * Turn to the left.
     * @param speed: the speed of rotation.
     * @return 1 in case of error, otherwise 0.
     */
    uint8_t turnLeft(int speed) const;

    /**
     * Stop motor during acceleration or deceleration.
     * @return 1 in case of error, otherwise 0.
     */
    uint8_t stopAccelerationDeceleration();

private:
    MotorDriverL9110 _motorDriverL9110 = MotorDriverL9110(0, 0, 0, 0, nullptr);
};


#endif //TANKMANAGER_TANKMANAGER_H
