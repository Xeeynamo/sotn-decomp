// SPDX-License-Identifier: AGPL-3.0-or-later
#include "ric.h"

#if defined(VERSION_PSP)
extern AnimationFrame* g_RicEmptyAnimGroup[ZERO_LEN]; // BSS
#else
static AnimationFrame* g_RicEmptyAnimGroup[ZERO_LEN] = {};
#endif

static u8 D_80154674[][4] = {
    {16, 127, 63, 0},
    {16, 127, 0, 0},
    {16, 63, 63, 127},
    {16, 63, 127, 63},
    {16, 47, 63, 127}};

static SubweaponDef subweapons_def[] = {
#include "gen/subweapons.h"
};
STATIC_ASSERT(LEN(subweapons_def) == NUM_WEAPONS, "weapons array wrong size");

static Entity* RicGetFreeEntity(s16 start, s16 end) {
    Entity* entity = &g_Entities[start];
    s16 i;

    for (i = start; i < end; i++, entity++) {
        if (entity->entityId == E_NONE) {
            return entity;
        }
    }
    return NULL;
}

static Entity* RicGetFreeEntityReverse(s16 start, s16 end) {
    Entity* entity = &g_Entities[end - 1];
    s16 i;
    for (i = end - 1; i >= start; i--, entity--) {
        if (entity->entityId == E_NONE) {
            return entity;
        }
    }
    return NULL;
}

#if defined(VERSION_PSP)
extern s32 D_80174F80[11];
#else
static s32 D_80174F80[11];
#endif
void func_8015F9F0(Entity* entity) {
    s32 i;
    s32 enemyId;

    if (entity < &g_Entities[32]) {
        entity->enemyId = 1;
        return;
    }

    for (i = 0;; i++) {
        for (enemyId = 2; enemyId < LEN(D_80174F80); ++enemyId) {
            if (D_80174F80[enemyId] == i) {
                ++D_80174F80[enemyId];
                entity->enemyId = enemyId;
                return;
            }
        }
    }
}

#if defined(VERSION_PSP)
extern u8 D_80174FAC;
extern u8 D_80174FB0;
extern u8 D_80174FB4;
extern u8 D_80174FB8;
#else
static u8 D_80174FAC;
STATIC_PAD_BSS(3);
static u8 D_80174FB0;
STATIC_PAD_BSS(3);
static u8 D_80174FB4;
STATIC_PAD_BSS(3);
static u8 D_80174FB8;
STATIC_PAD_BSS(3);
#endif
void func_8015FA5C(s32 arg0) {
    D_80174FAC = D_80154674[arg0][0];
    D_80174FB0 = D_80154674[arg0][1];
    D_80174FB4 = D_80154674[arg0][2];
    D_80174FB8 = D_80154674[arg0][3];
}

void RicSetSubweaponParams(Entity* entity) {
    SubweaponDef* subwpn = &subweapons_def[entity->ext.subweapon.subweaponId];
    if (g_Player.timers[PL_T_INVINCIBLE_SCENE]) {
        entity->attack = subwpn->attack * 2;
    } else {
        entity->attack = subwpn->attack;
    }
    entity->attackElement = subwpn->attackElement;
    entity->hitboxState = subwpn->hitboxState;
    entity->nFramesInvincibility = subwpn->nFramesInvincibility;
    entity->stunFrames = subwpn->stunFrames;
    entity->hitEffect = subwpn->hitEffect;
    entity->entityRoomIndex = subwpn->entityRoomIndex;
    entity->attack = g_api.func_800FD664(entity->attack);
    func_8015F9F0(entity);
}

// We're playing as Richter and we used a subweapon (normal or crash)
s32 RicCheckSubweapon(
    SubweaponDef* actualSubwpn, s32 isItemCrash, s32 useHearts) {
    SubweaponDef* subwpn;

    // Not an item crash. Just read the item in.
    if (isItemCrash == 0) {
        *actualSubwpn = subweapons_def[g_Status.subWeapon];
        if (g_Status.hearts >= actualSubwpn->heartCost) {
            if (useHearts) {
                g_Status.hearts -= actualSubwpn->heartCost;
            }
            return g_Status.subWeapon;
        }
        return -1;
    }
    // If it's a crash, load the subweapon by referencing our
    // subweapon's crash ID and loading that.
    subwpn = &subweapons_def[g_Status.subWeapon];
    *actualSubwpn = subweapons_def[subwpn->crashId];
    if (g_Status.hearts >= actualSubwpn->heartCost) {
        if (useHearts) {
            g_Status.hearts -= actualSubwpn->heartCost;
        }
        return g_Status.subWeapon;
    }
    return -1;
}

// Corresponding DRA function is func_80119E78
u8 uv_anim_801548F4[6][8] = {
    {0x00, 0x50, 0x10, 0x50, 0x00, 0x60, 0x10, 0x60},
    {0x10, 0x50, 0x20, 0x50, 0x10, 0x60, 0x20, 0x60},
    {0x70, 0x40, 0x80, 0x40, 0x70, 0x50, 0x80, 0x50},
    {0x70, 0x30, 0x78, 0x30, 0x70, 0x38, 0x78, 0x38},
    {0x78, 0x30, 0x80, 0x30, 0x78, 0x38, 0x80, 0x38},
    {0x70, 0x38, 0x78, 0x38, 0x77, 0x40, 0x78, 0x40}};
s32 func_8015FDB0(Primitive* prim, s16 posX, s16 posY) {
    s16 offset;
    s32 ret;
    u8* uvAnim;

    ret = 0;
    uvAnim = uv_anim_801548F4[0];
    if (prim->b0 >= 6) {
        prim->b0 = 0;
        ret = -1;
    }

    uvAnim = &uvAnim[prim->b0 * 8];

    if (prim->b0 >= 3) {
        offset = 4;
    } else {
        offset = 6;
    }

    prim->x0 = posX - offset;
    prim->y0 = posY - offset;
    prim->x1 = posX + offset;
    prim->y1 = posY - offset;
    prim->x2 = posX - offset;
    prim->y2 = posY + offset;
    prim->x3 = posX + offset;
    prim->y3 = posY + offset;
    prim->u0 = *uvAnim++;
    prim->v0 = *uvAnim++;
    prim->u1 = *uvAnim++;
    prim->v1 = *uvAnim++;
    prim->u2 = *uvAnim++;
    prim->v2 = *uvAnim++;
    prim->u3 = *uvAnim++;
    prim->v3 = *uvAnim;

    prim->b1++;
    if (!(prim->b1 & 1)) {
        prim->b0++;
    }
    return ret;
}

// Corresponding DRA function is func_80119F70
#if defined(VERSION_PSP)
extern Point16 D_80174FBC[16];
#else
static Point16 D_80174FBC[16];
#endif
void RicEntityHitByHoly(Entity* entity) {
    Primitive* prim;
    s32 i;
    s32 temp;
    s16 hitboxX;
    s16 hitboxY;
    s16 temp_xRand;
    s16 temp_yRand;

    switch (entity->step) {
    case 0:
        entity->primIndex =
            (s16)g_api.AllocPrimitives(PRIM_GT4, LEN(D_80174FBC));
        if (entity->primIndex == -1) {
            DestroyEntity(entity);
            return;
        }
        entity->flags =
            FLAG_HAS_PRIMS | FLAG_POS_PLAYER_LOCKED | FLAG_UNK_20000;
        hitboxX = PLAYER.posX.i.hi + PLAYER.hitboxOffX;
        hitboxY = PLAYER.posY.i.hi + PLAYER.hitboxOffY;
        prim = &g_PrimBuf[entity->primIndex];
        for (i = 0; i < LEN(D_80174FBC); i++) {
            temp_xRand = hitboxX + rand() % 24 - 12;
            temp_yRand = hitboxY + rand() % 48 - 24;
            D_80174FBC[i].x = temp_xRand;
            D_80174FBC[i].y = temp_yRand;
            prim->clut = 0x1B2;
            prim->tpage = 0x1A;
            prim->b0 = 0;
            prim->b1 = 0;
            prim->g0 = 0;
            prim->g1 = (rand() & 7) + 1;
            prim->g2 = 0;
            prim->priority = PLAYER.zPriority + 4;
            prim->drawMode = DRAW_UNK_100 | DRAW_TPAGE | DRAW_HIDE |
                             DRAW_UNK02 | DRAW_TRANSP;
            if (rand() & 1) {
                prim->drawMode =
                    DRAW_UNK_100 | DRAW_UNK_40 | DRAW_TPAGE2 | DRAW_TPAGE |
                    DRAW_HIDE | DRAW_UNK02 | DRAW_TRANSP;
            }
            prim = prim->next;
        }
        entity->step++;
        break;
    case 1:
        if (!(g_Player.status & PLAYER_STATUS_UNK10000)) {
            DestroyEntity(entity);
            return;
        }
        break;
    }

    prim = &g_PrimBuf[entity->primIndex];
    for (i = 0; i < 16; i++) {
        switch (prim->g0) {
        case 0:
            if (--prim->g1 == 0) {
                prim->g0++;
            }
            break;
        case 1:
            hitboxX = D_80174FBC[i].x;
            hitboxY = D_80174FBC[i].y;
            temp = func_8015FDB0(prim, hitboxX, hitboxY);
            D_80174FBC[i].y--;
            if (temp < 0) {
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

// same as DRA/func_8011F074
static AnimationFrame anim_smoke_dark[] = {
    POSE(2, 1, 0),  POSE(2, 2, 0),  POSE(2, 3, 0),  POSE(2, 4, 0),
    POSE(2, 5, 0),  POSE(2, 6, 0),  POSE(2, 7, 0),  POSE(2, 8, 0),
    POSE(2, 9, 0),  POSE(2, 10, 0), POSE(2, 11, 0), POSE(2, 12, 0),
    POSE(2, 13, 0), POSE_END};
#if defined(VERSION_PSP)
extern s32 D_80174FFC;
#else
static s32 D_80174FFC;
#endif
void RicEntityHitByDark(Entity* entity) {
    s16 x, y;

    switch (entity->step) {
    case 0:
        entity->flags =
            FLAG_UNK_20000 | FLAG_UNK_100000 | FLAG_POS_CAMERA_LOCKED;
        entity->unk5A = 0x79;
        entity->animSet = ANIMSET_DRA(14);
        entity->zPriority = PLAYER.zPriority + 2;
        entity->palette = PAL_OVL(0x19F);
        if (D_80174FFC & 1) {
            entity->drawMode = DRAW_UNK_40 | DRAW_TPAGE2 | DRAW_TPAGE;
        } else {
            entity->drawMode = DRAW_TPAGE;
        }
        D_80174FFC++;
        entity->opacity = 0xFF;
        entity->drawFlags = FLAG_DRAW_SCALEX | FLAG_DRAW_SCALEY |
                            FLAG_DRAW_UNK10 | FLAG_DRAW_UNK20;
        entity->scaleX = entity->scaleY = 0x40;
        entity->anim = anim_smoke_dark;
        entity->posY.i.hi += (rand() % 35) - 15;
        entity->posX.i.hi += (rand() % 20) - 10;
        entity->velocityY = -0x6000 - (rand() & 0x3FFF);
        entity->step++;
        break;
    case 1:
        if (entity->opacity > 16) {
            entity->opacity -= 8;
        }
        entity->posY.val += entity->velocityY;
        entity->scaleX += 8;
        entity->scaleY += 8;
        if (entity->poseTimer < 0) {
            DestroyEntity(entity);
        }
        break;
    }
}

static void RicEntityDummy(Entity* self) {}

static void func_801603BC(void) {}

void RicEntityFactory(Entity* self);
void RicEntitySmokePuff(Entity* self);
void RicEntitySubwpnCross(Entity* self);
void func_80169C10(Entity* self);
void RicEntityHitByCutBlood(Entity* self);
void RicEntitySubwpnCrossTrail(Entity* self);
void RicEntitySubwpnHolyWater(Entity* self);
void RicEntitySubwpnHolyWaterFlame(Entity* self);
void func_80161C2C(Entity* self);
void RicEntityWhip(Entity* self);
void RicEntityCrashHydroStorm(Entity* self);
void RicEntityCrashCrossBeam(Entity* self);
void RicEntitySubwpnCrashCross(Entity* self);
void RicEntityNotImplemented1(Entity* self);
void RicEntityNotImplemented2(Entity* self);
void RicEntityArmBrandishWhip(Entity* self);
void func_80167964(Entity* self);
void RicEntityDummy(Entity* self);
void func_80161EF8(Entity* self);
void RicEntityNotImplemented3(Entity* self);
void RicEntityRevivalColumn(Entity* self);
void RicEntityApplyMariaPowerAnim(Entity* self);
void RicEntitySlideKick(Entity* self);
void RicEntityBladeDash(Entity* self);
void func_801623E0(Entity* self);
void func_80162604(Entity* self);
void RicEntityMaria(Entity* self);
void RicEntityMariaPowers(Entity* self);
void func_80160F0C(Entity* self);
void RicEntityNotImplemented4(Entity* self);
void RicEntityPlayerBlinkWhite(Entity* self);
void RicEntitySubwpnCrashCrossParticles(Entity* self);
void func_801641A0(Entity* self);
void RicEntityShrinkingPowerUpRing(Entity* self);
void RicEntitySubwpnHolyWaterBreakGlass(Entity* self);
void RicEntitySubwpnThrownAxe(Entity* self);
void RicEntityCrashAxe(Entity* self);
void RicEntitySubwpnKnife(Entity* self);
void func_80160D2C(Entity* self);
void RicEntityHitByIce(Entity* self);
void RicEntityHitByLightning(Entity* self);
void RicEntitySubwpnReboundStone(Entity* self);
void RicEntitySubwpnThrownVibhuti(Entity* self);
void RicEntitySubwpnAgunea(Entity* self);
void RicEntityAguneaHitEnemy(Entity* self);
void RicEntityCrashVibhuti(Entity* self);
void RicEntityVibhutiCrashCloud(Entity* self);
void RicEntityCrashReboundStone(Entity* self);
void func_8016D9C4(Entity* self);
void RicEntityCrashReboundStoneExplosion(Entity* self);
void RicEntityCrashBible(Entity* self);
void RicEntityCrashBibleBeam(Entity* self);
void RicEntitySubwpnBible(Entity* self);
void RicEntitySubwpnBibleTrail(Entity* self);
void RicEntitySubwpnStopwatch(Entity* self);
void RicEntitySubwpnStopwatchCircle(Entity* self);
void RicEntityCrashStopwatch(Entity* self);
void func_8016F198(Entity* self);
void RicEntityAguneaCircle(Entity* self);
void RicEntityAguneaLightning(Entity* self);
void RicEntityCrashReboundStoneParticles(Entity* self);
void RicEntityHitByDark(Entity* self);
void RicEntityHitByHoly(Entity* self);
void RicEntityCrashStopwatchDoneSparkle(Entity* self);
void RicEntityStopwatchCrashLightning(Entity* self);
void RicEntityTeleport(Entity* self);
void RicEntityDummy(Entity* self);
static PfnEntityUpdate entity_functions[] = {
    RicEntityDummy,
    RicEntityFactory,
    RicEntitySmokePuff,
    RicEntitySubwpnCross,
    func_80169C10,
    RicEntityHitByCutBlood,
    RicEntitySubwpnCrossTrail,
    RicEntitySubwpnHolyWater,
    RicEntitySubwpnHolyWaterFlame,
    func_80161C2C,
    RicEntityWhip,
    RicEntityCrashHydroStorm,
    RicEntityCrashCrossBeam,
    RicEntitySubwpnCrashCross,
    RicEntityNotImplemented1,
    RicEntityNotImplemented2,
    RicEntityArmBrandishWhip,
    func_80167964,
    RicEntityDummy,
    func_80161EF8,
    RicEntityNotImplemented3,
    RicEntityRevivalColumn,
    RicEntityApplyMariaPowerAnim,
    RicEntitySlideKick,
    RicEntityBladeDash,
    func_801623E0,
    func_80162604,
    RicEntityMaria,
    RicEntityMariaPowers,
    func_80160F0C,
    RicEntityNotImplemented4,
    RicEntityPlayerBlinkWhite,
    RicEntitySubwpnCrashCrossParticles,
    func_801641A0,
    RicEntityShrinkingPowerUpRing,
    RicEntitySubwpnHolyWaterBreakGlass,
    RicEntitySubwpnThrownAxe,
    RicEntityCrashAxe,
    RicEntitySubwpnKnife,
    func_80160D2C,
    RicEntityHitByIce,
    RicEntityHitByLightning,
    RicEntitySubwpnReboundStone,
    RicEntitySubwpnThrownVibhuti,
    RicEntitySubwpnAgunea,
    RicEntityAguneaHitEnemy,
    RicEntityCrashVibhuti,
    RicEntityVibhutiCrashCloud,
    RicEntityCrashReboundStone,
    func_8016D9C4,
    RicEntityCrashReboundStoneExplosion,
    RicEntityCrashBible,
    RicEntityCrashBibleBeam,
    RicEntitySubwpnBible,
    RicEntitySubwpnBibleTrail,
    RicEntitySubwpnStopwatch,
    RicEntitySubwpnStopwatchCircle,
    RicEntityCrashStopwatch,
    func_8016F198,
    RicEntityAguneaCircle,
    RicEntityAguneaLightning,
    RicEntityCrashReboundStoneParticles,
    RicEntityHitByDark,
    RicEntityHitByHoly,
    RicEntityCrashStopwatchDoneSparkle,
    RicEntityStopwatchCrashLightning,
    RicEntityTeleport,
    RicEntityDummy};
STATIC_ASSERT(LEN(entity_functions) == NUM_ENTITIES, "entity array wrong size");

// Corresponding DRA function is UpdatePlayerEntities
extern AnimationFrame* g_RicEmptyAnimGroup[];
void RicUpdatePlayerEntities(void) {
    SubweaponDef subwpn;
    s32 isPrologueTimeStopped;
    s32 enemyId;
    s32 i;
    s32 j;
    Entity* entity;

    isPrologueTimeStopped = g_unkGraphicsStruct.unk20;
    entity = g_CurrentEntity = &g_Entities[4];
    for (i = 4; i < STAGE_ENTITY_START; i++, g_CurrentEntity++, entity++) {
        if (entity->entityId != 0) {
            if (entity->step == 0) {
                entity->pfnUpdate = entity_functions[entity->entityId];
            }
            if (!isPrologueTimeStopped || (entity->flags & FLAG_UNK_10000)) {
                entity->pfnUpdate(entity);
                entity = g_CurrentEntity;
                if (entity->entityId != 0) {
                    if (!(entity->flags & FLAG_KEEP_ALIVE_OFFCAMERA) &&
                        (entity->posX.i.hi > 288 || entity->posX.i.hi < -32 ||
                         entity->posY.i.hi > 256 || entity->posY.i.hi < -16)) {
                        DestroyEntity(g_CurrentEntity);
                    } else if (entity->flags & FLAG_UNK_100000) {
                        g_api.UpdateAnim(0, g_RicEmptyAnimGroup);
                    }
                }
            }
        }
    }
    if (D_80174FAC) {
        D_80174FAC--;
        if (D_80174FAC & 1) {
            g_api.func_800EA5AC(1, D_80174FB0, D_80174FB4, D_80174FB8);
        }
    }
    D_80174F80[1] = D_80174F80[2] = 0;
    if (g_Entities[E_WEAPON].enemyId == 1) {
        D_80174F80[1] = 1;
    } else if (g_Entities[E_WEAPON].enemyId == 2) {
        D_80174F80[2] = 1;
    }
    for (j = 3; j < 11; j++) {
        D_80174F80[j] = 0;
    }
    entity = &g_Entities[17];
    for (j = 17; j < 48; entity++, j++) {
        enemyId = entity->enemyId;
        if (enemyId > 2) {
            D_80174F80[enemyId]++;
        }
    }
    // This IF will fire if we have enough hearts to use a subweapon crash.
    // No idea what it's doing here.
    if (RicCheckSubweapon(&subwpn, true, false) >= 0) {
        g_Player.status |= PLAYER_STATUS_UNK200000;
    }
    if (g_Player.status & (PLAYER_STATUS_DEAD | PLAYER_STATUS_UNK80000)) {
        FntPrint("dead player\n");
        entity = &g_Entities[4];
        for (i = 4; i < 64; i++, entity++) {
            entity->hitboxState = 0;
        }
    }
}

// Similar to the version in DRA but with some logic removed.
// arg2 is unused, but needed to match other functions that call this function,
// probably part of the code for a debug build
Entity* RicCreateEntFactoryFromEntity(
    Entity* source, u32 factoryParams, s32 arg2) {
    Entity* entity = RicGetFreeEntity(8, 16);
    if (!entity) {
        return NULL;
    }
    DestroyEntity(entity);
    entity->entityId = E_FACTORY;
    // the parent pointer must align for anything the factory creates
    entity->ext.factory.parent = source;
    entity->posX.val = source->posX.val;
    entity->posY.val = source->posY.val;
    entity->facingLeft = source->facingLeft;
    entity->zPriority = source->zPriority;
    entity->params = factoryParams & 0xFFF;
    entity->ext.factory.paramsBase = (factoryParams & 0xFF0000) >> 8;
    if (source->flags & FLAG_UNK_10000) {
        entity->flags |= FLAG_UNK_10000;
    }
    return entity;
}

static FactoryBlueprint blueprints[] = {
#include GEN_VERSION(blueprints.h)
};
STATIC_ASSERT(LEN(blueprints) == NUM_BLUEPRINTS, "bp array wrong size");

// Similar to same function in DRA
static u8 entity_ranges[NUM_BLUEPRINT_KIND][2] = {
    {0x30, 0x3F}, // B_DECORATION
    {0x20, 0x2F}, // B_WEAPON
    {0x10, 0x1E}, // B_WEAPON_UNIQUE
    {0x10, 0x3F}, // B_EFFECTS
    {0x1F, 0x1F}, // B_WHIP
    {0x30, 0x30}, // B_CUTSCENE_MARIA
    {0x10, 0x2F}, // B_WEAPON_CHILDREN
};
void RicEntityFactory(Entity* self) {
    Entity* newEntity;
    s16 nPerCycle;
    s16 i;
    s16 startIndex;
    s16 endIndex;
    u8* data;

    if (self->step == 0) {
        data = (u8*)&blueprints[self->params];
        self->ext.factory.newEntityId = *data++;
        self->ext.factory.amount = *data++;
        self->ext.factory.nPerCycle = *data & 0x3F;
        self->ext.factory.isNonCritical = (s16)(*data >> 7) & 1;
        self->ext.factory.incParamsKind = (s16)(*data++ >> 6) & 1;
        self->ext.factory.tCycle = *data++;
        self->ext.factory.kind = *data & 0x7;
        self->ext.factory.origin = (s16)(*data++ >> 3) & 0x1F;
        self->ext.factory.delay = *data;
        self->flags |= FLAG_KEEP_ALIVE_OFFCAMERA;
        self->step++;
        switch (self->ext.factory.origin) {
        case B_ORIGIN_DEFAULT:
            self->flags |= FLAG_POS_CAMERA_LOCKED;
            break;
        case B_ORIGIN_FOLLOW_PLAYER_WHILE_PLAYER_IS_RUNNING:
            self->flags |= FLAG_UNK_20000;
        case B_ORIGIN_FOLLOW_PLAYER:
        case B_ORIGIN_SUBWEAPON_CRASH_PARTICLE:
            self->flags |= FLAG_POS_PLAYER_LOCKED;
        case B_ORIGIN_FOLLOW_PLAYER_WHILE_PLAYER_IS_HIT:
        case B_ORIGIN_FOLLOW_PLAYER_WHILE_PLAYER_IS_NOT_HIT:
            self->posX.val = PLAYER.posX.val;
            self->posY.val = PLAYER.posY.val;
            break;
        case B_ORIGIN_FOLLOW_PARENT_ENTITY:
            self->flags |= FLAG_POS_PLAYER_LOCKED;
            self->posX.val = self->ext.factory.parent->posX.val;
            self->posY.val = self->ext.factory.parent->posY.val;
            break;
        }
    } else {
        switch (self->ext.factory.origin) {
        case B_ORIGIN_DEFAULT:
            break;
        case B_ORIGIN_SUBWEAPON_CRASH_PARTICLE:
            if (g_Player.unk4E) {
                DestroyEntity(self);
                return;
            }
        case B_ORIGIN_FOLLOW_PLAYER:
            self->posX.val = PLAYER.posX.val;
            self->posY.val = PLAYER.posY.val;
            break;
        case B_ORIGIN_FOLLOW_PLAYER_WHILE_PLAYER_IS_RUNNING:
            self->posX.val = PLAYER.posX.val;
            self->posY.val = PLAYER.posY.val;
            if (PLAYER.step != PL_S_RUN) {
                self->entityId = 0;
                return;
            }
            break;
        case B_ORIGIN_FOLLOW_PLAYER_WHILE_PLAYER_IS_HIT:
            self->posX.val = PLAYER.posX.val;
            self->posY.val = PLAYER.posY.val;
            if (PLAYER.step == PL_S_HIT) {
                self->entityId = 0;
                return;
            }
            break;
        case B_ORIGIN_FOLLOW_PLAYER_WHILE_PLAYER_IS_NOT_HIT:
            self->posX.val = PLAYER.posX.val;
            self->posY.val = PLAYER.posY.val;
            if (PLAYER.step != PL_S_HIT) {
                self->entityId = 0;
                return;
            }
            break;
        case B_ORIGIN_FOLLOW_PARENT_ENTITY:
            self->posX.val = self->ext.factory.parent->posX.val;
            self->posY.val = self->ext.factory.parent->posY.val;
            break;
        }
    }
    if (self->ext.factory.delay) {
        if (--self->ext.factory.delay) {
            return;
        }
        self->ext.factory.delay = self->ext.factory.tCycle;
    }
    nPerCycle = self->ext.factory.nPerCycle;
    for (i = 0; i < nPerCycle; i++) {
        data = entity_ranges[0];
        data += self->ext.factory.kind * 2;
        startIndex = *data++;
        endIndex = *data;
        if (self->ext.factory.kind == B_DECORATION) {
            newEntity = RicGetFreeEntityReverse(startIndex, endIndex + 1);
        } else if (self->ext.factory.kind == B_WHIP) {
            newEntity = &g_Entities[31];
        } else if (self->ext.factory.kind == B_CUTSCENE_MARIA) {
            newEntity = &g_Entities[48];
        } else {
            newEntity = RicGetFreeEntity(startIndex, endIndex + 1);
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
        newEntity->entityId =
            self->ext.factory.newEntityId + self->ext.factory.entityIdMod;
        newEntity->params = self->ext.factory.paramsBase;
        // The child  (newEntity) is not an ent factory, but because the
        // factory creates many entities, we can't pick a particular extension.
        // But we're not allowed to use generic, so i'll just reuse entFactory.
        newEntity->ext.factory.parent = self->ext.factory.parent;
        newEntity->posX.val = self->posX.val;
        newEntity->posY.val = self->posY.val;
        newEntity->facingLeft = self->facingLeft;
        newEntity->zPriority = self->zPriority;
        if (self->flags & FLAG_UNK_10000) {
            newEntity->flags |= FLAG_UNK_10000;
        }
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

void RicEntitySlideKick(Entity* entity) {
    if (PLAYER.step != PL_S_SLIDE) {
        DestroyEntity(entity);
    } else {
        entity->posX.i.hi = PLAYER.posX.i.hi;
        entity->posY.i.hi = PLAYER.posY.i.hi;
        entity->facingLeft = PLAYER.facingLeft;
        if (entity->step == 0) {
            entity->flags = FLAG_UNK_20000 | FLAG_POS_PLAYER_LOCKED |
                            FLAG_KEEP_ALIVE_OFFCAMERA;
            entity->hitboxOffX = 0x14;
            entity->hitboxOffY = 0xC;
            entity->hitboxWidth = entity->hitboxHeight = 9;
            entity->ext.subweapon.subweaponId = PL_W_KICK;
            RicSetSubweaponParams(entity);
            entity->ext.subweapon.timer = entity->hitboxState;
            entity->step++;
        }
        entity->hitboxState = entity->ext.subweapon.timer;
        if (PLAYER.pose < 2) {
            entity->hitboxState = 0;
        }
        if (PLAYER.pose > 7) {
            DestroyEntity(entity);
        }
    }
}

void func_80160D2C(Entity* self) {
    if (PLAYER.step != PL_S_SLIDE_KICK) {
        DestroyEntity(self);
        return;
    }
    self->posX.i.hi = PLAYER.posX.i.hi;
    self->posY.i.hi = PLAYER.posY.i.hi;
    self->facingLeft = PLAYER.facingLeft;
    if (self->step == 0) {
        self->flags =
            FLAG_UNK_20000 | FLAG_POS_PLAYER_LOCKED | FLAG_KEEP_ALIVE_OFFCAMERA;
        self->hitboxOffX = 0x14;
        self->hitboxWidth = self->hitboxHeight = 9;
        self->ext.subweapon.subweaponId = PL_W_23;
        RicSetSubweaponParams(self);
        self->step++;
    }

    if (PLAYER.animCurFrame == 140) {
        self->hitboxOffY = 0;
    }

    if (PLAYER.animCurFrame == 141) {
        self->hitboxOffY = 12;
    }

    if (self->hitFlags) {
        g_Player.unk44 |= 0x80;
    } else {
        g_Player.unk44 &= ~0x80;
    }
    self->hitFlags = 0;
}

// created from a blueprint, #24
void RicEntityBladeDash(Entity* self) {
    if (PLAYER.step != PL_S_BLADEDASH) {
        DestroyEntity(self);
    } else {
        self->posX.i.hi = PLAYER.posX.i.hi;
        self->posY.i.hi = PLAYER.posY.i.hi;
        self->facingLeft = PLAYER.facingLeft;
        if (self->step == 0) {
            self->flags = FLAG_UNK_20000 | FLAG_POS_PLAYER_LOCKED |
                          FLAG_KEEP_ALIVE_OFFCAMERA;
            self->hitboxOffX = self->hitboxOffY = 0;
            self->hitboxWidth = self->hitboxHeight = 20;
            // Wow! So blade dash is treated as a subweapon!
            self->ext.subweapon.subweaponId = PL_W_BIBLE_BEAM;
            RicSetSubweaponParams(self);
            self->step++;
        }
        if (PLAYER.pose > 18) {
            DestroyEntity(self);
        }
    }
}

void func_80160F0C(Entity* self) {
    if (PLAYER.step != PL_S_HIGHJUMP) {
        DestroyEntity(self);
        return;
    }
    self->posX.i.hi = PLAYER.posX.i.hi;
    self->posY.i.hi = PLAYER.posY.i.hi;
    self->facingLeft = PLAYER.facingLeft;
    if (self->step == 0) {
        self->flags =
            FLAG_UNK_20000 | FLAG_POS_PLAYER_LOCKED | FLAG_KEEP_ALIVE_OFFCAMERA;
        self->hitboxOffX = 0xC;
        self->hitboxOffY = -0x1A;
        self->hitboxWidth = 12;
        self->hitboxHeight = 12;
        // High jump attack is a subweapon!
        self->ext.subweapon.subweaponId = PL_W_HIGHJUMP;
        RicSetSubweaponParams(self);
        self->step++;
    }
}

// Entity ID #2. Created by 6 blueprints:
// 0, 1, 24, 74, 75, 76.
// Matches DRA func_8011B5A4
static s16 pos_x_80154C50[] = {0, -4, -8, -12, -16, -20};
static s32 velocity_x_80154C5C[] = {
    FIX(-0.1875), FIX(-0.25), -0x6000, FIX(-0.5), FIX(-0.625), FIX(-0.75)};
static s16 rot_x_80154C74[] = {0x0030, 0x0040, 0x0050, 0x0060, 0x0070, 0x0080};
static AnimationFrame anim_smoke_puff[] = {
    POSE(1, 0x01, 0), POSE(1, 0x02, 0), POSE(1, 0x03, 0), POSE(1, 0x04, 0),
    POSE(1, 0x05, 0), POSE(1, 0x06, 0), POSE(1, 0x07, 0), POSE(1, 0x08, 0),
    POSE(1, 0x09, 0), POSE(1, 0x0A, 0), POSE(1, 0x0B, 0), POSE(1, 0x0C, 0),
    POSE(1, 0x0D, 0), POSE(1, 0x0E, 0), POSE(1, 0x0F, 0), POSE(1, 0x10, 0),
    POSE(1, 0x11, 0), POSE(1, 0x12, 0), POSE(1, 0x13, 0), POSE(1, 0x14, 0),
    POSE(1, 0x15, 0), POSE(1, 0x16, 0), POSE(1, 0x17, 0), POSE(1, 0x18, 0),
    POSE_END};
static u8 sensors1_80154CE4[] = {2, 9, 3, 10, 1, 8, 4, 11, 0, 7, 5, 12, 6, 13};
static u8 sensors2_80154CF4[] = {2, 9, 3, 10, 4, 11, 5, 12, 6, 13};
void RicEntitySmokePuff(Entity* self) {
    s16 posX;
    s32 i;

    s16 paramsHi = self->params >> 8;
    s16 paramsLo = self->params & 0xFF;

    if ((g_Player.status & PLAYER_STATUS_UNK20000) && (paramsHi != 9)) {
        DestroyEntity(self);
        return;
    }
    switch (self->step) {
    case 0:
        self->animSet = 5;
        self->anim = anim_smoke_puff;
        self->zPriority = PLAYER.zPriority + 2;
        self->flags = FLAG_POS_CAMERA_LOCKED | FLAG_UNK_100000 | FLAG_UNK_10000;
        self->drawMode = DRAW_TPAGE2 | DRAW_TPAGE;
        self->drawFlags =
            FLAG_DRAW_SCALEX | FLAG_DRAW_SCALEY | FLAG_DRAW_OPACITY;
        self->opacity = 0x60;
        posX = pos_x_80154C50[paramsLo];
        if (paramsHi == 0) {
            posX += 6;
        }
        if (paramsHi == 1) {
            posX -= 8;
        }
        if (paramsHi == 2) {
            posX -= 6;
        }
        if (paramsHi == 5) {
            posX = -6;
        }
        if (paramsHi == 3) {
            self->posY.i.hi -= 8;
        }
        if (paramsHi == 4) {
            for (i = paramsLo * 2; i < LEN(sensors1_80154CE4); i++) {
                if (g_Player.colWall[sensors1_80154CE4[i]].effects &
                    (EFFECT_UNK_0002 | EFFECT_SOLID)) {
                    break;
                }
            }
            if (i == LEN(sensors1_80154CE4)) {
                DestroyEntity(self);
                return;
            }
            self->posX.i.hi =
                PLAYER.posX.i.hi + g_RicSensorsWall[sensors1_80154CE4[i]].x;
            self->posY.i.hi =
                PLAYER.posY.i.hi + g_RicSensorsWall[sensors1_80154CE4[i]].y;
            self->velocityY = FIX(-0.25);
            self->scaleX = rot_x_80154C74[1] + 0x40;
            self->scaleY = self->scaleX;
            self->step++;
            return;
        }
        if (paramsHi == 8) {
            for (i = paramsLo * 2; i < LEN(sensors2_80154CF4); i++) {
                if (g_Player.colWall[sensors2_80154CF4[i]].effects &
                    (EFFECT_UNK_0002 | EFFECT_SOLID)) {
                    break;
                }
            }
            if (i == LEN(sensors2_80154CF4)) {
                DestroyEntity(self);
                return;
            }
            self->posX.i.hi =
                PLAYER.posX.i.hi + g_RicSensorsWall[sensors2_80154CF4[i]].x;
            self->posY.i.hi =
                PLAYER.posY.i.hi + g_RicSensorsWall[sensors2_80154CF4[i]].y;
            self->velocityY = velocity_x_80154C5C[paramsLo];
            self->scaleX = rot_x_80154C74[paramsLo] + 0x20;
            self->scaleY = self->scaleX;
            self->step++;
            return;
        }
        if (paramsHi == 1) {
            if (g_Player.vram_flag & TOUCHING_ANY_SLOPE) {
                posX /= 2;
            }
        }
        if (self->facingLeft) {
            posX = -posX;
        }
        self->posX.i.hi += posX;
        self->posY.i.hi += 0x18;
        self->scaleX = rot_x_80154C74[paramsLo] + 0x40;
        self->velocityY = velocity_x_80154C5C[paramsLo];
        if (paramsHi == 1) {
            self->velocityY = FIX(-0.25);
            RicSetSpeedX(-0x3000);
            self->scaleX = rot_x_80154C74[1] + 0x40;
        }
        if (paramsHi == 5) {
            self->velocityY = velocity_x_80154C5C[4 - paramsLo * 2];
        }
        if (paramsHi == 2) {
            self->velocityY = FIX(-0.5);
            RicSetSpeedX(-0x3000);
            self->scaleX = rot_x_80154C74[1] + 0x40;
        }
        self->scaleY = self->scaleX;
        if (paramsHi == 10) {
            self->posY.i.hi -= 6;
        }
        self->step++;
        break;
    case 1:
        self->opacity -= 2;
        self->posY.val += self->velocityY;
        self->posX.val += self->velocityX;
        if (self->poseTimer < 0) {
            DestroyEntity(self);
            return;
        }
        break;
    }
}

// Corresponding DRA function is func_8011E4BC
static unkStr_8011E4BC D_80154D00 = {
    0x08, 0xC0, 0x60, 0x00, 0x01, 0x01, 0x0004, 0x0033, 0x0003, 0x08800000};
static unkStr_8011E4BC D_80154D10 = {
    0x10, 0x7F, 0x7F, 0x7F, 0x01, 0x01, 0x0002, 0x0033, 0x0001, 0x0C800000};
static unkStr_8011E4BC D_80154D20 = {
    0x08, 0x7F, 0x7F, 0x7F, 0x02, 0x02, 0x0002, 0x0033, 0x0000, 0x08800000};
static unkStr_8011E4BC D_80154D30 = {
    0x06, 0x7F, 0xFF, 0xFF, 0x01, 0x01, 0x0004, 0x0073, 0x0003, 0x08800000};
static unkStr_8011E4BC D_80154D40 = {
    0x0C, 0xC0, 0x60, 0x00, 0x01, 0x01, 0x0004, 0x0033, 0x0003, 0x08800000};
static unkStr_8011E4BC D_80154D50 = {
    0x0C, 0x7F, 0x00, 0x00, 0x03, 0x03, 0x0002, 0x0002, 0x0004, 0x0C800000};
static unkStr_8011E4BC D_80154D60 = {
    0x08, 0x1F, 0x1F, 0x7F, 0x01, 0x01, 0x0004, 0x0033, 0x0006, 0x0C800000};
static unkStr_8011E4BC D_80154D70 = {
    0x14, 0x7F, 0x7F, 0xC0, 0x01, 0x01, 0xFFFE, 0x0033, 0x0007, 0x0C800000};
static unkStr_8011E4BC D_80154D80 = {
    0x06, 0xC0, 0xC0, 0xC0, 0x02, 0x02, 0x0002, 0x007B, 0x0008, 0x08800000};
static unkStr_8011E4BC D_80154D90 = {
    0x10, 0x7F, 0x7F, 0x7F, 0x01, 0x01, 0x0002, 0x0033, 0x0009, 0x08800000};
static unkStr_8011E4BC* D_80154DA0[] = {
    &D_80154D00, &D_80154D10, &D_80154D20, &D_80154D30, &D_80154D40,
    &D_80154D50, &D_80154D60, &D_80154D70, &D_80154D80, &D_80154D90};
void RicEntityHitByCutBlood(Entity* self) {
    byte stackpad[0x28];
    u8 thickness;
    s16 variant;
    s16 playerX;
    s16 playerY;
    s16 velocityScale;
    s16 velocityRnd;
    s32 timer;
    s16 x;
    s16 y;
    s16 rnd;
    s32 i;
    unkStr_8011E4BC* props;
    FakePrim* tilePrim;

    variant = (self->params) >> 8;
    props = D_80154DA0[variant];
    x = self->posX.i.hi;
    y = self->posY.i.hi;
    playerX = PLAYER.posX.i.hi;
    playerY = PLAYER.posY.i.hi;
    switch (self->step) {
    case 0:
        self->primIndex = g_api.func_800EDB58(PRIM_TILE_ALT, props->count + 1);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags = props->flags;
        switch (props->unkA) {
        case 8:
            self->ext.et_8011E4BC.unk7C = 0x100;
            break;
        case 7:
            self->ext.et_8011E4BC.unk7C = 0x3F;
            break;
        case 4:
            self->ext.et_8011E4BC.unk7C = 0x2F;
            break;
        case 3:
        case 6:
            self->ext.et_8011E4BC.unk7C = 0x1F;
            break;
        }
        tilePrim = (FakePrim*)&g_PrimBuf[self->primIndex];
        i = 0;
        while (1) {
            tilePrim->drawMode = props->drawMode;
            tilePrim->priority = PLAYER.zPriority + props->priority;
            if (tilePrim->next == NULL) {
                tilePrim->drawMode &= ~DRAW_HIDE;
                tilePrim->y0 = tilePrim->x0 = tilePrim->w = 0;
                break;
            }
            tilePrim->posX.i.hi = x;
            tilePrim->posY.i.hi = y;
            tilePrim->posX.i.lo = tilePrim->posY.i.lo = 0;
            switch (props->unkA) {
            case 0:
                velocityRnd = rand() & PSP_RANDMASK;
                velocityScale = (velocityRnd & 1) + 2;
                tilePrim->velocityX.val = (rcos(velocityRnd) << velocityScale);
                tilePrim->velocityY.val = -(rsin(velocityRnd) << velocityScale);
                break;
            case 1:
            case 9:
                tilePrim->velocityX.val = ((rand() & 0x1FF) - 0x100) << 8;
                tilePrim->velocityY.val = ((rand() & 0x1FF) - 0x100) << 8;
                break;
            case 3:
                tilePrim->posX.i.hi = x + (rand() & 0xF) - 7;
                tilePrim->posY.i.hi = y - (rand() & 0xF);
                tilePrim->velocityY.val = FIX(-0.75) - (rand() & 0x7FFF);
                tilePrim->velocityX.val =
                    self->ext.et_8011E4BC.parent->velocityX;
                tilePrim->delay = (rand() & 0xF) + 0x10;
                break;
            case 4:
                rnd = rand() & 0x1F;
                tilePrim->posX.i.hi = x + rnd - 0x10;
                rnd = rand() & 0x1F;
                tilePrim->posY.i.hi = y + rnd - 0x14;
                rnd = rand() & 0x1F;
                tilePrim->velocityX.val = D_80175958[rnd];
                tilePrim->velocityY.val = D_801759D8[rnd];
                break;
            case 6:
                tilePrim->posX.i.hi = self->posX.i.hi + (rand() & 0xF) - 8;
                tilePrim->posY.i.hi = self->posY.i.hi + (rand() & 0xF) - 4;
                tilePrim->velocityY.val = (rand() & PSP_RANDMASK) + FIX(0.5);
                tilePrim->delay = (rand() & 0xF) + 0x10;
                break;
            case 7:
                tilePrim->posX.i.hi = x;
                tilePrim->posY.i.hi = y;
                if (i < 10) {
                    tilePrim->velocityY.val =
                        -((i * i * FIX(0.09375)) + FIX(0.125));
                } else {
                    tilePrim->velocityY.val =
                        (i - 10) * (i - 10) * FIX(0.09375) + FIX(0.125);
                }
                tilePrim->delay = 0x3F;
                break;
            case 8:
                tilePrim->posX.i.hi = x;
                tilePrim->posY.i.hi = y;
#if defined(VERSION_PSP)
                tilePrim->velocityX.val = ((rand() & 0x7FFF) - FIX(0.25)) >> 1;
#else
                tilePrim->velocityX.val = (rand() - FIX(0.25)) >> 1;
#endif
                tilePrim->velocityY.val = -((rand() & 0x1FFF) + FIX(0.375));
                tilePrim->timer = (i * 4);
                break;
            }
            tilePrim->x0 = tilePrim->posX.i.hi;
            tilePrim->y0 = tilePrim->posY.i.hi;
            tilePrim->r0 = props->r;
            tilePrim->g0 = props->g;
            tilePrim->b0 = props->b;
            tilePrim->w = props->w;
            tilePrim->h = props->h;
            i++;
            tilePrim = tilePrim->next;
        }
        self->step++;
        break;
    case 1:
        switch (props->unkA) {
        case 3:
        case 6:
        case 7:
        case 8:
            if (--self->ext.et_8011E4BC.unk7C == 0) {
                DestroyEntity(self);
                return;
            }
        case 4:
            if (--self->ext.et_8011E4BC.unk7C == 0) {
                DestroyEntity(self);
                return;
            }
            thickness = 3;
            timer = self->ext.et_8011E4BC.unk7C;
            if (timer < 9) {
                thickness--;
            }
            if (timer < 4) {
                thickness--;
            }
        }
        tilePrim = (FakePrim*)&g_PrimBuf[self->primIndex];
        i = 0;
        while (1) {
            if (tilePrim->next == NULL) {
                tilePrim->drawMode &= ~DRAW_HIDE;
                tilePrim->y0 = tilePrim->x0 = tilePrim->w = 0;
                return;
            }
            tilePrim->posX.i.hi = tilePrim->x0;
            tilePrim->posY.i.hi = tilePrim->y0;
            switch (props->unkA) {
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
                tilePrim->velocityY.val =
                    (tilePrim->velocityY.val + FIX(0.15625));
                tilePrim->r0 -= 3;
                tilePrim->g0 -= 3;
                tilePrim->b0 -= 3;
                if (tilePrim->r0 < 8) {
                    DestroyEntity(self);
                    return;
                }
                break;
            case 3:
            case 6:
            case 7:
                tilePrim->posY.val += tilePrim->velocityY.val;
                if (--tilePrim->delay < 0) {
                    tilePrim->drawMode |= DRAW_HIDE;
                }
                break;
            case 4:
                tilePrim->posX.val += tilePrim->velocityX.val;
                tilePrim->posY.val += tilePrim->velocityY.val;
                // There is probably a clever way to write this
                tilePrim->velocityY.val -= tilePrim->velocityY.val >> 5;
                if (!(timer & 7)) {
                    tilePrim->velocityX.val >>= 1;
                    tilePrim->velocityY.val >>= 1;
                    if (timer & 0x20) {
                        tilePrim->velocityY.val >>= 1;
                    }
                    if (timer == 0x18) {
                        tilePrim->drawMode = DRAW_UNK02;
                    }
                }
                tilePrim->w = tilePrim->h = thickness;
                break;
            case 8:
                if (tilePrim->timer == 0) {
                    tilePrim->drawMode &= ~DRAW_HIDE;
                    tilePrim->r0 -= 1;
                    tilePrim->g0 -= 1;
                    tilePrim->b0 -= 1;
                    tilePrim->posY.val += tilePrim->velocityY.val;
                    tilePrim->posX.val += tilePrim->velocityX.val;
                    if (*D_80097448 == 0 ||
                        !(tilePrim->posY.i.hi >
                          (PLAYER.posY.i.hi - *D_80097448 + 0x19))) {
                        tilePrim->drawMode |= DRAW_HIDE;
                    }
                } else {
                    tilePrim->timer--;
                }
                break;
            }
            tilePrim->x0 = tilePrim->posX.i.hi;
            tilePrim->y0 = tilePrim->posY.i.hi;
            i++;
            tilePrim = tilePrim->next;
        }
    }
}

// DRA function is func_8011EDA8
static AnimationFrame anim_80154DC8[] = {
    POSE(2, 1, 0), POSE(2, 2, 0), POSE(2, 3, 0), POSE(2, 4, 0), POSE(2, 5, 0),
    POSE(2, 4, 0), POSE(2, 3, 0), POSE(2, 4, 0), POSE(2, 3, 0), POSE(2, 4, 0),
    POSE(2, 5, 0), POSE(1, 6, 0), POSE(1, 7, 0), POSE(1, 8, 0), POSE_END};
static AnimationFrame anim_80154E04[] = {
    POSE(1, 9, 0),  POSE(2, 10, 0), POSE(2, 11, 0), POSE(2, 12, 0),
    POSE(2, 13, 0), POSE(2, 14, 0), POSE(2, 15, 0), POSE(2, 16, 0),
    POSE(2, 17, 0), POSE(2, 18, 0), POSE(3, 19, 0), POSE(4, 20, 0),
    POSE_END};
void func_80161C2C(Entity* self) {
    s16 paramsHi;
    s16 paramsLo;

    paramsLo = self->params & 0xFF;
    paramsHi = (self->params >> 8) & 0xFF;
    switch (self->step) {
    case 0:
        if (paramsHi == 1) {
            self->scaleX = 0xC0;
            self->scaleY = 0xC0;
            self->drawFlags = FLAG_DRAW_SCALEX | FLAG_DRAW_SCALEY;
            self->animSet = ANIMSET_DRA(2);
            self->anim = anim_80154E04;
        }
        if (paramsHi == 0 || paramsHi == 2) {
            if (paramsLo & 3) {
                self->anim = anim_80154DC8;
                self->scaleX = 0x120;
                self->scaleY = 0x120;
                self->drawFlags = FLAG_DRAW_SCALEX | FLAG_DRAW_SCALEY;
                self->animSet = ANIMSET_DRA(2);
            } else {
                self->animSet = ANIMSET_DRA(5);
                self->anim = anim_smoke_puff;
                self->palette = PAL_OVL(0x170);
            }
        }
        self->flags = FLAG_UNK_20000 | FLAG_UNK_100000 | FLAG_POS_CAMERA_LOCKED;
        if (rand() & 3) {
            self->zPriority = PLAYER.zPriority + 2;
        } else {
            self->zPriority = PLAYER.zPriority - 2;
        }
        if (paramsHi == 2) {
            self->posX.i.hi = PLAYER.posX.i.hi + (rand() % 44) - 22;
        } else {
            self->posX.i.hi = PLAYER.posX.i.hi + (rand() & 15) - 8;
        }
        self->posY.i.hi =
            PLAYER.posY.i.hi + PLAYER.hitboxOffY + (rand() & 31) - 16;
        self->velocityY = FIX(-0.5);
        self->velocityX = PLAYER.velocityX >> 2;
        self->step++;
        break;
    case 1:
        self->scaleX -= 4;
        self->scaleY -= 4;
        self->posY.val += self->velocityY;
        self->posX.val += self->velocityX;
        if ((self->pose == 8) && (self->anim != anim_smoke_puff)) {
            self->drawMode = DRAW_TPAGE;
            if (!(paramsLo & 1) && self->poseTimer == 1) {
                RicCreateEntFactoryFromEntity(self, FACTORY(BP_EMBERS, 4), 0);
            }
        }
        if (self->pose == 16 && self->anim == anim_smoke_puff) {
            self->drawMode = DRAW_TPAGE;
        }
        if (self->poseTimer < 0) {
            DestroyEntity(self);
        }
        break;
    }
}

static AnimationFrame anim_80154E38[] = {
    POSE(2, 1, 0), POSE(2, 2, 0), POSE(2, 3, 0), POSE(2, 4, 0), POSE(2, 5, 0),
    POSE(2, 6, 0), POSE(2, 7, 0), POSE(2, 8, 0), POSE_END};
void func_80161EF8(Entity* self) {
    switch (self->step) {
    case 0:
        self->animSet = ANIMSET_DRA(2);
        self->anim = anim_80154E38;
        self->flags = FLAG_UNK_20000 | FLAG_UNK_100000 | FLAG_UNK_10000 |
                      FLAG_POS_PLAYER_LOCKED;
        self->zPriority = PLAYER.zPriority + 4;
        self->velocityY = (rand() & 0x3FFF) - 0x10000;
        self->step++;
        break;
    case 1:
        if (self->pose == 6) {
            if (self->poseTimer == 1 && (rand() & 1)) {
                RicCreateEntFactoryFromEntity(self, BP_EMBERS, 0);
            }
        }
        self->posY.val += self->velocityY;
        if (self->poseTimer < 0) {
            DestroyEntity(self);
        }
        break;
    }
}

typedef struct {
    s16 xPos;
    s16 yPos;
    s32 velocityX;
    s32 velocityY;
    s16 timerInit;
    s16 tpage;
    u16 clut;
    u8 uBase;
    u8 vBase;
} Props_80161FF0; // size = 0x14
static Props_80161FF0 D_80154E5C[] = {
    {-0x40, 0, +FIX(2.5), FIX(0), 0x0060, 0x1B, 0x0118, 128, 0},
    {+0x40, 0, -FIX(2.5), FIX(0), 0x0048, 0x1B, 0x0119, 0, 128},
    {0, -0x40, FIX(0), +FIX(2.5), 0x0030, 0x19, 0x011A, 0, 0},
    {0, +0x40, FIX(0), -FIX(2.5), 0x0018, 0x19, 0x011B, 128, 0}};
void RicEntityApplyMariaPowerAnim(Entity* self) {
    Primitive* prim;
    s16 posX;
    s16 posY;
    s16 params;
    Props_80161FF0* props;

    posX = self->posX.i.hi;
    posY = self->posY.i.hi;
    params = self->params;
    props = &D_80154E5C[params];
    switch (self->step) {
    case 0:
        self->primIndex = g_api.AllocPrimitives(PRIM_GT4, 1);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        g_api.PlaySfx(0x881);
        self->ext.ricMariaPower.size = 0x100;
        prim = &g_PrimBuf[self->primIndex];
        prim->u0 = props->uBase;
        prim->v0 = props->vBase;
        prim->u1 = props->uBase + 0x7F;
        prim->v1 = props->vBase;
        prim->u2 = props->uBase;
        prim->v2 = props->vBase + 0x6F;
        prim->u3 = props->uBase + 0x7F;
        prim->v3 = props->vBase + 0x6F;
        prim->tpage = props->tpage;
        prim->clut = props->clut;
        prim->priority = PLAYER.zPriority + 8;
        prim->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_TRANSP;
        self->velocityX = props->velocityX;
        self->velocityY = props->velocityY;
        posX = self->posX.i.hi += props->xPos;
        posY = self->posY.i.hi += props->yPos;
        self->flags =
            FLAG_KEEP_ALIVE_OFFCAMERA | FLAG_HAS_PRIMS | FLAG_UNK_10000;
        self->step++;
        break;
    case 1:
        self->ext.ricMariaPower.size -= 8;
        self->posX.val += self->velocityX;
        self->posY.val += self->velocityY;
        if (self->ext.ricMariaPower.size < 25) {
            self->ext.ricMariaPower.timer = props->timerInit;
            self->step++;
        }
        break;
    case 2:
        if (--self->ext.ricMariaPower.timer == 0) {
            self->step++;
        }
        break;
    case 3:
        self->ext.ricMariaPower.size -= 2;
        if (self->ext.ricMariaPower.size < 0) {
            DestroyEntity(self);
            return;
        }
        break;
    }
    prim = &g_PrimBuf[self->primIndex];
    prim->x0 =
        posX + (((rcos(0x600) >> 4) * self->ext.ricMariaPower.size) >> 8);
    prim->y0 =
        posY - (((rsin(0x600) >> 4) * self->ext.ricMariaPower.size) >> 8);
    prim->x1 =
        posX + (((rcos(0x200) >> 4) * self->ext.ricMariaPower.size) >> 8);
    prim->y1 =
        posY - (((rsin(0x200) >> 4) * self->ext.ricMariaPower.size) >> 8);
    prim->x2 =
        posX + (((rcos(0xA00) >> 4) * self->ext.ricMariaPower.size) >> 8);
    prim->y2 =
        posY - (((rsin(0xA00) >> 4) * self->ext.ricMariaPower.size) >> 8);
    prim->x3 =
        posX + (((rcos(0xE00) >> 4) * self->ext.ricMariaPower.size) >> 8);
    prim->y3 =
        posY - (((rsin(0xE00) >> 4) * self->ext.ricMariaPower.size) >> 8);
}

void func_801623E0(Entity* self) {
    Primitive* prim;

    self->posX.val = PLAYER.posX.val;
    self->posY.val = PLAYER.posY.val;
    switch (self->step) {
    case 0:
        self->primIndex = g_api.AllocPrimitives(PRIM_GT4, 1);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->ext.circleExpand.width = self->ext.circleExpand.height = 32;
        prim = &g_PrimBuf[self->primIndex];
        prim->u0 = prim->u2 = 64;
        prim->v0 = prim->v1 = 192;
        prim->u1 = prim->u3 = 127;
        prim->v2 = prim->v3 = 255;
        prim->tpage = 0x1A;
        prim->clut = 0x13E;
        prim->priority = PLAYER.zPriority + 8;
        prim->drawMode = DRAW_DEFAULT;
        self->flags = FLAG_UNK_10000 | FLAG_POS_PLAYER_LOCKED |
                      FLAG_KEEP_ALIVE_OFFCAMERA | FLAG_HAS_PRIMS;
        self->step++;
        break;

    case 1:
        self->ext.circleExpand.width++;
        self->ext.circleExpand.height++;
        if (self->ext.circleExpand.width > 44) {
            DestroyEntity(self);
            return;
        }
        break;
    }

    prim = &g_PrimBuf[self->primIndex];
    prim->x0 = self->posX.i.hi - self->ext.circleExpand.width;
    prim->y0 = self->posY.i.hi - self->ext.circleExpand.height;
    prim->x1 = self->posX.i.hi + self->ext.circleExpand.width;
    prim->y1 = self->posY.i.hi - self->ext.circleExpand.height;
    prim->x2 = self->posX.i.hi - self->ext.circleExpand.width;
    prim->y2 = self->posY.i.hi + self->ext.circleExpand.height;
    prim->x3 = self->posX.i.hi + self->ext.circleExpand.width;
    prim->y3 = self->posY.i.hi + self->ext.circleExpand.height;
    prim->clut = (g_Timer & 1) + 0x13E;
}

void func_80162604(Entity* self) {
    Primitive* prim;

    self->posX.val = PLAYER.posX.val;
    self->posY.val = PLAYER.posY.val;
    switch (self->step) {
    case 0:
        self->primIndex = g_api.AllocPrimitives(PRIM_GT4, 1);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->ext.circleExpand.width = self->ext.circleExpand.height = 0;
        prim = &g_PrimBuf[self->primIndex];

        prim->u0 = prim->u2 = 0;
        prim->v0 = prim->v1 = 192;
        prim->u1 = prim->u3 = 63;
        prim->v2 = prim->v3 = 255;
        prim->tpage = 0x1A;

        prim->clut = 0x162;
        prim->priority = PLAYER.zPriority - 4;
        prim->drawMode = DRAW_DEFAULT;
        self->flags = FLAG_UNK_10000 | FLAG_POS_PLAYER_LOCKED |
                      FLAG_KEEP_ALIVE_OFFCAMERA | FLAG_HAS_PRIMS;
        self->step++;
        break;
    case 1:
        self->ext.circleExpand.width += 8;
        self->ext.circleExpand.height += 8;
        if (self->ext.circleExpand.width >= 0x20) {
            self->step++;
        }
        break;
    case 2:
        self->step++;
        break;
    case 3:
        self->ext.circleExpand.width -= 8;
        self->ext.circleExpand.height -= 8;
        if (self->ext.circleExpand.width < 5) {
            DestroyEntity(self);
            return;
        }
        break;
    }
    prim = &g_PrimBuf[self->primIndex];
    prim->x0 = self->posX.i.hi - self->ext.circleExpand.width;
    prim->y0 = self->posY.i.hi - self->ext.circleExpand.height;
    prim->x1 = self->posX.i.hi + self->ext.circleExpand.width;
    prim->y1 = self->posY.i.hi - self->ext.circleExpand.height;
    prim->x2 = self->posX.i.hi - self->ext.circleExpand.width;
    prim->y2 = self->posY.i.hi + self->ext.circleExpand.height;
    prim->x3 = self->posX.i.hi + self->ext.circleExpand.width;
    prim->y3 = self->posY.i.hi + self->ext.circleExpand.height;
}

static u16 D_80154EAC[] = {0x016E, 0x0161, 0x0160, 0x0162};
// 0xFFFF2AAB = -FIX(1. / 3)
// 0xFFFDAAAB = -FIX(5. / 3)
static s32 D_80154EB4[] = {FIX(5. / 3), -FIX(5. / 3), FIX(1. / 3), -0xD555};
static s32 D_80154EC4[] = {-FIX(2), -FIX(5. / 3), -FIX(3), -0x25555};
void RicEntityMariaPowers(Entity* self) {
    Primitive* prim;
    s16 params;

    params = self->params;
    switch (self->step) {
    case 0:
        self->primIndex = g_api.AllocPrimitives(PRIM_GT4, 1);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->unk5A = 0x66;
        self->zPriority = PLAYER.zPriority - 12;
        self->palette = params + 0x149;
        self->animSet = ANIMSET_OVL(0x13);
        self->animCurFrame = params + 0x19;
        self->velocityX = D_80154EB4[params];
        self->velocityY = D_80154EC4[params];
        self->ext.et_80162870.unk7C = self->ext.et_80162870.unk7E =
            self->ext.et_80162870.unk80 = 8;

        prim = &g_PrimBuf[self->primIndex];
        prim->u0 = prim->v0 = prim->v1 = prim->u2 = 0;
        prim->u1 = prim->v2 = prim->u3 = prim->v3 = 0x1F;
        prim->tpage = 0x1A;
        prim->clut = D_80154EAC[params];
        prim->priority = PLAYER.zPriority - 16;
        prim->drawMode = DRAW_HIDE;
        self->flags = FLAG_HAS_PRIMS | FLAG_UNK_10000;
        if (params == 3) {
            self->flags |= FLAG_KEEP_ALIVE_OFFCAMERA;
        }
        g_api.PlaySfx(0x881);
        self->ext.et_80162870.unk82 = 12;
        self->step++;
        break;
    case 1:
        self->posX.val += self->velocityX;
        self->posY.val += self->velocityY;
        if (--self->ext.et_80162870.unk82 == 0) {
            self->drawFlags = FLAG_DRAW_SCALEY | FLAG_DRAW_SCALEX;
            self->scaleX = self->scaleY = 0x100;
            self->ext.et_80162870.unk82 = 0x10;
            self->step++;
            prim = &g_PrimBuf[self->primIndex];
            prim->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_TRANSP;
        }
        break;
    case 2:
        self->scaleX = self->scaleY = self->ext.et_80162870.unk82 * 0x10;
        if (--self->ext.et_80162870.unk82 == 0) {
            self->animCurFrame = 0;
            g_api.PlaySfx(SFX_MAGIC_SWITCH);
            self->step++;
            self->velocityY = FIX(-9);
        }
        break;
    case 3:
        self->posY.val += self->velocityY;
        if (self->ext.et_80162870.unk7C > 0 && !(g_Timer & 1)) {
            self->ext.et_80162870.unk7C--;
        }
        if (!(g_Timer & 1)) {
            self->ext.et_80162870.unk7E++;
        }
        self->ext.et_80162870.unk80 += 2;
        if ((params == 3) && (self->posY.i.hi < -0x20)) {
            D_801545AC = 8;
            DestroyEntity(self);
            return;
        }
        break;
    }
    prim = &g_PrimBuf[self->primIndex];
    prim->x0 = self->posX.i.hi - self->ext.et_80162870.unk7C;
    prim->y0 = self->posY.i.hi - self->ext.et_80162870.unk7E;
    prim->x1 = self->posX.i.hi + self->ext.et_80162870.unk7C;
    prim->y1 = self->posY.i.hi - self->ext.et_80162870.unk7E;
    prim->x2 = self->posX.i.hi - self->ext.et_80162870.unk7C;
    prim->y2 = self->posY.i.hi + self->ext.et_80162870.unk80;
    prim->x3 = self->posX.i.hi + self->ext.et_80162870.unk7C;
    prim->y3 = self->posY.i.hi + self->ext.et_80162870.unk80;
}

void RicEntityNotImplemented4(Entity* self) {}

static AnimationFrame anim_maria_walk[] = {
    POSE(4, 1, 0), POSE(4, 2, 0), POSE(4, 3, 0), POSE(4, 4, 0), POSE(4, 5, 0),
    POSE(4, 6, 0), POSE(4, 7, 0), POSE(4, 8, 0), POSE_LOOP(0)};
static AnimationFrame anim_maria_offering_powers[] = {
    POSE(0x08, 0x09, 0), POSE(0x08, 0x0D, 0), POSE(0x40, 0x0A, 0),
    POSE(0x02, 0x0B, 0), POSE(0x02, 0x0C, 0), POSE(0x06, 0x0D, 0),
    POSE(0x07, 0x0E, 0), POSE(0x06, 0x0F, 0), POSE(0x05, 0x0E, 0),
    POSE(0x04, 0x0D, 0), POSE(0x03, 0x0F, 0), POSE(0x03, 0x0E, 0),
    POSE(0x03, 0x0D, 0), POSE(0x03, 0x0E, 0), POSE(0x03, 0x0F, 0),
    POSE(0x03, 0x0E, 0), POSE(0x03, 0x0D, 0), POSE(0x04, 0x0E, 0),
    POSE(0x05, 0x0F, 0), POSE(0x06, 0x0E, 0), POSE(0x07, 0x0D, 0),
    POSE(0x30, 0x0E, 0), POSE(0x0C, 0x09, 0), POSE(0x0D, 0x10, 0),
    POSE(0x08, 0x11, 0), POSE(0x0C, 0x12, 0), POSE(0xB0, 0x13, 0),
    POSE(0x0A, 0x14, 0), POSE(0x0A, 0x15, 0), POSE(0x0A, 0x16, 0),
    POSE(0x30, 0x17, 0), POSE(0xD0, 0x18, 0), POSE_END};
void RicEntityMaria(Entity* self) {
    switch (self->step) {
    case 0:
        self->flags = FLAG_UNK_100000 | FLAG_KEEP_ALIVE_OFFCAMERA |
                      FLAG_UNK_10000 | FLAG_POS_CAMERA_LOCKED;
        self->facingLeft = 1;
        self->unk5A = 0x66;
        self->zPriority = PLAYER.zPriority - 8;
        self->palette = PAL_OVL(0x149);
        self->animSet = ANIMSET_OVL(19);
        RicSetAnimation(anim_maria_walk);
        self->velocityX = FIX(-1.75);
        self->posY.i.hi = 0xBB;
        self->posX.i.hi = 0x148;
        self->ext.ricMaria.boolDidSound = 0;
        self->step++;
        break;
    case 1:
        if (self->pose == 0 && self->poseTimer == 1) {
            g_api.PlaySfx(0x882);
        }
        if (self->pose == 4 && self->poseTimer == 1) {
            g_api.PlaySfx(0x883);
        }

        self->posX.val += self->velocityX;
        if ((self->ext.ricMaria.boolDidSound == false) &&
            (self->posX.i.hi < 256)) {
            g_api.PlaySfx(0x87D);
            self->ext.ricMaria.boolDidSound++;
        }
        if (self->posX.i.hi < 0xE0) {
            RicSetAnimation(anim_maria_offering_powers);
            self->step++;
            self->velocityX = 0;
            RicCreateEntFactoryFromEntity(self, FACTORY(BP_SKID_SMOKE, 4), 0);
        }
        break;
    case 2:
        if (self->pose == 16) {
            g_api.PlaySfx(0x87E);
            self->ext.ricMaria.timer = 0x80;
            self->step++;
        }
        break;
    case 3:
        if (--self->ext.ricMaria.timer == 0) {
            RicCreateEntFactoryFromEntity(self, BP_MARIA_POWERS_INVOKED, 0);
            self->step++;
        }
        break;
    case 4:
        break;
    }
}

// same as DRA/func_8011BD48
bool func_80162E9C(Entity* entity) {
    Entity* e;
    s32 i;
    s16 objId;
    s16 params;

    objId = entity->entityId;
    params = entity->params;
    for (e = &g_Entities[E_WEAPON], i = E_WEAPON; i < STAGE_ENTITY_START; e++,
        i++) {
        if (objId == e->entityId && params == e->params && e != entity) {
            return true;
        }
    }
    return false;
}

// EntityPlayerBlinkWhite (Richter's version).
// Same general logic flow as in DRA but lots of missing cases.
#if defined(VERSION_PSP)
extern s32 D_80154F7C[];
#else
static s32 D_80154F7C[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
#endif
static s16 D_80154FBC[][10] = {
    {0, 0, 0, 0x15F, 0x0100, 0x0100, 0x0100, 0x0060, 0x31, 0x200},
    {0, 2, 6, 0x15F, 0x0100, 0x0100, 0x0100, 0x0040, 0x31, 0x200},
    {0, 0, 0, 0x15F, 0x0100, 0x7000, 0x7000, 0x0040, 0x31, 0x200},
    {0, 0, 0, 0x15F, 0x0100, 0x7000, 0x0200, 0x0010, 0x31, 0x200},
    {0, 0, 0, 0x15F, 0x0100, 0x7000, 0x7000, 0x0010, 0x31, 0x200},
    {0, 0, 0, 0x15F, 0x0100, 0x7000, 0x0200, 0x7000, 0x31, 0x200},
    {0, 0, 0, 0x15F, 0x0100, 0x7000, 0x0100, 0x7002, 0x31, 0x100},
    {0, 0, 0, 0x15F, 0x0100, 0x0100, 0x7000, 0x0070, 0x31, 0x200},
    {0, 0, 0, 0x15F, 0x0100, 0x7000, 0x0200, 0x7006, 0x31, 0x200},
    {0, 0, 0, 0x15F, 0x0200, 0x0200, 0x0400, 0x7001, 0x31, 0x200},
    {0, 0, 0, 0x166, 0x0100, 0x0100, 0x0100, 0x7005, 0x31, 0x200},
    {0, 0, 0, 0x102, 0x0100, 0x7000, 0x7000, 0x0040, 0x31, 0x200},
    {0, 0, 0, 0x15F, 0x0100, 0x7100, 0x0100, 0x7005, 0x31, 0x200},
    {0, 0, 0, 0x15F, 0x0100, 0x0100, 0x0100, 0x7005, 0x31, 0x200},
    {0, 0, 0, 0x102, 0x0100, 0x7000, 0x0200, 0x0040, 0x31, 0x200},
    {0, 0, 0, 0x102, 0x0100, 0x7000, 0x0100, 0x0040, 0x31, 0x200},
    {0, 0, 0, 0x102, 0x0100, 0x0100, 0x7000, 0x0000, 0x31, 0x200},
    {0, 0, 0, 0x102, 0x0400, 0x0100, 0x0400, 0x0000, 0x31, 0x200},
    {0, 0, 0, 0x15F, 0x0100, 0x0100, 0x7000, 0x0000, 0x31, 0x200},
    {0, 0, 0, 0x15F, 0x0200, 0x0800, 0x0800, 0x7007, 0x31, 0x200},
    {0, 0, 0, 0x102, 0x0100, 0x0100, 0x0100, 0x0000, 0x31, 0x200},
    {0, 0, 0, 0x15F, 0x00C0, 0x00C0, 0x0100, 0x0010, 0x31, 0x200},
    {8, 0, 8, 0x165, 0x0100, 0x0100, 0x0100, 0x7007, 0x51, 0x200},
    {0, 0, 0, 0x168, 0x7100, 0x7100, 0x0200, 0x7007, 0x31, 0x200}};
void RicEntityPlayerBlinkWhite(Entity* self) {
    u8 xMargin;
    u8 yMargin;
    s16 angle;
    u8 wSprite;
    u8 hSprite;
    s16 width;
    s16 height;
    s16 selfX;
    s16 selfY;
    s32 i;
    Primitive* prim;
    s16 xPivot;
    s16 yPivot;
    s16 plSpriteIndex;
    s16 upperParams;
    s16 angleRedIndex;
    s16* sp44;
    u8* plSprite;
    s16* dataPtr;
    s16 angleGreenIndex;
    s16 angleBlueIndex;
    s16 redDivide;
    s16 blueDivide;
    s16 greenDivide;
    void* dummy48;

    if (!PLAYER.animSet || !(PLAYER.animCurFrame & 0x7FFF)) {
        DestroyEntity(self);
        return;
    }
    self->posY.i.hi = PLAYER.posY.i.hi;
    self->posX.i.hi = PLAYER.posX.i.hi;
    self->facingLeft = PLAYER.facingLeft;
#if defined(VERSION_PSP)
    sp44 = D_92641C8[PLAYER.animCurFrame & 0x7FFF];
#endif
    sp44 = D_801530AC[PLAYER.animCurFrame & 0x7FFF];
    plSpriteIndex = *sp44++;
    plSpriteIndex &= 0x7FFF;
    selfX = self->posX.i.hi;
    selfY = self->posY.i.hi;
    plSprite = ((u8**)SPRITESHEET_PTR)[plSpriteIndex];
    xMargin = 4;
    yMargin = 1;
    wSprite = xMargin + plSprite[0];
    hSprite = yMargin + plSprite[1];
    width = wSprite - xMargin;
    height = hSprite - yMargin;
    xPivot = sp44[0] + plSprite[2];
    yPivot = sp44[1] + plSprite[3];

    self->rotate = PLAYER.rotate;
    self->drawFlags = PLAYER.drawFlags;
    self->scaleX = PLAYER.scaleX;
    self->scaleY = PLAYER.scaleY;
    self->rotPivotY = PLAYER.rotPivotY;
    self->rotPivotX = PLAYER.rotPivotX;
    upperParams = (self->params & 0x7F00) >> 8;
    dataPtr = D_80154FBC[upperParams & 0x3F];
    switch (self->step) {
    case 0:
        if (func_80162E9C(self) != 0) {
            DestroyEntity(self);
            return;
        }
        self->primIndex = g_api.AllocPrimitives(PRIM_GT4, 8);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags = FLAG_KEEP_ALIVE_OFFCAMERA | FLAG_HAS_PRIMS |
                      FLAG_POS_PLAYER_LOCKED | FLAG_UNK_20000 | FLAG_UNK_10000;
        prim = &g_PrimBuf[self->primIndex];
        for (i = 0; i < 8; i++) {
            D_80154F7C[i] = i << 9;
            prim->tpage = 0x18;
            prim->clut = dataPtr[3];
            prim->r0 = prim->b0 = prim->g0 = prim->r1 = prim->b1 = prim->g1 =
                prim->r2 = prim->b2 = prim->g2 = prim->r3 = prim->b3 =
                    prim->g3 = 0x80;
            prim->priority = PLAYER.zPriority + 2;
            prim->drawMode =
                dataPtr[8] + DRAW_UNK_200 + DRAW_UNK_100 + DRAW_COLORS;
            prim = prim->next;
        }
        self->ext.playerBlink.unk8A = dataPtr[9];
        self->ext.playerBlink.colorIntensity = 0;
        self->step += 1;
        break;
    case 1:
        self->ext.playerBlink.colorIntensity += 0xA;
        if (self->ext.playerBlink.colorIntensity > 0x100) {
            self->ext.playerBlink.colorIntensity = 0x100;
            self->ext.playerBlink.unk80 = dataPtr[7];
            self->step += 1;
        }
        break;
    case 2:
        if (dataPtr[7] >= 0x7000) {
            switch ((u32)dataPtr[7]) {
            case 0x7000:
                if (g_Player.timers[PL_T_POISON] == 0) {
                    self->step++;
                }
                break;
            case 0x7001:
                if (g_Player.timers[PL_T_INVINCIBLE_SCENE] == 0) {
                    self->step++;
                }
                break;
            case 0x7007:
            case 0x7002:
                if (PLAYER.step != PL_S_HIT) {
                    self->step++;
                }
                break;
            case 0x7005:
            case 0x7006:
                if (PLAYER.step_s == 3) {
                    self->step++;
                }
                break;
            case 0x7003:
            case 0x7004:

                break;
            }
            self->ext.playerBlink.unk80 = 8;
        }
        if (--self->ext.playerBlink.unk80 == 0) {
            self->step++;
        }
        break;
    case 3:
        self->ext.playerBlink.colorIntensity -= 10;
        if (self->ext.playerBlink.colorIntensity < 0) {
            DestroyEntity(self);
            return;
        }
        break;
    }
    self->ext.playerBlink.unk82 += self->ext.playerBlink.unk8A;
    if (self->facingLeft) {
        selfX = selfX - xPivot;
    } else {
        selfX = selfX + xPivot;
    }
    selfY = selfY + yPivot;
    prim = &g_PrimBuf[self->primIndex];
    for (i = 0; i < 8; i++) {
        if (upperParams & 0x40) {
            switch (i) {
            case 0:
                if (self->facingLeft) {
                    prim->x0 = selfX;
                    prim->x1 = selfX - width / 2;
                    prim->u0 = xMargin;
                    prim->u1 = xMargin + width / 2;
                } else {
                    prim->x0 = selfX;
                    prim->x1 = selfX + width / 2;
                    prim->u0 = xMargin;
                    prim->u1 = xMargin + width / 2;
                }
                prim->y0 = prim->y1 = selfY;
                prim->v0 = prim->v1 = yMargin;
                break;
            case 1:
                if (self->facingLeft) {
                    prim->x0 = selfX - width / 2;
                    prim->x1 = selfX - width;
                    prim->u0 = xMargin + width / 2;
                    prim->u1 = xMargin + width;
                } else {
                    prim->x0 = selfX + width / 2;
                    prim->x1 = selfX + width;
                    prim->u0 = xMargin + width / 2;
                    prim->u1 = xMargin + width;
                }
                prim->y0 = prim->y1 = selfY;
                prim->v0 = prim->v1 = yMargin;
                break;
            case 2:
                if (self->facingLeft) {
                    prim->x0 = prim->x1 = selfX - width;
                    prim->u0 = prim->u1 = xMargin + width;
                } else {
                    prim->x0 = prim->x1 = selfX + width;
                    prim->u0 = prim->u1 = xMargin + width;
                }
                prim->y0 = selfY;
                prim->y1 = selfY + height / 2;
                prim->v0 = yMargin;
                prim->v1 = yMargin + height / 2;
                break;
            case 3:
                if (self->facingLeft) {
                    prim->x0 = prim->x1 = selfX - width;
                    prim->u0 = prim->u1 = xMargin + width;
                } else {
                    prim->x0 = prim->x1 = selfX + width;
                    prim->u0 = prim->u1 = xMargin + width;
                }

                prim->y0 = selfY + height / 2;
                prim->y1 = selfY + height;
                prim->v0 = yMargin + height / 2;
                prim->v1 = yMargin + height;
                break;
            case 4:
                if (self->facingLeft) {
                    prim->x0 = selfX - width;
                    prim->x1 = selfX - width / 2;
                    prim->u0 = xMargin + width;
                    prim->u1 = xMargin + width / 2;
                } else {
                    prim->x0 = selfX + width;
                    prim->x1 = selfX + width / 2;
                    prim->u0 = xMargin + width;
                    prim->u1 = xMargin + width / 2;
                }
                prim->y0 = prim->y1 = selfY + height;
                prim->v0 = prim->v1 = yMargin + height;
                break;
            case 5:
                if (self->facingLeft) {
                    prim->x0 = selfX - width / 2;
                    prim->x1 = selfX;
                    prim->u0 = xMargin + width / 2;
                    prim->u1 = xMargin;
                } else {
                    prim->x0 = selfX + width / 2;
                    prim->x1 = selfX;
                    prim->u0 = xMargin + width / 2;
                    prim->u1 = xMargin;
                }
                prim->y0 = prim->y1 = selfY + height;
                prim->v0 = prim->v1 = yMargin + height;
                break;
            case 6:
                if (self->facingLeft) {
                    prim->x0 = prim->x1 = selfX;
                    prim->u0 = prim->u1 = xMargin;
                } else {
                    prim->x0 = prim->x1 = selfX;
                    prim->u0 = prim->u1 = xMargin;
                }
                prim->y0 = selfY + height;
                prim->y1 = selfY + height / 2;
                prim->v0 = yMargin + height;
                prim->v1 = yMargin + height / 2;
                break;
            case 7:
                if (self->facingLeft) {
                    prim->x0 = prim->x1 = selfX;
                    prim->u0 = prim->u1 = xMargin;
                } else {
                    prim->x0 = prim->x1 = selfX;
                    prim->u0 = prim->u1 = xMargin;
                }
                prim->y0 = selfY + height / 2;
                prim->y1 = selfY;
                prim->v0 = yMargin + height / 2;
                prim->v1 = yMargin;
                break;
            }
            if (self->facingLeft) {
                prim->x2 = prim->x3 =
                    selfX - width / 2 +
                    (((rcos(self->ext.playerBlink.unk82) >> 4) * 3) >> 0xC);
            } else {
                prim->x2 = prim->x3 =
                    selfX + width / 2 +
                    (((rcos(self->ext.playerBlink.unk82) >> 4) * 3) >> 0xC);
            }
            prim->y2 = prim->y3 =
                (selfY + height / 2) -
                ((rsin(self->ext.playerBlink.unk82) >> 4) * 3 << 1 >> 8);
            prim->u2 = prim->u3 = xMargin + width / 2;
            prim->v2 = prim->v3 = yMargin + height / 2;
        } else {
            if (self->facingLeft) {
                prim->x0 = prim->x2 = (selfX - width) + 1;
                prim->x1 = prim->x3 = selfX + 1;
            } else {
                prim->x0 = prim->x2 = selfX;
                prim->x1 = prim->x3 = selfX + width;
            }
            prim->y0 = prim->y1 = selfY + height * i / 8;
            prim->y2 = prim->y3 = selfY + height * (i + 1) / 8;
            if (self->facingLeft) {
                prim->u0 = prim->u2 = wSprite - 1;
                prim->u1 = prim->u3 = xMargin - 1;
            } else {
                prim->u0 = prim->u2 = xMargin;
                prim->u1 = prim->u3 = wSprite;
            }
            prim->v0 = prim->v1 = yMargin + height * i / 8;
            prim->v2 = prim->v3 = yMargin + height * (i + 1) / 8;
        }
        angleRedIndex = dataPtr[0];
        angleGreenIndex = dataPtr[2];
        angleBlueIndex = dataPtr[1];
        redDivide = dataPtr[4];
        greenDivide = dataPtr[6];
        blueDivide = dataPtr[5];
        if (upperParams & 0x40) {
            angle = D_80154F7C[(i + angleRedIndex) % 8];
            prim->r0 = ((rsin(angle) + 0x1000) >> 6) *
                       self->ext.playerBlink.colorIntensity / redDivide;
            angle = D_80154F7C[(i + angleGreenIndex) % 8];
            prim->g0 = ((rsin(angle) + 0x1000) >> 6) *
                       self->ext.playerBlink.colorIntensity / greenDivide;
            angle = D_80154F7C[(i + angleBlueIndex) % 8];
            prim->b0 = ((rsin(angle) + 0x1000) >> 6) *
                       self->ext.playerBlink.colorIntensity / blueDivide;
            angle = D_80154F7C[(i + angleRedIndex + 1) % 8];
            prim->r1 = ((rsin(angle) + 0x1000) >> 6) *
                       self->ext.playerBlink.colorIntensity / redDivide;
            angle = D_80154F7C[(i + angleGreenIndex + 1) % 8];
            prim->g1 = ((rsin(angle) + 0x1000) >> 6) *
                       self->ext.playerBlink.colorIntensity / greenDivide;
            angle = D_80154F7C[(i + angleBlueIndex + 1) % 8];
            prim->b1 = ((rsin(angle) + 0x1000) >> 6) *
                       self->ext.playerBlink.colorIntensity / blueDivide;
            prim->r2 = prim->g2 = prim->b2 = prim->r3 = prim->g3 = prim->b3 = 0;
            D_80154F7C[i] += self->ext.playerBlink.unk8A;
        } else {
            angle = D_80154F7C[(i + angleRedIndex) % 8];
            prim->r0 = prim->r1 =
                (((rsin(angle) + 0x1000) >> 6) *
                 self->ext.playerBlink.colorIntensity / redDivide);
            angle = D_80154F7C[(i + angleGreenIndex) % 8];
            prim->g0 = prim->g1 =
                (((rsin(angle) + 0x1000) >> 6) *
                 self->ext.playerBlink.colorIntensity / greenDivide);
            angle = D_80154F7C[(i + angleBlueIndex) % 8];
            prim->b0 = prim->b1 =
                (((rsin(angle) + 0x1000) >> 6) *
                 self->ext.playerBlink.colorIntensity / blueDivide);
            angle = D_80154F7C[(i + angleRedIndex + 1) % 8];
            prim->r2 = prim->r3 =
                (((rsin(angle) + 0x1000) >> 6) *
                 self->ext.playerBlink.colorIntensity / redDivide);
            angle = D_80154F7C[(i + angleGreenIndex + 1) % 8];
            prim->g2 = prim->g3 =
                (((rsin(angle) + 0x1000) >> 6) *
                 self->ext.playerBlink.colorIntensity / greenDivide);
            angle = D_80154F7C[(i + angleBlueIndex + 1) % 8];
            prim->b2 = prim->b3 =
                (((rsin(angle) + 0x1000) >> 6) *
                 self->ext.playerBlink.colorIntensity / blueDivide);
            D_80154F7C[i] += self->ext.playerBlink.unk8A;
        }
        prim->priority = PLAYER.zPriority + 2;
        prim = prim->next;
    }
    if ((upperParams & 0x3F) == 0 || (upperParams & 0x3F) == 7) {
        RicSetInvincibilityFrames(1, 10);
    }
}

void func_801641A0(Entity* self) {
    Primitive* prim;
    s16 primIndex;

    self->posX.i.hi = PLAYER.posX.i.hi - 0;
    self->posY.i.hi = PLAYER.posY.i.hi - 8;
    switch (self->step) {
    case 0:
        self->primIndex = g_api.AllocPrimitives(PRIM_GT4, 1);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->ext.circleExpand.width = 16;
        self->ext.circleExpand.height = 12;
        prim = &g_PrimBuf[self->primIndex];
        prim->u0 = prim->u2 = 64;
        prim->v0 = prim->v1 = 192;
        prim->u1 = prim->u3 = 127;
        prim->v2 = prim->v3 = 255;
        PGREY(prim, 0) = PGREY(prim, 1) = PGREY(prim, 2) = PGREY(prim, 3) = 128;
        prim->tpage = 0x1A;
        prim->clut = 0x160;
        prim->priority = PLAYER.zPriority + 8;
        prim->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS | DRAW_TRANSP;
        self->flags =
            FLAG_POS_PLAYER_LOCKED | FLAG_KEEP_ALIVE_OFFCAMERA | FLAG_HAS_PRIMS;
        self->step++;
        break;

    case 1:
        self->ext.circleExpand.width += 2;
        self->ext.circleExpand.height += 2;
        if (self->ext.circleExpand.width > 56) {
            DestroyEntity(self);
            return;
        }
        break;
    }

    prim = &g_PrimBuf[self->primIndex];
    prim->x0 = self->posX.i.hi - self->ext.circleExpand.width;
    prim->y0 = self->posY.i.hi - self->ext.circleExpand.height;
    prim->x1 = self->posX.i.hi + self->ext.circleExpand.width;
    prim->y1 = self->posY.i.hi - self->ext.circleExpand.height;
    prim->x2 = self->posX.i.hi - self->ext.circleExpand.width;
    prim->y2 = self->posY.i.hi + self->ext.circleExpand.height;
    prim->x3 = self->posX.i.hi + self->ext.circleExpand.width;
    prim->y3 = self->posY.i.hi + self->ext.circleExpand.height;
    if (prim->b3 >= 12) {
        prim->b3 -= 12;
    }
    // remember last element of PGREY(prim,3) is prim->b3
    PGREY(prim, 0) = PGREY(prim, 1) = PGREY(prim, 2) = PGREY(prim, 3);
}

// Entity ID # 34. Created by blueprints 36, 37, 38, 39.
// Only difference in those blueprints is the "unk5" member of the blueprint.
// When the factory is made, unk5 loads into ext.factory.unk9A. This appears
// to create a delay before the factory actually creates the child.
// So 36, 37, 38, 39 create this entity with delay of 0, 4, 8, or 12 frames.
// All 4 are used in RicStepDeadPrologue. 36 alone (for instant child) is used
// when Richter does an item crash without a subweapon, in RicDoCrash.
// Creates a large semi-transparent circle around Richter which shrinks inward.
static s16 D_8015519C[][6] = {
    {0x0000, 0x0000, 0x0100, 0x0100, 0x0100, 0x0100},
    {0x0500, 0x0A00, 0x0100, 0x0100, 0x0100, 0x0000},
    {0x0000, 0x0000, 0x0100, 0x7000, 0x7000, 0x0200},
    {0x0000, 0x0000, 0x7100, 0x7100, 0x0100, 0x1000},
    {0x0000, 0x0000, 0x7100, 0x0100, 0x7000, 0x0800},
    {0x0000, 0x0000, 0x0100, 0x7100, 0x0100, 0x0400},
    {0x0500, 0x0A00, 0x0100, 0x0100, 0x0100, 0x0100},
    {0x0500, 0x0A00, 0x0100, 0x0200, 0x7100, 0x0100}};
void RicEntityShrinkingPowerUpRing(Entity* self) {
    s16 variant;
    s16 rMod;
    s16* loadedParams;
    s16 x;
    s16 gMod;
    s16 bMod;
    s16 gOffset;
    s16 bOffset;
    s16 angleStart;
    s16 y;
    s16 baseAngle;
    s32 i;
    s16 angle;
    Primitive* prim1;
    Primitive* prim2;

    variant = (self->params & 0x7F00) >> 8;
    loadedParams = D_8015519C[variant];
    rMod = loadedParams[2];
    gMod = loadedParams[3];
    bMod = loadedParams[4];
    gOffset = loadedParams[0];
    bOffset = loadedParams[1];
    self->posX.i.hi = PLAYER.posX.i.hi;
    self->posY.i.hi = PLAYER.posY.i.hi;
    switch (self->step) {
    case 0:
        self->primIndex = g_api.AllocPrimitives(PRIM_GT4, 32);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags = FLAG_KEEP_ALIVE_OFFCAMERA | FLAG_HAS_PRIMS |
                      FLAG_POS_PLAYER_LOCKED | FLAG_UNK_10000;
        x = self->posX.i.hi;
        y = self->posY.i.hi;
        prim2 = prim1 = &g_PrimBuf[self->primIndex];
        for (i = 0; i < 16; i++) {
            prim1 = prim1->next;
        }
        for (i = 0; i < 16; i++) {
            angle = i << 8;
            prim2->u0 = (rcos(angle) >> 4 << 5 >> 8) + 0x20;
            prim2->v0 = -(rsin(angle) >> 4 << 5 >> 8) + 0xDF;
            angle = (i + 1) << 8;
            prim2->u1 = (rcos(angle) >> 4 << 5 >> 8) + 0x20;
            prim2->v1 = -(rsin(angle) >> 4 << 5 >> 8) + 0xDF;
            prim1->u2 = prim1->u3 = 0x20;
            prim1->v2 = prim1->v3 = 0xDF;
            prim2->u2 = prim1->u0 = (prim2->u0 + prim1->u2) / 2;
            prim2->v2 = prim1->v0 = (prim2->v0 + prim1->v2) / 2;
            prim2->u3 = prim1->u1 = (prim2->u1 + prim1->u3) / 2;
            prim2->v3 = prim1->v1 = (prim2->v1 + prim1->v3) / 2;
            prim1->tpage = prim2->tpage = 0x1A;
            prim1->clut = prim2->clut = 0x15F;
            prim1->priority = prim2->priority = PLAYER.zPriority + 2;
            prim1->drawMode = prim2->drawMode =
                DRAW_UNK_200 | DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS |
                DRAW_TRANSP;
            prim2 = prim2->next;
            prim1 = prim1->next;
        }
        self->ext.ricPowerRing.unk80 = self->ext.ricPowerRing.unk82 = 0x280;
        self->ext.ricPowerRing.unk84 = self->ext.ricPowerRing.unk86 = 0x240;
        self->ext.ricPowerRing.unk8A = loadedParams[5];
        self->ext.ricPowerRing.unk88 = 0xC0;
        self->step++;
        break;
    case 1:
        self->ext.ricPowerRing.unk7E += 0x40;
        self->ext.ricPowerRing.unk86 -= 10;
        if (self->ext.ricPowerRing.unk86 < 0) {
            self->ext.ricPowerRing.unk86 = 0;
            self->ext.ricPowerRing.unk7C = 0x20;
            self->step++;
        }
        self->ext.ricPowerRing.unk84 = self->ext.ricPowerRing.unk86;
        self->ext.ricPowerRing.unk82 -= 5;
        self->ext.ricPowerRing.unk80 -= 5;
        break;
    case 2:
        self->ext.ricPowerRing.unk7E += 0x40;
        self->ext.ricPowerRing.unk82 -= 3;
        self->ext.ricPowerRing.unk80 -= 6;
        if (--self->ext.ricPowerRing.unk7C == 0) {
            self->step++;
        }
        break;
    case 3:
        self->ext.ricPowerRing.unk7E += 0x40;
        self->ext.ricPowerRing.unk82 -= 3;
        self->ext.ricPowerRing.unk80 -= 6;
        self->ext.ricPowerRing.unk88 -= 12;
        if (self->ext.ricPowerRing.unk88 < 0) {
            DestroyEntity(self);
            return;
        }
        break;
    }
    angleStart = self->ext.ricPowerRing.unk8A;
    x = self->posX.i.hi;
    y = self->posY.i.hi;
    prim1 = prim2 = &g_PrimBuf[self->primIndex];
    for (i = 0; i < 16; i++) {
        prim1 = prim1->next;
    }
    for (i = 0; i < 16; i++) {
        prim2->x0 =
            x + (prim2->u0 - 0x20) * self->ext.ricPowerRing.unk80 / 0x100;
        prim2->y0 =
            y + (prim2->v0 - 0xE0) * self->ext.ricPowerRing.unk82 / 0x100;
        prim2->x1 =
            x + (prim2->u1 - 0x20) * self->ext.ricPowerRing.unk80 / 0x100;
        prim2->y1 =
            y + (prim2->v1 - 0xE0) * self->ext.ricPowerRing.unk82 / 0x100;
        prim1->x2 = x + (rcos((i + 1) << 8) >> 4 << 5 >> 8) *
                            self->ext.ricPowerRing.unk84 / 0x100;
        prim1->y2 = y - (rsin((i + 1) << 8) >> 4 << 5 >> 8) *
                            self->ext.ricPowerRing.unk86 / 0x100;
        prim1->x3 = x + (rcos((i + 2) << 8) >> 4 << 5 >> 8) *
                            self->ext.ricPowerRing.unk84 / 0x100;
        prim1->y3 = y - (rsin((i + 2) << 8) >> 4 << 5 >> 8) *
                            self->ext.ricPowerRing.unk86 / 0x100;
        prim2->x2 = prim1->x0 = (prim2->x0 + prim1->x2) / 2;
        prim2->y2 = prim1->y0 = (prim2->y0 + prim1->y2) / 2;
        prim2->x3 = prim1->x1 = (prim2->x1 + prim1->x3) / 2;
        prim2->y3 = prim1->y1 = (prim2->y1 + prim1->y3) / 2;
        baseAngle = i * angleStart;
        angle = self->ext.ricPowerRing.unk7E + baseAngle;
        prim1->r0 = prim2->r2 =
            ((rsin(angle) + 0x1000) >> 7) * self->ext.ricPowerRing.unk88 / rMod;
        angle = self->ext.ricPowerRing.unk7E + gOffset + baseAngle;
        prim1->g0 = prim2->g2 =
            ((rsin(angle) + 0x1000) >> 7) * self->ext.ricPowerRing.unk88 / gMod;
        angle = self->ext.ricPowerRing.unk7E + bOffset + baseAngle;
        prim1->b0 = prim2->b2 =
            ((rsin(angle) + 0x1000) >> 7) * self->ext.ricPowerRing.unk88 / bMod;
        angle = self->ext.ricPowerRing.unk7E + angleStart + baseAngle;
        prim1->r1 = prim2->r3 =
            ((rsin(angle) + 0x1000) >> 7) * self->ext.ricPowerRing.unk88 / rMod;
        angle = self->ext.ricPowerRing.unk7E + gOffset + angleStart + baseAngle;
        prim1->g1 = prim2->g3 =
            ((rsin(angle) + 0x1000) >> 7) * self->ext.ricPowerRing.unk88 / gMod;
        angle = self->ext.ricPowerRing.unk7E + bOffset + angleStart + baseAngle;
        prim1->b1 = prim2->b3 =
            ((rsin(angle) + 0x1000) >> 7) * self->ext.ricPowerRing.unk88 / bMod;
        prim2->r0 = prim2->g0 = prim2->b0 = prim2->r1 = prim2->g1 = prim2->b1 =
            0;
        prim1->r2 = prim1->g2 = prim1->b2 = prim1->r3 = prim1->g3 = prim1->b3 =
            0;
        prim2 = prim2->next;
        prim1 = prim1->next;
    }
}

// Entity ID #40. Created by blueprint 47. That factory comes from
// RicStepHit.
static Point16 D_801551FC = {-2, -24};
static Point16 D_80155200 = {0, -8};
static Point16 D_80155204 = {2, 8};
static Point16 D_80155208 = {0, 24};
static Point16 D_8015520C = {6, -12};
static Point16 D_80155210 = {8, 0};
static Point16 D_80155214 = {7, 12};
static Point16 D_80155218 = {-8, -12};
static Point16 D_8015521C = {-9, 0};
static Point16 D_80155220 = {-7, 12};
static Point16 D_80155224 = {-14, -6};
static Point16 D_80155228 = {-15, 7};
static Point16 D_8015522C = {13, -7};
static Point16 D_80155230 = {16, 8};
static Point16 D_80155234 = {-7, -22};
static Point16 D_80155238 = {6, -21};
static Point16 D_8015523C = {-8, 21};
static Point16 D_80155240 = {7, 22};
static Point16* D_80155244[] = {
    &D_801551FC, &D_8015520C, &D_80155200, &D_8015520C, &D_80155210,
    &D_80155200, &D_80155210, &D_80155204, &D_80155200, &D_80155210,
    &D_80155214, &D_80155204, &D_80155214, &D_80155208, &D_80155204,
    &D_80155204, &D_80155208, &D_80155220, &D_80155204, &D_80155220,
    &D_8015521C, &D_80155200, &D_80155204, &D_8015521C, &D_80155200,
    &D_8015521C, &D_80155218, &D_80155200, &D_80155218, &D_801551FC,
    &D_8015520C, &D_8015522C, &D_80155210, &D_8015522C, &D_80155230,
    &D_80155210, &D_80155230, &D_80155214, &D_80155210, &D_80155218,
    &D_8015521C, &D_80155224, &D_8015521C, &D_80155228, &D_80155224,
    &D_8015521C, &D_80155220, &D_80155228, &D_801551FC, &D_80155218,
    &D_80155234, &D_801551FC, &D_80155238, &D_8015520C, &D_80155208,
    &D_8015523C, &D_80155220, &D_80155214, &D_80155240, &D_80155208,
    &D_80155234, &D_80155218, &D_80155224, &D_80155238, &D_8015522C,
    &D_8015520C, &D_80155228, &D_80155220, &D_8015523C, &D_80155230,
    &D_80155240, &D_80155214};
void RicEntityHitByIce(Entity* self) {
    const int PrimCount = LEN(D_80155244) / 3;
    s16 x;
    s16 y;
    s32 i;
    bool terminateFlag;
    s16 deltaX;
    s16 deltaY;
    s16 yMod;
    s32 distance;
    s16 angle;
    Point16* pos;
    Primitive* prim;

    self->posX.i.hi = PLAYER.posX.i.hi;
    self->posY.i.hi = PLAYER.posY.i.hi;
    terminateFlag = 0;
    if (!(g_Player.status & PLAYER_STATUS_UNK10000)) {
        terminateFlag = 1;
    }
    switch (self->step) {
    case 0:
        self->primIndex = g_api.AllocPrimitives(PRIM_GT3, PrimCount);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags = FLAG_HAS_PRIMS | FLAG_POS_PLAYER_LOCKED | FLAG_UNK_20000;
        prim = &g_PrimBuf[self->primIndex];
        while (prim != NULL) {
            prim->r0 = prim->r1 = prim->r2 = prim->r3 = (rand() & 0x0F) + 0x30;
            prim->b0 = prim->b1 = prim->b2 = prim->b3 = (rand() & 0x7F) + 0x80;
            prim->g0 = prim->g1 = prim->g2 = prim->g3 = (rand() & 0x1F) + 0x30;
            if (rand() & 1) {
                prim->drawMode = DRAW_UNK_200 | DRAW_UNK_100 | DRAW_TPAGE2 |
                                 DRAW_TPAGE | DRAW_COLORS | DRAW_TRANSP;
            } else {
                prim->drawMode = DRAW_UNK_200 | DRAW_UNK_100 | DRAW_TPAGE |
                                 DRAW_COLORS | DRAW_TRANSP;
            }
            prim->type = PRIM_G4;
            prim->priority = PLAYER.zPriority + 2;
            prim = prim->next;
        }
        // Weird repeated conditional
        if (PLAYER.velocityY != 0) {
            self->ext.hitbyice.unk7E = 1;
        }
        if (PLAYER.velocityY != 0) {
            if (PLAYER.facingLeft) {
                self->rotate = 0x100;
            } else {
                self->rotate = -0x100;
            }
        } else {
            if (PLAYER.velocityX > 0) {
                self->rotate = 0x80;
            } else {
                self->rotate = 0xF80;
            }
        }
        if (PLAYER.step == PL_S_DEAD) {
            if (PLAYER.facingLeft) {
                self->rotate = 0x180;
            } else {
                self->rotate = -0x180;
            }
            self->ext.hitbyice.unk80 = 1;
            self->ext.hitbyice.unk82 = 0x3C;
            if (self->params & 0x7F00) {
                self->ext.hitbyice.unk82 = 0x14;
            }
            self->ext.hitbyice.unk7E = 0;
        }
        self->step++;
        break;
    case 1:
        if (PLAYER.step == PL_S_DEAD) {
            if ((PLAYER.animCurFrame & 0x7FFF) == 0x21) {
                if (PLAYER.facingLeft) {
                    self->rotate = 0x280;
                } else {
                    self->rotate = -0x280;
                }
            }
            if ((PLAYER.animCurFrame & 0x7FFF) == 0x22) {
                if (PLAYER.facingLeft) {
                    self->rotate = 0x380;
                } else {
                    self->rotate = -0x380;
                }
            }
            if ((PLAYER.animCurFrame & 0x7FFF) == 0x20) {
                if (PLAYER.facingLeft) {
                    self->rotate = 0x180;
                } else {
                    self->rotate = -0x180;
                }
            }
        }
        if (self->ext.hitbyice.unk80 && --self->ext.hitbyice.unk82 == 0) {
            terminateFlag = true;
        }
        if (self->ext.hitbyice.unk7E &&
            g_Player.vram_flag & (TOUCHING_L_WALL | TOUCHING_R_WALL)) {
            terminateFlag = true;
        }
        if (terminateFlag) {
            self->ext.hitbyice.unk7C = 0x40;
            if (self->ext.hitbyice.unk80) {
                self->ext.hitbyice.unk7C = 0x80;
            }
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

    x = self->posX.i.hi;
    y = self->posY.i.hi;
    prim = &g_PrimBuf[self->primIndex];
    for (i = 0; i < PrimCount; i++) {
        pos = D_80155244[i * 3];
        if (prim->u0 < 2) {
            distance = SquareRoot12((pos->x * pos->x + pos->y * pos->y) << 0xC);
            angle = self->rotate + ratan2(pos->y, pos->x);
            deltaX = (((rcos(angle) >> 4) * distance) + 0x80000) >> 0x14;
            deltaY = (((rsin(angle) >> 4) * distance) + 0x80000) >> 0x14;
            prim->x0 = x + deltaX;
            prim->y0 = y + deltaY;

            pos = D_80155244[i * 3 + 1];
            distance = SquareRoot12((pos->x * pos->x + pos->y * pos->y) << 0xC);
            angle = self->rotate + ratan2(pos->y, pos->x);
            deltaX = (((rcos(angle) >> 4) * distance) + 0x80000) >> 0x14;
            deltaY = (((rsin(angle) >> 4) * distance) + 0x80000) >> 0x14;
            prim->x1 = x + deltaX;
            prim->y1 = y + deltaY;

            pos = D_80155244[i * 3 + 2];
            distance = SquareRoot12((pos->x * pos->x + pos->y * pos->y) << 0xC);
            angle = self->rotate + ratan2(pos->y, pos->x);
            deltaX = (((rcos(angle) >> 4) * distance) + 0x80000) >> 0x14;
            deltaY = (((rsin(angle) >> 4) * distance) + 0x80000) >> 0x14;
            prim->x2 = prim->x3 = x + deltaX;
            prim->y2 = prim->y3 = y + deltaY;
        }
        if (prim->u0 == 0 && terminateFlag) {
            prim->u0++;
            prim->v0 = (rand() & 15) + 1;
            if (self->ext.hitbyice.unk80) {
                prim->v0 = (rand() % 60) + 1;
            }
        }
        if (prim->u0 == 1) {
            if (--prim->v0 == 0) {
                prim->u0++;
                prim->v0 = 0x20;
                prim->u2 = 0xF0;
                if (self->ext.hitbyice.unk80) {
                    prim->v0 = (rand() & 31) + 0x28;
                }
            }
        }
        if (prim->u0 == 2) {
            if (prim->u2 < 0x70 || prim->u2 > 0xD0) {
                prim->u2 += 4;
            }
            yMod = (s8)prim->u2 >> 4;
            if (self->ext.hitbyice.unk80) {
                yMod = yMod >> 1;
            }
            prim->y0 += yMod;
            prim->y1 += yMod;
            prim->y2 += yMod;
            prim->y3 += yMod;
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
            prim->drawMode |= DRAW_UNK02;
            prim->drawMode &= ~(DRAW_UNK_200 | DRAW_UNK_100);
            if (--prim->v0 == 0) {
                prim->drawMode |= DRAW_HIDE;
            }
        }
        prim = prim->next;
    }
}

static u16 lightning_clut[] = {0x194, 0x199};
void RicEntityHitByLightning(Entity* self) {
    s16 x;
    s16 y;
    s16 mul2;
    s32 i;
    s32 xMod;
    s32 yMod;
    bool terminate;
    s32 mul;
    s16 angle;
    Primitive* primPrev;
    Primitive* prim;

    terminate = false;
    if ((self->params & 0xFF00) == 0x100) {
        if ((++self->ext.hitbylightning.unk9C) > 0xA8) {
            terminate = true;
        }
    } else if ((self->params & 0xFF00) == 0x200) {
        if (++self->ext.hitbylightning.unk9C > 0x90) {
            terminate = true;
        }
    } else if (PLAYER.step != PL_S_HIT) {
        terminate = true;
    }
    switch (self->step) {
    case 0:
        self->primIndex = g_api.AllocPrimitives(PRIM_GT4, 6);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }

        self->flags = FLAG_POS_CAMERA_LOCKED | FLAG_HAS_PRIMS | FLAG_UNK_20000;
        self->ext.hitbylightning.unk7C =
            ((self->params & 0xF) << 9) + (rand() & 0x3F);
        self->ext.hitbylightning.unk80 = (rand() & PSP_RANDMASK);
        self->ext.hitbylightning.unk82 = (rand() & 0x1FF) + 0x100;
        prim = &g_PrimBuf[self->primIndex];
        while (prim != NULL) {
            prim->x0 = prim->x1 = prim->x2 = prim->x3 = self->posX.i.hi;
            prim->y0 = prim->y1 = prim->y2 = prim->y3 = self->posY.i.hi;
            prim->tpage = 0x1A;
            prim->clut = lightning_clut[rand() & 1];
            prim->priority = PLAYER.zPriority - 2;
            prim->r0 = prim->g0 = prim->b0 = prim->r1 = prim->g1 = prim->b1 =
                prim->r2 = prim->g2 = prim->b2 = prim->r3 = prim->g3 =
                    prim->b3 = 0x80;
            prim->drawMode = DRAW_UNK_100 | DRAW_TPAGE2 | DRAW_TPAGE |
                             DRAW_UNK02 | DRAW_TRANSP;
            prim = prim->next;
        }
        if ((PLAYER.velocityY != 0) && (PLAYER.step != PL_S_DEAD)) {
            self->ext.hitbylightning.unk92 = 1;
        }
        self->ext.hitbylightning.unk94 = 0x10;
        self->step++;
        break;
    case 1:
        self->ext.hitbylightning.unk7C =
            ((self->params & 0xF) << 9) + (rand() & 0x1FF);
        mul = rsin(self->ext.hitbylightning.unk80);
        self->ext.hitbylightning.unk80 += self->ext.hitbylightning.unk82;
        xMod = ((rcos(self->ext.hitbylightning.unk7C) * mul) >> 7) * 12;
        yMod = (-((rsin(self->ext.hitbylightning.unk7C) * mul) >> 7) * 7) << 1;
        self->posX.val = xMod + PLAYER.posX.val;
        self->posY.val = yMod + PLAYER.posY.val;
        if (self->ext.hitbylightning.unk92 &&
            g_Player.vram_flag &
                (TOUCHING_L_WALL | TOUCHING_R_WALL | TOUCHING_CEILING)) {
            terminate = true;
        }
        if (terminate) {
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
        mul = rsin(self->ext.hitbylightning.unk80);
        self->ext.hitbylightning.unk80 += self->ext.hitbylightning.unk82;
        xMod = ((rcos(self->ext.hitbylightning.unk7C) * mul) >> 7) *
               ((rand() % 8) + 8);
        yMod = -((rsin(self->ext.hitbylightning.unk7C) * mul) >> 7) *
                   ((rand() % 8) + 10) +
               self->ext.hitbylightning.unk98;
        self->posX.val = PLAYER.posX.val + xMod;
        self->posY.val = PLAYER.posY.val + yMod;
        self->ext.hitbylightning.unk98 -= 0x8000;
        prim = &g_PrimBuf[self->primIndex];
        break;
    }

    x = (self->posX.i.hi + (rand() & 7)) - 4;
    y = (self->posY.i.hi + (rand() & 0x1F)) - 0x18;
    mul2 = self->ext.hitbylightning.unk94;
    mul2 = (mul2 * rsin(self->ext.hitbylightning.unk80)) >> 0xC;
    prim = &g_PrimBuf[self->primIndex];
    for (i = 0; i < 5; i++) {
        primPrev = prim;
        prim = prim->next;
        *primPrev = *prim;
        primPrev->next = prim;
        primPrev->u0 = primPrev->u2 = (i * 0x10) + 0x90;
        primPrev->u1 = primPrev->u3 = ((i + 1) * 0x10) + 0x90;
        primPrev->v0 = primPrev->v1 = 0xC0;
        primPrev->v2 = primPrev->v3 = 0xCF;
    }
    prim->x0 = prim->x1;
    prim->y0 = prim->y1;
    prim->x2 = prim->x3;
    prim->y2 = prim->y3;
    angle = self->ext.hitbylightning.unk7C + 0x400;
    prim->x1 = x + (((rcos(angle) >> 4) * mul2) >> 8);
    prim->y1 = y - (((rsin(angle) >> 4) * mul2) >> 8);
    angle = self->ext.hitbylightning.unk7C - 0x400;
    prim->x3 = x + (((rcos(angle) >> 4) * mul2) >> 8);
    prim->y3 = y - (((rsin(angle) >> 4) * mul2) >> 8);
    angle = self->ext.hitbylightning.unk80 & 0xFFF;
    if (angle < 0x400) {
        prim->priority = PLAYER.zPriority + 2;
    } else if (angle < 0xC00) {
        prim->priority = PLAYER.zPriority - 2;
    } else {
        prim->priority = PLAYER.zPriority + 2;
    }
    prim->u0 = prim->u2 = (i << 4) + 0x90;
    prim->u1 = prim->u3 = ((i + 1) << 4) + 0x90;
    prim->v0 = prim->v1 = 0xC0;
    prim->v2 = prim->v3 = 0xCF;
}

// Corresponding DRA function is func_80124164
static s32 D_800AE270 = 255;
static s32 D_800AE274 = 255;
static s32 D_800AE278 = 255;
static s32 D_800AE27C = 127;
static s32 D_800AE280 = 127;
static s32 D_800AE284 = 63;
static s32 D_800AE288 = 127;
static s32 D_800AE28C = 63;
static s32 D_800AE290 = 127;
static void func_80165DD8(
    Primitive* prim, s32 colorMul, s32 y, s32 radius, bool arg4) {
    prim->y0 = prim->y1 = y - radius;
    prim->y2 = prim->y3 = y + radius;
    if (prim->y0 < 0) {
        prim->y0 = prim->y1 = 0;
    }
    if (prim->y0 > 240) {
        prim->y2 = prim->y3 = 240;
    }
    if (arg4 == 0) {
        prim->r1 = prim->r3 = D_800AE270 * colorMul / 256;
        prim->g1 = prim->g3 = D_800AE274 * colorMul / 256;
        prim->b1 = prim->b3 = D_800AE278 * colorMul / 256;
        prim->r0 = prim->r2 = D_800AE27C * colorMul / 256;
        prim->g0 = prim->g2 = D_800AE280 * colorMul / 256;
        prim->b0 = prim->b2 = D_800AE284 * colorMul / 256;
    } else {
        prim->r1 = prim->r3 = D_800AE270 * colorMul / 256;
        prim->g1 = prim->g3 = D_800AE274 * colorMul / 256;
        prim->b1 = prim->b3 = D_800AE278 * colorMul / 256;
        prim->r0 = prim->r2 = D_800AE288 * colorMul / 256;
        prim->g0 = prim->g2 = D_800AE28C * colorMul / 256;
        prim->b0 = prim->b2 = D_800AE290 * colorMul / 256;
    }
}

static void func_80166024() {
    PLAYER.palette = 0x815E;
    PLAYER.drawMode = DRAW_UNK_40 | DRAW_TPAGE2 | DRAW_TPAGE;
}

static void func_80166044() {
    PLAYER.palette = 0x8120;
    PLAYER.drawMode = DRAW_DEFAULT;
}

// Entity ID 66. Made by blueprint 77 (the very last one).
// Created in 3 spots in 2 functions (total of 6 calls).
// DRA version is very similar.
#if defined(VERSION_PSP)
extern Point16 D_80175000[32];
#else
static Point16 D_80175000[32];
#endif
void RicEntityTeleport(Entity* self) {
    Primitive* prim;
    s32 w;
    s32 h;
    s32 yVar;
    s32 xVar;
    s32 i;
    s32 result;
    s32 upperParams;
    bool showParticles;
    bool var_s5;

    upperParams = self->params & 0xFE00;
    FntPrint("pl_warp_flag:%02x\n", g_Player.warp_flag);
    showParticles = false;
    var_s5 = false;
    switch (self->step) {
    case 0:
        self->primIndex = g_api.AllocPrimitives(PRIM_GT4, LEN(D_80175000) + 4);
        if (self->primIndex == -1) {
            return;
        }
        self->flags = FLAG_POS_CAMERA_LOCKED | FLAG_KEEP_ALIVE_OFFCAMERA |
                      FLAG_HAS_PRIMS | FLAG_UNK_10000;
        prim = &g_PrimBuf[self->primIndex];
        for (i = 0; i < 2; i++) {
            prim->r0 = prim->b0 = prim->g0 = 0;
            prim->x0 = 0xC0 * i;
            prim->y0 = 0;
            prim->u0 = 0xC0;
            prim->v0 = 0xF0;
            prim->type = PRIM_TILE;
            prim->priority = 0x1FD;
            prim->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_HIDE | DRAW_TRANSP;
            prim = prim->next;
        }
        for (i = 0; i < 2; i++) {
            prim->type = PRIM_G4;
            prim->priority = 0x1F8;
            prim->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_TRANSP;
            prim = prim->next;
        }
        for (i = 0; i < LEN(D_80175000); i++) {
            xVar = PLAYER.posX.i.hi + (rand() % 28) - 14;
            yVar = 0xE0 - (rand() & 0x3F);
            D_80175000[i].x = xVar;
            D_80175000[i].y = yVar;
            prim->clut = 0x1B2;
            prim->clut = 0x1B5;
            prim->clut = 0x1BA;
            prim->tpage = 0x1A;
            prim->b0 = 0;
            prim->b1 = 0;
            prim->g0 = 0;
            prim->g1 = (rand() & 0x1F) + 1;
            prim->g2 = 0;
            prim->priority = 0x1F0;
            prim->drawMode = DRAW_HIDE;
            prim = prim->next;
        }
        self->ext.teleport.width = 0;
        self->ext.teleport.height = 0x10;
        self->ext.teleport.colorIntensity = 0x80;
        if ((self->params & 0x100) == 0x100) {
            self->ext.teleport.width = 0x10;
            self->ext.teleport.height = 0x100;
            self->ext.teleport.colorIntensity = 0x80;
            self->ext.teleport.unk90 = 0xFF;
            var_s5 = true;
            self->step = Player_Unk20;
#ifndef VERSION_PSP
            g_api.PlaySfx(SFX_TELEPORT_SYNTH_DOWN);
#endif
        } else {
            self->ext.teleport.unk90 = 0;
            self->ext.teleport.width = 1;
            self->ext.teleport.height = 0x10;
            self->ext.teleport.colorIntensity = 0x80;
            self->step = 1;
            g_api.PlaySfx(SFX_TELEPORT_BANG_A);
            g_api.PlaySfx(SFX_TELEPORT_SYNTH_UP);
        }
        break;
    case 1:
        self->ext.teleport.height += 0x20;
        if (self->ext.teleport.height > 0x100) {
            self->step++;
        }
        break;
    case 2:
        self->ext.teleport.width++;
        if (self->ext.teleport.width >= 0x10) {
            self->ext.teleport.width = 0x10;
            self->ext.teleport.timer = 0x80;
            self->step++;
        }
        break;
    case 3:
        showParticles = true;
        self->ext.teleport.colorIntensity += 4;
        if (self->ext.teleport.colorIntensity >= 0x100) {
            self->ext.teleport.colorIntensity = 0x100;
        }
        if (--self->ext.teleport.timer == 0) {
            PLAYER.palette = PAL_OVL(0x10D);
            self->step++;
        }
        break;
    case 4:
        func_80166024();
        self->ext.teleport.width--;
        if (self->ext.teleport.width <= 0) {
            self->ext.teleport.width = 0;
            self->step++;
        }
        break;
    case 5:
        func_80166024();
        var_s5 = true;
        self->ext.teleport.unk90 += 4;
        if (self->ext.teleport.unk90 >= 0x100) {
            self->ext.teleport.unk90 = 0xFF;
            self->ext.teleport.timer = 0x20;
            self->step++;
        }
        break;
    case 6:
        func_80166024();
        var_s5 = true;
        if (--self->ext.teleport.timer == 0) {
            self->ext.teleport.unk90 = 0;
            if (upperParams == 0) {
                D_80097C98 = 6;
            }
            if (upperParams == 0x200) {
                D_80097C98 = 4;
            }
            if (upperParams == 0x400) {
                D_80097C98 = 5;
            }
        }
        break;
    case 20:
        var_s5 = true;
        self->ext.teleport.unk90 = 0xFF;
        self->ext.teleport.timer = 0x20;
        self->step++;
        break;
    case 21:
        var_s5 = true;
        if (--self->ext.teleport.timer == 0) {
#ifdef VERSION_PSP
            g_api.PlaySfx(SFX_TELEPORT_SYNTH_DOWN);
#endif
            self->step++;
        }
        break;
    case 22:
        var_s5 = true;
        self->ext.teleport.unk90 -= 4;
        if (self->ext.teleport.unk90 <= 0) {
            self->ext.teleport.unk90 = 0;
            self->step++;
        }
        break;
    case 23:
        self->ext.teleport.width--;
        if (self->ext.teleport.width < 2) {
            self->ext.teleport.width = 0;
            self->ext.teleport.timer = 4;
            self->step++;
            g_Player.warp_flag = 1;
            g_api.PlaySfx(SFX_TELEPORT_BANG_B);
            DestroyEntity(self);
            return;
        }
        break;
    }

    self->posX.i.hi = PLAYER.posX.i.hi;
    self->posY.i.hi = PLAYER.posY.i.hi;
    xVar = PLAYER.posX.i.hi;
    yVar = PLAYER.posY.i.hi;
    w = self->ext.teleport.width;
    h = self->ext.teleport.height;
    prim = &g_PrimBuf[self->primIndex];

    for (i = 0; i < 2; prim = prim->next, i++) {
        prim->r0 = prim->b0 = prim->g0 = self->ext.teleport.unk90;
        prim->drawMode |= DRAW_HIDE;
        if (var_s5) {
            prim->drawMode &= ~DRAW_HIDE;
        }
    }

    prim->x1 = prim->x3 = xVar;
    prim->x0 = prim->x2 = xVar - w;
    func_80165DD8(
        prim, self->ext.teleport.colorIntensity, yVar, h, upperParams);
    prim = prim->next;
    prim->x1 = prim->x3 = xVar;
    prim->x0 = prim->x2 = xVar + w;
    func_80165DD8(
        prim, self->ext.teleport.colorIntensity, yVar, h, upperParams);
    prim = prim->next;
    if (showParticles) {
        for (i = 0; i < LEN(D_80175000); i++) {
            switch (prim->g0) {
            case 0:
                if (--prim->g1 == 0) {
                    prim->g0++;
                }
                break;
            case 1:
                xVar = D_80175000[i].x;
                yVar = D_80175000[i].y;
                result = func_8015FDB0(prim, xVar, yVar);
                D_80175000[i].y -= 16;
                if (result < 0) {
                    prim->drawMode |= DRAW_HIDE;
                    prim->g0++;
                } else {
                    prim->drawMode &= ~DRAW_HIDE;
                }
                break;
            }
            prim = prim->next;
        }
    } else {
        // @bug: should probably be doing prim = prim->next
        for (i = 0; i < LEN(D_80175000); i++) {
            prim->drawMode |= DRAW_HIDE;
        }
    }
}
