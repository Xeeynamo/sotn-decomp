// SPDX-License-Identifier: AGPL-3.0-or-later
#include "inc_asm.h"
#include "sattypes.h"
#include "game.h"

void DestroyEntity(Entity* entity);

void PlaySfx(s32 sfxId);

INCLUDE_ASM("asm/saturn/game/f_nonmat", f606B6F8, LoadSubDisplayFiles);

// _READ_SUB_OUT_MODE
INCLUDE_ASM("asm/saturn/game/f_nonmat", f606B760, func_0606B760);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f606BB4C, func_0606BB4C);

extern char* g_StageAlternateMapNames[];

void ResetSpriteVram();
void func_0601AC48();
void func_0600C114();
void func_0600C2EC();
void func_0600C00C();
void func_0600C1A0();
void func_0600BE18(s32);

void func_0606BEE4(void) {
    char* ptr;
    u16 idx;

    idx = g_CurrentRoom.unk8;
    ResetSpriteVram();
    func_0600BE18(g_PlayableCharacter);
    func_0600C1A0();
    func_0600C00C();
    func_0600C2EC();
    func_0600C114();
    func_060645A4();
    DAT_0605d7dc = 0x252000;
    switch (g_CurrentRoom.stageID) {
    case 0x6:
        ptr = g_StageAlternateMapNames[idx + 0];
        break;
    case 0xB:
        ptr = g_StageAlternateMapNames[idx + 2];
        break;
    case 0x9:
        ptr = g_StageAlternateMapNames[idx + 4];
        break;
    case 0x3:
        ptr = g_StageAlternateMapNames[idx + 7];
        break;
    case 0x26:
        ptr = g_StageAlternateMapNames[idx + 9];
        break;
    case 0x2B:
        ptr = g_StageAlternateMapNames[idx + 11];
        break;
    case 0x29:
        ptr = g_StageAlternateMapNames[idx + 13];
        break;
    case 0x23:
        ptr = g_StageAlternateMapNames[idx + 16];
        break;
    default:
        ptr = NULL;
        break;
    }
    DAT_0605d7dc += ReadFileToAddr(ptr, 0x252000);
    if (DAT_0605d7dc & 1) {
        DAT_0605d7dc++;
    }
    func_0601AC48();
}

void func_0606C064(void) { ReadFileToAddr("GAMEOVER.MAP", 0x00252000); }

INCLUDE_ASM("asm/saturn/game/f_nonmat", f606C088, func_0606C088);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f606C160, func_0606C160);

extern u16 UNK_Invincibility0[];

void func_0606C3E4(void) {
    SpriteObject* sprite;
    Entity* entity;
    s16 iFramePalette;

    for (entity = &g_Entities[0]; entity < &g_Entities[64]; entity++) {
        if (entity->unk0 != NULL) {
            entity->unk0->unk0C = entity->unk1D;
            entity->unk0->unk0D = entity->opacity;
        }
    }
    for (entity = &g_Entities[64]; entity < &g_Entities[256]; entity++) {
        if (entity->pfnUpdate == NULL) {
            continue;
        }
        if (entity->step) {
            if ((entity->flags & FLAG_UNK_10000) == 0) {
                continue;
            }
            if (entity->flags & 0xF) {
                iFramePalette = entity->nFramesInvincibility << 1;
                iFramePalette += entity->flags & 1;
                if (entity->unk0 != NULL) {
                    entity->unk0->clutBase = UNK_Invincibility0[iFramePalette];
                }
                entity->flags -= 1;
                if ((entity->flags & 0xF) == 0) {
                    if (entity->unk0 != NULL) {
                        entity->unk0->clutBase = entity->hitEffect;
                    }
                    entity->hitEffect = 0;
                }
            }
            sprite = entity->unk0;
            if (sprite != NULL) {
                sprite->unk0C = entity->unk1D;
                sprite->unk0D = entity->opacity;
                sprite->posX = entity->posX.val;
                sprite->posY = entity->posY.val;
            }
        }
        g_CurrentEntity = entity;
        entity->pfnUpdate(entity);
        entity->hitParams = 0;
        entity->hitFlags = 0;
    }
}

// func_0606C504
void ScrollEntitiesWithCamera(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    Entity* entity;
    s32 i;

    entity = &g_Entities[0];
    for (i = 0; i < TOTAL_ENTITY_COUNT; i++, entity++) {
        if (entity->unk68) {
            s32 temp = entity->unk68 * 0x100;
            entity->posX.val += arg0 * temp;
            entity->posY.val += arg1 * temp;
        } else {
            if (entity->flags & FLAG_POS_CAMERA_LOCKED) {
                entity->posX.i.hi += arg0;
                entity->posY.i.hi += arg1;
            }
            if (entity->flags & FLAG_POS_PLAYER_LOCKED) {
                entity->posX.val -= arg2;
                entity->posY.val -= arg3;
            }
        }
    }
}

INCLUDE_ASM("asm/saturn/game/f_nonmat", f606C594, func_0606C594);
INCLUDE_ASM("asm/saturn/game/f_nonmat", f606C774, func_0606C774);

s32 func_800F0CD8(s32 arg0) {
    u32 dy;
    s32 ret;
    s32 x, y;

    if (g_unkGraphicsStruct.unk20 == 0) {
        if (D_80097C98 == 2) {
            x = g_Tilemap.left * 0x140 + PLAYER.posX.i.hi;
            y = g_Tilemap.top * 0x100 + PLAYER.posY.i.hi;
            ret = SetNextRoomToLoad(x / 0x140, y / 0x100);
            D_801375BC.pos.x = x % 0x140;
            D_801375BC.pos.y = y % 0x100;
            return ret;
        }
        if (arg0) {
            if (g_PlayerX < g_Tilemap.x) {
                ret = SetNextRoomToLoad(
                    g_Tilemap.left - 1, g_Tilemap.top + g_PlayerY / 0x100);
                if (ret) {
                    D_801375BC.pos.x = PLAYER.posX.i.hi + 0x13C;
                    D_801375BC.pos.y = PLAYER.posY.i.hi;
                    g_Player.unk78 = 1;
                    g_CurrentRoom.unkC = g_Tilemap.left - 1;
                    g_CurrentRoom.unk10 = g_Tilemap.top + g_PlayerY / 0x100;
                    func_0606D798();
                    if (D_801375BC.def->tilesetId == 0xFF) {
                        return ret;
                    }
                    if (g_CurrentRoom.unk4 == 0x50) {
                        D_8003C708.flags = FLAG_UNK_40;
                    } else if (g_CurrentRoom.unk4 > 0x5F) {
                        D_8003C708.flags = g_CurrentRoom.unk4 - 0x41;
                        g_CurrentRoom.unk4 &= 0x60;
                    }
                    return ret;
                }
                g_PlayerX = g_Tilemap.x;
                PLAYER.posX.i.hi = 4;
            }
            if (g_PlayerX >= g_Tilemap.width) {
                ret = SetNextRoomToLoad(
                    g_Tilemap.right + 1, g_Tilemap.top + g_PlayerY / 0x100);
                if (ret) {
                    D_801375BC.pos.x = PLAYER.posX.i.hi - 0x13C;
                    D_801375BC.pos.y = PLAYER.posY.i.hi;
                    g_Player.unk78 = 1;
                    g_CurrentRoom.unkC = g_Tilemap.right + 1;
                    g_CurrentRoom.unk10 = g_Tilemap.top + g_PlayerY / 0x100;
                    func_0606D6DC();
                    if (D_801375BC.def->tilesetId == 0xFF) {
                        return ret;
                    }
                    if (g_CurrentRoom.unk4 == 0x50) {
                        D_8003C708.flags = 0x41;
                    } else if (g_CurrentRoom.unk4 > 0x5F) {
                        D_8003C708.flags = g_CurrentRoom.unk4 - 0x41;
                        g_CurrentRoom.unk4 &= 0x60;
                    }
                    if (g_CurrentRoom.stageID == 0x41) {
                        if (g_CurrentRoom.unk6 == 0x12) {
                            g_CurrentRoom.unkC = 2;
                            g_CurrentRoom.unk10 = 0x28;
                        }
                    }
                    return ret;
                }
                g_PlayerX = g_Tilemap.width - 1;
                PLAYER.posX.i.hi = 0x13C;
            }
        } else {
            goto block_25;
        }
    }

    if (g_PlayerY < g_Tilemap.y + 4) {
        ret = SetNextRoomToLoad(
            g_Tilemap.left + g_PlayerX / 0x140, g_Tilemap.top - 1);
        if (ret) {
            D_801375BC.pos.x = PLAYER.posX.i.hi;
            D_801375BC.pos.y = PLAYER.posY.i.hi + 0xD0;
            g_PlayerY -= 0x80;
            g_Player.unk78 = 2;
            g_CurrentRoom.unkC = g_Tilemap.left + g_PlayerX / 0x140;
            g_CurrentRoom.unk10 = g_Tilemap.top - 1;
            return ret;
        }
        g_PlayerY = g_Tilemap.y + 4;
        PLAYER.posY.i.hi = 0;
    }

    if (!(g_Player.vram_flag & TOUCHING_GROUND) &&
        !(g_Player.status &
          (PLAYER_STATUS_MIST_FORM | PLAYER_STATUS_BAT_FORM))) {
        dy = 24;
    } else {
        dy = 48;
    }
    if (g_PlayerY >= (g_Tilemap.height - dy) + 0x14) {
        ret = SetNextRoomToLoad(
            g_Tilemap.left + g_PlayerX / 0x140, g_Tilemap.bottom + 1);
        if (ret) {
            D_801375BC.pos.x = PLAYER.posX.i.hi;
            D_801375BC.pos.y = PLAYER.posY.i.hi - (0x100 - dy);
            g_PlayerY += 0x80;
            g_Player.unk78 = 2;
            g_CurrentRoom.unkC = g_Tilemap.left + g_PlayerX / 0x140;
            g_CurrentRoom.unk10 = g_Tilemap.bottom + 1;
            return ret;
        }
        g_PlayerY = (g_Tilemap.height - dy) + 0x13;
        PLAYER.posY.i.hi = 0x10F - dy;
    }

block_25:
    if (g_PlayerX < g_Tilemap.x + g_unkGraphicsStruct.unk14) {
        if (arg0 && g_Tilemap.hSize != 1) {
            if (g_PlayerX + D_801375A4 >
                g_Tilemap.x + g_unkGraphicsStruct.unk14) {
                PLAYER.posX.i.hi += (g_PlayerX + D_801375A4) -
                                    (g_Tilemap.x + g_unkGraphicsStruct.unk14);
            }
        }
        g_Tilemap.scrollX.i.hi = g_Tilemap.x;
    } else if (
        g_PlayerX > g_Tilemap.width + g_unkGraphicsStruct.unk14 - 0x140) {
        if (arg0 && g_Tilemap.hSize != 1) {
            if (g_PlayerX + D_801375A4 <
                g_Tilemap.width + g_unkGraphicsStruct.unk14 - 0x140) {
                PLAYER.posX.i.hi +=
                    (g_PlayerX + D_801375A4) -
                    (g_Tilemap.width + g_unkGraphicsStruct.unk14 - 0x140);
            }
        }
        g_Tilemap.scrollX.i.hi = g_Tilemap.width - 0x140;
    } else {
        g_Tilemap.scrollX.i.hi = g_PlayerX - g_unkGraphicsStruct.unk14;
        PLAYER.posX.i.hi = g_unkGraphicsStruct.unk14;
    }

    if (g_unkGraphicsStruct.unk24 != 0) {
        if (g_PlayerY < g_Tilemap.y + 0x8C) {
            g_Tilemap.scrollY.i.hi = g_Tilemap.y + 4;
            PLAYER.posY.i.hi = g_PlayerY - g_Tilemap.scrollY.i.hi;
        } else if (g_PlayerY > g_Tilemap.height - 0x74) {
            g_Tilemap.scrollY.i.hi = g_Tilemap.height - 0xFC;
            PLAYER.posY.i.hi = g_PlayerY - g_Tilemap.scrollY.i.hi;
        } else {
            g_Tilemap.scrollY.i.hi = g_PlayerY - 0x88;
            PLAYER.posY.i.hi = 0x88;
        }
    } else {
        if (g_PlayerY < g_Tilemap.y + 0x8C) {
            if (g_Tilemap.scrollY.i.hi - (g_PlayerY - 0x88) >= 4 &&
                g_Tilemap.scrollY.i.hi > g_Tilemap.y + 8) {
                g_Tilemap.scrollY.i.hi -= 4;
                PLAYER.posY.i.hi += 4;
            } else if (
                g_Tilemap.scrollY.i.hi < g_Tilemap.y && g_Tilemap.y != 0) {
                g_Tilemap.scrollY.i.hi += 4;
                PLAYER.posY.i.hi -= 4;
            } else {
                g_Tilemap.scrollY.i.hi = g_Tilemap.y + 4;
                PLAYER.posY.i.hi = g_PlayerY - g_Tilemap.scrollY.i.hi;
            }
        } else {
            s16* temp_a0 = &g_Tilemap.scrollY.i.hi;
            s16* temp_a3 = &PLAYER.posY.i.hi;
            if (g_PlayerY > g_Tilemap.height - 0x74) {
                g_Tilemap.scrollY.i.hi = g_Tilemap.height - 0xFC;
                PLAYER.posY.i.hi = g_PlayerY - g_Tilemap.scrollY.i.hi;
            } else if (g_Tilemap.scrollY.i.hi - (g_PlayerY - 0x88) >= 4) {
                *temp_a0 -= 4;
                *temp_a3 += 4;
            } else {
                g_Tilemap.scrollY.i.hi = g_PlayerY - 0x88;
                PLAYER.posY.i.hi = 0x88;
            }
        }
    }
    return 0;
}

INCLUDE_ASM("asm/saturn/game/f_nonmat", f606D058, SetNextRoomToLoad);

s32 FindBossTeleport(s32 chunkX, s32 chunkY) {
    RoomBossTeleport* ptr;

    for (ptr = &g_RoomBossTeleports[0]; true; ptr++) {
        if (ptr->x == 0x80) {
            return 0;
        }
        if (ptr->x != chunkX || ptr->y != chunkY ||
            ptr->stageId != g_CurrentRoom.stageID) {
            continue;
        }
        if (ptr->eventId == 0xFF) {
            if (g_PlayableCharacter == 0) {
                return ptr->castleFlag + 2;
            }
        } else {
            if (TimeAttackController(ptr->eventId, 0) == 0) {
                return ptr->castleFlag + 2;
            }
        }
    }
}

// SAT: func_0606D358
void func_800F2404(s32 arg0) {
    u32 i;

    switch (arg0) {
    case 0:
        g_unkGraphicsStruct.BottomCornerTextTimer = 0;
        g_unkGraphicsStruct.primIndex = 0;
        g_unkGraphicsStruct.D_800973FC = 0;
        /* fallthrough */
    case 1:
        g_CutsceneHasControl = 0;
        g_unkGraphicsStruct.pauseEnemies = 0;
        g_unkGraphicsStruct.unk20 = 0;
        g_unkGraphicsStruct.unk14 = 0xA0;
        g_unkGraphicsStruct.unk24 = 0;
        if (g_unkGraphicsStruct.BottomCornerTextTimer != 0) {
            FreePrimitives(g_unkGraphicsStruct.BottomCornerTextPrims);
        }
        g_unkGraphicsStruct.BottomCornerTextTimer = 0;
        g_unkGraphicsStruct.BottomCornerTextPrims = 0;
        for (i = 0; i < 8; i++) {
            g_unkGraphicsStruct.D_80097428[i] = 0;
        }
        g_unkGraphicsStruct.unk28 = 0;
        g_unkGraphicsStruct.unk2C = 0;
        g_unkGraphicsStruct.D_80097448 = 0;
        g_unkGraphicsStruct.D_8009744C = 0;
        g_unkGraphicsStruct.D_80097450 = 0;
        func_0600FB34();
        func_060195F0();
        DAT_0605c6e4 = 0;
        break;
    }
}

// original name: PSX_POSITION_GET
void func_0606D3FC(void) {
    RoomTeleport* ptr;
    s32 newY;

    if ((D_8003C730 != 0) && (D_8003C708.flags != 0)) {
        PLAYER.posX.i.hi = 0xA0;
        PLAYER.posY.i.hi = 0xB0;
        if (g_CurrentRoom.stageID & 0x20) {
            PLAYER.posY.i.hi += 0x10;
        }
        return;
    }

    ptr = &g_RoomTeleports[D_8006C374];
    PLAYER.posX.i.hi = ptr->x;
    PLAYER.posY.i.hi = ptr->y;
    if ((g_CurrentRoom.stageID & 0x30) == 0x20 &&
        (g_CurrentRoom.unk2 & 0x10) == 0) {
        u8* defBytes = (u8*)D_801375BC.def;
        s32 width = defBytes[-2] - defBytes[-4];
        s32 height = defBytes[-1] - defBytes[-3];

        PLAYER.posX.i.hi = (width + 1) * 0x140 - ptr->x;
        newY = height * 0x100 - (ptr->y & 0xFF00);

        if (D_80097C98 == 4) {
            newY |= 0x47;
        } else if (g_CurrentRoom.stageID == 0x28) {
            newY |= 0xD0;
        } else if (g_CurrentRoom.stageID == 0x20 && D_8006C374 == 0x31) {
            newY |= 0x30;
        } else if (D_8006C374 == 0x32) {
            newY = 0xB3;
        } else {
            if (newY == 0) {
                if (newY != height) {
                    newY = 0x88;
                } else {
                    newY = 0x84;
                }
            } else {
                if (newY == height) {
                    newY |= 0x84;
                } else {
                    newY |= 0x88;
                }
            }
        }
        PLAYER.posY.i.hi = newY;
    }
}

// original name: PSX_TO_STAGE_NO_GET
void func_0606D554(s32 arg0) {
    RoomTeleport* ptr;

    ptr = &g_RoomTeleports[D_8006C374];

    if (D_8003C730 == 0) {
        if (D_80097C98 == 4) {
            g_CurrentRoom.stageID = 0x2B;
        } else if (D_80097C98 == 5) {
            g_CurrentRoom.stageID = 11;
        } else if (D_80097C98 == 6) {
            g_CurrentRoom.stageID = 0x40;
        } else if (arg0 != 0x0) {
            g_CurrentRoom.stageID = ptr->stageId;
            if ((g_CurrentRoom.stageID & 0x10) != 0x10 &&
                (g_CurrentRoom.unk2 & 0x20) == 0x20) {
                g_CurrentRoom.stageID ^= 0x20;
            }
        }
        D_801375BC.def = DAT_0606459c + ptr->roomId + 4;
        g_CurrentRoom.unk4 = D_801375BC.def->tileLayoutId;
    }
}

// func_0606D5FC
void HandleRoomTransitionTrigger(void) {
    RoomTeleport* ptr;

    if ((D_8003C708.flags & FLAG_UNK_40) == 0) {
        return;
    }
    if (D_8003C708.unk2 != 0 &&
        (PLAYER.posX.i.hi < 8 || PLAYER.posX.i.hi > 0x318)) {
        return;
    }
    switch (D_8003C708.unk2) {
    case 0:
        ptr = &g_RoomTeleports[D_8006C374];
        D_8003C708.unk4 = ptr->stageId;
        if (g_CurrentRoom.stageID & 0x20) {
            D_8003C708.unk4 ^= 0x20;
        }
        D_8003C708.zPriority = ptr->reloadStageId;
        if (g_CurrentRoom.stageID & 0x20) {
            D_8003C708.zPriority ^= 0x20;
        }
        if (D_8003C708.flags == FLAG_UNK_40) {
            g_Player.demo_timer = 0x18;
            g_Player.padSim = 0x4000;
        } else {
            g_Player.demo_timer = 0x18;
            g_Player.padSim = 0x8000;
        }
        D_8003C708.unk2++;
        break;
    case 1:
        D_8003C708.unk2++;
        break;
    case 2:
    case 3:
        break;
    }
}

void func_0606D6DC(void) {
    if (g_CurrentRoom.stageID == 6 && g_CurrentRoom.unk8 == 0) {
        switch (g_CurrentRoom.unk4) {
        case 2:
        case 3:
        case 9:
        case 10:
            g_CurrentRoom.unkC--;
            break;
        case 8:
            if (g_CurrentRoom.unkA == 0 && g_CurrentRoom.unk6 == 1) {
                g_CurrentRoom.unkC--;
            }
            break;
        }
    } else if (g_CurrentRoom.stageID == 0x2B && g_CurrentRoom.unk8 != 0) {
        switch (g_CurrentRoom.unk4) {
        case 1:
            if (g_CurrentRoom.unk6 == 0 || g_CurrentRoom.unk6 == 2 ||
                g_CurrentRoom.unk6 == 3 || g_CurrentRoom.unk6 == 4) {
                g_CurrentRoom.unkC--;
            }
            break;
        }
    }
}

void func_0606D798(void) {
    if (g_CurrentRoom.stageID == 6 && g_CurrentRoom.unk8 == 0) {
        if (g_CurrentRoom.unk4 != 8) {
            if (g_CurrentRoom.unk4 != 9) {
                return;
            }
            g_CurrentRoom.unkC++;
        } else {
            if (g_CurrentRoom.unk6 != 2) {
                return;
            }
            g_CurrentRoom.unkC++;
        }
    } else if (g_CurrentRoom.stageID == 0x26 && g_CurrentRoom.unk8 == 0) {
        if (g_CurrentRoom.unk4 != 2) {
            if (g_CurrentRoom.unk4 != 3) {
                return;
            }
        }
        g_CurrentRoom.unkC++;
    }
}

// func_0606D804
s32 GetRoomLoadDefTable(u16 arg0) {
    s32 ret;

    ret = DAT_0606459c;

    switch (arg0) {
    case 6:
        if (g_CurrentRoom.unk8 != 0) {
            ret += 0x6C;
        }
        break;
    case 9:
        if (g_CurrentRoom.unk8 == 1) {
            ret += 0x42;
        } else if (g_CurrentRoom.unk8 == 2) {
            ret += 0x114;
        }
        break;
    case 3:
    case 11:
        if (g_CurrentRoom.unk8 != 0) {
            ret += 0x66;
        }
        break;
    }
    return ret;
}

static bool IsAlucart(void) {
    if (CheckEquipmentItemCount(0xAB, 0) && CheckEquipmentItemCount(0xAA, 0) &&
        CheckEquipmentItemCount(0x5B, 2))
        return true;
    return false;
}

// func_0606D880
void UpdateEquipStatBonuses(void) {
    s32* statsPtr;
    s32 correctStonesEquipped;
    s32 hourOfDay;
    s32 i, j;
    s32 statBonus;

    statsPtr = g_Status.statsEquip;
    for (i = 0; i < 4; i++) {
        *statsPtr++ = 0;
    }

    // Iterate through each Item Slot
    for (i = 0; i < 5; i++) {
        // Iterate through the 4 stats (STR, CON, INT, LCK)
        for (j = 0; j < 4; j++) {
            statBonus =
                g_AccessoryDefs[g_Status.equipment[3 + i]].statsBonus[j];
            if (statBonus > 0x80) {
                statBonus -= 0x100;
            }
            g_Status.statsEquip[j] += statBonus;
        }
    }

    // different
    hourOfDay = (DAT_06057f62 / 16) * 10 + DAT_06057f62 % 16;

    // Hours of sunstone effectiveness
    if (6 <= hourOfDay && hourOfDay < 18) {
        // Sunstone check
        correctStonesEquipped = CheckEquipmentItemCount(0x3C, 4);
        statsPtr = g_Status.statsEquip;
        for (i = 0; i < 4; i++) {
            *statsPtr++ += correctStonesEquipped * 5;
        }
    } else {
        // Moonstone check
        correctStonesEquipped = CheckEquipmentItemCount(0x3B, 4);
        statsPtr = g_Status.statsEquip;
        for (i = 0; i < 4; i++) {
            *statsPtr++ += correctStonesEquipped * 5;
        }
    }

    if (g_StatBuffTimers[4]) {
        g_Status.statsEquip[0] += 20;
    }
    if (g_StatBuffTimers[3]) {
        g_Status.statsEquip[2] += 20;
    }
    if (g_StatBuffTimers[2]) {
        g_Status.statsEquip[3] += 20;
    }
    if (g_Status.relics[0x1B] & 2) {
        g_Status.statsEquip[1] += 10;
    }
    if (g_Status.relics[0x1D] & 2) {
        g_Status.statsEquip[3] += 10;
    }
    if (g_Status.relics[0x1A] & 2) {
        g_Status.statsEquip[0] += 10;
    }
    if (g_Status.relics[0x1C] & 2) {
        g_Status.statsEquip[2] += 10;
    }
    if (IsAlucart()) {
        g_Status.statsEquip[3] += 30;
    }

    for (i = 0; i < 4; i++) {
        if (g_Status.statsEquip[i] > 99) {
            g_Status.statsEquip[i] = 99;
        }
        g_Status.statsTotal[i] = g_Status.statsBase[i] + g_Status.statsEquip[i];
    }

    g_Status.statsTotal[1] = g_Status.statsBase[1] + g_Status.statsEquip[1] * 8;
    g_Status.statsTotal[2] = g_Status.statsBase[2] + g_Status.statsEquip[2] * 4;
    for (i = 0; i < 4; i++) {
        if (g_Status.statsTotal[i] < 0) {
            g_Status.statsTotal[i] = 0;
        }
    }
}

s32 CalcAttack(s32 equipId, s32 otherEquipId) {
    s32 i;
    s16 equipmentAttackBonus;
    s16 totalAttack;
    s16 strengthStat;

    if (g_EquipDefs[equipId].itemCategory == 6 ||
        g_EquipDefs[equipId].itemCategory == 10) {
        return 0;
    }

    if (g_EquipDefs[equipId].itemCategory == 9 &&
        g_EquipDefs[equipId].attack == 1) {
        return 0;
    }

    if (equipId == 0x10) {
        return 0;
    }

    equipmentAttackBonus = 0;

    for (i = 0; i < 5; i++) {
        equipmentAttackBonus +=
            g_AccessoryDefs[g_Status.equipment[3 + i]].attBonus;
    }

    totalAttack = g_EquipDefs[equipId].attack;
    strengthStat = g_Status.statsTotal[0];

    if (totalAttack <= strengthStat) {
        totalAttack += strengthStat;
    } else {
        totalAttack += strengthStat / 2;
    }

    totalAttack += equipmentAttackBonus;

    switch (equipId) {
    case 0x7F:
        totalAttack += g_Status.timerHours;
        break;
    case 0x8F:
        totalAttack += SquareRoot0(g_Status.D_80097C40);
        break;
    case 4:
        if (g_EquipDefs[otherEquipId].itemCategory == 9) {
            totalAttack += 5;
        }
        break;
    case 0x80:
        totalAttack += g_Status.statsFamiliars[4].level;
        break;
    case 0x6F: {
        s32 j;
        s32 sVar3 = 0;
        for (j = 0; j < 2; j++) {
            s32 index = g_Status.equipment[6 + j] - 0x40;
            if (index < 0) {
                continue;
            }
            if (index < 7) {
                sVar3 += g_JewelSwordAttackBonus[index];
            }
        }
        totalAttack += sVar3;
    } break;
    }

    if (g_StatBuffTimers[1]) {
        totalAttack += 20;
    }
    if (totalAttack < 0) {
        totalAttack = 0;
    }
    if (totalAttack > 999) {
        totalAttack = 999;
    }
    return totalAttack;
}

void make_att(void) {
    s32 i;

    for (i = 0; i < 2; i++) {
        s32 equipId = g_Status.equipment[i];
        s32 otherEquipId = g_Status.equipment[1 - i];
        g_Status.attackHands[i] = CalcAttack(equipId, otherEquipId);
    }
}

void CalcDefense(void) {
    Accessory* acc;
    s32 thisHandItem;
    s32 i;
    s16 totalDefense;

    totalDefense = 0;
    g_Status.elementsWeakTo = 0;
    g_Status.elementsResist = 0;
    g_Status.elementsImmune = 0;
    g_Status.elementsAbsorb = 0;

    // Iterate over player's hands, hand 0 and hand 1.
    for (i = 0; i < 2; i++) {
        thisHandItem = g_Status.equipment[i];
        totalDefense += g_EquipDefs[thisHandItem].defense;
        // If this hand is shield rod and other hand is a shield, defense bonus
        // of 2.
        if (thisHandItem == 4 &&
            g_EquipDefs[g_Status.equipment[1 - i]].itemCategory == 9) {
            totalDefense += 2;
        }
    }
    // Iterate over accessories worn by player
    for (i = 0; i < 5; i++) {
        acc = &g_AccessoryDefs[g_Status.equipment[i + 3]];
        totalDefense += acc->defBonus;
        g_Status.elementsWeakTo |= acc->weakToElements;
        g_Status.elementsResist |= acc->resistElements;
        g_Status.elementsImmune |= acc->immuneElements;
        g_Status.elementsAbsorb |= acc->absorbElements;
    }

    if (CheckEquipmentItemCount(13, 0) != 0) {
        g_Status.elementsImmune |= 0x200;
    }
    if (CheckEquipmentItemCount(15, 0) != 0) {
        g_Status.elementsImmune |= 0x8000;
    }
    if (g_Status.relics[0x19] & 2) {
        g_Status.elementsImmune |= 0x100;
    }
    if (g_StatBuffTimers[5]) {
        g_Status.elementsResist |= 0x8000;
    }
    if (g_StatBuffTimers[6]) {
        g_Status.elementsResist |= 0x2000;
    }
    if (g_StatBuffTimers[7]) {
        g_Status.elementsResist |= 0x4000;
    }
    if (g_StatBuffTimers[8]) {
        g_Status.elementsResist |= 0x100;
    }
    if (g_StatBuffTimers[9]) {
        g_Status.elementsResist |= 0x1000;
    }
    if (g_StatBuffTimers[10]) {
        g_Status.elementsImmune |= 0x200;
    }
    if (g_StatBuffTimers[11]) {
        g_Status.elementsResist |= 0x800;
    }

    totalDefense += SquareRoot0(g_Status.statsTotal[1]) - 2;

    if (CheckEquipmentItemCount(19, 2) != 0) {
        totalDefense += g_RoomCount / 60;
    }

    if (g_StatBuffTimers[0]) {
        totalDefense += 20;
    }
    if (totalDefense < 0) {
        totalDefense = 0;
    }
    if (totalDefense > 999) {
        totalDefense = 999;
    }
    g_Status.defenseEquip = totalDefense;
}

void make_all(void) {
    UpdateEquipStatBonuses();
    make_att();
    CalcDefense();
}

void CheckWeaponCombo(void) {
    s32 i;

    u32 handFlag = 0x80000000; // right hand

    s32 leftHand = g_Status.equipment[LEFT_HAND_SLOT];
    s32 rightHand = g_Status.equipment[RIGHT_HAND_SLOT];

    u32 combo =
        g_EquipDefs[leftHand].comboSub & g_EquipDefs[rightHand].comboMain;

    if (combo != 0) {
        handFlag = 0;
    }
    combo |= g_EquipDefs[leftHand].comboMain & g_EquipDefs[rightHand].comboSub;

    if (combo != 0) {
        for (i = 0xB1; i < 0xE4; i++) {
            if (combo & g_EquipDefs[i].comboSub) {
                D_8013AEE4 = handFlag + i;
                return;
            }
        }
    }
    D_8013AEE4 = 0;
}

// original name: servant_work_clear
void ServantWorkClear(void) {
    s32 i;
    Entity* entity;

    entity = &g_Entities[4];
    for (i = 4; i < STAGE_ENTITY_START; i++, entity++) {
        u16 entityID = entity->entityId;
        if (entityID >= 0xD0 && entityID < 0xE0) {
            DestroyEntity(entity);
        }
    }
}

void init_work_sub_out_p(void) {
    s32 i;
    Entity* entity;

    entity = &g_Entities[0];
    for (i = 0; i < STAGE_ENTITY_START; i++, entity++) {
        u16 entityID = entity->entityId;
        if (entityID >= 0xE0 && entityID < 0x100) {
            DestroyEntity(entity);
        }
    }
}
