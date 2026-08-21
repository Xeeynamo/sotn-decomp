// SPDX-License-Identifier: AGPL-3.0-or-later
#include "inc_asm.h"
#include "sattypes.h"

#include "alucard.h"

// func_060BD6A8 and func_060BFADC call with no args
void DestroyEntity();

INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60B24E0, func_060B24E0);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60B25F4, func_060B25F4);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60B2B30, func_060B2B30);
// GetPlayerSensor
void func_060B2DE4(Collider* col) {
    u32 mod = 0;

    if (g_Player.status & PLAYER_STATUS_WOLF_FORM) {
        mod += 0x20000;
    }

    col->unk14 = g_AlucardSensorsWall[0].x - mod;
    col->unk1C = g_AlucardSensorsWall[0].y + mod;
    col->unk18 = g_AlucardSensorsFloor[1].y - 0x10000;
    col->unk20 = g_AlucardSensorsCeiling[1].y + 0x10000;
}
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60B2E40, func_060B2E40);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60B3024, func_060B3024);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60B349C, func_060B349C);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60B38B4, func_060B38B4);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60B3A90, func_060B3A90);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60B3C70, func_060B3C70);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60B3D28, func_060B3D28);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60B3DF8, func_060B3DF8);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60B3F78, func_060B3F78);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60B4024, func_060B4024);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60B41C8, func_060B41C8);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60B4328, func_060B4328);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60B446C, func_060B446C);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60B4B90, func_060B4B90);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60B4E38, func_060B4E38);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60B4F78, func_060B4F78);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60B537C, func_060B537C);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60B5634, func_060B5634);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60B57F4, func_060B57F4);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60B5920, func_060B5920);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60B5AF4, func_060B5AF4);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60B5C68, func_060B5C68);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60B5E94, func_060B5E94);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60B6768, func_060B6768);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60B6AA4, func_060B6AA4);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60B6D94, func_060B6D94);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60B7214, func_060B7214);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60B761C, func_060B761C);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60B7848, func_060B7848);
void func_060B7994(void) {
    s16 zero;
    EntryS060CE980* entry;

    zero = 0;
    entry = DAT_060CE980;
    do {
        *entry->unk4 = zero;
        entry++;
    } while ((s32)entry <= (s32)DAT_060CEA70);
}
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60B79B8, func_060B79B8);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60B7A6C, func_060B7A6C);
// richter.c func_80159C04
void func_060B7B0C(void) {
    Entity* entity;
    s16 attackerOffX;
    s16 playerOffX;
    s16 distance;

    entity = PLAYER.unkB4;
    if (entity->facingLeft) {
        attackerOffX = -entity->hitboxOffX;
    } else {
        attackerOffX = entity->hitboxOffX;
    }

    if (PLAYER.facingLeft) {
        playerOffX = -PLAYER.hitboxOffX;
    } else {
        playerOffX = PLAYER.hitboxOffX;
    }

    distance = playerOffX + PLAYER.posX.i.hi - entity->posX.i.hi - attackerOffX;
    if (ABS(distance) < 16 && entity->velocityX != 0) {
        if (entity->velocityX < 0) {
            PLAYER.entityRoomIndex = 0;
        } else {
            PLAYER.entityRoomIndex = 1;
        }
        return;
    }

    if (distance < 0) {
        PLAYER.entityRoomIndex = 0;
    } else {
        PLAYER.entityRoomIndex = 1;
    }
}

const u16 DAT_060B7BB0 = 0xAAAA;
const u16 DAT_060B7BB2 = 0xAAAB;
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60B7BB4, func_060B7BB4);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60B86F4, func_060B86F4);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60B8B40, func_060B8B40);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60B8F68, func_060B8F68);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60B8FE0, func_060B8FE0);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60B9130, func_060B9130);
// GetFreeEntity
#define E_NONE 0
Entity* func_060B92B8(s16 start, s16 end) {
    Entity* entity = &g_Entities[start];
    s16 i;

    for (i = start; i < end; i++, entity++) {
        if (entity->entityId == E_NONE) {
            return entity;
        }
    }
    return NULL;
}
// GetFreeEntityReverse
Entity* func_060B92F8(s16 start, s16 end) {
    Entity* entity = &g_Entities[end - 1];
    s16 i;
    for (i = end - 1; i >= start; i--, entity--) {
        if (entity->entityId == E_NONE) {
            return entity;
        }
    }
    return NULL;
}
// func_80118894 on PSX
void func_060B9340(Entity* entity) {
    s32 i;
    s32 search_value;

    if (entity == &g_Entities[0x10]) {
        if (!(entity->params & 0x8000)) {
            entity->enemyId = 1;
        } else {
            entity->enemyId = 2;
        }
        return;
    }

    if (entity < &g_Entities[0x20]) {
        for (search_value = 0;; search_value++) {
            for (i = 3; i < 7; i++) {
                if (DAT_060CE4F0[i] == search_value) {
                    DAT_060CE4F0[i]++;
                    entity->enemyId = i;
                    return;
                }
            }
        }
    } else {
        for (search_value = 0;; search_value++) {
            for (i = 7; i < 11; i++) {
                if (DAT_060CE4F0[i] == search_value) {
                    DAT_060CE4F0[i]++;
                    entity->enemyId = i;
                    return;
                }
            }
        }
    }
}
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60B93C4, func_060B93C4);
s16 func_060B94F8(Entity* self, Entity* target, s16 targetOffscreenLeft) {
    s16 selfY;
    s16 targetY;
    s16 targetX;
    s32 angle;
    s32 reason;

    if (target != NULL) {
        targetX = target->posX.i.hi;
        targetY = target->posY.i.hi;
    } else {
        targetY = 0x70;
        if (targetOffscreenLeft != 0) {
            targetX = -0x30;
        } else {
            targetX = 0x170;
        }
    }

    angle = ratan2(-(s16)(targetY - self->posY.i.hi),
                   (s16)(targetX - self->posX.i.hi)) &
            0xFFF;
    reason = 0;

    if (target != NULL) {
        if (target->entityId == 0) {
            reason = 0x1000;
        }
        if (target->hitboxState == 0) {
            reason = 0x2000;
        }
        if (target->flags & 0x00200000) {
            reason = 0x3000;
        }
    }

    if (self->posX.i.hi > 0x160) {
        reason = 0x4000;
    }
    if (self->posX.i.hi < -0x20) {
        reason = 0x5000;
    }

    selfY = self->posY.i.hi;
    if (selfY > 0xF0) {
        reason = 0x6000;
    }
    if (selfY < 0) {
        reason = 0x7000;
    }

    return angle - reason;
}
void func_060B95C8(s32 arg0) {
    DAT_060CC9BC = DAT_060CC9BD[arg0].f0;
    DAT_060CE51C = DAT_060CC9BD[arg0].f1;
    DAT_060CE51D = DAT_060CC9BD[arg0].f2;
    DAT_060CE51E = DAT_060CC9BD[arg0].f3;
}
s32 func_060B9610(s16 arg0, s16 arg1) {
    Entity* entity;
    Entity* found;
    s16 limit;
    s16 index;

    limit = 0x40;
    entity = &g_Entities[0x38];
    index = 0x38;
    while (1) {
        if (entity->entityId == 0) {
            found = entity;
            break;
        }
        index++;
        entity++;
        if (index >= limit) {
            found = NULL;
            break;
        }
    }

    if (found == NULL) {
        return -1;
    }
    DestroyEntity(found);
    found->entityId = 0x13;
    found->posX.val = PLAYER.posX.val;
    found->posY.val = PLAYER.posY.val;
    found->ext.ILLEGAL.u16[2] = arg0;
    found->ext.ILLEGAL.u16[3] = arg1;
    return 0;
}

const u16 DAT_060B9690 = 0xCCCC;
const u16 DAT_060B9692 = 0xCCCD;
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60B9694, func_060B9694);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60B9DC0, func_060B9DC0);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60BA4CC, func_060BA4CC);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60BA604, func_060BA604);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60BA6B8, func_060BA6B8);
// SetSubweaponParams / richter.c func_060ABA98
void func_060BA90C(Entity* entity) {
    SubweaponDef subwpn;

    func_0606FC80(&subwpn, entity->ext.bat.lastPlayerPosX, 0);
    entity->attack = subwpn.attack;
    entity->attackElement = subwpn.attackElement;
    entity->hitboxState = subwpn.hitboxState;
    entity->nFramesInvincibility = subwpn.nFramesInvincibility;
    entity->stunFrames = subwpn.stunFrames;
    entity->hitEffect = subwpn.hitEffect;
    entity->entityRoomIndex = subwpn.entityRoomIndex;
    entity->ext.bat.lastPlayerPosY = subwpn.crashId;
    func_060B9340(entity);
}

INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60BA9A0, func_060BA9A0);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60BAA20, func_060BAA20);
// UpdatePlayerEntities
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60BAB00, func_060BAB00);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60BAD84, func_060BAD84);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60BAE70, func_060BAE70);
// CreateEntFactoryFromEntity
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60BAF44, func_060BAF44);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60BB070, func_060BB070);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60BB4FC, func_060BB4FC);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60BB678, func_060BB678);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60BB7A8, func_060BB7A8);
void func_060BB8A8(Entity* entity) {
    SpellDef spell;

    if (PLAYER.step != 0x25) {
        DestroyEntity(entity);
        return;
    }

    if (entity->step == 0) {
        entity->flags = 0x00060000;
        func_0606F59C(&spell, 5);
        entity->attack = spell.attack;
        entity->attackElement = spell.attackElement;
        entity->hitboxState = spell.hitboxState;
        entity->nFramesInvincibility = spell.nFramesInvincibility;
        entity->stunFrames = spell.stunFrames;
        entity->hitEffect = spell.hitEffect;
        entity->entityRoomIndex = spell.entityRoomIndex;
        func_060B9340(entity);
        entity->step++;
    }
}

const u16 DAT_060BB964 = 0x8888;
const u16 DAT_060BB966 = 0x8889;
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60BB968, func_060BB968);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60BBD9C, func_060BBD9C);
// func_8011BD48 on PSX
s32 func_060BBF08(Entity* arg0) {
    Entity* entity;
    s16 entityId;
    s16 params;
    s32 i;

    entityId = arg0->entityId;
    params = arg0->params;
    i = 0x10;
    entity = &g_Entities[0x10];

    for (; i <= 0x3F; i++, entity++) {
        if (entityId == entity->entityId && params == entity->params) {
            if (entity != arg0) {
                return 1;
            }
        }
    }

    return 0;
}
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60BBF5C, func_060BBF5C);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60BC01C, func_060BC01C);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60BCD98, func_060BCD98);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60BD214, func_060BD214);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60BD2B0, func_060BD2B0);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60BD39C, func_060BD39C);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60BD5A4, func_060BD5A4);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60BD61C, func_060BD61C);

void func_060BD6A8(void) { DestroyEntity(); }

void func_060BD6C0() {}

const u16 DAT_060BD6CA = 0;

void func_060BD6CC() {}

INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60BD6D8, func_060BD6D8);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60BD8F8, func_060BD8F8);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60BDA44, func_060BDA44);

void func_060BE354() {}

const u32 DAT_060be360 = 0xBA2E8BA3;

INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60BE364, func_060BE364);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60BE620, func_060BE620);
void func_060BE7DC(Primitive* src, Primitive* dst) {
    dst->unk4 = src->unk4;
    dst->unk6 = src->unk6;
    dst->unk8 = src->unk8;
    dst->unkA = src->unkA;
    dst->priority = src->priority;
    dst->x0 = src->x0;
    dst->y0 = src->y0;
    dst->x1 = src->x1;
    dst->y1 = src->y1;
    dst->x2 = src->x2;
    dst->y2 = src->y2;
    dst->x3 = src->x3;
    dst->y3 = src->y3;
    dst->drawMode = src->drawMode;
}
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60BE888, func_060BE888);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60BEEF8, func_060BEEF8);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60BF470, func_060BF470);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60BF894, func_060BF894);
void func_060BFADC(void) { DestroyEntity(); }

const u8 pad_060BFAF4[] = {
    0x23, 0x23, 0x3B, 0x3C, 0x3D, 0x3E, 0x3F, 0x40, 0x41, 0x42, 0x43, 0x44,
    0x23, 0x23, 0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39,
    0x3A, 0x2D, 0x2E, 0x2F, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2A,
    0x2B, 0x2C, 0x2D, 0x2E, 0x2F, 0x23, 0x23, 0x45, 0x46, 0x47, 0x48, 0x49,
    0x4A, 0x4B, 0x4C, 0x4D, 0x4E, 0x4F, 0x50, 0x23,
};
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60BFB2C, func_060BFB2C);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60C0014, func_060C0014);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60C01C0, func_060C01C0);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60C06A0, func_060C06A0);
void func_060C07F0(Entity* self) {
    if (!(g_Player.status & 2)) {
        DestroyEntity(self);
        return;
    }

    if (self->step == 0) {
        func_060BA9A0(self, 12);
        self->enemyId = 4;
        self->hitboxWidth = self->hitboxHeight = 8;
        self->flags = 0x04020000;
        self->step++;
    }

    self->posX.i.hi = PLAYER.posX.i.hi;
    self->posY.i.hi = PLAYER.posY.i.hi;
    self->hitboxWidth = self->hitboxHeight = 0x1C;

    if (func_0606FC60(9) == 0) {
        self->hitboxState = 0;
    } else {
        self->hitboxState = 2;
    }
}
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60C08A8, func_060C08A8);

void func_060C0BE8() {}

INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60C0BF4, func_060C0BF4);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60C0E48, func_060C0E48);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60C1374, func_060C1374);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60C1484, func_060C1484);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60C1618, func_060C1618);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60C175C, func_060C175C);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60C18A8, func_060C18A8);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60C1C60, func_060C1C60);
// CheckHolyWaterCollision
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60C2264, func_060C2264);
// func_80125B6C on PSX
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60C2338, func_060C2338);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60C239C, func_060C239C);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60C262C, func_060C262C);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60C293C, func_060C293C);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60C3214, func_060C3214);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60C3490, func_060C3490);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60C38CC, func_060C38CC);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60C3A48, func_060C3A48);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60C3BD4, func_060C3BD4);
void func_060C3D74() {}
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60C3D80, func_060C3D80);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60C3EE4, func_060C3EE4);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60C4DA0, func_060C4DA0);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60C4E5C, func_060C4E5C);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60C5320, func_060C5320);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60C593C, func_060C593C);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60C5C94, func_060C5C94);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60C6070, func_060C6070);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60C61E4, func_060C61E4);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60C6F68, func_060C6F68);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60C7154, func_060C7154);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60C75A8, func_060C75A8);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60C7FA0, func_060C7FA0);
