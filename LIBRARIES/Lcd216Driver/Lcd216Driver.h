#ifndef _LCD216DRIVER_H_
#define _LCD216DRIVER_H_

#include <SoftwareSerial.h>
#include <stdint.h>

class Lcd216Driver {

public:

    /**
     * Default constructor.
     * @param rxPin: Receive pin.
     * @param txPin: Transmit pin.
     */
    explicit Lcd216Driver(uint8_t rxPin, uint8_t txPin);

    /**
     * Copy constructor.
     *
     * @param other Lcd216Driver object.
     */
    Lcd216Driver(const Lcd216Driver &orig);

    /**
     * Destructor
     */
    virtual ~Lcd216Driver();

    void init();

    /* Base commands */

    /**
     * Clear the screen.
     */
    void clearScreen();

    /**
     * Enable autoscroll.
     */
    void autoScrollOn();

    /**
     * Disable autoscroll.
     */
    void autoScrollOff();

    long int changeStartupSplashScreen(String message);

    long int startupSplashScreenNoMessage();

    long int displayOn(unsigned char minutes);

    long int displayOff();

    long int setBrightness(unsigned char brightness);

    long int setContrast(unsigned char contrast);

    long int setDefaultContrast();

    long int setDefaultColor();

private:
    SoftwareSerial lcd_ = SoftwareSerial(0, 0);
    int fileDescriptor_;

};

#endif //_LCD216DRIVER_H_
