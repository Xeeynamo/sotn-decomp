// SPDX-License-Identifier: AGPL-3.0-or-later
#include <game.h>
#include <sfx.h>

#define OVL_EXPORT(x) MAR_##x

enum MarEntities {
    E_NONE,
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

enum MarPalette {
    /* 0x8114 */ PAL_MARIA = 0x8114,
    /* 0x8115 */ PAL_WPN_OWL,
    /* 0x8116 */ PAL_WPN_TURTLE,
    /* 0x8117 */ PAL_WPN_TURTLE_CRASH,
    /* 0x8118 */ PAL_WPN_CAT,
    /* 0x8119 */ PAL_WPN_CAT_CRASH,
    /* 0x811A */ PAL_WPN_CARDINAL,
    /* 0x811B */ PAL_WPN_DRAGON,
    /* 0x811C */ PAL_WPN_DRAGON_CRASH,
    /* 0x811D */ PAL_WPN_DOLL,
    /* 0x811E */ PAL_CRASH,
    /* 0x812E */ PAL_UNK_812E = 0x812E,
    /* 0x812F */ PAL_UNK_812F,
};

enum MarAnimset {
    ANIMSET_PL_MARIA = ANIMSET_OVL(16),
    ANIMSET_WPN_OWL = ANIMSET_OVL(17),
    ANIMSET_WPN_TURTLE = ANIMSET_OVL(18),
    ANIMSET_WPN_CAT = ANIMSET_OVL(19),
    ANIMSET_WPN_CARDINAL = ANIMSET_OVL(20),
    ANIMSET_WPN_DRAGON = ANIMSET_OVL(21),
    ANIMSET_WPN_DOLL = ANIMSET_OVL(22),
};

#include "maria_common.h"
