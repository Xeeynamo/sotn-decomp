#include "nz0.h"

void EntityBloodDrips(Entity* self) {
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
        if (self->unk2E == 0) {
            self->unk80.modeS16.unk0 = 128;
            self->unk2E++;
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
        entityFacing = func_801BCC5C() & 1;
        if ((PLAYER.facing == entityFacing) && (func_801BCBEC() < 128)) {
            self->facing = entityFacing ^ 1;
            func_801BD52C(3);
        }
        break;

    case 3:
        if (AnimateEntity(D_8018237C, self) == 0) {
            self->facing = (func_801BCC5C() & 1) ^ 1;
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
        if (func_801BCBEC() < 40) {
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
        if (self->unk2E == 0) {
            newEntity = AllocEntity(D_8007D858, &D_8007D858[32]);
            if (newEntity != NULL) {
                CreateEntityFromEntity(0x2D, self, newEntity);
                newEntity->facing = func_801BCC5C() & 1;
            }
            self->unk2E++;
        }

        if (AnimateEntity(D_80182320, self) == 0) {
            func_801BD52C(1);
            self->unk2E++;
        }
        break;

    case 8:
        if (self->unk2E == 0) {
            firstPrimIndex = g_api.AllocPrimitives(4, 0x14);
            if (firstPrimIndex == -1) {
                DestroyEntity(self);
                return;
            }
            self->firstPolygonIndex = firstPrimIndex;
            prim = &g_PrimBuf[firstPrimIndex];
            *(s32*)&self->unk7C = prim;
            self->flags |= 0x800000;
            self->unk2E++;
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

INCLUDE_ASM("asm/us/st/nz0/nonmatchings/45568", func_801C5D20);

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

// throws bones at you
// Unique
INCLUDE_ASM("asm/us/st/nz0/nonmatchings/45568", EntitySkeleton);

void func_801C6494(Entity* entity) {
    if (entity->step) {
        entity->unk88.S8.unk0--;
        if (entity->unk88.S8.unk0 & 0xFF) {
            entity->unk1E += D_80182424[entity->subId];
            FallEntity();
            MoveEntity();
            return;
        }

        entity->objectId = ENTITY_EXPLOSION;
        entity->pfnUpdate = (PfnEntityUpdate)EntityExplosion;
        entity->subId = 0;
        entity->step = 0;
        return;
    }

    InitializeEntity(&D_80180C94);
    entity->unk19 = 4;
    entity->animCurFrame = entity->subId + 15;

    if (entity->facing != 0) {
        entity->accelerationX = -entity->accelerationX;
    }
}

void func_801C6574(Entity* entity) {
    s32 var_a0;
    u32 value;

    if (entity->step) {
        if (entity->flags & 0x100) {
            func_801BD568(0, 0);
            return;
        }

        entity->unk1E += 0x80;
        entity->accelerationY += 0x2400;
        MoveEntity();

        if (entity->posY.i.hi > 240) {
            DestroyEntity(entity);
        }
    } else {
        InitializeEntity(&D_80180CA0);
        entity->posY.val -= 0x1000;
        value = func_801BCBEC();
        value /= 32;
        value = CLAMP_MAX(value, 7);
        var_a0 = D_80182488[value];
        value = entity->facing;

        if (value > 0) {
            var_a0 = -var_a0;
        }

        entity->accelerationY = -0x48000;
        entity->accelerationX = var_a0;
        entity->unk19 = 4;
    }
}

void func_801C6678(Entity* entity) {
    if (entity->step == 0) {
        InitializeEntity(D_80180C88);
        entity->unk1A = 0x120;
        entity->unk1C = 0x200;
        entity->unk6C = 0;
        entity->unk3C = 0;
        entity->unk19 = entity->unk19 | 0xB;
        return;
    }

    entity->facing = entity[-1].facing;
    entity->zPriority = entity[-1].zPriority - 1;
    entity->animCurFrame = entity[-1].animCurFrame;
    entity->posX.i.hi = entity[-1].posX.i.hi;
    entity->posY.i.hi = entity[-1].posY.i.hi - 0x14;

    if (entity[-1].objectId != 0x2E) {
        DestroyEntity(entity);
    }
}
