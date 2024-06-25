/*
  Jocelyn GIROD
  20/10/2023

  Programme de réglage des limites des servos DS3225 25Kg du bras.

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

void neutral(const uint8_t num);
void extractEntryData(String command);
void move_degrees();

#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm{};
uint16_t SERVOMIN_DS3225 = 166;
uint16_t SERVOMAX_DS3225 = 673;

float freq = 60;
bool initBreakout = false;
bool start_test = false;
float degrees = 0.0;
uint8_t num_servo = 0;
float currentDegrees = 0.0;
bool test1 = false;
bool test2 = false;
bool test3 = false;
int interval = 1;

void setup() {

  Serial.begin(19200);

  initBreakout = pwm.begin();

  if (initBreakout) {
    pwm.setPWMFreq(freq);  // au démarrage on initialise la fréquence du servo avec une valeur par défaut.

    uint32_t defautlOscillatorFrequency = pwm.getOscillatorFrequency();
    String defautlOscillatorFrequencyMessage = F("Valeur par défaut de la fréquence de l'oscillateur: ");
    defautlOscillatorFrequencyMessage.concat(defautlOscillatorFrequency);
    Serial.println(defautlOscillatorFrequencyMessage);

    pwm.setOscillatorFrequency(27000000);

    //Servo au neutre
    //neutral(1);
    //neutral(2);
    //neutral(3);
    //neutral(4);
  }
}

void loop() {
  // On attend plusieurs types de commandes:
  // - S:X, numéro de servo.
  // - TRUE/FALSE, qui permet d'activer ou non le test.
  // - T1 pour lancer le test 1, T2 pour le 2 et T3 pour lancer le test 3.
  // - D:XXX, permet de spécifier les degrés.
  // - NEUTRE, permet de mettre le servo au neutre.
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
    if (test1) {
      Serial.println(F("Move degrees"));
      move_degrees();
    } else if (test2) {
      Serial.println(F("Move degrees plus"));
      move_degrees_plus();
    } else if (test3) {
      Serial.println(F("Move degrees minus"));
      move_degrees_minus();
    }

    start_test = false;
  }
}


void neutral(const uint8_t num) {
  int pulseLen = map(135, 0, 270, SERVOMIN_DS3225, SERVOMAX_DS3225);
  pwm.setPWM(num, 0, pulseLen);

  currentDegrees = 135.0;

  Serial.print(F("Current degrees: "));
  Serial.println(currentDegrees);
}

/**
  Extrait les données lues sur l'entrée série
*/
void extractEntryData(String command) {

  if (command == "TRUE") {
    start_test = true;
  } else if (command == "FALSE") {
    start_test = false;
  } else if (command == "S1") {
    num_servo = 1;
  } else if (command == "S2") {
    num_servo = 2;
  } else if (command == "S3") {
    num_servo = 3;
  } else if (command == "S4") {
    num_servo = 4;
  } else if (command == "S5") {
    num_servo = 5;
  } else if (command == "S6") {
    num_servo = 6;
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
    neutral(num_servo);
  } else {
    if (command != "") {
      Serial.println(F("Commande non reconnue !"));
    }
  }
}


void move_degrees() {

  Serial.print(F("Servo "));
  Serial.print(num_servo);
  Serial.print(F(" à: "));
  Serial.print(degrees);
  Serial.println(F("°"));
  Serial.print(F("Num servo: "));
  Serial.println(num_servo);
  int pulseLen = map(degrees, 0, 270, SERVOMIN_DS3225, SERVOMAX_DS3225);
  Serial.print(F("pulseLen = "));
  Serial.println(pulseLen);
  pwm.setPWM(num_servo, 0, pulseLen);

  delay(500);
}

/**
  Test avec la fonction setPWM - sens +
*/
void move_degrees_plus() {

  float deg = 0.0;
  for (deg = currentDegrees; deg < degrees; deg++) {
    int pulseLen = map(deg, 0, 270, SERVOMIN_DS3225, SERVOMAX_DS3225);
    pwm.setPWM(num_servo, 0, pulseLen);
    Serial.print(F("degrees = "));
    Serial.println(deg);
    Serial.print(F("pulseLen = "));
    Serial.println(pulseLen);
    delay(interval);
  }
  currentDegrees = deg;

  Serial.print(F("Current degrees: "));
  Serial.println(currentDegrees);
}


/**
  Test avec la fonction setPWM - sens -
*/
void move_degrees_minus() {

  float deg = 0.0;
  for (deg = currentDegrees; deg > degrees; deg--) {
    int pulseLen = map(deg, 0, 270, SERVOMIN_DS3225, SERVOMAX_DS3225);
    pwm.setPWM(num_servo, 0, pulseLen);
    Serial.print(F("degrees = "));
    Serial.println(deg);
    Serial.print(F("pulseLen = "));
    Serial.println(pulseLen);
    delay(interval);
  }
  currentDegrees = deg;

  Serial.print(F("Current degrees: "));
  Serial.println(currentDegrees);
}