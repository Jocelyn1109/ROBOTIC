/**
 * Jocelyn GIROD - 21/06/2023
 * Logger on SD card.
 */

#include <Arduino.h>

#include "Logger.h"
#include "enum/LoggerLevel.hpp"

using namespace NSLoggerLevel;

/**
 * Default constructor
 * @param fileName the name of the log file (by default log.txt).
 */
Logger::Logger(String fileName) {
    fileName_ = fileName;
}

/**
 * Copy constructor
 *
 * @param other Logger object.
 */
Logger::Logger(const Logger &other) {}

/**
 * Destructor
 */
Logger::~Logger() = default;


/**
 * Initialize the logger.
 * @param scPinNumber: the CS pin number
 * @return 1 in case of error, otherwise 0.
 */
uint8_t Logger::loggerInitialization(uint8_t csPinNumber) {

    pinMode(csPinNumber, OUTPUT);

    if (!SD.begin(csPinNumber)) {
        return 1;
    }
    return 0;
}

/**
* Write communication message.
* @param message: the message to write.
* @return 1 in case of error, otherwise 0.
*/
uint8_t Logger::writeComMessage(String message) {
    logFile_ = SD.open(fileName_, FILE_WRITE);
    if (logFile_) {
        String comMessage = String(LoggerLevel::getTextFromEnum(EnumLevel::COMM) + ": " + message + ".");
        logFile_.println(comMessage);
        logFile_.close();
        return 0;
    } else {
        return 1;
    }
}

/**
  * Write information message.
  * @param message: the message to write.
  * @return 1 in case of error, otherwise 0.
  */
uint8_t Logger::writeInfoMessage(String message) {
    logFile_ = SD.open(fileName_, FILE_WRITE);
    if (logFile_) {
        String infoMessage = String(LoggerLevel::getTextFromEnum(EnumLevel::INFO) + ": " + message + ".");
        logFile_.println(infoMessage);
        logFile_.close();
        return 0;
    } else {
        return 1;
    }
}

/**
 * Write warning message.
 * @param message: the message to write.
 * @return 1 in case of error, otherwise 0.
  */
uint8_t Logger::writeWarningMessage(String message) {
    logFile_ = SD.open(fileName_, FILE_WRITE);
    if (logFile_) {
        String warnMessage = String(LoggerLevel::getTextFromEnum(EnumLevel::WARN) + ": " + message + ".");
        logFile_.println(warnMessage);
        logFile_.close();
        return 0;
    } else {
        return 1;
    }
}

/**
 * Write error message.
 * @param message: the message to write.
 * @return 1 in case of error, otherwise 0.
 */
uint8_t Logger::writeErrorMessage(String message) {
    logFile_ = SD.open(fileName_, FILE_WRITE);
    if (logFile_) {
        String errMessage = String(LoggerLevel::getTextFromEnum(EnumLevel::ERR) + ": " + message + ".");
        logFile_.println(errMessage);
        logFile_.close();
        return 0;
    } else {
        return 1;
    }
}

/**
 * Remove the log file
 * @return 0 in case of error, otherwise 1.
 */
uint8_t Logger::removeLogFile() {
    return SD.remove(fileName_);
}
