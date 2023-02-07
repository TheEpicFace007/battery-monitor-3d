#include <3ds.h>
#include <iostream>
#include "battery.h"
#include "utility.h"
#include <citro2d.h>
#include <citro3d.h>

bool statusPrintingLoop = true;
void statusPrinintLoopTh(void*) {
	std::cout << "Battery: " << (int)getBatteryPercentage() << "%" << std::endl;
	std::cout << "Charging state: " << chargingStateToString(checkChagringState()) << std::endl;
	std::cout << "Charger plugged in: " << (isChargerPluggedIn() ? "Yes" : "No") << std::endl;
}

C2D_TextBuf staticBuf, dynamicBuf;
C2D_Text batteryPercentageText;

void sceneInit() {
	staticBuf = C2D_TextBufNew(4096);
	dynamicBuf = C2D_TextBufNew(4096);
}

void sceneRender() {
	C2D_TextBufClear(dynamicBuf);

	// Display battery percentage
	char batPercentage[10];
	snprintf(batPercentage, 10, "%d%%", getBatteryPercentage());
	
	C2D_TextParse(&batteryPercentageText, dynamicBuf, batPercentage);
	C2D_TextOptimize(&batteryPercentageText);
	C2D_DrawText(&batteryPercentageText, C2D_AlignCenter, 0, 0, 0, 0.5f, 0.5f, 0.5f);
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

	// Initialize the scene
	sceneInit();

	while (aptMainLoop()){
		hidScanInput();

		u32 kDown = hidKeysDown();
		u32 kHeld = hidKeysHeld();
		if (kDown & KEY_START)
			break;


		C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
		C2D_TargetClear(top, C2D_Color32(0x00, 0x00, 0x00, 0xFF));
		C2D_SceneBegin(top);
		sceneRender();
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