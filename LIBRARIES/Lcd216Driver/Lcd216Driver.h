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

    /**
     * Change the startup splash screen with a new message.
     * @param message: new message (max 32 characters).
     * @return 1 if the message > 32 characters, otherwise 0.
     */
    uint8_t changeStartupSplashScreen(String message);

    /**
     * No message on the startup splash screen.
     */
    void startupSplashScreenNoMessage();

    /**
     * Lcd screen backlight activation.
     * @param minutes: number of minutes the display must remain on.
     */
    void displayOn(uint8_t minutes);

    /**
     * Lcd screen backlight off.
     */
    void displayOff();

    /**
     * Set the brightness of the lcd screen.
     * The color is set separately - the brightness setting takes effect only after setting the color.
     * This parameter is saved in the EEPROM.
     * @param brightness: brightness value.
     */
    void setBrightness(uint8_t brightness);

    /**
     * Define the lcd contrast.
     * In general, a value between 180 and 220 works correctly.
     * This parameter is saved in the EEPROM.
     * @param contrast: constrast value.
     */
    void setContrast(uint8_t contrast);

    /**
     * The the default contrast (by default 220).
     */
    void setDefaultContrast();

    /**
     * Set the default color.
     */
    void setDefaultColor();

private:

    SoftwareSerial lcd_ = SoftwareSerial(0, 0);

};

#endif //_LCD216DRIVER_H_
