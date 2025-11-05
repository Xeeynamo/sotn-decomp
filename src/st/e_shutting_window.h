// SPDX-License-Identifier: AGPL-3.0-or-later

static SVECTOR window_vec1 = {0, -120, 0};
static SVECTOR window_vec2 = {25, -120, 0};
static SVECTOR window_vec3 = {0, 0, 0};
static SVECTOR window_vec4 = {25, 0, 0};

static SVECTOR window_vec5 = {0, -120, 0};
static SVECTOR window_vec6 = {-25, -120, 0};
static SVECTOR window_vec7 = {0, 0, 0};
static SVECTOR window_vec8 = {-25, 0, 0};

static SVEC4 windowVectors[2] = {
    {&window_vec1, &window_vec2, &window_vec3, &window_vec4},
    {&window_vec5, &window_vec6, &window_vec7, &window_vec8}};

void EntityShuttingWindow(Entity* self) {
    Primitive* prim;
    s32 primIndex;
    s32 p;
    s32 flag;
    SVECTOR svec;
    SVEC4* svec4;
    VECTOR vec;
    MATRIX mtx;
    s32 i;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitParticle);
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 2);
        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags |= FLAG_HAS_PRIMS;
        self->primIndex = primIndex;
        prim = &g_PrimBuf[primIndex];
        self->ext.shuttingWindow.prim = prim;
        while (prim != NULL) {
            prim->tpage = 0xF;
            prim->clut = 0xD;
            prim->u0 = prim->u2 = 0x9C;
            prim->u1 = prim->u3 = 0x84;
            prim->v0 = prim->v1 = 4;
            prim->v2 = prim->v3 = 0x7C;
            prim->priority = 0x5F;
            prim->drawMode = DRAW_UNK02;
            prim = prim->next;
        }

    case 1:
        self->ext.shuttingWindow.unk80 += 8;
        if (self->ext.shuttingWindow.unk80 > 0x300) {
            self->ext.shuttingWindow.unk80 = 0x300;
            self->ext.shuttingWindow.unk82 = 0;
            self->step++;
        }
        break;

    case 2:
        self->ext.shuttingWindow.unk80 += self->ext.shuttingWindow.unk82;
        self->ext.shuttingWindow.unk82 -= 4;
        if (self->ext.shuttingWindow.unk80 < 0) {
            PlaySfxPositional(SFX_SHUTTING_WINDOW);
            self->ext.shuttingWindow.unk80 = 0;
            self->ext.shuttingWindow.timer = 32;
            self->step++;
        }
        break;

    case 3:
        if (!--self->ext.shuttingWindow.timer) {
            self->step = 1;
        }
        break;
    }
    SetGeomScreen(0x400);
    SetGeomOffset(self->posX.i.hi, self->posY.i.hi);

    for (prim = self->ext.shuttingWindow.prim, svec4 = windowVectors, i = 0;
         i < 2; svec4++, prim = prim->next, i++) {
        svec.vx = 0;
        if (i != 0) {
            svec.vy = self->ext.shuttingWindow.unk80;
        } else {
            svec.vy = -self->ext.shuttingWindow.unk80;
        }
        svec.vz = 0;
        RotMatrix(&svec, &mtx);
        if (i) {
            vec.vx = 0x19;
        } else {
            vec.vx = -0x18;
        }
        vec.vy = 0;
        vec.vz = 0x400;
        TransMatrix(&mtx, &vec);
        SetRotMatrix(&mtx);
        SetTransMatrix(&mtx);
        RotTransPers4(svec4->v0, svec4->v1, svec4->v2, svec4->v3,
                      (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2,
                      (long*)&prim->x3, (long*)&p, (long*)&flag);
    }
}
