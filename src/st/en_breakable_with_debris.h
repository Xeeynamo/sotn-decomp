#include <stage.h>

extern u16 g_eBreakableWithDebrisInit[];

// params: (>> 12) represents the breakable type.
//         Any non-zero value is considered a "tall" breakable, meaning it breaks into more debris, some of which spawns higher up
void EntityBreakableWithDebris(Entity* self) {
    const int DebrisBaseCount = 4;
    const int DebrisTallExtraCount = 3;
    const int BackgroundBlockOffsetY = -16;
    const int BackgroundBlockTallOffsetY = -32;
    const int DebrisTallOffsetY = -20;

    u16* ptr;
    s32 i;
    u16 breakableType = self->params >> 12;
    Entity* entity;

    if (!self->step) {
        InitializeEntity(&g_eBreakableWithDebrisInit);
        self->zPriority = 0x70;
        self->drawMode = g_eBreakableDrawModes[breakableType];
        self->hitboxHeight = g_eBreakableHitboxes[breakableType];
        self->animSet = g_eBreakableAnimSets[breakableType];

        entity = self + 1;
        DestroyEntity(entity);
        CreateEntityFromEntity(E_BACKGROUND_BLOCK, self, entity);
        if (breakableType) {
            (self + 1)->posY.i.hi += BackgroundBlockTallOffsetY;
        } else {
            (self + 1)->posY.i.hi += BackgroundBlockOffsetY;
        }
        entity->params = 1;
    }

    AnimateEntity(g_eBreakableAnimations[breakableType], self);

    if (self->hitParams) {
        g_api_PlaySfx(SFX_FIRE_SHOT);
        entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
        if (entity != NULL) {
            CreateEntityFromCurrentEntity(E_EXPLOSION, entity);
            entity->params = g_eBreakableExplosionTypes[breakableType] | 0x10;
        }

        for (ptr = &g_eBreakableDebrisOffsets, i = 0; i < DebrisBaseCount; i++) {
            entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (entity != NULL) {
                CreateEntityFromEntity(E_BREAKABLE_DEBRIS, self, entity);
                entity->posX.i.hi += *ptr++;
                entity->posY.i.hi += *ptr++;
                if (breakableType != 0) {
                    entity->posY.i.hi += DebrisTallOffsetY;
                }
                entity->params = i;
            }
        }

        if (breakableType) {
            for (i = 0; i < DebrisTallExtraCount; i++) {
                entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
                if (entity != NULL) {
                    CreateEntityFromEntity(E_BREAKABLE_DEBRIS, self, entity);
                    entity->posX.i.hi += *ptr++;
                    entity->posY.i.hi += *ptr++;
                    entity->params = i + DebrisBaseCount;
                }
            }
        }
        DestroyEntity(self + 1);
        ReplaceBreakableWithItemDrop(self);
    }
}

// params: Index of breakable debris to use
//         (>= 4) Considered a "tall" breakable debris
//         (== 6) The "last standing" debris, that doesn't move
void EntityBreakableDebris(Entity* entity) {
    Collider collider;
    Primitive* prim;
    s16 primIndex;
    s32 facing;
    s32 temp_v0_2;
    u16 angle;
    u16 temp_v0_5;
    Entity* newEntity;
    s32 temp;

    switch (entity->step) {
    case 0:
        InitializeEntity(&g_eBreakableWithDebrisInit);
        entity->zPriority = 0x70;
        entity->hitboxState = 0;
        entity->drawFlags = FLAG_DRAW_ROTZ;
        entity->animCurFrame = entity->params + 28;
        facing = GetSideToPlayer() & 1;

        angle = (Random() & 0x1E) + 8;
        entity->ext.breakableDebris.angle = angle;
        if (entity->facingLeft) {
            entity->ext.breakableDebris.angle = -angle;
        }

        // Check for upper "tall" debris
        if (entity->params >= 4) {
            entity->ext.breakableDebris.angle = -entity->ext.breakableDebris.angle;
        }

        if (facing == 0) {
            entity->velocityX = FIX(-1);
        } else {
            entity->velocityX = FIX(1);
        }

        temp = 0x8000;
        temp_v0_2 = Random() << 8;
        entity->velocityX = entity->velocityX + temp - temp_v0_2;
        entity->velocityY = FIX(-3);
        entity->velocityY = (entity->params >> 1) * 0x6000 - 0x30000;

        // "Last standing" debris just sits there (tall breakables only)
        if (entity->params == 6) {
            entity->velocityX = 0;
            entity->velocityY = 0;
            entity->step = 2;
        }

        entity->primIndex = 0;
        if (entity->params == 0) {
            primIndex = g_api.AllocPrimitives(PRIM_GT4, 2);
            if (primIndex != -1) {
                prim = &g_PrimBuf[primIndex];
                entity->primIndex = primIndex;
                entity->flags |= FLAG_HAS_PRIMS;

                UnkPolyFunc2(prim, primIndex);

                prim->tpage = 0x1A;
                prim->clut = 0x159;
                prim->u0 = prim->u2 = 0x40;
                prim->u1 = prim->u3 = 0x60;
                prim->v0 = prim->v1 = 0;
                prim->v2 = prim->v3 = 0x20;

                prim->next->x1 = entity->posX.i.hi + 4;
                prim->next->y0 = entity->posY.i.hi - 8;
                LOH(prim->next->r2) = 0x20;
                LOH(prim->next->b2) = 0x20;
                prim->next->b3 = 0x10;

                prim->priority = 0x72;
                prim->drawMode = DRAW_TRANSP | DRAW_UNK02 | DRAW_COLORS | DRAW_TPAGE | DRAW_TPAGE2;
            }
        }
        break;
    case 1:
        MoveEntity();
        entity->rotZ += entity->ext.breakableDebris.angle;
        entity->velocityY += FIX(0.25);
        g_api.CheckCollision(entity->posX.i.hi, entity->posY.i.hi + 6, &collider, 0);
        if (collider.effects & 1) {
            entity->posY.i.hi += collider.unk18;
            entity->velocityY = -entity->velocityY / 2;
            entity->velocityX -= entity->velocityX / 3;
            if (entity->velocityY > FIX(-0.625)) {
                newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
                if (newEntity != 0) {
                    CreateEntityFromEntity(E_INTENSE_EXPLOSION, entity, newEntity);
                    newEntity->params = 16;
                }
                DestroyEntity(entity);
                break;
            }
        }

        if (entity->primIndex != 0) {
            prim = &g_PrimBuf[entity->primIndex];
            UnkPrimHelper(prim);
            LOH(prim->next->r2) = LOH(prim->next->b2) += 4;
            if (LOH(prim->next->r2) > 64) {
                prim->next->b3 += 252;
                if (prim->next->b3 == 0) {
                    g_api.FreePrimitives(entity->primIndex);
                    entity->primIndex = 0;
                    entity->flags &= ~FLAG_HAS_PRIMS;
                }
            }
        }
        break;
    }
}