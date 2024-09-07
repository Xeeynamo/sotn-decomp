// SPDX-License-Identifier: AGPL-3.0-or-later
#include "st0.h"
#include "sfx.h"

void EntityStageTitleFadeout(Entity* self) {
    s16 primIndex;
    Primitive* prim;
    s32 temp_a0;
    s32 temp_a1;
    s32 posX;

    switch (self->step) {
    case 0:
        if (D_80180908 != 0) {
            DestroyEntity(self);
            return;
        }

        InitializeEntity(D_801805D4);
        primIndex = g_api.AllocPrimitives(PRIM_G4, 5);
        if (primIndex != -1) {
            prim = &g_PrimBuf[primIndex];
            self->primIndex = primIndex;
            self->ext.stageTitleCard.prim = prim;
            self->flags |= FLAG_HAS_PRIMS;
            while (prim != NULL) {
                prim->drawMode = DRAW_HIDE;
                prim = prim->next;
            }
            prim = self->ext.stageTitleCard.prim;
            prim->r0 = prim->g0 = prim->b0 = 0;
            prim->x1 = prim->x3 = 0x100;
            prim->y2 = prim->y3 = 0xF0;
            prim->priority = 0x1FD;
            prim->y0 = prim->y1 = prim->x0 = prim->x2 = 0;
            prim->drawMode = DRAW_DEFAULT;
            LOW(prim->r1) = LOW(prim->r0);
            LOW(prim->r2) = LOW(prim->r0);
            LOW(prim->r3) = LOW(prim->r0);
            self->ext.stageTitleCard.unk88 = 0x20;
        } else {
            DestroyEntity(self);
            break;
        }

    case 1:
        if (D_80180908 != 0) {
            prim = self->ext.stageTitleCard.prim;
            prim->r0 = prim->g0 = prim->b0 = 247;
            prim->drawMode = 0x51;
            LOW(prim->r1) = LOW(prim->r0);
            LOW(prim->r2) = LOW(prim->r0);
            LOW(prim->r3) = LOW(prim->r0);
            self->step++;
        }
        break;

    case 2:
        prim = self->ext.stageTitleCard.prim;
        prim = prim->next;
        prim->r0 = prim->g0 = prim->b0 = 0;
        prim->priority = 0xC0;
        prim->x1 = prim->x3 = 0x100;
        prim->y2 = prim->y3 = 0xF0;
        prim->drawMode = DRAW_DEFAULT;
        prim->y0 = prim->y1 = prim->x0 = prim->x2 = 0;
        LOW(prim->r1) = LOW(prim->r0);
        LOW(prim->r2) = LOW(prim->r0);
        LOW(prim->r3) = LOW(prim->r0);
        PLAYER.zPriority = 0xD0;
        self->step++;

    case 3:
        PLAYER.zPriority = 0xD0;
        prim = self->ext.stageTitleCard.prim;
        prim->r0 += 248;
        if (prim->r0 > 248) {
            prim->r0 = 0;
            prim->drawMode = DRAW_HIDE;
            prim = prim->next;
            prim->drawMode = DRAW_DEFAULT;
            self->step = 5;
            break;
        }
        prim->g0 = prim->b0 = LOW(prim->r0);
        LOW(prim->r1) = LOW(prim->r0);
        LOW(prim->r2) = LOW(prim->r0);
        LOW(prim->r3) = LOW(prim->r0);
        break;

    case 4:
        PLAYER.zPriority = 0xD0;
        prim = self->ext.stageTitleCard.prim;
        prim = prim->next;
        prim->r0 += 248;
        if (prim->r0 > 248) {
            prim->r0 = 0;
            prim->drawMode = DRAW_HIDE;
            PLAYER.zPriority = g_unkGraphicsStruct.g_zEntityCenter;
            self->step = 1;
        }
        prim->g0 = prim->b0 = LOW(prim->r0);
        LOW(prim->r1) = LOW(prim->r0);
        LOW(prim->r2) = LOW(prim->r0);
        LOW(prim->r3) = LOW(prim->r0);
        break;

    case 5:
        prim = self->ext.stageTitleCard.prim;
        while (prim != NULL) {
            prim->y0 = prim->y1 = 0;
            prim->y2 = prim->y3 = 0xF0;
            prim->priority = 0xB0;
            prim->drawMode = 0x55;
            prim->r0 = prim->g0 = prim->b0 = 255;
            LOW(prim->r1) = LOW(prim->r0);
            LOW(prim->r2) = LOW(prim->r0);
            LOW(prim->r3) = LOW(prim->r0);
            prim = prim->next;
        }
        prim = self->ext.stageTitleCard.prim;
        prim->x0 = prim->x2 = 0;

        prim = prim->next;
        prim->r0 = prim->g0 = prim->b0 = 255;
        prim->r1 = prim->g1 = prim->b1 = 0;
        LOW(prim->r2) = LOW(prim->r0);
        LOW(prim->r3) = LOW(prim->r1);

        prim = prim->next;
        prim->x1 = prim->x3 = 0x100;

        prim = prim->next;
        prim->r0 = prim->g0 = prim->b0 = 0;
        prim->r1 = prim->g1 = prim->b1 = 255;
        LOW(prim->r2) = LOW(prim->r0);
        LOW(prim->r3) = LOW(prim->r1);

        posX = PLAYER.posX.i.hi;
        self->ext.stageTitleCard.unk88 = 32;
        self->ext.stageTitleCard.unk84 = posX;
        self->ext.stageTitleCard.unk80 = posX;
        self->step++;

    case 6:
        if (self->ext.stageTitleCard.unk88 != 0) {
            self->ext.stageTitleCard.unk88--;
            if (self->ext.stageTitleCard.unk88 == 0) {
                g_Entities[PLAYER_CHARACTER].zPriority =
                    g_unkGraphicsStruct.g_zEntityCenter;
            }
        }
        temp_a0 = self->ext.stageTitleCard.unk80;
        temp_a1 = self->ext.stageTitleCard.unk84;
        prim = self->ext.stageTitleCard.prim;
        temp_a0 -= 4;
        temp_a1 += 4;
        prim->x1 = prim->x3 = temp_a0;

        prim = prim->next;
        prim->x0 = prim->x2 = temp_a0;
        prim->x1 = prim->x3 = temp_a0 + 0x40;

        prim = prim->next;
        prim->x0 = prim->x2 = temp_a1;

        prim = prim->next;
        prim->x1 = prim->x3 = temp_a1;
        prim->x0 = prim->x2 = temp_a1 - 0x40;

        if ((temp_a0 < -0x40) && (temp_a1 > 0x140)) {

            for (prim = self->ext.stageTitleCard.prim; prim != NULL;
                 prim = prim->next) {
                prim->drawMode = DRAW_HIDE;
            }
            PreventEntityFromRespawning(self);
            DestroyEntity(self);
            break;
        }
        self->ext.stageTitleCard.unk80 = temp_a0;
        self->ext.stageTitleCard.unk84 = temp_a1;
        break;
    }
}

void EntityStageTitleCard(Entity* self) {
    Entity* fakeEntity; // !FAKE
    s16 primIndex;
    Primitive* prim;
    VertexFake* v;
    s16 temp_unk8E;
    s32 var_s7;
    s16 angle;
    s32 i;
    s32 j;

    switch (self->step) {
    case 0:
        if (D_80180908 == 0) {
            InitializeEntity(D_801805D4);
            primIndex = g_api.AllocPrimitives(PRIM_GT4, 8);
            if (primIndex == -1) {
                D_80180908 = 1;
            label:
                DestroyEntity(self);
                return;
            }
            prim = &g_PrimBuf[primIndex];
            self->primIndex = primIndex;
            self->ext.stageTitleCard.prim = prim;
            self->flags |= FLAG_HAS_PRIMS;
            prim->type = PRIM_GT3;
            prim->tpage = 0x1A;
            prim->clut = 0x15F;
            prim->v2 = prim->v3 = prim->u1 = prim->u3 = 0x18;
            prim->r0 = prim->g0 = 8;
            prim->b0 = 0x60;
            prim->priority = 0x1FE;
            prim->v0 = prim->v1 = prim->u0 = prim->u2 = 0x10;
            prim->drawMode = DRAW_COLORS;
            LOW(prim->r1) = LOW(prim->r0);
            LOW(prim->r2) = LOW(prim->r0);

            prim = prim->next;
            prim->u1 = prim->u3 = 0x6F;
            prim->tpage = 0x11;
            prim->clut = 0x210;
            prim->v0 = prim->v1 = prim->u0 = prim->u2 = 0;
            prim->v2 = prim->v3 = 0xF;
            prim->x0 = prim->x2 = -0x6F;
            prim->y0 = prim->y1 = 0x70;
            prim->priority = 0x1FF;
            prim->drawMode = DRAW_DEFAULT;
            prim->x1 = prim->x3 = 0;
            prim->y2 = prim->y3 = 0x7F;

            prim = prim->next;
            prim->u1 = prim->u3 = 0x7F;
            prim->v2 = prim->v3 = 0x2A;
            prim->x0 = prim->x2 = 0x100;
            prim->x1 = prim->x3 = 0x17F;
            prim->y0 = prim->y1 = 0x80;
            prim->tpage = 0x11;
            prim->clut = 0x210;
            prim->u0 = prim->u2 = 0;
            prim->v0 = prim->v1 = 0x10;
            prim->priority = 0x1FF;
            prim->drawMode = DRAW_DEFAULT;
            prim->y2 = prim->y3 = 0x9A;

            prim = prim->next;
            while (prim != NULL) {
                prim->drawMode = DRAW_HIDE;
                prim = prim->next;
            }
            D_8003C8B8 = 0;
            self->ext.stageTitleCard.unk88 = 0x10;
        } else {
            goto label;
        }

    case 1:
        if (--self->ext.stageTitleCard.unk88 == 0) {
            self->step++;
        }
        g_Player.D_80072EFC = 4;
        g_Player.padSim = 0;
        break;

    case 2:
        prim = self->ext.stageTitleCard.prim;
        self->ext.stageTitleCard.unk8E += 6;
        if (self->ext.stageTitleCard.unk8E > 0x20) {
            self->ext.stageTitleCard.unk8E = 0x20;
            var_s7 = 1;
        } else {
            var_s7 = 0;
        }

        temp_unk8E = self->ext.stageTitleCard.unk8E;
        angle = self->ext.stageTitleCard.unk8C + 0x400;

        v = (VertexFake*)&prim->x0;
        for (i = 0; i < 3; i++) {
            v->x = (temp_unk8E * rcos(angle) >> 0xC) + 0x60;
            v->y = (temp_unk8E * rsin(angle) >> 0xC) + 0x80;
            angle += 0x555;
            v++;
        }

        prim = prim->next;
        if (prim->x0 < 0x40) {
            prim->x0 = prim->x0 + 8;
        } else {
            prim->x0 = 0x40;
            var_s7++;
        }
        prim->x2 = prim->x0;
        prim->x1 = prim->x3 = prim->x0 + 0x6F;

        prim = prim->next;
        if (prim->x0 > 0x40) {
            prim->x0 -= 6;
        } else {
            prim->x0 = 0x40;
            var_s7++;
        }
        prim->x2 = prim->x0;
        prim->x1 = prim->x3 = prim->x0 + 0x7F;

        if (var_s7 == 3) {
            self->step++;
        }
        g_Player.D_80072EFC = 4;
        g_Player.padSim = 0;
        break;

    case 3:
        prim = self->ext.stageTitleCard.prim;
        prim->drawMode |= 0x31;

        prim = prim->next;
        prim->u1 = prim->u3 = 0x7F;
        prim->v2 = prim->v3 = 0x2A;
        prim->x0 = prim->x2 = 0x40;
        prim->x1 = prim->x3 = 0xBF;
        prim->y0 = prim->y1 = 0x70;
        prim->y2 = prim->y3 = 0x9A;
        prim->r0 = prim->g0 = prim->b0 = 0x80;
        prim->v0 = prim->v1 = prim->u0 = prim->u2 = 0;
        prim->drawMode = 0x35;
        LOW(prim->r1) = LOW(prim->r0);
        LOW(prim->r2) = LOW(prim->r0);
        LOW(prim->r3) = LOW(prim->r0);

        for (prim = prim->next; prim != NULL; prim = prim->next) {
            prim->drawMode = DRAW_HIDE;
        }
        self->ext.stageTitleCard.unk88 = 0x20;
        self->step++;
        g_Player.D_80072EFC = 4;
        g_Player.padSim = 0;
        break;

    case 4:
        if (self->ext.stageTitleCard.unk88 == 0x10) {
            D_80180908 = 1;
        }
        if (--self->ext.stageTitleCard.unk88 == 0) {
            self->step++;
        }
        g_Player.D_80072EFC = 4;
        g_Player.padSim = 0;
        return;

    case 5:
        prim = self->ext.stageTitleCard.prim;
        angle = self->ext.stageTitleCard.unk8C + 0x400;
        self->ext.stageTitleCard.unk8C -= 4;
        temp_unk8E = self->ext.stageTitleCard.unk8E;

        fakeEntity = self; // !FAKE

        v = (VertexFake*)&prim->x0;
        for (j = 0; j < 3; j++) {
            v->x = (temp_unk8E * rcos(angle) >> 0xC) + 0x60;
            v->y = (temp_unk8E * rsin(angle) >> 0xC) + 0x80;
            angle += 0x555;
            v++;
        }

        PrimDecreaseBrightness(prim, 4);
        if (PrimDecreaseBrightness(prim->next, 3) == 0) {
            PreventEntityFromRespawning(fakeEntity);
            D_8003C8B8 = 1;
            DestroyEntity(fakeEntity);
        }
    default:
        g_Player.D_80072EFC = 4;
        g_Player.padSim = 0;
        break;
    }
}

// Helper function for EntityDracula
u32 func_801ABBBC(s32 step, Entity* dracula) {
    draculaPrimitive* prim;
    s32 randVar;
    s32 randVar2;
    s32 colorLimit;
    s32 var_a1;
    s32 var_a2;
    s32 var_a3;
    s32 i;
    s32 var_t0;
    s32 fake_a2;
    s32 color;
    u8* redPtr;
    u8* greenPtr;
    u8 constFF;

    switch (step) {
    case 0:
        prim = dracula->ext.dracula.prim;
        dracula->ext.dracula.unk80 = prim;
        for (i = 0; i < 16; i++) {
            prim->type = PRIM_LINE_G2_ALT;
            if (i == 15) {
                prim->type = PRIM_LINE_G2;
            }
            if (i & 1) {
                prim->x0 = prim->x1 = dracula->posX.i.hi + i / 2;
            } else {
                prim->x0 = prim->x1 = dracula->posX.i.hi - i / 2;
            }

            prim->y0 = prim->y1 = 0;
            prim->r0 = prim->g0 = prim->b0 = 0x70;
            prim->r1 = prim->g1 = prim->b1 = 0;
            randVar = Random();
            prim->r2 = (((randVar & 1) * 0x10) + 0x10);
            prim->g2 = (((randVar * 8) & 0x10) + 0x10);
            prim->b2 = (((randVar * 4) & 0x10) + 0x10);
            prim->priority = dracula->zPriority + 2;
            prim->drawMode = 0x33;
            if (i == 0) {
                prim->drawMode = DRAW_HIDE;
            }
            prim = prim->next;
        }
        step++;
        dracula->ext.dracula.unk90 = 1;
        dracula->ext.dracula.unk92 = 0;
        dracula->ext.dracula.unk8C = 0;
        break;
    case 1:
        if (dracula->ext.dracula.unk8C++ >= 3) {
            dracula->ext.dracula.unk90 += 2;
            if (dracula->ext.dracula.unk90 >= 16) {
                dracula->ext.dracula.unk90 = 16;
            }
            dracula->ext.dracula.unk8C = 0;
        }
        prim = dracula->ext.dracula.unk80;
        i = 0;
        for (i = 0; i < dracula->ext.dracula.unk90; i++) {
            prim->y1 += 0x30;
            if (dracula->ext.dracula.unkA1 != 0) {
                if (prim->y1 >= 171) {
                    prim->y1 = 171;
                }
            } else if (prim->y1 >= 203) {
                prim->y1 = 203;
            }
            // Iterate through r1, g1, and b1.
            for (redPtr = &prim->r1, var_a1 = 0; var_a1 < 3; redPtr++,
                var_a1++) {
                color = *redPtr;
                if (color < 0xFF) {
                    // This ends up offsetting to r2, g2, and b2
                    color += redPtr[0xC];
                    if (color > 0xFF) {
                        color = 0xFF;
                    }
                }
                *redPtr = color;
            }
            prim = prim->next;
        }
        if (dracula->ext.dracula.unk92++ >= 25) {
            dracula->ext.dracula.unk92 = 0;
            step++;
        }
        break;
    case 2:
        prim = dracula->ext.dracula.unk80;
        for (i = 0; i < 16; i++) {
            prim = prim->next;
        }
        dracula->ext.dracula.unk84 = prim;
        for (i = 0; i < 48; i++) {
            prim->type = PRIM_LINE_G2_ALT;
            if (i == 47) {
                prim->type = PRIM_LINE_G2;
            }
            prim->r0 = prim->g0 = prim->b0 = 0x70;
            prim->r1 = prim->g1 = prim->b1 = 0x20;
            randVar2 = Random();
            prim->r2 = (((randVar2 & 1) * 4) + 4);
            prim->g2 = (((randVar2 * 2) & 4) + 4);
            prim->b2 = ((randVar2 & 4) + 4);
            if (i & 1) {
                prim->x0 = prim->x1 = dracula->posX.i.hi + i / 2;
            } else {
                prim->x0 = prim->x1 = dracula->posX.i.hi - i / 2;
            }
            if (dracula->ext.dracula.unkA1 != 0) {
                prim->y0 = prim->y1 = 171;
                if (i >= 0x22) {
                    prim->y0 = prim->y1 = -0x20;
                }
            } else {
                prim->y0 = prim->y1 = 203;
            }
            prim->y1_f32.i.lo = 0;
            prim->y1_f32.i.hi = prim->y1;
            // FAKE variable reuse
            color = (i >> 1);
            prim->y1_f32_velocity.val =
                ((color * color * color) << 8) + 0x80000;
            prim->priority = dracula->zPriority + 2;
            prim->drawMode = 0x33;
            if (i == 0) {
                prim->drawMode = DRAW_HIDE;
            }
            prim = prim->next;
        }
        step++;
        dracula->ext.dracula.unk8C = 0;
        g_api.PlaySfx(SFX_TELEPORT_BANG_B);
        break;
    case 3:
        prim = dracula->ext.dracula.unk84;
        if (dracula->ext.dracula.unkA1 != 0) {
            var_a1 = 0x22;
        } else {
            var_a1 = 0x30;
        }
        for (i = 0; i < var_a1; prim = prim->next) {
            prim->y1_f32.i.hi = prim->y1;
            prim->y1_f32.val -= prim->y1_f32_velocity.val;
            prim->y1 = prim->y1_f32.i.hi;
            i++;
            if (prim->y1 < 0) {
                prim->y1 = 0U;
            }
        }
        if (++dracula->ext.dracula.unk8C < 9) {
            prim = dracula->ext.dracula.unk80;
            for (i = 0; i < 16 - (dracula->ext.dracula.unk8C * 2); i++) {
                prim = prim->next;
            }
            for (; i < 16; i++) {
                prim->drawMode = DRAW_HIDE;
                prim = prim->next;
            }
        }
        prim = dracula->ext.dracula.unk84;
        for (i = 0, constFF = 0xFF, colorLimit = 0xFF; i < 48; i++) {
            color = prim->r0;
            color += 4;
            prim->r0 = (color > colorLimit ? colorLimit : color);
            colorLimit -= 2;
            if (prim->r0 >= 0xFF) {
                prim->r0 = constFF;
                step = 4;
            }
            prim->b0 = prim->g0 = prim->r0;
            prim = prim->next;
        }
        var_a2 = 0xFF;
        prim = dracula->ext.dracula.unk84;
        for (i = 0; i < 48; i++) {
            redPtr = &prim->r1;
            for (var_a1 = 0; var_a1 < 3; var_a1 += 1) {
                color = *redPtr;
                color += redPtr[0xC];
                if (var_a2 < color) {
                    color = var_a2;
                }
                *redPtr = color;
                redPtr++;
            }
            prim = prim->next;
            var_a2 -= 2;
        }
        break;
    case 4:
        var_t0 = 1;
        prim = dracula->ext.dracula.unk84;
        for (i = 0, var_a3 = 0xFF; i < 48; i++) {

            for (redPtr = &prim->r1, var_a1 = 0, var_a2 = var_a3; var_a1 < 3;
                 redPtr++, var_a1++) {
                color = *redPtr;
                color += 0x18;
                if (var_a2 < color) {
                    color = var_a2;
                } else {
                    var_t0 = 0;
                }
                *redPtr = color;
            }
            prim = prim->next;
            var_a3 -= 2;
        }
        if (var_t0 != 0) {
            step = 5;
        }
        break;
    case 5:
        prim = dracula->ext.dracula.unk80;
        // @bug: They forgot to do prim = prim->next in this loop!
        for (i = 0; i < 16; i++) {
            prim->drawMode = DRAW_HIDE;
        }
        prim = dracula->ext.dracula.unk80;
        prim->type = PRIM_TILE;
        prim->r0 = prim->g0 = prim->b0 = 0;
        prim->y0 = 0;
        if (dracula->ext.dracula.unkA1 != 0) {
            prim->x0 = dracula->posX.i.hi - 17;
            prim->u0 = 0x22;
            prim->v0 = 0xAC;
        } else {
            prim->x0 = dracula->posX.i.hi - 24;
            prim->u0 = 0x30;
            prim->v0 = 0xCC;
        }
        step++;
        prim->priority = dracula->zPriority + 1;
        prim->drawMode = 0x53;
        dracula->ext.dracula.unk8C = 0;
        break;
    case 6:
        var_t0 = 1;
        prim = dracula->ext.dracula.unk84;
        for (i = 0; i < 48; i++) {
            redPtr = &prim->r0;
            var_a1 = 0;
            greenPtr = &prim->g0;
            for (; var_a1 < 2;) {
                color = *redPtr;
                color -= 10;
                if (color < 0) {
                    color = 0;
                } else {
                    var_t0 = 0;
                }
                var_a1++;
                greenPtr[0] = greenPtr[1] = color;
                greenPtr += 0xC;
                *redPtr = color;
                redPtr += 0xC;
            }
            prim = prim->next;
        }
        prim = dracula->ext.dracula.unk80;
        prim->r0 += 7;
        if (prim->r0 > 0xE0) {
            prim->r0 = 0xE0;
        } else {
            var_t0 = 0;
        }
        prim->g0 = prim->b0 = prim->r0;
        if (var_t0 != 0) {
            prim = dracula->ext.dracula.unk84;
            for (i = 0; i < 48; i++) {
                prim->drawMode = DRAW_HIDE;
                prim = prim->next;
            }
            step++;
            dracula->drawFlags = DRAW_HIDE;
            dracula->unk6C = 0;
            dracula->ext.dracula.unkA0 = 1;
        }
        break;
    case 7:
        prim = dracula->ext.dracula.unk80;
        color = prim->r0;
        color -= 16;
        if (color < 0) {
            color = 0;
        }
        prim->g0 = prim->b0 = prim->r0 = color;
        if (prim->r0 < 16) {
            prim->drawMode = DRAW_HIDE;
            step++;
        }
        break;
    case 8:
        dracula->unk6C += 10;
        if (dracula->unk6C >= 0x80U) {
            step++;
            dracula->unk6C = 0x80U;
            dracula->drawFlags = 0;
        }
        break;
    case 9:
        prim = dracula->ext.dracula.prim;
        while (prim != NULL) {
            prim->drawMode = DRAW_HIDE;
            prim = prim->next;
        }
        step = 0xFF;
        if (dracula->ext.dracula.unkA1 != 0) {
            dracula->ext.dracula.unkA1 = 0U;
        }
        break;
    }
    return step;
}

s32 func_801AC458(s16 arg0) {
    s32 ret = arg0;
    Entity* e;
    Entity* e2;

    switch (ret) {
    case 0:
        e = g_CurrentEntity;
        ret = 1;
        e[1].drawFlags = FLAG_DRAW_ROTY;
        e[1].rotY = 0x600;
        e[1].animFrameIdx = 0;
        e[1].animFrameDuration = 0;
        e[1].step = 2;
        e[1].posX.i.hi = e->posX.i.hi;
        e[1].posY.i.hi = e->posY.i.hi + 16;

    case 1:
        e2 = &g_CurrentEntity[1];
        if (AnimateEntity(D_80180964, e2) == 0) {
            ret++;
        }
        if (e2->animFrameIdx == 6 && e2->animFrameDuration == 0) {
            g_CurrentEntity->ext.stub[0x24] = 1;
        }
        break;

    case 2:
        e = &g_CurrentEntity[1];
        e->animCurFrame = 0;
        e->drawFlags = 0;
        e->step = 1;
        ret = 0xFF;
        break;
    }
    return ret;
}
