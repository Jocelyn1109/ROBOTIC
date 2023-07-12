#include <Arduino.h>
#include "Lcd216Driver.h"
#include "lcdparams.h"

/**
 * Default constructor.
 * @param rxPin: Receive pin.
 * @param txPin: Transmit pin.
 */
Lcd216Driver::Lcd216Driver(uint8_t rxPin, uint8_t txPin) {
    lcd_ = SoftwareSerial(rxPin, txPin);
}

/**
 * Copy constructor.
 *
 * @param other Lcd216Driver object.
 */
Lcd216Driver::Lcd216Driver(const Lcd216Driver &orig) {}

/**
 * Destructor
 */
Lcd216Driver::~Lcd216Driver() {}


/**
 * Clear the screen.
 */
void Lcd216Driver::clearScreen() {
    lcd_.write(CMD_CLEAR_SCREEN[0]);
    lcd_.write(CMD_CLEAR_SCREEN[1]);
    delay(10);
}

/**
 * Enable autoscroll.
 */
void Lcd216Driver::autoScrollOn() {
    lcd_.write(CMD_AUTOSCROLL_ON[0]);
    lcd_.write(CMD_AUTOSCROLL_ON[1]);
    delay(10);
}

/**
 * Disable autoscroll.
 */
void Lcd216Driver::autoScrollOff() {
    lcd_.write(CMD_AUTOSCROLL_OFF[0]);
    lcd_.write(CMD_AUTOSCROLL_OFF[1]);
    delay(10);
}

/**
 * Change the startup splash scree with a new message.
 * @param message: new message (max 32 characters).
 * @return 1 if the message > 32 characters, otherwise 0.
 */
uint8_t Lcd216Driver::changeStartupSplashScreen(String message) {

    if (message.length() > 32) {
        return 1;
    }

    char buffer[message.length() + 1];
    message.toCharArray(buffer, message.length() + 1);

    lcd_.write(CMD_CHANGE_STARTUP_SPLASH_SCREEN[0]);
    lcd_.write(CMD_CHANGE_STARTUP_SPLASH_SCREEN[1]);
    for (int i = 0; i < message.length() + 1; i++) {
        lcd_.write(buffer[i]);
    }
    delay(10);
    return 0;
}

/**
 * No message on the startup splash screen.
 */
void Lcd216Driver::startupSplashScreenNoMessage() {

    unsigned char message[32];
    for (int i = 0; i < 32; i++) {
        message[i] = ' ';
    }

    lcd_.write(CMD_CHANGE_STARTUP_SPLASH_SCREEN[0]);
    lcd_.write(CMD_CHANGE_STARTUP_SPLASH_SCREEN[1]);
    for (int i = 0; i < 32 + 1; i++) {
        lcd_.write(message[i]);
    }

    delay(10);
}

/**
 * Lcd screen backlight activation.
 * @param minutes: number of minutes the display must remain on.
 */
void Lcd216Driver::displayOn(uint8_t minutes) {

    lcd_.write(CMD_DISPLAY_ON[0]);
    lcd_.write(CMD_DISPLAY_ON[1]);
    lcd_.write(minutes);

    delay(10);
}

/**
 * Lcd screen backlight off.
 */
void Lcd216Driver::displayOff() {

    lcd_.write(CMD_DISPLAY_OFF[0]);
    lcd_.write(CMD_DISPLAY_OFF[1]);

    delay(10);
}

/**
 * Set the brightness of the lcd screen.
 * The color is set separately - the brightness setting takes effect only after setting the color.
 * This parameter is saved in the EEPROM.
 * @param brightness: the value of the brightness.
 */
void Lcd216Driver::setBrightness(uint8_t brightness) {

    lcd_.write(CMD_SET_BRIGHTNESS[0]);
    lcd_.write(CMD_SET_BRIGHTNESS[1]);
    lcd_.write(brightness);

    delay(10);
}

/**
 * Define the lcd contrast.
 * In general, a value between 180 and 220 works correctly.
 * This parameter is saved in the EEPROM.
 * @param contrast: constrast value.
 */
void Lcd216Driver::setContrast(uint8_t contrast) {

    lcd_.write(CMD_SET_CONTRAST[0]);
    lcd_.write(CMD_SET_CONTRAST[1]);
    lcd_.write(contrast);

    delay(10);
}

/**
 * The the default contrast (by default 220).
 */
void Lcd216Driver::setDefaultContrast() {

    lcd_.write(CMD_SET_CONTRAST[0]);
    lcd_.write(CMD_SET_CONTRAST[1]);
    lcd_.write(0xDC);

    delay(10);
}

/**
 * Set the default color.
 */
void Lcd216Driver::setDefaultColor() {

    uint8_t red = 0xB5;
    uint8_t green = 0xD5;
    uint8_t blue = 0x92;

    lcd_.write(CMD_SET_BACKLIGHT_COLOR[0]);
    lcd_.write(CMD_SET_BACKLIGHT_COLOR[1]);
    lcd_.write(red);
    lcd_.write(green);
    lcd_.write(blue);

    delay(10);
}
