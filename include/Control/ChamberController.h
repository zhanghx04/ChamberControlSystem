#ifndef CHAMBER_CONTROLLER_H
#define CHAMBER_CONTROLLER_H

#include "Types.h"
#include "Sensors.h"
#include "Actuators.h"
#include "SafetyManager.h"
#include "ProcessManager.h"

class ChamberController {
public:
    ChamberController();
    bool Initialize();
    void Run();
    void Stop();
    void EmergencyStop();

    SystemState GetState() const;
    SensorData GetSensorData() const;

private:
    SystemState currentState;
    Sensors sensors;
    Actuators actuators;
    SafetyManager safetyManager;
    ProcessManager processManager;
    uint32_t loopStartTime;

    void UpdateState();
    void HandleError();
}

#endif // CHAMBER_CONTROLLER_H