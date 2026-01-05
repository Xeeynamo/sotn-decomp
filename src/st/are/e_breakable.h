// SPDX-License-Identifier: AGPL-3.0-or-later
extern EInit g_EInitInteractable;
#ifdef INVERTED_STAGE
extern EInit g_EInitEnvironmentBreakable;
#else
extern EInit g_EInitEnvironment;
#endif
extern EInit g_EInitParticle;
extern EInit OVL_EXPORT(EInitBreakable);

#ifdef VERSION_PSP
extern s32 E_ID(BREAKABLE_DEBRIS);
#endif

static AnimateEntityFrame anim_candelabra_wall_double[] = {
    {4, 1}, {4, 2}, POSE_LOOP(0)};
static AnimateEntityFrame anim_torch[] = {
    {4, 20}, {4, 21}, {4, 22}, {4, 23}, {4, 24}, POSE_LOOP(0)};
static AnimateEntityFrame anim_candelabra_tall[] = {
    {5, 1}, {5, 2}, {5, 3}, {5, 4}, POSE_LOOP(0)};
static AnimateEntityFrame anim_candelabra_short[] = {
    {5, 5}, {5, 6}, {5, 7}, {5, 8}, POSE_LOOP(0)};
static AnimateEntityFrame anim_candelabra_table[] = {
    {5, 9}, {5, 10}, {5, 11}, {5, 12}, POSE_LOOP(0)};
static AnimateEntityFrame anim_brazier[] = {
    {5, 13}, {5, 14}, {5, 15}, {5, 16}, POSE_LOOP(0)};
static AnimateEntityFrame anim_candelabra_wall[] = {
    {5, 17}, {5, 18}, {5, 19}, POSE_LOOP(0)};
static AnimateEntityFrame anim_urn[] = {{5, 23}, POSE_LOOP(0)};
static AnimateEntityFrame anim_jug[] = {{5, 22}, POSE_LOOP(0)};
static AnimateEntityFrame anim_bust[] = {
    {5, 20}, {-1, -1}, {5, 21}, {5, 21}, POSE_END};
static AnimateEntityFrame* animations[] = {
    anim_candelabra_wall_double, // params 0x0000-0x0FFF
    anim_torch,                  // params 0x1000-0x1FFF
    anim_candelabra_tall,        // params 0x2000-0x2FFF
    anim_candelabra_short,       // params 0x3000-0x3FFF
    anim_candelabra_table,       // params 0x4000-0x4FFF
    anim_brazier,                // params 0x5000-0x5FFF
    anim_candelabra_wall,        // params 0x6000-0x6FFF
    anim_urn,                    // params 0x7000-0x7FFF
    anim_jug,                    // params 0x8000-0x8FFF
    anim_bust                    // params 0x9000-0x9FFF
};

// This has a strange extra element when there should only 10
static u8 hitbox_heights[] = {8, 16, 40, 24, 16, 16, 8, 8, 8, 8, 8};
static u8 explosion_types[] = {
    EXPLOSION_SMALL,          EXPLOSION_SMALL_MULTIPLE,
    EXPLOSION_SMALL_MULTIPLE, EXPLOSION_SMALL_MULTIPLE,
    EXPLOSION_SMALL_MULTIPLE, EXPLOSION_SMALL_MULTIPLE,
    EXPLOSION_SMALL,          EXPLOSION_SMALL_MULTIPLE,
    EXPLOSION_SMALL_MULTIPLE, EXPLOSION_SMALL_MULTIPLE};
static u16 palettes[] = {
    PAL_NULL,      PAL_NULL,      PAL_BREAKABLE, PAL_BREAKABLE, PAL_BREAKABLE,
    PAL_BREAKABLE, PAL_BREAKABLE, PAL_BREAKABLE, PAL_BREAKABLE, PAL_BREAKABLE};
static u16 anim_sets[] = {
    ANIMSET_DRA(3),
#ifdef INVERTED_STAGE
    ANIMSET_OVL(2),
#else
    ANIMSET_OVL(1),
#endif
    ANIMSET_OVL(10), ANIMSET_OVL(10), ANIMSET_OVL(10), ANIMSET_OVL(10),
    ANIMSET_OVL(10), ANIMSET_OVL(10), ANIMSET_OVL(10), ANIMSET_OVL(10)};
static u16 unk_5A[] = {0, 0, 91, 91, 91, 91, 91, 91, 91, 91};
static u8 draw_modes[] = {
    DRAW_TPAGE | DRAW_TPAGE2 | DRAW_UNK_40,
    DRAW_TPAGE | DRAW_TPAGE2,
    DRAW_TPAGE | DRAW_TPAGE2,
    DRAW_TPAGE | DRAW_TPAGE2,
    DRAW_TPAGE | DRAW_TPAGE2,
    DRAW_TPAGE | DRAW_TPAGE2,
    DRAW_TPAGE | DRAW_TPAGE2,
    DRAW_TPAGE | DRAW_TPAGE2,
    DRAW_TPAGE | DRAW_TPAGE2,
    DRAW_TPAGE | DRAW_TPAGE2,
};
// Strangely this is defined as a u16 for PSP match?
static u16 hitbox_offsets_y[] = {0, 0, -24, -16, 0, 0, 0, 0, 0, 0, 0, 0};
static s16 candelabra_debris_offsets_y[] = {0, 1, 2, 2, 3, 0, 1, 2, 3, 0};

void OVL_EXPORT(EntityBreakable)(Entity* self) {
    Entity* entity;
    Primitive* prim;
    s16* debrisOffsetsY;
    s32 debrisIndex;
    s16 posY;
    u16 breakableType;
    s32 debrisCount;

    breakableType = self->params >> 0xC;
    if (!self->step) {
        InitializeEntity(OVL_EXPORT(EInitBreakable));
        self->zPriority = g_unkGraphicsStruct.g_zEntityCenter - 0x14;
        self->drawMode = draw_modes[breakableType];
        self->hitboxHeight = hitbox_heights[breakableType];
        self->animSet = anim_sets[breakableType];
        self->unk5A = unk_5A[breakableType];
        self->palette = palettes[breakableType];
        self->hitboxOffY = hitbox_offsets_y[breakableType];
    }

    AnimateEntity(animations[breakableType], self);
    if (breakableType == 1) {
        prim = &g_PrimBuf[self->primIndex];
        if (g_Timer & 2) {
            prim->clut = PAL_BREAKABLE_TORCH_A;
        } else {
            prim->clut = PAL_BREAKABLE_TORCH_B;
        }
    }

    if (self->hitParams) {
        entity = AllocEntity(&g_Entities[224], &g_Entities[TOTAL_ENTITY_COUNT]);
        if (entity != NULL) {
            CreateEntityFromCurrentEntity(E_EXPLOSION, entity);
            entity->params = explosion_types[breakableType];
        }
        switch (breakableType) {
        case 1:
#if defined(INVERTED_STAGE)
            g_api.PlaySfx(SFX_CANDLE_HIT);
#else
            g_api.PlaySfx(SFX_FIRE_SHOT);
#endif
            break;
        case 2:
        case 3:
            self->facingLeft = GetSideToPlayer() & 1;
            posY = self->posY.i.hi - 0x28;
            if (breakableType == 2) {
                debrisCount = 4;
            } else {
                debrisCount = 3;
            }

            debrisOffsetsY = candelabra_debris_offsets_y;
            if (breakableType == 3) {
                debrisOffsetsY += 5;
            }

            for (debrisIndex = 0; debrisIndex < debrisCount; debrisIndex++) {
                entity = AllocEntity(
                    &g_Entities[224], &g_Entities[TOTAL_ENTITY_COUNT]);
                if (entity != NULL) {
                    CreateEntityFromEntity(
                        E_ID(BREAKABLE_DEBRIS), self, entity);
                    entity->posY.i.hi = posY;
                    entity->params = debrisOffsetsY[debrisIndex];
                    entity->facingLeft = self->facingLeft;
                }

                entity = AllocEntity(
                    &g_Entities[224], &g_Entities[TOTAL_ENTITY_COUNT]);
                if (entity != NULL) {
                    CreateEntityFromEntity(E_EXPLOSION, self, entity);
                    entity->posY.i.hi = posY;
                    entity->params = EXPLOSION_SMALL;
                }
                posY += 16;
            }
            g_api.PlaySfx(SFX_CANDLE_HIT);
            break;
        case 9:
            entity = AllocEntity(&g_Entities[160], &g_Entities[192]);
            if (entity != NULL) {
                CreateEntityFromCurrentEntity(E_ID(BREAKABLE_DEBRIS), entity);
                entity->params = 256;
            }
            g_api.PlaySfx(SFX_GLASS_BREAK_E);
            break;
        case 7:
            g_api.PlaySfx(SFX_GLASS_BREAK_E);
            entity = AllocEntity(&g_Entities[160], &g_Entities[192]);
            if (entity != NULL) {
                CreateEntityFromEntity(E_HEART_DROP, self, entity);
                entity->params = 0x28;
            }
            PreventEntityFromRespawning(self);
            DestroyEntity(self);
            return;
        case 8:
            g_api.PlaySfx(SFX_GLASS_BREAK_E);
            entity = AllocEntity(&g_Entities[160], &g_Entities[192]);
            if (entity != NULL) {
                CreateEntityFromEntity(E_HEART_DROP, self, entity);
                entity->params = 0x29;
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
    case 0:
        if (self->params & 512) {
#ifdef INVERTED_STAGE
            InitializeEntity(g_EInitEnvironmentBreakable);
#else
            InitializeEntity(g_EInitEnvironment);
#endif
            self->animCurFrame = 0x19;
            self->step = 256; // No case defined, resulting in nop
            return;
        }

        if (self->params & 256) {
            InitializeEntity(g_EInitInteractable);
            self->animSet = ANIMSET_OVL(10);
            self->unk5A = 91;
            self->palette = PAL_BREAKABLE;
            self->animCurFrame = 21;
            self->zPriority = 106;
            self->step = 256; // No case defined, resulting in nop
            return;
        }

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
        prim->v0 = prim->v1 = posY;
        prim->v2 = prim->v3 = posY + 15;
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
        // Fallthrough
    case 1:
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
            g_api.PlaySfx(SFX_QUICK_STUTTER_EXPLODE_B);
            explosion =
                AllocEntity(&g_Entities[224], &g_Entities[TOTAL_ENTITY_COUNT]);
            if (explosion != NULL) {
                CreateEntityFromCurrentEntity(E_EXPLOSION, explosion);
                explosion->params = EXPLOSION_SMALL;
            }
            DestroyEntity(self);
        }
        break;
    }
}
