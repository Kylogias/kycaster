#include "../common.h"
#ifdef KC_PLATFORM_USE_RAYLIB

#include <raylib.h>

void KC_InitPlatform(char* title, uint32_t width, uint32_t height) { 
	InitWindow(width, height, title);
	SetWindowState(FLAG_WINDOW_RESIZABLE);
	InitAudioDevice();
	SetExitKey(KEY_NULL);
	BeginDrawing();
}

void KC_DeinitPlatform() {
	CloseWindow();
	CloseAudioDevice();
}

void KC_RenderDrawLine(uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2, uint32_t color) { DrawLine(x1, y1, x2, y2, GetColor(color)); }
void KC_RenderSetPixel(uint32_t x, uint32_t y, uint32_t color) { DrawPixel(x, y, GetColor(color)); }
void KC_RenderSwapBuffers(uint32_t color) {
	EndDrawing();
	BeginDrawing();
	ClearBackground(GetColor(color));
}

uint8_t KC_InputPollEvents() { return 0; } // Raylib handles this?
uint8_t KC_InputGetWindowRunning() { return !WindowShouldClose(); }
uint8_t KC_InputGetWindowResized() { return IsWindowResized(); }

uint64_t KC_InputGetWindowSize() { return ((uint64_t)(GetScreenWidth()) << 32) + (uint64_t)(GetScreenHeight()); }

void KC_AudioSetMasterVolume(float volume) {
	SetMasterVolume(volume);
}


#endif