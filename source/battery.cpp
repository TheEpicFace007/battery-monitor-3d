#include "battery.h"

u8 getBatteryPercentage() {
    u8 level;
    MCUHWC_GetBatteryLevel(&level);
    return level;
}

bool isPluggedin() {
    u8 chargeState;
    PTMU_GetBatteryLevel(&chargeState);
    return chargeState == 1;
}

bool didFinishedCharging() {
    return isPluggedin() && getBatteryPercentage() == 100;
}