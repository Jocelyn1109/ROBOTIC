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
bool frameReceived = false;

void setup() {

  // Initialisation du terminal serie
  Serial.begin(19200);

  pinMode(3, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(3), stopTank, RISING);

  // Initialisation du LCD
  lcd216Driver.autoScrollOff();
  lcd216Driver.underlineCursorOn();
  lcd216Driver.setDefaultContrast();
  lcd216Driver.setDefaultColor();
  lcd216Driver.clearScreen();

}

void loop() {

  String frame = "";

  // Lecture des trames sur le port série.
  if (Serial.available() > 0) {

    frame = Serial.readString();
    Serial.print(F("Frame length: "));
    Serial.println(frame.length());

    if (frame.length() > 8) {
      lcd216Driver.clearScreen();
      lcd216Driver.setCursorPosition(1, 1);
      lcd216Driver.writeMessage("ERROR FRAME");
    } else {
      frameReceived = true;
    }
  }

  if (frameReceived) {
    frameReceived = false;

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
      // Green backlight color R:0, G:153, B:0
      lcd216Driver.setbacklightColor(0, 153, 0);
      lcd216Driver.writeMessage(frame);
    }
  }

}

void stopTank() {
  digitalWrite(LED_BUILTIN, ! digitalRead(LED_BUILTIN));
  Serial.println(F("stop"));
}
