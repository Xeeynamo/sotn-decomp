// SPDX-License-Identifier: AGPL-3.0-or-later
#include "st0.h"
#include "sfx.h"

extern ObjInit OVL_EXPORT(BackgroundBlockInit)[];
extern u16 g_EInitCommon[];
// void func_801A7D64(Entity* self) {
void OVL_EXPORT(EntityBackgroundBlock)(Entity* self) {
    ObjInit* obj = &OVL_EXPORT(BackgroundBlockInit)[self->params];
    if (!self->step) {
        InitializeEntity(g_EInitCommon);
        self->animSet = obj->animSet;
        self->zPriority = obj->zPriority;
        self->unk5A = obj->unk5A;
        self->palette = obj->palette;
        self->drawFlags = obj->drawFlags;
        self->drawMode = obj->drawMode;
        if (obj->unkC != 0) {
            self->flags = obj->unkC;
        }
    }
    AnimateEntity(obj->animFrames, self);
}

#include "../player_is_within_hitbox.h"

extern u16 D_801805B0[];
static u8 D_8018065C[] = {32, 0};
static u8 D_80180660[] = {0, 0};
static u16 D_80180664[] = {
    0x0000, 0x0000, 0x0500, 0x0200, // 0
    0x0000, 0x0000, 0x0500, 0x0100, // 1
};
void EntityLockCamera(Entity* self) {
    s32 facingLeft;
    u16 offset;
    u16* rect16;
    u16 params;
    u8 flag;

    params = (u8)self->params;
    if (self->step == 0) {
        InitializeEntity(D_801805B0);

        self->hitboxState = 1;

        flag = D_80180660[params];
        self->ext.lockCamera.unk7C = flag;

        if (flag) {
            self->hitboxWidth = D_8018065C[params];
            self->hitboxHeight = 20;
        } else {
            self->hitboxWidth = 20;
            self->hitboxHeight = D_8018065C[params];
        }
    }

    if (self->params & 0x100) {
        params *= 4;
        rect16 = &D_80180664[params];
        g_Tilemap.x = *rect16++;
        g_Tilemap.y = *rect16++;
        g_Tilemap.width = *rect16++;
        g_Tilemap.height = *rect16++;
        DestroyEntity(self);
        return;
    }

    if (PlayerIsWithinHitbox(self) != 0) {
        facingLeft = GetSideToPlayer();
        if (self->ext.lockCamera.unk7C) {
            facingLeft &= 2;
            offset = facingLeft * 2;
        } else {
            facingLeft &= 1;
            offset = facingLeft * 4;
        }
        params <<= 3;
        params += offset;
        rect16 = &D_80180664[params];
        g_Tilemap.x = *rect16++;
        g_Tilemap.y = *rect16++;
        g_Tilemap.width = *rect16++;
        g_Tilemap.height = *rect16++;
    }
}

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
static u16 palette[] = {0x0100, 0x0100, 0x0212, 0x0212, 0x0212,
                        0x0212, 0x0212, 0x0212, 0x0212, 0x0212};
static s16 animset[] = {
    ANIMSET_OVL(3), ANIMSET_OVL(3), ANIMSET_OVL(4), ANIMSET_OVL(4),
    ANIMSET_OVL(4), ANIMSET_OVL(4), ANIMSET_OVL(4), ANIMSET_OVL(4),
    ANIMSET_OVL(4), ANIMSET_OVL(4)};
static s16 D_80180738[] = {0x007C, 0x007C, 0x005B, 0x005B, 0x005B,
                           0x005B, 0x005B, 0x005B, 0x005B, 0x005B};
static s8 draw_mode[] = {
    0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30};
static s16 hitbox_y[] = {0, 0, -24, -16, 0, 0, 0, 0, 0, 0, 0, 0};
static u16 D_80180770[][5] = {{0, 1, 2, 2, 3}, {0, 1, 2, 3, 0}};
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
        AnimateEntity(anims_801A805C[params], self);
        if (self->hitParams) {
            params_ = params - 2;
            if (params_ < 2) {
                self->facingLeft = GetSideToPlayer() & 1;
                posY = self->posY.i.hi - 40;

                if (params == 2) {
                    entityCount = 4;
                } else {
                    entityCount = 3;
                }

                if (params == 3) {
                    temp = D_80180770[1];
                } else {
                    temp = D_80180770[0];
                }

                for (i = 0, paramsPtr = temp; i < entityCount; i++) {
                    newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
                    if (newEntity != NULL) {
                        CreateEntityFromEntity(E_ID_26, self, newEntity);
                        newEntity->posY.i.hi = posY;
                        newEntity->params = *paramsPtr;
                        newEntity->facingLeft = self->facingLeft;
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
                g_api.PlaySfx(SFX_CANDLE_HIT_WHOOSH_B);
            } else {
                if (params == 9) {
                    newEntity = AllocEntity(&g_Entities[160], &g_Entities[192]);
                    if (newEntity != NULL) {
                        CreateEntityFromCurrentEntity(E_ID_26, newEntity);
                        newEntity->params = 0x100;
                    }
                }
                g_api.PlaySfx(SFX_GLASS_BREAK_E);
            }
            newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (newEntity != NULL) {
                CreateEntityFromCurrentEntity(E_EXPLOSION, newEntity);
                newEntity->params = explosion_params[params];
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

        InitializeEntity(g_EInitParticle);
        firstPrimIndex = g_api.AllocPrimitives(PRIM_GT4, 2);
        if (firstPrimIndex != -1) {
            prim = &g_PrimBuf[firstPrimIndex];
            self->primIndex = firstPrimIndex;
            self->ext.prim = prim;
            self->flags |= FLAG_HAS_PRIMS;
            UnkPolyFunc2(prim);
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
            prim->drawMode = DRAW_UNK02;
            velX = ((Random() & 7) << 0xC) + 0x8000;
            self->velocityX = velX;
            if (self->facingLeft == 0) {
                self->velocityX = -velX;
            }
            self->velocityY = ((Random() & 7) << 0xC) - 0x8000;
        } else {
            DestroyEntity(self);
            break;
        }

    case 1:
        MoveEntity();

        prim = self->ext.prim;
        self->velocityY += FIX(0.125);
        prim->next->x1 = self->posX.i.hi;
        prim->next->y0 = self->posY.i.hi;

        if (self->facingLeft != 0) {
            prim->next->tpage += 0x10;
        } else {
            prim->next->tpage -= 0x10;
        }

        UnkPrimHelper(prim);

        g_api.CheckCollision(
            self->posX.i.hi, (s16)(self->posY.i.hi + 8), &collider, 0);
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
