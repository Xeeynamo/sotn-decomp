// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rbo0.h"
#include <scratchpad.h>

extern s32 D_us_801806B0;

static u8 D_us_801819BC[] = {
    0x03, 0x02, 0x18, 0x46, 0x18, 0x02, 0x2C, 0x46, 0x33, 0x02,
    0x5C, 0x46, 0x71, 0x01, 0x7E, 0x1E, 0x71, 0x01, 0x7E, 0x1E,
    0x61, 0x01, 0x6E, 0x36, 0x61, 0x01, 0x6E, 0x36,
};

static SVECTOR D_us_801819D8 = {
    0xFFEB,
    0xFFE3,
    0xFFF8,
    0x0000,
};

static SVECTOR D_us_801819E0 = {
    0x0000,
    0xFFE3,
    0xFFF8,
    0x0000,
};

static SVECTOR D_us_801819E8 = {
    0xFFEB,
    0x0026,
    0xFFF8,
    0x0000,
};

static SVECTOR D_us_801819F0 = {
    0x0000,
    0x0026,
    0xFFF8,
    0x0000,
};

static SVECTOR D_us_801819F8 = {
    0x0000,
    0xFFE3,
    0xFFF8,
    0x0000,
};

static SVECTOR D_us_80181A00 = {
    0x0015,
    0xFFE3,
    0xFFF8,
    0x0000,
};

static SVECTOR D_us_80181A08 = {
    0x0000,
    0x0026,
    0xFFF8,
    0x0000,
};

static SVECTOR D_us_80181A10 = {
    0x0015,
    0x0026,
    0xFFF8,
    0x0000,
};

static SVECTOR D_us_80181A18 = {
    0x0000,
    0xFFE3,
    0xFFF8,
    0x0000,
};

static SVECTOR D_us_80181A20 = {
    0x0015,
    0xFFE3,
    0xFFF8,
    0x0000,
};

static SVECTOR D_us_80181A28 = {
    0x0000,
    0x0026,
    0xFFF8,
    0x0000,
};

static SVECTOR D_us_80181A30 = {
    0x0015,
    0x0026,
    0xFFF8,
    0x0000,
};

static SVECTOR D_us_80181A38 = {
    0xFFEB,
    0xFFE3,
    0xFFF8,
    0x0000,
};

static SVECTOR D_us_80181A40 = {
    0x0000,
    0xFFE3,
    0xFFF8,
    0x0000,
};

static SVECTOR D_us_80181A48 = {
    0xFFEB,
    0x0026,
    0xFFF8,
    0x0000,
};

static SVECTOR D_us_80181A50 = {
    0x0000,
    0x0026,
    0xFFF8,
    0x0000,
};

static SVECTOR D_us_80181A58 = {
    0xFFEB,
    0xFFE3,
    0x0008,
    0x0000,
};

static SVECTOR D_us_80181A60 = {
    0x0015,
    0xFFE3,
    0x0008,
    0x0000,
};

static SVECTOR D_us_80181A68 = {
    0xFFEB,
    0x0026,
    0x0008,
    0x0000,
};

static SVECTOR D_us_80181A70 = {
    0x0015,
    0x0026,
    0x0008,
    0x0000,
};

static SVECTOR D_us_80181A78 = {
    0x0000,
    0xFFE1,
    0xFFF8,
    0x0000,
};

static SVECTOR D_us_80181A80 = {
    0x0000,
    0xFFE1,
    0x0008,
    0x0000,
};

static SVECTOR D_us_80181A88 = {
    0xFFEB,
    0xFFF1,
    0xFFF8,
    0x0000,
};

static SVECTOR D_us_80181A90 = {
    0xFFEB,
    0xFFF1,
    0x0008,
    0x0000,
};

static SVECTOR D_us_80181A98 = {
    0x0015,
    0xFFF1,
    0xFFF8,
    0x0000,
};

static SVECTOR D_us_80181AA0 = {
    0x0015,
    0xFFF1,
    0x0008,
    0x0000,
};

static SVECTOR D_us_80181AA8 = {
    0xFFEE,
    0x0026,
    0xFFF8,
    0x0000,
};

static SVECTOR D_us_80181AB0 = {
    0xFFEE,
    0x0026,
    0x0008,
    0x0000,
};

static SVECTOR D_us_80181AB8 = {
    0x0012,
    0x0026,
    0xFFF8,
    0x0000,
};

static SVECTOR D_us_80181AC0 = {
    0x0012,
    0x0026,
    0x0008,
    0x0000,
};

static SVECTOR* D_us_80181AC8[] = {
    &D_us_801819D8, &D_us_801819E0, &D_us_801819E8, &D_us_801819F0,
    &D_us_801819F8, &D_us_80181A00, &D_us_80181A08, &D_us_80181A10,
    &D_us_80181A58, &D_us_80181A60, &D_us_80181A68, &D_us_80181A70,
    &D_us_80181A78, &D_us_80181A80, &D_us_80181A88, &D_us_80181A90,
    &D_us_80181A78, &D_us_80181A80, &D_us_80181A98, &D_us_80181AA0,
    &D_us_80181A88, &D_us_80181A90, &D_us_80181AA8, &D_us_80181AB0,
    &D_us_80181A98, &D_us_80181AA0, &D_us_80181AB8, &D_us_80181AC0,
};

static SVECTOR* D_us_80181B38[] = {
    &D_us_80181A18, &D_us_80181A20, &D_us_80181A28, &D_us_80181A30,
    &D_us_80181A38, &D_us_80181A40, &D_us_80181A48, &D_us_80181A50,
    &D_us_80181A58, &D_us_80181A60, &D_us_80181A68, &D_us_80181A70,
    &D_us_80181A78, &D_us_80181A80, &D_us_80181A88, &D_us_80181A90,
    &D_us_80181A78, &D_us_80181A80, &D_us_80181A98, &D_us_80181AA0,
    &D_us_80181A88, &D_us_80181A90, &D_us_80181AA8, &D_us_80181AB0,
    &D_us_80181A98, &D_us_80181AA0, &D_us_80181AB8, &D_us_80181AC0,
};

void EntityCoffin(Entity* self) {
    Primitive* prim;
    s32 i;
    s32 primIndex;
    u16 priority;
    u8* var_a1;
    SVECTOR** var_s3;

    VECTOR* spVector;
    VECTOR* spVector2;
    MATRIX* spTransMatrix;
    SVECTOR* spRotVector;
    MATRIX* spDummyMatrix; // used only for dead store

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitInteractable);
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 8);
        if (primIndex == -1) {
            self->ext.prim = NULL;
            return;
        }
        self->flags |= FLAG_HAS_PRIMS;
        self->primIndex = primIndex;
        prim = &g_PrimBuf[primIndex];
        self->ext.prim = prim;

        var_a1 = D_us_801819BC;
        for (i = 0; i < 7; i++, var_a1 += 4) {
            prim->tpage = 0x15;
            prim->clut = 0x200;
            prim->u0 = prim->u2 = var_a1[0];
            prim->v0 = prim->v1 = var_a1[1];
            prim->u1 = prim->u3 = var_a1[2];
            prim->v2 = prim->v3 = var_a1[3];
            prim->priority = 0x80;
            prim->drawMode = DRAW_HIDE;
            prim = prim->next;
        }
        while (prim != NULL) {
            prim->tpage = 0x15;
            prim->clut = 0x200;
            prim->priority = 0x80;
            prim->drawMode = DRAW_HIDE;
            prim = prim->next;
        }
    case 1:
        self->ext.bossCoffin.unk82 = 0x300;
        if (D_us_801806B0 & 1) {
            g_api.PlaySfx(SFX_DOOR_OPEN);
            self->step++;
        }
        break;

    case 2:
        self->ext.bossCoffin.unk82 -= 0x20;
        if (self->ext.bossCoffin.unk82 < 0) {
            self->ext.bossCoffin.unk8C = 1;
            self->ext.bossCoffin.unk82 = 0;
            self->ext.bossCoffin.timer = 0xC0;
            self->step++;
        }
        break;

    case 3:
        if (self->ext.bossCoffin.unk84 < 0x80) {
            self->ext.bossCoffin.unk84++;
        }
        self->rotate += self->ext.bossCoffin.unk84;
        self->rotate &= 0xFFF;
        if (self->rotate > ROT(343.125)) {
            g_api.PlaySfx(SFX_SAVE_COFFIN_SWISH);
        }
        if (!--self->ext.bossCoffin.timer) {
            self->step++;
        }
        break;

    case 4:
        self->rotate += self->ext.bossCoffin.unk84;
        if (self->rotate > ROT(360)) {
            self->ext.bossCoffin.unk8C = 0;
            self->rotate = ROT(0);
            g_api.PlaySfx(SFX_DOOR_OPEN);
            self->step++;
        }
        break;

    case 5:
        self->ext.bossCoffin.unk82 += 16;
        if (self->ext.bossCoffin.unk82 > 0x300) {
            self->zPriority -= 16;
            self->step++;
        }
        break;
    case 0xFF:
#include "../../st/pad2_anim_debug.h"
        break;
    }

    if (self->ext.prim != NULL) {
        spTransMatrix = (MATRIX*)SPAD(4);
        spRotVector = (SVECTOR*)SPAD(2);
        spVector = (VECTOR*)SPAD(10);

        SetGeomScreen(0x200);
        SetGeomOffset(self->posX.i.hi, self->posY.i.hi);
        spRotVector->vx = 0;
        spRotVector->vy = self->rotate;
        spRotVector->vz = 0;
        RotMatrix(spRotVector, spTransMatrix);
        SetRotMatrix(spTransMatrix);
        spVector->vx = 0;
        spVector->vy = 0;
        spVector->vz = self->ext.bossCoffin.unk8A + 0x200;
        TransMatrix(spTransMatrix, spVector);
        SetTransMatrix(spTransMatrix);

        var_s3 = D_us_80181AC8;
        if (self->ext.bossCoffin.unk82) {
            var_s3 = D_us_80181B38;
        }
        prim = self->ext.prim;
        spDummyMatrix = (MATRIX*)SPAD(0);
        spVector2 = (VECTOR*)SPAD(1);

        for (i = 0; i < 7; i++) {
            if (self->ext.bossCoffin.unk82) {
                if (i < 2) {
                    spRotVector->vy = self->rotate;
                    if (i == 0) {
                        spRotVector->vy += self->ext.bossCoffin.unk82;
                    } else {
                        spRotVector->vy -= self->ext.bossCoffin.unk82;
                    }
                    RotMatrix(spRotVector, spTransMatrix);
                    gte_SetRotMatrix(spTransMatrix);
                } else {
                    spRotVector->vy = self->rotate;
                    RotMatrix(spRotVector, spTransMatrix);
                    gte_SetRotMatrix(spTransMatrix);
                }
                if (i == 0) {
                    gte_ldtx(-21);
                } else if (i == 1) {
                    gte_ldtx(21);
                } else {
                    gte_ldtx(0);
                }
            }
            gte_ldv3(var_s3[0], var_s3[1], var_s3[2]);
            gte_rtpt();
            gte_stsxy3_gt3(prim);
            gte_ldv0(var_s3[3]);
            gte_rtps();
            gte_stsxy((long*)&prim->x3);
            gte_avsz4();
            gte_stotz(spVector2);
            prim->priority =
                self->zPriority +
                (((self->ext.bossCoffin.unk8A + 0x200) / 4) - spVector2->vx);
            prim->drawMode = DRAW_UNK02;
            var_s3 += 4;
            prim = prim->next;
        }
    }
}
