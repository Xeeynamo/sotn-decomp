// SPDX-License-Identifier: AGPL-3.0-or-later
#include "richter.h"

// RicEntityWhip
INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60B061C, func_060B061C);

extern u16 D_80175080;
extern SaturnSpriteResource g_RichterSpritePackage2Resource;
extern SaturnSpriteImage g_RichterSpritePackage2Images[];
extern SaturnSpriteFrameHeader* g_RichterSpritePackage2Frames[];
extern u16 g_RichterWhipCrouchingFramesRight[];
extern u16 g_RichterWhipCrouchingFramesLeft[];
extern u16 g_RichterWhipStandingFramesRight[];
extern u16 g_RichterWhipStandingFramesLeft[];
extern u16 g_RichterWhipAirborneFramesRight[];
extern u16 g_RichterWhipAirborneFramesLeft[];

void RicEntityArmBrandishWhip(Entity* entity) {
    if (g_Player.unk46 == 0) {
        DestroyEntity(entity);
        return;
    }
    entity->facingLeft = PLAYER.facingLeft;
    if (entity->step == 0) {
        entity->unk0 = CreateSpriteObject(
            g_RichterSpritePackage2Resource.allocationIndex,
            g_RichterSpritePackage2Resource.flags,
            g_RichterSpritePackage2Images, 1);
        if (entity->unk0 == NULL) {
            DestroyEntity(entity);
            return;
        }
        entity->ext.spriteEntity.frames = g_RichterSpritePackage2Frames;
        entity->unk0->zPriority = PLAYER.zPriority + 2;
        entity->flags =
            FLAG_UNK_20000 | FLAG_POS_PLAYER_LOCKED |
            FLAG_KEEP_ALIVE_OFFCAMERA | FLAG_UNK_10000 | FLAG_POS_CAMERA_LOCKED;
        entity->animSet = 0x8012;
        entity->unk56 = 0x46;
        entity->palette = 0x8120;
        entity->zPriority = PLAYER.zPriority + 2;
        entity->step++;
    }
    if (PLAYER.step == PL_S_CROUCH) {
        if (PLAYER.facingLeft) {
            entity->animCurFrame = g_RichterWhipCrouchingFramesLeft[D_80175080];
        } else {
            entity->animCurFrame =
                g_RichterWhipCrouchingFramesRight[D_80175080];
        }
    } else if (PLAYER.step == 0) {
        if (PLAYER.facingLeft) {
            entity->animCurFrame = g_RichterWhipStandingFramesLeft[D_80175080];
        } else {
            entity->animCurFrame = g_RichterWhipStandingFramesRight[D_80175080];
        }
    } else if (PLAYER.facingLeft) {
        entity->animCurFrame = g_RichterWhipAirborneFramesLeft[D_80175080];
    } else {
        entity->animCurFrame = g_RichterWhipAirborneFramesRight[D_80175080];
    }
    entity->posX.val = PLAYER.posX.val;
    entity->posY.val = PLAYER.posY.val;
    UpdateEntitySprite(entity);
}

void func_80167964(Entity* entity) {
    if (g_Player.unk46 == 0) {
        DestroyEntity(entity);
        return;
    }
    if (entity->step == 0) {
        entity->flags = FLAG_UNK_20000 | FLAG_POS_PLAYER_LOCKED |
                        FLAG_KEEP_ALIVE_OFFCAMERA | FLAG_UNK_10000;
        entity->step++;
    }
    if (!(entity->params & 0xFF00)) {
        g_Entities[D_80155D30[entity->poseTimer]].palette = 5;
    }
    g_Entities[D_80155D30[entity->poseTimer]].ext.whip.unkA0 = 4;
    entity->poseTimer++;
    if (entity->poseTimer == 15) {
        DestroyEntity(entity);
    }
}
