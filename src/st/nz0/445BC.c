#include "nz0.h"

// green knight that throws axes
void EntityAxeKnight(Entity* self) {
    Entity* newEntity;
    u8 animStatus;
    s8* hitbox;
    s16 temp_s2;
    s32 temp_a0;
    u8 temp_v0;

    if ((self->flags & 0x100)) {
        if (self->step != 8) {
            func_801C29B0(0x767);
            func_801B3B78();
            self->unk3C = 0;
            self->unk80.modeS16.unk0 = 0x41;
            self->zPriority -= 0x10;
            func_801BD52C(8);
        }
    }
    switch (self->step) {
    case 0:
        InitializeEntity(D_80180C64);
        self->facing = (func_801BCC5C() & 1) ^ 1;
        self->unk12 = 0xA;
        self->unk7C.S8.unk1 = 0;
        self->unk80.modeS16.unk2 = 0x200;

    case 1:
        if (func_801BCCFC(&D_80182188) & 1) {
            self->facing = (func_801BCC5C() & 1) ^ 1;
            func_801BD52C(2);
        }
        break;

    case 2:
        if (self->unk2E == 0) {
            if (self->facing == 0) {
                self->accelerationX = -0x3000;
            } else {
                self->accelerationX = 0x3000;
            }
            self->unk2E++;
        }

        animStatus = AnimateEntity(&D_80182210, self);
        if (self->animFrameDuration == 0) {
            self->facing = (func_801BCC5C() & 1) ^ 1;
        }

        if (!(animStatus & 0xFF)) {
            if (self->facing == 0) {
                self->accelerationX = -0x3000;
            } else {
                self->accelerationX = 0x3000;
            }
            if (func_801BCBEC() < 0x60) {
                func_801BD52C(3);
                self->unk7C.S8.unk0 = 1;
            }
        }
        if ((self->animFrameIdx == 1) || (self->animFrameIdx == 4)) {
            if (self->facing == 0) {
                self->accelerationX -= 0x300;
            } else {
                self->accelerationX += 0x300;
            }
        } else if (self->facing != 0) {
            self->accelerationX -= 0x300;
        } else {
            self->accelerationX += 0x300;
        }
        if (func_801BCF74(&D_80182180) & 0x60) {
            self->posX.val -= self->accelerationX;
            self->accelerationX = 0;
        }
        func_801C4550();
        break;

    case 3:
        if (self->unk2E == 0) {
            if (self->facing == 0) {
                self->accelerationX = 0x3000;
            } else {
                self->accelerationX = -0x3000;
            }
            self->unk2E++;
        }

        animStatus = AnimateEntity(&D_80182210, self);
        if (self->animFrameDuration == 0) {
            self->facing = (func_801BCC5C() & 1) ^ 1;
        }
        if (!(animStatus != 0)) {
            if (self->facing == 0) {
                self->accelerationX = 0x3000;
            } else {
                self->accelerationX = -0x3000;
            }

            if (func_801BCBEC() >= 0x51) {
                func_801BD52C(2);
                self->unk7C.S8.unk0 = 0;
            }
        }

        if ((self->animFrameIdx == 1) || (self->animFrameIdx == 4)) {
            if (self->facing == 0) {
                self->accelerationX += 0x200;
            } else {
                self->accelerationX -= 0x200;
            }
        } else if (self->facing != 0) {
            self->accelerationX += 0x200;
        } else {
            self->accelerationX -= 0x200;
        }
        if (func_801BCF74(&D_80182180) & 0x60) {
            self->posX.val -= self->accelerationX;
            self->accelerationX = 0;
        }
        func_801C4550();
        break;

    case 4:
        temp_v0 = AnimateEntity(&D_80182244, self);
        if (!(temp_v0 != NULL)) {
        label:
            if (func_801BCBEC() < 89) {
                func_801BD52C(3);
                self->unk7C.S8.unk0 = 1;
            } else {
                func_801BD52C(2);
                self->unk7C.S8.unk0 = 0;
            }
        } else if ((temp_v0 & 0x80) && (self->animFrameIdx == 7)) {
            func_801C29B0(0x766);
            newEntity = AllocEntity(D_8007A958, &D_8007A958[32]);
            if (newEntity != NULL) {
                CreateEntityFromCurrentEntity(0x2A, newEntity);
                newEntity->facing = self->facing;
                newEntity->posY.i.hi -= 12;
                if (newEntity->facing != 0) {
                    newEntity->posX.i.hi += 8;
                } else {
                    newEntity->posX.i.hi -= 8;
                }
            }
        }
        break;

    case 5:
        temp_v0 = AnimateEntity(&D_80182220, self);
        if (temp_v0 != 0) {
            if ((temp_v0 & 0x80) && (self->animFrameIdx == 6)) {
                func_801C29B0(0x766);
                newEntity = AllocEntity(D_8007A958, &D_8007A958[32]);
                if (newEntity != NULL) {
                    CreateEntityFromCurrentEntity(0x2A, newEntity);
                    newEntity->facing = self->facing;
                    newEntity->subId = 1;
                    newEntity->posY.i.hi += 12;
                    if (newEntity->facing != 0) {
                        newEntity->posX.i.hi += 8;
                    } else {
                        newEntity->posX.i.hi -= 8;
                    }
                }
            }
        } else {
            goto label;
        }
        break;

    case 7:
        temp_v0 = AnimateEntity(&D_80182244, self);
        if (!(temp_v0 & 0xFF)) {
            if (func_801BCBEC() >= 0x59) {
                func_801BD52C(2);
                self->unk7C.S8.unk0 = 0;
            } else {
                func_801BD52C(3);
                self->unk7C.S8.unk0 = 1;
            }
            break;
        }

        if ((temp_v0 & 0x80) && (self->animFrameIdx == 7)) {
            func_801C29B0(0x766);
            newEntity = AllocEntity(D_8007A958, &D_8007A958[32]);
            if (newEntity != NULL) {
                CreateEntityFromCurrentEntity(0x2A, newEntity);
                newEntity->facing = self->facing;
                newEntity->subId = 2;
                newEntity->posY.i.hi -= 40;
                if (newEntity->facing != 0) {
                    newEntity->posX.i.hi += 16;
                } else {
                    newEntity->posX.i.hi -= 16;
                }
            }
        }
        break;

    case 8:
        if (self->unk80.modeS16.unk0 != 0) {
            temp_s2 = self->unk80.modeS16.unk0 - 1;
            self->unk80.modeS16.unk0 = temp_s2;
            if (!(temp_s2 & 7)) {
                newEntity = AllocEntity(D_8007D858, &D_8007D858[32]);
                if (newEntity != NULL) {
                    CreateEntityFromEntity(2, self, newEntity);
                    temp_a0 = ((s32)(temp_s2 << 0x10) >> 0x13);
                    newEntity->subId = 2;
                    newEntity->posX.i.hi += D_80182198[temp_a0];
                    newEntity->posY.i.hi += D_8018219A[temp_a0];
                }
            }
        }

        if (AnimateEntity(&D_80182268, self) == 0) {
            if (func_801C4198(self) != 0) {
                DestroyEntity(self);
                return;
            }
            if (self->unk2E < 16) {
                self->animCurFrame = 0;
            }
        }
        break;
    }

    hitbox = 4 * D_80182284[self->animCurFrame] + D_80182274 - 1; // Weird ?
    hitbox++;
    self->unk10 = *hitbox++;
    self->unk12 = *hitbox++;
    self->hitboxWidth = *hitbox++;
    self->hitboxHeight = *hitbox++;
}

void func_801C4CC0(void) {
    if (g_CurrentEntity->subId != 0) {
        g_CurrentEntity->unk1E += 0x80;
    } else {
        g_CurrentEntity->unk1E -= 0x80;
    }

    g_CurrentEntity->unk1E &= 0xFFF;
}

void EntityAxeKnightThrowingAxe(Entity* entity) {
    s32 accelerationX;

    if (entity->flags & 0x100) {
        func_801C29B0(0x66B);
        func_801BD568(0, 0);
        return;
    }

    switch (entity->step) {
    case 0:
        InitializeEntity(D_80180C70);
        entity->unk19 = 4;
        entity->accelerationY = D_801822C8[entity->subId];
        accelerationX = D_801822BC[entity->subId];

        if (entity->facing == 0) {
            entity->accelerationX = -accelerationX;
        } else {
            entity->accelerationX = accelerationX;
        }

        entity->unk7C.s = -0x40;

        if (entity->subId == 2) {
            entity->step++;
            return;
        }
        break;

    case 1:
        func_801C4CC0();
        if ((u16)entity->unk7C.s < 0x20) {
            if (entity->facing != 0) {
                entity->accelerationX -= 0x2000;
            } else {
                entity->accelerationX += 0x2000;
            }
        }

        entity->unk7C.s++;
        MoveEntity();
        break;

    case 2:
        func_801C4CC0();
        entity->accelerationY += 0x2000;
        MoveEntity();
        break;
    }
}

void EntityBloodSplatter(Entity* self) {
    Primitive *prim, *prim2, *prim3;
    s16 firstPrimIndex;

    switch (self->step) {
    case 0:
        InitializeEntity(D_80180BE0);
        return;

    case 1:
        firstPrimIndex = g_api.AllocPrimitives(4, 8);
        if (firstPrimIndex != -1) {
            self->firstPolygonIndex = firstPrimIndex;
            prim = &g_PrimBuf[firstPrimIndex];
            *(s32*)&self->unk7C = prim;
            self->flags |= 0x800000;
            self->step++;
            return;
        }
        DestroyEntity(self);
        break;

    case 2:
        prim = func_801C9E98(*(s32*)&self->unk7C, 2);
        if (prim != NULL) {
            self->unk8C.primPtr = prim;
            func_801CA07C(prim);
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

        prim = func_801C9E98(*(s32*)&self->unk7C, 2);
        if (prim != NULL) {
            *(s32*)&self->unk90 = prim;
            func_801CA07C(prim);
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
        prim = self->unk8C.entityPtr;
        func_801C9930(prim);

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
        if (func_801C9D18(&D_8018238C, prim) == 0) {
            func_801CA0D0(prim);
        }

        prim = *(s32*)&self->unk90;
        func_801C9930(prim);
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

        if (func_801C9D18(&D_801823A4, prim) == 0) {
            func_801CA0D0(prim);
        }

        if (self->unk80.modeS16.unk0++ > 128) {
            DestroyEntity(self);
        }
        break;
    }
}

void func_801C53AC(Primitive* prim) {
    switch (prim->next->u2) {
    case 0:
        prim->tpage = 0x12;
        prim->clut = 0x16D;
        prim->u0 = 80;
        prim->u1 = 96;
        prim->v1 = 239;
        prim->v0 = 239;
        prim->v3 = 255;
        prim->v2 = 255;
        prim->u2 = prim->u0;
        prim->u3 = prim->u1;
        *(s16*)&prim->next->r2 = 16;
        *(s16*)&prim->next->b2 = 16;
        prim->next->x1 = g_CurrentEntity->posX.i.hi;
        prim->next->y0 = g_CurrentEntity->posY.i.hi;

        if (g_CurrentEntity->facing != 0) {
            prim->next->x1 -= 8;
        } else {
            prim->next->x1 += 8;
        }
        if (prim->next->r3 == 0) {
            *(s32*)&prim->next->u0 = -0x4000;
        } else {
            *(s32*)&prim->next->u0 = 0x4000;
        }
        *(s32*)&prim->next->r1 = -0x20000;
        prim->next->b3 = 0x80;
        prim->priority = g_CurrentEntity->zPriority + 1;
        prim->blendMode = 2;
        prim->next->u2 = 1;
        break;

    case 1:
        func_801C9930(prim);
        *(s32*)&prim->next->r1 += 0x2000;
        if (*(s32*)&prim->next->r1 > 0x20000) {
            func_801CA0D0(prim);
        }
        break;
    }
}