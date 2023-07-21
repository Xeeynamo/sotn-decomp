#include "st0.h"

void func_801A7D64(Entity* self) {
    s32 temp_v0;
    ObjInit2* obj = &D_80180638[self->params];

    if (self->step == 0) {
        InitializeEntity(D_801805BC);
        self->animSet = obj->animSet;
        self->zPriority = obj->zPriority;
        self->unk5A = obj->unk4.s;
        self->palette = obj->palette;
        self->unk19 = obj->unk8;
        self->blendMode = obj->blendMode;
        if (obj->unkC != 0) {
            self->flags = obj->unkC;
        }
    }
    AnimateEntity(obj->unk10, self);
}

bool func_801A7E2C(Entity* self) {
    s16 diffX = PLAYER.posX.i.hi - self->posX.i.hi;

    diffX = ABS(diffX);
    if (self->hitboxWidth >= diffX) {
        diffX = PLAYER.posY.i.hi - self->posY.i.hi;
        diffX = ABS(diffX);
        return (self->hitboxHeight >= diffX);
    } else {
        return false;
    }
}

#ifndef NON_EQUIVALENT
INCLUDE_ASM("asm/us/st/st0/nonmatchings/27D64", EntityLockCamera);
#else
extern u16 D_801805B0[];
extern u8 D_8018065C[];
extern u8 D_80180660[];
extern u16 D_80180664[];

bool func_801A7E2C(Entity* entity);
void EntityLockCamera(Entity* entity) {
    s32 temp_v0_2;
    s32 temp_v1;
    u16* temp_v1_2;
    u16* temp_v1_5;
    u8 temp_s1;
    u8 temp_v0;
    s32 phi_v1;

    temp_s1 = entity->params;
    if (entity->step == 0) {
        InitializeEntity(D_801805B0);
        temp_v1 = temp_s1 & 0xFFFF;
        entity->unk3C = 1;
        temp_v0 = D_80180660[temp_v1];
        entity->ext.generic.unk7C.modeU16 = temp_v0;
        if (temp_v0) {
            entity->hitboxWidth = D_8018065C[temp_v1];
            entity->hitboxHeight = 20;
        } else {
            entity->hitboxWidth = 20;
            entity->hitboxHeight = D_8018065C[temp_v1];
        }
    }

    if (entity->params & 0x100) {
        temp_v1_2 = &D_80180664[(((temp_s1 & 0xFFFF) * 4) & 0xFFFF)];
        g_CurrentRoom.x = *temp_v1_2++;
        g_CurrentRoom.y = *temp_v1_2++;
        g_CurrentRoom.width = *temp_v1_2++;
        g_CurrentRoom.height = *temp_v1_2++;
        DestroyEntity(entity);
        return;
    }

    if (func_801A7E2C(entity)) {
        temp_v0_2 = GetSideToPlayer();
        if (entity->ext.generic.unk7C.modeU16) {
            phi_v1 = (temp_v0_2 & 2) * 2;
        } else {
            phi_v1 = (temp_v0_2 & 1) * 4;
        }

        temp_v1_5 = &D_80180664[(phi_v1 + temp_s1 * 8) & 0xFFFF];
        g_CurrentRoom.x = *temp_v1_5++;
        g_CurrentRoom.y = *temp_v1_5++;
        g_CurrentRoom.width = *temp_v1_5++;
        g_CurrentRoom.height = *temp_v1_5++;
    }
}
#endif

void func_801A805C(Entity* self) {
    Entity* newEntity;
    s32 entityCount;
    u16* paramsPtr;
    u16 params_;
    u16* temp;
    s16 posY;
    s32 i;
    u16 params = self->params >> 0xC;

    if (self->step != 0) {
        AnimateEntity(D_801806D0[params], self);
        if (self->unk44 != 0) {
            params_ = params - 2;
            if (params_ < 2) {
                self->facing = GetSideToPlayer() & 1;
                posY = self->posY.i.hi - 40;

                if (params == 2) {
                    entityCount = 4;
                } else {
                    entityCount = 3;
                }

                if (params == 3) {
                    temp = &D_80180770[10];
                } else {
                    temp = &D_80180770;
                }

                for (i = 0, paramsPtr = temp; i < entityCount; i++) {
                    newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
                    if (newEntity != NULL) {
                        CreateEntityFromEntity(E_ID_26, self, newEntity);
                        newEntity->posY.i.hi = posY;
                        newEntity->params = *paramsPtr;
                        newEntity->facing = self->facing;
                    }
                    newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
                    if (newEntity != NULL) {
                        CreateEntityFromEntity(E_EXPLOSION, self, newEntity);
                        newEntity->posY.i.hi = posY;
                        newEntity->params = 0;
                    }
                    posY += 16;
                    paramsPtr++;
                }
                g_api.PlaySfx(0x67F);
            } else {
                if (params == 9) {
                    newEntity = AllocEntity(&g_Entities[160], &g_Entities[192]);
                    if (newEntity != NULL) {
                        CreateEntityFromCurrentEntity(E_ID_26, newEntity);
                        newEntity->params = 0x100;
                    }
                }
                g_api.PlaySfx(0x61D);
            }
            newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (newEntity != NULL) {
                CreateEntityFromCurrentEntity(E_EXPLOSION, newEntity);
                newEntity->params = D_80180704[params];
            }
            ReplaceBreakableWithItemDrop(self);
        }
    } else {
        InitializeEntity(D_80180574);
        self->zPriority = g_zEntityCenter.S16.unk0 - 0x14;
        self->blendMode = D_8018074C[params];
        self->hitboxHeight = D_801806F8[params];
        self->animSet = D_80180724[params];
        self->unk5A = D_80180738[params];
        self->palette = D_80180710[params];
        self->hitboxOffY = D_80180758[params];
    }
}

// Entity ID: 0x26
void func_801A8328(Entity* self) {
    s16 firstPrimIndex;
    Entity* newEntity;
    Collider collider;
    Primitive* prim;
    s32 velX;
    s16 temp2;

    switch (self->step) {
    case 0:
        if (self->params & 0x100) {
            InitializeEntity(D_801805D4);
            self->animSet = ANIMSET_OVL(4);
            self->unk5A = 0x5B;
            self->palette = 0x212;
            self->animCurFrame = 0x15;
            self->zPriority = 0x6A;
            self->step = 256;
            break;
        }

        InitializeEntity(D_8018058C);
        firstPrimIndex = g_api.AllocPrimitives(PRIM_GT4, 2);
        if (firstPrimIndex != -1) {
            prim = &g_PrimBuf[firstPrimIndex];
            self->primIndex = firstPrimIndex;
            LOW(self->ext.generic.unk7C.s) = prim;
            self->flags |= FLAG_HAS_PRIMS;
            func_801BD80C(prim, firstPrimIndex);
            prim->tpage = 0x16;
            prim->clut = 0x216;
            prim->u0 = prim->u2 = 0x98;
            prim->u1 = prim->u3 = 0xA7;
            temp2 = (self->params * 16) - 124;
            prim->v2 = prim->v3 = temp2 + 15;
            prim->v0 = prim->v1 = temp2;
            prim->next->x1 = self->posX.i.hi;
            prim->next->y0 = self->posY.i.hi;
            LOH(prim->next->r2) = 0x10;
            LOH(prim->next->b2) = 0x10;
            prim->next->b3 = 0x80;
            prim->priority = self->zPriority;
            prim->blendMode = 2;
            velX = ((Random() & 7) << 0xC) + 0x8000;
            self->velocityX = velX;
            if (self->facing == 0) {
                self->velocityX = -velX;
            }
            self->velocityY = ((Random() & 7) << 0xC) - 0x8000;
        } else {
            DestroyEntity(self);
            break;
        }

    case 1:
        MoveEntity();

        prim = LOW(self->ext.generic.unk7C.s);
        self->velocityY += 0x2000;
        prim->next->x1 = self->posX.i.hi;
        prim->next->y0 = self->posY.i.hi;

        if (self->facing != 0) {
            prim->next->tpage += 0x10;
        } else {
            prim->next->tpage -= 0x10;
        }

        func_801BD0C0(prim);

        g_api.CheckCollision(
            self->posX.i.hi, (s16)(self->posY.i.hi + 8), &collider, 0);
        if (collider.effects & EFFECT_SOLID) {
            g_api.PlaySfx(0x691);
            newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (newEntity != NULL) {
                CreateEntityFromCurrentEntity(E_EXPLOSION, newEntity);
                newEntity->params = 0;
            }
            DestroyEntity(self);
            break;
        }
    }
}

void func_801A8620(Entity* entity) {
    s16 dist;
    s32 params = (s16)entity->params;

    FntPrint("set:%04x\n", params);
    FntPrint("sx:%04x\n", g_CurrentRoom.left);
    FntPrint("ex:%04x\n", g_CurrentRoom.right);

    switch (entity->step) {
    case 0:
        InitializeEntity(D_801805BC);
        entity->animSet = ANIMSET_DRA(2);
        entity->animCurFrame = 1;
        entity->zPriority = 0xB0;
        break;

    case 1:
        dist = entity->posY.i.hi - PLAYER.posY.i.hi;
        dist = ABS(dist);

        if (dist < 0x20) {
            switch (params) {
            case 0:
                if (playerX > 0x280) {
                    g_CurrentRoom.width = 0x280;
                    g_CurrentRoom.right--;
                    entity->step++;
                }
                break;

            case 1:
                if (playerX < 0x180) {
                    g_CurrentRoom.x = 0x180;
                    g_CurrentRoom.left++;
                    entity->step++;
                }
                break;

            case 3:
                if (playerX < 0x100) {
                    g_CurrentRoom.x = 0x100;
                    g_CurrentRoom.left++;
                    entity->step++;
                }
                break;

            case 5:
                if (playerX < 0x80) {
                    g_CurrentRoom.x = 0x80;
                    entity->step++;
                }
                break;

            case 6:
                if (playerX > 0x480) {
                    g_CurrentRoom.width = 0x480;
                    entity->step++;
                }
                break;

            case 7:
                if (playerX > 0x480) {
                    g_CurrentRoom.width = 0x480;
                    entity->step++;
                }
                break;

            case 8:
                if (playerX < 0x80) {
                    g_CurrentRoom.x = 0x80;
                    entity->step++;
                }
                break;

            case 9:
                if (playerX > 0x280) {
                    g_CurrentRoom.width = 0x280;
                    entity->step++;
                }
                break;

            case 10:
                if (playerX < 0x180) {
                    g_CurrentRoom.x = 0x180;
                    g_CurrentRoom.left++;
                    entity->step++;
                }
                break;

            case 11:
                if (playerX > 0x280) {
                    g_CurrentRoom.width = 0x280;
                    g_CurrentRoom.right--;
                    entity->step++;
                }
                break;

            case 12:
                if (playerX < 0x180) {
                    g_CurrentRoom.x = 0x180;
                    g_CurrentRoom.left++;
                    entity->step++;
                }
                break;

            case 2:
            case 4:
            case 13:
            case 14:
                if (playerX > 0x300) {
                    g_CurrentRoom.width = 0x300;
                    g_CurrentRoom.right--;
                    entity->step++;
                }
                break;
            }
        }
        break;
    }
}

void func_801A8984(void) {
    g_Dialogue.D_801C24D8 = 2;
    g_Dialogue.D_801C24D6 = 2;
    g_Dialogue.D_801C24DA = 0;
    g_Dialogue.D_801C24DE = 0;
    g_Dialogue.D_801C24E2 = 0;
    g_Dialogue.D_801C24E3 = 8;
    g_Dialogue.D_801C24D2 = g_Dialogue.D_801C24D4 + 0x14;
}

s32 func_801A89D8(const char* textDialogue) {
    Primitive* prim;
    s16 firstPrimIndex;

    firstPrimIndex = g_api.AllocPrimitives(PRIM_SPRT, 8);
    g_Dialogue.D_801C24FC[2] = firstPrimIndex;
    if (firstPrimIndex == -1) {
        g_Dialogue.D_801C24FC[2] = 0;
        return 0;
    }
    g_Dialogue.D_801C24CC = textDialogue;
    g_Dialogue.D_801C2508 = 0;
    g_Dialogue.D_801C24FC[1] = -1;
    g_Dialogue.D_801C24FC[0] = -1;
    func_801A8984();

    if (prim && prim) { // !FAKE
    }

    prim = g_Dialogue.D_801C24E4[0] = &g_PrimBuf[g_Dialogue.D_801C24FC[2]];

    prim->blendMode = 8;
    prim = g_Dialogue.D_801C24E4[1] = prim->next;

    prim->blendMode = 8;
    prim = g_Dialogue.D_801C24E4[2] = prim->next;

    prim->blendMode = 8;
    prim = g_Dialogue.D_801C24E4[3] = prim->next;

    prim->blendMode = 8;
    prim = g_Dialogue.D_801C24E4[4] = prim->next;

    prim->blendMode = 8;
    prim = g_Dialogue.D_801C24E4[5] = prim->next;

    prim->type = 4;
    prim->blendMode = 8;

    prim = prim->next;
    prim->type = 3;
    prim->r0 = prim->r1 = prim->r2 = prim->r3 = 0xFF;
    prim->g0 = prim->g1 = prim->g2 = prim->g3 = 0;
    prim->b0 = prim->b1 = prim->b2 = prim->b3 = 0;
    prim->x0 = prim->x2 = 4;
    prim->x1 = prim->x3 = 0xF8;
    prim->priority = 0x1FD;
    prim->blendMode = 8;

    prim = prim->next;
    prim->type = 1;
    prim->x0 = 3;
    prim->y0 = 0x2F;
    prim->v0 = 0x4A;
    prim->r0 = prim->g0 = prim->b0 = 0xFF;
    prim->priority = 0x1FC;
    prim->blendMode = 8;
    return 1;
}

void func_801A8B9C(s16 yOffset) {
    RECT rect;

    rect.y = (yOffset * 12) + 384;
    rect.w = 64;
    rect.x = 0;
    rect.h = 12;
    ClearImage(&rect, 0, 0, 0);
}
