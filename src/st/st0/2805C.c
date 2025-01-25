// SPDX-License-Identifier: AGPL-3.0-or-later
#include "st0.h"
#include "sfx.h"

static u8 D_80180674[] = {0x04, 0x13, 0x04, 0x14, 0x00};
static u8 D_8018067C[] = {0x04, 0x15, 0x04, 0x16, 0x04, 0x17, 0x00};
static u8 D_80180684[] = {0x05, 0x01, 0x05, 0x02, 0x05, 0x03, 0x05, 0x04, 0x00};
static u8 D_80180690[] = {0x05, 0x05, 0x05, 0x06, 0x05, 0x07, 0x05, 0x08, 0x00};
static u8 D_8018069C[] = {0x05, 0x09, 0x05, 0x0A, 0x05, 0x0B, 0x05, 0x0C, 0x00};
static u8 D_801806A8[] = {0x05, 0x0D, 0x05, 0x0E, 0x05, 0x0F, 0x05, 0x10, 0x00};
static u8 D_801806B4[] = {0x05, 0x11, 0x05, 0x12, 0x05, 0x13, 0x00};
static u8 D_801806BC[] = {0x05, 0x17, 0x00};
static u8 D_801806C0[] = {0x05, 0x16, 0x00};
static u8 D_801806C4[] = {
    0x05, 0x14, 0xFF, 0xFF, 0x05, 0x15, 0x05, 0x15, 0xFF, 0x00};
static u8* anims_801A805C[] = {
    D_80180674, D_8018067C, D_80180684, D_80180690, D_8018069C,
    D_801806A8, D_801806B4, D_801806BC, D_801806C0, D_801806C4};
static u8 hitbox_height[] = {8, 8, 40, 24, 16, 16, 8, 8, 8, 8, 8};
static u8 explosion_params[] = {0, 0, 2, 2, 2, 2, 2, 2, 2, 2};
static u16 palette[] = {
    PAL_DRA(0x100), PAL_DRA(0x100), PAL_DRA(0x212), PAL_DRA(0x212),
    PAL_DRA(0x212), PAL_DRA(0x212), PAL_DRA(0x212), PAL_DRA(0x212),
    PAL_DRA(0x212), PAL_DRA(0x212)};
static u16 animset[] = {
    ANIMSET_OVL(3), ANIMSET_OVL(3), ANIMSET_OVL(4), ANIMSET_OVL(4),
    ANIMSET_OVL(4), ANIMSET_OVL(4), ANIMSET_OVL(4), ANIMSET_OVL(4),
    ANIMSET_OVL(4), ANIMSET_OVL(4)};
static u16 D_80180738[] = {0x007C, 0x007C, 0x005B, 0x005B, 0x005B,
                           0x005B, 0x005B, 0x005B, 0x005B, 0x005B};
static u8 draw_mode[] = {
    DRAW_TPAGE | DRAW_TPAGE2, DRAW_TPAGE | DRAW_TPAGE2,
    DRAW_TPAGE | DRAW_TPAGE2, DRAW_TPAGE | DRAW_TPAGE2,
    DRAW_TPAGE | DRAW_TPAGE2, DRAW_TPAGE | DRAW_TPAGE2,
    DRAW_TPAGE | DRAW_TPAGE2, DRAW_TPAGE | DRAW_TPAGE2,
    DRAW_TPAGE | DRAW_TPAGE2, DRAW_TPAGE | DRAW_TPAGE2};
static u16 hitbox_y[] = {0, 0, 0xFFE8, 0xFFF0, 0, 0, 0, 0, 0, 0, 0, 0};
static s16 D_80180770[][5] = {{0, 1, 2, 2, 3}, {0, 1, 2, 3, 0}};
void func_801A805C(Entity* self) {
    s16* paramsPtr;
    Entity* newEntity;
    Entity* entityTwo;
    s32 i;
    s32 entityCount;
    s16 posY;
    u16 params = self->params >> 0xC;

    if (self->step) {
        AnimateEntity(anims_801A805C[params], self);
        if (self->hitParams) {
            if (params == 2 || params == 3) {
                self->facingLeft = GetSideToPlayer() & 1;
                posY = self->posY.i.hi - 40;

                if (params == 2) {
                    entityCount = 4;
                } else {
                    entityCount = 3;
                }

                paramsPtr = D_80180770[0];
                if (params == 3) {
                    paramsPtr += 5;
                }

                for (i = 0; i < entityCount; i++) {
                    newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
                    if (newEntity != NULL) {
                        CreateEntityFromEntity(E_ID_26, self, newEntity);
                        newEntity->posY.i.hi = posY;
                        newEntity->params = paramsPtr[i];
                        newEntity->facingLeft = self->facingLeft;
                    }
                    newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
                    if (newEntity != NULL) {
                        CreateEntityFromEntity(E_EXPLOSION, self, newEntity);
                        newEntity->posY.i.hi = posY;
                        newEntity->params = 0;
                    }
                    posY += 16;
                }
                g_api.PlaySfx(SFX_CANDLE_HIT_WHOOSH_B);
            } else if (params == 9) {
                entityTwo = AllocEntity(&g_Entities[160], &g_Entities[192]);
                if (entityTwo != NULL) {
                    CreateEntityFromCurrentEntity(E_ID_26, entityTwo);
                    entityTwo->params = 0x100;
                }
                g_api.PlaySfx(SFX_GLASS_BREAK_E);
            } else {
                g_api.PlaySfx(SFX_GLASS_BREAK_E);
            }

            entityTwo = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (entityTwo != NULL) {
                CreateEntityFromCurrentEntity(E_EXPLOSION, entityTwo);
                entityTwo->params = explosion_params[params];
            }
            ReplaceBreakableWithItemDrop(self);
        }
    } else {
        InitializeEntity(OVL_EXPORT(EInitBreakable));
        self->zPriority = g_unkGraphicsStruct.g_zEntityCenter - 0x14;
        self->drawMode = draw_mode[params];
        self->hitboxHeight = hitbox_height[params];
        self->animSet = animset[params];
        self->unk5A = D_80180738[params];
        self->palette = palette[params];
        self->hitboxOffY = hitbox_y[params];
    }
}

// Entity ID: 0x26
void func_801A8328(Entity* self) {
    Entity* newEntity;
    Primitive* prim;
    Collider collider;
    s32 primIndex;
    s16 posX;
    s16 posY; // reused for prim->v0-3

    switch (self->step) {
    case 0:
        if (self->params & 0x100) {
            InitializeEntity(g_EInit3DObject);
            self->animSet = ANIMSET_OVL(4);
            self->unk5A = 0x5B;
            self->palette = 0x212;
            self->animCurFrame = 0x15;
            self->zPriority = 0x6A;
            self->step = 256;
            break;
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
        self->ext.prim = prim;
        UnkPolyFunc2(prim);
        prim->tpage = 0x16;
        prim->clut = 0x216;
        prim->u0 = prim->u2 = 0x98;
        prim->u1 = prim->u3 = 0xA7;
        posY = 0x84;
        posY += (self->params * 16);
        prim->v0 = prim->v1 = posY;
        prim->v2 = prim->v3 = posY + 15;

        prim->next->x1 = self->posX.i.hi;
        prim->next->y0 = self->posY.i.hi;
        LOH(prim->next->r2) = 0x10;
        LOH(prim->next->b2) = 0x10;
        prim->next->b3 = 0x80;
        prim->priority = self->zPriority;
        prim->drawMode = DRAW_UNK02;
        self->velocityX = ((Random() & 7) << 0xC) + 0x8000;
        if (!self->facingLeft) {
            self->velocityX = -self->velocityX;
        }
        self->velocityY = ((Random() & 7) << 0xC) - 0x8000;
        // fallthrough
    case 1:
        MoveEntity();
        self->velocityY += FIX(0.125);
        prim = self->ext.prim;
        prim->next->x1 = self->posX.i.hi;
        prim->next->y0 = self->posY.i.hi;

        if (self->facingLeft) {
            LOH(prim->next->tpage) += 0x10;
        } else {
            LOH(prim->next->tpage) -= 0x10;
        }

        UnkPrimHelper(prim);

        posX = self->posX.i.hi;
        posY = self->posY.i.hi + 8;
        g_api.CheckCollision(posX, posY, &collider, 0);
        if (collider.effects & EFFECT_SOLID) {
            g_api.PlaySfx(SFX_SMALL_FLAME_IGNITE);
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
    FntPrint("sx:%04x\n", g_Tilemap.left);
    FntPrint("ex:%04x\n", g_Tilemap.right);

    switch (entity->step) {
    case 0:
        InitializeEntity(g_EInitCommon);
        entity->animSet = ANIMSET_DRA(2);
        entity->animCurFrame = 1;
        entity->zPriority = 0xB0;
        break;

    case 1:
        dist = entity->posY.i.hi - PLAYER.posY.i.hi;
        dist = abs(dist);

        if (dist < 0x20) {
            switch (params) {
            case 0:
                if (g_PlayerX > 0x280) {
                    g_Tilemap.width = 0x280;
                    g_Tilemap.right--;
                    entity->step++;
                }
                break;

            case 1:
                if (g_PlayerX < 0x180) {
                    g_Tilemap.x = 0x180;
                    g_Tilemap.left++;
                    entity->step++;
                }
                break;

            case 3:
                if (g_PlayerX < 0x100) {
                    g_Tilemap.x = 0x100;
                    g_Tilemap.left++;
                    entity->step++;
                }
                break;

            case 5:
                if (g_PlayerX < 0x80) {
                    g_Tilemap.x = 0x80;
                    entity->step++;
                }
                break;

            case 6:
                if (g_PlayerX > 0x480) {
                    g_Tilemap.width = 0x480;
                    entity->step++;
                }
                break;

            case 7:
                if (g_PlayerX > 0x480) {
                    g_Tilemap.width = 0x480;
                    entity->step++;
                }
                break;

            case 8:
                if (g_PlayerX < 0x80) {
                    g_Tilemap.x = 0x80;
                    entity->step++;
                }
                break;

            case 9:
                if (g_PlayerX > 0x280) {
                    g_Tilemap.width = 0x280;
                    entity->step++;
                }
                break;

            case 10:
                if (g_PlayerX < 0x180) {
                    g_Tilemap.x = 0x180;
                    g_Tilemap.left++;
                    entity->step++;
                }
                break;

            case 11:
                if (g_PlayerX > 0x280) {
                    g_Tilemap.width = 0x280;
                    g_Tilemap.right--;
                    entity->step++;
                }
                break;

            case 12:
                if (g_PlayerX < 0x180) {
                    g_Tilemap.x = 0x180;
                    g_Tilemap.left++;
                    entity->step++;
                }
                break;

            case 2:
            case 4:
            case 13:
            case 14:
                if (g_PlayerX > 0x300) {
                    g_Tilemap.width = 0x300;
                    g_Tilemap.right--;
                    entity->step++;
                }
                break;
            }
        }
        break;
    }
}
