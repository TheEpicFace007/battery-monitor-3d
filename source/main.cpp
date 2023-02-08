#include <3ds.h>
#include <iostream>
#include "battery.h"
#include "utility.h"
#include <citro2d.h>
#include <citro3d.h>
#include <thread>

const u32 C_NeonGreen = C2D_Color32(0x00, 0xFF, 0x00, 0xFF);
const u32 C_Green = C2D_Color32(0x00, 0x80, 0x00, 0xFF);
const u32 C_LightGreen = C2D_Color32(0x90, 0xEE, 0x90, 0xFF);
const u32 C_Yellow = C2D_Color32(0xFF, 0xFF, 0x00, 0xFF);
const u32 C_Orange = C2D_Color32(0xFF, 0xA5, 0x00, 0xFF);
const u32 C_Red = C2D_Color32(0xFF, 0x00, 0x00, 0xFF);

bool statusPrintingLoop = true;
void statusPrinintLoopTh(void*) {
	std::cout << "Battery: " << (int)getBatteryPercentage() << "%" << std::endl;
	std::cout << "Charging state: " << chargingStateToString(checkChagringState()) << std::endl;
	std::cout << "Charger plugged in: " << (isChargerPluggedIn() ? "Yes" : "No") << std::endl;
}

C2D_TextBuf staticBuf, dynamicBuf;
C2D_Text batteryPercentageText, batteryLevelText;

void sceneInit() {
	staticBuf = C2D_TextBufNew(4096);
	dynamicBuf = C2D_TextBufNew(4096);

	C2D_TextParse(&batteryLevelText, staticBuf, "Battery level:");\
	C2D_TextOptimize(&batteryLevelText);
}

void sceneRender() {
	C2D_TextBufClear(dynamicBuf);

	// Display battery percentage
	char batPercentage[10];
	snprintf(batPercentage, 10, "%d%%", getBatteryPercentage());
	
	C2D_TextParse(&batteryPercentageText, dynamicBuf, batPercentage);
	C2D_TextOptimize(&batteryPercentageText);
	C2D_DrawText(&batteryPercentageText, C2D_AlignCenter, 200.0, (240 / 2) + 10, 0, 0.8, 0.8, 0.5f);
	ChargingState state = checkChagringState();
	// Display "Battery level:" over the battery percentage
	C2D_DrawText(&batteryLevelText, C2D_AlignCenter, 200.0, (240 / 2) - 30, 0, 1, 1, 0.5f);
}

void sceneExit() {
	C2D_TextBufDelete(staticBuf);
	C2D_TextBufDelete(dynamicBuf);
}


int main(int argc, char **argv) {
	gfxInitDefault();
	mcuHwcInit();
	ptmuInit();
	C3D_Init(C3D_DEFAULT_CMDBUF_SIZE);
	C2D_Init(C2D_DEFAULT_MAX_OBJECTS);
	C2D_Prepare();
	// Create screens
	C3D_RenderTarget* top = C2D_CreateScreenTarget(GFX_TOP, GFX_LEFT);
	C3D_RenderTarget* bottom = C2D_CreateScreenTarget(GFX_BOTTOM, GFX_LEFT);
	// Initialize the scene
	sceneInit();

	while (aptMainLoop()){
		hidScanInput();

		u32 kDown = hidKeysDown();
		u32 kHeld = hidKeysHeld();
		if (kDown & KEY_START)
			break;

		// Render the scene
		C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
		u32 colorToRender = C_NeonGreen;
		if (getBatteryPercentage() < 90 && getBatteryPercentage() >= 80) {
			colorToRender = C_Green;
		} else if (getBatteryPercentage() < 80 && getBatteryPercentage() >= 50) {
			colorToRender = C_LightGreen;
		} else if (getBatteryPercentage() < 50 && getBatteryPercentage() >= 25) {
			colorToRender = C_Yellow;
		} else if (getBatteryPercentage() < 25 && getBatteryPercentage() >= 10) {
			colorToRender = C_Orange;
		} else if (getBatteryPercentage() < 10) {
			colorToRender = C_Red;
		}
		C2D_SceneBegin(top); 
		C2D_TargetClear(top, colorToRender);
		sceneRender();
		C2D_SceneBegin(bottom);
		C2D_TargetClear(bottom, colorToRender);
		C2D_SceneBegin(bottom);
		C3D_FrameEnd(0);
	}
	sceneExit();
	statusPrintingLoop = false;
	C3D_Fini();
	ptmuExit();
	mcuHwcExit();
	gfxExit();
	return 0;
}