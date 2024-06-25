/**
   Jocelyn GIROD
   14/12/2023
*/

#include "FrameManager.h"

FrameManager frameManager{};
unsigned long startTime;
unsigned long endTime;
char device;
char sub_device;
char function;
char functionValue;


void setup() {

  Serial.begin(19200);

}

void loop() {

  // Lecture des trames sur le port série.
  String frame = "";
  if (Serial.available() > 0) {
    startTime = millis();
    frame = Serial.readString();
    //Serial.print(F("Trame reçue: "));
    //Serial.println(frame);

    uint8_t f_size = frame.length();
    //Serial.print(F("Taille de la trame reçue: "));
    //Serial.println(f_size);

    if (f_size == 8) {
      char frameBuffer[8] = {};
      frame.toCharArray(frameBuffer, 8);
      uint8_t frameSize = sizeof(frameBuffer) / sizeof(char);

      frameManager.setFrame(&frameBuffer[0], frameSize);

      device = frameManager.getDevice();
      sub_device = frameManager.getSubDevice();
      function = frameManager.getFunction();
      functionValue = frameManager.getFunctionValue();

      endTime = millis();
      unsigned long timeDuration = endTime - startTime;
      Serial.print(F("Time duration: "));
      Serial.println(timeDuration);
    } else {
      Serial.print(F("Trame reçu incorrecte !"));
    }

    Serial.print(F("\nDevice: "));
    Serial.println(device);
    Serial.print(F("Sub Device: "));
    Serial.println(sub_device);
    Serial.print(F("Function: "));
    Serial.println(function);
    Serial.print(F("Function value: "));
    Serial.println(functionValue);
  }

}
