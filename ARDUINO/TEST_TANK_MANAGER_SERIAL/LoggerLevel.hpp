/**
 * Jocelyn GIROD - 25/05/2023
 * Class for logger level.
 */

#ifndef LOGGER_LOGGERLEVEL_HPP
#define LOGGER_LOGGERLEVEL_HPP

#include <Arduino.h>
#include <stdint.h>
#include "EnumLevel.hpp"

class LoggerLevel {
public:

    /**
     * Default constructor
     */
    LoggerLevel();

    /**
     * Copy constructor
     *
     * @param other LoggerLevel object.
     */
    LoggerLevel(const LoggerLevel &orig);

    /**
     * Destructor
     */
    virtual ~LoggerLevel();

    /**
     * Get text from enum.
     * @param enumVal: the value of enum.
     * @return text.
     */
    static String getTextFromEnum(NSLoggerLevel::EnumLevel enumVal);

};


#endif //LOGGER_LOGGERLEVEL_HPP
