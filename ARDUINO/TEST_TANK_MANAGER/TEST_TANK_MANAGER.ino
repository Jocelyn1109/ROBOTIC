/*
  Jocelyn GIROD
  04/06/2024

  Programme de test du TankManager
  Arduino - Raspberry
*/

#include "TankManager.h"

const uint8_t A1A = 5;   // pin PWM
const uint8_t A1B = 6;   // pin PWM
const uint8_t B1A = 9;  // pin PWM
const uint8_t B1B = 10;  // pin PWM

bool start_test = true;

TankManager tankManager = TankManager(nullptr, A1A, A1B, B1A, B1B);

void setup() {

  // Initialisation du terminal serie
  Serial.begin(19200);

  pinMode(3, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(3), stopTank, RISING);

  pinMode(A1A, OUTPUT);
  pinMode(A1B, OUTPUT);
  pinMode(B1A, OUTPUT);
  pinMode(B1B, OUTPUT);
}

void loop() {

  if (start_test) {

    Serial.println(F("Début du test"));

    // go forward - speed 200
    Serial.println(F("Go forward - speed 200"));
    uint8_t resGoF = tankManager.goForward(200);
    if (resGoF == 0) {
      delay(5000);
      tankManager.stopTank();
      delay(100);
    } else {
      Serial.println(F("Erreur goforward !"));
    }


    // go backward - speed 200
    Serial.println(F("Go backward - speed 200"));
    uint8_t resGoB = tankManager.goBackward(200);
    if (resGoB == 0) {
      delay(5000);
      tankManager.stopTank();
      delay(100);
    } else {
      Serial.println(F("Erreur gobackward !"));
    }


    // accelerate forward - speed 100 to 255
    Serial.println(F("Accelerate forward - speed 100 to 255"));
    uint8_t resAccF = tankManager.accelerateForward(100, 255, 50);
    if (resAccF != 0) {
      Serial.println(F("Erreur accelerate forward - speed 100 to 255"));
    }
    delay(10000);

    // decelerate forward - speed 255 to 100
    Serial.println(F("Decelerate forward - speed 255 to 100"));
    uint8_t resDeccF = tankManager.decelerateForward(255, 100, 50);
    if (resDeccF != 0) {
      Serial.println(F("Erreur decelerate forward - speed 255 to 100"));
    }
    delay(10000);
    tankManager.stopTank();
    delay(100);

    // accelerate backward - speed 100 to 255
    Serial.println(F("Accelerate backward - speed 100 to 255"));
    uint8_t resAccB = tankManager.accelerateBackward(100, 255, 50);
    if (resAccB != 0) {
      Serial.println(F("Erreur acccelerate backward - speed 100 to 255"));
    }
    delay(10000);

    // decelerate backward - speed 255 to 100
    Serial.println(F("Deccelerate backward - speed 255 to 100"));
    uint8_t resDeccB = tankManager.decelerateBackward(255, 100, 50);
    if (resDeccB != 0) {
      Serial.println(F("Erreur decelerate backward - speed 255 to 100"));
    }
    delay(10000);
    tankManager.stopTank();
    delay(300);

    // turn right
    Serial.println(F("Turn right - speed 100"));
    uint8_t resTR = tankManager.turnRight(100);
    if (resTR == 0) {
      delay(5000);
      tankManager.stopTank();
      delay(300);
    } else {
      Serial.println(F("Erreur turn right !"));
    }


    // turn left
    Serial.println(F("Turn left - speed 100"));
    uint8_t resTL = tankManager.turnLeft(100);
    if (resTL == 0) {
      delay(5000);
      tankManager.stopTank();
      delay(100);
    } else {
      Serial.println(F("Erreur turn left !"));
    }


    Serial.println(F("Stop tests"));
    start_test = false;
  }
}

void stopTank() {
  Serial.println(F("interrupt: stop"));
  //tankManager.stopAccelerationDeceleration();
}
