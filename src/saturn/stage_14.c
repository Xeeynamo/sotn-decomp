// SPDX-License-Identifier: AGPL-3.0-or-later
#include "inc_asm.h"
#include "sattypes.h"
#include "stage_14.h"

INCLUDE_ASM("asm/saturn/stage_14/f_nonmat", f60DC040, func_060DC040);
INCLUDE_ASM("asm/saturn/stage_14/f_nonmat", f60DC06C, func_060DC06C);
INCLUDE_ASM("asm/saturn/stage_14/f_nonmat", f60DC5A0, func_060DC5A0);
INCLUDE_ASM("asm/saturn/stage_14/f_nonmat", f60DC66C, func_060DC66C);
void func_060DC908(void) {}
void func_060DC914(void) {}
INCLUDE_ASM("asm/saturn/stage_14/f_nonmat", f60DC920, func_060DC920);
INCLUDE_ASM("asm/saturn/stage_14/f_nonmat", f60DD454, func_060DD454);
void func_060DD65C(void) {}
INCLUDE_ASM("asm/saturn/stage_14/f_nonmat", f60DD668, func_060DD668);
INCLUDE_ASM("asm/saturn/stage_14/f_nonmat", f60DD708, func_060DD708);
INCLUDE_ASM("asm/saturn/stage_14/f_nonmat", f60DD960, func_060DD960);
INCLUDE_ASM("asm/saturn/stage_14/f_nonmat", f60DD980, func_060DD980);
INCLUDE_ASM("asm/saturn/stage_14/f_nonmat", f60DDB20, func_060DDB20);
INCLUDE_ASM("asm/saturn/stage_14/f_nonmat", f60DDC64, func_060DDC64);
INCLUDE_ASM("asm/saturn/stage_14/f_nonmat", f60DE578, func_060DE578);
INCLUDE_ASM("asm/saturn/stage_14/f_nonmat", f60DE850, func_060DE850);
INCLUDE_ASM("asm/saturn/stage_14/f_nonmat", f60DE970, func_060DE970);
INCLUDE_ASM("asm/saturn/stage_14/f_nonmat", f60DEAE4, func_060DEAE4);
void func_060DEC10(u16 arg0) {
    Collider collider;
    Entity* self = g_CurrentEntity;
    Entity* current;

    if (self->velocityY < 0) {
        CheckCollision(self->posX.val, self->posY.val - FIX(7), &collider, 0);
        if (collider.effects & 5) {
            self->velocityY = 0;
        }
    }

    CheckCollision(self->posX.val, self->posY.val + FIX(8), &collider, 0);

    if (arg0) {
        if (!(collider.effects & 5)) {
            MoveEntity(self);
            FallEntity(self);
            return;
        }

        self->velocityX = 0;
        self->velocityY = 0;
        if (collider.effects & 4) {
            self->posY.val += FIX(0.125);
        } else {
            self->posY.val += collider.unk18;
        }
        self->posY.i.hi++;
        self->posY.i.lo = 0;
    } else if (!(collider.effects & 5)) {
        MoveEntity(self);
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
void func_060DED1C(u16 arg0) {
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
    subweaponId = ((s16*)g_Stage14AlucardSubweaponIndices.indices - 14)[arg0];
    g_Status.subWeapon = (u32)subweaponId;
    if (mappedId == subweaponId) {
        mappedId = 1;
        stepPtr = self->unk6D;
        step = 0x10;
    } else {
        mappedId = g_Stage14AlucardSubweaponIds[mappedId];
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
INCLUDE_ASM("asm/saturn/stage_14/f_nonmat", f60DEDF8, func_060DEDF8);
INCLUDE_ASM("asm/saturn/stage_14/f_nonmat", f60DF654, func_060DF654);
INCLUDE_ASM("asm/saturn/stage_14/f_nonmat", f60DFB40, func_060DFB40);
INCLUDE_ASM("asm/saturn/stage_14/f_nonmat", f60E0334, func_060E0334);
extern u8 g_CastleFlags[];

void func_060E0674(Entity* self) {
    u16 item;
    PfnEntityUpdate update;

    if (self->step == 0) {
        self->ext.prizeDrop.itemFlagIndex = self->params + 0x100;
        item = self->ext.prizeDrop.itemFlagIndex;
        if (((g_CastleFlags + 0x100)[item >> 3] >> (item & 7)) & 1) {
            DestroyEntity(self);
            return;
        }

        item -= 0x100;
        item = ((u16*)g_Stage14LayoutHorizontal49)[item];
        if (item < 0x80) {
            self->unkB4 = (Entity*)func_060DEDF8;
        } else {
            self->unkB4 = (Entity*)func_060DF654;
            item -= 0x80;
        }
        self->params = item + 0x8000;
    } else {
        item = self->ext.prizeDrop.itemFlagIndex;
        if (self->step < 5 && self->hitFlags) {
            (g_CastleFlags + 0x100)[item >> 3] |= 1 << (item & 7);
            self->step = 5;
        }
    }

    update = (PfnEntityUpdate)self->unkB4;
    update(self);
}
INCLUDE_ASM("asm/saturn/stage_14/f_nonmat", f60E0774, func_060E0774);
INCLUDE_ASM("asm/saturn/stage_14/f_nonmat", f60E0C88, func_060E0C88);
s32 func_060E12F8(Entity* entity) {
    Entity* player = &g_Entities[0];
    s16 distance;

    distance = (s16)(player->posX.i.hi - entity->posX.i.hi);
    distance = ABS(distance);
    if (distance > 22) {
        return 0;
    }

    distance = (s16)(player->posY.i.hi - entity->posY.i.hi);
    distance = ABS(distance);
    if (distance > 32) {
        return 0;
    }

    return 1;
}
INCLUDE_ASM("asm/saturn/stage_14/f_nonmat", f60E1350, func_060E1350);
#include "set_entity_collision_tiles.h"

const u16 DAT_060E178C[2] = {0xCCCC, 0xCCCD};
INCLUDE_ASM("asm/saturn/stage_14/f_nonmat", f60E1790, func_060E1790);
INCLUDE_ASM("asm/saturn/stage_14/f_nonmat", f60E1E64, func_060E1E64);
INCLUDE_ASM("asm/saturn/stage_14/f_nonmat", f60E1FCC, func_060E1FCC);
void func_060E2134(Entity* self) {
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
                CreateEntityFromEntity(E_EXPLOSION, self, entity);
                entity->entityId = E_EXPLOSION;
                entity->pfnUpdate = func_060E1E64;
                entity->params = self->params;
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
INCLUDE_ASM("asm/saturn/stage_14/f_nonmat", f60E2220, EntityDestructAnim);
INCLUDE_ASM("asm/saturn/stage_14/f_nonmat", f60E238C, func_060E238C);
#define SPAWN_DESTRUCT_ANIM_ID 20
#include "spawn_destruct_anim.h"
INCLUDE_ASM("asm/saturn/stage_14/f_nonmat", f60E25DC, func_060E25DC);
INCLUDE_ASM("asm/saturn/stage_14/f_nonmat", f60E26BC, func_060E26BC);
INCLUDE_ASM("asm/saturn/stage_14/f_nonmat", f60E29A8, func_060E29A8);
void func_060E2E80(Entity* self) {
    s32 sp0;
    s32 spriteSize;
    SpriteObject* sprite;
    s16 params;
    SaturnSpriteFrameHeader** frame;
    s32 flags;
    s32 frameType;
    s32 offset;
    s32 i;
    s32 count;

    if (self->step == 0) {
        params = (s16)self->params;
        sp0 = -0x100 & params;
        flags = 3 & params;
        frameType = 2 & flags;
        spriteSize = 6;
        if (frameType != 0) {
            spriteSize = 0x12;
        }

        sprite = CreateSpriteObject(
            g_SaturnSharedSpriteBank8Resource.allocationIndex,
            g_SaturnSharedSpriteBank8Resource.flags,
            g_SaturnSharedSpriteBank8Resource.images, spriteSize);
        self->unk0 = sprite;
        TekiInit(self, 3);

        self->step++;
        frame = DAT_06046CD0;
        if (frameType != 0) {
            frame += 2;
        } else {
            frame += 1;
        }
        func_0600AFA8(sprite, *frame);

        if (sp0 != 0) {
            sprite->flags = (s16)sprite->flags | 0x30;
        }
        sprite->flags = (sprite->flags & 0xFFF8) | 3;
        sprite->posX = self->posX.val;
        sprite->posY = self->posY.val;

        offset = 0xB0;
        if ((1 & flags) != 0) {
            offset = 0xBD;
        }
        if ((flags & 2) != 0) {
            count = 6;
        } else {
            count = 2;
        }

        i = 0;
        for (; i < count; i++) {
            DAT_0608FFF8[offset] = 3;
            DAT_0608FFF8[offset + 1] = 3;
            DAT_0608FFF8[offset + 2] = 3;
            offset -= 0x10;
        }
    }
}
INCLUDE_ASM("asm/saturn/stage_14/f_nonmat", f60E2F8C, func_060E2F8C);
void func_060E2FA4(Entity* entity) {
    entity->unk0 = CreateSpriteObject(
        g_Stage14SpriteBank21.allocationIndex, g_Stage14SpriteBank21.flags,
        g_Stage14SpriteBank21Images, 5);
    SyncSpriteObjectPosUnchecked(entity, g_Stage14MariaBossSensors);
    entity->step = 1;
}
void func_060E2FF4(Entity* self) {
    SyncSpriteObjectPos(self);
    func_0600B004(self->unk0, g_Stage14SpriteBank21Frames[self->animCurFrame]);
}
void func_060E302C(StatusFlagContext* context) {
    if (context->enabled == 0) {
        *context->flags |= FLAG_UNK_10;
    } else {
        *context->flags &= ~FLAG_UNK_10;
    }
}
INCLUDE_ASM("asm/saturn/stage_14/f_nonmat", f60E3058, func_060E3058);
INCLUDE_ASM("asm/saturn/stage_14/f_nonmat", f60E3184, func_060E3184);
INCLUDE_ASM("asm/saturn/stage_14/f_nonmat", f60E32AC, func_060E32AC);
INCLUDE_ASM_NO_ALIGN("asm/saturn/stage_14/f_nonmat", f60E3BB6, func_060E3BB6);
INCLUDE_ASM("asm/saturn/stage_14/f_nonmat", f60E5190, func_060E5190);
INCLUDE_ASM("asm/saturn/stage_14/f_nonmat", f60E5A30, func_060E5A30);
INCLUDE_ASM("asm/saturn/stage_14/f_nonmat", f60E5DF0, func_060E5DF0);
INCLUDE_ASM("asm/saturn/stage_14/f_nonmat", f60E5F50, func_060E5F50);
void func_060E60F8(Entity* self) {
    SyncSpriteObjectPos(self);
    func_0600B004(self->unk0, g_Stage14SpriteBank22Frames[self->animCurFrame]);
}
void func_060E6130(StatusFlagContext* context) {
    if (context->enabled == 0) {
        *context->flags |= FLAG_UNK_10;
    } else {
        *context->flags &= ~FLAG_UNK_10;
    }
}
INCLUDE_ASM("asm/saturn/stage_14/f_nonmat", f60E615C, func_060E615C);
INCLUDE_ASM("asm/saturn/stage_14/f_nonmat", f60E6300, func_060E6300);
INCLUDE_ASM("asm/saturn/stage_14/f_nonmat", f60E6498, func_060E6498);
INCLUDE_ASM("asm/saturn/stage_14/f_nonmat", f60E664C, func_060E664C);
