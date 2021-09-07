#ifndef KYCASTER_SCRIPTAPI_H
#define KYCASTER_SCRIPTAPI_H

#include "../../common.h"
#include <stdint.h>
#include <stdio.h>

// #define KYCASTER_SCRIPTAPI_USE_UMKA
// #define KYCASTER_SCRIPTAPI_USE_LUA

typedef struct KC_Scriptable {
    uint32_t type;
    void* script;
} KC_Scriptable;

#endif