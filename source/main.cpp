#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <3ds.h>
#include <iostream>
#include "utility.h"
#include "battery.h"

int main(int argc, char* argv[]) {
	gfxInitDefault();
	consoleInit(GFX_TOP, NULL);

	// Main loop
	while (aptMainLoop()) {
		gspWaitForVBlank();
		gfxSwapBuffers();
		hidScanInput();

		// Your code goes here
		u32 kDown = hidKeysDown();
		if (kDown & KEY_START)
			break; // break in order to return to hbmenu
		
		// clear screen
		consoleClear();
		std::cout << "Battery: " << (int)getBatteryPercentage() << "%" << std::endl;
		std::cout << "Plugged in: " << (isPluggedIn() ? "Yes" : "No") << std::endl;
		if (isPluggedIn()) {
			std::cout << "Finished charging: " << (didFinishedCharging() ? "Yes" : "No") << std::endl;
		}
		sleep(1000);
	}

	gfxExit();
	return 0;
}
