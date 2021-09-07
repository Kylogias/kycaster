#include "../common.h"
#include <math.h>

#define KC_ZBUF_PRECISION 8

KC_Player KC_ConstructPlayer(double x, double y, double z, float yaw, float pitch, double fov) {
    KC_Player pl;
    pl.x = x;
    pl.y = y;
    pl.z = z;

    pl.dirX = cosf(yaw);
    pl.dirY = sinf(yaw);

    pl.projX = cosf(yaw + PI/2) * tan(fov);
    pl.projY = sinf(yaw + PI/2) * tan(fov);

    pl.type = KC_ENTTYPE_PLAYER;
    pl.projOff = tanf(pitch);
    
    pl.zBuf2D = malloc(sizeof(double* ));
    pl.zBuf2D[0] = malloc(sizeof(double) * KC_ZBUF_PRECISION);
    pl.zBufColors = malloc(sizeof(uint32_t* ));
    pl.zBufColors[0] = malloc(sizeof(uint32_t) * KC_ZBUF_PRECISION);

    pl.zBufSize = 1;

    KC_PlayerResizeZBuf(&pl);

    return pl;
}

void KC_DestructPlayer(KC_Player* pl) {
    for (uint64_t i = 0; i < pl->zBufSize; i++) {
        free(pl->zBuf2D[i]);
        free(pl->zBufColors[i]);
    }
    free(pl->zBuf2D);
    free(pl->zBufColors);
}

void KC_PlayerResizeZBuf(KC_Player* pl) {
    uint64_t winSize = KC_InputGetWindowSize();
    for (uint64_t i = 0; i < pl->zBufSize; i++) {
        free(pl->zBuf2D[i]);
        free(pl->zBufColors[i]);
    }
    pl->zBufSize = KC_WINDOWSIZE_WIDTH(winSize) * KC_WINDOWSIZE_HEIGHT(winSize);
    pl->zBuf2D = realloc(pl->zBuf2D, sizeof(double *) * pl->zBufSize);
    pl->zBufColors = realloc(pl->zBufColors, sizeof(uint32_t *) * pl->zBufSize);
    for (uint64_t i = 0; i < pl->zBufSize; i++) {
        pl->zBuf2D[i] = malloc(sizeof(double) * KC_ZBUF_PRECISION);
        pl->zBufColors[i] = malloc(sizeof(uint32_t) * KC_ZBUF_PRECISION);
    }
}

void KC_PlayerClearZBuf(KC_Player* pl) {
    for (uint64_t i = 0; i < pl->zBufSize; i++) {
        for (uint64_t j = 0; j < KC_ZBUF_PRECISION; j++) {
            if (pl->zBuf2D[i] == 0xBAADF00DBAADF00D) printf("BAD FOOD");
            pl->zBuf2D[i][j] = 10000000000.0;
            pl->zBufColors[i][j] = 0;
        }
    }
}

void KC_RenderWorld(KC_Player* pl, KC_WorldState* ws) {
    if (KC_InputGetWindowResized()) KC_PlayerResizeZBuf(pl);
    KC_PlayerClearZBuf(pl);

    KC_CastWalls(pl, ws);
    KC_CastFloorCeil(pl, ws);
    KC_DrawEntities(pl, ws);
}
void KC_CastWalls(KC_Player* pl, KC_WorldState* ws) {

}
void KC_CastFloorCeil(KC_Player* pl, KC_WorldState* ws) {

}
void KC_DrawEntities(KC_Player* pl, KC_WorldState* ws) {

}