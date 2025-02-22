// SPDX-License-Identifier: AGPL-3.0-or-later
#include "lib.h"

// Lesser demon start
INCLUDE_ASM("st/lib/nonmatchings/e_lesser_demon", func_us_801BB8DC);

u8 func_us_801BBAB4(void);
INCLUDE_ASM("st/lib/nonmatchings/e_lesser_demon", func_us_801BBAB4);

INCLUDE_ASM("st/lib/nonmatchings/e_lesser_demon", func_us_801BBEB0);

INCLUDE_ASM("st/lib/nonmatchings/e_lesser_demon", func_us_801BC28C);

INCLUDE_ASM("st/lib/nonmatchings/e_lesser_demon", func_us_801BC57C);

INCLUDE_ASM("st/lib/nonmatchings/e_lesser_demon", func_us_801BC814);

INCLUDE_ASM("st/lib/nonmatchings/e_lesser_demon", func_us_801BCC10);

INCLUDE_ASM("st/lib/nonmatchings/e_lesser_demon", func_us_801BCFD4);

extern s32 D_psp_092A5510;
extern s32 D_psp_092A5560;
extern s32 D_psp_092A55C0;

// Lesser Demon minion spawn?
// Seems like the vertical tractor beam effect that spawns
// Mudmen, Skeleton, Ectoplasm
void func_us_801BD268(void) {
    Entity* tempEntity;
    Primitive* prim;
    s32 primIndex;
    s32 entityId;
    s16 xOffset;

    FntPrint("eff_step %x\n", g_CurrentEntity->ext.et_801BDAE4.unk84);
    FntPrint("eff_timer %x\n", g_CurrentEntity->ext.et_801BDAE4.unk85);
    switch (g_CurrentEntity->ext.et_801BDAE4.unk84) {
    case 0:
        primIndex = g_api.AllocPrimitives(PRIM_G4, 0x1E);
        if (primIndex != -1) {
            g_CurrentEntity->flags |= FLAG_HAS_PRIMS;
            g_CurrentEntity->primIndex = primIndex;
            prim = &g_PrimBuf[primIndex];
            g_CurrentEntity->ext.et_801BDAE4.unk7C = prim;
            while (prim != NULL) {
                prim->priority = g_CurrentEntity->zPriority + 8;
                prim->drawMode = DRAW_HIDE;
                prim->p3 = 0;
                prim = prim->next;
            }
        } else {
            g_CurrentEntity->ext.et_801BDAE4.unk84 = 6;
        }
        g_CurrentEntity->ext.et_801BDAE4.unk84++;
        break;

    case 1:
        prim = g_CurrentEntity->ext.et_801BDAE4.unk7C;
        prim->p3 = 2;
        PGREY(prim, 0) = 0;
        PGREY(prim, 1) = 0;
        PGREY(prim, 2) = 0x60;
        PGREY(prim, 3) = 0x60;
        prim->r2 += 0x40;
        prim->r3 += 0x40;
        prim->y0 = 0x120;
        prim->y1 = 0x100;
        prim->y2 = 0x140;
        prim->y3 = 0x120;
        if (g_CurrentEntity->facingLeft) {
            xOffset = -8;
        } else {
            xOffset = 8;
        }
        prim->x0 = g_CurrentEntity->posX.i.hi - 1 + xOffset;
        prim->x1 = prim->x0 + 2;
        prim->x2 = prim->x0;
        prim->x3 = prim->x1;
        prim->v0 = 1;
        prim->priority = g_CurrentEntity->zPriority + 4;
        prim->drawMode =
            DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS | DRAW_UNK02 | DRAW_TRANSP;
        prim->u1 = 1;
        prim = prim->next;

        prim->p3 = 2;
        PGREY(prim, 0) = 0;
        PGREY(prim, 1) = 0;
        PGREY(prim, 2) = 0x60;
        PGREY(prim, 3) = 0x60;
        prim->r2 += 0x40;
        prim->r3 += 0x40;
        prim->x0 = g_CurrentEntity->posX.i.hi + 1 + xOffset;
        prim->x1 = prim->x0 - 2;
        prim->x2 = prim->x0;
        prim->x3 = prim->x1;
        prim->y0 = 0x140;
        prim->y1 = 0x120;
        prim->y2 = 0x160;
        prim->y3 = 0x140;
        prim->v0 = 1;
        prim->priority = g_CurrentEntity->zPriority - 2;
        prim->drawMode = DRAW_TPAGE | DRAW_COLORS | DRAW_UNK02 | DRAW_TRANSP;
        prim->u1 = 0;
        g_CurrentEntity->ext.et_801BDAE4.unk85 = 0x18;
        g_CurrentEntity->ext.et_801BDAE4.unk84 = 3;
        break;

    case 2:
        prim = g_CurrentEntity->ext.et_801BDAE4.unk7C;
        while (prim != NULL) {
            if (prim->p3) {
                func_us_801BCFD4(prim);
            }
            prim = prim->next;
        }
        prim = g_CurrentEntity->ext.et_801BDAE4.unk7C;
        while (prim != NULL) {
            if (g_CurrentEntity->ext.et_801BDAE4.unk80 % 2) {
                if (prim->u1) {
                    prim->x0--;
                    prim->x2 = prim->x0;
                    prim->x1++;
                    prim->x3 = prim->x1;
                } else {
                    prim->x0++;
                    prim->x2 = prim->x0;
                    prim->x1--;
                    prim->x3 = prim->x1;
                }
            }
            prim->y0 -= 8;
            prim->y1 -= 8;
            prim->y2 -= 8;
            prim->y3 -= 8;
            prim = prim->next;
        }
        if (g_CurrentEntity->ext.et_801BDAE4.unk80 % 2) {
            if (!--g_CurrentEntity->ext.et_801BDAE4.unk85) {
                g_CurrentEntity->ext.et_801BDAE4.unk84++;
                tempEntity = AllocEntity(&g_Entities[160], &g_Entities[192]);
                if (tempEntity != NULL) {
                    switch (Random() & 3) {
                    case 0:
                    case 1:
#ifdef VERSION_PSP
                        entityId = D_psp_092A5510;
#else
                        entityId = E_ID_4D;
#endif
                        break;

                    case 2:
#ifdef VERSION_PSP
                        entityId = D_psp_092A55C0;
#else
                        entityId = E_ID_37;
#endif
                        break;

                    case 3:
#ifdef VERSION_PSP
                        entityId = D_psp_092A5560;
#else
                        entityId = E_SKELETON;
#endif
                        break;
                    }
                    CreateEntityFromEntity(
                        entityId, g_CurrentEntity, tempEntity);
                    tempEntity->facingLeft = g_CurrentEntity->facingLeft;
                    if (g_CurrentEntity->facingLeft) {
                        tempEntity->posX.i.hi -= 8;
                    } else {
                        tempEntity->posX.i.hi += 8;
                    }
                    tempEntity->posY.i.hi += 0x30;
                    tempEntity->params = 0x10;
                }
            }
        }
        break;

    case 3:
        prim = g_CurrentEntity->ext.et_801BDAE4.unk7C;
        while (prim != NULL) {
            if (prim->p3) {
                func_us_801BCFD4(prim);
            }
            prim = prim->next;
        }
        prim = g_CurrentEntity->ext.et_801BDAE4.unk7C;
        while (prim != NULL) {
            prim->y0 -= 8;
            prim->y1 -= 8;
            prim->y2 -= 8;
            prim->y3 -= 8;
            prim = prim->next;
        }
        if (g_CurrentEntity->ext.et_801BDAE4.unk85) {
            if (!--g_CurrentEntity->ext.et_801BDAE4.unk85) {
                g_CurrentEntity->ext.et_801BDAE4.unk85 = 0x18;
                g_CurrentEntity->ext.et_801BDAE4.unk84--;
            }
        }
        break;

    case 4:
        prim = g_CurrentEntity->ext.et_801BDAE4.unk7C;
        while (prim != NULL) {
            if (prim->p3) {
                func_us_801BCFD4(prim);
            }
            prim = prim->next;
        }
        prim = g_CurrentEntity->ext.et_801BDAE4.unk7C;
        while (prim != NULL) {
            if (prim->u1) {
                prim->x0++;
                prim->x2 = prim->x0;
                prim->x1--;
                prim->x3 = prim->x1;
            } else {
                prim->x0--;
                prim->x2 = prim->x0;
                prim->x1++;
                prim->x3 = prim->x1;
            }
            prim->y0 -= 8;
            prim->y1 -= 8;
            prim->y2 -= 8;
            prim->y3 -= 8;
            prim = prim->next;
        }
        if (++g_CurrentEntity->ext.et_801BDAE4.unk85 > 0x18) {
            g_CurrentEntity->ext.et_801BDAE4.unk84++;
        }
        break;

    case 5:
        primIndex = g_CurrentEntity->primIndex;
        g_api.FreePrimitives(primIndex);
        g_CurrentEntity->flags &= ~FLAG_HAS_PRIMS;
        g_CurrentEntity->ext.et_801BDAE4.unk84++;
        break;
    }
}

u8 func_us_801BDA34(void);
INCLUDE_ASM("st/lib/nonmatchings/e_lesser_demon", func_us_801BDA34);

u8 func_us_801BBAB4(void);

extern s32 D_us_80181ACC;
extern s16 D_us_80181AD4[];
extern u8 D_us_80181B04[];
extern u8 D_us_80181B14[];
extern u8 D_us_80181B2C[];
extern u8 D_us_80181B34[];
extern u8 D_us_80181B44[];
extern u8 D_us_80181B4C[];
extern u8 D_us_80181B68[];
extern u8 D_us_80181B84[];
extern u8 D_us_80181B90[];
extern u8 D_us_80181B9C[];
extern u8 D_us_80181BAC[];
extern u8 D_us_80181BBC[];
extern s16 D_us_80181C34[];
extern s32 D_psp_092A5668;
extern s32 D_psp_092A5670;
extern s32 D_psp_092A5678;

// Lesser Demon
void func_us_801BDAE4(Entity* self) {
    Collider collider;
    Entity* tempEntity;
    s32 xOffset, yOffset;
    s32 i;
    u8 hit;
    s16 posX, posY;
    s16 tempVar;

    FntPrint("step     %x\n", self->step);
    FntPrint("step_s   %x\n", self->step_s);
    if ((self->flags & FLAG_DEAD) && (self->step < 15)) {
        if (self->flags & FLAG_HAS_PRIMS) {
            g_api.FreePrimitives(self->primIndex);
            self->flags &= ~FLAG_HAS_PRIMS;
        }
        self->hitboxState = 0;
        SetStep(15);
    }
    switch (self->step) {
    case 0:
        InitializeEntity(D_us_80180968);
        self->flags &= ~(FLAG_UNK_800 | FLAG_UNK_400);
        self->zPriority -= 2;
        self->hitboxOffX = 0;
        self->hitboxOffY = 2;
        break;

    case 1:
        if (UnkCollisionFunc3(D_us_80181AD4) & 1) {
            SetStep(2);
        }
        break;

    case 2:
        self->hitboxState = 0;
        self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
        if (D_us_80181ACC & 1) {
            self->hitboxState = 3;
            SetStep(3);
        }
        break;

    case 3:
        if (!self->step_s) {
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
            self->ext.et_801BDAE4.unk80 = 0x30;
            self->step_s++;
        }
        hit = func_us_801BDA34();
        if (hit) {
            self->facingLeft ^= 1;
        }
        if (!AnimateEntity(D_us_80181B04, self)) {
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
        }
        xOffset = self->posX.i.hi + g_Tilemap.scrollX.i.hi;
        if (xOffset < 0x160) {
            self->facingLeft = 1;
            SetStep(6);
        }
        if (xOffset > 0x2B0) {
            self->facingLeft = 0;
            SetStep(6);
        }
        if (!--self->ext.et_801BDAE4.unk80) {
            if (!(self->posX.i.hi & 0xFF00)) {
                if (Random() & 3) {
                    self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
                    self->ext.et_801BDAE4.unk84 = 0;
                    SetStep(13);
                    if ((GetDistanceToPlayerX() < 0x40) && (Random() & 3)) {
                        SetStep(4);
                    }
                } else {
                    SetStep(8);
                }
            } else {
                SetStep(8);
            }
        }
        break;

    case 6:
        switch (self->step_s) {
        case 0:
            if (!AnimateEntity(D_us_80181B2C, self)) {
                self->animFrameIdx = 0;
                self->animFrameDuration = 0;
                self->step_s++;
                self->velocityY = FIX(-6.0);
                if (self->facingLeft) {
                    self->velocityX = FIX(1.5);
                } else {
                    self->velocityX = FIX(-1.5);
                }
            }
            break;

        case 1:
            AnimateEntity(D_us_80181B34, self);
            if (UnkCollisionFunc3(D_us_80181AD4) & 1) {
                PlaySfxPositional(SFX_STOMP_HARD_B);
                self->animFrameIdx = 0;
                self->animFrameDuration = 0;
                self->step_s++;
            } else {
                self->velocityY -= FIX(0.125);
            }
            break;

        case 2:
            if (!AnimateEntity(D_us_80181B44, self)) {
                SetStep(3);
            }
            break;
        }
        break;

    case 8:
        if (!AnimateEntity(D_us_80181B4C, self)) {
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
        }
        if (!self->animFrameDuration && self->animFrameIdx == 7) {
            PlaySfxPositional(SFX_WING_FLAP_B);
        }
        MoveEntity();
        self->velocityX = 0;
        self->velocityY = FIX(-1.5);
        if (self->posY.i.hi < 0x50) {
            self->velocityY = 0;
            SetStep(9);
        }
        break;

    case 9:
        if (!self->step_s) {
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
            self->ext.et_801BDAE4.unk80 = D_us_80181C34[Random() & 3];
            self->step_s++;
        }
        AnimateEntity(D_us_80181B4C, self);
        MoveEntity();
        if (!self->animFrameDuration && self->animFrameIdx == 7) {
            PlaySfxPositional(SFX_WING_FLAP_B);
        }
        if (self->facingLeft) {
            self->velocityX = FIX(1.0);
        } else {
            self->velocityX = FIX(-1.0);
        }
        if (!--self->ext.et_801BDAE4.unk80) {
            self->step_s--;
            if (self->posX.i.hi & 0xFF00) {
                if (Random() & 3) {
                    SetStep(14);
                } else {
                    SetStep(10);
                }
            } else {
                tempVar = GetDistanceToPlayerX();
                if (tempVar > 0x40) {
                    if ((Random() & 7) == 0) {
                        SetStep(4);
                    } else {
                        SetStep(12);
                        if ((Random() & 3) == 0) {
                            SetStep(14);
                        }
                    }
                } else {
                    SetStep(14);
                }
            }
            if (self->posY.i.hi < 0) {
                SetStep(11);
            }
        }
        break;

    case 10:
        if (!self->step_s) {
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
            if (self->facingLeft) {
                self->velocityX = FIX(2.0);
            } else {
                self->velocityX = FIX(-2.0);
            }
            self->ext.et_801BDAE4.unk80 = 0x60;
            self->step_s++;
            break;
        }
        MoveEntity();
        AnimateEntity(D_us_80181B68, self);
        if (g_Timer % 8 == 0) {
            PlaySfxPositional(SFX_WING_FLAP_B);
        }
        if (!--self->ext.et_801BDAE4.unk80) {
            SetStep(9);
        }
        break;

    case 4:
        switch (self->step_s) {
        case 0:
            tempEntity = &PLAYER;
            posX = tempEntity->posX.i.hi - self->posX.i.hi;
            posY = tempEntity->posY.i.hi - self->posY.i.hi;
            if (posX < 0) {
                posX += 0x20;
            } else {
                posX -= 0x20;
            }
            posY += 0x1A;
            tempVar = ratan2(-posY, posX);
            self->velocityX = rcos(tempVar) * 0x40;
            self->velocityY = -rsin(tempVar) * 0x40;
            if (self->velocityY < FIX(1.0)) {
                self->velocityY = FIX(1.0);
            }
            if (self->velocityX > 0) {
                self->facingLeft = 1;
            } else {
                self->facingLeft = 0;
            }
            tempEntity = AllocEntity(&g_Entities[160], &g_Entities[192]);
            if (tempEntity != NULL) {
#ifdef VERSION_PSP
                CreateEntityFromEntity(D_psp_092A5668, self, tempEntity);
#else
                CreateEntityFromEntity(E_ID_22, self, tempEntity);
#endif
                self->ext.et_801BDAE4.unk88 = tempEntity;
            } else {
                self->ext.et_801BDAE4.unk88 = NULL;
            }
            self->ext.et_801BDAE4.unk84 = 0;
            self->ext.et_801BDAE4.unk87 = 0;
            self->step_s++;
            /* fallthrough */
        case 1:
            MoveEntity();
            posX = self->posX.i.hi;
            posY = self->posY.i.hi + 0x20;
            g_api.CheckCollision(posX, posY, &collider, 0);
            if (collider.effects & EFFECT_SOLID) {
                PlaySfxPositional(SFX_STOMP_HARD_B);
                self->posY.i.hi += collider.unk18;
                self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
                self->step_s++;
                if (self->ext.et_801BDAE4.unk88 == NULL) {
                    SetStep(3);
                }
            } else {
                self->animCurFrame = 0x18;
            }
            break;

        case 2:
            tempEntity = self->ext.et_801BDAE4.unk88;
            if (!AnimateEntity(D_us_80181B14, self) &&
                !(self->flags & FLAG_HAS_PRIMS)) {
                self->ext.et_801BDAE4.unk87 = 0;
                DestroyEntity(tempEntity);
                SetStep(3);
                break;
            }
            if (!self->animFrameDuration && self->animFrameIdx == 5) {
                PlaySfxPositional(0x78F);
            }
            if (self->animFrameIdx > 4 && self->animFrameIdx < 11) {
                tempEntity->posX.i.hi = self->posX.i.hi;
                tempEntity->posY.i.hi = self->posY.i.hi;
                tempEntity->facingLeft = self->facingLeft;
                tempEntity->hitboxState = 1;
                self->ext.et_801BDAE4.unk87 = 1;
                if (self->facingLeft) {
                    EntityGreyPuffSpawner(self, 5, 3, -4, 32, 2, 7);
                } else {
                    EntityGreyPuffSpawner(self, 5, 3, 4, 32, 2, -7);
                }
            } else {
                tempEntity->hitboxState = 0;
            }
            break;
        }
        if (self->ext.et_801BDAE4.unk87) {
            func_us_801BC28C();
        }
        break;

    case 11:
        AnimateEntity(D_us_80181B4C, self);
        if (!self->animFrameDuration && self->animFrameIdx == 7) {
            PlaySfxPositional(SFX_WING_FLAP_B);
        }
        if (UnkCollisionFunc3(D_us_80181AD4) & 1) {
            PlaySfxPositional(SFX_STOMP_HARD_B);
            SetStep(3);
        }
        if (self->posY.i.hi > 0xD0) {
            SetStep(8);
        }
        break;

    case 12:
        switch (self->step_s) {
        case 0:
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
            AnimateEntity(D_us_80181B84, self);
            if (self->animFrameIdx == 2) {
                PlaySfxPositional(0x70E);
                self->ext.et_801BDAE4.unk84 = 0;
                self->step_s++;
                self->ext.et_801BDAE4.unk80 = 0;
            }
            break;

        case 1:
            if (func_us_801BBAB4()) {
                tempEntity = AllocEntity(&g_Entities[160], &g_Entities[192]);
                if (tempEntity != NULL) {
#ifdef VERSION_PSP
                    CreateEntityFromEntity(D_psp_092A5678, self, tempEntity);
#else
                    CreateEntityFromEntity(E_ID_20, self, tempEntity);
#endif
                    tempEntity->facingLeft = self->facingLeft;
                    if (self->facingLeft) {
                        tempEntity->posX.i.hi += 12;
                    } else {
                        tempEntity->posX.i.hi -= 12;
                    }
                    tempEntity->posY.i.hi -= 8;
                }
                self->ext.et_801BDAE4.unk84 = 0;
                PlaySfxPositional(SFX_FM_EXPLODE_D);
                self->step_s++;
            }
            break;

        case 2:
            if (!AnimateEntity(D_us_80181B84, self)) {
                SetStep(9);
            }
            break;
        }
        break;

    case 13:
        if (!self->step_s) {
            self->ext.et_801BDAE4.unk84 = 0;
            self->step_s++;
        }
        if (!AnimateEntity(D_us_80181B90, self)) {
            self->ext.et_801BDAE4.unk84 = 0;
            SetStep(3);
            break;
        }
        if (self->animFrameIdx == 3 && self->animFrameDuration == 0) {
            PlaySfxPositional(0x7D1);
            self->ext.et_801BDAE4.unk84 = 2;
            tempEntity = AllocEntity(&g_Entities[160], &g_Entities[192]);
            if (tempEntity != NULL) {
#ifdef VERSION_PSP
                CreateEntityFromEntity(D_psp_092A5670, self, tempEntity);
#else
                CreateEntityFromEntity(E_ID_21, self, tempEntity);
#endif
                tempEntity->facingLeft = self->facingLeft;
            }
        }
        if (self->animFrameIdx > 1) {
            func_us_801BC57C();
        }
        break;

    case 14:
        FntPrint("timer %x\n", self->ext.et_801BDAE4.unk80);
        switch (self->step_s) {
        case 0:
            posX = self->posX.i.hi;
            posY = self->posY.i.hi;
            tempVar = 0;
            hit = false;
            for (i = 0; i < 3; i++) {
                tempVar = posY + i * 16;
                g_api.CheckCollision(posX, tempVar, &collider, 0);
                if (collider.effects != EFFECT_NONE) {
                    self->ext.et_801BDAE4.unk87 = 0;
                    SetStep(9);
                    return;
                }
            }
            hit = false;
            for (i = 3; i < 10; i++) {
                tempVar = posY + i * 16;
                g_api.CheckCollision(posX, tempVar, &collider, 0);
                if (collider.effects != EFFECT_NONE) {
                    hit |= true;
                    break;
                }
            }
            if (!hit) {
                self->ext.et_801BDAE4.unk87 = 0;
                SetStep(9);
                return;
            }
            AnimateEntity(D_us_80181B9C, self);
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
            if (self->animFrameIdx == 3) {
                self->ext.et_801BDAE4.unk84 = 0;
                PlaySfxPositional(SFX_RAPID_SYNTH_BUBBLE);
                self->step_s++;
                self->ext.et_801BDAE4.unk8C = self->hitPoints;
                self->hitPoints = 0x7FFF;
                self->ext.et_801BDAE4.unk80 = 0x80;
            }
            break;

        case 1:
            if (self->ext.et_801BDAE4.unk80 & 1) {
                self->palette = 0x249;
            } else {
                self->palette = 0x24E;
            }
            if (!--self->ext.et_801BDAE4.unk80) {
                self->palette = 0x249;
                self->hitEffect = 0x249;
                self->flags &= ~0xF;
                PlaySfxPositional(SFX_TELEPORT_BANG_A);
                self->hitPoints = self->ext.et_801BDAE4.unk8C;
                self->step_s++;
                self->ext.et_801BDAE4.unk84++;
            }
            func_us_801BD268();
            break;

        case 2:
            self->ext.et_801BDAE4.unk80--;
            if (!AnimateEntity(D_us_80181B9C, self) &&
                !(self->flags & FLAG_HAS_PRIMS)) {
                self->ext.et_801BDAE4.unk87 = 0;
                SetStep(9);
            } else {
                func_us_801BD268();
            }
            break;
        }
        break;

    case 15:
        self->palette = PAL_OVL(0x160);
        if (g_Timer % 7 == 0) {
            tempEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (tempEntity != NULL) {
                CreateEntityFromEntity(E_INTENSE_EXPLOSION, self, tempEntity);
                tempEntity->posX.i.hi += (Random() & 0x1F) - 0x10;
                tempEntity->posY.i.hi += (Random() & 0x3F) - 0x20;
            }
        }
        if ((g_Timer & 0xF) == 0) {
            PlaySfxPositional(SFX_EXPLODE_B);
        }
        switch (self->step_s) {
        case 0:
            self->hitboxState = 0;
            D_us_80181ACC |= 2;
            self->step_s++;
            /* fallthrough */
        case 1:
            AnimateEntity(D_us_80181B4C, self);
            if (!self->animFrameDuration && self->animFrameIdx == 7) {
                PlaySfxPositional(SFX_WING_FLAP_B);
            }
            if (UnkCollisionFunc3(D_us_80181AD4) & 1) {
                self->step_s++;
                self->animFrameIdx = 0;
                self->animFrameDuration = 0;
            } else {
                self->velocityY -= FIX(3.5 / 16);
            }
            break;

        case 2:
            hit = func_us_801BDA34();
            if (!AnimateEntity(D_us_80181BAC, self) || hit) {
                self->animFrameIdx = 0;
                self->animFrameDuration = 0;
                self->drawFlags = FLAG_DRAW_UNK8;
                self->drawMode = DRAW_TPAGE2 | DRAW_TPAGE;
                self->unk6C = 0x80;
                self->ext.et_801BDAE4.unk80 = 0x40;
                self->step_s++;
            }
            break;

        case 3:
            AnimateEntity(D_us_80181BBC, self);
            self->unk6C -= 2;
            if (g_Timer % 5 == 0) {
                tempEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
                if (tempEntity != NULL) {
                    CreateEntityFromEntity(E_EXPLOSION, self, tempEntity);
                    tempEntity->params = 1;
                    tempEntity->posX.i.hi += (Random() & 0x1F) - 0x10;
                    tempEntity->posY.i.hi += (Random() & 0x1F) - 0x10;
                }
            }
            if (!--self->ext.et_801BDAE4.unk80) {
                PlaySfxPositional(SFX_EXPLODE_SMALL);
                self->animCurFrame = 0;
                D_us_80181ACC |= 4;
                self->step_s++;
            }
            break;

        case 4:
            DestroyEntity(self);
            return;
        }
        break;

    case 32:
        FntPrint("charal %x\n", self->animCurFrame);
        if (g_pads[1].pressed & PAD_SQUARE) {
            if (self->params) {
                break;
            }
            self->animCurFrame++;
            self->params |= 1;
        } else {
            self->params = 0;
        }
#ifdef VERSION_PSP
        if (g_pads[1].pressed & D_psp_08B42050) {
#else
        if (g_pads[1].pressed & PAD_CIRCLE) {
#endif
            if (!self->step_s) {
                self->animCurFrame--;
                self->step_s |= 1;
            }
        } else {
            self->step_s = 0;
        }
        break;
    }
    xOffset = self->posX.i.hi + g_Tilemap.scrollX.i.hi;
    yOffset = self->posY.i.hi + g_Tilemap.scrollY.i.hi;
    if (xOffset < 0x138) {
        self->posX.i.hi = 0x138 - g_Tilemap.scrollX.i.hi;
    }
    if (xOffset > 0x2C8) {
        self->posX.i.hi = 0x2C8 - g_Tilemap.scrollX.i.hi;
    }
    if (yOffset < 0x230) {
        self->posY.i.hi = 0x230 - g_Tilemap.scrollY.i.hi;
    }
    if (yOffset > 0x2A0) {
        self->posY.i.hi = 0x2A0 - g_Tilemap.scrollY.i.hi;
    }
}

INCLUDE_ASM("st/lib/nonmatchings/e_lesser_demon", func_us_801BED48);
