/**
 * Jocelyn GIROD - 07/07/2023
 * Set of commands available for the Adafruit 2x16 USB/Series LCD display.
 */

#ifndef LCD216DRIVER_LCDPARAMS_H
#define LCD216DRIVER_LCDPARAMS_H

#include <stdint.h>

/* BASIC COMMANDS */

/* Command display on. This command activates the backlight. */
const uint8_t CMD_DISPLAY_ON[] = {0xFE, 0x42};

/* Command display off. This command disables the backlight. */
const uint8_t CMD_DISPLAY_OFF[] = {0xFE, 0x46};

/* Command set brightness. Set the brightness of the backlight.
   The color is fixed separately - the brightness configuration takes effect only after fixing the color.
   This parameter is saved in the EEPROM. */
const uint8_t CMD_SET_BRIGHTNESS[] = {0xFE, 0x99};

/* Command set contrast. Set the contrast.
   Generally, a value between 180 and 220 works correctly. By default, it is the value 220 that will be used.
   This parameter is saved in the EEPROM. */
const uint8_t CMD_SET_CONTRAST[] = {0xFE, 0x50};

/* Command autoscrolle on - automatic scrolling.
   Auto-scrolling is enabled when there is more text received than space on the screen.
   In this case, the text scrolls automatically and, therefore, the second line becomes the first line, etc.
   New text is always displayed at the bottom of the screen. */
const uint8_t CMD_AUTOSCROLL_ON[] = {0xFE, 0x51};

/* Command autoscrolle off - disable automatic scrolling.
   When the display receives text and if there is no more room on the screen then the display starts again
   at the top left of the screen to continue viewing. */
const uint8_t CMD_AUTOSCROLL_OFF[] = {0xFE, 0x52};

/* Command clear screen. Clear the screen. */
const uint8_t CMD_CLEAR_SCREEN[] = {0xFE, 0x58};

/* Command change startup splash screen.
   Changes the message when the LCD starts (the splash screen). After sending this command, send 32 characters (for a 16x2 LCD).
   If you don't want a splash screen, write a series of spaces. */
const uint8_t CMD_CHANGE_STARTUP_SPLASH_SCREEN[] = {0xFE, 0x40};


/* CURSOR MOVE & EDIT COMMANDS ----------------*/

/* Command set cursor position. Moves cursor position.
   The column number and row start at 1.0, respectively. The first position at the top left is 1.0. */
const uint8_t CMD_SET_CURSOR_POSITION[] = {0xFE, 0x47};

/* Command go home. Returns to the original location. Position (1, 0).  */
const uint8_t CMD_GO_HOME[] = {0xFE, 0x48};

/* Command cursor back. Moves the cursor back one character.
   If the position is already (1,0) the cursor is moved to the last position of the screen. */
const uint8_t CMD_CURSOR_BACK[] = {0xFE, 0x4C};

/* Command cursor forward. Moves the cursor one character forward.
 * If the cursor is at the last position, it is moved to the original location (1,1). */
const uint8_t CMD_CURSOR_FORWARD[] = {0xFE, 0x4D};

/* Command underline cursor on. Displays underlined cursor. */
const uint8_t CMD_UNDERLINE_CURSOR_ON[] = {0xFE, 0x4A};

/* Command underline cursor off. Disable underlined cursor. */
const uint8_t CMD_UNDERLINE_CURSOR_OFF[] = {0xFE, 0x4B};

/* Command block cursor on. Activates the "flashing block" cursor. */
const uint8_t CMD_BLOCK_CURSOR_ON[] = {0xFE, 0x53};

/* Command block cursor off. Disable the "flashing block" cursor. */
const uint8_t CMD_BLOCK_CURSOR_OFF[] = {0xFE, 0x54};


/* RGB BACKLIGHT CONTROLS AND LCD SIZE ---------------------*/

/* Set RGB Backlight Color. Allows you to change the background color.
   0xFE 0xD0 - initializes the red, green, and blue components of the backlight.
   Color values must range from 0 to 255 (one byte/byte). Colour is saved in the EEPROM.
   Each of the colors R, G and B is represented in a byte/byte right after the command.
   To set the backlight to red, send the command 0xFE 0xD0 0xFF 0x0 0x0.
   In blue, it's 0xFE 0xD0 0x0 0x0 0xFF.
   In white, it is 0xFE 0xD0 0xFF 0xFF 0xFF... */
const uint8_t CMD_SET_BACKLIGHT_COLOR[] = {0xFE, 0xD0};

/* Command set lcd size. Allows you to set the size of the lcd screen.
   0xFE 0xD1 - This command is used to indicate to the backpack the size of the screen attached to it.
   This value is saved in the EEPROM and therefore this operation only needs to be performed once. */
const uint8_t CMD_SET_LCD_SIZE[] = {0xFE, 0xD1};


/* CUSTOM CHARACTER CONTROLS */

/* Command create custom character - Allows you to create custom characters.
   0xFE 0x4E - Creates a custom character in a given storage location (a position).
   This position must be between 0 and 7 (there are 8 memory slots to store custom characters).
   8 bytes (bytes of data) are sent to tell the backpack how it should be displayed. */
const uint8_t CMD_CREATE_CUSTOM_CHARACTER[] = {0xFE, 0x4E};

/* Command Save custom character to EEPROM bank.
   0xFE 0xC1 - Save the personalized character in an EEPROM bank to be able to reuse them later.
   There are 4 banks (from 0 to 3) of storage and 8 positions per bank. */
const uint8_t CMD_SAVE_CUSTOM_CARACTER[] = {0xFE, 0xC1};


/* Commande load custom characters from EEPROM bank.
   0xFE 0xC0 - This loads the 8 characters saved in an EEPROM bank into the LCD memory. */
const uint8_t CMD_LOAD_CUSTOM_CHARACTERS[] = {0xFE, 0xC0};

#endif //LCD216DRIVER_LCDPARAMS_H
