/*
  Jocelyn GIROD
  30/06/2023

  Programme de test de la librairie MotorDriverL9910.
  Test sans le logger.
*/

#include "MotorDriverL9910.h"

const uint8_t A1A = 3;
const uint8_t A1B = 9;
const uint8_t B1A = 10;
const uint8_t B1B = 11;

bool start_test = true;

MotorDriverL9910 motorDriverL9910(A1A, A1B, B1A, B1B);

void setup() {

  // Initialisation du terminal série
  Serial.begin(19200);

  pinMode(A1A, OUTPUT);
  pinMode(A1B, OUTPUT);
  pinMode(B1A, OUTPUT);
  pinMode(B1B, OUTPUT);
}

void loop() {

  if (start_test) {

    Serial.println("Début du test");

    // go forward - speed 120
    Serial.println("Go forward - speed 120");
    motorDriverL9910.goForward(120);
    delay(5000);
    motorDriverL9910.stopMotor();
    delay(100);

    // go backward - speed 120
    Serial.println("Go backward - speed 120");
    motorDriverL9910.goBackward(120);
    delay(5000);
    motorDriverL9910.stopMotor();
    delay(100);

    // accelerate forward - speed 60 to 255
    Serial.println("Accelerate forward - speed 60 to 255");
    uint8_t resAccF = motorDriverL9910.accelerateForward(60, 255, 20);
    if (resAccF != 0) {
      Serial.println("Erreur accelerate forward - speed 60 to 255");
    }
    delay(10000);

    // deccelerate forward - speed 255 to 60
    Serial.println("Deccelerate forward - speed 255 to 60");
    uint8_t resDeccF = motorDriverL9910.deccelerateForward(255, 60, 50);
    if (resDeccF != 0) {
      Serial.println("Erreur deccelerate forward - speed 255 to 60");
    }
    delay(10000);
    motorDriverL9910.stopMotor();
    delay(100);

    // accelerate backward - speed 60 to 255
    Serial.println("Accelerate backward - speed 60 to 255");
    uint8_t resAccB = motorDriverL9910.accelerateBackward(60, 255, 50);
    if (resAccB != 0) {
      Serial.println("Erreur acccelerate backward - speed 60 to 255");
    }
    delay(10000);

    // deccelerate backward - speed 255 to 60
    Serial.println("Deccelerate backward - speed 255 to 60");
    uint8_t resDeccB = motorDriverL9910.deccelerateBackward(255, 60, 50);
    if (resDeccB != 0) {
      Serial.println("Erreur deccelerate backward - speed 255 to 60");
    }
    delay(10000);
    motorDriverL9910.stopMotor();
    delay(300);

    // turn right
    Serial.println("Turn right - speed 100");
    motorDriverL9910.turnRight(100);
    delay(5000);
    motorDriverL9910.stopMotor();
    delay(300);

    // turn left
    Serial.println("Turn left - speed 100");
    motorDriverL9910.turnLeft(100);
    delay(5000);
    motorDriverL9910.stopMotor();
    delay(100);

    Serial.println("Stop tests");
    start_test = false;
  }
}
