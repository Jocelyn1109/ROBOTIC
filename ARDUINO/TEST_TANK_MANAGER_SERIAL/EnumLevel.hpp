/**
 * Jocelyn GIROD - 25/05/2023
 * Enum for logger level.
 */

#ifndef LOGGER_ENUMLEVEL_HPP
#define LOGGER_ENUMLEVEL_HPP

#include <stdint.h>

namespace NSLoggerLevel {
    enum class EnumLevel : uint8_t {
        INFO,
        COMM,
        WARN,
        ERR
    };
}

#endif //LOGGER_ENUMLEVEL_HPP
