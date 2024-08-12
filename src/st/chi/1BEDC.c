#include "chi.h"

/*
 * File: 1BEDC.c
 * Overlay: CHI
 * Description: Abandoned Mine
 */

#ifndef NON_MATCHING
INCLUDE_ASM("st/chi/nonmatchings/1BEDC", func_8019BEDC);
#else
extern u8 D_8003BE3C;
extern s32 D_8007D858[];
void* func_801AE478(Primitive*);    // FindFirstUnkPrim()
extern u16 D_8018089C;
extern u16 D_801808B4;
extern u16 g_pads_1_pressed;

typedef struct UnkStruct2 {
    s32 unk0;
    s32 unk4;
    s16 unk8;
    s16 unkA;
    s32 unkC;
    s32 unk10;
    s32 unk14;
    s32 unk18;
    s32 unk1C;
    s32 unk20;
    s32 unk24;
    s16 unk28;
    u8 unk2A;
    u8 unk2B;
} UnkStruct2;

// [Entity]
void func_8019BEDC(Entity* entity)
{
    Primitive* prim;
    s32 temp_posY;
    s16 primIdx;
    s32 var_s2;
    s32 temp_posX;
    s32 temp_v0_2;
    s32 temp_v1_4;
    s32 temp_v1_5;
    s32 i;
    s32 j;
    s32 temp2;
    s32 var_t0_2;
    s32 var_t1;
    u16* tempSrcTile;
    UnkStruct2* temp_v0_3;
    Entity* temp_entity;
    u8 temp1;
    u8 temp4;

    switch (entity->step) {
        case 0:
            entity->animCurFrame = 1;
            InitializeEntity(&EntityInit_8018067C);

            temp2 = 0x6D;
            temp1 = D_8003BE3C;
            tempSrcTile = &D_8018089C;
            if (temp1 != 0) {
                tempSrcTile = &D_8018089C + 0xC;
            }

            for (i = 0; i < 3; i++, temp2++) {
                for (j = 0; j < 4; j++, tempSrcTile++) {
                    *(&g_Tilemap.fg[temp2] + j * 16) = *tempSrcTile;
                }
            }

            if (D_8003BE3C != 0) {
                entity->animCurFrame = 0;
                entity->step = 16;
            }
            break;
        case 1:
            if (D_8003BE3C != 0) {
                entity->step++;
            }
            break;

        case 2:
            primIdx = g_api_AllocPrimitives(PRIM_TILE, 0x10);
            if (primIdx != -1) {
                prim = &g_PrimBuf[primIdx];
                entity->primIndex = primIdx;
                entity->ext.prim = prim;
                entity->flags |= FLAG_HAS_PRIMS;
                while (prim != NULL) {
                    prim->drawMode = DRAW_HIDE;
                    prim = prim->next;
                }
                entity->step++;
                break;
            }
            DestroyEntity(entity);
            return;

        case 3:
            temp_v0_2 = entity->ext.generic.unk80.modeS32 + 1;
            entity->ext.generic.unk80.modeS32 = temp_v0_2;
            if (temp_v0_2 & 1) {
                entity->posY.i.hi++;
            } else {
                entity->posY.i.hi--;
            }
            var_t1 = entity->ext.generic.unk80.modeS32 & 7;
            temp4 = var_t1;
            if (!temp4) {
                g_api_PlaySfx(NA_SE_EN_ROCK_BREAK);
            }
            MoveEntity();

            if (entity->velocityX < 0x4000) {
                entity->velocityX += 0x200;
            }

            temp_v0_3 = func_801AE478(entity->ext.prim);
            if (temp_v0_3 != NULL) {
                temp_v0_3->unk2B = 1;
                temp_v1_4 = entity->posX.i.hi + (Random() & 0x3F);

                if ((temp_v1_4 - 0x18) >= 0x101) {
                    var_s2 = temp_v1_4 - 0x28;
                }

                temp_v1_5 = (s16) entity->posY.i.hi - 0x20;
                temp_v0_3->unk8 = var_s2;
                temp_v0_3->unkA = (s16) temp_v1_5;
            }
            prim = entity->ext.prim;
            while (prim != NULL) {
                if (prim->p3 != 0) {
                    func_8019BD0C(prim);
                }
                prim = prim->next;
            }
            temp_posX = entity->posX.i.hi - 0x18;
            temp_posY = entity->posY.i.hi + 0x20;
            temp_entity = AllocEntity(D_8007D858, &D_8007D858[0x5E0]);
            if (temp_entity != NULL) {
                CreateEntityFromCurrentEntity(0x15, temp_entity);
                temp_entity->posX.i.hi = (s16) (temp_posX + (Random() & 0x1F));
                temp2 = temp_posY;
                temp_entity->posY.i.hi = temp2;
                temp_entity->params = (s16) (Random() & 3);
                temp_entity->zPriority = 0xA0;
            }
            var_t0_2 = entity->posX.i.hi - 0xE8;
            var_t1 = var_t0_2 >> 4;
            var_t0_2 = 0x6D;
            if (var_t1 >= 4) {
                var_t1 = 3;
            }
            tempSrcTile = &D_801808B4;

            for (i = 0; i < var_t1; i++, var_t0_2++) {
                for (j = 0; j < 4; j++, tempSrcTile++) {
                    *((&g_Tilemap.fg[var_t0_2]) + j * 16) = *tempSrcTile;
                }
            }

            if (entity->posX.i.hi >= 0x129) {
                DestroyEntity(entity);
            }
            break;
        case 16:
            if (g_pads_1_pressed & PAD_SQUARE && entity->params == 0) {
                entity->animCurFrame = (u16) (entity->animCurFrame + 1);
                entity->params = (u16) (entity->params | 1);
            } else {
                entity->params = 0;
            }
            if (g_pads_1_pressed & PAD_CIRCLE) {
                if (entity->step_s == 0) {
                    entity->animCurFrame--;
                    entity->step_s |= 1;
                }
            } else {
                entity->step_s = 0;
            }
            break;
    }
}
#endif

extern EntityInit EntityInit_8018067C;

// [Entity]
void func_8019C31C(Entity* entity)
{
    Collider collider;
    s32 temp_a0_2;
    s32 temp_a0_3;
    s32 temp_v1_3;
    s32 var_s2;
    u16 temp_v1;
    u16 temp_v1_2;
    u8 temp_a0;
    Entity* temp_v0;
    Entity* temp_v0_2;

    temp_v1 = entity->step;
    switch (temp_v1) {
        case 0:
            InitializeEntity(&EntityInit_8018067C);
            temp_a0 = entity->params;
            entity->drawFlags = 4;
            entity->zPriority = 0x69;
            entity->animCurFrame = (s16) temp_a0;
            if (entity->rotZ & 1) {
                entity->facingLeft = 1;
                entity->rotZ = (u16) (entity->rotZ & 0xFFF0);
            }
            temp_a0_2 = (Random() & 0xF) << 0xC;
            entity->velocityX = temp_a0_2;
            if (entity->animCurFrame == 0xD) {
                entity->velocityX = temp_a0_2 + 0x4000;
            }
            temp_a0_3 = ((Random() & 7) << 0xB) - 0x4000;
            entity->velocityY = temp_a0_3;
            if (entity->animCurFrame < 0xB) {
                entity->velocityY = temp_a0_3 + 0xFFFF0000;
            }
            //temp_a0_3 
            entity->ext.generic.unk9C.modeS16.unk0 = ((Random() & 3) + 1) * 32;
            return;
        case 1:
            temp_v1_2 = (u16) entity->params;
            if (temp_v1_2 & 0x100) {
                entity->params = (s16) (temp_v1_2 & 0xFF);
                entity->step = (u16) (entity->step + 1);
                return;
            }
            return;
        case 2:
            entity->rotZ += entity->ext.generic.unk9C.modeS16.unk0;
            MoveEntity();
            entity->velocityY = (s32) (entity->velocityY + 0x2000);
            g_api_CheckCollision((s32) entity->posX.i.hi, (s32) (s16) (entity->posY.i.hi + 6), &collider, 0);
            if (collider.effects & 1) {
                entity->posY.i.hi = (u16) (entity->posY.i.hi + (u16) collider.unk18);
                if (entity->animCurFrame >= 0xC) {
                    var_s2 = 0;
                    do {
                        temp_v0 = AllocEntity(&g_Entities[224], &g_Entities[256]);
                        var_s2 += 1;
                        if (temp_v0 != NULL) {
                            CreateEntityFromEntity(0x19, entity, temp_v0);
                            temp_v0->params = (s16) (((Random() & 3) + 9) | 0x100);
                        }
                    } while (var_s2 < 2);
                    DestroyEntity(entity);
                    return;
                }
                temp_v1_3 = entity->velocityY;
                if (temp_v1_3 <= 0x7FFF) {
                    temp_v0_2 = AllocEntity(&g_Entities[224], &g_Entities[256]);
                    if (temp_v0_2 != NULL) {
                        CreateEntityFromEntity(6, entity, temp_v0_2);
                        temp_v0_2->params = 0xC010;
                    }
                    DestroyEntity(entity);
                    return;
                }
                entity->velocityY = -temp_v1_3 * 2 / 3;
            }
            break;
    }
}
