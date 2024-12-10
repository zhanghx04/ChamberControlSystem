#include "Actuators.h"
#include <stdio.h>

Actuators::Actuators() :
    pumpState(false),
    ventState(false),
    heaterState(false) {}

bool Actuators::Initialize() {
    // Initialize actuator hardware
    return true;
}

void Actuators::SetPump(bool state) {
    pumpState = state;
}

void Actuators::SetHeater(bool state) {
    heaterState = state;
}

void Actuators::SetVent(bool state) {
    ventState = state;
}

void Actuators::EmergencyShutdown() {
    SetPump(false);
    SetHeater(false);
    SetVent(true);  // Vent to release pressure
}