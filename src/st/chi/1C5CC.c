#include "chi.h"

/*
 * File: 1C5CC.c
 * Overlay: CHI
 * Description: Abandoned Mine
 */

extern EntityInit EntityInit_8018067C;
extern u16 Room5_BreakableWallTilesCollision[];
extern u16 Room5_BreakableRoomEntityData[];

// [Entity] Room 5, Middle/Bottom, Breakable Wall
void EntityBreakableWall(Entity* self)
{
    const int WallWidthTiles = 3;
    const int WallHeightTiles = 4;
    const int WallTotalTiles = WallWidthTiles * WallHeightTiles;
    const int ResetTime = 20;
    //TODO: Defined elsewhere?
    const int RoomWidthTiles = 16;

    const int startTileIdx = 0x160;

    enum Step {
        Init = 0,
        Idle = 1,
        Break_1 = 2,    // Dynamically calculated, never set directly
        Break_2 = 3,    // Dynamically calculated, never set directly
        Break_3 = 4,    // Dynamically calculated, never set directly
        WaitForReset = 8,
    };

    s32 xPos; //s6
    s32 yPos; //s7
    s32 newPrimIdx; //s8
    s32 b; //s0
    s32 c; //s5
    s32 tileIdx; //s4
    s16* pSrcTile; //s1
    Primitive* prim;
    Entity* entity;
    
    switch (self->step) {
        case Init:
            InitializeEntity(&EntityInit_8018067C);
            self->animCurFrame = 2;
            self->animCurFrame = 0;
            self->hitPoints = 0x20;
            self->hitboxWidth = 24;
            self->hitboxHeight = 32;
            self->hitboxState = 2;

            self->flags |= FLAG_UNK_400000;

            // Determine tile indices to use
            pSrcTile = Room5_BreakableWallTilesCollision;
            if (g_CastleFlags[CASTLE_FLAG_CHI_BREAKABLE_WALL]) {
                pSrcTile += 0xC;    // No collision
            }
            
            // Update tilemap with appropriate collision
            tileIdx = 0x160;
            for (c = 0; c < WallWidthTiles; tileIdx++, c++) {
                for (b = 0; b < WallHeightTiles; b++, pSrcTile++) {
                    *(&g_Tilemap.fg[tileIdx] + b * RoomWidthTiles) = *pSrcTile;
                }
            }

            if (g_CastleFlags[CASTLE_FLAG_CHI_BREAKABLE_WALL]) {
                DestroyEntity(self);
                return;
            }

            newPrimIdx = g_api.AllocPrimitives(PRIM_GT4, 2);
            if (newPrimIdx == -1) {
                DestroyEntity(self);
                return;
            }
            self->flags |= FLAG_UNK_800000;
            self->primIndex = newPrimIdx;
            prim = &g_PrimBuf[newPrimIdx];

            self->ext.prim = prim;

            // Calculate values for left prim
            xPos = self->posX.i.hi - 23;
            yPos = self->posY.i.hi - 31;

            // Left prim
            prim->tpage = 0xF;
            prim->clut = 7;
            prim->u0 = prim->u2 = 0x94;
            prim->u1 = prim->u3 = 0xB4;
            prim->v0 = prim->v1 = 0x84;
            prim->v2 = prim->v3 = 0xC4;
            prim->x0 = prim->x2 = xPos;
            xPos += 32;
            prim->x1 = prim->x3 = xPos;
            prim->y0 = prim->y1 = yPos;
            prim->y2 = prim->y3 = yPos + 64;
            prim->priority = 0x6A;
            prim->drawMode = DRAW_UNK02;


            // Right prim
            prim = prim->next;
            prim->tpage = 0xF;
            prim->clut = 8;
            prim->u0 = prim->u2 = 0xBC;
            prim->u1 = prim->u3 = 0xCC;
            prim->v0 = prim->v1 = 0x84;
            prim->v2 = prim->v3 = 0xC4;
            prim->x0 = prim->x2 = xPos;
            prim->x1 = prim->x3 = xPos + 0x10;
            prim->y0 = prim->y1 = yPos;
            prim->y2 = prim->y3 = yPos + 0x40;
            prim->priority = 0x6A;
            prim->drawMode = DRAW_UNK02;
            
            pSrcTile = Room5_BreakableRoomEntityData;
            entity = self + 1;
            for (c = 0; c < 15; c++, entity++) {
                DestroyEntity(entity);
                CreateEntityFromEntity(0x19, self, entity);

                entity->params = *pSrcTile++;
                entity->posX.i.hi += *pSrcTile++;
                entity->posY.i.hi += *pSrcTile++;
                entity->rotZ = *pSrcTile++;
            }
            return;
        case Idle:
            if (self->flags & FLAG_DEAD) {
                g_api.PlaySfx(NA_SE_EN_ROCK_BREAK);
                
                self->ext.breakableWall.breakCount++;

                self->flags &= ~FLAG_DEAD;
                self->hitPoints = 0x20;
                self->hitboxWidth -= 8;
                self->hitboxOffX -= 8;

                // Update collision via tilemap
                pSrcTile = Room5_BreakableWallTilesCollision;
                pSrcTile += 0x18 - self->ext.breakableWall.breakCount * 4;
                tileIdx = 0x163 - self->ext.breakableWall.breakCount;
                for (b = 0; b < WallHeightTiles; b++, pSrcTile++) {
                    *(&g_Tilemap.fg[tileIdx] + b * RoomWidthTiles) = *pSrcTile;
                }

                entity = self + 1;
                entity += (self->ext.breakableWall.breakCount - 1) * 5;
                for (c = 0; c < 5; c++, entity++) {
                    entity->step++;
                }

                // Smoke entity?
                xPos = self->posX.i.hi + 0x20;
                yPos = self->posY.i.hi;
                xPos -= self->ext.breakableWall.breakCount * 0xC;
                entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
                if (entity != NULL) {
                    CreateEntityFromEntity(0x2, self, entity);
                    entity->posX.i.hi = xPos;
                    entity->posY.i.hi = yPos + 0x10;
                    entity->params = 0x13;
                    entity->params |= 0xC000;
                }
                
                // Rotating brick entities?
                for (c = 0; c < 3; c++) {
                    entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
                    if (entity != NULL) {
                        CreateEntityFromEntity(0x6, self, entity);
                        entity->posX.i.hi = xPos;
                        entity->posY.i.hi = yPos + 0x20 - (Random() & 3) * 8;
                        entity->params = 0x10;
                        entity->params |= 0xC000;
                    }
                }
                // Dynamically set Break_1, Break_2, or Break_3
                self->step += self->ext.breakableWall.breakCount;
            }
            return;
        case Break_1:   // Dynamically calculated, never set directly
            prim = self->ext.prim;
            prim = prim->next;
            prim->drawMode = DRAW_HIDE;
            self->ext.breakableWall.resetTimer = ResetTime;
            self->step = WaitForReset;
            return;
        case Break_2:   // Dynamically calculated, never set directly
            prim = self->ext.prim;
            prim->u1 = prim->u3 -= 0x10;
            prim->x1 = prim->x3 -= 0x10;
            entity = AllocEntity(&g_Entities[160], &g_Entities[192]);
            if (entity != NULL) {

                CreateEntityFromCurrentEntity(12, entity);
                entity->posX.i.hi = 0x20 - g_Tilemap.scrollX.i.hi;
                entity->posY.i.hi = 0x188 - g_Tilemap.scrollY.i.hi;
                entity->params = 3;
            }
            self->ext.breakableWall.resetTimer = ResetTime;
            self->step = WaitForReset;
            return;
        case Break_3:   // Dynamically calculated, never set directly
            prim = self->ext.prim;
            prim->drawMode = DRAW_HIDE;
            self->hitboxState = 0;
            g_CastleFlags[CASTLE_FLAG_CHI_BREAKABLE_WALL] = 1;
            // Update the map "explored" state
            // This is read from an array of data in DRA, and in
            // this case results in exploring the room to the left
            g_api.func_800F1FC4(CASTLE_FLAG_CHI_BREAKABLE_WALL);
            DestroyEntity(self);
            return;
        case WaitForReset:
            if (!--self->ext.breakableWall.resetTimer) {
                self->step = Idle;
            }
            return;
    }
}

// POSSIBLE FILE BREAK

INCLUDE_ASM("st/chi/nonmatchings/1C5CC", func_8019CBA8);    // [Entity]

INCLUDE_ASM("st/chi/nonmatchings/1C5CC", func_8019D0D8);

INCLUDE_ASM("st/chi/nonmatchings/1C5CC", func_8019D1A8);    // [Entity]

INCLUDE_ASM("st/chi/nonmatchings/1C5CC", func_8019D9C8);    // [Entity]

#include "../random.h"

// POSSIBLE FILE BREAK

#include "../update.h"

// POSSIBLE FILE BREAK

INCLUDE_ASM("st/chi/nonmatchings/1C5CC", func_8019E1A0);    // UpdateStageEntities()
//#include "../update_stage_entities.h"

// POSSIBLE FILE BREAK

INCLUDE_ASM("st/chi/nonmatchings/1C5CC", func_8019E2A8);    // HitDetection()
INCLUDE_ASM("st/chi/nonmatchings/1C5CC", func_8019F3C0);    // EntityDamageDisplay()
//#include "../collision.h"

#include "../create_entity.h"

INCLUDE_ASM("st/chi/nonmatchings/1C5CC", func_801A05DC);    // EntityIsNearPlayer2()
INCLUDE_ASM("st/chi/nonmatchings/1C5CC", func_801A0654);    // EntityRedDoor()
//#include "../e_red_door.h"

#include "../entity.h"

INCLUDE_ASM("st/chi/nonmatchings/1C5CC", func_801A1474);    // [Duplicate]

// "Current entity" functions?
#include "../get_distance_to_player_x.h"
#include "../get_distance_to_player_y.h"
#include "../get_side_to_player.h"
#include "../move_entity.h"
#include "../fall_entity.h"

INCLUDE_ASM("st/chi/nonmatchings/1C5CC", func_801A169C);    // [Duplicate]

INCLUDE_ASM("st/chi/nonmatchings/1C5CC", func_801A1914);    // [Duplicate]

#include "../../alloc_entity.h"

INCLUDE_ASM("st/chi/nonmatchings/1C5CC", func_801A1B5C);    // [Duplicate]

INCLUDE_ASM("st/chi/nonmatchings/1C5CC", func_801A1B88);    // [Duplicate]

INCLUDE_ASM("st/chi/nonmatchings/1C5CC", func_801A1BA4);    // [Duplicate]

INCLUDE_ASM("st/chi/nonmatchings/1C5CC", func_801A1C10);    // [Duplicate]

INCLUDE_ASM("st/chi/nonmatchings/1C5CC", func_801A1C48);    // [Duplicate]

INCLUDE_ASM("st/chi/nonmatchings/1C5CC", func_801A1C90);    // [Duplicate]

#include "../adjust_value_within_threshold.h"
#include "../unk_entity_func0.h"

INCLUDE_ASM("st/chi/nonmatchings/1C5CC", func_801A1DBC);    // [Duplicate]

#include "../get_angle_between_entities.h"
INCLUDE_ASM("st/chi/nonmatchings/1C5CC", func_801A1E24);    // [Duplicate]
#include "../get_normalized_angle.h"

#include "../set_step.h"
#include "../set_sub_step.h"

INCLUDE_ASM("st/chi/nonmatchings/1C5CC", func_801A1F08);    // EntityExplosionSpawn()
//#include "../entity_explosion_spawn.h"

#include "../init_entity.h"
#include "../entity_dummy.h"

INCLUDE_ASM("st/chi/nonmatchings/1C5CC", func_801A20C0);    // [Duplicate]

#include "../check_field_collision.h"
#include "../get_player_collision_with.h"

INCLUDE_ASM("st/chi/nonmatchings/1C5CC", func_801A2684);    // ReplaceBreakableWithItemDrop()
//#include "../replace_breakable_with_item_drop.h"

INCLUDE_ASM("st/chi/nonmatchings/1C5CC", func_801A273C);    // [Duplicate]
INCLUDE_ASM("st/chi/nonmatchings/1C5CC", func_801A27C0);    // [Duplicate]
INCLUDE_ASM("st/chi/nonmatchings/1C5CC", func_801A291C);    // CollectHeart()
INCLUDE_ASM("st/chi/nonmatchings/1C5CC", func_801A299C);    // CollectGold()
INCLUDE_ASM("st/chi/nonmatchings/1C5CC", func_801A2A78);    // CollectSubweapon()
INCLUDE_ASM("st/chi/nonmatchings/1C5CC", func_801A2B90);    // CollectHeartVessel()
INCLUDE_ASM("st/chi/nonmatchings/1C5CC", func_801A2C34);    // CollectLifeVessel()
INCLUDE_ASM("st/chi/nonmatchings/1C5CC", func_801A2C84);    // DestroyCurrentEntity()

// POSSIBLE FILE BREAK

INCLUDE_ASM("st/chi/nonmatchings/1C5CC", func_801A2CAC);    // EntityPrizeDrop()
//#include "../e_collect.h"

INCLUDE_ASM("st/chi/nonmatchings/1C5CC", func_801A3520);    // EntityExplosion()
//#include "../entity_explosion.h"

#include "../blink_item.h"

INCLUDE_ASM("st/chi/nonmatchings/1C5CC", func_801A36C0);    // EntityEquipItemDrop()

#include "../blit_char.h"

INCLUDE_ASM("st/chi/nonmatchings/1C5CC", func_801A3F58);    // EntityRelicOrb()
//#include "../entity_relic_orb.h"

INCLUDE_ASM("st/chi/nonmatchings/1C5CC", func_801A4A28);    // EntityHeartDrop()

INCLUDE_ASM("st/chi/nonmatchings/1C5CC", func_801A4B50);    // EntityMessageBox()
//#include "../entity_message_box.h"

#include "../check_coll_offsets.h"

INCLUDE_ASM("st/chi/nonmatchings/1C5CC", func_801A519C);    // EntityUnkId13()
//#include "../entity_unkId13.h"

INCLUDE_ASM("st/chi/nonmatchings/1C5CC", func_801A52AC);    // EntityUnkId14Spawner()
//#include "../entity_unkId14_spawner.h"

INCLUDE_ASM("st/chi/nonmatchings/1C5CC", func_801A53DC);    // EntityUnkId15Spawner()
//#include "../entity_unkId15_spawner.h"

INCLUDE_ASM("st/chi/nonmatchings/1C5CC", func_801A54C4);    // EntityUnkId14()
//#include "../entity_unkId14.h"

INCLUDE_ASM("st/chi/nonmatchings/1C5CC", func_801A55B4);    // EntityUnkId15()
//#include "../entity_unkId15.h"

INCLUDE_ASM("st/chi/nonmatchings/1C5CC", func_801A56A8);    // EntityOlroxDrool()
//#include "../entity_olrox_drool.h"

INCLUDE_ASM("st/chi/nonmatchings/1C5CC", func_801A58D8);    // [Duplicate]

INCLUDE_ASM("st/chi/nonmatchings/1C5CC", func_801A59D4);    // [Duplicate]

INCLUDE_ASM("st/chi/nonmatchings/1C5CC", func_801A5F54);    // EntityIntenseExplosion()
//#include "../entity_intense_explosion.h"

INCLUDE_ASM("st/chi/nonmatchings/1C5CC", func_801A6054);    // [Duplicate]

// [Duplicate]
void func_801A6120(u16 entityId, Entity* src, Entity* dst)
{
    DestroyEntity(dst);
    dst->entityId = entityId;
    dst->pfnUpdate = PfnEntityUpdates[entityId - 1];
    dst->posX.i.hi = src->posX.i.hi;
    dst->posY.i.hi = src->posY.i.hi;
    dst->unk5A = src->unk5A;
    dst->zPriority = src->zPriority;
    dst->animSet = src->animSet;
    dst->flags = FLAG_UNK_2000 | FLAG_UNK_01000000 | FLAG_UNK_04000000 |
                 FLAG_UNK_08000000 | FLAG_DESTROY_IF_BARELY_OUT_OF_CAMERA |
                 FLAG_DESTROY_IF_OUT_OF_CAMERA;

    if (src->palette & 0x8000) {
        dst->palette = src->hitEffect;
    } else {
        dst->palette = src->palette;
    }
}

INCLUDE_ASM("st/chi/nonmatchings/1C5CC", func_801A61E8);    // [Duplicate]

INCLUDE_ASM("st/chi/nonmatchings/1C5CC", func_801A62A0);    // EntityBigRedFireball()
//#include "../entity_big_red_fireball.h"

INCLUDE_ASM("st/chi/nonmatchings/1C5CC", func_801A6478);    // UnkRecursivePrimFunc1()
//#include "../unk_recursive_primfunc_1.h"

INCLUDE_ASM("st/chi/nonmatchings/1C5CC", func_801A6A58);    // UnkRecursivePrimFunc2()
//#include "../unk_recursive_primfunc_2.h"

#include "../clut_lerp.h"

#include "../play_sfx_with_pos_args.h"

INCLUDE_ASM("st/chi/nonmatchings/1C5CC", func_801A7448);    // EntitySoulStealOrb()
//#include "../entity_soul_steal_orb.h"

INCLUDE_ASM("st/chi/nonmatchings/1C5CC", func_801A77DC);    // EntityEnemyBlood()
//#include "../entity_enemy_blood.h"

INCLUDE_ASM("st/chi/nonmatchings/1C5CC", func_801A7C8C);    // EntityRoomForeground()
//#include "../e_room_fg.h"

#include "../bottom_corner_text.h"

INCLUDE_ASM("st/chi/nonmatchings/1C5CC", func_801A80A8);

// POSSIBLE FILE BREAK

INCLUDE_ASM("st/chi/nonmatchings/1C5CC", func_801A813C);    // [Entity]

INCLUDE_ASM("st/chi/nonmatchings/1C5CC", func_801A8DE8);    // [Entity]

INCLUDE_ASM("st/chi/nonmatchings/1C5CC", func_801A8EAC);    // [Entity]

INCLUDE_ASM("st/chi/nonmatchings/1C5CC", func_801A93D4);    // [Entity]

INCLUDE_ASM("st/chi/nonmatchings/1C5CC", func_801A9588);    // [Entity]

INCLUDE_ASM("st/chi/nonmatchings/1C5CC", func_801A97C8);    // [Entity]

INCLUDE_ASM("st/chi/nonmatchings/1C5CC", func_801A9D40);    // [Entity]

INCLUDE_ASM("st/chi/nonmatchings/1C5CC", func_801A9E94);    // [Entity]

INCLUDE_ASM("st/chi/nonmatchings/1C5CC", func_801AA020);    // [Entity]

INCLUDE_ASM("st/chi/nonmatchings/1C5CC", func_801AA390);    // [Entity]

INCLUDE_ASM("st/chi/nonmatchings/1C5CC", func_801AB0C0);    // [Entity]

INCLUDE_ASM("st/chi/nonmatchings/1C5CC", func_801AB548);

// POSSIBLE FILE BREAK

INCLUDE_ASM("st/chi/nonmatchings/1C5CC", func_801AB7CC);    // [Entity]

INCLUDE_ASM("st/chi/nonmatchings/1C5CC", func_801AC074);    // [Entity]

INCLUDE_ASM("st/chi/nonmatchings/1C5CC", func_801AC730);    // [Entity]

INCLUDE_ASM("st/chi/nonmatchings/1C5CC", func_801ACB6C);    // [Entity]

INCLUDE_ASM("st/chi/nonmatchings/1C5CC", func_801ACEF4);    // [Entity]

s32 func_801AE70C(Primitive* prim, u8 arg1);
void StageNamePopupHelper(Primitive* prim)  // [Duplicate]
{
    u8 xPos;
    s32 i;
    s32 j;

    switch (prim->p3) {
    case 0:
        if (prim->p1 < 0x80) {
            if (--prim->p1 == 0) {
                prim->p3 = 1;
            }
        } else {
            if (++prim->p1 == 0) {
                prim->p3 = 2;
            }
        }

        if (prim->p3 != 0) {
            u8* dst = prim->p3 == 1 ? &prim->r1 : &prim->r0;
            for (i = 0; i < 2; i++) {
                for (j = 0; j < 3; j++) {
                    dst[j] = 0x50;
                }
                dst += 0x18;
            }
            prim->p2 = 0;
        }
        break;
    case 1:
        if (prim->p2 < 0x14) {
            prim->p2++;
        }
        xPos = prim->p2 / 5;
        prim->x2 = prim->x0 = prim->x0 + xPos;
        prim->x1 = prim->x1 + xPos;
        prim->x3 = prim->x0;
        func_801AE70C(prim, 4);
        break;
    case 2:
        if (prim->p2 < 0x14) {
            prim->p2++;
        }
        xPos = prim->p2 / 5;
        prim->x2 = prim->x0 = prim->x0 - xPos;
        prim->x1 = prim->x1 - xPos;
        prim->x3 = prim->x0;
        func_801AE70C(prim, 4);
        break;
    }
}

// POSSIBLE FILE BREAK

INCLUDE_ASM("st/chi/nonmatchings/1C5CC", func_801AD2BC);    // EntityStageNamePopup()
//#include "../e_stage_name.h"

//NOTE: The remaining functions are all contained in "../prim_helpers.h" but
//      UnkPrimHelper and PrimDecreaseBrightness don't match.
INCLUDE_ASM("st/chi/nonmatchings/1C5CC", func_801ADF40);    // UnkPrimHelper()
//INCLUDE_ASM("st/chi/nonmatchings/1C5CC", func_801AE328);    // UpdateAnimation()
s32 UpdateAnimation(u8* texAnimations, Primitive* prim) {
    s16 sp0;
    s16 tempUv;
    u8 new_var;
    u8* nextAnimation = texAnimations + ((prim->p1 * 5) & 0xFF);
    u8 new_var2;
    s32 retVal = 0;

    if (prim->p2 == 0) {
        if (*nextAnimation) {
            if (*nextAnimation == 0xFF) {
                return 0;
            }
            retVal = 0x80;
            prim->p2 = nextAnimation[0];
            ++nextAnimation;
            tempUv = nextAnimation[0] + (nextAnimation[1] << 8);
            nextAnimation += 2;
            sp0 = nextAnimation[0] + (nextAnimation[1] << 8);
            LOH(prim->u0) = tempUv;
            LOH(prim->u1) = tempUv + *((u8*)(&sp0));
            new_var = *((u8*)&sp0 + 1);
            LOH(prim->u3) = tempUv + sp0;
            LOH(prim->u2) = tempUv + (new_var << 8);
            ++prim->p1;
        } else {
            prim->p1 = 0;
            prim->p2 = 0;
            prim->p2 = texAnimations[0];
            tempUv = texAnimations[1] + (texAnimations[2] << 8);
            sp0 = texAnimations[3] + (texAnimations[4] << 8);
            LOH(prim->u0) = tempUv;
            LOH(prim->u1) = tempUv + (*(u8*)&sp0);
            new_var2 = *((u8*)&sp0 + 1);
            LOH(prim->u3) = tempUv + sp0;
            LOH(prim->u2) = tempUv + (new_var2 << 8);
            ++prim->p1;
            return 0;
        }
    }

    retVal |= 1;
    --prim->p2;
    return (retVal | 1) & 0xFF;
}
//INCLUDE_ASM("st/chi/nonmatchings/1C5CC", func_801AE478);    // FindFirstUnkPrim()
Primitive* FindFirstUnkPrim(Primitive* poly) {
    while (poly != NULL) {
        if (poly->p3 != 0) {
            poly = poly->next;
        } else {
            return poly;
        }
    }
    return NULL;
}
//INCLUDE_ASM("st/chi/nonmatchings/1C5CC", func_801AE4A8);    // FindFirstUnkPrim2()
Primitive* FindFirstUnkPrim2(Primitive* prim, u8 index) {

    Primitive* ret;
    int i;

    for (; prim; prim = prim->next) {
        if (!prim->p3) {
            ret = prim;
            for (i = 1; i < index; ++i) {
                prim = prim->next;
                if (!prim) {
                    return NULL;
                }
                if (prim->p3) {
                    break;
                }
            }
            if (i == index) {
                return ret;
            }
        }
    }
    return NULL;
}
//INCLUDE_ASM("st/chi/nonmatchings/1C5CC", func_801AE524);    // PrimToggleVisibility()
Primitive* PrimToggleVisibility(Primitive* firstPrim, s32 count) {
    Primitive* prim;
    s8 isVisible;
    s32 i;

    if (firstPrim->p3) {
        firstPrim->p3 = 0;
    } else {
        firstPrim->p3 = 1;
    }

    prim = firstPrim;
    for (i = 0; i < count; i++) {
        if (prim->p3) {
            prim->drawMode &= ~DRAW_HIDE;
            isVisible = false;
        } else {
            prim->drawMode |= DRAW_HIDE;
            isVisible = true;
        }

        prim = prim->next;
        if (prim == NULL)
            return 0;
        prim->p3 = isVisible;
    }

    return prim;
}
//INCLUDE_ASM("st/chi/nonmatchings/1C5CC", func_801AE5AC);    // PrimResetNext()
void PrimResetNext(Primitive* prim) {
    prim->p1 = 0;
    prim->p2 = 0;
    prim->p3 = 0;
    prim->next->x1 = 0;
    prim->next->y1 = 0;
    prim->next->y0 = 0;
    prim->next->x0 = 0;
    prim->next->clut = 0;
    LOHU(prim->next->u0) = 0;
    LOHU(prim->next->b1) = 0;
    LOHU(prim->next->r1) = 0;
    LOHU(prim->next->u1) = 0;
    prim->next->tpage = 0;
    LOHU(prim->next->r2) = 0;
    LOHU(prim->next->b2) = 0;
    prim->next->u2 = 0;
    prim->next->v2 = 0;
    prim->next->r3 = 0;
    prim->next->b3 = 0;
    prim->next->x2 = 0;
    prim->next->y2 = 0;
}
//INCLUDE_ASM("st/chi/nonmatchings/1C5CC", func_801AE68C);    // UnkPolyFunc2()
void UnkPolyFunc2(Primitive* prim) {
    PrimResetNext(prim);
    prim->p3 = 8;
    prim->next->p3 = 1;
    prim->next->type = PRIM_LINE_G2;
    prim->next->drawMode = 0xA;
}
//INCLUDE_ASM("st/chi/nonmatchings/1C5CC", func_801AE6E0);    // UnkPolyFunc0()
void UnkPolyFunc0(Primitive* prim) {
    prim->p3 = 0;
    prim->drawMode = DRAW_HIDE;
    prim->next->p3 = 0;
    prim->next->type = PRIM_GT4;
    prim->next->drawMode = DRAW_HIDE;
}
INCLUDE_ASM("st/chi/nonmatchings/1C5CC", func_801AE70C);    // PrimDecreaseBrightness()
//#include "../prim_helpers.h"
