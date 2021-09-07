#ifndef KYCASTER_PROP_H
#define KYCASTER_PROP_H

#include <stdint.h>

typedef struct KC_Prop {
    uint32_t type;
    double x, y, z;
    uint32_t texW, texH, frameW, frameH;
} KC_Prop;

#endif