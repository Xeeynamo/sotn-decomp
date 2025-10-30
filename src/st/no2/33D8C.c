// SPDX-License-Identifier: AGPL-3.0-or-later
#include "no2.h"

u16 D_us_80180B7C[] = {
    PAL_FLAG(0x44), PAL_FLAG(0x48), PAL_FLAG(0x49), PAL_FLAG(0x4A),
    PAL_FLAG(0x4B), PAL_FLAG(0x4C), PAL_FLAG(0x4D)};
u32 D_us_80180B8C[] = {4, 8, 9, 10, 11, 12, 13};
u8 D_us_80180BA8[] = {10, 4, 10, 5, 10, 6, 10, 7, 10, 8, 0, 0};
u8 D_us_80180BB4[] = {10, 10, 0, 0};

void func_us_801B3D8C(Entity* self) {
    Primitive* prim;
    s16 offsetX;
    s16 offsetY;
    s32 i;

    if (self->params) {
        offsetX = 0;
        offsetY = -0x40;
    } else {
        offsetX = 0;
        offsetY = 0x58;
    }
    if (!self->step) {
        self->step++;
        if (self->params) {
            self->primIndex = g_api.AllocPrimitives(PRIM_GT4, 0x20);
        } else {
            self->primIndex = g_api.AllocPrimitives(PRIM_GT4, 8);
        }
        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags = FLAG_KEEP_ALIVE_OFFCAMERA | FLAG_HAS_PRIMS;
        prim = &g_PrimBuf[self->primIndex];
        for (i = 0; prim != NULL; i++, prim = prim->next) {
            prim->x0 = prim->x2 = (i & 7) * 0x40 + offsetX;
            prim->x1 = prim->x3 = prim->x0 + 0x48;
            prim->y1 = prim->y0 = (i >> 3) * 0x64 + offsetY;
            prim->y3 = prim->y2 = prim->y0 + 0x6C;
            prim->u0 = 0x80;
            prim->v0 = 0;
            prim->u1 = 0xC8;
            prim->v1 = 0;
            prim->u2 = 0x80;
            prim->v2 = 0x68;
            prim->u3 = 0xC8;
            prim->v3 = 0x68;
            prim->tpage = 0xF;
            prim->clut = 0x36;
            prim->priority = 0x10;
            prim->drawMode = DRAW_DEFAULT;
        }
    }
}

void func_us_801B3F30(Entity* self) {
    u8 colorLo;
    u16 color;
    s16 deltaPosXHi;
    s16 absDeltaPosXHi;
    u32 curPal;
    s32 i;
    s32 j;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitCommon);
        self->animSet = ANIMSET_OVL(2);
        self->animCurFrame = 3;
        self->ext.et_801B3F30.unk7C = 2;
        self->ext.et_801B3F30.unk80 = 0x10;
        self->zPriority = 0x80;
        self->drawMode = DRAW_UNK_40 | DRAW_TPAGE2 | DRAW_TPAGE;
        break;
    case 1:
        if (g_Tilemap.scrollY.i.hi >= 0x304) {
            deltaPosXHi = self->posX.i.hi - PLAYER.posX.i.hi;
            absDeltaPosXHi = abs(deltaPosXHi);
            if (absDeltaPosXHi < 0x80)
                self->step++;
        }
        break;
    case 2:
        if (--self->ext.et_801B3F30.unk80 == 0) {
            for (i = 0; i < 7; i++) {
                curPal = D_us_80180B8C[i];
                for (j = 1; j < 16; j++) {
                    color = g_Clut[0][0x400 + curPal * COLORS_PER_PAL + j];
                    colorLo = color & 0x1F;
                    colorLo++;
                    if (colorLo > 0x1F) {
                        colorLo = 0x1F;
                    }
                    g_Clut[0][0x400 + curPal * COLORS_PER_PAL + j] =
                        (color & ~0x1F) + colorLo;
                }
            }
            LoadClut((void*)&(g_Clut[0][0x400]), 0x200, 0xF4);
            self->ext.et_801B3F30.unk80 = 0x10;
        }
        break;
    }
    if (--self->ext.et_801B3F30.unk7C == 0) {
        self->ext.et_801B3F30.unk7E++;
        self->ext.et_801B3F30.unk7C = 2;
    }
    if (self->ext.et_801B3F30.unk7E > 6) {
        self->ext.et_801B3F30.unk7E = 0;
    }
    self->palette = D_us_80180B7C[self->ext.et_801B3F30.unk7E];
}

void func_us_801B4148(Entity* self) {
    if (self->step == 0) {
        InitializeEntity(g_EInitCommon);
        self->animSet = ANIMSET_OVL(2);
        self->animCurFrame = 1;
        self->zPriority = 0xA0;
    }
}

void func_us_801B41A4(Entity* self) {
    if (g_CurrentEntity->step == 0) {
        g_CurrentEntity->step++;
    }
    g_GpuBuffers[0].draw.r0 = 0x20;
    g_GpuBuffers[0].draw.g0 = 0x18;
    g_GpuBuffers[0].draw.b0 = 0x28;
    g_GpuBuffers[1].draw.r0 = 0x20;
    g_GpuBuffers[1].draw.g0 = 0x18;
    g_GpuBuffers[1].draw.b0 = 0x28;
}

void func_us_801B4210(Entity* self) {
    Entity* entity;
    bool flag;
    s32 i;

    flag = false;
    if ((g_Entities[self->params + 0x40].entityId) != 1) {
        flag = true;
    }
    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitCommon);
        self->animSet = ANIMSET_OVL(2);
        self->zPriority = 0x80;
        break;
    case 1:
        if (self->ext.et_801B4210.unk7C == 0 && flag) {
            self->pose = self->poseTimer = 0;
            for (i = 0; i < 5; i++) {
                entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
                if (entity != NULL) {
                    CreateEntityFromEntity(E_INTENSE_EXPLOSION, self, entity);
                    entity->posX.i.hi += (rand() & 0xF) - 8;
                    entity->posY.i.hi += (rand() & 0xF) - 8;
                    entity->params = 0x10;
                }
            }
        }
        break;
    }
    if (!flag) {
        AnimateEntity(D_us_80180BA8, self);
    } else {
        AnimateEntity(D_us_80180BB4, self);
    }
    self->ext.et_801B4210.unk7C = flag;
}
