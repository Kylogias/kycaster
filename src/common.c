#include "common.h"

char* KC_getExePath(uint64_t maxLength)  {
	char* exePath = malloc(sizeof(char)*maxLength);
	#ifdef _WIN32
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