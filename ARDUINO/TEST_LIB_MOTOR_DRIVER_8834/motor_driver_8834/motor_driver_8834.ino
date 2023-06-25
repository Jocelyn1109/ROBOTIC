/*
  Jocelyn GIROD
  16/06/2023

  Test simple de fonctionnement du driver DRV8834 et du moteur pas à pas SY20STH30-0604A.
  Code testé et fonctionnel.
*/
const uint8_t DIR_PIN = 7;
const uint8_t STEP_PIN = 8;
const uint8_t SLEEP_PIN = 4;

bool start_test = true;

void setup() {

  Serial.begin(19200);
  Serial.println("Test DRV8834");

  pinMode(STEP_PIN, OUTPUT);
  pinMode(DIR_PIN, OUTPUT);
  pinMode(SLEEP_PIN, OUTPUT);
  digitalWrite(SLEEP_PIN, HIGH);
  digitalWrite(DIR_PIN, HIGH);  // Direction avant
  digitalWrite(STEP_PIN, LOW);  // Initialisation de la broche step
}

void loop() {

  int nbPas = 3000;

  if (start_test) {
    Serial.write("Start test");
    for (int i = 0; i < nbPas; i++) {
      digitalWrite(STEP_PIN, HIGH);
      delay(1);
      digitalWrite(STEP_PIN, LOW);
      delay(1);
    }

    delay(2000);

    digitalWrite(DIR_PIN, LOW);  // changement de direction

    for (int i = 0; i < nbPas; i++) {
      digitalWrite(STEP_PIN, HIGH);
      delay(1);
      digitalWrite(STEP_PIN, LOW);
      delay(1);
    }

    start_test = false;
  }
}
