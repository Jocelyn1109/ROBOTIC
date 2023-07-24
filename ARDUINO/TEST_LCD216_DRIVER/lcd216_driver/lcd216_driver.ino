/*
  Jocelyn GIROD
  24/07/2023

  Programme de test de la librairie Lcd216Driver:
  - goHome(),
  - setbacklightColor(...),
  - writeMessage(...),
  - clearScreen(),
  - autoScrollOff().
*/

#include "Lcd216Driver.h"

const uint8_t RX_PIN = 0;
const uint8_t TX_PIN = 2;

Lcd216Driver lcd216Driver(RX_PIN, TX_PIN);

bool start_test = true;



void setup() {

  // Initialisation du terminal serie
  Serial.begin(19200);

  lcd216Driver.autoScrollOff();

}

void loop() {

  if (start_test) {
    
    lcd216Driver.goHome();

    // Green backlight color R:0, G:153, B:0
    lcd216Driver.setbacklightColor(0, 153, 0);
    String okMessage("OK MESSAGE");
    lcd216Driver.writeMessage(okMessage);

    delay(2000);
    lcd216Driver.clearScreen();

    // Red backlight color R:204, G:0, B:0
    lcd216Driver.setbacklightColor(204, 0, 0);
    String errorMessage("ERROR MESSAGE");
    lcd216Driver.writeMessage(errorMessage);

    delay(2000);
    lcd216Driver.clearScreen();

    // Blue backlight color R:204, G:0, B:0
    lcd216Driver.setbacklightColor(0, 102, 204);
    String infoMessage("INFORMATION MESSAGE");
    lcd216Driver.writeMessage(infoMessage);

    delay(5000);
    lcd216Driver.clearScreen();
    lcd216Driver.setbacklightColor(255, 255, 255);
    start_test = false;
  }
}
