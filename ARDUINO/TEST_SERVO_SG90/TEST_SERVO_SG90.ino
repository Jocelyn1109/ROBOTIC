/*
  Jocelyn GIROD
  18/06/2024

  Test du servo SG90 avec la bibliothèque Servo Arduino.
*/

#include <Servo.h>
Servo servo_1{};
uint8_t servo_1_pin = 9;
bool start_test = true;

void setup() {
  Serial.begin(19200);
  servo_1.attach(servo_1_pin);
  servo_1.write(0);
}

void loop() {

  // Lecture des commandes sur le port série.
  // On attend plusieurs types de commandes:
  // - 0 pour 0°, 90 pour 90° et 180 pour 180°
  String command = "";
  if (Serial.available() > 0) {
    command = Serial.readString();
    command.trim();
    command.toUpperCase();
    Serial.print(F("Commande reçue: "));
    Serial.println(command);
  }

  if (command == "0") {
    servo_1.write(0);
  } else if (command == "90") {
    servo_1.write(90);
  } else if (command == "180") {
    servo_1.write(180);
  }

  // if (start_test) {
  //   for (int i = 0; i <= 180; i++) {
  //     servo_1.write(i);
  //     delay(5);
  //   }

  //   delay(25);

  //   for (int i = 180; i >= 0; i--) {
  //     servo_1.write(i);
  //     delay(5);
  //   }

  //   delay(25);

  //   for (int i = 0; i <= 90; i++) {
  //     servo_1.write(i);
  //     delay(5);
  //   }

  //   start_test = false;
  // }
}
