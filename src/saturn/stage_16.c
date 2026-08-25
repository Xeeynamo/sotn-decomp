// SPDX-License-Identifier: AGPL-3.0-or-later
#include "inc_asm.h"
#include "sattypes.h"
#include "stage_16.h"

#include "stage_16.h"
INCLUDE_ASM("asm/saturn/stage_16/f_nonmat", f60DC040, func_060DC040);
INCLUDE_ASM("asm/saturn/stage_16/f_nonmat", f60DC1A8, func_060DC1A8);
INCLUDE_ASM("asm/saturn/stage_16/f_nonmat", f60DC318, func_060DC318);
void func_060DC418(Entity* self) {
    SpriteObject* sprite;

    if (self->step == 0) {
        TekiInit(self, 5);
        self->step++;
        sprite = CreateSpriteObject(
            g_Stage16SpriteBank16.allocationIndex, g_Stage16SpriteBank16.flags,
            g_Stage16SpriteBank16.images, 1);
        self->unk0 = sprite;
        if (self->params == 0) {
            self->animCurFrame = 10;
        } else {
            self->animCurFrame = 5;
        }
        func_0600AFA8(sprite, g_Stage16SpriteBank16Frames[self->animCurFrame]);
        sprite->zPriority = 0x6A;
        self->step = 0x100;
        func_06079BB4(self);
    }
}
INCLUDE_ASM("asm/saturn/stage_16/f_nonmat", f60DC4C0, func_060DC4C0);
INCLUDE_ASM("asm/saturn/stage_16/f_nonmat", f60DC60C, func_060DC60C);
INCLUDE_ASM("asm/saturn/stage_16/f_nonmat", f60DC734, func_060DC734);
INCLUDE_ASM("asm/saturn/stage_16/f_nonmat", f60DC894, func_060DC894);
INCLUDE_ASM("asm/saturn/stage_16/f_nonmat", f60DC9E0, func_060DC9E0);
void func_060DCC58(void) {}

const u16 pad_060DCC62[] = {
    0x0000, 0x0415, 0x1010, 0x10FF, 0x0000, 0x0412, 0x1010, 0x10FF,
    0x0000, 0x0411, 0x1010, 0x10FF, 0x0000, 0x0417, 0x1010, 0xFF00,
    0x0009, 0x0414, 0x1010, 0xFF00, 0x0009, 0x0412, 0x1510, 0xFF00,
    0x0009, 0x0411, 0x1010, 0xFF00, 0x0009, 0x0415, 0x10FF, 0x0000,
    0x0009, 0x0412, 0x15FF, 0x0000, 0x0009, 0x0411, 0xFF00,
};
INCLUDE_ASM("asm/saturn/stage_16/f_nonmat", f60DCCB0, func_060DCCB0);
void func_060DCDBC(u16 arg0) {
    Entity* self;
    Entity* entities;
    u16 mappedId;
    s16 subweaponId;
    u8* stepPtr;
    s8 step;

    self = g_CurrentEntity;
    PlaySfx(0x67C);
    mappedId = (u16)g_Status.subWeapon;
    entities = g_Entities;
    subweaponId = DAT_060EA4B0[arg0];
    g_Status.subWeapon = (u32)subweaponId;
    if (mappedId == subweaponId) {
        mappedId = 1;
        stepPtr = self->unk6D;
        step = 0x10;
    } else {
        mappedId = DAT_060EA294[mappedId];
        stepPtr = self->unk6D;
        step = 0x60;
    }
    *stepPtr = step;
    if (mappedId != 0) {
        self->params = mappedId;
        self->posY.i.hi = entities->posY.i.hi + 0xC;
        SetStep(7);
        self->unk0->flags |= 8;
        self->ext.subweaponCard.unk86 = 5;
        self->velocityY = -FIX(2.5);
        if (entities->facingLeft != 1) {
            self->velocityX = -FIX(2.5);
            return;
        }
        self->velocityX = FIX(2.5);
    } else {
        DestroyEntity(self);
    }
}
INCLUDE_ASM("asm/saturn/stage_16/f_nonmat", f60DCE98, func_060DCE98);
INCLUDE_ASM("asm/saturn/stage_16/f_nonmat", f60DD6F4, func_060DD6F4);
INCLUDE_ASM("asm/saturn/stage_16/f_nonmat", f60DE3D4, func_060DE3D4);
INCLUDE_ASM("asm/saturn/stage_16/f_nonmat", f60DE714, func_060DE714);
INCLUDE_ASM("asm/saturn/stage_16/f_nonmat", f60DED28, func_060DED28);
INCLUDE_ASM("asm/saturn/stage_16/f_nonmat", f60DF398, func_060DF398);
INCLUDE_ASM("asm/saturn/stage_16/f_nonmat", f60DF3F0, func_060DF3F0);
void func_060DF7A8(Entity* arg0) {
    Tilemap* map;
    u8* dest;
    s16 scroll_y;
    s32 index;
    s32 i;
    s32 offset;
    s32 x;
    s32 y;

    map = &g_Tilemap;
    i = 0;
    dest = DAT_0608FFF8;
    offset = -0x18;
    do {
        x = arg0->posX.i.hi;
        y = arg0->posY.i.hi;
        index = ((x + map->scrollX.i.hi) << 2) / 5;
        scroll_y = map->scrollY.i.hi;
        index =
            (index >> 4) + (((y + offset + scroll_y) >> 4) * map->hSize * 0x10);
        dest[index] = arg0->animCurFrame != 0 ? 3 : 0;
        i += 1;
        offset += 0x10;
    } while (i <= 3);
}

const u16 pad_060DF82C[] = {0xCCCC, 0xCCCD};
INCLUDE_ASM("asm/saturn/stage_16/f_nonmat", f60DF830, func_060DF830);
INCLUDE_ASM("asm/saturn/stage_16/f_nonmat", f60DFF04, func_060DFF04);
INCLUDE_ASM("asm/saturn/stage_16/f_nonmat", f60E006C, func_060E006C);
void func_060E01D4(Entity* self) {
    Entity* entity;

    switch (self->step) {
    case 0:
        TekiInit(self, 2);
        self->step++;
        self->ext.explosionEmitter.parentId =
            self->ext.explosionEmitter.parent->entityId;
        /* fall through */
    case 1:
        if (self->ext.explosionEmitter.timer++ > 4U) {
            entity = AllocEntity(&g_Entities[0xE0], &g_Entities[0x100]);
            if (entity != NULL) {
                CreateEntityFromEntity(2, self, entity);
                entity->entityId = 2;
                entity->pfnUpdate = func_060DFF04;
                entity->params = self->params;
            }
            self->ext.explosionEmitter.timer = 0;
        }

        self->posX.i.hi = self->ext.explosionEmitter.parent->posX.i.hi;
        self->posY.i.hi = self->ext.explosionEmitter.parent->posY.i.hi;
        if (self->ext.explosionEmitter.parent->entityId !=
            self->ext.explosionEmitter.parentId) {
            ((void (*)(Entity*))DestroyEntity)(self);
        }
        break;
    }
}
INCLUDE_ASM("asm/saturn/stage_16/f_nonmat", f60E02C0, func_060E02C0);
INCLUDE_ASM("asm/saturn/stage_16/f_nonmat", f60E042C, func_060E042C);
INCLUDE_ASM("asm/saturn/stage_16/f_nonmat", f60E0560, func_060E0560);
INCLUDE_ASM("asm/saturn/stage_16/f_nonmat", f60E067C, func_060E067C);
INCLUDE_ASM("asm/saturn/stage_16/f_nonmat", f60E075C, func_060E075C);
INCLUDE_ASM("asm/saturn/stage_16/f_nonmat", f60E0A48, func_060E0A48);

void func_060E0F20(Entity* self) {
    s32 spriteFlags;
    s16 params;
    s32 flags;
    s32 frameType;
    s32 spriteSize;
    SpriteObject* sprite;
    SaturnSpriteFrameHeader** frame;
    s32 offset;
    s32 i;
    s32 count;

    if (self->step == 0) {
        params = self->params;
        flags = 3;
        spriteFlags = -0x100 & params;
        flags &= params;
        frameType = 2 & flags;
        spriteSize = 6;
        if (frameType != 0) {
            spriteSize = 18;
        }

        sprite = CreateSpriteObject(
            g_EntitySpriteBank08.allocationIndex, g_EntitySpriteBank08.flags,
            g_EntitySpriteBank08.images, spriteSize);
        self->unk0 = sprite;
        TekiInit(self, 3);

        frame = DAT_06046CD0;
        self->step++;
        if (frameType != 0) {
            frame += 2;
        } else {
            frame += 1;
        }
        func_0600AFA8(sprite, *frame);

        if (spriteFlags != 0) {
            sprite->flags |= 0x30;
        }
        sprite->flags = (sprite->flags & ~7) | 3;
        sprite->posX = self->posX.val;
        offset = 0xB0;
        sprite->posY = self->posY.val;
        if (1 & flags) {
            offset = 0xBD;
        }
        if (flags & 2) {
            count = 6;
        } else {
            count = 2;
        }

        for (i = 0; i < count; i++) {
            DAT_0608FFF8[offset] = 3;
            DAT_0608FFF8[offset + 1] = 3;
            DAT_0608FFF8[offset + 2] = 3;
            offset -= 0x10;
        }
    }
}
INCLUDE_ASM("asm/saturn/stage_16/f_nonmat", f60E102C, func_060E102C);
INCLUDE_ASM("asm/saturn/stage_16/f_nonmat", f60E1434, func_060E1434);
INCLUDE_ASM("asm/saturn/stage_16/f_nonmat", f60E17EC, func_060E17EC);
INCLUDE_ASM("asm/saturn/stage_16/f_nonmat", f60E1928, func_060E1928);
void func_060E25F4(Entity* self) {
    s32 state;
    s32 i;
    s32 result;
    s8 save_id;
    unsigned int sp[6];

    state = self->ext.save.unk4;
    if (state == 10) {
        goto state10;
    }
    if (state > 10) {
        if (state == 30) {
            goto state30;
        }
    }
    goto cleanup;

state10:
    save_id = DAT_060485C4;
    for (i = 1; i <= 5; i++) {
        result = func_0600D028(save_id, i);
        if (result != 0 && result != 8) {
            DAT_060485C0.unk5 = i;
            DAT_060485C0.unk4 = save_id;
            self->ext.save.unk4 = 30;
            break;
        }
    }
    if (i == 6) {
        self->step = 1;
        self->ext.save.unk4 = 41;
    }
    goto cleanup;

state30:
    save_id = DAT_060485C0.unk4;
    i = DAT_060485C0.unk5;
    result = func_06030690(save_id, 70, sp);
    if (result == 2) {
        self->ext.save.unk4 = 43;
    } else {
        result = func_0600D028(save_id, i);
        if (result == 5 && sp[4] <= 0x4D) {
            self->ext.save.unk4 = 44;
        } else if (
            func_0600D264(save_id, i) == 0 && func_0600D264(save_id, i) == 0 &&
            func_0600D47C(save_id, i) == 0) {
            self->ext.save.unk4 = 40;
        } else {
            self->ext.save.unk4 = 45;
        }
    }

cleanup:
    return;
}
u16 func_060E270C(s32 minX, s32 maxX) {
    u16 standing;

    g_Player.unk7A = 1;
    if (PLAYER.step != 0 || (standing = PLAYER.step_s) != 1 ||
        PLAYER.posX.i.hi < minX || PLAYER.posX.i.hi > maxX) {
        standing = 0;
    }
    return standing;
}
void func_060E2750(void) {
    g_Player.padSim = PAD_UP;
    g_Player.demo_timer = 1;
}
void func_060E2770(Entity* self) {
    Primitive* prim = self->ext.save.unk10;
    s32 i;

    for (i = 0; i < 9; i++) {
        prim->x3 = 0;
        prim->drawMode = DRAW_HIDE;
        prim = prim->next;
    }
}
INCLUDE_ASM("asm/saturn/stage_16/f_nonmat", f60E279C, func_060E279C);
void func_060E2BA0(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    func_060E2BF0(arg1, arg3);
    func_060E2DB0(arg1, arg2, arg3);
    func_060E2EFC(arg0, arg1, arg3);
}
INCLUDE_ASM("asm/saturn/stage_16/f_nonmat", f60E2BF0, func_060E2BF0);
INCLUDE_ASM("asm/saturn/stage_16/f_nonmat", f60E2DB0, func_060E2DB0);
INCLUDE_ASM("asm/saturn/stage_16/f_nonmat", f60E2EFC, func_060E2EFC);
void func_060E3200(s32 arg0, s32 arg1, s32 arg2) {
    func_060E323C(arg1, arg2);
    func_060E330C(arg0, arg1, arg2);
}
void func_060E323C(s32 scale, s32 unused) {
    s32* base;
    s32* dstY;
    s32* srcY;
    s32* dstX;
    s32* srcX;
    s32 scaledZ;
    s32 factor;
    s32 i;
    s32 last;

    base = DAT_060485e0;
    srcX = g_Stage16Entity08ModelVertices14[0];
    dstX = base;
    factor = scale << 8;
    i = 0;
    last = 13;
    srcY = srcX + 1;
    dstY = dstX + 1;
    do {
        *dstX = *srcX * factor;
        i += 1;
        dstY[0] = srcY[0] * factor;
        srcX += 3;
        scaledZ = srcY[1] * factor;
        dstX += 3;
        srcY += 3;
        dstY[1] = scaledZ;
        dstY += 3;
    } while (i <= last);

    SetCurrentMatrixBinAngle(&DAT_060EF100, &DAT_060EF110);

    DAT_06061DF0.current->val[0][0] = DAT_06061DF0.current->val[0][0] * 5 / 4;
    DAT_06061DF0.current->val[0][1] = DAT_06061DF0.current->val[0][1] * 5 / 4;
    DAT_06061DF0.current->val[0][2] = DAT_06061DF0.current->val[0][2] * 5 / 4;

    TransformAndProjectPoints(
        base, (s32*)((char*)base + 0x408), 0xE, &DAT_06061DF0);
}
INCLUDE_ASM("asm/saturn/stage_16/f_nonmat", f60E330C, func_060E330C);
INCLUDE_ASM("asm/saturn/stage_16/f_nonmat", f60E3478, func_060E3478);
INCLUDE_ASM("asm/saturn/stage_16/f_nonmat", f60E34CC, func_060E34CC);
INCLUDE_ASM("asm/saturn/stage_16/f_nonmat", f60E3D00, func_060E3D00);
INCLUDE_ASM("asm/saturn/stage_16/f_nonmat", f60E3FC8, func_060E3FC8);
void func_060E401C(Entity* self) {
    if (g_Player.status & 0x1C00) {
        if ((s16)GetDistanceToPlayerX(self) > 0x48 && (Random() & 1)) {
            SetStep(9);
        }
    } else if (--self->ext.et_060E401C.timer == 0) {
        SetStep(g_Stage16Entity20Steps[self->ext.et_060E401C.stepIndex++ & 7]);
        self->ext.et_060E401C.timer = g_Stage16Entity20StepDelays[Random() & 3];
        if (self->params != 0 && (s16)GetDistanceToPlayerX(self) > 0x50 &&
            (Random() & 1)) {
            SetStep(11);
        }
        self->velocityX = 0;
    }
}
s32 GetDistanceToPlayerY(Entity* self);

void func_060E40F4(Entity* self) {
    s16 dist = GetDistanceToPlayerY(self);

    if (dist > 0x40) {
        SetStep(3);
    }
}
void func_060E411C(Entity* self, u8 arg1) {
    s32 velocityX;

    if ((AnimateEntityWithSpriteData(
             self, DAT_060EB46C[arg1], g_Stage16SpriteBank21Frames) &
         0x80) &&
        self->step == 7) {
        if (self->pose != 3) {
            if (self->ext.et_060E411C.facingLatch != self->facingLeft) {
                self->velocityX = -self->velocityX;
            }
            self->ext.et_060E411C.facingLatch = self->facingLeft;
        }
    }

    velocityX = self->velocityX;
    if (self->pose >= DAT_060EB38C[arg1]) {
        if (velocityX != 0) {
            if (self->ext.et_060E411C.facingLatch != 0) {
                velocityX += DAT_060EB394[arg1];
            } else {
                velocityX -= DAT_060EB394[arg1];
            }
        }
    } else if (self->ext.et_060E411C.facingLatch != 0) {
        velocityX -= DAT_060EB394[arg1];
    } else {
        velocityX += DAT_060EB394[arg1];
    }

    self->velocityX = velocityX;
    if ((func_06079DEC(self, DAT_060EB47C) & 0x60) == 0x60) {
        self->posX.val -= velocityX;
    }
}
INCLUDE_ASM("asm/saturn/stage_16/f_nonmat", f60E4210, func_060E4210);
INCLUDE_ASM("asm/saturn/stage_16/f_nonmat", f60E49F0, func_060E49F0);
INCLUDE_ASM("asm/saturn/stage_16/f_nonmat", f60E4AEC, func_060E4AEC);
void func_060E4C74(Entity* self) {
    SaturnSpriteImage* images = g_Stage16SpriteBank22Images;
    SaturnSpriteResource* bank =
        (SaturnSpriteResource*)g_Stage16SpriteBankSkeletonBeast;

    self->unk0 =
        CreateSpriteObject(bank->allocationIndex, bank->flags, images, 5);

    self->ext.spriteAnimEnemy.frames = g_Stage16SpriteBank22Frames;
    self->ext.spriteAnimEnemy.animations = g_Stage16SkeletonBeastAnimations;
    self->ext.spriteAnimEnemy.unk80 = 0;
    self->ext.spriteAnimEnemy.unk81 = 0;
    self->ext.spriteAnimEnemy.unk82 = 0;

    SyncSpriteObjectPosUnchecked(self, DAT_060EC690);
    self->step++;
}
INCLUDE_ASM("asm/saturn/stage_16/f_nonmat", f60E4CF4, func_060E4CF4);
INCLUDE_ASM("asm/saturn/stage_16/f_nonmat", f60E5258, func_060E5258);
INCLUDE_ASM("asm/saturn/stage_16/f_nonmat", f60E53E0, func_060E53E0);
void func_060E558C(Entity* entity, s16 step) {
    entity->pose = 0;
    entity->poseTimer = 0;
    entity->step = step;
    entity->step_s = 0;
}

const u16 DAT_060E55AC = 0x8888;
const u16 DAT_060E55AE = 0x8889;
INCLUDE_ASM("asm/saturn/stage_16/f_nonmat", f60E55B0, func_060E55B0);
INCLUDE_ASM("asm/saturn/stage_16/f_nonmat", f60E636C, func_060E636C);
INCLUDE_ASM("asm/saturn/stage_16/f_nonmat", f60E63A8, func_060E63A8);
INCLUDE_ASM("asm/saturn/stage_16/f_nonmat", f60E6A6C, func_060E6A6C);
INCLUDE_ASM("asm/saturn/stage_16/f_nonmat", f60E6C88, func_060E6C88);
void func_060E6D90(Entity* entity, s16 step) {
    entity->velocityX = 0;
    entity->velocityY = 0;
    entity->pose = 0;
    entity->poseTimer = 0;
    entity->step = step;
    entity->step_s = 0;
}
s32 func_060E6DB8(Entity* self, Entity* other) {
    s32 result;

    result = 0;
    if (self->posX.val > other->posX.val) {
        result = 1;
    }
    if (self->posY.val > other->posY.val) {
        result |= 2;
    }
    return result;
}

const u16 DAT_060E6DD8 = 0x8888;
const u16 DAT_060E6DDA = 0x8889;
INCLUDE_ASM("asm/saturn/stage_16/f_nonmat", f60E6DDC, func_060E6DDC);
INCLUDE_ASM("asm/saturn/stage_16/f_nonmat", f60E72FC, func_060E72FC);
INCLUDE_ASM("asm/saturn/stage_16/f_nonmat", f60E73FC, func_060E73FC);
INCLUDE_ASM("asm/saturn/stage_16/f_nonmat", f60E7C60, func_060E7C60);
void func_060E7EA8(Entity* entity, s16 step) {
    entity->velocityX = 0;
    entity->velocityY = 0;
    entity->pose = 0;
    entity->poseTimer = 0;
    entity->step = step;
    entity->step_s = 0;
}
INCLUDE_ASM("asm/saturn/stage_16/f_nonmat", f60E7ED0, func_060E7ED0);
INCLUDE_ASM("asm/saturn/stage_16/f_nonmat", f60E7FC4, func_060E7FC4);
INCLUDE_ASM("asm/saturn/stage_16/f_nonmat", f60E86BC, func_060E86BC);
INCLUDE_ASM("asm/saturn/stage_16/f_nonmat", f60E887C, func_060E887C);
INCLUDE_ASM("asm/saturn/stage_16/f_nonmat", f60E8AC0, func_060E8AC0);
