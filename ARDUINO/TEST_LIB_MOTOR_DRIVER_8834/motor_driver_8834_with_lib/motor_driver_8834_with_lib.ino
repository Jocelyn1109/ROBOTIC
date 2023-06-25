/*
  Jocelyn GIROD
  16/06/2023

  Programme de test de la librairie MotorDriver8834:
  - initPins,
  - enableDriver,
  - defineMicrostepResolution,
  - goForward,
  - goBackward.
*/

#include "MotorDriver8834.h"
#include "Logger.h"

Logger logger(String("drv8834.txt"));
MotorDriver8834 motorDriver8834(&logger);

const uint8_t DIR_PIN = 7;
const uint8_t STEP_PIN = 8;
const uint8_t SLEEP_PIN = 4;
const uint8_t M0_PIN = 9;
const uint8_t M1_PIN = 10;
const uint8_t SC_PIN = 2;

uint8_t resInitDrv = 0;
uint8_t resInitLog = 0;
bool start_test = true;

void setup() {

  // Initialisation du terminal serie
  Serial.begin(19200);

  //Initialisation du logger
  resInitLog = logger.loggerInitialization(SC_PIN);
  if (resInitLog == 1) {
    Serial.println(F("Erreur lors de l'initialisation du logger"));
  } else {
    Serial.println(F("Succès de l'initialisation du logger"));
  }

  // Initialisation du driver
  motorDriver8834.initPins(STEP_PIN, DIR_PIN, SLEEP_PIN, M0_PIN, M1_PIN);
  resInitDrv = motorDriver8834.enableDriver();

  if (resInitDrv == 1) {
    Serial.write("Erreur lors de l'initialisation du driver\n");
  } else {
    Serial.write("Succès de l'initialisation du driver\n");
  }
}

void loop() {

  if (resInitDrv == 0 && resInitLog == 0 && start_test) {
    int nbPas = 3000;
    int delais = 1;
    uint8_t resInitMicroSteps = 0;
    Serial.write("Début du test\n");

    // FULL STEP
    Serial.write("FULL STEP\n");
    resInitMicroSteps = motorDriver8834.defineMicrostepResolution(microstep_resolution::FULL_STEP);
    if (resInitMicroSteps == 0) {
      uint8_t resGF = motorDriver8834.goForward(nbPas, delais);
      if (resGF == 1) {
        Serial.write("Erreur goforward !\n");
      }
      delay(2000);
      motorDriver8834.goBackward(nbPas, delais);
      delay(2000);
    }

    // HALF STEP
    Serial.write("HALF STEP\n");
    resInitMicroSteps = motorDriver8834.defineMicrostepResolution(microstep_resolution::HALF_STEP);
    if (resInitMicroSteps == 0) {
      motorDriver8834.goForward(nbPas, delais);
      delay(2000);
      motorDriver8834.goBackward(nbPas, delais);
      delay(2000);
    }

    // 1/4 STEP
    Serial.write("1/4 STEP\n");
    resInitMicroSteps = motorDriver8834.defineMicrostepResolution(microstep_resolution::ONE_FOUR_STEP);
    if (resInitMicroSteps == 0) {
      motorDriver8834.goForward(nbPas, delais);
      delay(2000);
      motorDriver8834.goBackward(nbPas, delais);
      delay(2000);
    }

    // 1/8 STEP
    Serial.write("1/8 STEP\n");
    resInitMicroSteps = motorDriver8834.defineMicrostepResolution(microstep_resolution::ONE_HEIGHT_STEP);
    if (resInitMicroSteps == 0) {
      motorDriver8834.goForward(nbPas, delais);
      delay(2000);
      motorDriver8834.goBackward(nbPas, delais);
      delay(2000);
    }

    // 1/16 STEP
    Serial.write("1/16 STEP\n");
    resInitMicroSteps = motorDriver8834.defineMicrostepResolution(microstep_resolution::ONE_SIXTEEN_STEP);
    if (resInitMicroSteps == 0) {
      motorDriver8834.goForward(nbPas, delais);
      delay(2000);
      motorDriver8834.goBackward(nbPas, delais);
      delay(2000);
    }

    // 1/32
    Serial.write("1/32 STEP\n");
    resInitMicroSteps = motorDriver8834.defineMicrostepResolution(microstep_resolution::ONE_THIRTY_TWO_STEP);
    if (resInitMicroSteps == 0) {
      motorDriver8834.goForward(nbPas, delais);
      delay(2000);
      motorDriver8834.goBackward(nbPas, delais);
      delay(2000);
    }

    Serial.write("Fin du test\n");
    start_test = false;
  }
}
