#include "battery.h"
#include <iostream>

u8 getBatteryPercentage() {
    u8 level;
    MCUHWC_GetBatteryLevel(&level);
    return level;
}

bool isChargerPluggedIn() {
    bool chargeState;
    PTMU_GetAdapterState(&chargeState);
    return chargeState;
}

bool didFinishedCharging() {
    return isChargerPluggedIn() && getBatteryPercentage() == 100;
}