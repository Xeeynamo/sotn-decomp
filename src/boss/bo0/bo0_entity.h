// SPDX-License-Identifier: AGPL-3.0-or-later
#ifndef BO0_ENTITY_H
#define BO0_ENTITY_H

#include <types.h>
#include <common.h>
#include <primitive.h>

typedef struct Entity;

typedef struct {
    /* 0x7C */ u32 : 32;
    /* 0x80 */ s16 timer;
    /* 0x82 */ u16 : 16;
    /* 0x84 */ u8 unk84;
    /* 0x85 */ u8 unk85;
    /* 0x86 */ u8 unk86;
    /* 0x87 */ u8 unk87;
    /* 0x88 */ u8 unk88;
} ET_Olrox;

typedef struct {
    /* 0x7C */ u32 : 32;
    /* 0x80 */ s16 timer;
    /* 0x82 */ u16 : 16;
    /* 0x84 */ u8 unk84;
    /* 0x85 */ u8 unk85;
    /* 0x86 */ u8 : 8;
    /* 0x87 */ u8 : 8;
    /* 0x88 */ u32 : 32;
    /* 0x8C */ u32 : 32;
    /* 0x90 */ u32 : 32;
    /* 0x94 */ u32 : 32;
    /* 0x98 */ u32 : 32;
    /* 0x9C */ u32 : 32;
    /* 0xA0 */ u32 : 32;
    /* 0xA4 */ struct Entity* parent;
    /* 0xA8 */ u8 unkA8;
} ET_OlroxAfterImage;

typedef struct {
    /* 0x7C */ struct Primitive* prim;
    /* 0x80 */ s32 velocityX;
    /* 0x84 */ s32 velocityY;
    /* 0x88 */ u32 : 32;
    /* 0x8C */ u32 : 32;
    /* 0x90 */ u32 : 32;
    /* 0x94 */ u32 : 32;
    /* 0x98 */ u32 : 32;
    /* 0x9C */ u32 : 32;
    /* 0xA0 */ u32 : 32;
    /* 0xA4 */ struct Entity* parent;
} ET_OlroxDrool;

typedef struct {
    /* 0x7C */ Primitive* prim1;
    /* 0x80 */ Primitive* prim2;
    /* 0x84 */ Primitive* prim3;
    /* 0x88 */ Primitive* prim4;
    /* 0x8C */ Primitive* prim5;
    /* 0x90 */ Primitive* prim6;
    /* 0x94 */ u32 : 32;
    /* 0x98 */ s16 hitboxOffX;
    /* 0x9A */ u16 : 16;
    /* 0x9C */ s16 timer9C;
    /* 0x9E */ s16 timer9E;
    /* 0xA0 */ s16 timer;
    /* 0xA2 */ u16 : 16;
    /* 0xA4 */ struct Entity* parent;
    /* 0xA8 */ u8 : 8;
    /* 0xA9 */ u8 unkA9;
    /* 0xAA */ u8 : 8;
    /* 0xAB */ u8 : 8;
    /* 0xAC */ u8 : 8;
    /* 0xAD */ u8 scaleIndex;
} ET_OlroxLaser;

typedef struct {
    /* 0x7C */ Primitive* prim7C;
    /* 0x80 */ s16 timer;
    /* 0x82 */ u16 : 16;
    /* 0x84 */ s16 : 16;
    /* 0x86 */ u8 unk86;
    /* 0x87 */ u8 : 8;
    /* 0x88 */ u32 : 32;
    /* 0x8C */ s16 timer2;
    /* 0x8E */ s16 height;
    /* 0x90 */ Primitive* prim;
    /* 0x94 */ s16 unk94;
    /* 0x94 */ s16 unk96;
    /* 0x98 */ s16 unk98;
    /* 0x9A */ s16 unk9A;
    /* 0x9C */ s16 unk9C;
    /* 0x9E */ s16 unk9E;
    /* 0xA0 */ s16 unkA0;
    /* 0xA2 */ s16 : 16;
    /* 0xA4 */ struct Entity* parent;
} ET_OlroxGroundBlast;

typedef struct {
    /* 0x7C */ u32 : 32;
    /* 0x80 */ u32 : 32;
    /* 0x84 */ u32 : 32;
    /* 0x88 */ u32 : 32;
    /* 0x8C */ u32 : 32;
    /* 0x90 */ u32 : 32;
    /* 0x94 */ u32 : 32;
    /* 0x98 */ u32 : 32;
    /* 0x9C */ u32 : 32;
    /* 0xA0 */ u32 : 32;
    /* 0xA4 */ struct Entity* parent;
} ET_OlroxPortal;

typedef struct {
    /* 0x7C */ u32 : 32;
    /* 0x80 */ u32 : 32;
    /* 0x84 */ u32 : 32;
    /* 0x88 */ u32 : 32;
    /* 0x8C */ u32 : 32;
    /* 0x90 */ u32 : 32;
    /* 0x94 */ u32 : 32;
    /* 0x98 */ u32 : 32;
    /* 0x9C */ u32 : 32;
    /* 0xA0 */ u32 : 32;
    /* 0xA4 */ u32 : 32;
    /* 0xA8 */ f32 unkAA;
} ET_OlroxBlast;

typedef struct {
    /* 0x7C */ u32 : 32;
    /* 0x80 */ u32 : 32;
    /* 0x84 */ u32 : 32;
    /* 0x88 */ u32 : 32;
    /* 0x8C */ u32 : 32;
    /* 0x90 */ u32 : 32;
    /* 0x94 */ u32 : 32;
    /* 0x98 */ u32 : 32;
    /* 0x9C */ u32 : 32;
    /* 0xA0 */ u32 : 32;
    /* 0xA4 */ struct Entity* parent;
    /* 0xA8 */ u16 : 16;
    /* 0xAA */ s16 unkAA;
} ET_OlroxSkulls;

typedef struct {
    /* 0x7C */ Primitive* prim;
    /* 0x80 */ u8 unk80;
    /* 0x81 */ u8 : 8;
    /* 0x82 */ u16 : 16;
    /* 0x84 */ s16 unk84;
    /* 0x86 */ u16 : 16;
    /* 0x88 */ s16 unk88[6];
    /* 0x94 */ s16 unk94;
    /* 0x96 */ s16 : 16;
    /* 0x98 */ u8 : 8;
    /* 0x99 */ u8 : 8;
    /* 0x9A */ u8 : 8;
    /* 0x9B */ u8 unk9B;
} ET_OlroxTrueForm;

#define STAGE_EXTENSIONS                                                       \
    ET_Olrox olrox;                                                            \
    ET_OlroxAfterImage olroxAfterImage;                                        \
    ET_OlroxDrool olroxDrool;                                                  \
    ET_OlroxLaser olroxLaser;                                                  \
    ET_OlroxGroundBlast olroxGroundBlast;                                      \
    ET_OlroxPortal olroxPortal;                                                \
    ET_OlroxBlast olroxBlast;                                                  \
    ET_OlroxSkulls olroxSkulls;                                                \
    ET_OlroxTrueForm olroxTrueForm;

SYNC_FIELD(ET_OlroxAfterImage, ET_OlroxDrool, parent);
SYNC_FIELD(ET_OlroxAfterImage, ET_OlroxLaser, parent);
SYNC_FIELD(ET_OlroxAfterImage, ET_OlroxGroundBlast, parent);
SYNC_FIELD(ET_OlroxAfterImage, ET_OlroxPortal, parent);
SYNC_FIELD(ET_OlroxAfterImage, ET_OlroxSkulls, parent);

#endif // BO0_ENTITY_H
