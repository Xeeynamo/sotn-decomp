// SPDX-License-Identifier: AGPL-3.0-or-later
/*
 * File: chi.h
 * Overlay: CHI
 * Description: Abandoned Mine
 */

#ifndef CHI_H
#define CHI_H

#include "stage.h"

#define STAGE_IS_CHI

#define OVL_EXPORT(x) CHI_##x

#define CASTLE_FLAG_BANK 0x52

typedef enum {
    /* 0x00 */ E_NONE,
    /* 0x01 */ E_BREAKABLE,
    /* 0x02 */ E_EXPLOSION,
    /* 0x03 */ E_PRIZE_DROP,
    /* 0x04 */ E_NUMERIC_DAMAGE,
    /* 0x05 */ E_RED_DOOR,
    /* 0x06 */ E_INTENSE_EXPLOSION,
    /* 0x07 */ E_SOUL_STEAL_ORB,
    /* 0x08 */ E_ROOM_FOREGROUND,
    /* 0x09 */ E_STAGE_NAME_POPUP,
    /* 0x0A */ E_EQUIP_ITEM_DROP,
    /* 0x0B */ E_RELIC_ORB,
    /* 0x0C */ E_HEART_DROP,
    /* 0x0D */ E_ENEMY_BLOOD,
    /* 0x0E */ E_SAVE_GAME_POPUP,
    /* 0x0F */ E_DUMMY_0F,
    /* 0x10 */ E_DUMMY_10,
    /* 0x11 */ E_BACKGROUND_BLOCK,
    /* 0x12 */ E_CAMERA_LOCK,
    /* 0x13 */ E_PARTICLE_TRAIL,
    /* 0x14 */ E_ID_14,
    /* 0x15 */ E_GREY_PUFF,
    /* 0x16 */ E_DEMON_SWITCH_WALL,
    /* 0x17 */ E_DEMON_SWITCH,
    /* 0x18 */ E_BREAKABLE_WALL,
    /* 0x19 */ E_BREAKABLE_WALL_DEBRIS,
    /* 0x1A */ E_BREAKABLE_DEBRIS,
    /* 0x1B */ E_CERBERUS_GATE_DEBUG,
    /* 0x1C */ E_FALLING_STAIRS,
    /* 0x1D */ E_FALLING_STEP,
    /* 0x1E */ E_GREMLIN,
    /* 0x1F */ E_GREMLIN_EFFECT,
    /* 0x20 */ E_GREMLIN_FIRE,
    /* 0x21 */ E_SALEM_WITCH,
    /* 0x22 */ E_SALEM_WITCH_GLOW,
    /* 0x23 */ E_SALEM_WITCH_CURSE,
    /* 0x24 */ E_SALEM_WITCH_TRIBOLT_LAUNCH,
    /* 0x25 */ E_SALEM_WITCH_TRIBOLT_PROJECTILE,
    /* 0x26 */ E_THORNWEED,
    /* 0x27 */ E_CORPSEWEED,
    /* 0x28 */ E_CORPSEWEED_PROJECTILE,
    /* 0x29 */ E_VENUS_WEED,
    /* 0x2A */ E_VENUS_WEED_FLOWER,
    /* 0x2B */ E_VENUS_WEED_TENDRIL,
    /* 0x2C */ E_VENUS_WEED_DART,
    /* 0x2D */ E_VENUS_WEED_SPIKE,
} EntityIDs;

extern PfnEntityUpdate PfnEntityUpdates[];

extern EInit OVL_EXPORT(EInitBreakable);
extern u16 g_EInitObtainable[];
extern u16 g_EInitParticle[];
extern u16 g_EInitInteractable[];
extern u16 g_EInitUnkId13[];
extern u16 g_EInitUnkId12[];
extern u16 g_EInitCommon[];
extern u16 g_EInitDamageNum[];
extern u16 g_EInitSecret[];
extern u16 g_EInitSalemWitch[];
extern u16 g_EInitSalemWitchCurse[];
extern u16 g_EInitSalemWitchTribolt[];
extern u16 g_EInitGremlin[];
extern u16 g_EInitGremlinFire[];
extern u16 g_EInitThornweed[];
extern u16 g_EInitCorpseweed[];
extern u16 g_EInitCorpseweedProjectile[];
extern u16 g_EInitVenusWeedRoot[];
extern u16 g_EInitVenusWeedFlower[];
extern u16 g_EInitVenusWeedTendril[];
extern u16 g_EInitVenusWeedDart[];
extern ObjInit2 g_eBackgroundBlockInit[];

#endif
