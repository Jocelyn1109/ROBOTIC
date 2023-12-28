/*
  Jocelyn GIROD
  28/12/2023

  Programme de tests de l'éclairage avec une rampe de led
  et un module MOFSET.

*/

#define SIG 9

void setup() {

  Serial.begin(19200);
  pinMode(SIG, OUTPUT);

  //Lumière éteinte
  switchOffLight();
}

void loop() {

  // Lecture des commandes sur le port série.
  // On attend plusieurs types de commandes:
  // - LOW, MEDIUM, HIGH pour définir l'inensité de l'éclairage.
  // - OFF pour éteindre la rample de led.
  // - VAR, permet de faire varier l'intensité de la lumière e façon progressive.
  String command = "";
  if (Serial.available() > 0) {
    command = Serial.readString();
    command.trim();
    command.toUpperCase();
    Serial.print(F("Commande reçue: "));
    Serial.println(command);
  }

  if (command == "LOW") {
      lowLight();
    } else if (command == "MEDIUM") {
      mediumLight();
    } else if (command == "HIGH") {
      highLight();
    } else if (command == "OFF") {
      switchOffLight();
    } else if (command == "VAR") {
      lightVariation();
    } else {
      if (command != "") {
        Serial.println(F("Commande non reconnue !"));
      }
    }
}

void switchOffLight() {
  analogWrite(SIG, 0);
}

void lowLight() {
  analogWrite(SIG, 85);
}

void mediumLight() {
  analogWrite(SIG, 170);
}

void highLight() {
  analogWrite(SIG, 255);
}

void lightVariation() {

  int i;
  for (i = 0; i < 255; i++) {
    analogWrite(SIG, i);
    delay(30);
  }

  delay(5);

  for (i = 255; i > 0; i--) {
    analogWrite(SIG, i);
    delay(30);
  }

  switchOffLight();
}
