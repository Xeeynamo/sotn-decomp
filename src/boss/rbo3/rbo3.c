// SPDX-License-Identifier: AGPL-3.0-or-later

#include "rbo3.h"

#ifdef VERSION_PSP
extern s32 E_ID(UNK_24);
extern s32 E_ID(UNK_25);
extern s32 E_ID(UNK_26);
extern s32 E_ID(UNK_27);
extern s32 E_ID(MEDUSA);
#endif

extern EInit g_EInitMedusa;
#ifdef VERSION_PSP
extern u8 D_us_801805F0[];
#else
extern u8 PrizeDrops[];
#define D_us_801805F0 PrizeDrops
#endif
extern u8 D_us_801805FC[];
extern u8 D_us_8018060C[];
extern u8 D_us_80180618[];
extern u8 D_us_80180624[];
extern u8 D_us_80180630[];
extern u8 D_us_8018063C[];
extern s8 D_us_80180648[];
extern u8 D_us_80180670[];
extern s32 D_us_80180728;

#ifdef VERSION_PSP
char D_pspeu_09254890[] = "charal %x\n";
#endif

#ifdef VERSION_PSP
INCLUDE_ASM("boss/rbo3/nonmatchings/rbo3", EntityMedusa);
#else
void EntityMedusa(Entity* self) {
    Entity* entity;
    s16 rotate;
    s32 x;
    s32 i;
    s32 velocityX;
    s8* rect;
    u8* indexes;

    if (self->flags & FLAG_DEAD) {
        if (self->step != 7) {
            SetStep(7);
        }
    }

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitMedusa);
        self->animCurFrame = 1;
        self->hitboxState = 0;
        CreateEntityFromEntity(E_ID(UNK_25), self, self + 1);
        SetStep(1);
        // fallthrough

    case 1:
        if (D_us_80180728 & 1) {
            SetStep(2);
        }
        break;

    case 2:
        // n.b.! AnimateEntity is not declared
        if (!AnimateEntity(D_us_801805F0, self)) {
            self->hitboxState = 3;
            SetStep(3);
        }
        break;

    case 3:
        AnimateEntity(D_us_801805FC, self);
        if (self->step_s == 0) {
            self->ext.GS_Props.timer = 64;
            self->step_s++;
        }
        if (GetDistanceToPlayerX() < 104) {
            self->ext.GS_Props.attackMode = 1;
        }
        if (GetDistanceToPlayerX() > 128) {
            self->ext.GS_Props.attackMode = 0;
        }
        if (GetDistanceToPlayerX() > 32) {
            self->facingLeft = GetSideToPlayer() & 1;
        }
        MoveEntity();

        if (self->facingLeft == self->ext.GS_Props.attackMode) {
            self->velocityX = FIX(1.0 / 2.0);
        } else {
            self->velocityX = -FIX(1.0 / 2.0);
        }
        if (self->hitFlags & 3) {
            SetStep(6);
        }
        x = PLAYER.posX.i.hi - self->posX.i.hi;
        if (g_Player.status & PLAYER_STATUS_UNK2000 &&
            (x * PLAYER.velocityX) < 0) {
            if (abs(x) < 80) {
                SetStep(5);
            }
        }

        if (!--self->ext.GS_Props.timer) {
            GetSideToPlayer();
            if (GetDistanceToPlayerX() <= 64) {
                SetStep(5);
            } else {
                SetStep(4);
            }
        }
        break;
    case 5:
        if (self->step_s == 0) {
            if (Random() & 1) {
                PlaySfxPositional(SFX_MEDUSA_ATTACK_A);
            } else {
                PlaySfxPositional(SFX_MEDUSA_ATTACK_B);
            }
            PlaySfxPositional(SFX_MEDUSA_WEAPON_SWING);
            self->step_s++;
        }
        self->ext.GS_Props.flag = 1;
        if (AnimateEntity(D_us_80180624, self) == 0) {
            self->ext.GS_Props.flag = 0;
            SetStep(3);
        }
        break;
    case 4:
        if (self->step_s == 0) {
            if (!(Random() & 3)) {
                PlaySfxPositional(SFX_MEDUSA_STONE);
            }
            self->step_s++;
        }
        if (AnimateEntity(D_us_8018060C, self) == 0) {
            SetStep(3);
            if (g_Player.status & PLAYER_STATUS_STONE) {
                SetStep(8);
            }
        }

        if (self->pose == 4 && self->poseTimer == 0) {
            entity = AllocEntity(&g_Entities[0xA0], &g_Entities[0xC0]);
            if (entity != NULL) {
                CreateEntityFromEntity(E_ID(UNK_24), self, entity);
                entity->facingLeft = self->facingLeft;
                if (self->facingLeft) {
                    entity->posX.i.hi -= 13;
                } else {
                    entity->posX.i.hi += 13;
                }
                entity->posY.i.hi = entity->posY.i.hi - 28;
                PlaySfxPositional(SFX_BAT_ECHO_B);
            }
        }
        break;
    case 8:
        if (self->step_s == 0) {
            PlaySfxPositional(SFX_MEDUSA_VENOM);
            self->step_s++;
        }
        if (AnimateEntity(D_us_80180618, self) == 0) {
            SetStep(3);
        }
        if (self->pose == 3 && self->poseTimer == 0) {
            // This sound is never heard because it is immediately interrupted
            // by the SFX_ELECTRICITY sound call below
            PlaySfxPositional(SFX_SCIFI_BLAST);
            for (i = 0; i < 2; i++) {
                entity = AllocEntity(&g_Entities[0xA0], &g_Entities[0xC0]);
                if (entity != NULL) {
                    CreateEntityFromEntity(E_ID(UNK_26), self, entity);
                    entity->rotate = i * 1024 - 512;
                    if (!self->facingLeft) {
                        entity->rotate = (i * 1024) + 1536;
                    }
                    entity->posY.i.hi -= 16;
                    entity->zPriority = self->zPriority - 2;
                }
            }
        }
        break;
    case 6:
        if (self->step_s == 0) {
            if (Random() & 1) {
                PlaySfxPositional(SFX_MEDUSA_PAIN_A);
            } else {
                PlaySfxPositional(SFX_MEDUSA_PAIN_B);
            }
            self->step_s++;
        }

        if (!AnimateEntity(D_us_80180630, self)) {
            self->facingLeft = GetSideToPlayer() & 1;
            SetStep(4);
        }
        break;
    case 7:
        switch (self->step_s) {
        case 0:
            PlaySfxPositional(SFX_MEDUSA_DEATH);
            self->hitboxState = 0;
            D_us_80180728 |= 2;
            self->step_s++;
            // fallthrough
        case 1:
            if (!AnimateEntity(D_us_8018063C, self)) {
                self->ext.GS_Props.timer = 80;
                // This sfxID is used by several bosses during death anim,
                // however it was purposely muted for Medusa and Death
                PlaySfxPositional(SFX_BOSS_LARGE_FLAMES);
                self->step_s++;
            }
            break;

        case 2:
            entity = AllocEntity(&g_Entities[0xC0], &g_Entities[0x100]);
            if (entity != NULL) {
                CreateEntityFromEntity(E_ID(UNK_27), self, entity);
                entity->params = 0;
                entity->zPriority = self->zPriority + 1;
                entity->posX.i.hi -= 16 - (Random() & 31);
                entity->posY.i.hi += 24;
            }
            if (!(self->ext.GS_Props.timer & 0xF)) {
                PlaySfxPositional(SFX_FIREBALL_SHOT_B);
            }

            if (!--self->ext.GS_Props.timer) {
                self->animCurFrame = 0;
                D_us_80180728 |= 4;
                self->step_s++;
            }
            break;
        }
        break;

    case 255:
#include "../../st/pad2_anim_debug.h"
    }

    x = self->posX.i.hi + g_Tilemap.scrollX.i.hi;
    if (self->velocityX < 0) {
        if (x < 128) {
            self->posX.i.hi = 128 - g_Tilemap.scrollX.i.hi;
        }
    } else if (x > 384) {
        self->posX.i.hi = 384 - g_Tilemap.scrollX.i.hi;
    }

    indexes = D_us_80180670;
    rect = D_us_80180648;
    rect += indexes[self->animCurFrame] * 4;

    self->hitboxOffX = *rect++;
    self->hitboxOffY = *rect++;
    self->hitboxWidth = *rect++;
    self->hitboxHeight = *rect++;
}
#endif

extern EInit D_us_80180498;

void func_us_80192020(Entity* self) {
    Primitive* prim;
    s32 posX, posY;
    s32 primIndex;
    Entity* player;
    s32 var_a2;
    s16 angle;
#ifndef VERSION_PSP
    u16 var_v0;
#endif

    if (self->flags & FLAG_DEAD) {
        SetStep(2);
    }

    switch (self->step) {
    case 0:
        InitializeEntity(D_us_80180498);
        self->hitboxHeight = 1;
        primIndex = g_api.AllocPrimitives(PRIM_LINE_G2, 1);
        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags |= FLAG_HAS_PRIMS;
        self->primIndex = primIndex;
        prim = &g_PrimBuf[primIndex];
        self->ext.prim = prim;
        prim->x0 = prim->x1 = self->posX.i.hi;
        prim->y0 = prim->y1 = self->posY.i.hi;
        prim->r0 = 255;
        prim->g0 = 64;
        prim->b0 = 128;
        prim->r1 = 0;
        prim->g1 = 0;
        prim->b1 = 0;
        prim->priority = self->zPriority;
        prim->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_UNK02 | DRAW_TRANSP;
        player = &PLAYER;
        posX = player->posX.i.hi - self->posX.i.hi;
        posY = player->posY.i.hi - self->posY.i.hi;

        angle = ratan2(posY, posX);
        if (self->facingLeft) {
#ifdef VERSION_PSP
            if (angle > 0) {
                if (angle < FLT(3.0 / 8.0)) {
                    angle = FLT(3.0 / 8.0);
                }
            }
            if (angle < 0) {
                if (angle > FLT(-3.0 / 8.0)) {
                    angle = FLT(-3.0 / 8.0);
                }
            }
#else
            var_v0 = angle - 1;
            if (var_v0 < (FLT(3.0 / 8.0) - 1)) {
                angle = FLT(3.0 / 8.0);
            }
            var_v0 = angle + FLT(3.0 / 8.0) - 1;
            if (var_v0 < FLT(3.0 / 8.0) - 1) {
                angle = FLT(-3.0 / 8.0);
            }
#endif
        } else {
            if (angle > FLT(1.0 / 8.0)) {
                angle = FLT(1.0 / 8.0);
            }
            if (angle < -FLT(1.0 / 8.0)) {
                angle = -FLT(1.0 / 8.0);
            }
        }
        self->velocityX = rcos(angle) << 7;
        self->velocityY = rsin(angle) << 7;

    case 1:
        MoveEntity();

        prim = self->ext.prim;
        posX = prim->x0 = self->posX.i.hi;
        posY = prim->y0 = self->posY.i.hi;

        var_a2 = 0;
        if (self->velocityX > 0) {
#ifdef VERSION_PSP
            if (posX > 288) {
                var_a2 = 1;
            }
#else
            var_a2 = (posX <= 288) ^ 1;
#endif
        } else if (posX < -32) {
            var_a2 = 1;
        }
        if (self->velocityY > 0) {
            if (posY > 288) {
                var_a2 = 1;
            }
        } else if (posY < -32) {
            var_a2 = 1;
        }
        if (var_a2) {
            self->hitboxState = 0;
            self->step++;
        }
        break;

    case 2:
        prim = self->ext.prim;
        if (PrimDecreaseBrightness(prim, 16) == 0) {
            DestroyEntity(self);
        }
        break;
    }
}

extern EInit D_us_8018048C;
extern s8 D_us_80180684[];
extern u8 D_us_801806B0[];

void func_us_801922EC(Entity* self) {
    Entity* prev;
    s32 animCurFrame;
    s8* rect;

    if (!self->step) {
        InitializeEntity(D_us_8018048C);
    }

    prev = self - 1;
    animCurFrame = prev->animCurFrame;
    self->posX.i.hi = prev->posX.i.hi;
    self->posY.i.hi = prev->posY.i.hi;
    self->facingLeft = prev->facingLeft;

    if (prev->ext.GS_Props.flag) {
        self->hitboxState = 1;
    } else {
        self->hitboxState = 2;
    }

    animCurFrame = prev->animCurFrame;
    rect = D_us_80180684;
    rect += D_us_801806B0[animCurFrame] * 4;

    self->hitboxOffX = *rect++;
    self->hitboxOffY = *rect++;
    self->hitboxWidth = *rect++;
    self->hitboxHeight = *rect++;

    if (prev->entityId != E_ID(MEDUSA)) {
        DestroyEntity(self);
    }
}

extern EInit D_us_801804A4;

void func_us_801923DC(Entity* self) {
    const int PrimCount = 13;
    s32 i;
    s32 primIndex;
    s16 angle;
    s32 xOffset;
    s32 yOffset;
    s32 x;
    s32 y;
    Primitive* prim;
    s16* offsets;
    Entity* next;
    s32 tempY;
    Entity* player;

    switch (self->step) {
    case 0:
        InitializeEntity(D_us_801804A4);
        primIndex = g_api.AllocPrimitives(PRIM_GT4, PrimCount);
        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }

        self->flags |= FLAG_HAS_PRIMS;
        self->primIndex = primIndex;
        prim = &g_PrimBuf[primIndex];
        self->ext.prim = prim;

        for (i = 0; i < PrimCount; i++) {
            prim->tpage = 0x1A;
            prim->clut = PAL_UNK_194;

            prim->u0 = prim->u1 = i * 4 + 144;
            prim->u2 = prim->u3 = i * 4 + 148;
            prim->v0 = prim->v2 = 208;
            prim->v1 = prim->v3 = 192;
            prim->r0 = prim->g0 = prim->b0 = 192 - (i * 16);

            LOW(prim->r1) = LOW(prim->r0);
            LOW(prim->r2) = LOW(prim->r0);
            LOW(prim->r3) = LOW(prim->r0);

            prim->priority = self->zPriority + 1;
            prim->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS |
                             DRAW_UNK02 | DRAW_TRANSP;

            prim = prim->next;
        }

        offsets = self->ext.medusaUnk1A.offsets;
        for (i = 0; i < (PrimCount + 1); i++) {
            offsets[0] = self->posX.i.hi;
            offsets[1] = self->posY.i.hi;
            offsets += 2;
        }

        angle = self->rotate;
        self->velocityX = rcos(angle) * 160;
        self->velocityY = rsin(angle) * 160;
        self->ext.factory.unk82 = angle;
        self->ext.factory.unk80 = 0x40;

    case 1:
        MoveEntity();
        player = &PLAYER;
        angle = GetAngleBetweenEntities(self, player);
        tempY = 96 - self->ext.factory.unk80;
        angle = LimitAngleChange(tempY, self->ext.factory.unk82, angle);
        self->velocityX = rcos(angle) * 160;
        self->velocityY = rsin(angle) * 160;
        self->ext.factory.unk82 = angle;

        if (!--self->ext.factory.unk80 || self->hitFlags & 0x80) {
            self->step++;
        }
        break;

    case 2:
        MoveEntity();
        xOffset = self->posX.i.hi + g_Tilemap.scrollX.i.hi;
        yOffset = self->posY.i.hi + g_Tilemap.scrollY.i.hi;
        if ((xOffset < -64) || (yOffset < -64) || (xOffset > 576) ||
            (yOffset > 320)) {
            DestroyEntity(self);
            return;
        }
        break;
    }

    if (!(g_Timer & 7)) {
        PlaySfxPositional(SFX_ELECTRICITY);
    }

    // this is the same as self->ext.unkB8. for this
    // entity 0xB8 is not an entity pointer but the
    // last pair of offsets.
    offsets = &self->ext.medusaUnk1A
                   .offsets[sizeof(self->ext.medusaUnk1A.offsets) / 2];

    for (i = 0; i < PrimCount; i++) {
        offsets[0] = offsets[-2] - g_ScrollDeltaX;
        offsets[1] = offsets[-1] - g_ScrollDeltaY;
        offsets -= 2;
    }

    offsets = self->ext.medusaUnk1A.offsets;

    offsets[0] = self->posX.i.hi;
    offsets[1] = self->posY.i.hi;
    offsets = self->ext.medusaUnk1A.offsets;
    prim = self->ext.prim;
    x = offsets[0];
    y = offsets[1];
    prim = self->ext.prim;

    xOffset = offsets[2] - x;
    yOffset = offsets[3] - y;
    angle = ratan2(yOffset, xOffset);
    angle -= FLT(1.0 / 4.0);
    xOffset = (rcos(angle) * 5) >> 12;
    yOffset = (rsin(angle) * 5) >> 12;
    prim->x0 = x + xOffset;
    prim->y0 = y + yOffset;
    prim->x1 = x - xOffset;
    prim->y1 = y - yOffset;
    prim->priority = self->zPriority;
    offsets += 2;

    for (i = 0; i < (PrimCount - 2); i++) {
        xOffset = offsets[0] - x;
        yOffset = offsets[1] - y;
        angle = ratan2(yOffset, xOffset);
        angle -= FLT(1.0 / 4.0);

        x = (offsets[0] + x) / 2;
        y = (offsets[1] + y) / 2;

        xOffset = ((12 - i) * rcos(angle)) >> 12;
        yOffset = ((12 - i) * rsin(angle)) >> 12;

        prim->x2 = x + xOffset;
        prim->y2 = y + yOffset;
        prim->x3 = x - xOffset;
        prim->y3 = y - yOffset;

        prim->priority = self->zPriority;
        prim = prim->next;

        prim->x0 = x + xOffset;
        prim->y0 = y + yOffset;
        prim->x1 = x - xOffset;
        prim->y1 = y - yOffset;

        x = offsets[0];
        y = offsets[1];
        offsets += 2;
    }

    prim->x1 = prim->x2 = offsets[0];
    prim->y2 = prim->y3 = offsets[1];
    prim->priority = self->zPriority;

    while (prim != NULL) {
        prim->drawMode = DRAW_HIDE;
        prim = prim->next;
    }

    for (prim = self->ext.prim; prim != NULL; prim = prim->next) {
        if (g_Timer & 1) {
            prim->v0 = prim->v2 = 208;
            prim->v1 = prim->v3 = 192;
        } else {
            prim->v0 = prim->v2 = 192;
            prim->v1 = prim->v3 = 208;
        }
    }
}
