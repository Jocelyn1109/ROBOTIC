/*
  Jocelyn GIROD
  02/08/2023

  Programme de test du PCA9685
  sans le driver ServoDriverPCA9685.
*/

#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

// Suivant le type de servo utilisé, la largeur d'impulsion minimale et Maximale
// peut changer. L'idéal est de sélectionner des valeurs aussi petites et aussi
// grande que possible sans jamais atteindre la butée de blocage du servo-moteur.
// Mmodifier ces valeurs pour les faire correspondrent au type de servo.
// Min et Max pour servo MG996R
#define SERVOMIN 177          // La longueur d'impulsion 'minimale' (valeur du compteur, max 4096)
#define SERVOMAX 673          // La longueur d'impulsion 'maximale' (valeur du compteur, max 4096)

uint8_t servo_1 = 1;

bool initBreakout;
bool start_test = true;

void setup() {

  Serial.begin(19200);

  initBreakout = pwm.begin();
  if (initBreakout) {
    pwm.setPWMFreq(SERVO_FREQ);  // servo sont mis-à-jour à ~50 Hz pour MG996R.
    pwm.setOscillatorFrequency(27000000);
  } else {
    Serial.println(F("Erreur d'initialisation du breakout."));
  }

  delay(10);
}

void loop() {

  if (initBreakout && start_test) {


    // for (uint16_t pulselen = SERVOMAX; pulselen > SERVOMIN; pulselen--) {
    //   String pulse_0 = F("Pulse: ");
    //   pulse_0.concat(pulselen);
    //   Serial.println(pulse_0);
    //   pwm.setPWM(servo_0, 0, pulselen);
    // }

    // delay(500);

    // for (uint16_t pulselen = SERVOMAX; pulselen > SERVOMIN; pulselen--) {
    //   String pulse_0 = F("Pulse: ");
    //   pulse_0.concat(pulselen);
    //   Serial.println(pulse_0);
    //   pwm.setPWM(servo_1, 0, pulselen);
    // }


    //pwm.setPWM(servo_1, 0, 1500);

    //O°
    Serial.println(F("Servo 1 à 0 degré"));
    int pulseLen = map(0, 0, 270, SERVOMIN_DS3225, SERVOMAX_DS3225);
    String pulse_0 = F("Pulse pour 0 degré: ");
    pulse_0.concat(pulseLen);
    Serial.println(pulse_0);
    //pwm.setPWM(servo_1, 0, pulseLen);
    pwm.setPWM(servo_1, 0, 500);

    delay(10000);

    //Neutre (180°)
    Serial.println(F("Servo 1 à 135 degré"));
    pulseLen = map(135, 0, 270, SERVOMIN_DS3225, SERVOMAX_DS3225);
    String pulse_135 = F("Pulse pour 135 degré: ");
    pulse_135.concat(pulseLen);
    Serial.println(pulse_135);
    //pwm.setPWM(servo_1, 0, pulseLen);
    pwm.setPWM(servo_1, 0, 1500);

    delay(10000);

    // 270°
    Serial.println(F("Servo 1 à 270 degré"));
    pulseLen = map(270, 0, 270, SERVOMIN_DS3225, SERVOMAX_DS3225);
    String pulse_270 = F("Pulse pour 270 degré: ");
    pulse_270.concat(pulseLen);
    Serial.println(pulse_270);
    //pwm.setPWM(servo_1, 0, pulseLen);
    pwm.setPWM(servo_1, 0, 2500);


    // Serial.println(F("Servo 0 à 180 degré"));
    // int pulseLen = map(180, 0, 180, SERVOMIN, SERVOMAX);
    // String pulse_0 = F("Pulse pour 0 degré: ");
    // pulse_0.concat(pulseLen);
    // Serial.println(pulse_0);
    // pwm.setPWM(servo_0, 0, pulseLen);
    // delay(1000);
    // pwm.setPWM(servo_14, 0, pulseLen);
    // delay(1000);
    // pwm.setPWM(servo_15, 0, pulseLen);



    // Serial.println(F("Servo 14 à 45 degrés"));
    // pulseLen = map(45, 0, 180, SERVOMIN, SERVOMAX);
    // String pulse_45 = F("Pulse pour 45 degrés: ");
    // pulse_45.concat(pulseLen);
    // Serial.println(pulse_45);
    // pwm.setPWM(servo_14, 0, pulseLen);

    // delay(3000);

    // Serial.println(F("Servo 14 à 90 degrés"));
    // pulseLen = map(90, 0, 180, SERVOMIN, SERVOMAX);
    // String pulse_90 = F("Pulse pour 90 degrés: ");
    // pulse_90.concat(pulseLen);
    // Serial.println(pulse_90);
    // pwm.setPWM(servo_14, 0, pulseLen);

    // delay(3000);

    // Serial.println(F("Servo 14 à 135 degrés"));
    // pulseLen = map(135, 0, 180, SERVOMIN, SERVOMAX);
    // String pulse_135 = F("Pulse pour 135 degrés: ");
    // pulse_135.concat(pulseLen);
    // Serial.println(pulse_135);
    // pwm.setPWM(servo_14, 0, pulseLen);

    // delay(3000);

    // Serial.println(F("Servo 14/15 à 180 degrés"));
    // pulseLen = map(180, 0, 180, SERVOMIN, SERVOMAX);
    // String pulse_180 = F("Pulse pour 90 degrés: ");
    // pulse_180.concat(pulseLen);
    // Serial.println(pulse_180);
    // pwm.setPWM(servo_13, 0, pulseLen);
    // delay(1000);
    // pwm.setPWM(servo_14, 0, pulseLen);
    // delay(1000);
    // pwm.setPWM(servo_15, 0, pulseLen);


    // delay(1000);

    // Serial.println(F("Servo 14/15 à 0 degré"));
    // pulseLen = map(0, 0, 180, SERVOMIN, SERVOMAX);
    // pulse_0 = F("Pulse pour 0 degré: ");
    // pulse_0.concat(pulseLen);
    // Serial.println(pulse_0);
    // pwm.setPWM(servo_13, 0, pulseLen);
    // delay(1000);
    // pwm.setPWM(servo_14, 0, pulseLen);
    // delay(1000);
    // pwm.setPWM(servo_15, 0, pulseLen);


    start_test = false;
  }
}
