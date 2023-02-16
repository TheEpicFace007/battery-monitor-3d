#include <3ds.h>
#include <iostream>
#include "battery.h"
#include "utility.h"
#include <citro2d.h>
#include <citro3d.h>
#include <vector>
#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>
#include "ctr-led-brary.hpp"

const u32 C_NeonGreen = C2D_Color32(0x00, 0xFF, 0x00, 0xFF);
const u32 C_Green = C2D_Color32(0x00, 0x80, 0x00, 0xFF);
const u32 C_LightGreen = C2D_Color32(0x90, 0xEE, 0x90, 0xFF);
const u32 C_Yellow = C2D_Color32(0xFF, 0xFF, 0x00, 0xFF);
const u32 C_Orange = C2D_Color32(0xFF, 0xA5, 0x00, 0xFF);
const u32 C_Red = C2D_Color32(0xFF, 0x00, 0x00, 0xFF);

bool pluggedInSoundLoopRunning = true;
void pluggedInSoundLoop(void*);
bool ledIndicatorLoopRunning = true;
void ledIndicatorLoop(void*);

C2D_TextBuf staticBuf, dynamicBuf;
C2D_Text batteryPercentageText, batteryLevelText;
C2D_SpriteSheet spritesheet;
C2D_Sprite batterySprite;
constexpr float batterySpriteSize = 0.73;
void sceneInit() {
	staticBuf = C2D_TextBufNew(4096);
	dynamicBuf = C2D_TextBufNew(4096);

	C2D_TextParse(&batteryLevelText, staticBuf, "Battery level:");
	C2D_TextOptimize(&batteryLevelText);
	// Display the sprites
	C2D_SpriteFromSheet(&batterySprite, spritesheet, 1);
}

void sceneRender() {
	C2D_TextBufClear(dynamicBuf);

	// Display battery percentage
	char batPercentage[100];
	snprintf(batPercentage, 100, "%d%% (%s)", getBatteryPercentage(), chargingStateToString(checkChagringState()).c_str());
	
	C2D_TextParse(&batteryPercentageText, dynamicBuf, batPercentage);
	C2D_TextOptimize(&batteryPercentageText);
	C2D_DrawText(&batteryPercentageText, C2D_AlignCenter, 200.0, 215, 0, 0.8, 0.8, 0.5f);

	// Sprite drawing:
	int batterySpriteIndex;
	// Load the sprite from it's index. First thing we do is chec
	if (checkChagringState() == ChargingState::Charging || checkChagringState() == ChargingState::FullyCharged)
		batterySpriteIndex = 5;
	else if (getBatteryPercentage() <= 100 && getBatteryPercentage() >= 80)
		batterySpriteIndex = 4;
	else if (getBatteryPercentage() < 80 && getBatteryPercentage() >= 60)
		batterySpriteIndex = 3;
	else if (getBatteryPercentage() < 60 && getBatteryPercentage() >= 40)
		batterySpriteIndex = 2;
	else if (getBatteryPercentage() < 40 && getBatteryPercentage() >= 20)
		batterySpriteIndex = 1;
	else
		batterySpriteIndex = 0;
	C2D_SpriteFromSheet(&batterySprite, spritesheet, batterySpriteIndex);
	// Set the size, scale and etc...
	C2D_SpriteSetScale(&batterySprite, batterySpriteSize, batterySpriteSize);
	C2D_SpriteSetCenter(&batterySprite, 0.5, 0);
	C2D_SpriteSetPos(&batterySprite, 200, 25);
	// Draw the sprite
	C2D_DrawSprite(&batterySprite);
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
	romfsInit();
	newsInit();
	if (SDL_Init(SDL_INIT_AUDIO) < 0) {
		std::cout << "Error initializing SDL: " << SDL_GetError() << std::endl;
	}
	// Create screens
	C3D_RenderTarget* top = C2D_CreateScreenTarget(GFX_TOP, GFX_LEFT);
	consoleInit(GFX_BOTTOM, NULL);
	// Initialize and run threads
	s32 mainThreadPriority;
	svcGetThreadPriority(&mainThreadPriority, CUR_THREAD_HANDLE);
	Thread pluggedInSoundLoopThread = threadCreate(pluggedInSoundLoop, nullptr, 2048 * 4, mainThreadPriority-1,
													-1, true);
	Thread ledIndicatorThread = threadCreate(ledIndicatorLoop, nullptr, 1024, mainThreadPriority-2, -1, true);

	
	// Initialize sprites
	spritesheet = C2D_SpriteSheetLoad("romfs:/battery-sprites.t3x");
	if (!spritesheet)
		svcBreak(UserBreakType::USERBREAK_PANIC);
	// Initialize the scene
	sceneInit();

	while (aptMainLoop()){
		hidScanInput();

		u32 kDown = hidKeysDown();
		if (kDown & KEY_START)
			break;

		// Render the scene
		C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
		u32 colorToRender = C_NeonGreen;
		if (getBatteryPercentage() < 100 && getBatteryPercentage() >= 80) {
			colorToRender = C_Green;
		} else if (getBatteryPercentage() < 80 && getBatteryPercentage() >= 60) {
			colorToRender = C_LightGreen;
		} else if (getBatteryPercentage() < 60 && getBatteryPercentage() >= 40) {
			colorToRender = C_Yellow;
		} else if (getBatteryPercentage() < 40 && getBatteryPercentage() >= 20) {
			colorToRender = C_Orange;
		} else if (getBatteryPercentage() < 20 && getBatteryPercentage() > 0) {
			colorToRender = C_Red;
		}

		C2D_SceneBegin(top); 
		C2D_TargetClear(top, colorToRender);
		sceneRender();
		C3D_FrameEnd(0);
	}
	// Free things
	C2D_SpriteSheetFree(spritesheet);
	pluggedInSoundLoopRunning = false;
	threadJoin(pluggedInSoundLoopThread, U64_MAX);
	threadFree(pluggedInSoundLoopThread);
	ledIndicatorLoopRunning = false;
	threadJoin(ledIndicatorThread, U64_MAX);
	threadFree(ledIndicatorThread);
	// Deinit libs
	sceneExit();
	C3D_Fini();
	C2D_Fini();
	ptmuExit();
	mcuHwcExit();
	newsExit();
	gfxExit();
	romfsExit();
	SDL_Quit();
	return 0;
}

void pluggedInSoundLoop(void*){
	bool lastIsPluggedIn = isChargerPluggedIn();
	if (Mix_OpenAudio(44100, AUDIO_S16SYS, 2, 4096) < 0) {
		std::cout << "Error initializing SDL_Mixer: " << Mix_GetError() << std::endl;
	}
	Mix_Chunk *wav = Mix_LoadWAV("romfs:/plugged-in.wav");
	if (wav == NULL)
		std::cout << "Error loading plugged in sound: " << Mix_GetError() << std::endl;
	Mix_VolumeChunk(wav, 128);
	while (pluggedInSoundLoopRunning) {
		if (lastIsPluggedIn != isChargerPluggedIn()) {
			lastIsPluggedIn = isChargerPluggedIn();
			std::cout << "Charger is now " << (isChargerPluggedIn() ? "Plugged in" : "Not Plugged in") << std::endl;
			if (isChargerPluggedIn()) {
				if (Mix_PlayChannel(-1, wav, 0) < 0)
					std::cout << "Error playing plugged in sound: " << Mix_GetError() << std::endl;
			}
		}
	}
	delete wav;
	Mix_CloseAudio();
}


void ledIndicatorLoop(void*) {

	while (ledIndicatorLoopRunning){
		u8 batteryPercentage = getBatteryPercentage();
	}
}