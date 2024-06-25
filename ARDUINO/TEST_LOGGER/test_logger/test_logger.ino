/*
  Jocelyn GIROD
  21/06/2023

  Programme de test de la librairie Logger sur carte SD.
*/

#include "Logger.h"

const uint8_t SC_PIN = 2;
Logger logger{String("log_1.txt")};
uint8_t resInit = 0;
bool start_test = true;
bool is_remove_file = false;

void testCard();

void setup() {

  // Initialisation du terminal serie
  Serial.begin(19200);

  //Initialisation du logger
  resInit = logger.loggerInitialization(SC_PIN);
  if (resInit != 0) {
    Serial.println(F("Erreur lors de l'initialisation du logger"));
  } else {
    Serial.println(F("Succès de l'initialisation du logger"));
  }

  //Test de la carte
  //testCard();
}

void loop() {

  if (start_test) {

    //Message de communication
    Serial.println(F("Message de communication"));
    uint8_t resWriteCom = logger.writeComMessage("Test message de communication");
    if (resWriteCom != 0) {
      Serial.println(F("Erreur lors de l'écriture du message de communication"));
    } else {
      Serial.println(F("Succès de l'écriture du message de communication"));
    }

    delay(2000);

    //Message d'information
    Serial.println(F("Message d'information"));
    uint8_t resWriteInfo = logger.writeInfoMessage("Test message d'information");
    if (resWriteInfo != 0) {
      Serial.println(F("Erreur lors de l'écriture du message d'information"));
    } else {
      Serial.println(F("Succès de l'écriture du message d'information"));
    }

    delay(2000);

    //Message de warning
    Serial.write("Message de warning\n");
    uint8_t resWriteWarn = logger.writeWarningMessage("Test message de warning");
    if (resWriteWarn != 0) {
      Serial.println(F("Erreur lors de l'écriture du message de warning"));
    } else {
      Serial.println(F("Succès de l'écriture du message de warning"));
    }

    delay(2000);

    //Message d'erreur
    Serial.println("Message d'erreur");
    uint8_t resWriteErr = logger.writeErrorMessage("Test message d'erreur");
    if (resWriteErr != 0) {
      Serial.println(F("Erreur lors de l'écriture du message d'erreur"));
    } else {
      Serial.println("Succès de l'écriture du message d'erreur");
    }

    delay(2000);

    start_test = false;
  }

  if (is_remove_file) {
    uint8_t resRemove = logger.removeLogFile();
    if (resRemove != 1) {
      Serial.println(F("Erreur lors de la suppression du fichier de log"));
    } else {
      Serial.println(F("Succès de la suppression du fichier de log"));
    }
    is_remove_file = false;
  }
}

/**
Fonction permettant de vérifier la carte SD.
Voir: https://arduino-france.site/sd-arduino/#4
*/
void testCard() {

  Sd2Card card;
  SdVolume volume;
  SdFile root;

  while (!card.init(SPI_HALF_SPEED, SC_PIN)) { Serial.println("initialization failed"); }

  Serial.print(F("\nCard type: "));
  switch (card.type()) {
    case SD_CARD_TYPE_SD1:
      Serial.println(F("SD1"));
      break;
    case SD_CARD_TYPE_SD2:
      Serial.println(F("SD2"));
      break;
    case SD_CARD_TYPE_SDHC:
      Serial.println(F("SDHC"));
      break;
    default:
      Serial.println(F("Unknown"));
  }

  if (!volume.init(card)) {
    Serial.println(F("Could not find FAT16/FAT32 partition.\nMake sure you've formatted the card"));
    return;
  }

  uint32_t volumesize;
  Serial.print(F("\nVolume type is FAT"));
  Serial.println(volume.fatType(), DEC);
  Serial.println();

  volumesize = volume.blocksPerCluster();
  volumesize *= volume.clusterCount();
  volumesize *= 512;

  Serial.print(F("Volume size (Kbytes): "));
  volumesize /= 1024;
  Serial.println(volumesize);

  Serial.print(F("Volume size (Mbytes): "));
  volumesize /= 1024;
  Serial.println(volumesize);

  Serial.println(F("\nFiles found on the card (name, date and size in bytes): "));
  root.openRoot(volume);

  root.ls(LS_R | LS_DATE | LS_SIZE);
}
