// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "servant.h"
#include "sfx.h"

extern s32 s_TargetMatch[0x80];
extern s32 g_DemonAbilityStats[10][4];
extern FamiliarStats s_DemonStats;
extern s32 s_LastTargetedEntityIndex;
extern AnimationFrame* g_DemonAnimationFrames[];
extern s32 s_ServantId;
extern u16 g_DemonClut[64];
extern SpriteParts* g_DemonSpriteParts[];
extern s32 D_us_801786D0;
extern s32 D_us_801786D4;

extern void (*s_PassthroughFunctions[])(Entity*);

void ServantInit(InitializeMode);
void UpdateServantDefault(Entity*);
void func_us_80174FD0(Entity*);
void func_us_8017540C(Entity*);
void unused_5800(Entity*);
void unused_5808(Entity*);
void func_us_80175810(Entity*);
void func_us_80175C08(Entity*);
void func_us_80175D20(Entity*);
void UpdateServantSfxPassthrough(Entity*);
void FunctionPointerPassthrough(Entity*);
void func_us_801765A0(Entity*);
void func_us_80176814(Entity*);
void func_us_80176C1C(Entity*);
void func_us_801771B0(Entity*);
void func_us_80177690(Entity*);

ServantDesc demon_ServantDesc = {
    ServantInit,
    UpdateServantDefault,
    func_us_80174FD0,
    func_us_8017540C,
    unused_5800,
    unused_5808,
    func_us_80175810,
    func_us_80175C08,
    func_us_80175D20,
    UpdateServantSfxPassthrough,
    FunctionPointerPassthrough,
    func_us_801765A0,
    func_us_80176814,
    func_us_80176C1C,
    func_us_801771B0,
    func_us_80177690,
};

static void SetAnimationFrame(Entity* self, s32 animationIndex) {
    if (self->anim != g_DemonAnimationFrames[animationIndex]) {
        self->anim = g_DemonAnimationFrames[animationIndex];
        self->animFrameIdx = 0;
        self->animFrameDuration = 0;
    }
}

static Entity* FindValidTarget(Entity* self) {
    const int EntitySearchCount = 128;
    s32 foundIndex;
    s32 i;
    u32 found;
    Entity* entity;
    s32 distance;

    found = 0;
    entity = &g_Entities[STAGE_ENTITY_START];
    for (i = 0; i < EntitySearchCount; i++, entity++) {
        s_TargetMatch[i] = 0;
        if (!entity->entityId) {
            continue;
        }
        if (entity->hitboxState == 0) {
            continue;
        }
        if (entity->flags & FLAG_UNK_00200000) {
            continue;
        }
        if (entity->posX.i.hi < -16) {
            continue;
        }
        if (entity->posX.i.hi > 272) {
            continue;
        }
        if (entity->posY.i.hi > 240) {
            continue;
        }
        if (entity->posY.i.hi < 0) {
            continue;
        }
        if (!g_DemonAbilityStats[s_DemonStats.level / 10][2] &&
            entity->hitboxState & 8) {
            continue;
        }

        if (abs(self->posX.i.hi - entity->posX.i.hi) >
                g_DemonAbilityStats[s_DemonStats.level / 10][3] ||
            abs(self->posY.i.hi - entity->posY.i.hi) >
                g_DemonAbilityStats[s_DemonStats.level / 10][3]) {
            continue;
        }
        if (self->facingLeft && self->posX.i.hi < entity->posX.i.hi) {
            continue;
        }
        if (!self->facingLeft && self->posX.i.hi > entity->posX.i.hi) {
            continue;
        }
        if (entity->hitPoints >= 0x7000) {
            continue;
        }

        if (entity->flags & FLAG_UNK_80000) {
            if (entity->hitPoints >=
                g_DemonAbilityStats[s_DemonStats.level / 10][1]) {
                found++;
                s_TargetMatch[i] = 1;
            }
        } else {
            entity->flags |= FLAG_UNK_80000;
            return entity;
        }
    }

    if (found > 0) {
        foundIndex = s_LastTargetedEntityIndex % EntitySearchCount;
        for (i = 0; i < EntitySearchCount; i++) {
            if (s_TargetMatch[foundIndex]) {
                entity = &g_Entities[STAGE_ENTITY_START + foundIndex];
                s_LastTargetedEntityIndex =
                    (foundIndex + 1) % EntitySearchCount;
                return entity;
            }
            foundIndex = (foundIndex + 1) % EntitySearchCount;
        }
    }

    return NULL;
}

#include "../check_entity_valid.h"

void unused_2DBC(void) {}

INCLUDE_ASM("servant/tt_003/nonmatchings/demon", func_us_80172DC4);

void DestroyEntityPassthrough(Entity* self) { DestroyEntity(self); }

INCLUDE_ASM("servant/tt_003/nonmatchings/demon", func_us_80172EF8);

INCLUDE_ASM("servant/tt_003/nonmatchings/demon", func_us_80173348);

INCLUDE_ASM("servant/tt_003/nonmatchings/demon", func_us_801737F0);

INCLUDE_ASM("servant/tt_003/nonmatchings/demon", func_us_80173D14);

void ServantInit(InitializeMode mode) {
    u16* src;
    u16* dst;
    RECT rect;
    s32 i;
    SpriteParts** spriteBanks;
    Entity* entity;

#ifdef VERSION_PC
    const int lenServant = LEN(g_ServantClut);
    const int lenDemon = LEN(g_DemonClut);
#else
    const int lenServant = 256;
    const int lenDemon = 80;
#endif

    s_ServantId = g_Servant;

    if ((mode == MENU_SWITCH_SERVANT) || (mode == MENU_SAME_SERVANT)) {
        ProcessEvent(NULL, true);
        if (mode == MENU_SAME_SERVANT) {
            return;
        }
    }

    dst = &g_Clut[CLUT_INDEX_SERVANT];
    src = g_ServantClut;
    for (i = 0; i < lenServant; i++) {
        *dst++ = *src++;
    }

    dst = &g_Clut[CLUT_INDEX_SERVANT_OVERWRITE];
    src = g_DemonClut;

    for (i = 0; i < lenDemon; i++) {
        *dst++ = *src++;
    }

    rect.x = 0;
    rect.w = 0x100;
    rect.h = 1;
    rect.y = 0xF4;

    dst = &g_Clut[CLUT_INDEX_SERVANT];
    LoadImage(&rect, (u_long*)dst);

    spriteBanks = g_api.o.spriteBanks;
    spriteBanks += 20;
    *spriteBanks = (SpriteParts*)g_DemonSpriteParts;

    entity = &g_Entities[SERVANT_ENTITY_INDEX];

    DestroyEntity(entity);
    entity->unk5A = 0x6C;
    entity->palette = 0x140;
    entity->animSet = ANIMSET_OVL(20);
    entity->zPriority = PLAYER.zPriority - 2;
    entity->facingLeft = PLAYER.facingLeft;
    entity->params = 0;

    if (mode == MENU_SWITCH_SERVANT) {
        if (LOW(D_8003C708.flags) &
            (LAYOUT_RECT_PARAMS_UNKNOWN_20 | LAYOUT_RECT_PARAMS_UNKNOWN_40)) {
            entity->entityId = 0xD1;
        } else {
            entity->entityId = 0xD8;
        }
        entity->posX.val = FIX(128);
        entity->posY.val = FIX(-32);
    } else {
        entity->entityId = 0xD1;
        if (D_8003C708.flags & LAYOUT_RECT_PARAMS_UNKNOWN_20) {
            if (ServantUnk0()) {
                entity->posX.val = FIX(192);
            } else {
                entity->posX.val = FIX(64);
            }
            entity->posY.val = FIX(160);
        } else {
            entity->posX.val =
                PLAYER.posX.val + (PLAYER.facingLeft ? FIX(24) : FIX(-24));
            entity->posY.val = PLAYER.posY.val + FIX(-32);
        }
    }

    D_us_801786D0 = 0;
    D_us_801786D4 = 0;
    g_api.GetServantStats(entity, 0, 0, &s_DemonStats);
}

INCLUDE_ASM("servant/tt_003/nonmatchings/demon", UpdateServantDefault);

INCLUDE_ASM("servant/tt_003/nonmatchings/demon", func_us_80174FD0);

INCLUDE_ASM("servant/tt_003/nonmatchings/demon", func_us_8017540C);

void unused_5800(Entity* self) {}

void unused_5808(Entity* self) {}

INCLUDE_ASM("servant/tt_003/nonmatchings/demon", func_us_80175810);

INCLUDE_ASM("servant/tt_003/nonmatchings/demon", func_us_80175C08);

INCLUDE_ASM("servant/tt_003/nonmatchings/demon", func_us_80175D20);

void UpdateServantSfxPassthrough(Entity* self) { ProcessSfxState(self); }

void FunctionPointerPassthrough(Entity* arg0) {
    s_PassthroughFunctions[arg0->params](arg0);
}

INCLUDE_ASM("servant/tt_003/nonmatchings/demon", func_us_801765A0);

INCLUDE_ASM("servant/tt_003/nonmatchings/demon", func_us_80176814);

INCLUDE_ASM("servant/tt_003/nonmatchings/demon", func_us_80176C1C);

INCLUDE_ASM("servant/tt_003/nonmatchings/demon", func_us_801771B0);

INCLUDE_ASM("servant/tt_003/nonmatchings/demon", func_us_80177690);

#ifndef VERSION_PSP
#include "../servant_update_anim.h"
#endif

#include "../../destroy_entity.h"

#ifndef VERSION_PSP
#include "../accumulate_toward_zero.h"
#include "../search_for_entity_in_range.h"
#endif

#include "../calculate_angle_to_entity.h"

#include "../get_target_position_with_distance_buffer.h"

#ifndef VERSION_PSP
#include "../calculate_distance.h"
#include "../play_sfx.h"
#endif

#include "../process_event.h"

#include "../create_event_entity.h"

#include "../is_movement_allowed.h"

#ifndef VERSION_PSP
#include "../check_all_entities_valid.h"
#endif

#include "../servant_unk0.h"
