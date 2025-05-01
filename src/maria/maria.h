// SPDX-License-Identifier: AGPL-3.0-or-later
#include <game.h>
#include <sfx.h>

#define OVL_EXPORT(x) MAR_##x

#define CHECK_GROUND 1
#define CHECK_FALL 4
#define CHECK_FACING 8
#define CHECK_JUMP 0x10
#define CHECK_20 0x20
#define CHECK_CRASH 0x40
#define CHECK_80 0x80
#define CHECK_GRAVITY_HIT 0x200
#define CHECK_400 0x400
#define CHECK_800 0x800
#define CHECK_ATTACK 0x1000
#define CHECK_CROUCH 0x2000
#define CHECK_GRAVITY_FALL 0x8000
#define CHECK_GRAVITY_JUMP 0x10000
#define CHECK_GROUND_AFTER_HIT 0x20000
#define CHECK_SLIDE 0x40000

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
    /* 0x811E */ PAL_UNK_811E,
    /* 0x812E */ PAL_UNK_812E = 0x812E,
    /* 0x812F */ PAL_UNK_812F,
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
    PL_S_SUBWPN_19,
    PL_S_SUBWPN_20,
    PL_S_SUBWPN_21,
    PL_S_22, // unused
    PL_S_SLIDE,
    PL_S_BLADEDASH,
    PL_S_RUN,
    PL_S_26, // unused
    PL_S_SUBWPN_27,
    PL_S_SUBWPN_28,
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
    PL_T_INVINCIBLE_SCENE, // "dying" in the prologue
    PL_T_INVINCIBLE,
    PL_T_AFTERIMAGE_DISABLE,
};

enum MarEntities {
    E_NONE,
    E_FACTORY,
    E_SMOKE_PUFF,             // MarEntitySmokePuff
    E_UNK_3,                  // func_pspeu_092A7B80
    E_UNK_4,                  // func_pspeu_092A6280
    E_HIT_BY_CUT_BLOOD,       // MarEntityHitByCutBlood
    E_UNK_6,                  // func_pspeu_092BF950
    E_UNK_7,                  // func_pspeu_092AAA38
    E_UNK_8,                  // func_pspeu_092AB1C0
    E_80161C2C,               // func_80161C2C
    E_UNK_10,                 // func_pspeu_092B92F0
    E_UNK_11,                 // func_pspeu_092AAC80
    E_DUMMY_12,               // MarEntityDummy
    E_UNK_13,                 // func_pspeu_092A82E0
    E_UNK_14,                 // func_pspeu_092A8AE8
    E_DUMMY_15,               // MarEntityDummy
    E_UNK_16,                 // func_pspeu_092BEB40
    E_UNK_17,                 // func_pspeu_092BFD30
    E_UNK_18,                 // func_pspeu_092BFF78
    E_DUMMY_19,               // MarEntityDummy
    E_DUMMY_20,               // MarEntityDummy
    E_DUMMY_21,               // MarEntityDummy
    E_APPLY_MARIA_POWER_ANIM, // MarEntityApplyMariaPowerAnim
    E_SLIDE_KICK,             // MarEntitySlideKick
    E_BLADE_DASH,             // MarEntityBladeDash
    E_801623E0,               // func_801623E0
    E_80162604,               // func_80162604
    E_DUMMY_27,               // MarEntityDummy
    E_DUMMY_28,               // MarEntityDummy
    E_80160F0C,               // func_80160F0C
    E_UNK_30,                 // func_pspeu_092B91A8
    E_BLINK_WHITE,            // MarEntityPlayerBlinkWhite
    E_DUMMY_32,               // MarEntityDummy
    E_DUMMY_33,               // MarEntityDummy
    E_SHRINKING_POWERUP_RING, // MarEntityShrinkingPowerUpRing
    E_UNK_35,                 // func_pspeu_092A7950
    E_UNK_36,                 // func_pspeu_092A6E50
    E_UNK_37,                 // func_pspeu_092A7560
    E_UNK_38,                 // func_pspeu_092A9288
    E_UNK_39,                 // func_pspeu_092A95A8
    E_HIT_BY_ICE,             // MarEntityHitByIce
    E_HIT_BY_LIGHTNING,       // MarEntityHitByLightning
    E_UNK_42,                 // func_pspeu_092A9E88
    E_DUMMY_43,               // MarEntityDummy
    E_DUMMY_44,               // MarEntityDummy
    E_DUMMY_45,               // MarEntityDummy
    E_DUMMY_46,               // MarEntityDummy
    E_DUMMY_47,               // MarEntityDummy
    E_DUMMY_48,               // MarEntityDummy
    E_DUMMY_49,               // MarEntityDummy
    E_UNK_50,                 // func_pspeu_092A6740
    E_DUMMY_51,               // MarEntityDummy
    E_DUMMY_52,               // MarEntityDummy
    E_DUMMY_53,               // MarEntityDummy
    E_DUMMY_54,               // MarEntityDummy
    E_DUMMY_55,               // MarEntityDummy
    E_DUMMY_56,               // MarEntityDummy
    E_DUMMY_57,               // MarEntityDummy
    E_DUMMY_58,               // MarEntityDummy
    E_DUMMY_59,               // MarEntityDummy
    E_DUMMY_60,               // MarEntityDummy
    E_DUMMY_61,               // MarEntityDummy
    E_DUMMY_62,               // MarEntityDummy
    E_DUMMY_63,               // MarEntityDummy
    E_DUMMY_64,               // MarEntityDummy
    E_DUMMY_65,               // MarEntityDummy
    E_TELEPORT,               // MarEntityTeleport
    E_DUMMY_67,               // MarEntityDummy
};

// all enums with an underscore as prefix are unconfirmed
enum MarBlueprints {
    BP_SKID_SMOKE,
    BP_SMOKE_PUFF,
    _BP_SUBWPN_CROSS,
    _BP_SUBWPN_CROSS_PARTICLES,
    BP_EMBERS,
    _BP_5,
    _BP_SUBWPN_HOLYWATER,
    _BP_HOLYWATER_FIRE,
    _BP_HIT_BY_FIRE,
    _BP_HOLYWATER_FLAMES,
    BP_OWL,
    BP_MULTIPLE_EMBERS,
    _BP_HYDROSTORM,
    _BP_CRASH_CROSS,
    _BP_CRASH_CROSSES_ONLY,
    _BP_NOT_IMPLEMENTED_1,
    // 0x10
    _BP_NOT_IMPLEMENTED_2,
    _BP_ARM_BRANDISH_WHIP,
    _BP_18,
    _BP_AXE,
    _BP_20,
    _BP_NOT_IMPLEMENTED_3,
    _BP_REVIVAL_COLUMN,
    _BP_MARIA_POWERS_APPLIED,
    _BP_SLIDE,
    BP_25,
    BP_BLADE_DASH,
    _BP_BLUE_CIRCLE,
    _BP_BLUE_SPHERE,
    _BP_MARIA,
    _BP_MARIA_POWERS_INVOKED,
    _BP_31,
    // 0x20
    _BP_NOT_IMPLEMENTED_4,
    BP_MAR_BLINK,
    _BP_CRASH_CROSS_PARTICLES,
    _BP_35,
    _BP_36,
    _BP_37,
    _BP_38,
    _BP_39,
    _BP_HOLYWATER_GLASS,
    _BP_CRASH_AXE,
    _BP_42,
    _BP_SUBWPN_DAGGER,
    _BP_CRASH_DAGGER,
    _BP_HIGH_JUMP,
    _BP_HIT_BY_CUT,
    BP_HIT_BY_ICE,
    // 0x30
    BP_HIT_BY_THUNDER,
    _BP_VIBHUTI,
    _BP_REBOUND_STONE,
    _BP_AGUNEA,
    _BP_AGUNEA_HIT_ENEMY,
    BP_DEATH_BY_FIRE,
    _BP_CRASH_VITHUBI,
    _BP_VITHUBI_CRASH_CLOUD,
    _BP_CRASH_REBOUND_STONE,
    _BP_57,
    _BP_CRASH_REBOUND_STONE_EXPLOSION,
    _BP_CRASH_BIBLE,
    _BP_CRASH_BIBLE_BEAM,
    _BP_BIBLE,
    _BP_BIBLE_TRAIL,
    _BP_SUBWPN_STOPWATCH,
    // 0x40
    _BP_STOPWATCH_CIRCLE,
    _BP_CRASH_STOPWATCH,
    _BP_66,
    _BP_CRASH_AGUNEA,
    _BP_CRASH_AGUNEA_THUNDER,
    _BP_CRASH_REBOUND_STONE_PARTICLES,
    _BP_HIT_BY_DARK,
    _BP_HIT_BY_HOLY,
    _BP_AGUNEA_THUNDER,
    _BP_CRASH_STOPWATCH_LIGHTNING,
    _BP_SMOKE_PUFF_2,
    _BP_SKID_SMOKE_2,
    _BP_SKID_SMOKE_3,
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
    PL_W_NONE,
    _PL_W_DAGGER,
    _PL_W_AXE,
    _PL_W_HOLYWATER,
    _PL_W_CROSS,
    _PL_W_BIBLE,
    _PL_W_STOPWATCH,
    _PL_W_REBNDSTONE,
    _PL_W_VIBHUTI,
    _PL_W_AGUNEA,
    _PL_W_10,
    _PL_W_HOLYWATER_FLAMES,
    _PL_W_CRASH_CROSS,
    _PL_W_CRASH_CROSS_BEAM,
    _PL_W_WHIP,
    _PL_W_15,
    _PL_W_HYDROSTORM,
    PL_W_BIBLE_BEAM,
    PL_W_KICK,
    _PL_W_19,
    _PL_W_20,
    _PL_W_21,
    PL_W_HIGHJUMP,
    _PL_W_23,
    _PL_W_CRASH_VIBHUTI,
    _PL_W_CRASH_REBOUND_STONE,
    _PL_W_CRASH_AGUNEA,
    _PL_W_27,
    _PL_W_28,
    _PL_W_CRASH_REBOUND_EXPLOSION,
    _PL_W_30,
    _PL_W_31,
    NUM_WEAPONS,
};

extern s32 mar_8015459C;

extern u16 mar_80154574[];

extern s16 mar_80154568[];
extern ButtonComboState g_MarComboButtons[2];
extern DebugInfo g_MarDebug;
extern s32 mar_80175958[32];
extern s32 mar_801759D8[32];

extern u8 mar_801545B0[];
extern u8 mar_801545C4[];
extern u8 mar_801545D4[];

extern Point16 g_MarSensorsCeiling[];
extern Point16 g_MarSensorsFloor[];
extern Point16 g_MarSensorsWall[];
extern s16 g_MarSensorsCeilingDefault[];
extern s16 g_MarSensorsFloorDefault[];
extern s16 g_MarSensorsWallDefault[];
extern s16 g_MarSensorsCeilingCrouch[];
extern s16 g_MarSensorsWallCrouch[];

extern s16* mar_801530AC[];
extern s16* wpn_owl_spr[];
extern s16* wpn_turtle_spr[];
extern s16* wpn_cat_spr[];
extern s16* wpn_cardinal_spr[];
extern s16* wpn_dragon_spr[];
extern s16* wpn_doll_spr[];

extern AnimationFrame* mar_8015538C[];
extern AnimationFrame mar_anim_stand[];
extern AnimationFrame mar_anim_stand_relax[];
extern AnimationFrame mar_anim_walk[];
extern AnimationFrame mar_anim_crouch[];
extern AnimationFrame mar_anim_crouch_from_stand[];
extern AnimationFrame mar_80155534[];
extern AnimationFrame mar_80155544[];
extern AnimationFrame mar_anim_run[];
extern AnimationFrame mar_anim_high_jump[];
extern AnimationFrame mar_anim_stun[];
extern AnimationFrame mar_801556C4[];
extern AnimationFrame mar_80155750[];
extern AnimationFrame mar_8015591C[];
extern AnimationFrame mar_80155950[];
extern AnimationFrame D_pspeu_092C0630[];
extern AnimationFrame D_pspeu_092C04B8[];
extern AnimationFrame mar_anim_blade_dash[];
extern AnimationFrame D_pspeu_092C04A8[];
extern AnimationFrame D_pspeu_092C0498[];
extern AnimationFrame D_pspeu_092C0528[];
extern AnimationFrame D_pspeu_092C0620[];
extern AnimationFrame D_pspeu_092C05A0[];
extern AnimationFrame D_pspeu_092C0668[];
extern AnimationFrame D_pspeu_092C06A0[];
extern AnimationFrame mar_80155588[];
extern AnimationFrame mar_801555A8[];
extern AnimationFrame mar_801555C8[];
extern AnimationFrame mar_801555E8[];
extern AnimationFrame D_pspeu_092C0878[];
extern AnimationFrame D_pspeu_092C07E8[];
extern AnimationFrame D_pspeu_092C0858[];
extern AnimationFrame mar_801554E0[];
extern FrameProperty mar_80155964[];

void MarStepDead(
    s32 damageEffects, s32 damageKind, s32 prevStep, s32 prevStepS);
Entity* MarCreateEntFactoryFromEntity(Entity* entity, u32 arg1, s32 arg2);
s32 func_pspeu_092BEAB0(s16);
void func_pspeu_092BEA38(Entity* entity, s32 setUnk6C);
