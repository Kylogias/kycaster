#ifndef KYCASTER_ENTDEF_H
#define KYCASTER_ENTDEF_H

#include <stdint.h>
#include "../common.h"

typedef enum KC_WeaponType {
    KC_WEAPONTYPE_PISTOL, KC_WEAPONTYPE_SHOTGUN, KC_WEAPONTYPE_END
} KC_WeaponType;

typedef enum KC_EntTypes {
    KC_ENTTYPE_PLAYER, // Player
    KC_ENTTYPE_PROP, // Prop, doesn't rotate
    KC_ENTTYPE_ENEBEAN, // Enemy Bean

    KC_ENTTYPE_AMMO, // Any ammunition
    KC_ENTTYPE_GUN, // Any gun

    KC_ENTTYPE_SCRIPTABLE, // Script, likely using Umka API
    KC_ENTTYPE_END // End of EntTypes enum
} KC_EntTypes;

typedef union KC_Entity {
    uint32_t type;
    KC_Player pl;
    KC_Prop pr;
    KC_Enebean eb;
    KC_Ammo am;
    KC_Gun gn;
    KC_Scriptable sc;
} KC_Entity;

#endif