#ifndef ITEM_H
#define ITEM_H

#include "types.h"

typedef enum EquipKind {
    EQUIP_HAND,
    EQUIP_HEAD,
    EQUIP_ARMOR,
    EQUIP_CAPE,
    EQUIP_ACCESSORY,
    NUM_EQUIP_KINDS,
} EquipKind;

typedef enum {
    ITEM_S_SWORD,
    ITEM_SWORD,
    ITEM_THROW_1,
    ITEM_FIST,
    ITEM_CLUB,
    ITEM_TWOHAND,
    ITEM_FOOD,
    ITEM_BOMB,
    ITEM_THROW_2,
    ITEM_SHIELD,
    ITEM_MEDICINE,
    ITEM_END,
} ItemCategory;

typedef enum {
    SUBWPN_NONE,
    SUBWPN_DAGGER,
    SUBWPN_AXE,
    SUBWPN_HOLYWATER,
    SUBWPN_CROSS,
    SUBWPN_BIBLE,
    SUBWPN_STOPWATCH,
    SUBWPN_REBNDSTONE,
    SUBWPN_VIBHUTI,
    SUBWPN_AGUNEA
} SubWpnID;

extern s32 subWeapon; // g_SubweaponId

typedef struct {
    /* 0x00 */ u16** frames;   // all the animation frames
    /* 0x04 */ s8* frameProps; // hitboxes
    /* 0x08 */ u16 palette;    // palette modifier
    /* 0x0A */ u16 soundId;    // which sound effect to trigger
    /* 0x0C */ u8 frameStart;  // when the animation starts
    /* 0x0D */ u8 soundFrame;  // when the sound effect is triggered
    /* 0x0E */ s16 unused;     // reserved, always 0
} WeaponAnimation;
 /* size=0x8 */

#endif // ITEM_H
