// SPDX-License-Identifier: AGPL-3.0-or-later
#include "richter.h"

// RicEntitySubwpnReboundStone
INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60B1520, func_060B1520);

// The PSX version fades the primitive colors, here it fades its gouraud entry
static u8 PrimDecreaseBrightness(Primitive* prim, u8 amount) {
    s32 i;
    u16* colors;
    s8 r, g, b;
    u8 isEnd;
    u16 idx;

    isEnd = 0;
    idx = prim->unk1C;
    colors = ((u16(*)[4])SpGourTbl)[idx];
    for (i = 0; i < 4; i++) {
        r = colors[i] & 0x1F;
        g = (colors[i] >> 5) & 0x1F;
        b = (colors[i] >> 10) & 0x1F;
        r -= amount;
        if (r < 0) {
            r = 0;
        }
        g -= amount;
        if (g < 0) {
            g = 0;
        }
        b -= amount;
        if (b < 0) {
            b = 0;
        }
        if (r + b + g <= 2) {
            r = g = b = 1;
        } else {
            isEnd |= 1;
        }
        colors[i] = (b << 10) + (g << 5) + r + 0x8000;
    }
    return isEnd;
}

// RicEntitySubwpnAgunea
INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60B24C8, func_060B24C8);

// RicEntityAguneaHitEnemy
INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60B28E8, func_060B28E8);

extern AnimationFrame D_80155EA8[];

void RicEntityVibhutiCrashCloud(Entity* entity) {
    s32 angle;

    switch (entity->step) {
    case 0:
        entity->unk0 = CreateSpriteObject(
            g_SaturnSharedSpriteBank7Resource.allocationIndex,
            g_SaturnSharedSpriteBank7Resource.flags + 0x1C,
            g_SaturnSharedSpriteBank7Resource.images, 2);
        if (entity->unk0 == NULL) {
            DestroyEntity(entity);
            return;
        }
        entity->ext.spriteEntity.frames = g_SaturnSharedOpaquePuffFrames0;
        entity->unk0->zPriority = PLAYER.zPriority + 2;
        entity->flags = FLAG_POS_CAMERA_LOCKED | FLAG_UNK_100000;
        entity->posX.val = entity->ext.vibCrashCloud.parent->ext.vibhutiCrash.x;
        entity->posY.val = entity->ext.vibCrashCloud.parent->ext.vibhutiCrash.y;
        entity->facingLeft =
            entity->ext.vibCrashCloud.parent->ext.vibhutiCrash.facing;
        entity->ext.vibCrashCloud.subweaponId = PL_W_CRASH_VIBHUTI;
        RicSetSubweaponParams(entity);
        entity->unk56 = 0x79;
        entity->animSet = 14;
        entity->palette = 0x819E;
        entity->anim = D_80155EA8;
        entity->unk1C = 0x30;
        entity->drawFlags = ENTITY_OPACITY;
        entity->opacity = 0x60;
        entity->hitboxWidth = 10;
        entity->hitboxHeight = 8;
        angle = (MTH_GetRand() % 512) + 0x300;
        entity->velocityX = (rcos(angle) * 160) >> 2;
        entity->velocityY = -(rsin(angle) * 32);
        entity->step++;
        break;
    case 1:
        entity->ext.vibCrashCloud.unk7C++;
        if (entity->ext.vibCrashCloud.unk7C >= 39) {
            DestroyEntity(entity);
        } else {
            entity->posX.val += entity->velocityX;
            entity->posY.val += entity->velocityY;
        }
        break;
    }
}

const u16 pad_60B3070[] = {0xAAAA, 0xAAAB};

// RicEntityCrashVibhuti
INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60B3074, func_060B3074);

// func_060B33DC
void RicEntityCrashReboundStoneParticles(Entity* entity) {
    switch (entity->step) {
    case 0:
        entity->flags = FLAG_KEEP_ALIVE_OFFCAMERA;
        entity->ext.subweapon.subweaponId = PL_W_CRASH_REBOUND_STONE;
        RicSetSubweaponParams(entity);
        entity->hitboxWidth = 5; // 4 on ps1
        entity->hitboxHeight = 4;
        entity->step++;
        break;
    case 1:
        entity->ext.subweapon.timer++;
        if (entity->ext.subweapon.timer > 3) {
            DestroyEntity(entity);
        }
        break;
    }
}
