#ifndef _MOTOR_DRIVER_L9910_H_
#define _MOTOR_DRIVER_L9910_H_

#include <stdint.h>

class MotorDriverL9910 {

public:

    /**
     * Default constructor.
     * @param pinA1A: pin A1A.
     * @param pinA1B: pin A1B.
     * @param pinB1A: pin B1A.
     * @param pinB1B: pin B1B.
     */
    explicit MotorDriverL9910(uint8_t pinA1A, uint8_t pinA1B, uint8_t pinB1A, uint8_t pinB1B);

    /**
     * Copy constructor.
     *
     * @param other MotorDriverL9910 object.
     */
    MotorDriverL9910(const MotorDriverL9910 &other);

    /**
     * Destructor
     */
    ~MotorDriverL9910();

    /**
     * Stop the motor.
     */
    void stopMotor() const;

    /**
     * Go backward.
     * @param speed: speed between 0 and 255 (0 <= speed <= 255).
     */
    void goBackward(uint8_t speed) const;

    /**
     * Go forward.
     * @param speed: speed between 0 and 255 (0 <= speed <= 255).
     */
    void goForward(int speed) const;

    /**
     * Accelerate forward.
     * @param fromSpeed: start speed (0 <= fromSpeed <= 255 & fromSpeed < toSpeed).
     * @param toSpeed: end speed (0 <= toSpeed <= 255 & toSpeed > fromSpeed).
     * @param accelerateSpeed: acceleration speed (the smaller accelerateSpeed the faster the acceleration because in fact accelerateSpeed is a "delay").
     * @return 1 in case of error ( if fromSpeed >= toSpeed), otherwise 0.
     */
    uint8_t accelerateForward(uint8_t fromSpeed, uint8_t toSpeed, int accelerateSpeed);

    /**
     * Accelerate backward.
     * @param fromSpeed: start speed (0 <= fromSpeed <= 255 & fromSpeed < toSpeed).
     * @param toSpeed: end speed (0 <= toSpeed <= 255 & toSpeed > fromSpeed).
     * @param accelerateSpeed: acceleration speed (the smaller accelerateSpeed the faster the acceleration because in fact accelerateSpeed is a "delay").
     * @return 1 in case of error ( if fromSpeed >= toSpeed), otherwise 0.
     */
    uint8_t accelerateBackward(uint8_t fromSpeed, uint8_t toSpeed, int accelerateSpeed);

    /**
     * Deccelerate forward.
     * @param fromSpeed: start speed (0 <= fromSpeed <= 255 & fromSpeed > toSpeed).
     * @param toSpeed: end speed (0 <= toSpeed <= 255 & toSpeed < fromSpeed).
     * @param deccelerateSpeed: decceleration speed (the smaller deccelerateSpeed the faster the decceleration because in fact deccelerateSpeed is a "delay").
     * @return 1 in case of error ( if fromSpeed <= toSpeed), otherwise 0.
     */
    uint8_t deccelerateForward(uint8_t fromSpeed, uint8_t toSpeed, int deccelerateSpeed);

    /**
     * Deccelerate backward.
     * @param fromSpeed: start speed (0 <= fromSpeed <= 255 & fromSpeed > toSpeed).
     * @param toSpeed: end speed (0 <= toSpeed <= 255 & toSpeed < fromSpeed).
     * @param deccelerateSpeed: decceleration speed (the smaller deccelerateSpeed the faster the decceleration because in fact deccelerateSpeed is a "delay").
     * @return 1 in case of error ( if fromSpeed <= toSpeed), otherwise 0.
     */
    uint8_t deccelerateBackward(uint8_t fromSpeed, uint8_t toSpeed, int deccelerateSpeed);

    /**
     * Turn to the right.
     * @param speed: the speed of rotation.
     */
    void turnRight(int speed) const;

    /**
     * Turn to the left.
     * @param speed: the speed of rotation.
     */
    void turnLeft(int speed) const;

    /**
     * Stop motor during acceleration or deceleration.
     */
    void stopMotorAccelerationDeceleration();

private:

    uint8_t pinA1A_;
    uint8_t pinA1B_;
    uint8_t pinB1A_;
    uint8_t pinB1B_;
    bool stopAccelerateDecelerate_;

    /**
     * Initialize pins.
     */
    void initPin();

};

#endif //_MOTOR_DRIVER_L9910_H_
