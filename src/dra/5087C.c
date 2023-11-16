#include "dra.h"

s32 func_800F087C(u32 chunkX, u32 chunkY) {
    RoomBossTeleport* phi_s1;
    s32 res;

    for (phi_s1 = D_800A297C; true; phi_s1++) {
        if (phi_s1->x == 0x80) {
            return 0;
        }

        res = phi_s1->x == chunkX;
        if (res && phi_s1->y == chunkY && phi_s1->stageId == g_StageId &&
            (phi_s1->eventId == TIMEATTACK_EVENT_INVALID ||
             TimeAttackController(phi_s1->eventId, TIMEATTACK_GET_RECORD) ==
                 0)) {
            return phi_s1->unk10 + 2;
        }
    }
}

// Performs calculations for background parallax
void func_800F0940(void) {
    s32 temp;

    switch (g_Tilemap.bg[0].scrollKind) {
    case 1:
        g_Tilemap.bg[0].scrollX.i.hi = g_Tilemap.cameraX.i.hi;
        g_Tilemap.bg[0].scrollY.i.hi = g_Tilemap.cameraY.i.hi;
        return;
    case 2:
        g_Tilemap.bg[0].scrollX.i.hi = (g_Tilemap.cameraX.i.hi / 2);
        g_Tilemap.bg[0].scrollY.i.hi = (g_Tilemap.cameraY.i.hi / 2) + 0x76;
        return;
    case 3:
        g_Tilemap.bg[0].scrollX.i.hi = g_Tilemap.cameraX.i.hi / 2;
        g_Tilemap.bg[0].scrollY.i.hi = g_Tilemap.cameraY.i.hi;
        return;
    case 4:
        g_Tilemap.bg[0].scrollX.i.hi = g_Tilemap.cameraX.i.hi;
        g_Tilemap.bg[0].scrollY.i.hi = g_Tilemap.cameraY.i.hi / 2;
        if (g_StageId == STAGE_RCHI) {
            g_Tilemap.bg[0].scrollY.i.hi += 0x80;
        }
        return;
    case 5:
        g_Tilemap.bg[0].scrollX.i.hi = g_Tilemap.cameraX.i.hi / 2;
        g_Tilemap.bg[0].scrollY.i.hi = g_Tilemap.cameraY.i.hi / 2;
        if (g_StageId == STAGE_RDAI) {
            g_Tilemap.bg[0].scrollX.i.hi += 0x80;
        }
        return;
    case 6:
        g_Tilemap.bg[0].scrollX.i.hi = g_Tilemap.cameraX.i.hi / 2;
        temp = (g_Tilemap.cameraY.i.hi / 2 - ((g_Tilemap.vSize - 1) << 7)) +
               (g_Tilemap.bg[0].h << 7);
        g_Tilemap.bg[0].scrollY.i.hi = temp;
        if (g_StageId == STAGE_RDAI) {
            g_Tilemap.bg[0].scrollX.i.hi += 0x80;
            g_Tilemap.bg[0].scrollY.i.hi = g_Tilemap.cameraY.i.hi / 2;
        }
        return;
    case 7:
        g_Tilemap.bg[0].scrollY.i.hi = 4;
        g_Tilemap.bg[0].scrollX.i.hi = g_Tilemap.cameraX.i.hi / 2;
        return;
    default:
        g_Tilemap.bg[0].scrollX.i.hi = 0;
        g_Tilemap.bg[0].scrollY.i.hi = 4;
        return;
    }
}

s32 SetNextRoomToLoad(u32 x, u32 y) {
    s32 res;
    RoomHeader* room;
    u32 stack[4];

    if (g_Player.unk0C & 0x40000) {
        return 0;
    }
    res = func_800F087C(x, y);
    if (res) {
        return res;
    }

    room = g_api.o.rooms;
    while (true) {
        if (room->left == 0x40) {
            return 0;
        }
        if (room->left <= x && room->top <= y && room->right >= x &&
            room->bottom >= y) {
            stack[0] = &room->load;
            if (room->load.tilesetId == 0xFF &&
                D_800A245C[room->load.tileLayoutId].stageId == STAGE_ST0) {
                return 0;
            }
            D_801375BC.def = &room->load;
            return 1;
        }
        room++;
    }
}

#ifndef NON_EQUIVALENT
INCLUDE_ASM("dra/nonmatchings/5087C", func_800F0CD8);
#else
extern s16 D_80072F98;
extern s32 D_801375A4;
extern s32 D_801375C0;
extern s32 D_801375C4;

s32 func_800F0CD8(s32 arg0) {
    s32 temp_a1;
    s32 temp_a1_2;
    s32 temp_v0;
    s32 new_var2;
    s32 var_s0;
    s32 var_v0;

    if (D_80097418 == 0) {
        if (D_80097C98 == 2) {
            var_v0 = SetNextRoomToLoad(
                (g_Entities[0].posX.i.hi >> 8) + g_Tilemap.left,
                (g_Entities[0].posY.i.hi >> 8) + g_Tilemap.top);
            D_801375C0 = (u8)g_Entities[0].posX.i.hi;
            D_801375C4 = (u8)g_Entities[0].posY.i.hi;
            return var_v0;
        }
        if (arg0 == 0) {
            goto block_25;
        }
        if (playerX < g_Tilemap.x) {
            var_v0 = SetNextRoomToLoad(
                g_Tilemap.left - 1, (playerY >> 8) + g_Tilemap.top);
            if (var_v0) {
                D_80072F98 = 1;
                D_801375C0 = g_Entities[0].posX.i.hi + 0x100;
                D_801375C4 = g_Entities[0].posY.i.hi;
                return var_v0;
            }
            g_Entities[0].posX.i.hi = 0;
            playerX = g_Tilemap.x;
        }
        if (playerX >= g_Tilemap.width) {
            var_v0 = SetNextRoomToLoad(
                g_Tilemap.right + 1, (playerY >> 8) + g_Tilemap.top);
            if (var_v0) {
                D_80072F98 = 1;
                D_801375C0 = g_Entities[0].posX.i.hi - 0x100;
                D_801375C4 = g_Entities[0].posY.i.hi;
                return var_v0;
            }
            g_Entities[0].posX.i.hi = 0xFF;
            playerX = g_Tilemap.width - 1;
        }
    }
    if (D_80097424 == 0) {
        if (playerY < g_Tilemap.y + 4) {
            temp_v0 = SetNextRoomToLoad(
                (playerX >> 8) + g_Tilemap.left, g_Tilemap.top - 1);
            if (temp_v0 != false) {
                D_80072F98 = 2;
                D_801375C0 = g_Entities[0].posX.i.hi;
                D_801375C4 = g_Entities[0].posY.i.hi + 0xD0;
                playerY -= 0x80;
                return temp_v0;
            }
            g_Entities[0].posY.i.hi = 0;
            playerY = g_Tilemap.y + 4;
        }
        var_s0 = 0x30;
        if ((!(*g_Player.pl_vram_flag & 1)) && !(g_Player.unk0C & 3)) {
            var_s0 = 0x18;
        }
        if (playerY >= ((g_Tilemap.height - var_s0) + 0x14)) {
            temp_v0 = SetNextRoomToLoad(
                (playerX >> 8) + g_Tilemap.left, g_Tilemap.bottom + 1);
            if (temp_v0 != false) {
                D_80072F98 = 2;
                D_801375C0 = g_Entities[0].posX.i.hi;
                D_801375C4 = g_Entities[0].posY.i.hi - 0x100;
                D_801375C4 = D_801375C4 + var_s0;
                playerY += 0x80;
                return temp_v0;
            }
            g_Entities[0].posY.i.hi = 0x10F - var_s0;
            playerY = g_Tilemap.height - var_s0 + 0x13;
        }
    }
block_25:
    temp_a1 = g_Tilemap.x + *D_8009740C;

    if (playerX < temp_a1) {
        if (arg0 != 0 && g_Tilemap.hSize != 1 &&
            temp_a1 < playerX + D_801375A4) {
            g_Entities[0].posX.i.hi =
                (u16)g_Entities[0].posX.i.hi +
                (playerX + D_801375A4 - (g_Tilemap.x + *D_8009740C));
        }
        g_Tilemap.cameraX.i.hi = g_Tilemap.x;
    } else {
        temp_a1_2 = g_Tilemap.width + *D_8009740C - 0x100;
        if (temp_a1_2 < playerX) {
            if (arg0 != 0 && g_Tilemap.hSize != 1 &&
                playerX + D_801375A4 < temp_a1_2) {
                g_Entities[0].posX.i.hi =
                    ((u16)g_Entities[0].posX.i.hi) +
                    (((playerX + D_801375A4) + 0x100) -
                     (g_Tilemap.width + (*D_8009740C)));
            }
            g_Tilemap.cameraX.i.hi = g_Tilemap.width - 0x100;
        } else {
            g_Tilemap.cameraX.i.hi = playerX - (*D_8009740C);
            g_Entities[0].posX.i.hi = *D_8009740C;
        }
    }
    if (D_8009741C != 0) {
        if (playerY < g_Tilemap.y + 0x8C) {
            g_Tilemap.cameraY.i.hi = g_Tilemap.y + 4;
            g_Entities[0].posY.i.hi = playerY - g_Tilemap.cameraY.i.hi;
        } else if (g_Tilemap.height - 0x74 < playerY) {
            g_Tilemap.cameraY.i.hi = g_Tilemap.height - 0xFC;
            g_Entities[0].posY.i.hi = playerY - g_Tilemap.cameraY.i.hi;
        } else {
            g_Entities[0].posY.i.hi = 0x88;
            g_Tilemap.cameraY.i.hi = playerY - 0x88;
        }
    } else {
        new_var2 = 0x88;
        if (playerY < g_Tilemap.y + 0x8C) {
            if (g_Tilemap.cameraY.i.hi + new_var2 - playerY >= 4 &&
                g_Tilemap.y + 8 < g_Tilemap.cameraY.i.hi) {
                g_Tilemap.cameraY.i.hi -= 4;
                g_Entities[0].posY.i.hi += 4;
            } else if (
                g_Tilemap.cameraY.i.hi < g_Tilemap.y && g_Tilemap.y != 0) {
                g_Tilemap.cameraY.i.hi += 4;
                g_Entities[0].posY.i.hi -= 4;
            } else {
                g_Tilemap.cameraY.i.hi = g_Tilemap.y + 4;
                g_Entities[0].posY.i.hi = playerY - g_Tilemap.cameraY.i.hi;
            }
        } else {
            g_Entities[0].posY.i.hi = g_Tilemap.cameraY.i.hi;
            if (g_Tilemap.height - 0x74 < playerY) {
                g_Tilemap.cameraY.i.hi = g_Tilemap.height - 0xFC;
                g_Entities[0].posY.i.hi = playerY - g_Tilemap.cameraY.i.hi;
            } else if (g_Tilemap.cameraY.i.hi + new_var2 - playerY >= 4) {
                g_Tilemap.cameraY.i.hi -= 4;
                g_Entities[0].posY.i.hi += 4;
            } else {
                g_Entities[0].posY.i.hi = 0x88;
                g_Tilemap.cameraY.i.hi = playerY - 0x88;
            }
        }
    }
    return false;
}
#endif

void func_800F1424(void) {
    if (g_pads[1].tapped & PAD_R1) {
        g_Tilemap.flags ^= 2;
    }
    if (g_pads[1].tapped & PAD_L1) {
        g_Tilemap.flags ^= 1;
    }
    if ((g_pads[1].tapped & PAD_L2) && (g_Tilemap.bg[0].tileDef != 0)) {
        g_Tilemap.bg[0].flags ^= 1;
    }
}

void func_800F14CC(void) {
    RoomTeleport* temp_a2;
    s32 temp_a1;
    s32 newY;

    if (D_8003C730 == 1) {
        PLAYER.posX.i.hi = 0x80;
        PLAYER.posY.i.hi = 0xA4;
        if (g_StageId & 0x20) {
            PLAYER.posY.i.hi = 0xB4;
        }
        SetNextRoomToLoad(g_Tilemap.left, g_Tilemap.top);
        return;
    }
    if (D_8003C730 == 2) {
        PLAYER.posX.i.hi = 0x74;
        PLAYER.posY.i.hi = 0xA4;
        SetNextRoomToLoad(g_Tilemap.left, g_Tilemap.top);
        return;
    }
    temp_a2 = &D_800A245C[D_8006C374];
    do {
    } while (0);
    // TODO: !FAKE Ugly casts, need to work this out.
    D_801375BC.def =
        &((RoomHeader*)((u8*)g_api.o.rooms + temp_a2->roomId))->load;
    PLAYER.posX.i.hi = temp_a2->x;
    PLAYER.posY.i.hi = temp_a2->y;

    if (g_StageId & STAGE_INVERTEDCASTLE_FLAG) {
        temp_a1 =
            (D_801375BC.def - 1)->objLayoutId - (D_801375BC.def - 1)->tilesetId;
        PLAYER.posX.i.hi =
            (((D_801375BC.def - 1)->objGfxId -
              (D_801375BC.def - 1)->tileLayoutId + 1)
             << 8) -
            temp_a2->x;
        newY = (temp_a1 << 8) - (temp_a2->y & 0xFF00);
        if (D_80097C98 == 4) {
            newY |= 0x47;
        } else if (g_StageId == STAGE_RCEN) {
            newY |= 0xD0;
        } else if ((g_StageId == STAGE_RNO0) && (D_8006C374 == 7)) {
            newY |= 0x30;
        } else if (D_8006C374 == 8) {
            newY = 0xB3;
        } else if (newY == 0) {
            if (temp_a1 != 0) {
                newY = 0x88;
            } else {
                newY = 0x84;
            }
        } else if (newY == temp_a1) {
            newY |= 0x84;
        } else {
            newY |= 0x88;
        }
        PLAYER.posY.i.hi = newY;
    }
}

s32 func_800F16D0(void) {
    if (D_8003C730 != 0)
        return g_StageId;
    else if (D_80097C98 == 4)
        return STAGE_TOP | STAGE_INVERTEDCASTLE_FLAG;
    else if (D_80097C98 == 5)
        return STAGE_TOP;
    else if (D_80097C98 == 6)
        return STAGE_LIB;
    else {
        s32 stageId = D_800A245C[D_8006C374].stageId;
        if (g_StageId & STAGE_INVERTEDCASTLE_FLAG) {
            stageId ^= STAGE_INVERTEDCASTLE_FLAG;
        }
        return stageId;
    }
}

void func_800F1770(s8 arg0[], s32 arg1, s32 arg2, s32 isEnabled) {
    s32 temp_v0 = (arg1 / 2) + (arg2 * 4);

    if (!(arg1 & 1)) {
        arg0[temp_v0] = (arg0[temp_v0] & 0xF0) + isEnabled;
    } else {
        arg0[temp_v0] = (arg0[temp_v0] & 0xF) + (isEnabled * 0x10);
    }
}

u8 func_800F17C8(s8 arg0[], s32 arg1, s32 arg2) {
    s32 temp_v0 = (arg1 / 2) + (arg2 * 4);

    if (!(arg1 & 1)) {
        return (u8)arg0[temp_v0] & 0xF;
    } else {
        return (u8)arg0[temp_v0] >> 4;
    }
}

void func_800F180C(s32 x, s32 y, u8* dst) {
    s32 i, j;
    u8 *start, *curSrc, *src;

    start = CASTLE_MAP_PTR;
    start += x * 2;
    start += y * 4 * 128;
    for (i = 0; i < 5; i++, start += 0x80) {
        for (j = 0, src = start; j < 4; j++) {
            do {
                curSrc = src;
            } while (0);
            dst[4 * i + j] = curSrc[j];
        }
    }
}

void func_800F1868(s32 x, s32 y, u8* src) {
    s32 i;
    s32 j;
    u8* dst;
    u8* curDst;
    u8* start;

    start = CASTLE_MAP_PTR;
    start += x * 2;
    start += y * 4 * 128;
    for (i = 0; i < 5; i++, start += 0x80) {
        for (j = 0, dst = start; j < 4; j++) {
            do {
                curDst = dst;
            } while (0);
            curDst[j] = src[4 * i + j];
        }
    }
}

void func_800F18C4(s32 arg0, s32 arg1) {
    s8 sp10[20];
    s32 i;
    s32 j;

    func_800F180C(arg0, arg1, &sp10);

    for (i = 0; i < 4; i++) {
        for (j = 0; j < 5; j++) {
            func_800F1770(sp10, j, i, false);
        }
    }
    func_800F1868(arg0, arg1, &sp10);
}

void func_800F1954(s32 x, s32 y, s32 arg2) {
    u8 sp10[20];
    s32 i;
    s32 j;

    func_800F180C(x, y, sp10);
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 5; j++) {
            if (arg2 == 1 && j == 0) {
                func_800F1770(sp10, 0, i, false);
            } else if (arg2 != 2 && j == 4) {
                func_800F1770(sp10, 4, i, false);
            } else {
                func_800F1770(sp10, j, i, true);
            }
        }
    }
    func_800F1868(x, y, &sp10);
}

void func_800F1A3C(s32 arg0) {
    if (arg0 == 0) {
        func_800F18C4(0xE, 0x2B);
        func_800F18C4(0x10, 0x2B);
        func_800F18C4(0x2B, 0x2A);
        func_800F18C4(0x2C, 0x2A);
        func_800F18C4(0x2D, 0x2A);
        func_800F18C4(0x30, 0x2A);
    } else {
        func_800F1954(0xE, 0x2B, 0);
        func_800F1954(0x10, 0x2B, 1);
        func_800F1954(0x2B, 0x2A, 2);
        func_800F1954(0x2C, 0x2A, 2);
        func_800F1954(0x2D, 0x2A, 2);
        func_800F1954(0x30, 0x2A, 2);
    }
}

INCLUDE_ASM("dra/nonmatchings/5087C", func_800F1B08);

INCLUDE_ASM("dra/nonmatchings/5087C", func_800F1D54);

void func_800F1EB0(s32 arg0, s32 arg1, s32 arg2) {
    s32 data_0;
    s32 data_1;
    s32 data_2;
    s32 data_3;
    s32 data_4;
    u8* ptr;

    if (g_StageId & STAGE_INVERTEDCASTLE_FLAG) {
        arg0 = 0x3F - arg0;
        arg1 = 0x3F - arg1;
    }
    ptr = &D_800A2BC0;
    while (*ptr != 0) {
        data_0 = *ptr++;
        data_1 = *ptr++;
        data_2 = *ptr++;
        data_3 = *ptr++;
        data_4 = *ptr++;
        if (g_StageId & STAGE_INVERTEDCASTLE_FLAG) {
            data_3 = data_4;
        }
        if (data_3 != 0xFF) {
            if (arg2 != 0xFFFF) {
                if (arg2 == data_3) {
                    func_800F1D54(data_0, data_1, data_2, data_4);
                }
            } else if ((data_0 == arg0) && (data_1 == arg1) &&
                       (g_CastleFlags[data_3] != 0)) {
                func_800F1D54(data_0, data_1, data_2, data_4);
            }
        }
    }
}

void func_800F1FC4(s32 arg0) {
    func_800F1EB0(
        (playerX >> 8) + g_Tilemap.left, (playerY >> 8) + g_Tilemap.top, arg0);
}

void func_800F2014(void) {
    s32 x;
    s32 y;
    s32 subMap;
    s32 idx;
    s32 currMapRect;

    if ((D_8013AED0 != 0) && (g_StageId != STAGE_ST0)) {
        x = (playerX >> 8) + g_Tilemap.left;
        y = (playerY >> 8) + g_Tilemap.top;
        idx = (x >> 2) + (y * 16);
        subMap = 1 << ((3 - (x & 3)) * 2);
        if (g_StageId & STAGE_INVERTEDCASTLE_FLAG) {
            idx += 0x400;
        }
        currMapRect = g_CastleMap[idx];
        if (!(currMapRect & subMap)) {
            g_CastleMap[idx] = currMapRect | subMap;
            g_RoomCount++;
            func_800F1B08(x, y, 0);
            func_800F1EB0(x, y, 0xFFFF);
        }
    }
}

void func_800F2120(void) {
    s32 x;
    s32 y;
    s32 subMap;
    s32 idx;
    u8 currMapRect;

    func_800F1A3C(g_StageId & STAGE_INVERTEDCASTLE_FLAG);
    ClearImage(&g_Vram.D_800ACDE8, 0, 0, 0);
    DrawSync(0);

    for (y = 0; y < 64; y++) {
        for (x = 0; x < 64; x++) {
            idx = (x >> 2) + (y * 16);
            // sequence of 2 bit masks: 0xC0, 0x30, 0x0C, 0x03
            // 0b11000000, 0b110000, 0b1100, 0b11
            subMap = 3 << ((3 - (x & 3)) * 2);

            if (g_StageId & STAGE_INVERTEDCASTLE_FLAG) {
                idx += 0x400;
            }
            currMapRect = g_CastleMap[idx];
            // 0x55 and 0xAA are masks for even and odd bits.
            // 0x55 is 0b1010101
            if (currMapRect & 0x55 & subMap) {
                func_800F1B08(x, y, 0);
                func_800F1EB0(x, y, 0xFFFF);
                // 0xAA is 0b10101010
            } else if (currMapRect & 0xAA & subMap) {
                func_800F1B08(x, y, 1);
            }
        }
    }
}

void func_800F223C(void) {
    g_StageId ^= STAGE_INVERTEDCASTLE_FLAG;
    func_800F2120();
    g_StageId ^= STAGE_INVERTEDCASTLE_FLAG;
}

INCLUDE_ASM("dra/nonmatchings/5087C", func_800F2288);

void func_800F2404(s32 arg0) {
    s32* temp;
    s32* ptr;
    s32 count;

    if (arg0 == 0) {
        g_BottomCornerTextTimer = 0;
        D_800973F8 = 0;
        D_800973FC = 0;
    }

    temp = D_80097400;
    *temp = 0;
    D_8003C704 = 0;
    D_80097418 = 0;
    D_8009741C = 0;
    D_8009740C[0] = 0x80;

    if (g_BottomCornerTextTimer != 0) {
        FreePrimitives(g_BottomCornerTextPrims);
    }

    g_BottomCornerTextTimer = 0;
    g_BottomCornerTextPrims = 0;
    g_unkGraphicsStruct.g_zEntityCenter.unk = 148;
    count = 7;

    ptr = &D_80097400[17];

    while (count >= 0) {
        *ptr = 0;
        count -= 1;
        ptr -= 1;
    }

    D_80097420[0] = 0;
    D_80097424 = 0;
    D_80097448[0] = 0;
    D_80097448[1] = 0;
    D_80097450 = 0;
    func_800E346C();
}

#ifndef NON_EQUIVALENT
INCLUDE_ASM("dra/nonmatchings/5087C", func_800F24F4);
#else
void func_801042C4(s32);
void func_80105428();
extern s32 D_80137598;

void func_800F24F4(void) {
    s32 castleX;
    s32 castleY;
    s32 phi_v1;
    s32 phi_a0;

    castleX = ((s32)playerX >> 8) + g_Tilemap.left;
    castleY = ((s32)playerY >> 8) + g_Tilemap.top;
    if (D_8003C708 & 0x20) {
        phi_v1 = g_StageId;
        if (phi_v1 == (STAGE_NO0 | STAGE_INVERTEDCASTLE_FLAG)) {
            if ((castleX == phi_v1) && (castleY == 0x24)) {
                if (TimeAttackController(TIMEATTACK_EVENT_FINAL_SAVEPOINT,
                                         TIMEATTACK_GET_RECORD) == 0) {
                    TimeAttackController(TIMEATTACK_EVENT_FINAL_SAVEPOINT,
                                         TIMEATTACK_SET_RECORD);
                }
                phi_v1 = g_StageId;
            }
        }

        if (phi_v1 == (STAGE_NO4 | STAGE_INVERTEDCASTLE_FLAG) &&
            castleX == 0x12 && castleY == 0x1E) {
        } else {
            phi_a0 = 0;
            if (g_StageId == STAGE_NO4 && castleX == 0x2D && castleY == 0x21) {
                if (PLAYER.posX.val == 0x80) {
                    D_8003C730 = 1;
                    phi_a0 = 1;
                } else {
                    phi_a0 = 1;
                    if (TimeAttackController(TIMEATTACK_EVENT_ORLOX_DEFEAT,
                                             TIMEATTACK_GET_RECORD)) {
                        goto block_18;
                    }
                }
            }

            func_801042C4(phi_a0);
            D_80137598 = 1;
            func_80105428();
            return;
        }
    }
block_18:
    D_80137598 = 0;
}
#endif

INCLUDE_ASM("dra/nonmatchings/5087C", func_800F2658);

bool func_800F27F4(s32 arg0) {
    if (arg0 == 0) {
        if (D_800973FC != 0 || D_8006BB00 != 0 || D_8003C708.flags & 0x60) {
            return false;
        }
        D_801375C8 = 1;
        return true;
    }
    D_801375C8 = 8;
}

const u32 rodata_padding_3C530 = 0;
