#ifndef KYCASTER_COMMON_H
#define KYCASTER_COMMON_H

// If you add any headers, put them under this comment, and if you need any headers, include this header
// All entities go before entdef.h

#include "map/kcm_format.h"
#include "map/map.h"

#include "world.h"

#include "entities/scriptapi/scriptable.h"
#include "entities/ammo.h"
#include "entities/enebean.h"
#include "entities/gun.h"
#include "entities/player.h"
#include "entities/prop.h"
#include "entities/entdef.h"

#include "platform/platform.h"


// Use "Namespaces" Raylib
#ifndef KC_PLATFORM_USE_RAYLIB
	#ifdef _WIN32
		#include <windows.h>
		#define KC_WIN32_AVAILABLE
	#endif
#endif

#include <stdint.h>
#include <malloc.h>
#include <stdio.h>

#include <time.h>

#ifdef __GNUC__
	#include <sys/stat.h> // May only work on MSYS2 MinGW-W64
#endif

#define PI 3.141592653589793238462643383

void KC_SetArguments(int argc, char* argv[]);
char* KC_GetExePath(uint64_t maxLength);
char* KC_OpenFile(char* name, uint64_t* size);
double KC_GetDelta();
void KC_UpdateDelta();

#endif