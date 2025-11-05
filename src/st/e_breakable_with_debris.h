// SPDX-License-Identifier: AGPL-3.0-or-later
enum BreakableTypes {
    CANDELABRA_WALL_DOUBLE,
    NONE,
    CANDELABRA_TALL,
    CANDELABRA_SHORT,
    CANDELABRA_TABLE,
    BRAZIER,
    CANDELABRA_WALL_TRIPLE,
    URN,
    JUG,
    BUST,
};

enum BreakableDebrisSteps {
    INIT,
    UPDATE,
    DEBRIS_NOP = 256,
};

#if defined(VERSION_PSP)
extern s32 E_ID(BREAKABLE_DEBRIS);
#endif

extern EInit OVL_EXPORT(EInitBreakable);
extern EInit g_EInitInteractable;
extern EInit g_EInitParticle;

void OVL_EXPORT(EntityBreakable)(Entity* self) {
    Entity* entity;
    s16* debrisOffsetsY;
    u16 breakableType;
    s32 debrisIndex;
    s32 debrisCount;
    s16 posY;

    breakableType = self->params >> 12;
    if (!self->step) {
        InitializeEntity(OVL_EXPORT(EInitBreakable));
        self->zPriority = g_unkGraphicsStruct.g_zEntityCenter - 20;
        self->drawMode = draw_modes[breakableType];
        self->hitboxHeight = hitbox_heights[breakableType];
        self->animSet = anim_sets[breakableType];
        self->unk5A = unk_5A[breakableType];
        self->palette = palettes[breakableType];
#ifdef INVERTED_STAGE
        self->hitboxOffY = -hitbox_offsets_y[breakableType];
#else
        self->hitboxOffY = hitbox_offsets_y[breakableType];
#endif
    }
    AnimateEntity(animations[breakableType], self);
    if (self->hitParams) {
        entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
        if (entity != NULL) {
            CreateEntityFromCurrentEntity(E_EXPLOSION, entity);
            entity->params = explosion_types[breakableType];
        }
        switch (breakableType) {
        case CANDELABRA_TALL:
        case CANDELABRA_SHORT:
            self->facingLeft = GetSideToPlayer() & 1;
#ifdef INVERTED_STAGE
            posY = self->posY.i.hi + 40;
#else
            posY = self->posY.i.hi - 40;
#endif
            if (breakableType == CANDELABRA_TALL) {
                debrisCount = 4;
            } else {
                debrisCount = 3;
            }
            debrisOffsetsY = candelabra_debris_offsets_y;
            if (breakableType == CANDELABRA_SHORT) {
                debrisOffsetsY += 5;
            }
            for (debrisIndex = 0; debrisIndex < debrisCount; debrisIndex++) {
                entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
                if (entity != NULL) {
                    CreateEntityFromEntity(
                        E_ID(BREAKABLE_DEBRIS), self, entity);
                    entity->posY.i.hi = posY;
                    entity->params = debrisOffsetsY[debrisIndex];
                    entity->facingLeft = self->facingLeft;
                }
                entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
                if (entity != NULL) {
                    CreateEntityFromEntity(E_EXPLOSION, self, entity);
                    entity->posY.i.hi = posY;
                    entity->params = EXPLOSION_SMALL;
                }
#ifdef INVERTED_STAGE
                posY -= 16;
#else
                posY += 16;
#endif
            }
            g_api.PlaySfx(CANDELABRA_HIT_SFX);
            break;
        case BUST:
            entity = AllocEntity(&g_Entities[160], &g_Entities[192]);
            if (entity != NULL) {
                CreateEntityFromCurrentEntity(E_ID(BREAKABLE_DEBRIS), entity);
                entity->params = 256;
            }
            g_api.PlaySfx(SFX_GLASS_BREAK_E);
#if defined(STAGE_IS_TOP) || defined(STAGE_IS_RTOP)
            entity = AllocEntity(&g_Entities[160], &g_Entities[192]);
            if (entity != NULL) {
                CreateEntityFromEntity(E_HEART_DROP, self, entity);
                entity->params = self->params & 0x1FF;
            }
            PreventEntityFromRespawning(self);
            DestroyEntity(self);
            return;
#endif
            break;
        case URN:
            g_api.PlaySfx(SFX_GLASS_BREAK_E);
            entity = AllocEntity(&g_Entities[160], &g_Entities[192]);
            if (entity != NULL) {
                CreateEntityFromEntity(E_HEART_DROP, self, entity);
                entity->params = self->params & 0x1FF;
            }
            PreventEntityFromRespawning(self);
            DestroyEntity(self);
            return;
        case JUG:
            g_api.PlaySfx(SFX_GLASS_BREAK_E);
            entity = AllocEntity(&g_Entities[160], &g_Entities[192]);
            if (entity != NULL) {
                CreateEntityFromEntity(E_HEART_DROP, self, entity);
#ifdef STAGE_IS_NO1
                entity->params = 3; // item drop index
#else
                entity->params = self->params & 0x1FF;
#endif
            }
            PreventEntityFromRespawning(self);
            DestroyEntity(self);
            return;
        default:
            g_api.PlaySfx(SFX_CANDLE_HIT);
            break;
        }
        ReplaceBreakableWithItemDrop(self);
    }
}

void OVL_EXPORT(EntityBreakableDebris)(Entity* self) {
    Collider collider;
    Entity* explosion;
    Primitive* prim;
    s32 primIndex;
    s16 posX, posY;

    switch (self->step) {
    case INIT:
        // Always applies to the bust
        // Applies to the urn and jug if they have params & 0x1FF
        // Doesn't apply to any others
        if (self->params & 256) {
            InitializeEntity(g_EInitInteractable);
            self->animSet = OVL_BREAKABLE_ANIMSET;
            self->unk5A = 91;
            self->palette = PAL_BREAKABLE;
            self->animCurFrame = 21;
            self->zPriority = 106;
            self->step = DEBRIS_NOP; // No case defined, resulting in nop
            return;
        } else {
            InitializeEntity(g_EInitParticle);
            primIndex = g_api.AllocPrimitives(PRIM_GT4, 2);
            if (primIndex == -1) {
                DestroyEntity(self);
                return;
            }
            self->flags |= FLAG_HAS_PRIMS;
            self->primIndex = primIndex;
            prim = &g_PrimBuf[primIndex];
            self->ext.breakableDebris.prim = prim;
            UnkPolyFunc2(prim);
            prim->tpage = 22;
            prim->clut = PAL_BREAKABLE_DEBRIS;
            prim->u0 = prim->u2 = 152;
            prim->u1 = prim->u3 = 167;
            posY = 132;
            posY += self->params * 16;
#ifdef INVERTED_STAGE
            prim->v0 = prim->v1 = posY + 15;
            prim->v2 = prim->v3 = posY;
#else
            prim->v0 = prim->v1 = posY;
            prim->v2 = prim->v3 = posY + 15;
#endif
            prim->next->x1 = self->posX.i.hi;
            prim->next->y0 = self->posY.i.hi;
            LOH(prim->next->r2) = 16;
            LOH(prim->next->b2) = 16;
            prim->next->b3 = 128;
            prim->priority = self->zPriority;
            prim->drawMode = DRAW_UNK02;
            self->velocityX = ((Random() & 7) << 12) + FIX(0.5);
            if (!self->facingLeft) {
                self->velocityX = -self->velocityX;
            }
            self->velocityY = ((Random() & 7) << 12) - FIX(0.5);
        }
    case UPDATE:
        MoveEntity();
        self->velocityY += FIX(0.125);
        prim = self->ext.breakableDebris.prim;
        prim->next->x1 = self->posX.i.hi;
        prim->next->y0 = self->posY.i.hi;
        if (self->facingLeft) {
            LOH(prim->next->tpage) += 16;
        } else {
            LOH(prim->next->tpage) -= 16;
        }
        UnkPrimHelper(prim);
        posX = self->posX.i.hi;
        posY = self->posY.i.hi + 8;
        g_api.CheckCollision(posX, posY, &collider, 0);
        if (collider.effects & EFFECT_SOLID) {
            g_api.PlaySfx(BREAKABLE_HIT_SFX);
            explosion = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (explosion != NULL) {
                CreateEntityFromCurrentEntity(E_EXPLOSION, explosion);
                explosion->params = EXPLOSION_SMALL;
            }
            DestroyEntity(self);
        }
        break;
    }
}
