/*
  Jocelyn GIROD
  22/11/2023

  Programme de tests de la librairie ServoDriverPCA9685.

*/

#include "ServoDriverPCA9685.h"

#define SERVO_1 1
#define SERVO_2 2
#define SERVO_3 3
#define SERVO_4 4
#define SERVO_5 5
#define SERVO_6 6

#define MAX_DEGREES 270.0

long SERVOMIN_DS3225 = 166.0;
long SERVOMAX_DS3225 = 673.0;

// servo 1 currentServosDegrees[0]
// servo 2 currentServosDegrees[1]
// servo 3 currentServosDegrees[2]
// servo 4 currentServosDegrees[3]
// servo 5 currentServosDegrees[4]
// servo 6 currentServosDegrees[5]
float curentServosDegrees[6] = {};

bool start_test = false;
float degrees_ = 0.0;
uint8_t num_servo = 0;
int interval = 3;

ServoDriverPCA9685 servoDriverPCA9685(0x40, 50.0, 27000000);
bool initBreakout = false;

void setup() {

  Serial.begin(19200);

  initBreakout = servoDriverPCA9685.initDriver();

  if (initBreakout) {
    Serial.println(F("Init arm"));
    initArm();
  } else {
    Serial.println(F("Erreur d'initialisation du breakout."));
  }
}

void loop() {

  // Lecture des commandes sur le port série.
  // On attend plusieurs types de commandes:
  // - S1, S2,....S6 pour définir le numéro du servo.
  // - TRUE/FALSE, qui permet d'activer ou non le test.
  // - INIT, permet d'initialiser le bras.
  // - I permet de définir l'interval (vitesse de rotation du servo).
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
  }
}

/**
  Extrait les données lues sur l'entrée série
*/
void extractEntryData(String command) {

  if (command == "TRUE") {
    start_test = true;
  } else if (command == "S1") {
    num_servo = SERVO_1;
  } else if (command == "S2") {
    num_servo = SERVO_2;
  } else if (command == "S3") {
    num_servo = SERVO_3;
  } else if (command == "S4") {
    num_servo = SERVO_4;
  } else if (command == "S5") {
    num_servo = SERVO_5;
  } else if (command == "S6") {
    num_servo = SERVO_6;
  } else if (command == "INIT") {
    initArm();
  } else if (command == "SLEEP") {
    //TODO
  } else if (command == "WAKEUP") {
    //TODO
  } else if (command.charAt(0) == 'D') {
    String degreesStr = command.substring(2, command.length());
    Serial.print(F("Valeur des degrés: "));
    Serial.println(degreesStr);
    degrees_ = degreesStr.toFloat();
  } else if (command.charAt(0) == 'I') {
    String intervalStr = command.substring(2, command.length());
    Serial.print(F("Valeur de l'interval: "));
    Serial.println(intervalStr);
    interval = intervalStr.toInt();
  } else {
    if (command != "") {
      Serial.println(F("Commande non reconnue !"));
    }
  }
}

/**
  Permet d'initialiser la position du bras.
  Le servo 1 doit avoir un débatement de 66°<-->200°, un neutre à 133° et une position initiale de 133°.
  Le servo 2 doit avoir un débatement de 125°<-->270°, un neutre à 145° et une position initiale de 270°.
  Le servo 3 doit avoir un débatement de 40°<-->220°, un neutre à 133° et une position initiale de 40°.
  Le servo 4 doit avoir un débatement de 133°<-->270°, un neutre à 133° et une position initiale de 270°.
  Le servo 5 doit avoir un débatement de 10°<-->210°, un neutre à 125° et une position initiale de 125°.
  Le servo 6 doit avoir un débatement de 120°<-->220°, un neutre à 120° et une position initiale de 120°.
*/
void initArm() {

  servoDriverPCA9685.setPWMOutput(SERVO_1, 0, 0);
  servoDriverPCA9685.setPWMOutput(SERVO_2, 0, 0);
  servoDriverPCA9685.setPWMOutput(SERVO_3, 0, 0);
  servoDriverPCA9685.setPWMOutput(SERVO_4, 0, 0);
  servoDriverPCA9685.setPWMOutput(SERVO_5, 0, 0);
  servoDriverPCA9685.setPWMOutput(SERVO_6, 0, 0);

  servoDriverPCA9685.setDegrees(SERVO_1, 133.0, 270.0, SERVOMIN_DS3225, SERVOMAX_DS3225, true);
  curentServosDegrees[0] = servoDriverPCA9685.getCurrentDegrees(SERVO_1, MAX_DEGREES, SERVOMIN_DS3225, SERVOMAX_DS3225);
  delay(100);

  servoDriverPCA9685.setDegrees(SERVO_2, 270.0, 270.0, SERVOMIN_DS3225, SERVOMAX_DS3225, true);
  curentServosDegrees[1] = servoDriverPCA9685.getCurrentDegrees(SERVO_2, MAX_DEGREES, SERVOMIN_DS3225, SERVOMAX_DS3225);
  delay(100);

  servoDriverPCA9685.setDegrees(SERVO_3, 40.0, 270.0, SERVOMIN_DS3225, SERVOMAX_DS3225, true);
  curentServosDegrees[2] = servoDriverPCA9685.getCurrentDegrees(SERVO_3, MAX_DEGREES, SERVOMIN_DS3225, SERVOMAX_DS3225);
  delay(100);

  servoDriverPCA9685.setDegrees(SERVO_4, 270.0, 270.0, SERVOMIN_DS3225, SERVOMAX_DS3225, true);
  curentServosDegrees[3] = servoDriverPCA9685.getCurrentDegrees(SERVO_4, MAX_DEGREES, SERVOMIN_DS3225, SERVOMAX_DS3225);
  delay(100);

  servoDriverPCA9685.setDegrees(SERVO_5, 125.0, 270.0, SERVOMIN_DS3225, SERVOMAX_DS3225, true);
  curentServosDegrees[4] = servoDriverPCA9685.getCurrentDegrees(SERVO_5, MAX_DEGREES, SERVOMIN_DS3225, SERVOMAX_DS3225);
  delay(100);

  servoDriverPCA9685.setDegrees(SERVO_6, 120.0, 270.0, SERVOMIN_DS3225, SERVOMAX_DS3225, true);
  curentServosDegrees[5] = servoDriverPCA9685.getCurrentDegrees(SERVO_6, MAX_DEGREES, SERVOMIN_DS3225, SERVOMAX_DS3225);
  delay(100);
}
