// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../no3/no3.h"

void EntityHeartRoomSwitch(Entity* self) {
    s32 collision = GetPlayerCollisionWith(self, 8, 4, 4);
    s32 worldPos;
    Entity* player;
    
    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitStInteractable);
        self->animCurFrame = 9;
        self->zPriority = 0x5E;
        if (g_CastleFlags[WRP_TO_NP3_SHORTCUT]) {
            self->posY.i.hi += 4;
            self->step = 2;
        }
        break;

    case 1:
        if (collision != 0) {
            player = &PLAYER;
            player->posY.i.hi++;
            self->posY.val += FIX(0.25);
            worldPos = g_Tilemap.scrollY.i.hi + self->posY.i.hi;
            if (worldPos > 193) {
                self->posY.i.hi = 193 - g_Tilemap.scrollY.i.hi;
                g_CastleFlags[WRP_TO_NP3_SHORTCUT] = 1;
#if defined(STAGE_IS_NO3)
                g_api.PlaySfx(SFX_STONE_MOVE_B);
#else
                g_api.PlaySfx(SFX_SWITCH_CLICK);
#endif
                self->step++;
            }
        }
        break;
    }
}

void EntityHeartRoomGoldDoor(Entity* self) {
    Entity* newEntity;
    Primitive* prim;
    s32 primIndex;
    s32 yPos;
    s32 i;
    s32 tilePos;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitStInteractable);
        self->animCurFrame = 37;
        self->zPriority = 0x5E;

        if (g_CastleFlags[WRP_TO_NP3_SHORTCUT]) {
            self->step = 128;
            self->animCurFrame = 0;
            for (tilePos = 0x48, i = 0; i < 8; tilePos += 0x10, i++) {
                g_Tilemap.fg[tilePos] = 0;
            }
            break;
        }

        primIndex = g_api.AllocPrimitives(PRIM_TILE, 64);
        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags |= FLAG_HAS_PRIMS;
        self->primIndex = primIndex;
        prim = &g_PrimBuf[primIndex];
        self->ext.heartRoomGoldDoor.prim = prim;
        while (prim != NULL) {
            prim->u0 = prim->v0 = 1;
            prim->r0 = 64;
            prim->b0 = 128;
            prim->g0 = 96;
            prim->priority = self->zPriority + 0x18;
            prim->drawMode = DRAW_HIDE;
            prim->p3 = 0;
            prim = prim->next;
        }

        for (tilePos = 0x48, i = 0; i < 8; tilePos += 0x10, i++) {
            g_Tilemap.fg[tilePos] = 0x4FA;
        }
        break;

    case 1:
        if (g_CastleFlags[WRP_TO_NP3_SHORTCUT]) {
            g_api.PlaySfx(SFX_STONE_MOVE_A);
            self->step++;
        }
        break;

    case 2:
        self->posY.val += FIX(0.375);
        self->ext.heartRoomGoldDoor.timer++;
        if (self->ext.heartRoomGoldDoor.timer & 1) {
            self->posX.i.hi++;
        } else {
            self->posX.i.hi--;
        }
#if !defined(STAGE_IS_NO3)
        if ((self->ext.heartRoomGoldDoor.timer & 0xF) == 0) {
            g_api.PlaySfx(SFX_STONE_MOVE_A);
        }
#endif

        yPos = self->posY.i.hi - 112;
        yPos = yPos / 16;
        // Door is fully opened now.
        if (yPos > 8) {
            yPos = 8;
            self->step = 3;
        }

        for (tilePos = 0x48, i = 0; i < yPos; tilePos += 0x10, i++) {
            g_Tilemap.fg[tilePos] = 0;
        }

        if (!(g_Timer & 1)) {
            prim = self->ext.heartRoomGoldDoor.prim;
            prim = FindFirstUnkPrim(prim);
            if (prim != NULL) {
                prim->p3 = 1;
            }
            if (!(g_Timer & 0xF)) {
                newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
                if (newEntity != NULL) {
                    CreateEntityFromEntity(
                        E_INTENSE_EXPLOSION, self, newEntity);
                    newEntity->posY.i.hi = 188;
                    newEntity->posX.i.hi += -8 + (Random() & 15);
                    newEntity->params = 0x10;
                    newEntity->drawFlags |= FLAG_DRAW_ROTY | FLAG_DRAW_ROTX;
                    newEntity->rotX = newEntity->rotY = 192;
                }
            }
        }
        break;
    }

    if (self->flags & FLAG_HAS_PRIMS) {
        prim = self->ext.heartRoomGoldDoor.prim;
        while (prim != NULL) {
            if (prim->p3) {
                DoorCascadePhysics(prim);
            }
            prim = prim->next;
        }
    }
}

INCLUDE_ASM("st/no3_psp/psp/no3_psp/13C8", func_pspeu_09239020);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/13C8", EntityWeightsSwitch);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/13C8", EntityPathBlockSmallWeight);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/13C8", EntityPathBlockTallWeight);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/13C8", DoorCascadePhysics);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/13C8", EntityCavernDoorLever);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/13C8", EntityCavernDoorPlatform);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/13C8", EntityCavernDoor);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/13C8", EntityTransparentWater);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/13C8", EntityBackgroundBushes);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/13C8", EntityBackgroundTrees);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/13C8", EntityStairwayPiece);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/13C8", EntityFallingRock);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/13C8", EntityMermanRockLeftSide);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/13C8", EntityMermanRockRightSide);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/13C8", EntityJewelSwordDoor);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/13C8", EntityFallingRock2);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/13C8", func_pspeu_0923C528);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/13C8", EntityDeathSkySwirl);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/13C8", EntityLightningThunder);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/13C8", EntityLightningCloud);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/13C8", EntityTrapDoor);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/13C8", func_pspeu_0923D348);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/13C8", EntityExplosionPuffOpaque);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/13C8", EntityPushAlucard);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/13C8", EntityCastleDoorTransition);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/13C8", EntityForegroundTree);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/13C8", EntityUnkId50);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/13C8", EntityBackgroundPineTrees);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/13C8", EntityUnkId52);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/13C8", EntityCastleBridge);

// clumsy thing, linter splits the line which breaks INCLUDE_ASM
// clang-format off
INCLUDE_ASM("st/no3_psp/psp/no3_psp/13C8", EntityDistantBackgroundTrees);
// clang-format on

INCLUDE_ASM("st/no3_psp/psp/no3_psp/13C8", EntityBackgroundCastleWall);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/13C8", EntityFlyingOwlAndLeaves);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/13C8", EntityFallingLeaf);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/13C8", EntityRoomTransition2);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/13C8", EntityDeathStolenItem);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/13C8", EntityDeath);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/13C8", EntityDeathScythe);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/13C8", EntityDeathScytheShadow);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/13C8", EntityTilemapShufflerUnused);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/13C8", EntityShuttingWindow);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/13C8", EntityBreakable);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/13C8", EntityCavernDoorVase);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/13C8", EntityUnkId16);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/13C8", func_pspeu_09242C00);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/13C8", func_pspeu_09242CA0);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/13C8", func_pspeu_09242FB8);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/13C8", func_pspeu_09243040);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/13C8", func_pspeu_09243108);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/13C8", func_pspeu_09243168);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/13C8", func_pspeu_09243378);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/13C8", func_pspeu_092433B0);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/13C8", func_pspeu_09243748);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/13C8", NO3_EntityCutscene);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/13C8", EntityLockCamera);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/13C8", func_pspeu_09245A58);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/13C8", func_pspeu_09245B78);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/13C8", func_pspeu_09245D10);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/13C8", func_pspeu_09245EA8);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/13C8", func_pspeu_09245F18);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/13C8", func_pspeu_09245FA0);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/13C8", func_pspeu_092460E0);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/13C8", func_pspeu_09246238);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/13C8", func_pspeu_092462B0);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/13C8", func_pspeu_09246338);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/13C8", func_pspeu_09246480);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/13C8", InitRoomEntities);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/13C8", UpdateRoomPosition);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/13C8", CreateEntityFromCurrentEntity);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/13C8", CreateEntityFromEntity);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/13C8", EntityBat);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/13C8", EntityStageNamePopup);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/13C8", func_pspeu_09247BB8);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/13C8", NO3_EntityRedDoor);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/13C8", Random);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/13C8", Update);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/13C8", UpdateStageEntities);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/13C8", func_pspeu_092493F8);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/13C8", func_pspeu_09249590);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/13C8", func_pspeu_09249738);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/13C8", func_pspeu_09249878);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/13C8", EntityFireWarg);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/13C8", EntityUnkId30);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/13C8", EntityUnkId31);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/13C8", EntityExplosion3);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/13C8", func_pspeu_0924C7A8);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/13C8", EntityFireWargWaveAttack);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/13C8", EntityUnkId2F);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/13C8", EntityFireWargDeathBeams);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/13C8", func_pspeu_0924D9C0);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/13C8", EntityMerman2);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/13C8", EntityExplosion2);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/13C8", EntityMediumWaterSplash);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/13C8", EntityMermanWaterSplash);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/13C8", EntityFallingObject2);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/13C8", EntityHighWaterSplash);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/13C8", EntityDeadMerman);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/13C8", EntityMermanSpawner);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/13C8", EntityMerman);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/13C8", EntityMermanFireball);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/13C8", EntityFallingObject);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/13C8", EntityMermanExplosion);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/13C8", func_pspeu_092516E8);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/13C8", func_pspeu_09251C70);
