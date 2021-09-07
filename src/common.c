#include "common.h"
#include <string.h>

int common_argc;
char** common_argv;
uint64_t KC_LastNsec = 0;
double KC_CurDelta = 0;

void KC_SetArguments(int argc, char* argv[]) {
	common_argc = argc;
	common_argv = argv;
}

char* KC_GetExePath(uint64_t maxLength)  {
	char* exePath = malloc(sizeof(char)*maxLength);
	#ifdef KC_PLATFORM_USE_RAYLIB
		strcpy_s(exePath, maxLength, GetDirectoryPath(common_argv[0]));
	#endif
	#ifdef KC_WIN32_AVAILABLE
		GetModuleFileNameA(NULL, (LPSTR)exePath, maxLength);
	#endif
	return exePath;
}

char* KC_OpenFile(char* name, uint64_t* size) {
	char* buf;
	
	FILE* fp;
	fopen_s(&fp, name, "r");
	if (fp) {
		uint64_t fsize;
		
		#ifdef __GNUC__
			struct stat64 info;
			stat64(name, &info);
			fsize = info.st_size;
		#else // Preferred to use the POSIX (aka GCC/MinGW-W64) version for 64-bit
			fseek(fp, 0, SEEK_END);
			fsize = ftell(fp);
		#endif
		
		buf = malloc((sizeof(char) * fsize) + 1);
		fseek(fp, 0, SEEK_SET);
		fread(buf, fsize, 1, fp);
		fclose(fp);
		
		buf[fsize] = '\0';
	}
	
	return buf;
}

double KC_GetDelta() {
	return KC_CurDelta;
}

void KC_UpdateDelta() {
	struct timespec tp;
	clock_gettime(CLOCK_MONOTONIC, &tp);

	KC_CurDelta = (double)(tp.tv_nsec - KC_LastNsec) / 1000000000.0;
	KC_LastNsec = tp.tv_nsec;
}