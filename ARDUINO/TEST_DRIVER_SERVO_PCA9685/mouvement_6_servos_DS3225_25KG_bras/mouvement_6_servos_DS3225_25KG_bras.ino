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
#include <math.h>

#define SERVO_1 1
#define SERVO_2 2
#define SERVO_3 3
#define SERVO_4 4
#define SERVO_5 5
#define SERVO_6 6

long SERVOMIN_DS3225 = 166.0;
long SERVOMAX_DS3225 = 673.0;
Adafruit_PWMServoDriver pwm{};

float freq = 60;
bool initBreakout = false;
bool start_test = false;
float degrees_ = 0.0;
uint8_t num_servo = 0;
int interval = 3;

// servo 1 currentServosDegrees[0]
// servo 2 currentServosDegrees[1]
// servo 3 currentServosDegrees[2]
// servo 4 currentServosDegrees[3]
// servo 5 currentServosDegrees[4]
// servo 6 currentServosDegrees[5]
float curentServosDegrees[6] = {};

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

    delay(2000);
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

    switch (num_servo) {
      case 1:
        move_servo_1(degrees_);
        break;
      case 2:
        move_servo_2(degrees_);
        break;
      case 3:
        move_servo_3(degrees_);
        break;
      case 4:
        move_servo_4(degrees_);
        break;
      case 5:
        move_servo_5(degrees_);
        break;
      case 6:
        move_servo_6(degrees_);
        break;
      default: break;
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
  } else if (command == "SLEEP") {
    pwm.sleep();
  } else if (command == "WAKEUP") {
    pwm.wakeup();
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
  Le servo 1 doit avoir un débatement de 66°<-->200°, un neutre à 133° et une position initiale de 133°.
  Le servo 2 doit avoir un débatement de 125°<-->270°, un neutre à 145° et une position initiale de 270°.
  Le servo 3 doit avoir un débatement de 40°<-->220°, un neutre à 133° et une position initiale de 40°.
  Le servo 4 doit avoir un débatement de 133°<-->270°, un neutre à 133° et une position initiale de 270°.
  Le servo 5 doit avoir un débatement de 10°<-->210°, un neutre à 125° et une position initiale de 125°.
  Le servo 6 doit avoir un débatement de 120°<-->220°, un neutre à 120° et une position initiale de 120°.
*/
void initArm() {

  pwm.setPWM(SERVO_1, 0, 0);
  pwm.setPWM(SERVO_2, 0, 0);
  pwm.setPWM(SERVO_3, 0, 0);
  pwm.setPWM(SERVO_4, 0, 0);
  pwm.setPWM(SERVO_5, 0, 0);
  pwm.setPWM(SERVO_6, 0, 0);

  float pulseLen = map(133.0, 0.0, 270.0, SERVOMIN_DS3225, SERVOMAX_DS3225);
  pwm.setPWM(SERVO_1, 0, pulseLen);
  curentServosDegrees[0] = 133.0;
  delay(100);

  pulseLen = map(270.0, 0.0, 270.0, SERVOMIN_DS3225, SERVOMAX_DS3225);
  pwm.setPWM(SERVO_2, 0, pulseLen);
  curentServosDegrees[1] = 270.0;
  delay(100);

  pulseLen = map(40.0, 0.0, 270.0, SERVOMIN_DS3225, SERVOMAX_DS3225);
  pwm.setPWM(SERVO_3, 0, pulseLen);
  curentServosDegrees[2] = 40.0;
  delay(100);

  pulseLen = map(270.0, 0.0, 270.0, SERVOMIN_DS3225, SERVOMAX_DS3225);
  pwm.setPWM(SERVO_4, 0, pulseLen);
  curentServosDegrees[3] = 270.0;
  delay(100);

  pulseLen = map(125.0, 0.0, 270.0, SERVOMIN_DS3225, SERVOMAX_DS3225);
  pwm.setPWM(SERVO_5, 0, pulseLen);
  curentServosDegrees[4] = 125.0;
  delay(100);

  pulseLen = map(120.0, 0.0, 270.0, SERVOMIN_DS3225, SERVOMAX_DS3225);
  pwm.setPWM(SERVO_6, 0, pulseLen);
  curentServosDegrees[5] = 120.0;
  delay(100);
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

  Serial.print(F("currentDegrees = "));
  Serial.println(currentDegrees);
  Serial.print(F("degrees = "));
  Serial.println(degrees);

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

/**
  Mouvement servo 1
*/
void move_servo_1(float degrees) {

  Serial.println(F("Mouvement servo 1\n"));

  // limite servo 1 [66;200]
  if (degrees >= 66 && degrees <= 200) {

    float currentDegrees = curentServosDegrees[0];
    if (degrees > currentDegrees) {
      // sens +
      for (float deg = currentDegrees; deg <= degrees; deg++) {
        float pulseLen = map(deg, 0.0, 270.0, SERVOMIN_DS3225, SERVOMAX_DS3225);
        pwm.setPWM(SERVO_1, 0, pulseLen);
        curentServosDegrees[0] = deg;
        delay(interval);
      }
    } else if (degrees < currentDegrees) {
      // sens -
      for (float deg = currentDegrees; deg >= degrees; deg--) {
        float pulseLen = map(deg, 0.0, 270.0, SERVOMIN_DS3225, SERVOMAX_DS3225);
        pwm.setPWM(SERVO_1, 0, pulseLen);
        curentServosDegrees[0] = deg;
        delay(interval);
      }
    }
  }
}

/**
  Mouvement servo 2
*/
void move_servo_2(float degrees) {

  Serial.println(F("Mouvement servo 2\n"));

  float incr = calculIncrement(230.0, degrees, curentServosDegrees[2], 80.0);

  Serial.print(F("\nValeur de l'incrément: "));
  Serial.println(incr);
  Serial.print(F("Valeur initiale servo 3: "));
  Serial.println(curentServosDegrees[2]);


  // limite servo 2 [125;270]
  if (degrees >= 125 && degrees <= 270) {

    float currentDegrees = curentServosDegrees[1];
    if (degrees > currentDegrees) {
      // sens +
      for (float deg = currentDegrees; deg <= degrees; deg++) {
        float pulseLen = map(deg, 0.0, 270.0, SERVOMIN_DS3225, SERVOMAX_DS3225);
        pwm.setPWM(SERVO_2, 0, pulseLen);
        curentServosDegrees[1] = deg;
        delay(interval);
      }
    } else if (degrees < currentDegrees) {
      // sens -
      for (float deg = currentDegrees; deg >= degrees; deg--) {
        float pulseLen = map(deg, 0.0, 270.0, SERVOMIN_DS3225, SERVOMAX_DS3225);
        pwm.setPWM(SERVO_2, 0, pulseLen);
        curentServosDegrees[1] = deg;
        if (deg <= 230.0 && curentServosDegrees[2] <= 80.0) {
          //float degreesS3 = curentServosDegrees[2] + incr;
          //float pulseLen = map(degreesS3, 0.0, 270.0, SERVOMIN_DS3225, SERVOMAX_DS3225);
          //pwm.setPWM(SERVO_3, 0, pulseLen);
          float pulseLen = map(100.0, 0.0, 270.0, SERVOMIN_DS3225, SERVOMAX_DS3225);
          pwm.setPWM(SERVO_3, 0, pulseLen);
          //curentServosDegrees[2] = degreesS3;
          curentServosDegrees[2] = 100.0;
        }
        delay(interval);
      }
    }
  }

  Serial.print("Degrés servo 3 = ");
  Serial.println(curentServosDegrees[2]);
}

/**
  Mouvement servo 3
*/
void move_servo_3(float degrees) {

  Serial.println(F("Mouvement servo 3\n"));

  // limite servo 3 [40;220]
  if (degrees >= 40 && degrees <= 220) {

    float currentDegrees = curentServosDegrees[2];
    if (degrees > currentDegrees) {
      // sens +
      for (float deg = currentDegrees; deg <= degrees; deg++) {
        float pulseLen = map(deg, 0.0, 270.0, SERVOMIN_DS3225, SERVOMAX_DS3225);
        pwm.setPWM(SERVO_3, 0, pulseLen);
        curentServosDegrees[2] = deg;
        // empêche la basculement vers l'arrière à cause du poids
        // l'angle du servo 3 ne doit pas être inférieur à 80 degrés lorsque le servo 2 est dans l'intervalle [250;270]
        if (curentServosDegrees[1] >= 250 && curentServosDegrees[1] <= 270 && deg >= 80) {
          return;
        }
        delay(interval);
      }
    } else if (degrees < currentDegrees) {
      // sens -
      for (float deg = currentDegrees; deg >= degrees; deg--) {
        float pulseLen = map(deg, 0.0, 270.0, SERVOMIN_DS3225, SERVOMAX_DS3225);
        pwm.setPWM(SERVO_3, 0, pulseLen);
        curentServosDegrees[2] = deg;
        delay(interval);
      }
    }
  }
}

/**
  Mouvement servo 4
*/
void move_servo_4(float degrees) {

  Serial.println(F("Mouvement servo 4\n"));

  // limite servo 4 [133;270]
  if (degrees >= 133 && degrees <= 270) {

    float currentDegrees = curentServosDegrees[3];
    if (degrees > currentDegrees) {
      // sens +
      for (float deg = currentDegrees; deg <= degrees; deg++) {
        float pulseLen = map(deg, 0.0, 270.0, SERVOMIN_DS3225, SERVOMAX_DS3225);
        pwm.setPWM(SERVO_4, 0, pulseLen);
        curentServosDegrees[3] = deg;
        delay(interval);
      }
    } else if (degrees < currentDegrees) {
      // sens -
      for (float deg = currentDegrees; deg >= degrees; deg--) {
        float pulseLen = map(deg, 0.0, 270.0, SERVOMIN_DS3225, SERVOMAX_DS3225);
        pwm.setPWM(SERVO_4, 0, pulseLen);
        curentServosDegrees[3] = deg;
        delay(interval);
      }
    }
  }
}

/**
  Mouvement servo 5
*/
void move_servo_5(float degrees) {

  Serial.println(F("Mouvement servo 5\n"));

  // limite servo 5 [10;210]
  if (degrees >= 10 && degrees <= 210) {

    float currentDegrees = curentServosDegrees[4];
    if (degrees > currentDegrees) {
      // sens +
      for (float deg = currentDegrees; deg <= degrees; deg++) {
        float pulseLen = map(deg, 0.0, 270.0, SERVOMIN_DS3225, SERVOMAX_DS3225);
        pwm.setPWM(SERVO_5, 0, pulseLen);
        curentServosDegrees[4] = deg;
        delay(interval);
      }
    } else if (degrees < currentDegrees) {
      // sens -
      for (float deg = currentDegrees; deg >= degrees; deg--) {
        float pulseLen = map(deg, 0.0, 270.0, SERVOMIN_DS3225, SERVOMAX_DS3225);
        pwm.setPWM(SERVO_5, 0, pulseLen);
        curentServosDegrees[4] = deg;
        delay(interval);
      }
    }
  }
}


/**
  Mouvement servo 6
*/
void move_servo_6(float degrees) {

  Serial.println(F("Mouvement servo 6\n"));

  // limite servo 6 [120;220]
  if (degrees >= 120 && degrees <= 220) {

    float currentDegrees = curentServosDegrees[5];
    if (degrees > currentDegrees) {
      // sens +
      for (float deg = currentDegrees; deg <= degrees; deg++) {
        float pulseLen = map(deg, 0.0, 270.0, SERVOMIN_DS3225, SERVOMAX_DS3225);
        pwm.setPWM(SERVO_6, 0, pulseLen);
        curentServosDegrees[5] = deg;
        delay(interval);
      }
    } else if (degrees < currentDegrees) {
      // sens -
      for (float deg = currentDegrees; deg >= degrees; deg--) {
        float pulseLen = map(deg, 0.0, 270.0, SERVOMIN_DS3225, SERVOMAX_DS3225);
        pwm.setPWM(SERVO_6, 0, pulseLen);
        curentServosDegrees[5] = deg;
        delay(interval);
      }
    }
  }
}

/**
  Calcul de l'incrément
*/
float calculIncrement(float startFirstServo, float endFirstServo, float startSecondServo, float endSecondServo) {

  float todoFirstServo = endFirstServo - startFirstServo;
  if (endFirstServo < startFirstServo) {
    todoFirstServo = todoFirstServo * -1;
  }
  float todoSecondServo = endSecondServo - startSecondServo;
  return todoFirstServo / todoSecondServo;
}
