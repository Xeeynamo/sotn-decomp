// SPDX-License-Identifier: AGPL-3.0-or-later
#include "bo0.h"

extern Pos D_us_801CD6E4[];

static s16 D_us_80180DC4[] = {
    0x0000, 0x0000, 0x000B, 0x0002, 0x000F, 0x0003, 0x0011, 0x0005, 0x0007,
    0x0003, 0x0006, 0x0005, 0x0006, 0x0007, 0x000A, 0x0007, 0x0005, 0x000D,
    0x0009, 0x0006, 0x000B, 0x0006, 0x0009, 0x0008, 0x000B, 0x0008, 0x0014,
    0x0007, 0x0017, 0x0009, 0x0019, 0x000C, 0x0010, 0x000C, 0x0014, 0x000D,
    0x0014, 0x0012, 0x001A, 0x0013, 0x001A, 0x0013, 0x000A, 0x0012, 0x000A,
    0x0012, 0x000A, 0x0012, 0x001A, 0x0013, 0x0013, 0x0015, 0x0015, 0x001B,
    0x0012, 0x0029, 0x0012, 0x0021, 0x0018, 0x0019, 0x0015, 0x001B, 0x0012,
    0x0019, 0x0014, 0x0014, 0x0018, 0x0019, 0x001B, 0x001F, 0x000D, 0x0011,
    0x0009, 0x0012, 0x0009, 0x0017, 0x0016, 0x0025, 0x0012, 0x0018, 0x0012,
    0x0018, 0x000B, 0x0019, 0x0006, 0x0022, 0x000B, 0x0027, 0x000E, 0x0022,
    0x0012, 0x0021, 0x0012, 0x001D, 0x0012, 0x0021, 0x0012, 0x0021, 0x0012,
    0x0021, 0x0012, 0x0021, 0x0012, 0x0021, 0x0012, 0x0021, 0x0012, 0x0021,
    0x0012, 0x0021, 0x000E, 0x0023, 0x0012, 0x0021, 0x000E, 0x0025, 0x000D,
    0x0025, 0x000D, 0x0025, 0x000D, 0x0027, 0x0010, 0x0027, 0x0013, 0x0027,
    0x0017, 0x0027, 0x0012, 0x0021, 0x0017, 0x0027, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
};

static s16 D_us_80180EE0[] = {
    0x0000, 0x0000, 0x001B, 0x0016, 0x0020, 0x0014, 0x002A, 0x0013, 0x0016,
    0x001D, 0x001A, 0x0026, 0x0021, 0x002B, 0x0027, 0x0027, 0x0031, 0x0026,
    0x0019, 0x001E, 0x001E, 0x001B, 0x001C, 0x0021, 0x0021, 0x001F, 0x0035,
    0x000C, 0x003F, 0x000C, 0x004A, 0x0016, 0x003B, 0x001D, 0x0043, 0x0018,
    0x0043, 0x0028, 0x004E, 0x0028, 0x0051, 0x002A, 0x0036, 0x0029, 0x003E,
    0x002C, 0x003F, 0x0034, 0x0048, 0x0030, 0x003E, 0x0036, 0x0049, 0x0032,
    0x0046, 0x0036, 0x0044, 0x0036, 0x0041, 0x003B, 0x0035, 0x0041, 0x002D,
    0x003C, 0x0032, 0x0036, 0x0051, 0x003E, 0x004E, 0x0044, 0x002A, 0x003D,
    0x002A, 0x0045, 0x002D, 0x0047, 0x003A, 0x0046, 0x0035, 0x0046, 0x0035,
    0x0049, 0x0034, 0x0050, 0x0031, 0x0052, 0x0032, 0x0055, 0x0037, 0x0056,
    0x003F, 0x0052, 0x003E, 0x0056, 0x004F, 0x0054, 0x005B, 0x005E, 0x005E,
    0x006D, 0x0056, 0x0064, 0x004B, 0x0071, 0x0046, 0x0069, 0x0045, 0x0071,
    0x0044, 0x006E, 0x003C, 0x0066, 0x0040, 0x0066, 0x0037, 0x006A, 0x0032,
    0x006A, 0x002F, 0x006C, 0x0022, 0x006A, 0x0022, 0x0071, 0x0032, 0x0072,
    0x003B, 0x0071, 0x0063, 0x005F, 0x0044, 0x006E, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
};

static u8 D_us_80180FFC[] = {
    0x04, 0x01, 0x0A, 0x02, 0x05, 0x04, 0x09, 0x0A, 0x09, 0x0A, 0x0B, 0x0C,
    0x05, 0x09, 0x06, 0x0B, 0x0A, 0x02, 0x0C, 0x03, 0x06, 0x0B, 0x07, 0x0C,
    0x0C, 0x03, 0x07, 0x0D, 0x07, 0x0D, 0x08, 0x10, 0x0D, 0x0E, 0x10, 0x0F,
    0x08, 0x10, 0x15, 0x12, 0x10, 0x0F, 0x11, 0x14, 0x10, 0x11, 0x12, 0x13,
    0x12, 0x13, 0x19, 0x1D, 0x19, 0x1D, 0x1F, 0x1E, 0x2A, 0x29, 0x2B, 0x2C,
    0x23, 0x20, 0x24, 0x1F, 0x24, 0x1F, 0x25, 0x27, 0x25, 0x27, 0x29, 0x28,
    0x29, 0x28, 0x2C, 0x2E, 0x2C, 0x2E, 0x37, 0x38, 0x37, 0x38, 0x3F, 0x41,
    0x39, 0x37, 0x3E, 0x3F, 0x3A, 0x39, 0x3B, 0x3E, 0x3C, 0x3B, 0x3D, 0x3E,
    0x1C, 0x1B, 0x26, 0x22, 0x1B, 0x1A, 0x22, 0x21, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};

static u8 D_us_801810BC[] = {
    0x04, 0x01, 0x09, 0x0A, 0x01, 0x02, 0x0A, 0x03, 0x04, 0x09, 0x05, 0x0B,
    0x09, 0x0A, 0x0B, 0x0C, 0x05, 0x0B, 0x06, 0x07, 0x0B, 0x0C, 0x07, 0x08,
    0x0A, 0x03, 0x0C, 0x08, 0x03, 0x0D, 0x08, 0x10, 0x0D, 0x0E, 0x10, 0x11,
    0x08, 0x10, 0x15, 0x12, 0x10, 0x11, 0x12, 0x13, 0x0E, 0x0F, 0x11, 0x13,
    0x0F, 0x14, 0x13, 0x18, 0x15, 0x12, 0x16, 0x17, 0x12, 0x13, 0x1C, 0x18,
    0x17, 0x12, 0x19, 0x1C, 0x18, 0x14, 0x1A, 0x21, 0x1A, 0x21, 0x1B, 0x22,
    0x1C, 0x1B, 0x1D, 0x22, 0x19, 0x1C, 0x1E, 0x1D, 0x20, 0x19, 0x1F, 0x1E,
    0x23, 0x20, 0x24, 0x1F, 0x24, 0x1F, 0x25, 0x1E, 0x1E, 0x1D, 0x26, 0x22,
    0x25, 0x1E, 0x27, 0x26, 0x25, 0x27, 0x29, 0x28, 0x29, 0x28, 0x2C, 0x2D,
    0x2A, 0x29, 0x2B, 0x2C, 0x26, 0x22, 0x28, 0x2D, 0x2C, 0x2D, 0x2E, 0x2F,
    0x2C, 0x2E, 0x37, 0x38, 0x37, 0x38, 0x3F, 0x41, 0x39, 0x37, 0x3E, 0x3F,
    0x3B, 0x3A, 0x3E, 0x39, 0x3C, 0x3B, 0x3D, 0x3E, 0x2E, 0x2F, 0x32, 0x30,
    0x32, 0x30, 0x31, 0x40, 0x34, 0x32, 0x33, 0x31, 0x36, 0x34, 0x35, 0x33,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};

static void func_us_801B053C(void) {
    s32 i;
    Primitive* prim;
    s16* pos;
    u8* indexes;
    s16* var_t0;

    u8 u, v;

    prim = g_CurrentEntity->ext.et_801B0930.prim7C;
    pos = D_us_80180DC4;
    indexes = D_us_80180FFC;

    u = 0x60;
    v = 0x40;

    for (i = 0; i < 26; i++) {
        prim->tpage = 0x13;
        prim->clut = 0x209;
        prim->u0 = u + (*indexes * 2)[pos];
        prim->v0 = v + (*indexes++ * 2)[pos + 1];
        prim->u1 = u + (*indexes * 2)[pos];
        prim->v1 = v + (*indexes++ * 2)[pos + 1];
        prim->u2 = u + (*indexes * 2)[pos];
        prim->v2 = v + (*indexes++ * 2)[pos + 1];
        prim->u3 = u + (*indexes * 2)[pos];
        prim->v3 = v + (*indexes++ * 2)[pos + 1];

        prim->r0 = prim->g0 = prim->b0 = 0x80;
        LOW(prim->r1) = LOW(prim->r0);
        LOW(prim->r2) = LOW(prim->r0);
        LOW(prim->r3) = LOW(prim->r0);
        prim->priority = 0xD0;
        prim->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS | DRAW_TRANSP;
        prim = prim->next;
    }
    g_CurrentEntity->ext.et_801B0930.prim0 = prim;
    pos = D_us_80180EE0;
    indexes = D_us_801810BC;
    u = 0;
    v = 0x80;
    for (i = 0; i < 39; i++) {
        prim->tpage = 0x110;
        prim->clut = 0x20B;
        prim->u0 = u + (*indexes * 2)[pos];
        prim->v0 = v + (*indexes++ * 2)[pos + 1];
        prim->u1 = u + (*indexes * 2)[pos];
        prim->v1 = v + (*indexes++ * 2)[pos + 1];
        prim->u2 = u + (*indexes * 2)[pos];
        prim->v2 = v + (*indexes++ * 2)[pos + 1];
        prim->u3 = u + (*indexes * 2)[pos];
        prim->v3 = v + (*indexes++ * 2)[pos + 1];
        prim->r0 = prim->g0 = prim->b0 = 0;
        LOW(prim->r1) = LOW(prim->r0);
        LOW(prim->r2) = LOW(prim->r0);
        LOW(prim->r3) = LOW(prim->r0);
        prim->priority = 0xD0;
        prim->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS | DRAW_TRANSP;
        prim = prim->next;
    }

    pos = D_us_80180DC4;
    for (i = 0; i < 66; i++) {
        D_us_801CD6E4[i].x.val = (*pos - 0x10) * FIX(1.0);
        pos++;
        D_us_801CD6E4[i].y.val = (*pos - 0x27) * FIX(1.0);
        pos++;
    }
}

static void func_us_801B088C(void) {
    s32 i;
    s32 x;
    s32 y;
    s32 t1, t2, t3, t4;
    s16* var_a1;
    s16* var_a0;

    var_a1 = D_us_80180DC4;
    var_a0 = D_us_80180EE0;

    t1 = -0x10;
    t2 = -0x27;
    t3 = -0x40;
    t4 = -0x70;

    for (i = 0; i < 66; i++) {
        x = (t3 + *var_a0) - (t1 + *var_a1);
        x = (x * FIX(1.0)) / 128;
        D_us_801CD6E4[i].x.val = D_us_801CD6E4[i].x.val + x;
        var_a1++;
        var_a0++;

        y = (t4 + *var_a0) - (t2 + *var_a1);
        y = (y * FIX(1.0)) / 128;
        D_us_801CD6E4[i].y.val = D_us_801CD6E4[i].y.val + y;
        var_a1++;
        var_a0++;
    }
}

extern EInit g_EInitOlroxAfterImage;
extern s32 D_us_801CE5B0;

static s16 D_us_8018117C[] = {
    4, 16, 8, 16, 4, 64, 12, 6, 128, 0,
};

void func_us_801B0930(Entity* self) {
    Primitive* prim;
    s32 primIndex;
    s32 i;
    s16 x;
    s16 y;
    u8* indexes;
    s32* pos;
    u8 brightness;
    Entity* entity;
    DR_ENV* drEnv;
    RECT clip;
    DRAWENV drawEnv;
    GpuBuffer* buffer;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitOlroxAfterImage);
        self->hitboxState = 0;
        self->animCurFrame = 0;
        self->blendMode |= BLEND_ADD | BLEND_TRANSP;
        self->flags &= ~FLAG_POS_CAMERA_LOCKED;
        D_us_801CE5B0 = 1;
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 0x44);
        if (primIndex != -1) {
            self->flags |= FLAG_HAS_PRIMS;
            self->primIndex = primIndex;
            prim = &g_PrimBuf[primIndex];
            self->ext.et_801B0930.prim1 = prim;
            prim->tpage = 0x110;
            if (!self->facingLeft) {
                prim->u0 = prim->u2 = 0;
                prim->u1 = prim->u3 = prim->u0 + 0x80;
            } else {
                prim->u1 = prim->u3 = 0;
                prim->u0 = prim->u2 = prim->u1 + 0x7F;
            }
            prim->v0 = prim->v1 = 0;
            prim->v2 = prim->v3 = prim->v0 + 0x80;
            if (!self->facingLeft) {
                prim->x0 = prim->x2 = self->posX.i.hi - 0x3C;
                prim->x1 = prim->x3 = self->posX.i.hi + 0x44;
            } else {
                prim->x0 = prim->x2 = self->posX.i.hi - 0x44;
                prim->x1 = prim->x3 = self->posX.i.hi + 0x3C;
            }

            prim->y0 = prim->y1 = self->posY.i.hi - 0x70;
            prim->y2 = prim->y3 = self->posY.i.hi + 0x10;
            prim->drawMode = DRAW_HIDE | DRAW_UNK02;
            prim->priority = 0xE0;
            prim = prim->next;
            self->ext.et_801B0930.prim2 = prim;
            drEnv = g_api.func_800EDB08((POLY_GT4*)prim);
            if (!drEnv) {
                g_api.FreePrimitives(primIndex);
                self->step = 0;
                return;
            } else {
                prim->type = PRIM_ENV;
                prim->drawMode = DRAW_HIDE;
                prim = prim->next;
                drEnv = g_api.func_800EDB08((POLY_GT4*)prim);
                if (prim == NULL) {
                    g_api.FreePrimitives(primIndex);
                    self->step = 0;
                    return;
                }
            }
            prim->type = PRIM_ENV;
            prim->drawMode = DRAW_HIDE;
            prim = prim->next;
            self->ext.et_801B0930.prim7C = prim;
            while (prim != NULL) {
                prim->priority = 0xD0;
                prim->drawMode = DRAW_HIDE;
                prim = prim->next;
            }
        } else {
            self->step = 0;
            FntPrint("can't get effect works!\n");
            break;
        }
        // fallthrough

    case 1:
        prim = self->ext.et_801B0930.prim2;
        drawEnv = g_CurrentBuffer->draw;
        drawEnv.isbg = 1;
        clip.x = 0;
        clip.y = 0x100;
        clip.w = 0x7F;
        clip.h = 0x100;
        drawEnv.clip = clip;
        drawEnv.ofs[0] = 0;
#ifdef VERSION_PSP
        drawEnv.ofs[1] = 0x100;
#else
        drawEnv.ofs[1] = 0;
#endif
        drEnv = (DR_ENV*)LOW(prim->r1);
        SetDrawEnv(drEnv, &drawEnv);

        prim->priority = 0xCB;
        prim->drawMode = DRAW_DEFAULT;
        prim = prim->next;
        prim->priority = 0xD4;
        prim->drawMode = DRAW_UNK_800;

        entity = self + 1;
        DestroyEntity(entity);
        CreateEntityFromEntity(E_ID(UNK_33), self, entity);
        entity->posX.i.hi = 0x40;
#ifdef VERSION_PSP
        entity->posY.i.hi = 0xEC;
#else
        entity->posY.i.hi = 0x1EC;
#endif
        entity->params = self->facingLeft;

        self->step++;
        break;

    case 2:
        func_us_801B053C();
        prim = (Primitive*)self->ext.et_801B0930.prim2;
        drEnv = (DR_ENV*)LOW(prim->r1);
        drawEnv = g_CurrentBuffer->draw;
        drawEnv.isbg = 1;
        drawEnv.dtd = 0;
        clip.x = 0;
        clip.y = 0x100;
        clip.w = 0x80;
        clip.h = 0x80;
        drawEnv.clip = clip;
        drawEnv.ofs[0] = 0;
        drawEnv.ofs[1] = 0x100;
        SetDrawEnv(drEnv, &drawEnv);
        prim->priority = 0xCF;
        prim->drawMode = DRAW_DEFAULT;
        prim = prim->next;
        prim->priority = 0xD1;
        prim->drawMode = DRAW_UNK_800;
        self->animCurFrame = 0;
        self->zPriority = 0xA0;
        prim = self->ext.et_801B0930.prim1;
        self->posX.i.hi = prim->x0 + 0x40;
        self->posY.i.hi = prim->y0 + 0x70;
        self->flags |= FLAG_POS_CAMERA_LOCKED;
        self->ext.et_801B0930.timer0 = 0x80;
        self->ext.et_801B0930.brightness = -0x8000;
        self->ext.et_801B0930.timer1 = D_us_8018117C[0];
        self->pose = 0;
        self->step_s = 0;
        g_api.PlaySfx(SFX_OLROX_MONSTER_PAIN);
        self->step++;
        break;

    case 3:
        prim = self->ext.et_801B0930.prim1;
        prim->drawMode = DRAW_UNK02;
        if (self->ext.et_801B0930.timer0 > 0) {
            func_us_801B088C();
        }
        brightness = self->ext.et_801B0930.brightness >> 8;
        if (brightness > 0x80) {
            brightness = 0x80;
        }
        prim = self->ext.et_801B0930.prim7C;
        x = 0x40;
        y = 0x70;
        pos = (s32*)D_us_801CD6E4;
        indexes = D_us_80180FFC;

        for (i = 0; i < 26; i++) {
            prim->x0 = ((*indexes * 2)[pos] >> 16) + x;
            prim->y0 = ((*indexes++ * 2)[pos + 1] >> 16) + y;
            prim->x1 = ((*indexes * 2)[pos] >> 16) + x;
            prim->y1 = ((*indexes++ * 2)[pos + 1] >> 16) + y;
            prim->x2 = ((*indexes * 2)[pos] >> 16) + x;
            prim->y2 = ((*indexes++ * 2)[pos + 1] >> 16) + y;
            prim->x3 = ((*indexes * 2)[pos] >> 16) + x;
            prim->y3 = ((*indexes++ * 2)[pos + 1] >> 16) + y;

            prim->r0 = prim->g0 = prim->b0 = brightness;
            LOW(prim->r1) = LOW(prim->r0);
            LOW(prim->r2) = LOW(prim->r0);
            LOW(prim->r3) = LOW(prim->r0);
            prim = prim->next;
        }
        brightness = 0x80 - brightness;
        prim = self->ext.et_801B0930.prim0;
        pos = (s32*)D_us_801CD6E4;
        indexes = D_us_801810BC;
        x = 0x40;
        y = 0x70;

        for (i = 0; i < 39; i++) {
            prim->x0 = ((*indexes * 2)[pos] >> 16) + x;
            prim->y0 = ((*indexes++ * 2)[pos + 1] >> 16) + y;
            prim->x1 = ((*indexes * 2)[pos] >> 16) + x;
            prim->y1 = ((*indexes++ * 2)[pos + 1] >> 16) + y;
            prim->x2 = ((*indexes * 2)[pos] >> 16) + x;
            prim->y2 = ((*indexes++ * 2)[pos + 1] >> 16) + y;
            prim->x3 = ((*indexes * 2)[pos] >> 16) + x;
            prim->y3 = ((*indexes++ * 2)[pos + 1] >> 16) + y;

            prim->r0 = prim->g0 = prim->b0 = brightness;
            LOW(prim->r1) = LOW(prim->r0);
            LOW(prim->r2) = LOW(prim->r0);
            LOW(prim->r3) = LOW(prim->r0);
            prim = prim->next;
        }
        self->ext.et_801B0930.timer0--;
        self->ext.et_801B0930.brightness =
            (self->ext.et_801B0930.timer0 + 16) * 256;
        if (self->ext.et_801B0930.timer0 < 0 &&
            self->ext.et_801B0930.brightness < 0) {
            self->ext.et_801B0930.timer0 = 0x20;
            self->step = 5;
        }
        // fallthrough

    case 4:
        if (!(g_Timer & 7)) {
            g_api.PlaySfx(SFX_OLROX_TRANSFORM);
        }

        switch (self->step_s) {
        case 0:
            if (!--self->ext.et_801B0930.timer1) {
                self->pose++;
                self->ext.et_801B0930.timer1 = D_us_8018117C[self->pose];
                self->step = 4;
                self->step_s++;
            }
            break;
        case 1:
            if (!(self->ext.et_801B0930.timer1 % 8)) {
                prim = self->ext.et_801B0930.prim1;

                if (self->ext.et_801B0930.timer1 >
                    (D_us_8018117C[self->pose] / 2)) {
                    prim->y0 = prim->y1 -= 2;
                    prim->x1 = prim->x3 += 1;
                    prim->x0 = prim->x2 -= 1;
                } else {
                    prim->y0 = prim->y1 += 2;
                    prim->x1 = prim->x3 -= 1;
                    prim->x0 = prim->x2 += 1;
                }
            }

            if (!--self->ext.et_801B0930.timer1) {
                prim = self->ext.et_801B0930.prim1;
                prim->x1 = prim->x3 = self->posX.i.hi + 0x40;
                prim->x0 = prim->x2 = self->posX.i.hi - 0x40;
                prim->y0 = prim->y1 = self->posY.i.hi - 0x70;
                self->pose++;
                self->ext.et_801B0930.timer1 = D_us_8018117C[self->pose];
                self->step = 3;
                self->step_s--;
            }
            break;
        }
        break;

    case 5:
        if (!--self->ext.et_801B0930.timer0) {
            self->step++;
        }
        break;

    case 6:
        D_us_801CE5B0 = 0;
        entity = self + 1;
        entity->posX.i.hi = self->posX.i.hi;
        entity->posY.i.hi = 0x1CC - g_Tilemap.scrollY.i.hi;
        DestroyEntity(self);
        break;
    }
}
