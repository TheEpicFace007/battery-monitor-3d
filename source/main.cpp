#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <3ds.h>
#include <iostream>
#include "utility.h"
#include "battery.h"
#include "string"

void playsound(std::string path);

void init() {
	gfxInitDefault();
	consoleInit(GFX_TOP, NULL);
	Result ptmuInitRes = ptmuInit();
	printf("ptmu initialization %s\n", R_FAILED(ptmuInitRes) == 0 ? "succeeded" : "failed");
	Result mcuhwcInitRes = mcuHwcInit();
	printf("mcuHwc initialization %s\n", R_FAILED(mcuhwcInitRes) == 0 ? "succeeded" : "failed");
	Result ndspInitRes = ndspInit();
	std::cout << "ndsp initialization " << (R_FAILED(ndspInitRes) == 0 ? "succeeded" : "failed") << std::endl;
}

void cleanup() {
	gfxExit();
	ptmuExit();
	mcuHwcExit();
	ndspExit();
}

bool lastPluggedIn = isChargerPluggedIn();
int main(int argc, char* argv[]) {
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
			if (isChargerPluggedIn()) {	
				playsound("romfs:/charing.opus");
			}
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

void playsound(std::string path) {
	ndspSetOutputMode(NDSP_OUTPUT_STEREO);
	ndspChnReset(0);
	ndspChnSetInterp(0, NDSP_INTERP_LINEAR);
	ndspChnSetRate(0, 44100.0f);
	ndspChnSetFormat(0, NDSP_FORMAT_STEREO_PCM16);
	FILE* file = fopen(path.c_str(), "rb");
	fseek(file, 0, SEEK_END);
	u32 size = ftell(file);
	fseek(file, 0, SEEK_SET);
	u8* buffer = (u8*)malloc(size);
	fread(buffer, 1, size, file);
	fclose(file);
	ndspChnWaveBufAdd(0, (ndspWaveBuf*)buffer);
}