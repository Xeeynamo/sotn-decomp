// SPDX-License-Identifier: AGPL-3.0-or-later
#include <game.h>
#include <sfx.h>
#include <input.h>

#define OVL_EXPORT(x) MAR_##x

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

enum MarSteps {
    PL_S_STAND,
    PL_S_WALK,
    PL_S_CROUCH,
    PL_S_FALL,
    PL_S_JUMP,
    PL_S_5, // unused
    PL_S_6, // unused
    PL_S_7, // unused
    PL_S_HIGHJUMP,
    PL_S_9, // unused
    PL_S_HIT,
    PL_S_11, // unused
    PL_S_BOSS_GRAB,
    PL_S_13, // unused
    PL_S_14, // unused
    PL_S_15, // unused
    PL_S_DEAD,
    PL_S_17, // unused
    PL_S_18,
    PL_S_CARDINAL_CRASH,
    PL_S_CAT_CRASH,
    PL_S_TURTLE_CRASH,
    PL_S_22, // unused
    PL_S_SLIDE,
    PL_S_BLADEDASH,
    PL_S_RUN,
    PL_S_26, // unused
    PL_S_DRAGON_CRASH,
    PL_S_CARDINAL_ATTACK,
    PL_S_29, // unused
    PL_S_30, // unused
    PL_S_31, // unused
    PL_S_INIT,
    PL_S_DEBUG = 0xF0,
};

enum MarTimers {
    PL_T_POISON,
    PL_T_CURSE,
    PL_T_2,
    PL_T_3,
    PL_T_4,
    PL_T_5,
    PL_T_6,
    PL_T_7,
    PL_T_8,
    PL_T_ATTACK,
    PL_T_10,
    PL_T_RUN,
    PL_T_12,
    PL_T_INVINCIBLE_SCENE,
    PL_T_INVINCIBLE,
    PL_T_AFTERIMAGE_DISABLE,
};

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

// all enums with an underscore as prefix are unconfirmed
enum MarBlueprints {
    BP_SKID_SMOKE,
    BP_SMOKE_PUFF,
    BP_DRAGON_ATTACK,
    BP_DOLL_ATTACK,
    BP_EMBERS,
    _BP_5,
    BP_TURTLE_ATTACK,
    BP_DUMMY_7,
    BP_HIT_BY_FIRE,
    _BP_HOLYWATER_FLAMES,
    BP_OWL,
    BP_MULTIPLE_EMBERS,
    BP_TURTLE_CRASH,
    BP_DRAGON_CRASH,
    BP_TURTLE_CRASH_VORTEX,
    BP_DRAGON_CRASH_BODY_PART,
    BP_DUMMY_16,
    BP_DUMMY_17,
    BP_DUMMY_18,
    BP_CAT_ATTACK,
    BP_DUMMY_20,
    BP_DUMMY_21,
    BP_DUMMY_22,
    BP_DUMMY_23,
    BP_SLIDE,
    BP_SLIDE_KICK,
    BP_BLADE_DASH,
    BP_DUMMY_27,
    BP_DUMMY_28,
    BP_DUMMY_29,
    BP_DUMMY_30,
    BP_DUMMY_31,
    BP_DUMMY_32,
    BP_MAR_BLINK,
    BP_DUMMY_34,
    BP_DUMMY_35,
    BP_36,
    BP_37,
    BP_38,
    BP_39,
    BP_CAT_CRASH_ATTACK,
    BP_CAT_CRASH,
    BP_42,
    BP_CARDINAL_ATTACK,
    BP_CARDINAL_CRASH,
    BP_45,
    BP_HIT_BY_CUT,
    BP_HIT_BY_ICE,
    BP_HIT_BY_THUNDER,
    BP_CARDINAL_CRASH_FIREBALL,
    BP_DOLL_ACTIVATE,
    BP_DUMMY_51,
    BP_DUMMY_52,
    BP_DEATH_BY_FIRE,
    BP_DUMMY_54,
    BP_DUMMY_55,
    BP_DUMMY_56,
    BP_DUMMY_57,
    BP_DUMMY_58,
    BP_DUMMY_59,
    BP_DUMMY_60,
    BP_DUMMY_61,
    BP_DUMMY_62,
    BP_DUMMY_63,
    BP_DUMMY_64,
    BP_DUMMY_65,
    BP_DUMMY_66,
    BP_DUMMY_67,
    BP_DUMMY_68,
    BP_DUMMY_69,
    BP_HIT_BY_DARK,
    BP_HIT_BY_HOLY,
    BP_DUMMY_72,
    BP_DUMMY_73,
    BP_SMOKE_PUFF_2,
    BP_SKID_SMOKE_2,
    BP_SKID_SMOKE_3,
    BP_TELEPORT,
    NUM_BLUEPRINTS,
};

// NOTE: B_MAKE from DRA is different than RIC or MARIA!
// Parsing is done in RicEntityFactory
// entityId: what entity to spawn based on the Entity Set
// amount: How many entities to spawn in total
// nPerCycle: how many entities to spawn at once without waiting for tCycle
// isNonCritical: 'true' for particles, 'false' for gameplay related entities
//   false: keep searching for a free entity slot every frame to make the entity
//   true: when there are no entities available then just forgets about it
// incParamsKind: the technique used to set the self->params to the new entity
//   false: it is set from 0 to 'nPerCycle'
//   true: it is set from 0 to 'amount'
// timerCycle: wait frames per cycle until 'amount' of entities are made
// kind: refer to `BlueprintKind` for a list of options
// origin: position where the entity will spawn from
// timerDelay: how many frames to wait before starting to make the first entity
#define B_MAKE(entityId, amount, nPerCycle, isNonCritical, incParamsKind,      \
               timerCycle, kind, origin, timerDelay)                           \
    {(entityId),                                                               \
     (amount),                                                                 \
     ((nPerCycle) & 0x3F) | ((!!(incParamsKind)) << 6) |                       \
         ((!!(isNonCritical)) << 7),                                           \
     (timerCycle),                                                             \
     ((kind) & 7) | (((origin) & 31) << 3),                                    \
     timerDelay}
enum BlueprintKind {
    // cannot collide with any other entity, used for decoration
    B_DECORATION,

    // can collide to stage items, like candles or enemies
    B_WEAPON,

    // same as above, but new entity replaces the previous one
    B_WEAPON_UNIQUE,

    // graphics and particle effects
    B_EFFECTS,

    // Exclusive to the whip entity controller, entity slot 31
    B_WHIP,

    // Exclusive to young Maria during the prologue, entity slot 48
    B_CUTSCENE_MARIA,

    // Used by subweapon crashes that use a lot of particiles that deal damage
    B_WEAPON_CHILDREN,

    B_KIND_7, // unused
    NUM_BLUEPRINT_KIND,
};
enum BlueprintOrigin {
    // Spawned entities have a life-cycle on their own and
    B_ORIGIN_DEFAULT,

    // Entity moves with the camera, remaining static on the screen.
    B_ORIGIN_FOLLOW_CAMERA,

    // Entity remains attached to the player.
    B_ORIGIN_FOLLOW_PLAYER,

    // The player moves when getting hit with a velocity that corresponds to the
    // severity of the attack received, and we want tjhe effect to follow the
    // player when moving during that phase.
    B_ORIGIN_FOLLOW_PLAYER_WHILE_PLAYER_IS_HIT,

    // Entity remains attached to the player, but only with step==PL_S_RUN
    B_ORIGIN_FOLLOW_PLAYER_WHILE_PLAYER_IS_RUNNING,

    B_ORIGIN_5, // unused, same behaviour as B_ORIGIN_FOLLOW_CAMERA
    B_ORIGIN_6, // unused, same behaviour as B_ORIGIN_FOLLOW_CAMERA

    // Useful when the player is about to use a subweapon: once the command is
    // issued, there is a fraction of delay until the subweapon is spawned to
    // allow the attack to be synchronized with the animaiton. If the player is
    // hit during that fraction, the spawning of the subweapon is effectively
    // canceled.
    B_ORIGIN_FOLLOW_PLAYER_WHILE_PLAYER_IS_NOT_HIT,

    // Spawned entites remain attached to their parent.
    B_ORIGIN_FOLLOW_PARENT_ENTITY,

    // A subweapon crash will spawn different particles that should get
    // de-spawned when the attack terminates.
    B_ORIGIN_SUBWEAPON_CRASH_PARTICLE,
};

// all enums with an underscore as prefix are unconfirmed
enum MarSubweapons {
    PL_W_NONE, // also used for DOLL
    PL_W_CARDINAL,
    PL_W_CAT,
    PL_W_TURTLE,
    PL_W_DRAGON,
    PL_W_DUMMY_5,  // left-over from RIC
    PL_W_DUMMY_6,  // left-over from RIC
    PL_W_DUMMY_7,  // left-over from RIC
    PL_W_DUMMY_8,  // left-over from RIC
    PL_W_DUMMY_9,  // left-over from RIC
    PL_W_DUMMY_10, // left-over from RIC
    PL_W_DUMMY_11, // left-over from RIC
    PL_W_DRAGON_CRASH,
    PL_W_DUMMY_13, // left-over from RIC
    PL_W_DUMMY_14, // left-over from RIC
    PL_W_DOLL,
    PL_W_TURTLE_CRASH,
    PL_W_BLADE_DASH,
    PL_W_KICK,
    PL_W_DUMMY_19, // left-over from RIC
    PL_W_CAT_CRASH,
    PL_W_CARDINAL_CRASH,
    PL_W_HIGHJUMP,
    PL_W_DUMMY_23, // left-over from RIC
    PL_W_DUMMY_24, // left-over from RIC
    PL_W_DUMMY_25, // left-over from RIC
    PL_W_DUMMY_26, // left-over from RIC
    PL_W_DUMMY_27, // left-over from RIC
    PL_W_DUMMY_28, // left-over from RIC
    PL_W_DUMMY_29, // left-over from RIC
    PL_W_DUMMY_30, // left-over from RIC
    PL_W_DUMMY_31, // left-over from RIC
    NUM_WEAPONS,
};

extern DebugInfo g_MarDebug;
extern s32 mar_80175958[32];
extern s32 mar_801759D8[32];

extern Point16 g_MarSensorsCeiling[];
extern Point16 g_MarSensorsFloor[];
extern Point16 g_MarSensorsWall[];
extern s16 g_MarSensorsCeilingDefault[];
extern s16 g_MarSensorsFloorDefault[];
extern s16 g_MarSensorsWallDefault[];
extern s16 D_pspeu_092C5198[NUM_HORIZONTAL_SENSORS]; // unknown ceiling sensors
extern s16 D_pspeu_092C51A0[NUM_HORIZONTAL_SENSORS]; // unknown floor sensors
extern s16 D_pspeu_092C51A8[NUM_VERTICAL_SENSORS];   // unknown wall sensors
extern s16 g_MarSensorsCeilingCrouch[];
extern s16 g_MarSensorsWallCrouch[];

extern s16* maria_spr[];
extern s16* wpn_owl_spr[];
extern s16* wpn_turtle_spr[];
extern s16* wpn_cat_spr[];
extern s16* wpn_cardinal_spr[];
extern s16* wpn_dragon_spr[];
extern s16* wpn_doll_spr[];

extern AnimationFrame mar_anim_stand_relax[];
extern AnimationFrame D_pspeu_092C0450[];
extern AnimationFrame D_pspeu_092C0498[];
extern AnimationFrame D_pspeu_092C04A8[];
extern AnimationFrame D_pspeu_092C04B8[];
extern AnimationFrame mar_anim_crouch[];
extern AnimationFrame mar_anim_crouch_from_stand[];
extern AnimationFrame mar_801554E0[];
extern AnimationFrame D_pspeu_092C0528[];
extern AnimationFrame mar_80155534[];
extern AnimationFrame D_pspeu_092C05A0[];
extern AnimationFrame D_pspeu_092C0620[];
extern AnimationFrame D_pspeu_092C0630[];
extern AnimationFrame D_pspeu_092C0668[];
extern AnimationFrame D_pspeu_092C06A0[];
extern AnimationFrame mar_80155750[];
extern AnimationFrame mar_80155588[];
extern AnimationFrame mar_801555C8[];
extern AnimationFrame mar_801555A8[];
extern AnimationFrame mar_anim_high_jump[];
extern AnimationFrame mar_anim_stun[];
extern AnimationFrame D_pspeu_092C0790[];
extern AnimationFrame mar_80155704[];
extern AnimationFrame anim_maria_use_crash[];
extern AnimationFrame mar_80155544[];
extern AnimationFrame D_pspeu_092C0858[];
extern AnimationFrame mar_anim_press_up[];
extern AnimationFrame D_pspeu_092C0878[];
extern AnimationFrame mar_801556C4[];
extern AnimationFrame mar_8015591C[];
extern AnimationFrame mar_80155950[];
extern FrameProperty mar_80155964[];
extern AnimationFrame* mar_8015538C[];

void MarStepDead(
    s32 damageEffects, s32 damageKind, s32 prevStep, s32 prevStepS);
Entity* MarCreateEntFactoryFromEntity(Entity* entity, u32 arg1, s32 arg2);
s32 func_pspeu_092BEAB0(s16);
void SetOpacity(Entity* entity, s32 opacity);
