#ifndef KYCASTER_DISPLAY_H
#define KYCASTER_DISPLAY_H

#include <stdint.h>

void KC_CreateWindow(char* title, uint32_t width, uint32_t height);
void KC_DrawLine(uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2, uint32_t color);
void KC_SetPixel(uint32_t x, uint32_t y, uint32_t color);
void KC_SwapBuffers(uint32_t color);
uint8_t KC_PollEvents();
uint8_t KC_GetWindowRunning();

#endif