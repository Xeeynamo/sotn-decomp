// SPDX-License-Identifier: AGPL-3.0-or-later

#include "rbo3.h"

void func_us_80191438(Entity* self) {
    s16 params;
    s16 y;

    params = self->params;
    FntPrint("set:%04x\n", params);
    FntPrint("sx:%04x\n", g_Tilemap.left);
    FntPrint("ex:%04x\n", g_Tilemap.right);

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitCommon);
        self->animSet = 2;
        self->animCurFrame = 1;
        self->zPriority = 176;
        break;

    case 1:
        y = self->posY.i.hi - PLAYER.posY.i.hi;
        y = abs(y);

        if (y < 32) {
            switch (params) {
            case 0:
                if (g_PlayerX < 384) {
                    g_Tilemap.x = 384;
                    g_Tilemap.left++;
                    self->step++;
                }
                break;

            case 1:
                if (g_PlayerX > 640) {
                    g_Tilemap.width = 640;
                    g_Tilemap.right--;
                    self->step++;
                }
                break;

            case 2:
                if (g_PlayerX < 256) {
                    g_Tilemap.x = 256;
                    g_Tilemap.left++;
                    self->step++;
                }
                break;

            case 3:
                if (g_PlayerX > 768) {
                    g_Tilemap.width = 768;
                    g_Tilemap.right--;
                    self->step++;
                }
                break;

            case 4:
                if (g_PlayerX < 256) {
                    g_Tilemap.x = 256;
                    g_Tilemap.left++;
                    self->step++;
                }
                break;

            case 5:
                if (g_PlayerX > 1152) {
                    g_Tilemap.width = 1152;
                    self->step++;
                }
                break;

            case 6:
                if (g_PlayerX < 128) {
                    g_Tilemap.x = 128;
                    self->step++;
                }
                break;

            case 7:
                if (g_PlayerX < 128) {
                    g_Tilemap.x = 128;
                    self->step++;
                }
                break;

            case 8:
                if (g_PlayerX > 640) {
                    g_Tilemap.width = 640;
                    self->step++;
                }
                break;

            case 9:
                if (g_PlayerX < 128) {
                    g_Tilemap.x = 128;
                    self->step++;
                }
                break;

            case 10:
                if (g_PlayerX > 640) {
                    g_Tilemap.width = 640;
                    g_Tilemap.right--;
                    self->step++;
                }
                break;

            case 11:
                if (g_PlayerX < 384) {
                    g_Tilemap.x = 384;
                    g_Tilemap.left++;
                    self->step++;
                }
                break;

            case 12:
                if (g_PlayerX > 640) {
                    g_Tilemap.width = 640;
                    g_Tilemap.right--;
                    self->step++;
                }
                break;

            case 13:
            case 14:
                if (g_PlayerX < 256) {
                    g_Tilemap.x = 256;
                    g_Tilemap.left++;
                    self->step++;
                }
                break;
            }
        }
        break;
    }
}

extern Entity D_8007A958;
extern Entity D_8007C0D8;
extern EInit D_us_80180480;
extern u8 RBO3_PrizeDrops[];
extern u8 D_us_801805FC[];
extern u8 D_us_8018060C[];
extern u8 D_us_80180618[];
extern u8 D_us_80180624[];
extern u8 D_us_80180630[];
extern u8 D_us_8018063C[];
extern s8 D_us_80180648[];
extern u8 D_us_80180670[];
extern s32 D_us_80180728;

void EntityMedusa(Entity* self) {
    Entity* entity;
    s16 rotZ;
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
        InitializeEntity(D_us_80180480);
        self->animCurFrame = 1;
        self->hitboxState = 0;
        CreateEntityFromEntity(UNK_ENTITY_25, self, self + 1);
        SetStep(1);
        // fallthrough

    case 1:
        if (D_us_80180728 & 1) {
            SetStep(2);
        }
        break;

    case 2:
        // n.b.! AnimateEntity is not declared
        if (!AnimateEntity(RBO3_PrizeDrops, self)) {
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
                PlaySfxPositional(SFX_RBO3_UNK_7FE);
            } else {
                PlaySfxPositional(SFX_RBO3_UNK_7FF);
            }
            PlaySfxPositional(SFX_RBO3_UNK_7C8);
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
                PlaySfxPositional(SFX_RBO3_UNK_7FB);
            }
            self->step_s++;
        }
        if (AnimateEntity(D_us_8018060C, self) == 0) {
            SetStep(3);
            if (g_Player.status & PLAYER_STATUS_STONE) {
                SetStep(8);
            }
        }

        if (self->animFrameIdx == 4 && self->animFrameDuration == 0) {
            entity = AllocEntity(&g_Entities[0xA0], &g_Entities[0xC0]);
            if (entity != NULL) {
                CreateEntityFromEntity(UNK_ENTITY_24, self, entity);
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
            PlaySfxPositional(SFX_RBO3_UNK_7FD);
            self->step_s++;
        }
        if (AnimateEntity(D_us_80180618, self) == 0) {
            SetStep(3);
        }
        if (self->animFrameIdx == 3 && self->animFrameDuration == 0) {
            PlaySfxPositional(SFX_RBO3_UNK_7D1);
            for (i = 0; i < 2; i++) {
                entity = AllocEntity(&g_Entities[0xA0], &g_Entities[0xC0]);
                if (entity != NULL) {
                    CreateEntityFromEntity(UNK_ENTITY_26, self, entity);
                    entity->rotZ = i * 1024 - 512;
                    if (!self->facingLeft) {
                        entity->rotZ = (i * 1024) + 1536;
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
                PlaySfxPositional(SFX_RBO3_UNK_801);
            } else {
                PlaySfxPositional(SFX_RBO3_UNK_802);
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
            PlaySfxPositional(SFX_RBO3_UNK_804);
            self->hitboxState = 0;
            D_us_80180728 |= 2;
            self->step_s++;
            // fallthrough
        case 1:
            if (!AnimateEntity(D_us_8018063C, self)) {
                self->ext.GS_Props.timer = 80;
                PlaySfxPositional(SFX_RBO3_UNK_7C5);
                self->step_s++;
            }
            break;

        case 2:
            entity = AllocEntity(&g_Entities[0xC0], &g_Entities[0x100]);
            if (entity != NULL) {
                CreateEntityFromEntity(UNK_ENTITY_27, self, entity);
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

extern EInit D_us_80180498;

void func_us_80192020(Entity* self) {
    Primitive* prim;
    s32 posX, posY;
    s16 primIndex;
    s32 var_a2;
    s16 angle;
    u16 var_v0;

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
        prim = &g_PrimBuf[primIndex];
        self->primIndex = primIndex;
        self->ext.prim = prim;
        self->flags |= FLAG_HAS_PRIMS;
        prim->x0 = prim->x1 = self->posX.i.hi;
        prim->y0 = prim->y1 = self->posY.i.hi;
        prim->r0 = 255;
        prim->g0 = 64;
        prim->b0 = 128;
        prim->b1 = prim->g1 = prim->r1 = 0;
        prim->priority = self->zPriority;
        prim->blendMode = 0x33;
        posX = PLAYER.posX.i.hi - self->posX.i.hi;
        posY = PLAYER.posY.i.hi - self->posY.i.hi;

        angle = ratan2(posY, posX);
        if (self->facingLeft) {
            var_v0 = angle - 1;
            if (var_v0 < (FLT(3.0 / 8.0) - 1)) {
                angle = FLT(3.0 / 8.0);
            }
            var_v0 = angle + FLT(3.0 / 8.0) - 1;
            if (var_v0 < FLT(3.0 / 8.0) - 1) {
                angle = FLT(-3.0 / 8.0);
            }
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
            var_a2 = (posX <= 288) ^ 1;
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
        if (PrimDecreaseBrightness(self->ext.prim, 16) == 0) {
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
    u8* indexes;
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
    indexes = D_us_801806B0;
    rect = D_us_80180684;
    rect += indexes[animCurFrame] * 4;

    self->hitboxOffX = *rect++;
    self->hitboxOffY = *rect++;
    self->hitboxWidth = *rect++;
    self->hitboxHeight = *rect++;

    if (prev->entityId != 23) {
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
            prim->clut = 0x194;

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

        offsets = &self->ext.medusaUnk1A.offsets;
        for (i = 0; i < (PrimCount + 1); i++) {
            offsets[0] = self->posX.i.hi;
            offsets[1] = self->posY.i.hi;
            offsets += 2;
        }

        angle = self->rotZ;
        self->velocityX = rcos(angle) * 160;
        self->velocityY = rsin(angle) * 160;
        self->ext.factory.unk82 = angle;
        self->ext.factory.unk80 = 0x40;

    case 1:
        MoveEntity();
        player = &PLAYER;
        angle = GetAngleBetweenEntities(self, player);
        tempY = 96 - self->ext.factory.unk80;
        angle = GetNormalizedAngle(tempY, self->ext.factory.unk82, angle);
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

extern EInit g_EInitParticle;
extern Unkstruct_80180FE0 D_us_8018071C[];

// Entity ID 0x1B
void func_us_80192998(Entity* self) {
    s32 params;
    u32 priorityParams;
    Unkstruct_80180FE0* obj;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitParticle);
        params = self->params & 0xF;
        obj = &D_us_8018071C[params];
        self->palette = obj->palette + 0x2E0;
        self->blendMode = obj->blendMode;
        self->animSet = obj->animSet;
        self->unk5A = obj->unk2;
        self->ext.e_80192998.anim = obj->anim;
        self->step = params + 1;
        priorityParams = self->params & 0xFF00;
        if (priorityParams) {
            self->zPriority = priorityParams >> 8;
        }

        if (self->params & 0xF0) {
            self->palette = PAL_OVL(0x19F);
            self->blendMode = 0x10;
            self->facingLeft = 1;
        }
        break;

    case 1:
        if (self->step_s == 0) {
            self->drawFlags = FLAG_DRAW_UNK8;
            self->unk6C = 0xC0;
            self->facingLeft = Random() & 1;
            self->velocityX = (Random() << 8) - FIX(1.0 / 2.0);
            self->velocityY = FIX(-0.75);
            self->ext.e_80192998.accelY = -(Random() * 16) - FIX(1.0 / 4.0);
            self->step_s++;
        }
        MoveEntity();
        self->velocityY += self->ext.e_80192998.accelY;
        self->unk6C += 255;
        if (AnimateEntity(self->ext.e_80192998.anim, self) == 0) {
            DestroyEntity(self);
        }
        break;
    }
}

extern Entity D_8007A958;
extern EInit g_EInitInteractable;
extern s32 D_us_80180728;
extern s32 D_us_8018072C;

void func_us_80192B38(Entity* self) {
    Entity* entity;
    s32 x;
    s32 y;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitInteractable);
        // fallthrough
    case 1:
        entity = &PLAYER;
        x = entity->posX.i.hi + g_Tilemap.scrollX.i.hi;
        if (x > 128 && x < 384) {
            D_us_8018072C = 1;
            D_us_80180728 = 1;
            g_api.TimeAttackController(
                TIMEATTACK_EVENT_MEDUSA_DEFEAT, TIMEATTACK_SET_VISITED);
            D_80097928 = 1;
            D_80097910 = 0x330;
            self->step++;
        }
        break;
    case 2:
        if (g_api.func_80131F68() == false) {
            D_80097928 = 0;
            g_api.PlaySfx(D_80097910);
            self->step++;
        }
        break;

    case 3:
        if (D_us_80180728 & 2) {
            g_api.TimeAttackController(
                TIMEATTACK_EVENT_MEDUSA_DEFEAT, TIMEATTACK_SET_RECORD);
            g_api.PlaySfx(SET_UNK_90);
            D_80097910 = 0x301;
            self->step++;
        }
        break;

    case 4:
        if (D_us_80180728 & 4) {
            self->step++;
        }
        break;

    case 5:
        x = 256 - g_Tilemap.scrollX.i.hi;
        y = 128 - g_Tilemap.scrollY.i.hi;
        entity = AllocEntity(&g_Entities[0xA0], &g_Entities[0xC0]);
        if (entity == NULL) {
            break;
        }
#ifdef VERSION_PSP
        // n.b.! CreateEntityFromEntity cannot be defined
        CreateEntityFromEntity(D_psp_09254D20, self, entity);
#else
        CreateEntityFromEntity(UNK_ENTITY_30, self, entity);
#endif
        entity->posX.i.hi = x;
        entity->posY.i.hi = y;
        entity->params = 0x11;
        D_us_8018072C = 0;
        D_80097928 = 1;
        D_80097910 = 0x301;
        self->step++;
        break;

    case 6:
        if (g_api.func_80131F68() == false) {
            D_80097928 = 0;
            g_api.PlaySfx(D_80097910);
            self->step++;
        }
        break;
    }
}
