/*
  Jocelyn GIROD
  02/08/2023

  Programme de test du PCA9685
  sans le driver ServoDriverPCA9685.
*/

#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

#define SERVOMIN 100  // La longueur d'impulsion 'minimale' (valeur du compteur, max 4096)
#define SERVOMAX 650  // La longueur d'impulsion 'maximale' (valeur du compteur, max 4096)

uint8_t servo_14 = 14;
uint8_t servo_15 = 15;

bool initBreakout;
bool start_test = true;

void setup() {

  Serial.begin(19200);
  Serial.println("Controle des Servo Moteur #14 et #15");

  initBreakout = pwm.begin();
  if (initBreakout) {
    pwm.setPWMFreq(60);  // Les servo sont mis-à-jour à ~60 Hz
  } else {
    Serial.println("Erreur d'initialisation du breakout.");
  }
}

void loop() {

  if (initBreakout && start_test) {


    Serial.println("Servo #14 à 180 degrés");
    // Transformation de degré (0 à 180) en pulse (SERVOMIN à SERVOMAX)
    int pulseLen = map(180, 0, 180, SERVOMIN, SERVOMAX);
    pwm.setPWM(servo_14, 0, pulseLen);

    delay(5000);

    Serial.println("Servo #15 à 180 degrés");
    // Transformation de degré (0 à 180) en pulse (SERVOMIN à SERVOMAX)
    pulseLen = map(180, 0, 180, SERVOMIN, SERVOMAX);
    pwm.setPWM(servo_15, 0, pulseLen);

    delay(5000);

    pulseLen = map(0, 0, 180, SERVOMIN, SERVOMAX);
    pwm.setPWM(servo_14, 0, pulseLen);
    pwm.setPWM(servo_15, 0, pulseLen);

    //--- Controle du Premier Servo (no 14) ---
    // Serial.println("Servo #14 à 45 degrés");
    // // Transformation de degré (0 à 180) en pulse (SERVOMIN à SERVOMAX)
    // int pulseLen = map(45, 0, 180, SERVOMIN, SERVOMAX);
    // pwm.setPWM(servo_14, 0, pulseLen);

    // delay(1000);

    //--- Controle du Deuxieme Servo (no 15) ---
    // Serial.println("Servo #15 à 30 degrés");
    // pulseLen = map(30, 0, 180, SERVOMIN, SERVOMAX);
    // pwm.setPWM(servo_15, 0, pulseLen);

    // delay(1000);

    //--- Controle du Premier Servo (no 14) ---
    // Serial.println("Servo #14 à 120 degrés");
    // // Transformation de degré (0 à 180) en pulse (SERVOMIN à SERVOMAX)
    // pulseLen = map(120, 0, 180, SERVOMIN, SERVOMAX);
    // pwm.setPWM(servo_14, 0, pulseLen);

    // delay(1000);

    //--- Controle du Deuxieme Servo (no 15) ---
    // Serial.println("Servo #15 à 150 degrés");
    // pulseLen = map(150, 0, 180, SERVOMIN, SERVOMAX);
    // pwm.setPWM(servo_15, 0, pulseLen);

    // delay(1000);

    //--- Les deux servo à 0 ---
    // Serial.println("Servo #14 et #15 à 150 degrés");
    // pulseLen = map(0, 0, 180, SERVOMIN, SERVOMAX);
    // pwm.setPWM(servo_14, 0, pulseLen);
    //pwm.setPWM(servo_15, 0, pulseLen);

    //delay(3000);

    start_test = false;
  }
}
