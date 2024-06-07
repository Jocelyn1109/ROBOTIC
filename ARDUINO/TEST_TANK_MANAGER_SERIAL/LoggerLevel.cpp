/**
 * Jocelyn GIROD - 25/05/2023
 * Class for logger level.
 */

#include "LoggerLevel.hpp"

using namespace NSLoggerLevel;

/**
 * Default constructor
 */
LoggerLevel::LoggerLevel() {}

/**
 * Copy constructor
 *
 * @param other LoggerLevel object.
 */
LoggerLevel::LoggerLevel(const LoggerLevel &orig) {}

/**
 * Destructor
 */
LoggerLevel::~LoggerLevel() {}

/**
 * Get text from enum.
 * @param enumVal: the value of enum.
 * @return text.
 */
String LoggerLevel::getTextFromEnum(EnumLevel enumVal) {

    switch (enumVal) {
        case EnumLevel::INFO:
            return "Information";
        case EnumLevel::COMM:
            return "Communication";
        case EnumLevel::WARN:
            return "Warning";
        case EnumLevel::ERR:
            return "Error";
        default:
            return "";
    }
}
