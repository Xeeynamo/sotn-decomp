// SPDX-License-Identifier: AGPL-3.0-or-later
#include "tek.h"

void func_801BF424(Entity* self);
void func_801C58C0(Entity* self);
void func_801C5088(Entity* self);
void func_801C08EC(Entity* self);
void func_801C1B6C(Entity* self);
void func_801C7844(Entity* self);
void func_801C2C28(Entity* self);
void func_801C2788(Entity* self);
void func_801C8FD4(Entity* self);
void func_801C5A94(Entity* self);
void func_801C6074(Entity* self);
void func_801C6898(Entity* self);
void func_801C3004(Entity* self);
void func_801C44CC(Entity* self);
void func_801BEE30(Entity* self);
void func_801BEFC8(Entity* self);
void func_801C6A90(Entity* self);
void func_801C6DB8(Entity* self);
void func_801C6EA8(Entity* self);
void func_801CAC9C(Entity* self);
void func_801CB204(Entity* self);
void func_801CB89C(Entity* self);
void func_801CB9A4(Entity* self);
void func_801CC084(Entity* self);
void func_801CC434(Entity* self);
void func_801CCBFC(Entity* self);
void func_801CCE90(Entity* self);
void func_801CD990(Entity* self);
void func_801CDA88(Entity* self);
void func_801CDCF8(Entity* self);
void func_801CE0AC(Entity* self);
void func_801CE3F8(Entity* self);
void func_801CE8D8(Entity* self);
void func_801CE9B8(Entity* self);
void func_801CED54(Entity* self);
void func_801CF414(Entity* self);
void func_801CF320(Entity* self);
void func_801CF4EC(Entity* self);
void func_801CF9FC(Entity* self);
void func_801CFD2C(Entity* self);
void func_801CFF04(Entity* self);
void func_801D082C(Entity* self);
void func_801D0940(Entity* self);
void func_801D0BA4(Entity* self);
void func_801D0DD8(Entity* self);
void func_801D14A4(Entity* self);
void func_801D13B0(Entity* self);
void func_801D18A4(Entity* self);
void func_801D1E60(Entity* self);
void func_801D22EC(Entity* self);
void func_801D1D6C(Entity* self);
void func_801D2464(Entity* self);
void func_801D2C00(Entity* self);
void func_801D2EF0(Entity* self);
void func_801D3160(Entity* self);
void func_801DC5B0(Entity* self);
void func_801DD314(Entity* self);
void func_801DD3E8(Entity* self);
void func_801D3360(Entity* self);
void func_801D3E08(Entity* self);
void func_801D3EDC(Entity* self);
void func_801D41FC(Entity* self);
void func_801D497C(Entity* self);
void func_801D4AD4(Entity* self);
void func_801D4CD0(Entity* self);
void func_801D579C(Entity* self);
void func_801D5870(Entity* self);
void func_801D5E8C(Entity* self);
void func_801D6290(Entity* self);
void func_801D6A88(Entity* self);
void func_801D6D14(Entity* self);
void func_801D6E20(Entity* self);
void func_801D6FD4(Entity* self);
void func_801D7108(Entity* self);
void func_801D758C(Entity* self);
void func_801D7810(Entity* self);
void func_801D791C(Entity* self);
void func_801D7C68(Entity* self);
void func_801D8504(Entity* self);
void func_801D8BE8(Entity* self);
void func_801D902C(Entity* self);
void func_801D93C0(Entity* self);
void func_801D95B4(Entity* self);
void func_801D9D44(Entity* self);
void func_801DA550(Entity* self);
void func_801DA148(Entity* self);
void func_801DA288(Entity* self);
void func_801DA484(Entity* self);
void func_801DA6C0(Entity* self);
void func_801DA7D0(Entity* self);
void func_801DAB40(Entity* self);
void func_801DB884(Entity* self);

PfnEntityUpdate EntityUpdates[] = {
    /* 0x01 */ func_801BF424,
    /* 0x02 */ func_801C58C0,
    /* 0x03 */ func_801C5088,
    /* 0x04 */ func_801C08EC,
    /* 0x05 */ func_801C1B6C,
    /* 0x06 */ func_801C7844,
    /* 0x07 */ func_801C2C28,
    /* 0x08 */ func_801C2788,
    /* 0x09 */ func_801C8FD4,
    /* 0x0A */ func_801C5A94,
    /* 0x0B */ func_801C6074,
    /* 0x0C */ func_801C6898,
    /* 0x0D */ func_801C3004,
    /* 0x0E */ func_801C44CC,
    /* 0x0F */ func_801C44CC,
    /* 0x10 */ func_801C44CC,
    /* 0x11 */ func_801BEE30,
    /* 0x12 */ func_801BEFC8,
    /* 0x13 */ func_801C6A90,
    /* 0x14 */ func_801C6DB8,
    /* 0x15 */ func_801C6EA8,
    /* 0x16 */ func_801CAC9C,
    /* 0x17 */ func_801CB204,
    /* 0x18 */ func_801CB89C,
    /* 0x19 */ func_801CB9A4,
    /* 0x1A */ func_801CC084,
    /* 0x1B */ func_801CC434,
    /* 0x1C */ func_801CCBFC,
    /* 0x1D */ func_801CCE90,
    /* 0x1E */ func_801CD990,
    /* 0x1F */ func_801CDA88,
    /* 0x20 */ func_801CDCF8,
    /* 0x21 */ func_801CE0AC,
    /* 0x22 */ func_801CE3F8,
    /* 0x23 */ func_801CE8D8,
    /* 0x24 */ func_801CE9B8,
    /* 0x25 */ func_801CED54,
    /* 0x26 */ func_801CF414,
    /* 0x27 */ func_801CF320,
    /* 0x28 */ func_801CF4EC,
    /* 0x29 */ func_801CF9FC,
    /* 0x2A */ func_801CFD2C,
    /* 0x2B */ func_801CFF04,
    /* 0x2C */ func_801D082C,
    /* 0x2D */ func_801D0940,
    /* 0x2E */ func_801D0BA4,
    /* 0x2F */ func_801D0DD8,
    /* 0x30 */ func_801D14A4,
    /* 0x31 */ func_801D13B0,
    /* 0x32 */ func_801D18A4,
    /* 0x33 */ func_801D1E60,
    /* 0x34 */ func_801D22EC,
    /* 0x35 */ func_801D1D6C,
    /* 0x36 */ func_801D2464,
    /* 0x37 */ func_801D2C00,
    /* 0x38 */ func_801D2EF0,
    /* 0x39 */ func_801D3160,
    /* 0x3A */ func_801DC5B0,
    /* 0x3B */ func_801DD314,
    /* 0x3C */ func_801DD3E8,
    /* 0x3D */ func_801D3360,
    /* 0x3E */ func_801D3E08,
    /* 0x3F */ func_801D3EDC,
    /* 0x40 */ func_801D41FC,
    /* 0x41 */ func_801D497C,
    /* 0x42 */ func_801D4AD4,
    /* 0x43 */ func_801D4CD0,
    /* 0x44 */ func_801D579C,
    /* 0x45 */ func_801D5870,
    /* 0x46 */ func_801D5E8C,
    /* 0x47 */ func_801D6290,
    /* 0x48 */ func_801D6A88,
    /* 0x49 */ func_801D6D14,
    /* 0x4A */ func_801D6E20,
    /* 0x4B */ func_801D6FD4,
    /* 0x4C */ func_801D7108,
    /* 0x4D */ func_801D758C,
    /* 0x4E */ func_801D7810,
    /* 0x4F */ func_801D791C,
    /* 0x50 */ func_801D7C68,
    /* 0x51 */ func_801D8504,
    /* 0x52 */ func_801D8BE8,
    /* 0x53 */ func_801D902C,
    /* 0x54 */ func_801D93C0,
    /* 0x55 */ func_801D95B4,
    /* 0x56 */ func_801D9D44,
    /* 0x57 */ func_801DA550,
    /* 0x58 */ func_801DA148,
    /* 0x59 */ func_801DA288,
    /* 0x5A */ func_801DA484,
    /* 0x5B */ func_801DA6C0,
    /* 0x5C */ func_801DA7D0,
    /* 0x5D */ func_801DAB40,
    /* 0x5E */ func_801DB884,
};

// clang-format off
EInit D_80180950 = {ANIMSET_DRA(0x03), 0x00, 0x00, PAL_NONE, ENEMY_BREAKABLE};
EInit D_8018095C = {ANIMSET_DRA(0x03), 0x00, 0x00, PAL_NONE, ENEMY_OBTAINABLE};
EInit D_80180968 = {ANIMSET_DRA(0x03), 0x00, 0x00, PAL_NONE, ENEMY_PARTICLE};
EInit D_80180974 = {ANIMSET_DRA(0x00), 0x00, 0x00, PAL_NONE, ENEMY_SPAWNER};
EInit D_80180980 = {ANIMSET_DRA(0x00), 0x00, 0x00, PAL_NONE, ENEMY_INTERACTABLE};
EInit D_8018098C = {ANIMSET_DRA(0x02), 0x00, 0x00, PAL_NONE, ENEMY_WHITE_DRAGON_FLAME_BREATH};
EInit D_80180998 = {ANIMSET_OVL(0x05), 0x00, 0x24, PAL_NONE, ENEMY_COMMON};
EInit D_801809A4 = {ANIMSET_DRA(0x02), 0x00, 0x48, PAL_NONE, ENEMY_LOCK_CAMERA_VARIANT};
EInit D_801809B0 = {ANIMSET_DRA(0x03), 0x00, 0x48, PAL_NONE, ENEMY_UNK_5C};
EInit D_801809BC = {ANIMSET_DRA(0x00), 0x00, 0x00, PAL_NONE, ENEMY_PARTICLE};
EInit D_801809C8 = {ANIMSET_DRA(0x00), 0x00, 0x00, PAL_NONE, ENEMY_COMMON};
EInit D_801809D4 = {ANIMSET_DRA(0x00), 0x00, 0x00, PAL_NONE, ENEMY_COMMON};
EInit D_801809E0 = {ANIMSET_DRA(0x00), 0x00, 0x00, PAL_NONE, ENEMY_COMMON};
EInit D_801809EC = {ANIMSET_OVL(0x01), 0x01, 0x48, PAL_DODO_BIRD, ENEMY_DODO_BIRD};
EInit D_801809F8 = {ANIMSET_OVL(0x02), 0x01, 0x49, PAL_BONE_SCIMITAR, ENEMY_BONE_SCIMITAR};
EInit D_80180A04 = {ANIMSET_OVL(0x02), 0x00, 0x49, PAL_BONE_SCIMITAR, ENEMY_PARTICLE};
EInit D_80180A10 = {ANIMSET_OVL(0x03), 0x01, 0x4A, PAL_TOAD_FROG, ENEMY_TOAD};
EInit D_80180A1C = {ANIMSET_OVL(0x04), 0x01, 0x4B, PAL_BONE_ARCHER, ENEMY_BONE_ARCHER};
EInit D_80180A28 = {ANIMSET_OVL(0x04), 0x01, 0x4B, PAL_BONE_ARCHER, ENEMY_BONE_ARCHER_ARROW};
EInit D_80180A34 = {ANIMSET_OVL(0x06), 0x01, 0x4D, PAL_GRAVE_KEEPER_TOMBSTONE, ENEMY_GRAVE_KEEPER};
EInit D_80180A40 = {ANIMSET_OVL(0x00), 0x00, 0x00, PAL_NONE, ENEMY_GRAVE_KEEPER_HITBOX};
EInit D_80180A4C = {ANIMSET_OVL(0x06), 0x15, 0x4D, PAL_GRAVE_KEEPER_TOMBSTONE, ENEMY_TOMBSTONE};
EInit D_80180A58 = {ANIMSET_OVL(0x07), 0x00, 0x4F, PAL_CROW, ENEMY_BLUE_RAVEN};
EInit D_80180A64 = {ANIMSET_OVL(0x08), 0x01, 0x50, PAL_JACK_O_BONES, ENEMY_JACK_O_BONES};
EInit D_80180A70 = {ANIMSET_OVL(0x08), 0x00, 0x50, PAL_JACK_O_BONES, ENEMY_PARTICLE};
EInit D_80180A7C = {ANIMSET_OVL(0x08), 0x15, 0x50, PAL_JACK_O_BONES, ENEMY_JACK_O_BONES_3};
EInit D_80180A88 = {ANIMSET_OVL(0x09), 0x01, 0x58, PAL_BONE_HALBERD, ENEMY_BONE_HALBERD};
EInit D_80180A94 = {ANIMSET_OVL(0x00), 0x00, 0x00, PAL_DODO_BIRD, ENEMY_BONE_HALBERD_ATTACK};
EInit D_80180AA0 = {ANIMSET_OVL(0x0A), 0x01, 0x56, PAL_YORICK, ENEMY_YORICK};
EInit D_80180AAC = {ANIMSET_OVL(0x0A), 0x1E, 0x56, PAL_YORICK, ENEMY_YORICK_SKULL};
EInit D_80180AB8 = {ANIMSET_OVL(0x0B), 0x01, 0x51, PAL_BLADE_MASTER, ENEMY_BLADE_MASTER};
EInit D_80180AC4 = {ANIMSET_OVL(0x00), 0x00, 0x00, PAL_NONE, ENEMY_BLADE_MASTER_ATTACK_HITBOX};
EInit D_80180AD0 = {ANIMSET_OVL(0x0C), 0x01, 0x57, PAL_BLADE_SOLDIER, ENEMY_BLADE_SOLDIER};
EInit D_80180ADC = {ANIMSET_OVL(0x00), 0x00, 0x00, PAL_NONE, ENEMY_BLADE_SOLDIER_ATTACK_HITBOX};
EInit D_80180AE8 = {ANIMSET_OVL(0x0D), 0x01, 0x48, PAL_NOVA_SKELETON, ENEMY_NOVA_SKELETON};
EInit D_80180AF4 = {ANIMSET_OVL(0x0E), 0x00, 0x52, PAL_BONE_MUSKET, ENEMY_BONE_MUSKET};
EInit D_80180B00 = {ANIMSET_OVL(0x0E), 0x00, 0x52, PAL_BONE_MUSKET, ENEMY_UNK_67};
EInit D_80180B0C = {ANIMSET_OVL(0x0F), 0x00, 0x49, PAL_WINGED_GUARD, ENEMY_WINGED_GUARD};
EInit D_80180B18 = {ANIMSET_OVL(0x0F), 0x00, 0x49, PAL_WINGED_GUARD, ENEMY_COMMON};
EInit D_80180B24 = {ANIMSET_OVL(0x18), 0x00, 0x50, PAL_SPECTRAL_SWORD, ENEMY_SPECTRAL_SWORD_NO2};
EInit D_80180B30 = {ANIMSET_OVL(0x18), 0x00, 0x50, PAL_SPECTRAL_SWORD, ENEMY_POLTERGEIST};
EInit D_80180B3C = {ANIMSET_OVL(0x19), 0x00, 0x51, PAL_SPECTRAL_SWORD, ENEMY_SPECTRAL_SWORD_DAI};
EInit D_80180B48 = {ANIMSET_OVL(0x19), 0x00, 0x51, PAL_SPECTRAL_SWORD_WEAPON, ENEMY_SPECTRAL_SWORD_WEAPON};
EInit D_80180B54 = {ANIMSET_OVL(0x19), 0x00, 0x51, PAL_SPECTRAL_SWORD_WEAPON, ENEMY_SPECTRAL_SWORD_RDAI};
EInit D_80180B60 = {ANIMSET_OVL(0x19), 0x00, 0x51, PAL_SPECTRAL_SWORD_WEAPON, ENEMY_SPEAR};
EInit D_80180B6C = {ANIMSET_OVL(0x19), 0x00, 0x51, PAL_SPECTRAL_SWORD_WEAPON, ENEMY_SHIELD};
EInit D_80180B78 = {ANIMSET_OVL(0x1A), 0x01, 0x48, PAL_VALHALLA_KNIGHT, ENEMY_VALHALLA_KNIGHT};
EInit D_80180B84 = {ANIMSET_OVL(0x1A), 0x01, 0x48, PAL_VALHALLA_KNIGHT, ENEMY_COMMON};
EInit D_80180B90 = {ANIMSET_OVL(0x00), 0x00, 0x00, PAL_NONE, ENEMY_VALHALLA_KNIGHT_UNK2};
EInit D_80180B9C = {ANIMSET_OVL(0x00), 0x00, 0x00, PAL_NONE, ENEMY_VALHALLA_KNIGHT_UNK3};
EInit D_80180BA8 = {ANIMSET_OVL(0x1B), 0x01, 0x51, PAL_OROBOUROUS, ENEMY_OROBOUROUS};
EInit D_80180BB4 = {ANIMSET_OVL(0x1B), 0x04, 0x51, PAL_OROBOUROUS, ENEMY_ORUBUROS};
EInit D_80180BC0 = {ANIMSET_OVL(0x1B), 0x04, 0x50, PAL_OROBOUROUS, ENEMY_PARTICLE};
EInit D_80180BCC = {ANIMSET_OVL(0x1B), 0x04, 0x50, PAL_OROBOUROUS, ENEMY_ORUBUROS_RIDER};
EInit D_80180BD8 = {ANIMSET_OVL(0x1B), 0x01, 0x50, PAL_DRAGON_RIDER, ENEMY_DRAGON_RIDER_1};
EInit D_80180BE4 = {ANIMSET_OVL(0x1B), 0x04, 0x50, PAL_DRAGON_RIDER, ENEMY_DRAGON_RIDER_2};
EInit D_80180BF0 = {ANIMSET_OVL(0x1B), 0x04, 0x50, PAL_DRAGON_RIDER, ENEMY_PARTICLE};
EInit D_80180BFC = {ANIMSET_OVL(0x1E), 0x00, 0x4C, PAL_THORNWEED_CORPSEWEED, ENEMY_THORNWEED};
EInit D_80180C08 = {ANIMSET_OVL(0x1E), 0x00, 0x4C, PAL_THORNWEED_CORPSEWEED, ENEMY_CORPSEWEED_UNUSED};
EInit D_80180C14 = {ANIMSET_OVL(0x1E), 0x00, 0x4C, PAL_THORNWEED_CORPSEWEED, ENEMY_CORPSEWEED};
EInit D_80180C20 = {ANIMSET_OVL(0x1E), 0x00, 0x4C, PAL_THORNWEED_CORPSEWEED, ENEMY_CORPSEWEED_PROJECTILE};
EInit D_80180C2C = {ANIMSET_OVL(0x1F), 0x00, 0x50, PAL_VENUS_WEED, ENEMY_VENUS_WEED_ROOT};
EInit D_80180C38 = {ANIMSET_OVL(0x1F), 0x00, 0x50, PAL_VENUS_WEED, ENEMY_VENUS_WEED_FLOWER};
EInit D_80180C44 = {ANIMSET_OVL(0x1F), 0x00, 0x50, PAL_VENUS_WEED, ENEMY_VENUS_WEED_TENDRIL};
EInit D_80180C50 = {ANIMSET_OVL(0x1F), 0x37, 0x50, PAL_VENUS_WEED, ENEMY_VENUS_WEED_DART};
EInit D_80180C5C = {ANIMSET_OVL(0x1C), 0x01, 0x48, PAL_BOMB_KNIGHT, ENEMY_BOMB_KNIGHT};
EInit D_80180C68 = {ANIMSET_OVL(0x1C), 0x24, 0x48, PAL_BOMB_KNIGHT, ENEMY_BOMB};
EInit D_80180C74 = {ANIMSET_OVL(0x1C), 0x00, 0x48, PAL_BOMB_KNIGHT, ENEMY_PARTICLE};
EInit D_80180C80 = {ANIMSET_OVL(0x1C), 0x41, 0x48, PAL_BOMB_KNIGHT, ENEMY_ROCK};
