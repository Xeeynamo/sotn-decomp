// SPDX-License-Identifier: AGPL-3.0-or-later
#include "no3.h"
#include "sfx.h"

INCLUDE_ASM("st/no3/nonmatchings/4ED60", EntityUnkId2F);

// beams that go up when strong warg dies
void EntityStrongWargDeathBeams(Entity* self) {
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

        InitializeEntity(g_eInitGeneric2);
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
        if ((self->ext.strongWargDeathBeams.unk7C == 0) &&
            (self->ext.strongWargDeathBeams.unk7E < 0x14)) {
            prim = &g_PrimBuf[self->primIndex];

            while (prim != NULL) {
                if (prim->drawMode == DRAW_HIDE) {
                    if (self->ext.strongWargDeathBeams.unk7E & 1) {
                        PlaySfxPositional(SFX_EXPLODE_B);
                    }

                    if (self->facingLeft != 0) {
                        baseX =
                            self->posX.i.hi -
                            D_80183080[self->ext.strongWargDeathBeams.unk7E &
                                       0xF];
                        prim->x0 = prim->x2 = baseX + 0x10;
                        prim->x1 = prim->x3 = baseX - 0x10;
                    } else {
                        baseX =
                            self->posX.i.hi +
                            D_80183080[self->ext.strongWargDeathBeams.unk7E &
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
                        D_801830A0[self->ext.strongWargDeathBeams.unk7E & 0xF];
                    prim->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS |
                                     DRAW_UNK02 | DRAW_TRANSP;
                    prim->p1 = (Random() & 3) + 0x10;
                    prim->p2 = 0;
                    break;
                }

                prim = prim->next;
            }

            self->ext.strongWargDeathBeams.unk7C = 4;
            self->ext.strongWargDeathBeams.unk7E++;
        } else {
            self->ext.strongWargDeathBeams.unk7C--;
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

        if (hiddenPrimCount == 4 &&
            self->ext.strongWargDeathBeams.unk7E > 0x13) {
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
            newEnt->pfnUpdate = EntityUnkId14;
            newEnt->params = params;
            newEnt->posX.i.hi = x + i * xOfst;
            newEnt->posY.i.hi = y;
            newEnt->ext.generic.unk94 = D_801832E8[i];
            newEnt->rotY = newEnt->rotX = D_801832D8[D_801832E8[i] + arg5];
            newEnt->drawFlags = FLAG_DRAW_ROTY | FLAG_DRAW_ROTX;
            newEnt->zPriority = entity->zPriority + 1;
        }
    }
}

void func_801CF58C(Entity* self) {
    self->velocityX = 0;
    self->ext.generic.unk84.S16.unk2 = 0x100;
    SetStep(6);
    g_api.PlaySfx(SE_WARG_GROWL);
    self->ext.generic.unk80.modeS16.unk0 = 0x20;
}

void func_801CF5E0(Entity* self) {
    s16 temp_v0;

    if (self->facingLeft == GetSideToPlayer()) {
        SetStep(5);
        return;
    }

    if (self->ext.generic.unk84.S16.unk2 == 0) {
        func_801CF58C(self);
        return;
    }

    temp_v0 = self->ext.generic.unk84.S16.unk0 - self->posX.i.hi -
              g_Tilemap.scrollX.i.hi;

    if (temp_v0 > 16) {
        SetStep(3);
        if (self->facingLeft != 0) {
            self->ext.generic.unk7C.S8.unk0 = 0;
        } else {
            self->ext.generic.unk7C.S8.unk0 = 1;
        }
    } else if (temp_v0 < -16) {
        SetStep(3);
        if (self->facingLeft != 0) {
            self->ext.generic.unk7C.S8.unk0 = 1;
        } else {
            self->ext.generic.unk7C.S8.unk0 = 0;
        }
    } else {
        SetStep(7);
    }

    self->ext.generic.unk80.modeS16.unk0 = 0;
    self->ext.generic.unk80.modeS16.unk2 = 32;
}

// duplicate of func_801CC90C in this file
void func_801CF6D8(Entity* arg0) {
    s16 temp_v0_2;
    s16 temp_v1;
    s16 temp_v0;

    temp_v0 = GetDistanceToPlayerX();
    temp_v1 = arg0->ext.generic.unk84.S16.unk2;
    if (temp_v1 != 0) {

        if ((u32)(temp_v0) < 0x60) {
            temp_v0_2 = temp_v1 - 2;
            arg0->ext.generic.unk84.S16.unk2 = temp_v0_2;
            if (temp_v0_2 < 0) {
                arg0->ext.generic.unk84.S16.unk2 = 0;
            }
        } else {
            arg0->ext.generic.unk84.S16.unk2 = (temp_v1 - 1);
        }
    }
}

INCLUDE_ASM("st/no3/nonmatchings/4ED60", EntityWarg);

// func_psp_09254348
void EntityUnkId4B(Entity* self) {
    u16 lastAnimFrame;
    Entity* previous;
    s16* hitboxPtr;

    previous = self - 1;

    if (!self->step) {
        InitializeEntity(&D_80180B9C);
        self->animCurFrame = 0;
        self->hitPoints = 0x7FFF;
    }

    self->posX.i.hi = previous->posX.i.hi;
    self->posY.i.hi = previous->posY.i.hi;
    self->facingLeft = previous->facingLeft;
    lastAnimFrame = previous->animCurFrame;

    if (lastAnimFrame) {

        if (self->params) {

            if (lastAnimFrame >= 109) {
                lastAnimFrame -= 108;
            } else if (lastAnimFrame >= 82) {
                lastAnimFrame -= 62;
            } else if (lastAnimFrame >= 76) {
                lastAnimFrame -= 59;
            } else if (lastAnimFrame >= 63) {
                lastAnimFrame -= 56;
            } else if (lastAnimFrame >= 51) {
                lastAnimFrame -= 50;
            } else {
                lastAnimFrame -= 49;
            }
            hitboxPtr = &D_801836BC[lastAnimFrame * 8];

        } else {
            if (previous->params) {
                if (lastAnimFrame >= 86 || lastAnimFrame >= 57) {
                    lastAnimFrame -= 57;
                } else {
                    lastAnimFrame = 13;
                }
            } else if (lastAnimFrame >= 96) {
                lastAnimFrame -= 48;
            } else {
                lastAnimFrame -= 1;
            }
            hitboxPtr = &D_801832EC[lastAnimFrame * 8];
        }

        hitboxPtr = hitboxPtr + 4;
        self->hitboxOffX = *hitboxPtr++;
        self->hitboxOffY = *hitboxPtr++;
        self->hitboxWidth = *hitboxPtr++;
        self->hitboxHeight = *hitboxPtr;
    }
}

// A single "puff" of the warg explosion animation, transparent
void EntityWargExplosionPuffTransparent(Entity* entity) {
    u32 temp_v0;

    if (entity->step == 0) {
        InitializeEntity(g_InitializeEntityData0);
        entity->animSet = ANIMSET_DRA(14);
        entity->unk5A = 0x79;
        entity->palette = 0xD0;
        entity->drawMode = DRAW_TPAGE2 | DRAW_TPAGE;
        entity->drawFlags = FLAG_DRAW_UNK8;
        entity->animFrameIdx = 0;
        entity->animFrameDuration = 0;
        entity->unk6C = 0x60;
        temp_v0 = entity->params & 0xFF00;
        if (temp_v0 != 0) {
            entity->zPriority = temp_v0 >> 8;
        }
        entity->velocityY += 0xFFFF0000;
        return;
    }
    entity->posY.val += entity->velocityY;
    if (AnimateEntity(D_8018383C, entity) == 0) {
        DestroyEntity(entity);
    }
}

#include "../popup.h"
