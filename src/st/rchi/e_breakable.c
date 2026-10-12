// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rchi.h"

enum BreakableDebrisSteps {
    INIT,
    UPDATE,
};

#define BREAKABLE_ZPRIORITY 112
#define BASE_DEBRIS_COUNT 4
#define TALL_EXTRA_DEBRIS 3

#ifdef VERSION_PSP
extern s32 E_ID(BACKGROUND_BLOCK);
extern s32 E_ID(BREAKABLE_DEBRIS);
#endif

extern EInit g_EInitBreakable;

static AnimateEntityFrame anim_brazier_short[] = {
    {3, 14}, {4, 15}, {4, 16}, {4, 17},
    {4, 18}, {4, 19}, {3, 20}, POSE_LOOP(0)};
static AnimateEntityFrame anim_brazier_tall[] = {
    {3, 21}, {4, 22}, {4, 23}, {4, 24},
    {4, 25}, {4, 26}, {3, 27}, POSE_LOOP(0)};
static AnimateEntityFrame* animations[] = {
    anim_brazier_short,
    anim_brazier_tall,
};
static u8 hitbox_heights[] = {12, 20, 0, 0};
static u8 explosion_types[] = {3, 3, 0, 0};
static u16 anim_sets[] = {ANIMSET_OVL(2), ANIMSET_OVL(2)};
static u8 blend_modes[] = {
    BLEND_TRANSP | BLEND_ADD,
    BLEND_TRANSP | BLEND_ADD,
    BLEND_NO,
    BLEND_NO,
};
static s16 debris_offsets_y[] = {
    -4, -4, 3, -6, 2, 9, -4, 12, 0, 2, 0, 15, 0, 31};

void EntityBreakable(Entity* self) {
    u16 breakableType = self->params >> 12;
    Entity* entity;
    s32 i;
    s16* debrisOffsets;

    if (!self->step) {
        InitializeEntity(g_EInitBreakable);
        self->zPriority = 0x70;
        self->blendMode = blend_modes[breakableType];
        self->hitboxHeight = hitbox_heights[breakableType];
        self->animSet = anim_sets[breakableType];
        entity = self + 1;
        CreateEntityFromEntity(E_ID(BACKGROUND_BLOCK), self, entity);
        if (breakableType) {
            entity->posY.i.hi += 0x20;
        } else {
            entity->posY.i.hi += 0x10;
        }
        entity->params = 1;
    }

    AnimateEntity(animations[breakableType], self);
    if (self->hitParams) {
        g_api.PlaySfx(SFX_FIRE_SHOT);
        entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
        if (entity != NULL) {
            CreateEntityFromCurrentEntity(E_EXPLOSION, entity);
            entity->params = explosion_types[breakableType];
            entity->params |= 0x10;
        }

        debrisOffsets = debris_offsets_y;
        for (i = 0; i < 4; i++) {
            entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (entity != NULL) {
                CreateEntityFromEntity(E_ID(BREAKABLE_DEBRIS), self, entity);
                entity->posX.i.hi -= *debrisOffsets++;
                entity->posY.i.hi -= *debrisOffsets++;
                if (breakableType) {
                    entity->posY.i.hi += 0x14;
                }
                entity->params = i;
            }
        }
        if (breakableType) {
            for (i = 0; i < 3; i++) {
                entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
                if (entity != NULL) {
                    CreateEntityFromEntity(
                        E_ID(BREAKABLE_DEBRIS), self, entity);
                    entity->posX.i.hi -= *debrisOffsets++;
                    entity->posY.i.hi -= *debrisOffsets++;
                    entity->params = i + 4;
                }
            }
        }
        entity = self + 1;
        DestroyEntity(entity);
        ReplaceBreakableWithItemDrop(self);
    }
}

// params: Index of breakable debris to use
//         (>= 4) Considered a "tall" breakable debris
//         (== 6) The "last standing" debris, that doesn't move
void EntityBreakableDebris(Entity* self) {
    Entity* entity;
    Collider collider;
    Primitive* prim;
    u32 primIndex;
    s32 facingLeft;
    u32 posX;
    u32 posY;

    switch (self->step) {
    case INIT:
        InitializeEntity(g_EInitBreakable);
        self->animSet = ANIMSET_OVL(2);
        self->hitboxState = 0;
        self->zPriority = BREAKABLE_ZPRIORITY;
        self->drawFlags = ENTITY_ROTATE;
        self->animCurFrame = self->params + 28;
        facingLeft = GetSideToPlayer() & 1;

        self->ext.breakableDebris.angle = (Random() & 30) + 8;
        if (self->facingLeft) {
            self->ext.breakableDebris.angle = -self->ext.breakableDebris.angle;
        }

        if (self->params > BASE_DEBRIS_COUNT - 1) {
            self->ext.breakableDebris.angle = -self->ext.breakableDebris.angle;
        }

        if (facingLeft) {
            self->velocityX = FIX(1);
        } else {
            self->velocityX = FIX(-1);
        }

        self->velocityX += FIX(0.5) - (Random() << 8);
        self->velocityY = FIX(-2.25);
        self->velocityY += (self->params >> 1) * FIX(0.375);

        // "Last standing" debris just sits there (tall breakables only)
        if (self->params == 6) {
            self->velocityX = 0;
            self->velocityY = 0;
            self->step = 2;
        }

        self->primIndex = 0;
        if (!self->params) {
            primIndex = g_api.AllocPrimitives(PRIM_GT4, 2);
            if (primIndex != -1) {
                self->flags |= FLAG_HAS_PRIMS;
                self->primIndex = primIndex;
                prim = &g_PrimBuf[primIndex];

                UnkPolyFunc2(prim);

                prim->tpage = 26;
                prim->clut = PAL_BREAKABLE_DEBRIS;
                prim->u0 = prim->u2 = 64;
                prim->u1 = prim->u3 = 96;
                prim->v0 = prim->v1 = 0;
                prim->v2 = prim->v3 = 32;

                prim->next->x1 = self->posX.i.hi - 4;
                prim->next->y0 = self->posY.i.hi + 8;
                LOH(prim->next->r2) = 32;
                LOH(prim->next->b2) = 32;
                prim->next->b3 = 16;

                prim->priority = BREAKABLE_ZPRIORITY + 2;
                prim->drawMode = DRAW_TRANSP | DRAW_UNK02 | DRAW_COLORS |
                                 DRAW_TPAGE | DRAW_TPAGE2;
            } else {
                DestroyEntity(self);
            }
        }
        break;

    case UPDATE:
        MoveEntity();
        self->rotate += self->ext.breakableDebris.angle;
        self->velocityY += FIX(0.25);
        posX = self->posX.i.hi;
        posY = self->posY.i.hi + 6;
        g_api.CheckCollision(posX, posY, &collider, 0);
        if (collider.effects & EFFECT_SOLID) {
            self->posY.i.hi += collider.unk18;
            self->velocityY = -self->velocityY / 2;
            self->velocityX -= self->velocityX / 3;
            if (self->velocityY > FIX(-0.625)) {
                entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
                if (entity != NULL) {
                    CreateEntityFromEntity(E_INTENSE_EXPLOSION, self, entity);
                    entity->params = 16;
                }
                DestroyEntity(self);
                break;
            }
        }

        if (self->primIndex != 0) {
            prim = &g_PrimBuf[self->primIndex];
            UnkPrimHelper(prim);
            LOH(prim->next->r2) = LOH(prim->next->b2) += 4;
            if (LOH(prim->next->r2) > 64) {
                prim->next->b3 -= 4;
                if (!prim->next->b3) {
                    g_api.FreePrimitives(self->primIndex);
                    self->flags &= ~FLAG_HAS_PRIMS;
                    self->primIndex = 0;
                }
            }
        }
        break;
    }
}
