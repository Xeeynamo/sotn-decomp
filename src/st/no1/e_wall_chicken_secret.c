// SPDX-License-Identifier: AGPL-3.0-or-later
#include "no1.h"

// Breakable wall with chicken
INCLUDE_ASM("st/no1/nonmatchings/e_wall_chicken_secret", func_us_801BE880);

// Hit spawner?
INCLUDE_ASM("st/no1/nonmatchings/e_wall_chicken_secret", func_us_801BEB54);

// Wall particles on hit
INCLUDE_ASM("st/no1/nonmatchings/e_wall_chicken_secret", func_us_801BEE00);

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
        return;
    case 1:
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 2);
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

extern s32 D_80097408[];
extern u16 D_us_801815F4[];
extern u16 D_us_80181604[];
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
            g_Tilemap.fg[tilePos] = *(&D_us_80181604[i] + 32);
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
                    g_Tilemap.fg[tilePos] = *(&D_us_80181604[i] + 40);
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
                g_Tilemap.fg[tilePos] = *(&D_us_80181604[i] + 40);
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
            g_api.func_8010DFF0(0, 1);
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
            g_api.func_8010DFF0(0, 1);
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
            g_api.func_8010DFF0(0, 1);
        }
        posY = self->posY.i.hi + g_Tilemap.scrollY.i.hi;
        if (posY < 0xC7) {
            self->posY.i.hi = 0xC7 - g_Tilemap.scrollY.i.hi;
            D_us_80181664 = 0;
            for (i = 6; i < 8; i++) {
                tilePos = D_us_801815F4[i];
                g_Tilemap.fg[tilePos] = *(&D_us_80181604[i] + 32);
            }
            self->step = 1;
        }
        break;
    }
    if (collision) {
        D_80097408[0] = 0x6E;
        PLAYER.zPriority = D_80097408[0];
    } else {
        D_80097408[0] = 0x94;
        PLAYER.zPriority = D_80097408[0];
    }
    FntPrint("idou_flag %x\n", D_us_80181664);
}
