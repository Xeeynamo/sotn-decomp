// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../nz0/nz0.h"

#ifndef VERSION_PSP
static s32 D_80180ED0[] = {0};
#else
extern s32 D_80180ED0[];
#endif
void EntityCannonLever(Entity* self) {
    Primitive* prim;
    Entity* player;
    s32 primIndex;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitInteractable);
        self->hitboxWidth = 4;
        self->hitboxHeight = 20;
        self->hitboxState = 2;

        primIndex = g_api.AllocPrimitives(PRIM_GT4, 1);
        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags |= FLAG_HAS_PRIMS;
        self->primIndex = primIndex;
        prim = &g_PrimBuf[primIndex];
        self->ext.prim = prim;

        prim->type = PRIM_SPRT;
        prim->tpage = 0xF;
        prim->clut = 9;
        prim->u0 = 0x68;
        prim->v0 = 0x80;
        prim->u1 = 8;
        prim->v1 = 0x28;
        prim->priority = 0x70;
        prim->drawMode = DRAW_UNK02;

        player = &PLAYER;
        if (player->posX.i.hi < 128) {
            self->hitboxState = 0;
        }
        break;

    case 1:
        if (self->hitFlags) {
            self->velocityX = FIX(-4);
            self->step++;
        }
        break;

    case 2:
        MoveEntity();
        self->velocityX -= self->velocityX / 16;
        if (abs(self->velocityX < 0x2000)) {
            self->step++;
        }
        break;

    case 3:
        D_80180ED0[0] = 1;
        break;
    }

    if (g_CastleFlags[NZ0_CANNON_WALL_SHORTCUT]) {
        self->hitboxState = 0;
    }
    prim = self->ext.prim;
    prim->x0 = self->posX.i.hi - 4;
    prim->y0 = self->posY.i.hi - 20;
}

INCLUDE_ASM("st/nz0_psp/nonmatchings/nz0_psp/e_cannon", EntityCannon);

INCLUDE_ASM("st/nz0_psp/nonmatchings/nz0_psp/e_cannon", EntityCannonShot);

INCLUDE_ASM("st/nz0_psp/nonmatchings/nz0_psp/e_cannon", EntityCannonWall);
