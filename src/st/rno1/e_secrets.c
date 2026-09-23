// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rno1.h"

#ifdef VERSION_PSP
extern s32 E_ID(WALL_SEGMENT);
extern s32 E_ID(WALL_PARTICLES);
extern s32 E_ID(WALL_DEBRIS);
#endif

extern EInit g_EInitParticle;
extern EInit g_EInitSecretWall;
extern EInit g_EInitWallSegment;
extern EInit g_EInitSecretElevator;


static u16 tilePositions[] = {0x6E, 0x6D, 0x5E, 0x5D, 0x4E, 0x4D, 0x3E, 0x3D};

static u16 tiles[][8] = {
    {0x3F9, 0x3FB, 0x3FE, 0x401, 0x403, 0x40D, 0x3FE, 0x40F},
    {0x3F9, 0x3FB, 0x3FE, 0x401, 0x403, 0x40D, 0x3FE, 0x40F},
    {0x3F9, 0x3FB, 0x3FE, 0x401, 0x403, 0x40D, 0x3FE, 0x40F},
    {0x3F9, 0x3FB, 0x412, 0x419, 0x50B, 0x4BE, 0x3FE, 0x40F},
    {0x4B7, 0x4B2, 0x53D, 0x53E, 0x403, 0x40D, 0x3FE, 0x40F},
    {0x4B7, 0x4B2, 0x4BD, 0x4B8, 0x50B, 0x4BE, 0x4BD, 0x50C},
};

static bool elevatorBool = false;


static s16 g_Rno1DebrisCollisionSensors[] = {
    0, 0, 0, 4, 0, -4, 0, 0,
};

static s32 g_Rno1DebrisVelocities[][2] = {
    {FIX(1), FIX(-3)}, {FIX(1.5), FIX(-1.5)},  {FIX(0.75), FIX(-2.25)},
    {FIX(2), FIX(-1)}, {FIX(0.5), FIX(-0.25)}, {FIX(1), FIX(-2)},
};

static s32 g_Rno1WallDebrisVelocities[][2] = {
    {0, 0x6000},      {0x2000, 0x4000}, {0x4000, 0x8000},
    {0x8000, 0x6000}, {0xC000, 0x4000},
};

static s16 g_Rno1WallDebrisSizes[] = {8, 12, 4, 14, 6, 0};
static s16 g_Rno1WallDebrisRotations[] = {
    0x180, 0x100, 0x200, 0xC0, 0x1C0, 0,
};

static AnimateEntityFrame g_Rno1DebrisAnim[] = {
    {3, 1}, {3, 2}, {3, 3}, {3, 4}, {3, 5}, {3, 6}, {-1, 0},
};

// Wall which must be broken in order to access the secret pink elevator
void EntitySecretElevatorWall(Entity* self) {
    Entity* tempEntity;
    s32 tilePos;
    s32 i;
    u8 animFrame;
    Entity* tempEntity2;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitSecretWall);
        self->zPriority = 0x70;
        self->hitPoints = 0x7FFF;
        self->hitboxState = 0;
        self->ext.segmentedBreakableWall.damageTaken = 0;
        if (g_CastleFlags[RNO1_SECRET_WALL_BROKEN]) {
            self->step = 5;
        } else {
            tempEntity = self + 2;
            CreateEntityFromEntity(E_ID(WALL_SEGMENT), self, tempEntity);
            tempEntity->posY.i.hi += 0x18;
            tempEntity->params = 2;
            tempEntity = self + 1;
            CreateEntityFromEntity(E_ID(WALL_SEGMENT), self, tempEntity);
            tempEntity->posY.i.hi += 0x30;
            tempEntity->params = 1;
        }
        break;

    case 1:
        if (self->ext.segmentedBreakableWall.damageTaken > 8) {
            self->ext.segmentedBreakableWall.damageTaken = 0;
            for (i = 0; i < 5; i++) {
                tempEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
                if (tempEntity != NULL) {
                    CreateEntityFromEntity(E_ID(WALL_PARTICLES), self, tempEntity);
                    tempEntity->posX.i.hi -= 0x10;
                    tempEntity->posY.i.hi += 0x30;
                    tempEntity->params = i;
                }
            }
            if (self->animCurFrame < 0x4D) {
                self->animCurFrame++;
            }
        }
        if (self->ext.segmentedBreakableWall.pieceBroken) {
            PlaySfxPositional(SFX_WALL_DEBRIS_B);
            self->step_s = 0;
            self->step = self->ext.segmentedBreakableWall.pieceBroken + 1;
            if (self->ext.segmentedBreakableWall.pieceBroken == 3) {
                self->step = 2;
            }
        }
        break;

    case 2:
        self->animCurFrame = 0x4F;
        if (self->ext.segmentedBreakableWall.pieceBroken & 2) {
            PlaySfxPositional(SFX_WALL_DEBRIS_B);
            self->step = 4;
        }
        break;

    case 3:
        self->animCurFrame = 0x4E;
        if (self->ext.segmentedBreakableWall.pieceBroken & 1) {
            PlaySfxPositional(SFX_WALL_DEBRIS_B);
            self->step = 4;
        }
        break;

    case 4:
        self->animCurFrame = 0x50;
        g_CastleFlags[RNO1_SECRET_WALL_BROKEN] = 1;
        tempEntity = AllocEntity(&g_Entities[160], &g_Entities[192]);
        if (tempEntity != NULL) {
            CreateEntityFromEntity(E_EQUIP_ITEM_DROP, self, tempEntity);
            tempEntity->params = ITEM_DIM_SUM_SET;
            tempEntity->posY.i.hi += 0x30;
        }
        self->step++;
        break;
    default:
        self->animCurFrame = 0x50;
        break;
    }
    animFrame = self->animCurFrame - 0x4B;
    for (i = 0; i < 6; i++) {
        tilePos = tilePositions[i];
        g_Tilemap.fg[tilePos] = tiles[animFrame][i];
    }
}

void EntityBreakableWallSegment(Entity* self) {
    Entity* tempEntity;
    s32 i;

    if (self->hitParams) {
        PlaySfxPositional(SFX_EXPLODE_FAST_B);
    }

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitWallSegment);
        self->hitPoints = 0x18;
        self->hitboxWidth = 0x10;
        self->hitboxHeight = 0xC;
        self->hitboxState = 2;
        self->ext.segmentedBreakableWall.hitPoints = self->hitPoints;
        self->hitboxOffY = 0xC;
        break;

    case 1:
        if (self->hitPoints ^ self->ext.segmentedBreakableWall.hitPoints) {
            (self - self->params)->ext.segmentedBreakableWall.damageTaken +=
                self->ext.segmentedBreakableWall.hitPoints - self->hitPoints;
            self->ext.segmentedBreakableWall.hitPoints = self->hitPoints;
        }
        if (self->flags & FLAG_DEAD) {
            (self - self->params)->ext.segmentedBreakableWall.pieceBroken |=
                self->params;
            self->step++;
        }
        break;

    case 2:
        switch (self->step_s) {
        case 0:
            tempEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (tempEntity != NULL) {
                CreateEntityFromEntity(E_EXPLOSION, self, tempEntity);
                tempEntity->posY.i.hi += 8;
                tempEntity->params = 0x13;
            }

            for (i = 0; i < 3; i++) {
                tempEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
                if (tempEntity != NULL) {
                    CreateEntityFromEntity(
                        E_INTENSE_EXPLOSION, self, tempEntity);
                    tempEntity->posX.i.hi -= (i * 0x10) - 0x10;
                    tempEntity->params = 0x10;
                }
            }

            for (i = 0; i < 5; i++) {
                tempEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
                if (tempEntity != NULL) {
                    CreateEntityFromEntity(E_ID(WALL_DEBRIS), self, tempEntity);
                    tempEntity->posX.i.hi -= (i * 8) - 0x10 + (Random() & 3);
                    tempEntity->posY.i.hi += (Random() & 7) + 0x14;
                    tempEntity->params = i;
                }
            }
            self->step_s++;
            break;
        }
        break;
    }
}

void EntityWallParticles(Entity* self) {
    Primitive* prim;
    s32 primIndex;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitParticle);
        self->animSet = 8;
        self->animCurFrame = 1;
        self->palette = PAL_FLAG(0x4);
        return;

    case 1:
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 2);
        if (primIndex != -1) {
            self->flags |= FLAG_HAS_PRIMS;
            self->primIndex = primIndex;
            prim = &g_PrimBuf[primIndex];
            self->ext.prim = prim;
#ifdef VERSION_PSP
            UnkPolyFunc2(prim);
#else
            UnkPolyFunc2(prim, primIndex);
#endif

            prim->tpage = 0xE;
            prim->clut = 2;
            prim->u0 = 0x70;
            prim->u1 = 0x78;
            prim->u2 = prim->u0;
            prim->u3 = prim->u1;
            prim->v0 = 0xF6;
            prim->v1 = prim->v0;
            prim->v2 = 0xFD;
            prim->v3 = prim->v2;
            prim->priority = self->zPriority;
            prim->drawMode = DRAW_UNK02;

            prim->next->x1 = self->posX.i.hi;
            prim->next->y0 = self->posY.i.hi;
            *(u16*)&prim->next->r2 = 4;
            *(u16*)&prim->next->b2 = 4;
            prim->next->b3 = 0x80;
        } else {
            DestroyEntity(self);
            return;
        }

        self->velocityX = g_Rno1DebrisVelocities[self->params][0];
        self->velocityY = g_Rno1DebrisVelocities[self->params][1];
        self->step++;
        return;

    case 2:
        prim = self->ext.prim;
        LOH(prim->next->tpage) += 0x180;
        prim->next->x1 = self->posX.i.hi;
        prim->next->y0 = self->posY.i.hi;
        UnkPrimHelper(prim);
        if (AnimateEntity(g_Rno1DebrisAnim, self) == 0) {
            self->animCurFrame = 0;
        }
        if (UnkCollisionFunc5(g_Rno1DebrisCollisionSensors) != 0) {
            DestroyEntity(self);
            return;
        }
        self->velocityY -= FIX(0.0625);
        return;
    }
}

void EntityBreakableWallDebris(Entity* self) {
    Collider collider;
    Entity* tempEntity;
    Primitive* prim;
    s32 primIndex;
    s16 posX, posY;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitParticle);
        self->animSet = 8;
        self->animCurFrame = 1;
        self->palette = PAL_FLAG(4);
        break;

    case 1:
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 2);
        if (primIndex != -1) {
            self->flags |= FLAG_HAS_PRIMS;
            self->primIndex = primIndex;
            prim = &g_PrimBuf[primIndex];
            self->ext.segmentedBreakableWall.prim = prim;
            UnkPolyFunc2(prim);
            prim->tpage = 0xE;
            prim->clut = 2;
            prim->u0 = 0x70;
            prim->u1 = 0x78;
            prim->u2 = prim->u0;
            prim->u3 = prim->u1;
            prim->v0 = 0xF6;
            prim->v1 = prim->v0;
            prim->v2 = 0xFD;
            prim->v3 = prim->v2;
            prim->priority = self->zPriority;
            prim->drawMode = DRAW_UNK02;

            prim->next->x1 = self->posX.i.hi;
            prim->next->y0 = self->posY.i.hi;
            LOH(prim->next->r2) = g_Rno1WallDebrisSizes[self->params];
            LOH(prim->next->b2) = LOH(prim->next->r2);
            prim->next->b3 = 0x80;
        } else {
            DestroyEntity(self);
            return;
        }

        self->velocityX = g_Rno1WallDebrisVelocities[self->params][0];
        self->velocityY = g_Rno1WallDebrisVelocities[self->params][1];
        self->step++;
        break;

    case 2:
        prim = self->ext.segmentedBreakableWall.prim;
        LOH(prim->next->tpage) += g_Rno1WallDebrisRotations[self->params];
        prim->next->x1 = self->posX.i.hi;
        prim->next->y0 = self->posY.i.hi;
        UnkPrimHelper(prim);
        if (!AnimateEntity(g_Rno1DebrisAnim, self)) {
            self->animCurFrame = 0;
        }
        MoveEntity();
        self->velocityY += FIX(0.125);
        if (self->velocityY < 0) {
            break;
        }

        posX = self->posX.i.hi;
        posY = self->posY.i.hi;
        posY += (LOH(prim->next->r2) / 2) - 2;
        g_api.CheckCollision(posX, posY, &collider, 0);
        if (collider.effects & EFFECT_SOLID) {
            self->posY.i.hi += collider.unk18;
            self->velocityX += FIX(0.25);
            self->velocityY = -self->velocityY / 2;
            if (self->velocityY > FIX(-0.25)) {
                if (LOH(prim->next->r2) > 6) {
                    tempEntity =
                        AllocEntity(&g_Entities[224], &g_Entities[256]);
                    if (tempEntity != NULL) {
                        CreateEntityFromEntity(
                            E_INTENSE_EXPLOSION, self, tempEntity);
                        tempEntity->params = 0x10;
                    }
                }
                DestroyEntity(self);
                return;
            }
        }
        break;
    }
}

// Secret elevator inside chicken wall
// Stand still for ~20 seconds to activate
void EntitySecretElevator(Entity* self) {
    Collider collider;
    s32 tilePos;
    s32 i;
    u8 collision;
    s16 posX, posY;

    Entity* player = &PLAYER;

    collision = GetPlayerCollisionWith(self, 16, 8 - self->params, 4);
    
    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitSecretElevator);
        self->blendMode = BLEND_TRANSP | BLEND_ADD;
        self->zPriority = 0x6A;
        if (self->params) {
            if (collision) {
                self->step = 3;
                tilePos = 0x31;
                for (i = 0; i < 2; i++) {
                    g_Tilemap.fg[tilePos] = 0x4BD;
                    tilePos++;
                }
            } else {
                tilePos = 0xCD;
                for (i = 0; i < 2; i++) {
                    g_Tilemap.fg[tilePos] = 0x3FE;
                    tilePos++;
                }
                self->step = 5;
            }
            break;
        }
        for (i = 6; i < 8; i++) {
            tilePos = tilePositions[i];
            g_Tilemap.fg[tilePos] = tiles[4][i];
        }
        if (elevatorBool) {
            self->posY.i.hi = 0xEE - g_Tilemap.scrollY.i.hi;
            collision = GetPlayerCollisionWith(self, 16, 8 - self->params, 4);
            if (collision) {
                g_Player.padSim = 0;
                g_Player.demo_timer = 2;
                self->step = 6;
                for (i = 6; i < 8; i++) {
                    tilePos = tilePositions[i];
                    g_Tilemap.fg[tilePos] = tiles[5][i];
                }
            }
        }
        break;

    case 1:
        break;

    case 2:
        if (!self->params) {
            for (i = 0; i < 8; i++) {
                tilePos = tilePositions[i];
                g_Tilemap.fg[tilePos] = tiles[5][i];
            }
        }
        g_Player.padSim = 0;
        g_Player.demo_timer = 2;
        elevatorBool = true;
        g_api.PlaySfx(SFX_BAD_LUCK_JINGLE);
        self->step++;
        break;

    case 3:
        g_Player.demo_timer = 2;
        self->posY.i.hi++;
        if (collision) {
            player->posY.i.hi++;
            g_unkGraphicsStruct.shoveY.i.hi += 1;
            g_api.func_8010DFF0(0, 1);
        }
        if (self->params) {
            posX = self->posX.i.hi;
            posY = self->posY.i.hi + 8;
            g_api.CheckCollision(posX, posY, &collider, 0);
            FntPrint("vram %x\n", collider.effects);
            if (collider.effects & EFFECT_SOLID) {
                g_Player.demo_timer = 0;
                self->step++;
            }
        }
        break;

    case 4:
        tilePos = 0xCD;
        for (i = 0; i < 2; i++) {
            g_Tilemap.fg[tilePos] = 0x3FE;
            tilePos++;
        }
        if (!collision) {
            self->step++;
        }
        break;

    case 5:
        break;
    case 6:
        g_Player.demo_timer = 2;
        self->posY.i.hi--;
        if (collision) {
            player->posY.i.hi--;
            g_unkGraphicsStruct.shoveY.i.hi -= 1;
            g_api.func_8010DFF0(0, 1);
        }
        posY = self->posY.i.hi + g_Tilemap.scrollY.i.hi;
        if (posY < 0xC7) {
            self->posY.i.hi = 0xC7 - g_Tilemap.scrollY.i.hi;
            elevatorBool = false;
            for (i = 6; i < 8; i++) {
                tilePos = tilePositions[i];
                g_Tilemap.fg[tilePos] = tiles[4][i];
            }
            self->step = 1;
        }
        break;
    }
}
