#ifndef ACTUATORS_H
#define ACTUATORS_H

class Actuators {
public:
    Actuators();
    bool Initialize();

    void SetPump(bool state);
    void SetHeater(bool state);
    void SetVent(bool state);
    void EmergencyShutdown();

private:
    bool pumpState;
    bool heaterState;
    bool ventState;
};

#endif // ACTUATORS_H