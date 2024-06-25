/*
  Jocelyn GIROD
  23/01/2024

  Programme de test de la liaison série et des moteurs du robot
  Arduino - Raspberry
*/

#include "Lcd216Driver.h"
#include "FrameManager.h"
#include "MotorDriverL9110.h"
#include "Logger.h"

const uint8_t RX_PIN = 0;
const uint8_t TX_PIN = 1;

const uint8_t A1A = 5;   // pin PWM
const uint8_t A1B = 9;   // pin PWM
const uint8_t B1A = 10;  // pin PWM
const uint8_t B1B = 11;  // pin PWM
const uint8_t SC_PIN = 4;

Lcd216Driver lcd216Driver{RX_PIN, TX_PIN};
FrameManager frameManager{};
Logger logger{String("drvL9110.txt")};
MotorDriverL9110 motorDriverL9110{A1A, A1B, B1A, B1B, &logger};
bool frameReceived = false;
uint8_t resInitLog = 0;

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

      char subdevice = frameManager.getSubDevice();
      switch (subdevice) {
        case 'F':
          motorDriverL9110.accelerateForward(0, 255, 2);
          break;
        case 'B':
          motorDriverL9110.accelerateBackward(0, 255, 2);
          break;
        case 'L':
          motorDriverL9110.turnLeft(100);
          break;
        case 'R':
          motorDriverL9110.turnRight(100);
          break;
        default:
          Serial.println(F("Unknown subdevice"));
      }
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
  Serial.println(F("stop"));
  motorDriverL9110.stopMotorAccelerationDeceleration();
}
