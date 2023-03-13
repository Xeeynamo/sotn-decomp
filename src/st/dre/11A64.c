/*
 * File: 11A64.c
 * Overlay: DRE
 * Description: Nightmare
 */

#include "dre.h"

// puts garbled hp max up text on screen
void EntityUnkId11(Entity* entity) {
    ObjInit2* obj = (ObjInit2*)&D_80180528[entity->subId * 10];

    if (entity->step == 0) {
        InitializeEntity(&D_801804AC);
        entity->animSet = obj->animSet;
        entity->zPriority = obj->zPriority;
        entity->unk5A = obj->unk4.s;
        entity->palette = obj->palette;
        entity->unk19 = obj->unk8;
        entity->blendMode = obj->blendMode;

        if (obj->unkC != 0) {
            entity->flags = obj->unkC;
        }

        if (entity->subId == 1) {
            entity->unk1C = 0x200;
            entity->unk1A = 0x200;
        }
    }

    AnimateEntity(obj->unk10, entity);
}

void func_80191B44(Entity* entity) {
    s32 ret;
    u16* temp_v0_2;
    u16 temp_s1 = entity->subId;
    u16 phi_v1;
    u16 unk;
    entity->unk6D = 0;

    if (entity->step != 0) {
        switch (temp_s1) {
        case 4:
        case 5:
            if (g_CurrentRoom.x != 0) {
                return;
            }
            break;

        case 6:
            if (g_pads->pressed & PAD_TRIANGLE) {
                g_CurrentRoom.x = 0;
                g_CurrentRoom.width = 1280;
                entity->step++;
                return;
            }
            break;
        }

        if (entity->unk44 != 0) {
            ret = func_8019A718();
            phi_v1 = entity->unk7C.s;
            if (phi_v1 != 0) {
                phi_v1 = (ret & 2) * 2;
            } else {
                phi_v1 = (ret & 1) * 4;
            }
            unk = 8;
            temp_s1 = (temp_s1 * unk) + phi_v1;
            temp_v0_2 = &D_80180590[temp_s1];
            g_CurrentRoom.x = *(temp_v0_2++);
            g_CurrentRoom.y = *(temp_v0_2++);
            g_CurrentRoom.width = *(temp_v0_2++);
            g_CurrentRoom.height = *(temp_v0_2++);
        }
    } else {
        InitializeEntity(D_801804A0);
        entity->unk7C.s = D_80180588[temp_s1];
        if (entity->unk7C.s != 0) {
            entity->hitboxWidth = D_80180580[temp_s1];
            entity->hitboxHeight = 16;
        } else {
            entity->hitboxWidth = 16;
            entity->hitboxHeight = D_80180580[temp_s1];
        }
    }
}

extern u16 g_eBreakableInit[];
extern u8* g_eBreakableAnimations[];
extern u8 g_eBreakableHitboxes[];
extern u8 g_eBreakableExplosionTypes[];
extern u16 g_eBreakableanimSets[];
extern u8 g_eBreakableBlendModes[];
void EntityBreakable(Entity* entity) {
    Entity* temp_v0;
    u16 temp_s0 = entity->subId >> 0xC;

    if (entity->step != 0) {
        AnimateEntity(g_eBreakableAnimations[temp_s0], entity);
        if (entity->unk44 != 0) {
            g_api.PlaySfx(NA_SE_BREAK_CANDLE);
            temp_v0 = AllocEntity(D_8007D858, &D_8007D858[32]);
            if (temp_v0 != NULL) {
                CreateEntityFromCurrentEntity(2, temp_v0);
                temp_v0->subId = g_eBreakableExplosionTypes[temp_s0];
            }
            ReplaceBreakableWithItemDrop(entity);
        }
    } else {
        InitializeEntity(g_eBreakableInit);
        entity->zPriority = g_zEntityCenter.S16.unk0 - 20;
        entity->blendMode = g_eBreakableBlendModes[temp_s0];
        entity->hitboxHeight = g_eBreakableHitboxes[temp_s0];
        entity->animSet = g_eBreakableanimSets[temp_s0];
    }
}

// clouds in the background ID 0x18
INCLUDE_ASM("asm/us/st/dre/nonmatchings/11A64", EntityBackgroundClouds);

// Shows Alucard's mother on cross, but may be the succubus boss given
// that the asm is huge (ID 0x19)
INCLUDE_ASM("asm/us/st/dre/nonmatchings/11A64", EntityMother);

// Petal projectile shot by succubus ID 0x1A
INCLUDE_ASM("asm/us/st/dre/nonmatchings/11A64", EntitySuccubusPetal);

void EntityUnkId1B(Entity* entity) {
    if (entity->step == 0) {
        InitializeEntity(D_801804E8);
    }

    entity->posX.i.hi = entity[-1].posX.i.hi;
    entity->animCurFrame = 0;
    entity->posY.i.hi = entity[-1].posY.i.hi;
    entity->facing = entity[-1].facing;

    if (entity[-1].animCurFrame == 0x32) {
        entity->animCurFrame = 0x3E;
    }

    if (entity[-1].animCurFrame == 0x33) {
        entity->animCurFrame = 0x3F;
    }

    entity->zPriority = PLAYER.zPriority + 4;
}

INCLUDE_ASM("asm/us/st/dre/nonmatchings/11A64", EntityUnkId1C);
