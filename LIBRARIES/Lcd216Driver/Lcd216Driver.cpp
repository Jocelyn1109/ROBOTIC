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

/**
 * Set the cursor position.
 * @param column: column number (between 1 and 16).
 * @param line: line number ligne (0 or 1).
 */
void Lcd216Driver::setCursorPosition(uint8_t column, uint8_t line) {

    if ((column >= 1 && column <= 16) && (line == 0 || line == 1)) {
        lcd_.write(CMD_SET_CURSOR_POSITION[0]);
        lcd_.write(CMD_SET_CURSOR_POSITION[1]);
        lcd_.write(column);
        lcd_.write(line);

        delay(10);
    }
}

/**
 * Set the cursor to the home position (column 1 and line 0).
   */
void Lcd216Driver::goHome() {
    lcd_.write(CMD_GO_HOME[0]);
    lcd_.write(CMD_GO_HOME[1]);
    delay(10);
}

/**
 * Moving the cursor one character back.
 * If the position is already (1,0) the cursor is moved to the last position on the screen.
 */
void Lcd216Driver::cursorBack() {
    lcd_.write(CMD_CURSOR_BACK[0]);
    lcd_.write(CMD_CURSOR_BACK[1]);
    delay(10);
}

/**
 * Moves the cursor one character forward.
 * If the cursor is at the last position, it is moved to the original location (1,1).
 */
void Lcd216Driver::cursorForward() {
    lcd_.write(CMD_CURSOR_FORWARD[0]);
    lcd_.write(CMD_CURSOR_FORWARD[1]);
    delay(10);
}

/**
 * Displays the underlined cursor.
 */
void Lcd216Driver::underlineCursorOn() {
    lcd_.write(CMD_UNDERLINE_CURSOR_ON[0]);
    lcd_.write(CMD_UNDERLINE_CURSOR_ON[1]);
    delay(10);
}

/**
 * Disables the display of the underlined cursor.
 */
void Lcd216Driver::underlineCursorOff() {
    lcd_.write(CMD_UNDERLINE_CURSOR_OFF[0]);
    lcd_.write(CMD_UNDERLINE_CURSOR_OFF[1]);
    delay(10);
}

/**
 * Turn on the blincking bloxk cursor.
 */
void Lcd216Driver::blockCursorOn() {
    lcd_.write(CMD_BLOCK_CURSOR_ON[0]);
    lcd_.write(CMD_BLOCK_CURSOR_ON[1]);
    delay(10);
}

/**
 * Turn off the blincking bloxk cursor.
 */
void Lcd216Driver::blockCursorOff() {
    lcd_.write(CMD_BLOCK_CURSOR_OFF[0]);
    lcd_.write(CMD_BLOCK_CURSOR_OFF[1]);
    delay(10);
}

/**
 * Method for changing the background color of the LCD screen.
 * The values of the colors must evolve between 0 and 255 (one byte/byte).
 * The color is saved in the EEPROM.
 * @param red: red value.
 * @param green: green value.
 * @param blue: blue value.
 */
void Lcd216Driver::setbacklightColor(uint8_t red, uint8_t green, uint8_t blue) {
    lcd_.write(CMD_SET_BACKLIGHT_COLOR[0]);
    lcd_.write(CMD_SET_BACKLIGHT_COLOR[1]);
    lcd_.write(red);
    lcd_.write(green);
    lcd_.write(blue);
    delay(10);
}

/**
 * Method for setting the size of the LCD screen.
 * This command allows to indicate to the backpack the size of the screen which is attached to it.
 * This value is saved in the EEPROM and therefore, this operation must be performed only once.
 * @param nbRow: row number.
 * @param nbColumn: column number.
 */
void Lcd216Driver::setLcdSize(uint8_t nbRow, uint8_t nbColumn) {
    lcd_.write(CMD_SET_LCD_SIZE[0]);
    lcd_.write(CMD_SET_LCD_SIZE[1]);
    lcd_.write(nbRow);
    lcd_.write(nbColumn);
    delay(10);
}

/**
 * Method for creating a custom character.
 * Creates a custom character in a given storage location (a position).
 * This position must be between 0 and 7 (there are 8 memory slots to store custom characters).
 * 8 bytes (bytes of data) are sent to indicate to the backpack how it should be displayed.
 * @param position: memory position of the character.
 * @param characterValues: character values.
 * @return 1 if position is greater than expected, otherise 0.
 */
uint8_t Lcd216Driver::createCustomCharacter(uint8_t position, uint8_t *characterValues) {

    if (position > 7) {
        return 1;
    }

    lcd_.write(CMD_CREATE_CUSTOM_CHARACTER[0]);
    lcd_.write(CMD_CREATE_CUSTOM_CHARACTER[1]);
    lcd_.write(position);

    for (int i = 0; i < 8; i++) {
        lcd_.write(characterValues[i]);
    }

    delay(10);
    return 0;
}

/**
 * Method to save the custom character in a bank of the EEPROM to be able to reuse them later.
 * There are 4 banks (from 0 to 3) of storage and 8 positions per bank.
 * @param bank
 * @return 1 if bank number than expected, otherise 0.
 */
uint8_t Lcd216Driver::saveCustomCharacter(uint8_t bank) {

    if (bank > 7) {
        return 1;
    }

    lcd_.write(CMD_SAVE_CUSTOM_CARACTER[0]);
    lcd_.write(CMD_SAVE_CUSTOM_CARACTER[1]);
    lcd_.write(bank);

    delay(10);
    return 0;
}

/**
 * Write message on lcd.
 * @param message: message.
 */
void Lcd216Driver::writeMessage(String message) {

    lcd_.write(message.c_str());
}
