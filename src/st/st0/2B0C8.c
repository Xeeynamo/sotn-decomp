REDACTED
#include "sfx.h"
REDACTED
REDACTED
    s16 primIndex;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
        if (D_80180908 != 0) {
            DestroyEntity(self);
            return;
        }

        InitializeEntity(D_801805D4);
        primIndex = g_api.AllocPrimitives(PRIM_G4, 5);
        if (primIndex != -1) {
            prim = &g_PrimBuf[primIndex];
            self->primIndex = primIndex;
REDACTED
            self->flags |= FLAG_HAS_PRIMS;
            while (prim != NULL) {
                prim->drawMode = DRAW_HIDE;
                prim = prim->next;
REDACTED
REDACTED
            prim->r0 = prim->g0 = prim->b0 = 0;
            prim->x1 = prim->x3 = 0x100;
            prim->y2 = prim->y3 = 0xF0;
            prim->priority = 0x1FD;
            prim->y0 = prim->y1 = prim->x0 = prim->x2 = 0;
            prim->drawMode = DRAW_DEFAULT;
REDACTED
REDACTED
REDACTED
            self->ext.stageTitleCard.unk88 = 0x20;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
            prim->drawMode = 0x51;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
        prim->drawMode = DRAW_DEFAULT;
REDACTED
        LOW(prim->r1) = LOW(prim->r0);
        LOW(prim->r2) = LOW(prim->r0);
        LOW(prim->r3) = LOW(prim->r0);
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
            prim->drawMode = DRAW_HIDE;
REDACTED
            prim->drawMode = DRAW_DEFAULT;
REDACTED
REDACTED
REDACTED
REDACTED
        LOW(prim->r1) = LOW(prim->r0);
        LOW(prim->r2) = LOW(prim->r0);
        LOW(prim->r3) = LOW(prim->r0);
        break;

    case 4:
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
            prim->drawMode = DRAW_HIDE;
            PLAYER.zPriority = g_unkGraphicsStruct.g_zEntityCenter;
REDACTED
REDACTED
REDACTED
        LOW(prim->r1) = LOW(prim->r0);
        LOW(prim->r2) = LOW(prim->r0);
        LOW(prim->r3) = LOW(prim->r0);
        break;

REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
            prim->drawMode = 0x55;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
                    g_unkGraphicsStruct.g_zEntityCenter;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED

            for (prim = self->ext.stageTitleCard.prim; prim != NULL;
                 prim = prim->next) {
                prim->drawMode = DRAW_HIDE;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
    s16 primIndex;
REDACTED
    VertexFake* v;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
            primIndex = g_api.AllocPrimitives(PRIM_GT4, 8);
            if (primIndex == -1) {
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
            prim = &g_PrimBuf[primIndex];
            self->primIndex = primIndex;
REDACTED
            self->flags |= FLAG_HAS_PRIMS;
            prim->type = PRIM_GT3;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
            prim->drawMode = DRAW_COLORS;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
            prim->drawMode = DRAW_DEFAULT;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
            prim->drawMode = DRAW_DEFAULT;
REDACTED
REDACTED
REDACTED
REDACTED
                prim->drawMode = DRAW_HIDE;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
        g_Player.padSim = 0;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
        v = (VertexFake*)&prim->x0;
REDACTED
            v->x = (temp_unk8E * rcos(angle) >> 0xC) + 0x60;
            v->y = (temp_unk8E * rsin(angle) >> 0xC) + 0x80;
REDACTED
            v++;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
        g_Player.padSim = 0;
REDACTED
REDACTED
REDACTED
REDACTED
        prim->drawMode |= 0x31;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
        prim->drawMode = 0x35;
        LOW(prim->r1) = LOW(prim->r0);
        LOW(prim->r2) = LOW(prim->r0);
        LOW(prim->r3) = LOW(prim->r0);
REDACTED
        for (prim = prim->next; prim != NULL; prim = prim->next) {
            prim->drawMode = DRAW_HIDE;
REDACTED
REDACTED
REDACTED
REDACTED
        g_Player.padSim = 0;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
        g_Player.padSim = 0;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
        v = (VertexFake*)&prim->x0;
REDACTED
            v->x = (temp_unk8E * rcos(angle) >> 0xC) + 0x60;
            v->y = (temp_unk8E * rsin(angle) >> 0xC) + 0x80;
REDACTED
            v++;
REDACTED
REDACTED
        PrimDecreaseBrightness(prim, 4);
        if (PrimDecreaseBrightness(prim->next, 3) == 0) {
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
        g_Player.padSim = 0;
REDACTED
REDACTED
REDACTED
REDACTED
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
REDACTED
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
REDACTED
REDACTED
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
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
        e[1].drawFlags = FLAG_DRAW_ROTY;
        e[1].rotY = 0x600;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
        if (e2->animFrameIdx == 6 && e2->animFrameDuration == 0) {
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
        e->drawFlags = 0;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
}
