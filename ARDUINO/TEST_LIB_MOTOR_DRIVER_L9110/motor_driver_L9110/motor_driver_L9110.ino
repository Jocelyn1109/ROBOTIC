/*
  Jocelyn GIROD
  30/06/2023

  Programme de test de la librairie MotorDriverL9910.
  Test sans le logger.
*/

#include "MotorDriverL9110.h"
#include "Logger.h"

const uint8_t A1A = 3;   // pin PWM
const uint8_t A1B = 5;   // pin PWM
const uint8_t B1A = 9;   // pin PWM
const uint8_t B1B = 10;  // pin PWM
const uint8_t SC_PIN = 4;

uint8_t resInitLog = 0;
bool start_test = true;

Logger logger{String("drvL9110.txt")};
MotorDriverL9110 motorDriverL9110{A1A, A1B, B1A, B1B, &logger};

void setup() {

  // Initialisation du terminal série
  Serial.begin(19200);

  //Initialisation du logger
  resInitLog = logger.loggerInitialization(SC_PIN);
  if (resInitLog == 1) {
    Serial.println(F("Erreur lors de l'initialisation du logger"));
  } else {
    Serial.println(F("Succès de l'initialisation du logger"));
  }

  pinMode(A1A, OUTPUT);
  pinMode(A1B, OUTPUT);
  pinMode(B1A, OUTPUT);
  pinMode(B1B, OUTPUT);
}

void loop() {

  if (start_test && resInitLog == 0) {

    Serial.println("Début du test");

    // go forward - speed 200
    Serial.println("Go forward - speed 200");
    uint8_t resGoF = motorDriverL9110.goForward(200);
    if (resGoF == 0) {
      delay(5000);
      motorDriverL9110.stopMotor();
      delay(100);
    } else {
      Serial.println(F("Erreur goforward !"));
    }


    // go backward - speed 200
    Serial.println("Go backward - speed 200");
    uint8_t resGoB = motorDriverL9110.goBackward(200);
    if (resGoB == 0) {
      delay(5000);
      motorDriverL9110.stopMotor();
      delay(100);
    } else {
      Serial.println(F("Erreur gobackward !"));
    }


    // accelerate forward - speed 100 to 255
    Serial.println("Accelerate forward - speed 100 to 255");
    uint8_t resAccF = motorDriverL9110.accelerateForward(100, 255, 20);
    if (resAccF != 0) {
      Serial.println("Erreur accelerate forward - speed 100 to 255");
    }
    delay(10000);

    // decelerate forward - speed 255 to 100
    Serial.println("Decelerate forward - speed 255 to 100");
    uint8_t resDeccF = motorDriverL9110.decelerateForward(255, 100, 50);
    if (resDeccF != 0) {
      Serial.println("Erreur decelerate forward - speed 255 to 100");
    }
    delay(10000);
    motorDriverL9110.stopMotor();
    delay(100);

    // accelerate backward - speed 100 to 255
    Serial.println("Accelerate backward - speed 100 to 255");
    uint8_t resAccB = motorDriverL9110.accelerateBackward(100, 255, 50);
    if (resAccB != 0) {
      Serial.println("Erreur acccelerate backward - speed 100 to 255");
    }
    delay(10000);

    // decelerate backward - speed 255 to 100
    Serial.println("Deccelerate backward - speed 255 to 100");
    uint8_t resDeccB = motorDriverL9110.decelerateBackward(255, 100, 50);
    if (resDeccB != 0) {
      Serial.println("Erreur decelerate backward - speed 255 to 100");
    }
    delay(10000);
    motorDriverL9110.stopMotor();
    delay(300);

    // turn right
    Serial.println("Turn right - speed 100");
    uint8_t resTR = motorDriverL9110.turnRight(100);
    if (resTR == 0) {
      delay(5000);
      motorDriverL9110.stopMotor();
      delay(300);
    } else {
      Serial.println(F("Erreur turn right !"));
    }


    // turn left
    Serial.println("Turn left - speed 100");
    uint8_t resTL = motorDriverL9110.turnLeft(100);
    if (resTL == 0) {
      delay(5000);
      motorDriverL9110.stopMotor();
      delay(100);
    } else {
      Serial.println(F("Erreur turn left !"));
    }


    Serial.println("Stop tests");
    start_test = false;
  }
}
