#define _DECL_ENTITY_NAME(x) E_##x
#define DECL_ENTITY_NAME(x) _DECL_ENTITY_NAME(x)
#define _DECL_ENTITY_EXT(x) ET_##x
#define DECL_ENTITY_EXT(x) _DECL_ENTITY_EXT(x)

typedef struct Entity {
    /* 0x00 */ f32 posX;
    /* 0x04 */ f32 posY;
    /* 0x08 */ s32 velocityX;
    /* 0x0C */ s32 velocityY;
#if defined(STAGE) || defined(WEAPON) || defined(SERVANT) ||                   \
    defined(VERSION_PSP)
    /* 0x10 */ s16 hitboxOffX;
#else // hack to match in DRA and RIC
    /* 0x10 */ u16 hitboxOffX;
#endif
    /* 0x12 */ s16 hitboxOffY;
    /* 0x14 */ u16 facingLeft;
    /* 0x16 */ u16 palette;
    /* 0x18 */ u8 drawMode;
    /* 0x19 */ u8 drawFlags;
    /* 0x1A */ s16 rotX;
    /* 0x1C */ s16 rotY;
    /* 0x1E */ s16 rotZ;
    /* 0x20 */ s16 rotPivotX;
    /* 0x22 */ s16 rotPivotY;
    /* 0x24 */ u16 zPriority;
    /* 0x26 */ u16 entityId;
    /* 0x28 */ PfnEntityUpdate pfnUpdate;
    /* 0x2C */ u16 step;
    /* 0x2E */ u16 step_s;
    /* 0x30 */ u16 params;
    /* 0x32 */ u16 entityRoomIndex;
    /* 0x34 */ s32 flags;
    /* 0x38 */ s16 unk38;
    /* 0x3A */ u16 enemyId;
    /* 0x3C */ u16 hitboxState; // hitbox state
    /* 0x3E */ s16 hitPoints;
    /* 0x40 */ s16 attack;
    /* 0x42 */ u16 attackElement;
    /* 0x44 */ u16 hitParams;
    /* 0x46 */ u8 hitboxWidth;
    /* 0x47 */ u8 hitboxHeight;
    /* 0x48 */ u8 hitFlags; // 1 = took hit
    /* 0x49 */ u8 nFramesInvincibility;
    /* 0x4A */ s16 unk4A;
    /* 0x4C */ AnimationFrame* anim;
    /* 0x50 */ u16 animFrameIdx;
    /* 0x52 */ s16 animFrameDuration;
    /* 0x54 */ s16 animSet;
    /* 0x56 */ s16 animCurFrame;
    /* 0x58 */ s16 stunFrames;
    /* 0x5A */ u16 unk5A;
    /* 0x5C */ struct Entity* unk5C;
    /* 0x60 */ struct Entity* unk60;
    /* 0x64 */ s32 primIndex;
    /* 0x68 */ u16 unk68; // Appears to be set for entities with parallax
    /* 0x6A */ u16 hitEffect;
    /* 0x6C */ u8 unk6C; // Salem Witch: timer to destroy its shadows.
                         // Thornweed: timer before spawning death explosion
    /* 0x6D */ u8 unk6D[11];
    /* 0x78 */ s32 unk78;

    DECL_ENTITY_EXT(ENTITY_EXT) ext;
    /* 0xB8 */ struct Entity* unkB8;
} DECL_ENTITY_NAME(ENTITY_EXT); // size = 0xBC
