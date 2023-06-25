#include <Arduino.h>
#include "MotorDriver8834.h"

MotorDriver8834 motorDriver8834(NULL);

const uint8_t DIR_PIN = 7;
const uint8_t STEP_PIN = 8;
const uint8_t SLEEP_PIN = 4;
const uint8_t M0_PIN = 12;
const uint8_t M1_PIN = 13;

uint8_t resInit = 0;
bool start_test = true;


void setup() {

    // Initialisation du terminal serie
    Serial.begin(19200);

    // Initialisation du driver
    motorDriver8834.initPins(STEP_PIN, DIR_PIN, SLEEP_PIN, M0_PIN, M1_PIN);
    resInit = motorDriver8834.enableDriver();

    if (resInit == 1) {
        Serial.write("Erreur lors de l'initialisation du driver\n");
    } else {
        Serial.write("Succès de l'initialisation du driver\n");
    }
}

void loop() {

    if (resInit == 0 && start_test) {
        int nbPas = 3000;
        int delais = 1;
        uint8_t resInitMicroSteps = 0;
        Serial.write("Début du test\n");

        // FULL STEP
        Serial.write("FULL STEP\n");
        resInitMicroSteps = motorDriver8834.defineMicrostepResolution(microstep_resolution::FULL_STEP);
        if (resInitMicroSteps == 0) {
            motorDriver8834.goForward(nbPas, delais);
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
