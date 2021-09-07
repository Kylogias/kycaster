#ifndef KYCASTER_GUN_H
#define KYCASTER_GUN_H

#include <stdio.h>

typedef struct KC_Gun {
    uint32_t type;
    double x, y, z;
    uint32_t weapon;
} KC_Gun;

#endif