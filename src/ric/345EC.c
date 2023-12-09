#include "ric.h"

void func_801705EC(Entity* entity) {
    u16 temp;

    switch (entity->step) {
    case 0:
        entity->flags = FLAG_UNK_04000000;
        entity->ext.generic.unk7E.modeU16 = 0;
        entity->step++;

    case 1:
    case 3:
    case 5:
    case 7:
        temp = entity->ext.generic.unk7E.modeU16 + 1;
        entity->ext.generic.unk7E.modeU16 = temp;
        func_801606BC(entity, (temp << 0x10) | 0x3F, 0);
        entity->ext.generic.unk7C.s = 0;
        entity->step++;
        break;

    case 2:
    case 4:
    case 6:
        entity->ext.generic.unk7C.s++;
        if (entity->ext.generic.unk7C.s >= 16) {
            entity->step++;
        }
        break;

    case 8:
        DestroyEntity(entity);
        break;
    }
}

s16 func_801706C0(u16* arg0, s16 arg1, s16 arg2, s16* arg3) {
    s16 temp_s3;
    s16 s3_offset = 0x80;
    s8 arg2_copy = arg2;

    temp_s3 = arg1 - s3_offset + rand() % 256;
    *arg3 = (rand() % 48) + 0x10;
    arg0[0] = arg0[1];
    arg0[2] = arg0[3];
    if (arg2 != 0) {
        arg0[1] = arg0[1] + ((rcos(temp_s3) * *arg3) >> 0xC);
        arg0[3] = arg0[3] + ((rsin(temp_s3) * *arg3) >> 0xC);
        if (arg2_copy & 1) {
            return func_801706C0(arg0, (temp_s3 - 0x140), arg2 / 2, arg3);
        } else {
            rand();
            rand();
            return func_801706C0(arg0, (temp_s3 + 0x140), (arg2 - 1) / 2, arg3);
        }
    } else {
        return temp_s3;
    }
}

void func_80170874(s32 bufSize, s32* buf) {
    s32 i, idx, swapTemp;

    for (i = bufSize - 1; i > 0; i--) {
        // Pick random index
        idx = rand() % bufSize;

        // Hold swap value temporarily
        swapTemp = buf[i];
        buf[i] = buf[idx];
        buf[idx] = swapTemp;
    }
}

void func_8017091C(Entity* self) {
    u16 sp10[4];
    s16 sp18;
    u16 sp20;
    s32 temp_s0;
    s16 angle;
    s32 angleCos;
    s32 angleSin;
    s16 xCoord;
    s16 yCoord;
    Primitive* prim;
    s32 i;
    s32 randomSeed;
    s16 var_s4;
    s16 var_s6;

    switch (self->step) {
    case 0:
        self->primIndex = g_api.AllocPrimitives(PRIM_GT4, 0xF);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags = FLAG_UNK_04000000 | FLAG_HAS_PRIMS | FLAG_UNK_40000;
        prim = &g_PrimBuf[self->primIndex];
        for (i = 0; i < 15; i++) {
            prim->tpage = 0x1A;
            prim->clut = 0x194;
            prim->u0 = prim->u2 = (rand() % 5) * 0x10 - 0x70;
            prim->u1 = prim->u3 = prim->u0 + 0x20;
            if (rand() & 1) {
                prim->v0 = prim->v1 = 0xD0;
                prim->v2 = prim->v3 = 0xE0;
            } else {
                prim->v0 = prim->v1 = 0xE0;
                prim->v2 = prim->v3 = 0xD0;
            }
            prim->priority = 0xC1;
            prim->blendMode = 0x20C;
            prim->r0 = prim->g0 = prim->b0 = prim->r1 = prim->g1 = prim->b1 =
                prim->r2 = prim->g2 = prim->b2 = prim->r3 = prim->g3 =
                    prim->b3 = 0x80;
            prim = prim->next;
        }
        prim = &g_PrimBuf[self->primIndex];
        temp_s0 = self->params / 0x100 * 0x200;
        sp20 = (temp_s0)-0x100 + rand() % 0x200;
        randomSeed = rand();
        for (i = 0; i < 15; i++) {
            srand(randomSeed);
            sp10[1] = self->posX.i.hi;
            sp10[3] = self->posY.i.hi;
            angle = func_801706C0(&sp10, sp20, i, &sp18);
            xCoord = sp10[0];
            yCoord = sp10[2];
            var_s6 = (i == 0) ? 2 : 8;
            var_s4 = (i < 7) ? 8 : 2;

            angleCos = rcos(angle);
            angleSin = rsin(angle);
            prim->x0 = xCoord + (-(angleSin * -var_s6) >> 0xC);
            prim->y0 = yCoord + ((angleCos * -var_s6) >> 0xC);
            prim->x1 =
                xCoord + ((angleCos * sp18 - (angleSin * -var_s4)) >> 0xC);
            prim->y1 =
                yCoord + ((angleSin * sp18 + (angleCos * -var_s4)) >> 0xC);
            prim->x2 = xCoord + (-(angleSin * var_s6) >> 0xC);
            prim->y2 = yCoord + ((angleCos * var_s6) >> 0xC);
            prim->x3 =
                xCoord + ((angleCos * sp18 - (angleSin * var_s4)) >> 0xC);
            prim->y3 =
                yCoord + ((angleSin * sp18 + (angleCos * var_s4)) >> 0xC);
            prim = prim->next;
        }
        self->ext.et_8017091C.unk7E = 1;
        self->step++;
        return;
    case 1:
        prim = &g_PrimBuf[self->primIndex];
        for (i = 0; i < 15; i++) {
            prim->blendMode &= ~BLEND_VISIBLE;
            prim = prim->next;
        }
        self->step++;
    case 2:
        if (++self->ext.et_8017091C.unk7C >= 5) {
            prim = &g_PrimBuf[self->primIndex];
            for (i = 0; i < 15; i++) {
                prim->clut = 0x15F;
                prim->r0 = prim->g0 = prim->b0 = prim->r1 = prim->g1 =
                    prim->b1 = prim->r2 = prim->g2 = prim->b2 = prim->r3 =
                        prim->g3 = prim->b3 = 0xFF;
                prim->v0 = prim->v1 = prim->v0 - 0x10;
                // Seems fake but without this the registers get shuffled
                xCoord = prim->v2;
                prim->v2 = prim->v3 = xCoord - 0x10;
                prim = prim->next;
            }
            self->ext.et_8017091C.unk7C = 0;
            self->step++;
            return;
        }
        break;
    case 3:
    case 5:
        prim = &g_PrimBuf[self->primIndex];
        for (i = 0; i < 15; i++) {
            prim->clut = 0x194;
            prim = prim->next;
        }
        self->step++;
        return;
    case 4:
        prim = &g_PrimBuf[self->primIndex];
        for (i = 0; i < 15; i++) {
            prim->clut = 0x15F;
            prim = prim->next;
        }
        self->step++;
        return;
    case 6:
        prim = &g_PrimBuf[self->primIndex];
        for (i = 0; i < 15; i++) {
            prim->r0 = prim->g0 = prim->b0 = prim->r1 = prim->g1 = prim->b1 =
                prim->r2 = prim->g2 = prim->b2 = prim->r3 = prim->g3 =
                    prim->b3 = 0x60 - (self->ext.et_8017091C.unk7C * 4);
            prim = prim->next;
        }
        if (++self->ext.et_8017091C.unk7C >= 0x10) {
            DestroyEntity(self);
            return;
        }
        break;
    }
}

void func_80170F64(Entity* self) {
    Primitive* prim;
    s16 rand_angle;
    s16 xCoord;
    s16 yCoord;
    s32 quarterSelfY;
    s32 i;

    switch (self->step) {
    case 0:
        self->primIndex = g_api.AllocPrimitives(PRIM_GT4, 4);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            g_Player.unk4E = 1;
            return;
        }
        self->flags = FLAG_UNK_04000000 | FLAG_HAS_PRIMS | FLAG_UNK_40000;
        prim = &g_PrimBuf[self->primIndex];
        self->posX.i.hi = PLAYER.posX.i.hi;
        self->posY.i.hi = PLAYER.posY.i.hi - 0x20;
        quarterSelfY = self->posY.i.hi / 4;
        xCoord = self->posX.i.hi;
        yCoord = 0;
        for (i = 0; i < 4; i++) {
            prim->tpage = 0x1A;
            prim->clut = 0x194;
            prim->x0 = xCoord - 8;
            prim->x2 = xCoord + 8;
            prim->y0 = prim->y2 = yCoord;
            if (i < 3) {
                rand_angle = rand() % 0x100 + 0x380;
                xCoord += ((rcos(rand_angle) * quarterSelfY) >> 0xC);
                yCoord += ((rsin(rand_angle) * quarterSelfY) >> 0xC);
                prim->x1 = xCoord - 8;
                prim->x3 = xCoord + 8;
            } else {
                xCoord = self->posX.i.hi;
                yCoord = self->posY.i.hi;
                prim->x1 = xCoord - 4;
                prim->x3 = xCoord + 4;
            }
            prim->y1 = prim->y3 = yCoord;
            prim->u0 = prim->u2 = (rand() % 6) * 0x10 - 0x70;
            prim->u1 = prim->u3 = prim->u0 + 0x10;
            if (rand() & 1) {
                prim->v0 = prim->v1 = 0xD0;
                prim->v2 = prim->v3 = 0xE0;
            } else {
                prim->v0 = prim->v1 = 0xE0;
                prim->v2 = prim->v3 = 0xD0;
            }
            prim->priority = 0xC2;
            prim->blendMode = 0x200 | BLEND_VISIBLE;
            prim = prim->next;
        }
        self->ext.et_80170F64.unkB0 = 0x1A;
        func_8015FAB8(self);
        self->step++;
        break;
    case 1:
        prim = &g_PrimBuf[self->primIndex];
        for (i = 0; i < self->ext.et_80170F64.unk7C; i++) {
            prim = prim->next;
        }
        prim->blendMode &= ~BLEND_VISIBLE;
        if (++self->ext.et_80170F64.unk7C >= 4) {
            self->ext.et_80170F64.unk7C = 0;
            self->step++;
        }
        break;
    case 2:
        prim = &g_PrimBuf[self->primIndex];
        for (i = 0; i < self->ext.et_80170F64.unk7C; i++) {
            prim = prim->next;
        }
        if (self->ext.et_80170F64.unk7C == 0) {
            prim->blendMode = 0x235;
            prim->tpage = 0x1A;
            prim->clut = 0x19F;
            prim->u0 = prim->u2 = 0;
            prim->u1 = prim->u3 = 0x3F;
            prim->v0 = prim->v1 = 0xC0;
            prim->v2 = prim->v3 = 0xFF;
            prim->r0 = prim->g0 = prim->r1 = prim->g1 = prim->r2 = prim->g2 =
                prim->r3 = prim->g3 = 0x7F;
            prim->b0 = prim->b1 = prim->b2 = prim->b3 = 0xFF;
            self->ext.et_80170F64.unk7E = 1;
            self->ext.et_80170F64.unk80 = 2;
            self->ext.et_80170F64.unk82 = 0x64;
        } else {
            self->ext.et_80170F64.unk80 += 2;
            prim->blendMode |= BLEND_VISIBLE;
        }
        if (++self->ext.et_80170F64.unk7C >= 4) {
            // think this loop has to count down since we assign to i
            for (i = 7; i >= 0; i--) {
                D_801758B0[i] = i;
            }
            func_80170874(8, &D_801758B0[0]);
            self->ext.et_80170F64.unk7C = 0;
            g_api.PlaySfx(0x665);
            self->step++;
        }
        break;
    case 3:
        func_801606BC(
            self, FACTORY(D_801758B0[self->ext.et_80170F64.unk7C] * 0x100, 68),
            0);
        if (++self->ext.et_80170F64.unk7C >= 8) {
            self->hitboxHeight = self->hitboxWidth = 0x80;
            self->ext.et_80170F64.unk7C = 0;
            self->step++;
        }
        break;
    case 4:
        if (++self->ext.et_80170F64.unk7C >= 9) {
            self->step++;
        }
        break;
    case 5:
        self->ext.et_80170F64.unk80 += 2;
        self->ext.et_80170F64.unk82 -= 10;
        if (self->ext.et_80170F64.unk82 <= 0) {
            self->hitboxHeight = self->hitboxWidth = 0;
            self->step++;
        }
        break;
    case 6:
        g_Player.unk4E = 1;
        DestroyEntity(self);
        return;
    }
    if (self->ext.et_80170F64.unk7E != 0) {
        prim = &g_PrimBuf[self->primIndex];
        prim->x0 = prim->x2 = self->posX.i.hi - self->ext.et_80170F64.unk80;
        prim->x1 = prim->x3 = self->posX.i.hi + self->ext.et_80170F64.unk80;
        prim->y0 = prim->y1 = self->posY.i.hi - self->ext.et_80170F64.unk80;
        prim->y2 = prim->y3 = self->posY.i.hi + self->ext.et_80170F64.unk80;
        prim->r0 = prim->g0 = prim->r1 = prim->g1 = prim->r2 = prim->g2 =
            prim->r3 = prim->g3 = (self->ext.et_80170F64.unk82 * 0x7F) / 100;
        prim->b0 = prim->b1 = prim->b2 = prim->b3 =
            (self->ext.et_80170F64.unk82 * 0xFF) / 100;
    }
    return;
}

// Needs to be in between functions in this file with rodata
// Can remove once all rodata is pulled in.
const u32 rodataPadding_345EC = 0;

void func_8017161C(Entity* self) {
    Primitive* prim;
    s16 temp_s0_4;
    s32 sine;
    s32 cosine;
    s32 i;
    s16 yCoord;
    s16 xCoord;

    switch (self->step) {
    case 0:
        self->primIndex = g_api.AllocPrimitives(PRIM_GT4, 0x10);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags = FLAG_UNK_08000000 | FLAG_HAS_PRIMS;
        prim = &g_PrimBuf[self->primIndex];
        for (i = 0; i < 16; i++) {
            prim->tpage = 0x1A;
            prim->clut = 0x15F;
            prim->priority = self->zPriority = 0xC2;
            prim->blendMode = 0x435;
            prim->u0 = ((rsin((s16)(i * 0x100)) << 5) >> 0xC) + 0x20;
            prim->v0 = -((rcos((s16)(i * 0x100)) << 5) >> 0xC) - 0x21;
            prim->u1 = ((rsin((s16)((i + 1) * 0x100)) << 5) >> 0xC) + 0x20;
            prim->v1 = -((rcos((s16)((i + 1) * 0x100)) << 5) >> 0xC) - 0x21;
            prim->v2 = prim->v3 = 0xE0;
            prim->u2 = prim->u3 = 0x20;
            prim->r0 = prim->r1 = prim->g0 = prim->g1 = prim->b0 = prim->b1 =
                0x40;
            prim->r2 = prim->r3 = prim->g2 = prim->g3 = 0;
            prim->b2 = prim->b3 = 0x20;
            prim = prim->next;
        }
        self->ext.et_8017161C.unk7E = 0x20;
        self->step++;
        break;
    case 1:
        self->ext.et_8017161C.unk7E += 0x18;
        if (++self->ext.et_8017161C.unk7C >= 0x1F) {
            DestroyEntity(self);
            return;
        }
    }
    xCoord = self->posX.i.hi;
    yCoord = self->posY.i.hi;
    prim = &g_PrimBuf[self->primIndex];
    for (i = 0; i < 16; i++) {
        sine = rsin(i * 0x100);
        cosine = rcos(i * 0x100);
        temp_s0_4 = self->ext.et_8017161C.unk7E - 0x20;
        prim->x0 = xCoord + ((sine * self->ext.et_8017161C.unk7E) >> 0xC);
        prim->y0 = yCoord - ((cosine * self->ext.et_8017161C.unk7E) >> 0xC);
        prim->x2 = xCoord + ((sine * (temp_s0_4)) >> 0xC);
        prim->y2 = yCoord - ((cosine * temp_s0_4) >> 0xC);
        sine = rsin((i + 1) * 0x100);
        cosine = rcos((i + 1) * 0x100);
        prim->x1 = xCoord + ((sine * self->ext.et_8017161C.unk7E) >> 0xC);
        prim->y1 = yCoord - ((cosine * self->ext.et_8017161C.unk7E) >> 0xC);
        prim->x3 = xCoord + ((sine * temp_s0_4) >> 0xC);
        prim->y3 = yCoord - ((cosine * temp_s0_4) >> 0xC);
        prim = prim->next;
    }
    return;
}

INCLUDE_ASM("asm/us/ric/nonmatchings/345EC", func_801719A4);

void func_80172AE8(Entity* entity) {
    POLY_GT4* poly;
    s32 ret;

    switch (entity->step) {
    case 0:
        ret = g_api.AllocPrimitives(PRIM_GT4, 1);
        entity->primIndex = ret;
        if (entity->primIndex != -1) {
            entity->flags = FLAG_UNK_20000 | FLAG_UNK_04000000 | FLAG_HAS_PRIMS;
            poly = &g_PrimBuf[entity->primIndex];
            poly->tpage = 0x1C;
            poly->clut = 0x19D;
            poly->u2 = 0x20;
            poly->u0 = 0x20;
            poly->u3 = 0x30;
            poly->u1 = 0x30;
            poly->v1 = 0;
            poly->v0 = 0;
            poly->v3 = 0x10;
            poly->v2 = 0x10;
            poly->x0 = poly->x2 = entity->posX.i.hi - 8;
            poly->x1 = poly->x3 = entity->posX.i.hi + 8;
            poly->y0 = poly->y1 = entity->posY.i.hi - 8;
            poly->y2 = poly->y3 = entity->posY.i.hi + 8;
            poly->pad2 = entity->zPriority;
            poly->pad3 = 0x115;
            entity->ext.generic.unk7E.modeU16 = 0x60U;
            entity->step++;
        } else {
            DestroyEntity(entity);
            return;
        }
        break;

    case 1:
        if (++entity->ext.generic.unk7C.s > 5) {
            entity->step++;
        }
        entity->ext.generic.unk7E.modeU16 -= 8;
        break;

    case 2:
        DestroyEntity(entity);
        return;

    default:
        break;
    }
    poly = &g_PrimBuf[entity->primIndex];
    poly->r0 = poly->r1 = poly->r2 = poly->r3 = poly->g0 = poly->g1 = poly->g2 =
        poly->g3 = poly->b0 = poly->b1 = poly->b2 = poly->b3 =
            entity->ext.generic.unk7E.modeU8.unk0;
}

INCLUDE_ASM("asm/us/ric/nonmatchings/345EC", func_80172D00);

INCLUDE_ASM("asm/us/ric/nonmatchings/345EC", func_8017328C);
