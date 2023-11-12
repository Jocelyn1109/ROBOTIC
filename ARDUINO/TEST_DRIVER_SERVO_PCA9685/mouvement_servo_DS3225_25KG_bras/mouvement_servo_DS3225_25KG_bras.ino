/*
  Jocelyn GIROD
  08/11/2023

  Programme de test du servo DS3225 25Kg.
  Test des mouvement des servos pour le bras.

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

uint16_t SERVOMIN_DS3225 = 166;
uint16_t SERVOMAX_DS3225 = 673;
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
const uint8_t servo_0 = 0;
float freq = 60;
bool initBreakout = false;
bool start_test = false;
bool test1 = false;
bool test2 = false;
float currentDegrees = 0.0;
float currentDegreesArray[6] = {};
float degrees = 0.0;
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
    neutral(servo_0);

  } else {
    Serial.println(F("Erreur d'initialisation du breakout."));
  }

  delay(10);
}

void loop() {

  // Lecture des commandes sur le port série.
  // On attend plusieurs types de commandes:
  // - T1 pour lancer le test 1 et T2 pour lancer le test 2.
  // - TRUE/FALSE, qui permet d'activer ou non le test.
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
      Serial.println(F("TEST 1 - sens +"));
      test_1();
    }

    if (test2) {
      Serial.println(F("TEST 2 - sens -"));
      test_2();
    }

    start_test = false;
  }
}


void neutral(const uint8_t servo_num) {
  int pulseLen = map(135, 0, 270, SERVOMIN_DS3225, SERVOMAX_DS3225);
  pwm.setPWM(servo_num, 0, pulseLen);
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
  } else if (command == "T1") {
    test1 = true;
    test2 = false;
  } else if (command == "T2") {
    test2 = true;
    test1 = false;
  } else if (command == "NEUTRE") {
    neutral(servo_0);
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
  } else {
    if (command != "") {
      Serial.println(F("Commande non reconnue !"));
    }
  }
}


/**
  Test avec la fonction setPWM - sens +
*/
void test_1() {

  //TODO:à tester
  uint16_t currentPWMOutput = pwm.getPWM(servo_0);
  int curDeg = map(currentPWMOutput, SERVOMIN_DS3225, SERVOMAX_DS3225, 0, 270);
  Serial.print("Current PWM in degrees: ");
  Serial.println(curDeg);
  Serial.print("Current degrees saved: ");
  Serial.println(currentDegrees);
  
  float deg = 0.0;
  for (deg = currentDegrees; deg < degrees; deg++) {
    int pulseLen = map(deg, 0, 270, SERVOMIN_DS3225, SERVOMAX_DS3225);
    pwm.setPWM(servo_0, 0, pulseLen);
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
void test_2() {

  float deg = 0.0;
  for (deg = currentDegrees; deg > degrees; deg--) {
    int pulseLen = map(deg, 0, 270, SERVOMIN_DS3225, SERVOMAX_DS3225);
    pwm.setPWM(servo_0, 0, pulseLen);
    Serial.println(pulseLen);
    delay(interval);
  }
  currentDegrees = deg;

  Serial.print(F("Current degrees: "));
  Serial.println(currentDegrees);
}