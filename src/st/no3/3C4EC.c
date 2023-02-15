#include "no3.h"

// pushes alucard to the right
void EntityPushAlucard(Entity* entity) {
    Entity* player = &PLAYER;
    Unkstruct8* roomLayout = &g_CurrentRoomTileLayout;

    switch (entity->step) {
    case 0:
        InitializeEntity(&D_80180AD0);
        g_EntityArray[UNK_ENTITY_1].unk7C.S8.unk0 = 1;
        *D_80072EF4 = 0;
        D_80072EFC = 255;
        player->posX.i.hi = 0;
        *D_8009740C = 0;
        player->animCurFrame = 0;
        D_8003C8B8 = 0;
        break;

    case 1:
        player->posX.val += 0x60000;
        if (roomLayout->unkA > 0x800) {
            g_EntityArray[UNK_ENTITY_1].unk7C.S8.unk0 = 0;
            *D_80072EF4 = 0x2000;
            entity->step++;
        }
        player->animCurFrame = 0;
        D_80072EFC = 1;
        g_api.func_8010E0A8();
        break;

    case 2:
        player->posX.val += 0x88000;
        *D_8009740C += 4;
        if (*D_8009740C == 192) {
            entity->unk80.modeS32 = 0x48000;
            entity->step++;
        }
        D_80072EFC = 1;
        g_api.func_8010E0A8();
        break;

    case 3:
        if (*D_8009740C > 128) {
            *D_8009740C -= 1;
            entity->unk80.modeS32 = 0x38000;
        } else {
            entity->unk80.modeS32 = 0x48000;
        }
        player->posX.val += entity->unk80.modeS32;
        if (entity->unk80.modeS32 == 0x48000) {
            entity->step++;
        }
        D_80072EFC = 1;
        g_api.func_8010E0A8();
        break;

    case 4:
        player->posX.val += 0x48000;
        if (roomLayout->unkA > 0xF80) {
            g_api.PlaySfx(0x6EF);
            *D_80072EF4 = 0x2040;
            entity->unk7C.S8.unk0 = 0;
            entity->step++;
        }
        D_80072EFC = 1;
        g_api.func_8010E0A8();
        break;

    case 5:
        if ((player->accelerationY > 0) && (entity->unk7C.U8.unk0 == 0)) {
            *D_80072EF4 = 0x40;
            entity->unk7C.S8.unk0 = 1;
        } else {
            *D_80072EF4 = 0x2040;
        }
        g_api.func_8010E0A8();
        D_80072EFC = 1;
        player->posX.val += 0x48000;
    }
}

// Instruction reorder, only matches in PSY-Q 4.0
// Probably ASPSX
#ifndef NON_MATCHING
INCLUDE_ASM("asm/st/no3/nonmatchings/3C4EC", EntityUnkId53);
#else
void EntityUnkId53(Entity* entity) {
    s32 temp_v0;
    Entity* player = &PLAYER;

    switch (entity->step) {
    case 0:
        if (*D_8003BE20 != 0) {
            DestroyEntity(entity);
            return;
        }
        InitializeEntity(&D_80180AD0);
        g_EntityArray[1].unk7C.S8.unk0 = 1;
        *D_80072EF4 = 0x2000;
        D_80072EFC = 0xFF;
        player->posX.i.hi = 8;
        *(s32*)&entity->unk7C.s = 0x28000;
        break;

    case 1:
        player->posX.val += *(s32*)&entity->unk7C.s;
        D_80072EFC = 1;
        if ((player->posX.i.hi + (s16)D_8007308E) > 120) {
            *D_80072EF4 = 0;
            entity->step++;
        }
        break;

    case 2:
        if (*(s32*)&entity->unk7C.s != 0) {
            *(s32*)&entity->unk7C.s -= 0x2800;
            func_801C8C84(&PLAYER, 1, 1, 4, 0x18, (Random() & 3) + 1, -4);
        } else {
            D_8003C8B8 = 1;
            entity->step++;
        }
        player->posX.val += *(s32*)&entity->unk7C.s;
        D_80072EFC = 1;
        break;
    }
}
#endif

// large foreground tree during intro
INCLUDE_ASM("asm/st/no3/nonmatchings/3C4EC", EntityForegroundTree);

INCLUDE_ASM("asm/st/no3/nonmatchings/3C4EC", EntityUnkId50);

// part of parallax background with pine trees
INCLUDE_ASM("asm/st/no3/nonmatchings/3C4EC", EntityBackgroundPineTrees);

INCLUDE_ASM("asm/st/no3/nonmatchings/3C4EC", EntityUnkId52);

INCLUDE_ASM("asm/st/no3/nonmatchings/3C4EC", EntityUnkId54);

INCLUDE_ASM("asm/st/no3/nonmatchings/3C4EC", EntityUnkId55);

// shows part of the parallax background castle wall
void EntityBackgroundCastleWall(Entity* entity) {
    Entity* newEntity;

    newEntity = AllocEntity(D_8007C0D8, &D_8007C0D8[64]);
    if (newEntity != NULL) {
        CreateEntityFromCurrentEntity(0x11U, newEntity);
        newEntity->subId = 0xC;
        newEntity->unk68 = 0x80;
        newEntity = AllocEntity(newEntity, &D_8007C0D8[64]);
        if (newEntity != NULL) {
            CreateEntityFromCurrentEntity(0x11U, newEntity);
            newEntity->subId = 0xB;
            newEntity->posY.i.hi = 0x80;
            newEntity->unk68 = 0xC0;
            newEntity->posX.i.hi += 0x40;
        }
    }
    DestroyEntity(entity);
}
