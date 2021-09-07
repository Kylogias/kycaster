#ifndef KYCASTER_AMMO_H
#define KYCASTER_AMMO_H

#include <stdint.h>

typedef struct KC_Ammo {
    uint32_t type;
    double x, y, z;
    uint32_t weapon;
    uint32_t amount;
} KC_Ammo;

#endif