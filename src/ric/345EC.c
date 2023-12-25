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
        CreateEntFactoryFromEntity(entity, (temp << 0x10) | 0x3F, 0);
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
        CreateEntFactoryFromEntity(
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

void func_801719A4(Entity* self) {
    Primitive* prim;
    s16 firstmult;
    s16 secondmult;
    s16 var_a0;
    s16 var_a1;
    Entity* parent;
    s32 sine;
    s32 cosine;
    s32 var_s4;
    s32 var_s6;
    s32 xDiff;
    s32 ySub;
    s16 temp_v0;

    s32 temp_t1;
    s32 temp_a3;
    s32 temp_t2;
    s32 temp_a0_6;
    s32 temp_a2_3;
    s32 temp_a1_3;
    s32 temp_t0;
    s32 temp_v1_11;
    if (*D_80097400 != 0) {
        // FAKE, needed to make step load at the right time
        do {
            D_800973FC = 0;
        } while (0);
        if ((self->step > 0) && (self->step < 4)) {
            self->step = 4;
        }
    }
    switch (self->step) {
    case 0:
        self->primIndex = g_api.AllocPrimitives(PRIM_GT4, 3);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags = FLAG_UNK_08000000 | FLAG_UNK_04000000 | FLAG_HAS_PRIMS |
                      FLAG_UNK_20000;
        prim = &g_PrimBuf[self->primIndex];
        prim->tpage = 0x1E;
        prim->clut = 0x17F;
        prim->v0 = prim->v1 = 0xC0;
        prim->v2 = prim->v3 = 0xD8;
        if (self->facingLeft) {
            prim->u0 = prim->u2 = 0x98;
            prim->u1 = prim->u3 = 0xA8;
        } else {
            prim->u0 = prim->u2 = 0xA8;
            prim->u1 = prim->u3 = 0x98;
        }
        prim->priority = PLAYER.zPriority + 1;
        prim->blendMode = 0x10A;
        prim = prim->next;

        prim->tpage = 0x1A;
        prim->clut = 0x186;
        prim->priority = PLAYER.zPriority + 3;
        prim->blendMode = 0x10A;

        prim = prim->next;

        prim->tpage = 0x1A;
        prim->clut = 0x186;
        prim->priority = PLAYER.zPriority + 3;
        prim->blendMode = 0x10A;
        if (self->params & 0xFF00) {
            CreateEntFactoryFromEntity(self, 0x42U, 0);
            D_801758D0 = self->ext.et_801719A4.unk94 = self->params >> 8;
            if (self->ext.et_801719A4.unk94 < 4) {
                (&D_801758D0)[self->ext.et_801719A4.unk94] = (u32)self;
            }
            if (self->ext.et_801719A4.unk94 >= 2) {
                self->ext.et_801719A4.unk98 =
                    D_801758CC[self->ext.et_801719A4.unk94];
            }
        } else {
            CreateEntFactoryFromEntity(self, 0x40U, 0);
            self->ext.et_801719A4.unk94 = 0;
        }
        self->ext.et_801719A4.unkB0 = 6;
        func_8015FAB8(self);
        g_api.PlaySfx(0x6AD);
        if (self->ext.et_801719A4.unk94 < 2) {
            D_800973FC = 1;
        }
        self->step++;
        break;
    case 1:
        prim = &g_PrimBuf[self->primIndex];
        prim->blendMode &= ~BLEND_VISIBLE;
        self->ext.et_801719A4.unk84.val += 0x18000;
        if (self->ext.et_801719A4.unk84.val > 0x19FFFF) {
            self->step++;
        }
        break;
    case 2:
        self->ext.et_801719A4.unk84.val += 0xFFFF0000;
        if (self->ext.et_801719A4.unk84.val <= 0x100000) {
            self->ext.et_801719A4.unk7C = 5;
            g_api.PlaySfx(0x6A1);
            self->step++;
        }
        break;
    case 3:
        if (++self->ext.et_801719A4.unk7E >= 0x51) {
            g_api.PlaySfx(0x6A1);
            self->ext.et_801719A4.unk7E = 0;
            self->ext.et_801719A4.unk90 = 1;
            if (--self->ext.et_801719A4.unk7C < 0) {
                self->step++;
                break;
            }
        }

        if (self->ext.et_801719A4.unk7C < 5) {
            prim = g_PrimBuf[self->primIndex].next;
            if (self->ext.et_801719A4.unk7C >= 10) {
                self->ext.et_801719A4.unk92 = 1;
                // MISMATCH: Not using S4 for this
                var_s4 = 8 * (self->ext.et_801719A4.unk7C / 10);
                prim->u0 = prim->u2 = var_s4 + 0x18;
                prim->u1 = prim->u3 = var_s4 + 0x1E;
                prim->v0 = prim->v1 = 0x40;
                prim->v2 = prim->v3 = 0x49;
                prim->blendMode &= ~BLEND_VISIBLE;
                prim = prim->next;
            } else {
                self->ext.et_801719A4.unk92 = 0;
            }
            var_s4 = 8 * (self->ext.et_801719A4.unk7C % 10);
            if (var_s4 == 0) {
                var_s4 = 0x50;
            }
            prim->u0 = prim->u2 = var_s4 + 0x18;
            prim->u1 = prim->u3 = var_s4 + 0x1E;
            prim->v0 = prim->v1 = 0x40;
            prim->v2 = prim->v3 = 0x49;
            prim->blendMode &= ~BLEND_VISIBLE;
        }
        break;
    case 4:
        prim = &g_PrimBuf[self->primIndex];
        self->flags &= ~FLAG_UNK_40000;
        prim->priority = 0xC2;
        prim->blendMode &= ~0x200;
        prim = prim->next;
        prim->blendMode |= BLEND_VISIBLE;
        prim = prim->next;
        prim->blendMode |= BLEND_VISIBLE;
        self->posX.i.hi += self->facingLeft ? 6 : -6;
        ySub = self->ext.et_801719A4.unk84.i.hi;
        self->posY.i.hi -= ySub;
        self->ext.et_801719A4.unk7C = 0;
        if (self->ext.et_801719A4.unk94 != 0) {
            self->step = 7;
            CreateEntFactoryFromEntity(self, 0x48U, 0);
        } else {
            self->step++;
        }
        break;
    case 5:
        if (++self->ext.et_801719A4.unk7C >= 4) {
            prim = &g_PrimBuf[self->primIndex];
            prim->clut = 0x15F;
            prim->g0 = prim->g1 = prim->g2 = prim->g3 = prim->r0 = prim->r1 =
                prim->r2 = prim->r3 = 0x40;
            prim->b0 = prim->b1 = prim->b2 = prim->b3 = 0x60;
            prim->blendMode |= 4;
            g_api.PlaySfx(0x6A4);
            self->step++;
        }
        break;
    case 6:
        if (++self->ext.et_801719A4.unk7C >= 0xF) {
            CreateEntFactoryFromEntity(self, 0x70004U, 0);
            self->step++;
        }
        break;
    case 7:
        if ((self->ext.et_801719A4.unk94 == 0) ||
            (self->ext.et_801719A4.unk94 == D_801758D0)) {
            D_800973FC = 0;
        }
        if (self->ext.et_801719A4.unk94 != 0) {
            (&D_801758D0)[self->ext.et_801719A4.unk94] = 0;
        }
        DestroyEntity(self);
        return;
    }
    if (self->step == 0) {
        return;
    }
    prim = &g_PrimBuf[self->primIndex];
    if (self->step < 5) {
        if (self->ext.et_801719A4.unk94 < 2) {
            var_s4 = PLAYER.posX.val + (PLAYER.facingLeft ? FIX(8) : FIX(-8));
            var_s6 = PLAYER.posY.val + FIX(-16);
        } else if (D_801758CC[self->ext.et_801719A4.unk94] != 0) {
            var_s4 = self->ext.et_801719A4.unk98->posX.val +
                     (PLAYER.facingLeft ? FIX(16) : FIX(-16));
            var_s6 = self->ext.et_801719A4.unk98->posY.val + FIX(-16);
        } else {
            var_s4 = self->posX.val;
            var_s6 = self->posY.val;
        }
        self->posX.val += (var_s4 - self->posX.val) / 12;
        self->posY.val += (var_s6 - self->posY.val) / 4;
        if (self->ext.et_801719A4.unk94 < 2) {
            if (PLAYER.facingLeft != self->facingLeft) {
                xDiff = var_s4 - self->posX.val;
                if (ABS(xDiff) < FIX(1)) {
                    self->facingLeft = PLAYER.facingLeft;
                } else if (!self->facingLeft) {
                    if (var_s4 < self->posX.val) {
                        self->facingLeft = PLAYER.facingLeft;
                    } else {
                        goto block_84;
                    }
                } else if (self->posX.val < var_s4) {
                    self->facingLeft = PLAYER.facingLeft;
                }
            }
        } else if (D_801758CC[self->ext.et_801719A4.unk94] != 0) {
            parent = self->ext.et_801719A4.unk98;
            if (parent->facingLeft != self->facingLeft) {
                xDiff = var_s4 - self->posX.val;
                if (ABS(xDiff) >= FIX(1)) {
                    if (!self->facingLeft) {
                        if (var_s4 < self->posX.val) {
                            self->facingLeft = parent->facingLeft;
                        } else {
                            goto block_84;
                        }
                    } else if (self->posX.val < var_s4) {
                        self->facingLeft = parent->facingLeft;
                    }
                } else {
                    self->facingLeft = parent->facingLeft;
                }
            }
        }
        if (self->facingLeft) {
            prim->u2 = 0x98;
            prim->u0 = 0x98;
            prim->u1 = prim->u3 = 0xA8;
        } else {
        block_84:
            prim->u2 = 0xA8;
            prim->u0 = 0xA8;
            prim->u1 = prim->u3 = 0x98;
        }
    }
    if (self->step < 3) {
        var_s4 = self->posX.i.hi + (self->facingLeft ? 6 : -6);
        var_s6 = self->posY.i.hi - self->ext.et_801719A4.unk84.i.hi;
        if (self->ext.et_801719A4.unk82 < 0x64) {
            self->ext.et_801719A4.unk82 += 4;
        }
        if (self->ext.et_801719A4.unk80 < 0x1000) {
            self->ext.et_801719A4.unk80 += 0x80;
        }
        firstmult = (self->ext.et_801719A4.unk82 * 8) / 100;
        secondmult = (self->ext.et_801719A4.unk82 * 0xC) / 100;
        sine = rsin(self->ext.et_801719A4.unk80);
        cosine = rcos(self->ext.et_801719A4.unk80);
        prim->x0 = var_s4 + ((cosine * -firstmult - sine * -secondmult) >> 0xC);
        prim->y0 = var_s6 + ((sine * -firstmult + cosine * -secondmult) >> 0xC);
        prim->x1 = var_s4 + ((cosine * firstmult - sine * -secondmult) >> 0xC);
        prim->y1 = var_s6 + ((sine * firstmult + cosine * -secondmult) >> 0xC);
        prim->x2 = var_s4 + ((cosine * -firstmult - sine * secondmult) >> 0xC);
        prim->x3 = var_s4 + ((cosine * firstmult - sine * secondmult) >> 0xC);
        prim->y2 = var_s6 + ((sine * -firstmult + cosine * secondmult) >> 0xC);
        prim->y3 = var_s6 + ((sine * firstmult + cosine * secondmult) >> 0xC);
    } else if (self->step < 5U) {
        if (self->ext.et_801719A4.unk84.val <= 0x100000) {
            if (self->ext.et_801719A4.unk90 != 0) {
                self->ext.et_801719A4.unk88 = (rand() % 0x40 + 0x200) * 0x100;
                self->ext.et_801719A4.unk90 = 0;
            } else {
                self->ext.et_801719A4.unk88 = (rand() % 0x80 + 0x100) * 0x100;
            }
            if (self->ext.et_801719A4.unk80 >= 0) {
                self->ext.et_801719A4.unk80 = -(rand() % 0x40 + 0x40);
            } else {
                self->ext.et_801719A4.unk80 = rand() % 0x40 + 0x40;
            }
        }
        self->ext.et_801719A4.unk84.val += self->ext.et_801719A4.unk88;
        self->ext.et_801719A4.unk88 -= 0x4000;
        var_s4 = self->posX.i.hi + (self->facingLeft ? 6 : -6);
        var_s6 = self->posY.i.hi - self->ext.et_801719A4.unk84.i.hi;
        sine = rsin(self->ext.et_801719A4.unk80);
        cosine = rcos(self->ext.et_801719A4.unk80);
        temp_t1 = cosine * 8;
        temp_a3 = -temp_t1;
        temp_t2 = sine * 0xC;
        temp_a0_6 = -temp_t2;
        temp_a2_3 = sine * 8;
        temp_a1_3 = -temp_a2_3;
        temp_t0 = cosine * 0xC;
        temp_v1_11 = -temp_t0;
        prim->x0 = var_s4 + ((temp_a3 - temp_a0_6) >> 0xC);
        prim->y0 = var_s6 + ((temp_a1_3 + temp_v1_11) >> 0xC);
        prim->x1 = var_s4 + ((temp_t1 - temp_a0_6) >> 0xC);
        prim->y1 = var_s6 + ((temp_a2_3 + temp_v1_11) >> 0xC);
        prim->x2 = var_s4 + ((temp_a3 - temp_t2) >> 0xC);
        prim->y2 = var_s6 + ((temp_a1_3 + temp_t0) >> 0xC);
        prim->x3 = var_s4 + ((temp_t1 - temp_t2) >> 0xC);
        prim->y3 = var_s6 + ((temp_a2_3 + temp_t0) >> 0xC);
    } else {
        temp_v0 = 8 - self->ext.et_801719A4.unk7C;
        var_a0 = temp_v0;
        if (temp_v0 <= 0) {
            var_a0 = 1;
        }
        var_a1 = ((self->ext.et_801719A4.unk7C << 0x10) >> 0xB) + 0xC;
        if (var_a1 >= 0x80) {
            var_a1 = 0x80;
        }
        prim->x0 = prim->x2 = self->posX.i.hi - var_a0;
        prim->x1 = prim->x3 = var_a0 + self->posX.i.hi;
        prim->y0 = prim->y1 = self->posY.i.hi - var_a1;
        prim->y2 = prim->y3 = var_a1 + self->posY.i.hi;
    }
    if (self->step < 4) {
        var_s6 = self->posY.i.hi - 0xE;
        if (self->ext.et_801719A4.unk92 != 0) {
            var_s4 = self->posX.i.hi + (self->facingLeft ? -10 : 4);
            prim = prim->next;
            if (self->ext.et_801719A4.unk7E < 8) {
                prim->x0 = prim->x2 =
                    var_s4 - (self->ext.et_801719A4.unk7E / 2);
                prim->x1 = prim->x3 =
                    var_s4 + (self->ext.et_801719A4.unk7E / 2);
                temp_t2 = 0xF;
                prim->y0 = prim->y1 =
                    var_s6 + (self->ext.et_801719A4.unk7E - temp_t2);
                prim->y2 = prim->y3 =
                    var_s6 - (self->ext.et_801719A4.unk7E - temp_t2);
            } else if (self->ext.et_801719A4.unk7E >= 0x44) {
                var_a0 = (0x4C - self->ext.et_801719A4.unk7E) / 2;
                if (var_a0 < 0) {
                    var_a0 = 0;
                }
                var_a1 = self->ext.et_801719A4.unk7E - 0x44;
                if (var_a1 >= 9) {
                    var_a1 = 8;
                }
                var_a1 += 8;
                prim->x0 = prim->x2 = var_s4 - var_a0;
                prim->x1 = prim->x3 = var_s4 + var_a0;
                prim->y0 = prim->y1 = var_s6 - var_a1;
                // FAKE horrible thing needed to match, secondmult should be
                // totally irrelevant here
                prim->y2 = prim->y3 = (secondmult = var_s6) + var_a1;
            } else {
                prim->x0 = prim->x2 = var_s4 - 4;
                prim->x1 = prim->x3 = var_s4 + 4;
                prim->y0 = prim->y1 = var_s6 - 8;
                prim->y2 = prim->y3 = var_s6 + 8;
            }
            var_s4 = self->posX.i.hi + (self->facingLeft ? -4 : 10);
            prim = prim->next;
            if (self->ext.et_801719A4.unk7E < 0xC) {
                var_a0 = (self->ext.et_801719A4.unk7E - 4) / 2;
                if (var_a0 < 0) {
                    var_a0 = 0;
                }
                var_a1 = 0xB - self->ext.et_801719A4.unk7E;
                if (var_a1 < 0) {
                    var_a1 = 0;
                }
                var_a1 += 8;
                prim->x0 = prim->x2 = var_s4 - var_a0;
                prim->x1 = prim->x3 = var_s4 + var_a0;
                prim->y0 = prim->y1 = var_s6 - var_a1;
                // FAKE horrible thing needed to match, secondmult should be
                // totally irrelevant here
                prim->y2 = prim->y3 = (secondmult = var_s6) + var_a1;
            } else if (self->ext.et_801719A4.unk7E < 0x48) {
                prim->x0 = prim->x2 = var_s4 - 4;
                prim->x1 = prim->x3 = var_s4 + 4;
                prim->y0 = prim->y1 = var_s6 - 8;
                prim->y2 = prim->y3 = var_s6 + 8;
            } else {
                prim->x0 = prim->x2 =
                    var_s4 - ((0x50 - self->ext.et_801719A4.unk7E) / 2);
                prim->x1 = prim->x3 =
                    var_s4 + ((0x50 - self->ext.et_801719A4.unk7E) / 2);
                temp_t2 = -0x40;
                prim->y0 = prim->y1 =
                    var_s6 - (self->ext.et_801719A4.unk7E + temp_t2);
                prim->y2 = prim->y3 =
                    var_s6 + (self->ext.et_801719A4.unk7E + temp_t2);
            }
        } else {
            var_s4 = self->posX.i.hi + (self->facingLeft ? -4 : 4);
            prim = prim->next;
            if (self->ext.et_801719A4.unk7E < 8) {
                prim->x0 = prim->x2 =
                    var_s4 - (self->ext.et_801719A4.unk7E / 2);
                prim->x1 = prim->x3 =
                    var_s4 + (self->ext.et_801719A4.unk7E / 2);
                temp_t2 = 0xF;
                prim->y0 = prim->y1 =
                    var_s6 + (self->ext.et_801719A4.unk7E - temp_t2);
                prim->y2 = prim->y3 =
                    var_s6 - (self->ext.et_801719A4.unk7E - temp_t2);
            } else if (self->ext.et_801719A4.unk7E >= 0x48) {
                prim->x0 = prim->x2 =
                    var_s4 - ((0x50 - self->ext.et_801719A4.unk7E) / 2);
                prim->x1 = prim->x3 =
                    var_s4 + ((0x50 - self->ext.et_801719A4.unk7E) / 2);
                temp_t2 = -0x40;
                prim->y0 = prim->y1 =
                    var_s6 - (self->ext.et_801719A4.unk7E + temp_t2);
                prim->y2 = prim->y3 =
                    var_s6 + (self->ext.et_801719A4.unk7E + temp_t2);
            } else {
                prim->x0 = prim->x2 = var_s4 - 5;
                prim->x1 = prim->x3 = var_s4 + 5;
                prim->y0 = prim->y1 = var_s6 - 8;
                prim->y2 = prim->y3 = var_s6 + 8;
            }
        }
    }
}

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

void EntitySubwpnBible(Entity* self) {
    Primitive* prim;
    s16 left;
    s16 top;
    s16 bottom;
    s16 right;

    s32 sine;
    s32 cosine;
    s32 cos_s2;
    s32 sin_s3;
    s32 cos_s3;
    s32 sin_s2;

    s32 temp_a3;
    s32 temp_s2;
    s32 temp_s3;
    s32 temp_a1;

    s32 temp_v0;
    // Note: Not initialized in this function! will retain
    // value already held (due to being a saved register)
    s32 var_s4;

    switch (self->step) {
    case 0:
        self->primIndex = g_api.AllocPrimitives(PRIM_GT4, 1);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags = FLAG_UNK_04000000 | FLAG_HAS_PRIMS | FLAG_UNK_20000;
        prim = &g_PrimBuf[self->primIndex];
        prim->tpage = 0x1E;
        prim->clut = 0x17F;
        prim->u0 = prim->u2 = 0x98;
        prim->v0 = prim->v1 = 0xD8;
        prim->u1 = prim->u3 = 0xA8;
        prim->v2 = prim->v3 = 0xF0;
        prim->priority = PLAYER.zPriority + 1;
        prim->blendMode = 0x108;
        self->ext.et_BibleSubwpn.unk84 = self->facingLeft ? 0x20 : -0x20;
        self->ext.et_BibleSubwpn.unkB0 = 5;
        func_8015FAB8(self);
        self->hitboxWidth = 6;
        self->hitboxHeight = 6;
        self->step++;
        break;
    case 1:
        prim = &g_PrimBuf[self->primIndex];
        prim->blendMode &= ~BLEND_VISIBLE;
        self->ext.et_BibleSubwpn.unk86++;
        self->step++;
    case 2:
        self->ext.et_BibleSubwpn.unk7C++;
        if (++self->ext.et_BibleSubwpn.unk7E >= 0x30) {
            self->step++;
        }
        break;
    case 3:
        if (++self->ext.et_BibleSubwpn.unk7C >= 0x12C) {
            self->flags &= ~FLAG_UNK_04000000;
            self->velocityX = self->facingLeft ? FIX(-12) : FIX(12);
            self->velocityY = FIX(-12);
            g_api.PlaySfx(0x6B2);
            self->ext.et_BibleSubwpn.unk86++;
            self->step++;
        }
        break;
    }
    switch (self->ext.et_BibleSubwpn.unk86) {
    case 0:
        break;
    case 1:
        // All this logic is a mess, could use a cleanup
        sine = rsin(self->ext.et_BibleSubwpn.unk80);
        cosine = rcos(self->ext.et_BibleSubwpn.unk80);
        temp_s2 = (sine * self->ext.et_BibleSubwpn.unk7E) >> 0xC;
        temp_s3 = (cosine * self->ext.et_BibleSubwpn.unk7E) >> 0xC;
        cos_s2 = cosine * temp_s2;
        sin_s3 = sine * temp_s3;
        cos_s3 = cosine * temp_s3;
        temp_a1 = cos_s2 + sin_s3;
        sin_s2 = sine * temp_s2;
        temp_s2 = temp_a1 >> 0xC;
        temp_s3 = (cos_s3 - sin_s2) >> 0xC;
        sine = rsin(self->ext.et_BibleSubwpn.unk82);
        cosine = rcos(self->ext.et_BibleSubwpn.unk82);
        temp_a1 = ((cosine * temp_s2) + (sine * var_s4)) >> 0xC;
        temp_a3 = ((cosine * var_s4) - (sine * temp_s2)) >> 0xC;
        if (self->facingLeft != 0) {
            temp_a3 = ((cosine * temp_a3) + (sine * temp_s3)) >> 0xC;
        } else {
            temp_a3 = ((cosine * temp_a3) - (sine * temp_s3)) >> 0xC;
        }

        self->ext.et_BibleSubwpn.unk80 += (self->facingLeft ? 0x80 : -0x80);
        self->ext.et_BibleSubwpn.unk80 &= 0xFFF;
        self->ext.et_BibleSubwpn.unk82 += self->ext.et_BibleSubwpn.unk84;
        if (ABS(self->ext.et_BibleSubwpn.unk82) >= 0x200) {
            // temp_v0 needed because otherwise unk84 gets loaded with lhu
            // instead of lh
            temp_v0 = -self->ext.et_BibleSubwpn.unk84;
            self->ext.et_BibleSubwpn.unk84 = temp_v0;
        }
        self->posX.i.hi = PLAYER.posX.i.hi + temp_a1;
        self->posY.i.hi = PLAYER.posY.i.hi + temp_a3;
        self->zPriority = PLAYER.zPriority + (temp_s3 < 0 ? 2 : -2);
        break;
    case 2:
        self->posX.val += self->velocityX;
        self->posY.val += self->velocityY;
        self->velocityY += FIX(-2);
        break;
    }
    if (self->ext.et_BibleSubwpn.unk86 != 0) {
        prim = &g_PrimBuf[self->primIndex];
        left = self->posX.i.hi - 8;
        right = self->posX.i.hi + 8;
        top = self->posY.i.hi - 12;
        bottom = self->posY.i.hi + 12;
        prim->x0 = prim->x2 = left;
        prim->x1 = prim->x3 = right;
        prim->y0 = prim->y1 = top;
        prim->y2 = prim->y3 = bottom;
        prim->priority = self->zPriority;
        CreateEntFactoryFromEntity(self, 0x3E, 0);
        if (g_GameTimer % 10 == 0) {
            g_api.PlaySfx(BIBLE_SUBWPN_SWOOSH);
        }
    }
}

void EntityGiantSpinningCross(Entity* self) {
    MATRIX m;
    SVECTOR rot;
    VECTOR trans1;
    SVECTOR pos;
    SVECTOR sp50;
    s32 z;
    s32 nclip;
    Primitive* prim;
    s32 temp_v1;
    s32 i;
    u8* primUVCoords;
    SVECTOR* temp_a3;
    SVECTOR** vectors_ptr;
    u16 priority;

    pos = D_80156C50;
    sp50 = D_80156C58;
    if (self->step == 0) {
        self->primIndex = g_api.func_800EDB58(PRIM_GT4, 46);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        prim = &g_PrimBuf[self->primIndex];
        while (prim != NULL) {
            prim->tpage = 0x1C;
            prim->blendMode = 0x100 | BLEND_VISIBLE;
            prim = prim->next;
        }
        self->ext.giantcross.unkB0 = 0xD;
        func_8015FAB8(self);
        self->hitboxHeight = 0x50;
        self->hitboxWidth = 0xC;
        self->posY.i.hi = 0x160;
        self->velocityY = FIX(-6.0);
        self->flags = FLAG_UNK_04000000 | FLAG_HAS_PRIMS | FLAG_UNK_20000;
        self->facingLeft = 0;
        self->ext.giantcross.unk7C = 0;
        self->ext.giantcross.unk7E = 0x400;
        g_api.PlaySfx(0x661);
        self->step++;
        primUVCoords = &D_8015635C[0][0];
        prim = &g_PrimBuf[self->primIndex];
        for (i = 0; i < 46; i++, prim = prim->next, primUVCoords += 5) {
            prim->clut = (primUVCoords[4] & 0xF) | 0x1A0;
            switch (primUVCoords[4] & 0xF0) {
            case 0x10:
                prim->u0 = primUVCoords[0] + primUVCoords[2];
                prim->v0 = primUVCoords[1];
                prim->u1 = primUVCoords[0];
                prim->v1 = primUVCoords[1];
                prim->u2 = primUVCoords[0] + primUVCoords[2];
                prim->v2 = primUVCoords[1] + primUVCoords[3];
                prim->u3 = primUVCoords[0];
                prim->v3 = primUVCoords[1] + primUVCoords[3];
                break;
            case 0x20:
                prim->u0 = primUVCoords[0];
                prim->v0 = primUVCoords[1] + primUVCoords[3];
                prim->u1 = primUVCoords[0] + primUVCoords[2];
                prim->v1 = primUVCoords[1] + primUVCoords[3];
                prim->u2 = primUVCoords[0];
                prim->v2 = primUVCoords[1];
                prim->u3 = primUVCoords[0] + primUVCoords[2];
                prim->v3 = primUVCoords[1];
                break;
            case 0x30:
                prim->u0 = primUVCoords[0] + primUVCoords[2];
                prim->v0 = primUVCoords[1] + primUVCoords[3];
                prim->u1 = primUVCoords[0];
                prim->v1 = primUVCoords[1] + primUVCoords[3];
                prim->u2 = primUVCoords[0] + primUVCoords[2];
                prim->v2 = primUVCoords[1];
                prim->u3 = primUVCoords[0];
                prim->v3 = primUVCoords[1];
                break;
            case 0x40:
                prim->u3 = primUVCoords[0];
                prim->v3 = primUVCoords[1];
                prim->u1 = primUVCoords[0] + primUVCoords[2];
                prim->v1 = primUVCoords[1];
                prim->u2 = primUVCoords[0];
                prim->v2 = primUVCoords[1] + primUVCoords[3];
                prim->u0 = primUVCoords[0] + primUVCoords[2];
                prim->v0 = primUVCoords[1] + primUVCoords[3];
                break;
            case 0x50:
                prim->u3 = primUVCoords[0] + primUVCoords[2];
                prim->v3 = primUVCoords[1];
                prim->u1 = primUVCoords[0];
                prim->v1 = primUVCoords[1];
                prim->u2 = primUVCoords[0] + primUVCoords[2];
                prim->v2 = primUVCoords[1] + primUVCoords[3];
                prim->u0 = primUVCoords[0];
                prim->v0 = primUVCoords[1] + primUVCoords[3];
                break;
            case 0x60:
                prim->u3 = primUVCoords[0];
                prim->v3 = primUVCoords[1] + primUVCoords[3];
                prim->u1 = primUVCoords[0] + primUVCoords[2];
                prim->v1 = primUVCoords[1] + primUVCoords[3];
                prim->u2 = primUVCoords[0];
                prim->v2 = primUVCoords[1];
                prim->u0 = primUVCoords[0] + primUVCoords[2];
                prim->v0 = primUVCoords[1];
                break;
            case 0x70:
                prim->u3 = primUVCoords[0] + primUVCoords[2];
                prim->v3 = primUVCoords[1] + primUVCoords[3];
                prim->u1 = primUVCoords[0];
                prim->v1 = primUVCoords[1] + primUVCoords[3];
                prim->u2 = primUVCoords[0] + primUVCoords[2];
                prim->v2 = primUVCoords[1];
                prim->u0 = primUVCoords[0];
                prim->v0 = primUVCoords[1];
                break;
            default:
                prim->u0 = primUVCoords[0];
                prim->v0 = primUVCoords[1];
                prim->u1 = primUVCoords[0] + primUVCoords[2];
                prim->v1 = primUVCoords[1];
                prim->u2 = primUVCoords[0];
                prim->v2 = primUVCoords[1] + primUVCoords[3];
                prim->u3 = primUVCoords[0] + primUVCoords[2];
                prim->v3 = primUVCoords[1] + primUVCoords[3];
                break;
            }
        }
        return;
    }
    if (self->posY.i.hi < -0x40) {
        DestroyEntity(self);
        return;
    }
    if (self->posY.i.hi < 0) {
        self->velocityY -= FIX(0.5);
    }
    self->posY.val += self->velocityY;
    self->ext.giantcross.unk7C += 0x60;
    self->ext.giantcross.unk7E += 0x60;
    trans1.vx = -(rcos(self->ext.giantcross.unk7C) * 0x60) >> 0xC;
    trans1.vy = self->posY.i.hi - 0x80;
    trans1.vz = ((rsin(self->ext.giantcross.unk7C) * 0x60) >> 0xC) + 0x180;
    rot.vy = self->ext.giantcross.unk7E;
    rot.vz = 0x40;
    rot.vx = 0;

    SetGeomOffset(self->posX.i.hi, 120);
    gte_SetGeomScreen(320);
    RotMatrix(&rot, &m);
    TransMatrix(&m, &trans1);
    gte_SetRotMatrix(&m);
    gte_SetTransMatrix(&m);
    gte_ldv0(&pos);
    gte_rtps();
    prim = &g_PrimBuf[self->primIndex];
    vectors_ptr = &D_8015607C;
    gte_stsxy2(&prim->x0);
    gte_stszotz(&z);
    self->hitboxOffX = prim->x0 - self->posX.i.hi;
    self->hitboxOffY = prim->y0 - self->posY.i.hi;
    for (i = 0; i < 46; i++, prim = prim->next, vectors_ptr += 4) {
        gte_ldv3(vectors_ptr[0], vectors_ptr[1], vectors_ptr[3]);
        gte_rtpt();
        temp_a3 = vectors_ptr[2];
        prim->type = 4;
        gte_nclip();
        prim->blendMode = 8;
        gte_stopz(&nclip);
        if (nclip < 0) {
            continue;
        }
        gte_stsxy3(&prim->x0, &prim->x1, &prim->x2);
        gte_ldv0(temp_a3);
        gte_rtps();
        prim->blendMode = 0;
        if (z < 16) {
            priority = 0x1F6;
        } else if (z >= 999) {
            priority = 0x10;
        } else {
            priority = 0x120;
            priority -= z;
        }
        prim->priority = priority;
        gte_stsxy(&prim->x3);
    }
}
