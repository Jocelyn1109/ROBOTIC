/*
  Jocelyn GIROD
  30/06/2023

  Programme de test multi driver 
  MotorDriverL9910.
  Lcd216Driver
  Test avec le logger.
*/

#include "MotorDriverL9110.h"
#include "Logger.h"
#include "Lcd216Driver.h"

const uint8_t A1A = 3;   // pin PWM
const uint8_t A1B = 5;   // pin PWM
const uint8_t B1A = 9;   // pin PWM
const uint8_t B1B = 10;  // pin PWM
const uint8_t SC_PIN = 4;
const uint8_t RX_PIN = 0;
const uint8_t TX_PIN = 2;

uint8_t resInitLog = 0;
bool start_test = true;

Logger logger{String("drvL9110.txt")};
MotorDriverL9110 motorDriverL9110{A1A, A1B, B1A, B1B, &logger};
Lcd216Driver lcd216Driver{RX_PIN, TX_PIN};

void setup() {

  // Initialisation du terminal série
  Serial.begin(19200);

  lcd216Driver.autoScrollOff();
  lcd216Driver.setDefaultContrast();
  lcd216Driver.setDefaultColor();
  lcd216Driver.clearScreen();

  //Initialisation du logger
  resInitLog = logger.loggerInitialization(SC_PIN);
  if (resInitLog == 1) {
    String errorMessage(F("INIT LOG ERROR"));
    displayMessageOnLCD(errorMessage, 204, 0, 0);
  } else {
    String okMessage(F("INIT LOG SUCCESS"));
    displayMessageOnLCD(okMessage, 0, 153, 0);
  }

  pinMode(A1A, OUTPUT);
  pinMode(A1B, OUTPUT);
  pinMode(B1A, OUTPUT);
  pinMode(B1B, OUTPUT);
}

void loop() {

  if (start_test && resInitLog == 0) {

    Serial.println(F("Début du test"));
    lcd216Driver.clearScreen();

    String errorMessage(F(""));
    // go forward - speed 200
    String infoMessage(F("GF-SPD200"));
    displayMessageOnLCD(infoMessage, 0, 102, 204);
    uint8_t resGoF = motorDriverL9110.goForward(200);
    if (resGoF == 0) {
      delay(5000);
      motorDriverL9110.stopMotor();
      delay(100);
    } else {
      String errorMessage(F("GF ERROR"));
      displayMessageOnLCD(errorMessage, 204, 0, 0);
    }

    lcd216Driver.clearScreen();

    // go backward - speed 200
    infoMessage = F("GB-SPD200");
    displayMessageOnLCD(infoMessage, 0, 102, 204);
    uint8_t resGoB = motorDriverL9110.goBackward(200);
    if (resGoB == 0) {
      delay(5000);
      motorDriverL9110.stopMotor();
      delay(100);
    } else {
      errorMessage = F("GB ERROR");
      displayMessageOnLCD(errorMessage, 204, 0, 0);
    }

    lcd216Driver.clearScreen();

    // accelerate forward - speed 100 to 255
    infoMessage = F("AF->SPD255");
    displayMessageOnLCD(infoMessage, 0, 102, 204);
    uint8_t resAccF = motorDriverL9110.accelerateForward(100, 255, 20);
    if (resAccF != 0) {
      errorMessage = F("AF ERROR");
      displayMessageOnLCD(errorMessage, 204, 0, 0);
    }

    delay(10000);
    lcd216Driver.clearScreen();

    // decelerate forward - speed 255 to 100
    infoMessage = F("DF->SPD100");
    displayMessageOnLCD(infoMessage, 0, 102, 204);
    uint8_t resDeccF = motorDriverL9110.decelerateForward(255, 100, 50);
    if (resDeccF != 0) {
      errorMessage = F("DF ERROR");
      displayMessageOnLCD(errorMessage, 204, 0, 0);
    }

    delay(10000);
    motorDriverL9110.stopMotor();
    lcd216Driver.clearScreen();
    delay(100);

    // accelerate backward - speed 100 to 255
    infoMessage = F("AB->SPD255");
    displayMessageOnLCD(infoMessage, 0, 102, 204);
    uint8_t resAccB = motorDriverL9110.accelerateBackward(100, 255, 50);
    if (resAccB != 0) {
      errorMessage = F("AB ERROR");
      displayMessageOnLCD(errorMessage, 204, 0, 0);
    }

    delay(10000);
    lcd216Driver.clearScreen();

    // decelerate backward - speed 255 to 100
    infoMessage = F("DB->SPD100");
    displayMessageOnLCD(infoMessage, 0, 102, 204);
    uint8_t resDeccB = motorDriverL9110.decelerateBackward(255, 100, 50);
    if (resDeccB != 0) {
      errorMessage = F("DB ERROR");
      displayMessageOnLCD(errorMessage, 204, 0, 0);
    }

    delay(10000);
    motorDriverL9110.stopMotor();
    lcd216Driver.clearScreen();
    delay(300);

    // turn right
    infoMessage = F("TR->SPD100");
    displayMessageOnLCD(infoMessage, 0, 102, 204);
    uint8_t resTR = motorDriverL9110.turnRight(100);
    if (resTR == 0) {
      delay(5000);
      motorDriverL9110.stopMotor();
      delay(300);
    } else {
      errorMessage = F("TR ERROR");
      displayMessageOnLCD(errorMessage, 204, 0, 0);
    }

    lcd216Driver.clearScreen();

    // turn left
    infoMessage = F("TL->SPD100");
    displayMessageOnLCD(infoMessage, 0, 102, 204);
    uint8_t resTL = motorDriverL9110.turnLeft(100);
    if (resTL == 0) {
      delay(5000);
      motorDriverL9110.stopMotor();
      delay(100);
    } else {
      errorMessage = F("TL ERROR");
      displayMessageOnLCD(errorMessage, 204, 0, 0);
    }


    Serial.println(F("Stop tests"));
    start_test = false;

    lcd216Driver.clearScreen();
    infoMessage = F("TEST OK");
    displayMessageOnLCD(infoMessage, 0, 153, 0);
  }
}

void displayMessageOnLCD(String message, uint8_t red, uint8_t green, uint8_t blue) {
  lcd216Driver.setbacklightColor(red, green, blue);
  lcd216Driver.writeMessage(message);
}
