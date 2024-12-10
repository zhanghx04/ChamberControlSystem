#include "ProcessManager.h"
#include <stdio.h>

ProcessManager::ProcessManager() :
    currentStep(ProcessStep::NONE),
    processActive(false),
    startTime(0) {}

void ProcessManager::Initialize() {
    currentStep = ProcessStep::PUMP_DOWN;
    processActive = true;
    startTime = osGetTime();
}

void ProcessManager::UpdateProcess(const SensorData& data) {
    if (!processActive) {
        return ;
    }

    switch (currentStep) {
        case ProcessStep::PUMP_DOWN:
            HandlePumpDown(data);
            break;
        case ProcessStep::PROCESS:
            HandleProcess(data);
            break;
        case ProcessStep::VENT:
            HandleVent(data);
            break;
        default:
            break;
    }

    if (CheckStepCompletion(data)) {
        TransitionToNextStep();
    }
}

void ProcessManager::HandlePumpDown(const SensorData& data) {
    if (data.pressure < Config::PRESSURE_WARNING_THRESHOLD) {
        TransitionToNextStep();
    }
}

void ProcessManager::HandleProcess(const SensorData& data) {
    if (OSTimeGet() - startTime > Config::SAMPLING_RATE * 100) {
        TransitionToNextStep();
    }
}

void ProcessManager::HandleVent(const SensorData& data)  {
    if (data.pressure >= Config::ATMOSPHERIC_PRESSURE) {
        TransitionToNextStep();
    }
}

bool ProcessManager::CheckStepCompletion(const SensorData& data) {
    switch (currentStep) {
        case ProcessStep::PUMP_DOWN:
            return data.pressure < Config::PRESSURE_WARNING_THRESHOLD;
        case ProcessStep::PROCESS:
            return OSTimeGet() - startTime > Config::SAMPLING_RATE * 100;
        case ProcessStep::VENT:
            return data.pressure >= Config::ATMOSPHERIC_PRESSURE;
        default:
            return false;
    }
}

void ProcessManager::TransitionToNextStep() {
    switch (currentStep) {
        case ProcessStep::NONE:
            currentStep = ProcessStep::PUMP_DOWN;
            break;
        case ProcessStep::PUMP_DOWN:
            currentStep = ProcessStep::PROCESS;
            break;
        case ProcessStep::PROCESS:
            currentStep = ProcessStep::VENT;
            break;
        case ProcessStep::VENT:
            currentStep = ProcessStep::NONE;
            processActive = false;
            break;
        default:
            break;
    }

    startTime = OSTimeGet();
}