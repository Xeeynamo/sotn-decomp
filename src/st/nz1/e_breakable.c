// SPDX-License-Identifier: AGPL-3.0-or-later
#include "nz1.h"

enum BreakableTypes {
    CANDELABRA_WALL_DOUBLE,
    WALL_SCONCE_FLAME,
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

#ifdef VERSION_PSP
extern s32 E_ID(BREAKABLE_DEBRIS);
#endif

extern EInit OVL_EXPORT(EInitBreakable);
extern EInit g_EInitInteractable;
extern EInit g_EInitParticle;

static AnimateEntityFrame anim_candelabra_wall_double[] = {
    {4, 1}, {4, 2}, POSE_LOOP(0)};
static AnimateEntityFrame anim_wall_sconce_flame[] = {
    {4, 14}, {4, 15}, {4, 16}, {4, 17}, POSE_LOOP(0)};
static AnimateEntityFrame anim_candelabra_tall[] = {
    {5, 1}, {5, 2}, {5, 3}, {5, 4}, POSE_LOOP(0)};
static AnimateEntityFrame anim_candelabra_short[] = {
    {5, 5}, {5, 6}, {5, 7}, {5, 8}, POSE_LOOP(0)};
static AnimateEntityFrame anim_candelabra_table[] = {
    {5, 9}, {5, 10}, {5, 11}, {5, 12}, POSE_LOOP(0)};
static AnimateEntityFrame anim_brazier[] = {
    {5, 13}, {5, 14}, {5, 15}, {5, 16}, POSE_LOOP(0)};
static AnimateEntityFrame anim_candelabra_wall_triple[] = {
    {5, 17}, {5, 18}, {5, 19}, POSE_LOOP(0)};
static AnimateEntityFrame anim_urn[] = {{5, 23}, POSE_LOOP(0)};
static AnimateEntityFrame anim_jug[] = {{5, 22}, POSE_LOOP(0)};
static AnimateEntityFrame anim_bust[] = {
    {5, 20}, {-1, -1}, {5, 21}, {5, 21}, POSE_END};
static AnimateEntityFrame* animations[] = {
    anim_candelabra_wall_double,
    anim_wall_sconce_flame,
    anim_candelabra_tall,
    anim_candelabra_short,
    anim_candelabra_table,
    anim_brazier,
    anim_candelabra_wall_triple,
    anim_urn,
    anim_jug,
    anim_bust,
};

static u8 hitbox_heights[] = {8, 8, 40, 24, 16, 16, 8, 8, 8, 8, 8, 0};
static u8 explosion_types[] = {
    EXPLOSION_SMALL,          EXPLOSION_SMALL,
    EXPLOSION_SMALL_MULTIPLE, EXPLOSION_SMALL_MULTIPLE,
    EXPLOSION_SMALL_MULTIPLE, EXPLOSION_SMALL_MULTIPLE,
    EXPLOSION_SMALL,          EXPLOSION_SMALL_MULTIPLE,
    EXPLOSION_SMALL_MULTIPLE, EXPLOSION_SMALL_MULTIPLE,
};
static u16 palettes[] = {
    PAL_NONE, 0x226, 0x22A, 0x22A, 0x22A, 0x22A, 0x22A, 0x22A, 0x22A, 0x22A,
};
static u16 anim_sets[] = {
    ANIMSET_DRA(3),  ANIMSET_OVL(9),  ANIMSET_OVL(10), ANIMSET_OVL(10),
    ANIMSET_OVL(10), ANIMSET_OVL(10), ANIMSET_OVL(10), ANIMSET_OVL(10),
    ANIMSET_OVL(10), ANIMSET_OVL(10),
};
static u16 unk_5A[] = {0, 87, 91, 91, 91, 91, 91, 91, 91, 91};
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
static u16 hitbox_offsets_y[] = {0, 0, -24, -16, 0, 0, 0, 0, 0, 0, 0, 0};

// The first 5 elements are used with the tall candelabra and the last 5 are
// used with the short candelabra
static s16 candelabra_debris_offsets_y[] = {0, 1, 2, 2, 3, 0, 1, 2, 3, 0};

void OVL_EXPORT(EntityBreakable)(Entity* self) {
    Entity* entity;
    Primitive* prim;
    s16* debrisOffsetsY;
    s16 primIndex;
    u16 breakableType;
    s32 debrisIndex;
    s32 debrisCount;
    s16 posX, posY;

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

        if (breakableType == WALL_SCONCE_FLAME) {
            self->primIndex = g_api.AllocPrimitives(PRIM_GT4, 1);
            if (self->primIndex == -1) {
                DestroyEntity(self);
                return;
            }
            self->flags |= FLAG_HAS_PRIMS;
            prim = &g_PrimBuf[self->primIndex];
            prim->tpage = 21;
            prim->u0 = prim->u2 = 200;
            prim->u1 = prim->u3 = 248;
            prim->v0 = prim->v1 = 128;
            prim->v2 = prim->v3 = 160;
            // These are equivalent to the -23, but pspeu doesn't like
            // subtraction here
            prim->x0 = prim->x2 = self->posX.i.hi + 0xFFE9;
            prim->x1 = prim->x3 = prim->x0 + 48;
            prim->y0 = prim->y1 = self->posY.i.hi + 0xFFE9;
            prim->y2 = prim->y3 = prim->y0 + 32;
            prim->priority = self->zPriority;
            prim->drawMode = DRAW_UNK_40 | DRAW_TPAGE2 | DRAW_TPAGE |
                             DRAW_UNK02 | DRAW_TRANSP;
        }
    }
    AnimateEntity(animations[breakableType], self);
    if (breakableType == WALL_SCONCE_FLAME) {
        prim = &g_PrimBuf[self->primIndex];
        if (g_Timer & 2) {
            prim->clut = PAL_WALL_CANDELABRA_A;
        } else {
            prim->clut = PAL_WALL_CANDELABRA_B;
        }
    }
    if (self->hitParams) {
        entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
        if (entity != NULL) {
            CreateEntityFromCurrentEntity(E_EXPLOSION, entity);
            entity->params = explosion_types[breakableType];
        }
        switch (breakableType) {
        case WALL_SCONCE_FLAME:
            g_api.FreePrimitives(self->primIndex);
            self->flags &= ~FLAG_HAS_PRIMS;
            break;
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
            g_api.PlaySfx(SFX_CANDLE_HIT);
            break;
        case BUST:
            entity = AllocEntity(&g_Entities[160], &g_Entities[192]);
            if (entity != NULL) {
                CreateEntityFromCurrentEntity(E_ID(BREAKABLE_DEBRIS), entity);
                entity->params = 256;
            }
            g_api.PlaySfx(SFX_GLASS_BREAK_E);
            break;
        case URN:
            g_api.PlaySfx(SFX_GLASS_BREAK_E);
            entity = AllocEntity(&g_Entities[160], &g_Entities[192]);
            if (entity != NULL) {
                CreateEntityFromEntity(E_HEART_DROP, self, entity);
                entity->params = 0x28;
            }
            PreventEntityFromRespawning(self);
            DestroyEntity(self);
            return;
        case JUG:
            g_api.PlaySfx(SFX_GLASS_BREAK_E);
            entity = AllocEntity(&g_Entities[160], &g_Entities[192]);
            if (entity != NULL) {
                CreateEntityFromEntity(E_HEART_DROP, self, entity);
                entity->params = 0x29; // item drop index
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
            self->animSet = ANIMSET_OVL(10);
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
            g_api.PlaySfx(SFX_QUICK_STUTTER_EXPLODE_B);
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
