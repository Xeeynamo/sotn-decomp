// SPDX-License-Identifier: AGPL-3.0-or-later
/**
 * Custom Entity Subtypes
 */

#include "common.h"

struct Entity;
typedef void (*PfnEntityUpdate)(struct Entity*);

typedef union {
    s32 unk;
    void* ptr;
    struct {
        s8 unk0, unk1, unk2, unk3;
    } S8;
    struct {
        u8 unk0, unk1, unk2, unk3;
    } U8;
    struct {
        s16 unk0, unk2;
    } S16;
    struct {
        u16 unk0, unk2;
    } U16;
} Multi;

typedef union {
    s16 s;
    u16 u;
    struct {
        s8 unk0, unk1;
    } S8;
    struct {
        u8 unk0, unk1;
    } U8;
} Multi16;

struct Entity;

typedef struct ET_Generic {
    /* 0x7C */ Multi16 unk7C; // posX
    union {
        /* 0x7E */ u16 modeU16;
        struct {
            /* 0x7E */ u8 unk0;
            /* 0x7F */ u8 unk1;
        } modeU8;
    } unk7E; // posY
    union {
        /* 0x80 */ s32 modeS32;
        /* 0x80 */ struct Entity* entityPtr;
        struct {
            /* 0x80 */ s16 unk0;
            /* 0x82 */ s16 unk2;
        } modeS16;
        struct {
            /* 0x80 */ u8 unk0;
            /* 0x81 */ u8 unk1;
        } modeS8;
    } unk80; // size = 0x4
    /* 0x84 */ Multi unk84;
    /* 0x88 */ s32 : 32;
    /* 0x8C */ s32 : 32;
    /* 0x90 */ s16 unk90;
    /* 0x92 */ s16 : 16;
    /* 0x94 */ u8 unk94;
    /* 0x95 */ u8 : 8;
    /* 0x96 */ s16 : 16;
    /* 0x98 */ s32 unk98;
    /* 0x9C */ struct Entity* unk9C;
    /* 0xA0 */ s16 unkA0;
    /* 0xA2 */ s16 : 16;
    /* 0xA4 */ s32 : 32;
    /* 0xA8 */ s32 : 32;
    /* 0xAC */ s16 : 16;
    /* 0xAE */ s8 unkAE;
    /* 0xAF */ s8 : 8;
    /* 0xB0 */ s16 unkB0;
    /* 0xB2 */ s16 unkB2;
    /* 0xB4 */ s32 : 32;
    union {
        /* 0xB8 */ void (*unkFuncB8)(struct Entity*);
        /* 0xB8 */ struct Entity* entityPtr;
        struct {
            /* 0xB8 */ u8 unk0;
            /* 0xB9 */ u8 unk1;
            /* 0xBA */ u8 unk2;
            /* 0xBB */ u8 unk3;
        } modeU8;
    } unkB8;
} ET_Generic;

typedef struct {
    /* 0x00 */ u16 timer;
    /* 0x02 */ s16 unk7E;
    /* 0x04 */ u8 aliveTimer;
    /* 0x05 */ s8 unk81;
    /* 0x06 */ s16 unk82;
    /* 0x08 */ s32 fallSpeed;
    /* 0x0C */ s16 gravity;
    /* 0x0E */ s16 unk8A;
    /* 0x10 */ s16 iconSlot;
    /* 0x12 */ s16 unk8E;
    /* 0x14 */ s16 unk90;
    /* 0x16 */ s16 unk92;
    /* 0x18 */ s32 castleFlag;
} ET_EquipItemDrop;

typedef struct {
    /* 0x7C */ u32 unk[14];
    /* 0xB4 */ u16 unkB4;
    /* 0xB6 */ s16 unkB6;
    /* 0xB8 */ PfnEntityUpdate update;
} ET_HeartDrop;

typedef struct {
    /* 0x7C */ u16 timer;
    /* 0x7E */ u16 size;
    /* 0x80 */ u32 speed;
} ET_BloodDroplets;

typedef struct {
    /* 0x7C */ u16 nPrims;
    /* 0x7E */ u16 nDigits;
    /* 0x80 */ u8 digits[4];
    /* 0x84 */ u16 timer;
    /* 0x86 */ s16 unk86;
    /* 0x88 */ u16 unk88;
    /* 0x8A */ s16 unk8A;
} ET_NumericDamage;

typedef struct {
    u16 unk7C;
    u16 unk7E;
    u16 sparkleCycle;
    u16 sparkleAnim;
    u32 unk84;
    u32 unk88;
    s16 iconSlot;
    u16 unk8E;
    u16 floatTimer;
    u16 unk92;
    s32 yFloatSpeed;
} ET_RelicOrb;

typedef struct {
    /* 0x7C */ u32 unused7C;
    /* 0x80 */ s16 unused80;
    /* 0x82 */ s16 unk82;
    /* 0x84 */ s16 angle;
    /* 0x86 */ s16 unk86;
    /* 0x88 */ u8 sideToPlayer;
    /* 0x89 */ u8 showedMessage;
} ET_Door; // Normal red doors between stages, but also magically sealed blue
           // ones

typedef struct {
    /* 0x7C */ struct Primitive* prim;
    /* 0x80 */ s32 unk80;
    /* 0x84 */ struct Primitive* unk84;
    /* 0x88 */ struct Primitive* unk88;
    /* 0x8C */ struct Primitive* unk8C;
    /* 0x90 */ s16 unk90;
    /* 0x92 */ s16 unk92;
} ET_StagePopup;

typedef struct {
    /* 0x7C */ struct Primitive* prim;
    /* 0x80 */ s16 unk80;
    /* 0x84 */ struct Primitive* unk84;
    /* 0x88 */ struct Primitive* unk88;
    /* 0x8C */ u8 unk8C;
} ET_StagePopupJP;

typedef struct {
    /* 0x7C */ char* label;
    /* 0x80 */ u16 width;
    /* 0x82 */ u16 height;
    /* 0x84 */ s16 unk84;
    /* 0x86 */ u16 duration;
} ET_MessageBox;

typedef struct PACKED {
    /* 0x7C */ s16 lifetime;
    /* 0x7E */ s16 unk7E;
    /* 0x80 */ s16 unk80; // Y?
    /* 0x82 */ s16 unk82; // X?
    /* 0x84 */ struct Entity* some_ent;
    /* 0x88 */ s16 childPalette;
    /* 0x8A */ s16 unk8A;
    /* 0x8C */ struct Entity* parent;
    /* 0x90 */ s32 unk90;
    /* 0x94 */ s32 unk94;
    /* 0x98 */ s16 unk98;
    /* 0x9A */ s16 unk9A;
    /* 0x9C */ s32 accelerationX;
    /* 0xA0 */ s32 accelerationY;
    /* 0xA4 */ s16 unkA4;
    /* 0xA6 */ s16 vol;
    /* 0xA8 */ s32 unkA8;
    /* 0xAC */ u8 anim;
    /* 0xAD */ u8 unkAD;
    /* 0xAE */ s16 equipId;
} ET_Weapon;

typedef struct {
    s16 unk7C;
    s16 unk7E;
    s16 unk80;
    s16 unk82;
    s32 unk84;
    s32 unk88;
    byte pad[32];
#ifdef VERSION_PC
    s32 _align_anim[2];
#endif
    u8 anim;
} ET_WeaponUnk006;

typedef struct PACKED {
    /* 0x7C */ s16 lifetime;
    /* 0x7E */ s16 unk7E;
    /* 0x80 */ s16 unk80;
    /* 0x82 */ s16 unk82;
    /* 0x84 */ s32 unk84;
    /* 0x88 */ s16 childPalette;
    /* 0x8A */ s16 unk8A;
    /* 0x8C */ struct Entity* parent;
    /* 0x90 */ s32 unk90;
    /* 0x94 */ struct Entity* other;
    /* 0x98 */ s16 unk98;
    /* 0x9A */ s16 unk9A;
    /* 0x9C */ s32 accelerationX;
    /* 0xA0 */ s32 accelerationY;
    /* 0xA4 */ s32 unkA4;
    /* 0xA8 */ s32 unkA8;
    /* 0xAC */ u8 anim;
    /* 0xAD */ u8 unkAD;
    /* 0xAE */ s16 equipId;
} ET_WeaponUnk030;

typedef struct PACKED {
    s32 unk7C;
    s32 unk80;
    s32 unk84;
    s32 : 32;
    s32 : 32;
    s32 unk90;
    s32 unk94;
    s32 unk98;
    /* 0x9C */ s32 : 32;
    /* 0xA0 */ s32 : 32;
    /* 0xA4 */ s32 : 32;
    /* 0xA8 */ s32 : 32;
#ifdef VERSION_PC
    s32 _align_anim[2];
#endif
    u8 anim;
} ET_WeaponUnk046;

typedef struct {
    s32 unk7C;
    s32 : 32;
    s32 unk84;
    s32 unk88;
    byte pad[32];
#ifdef VERSION_PC
    s32 _align_anim[2];
#endif
    u8 anim;
} ET_WeaponUnk047;

typedef struct {
    s16 timer;
    s16 unk7E;
    s32 unk80;
    s16 unk84;
    s16 unk86;
    s16 unk88;
    s16 unk8A;
    s32 unk8C;
    s16 unk90;
    s16 unk92;
    s16 unk94;
    /* 0x98 */ s32 : 32;
    /* 0x9C */ s32 : 32;
    /* 0xA0 */ s32 : 32;
    /* 0xA4 */ s32 : 32;
    /* 0xA8 */ s32 : 32;
#ifdef VERSION_PC
    s32 _align_anim[2];
#endif
    u8 anim;
} ET_KarmaCoin;

typedef struct {
    s16 unk7C;
    s16 unk7E;
    s16 : 16;
    s16 unk82;
    s16 unk84;
    s16 unk86;
    byte pad[16];
    s32 vol;
    s32 unk9C;
    /* 0xA0 */ s32 : 32;
    /* 0xA4 */ s32 : 32;
    /* 0xA8 */ s32 : 32;
#ifdef VERSION_PC
    s32 _align_anim[2];
#endif
    u8 anim;
} ET_WeaponUnk012;

typedef struct {
    s16 unk7C;
    s16 : 16;
    byte pad[28];
    s16 unk9C;
    /* 0xA0 */ s32 : 32;
    /* 0xA4 */ s32 : 32;
    /* 0xA8 */ s32 : 32;
#ifdef VERSION_PC
    s32 _align_anim[2];
#endif
    u8 anim;
} ET_WeaponUnk014;

typedef struct PACKED {
    s16 unk7C;
    s16 unk7E;
    s16 unk80;
    s16 unk82;
    s16 unk84;
    s16 unk86;
    s16 unk88;
    s16 unk8A;
    struct Entity* parent;
    s16 unk90;
    s16 unk92;
    s16 unk94;
    s16 unk96;
    s16 unk98;
    s16 unk9A;
    s16 unk9C;
    s16 unk9E;
    s16 unkA0;
    s16 unkA2;
    s32 unkA4;
    s32 unkA8;
#ifdef VERSION_PC
    s32 _align_anim;
#endif
    u8 anim;
    u8 unkAD;
    s16 equipId;
} ET_Sword;

typedef struct PACKED {
    s16 angle;
    s16 unk7E;
    s16 unk80;
    s16 unk82;
    s16 unk84;
    s16 unk86;
    s16 xPos;
    s16 unk8A;
    struct Entity* parent;
    s32 unk90;
    s32 unk94;
    s32 unk98;
    s32 accelerationX;
    s32 accelerationY;
    s32 unkA4;
    s32 unkA8;
#ifdef VERSION_PC
    s32 _align_anim;
#endif
    u8 anim;
    u8 unkAD;
    s16 equipId;
} ET_HeavenSword;

typedef struct PACKED {
    s16 angle;
    s16 unk7E;
    s16 unk80;
    s16 unk82;
    s32 unk84;
    s16 xPos;
    s16 unk8A;
    struct Entity* parent;
    s32 unk90;
    s32 unk94;
    s32 unk98;
    s32 accelerationX;
    s32 accelerationY;
    s32 unkA4;
    s32 unkA8;
#ifdef VERSION_PC
    s32 _align_anim;
#endif
    u8 anim;
    u8 unkAD;
    s16 equipId;
} ET_HeavenSword2;

typedef struct PACKED {
    /* 0x7C */ u8 unk7C;
    /* 0x7D */ u8 unk7D;
    /* 0x7E */ s16 unk7E;
    /* 0x80 */ s16 unk80;
    /* 0x82 */ s16 unk82;
    /* 0x84 */ s16 unk84;
    /* 0x86 */ s16 unk86;
    /* 0x88 */ s16 childPalette;
    /* 0x8A */ s16 unk8A;
    /* 0x8C */ struct Entity* parent;
    /* 0x90 */ s16 unk90;
    /* 0x92 */ s16 unk92;
    /* 0x94 */ s16 unk94;
    /* 0x96 */ s16 unk96;
    /* 0x98 */ s16 unk98;
    /* 0x9A */ s16 unk9A;
    /* 0x9C */ s16 unk9C;
    /* 0x9E */ s16 unk9E;
    /* 0xA0 */ s16 unkA0;
    /* 0xA4 */ byte pad[10];
#ifdef VERSION_PC
    s32 _align_anim;
#endif
    /* 0xAC */ u8 anim;
    /* 0xAD */ u8 padAD;
    /* 0xAE */ s16 unkAE;
} ET_Shield;

typedef struct PACKED {
    /* 0x7C */ u8 unk7C;
    /* 0x7D */ u8 unk7D;
    /* 0x7E */ s16 unk7E;
    /* 0x80 */ u16 unk80;
    /* 0x82 */ s16 pal;
    /* 0x84 */ s16* palettePtr;
    /* 0x88 */ u16 childPalette;
    /* 0x8A */ s16 unk8A;
    /* 0x8C */ struct Entity* parent;
    /* 0x90 */ s16 unk90;
    /* 0x92 */ s16 unk92;
    /* 0x94 */ s16 unk94;
    /* 0x96 */ s16 unk96;
    /* 0x98 */ s16 unk98;
    /* 0x9A */ s16 unk9A;
    /* 0x9C */ s16 unk9C;
    /* 0x9E */ byte pad[14];
    /* 0xAC */ u8 anim;
    /* 0xAD */ u8 padAD;
    /* 0xAE */ s16 unkAE;
} ET_DarkShield;

typedef struct {
    /* 0x7D */ u8 unk7C;
    /* 0x7D */ u8 unk7D;
    /* 0x7E */ s16 unk7E;
    /* 0x80 */ s16 unk80;
    /* 0x82 */ s16 unk82;
    /* 0x84 */ s16 unk84;
    /* 0x86 */ s16 unk86;
    /* 0x88 */ s16 childPalette;
    /* 0x8A */ s16 unk8A;
    /* 0x8C */ struct Entity* parent;
    /* 0x90 */ struct Entity* target;
    /* 0x94 */ s16 unk94;
    /* 0x96 */ s16 unk96;
    /* 0x98 */ s32 unk98;
    /* 0x9C */ s16 unk9C;
    /* 0x9E */ s16 unk9E;
    /* 0xA0 */ s16 unkA0;
    /* 0xA2 */ s16 unkA2;
    /* 0xA4 */ s16 unkA4;
    /* 0xA6 */ u8 pad[4];
#ifdef VERSION_PC
    s16 _align_anim;
#endif
    /* 0xAC */ u8 anim;
    /* 0xAD */ u8 unkAD;
    /* 0xAE */ s16 unkAE;
} ET_MedusaShieldLaser;

typedef struct PACKED {
    /* 0x7C */ s16 unk7C;
    /* 0x7E */ s16 unk7E;
    /* 0x80 */ s16 unk80;
    /* 0x82 */ s16 unk82;
    /* 0x84 */ s16 unk84;
    /* 0x86 */ s16 unk86;
    /* 0x88 */ s16 childPalette;
    /* 0x8A */ s16 unk8A;
    /* 0x8C */ struct Entity* parent;
    /* 0x90 */ s16 unk90;
    /* 0x92 */ s16 unk92;
    /* 0x94 */ s16 unk94;
    /* 0x96 */ s16 unk96;
    /* 0x98 */ s16 unk98;
    /* 0x9A */ s16 unk9A;
    /* 0x9C */ s16 unk9C;
    /* 0x9E */ s16 unk9E;
    /* 0xA0 */ u32 : 32;
    /* 0xA4 */ u32 : 32;
    /* 0xA8 */ u32 : 32;
#ifdef VERSION_PC
    s32 _align_anim;
#endif
    /* 0xAC */ u8 anim;
} ET_ShamanShieldStar;

typedef struct PACKED {
    /* 0x7C */ u8 unk7C;
    /* 0x7D */ u8 unk7D;
    /* 0x7E */ s16 unk7E;
    /* 0x80 */ s16 unk80;
    /* 0x82 */ s16 unk82;
    /* 0x84 */ s16 unk84;
    /* 0x86 */ s16 unk86;
    /* 0x88 */ s16 childPalette;
    /* 0x8A */ s16 unk8A;
    /* 0x8C */ struct Entity* parent;
    /* 0x90 */ s16 unk90;
    /* 0x92 */ s16 unk92;
    /* 0x94 */ s16 unk94;
    /* 0x96 */ s16 unk96;
    /* 0x98 */ s16 unk98;
    /* 0x9A */ s16 unk9A;
    /* 0x9C */ u8 unk9C;
    /* 0x9D */ u8 pad[15];
#ifdef VERSION_PC
    s32 _align_anim;
#endif
    /* 0xAC */ u8 anim;
    /* 0xAE */ s16 unkAE;
} ET_HeraldShieldSwirlEffect;

typedef struct {
    s16 timer;
    s16 unk7E;
    s32 unk80;
    s16 pad[21];
    s16 foodId;
} ET_Food;

typedef struct {
    /* 0x7C */ char pad_7C[0x4];
    /* 0x80 */ s16 timer;
    /* 0x82 */ char pad_82[0x2];
    /* 0x84 */ u8 attackMode;
    /* 0x85 */ u8 flag;      // Slogra's moveMode / Gaibon's palette
    /* 0x86 */ u8 nearDeath; // Slogra loses spear, Gaibon in rage mode
    /* 0x88 */ s32 speed;
    /* 0x8C */ s16 angle;
    /* 0x8E */ char pad_8E[0xE];
    /* 0x9C */ u8 pickupFlag;
    /* 0x9D */ u8 grabedAscending;
} ET_GaibonSlogra;

typedef struct {
    /* 0x7C */ u16 angle;
    /* 0x7E */ u16 unk7E;
    /* 0x80 */ u16 unk80;
    /* 0x82 */ s16 unk82;
} ET_SoulStealOrb;

typedef struct {
    /* 0x7C */ Primitive* primBg;
    /* 0x80 */ s32 unused80;
    /* 0x84 */ Primitive* primFade;
    /* 0x88 */ s32 unk88;
} ET_WarpRoom;

typedef struct {
    /* 0x7C */ char pad_0[0x8];
    /* 0x84 */ u8 timer;
    /* 0x85 */ char pad_85[0x1];
    /* 0x86 */ s8 timer2;
    /* 0x87 */ char pad_87[0x5];
    /* 0x8C */ u16 palette;
    /* 0x8E */ char pad_8E[0x12];
    /* 0xA0 */ u8 isUnderwater;
    /* 0xA1 */ u8 ignoreCol;
} ET_Merman;

typedef struct {
    /* 0x7C */ struct Primitive* prim;
    /* 0x80 */ char pad_0[0x6];
    /* 0x86 */ s8 timer;
    /* 0x87 */ char pad_87[0x5];
    /* 0x8C */ s16 rotation;
    /* 0x8E */ char pad_8E[0x12];
    /* 0xA0 */ u8 isUnderwater;
    /* 0xA1 */ u8 ignoreCol;
} ET_Merman_2;

typedef struct {
    /* 0x7C */ s16 unk7C;
    /* 0x7E */ s16 unk7E;
    /* 0x80 */ s16 unk80;
    /* 0x82 */ s16 unk82;
    /* 0x84 */ s16 unk84;
    /* 0x84 */ s16 unk86;
    /* 0x88 */ s16 unk88;
    /* 0x8A */ s16 unk8A;
    /* 0x8C */ s16 unk8C;
    /* 0x8e */ s16 unk8E;
    /* 0x90 */ s32 unk90;
    /* 0x94 */ s32 unk94;
    /* 0x98 */ s32 unk98;
    /* 0x9C */ s16 unk9C;
    /* 0x9E */ s16 unk9E;
    /* 0xA0 */ s32 unkA0;
    /* 0xA4 */ struct Entity* target;
    /* 0xA8 */ s16 unkA8;
    /* 0xAA */ s16 unkAA;
    /* 0xAC */ s16 cameraX;
    /* 0xAE */ s16 cameraY;
    /* 0xB0 */ s16 unkB0;
    /* 0xB2 */ s16 unkB2;
    /* 0xB4 */ struct Entity* follow;
} ET_Bat;

typedef struct {
    /* 0x7C */ s32 : 32;
    /* 0x80 */ s32 : 32;
    /* 0x84 */ s32 : 32;
    /* 0x88 */ s32 : 32;
    /* 0x8C */ struct Entity* parent;
} ET_BatFamBlueTrail;

typedef struct {
    s16 unk7C;
    s16 unk7E;
    s16 unk80;
    s16 unk82;
    struct Primitive* unk84;
    s16 unk88;
    s16 unk8A;
} ET_BatEcho;

typedef struct {
    /* 0x7C */ char pad_0[0xC];
    /* 0x88 */ u16 unk88;
    /* 0x8A */ char pad_8A[0x3];
    /* 0x8D */ u8 unk8D;
    /* 0x8E */ char pad_8E[0xE];
    /* 0x9C */ s16 unk9C;
    /* 0xA0 */ struct Entity* next;
} ET_801CF254;

typedef struct {
    /* 0x7C */ char pad_0[0x4];
    /* 0x80 */ s16 unk80;
    /* 0x82 */ char pad_82[0xA];
    /* 0x8C */ u8 unk8C;
    /* 0x8D */ char pad_8D[0xF];
    /* 0x9C */ u16 unk9C;
    /* 0x9E */ char pad_9E[0x8];
    /* 0xA6 */ s16 unkA6;
} ET_GurkhaSword;

struct draculaPrimitive;
typedef struct ET_Dracula {
    /* 0x7C */ char pad_7C[4];
    /* 0x80 */ struct draculaPrimitive* unk80;
    /* 0x84 */ struct draculaPrimitive* unk84;
    /* 0x88 */ char pad_88[4];
    /* 0x8C */ s16 unk8C;
    /* 0x8E */ char pad_8E[0x2];
    /* 0x90 */ u8 unk90;
    /* 0x91 */ char pad91;
    /* 0x92 */ u8 unk92;
    /* 0x93 */ char pad93;
    /* 0x94 */ u8 unk94;
    /* 0x95 */ char pad_95[0x3];
    /* 0x98 */ s16 unk98;
    /* 0x9A */ char pad_9A[0x2];
    /* 0x9C */ s16 unk9C;
    /* 0x9E */ char pad_9E[0x2];
    /* 0xA0 */ u8 unkA0;
    /* 0xA1 */ u8 unkA1;
    /* 0xA2 */ u8 unkA2;
    /* 0xA3 */ char pad_A3[0x9];
    /* 0xAC */ struct Primitive* prim;
} ET_Dracula;

typedef struct {
    /* 0x7C */ struct Primitive* prim;
    /* 0x80 */ s32 unk80;
    /* 0x84 */ s32 unk84;
    /* 0x88 */ s16 unk88;
    /* 0x8A */ char pad_8A[0x2];
    /* 0x8C */ s16 unk8C;
    /* 0x8E */ s16 unk8E;
} ET_StageTitleCard;

typedef struct ET_Succubus {
    /* 0x7C */ char pad_7C[0x4];
    /* 0x80 */ s16 timer;
    /* 0x82 */ char pad_82[0x2];
    /* 0x84 */ u8 facingLeft;
    /* 0x85 */ u8 unk85;
    /* 0x86 */ u8 nextAttack;
    /* 0x87 */ u8 unk87;
    /* 0x88 */ u16 nextStep;
    /* 0x8A */ char pad_8A[0x4];
    /* 0x8E */ s16 yOffset;
    /* 0x90 */ char pad_90[0xC];
    /* 0x9C */ struct Entity* real;
    /* 0xA0 */ s16 clonePosX;
    /* 0xA2 */ s16 unkA2;
} ET_Succubus;

typedef struct {
    /* 0x7C */ u16 timer;
    /* 0x7E */ char pad_7E[2];
    /* 0x80 */ s32 unk80;
} ET_RoomTransition2;

typedef struct {
    /* 0x7C */ u8 pad0[0x4];
    /* 0x80 */ s32 unk80;
    /* 0x84 */ s16 unk84;
    /* 0x86 */ u8 pad86[2];
    /* 0x88 */ u8 unk88;
    /* 0x89 */ u8 unk89;
} ET_WargExplosionPuffOpaque;

typedef struct {
    /* 0x7C */ u16 unk7C;
} ET_801BCC4C;

typedef struct ET_CastleDoor {
    /* 0x7C */ struct Primitive* prim;
    /* 0x80 */ s16 timer;
    /* 0x82 */ char pad_82[0x2];
    /* 0x84 */ s16 rotZ;
} ET_CastleDoor;

typedef struct {
    /* 0x7C */ struct Primitive* prim;
    /* 0x80 */ s16 unk80; // angle?
    /* 0x82 */ s16 unk82;
    /* 0x84 */ s16 timer;
} ET_ShuttingWindow;

typedef struct {
    /* 0x7C */ struct Primitive* prim;
    /* 0x80 */ char pad_80[0x4];
    /* 0x84 */ u16 unk84;
} ET_DeathSkySwirl;

typedef struct {
    /* 0x7C */ struct Primitive* prim;
    /* 0x80 */ char pad_80[0x4];
    /* 0x84 */ s32 elevatorTarget;
} ET_Elevator;

typedef struct {
    /* 0x7C */ s32 pad[8];
    /* 0x84 */ s16 unk84;
    /* 0x86 */ s16 unk86;
    /* 0x88 */ s16* unk88;
} ET_801D0B40;

typedef struct {
    /* 0x7C */ struct Primitive* prim;
    /* 0x80 */ char pad_80[0xC];
    /* 0x8C */ u8 unk8C;
    /* 0x8D */ u8 unk8D;
    /* 0x8E */ char pad_8E[0xE];
    /* 0x9C */ u16 unk9C;
} ET_801D1BB8;

typedef struct {
    /* 0x7C */ char pad_0[0xC];
    /* 0x88 */ u16 unk88;
} ET_801D0B78;

typedef struct {
    /* 0x7C */ s32 accelY;
    /* 0x80 */ s16 : 16;
    /* 0x82 */ s16 unk82;
    /* 0x84 */ f32 topY;
    /* 0x88 */ u16 unk88;
    /* 0x8A */ s16 unk8A;
} ET_WaterEffects;

typedef struct {
    /* 0x7C */ char pad_0[4];
    /* 0x80 */ s16 unk80;
    /* 0x82 */ char pad_82[2];
    /* 0x84 */ u8 unk84;
    /* 0x85 */ char pad_85[3];
    /* 0x88 */ u16 unk88;
    /* 0x8A */ char pad_8A[2];
    /* 0x8C */ u8 unk8C;
    /* 0x8D */ u8 unk8D;
    /* 0x8E */ u8 unk8E;
    /* 0x8E */ char pad_8E[13];
    /* 0x9C */ s16 rotZ;
    /* 0x9E */ s16 unk9E;
    /* 0xA0 */ struct Entity* parent;
    /* 0xA4 */ s16 unkA4;
    /* 0xA6 */ s16 unkA6;
    /* 0xA8 */ u8 unkA8;
    /* 0xA9 */ char pad_A9[0x7];
    /* 0xB0 */ u16 unkB0[0x6];
} ET_GurkhaHammer;

typedef struct {
    /* 0x7C */ char pad_0[0x20];
    /* 0x9C */ s16 unk9C;
    /* 0xA0 */ char pad_A0[0x6];
    /* 0xA4 */ s16 unkA4;
    /* 0xA6 */ s16 unkA6;
    /* 0xA9 */ char pad_A8[0xC];
    /* 0xB0 */ u16 unkB4;
} ET_801CDFD8;

typedef struct {
    /* 0x7C */ char pad_0[0x8];
    /* 0x84 */ u8 unk84;
    /* 0x85 */ char pad_85[0x9];
    /* 0x8E */ u8 unk8E;
    /* 0x8F */ char pad_8F[0x20];
    /* 0xB0 */ s16 unkB0;
} ET_801CE4CC;

typedef struct {
    /* 0x7C */ struct Primitive* prim;
    /* 0x80 */ s16 unk80;
} ET_TransparentWater;

typedef struct {
    /* 0x7C */ struct Primitive* prim;
    /* 0x80 */ s32 timer;
} ET_HeartRoomGoldDoor;

typedef struct {
    /* 0x7C */ struct Primitive* prim;
    /* 0x80 */ char pad_80[0x4];
    /* 0x84 */ s8 unk84;
    /* 0x85 */ char pad_85[0x1];
    /* 0x86 */ s8 unk86;
} ET_MermanWaterSplash;

typedef struct {
    /* 0x7C */ s32 playerVelocity;
} ET_CastleDoorTransition;

typedef struct {
    /* 0x7C */ s8 unk7C;
} ET_AlucardController;

typedef struct {
    /* 0x7C */ u16 unk7C;
} ET_ForegroundTree;

typedef struct {
    /* 0x7C */ u16 unk7C;
    /* 0x7E */ u16 unk7E;
    /* 0x80 */ s16 unk80;
} ET_FadeToWhite;

typedef struct {
    /* 0x7C */ u16 unk7C;
} ET_DeathStolenItems;

typedef struct {
    /* 0x7C */ u16 unk7C;
    /* 0x7E */ char pad_7E[0x2];
    /* 0x80 */ s16 posX;
    /* 0x82 */ s16 posY;
    /* 0x84 */ u16 moveTimer;
    /* 0x86 */ u16 moveDirection;
} ET_Death;

typedef struct {
    /* 0x7C */ u8 unk7C;
    /* 0x7D */ char pad_7D[0x3];
    /* 0x80 */ s16 unk80;
    /* 0x82 */ s16 unk82;
    /* 0x84 */ struct Entity* unk84;
} ET_SpittleBone;

typedef struct PACKED {
    Primitive* prim;
    char pad[0x24];
    s16 unkA4;
    s16 unkA6;
    void* unkA8;
    u8 anim;
    char pad2[0x8];
    struct Entity* unkB8;
} ET_Player;

typedef struct {
    u8 unk0;
    u8 unk1;
    u8 unk2;
    u8 unk3;
} ET_EntitySlot1;

typedef struct {
    char pad[0x32];
    s16 unkAE;
} ET_EntitySlot16;

typedef struct {
    /* 0x7C */ s16 unk7C;
} ET_Entity12;

typedef struct {
    u8 fiveFrameCounter;
    struct Entity* parent;
    char pad[8];
    u16 parentId;
} ET_Entity13;

typedef struct {
    s16 t;
} ET_TimerOnly;

typedef struct {
    char pad[8];
    struct Primitive* prim;
} ET_AxeKnight;

typedef struct {
    /* 0x7C */ s16 unk7C;
    /* 0x7E */ s16 unk7E;
    /* 0x80 */ s16 unk80;
    /* 0x82 */ s16 unk82;
    /* 0x84 */ s16 unk84;
    /* 0x86 */ s16 unk86;
    /* 0x88 */ s16 unk88;
    /* 0x8A */ s16 unk8A;
    /* 0x8C */ struct Entity* parent;
    /* 0x90 */ s16 childId;
    /* 0x92 */ s16 unk92;
    /* 0x94 */ s16 unk94;
    /* 0x96 */ s16 unk96;
    /* 0x98 */ s16 unk98;
    /* 0x9A */ s16 unk9A;
    /* 0x9C */ s16 unk9C;
    /* 0x9E */ s16 unk9E;
    /* 0xA0 */ s16 unkA0;
    /* 0xA2 */ s16 unkA2;
    /* 0xA4 */ s16 unkA4;
    /* 0xA6 */ s16 unkA6;
    /* 0xA8 */ s16 unkA8;
    /* 0xAA */ s16 unkAA;
    /* 0xAC */ s16 unkAC;
    /* 0xAE */ s16 unkAE;
    /* 0xB0 */ s16 unkB0;
    /* 0xB2 */ s16 unkB2;
} ET_EntFactory;

typedef struct {
    char pad[8];
    s32 unk8;
} unk_sub_8011E4BC;

typedef struct {
    s16 unk7C;
    byte pad[14];
    /* 0x8C */ struct Entity* parent;
} ET_8011E4BC;

typedef struct {
    s16 unk7C;
    s16 unk7E;
    s16 unk80;
} ET_HellfireHandler;

typedef struct {
    s16 stoneAngle;
    s16 lifeTimer;
    s16 unk80;
    s16 unk82;
    s16 unk84;
    /* 0x86 */ s16 : 16;
    /* 0x88 */ s32 : 32;
    /* 0x8C */ struct Entity* parent;
    /* 0x90 */ s32 : 32;
    /* 0x94 */ s32 : 32;
    /* 0x98 */ s32 : 32;
    /* 0x9C */ s32 : 32;
    /* 0xA0 */ s32 : 32;
    /* 0xA4 */ s32 : 32;
    /* 0xA8 */ s32 : 32;
    /* 0xAC */ s32 : 32;
    /* 0xB0 */ s16 subweaponId;
} ET_ReboundStone;
typedef struct {
    s16 unk7C;
    s16 unk7E;
    s16 unk80;
    s16 unk82;
    s16 unk84;
    s16 unk86;
    /* 0x88 */ s32 : 32;
    /* 0x8C */ struct Entity* parent;
    /* 0x90 */ s32 : 32;
    /* 0x94 */ s32 : 32;
    /* 0x98 */ s32 : 32;
    /* 0x9C */ s32 : 32;
    /* 0xA0 */ s32 : 32;
    /* 0xA4 */ s32 : 32;
    /* 0xA8 */ s32 : 32;
    /* 0xAC */ s32 : 32;
    /* 0xB0 */ s16 subweaponId;
} ET_ReboundStoneCrashExplosion;

typedef struct {
    /* 0x7C */ s16 unk7C;
    /* 0x7E */ s16 unk7E;
    /* 0x80 */ s32 : 32;
    /* 0x84 */ s32 : 32;
    /* 0x88 */ s32 : 32;
    /* 0x8C */ struct Entity* parent;
    /* 0x90 */ s32 : 32;
    /* 0x94 */ s32 : 32;
    /* 0x98 */ s32 : 32;
    /* 0x9C */ s32 : 32;
    /* 0xA0 */ s32 : 32;
    /* 0xA4 */ s32 : 32;
    /* 0xA8 */ s32 : 32;
    /* 0xAC */ s32 : 32;
    /* 0xB0 */ s16 subweaponId;
} ET_GiantSpinningCross;

typedef struct {
    s16 unk7C;
    s16 unk7E;
    /* 0x80 */ s32 : 32;
    /* 0x84 */ s32 : 32;
    /* 0x88 */ s32 : 32;
    /* 0x8C */ struct Entity* parent;
} ET_8017091C;

typedef struct {
    s16 unk7C;
    s16 unk7E;
    s16 unk80;
    s16 unk82;
    s32 unk84;
    s32 unk88;
    /* 0x8C */ struct Entity* parent;
    s32 : 32;
    s32 : 32;
    s32 : 32;
    s32 : 32;
    s32 : 32;
    s32 : 32;
    s32 : 32;
    s32 : 32;
    s16 subweaponId;
#ifndef VERSION_PC
    s32 pad2;
#endif
    struct Entity* parent2;
} ET_Agunea;
typedef struct {
    s16 unk7C;
    s16 unk7E;
    s16 unk80;
    s16 unk82;
    s32 : 32;
    s32 : 32;
    /* 0x8C */ struct Entity* parent;
    s32 : 32;
    s32 : 32;
    s32 : 32;
    s32 : 32;
    s32 : 32;
    s32 : 32;
    s32 : 32;
    s32 : 32;
    s16 subweaponId;
} ET_AguneaCrash;
typedef struct {
    s16 timer;
    s16 size;
    s32 : 32;
    s32 : 32;
    s32 : 32;
    /* 0x8C */ struct Entity* parent;
} ET_stopwatchCircle;
typedef struct {
    s16 unk7C;
    s16 unk7E;
    s16 unk80;
    s16 unk82;
    f32 unk84;
    s32 unk88;
    /* 0x8C */ struct Entity* parent;
    s16 unk90;
    s16 unk92;
    s16 unk94;
    s16 unk96;
    struct Entity* unk98;
    s32 : 32;
    s32 : 32;
    s32 : 32;
    s32 : 32;
#ifndef VERSION_PC
    s32 : 32;
#endif
    s16 subweaponId;
} ET_StopWatch;
typedef struct {
    s16 t;
    s16 unk7E;
    s16 unk80;
    s16 unk82;
    f32 unk84;
    f32 unk88;
    s16 unk8C;
    s16 unk8E;
} ET_stopwatch;
typedef struct {
    s16 unk7C;
    s16 unk7E;
    s16 unk80;
    s16 unk82;
    s16 unk84;
    s16 unk86;
    struct Primitive* unk88;
    s16 unk8C;
    s16 unk8E;
    s16 unk90;
    s16 unk92;
    s16 unk94;
} ET_stopwatchSparkle;
typedef struct {
    s16 unk7C;
    s16 unk7E;
    s16 unk80;
    s16 unk82;
    s16 unk84;
    s16 unk86;
    s32 unk88;
    /* 0x8C */ struct Entity* parent;
    s16 unk90;
    s16 unk92;
    s16 unk94;
    s16 unk96;
    struct Entity* unk98;
    s32 : 32;
    s32 : 32;
    s32 : 32;
    s32 : 32;
#ifndef VERSION_PC
    s32 : 32;
#endif
    s16 subweaponId;
} ET_BibleSubwpn;

typedef struct {
    s16 unk7C; // TODO rename as timer
    s16 unk7E;
    /* 0x80 */ s32 : 32;
    /* 0x84 */ s32 : 32;
    /* 0x88 */ s32 : 32;
    /* 0x8C */ struct Entity* parent;
    /* 0x90 */ s32 : 32;
    /* 0x94 */ s32 : 32;
    /* 0x98 */ s32 : 32;
    /* 0x9C */ s32 : 32;
    /* 0xA0 */ s32 : 32;
    /* 0xA4 */ s32 : 32;
    /* 0xA8 */ s32 : 32;
    /* 0xAC */ s32 : 32;
} ET_80161FF0;

typedef struct {
    s16 unk7C;
    s16 unk7E;
    s16 unk80;
    s16 unk82;
    /* 0x84 */ s32 : 32;
    /* 0x88 */ s32 : 32;
    /* 0x8C */ struct Entity* parent;
} ET_80162870;

typedef struct {
    s16 unk7C;
    s16 unk7E;
    s16 unk80;
    s16 unk82;
    s16 unk84;
    s16 unk86;
    s32 unk88;
    struct Entity* parent;
} ET_8016E9E4;

typedef struct {
    u8 unk7C;
    u8 unk7D[3];
    s16 unk80;
    s16 unk82;
    s16 unk84;
    s16 unk86;
} ET_801CC820;

typedef struct {
    s16 unk7C;
    s16 unk7E;
    s16 unk80;
    s16 unk82;
    s16 unk84;
    s16 unk86;
    s16 unk88;
    s16 unk8A;
    struct Entity* parent;
} ET_RichterPowerUpRing;

typedef struct {
    s16 unk7C;
    s16 unk7E;
    s16 unk80;
    s16 unk82;
    s16 unk84;
    s16 unk86;
    s16 unk88;
    s16 unk8A;
} ET_TransparentWhiteCircle;

typedef struct {
    s16 unk7C;
    s16 unk7E;
    s16 unk80;
    s16 unk82;
    s32 : 32;
    s32 : 32;
    struct Entity* parent;
} ET_HitByIce;

typedef struct {
    s16 unk7C;
    s16 pad7E;
    s16 unk80;
    s16 unk82;
    s32 : 32;
    s32 : 32;
    struct Entity* parent;
    s16 unk90;
    s16 unk92;
    s16 unk94;
    s16 pad96[3];
    s16 unk9C;
} ET_HitByLightning;

typedef struct {
    s32 unk7C;
    s32 unk80;
    s32 unk84;
    s32 unk88;
    struct Entity* parent;
    s32 unk90;
} ET_Teleport;

typedef struct {
    /* 0x7C */ s16 timer;
    /* 0x7E */ s16 : 16;
    /* 0x80 */ s32 : 32;
    /* 0x84 */ s32 : 32;
    /* 0x88 */ s32 : 32;
    /* 0x8C */ struct Entity* parent;
    /* 0x90 */ s32 : 32;
    /* 0x94 */ s32 : 32;
    /* 0x98 */ s32 : 32;
    /* 0x9C */ s32 : 32;
    /* 0xA0 */ s32 : 32;
    /* 0xA4 */ s32 : 32;
    /* 0xA8 */ s32 : 32;
    /* 0xAC */ s32 : 32;
    /* 0xB0 */ s16 subweaponId;
} ET_Subweapon;
typedef struct {
    s16 timer;
    s16 angle;
    s16 unk80;
    s16 unk82;
    s16 hitboxState;
    /* 0x86 */ s16 : 16;
    /* 0x88 */ s32 : 32;
    /* 0x8C */ struct Entity* parent;
    /* 0x90 */ s32 : 32;
    /* 0x94 */ s32 : 32;
    /* 0x98 */ s32 : 32;
    /* 0x9C */ s32 : 32;
    /* 0xA0 */ s32 : 32;
    /* 0xA4 */ s32 : 32;
    /* 0xA8 */ s32 : 32;
    /* 0xAC */ s32 : 32;
    /* 0xB0 */ s16 subweaponId;
} ET_HolyWater;
typedef struct {
    u16 unk7C;
    u16 unk7E;
    u8 unk80;
    byte pad81;
    u8 unk82;
    byte pad83;
    s32 unk84;
    /* 0x88 */ s32 : 32;
    /* 0x8C */ struct Entity* parent;
    /* 0x90 */ s32 : 32;
    /* 0x94 */ s32 : 32;
    /* 0x98 */ s32 : 32;
    /* 0x9C */ s32 : 32;
    /* 0xA0 */ s32 : 32;
    /* 0xA4 */ s32 : 32;
    /* 0xA8 */ s32 : 32;
    /* 0xAC */ s32 : 32;
    /* 0xB0 */ s16 subweaponId;
} ET_CrashCross;
typedef struct {
    s16 timer;
    s16 unk7E;
    u16 unk80;
    u16 pad82;
    Point16* unk84;
#ifndef VERSION_PC
    /* 0x88 */ s32 : 32;
#endif
    /* 0x8C */ struct Entity* parent;
    /* 0x90 */ s32 : 32;
    /* 0x94 */ s32 : 32;
    /* 0x98 */ s32 : 32;
    /* 0x9C */ s32 : 32;
    /* 0xA0 */ s32 : 32;
    /* 0xA4 */ s32 : 32;
    /* 0xA8 */ s32 : 32;
    /* 0xAC */ s32 : 32;
    /* 0xB0 */ s16 subweaponId;
} ET_CrossBoomerang;
typedef struct {
    s16 unk7C;
    s16 unk7E;
    s16 unk80;
    s16 unk82;
    s16 unk84;
    s16 unk86;
    s16 unk88;
    s8 unk8A;
    u8 unk8B[12];
    s32 unk98;
    /* 0x9C */ s32 : 32;
    /* 0xA0 */ s32 : 32;
    /* 0xA4 */ s32 : 32;
    /* 0xA8 */ s32 : 32;
    /* 0xAC */ s32 : 32;
#ifdef VERSION_PC
    s32 : 32;
#endif
    /* 0xB0 */ s16 subweaponId;
} ET_SubwpnAxe;
typedef struct {
    s16 unk7C;
    s16 unk7E;
    s16 unk80;
    s16 unk82;
    s16 unk84;
    s16 unk86;
    s16 unk88;
    s8 unk8A;
    u8 unk8B[12];
    s32 unk98;
    s32 unk9C;
    u16 unkA0;
    u16 : 16;
    /* 0xA4 */ s32 : 32;
    /* 0xA8 */ s32 : 32;
    /* 0xAC */ s32 : 32;
#ifdef VERSION_PC
    s32 : 32;
#endif
    /* 0xB0 */ s16 subweaponId;
} ET_AxeCrash;
typedef struct {
    s16 timer;
    u16 unk7E;
    s16 unk80;
    s16 pad82;
    s32 unk84;
    s32 unk88;
    u16 unk8C;
} ET_VibhutiCrash;
typedef struct {
    s16 unk7C;
    s16 : 16;
    s32 : 32;
    s32 : 32;
    s32 : 32;
    struct Entity* parent;
    /* 0x90 */ s32 : 32;
    /* 0x94 */ s32 : 32;
    /* 0x98 */ s32 : 32;
    /* 0x9C */ s32 : 32;
    /* 0xA0 */ s32 : 32;
    /* 0xA4 */ s32 : 32;
    /* 0xA8 */ s32 : 32;
    /* 0xAC */ s32 : 32;
    /* 0xB0 */ s16 subweaponId;
} ET_VibhutiCrashCloud;
typedef struct {
    s16 unk7C;
    s16 unk7E;
    s16 unk80;
    s16 : 16;
    s32 : 32;
    /* 0x88 */ s32 : 32;
    struct Entity* parent;
    /* 0x90 */ s32 : 32;
    /* 0x94 */ s32 : 32;
    /* 0x98 */ s32 : 32;
    /* 0x9C */ s32 : 32;
    /* 0xA0 */ s32 : 32;
    /* 0xA4 */ s32 : 32;
    /* 0xA8 */ s32 : 32;
    /* 0xAC */ s32 : 32;
    s16 subweaponId;
} ET_BibleBeam;

typedef struct {
    u16 unk7C;
    u16 unk7E;
    u8 unk80;
    byte pad81;
    u8 unk82;
    byte pad83;
    s32 unk84;
    struct Entity* parent;
} ET_RicRevivalColumn; // Note this is the same as CrashCross

typedef struct {
    f32 unk7C;
    f32 unk80;
    s16 unk84;
    s16 unk86;
    s32 unk88;
    s16 unk8C;
    s16 unk8E;
    s32 unk90;
    s32 unk94;
    s32 unk98;
    s32 unk9C;
    s32 unkA0;
    s16 unkA4;
    s16 unkA6;
    s32 unkA8;
    s32 unkAC;
    s16 unkB0;
    s32 unkB4;
    s32 unkB8;
} ET_Whip;

typedef struct {
#ifndef VERSION_PC
    s32 pad7c;
#endif
    Primitive* unk80;
    s16 unk84;
    s16 unk86;
    s16 unk88;
    struct Entity* parent;
    s16 unk90;
} ET_801291C4;

typedef struct {
    PrimLineG2* lines[4];
    s16 unk8C;
    s16 unk8E;
    s16 unk90;
} ET_8016D9C4;

typedef struct {
    struct Primitive* prim1;
    struct Primitive* prim2;
    struct Primitive* prim3;
    struct Primitive* prim4;
    s16 unk8C;
    s16 unk8E;
    u8 unk90;
} ET_801AF774;

typedef struct {
    s32 unk7C;
    s16 timer;
    s16 unk82;
    s16 unk84;
} ET_DracFinal;

// To be used for EntityEquipItemDrop and/or EntityPrizeDrop, when they are
// moved off of Generic.
typedef struct {
    byte pad[0x18];
    s32 unk94;
} ET_Drop;

typedef struct {
    /* 0x7C */ byte pad[4];
    /* 0x80 */ s16 angle;
    /* 0x82 */ byte pad2[2];
    /* 0x84 */ u8 switch_control;
    /* 0x85 */ u8 speed;
} ET_BigRedFireball;

typedef struct {
    s16 timer;
    s16 spawnTimer;
} ET_SummonSpirit;

typedef struct {
    struct Primitive* prim;
    s16 unk80;
    s16 unk82;
    s16 unk84;
} ET_3DBackgroundhouse;

typedef struct {
    struct Primitive* prim1;
    struct Primitive* prim2;
    s16 unk84;
    s16 unk86;
    s16 unk88;
} ET_LifeUpSpawn;

typedef struct {
    u16 unk7C;
    u16 unk7E;
    s16 unk80;
    s16 unk82;
    s16 unk84;
    s16 unk86;
    u16 unk88;
    u16 unk8A;
} ET_801B0AA4;

typedef struct {
    byte pad[4];
    u16 unk80;
    u16 unk82;
    s16 unk84;
    s16 unk86;
    s16 unk88;
    s16 unk8A;
    u8 unk8C;
} ET_Owl;

typedef struct {
    u16 unk7C;
    s16 unk7E;
    s16 unk80;
    s16 unk82;
    s16 unk84;
    s16 unk86;
    u16 unk88;
    s16 unk8A;
    s16 unk8C;
    s16 unk8E;
} ET_AlucardWaterEffect;
typedef struct {
    s32 pad;
    s16 timer;
} ET_801B28E4;

typedef struct {
    u32 unk24[10];
    u8 unk28;
    u8 unk29;
} ET_80123B40;

typedef struct {
    struct Entity* ent;
    s16 unk80;
    s16 unk82;
    s16 unk84;
    s16 unk86;
} ET_80129864;

typedef struct {
    s16 timer;
    s16 pad;
    s16 xCurrent;
    s16 yCurrent;
    s16 xTarget;
    s16 yTarget;
} ET_Mist;

typedef struct {
    s32 unk7C;
    s16 unk80;
    s16 unk82;
    s32 un84;
    s16 unk88;
    s16 unk8A;
    struct Entity* parent;
    s16 unk90;
    s16 unk92;
    s32 unk94;
    s16 unk98;
    s16 unk9A;
    s16 unk9C;
} ET_PlayerBlink;

typedef struct {
    struct Primitive* prim;
    s16 unk80;
    s16 pad82;
    s32 pad84;
    s32 pad88;
    struct Primitive* prim2;
    struct Primitive* prim3;
} ET_BloodSplatter;

typedef struct {
    s32 pad7c;
    s16 timer;
    s16 pad82;
    s32 pad84;
    s32 pad88;
    s32 pad8C;
    s16 brightness;
} ET_PlayerOutline;

typedef struct {
    u8 digits[4];
    s16 unk80;
    s16 unk82;
    s16 unk84;
    u16 unk86;
    u16 unk88;
    u16 unk8A;
    s16 unk8C;
    s16 unk8E;
    s16 unk90;
    s16 unk92;
    s16 angleToMeter;
    s16 distToMeter;
    s16 unk98;
} ET_HPNumberMove;

typedef struct {
    s16 timer;
    s16 pad1;
    s16 halfWidth;
    s16 halfHeight;
    s32 pad2;
    s16 angle;
    s16 pad3;
    s32 pad4;
    s32 str_x;
    s32 str_y;
    s32 unk98;
} ET_GuardText;

typedef struct {
    s16 unk7C;
    s16 unk7E;
    s16 unk80;
} ET_Dissolve;

typedef struct {
    u16 unk7C;
} ET_LockCamera;

typedef struct {
    struct Primitive* prim;
    s32 jiggler;
    s8 collision;
    f32 xCoord;
    f32 yCoord;
} ET_CavernDoor;

// Unknown g_Entities[8] and [1] accessed directly in SEL
typedef struct {
    /* 0x7C */ s32 : 32;
    /* 0x80 */ s32 : 32;
    /* 0x84 */ s32 : 32;
    /* 0x88 */ s16 unk88;
    /* 0x8A */ s16 : 16;
    /* 0x8C */ s32 unk8C;
} ET_UnkSelEnts;

typedef struct {
    /* 0x7C */ s32 : 32;
    /* 0x80 */ s16 spawnDelay;
    /* 0x82 */ s16 : 16;
    /* 0x84 */ s32 : 32;
    /* 0x88 */ s32 spawnSide;
} ET_ZombieSpawner;

typedef struct {
    /* 0x7C */ u8 attackTimer;
    /* 0x7D */ s32 : 24;
    /* 0x80 */ u8 facingLeft;
    /* 0x81 */ s32 : 24;
    /* 0x84 */ u8 attackTimerIndex;
    /* 0x85 */ s32 : 24;
    /* 0x88 */ s8 explosionTimer;
    /* 0x89 */ s32 : 24;
    /* 0x8C */ s32 : 32;
    /* 0x90 */ s32 : 32;
    /* 0x94 */ s32 : 32;
    /* 0x98 */ s32 : 32;
    /* 0x9C */ s32 initialX;
} ET_Skeleton;

// Common EXT member for all of NZ0/311C0.c file.
typedef struct {
    /* 0x7C */ struct Primitive* prim;
    /* 0x80 */ s32 unk80;
    /* 0x84 */ s32 unk84;
    /* 0x88 */ u8 unk88;
} ET_NZ0_311C0;

// ====== RIC ENTITIES ======

// ==========================

typedef union { // offset=0x7C
    struct Primitive* prim;
    char stub[0x40];
    ET_TimerOnly timer;
    ET_EntFactory factory;
    ET_Generic generic;
    ET_EntitySlot1 entSlot1; // g_Entities[1], not entityID 1
    ET_EntitySlot16 entSlot16;
    ET_Entity12 ent12; // entityID 12
    ET_Entity13 ent13; // entityID 13
    ET_8011E4BC et_8011E4BC;
    ET_HellfireHandler hellfireHandler;
    ET_8016D9C4 et_8016D9C4;
    ET_ReboundStoneCrashExplosion reboundStoneCrashExplosion;
    ET_CrossBoomerang crossBoomerang;
    ET_Subweapon subweapon;
    ET_HolyWater holywater;
    ET_CrashCross crashcross;
    ET_SubwpnAxe subwpnAxe;
    ET_AxeCrash axeCrash;
    ET_VibhutiCrash vibhutiCrash;
    ET_VibhutiCrashCloud vibCrashCloud;
    ET_RicRevivalColumn ricColumn;
    ET_GiantSpinningCross giantcross;
    ET_ReboundStone reboundStone;
    ET_BibleBeam bibleBeam;
    ET_BibleSubwpn et_BibleSubwpn;
    ET_EquipItemDrop equipItemDrop;
    ET_HeartDrop heartDrop;
    ET_BloodDroplets bloodDroplets;
    ET_BloodSplatter bloodSplatter;
    ET_NumericDamage ndmg;
    ET_RelicOrb relicOrb;
    ET_Door door;
    ET_StagePopup stpopup;
    ET_StagePopupJP stpopupj;
    ET_MessageBox messageBox;
    ET_Weapon weapon;
    ET_WeaponUnk006 weapon_006;
    ET_WeaponUnk012 weapon_012;
    ET_WeaponUnk014 weapon_014;
    ET_WeaponUnk030 weapon_030;
    ET_WeaponUnk046 weapon_046;
    ET_WeaponUnk047 weapon_047;
    ET_Shield shield;
    ET_DarkShield darkShield;
    ET_KarmaCoin karmacoin;
    ET_Sword sword;
    ET_HeavenSword heavenSword;
    ET_HeavenSword2 heavenSword2;
    ET_MedusaShieldLaser medshieldlaser;
    ET_ShamanShieldStar shamanshieldstar;
    ET_HeraldShieldSwirlEffect heraldSwirl;
    ET_Food food;
    ET_HitByIce hitbyice;
    ET_HitByLightning hitbylightning;
    ET_PlayerBlink playerBlink;
    ET_Mist mist;
    ET_Bat bat;
    ET_BatFamBlueTrail batFamBlueTrail;
    ET_BatEcho batEcho;
    ET_SoulStealOrb soulStealOrb;
    ET_GaibonSlogra GS_Props;
    ET_WarpRoom warpRoom;
    ET_Teleport teleport;
    ET_Merman merman;
    ET_Merman_2 merman2;
    ET_MermanWaterSplash mermanWaterSplash;
    ET_Agunea agunea;
    ET_801291C4 et_801291C4;
    ET_8017091C et_8017091C;
    ET_AguneaCrash aguneaCrash;
    ET_stopwatch stopwatch;
    ET_StopWatch et_801719A4;
    ET_stopwatchCircle et_stopwatchCircle;
    ET_stopwatchSparkle et_stopWatchSparkle;
    ET_80161FF0 et_80161FF0;
    ET_80162870 et_80162870;
    ET_Whip whip;
    ET_RichterPowerUpRing ricPowerRing;
    ET_TransparentWhiteCircle whiteCircle;
    ET_8016E9E4 et_8016E9E4;
    ET_801CF254 et_801CF254;
    ET_GurkhaSword gurkhaSword;
    ET_Dracula dracula;
    ET_DracFinal dracFinalForm;
    ET_Succubus succubus;
    ET_StageTitleCard stageTitleCard;
    ET_RoomTransition2 roomTransition2;
    ET_WargExplosionPuffOpaque wargpuff;
    ET_801BCC4C et_801BCC4C;
    ET_ShuttingWindow shuttingWindow;
    ET_CastleDoor castleDoor;
    ET_DeathSkySwirl deathSkySwirl;
    ET_Elevator elevator;
    ET_801D0B40 et_801D0B40;
    ET_801D1BB8 et_801D1BB8;
    ET_801D0B78 et_801D0B78;
    ET_WaterEffects waterEffects;
    ET_GurkhaHammer GH_Props;
    ET_801CE4CC et_801CE4CC;
    ET_801CDFD8 et_801CDFD8;
    ET_TransparentWater transparentWater;
    ET_HeartRoomGoldDoor heartRoomGoldDoor;
    ET_CastleDoorTransition castleDoorTransition;
    ET_AlucardController alucardController;
    ET_ForegroundTree foregroundTree;
    ET_FadeToWhite fadeToWhite;
    ET_DeathStolenItems deathStolenItems;
    ET_Death death;
    ET_SpittleBone spittleBone;
    ET_Player player;
    ET_801CC820 et_801CC820;
    ET_801AF774 et_801AF774;
    ET_Drop drop;
    ET_BigRedFireball bigredfireball;
    ET_SummonSpirit summonspirit;
    ET_3DBackgroundhouse bghouse;
    ET_LifeUpSpawn lifeUpSpawn;
    ET_AxeKnight axeknight;
    ET_801B0AA4 et_801B0AA4;
    ET_Owl owl;
    ET_AlucardWaterEffect aluwater;
    ET_80123B40 et_80123B40;
    ET_80129864 et_80129864;
    ET_801B28E4 et_801B28E4;
    ET_PlayerOutline playerOutline;
    ET_HPNumberMove hpNumMove;
    ET_GuardText guardText;
    ET_Dissolve dissolve;
    ET_LockCamera lockCamera;
    ET_CavernDoor cavernDoor;
    ET_UnkSelEnts unkSelEnts;
    ET_ZombieSpawner zombieSpawner;
    ET_Skeleton skeleton;
    ET_NZ0_311C0 nz0311c0;
} Ext;

#define SYNC_FIELD(struct1, struct2, field_name)                               \
    STATIC_ASSERT(OFF(struct1, field_name) == OFF(struct2, field_name))

SYNC_FIELD(ET_Player, ET_Weapon, anim);
SYNC_FIELD(ET_Player, ET_WeaponUnk006, anim);
SYNC_FIELD(ET_Player, ET_WeaponUnk012, anim);
SYNC_FIELD(ET_Player, ET_WeaponUnk014, anim);
SYNC_FIELD(ET_Player, ET_WeaponUnk030, anim);
SYNC_FIELD(ET_Player, ET_WeaponUnk046, anim);
SYNC_FIELD(ET_Player, ET_WeaponUnk047, anim);
SYNC_FIELD(ET_Player, ET_KarmaCoin, anim);
SYNC_FIELD(ET_Player, ET_Sword, anim);
SYNC_FIELD(ET_Player, ET_HeavenSword, anim);
SYNC_FIELD(ET_Player, ET_HeavenSword2, anim);
SYNC_FIELD(ET_Player, ET_Shield, anim);
SYNC_FIELD(ET_Player, ET_DarkShield, anim);
SYNC_FIELD(ET_Player, ET_MedusaShieldLaser, anim);
SYNC_FIELD(ET_Player, ET_ShamanShieldStar, anim);
SYNC_FIELD(ET_Player, ET_HeraldShieldSwirlEffect, anim);

SYNC_FIELD(ET_EntFactory, ET_Subweapon, parent);
SYNC_FIELD(ET_EntFactory, ET_CrossBoomerang, parent);
SYNC_FIELD(ET_EntFactory, ET_8011E4BC, parent);
SYNC_FIELD(ET_EntFactory, ET_HolyWater, parent);
SYNC_FIELD(ET_EntFactory, ET_GiantSpinningCross, parent);
SYNC_FIELD(ET_EntFactory, ET_CrashCross, parent);
SYNC_FIELD(ET_EntFactory, ET_RicRevivalColumn, parent);
SYNC_FIELD(ET_EntFactory, ET_80161FF0, parent);
SYNC_FIELD(ET_EntFactory, ET_80162870, parent);
SYNC_FIELD(ET_EntFactory, ET_PlayerBlink, parent);
SYNC_FIELD(ET_EntFactory, ET_RichterPowerUpRing, parent);
SYNC_FIELD(ET_EntFactory, ET_HitByIce, parent);
SYNC_FIELD(ET_EntFactory, ET_HitByLightning, parent);
SYNC_FIELD(ET_EntFactory, ET_ReboundStone, parent);
SYNC_FIELD(ET_EntFactory, ET_Agunea, parent);
SYNC_FIELD(ET_EntFactory, ET_801291C4, parent);
SYNC_FIELD(ET_EntFactory, ET_VibhutiCrashCloud, parent);
SYNC_FIELD(ET_EntFactory, ET_ReboundStoneCrashExplosion, parent);
SYNC_FIELD(ET_EntFactory, ET_8016E9E4, parent);
SYNC_FIELD(ET_EntFactory, ET_BibleBeam, parent);
SYNC_FIELD(ET_EntFactory, ET_BibleSubwpn, parent);
SYNC_FIELD(ET_EntFactory, ET_StopWatch, parent);
SYNC_FIELD(ET_EntFactory, ET_stopwatchCircle, parent);
SYNC_FIELD(ET_EntFactory, ET_AguneaCrash, parent);
SYNC_FIELD(ET_EntFactory, ET_8017091C, parent);
SYNC_FIELD(ET_EntFactory, ET_Teleport, parent);

SYNC_FIELD(ET_Subweapon, ET_HolyWater, subweaponId);
SYNC_FIELD(ET_Subweapon, ET_SubwpnAxe, subweaponId);
SYNC_FIELD(ET_Subweapon, ET_AxeCrash, subweaponId);
SYNC_FIELD(ET_Subweapon, ET_CrossBoomerang, subweaponId);
SYNC_FIELD(ET_Subweapon, ET_BibleSubwpn, subweaponId);
SYNC_FIELD(ET_Subweapon, ET_BibleBeam, subweaponId);
SYNC_FIELD(ET_Subweapon, ET_StopWatch, subweaponId);
SYNC_FIELD(ET_Subweapon, ET_ReboundStone, subweaponId);
SYNC_FIELD(ET_Subweapon, ET_ReboundStoneCrashExplosion, subweaponId);
SYNC_FIELD(ET_Subweapon, ET_VibhutiCrashCloud, subweaponId);
SYNC_FIELD(ET_Subweapon, ET_Agunea, subweaponId);
SYNC_FIELD(ET_Subweapon, ET_AguneaCrash, subweaponId);
SYNC_FIELD(ET_Subweapon, ET_GiantSpinningCross, subweaponId);
SYNC_FIELD(ET_Subweapon, ET_CrashCross, subweaponId);
