#ifndef PROCESS_MANAGER_H
#define PROCESS_MANAGER_H

#include "Types.h"
#include "Config.h"

class ProcessManager {
public:
    ProcessManager();
    void Initialize();
    void UpdateProcess(const SensorData& data);
    ProcessStep GetCurrentStep() const;
    bool IsProcessComplete() const;
    void StartProcess();
    void StopProcess();
    void EmergencyShutdown();

private:
    ProcessStep currentStep;
    bool processActive;
    uint32_t startTime;

    void TransitionToNextStep();
    bool CheckStepCompletion(const SensorData& data);
    void HandlePumpDown(const SensorData& data);
    void HandleProcess(const SensorData& data);
    void HandleVent(const SensorData& data);
};

#endif // PROCESS_MANAGER_H