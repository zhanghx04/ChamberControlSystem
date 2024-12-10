#ifndef CONFIG_H
#define CONFIG_H

namespace Config {
    // Network Configuratjion
    constexpr char SERVER_IP[] = "192.168.1.100";
    constexpr int SERVER_PORT = 502;

    // Hardware Configuration
    constexpr int MAX_TEMPERATURE = 200; // Celsius 
    constexpr int MAX_PRESSURE = 1000;   // kPa
    constexpr int MAX_HUMIDITY = 100;    // %
    constexpr int SAMPLING_RATE = 100;   // ms 

    // Safety Threshold
    constexpr float TEMP_WARNING_THRESHOLD = 180.0f;
    constexpr float PRESSURE_WARNING_THRESHOLD = 900.0f;
    constexpr float HUMIDITY_WARNING_THRESHOLD = 90.0f;
    constexpr float ATMOSPHERIC_PRESSURE = 101.325; // kPa
}

#endif // CONFIG_H
