#ifndef TYPES_H
#define TYPES_H

#include <cstdint>  // for uint32_t

enum class SystemState {
    IDLE,
    INITIALIZING,
    RUNNING,
    ERROR,
    MAINTENANCE,
    EMERGENCY_STOP
};

enum class ProcessStep {
    NONE,
    PUMP_DOWN,
    PROCESS,
    VENT,
    COMPLETE
};

struct SensorData {
    float temperature;
    float pressure;
    float humidity;
    uint32_t timestamp;
};

#endif // TYPES_H