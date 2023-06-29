/*
 * Overlay: NZ0
 * Entity: SubWeapon container
 */

#include "nz0.h"

// SubWeapons floating in the breakable container
void EntitySubWeaponContainer(Entity* self) {
    SubWpnContDebris* glassPieceTBL;
    Entity* newEntity;
    Primitive* prim;
    s16 firstPrimIndex;
    s32 rnd;
    s32 rndPosX;
    s32 rndPosY;
    s32 absRnd;
    s32 i;
    s32 pad[23];

    switch (self->step) {
    case SUBWPNCONT_INIT:
        InitializeEntity(D_80180CE8);
        self->blendMode = 0x10;
        self->animCurFrame = 1;
        self->zPriority = 0x70;
        self->hitboxWidth = 14;
        self->hitboxHeight = 32;
        self->hitboxOffY = -0x38;
        self->hitboxOffX = 0;
        self->hitboxState = 2;
        self->palette += self->subId;
        CreateEntityFromEntity(0x3D, self, &self[1]); // Create SubWeapon
        self[1].posY.i.hi -= 72;
        self[1].subId = D_801825CC[self->subId];
        self[1].zPriority = self->zPriority - 2;

        firstPrimIndex = g_api.AllocPrimitives(4, 2);
        if (firstPrimIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->firstPolygonIndex = firstPrimIndex;
        prim = &g_PrimBuf[firstPrimIndex];
        *(s32*)&self->ext.generic.unk7C = prim;
        self->flags |= FLAG_FREE_POLYGONS;
        while (prim != NULL) {
            prim->priority = self->zPriority + 0xFFFF;
            prim->blendMode = 8;
            prim = prim->next;
        }
        break;

    case SUBWPNCONT_IDLE: // Spawn Liquid bubbles
        if (!(g_blinkTimer & 0xF)) {
            newEntity = AllocEntity(D_8007D858, &D_8007D858[32]);
            if (newEntity != NULL) {
                CreateEntityFromEntity(0x3C, self, newEntity);
                rnd = (Random() & 0x18) - 12;
                newEntity->posX.i.hi += rnd;
                newEntity->posY.i.hi -= 30;
                newEntity->subId = Random() & 3;
                if (newEntity->subId == 0) {
                    absRnd = ABS(rnd);
                    if (absRnd >= 9) {
                        newEntity->subId = 1;
                    }
                }
                newEntity->zPriority = self->zPriority - 1;
            }
        }

        if (self->hitFlags != 0) { // container got hit!
            self->step++;
        }
        break;

    case SUBWPNCONT_BREAK: // Break container into pieces
        // Spawn falling glass pieces
        glassPieceTBL = D_80182584;
        i = 0;
        g_api.FreePrimitives(self->firstPolygonIndex);
        self->flags &= ~FLAG_FREE_POLYGONS;
        g_api.PlaySfx(NA_SE_EV_GLASS_BREAK);
        while (i < ENTITY_SUBWPNCONT_DEBRIS_COUNT) {
            newEntity = AllocEntity(D_8007D858, &D_8007D858[32]);
            if (newEntity != NULL) {
                CreateEntityFromEntity(0x3A, self, newEntity);
                newEntity->posX.i.hi += glassPieceTBL->posX;
                newEntity->posY.i.hi += glassPieceTBL->posY;
                newEntity->ext.generic.unk84.S16.unk0 = glassPieceTBL->posX;
                newEntity->subId = glassPieceTBL->subId;
                newEntity->facing = glassPieceTBL->facing;
                newEntity->ext.generic.unk84.S16.unk2 = self->subId;
            }
            glassPieceTBL++;
            i++;
        }

        for (i = 0; i < 96; i++) { // Spawn falling liquid
            newEntity = AllocEntity(&g_Entities[UNK_ENTITY_51],
                                    &g_Entities[UNK_ENTITY_100]);
            if (newEntity != NULL) {
                CreateEntityFromEntity(0x3B, self, newEntity);
                rndPosX = (Random() & 0x1F) - 16;
                rndPosY = -(Random() & 0x3F) - 16;
                newEntity->posX.i.hi += rndPosX;
                newEntity->posY.i.hi += rndPosY;
                newEntity->rotAngle = ratan2(rndPosY, rndPosX);
                newEntity->zPriority = self->zPriority + 1;
            }
        }
        func_801C29B0(NA_SE_EV_VASE_BREAK);
        self->hitboxState = 0;
        self->animCurFrame = 2;
        self->step++;
        break;

    case SUBWPNCONT_DEBUG:
        /**
         * Debug: Press SQUARE / CIRCLE on the second controller
         * to advance/rewind current animation frame
         */
        FntPrint("charal %x\n", self->animCurFrame);
        if (g_pads[1].pressed & PAD_SQUARE) {
            if (self->subId == 0) {
                newEntity->animCurFrame++;
                self->subId |= 1;
            } else {
                break;
            }
        } else {
            self->subId = 0;
        }
        if (g_pads[1].pressed & PAD_CIRCLE) {
            if (self->step_s == 0) {
                newEntity->animCurFrame--;
                self->step_s |= 1;
                break;
            }
        } else {
            self->step_s = 0;
        }
        break;
    }
}

// Subweapon container falling glass pieces
void func_801C7538(Entity* entity) {
    s32 new_var;
    s16 var_v0;

    switch (entity->step) {
    case 0:
        InitializeEntity(D_80180CF4);
        entity->unk19 = 4;
        entity->animCurFrame = entity->subId;
        entity->palette += entity->ext.generic.unk84.S16.unk2;
        entity->accelerationX = entity->ext.generic.unk84.S16.unk0 << 12;
        entity->accelerationX += 0x8000 - (Random() << 8);
        entity->accelerationY -= (Random() & 0x1F) << 12;
        break;

    case 1:
        MoveEntity();
        entity->accelerationY += 0x2000;

        if (entity->accelerationX != 0) {
            if (entity->facing == 0) {
                new_var = (u16)entity->rotAngle - 16;
                var_v0 = new_var;
            } else {
                var_v0 = entity->rotAngle + 16;
            }
        } else if (entity->facing != 0) {
            var_v0 = entity->rotAngle - 16;
        } else {
            var_v0 = entity->rotAngle + 16;
        }

        entity->rotAngle = var_v0;
        break;
    }
}

// falling liquid from subweapons container
void func_801C7654(Entity* entity) {
    Collider collider;

    switch (entity->step) {
    case 0:
        InitializeEntity(D_80180BE0);
        entity->animSet = 2;
        entity->palette = 0x816D;
        entity->blendMode = 0x70;
        entity->accelerationX = rcos(entity->rotAngle) * 0x10;
        entity->accelerationY = rsin(entity->rotAngle) * 0x10;
        break;

    case 1:
        AnimateEntity(D_801825F0, entity);
        MoveEntity();
        entity->accelerationY += 0x2000;

        g_api.CheckCollision(entity->posX.i.hi, entity->posY.i.hi + 8,
                             &collider.effects, 0);

        if (collider.effects & EFFECT_SOLID) {
            entity->unk19 = 2;
            entity->unk1C = 0x100;
            entity->accelerationY = 0x4000;
            entity->accelerationX *= 8;
            entity->step++;
        }
        break;

    case 2:
        MoveEntity();
        entity->unk1C -= 8;
        if (!(entity->unk1C << 0x10)) {
            DestroyEntity(entity);
        }
        break;
    }
}

// Liquid bubbles from the Subweapon container
void func_801C77B8(Entity* entity) {
    s16 temp_v1_2;

    switch (entity->step) {
    case 0:
        InitializeEntity(D_80180CF4);
        entity->unk19 = 3;
        entity->unk1C = 0x100;
        entity->unk1A = 0x100;
        entity->accelerationX = 0;
        entity->animCurFrame = entity->subId + 8;
        entity->accelerationY = D_80182600[entity->subId];
        break;

    case 1:
        MoveEntity();
        temp_v1_2 = entity->unk1C - 8;
        entity->accelerationY -= 0x400;
        entity->unk1C = temp_v1_2;
        entity->unk1A = temp_v1_2;

        if ((temp_v1_2 << 0x10) == 0) {
            DestroyEntity(entity);
        }
        break;
    }
}

void func_801C7884(Entity* entity) {
    u16 subId = entity->subId;

    switch (entity->step) {
    case 0:
        InitializeEntity(D_80180BD4);
        entity->hitboxState = 0;

    case 1:
        MoveEntity();
        AnimateEntity(D_80181D3C[subId], entity);

        entity->accelerationY = rsin(entity->rotAngle) * 2;
        entity->rotAngle += 0x20;

        if (entity[-1].step != 1) {
            entity->objectId = E_PRIZE_DROP;
            entity->pfnUpdate = EntityPrizeDrop;
            entity->animFrameDuration = 0;
            entity->animFrameIdx = 0;
            entity->step = 0;
            entity->hitboxState = 1;
        }
    }
}