#pragma once
#include <3ds.h>
#include <string>

enum class ChargingState {
    Charging,
    NotCharging,
    FullyCharged
};


std::string chargingStateToString(ChargingState state);
u8 getBatteryPercentage();
bool isChargerPluggedIn();
ChargingState checkCharingState();