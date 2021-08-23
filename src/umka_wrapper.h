#ifndef KYCASTER_UMKA_WRAPPER_H
#define KYCASTER_UMKA_WRAPPER_H

#include "../inc/umka_api.h"
#include "common.h"
#include <stdint.h>
#include <stdio.h>

void KC_AddScript(char* name);
void KC_RemoveScript(char* name);
void KC_TickScripts();
void KC_CallFN(char* name, char* fn);

#endif