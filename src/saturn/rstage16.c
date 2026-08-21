// SPDX-License-Identifier: AGPL-3.0-or-later
#include "inc_asm.h"
#include "sattypes.h"

#include "rstage16.h"

INCLUDE_ASM("asm/saturn/rstage16/f_nonmat", f60DC040, func_060DC040);
INCLUDE_ASM("asm/saturn/rstage16/f_nonmat", f60DC1A8, func_060DC1A8);
INCLUDE_ASM("asm/saturn/rstage16/f_nonmat", f60DC318, func_060DC318);
void func_060DC418(Entity* self) {
    SpriteObject* sprite;

    if (self->step == 0) {
        TekiInit(self, 5);
        self->step++;
        sprite = CreateSpriteObject(
            g_RStage16SpriteBank16.allocationIndex,
            g_RStage16SpriteBank16.flags, g_RStage16SpriteBank16.images, 1);
        self->unk0 = sprite;
        if (self->params == 0) {
            self->animCurFrame = 10;
        } else {
            self->animCurFrame = 5;
        }
        func_0600AFA8(sprite, DAT_060E8898[self->animCurFrame]);
        sprite->zPriority = 0x6A;
        self->step = 0x100;
        func_06079BB4(self);
    }
}
INCLUDE_ASM("asm/saturn/rstage16/f_nonmat", f60DC4C0, func_060DC4C0);
INCLUDE_ASM("asm/saturn/rstage16/f_nonmat", f60DC658, func_060DC658);
void func_060DC764(u16 cardIndex) {
    Entity* self;
    Entity* player;
    PlayerStatus* status;
    s16 subWeaponId;
    u16 params;

    self = g_CurrentEntity;
    PlaySfx(0x67C);

    status = &g_Status;
    params = status->subWeapon;
    player = g_Entities;
    subWeaponId = DAT_060E9CFC[cardIndex];
    status->subWeapon = subWeaponId;

    if (params == subWeaponId) {
        params = 1;
        self->unk6D[0] = 0x10;
    } else {
        params = DAT_060E9AE0[params];
        self->unk6D[0] = 0x60;
    }

    if (params != 0) {
        self->params = params;
        self->posY.i.hi = player->posY.i.hi + 0xC;
        SetStep(7);
        self->unk0->flags |= 8;
        self->ext.ILLEGAL.u16[7] = 5;
        self->velocityY = -0x28000;

        if (player->facingLeft != 1) {
            self->velocityX = -0x28000;
            return;
        }
        self->velocityX = 0x28000;
    } else {
        DestroyEntity(self);
    }
}
INCLUDE_ASM("asm/saturn/rstage16/f_nonmat", f60DC840, func_060DC840);
INCLUDE_ASM("asm/saturn/rstage16/f_nonmat", f60DD09C, func_060DD09C);
INCLUDE_ASM("asm/saturn/rstage16/f_nonmat", f60DDD7C, func_060DDD7C);
INCLUDE_ASM("asm/saturn/rstage16/f_nonmat", f60DE0BC, func_060DE0BC);
INCLUDE_ASM("asm/saturn/rstage16/f_nonmat", f60DE6D0, func_060DE6D0);
INCLUDE_ASM("asm/saturn/rstage16/f_nonmat", f60DED40, func_060DED40);
INCLUDE_ASM("asm/saturn/rstage16/f_nonmat", f60DED98, func_060DED98);
INCLUDE_ASM("asm/saturn/rstage16/f_nonmat", f60DF150, func_060DF150);
INCLUDE_ASM("asm/saturn/rstage16/f_nonmat", f60DF1D8, func_060DF1D8);
INCLUDE_ASM("asm/saturn/rstage16/f_nonmat", f60DF8AC, func_060DF8AC);
INCLUDE_ASM("asm/saturn/rstage16/f_nonmat", f60DFA14, func_060DFA14);
void func_060DFB7C(Entity* self) {
    Entity* particle;

    switch (self->step) {
    case 0:
        TekiInit(self, 2);
        self->step++;
        self->ext.ILLEGAL.u16[8] =
            ((Entity*)self->ext.ILLEGAL.u32[1])->entityId;
        /* fall through */
    case 1:
        if (self->ext.ILLEGAL.u8[0]++ > 4U) {
            particle = AllocEntity(&g_Entities[0xE0], &DAT_060A4FF8);
            if (particle != NULL) {
                CreateEntityFromEntity(2, self, particle);
                particle->entityId = 2;
                particle->pfnUpdate = func_060DF8AC;
                particle->params = self->params;
            }
            self->ext.ILLEGAL.u8[0] = 0;
        }
        self->posX.i.hi = ((Entity*)self->ext.ILLEGAL.u32[1])->posX.i.hi;
        self->posY.i.hi = ((Entity*)self->ext.ILLEGAL.u32[1])->posY.i.hi;
        if (((Entity*)self->ext.ILLEGAL.u32[1])->entityId !=
            self->ext.ILLEGAL.u16[8]) {
            DestroyEntity(self);
        }
        break;
    }
}
INCLUDE_ASM("asm/saturn/rstage16/f_nonmat", f60DFC68, func_060DFC68);
INCLUDE_ASM("asm/saturn/rstage16/f_nonmat", f60DFDD4, func_060DFDD4);
INCLUDE_ASM("asm/saturn/rstage16/f_nonmat", f60DFF08, func_060DFF08);
INCLUDE_ASM("asm/saturn/rstage16/f_nonmat", f60E0024, func_060E0024);
INCLUDE_ASM("asm/saturn/rstage16/f_nonmat", f60E0104, func_060E0104);
INCLUDE_ASM("asm/saturn/rstage16/f_nonmat", f60E03F0, func_060E03F0);
INCLUDE_ASM("asm/saturn/rstage16/f_nonmat", f60E08C8, func_060E08C8);
void func_060E09D4(void) { DestroyEntity(); }
INCLUDE_ASM("asm/saturn/rstage16/f_nonmat", f60E09EC, func_060E09EC);
INCLUDE_ASM("asm/saturn/rstage16/f_nonmat", f60E16B8, func_060E16B8);
u16 func_060E17D0(s32 minX, s32 maxX) {
    u16 result;

    g_Player.unk7A = 1;
    if ((u16)(s16)g_Entities->step != 0 ||
        (result = (u16)(s16)g_Entities->step_s, result != 1) ||
        g_Entities->posX.i.hi < minX || g_Entities->posX.i.hi > maxX) {
        result = 0;
    }
    return result;
}
void func_060E1814(void) {
    g_Player.padSim = PAD_UP;
    g_Player.demo_timer = 1;
}
void func_060E1834(Entity* self) {
    Primitive* prim = self->ext.save.unk10;
    s32 i;

    for (i = 0; i < 9; i++) {
        prim->x3 = 0;
        prim->drawMode = DRAW_HIDE;
        prim = prim->next;
    }
}
INCLUDE_ASM("asm/saturn/rstage16/f_nonmat", f60E1860, func_060E1860);
void func_060E1C64(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    func_060E1CB4(arg1, arg3);
    func_060E1E74(arg1, arg2, arg3);
    func_060E1FC0(arg0, arg1, arg3);
}
INCLUDE_ASM("asm/saturn/rstage16/f_nonmat", f60E1CB4, func_060E1CB4);
INCLUDE_ASM("asm/saturn/rstage16/f_nonmat", f60E1E74, func_060E1E74);
INCLUDE_ASM("asm/saturn/rstage16/f_nonmat", f60E1FC0, func_060E1FC0);
void func_060E22C4(s32 arg0, s32 arg1, s32 arg2) {
    func_060E2300(arg1, arg2);
    func_060E23D0(arg0, arg1, arg2);
}
void func_060E2300(s32 scale, s32 unused) {
    s32* base;
    s32* srcX;
    s32* dstX;
    s32* srcY;
    s32* dstY;
    s32 factor;
    s32 scaledZ;
    s32 i;
    s32 last;

    base = DAT_060485e0;
    srcX = DAT_060EA000;
    dstX = base;
    factor = scale << 8;
    i = 0;
    last = 13;
    srcY = srcX + 1;
    dstY = dstX + 1;
    do {
        *dstX = *srcX * factor;
        i++;
        dstY[0] = srcY[0] * factor;
        srcX += 3;
        scaledZ = srcY[1] * factor;
        dstX += 3;
        srcY += 3;
        dstY[1] = scaledZ;
        dstY += 3;
    } while (i <= last);

    SetCurrentMatrixBinAngle(DAT_060EFCC0, DAT_060EFCD0);

    DAT_06061DF0.current->val[0][0] = DAT_06061DF0.current->val[0][0] * 5 / 4;
    DAT_06061DF0.current->val[0][1] = DAT_06061DF0.current->val[0][1] * 5 / 4;
    DAT_06061DF0.current->val[0][2] = DAT_06061DF0.current->val[0][2] * 5 / 4;

    TransformAndProjectPoints(
        base, (s32*)((char*)base + 0x408), 0xE, &DAT_06061DF0);
}
INCLUDE_ASM("asm/saturn/rstage16/f_nonmat", f60E23D0, func_060E23D0);
INCLUDE_ASM("asm/saturn/rstage16/f_nonmat", f60E253C, func_060E253C);
INCLUDE_ASM("asm/saturn/rstage16/f_nonmat", f60E3244, func_060E3244);
INCLUDE_ASM("asm/saturn/rstage16/f_nonmat", f60E3438, func_060E3438);
void func_060E35E0(Entity* entity, s16 step) {
    entity->pose = 0;
    entity->poseTimer = 0;
    entity->step = step;
    entity->step_s = 0;
}

const u16 DAT_060E3600[] = {0x8888, 0x8889, 0xAAAA, 0xAAAB};
INCLUDE_ASM("asm/saturn/rstage16/f_nonmat", f60E3608, func_060E3608);
INCLUDE_ASM("asm/saturn/rstage16/f_nonmat", f60E4664, func_060E4664);
INCLUDE_ASM("asm/saturn/rstage16/f_nonmat", f60E4804, func_060E4804);
INCLUDE_ASM("asm/saturn/rstage16/f_nonmat", f60E4AFC, func_060E4AFC);
void func_060E4E50(Entity* entity) {
    entity->unk0 =
        CreateSpriteObject(g_RStage16SpriteBankWight.allocationIndex,
                           g_RStage16SpriteBankWight.flags, DAT_060EDE4C, 5);
    SyncSpriteObjectPosUnchecked(entity, DAT_060ED9FA);
    entity->step++;
}
void func_060E4EA4(Entity* self) {
    func_06079BB4(self);
    func_0600B004(self->unk0, DAT_060EDDE4[self->animCurFrame]);
}
INCLUDE_ASM("asm/saturn/rstage16/f_nonmat", f60E4EDC, func_060E4EDC);
INCLUDE_ASM("asm/saturn/rstage16/f_nonmat", f60E56DC, func_060E56DC);
INCLUDE_ASM("asm/saturn/rstage16/f_nonmat", f60E5CB0, func_060E5CB0);
INCLUDE_ASM("asm/saturn/rstage16/f_nonmat", f60E5E70, func_060E5E70);
void func_060E5F0C(Entity* self) {
    func_06079BB4(self);
    func_0600B004(self->unk0, DAT_060EEFD0[self->animCurFrame]);
}

const u32 DAT_060E5F44 = 0xAAAAAAAB;
INCLUDE_ASM("asm/saturn/rstage16/f_nonmat", f60E5F48, func_060E5F48);
INCLUDE_ASM("asm/saturn/rstage16/f_nonmat", f60E660C, func_060E660C);
INCLUDE_ASM("asm/saturn/rstage16/f_nonmat", f60E6828, func_060E6828);
void func_060E6930(Entity* self) {
    u8 sensorHit;
    u16 collision;

    sensorHit = func_06079DEC(self, &DAT_060EF2B4);
    collision = func_06079F60(self, &DAT_060EF2BC, 3);
    if (sensorHit == 0x80 || (collision & 2)) {
        SetStep(5);
        return;
    }
    if (self->ext.afterImage.disableFlag == 0) {
        SetStep(4);
        return;
    }
    self->ext.afterImage.disableFlag--;
}
INCLUDE_ASM("asm/saturn/rstage16/f_nonmat", f60E69A4, func_060E69A4);
INCLUDE_ASM("asm/saturn/rstage16/f_nonmat", f60E6F38, func_060E6F38);
INCLUDE_ASM("asm/saturn/rstage16/f_nonmat", f60E70A0, func_060E70A0);
void func_060E7338(MthXyz* rotation, MthXyz* position) {
    MthMatrix* current;
    s32 angle;

    MTH_ClearMatrix(&DAT_06061DF0);
    current = DAT_06061DF0.current;
    current->val[0][3] = position->x;
    current->val[1][3] = position->y;
    current->val[2][3] = position->z;

    angle = rotation->y & 0x0FFF;
    if (angle != 0) {
        angle = (angle << 12) + (angle << 10) + (angle << 9) + (angle << 7);
        if (angle > 0xB3FFFF) {
            angle += 0xFE980000;
        }
        MTH_RotateMatrixY(&DAT_06061DF0, angle);
    }

    angle = rotation->z & 0x0FFF;
    if (angle != 0) {
        angle = (angle << 12) + (angle << 10) + (angle << 9) + (angle << 7);
        if (angle > 0xB3FFFF) {
            angle += 0xFE980000;
        }
        MTH_RotateMatrixZ(&DAT_06061DF0, angle);
    }
}
INCLUDE_ASM("asm/saturn/rstage16/f_nonmat", f60E7400, func_060E7400);
INCLUDE_ASM("asm/saturn/rstage16/f_nonmat", f60E7698, func_060E7698);
INCLUDE_ASM("asm/saturn/rstage16/f_nonmat", f60E7C60, func_060E7C60);
INCLUDE_ASM("asm/saturn/rstage16/f_nonmat", f60E7DB8, func_060E7DB8);
INCLUDE_ASM("asm/saturn/rstage16/f_nonmat", f60E81F4, func_060E81F4);
INCLUDE_ASM("asm/saturn/rstage16/f_nonmat", f60E8368, func_060E8368);
