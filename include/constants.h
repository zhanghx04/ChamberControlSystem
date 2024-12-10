#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <cstdint>
namespace Constants {
    // System timing constants
    constexpr uint32_t TICKS_PER_SECOND = 1000;
    constexpr uint32_t CONTROL_LOOP_MS = 100;
    constexpr uint32_t SENSOR_READ_MS = 50;
    constexpr uint32_t WATCHDOG_TIMEOUT_MS = 1000;

    // Hardware limits
    constexpr float MIN_TEMPERATURE = -50.0f;
    constexpr float MAX_TEMPERATURE = 200.0f;
    constexpr float MIN_PRESSURE = 0.0f;
    constexpr float MAX_PRESSURE = 1000.0f;
    constexpr float MIN_HUMIDITY = 0.0f;
    constexpr float MAX_HUMIDITY = 100.0f;

    // Control parameters
    constexpr float TEMP_TOLERANCE = 100.0f;
    constexpr float PRESSURE_TOLERANCE = 100.0f;
    constexpr float HUMIDITY_TOLERANCE = 10.0f;
}

#endif // CONSTANTS_H