#include "common.h"
#include <stdio.h>

int main(int argc, char* argv[]) {
	KC_SetArguments(argc, argv);
	KC_InitPlatform("Kycaster", 1280, 720);
	free(KC_GetExePath(1024));
	KC_Player pl = KC_ConstructPlayer(0, 0, 0, 0, 0, 90);
	KC_WorldState ws;
	while (KC_InputGetWindowRunning()) {
		KC_UpdateDelta();
		KC_RenderWorld(&pl, &ws);
		printf("%f\n", 1.0/KC_GetDelta());
		KC_InputPollEvents();
		KC_RenderSwapBuffers(0x3F3F3FFF);
	}
	return 0;
}