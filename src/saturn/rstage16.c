// SPDX-License-Identifier: AGPL-3.0-or-later
#include "inc_asm.h"
#include "sattypes.h"
#include "rstage16.h"

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
void func_060DC658(u16 arg0) {
    Entity* entity;
    Entity* current;
    Collider collider;

    entity = g_CurrentEntity;
    if (entity->velocityY < 0) {
        CheckCollision(
            entity->posX.val, entity->posY.val - FIX(7), &collider, 0);
        if (collider.effects & 5) {
            entity->velocityY = 0;
        }
    }

    CheckCollision(entity->posX.val, entity->posY.val + FIX(8), &collider, 0);
    if (arg0) {
        if (!(collider.effects & 5)) {
            MoveEntity(entity);
            func_06079BE4(entity);
            return;
        }

        entity->velocityX = 0;
        entity->velocityY = 0;
        if (collider.effects & 4) {
            entity->posY.val += FIX(0.125);
        } else {
            entity->posY.val += collider.unk18;
        }
        entity->posY.i.hi++;
        entity->posY.i.lo = 0;
    } else if (!(collider.effects & 5)) {
        MoveEntity(entity);
        current = g_CurrentEntity;

        if (current->velocityY >= 0) {
            current->ext.equipItemDrop.fallSpeed +=
                current->ext.equipItemDrop.gravity;
            current->velocityX = current->ext.equipItemDrop.fallSpeed;
            if (current->velocityX == FIX(1) || current->velocityX == FIX(-1)) {
                current->ext.equipItemDrop.gravity =
                    -current->ext.equipItemDrop.gravity;
            }
        }

        if (current->velocityY < FIX(0.25)) {
            current->velocityY += FIX(0.125);
        }
    }
}
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
        self->ext.subweaponCard.unk86 = 5;
        self->velocityY = -FIX(2.5);

        if (player->facingLeft != 1) {
            self->velocityX = -FIX(2.5);
            return;
        }
        self->velocityX = FIX(2.5);
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
#include "set_entity_collision_tiles.h"

const u32 DAT_060DF1D4 = 0xCCCCCCCD;
INCLUDE_ASM("asm/saturn/rstage16/f_nonmat", f60DF1D8, func_060DF1D8);
INCLUDE_ASM("asm/saturn/rstage16/f_nonmat", f60DF8AC, func_060DF8AC);
INCLUDE_ASM("asm/saturn/rstage16/f_nonmat", f60DFA14, func_060DFA14);
void func_060DFB7C(Entity* self) {
    Entity* particle;

    switch (self->step) {
    case 0:
        TekiInit(self, 2);
        self->step++;
        self->ext.explosionEmitter.parentId =
            self->ext.explosionEmitter.parent->entityId;
        /* fall through */
    case 1:
        if (self->ext.explosionEmitter.timer++ > 4U) {
            particle = AllocEntity(&g_Entities[0xE0], &g_Entities[0x100]);
            if (particle != NULL) {
                CreateEntityFromEntity(E_EXPLOSION, self, particle);
                particle->entityId = E_EXPLOSION;
                particle->pfnUpdate = func_060DF8AC;
                particle->params = self->params;
            }
            self->ext.explosionEmitter.timer = 0;
        }
        self->posX.i.hi = self->ext.explosionEmitter.parent->posX.i.hi;
        self->posY.i.hi = self->ext.explosionEmitter.parent->posY.i.hi;
        if (self->ext.explosionEmitter.parent->entityId !=
            self->ext.explosionEmitter.parentId) {
            DestroyEntity(self);
        }
        break;
    }
}
INCLUDE_ASM("asm/saturn/rstage16/f_nonmat", f60DFC68, func_060DFC68);
INCLUDE_ASM("asm/saturn/rstage16/f_nonmat", f60DFDD4, func_060DFDD4);
#define SPAWN_DESTRUCT_ANIM_ID 19
#include "spawn_destruct_anim.h"
INCLUDE_ASM("asm/saturn/rstage16/f_nonmat", f60E0024, func_060E0024);
INCLUDE_ASM("asm/saturn/rstage16/f_nonmat", f60E0104, func_060E0104);
INCLUDE_ASM("asm/saturn/rstage16/f_nonmat", f60E03F0, func_060E03F0);
INCLUDE_ASM("asm/saturn/rstage16/f_nonmat", f60E08C8, func_060E08C8);
void func_060E09D4(void) { DestroyEntity(); }
INCLUDE_ASM("asm/saturn/rstage16/f_nonmat", f60E09EC, func_060E09EC);
void func_060E16B8(void* arg0) {
    Entity* self;
    s32* state_ptr;
    u32 local[6];
    s32 state;
    s32 result;
    s32 count;
    s8 item;

    self = arg0;
    state_ptr = &self->ext.save.unk4;
    state = *state_ptr;

    if (state == 10)
        goto L_case10;
    if (state > 10) {
        if (state == 30)
            goto L_case30;
    }
    return;

L_case10_success:
    DAT_060485C0.unk5 = count;
    DAT_060485C0.unk4 = item;
    self->ext.save.unk4 = 30;
    goto L_case10_after;

L_case10:
    item = DAT_060485C0.unk4;
    count = 1;

    for (;;) {
        result = func_0600D028(item, count);
        if (result == 0 || result == 8) {
            count += 1;
            if (count > 5)
                break;
        } else {
            goto L_case10_success;
        }
    }

L_case10_after:
    if (count == 6) {
        self->step = 1;
        self->ext.save.unk4 = 41;
    }
    return;

L_case30:
    item = DAT_060485C0.unk4;
    count = DAT_060485C0.unk5;

    result = func_06030690(item, 70, local);
    if (result == 2) {
        self->ext.save.unk4 = 43;
        return;
    }

    result = func_0600D028(item, count);
    if (result == 5 && local[4] <= 0x4D) {
        self->ext.save.unk4 = 44;
        return;
    }

    if (func_0600D264(item, count) == 0 && func_0600D264(item, count) == 0 &&
        func_0600D47C(item, count) == 0) {
        self->ext.save.unk4 = 40;
    } else {
        self->ext.save.unk4 = 45;
    }
}
u16 func_060E17D0(s32 minX, s32 maxX) {
    u16 result;

    g_Player.unk7A = 1;
    if (PLAYER.step != 0 || (result = PLAYER.step_s, result != 1) ||
        PLAYER.posX.i.hi < minX || PLAYER.posX.i.hi > maxX) {
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
void func_060E5E70(Entity* entity) {
    SpriteObject* (*createSpriteObject)(u16, u16, SaturnSpriteImage*, s32);
    void (*syncSpriteObjectPos)(Entity*, s16*);
    u16* bank;
    s32 maxParts;

    switch (entity->step) {
    case 0:
        bank = &g_RStage16SpriteBankWight.flags;
        createSpriteObject = CreateSpriteObject;
        maxParts = 5;
        entity->unk0 =
            createSpriteObject(bank[-1], bank[0], DAT_060EDE4C, maxParts);
        syncSpriteObjectPos = SyncSpriteObjectPosUnchecked;
        syncSpriteObjectPos(entity, DAT_060EDA60);
        TekiInit(entity, 2);
        entity->step = 1;
        entity->hitboxState = 0;
    case 1:
        if (AnimateEntityWithSpriteData(entity, DAT_060EDA34, DAT_060EDDE4) ==
            0) {
            DestroyEntity(entity);
        }
        break;
    }
}
void func_060E5F0C(Entity* self) {
    func_06079BB4(self);
    func_0600B004(self->unk0, DAT_060EEFD0[self->animCurFrame]);
}

const u32 DAT_060E5F44 = 0xAAAAAAAB;
INCLUDE_ASM("asm/saturn/rstage16/f_nonmat", f60E5F48, func_060E5F48);
INCLUDE_ASM("asm/saturn/rstage16/f_nonmat", f60E660C, func_060E660C);
void func_060E6828(Entity* self) {
    if (self->step == 0) {
        self->unk0 = CreateSpriteObject(
            g_RStage16SpriteBankGargoyle[0].allocationIndex,
            g_RStage16SpriteBankGargoyle[0].flags, DAT_060EF0C0, 1);
        SyncSpriteObjectPosUnchecked(self, &DAT_060EDEBC);
        self->step = 1;
        TekiInit(self, 5);
        self->ext.gargoyle.clutBase = self->unk0->clutBase;

        switch (self->ext.gargoyle.variant) {
        case 1:
            self->animCurFrame = 1;
            self->unk0->clutBase = self->ext.gargoyle.clutBase;
            break;
        case 2:
            self->animCurFrame = 0x3A;
            self->unk0->clutBase = self->ext.gargoyle.clutBase + 9;
            break;
        case 0:
            self->animCurFrame = 0x3B;
            self->unk0->clutBase = self->ext.gargoyle.clutBase + 0x12;
            break;
        }

        self->unk0->zPriority -= 2;
        func_06079BB4(self);
        func_0600B004(self->unk0, DAT_060EEFD0[self->animCurFrame]);
    }
}
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
