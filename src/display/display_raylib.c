#if 1

#include "display.h"
#include "../../inc/raylib.h"

void KC_CreateWindow(char* title, uint32_t width, uint32_t height) { 
	InitWindow(width, height, title);
	SetExitKey(KEY_NULL);
	BeginDrawing();
}

void KC_DrawLine(uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2, uint32_t color) { DrawLine(x1, y1, x2, y2, GetColor(color)); }
void KC_SetPixel(uint32_t x, uint32_t y, uint32_t color) { DrawPixel(x, y, GetColor(color)); }
void KC_SwapBuffers(uint32_t color) {
	EndDrawing();
	BeginDrawing();
	ClearBackground(GetColor(color));
}

uint8_t KC_PollEvents() { return 0; } // Raylib handles this?
uint8_t KC_GetWindowRunning() { return !WindowShouldClose(); }

#endif