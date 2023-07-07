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
