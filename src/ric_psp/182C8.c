// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../ric/ric.h"
#include <player.h>

Entity* RicGetFreeEntity(s16 start, s16 end) {
    Entity* entity = &g_Entities[start];
    s16 i;

    for (i = start; i < end; i++, entity++) {
        if (entity->entityId == E_NONE) {
            return entity;
        }
    }
    return NULL;
}

Entity* RicGetFreeEntityReverse(s16 start, s16 end) {
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
    SubweaponDef* subwpn = &D_80154688[entity->ext.subweapon.subweaponId];
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
s32 func_8015FB84(SubweaponDef* actualSubwpn, s32 isItemCrash, s32 useHearts) {
    SubweaponDef* subwpn;

    // Not an item crash. Just read the item in.
    if (isItemCrash == 0) {
        *actualSubwpn = D_80154688[g_Status.subWeapon];
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
    subwpn = &D_80154688[g_Status.subWeapon];
    *actualSubwpn = D_80154688[subwpn->crashId];
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
    {2, FRAME(1, 0)},  {2, FRAME(2, 0)},
    {2, FRAME(3, 0)},  {2, FRAME(4, 0)},
    {2, FRAME(5, 0)},  {2, FRAME(6, 0)},
    {2, FRAME(7, 0)},  {2, FRAME(8, 0)},
    {2, FRAME(9, 0)},  {2, FRAME(10, 0)},
    {2, FRAME(11, 0)}, {2, FRAME(12, 0)},
    {2, FRAME(13, 0)}, A_END};
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
        entity->unk6C = 0xFF;
        entity->drawFlags =
            FLAG_DRAW_ROTX | FLAG_DRAW_ROTY | FLAG_DRAW_UNK10 | FLAG_DRAW_UNK20;
        entity->rotX = entity->rotY = 0x40;
        entity->anim = anim_smoke_dark;
        entity->posY.i.hi += (rand() % 35) - 15;
        entity->posX.i.hi += (rand() % 20) - 10;
        entity->velocityY = -0x6000 - (rand() & 0x3FFF);
        entity->step++;
        break;
    case 1:
        if (entity->unk6C > 16) {
            entity->unk6C -= 8;
        }
        entity->posY.val += entity->velocityY;
        entity->rotX += 8;
        entity->rotY += 8;
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
void func_80167A70(Entity* self);
void RicEntitySubwpnThrownAxe(Entity* self);
void RicEntityCrashAxe(Entity* self);
void RicEntitySubwpnThrownDagger(Entity* self);
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
    func_80167A70,
    RicEntitySubwpnThrownAxe,
    RicEntityCrashAxe,
    RicEntitySubwpnThrownDagger,
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
    for (i = 4; i < 0x40; i++, g_CurrentEntity++, entity++) {
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
            g_api.g_pfn_800EA5AC(1, D_80174FB0, D_80174FB4, D_80174FB8);
        }
    }
    D_80174F80[1] = D_80174F80[2] = 0;
    if (g_Entities[16].enemyId == 1) {
        D_80174F80[1] = 1;
    } else if (g_Entities[16].enemyId == 2) {
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
    if (func_8015FB84(&subwpn, true, false) >= 0) {
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

#if defined(VERSION_US)
#define NON_CRITICAL false
#else
#define NON_CRITICAL true
#endif
static FactoryBlueprint g_RicFactoryBlueprints[] = {
    // clang-format off
    B_MAKE(E_SMOKE_PUFF, 5, 1, true, true, 2, B_DECOR, 0, 0),
    B_MAKE(E_SMOKE_PUFF, 3, 1, true, true, 4, B_DECOR, 2, 0),
    B_MAKE(E_SUBWPN_CROSS, 1, 1, true, true, 0, B_KIND_9, 1, 8),
    B_MAKE(E_80169C10, 3, 1, true, true, 2, B_DECOR, 0, 0),
    B_MAKE(E_HIT_BY_CUT_BLOOD, 1, 1, true, true, 0, B_DECOR, 0, 0),
    B_MAKE(E_SUBWPN_CROSS_TRAIL, 4, 1, true, true, 4, B_DECOR, 0, 4),
    B_MAKE(E_SUBWPN_HOLY_WATER, 1, 1, true, true, 0, B_KIND_9, 1, 8),
    B_MAKE(E_SUBWPN_HOLY_WATER_FLAME, 1, 1, true, true, 0, B_WPN, 0, 0),
    B_MAKE(E_80161C2C, 6, 1, true, true, 12, B_KIND_8, 3, 0),
    B_MAKE(E_80161C2C, 128, 1, true, true, 3, B_KIND_8, 3, 8),
    B_MAKE(E_WHIP, 15, 15, NON_CRITICAL, true, 0, B_KIND_10, 1, 0),
    B_MAKE(E_HIT_BY_CUT_BLOOD, 72, 1, true, true, 2, B_KIND_3, 1, 0),
    B_MAKE(E_CRASH_HYDROSTORM, 48, 1, NON_CRITICAL, true, 6, B_WPN, 1, 48),
    B_MAKE(E_CRASH_CROSS_ROTATING, 1, 1, NON_CRITICAL, true, 0, B_KIND_9, 0, 0),
    B_MAKE(E_CRASH_CROSS_BEAM, 6, 1, true, true, 24, B_KIND_9, 0, 0),
    B_MAKE(E_NOT_IMPLEMENTED_1, 16, 16, NON_CRITICAL, true, 0, B_KIND_8, 1, 0),
    //0x10
    B_MAKE(E_NOT_IMPLEMENTED_2, 15, 15, true, true, 0, B_KIND_8, 1, 0),
    B_MAKE(E_ARM_BRANDISH_WHIP, 1, 1, NON_CRITICAL, true, 0, B_KIND_12, 1, 0),
    B_MAKE(E_80167964, 1, 1, true, true, 0, B_KIND_8, 0, 0),
    B_MAKE(E_SUBWPN_AXE, 1, 1, true, true, 0, B_KIND_9, 1, 8),
    B_MAKE(E_80161EF8, 1, 1, true, true, 0, B_DECOR, 4, 0),
    B_MAKE(E_NOT_IMPLEMENTED_3, 1, 1, true, true, 0, B_DECOR, 0, 0),
    B_MAKE(E_REVIVAL_COLUMN, 1, 1, NON_CRITICAL, true, 0, B_KIND_3, 0, 0),
    B_MAKE(E_APPLY_MARIA_POWER_ANIM, 4, 1, NON_CRITICAL, true, 24, B_KIND_3, 0, 0),
    B_MAKE(E_SMOKE_PUFF, 1, 1, true, true, 0, B_DECOR, 0, 0),
    B_MAKE(E_SLIDE_KICK, 1, 1, true, true, 0, B_WPN, 0, 0),
    B_MAKE(E_BLADE_DASH, 1, 1, true, true, 0, B_WPN, 0, 0),
    B_MAKE(E_801623E0, 1, 1, true, true, 0, B_KIND_3, 0, 0),
    B_MAKE(E_80162604, 1, 1, true, true, 0, B_KIND_3, 0, 0),
    B_MAKE(E_MARIA, 1, 1, NON_CRITICAL, true, 0, B_KIND_5, 0, 0),
    B_MAKE(E_MARIA_POWERS, 4, 1, true, true, 4, B_KIND_3, 0, 0),
    B_MAKE(E_80160D2C, 1, 1, true, true, 0, B_WPN, 0, 0),
    //0x20
    B_MAKE(E_NOT_IMPLEMENTED_4, 1, 1, true, true, 0, B_DECOR, 0, 0),
    B_MAKE(E_BLINK_WHITE, 1, 1, true, true, 0, B_DECOR, 0, 0),
    B_MAKE(E_SUBWPN_CRASH_CROSS_PARTICLES, 1, 1, true, true, 0, B_DECOR, 0, 0),
    B_MAKE(E_801641A0, 1, 1, true, true, 0, B_DECOR, 0, 0),
    B_MAKE(E_SHRINKING_POWERUP_RING, 1, 1, true, true, 0, B_DECOR, 0, 0),
    B_MAKE(E_SHRINKING_POWERUP_RING, 1, 1, true, true, 0, B_DECOR, 0, 4),
    B_MAKE(E_SHRINKING_POWERUP_RING, 1, 1, true, true, 0, B_DECOR, 0, 8),
    B_MAKE(E_SHRINKING_POWERUP_RING, 1, 1, true, true, 0, B_DECOR, 0, 12),
    B_MAKE(E_80167A70, 1, 1, true, true, 0, B_DECOR, 0, 0),
    B_MAKE(E_CRASH_AXE, 8, 8, NON_CRITICAL, true, 0, B_WPN, 1, 32),
    B_MAKE(E_HIT_BY_CUT_BLOOD, 3, 1, true, true, 3, B_DECOR, 0, 0),
    B_MAKE(E_SUBWPN_DAGGER, 1, 1, true, true, 0, B_KIND_9, 1, 8),
    B_MAKE(E_SUBWPN_DAGGER, 128, 1, NON_CRITICAL, true, 4, B_KIND_14, 4, 8),
    B_MAKE(E_80160F0C, 1, 1, true, true, 0, B_WPN, 0, 0),
    B_MAKE(E_HIT_BY_CUT_BLOOD, 12, 1, true, true, 2, B_KIND_8, 3, 0),
    B_MAKE(E_HIT_BY_ICE, 1, 1, true, true, 0, B_DECOR, 0, 0),
    //0x30
    B_MAKE(E_HIT_BY_LIGHTNING, 1, 1, true, true, 0, B_DECOR, 0, 0),
    B_MAKE(E_SUBWPN_VIBHUTI, 1, 1, true, true, 0, B_WPN, 1, 8),
    B_MAKE(E_SUBWPN_REBOUND_STONE, 1, 1, true, true, 0, B_WPN, 1, 4),
    B_MAKE(E_SUBWPN_AGUNEA, 1, 1, true, true, 0, B_WPN, 1, 4),
    B_MAKE(E_SUBWPN_AGUNEA_HIT_ENEMY, 1, 1, true, true, 0, B_DECOR, 1, 0),
    B_MAKE(E_80161C2C, 72, 1, true, true, 2, B_KIND_3, 1, 16),
    B_MAKE(E_CRASH_VIBHUTI, 1, 1, NON_CRITICAL, true, 0, B_DECOR, 0, 18),
    B_MAKE(E_CRASH_VIBHUTI_CLOUD, 1, 1, true, true, 0, B_KIND_6, 0, 0),
    B_MAKE(E_CRASH_REBOUND_STONE, 1, 1, NON_CRITICAL, true, 0, B_DECOR, 0, 0),
    B_MAKE(E_8016D9C4, 1, 1, true, true, 0, B_WPN, 0, 0),
    B_MAKE(E_CRASH_REBOUND_STONE_EXPLOSION, 1, 1, NON_CRITICAL, true, 0, B_WPN, 0, 0),
    B_MAKE(E_CRASH_BIBLE, 1, 1, NON_CRITICAL, true, 0, B_WPN, 0, 0),
    B_MAKE(E_CRASH_BIBLE_BEAM, 1, 1, true, true, 0, B_WPN, 0, 0),
    B_MAKE(E_SUBWPN_BIBLE, 1, 1, true, true, 0, B_WPN, 0, 0),
    B_MAKE(E_SUBWPN_BIBLE_TRAIL, 1, 1, true, true, 0, B_DECOR, 0, 0),
    B_MAKE(E_SUBWPN_STOPWATCH, 1, 1, true, true, 0, B_WPN, 0, 0),
    //0x40
    B_MAKE(E_SUBWPN_STOPWATCH_CIRCLE, 1, 1, true, true, 0, B_DECOR, 0, 0),
    B_MAKE(E_CRASH_STOPWATCH, 1, 1, NON_CRITICAL, true, 0, B_DECOR, 0, 0),
    B_MAKE(E_8016F198, 2, 1, true, true, 2, B_DECOR, 0, 0),
    B_MAKE(E_AGUNEA_CIRCLE, 1, 1, NON_CRITICAL, true, 0, B_WPN, 0, 20),
    B_MAKE(E_AGUNEA_LIGHTNING, 1, 1, true, true, 0, B_DECOR, 0, 0),
    B_MAKE(E_CRASH_REBOUND_STONE_PARTICLES, 1, 1, true, true, 0, B_KIND_3, 0, 0),
    B_MAKE(E_HIT_BY_DARK, 96, 1, true, true, 4, B_KIND_8, 1, 0),
    B_MAKE(E_HIT_BY_HOLY, 1, 1, true, true, 0, B_DECOR, 0, 0),
    B_MAKE(E_CRASH_STOPWATCH_DONE_PARTICLE, 1, 1, true, true, 0, B_DECOR, 0, 0),
    B_MAKE(E_CRASH_STOPWATCH_LIGHTNING, 1, 1, true, true, 0, B_WPN, 0, 0),
    B_MAKE(E_SMOKE_PUFF, 1, 1, true, true, 0, B_WPN, 0, 0),
    B_MAKE(E_SMOKE_PUFF, 4, 1, true, true, 2, B_DECOR, 3, 0),
    B_MAKE(E_SMOKE_PUFF, 6, 6, true, true, 0, B_DECOR, 0, 0),
    B_MAKE(E_TELEPORT, 1, 1, false, true, 0, B_KIND_3, 0, 0),
    // clang-format on
};
STATIC_ASSERT(
    LEN(g_RicFactoryBlueprints) == NUM_BLUEPRINTS, "bp array wrong size");
static u8 entity_ranges[][2] = {
    {0x30, 0x3F}, {0x20, 0x2F}, {0x10, 0x1E}, {0x10, 0x3F},
    {0x1F, 0x1F}, {0x30, 0x30}, {0x10, 0x2F}, {0x00, 0x00}};
void RicEntityFactory(Entity* self) {
    Entity* newEntity;
    s16 nPerCycle;
    s16 i;
    s16 startIndex;
    s16 endIndex;
    u8* data;

    if (self->step == 0) {
        data = (u8*)&g_RicFactoryBlueprints[self->params];
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
        case 0:
            self->flags |= FLAG_POS_CAMERA_LOCKED;
            break;
        case 4:
            self->flags |= FLAG_UNK_20000;
        case 2:
        case 9:
            self->flags |= FLAG_POS_PLAYER_LOCKED;
        case 3:
        case 7:
            self->posX.val = PLAYER.posX.val;
            self->posY.val = PLAYER.posY.val;
            break;
        case 8:
            self->flags |= FLAG_POS_PLAYER_LOCKED;
            self->posX.val = self->ext.factory.parent->posX.val;
            self->posY.val = self->ext.factory.parent->posY.val;
            break;
        }
    } else {
        switch (self->ext.factory.origin) {
        case 0:
            break;
        case 9:
            if (g_Player.unk4E) {
                DestroyEntity(self);
                return;
            }
        case 2:
            self->posX.val = g_Entities->posX.val;
            self->posY.val = PLAYER.posY.val;
            break;
        case 4:
            self->posX.val = g_Entities->posX.val;
            self->posY.val = PLAYER.posY.val;
            if (PLAYER.step != PL_S_RUN) {
                self->entityId = 0;
                return;
            }
            break;
        case 3:
            self->posX.val = g_Entities->posX.val;
            self->posY.val = PLAYER.posY.val;
            if (PLAYER.step == PL_S_HIT) {
                self->entityId = 0;
                return;
            }
            break;
        case 7:
            self->posX.val = g_Entities->posX.val;
            self->posY.val = PLAYER.posY.val;
            if (PLAYER.step != PL_S_HIT) {
                self->entityId = 0;
                return;
            }
            break;
        case 8:
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
        if (self->ext.factory.kind == 0) {
            newEntity = RicGetFreeEntityReverse(startIndex, endIndex + 1);
        } else if (self->ext.factory.kind == 4) {
            newEntity = &g_Entities[31];
        } else if (self->ext.factory.kind == 5) {
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
    -0x3000, -0x4000, -0x6000, -0x8000, -0xA000, -0xC000};
static s16 rot_x_80154C74[] = {0x0030, 0x0040, 0x0050, 0x0060, 0x0070, 0x0080};
static AnimationFrame anim_smoke_puff[] = {
    {1, FRAME(0x01, 0)},
    {1, FRAME(0x02, 0)},
    {1, FRAME(0x03, 0)},
    {1, FRAME(0x04, 0)},
    {1, FRAME(0x05, 0)},
    {1, FRAME(0x06, 0)},
    {1, FRAME(0x07, 0)},
    {1, FRAME(0x08, 0)},
    {1, FRAME(0x09, 0)},
    {1, FRAME(0x0A, 0)},
    {1, FRAME(0x0B, 0)},
    {1, FRAME(0x0C, 0)},
    {1, FRAME(0x0D, 0)},
    {1, FRAME(0x0E, 0)},
    {1, FRAME(0x0F, 0)},
    {1, FRAME(0x10, 0)},
    {1, FRAME(0x11, 0)},
    {1, FRAME(0x12, 0)},
    {1, FRAME(0x13, 0)},
    {1, FRAME(0x14, 0)},
    {1, FRAME(0x15, 0)},
    {1, FRAME(0x16, 0)},
    {1, FRAME(0x17, 0)},
    {1, FRAME(0x18, 0)},
    A_END};
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
        self->drawFlags = FLAG_DRAW_ROTX | FLAG_DRAW_ROTY | FLAG_DRAW_UNK8;
        self->unk6C = 0x60;
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
            self->rotX = rot_x_80154C74[1] + 0x40;
            self->rotY = self->rotX;
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
            self->rotX = rot_x_80154C74[paramsLo] + 0x20;
            self->rotY = self->rotX;
            self->step++;
            return;
        }
        if (paramsHi == 1) {
            if (g_Player.vram_flag & 0x8000) {
                posX /= 2;
            }
        }
        if (self->facingLeft) {
            posX = -posX;
        }
        self->posX.i.hi += posX;
        self->posY.i.hi += 0x18;
        self->rotX = rot_x_80154C74[paramsLo] + 0x40;
        self->velocityY = velocity_x_80154C5C[paramsLo];
        if (paramsHi == 1) {
            self->velocityY = FIX(-0.25);
            RicSetSpeedX(-0x3000);
            self->rotX = rot_x_80154C74[1] + 0x40;
        }
        if (paramsHi == 5) {
            self->velocityY = velocity_x_80154C5C[4 - paramsLo * 2];
        }
        if (paramsHi == 2) {
            self->velocityY = FIX(-0.5);
            RicSetSpeedX(-0x3000);
            self->rotX = rot_x_80154C74[1] + 0x40;
        }
        self->rotY = self->rotX;
        if (paramsHi == 10) {
            self->posY.i.hi -= 6;
        }
        self->step++;
        break;
    case 1:
        self->unk6C -= 2;
        self->posY.val += self->velocityY;
        self->posX.val += self->velocityX;
        if (self->poseTimer < 0) {
            DestroyEntity(self);
            return;
        }
        break;
    }
}

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/182C8", RicEntityHitByCutBlood);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/182C8", func_80161C2C);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/182C8", func_80161EF8);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/182C8", RicEntityApplyMariaPowerAnim);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/182C8", func_801623E0);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/182C8", func_80162604);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/182C8", RicEntityMariaPowers);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/182C8", RicEntityNotImplemented4);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/182C8", RicEntityMaria);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/182C8", func_80162E9C);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/182C8", RicEntityPlayerBlinkWhite);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/182C8", func_801641A0);

// clang-format off
INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/182C8", RicEntityShrinkingPowerUpRing);
// clang-format on

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/182C8", RicEntityHitByIce);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/182C8", RicEntityHitByLightning);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/182C8", func_80165DD8);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/182C8", func_80166024);

INCLUDE_ASM("ric_psp/nonmatchings/ric_psp/182C8", RicEntityTeleport);
