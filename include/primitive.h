/**
 * Standard Primitive and its variants
 */

#ifndef PRIMITIVE_H
#define PRIMITIVE_H
#include "common.h"

#define blendMode drawMode // maintained to easily migrate existing scratches
typedef struct Primitive {
    /* 0x00 */ struct Primitive* next;
#if defined(VERSION_PC) || defined(VERSION_PSP)
    u_long dummy;
#endif
    /* 0x04 */ u8 r0;
    /* 0x05 */ u8 g0;
    /* 0x06 */ u8 b0;
    /* 0x07 */ u8 type; // PrimitiveType
    /* 0x08 */ s16 x0;
    /* 0x0A */ s16 y0;
    /* 0x0C */ u8 u0;    // w for PrimitiveType::TILE
    /* 0x0D */ u8 v0;    // h for PrimitiveType::TILE
    /* 0x0E */ u16 clut; // TODO not verified
    /* 0x10 */ u8 r1;
    /* 0x11 */ u8 g1;
    /* 0x12 */ u8 b1;
    /* 0x13 */ u8 p1; // TODO not verified
    /* 0x14 */ s16 x1;
    /* 0x16 */ s16 y1;
    /* 0x18 */ u8 u1;     // TODO not verified
    /* 0x19 */ u8 v1;     // TODO not verified
    /* 0x1A */ u16 tpage; // TODO not verified
    /* 0x1C */ u8 r2;
    /* 0x1D */ u8 g2;
    /* 0x1E */ u8 b2;
    /* 0x1F */ u8 p2; // TODO not verified
    /* 0x20 */ s16 x2;
    /* 0x22 */ s16 y2;
    /* 0x24 */ u8 u2; // TODO not verified
    /* 0x25 */ u8 v2; // TODO not verified
    /* 0x26 */ u16 priority;
    /* 0x28 */ u8 r3;
    /* 0x29 */ u8 g3;
    /* 0x2A */ u8 b3;
    /* 0x2B */ u8 p3; // TODO not verified
    /* 0x2C */ s16 x3;
    /* 0x2E */ s16 y3;
    /* 0x30 */ u8 u3; // TODO not verified
    /* 0x31 */ u8 v3; // TODO not verified
    /* 0x32 */ u16 drawMode;
} Primitive; /* size=0x34 */

// FakePrim is really the wrong name for this.
// But it's an alternate use of the Primitive structure.
typedef struct FakePrim {
    struct FakePrim* next;
#if defined(VERSION_PC) || defined(VERSION_PSP)
    u_long dummy;
#endif
    /* 0x04 */ u8 r0;
    /* 0x05 */ u8 g0;
    /* 0x06 */ u8 b0;
    /* 0x07 */ u8 type; // PrimitiveType
    /* 0x08 */ s16 x0;
    /* 0x0A */ s16 y0;
    /* 0x0C */ u8 w;
    /* 0x0D */ u8 h;
    /* 0x0E */ u16 clut;
    /* 0x10 */ f32 posX;
    /* 0x14 */ f32 posY;
    /* 0x18 */ f32 velocityX;
    /* 0x1C */ f32 velocityY;
    /* 0x20 */ s16 x2;
    /* 0x22 */ s16 y2;
    /* 0x24 */ s16 delay;
    /* 0x26 */ u16 priority;
    /* 0x28 */ f32 accelerationX;
    /* 0x2C */ f32 accelerationY;
    /* 0x30 */ s16 timer;
    /* 0x32 */ u16 drawMode;
} FakePrim;

// Not actually sure if this is for LineG2, but the only time LineG2
// is used is also the only time this struct is used, so we will call
// it this for now. That one use is in RicEntityCrashHydroStorm.
typedef struct PrimLineG2 {
    struct PrimLineG2* next;
    /* 0x04 */ u8 r0;
    /* 0x05 */ u8 g0;
    /* 0x06 */ u8 b0;
    /* 0x07 */ u8 type;
    /* 0x08 */ s16 x0;
    /* 0x0A */ s16 y0;
    /* 0x0C */ s16 xLength;
    /* 0x0E */ s16 yLength;
    /* 0x10 */ u8 r1;
    /* 0x11 */ u8 g1;
    /* 0x12 */ u8 b1;
    /* 0x13 */ u8 p1;
    /* 0x14 */ s16 x1;
    /* 0x16 */ s16 y1;
    /* 0x18 */ f32 velocityX;
    /* 0x1C */ f32 velocityY;
    /* 0x20 */ s32 angle;
    /* 0x24 */ s16 delay;
    /* 0x26 */ u16 priority;
    /* 0x28 */ f32 preciseX;
    /* 0x2C */ f32 preciseY;
    /* 0x30 */ s16 timer;
    /* 0x32 */ u16 drawMode;
} PrimLineG2;

typedef struct {
    struct primitive* next;
    /* 0x04 */ u8 r0;
    /* 0x05 */ u8 g0;
    /* 0x06 */ u8 b0;
    /* 0x07 */ u8 type;
    /* 0x08 */ s16 x0;
    /* 0x0A */ s16 y0;
    /* 0x0C */ u8 u0;
    /* 0x0D */ u8 v0;
    /* 0x0E */ u16 clut;
    /* 0x10 */ u8 r1;
    /* 0x11 */ u8 g1;
    /* 0x12 */ u8 b1;
    /* 0x13 */ u8 p1;
    /* 0x14 */ s16 x1;
    /* 0x16 */ s16 y1;
    /* 0x18 */ u8 u1;
    /* 0x19 */ u8 v1;
    /* 0x1A */ u16 tpage;
    /* 0x1C */ u8 r2;
    /* 0x1D */ u8 g2;
    /* 0x1E */ u8 b2;
    /* 0x1F */ u8 p2;
    /* 0x20 */ f32 y1_f32;
    /* 0x24 */ s16 unk24;
    /* 0x26 */ u16 priority;
    /* 0x28 */ u8 r3;
    /* 0x29 */ u8 g3;
    /* 0x2A */ u8 b3;
    /* 0x2B */ u8 p3;
    /* 0x2C */ f32 y1_f32_velocity;
    /* 0x30 */ s16 unk30;
    /* 0x32 */ u16 drawMode;
} draculaPrimitive;

typedef struct AxePrim {
    struct AxePrim* next;
    /* 0x04 */ u8 r0;
    /* 0x05 */ u8 g0;
    /* 0x06 */ u8 b0;
    /* 0x07 */ u8 type; // PrimitiveType
    /* 0x08 */ s16 x0;
    /* 0x0A */ s16 y0;
    /* 0x0C */ s32 unk0C;
    /* 0x10 */ s32 unk10;
    /* 0x14 */ s16 x1;
    /* 0x16 */ s16 y1;
    /* 0x18 */ u8 u1;
    /* 0x19 */ u8 v1;
    /* 0x1A */ u16 tpage;
    /* 0x1C */ s16 unk1C;
    /* 0x1E*/ s16 unk1E;
    /* 0x20 */ s16 x2;
    /* 0x22 */ s16 y2;
    /* 0x24 */ u8 step;
    /* 0x26 */ u16 priority;
    /* 0x2A */ s32 pad;
    /* 0x2C */ s16 timer;
    /* 0x2E */ s16 unk2E;
    /* 0x30 */ s16 unk30;
    /* 0x32 */ u16 drawMode;
} AxePrim;
#endif
