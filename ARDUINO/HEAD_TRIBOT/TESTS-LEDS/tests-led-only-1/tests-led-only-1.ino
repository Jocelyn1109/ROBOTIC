
/** Programme de tests tête TRIBOT - Leds */

//oeil gauche: fil bleu - oeil droit: fil turquoise
#define LEFT_EYE_LED 3
#define RIGHT_EYE_LED 5

//bouche milieu: fil rouge/droite: fil marron (nappe 1)/gauche: fil marron (nappe 2)
#define MIDDLE_MOUTH_LED 2
#define RIGHT_MOUTH_LED 4
#define LEFT_MOUTH_LED 6

#define DELAY_BETWEEN_EXECUTION 1000


bool isWakeUp = false;
bool isGoodBye = false;
bool isBlinkLeftEye = false;
bool isBlinkRightEye = false;
bool isBlinkTwoEyes = false;
bool isTalk = false;
bool isSmile = false;

void setup() {

  /* Attention ici HIGH = eteind et LOW = allumé
     Ceci vient du cablage de la tête         */

  /* Oeil droit et gauche */
  pinMode(LEFT_EYE_LED, OUTPUT);
  pinMode(RIGHT_EYE_LED, OUTPUT);
  digitalWrite(LEFT_EYE_LED, HIGH);
  digitalWrite(RIGHT_EYE_LED, HIGH);

  /* Bouche */
  pinMode(MIDDLE_MOUTH_LED, OUTPUT);
  pinMode(RIGHT_MOUTH_LED, OUTPUT);
  pinMode(LEFT_MOUTH_LED, OUTPUT);
  digitalWrite(MIDDLE_MOUTH_LED, HIGH);
  digitalWrite(RIGHT_MOUTH_LED, HIGH);
  digitalWrite(LEFT_MOUTH_LED, HIGH);

}

void loop() {

  //doubtFulLeft();
  //delay(3000);
  //doubtFulRight();

  if (isWakeUp) {
    wakeUp(5);
    isWakeUp = false;
  }

  delay(DELAY_BETWEEN_EXECUTION);

  reset();

  delay(DELAY_BETWEEN_EXECUTION);

  if (isBlinkLeftEye) {
    blinkLeftEye();
    isBlinkLeftEye = false;
  }

  delay(DELAY_BETWEEN_EXECUTION);

  if (isBlinkRightEye) {
    blinkRightEye();
    isBlinkRightEye = false;
  }

  delay(DELAY_BETWEEN_EXECUTION);

  if (isBlinkTwoEyes) {
    blinkTwoEyes();
    isBlinkTwoEyes = false;
  }

  delay(DELAY_BETWEEN_EXECUTION);

  if (isTalk) {
    for (int i = 0; i < 30; i++) {
      talk(100);
      delay(10);
    }

    isTalk = false;
  }

  delay(DELAY_BETWEEN_EXECUTION);

  reset();

  delay(DELAY_BETWEEN_EXECUTION);

  if (isSmile) {
    switchOnEyes();
    delay(60);
    smile();
    isSmile = false;
  }

  delay(DELAY_BETWEEN_EXECUTION);

  if (isGoodBye) {
    goodBye(5);
    isGoodBye = false;
  }

  delay(DELAY_BETWEEN_EXECUTION);

  reset();

}


/*************** FUNCTION *************************/

/*
   Eteind toutes les leds
*/
void reset() {
  digitalWrite(LEFT_EYE_LED, HIGH);
  digitalWrite(RIGHT_EYE_LED, HIGH);
  digitalWrite(MIDDLE_MOUTH_LED, HIGH);
  digitalWrite(RIGHT_MOUTH_LED, HIGH);
  digitalWrite(LEFT_MOUTH_LED, HIGH);
}

/*
   Réveil
*/
void wakeUp(int speed) {
  digitalWrite(LEFT_EYE_LED, HIGH);
  digitalWrite(RIGHT_EYE_LED, HIGH);
  for (int fadeValue = 255 ; fadeValue >= 0; fadeValue -= speed) {
    analogWrite(LEFT_EYE_LED, fadeValue);
    analogWrite(RIGHT_EYE_LED, fadeValue);
    delay(60);
  }
}

/*
   Au revoir !
*/
void goodBye(int speed) {
  for (int fadeValue = 0 ; fadeValue <= 255; fadeValue += speed) {
    analogWrite(LEFT_EYE_LED, fadeValue);
    analogWrite(RIGHT_EYE_LED, fadeValue);
    delay(60);
  }
}

/*
   Clignotement de l'oeil gauche
*/
void blinkLeftEye() {
  digitalWrite(LEFT_EYE_LED, LOW);
  digitalWrite(RIGHT_EYE_LED, LOW);

  delay(500);
  digitalWrite(LEFT_EYE_LED, HIGH);
  delay(100);
  digitalWrite(LEFT_EYE_LED, LOW);
}

/*
   Clignotement de l'oeil droit
*/
void blinkRightEye() {
  digitalWrite(LEFT_EYE_LED, LOW);
  digitalWrite(RIGHT_EYE_LED, LOW);

  delay(500);
  digitalWrite(RIGHT_EYE_LED, HIGH);
  delay(100);
  digitalWrite(RIGHT_EYE_LED, LOW);
}

/*
   Clignotement des deux yeux
*/
void blinkTwoEyes() {
  digitalWrite(LEFT_EYE_LED, LOW);
  digitalWrite(RIGHT_EYE_LED, LOW);

  delay(500);
  digitalWrite(LEFT_EYE_LED, HIGH);
  digitalWrite(RIGHT_EYE_LED, HIGH);
  delay(100);
  digitalWrite(LEFT_EYE_LED, LOW);
  digitalWrite(RIGHT_EYE_LED, LOW);
  delay(100);
  digitalWrite(LEFT_EYE_LED, HIGH);
  digitalWrite(RIGHT_EYE_LED, HIGH);
  delay(100);
  digitalWrite(LEFT_EYE_LED, LOW);
  digitalWrite(RIGHT_EYE_LED, LOW);

}

/**
   Parler
*/
void talk(int speed) {
  digitalWrite(MIDDLE_MOUTH_LED, LOW);
  digitalWrite(RIGHT_MOUTH_LED, LOW);
  digitalWrite(LEFT_MOUTH_LED, LOW);
  delay(speed);
  digitalWrite(MIDDLE_MOUTH_LED, HIGH);
  digitalWrite(RIGHT_MOUTH_LED, HIGH);
  digitalWrite(LEFT_MOUTH_LED, HIGH);
  delay(speed);
  digitalWrite(MIDDLE_MOUTH_LED, LOW);
  digitalWrite(RIGHT_MOUTH_LED, LOW);
  digitalWrite(LEFT_MOUTH_LED, LOW);
  delay(speed);
  digitalWrite(MIDDLE_MOUTH_LED, HIGH);
  digitalWrite(RIGHT_MOUTH_LED, HIGH);
  digitalWrite(LEFT_MOUTH_LED, HIGH);
}


/**
   Allumer les yeux
*/
void switchOnEyes() {
  digitalWrite(LEFT_EYE_LED, LOW);
  digitalWrite(RIGHT_EYE_LED, LOW);
}

/**
   Eteindre les yeux
*/
void switchOfEyes() {
  digitalWrite(LEFT_EYE_LED, HIGH);
  digitalWrite(RIGHT_EYE_LED, HIGH);
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
}

void doubtFulRight() {
  digitalWrite(RIGHT_EYE_LED, LOW);
  analogWrite(LEFT_EYE_LED, 251);
}
