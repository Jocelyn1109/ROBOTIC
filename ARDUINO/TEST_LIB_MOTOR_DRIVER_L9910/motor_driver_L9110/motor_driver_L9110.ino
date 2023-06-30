/*
  Jocelyn GIROD
  30/06/2023

  Programme de test de la librairie MotorDriverL9910.
  Test sans le logger.
*/

#include "MotorDriverL9910.h"

const uint8_t AIA = 4;
const uint8_t AIB = 5;
const uint8_t BIA = 2;
const uint8_t BIB = 3;

bool start_test = true;

MotorDriverL9910 motorDriverL9910(AIA, AIB, BIA, BIB);

void setup() {

  // Initialisation du terminal série
  Serial.begin(19200);
}

void loop() {

  if (start_test) {

    Serial.println("Début du test");

    // go forward - speed 120
    Serial.println("Go forward - speed 120");
    motorDriverL9910.goForward(120);
    delay(5000);
    motorDriverL9910.stopMotor();

    // go backward - speed 120
    Serial.println("Go backward - speed 120");
    motorDriverL9910.goBackward(120);
    delay(5000);
    motorDriverL9910.stopMotor();

    // accelerate forward - speed 0 to 255
    Serial.println("Accelerate forward - speed 0 to 255");
    uint8_t resAccF = motorDriverL9910.accelerateForward(0, 255, 50);
    if (resAccF != 0) {
      Serial.println("Erreur accelerate forward - speed 0 to 255");
    }
    delay(10000);
    motorDriverL9910.stopMotor();

    // accelerate backward - speed 0 to 255
    Serial.println("Accelerate backward - speed 0 to 255");
    uint8_t resAccB = motorDriverL9910.accelerateBackward(0, 255, 50);
    if (resAccB != 0) {
      Serial.println("Erreur acccelerate backward - speed 0 to 255");
    }
    delay(10000);
    motorDriverL9910.stopMotor();

    // deccelerate forward - speed 120 to 0
    Serial.println("Deccelerate forward - speed 120 to 0");
    uint8_t resDeccF = motorDriverL9910.deccelerateForward(120, 0, 50);
    if (resDeccF != 0) {
      Serial.println("Erreur deccelerate forward - speed 120 to 0");
    }
    delay(10000);
    motorDriverL9910.stopMotor();

    // deccelerate backward - speed 120 to 0
    Serial.println("Deccelerate backward - speed 120 to 0");
    uint8_t resDeccB = motorDriverL9910.deccelerateBackward(120, 0, 50);
    if (resDeccB != 0) {
      Serial.println("Erreur deccelerate backward - speed 120 to 0");
    }
    delay(10000);
    motorDriverL9910.stopMotor();

    start_test = false;
  }
}
