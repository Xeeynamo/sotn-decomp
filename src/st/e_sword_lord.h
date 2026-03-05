// SPDX-License-Identifier: AGPL-3.0-or-later

extern EInit g_EInitSwordLord;
extern EInit g_EInitSwordLordAttack;

static u16 D_us_80182A80[] = {0, 30, 24, 0};
static s16 D_us_80182A88[] = {0, 30, 0, 4, 24, -4, -48, 0};
static u8 delays[] = {0x40, 0x50, 0x70, 0x90};

static u8 anim0[] = {15, 1, 10, 2, 10, 3, 13, 4, 10, 3, 10, 2, 0, 0};
static u8 anim1[] = {
    40, 1, 8,  5, 8,  6, 8,  7, 8,  8, 31, 7, 3, 9, 3, 10, 2, 11, 2,
    12, 8, 13, 8, 12, 8, 11, 8, 10, 8, 9,  8, 6, 8, 5, 8,  1, 0,  0};
static u8 anim2[] = {24, 1,  8,  5,  8,  6, 8,  7, 8,  14, 8,  15, 8,  16, 40,
                     17, 6,  18, 10, 19, 3, 20, 3, 17, 6,  21, 38, 22, 6,  17,
                     6,  15, 6,  14, 6,  7, 6,  6, 6,  5,  6,  1,  0,  0};
static u8 anim3[] = {40, 1, 4, 5, 4, 6, 4, 7, 4, 14, 7, 25, -1, 0};
static u8 anim4[] = {7, 26, 7, 27, 7, 28, 40, 29, -1, 0};
static u8 anim5[] = {36, 1, 4, 23, 11, 24, 6, 23, 6, 1, 0, 0};
static u8 anim6[] = {2, 36, 2, 37, 2, 38, 2, 39, 0, 0};

static s32 D_us_80182B34[] = {0x1000, 0x1000, 0x3A0, 0x700, 0x780, 0x580};
static Point16 explosionOffsets[] = {
    {23, -51}, {15, -18}, {-13, -10}, {0, 3}, {16, 22}, {-16, 22}};

static u8 func_us_801CF57C(u8 step, Primitive* prim) {
    switch (step) {
    case 0:
        UnkPolyFunc2(prim);
        prim->tpage = 0x1A;
        prim->clut = PAL_UNK_19D;
        prim->u0 = prim->u2 = 0;
        prim->u1 = prim->u3 = 0x3F;
        prim->v0 = prim->v1 = 0xC0;
        prim->v2 = prim->v3 = 0xFF;
        prim->next->x1 = g_CurrentEntity->posX.i.hi;
        prim->next->y0 = g_CurrentEntity->posY.i.hi;
        LOH(prim->next->r2) = 0x40;
        LOH(prim->next->b2) = 0x40;
        prim->next->b3 = 0x80;
        prim->p3 |= 0x10;
        prim->next->x2 = 0;
        prim->next->y2 = prim->next->x2;
        prim->priority = g_CurrentEntity->zPriority + 3;
        prim->drawMode =
            DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS | DRAW_UNK02 | DRAW_TRANSP;
        UnkPrimHelper(prim);
        PlaySfxPositional(SFX_NOISE_SWEEP_DOWN_A);
        step++;
        /* fallthrough */
    case 1:
        prim->next->x2 += 0x300;
        prim->next->y2 = prim->next->x2;
        if (prim->next->x2 > 0x1800) {
            prim->clut = PAL_UNK_19C;
            prim->next->b3 = 0x28;
            step++;
        }
        break;

    case 2:
        prim->next->x2 += 0x180;
        prim->next->y2 = prim->next->x2;
        if (prim->next->x2 > 0x2000) {
            prim->clut = PAL_UNK_19E;
            prim->u0 = prim->u2 = 0x40;
            prim->u1 = prim->u3 = 0x7F;
            prim->v0 = prim->v1 = 0xC0;
            prim->v2 = prim->v3 = 0xFF;
            prim->drawMode |= DRAW_UNK_400;
            prim->next->b3 = 0x40;
            step++;
        }
        break;

    case 3:
        prim->next->x2 += 0x40;
        if (prim->next->x2 > 0x2800) {
            step++;
        }
        /* fallthrough */
    case 4:
        prim->next->x2 += 0x40;
        prim->next->y2 = prim->next->x2;
        prim->next->b3 -= 1;
        if (!prim->next->b3) {
            step++;
        }
        break;
    }
    UnkPrimHelper(prim);
    return step;
}

void EntitySwordLord(Entity* self) {
    Collider collider;
    Entity* tempEntity;
    Primitive* prim;
    s16 posX, posY;
    s32 primIndex;
    u8 colRet;
    s32 i;
    s32 s8;
    s16 xDistance;

    if ((self->flags & FLAG_DEAD) && self->step < 6) {
        PlaySfxPositional(SFX_SWORD_LORD_DEATH);
        self->hitboxState = 0;
        (self + 1)->hitboxState = 0;
        self->pose = 0;
        self->poseTimer = 0;
        self->step_s = 0;
        self->step = 6;
        self->zPriority -= 1;
        self->ext.swordLord.unk84 = 0;
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 2);
        if (primIndex != -1) {
            self->flags |= FLAG_HAS_PRIMS;
            self->primIndex = primIndex;
            prim = &g_PrimBuf[primIndex];
            self->ext.swordLord.prim = prim;
            while (prim != NULL) {
                prim->drawMode = DRAW_HIDE;
                prim = prim->next;
            }
        } else {
            self->ext.swordLord.prim = NULL;
        }
    }
    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitSwordLord);
        self->facingLeft = GetSideToPlayer() & 1;
        tempEntity = self + 1;
        DestroyEntity(tempEntity);
        CreateEntityFromEntity(E_SWORD_LORD_ATTACK, self, tempEntity);
        break;

    case 1:
        if (UnkCollisionFunc3(D_us_80182A88) & 1) {
            self->step = 2;
        }
        break;

    case 2:
        AnimateEntity(anim5, self);
        self->facingLeft = GetSideToPlayer() & 1;
        if (GetDistanceToPlayerX() < 0x60) {
            self->poseTimer = 0;
            self->pose = 0;
            self->ext.swordLord.delay = delays[Random() & 3];
            self->step = 3;
            if (self->facingLeft) {
                self->velocityX = FIX(1.0);
            } else {
                self->velocityX = FIX(-1.0);
            }
        }
        break;

    case 3:
        AnimateEntity(anim0, self);
        colRet = UnkCollisionFunc2(D_us_80182A80);
        if (colRet & 0x60) {
            self->posX.val -= self->velocityX;
            self->velocityX = -self->velocityX;
        }
        xDistance = GetDistanceToPlayerX();
        if (xDistance > 0x60) {
            if (self->facingLeft) {
                self->velocityX = FIX(-1.0);
            } else {
                self->velocityX = FIX(1.0);
            }
        }
        if (xDistance < 0x40) {
            if (self->facingLeft) {
                self->velocityX = FIX(1.0);
            } else {
                self->velocityX = FIX(-1.0);
            }
        }
        if (self->ext.swordLord.timer++ > self->ext.swordLord.delay) {
            self->pose = 0;
            self->poseTimer = 0;
            self->ext.swordLord.timer = 0;
            self->velocityX = 0;
            if (Random() % 2) {
                self->step = 4;
            } else {
                self->ext.swordLord.unk7E = true;
                self->step = 5;
            }
        }
        break;

    case 4:
        colRet = UnkCollisionFunc2(D_us_80182A80);
        if (colRet & 0x60) {
            self->posX.val -= self->velocityX;
            self->velocityX = 0;
        }
        if (AnimateEntity(anim1, self) == 0) {
            self->pose = 0;
            self->poseTimer = 0;
            self->ext.swordLord.delay = delays[Random() & 3];
            if (self->facingLeft) {
                self->velocityX = FIX(1.0);
            } else {
                self->velocityX = FIX(-1.0);
            }
            self->ext.swordLord.unk7E = false;
            self->step_s = 0;
            self->step = 3;
        }
        if (self->animCurFrame == 9 && !self->step_s) {
            PlaySfxPositional(SFX_SWORD_LORD_SWIPE_ATTACK);
            PlaySfxPositional(SFX_WHIP_TWIRL_SWISH);
            if (self->facingLeft) {
                self->velocityX = FIX(-4.0);
            } else {
                self->velocityX = FIX(4.0);
            }
            self->step_s = 1;
        }
        if (self->animCurFrame == 13) {
            self->velocityX = 0;
            if (!self->ext.swordLord.unk7E) {
                if (self->facingLeft) {
                    EntityExplosionVariantsSpawner(self, 4, 1, -16, 30, 1, 4);
                    EntityExplosionVariantsSpawner(self, 4, 1, 16, 30, 1, 4);
                } else {
                    EntityExplosionVariantsSpawner(self, 4, 1, -16, 30, 1, -4);
                    EntityExplosionVariantsSpawner(self, 4, 1, 16, 30, 1, -4);
                }
                self->ext.swordLord.unk7E = true;
            }
        }
        break;

    case 5:
        colRet = UnkCollisionFunc2(D_us_80182A80);
        if (colRet & 0x60) {
            self->posX.val -= self->velocityX;
            self->velocityX = 0;
        }
        self->step_s ^= 1;
        if (AnimateEntity(anim2, self) == 0) {
            self->pose = 0;
            self->poseTimer = 0;
            self->ext.swordLord.delay = delays[Random() & 3];
            if (self->facingLeft) {
                self->velocityX = FIX(1.0);
            } else {
                self->velocityX = FIX(-1.0);
            }
            self->ext.swordLord.unk7E = false;
            self->step_s = 0;
            self->step = 3;
        }
        if (self->animCurFrame == 19 && self->step_s) {
            if (!self->poseTimer) {
                PlaySfxPositional(SFX_STOMP_HARD_E);
            }
            if (self->facingLeft) {
                EntityExplosionVariantsSpawner(self, 2, 1, 8, 30, 0, 4);
            } else {
                EntityExplosionVariantsSpawner(self, 2, 1, -8, 30, 0, -4);
            }
        }
        if (self->animCurFrame == 18) {
            if (self->facingLeft) {
                self->velocityX = FIX(-4.0);
            } else {
                self->velocityX = FIX(4.0);
            }
            self->ext.swordLord.unk7E = false;
        }
        if (self->animCurFrame == 17) {
            self->velocityX = 0;
            if (!self->ext.swordLord.unk7E) {
                if (self->facingLeft) {
                    EntityExplosionVariantsSpawner(self, 5, 3, -16, 30, 0, 4);
                    EntityExplosionVariantsSpawner(self, 5, 3, 16, 30, 0, 4);
                } else {
                    EntityExplosionVariantsSpawner(self, 5, 3, -16, 30, 0, -4);
                    EntityExplosionVariantsSpawner(self, 5, 3, 16, 30, 0, -4);
                }
                PlaySfxPositional(SFX_SWORD_LORD_STAB_ATTACK);
                PlaySfxPositional(SFX_WEAPON_SWISH_B);
                PlaySfxPositional(SFX_STOMP_HARD_D);
                self->ext.swordLord.unk7E = true;
            }
        }
        break;

    case 6:
        switch (self->step_s) {
        case 0:
            if ((Random() & 7) == 0) {
                tempEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
                if (tempEntity != NULL) {
                    CreateEntityFromEntity(
                        E_INTENSE_EXPLOSION, self, tempEntity);
                    tempEntity->posX.i.hi += 0x20 - (Random() & 0x2F);
                    tempEntity->posY.i.hi += 0x20 - (Random() & 0x3F);
                }
            }
            if (AnimateEntity(anim3, self) == 0) {
                tempEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
                if (tempEntity != NULL) {
                    CreateEntityFromEntity(E_EXPLOSION, self, tempEntity);
                    tempEntity->params = 3;
                    PlaySfxPositional(SFX_FAST_STUTTER_EXPLODE);
                }
                self->pose = 0;
                self->poseTimer = 0;
                self->step_s++;
            }
            break;

        case 1:
            if (self->animCurFrame == 29) {
                tempEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
                if (tempEntity != NULL) {
                    CreateEntityFromEntity(E_SWORD_LORD, self, tempEntity);
                    tempEntity->params = 0;
                    tempEntity->facingLeft = self->facingLeft;
                    tempEntity->step = 7;
                    tempEntity->flags |= FLAG_UNK_2000;
                }
                self->step_s++;
            }

        case 2:
            if (!self->poseTimer && self->pose == 1) {
                PlaySfxPositional(SFX_ANIME_SWORD_B);
            }
            if (AnimateEntity(anim4, self) == 0) {
                s8 = 0;
#ifdef STAGE_IS_NZ1
                tempEntity = AllocEntity(&g_Entities[160], &g_Entities[192]);
                if (tempEntity != NULL) {
                    CreateEntityFromEntity(E_VANDAL_SWORD, self, tempEntity);
                    tempEntity->facingLeft = self->facingLeft;
                    if (self->facingLeft) {
                        tempEntity->posX.i.hi += 14;
                    } else {
                        tempEntity->posX.i.hi -= 14;
                    }
                    tempEntity->posY.i.hi -= 22;
                    s8 = 1;
                }
#endif
                for (i = s8; i < 5; i++) {
                    tempEntity =
                        AllocEntity(&g_Entities[224], &g_Entities[256]);
                    if (tempEntity != NULL) {
                        CreateEntityFromEntity(E_SWORD_LORD, self, tempEntity);
                        tempEntity->params = i + 1;
                        tempEntity->facingLeft = self->facingLeft;
                        tempEntity->step = 7;
                        tempEntity->flags |= FLAG_UNK_2000;
                    }
                }
                self->animCurFrame = 0;
                self->ext.swordLord.timer = 0x30;
                self->step_s++;
            }
            break;

        case 3:
            if (!--self->ext.swordLord.timer) {
                PlaySfxPositional(SFX_SWORD_LORD_EXPLODE);
                DestroyEntity(self);
                return;
            }
            break;
        }
        if (self->step_s) {
            if (self->ext.swordLord.prim != NULL) {
                prim = self->ext.swordLord.prim;
                self->ext.swordLord.unk84 =
                    func_us_801CF57C(self->ext.swordLord.unk84, prim);
            }
        }
        break;

    case 7:
        InitializeEntity(g_EInitSwordLord);
        self->hitboxState = 0;
        self->animCurFrame = self->params + 30;
        self->flags |= FLAG_DESTROY_IF_OUT_OF_CAMERA |
                       FLAG_DESTROY_IF_BARELY_OUT_OF_CAMERA |
                       FLAG_UNK_00200000 | FLAG_UNK_2000;
        self->ext.swordLord.unk80 = D_us_80182B34[self->params];
        self->zPriority--;
        self->opacity = 0xA0;
        break;

    case 8:
        MoveEntity();
        self->velocityY += self->ext.swordLord.unk80;
        posX = self->posX.i.hi;
        posY = self->posY.i.hi;
        if (self->facingLeft) {
            posX += explosionOffsets[self->params].x;
        } else {
            posX -= explosionOffsets[self->params].x;
        }
        posY += explosionOffsets[self->params].y;
        g_api.CheckCollision(posX, posY, &collider, 0);
        if (self->params < 2) {
            if (collider.effects != EFFECT_NONE) {
                tempEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
                if (tempEntity != NULL) {
                    CreateEntityFromCurrentEntity(E_EXPLOSION, tempEntity);
                    tempEntity->params = 2;
                    tempEntity->posX.i.hi = posX;
                    tempEntity->posY.i.hi = posY;
                }
                DestroyEntity(self);
            }
        } else {
            if (collider.effects != EFFECT_NONE) {
                self->drawFlags |= ENTITY_OPACITY;
                self->step++;
            }
        }
        break;

    case 9:
        posX = self->posX.i.hi;
        posY = self->posY.i.hi;
        if (self->facingLeft) {
            posX += explosionOffsets[self->params].x;
        } else {
            posX -= explosionOffsets[self->params].x;
        }
        posY += explosionOffsets[self->params].y;
        if (Random() & 0xF) {
            tempEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (tempEntity != NULL) {
                CreateEntityFromCurrentEntity(E_EXPLOSION, tempEntity);
                tempEntity->params = 2;
                tempEntity->posX.i.hi = posX;
                tempEntity->posY.i.hi = posY;
            }
        }
        self->opacity -= 4;
        if (!self->opacity) {
            DestroyEntity(self);
        }
        break;

    case 16:
#include "pad2_anim_debug.h"
    }
}

static s8 hitboxes[][4] = {
    {0, 0, 0, 0},      {-47, 16, 28, 8},   {-47, 14, 28, 8},  {-47, 11, 28, 8},
    {-47, 10, 28, 8},  {-47, 13, 28, 8},   {-56, -3, 25, 4},  {-47, -24, 28, 8},
    {-47, -27, 28, 8}, {-35, -56, 16, 16}, {7, -62, 4, 32},   {41, -24, 16, 16},
    {48, -11, 28, 8},  {54, 5, 25, 4},     {-13, -53, 4, 23}, {17, -46, 16, 16},
    {38, -19, 20, 4},  {38, -29, 20, 4},   {38, -21, 20, 4},  {41, -10, 25, 4},
    {43, -9, 25, 4}};
static u8 hitboxOffsets[] = {
    0,  1,  2,  3,  4,  5,  6,  7,  8, 9, 10, 11, 12, 13, 14,
    15, 16, 16, 16, 17, 18, 19, 20, 1, 1, 14, 14, 14, 14, 14};

void EntitySwordLordAttack(Entity* self) {
    s32 animFrame;
    s8* hitboxPtr;
    Entity* swordLord;

    if (!self->step) {
        InitializeEntity(g_EInitSwordLordAttack);
    }
    swordLord = self - 1;
    animFrame = swordLord->animCurFrame;
    if (animFrame > LEN(hitboxOffsets) - 1) {
        animFrame = 0;
    }
    hitboxPtr = hitboxes[0];
    hitboxPtr += hitboxOffsets[animFrame] * 4;
    self->hitboxOffX = *hitboxPtr++;
    self->hitboxOffY = *hitboxPtr++;
    self->hitboxWidth = *hitboxPtr++;
    self->hitboxHeight = *hitboxPtr++;
    self->facingLeft = swordLord->facingLeft;
    self->posX.i.hi = swordLord->posX.i.hi;
    self->posY.i.hi = swordLord->posY.i.hi;
    if (swordLord->entityId != E_SWORD_LORD) {
        DestroyEntity(self);
    }
}
