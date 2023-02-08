#pragma once
#include <3ds.h>
#include <string>

enum class ChargingState {
    Charging,
    NotCharging,
    FullyCharged
};

/**
* Converts a ChargingState enum to a string
*/
std::string chargingStateToString(ChargingState state);
/*
* Gets the battery percentage
*/
u8 getBatteryPercentage();
/*
* Checks if the charger is plugged in
*/
bool isChargerPluggedIn();

/*
* Fetch the charging state
*/
ChargingState checkChagringState();