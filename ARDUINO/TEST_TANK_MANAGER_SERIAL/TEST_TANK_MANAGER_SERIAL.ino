/*
  Jocelyn GIROD
  05/06/2024

  Programme de test du TankManager avec les trames sur la liaison série.
  Arduino - Raspberry
*/

#include "Lcd216Driver.h"
#include "FrameManager.h"
#include "TankManager.h"

const uint8_t RX_PIN = 0;
const uint8_t TX_PIN = 2;

const uint8_t A1A = 5;   // pin PWM
const uint8_t A1B = 6;   // pin PWM
const uint8_t B1A = 9;   // pin PWM
const uint8_t B1B = 10;  // pin PWM

bool start_test = true;

TankManager tankManager = TankManager(nullptr, A1A, A1B, B1A, B1B);
Lcd216Driver lcd216Driver(RX_PIN, TX_PIN);
FrameManager frameManager;
bool frameReceived = false;

int speed = 100;

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

  pinMode(A1A, OUTPUT);
  pinMode(A1B, OUTPUT);
  pinMode(B1A, OUTPUT);
  pinMode(B1B, OUTPUT);
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
      Serial.println(F("Trame true"));
      frameReceived = true;
    }
  }

  if (frameReceived) {
    frameReceived = false;

    frameManager.setFrame(frame.c_str(), frame.length());
    char device = frameManager.getDevice();
    Serial.println(device);

    if (device == 'T') {
      manageTankDevice(frame);
    } else if (device == 'A') {
      manageArmDevice(frame);
    } else if (device == 'C') {
      manageCameraDevice(frame);
    } else {
      Serial.println(F("Unknown device"));
    }
  }
}

/**
  Stop tank
*/
void stopTank() {
  Serial.println(F("interrupt: stop"));
  //tankManager.stopAccelerationDeceleration();
  tankManager.stopTank();
}

/**
  Manage Tank device
*/
void manageTankDevice(String frame) {
  lcd216Driver.clearScreen();
  lcd216Driver.setCursorPosition(1, 1);
  // Red backlight color R:204, G:0, B:0
  lcd216Driver.setbacklightColor(204, 0, 0);
  lcd216Driver.writeMessage(frame);

  char function = frameManager.getFunction();
  Serial.println(function);

  if (function == 'F') {
    Serial.println(F("Tank forward"));
    uint8_t resF = tankManager.goForward(speed);
    if (resF != 0) {
      Serial.println(F("Erreur forward"));
    }
  } else if (function == 'B') {
    Serial.println(F("Tank backward"));
    uint8_t resB = tankManager.goBackward(speed);
    if (resB != 0) {
      Serial.println(F("Erreur backward"));
    }
  } else if (function == 'L') {
    Serial.println(F("Turn left"));
    uint8_t resTL = tankManager.turnLeft(speed);
    if (resTL != 0) {
      Serial.println(F("Erreur turn left"));
    }
  } else if (function == 'R') {
    Serial.println(F("Turn right"));
    uint8_t resTR = tankManager.turnRight(speed);
    if (resTR != 0) {
      Serial.println(F("Erreur turn right"));
    }
  } else if (function == 'A') {
    char functionValue = frameManager.getFunctionValue();
    if (functionValue == 'F') {
      Serial.println(F("Accelerate forward - speed 0 to 255"));
      uint8_t resAccF = tankManager.accelerateForward(0, 255, 2);
      if (resAccF != 0) {
        Serial.println(F("Erreur accelerate forward - speed 100 to 255"));
      }
    } else if (functionValue == 'B') {
      Serial.println(F("Accelerate backward - speed 0 to 255"));
      uint8_t resAccB = tankManager.accelerateBackward(0, 255, 2);
      if (resAccB != 0) {
        Serial.println(F("Erreur accelerate backward - speed 0 to 255"));
      }
    }
  } else if (function == 'D') {
    char functionValue = frameManager.getFunctionValue();
    if (functionValue == 'F') {
      Serial.println(F("Deccelerate forward - speed 255 to 0"));
      uint8_t resDeccF = tankManager.decelerateForward(255, 0, 2);
      if (resDeccF != 0) {
        Serial.println(F("Erreur deccelerate forward - speed 255 to 0"));
      }
    } else if (functionValue == 'B') {
      Serial.println(F("Deccelerate backward - speed 0 to 255"));
      uint8_t resDeccB = tankManager.decelerateBackward(255, 0, 2);
      if (resDeccB != 0) {
        Serial.println(F("Erreur deccelerate backward - speed 255 to 0"));
      }
    }
  } else if (function == 'S') {
    char functionValue = frameManager.getFunctionValue();
    if (functionValue == '+') {
      Serial.println(F("Increase speed"));
      speed = speed + 10;
    } else if (functionValue == '-') {
      Serial.println(F("Decrease speed"));
      speed = speed - 10;
    }
  } else {
    Serial.println(F("Unknown function"));
  }
}

/**
  Manage Arm device
*/
void manageArmDevice(String frame) {
  lcd216Driver.clearScreen();
  lcd216Driver.setCursorPosition(1, 1);
  // Blue backlight color R:0, G:102, B:0
  lcd216Driver.setbacklightColor(0, 102, 204);
  lcd216Driver.writeMessage(frame);
}

/**
  Manage Camera device
*/
void manageCameraDevice(String frame) {
  lcd216Driver.clearScreen();
  lcd216Driver.setCursorPosition(1, 1);
  // Green backlight color R:0, G:153, B:0
  lcd216Driver.setbacklightColor(0, 153, 0);
  lcd216Driver.writeMessage(frame);
}
