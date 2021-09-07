#ifndef KYCASTER_PLATFORM_H
#define KYCASTER_PLATFORM_H

#include <stdint.h>

// #define KC_PLATFORM_USE_NATIVE
// #define KC_PLATFORM_MSYS2_MINGW64_USE_X11_MINIAUDIO
// #define KC_PLATFORM_USE_SDL2
// #define KC_PLATFORM_USE_RAWDRAW_MINIAUDIO
#define KC_PLATFORM_USE_RAYLIB

#define KC_WINDOWSIZE_WIDTH(x) ((x & 0xFFFFFFFF00000000) >> 32)
#define KC_WINDOWSIZE_HEIGHT(x) (x & 0x00000000FFFFFFFF)

void KC_InitPlatform(char* title, uint32_t width, uint32_t height);
void KC_DeinitPlatform();

void KC_RenderDrawLine(uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2, uint32_t color);
void KC_RenderSetPixel(uint32_t x, uint32_t y, uint32_t color);
void KC_RenderBuffer(uint32_t* buf, uint32_t bufW, uint32_t bufH);
void KC_RenderSwapBuffers(uint32_t color);

uint8_t KC_InputPollEvents();
uint8_t KC_InputGetWindowRunning();
uint8_t KC_InputGetWindowResized();
uint64_t KC_InputGetWindowSize();

void KC_AudioSetMasterVolume(float volume);

#endif