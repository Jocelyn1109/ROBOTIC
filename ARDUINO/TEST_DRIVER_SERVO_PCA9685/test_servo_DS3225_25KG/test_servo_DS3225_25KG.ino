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

#define SERVOMIN_DS3225 500   // La longueur d'impulsion 'minimale' du servo DS3225 25Kg (valeur du compteur, max 4096)
#define SERVOMAX_DS3225 2500  // La longueur d'impulsion 'maximale' du servo DS3225 25Kg (valeur du compteur, max 4096)

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
const uint8_t servo_0 = 0;
;
float freq = 50;
bool initBreakout = false;
bool start_test = false;

void setup() {

  Serial.begin(19200);

  initBreakout = pwm.begin();
  if (initBreakout) {
    pwm.setPWMFreq(freq);  // au démarrage on initialise la fréquence sur servo avec une valeur par défaut.

    uint32_t defautlOscillatorFrequency = pwm.getOscillatorFrequency();
    String defautlOscillatorFrequencyMessage = F("Valeur par défaut de la fréquence de l'oscillateur: ");
    defautlOscillatorFrequencyMessage.concat(defautlOscillatorFrequency);
    Serial.println(defautlOscillatorFrequencyMessage);

    pwm.setOscillatorFrequency(27000000);
  } else {
    Serial.println(F("Erreur d'initialisation du breakout."));
  }

  delay(10);
}

void loop() {

  // Lecture des commandes sur le port série.
  // On attend deux types de commandes:
  // - F:XXX, qui permet de spécifier la fréquence (XXX étant la valeur de la fréquence)
  // - TRUE/FALSE, qui permet d'activer ou non le test.
  String command = "";
  if (Serial.available() > 0) {
    command = Serial.readString();
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
  } else {
    Serial.print(F("Commande non reconnue !"));
  }

  if (start_test && initBreakout) {

    //Position 0 (min: 0°)
    pwm.setPWM(servo_0, 0, 500);

    delay(500);

    //Position 2500 (max: 270°)
    pwm.setPWM(servo_0, 0, 2500);

    delay(500);
  }
  
}
