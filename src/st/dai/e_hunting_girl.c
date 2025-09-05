// SPDX-License-Identifier: AGPL-3.0-or-later
#include "dai.h"

typedef struct {
    s16 x;
    s16 y;
    s16 rotate;
    s16 frames;
} huntingGirlAttackStep;

static u8 anim[] = {1, 1, 1, 2};
static u8 unused[] = {0, 0, 0, 0, 0, 0, 46, 0, 4, 0, 0, 0};
static s16 sensors[] = {0, 46, 0, 4, 4, -4, -8, 0};
#ifdef VERSION_PSP
static s8 fade_interval[] = {8, 4, 3, 12, 8, 4, 0, 0};
#else
static u8 fade_interval[] = {8, 4, 3, 12, 8, 4, 0, 0};
#endif
// u, v, width, height, offxetX, offsetY
static s16 params[][6] = {
    {48, 0, 31, 79, -5, -32},
    {80, 0, 31, 79, -18, -38},
    {0, 0, 47, 55, -32, -16},
    {0, 56, 47, 71, -24, -8},
    {48, 80, 55, 47, -44, -44}};
static huntingGirlAttackStep attack_pattern_1[] = {
    {6, -1, ROT(22.5), 16}, {6, 1, ROT(28.125), 16}, {0xFFF, 0, 0, 0}};
static huntingGirlAttackStep attack_pattern_2[] = {
    {-5, -1, ROT(33.75), 16}, {-5, 1, ROT(39.375), 16}, {0xFFF, 0, 0, 0}};
static huntingGirlAttackStep attack_pattern_3[] = {
    {-16, 8, ROT(90), 8}, {0, 0, ROT(90), 16}, {0x7FFF, 0, 0, 0}};
static huntingGirlAttackStep attack_pattern_4[] = {
    {-10, 5, ROT(33.75), 16}, {0x7FFF, 0, 0, 0}};
static huntingGirlAttackStep attack_pattern_5[] = {
    {-12, 0, ROT(90), 16},       {44, 0, ROT(90), 8},
    {-44, -16, ROT(61.875), 12}, {44, 16, ROT(61.875), 8},
    {-44, 16, ROT(118.125), 12}, {44, -20, ROT(118.125), 8},
    {-44, 0, ROT(78.75), 16},    {0x7FFF, 0, 0, 0}};
static huntingGirlAttackStep attack_pattern_6[] = {
    {-8, 0, ROT(90), 8}, {40, 0, ROT(90), 8},   {-4, -4, ROT(135), 8},
    {0, 8, ROT(45), 8},  {-32, -4, ROT(90), 8}, {64, 0, ROT(90), 8},
    {0x7FFF, 0, 0, 0}};
static huntingGirlAttackStep attack_pattern_7[] = {
    {-8, -8, ROT(135), 8}, {24, 8, ROT(39.375), 8}, {-52, -16, 0x0400, 8},
    {36, 0, ROT(90), 8},   {-16, 20, ROT(45), 8},   {7, -12, ROT(135), 8},
    {0x7FFF, 0, 0, 0}};
static huntingGirlAttackStep* attack_pattern_ptr[] = {
    attack_pattern_7, attack_pattern_5, attack_pattern_6};

static bool HuntingGirlAttack(huntingGirlAttackStep* arg0) {
    Primitive* prim;
    s32 velocityX;
    s32 velocityY;
    s32 angle;
    s32 frames;
    s32 tempY;
    s32 tempX;
    s16 rotation;

    arg0 = &arg0[g_CurrentEntity->ext.huntingGirl.attackStep];
    if (!g_CurrentEntity->ext.huntingGirl.frames) {
        if (arg0->x == 0x7FFF) {
            return true;
        }
        frames = g_CurrentEntity->ext.huntingGirl.frames = arg0->frames;
        tempX = arg0->x;
        if (!g_CurrentEntity->facingLeft) {
            tempX = -tempX;
        }
        tempX <<= 16;

// It seems like there should be a way to coalesce these two
#ifdef VERSION_PSP
        if (frames) {
            velocityX = tempX / frames;
        } else {
            velocityX = 0;
        }
        g_CurrentEntity->velocityX = velocityX;
        tempY = arg0->y;
        tempY <<= 16;
        if (frames) {
            velocityY = tempY / frames;
        } else {
            velocityY = 0;
        }
        g_CurrentEntity->velocityY = velocityY;
        rotation = arg0->rotate - g_CurrentEntity->rotate;
        if (rotation > FLT(0.5)) {
            rotation = rotation - FLT(1);
        }
        if (rotation < FLT(-0.5)) {
            rotation = rotation + FLT(1);
        }
        if (frames) {
            angle = rotation / frames;
        } else {
            angle = 0;
        }
#else
        velocityX = tempX / frames;
        g_CurrentEntity->velocityX = velocityX;
        tempY = arg0->y;
        tempY <<= 16;
        velocityY = tempY / frames;
        g_CurrentEntity->velocityY = velocityY;
        rotation = arg0->rotate - g_CurrentEntity->rotate;
        if (rotation > ROT(180)) {
            rotation -= ROT(360);
        }
        if (rotation < ROT(-180)) {
            rotation += ROT(360);
        }
        angle = rotation / frames;
#endif
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
        arg0++;
        prim = g_CurrentEntity->ext.huntingGirl.attackPrim;
#ifdef VERSION_PSP
        if (!prim) {
            return false;
        }
#endif
        prim->p3 = 2;
        prim = prim->next;
        g_CurrentEntity->ext.huntingGirl.attackPrim = prim;
        if (arg0->x == 0xFFF) {
            g_CurrentEntity->ext.huntingGirl.attackStep = 0;
            return true;
        }
    }
    return false;
}

static bool HuntingGirlPrimHelper(s32 paramIdx, s32 type) {
    u8 brightness;
    s16* paramsPtr;
    Primitive* prim;

    prim = g_CurrentEntity->ext.huntingGirl.prim;
    paramsPtr = params[paramIdx];
    if (g_CurrentEntity->facingLeft) {
        prim->x0 = prim->x2 = g_CurrentEntity->posX.i.hi - paramsPtr[4];
        prim->x1 = prim->x3 = prim->x0 - paramsPtr[2];
    } else {
        prim->x0 = prim->x2 = g_CurrentEntity->posX.i.hi + paramsPtr[4];
        prim->x1 = prim->x3 = prim->x0 + paramsPtr[2];
    }
    prim->y0 = prim->y1 = g_CurrentEntity->posY.i.hi + paramsPtr[5];
    prim->y2 = prim->y3 = prim->y0 + paramsPtr[3];
    switch (type) {
    case 0:
        prim->clut = PAL_HUNTING_GIRL;
        prim->u0 = prim->u2 = paramsPtr[0];
        prim->u1 = prim->u3 = paramsPtr[0] + paramsPtr[2];
        prim->v0 = prim->v1 = paramsPtr[1];
        prim->v2 = prim->v3 = paramsPtr[1] + paramsPtr[3];
        prim->priority = g_CurrentEntity->zPriority + 1;
        prim->drawMode = DRAW_HIDE | DRAW_UNK02;
        g_CurrentEntity->ext.huntingGirl.brightness = 0;
        break;
    case 1:
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
    case 2:
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

static void HuntingGirlSetNextStep(s32 step) {
    g_CurrentEntity->ext.huntingGirl.attackStep = 0;
    g_CurrentEntity->ext.huntingGirl.frames = 0;
    g_CurrentEntity->ext.huntingGirl.nextStep = step;
    SetStep(6);
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

    if ((self->hitFlags & 3) && (self->step != 8)) {
        self->ext.huntingGirl.attacking = false;
        SetStep(8);
    }
    if ((self->flags & FLAG_DEAD) && (self->step < 9)) {
        SetStep(9);
    }
    switch (self->step) {
    case 0:
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
            CreateEntityFromCurrentEntity(E_HUNTING_GIRL_SPIRIT, entity);
            entity->params = count + 1;
        }
        self->ext.huntingGirl.cycleTimer = 512;
        break;
    case 1:
        if (UnkCollisionFunc3(sensors) & 1) {
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
            self->ext.huntingGirl.scrollY =
                self->posY.i.hi + g_Tilemap.scrollY.i.hi;
            HuntingGirlSetNextStep(2);
        }
        break;
    case 2:
        switch (self->step_s) {
        case 0:
            HuntingGirlPrimHelper(0, 0);
            self->step_s++;
            // fallthrough
        case 1:
            HuntingGirlPrimHelper(0, 1);
            if (GetDistanceToPlayerX() < 80 && GetDistanceToPlayerY() < 48) {
                self->step_s++;
            }
            break;
        case 2:
            if (HuntingGirlPrimHelper(0, 2)) {
                HuntingGirlSetNextStep(3);
            }
            break;
        }
        break;
    case 4:
        switch (self->step_s) {
        case 0:
            HuntingGirlPrimHelper(1, 0);
            self->ext.huntingGirl.attackTimer = 48;
            self->step_s++;
            // fallthrough
        case 1:
            HuntingGirlAttack(attack_pattern_4);
            HuntingGirlPrimHelper(1, 1);
            if (!--self->ext.huntingGirl.attackTimer) {
                self->step_s++;
            }
            if (GetDistanceToPlayerX() < 64) {
                HuntingGirlSetNextStep(5);
            }
            break;
        case 2:
            if (HuntingGirlPrimHelper(1, 2)) {
                HuntingGirlSetNextStep(3);
            }
            break;
        }
        break;
    case 3:
        if (!self->step_s) {
            self->ext.huntingGirl.attackTimer = 64;
            self->step_s++;
        }
        HuntingGirlAttack(attack_pattern_1);
        if (GetDistanceToPlayerX() > 80) {
            self->ext.huntingGirl.cycleTimer--;
        }
        if (!self->ext.huntingGirl.cycleTimer) {
            self->ext.huntingGirl.cycleTimer = 512;
            HuntingGirlSetNextStep(4);
        }
        if (((GetSideToPlayer() & 1) ^ 1) != self->facingLeft) {
            HuntingGirlSetNextStep(5);
        }
        if (!self->ext.huntingGirl.attackTimer) {
            if (GetDistanceToPlayerX() < 80) {
                HuntingGirlSetNextStep(5);
            }
        } else {
            self->ext.huntingGirl.attackTimer--;
            if (GetDistanceToPlayerX() < 56) {
                HuntingGirlSetNextStep(7);
            }
        }
        break;
    case 7:
        if (!self->step_s) {
            self->ext.huntingGirl.attackTimer = 16;
            self->step_s++;
        }
        HuntingGirlAttack(attack_pattern_2);
        if (GetDistanceToPlayerX() > 80) {
            self->ext.huntingGirl.cycleTimer--;
        }
        if (!self->ext.huntingGirl.cycleTimer) {
            self->ext.huntingGirl.cycleTimer = 512;
            HuntingGirlSetNextStep(4);
        }
        if (GetDistanceToPlayerX() > 96) {
            HuntingGirlSetNextStep(3);
        }
        if (((GetSideToPlayer() & 1) ^ 1) != self->facingLeft) {
            HuntingGirlSetNextStep(5);
        }
        if (!self->ext.huntingGirl.attackTimer) {
            if (GetDistanceToPlayerX() < 80) {
                HuntingGirlSetNextStep(5);
            }
        } else {
            self->ext.huntingGirl.attackTimer--;
        }
        break;
    case 5:
        switch (self->step_s) {
        case 0:
            HuntingGirlPrimHelper(2, 0);
            self->step_s++;
            // fallthrough
        case 1:
            HuntingGirlPrimHelper(2, 1);
            if (HuntingGirlAttack(attack_pattern_3)) {
                self->step_s++;
            }
            break;
        case 2:
            if (HuntingGirlPrimHelper(2, 2)) {
                self->ext.huntingGirl.attacking = true;
                self->ext.huntingGirl.attackPrim =
                    self->ext.huntingGirl.spiritPrim;
                self->ext.huntingGirl.attackStep = 0;
                self->ext.huntingGirl.frames = 0;
                PlaySfxPositional(SFX_UNK_72A);
                self->step_s++;
            }
            break;
        case 3:
            if (HuntingGirlAttack(attack_pattern_ptr[self->ext.huntingGirl
                                                         .attackPatternIdx])) {
                self->ext.huntingGirl.attacking = false;
                self->ext.huntingGirl.attackPatternIdx++;
                if ((self->ext.huntingGirl.attackPatternIdx) > 2) {
                    self->ext.huntingGirl.attackPatternIdx = 0;
                }
                HuntingGirlSetNextStep(3);
            }
            break;
        }
        break;
    case 6:
        switch (self->step_s) {
        case 0:
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
        case 1:
            tempVar = (GetSideToPlayer() & 1) ^ 1;
            if (tempVar != self->facingLeft) {
                self->rotate = -self->rotate;
            }
            self->facingLeft = tempVar;
            SetStep(self->ext.huntingGirl.nextStep);
            break;
        }
        break;
    case 8:
        switch (self->step_s) {
        case 0:
            tempVar = Random() & 1;
            self->ext.huntingGirl.random = tempVar;
            HuntingGirlPrimHelper((self->ext.huntingGirl.random) + 3, 0);
            if (GetSideToPlayer() & 1) {
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
        case 1:
            HuntingGirlPrimHelper((self->ext.huntingGirl.random) + 3, 1);
            MoveEntity();
            self->velocityX -= self->velocityX / 32;
            self->velocityY += FIX(0.125);
            if (self->velocityY > FIX(2.0)) {
                self->step_s++;
            }
            break;
        case 2:
            if (HuntingGirlPrimHelper(self->ext.huntingGirl.random + 3, 2)) {
                HuntingGirlSetNextStep(4);
            }
            break;
        }
        break;
    case 9:
        switch (self->step_s) {
        case 0:
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
            HuntingGirlPrimHelper((self->ext.huntingGirl.random) + 3, 0);
            self->velocityX = 0;
            self->velocityY = FIX(-3.0);
            PlaySfxPositional(SFX_UNK_72C);
            self->step_s++;
            // fallthrough
        case 1:
            HuntingGirlPrimHelper((self->ext.huntingGirl.random) + 3, 1);
            MoveEntity();
            self->velocityY += FIX(0.125);
            if (self->velocityY > 0) {
                self->step_s++;
            }
            break;
        case 2:
            if (HuntingGirlPrimHelper(self->ext.huntingGirl.random + 3, 2)) {
                self->flags |= FLAG_DESTROY_IF_OUT_OF_CAMERA;
                self->step_s++;
            }
            break;
        case 3:
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

void EntityHuntingGirlSpirit(Entity* self) {
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
