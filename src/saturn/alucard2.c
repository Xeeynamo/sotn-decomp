// SPDX-License-Identifier: AGPL-3.0-or-later
#include "inc_asm.h"
#include "sattypes.h"

#include "alucard.h"

s32 func_060B24E0(Entity* arg0, s32 arg1) {
    s32 xOffset;
    s32 yOffset;
    s16 xDist;
    s16 yDist;

    if (arg1 == 0) {
        if (arg0->velocityY < 0 || arg0->velocityY < FIX(2)) {
            return 0;
        }
    }

    if ((*(u8*)&arg0->params & 0x7F) == 6) {
        if (PLAYER.animCurFrame != 0x7B && PLAYER.animCurFrame != 0x79) {
            return 0;
        }

        if (((u32)(g_Player.anim - 0x19) <= 1U) &&
            arg0->posY.i.hi <= PLAYER.posY.i.hi - 0x10 &&
            arg0->posY.i.hi >= PLAYER.posY.i.hi - 0x18 &&
            arg0->posX.i.hi <= PLAYER.posX.i.hi + 4 &&
            arg0->posX.i.hi >= PLAYER.posX.i.hi - 4) {
            g_Player.poseTimer = 3;
            g_Player.pose = 8;
            return 1;
        }
        return 0;
    }

    xOffset = (arg0->posX.i.hi - PLAYER.posX.i.hi) + PLAYER.hitboxOffX;
    xDist = (s16)(xOffset < 0 ? -xOffset : xOffset);

    yOffset = (arg0->posY.i.hi - PLAYER.posY.i.hi) + PLAYER.hitboxOffY;
    yDist = (s16)(yOffset < 0 ? -yOffset : yOffset);

    if (xDist <= arg0->hitboxWidth + PLAYER.hitboxWidth &&
        yDist <= arg0->hitboxHeight + PLAYER.hitboxHeight) {
        return 1;
    }
    return 0;
}
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
s32 func_060B3C70(void) {
    if (PLAYER.step_s == 0 || PLAYER.step_s == 8) {
        return 0;
    }

    if ((g_unkGraphicsStruct.D_8009744C != 0 && func_0606FC60(0xE) == 0) ||
        (g_Player.padTapped & 0x10) || func_06070410(2, 1) < 0) {
        SetPlayerStep(0x19);
        g_Player.timers[0x45] = 0;
        g_Player.timers[0x46] = 0;
        g_Player.pad0[0x39D] |= 2;
        func_060BAF44(g_CurrentEntity, 0x0024007B, 0);
        PLAYER.velocityY >>= 1;
        return 1;
    }

    return 0;
}

void func_060B3D28(void) {
    PLAYER.step_s = 2;
    if ((PLAYER.facingLeft == 1 && (g_Player.padPressed & PAD_RIGHT)) ||
        (PLAYER.facingLeft == 0 && (g_Player.padPressed & PAD_LEFT))) {
        func_060A5674(3);
        DAT_060CC774 = 0;
        DAT_060CE4B8 = 0;
    } else if (DAT_060CE4B8 != 0) {
        func_060A5674(4);
        DAT_060CC774 = 2;
        if (PLAYER.velocityX >= 0) {
            if (PLAYER.velocityX < FIX(2.5)) {
                goto apply_velocity;
            }
            return;
        }
        if (-PLAYER.velocityX < FIX(2.5)) {
        apply_velocity:
            func_060A5574(FIX(2.5));
        }
    } else {
        func_060A5674(2);
        DAT_060CC774 = 1;
        DAT_060CE4B8 = 12;
    }
}
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60B3DF8, func_060B3DF8);
void func_060B3F78(void) {
    if (g_Entities->step_s == 2 && DAT_060CC774 == 2) {
        func_060A5674(9);
        DAT_060CC774 = 1;
    } else {
        func_060A5674(10);
        func_060A5574(FIX(1.25));
        DAT_060CC774 = 0;
        if (DAT_060CE4C0 & 0x40) {
            g_Entities->velocityX = 0;
            g_Player.poseTimer = 4;
            g_Entities->poseTimer = 1;
        }
    }
    g_Entities->step_s = 5;
    DAT_060CE4BC -= 0x100;
    g_Player.timers[5] = 8;
    g_Entities->velocityY = 0;
}
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
s32 func_060B79B8(s16 arg0) {
    s32 sp[4];
    s32 result;

    result = func_0607003C(sp, 2, arg0 / 2, 1);
    func_060B9610Internal(sp[2], 0);
    if (result == 4) {
        s16 step = g_Entities->step;
        s16 step_s = g_Entities->step_s;

        sp[0] = 0;
        sp[1] = 0;
        SetPlayerStep(Player_Kill);
        func_060B8B40(sp, step, step_s);
        return -1;
    }
    g_Player.timers[2] = 4;
    g_Player.timers[0x32] = 0x46;
    PlaySfx(DAT_060CC98E[MTH_GetRand() & 1]);
    return 0;
}
void func_060B7A6C(void) {
    u8* playerFlags;

    g_Player.anim = g_Player.pose = g_Player.poseTimer = 0;
    g_Entities->pose = g_Entities->poseTimer = 0;
    g_Entities->animSet = 1;
    g_Entities->entityId = 0;
    g_Entities->unk1C = 0;
    g_Player.unk44 = 0;
    g_Player.unk46 = 0;
    g_Entities->drawFlags &= 0xF3;
    g_Entities->rotate = 0;
    playerFlags = &g_Player.unk39D;
    *playerFlags &= 0xFC;
    if (g_Entities[0x10].entityId == 0x22) {
        func_060A7D3C();
    }
}
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
void func_060B8F68(void) {
    g_Entities->drawFlags = 4;
    g_Entities->velocityY = 0;
    g_Entities->velocityX = 0;
    g_Player.pose = 4;
    if (g_unkGraphicsStruct.unk28 == 0) {
        if (g_Player.vram_flag & 1) {
            func_060A580C(0);
        } else {
            func_060A5AF0();
        }
        func_060BAF44(g_CurrentEntity, 0x4A002C, 0);
    }
}
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
    found->ext.hpNumMove.number = arg0;
    found->ext.hpNumMove.type = arg1;
    return 0;
}

const u16 DAT_060B9690 = 0xCCCC;
const u16 DAT_060B9692 = 0xCCCD;
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60B9694, func_060B9694);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60B9DC0, func_060B9DC0);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60BA4CC, func_060BA4CC);
s32 func_060BA604(Primitive* prim, s16 posX, s16 posY) {
    s16 offset;
    s16 xOffset;
    u16* texture;
    u16* frameWord = (u16*)&prim->x1;
    u8 frame = ((u8*)frameWord)[1];

    if (frame >= 3) {
        offset = 4;
    } else {
        offset = 6;
    }

    if (frame == 6) {
        return -1;
    }

    xOffset = offset | 1;
    prim->x0 = posX - xOffset;
    prim->y0 = posY - offset;
    prim->x2 = posX + xOffset;
    prim->y2 = posY + offset;

    texture = DAT_0605aec0[(u16)DAT_060CBE3C +
                           g_AlucardFactoryAnimationLookup[frame]];
    prim->unk8 = texture[0];
    prim->unkA = texture[1];

    prim->y1++;
    if (!(prim->y1 & 1)) {
        (*frameWord)++;
    }
    return 0;
}

const u16 DAT_060BA6B4 = 0xAAAA;
const u16 DAT_060BA6B6 = 0xAAAB;
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

s32 func_060BA9A0(Entity* entity, s32 arg) {
    SpellDef spell;

    func_0606F59C(&spell, arg);
    entity->attack = spell.attack;
    entity->attackElement = spell.attackElement;
    entity->hitboxState = spell.hitboxState;
    entity->nFramesInvincibility = spell.nFramesInvincibility;
    entity->stunFrames = spell.stunFrames;
    entity->hitEffect = spell.hitEffect;
    entity->entityRoomIndex = spell.entityRoomIndex;
    func_060B9340(entity);
}
void func_060BAA20(Entity* arg0, s32 arg1, s32 arg2, FamiliarStats* arg3) {
    SpellDef spell;

    *arg3 = g_Status.statsFamiliars[g_Servant - 1];
    if (arg2 != 0) {
        func_0606F59C((SpellDef*)&spell, arg1);
        arg0->attack = spell.attack;
        arg0->attackElement = spell.attackElement;
        arg0->hitboxState = spell.hitboxState;
        arg0->nFramesInvincibility = spell.nFramesInvincibility;
        arg0->stunFrames = spell.stunFrames;
        arg0->hitEffect = spell.hitEffect;
        arg0->entityRoomIndex = spell.entityRoomIndex;
        arg0->attack = spell.attack * (arg3->level * 4 / 95 + 1);
        func_060B9340(arg0);
    }
}
// UpdatePlayerEntities
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60BAB00, func_060BAB00);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60BAD84, func_060BAD84);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60BAE70, func_060BAE70);
// CreateEntFactoryFromEntity
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60BAF44, func_060BAF44);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60BB070, func_060BB070);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60BB4FC, func_060BB4FC);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60BB678, func_060BB678);
void func_060BB7A8(Entity* entity) {
    Entity* player = g_Entities;

    if (player->step != 5 || player->step_s != 3) {
        DestroyEntity(entity);
        return;
    }

    entity->flags = 0x00060000;
    entity->facingLeft = player->facingLeft;
    entity->posY.i.hi = player->posY.i.hi;
    entity->posX.i.hi = player->posX.i.hi;

    if (entity->step == 0) {
        func_060BA9A0(entity, 6);
        entity->hitboxOffX = 4;
        entity->hitboxOffY = 0;
        entity->hitboxWidth = 12;
        entity->hitboxHeight = 12;
        entity->step++;
    }
}

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
void func_060BD5A4(void) {
    SaturnSpriteResource* resource;
    u16* flags;
    u8* destination;
    AlucardSubPaletteData* palette;
    s32 tableNo;
    s32 nextTableNo;

    if (g_Entities->animSet == 13 || g_Entities->animSet <= 13 ||
        g_Entities->animSet != 15) {
        destination = &DAT_060C8574;
        tableNo = (u16)DAT_060CBE02;
    } else {
        flags = &AlucardSpriteResources[2].flags;
        tableNo = *flags;
        nextTableNo = tableNo + 1;
        resource =
            (SaturnSpriteResource*)((u8*)flags - (sizeof(SaturnSpriteResource) -
                                                  sizeof(resource->flags)));
        palette = (AlucardSubPaletteData*)resource->palettes;
        destination = (u8*)palette->colors[0];
        LookupTblNoToVramAddr((u16)nextTableNo, (u8*)palette->colors[1]);
    }

    LookupTblNoToVramAddr((u16)tableNo, destination);
    g_Player.unk452 = 3;
}
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
    s32 (*applySpell)(Entity*, s32);

    if (!(g_Player.status & 2)) {
        DestroyEntity(self);
        return;
    }

    if (self->step == 0) {
        applySpell = func_060BA9A0;
        applySpell(self, 12);
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
s32 func_060C2338(s32 y, s32 x) {
    Collider collider;
    s32 xShift;

    if (g_CurrentEntity->velocityX == 0) {
        return 0;
    }

    ((s32(*)(s32, s32, Collider*, u16))CheckCollision)(
        g_CurrentEntity->posX.val + x, g_CurrentEntity->posY.val + y, &collider,
        0);

    if (g_CurrentEntity->velocityX > 0) {
        xShift = collider.unk14;
    } else {
        xShift = collider.unk1C;
    }

    if (collider.effects & EFFECT_SIDE) {
        g_CurrentEntity->posX.val += xShift;
        g_CurrentEntity->posX.i.lo = 0;
        return 2;
    }
    return 0;
}
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
