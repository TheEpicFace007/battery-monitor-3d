#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <3ds.h>
#include <iostream>
#include "utility.h"
#include "battery.h"
#include "string"
#include "3ds/imgui_citro3d.h"
#include "3ds/imgui_ctru.h"

void init() {
	gfxInitDefault();
	ptmuInit();
	mcuHwcInit();
	ndspInit();
}

void cleanup() {
	gfxExit();
	ptmuExit();
	mcuHwcExit();
	ndspExit();
}

int main(int argc, char* argv[]) {
	bool lastPluggedIn = isChargerPluggedIn();
	init();
	// Main loop
	while (aptMainLoop()) {

		// Initialize
		gspWaitForVBlank();
		gfxSwapBuffers();
		hidScanInput();
		

		// Your code goes here
		u32 kDown = hidKeysDown();
		if (kDown & KEY_START)
			break; // break in order to return to hbmenu
		// Check if the charger state changed
		if (lastPluggedIn != isChargerPluggedIn()) {
			lastPluggedIn = isChargerPluggedIn();
		}
		std::cout << "Battery: " << (int)getBatteryPercentage() << "%" << std::endl;
		std::cout << "Plugged in: " << (isChargerPluggedIn() ? "Yes" : "No") << std::endl;
		if (checkCharingState() == ChargingState::Charging || checkCharingState() == ChargingState::FullyCharged) {
			std::cout << "Finished charging: " << (checkCharingState() == ChargingState::FullyCharged ? "Yes" : "No") << std::endl;
		}
		sleep(1000);
	}
	cleanup();
	return 0;
}