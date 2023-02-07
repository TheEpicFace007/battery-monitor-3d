#include <3ds.h>
#include <iostream>
#include "battery.h"
#include "utility.h"

int main(int argc, char **argv) {
	gfxInitDefault();
	mcuHwcInit();
	ptmuInit();
	consoleInit(GFX_TOP, NULL);


	while (aptMainLoop()){
		hidScanInput();

		u32 kDown = hidKeysDown();
		if (kDown & KEY_START)
			break;
		// Clear the screen
		for (int i = 0; i < 30; i++)
			std::cout << std::endl;
		std::cout << "Battery: " << getBatteryPercentage() << "%" << std::endl;
		std::cout << "Charging state: " << chargingStateToString(checkChagringState()) << std::endl;
		std::cout << "Charger plugged in: " << (isChargerPluggedIn() ? "Yes" : "No") << std::endl;
		std::cout << "Press START to exit." << std::endl;


		gfxFlushBuffers();
		gfxSwapBuffers();
		gspWaitForVBlank();
	}
	
	ptmuExit();
	mcuHwcExit();
	gfxExit();
	return 0;
}