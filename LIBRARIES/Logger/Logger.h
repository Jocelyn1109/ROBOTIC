/**
 * Jocelyn GIROD - 21/06/2023
 * Logger on SD card.
 */

#ifndef _LOGGER_H_
#define _LOGGER_H_

#include <SPI.h>
#include <SD.h>


class Logger {

public:

    /**
     * Default constructor
     * @param fileName the name of the log file (by default log.txt).
     */
    Logger(String fileName);

    /**
    * Copy constructor
    *
    * @param other Logger object.
    */
    Logger(const Logger &other);

    /**
     * Destructor
     */
    ~Logger();

    /**
     * Initialize the logger.
     * @param scPinNumber: the CS pin number
     * @return 1 in case of error, otherwise 0.
     */
    uint8_t loggerInitialization(uint8_t csPinNumber);

    /**
     * Write communication message.
     * @param message: the message to write.
     * @return 1 in case of error, otherwise 0.
     */
    uint8_t writeComMessage(String message);

    /**
     * Write information message.
     * @param message: the message to write.
     * @return 1 in case of error, otherwise 0.
     */
    uint8_t writeInfoMessage(String message);

    /**
     * Write warning message.
     * @param message: the message to write.
     * @return 1 in case of error, otherwise 0.
     */
    uint8_t writeWarningMessage(String message);

    /**
     * Write error message.
     * @param message: the message to write.
     * @return 1 in case of error, otherwise 0.
     */
    uint8_t writeErrorMessage(String message);

    /**
     * Remove the log file
     * @return 0 in case of error, otherwise 1.
     */
    uint8_t removeLogFile();

private:

    File logFile_;
    String fileName_;
};

#endif //_LOGGER_H_
