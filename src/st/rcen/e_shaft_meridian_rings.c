// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rcen.h"
#include <scratchpad.h>

#ifdef VERSION_PSP
extern s32 E_ID(SHAFT_CRYSTAL_BALL);
#endif
extern EInit g_EInitInteractable;
extern s32 g_RcenShaftFlags;

typedef struct {
    /* 0x0 */ u8 u0;
    /* 0x1 */ u8 v0;
    /* 0x2 */ u8 u1;
    /* 0x3 */ u8 v1;
    /* 0x4 */ s16 uCenter;
    /* 0x6 */ s16 vCenter;
    /* 0x8 */ s16 halfSize;
    /* 0xA */ s16 priorityOffset;
} RingTexture;

static RingTexture ring_textures[3] = {
    {
        .u0 = 0x90,
        .v0 = 0x10,
        .u1 = 0xEF,
        .v1 = 0x6F,
        .uCenter = 192,
        .vCenter = 64,
        .halfSize = 48,
        .priorityOffset = 2,
    },
    {
        .u0 = 0x08,
        .v0 = 0x08,
        .u1 = 0x77,
        .v1 = 0x77,
        .uCenter = 64,
        .vCenter = 64,
        .halfSize = 56,
        .priorityOffset = 4,
    },
    {
        .u0 = 0,
        .v0 = 0x80,
        .u1 = 0x7F,
        .v1 = 0xFF,
        .uCenter = 64,
        .vCenter = 192,
        .halfSize = 64,
        .priorityOffset = 6,
    },
};
static SVECTOR ring_vertices[3][4] = {
    {
        {.vx = -48, .vy = -48, .vz = 0},
        {.vx = 48, .vy = -48, .vz = 0},
        {.vx = -48, .vy = 48, .vz = 0},
        {.vx = 48, .vy = 48, .vz = 0},
    },
    {
        {.vx = -56, .vy = -56, .vz = 0},
        {.vx = 56, .vy = -56, .vz = 0},
        {.vx = -56, .vy = 56, .vz = 0},
        {.vx = 56, .vy = 56, .vz = 0},
    },
    {
        {.vx = -64, .vy = -64, .vz = 0},
        {.vx = 64, .vy = -64, .vz = 0},
        {.vx = -64, .vy = 64, .vz = 0},
        {.vx = 64, .vy = 64, .vz = 0},
    },
};

static SVECTOR* ring_quads[3][4] = {
    {
        &ring_vertices[0][0],
        &ring_vertices[0][1],
        &ring_vertices[0][2],
        &ring_vertices[0][3],
    },
    {
        &ring_vertices[1][0],
        &ring_vertices[1][1],
        &ring_vertices[1][2],
        &ring_vertices[1][3],
    },
    {
        &ring_vertices[2][0],
        &ring_vertices[2][1],
        &ring_vertices[2][2],
        &ring_vertices[2][3],
    },
};
static SVECTOR ring_rotation_speeds[3] = {
    {.vx = 16, .vy = -8, .vz = 8},
    {.vx = -4, .vy = -24, .vz = 32},
    {.vx = -6, .vy = 4, .vz = 16},
};

void EntityShaftMeridianRings(Entity* self) {
    s32 primIndex;
    s32 splitX;
    s32 splitY;
    s32 edgeDistance;
    s32 i;
    VECTOR* translation;
    MATRIX* matrix;
    s32 unusedScratch0;
    Entity* crystalBall;
    SVECTOR** quad;
    long* otz;
    s16 angle;
    SVECTOR* rotation;
    SVECTOR* splitStart;
    SVECTOR* splitEnd;
    RingTexture* tex;
    Primitive* prim;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitInteractable);
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 0x30);
        if (primIndex == -1) {
            self->step = 0;
            return;
        }

        self->flags |= FLAG_HAS_PRIMS;
        self->primIndex = primIndex;
        prim = &g_PrimBuf[primIndex];
        self->ext.shaftMeridianRings.prim = prim;
        while (prim != NULL) {
            prim->tpage = 0x15;
            prim->clut = 0x201;
            prim->priority = self->zPriority;
            prim->drawMode = DRAW_HIDE;
            prim = prim->next;
        }
        // fallthrough
    case 1:
        rotation = self->ext.shaftMeridianRings.rotations;
        splitEnd = ring_rotation_speeds;
        // Spin at half speed once Shaft has been defeated
        if (g_RcenShaftFlags & 4) {
            for (i = 0; i < LEN(ring_rotation_speeds); i++, rotation++,
                splitEnd++) {
                rotation->vx += splitEnd->vx / 2;
                rotation->vy += splitEnd->vy / 2;
                rotation->vz += splitEnd->vz / 2;
            }
        } else {
            for (i = 0; i < LEN(ring_rotation_speeds); i++, rotation++,
                splitEnd++) {
                rotation->vx += splitEnd->vx;
                rotation->vy += splitEnd->vy;
                rotation->vz += splitEnd->vz;
            }
        }
        break;
    }

    crystalBall = self - 1;
    self->posX.i.hi = crystalBall->posX.i.hi;
    self->posY.i.hi = crystalBall->posY.i.hi;
    if (crystalBall->entityId != E_ID(SHAFT_CRYSTAL_BALL)) {
        DestroyEntity(self);
        return;
    }

    matrix = (MATRIX*)SP(0x10);
    rotation = self->ext.shaftMeridianRings.rotations;
    translation = (VECTOR*)SP(0x28);
    otz = (long*)SP(0x4);
    unusedScratch0 = SP(0);
    SetGeomScreen(0x200);
    SetGeomOffset(self->posX.i.hi, self->posY.i.hi);
    translation->vx = 0;
    translation->vy = 0;
    translation->vz = 0x200;
    TransMatrix(matrix, translation);
    SetTransMatrix(matrix);
    quad = *ring_quads;
    splitEnd = (SVECTOR*)SP(0x38);
    splitStart = (SVECTOR*)SP(0x30);
    prim = self->ext.shaftMeridianRings.prim;
    tex = ring_textures;

    // Each ring is split in half through its center so the near half can be
    // drawn in front of the crystal ball and the far half behind it
    for (i = 0; i < LEN(ring_textures); i++, rotation++, quad += 4, tex++) {
        RotMatrix(rotation, matrix);
        gte_SetRotMatrix(matrix);
        angle = rotation->vz & 0xFFF;
        if (angle < ROT(45) || (angle >= ROT(135) && angle < ROT(225)) ||
            angle >= ROT(315)) {
            edgeDistance = tex->halfSize - 1;
            splitX = edgeDistance;
            splitY = (edgeDistance * rsin(angle)) / rcos(angle);

            splitEnd->vx = splitX;
            splitEnd->vy = -splitY;
            splitEnd->vz = 0;

            splitStart->vx = -splitX;
            splitStart->vy = splitY;
            splitStart->vz = 0;

            gte_ldv3(quad[0], quad[1], splitStart);
            gte_rtpt();
            gte_stsxy3_gt3(prim);
            gte_ldv0(splitEnd);
            gte_rtps();
            gte_stsxy((long*)&prim->x3);
            gte_avsz4();
            gte_stotz(otz);
            if (0x80 - *otz > 0) {
                prim->priority = self->zPriority + tex->priorityOffset;
            } else {
                prim->priority = self->zPriority - tex->priorityOffset;
            }

            prim->u0 = prim->u2 = tex->u0;
            prim->u1 = prim->u3 = tex->u1;
            prim->v0 = prim->v1 = tex->v0;
            prim->v2 = tex->vCenter + splitStart->vy;
            prim->v3 = tex->vCenter + splitEnd->vy;
            prim->drawMode = DRAW_UNK02;
            prim = prim->next;
            gte_ldv3(splitStart, splitEnd, quad[2]);
            gte_rtpt();
            gte_stsxy3_gt3(prim);
            gte_ldv0(quad[3]);
            gte_rtps();
            gte_stsxy((long*)&prim->x3);
            gte_avsz4();
            gte_stotz(otz);

            if (0x80 - *otz > 0) {
                prim->priority = self->zPriority + tex->priorityOffset;
            } else {
                prim->priority = self->zPriority - tex->priorityOffset;
            }

            prim->u0 = prim->u2 = tex->u0;
            prim->u1 = prim->u3 = tex->u1;
            prim->v0 = (tex->vCenter + splitStart->vy);
            prim->v1 = (tex->vCenter + splitEnd->vy);
            prim->v2 = prim->v3 = tex->v1;
            prim->drawMode = DRAW_UNK02;
            prim = prim->next;
        } else {
            edgeDistance = tex->halfSize - 1;
            angle = ROT(90) - angle;
            splitX = (edgeDistance * rsin(angle)) / rcos(angle);
            splitY = edgeDistance;

            splitEnd->vx = splitX;
            splitEnd->vy = -splitY;
            splitEnd->vz = 0;

            splitStart->vx = -splitX;
            splitStart->vy = splitY;
            splitStart->vz = 0;

            gte_ldv3(quad[0], splitEnd, quad[2]);
            gte_rtpt();
            gte_stsxy3_gt3(prim);
            gte_ldv0(splitStart);
            gte_rtps();
            gte_stsxy((long*)&prim->x3);
            gte_avsz4();
            gte_stotz(otz);
            if (0x80 - *otz > 0) {
                prim->priority = self->zPriority + tex->priorityOffset;
            } else {
                prim->priority = self->zPriority - tex->priorityOffset;
            }

            prim->u0 = prim->u2 = tex->u0;
            prim->u1 = (tex->uCenter + splitEnd->vx);
            prim->u3 = (tex->uCenter + splitStart->vx);
            prim->v0 = prim->v1 = tex->v0;
            prim->v2 = prim->v3 = tex->v1;
            prim->drawMode = DRAW_UNK02;
            prim = prim->next;
            gte_ldv3(splitEnd, quad[1], splitStart);
            gte_rtpt();
            gte_stsxy3_gt3(prim);
            gte_ldv0(quad[3]);
            gte_rtps();
            gte_stsxy((long*)&prim->x3);
            gte_avsz4();
            gte_stotz(otz);
            if (0x80 - *otz > 0) {
                prim->priority = self->zPriority + tex->priorityOffset;
            } else {
                prim->priority = self->zPriority - tex->priorityOffset;
            }
            prim->u0 = (tex->uCenter + splitEnd->vx);
            prim->u2 = (tex->uCenter + splitStart->vx);
            prim->u1 = prim->u3 = tex->u1;
            prim->v0 = prim->v1 = tex->v0;
            prim->v2 = prim->v3 = tex->v1;
            prim->drawMode = DRAW_UNK02;
            prim = prim->next;
        }
    }
}
