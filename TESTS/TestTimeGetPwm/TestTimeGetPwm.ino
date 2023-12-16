/*
  Jocelyn GIROD
  20/10/2023

  Test le temps d'exécution du getPWM
*/

#include <Adafruit_PWMServoDriver.h>

long SERVOMIN_DS3225 = 166.0;
long SERVOMAX_DS3225 = 673.0;
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

float freq = 60;
uint8_t num_servo = 1;
bool initBreakout = false;
bool start_test = false;
unsigned long startTime;
unsigned long endTime;

void setup() {

  Serial.begin(19200);

  initBreakout = pwm.begin();

  if (initBreakout) {
    pwm.setPWMFreq(freq);  // au démarrage on initialise la fréquence du servo avec une valeur par défaut.
    pwm.setOscillatorFrequency(27000000);
    pwm.setPWM(num_servo, 0, 0);
    float pulseLen = map(270.0, 0.0, 270.0, SERVOMIN_DS3225, SERVOMAX_DS3225);
    pwm.setPWM(num_servo, 0, pulseLen);
    delay(100);
  } else {
    Serial.println(F("Erreur d'initialisation du breakout."));
  }
}

void loop() {

  // Lecture des commandes sur le port série.
  String command = "";
  if (Serial.available() > 0) {
    command = Serial.readString();
    command.trim();
    command.toUpperCase();
    if (command == "TRUE") {
      start_test = true;
    }
  }

  if (start_test) {
    startTime = micros();
    uint16_t currentPWM = pwm.getPWM(num_servo, true);
    endTime = micros();
    unsigned long timeDuration = endTime - startTime;
    Serial.print(F("Time duration: "));
    Serial.println(timeDuration);

    Serial.print(F("Current PWM: "));
    Serial.println(currentPWM);
    start_test = false;

    float pulseLen = map(0.0, 0.0, 270.0, SERVOMIN_DS3225, SERVOMAX_DS3225);
    pwm.setPWM(num_servo, 0, pulseLen);
    delay(100);
  }

}
