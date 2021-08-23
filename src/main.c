#include "display/display.h"

int main(int argc, char* argv[]) {
	KC_CreateWindow("Kycaster", 1280, 720);
	while (KC_GetWindowRunning()) {
		KC_PollEvents();
		KC_SwapBuffers(0x3F3F3FFF);
	}
	return 0;
}