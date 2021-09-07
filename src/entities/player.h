#ifndef KYCASTER_PLAYER_H
#define KYCASTER_PLAYER_H

#include <stdint.h>
#include "../common.h"

typedef struct KC_Player {
    uint32_t type;
    double x, y, z;
    double dirX, dirY;
    double projX, projY;
    float projOff;
    double** zBuf2D;
    uint32_t** zBufColors;
    uint64_t zBufSize;
} KC_Player;

KC_Player KC_ConstructPlayer(double x, double y, double z, float yaw, float pitch, double fov);
void KC_DestructPlayer(KC_Player* pl);
void KC_PlayerResizeZBuf(KC_Player* pl);
void KC_PlayerClearZBuf(KC_Player* pl);

void KC_RenderWorld(KC_Player* pl, KC_WorldState* ws);
void KC_CastWalls(KC_Player* pl, KC_WorldState* ws);
void KC_CastFloorCeil(KC_Player* pl, KC_WorldState* ws);
void KC_DrawEntities(KC_Player* pl, KC_WorldState* ws);
#endif