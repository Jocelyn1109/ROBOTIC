/*
  Jocelyn GIROD
  22/11/2023

  Programme de tests de la librairie ServoDriverPCA9685.

*/

#include "ServoDriverPCA9685.h"

ServoDriverPCA9685 servoDriverPCA9685(0x40, 50.0, 27000000);
bool initBreakout = false;

void setup() {

  Serial.begin(19200);

  initBreakout = servoDriverPCA9685.initDriver();

  if (initBreakout) {
    //TODO
  } else {
    Serial.println(F("Erreur d'initialisation du breakout."));
  }
}

void loop() {
  // put your main code here, to run repeatedly:
}
