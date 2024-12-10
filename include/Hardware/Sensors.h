#ifndef SENSORS_H
#define SENSORS_H

#include "Types.h"

class Sensors {
public:
    Sensors();
    bool Initialize();
    SensorData ReadAllSensors();
    float ReadTemperature();
    float ReadPressure();
    float ReadHumidity();

private:
    void CalibrateSensors();
    bool ValidateReading(float value, float min, float max);
};

#endif // SENSORS_H