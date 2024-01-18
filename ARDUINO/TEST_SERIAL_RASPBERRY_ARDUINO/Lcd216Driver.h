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

    /* Cursor movement & modification commands */

    /**
     * Set the cursor position.
     * @param column: column number (between 1 and 16).
     * @param line: line number ligne (0 or 1).
     */
    void setCursorPosition(uint8_t column, uint8_t line);

    /**
     * Set the cursor to the home position (column 1 and line 0).
     */
    void goHome();

    /**
     * Moves the cursor one character back.
     * If the position is already (1,0) the cursor is moved to the last position on the screen.
     */
    void cursorBack();

    /**
     * Moves the cursor one character forward.
     * If the cursor is at the last position, it is moved to the original location (1,1).
     */
    void cursorForward();

    /**
     * Displays the underlined cursor.
     */
    void underlineCursorOn();

    /**
     * Disables the display of the underlined cursor.
     */
    void underlineCursorOff();

    /**
     * Turn on the blincking block cursor.
     */
    void blockCursorOn();

    /**
     * Turn off the blincking block cursor.
     */
    void blockCursorOff();


    /* RGB backlight and LCD size commands */

    /**
     * Method for changing the background color of the LCD screen.
     * The values of the colors must evolve between 0 and 255 (one byte/byte).
     * The color is saved in the EEPROM.
     * @param red: red value.
     * @param green: green value.
     * @param blue: blue value.
     */
    void setbacklightColor(uint8_t red, uint8_t green, uint8_t blue);

    /**
     * Method for setting the size of the LCD screen.
     * This command allows to indicate to the backpack the size of the screen which is attached to it.
     * This value is saved in the EEPROM and therefore, this operation must be performed only once.
     * @param nbColumn: column number.
     * @param nbRow: row number.
 */
    void setLcdSize(uint8_t nbColumn, uint8_t nbRow);

    /**
     * Method for creating a custom character.
     * Creates a custom character in a given storage location (a position).
     * This position must be between 0 and 7 (there are 8 memory slots to store custom characters).
     * 8 bytes (bytes of data) are sent to indicate to the backpack how it should be displayed.
     * @param position
     * @param characterValues
     * @return 1 if position is greater than expected, otherise 0.
     */
    uint8_t createCustomCharacter(uint8_t position, uint8_t characterValues[8]);

    /**
     * Method to save the custom character in a bank of the EEPROM to be able to reuse them later.
     * There are 4 banks (from 0 to 3) of storage and 8 positions per bank.
     * @param bank
     * @return 1 if bank number than expected, otherise 0.
     */
    uint8_t saveCustomCharacter(uint8_t bank);

    /**
     * Method allowing the loading of the 8 characters saved in a bank of the EEPROM in the memory of the LCD.
     * @param bankToLoad (there are 4 banks from 0 to 3 of storage and 8 positions per bank).
     * @return 1 if bank number than expected, otherise 0.
     */
    uint8_t loadCustomCharacters(uint8_t bankToLoad);

    /* Read/Write message command */
    /**
     * Write message on lcd.
     * @param message: message.
     */
    void writeMessage(String message);

private:

    SoftwareSerial lcd_ = SoftwareSerial(0, 0);

};

#endif //_LCD216DRIVER_H_
