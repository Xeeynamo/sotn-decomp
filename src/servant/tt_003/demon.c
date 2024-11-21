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

// This is likey the analog to Faerie.ExecuteAbilityInitialize
void func_us_80172DC4(Entity* self) {
    if (!self->ext.demon.isAbilityInitialized) {
        if ((self->entityId == 0xD1) || (self->entityId == 0xD8)) {
            self->flags = FLAG_POS_CAMERA_LOCKED | FLAG_KEEP_ALIVE_OFFCAMERA |
                          FLAG_UNK_20000;
            SetAnimationFrame(self, 0);

            self->ext.demon.randomMovementAngle = rand() % 4096;
            self->ext.demon.defaultDistToTargetLoc = 8;
            self->ext.demon.targetAngle = 0;
            self->ext.demon.maxAngle = 0x20;
            self->step++;
        }
    } else {
        switch (self->entityId) {
        case 0xD1:
        case 0xD2:
        case 0xD3:
        case 0xD6:
        case 0xD8:
            self->flags = FLAG_POS_CAMERA_LOCKED | FLAG_KEEP_ALIVE_OFFCAMERA |
                          FLAG_UNK_20000;
            SetAnimationFrame(self, 0);
            self->step++;
            break;
        }
    }
    D_us_801786D0 = 0;
    self->ext.demon.isAbilityInitialized = self->entityId;
}

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

//#ifndef NON_MATCHING
//INCLUDE_ASM("servant/tt_003/nonmatchings/demon", UpdateServantDefault);
//#else
extern /*?*/s32 D_us_801719F0;
extern s8 D_us_80171FE8;
extern /*?*/s32 D_us_80172092;
extern s32 D_us_801785C4;
extern s32 D_us_801785C8;
extern s16 D_us_801785CC;
extern s16 D_us_801785D0;
extern u16 D_us_801785D4;
extern s16 D_us_801785D8;
extern u16 D_us_801785DC;
extern u16 D_us_801785E0;
extern s32 D_us_801785E4;
extern s32 D_us_801785E8;
extern s32 D_us_801785EC;
extern s32 D_us_801786D8;
extern u16 PLAYER.facingLeft;
extern u16 PLAYER.posY.i.hi;
extern u16 PLAYER_zPriority;

void UpdateServantDefault(Entity* arg0)
{
    ServantEvent* var_v1_2;
    s16 temp_a0;
    s16 temp_a1_3;
    s16 temp_a2;
    s16 temp_v0_3;
    s16 temp_v0_9;
    s32 temp_v0;
    s32 temp_v0_4;
    s32 temp_v0_5;
    s32 temp_v0_6;
    s32 temp_v0_8;
    s32 temp_v1_2;
    s32 temp_v1_4;
    s32 var_a0;
    s32 var_a0_2;
    s32 var_a1;
    s32 var_v0_2;
    s32 var_v0_4;
    s32 var_v1;
    u16 temp_a1;
    u16 temp_a1_2;
    u16 temp_v0_2;
    u16 temp_v1;
    u16 temp_v1_3;
    u16 var_v0;
    u16 var_v0_3;
    u32 temp_v0_7;

    g_api.GetServantStats(arg0, 0, 0, &s_DemonStats);
    if (D_us_801786D4 != 0) {
        arg0->zPriority = PLAYER_zPriority - 2;
    }
    if (D_8003C708.flags & 0x20) {
        temp_v0 = ServantUnk0();
        switch (temp_v0) {                          // irregular
            case 0:
                D_us_801785C4 = 0x40;
                break;
            case 1:
                D_us_801785C4 = 0xC0;
                break;
            case 2:
                var_v1 = 0x40;
                if (arg0->posX.i.hi >= 0x81) {
                    var_v1 = 0xC0;
                }
                D_us_801785C4 = var_v1;
                break;
        }
        D_us_801785C8 = 0xA0;
    } else {
        D_us_801785E0 = -0x18U;
        if (PLAYER.facingLeft != 0) {
            D_us_801785E0 = 0x18;
        }
        temp_a1 = (u16) arg0->ext.demon.randomMovementAngle;
        D_us_801785D4 = temp_a1;
        D_us_801785CC = (u16) g_Entities->posX.i.hi + D_us_801785E0;
        D_us_801785D0 = PLAYER.posY.i.hi - 0x20;
        arg0->ext.demon.randomMovementAngle = ((u16) arg0->ext.demon.randomMovementAngle + 0x10) & 0xFFF;
        D_us_801785DC = (u16) arg0->ext.demon.defaultDistToTargetLoc;
        D_us_801785C4 = D_us_801785CC + ((s32) (rcos((s32) ((s16) temp_a1 + ((u32) (temp_a1 << 0x10) >> 0x1F)) >> 1) * (s16) D_us_801785DC) >> 0xC);
        D_us_801785C8 = D_us_801785D0 - ((s32) (rsin((s32) (s16) D_us_801785D4) * ((s16) D_us_801785DC / 2)) >> 0xC);
    }
    temp_v1 = arg0->step;
    switch (temp_v1) {                              // switch 1; irregular
        case 0:                                     // switch 1
            func_us_80172DC4(arg0);
            break;
        case 1:                                     // switch 1
            if (D_8003C708.flags & 0x20) {
                var_v0 = 1;
                if (g_Entities->posX.i.hi >= arg0->posX.i.hi) {
                    arg0->facingLeft = 0;
                } else {
                    goto block_39;
                }
            } else {
                temp_a1_2 = arg0->facingLeft;
                if (PLAYER.facingLeft != temp_a1_2) {
                    temp_a0 = arg0->posX.i.hi;
                    var_v0_2 = D_us_801785C4 - temp_a0;
                    if (var_v0_2 < 0) {
                        var_v0_2 = -var_v0_2;
                    }
                    if (var_v0_2 <= 0) {
                        arg0->facingLeft = PLAYER.facingLeft;
                    } else if (temp_a1_2 == 0) {
                        if (D_us_801785C4 < temp_a0) {
                            arg0->facingLeft = PLAYER.facingLeft;
                        }
                    } else if (temp_a0 < D_us_801785C4) {
                        arg0->facingLeft = PLAYER.facingLeft;
                    }
                } else if (PLAYER.facingLeft == 0) {
                    if ((arg0->posX.i.hi - D_us_801785C4) >= 0x29) {
                        arg0->facingLeft = 1;
                    }
                } else {
                    var_v0 = PLAYER.facingLeft == 0;
                    if ((D_us_801785C4 - arg0->posX.i.hi) >= 0x29) {
block_39:
                        arg0->facingLeft = var_v0;
                    }
                }
            }
            temp_v0_2 = CalculateAngleToEntity(arg0, (s16) D_us_801785C4, (s16) D_us_801785C8);
            D_us_801785D4 = temp_v0_2;
            temp_v0_3 = GetTargetPositionWithDistanceBuffer((s16) temp_v0_2, arg0->ext.demon.targetAngle, arg0->ext.demon.maxAngle);
            arg0->ext.demon.targetAngle = temp_v0_3;
            temp_a2 = (u16) D_us_801785C4 - (u16) arg0->posX.i.hi;
            temp_a1_3 = (u16) D_us_801785C8 - (u16) arg0->posY.i.hi;
            D_us_801785D8 = temp_v0_3;
            D_us_801785CC = temp_a2;
            D_us_801785D0 = temp_a1_3;
            temp_v0_4 = SquareRoot12(((temp_a2 * temp_a2) + (temp_a1_3 * temp_a1_3)) << 0xC) >> 0xC;
            D_us_801785DC = (u16) temp_v0_4;
            if ((s16) temp_v0_4 < 0x28) {
                arg0->velocityY = -(rsin((s32) D_us_801785D8) * 8);
                arg0->velocityX = rcos((s32) D_us_801785D8) * 8;
                arg0->ext.demon.maxAngle = 0x20;
            } else if ((s16) temp_v0_4 < 0x3C) {
                arg0->velocityY = -(rsin((s32) D_us_801785D8) * 0x10);
                arg0->velocityX = rcos((s32) D_us_801785D8) * 0x10;
                arg0->ext.demon.maxAngle = 0x40;
            } else if ((s16) temp_v0_4 < 0x64) {
                arg0->velocityY = -(rsin((s32) D_us_801785D8) << 5);
                arg0->velocityX = rcos((s32) D_us_801785D8) << 5;
                arg0->ext.demon.maxAngle = 0x60;
            } else if ((s16) temp_v0_4 < 0x100) {
                arg0->velocityY = -(rsin((s32) D_us_801785D8) << 6);
                arg0->velocityX = rcos((s32) D_us_801785D8) << 6;
                arg0->ext.demon.maxAngle = 0x80;
            } else {
                arg0->ext.demon.maxAngle = 0x80;
                arg0->velocityX = (D_us_801785C4 - arg0->posX.i.hi) << 0xE;
                arg0->velocityY = (D_us_801785C8 - arg0->posY.i.hi) << 0xE;
            }
            if (arg0->velocityY > 0x10000) {
                var_a1 = 0xA;
                goto block_54;
            }
            var_a1 = 0;
            if ((s16) D_us_801785DC >= 0x3C) {
                if ((s16) D_us_801785DC >= 0x65) {
                    var_a1 = 0xB;
                    goto block_54;
                }
            } else {
block_54:
                SetAnimationFrame(arg0, var_a1);
            }
            arg0->posX.val += arg0->velocityX;
            arg0->posY.val += arg0->velocityY;
            if (g_CutsceneHasControl == 0) {
                temp_v1_2 = D_us_801785C4 - arg0->posX.i.hi;
                temp_v0_5 = D_us_801785C8 - arg0->posY.i.hi;
                D_us_801785E4 = temp_v1_2;
                D_us_801785E8 = temp_v0_5;
                temp_v0_6 = SquareRoot12(((temp_v1_2 * temp_v1_2) + (temp_v0_5 * temp_v0_5)) << 0xC) >> 0xC;
                D_us_801785EC = temp_v0_6;
                if (temp_v0_6 < 0x20) {
                    temp_v1_3 = arg0->ext.ILLEGAL.u16[8] + 1;
                    arg0->ext.ILLEGAL.u16[8] = temp_v1_3;
                    if (*g_DemonAbilityStats[s_DemonStats.level / 10] < (s16) temp_v1_3) {
                        arg0->ext.ILLEGAL.u16[8] = 0;
                        temp_v0_7 = FindValidTarget(arg0);
                        arg0->ext.ILLEGAL.u32[0xA] = temp_v0_7;
                        if (temp_v0_7 != 0) {
                            temp_v0_8 = rand();
                            var_a0 = temp_v0_8;
                            if (temp_v0_8 < 0) {
                                var_a0 = temp_v0_8 + 0xFF;
                            }
                            var_v0_3 = 0xD3;
                            if (*(&D_us_801719F0 + ((s_DemonStats.level / 10) * 0xC)) >= (temp_v0_8 - ((var_a0 >> 8) << 8))) {
                                var_v0_3 = 0xD2;
                            }
                            arg0->entityId = var_v0_3;
                            arg0->step = 0;
                        }
                    }
                }
                if (s_ServantId == 7) {
                    if ((g_CutsceneHasControl == 0) && (IsMovementAllowed(1) == 0) && (CheckAllEntitiesValid() == 0) && !(D_8003C708.flags & 0x20) && (D_us_801786D0 == 0)) {
                        temp_v0_9 = (s16) arg0->ext.ILLEGAL.u16[0x12];
                        if (temp_v0_9 < 0x4651) {
                            arg0->ext.ILLEGAL.u16[0x12] = temp_v0_9 + 1;
                        }
                    } else {
                        arg0->ext.ILLEGAL.u16[0x12] = 0;
                    }
                    if ((s16) arg0->ext.ILLEGAL.u16[0x12] == 0x4650) {
                        var_v0_4 = rand();
                        temp_v1_4 = var_v0_4;
                        var_a0_2 = 0;
                        if (temp_v1_4 < 0) {
                            var_v0_4 = temp_v1_4 + 0xFF;
                        }
                        var_v1_2 = g_Events;
loop_77:
                        if (*var_v1_2 < (temp_v1_4 - ((var_v0_4 >> 8) << 8))) {
                            var_v1_2 += 4;
                            var_a0_2 += 1;
                            goto loop_77;
                        }
                        CreateEventEntity(arg0, 0xD9, (s32) *(&D_us_80172092 + (var_a0_2 * 4)));
                    }
                }
                if (D_us_801786D0 == 2) {
                    D_us_801786D8 = 0;
                    CreateEventEntity(arg0, 0xD7, 0);
                    arg0->entityId = 0xD6;
                    arg0->step = 0;
                }
            }
            break;
    }
    ProcessEvent(arg0, false);
    unused_2DBC();
    ServantUpdateAnim(arg0, &D_us_80171FE8, g_DemonAnimationFrames);
}
// Warning: struct draculaPrimitive is not defined (only forward-declared)
// Warning: struct Primitve is not defined (only forward-declared)
//#endif

INCLUDE_ASM("servant/tt_003/nonmatchings/demon", func_us_80174FD0);

INCLUDE_ASM("servant/tt_003/nonmatchings/demon", func_us_8017540C);

void unused_5800(Entity* self) {}

void unused_5808(Entity* self) {}

INCLUDE_ASM("servant/tt_003/nonmatchings/demon", func_us_80175810);

INCLUDE_ASM("servant/tt_003/nonmatchings/demon", func_us_80175C08);

INCLUDE_ASM("servant/tt_003/nonmatchings/demon", func_us_80175D20);

void UpdateServantSfxPassthrough(Entity* self) { ProcessSfxState(self); }

void FunctionPointerPassthrough(Entity* self) {
    s_PassthroughFunctions[self->params](self);
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
