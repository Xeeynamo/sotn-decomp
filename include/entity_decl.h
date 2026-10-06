#ifndef ENTITY_DECL_H
#define ENTITY_DECL_H

#include <types.h>
#include <common.h>
#include <primitive.h>

#define E(e) ((Entity*) (e))

// Placeholders for M2C to use. No code should be merged which uses them.
typedef union {
    u8 u8[0x3C];
    s8 s8[0x3C];
    u16 u16[0x1E];
    s16 s16[0x1E];
    u32 u32[0xF];
    s32 s32[0xF];
} ET_Illegal;

typedef union {
    Primitive* prim;
    ET_Illegal ILLEGAL;
} ExtProto;

#define EXT(type) \
    typedef union { \
        Primitive* prim; \
        ET_Placeholder ILLEGAL; \
        type \
    } Ext;

#define ENTITY_NAME(name) Entity ## name

#define ENTITY(name, extension) \
typedef struct { \
    /* 0x00 */ f32 posX; \
    /* 0x04 */ f32 posY; \
    /* 0x08 */ s32 velocityX; \
    /* 0x0C */ s32 velocityY; \
    /* 0x10 */ s16 hitboxOffX; \
    /* 0x12 */ s16 hitboxOffY; \
    /* 0x14 */ u16 facingLeft; \
    /* 0x16 */ u16 palette; \
    /* 0x18 */ u8 blendMode; /* refer to enum BlendModes */ \
    /* 0x19 */ u8 drawFlags; /* // refer to enum EntityDrawFlags */ \
    /* 0x1A */ s16 scaleX;   /* 0x100: 1.0, enabled with ENTITY_SCALE_X */ \
    /* 0x1C */ s16 scaleY;   /* 0x100: 1.0, enabled with ENTITY_SCALE_Y */ \
    /* 0x1E */ s16 rotate;   /* 0x1000: 360 degrees, enabled with ENTITY_ROTATE */ \
    /* 0x20 */ s16 rotPivotX; \
    /* 0x22 */ s16 rotPivotY; \
    /* 0x24 */ u16 zPriority; \
    /* 0x26 */ u16 entityId; \
    /* 0x28 */ PfnEntityUpdate pfnUpdate; \
    /* 0x2C */ u16 step; \
    /* 0x2E */ u16 step_s; \
    /* 0x30 */ u16 params; \
    /* 0x32 */ u16 entityRoomIndex; \
    /* 0x34 */ s32 flags; \
    /* 0x38 */ s16 : 16; \
    /* 0x3A */ u16 enemyId; /* also used as a Alucard weapon entity slot index */ \
    /* 0x3C */ u16 hitboxState; \
    /* 0x3E */ s16 hitPoints; \
    /* 0x40 */ s16 attack; \
    /* 0x42 */ u16 attackElement; \
    /* 0x44 */ u16 hitParams; \
    /* 0x46 */ u8 hitboxWidth; \
    /* 0x47 */ u8 hitboxHeight; \
    /* 0x48 */ u8 hitFlags; /* 1 = took hit */ \
    /* 0x49 */ u8 nFramesInvincibility; \
    /* 0x4A */ s16 unk4A; \
    /* 0x4C */ AnimationFrame* anim; \
    /* 0x50 */ u16 pose; \
    /* 0x52 */ s16 poseTimer; \
    /* 0x54 */ s16 animSet; \
    /* 0x56 */ s16 animCurFrame; \
    /* 0x58 */ s16 stunFrames; \
    /* 0x5A */ u16 unk5A; \
    /* 0x5C */ struct Entity* parent;   /* for multi-part entities only */ \
    /* 0x60 */ struct Entity* nextPart; /* next linked-list entity part */ \
    /* 0x64 */ s32 primIndex; \
    /* 0x68 */ u16 unk68; /* Appears to be set for entities with parallax */ \
    /* 0x6A */ u16 hitEffect; \
    /* 0x6C */ u8 opacity; /* enabled with ENTITY_OPACITY */ \
    /* 0x6D */ u8 unk6D[11]; \
    /* 0x78 */ s32 unk78; \
    /* 0x7C */ union { \
        Primitive* prim; \
        ET_Illegal ILLEGAL; \
        extension; \
    } ext; \
    /* 0xB8 */ struct Entity* unkB8; \
} ENTITY_NAME(name); /* size = 0xBC */ \
STATIC_ASSERT(sizeof(ENTITTY_NAME(name)) == 0xBC, "entity size")

#endif // ENTITY_DECL_H
