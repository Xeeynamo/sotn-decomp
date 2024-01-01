#include "ric.h"

void func_8016E324(Entity* entity) {
    switch (entity->step) {
    case 0:
        entity->flags = FLAG_UNK_20000 | FLAG_UNK_04000000;
        entity->ext.generic.unk7C.s = 0x14;
        entity->step++;

    case 1:
        entity->ext.generic.unk7C.s--;
        if ((entity->ext.generic.unk7C.s) == 0) {
        case 3:
        case 5:
            CreateEntFactoryFromEntity(entity, 0x39, 0);
            entity->step++;
        case 2:
        case 4:
        case 6:
            entity->ext.generic.unk7C.s++;
            if (entity->ext.generic.unk7C.s >= 11) {
                entity->ext.generic.unk7C.s = 0;
                entity->posX.val = FIX(128.0);
                entity->posY.val = 0;
                CreateEntFactoryFromEntity(entity, 0x10004, 0);
                entity->step++;
            }
        }
        break;

    case 7:
        entity->ext.generic.unk7C.s++;
        if (entity->ext.generic.unk7C.s >= 16) {
            DestroyEntity(entity);
            g_Player.unk4E = 1;
            CreateEntFactoryFromEntity(entity, 0x3A, 0);
        }
        break;
    }
}

INCLUDE_ASM("asm/us/ric/nonmatchings/32324", func_8016E46C);

void func_8016E9E4(Entity* self) {
    Primitive* prim;
    s16 temp_a1_3;
    s16 temp_v0_6;
    s32 temp_s0_2;
    s32 temp_s5;
    s32 temp_s6;
    s32 temp_v0_4;
    s32 temp_v0_5;
    s32 i;
    s16 temp_a0;
    s16 temp_a1;

    switch (self->step) {
    case 0:
        self->primIndex = g_api.AllocPrimitives(PRIM_GT4, 7);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            g_Player.unk4E = 1;
            return;
        }
        self->flags = FLAG_UNK_04000000 | FLAG_HAS_PRIMS | FLAG_UNK_20000;
        self->posX.val = PLAYER.posX.val;
        self->posY.val = PLAYER.posY.val;
        self->velocityY = FIX(-4);
        if (self->facingLeft) {
            self->velocityX = FIX(12);
            self->ext.et_8016E9E4.unk88 = FIX(1.5);
            self->ext.et_8016E9E4.unk7E = -0x200;
        } else {
            self->velocityX = FIX(-12);
            self->ext.et_8016E9E4.unk88 = FIX(-1.5);
            self->ext.et_8016E9E4.unk7E = 0x200;
        }
        prim = &g_PrimBuf[self->primIndex];
        prim->tpage = 0x1E;
        prim->clut = 0x17F;

        prim->u0 = prim->u2 = 0x98;
        prim->v0 = prim->v1 = 0xD8;
        prim->u1 = prim->u3 = 0xA8;
        prim->v2 = prim->v3 = 0xF0;
        prim->priority = 0xC2;
        prim->blendMode = 8;
        prim = prim->next;
        for (i = 0; i < 6; i++) {
            prim->tpage = 0x1C;
            prim->clut = 0x1AE;
            prim->u0 = prim->u2 = 0x20;
            prim->u1 = prim->u3 = 0x30;
            prim->v0 = prim->v1 = 0;
            prim->v2 = prim->v3 = 0x10;
            prim->priority = 0xC1;
            prim->blendMode = BLEND_VISIBLE;
            prim = prim->next;
        }
        self->ext.et_8016E9E4.unk84 = 0x40;
        D_801758AC = 0x60;
        self->step++;
        break;
    case 1:
        prim = &g_PrimBuf[self->primIndex];
        prim->blendMode &= ~BLEND_VISIBLE;
        self->step++;
    case 2:
        self->posX.val += self->velocityX;
        self->posY.val += self->velocityY;
        self->velocityX -= self->ext.et_8016E9E4.unk88;
        self->velocityY -= FIX(0.5);
        if (++self->ext.et_8016E9E4.unk82 >= 8) {
            self->ext.et_8016E9E4.unk82 = 0;
            self->step++;
        }
        break;
    case 3:
        if (++self->ext.et_8016E9E4.unk82 >= 6) {
            prim = &g_PrimBuf[self->primIndex];
            prim->clut = 0x19F;
            prim->blendMode |= 0x35;
            prim = prim->next;
            for (i = 0; i < 6; i++) {
                prim->blendMode &= ~BLEND_VISIBLE;
                prim = prim->next;
            }
            self->ext.et_8016E9E4.unk82 = 0;
            self->step++;
        }
        break;
    case 4:
        self->ext.et_8016E9E4.unk84 -= 4;
        if (self->ext.et_8016E9E4.unk84 <= 0) {
            self->step++;
        }
        break;
    case 5:
        prim = &g_PrimBuf[self->primIndex];
        prim->blendMode |= BLEND_VISIBLE;
        self->step++;
    case 6:
        self->ext.et_8016E9E4.unk7C =
            (self->ext.et_8016E9E4.unk7C + 0x80) & 0xFFF;
        self->ext.et_8016E9E4.unk80 += 4;
        if (self->ext.et_8016E9E4.unk80 >= 0x30) {
            self->step++;
        }
        break;
    case 7:
        self->ext.et_8016E9E4.unk7C =
            (self->ext.et_8016E9E4.unk7C + 0x80) & 0xFFF;
        if (++self->ext.et_8016E9E4.unk82 >= 0x1E) {
            CreateEntFactoryFromEntity(self, FACTORY(0, 60), 0);
            self->ext.et_8016E9E4.unk82 = 0;
            self->step++;
        }
        break;
    case 8:
        self->ext.et_8016E9E4.unk7C =
            (self->ext.et_8016E9E4.unk7C + 0x80) & 0xFFF;
        if (++self->ext.et_8016E9E4.unk82 >= 0x60) {
            g_Player.unk4E = 1;
            self->step++;
        }
        break;
    case 9:
        self->ext.et_8016E9E4.unk7C =
            (self->ext.et_8016E9E4.unk7C + 0x80) & 0xFFF;
        self->ext.et_8016E9E4.unk80 -= 2;
        if (self->ext.et_8016E9E4.unk80 <= 0) {
            DestroyEntity(self);
            return;
        }
        break;
    }
    // FAKE, needed for reg match
    temp_a1 = self->ext.et_8016E9E4.unk7C;
    if ((self->ext.et_8016E9E4.unk7C == 0x100) ||
        (self->ext.et_8016E9E4.unk7C == 0x500) ||
        (self->ext.et_8016E9E4.unk7C == 0x900) ||
        (self->ext.et_8016E9E4.unk7C == 0xD00)) {
        if (self->step < 9) {
            g_api.func_80134714(0x625, D_801758AC, 0);
            if (self->step >= 5) {
                D_801758AC -= 4;
            }
            if (D_801758AC < 0) {
                D_801758AC = 0;
            }
        }
    }

    temp_a0 = self->posX.i.hi;
    temp_a1 = self->posY.i.hi;
    prim = &g_PrimBuf[self->primIndex];
    prim->x0 = prim->x2 = temp_a0 - 8;
    prim->x1 = prim->x3 = temp_a0 + 8;
    prim->y0 = prim->y1 = temp_a1 - 12;
    prim->y2 = prim->y3 = temp_a1 + 12;
    prim->r0 = prim->g0 = prim->b0 = prim->r1 = prim->g1 = prim->b1 = prim->r2 =
        prim->g2 = prim->b2 = prim->r3 = prim->g3 = prim->b3 =
            self->ext.et_8016E9E4.unk84;
    prim = prim->next;

    temp_s6 = rsin(self->ext.et_8016E9E4.unk7E);
    temp_s5 = rcos(self->ext.et_8016E9E4.unk7E);
    for (i = 0; i < 6; i++) {
        temp_s0_2 = (rsin(self->ext.et_8016E9E4.unk7C + D_80155EF0[i]) *
                     self->ext.et_8016E9E4.unk80) >>
                    0xC;
        temp_v0_4 = (rcos(self->ext.et_8016E9E4.unk7C + D_80155EF0[i]) *
                     self->ext.et_8016E9E4.unk80) >>
                    0xC;
        temp_a1_3 =
            self->posX.i.hi + ((((temp_s6 * temp_v0_4) >> 0xC) << 9) /
                               (((temp_s5 * temp_v0_4) >> 0xC) + 0x200));
        temp_v0_6 =
            self->posY.i.hi +
            ((temp_s0_2 << 9) / (((temp_s5 * temp_v0_4) >> 0xC) + 0x200));
        temp_v0_5 = ((temp_s5 * temp_v0_4) >> 0xC) + 0x200;
        D_80175894[i].unk0 = temp_a1_3;
        D_80175894[i].unk2 = temp_v0_6;
        prim->x0 = prim->x2 = temp_a1_3 - 0x1000 / temp_v0_5;
        prim->x1 = prim->x3 = temp_a1_3 + 0x1000 / temp_v0_5;
        // FAKE, needed for reg match
        temp_a0 = (prim->y1 = temp_v0_6 - 0x1000 / temp_v0_5);
        prim->y0 = temp_a0;

        prim->y2 = prim->y3 = temp_v0_6 + 0x1000 / temp_v0_5;
        prim = prim->next;
    }
}

void func_8016F198(Entity* self) {
    Primitive* prim;
    s16 unk7C;
    s16 temp_s6;
    s16 temp_a0;
    s16 temp_a1;
    s16 temp_a2;
    s16 temp_v1;
    s16 var_s0_2;
    s32 sine;
    s32 cosine;
    s32 i;
    u16 tpage;

    switch (self->step) {
    case 0:
        self->primIndex = g_api.AllocPrimitives(PRIM_GT4, 0x10);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            g_Player.unk4E = 1;
            return;
        }
        self->flags = FLAG_UNK_04000000 | FLAG_HAS_PRIMS;
        prim = &g_PrimBuf[self->primIndex];
        for (i = 0; i < 16; i++) {
            prim->priority = 0xC2;
            prim->blendMode = 8;
            prim = prim->next;
        }
        self->step++;
        break;
    case 1:
        i = 0;
        prim = &g_PrimBuf[self->primIndex];
        for (i = 0; i < 16; i++) {
            prim->blendMode &= ~BLEND_VISIBLE;
            prim = prim->next;
        }
        self->step++;
    case 2:
        if (++self->ext.factory.unk7C >= 0x18) {
            self->step++;
        }
        break;
    case 3:
        g_Player.unk4E = 1;
        DestroyEntity(self);
        return;
    }
    if (self->ext.factory.unk7C == 0) {
        return;
    }
    if (g_CurrentBuffer == g_GpuBuffers) {
        tpage = 0x104;
    } else {
        tpage = 0x100;
    }
    prim = &g_PrimBuf[self->primIndex];
    for (i = 0; i < 16; i++) {
        sine = rsin(i << 8);
        cosine = rcos(i << 8);
        unk7C = self->ext.factory.unk7C;
        var_s0_2 = 0;
        temp_s6 = unk7C * 8;
        if (unk7C >= 4) {
            var_s0_2 = (unk7C - 4) * 8;
        }
        temp_a1 = ((cosine * (s16)(unk7C * 8)) >> 0xC) + 0x80;
        temp_v1 = ((cosine * var_s0_2) >> 0xC) + 0x80;
        temp_a0 = ((sine * (s16)(unk7C * 8)) >> 0xC) + 0x78;
        temp_a2 = ((sine * var_s0_2) >> 0xC) + 0x78;

        temp_a1 = temp_a1 >= 0 ? MIN(temp_a1, 0xFF) : 0;
        prim->x0 = temp_a1;

        temp_v1 = temp_v1 >= 0 ? MIN(temp_v1, 0xFF) : 0;
        prim->x2 = temp_v1;

        temp_a0 = temp_a0 >= 0 ? MIN(temp_a0, 0xF0) : 0;
        prim->y0 = temp_a0;

        temp_a2 = temp_a2 >= 0 ? MIN(temp_a2, 0xF0) : 0;
        prim->y2 = temp_a2;

        prim->u0 = ~prim->x0;
        prim->u2 = ~prim->x2;
        prim->v0 = -0x10 - prim->y0;
        prim->v2 = -0x10 - prim->y2;

        sine = rsin((i + 1) << 8);
        cosine = rcos((i + 1) << 8);
        temp_a1 = ((cosine * temp_s6) >> 0xC) + 0x80;
        temp_v1 = ((cosine * var_s0_2) >> 0xC) + 0x80;
        temp_a0 = ((sine * temp_s6) >> 0xC) + 0x78;
        temp_a2 = ((sine * var_s0_2) >> 0xC) + 0x78;

        temp_a1 = temp_a1 >= 0 ? MIN(temp_a1, 0xFF) : 0;
        prim->x1 = temp_a1;

        temp_v1 = temp_v1 >= 0 ? MIN(temp_v1, 0xFF) : 0;
        prim->x3 = temp_v1;

        temp_a0 = temp_a0 >= 0 ? MIN(temp_a0, 0xF0) : 0;
        prim->y1 = temp_a0;

        temp_a2 = temp_a2 >= 0 ? MIN(temp_a2, 0xF0) : 0;
        prim->y3 = temp_a2;

        prim->tpage = tpage;
        prim->u1 = ~prim->x1;
        prim->u3 = ~prim->x3;
        prim->v1 = -0x10 - prim->y1;
        prim->v3 = -0x10 - prim->y3;
        prim = prim->next;
    }
}

INCLUDE_ASM("asm/us/ric/nonmatchings/32324", func_8016F6F0);

void func_80170548(Entity* entity) {
    switch (entity->step) {
    case 0:
        entity->flags = FLAG_UNK_04000000;
        entity->ext.generic.unkB0 = 0x1E;
        func_8015FAB8(entity);
        entity->hitboxWidth = 8;
        entity->hitboxHeight = 8;
        entity->step++;
        break;

    case 1:
        if (++entity->ext.generic.unk7C.s >= 5) {
            DestroyEntity(entity);
        }
        break;
    }
}
