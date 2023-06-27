
/**
   Programme de tests de la tête du robot Tribot
   Leds + moteur (driveur L9110)
   Expressionss faciales

   Nappe fils 1:
   fil violet: alim 5V
   fil bleu: led oeil gauche
   fil turquoise: led oeil droit
   fil jaune: led oreille droite
   fil orange: led oreille gauche
   fil rouge: led milieu bouche
   fil maron: led droite bouche

   Nappe fils 2:
   fil maron: led gauche bouche
   fil rouge: led capôt tête
   fil orange: fin de course milieu
   fil jaune: fin de course gauche
   fil turquoise: fin de course droit
   fil bleu: commun fins de course
*/

//leds oeil gauche: fil bleu - oeil droit: fil turquoise
#define LEFT_EYE_LED 3
#define RIGHT_EYE_LED 5

//leds bouche milieu: fil rouge/droite: fil marron (nappe 1)/gauche: fil marron (nappe 2)
#define MIDDLE_MOUTH_LED 2
#define RIGHT_MOUTH_LED 4
#define LEFT_MOUTH_LED 6

//leds oreilles
#define RIGHT_EAR_LED 9
#define LEFT_EAR_LED 10

//led capôt tête
#define HEAD_HOOP_LED 11

//Moteur A: A-IA Fil blanc - pin 7
#define MOTORA_INPUT_A 7

//Moteur A: A-IB Fil marron - pin 8
#define MOTORA_INPUT_B 8

//fins de course
#define INPUT_R_SWITCH A0 //cable turquoise - right switch
#define INPUT_L_SWITCH A1 //cable jaune - left switch
#define INPUT_M_SWITCH A2 //cable orange - middle switch

volatile bool isEyebrows = false;
volatile bool isHeadHood = false;
volatile bool isAllOpen = false;
volatile bool isBackward = false;

bool isPeriodicBlinkEyes = true;

volatile bool isTalk = false;

char func = 'I';

unsigned long previousTime;
unsigned long currentTime;


/**
   DOCUMENTATION:
   One macro "digitalPinToPCMSK" is defined in "pins_arduino.h" which allows us to quickly get the proper register (PCMSK0, PCMSK1, or PCMSK2) given the number of the Arduino pin.
   So when we write: digitalPinToPCMSK(9), the address of PCMSK0 is returned. We can use the dereferencing operator '*' to get the value of the address.
   That is, *digitalPinToPCMSK(9) returns: {00000000}.
   Another macro , "digitalPinToPCMSKbit" is also defined in "pins_arduino.h" and returns the position of the bit of interest within the PCMSK of interest.
*/
void pciSetup(byte pin)
{
  *digitalPinToPCMSK(pin) |= bit (digitalPinToPCMSKbit(pin));  // enable pin
  PCIFR  |= bit (digitalPinToPCICRbit(pin)); // clear any outstanding interrupt
  PCICR  |= bit (digitalPinToPCICRbit(pin)); // enable interrupt for the group
}

/**
   Méthode appelée pour INPUT_R_SWITCH, INPUT_L_SWITCH et INPUT_M_SWITCH
*/
ISR (PCINT1_vect) // handle pin change interrupt for D8 to D13 here
{
  //sourcils (battements)
  if (isEyebrows && digitalRead(INPUT_R_SWITCH) == HIGH) {
    if (isTalk) {
      digitalWrite(MIDDLE_MOUTH_LED, LOW);
      digitalWrite(RIGHT_MOUTH_LED, LOW);
      digitalWrite(LEFT_MOUTH_LED, LOW);
    }
    backward();
  }

  //ouverture du capot de la tête
  if (isHeadHood && digitalRead(INPUT_R_SWITCH) == LOW && digitalRead(INPUT_M_SWITCH) == LOW && digitalRead(INPUT_L_SWITCH) == LOW) {
    isHeadHood = false;
    stop();
  }

  //Butée initiale
  if (isBackward && digitalRead(INPUT_R_SWITCH) == LOW && digitalRead(INPUT_M_SWITCH) == HIGH && digitalRead(INPUT_L_SWITCH) == HIGH) {
    stop();
    isBackward = false;
  }

  //Butée finale - sourcils, capot et oreilles
  if (isAllOpen == true && digitalRead(INPUT_R_SWITCH) == LOW && digitalRead(INPUT_M_SWITCH) == HIGH && digitalRead(INPUT_L_SWITCH) == LOW) {
    stop();
    isAllOpen = false;
  }
}

void setup() {

  Serial.begin(19200);
  previousTime = millis();
  initialMessage();

  /* Attention ici HIGH = eteind et LOW = allumé
       Ceci vient du cablage de la tête         */

  /* leds oeil droit et gauche */
  pinMode(LEFT_EYE_LED, OUTPUT);
  pinMode(RIGHT_EYE_LED, OUTPUT);

  /* leds bouche */
  pinMode(MIDDLE_MOUTH_LED, OUTPUT);
  pinMode(RIGHT_MOUTH_LED, OUTPUT);
  pinMode(LEFT_MOUTH_LED, OUTPUT);

  /* leds oreilles */
  pinMode(RIGHT_EAR_LED, OUTPUT);
  pinMode(LEFT_EAR_LED, OUTPUT);

  /* leds capôt tête */
  pinMode(HEAD_HOOP_LED, OUTPUT);

  /* output moteur */
  pinMode(MOTORA_INPUT_A, OUTPUT);
  pinMode(MOTORA_INPUT_B, OUTPUT);

  /* fins de course */
  pinMode(INPUT_R_SWITCH, INPUT_PULLUP);
  pinMode(INPUT_L_SWITCH, INPUT_PULLUP);
  pinMode(INPUT_M_SWITCH, INPUT_PULLUP);

  /* activation des interruption */
  pciSetup(INPUT_R_SWITCH);
  pciSetup(INPUT_L_SWITCH);
  pciSetup(INPUT_M_SWITCH);

  stop();

  switchOffAllLeds();
  wakeUp(5, true);

}

void loop() {

  currentTime = millis();

  //clignotement des yeux toutes les 20 secondes
  if ((currentTime - previousTime) == 20000) {
    previousTime = currentTime;
    if(isPeriodicBlinkEyes == true){
      blinkTwoEyes(100);
      Serial.println("blink eyes");
    }
  }

  if (Serial.available() > 0) {
    func = Serial.read();

  } else {
    func = 'I';
  }

  setMode(func);

  //Parler
  if (isTalk) {
    digitalWrite(MIDDLE_MOUTH_LED, LOW);
    digitalWrite(RIGHT_MOUTH_LED, LOW);
    digitalWrite(LEFT_MOUTH_LED, LOW);
    delay(100);
    digitalWrite(MIDDLE_MOUTH_LED, HIGH);
    digitalWrite(RIGHT_MOUTH_LED, HIGH);
    digitalWrite(LEFT_MOUTH_LED, HIGH);
    delay(100);
  }

  //Battement des sourcils
  if (func == 'A') {
    func = 'I';
    blinkEyeBrown(200, 2);
    delay(300);
    blinkEyeBrown(200, 2);
  }

  //Capôt tête + led
  if (func == 'B') {
    func = 'I';
    forward();
    delay(1000);
    switchOnOffHeadHoodLed(true);
  }

  // Tout ouvert + leds
  if (func == 'C') {
    func = 'I';
    isPeriodicBlinkEyes = false;
    forward();
    delay(1000);
    switchOnOffHeadHoodLed(true);
    switchOnOffEarsLed(true);
    delay(100);
    blinkTwoEyes(200);
    delay(100);
    isPeriodicBlinkEyes = true;
  }

  //Demo expressions visage - leds uniquement
  if (func == 'D') {
    func == 'I';
    isPeriodicBlinkEyes = false;
    switchOnOffEyesLed(true);
    switchOnOffMouthLed(true);
    delay(2000);
    switchOnOffMouthLed(false);
    delay(1500);
    talk(100, 20);
    delay(1500);
    talk(50, 20);
    delay(1500);
    switchOnOffMouthLed(false);
    delay(1500);
    talk_2(100, 20);
    delay(1500);
    talk_3(200, 10);
    delay(2000);
    switchOnOffMouthLed(false);
    doubtFulLeft();
    delay(2000);
    doubtFulRight();
    delay(1500);
    switchOnOffMouthLed(false);
    switchOnOffEyesLed(true);
    isPeriodicBlinkEyes = true;
  }


  //Retour à la position initiale: oreilles et capôt fermé
  if (func == 'R') {
    func == 'I';
    switchOnOffHeadHoodLed(false);
    switchOnOffEarsLed(false);
    backward();
  }

  //Eteindre les leds
  if (func == 'S') {
    func == 'I';
    isTalk = false;
    switchOffAllLeds();
  }

}

/**
   Détermine ce que l'on veut tester
*/
void setMode(char mode) {
  if (mode == '1') {
    Serial.println("mode 1");
    isEyebrows = true;
    isHeadHood = false;
    isAllOpen = false;
    isTalk = true;
  } else if (mode == '2') {
    Serial.println("mode 2");
    isEyebrows = false;
    isHeadHood = true;
    isAllOpen = false;
    isTalk = false;
  } else if (mode == '3') {
    Serial.println("mode 3");
    isEyebrows = false;
    isHeadHood = false;
    isAllOpen = true;
    isTalk = false;
  } else if (mode == '4') {
    Serial.println("mode 4");
    isEyebrows = false;
    isHeadHood = false;
    isAllOpen = false;
    isTalk = false;
  }
}

/**
   Message d'informations
*/
void initialMessage() {
  Serial.println("Fonction 1 & A: parler");
  Serial.println("Fonction 2 & B: ouverture capôt tête avec allumage de la led");
  Serial.println("Fonction 3 & C: ouverture capôt et des oreilles avec allumage des leds (capôt & oreilles)");
  Serial.println("Fonction D: demo expressions visages leds uniquement");

  Serial.println("Fonction R: retour à la position initiale");
}

/****************** FONCTIONS MOTEUR **************************/

/**
  Stop motor
*/
void stop() {
  digitalWrite(MOTORA_INPUT_A, HIGH);
  digitalWrite(MOTORA_INPUT_B, HIGH);
}

/**
   Forward motor
*/
void forward() {
  digitalWrite(MOTORA_INPUT_A, HIGH);
  digitalWrite(MOTORA_INPUT_B, LOW);
}

/**
   Backward motor
*/
void backward() {
  isBackward = true;
  digitalWrite(MOTORA_INPUT_A, LOW);
  digitalWrite(MOTORA_INPUT_B, HIGH);
}



/**
   Battre des sourcils
*/
void blinkEyeBrown(int speed, int lengthBlink) {
  for (int i = 0; i < lengthBlink; i++) {
    forward();
    delay(speed);
  }
}

/******************** FONCTIONS LEDS **************************/


/**
   Eteind toutes les leds
*/
void switchOffAllLeds() {
  digitalWrite(LEFT_EYE_LED, HIGH);
  digitalWrite(RIGHT_EYE_LED, HIGH);
  digitalWrite(MIDDLE_MOUTH_LED, HIGH);
  digitalWrite(LEFT_MOUTH_LED, HIGH);
  digitalWrite(RIGHT_MOUTH_LED, HIGH);
  digitalWrite(LEFT_EAR_LED, HIGH);
  digitalWrite(RIGHT_EAR_LED, HIGH);
  digitalWrite(HEAD_HOOP_LED, HIGH);

}

/*
   Réveil
*/
void wakeUp(int speed, bool isDelayBefore) {

  if (isDelayBefore) {
    delay(60);
  }

  digitalWrite(LEFT_EYE_LED, HIGH);
  digitalWrite(RIGHT_EYE_LED, HIGH);
  for (int fadeValue = 255 ; fadeValue >= 0; fadeValue -= speed) {
    analogWrite(LEFT_EYE_LED, fadeValue);
    analogWrite(RIGHT_EYE_LED, fadeValue);
    delay(60);
  }
}

/**
   Allume/Eteind les leds des yeux
*/
void switchOnOffEyesLed(bool isLight) {
  if (isLight) {
    digitalWrite(LEFT_EYE_LED, LOW);
    digitalWrite(RIGHT_EYE_LED, LOW);
  } else {
    digitalWrite(LEFT_EYE_LED, HIGH);
    digitalWrite(RIGHT_EYE_LED, HIGH);
  }
}


/**
   Allume/Eteind les leds de la bouche
*/
void switchOnOffMouthLed(bool isLight) {
  if (isLight) {
    digitalWrite(MIDDLE_MOUTH_LED, LOW);
    digitalWrite(LEFT_MOUTH_LED, LOW);
    digitalWrite(RIGHT_MOUTH_LED, LOW);
  } else {
    digitalWrite(MIDDLE_MOUTH_LED, HIGH);
    digitalWrite(LEFT_MOUTH_LED, HIGH);
    digitalWrite(RIGHT_MOUTH_LED, HIGH);
  }
}

/**
   Allume/éteind la led du capôt
*/
void switchOnOffHeadHoodLed(bool isLight) {
  if (isLight) {
    digitalWrite(HEAD_HOOP_LED, LOW);
  } else {
    digitalWrite(HEAD_HOOP_LED, HIGH);
  }
}


/**
   Allume/éteind les leds des oreilles
*/
void switchOnOffEarsLed(bool isLight) {
  if (isLight) {
    digitalWrite(LEFT_EAR_LED, LOW);
    digitalWrite(RIGHT_EAR_LED, LOW);
  } else {
    digitalWrite(LEFT_EAR_LED, HIGH);
    digitalWrite(RIGHT_EAR_LED, HIGH);
  }
}

/*
   Clignotement des deux yeux
*/
void blinkTwoEyes(int speed) {
  digitalWrite(LEFT_EYE_LED, LOW);
  digitalWrite(RIGHT_EYE_LED, LOW);
  delay(speed);
  digitalWrite(LEFT_EYE_LED, HIGH);
  digitalWrite(RIGHT_EYE_LED, HIGH);
  delay(speed);
  digitalWrite(LEFT_EYE_LED, LOW);
  digitalWrite(RIGHT_EYE_LED, LOW);
  delay(speed);
  digitalWrite(LEFT_EYE_LED, HIGH);
  digitalWrite(RIGHT_EYE_LED, HIGH);
  delay(speed);
  digitalWrite(LEFT_EYE_LED, LOW);
  digitalWrite(RIGHT_EYE_LED, LOW);
}

/**
   Parler
*/
void talk(int speed, int talkLength) {
  for (int i = 0; i < talkLength; i++) {
    digitalWrite(MIDDLE_MOUTH_LED, HIGH);
    digitalWrite(RIGHT_MOUTH_LED, HIGH);
    digitalWrite(LEFT_MOUTH_LED, HIGH);
    delay(speed);
    digitalWrite(MIDDLE_MOUTH_LED, LOW);
    digitalWrite(RIGHT_MOUTH_LED, LOW);
    digitalWrite(LEFT_MOUTH_LED, LOW);
    delay(speed);
  }
}

void talk_2(int speed, int talkLength) {
  for (int i = 0; i < talkLength; i++) {
    digitalWrite(MIDDLE_MOUTH_LED, LOW);
    digitalWrite(RIGHT_MOUTH_LED, HIGH);
    digitalWrite(LEFT_MOUTH_LED, HIGH);
    delay(speed);
    digitalWrite(MIDDLE_MOUTH_LED, HIGH);
    digitalWrite(RIGHT_MOUTH_LED, LOW);
    digitalWrite(LEFT_MOUTH_LED, LOW);
    delay(speed);
  }
}


void talk_3(int speed, int talkLength) {
  for (int i = 0; i < talkLength; i++) {
    digitalWrite(RIGHT_MOUTH_LED, LOW);
    digitalWrite(MIDDLE_MOUTH_LED, HIGH);
    digitalWrite(LEFT_MOUTH_LED, HIGH);
    delay(speed);
    digitalWrite(RIGHT_MOUTH_LED, HIGH);
    digitalWrite(MIDDLE_MOUTH_LED, LOW);
    digitalWrite(LEFT_MOUTH_LED, HIGH);
    delay(speed);
    digitalWrite(RIGHT_MOUTH_LED, HIGH);
    digitalWrite(MIDDLE_MOUTH_LED, HIGH);
    digitalWrite(LEFT_MOUTH_LED, LOW);
    delay(speed);
  }
}

/**
   Sourir
*/
void smile() {
  digitalWrite(MIDDLE_MOUTH_LED, LOW);
  digitalWrite(RIGHT_MOUTH_LED, LOW);
  digitalWrite(LEFT_MOUTH_LED, LOW);
}


/**
   Dubitatif
*/
void doubtFulLeft() {
  digitalWrite(LEFT_EYE_LED, LOW);
  analogWrite(RIGHT_EYE_LED, 251);
  digitalWrite(RIGHT_MOUTH_LED, HIGH);
  digitalWrite(MIDDLE_MOUTH_LED, HIGH);
  digitalWrite(LEFT_MOUTH_LED, LOW);
}

void doubtFulRight() {
  digitalWrite(RIGHT_EYE_LED, LOW);
  analogWrite(LEFT_EYE_LED, 251);
  digitalWrite(RIGHT_MOUTH_LED, LOW);
  digitalWrite(MIDDLE_MOUTH_LED, HIGH);
  digitalWrite(LEFT_MOUTH_LED, HIGH);
}
