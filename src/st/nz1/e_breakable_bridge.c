// SPDX-License-Identifier: AGPL-3.0-or-later
#include "nz1.h"

extern EInit g_EInitInteractable;
extern EInit g_EInitEnvironment;

static s32 D_us_80180EDC = 0;

static s16 D_us_80180EE0[] = {0, 16, 0, 4, 16, -4, -32, 0};

// clang-format off
static s16 D_us_80180EF0[] = {
    0x17, 0x4D, 0x5A, 0x59,
    0x41, 0x42, 0x43, 0x59,
    0x44, 0x45, 0x46, 0x47,
    0x3F, 0x23, 0x40, 0x24,
};
// clang-format on

static Point16 D_us_80180F10[] = {
    {0x490, 0x370}, {0x350, 0x370}, {0x2D0, 0x370},
    {0x190, 0x370}, {0x0D0, 0x3C0},
};

static s16 D_us_80180F24[][3] = {
    {0x490, 0x4C0, ROT(-21.8)},
    {0x350, 0x3B0, ROT(-6)},
    {0x2D0, 0x3B0, ROT(12)},
    {0x190, 0x4C0, ROT(-43.6)},
    {0x0D0, 0x400, ROT(12)}};

static void DropBridgePiece(void) {
    s32 i, j;
    s32 dx, dy;
    s32 tileX, tileY;
    s32 tileIdx;

    tileX = g_CurrentEntity->posX.i.hi + g_Tilemap.scrollX.i.hi;
    tileY = g_CurrentEntity->posY.i.hi + g_Tilemap.scrollY.i.hi;
    dx = tileX - 64;
    dy = tileY - 32;

    for (i = 0; i < 4; i++) {
        tileY = i * 16 + dy;
        for (j = 0; j < 8; j++) {
            tileX = j * 16 + dx;
            tileIdx = (tileX >> 4) + (((tileY >> 4) * g_Tilemap.hSize) << 4);
            g_Tilemap.fg[tileIdx] = 0;
        }
    }
}

static void BreakBridge(s32 tileIndex) {
    s32 i;
    s32 n;
    s32 tileX, tileY;
    s32 dx, dy;
    s32 tileIdx;
    s16* ptr;

    tileX = g_CurrentEntity->posX.i.hi + g_Tilemap.scrollX.i.hi;
    tileY = g_CurrentEntity->posY.i.hi + g_Tilemap.scrollY.i.hi;
    dx = tileX - 80;
    dy = tileY - 32;

    ptr = &D_us_80180EF0[tileIndex * 4];
    n = (g_CurrentEntity->params >> 8) - 1;
    for (i = 0; i < 2; i++, dx += 0x80) {
        if (n != i) {
            tileX = dx;
            tileY = dy;
            tileIdx = (tileX >> 4) + (((tileY >> 4) * g_Tilemap.hSize) << 4);

            (&g_Tilemap.fg[tileIdx])[0] = ptr[0];
            (&g_Tilemap.fg[tileIdx])[1] = ptr[1];
            (&g_Tilemap.fg[tileIdx])[0x60] = ptr[2];
            (&g_Tilemap.fg[tileIdx])[0x61] = ptr[3];
        }
    }
}

void EntityBridgeBreakTrigger(Entity* self) {
    Entity* entity;
    s32 posX;
    u32 posY;
    u32 params;
    s32 i;
    s32 var_s3;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitEnvironment);
        self->zPriority = 0x5F;
        self->animCurFrame = 1;
        params = self->params & 0xF;
        self->posX.i.hi = D_us_80180F10[params].x - g_Tilemap.scrollX.i.hi;
        self->posY.i.hi = D_us_80180F10[params].y - g_Tilemap.scrollY.i.hi;
        var_s3 = D_us_80180EDC & (1 << params);
        if (var_s3) {
            BreakBridge(3);
            DropBridgePiece();
            if (params == 0 || params == 3) {
                self->zPriority = 0x6E;
            }
            self->posX.i.hi = D_us_80180F24[params][0] - g_Tilemap.scrollX.i.hi;
            self->posY.i.hi = D_us_80180F24[params][1] - g_Tilemap.scrollY.i.hi;
            self->rotate = D_us_80180F24[params][2];
            self->opacity = 0x40;
            self->drawFlags |= ENTITY_OPACITY | ENTITY_ROTATE;
            self->step = 16;
            break;
        }
    case 1:
        entity = &PLAYER;
        posX = self->posX.i.hi - entity->posX.i.hi;
        posY = self->posY.i.hi - entity->posY.i.hi;

        if (posX < 0) {
            posX = -posX;
        }
        var_s3 = false;
        if (posX < 0x30 && posY < 0x40 &&
            g_Player.vram_flag & TOUCHING_GROUND) {
            var_s3 = true;
        }
        params = self->params & 0xF;
        if (D_us_80180EDC & (1 << params)) {
            var_s3 = true;
        }
        if (var_s3) {
            D_us_80180EDC |= 1 << params;
            if (params == 1) {
                params = params + 1;
                if (D_us_80180EDC & (1 << params)) {
                    self->params = 0x101;
                } else {
                    self->params = 1;
                }
                D_us_80180EDC |= 1 << params;
            } else if (params == 2) {
                params = params - 1;
                if (D_us_80180EDC & (1 << params)) {
                    self->params = 0x202;
                } else {
                    self->params = 2;
                }
                D_us_80180EDC |= 1 << params;
            }
            self->pose = 1;
            self->poseTimer = 1;
            PlaySfxPositional(SFX_WALL_DEBRIS_B);
            self->step++;
        }
        break;

    case 2:
        if (!--self->poseTimer) {
            self->poseTimer = 4;
            BreakBridge(self->pose);
            self->pose++;
            if (self->pose > 3) {
                self->step++;
            }
        }
        break;

    case 3:
        DropBridgePiece();
        var_s3 = (self->params >> 8) - 1;
        for (i = 0; i < 2; i++) {
            if (var_s3 != i) {
                entity = AllocEntity(
                    &g_Entities[224], &g_Entities[TOTAL_ENTITY_COUNT]);
                if (entity != NULL) {
                    CreateEntityFromEntity(E_EXPLOSION, self, entity);
                    entity->params = 0x13;
                    entity->posX.i.hi += -64 + (i << 7);
                }
            }
        };
        self->velocityY = FIX(2.0);
        self->drawFlags = ENTITY_ROTATE;
        params = self->params & 0xF;
        if ((params == 0) || (params == 3)) {
            self->zPriority = 0x6E;
        }
        self->step++;
        // fallthrough

    case 4:
        var_s3 = self->params >> 8;
        if (var_s3 == 1) {
            self->rotate -= 8;
        } else if (var_s3 == 2) {
            self->rotate += 8;
        } else {
            self->rotate -= 4;
        }

        if (UnkCollisionFunc3(D_us_80180EE0) & 1) {
            PlaySfxPositional(SFX_FIREBALL_SHOT_A);
            self->step++;
        }
        break;

    case 5:
        for (i = 0; i < 16; i++) {
            entity =
                AllocEntity(&g_Entities[224], &g_Entities[TOTAL_ENTITY_COUNT]);
            if (entity != NULL) {
                CreateEntityFromEntity(E_ID(EXPLODE_PUFF_OPAQUE), self, entity);
                entity->params = 0x10;
                entity->zPriority = 0x72;
                entity->posX.i.hi += (Random() & 0x7F) - 64;
                entity->posY.i.hi += (Random() & 0xF) + 12;
            }
        }
        self->drawFlags |= ENTITY_OPACITY;
        self->opacity = 0x40;
        self->step++;
        break;
    }
}

void EntityBridgeBackgroundPiece(Entity* self) {
    Primitive* prim;
    s32 primIndex;
    DRAWENV sp10;
    RECT clipRect;
    DR_ENV* dr_env;
    s32 temp_t1;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitInteractable);
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 2);
        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags |= FLAG_HAS_PRIMS;
        self->primIndex = primIndex;
        prim = &g_PrimBuf[primIndex];
        self->ext.prim = prim;

        dr_env = g_api.func_800EDB08((POLY_GT4*)prim);
        if (dr_env == NULL) {
            DestroyEntity(self);
            return;
        }

        prim->type = PRIM_ENV;
        sp10 = g_CurrentBuffer->draw;
        sp10.isbg = 0;
        sp10.r0 = 0;
        sp10.g0 = 0;
        sp10.b0 = 0;
        sp10.dtd = 0;
        sp10.ofs[0] = 0;
        clipRect.x = 0;
        clipRect.w = 256;
        clipRect.y = 20;
        clipRect.h = 0xCF;
        sp10.clip = clipRect;
        SetDrawEnv(dr_env, &sp10);
        prim->priority = 0x6D;
        prim->drawMode = DRAW_UNK_1000 | DRAW_HIDE;
        prim = prim->next;
        dr_env = g_api.func_800EDB08((POLY_GT4*)prim);
        if (dr_env == NULL) {
            DestroyEntity(self);
            return;
        }
        prim->type = PRIM_ENV;
        prim->drawMode = DRAW_UNK_800 | DRAW_HIDE;
        prim->priority = 0x6F;
        prim = prim->next;
        // fallthrough

    case 1:
        prim = self->ext.prim;
        temp_t1 = 0x4D0 - g_Tilemap.scrollY.i.hi;
        if (temp_t1 > 0xE3) {
            prim->drawMode |= DRAW_HIDE;
            prim = prim->next;
            prim->drawMode |= DRAW_HIDE;
        } else {
            // n.b.! this can't be right...
            dr_env = *((DR_ENV**)&prim->r1);
            sp10 = g_CurrentBuffer->draw;
            sp10.isbg = 0;
            sp10.ofs[0] = 0;
            clipRect.x = 0;
            clipRect.w = 256;
            clipRect.y = 0x14;
            clipRect.h = temp_t1 - 0x15;
            FntPrint("cut y:%x\n", clipRect.h + 0x15);
            sp10.clip = clipRect;
            SetDrawEnv(dr_env, &sp10);
            prim->drawMode = DRAW_UNK_1000;
            prim = prim->next;
            prim->drawMode = DRAW_UNK_800;
            prim = prim->next;
        }
        break;
    }
}
