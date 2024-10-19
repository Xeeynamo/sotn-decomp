/*
 * File: 1B3FC.c
 * Overlay: CHI
 * Description: Abandoned Mine
 */

#include "chi.h"

extern s32 g_eInitGeneric2;
extern ObjInit2 ObjInit2_80180740[];

// func_8019B3FC: [E_BACKGROUND_BLOCK] EntityBackgroundBlock
void EntityBackgroundBlock(Entity* entity) {
    ObjInit2* objInit = &ObjInit2_80180740[entity->params];
    if (entity->step == 0) {
        InitializeEntity(&g_eInitGeneric2);
        entity->animSet = objInit->animSet;
        entity->zPriority = objInit->zPriority;
        entity->unk5A = objInit->unk4.u;
        entity->palette = objInit->palette;
        entity->drawFlags = objInit->drawFlags;
        entity->drawMode = objInit->drawMode;
        if (objInit->unkC != 0) {
            entity->flags = objInit->unkC;
        }
        if (entity->params == 1) {
            entity->rotY = 0x200;
            entity->rotX = 0x200;
        }
    }
    AnimateEntity(objInit->unk10, entity);
}

extern u16 EntityInit_80180658;
extern u8 D_80180798[];     // Trigger long dimension size
extern u8 D_801807A0[];     // Trigger long dimension is horizontal
extern u16 D_801807A8[];

// E_TRIGGER_VOLUME
// func_8019B4DC
void EntityTriggerVolume(Entity* entity) {
    s32 temp_v0;
    u16* temp_v0_2;
    u16 temp_s1 = entity->params;
    u16 var_v1;
    u16 unk;

    entity->unk6D[0] = 0;

    if (entity->step != 0) {
        switch (temp_s1) {
        case 4:
        case 5:
            if (g_Tilemap.x != 0) {
                return;
            }
            break;

        case 6:
            if (g_pads->pressed & PAD_TRIANGLE) {
                g_Tilemap.x = 0;
                g_Tilemap.width = 1280;
                entity->step++;
                return;
            }
            break;
        }

        if (entity->unk44 != 0) {
            temp_v0 = GetSideToPlayer();
            var_v1 = entity->ext.generic.unk7C.s;
            if (var_v1 != 0) {
                var_v1 = (temp_v0 & 2) * 2;
            } else {
                var_v1 = (temp_v0 & 1) * 4;
            }
            unk = 8;
            temp_s1 = (temp_s1 * unk) + var_v1;
            temp_v0_2 = &D_801807A8[temp_s1];
            g_Tilemap.x = *(temp_v0_2++);
            g_Tilemap.y = *(temp_v0_2++);
            g_Tilemap.width = *(temp_v0_2++);
            g_Tilemap.height = *(temp_v0_2++);
        }
    } else {
        InitializeEntity(&EntityInit_80180658);
        entity->ext.generic.unk7C.s = D_801807A0[temp_s1];
        if (entity->ext.generic.unk7C.s != 0) {
            entity->hitboxWidth = D_80180798[temp_s1];
            entity->hitboxHeight = 16;
        } else {
            entity->hitboxWidth = 16;
            entity->hitboxHeight = D_80180798[temp_s1];
        }
    }
}

extern s32 D_8007D858[];
extern s32 EntityInit_80180610;
extern s32 D_80180838[];    // Candle anim frames
extern u8 D_80180858[];     // Candle hitbox height
extern u8 D_80180860[];     // Candle death E_EXPLOSION params
extern u16 D_80180868[];    // Candle anim set
extern u8 D_80180878[];     // Candle draw mode
extern u16 D_80180880;      // Candle death particles spawn offset

// E_BREAKABLE
// func_8019B698
void EntityBreakable(Entity* entity) {
    u16* ptr;
    s32 i;
    u16 params = entity->params >> 0xC;
    Entity* newEntity;

    if (entity->step == 0) {
        InitializeEntity(&EntityInit_80180610);
        entity->zPriority = 0x70;
        entity->drawMode = D_80180878[params];
        newEntity = &entity[1];
        entity->hitboxHeight = D_80180858[params];
        entity->animSet = D_80180868[params];
        DestroyEntity(newEntity);
        CreateEntityFromEntity(E_BACKGROUND_BLOCK, entity, newEntity);
        if (params != 0) {
            entity[1].posY.i.hi -= 32;
        } else {
            entity[1].posY.i.hi -= 16;
        }
        newEntity->params = 1;
    }

    AnimateEntity(D_80180838[params], entity);

    if (entity->unk44 != 0) {
        g_api_PlaySfx(SFX_WEAPON_62C);
        newEntity = AllocEntity(&D_8007D858[0], &D_8007D858[0x5E0]);
        if (newEntity != NULL) {
            CreateEntityFromCurrentEntity(E_EXPLOSION, newEntity);
            newEntity->params = D_80180860[params] | 0x10;
        }

        for (ptr = &D_80180880, i = 0; i < 4; i++) {
            newEntity = AllocEntity(&D_8007D858[0], &D_8007D858[0x5E0]);
            if (newEntity != NULL) {
                CreateEntityFromEntity(E_BREAKABLE_DEBRIS, entity, newEntity);
                newEntity->posX.i.hi += *ptr++;
                newEntity->posY.i.hi += *ptr++;
                if (params != 0) {
                    newEntity->posY.i.hi -= 20;
                }
                newEntity->params = i;
            }
        }

        if (params != 0) {
            for (i = 0; i < 3; i++) {
                newEntity = AllocEntity(&D_8007D858[0], &D_8007D858[0x5E0]);
                if (newEntity != NULL) {
                    CreateEntityFromEntity(E_BREAKABLE_DEBRIS, entity, newEntity);
                    newEntity->posX.i.hi += *ptr++;
                    newEntity->posY.i.hi += *ptr++;
                    newEntity->params = i + 4;
                }
            }
        }
        DestroyEntity(&entity[1]);
        ReplaceBreakableWithItemDrop(entity);
    }
}

// [Duplicate of CEN.func_8018DB18]
// E_BREAKABLE_DEBRIS
// func_8019B914
void EntityBreakableDebris(Entity* entity) {
    Collider collider;
    Primitive* prim;
    s16 primIndex;
    s32 facing;
    s32 temp_v0_2;
    u16 temp_v0;
    u16 temp_v0_5;
    Entity* newEntity;
    s32 temp;

    switch (entity->step) {
    case 0:
        InitializeEntity(&EntityInit_80180610);
        entity->zPriority = 0x70;
        entity->hitboxState = 0;
        entity->drawFlags = FLAG_DRAW_ROTZ;
        entity->animCurFrame = entity->params + 28;
        facing = GetSideToPlayer() & 1;

        temp_v0 = (Random() & 0x1E) + 8;
        entity->ext.generic.unk80.modeS16.unk0 = temp_v0;
        if (entity->facingLeft != 0) {
            entity->ext.generic.unk80.modeS16.unk0 = -temp_v0;
        }

        if (entity->params >= 4) {
            entity->ext.generic.unk80.modeS16.unk0 = -entity->ext.generic.unk80.modeS16.unk0;
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
                prim->drawMode = 0x37;
            }
        }
        break;
    case 1:
        MoveEntity();
        entity->rotZ += entity->ext.generic.unk80.modeS16.unk0;
        entity->velocityY += FIX(0.25);
        g_api.CheckCollision(entity->posX.i.hi, entity->posY.i.hi + 6, &collider, 0);
        if (collider.effects & 1) {
            entity->posY.i.hi += collider.unk18;
            entity->velocityY = -entity->velocityY / 2;
            entity->velocityX -= entity->velocityX / 3;
            if (entity->velocityY > FIX(-0.625)) {
                newEntity = AllocEntity(&D_8007D858[0], &D_8007D858[0x5E0]);
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