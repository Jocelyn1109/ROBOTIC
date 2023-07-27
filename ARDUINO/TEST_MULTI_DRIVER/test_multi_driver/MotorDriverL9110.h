#ifndef _MOTOR_DRIVER_L9910_H_
#define _MOTOR_DRIVER_L9910_H_

#include <stdint.h>
#include "Logger.h"

class MotorDriverL9110 {

public:

    /**
     * Default constructor.
     * @param pinA1A: pin A1A.
     * @param pinA1B: pin A1B.
     * @param pinB1A: pin B1A.
     * @param pinB1B: pin B1B.
     * @param logger (let NULL for no log).
     */
    explicit MotorDriverL9110(uint8_t pinA1A, uint8_t pinA1B, uint8_t pinB1A, uint8_t pinB1B, Logger *logger);

    /**
     * Copy constructor.
     *
     * @param other MotorDriverL9110 object.
     */
    MotorDriverL9110(const MotorDriverL9110 &other);

    /**
     * Destructor
     */
    virtual ~MotorDriverL9110();

    /**
     * Stop the motor.
     * @return 1 in case of error, otherwise 0.
     */
    uint8_t stopMotor() const;

    /**
     * Go backward.
     * @param speed: speed between 0 and 255 (0 <= speed <= 255).
     * @return 1 in case of error, otherwise 0.
     */
    uint8_t goBackward(uint8_t speed) const;

    /**
     * Go forward.
     * @param speed: speed between 0 and 255 (0 <= speed <= 255).
     * @return 1 in case of error, otherwise 0.
     */
    uint8_t goForward(int speed) const;

    /**
     * Accelerate forward.
     * @param fromSpeed: start speed (0 <= fromSpeed <= 255 & fromSpeed < toSpeed).
     * @param toSpeed: end speed (0 <= toSpeed <= 255 & toSpeed > fromSpeed).
     * @param accelerateSpeed: acceleration speed (the smaller accelerateSpeed the faster the acceleration because in fact accelerateSpeed is a "delay").
     * @return 1 in case of error ( if fromSpeed >= toSpeedor or logger error), otherwise 0.
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
     * Decelerate forward.
     * @param fromSpeed: start speed (0 <= fromSpeed <= 255 & fromSpeed > toSpeed).
     * @param toSpeed: end speed (0 <= toSpeed <= 255 & toSpeed < fromSpeed).
     * @param decelerateSpeed: deceleration speed (the smaller decelerateSpeed the faster the deceleration because in fact decelerateSpeed is a "delay").
     * @return 1 in case of error ( if fromSpeed <= toSpeed or logger error), otherwise 0.
     */
    uint8_t decelerateForward(uint8_t fromSpeed, uint8_t toSpeed, int decelerateSpeed);

    /**
     * Decelerate backward.
     * @param fromSpeed: start speed (0 <= fromSpeed <= 255 & fromSpeed > toSpeed).
     * @param toSpeed: end speed (0 <= toSpeed <= 255 & toSpeed < fromSpeed).
     * @param decelerateSpeed: decceleration speed (the smaller decelerateSpeed the faster the deceleration because in fact decelerateSpeed is a "delay").
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
     */
    uint8_t stopMotorAccelerationDeceleration();

private:

    uint8_t pinA1A_;
    uint8_t pinA1B_;
    uint8_t pinB1A_;
    uint8_t pinB1B_;
    bool stopAccelerateDecelerate_;
    Logger *logger_;

    /**
     * Initialize pins.
     */
    void initPin();

};

#endif //_MOTOR_DRIVER_L9910_H_
