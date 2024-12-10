#include "ChamberController.h"

ChamberController::CamberController() : currentState(SystemState::IDLE) {}

bool ChamberController::Initialize() {
    if (!sensors.Initialize() || !actuators.Initialize()) {
        currentState = SystemState::ERROR;
        return false;
    }

    currentState = SystemState::INITIALIZING;
    return true;
}

void ChamberController::Run() {
    while (currentState != SystemState::ERROR && currentState != SystemState::EMERGENCY_STOP) {
        SensorData data = sensors.ReadAllSensors();

        if (!safetyManager.CheckSafety(data)) {
            EmergencyStop();
            break;
        }

        processManager.UpdateProcess(data);
        UpdateState();

        // Configurable timing delay
        static const uint32_t CONTROL_LOOP_MS = 100;    // 100ms control loop delay
        uint32_t elapsedTime = OSTimeGet() - loopStartTime;
        if (elapsedTime < CONTROL_LOOP_MS)  {
            OSTimeDly(CONTROL_LOOP_MS - elapsedTime);
        }
        loopStartTime = OSTimeGet();
    }
}

void ChamberController::EmergencyStop() {
    currentState = SystemState::EMERGENCY_STOP;
    actuators.EmergencyShutdown();
}

SystemState ChamberController::GetState() const {
    return currentState;
}

SensorData ChamberController::GetSensorData() const {
    return sensors.ReadAllSensors();
}