// SPDX-License-Identifier: AGPL-3.0-or-later
#include "no0.h"

void func_us_801C2A34(Entity* self) {
    s16 angle;

    if (!self->step) {
        InitializeEntity(g_EInitCommon);
        self->animSet = -0x7FFF;
        self->animCurFrame = 0x21;
        self->zPriority = 0x50;
        self->unk5A = 0;
        self->palette = 0;
        self->drawFlags = FLAG_DRAW_ROTZ | FLAG_DRAW_UNK8;
        self->unk6C = 0x60;
    }
    angle = rsin((((g_Timer % 120) << 0xC) + 0x3C) / 120);
    if (!angle) {
        g_api_PlaySfx(SFX_LOW_CLOCK_TICK);
    }
    self->rotZ = (angle >> 6) + (angle >> 7);
}

void func_us_801C2B24(Entity* self) {
    Tilemap* tilemap = &g_Tilemap;
    Entity* player = &PLAYER;
    s16 volume;

    if (!self->step) {
        InitializeEntity(D_us_80180A88);
    }
    if (g_Timer % 60 == 0) {
        switch (self->params) {
        case 0:
            g_api.PlaySfx(SFX_LOW_CLOCK_TICK);
            return;
        case 1:
            volume =
                ((tilemap->scrollX.i.hi + player->posX.i.hi - 0x1C0) * 2) / 5;
            if (volume < 0) {
                volume = 0;
            } else if (volume >= 0x80) {
                volume = 0x7F;
            }
            volume = volume & 0xFF;
            g_api.PlaySfxVolPan(SFX_LOW_CLOCK_TICK, volume, 8);
            return;
        case 2:
            volume = ((0x140 - player->posX.i.hi) * 2) / 5;
            if (volume < 0) {
                volume = 0;
            } else if (volume >= 0x80) {
                volume = 0x7F;
            }
            volume = volume & 0xFF;
            g_api.PlaySfxVolPan(SFX_LOW_CLOCK_TICK, volume, -8);
            return;
        }
    }
}

void func_us_801C2CD8(Entity* self) {
    s32 var = GetPlayerCollisionWith(self, 16, 8, 5);
    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitCommon);
        self->animSet = -0x7FFF;
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
                g_api_PlaySfx(SFX_LEVER_METAL_BANG);
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

INCLUDE_ASM("st/no0/nonmatchings/42A34", func_us_801C2E7C);

void func_us_801C3308(Entity* self) {
    g_CastleFlags[CASTLE_FLAG_1] = 1;
    DestroyEntity(self);
}

void AxeKnightDeath() {
    Entity* entity;
    s8 temp_s4 = Random() & 3;
    s16 temp_s3 = ((Random() & 0xF) << 8) - 0x800;
    s32 i;

    for (i = 0; i < 6; i++) {
        entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
        if (entity != NULL) {
            CreateEntityFromEntity(E_WARG_EXP_OPAQUE, g_CurrentEntity, entity);
            entity->params = 2;
            entity->ext.wargpuff.unk89 = 6 - i;
            entity->ext.wargpuff.unk84 = temp_s3;
            entity->ext.wargpuff.unk88 = temp_s4;
        }
    }
}

INCLUDE_ASM("st/no0/nonmatchings/42A34", EntityWargExplosionPuffOpaque);
