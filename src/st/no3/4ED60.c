// SPDX-License-Identifier: AGPL-3.0-or-later
#include "no3.h"
#include "sfx.h"

// func_psp_0924D030
void EntityUnkId2F(Entity* self) {

    switch (self->step) {
    case 0:
        InitializeEntity(D_80180B3C);
        self->attack /= 2;
        self->ext.timer.t = 8;
        self->hitboxWidth = 4;
        self->hitboxHeight = 0;

        break;
    case 1:
        self->posY.i.hi -= 4;
        self->hitboxHeight += 2;
        if (self->facingLeft) {
            self->posX.i.hi += 6;
        } else {
            self->posX.i.hi -= 6;
        }
        self->hitboxWidth += 2;
        if (!--self->ext.timer.t) {
            self->ext.timer.t = 20;
            self->step++;
        }
        break;
    case 2:
        if (self->hitboxHeight < 192) {
            self->posY.i.hi -= 4;
            self->hitboxHeight += 2;
        }
        if (self->facingLeft) {
            self->posX.i.hi += 1;
        } else {
            self->posX.i.hi -= 1;
        }

        if (!--self->ext.timer.t) {
            self->ext.timer.t = 16;
            self->step++;
        }
        break;
    case 3:
        self->posY.i.hi += 4;
        self->hitboxHeight -= 2;
        if (self->facingLeft) {
            self->posX.i.hi += 1;
        } else {
            self->posX.i.hi -= 1;
        }
        self->hitboxWidth -= 1;
        if (!--self->ext.timer.t) {
            self->ext.timer.t = 32;
            self->hitboxState = 0;
            self->step++;
        }
        break;
    case 4:
        if (!--self->ext.timer.t) {
            DestroyEntity(self);
        }
        break;
    }
}

// beams that go up when strong warg dies
void EntityFireWargDeathBeams(Entity* self) {
    Primitive* prim;
    s16 baseX;
    u16 hiddenPrimCount;
    u16 palette;
    s32 primIndex;
    s32 temp_s1;
    u16 temp_s1_u16;

    switch (self->step) {
    case 0:
        palette = self->palette + 4;
        temp_s1 = self->unk5A + 3;
        temp_s1_u16 = (u16)temp_s1;

        InitializeEntity(g_EInitCommon);
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 4);

        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }

        self->primIndex = primIndex;
        self->flags |= FLAG_HAS_PRIMS;
        prim = &g_PrimBuf[primIndex];

        while (prim != NULL) {
            prim->tpage = temp_s1_u16 / 4;
            prim->clut = palette;
            prim->u0 = prim->u1 = ((temp_s1 & 1) << 7) + 0x21;
            prim->v1 = prim->v3 = ((temp_s1 & 2) << 6) + 0x59;
            prim->v0 = prim->v2 = ((temp_s1 & 2) << 6) + 0x7F;
            prim->u3 = prim->u2 = prim->u0 + 0x2D;
            prim->drawMode = DRAW_HIDE;
            prim = prim->next;
        }
        break;
    case 1:
        if ((self->ext.fireWargDeathBeams.unk7C == 0) &&
            (self->ext.fireWargDeathBeams.unk7E < 0x14)) {
            prim = &g_PrimBuf[self->primIndex];

            while (prim != NULL) {
                if (prim->drawMode == DRAW_HIDE) {
                    if (self->ext.fireWargDeathBeams.unk7E & 1) {
                        PlaySfxPositional(SFX_EXPLODE_B);
                    }

                    if (self->facingLeft != 0) {
                        baseX = self->posX.i.hi -
                                D_80183080[self->ext.fireWargDeathBeams.unk7E &
                                           0xF];
                        prim->x0 = prim->x2 = baseX + 0x10;
                        prim->x1 = prim->x3 = baseX - 0x10;
                    } else {
                        baseX = self->posX.i.hi +
                                D_80183080[self->ext.fireWargDeathBeams.unk7E &
                                           0xF];
                        prim->x0 = prim->x2 = baseX - 0x10;
                        prim->x1 = prim->x3 = baseX + 0x10;
                    }

                    prim->y0 = prim->y1 = prim->y2 = prim->y3 =
                        self->posY.i.hi + 0x28;
                    prim->b1 = prim->b3 = prim->g1 = prim->g3 = prim->r1 =
                        prim->r3 = prim->b0 = prim->b2 = prim->g0 = prim->g2 =
                            prim->r0 = prim->r2 = 0x40;

                    prim->priority =
                        self->zPriority +
                        D_801830A0[self->ext.fireWargDeathBeams.unk7E & 0xF];
                    prim->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS |
                                     DRAW_UNK02 | DRAW_TRANSP;
                    prim->p1 = (Random() & 3) + 0x10;
                    prim->p2 = 0;
                    break;
                }

                prim = prim->next;
            }

            self->ext.fireWargDeathBeams.unk7C = 4;
            self->ext.fireWargDeathBeams.unk7E++;
        } else {
            self->ext.fireWargDeathBeams.unk7C--;
        }

        prim = &g_PrimBuf[self->primIndex];
        hiddenPrimCount = 0;

        while (prim != NULL) {
            if (prim->drawMode != DRAW_HIDE) {
                prim->p2++;
                prim->x0 = prim->x2 = prim->x2 + 1;
                prim->x1 = prim->x3 = prim->x3 - 1;

                if (prim->p2 > 8) {
                    prim->r0 = prim->r1 = prim->r1 - 0x10;
                    prim->g0 = prim->g1 = prim->g1 - 0x10;
                    prim->b0 = prim->b1 = prim->b1 - 0x10;

                    if (prim->r2) {
                        prim->r2 = prim->r3 = prim->r3 - 0x14;
                        prim->g2 = prim->g3 = prim->g3 - 0x14;
                        prim->b2 = prim->b3 = prim->b3 - 0x14;
                    }
                } else {
                    prim->r0 = prim->r2 = prim->r1 = prim->r3 = prim->r3 + 0x10;
                    prim->g0 = prim->g2 = prim->g1 = prim->g3 = prim->g3 + 0x10;
                    prim->b0 = prim->b2 = prim->b1 = prim->b3 = prim->b3 + 0x10;
                }

                prim->y0 = prim->y1 = prim->y1 - prim->p1;

                if (prim->p2 > 0x10) {
                    prim->drawMode = DRAW_HIDE;
                }
            } else {
                hiddenPrimCount++;
            }
            prim = prim->next;
        }

        if (hiddenPrimCount == 4 && self->ext.fireWargDeathBeams.unk7E > 0x13) {
            DestroyEntity(self);
            return;
        }
        break;
    }
}

void func_801CF438(Entity* entity, u8 count, u8 params, s32 xDist, s32 yDist,
                   u8 arg5, s16 xOfst) {
    s32 i;
    s16 y = entity->posY.i.hi + yDist;
    s16 x = entity->posX.i.hi + xDist;

    for (i = 0; i < count; ++i) {
        Entity* newEnt = AllocEntity(&g_Entities[160], &g_Entities[192]);
        if (newEnt != NULL) {
            newEnt->entityId = E_ID_14;
            newEnt->pfnUpdate = EntityExplosionVariants;
            newEnt->params = params;
            newEnt->posX.i.hi = x + i * xOfst;
            newEnt->posY.i.hi = y;
            newEnt->ext.destructAnim.index = D_801832E8[i];
            newEnt->rotY = newEnt->rotX = D_801832D8[D_801832E8[i] + arg5];
            newEnt->drawFlags = FLAG_DRAW_ROTY | FLAG_DRAW_ROTX;
            newEnt->zPriority = entity->zPriority + 1;
        }
    }
}
