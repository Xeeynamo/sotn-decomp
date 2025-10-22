// SPDX-License-Identifier: AGPL-3.0-or-later
#include "dai.h"

// HuntingGirlDrawAttack has conditions that can be expected to attempt to
// divide by 0, therefore psp uses a division guard.
#ifdef VERSION_PSP
#define DIV_GUARD(q, a, b)                                                     \
    if (b) {                                                                   \
        q = a / b;                                                             \
    } else {                                                                   \
        q = 0;                                                                 \
    }
#else
#define DIV_GUARD(q, a, b) q = a / b;
#endif

#define END_ATTACK 0xFFF
#define HALT_ATTACK 0x7FFF
// This is the reason for the div guard
// The 0xFFF terminator is checked for after the division, so the 0's in this
// group would cause a div by 0 error
#define ATTACK_END {0xFFF, 0, 0, 0}
#define ATTACK_HALT {0x7FFF, 0, 0, 0}

enum HuntingGirlSteps {
    HUNTING_GIRL_INIT,
    HUNTING_GIRL_READY,
    HUNTING_GIRL_IDLE,
    HUNTING_GIRL_PREPARE_ATTACK,
    HUNTING_GIRL_RECOVER,
    HUNTING_GIRL_ATTACK,
    HUNTING_GIRL_TRANSITION,
    HUNTING_GIRL_RETURN_TO_READY,
    HUNTING_GIRL_HIT,
    HUNTING_GIRL_DEATH,
};

enum HuntingGirlSubsteps {
    HUNTING_GIRL_IDLE_INIT,
    HUNTING_GIRL_IDLE_PULSE,
    HUNTING_GIRL_IDLE_FADE,
};
enum HuntingGirlRecoverSubsteps {

    HUNTING_GIRL_RECOVER_INIT,
    HUNTING_GIRL_RECOVER_FADE_IN,
    HUNTING_GIRL_RECOVER_FADE_OUT,
};
enum HuntingGirlAttackSubsteps {
    HUNTING_GIRL_ATTACK_INIT,
    HUNTING_GIRL_ATTACK_FADE_IN,
    HUNTING_GIRL_ATTACK_FADE_OUT,
    HUNTING_GIRL_ATTACK_DRAW,
};
enum HuntingGirlTransitionSubsteps {
    HUNTING_GIRL_TRANSITION_POS,
    HUNTING_GIRL_TRANSITION_TURN,
};

enum HuntingGirlHitSubsteps {
    HUNTING_GIRL_HIT_INIT,
    HUNTING_GIRL_HIT_KNOCKBACK,
    HUNTING_GIRL_HIT_FADE,
};
enum HuntingGirlDeathSubsteps {
    HUNTING_GIRL_DEATH_INIT,
    HUNTING_GIRL_DEATH_KNOCKBACK,
    HUNTING_GIRL_DEATH_FADE,
    HUNTING_GIRL_DEATH_EXPLODE,
};

enum SpiritSteps {
    SPIRIT_IDLE,
    SPIRIT_RECOVER,
    SPIRIT_ATTACK,
};
enum SpiritSubSteps {
    SPIRIT_INIT,
    SPIRIT_PULSE,
    SPIRIT_FADE,
};

typedef struct {
    s16 x;
    s16 y;
    s16 rotate;
    s16 frames;
} HuntingGirlAttackStep;

typedef struct {
    s16 u;
    s16 v;
    s16 width;
    s16 height;
    s16 offsetX;
    s16 offsetY;
} HuntingGirlSpiritParams;

static AnimateEntityFrame anim[] = {{1, 1}, {1, 2}};
static u8 unused[] = {0, 0, 0, 0, 0, 0, 46, 0, 4, 0, 0, 0};
static s16 sensors[] = {0, 46, 0, 4, 4, -4, -8, 0};
#ifdef VERSION_PSP
static s8 fade_interval[] = {8, 4, 3, 12, 8, 4, 0, 0};
#else
static u8 fade_interval[] = {8, 4, 3, 12, 8, 4, 0, 0};
#endif
static HuntingGirlSpiritParams spirit_params[] = {
    {48, 0, 31, 79, -5, -32},
    {80, 0, 31, 79, -18, -38},
    {0, 0, 47, 55, -32, -16},
    {0, 56, 47, 71, -24, -8},
    {48, 80, 55, 47, -44, -44}};
static HuntingGirlAttackStep attack_pattern_1[] = {
    {6, -1, ROT(22.5), 16}, {6, 1, ROT(28.125), 16}, ATTACK_END};
static HuntingGirlAttackStep attack_pattern_2[] = {
    {-5, -1, ROT(33.75), 16}, {-5, 1, ROT(39.375), 16}, ATTACK_END};
static HuntingGirlAttackStep attack_pattern_3[] = {
    {-16, 8, ROT(90), 8}, {0, 0, ROT(90), 16}, ATTACK_HALT};
static HuntingGirlAttackStep attack_pattern_4[] = {
    {-10, 5, ROT(33.75), 16}, ATTACK_HALT};
static HuntingGirlAttackStep attack_pattern_5[] = {
    {-12, 0, ROT(90), 16},       {44, 0, ROT(90), 8},
    {-44, -16, ROT(61.875), 12}, {44, 16, ROT(61.875), 8},
    {-44, 16, ROT(118.125), 12}, {44, -20, ROT(118.125), 8},
    {-44, 0, ROT(78.75), 16},    ATTACK_HALT};
static HuntingGirlAttackStep attack_pattern_6[] = {
    {-8, 0, ROT(90), 8}, {40, 0, ROT(90), 8},   {-4, -4, ROT(135), 8},
    {0, 8, ROT(45), 8},  {-32, -4, ROT(90), 8}, {64, 0, ROT(90), 8},
    ATTACK_HALT};
static HuntingGirlAttackStep attack_pattern_7[] = {
    {-8, -8, ROT(135), 8},
    {24, 8, ROT(39.375), 8},
    {-52, -16, 0x0400, 8},
    {36, 0, ROT(90), 8},
    {-16, 20, ROT(45), 8},
    {7, -12, ROT(135), 8},
    ATTACK_HALT};
static HuntingGirlAttackStep* attack_pattern_ptr[] = {
    attack_pattern_7, attack_pattern_5, attack_pattern_6};

static bool HuntingGirlDrawAttack(HuntingGirlAttackStep* attackPattern) {
    Primitive* prim;
    s32 velocityX;
    s32 velocityY;
    s32 angle;
    s32 frames;
    s32 tempY;
    s32 tempX;
    s16 rotation;

    attackPattern = &attackPattern[g_CurrentEntity->ext.huntingGirl.attackStep];
    if (!g_CurrentEntity->ext.huntingGirl.frames) {
        if (attackPattern->x == HALT_ATTACK) {
            return true;
        }
        frames = g_CurrentEntity->ext.huntingGirl.frames =
            attackPattern->frames;
        tempX = attackPattern->x;
        if (!g_CurrentEntity->facingLeft) {
            tempX = -tempX;
        }
        tempX <<= 16;

        DIV_GUARD(velocityX, tempX, frames)
        g_CurrentEntity->velocityX = velocityX;
        tempY = attackPattern->y;
        tempY <<= 16;
        DIV_GUARD(velocityY, tempY, frames)
        g_CurrentEntity->velocityY = velocityY;
        rotation = attackPattern->rotate - g_CurrentEntity->rotate;
        if (rotation > ROT(180)) {
            // pspeu doesn't like rotation -= ROT(360);
            rotation = rotation - ROT(360);
        }
        if (rotation < ROT(-180)) {
            // pspeu doesn't like rotation += ROT(360);
            rotation = rotation + ROT(360);
        }
        DIV_GUARD(angle, rotation, frames)
        rotation = angle;
        g_CurrentEntity->ext.huntingGirl.rotate = rotation;
        if (g_CurrentEntity->ext.huntingGirl.attacking) {
            PlaySfxPositional(SFX_ANIME_SWORD_B);
            prim = g_CurrentEntity->ext.huntingGirl.attackPrim;
            prim->p3 = 8;
            prim->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS |
                             DRAW_UNK02 | DRAW_TRANSP;
            rotation = g_CurrentEntity->rotate;
            if (g_CurrentEntity->facingLeft) {
                rotation = -rotation;
            }
            tempX = g_CurrentEntity->posX.i.hi;
            tempY = g_CurrentEntity->posY.i.hi;
            tempX += ((rsin(rotation) * -48) >> 12);
            tempY += ((rcos(rotation) * 48) >> 12);
            prim->x0 = prim->x1 = tempX;
            prim->y0 = prim->y1 = tempY;
            prim->r0 = 192;
            prim->g0 = 64;
            prim->b0 = 128;
            prim->r1 = 192;
            prim->g1 = 64;
            prim->b1 = 128;
        } else {
            g_CurrentEntity->ext.huntingGirl.attackPrim = 0;
        }
    }
    g_CurrentEntity->posX.val += g_CurrentEntity->velocityX;
    g_CurrentEntity->posY.val += g_CurrentEntity->velocityY;
    g_CurrentEntity->rotate += g_CurrentEntity->ext.huntingGirl.rotate;
    prim = g_CurrentEntity->ext.huntingGirl.attackPrim;
    if (prim) {
        rotation = g_CurrentEntity->rotate;
        if (g_CurrentEntity->facingLeft) {
            rotation = -rotation;
        }
        tempX = g_CurrentEntity->posX.i.hi;
        tempY = g_CurrentEntity->posY.i.hi;
        tempX += ((rsin(rotation) * -48) >> 12);
        tempY += ((rcos(rotation) * 48) >> 12);
        prim->x0 = tempX;
        prim->y0 = tempY;
        prim->drawMode =
            DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS | DRAW_UNK02 | DRAW_TRANSP;
    }
    if (!--g_CurrentEntity->ext.huntingGirl.frames) {
        g_CurrentEntity->ext.huntingGirl.attackStep++;
        attackPattern++;
        prim = g_CurrentEntity->ext.huntingGirl.attackPrim;
#ifdef VERSION_PSP
        if (!prim) {
            return false;
        }
#endif
        prim->p3 = 2;
        prim = prim->next;
        g_CurrentEntity->ext.huntingGirl.attackPrim = prim;
        if (attackPattern->x == END_ATTACK) {
            g_CurrentEntity->ext.huntingGirl.attackStep = 0;
            return true;
        }
    }
    return false;
}

static bool HuntingGirlDrawSpirit(s32 spiritStep, s32 spiritSubStep) {
    u8 brightness;
    HuntingGirlSpiritParams* step_params;
    Primitive* prim;

    prim = g_CurrentEntity->ext.huntingGirl.prim;
    step_params = &spirit_params[spiritStep];
    if (g_CurrentEntity->facingLeft) {
        prim->x0 = prim->x2 = g_CurrentEntity->posX.i.hi - step_params->offsetX;
        prim->x1 = prim->x3 = prim->x0 - step_params->width;
    } else {
        prim->x0 = prim->x2 = g_CurrentEntity->posX.i.hi + step_params->offsetX;
        prim->x1 = prim->x3 = prim->x0 + step_params->width;
    }
    prim->y0 = prim->y1 = g_CurrentEntity->posY.i.hi + step_params->offsetY;
    prim->y2 = prim->y3 = prim->y0 + step_params->height;
    switch (spiritSubStep) {
    case SPIRIT_INIT:
        prim->clut = PAL_HUNTING_GIRL;
        prim->u0 = prim->u2 = step_params->u;
        prim->u1 = prim->u3 = step_params->u + step_params->width;
        prim->v0 = prim->v1 = step_params->v;
        prim->v2 = prim->v3 = step_params->v + step_params->height;
        prim->priority = g_CurrentEntity->zPriority + 1;
        prim->drawMode = DRAW_HIDE | DRAW_UNK02;
        g_CurrentEntity->ext.huntingGirl.brightness = 0;
        break;
    case SPIRIT_PULSE:
        brightness = (g_CurrentEntity->ext.huntingGirl.brightness *
                      abs(rsin(g_CurrentEntity->ext.huntingGirl.sinePhase))) >>
                     12;
        PGREY(prim, 0) = brightness;
        LOW(prim->r1) = LOW(prim->r0);
        LOW(prim->r2) = LOW(prim->r0);
        LOW(prim->r3) = LOW(prim->r0);
        prim->drawMode =
            DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS | DRAW_UNK02 | DRAW_TRANSP;
        if ((g_CurrentEntity->ext.huntingGirl.brightness) < 128) {
            g_CurrentEntity->ext.huntingGirl.brightness += 16;
        }
        g_CurrentEntity->ext.huntingGirl.sinePhase += 64;
        break;
    case SPIRIT_FADE:
        prim->drawMode =
            DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS | DRAW_UNK02 | DRAW_TRANSP;
        if (!PrimDecreaseBrightness(prim, 7)) {
            prim->drawMode = DRAW_HIDE;
            return true;
        }
        break;
    }
    return false;
}

static void HuntingGirlTransitionToStep(s32 step) {
    g_CurrentEntity->ext.huntingGirl.attackStep = 0;
    g_CurrentEntity->ext.huntingGirl.frames = NULL;
    g_CurrentEntity->ext.huntingGirl.nextStep = step;
    SetStep(HUNTING_GIRL_TRANSITION);
}

void EntityHuntingGirl(Entity* self) {
    s32 primIndex;
    s32 offsetX, offsetY;
    s32 posX, posY;
    Primitive* tempPrim;
    s32 count;
    Entity* entity;
    s32 tempVar;
    u8* colorPtr;
    Primitive* prim;
    s32 tempColor;
    s32 color;
    s16 rotate;

    if ((self->hitFlags & 3) && (self->step != HUNTING_GIRL_HIT)) {
        self->ext.huntingGirl.attacking = false;
        SetStep(HUNTING_GIRL_HIT);
    }
    if ((self->flags & FLAG_DEAD) && (self->step < HUNTING_GIRL_DEATH)) {
        SetStep(HUNTING_GIRL_DEATH);
    }
    switch (self->step) {
    case HUNTING_GIRL_INIT:
        InitializeEntity(g_EInitHuntingGirl);
        self->hitboxWidth = self->hitboxHeight = 10;
        self->hitboxState = 2;
        self->zPriority = 176;
        self->drawFlags = FLAG_DRAW_ROTATE;
        self->rotate = 0;
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 32);
        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags |= FLAG_HAS_PRIMS;
        self->primIndex = primIndex;
        prim = &g_PrimBuf[primIndex];
        self->ext.huntingGirl.prim = prim;
        prim->tpage = 21;
        prim->clut = PAL_HUNTING_GIRL;
        prim->priority = self->zPriority;
        prim->priority = self->zPriority;
        prim->drawMode = DRAW_HIDE;
        prim = prim->next;
        self->ext.huntingGirl.spiritPrim = prim;
        self->ext.huntingGirl.attackPrim = prim;
        for (; prim != NULL; prim = prim->next) {
            prim->type = PRIM_LINE_G2;
            prim->p3 = 0;
            prim->priority = self->zPriority + 1;
            prim->drawMode = DRAW_HIDE;
        }
        entity = self + 1;
        for (count = 0; count < 3; count++, entity++) {
            CreateEntityFromCurrentEntity(E_HUNTING_GIRL_ATTACK, entity);
            entity->params = count + 1;
        }
        self->ext.huntingGirl.cycleTimer = 512;
        break;
    case HUNTING_GIRL_READY:
        if (UnkCollisionFunc3(sensors) & 1) {
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
            self->ext.huntingGirl.scrollY =
                self->posY.i.hi + g_Tilemap.scrollY.i.hi;
            HuntingGirlTransitionToStep(HUNTING_GIRL_IDLE);
        }
        break;
    case HUNTING_GIRL_IDLE:
        switch (self->step_s) {
        case HUNTING_GIRL_IDLE_INIT:
            HuntingGirlDrawSpirit(SPIRIT_IDLE, SPIRIT_INIT);
            self->step_s++;
            // fallthrough
        case HUNTING_GIRL_IDLE_PULSE:
            HuntingGirlDrawSpirit(SPIRIT_IDLE, SPIRIT_PULSE);
            if (GetDistanceToPlayerX() < 80 && GetDistanceToPlayerY() < 48) {
                self->step_s++;
            }
            break;
        case HUNTING_GIRL_IDLE_FADE:
            if (HuntingGirlDrawSpirit(SPIRIT_IDLE, SPIRIT_FADE)) {
                HuntingGirlTransitionToStep(HUNTING_GIRL_PREPARE_ATTACK);
            }
            break;
        }
        break;
    case HUNTING_GIRL_RECOVER:
        switch (self->step_s) {
        case HUNTING_GIRL_RECOVER_INIT:
            HuntingGirlDrawSpirit(SPIRIT_RECOVER, SPIRIT_INIT);
            self->ext.huntingGirl.attackTimer = 48;
            self->step_s++;
            // fallthrough
        case HUNTING_GIRL_RECOVER_FADE_IN:
            HuntingGirlDrawAttack(attack_pattern_4);
            HuntingGirlDrawSpirit(SPIRIT_RECOVER, SPIRIT_PULSE);
            if (!--self->ext.huntingGirl.attackTimer) {
                self->step_s++;
            }
            if (GetDistanceToPlayerX() < 64) {
                HuntingGirlTransitionToStep(HUNTING_GIRL_ATTACK);
            }
            break;
        case HUNTING_GIRL_RECOVER_FADE_OUT:
            if (HuntingGirlDrawSpirit(SPIRIT_RECOVER, SPIRIT_FADE)) {
                HuntingGirlTransitionToStep(HUNTING_GIRL_PREPARE_ATTACK);
            }
            break;
        }
        break;
    case HUNTING_GIRL_PREPARE_ATTACK:
        if (!self->step_s) {
            self->ext.huntingGirl.attackTimer = 64;
            self->step_s++;
        }
        HuntingGirlDrawAttack(attack_pattern_1);
        if (GetDistanceToPlayerX() > 80) {
            self->ext.huntingGirl.cycleTimer--;
        }
        if (!self->ext.huntingGirl.cycleTimer) {
            self->ext.huntingGirl.cycleTimer = 512;
            HuntingGirlTransitionToStep(HUNTING_GIRL_RECOVER);
        }
        if (((GetSideToPlayer() & 1) ^ 1) != self->facingLeft) {
            HuntingGirlTransitionToStep(HUNTING_GIRL_ATTACK);
        }
        if (!self->ext.huntingGirl.attackTimer) {
            if (GetDistanceToPlayerX() < 80) {
                HuntingGirlTransitionToStep(HUNTING_GIRL_ATTACK);
            }
        } else {
            self->ext.huntingGirl.attackTimer--;
            if (GetDistanceToPlayerX() < 56) {
                HuntingGirlTransitionToStep(HUNTING_GIRL_RETURN_TO_READY);
            }
        }
        break;
    case HUNTING_GIRL_RETURN_TO_READY:
        if (!self->step_s) {
            self->ext.huntingGirl.attackTimer = 16;
            self->step_s++;
        }
        HuntingGirlDrawAttack(attack_pattern_2);
        if (GetDistanceToPlayerX() > 80) {
            self->ext.huntingGirl.cycleTimer--;
        }
        if (!self->ext.huntingGirl.cycleTimer) {
            self->ext.huntingGirl.cycleTimer = 512;
            HuntingGirlTransitionToStep(HUNTING_GIRL_RECOVER);
        }
        if (GetDistanceToPlayerX() > 96) {
            HuntingGirlTransitionToStep(HUNTING_GIRL_PREPARE_ATTACK);
        }
        if (((GetSideToPlayer() & 1) ^ 1) != self->facingLeft) {
            HuntingGirlTransitionToStep(HUNTING_GIRL_ATTACK);
        }
        if (!self->ext.huntingGirl.attackTimer) {
            if (GetDistanceToPlayerX() < 80) {
                HuntingGirlTransitionToStep(HUNTING_GIRL_ATTACK);
            }
        } else {
            self->ext.huntingGirl.attackTimer--;
        }
        break;
    case HUNTING_GIRL_ATTACK:
        switch (self->step_s) {
        case HUNTING_GIRL_ATTACK_INIT:
            HuntingGirlDrawSpirit(SPIRIT_ATTACK, SPIRIT_INIT);
            self->step_s++;
            // fallthrough
        case HUNTING_GIRL_ATTACK_FADE_IN:
            HuntingGirlDrawSpirit(SPIRIT_ATTACK, SPIRIT_PULSE);
            if (HuntingGirlDrawAttack(attack_pattern_3)) {
                self->step_s++;
            }
            break;
        case HUNTING_GIRL_ATTACK_FADE_OUT:
            if (HuntingGirlDrawSpirit(SPIRIT_ATTACK, SPIRIT_FADE)) {
                self->ext.huntingGirl.attacking = true;
                self->ext.huntingGirl.attackPrim =
                    self->ext.huntingGirl.spiritPrim;
                self->ext.huntingGirl.attackStep = 0;
                self->ext.huntingGirl.frames = NULL;
                PlaySfxPositional(SFX_UNK_72A);
                self->step_s++;
            }
            break;
        case HUNTING_GIRL_ATTACK_DRAW:
            if (HuntingGirlDrawAttack(
                    attack_pattern_ptr[self->ext.huntingGirl
                                           .attackPatternIdx])) {
                self->ext.huntingGirl.attacking = false;
                self->ext.huntingGirl.attackPatternIdx++;
                if ((self->ext.huntingGirl.attackPatternIdx) > 2) {
                    self->ext.huntingGirl.attackPatternIdx = 0;
                }
                HuntingGirlTransitionToStep(HUNTING_GIRL_PREPARE_ATTACK);
            }
            break;
        }
        break;
    case HUNTING_GIRL_TRANSITION:
        switch (self->step_s) {
        case HUNTING_GIRL_TRANSITION_POS:
            offsetY = self->posY.i.hi + g_Tilemap.scrollY.i.hi;
            if (g_Player.status & PLAYER_STATUS_BAT_FORM) {
                offsetY -= PLAYER.posY.i.hi + g_Tilemap.scrollY.i.hi;
            } else {
                offsetY -= self->ext.huntingGirl.scrollY;
            }
            if (!offsetY) {
                self->step_s++;
            } else if (offsetY > 0) {
                self->posY.i.hi--;
            } else {
                self->posY.i.hi++;
            }
            break;
        case HUNTING_GIRL_TRANSITION_TURN:
            tempVar = (GetSideToPlayer() & 1) ^ 1; // Player on right
            if (tempVar != self->facingLeft) {
                self->rotate = -self->rotate;
            }
            self->facingLeft = tempVar;
            SetStep(self->ext.huntingGirl.nextStep);
            break;
        }
        break;
    case HUNTING_GIRL_HIT:
        switch (self->step_s) {
        case HUNTING_GIRL_HIT_INIT:
            tempVar = Random() & 1;
            // hit and death spirit step
            self->ext.huntingGirl.random = tempVar;
            HuntingGirlDrawSpirit(
                self->ext.huntingGirl.random + 3, SPIRIT_INIT);
            if (GetSideToPlayer() & 1) { // Player on left
                self->velocityX = FIX(1.5);
            } else {
                self->velocityX = FIX(-1.5);
            }
            self->velocityY = FIX(-3.0);
            self->ext.huntingGirl.attacking = false;
            for (prim = self->ext.huntingGirl.spiritPrim; prim;
                 prim = prim->next) {
                prim->drawMode = DRAW_HIDE;
            }
            PlaySfxPositional(SFX_UNK_72B);
            self->step_s++;
            // fallthrough
        case HUNTING_GIRL_HIT_KNOCKBACK:
            HuntingGirlDrawSpirit(
                self->ext.huntingGirl.random + 3, SPIRIT_PULSE);
            MoveEntity();
            self->velocityX -= self->velocityX / 32;
            self->velocityY += FIX(0.125);
            if (self->velocityY > FIX(2.0)) {
                self->step_s++;
            }
            break;
        case HUNTING_GIRL_HIT_FADE:
            if (HuntingGirlDrawSpirit(
                    self->ext.huntingGirl.random + 3, SPIRIT_FADE)) {
                HuntingGirlTransitionToStep(HUNTING_GIRL_RECOVER);
            }
            break;
        }
        break;
    case HUNTING_GIRL_DEATH:
        switch (self->step_s) {
        case HUNTING_GIRL_DEATH_INIT:
            entity = self + 1;
            for (count = 0; count < 3; count++, entity++) {
                DestroyEntity(entity);
            }
            self->hitboxState = 0;
            self->ext.huntingGirl.attacking = false;
            for (prim = self->ext.huntingGirl.spiritPrim; prim;
                 prim = prim->next) {
                prim->drawMode = DRAW_HIDE;
            }
            tempVar = Random() & 1;
            self->ext.huntingGirl.random = tempVar;
            HuntingGirlDrawSpirit(
                self->ext.huntingGirl.random + 3, SPIRIT_INIT);
            self->velocityX = 0;
            self->velocityY = FIX(-3.0);
            PlaySfxPositional(SFX_UNK_72C);
            self->step_s++;
            // fallthrough
        case HUNTING_GIRL_DEATH_KNOCKBACK:
            HuntingGirlDrawSpirit(
                self->ext.huntingGirl.random + 3, SPIRIT_PULSE);
            MoveEntity();
            self->velocityY += FIX(0.125);
            if (self->velocityY > 0) {
                self->step_s++;
            }
            break;
        case HUNTING_GIRL_DEATH_FADE:
            if (HuntingGirlDrawSpirit(
                    self->ext.huntingGirl.random + 3, SPIRIT_FADE)) {
                self->flags |= FLAG_DESTROY_IF_OUT_OF_CAMERA;
                self->step_s++;
            }
            break;
        case HUNTING_GIRL_DEATH_EXPLODE:
            MoveEntity();
            self->velocityY += FIX(0.0625);
            if (!(g_Timer & 7)) {
                PlaySfxPositional(SFX_SMALL_FLAME_IGNITE);
                entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
                if (entity != NULL) {
                    CreateEntityFromEntity(E_INTENSE_EXPLOSION, self, entity);
                    rotate = self->rotate;
                    if (self->facingLeft) {
                        rotate = -rotate;
                    }
                    offsetX = (rsin(rotate) * -48) >> 12;
                    offsetY = (rcos(rotate) * 48) >> 12;
                    // Reuse of tempColor variable
                    tempColor = Random() & 3;
                    entity->posX.i.hi += (offsetX * tempColor) / 4;
                    entity->posY.i.hi += (offsetY * tempColor) / 4;
                }
            }
            break;
        }
        break;
    }
    AnimateEntity(anim, self);
    if (!(self->flags & FLAG_DEAD)) {
        posX = self->posX.i.hi;
        posY = self->posY.i.hi;
        rotate = self->rotate;
        if (self->facingLeft) {
            rotate = -rotate;
        }
        offsetX = (rsin(rotate) * -48) >> 12;
        offsetY = (rcos(rotate) * 48) >> 12;
        entity = self + 1;
        for (count = 1; count < 4; count++, entity++) {
            entity->posX.i.hi = posX + (offsetX * count) / 4;
            entity->posY.i.hi = posY + (offsetY * count) / 4;
        }
    }
    for (prim = self->ext.huntingGirl.spiritPrim; prim; prim = prim->next) {
        if (prim->p3 == 2) {
            tempPrim = prim->next;
            LOW(prim->r0) = LOW(prim->r1);
            prim->type = PRIM_NONE;
            colorPtr = &prim->r1;
            tempVar = 0;
            for (color = 0; color < 3; color++) {
                tempColor = colorPtr[color];
                tempColor -= fade_interval[color];
                if (tempColor < 0) {
                    tempColor = 0;
                } else {
                    tempVar = 1;
                }
                colorPtr[color] = tempColor;
            }
            if (!tempVar && !LOW(prim->r0)) {
                prim->drawMode = DRAW_HIDE;
                prim->p3 = 0;
            }
            prim->type = PRIM_LINE_G2;
        }
    }
}

void EntityHuntingGirlAttack(Entity* self) {
    Entity* entity;

    if (!self->step) {
        InitializeEntity(g_EInitHuntingGirl);
        self->hitboxWidth = self->hitboxHeight = 2;
        self->hitboxState = 1;
        self->ext.huntingGirl.attack = self->attack;
    }
    if (g_Player.status & (PLAYER_STATUS_WOLF_FORM | PLAYER_STATUS_BAT_FORM)) {
#ifdef VERSION_PSP
        self->attack = self->ext.huntingGirl.attack * 2;
#else
        self->attack = LOHU(self->ext.huntingGirl.attack) * 2;
#endif
    } else {
        self->attack = self->ext.huntingGirl.attack;
    }
    entity = self - self->params;
    if (entity->entityId != E_HUNTING_GIRL) {
        DestroyEntity(self);
    }
}
