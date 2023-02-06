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

ChargingState checkCharingState() {
    if (isChargerPluggedIn()) {
        if (getBatteryPercentage() == 100) {
            return ChargingState::FullyCharged;
        } else {
            return ChargingState::Charging;
        }
    } else {
        return ChargingState::NotCharging;
    }
}

std::string chargingStateToString(ChargingState state) {
    switch (state) {
        case ChargingState::Charging:
            return "Charging";
        case ChargingState::NotCharging:
            return "Not Charging";
        case ChargingState::FullyCharged:
            return "Fully Charged";
        default:
            return "Unknown";
    }
}