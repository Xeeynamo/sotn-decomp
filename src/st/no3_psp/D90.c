// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../no3/no3.h"

static SVECTOR doorvec1 = {-8, -128, -48};
static SVECTOR doorvec2 = {8, -128, -48};
static SVECTOR doorvec3 = {-8, 0, -48};
static SVECTOR doorvec4 = {8, 0, -48};

static SVECTOR doorvec5 = {-8, -128, 4};
static SVECTOR doorvec6 = {-8, -128, -48};
static SVECTOR doorvec7 = {-8, 0, 4};
static SVECTOR doorvec8 = {-8, 0, -48};

static SVECTOR doorvec9 = {8, -128, -48};
static SVECTOR doorvec10 = {8, -128, 4};
static SVECTOR doorvec11 = {8, 0, -48};
static SVECTOR doorvec12 = {8, 0, 4};

static SVEC4 castleDoorVectors[3] = {
    {
        &doorvec1,
        &doorvec2,
        &doorvec3,
        &doorvec4,
    },
    {
        &doorvec5,
        &doorvec6,
        &doorvec7,
        &doorvec8,
    },
    {
        &doorvec9,
        &doorvec10,
        &doorvec11,
        &doorvec12,
    }};

static MATRIX castleDoorColorMatrix = {
    {{0x800, 0, 0x800}, {0x800, 0, 0x800}, {0x800, 0, 0x800}}};

static SVECTOR doorColNormVec1 = {0, 0, 0x1000};
static SVECTOR doorColNormVec2 = {0x1000, 0, 0};
static SVECTOR doorColNormVec3 = {-0x1000, 0, 0};

static SVECTOR* doorColorNormalVectors[] = {
    &doorColNormVec1, &doorColNormVec2, &doorColNormVec3};

static u8 castleDoorUCoords[] = {
    0x3A, 0x46, 0x01, 0x35, 0x35, 0x01, 0x00, 0x00};
static u16 castleDoorTilesOpen[] = {
    0x06D1, 0x06D2, 0x06D3, 0x06D4, 0x06D5, 0x06D6, 0x06D3, 0x06D4,
};
static u16 castleDoorTilesShut[] = {
    0x010F, 0x112, 0x114, 0x116, 0x118, 0x11A, 0x114, 0x116,
};

void EntityCastleDoor(Entity* self) {
    s32 selfX, selfY;
    long sxy2, p, sxy3;
    SVECTOR sVec1;
    VECTOR vec1;
    MATRIX mtx1, mtx2;
    CVECTOR cVec1, cVec2;
    Primitive* prim;
    SVECTOR** var_s5;
    SVEC4* var_s6;
    s32 primIndex;
    s32 temp_s3;
    s32 tilePos;
    u8* uPtr;
    s32 i;
    
    SVECTOR sVec2 = {0};


    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitInteractable);
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 3);
        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags |= FLAG_HAS_PRIMS;
        self->primIndex = primIndex;
        prim = &g_PrimBuf[primIndex];
        self->ext.castleDoor.prim = prim;
        uPtr = castleDoorUCoords;
        for (i = 0; i < 3; i++) {
            prim->tpage = 0xF;
            prim->clut = 0x41;
            prim->priority = 0x6A;
            prim->drawMode = DRAW_UNK02;
            prim->u0 = prim->u2 = *uPtr++;
            prim->u1 = prim->u3 = *uPtr++;
            prim->v0 = prim->v1 = 1;
            prim->v2 = prim->v3 = 0x81;
            prim = prim->next;
        }
#if defined(STAGE_IS_NO3)
        if (g_CastleFlags[PROLOGUE_COMPLETE]) {
            self->ext.castleDoor.rotZ = 0;
            self->step = 5;
        }
#else
        self->ext.castleDoor.rotZ = 0;
        tilePos = 0x445;
        for (i = 0; i < 8; i++) {
            g_Tilemap.fg[tilePos] = castleDoorTilesShut[i];
            tilePos += 0x20;
        }
#endif
        break;
#if defined(STAGE_IS_NO3)
    case 1:
        tilePos = 0x445;
        for (i = 0; i < 8; tilePos += 0x20, i++) {
            g_Tilemap.fg[tilePos] = castleDoorTilesOpen[i];
        }
        self->ext.castleDoor.rotZ = -0x380;
        self->ext.castleDoor.timer = 32;
        self->step = 4;
        g_CastleFlags[PROLOGUE_COMPLETE] = 1;
        break;

    case 2:
        self->ext.castleDoor.rotZ -= 8;
        if (self->ext.castleDoor.rotZ < -0x380) {
            self->ext.castleDoor.rotZ = -0x380;
            self->ext.castleDoor.timer = 128;
            self->step++;
        }
        break;

    case 3:
        if (!--self->ext.castleDoor.timer) {
            self->step++;
        }
        break;

    case 4:
        self->ext.castleDoor.rotZ += 0x10;
        if (self->ext.castleDoor.rotZ > 0) {
            self->ext.castleDoor.rotZ = 0;
            self->step += 2;
            g_api.PlaySfx(SFX_START_SLAM_B);
            tilePos = 0x445;
            for (i = 0; i < 8; tilePos += 0x20, i++) {
                g_Tilemap.fg[tilePos] = castleDoorTilesShut[i];
            }
        }
        break;

    case 5:
        self->step++;
        tilePos = 0x445;
        for (i = 0; i < 8; tilePos += 0x20, i++) {
            g_Tilemap.fg[tilePos] = castleDoorTilesShut[i];
        }
        break;
#endif
    }
    SetGeomScreen(0x300);
    selfX = self->posX.i.hi;
    selfY = self->posY.i.hi;
    SetGeomOffset(selfX, selfY);
    sVec1.vx = 0;
    sVec1.vy = self->ext.castleDoor.rotZ;
    sVec1.vz = 0;
    RotMatrix(&sVec2, &mtx1);
    RotMatrixY(sVec1.vy, &mtx1);
    vec1.vx = 0;
    vec1.vy = 0;
    vec1.vz = 0x334;
    TransMatrix(&mtx1, &vec1);
    SetRotMatrix(&mtx1);
    SetTransMatrix(&mtx1);
    SetBackColor(128, 128, 128);
    cVec1.r = 128;
    cVec1.g = 128;
    cVec1.b = 128;
    cVec1.cd = 4;
    cVec2.r = 64;
    cVec2.g = 64;
    cVec2.b = 64;
    cVec2.cd = 4;
    RotMatrix(&sVec1, &mtx2);
    SetColorMatrix(&castleDoorColorMatrix);
    SetLightMatrix(&mtx2);

    prim = self->ext.castleDoor.prim;
    var_s6 = castleDoorVectors;
    var_s5 = doorColorNormalVectors;
    for (i = 0; i < 3; var_s6++, var_s5++, i++) {
        temp_s3 = RotAverageNclip4(
            var_s6->v0, var_s6->v1, var_s6->v2, var_s6->v3, (long*)&prim->x0,
            (long*)&prim->x1, (long*)&prim->x2, (long*)&prim->x3, &sxy2, &sxy3,
            &p);
        NormalColorCol(*var_s5, &cVec1, (CVECTOR*)&prim->r0);
        LOW(prim->r1) = LOW(prim->r0);
        LOW(prim->r2) = LOW(prim->r0);
        LOW(prim->r3) = LOW(prim->r0);

        if (i != 0) {
            NormalColorCol(*var_s5, &cVec2, (CVECTOR*)&prim->r0);
            LOW(prim->r2) = LOW(prim->r0);
        }

        if (temp_s3 <= 0) {
            prim->drawMode = DRAW_HIDE;
        } else {
            prim->drawMode = DRAW_COLORS | DRAW_UNK02;
        }
        prim = prim->next;
    }
}

INCLUDE_ASM("st/no3_psp/psp/no3_psp/D90", EntityHeartRoomSwitch);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/D90", EntityHeartRoomGoldDoor);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/D90", func_pspeu_09239020);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/D90", EntityWeightsSwitch);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/D90", EntityPathBlockSmallWeight);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/D90", EntityPathBlockTallWeight);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/D90", func_pspeu_09239940);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/D90", EntityCavernDoorLever);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/D90", EntityCavernDoorPlatform);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/D90", EntityCavernDoor);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/D90", EntityTransparentWater);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/D90", EntityBackgroundBushes);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/D90", EntityBackgroundTrees);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/D90", EntityStairwayPiece);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/D90", EntityFallingRock);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/D90", EntityMermanRockLeftSide);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/D90", EntityMermanRockRightSide);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/D90", EntityJewelSwordDoor);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/D90", EntityFallingRock2);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/D90", func_pspeu_0923C528);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/D90", EntityDeathSkySwirl);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/D90", EntityLightningThunder);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/D90", EntityLightningCloud);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/D90", EntityTrapDoor);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/D90", func_pspeu_0923D348);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/D90", EntityExplosionPuffOpaque);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/D90", EntityPushAlucard);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/D90", EntityCastleDoorTransition);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/D90", EntityForegroundTree);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/D90", EntityUnkId50);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/D90", EntityBackgroundPineTrees);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/D90", EntityUnkId52);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/D90", EntityCastleBridge);

// clumsy thing, linter splits the line which breaks INCLUDE_ASM
// clang-format off
INCLUDE_ASM("st/no3_psp/psp/no3_psp/D90", EntityDistantBackgroundTrees);
// clang-format on

INCLUDE_ASM("st/no3_psp/psp/no3_psp/D90", EntityBackgroundCastleWall);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/D90", EntityFlyingOwlAndLeaves);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/D90", EntityFallingLeaf);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/D90", EntityRoomTransition2);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/D90", EntityDeathStolenItem);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/D90", EntityDeath);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/D90", EntityDeathScythe);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/D90", EntityDeathScytheShadow);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/D90", EntityTilemapShufflerUnused);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/D90", EntityShuttingWindow);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/D90", EntityBreakable);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/D90", EntityCavernDoorVase);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/D90", EntityUnkId16);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/D90", func_pspeu_09242C00);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/D90", func_pspeu_09242CA0);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/D90", func_pspeu_09242FB8);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/D90", func_pspeu_09243040);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/D90", func_pspeu_09243108);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/D90", func_pspeu_09243168);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/D90", func_pspeu_09243378);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/D90", func_pspeu_092433B0);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/D90", func_pspeu_09243748);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/D90", NO3_EntityCutscene);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/D90", EntityLockCamera);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/D90", func_pspeu_09245A58);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/D90", func_pspeu_09245B78);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/D90", func_pspeu_09245D10);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/D90", func_pspeu_09245EA8);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/D90", func_pspeu_09245F18);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/D90", func_pspeu_09245FA0);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/D90", func_pspeu_092460E0);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/D90", func_pspeu_09246238);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/D90", func_pspeu_092462B0);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/D90", func_pspeu_09246338);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/D90", func_pspeu_09246480);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/D90", InitRoomEntities);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/D90", UpdateRoomPosition);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/D90", CreateEntityFromCurrentEntity);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/D90", func_pspeu_09246978);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/D90", EntityBat);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/D90", EntityStageNamePopup);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/D90", func_pspeu_09247BB8);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/D90", NO3_EntityRedDoor);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/D90", Random);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/D90", Update);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/D90", UpdateStageEntities);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/D90", func_pspeu_092493F8);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/D90", func_pspeu_09249590);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/D90", func_pspeu_09249738);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/D90", func_pspeu_09249878);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/D90", EntityFireWarg);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/D90", EntityUnkId30);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/D90", EntityUnkId31);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/D90", EntityExplosion3);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/D90", func_pspeu_0924C7A8);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/D90", EntityFireWargWaveAttack);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/D90", EntityUnkId2F);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/D90", EntityFireWargDeathBeams);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/D90", func_pspeu_0924D9C0);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/D90", EntityMerman2);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/D90", EntityExplosion2);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/D90", EntityMediumWaterSplash);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/D90", EntityMermanWaterSplash);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/D90", EntityFallingObject2);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/D90", EntityHighWaterSplash);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/D90", EntityDeadMerman);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/D90", EntityMermanSpawner);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/D90", EntityMerman);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/D90", EntityMermanFireball);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/D90", EntityFallingObject);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/D90", EntityMermanExplosion);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/D90", func_pspeu_092516E8);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/D90", func_pspeu_09251C70);
