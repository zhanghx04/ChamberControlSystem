#include <predef.h>
#include <stdio.h>
#include <ctype.h>
#include <startnet.h>
#include <dhcpclient.h>
#include <smarttrap.h>
#include <taskmon.h>
#include <NetworkDebug.h>

#include "ChamberController.h"
#include "NetworkManager.h"

const char *AppName = "ChamberControlSystem";

void UserMain(void *pd) {
    InitializeStack();
    GetDHCPAddress();
    OSChangePrio(MAIN_PRIO);
    EnableAutoUpdate();

    iprintf("Initializing Chamber Control System...\n");

    ChamberController chamberController;
    NetworkManager networkManager;

    if (!chamberController.Initialize() || !networkManager.Initialize()) {
        iprintf("Initialization failed. Exiting...\n");
        return;
    }  

    // Create tasks for different components
    OSTaskCreate(
        [](void *pd) {
            auto *c = (ChamberController *)pd;
            c->Run();
        },
        (void *)&chamberController,
        &Stack1[STACK_SIZE - 1],
        MAIN_PRIO
    );

    OSTaskCreate(
        [](void *pd) {
            auto *n = (NetworkManager *)pd;
            n->HandleIncommingMessage();
        },
        (void *)&networkManager,
        &Stack2[STACK_SIZE - 1],
        MAIN_PRIO + 1
    );

    // Main monitoring loop
    while (1) {
        SystemState state = chamberController.GetState();
        SensorData data = chamberController.GetSensorData();

        networkManager.SendStatus(state, data);

        // Log system status
        iprintf("State: %d, Temp: %.2f, Press: %.2f\n",
                static_cast<int>(state), 
                data.temperature, 
                data.pressure);

        OSTimeDly(TICKS_PER_SECOND);
    }
}