// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "servant.h"
#include "sfx.h"

typedef enum { 
    DEMON_MODE_DEFAULT_UPDATE = ENTITY_ID_SERVANT,
    DEMON_MODE_UNK_D2,
    DEMON_MODE_UNK_D3,
    DEMON_MODE_UNK_D4,
    DEMON_MODE_UNK_D5,
    DEMON_MODE_UNK_D6,
    DEMON_SUBENTITY_UNK_D7,
    DEMON_MODE_UNK_D8,
    DEMON_EVENT_SFX_PASSTHROUGH,
} EntityIds;

extern s32 s_TargetMatch[0x80];
extern s32 g_DemonAbilityStats[10][6];
extern FamiliarStats s_DemonStats;
extern s32 s_LastTargetedEntityIndex;
extern AnimationFrame* g_DemonAnimationFrames[];
extern s32 s_ServantId;
extern u16 g_DemonClut[64];
extern SpriteParts* g_DemonSpriteParts[];
extern s32 D_us_801786D0;
extern s32 D_us_801786D4;
extern s8 D_us_80171FE8;
extern s32 s_TargetLocationX;
extern s32 s_TargetLocationY;
extern s16 s_TargetLocationX_calc;
extern s16 s_TargetLocationY_calc;
extern s16 s_AngleToTarget;
extern s16 s_AllowedAngle;
extern s16 s_DistToTargetLocation;
extern s16 s_TargetLocOffset_calc;
extern s32 s_DeltaX;
extern s32 s_DeltaY;
extern s32 s_DistToTargetLocation2;
extern s32 D_us_801786D8;

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

void unused_2DBC(Entity* self) {}

// This is likey the analog to Faerie.ExecuteAbilityInitialize
void func_us_80172DC4(Entity* self) {
    if (!self->ext.demon.isAbilityInitialized) {
        if ((self->entityId == DEMON_MODE_DEFAULT_UPDATE) || (self->entityId == DEMON_MODE_UNK_D8)) {
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
        case DEMON_MODE_DEFAULT_UPDATE:
        case DEMON_MODE_UNK_D2:
        case DEMON_MODE_UNK_D3:
        case DEMON_MODE_UNK_D6:
        case DEMON_MODE_UNK_D8:
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
            entity->entityId = DEMON_MODE_DEFAULT_UPDATE;
        } else {
            entity->entityId = DEMON_MODE_UNK_D8;
        }
        entity->posX.val = FIX(128);
        entity->posY.val = FIX(-32);
    } else {
        entity->entityId = DEMON_MODE_DEFAULT_UPDATE;
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

void UpdateServantDefault(Entity* self)
{
    s32 temp;
    s32 i;
    s32 rnd;

    g_api.GetServantStats(self, 0, 0, &s_DemonStats);
    if (D_us_801786D4) {
        self->zPriority = PLAYER.zPriority - 2;
    }
    
    if (D_8003C708.flags & 0x20) {
        switch (ServantUnk0()) {  
            case 0:
                s_TargetLocationX = 0x40;
                break;
            case 1:
                s_TargetLocationX = 0xC0;
                break;
            case 2:
                
                if (self->posX.i.hi > 0x80) {
                    temp = 0xC0;
                }
                else
                {
                    temp = 0x40;
                }
                s_TargetLocationX = temp;
                break;
        }
        s_TargetLocationY = 0xA0;
    } else {
        s_TargetLocOffset_calc = -0x18;
        if (PLAYER.facingLeft) {
            s_TargetLocOffset_calc = -s_TargetLocOffset_calc;
        }
        s_TargetLocationX_calc =  g_Entities->posX.i.hi + s_TargetLocOffset_calc;
        s_TargetLocationY_calc = PLAYER.posY.i.hi - 0x20;
        
        s_AngleToTarget = self->ext.demon.randomMovementAngle;
        self->ext.demon.randomMovementAngle += 0x10;
        self->ext.demon.randomMovementAngle &= 0xFFF;
        s_DistToTargetLocation = self->ext.demon.defaultDistToTargetLoc;
        
        s_TargetLocationX =
            s_TargetLocationX_calc +
            ((rcos(s_AngleToTarget / 2) * s_DistToTargetLocation) >> 0xC);
        s_TargetLocationY =
            s_TargetLocationY_calc -
            ((rsin(s_AngleToTarget) * (s_DistToTargetLocation / 2)) >> 0xC);
    }
    switch (self->step) { 
        case 0:
            func_us_80172DC4(self);
            break;
        case 1: 
            if (D_8003C708.flags & 0x20) {
                if (PLAYER.posX.i.hi >= self->posX.i.hi) {
                    self->facingLeft = 0;
                } else {
                    self->facingLeft = 1;
                }
            } else { 
                if (PLAYER.facingLeft != self->facingLeft) {
                    if (abs(s_TargetLocationX - self->posX.i.hi) <= 0) {
                        self->facingLeft = PLAYER.facingLeft;
                    } else if (!self->facingLeft && s_TargetLocationX < self->posX.i.hi) { 
                            self->facingLeft = PLAYER.facingLeft;
                    } else if (self->facingLeft && s_TargetLocationX > self->posX.i.hi) { 
                        self->facingLeft = PLAYER.facingLeft;
                    }
                } 
                else if (!self->facingLeft && (self->posX.i.hi - s_TargetLocationX) > 0x28) { 
                    self->facingLeft = PLAYER.facingLeft ? 0 : 1;
                } else if (self->facingLeft && (s_TargetLocationX - self->posX.i.hi) > 0x28) 
                { 
                    self->facingLeft = PLAYER.facingLeft ? 0 : 1;
                }
            }
            
            s_AngleToTarget = CalculateAngleToEntity(self, s_TargetLocationX, s_TargetLocationY);
            s_AllowedAngle = GetTargetPositionWithDistanceBuffer(s_AngleToTarget, self->ext.demon.targetAngle, self->ext.demon.maxAngle);
            self->ext.demon.targetAngle = s_AllowedAngle;
            s_TargetLocationX_calc =  s_TargetLocationX - self->posX.i.hi;
            s_TargetLocationY_calc =  s_TargetLocationY - self->posY.i.hi;
            s_DistToTargetLocation = SquareRoot12(((s_TargetLocationX_calc * s_TargetLocationX_calc) + (s_TargetLocationY_calc * s_TargetLocationY_calc)) << 0xC) >> 0xC;
            if (s_DistToTargetLocation < 0x28) {
                self->velocityY = -(rsin((s32) s_AllowedAngle) * 8);
                self->velocityX = rcos((s32) s_AllowedAngle) * 8;
                self->ext.demon.maxAngle = 0x20;
            } else if (s_DistToTargetLocation < 0x3C) {
                self->velocityY = -(rsin((s32) s_AllowedAngle) * 0x10);
                self->velocityX = rcos((s32) s_AllowedAngle) * 0x10;
                self->ext.demon.maxAngle = 0x40;
            } else if (s_DistToTargetLocation < 0x64) {
                self->velocityY = -(rsin((s32) s_AllowedAngle) << 5);
                self->velocityX = rcos((s32) s_AllowedAngle) << 5;
                self->ext.demon.maxAngle = 0x60;
            } else if (s_DistToTargetLocation < 0x100) {
                self->velocityY = -(rsin((s32) s_AllowedAngle) << 6);
                self->velocityX = rcos((s32) s_AllowedAngle) << 6;
                self->ext.demon.maxAngle = 0x80;
            } else {
                self->velocityX = (s_TargetLocationX - self->posX.i.hi) << 0xE;
                self->velocityY = (s_TargetLocationY - self->posY.i.hi) << 0xE;
                self->ext.demon.maxAngle = 0x80;
            }
            if (self->velocityY > 0x10000) {
                SetAnimationFrame(self, 0xA);
            }
            else if (s_DistToTargetLocation < 0x3C) {
                SetAnimationFrame(self, 0);
            
            } else if ( s_DistToTargetLocation > 0x64) {
                SetAnimationFrame(self, 0xB);
            }
            self->posX.val += self->velocityX;
            self->posY.val += self->velocityY;
            if (!g_CutsceneHasControl) {
                s_DeltaX = s_TargetLocationX - self->posX.i.hi;
                s_DeltaY = s_TargetLocationY - self->posY.i.hi;
                
                s_DistToTargetLocation2 = SquareRoot12(((s_DeltaX * s_DeltaX) + (s_DeltaY * s_DeltaY)) << 0xC) >> 0xC;
                
                if (s_DistToTargetLocation2 < 0x20) {
                    self->ext.ILLEGAL.s16[8]++;
                    if (self->ext.ILLEGAL.s16[8] > g_DemonAbilityStats[s_DemonStats.level / 10][0]) {
                        self->ext.ILLEGAL.s16[8] = 0;
                        
                        if (self->ext.demon.target = FindValidTarget(self)) {
                            if (rand() % 0x100 <= g_DemonAbilityStats[s_DemonStats.level / 10][0]) {
                                self->entityId = DEMON_MODE_UNK_D2;
                            }
                            else
                            {
                                self->entityId = DEMON_MODE_UNK_D3;
                            }
                            self->step = 0;
                        }
                    }
                }
                // This is likely dead code and not actually valid as it's doing some weird stuff with
                // g_Events that doesn't make any sense.  And it only does it with the N Demon, which
                // was stripped out anyway
                if (s_ServantId == 7) {
                    if (!g_CutsceneHasControl && !IsMovementAllowed(1) && !CheckAllEntitiesValid() && 
                            !(D_8003C708.flags & 0x20) && !D_us_801786D0) {
                        if (self->ext.ILLEGAL.s16[0x12] < 0x4651) {
                            self->ext.ILLEGAL.s16[0x12]++;
                        }
                    } else {
                        self->ext.ILLEGAL.s16[0x12] = 0;
                    }
                    if (self->ext.ILLEGAL.s16[0x12] == 0x4650) {

                        for(rnd = rand() % 0x100, i = 0; true; i++ )
                        { 
                            if(rnd <= ((s16*)g_Events)[i* 2])
                            {
                                CreateEventEntity(self, DEMON_EVENT_SFX_PASSTHROUGH, ((s16*)g_Events)[i*2 +1]);
                                break;
                            }
                        } 
                    }
                }
                if (D_us_801786D0 == 2) {
                    D_us_801786D8 = 0;
                    CreateEventEntity(self, DEMON_SUBENTITY_UNK_D7, 0);
                    self->entityId = DEMON_MODE_UNK_D6;
                    self->step = 0;
                }
            }
            break;
    }
    ProcessEvent(self, false);
    unused_2DBC(self);
    ServantUpdateAnim(self, &D_us_80171FE8, g_DemonAnimationFrames);
}

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
