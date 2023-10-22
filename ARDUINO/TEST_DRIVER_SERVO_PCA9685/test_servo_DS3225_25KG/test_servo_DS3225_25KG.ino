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

uint16_t SERVOMIN_DS3225 = 500;   // La longueur d'impulsion 'minimale' du servo DS3225 25Kg (valeur du compteur, max 4096)
uint16_t SERVOMAX_DS3225 = 2500;  // La longueur d'impulsion 'maximale' du servo DS3225 25Kg (valeur du compteur, max 4096)

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
const uint8_t servo_0 = 0;

float freq = 330;
bool initBreakout = false;
bool start_test = false;
float degrees = 0.0;

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
    pwm.setPWM(servo_0, 0, 1500);
    
  } else {
    Serial.println(F("Erreur d'initialisation du breakout."));
  }

  delay(10);
}

void loop() {

  // Lecture des commandes sur le port série.
  // On attend deux types de commandes:
  // - F:XXX, permet de spécifier la fréquence (XXX étant la valeur de la fréquence).
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

  if (command == "TRUE") {
    start_test = true;
  } else if (command == "FALSE") {
    start_test = false;
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
  } else if (command == "NEUTRE") {
    pwm.setPWM(servo_0, 0, 1500);
  } else {
    if (command != "") {
      Serial.println(F("Commande non reconnue !"));
    }
  }

  if (start_test && initBreakout) {
    Serial.println(F("Test 1"));
    test_1();
    //test_2();
    delay(500);
    start_test = false;
  }
}

void test_1() {
  //Position 0 (min: 0°)
  Serial.print(F("Servo à: "));
  Serial.print(degrees);
  Serial.println(F("°"));
  int pulseLen = map(degrees, 0, 270, SERVOMIN_DS3225, SERVOMAX_DS3225);
  Serial.print(F("pulseLen = "));
  Serial.println(pulseLen);
  pwm.setPWM(servo_0, 0, pulseLen);

  //delay(5000);

  //Position 2500 (max: 270°)
  // Serial.println(F("Servo à 270°"));
  // pulseLen = map(270, 0, 270, SERVOMIN_DS3225, SERVOMAX_DS3225);
  // Serial.print(F("pulseLen = "));
  // Serial.println(pulseLen);
  // pwm.setPWM(servo_0, 0, pulseLen);
}

void test_2() {

  for (uint16_t pulselen = SERVOMIN_DS3225; pulselen < SERVOMAX_DS3225; pulselen++) {
    pwm.setPWM(servo_0, 0, pulselen);
  }

  delay(500);
  for (uint16_t pulselen = SERVOMAX_DS3225; pulselen > SERVOMIN_DS3225; pulselen--) {
    pwm.setPWM(servo_0, 0, pulselen);
  }
}
