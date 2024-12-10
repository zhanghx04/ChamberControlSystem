#include "SafetyManager.h"
#include <stdio.h>

SafetyManager::SafetyManager() : 
    emergencyStop(false), 
    lastCheckTime(0), 
    warningCount(0) {}

void SafetyManager::Initialize() {
    emergencyStop = false;
    lastCheckTime = OSTimeGet();
}

bool SafetyManager::CheckSafety(const SensorData &data) {
    if (emergencyStop) {
        return false;
    }

    bool isTemperatureSafe = CheckTemperature(data.temperature);
    bool isPressureSafe = CheckPressure(data.pressure);
    bool isHumiditySafe = CheckHumidity(data.humidity);

    lastCheckTime = OSTimeGet();

    if (!isTemperatureSafe || !isPressureSafe || !isHumiditySafe) {
        emergencyStop = true;
        LogSafetyEvent("Emergency Stop triggered");
        return false;
    }

    return true;
}

bool SafetyManager::CheckTemperature(float temperature) {
    if (temperature > Config::MAX_TEMPERATURE) {
        LogSafetyEvent("Temperature exceeded max limit");
        return false;
    }

    if (temperature > Config::TEMP_WARNING_THRESHOLD) {
        LogSafetyEvent("Temperature warning");
        warningCount++;
    }

    return true;
}

bool SafetyManager::CheckPressure(float pressure) {
    if (pressure > Config::MAX_PRESSURE) {
        LogSafetyEvent("Pressure exceeded max limit");
        return false;
    }

    if (pressure > Config::PRESSURE_WARNING_THRESHOLD) {
        LogSafetyEvent("Pressure warning");
        warningCount++;
    }

    return true;
}

bool SafetyManager::CheckHumidity(float humidity) {
    if (humidity > Config::MAX_HUMIDITY) {
        LogSafetyEvent("Humidity exceeded max limit");
        return false;
    }

    if (humidity > Config::HUMIDITY_WARNING_THRESHOLD) {
        LogSafetyEvent("Humidity warning");
        warningCount++;
    }

    return true;
}

void SafetyManager::LogSafetyEvent(const char *message) {
    iprintf("Safety Event: %s (Time: %lu)\n", message, OSTimeGet());
}