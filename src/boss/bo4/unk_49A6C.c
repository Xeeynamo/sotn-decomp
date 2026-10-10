// SPDX-License-Identifier: AGPL-3.0-or-later
#include "bo4.h"
#include "../../dra/subwpn_dagger.h"

// Used in dra/7E4BC, dra/bss, rbo5/unk_4648C, bo4/unk_49A6C
typedef struct {
    f32 posX;
    f32 posY;
    s16 angle1;
    s16 angle2;
    s16 size;
    s16 xOffset;
    s16 yOffset;
    s16 pad;
} mistStruct; // size = 0x14

Entity* CreateEntFactoryFromEntity(Entity* source, u32 factoryParams, s16 arg2);
void SetDopplegangerAnim(u8 anim);
bool func_us_801C6040(s32 branchFlags);
void func_8010FAF4();

extern PlayerState g_Dop;
extern s32 D_us_801805A0;
extern u_long D_us_801D421C[];
extern s32 D_us_801D4A1C;

#ifndef VERSION_PC
#include "../../get_free_entity.h"
#endif

// this is the same as unionD_800ACFB4 in DRA
typedef union {
    u8 rawBytes[4];
    AnimationFrame af;
} unionD_us_8018136C;
static AnimationFrame* g_DopEmptyAnimGroup[ZERO_LEN] = {};
static unionD_us_8018136C D_us_8018136C[] = {
    {.rawBytes =
         {
             0x10,
             0x7F,
             0x3F,
             0x00,
         }},
    {.rawBytes =
         {
             0x10,
             0x7F,
             0x00,
             0x00,
         }},
    {.rawBytes =
         {
             0x10,
             0x3F,
             0x3F,
             0x3F,
         }},
    {.rawBytes =
         {
             0x10,
             0x5F,
             0x2F,
             0x00,
         }},
    {.rawBytes =
         {
             0x0C,
             0x7F,
             0x3F,
             0x00,
         }},
    {.rawBytes =
         {
             0x0C,
             0x7F,
             0x3F,
             0x7F,
         }},
    {.rawBytes =
         {
             0x02,
             0x7F,
             0x3F,
             0x7F,
         }},
    {.rawBytes =
         {
             0x06,
             0x00,
             0x3F,
             0x7F,
         }},
    {.rawBytes =
         {
             0x06,
             0x3F,
             0x3F,
             0x3F,
         }},
    {.rawBytes =
         {
             0x10,
             0x3F,
             0x3F,
             0x7F,
         }},
    {.rawBytes =
         {
             0x10,
             0xFF,
             0xFF,
             0xFF,
         }},
    {.rawBytes =
         {
             0x12,
             0x7F,
             0x00,
             0x00,
         }},
    {.rawBytes =
         {
             0x12,
             0x7F,
             0x7F,
             0x7F,
         }},
};

// some kind of timer
static u8 D_us_801D3D4C;
STATIC_PAD_BSS(3);
static u8 D_us_801D3D50;
STATIC_PAD_BSS(3);
static u8 D_us_801D3D54;
STATIC_PAD_BSS(3);
static u8 D_us_801D3D58;
STATIC_PAD_BSS(3);

void func_80118C28(s32 arg0) {
    // Break up the 4-byte struct D_us_8018136C[arg0] into individual bytes.
    D_us_801D3D4C = D_us_8018136C[arg0].rawBytes[0];
    D_us_801D3D50 = D_us_8018136C[arg0].rawBytes[1];
    D_us_801D3D54 = D_us_8018136C[arg0].rawBytes[2];
    D_us_801D3D58 = D_us_8018136C[arg0].rawBytes[3];
}

static u8 D_us_801813A0[] = {
    0x00, 0x50, 0x10, 0x50, 0x00, 0x60, 0x10, 0x60, 0x10, 0x50, 0x20, 0x50,
    0x10, 0x60, 0x20, 0x60, 0x70, 0x40, 0x80, 0x40, 0x70, 0x50, 0x80, 0x50,
    0x70, 0x30, 0x78, 0x30, 0x70, 0x38, 0x78, 0x38, 0x78, 0x30, 0x80, 0x30,
    0x78, 0x38, 0x80, 0x38, 0x70, 0x38, 0x78, 0x38, 0x77, 0x40, 0x78, 0x40,
};

static s32 func_80119E78(Primitive* prim, s16 xCenter, s16 yCenter) {
    s16 right;
    s16 size;
    u8* idx;

    // D_us_801813A0 is a read-only array of bytes in 8-byte groups.
    // These are sets of 4 pairs of u,v values.
    // the ->b0 value is very likely fake.
    idx = D_us_801813A0;
    idx += prim->b0 * 8;
    if (prim->b0 >= 3) {
        size = 4;
    } else {
        size = 6;
    }
    if (prim->b0 == 6) {
        return -1;
    }
    prim->x0 = xCenter - size;
    prim->y0 = yCenter - size;
    prim->x1 = xCenter + size;
    prim->y1 = yCenter - size;
    prim->x2 = xCenter - size;
    prim->y2 = yCenter + size;
    prim->x3 = xCenter + size;
    prim->y3 = yCenter + size;

    prim->u0 = *idx++;
    prim->v0 = *idx++;
    prim->u1 = *idx++;
    prim->v1 = *idx++;
    prim->u2 = *idx++;
    prim->v2 = *idx++;
    prim->u3 = *idx++;
    prim->v3 = *idx;
    prim->b1++;
    if (!(prim->b1 & 1)) {
        prim->b0++;
    }
    return 0;
}

static Point16 D_us_801D3D5C[16];

void DopEntityHitByHoly(Entity* self) {
    s32 shouldHide;
    s16 xRand;
    s16 yRand;
    s32 i;
    s16 hitboxX;
    s16 hitboxY;
    Primitive* prim;

    switch (self->step) {
    case 0:
        self->primIndex = g_api.AllocPrimitives(PRIM_GT4, LEN(D_us_801D3D5C));
        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags = FLAG_HAS_PRIMS | FLAG_POS_CAMERA_LOCKED;
        hitboxX = DOPPLEGANGER.posX.i.hi + DOPPLEGANGER.hitboxOffX;
        hitboxY = DOPPLEGANGER.posY.i.hi + DOPPLEGANGER.hitboxOffY;
        prim = &g_PrimBuf[self->primIndex];
        for (i = 0; i < LEN(D_us_801D3D5C); i++) {
            xRand = hitboxX + rand() % 24 - 12;
            yRand = hitboxY + rand() % 48 - 24;
            D_us_801D3D5C[i].x = xRand;
            D_us_801D3D5C[i].y = yRand;
            prim->clut = PAL_UNK_1B2;
            prim->tpage = 0x1A;
            prim->b0 = 0;
            prim->b1 = 0;
            prim->g0 = 0;
            prim->g1 = (rand() & 7) + 1;
            prim->g2 = 0;
            prim->priority = DOPPLEGANGER.zPriority + 4;
            prim->drawMode = DRAW_UNK_100 | DRAW_TPAGE | DRAW_HIDE |
                             DRAW_UNK02 | DRAW_TRANSP;
            if (rand() & 1) {
                prim->drawMode =
                    DRAW_UNK_100 | DRAW_UNK_40 | DRAW_TPAGE2 | DRAW_TPAGE |
                    DRAW_HIDE | DRAW_UNK02 | DRAW_TRANSP;
            }
            prim = prim->next;
        }
        self->step++;
        break;

    case 1:
        if (!(g_Dop.status & PLAYER_STATUS_UNK10000)) {
            DestroyEntity(self);
            return;
        }
    }

    prim = &g_PrimBuf[self->primIndex];
    for (i = 0; i < LEN(D_us_801D3D5C); i++) {
        switch (prim->g0) {
        case 0:
            if (--prim->g1 == 0) {
                prim->g0++;
            }
            break;
        case 1:
            hitboxX = D_us_801D3D5C[i].x;
            hitboxY = D_us_801D3D5C[i].y;
            shouldHide = func_80119E78(prim, hitboxX, hitboxY);
            D_us_801D3D5C[i].y--;
            if (shouldHide < 0) {
                prim->drawMode |= DRAW_HIDE;
                prim->g0++;
            } else {
                prim->drawMode &= ~DRAW_HIDE;
            }
            break;
        }
        prim = prim->next;
    }
}

void PrintDummySet(Entity* self) { FntPrint("dummy set\n"); }

void func_us_801CA2AC(Entity*);
void EntitySmokePuff(Entity*);
void EntityGravityBootBeam(Entity*);
void EntitySubwpnKnife(Entity*);
void func_us_801CD178(Entity*);
void EntityDopplegangerBlinkWhite(Entity*);
void func_us_801CD89C(Entity*);
void EntitySubwpnReboundStone(Entity*);
void DopEntityHitByLightning(Entity*);
void EntityDopplegangerOutline(Entity*);
void EntityDopplegangerDissolves(Entity*);
void EntityHitByIce(Entity*);
void EntityMist(Entity*);
void EntityWingSmashTrail(Entity*);
void func_us_801CA748(Entity*);
void DopEntityHitByHoly(Entity*);
void DopEntityHitByDark(Entity*);
void DopplegangerUnarmedAttack(Entity*);

static PfnEntityUpdate D_us_801813D0[] = {
    PrintDummySet,
    func_us_801CA2AC,
    EntitySmokePuff,
    EntityGravityBootBeam,
    EntitySubwpnKnife,
    func_us_801CD178,
    PrintDummySet,
    PrintDummySet,
    PrintDummySet,
    PrintDummySet,
    PrintDummySet,
    EntityDopplegangerBlinkWhite,
    PrintDummySet,
    PrintDummySet,
    PrintDummySet,
    PrintDummySet,
    func_us_801CD89C,
    PrintDummySet,
    PrintDummySet,
    PrintDummySet,
    EntitySubwpnReboundStone,
    PrintDummySet,
    PrintDummySet,
    PrintDummySet,
    PrintDummySet,
    PrintDummySet,
    PrintDummySet,
    PrintDummySet,
    PrintDummySet,
    PrintDummySet,
    DopEntityHitByLightning,
    EntityDopplegangerOutline,
    EntityDopplegangerDissolves,
    EntityHitByIce,
    EntityMist,
    EntityWingSmashTrail,
    func_us_801CA748,
    PrintDummySet,
    PrintDummySet,
    PrintDummySet,
    PrintDummySet,
    PrintDummySet,
    PrintDummySet,
    PrintDummySet,
    PrintDummySet,
    PrintDummySet,
    PrintDummySet,
    DopEntityHitByHoly,
    PrintDummySet,
    PrintDummySet,
    PrintDummySet,
    PrintDummySet,
    PrintDummySet,
    PrintDummySet,
    DopEntityHitByDark,
    DopplegangerUnarmedAttack,
};

void func_us_801CA014(void) {
    Entity* entity;
    PfnEntityUpdate entityUpdate;
    s32 i;

    entity = g_CurrentEntity = &g_Entities[E_ID_44];

    for (i = E_ID_44; i < E_ID_90; i++, g_CurrentEntity++, entity++) {
        if (i == 16 && entity->entityId == 0) {
            g_Dop.unk48 = 0;
        }

        if (entity->entityId == 0) {
            continue;
        }

        entityUpdate = D_us_801813D0[entity->entityId];
        entityUpdate(entity);

        entity = g_CurrentEntity;
        if (entity->entityId != 0) {
            if (!(entity->flags & FLAG_UNK_10000000) &&
                (entity->posX.i.hi > 288 || entity->posX.i.hi < -32 ||
                 entity->posY.i.hi > 256 || entity->posY.i.hi < -16)) {
                DestroyEntity(g_CurrentEntity);
            } else {
                if (entity->flags & FLAG_UNK_20000000) {
                    UpdateAnim(0, g_DopEmptyAnimGroup);
                }
                entity->flags |= FLAG_NOT_AN_ENEMY;
            }
        }
    }

    if (D_us_801D3D4C) {
        D_us_801D3D4C--;
        if (D_us_801D3D4C & 1) {
            g_api.func_800EA5AC(1, D_us_801D3D50, D_us_801D3D54, D_us_801D3D58);
        }
    }

    if (g_Dop.status & (PLAYER_STATUS_DEAD | PLAYER_STATUS_UNK80000)) {
        FntPrint("dead boss\n");
        entity = &g_Entities[E_ID_44];
        for (i = E_ID_44; i < E_ID_90; i++, entity++) {
            entity->hitboxState = 0;
        }
    }
}

Entity* CreateEntFactoryFromEntity(
    Entity* source, u32 factoryParams, s16 arg2) {
    Entity* newFactory = GetFreeEntity(E_ID_44, E_ID_50);

    if (newFactory == NULL) {
        return NULL;
    }

    DestroyEntity(newFactory);
    newFactory->entityId = E_FACTORY;
    newFactory->ext.factory.parent = source;
    newFactory->posX.val = source->posX.val;
    newFactory->posY.val = source->posY.val;
    newFactory->facingLeft = source->facingLeft;
    newFactory->zPriority = source->zPriority;
    newFactory->params = factoryParams & 0xFFF;
    newFactory->ext.factory.paramsBase = (factoryParams & 0xFF0000) >> 8;
    return newFactory;
}

Entity* GetFreeEntityReverse(s16 start, s16 end);

#define B_MAKE(entityId, amount, nPerCycle, isNonCritical, incParamsKind,      \
               timerCycle, kind, origin, timerDelay)                           \
    {(entityId),                                                               \
     (amount),                                                                 \
     ((nPerCycle) & 0x3F) | ((!!(incParamsKind)) << 6) |                       \
         ((!!(isNonCritical)) << 7),                                           \
     (timerCycle),                                                             \
     ((kind) & 0xF) | (((origin) & 0xF) << 3),                                 \
     timerDelay}

static FactoryBlueprint D_us_801814B0[] = {
#include "gen/blueprints.h"
};
STATIC_ASSERT(LEN(D_us_801814B0) == NUM_BLUEPRINTS, "bp array wrong size");
static u8 D_us_80181764[NUM_BLUEPRINT_KIND][2] = {
    {0x60, 0x8F}, {0x51, 0x6F}, {0x60, 0x6F}, {0x50, 0x50}, {0x5C, 0x5F},
    {0x59, 0x5F}, {0x51, 0x5F}, {0x51, 0x8F}, {0x51, 0x7F}, {0x6F, 0x6F},

};

void func_us_801CA2AC(Entity* self) {
    Entity* newEntity;
    s16 i;
    s16 n;
    s16 endIndex;
    s16 startIndex;
    u8* data;

    if (self->step == 0) {
        data = (u8*)&D_us_801814B0[self->params];
        self->ext.factory.newEntityId = *data++;
        self->ext.factory.amount = *data++;
        self->ext.factory.nPerCycle = *data & 0x3F;
        self->ext.factory.isNonCritical = (s16)(*data >> 7) & 1;
        self->ext.factory.incParamsKind = (s16)(*data++ >> 6) & 1;
        self->ext.factory.tCycle = *data++;
        self->ext.factory.kind = *data & 0xF;
        self->ext.factory.origin = (s16)(*data++ >> 4) & 0xF;
        self->ext.factory.delay = *data;
        self->flags |= FLAG_UNK_10000000;

        self->step++;

        switch (self->ext.factory.origin) {
        case B_ORIGIN_DEFAULT:
        case B_ORIGIN_6:
            self->flags |= FLAG_POS_CAMERA_LOCKED;
            break;
        case B_ORIGIN_2:
        case B_ORIGIN_4:
        case B_ORIGIN_5:
        case B_ORIGIN_7:
            self->posX.val = DOPPLEGANGER.posX.val;
            self->posY.val = DOPPLEGANGER.posY.val;
            break;
        }
    } else {
        switch (self->ext.factory.origin) {
        case B_ORIGIN_DEFAULT:
        case B_ORIGIN_1:
        case B_ORIGIN_3:
        case B_ORIGIN_5:
        case B_ORIGIN_6:
            break;
        case B_ORIGIN_2:
            self->posX.val = DOPPLEGANGER.posX.val;
            self->posY.val = DOPPLEGANGER.posY.val;
            break;
        case B_ORIGIN_4:
            self->posX.val = DOPPLEGANGER.posX.val;
            self->posY.val = DOPPLEGANGER.posY.val;
            if (DOPPLEGANGER.step != Dop_Walk) {
                self->entityId = 0;
                return;
            }
            break;
        case B_ORIGIN_7:
            self->posX.val = DOPPLEGANGER.posX.val;
            self->posY.val = DOPPLEGANGER.posY.val;
            if (DOPPLEGANGER.step != Dop_Hit) {
                self->entityId = 0;
                return;
            }
            break;
        }
    }

    if (self->ext.factory.delay) {
        if (--self->ext.factory.delay) {
            return;
        }
        self->ext.factory.delay = self->ext.factory.tCycle;
    }

    // Save this value so we don't have to re-fetch on every for-loop cycle
    n = self->ext.factory.nPerCycle;
    for (i = 0; i < n; i++) {

        // !FAKE, this should probably be &entity_ranges[unk9C] or similar,
        // instead of doing &entity_ranges followed by +=
        data = (u8*)&D_us_80181764[0];
        data += self->ext.factory.kind * 2;

        startIndex = *data++;
        endIndex = *data;

        if (self->ext.factory.kind == 3) {
            DestroyEntity(&g_Entities[startIndex]);
            newEntity = &g_Entities[startIndex];
            g_Dop.unk48 = 0;
        } else if (self->ext.factory.kind == 0) {
            newEntity = GetFreeEntityReverse(startIndex, endIndex + 1);
        } else if (self->ext.factory.kind == 8) {
            if ((self->ext.factory.spawnIndex % 3) == 0) {
                newEntity = GetFreeEntity(81, 96);
            }
            if ((self->ext.factory.spawnIndex % 3) == 1) {
                newEntity = GetFreeEntity(96, 112);
            }
            if ((self->ext.factory.spawnIndex % 3) == 2) {
                newEntity = GetFreeEntity(112, 128);
            }
        } else {
            newEntity = GetFreeEntity(startIndex, endIndex + 1);
        }

        if (newEntity == NULL) {
            if (self->ext.factory.isNonCritical == 1) {
                self->entityId = 0;
            } else {
                self->ext.factory.delay = self->ext.factory.tCycle;
            }
            return;
        }

        DestroyEntity(newEntity);
        newEntity->entityId = self->ext.factory.newEntityId;
        newEntity->params = self->ext.factory.paramsBase;
        // The child  (newEntity) is not an ent factory, but because the factory
        // creates many entities, we can't pick a particular extension. But
        // we're not allowed to use generic, so i'll just reuse entFactory.
        newEntity->ext.factory.parent = self->ext.factory.parent;
        newEntity->posX.val = self->posX.val;
        newEntity->posY.val = self->posY.val;
        newEntity->facingLeft = self->facingLeft;
        newEntity->zPriority = self->zPriority;

        if (self->ext.factory.incParamsKind) {
            newEntity->params += self->ext.factory.spawnIndex;
        } else {
            newEntity->params += i;
        }

        self->ext.factory.spawnIndex++;

        if (self->ext.factory.spawnIndex == self->ext.factory.amount) {
            self->entityId = 0;
            return;
        }
    }
    self->ext.factory.delay = self->ext.factory.tCycle;
}

extern EInit D_us_80180434;

void func_us_801CA748(Entity* self) {
    if (DOPPLEGANGER.step_s != Dop_Crouch ||
        DOPPLEGANGER.step != Dop_MorphBat) {
        DestroyEntity(self);
        return;
    }

    if (self->step == 0) {
        InitializeEntity(D_us_80180434);
        if (g_Dop.status & PLAYER_STATUS_POISON) {
            self->attack = self->attack / 2;
        }
        self->hitboxOffX = 4;
        self->step++;
    }

    self->flags =
        FLAG_UNK_10000000 | FLAG_POS_CAMERA_LOCKED | FLAG_NOT_AN_ENEMY;
    self->facingLeft = DOPPLEGANGER.facingLeft;
    self->posY.i.hi = DOPPLEGANGER.posY.i.hi;
    self->posX.i.hi = DOPPLEGANGER.posX.i.hi;
}

static s16 D_us_80181778[] = {
    0, -4, -8, -12, -16, -20,
};
static s32 D_us_80181784[] = {
    FIX(-0.1875), FIX(-0.25), FIX(-0.375), FIX(-0.5), FIX(-0.625), FIX(-0.75),
};
static s16 D_us_8018179C[] = {
    0x30, 0x40, 0x50, 0x60, 0x70, 0x80,
};
static AnimationFrame D_us_801817A8[] = {
    POSE(1, 1, 0),  POSE(1, 2, 0),  POSE(1, 3, 0),  POSE(1, 4, 0),
    POSE(1, 5, 0),  POSE(1, 6, 0),  POSE(1, 7, 0),  POSE(1, 8, 0),
    POSE(1, 9, 0),  POSE(1, 10, 0), POSE(1, 11, 0), POSE(1, 12, 0),
    POSE(1, 13, 0), POSE(1, 14, 0), POSE(1, 15, 0), POSE(1, 16, 0),
    POSE(1, 17, 0), POSE(1, 18, 0), POSE(1, 19, 0), POSE(1, 20, 0),
    POSE(1, 21, 0), POSE(1, 22, 0), POSE(1, 23, 0), POSE(1, 24, 0),
    POSE_END,
};

static u8 D_us_8018180C[NUM_VERTICAL_SENSORS * 2] = {
    2, 9, 3, 10, 1, 8, 4, 11, 0, 7, 5, 12, 6, 13,
};

static u8 D_us_8018181C[10] = {
    2, 9, 3, 10, 4, 11, 5, 12, 6, 13,
};
extern Point16 g_DopSensorsWall[NUM_VERTICAL_SENSORS * 2];

void EntitySmokePuff(Entity* self) {
    byte stackpad[40];
    s16 posX;
    s32 i;
    s16 paramsLo;
    s16 paramsHi;

    switch (self->step) {
    case 0:
        paramsHi = self->params >> 8;
        paramsLo = self->params & 0xFF;
        self->animSet = 5;
        self->anim = D_us_801817A8;
        self->zPriority = DOPPLEGANGER.zPriority + 2;
        self->flags = FLAG_UNK_20000000 | FLAG_POS_CAMERA_LOCKED;
        self->palette = PAL_FLAG(PAL_UNK_195);
        self->blendMode = BLEND_TRANSP;
        self->drawFlags = ENTITY_SCALEY | ENTITY_SCALEX;

        posX = D_us_80181778[paramsLo];
        if (paramsHi == 0) {
            posX += 6;
        }
        if (paramsHi == 1) {
            posX -= 8;
        }
        if ((paramsHi == 2) || (paramsHi == 0xA)) {
            posX -= 2;
        }
        if (paramsHi == 5) {
            posX = -6;
        }
        if (paramsHi == 6) {
            posX = -24;
        }
        if (paramsHi == 3) {
            posX = (rand() % 30) - 0xE;
            paramsLo = (rand() & 3) + 2;
            self->posY.i.hi -= rand() % 4;
        }
        if (paramsHi == 7) {
            posX = (rand() % 60) - 0x1E;
            paramsLo = (rand() & 3) + 2;
            self->posY.i.hi -= rand() % 4;
        }
        if (paramsHi == 9) {
            posX = rand() % 16 - 8;
            paramsLo = (rand() & 3) + 2;
            self->posY.i.hi -= (20 + (rand() % 4));
        }
        if (paramsHi == 4) {
            for (i = paramsLo * 2; i < LEN(D_us_8018180C); i++) {
                if (g_Dop.colWall[D_us_8018180C[i]].effects & EFFECT_BLOCK) {
                    break;
                }
            }
            if (i == LEN(D_us_8018180C)) {
                DestroyEntity(self);
                return;
            }
            self->posX.i.hi =
                DOPPLEGANGER.posX.i.hi + g_DopSensorsWall[D_us_8018180C[i]].x;
            self->posY.i.hi =
                DOPPLEGANGER.posY.i.hi + g_DopSensorsWall[D_us_8018180C[i]].y;
            self->velocityY = FIX(-0.25);
            self->scaleX = D_us_8018179C[1] + 0x40;
            self->scaleY = self->scaleX;
            self->step++;
            return;
        }
        if (paramsHi == 8) {
            for (i = paramsLo * 2; i < LEN(D_us_8018181C); i++) {
                if (g_Dop.colWall[D_us_8018181C[i]].effects & EFFECT_BLOCK) {
                    break;
                }
            }
            if (i == LEN(D_us_8018181C)) {
                DestroyEntity(self);
                return;
            }
            self->posX.i.hi =
                DOPPLEGANGER.posX.i.hi + g_DopSensorsWall[D_us_8018181C[i]].x;
            self->posY.i.hi =
                DOPPLEGANGER.posY.i.hi + g_DopSensorsWall[D_us_8018181C[i]].y;
            self->velocityY = D_us_80181784[paramsLo];
            self->scaleX = D_us_8018179C[paramsLo] + 0x20;
            self->scaleY = self->scaleX;
            self->step++;
            return;
        }
        if (paramsHi == 1) {
            if (g_Dop.vram_flag & TOUCHING_ANY_SLOPE) {
                posX /= 2;
            }
        }
        if (paramsHi == 6) {
            if (DOPPLEGANGER.velocityX > 0) {
                posX = -posX;
            }
        } else {
            if (self->facingLeft) {
                posX = -posX;
            }
        }
        self->posX.i.hi += posX;
        self->posY.i.hi += 0x18;
        self->scaleX = D_us_8018179C[paramsLo] + 0x40;
        self->velocityY = D_us_80181784[paramsLo];
        if (paramsHi == 1) {
            self->velocityY = FIX(-0.25);
            SetSpeedX(-0x3000);
            self->scaleX = D_us_8018179C[1] + 0x40;
        }
        if (paramsHi == 5) {
            self->velocityY = D_us_80181784[4 - paramsLo * 2];
        }
        self->scaleY = self->scaleX;
        if (paramsHi == 10) {
            self->posY.i.hi -= 6;
        }
        self->step++;
        break;
    case 1:
        self->posY.val += self->velocityY;
        self->posX.val += self->velocityX;
        if (self->poseTimer < 0) {
            DestroyEntity(self);
        }
        break;
    }
}

static s32 D_us_801D3D9C;
static AnimationFrame D_us_80181828[14] = {
    POSE(2, 1, 0),  POSE(2, 2, 0),  POSE(2, 3, 0),  POSE(2, 4, 0),
    POSE(2, 5, 0),  POSE(2, 6, 0),  POSE(2, 7, 0),  POSE(2, 8, 0),
    POSE(2, 9, 0),  POSE(2, 10, 0), POSE(2, 11, 0), POSE(2, 12, 0),
    POSE(2, 13, 0), POSE_END,
};

void DopEntityHitByDark(Entity* self) {
    switch (self->step) {
    case 0:
        self->flags = FLAG_UNK_20000000 | FLAG_POS_CAMERA_LOCKED;
        self->unk5A = 0x79;
        self->animSet = ANIMSET_DRA(14);
        self->zPriority = DOPPLEGANGER.zPriority + 2;
        self->palette = PAL_FLAG(PAL_UNK_19F);

        if (D_us_801D3D9C & 1) {
            self->blendMode = BLEND_TRANSP | BLEND_QUARTER;
        } else {
            self->blendMode = BLEND_TRANSP;
        }
        D_us_801D3D9C++;
        self->opacity = 0xFF;
        self->drawFlags =
            ENTITY_SCALEX | ENTITY_SCALEY | ENTITY_MASK_R | ENTITY_MASK_G;
        self->scaleX = self->scaleY = 0x40;
        self->anim = D_us_80181828;

        self->posY.i.hi += ((rand() % 35) - 15);
        self->posX.i.hi += ((rand() % 20) - 10);
        self->velocityY = FIX(-0.375) - (rand() & 0x3FFF);
        self->step++;
        break;
    case 1:
        if (self->opacity > 16) {
            self->opacity -= 8;
        }
        self->posY.val += self->velocityY;
        self->scaleX += 8;
        self->scaleY += 8;
        if (self->poseTimer < 0) {
            DestroyEntity(self);
        }
        break;
    }
}

// Does any entity with the same ID and params already
// exist in the index range [0x50, 0x90)
static bool func_8011BD48(Entity* entity) {
    s16 objId = entity->entityId;
    s16 params = entity->params;
    Entity* e;
    s32 i;

    for (e = &g_Entities[E_ID_50], i = E_ID_50; i < E_ID_90; e++, i++) {
        if (objId == e->entityId && params == e->params && e != entity) {
            return true;
        }
    }

    return false;
}

extern AluFrame* D_us_801B0A78[];
extern s16* D_us_801B159C[];

s32 D_us_80181860[16] = {0};
s16 D_us_801818A0[36][10] = {
    {
        0x0000,
        0x0000,
        0x0000,
        0x015F,
        0x0100,
        0x0100,
        0x0100,
        0x0060,
        0x0031,
        0x0200,
    },
    {
        0x0000,
        0x0002,
        0x0006,
        0x015F,
        0x0100,
        0x0100,
        0x0100,
        0x0010,
        0x0031,
        0x0200,
    },
    {
        0x0000,
        0x0000,
        0x0000,
        0x015F,
        0x0100,
        0x0400,
        0x0400,
        0x0010,
        0x0031,
        0x0200,
    },
    {
        0x0000,
        0x0000,
        0x0000,
        0x015F,
        0x7100,
        0x0100,
        0x7000,
        0x0010,
        0x0031,
        0x0200,
    },
    {
        0x0000,
        0x0000,
        0x0000,
        0x015F,
        0x7100,
        0x7000,
        0x0100,
        0x0010,
        0x0031,
        0x0200,
    },
    {
        0x0000,
        0x0000,
        0x0000,
        0x015F,
        0x0100,
        0x7000,
        0x0200,
        0x0010,
        0x0031,
        0x0200,
    },
    {
        0x0000,
        0x0000,
        0x0000,
        0x015F,
        0x0100,
        0x7000,
        0x0100,
        0x7001,
        0x0031,
        0x0100,
    },
    {
        0x0000,
        0x0000,
        0x0000,
        0x015F,
        0x0100,
        0x0100,
        0x7000,
        0x0070,
        0x0031,
        0x0200,
    },
    {
        0x0000,
        0x0000,
        0x0000,
        0x0203,
        0x0200,
        0x0200,
        0x0080,
        0x0060,
        0x0031,
        0x0200,
    },
    {
        0x0000,
        0x0000,
        0x0000,
        0x015F,
        0x0100,
        0x0100,
        0x0100,
        0x0010,
        0x0031,
        0x0200,
    },
    {
        0x0000,
        0x0002,
        0x0006,
        0x015F,
        0x0100,
        0x0100,
        0x0100,
        0x0060,
        0x0031,
        0x0200,
    },
    {
        0x0000,
        0x0000,
        0x0000,
        0x015F,
        0x0100,
        0x7000,
        0x0100,
        0x0010,
        0x0031,
        0x0200,
    },
    {
        0x0000,
        0x0000,
        0x0000,
        0x015F,
        0x7100,
        0x0100,
        0x7000,
        0x0010,
        0x0031,
        0x0200,
    },
    {
        0x0000,
        0x0000,
        0x0000,
        0x015F,
        0x7100,
        0x7000,
        0x0100,
        0x0010,
        0x0031,
        0x0200,
    },
    {
        0x0000,
        0x0000,
        0x0000,
        0x015F,
        0x0400,
        0x0100,
        0x0400,
        0x7004,
        0x0031,
        0x0200,
    },
    {
        0x0000,
        0x0000,
        0x0000,
        0x015F,
        0x0100,
        0x7000,
        0x0200,
        0x7006,
        0x0031,
        0x0200,
    },
    {
        0x0000,
        0x0000,
        0x0000,
        0x015F,
        0x0100,
        0x0100,
        0x7000,
        0x0010,
        0x0031,
        0x0200,
    },
    {
        0x0000,
        0x0000,
        0x0000,
        0x0203,
        0x7400,
        0x0080,
        0x7400,
        0x0060,
        0x0031,
        0x0200,
    },
    {
        0x0000,
        0x0000,
        0x0000,
        0x015F,
        0x0200,
        0x0100,
        0x0400,
        0x7003,
        0x0031,
        0x0200,
    },
    {
        0x0000,
        0x0000,
        0x0000,
        0x0166,
        0x0100,
        0x0100,
        0x0100,
        0x7005,
        0x0031,
        0x0200,
    },
    {
        0x0000,
        0x0000,
        0x0000,
        0x015F,
        0x0100,
        0x0100,
        0x0100,
        0x0010,
        0x0031,
        0x0200,
    },
    {
        0x0000,
        0x0000,
        0x0000,
        0x015F,
        0x00C0,
        0x00C0,
        0x0100,
        0x0010,
        0x0031,
        0x0200,
    },
    {
        0x0008,
        0x0000,
        0x0004,
        0x0168,
        0x0100,
        0x0100,
        0x0100,
        0x7002,
        0x0051,
        0x0100,
    },
    {
        0x0000,
        0x0002,
        0x0009,
        0x0165,
        0x0100,
        0x0100,
        0x0100,
        0x7000,
        0x0051,
        0x0180,
    },
    {
        0x0000,
        0x0000,
        0x0000,
        0x015F,
        0x0200,
        0x0800,
        0x0800,
        0x7007,
        0x0031,
        0x0200,
    },
    {
        0x0000,
        0x0000,
        0x0000,
        0x015F,
        0x0200,
        0x0100,
        0x0200,
        0x7005,
        0x0031,
        0x0200,
    },
    {
        0x0000,
        0x0000,
        0x0000,
        0x015F,
        0x0100,
        0x0100,
        0x0100,
        0x7005,
        0x0031,
        0x0200,
    },
    {
        0x0000,
        0x0000,
        0x0000,
        0x015F,
        0x0100,
        0x0100,
        0x0100,
        0x7008,
        0x0031,
        0x0200,
    },
    {
        0x0000,
        0x0000,
        0x0000,
        0x015F,
        0x0100,
        0x0100,
        0x0100,
        0x7009,
        0x0031,
        0x0200,
    },
    {
        0x0000,
        0x0000,
        0x0000,
        0x015F,
        0x0100,
        0x0100,
        0x0100,
        0x700A,
        0x0031,
        0x0200,
    },
    {
        0x0000,
        0x0000,
        0x0000,
        0x015F,
        0x0100,
        0x0100,
        0x7000,
        0x0010,
        0x0031,
        0x0200,
    },
    {
        0x0000,
        0x0000,
        0x0000,
        0x015F,
        0x0400,
        0x0100,
        0x0400,
        0x0010,
        0x0031,
        0x0200,
    },
    {
        0x0000,
        0x0000,
        0x0000,
        0x0200,
        0x0040,
        0x0040,
        0x0040,
        0x0010,
        0x0031,
        0x0200,
    },
    {
        0x0000,
        0x0000,
        0x0000,
        0x0200,
        0x0040,
        0x0040,
        0x0040,
        0x0010,
        0x0031,
        0x0200,
    },
    {
        0x0008,
        0x0000,
        0x0008,
        0x0165,
        0x0100,
        0x0100,
        0x0100,
        0x7007,
        0x0051,
        0x0200,
    },
    {
        0x0000,
        0x0000,
        0x0000,
        0x0168,
        0x7100,
        0x7100,
        0x0200,
        0x7007,
        0x0031,
        0x0200,
    },
};

#ifdef VERSION_PSP
extern u8** doppleganger_sprites;
extern u8** bat_form_sprites;
#else
extern u8* doppleganger_sprites[];
extern u8** bat_form_sprites[];
#endif
s32 D_us_80181B70 = 0;

// player turns white for some sort of status effect
#ifdef VERSION_PSP
INCLUDE_ASM("boss/bo4_psp/nonmatchings/bo4/unk_49A6C", EntityDopplegangerBlinkWhite);
#else
void EntityDopplegangerBlinkWhite(Entity* self) {
    Primitive* prim;
    u8 var_s7;
    u8 var_s6;
    u8 sp7f;
    u8 sp7e;
    s16 sp7c;
    s16 sp7a;
    s16 xOffset;
    s16 yOffset;
    s16 sp78;
    s16 sp76;
    s16 sp74;
    s16 sp72;
    s16 posX;
    s16 posY;
    s16* sp5c;
    u8* sp58;
    s32 i;
    s32 sp54;
    s32 sp50;

    s16 maskedParams;
    s16 angle;
    s16 sp6e;
    s16* sp4c;
    s16 sp6c;
    s16 sp6a;
    s16 sp68;
    s16 sp66;
    s16 sp64;
    s16 sp62;
    s16 sp60;

    s32 sp40;
    Entity* sp3C;
    s32 sp38;

    maskedParams = (self->params & 0x7F00) >> 8;

    if (((maskedParams & 0x3F) != 0x1D) &&
        (g_Dop.status & PLAYER_STATUS_MIST_FORM)) {
        D_us_80181B70 = 0;
        DestroyEntity(self);
        return;
    }

    if ((D_us_80181B70) && maskedParams != 0x20 && maskedParams != 0x21 &&
        ((maskedParams & 0x3F) != 0x1D)) {
        DestroyEntity(self);
        return;
    }

    self->posY.i.hi = DOPPLEGANGER.posY.i.hi;
    self->posX.i.hi = DOPPLEGANGER.posX.i.hi;
    self->facingLeft = DOPPLEGANGER.facingLeft;
    if (DOPPLEGANGER.animSet == (s16)ANIMSET_OVL(1)) {
        sp5c = (s16*)D_us_801B0A78[DOPPLEGANGER.animCurFrame & 0x7FFF];
    }
    if (DOPPLEGANGER.animSet == (s16)ANIMSET_OVL(2)) {
        sp5c = D_us_801B159C[DOPPLEGANGER.animCurFrame & 0x7FFF];
    }
    if (!DOPPLEGANGER.animSet || (DOPPLEGANGER.animCurFrame & 0x7FFF) == 0) {
        DestroyEntity(self);
        return;
    }

    sp72 = *sp5c++;
    sp72 &= 0x7FFF;

    posX = self->posX.i.hi;
    posY = self->posY.i.hi;

    if (DOPPLEGANGER.animSet == (s16)ANIMSET_OVL(1)) {
        sp58 = doppleganger_sprites[sp72];
    }
    if (DOPPLEGANGER.animSet == (s16)ANIMSET_OVL(2)) {
        sp58 = bat_form_sprites[sp72];
    }

    var_s7 = 4;
    var_s6 = 1;
    sp7f = var_s7 + sp58[0];
    sp7e = var_s6 + sp58[1];
    xOffset = sp7f - var_s7;
    yOffset = sp7e - var_s6;
    sp7c = sp5c[0] + sp58[2];
    sp7a = sp5c[1] + sp58[3];

    self->rotate = DOPPLEGANGER.rotate;
    self->drawFlags = DOPPLEGANGER.drawFlags;
    self->scaleX = DOPPLEGANGER.scaleX;
    self->scaleY = DOPPLEGANGER.scaleY;
    self->rotPivotY = DOPPLEGANGER.rotPivotY;
    self->rotPivotX = DOPPLEGANGER.rotPivotX;

    sp4c = D_us_801818A0[maskedParams & 0x3F];
    switch (self->step) {
    case 0:
        if (func_8011BD48(self)) {
            DestroyEntity(self);
            return;
        }
        self->primIndex = g_api.AllocPrimitives(PRIM_GT4, 8);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags = FLAG_UNK_10000000 | FLAG_HAS_PRIMS;
        prim = &g_PrimBuf[self->primIndex];
        for (i = 0; i < 8; i++) {
            D_us_80181860[i] = i << 9;
            prim->tpage = 0x10;
            prim->clut = sp4c[3];
            prim->r0 = prim->b0 = prim->g0 = prim->r1 = prim->b1 = prim->g1 =
                prim->r2 = prim->b2 = prim->g2 = prim->r3 = prim->b3 =
                    prim->g3 = 0x80;
            prim->priority = DOPPLEGANGER.zPriority + 2;

            prim->drawMode = sp4c[8] + DRAW_COLORS + DRAW_UNK02;
            prim = prim->next;
        }
        self->ext.playerBlink.unk8A = sp4c[9];
        self->ext.playerBlink.unk90 = 0;
        self->ext.playerBlink.unk98 = 0;
        self->ext.playerBlink.unk9A = 0x100;
        self->step++;
        if (maskedParams == 0x20) {
            self->step = 8;
        }
        if (maskedParams == 0x21) {
            self->step = 0xA;
        }
        break;
    case 1:
        if (sp4c[7] == 0x7008) {
            self->ext.playerBlink.unk90 += 0x50;
        } else {
            self->ext.playerBlink.unk90 += 0xA;
        }
        if (self->ext.playerBlink.unk90 > 0x100) {
            self->ext.playerBlink.unk90 = 0x100;
            self->ext.playerBlink.unk80 = sp4c[7];
            self->step++;
        }
        break;
    case 2:
        if (sp4c[7] >= 0x7000) {
            self->ext.playerBlink.unk80 = 8;
            switch ((u32)sp4c[7]) {
            case 0x7000:
                if (g_Dop.timers[ALU_T_CURSE] == 0) {
                    self->step++;
                }
                break;
            case 0x7001:
            case 0x7007:
                if (DOPPLEGANGER.step != Dop_Hit) {
                    self->step++;
                }
                break;
            case 0x7005:
            case 0x7006:
                if (DOPPLEGANGER.ext.player.anim != 0xC0) {
                    self->step++;
                }
                break;
            case 0x7008:
                if ((g_Dop.status & PLAYER_STATUS_UNK400000) == 0) {
                    self->step++;
                }
                break;
            case 0x7009: // Hold this step until player is out of state (5,3)
                // This state corresponds to wing smashing.
                if (DOPPLEGANGER.step_s != 3 ||
                    DOPPLEGANGER.step != Dop_MorphBat) {
                    self->step++;
                }
            }
        }
        if (--self->ext.playerBlink.unk80 == 0) {
            self->step++;
        }
        break;
    case 3:
        self->ext.playerBlink.unk90 -= 10;
        if (self->ext.playerBlink.unk90 < 0) {
            DestroyEntity(self);
            return;
        }
        break;
    case 8:
        D_us_80181B70 = 1;
        self->ext.playerBlink.unk98 += 8;
        self->ext.playerBlink.unk9C += 256;
        if (self->ext.playerBlink.unk98 > 128) {
            self->ext.playerBlink.unk98 = 128;
            g_Dop.unk66 = 2;
            self->step++;
        }
        break;
    case 9:
    case 11:
        self->ext.playerBlink.unk98 -= 8;
        self->ext.playerBlink.unk9C += 0x100;
        if (self->ext.playerBlink.unk98 < 0) {
            g_Dop.unk66 = 3;
            self->params = 0x1B00;
            self->step = 1;
            prim = &g_PrimBuf[self->primIndex];
            for (i = 0; i < 8; i++) {
                prim->clut = PAL_FILL_WHITE;
                prim = prim->next;
            }
            D_us_80181B70 = 0;
            return;
        }
        break;
    case 10:
        D_us_80181B70 = 1;
        self->ext.playerBlink.unk98 += 8;
        self->ext.playerBlink.unk9C += 0x100;
        if (self->ext.playerBlink.unk98 > 0x80) {
            self->ext.playerBlink.unk98 = 0x80;
        }
        if (g_Dop.unk66 == 1) {
            self->step++;
        }
        break;
    }

    sp78 = self->ext.playerBlink.unk9C;
    sp76 = self->ext.playerBlink.unk98;
    sp54 = 3;
    sp50 = 6;
    if (sp4c[7] == 0x700A) {
        sp50 = 0;
        sp54 = 0;
    }
    self->ext.playerBlink.unk82 += self->ext.playerBlink.unk8A;
    if (self->facingLeft) {
        posX = posX - sp7c;
    } else {
        posX = posX + sp7c;
    }
    posY = posY + sp7a;
    prim = &g_PrimBuf[self->primIndex];
    for (i = 0; i < 8; i++) {
        if (maskedParams & 0x40) {
            switch (i) {
            case 0:
                if (self->facingLeft) {
                    prim->x1 = posX - xOffset / 2;
                } else {
                    prim->x1 = posX + xOffset / 2;
                }
                prim->x0 = posX;
                prim->u0 = var_s7;
                prim->u1 = var_s7 + xOffset / 2;
                prim->y1 = posY;
                prim->y0 = posY;
                prim->v1 = var_s6;
                prim->v0 = var_s6;
                break;
            case 1:
                if (self->facingLeft) {
                    prim->x0 = posX - xOffset / 2;
                    prim->x1 = posX - xOffset;
                } else {
                    prim->x0 = posX + xOffset / 2;
                    prim->x1 = posX + xOffset;
                }
                prim->u0 = var_s7 + xOffset / 2;
                prim->u1 = var_s7 + xOffset;
                prim->y0 = prim->y1 = posY;
                prim->v0 = prim->v1 = var_s6;
                break;
            case 2:
                if (self->facingLeft) {
                    prim->x0 = prim->x1 = posX - xOffset;
                } else {
                    prim->x0 = prim->x1 = posX + xOffset;
                }
                prim->u0 = prim->u1 = var_s7 + xOffset;
                prim->y0 = posY;
                prim->y1 = posY + yOffset / 2;
                prim->v0 = var_s6;
                prim->v1 = var_s6 + yOffset / 2;
                break;
            case 3:
                if (self->facingLeft) {
                    prim->x0 = prim->x1 = posX - xOffset;
                } else {
                    prim->x0 = prim->x1 = posX + xOffset;
                }

                prim->u0 = prim->u1 = var_s7 + xOffset;
                prim->y0 = posY + yOffset / 2;
                prim->y1 = posY + yOffset;
                prim->v0 = var_s6 + yOffset / 2;
                prim->v1 = var_s6 + yOffset;
                break;
            case 4:
                if (self->facingLeft) {
                    prim->x0 = posX - xOffset;
                    prim->x1 = posX - xOffset / 2;
                } else {
                    prim->x0 = posX + xOffset;
                    prim->x1 = posX + xOffset / 2;
                }
                prim->u0 = var_s7 + xOffset;
                prim->u1 = var_s7 + xOffset / 2;
                prim->y0 = prim->y1 = posY + yOffset;
                prim->v0 = prim->v1 = var_s6 + yOffset;
                break;
            case 5:
                if (self->facingLeft) {
                    prim->x0 = posX - xOffset / 2;
                } else {
                    prim->x0 = posX + xOffset / 2;
                }
                prim->x1 = posX;
                prim->u0 = var_s7 + xOffset / 2;
                prim->u1 = var_s7;
                prim->y0 = prim->y1 = posY + yOffset;
                prim->v0 = prim->v1 = var_s6 + yOffset;

                break;
            case 6:
                prim->x1 = posX;
                prim->x0 = posX;
                prim->u1 = var_s7;
                prim->u0 = var_s7;
                prim->y0 = posY + yOffset;
                prim->y1 = posY + yOffset / 2;
                prim->v0 = var_s6 + yOffset;
                prim->v1 = var_s6 + yOffset / 2;
                break;
            case 7:
                prim->x1 = posX;
                prim->x0 = posX;
                prim->u1 = var_s7;
                prim->u0 = var_s7;
                prim->y0 = posY + yOffset / 2;
                prim->y1 = posY;
                prim->v0 = var_s6 + yOffset / 2;
                prim->v1 = var_s6;
                break;
            }
            if (self->facingLeft) {
                prim->x2 = prim->x3 =
                    posX - xOffset / 2 +
                    ((rcos(self->ext.playerBlink.unk82) >> 4) * sp54 >> 0xC);
            } else {
                prim->x2 = prim->x3 =
                    posX + xOffset / 2 +
                    ((rcos(self->ext.playerBlink.unk82) >> 4) * sp54 >> 0xC);
            }
            prim->y2 = prim->y3 =
                (posY + yOffset / 2) -
                ((rsin(self->ext.playerBlink.unk82) >> 4) * sp50 >> 8);
            prim->u2 = prim->u3 = var_s7 + xOffset / 2;
            prim->v2 = prim->v3 = var_s6 + yOffset / 2;
        } else {
            if (self->facingLeft) {
                prim->x0 = prim->x2 = (posX - xOffset) + 1;
                prim->x1 = prim->x3 = posX + 1;
            } else {
                prim->x0 = prim->x2 = posX;
                prim->x1 = prim->x3 = posX + xOffset;
            }
            if (maskedParams == 0x20 || maskedParams == 0x21) {
                sp74 = (rsin(sp78) >> 7) * sp76 / 256;
                prim->x0 += sp74;
                prim->x1 += sp74;
                sp78 += 0x600;
                sp74 = (rsin(sp78) >> 7) * sp76 / 256;
                prim->x2 += sp74;
                prim->x3 += sp74;
            }
            prim->y0 = prim->y1 = posY + yOffset * i / 8;
            prim->y2 = prim->y3 = posY + yOffset * (i + 1) / 8;
            if (self->facingLeft) {
                prim->u0 = prim->u2 = sp7f - 1;
                prim->u1 = prim->u3 = var_s7 - 1;
            } else {
                prim->u0 = prim->u2 = var_s7;
                prim->u1 = prim->u3 = sp7f;
            }
            prim->v0 = prim->v1 = var_s6 + yOffset * i / 8;
            prim->v2 = prim->v3 = var_s6 + yOffset * (i + 1) / 8;
        }

        g_api.func_800EB758(self->posX.i.hi, self->posY.i.hi, self,
                            self->drawFlags, (POLY_GT4*)prim, self->facingLeft);

        if (maskedParams != 0x20 && maskedParams != 0x21) {
            sp6e = sp4c[0];
            sp6c = sp4c[2];
            sp6a = sp4c[1];
            sp68 = sp4c[4];
            sp64 = sp4c[6];
            sp66 = sp4c[5];
            // clang-format off
            if (maskedParams & 0x40) {
                angle = D_us_80181860[(i + sp6e) % 8];
                prim->r0 = (((rsin(angle) + 0x1000) >> 6) * self->ext.playerBlink.unk90 / sp68);
                angle = D_us_80181860[(i + sp6c) % 8];
                prim->g0 = (((rsin(angle) + 0x1000) >> 6) * self->ext.playerBlink.unk90 / sp64);
                angle = D_us_80181860[(i + sp6a) % 8];
                prim->b0 = (((rsin(angle) + 0x1000) >> 6) * self->ext.playerBlink.unk90 / sp66);
                angle = D_us_80181860[(i + sp6e + 1) % 8];
                prim->r1 = (((rsin(angle) + 0x1000) >> 6) * self->ext.playerBlink.unk90 / sp68);
                angle = D_us_80181860[(i + sp6c + 1) % 8];
                prim->g1 = (((rsin(angle) + 0x1000) >> 6) * self->ext.playerBlink.unk90 / sp64);
                angle = D_us_80181860[(i + sp6a + 1) % 8];
                prim->b1 = (((rsin(angle) + 0x1000) >> 6) * self->ext.playerBlink.unk90 / sp66);
                prim->r2 = prim->g2 = prim->b2 = prim->r3 = prim->g3 = prim->b3 = 0;
                D_us_80181860[i] += self->ext.playerBlink.unk8A;
            } else {
                angle = D_us_80181860[(i + sp6e) % 8];
                prim->r0 = prim->r1 =(((rsin(angle) + 0x1000) >> 6) * self->ext.playerBlink.unk90 / sp68);
                angle = D_us_80181860[(i + sp6c) % 8];
                prim->g0 = prim->g1 =(((rsin(angle) + 0x1000) >> 6) * self->ext.playerBlink.unk90 / sp64);
                angle = D_us_80181860[(i + sp6a) % 8];
                prim->b0 = prim->b1 =(((rsin(angle) + 0x1000) >> 6) * self->ext.playerBlink.unk90 / sp66);
                angle = D_us_80181860[(i + sp6e + 1) % 8];
                prim->r2 = prim->r3 =(((rsin(angle) + 0x1000) >> 6) * self->ext.playerBlink.unk90 / sp68);
                angle = D_us_80181860[(i + sp6c + 1) % 8];
                prim->g2 = prim->g3 =(((rsin(angle) + 0x1000) >> 6) * self->ext.playerBlink.unk90 / sp64);
                angle = D_us_80181860[(i + sp6a + 1) % 8];
                prim->b2 = prim->b3 =(((rsin(angle) + 0x1000) >> 6) * self->ext.playerBlink.unk90 / sp66);
                D_us_80181860[i] += self->ext.playerBlink.unk8A;
            }
        }
        // clang-format on
        prim = prim->next;
    }
    func_us_801C5354(1, 1);
    if (((maskedParams & 0x3F) == 0) || ((maskedParams & 0x3F) == 7)) {
        func_us_801C5430(1, 0xA);
    }
}
#endif

s16 D_us_80181B74[23][5] = {
    {
        0x0000,
        0x00FF,
        0x00FF,
        0x0103,
        0x0031,
    },

    {
        0x00FF,
        0x007F,
        0x001F,
        0x0103,
        0x0031,
    },

    {
        0x003F,
        0x001F,
        0x00FF,
        0x0103,
        0x0031,
    },

    {
        0x0000,
        0x003F,
        0x001F,
        0x0103,
        0x0031,
    },

    {
        0x003F,
        0x003F,
        0x003F,
        0x0103,
        0x0031,
    },

    {
        0x00FF,
        0x003F,
        0x003F,
        0x0103,
        0x0031,
    },

    {
        0x001F,
        0x003F,
        0x007F,
        0x0103,
        0x0031,
    },

    {
        0x007F,
        0x003F,
        0x000F,
        0x0103,
        0x0031,
    },

    {
        0x00FF,
        0x007F,
        0x001F,
        0x0103,
        0x0031,
    },

    {
        0x007F,
        0x007F,
        0x000F,
        0x0103,
        0x0031,
    },

    {
        0x000F,
        0x000F,
        0x007F,
        0x0103,
        0x0031,
    },

    {
        0x003F,
        0x003F,
        0x003F,
        0x0103,
        0x0031,
    },

    {
        0x007F,
        0x000F,
        0x007F,
        0x0103,
        0x0031,
    },

    {
        0x000F,
        0x00FF,
        0x002F,
        0x0103,
        0x0031,
    },

    {
        0x002F,
        0x00FF,
        0x002F,
        0x0103,
        0x0031,
    },

    {
        0x005F,
        0x000F,
        0x005F,
        0x0103,
        0x0031,
    },

    {
        0x007F,
        0x003F,
        0x000F,
        0x0103,
        0x0031,
    },

    {
        0x00FF,
        0x000F,
        0x000F,
        0x0103,
        0x0031,
    },

    {
        0x007F,
        0x003F,
        0x003F,
        0x0103,
        0x0031,
    },

    {
        0x0000,
        0x00FF,
        0x00FF,
        0x0103,
        0x0031,
    },

    {
        0x00FF,
        0x003F,
        0x003F,
        0x0103,
        0x0031,
    },

    {
        0x00FF,
        0x003F,
        0x003F,
        0x0103,
        0x0031,
    },

    {
        0x007F,
        0x007F,
        0x007F,
        0x0103,
        0x0031,
    },

};

#ifdef VERSION_PSP
INCLUDE_ASM("boss/bo4_psp/nonmatchings/bo4/unk_49A6C", EntityDopplegangerOutline);
#else
void EntityDopplegangerOutline(Entity* self) {
    s16* animFramePtr;
    u8* spritesheetPtr;
    s16 xOffset;
    s16 yOffset;
    s16 width;
    Primitive* prim;
    s16 spriteIdx;
    s32 i;
    s16 upperparams;
    u8 spriteX;
    s16* primData;
    s16 xVar;
    s16 yVar;
    u8 four;
    u8 one;
    s16 height;
    u8 spriteY;
    s16 selfX;
    s16 selfY;

    if ((g_Dop.status & (PLAYER_STATUS_AXEARMOR | PLAYER_STATUS_TRANSFORM)) ||
        !DOPPLEGANGER.animSet || !(DOPPLEGANGER.animCurFrame & INT16_MAX)) {
        DestroyEntity(self);
        return;
    }

    upperparams = (self->params & 0x7F00) >> 8;
    self->posX.i.hi = DOPPLEGANGER.posX.i.hi;
    self->posY.i.hi = DOPPLEGANGER.posY.i.hi;
    self->facingLeft = DOPPLEGANGER.facingLeft;
    animFramePtr = (s16*)D_us_801B0A78[DOPPLEGANGER.animCurFrame & INT16_MAX];
    spriteIdx = *animFramePtr++;
    spriteIdx &= INT16_MAX;
    selfX = self->posX.i.hi;
    selfY = self->posY.i.hi;
    spritesheetPtr = ((u8**)doppleganger_sprites)[spriteIdx];
    four = 4;
    one = 1;
    spriteX = four + spritesheetPtr[0];
    spriteY = one + spritesheetPtr[1];
    width = spriteX - four;
    height = spriteY - one;
    xOffset = animFramePtr[0] + spritesheetPtr[2];
    yOffset = animFramePtr[1] + spritesheetPtr[3];
    self->rotate = DOPPLEGANGER.rotate;
    self->drawFlags = DOPPLEGANGER.drawFlags | (ENTITY_SCALEX | ENTITY_SCALEY);
    primData = D_us_80181B74[upperparams];
    switch (self->step) {
    case 0: // Initialization
        self->primIndex = g_api.AllocPrimitives(PRIM_GT4, 1);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags = FLAG_UNK_10000000 | FLAG_HAS_PRIMS;
        prim = &g_PrimBuf[self->primIndex];
        // This is just not a for-loop, that's weird
        for (i = 0; i < 1; i++) {
            prim->tpage = 0x10;
            prim->clut = primData[3]; // Always 259
            prim->priority = DOPPLEGANGER.zPriority + 2;
            // primData[4] is always 49; DRAW_UNK_40 | DRAW_HIDE | DRAW_TRANSP
            prim->drawMode = primData[4] + (DRAW_COLORS | DRAW_UNK02);
            prim = prim->next;
        }
        switch (upperparams) {
        case 0: // MP refill
        case 8:
        case 9:
        case 10:
        case 11:
        case 12:
        case 13:
        case 17: // Dark Metamorphosis
        case 18:
        case 20: // Sword Warp Spell (#1)
        case 22: // Soul Steal
            self->ext.playerOutline.brightness = 0x80;
            self->scaleX =
                DOPPLEGANGER.scaleX; // Player scaleX is (always?) 0x100
            self->scaleY =
                DOPPLEGANGER.scaleY; // Player scaleY is (always?) 0x100
            self->rotPivotY = DOPPLEGANGER.rotPivotY;
            self->rotPivotX = DOPPLEGANGER.rotPivotX;
            self->ext.playerOutline.timer = 8;
            break;
        case 2: // Agunea
            self->ext.playerOutline.brightness = 0xC0;
            self->scaleX =
                DOPPLEGANGER.scaleX; // Player scaleX is (always?) 0x100
            self->scaleY =
                DOPPLEGANGER.scaleY; // Player scaleY is (always?) 0x100
            self->rotPivotY = DOPPLEGANGER.rotPivotY;
            self->rotPivotX = DOPPLEGANGER.rotPivotX;
            self->ext.playerOutline.timer = 8;
            break;
        case 1: // Curse attack
            self->ext.playerOutline.brightness = 0x100;
            self->scaleX =
                DOPPLEGANGER.scaleX; // Player scaleX is (always?) 0x100
            self->scaleY =
                DOPPLEGANGER.scaleY; // Player scaleY is (always?) 0x100
            self->rotPivotY = DOPPLEGANGER.rotPivotY;
            self->rotPivotX = DOPPLEGANGER.rotPivotX;
            self->ext.playerOutline.timer = 8;
            break;
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 14:
        case 15:
        case 16:
        case 19:
        case 21: // Sword Warp Spell (#2)
            self->ext.playerOutline.brightness = 0x80;
            self->scaleX = DOPPLEGANGER.scaleX + 0x60;
            self->scaleY = DOPPLEGANGER.scaleY + 0x60;
            self->rotPivotY = DOPPLEGANGER.rotPivotY;
            self->rotPivotX = DOPPLEGANGER.rotPivotX;
            self->ext.playerOutline.timer = 8;
            break;
        }
        self->step++;
        break;

    case 1: // 8 frames at constant size
        switch (upperparams) {
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 14:
        case 15:
        case 16:
        case 18:
        case 21: // Sword Warp Spell (#2)
            self->ext.playerOutline.brightness += 16;
        case 0: // MP refill
        case 1: // Curse attack
        case 2: // Agunea
        case 8:
        case 9:
        case 10:
        case 11:
        case 12:
        case 13:
        case 17: // Dark Metamorphosis
        case 19:
        case 20: // Sword Warp Spell (#1)
        case 22: // Soul Steal
            if (--self->ext.playerOutline.timer == 0) {
                self->step++;
            }
        }
        break;
    case 2: // Outline grows/shrinks, and dims
        switch (upperparams) {
        case 0: // MP refill
        case 2: // Agunea
        case 8:
        case 9:
        case 10:
        case 11:
        case 12:
        case 13:
        case 15:
        case 16:
        case 17: // Dark Metamorphosis
        case 18:
        case 20: // Sword Warp Spell (#1)
        case 22: // Soul Steal
            self->scaleX += 8;
            self->scaleY += 8;
            self->ext.playerOutline.brightness -= 5;
            if (self->ext.playerOutline.brightness < 0) {
                DestroyEntity(self);
                return;
            }
            break;
        case 1: // Curse attack, grows slower and dims faster
            self->scaleX += 2;
            self->scaleY += 2;
            self->ext.playerOutline.brightness -= 16;
            if (self->ext.playerOutline.brightness < 0) {
                DestroyEntity(self);
                return;
            }
            break;
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 14:
        case 19:
        case 21: // Sword Warp Spell (#2)
            // Shrinks inward, and when at size 0x100, holds there for 8 frames
            // in step 3
            self->scaleX -= 8;
            self->scaleY -= 8;
            if (self->scaleX <= 0x100) {
                self->scaleY = self->scaleX = 0x100;
                self->ext.playerOutline.timer = 8;
                self->step++;
            }
        }
        break;
    case 3: // Outline continues static until done
        if (--self->ext.playerOutline.timer == 0) {
            DestroyEntity(self);
            return;
        }
        break;
    }
    if (self->facingLeft) {
        selfX = selfX - xOffset;
    } else {
        selfX = selfX + xOffset;
    }
    selfY = selfY + yOffset;
    prim = &g_PrimBuf[self->primIndex];
    for (i = 0; i <= 0; i++) {
        if (self->facingLeft) {
            prim->x0 = prim->x2 = (selfX - width) + 1;
            prim->x1 = prim->x3 = selfX + 1;
        } else {
            prim->x0 = prim->x2 = selfX;
            prim->x1 = prim->x3 = selfX + width;
        }

        prim->y0 = prim->y1 = selfY;
        prim->y2 = prim->y3 = selfY + height;
        if (self->facingLeft) {
            prim->u0 = prim->u2 = spriteX - 1;
            prim->u1 = prim->u3 = four - 1;
        } else {
            prim->u0 = prim->u2 = four;
            prim->u1 = prim->u3 = spriteX;
        }
        prim->v0 = prim->v1 = one;
        prim->v2 = prim->v3 = one + height;
        g_api.func_800EB758(self->posX.i.hi, self->posY.i.hi, self,
                            self->drawFlags, (POLY_GT4*)prim, (u16)self->facingLeft);
        PRED(prim) = primData[0] * self->ext.playerOutline.brightness / 256;
        PGRN(prim) = primData[1] * self->ext.playerOutline.brightness / 256;
        PBLU(prim) = primData[2] * self->ext.playerOutline.brightness / 256;
        prim->priority = DOPPLEGANGER.zPriority + 2;
        prim = prim->next;
    }
    func_us_801C5354(1, 1);
}
#endif

void EntityGravityBootBeam(Entity* self) {
    Primitive* prim;
    s16 halfWidth;
    s32 i;
    s16 yOffset = -12;

    switch (self->step) {
    case 0:
        self->posY.i.hi = DOPPLEGANGER.posY.i.hi + 37;
        self->ext.timer.t = 1536;
        self->primIndex = g_api.AllocPrimitives(PRIM_G4, 4);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags =
            FLAG_UNK_10000000 | FLAG_POS_CAMERA_LOCKED | FLAG_HAS_PRIMS;

        for (prim = &g_PrimBuf[self->primIndex], i = 0; prim != NULL; i++,
            prim = prim->next) {
            halfWidth = (self->ext.timer.t >> 8) - i; // unused in this loop
            prim->r0 = 0;
            prim->g0 = 0;
            prim->b0 = 0xC0;
            prim->r1 = 0;
            prim->g1 = 0;
            prim->b1 = 0xC0;
            prim->r2 = 0x40;
            prim->g2 = 0x40;
            prim->b2 = 0x40;
            prim->r3 = 0x40;
            prim->g3 = 0x40;
            prim->b3 = 0x40;

            prim->priority = DOPPLEGANGER.zPriority - 2;
            prim->drawMode = DRAW_DITHERING | DRAW_TPAGE2 | DRAW_TPAGE |
                             DRAW_COLORS | DRAW_UNK02 | DRAW_TRANSP;
        }
        self->step++;
        break;

    case 1:
        if (DOPPLEGANGER.velocityY > FIX(-1.5)) {
            self->step = Dop_Walk;
        }
        // If transformed, timer drains faster
        if (g_Dop.status & (PLAYER_STATUS_BAT_FORM | PLAYER_STATUS_MIST_FORM)) {
            self->step = Dop_Crouch;
        }
        break;

    case 3:
        // note that with the fallthrough these decrements stack
        self->ext.timer.t -= 160;
    case 2:
        self->ext.timer.t -= 96;
        if (self->ext.timer.t < 0) {
            DestroyEntity(self);
            return;
        }
        break;
    }
    for (prim = &g_PrimBuf[self->primIndex], i = 0; prim != NULL; i++,
        prim = prim->next) {
        // As timer counts down, beam gets narrower.
        halfWidth = (self->ext.timer.t >> 8) - i;
        if (halfWidth < 0) {
            halfWidth = 0;
        }
        prim->x0 = self->posX.i.hi - halfWidth;
        prim->x1 = self->posX.i.hi + halfWidth;
        prim->x2 = DOPPLEGANGER.posX.i.hi - halfWidth;
        prim->x3 = DOPPLEGANGER.posX.i.hi + halfWidth;
        prim->y2 = prim->y3 = DOPPLEGANGER.posY.i.hi - yOffset;
        prim->y0 = prim->y1 = self->posY.i.hi;
    }
}

// The blue outlines of the bat that show up when wing smashing
void EntityWingSmashTrail(Entity* self) {
    if (!(DOPPLEGANGER.step_s == 3 && DOPPLEGANGER.step == Dop_MorphBat)) {
        DestroyEntity(self);
        return;
    }

    if (self->step == 0) {
        self->flags = FLAG_POS_CAMERA_LOCKED;
        self->animSet = DOPPLEGANGER.animSet;
        self->animCurFrame = DOPPLEGANGER.animCurFrame | ANIM_FRAME_LOAD;
        self->unk5A = 8;
        self->zPriority = DOPPLEGANGER.zPriority - 2;
        self->drawFlags = DOPPLEGANGER.drawFlags |
                          (ENTITY_OPACITY | ENTITY_SCALEY | ENTITY_SCALEX);
        self->opacity = 0x80;
        self->blendMode = BLEND_TRANSP | BLEND_ADD;
        self->rotate = DOPPLEGANGER.rotate;
        self->facingLeft = DOPPLEGANGER.facingLeft;
        self->palette = PAL_FLAG(0x202);
        self->scaleX = self->scaleY = 0x100;
        self->step++;
        return;
    }
    // This actually makes the wing smashes shrink over time, not rotate.
    self->scaleX -= 8;
    self->scaleY -= 8;
    self->animCurFrame = DOPPLEGANGER.animCurFrame | ANIM_FRAME_LOAD;
    if (self->opacity >= 5) {
        self->opacity -= 5;
    } else {
        DestroyEntity(self);
    }
}

static unkStr_8011E4BC D_us_80181C5C = {
    0x08, 0x7F,   0x7F,   0x7F,   0x02,
    0x02, 0x0002, 0x0033, 0x0000, FLAG_POS_CAMERA_LOCKED | FLAG_HAS_PRIMS,
};

static unkStr_8011E4BC D_us_80181C6C = {
    0x10,   0x7F,
    0x7F,   0x7F,
    0x01,   0x01,
    0x0002, 0x0033,
    0x0001, FLAG_UNK_10000000 | FLAG_POS_CAMERA_LOCKED | FLAG_HAS_PRIMS,
};

static unkStr_8011E4BC D_us_80181C7C = {
    0x08, 0x7F,   0x7F,   0x7F,   0x01,
    0x01, 0x0002, 0x0033, 0x0000, FLAG_POS_CAMERA_LOCKED | FLAG_HAS_PRIMS,
};

static unkStr_8011E4BC D_us_80181C8C = {
    0x08, 0x4F,   0x4F,   0x4F,   0x01,
    0x01, 0x0004, 0x0002, 0x0002, FLAG_POS_CAMERA_LOCKED | FLAG_HAS_PRIMS,
};

static unkStr_8011E4BC D_us_80181C9C = {
    0x0A, 0xC0,   0x60,   0x00,   0x01,
    0x01, 0x0004, 0x0033, 0x0003, FLAG_POS_CAMERA_LOCKED | FLAG_HAS_PRIMS,
};

static unkStr_8011E4BC D_us_80181CAC = {
    0x0c, 0x7f,   0x00,   0x00,   0x02,
    0x02, 0x0002, 0x0002, 0x0004, FLAG_POS_CAMERA_LOCKED | FLAG_HAS_PRIMS,
};

static unkStr_8011E4BC D_us_80181CBC = {
    0x08, 0x3F,   0xF0,   0x3F,   0x01,
    0x01, 0x0004, 0x0073, 0x0003, FLAG_POS_CAMERA_LOCKED | FLAG_HAS_PRIMS,
};

static unkStr_8011E4BC D_us_80181CCC = {
    0x1E, 0x3F,   0x3F,   0x3F,   0x01,
    0x01, 0x0004, 0x0002, 0x0008, FLAG_POS_CAMERA_LOCKED | FLAG_HAS_PRIMS,
};

static unkStr_8011E4BC D_us_80181CDC = {
    0x10, 0x7F,   0x7F,   0x7F,   0x01,
    0x01, 0x0002, 0x0033, 0x0009, FLAG_POS_CAMERA_LOCKED | FLAG_HAS_PRIMS,
};

static unkStr_8011E4BC D_us_80181CEC UNUSED = {
    0x0A, 0xC0,   0xC0,   0x3F,   0x01,
    0x01, 0xFFFE, 0x0033, 0x000A, FLAG_POS_CAMERA_LOCKED | FLAG_HAS_PRIMS,
};

static unkStr_8011E4BC D_us_80181CFC = {
    0x04, 0xC0,   0x60,   0x00,   0x01,
    0x01, 0x0004, 0x0033, 0x0003, FLAG_POS_CAMERA_LOCKED | FLAG_HAS_PRIMS,
};

unkStr_8011E4BC* D_us_80181D0C[] = {
    &D_us_80181C5C, &D_us_80181C6C, &D_us_80181C7C, &D_us_80181C8C,
    &D_us_80181C9C, &D_us_80181CAC, &D_us_80181CAC, &D_us_80181CBC,
    &D_us_80181CCC, &D_us_80181CDC, &D_us_80181CFC, &D_us_80181CFC,
};

extern s32 D_us_801D4118[32];
extern s32 D_us_801D4198[32];

#ifdef VERSION_PSP
INCLUDE_ASM("boss/bo4_psp/nonmatchings/bo4/unk_49A6C", func_us_801CD178);
#else
void func_us_801CD178(Entity* self) {
    byte stackpad[0x28];
    FakePrim* tilePrim;
    u8 thickness;
    s16 upperParams;
    s16 randAngleShift;
    s32 var_a2;
    s16 randVar2;
    s16 twelveShift;
    s16 randVar;
    s16 selfXPos;
    s16 selfYPos;
    unkStr_8011E4BC* temp_s5;
    s32 i;

    upperParams = self->params >> 8;
    temp_s5 = D_us_80181D0C[upperParams];
    selfXPos = self->posX.i.hi;
    selfYPos = self->posY.i.hi;

    switch (self->step) {
    case 0:
        self->primIndex =
            g_api.func_800EDB58(PRIM_TILE_ALT, temp_s5->count + 1);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags = temp_s5->flags;
        switch (upperParams) {
        case 8:
            self->ext.et_8011E4BC.unk7C = 0x3F;
            break;
        case 3:
        case 5:
            self->ext.et_8011E4BC.unk7C = 0x2F;
            break;
        case 4:
        case 7:
        case 11:
            self->ext.et_8011E4BC.unk7C = 0x1F;
            break;
        }
        for (tilePrim = (FakePrim*)&g_PrimBuf[self->primIndex], i = 0; true;
             i++, tilePrim = tilePrim->next) {
            tilePrim->drawMode = temp_s5->drawMode;
            tilePrim->priority = DOPPLEGANGER.zPriority + temp_s5->priority;
            if (tilePrim->next == NULL) {
                tilePrim->drawMode &= ~DRAW_HIDE;
                tilePrim->y0 = tilePrim->x0 = tilePrim->w = 0;
                break;
            }
            tilePrim->posX.i.hi = selfXPos;
            tilePrim->posY.i.hi = selfYPos;
            tilePrim->posX.i.lo = tilePrim->posY.i.lo = 0;
            switch (temp_s5->unkA) {
            case 0:
                randVar2 = rand() & PSP_RANDMASK;
                randAngleShift = (randVar2 & 1) + 2;
                tilePrim->velocityX.val = (rcos(randVar2) << randAngleShift);
                tilePrim->velocityY.val = -(rsin(randVar2) << randAngleShift);
                break;
            case 1:
            case 9:
                tilePrim->velocityX.val = (((rand() & 0x1FF) - 0x100) << 8);
                tilePrim->velocityY.val = (((rand() & 0x1FF) - 0x100) << 8);
                break;
            case 2:
                tilePrim->velocityX.val =
                    ((s32)(((rand() & PSP_RANDMASK) * 2) - 0x8000)) >> 1;
                tilePrim->velocityY.val = -(rand() & 0x3FFF);
                tilePrim->posX.val += (tilePrim->velocityX.val * 19);
                tilePrim->posY.i.hi = (selfYPos + (rand() & 7)) - 3;
                tilePrim->delay = (rand() & 0xF) + 0x10;
                break;
            case 8:
                twelveShift = -12;
                if (DOPPLEGANGER.facingLeft) {
                    twelveShift = -twelveShift;
                }
                tilePrim->velocityX.val =
                    ((rand() & PSP_RANDMASK) * 4) - FIX(1);
                tilePrim->velocityY.val = -(rand() & 0x3FFF);
                tilePrim->posX.val +=
                    ((tilePrim->velocityX.val * 35) + (twelveShift << 16));
                tilePrim->velocityX.val >>= 2;
                tilePrim->posY.i.hi = selfYPos - (rand() & 0x1F);
                tilePrim->delay = (rand() & 0x1F) + 0x10;
                break;
            case 3:
                tilePrim->posX.i.hi = (selfXPos + (rand() & 0xF)) - 7;
                tilePrim->posY.i.hi = selfYPos - (rand() & 0x1F);
                tilePrim->velocityY.val = FIX(-0.75) - (rand() & 0x7FFF);
                tilePrim->velocityX.val =
                    self->ext.et_8011E4BC.parent->velocityX;
                tilePrim->delay = ((i * 2) + 0xF);
                break;
            case 4:
                randVar = (rand() & 0x1F);
                tilePrim->posX.i.hi = (selfXPos + randVar) - 0x10;
                randVar = (rand() & 0x1F);
                tilePrim->posY.i.hi = (selfYPos + randVar) - 0x14;
                randVar = rand() & 0x1F;
                tilePrim->velocityX.val = D_us_801D4118[randVar];
                tilePrim->velocityY.val = D_us_801D4198[randVar];
                break;
            case 10:
            case 11:
            case 12:
            case 13:
                break;
            }
            tilePrim->x0 = tilePrim->posX.i.hi;
            tilePrim->y0 = tilePrim->posY.i.hi;
            tilePrim->r0 = temp_s5->r;
            tilePrim->g0 = temp_s5->g;
            tilePrim->b0 = temp_s5->b;
            tilePrim->w = temp_s5->w;
            tilePrim->h = temp_s5->h;
        }
        self->step++;
        break;
    case 1:
        switch (upperParams) {
        case 3:
        case 4:
        case 7:
        case 8:
        case 11:
            if (--self->ext.et_8011E4BC.unk7C == 0) {
                DestroyEntity(self);
                return;
            }
            // fallthrough
        case 5:
            if (--self->ext.et_8011E4BC.unk7C == 0) {
                DestroyEntity(self);
                return;
            }
            thickness = 2;
            var_a2 = self->ext.et_8011E4BC.unk7C;
            if (var_a2 < 9) {
                thickness--;
            }
            break;
        }
        for (tilePrim = (FakePrim*)&g_PrimBuf[self->primIndex], i = 0; true;
             i++, tilePrim = tilePrim->next) {
            if (tilePrim->next == NULL) {
                tilePrim->drawMode &= ~DRAW_HIDE;
                tilePrim->y0 = tilePrim->x0 = tilePrim->w = 0;
                return;
            }

            tilePrim->posX.i.hi = tilePrim->x0;
            tilePrim->posY.i.hi = tilePrim->y0;
            switch (temp_s5->unkA) {
            case 0:
                tilePrim->posY.val += tilePrim->velocityY.val;
                tilePrim->posX.val += tilePrim->velocityX.val;
                tilePrim->r0 -= 6;
                tilePrim->g0 -= 6;
                tilePrim->b0 -= 6;
                if (tilePrim->r0 < 8) {
                    DestroyEntity(self);
                    return;
                }
                break;
            case 1:
            case 9:
                tilePrim->posY.val += tilePrim->velocityY.val;
                tilePrim->posX.val += tilePrim->velocityX.val;
                tilePrim->velocityY.val += FIX(5.0 / 32.0);
                tilePrim->r0 -= 3;
                tilePrim->g0 -= 3;
                tilePrim->b0 -= 3;
                if (tilePrim->r0 < 8) {
                    DestroyEntity(self);
                    return;
                }
                break;
            case 2:
            case 8:
                if (--tilePrim->delay == 0) {
                    tilePrim->drawMode |= DRAW_HIDE;
                }
                tilePrim->posX.val += tilePrim->velocityX.val;
                tilePrim->posY.val += tilePrim->velocityY.val;
                tilePrim->velocityY.val += FIX(5.0 / 64.0);
                break;
            case 3:
                tilePrim->posY.val += tilePrim->velocityY.val;
                if (--tilePrim->delay < 0) {
                    tilePrim->drawMode |= DRAW_HIDE;
                }
                break;
            case 4:
                tilePrim->posX.val += tilePrim->velocityX.val;
                tilePrim->posY.val += tilePrim->velocityY.val;
                tilePrim->velocityY.val -= (tilePrim->velocityY.val >> 5);
                if (!(var_a2 & 7)) {
                    tilePrim->velocityX.val >>= 1;
                    tilePrim->velocityY.val >>= 1;
                    if (var_a2 & 0x20) {
                        tilePrim->velocityY.val >>= 1;
                    }
                }

                tilePrim->w = tilePrim->h = thickness;
                break;
            }
            tilePrim->x0 = tilePrim->posX.i.hi;
            tilePrim->y0 = tilePrim->posY.i.hi;
        }
        break;
    }
}
#endif

static AnimationFrame D_us_80181D3C[] = {
    POSE(2, 1, 0), POSE(2, 2, 0), POSE(2, 3, 0), POSE(2, 4, 0), POSE(2, 5, 0),
    POSE(2, 4, 0), POSE(2, 3, 0), POSE(2, 4, 0), POSE(2, 3, 0), POSE(2, 4, 0),
    POSE(2, 5, 0), POSE(1, 6, 0), POSE(1, 7, 0), POSE(1, 8, 0), POSE_END,
};
static AnimationFrame D_us_80181D78[] = {
    POSE(1, 0x09, 0), POSE(2, 0x0A, 0), POSE(2, 0x0B, 0), POSE(2, 0x0C, 0),
    POSE(2, 0x0D, 0), POSE(2, 0x0E, 0), POSE(2, 0x0F, 0), POSE(2, 0x10, 0),
    POSE(2, 0x11, 0), POSE(2, 0x12, 0), POSE(3, 0x13, 0), POSE(4, 0x14, 0),
    POSE_END,
};

void func_us_801CD89C(Entity* self) {
    s16 paramsLo = self->params & 0xFF;
    s16 paramsHi = (self->params >> 8) & 0xFF;

    switch (self->step) {
    case 0:
        if (paramsHi == 1) {
            self->scaleX = 0xC0;
            self->scaleY = 0xC0;
            self->drawFlags = ENTITY_SCALEX | ENTITY_SCALEY;
            self->animSet = ANIMSET_DRA(2);
            self->anim = D_us_80181D78;
        }

        if ((paramsHi == 0) || (paramsHi == 2)) {
            if (paramsLo & 3) {
                self->anim = D_us_80181D3C;
                self->scaleX = 0x120;
                self->scaleY = 0x120;
                self->drawFlags = ENTITY_SCALEX | ENTITY_SCALEY;
                self->animSet = ANIMSET_DRA(2);
            } else {
                self->animSet = ANIMSET_DRA(5);
                self->anim = D_us_801817A8;
                self->palette = PAL_FLAG(PAL_UNK_170);
            }
        }
        self->flags = FLAG_UNK_20000000 | FLAG_POS_CAMERA_LOCKED;

        if (rand() & 3) {
            self->zPriority = DOPPLEGANGER.zPriority + 2;
        } else {
            self->zPriority = DOPPLEGANGER.zPriority - 2;
        }

        if (paramsHi == 2) {
            self->posX.i.hi = DOPPLEGANGER.posX.i.hi + (rand() % 44) - 22;
        } else {
            self->posX.i.hi = DOPPLEGANGER.posX.i.hi + (rand() & 15) - 8;
        }

        self->posY.i.hi = DOPPLEGANGER.posY.i.hi + DOPPLEGANGER.hitboxOffY +
                          (rand() & 31) - 16;
        self->velocityY = FIX(-0.5);
        self->velocityX = DOPPLEGANGER.velocityX >> 2;
        self->step++;
        break;

    case 1:
        self->scaleX -= 4;
        self->scaleY -= 4;
        self->posY.val += self->velocityY;
        self->posX.val += self->velocityX;
        if ((self->pose == 8) && (self->anim != D_us_801817A8)) {
            self->blendMode = BLEND_TRANSP;
            if (!(paramsLo & 1) && (self->poseTimer == 1)) {
                CreateEntFactoryFromEntity(self, FACTORY(4, 4), 0);
            }
        }

        if ((self->pose == 16) && (self->anim == D_us_801817A8)) {
            self->blendMode = BLEND_TRANSP;
        }

        if (self->poseTimer < 0) {
            DestroyEntity(self);
        }
        break;
    }
}

static u16 D_us_80181DAC[2] = {0x194, 0x199};

void DopEntityHitByLightning(Entity* self) {
    s16 xBase;
    s16 yBase;
    s32 xOffset;
    s32 yOffset;
    bool var_s0 = false;
    s32 temp_s2;
    s16 temp_s1_2;
    s16 temp_s0;
    s32 i;
    Primitive* prevPrim;
    Primitive* prim;

    if ((self->params & 0xFF00) != 0) {
        if ((++self->ext.hitbylightning.unk9C) > 0xA8) {
            var_s0 = true;
        }
    } else if (DOPPLEGANGER.step != Dop_Hit) {
        var_s0 = true;
    }

    switch (self->step) {
    case 0:
        self->primIndex = g_api.AllocPrimitives(PRIM_GT4, 6);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }

        self->flags = FLAG_POS_CAMERA_LOCKED | FLAG_HAS_PRIMS;
        self->ext.hitbylightning.unk7C =
            ((self->params & 0xF) << 9) + (rand() & 0x3F);
        self->ext.hitbylightning.unk80 = rand() & PSP_RANDMASK;
        self->ext.hitbylightning.unk82 = (rand() & 0x1FF) + 0x100;
        prim = &g_PrimBuf[self->primIndex];
        while (prim != NULL) {
            prim->x0 = prim->x1 = prim->x2 = prim->x3 = self->posX.i.hi;
            prim->y0 = prim->y1 = prim->y2 = prim->y3 = self->posY.i.hi;
            prim->tpage = 0x1A;
            prim->clut = D_us_80181DAC[rand() & 1];
            prim->priority = DOPPLEGANGER.zPriority - 2;
            PGREY(prim, 0) = PGREY(prim, 1) = PGREY(prim, 2) = PGREY(prim, 3) =
                0x80;
            prim->drawMode =
                DRAW_TPAGE2 | DRAW_TPAGE | DRAW_UNK02 | DRAW_TRANSP;
            prim = prim->next;
        }
        if ((DOPPLEGANGER.velocityY != 0) && (DOPPLEGANGER.step != Dop_Kill)) {
            self->ext.hitbylightning.unk92 = 1;
        }
        self->ext.hitbylightning.unk94 = 16;
        g_api.PlaySfx(SFX_MAGIC_SWITCH);
        g_api.PlaySfx(SFX_THUNDER_B);
        self->step++;
        break;
    case 1:
        self->ext.hitbylightning.unk7C =
            ((self->params & 0xF) << 9) + (rand() & 0x1FF);
        temp_s2 = rsin(self->ext.hitbylightning.unk80);
        self->ext.hitbylightning.unk80 += self->ext.hitbylightning.unk82;
        xOffset = ((rcos(self->ext.hitbylightning.unk7C) * temp_s2) >> 7) * 12;
        // This should probably be * -14 but that doesn't work.
        yOffset =
            -((rsin(self->ext.hitbylightning.unk7C) * temp_s2) >> 7) * 7 << 1;
        self->posX.val = xOffset + DOPPLEGANGER.posX.val;
        self->posY.val = yOffset + DOPPLEGANGER.posY.val;
        if ((self->ext.hitbylightning.unk92) &&
            (g_Dop.vram_flag &
             (TOUCHING_L_WALL | TOUCHING_R_WALL | TOUCHING_CEILING))) {
            var_s0 = true;
        }
        if (var_s0) {
            self->ext.hitbylightning.unk90 = (rand() & 0xF) + 0x10;
            self->step++;
        }
        break;
    case 2:
        if (--self->ext.hitbylightning.unk90 == 0) {
            DestroyEntity(self);
            return;
        }
        if (self->ext.hitbylightning.unk94 > 0) {
            self->ext.hitbylightning.unk94--;
        }
        self->ext.hitbylightning.unk7C =
            ((self->params & 0xF) << 9) + (rand() & 0xFF);
        temp_s2 = rsin(self->ext.hitbylightning.unk80);
        self->ext.hitbylightning.unk80 += self->ext.hitbylightning.unk82;
        xOffset = (((rcos(self->ext.hitbylightning.unk7C) * temp_s2) >> 7) *
                   ((rand() % 8) + 8));
        yOffset = (-((rsin(self->ext.hitbylightning.unk7C) * temp_s2) >> 7) *
                   ((rand() % 8) + 10)) +
                  self->ext.hitbylightning.unk98;
        self->posX.val = DOPPLEGANGER.posX.val + xOffset;
        self->posY.val = DOPPLEGANGER.posY.val + yOffset;
        self->ext.hitbylightning.unk98 -= 0x8000;
        prim = &g_PrimBuf[self->primIndex];
        break;
    }
    xBase = (self->posX.i.hi + (rand() & 7)) - 4;
    yBase = (self->posY.i.hi + (rand() & 0x1F)) - 0x18;
    temp_s1_2 = self->ext.hitbylightning.unk94;
    temp_s1_2 = (temp_s1_2 * rsin(self->ext.hitbylightning.unk80)) >> 0xC;
    prim = &g_PrimBuf[self->primIndex];
    for (i = 0; i < 5; i++) {
        prevPrim = prim;
        prim = prim->next;
        *prevPrim = *prim;
        prevPrim->next = prim;
        prevPrim->u0 = prevPrim->u2 = (i * 0x10) + 0x90;
        prevPrim->u1 = prevPrim->u3 = ((i + 1) * 0x10) + 0x90;
        prevPrim->v0 = prevPrim->v1 = 0xC0;
        prevPrim->v2 = prevPrim->v3 = 0xCF;
    }
    prim->x0 = prim->x1;
    prim->y0 = prim->y1;
    prim->x2 = prim->x3;
    prim->y2 = prim->y3;
    temp_s0 = self->ext.hitbylightning.unk7C + 0x400;
    prim->x1 = xBase + (((rcos(temp_s0) >> 4) * temp_s1_2) >> 8);
    prim->y1 = yBase - (((rsin(temp_s0) >> 4) * temp_s1_2) >> 8);
    temp_s0 = self->ext.hitbylightning.unk7C - 0x400;
    prim->x3 = xBase + (((rcos(temp_s0) >> 4) * temp_s1_2) >> 8);
    prim->y3 = yBase - (((rsin(temp_s0) >> 4) * temp_s1_2) >> 8);

    temp_s0 = (self->ext.hitbylightning.unk80 & 0xFFF);
    if (temp_s0 < 0x400) {
        prim->priority = DOPPLEGANGER.zPriority + 2;
    } else if (temp_s0 < 0xC00) {
        prim->priority = DOPPLEGANGER.zPriority - 2;
    } else {
        prim->priority = DOPPLEGANGER.zPriority + 2;
    }
    prim->u0 = prim->u2 = (i << 4) + 0x90;
    prim->u1 = prim->u3 = (i + 1 << 4) + 0x90;
    prim->v0 = prim->v1 = 0xC0;
    prim->v2 = prim->v3 = 0xCF;
}

// player gets frozen

static Point16 D_us_80181DB0 = {0xFFFE, 0xFFE8};
static Point16 D_us_80181DB4 = {0x0000, 0xFFF8};
static Point16 D_us_80181DB8 = {0x0002, 0x0008};
static Point16 D_us_80181DBC = {0x0000, 0x0018};
static Point16 D_us_80181DC0 = {0x0006, 0xFFF4};
static Point16 D_us_80181DC4 = {0x0008, 0x0000};
static Point16 D_us_80181DC8 = {0x0007, 0x000C};
static Point16 D_us_80181DCC = {0xFFF8, 0xFFF4};
static Point16 D_us_80181DD0 = {0xFFF7, 0x0000};
static Point16 D_us_80181DD4 = {0xFFF9, 0x000C};
static Point16 D_us_80181DD8 = {0xFFF2, 0xFFFA};
static Point16 D_us_80181DDC = {0xFFF1, 0x0007};
static Point16 D_us_80181DE0 = {0x000D, 0xFFF9};
static Point16 D_us_80181DE4 = {0x0010, 0x0008};
static Point16 D_us_80181DE8 = {0xFFF9, 0xFFEA};
static Point16 D_us_80181DEC = {0x0006, 0xFFEB};
static Point16 D_us_80181DF0 = {0xFFF8, 0x0015};
static Point16 D_us_80181DF4 = {0x0007, 0x0016};

Point16* D_us_80181DF8[] = {
    &D_us_80181DB0, &D_us_80181DC0, &D_us_80181DB4, &D_us_80181DC0,
    &D_us_80181DC4, &D_us_80181DB4, &D_us_80181DC4, &D_us_80181DB8,
    &D_us_80181DB4, &D_us_80181DC4, &D_us_80181DC8, &D_us_80181DB8,
    &D_us_80181DC8, &D_us_80181DBC, &D_us_80181DB8, &D_us_80181DB8,
    &D_us_80181DBC, &D_us_80181DD4, &D_us_80181DB8, &D_us_80181DD4,
    &D_us_80181DD0, &D_us_80181DB4, &D_us_80181DB8, &D_us_80181DD0,
    &D_us_80181DB4, &D_us_80181DD0, &D_us_80181DCC, &D_us_80181DB4,
    &D_us_80181DCC, &D_us_80181DB0, &D_us_80181DC0, &D_us_80181DE0,
    &D_us_80181DC4, &D_us_80181DE0, &D_us_80181DE4, &D_us_80181DC4,
    &D_us_80181DE4, &D_us_80181DC8, &D_us_80181DC4, &D_us_80181DCC,
    &D_us_80181DD0, &D_us_80181DD8, &D_us_80181DD0, &D_us_80181DDC,
    &D_us_80181DD8, &D_us_80181DD0, &D_us_80181DD4, &D_us_80181DDC,
    &D_us_80181DB0, &D_us_80181DCC, &D_us_80181DE8, &D_us_80181DB0,
    &D_us_80181DEC, &D_us_80181DC0, &D_us_80181DBC, &D_us_80181DF0,
    &D_us_80181DD4, &D_us_80181DC8, &D_us_80181DF4, &D_us_80181DBC,
    &D_us_80181DE8, &D_us_80181DCC, &D_us_80181DD8, &D_us_80181DEC,
    &D_us_80181DE0, &D_us_80181DC0, &D_us_80181DDC, &D_us_80181DD4,
    &D_us_80181DF0, &D_us_80181DE4, &D_us_80181DF4, &D_us_80181DC8,
};

#ifdef VERSION_PSP
INCLUDE_ASM("boss/bo4_psp/nonmatchings/bo4/unk_49A6C", EntityHitByIce);
#else
void EntityHitByIce(Entity* self) {
    s32 i;
    s16 xShift;
    s16 yShift;
    s32 size;
    s16 primYshift;
    s16 selfX;
    s16 selfY;
    Point16* offset;
    bool sp18;

    s16 angle;

    Primitive* prim;

    self->posX.i.hi = DOPPLEGANGER.posX.i.hi;
    self->posY.i.hi = DOPPLEGANGER.posY.i.hi;

    sp18 = false;
    if (!(g_Dop.status & PLAYER_STATUS_UNK10000)) {
        sp18 = true;
    }

    switch (self->step) {
    case 0:
        self->primIndex = g_api.AllocPrimitives(PRIM_GT3, 24);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags = FLAG_HAS_PRIMS;
        for (prim = &g_PrimBuf[self->primIndex]; prim != NULL;
             prim = prim->next) {
            prim->r0 = prim->r1 = prim->r2 = prim->r3 = (rand() & 0xF) + 0x30;
            prim->b0 = prim->b1 = prim->b2 = prim->b3 = (rand() & 0x7F) + 0x80;
            prim->g0 = prim->g1 = prim->g2 = prim->g3 = (rand() & 0x1F) + 0x30;
            if (rand() & 1) {
                prim->drawMode =
                    DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS | DRAW_TRANSP;
            } else {
                prim->drawMode = DRAW_TPAGE | DRAW_COLORS | DRAW_TRANSP;
            }
            prim->type = PRIM_G4;
            prim->priority = DOPPLEGANGER.zPriority + 2;
        }
        if (DOPPLEGANGER.velocityY != 0) {
            self->ext.hitbyice.unk7E = 1;
        }
        if (DOPPLEGANGER.step == Dop_Kill) {
            self->ext.hitbyice.unk80 = 1;
            self->ext.hitbyice.unk82 = 0x14;
            self->ext.hitbyice.unk7E = 0;
        }
        if (DOPPLEGANGER.velocityY != 0) {
            if (DOPPLEGANGER.facingLeft) {
                self->rotate = ROT(22.5);
            } else {
                self->rotate = ROT(-22.5);
            }
        } else {
            if (DOPPLEGANGER.velocityX > 0) {
                self->rotate = ROT(11.25);
            } else {
                self->rotate = ROT(348.75);
            }
        }
        self->step++;
        break;
    case 1:
        if (self->ext.hitbyice.unk80 && --self->ext.hitbyice.unk82 == 0) {
            sp18 = true;
        }
        // Could rewrite as a series of && and || but that would probably reduce
        // readability
        if (self->ext.hitbyice.unk7E) {
            if (g_Dop.vram_flag & (TOUCHING_L_WALL | TOUCHING_R_WALL)) {
                sp18 = true;
            }
            if (DOPPLEGANGER.step == Dop_Hit && DOPPLEGANGER.step_s == 5) {
                sp18 = true;
            }
        }
        if (sp18) {
            self->ext.hitbyice.unk7C = 0x40;
            g_api.PlaySfx(SFX_MAGIC_SWITCH);
            self->step++;
        }
        break;
    case 2:
        if (--self->ext.hitbyice.unk7C == 0) {
            DestroyEntity(self);
            return;
        }
        break;
    }
    selfX = self->posX.i.hi;
    selfY = self->posY.i.hi;
    for (prim = &g_PrimBuf[self->primIndex], i = 0; i < 24; prim = prim->next,
        i++) {
        offset = D_us_80181DF8[i * 3];
        if (prim->u0 < 2) {
            size = SquareRoot12(
                ((offset->x * offset->x) + (offset->y * offset->y)) << 0xC);
            angle = self->rotate + ratan2(offset->y, offset->x);
            xShift = (((rcos(angle) >> 4) * size) + 0x80000) >> 0x14;
            yShift = (((rsin(angle) >> 4) * size) + 0x80000) >> 0x14;
            prim->x0 = selfX + xShift;
            prim->y0 = selfY + yShift;

            offset = D_us_80181DF8[i * 3 + 1];
            size = SquareRoot12(
                ((offset->x * offset->x) + (offset->y * offset->y)) << 0xC);
            angle = self->rotate + ratan2(offset->y, offset->x);
            xShift = (((rcos(angle) >> 4) * size) + 0x80000) >> 0x14;
            yShift = (((rsin(angle) >> 4) * size) + 0x80000) >> 0x14;
            prim->x1 = selfX + xShift;
            prim->y1 = selfY + yShift;

            offset = D_us_80181DF8[i * 3 + 2];
            size = SquareRoot12(
                ((offset->x * offset->x) + (offset->y * offset->y)) << 0xC);
            angle = self->rotate + ratan2(offset->y, offset->x);
            xShift = (((rcos(angle) >> 4) * size) + 0x80000) >> 0x14;
            yShift = (((rsin(angle) >> 4) * size) + 0x80000) >> 0x14;
            prim->x2 = prim->x3 = selfX + xShift;
            prim->y2 = prim->y3 = selfY + yShift;
        }
        if ((prim->u0 == 0) && (sp18 != 0)) {
            prim->u0++;
            prim->v0 = (rand() & 15) + 1;
        }
        if (prim->u0 == 1) {
            if (--prim->v0 == 0) {
                prim->u0++;
                prim->v0 = 0x20;
                prim->u2 = 0xF0;
            }
        }
        if (prim->u0 == 2) {
            if ((prim->u2 < 0x70) || (prim->u2 > 0xD0)) {
                prim->u2 += 4;
            }
            primYshift = (s8)prim->u2 >> 4;
            prim->y0 += primYshift;
            prim->y1 += primYshift;
            prim->y2 += primYshift;
            prim->y3 += primYshift;
            if (prim->r3 < 4) {
                prim->r3 -= 4;
            }
            if (prim->g3 < 4) {
                prim->g3 -= 4;
            }
            if (prim->b3 < 4) {
                prim->b3 -= 4;
            }
            prim->r0 = prim->r1 = prim->r2 = prim->r3;
            prim->b0 = prim->b1 = prim->b2 = prim->b3;
            prim->g0 = prim->g1 = prim->g2 = prim->g3;

            prim->drawMode &= ~DRAW_UNK02;
            if (--prim->v0 == 0) {
                prim->drawMode |= DRAW_HIDE;
            }
        }
    }
}
#endif

mistStruct D_us_801D3DA0[16];

#ifndef VERSION_PC
void func_80121F14(s32 velocityX, s32 velocityY) UNUSED {
    mistStruct* ptr = D_us_801D3DA0;
    s32 i;

    for (i = 0; i < LEN(D_us_801D3DA0); i++, ptr++) {
        ptr->posX.val += velocityX;
        ptr->posY.val += velocityY;
    }
}
#endif

s16 D_us_801D3EE0;
STATIC_PAD_BSS(2);
s16 D_us_801D3EE4;
STATIC_PAD_BSS(2);
s16 D_us_801D3EE8;
STATIC_PAD_BSS(2);
s16 D_us_801D3EEC;
STATIC_PAD_BSS(2);
s16 D_us_801D3EF0;
STATIC_PAD_BSS(2);
s16 D_us_801D3EF4;
STATIC_PAD_BSS(2);
s16 D_us_801D3EF8;
STATIC_PAD_BSS(2);
s16 D_us_801D3EFC;
STATIC_PAD_BSS(2);

Primitive D_us_801D3F00[8];

s16 D_us_80181F18[] = {
    0x48, 0x48, 0x48, 0x44, 0x44, 0x40, 0x40, 0x3C, 0x40, 0x40, 0x44,
    0x48, 0x4C, 0x50, 0x58, 0x60, 0x60, 0x58, 0x50, 0x4C, 0x48, 0x44,
    0x40, 0x40, 0x3C, 0x40, 0x40, 0x44, 0x44, 0x48, 0x48, 0x48,
};

s16 D_us_80181F58[] = {
    -1, -1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0,  0,
    0,  0,  0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, -1, -1,
};

u32 D_us_80181F98[8] = {7, 0, 1, 2, 3, 4, 5, 6};
u32 D_us_80181FB8[8] = {2, 1, 0, 7, 6, 5, 4, 3};

static Primitive* func_80121F58(
    bool arg0, s32 arg1, Primitive* arg2, s16 facingLeft) {
    s32 primU0;
    s32 tempU;
    s32 tempV;
    s32 primU1;
    s32 primV0;
    s32 primV1;
    s16 angle1;
    s16 angle2;
    Primitive* prim;
    s32 i;

    if (arg0 == false) {
        if (facingLeft) {
            prim = &D_us_801D3F00[D_us_80181F98[arg1 >> 1]];
            primU0 = prim->u0;
            tempU = prim->u1;
            primV0 = prim->v0;
            tempV = prim->v1;
        } else {
            prim = &D_us_801D3F00[D_us_80181FB8[arg1 >> 1]];
            primU0 = prim->u1;
            tempU = prim->u0;
            primV0 = prim->v1;
            tempV = prim->v0;
        }

        primU1 = (prim->u0 + prim->u1) / 2;
        primV1 = (prim->v0 + prim->v1) / 2;

        if (arg1 & 1) {
            primU0 = primU1;
            primU1 = tempU;
            primV0 = primV1;
            primV1 = tempV;
        }
        arg2->u0 = primU0;
        arg2->v0 = primV0;
        arg2->u1 = primU1;
        arg2->v1 = primV1;
        arg2->u3 = arg2->u2 = prim->u2;
        arg2->v3 = arg2->v2 = prim->v2;
        if (DOPPLEGANGER.animSet == 0xF) {
            arg2->tpage = 0x118;
        } else {
#ifdef VERSION_PSP
            arg2->tpage = 0x18;
#else
            arg2->tpage = 0x10;
#endif
        }
        arg2->clut = 0x20F;
        arg2->priority = DOPPLEGANGER.zPriority + 2;
        arg2->drawMode = DRAW_DITHERING | DRAW_UNK_100 | DRAW_TPAGE2 |
                         DRAW_TPAGE | DRAW_COLORS | DRAW_UNK02 | DRAW_TRANSP;
        arg2 = arg2->next;
    } else {
        angle1 = D_us_801D3DA0[arg1].angle1;
        angle2 = D_us_801D3DA0[(arg1 + 1) % 16].angle1;

        for (i = 0; i < 4; i++) {
            // nb: the cos/sin arguments seem to be invariant, could've been
            // extracted outside the loop
            arg2->u0 = 0x60 + ((((rcos(angle1) >> 4) * 8) * (i + 1)) >> 8);
            arg2->v0 = 0xA0 - ((((rsin(angle1) >> 4) * 8) * (i + 1)) >> 8);
            arg2->u1 = 0x60 + ((((rcos(angle2) >> 4) * 8) * (i + 1)) >> 8);
            arg2->v1 = 0xA0 - ((((rsin(angle2) >> 4) * 8) * (i + 1)) >> 8);

            if (i == 3) {
                if (arg2->u0 < 4) {
                    arg2->u0 = -1;
                }
                if (arg2->u1 < 4) {
                    arg2->u1 = -1;
                }
                if (arg2->v0 < 4) {
                    arg2->v0 = -1;
                }
                if (arg2->v1 < 4) {
                    arg2->v1 = -1;
                }
            }

            arg2->u2 = 0x60 + ((((rcos(angle1) >> 4) * 8) * i) >> 8);
            arg2->v2 = 0xA0 - ((((rsin(angle1) >> 4) * 8) * i) >> 8);
            arg2->u3 = 0x60 + ((((rcos(angle2) >> 4) * 8) * i) >> 8);
            arg2->v3 = 0xA0 - ((((rsin(angle2) >> 4) * 8) * i) >> 8);

            arg2->tpage = 0x18;
            arg2->clut = 0x20F;
            arg2->priority = DOPPLEGANGER.zPriority + 4;
            arg2->drawMode =
                DRAW_DITHERING | DRAW_UNK_100 | DRAW_TPAGE2 | DRAW_TPAGE |
                DRAW_COLORS | DRAW_UNK02 | DRAW_TRANSP;
            arg2 = arg2->next;
        }
    }
    return arg2;
}

s32 D_us_801D40A0;
static s32 D_us_801D40A4;
static s32 D_us_801D40A8;
s32 D_us_801D40AC;
STATIC_PAD_BSS(0x68);

// spawns mist (player transform)
#ifdef VERSION_PSP
INCLUDE_ASM("boss/bo4_psp/nonmatchings/bo4/unk_49A6C", EntityMist);
#else
void EntityMist(Entity* self) {
    Primitive* prim;
    Primitive* mistPrim;
    mistStruct* mistStruct;
    s16 xVar;
    s16 yVar;
    s16 angle;
    s16 magnitude;
    s16 angle2;
    s16 angle3;
    s16 xSize;
    s16 ySize;
    s16 baseSize;
    s16 index;
    s16 xVar2;
    s16 yVar2;
    s16 xVar3;
    s16 yVar3;
    s32 primColor1;
    s32 primColor2;
    s32 primColor3;
    s32 primColor4;
    s16 xVar4;
    s16 yVar4;
    s32 velX;
    s32 velY;
    s32 cosine;
    s32 sine;
    s32 i;
    s32 j;
    s16 xVar5;
    s16 yVar5;

    velX = DOPPLEGANGER.velocityX >> 1;
    velY = DOPPLEGANGER.velocityY >> 1;
    primColor1 = D_us_801D3EF0 + (rsin(D_us_801D3EE0) >> 8);
    primColor2 = D_us_801D3EF4 + (rsin(D_us_801D3EE4) >> 8);
    primColor3 = D_us_801D3EF8 + (rsin(D_us_801D3EE8) >> 8);
    primColor4 = D_us_801D3EFC + (rsin(D_us_801D3EEC) >> 8);
    D_us_801D3EE0 += 0x20;
    D_us_801D3EE4 -= 0x20;
    D_us_801D3EE8 += 0x20;
    D_us_801D3EEC -= 0x20;
    self->ext.mist.timer++;

    self->facingLeft = DOPPLEGANGER.facingLeft;
    if (DOPPLEGANGER.animSet == 0xF) {
        self->facingLeft = 0;
    }

    if (self->step != 0) {
        mistStruct = D_us_801D3DA0;
        velX = self->posX.i.hi - D_us_801D40AC;
        for (i = 0; i < 16; i++) {
            mistStruct->posX.i.hi += velX;
            mistStruct++;
        }
    }

    switch (self->step) {
    case 0:
        // Weird that we set FLAG_DEAD here.
        self->params = FLAG_UNK_4000 | FLAG_UNK_1000 | FLAG_UNK_800 |
                       FLAG_UNK_400 | FLAG_DEAD;
        EntityDopplegangerBlinkWhite(self);
        if (self->primIndex == -1) {
            goto block_147;
        }
        prim = &g_PrimBuf[self->primIndex];
        mistPrim = D_us_801D3F00;
        for (i = 0; i < LEN(D_us_801D3F00); i++, mistPrim++) {
            *mistPrim = *prim;
            prim = prim->next;
        }
        g_api.FreePrimitives(self->primIndex);
        self->step = 0;
        self->primIndex = g_api.AllocPrimitives(PRIM_GT4, 80);
        if (self->primIndex == -1) {
            goto block_147;
        }

        D_us_801D3EE0 = rand() & PSP_RANDMASK;
        D_us_801D3EE4 = rand() & PSP_RANDMASK;
        D_us_801D3EE8 = rand() & PSP_RANDMASK;
        D_us_801D3EEC = rand() & PSP_RANDMASK;

        D_us_801D3EF0 = 0xEF;
        D_us_801D3EF4 = 0xEF;
        D_us_801D3EF8 = 0xEF;
        D_us_801D3EFC = 0xEF;
        mistStruct = &D_us_801D3DA0[0];
        for (i = 0; i < LEN(D_us_801D3DA0); i++, mistStruct++) {
            if (self->facingLeft) {
                mistPrim = &D_us_801D3F00[D_us_80181F98[i >> 1]];
                xVar = mistPrim->x0;
                yVar = mistPrim->y0;
            } else {
                mistPrim = &D_us_801D3F00[D_us_80181FB8[i >> 1]];
                xVar = mistPrim->x1;
                yVar = mistPrim->y1;
            }
            xVar5 = (mistPrim->x0 + mistPrim->x1) / 2;
            yVar5 = (mistPrim->y0 + mistPrim->y1) / 2;
            if (!(i & 1)) {
                mistStruct->posX.i.hi = xVar;
                mistStruct->posY.i.hi = yVar;
            } else {
                mistStruct->posX.i.hi = xVar5;
                mistStruct->posY.i.hi = yVar5;
            }
            xVar2 = mistPrim->x2;
            yVar2 = mistPrim->y2;
            angle = mistStruct->angle1 = (i * 4096) / 16;
            mistStruct->angle2 = i << 9;
            xVar3 = mistStruct->posX.i.hi - xVar2;
            yVar3 = mistStruct->posY.i.hi - yVar2;
            mistStruct->size =
                (SquareRoot12(((xVar3 * xVar3) + (yVar3 * yVar3)) << 0xC) >>
                 0xC);
        }
        xVar4 = xVar2;
        yVar4 = yVar2;
        self->ext.mist.xCurrent = xVar2 - DOPPLEGANGER.posX.i.hi;
        self->ext.mist.yCurrent = yVar2 - DOPPLEGANGER.posY.i.hi;
        self->posX.i.hi = xVar4;
        self->posY.i.hi = yVar4;
        prim = &g_PrimBuf[self->primIndex];
        for (j = 0; j < 16; j++) {
            prim = func_80121F58(0, j, prim, self->facingLeft);
        }
        for (j = 0; j < 16; j++) {
            prim = func_80121F58(1, j, prim, self->facingLeft);
        }
        self->flags =
            FLAG_UNK_10000000 | FLAG_POS_CAMERA_LOCKED | FLAG_HAS_PRIMS;
        self->step++;
        self->ext.mist.timer = 0;
        D_us_801D40A0 = 0;
        break;
    case 1:
        D_us_801D3EF0 -= 1;
        D_us_801D3EF4 -= 2;
        D_us_801D3EF8 -= 3;
        D_us_801D3EFC -= 4;
        if (D_us_801D3EF0 < 0xD0) {
            D_us_801D3EF0 = 0xD0;
        }
        if (D_us_801D3EF4 < 0xA0) {
            D_us_801D3EF4 = 0xA0;
        }
        if (D_us_801D3EF8 < 0x70) {
            D_us_801D3EF8 = 0x70;
        }
        if (D_us_801D3EFC < 0x30) {
            D_us_801D3EFC = 0x30;
        }
        if (self->ext.mist.timer == 0x4F) {
            self->step++;
            g_api.func_800EA538(5);
        }
        // Fallthrough!
    case 2:
        j = 0;
        if (self->ext.mist.timer < 16) {
            j = 1;
        }
        xVar4 = DOPPLEGANGER.posX.i.hi + self->ext.mist.xCurrent;
        yVar4 = DOPPLEGANGER.posY.i.hi + self->ext.mist.yCurrent;
        xVar = xVar4 - self->posX.i.hi;
        yVar = yVar4 - self->posY.i.hi;
        angle = ratan2(-yVar, xVar);
        magnitude = SquareRoot12(((xVar * xVar) + (yVar * yVar)) << 0xC) >> 0xC;
        if (magnitude > 10) {
            cosine = rcos(angle) * 8;
            sine = -rsin(angle) * 8;
            if (magnitude > 35) {
                cosine *= 2;
                sine *= 2;
            }
            if (magnitude > 60) {
                cosine *= 2;
                sine *= 2;
            }
            self->posX.val += (s32)cosine;
            self->posY.val += (s32)sine;
        }
        angle3 = angle;
        xVar3 = (self->posX.i.hi + xVar4) / 2;
        yVar3 = (self->posY.i.hi + yVar4) / 2;
        xVar2 = abs(xVar) / 2;
        yVar2 = abs(yVar) / 2;
        mistStruct = D_us_801D3DA0;
        for (i = 0; i < LEN(D_us_801D3DA0); i++, mistStruct++) {
            if ((mistStruct->size < 0x28) && (g_GameTimer & 1)) {
                mistStruct->size++;
            }
            angle2 = mistStruct->angle1;
            index = ((angle3 - angle2) & 0xFFF);
            index = (index >> 7) & 0x1F;
            baseSize = D_us_80181F18[index];
            xSize = ((mistStruct->size + xVar2) * baseSize) / 80;
            ySize = ((mistStruct->size + yVar2) * baseSize) / 80;
            xVar = xVar3 + (((rcos(angle2) >> 4) * xSize) >> 8);
            yVar = yVar3 - (((rsin(angle2) >> 4) * ySize) >> 8);
            mistStruct->angle2 += 8;
            angle = mistStruct->angle2;
            if (j) {
                xVar += (rcos(angle) >> 4) * 2 >> 8;
                yVar -= (rsin(angle) >> 4) * 2 >> 8;
            } else {
                xVar += (((rcos(angle) >> 4) * 6) >> 8);
                yVar -= (((rsin(angle) >> 4) * 6) >> 8);
            }
            xVar5 = xVar - mistStruct->posX.i.hi;
            yVar5 = yVar - mistStruct->posY.i.hi;
            angle = ratan2(-yVar5, xVar5) & 0xFFF;
            mistStruct->posX.val += rcos(angle) << 5;
            mistStruct->posY.val += -rsin(angle) << 5;
            if (D_us_80181F58[index] == -1) {
                mistStruct->posX.val += (s32)velX;
                mistStruct->posY.val += (s32)velY;
            }
        }
        D_us_801D40A0 += 8;
        if (D_us_801D40A0 >= 0xFF) {
            D_us_801D40A0 = 0xFF;
        }
        break;
    case 3:
        g_api.FreePrimitives(self->primIndex);
        self->step = 0;
        xVar = self->ext.mist.xCurrent;
        yVar = self->ext.mist.yCurrent;
        self->params = FLAG_UNK_4000 | FLAG_UNK_1000 | FLAG_UNK_800 |
                       FLAG_UNK_400 | FLAG_DEAD;
        EntityDopplegangerBlinkWhite(self);
        if (self->primIndex == -1) {
            self->flags = 0;
            DestroyEntity(self);
            goto block_147;
        }
        prim = &g_PrimBuf[self->primIndex];
        mistPrim = D_us_801D3F00;
        for (i = 0; i < 8; i++, mistPrim++) {
            *mistPrim = *prim;
            prim = prim->next;
        }
        g_api.FreePrimitives(self->primIndex);
        self->ext.mist.xCurrent = xVar;
        self->ext.mist.yCurrent = yVar;
        self->ext.mist.timer = 0;
        self->step = 4;
        self->primIndex = g_api.AllocPrimitives(PRIM_GT4, 80);
        if (self->primIndex == -1) {
            DestroyEntity(self);
        } else {
            mistStruct = D_us_801D3DA0;
            for (i = 0; i < LEN(D_us_801D3DA0); i++, mistStruct++) {
                if (self->facingLeft) {
                    mistPrim = &D_us_801D3F00[D_us_80181F98[i >> 1]];
                    xVar = mistPrim->x0;
                    yVar = mistPrim->y0;
                } else {
                    mistPrim = &D_us_801D3F00[D_us_80181FB8[i >> 1]];
                    xVar = mistPrim->x1;
                    yVar = mistPrim->y1;
                }
                xVar5 = (mistPrim->x0 + mistPrim->x1) / 2;
                yVar5 = (mistPrim->y0 + mistPrim->y1) / 2;
                if (!(i & 1)) {
                    mistStruct->xOffset = xVar;
                    mistStruct->yOffset = yVar;
                } else {
                    mistStruct->xOffset = xVar5;
                    mistStruct->yOffset = yVar5;
                }
                mistStruct->xOffset -= DOPPLEGANGER.posX.i.hi;
                mistStruct->yOffset -= DOPPLEGANGER.posY.i.hi;
                xVar2 = mistPrim->x2;
                yVar2 = mistPrim->y2;
            }
            self->ext.mist.xTarget = xVar2 - DOPPLEGANGER.posX.i.hi;
            self->ext.mist.yTarget = yVar2 - DOPPLEGANGER.posY.i.hi;
            prim = &g_PrimBuf[self->primIndex];
            for (j = 0; j < 16; j++) {
                prim = func_80121F58(0, j, prim, self->facingLeft);
            }
            for (j = 0; j < 16; j++) {
                prim = func_80121F58(1, j, prim, self->facingLeft);
            }
            self->flags =
                FLAG_UNK_10000000 | FLAG_POS_CAMERA_LOCKED | FLAG_HAS_PRIMS;
            xVar4 = DOPPLEGANGER.posX.i.hi + self->ext.mist.xCurrent;
            yVar4 = DOPPLEGANGER.posY.i.hi + self->ext.mist.yCurrent;
            self->posX.i.hi = DOPPLEGANGER.posX.i.hi;
            self->posY.i.hi = DOPPLEGANGER.posY.i.hi;
            D_us_801D40A0 = 0xFF;
            break;
        }
        goto block_147;
    case 4:
        if (self->ext.mist.timer == 0xC) {
            g_api.func_800EA538(5);
            g_api.func_800EA5E4(0x8802);
        }
        j = 0;
        // These if-statements seem to allow for the mist to stretch and move
        // The mist's current location moves toward the target in X and Y.
        if (self->ext.mist.xCurrent > self->ext.mist.xTarget) {
            self->ext.mist.xCurrent--;
        }
        if (self->ext.mist.xCurrent < self->ext.mist.xTarget) {
            self->ext.mist.xCurrent++;
        }
        if (self->ext.mist.yCurrent > self->ext.mist.yTarget) {
            self->ext.mist.yCurrent--;
        }
        if (self->ext.mist.yCurrent < self->ext.mist.yTarget) {
            self->ext.mist.yCurrent++;
        }
        xVar4 = DOPPLEGANGER.posX.i.hi + self->ext.mist.xCurrent;
        yVar4 = DOPPLEGANGER.posY.i.hi + self->ext.mist.yCurrent;

        xVar = xVar4 - self->posX.i.hi;
        yVar = yVar4 - self->posY.i.hi;

        mistStruct = D_us_801D3DA0;

        for (i = 0; i < LEN(D_us_801D3DA0); i++, mistStruct++) {
            xVar = (mistStruct->xOffset + DOPPLEGANGER.posX.i.hi) -
                   mistStruct->posX.i.hi;
            yVar = (mistStruct->yOffset + DOPPLEGANGER.posY.i.hi) -
                   mistStruct->posY.i.hi;
            if (xVar | yVar) {
                angle = ratan2(-yVar, xVar);
                mistStruct->posX.val += rcos(angle) << 5;
                mistStruct->posY.val += -rsin(angle) << 5;
            }
            mistStruct->posX.val += DOPPLEGANGER.velocityX;
            mistStruct->posY.val += DOPPLEGANGER.velocityY;
        }
        if (self->ext.mist.timer > 0x18) {
            self->step++;
            self->ext.mist.timer = 0x10;
        }
        D_us_801D40A0 -= 0x10;
        if (D_us_801D40A0 <= 0) {
            D_us_801D40A0 = 0;
        }
        break;
    case 5:
        if (self->ext.mist.timer <= 0) {
            DestroyEntity(self);
        }
        return;
    }
    D_us_801D40A4 = 0xFF - D_us_801D40A0;

    prim = &g_PrimBuf[self->primIndex];
    for (j = 0; j < LEN(D_us_801D3DA0); j++) {
        xVar5 = D_us_801D3DA0[j].posX.i.hi;
        yVar5 = D_us_801D3DA0[j].posY.i.hi;
        xVar2 = D_us_801D3DA0[(j + 1) % 16].posX.i.hi;
        yVar2 = D_us_801D3DA0[(j + 1) % 16].posY.i.hi;
        prim->x0 = xVar5;
        prim->y0 = yVar5;
        prim->x1 = xVar2;
        prim->y1 = yVar2;
        prim->x2 = xVar4;
        prim->x3 = xVar4;
        prim->y2 = yVar4;
        prim->y3 = yVar4;
        PGREY(prim, 0) = PGREY(prim, 1) = 0;
        PGREY(prim, 2) = PGREY(prim, 3) = D_us_801D40A4;

        prim = prim->next;
    }
    for (j = 0; j < LEN(D_us_801D3DA0); j++) {
        xVar5 = D_us_801D3DA0[j].posX.i.hi;
        yVar5 = D_us_801D3DA0[j].posY.i.hi;
        xVar2 = D_us_801D3DA0[(j + 1) % 16].posX.i.hi;
        yVar2 = D_us_801D3DA0[(j + 1) % 16].posY.i.hi;
        for (i = 0; i < 4; prim = prim->next, i++) {
            prim->x0 = xVar4 + (i + 1) * (xVar5 - xVar4) / 4;
            prim->y0 = yVar4 + (i + 1) * (yVar5 - yVar4) / 4;
            prim->x1 = xVar4 + (i + 1) * (xVar2 - xVar4) / 4;
            prim->y1 = yVar4 + (i + 1) * (yVar2 - yVar4) / 4;
            prim->x2 = xVar4 + i * (xVar5 - xVar4) / 4;
            prim->y2 = yVar4 + i * (yVar5 - yVar4) / 4;
            prim->x3 = xVar4 + i * (xVar2 - xVar4) / 4;
            prim->y3 = yVar4 + i * (yVar2 - yVar4) / 4;
            switch (i) {
            case 0:
                PGREY(prim, 0) = PGREY(prim, 1) =
                    (D_us_801D40A0 * primColor2 / 256) & 0xFF;
                PGREY(prim, 2) = PGREY(prim, 3) =
                    (D_us_801D40A0 * primColor1 / 256) & 0xFF;
                break;
            case 1:
                PGREY(prim, 0) = PGREY(prim, 1) =
                    (D_us_801D40A0 * primColor3 / 256) & 0xFF;
                PGREY(prim, 2) = PGREY(prim, 3) =
                    (D_us_801D40A0 * primColor2 / 256) & 0xFF;
                break;
            case 2:
                PGREY(prim, 0) = PGREY(prim, 1) =
                    (D_us_801D40A0 * primColor4 / 256) & 0xFF;
                PGREY(prim, 2) = PGREY(prim, 3) =
                    (D_us_801D40A0 * primColor3 / 256) & 0xFF;
                break;
            case 3:
                PGREY(prim, 0) = PGREY(prim, 1) = 0;
                PGREY(prim, 2) = PGREY(prim, 3) =
                    (D_us_801D40A0 * primColor4 / 256) & 0xFF;
                break;
            }
        }
    }

block_147:
    self->facingLeft = DOPPLEGANGER.facingLeft;
    D_us_801D40A8 = self->posX.val;
    D_us_801D40AC = self->posX.i.hi;
}
#endif

RECT D_us_80181FD8 = {0, 0x100, 0x10, 0x40};
static RECT D_us_80181FE0 = {0x20, 0x100, 0x10, 0x40};

extern s32 D_us_801D4DF0;
extern s32 D_us_801D4DF4;
static u8 D_us_80181FE8[][8] = {
    {0x00, 0x11, 0x21, 0x22, 0x32, 0x43, 0x44, 0x54},
    {0x90, 0x91, 0x82, 0x83, 0x94, 0xA5, 0xB6, 0xB7},
    {0xC7, 0xD8, 0xE8, 0xF7, 0xE9, 0xEA, 0xEB, 0xEC},
    {0x7F, 0x7E, 0x7D, 0x8C, 0x9B, 0xAA, 0xB9, 0xA8},
    {0x07, 0x17, 0x27, 0x38, 0x47, 0x57, 0x56, 0x58},
    {0x7A, 0x6B, 0x5C, 0x4D, 0x3E, 0x2D, 0x1C, 0x0C},
    {0xE0, 0xF1, 0xF2, 0xF3, 0xF4, 0xE4, 0xF5, 0xF6},
    {0xB9, 0xC9, 0xCA, 0xCB, 0xCC, 0xDD, 0xEE, 0xEF},
};
extern s32 g_stone_flag;

// player dissolves into pixels
void EntityDopplegangerDissolves(Entity* self) {
    const int PrimCount = 36;
    const int Iterations = 16;

    u8 xMargin;
    u8 yMargin;
    u8 wSprite;
    u8 hSprite;
    s16 blueOffset;
    s16 xPivot;
    s16 yPivot;
    s16 width;
    s16 height;
    u_long* data;
    s32 sp3C;
    s16* sp38;
    Primitive* prim;
    s32 i;
    u8* s2;
    s16 s3;
    s16 s4;
    s16 s5;
    s32 s6;
    s16 s7;
    s16 sp42;
    u8* plSprite;

    s32 xBase, yBase, angle, tangent;

    if (DOPPLEGANGER.ext.player.anim != 0x38 &&
        (self->step == 2 || self->step == 3)) {
        self->step = 4;
        LoadImage(&D_us_80181FE0, (u_long*)D_us_801D421C);
        self->ext.dissolve.unk7E = rand() & 0xFF;
        self->ext.dissolve.unk7C = 0x30;
        prim = &g_PrimBuf[self->primIndex];
        for (i = 0; i < PrimCount; i++) {
            prim->drawMode &= ~DRAW_HIDE;
            prim = prim->next;
        }
    }

    switch (self->step) {
    case 0:
        self->primIndex = g_api.AllocPrimitives(PRIM_GT4, PrimCount);
        if (self->primIndex == -1) {
            return;
        }
        self->flags = FLAG_HAS_PRIMS | FLAG_POS_CAMERA_LOCKED;
        self->ext.dissolve.unk7C = 0;
        self->ext.dissolve.unk80 = rand() & 7;
        self->ext.dissolve.unk7E =
            D_us_80181FE8[self->ext.dissolve.unk80][self->ext.dissolve.unk7C];

        s5 = self->posX.i.hi = DOPPLEGANGER.posX.i.hi;
        s7 = self->posY.i.hi = DOPPLEGANGER.posY.i.hi;
        self->facingLeft = DOPPLEGANGER.facingLeft;

        sp38 = (s16*)D_us_801B0A78[DOPPLEGANGER.animCurFrame & 0x7FFF];
        sp42 = *sp38++;
        sp42 &= 0x7FFF;
        plSprite = doppleganger_sprites[sp42];
        xMargin = 4;
        yMargin = 1;
        wSprite = xMargin + plSprite[0];
        hSprite = yMargin + plSprite[1];
        width = wSprite - xMargin;
        height = hSprite - yMargin;
        s3 = width / 6;
        s4 = height / 6;
        xPivot = sp38[0] + plSprite[2];
        yPivot = sp38[1] + plSprite[3];
        if (self->facingLeft) {
            s5 = s5 - xPivot;
        } else {
            s5 = s5 + xPivot;
        }
        s7 = s7 + yPivot;

        prim = &g_PrimBuf[self->primIndex];
        for (i = 0; i < PrimCount; i++) {

            if (self->facingLeft) {
                prim->x0 = prim->x2 = (s5 - (s3 * (i % 6))) + 1;
                prim->x1 = prim->x3 = prim->x0 - s3;
            } else {
                prim->x0 = prim->x2 = s5 + (s3 * (i % 6));
                prim->x1 = prim->x3 = prim->x0 + s3;
            }
            prim->y0 = prim->y1 = s7 + (s4 * (i / 6));
            prim->y2 = prim->y3 = prim->y0 + s4;
            prim->u0 = prim->u2 = (xMargin) + (s3 * (i % 6)) + 0x80;
            prim->u1 = prim->u3 = prim->u0 + s3;
            prim->v0 = prim->v1 = (yMargin + (s4 * (i / 6)));
            prim->v2 = prim->v3 = prim->v0 + s4;
            prim->g0 = (((i / 6) * 2) + (rand() & 3));
            prim->tpage = 0x10;
            prim->clut = DOPPLEGANGER.palette & 0x7FFF;
            prim->priority = DOPPLEGANGER.zPriority + 2;
            prim->drawMode = DRAW_HIDE | DRAW_UNK02;
            prim->r3 = i * 7;
            prim = prim->next;
        }
        self->step++;
        break;
    case 1:
        StoreImage(&D_us_80181FD8, (u_long*)D_us_801D421C);

        self->step++;
        // fallthrough
    case 2:
        DOPPLEGANGER.animCurFrame |= 0x8000;
        if (g_Dop.padTapped & (PAD_UP | PAD_RIGHT | PAD_DOWN | PAD_LEFT)) {
            self->step++;
        }
        break;
    case 3:
        DOPPLEGANGER.animCurFrame |= 0x8000;
        self->ext.dissolve.unk7E =
            D_us_80181FE8[self->ext.dissolve.unk80][self->ext.dissolve.unk7C];
        data = (u_long*)D_us_801D421C;
        s2 = (u8*)data;
        s2 = s2 + ((self->ext.dissolve.unk7E >> 1) & 7);
        s2 = s2 + (((self->ext.dissolve.unk7E & 0xFF) >> 4) << 5);
        for (i = 0; i < Iterations; i++) {
            if (rand() & 3) {
                if (self->ext.dissolve.unk7E & 1) {
                    if (*(s2 + (i & 3) * 8 + (i >> 2) * 0x200)) {
                        *(s2 + (i & 3) * 8 + (i >> 2) * 0x200) &= 0xF0;
                        *(s2 + (i & 3) * 8 + (i >> 2) * 0x200) |= 1;
                    }
                } else if (*(s2 + (i & 3) * 8 + (i >> 2) * 0x200)) {
                    *(s2 + (i & 3) * 8 + (i >> 2) * 0x200) &= 0x0F;
                    *(s2 + (i & 3) * 8 + (i >> 2) * 0x200) |= 0x10;
                }
            }
        }
        LoadImage(&D_us_80181FD8, data);
        if (++self->ext.dissolve.unk7C == 8) {
            self->ext.dissolve.unk7C = 0;
            self->ext.dissolve.unk80 += 1;
            self->ext.dissolve.unk80 &= 7;
            self->step = 2;
        }
        break;
    case 4:
        if (DOPPLEGANGER.step == Dop_Kill || g_Dop.unk6A <= 0) {
            g_stone_flag = 1;
            if (g_Timer % 2 == 0) {
                goto after_loop;
            }
        } else if (g_Timer % 3 == 0) {
            break;
        }

        for (sp3C = 0; sp3C < 6; sp3C++) {
            data = (u_long*)D_us_801D421C;
            s2 = (u8*)data;
            s2 = s2 + ((self->ext.dissolve.unk7E >> 1) & 7);
            s2 = s2 + (((self->ext.dissolve.unk7E & 0xFF) >> 4) << 5);
            for (i = 0; i < Iterations; i++) {
                if (self->ext.dissolve.unk7E & 1) {
                    *(s2 + (i & 3) * 8 + (i >> 2) * 0x200) &= 0xF0;
                } else {
                    *(s2 + (i & 3) * 8 + (i >> 2) * 0x200) &= 0x0F;
                }
            }
            // some sort of prng state
            self->ext.dissolve.unk7E += 0x23;
            self->ext.dissolve.unk7E &= 0xFF;
        }

        LoadImage(&D_us_80181FE0, data);
        if (--self->ext.dissolve.unk7C <= 0) {
            if ((DOPPLEGANGER.step == Dop_Kill) || g_Dop.unk6A <= 0) {
                if (self->ext.dissolve.unk7C < -0x1F) {
                    g_stone_flag = 2;
                    DestroyEntity(self);
                    return;
                }
            } else {
                DestroyEntity(self);
                return;
            }
        }

    after_loop:
        prim = &g_PrimBuf[self->primIndex];
        for (i = 0; i < PrimCount; i++) {
            if (prim->r0 == 0) {
                if (--prim->g0 == 0) {
                    prim->r0++;
                    prim->b0 = ((rand() & 3) + 0xF8);
                    prim->r1 = 0x20 - ((i / 6) * 2);
                }
            } else if (DOPPLEGANGER.step == Dop_Kill || g_Dop.unk6A <= 0) {
                xBase = D_us_801D4DF0 - (prim->x0 + prim->x1) / 2;
                yBase = D_us_801D4DF4 - ((prim->y0 + prim->y2) / 2);
                tangent = ratan2(-yBase, xBase);
                angle = prim->r3;
                angle *= 0x10;
                if ((angle - tangent) < 0) {
                    angle += 0x80;
                }

                if ((angle - tangent) > 0) {
                    angle -= 0x80;
                }
                angle &= 0xFFF;
                xBase = rcos(angle) >> 0xB;
                yBase = rsin(angle) >> 0xB;
                angle >>= 4;
                prim->r3 = angle;
                prim->x0 += xBase;
                prim->x1 += xBase;
                prim->x2 += xBase;
                prim->x3 += xBase;
                prim->y0 -= yBase;
                prim->y1 -= yBase;
                prim->y2 -= yBase;
                prim->y3 -= yBase;
            } else {
                if (prim->r1) {
                    prim->r1--;
                } else {
                    prim->drawMode = DRAW_HIDE;
                }
                if (prim->b0 < 0x30 || prim->b0 > 0xD0) {
                    prim->b0 += 2;
                }
                blueOffset = (s16)((s8)prim->b0 >> 4);
                prim->y0 += blueOffset;
                prim->y1 += blueOffset;
                prim->y2 += blueOffset;
                prim->y3 += blueOffset;
            }
            prim = prim->next;
        }
        break;
    }

    if (DOPPLEGANGER.step == Dop_Kill || g_Dop.unk6A <= 0) {
        g_stone_flag = 1;
    }
    func_us_801C5354(1, 1);
}

#ifdef VERSION_PSP
u_long D_us_801D421C[0x200];
#endif
