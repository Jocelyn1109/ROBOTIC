/*
  Jocelyn GIROD
  16/11/2023

  Programme de test du servo DS3225 25Kg.
  Test des mouvement des 6 servos pour le bras.
  On cherche ici à valider les mouvements définitifs et le comportement du bras.

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

#define SERVO_1 1
#define SERVO_2 2
#define SERVO_3 3
#define SERVO_4 4
#define SERVO_5 5
#define SERVO_6 6

long SERVOMIN_DS3225 = 166.0;
long SERVOMAX_DS3225 = 673.0;
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

float freq = 60;
bool initBreakout = false;
bool start_test = false;
float degrees_ = 0.0;
uint8_t num_servo = 0;
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

    initArm();

  } else {
    Serial.println(F("Erreur d'initialisation du breakout."));
  }

  delay(10);
}

void loop() {

  // Lecture des commandes sur le port série.
  // On attend plusieurs types de commandes:
  // - S1, S2,....S6 pour définir le numéro du servo.
  // - TRUE/FALSE, qui permet d'activer ou non le test.
  // - INIT, permet d'initialiser le bras.
  // - I permet de définir l'interval (vitesse de rotation du servo).
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
    move(num_servo, degrees_);
    start_test = false;
  }
}


/**
  Extrait les données lues sur l'entrée série
*/
void extractEntryData(String command) {

  if (command == "TRUE") {
    start_test = true;
  } else if (command == "S1") {
    num_servo = SERVO_1;
  } else if (command == "S2") {
    num_servo = SERVO_2;
  } else if (command == "S3") {
    num_servo = SERVO_3;
  } else if (command == "S4") {
    num_servo = SERVO_4;
  } else if (command == "S5") {
    num_servo = SERVO_5;
  } else if (command == "S6") {
    num_servo = SERVO_6;
  } else if (command == "INIT") {
    initArm();
  } else if (command.charAt(0) == 'D') {
    String degreesStr = command.substring(2, command.length());
    Serial.print(F("Valeur des degrés: "));
    Serial.println(degreesStr);
    degrees_ = degreesStr.toFloat();
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
  Permet d'initialiser la position du bras.
  Le servo 1 doit avoir un débatement de 20°<-->250°, un neutre à 133° et une position initiale de 133°.
  Le servo 2 doit avoir un débatement de 125°<-->270°, un neutre à 145° et une position initiale de 270°.
  Le servo 3 doit avoir un débatement de 40°<-->220°, un neutre à 133° et une position initiale de 40°.
  Le servo 4 doit avoir un débatement de 133°<-->270°, un neutre à 133° et une position initiale de 270°.
  Le servo 5 doit avoir un débatement de 10°<-->210°, un neutre à 125° et une position initiale de 125°.
  Le servo 6 doit avoir un débatement de 120°<-->220°, un neutre à 120° et une position initiale de 120°.
*/
void initArm() {

  float pulseLen = map(133.0, 0.0, 270.0, SERVOMIN_DS3225, SERVOMAX_DS3225);
  pwm.setPWM(SERVO_1, 0, pulseLen);

  pulseLen = map(270.0, 0.0, 270.0, SERVOMIN_DS3225, SERVOMAX_DS3225);
  pwm.setPWM(SERVO_2, 0, pulseLen);

  pulseLen = map(40.0, 0.0, 270.0, SERVOMIN_DS3225, SERVOMAX_DS3225);
  pwm.setPWM(SERVO_3, 0, pulseLen);

  pulseLen = map(270.0, 0.0, 270.0, SERVOMIN_DS3225, SERVOMAX_DS3225);
  pwm.setPWM(SERVO_4, 0, pulseLen);

  pulseLen = map(125.0, 0.0, 270.0, SERVOMIN_DS3225, SERVOMAX_DS3225);
  pwm.setPWM(SERVO_5, 0, pulseLen);

  pulseLen = map(120.0, 0.0, 270.0, SERVOMIN_DS3225, SERVOMAX_DS3225);
  pwm.setPWM(SERVO_6, 0, pulseLen);
}

/**
   Fait bouger le servo du nombre de degrés passés en paramètre.
*/
void move(uint8_t numServo, float degrees) {

  if (degrees < 0.0 || degrees > 270.0) {
    return;
  }

  uint16_t currentPWM = pwm.getPWM(numServo, true);
  float currentDegrees = map(currentPWM, SERVOMIN_DS3225, SERVOMAX_DS3225, 0.0, 270.0);

  if (degrees > currentDegrees) {
    // sens +
    for (float deg = currentDegrees; deg <= degrees; deg++) {
      float pulseLen = map(deg, 0.0, 270.0, SERVOMIN_DS3225, SERVOMAX_DS3225);
      pwm.setPWM(numServo, 0, pulseLen);
      delay(interval);
    }
  } else if (degrees < currentDegrees) {
    // sens -
    for (float deg = currentDegrees; deg >= degrees; deg--) {
      float pulseLen = map(deg, 0.0, 270.0, SERVOMIN_DS3225, SERVOMAX_DS3225);
      pwm.setPWM(numServo, 0, pulseLen);
      delay(interval);
    }
  }
}
