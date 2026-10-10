// SPDX-License-Identifier: AGPL-3.0-or-later
#ifndef TEK_H
#define TEK_H
#define STAGE_IS_TEK

#include <stage.h>

enum Palettes {
    PAL_NONE = 0,
    PAL_DODO_BIRD = 0x200,
    PAL_BONE_SCIMITAR = 0x201,
    PAL_TOAD_FROG = 0x202,
    PAL_BONE_ARCHER = 0x204,
    PAL_GRAVE_KEEPER_TOMBSTONE = 0x208,
    PAL_CROW = 0x20A,
    PAL_JACK_O_BONES = 0x20C,
    PAL_BONE_HALBERD = 0x20E,
    PAL_YORICK = 0x20F,
    PAL_BLADE_MASTER = 0x210,
    PAL_BLADE_SOLDIER = 0x212,
    PAL_NOVA_SKELETON = 0x214,
    PAL_BONE_MUSKET = 0x219,
    PAL_WINGED_GUARD = 0x21D,
    PAL_SPECTRAL_SWORD = 0x21E,
    PAL_SPECTRAL_SWORD_WEAPON = 0x21F,
    PAL_VALHALLA_KNIGHT = 0x22E,
    PAL_DRAGON_RIDER = 0x231,
    PAL_OROBOUROUS = 0x233,
    PAL_BOMB_KNIGHT = 0x236,
    PAL_THORNWEED_CORPSEWEED = 0x23C,
    PAL_VENUS_WEED = 0x240,
};

typedef enum EntityID {
    /* 0x00 */ E_NONE,
    /* 0x01 */ E_BREAKABLE,                    // func_801BF424
    /* 0x02 */ E_EXPLOSION,                    // func_801C58C0
    /* 0x03 */ E_PRIZE_DROP,                   // func_801C5088
    /* 0x04 */ E_DAMAGE_DISPLAY,               // func_801C08EC
    /* 0x05 */ E_RED_DOOR,                     // func_801C1B6C
    /* 0x06 */ E_INTENSE_EXPLOSION,            // func_801C7844
    /* 0x07 */ E_SOUL_STEAL_ORB,               // func_801C2C28
    /* 0x08 */ E_ROOM_FOREGROUND,              // func_801C2788
    /* 0x09 */ E_STAGE_NAME_POPUP,             // func_801C8FD4
    /* 0x0A */ E_EQUIP_ITEM_DROP,              // func_801C5A94
    /* 0x0B */ E_RELIC_ORB,                    // func_801C6074
    /* 0x0C */ E_PERSISTENT_ITEM_DROP,         // func_801C6898
    /* 0x0D */ E_ENEMY_BLOOD,                  // func_801C3004
    /* 0x0E */ E_DUMMY_0E,                     // func_801C44CC
    /* 0x0F */ E_DUMMY_0F,                     // func_801C44CC
    /* 0x10 */ E_DUMMY_10,                     // func_801C44CC
    /* 0x11 */ E_BACKGROUND_BLOCK,             // func_801BEE30
    /* 0x12 */ E_LOCK_CAMERA,                  // func_801BEFC8
    /* 0x13 */ E_UNK_ID13,                     // func_801C6A90
    /* 0x14 */ E_EXPLOSION_VARIANTS,           // func_801C6DB8
    /* 0x15 */ E_GREY_PUFF,                    // func_801C6EA8
    /* 0x16 */ E_DODO_BIRD,                    // func_801CAC9C
    /* 0x17 */ E_BONE_SCIMITAR,                // func_801CB204
    /* 0x18 */ E_BONE_SCIMITAR_PARTS,          // func_801CB89C
    /* 0x19 */ E_TOAD,                         // func_801CB9A4
    /* 0x1A */ E_FROG,                         // func_801CC084
    /* 0x1B */ E_BONE_ARCHER,                  // func_801CC434
    /* 0x1C */ E_BONE_ARCHER_ARROW,            // func_801CCBFC
    /* 0x1D */ E_GRAVE_KEEPER,                 // func_801CCE90
    /* 0x1E */ E_GRAVE_KEEPER_HITBOX,          // func_801CD990
    /* 0x1F */ E_TOMBSTONE,                    // func_801CDA88
    /* 0x20 */ E_BLACK_CROW,                   // func_801CDCF8
    /* 0x21 */ E_BLUE_RAVEN,                   // func_801CE0AC
    /* 0x22 */ E_JACK_O_BONES,                 // func_801CE3F8
    /* 0x23 */ E_JACK_O_BONES_PIECES,          // func_801CE8D8
    /* 0x24 */ E_JACK_O_BONES_JACK,            // func_801CE9B8
    /* 0x25 */ E_BONE_HALBERD,                 // func_801CED54
    /* 0x26 */ E_BONE_HALBERD_ATTACK,          // func_801CF414
    /* 0x27 */ E_BONE_HALBERD_PIECES,          // func_801CF320
    /* 0x28 */ E_YORICK,                       // func_801CF4EC
    /* 0x29 */ E_YORICK_SKULL,                 // func_801CF9FC
    /* 0x2A */ E_YORICK_PIECES,                // func_801CFD2C
    /* 0x2B */ E_BLADE_MASTER,                 // func_801CFF04
    /* 0x2C */ E_BLADE_MASTER_ATTACK_HITBOX,   // func_801D082C
    /* 0x2D */ E_BLADE_MASTER_DEATH_PARTS,     // func_801D0940
    /* 0x2E */ E_BLADE_MASTER_DEATH_EXPLOSION, // func_801D0BA4
    /* 0x2F */ E_BLADE_SOLDIER,                // func_801D0DD8
    /* 0x30 */ E_BLADE_SOLDIER_ATTACK_HITBOX,  // func_801D14A4
    /* 0x31 */ E_BLADE_SOLDIER_DEATH_PARTS,    // func_801D13B0
    /* 0x32 */ E_NOVA_SKELETON,                // func_801D18A4
    /* 0x33 */ E_NOVA_LASER,                   // func_801D1E60
    /* 0x34 */ E_NOVA_LASER_PULSE,             // func_801D22EC
    /* 0x35 */ E_NOVA_SKELETON_PIECES,         // func_801D1D6C
    /* 0x36 */ E_BONE_MUSKET,                  // func_801D2464
    /* 0x37 */ E_BONE_MUSKET_UNK,              // func_801D2C00
    /* 0x38 */ E_WINGED_GUARD,                 // func_801D2EF0
    /* 0x39 */ E_WINGED_GUARD_PARTS,           // func_801D3160
    /* 0x3A */ E_SPECTRAL_SWORD_NO2,           // func_801DC5B0
    /* 0x3B */ E_SPECTRAL_SWORD_NO2_AURA,      // func_801DD314
    /* 0x3C */ E_POLTERGEIST,                  // func_801DD3E8
    /* 0x3D */ E_SPECTRAL_SWORD_DAI,           // func_801D3360
    /* 0x3E */ E_SPECTRAL_SWORD_DAI_AURA,      // func_801D3E08
    /* 0x3F */ E_SPECTRAL_SWORD_WEAPON,        // func_801D3EDC
    /* 0x40 */ E_VALHALLA_KNIGHT,              // func_801D41FC
    /* 0x41 */ E_VALHALLA_KNIGHT_UNK1,         // func_801D497C
    /* 0x42 */ E_VALHALLA_KNIGHT_UNK2,         // func_801D4AD4
    /* 0x43 */ E_SPECTRAL_SWORD_RDAI,          // func_801D4CD0
    /* 0x44 */ E_SPECTRAL_SWORD_RDAI_AURA,     // func_801D579C
    /* 0x45 */ E_SPEAR,                        // func_801D5870
    /* 0x46 */ E_SHIELD,                       // func_801D5E8C
    /* 0x47 */ E_OROBOUROUS,                   // func_801D6290
    /* 0x48 */ E_OROB_SEGMENT,                 // func_801D6A88
    /* 0x49 */ E_OROB_HEAD_PARTS,              // func_801D6D14
    /* 0x4A */ E_OROB_RIDER,                   // func_801D6E20
    /* 0x4B */ E_OROB_HOLY_ATTACKER,           // func_801D6FD4
    /* 0x4C */ E_DRAGON_RIDER,                 // func_801D7108
    /* 0x4D */ E_DRAGON_SEGMENT,               // func_801D758C
    /* 0x4E */ E_DRAGON_HEAD_PARTS,            // func_801D7810
    /* 0x4F */ E_DRAGON_RIDER_HITBOX,          // func_801D791C
    /* 0x50 */ E_VENUS_WEED_ROOT,              // func_801D7C68
    /* 0x51 */ E_VENUS_WEED_FLOWER,            // func_801D8504
    /* 0x52 */ E_VENUS_WEED_TENDRIL,           // func_801D8BE8
    /* 0x53 */ E_VENUS_WEED_DART,              // func_801D902C
    /* 0x54 */ E_VENUS_WEED_SPIKE,             // func_801D93C0
    /* 0x55 */ E_BOMB_KNIGHT,                  // func_801D95B4
    /* 0x56 */ E_THROWN_BOMB,                  // func_801D9D44
    /* 0x57 */ E_BOMB_KNIGHT_DEATH_PARTS,      // func_801DA550
    /* 0x58 */ E_BOMB_FUSE_SPARKS,             // func_801DA148
    /* 0x59 */ E_THROWN_ROCK,                  // func_801DA288
    /* 0x5A */ E_ROCK_PIECE,                   // func_801DA484
    /* 0x5B */ E_BOMB_KNIGHT_ARM,              // func_801DA6C0
    /* 0x5C */ E_THORNWEED,                    // func_801DA7D0
    /* 0x5D */ E_CORPSEWEED,                   // func_801DAB40
    /* 0x5E */ E_CORPSEWEED_PROJECTILE,        // func_801DB884
    NUM_ENTITIES,
} EntityID;

#endif
