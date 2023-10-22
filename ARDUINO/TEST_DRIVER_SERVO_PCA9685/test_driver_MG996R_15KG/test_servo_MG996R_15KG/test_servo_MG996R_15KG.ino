/*
  Jocelyn GIROD
  20/10/2023

  Programme de test du servo MG996R 15Kg.
  
  Spécifications électriques ：
  1) Vitesse de rotation: 0,17s / 60 degrés (4,8V sans charge)
  2) Vitesse de rotation: 0,13s / 60 degrés (6,0V sans charge)
  3) Couple: 13 kg.cm à 4,8V
  4) Couple de décrochage: 15 kg.cm à 6V
  5) Tension de fonctionnement: 4,8 - 7,2V
*/

#include <Adafruit_PWMServoDriver.h>

// Suivant le type de servo utilisé, la largeur d'impulsion minimale et Maximale
// peut changer. L'idéal est de sélectionner des valeurs aussi petites et aussi
// grande que possible sans jamais atteindre la butée de blocage du servo-moteur.
// Modifier ces valeurs pour les faire correspondrent au type de servo.

// Min et Max pour servo MG996R
uint16_t SERVOMIN_MG996R = 166;  // La longueur d'impulsion 'minimale' (valeur du compteur, max 4096)
uint16_t SERVOMAX_MG996R = 673;  // La longueur d'impulsion 'maximale' (valeur du compteur, max 4096)

#define SERVO_FREQ 60  // mis-à-jour à 60 Hz pour MG996R.

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
const uint8_t servo_0 = 0;
bool initBreakout = false;
bool start_test = false;
bool test1 = false;
bool test2 = false;
float degrees = 0.0;

void setup() {

  Serial.begin(19200);

  initBreakout = pwm.begin();

  if (initBreakout) {
    pwm.setPWMFreq(SERVO_FREQ);

    uint32_t defautlOscillatorFrequency = pwm.getOscillatorFrequency();
    String defautlOscillatorFrequencyMessage = F("Valeur par défaut de la fréquence de l'oscillateur: ");
    defautlOscillatorFrequencyMessage.concat(defautlOscillatorFrequency);
    Serial.println(defautlOscillatorFrequencyMessage);

    pwm.setOscillatorFrequency(27000000);

    //Servo au neutre
    neutral();

  } else {
    Serial.println(F("Erreur d'initialisation du breakout."));
  }

  delay(10);
}

void loop() {

  // Lecture des commandes sur le port série.
  // On attend deux types de commandes:
  // - TRUE/FALSE, qui permet d'activer ou non le test.
  // - T1 pour lancer le test 1 et T2 pour le 2.
  // - MAX:XXX, permet de spécifier la pulse max.
  // - MIN:XXX, permet de spécifier la pulse min.
  // - NEUTRE, permet de mettre le servo au neutre.
  // - D:XXX, permet de spécifier les degrés.
  String command = "";
  if (Serial.available() > 0) {
    command = Serial.readString();
    command.trim();
    command.toUpperCase();
    Serial.print(F("Commande reçue: "));
    Serial.println(command);
  }

  if (command == "TRUE") {
    start_test = true;
  } else if (command == "FALSE") {
    start_test = false;
  } else if (command == "T1") {
    test1 = true;
    test2 = false;
  } else if (command == "T2") {
    test2 = true;
    test1 = false;
  } else if (command.charAt(0) == 'M') {
    String minOrMax = command.substring(0, 3);
    String valueStr = command.substring(4, command.length());
    Serial.print(minOrMax);
    Serial.print(F(": "));
    Serial.println(valueStr);

    if (minOrMax == "MIN") {
      SERVOMIN_MG996R = valueStr.toInt();
    } else {
      SERVOMAX_MG996R = valueStr.toInt();
    }
  } else if (command.charAt(0) == 'D') {
    String degreesStr = command.substring(2, command.length());
    Serial.print(F("Valeur des degrés: "));
    Serial.println(degreesStr);
    degrees = degreesStr.toFloat();
  } else if (command == "NEUTRE") {
    neutral();
  } else {
    if (command != "") {
      Serial.println(F("Commande non reconnue !"));
    }
  }

  if (start_test && initBreakout) {

    Serial.print(F("Valeur de SERVOMIN_MG996R: "));
    Serial.println(SERVOMIN_MG996R);
    Serial.print(F("Valeur de SERVOMAX_MG996R: "));
    Serial.println(SERVOMAX_MG996R);

    if (test1) {
      Serial.println(F("TEST 1"));
      test_1();
    }

    if (test2) {
      Serial.println(F("TEST 2"));
      test_2();
    }

    start_test = false;
  }
}


void neutral() {
  Serial.println(F("Servo 0 à 90 degré"));
  int pulseLen = map(90, 0, 180, SERVOMIN_MG996R, SERVOMAX_MG996R);
  pwm.setPWM(servo_0, 0, pulseLen);
}

void test_1() {
  Serial.println(F("Servo à 0°"));
  int pulseLen = map(0, 0, 180, SERVOMIN_MG996R, SERVOMAX_MG996R);
  pwm.setPWM(servo_0, 0, pulseLen);
  delay(3000);

  Serial.println(F("Servo à 180°"));
  pulseLen = map(180, 0, 180, SERVOMIN_MG996R, SERVOMAX_MG996R);
  pwm.setPWM(servo_0, 0, pulseLen);
}

void test_2() {
  Serial.print(F("Servo à: "));
  Serial.print(degrees);
  Serial.println(F("°"));
  int pulseLen = map(degrees, 0, 180, SERVOMIN_MG996R, SERVOMAX_MG996R);
  pwm.setPWM(servo_0, 0, pulseLen);
  delay(3000);
}
