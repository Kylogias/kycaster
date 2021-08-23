#ifndef KYCASTER_COMMON_H
#define KYCASTER_COMMON_H

#ifdef _WIN32
	#include <windows.h>
#endif

#include <stdint.h>
#include <malloc.h>
#include <stdio.h>

#ifdef __GNUC__
	#include <sys/stat.h> // May only work on MSYS2 MinGW-W64
#endif

char* KC_getExePath(uint64_t maxLength);
char* KC_OpenFile(char* name, uint64_t* size);

#endif