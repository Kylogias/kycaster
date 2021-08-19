#ifndef KYCASTER_UMKA_WRAPPER_H
#define KYCASTER_UMKA_WRAPPER_H

#include <umka_api.h>
#include <stdint.h>

void KC_AddScript(char* name, uint32_t nameLen);
void KC_TickScripts();

#endif