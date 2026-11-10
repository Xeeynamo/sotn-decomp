// SPDX-License-Identifier: AGPL-3.0-or-later
#include "richter.h"

// func_8016D9C4, includes part of next function
INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60B3454, func_060B3454);

// RicEntityCrashReboundStoneExplosion, split start at mid function
INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60B38FC, func_060B38FC);
// RicEntityCrashReboundStone
void RicEntityCrashReboundStone(Entity* entity) {
    switch (entity->step) {
    case 0:
        entity->flags = FLAG_UNK_20000 | FLAG_KEEP_ALIVE_OFFCAMERA;
        entity->step++;
        entity->ext.subweapon.timer = 0x14;
    case 1:
        if (--entity->ext.subweapon.timer) {
            break;
        }
    case 3:
    case 5:
        RicCreateEntFactoryFromEntity(entity, BP_57, 0);
        entity->step++;
    case 2:
    case 4:
    case 6:
        entity->ext.subweapon.timer++;
        if (entity->ext.subweapon.timer > 10) {
            entity->ext.subweapon.timer = 0;
            entity->posX.val = FIX(160.0);
            entity->posY.val = 0;
            RicCreateEntFactoryFromEntity(entity, FACTORY(BP_EMBERS, 1), 0);
            entity->step++;
        }
        break;
    case 7:
        entity->ext.subweapon.timer++;
        if (entity->ext.subweapon.timer > 15) {
            DestroyEntity(entity);
            g_Player.unk4E = 1;
            RicCreateEntFactoryFromEntity(
                entity, BP_CRASH_REBOUND_STONE_EXPLOSION, 0);
        }
        break;
    }
}

// RicEntityCrashBibleBeam
INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60B3B3C, func_060B3B3C);

// RicEntityCrashBible
INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60B40F8, func_060B40F8);

// Saturn draws the same expanding circle as RicEntitySubwpnStopwatchCircle
void func_8016F198(Entity* self) {
    s32 temp_s0_4;
    s32 sine;
    s32 cosine;
    s32 xCoord;
    s32 yCoord;
    Primitive* prim;
    s32 i;

    switch (self->step) {
    case 0:
        self->primIndex = AllocPrimitives(5, 32);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            g_Player.unk4E = 1;
            return;
        }
        self->flags = FLAG_KEEP_ALIVE_OFFCAMERA | FLAG_HAS_PRIMS;
        prim = &g_PrimBuf[self->primIndex];
        for (i = 0; i < 32; i++) {
            ((RicPrimitive*)prim)->unk6 = 0xFFFF;
            prim->priority = 0xC2;
            prim = prim->next;
        }
        self->ext.et_stopwatchCircle.size = 0x20;
        self->step++;
        break;
    case 1:
        self->ext.et_stopwatchCircle.size += 0x18;
        self->ext.et_stopwatchCircle.timer++;
        if (self->ext.et_stopwatchCircle.timer > 29) {
            self->step++;
        }
        break;
    case 2:
        g_Player.unk4E = 1;
        DestroyEntity(self);
        return;
    }
    xCoord = self->posX.i.hi;
    yCoord = self->posY.i.hi;
    prim = &g_PrimBuf[self->primIndex];
    for (i = 0; i < 32; i++) {
        sine = rsin(i * 0x80);
        cosine = rcos(i * 0x80);
        temp_s0_4 = self->ext.et_stopwatchCircle.size - 0x38;
        prim->x0 = xCoord + ((sine * self->ext.et_stopwatchCircle.size) >> 0xC);
        prim->y0 =
            yCoord - ((cosine * self->ext.et_stopwatchCircle.size) >> 0xC);
        prim->x1 = xCoord + ((sine * temp_s0_4) >> 0xC);
        prim->y1 = yCoord - ((cosine * temp_s0_4) >> 0xC);
        prim = prim->next;
    }
}

// RicEntityCrashStopwatchDoneSparkle
INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60B47EC, func_060B47EC);

// func_060B5434
void RicEntityStopwatchCrashLightning(Entity* entity) {
    switch (entity->step) {
    case 0:
        entity->flags = FLAG_KEEP_ALIVE_OFFCAMERA;
        entity->ext.subweapon.subweaponId = PL_W_30;
        RicSetSubweaponParams(entity);
        entity->hitboxWidth = 10;
        entity->hitboxHeight = 8;
        entity->step++;
        break;
    case 1:
        entity->ext.subweapon.timer++;
        if (entity->ext.subweapon.timer > 4) {
            DestroyEntity(entity);
        }
        break;
    }
}

// RicEntityCrashStopwatch
void RicEntityCrashStopwatch(Entity* self) {
    switch (self->step) {
    case 0:
        self->flags = FLAG_POS_CAMERA_LOCKED | FLAG_UNK_20000;
        self->ext.subweapon.crashIndex = 0;
        self->step_s++;
        if (self->step_s > 3) {
            self->step++;
        }
        break;
    case 1:
    case 3:
    case 5:
    case 7:
        self->ext.subweapon.crashIndex++;
        RicCreateEntFactoryFromEntity(
            self, FACTORY(BP_SUBWPN_STOPWATCH, self->ext.subweapon.crashIndex),
            0);
        self->ext.subweapon.timer = 0;
        self->step++;
        break;
    case 2:
    case 4:
    case 6:
        self->ext.subweapon.timer++;
        if (self->ext.subweapon.timer > 15) {
            self->step++;
        }
        break;
    case 8:
        DestroyEntity(self);
        break;
    }
}
s16 GetAguneaLightningAngle(s16* arg0, s32 arg1, s32 arg2, s32* arg3) {
    arg1 += MTH_GetRand() % 256 - 0x80;
    *arg3 = (MTH_GetRand() % 48) + 0x10;
    arg0[1] = arg0[0];
    arg0[3] = arg0[2];
    if (arg2) {
        // the PSX version shifts by 12
        arg0[0] += (rcos(arg1) * *arg3 * 5) >> 14;
        arg0[2] += (rsin(arg1) * *arg3) >> 12;
        if (arg2 % 2) {
            return GetAguneaLightningAngle(arg0, arg1 - 0x140, arg2 / 2, arg3);
        } else {
            MTH_GetRand();
            MTH_GetRand();
            return GetAguneaLightningAngle(
                arg0, arg1 + 0x140, (arg2 - 1) / 2, arg3);
        }
    }
    return arg1;
}

const u16 pad_60B566C[] = {0xCCCC, 0xCCCD};

// RicEntityAguneaLightning
INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60B5670, func_060B5670);

// RicEntityAguneaCircle
INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60B5AA0, func_060B5AA0);

void RicEntitySubwpnStopwatchCircle(Entity* self) {
    s16 temp_s0_4;
    s32 sine;
    s32 cosine;
    s32 xCoord;
    s32 yCoord;
    Primitive* prim;
    s32 i;

    switch (self->step) {
    case 0:
        self->primIndex = AllocPrimitives(5, 32);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags = FLAG_POS_CAMERA_LOCKED | FLAG_KEEP_ALIVE_OFFCAMERA |
                      FLAG_HAS_PRIMS | FLAG_UNK_20000;
        prim = &g_PrimBuf[self->primIndex];
        for (i = 0; i < 32; i++) {
            ((RicPrimitive*)prim)->unk6 = 0xFFFF;
            prim->priority = 0xC2;
            prim = prim->next;
        }
        self->ext.et_stopwatchCircle.size = 0x20;
        self->step++;
        break;
    case 1:
        self->ext.et_stopwatchCircle.size += 0x18;
        self->ext.et_stopwatchCircle.timer++;
        if (self->ext.et_stopwatchCircle.timer > 0x1E) {
            DestroyEntity(self);
            return;
        }
    }
    xCoord = self->posX.i.hi;
    yCoord = self->posY.i.hi;
    prim = &g_PrimBuf[self->primIndex];
    for (i = 0; i < 32; i++) {
        sine = rsin(i * 0x80);
        cosine = rcos(i * 0x80);
        temp_s0_4 = self->ext.et_stopwatchCircle.size - 0x38;
        prim->x0 = xCoord + ((sine * self->ext.et_stopwatchCircle.size) >> 0xC);
        prim->y0 =
            yCoord - ((cosine * self->ext.et_stopwatchCircle.size) >> 0xC);
        prim->x1 = xCoord + ((sine * temp_s0_4) >> 0xC);
        prim->y1 = yCoord - ((cosine * temp_s0_4) >> 0xC);
        prim = prim->next;
    }
}

// RicEntitySubwpnStopwatch
INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60B60D8, func_060B60D8);

// RicEntitySubwpnBibleTrail
INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60B7020, func_060B7020);

// RicEntitySubwpnBible
INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60B720C, func_060B720C);
