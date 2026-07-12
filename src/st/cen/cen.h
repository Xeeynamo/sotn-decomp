// SPDX-License-Identifier: AGPL-3.0-or-later
#ifndef CEN_H
#define CEN_H

#define STAGE_IS_CEN

#include <stage.h>

#define OVL_EXPORT(x) CEN_##x

enum Palettes {
    PAL_NONE = 0,
    PAL_BREAKABLE_DEBRIS = 0x159,
};

typedef enum EntityIDs {
    /* 0x00 */ E_NONE,
    /* 0x01 */ E_ID_01,
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
    /* 0x0E */ E_MESSAGE_BOX,
    /* 0x0F */ E_DUMMY_0F,
    /* 0x10 */ E_DUMMY_10,
    /* 0x11 */ E_BACKGROUND_BLOCK,
    /* 0x12 */ E_ID_12,
    /* 0x13 */ E_ID_13,
    /* 0x14 */ E_EXPLOSION_VARIANTS,
    /* 0x15 */ E_GREY_PUFF,
    /* 0x16 */ E_CUTSCENE,
    /* 0x17 */ E_PLATFORM,
    /* 0x18 */ E_BOSS_MARIA,
    /* 0x19 */ E_ROOM_DARKNESS,
    /* 0x1A */ E_ELEVATOR_STATIONARY_UNUSED,
    /* 0x1B */ E_ELEVATOR_STATIONARY,
    /* 0x1C */ E_MOVING_ELEVATOR,
    /* 0x80 */ E_BREAKABLE_DEBRIS = 0x80,
} EntityIDs;

enum MarEntities {
    MAR_NONE,
    E_FACTORY,
    E_SMOKE_PUFF,              // MarEntitySmokePuff
    E_DRAGON_ATTACK,           // EntityMariaDragonAttack
    E_DOLL_ATTACK,             // EntityMariaDollAttack
    E_HIT_BY_CUT_BLOOD,        // MarEntityHitByCutBlood
    E_CRASH_SUMMON,            // EntityMariaCrashSummon
    E_TURTLE_ATTACK,           // EntityMariaTurtleAttack
    E_TURTLE_CRASH_VORTEX,     // EntityMariaTurtleCrashVortex
    E_80161C2C,                // func_maria_80161C2C
    E_OWL,                     // EntityMariaOwl
    E_TURTLE_CRASH,            // EntityMariaTurtleCrash
    E_DUMMY_12,                // MarEntityDummy
    E_DRAGON_CRASH,            // EntityMariaDragonCrash
    E_DRAGON_CRASH_BODY_PART,  // EntityMariaDragonCrashBodyPart
    E_DUMMY_15,                // MarEntityDummy
    E_UNK_16,                  // func_pspeu_092BEB40
    E_UNK_17,                  // func_pspeu_092BFD30
    E_UNK_18,                  // func_pspeu_092BFF78
    E_DUMMY_19,                // MarEntityDummy
    E_DUMMY_20,                // MarEntityDummy
    E_DUMMY_21,                // MarEntityDummy
    E_APPLY_MARIA_POWER_ANIM,  // MarEntityApplyMariaPowerAnim
    E_SLIDE_KICK,              // MarEntitySlideKick
    E_BLADE_DASH,              // MarEntityBladeDash
    E_801623E0,                // func_maria_801623E0
    E_80162604,                // func_maria_80162604
    E_DUMMY_27,                // MarEntityDummy
    E_DUMMY_28,                // MarEntityDummy
    E_80160F0C,                // func_maria_80160F0C
    E_NOT_IMPLEMENTED_4,       // MarEntityNotImplemented4
    E_BLINK_WHITE,             // MarEntityPlayerBlinkWhite
    E_DUMMY_32,                // MarEntityDummy
    E_DUMMY_33,                // MarEntityDummy
    E_SHRINKING_POWERUP_RING,  // MarEntityShrinkingPowerUpRing
    E_CAT_CRASH_ATTACK,        // EntityMariaCatCrashAttack
    E_CAT_ATTACK,              // EntityMariaCatAttack
    E_CAT_CRASH,               // EntityMariaCatCrash
    E_CARDINAL_ATTACK,         // EntityMariaCardinalAttack
    E_CARDINAL_CRASH,          // EntityMariaCardinalCrash
    E_HIT_BY_ICE,              // MarEntityHitByIce
    E_HIT_BY_LIGHTNING,        // MarEntityHitByLightning
    E_CARDINAL_CRASH_FIREBALL, // EntityMariaCardinalCrashFireball
    E_DUMMY_43,                // MarEntityDummy
    E_DUMMY_44,                // MarEntityDummy
    E_DUMMY_45,                // MarEntityDummy
    E_DUMMY_46,                // MarEntityDummy
    E_DUMMY_47,                // MarEntityDummy
    E_DUMMY_48,                // MarEntityDummy
    E_DUMMY_49,                // MarEntityDummy
    E_DOLL_ACTIVATE,           // EntityMariaDollActivate
    E_DUMMY_51,                // MarEntityDummy
    E_DUMMY_52,                // MarEntityDummy
    E_DUMMY_53,                // MarEntityDummy
    E_DUMMY_54,                // MarEntityDummy
    E_DUMMY_55,                // MarEntityDummy
    E_DUMMY_56,                // MarEntityDummy
    E_DUMMY_57,                // MarEntityDummy
    E_DUMMY_58,                // MarEntityDummy
    E_DUMMY_59,                // MarEntityDummy
    E_DUMMY_60,                // MarEntityDummy
    E_DUMMY_61,                // MarEntityDummy
    E_DUMMY_62,                // MarEntityDummy
    E_DUMMY_63,                // MarEntityDummy
    E_DUMMY_64,                // MarEntityDummy
    E_DUMMY_65,                // MarEntityDummy
    E_TELEPORT,                // MarEntityTeleport
    E_DUMMY_67,                // MarEntityDummy
    NUM_ENTITIES,
};

void EntityExplosionVariants(Entity* entity);
void EntityGreyPuff(Entity* entity);

/*** Initializers ***/
extern EInit OVL_EXPORT(EInitBreakable);
extern EInit OVL_EXPORT(EInitObtainable);
extern GAME_IMPORT EInit g_EInitSpawner;
extern EInit g_EInitInteractable;
extern EInit g_EInitCommon;
extern EInit g_EInitParticle;
extern EInit g_EInitLockCamera;

extern u16* D_80180574[];
extern u8 D_80180594[];
extern u8 D_8018059C[];
extern u16 D_801805A4[];
extern u8 D_801805B4[];
extern s16 D_801805BC[];
extern u16 D_80180EEC[];
extern u16 D_80180F1C[];
extern ObjInit D_8018125C[];

#include "../../maria/maria_common.h"

#ifdef VERSION_PSP
enum MarPalette {
    /* 0x812E */ PAL_UNK_812E = 0x812E,
    /* 0x812F */ PAL_UNK_812F,
    /* 0x8130 */ PAL_MARIA = 0x8130,
    /* 0x8131 */ PAL_WPN_OWL,
    /* 0x8132 */ PAL_WPN_TURTLE,
    /* 0x8133 */ PAL_WPN_TURTLE_CRASH,
    /* 0x8134 */ PAL_WPN_CAT,
    /* 0x8135 */ PAL_WPN_CAT_CRASH,
    /* 0x8136 */ PAL_WPN_CARDINAL,
    /* 0x8137 */ PAL_WPN_DRAGON,
    /* 0x8138 */ PAL_WPN_DRAGON_CRASH,
    /* 0x8139 */ PAL_WPN_DOLL,
    /* 0x813A */ PAL_CRASH,
};

enum MarAnimset {
    ANIMSET_EN_MARIA = ANIMSET_OVL(1),
    ANIMSET_PL_MARIA = ANIMSET_OVL(3),
    ANIMSET_WPN_OWL = ANIMSET_OVL(4),
    ANIMSET_WPN_TURTLE = ANIMSET_OVL(5),
    ANIMSET_WPN_CAT = ANIMSET_OVL(6),
    ANIMSET_WPN_CARDINAL = ANIMSET_OVL(7),
    ANIMSET_WPN_DRAGON = ANIMSET_OVL(8),
    ANIMSET_WPN_DOLL = ANIMSET_OVL(9),
};

#define MAR_SFX_OFFSET 21
#define MARIA g_Entities[STAGE_ENTITY_START]
#define MARIA_AFTERIMAGE_1 g_Entities[STAGE_ENTITY_START + E_AFTERIMAGE_1]
#define MARIA_AFTERIMAGE_2 g_Entities[STAGE_ENTITY_START + E_AFTERIMAGE_2]
#define MARIA_AFTERIMAGE_3 g_Entities[STAGE_ENTITY_START + E_AFTERIMAGE_3]
extern PlayerState g_Maria;
#endif

#endif
