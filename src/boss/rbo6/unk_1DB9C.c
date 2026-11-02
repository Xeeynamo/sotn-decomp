// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../rbo6/rbo6.h"
#include "scratchpad.h"

#ifdef VERSION_PSP
extern s32 E_ID(DRACULA_SMALL_HAND);
extern s32 E_ID(DRACULA_DECOR);
extern s32 E_ID(DRACULA_ARM);
extern s32 E_ID(DRACULA_HAND);
extern s32 E_ID(DRACULA_PUPPET_HEAD);
extern s32 E_ID(DRACULA_VERTEBRA);
extern s32 E_ID(DRACULA_WINGS);
extern s32 E_ID(SUMMONING_LIGHTNING);
extern s32 E_ID(BOSS_PORTAL);
extern s32 E_ID(SUMMONED_BOSS);
extern s32 E_ID(SQUISH_BLOOD_BALLS);
extern s32 E_ID(BLUE_FLASH_ORB);
extern s32 E_ID(RAINBOW_TRIANGLE);
extern s32 E_ID(TRIANGLE_CORNER_GLOW);
extern s32 E_ID(BLUE_ORB_SHADOW);
extern s32 E_ID(UNK_27);
#endif

// BSS vars
s32 g_BossFlag = 0;
s32 draculaIsInBackground = 0;
typedef enum {
    SUMMON_INACTIVE = 0,
    SUMMON_START,
    SUMMON_ARRIVED,
    SUMMON_SQUISH_START,
    SUMMON_SQUISHING,
    SUMMON_CLEANUP = 5,
} SummonAtkState;
s32 summonAttackState = 0;
s32 bossSummonCycler = 0;
// Used as a bool. When it hits 1, the orb fires at the player.
s32 orbAttackLaunch = 0;
// Indicates if attacking with left hand (1), right hand (2), or done (3)
s32 handAttackMode = 0;
// Identifies which head should attack when we do the three-head attack
s32 headAttackCycler = 0;
typedef enum {
    TRI_INACTIVE = 0,
    TRI_CLEANUP = 5,
} TriAtkState;
s32 triangleAttackState = TRI_INACTIVE;
s32 currentDraculaPalette = 0;

static AnimateEntityFrame anim_idle_flap[] = {{32, 1}, {32, 2}, POSE_LOOP(0)};
static AnimateEntityFrame anim_shoot_orb[] = {
    {64, 1}, {8, 4}, {72, 3}, {2, 1}, {48, 4}, POSE_END};
static AnimateEntityFrame anim_blue_flashing_orb[] = {
    {1, 5}, {1, 6}, {1, 7}, POSE_LOOP(0)};
static AnimateEntityFrame anim_blue_orb_shadow[] = {
    {1, 6}, {1, 7}, POSE_LOOP(0)};
static AnimateEntityFrame anim_hand_flex[] = {{30, 8}, {30, 9}, POSE_LOOP(0)};
static AnimateEntityFrame anim_hand_grab[] = {
    {4, 8}, {4, 9}, {4, 8}, {4, 10}, {32, 11}, {12, 10}, POSE_END};
static AnimateEntityFrame anim_hand_release[] = {
    {8, 10}, {8, 8}, {8, 9}, POSE_END};
static AnimateEntityFrame anim_arm_swoop[] = {
    {4, 12}, {4, 13}, {4, 14}, {4, 15}, {48, 16}, POSE_END};
static AnimateEntityFrame anim_arm_swoop_slow[] = {
    {32, 12}, {2, 13}, {2, 14}, {2, 15}, {64, 16}, POSE_END};
static AnimateEntityFrame anim_arm_swoop_slower[] = {
    {32, 12}, {8, 13}, {8, 14}, {8, 15}, {32, 16}, POSE_END};
static AnimateEntityFrame anim_arm_unswoop[] = {
    {4, 16}, {8, 15}, {8, 14}, {8, 13}, {15, 12}, {1, 12}, POSE_END};
static AnimateEntityFrame anim_head_jitter[] = {{1, 18}, {1, 19}, POSE_LOOP(0)};
static AnimateEntityFrame anim_head_open_mouth[] = {
    {2, 19}, {2, 20}, {2, 21}, {64, 22}, POSE_END};
static AnimateEntityFrame anim_head_close_mouth[] = {
    {2, 22}, {4, 21}, {4, 20}, {2, 19}, POSE_END};
static AnimateEntityFrame anim_mainbody_engorge[] = {
    {30, 23}, {30, 24}, POSE_LOOP(0)};
static AnimateEntityFrame anim_hand_gesture[] = {
    {128, 25}, {8, 26}, {128, 27}, {8, 26}, POSE_LOOP(0)};
// The decorative add-ons on Dracula. Skull on far left, naked figure upper
// left, etc
static AnimateEntityFrame anim_skull_myah[] = {
    {48, 28}, {30, 29}, POSE_LOOP(0)};
static AnimateEntityFrame anim_naked_shift[] = {
    {32, 30}, {32, 31}, POSE_LOOP(0)};
static AnimateEntityFrame anim_scragglehand_shift[] = {
    {32, 32}, {32, 33}, POSE_LOOP(0)};
static AnimateEntityFrame anim_fishhead_shift[] = {
    {48, 34}, {16, 35}, POSE_LOOP(0)};
static AnimateEntityFrame anim_danglebat_shift[] = {
    {48, 36}, {8, 37}, {24, 38}, {8, 37}, POSE_LOOP(0)};

static AnimateEntityFrame anim_red_ball_squish[] = {
    {6, 39}, {6, 40}, {6, 39}, {6, 41}, POSE_LOOP(0)};
static AnimateEntityFrame anim_small_blue_ball_pulse[] = {
    {1, 43}, {1, 44}, POSE_LOOP(0)};
static AnimateEntityFrame* decorEntAnims[] = {
    anim_skull_myah, anim_naked_shift, anim_scragglehand_shift,
    anim_fishhead_shift, anim_danglebat_shift};
static Point16 handOffsets[] = {
    {-32, -16}, {-16, 16}, {0, 16}, {32, 8}, {48, -16},
};
static Point16 headLocations[] = {
    {-24, -16},
    {-16, 16},
    {24, -16},
};
static s16 headTriangleAngles[] = {
    ROT(-135),
    ROT(61.875),
    ROT(-39.375),
};
typedef enum {
    DRAC_INIT,
    DRAC_START_FIGHT,
    DRAC_COME_FROM_BACK,
    DRAC_DROP_IN,
    DRAC_NORMAL,
    DRAC_SUMMON_BOSS,
    DRAC_AFTER_BOSS_SQUISH,
    DRAC_FLY_TO_BACKGROUND,
    DRAC_BLUE_ORB_ATTACK,
    DRAC_HAND_ATTACK,
    DRAC_HEADS_ATTACK,
    DRAC_TRIANGLE_ATTACK,
    DRAC_DEAD,
    DRAC_DEBUG = 255
} BossDraculaSteps;

// This is a strict cycle of one to the next. He always does these attacks in
// this exact order. Note: The summon attack is followed by the blue orb but is
// not mentioned in this cycle.
static u16 attackCycle[] = {DRAC_HAND_ATTACK, DRAC_SUMMON_BOSS,
                            DRAC_HEADS_ATTACK, DRAC_TRIANGLE_ATTACK};
static s8 handHitboxes[][4] = {
    {0, 0, 0, 0},     {-64, -84, 0, 0}, {0, 0, 16, 16},   {-18, 0, 12, 24},
    {-10, 0, 12, 24}, {-72, 112, 0, 0}, {-12, -17, 0, 0},
};
static u8 handHitboxIndices[] = {0, 1, 1, 1, 1, 2, 2, 2, 3, 3, 3, 4, 5, 5};

// Extern BSS var
extern s32 g_CutsceneFlags;

extern EInit g_EInitDraculaLvl98;

// Lots of entities are part of Dracula. Here is a catalog of what entities
// are in which slots in g_Entities:
// 80: Dracula himself. Created by the normal e_layout system.
// 81: Dracula decor, params 0, skull on far left
// 82: Dracula decor, params 1, naked figure in upper left
// 83: Dracula decor, params 2, scraggly hand in upper right
// 84: Dracula decor, params 3, fish head on far right
// 85: Dracula decor, params 4, bat hanging under right side
// 86: Dracula arm, params 0
// 87: Dracula hand (created by arm), params 0
// 88: Dracula arm, params 1
// 89: Dracula hand (created by arm), params 1
// 90: The hand of the small humanoid dracula in center, gestures on occasion
// 91: The first of the 3 "puppet heads" which float around the middle
// 92-96: The 5 vertebrae connecting up to the first head
// 97: The second puppet head
// 98-102: 5 vertebrae for the second head
// 103: The third and final puppet head
// 104-108: The last 5 vertebrae
// 109: The wings. Note: one single entity (not one entity for each wing)
// That covers all the "persistent" entities attached to Dracula. Others that
// come and go include:
// 129: The portal between Dracula's hands that summons in bosses to squish
// 130: The boss that comes in from that portal
// 132: The blue flashing orb attack, when Dracula is in background. Grows.

void EntityBossDracula(Entity* self) {
    s32 distFromCenter;
    Entity* other;
    s16 angle;
    s32 xVar;
    s32 yVar;
    s32 i;

    if (self->hitFlags & 3) {
        if ((Random() & 7) == 0) {
            if (Random() & 1) {
                g_api.PlaySfx(SFX_DRACULA_PAIN_A);
            } else {
                g_api.PlaySfx(SFX_DRACULA_PAIN_B);
            }
        }
    }
    if ((self->flags & FLAG_DEAD) && (self->step != DRAC_DEAD)) {
        SetStep(DRAC_DEAD);
    }
    switch (self->step) {
    case DRAC_INIT:
        InitializeEntity(g_EInitDraculaLvl98);
        self->zPriority = 0x80;
        self->hitboxOffY = -4;
        other = &g_Entities[81];
        for (i = 0; i < 5; i++, other++) {
            CreateEntityFromCurrentEntity(E_ID(DRACULA_DECOR), other);
            other->zPriority = self->zPriority + 1;
            other->params = i;
        }
        other = &g_Entities[86];
        CreateEntityFromCurrentEntity(E_ID(DRACULA_ARM), other);
        other->params = 0;
        other->zPriority = self->zPriority + 3;
        other += 2;
        CreateEntityFromCurrentEntity(E_ID(DRACULA_ARM), other);
        other->params = 1;
        other->zPriority = self->zPriority + 3;
        other = &g_Entities[86];
        self->nextPart = other + 1;
        self->parent = NULL;
        other = &g_Entities[90];
        CreateEntityFromCurrentEntity(E_ID(DRACULA_SMALL_HAND), other);
        other->zPriority = self->zPriority + 1;
        other = &g_Entities[91];
        for (i = 0; i < 3; i++, other += 6) {
            CreateEntityFromCurrentEntity(E_ID(DRACULA_PUPPET_HEAD), other);
            other->params = i;
            other->zPriority = self->zPriority + 6;
        }
        other = &g_Entities[109];
        CreateEntityFromCurrentEntity(E_ID(DRACULA_WINGS), other);
        other->zPriority = self->zPriority;
        SetStep(DRAC_START_FIGHT);
        /* fallthrough */
    case DRAC_START_FIGHT:
        self->hitboxState = 0;
        draculaIsInBackground = 1;
        switch (self->step_s) {
        case 0:
            self->animCurFrame = 1;
            self->drawFlags = ENTITY_OPACITY;
            self->opacity = 0;
            if (g_CutsceneFlags & 0x20) {
                self->ext.finalDrac.timer = 0x80;
                self->step_s++;
            }
            break;
        case 1:
            AnimateEntity(anim_idle_flap, self);
            if (!--self->ext.finalDrac.timer) {
                self->step_s++;
            }
            break;
        case 2:
            AnimateEntity(anim_idle_flap, self);
            self->opacity++;
            if (self->opacity >= 0x80) {
                self->drawFlags = ENTITY_DEFAULT;
                self->step_s++;
            }
            break;
        case 3:
            AnimateEntity(anim_idle_flap, self);
            if (g_CutsceneFlags & 2) {
                g_api.TimeAttackController(
                    TIMEATTACK_EVENT_UNUSED_28, TIMEATTACK_SET_VISITED);
                g_api.PlaySfx(SFX_DRACULA_BEHOLD_MY_TRUE_FORM);
                SetStep(DRAC_COME_FROM_BACK);
            }
            break;
        }
        break;
    case DRAC_DEAD:
        switch (self->step_s) {
        case 0:
            g_api.TimeAttackController(
                TIMEATTACK_EVENT_UNUSED_28, TIMEATTACK_SET_RECORD);
            g_BossFlag |= 1;
            self->hitboxState = 0;
            self->palette = PAL_DRACULA;
            self->flags &= ~0xF;
            self->step_s++;
            break;
        case 1:
            other = &g_Entities[200];
            CreateEntityFromCurrentEntity(E_ID(UNK_27), other);
            other->flags |= FLAG_UNK_10000;
            other->params = 1;
            g_unkGraphicsStruct.unk28 = 0xFF;
            self->step_s++;
            break;
        case 2:
            // Distance from center
            xVar = 128 - self->posX.i.hi;
            yVar = 138 - self->posY.i.hi;
            angle = ratan2(yVar, xVar);
            // Set velocity to push us back toward the center
            // Note: this angle stuff is a bit excessive, they could
            // have just had velocities as function of distances.
            self->velocityX = (rcos(angle) << 0xF) >> 0xC;
            self->velocityY = (rsin(angle) << 0xF) >> 0xC;
            MoveEntity();
            distFromCenter = SquareRoot0((xVar * xVar) + (yVar * yVar));
            if (distFromCenter < 3) {
                self->step_s++;
            }
            break;
        case 3:
            g_BossFlag |= 2;
            self->velocityX = 0;
            self->velocityY = 0;
            self->step_s++;
            break;
        case 4:
            // Test g_timer, but don't actually do anything. But PSP
            // needs something in the body, so I use "self".
            if (!(g_Timer & 0xF)) {
                self;
            }
            break;
        }
        break;
    case DRAC_COME_FROM_BACK:
        AnimateEntity(anim_idle_flap, self);
        draculaIsInBackground = 1;
        self->hitboxState = 0;
        switch (self->step_s) {
        case 0:
            // Drop downward fast
            self->velocityY = FIX(6.0);
            self->step_s++;
            /* fallthrough */
        case 1:
            MoveEntity();
            // After dropping down, fly off top of screen
            self->velocityY -= FIX(0.25);
            if (self->posY.i.hi < -0x60) {
                SetStep(DRAC_DROP_IN);
            }
            break;
        }
        break;
    case DRAC_DROP_IN:
        AnimateEntity(anim_mainbody_engorge, self);
        draculaIsInBackground = 0;
        self->hitboxState = 2;
        switch (self->step_s) {
        case 0:
            self->velocityX = 0;
            self->velocityY = FIX(1.25);
            self->posY.i.hi = -0x50;
            self->posX.i.hi = 0x80;
            self->zPriority = 0x80;
            self->ext.finalDrac.timer = 0;
            self->step_s++;
            /* fallthrough */
        case 1:
            if (!(self->ext.finalDrac.timer & 0x3F)) {
                g_api.PlaySfx(SFX_DRACULA_FLY_IN);
            }
            self->ext.finalDrac.timer++;
            MoveEntity();
            if (self->posY.i.hi > 0x90) {
                SetStep(DRAC_NORMAL);
            }
            break;
        }
        break;
    case DRAC_NORMAL:
        if (!self->step_s) {
            self->ext.finalDrac.timer = 0x40;
            self->step_s++;
        }
        AnimateEntity(anim_mainbody_engorge, self);
        draculaIsInBackground = 0;
        self->hitboxState = 2;
        MoveEntity();
        angle = self->ext.finalDrac.hoverPhase += 0x20;
        self->velocityY = (rcos(angle) << 0xF) >> 0xC;
        if (!--self->ext.finalDrac.timer) {
            SetStep(attackCycle[self->ext.finalDrac.nextAttack]);
            self->ext.finalDrac.nextAttack++;
            self->ext.finalDrac.nextAttack &= 3;
        }
        break;
    case DRAC_SUMMON_BOSS:
        AnimateEntity(anim_mainbody_engorge, self);
        draculaIsInBackground = 0;
        self->hitboxState = 2;
        MoveEntity();
        angle = self->ext.finalDrac.hoverPhase += 0x20;
        self->velocityY = (rcos(angle) << 0xF) >> 0xC;
        switch (self->step_s) {
        case 0:
            summonAttackState = SUMMON_START;
            other = &g_Entities[129];
            CreateEntityFromCurrentEntity(E_ID(BOSS_PORTAL), other);
            other->zPriority = self->zPriority + 3;
            self->step_s++;
            /* fallthrough */
        case 1:
            if (summonAttackState == SUMMON_ARRIVED) {
                self->step_s++;
            }
            break;
        case 2:
            summonAttackState = SUMMON_SQUISH_START;
            g_api.PlaySfx(SFX_DRACULA_SQUISH_GRUNT);
            self->step_s++;
            /* fallthrough */
        case 3:
            if (summonAttackState == SUMMON_CLEANUP) {
                self->ext.finalDrac.timer = 0xA0;
                self->step_s++;
            }
            break;
        case 4:
            if (!--self->ext.finalDrac.timer) {
                bossSummonCycler++;
                if (bossSummonCycler > 7) {
                    bossSummonCycler = 0;
                }
                summonAttackState = SUMMON_INACTIVE;
                SetStep(DRAC_AFTER_BOSS_SQUISH);
            }
            break;
        }
        break;
    case DRAC_AFTER_BOSS_SQUISH:
        if (!self->step_s) {
            self->velocityX = 0;
            self->velocityY = FIX(1.0);
            g_api.PlaySfx(SFX_DRACULA_LAUGH_A);
            self->step_s++;
        }
        AnimateEntity(anim_mainbody_engorge, self);
        draculaIsInBackground = 0;
        self->hitboxState = 2;
        MoveEntity();
        self->velocityY -= FIX(0.0625);
        if (self->posY.i.hi < -0x40) {
            SetStep(DRAC_FLY_TO_BACKGROUND);
        }
        break;
    case DRAC_FLY_TO_BACKGROUND:
        if (!self->step_s) {
            self->posX.i.hi = 0x80;
            self->posY.i.hi = -0x40;
            self->velocityX = 0;
            self->velocityY = FIX(3.0);
            self->zPriority = 0x80;
            self->step_s++;
        }
        AnimateEntity(anim_idle_flap, self);
        draculaIsInBackground = 1;
        self->hitboxState = 0;
        MoveEntity();
        self->velocityY -= self->velocityY >> 6;
        if (self->posY.i.hi > 0x70) {
            SetStep(DRAC_BLUE_ORB_ATTACK);
        }
        break;
    case DRAC_BLUE_ORB_ATTACK:
        if (!self->step_s) {
            orbAttackLaunch = 0;
            self->step_s++;
        }
        draculaIsInBackground = 1;
        self->hitboxState = 0;
        if (!AnimateEntity(anim_shoot_orb, self)) {
            SetStep(DRAC_COME_FROM_BACK);
        }
        if ((!self->poseTimer) && (self->pose == 2)) {
            other = &g_Entities[132];
            CreateEntityFromEntity(E_ID(BLUE_FLASH_ORB), self, other);
            other->zPriority = self->zPriority + 1;
        }
        if ((!self->poseTimer) && (self->pose == 3)) {
            g_api.PlaySfx(SFX_DRACULA_MONSTER_MAGIC_ATTACK);
            orbAttackLaunch = 1;
        }
        break;
    case DRAC_HAND_ATTACK:
        AnimateEntity(anim_mainbody_engorge, self);
        draculaIsInBackground = 0;
        self->hitboxState = 2;
        MoveEntity();
        angle = self->ext.finalDrac.hoverPhase += 0x20;
        self->velocityY = (rcos(angle) << 0xF) >> 0xC;
        switch (self->step_s) {
        case 0:
            self->ext.finalDrac.handSwipesRemain = 4;
            self->step_s++;
            /* fallthrough */
        case 1:
            other = &PLAYER;
            if (other->posX.i.hi < 0x80) {
                handAttackMode = 1;
                self->velocityX = FIX(-0.5);
            } else {
                handAttackMode = 2;
                self->velocityX = FIX(0.5);
            }
            self->ext.finalDrac.timer = 0x28;
            self->step_s++;
            /* fallthrough */
        case 2:
            self->velocityX -= self->velocityX >> 4;
            if (!--self->ext.finalDrac.timer) {
                if (handAttackMode == 1) {
                    self->velocityX = FIX(2.0);
                } else {
                    self->velocityX = FIX(-2.0);
                }
                self->step_s++;
            }
            break;
        case 3:
            self->velocityX -= self->velocityX >> 4;
            if (handAttackMode == 3) {
                self->step_s++;
            }
            break;
        case 4:
            xVar = 0x80 - self->posX.i.hi;
            if (xVar > 0) {
                self->velocityX = FIX(1.125);
            }
            if (xVar < 0) {
                self->velocityX = FIX(-1.125);
            }
            if (abs(xVar) < 3) {
                self->velocityX = 0;
                if (!--self->ext.finalDrac.handSwipesRemain) {
                    handAttackMode = 0;
                    SetStep(DRAC_NORMAL);
                } else {
                    self->step_s = 1;
                }
            }
            break;
        }
        break;
    // Each of the 3 heads attacks in sequence
    // This is done by setting headAttackCycler to 1.
    // Each head is listening for headAttackCycler all the time.
    // Heads have params 0-2 so it says "if cycler is me + 1, i go"
    // When each head is finished, it increments the cycler. This signals
    // the next head to launch.
    // Once we have seen the cycler hit 4, we go back to DRAC_NORMAL.
    case DRAC_HEADS_ATTACK:
        AnimateEntity(anim_mainbody_engorge, self);
        draculaIsInBackground = 0;
        self->hitboxState = 2;
        MoveEntity();
        angle = self->ext.finalDrac.hoverPhase += 0x20;
        self->velocityY = (rcos(angle) << 0xF) >> 0xC;
        switch (self->step_s) {
        case 0:
            headAttackCycler = 1;
            self->step_s++;
            /* fallthrough */
        case 1:
            if (headAttackCycler == 4) {
                headAttackCycler = 0;
                SetStep(DRAC_NORMAL);
            }
            break;
        }
        break;
    case DRAC_TRIANGLE_ATTACK:
        AnimateEntity(anim_mainbody_engorge, self);
        draculaIsInBackground = 0;
        self->hitboxState = 2;
        switch (self->step_s) {
        case 0:
            triangleAttackState = 1;
            self->step_s++;
            /* fallthrough */
        case 1:
            if (triangleAttackState == 4) {
                self->ext.finalDrac.timer = 0x40;
                self->step_s++;
            }
            break;
        case 2:
            if (!(self->ext.finalDrac.timer & 0xF)) {
                other = AllocEntity(&g_Entities[160], &g_Entities[192]);
                if (other != NULL) {
                    CreateEntityFromCurrentEntity(
                        E_ID(RAINBOW_TRIANGLE), other);
                    other->zPriority = self->zPriority + 8;
                }
            }
            if (!--self->ext.finalDrac.timer) {
                self->ext.finalDrac.timer = 0x40;
                self->step_s++;
            }
            break;
        case 3:
            if (!--self->ext.finalDrac.timer) {
                triangleAttackState = TRI_CLEANUP;
                self->step_s++;
            }
            break;
        case 4:
            triangleAttackState = 0;
            SetStep(DRAC_NORMAL);
            break;
        }
        break;
    case DRAC_DEBUG:
#include "../../st/pad2_anim_debug.h"
    }
    currentDraculaPalette = self->palette;
}

extern EInit g_EInitDraculaMisc;

void EntityDraculaArm(Entity* self) {
    Entity* other;
    other = &g_Entities[80];
    self->posX.i.hi = other->posX.i.hi;
    self->posY.i.hi = other->posY.i.hi;
    if (!self->params) {
        self->posX.i.hi -= 0x34;
        self->posY.i.hi += 0x10;
    } else {
        self->posX.i.hi += 0x3B;
        self->posY.i.hi += 0x18;
    }
    self->palette = currentDraculaPalette;
    if ((g_BossFlag & 1) && (self->step != 16)) {
        SetStep(16);
    }
    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitDraculaMisc);
        self->facingLeft = self->params;
        other = self + 1;
        CreateEntityFromCurrentEntity(E_ID(DRACULA_HAND), other);
        other->params = self->params;
        other->zPriority = self->zPriority + 1;
        /* fallthrough */
    case 1:
        self->animCurFrame = 12;
        if (summonAttackState == SUMMON_START) {
            SetStep(2);
        }
        if (handAttackMode == ((self->params) + 1)) {
            SetStep(3);
        }
        break;
    case 2:
        switch (self->step_s) {
        case 0:
            self->animCurFrame = 12;
            // Once we see that the summoned monster is being squished,
            // we step ahead into the squish process
            if (summonAttackState == SUMMON_SQUISH_START) {
                self->step_s++;
            }
            break;
        case 1:
            // Once our pose is finished we can move onward
            if ((!self->poseTimer) && (self->pose == 3)) {
                summonAttackState = SUMMON_SQUISHING;
            }
            // Once we've swooped, the summon is done and can
            // cleanup the spawned entities, while we unswoop.
            if (AnimateEntity(anim_arm_swoop, self) == 0) {
                summonAttackState = SUMMON_CLEANUP;
                SetSubStep(2);
            }
            break;
        case 2:
            if (AnimateEntity(anim_arm_unswoop, self) == 0) {
                SetStep(1);
            }
            break;
        }
        break;
    case 3:
        switch (self->step_s) {
        case 0:
            if (AnimateEntity(anim_arm_swoop_slow, self) == 0) {
                SetSubStep(1);
            }
            if ((!self->poseTimer) && (self->pose == 2)) {
                PlaySfxPositional(SFX_FIREBALL_SHOT_C);
            }
            break;
        case 1:
            if (AnimateEntity(anim_arm_unswoop, self) == 0) {
                handAttackMode = 3;
                SetStep(1);
            }
            break;
        }
        break;
    case 8:
        if (AnimateEntity(anim_arm_swoop_slower, self) == 0) {
            self->pose = 0;
            self->poseTimer = 0;
        }
        break;
    case 16:
        switch (self->step_s) {
        case 0:
            self->pose = 16 - self->animCurFrame;
            self->step_s++;
            /* fallthrough */
        case 1:
            if (AnimateEntity(anim_arm_unswoop, self) == 0) {
                self->pose = 0;
                self->poseTimer = 0;
                self->step_s++;
            }
            break;
        }
        break;
    }
    if (draculaIsInBackground) {
        self->animCurFrame = 0;
        self->hitboxState = 0;
    }
}

extern EInit g_EInitDraculaHand;

void EntityDraculaHand(Entity* self) {
    Entity* other;
    s32 i;
    s32 offsetIndex;
    s8* hitbox;

    self->palette = currentDraculaPalette;
    if ((g_BossFlag & 1) && (self->step != 16)) {
        SetStep(16);
    }
    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitDraculaHand);
        self->facingLeft = self->params;
        self->parent = &g_Entities[80];
        if (!self->params) {
            self->nextPart = self + 2;
        } else {
            self->nextPart = &g_Entities[80];
        }
        /* fallthrough */
    case 1:
        AnimateEntity(anim_hand_flex, self);
        if (summonAttackState == SUMMON_START) {
            SetStep(2);
        }
        if (handAttackMode == self->params + 1) {
            self->animCurFrame = 10;
        }
        break;
    case 2:
        switch (self->step_s) {
        case 0:
            for (i = 0; i < 2; i++) {
                other = AllocEntity(&g_Entities[144], &g_Entities[152]);
                if (other != NULL) {
                    CreateEntityFromCurrentEntity(
                        E_ID(SUMMONING_LIGHTNING), other);
                    other->params = self->params;
                    other->zPriority = self->zPriority + 4;
                }
            }
            self->animCurFrame = 9;
            self->step_s++;
            /* fallthrough */
        case 1:
            if (summonAttackState == SUMMON_SQUISH_START) {
                SetSubStep(2);
            }
            break;
        case 2:
            AnimateEntity(anim_hand_grab, self);
            if (summonAttackState == SUMMON_CLEANUP) {
                SetSubStep(3);
            }
            break;
        case 3:
            if (AnimateEntity(anim_hand_release, self) == 0) {
                SetStep(1);
            }
            break;
        }
        break;
    case 16:
        switch (self->step_s) {
        case 0:
            self->hitboxState = 0;
            self->animCurFrame = 9;
            self->step_s++;
            break;
        case 1:
            break;
        }
        break;
    }
    other = self - 1;
    self->posX.i.hi = other->posX.i.hi;
    self->posY.i.hi = other->posY.i.hi;
    offsetIndex = other->animCurFrame - 12;
    if (offsetIndex < 0) {
        offsetIndex = 0;
    }
    if (offsetIndex > 4) {
        offsetIndex = 4;
    }
    if (!self->params) {
        self->posX.i.hi += handOffsets[offsetIndex].x;
    } else {
        self->posX.i.hi -= handOffsets[offsetIndex].x;
    }
    self->posY.i.hi += handOffsets[offsetIndex].y;
    hitbox = (s8*)&handHitboxes;
    hitbox += handHitboxIndices[self->animCurFrame] * 4;
    self->hitboxOffX = *hitbox++;
    self->hitboxOffY = *hitbox++;
    self->hitboxWidth = *hitbox++;
    self->hitboxHeight = *hitbox++;
    if (draculaIsInBackground) {
        self->animCurFrame = 0;
        self->hitboxState = 0;
    } else {
        self->hitboxState = 3;
    }
}

extern EInit g_EInitDraculaPuppetHead;

void EntityDraculaPuppetHead(Entity* self) {
    Entity* previous;
    Entity* other;
    s32 sqMag;
    s16 angle;
    s32 i;
    s32 xVar2;
    s32 yVar2;
    s32 xVar;
    s32 yVar;

    self->palette = currentDraculaPalette;
    if ((g_BossFlag & 1) && ((self->step) != 0x10)) {
        SetStep(0x10);
    }
    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitDraculaPuppetHead);
        other = self + 1;
        for (i = 0; i < 5; i++, other++) {
            CreateEntityFromCurrentEntity(E_ID(DRACULA_VERTEBRA), other);
            other->zPriority = self->zPriority - i;
        }
        /* fallthrough */
    case 1:
        AnimateEntity(anim_head_jitter, self);
        other = &g_Entities[80];
        xVar = other->posX.i.hi + headLocations[self->params].x;
        yVar = other->posY.i.hi + headLocations[self->params].y;
        self->posX.i.hi = xVar;
        self->posY.i.hi = yVar;
        self->zPriority = other->zPriority + 2;
        self->hitboxState = 0;
        if (headAttackCycler == self->params + 1) {
            self->zPriority = other->zPriority + 6;
            SetStep(2);
        }
        if (triangleAttackState == 1) {
            self->zPriority = other->zPriority + 6;
            SetStep(3);
        }
        break;
    case 2:
        self->hitboxState = 3;
        switch (self->step_s) {
        case 0:
            other = &PLAYER;
            xVar = other->posX.i.hi - self->posX.i.hi;
            yVar = other->posY.i.hi - self->posY.i.hi;
            angle = ratan2(yVar, xVar);
            self->velocityX = (rcos(angle) << 0x12) >> 0xC;
            self->velocityY = (rsin(angle) << 0x12) >> 0xC;
            PlaySfxPositional(SFX_DRACULA_MONSTER_ROAR);
            self->step_s++;
            /* fallthrough */
        case 1:
            MoveEntity();
            if (AnimateEntity(anim_head_open_mouth, self) == 0) {
                SetSubStep(2);
            }
            break;
        case 2:
            AnimateEntity(anim_head_close_mouth, self);
            MoveEntity();
            other = &g_Entities[80];
            xVar = other->posX.i.hi + headLocations[self->params].x;
            yVar = other->posY.i.hi + headLocations[self->params].y;
            xVar -= self->posX.i.hi;
            yVar -= self->posY.i.hi;
            angle = ratan2(yVar, xVar);
            self->velocityX = rcos(angle) << 5;
            self->velocityY = rsin(angle) << 5;
            if ((abs(xVar) < 3) && (abs(yVar) < 3)) {
                headAttackCycler++;
                SetStep(1);
            }
            break;
        }
        break;
    case 3:
        switch (self->step_s) {
        case 0:
            angle = headTriangleAngles[self->params];
            self->velocityX = (rcos(angle) << 0x12) >> 0xC;
            self->velocityY = (rsin(angle) << 0x12) >> 0xC;
            self->step_s++;
            /* fallthrough */
        case 1:
            MoveEntity();
            if (AnimateEntity(anim_head_open_mouth, self) == 0) {
                g_api.PlaySfx(SFX_WEAPON_APPEAR);
                other = AllocEntity(&g_Entities[192], &g_Entities[256]);
                if (other != NULL) {
                    CreateEntityFromCurrentEntity(
                        E_ID(TRIANGLE_CORNER_GLOW), other);
                    other->ext.finalDrac.unk9C = self;
                    other->zPriority = self->zPriority + 1;
                }
                triangleAttackState++;
                self->step_s++;
            }
            break;
        case 2:
            if (triangleAttackState == TRI_CLEANUP) {
                self->step_s++;
            }
            break;
        case 3:
            AnimateEntity(anim_head_close_mouth, self);
            MoveEntity();
            other = &g_Entities[80];
            xVar = other->posX.i.hi + headLocations[self->params].x;
            yVar = other->posY.i.hi + headLocations[self->params].y;
            xVar -= self->posX.i.hi;
            yVar -= self->posY.i.hi;
            angle = ratan2(yVar, xVar);
            self->velocityX = rcos(angle) * 0x28;
            self->velocityY = rsin(angle) * 0x28;
            if ((abs(xVar) < 3) && (abs(yVar) < 3)) {
                SetStep(1);
            }
            break;
        }
        break;
    case 16:
        switch (self->step_s) {
        case 0:
            self->hitboxState = 0;
            self->animCurFrame = 0x12;
            MoveEntity();
            other = &g_Entities[80];
            xVar = other->posX.i.hi + headLocations[self->params].x;
            yVar = other->posY.i.hi + headLocations[self->params].y;
            xVar -= self->posX.i.hi;
            yVar -= self->posY.i.hi;
            angle = ratan2(yVar, xVar);
            self->velocityX = rcos(angle) * 0x28;
            self->velocityY = rsin(angle) * 0x28;
            if ((abs(xVar) < 3) && (abs(yVar) < 3)) {
                self->zPriority = ((other->zPriority) + 2);
                self->step_s++;
            }
            break;
        case 1:
            other = &g_Entities[80];
            xVar = other->posX.i.hi + headLocations[self->params].x;
            yVar = other->posY.i.hi + headLocations[self->params].y;
            self->posX.i.hi = xVar;
            self->posY.i.hi = yVar;
            break;
        }
        break;
    }
    other = &g_Entities[80];
    xVar2 = other->posX.val + (headLocations[self->params].x << 0x10);
    yVar2 = other->posY.val + (headLocations[self->params].y << 0x10);

    other = self + 5;
    for (i = 0; i < 5; i++) {
        previous = other - 1;
        xVar2 = (xVar2 + previous->posX.val) >> 1;
        yVar2 = (yVar2 + previous->posY.val) >> 1;
        xVar = xVar2 - other->posX.val;
        yVar = yVar2 - other->posY.val;
        xVar2 = (xVar >> 2) + xVar2;
        yVar2 = (yVar >> 2) + yVar2;
        other->posX.val = xVar2;
        other->posY.val = yVar2;
        other->zPriority = (self->zPriority - 5 + i);
        other = previous;
    }
    other = &g_Entities[80];
    xVar2 = other->posX.i.hi + headLocations[self->params].x;
    yVar2 = other->posY.i.hi + headLocations[self->params].y;
    other = self + 5;
    for (i = 0; i < 6; i++, other--) {
        xVar = other->posX.i.hi - xVar2;
        yVar = other->posY.i.hi - yVar2;
        angle = ratan2(yVar, xVar);
        sqMag = (xVar * xVar) + (yVar * yVar);
        if (sqMag > 0x90) {
            other->posX.i.hi = xVar2 + ((rcos(angle) * 0xC) >> 0xC);
            other->posY.i.hi = yVar2 + ((rsin(angle) * 0xC) >> 0xC);
        }
        xVar2 = other->posX.i.hi;
        yVar2 = other->posY.i.hi;
    }
    if (draculaIsInBackground) {
        self->animCurFrame = 0;
        self->hitboxState = 0;
    }
}

void EntityDraculaPuppetVertebra(Entity* self) {
    self->palette = currentDraculaPalette;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitDraculaMisc);
        self->animCurFrame = 0x11;
        /* fall through */
    case 1:
        self->animCurFrame = 0x11;
        break;
    }

    if (draculaIsInBackground) {
        self->animCurFrame = 0;
        self->hitboxState = 0;
    }
}

// A group of 5 entities which cling onto Dracula but don't really do anything
void EntityDraculaDecoration(Entity* self) {
    AnimateEntityFrame* anim;
    Entity* source;

    self->palette = currentDraculaPalette;
    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitDraculaMisc);
        /* fall through */
    case 1:
        anim = decorEntAnims[self->params];
        AnimateEntity(anim, self);
        source = &g_Entities[80];
        self->posX.i.hi = source->posX.i.hi;
        self->posY.i.hi = source->posY.i.hi;
        break;
    }

    if (draculaIsInBackground) {
        self->animCurFrame = 0;
        self->hitboxState = 0;
    }
}

// This is the hand of the small humanoid dracula - the two giant hands are
// EntityDraculaHand. All it does is wave occasionally.
void EntityDraculaSmallHand(Entity* self) {
    Entity* other;
    other = &g_Entities[80];
    self->posX.i.hi = other->posX.i.hi;
    self->posY.i.hi = other->posY.i.hi;
    self->palette = currentDraculaPalette;
    if ((g_BossFlag & 1) && (self->step != 16)) {
        SetStep(16);
    }
    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitDraculaMisc);
        /* fallthrough */
    case 1:
        AnimateEntity(anim_hand_gesture, self);
        break;
    case 16:
        self->animCurFrame = 27;
        break;
    }
    if (draculaIsInBackground) {
        self->animCurFrame = 0;
        self->hitboxState = 0;
    }
}

extern EInit g_EInitInteractable;

void EntityDraculaWings(Entity* self) {
    Primitive* prim;
    s32 primIndex;
    Entity* other;
    s16 angle;
    s16 yVar;
    s16 xVar;
    s32 i;
    s32 color;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitInteractable);
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 4);
        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags |= FLAG_HAS_PRIMS;
        self->primIndex = primIndex;
        prim = &g_PrimBuf[primIndex];
        for (self->ext.finalDrac.prim = prim; prim != NULL; prim = prim->next) {
            prim->tpage = 0x14;
            prim->clut = PAL_DRACULA_WINGS;
            prim->priority = self->zPriority - 1;
            prim->drawMode = DRAW_HIDE;
        }
        // Initialize 4 prims. This loop runs twice, creating two prims each
        prim = self->ext.finalDrac.prim;
        for (i = 0; i < 2; i++) {
            // Small subwing
            prim->u0 = 193;
            prim->u1 = 255;
            prim->u2 = 193;
            prim->u3 = 255;
            prim->v0 = 1;
            prim->v1 = 1;
            prim->v2 = 71;
            prim->v3 = 71;
            prim->priority = self->zPriority - 2;
            prim = prim->next;
            // Main large wing
            prim->u0 = 1;
            prim->u1 = 191;
            prim->u2 = 1;
            prim->u3 = 191;
            prim->v0 = 1;
            prim->v1 = 1;
            prim->v2 = 180;
            prim->v3 = 180;
            prim = prim->next;
        }
    case 1:
        other = &g_Entities[80];
        self->posX.i.hi = other->posX.i.hi;
        self->posY.i.hi = other->posY.i.hi;
        self->ext.finalDrac.hoverPhase += 0x10;
        angle = self->rotate =
            (rsin(self->ext.finalDrac.hoverPhase) << 7) >> 0xC;
        prim = self->ext.finalDrac.prim;
        for (i = 0; i < 2; i++) {
            if (i == 0) {
                xVar = self->posX.i.hi - 8;
            } else {
                xVar = self->posX.i.hi + 8;
            }
            yVar = self->posY.i.hi - 0x34;
            prim->x1 = xVar;
            prim->y1 = yVar;
            prim->x3 = xVar;
            prim->y3 = yVar + 0x46;
            if (i == 0) {
                xVar = xVar - ((rcos(angle) * 0x3E) >> 0xC);
            } else {
                xVar = xVar + ((rcos(angle) * 0x3E) >> 0xC);
            }
            yVar = yVar + ((rsin(angle) * 0x3E) >> 0xC);
            prim->x0 = xVar;
            prim->y0 = yVar;
            if (i == 0) {
                prim->x2 = xVar + ((rsin(angle) * 0x46) >> 0xC);
            } else {
                prim->x2 = xVar - ((rsin(angle) * 0x46) >> 0xC);
            }
            prim->y2 = yVar + ((rcos(angle) * 0x46) >> 0xC);
            prim->drawMode = DRAW_UNK02;
            prim = prim->next;

            if (i == 0) {
                xVar = xVar + 0x18;
            } else {
                xVar = xVar - 0x18;
            }
            yVar = yVar - 0x78;
            prim->x1 = xVar;
            prim->y1 = yVar;
            prim->x3 = xVar;
            prim->y3 = yVar + 0xB3;
            if (i == 0) {
                xVar = xVar - ((rcos(angle) * 0xBE) >> 0xC);
            } else {
                xVar = xVar + ((rcos(angle) * 0xBE) >> 0xC);
            }
            yVar = yVar + ((rsin(angle) * 0xBE) >> 0xC);
            prim->x0 = xVar;
            prim->y0 = yVar;
            if (i == 0) {
                prim->x2 = xVar + ((rsin(angle) * 0xB3) >> 0xC);
            } else {
                prim->x2 = xVar - ((rsin(angle) * 0xB3) >> 0xC);
            }
            prim->y2 = yVar + ((rcos(angle) * 0xB3) >> 0xC);
            prim->drawMode = DRAW_UNK02;
            prim = prim->next;
        }
    }
    prim = self->ext.finalDrac.prim;
    color = currentDraculaPalette & 0xFFF;
    if (color == PAL_DRACULA) {
        color = PAL_DRACULA_WINGS;
    }
    while (prim != NULL) {
        prim->clut = color;
        if (draculaIsInBackground) {
            prim->drawMode |= DRAW_HIDE;
        }
        prim = prim->next;
    }
    FntPrint("color %x\n", currentDraculaPalette);
}

// Very faint lightning appears between the hands in front of the summoning
// portal. Destroyed once the boss has arrived. Hard to see this entity.
void EntitySummoningLightning(Entity* self) {
    Entity* other;
    s16 arctan;
    s32 primIndex;
    s32 length;
    Primitive* prim2;
    Primitive* prim;
    u8 var_s7;
    s32 i;
    s16 angle1;
    s32 xVar;
    s32 yVar;
    s16 angle2;

    if (g_BossFlag & 1) {
        DestroyEntity(self);
        return;
    }
    if (summonAttackState == SUMMON_ARRIVED) {
        DestroyEntity(self);
        return;
    }
    // Log the two arms. One is our source, one is destination
    if (!self->params) {
        self->ext.finalDrac.unk9C = &g_Entities[86];
        self->ext.finalDrac.unkA0 = &g_Entities[88];
    } else {
        self->ext.finalDrac.unkA0 = &g_Entities[86];
        self->ext.finalDrac.unk9C = &g_Entities[88];
    }
    other = self->ext.finalDrac.unk9C;
    self->posX.i.hi = other->posX.i.hi;
    self->posY.i.hi = other->posY.i.hi;
    if (!(g_Timer & 0xF)) {
        // This is bad. Not proper arguments. Necessitates empty
        // prototype in gameapi.
        // Probably supposed to be PlaySfxVolPan
        g_api.PlaySfx(SFX_DRACULA_ELECTRICITY, 0x70, 0);
    }
    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitInteractable);
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 20);
        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags |= FLAG_HAS_PRIMS;
        self->primIndex = primIndex;
        prim = &g_PrimBuf[primIndex];
        self->ext.finalDrac.prim = prim;
        self->ext.dracZap.prim2 = prim;
        i = 0;
        while (prim != NULL) {
            prim->tpage = 0x1A;
            prim->clut = 0x194;
            prim->u0 = prim->u1 = (i * 0x10) + 144;
            prim->u2 = prim->u3 = prim->u0 + 0x10;
            prim->v0 = prim->v2 = 208;
            prim->v1 = prim->v3 = 192;
            prim->r0 = prim->g0 = prim->b0 = 0x50;
            LOW(prim->r1) = LOW(prim->r0);
            LOW(prim->r2) = LOW(prim->r0);
            LOW(prim->r3) = LOW(prim->r0);
            prim->priority = self->zPriority + 1;
            prim->drawMode = DRAW_HIDE;
            prim = prim->next;
            i++;
            if (i > 5) {
                i = 0;
            }
        }
    case 1:
        prim = self->ext.finalDrac.prim;
        prim->x0 = self->posX.i.hi;
        prim->y0 = self->posY.i.hi;
        prim->x1 = prim->x0;
        prim->y1 = prim->y1 - 0x10;
        prim->x2 = self->posX.i.hi;
        prim->y2 = self->posY.i.hi;
        prim->x3 = prim->x2;
        prim->y3 = prim->y2 - 0x10;
        self->ext.dracZap.prim2 = prim;
        self->ext.dracZap.angle1 = Random() * 0x10;
        while (prim != NULL) {
            prim->r0 = prim->g0 = prim->b0 = 0x50;
            LOW(prim->r1) = LOW(prim->r0);
            LOW(prim->r2) = LOW(prim->r0);
            LOW(prim->r3) = LOW(prim->r0);
            prim->drawMode = DRAW_HIDE;
            prim = prim->next;
        }
        self->ext.dracZap.timer = 0;
        self->step++;
    case 2:
        for (i = 0; true; i++) {
            prim = self->ext.dracZap.prim2;
            angle1 = self->ext.dracZap.angle1;
            other = self->ext.finalDrac.unkA0;
            xVar = other->posX.i.hi;
            yVar = other->posY.i.hi;
            xVar -= prim->x2;
            yVar -= prim->y2;
            if ((abs(xVar) < 0x10) && (abs(yVar) < 0x10)) {
                self->step = 1;
                return;
            }
            if ((abs(xVar) < 0x20) && (abs(yVar) < 0x20)) {
                var_s7 = 1;
            } else {
                var_s7 = 0;
            }
            if (!self->ext.dracZap.timer) {
                self->ext.dracZap.timer = 4;
                if (var_s7) {
                    self->ext.dracZap.timer = 2;
                }
                arctan = ratan2(-yVar, xVar);
                angle2 = arctan - angle1;
                if (angle2 > 0x800) {
                    angle2 = angle2 - 0x1000;
                }
                if (angle2 < -0x800) {
                    angle2 = angle2 + 0x1000;
                }
                if (!var_s7) {
                    angle2 /= 4;
                } else {
                    angle2 /= 2;
                }
                self->ext.dracZap.angle2 = angle2;
            }
            angle1 += self->ext.dracZap.angle2;
            if (!var_s7) {
                angle1 += (0x60 - ((Random() & 3) << 6));
            }
            angle1 &= 0xFFF;
            prim2 = prim->next;
            if (prim2 == NULL) {
                self->step = 1;
                return;
            }
            LOW(prim2->x0) = LOW(prim->x2);
            LOW(prim2->x1) = LOW(prim->x3);
            self->ext.dracZap.angle1 = angle1;
            self->ext.dracZap.prim2 = prim2;
            xVar = (rcos(angle1) * 0xC) >> 0xC;
            yVar = -((rsin(angle1) * 0xC) >> 0xC);
            prim2->x2 = (prim2->x0 + xVar);
            prim2->y2 = (prim2->y0 + yVar);
            angle2 = angle1 - 0x400;
            length = 0x10;
            xVar = (length * rcos(angle2)) >> 0xC;
            yVar = -((length * rsin(angle2)) >> 0xC);
            xVar = prim2->x3 = (prim2->x2 + xVar);
            yVar = prim2->y3 = (prim2->y2 + yVar);
            prim2->drawMode = DRAW_UNK_40 | DRAW_TPAGE2 | DRAW_TPAGE |
                              DRAW_COLORS | DRAW_UNK02 | DRAW_TRANSP;
            self->ext.dracZap.timer--;
        }
    case 3:
        for (prim = self->ext.finalDrac.prim; prim != NULL; prim = prim->next) {
            prim->drawMode = DRAW_HIDE;
        }
        self->step = 1;
        return;
    }
}

void EntityBossPortal(Entity* self) {
    Entity* other;
    s32 temp_s1;

    if (g_BossFlag & 1) {
        DestroyEntity(self);
        return;
    }
    other = &g_Entities[80];
    self->posX.i.hi = other->posX.i.hi;
    self->posY.i.hi = other->posY.i.hi + 0x10;
    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitDraculaMisc);
        self->animCurFrame = 42;
        self->drawFlags = ENTITY_SCALEY | ENTITY_SCALEX;
        self->scaleX = self->scaleY = 0;
        /* fallthrough */
    case 1:
        self->scaleX = self->scaleY += 0x10;
        if (self->scaleX > 0x180) {
            self->step++;
        }
        break;
    case 2:
        other = &g_Entities[130];
        CreateEntityFromCurrentEntity(E_ID(SUMMONED_BOSS), other);
        other->zPriority = self->zPriority + 1;
        self->step++;
        break;
    case 3:
        // Once the summoned boss has arrived, we start to shrink
        if (summonAttackState == SUMMON_ARRIVED) {
            self->step++;
        }
        break;
    case 4:
        temp_s1 = self->scaleX;
        temp_s1 -= 0x20;
        self->scaleX = self->scaleY = temp_s1;
        if (temp_s1 < 0) {
            DestroyEntity(self);
        }
        break;
    }
}

// Fake bosses summon in, but then squished by Dracula.
// Runs in a fixed cycle of 8 bosses: Karasuman, Succubus,
// Slogra, Medusa, Akmodan, Cerberus, Gaibon, Werewolf
// Weirdly this cycle is maintained with a global var that
// I'm calling bossSummonCycler. Normally I would expect this
// to be kept in Dracula's Ext, and then passed to this entity
// in its params field. Somewhat unusual.
void EntitySummonedBoss(Entity* self) {
    Entity* other;
    s32 scaleY;
    s32 i;

    if (g_BossFlag & 1) {
        DestroyEntity(self);
        return;
    }
    other = &g_Entities[80];
    self->posX.i.hi = other->posX.i.hi;
    self->posY.i.hi = other->posY.i.hi + 0x10;
    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitDraculaMisc);
        self->animCurFrame = bossSummonCycler + 45;
        self->drawFlags = ENTITY_SCALEY | ENTITY_SCALEX;
        self->scaleX = self->scaleY = 0;
        self->drawFlags |= ENTITY_OPACITY;
        self->opacity = 0;
        /* fallthrough */
    case 1:
        self->scaleX = self->scaleY += 8;
        if (self->scaleX >= 0x100) {
            self->scaleX = self->scaleY = 0x100;
            self->step++;
        }
        /* fallthrough */
    case 2:
        // Increase opacity until 0x80. Then flag that we have arrived.
        self->opacity += 2;
        if (self->opacity >= 0x80) {
            summonAttackState = SUMMON_ARRIVED;
            self->step = 3;
        }
        break;
    case 3:
        if (summonAttackState == SUMMON_SQUISHING) {
            g_api.PlaySfx(SFX_DRACULA_KARASUMAN_SQUISH);
            self->step++;
        }
        break;
    case 4:
        self->scaleX += 8;
        scaleY = self->scaleY;
        scaleY -= 0x18;
        if (scaleY < 0) {
            scaleY = 0;
        }
        self->scaleY = scaleY;
        for (i = 0; i < 16; i++) {
            other = AllocEntity(&g_Entities[192], &g_Entities[256]);
            if (other != NULL) {
                CreateEntityFromEntity(E_ID(SQUISH_BLOOD_BALLS), self, other);
                other->zPriority = self->zPriority + 1;
            }
        }
        if (scaleY == 0) {
            self->animCurFrame = 0;
            self->ext.finalDrac.timer = 0x50;
            self->step++;
        }
        break;
    case 5:
        if (!--self->ext.finalDrac.timer) {
            g_api.PlaySfx(SFX_NOISE_SWEEP_DOWN_A);
            DestroyEntity(self);
        }
        break;
    }
}

// The balls of blood that pop out when the summoned boss is squished
void EntitySquishBloodBalls(Entity* self) {
    s32 xVar;
    s32 yVar;
    Entity* other;
    s16 angle;
    s32 speed;

    if (g_BossFlag & 1) {
        DestroyEntity(self);
        return;
    }
    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitDraculaMisc);
        self->drawFlags = ENTITY_SCALEY | ENTITY_SCALEX;
        self->scaleX = self->scaleY = (Random() & 0x7F) + 0x80;
        self->blendMode = BLEND_TRANSP;
        angle = rand() & 0xFFF;
        speed = (Random() & 0x1F) + 0x10;
        self->velocityX = speed * rcos(angle);
        self->velocityY = speed * rsin(angle);
        self->posX.val = self->posX.val + (self->velocityX * 4);
        self->posY.val += self->velocityY * 4;
        self->ext.finalDrac.timer = ((Random() & 0x1F) + 0x10);
        /* fallthrough */
    case 1:
        MoveEntity();
        AnimateEntity(anim_red_ball_squish, self);
        self->velocityX -= self->velocityX >> 5;
        self->velocityY -= self->velocityY >> 5;
        if (summonAttackState == SUMMON_CLEANUP) {
            self->velocityX = 0;
            self->velocityY = 0;
            self->step++;
        }
        break;
    case 2:
        AnimateEntity(anim_red_ball_squish, self);
        if (!--self->ext.finalDrac.timer) {
            self->step++;
        }
        if (!(g_Timer & 7)) {
            g_api.PlaySfx(SFX_NOISE_SWEEP_DOWN_B);
        }
        break;
    case 3:
        MoveEntity();
        if (self->scaleX > 0x20) {
            self->scaleX = self->scaleY -= 2;
        }
        other = &g_Entities[80];
        xVar = other->posX.i.hi - self->posX.i.hi;
        yVar = other->posY.i.hi - 0x18 - self->posY.i.hi;
        angle = ratan2(yVar, xVar);
        if (self->ext.finalDrac.bloodSpeed < FIX(3)) {
            self->ext.finalDrac.bloodSpeed += 0x1000;
        }
        speed = self->ext.finalDrac.bloodSpeed;
        self->velocityX = (speed * rcos(angle)) >> 0xC;
        self->velocityY = (speed * rsin(angle)) >> 0xC;
        speed = (xVar * xVar) + (yVar * yVar);
        if (speed < 0x40) {
            DestroyEntity(self);
        }
        break;
    }
}

extern EInit g_EInitDraculaOrbAttack;

void EntityBlueFlashingOrb(Entity* self) {
    Entity* other;
    s32 scale;
    s32 xVar;
    s32 yVar;

    if (g_BossFlag & 1) {
        DestroyEntity(self);
        return;
    }
    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitDraculaOrbAttack);
        self->drawFlags = ENTITY_SCALEY | ENTITY_SCALEX;
        self->scaleX = self->scaleY = 0;
        self->blendMode |= BLEND_ADD | BLEND_TRANSP;
        self->drawFlags |= ENTITY_OPACITY;
        self->opacity = 0x60;
        self->hitboxState = 0;
        /* fallthrough */
    case 1:
        AnimateEntity(anim_blue_flashing_orb, self);
        scale = self->scaleX;
        scale += 0x10;
        if (scale > 0xCC) {
            scale = 0xCC;
        }
        self->scaleX = self->scaleY = scale;
        if (orbAttackLaunch) {
            self->ext.finalDrac.timer = 0x60;
            other = &PLAYER;
            xVar = other->posX.val - self->posX.val;
            yVar = other->posY.val - self->posY.val;
            self->velocityX = xVar / 96;
            self->velocityY = yVar / 96;
            self->step++;
        }
        if (!(g_Timer & 0x1F)) {
            g_api.PlaySfxVolPan(SFX_RAPID_SYNTH_BUBBLE_SHORT, 0x50, 0);
        }
        break;
    case 2:
        AnimateEntity(anim_blue_flashing_orb, self);
        MoveEntity();
        scale = 0x6000 / (self->ext.finalDrac.timer + 0x18);
        self->scaleX = self->scaleY = scale;
        if (!(self->ext.finalDrac.timer & 3)) {
            other = AllocEntity(&g_Entities[192], &g_Entities[256]);
            if (other != NULL) {
                CreateEntityFromEntity(E_ID(BLUE_ORB_SHADOW), self, other);
                other->scaleX = other->scaleY = self->scaleX;
                other->zPriority = self->zPriority;
                other->opacity = self->opacity;
            }
        }
        if (!(self->ext.finalDrac.timer & 0xF)) {
            g_api.PlaySfxVolPan(
                SFX_RIC_SUC_REVIVE, 0x80 - self->ext.finalDrac.timer / 2, 0);
        }
        if (!--self->ext.finalDrac.timer) {
            g_api.PlaySfx(SFX_FIREBALL_SHOT_B);
            self->zPriority = g_unkGraphicsStruct.g_zEntityCenter + 8;
            other = &PLAYER;
            xVar = other->posX.i.hi - self->posX.i.hi;
            yVar = other->posY.i.hi - self->posY.i.hi;
            scale = self->scaleX * 20 / 256;
            if (((xVar * xVar) + (yVar * yVar)) < (scale * scale)) {
                self->hitboxOffX = xVar;
                self->hitboxOffY = yVar;
                self->hitboxState = 1;
            }
            self->step++;
        }
        break;
    case 3:
        DestroyEntity(self);
        break;
    }
}

void EntityBlueOrbShadow(Entity* self) {
    s32 opacity;

    if (!self->step) {
        InitializeEntity(g_EInitDraculaMisc);
        self->drawFlags = ENTITY_SCALEY | ENTITY_SCALEX;
        self->drawFlags |= ENTITY_OPACITY;
        self->blendMode = BLEND_ADD | BLEND_TRANSP;
    }
    AnimateEntity(anim_blue_orb_shadow, self);
    opacity = self->opacity;
    opacity -= 2;
    if (opacity < 0) {
        opacity = 0;
    }
    self->opacity = opacity;
    if (opacity == 0) {
        DestroyEntity(self);
    }
}

extern EInit g_EInitDraculaTriangleAttack;

void EntityRainbowTriangleAttack(Entity* self) {
    s16 angle;
    s16 redAngle;
    s32 primIndex;
    s32 brightness;
    s32 xVar;
    s32 yVar;
    s32 sine;
    s32 cosine;
    Entity* other;
    Primitive* prim;
    s16 greenAngle;
    s16 blueAngle;
    Pos* SP_PosArr;
    s16* primXY;
    s32 tmp;
    s32 i;
    s16* extXY;
    u8* rgb;

    if (g_BossFlag & 1) {
        DestroyEntity(self);
        return;
    }
    SP_PosArr = (Pos*)SP(0);
    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitDraculaTriangleAttack);
        self->hitboxState = 0;
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 10);
        if (primIndex == -1) {
            self->step = 0;
            return;
        }
        self->flags |= FLAG_HAS_PRIMS;
        self->primIndex = primIndex;
        prim = &g_PrimBuf[primIndex];
        self->ext.finalDrac.prim = prim;
        // 3 lines to connect the heads and make a triangle
        for (i = 0; i < 3; i++) {
            prim->type = PRIM_LINE_G2;
            prim->r0 = prim->g0 = prim->b0 = 0xC0;
            prim->r1 = prim->g1 = prim->b1 = 0xC0;
            prim->priority = self->zPriority;
            prim->drawMode =
                DRAW_TPAGE2 | DRAW_TPAGE | DRAW_UNK02 | DRAW_TRANSP;
            prim = prim->next;
        }
        prim->type = PRIM_GT3;
        prim->tpage = 0x1A;
        prim->clut = 0x15F;
        prim->u0 = prim->v0 = 0x10;
        prim->u1 = 0x14;
        prim->v1 = 0x10;
        prim->u2 = prim->v2 = 0x14;
        prim->r0 = prim->g0 = prim->b0 = 0x10;
        LOW(prim->r1) = LOW(prim->r0);
        LOW(prim->r2) = LOW(prim->r0);
        prim->priority = self->zPriority;
        prim->drawMode =
            DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS | DRAW_UNK02 | DRAW_TRANSP;
        self->opacity = 0;
    case 1:
        // Iterate over the 3 heads and save where they are so we can
        // draw around them
        other = &g_Entities[91];
        for (i = 0; i < 3; i++, other += 6) {
            SP_PosArr[i].x.i.hi = other->posX.i.hi;
            SP_PosArr[i].y.i.hi = other->posY.i.hi + 12;
        }
        // Take the first head and save its location again.
        // We'll draw lines between head i and head i+1 and it's
        // easiest to draw from the third one to a fake fourth one
        // than to have a special case to connect back to the start.
        other = &g_Entities[91];
        SP_PosArr[3].x.i.hi = other->posX.i.hi;
        SP_PosArr[3].y.i.hi = other->posY.i.hi + 12;

        // Iterate over the 3 white lines and set each one's first xy
        // to the location of one of the heads
        prim = self->ext.finalDrac.prim;
        for (i = 0; i < 3; i++) {
            prim->x0 = SP_PosArr[i].x.i.hi;
            prim->y0 = SP_PosArr[i].y.i.hi;
            prim = prim->next;
        }
        prim = self->ext.finalDrac.prim;
        // Mark the second point to go to the next head
        for (i = 1; i < 4; i++) {
            prim->x1 = SP_PosArr[i].x.i.hi;
            prim->y1 = SP_PosArr[i].y.i.hi;
            prim = prim->next;
        }
        // Now set all 3 vertices of the big triangle
        prim->x0 = SP_PosArr[0].x.i.hi;
        prim->y0 = SP_PosArr[0].y.i.hi;
        prim->x1 = SP_PosArr[1].x.i.hi;
        prim->y1 = SP_PosArr[1].y.i.hi;
        prim->x2 = SP_PosArr[2].x.i.hi;
        prim->y2 = SP_PosArr[2].y.i.hi;
        self->opacity += 3;
        redAngle = self->ext.finalDrac.redAngle += 0x100;
        greenAngle = self->ext.finalDrac.greenAngle += 0x40;
        blueAngle = self->ext.finalDrac.blueAngle += 0x80;
        rgb = &prim->r0;
        tmp = self->opacity;
        for (i = 0; i < 3; i++, rgb += 12) {
            rgb[0] = (tmp + ((tmp * rcos(redAngle)) >> 0xC)) / 2;
            rgb[1] = (tmp + ((tmp * rsin(greenAngle)) >> 0xC)) / 2;
            rgb[2] = (tmp + ((tmp * rcos(blueAngle)) >> 0xC)) / 2;
            redAngle += 0x40;
            greenAngle += 0x280;
            blueAngle += 0x100;
        }
        if (self->opacity > 0x40) {
            xVar = 0;
            yVar = 0;
            // Warning here: extXY uninitialized, but unused so it's ok
            for (i = 0; i < 3; i++, extXY += 2) {
                xVar += SP_PosArr[i].x.i.hi;
                yVar += SP_PosArr[i].y.i.hi;
            }
            self->posX.i.hi = xVar / 3;
            self->posY.i.hi = yVar / 3;
            extXY = &self->ext.finalDrac.triangleXY[0];
            for (i = 0; i < 3; i++, extXY += 2) {
                extXY[0] = SP_PosArr[i].x.i.hi - self->posX.i.hi;
                extXY[1] = SP_PosArr[i].y.i.hi - self->posY.i.hi;
            }
            self->scaleX = 0x100;
            self->step++;
        }
        break;
    case 2:
        prim = self->ext.finalDrac.prim;
        for (i = 0; i < 3; i++) {
            brightness = PrimDecreaseBrightness(prim, 8);
            if (brightness == 0) {
                prim->drawMode = DRAW_HIDE;
            }
            prim = prim->next;
        }
        self->scaleX -= 8;
        primXY = &prim->x0;
        tmp = self->scaleX;
        xVar = self->posX.i.hi;
        yVar = self->posY.i.hi;
        extXY = &self->ext.finalDrac.triangleXY[0];
        for (i = 0; i < 3; i++, extXY += 2, primXY += 6) {
            primXY[0] = xVar + ((extXY[0] * tmp) >> 8);
            primXY[1] = yVar + ((extXY[1] * tmp) >> 8);
        }
        if (self->opacity < 0xC0) {
            self->opacity += 4;
        }
        redAngle = self->ext.finalDrac.redAngle += 0x100;
        greenAngle = self->ext.finalDrac.greenAngle += 0x40;
        blueAngle = self->ext.finalDrac.blueAngle += 0x80;
        rgb = &prim->r0;
        tmp = self->opacity;
        for (i = 0; i < 3; i++, rgb += 12) {
            rgb[0] = (tmp + ((tmp * rcos(redAngle)) >> 0xC)) / 2;
            rgb[1] = (tmp + ((tmp * rsin(greenAngle)) >> 0xC)) / 2;
            rgb[2] = (tmp + ((tmp * rcos(blueAngle)) >> 0xC)) / 2;
            redAngle += 0x40;
            greenAngle += 0x280;
            blueAngle += 0x100;
        }
        if (self->scaleX < 0x60) {
            prim = self->ext.finalDrac.prim;
            for (i = 0; i < 3; i++) {
                prim->drawMode = DRAW_HIDE;
                prim = prim->next;
            }
            extXY = &self->ext.finalDrac.triangleXY[0];
            tmp = self->scaleX;
            for (i = 0; i < 3; i++, extXY += 2) {
                extXY[0] = ((extXY[0] * tmp) >> 8);
                extXY[1] = ((extXY[1] * tmp) >> 8);
            }
            self->step++;
            return;
        }
        break;
    case 3:
        other = &PLAYER;
        xVar = other->posX.i.hi - self->posX.i.hi;
        yVar = other->posY.i.hi - self->posY.i.hi;
        angle = ratan2(yVar, xVar);
        self->velocityX = (rcos(angle) << 0x12) >> 0xC;
        self->velocityY = (rsin(angle) << 0x12) >> 0xC;
        self->hitboxState = 1;
        g_api.PlaySfx(SFX_DRACULA_TRIANGLE_ATTACK);
        self->step++;
        /* fallthrough */
    case 4:
        MoveEntity();
        self->flags |= FLAG_DESTROY_IF_OUT_OF_CAMERA;
        if (self->velocityX > 0) {
            self->rotate += ROT(5.625);
        } else {
            self->rotate -= ROT(5.625);
        }
        prim = self->ext.finalDrac.prim;
        for (i = 0; i < 3; i++) {
            prim = prim->next;
        }
        redAngle = self->ext.finalDrac.redAngle += 0x100;
        greenAngle = self->ext.finalDrac.greenAngle += 0x40;
        blueAngle = self->ext.finalDrac.blueAngle += 0x80;
        rgb = &prim->r0;
        tmp = self->opacity;
        for (i = 0; i < 3; i++, rgb += 12) {
            rgb[0] = (tmp + ((tmp * rcos(redAngle)) >> 0xC)) / 2;
            rgb[1] = (tmp + ((tmp * rsin(greenAngle)) >> 0xC)) / 2;
            rgb[2] = (tmp + ((tmp * rcos(blueAngle)) >> 0xC)) / 2;
            redAngle += 0x40;
            greenAngle += 0x280;
            blueAngle += 0x100;
        }
        primXY = &prim->x0;
        xVar = self->posX.i.hi;
        yVar = self->posY.i.hi;
        extXY = &self->ext.finalDrac.triangleXY[0];
        angle = self->rotate;
        sine = rsin(angle);
        cosine = rcos(angle);
        for (i = 0; i < 3; i++, extXY += 2, primXY += 6) {
            primXY[0] =
                xVar + (((extXY[0] * cosine) - (extXY[1] * sine)) >> 0xC);
            primXY[1] =
                yVar + (((extXY[0] * sine) + (extXY[1] * cosine)) >> 0xC);
        }
        break;
    }
}

// When the triangle attack is happening, each corner gets a small glowing
// blue ball. This entity is that ball.
void EntityTriangleCornerGlow(Entity* self) {
    Entity* other;

    if (g_BossFlag & 1) {
        DestroyEntity(self);
        return;
    }

    if (!self->step) {
        InitializeEntity(g_EInitDraculaMisc);
        self->blendMode = BLEND_ADD | BLEND_TRANSP;
    }

    AnimateEntity(anim_small_blue_ball_pulse, self);

    other = self->ext.finalDrac.unk9C;
    self->posX.i.hi = other->posX.i.hi;
    self->posY.i.hi = other->posY.i.hi + 12;

    if (triangleAttackState == TRI_CLEANUP) {
        DestroyEntity(self);
    }
}
