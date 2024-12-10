#ifndef NETWORK_MANAGER_H
#define NETWORK_MANAGER_H

#include <tcp.h>

#include "Types.h"

class NetworkManager {
public:
    NetworkManager();
    bool Initialize();
    void SendStatus(const SystemState& state, const SensorData& data);
    void HandleIncommingMessage();

private:
    int socketFd;
    void ProcessCommand(const char *cmd);
};

#endif // NETWORK_MANAGER_H