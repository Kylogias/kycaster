#ifndef KYCASTER_ENEBEAN_H
#define KYCASTER_ENEBEAN_H

#include <stdint.h>

typedef struct KC_Enebean {
    uint32_t type;
    double x, y, z;
    float pitch, yaw;
} KC_Enebean;

#endif