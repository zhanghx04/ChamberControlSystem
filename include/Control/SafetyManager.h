#ifndef SAFETY_MANAGER_H
#define SAFETY_MANAGER_H

#include "Types.h"
#include "Config.h"

class SafetyManager {
public:
    SafetyManager();
    void Initialize();
    bool CheckSafety(const SensorData &data);
    void ResetSafetyStatus();
    bool IsEmergencyStop() const;

private:
    bool emergencyStop;
    uint32_t lastCheckTime;
    uint32_t warningCount;

    bool CheckTemperature(float temperature);
    bool CheckPressure(float pressure);
    bool CheckHumidity(float humidity);
    void LogSafetyEvent(const char *message);
};

#endif // SAFETY_MANAGER_H