/*
  Jocelyn GIROD
  19/06/2024

  Programme de tests su mini servo SG90 avec la librairie ServoDriverPCA9685.
*/

#include "Adafruit_PWMServoDriver.h"
#include "ServoDriverPCA9685.h"

#define SERVO_7 7
#define SERVO_8 8
#define MAX_DEGREES 180.0

long SERVOMIN_SG90 = 166.0;
long SERVOMAX_SG90 = 673.0;
float frequence = 60.0;
bool start_test = false;
uint8_t num_servo = 0;
ServoDriverPCA9685 servoDriverPCA9685{0x40, frequence, 27000000};
bool initBreakout = false;
float curentServosDegrees[2] = {};
float degrees_ = 0.0;
int interval = 3;

void setup() {
  Serial.begin(19200);

  initBreakout = servoDriverPCA9685.initDriver();
  if (!initBreakout) {
    Serial.println(F("Erreur d'initialisation du breakout."));
  }
}

void loop() {

  // Lecture des commandes sur le port série.
  // On attend plusieurs types de commandes:
  // - S7, S8 pour définir le numéro du servo.
  // - TRUE/FALSE, qui permet d'activer ou non le test.
  String command = "";
  if (Serial.available() > 0) {
    command = Serial.readString();
    command.trim();
    command.toUpperCase();
    Serial.print(F("Commande reçue: "));
    Serial.println(command);
  }

  extractEntryData(command);

  if (start_test && initBreakout) {
    switch (num_servo) {
      case 7:
        move_servo_7(degrees_);
        break;
      case 8:
        move_servo_8(degrees_);
        break;
      default: break;
    }
    start_test = false;
  }
}

/**
  Extrait les données lues sur l'entrée série
*/
void extractEntryData(String command) {

  if (command == "TRUE") {
    start_test = true;
  } else if (command == "S7") {
    num_servo = SERVO_7;
  } else if (command == "S8") {
    num_servo = SERVO_8;
  } else if (command.charAt(0) == 'D') {
    String degreesStr = command.substring(2, command.length());
    Serial.print(F("Valeur des degrés: "));
    Serial.println(degreesStr);
    degrees_ = degreesStr.toFloat();
  } else {
    if (command != "") {
      Serial.println(F("Commande non reconnue !"));
    }
  }
}


/**
  Mouvement servo 7
*/
void move_servo_7(float degrees) {

  Serial.println(F("Mouvement servo 7\n"));

  float currentDegrees = curentServosDegrees[0];
  if (degrees > currentDegrees) {
    // sens +
    for (float deg = currentDegrees; deg <= degrees; deg++) {
      servoDriverPCA9685.setDegreesWithPWM(SERVO_7, deg, MAX_DEGREES, SERVOMIN_SG90, SERVOMAX_SG90, true);
      delay(interval);
    }
  } else if (degrees < currentDegrees) {
    // sens -
    for (float deg = currentDegrees; deg >= degrees; deg--) {
      servoDriverPCA9685.setDegreesWithPWM(SERVO_7, deg, MAX_DEGREES, SERVOMIN_SG90, SERVOMAX_SG90, true);
      delay(interval);
    }
  }
  curentServosDegrees[0] = servoDriverPCA9685.getCurrentDegreesWithPWM(SERVO_7, MAX_DEGREES, SERVOMIN_SG90, SERVOMAX_SG90);
}

/**
  Mouvement servo 8
*/
void move_servo_8(float degrees) {

  Serial.println(F("Mouvement servo 8\n"));

  float currentDegrees = curentServosDegrees[1];
  if (degrees > currentDegrees) {
    // sens +
    for (float deg = currentDegrees; deg <= degrees; deg++) {
      servoDriverPCA9685.setDegreesWithPWM(SERVO_8, deg, MAX_DEGREES, SERVOMIN_SG90, SERVOMAX_SG90, true);
      delay(interval);
    }
  } else if (degrees < currentDegrees) {
    // sens -
    for (float deg = currentDegrees; deg >= degrees; deg--) {
      servoDriverPCA9685.setDegreesWithPWM(SERVO_8, deg, MAX_DEGREES, SERVOMIN_SG90, SERVOMAX_SG90, true);
      delay(interval);
    }
  }
  curentServosDegrees[0] = servoDriverPCA9685.getCurrentDegreesWithPWM(SERVO_8, MAX_DEGREES, SERVOMIN_SG90, SERVOMAX_SG90);
}
