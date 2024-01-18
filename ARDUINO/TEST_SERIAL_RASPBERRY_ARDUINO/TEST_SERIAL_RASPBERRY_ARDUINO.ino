/*
  Jocelyn GIROD
  15/01/2024

  Programme de test de la liaison série
  Arduino - Raspberry
*/

#include "Lcd216Driver.h"
#include "FrameManager.h"

const uint8_t RX_PIN = 0;
const uint8_t TX_PIN = 2;

Lcd216Driver lcd216Driver(RX_PIN, TX_PIN);
FrameManager frameManager;

void setup() {

  // Initialisation du terminal serie
  Serial.begin(19200);

  //lcd216Driver.setLcdSize(16, 2);

  lcd216Driver.autoScrollOff();
  //lcd216Driver.blockCursorOn();
  lcd216Driver.underlineCursorOn();

  //lcd216Driver.setContrast(250);
  lcd216Driver.setDefaultContrast();

}

void loop() {

  // Lecture des trames sur le port série.
  if (Serial.available() > 0) {
    String frame = "";
    frame = Serial.readString();
    frame.trim();

    frameManager.setFrame(frame.c_str(), frame.length());
    char device = frameManager.getDevice();

    if (device == 'T') {
      lcd216Driver.clearScreen();
      lcd216Driver.setCursorPosition(1, 1);
      // Red backlight color R:204, G:0, B:0
      lcd216Driver.setbacklightColor(204, 0, 0);
      lcd216Driver.writeMessage(frame);
    } else if (device == 'A') {
      lcd216Driver.clearScreen();
      lcd216Driver.setCursorPosition(1, 1);
      // Blue backlight color R:0, G:102, B:0
      lcd216Driver.setbacklightColor(0, 102, 204);
      lcd216Driver.writeMessage(frame);
    } else if (device == 'C') {
      lcd216Driver.clearScreen();
      lcd216Driver.setCursorPosition(1, 1);
      // Orange backlight color R:96, G:50, B:5
      lcd216Driver.setbacklightColor(96, 50, 5);
      lcd216Driver.writeMessage(frame);
    }

  }

}
