#include "no3.h"

// intro owl and leaves
void EntityFlyingOwlAndLeaves(Entity* entity) {
    Unkstruct8* currentRoomTiles = &g_CurrentRoomTileLayout;
    Entity* newEntity;
    u16 animFlag = true;
    u16 i;

    switch (entity->step) {
    case 0:
        InitializeEntity(D_80180B00);
        entity->animSet = ANIMSET_OVL(1);
        entity->animCurFrame = 56;
        if (entity->params != 0) {
            entity->unk19 = 0xB;
            entity->unk1A = 0x180;
            entity->unk1C = 0x180;
            entity->unk6C = 0x60;
            entity->posY.i.hi = -16;
            entity->zPriority = 0xC1;
        } else {
            entity->unk19 = 8;
            entity->unk6C = 0x20;
            entity->zPriority = 0xBF;
        }
        entity->unk68 = 0x1C0;
        break;

    case 1:
        if (entity->posX.i.hi < 224) {
            entity->ext.generic.unk7C.s = 0;
            entity->step++;
        }
        break;

    case 2:
        if (!(entity->ext.generic.unk7C.s++ & 7)) {
            g_api.PlaySfx(0x7A4);
        }
        if (entity->posX.i.hi < 192) {
            SetStep(3);
            if (entity->params != 0) {
                entity->velocityX = FIX(8);
                entity->velocityY = FIX(3);
                break;
            }
            entity->velocityX = FIX(10);
            entity->velocityY = FIX(1.625);
            for (i = 0; i < 8; i++) {
                newEntity = AllocEntity(D_8007D858, &D_8007D858[32]);
                if (newEntity != NULL) {
                    CreateEntityFromCurrentEntity(0x60, newEntity);
                    newEntity->params = i;
                }
            }
        }
        break;

    case 3:
        if (entity->params != 0) {
            animFlag = AnimateEntity(D_801819DC, entity);
            entity->velocityY -= 0xA00;
        } else {
            animFlag = AnimateEntity(D_801819D0, entity);
            if (entity->velocityY > (s32)0xFFFE0000) {
                entity->velocityY -= FIX(0.03125);
            }
        }
        MoveEntity();
        if ((entity->params == 0) && (currentRoomTiles->unkA > 0xD80)) {
            entity->step++;
        }
        if (entity->posX.i.hi > 288) {
            DestroyEntity(entity);
        } else if (entity->posY.i.hi < -16) {
            DestroyEntity(entity);
        }
        break;

    case 4:
        if (entity->velocityY > (s32)0xFFFE0000) {
            entity->velocityY -= FIX(0.03125);
        }
        animFlag = AnimateEntity(D_801819D0, entity);
        MoveEntity();
        if (entity->unk6C < 0x78) {
            entity->unk6C += 2;
        }
        if (entity->posX.i.hi > 288) {
            DestroyEntity(entity);
        } else if (entity->posY.i.hi < -16) {
            DestroyEntity(entity);
        }
    }

    if (!animFlag) {
        func_801CAD28(0x68C);
    }
}

// a single leaf from when the owl comes out in the intro
void EntityFallingLeaf(Entity* entity) {
    volatile int pad;

    switch (entity->step) {
    case 0:
        InitializeEntity(D_80180B00);
        entity->animSet = ANIMSET_OVL(1);
        entity->animCurFrame = (entity->params & 1) + 63;
        entity->zPriority = 0xC1;
        entity->velocityX = D_801819E8[entity->params * 2];
        entity->velocityY = D_801819EC[entity->params * 2];
        entity->unk68 = 0x1C0;
        break;

    case 1:
        if (entity->velocityX > 0) {
            entity->velocityX -= FIX(0.0625);
        }
        if (entity->velocityY < FIX(1.0); {
            entity->velocityY += 0x400;
        }
        if (entity->velocityY > FIX(1.0); {
            entity->velocityY -= 0x400;
        }
        MoveEntity();
        break;
    }
}

void func_801BE544(void) {
    D_801D7D30 = 0x182;
    D_801D7D2E = 0x182;
    D_801D7D32 = 0;
    D_801D7D36 = 0;
    D_801D7D3A = 0;
    D_801D7D3B = 8;
    D_801D7D2A = D_801D7D2C + 0x14;
}

INCLUDE_ASM("asm/us/st/no3/nonmatchings/3E134", func_801BE598);

void func_801BE75C(s16 yOffset) {
    RECT rect;

    rect.x = 384;
    rect.y = (yOffset * 12) + 256;
    rect.w = 64;
    rect.h = 12;
    ClearImage(&rect, 0, 0, 0);
}

INCLUDE_ASM("asm/us/st/no3/nonmatchings/3E134", func_801BE7BC);

INCLUDE_ASM("asm/us/st/no3/nonmatchings/3E134", func_801BE870);

void func_801BE9F4(s32 arg0) {
    D_801D7D64 = arg0 + 0x100000;
    D_801D7D62 = 0;
    D_801D7D60 = 1;
}

INCLUDE_ASM("asm/us/st/no3/nonmatchings/3E134", func_801BEA20);

void func_801BECCC(Entity* entity) {
    /** TODO: !FAKE
     * do while (0) fixed instruction reordering at
     * entity->flags ^= FLAG_HAS_PRIMS;
     * but intruduces a problem in PlaySfx, which is fixed
     * by using gameApi pointer.
     */
    GameApi* gameApi;

    if (g_pads[0].tapped == 0x800) {
        D_801D7D20 = 1;
        g_api.FreePrimitives(entity->primIndex);
        do {
            entity->flags ^= FLAG_HAS_PRIMS;
        } while (0);
        if (D_801D7D58 != -1) {
            g_api.FreePrimitives(D_801D7D58);
        }
        if (D_801D7D54 != -1) {
            g_api.FreePrimitives(D_801D7D54);
        }
        gameApi = &g_api;
        (*gameApi).PlaySfx(SET_STOP_MUSIC);
        entity->step = 1;
        entity->step_s = 0;
    }
}

INCLUDE_ASM("asm/us/st/no3/nonmatchings/3E134", func_801BEDAC);
// seems to cause a room transition
INCLUDE_ASM("asm/us/st/no3/nonmatchings/3E134", EntityRoomTransition1);
