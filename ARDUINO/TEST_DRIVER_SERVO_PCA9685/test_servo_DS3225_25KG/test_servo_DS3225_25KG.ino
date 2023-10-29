/*
  Jocelyn GIROD
  20/10/2023

  Programme de test du servo DS3225 25Kg.

  Spécifications électriques ：
  1) Plage de tension de fonctionnement: 4,8 - 6,8 V
  2) Vitesse de fonctionnement (5,0 V): 0,15 sec / 60 degrés
  3) Vitesse de fonctionnement (6,8 V): 0,13 sec / 60 degrés
  4) Couple de décrochage (5.0V): 21kg / cm
  5) Couple de décrochage (6,8 V): 25 kg / cm

  Spécification de contrôle:
  1) Système de contrôle: PWM (modification de la largeur d'impulsion)
  2) Plage de largeur d'impulsion: 500 ~ 2500 μsec
  3) Position neutre: 1500μsec
  4) Degré de fonctionnement: 270 ° (lorsque 500 ~ 2500 μsec)
  5) Largeur de bande morte: 3 μsec
  6) Fréquence de fonctionnement: 50-330Hz
  7) Sens de rotation: sens antihoraire (lorsque 500 ~ 2500 μsec)

  Spécifications mécaniques:
  1) Rapport de démultiplication: 275
  2) Roulement: Double roulement
  3) Fil de connecteur: 17,7 pouces (450 mm)
  4) Moteur: 3 pôles
  5) Performance étanche: IP66
  6) Taille: 40 x 20 x 40,5 mm

*/

#include <Adafruit_PWMServoDriver.h>

/**
  Formule pour trouver la largeur d’impulsion correspondante sur 4096 (2^12, 12bits).
  Soit F la fréquence en Hz, T la période en secondes, pulseMin l'impulsion minimum en microsecondes spécifique au servo (donnée constructeur),
  pulseMax l'impulsion maximum en microsecondes spécifique au servo (donnée constructeur), pwmMin l'impulsion minimum correspondante sur 4096 et
  pwmMax l'impulsion maximum correspondante sur 4096.

  Ici T sera exprimé microsecondes.
  - pwmMin = (pulseMin/T) * 4096
  - pwmMax = (pulseMax/T) * 4096

  Exemple dans le cas du servo DS3225 25Kg (Plage de largeur d'impulsion: 500 ~ 2500 μsec)
  F = 60Hz => T = 0.016s soit 16ms ou encore 16 000 μsec.
  pulseMin = 500 microsecondes (donnée constructeur).
  pulseMax = 2500 microsecondes (donnée constructeur).

  pwmMin = (500/16000) * 4096 = 128 (on pourra prendre 130 pour avoir une marge de sécurité).
  pwmMax = (2500/16000) * 4096 = 640 (on pourra prendre 638 pour avoir une marge de sécurité).
*/

uint16_t SERVOMIN_DS3225 = 166;
uint16_t SERVOMAX_DS3225 = 673;
//uint16_t SERVOMIN_DS3225 = 128;  // La longueur d'impulsion 'minimale' pwm du servo DS3225 25Kg (valeur du compteur, max 4096 -> voir formule)
//uint16_t SERVOMAX_DS3225 = 638;  // La longueur d'impulsion 'maximale' pwm du servo DS3225 25Kg (valeur du compteur, max 4096 - -> voir formule)
uint16_t PULSE_MIN = 500;
uint16_t PULSE_MAX = 2500;

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
const uint8_t servo_0 = 0;
const uint8_t servo_1 = 1;

float freq = 60;
bool initBreakout = false;
bool start_test = false;
float degrees = 0.0;
bool test1 = false;
bool test2 = false;
bool test3 = false;
volatile bool stop_servo = false;
int interval = 3;

void setup() {

  Serial.begin(19200);
  attachInterrupt(digitalPinToInterrupt(2), stopServo, CHANGE);

  initBreakout = pwm.begin();

  if (initBreakout) {
    pwm.setPWMFreq(freq);  // au démarrage on initialise la fréquence du servo avec une valeur par défaut.

    uint32_t defautlOscillatorFrequency = pwm.getOscillatorFrequency();
    String defautlOscillatorFrequencyMessage = F("Valeur par défaut de la fréquence de l'oscillateur: ");
    defautlOscillatorFrequencyMessage.concat(defautlOscillatorFrequency);
    Serial.println(defautlOscillatorFrequencyMessage);

    pwm.setOscillatorFrequency(27000000);

    //Servo au neutre
    neutral(servo_0);
    neutral(servo_1);

  } else {
    Serial.println(F("Erreur d'initialisation du breakout."));
  }

  delay(10);
}

void loop() {

  // Lecture des commandes sur le port série.
  // On attend plusieurs types de commandes:
  // - F:XXX, permet de spécifier la fréquence (XXX étant la valeur de la fréquence).
  // - T1 pour lancer le test 1, T2 pour le 2 et T3 pour lancer le test 3.
  // - TRUE/FALSE, qui permet d'activer ou non le test.
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

  extractEntryData(command);

  if (start_test && initBreakout) {

    Serial.print(F("Valeur de SERVOMIN_MG996R: "));
    Serial.println(SERVOMIN_DS3225);
    Serial.print(F("Valeur de SERVOMAX_MG996R: "));
    Serial.println(SERVOMAX_DS3225);

    if (test1) {
      Serial.println(F("TEST 1"));
      test_1();
    } else if (test2) {
      Serial.println(F("TEST 2"));
      test_2();
      stop_servo = false;
    } else if (test3) {
      Serial.println(F("TEST 3"));
      test_3();
      stop_servo = false;
    }

    start_test = false;
  }
}


/**
  Extrait les données lues sur l'entrée série
*/
void extractEntryData(String command) {

  if (command == "TRUE") {
    start_test = true;
  } else if (command == "FALSE") {
    start_test = false;
  } else if (command == "T1") {
    test1 = true;
    test2 = false;
    test3 = false;
  } else if (command == "T2") {
    test2 = true;
    test1 = false;
    test3 = false;
  } else if (command == "T3") {
    test3 = true;
    test1 = false;
    test2 = false;
  } else if (command.charAt(0) == 'F') {
    String freqStr = command.substring(2, command.length());
    Serial.print(F("Valeur de la fréquence: "));
    Serial.println(freqStr);
    freq = freqStr.toFloat();
    pwm.setPWMFreq(freq);
  } else if (command.charAt(0) == 'M') {
    String minOrMax = command.substring(0, 3);
    String valueStr = command.substring(4, command.length());
    Serial.print(minOrMax);
    Serial.print(F(": "));
    Serial.println(valueStr);

    if (minOrMax == "MIN") {
      SERVOMIN_DS3225 = valueStr.toInt();
    } else {
      SERVOMAX_DS3225 = valueStr.toInt();
    }
  } else if (command.charAt(0) == 'D') {
    String degreesStr = command.substring(2, command.length());
    Serial.print(F("Valeur des degrés: "));
    Serial.println(degreesStr);
    degrees = degreesStr.toFloat();
  } else if (command.charAt(0) == 'I') {
    String intervalStr = command.substring(2, command.length());
    Serial.print(F("Valeur de l'interval: "));
    Serial.println(intervalStr);
    interval = intervalStr.toInt();
  } else if (command == "NEUTRE") {
    neutral(servo_0);
    neutral(servo_1);
  } else {
    if (command != "") {
      Serial.println(F("Commande non reconnue !"));
    }
  }
}

void neutral(const uint8_t servo_num) {
  //int pulseLen = map(135, 0, 270, SERVOMIN_DS3225, SERVOMAX_DS3225);
  int pulseLen = map(133, 0, 270, SERVOMIN_DS3225, SERVOMAX_DS3225);
  pwm.setPWM(servo_num, 0, pulseLen);
}

void test_1() {

  Serial.print(F("Servo 0 à: "));
  Serial.print(degrees);
  Serial.println(F("°"));
  int pulseLen = map(degrees, 0, 270, SERVOMIN_DS3225, SERVOMAX_DS3225);
  Serial.print(F("pulseLen = "));
  Serial.println(pulseLen);
  pwm.setPWM(servo_0, 0, pulseLen);

  Serial.print(F("Servo 1 à: "));
  Serial.print(degrees);
  Serial.println(F("°"));
  pulseLen = map(degrees, 0, 270, SERVOMIN_DS3225, SERVOMAX_DS3225);
  Serial.print(F("pulseLen = "));
  Serial.println(pulseLen);
  pwm.setPWM(servo_1, 0, pulseLen);

  delay(500);
}

/**
  Test avec la fonction setPWM.
*/
void test_2() {

  pwm.setPWM(servo_0, 0, SERVOMIN_DS3225);
  pwm.setPWM(servo_1, 0, SERVOMIN_DS3225);

  delay(2000);

  for (uint16_t pulselen = SERVOMIN_DS3225; pulselen < SERVOMAX_DS3225; pulselen++) {
    if (stop_servo) {
      Serial.println(F("STOP"));
      break;
    }
    pwm.setPWM(servo_0, 0, pulselen);
    pwm.setPWM(servo_1, 0, pulselen);
    delay(interval);
  }

  delay(5000);

  for (uint16_t pulselen = SERVOMAX_DS3225; pulselen > SERVOMIN_DS3225; pulselen--) {
    if (stop_servo) {
      Serial.println(F("STOP"));
      break;
    }
    pwm.setPWM(servo_0, 0, pulselen);
    pwm.setPWM(servo_1, 0, pulselen);
    delay(interval);
  }
}

/**
  Test avec la fonction writeMicroseconds.
*/
void test_3() {

  pwm.writeMicroseconds(servo_0, PULSE_MIN);
  pwm.writeMicroseconds(servo_1, PULSE_MIN);

  delay(2000);

  for (uint16_t pulselen = PULSE_MIN; pulselen < PULSE_MAX; pulselen++) {
    if (stop_servo) {
      Serial.println(F("STOP"));
      break;
    }
    pwm.writeMicroseconds(servo_0, pulselen);
    pwm.writeMicroseconds(servo_1, pulselen);
    delay(interval);
  }

  delay(5000);

  for (uint16_t pulselen = PULSE_MAX; pulselen > PULSE_MIN; pulselen--) {
    if (stop_servo) {
      Serial.println(F("STOP"));
      break;
    }
    pwm.writeMicroseconds(servo_0, pulselen);
    pwm.writeMicroseconds(servo_1, pulselen);
    delay(interval);
  }
}

void stopServo() {
  //stop_servo = true;
}
