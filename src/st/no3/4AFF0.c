// SPDX-License-Identifier: AGPL-3.0-or-later
#include "no3.h"

#include "../e_stage_name.h"

#include "../entity_soul_steal_orb.h"

#include "../entity_enemy_blood.h"

#include "sfx.h"

void EntityRoomForeground(Entity* entity) {
    ObjInit* objInit = &D_80182764[entity->params];

    if (entity->step == 0) {
        InitializeEntity(g_eInitGeneric2);
        entity->animSet = objInit->animSet;
        entity->zPriority = objInit->zPriority;
        entity->unk5A = objInit->unk5A;
        entity->palette = objInit->palette;
        entity->drawFlags = objInit->drawFlags;
        entity->drawMode = objInit->drawMode;
        if (objInit->unkC != 0) {
            entity->flags = objInit->unkC;
        }
        if (entity->params >= 5) {
            entity->rotZ = 0x800;
            entity->drawFlags |= FLAG_DRAW_ROTZ;
        }
    }
    AnimateEntity(objInit->animFrames, entity);
}

void func_801CC5A4(Entity* entity, u8 count, u8 params, s32 xDist, s32 yDist,
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
            newEnt->ext.generic.unk94 = D_80182A48[i];
            newEnt->rotY = newEnt->rotX = D_80182A38[D_80182A48[i] + arg5];
            newEnt->drawFlags = FLAG_DRAW_ROTY | FLAG_DRAW_ROTX;
            newEnt->zPriority = entity->zPriority + 1;
        }
    }
}

void func_801CC6F8(Entity* entity) {
    u16 distance = GetDistanceToPlayerX();
    bool var_s1;

    entity->ext.et_801CC820.unk86 = 0x100;
    entity->velocityX = 0;

    if (entity->params != 0) {
        SetStep(0xC);
        return;
    }

    var_s1 = 0;

    if (entity->facingLeft != 0) {
        var_s1 = entity->posX.i.hi >= 0x71;
    } else if (entity->posX.i.hi < 0x90) {
        var_s1 = 1;
    }

    if (distance < 0x70) {
        if (!(Random() & 3) && !var_s1) {
            SetStep(9);
            return;
        }
    } else if ((Random() & 3) && !var_s1) {
        SetStep(9);
        if (!(Random() & 3)) {
            entity->ext.et_801CC820.unk86 = 0;
        }
        return;
    }

    SetStep(6);
    PlaySfxPositional(0x783);
    entity->ext.et_801CC820.unk80 = 0x20;
}

void func_801CC820(Entity* entity) {
    u16 distance;

    if (entity->facingLeft == GetSideToPlayer()) {
        if (entity->params == 0) {
            SetStep(5);
        } else {
            SetStep(4);
        }
        return;
    }
    if (entity->ext.et_801CC820.unk86 == 0) {
        func_801CC6F8(entity);
        return;
    }
    distance = GetDistanceToPlayerX();
    if ((distance < 0x48) && (entity->step != 4)) {
        SetStep(4);
        return;
    }
    SetStep(3);
    if (distance < 0x60) {
        entity->ext.et_801CC820.unk7C = 1;
    } else {
        entity->ext.et_801CC820.unk7C = 0;
    }
    entity->ext.et_801CC820.unk80 = 0;
    entity->ext.et_801CC820.unk82 = 0x20;
}

void func_801CC90C(Entity* arg0) {
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

// stronger version of warg with jump and flame attack
INCLUDE_ASM("st/no3/nonmatchings/4AFF0", EntityStrongWarg);

void EntityUnkId30(Entity* self) {
    Entity* entity;
    u16 animCurFrame;
    u16* hitboxPtr;

    entity = self - 1;
    if (self->step == 0) {
        if (self->params != 0) {
            InitializeEntity(D_80180B30);
            self->hitboxState = 0;
        } else {
            if (entity->params != 0) {
                InitializeEntity(D_80180B30);
            } else {
                InitializeEntity(D_80180B24);
            }
        }
        self->animCurFrame = 0;
        self->hitPoints = 32767;
    }
    self->posX.i.hi = entity->posX.i.hi;
    self->posY.i.hi = entity->posY.i.hi;
    self->facingLeft = entity->facingLeft;
    animCurFrame = entity->animCurFrame;

    if (animCurFrame != 0) {
        if (self->params != 0) {
            if (animCurFrame < 63) {
                animCurFrame = 0;
            } else {
                animCurFrame -= 56;
            }
            hitboxPtr = &D_80182E1C[animCurFrame * 8];
        } else {
            if (entity->params != 0) {
                if (animCurFrame >= 86 || animCurFrame >= 57) {
                    animCurFrame -= 57;
                } else {
                    animCurFrame = 13;
                }
            } else {
                if (animCurFrame >= 96) {
                    animCurFrame -= 48;
                } else {
                    animCurFrame -= 1;
                }
            }
            hitboxPtr = &D_80182A4C[animCurFrame * 8];
        }
        hitboxPtr += 4;
        self->hitboxOffX = *hitboxPtr++;
        self->hitboxOffY = *hitboxPtr++;
        self->hitboxWidth = *hitboxPtr++;
        self->hitboxHeight = *hitboxPtr++;
    }
}

void EntityUnkId31(Entity* self) {
    Entity* entity;
    u16* hitboxPtr;
    u16 animFrameIdx;
    u16 animCurFrame;
    s16 i;

    entity = self - 2;
    if (self->step == 0) {
        InitializeEntity(D_80180B24);
        self->zPriority++;
        CreateEntityFromCurrentEntity(E_ID_30, self + 1);
        (self + 1)->params = 1;
    }
    if (self->ext.prim) {
        animFrameIdx = (self->animFrameIdx - 1) * 2;
        if (entity->step_s == 1) {
            hitboxPtr = D_80182FC8 + animFrameIdx;
        } else {
            hitboxPtr = D_80182FE8 + animFrameIdx;
        }

        if (self->facingLeft) {
            self->posX.i.hi = entity->posX.i.hi - *hitboxPtr++;
        } else {
            self->posX.i.hi = entity->posX.i.hi + *hitboxPtr++;
        }
        self->posY.i.hi = entity->posY.i.hi + *hitboxPtr++;
    } else {
        self->posX.i.hi = entity->posX.i.hi;
        self->posY.i.hi = entity->posY.i.hi;
    }
    self->facingLeft = entity->facingLeft;
    animCurFrame = entity->animCurFrame;
    if (self->flags & FLAG_DEAD) {
        hitboxPtr = D_80182F9C;
        PlaySfxPositional(SFX_FM_THUNDER_EXPLODE);

        for (i = 0; i < 3; i++) {
            entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (entity) {
                CreateEntityFromCurrentEntity(E_ID_32, entity);
                if (self->facingLeft != 0) {
                    entity->posX.i.hi -= *hitboxPtr++;
                } else {
                    entity->posX.i.hi += *hitboxPtr++;
                }
                entity->posY.i.hi += *hitboxPtr++;
                entity->params = i;
                entity->facingLeft = self->facingLeft;
            }
        }

        hitboxPtr = D_80182FA8;
        for (i = 0; i < 8; i++) {
            entity = AllocEntity(&g_Entities[224], &g_Entities[256]);

            if (!entity) {
                break;
            }

            CreateEntityFromCurrentEntity(E_EXPLOSION, entity);
            entity->params = ((self->zPriority + 1) << 8) + 1;
            if (self->facingLeft != 0) {
                entity->posX.i.hi -= *hitboxPtr++;
            } else {
                entity->posX.i.hi += *hitboxPtr++;
            }
            entity->posY.i.hi += *hitboxPtr++;
        }

        DestroyEntity(self);
        DestroyEntity(self + 1);
        return;
    }

    if (!self->ext.prim) {
        if (animCurFrame >= 86) {
            animCurFrame -= 10;
        } else if (animCurFrame > 72) {
            animCurFrame -= 3;
        } else if (animCurFrame < 57) {
            animCurFrame = 49;
        } else {
            animCurFrame -= 6;
        }

        if (animCurFrame != 78) {
            if ((entity->step == 3) && ((u8)entity->ext.timer.t != 0)) {
                self->animCurFrame = animCurFrame + 58;
            } else {
                self->animCurFrame = animCurFrame;
            }
        }
    } else {
        animCurFrame = self->animCurFrame;
    }

    if (animCurFrame > 81) {
        animCurFrame -= 62;
    } else if (animCurFrame > 75) {
        animCurFrame -= 59;
    } else if (animCurFrame > 62) {
        animCurFrame -= 56;
    } else if (animCurFrame > 50) {
        animCurFrame -= 50;
    } else {
        animCurFrame -= 49;
    }
    hitboxPtr = &D_80182E1C[animCurFrame * 8];
    self->hitboxOffX = *hitboxPtr++;
    self->hitboxOffY = *hitboxPtr++;
    self->hitboxWidth = *hitboxPtr++;
    self->hitboxHeight = *hitboxPtr++;
}

// some sort of explosion
void EntityExplosion3(Entity* entity) {
    Entity* newEntity;
    u32* ptr32;
    u8* ptr;
    Point16* point;
    Primitive* prim;
    u16 params;
    s32 xOffset;
    s32 yOffset;
    s16 primIndex;
    u16 angle;
    s16 posX;
    s16 posY;
    u16 newX;
    u16 newY;

    params = entity->params;
    if (!entity->step) {
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 1);
        if (primIndex != -1) {
            InitializeEntity(D_80180B3C);
            entity->flags |= FLAG_UNK_2000;
            entity->hitboxState = 0;
            prim = &g_PrimBuf[primIndex];
            entity->flags |= FLAG_HAS_PRIMS;
            entity->primIndex = primIndex;
            primIndex = entity->unk5A + 3;
            prim->tpage = primIndex >> 2;
            prim->clut = entity->palette + 1;

            ptr = &D_80183028[params * 4];
            prim->u0 = prim->u2 = *ptr++ + ((primIndex & 1) << 7);
            prim->u1 = prim->u3 = *ptr++ + ((primIndex & 1) << 7);
            prim->v0 = prim->v1 = *ptr++ + ((primIndex & 2) << 6);
            prim->v2 = prim->v3 = *ptr + ((primIndex & 2) << 6);
            prim->r0 = prim->r1 = prim->r2 = prim->r3 = 0x80;
            prim->g0 = prim->g1 = prim->g2 = prim->g3 = 0x80;
            prim->b0 = prim->b2 = prim->b1 = prim->b3 = 0x80;

            prim->priority = entity->zPriority + 1;
            prim->drawMode = DRAW_UNK02;
        } else {
            DestroyEntity(entity);
            return;
        }

        entity->ext.entityExplosion3.timer = 0;
        ptr32 = &D_80183034[params * 2];
        if (entity->facingLeft) {
            entity->velocityX = -*ptr32++;
        } else {
            entity->velocityX = *ptr32++;
        }
        entity->velocityY = *ptr32;
    }

    posX = entity->posX.i.hi;
    posY = entity->posY.i.hi;
    point = &D_80183054[params];
    prim = &g_PrimBuf[entity->primIndex];
    entity->ext.entityExplosion3.unk7E += D_8018304C[params];
    newX = point->x;
    newY = point->y;
    angle = newX + entity->ext.entityExplosion3.unk7E;
    xOffset = rcos(angle) * newY;
    if (xOffset < 0) {
        xOffset += 0xFFF;
    }
    xOffset = xOffset >> 12;
    if (entity->facingLeft != 0) {
        prim->x3 = posX - xOffset;
        prim->x0 = posX + xOffset;
    } else {
        prim->x0 = posX - xOffset;
        prim->x3 = posX + xOffset;
    }
    yOffset = rsin(angle) * newY;
    if (yOffset < 0) {
        yOffset += 0xFFF;
    }
    prim->y0 = posY - (yOffset >> 12);
    prim->y3 = posY + (yOffset >> 12);

    angle = entity->ext.entityExplosion3.unk7E - newX;
    xOffset = rcos(angle) * newY;
    if (xOffset < 0) {
        xOffset += 0xFFF;
    }
    xOffset = xOffset >> 12;
    if (entity->facingLeft != 0) {
        prim->x1 = posX - xOffset;
        prim->x2 = posX + xOffset;
    } else {
        prim->x1 = posX + xOffset;
        prim->x2 = posX - xOffset;
    }

    yOffset = rsin(angle) * newY;
    if (yOffset < 0) {
        yOffset += 0xFFF;
    }
    prim->y1 = posY + (yOffset >> 12);
    prim->y2 = posY - (yOffset >> 12);
    FallEntity();
    MoveEntity();
    if (entity->ext.entityExplosion3.timer & 1) {
        newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
        if (newEntity) {
            CreateEntityFromCurrentEntity(E_EXPLOSION, newEntity);
            point = &D_80183060[(Random() & 7)];
            newEntity->posX.i.hi += point->x;
            newEntity->posY.i.hi += point->y;
            newEntity->params = 1;
        }
    }
    entity->ext.entityExplosion3.timer++;
    if (entity->ext.entityExplosion3.timer >= 32) {
        CreateEntityFromCurrentEntity(2, entity);
        entity->params = 1;
    }
}

void func_801CE740(Entity* self) {
    Primitive* prim = &g_PrimBuf[self->primIndex];

    if (prim == NULL) {
        return;
    }

    while (prim != NULL) {
        if (prim->p1 != 0) {
            prim->p1--;
        } else {
            if (prim->p2 < 8) {
                prim->y0 = prim->y1 = prim->y1 - 12;
                if (self->facingLeft) {
                    prim->x1 = prim->x3 = prim->x3 + 8;
                    prim->r0 = prim->r2 = prim->r2 - 8;
                    prim->g0 = prim->g2 = prim->g2 - 8;
                    prim->b0 = prim->b2 = prim->b2 - 8;
                } else {
                    prim->x0 = prim->x2 = prim->x2 - 8;
                    prim->r1 = prim->r3 = prim->r3 - 8;
                    prim->g1 = prim->g3 = prim->g3 - 8;
                    prim->b1 = prim->b3 = prim->b3 - 8;
                }
            } else if (prim->p2 < 24) {
                prim->y0 = prim->y1 = prim->y1 - 12;
                if (self->facingLeft) {
                    prim->x0 = prim->x2 = prim->x2 + 4;
                    prim->x1 = prim->x3 = prim->x3 + 1;
                } else {
                    prim->x1 = prim->x3 = prim->x3 - 4;
                    prim->x0 = prim->x2 = prim->x2 - 1;
                }
            } else if (prim->p2 < 32) {
                prim->y0 = prim->y1 = prim->y1 + 36;
                if (self->facingLeft != 0) {
                    prim->x0 = prim->x2 = prim->x2 + 2;
                    if (prim->p2 & 1) {
                        prim->x1 = prim->x3 = prim->x3 + 1;
                    }
                } else {
                    prim->x1 = prim->x3 = prim->x3 - 2;
                    if (prim->p2 & 1) {
                        prim->x0 = prim->x2 = prim->x2 - 1;
                    }
                }
            } else {
                prim->drawMode = DRAW_HIDE;
            }
            prim->p2 += 1;
        }
        prim = prim->next;
    }
}

// flame-like attack on ground from strong warg
INCLUDE_ASM("st/no3/nonmatchings/4AFF0", EntityStrongWargWaveAttack);
