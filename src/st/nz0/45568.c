#include "nz0.h"

void EntityBloodyZombie(Entity* self) {
    Primitive* prim;
    Primitive** prim2;
    Entity* newEntity;
    s16 firstPrimIndex;
    s16 entityFacing;
    s32 animState;

    if ((self->unk44 != 0) && (self->step & 1)) {
        func_801C29B0(0x746);
        func_801C29B0(0x748);
        func_801BD52C(6);
    }

    if ((self->flags & 0x100) && (self->step < 8)) {
        func_801C29B0(0x747);
        self->unk3C = 0;
        self->flags &= 0xDFFFFFFF;
        func_801BD52C(8);
    }

    switch (self->step) {
    case 0:
        InitializeEntity(D_80180C7C);
        self->unk10 = 1;
        self->unk12 = 4;
        func_801BD52C(2);
        break;

    case 2:
        if (func_801BCCFC(D_801822D4) & 1) {
            func_801BD52C(1);
        }
        break;

    case 1:
        if (self->step_s == 0) {
            self->unk80.modeS16.unk0 = 128;
            self->step_s++;
        }

        AnimateEntity(D_801822EC, self);
        func_801BCF74(D_801822E4);

        if (self->facing == 0) {
            self->accelerationX = -0x6000;
        } else {
            self->accelerationX = 0x6000;
        }

        if (--self->unk80.modeS16.unk0 == 0) {
            self->unk80.modeS16.unk0 = 128;
            self->facing ^= 1;
        }

        if (!(Random() & 0x3F)) {
            newEntity = AllocEntity(D_8007D858, &D_8007D858[32]);
            if (newEntity != NULL) {
                CreateEntityFromEntity(0x2C, self, newEntity);
                if (self->facing != 0) {
                    newEntity->posX.i.hi += 16;
                } else {
                    newEntity->posX.i.hi -= 16;
                }
                newEntity->posY.i.hi += 12;
            }
        }
        entityFacing = GetPlayerSide() & 1;
        if ((PLAYER.facing == entityFacing) && (GetPlayerDistanceX() < 128)) {
            self->facing = entityFacing ^ 1;
            func_801BD52C(3);
        }
        break;

    case 3:
        if (AnimateEntity(D_8018237C, self) == 0) {
            self->facing = (GetPlayerSide() & 1) ^ 1;
        }

        func_801BCF74(D_801822E4);

        if (self->facing != 0) {
            self->accelerationX = 0xC000;
        } else {
            self->accelerationX = -0xC000;
        }

        if (!(Random() & 0x3F)) {
            newEntity = AllocEntity(D_8007D858, &D_8007D858[32]);
            if (newEntity != NULL) {
                CreateEntityFromEntity(0x2C, self, newEntity);
                if (self->facing != 0) {
                    newEntity->posX.i.hi += 18;
                } else {
                    newEntity->posX.i.hi -= 18;
                }
                newEntity->posY.i.hi += 12;
            }
        }
        if (GetPlayerDistanceX() < 40) {
            func_801BD52C(4);
        }
        break;

    case 4:
        animState = AnimateEntity(D_801822FC, self);
        if ((animState & 0x80) && (self->animFrameIdx == 10)) {
            func_801C29B0(0x60B);
        }

        if (animState == 0) {
            func_801BD52C(1);
        }
        break;

    case 6:
        if (self->step_s == 0) {
            newEntity = AllocEntity(D_8007D858, &D_8007D858[32]);
            if (newEntity != NULL) {
                CreateEntityFromEntity(0x2D, self, newEntity);
                newEntity->facing = GetPlayerSide() & 1;
            }
            self->step_s++;
        }

        if (AnimateEntity(D_80182320, self) == 0) {
            func_801BD52C(1);
            self->step_s++;
        }
        break;

    case 8:
        if (self->step_s == 0) {
            firstPrimIndex = g_api.AllocPrimitives(4, 0x14);
            if (firstPrimIndex == -1) {
                DestroyEntity(self);
                return;
            }
            self->firstPolygonIndex = firstPrimIndex;
            prim = &g_PrimBuf[firstPrimIndex];
            *(s32*)&self->unk7C = prim;
            self->flags |= 0x800000;
            self->step_s++;
        }

        if (self->animFrameIdx < 13) {
            if (!(g_blinkTimer & 7)) {
                func_801C29B0(0x749);

                newEntity = AllocEntity(D_8007D858, &D_8007D858[32]);
                if (newEntity != NULL) {
                    CreateEntityFromEntity(0x2DU, self, newEntity);
                    newEntity->facing = self->unk84.U8.unk0;
                    if (self->facing != 0) {
                        newEntity->posX.i.hi -= 4;
                    } else {
                        newEntity->posX.i.hi += 4;
                    }
                    newEntity->posY.i.hi += 4;
                }
                self->unk84.S8.unk0 ^= 1;
            }
            self->unk80.modeS16.unk0 = 0;
        } else {
            if (self->unk80.modeS16.unk0 == 0) {
                func_801C29B0(0x749);
            }

            self->unk80.modeS16.unk0++;
            if (!(g_blinkTimer & 3)) {
                prim2 = func_801C9E98(*(s32*)&self->unk7C, 2);
                if (prim2 != NULL) {
                    func_801CA07C(prim2);
                    (*prim2)->r3 = self->unk84.S8.unk0;
                }
                self->unk84.S8.unk0 ^= 1;
            }
        }

        if (self->flags & 0x800000) {
            prim = *(s32*)&self->unk7C;
            while (prim != NULL) {
                if (prim->p3 & 8) {
                    func_801C53AC(prim);
                }
                prim = prim->next;
            }
        }

        if (AnimateEntity(D_80182334, self) == 0) {
            newEntity = AllocEntity(D_8007D858, &D_8007D858[32]);
            if (newEntity != NULL) {
                CreateEntityFromEntity(2, self, newEntity);
                newEntity->subId = 2;
                newEntity->posY.i.hi += 16;
                if (self->facing != 0) {
                    newEntity->posX.i.hi -= 8;
                } else {
                    newEntity->posX.i.hi += 8;
                }
            }
            self->unk80.modeS16.unk0 = 0x40;
            self->animCurFrame = 0;
            func_801C29B0(0x693);
            self->step++;
        }
        break;

    case 9:
        if (self->flags & 0x800000) {
            prim = *(s32*)&self->unk7C;
            while (prim != NULL) {
                if (prim->p3 & 8) {
                    func_801C53AC(prim);
                }
                prim = prim->next;
            }
        }

        if (--self->unk80.modeS16.unk0 == 0) {
            DestroyEntity(self);
        }
        break;
    }

    if (((u16)self->animCurFrame - 11) < 2U) {
        self->hitboxWidth = 18;
        self->hitboxHeight = 12;
        *(s16*)&self->unk10 = -12;
        self->unk12 = -12;
    } else {
        self->hitboxWidth = 4;
        self->hitboxHeight = 22;
        *(s16*)&self->unk10 = 1;
        self->unk12 = 4;
    }
}

void func_801C5D20(Entity* self) {
    Primitive* prim;
    s16 firstPrimIndex;

    switch (self->step) {
    case 0:
        InitializeEntity(D_80180BE0);
        firstPrimIndex = g_api.AllocPrimitives(2, 1);
        if (firstPrimIndex != -1) {
            prim = &g_PrimBuf[firstPrimIndex];
            self->firstPolygonIndex = firstPrimIndex;
            self->unk3C = 0;
            *(s32*)&self->unk7C = prim;
            self->flags |= 0x800000;
            while (prim != NULL) {
                prim->x0 = prim->x1 = self->posX.i.hi;
                prim->y0 = prim->y1 = self->posY.i.hi;
                prim->r0 = 255;
                prim->r1 = 32;
                prim->g0 = 0;
                prim->g1 = 0;
                prim->b0 = 48;
                prim->b1 = 16;
                prim->priority = self->zPriority + 1;
                prim->blendMode |= 0x37;
                prim = prim->next;
            }
        } else {
            DestroyEntity(self);
        }
        break;

    case 1:
        prim = *(s32*)&self->unk7C;
        if (func_801C070C(&D_801823C4, 0) != 0) {
            prim->y1 += 2;
            if (self->step_s == 0) {
                self->step_s = 1;
            }
        } else {
            self->accelerationY += 0x1800;
            self->posY.val += self->accelerationY;
            if ((prim->y0 - prim->y1) >= 9) {
                prim->y1 = prim->y0 - 8;
            }
        }
        prim->x0 = self->posX.i.hi;
        prim->x1 = self->posX.i.hi;
        prim->y0 = self->posY.i.hi;
        if (prim->y0 < prim->y1) {
            g_api.FreePrimitives(self->firstPolygonIndex);
            DestroyEntity(self);
        }
        break;
    }
}

void func_801C5F2C(Entity* arg0) {
    if ((func_801BCF74(&D_801824B8) & 0x60) == 0x60) {
        arg0->posX.val -= arg0->accelerationX;
    }

    if (!(func_801BD720(&D_801824C0, 3) & 2)) {
        if ((--arg0->unk7C.U8.unk0) == 0) {
            func_801BD52C(4);
        }
    } else {
        func_801BD52C(5);
    }
}
