// SPDX-License-Identifier: AGPL-3.0-or-later
#include "no0.h"

void func_us_801C2A34(Entity* self) {
    s16 angle;

    if (!self->step) {
        InitializeEntity(g_EInitCommon);
        self->animSet = ANIMSET_OVL(1);
        self->animCurFrame = 0x21;
        self->zPriority = 0x50;
        self->unk5A = 0;
        self->palette = 0;
        self->drawFlags = FLAG_DRAW_ROTZ | FLAG_DRAW_UNK8;
        self->unk6C = 0x60;
    }
    angle = rsin((((g_Timer % 120) << 0xC) + 0x3C) / 120);
    if (!angle) {
        g_api.PlaySfx(SFX_LOW_CLOCK_TICK);
    }
    self->rotZ = (angle >> 6) + (angle >> 7);
}

void func_us_801C2B24(Entity* self) {
    Tilemap* tilemap = &g_Tilemap;
    Entity* player = &PLAYER;
    u8 volume;
    s16 distance;

    if (!self->step) {
        InitializeEntity(D_us_80180A88);
    }
    if (g_Timer % 60 == 0) {
        switch (self->params) {
        case 0:
            g_api.PlaySfx(SFX_LOW_CLOCK_TICK);
            break;
        case 1:
            distance =
                ((tilemap->scrollX.i.hi + player->posX.i.hi - 0x1C0) * 2) / 5;
            if (distance < 0) {
                volume = 0;
            } else if (distance >= 0x80) {
                volume = 0x7F;
            } else {
                volume = (u8)distance;
            }
            g_api.PlaySfxVolPan(SFX_LOW_CLOCK_TICK, volume, 8);
            break;
        case 2:
            distance = ((0x140 - player->posX.i.hi) * 2) / 5;
            if (distance < 0) {
                volume = 0;
            } else if (distance >= 0x80) {
                volume = 0x7F;
            } else {
                volume = (u8)distance;
            }
            g_api.PlaySfxVolPan(SFX_LOW_CLOCK_TICK, volume, -8);
            break;
        }
    }
}

void func_us_801C2CD8(Entity* self) {
    s32 var = GetPlayerCollisionWith(self, 16, 8, 5);
    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitCommon);
        self->animSet = ANIMSET_OVL(1);
        self->animCurFrame = 0x2D;
        self->zPriority = 0x9E;
        if (g_CastleFlags[CASTLE_FLAG_1]) {
            self->posY.i.hi += 4;
            self->step = 3;
        }
        break;
    case 1:
        if (var & 4) {
            Entity* player = &PLAYER;
            self->posY.val += FIX(0.5);
            player->posY.val += FIX(0.5);
            self->ext.timer.t++;
            if (self->ext.timer.t > 8) {
                g_api.PlaySfx(SFX_LEVER_METAL_BANG);
                g_CastleFlags[CASTLE_FLAG_1] = 1;
                self->step++;
            }
        }
        break;
    case 2:
        var = self->ext.timer.t++;
        if (var & 1) {
            g_backbufferY = 1;
        } else {
            g_backbufferY = -1;
        }
        if (var > 64) {
            g_backbufferY = 0;
            self->step++;
        }
        break;
    }
}

extern u8 D_8003BDED;
extern s16 D_us_80180FF0[];
extern s16 D_us_80180FF8[];
extern u8 D_us_80181028[];
extern s16 D_us_80181034[];
extern u16 g_EInitCommon;

void func_us_801C2E7C(Entity* self) {
    Primitive* prim;
    s32 primIndex;
    s16 i;
    s16 posY;
    u16 params;
    u8* var_a0;
    s16 posX;
    s16 tilePos;
    s16* dataPtr;
    u32 castleFlag1;

    params = self->params;
    castleFlag1 = g_CastleFlags[CASTLE_FLAG_1];
    switch (self->step) {
    case 0:
        InitializeEntity(&g_EInitCommon);
        self->animCurFrame = 0;
        self->zPriority = 0x9E;

        if (castleFlag1) {
            primIndex = g_api.AllocPrimitives(PRIM_GT4, 3);
        } else {
            primIndex = g_api.AllocPrimitives(PRIM_GT4, 3);
        }

        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }

        self->flags |= FLAG_HAS_PRIMS;
        self->primIndex = primIndex;
        prim = &g_PrimBuf[primIndex];
        var_a0 = D_us_80181028;

        while (prim != NULL) {
            prim->tpage = 0xF;
            prim->clut = 0x3E;
            prim->u0 = prim->u2 = *var_a0++;
            prim->u1 = prim->u3 = *var_a0++;
            prim->v0 = prim->v1 = *var_a0++;
            prim->v2 = prim->v3 = *var_a0++;
            prim->priority = self->zPriority + 1;
            prim->drawMode = DRAW_UNK02;
            prim = prim->next;
        }
        if (!castleFlag1) {
            dataPtr = &D_us_80180FF0[params * 2];
            tilePos = *dataPtr++;
            posX = *dataPtr++;
            for (i = 0; i < 3; i++) {
                (&g_Tilemap.fg[tilePos])[0] = 0x597;
                (&g_Tilemap.fg[tilePos])[1] = 0x597;
                (&g_Tilemap.fg[tilePos])[2] = 0x597;
                (&g_Tilemap.fg[tilePos])[3] = 0x597;
                tilePos += posX;
            }
        } else {
            self->step = 3;
        }
        break;

    case 1:
        if (castleFlag1) {
            self->ext.timer.t = 0x20;
            self->step++;
        }
        break;

    case 2:
        i = 0;
        prim = &g_PrimBuf[self->primIndex];
        while (prim != NULL) {
            if (params) {
                if (i >= 2) {
                    prim->x0 = prim->x2--;
                    prim->x1 = prim->x3--;
                } else {
                    prim->x0 = prim->x2++;
                    prim->x1 = prim->x3++;
                }
            } else {
                if (i >= 2) {
                    prim->x0 = prim->x2++;
                    prim->x1 = prim->x3++;
                } else {
                    prim->x0 = prim->x2--;
                    prim->x1 = prim->x3--;
                }
            }
        }
        if (!--self->ext.timer.t) {
            self->step++;
        }
        break;

    case 3:
        dataPtr = &D_us_80180FF0[params * 2];
        tilePos = *dataPtr++;
        posX = *dataPtr++;
        dataPtr = &D_us_80180FF8[params * 12];
        for (i = 0; i < 3; i++) {
            (&g_Tilemap.fg[tilePos])[0] = *dataPtr++;
            (&g_Tilemap.fg[tilePos])[1] = *dataPtr++;
            (&g_Tilemap.fg[tilePos])[2] = *dataPtr++;
            (&g_Tilemap.fg[tilePos])[3] = *dataPtr++;
            tilePos += posX;
        }
        self->step++;
        break;
    }

    if (self->step != 2) {
        dataPtr = &D_us_80181034[(params * 2 + castleFlag1) * 12];
        prim = &g_PrimBuf[self->primIndex];
        posX = self->posX.i.hi;
        posY = self->posY.i.hi;
        while (prim != NULL) {
            prim->x0 = prim->x2 = posX + *dataPtr++;
            prim->x1 = prim->x3 = posX + *dataPtr++;
            prim->y0 = prim->y1 = posY + *dataPtr++;
            prim->y2 = prim->y3 = posY + *dataPtr++;
            prim = prim->next;
        }
    }
}

void func_us_801C3308(Entity* self) {
    g_CastleFlags[CASTLE_FLAG_1] = 1;
    DestroyEntity(self);
}
