#pragma once
#include <3ds.h>

enum class ChargingState {
    Charging,
    NotCharging,
    FullyCharged
};

u8 getBatteryPercentage();
bool isChargerPluggedIn();
ChargingState checkCharingState();