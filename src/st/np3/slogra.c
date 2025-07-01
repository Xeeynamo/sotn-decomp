// SPDX-License-Identifier: AGPL-3.0-or-later
#include "np3.h"

#ifdef VERSION_PSP
extern s32 E_ID(SLOGRA_SPEAR);
extern s32 E_ID(SLOGRA_SPEAR_PROJECTILE);
#endif

typedef enum {
    SLOGRA_INIT,
    SLOGRA_FLOOR_ALIGN,
    SLOGRA_IDLE,
    SLOGRA_TAUNT_WITH_SPEAR,
    SLOGRA_SPEAR_POKE,
    SLOGRA_SPEAR_FIRE,
    SLOGRA_ATTACK,
    SLOGRA_KNOCKBACK = 8,
    SLOGRA_WALKING_WITH_SPEAR,
    SLOGRA_TAUNT_WITHOUT_SPEAR,
    SLOGRA_WALKING_WITHOUT_SPEAR,
    SLOGRA_LOSE_SPEAR,
    SLOGRA_GAIBON_COMBO_ATTACK,
    SLOGRA_GAIBON_RETREAT,
    SLOGRA_DYING = 16,
    SLOGRA_DEBUG = 255,
} SlograSteps;

typedef enum {
    SLOGRA_FIRE_FACE_PLAYER,
    SLOGRA_FIRE_PROJECTILE,
    SLOGRA_FIRE_COOLDOWN,
    SLOGRA_FIRE_END,
} SlograSpearFireSubSteps;

typedef enum {
    SLOGRA_COMBO_ATTACK_START,
    SLOGRA_COMBO_ATTACK_PLUNGE,
    SLOGRA_COMBO_ATTACK_COOLDOWN,
} SlograComboAttackSubSteps;

typedef enum {
    SLOGRA_DYING_START,
    SLOGRA_DYING_EXPLODING,
    SLOGRA_DYING_END,
} SlograDyingSubSteps;

// not static since gaibon also uses it
bool slograGaibonRetreat = false;

static s16 sensors1[] = {0, 32, 0, 4, 16, -4, -32, 0};
static s16 sensors2[] = {0, 32, 16, 0};
static u8 anim1[] = {9, 1, 8, 2, 12, 3, 10, 2, 0};
static u8 anim2[] = {7, 1, 7, 4, 7, 5, 17, 1, 0};
static u8 anim3[] = {8, 1, 4, 31, 10, 32, 4, 33, 4, 34, 4, 6, 255, 0};
static u8 anim4[] = {4, 6, 3, 7, 2, 9, 4, 8, 32, 6, 255, 0};
static u8 anim5[] = {1, 6, 6, 32, 6, 31, 53, 1, 255, 0};
static u8 anim6[] = {7,  1, 5,  10, 22, 11, 2,  12,  2,
                     13, 2, 14, 2,  15, 65, 14, 255, 0};
static u8 unused_anim[] = {24, 14, 6, 13, 5, 31, 34, 1, 255, 0};
static u8 anim7[] = {3,  16, 3,  17, 1,  18, 1,  19,  1,
                     18, 1,  19, 1,  18, 24, 19, 255, 0};
static u8 anim8[] = {3, 16, 3, 17, 3, 18, 1,  21, 1,   20,
                     1, 21, 1, 20, 1, 21, 40, 20, 255, 0};
static u8 anim9[] = {9, 22, 8, 23, 12, 24, 10, 23, 0};
static u8 anim10[] = {7, 22, 7, 25, 7, 26, 17, 22, 0};
static u8 anim11[] = {3,  27, 3,  28, 1,  21, 1,  20,  1,
                      21, 1,  20, 1,  21, 24, 20, 255, 0};
static u8 anim12[] = {5, 25, 5, 26, 5, 27, 5, 28, 7,  20, 14,  21,
                      5, 27, 2, 30, 1, 29, 1, 30, 50, 29, 255, 0};
static u8 anim13[] = {2, 21, 2, 27, 2, 30, 1, 29, 1, 30, 2, 29, 255, 0};
static u8 anim14[] = {2, 21, 3, 20, 0};
static u8 anim15[] = {3, 36, 2, 37, 255, 0};
static u8 anim16[] = {2, 38, 2, 39, 2, 40, 2, 41, 2, 42, 2, 43, 255, 0};
static u8 anim17[] = {1, 38, 1, 39, 0};
static s8 slograHitboxes[] = {
    0,  0, 0,  0,  -8,  2,   19, 27, -12, 6,   19, 24, -11, 6,  19, 24,
    -7, 2, 19, 27, 0,   2,   19, 27, -82, -96, 0,  0,  -27, 13, 32, 11,
    -9, 2, 19, 27, -85, -97, 0,  0,  -4,  18,  8,  32, 0,   0,  7,  4,
    1,  1, 4,  11, 2,   1,   7,  7,  2,   1,   9,  4,  3,   1,  7,  5};
static u8 slograHitboxIdx[] = {
    0, 1, 1, 1, 1, 1, 2, 3, 2, 2, 4, 5, 1, 1, 2, 2, 5, 5, 5, 5,
    5, 5, 1, 1, 1, 4, 4, 1, 1, 7, 7, 8, 8, 8, 8, 9, 1, 1, 0, 0};
static s8 spearHitboxes[] = {
    0,   0,  0,   0,  -36, 12, 8,   5,  -36, 11, 8,   5,  -51, -5,
    19,  6,  -49, -5, 19,  6,  -33, 12, 7,   4,  -27, 8,  7,   4,
    -34, 13, 7,   4,  -40, 16, 10,  4,  -52, -5, 19,  6,  -82, -96,
    0,   0,  -36, 14, 7,   4,  -36, 16, 7,   4,  -4,  18, 4,   32};
static u8 spearHitboxIdx[] = {
    0,  0,  0,  0,  0,  0,  3,  4,  3,  3,  0,  0, 0, 0, 9, 9, 10, 10, 10, 10,
    10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 0, 0, 0, 0, 0, 13, 13, 0,  0};

extern u16 g_EInitSlograNP3[]; // Init
void EntitySlogra(Entity* self) {
    Entity* otherEnt;
    s32 unusedCollResult;
    s8* hitbox;
    u8* animation;

    self->ext.GS_Props.pickupFlag = 0;

    if (self->step) {
        if ((self->hitFlags & 3) && (self->step != SLOGRA_KNOCKBACK)) {
            SetStep(SLOGRA_KNOCKBACK);
        }
        if (!self->ext.GS_Props.nearDeath) {
            if ((self->hitPoints < g_api.enemyDefs[243].hitPoints / 4) &&
                (self->step != SLOGRA_LOSE_SPEAR)) {
                self->hitboxState = 0;
                PlaySfxPositional(SFX_SLOGRA_ROAR_DEFEAT);
                SetStep(SLOGRA_LOSE_SPEAR);
            }
        }
        otherEnt = self + 8;
        if (otherEnt->ext.GS_Props.grabedAscending) {
            if ((self->step != SLOGRA_DYING) &&
                (self->step != SLOGRA_GAIBON_COMBO_ATTACK)) {
                SetStep(SLOGRA_GAIBON_COMBO_ATTACK);
            }
        }
        if (slograGaibonRetreat) {
            self->hitboxState = 0;
            if (self->step != SLOGRA_GAIBON_RETREAT) {
                SetStep(SLOGRA_GAIBON_RETREAT);
            }
        }
    }

    switch (self->step) {
    case SLOGRA_INIT:
        if (g_CastleFlags[SLO_GAI_DEFEATED]) {
            DestroyEntity(self);
            return;
        }
        if (g_CastleFlags[SLO_GAI_RETREATED]) {
            DestroyEntity(self);
            return;
        }
        InitializeEntity(g_EInitSlograNP3);
        self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
        otherEnt = self + 1;
        CreateEntityFromCurrentEntity(E_ID(SLOGRA_SPEAR), otherEnt);

    case SLOGRA_FLOOR_ALIGN:
        if (UnkCollisionFunc3(&sensors1) & 1) {
            SetStep(SLOGRA_IDLE);
        }
        break;

    case SLOGRA_IDLE:
        AnimateEntity(anim2, self);
        if (GetDistanceToPlayerX() < 96) {
            SetStep(SLOGRA_WALKING_WITH_SPEAR);
        }
        break;

    case SLOGRA_TAUNT_WITH_SPEAR:
        if (AnimateEntity(anim2, self) == 0) {
            SetStep(SLOGRA_WALKING_WITH_SPEAR);
        }
        break;

    case SLOGRA_WALKING_WITH_SPEAR:
        if (!self->step_s) {
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
            if (self->ext.GS_Props.attackMode) {
                self->ext.GS_Props.flag = 1;
            } else {
                self->ext.GS_Props.flag = 0;
            }
            self->ext.GS_Props.timer = 128;
            self->step_s++;
        }
        AnimateEntity(anim1, self);
        self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
        if (self->facingLeft ^ self->ext.GS_Props.flag) {
            self->velocityX = FIX(0.75);
        } else {
            self->velocityX = FIX(-0.75);
        }
        UnkCollisionFunc2(&sensors2);
        if (!self->ext.GS_Props.flag) {
            if (GetDistanceToPlayerX() < 72) {
                if (!self->ext.GS_Props.attackMode) {
                    self->ext.GS_Props.timer = 1;
                } else {
                    self->ext.GS_Props.flag ^= 1;
                }
            }
        }
        if (self->ext.GS_Props.flag) {
            if (GetDistanceToPlayerX() > 112) {
                if (self->ext.GS_Props.attackMode) {
                    self->ext.GS_Props.timer = 1;
                } else {
                    self->ext.GS_Props.flag ^= 1;
                }
            }
        }
        if (!(Random() & 0x3F)) {
            SetStep(SLOGRA_TAUNT_WITH_SPEAR);
        }
        if (!--self->ext.GS_Props.timer) {
            if (self->ext.GS_Props.attackMode) {
                SetStep(SLOGRA_SPEAR_FIRE);
            } else {
                SetStep(SLOGRA_SPEAR_POKE);
            }
            self->ext.GS_Props.attackMode ^= 1;
        }
        break;

    case SLOGRA_SPEAR_POKE:
        if (!self->step_s) {
            PlaySfxPositional(SFX_SLOGRA_ROAR);
            self->step_s++;
        }
        if (AnimateEntity(anim6, self) == 0) {
            SetStep(SLOGRA_WALKING_WITH_SPEAR);
        }
        if (!self->poseTimer && self->pose == 4) {
            PlaySfxPositional(SFX_BOSS_WING_FLAP);
        }
        break;

    case SLOGRA_SPEAR_FIRE:
        switch (self->step_s) {
        case SLOGRA_FIRE_FACE_PLAYER:
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
            self->step_s++;

        case SLOGRA_FIRE_PROJECTILE:
            if (AnimateEntity(anim3, self) == 0) {
                PlaySfxPositional(SFX_FM_EXPLODE_SWISHES);
                otherEnt = AllocEntity(&g_Entities[160], &g_Entities[192]);
                if (otherEnt != NULL) {
                    CreateEntityFromEntity(
                        E_ID(SLOGRA_SPEAR_PROJECTILE), self, otherEnt);
                    if (self->facingLeft) {
                        otherEnt->posX.i.hi += 68;
                    } else {
                        otherEnt->posX.i.hi -= 68;
                    }
                    otherEnt->posY.i.hi -= 6;
                    otherEnt->facingLeft = self->facingLeft;
                    otherEnt->zPriority = self->zPriority + 1;
                }
                SetSubStep(SLOGRA_FIRE_COOLDOWN);
            }
            break;

        case SLOGRA_FIRE_COOLDOWN:
            if (AnimateEntity(anim4, self) == 0) {
                SetSubStep(SLOGRA_FIRE_END);
            }
            break;

        case SLOGRA_FIRE_END:
            if (AnimateEntity(anim5, self) == 0) {
                SetStep(SLOGRA_WALKING_WITH_SPEAR);
            }
            break;
        }
        break;

    case SLOGRA_KNOCKBACK:
        if (!self->step_s) {
            PlaySfxPositional(SFX_SLOGRA_PAIN_B);
            self->step_s++;
        }
        if (self->ext.GS_Props.nearDeath) {
            animation = anim11;
        } else {
            animation = anim7;
        }
        if (AnimateEntity(animation, self) == 0) {
            SetStep(SLOGRA_WALKING_WITH_SPEAR);
            if (self->ext.GS_Props.nearDeath) {
                SetStep(SLOGRA_TAUNT_WITHOUT_SPEAR);
            }
        }
        break;

    case SLOGRA_LOSE_SPEAR:
        if (AnimateEntity(anim8, self) == 0) {
            slograGaibonRetreat = 1;
            SetStep(SLOGRA_GAIBON_RETREAT);
        }
        if (self->pose > 1) {
            self->ext.GS_Props.nearDeath = 1;
        }
        break;

    case SLOGRA_TAUNT_WITHOUT_SPEAR:
        if (AnimateEntity(anim10, self) == 0) {
            SetStep(SLOGRA_WALKING_WITHOUT_SPEAR);
        }
        break;

    case SLOGRA_WALKING_WITHOUT_SPEAR:
        if (!self->step_s) {
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
            self->ext.GS_Props.flag = 1;
            self->ext.GS_Props.timer = 128;
            self->step_s++;
        }

        AnimateEntity(anim9, self);
        self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
        if (self->facingLeft ^ self->ext.GS_Props.flag) {
            self->velocityX = FIX(0.75);
        } else {
            self->velocityX = FIX(-0.75);
        }

        UnkCollisionFunc2(&sensors2);
        if (!self->ext.GS_Props.flag && GetDistanceToPlayerX() < 72) {
            self->ext.GS_Props.flag ^= 1;
        }
        if (self->ext.GS_Props.flag) {
            if (GetDistanceToPlayerX() > 112) {
                self->ext.GS_Props.flag ^= 1;
            }
        }
        if (!(Random() & 0x3F)) {
            SetStep(SLOGRA_TAUNT_WITHOUT_SPEAR);
        }
        if (!--self->ext.GS_Props.timer) {
            SetStep(SLOGRA_ATTACK);
        }
        break;

    case SLOGRA_ATTACK: // Attack without spear
        if (AnimateEntity(anim12, self) == 0) {
            SetStep(SLOGRA_WALKING_WITHOUT_SPEAR);
        }
        if (!self->poseTimer && self->pose == 7) {
            PlaySfxPositional(SFX_BONE_THROW);
        }
        break;

    case SLOGRA_GAIBON_COMBO_ATTACK: // Unused
        switch (self->step_s) {
        case SLOGRA_COMBO_ATTACK_START:
            otherEnt = self + 8;
            if (!otherEnt->ext.GS_Props.grabedAscending) {
                self->velocityX = 0;
                self->velocityY = 0;
                self->step_s++;
            }
            break;

        case 1:
            if (self->ext.GS_Props.nearDeath) {
                animation = anim13;
            } else {
                animation = anim15;
            }
            AnimateEntity(animation, self);

            if (UnkCollisionFunc3(&sensors1) & 1) {
                g_api.func_80102CD8(1);
                self->ext.GS_Props.timer = 16;
                self->step_s++;
            }
            break;

        case SLOGRA_COMBO_ATTACK_COOLDOWN:
            if (!--self->ext.GS_Props.timer) {
                SetStep(SLOGRA_WALKING_WITH_SPEAR);
                if (self->ext.GS_Props.nearDeath) {
                    SetStep(SLOGRA_WALKING_WITHOUT_SPEAR);
                }
            }
            break;
        }
        break;

    case SLOGRA_GAIBON_RETREAT:
        if (self->ext.GS_Props.nearDeath) {
            animation = anim10;
        } else {
            animation = anim2;
        }
        AnimateEntity(animation, self);
        break;

    case SLOGRA_DYING: // Unused
        switch (self->step_s) {
        case SLOGRA_DYING_START:
            self->hitboxState = 0;
            if (!self->ext.GS_Props.nearDeath) {
                self->ext.GS_Props.nearDeath = 1;
            }
            self->ext.GS_Props.timer = 64;
            PlaySfxPositional(SFX_STUTTER_EXPLODE_A);
            g_CastleFlags[SLO_GAI_RETREATED] |= 1;
            self->step_s++;

        case SLOGRA_DYING_EXPLODING:
            unusedCollResult = UnkCollisionFunc3(&sensors1);
            AnimateEntity(anim14, self);
            if (!(g_Timer & 3)) {
                otherEnt = AllocEntity(&g_Entities[224], &g_Entities[256]);
                if (otherEnt != NULL) {
                    CreateEntityFromEntity(E_EXPLOSION, self, otherEnt);
                    otherEnt->posX.i.hi += (Random() & 31) - 16;
                    otherEnt->posY.i.hi += (Random() & 31) - 16;
                    otherEnt->zPriority = self->zPriority + 1;
                    otherEnt->params = 1;
                }
            }
            if (!--self->ext.GS_Props.timer) {
                self->step_s++;
            }
            break;

        case SLOGRA_DYING_END:
            otherEnt = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (otherEnt != NULL) {
                CreateEntityFromEntity(E_EXPLOSION, self, otherEnt);
                otherEnt->posY.i.hi += 16;
                otherEnt->params = 3;
            }
            DestroyEntity(self);
            return;
        }
        break;

    case SLOGRA_DEBUG:
#include "../pad2_anim_debug.h"
    }
    hitbox = slograHitboxes;
    hitbox += 4 * slograHitboxIdx[self->animCurFrame];
    self->hitboxOffX = *hitbox++;
    self->hitboxOffY = *hitbox++;
    self->hitboxWidth = *hitbox++;
    self->hitboxHeight = *hitbox++;
}

void EntitySlograSpear(Entity* self) {
    s32 animFrame;
    Entity* slogra;
    s8* hitbox;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitSlograSpearNP3);

    case 1:
        slogra = self - 1;
        self->facingLeft = slogra->facingLeft;
        self->posX.i.hi = slogra->posX.i.hi;
        self->posY.i.hi = slogra->posY.i.hi;
        animFrame = slogra->animCurFrame;
        hitbox = spearHitboxes;
        hitbox += 4 * spearHitboxIdx[animFrame];
        self->hitboxOffX = *hitbox++;
        self->hitboxOffY = *hitbox++;
        self->hitboxWidth = *hitbox++;
        self->hitboxHeight = *hitbox++;
        if (slogra->ext.GS_Props.nearDeath) {
            self->step++;
        }
        break;

    case 2:
        switch (self->step_s) {
        case 0:
            self->drawFlags = FLAG_DRAW_ROTATE;
            self->hitboxState = 0;
            if (self->facingLeft) {
                self->velocityX = FIX(-2.25);
            } else {
                self->velocityX = FIX(2.25);
            }
            self->velocityY = FIX(-4);
            self->animCurFrame = 35;
            self->flags |= FLAG_DESTROY_IF_OUT_OF_CAMERA;
            self->step_s++;

        case 1:
            MoveEntity();
            self->velocityY += FIX(0.15625);
            self->rotate += 0x80;
            if (!(self->rotate & 0xFFF)) {
                PlaySfxPositional(SFX_ARROW_SHOT_A);
            }
        }
    }
}

// projectile fired from slogra's spear
void EntitySlograSpearProjectile(Entity* self) {
    Entity* entity;

    if (self->flags & FLAG_DEAD) {
        entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
        if (entity != NULL) {
            CreateEntityFromEntity(E_EXPLOSION, self, entity);
            entity->params = 1;
        }
        DestroyEntity(self);
        return;
    }

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitSlograProjectileNP3);
        if (self->facingLeft) {
            self->velocityX = FIX(4);
        } else {
            self->velocityX = FIX(-4);
        }

    case 1:
        if (AnimateEntity(anim16, self) == 0) {
            SetStep(2);
        }
        break;

    case 2:
        MoveEntity();
        AnimateEntity(anim17, self);
        break;
    }
}
