// SPDX-License-Identifier: AGPL-3.0-or-later
#include "no1.h"

extern u16 D_us_801815F4[];
extern u16 D_us_80181604[][8];
extern s32 D_psp_0929A738;
extern s32 D_psp_0929A740;
extern s32 D_psp_0929A748;

// Breakable wall with chicken
void func_us_801BE880(Entity* self) {
    Entity* tempEntity;
    s32 tilePos;
    s32 i;
    u8 animFrame;
    Entity* tempEntity2;

    switch (self->step) {
    case 0:
        InitializeEntity(D_us_801809C8);
        self->zPriority = 0x70;
        self->hitPoints = 0x7FFF;
        self->hitboxState = 0;
        self->ext.et_801BE880.unk82 = 0;
        if (g_CastleFlags[NO1_SECRET_WALL_BROKEN]) {
            self->step = 5;
        } else {
            tempEntity = self + 2;
#ifdef VERSION_PSP
            CreateEntityFromEntity(D_psp_0929A748, self, tempEntity);
#else
            CreateEntityFromEntity(E_ID_25, self, tempEntity);
#endif
            tempEntity->posY.i.hi -= 0x18;
            tempEntity->params = 2;
            tempEntity = self + 1;
#ifdef VERSION_PSP
            CreateEntityFromEntity(D_psp_0929A748, self, tempEntity);
#else
            CreateEntityFromEntity(E_ID_25, self, tempEntity);
#endif
            tempEntity->posY.i.hi -= 0x30;
            tempEntity->params = 1;
        }
        break;

    case 1:
        if (self->ext.et_801BE880.unk82 > 8) {
            self->ext.et_801BE880.unk82 = 0;
            for (i = 0; i < 5; i++) {
                tempEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
                if (tempEntity != NULL) {
#ifdef VERSION_PSP
                    CreateEntityFromEntity(D_psp_0929A740, self, tempEntity);
#else
                    CreateEntityFromEntity(E_ID_26, self, tempEntity);
#endif
                    tempEntity->posX.i.hi += 0x10;
                    tempEntity->posY.i.hi -= 0x30;
                    tempEntity->params = i;
                }
            }
            if (self->animCurFrame < 0x4D) {
                self->animCurFrame++;
            }
        }
        if (self->ext.et_801BE880.unk84) {
            PlaySfxPositional(SFX_WALL_DEBRIS_B);
            self->step_s = 0;
            self->step = self->ext.et_801BE880.unk84 + 1;
            if (self->ext.et_801BE880.unk84 == 3) {
                self->step = 2;
            }
        }
        break;

    case 2:
        self->animCurFrame = 0x4F;
        if (self->ext.et_801BE880.unk84 & 2) {
            PlaySfxPositional(SFX_WALL_DEBRIS_B);
            self->step = 4;
        }
        break;

    case 3:
        self->animCurFrame = 0x4E;
#ifdef VERSION_PSP
        tempEntity2 = self + 1;
        if (tempEntity2->step == 1 && (tempEntity2->flags & FLAG_DEAD) == 0) {
            tempEntity2->flags |= FLAG_DEAD;
        }
        PlaySfxPositional(SFX_WALL_DEBRIS_B);
        self->step = 4;
#else
        if (self->ext.et_801BE880.unk84 & 1) {
            PlaySfxPositional(SFX_WALL_DEBRIS_B);
            self->step = 4;
        }
#endif
        break;

    case 4:
        self->animCurFrame = 0x50;
        g_CastleFlags[NO1_SECRET_WALL_BROKEN] = 1;
        tempEntity = AllocEntity(&g_Entities[160], &g_Entities[192]);
        if (tempEntity != NULL) {
            CreateEntityFromEntity(E_EQUIP_ITEM_DROP, self, tempEntity);
            tempEntity->params = 0x43;
            tempEntity->posY.i.hi -= 0x30;
        }
        self->step++;
        break;
    default:
        self->animCurFrame = 0x50;
        break;
    }
    animFrame = self->animCurFrame - 0x4B;
    for (i = 0; i < 6; i++) {
        tilePos = D_us_801815F4[i];
        g_Tilemap.fg[tilePos] = D_us_80181604[animFrame][i];
    }
}

// Hit spawner?
void func_us_801BEB54(Entity* self) {
    Entity* tempEntity;
    s32 i;

    if (self->hitParams) {
        PlaySfxPositional(SFX_EXPLODE_FAST_B);
    }
    switch (self->step) {
    case 0:
        InitializeEntity(D_us_801809D4);
        self->hitPoints = 0x18;
        self->hitboxWidth = 0x10;
        self->hitboxHeight = 0xC;
        self->hitboxState = 2;
        self->ext.et_801BE880.unk80 = self->hitPoints;
        self->hitboxOffY = -0xC;
        break;

    case 1:
        if (self->hitPoints ^ self->ext.et_801BE880.unk80) {
            (self - self->params)->ext.et_801BE880.unk82 +=
                self->ext.et_801BE880.unk80 - self->hitPoints;
            self->ext.et_801BE880.unk80 = self->hitPoints;
        }
        if (self->flags & FLAG_DEAD) {
            (self - self->params)->ext.et_801BE880.unk84 |= self->params;
            self->step++;
        }
        break;

    case 2:
        if (self->step_s == 0) {
            tempEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (tempEntity != NULL) {
                CreateEntityFromEntity(E_EXPLOSION, self, tempEntity);
                tempEntity->posY.i.hi -= 8;
                tempEntity->params = 0x13;
            }
            for (i = 0; i < 3; i++) {
                tempEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
                if (tempEntity != NULL) {
                    CreateEntityFromEntity(
                        E_INTENSE_EXPLOSION, self, tempEntity);
                    tempEntity->posX.i.hi += (i * 0x10) - 0x10;
                    tempEntity->params = 0x10;
                }
            }
            for (i = 0; i < 5; i++) {
                tempEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
                if (tempEntity != NULL) {
#ifdef VERSION_PSP
                    CreateEntityFromEntity(D_psp_0929A738, self, tempEntity);
#else
                    CreateEntityFromEntity(E_ID_27, self, tempEntity);
#endif
                    tempEntity->posX.i.hi += (i * 8) - 0x10 + (Random() & 3);
                    tempEntity->posY.i.hi -= (Random() & 7) + 0x14;
                    tempEntity->params = i;
                }
            }
            self->step_s++;
        }
        break;
    }
}

extern s16 D_us_80181668[];
extern s32 D_us_80181678[][2];
extern u8 D_us_801816E8[];

// Wall particles on hit
void func_us_801BEE00(Entity* self) {
    Primitive* prim;
    s32 primIndex;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitParticle);
        self->animSet = 8;
        self->animCurFrame = 1;
        self->palette = 0x8004;
        break;

    case 1:
        primIndex = g_api.AllocPrimBuffers(PRIM_GT4, 2);
        if (primIndex != -1) {
            self->flags |= FLAG_HAS_PRIMS;
            self->primIndex = primIndex;
            prim = &g_PrimBuf[primIndex];
            self->ext.et_801BE880.unk7C = prim;
            UnkPolyFunc2(prim);
            prim->tpage = 0xE;
            prim->clut = 2;
            prim->u0 = 0x70;
            prim->u1 = 0x78;
            prim->u2 = prim->u0;
            prim->u3 = prim->u1;
            prim->v0 = 0xF6;
            prim->v1 = prim->v0;
            prim->v2 = 0xFD;
            prim->v3 = prim->v2;
            prim->priority = self->zPriority;
            prim->drawMode = DRAW_UNK02;
            prim->next->x1 = self->posX.i.hi;
            prim->next->y0 = self->posY.i.hi;
            LOH(prim->next->r2) = 4;
            LOH(prim->next->b2) = 4;
            prim->next->b3 = 0x80;
        } else {
            DestroyEntity(self);
            return;
        }
        self->velocityX = D_us_80181678[self->params][0];
        self->velocityY = D_us_80181678[self->params][1];
        self->step++;
        break;

    case 2:
        prim = self->ext.et_801BE880.unk7C;
        LOH(prim->next->tpage) += 0x180;
        prim->next->x1 = self->posX.i.hi;
        prim->next->y0 = self->posY.i.hi;
        UnkPrimHelper(prim);
        if (!AnimateEntity(D_us_801816E8, self)) {
            self->animCurFrame = 0;
        }
        if (UnkCollisionFunc5(D_us_80181668) != 0) {
            DestroyEntity(self);
            return;
        }
        self->velocityY -= FIX(0.0625);
        break;
    }
}

extern s32 D_us_801816A8[][2];
extern s16 D_us_801816D0[];
extern s16 D_us_801816DC[];
extern u8 D_us_801816E8[];

// More particles / stones
void func_us_801BF074(Entity* self) {
    Collider collider;
    Entity* tempEntity;
    Primitive* prim;
    s32 primIndex;
    s16 posX, posY;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitParticle);
        self->animSet = 8;
        self->animCurFrame = 1;
        self->palette = 0x8004;
        break;

    case 1:
        primIndex = g_api.AllocPrimBuffers(PRIM_GT4, 2);
        if (primIndex != -1) {
            self->flags |= FLAG_HAS_PRIMS;
            self->primIndex = primIndex;
            prim = &g_PrimBuf[primIndex];
            self->ext.prim = prim;
            UnkPolyFunc2(prim);
            prim->tpage = 0xE;
            prim->clut = 2;
            prim->u0 = 0x70;
            prim->u1 = 0x78;
            prim->u2 = prim->u0;
            prim->u3 = prim->u1;
            prim->v0 = 0xF6;
            prim->v1 = prim->v0;
            prim->v2 = 0xFD;
            prim->v3 = prim->v2;
            prim->priority = self->zPriority;
            prim->drawMode = DRAW_UNK02;

            prim->next->x1 = self->posX.i.hi;
            prim->next->y0 = self->posY.i.hi;
            LOH(prim->next->r2) = D_us_801816D0[self->params];
            LOH(prim->next->b2) = LOH(prim->next->r2);
            prim->next->b3 = 0x80;
        } else {
            DestroyEntity(self);
            return;
        }
        self->velocityX = D_us_801816A8[self->params][0];
        self->velocityY = D_us_801816A8[self->params][1];
        self->step++;
        break;

    case 2:
        prim = self->ext.prim;
        LOH(prim->next->tpage) += D_us_801816DC[self->params];
        prim->next->x1 = self->posX.i.hi;
        prim->next->y0 = self->posY.i.hi;
        UnkPrimHelper(prim);
        if (!AnimateEntity(D_us_801816E8, self)) {
            self->animCurFrame = 0;
        }
        MoveEntity();
        self->velocityY += FIX(0.125);
        if (self->velocityY < 0) {
            break;
        }
        posX = self->posX.i.hi;
        posY = self->posY.i.hi;
        posY += (LOH(prim->next->r2) / 2) - 2;
        g_api.CheckCollision(posX, posY, &collider, 0);
        if (collider.effects & EFFECT_SOLID) {
            self->posY.i.hi += collider.unk18;
            self->velocityX += FIX(0.25);
            self->velocityY = -self->velocityY / 2;
            if (self->velocityY > FIX(-0.25)) {
                if (LOH(prim->next->r2) > 6) {
                    tempEntity =
                        AllocEntity(&g_Entities[224], &g_Entities[256]);
                    if (tempEntity != NULL) {
                        CreateEntityFromEntity(
                            E_INTENSE_EXPLOSION, self, tempEntity);
                        tempEntity->params = 0x10;
                    }
                }
                DestroyEntity(self);
                return;
            }
        }
        break;
    }
}

extern s32 D_us_80181664;

// Secret elevator inside chicken wall
// Stand still for ~20 seconds to activate
void func_us_801BF3F4(Entity* self) {
    Collider collider;
    s32 tilePos;
    s32 i;
    u8 collision;
    s16 posX, posY;

    Entity* player = &PLAYER;

    if (g_Player.status & (PLAYER_STATUS_WOLF_FORM | PLAYER_STATUS_MIST_FORM |
                           PLAYER_STATUS_BAT_FORM)) {
        collision = 0;
    } else {
        collision = GetPlayerCollisionWith(self, 16, 8 - self->params, 4);
    }
    switch (self->step) {
    case 0:
        InitializeEntity(D_us_80180A40);
        self->drawMode = DRAW_TPAGE2 | DRAW_TPAGE;
        self->zPriority = 0x6A;
        if (self->params) {
            if (collision) {
                self->step = 3;
                tilePos = 0x31;
                for (i = 0; i < 2; i++) {
                    g_Tilemap.fg[tilePos] = 0x4BD;
                    tilePos++;
                }
            } else {
                tilePos = 0x31;
                for (i = 0; i < 2; i++) {
                    g_Tilemap.fg[tilePos] = 0x3FE;
                    tilePos++;
                }
                self->step = 5;
            }
            break;
        }
        for (i = 6; i < 8; i++) {
            tilePos = D_us_801815F4[i];
            g_Tilemap.fg[tilePos] = D_us_80181604[4][i];
        }
        if (D_us_80181664 != 0) {
            self->posY.i.hi = 0xEE - g_Tilemap.scrollY.i.hi;
            collision = GetPlayerCollisionWith(self, 16, 8 - self->params, 4);
            if (collision) {
                g_Player.padSim = 0;
                g_Player.D_80072EFC = 2;
                self->step = 6;
                for (i = 6; i < 8; i++) {
                    tilePos = D_us_801815F4[i];
                    g_Tilemap.fg[tilePos] = D_us_80181604[5][i];
                }
            }
        }
        break;

    case 1:
        FntPrint("timer %x\n", self->ext.et_801BF3F4.unk88);
        if (collision && (GetDistanceToPlayerX() < 6)) {
            if (!--self->ext.et_801BF3F4.unk88) {
                g_Player.padSim = 0;
                g_Player.D_80072EFC = 2;
                self->step++;
            }
        } else {
            self->ext.et_801BF3F4.unk88 = 0x400;
        }
        break;

    case 2:
        if (!self->params) {
            for (i = 0; i < 8; i++) {
                tilePos = D_us_801815F4[i];
                g_Tilemap.fg[tilePos] = D_us_80181604[5][i];
            }
        }
        g_Player.padSim = 0;
        g_Player.D_80072EFC = 2;
        D_us_80181664 = 1;
        g_api.PlaySfx(0x7B6);
        self->step++;
        break;

    case 3:
        g_Player.D_80072EFC = 2;
        self->posY.i.hi++;
        if (collision) {
            player->posY.i.hi++;
            D_80097488.y.i.hi += 1;
            g_api.ResetAfterImage(0, 1);
        }
        if (self->params) {
            posX = self->posX.i.hi;
            posY = self->posY.i.hi + 8;
            g_api.CheckCollision(posX, posY, &collider, 0);
            FntPrint("vram %x\n", collider.effects);
            if (collider.effects & EFFECT_SOLID) {
                g_Player.D_80072EFC = 0;
                self->step++;
            }
        }
        break;

    case 4:
        tilePos = 0x31;
        for (i = 0; i < 2; i++) {
            g_Tilemap.fg[tilePos] = 0x3FE;
            tilePos++;
        }
        if (!collision) {
            self->step++;
        }
        break;

    case 5:
        if (collision && GetDistanceToPlayerX() < 6) {
            g_api.ResetAfterImage(0, 1);
            g_Player.D_80072EFC = 2;
            g_Player.padSim = 0;
            player->posY.i.hi--;
            D_80097488.y.i.hi -= 1;
            self->posY.i.hi--;
            tilePos = 0x31;
            for (i = 0; i < 2; i++) {
                g_Tilemap.fg[tilePos] = 0x4BD;
                tilePos++;
            }
        } else {
            if (D_us_80181664 != 0) {
                self->posY.i.hi = 0xB4;
            }
        }
        break;

    case 6:
        g_Player.D_80072EFC = 2;
        self->posY.i.hi--;
        if (collision) {
            player->posY.i.hi--;
            D_80097488.y.i.hi -= 1;
            g_api.ResetAfterImage(0, 1);
        }
        posY = self->posY.i.hi + g_Tilemap.scrollY.i.hi;
        if (posY < 0xC7) {
            self->posY.i.hi = 0xC7 - g_Tilemap.scrollY.i.hi;
            D_us_80181664 = 0;
            for (i = 6; i < 8; i++) {
                tilePos = D_us_801815F4[i];
                g_Tilemap.fg[tilePos] = D_us_80181604[4][i];
            }
            self->step = 1;
        }
        break;
    }
    if (collision) {
        g_unkGraphicsStruct.g_zEntityCenter = 0x6E;
        PLAYER.zPriority = g_unkGraphicsStruct.g_zEntityCenter;
    } else {
        g_unkGraphicsStruct.g_zEntityCenter = 0x94;
        PLAYER.zPriority = g_unkGraphicsStruct.g_zEntityCenter;
    }
    FntPrint("idou_flag %x\n", D_us_80181664);
}
