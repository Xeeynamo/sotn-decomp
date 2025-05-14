// SPDX-License-Identifier: AGPL-3.0-or-later
#define UVWH(u, v, w, h) u, v, w, h

static u8 bush_uvwh[] = {
    UVWH(0x10, 0xC8, 0x20, 0x1F), UVWH(0x30, 0xC8, 0x20, 0x1F),
    UVWH(0x50, 0xD0, 0x20, 0x2F), UVWH(0xB8, 0xB8, 0x47, 0x47),
    UVWH(0xAE, 0xC9, 0x0A, 0x32), UVWH(0xAD, 0xC9, 0x0C, 0x28)};
// Seems to be used when continuing a bush from one of the above starts?
static u8 bush_uvwh_cont[] = {
    UVWH(0x80, 0x80, 0x38, 0x42), UVWH(0x80, 0x80, 0x2C, 0x34)};
// clang-format off
static s16 bush_unk_data[] = {0, 20, 0, 32, 1, 32, 0, 8, 2, 20, 1, 16, 0xFFFF, 0,
                           3, 63, 0xFFFF, 0,
                           4, 64, 4, 96, 0xFFFF, 0,
                           5, 80, 5, 96, 5, 32, 0xFFFF, 0};
// clang-format on
// VZ, Priority, Clut, and an X value. 4 such sets.
static s16 bush_render_data[] = {
    0x00C0, 0x005E, 0x0017, 0x0080, 0x0200, 0x005B, 0x0014, 0x003F,
    0x0140, 0x005D, 0x003C, 0x00A0, 0x01C0, 0x005C, 0x003C, 0x00D0};
static s16* bush_unk_starts[] = {&bush_unk_data[0], &bush_unk_data[14],
                                 &bush_unk_data[18], &bush_unk_data[24]};
static s16 backgroundTreePositions[][2] = {
    {0x200, 0}, {0x280, 12}, {0x300, 4}, {0x380, 16}};
static u16 backgroundTreeCluts[] = {0x15, 0x46, 0x47, 0x48};
static SVECTOR backgroundBushZeroVec = {0, 0, 0};
static SVECTOR backgroundTreeZeroVec = {0, 0, 0};

void EntityBackgroundBushes(Entity* self) {
    byte stackpad[8];

    // Lots of ugly pointers
    u8* var_s1;
    s16* var_s4;
    s16* var_s5;
    s16** var_s8;
    Primitive* prim;
    s32 primIndex;
    s32 i;
    s32 yOffset;
    s16 xPos;
    s16 yPos;
    s32 rotTransXYResult;
    s32 unused1; // return args for rottranspers
    s32 unused2; // we don't use them.
    VECTOR trans;
    MATRIX m;

    if (!self->step) {
        InitializeEntity(g_EInitStInteractable);
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 0x48);
        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags |= FLAG_HAS_PRIMS;
        self->primIndex = primIndex;
        prim = &g_PrimBuf[primIndex];
        self->ext.prim = prim;
        while (prim != NULL) {
            prim->tpage = 0xF;
            prim->drawMode = DRAW_HIDE;
            prim = prim->next;
        }
    }
    SetGeomScreen(0x400);
    SetGeomOffset(0x80, self->posY.i.hi);
    RotMatrix(&backgroundBushZeroVec, &m);
    SetRotMatrix(&m);
    if (self->params) {
        trans.vx = self->posX.i.hi - 0x200;
    } else {
        trans.vx = self->posX.i.hi + 0x200;
    }
    trans.vy = 0;
    var_s5 = bush_render_data;
    var_s8 = bush_unk_starts;
    prim = self->ext.prim;
    for (i = 0; i < 4; i++, var_s8++, var_s5 += 4) {
        trans.vz = var_s5[0] + 0x400;
        TransMatrix(&m, &trans);
        SetTransMatrix(&m);
        RotTransPers(
            &backgroundBushZeroVec, &rotTransXYResult, &unused1, &unused2);
        // Split out the upper and lower halfword of rotTransXYResult
        xPos = rotTransXYResult & 0xFFFF;
        yPos = rotTransXYResult >> 16;
        xPos = xPos % var_s5[3];
        xPos -= var_s5[3];
        yPos = self->posY.i.hi;
        var_s4 = *var_s8;
        while (xPos < 0x140) {
            var_s1 = &bush_uvwh[0];
            var_s1 += ((*var_s4++) * 4);
            prim->u0 = prim->u2 = var_s1[0];
            prim->u1 = prim->u3 = prim->u0 + var_s1[2];
            prim->v0 = prim->v1 = var_s1[1];
            prim->v2 = prim->v3 = prim->v0 + var_s1[3];
            prim->x0 = prim->x2 = xPos - var_s1[2] / 2;
            prim->x1 = prim->x3 = xPos + var_s1[2] / 2;
            prim->y0 = prim->y1 = yPos - var_s1[3];
            prim->y2 = prim->y3 = yPos;
            prim->clut = var_s5[2];
            prim->priority = var_s5[1];
            prim->drawMode = DRAW_UNK02;
            prim = prim->next;

            if (prim == NULL) {
                return;
            }
            // Need to figure out what this means.
            if (i > 1) {
                yOffset = var_s1[3];
                var_s1 = &bush_uvwh_cont[0];
                prim->u0 = prim->u2 = var_s1[0];
                prim->u1 = prim->u3 = prim->u0 + var_s1[2];
                prim->v0 = prim->v1 = var_s1[1];
                prim->v2 = prim->v3 = prim->v0 + var_s1[3];
                var_s1 += (i - 2) * 4;
                prim->x0 = prim->x2 = xPos - var_s1[2] / 2;
                prim->x1 = prim->x3 = xPos + var_s1[2] / 2;
                prim->y0 = prim->y1 = (yPos - yOffset) - var_s1[3];
                prim->y2 = prim->y3 = (yPos - yOffset);
                prim->clut = 0x17;
                if (i > 2) {
                    prim->clut = 0x49;
                }
                prim->priority = var_s5[1];
                prim->drawMode = DRAW_UNK02;
                prim = prim->next;
                if (prim == NULL) {
                    return;
                }
            }
            xPos += *var_s4++;
            if (*var_s4 == -1) {
                var_s4 = *var_s8;
            }
        }
    }
    while (prim != NULL) {
        prim->drawMode = DRAW_HIDE;
        prim = prim->next;
    }
}

void EntityBackgroundTrees(Entity* self) {
    volatile char pad[8]; //! FAKE
    long sxy, p, flag;
    Primitive* prim;
    s32 primIndex;
    VECTOR vec;
    MATRIX mtx;
    s32 zVal;
    s32 posX;
    s32 posY;

    if (!self->step) {
        InitializeEntity(g_EInitStInteractable);
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 32);
        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags |= FLAG_HAS_PRIMS;
        self->primIndex = primIndex;
        prim = &g_PrimBuf[primIndex];
        self->ext.prim = prim;
        while (prim != NULL) {
            prim->tpage = 0xF;
            prim->clut = backgroundTreeCluts[self->params & 0xF];
            prim->u0 = prim->u2 = 0xBF;
            prim->u1 = prim->u3 = 0xFF;
            prim->v0 = prim->v1 = 0x80;
            prim->v2 = prim->v3 = 0xB8;
            prim->priority = 0x5A;
            prim->drawMode = DRAW_HIDE;
            prim = prim->next;
        }
    }
    zVal = backgroundTreePositions[self->params & 0xF][0];

    SetGeomScreen(0x400);
    if (self->params & 0x100) {
        SetGeomOffset(0x80, 0x98);
    } else {
        SetGeomOffset(0x80, 0x80);
    }

    RotMatrix(&backgroundTreeZeroVec, &mtx);
    vec.vx = self->posX.i.hi - 128;
    vec.vy = self->posY.i.hi - 128;
    vec.vz = zVal + 0x400;
    TransMatrix(&mtx, &vec);
    SetRotMatrix(&mtx);
    SetTransMatrix(&mtx);
    RotTransPers(&backgroundTreeZeroVec, &sxy, &p, &flag);
    posX = sxy & 0xFFFF;
    posY = sxy >> 0x10;

    posX %= 64;
    posX -= 64;
    posX -= backgroundTreePositions[self->params & 0xF][1];
    prim = self->ext.prim;
    while (posX < 320) {
        prim->x0 = prim->x2 = posX;
        prim->x1 = prim->x3 = posX + 64;
        prim->y0 = prim->y1 = posY - 56;
        prim->y2 = prim->y3 = posY;
        prim->drawMode = DRAW_UNK02;
        prim = prim->next;
        posX += 64;
    }

    while (prim != NULL) {
        prim->drawMode = DRAW_HIDE;
        prim = prim->next;
    }
}
