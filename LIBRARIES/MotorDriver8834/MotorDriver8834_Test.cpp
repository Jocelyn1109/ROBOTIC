#include <Arduino.h>
#include "MotorDriver8834.h"

MotorDriver8834 motorDriver8834;

const uint8_t DIR_PIN = 2;
const uint8_t STEP_PIN = 3;
const uint8_t SLEEP_PIN = 4;
const uint8_t M0_PIN = 5;
const uint8_t M1_PIN = 6;

bool start_test = true;

void setup() {
    motorDriver8834.initPins(STEP_PIN, DIR_PIN, SLEEP_PIN, M0_PIN, M1_PIN);
}

void loop() {

    if(start_test){

        motorDriver8834.goForward(50,15);
        delay(500);
        motorDriver8834.goBackward(50,15);

        start_test = false;
    }
}
