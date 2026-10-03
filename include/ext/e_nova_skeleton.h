// SPDX-License-Identifier: AGPL-3.0-or-later
#ifndef E_NOVA_SKELETON_ENTITY_H
#define E_NOVA_SKELETON_ENTITY_H

#include <types.h>
#include <common.h>
#include <primitive.h>

typedef struct {
    /* 0x7C */ struct Primitive* prim;
    /* 0x80 */ u8 movingLeft;
    /* 0x81 */ u8 cooldown;
    /* 0x82 */ u8 laserTimerIndex;
    /* 0x83 */ u8 deathPartLife;
    /* 0x84 */ s16 : 16;
    /* 0x86 */ s16 laserTimer;
    /* 0x88 */ u8 ringState;
    /* 0x8A */ s16 : 16;
    /* 0x8C */ s16 ringSize;
    /* 0x8E */ s16 ringRot;
    /* 0x90 */ s16 laserLength;
    /* 0x92 */ s16 laserFadeTimer;
    /* 0x94 */ u32 laserPulseDist;
} ET_NovaSkeleton;

#define STAGE_EXTENSIONS                                                       \
    ET_NovaSkeleton nova;

#endif // E_NOVA_SKELETON_ENTITY_H
