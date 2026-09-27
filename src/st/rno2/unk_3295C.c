// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rno2.h"

// Appears far in the background in the rooms with Azaghal and Malachi
// The Azaghal room has 3 of this entity, and the Malachi corridor
// has 2 more. This entity does not move with the background and stays
// fixed in the camera - no scrolling.
// Params = 0 in Malachi corridor, 1 in Azaghal room
void EntityDeepBackgroundArch(Entity* self) {
    Primitive* prim;
    s16 xOffset;
    s16 yOffset;
    s32 i;

    if (self->params) {
        xOffset = 0;
        yOffset = -0x80;
    } else {
        xOffset = 0;
        yOffset = 0x30;
    }

    if (!self->step) {
        self->step += 1;
        if (self->params) {
            self->primIndex = g_api.AllocPrimitives(PRIM_GT4, 32);
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
            prim->u1 = 0x80;
            prim->v2 = 0;
            prim->u0 = 0xC8;
            prim->v3 = 0;
            prim->u3 = 0x80;
            prim->v0 = 0x68;
            prim->u2 = 0xC8;
            prim->v1 = 0x68;

            prim->x0 = prim->x2 = xOffset + ((i & 7) << 6);
            prim->x1 = prim->x3 = prim->x0 + 0x48;
            prim->y1 = prim->y0 = yOffset + ((i >> 3) * 0x64);
            prim->y3 = prim->y2 = prim->y0 + 0x6C;

            prim->tpage = 0xF;
            prim->clut = 0x36;
            prim->priority = 0x1E;
            prim->drawMode = DRAW_DEFAULT;
        }
    }
}

void func_us_801B3F30_from_bo0(Entity* self) {
    u8 colorLo;
    u16 color;
    s16 deltaPosXHi;
    s16 absDeltaPosXHi;
    u32 curPal;
    s32 i;
    s32 j;

    extern s32 g_Unk17ClutIds[];
    extern u16 g_Unk17PaletteAnim[];

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitCommon);
        self->animSet = ANIMSET_OVL(2);
        self->animCurFrame = 3;
        self->ext.et_801B3F30.unk7C = 2;
        self->ext.et_801B3F30.unk80 = 0x10;
        self->zPriority = 0x80;
        self->blendMode = BLEND_TRANSP | BLEND_QUARTER;
        break;
    case 1:
        if (g_Tilemap.scrollY.i.hi >= 0x304) {
            deltaPosXHi = self->posX.i.hi - PLAYER.posX.i.hi;
            absDeltaPosXHi = abs(deltaPosXHi);
            if (absDeltaPosXHi < 0x80) {
                self->step++;
            }
        }
        break;
    case 2:
        if (--self->ext.et_801B3F30.unk80 == 0) {
            for (i = 0; i < 7; i++) {
                curPal = g_Unk17ClutIds[i];
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
            LoadClut((u_long*)&g_Clut[0][0x400], 0x200, 0xF4);
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
    self->palette = g_Unk17PaletteAnim[self->ext.et_801B3F30.unk7E];
}

void func_us_801B4148_from_bo0(Entity* self) {
    if (self->step == 0) {
        InitializeEntity(g_EInitCommon);
        self->animSet = ANIMSET_OVL(2);
        self->animCurFrame = 1;
        self->zPriority = 0xA0;
    }
}

void func_us_801B41A4_from_bo0(Entity* self) {
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

extern u8 g_Unk1AAnimIdle;
extern u8 g_Unk1AAnimDestroyed;

void func_us_801B4210_from_bo0(Entity* self) {
    Entity* entity;
    bool flag;
    s32 i;

    flag = false;
    if (g_Entities[self->params + 0x40].entityId != 1) {
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
        AnimateEntity(&g_Unk1AAnimIdle, self);
    } else {
        AnimateEntity(&g_Unk1AAnimDestroyed, self);
    }
    self->ext.et_801B4210.unk7C = flag;
}
