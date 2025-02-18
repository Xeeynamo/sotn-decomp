// SPDX-License-Identifier: AGPL-3.0-or-later
#include "lib.h"

INCLUDE_ASM("st/lib/nonmatchings/unk_3C57C", func_us_801BC57C);

INCLUDE_ASM("st/lib/nonmatchings/unk_3C57C", func_us_801BC814);

INCLUDE_ASM("st/lib/nonmatchings/unk_3C57C", func_us_801BCC10);

INCLUDE_ASM("st/lib/nonmatchings/unk_3C57C", func_us_801BCFD4);

// Lesser Demon minion spawn?
// Seems like the vertical tractor beam effect that spawns
// Mudmen, Skeleton, Ectoplasm
INCLUDE_ASM("st/lib/nonmatchings/unk_3C57C", func_us_801BD268);

u8 func_us_801BDA34(void);
INCLUDE_ASM("st/lib/nonmatchings/unk_3C57C", func_us_801BDA34);

u8 func_us_801BBAB4(void);

extern u16 D_us_80180968[];
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
extern s32 D_psp_08B42050;
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
#ifdef VERSION_PSP
#define DEBUG_REWIND_BUTTON D_psp_08B42050
#endif
#include "../pad2_anim_debug.h"
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

INCLUDE_ASM("st/lib/nonmatchings/unk_3C57C", func_us_801BED48);
