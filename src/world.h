#ifndef KYCASTER_WORLD_H
#define KYCASTER_WORLD_H

#include "common.h"
#include <stdint.h>

typedef union KC_Entity KC_Entity;

typedef struct KC_WorldState {
    union KC_Entity* ents;
    KC_Map map;
    uint8_t*** geommap;
    uint32_t gmapX, gmapY, gmapZ;
} KC_WorldState;

#endif