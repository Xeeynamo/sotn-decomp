#include "np3.h"

void EntityZombie(Entity_*self) {
    Entity_*newEntity;
    s32 temp_a0;

    if ((self->flags & 0x100) && (self->step < 4)) {
        func_801C2598(NA_SE_EN_ZOMBIE_EXPLODE);
        self->unk3C = 0;
        // Spawn Zombie explosion
        newEntity = AllocEntity(D_8007D858, &D_8007D858[32]);
        if (newEntity != NULL) {
            CreateEntityFromEntity(0x4D, self, newEntity);
            newEntity->zPriority = self->zPriority + 1;
            newEntity->subId = 3;
            newEntity->posY.i.hi += 12;
        }
        DestroyEntity(self);
        return;
    }

    switch (self->step) {
    case 0:
        InitializeEntity(D_80180B08);
        self->hitboxWidth = 8;
        self->unk12 = 0x10;
        self->hitboxHeight = 0;
        self->zPriority += 4;
        if (g_blinkTimer & 1) {
            self->palette++;
        }
        if (Random() & 1) {
            self->palette++;
        }
        self->animCurFrame = 0;
        break;

    case 1:
        if (func_801BC8E4(D_801825BC) & 1) {
            self->facing = (GetPlayerSide() & 1) ^ 1;
            self->step++;
        }
        break;

    case 2:
        if (AnimateEntity(D_80182594, self) == 0) {
            func_801BD114(3);
        }
        if (self->animFrameDuration == 0) {
            self->unk12 -= 2;
            self->hitboxHeight += 2;
        }
        break;

    case 3:
        AnimateEntity(D_8018258C, self);
        temp_a0 = func_801BCB5C(&D_801825CC);
        if (self->facing != 0) {
            self->accelerationX = 0x8000;
        } else {
            self->accelerationX = -0x8000;
        }

        if (temp_a0 & 0xC0) {
            self->unk3C = 0;
            func_801BD114(4);
        }
        break;

    case 4:
        if (AnimateEntity(D_801825A8, self) == 0) {
            DestroyEntity(self);
        }
        break;
    }
}

void EntityUnkId4D(Entity_*self) {
    s32 distCameraEntity;
    Entity_*newEntity;
    s32 rnd;

    if (self->step == 0) {
        InitializeEntity(D_80180A60);
        self->ext.generic.unk80.modeS16.unk0 = 1;
        self->flags &= 0x2000;
    }

    if (D_8003BE23 != 0) {
        self->posX.i.hi = 128;
        if (--self->ext.generic.unk80.modeS16.unk0 == 0) {
            newEntity = AllocEntity(D_8007A958, &D_8007A958[8]);
            if (newEntity != NULL) {
                CreateEntityFromEntity(0x42, self, newEntity);
                rnd = (Random() & 0x3F) + 96;

                if (self->ext.generic.unk88.unk != 0) {
                    newEntity->posX.i.hi += rnd;
                } else {
                    newEntity->posX.i.hi -= rnd;
                }
                newEntity->posY.i.hi -= 48;
                self->ext.generic.unk88.unk ^= 1;

                distCameraEntity = g_Camera.posX.i.hi + newEntity->posX.i.hi;
                if ((distCameraEntity < (g_CurrentRoom.x + 128)) ||
                    ((g_CurrentRoom.width - 128) < distCameraEntity)) {
                    DestroyEntity(newEntity);
                }
            }
            self->ext.generic.unk80.modeS16.unk0 = (Random() & 0x3F) + 32;
        }
    }
}

void EntityBloodSplatter(Entity_*self) {
    Primitive *prim, *prim2, *prim3;
    s16 firstPrimIndex;

    switch (self->step) {
    case 0:
        InitializeEntity(D_80180A54);
        break;

    case 1:
        firstPrimIndex = g_api.AllocPrimitives(4, 8);
        if (firstPrimIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->firstPolygonIndex = firstPrimIndex;
        prim = &g_PrimBuf[firstPrimIndex];
        *(s32*)&self->ext.generic.unk7C = prim;
        self->flags |= FLAG_FREE_POLYGONS;
        self->step++;
        break;

    case 2:
        prim = func_801D24A0(*(s32*)&self->ext.generic.unk7C, 2);
        if (prim != NULL) {
            self->ext.generic.unk8C.primPtr = prim;
            func_801D2684(prim);
            prim->v0 = 0x30;
            prim->tpage = 0x1A;
            prim->v2 = 0x30;
            prim->clut = 0x1B7;
            prim->u0 = 0x50;
            prim->u1 = 0x50;
            prim->u2 = 0x40;
            prim->u3 = 0x40;
            prim->v1 = 0x40;
            prim->v3 = 0x40;
            prim->next->b3 = 0x60;
            prim->next->x1 = self->posX.i.hi;
            prim->next->y0 = self->posY.i.hi;
            *(u16*)&prim->next->r2 = 0x10;
            *(u16*)&prim->next->b2 = 0x10;
            *(s32*)&prim->next->r1 = -0x6000;

            if (self->facing != 0) {
                *(s32*)&prim->next->u0 = 0xA000;
                prim->next->tpage = 0x200;
                prim->next->x1 = prim->next->x1 + 4;
            } else {
                *(s32*)&prim->next->u0 = 0xFFFF6000;
                *(s16*)&prim->next->tpage = -0x200;
                prim->next->x1 = prim->next->x1 - 4;
            }
            prim->priority = self->zPriority + 2;
            prim->blendMode = 6;
        }

        prim = func_801D24A0(*(s32*)&self->ext.generic.unk7C, 2);
        if (prim != NULL) {
            *(s32*)&self->ext.generic.unk90 = prim;
            func_801D2684(prim);
            prim->v1 = 0x40;
            prim->tpage = 0x1A;
            prim->v3 = 0x40U;
            prim->clut = 0x1B7;
            prim->u0 = 0x20;
            prim->u1 = 0x20;
            prim->u2 = 0;
            prim->u3 = 0;
            prim->v0 = 0x20;
            prim->v2 = 0x20;
            prim->next->x1 = self->posX.i.hi;
            prim->next->y0 = self->posY.i.hi;
            *(u16*)&prim->next->r2 = 8;
            *(u16*)&prim->next->b2 = 0x10;
            prim->next->b3 = 0x80;
            *(s32*)&prim->next->r1 = -0x8000;
            if (self->facing != 0) {
                *(s32*)&prim->next->u0 = 0xC000;
                *(s16*)&prim->next->tpage = 0x200;
            } else {
                *(s32*)&prim->next->u0 = 0xFFFF4000;
                *(s16*)&prim->next->tpage = -0x200;
            }
            prim->priority = self->zPriority + 2;
            prim->blendMode = 6;
        }
        self->step++;
        break;

    case 3:
        prim = self->ext.generic.unk8C.entityPtr;
        func_801D1F38(prim);

        if (g_blinkTimer & 1) {
            prim3 = prim->next;
            *(u16*)&prim3->r2 = *(u16*)&prim3->r2 + 1;
            prim3 = prim->next;
            *(u16*)&prim3->b2 = *(u16*)&prim3->b2 + 1;
            prim->clut = 0x1B7;
        } else {
            prim->clut = 0x16D;
        }

        prim2 = prim->next;
        *(s32*)&prim2->r1 += 0xC00;

        if (self->facing != 0) {
            prim->next->tpage += 0x18;
        } else {
            prim->next->tpage = prim->next->tpage - 0x18;
        }

        prim3 = prim->next;
        prim3->b3 += 254;
        if (func_801D2320(&D_8018268C, prim) == 0) {
            func_801D26D8(prim);
        }

        prim = *(s32*)&self->ext.generic.unk90;
        func_801D1F38(prim);
        prim3 = prim->next;
        *(u16*)&prim3->r2 = *(u16*)&prim3->r2 + 2;
        prim3 = prim->next;
        *(u16*)&prim3->b2 = *(u16*)&prim3->b2 + 2;
        if (prim->p1 >= 4) {
            *(u16*)&prim->next->b2 = 16;
        }

        prim->next->b3 += 253;
        prim3 = prim->next;
        if (prim3->b3 > 240) {
            prim3->b3 = 0;
        }

        if (func_801D2320(&D_801826A4, prim) == 0) {
            func_801D26D8(prim);
        }

        if (self->ext.generic.unk80.modeS16.unk0++ > 128) {
            DestroyEntity(self);
        }
        break;
    }
}

INCLUDE_ASM("asm/us/st/np3/nonmatchings/49BC8", func_801CA498);
