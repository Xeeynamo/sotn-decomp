// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../dra/dra.h"
#include "../dra/dra_bss.h"
#include "servant.h"
#include "../dra/menu.h"

extern RoomBossTeleport D_800A297C[];
s32 func_800F087C(u32 chunkX, u32 chunkY) {
    RoomBossTeleport* phi_s1;

    for (phi_s1 = &D_800A297C[0]; true; phi_s1++) {
        if (phi_s1->x == 0x80) {
            return 0;
        }
        // All must match, otherwise we jump out.
        if (phi_s1->x != chunkX || phi_s1->y != chunkY ||
            phi_s1->stageId != g_StageId) {
            continue;
        }

        if (phi_s1->eventId == TIMEATTACK_EVENT_INVALID) {
            return phi_s1->unk10 + 2;
        }
        if (TimeAttackController(phi_s1->eventId, TIMEATTACK_GET_RECORD) == 0) {
            return phi_s1->unk10 + 2;
        }
    }
}

void func_800F0940(void) {
    switch (g_BgLayers[0].scrollKind) {
    case 1:
        g_BgLayers[0].scrollX.i.hi = g_Tilemap.scrollX.i.hi;
        g_BgLayers[0].scrollY.i.hi = g_Tilemap.scrollY.i.hi;
        break;
    case 2:
        g_BgLayers[0].scrollX.i.hi = (g_Tilemap.scrollX.i.hi / 2);
        g_BgLayers[0].scrollY.i.hi = (g_Tilemap.scrollY.i.hi / 2) + 0x76;
        break;
    case 3:
        g_BgLayers[0].scrollX.i.hi = g_Tilemap.scrollX.i.hi / 2;
        g_BgLayers[0].scrollY.i.hi = g_Tilemap.scrollY.i.hi;
        break;
    case 4:
        g_BgLayers[0].scrollX.i.hi = g_Tilemap.scrollX.i.hi;
        g_BgLayers[0].scrollY.i.hi = g_Tilemap.scrollY.i.hi / 2;
        if (g_StageId == STAGE_RCHI) {
            g_BgLayers[0].scrollY.i.hi += 0x80;
        }
        break;
    case 5:
        g_BgLayers[0].scrollX.i.hi = g_Tilemap.scrollX.i.hi / 2;
        g_BgLayers[0].scrollY.i.hi = g_Tilemap.scrollY.i.hi / 2;
        if (g_StageId == STAGE_RDAI) {
            g_BgLayers[0].scrollX.i.hi += 0x80;
        }
        break;
    case 6:
        g_BgLayers[0].scrollX.i.hi = g_Tilemap.scrollX.i.hi / 2;
        g_BgLayers[0].scrollY.i.hi =
            (g_Tilemap.scrollY.i.hi / 2 - ((g_Tilemap.vSize - 1) * 128)) +
            (g_BgLayers[0].h * 128);
        if (g_StageId == STAGE_RDAI) {
            g_BgLayers[0].scrollX.i.hi += 0x80;
            g_BgLayers[0].scrollY.i.hi = g_Tilemap.scrollY.i.hi / 2;
        }
        break;
    case 7:
        g_BgLayers[0].scrollX.i.hi = g_Tilemap.scrollX.i.hi / 2;
        g_BgLayers[0].scrollY.i.hi = 4;
        break;
    default:
        g_BgLayers[0].scrollX.i.hi = 0;
        g_BgLayers[0].scrollY.i.hi = 4;
        break;
    }
}
extern RoomLoadDefHolder D_801375BC;

s32 SetNextRoomToLoad(u32 x, u32 y) {
    s32 res;
    RoomHeader* room;
    RoomLoadDef* loader;
    RoomTeleport* tele;

    if (g_Player.status & PLAYER_STATUS_DEAD) {
        return 0;
    }
    res = func_800F087C(x, y);
    if (res) {
        return res;
    }
    // Look for the proper room at the xy coordinates.
    for (room = &g_api.o.rooms[0]; true; room++) {
        // Perhaps the final room gets a hard-coded value of 0x40?
        // Indicates no room found, return 0
        if (room->left == 0x40) {
            return 0;
        }
        // Now check the 4 coordinates. If x,y are beyond the room's
        // bounds, then this isn't the room we're looking for.
        if (x < room->left) {
            continue;
        }
        if (y < room->top) {
            continue;
        }
        if (x > room->right) {
            continue;
        }
        if (y > room->bottom) {
            continue;
        }
        // All 4 bounds passed. We found our room.

        // Don't know what this is testing for.
        loader = &room->load;
        if (loader->tilesetId == 0xFF) {
            tele = &D_800A245C[loader->tileLayoutId];
            if (tele->stageId == STAGE_ST0) {
                return 0;
            }
        }
        // Finally set this to the room we found, and return a success.
        D_801375BC.def = &room->load;
        return 1;
    }
}
extern s32 D_801375A4;
extern s32 D_801375C0;
extern s32 D_801375C4;
extern s32 D_801375C8;

s32 func_800F0CD8(s32 arg0) {
    s32 var_s0;
    s32 ret;

    if (!g_unkGraphicsStruct.unk18) {
        if (D_80097C98 == 2) {
            ret = SetNextRoomToLoad(g_Tilemap.left + (PLAYER.posX.i.hi >> 8),
                                    g_Tilemap.top + (PLAYER.posY.i.hi >> 8));
            D_801375C0 = PLAYER.posX.i.hi & 0xFF;
            D_801375C4 = PLAYER.posY.i.hi & 0xFF;
            return ret;
        }
        if (arg0) {
            if (g_PlayerX < g_Tilemap.x) {
                ret = SetNextRoomToLoad(
                    g_Tilemap.left - 1, g_Tilemap.top + (g_PlayerY >> 8));
                if (ret) {
                    if (PLAYER.posX.i.hi < 4) {
                        PLAYER.posX.i.hi = -1;
                        PLAYER.posX.i.lo = 0;
                    }
                    D_801375C0 = PLAYER.posX.i.hi + 256;
                    D_801375C4 = PLAYER.posY.i.hi;
                    g_Player.unk78 = 1;
                    return ret;
                } else {
                    g_PlayerX = g_Tilemap.x;
                    PLAYER.posX.i.hi = 0;
                }
            }
            if (g_PlayerX >= g_Tilemap.width) {
                ret = SetNextRoomToLoad(
                    g_Tilemap.right + 1, g_Tilemap.top + (g_PlayerY >> 8));
                if (ret) {
                    if (PLAYER.posX.i.hi > 252) {
                        PLAYER.posX.i.hi = 256;
                        PLAYER.posX.i.lo = 0;
                    }
                    D_801375C0 = PLAYER.posX.i.hi - 256;
                    D_801375C4 = PLAYER.posY.i.hi;
                    g_Player.unk78 = 1;
                    return ret;
                } else {
                    g_PlayerX = g_Tilemap.width - 1;
                    PLAYER.posX.i.hi = 255;
                }
            }
        } else {
            goto block_25;
        }
    }
    if (!g_unkGraphicsStruct.unk24) {
        if (g_PlayerY < g_Tilemap.y + 4) {
            ret = SetNextRoomToLoad(
                g_Tilemap.left + (g_PlayerX >> 8), g_Tilemap.top - 1);
            if (ret) {
                D_801375C0 = PLAYER.posX.i.hi;
                D_801375C4 = PLAYER.posY.i.hi + 208;
                g_PlayerY -= 128;
                g_Player.unk78 = 2;
                return ret;
            } else {
                g_PlayerY = g_Tilemap.y + 4;
                PLAYER.posY.i.hi = 0;
            }
        }
        var_s0 = 48;
        if (!(g_Player.vram_flag & 1) &&
            !(g_Player.status &
              (PLAYER_STATUS_BAT_FORM | PLAYER_STATUS_MIST_FORM))) {
            var_s0 = 24;
        }
        if (g_PlayerY >= g_Tilemap.height - var_s0 + 20) {
            ret = SetNextRoomToLoad(
                g_Tilemap.left + (g_PlayerX >> 8), g_Tilemap.bottom + 1);
            if (ret) {
                D_801375C0 = PLAYER.posX.i.hi;
                D_801375C4 = PLAYER.posY.i.hi - (256 - var_s0);
                g_PlayerY += 0x80;
                g_Player.unk78 = 2;
                return ret;
            } else {
                g_PlayerY = g_Tilemap.height - var_s0 + 0x13;
                PLAYER.posY.i.hi = 271 - var_s0;
            }
        }
    }
block_25:
    if (g_PlayerX < g_Tilemap.x + g_unkGraphicsStruct.unkC) {
        if (arg0 && g_Tilemap.hSize != 1) {
            if (g_Tilemap.x + g_unkGraphicsStruct.unkC <
                g_PlayerX + D_801375A4) {
                PLAYER.posX.i.hi += g_PlayerX + D_801375A4 -
                                    (g_Tilemap.x + g_unkGraphicsStruct.unkC);
            }
        }
        g_Tilemap.scrollX.i.hi = g_Tilemap.x;
    } else if (g_Tilemap.width + g_unkGraphicsStruct.unkC - 256 < g_PlayerX) {
        if (arg0 && g_Tilemap.hSize != 1) {
            if (g_PlayerX + D_801375A4 <
                g_Tilemap.width + g_unkGraphicsStruct.unkC - 256) {
                PLAYER.posX.i.hi +=
                    g_PlayerX + D_801375A4 -
                    (g_Tilemap.width + g_unkGraphicsStruct.unkC - 256);
            }
        }
        g_Tilemap.scrollX.i.hi = g_Tilemap.width - 256;
    } else {
        g_Tilemap.scrollX.i.hi = g_PlayerX - g_unkGraphicsStruct.unkC;
        PLAYER.posX.i.hi = g_unkGraphicsStruct.unkC;
    }
    if (g_unkGraphicsStruct.unk1C != 0) {
        if (g_PlayerY < g_Tilemap.y + 140) {
            g_Tilemap.scrollY.i.hi = g_Tilemap.y + 4;
            PLAYER.posY.i.hi = g_PlayerY - g_Tilemap.scrollY.i.hi;
        } else if (g_Tilemap.height - 116 < g_PlayerY) {
            g_Tilemap.scrollY.i.hi = g_Tilemap.height - 252;
            PLAYER.posY.i.hi = g_PlayerY - g_Tilemap.scrollY.i.hi;
        } else {
            g_Tilemap.scrollY.i.hi = g_PlayerY - 136;
            PLAYER.posY.i.hi = 136;
        }
    } else if (g_PlayerY < g_Tilemap.y + 140) {
        if (g_Tilemap.scrollY.i.hi - (g_PlayerY - 136) >= 4 &&
            g_Tilemap.y + 8 < g_Tilemap.scrollY.i.hi) {
            g_Tilemap.scrollY.i.hi -= 4;
            PLAYER.posY.i.hi += 4;
        } else if (g_Tilemap.scrollY.i.hi < g_Tilemap.y && g_Tilemap.y != 0) {
            g_Tilemap.scrollY.i.hi += 4;
            PLAYER.posY.i.hi -= 4;
        } else {
            g_Tilemap.scrollY.i.hi = g_Tilemap.y + 4;
            PLAYER.posY.i.hi = g_PlayerY - g_Tilemap.scrollY.i.hi;
        }
    } else {
        if (g_Tilemap.height - 116 < g_PlayerY) {
            g_Tilemap.scrollY.i.hi = g_Tilemap.height - 252;
            PLAYER.posY.i.hi = g_PlayerY - g_Tilemap.scrollY.i.hi;
        } else if (g_Tilemap.scrollY.i.hi - (g_PlayerY - 136) >= 4) {
            g_Tilemap.scrollY.i.hi = g_Tilemap.scrollY.i.hi - 4;
            PLAYER.posY.i.hi = PLAYER.posY.i.hi + 4;
        } else {
            g_Tilemap.scrollY.i.hi = g_PlayerY - 136;
            PLAYER.posY.i.hi = 136;
        }
    }
    return 0;
}

void func_800F14CC(void) {
    RoomTeleport* temp_a2;
    s32 temp_a1;
    s32 newY;

    if (D_8003C730 == 1) {
        PLAYER.posX.i.hi = 0x80;
        PLAYER.posY.i.hi = 0xA4;
        if (g_StageId & STAGE_INVERTEDCASTLE_FLAG) {
            PLAYER.posY.i.hi += 0x10;
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
    s32 stageId;
    RoomTeleport* tele;

    if (D_8003C730 != 0)
        return g_StageId;
    else if (D_80097C98 == 4)
        return STAGE_TOP | STAGE_INVERTEDCASTLE_FLAG;
    else if (D_80097C98 == 5)
        return STAGE_TOP;
    else if (D_80097C98 == 6)
        return STAGE_LIB;
    else {
        tele = &D_800A245C[D_8006C374];
        stageId = tele->stageId;
        if (g_StageId & STAGE_INVERTEDCASTLE_FLAG) {
            stageId ^= STAGE_INVERTEDCASTLE_FLAG;
        }
        return stageId;
    }
}

static void func_800F1770(u8 bitmap[], s32 x, s32 y, s32 explored) {
    // Pixels are stored 2 per byte
    s32 index = (x / 2) + (y * 4);

    if (!(x & 1)) {
        bitmap[index] = (bitmap[index] & 0xF0) + explored;
    } else {
        bitmap[index] = (bitmap[index] & 0xF) + (explored << 4);
    }
}

static s32 func_800F17C8(u8 bitmap[], s32 x, s32 y) {
    s32 temp_v0 = (x / 2) + (y * 4);

    if (!(x & 1)) {
        return bitmap[temp_v0] & 0xF;
    } else {
        return (bitmap[temp_v0] & 0xF0) >> 4;
    }
}

static void func_800F180C(s32 x, s32 y, u8* dst) {
    s32 i, j;
    u8 *start, *src;

    start = CASTLE_MAP_PTR;
    start += x * 2;
    start += y * 4 * 128;
    for (i = 0; i < 5; i++, start += 0x80) {
        for (j = 0, src = start; j < 4; j++) {
            dst[4 * i + j] = src[j];
        }
    }
}

static void func_800F1868(s32 x, s32 y, u8* src) {
    s32 i;
    s32 j;
    u8* start;

    start = CASTLE_MAP_PTR;
    start += x * 2;
    for (i = 0; i < 5; i++) {
        for (j = 0; j < 4; j++) {
            (start + (((y * 4) + i) * 128))[j] = src[(4 * i) + j];
        }
    }
}

void func_800F18C4(s32 x, s32 y) {
    u8 sp10[4 * 5];
    s32 i;
    s32 j;

    func_800F180C(x, y, sp10);

    for (i = 0; i < 4; i++) {
        for (j = 0; j < 5; j++) {
            func_800F1770(sp10, j, i, false);
        }
    }
    func_800F1868(x, y, sp10);
}

void func_800F1954(s32 x, s32 y, s32 arg2) {
    u8 sp10[4 * 5];
    s32 i;
    s32 j;

    func_800F180C(x, y, sp10);
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 5; j++) {
            if (arg2 == 1 && j == 0) {
                func_800F1770(sp10, j, i, false);
            } else if (arg2 != 2 && j == 4) {
                func_800F1770(sp10, j, i, false);
            } else {
                func_800F1770(sp10, j, i, true);
            }
        }
    }
    func_800F1868(x, y, sp10);
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

void func_800F1B08(s32 x, s32 y, s32 arg2) {
    #define VramPosX 0x340
    #define VramPosY 0x100
    RECT rect;
    u8 sp28[2][20];
    s32 j;
    s32 i;
    s32 temp_v0;
    u8* src;
    u8* dst;
    u8* bitmap;

    if (g_StageId & STAGE_INVERTEDCASTLE_FLAG) {
        x = 0x3F - x;
        y = 0x3F - y;
    }
    bitmap = sp28[1];
    rect.x = VramPosX + x;
    rect.y = VramPosY + y * 4;
    rect.w = 2;
    rect.h = 5;
    StoreImage(&rect, (u_long*)bitmap);
    DrawSync(0);
    src = CASTLE_MAP_PTR;
    src += x * 2;
    src += y * 4 * 0x80;

    for (i = 0; i < 5; i++, src += 0x80) {
        for (j = 0; j < 4; j++) {
            sp28[0][4 * i + j] = src[j];
        }
    }
    
    if (arg2 == 0) {
        for (i = 0; i < 5; i++) {
            for (j = 0; j < 5; j++) {
                temp_v0 = func_800F17C8(bitmap, j, i);
                if (temp_v0 == 0 || temp_v0 == 3 || temp_v0 == 13) {
                    temp_v0 = func_800F17C8(sp28[0], j, i);
                    if (temp_v0 == 2) {
                        temp_v0 = 1;
                    }
                    if (temp_v0 == 0) {
                        func_800F1770(bitmap, j, i, 14);
                    } else {
                        func_800F1770(bitmap, j, i, temp_v0);
                    }
                }
            }
        }
    } else {
        for (i = 0; i < 5; i++) {
            for (j = 0; j < 5; j++) {
                if (func_800F17C8(bitmap, j, i) == 0) {
                    if (func_800F17C8(sp28[0], j, i) == 0) {
                        func_800F1770(bitmap, j, i, 13);
                    } else {
                        func_800F1770(bitmap, j, i, 3);
                    }
                }
            }
        }
    }
    LoadTPage((u_long*)bitmap, 0, 0, VramPosX + x, VramPosY + y * 4, 8, 5);
}

void DrawSecretPassageOnMap(s32 x, s32 y, s32 direction) {
    #define VramPosX 0x340
    #define VramPosY 0x100
    RECT rect;
    u8 buf[20];
    u8* bitmap = buf;

    rect.x = x + VramPosX;
    rect.y = y * 4 + VramPosY;
    rect.w = 2;
    rect.h = 5;
    StoreImage(&rect, (u_long*)bitmap);
    DrawSync(0);
    if (direction == WALL_TOP) {
        func_800F1770(bitmap, 2, 0, func_800F17C8(bitmap, 2, 1));
    }
    if (direction == WALL_LEFT) {
        func_800F1770(bitmap, 0, 2, func_800F17C8(bitmap, 1, 2));
    }
    if (direction == WALL_BOTTOM) {
        func_800F1770(bitmap, 2, 4, func_800F17C8(bitmap, 2, 3));
    }
    if (direction == WALL_RIGHT) {
        func_800F1770(bitmap, 4, 2, func_800F17C8(bitmap, 3, 2));
    }
    LoadTPage((u_long*)bitmap, 0, 0, x + VramPosX, y * 4 + VramPosY, 8, 5);
}

// clang-format off
u8 D_800A2BC0[] = {
    12, 34, WALL_LEFT, NZ0_SECRET_WALL_OPEN, RNZ0_SECRET_WALL_OPEN, //
    12, 34, WALL_BOTTOM, NZ0_SECRET_FLOOR_OPEN, RNZ0_SECRET_CEILING_OPEN, //
    32, 40, WALL_RIGHT, CHI_DEMON_SWITCH, RCHI_DEMON_SWITCH, //
    37, 41, WALL_LEFT, CHI_SECRET_WALL_OPEN, RCHI_SECRET_WALL_OPEN, //
    43, 11, WALL_LEFT, NZ1_LOWER_WALL_OPEN, RNZ1_UPPER_WALL_OPEN, //
    50, 11, WALL_RIGHT, NZ1_UPPER_WALL_OPEN, RNZ1_LOWER_WALL_OPEN, //
    11, 41, WALL_LEFT, JEWEL_SWORD_ROOM_OPEN, JEWEL_ROOM_OPEN, //
    21, 22, WALL_BOTTOM, ARE_ELEVATOR_ACTIVATED, RARE_ELEVATOR_ACTIVATED, //
    20, 21, WALL_TOP, ARE_SECRET_CEILING_OPEN, RARE_SECRET_FLOOR_OPEN, //
    29, 22, WALL_RIGHT, NO2_SECRET_WALL_OPEN, RNO2_SECRET_WALL_OPEN, //
    19, 19, WALL_TOP, NO2_SECRET_CEILING_OPEN, RNO2_SECRET_FLOOR_OPEN, //
    35, 8, WALL_TOP, TOP_SECRET_STAIRS, RTOP_SECRET_STAIRS, //
    39, 39, WALL_BOTTOM, NO4_SECRET_FLOOR_OPEN, RNO4_SECRET_CEILING_OPEN, //
    36, 27, WALL_LEFT, NO4_SECRET_WALL_OPEN, RNO4_SECRET_WALL_OPEN, //
    32, 26, WALL_BOTTOM, CEN_OPEN, RCEN_OPEN, //
    0x00, // terminator
};
// clang-format on

void RevealSecretPassageOnMap(s32 playerMapX, s32 playerMapY, s32 flagId) {
    s32 mapX;
    s32 mapY;
    s32 passageDirection;
    s32 castleFlagId;
    s32 reverseCastleFlagId;
    u8* secretMapWallEntry;

    if (g_StageId & STAGE_INVERTEDCASTLE_FLAG) {
        playerMapX = 63 - playerMapX;
        playerMapY = 63 - playerMapY;
    }
    secretMapWallEntry = D_800A2BC0;
    while (*secretMapWallEntry) {
        mapX = *secretMapWallEntry++;
        mapY = *secretMapWallEntry++;
        passageDirection = *secretMapWallEntry++;
        castleFlagId = *secretMapWallEntry++;
        reverseCastleFlagId = *secretMapWallEntry++;
        if (g_StageId & STAGE_INVERTEDCASTLE_FLAG) {
            // Use the equivalent flag in Reverse Castle instead
            castleFlagId = reverseCastleFlagId;
        }
        if (castleFlagId != 0xFF) {
            if (flagId != 0xFFFF) {
                if (flagId == castleFlagId) {
                    DrawSecretPassageOnMap(mapX, mapY, passageDirection);
                }
            } else {
                if (mapX == playerMapX && mapY == playerMapY &&
                    g_CastleFlags[castleFlagId]) {
                    DrawSecretPassageOnMap(mapX, mapY, passageDirection);
                }
            }
        }
    }
}

void RevealSecretPassageAtPlayerPositionOnMap(s32 castleFlagId) {
    RevealSecretPassageOnMap(g_Tilemap.left + (g_PlayerX >> 8),
                              g_Tilemap.top + (g_PlayerY >> 8), castleFlagId);
}

void func_800F2014(void) {
    s32 x;
    s32 y;
    s32 subMap;
    s32 idx;

    if (g_canRevealMap && (g_StageId != STAGE_ST0)) {
        x = g_Tilemap.left + (g_PlayerX >> 8);
        y = g_Tilemap.top + (g_PlayerY >> 8);
        subMap = 1 << ((3 - (x & 3)) * 2);
        idx = (x >> 2) + (y * 16);
        if (g_StageId & STAGE_INVERTEDCASTLE_FLAG) {
            idx += 2 * 4 * 0x80;
        }
        if (!(g_CastleMap[idx] & subMap)) {
            g_CastleMap[idx] |= subMap;
            g_RoomCount++;
            func_800F1B08(x, y, 0);
            RevealSecretPassageOnMap(x, y, 0xFFFF);
        }
    }
}

INCLUDE_ASM("dra_psp/psp/dra_psp/A710", func_psp_090E8760);

INCLUDE_ASM("dra_psp/psp/dra_psp/A710", func_800F223C);

u8 D_800A2C0C[] = {
    0x00, 0x06, 0x08, 0x26, 0x00, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x80, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80,
    0x7F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xFF, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x98, 0xFF, 0xFF, 0x03, 0x00, 0x00, 0x00, 0x18, 0x98,
    0xFF, 0xF8, 0xE7, 0x07, 0x00, 0xC0, 0x18, 0xF8, 0xFF, 0x01, 0xFC, 0x07,
    0x00, 0xC0, 0xF8, 0x3F, 0x00, 0x00, 0xFC, 0x37, 0x00, 0xC0, 0x1F, 0x00,
    0x00, 0x00, 0xFC, 0x3F, 0x00, 0xFF, 0x00, 0x00, 0x00, 0x00, 0xE0, 0x3F,
    0x00, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x00, 0xC0, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x38, 0x00, 0xC0, 0x00, 0x00, 0x00, 0x00, 0xE0, 0x3F,
    0x00, 0xC0, 0x00, 0x00, 0x00, 0x00, 0xE0, 0x3F, 0x00, 0xC4, 0x00, 0x00,
    0x00, 0x00, 0xFE, 0x3F, 0x00, 0xFF, 0x01, 0x00, 0x00, 0x00, 0xFE, 0x3F,
    0x80, 0x3F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0xC0, 0x03, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x3F, 0xE0, 0x00, 0x00, 0x00, 0xE0, 0x7F, 0x80, 0x3F,
    0x70, 0x00, 0x18, 0x00, 0x60, 0xFF, 0xFF, 0x3F, 0x38, 0xC0, 0xFF, 0xFF,
    0xFF, 0x03, 0x00, 0x38, 0x1C, 0xDF, 0x18, 0x38, 0x80, 0x01, 0x00, 0x30,
    0xFC, 0xFF, 0x03, 0x0E, 0x80, 0x00, 0x00, 0x30, 0x00, 0x01, 0x02, 0x06,
    0x80, 0x00, 0x00, 0x30, 0x80, 0x07, 0x02, 0x06, 0x80, 0x00, 0x00, 0x00,
    0x00, 0x0F, 0x03, 0x06, 0x80, 0x00, 0x00, 0x00, 0x00, 0x18, 0x02, 0x0E,
    0x80, 0x00, 0x00, 0x00, 0x00, 0x10, 0x02, 0x08, 0x80, 0x00, 0x00, 0x00,
    0x00, 0xF0, 0xE3, 0x0F, 0x80, 0x00, 0x00, 0x00, 0x00, 0xE0, 0xE1, 0x07,
    0x80, 0x00, 0x00, 0x00, 0x00, 0xC0, 0xFF, 0x07, 0x80, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x8E, 0xFF, 0xFF, 0x01, 0x00, 0x00, 0x0C, 0x80, 0xBF, 0xC1,
    0xFE, 0x3F, 0x00, 0x00, 0x0C, 0x00, 0xB0, 0x01, 0x80, 0x3F, 0x00, 0x00,
    0xFC, 0xFF, 0xBF, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x78, 0x80, 0x01,
    0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x01, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x3E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF,
};

u8* D_800A2D44[] = {D_800A2C0C};

const char* D_800A2D10[] = {
    "装備技システム短剣必殺使攻撃力防",
};

const char* D_800A2D14[] = {
    "御魔導器拳こ一覧棒両手食物爆弾盾",
};

const char* D_800A2D18[] = {
    "投射薬ん右左武兜鎧マントその他い",
};

const char* D_800A2D58[] = {
    "再開中断終了決定戻る　　　　　　",
};

void func_800F2288(s32 arg0) {
    s32 width; //s8
    s32 height; //s7
    s32 startx; //sp3c
    s32 starty; //s2
    u8* ptrMap; //s6
    s32 j; //s5
    s32 bit; //s4
    s32 x; //s3
    s32 y; //s2
    s32 n; //s0
    
    s32 idx; //a1
    s32 subMap; //a2

    ptrMap = D_800A2D44[arg0];
    while (true) {
        
        if ((startx = *ptrMap++) == 0xFF) {
            return;
        }
        starty = *ptrMap++;
        width = *ptrMap++;
        height = *ptrMap++;
        
        for (y = starty; height != 0; height--, y++) {
            for (j = width, x = startx; j != 0; j--) {
                n = *ptrMap++;
                for (bit = 0; bit < 8; bit++, x++) {
                    if (n & (1 << bit)) {
                        subMap = 3 << ((3 - (x & 3)) * 2);
                        idx = (x >> 2) + (y * 16);
                        if (g_StageId & 0x20) {
                            idx += 0x400;
                        }
                        subMap &= 0xAA;
                        if (!(g_CastleMap[idx] & subMap)) {
                            g_CastleMap[idx] |= subMap;
                            func_800F1B08(x, y, 1);
                        }
                    }
                }
            }
        }
    }
}

extern bool D_80137598;

INCLUDE_ASM("dra_psp/psp/dra_psp/A710", func_800F2404);

void func_800F24F4(void) {
    s32 x;
    s32 y;
    s32 var_a0;

    x = g_Tilemap.left + (g_PlayerX >> 8);
    y = g_Tilemap.top + (g_PlayerY >> 8);
    if (D_8003C708.flags & STAGE_INVERTEDCASTLE_FLAG) {
        if (g_StageId == STAGE_RNO0 && x == 32 && y == 36) {
            if (TimeAttackController(TIMEATTACK_EVENT_FINAL_SAVEPOINT,
                                     TIMEATTACK_GET_RECORD) == 0) {
                TimeAttackController(
                    TIMEATTACK_EVENT_FINAL_SAVEPOINT, TIMEATTACK_SET_RECORD);
            }
        }

        var_a0 = 0;
        if (g_StageId == STAGE_RNO4 && x == 18 && y == 30) {
            D_80137598 = false;
            return;
        }
        if (g_StageId == STAGE_NO4 && x == 45 && y == 33) {
            if (PLAYER.posX.i.hi == 128) {
                D_8003C730 = 1;
            } else {
                if (TimeAttackController(TIMEATTACK_EVENT_SUCCUBUS_DEFEAT,
                                         TIMEATTACK_GET_RECORD)) {
                    D_80137598 = false;
                    return;
                }
            }
            var_a0 = 1;
        }
        func_801042C4(var_a0);
        D_80137598 = true;
        func_80105428();
    } else {
        D_80137598 = false;
    }
}

INCLUDE_ASM("dra_psp/psp/dra_psp/A710", DrawMapCursor);

INCLUDE_ASM("dra_psp/psp/dra_psp/A710", func_psp_090E8E58);

INCLUDE_ASM("dra_psp/psp/dra_psp/A710", func_800F2860);

extern bool D_80137598;
extern s32 D_8013759C;
extern s32 D_801375A0;
extern s32 D_801375A8;
extern s32 D_801375AC;
extern s32 D_801375B0;
extern s32 D_801375B4;
extern s32 D_801375B8;
extern RoomLoadDefHolder D_801375BC;

extern bool D_8C630C8;
extern s32 D_psp_091CE578;
extern s32* D_8D97C40;
void (*D_8CE9C48)();
extern s32 D_psp_091CE570;

void RunMainEngine(void) {
    Entity* ent;
    Primitive* prim;
    LayerDef* layer;
    s32 i;
    u16 ent_unk68;
    void (*playerInit)();
    void (*RichterUpdater)(void);
    u32 tempX;
    u32 tempY;

    if (D_8C630C8) {
        g_Status.hearts = 99;
    }
    // This function is a state machine, this variable is some kind of
    // overall state of the game engine
    switch (g_GameEngineStep) {
    case Engine_Init:
        if (g_IsUsingCd) {
            return;
        }
        D_8006BB00 = 0;
        D_801375C8 = 0;
        g_PauseAllowed = true;
        D_psp_091CE578 = 1;
        g_StageId = func_800F16D0();
        DestroyEntitiesFromIndex(0);
        DestroyAllPrimitives();
        func_800EDAE4();
        func_800EAD7C();
        DrawHud();
        func_800F2404(0);
        if (g_StageId == STAGE_ST0 || g_PlayableCharacter != PLAYER_ALUCARD) {
            playerInit = (void*)g_PlOvl.D_8013C004;
            if (g_StageId == STAGE_ST0) {
                playerInit(1);
            } else {
                playerInit(0);
            }
        } else {
            AluInit();
        }
        if (g_StageId == STAGE_MAD) {
            g_api.o.StageEndCutScene();
        }
        g_backbufferX = 0;
        g_backbufferY = 0;
        func_800F14CC();
        LoadRoomLayer(D_801375BC.def->tileLayoutId);
        if (D_8003C708.flags & FLAG_UNK_20) {
            LoadGfxAsync(ANIMSET_DRA(3));
        }
        if (D_8003C708.flags & FLAG_UNK_40) {
            LoadGfxAsync(ANIMSET_DRA(4));
        }
        D_80097910 = g_StagesLba[g_StageId].unk18;
        if (g_StageId == STAGE_NO3 && D_8003C730 == 0) {
            D_80097910 = MU_METAMORPHOSIS;
        }
        if ((D_8003C730 == 4) ||
            (D_8003C730 == 0) && !(D_8003C708.flags & FLAG_UNK_20)) {
            PlaySfx(D_80097910);
        }
        D_80097928 = 0;
        func_800EA538(2);
        if (D_801375BC.def->tilesetId != 0) {
            func_800EA5E4((D_801375BC.def->tilesetId & 0xFF) + 0x7fff | 0x4000);
        }
        if (D_801375BC.def->objGfxId != 0) {
            LoadGfxAsync((D_801375BC.def->objGfxId & 0xFF) + 0x7fff);
            D_80097904 = D_801375BC.def->objGfxId + 0x7fff;
        } else {
            D_80097904 = 0;
        }
        tempX = PLAYER.posX.i.hi;
        tempY = PLAYER.posY.i.hi;
        g_PlayerX = tempX;
        g_PlayerY = tempY;
        PLAYER.posX.i.hi = (u8)tempX;
        PLAYER.posY.i.hi = (u8)tempY;

        if (PLAYER.posX.i.hi < 0x80) {
            PLAYER.facingLeft = 0;
        }
        // This is so dumb. SOTN programmers never heard of "else"?
        if (PLAYER.posX.i.hi >= 0x80) {
            PLAYER.facingLeft = 1;
        }
        g_Tilemap.x =
            ((D_801375BC.def - 1)->tileLayoutId - g_Tilemap.left) << 8;
        g_Tilemap.y = ((D_801375BC.def - 1)->tilesetId - g_Tilemap.top) << 8;
        g_Tilemap.width =
            (((D_801375BC.def - 1)->objGfxId - g_Tilemap.left) + 1) << 8;
        g_Tilemap.height =
            (((D_801375BC.def - 1)->objLayoutId - g_Tilemap.top) + 1) << 8;

        D_8009791C = g_Tilemap.left + (g_PlayerX >> 8);
        D_80097920 = g_Tilemap.top + (g_PlayerY >> 8);

        g_Tilemap.scrollX.i.hi = (D_8009791C - g_Tilemap.left) << 8;
        g_Tilemap.scrollY.i.hi = (D_80097920 - g_Tilemap.top) << 8;

        if (D_8003C730 == 2) {
            g_Tilemap.bottom -= 1;
            g_Tilemap.height -= 0x100;
            PLAYER.facingLeft = 1;
        }
        if (D_8006C374 == 0x2C) {
            g_Tilemap.y = 0x2FB;
            g_Tilemap.height = 0x3FB;
            g_StageId = STAGE_TOP;
        }
        if (D_80097C98 == 6) {
            PLAYER.facingLeft = 1;
        }
        if ((D_80097C98 == 4) || (D_80097C98 == 5) || (D_80097C98 == 6)) {
            func_800EA5AC(2, 0xFF, 0xFF, 0xFF);
        }
        func_800F0CD8(0);
        func_800F0CD8(0);
        g_PrevScrollX = (s32)g_Tilemap.scrollX.i.hi;
        g_PrevScrollY = (s32)g_Tilemap.scrollY.i.hi;
        g_api.o.InitRoomEntities(D_801375BC.def->objLayoutId);
        g_api.o.Update();
        g_api.o.Update();
        func_800F0940();
        func_801024DC();
        if ((D_80097C98 != 4) && (D_80097C98 != 5) && (D_80097C98 != 6)) {
            func_801027C4(4);
            func_801027C4(2);
        }
        D_80097C98 = 0;
        if (D_8003C730 == 1) {
            InitializeServant(ENGINE_INIT_SERVANT_2);
        } else {
            InitializeServant(ENGINE_INIT_SERVANT_0);
        }
        if (D_8003C730 == 3) {
            D_8003C730 = 0;
        }
        if (D_8003C730 == 4) {
            D_8003C730 = 0;
            D_80097928 = 1;
            if (D_8006C374 == 0x25) {
                g_Tilemap.scrollX.i.hi = 0x640;
                g_Tilemap.scrollY.i.hi = 0x4BF;
                PLAYER.posX.i.hi = 0x80;
                PLAYER.posY.i.hi = 0x88;
                g_PlayerX = 0x6C0;
                g_PlayerY = 0x547;
                g_PrevScrollX = 0x640;
                g_PrevScrollY = 0x4BF;
            }
        }
        func_800F24F4();
        g_unkGraphicsStruct.D_800973F8 = (s16)AllocPrimitives(PRIM_GT4, 16);
        if (g_unkGraphicsStruct.D_800973F8 != 0) {
            prim = &g_PrimBuf[g_unkGraphicsStruct.D_800973F8];
            while (prim != NULL) {
                prim->tpage = 0x1A;
                prim->clut = 0x120;
                prim->drawMode = DRAW_HIDE;
                prim = prim->next;
            }
        }
        RefreshCapePalette();
        g_GameEngineStep++; // Move to Engine_Normal
        func_psp_090DFBD0();
        return;
    case Engine_Normal:
        g_GameTimer++;
#if defined(VERSION_HD)
        func_800F1424();
#endif
        func_800F2014();
        g_ScrollDeltaX = g_Tilemap.scrollX.i.hi - g_PrevScrollX;
        g_ScrollDeltaY = g_Tilemap.scrollY.i.hi - g_PrevScrollY;
        g_PrevScrollX = g_Tilemap.scrollX.i.hi;
        g_PrevScrollY = g_Tilemap.scrollY.i.hi;

        g_api.o.HitDetection();
        D_8013759C = PLAYER.posX.i.hi;
        g_Player.unk7C = PLAYER.posX.i.hi;
        D_801375A0 = PLAYER.posY.i.hi;
        g_Player.unk7E = PLAYER.posY.i.hi;
        D_80097488.x.val = 0;
        D_80097488.y.val = 0;
        if (g_StageId == STAGE_ST0 || g_PlayableCharacter != PLAYER_ALUCARD) {
            g_PlOvl.D_8013C000();
            g_PlOvl.D_8013C008();
        } else {
            EntityAlucard();
            UpdatePlayerEntities();
        }
        g_api.o.UpdateRoomPosition();
        g_api.o.Update();

        if (g_GameState == Game_Ending) {
            if (D_80097C98 == 6) {
                D_80097C98 = 0;
                return;
            }
        } else {
            func_800F2860();
            if (g_DemoMode == Demo_End) {
                g_DemoMode = Demo_None;
                D_80097C98 = 0x08000000;
                LoadSaveData(&D_8D97C40);
                D_8003C730 = 2;
                g_GameStep = Play_PrepareNextStage;
                return;
            }
            if (D_80097C98 & 0x80000000) {
                PlaySfx(SET_STOP_SEQ);
                StoreSaveData(&D_8D97C40, 0, 0);
                g_GameStep = Play_PrepareNextStage;
                return;
            }
            if ((D_80097C98 == 4) || (D_80097C98 == 5) || (D_80097C98 == 6)) {
                PlaySfx(SET_STOP_SEQ);
                func_800EA5AC(0xFFFF, 0xFF, 0xFF, 0xFF);
            }
            if (D_80097C98 == 4) {
                func_800F223C();
                D_8006C374 = 0x25;
                g_GameStep = Play_PrepareNextStage;
                return;
            } else if (D_80097C98 == 5) {
                func_800F223C();
                D_8006C374 = 0x26;
                g_GameStep = Play_PrepareNextStage;
                return;
            } else if (D_80097C98 == 6) {
                g_StageId = 0x22;
                func_800F223C();
                D_8006C374 = 0x27;
                g_GameStep = Play_PrepareNextStage;
                return;
            } else if (D_80097C98 == 1) {
                PLAYER.posX.i.hi += 0x100;
            }
            D_801375A4 = D_8013759C - PLAYER.posX.i.hi;
            D_801375A8 = D_801375A0 - PLAYER.posY.i.hi;
            g_PlayerX -= D_801375A4;
            g_PlayerY -= D_801375A8;
            D_8013759C = PLAYER.posX.val;
            D_801375A0 = PLAYER.posY.val;
            D_801375AC = g_Tilemap.scrollX.i.hi;
            D_801375B0 = g_Tilemap.scrollY.i.hi;

            if (g_unkGraphicsStruct.unk20 != 0) {
                func_8010E0D0(g_unkGraphicsStruct.unk20);
                PlaySfx(SET_PAUSE_SFX_SCRIPTS);
                g_GameEngineStep = Engine_5;
                return;
            }
            i = func_800F0CD8(1);
            if (i != 0) {
                func_801027A4();
                if (i > 1) {
                    D_8006C374 = i - 2;
                    g_GameStep = Play_PrepareNextStage;
                    return;
                }
                if (D_801375BC.def->tilesetId == 0xFF) {
                    D_8006C374 = D_801375BC.def->tileLayoutId;
                    g_GameStep = Play_PrepareNextStage;
                    return;
                }
                func_8932B50();
                g_GameEngineStep = Engine_3;
                g_MenuStep = MENU_STEP_INIT;
                return;
            }
            D_801375B4 = D_801375AC - g_Tilemap.scrollX.i.hi;
            D_801375B8 = D_801375B0 - g_Tilemap.scrollY.i.hi;
            D_801375A4 = D_8013759C - PLAYER.posX.val;
            D_801375A8 = D_801375A0 - PLAYER.posY.val;
            D_801375A4 -= D_80097488.x.val;
            D_801375A8 -= D_80097488.y.val;
            func_800F0940();

            for (i = 0, ent = &g_Entities[0]; i < LEN(g_Entities); i++, ent++) {
                ent_unk68 = ent->unk68;
                if (ent_unk68) {
                    ent->posX.val += D_801375B4 * ent_unk68 * 0x100;
                    ent->posY.val += D_801375B8 * ent_unk68 * 0x100;
                } else {
                    if (ent->flags & FLAG_POS_CAMERA_LOCKED) {
                        ent->posX.i.hi += D_801375B4;
                        ent->posY.i.hi += D_801375B8;
                    }
                    if (ent->flags & FLAG_POS_PLAYER_LOCKED) {
                        ent->posX.val -= D_801375A4;
                        ent->posY.val -= D_801375A8;
                    }
                }
            }
            func_80121F14(D_801375B4 << 0x10, D_801375B8 << 0x10);
            D_801375A4 = D_801375A4 >> 16;
            D_801375A8 = D_801375A8 >> 16;
            // Note: g_PrimBuf is MAX_PRIM_COUNT=1280 total in size.
            for (i = 0, prim = &g_PrimBuf[0]; i < 1024; i++, prim++) {
                if (prim->drawMode & DRAW_UNK02) {
                    switch (prim->type & 0xf) {
                    case PRIM_G4:
                    case PRIM_GT4:
                        prim->x3 += D_801375B4;
                        prim->y3 += D_801375B8;
                    case PRIM_GT3:
                        prim->x2 += D_801375B4;
                        prim->y2 += D_801375B8;
                    case PRIM_LINE_G2:
                        prim->x1 += D_801375B4;
                        prim->y1 += D_801375B8;
                    case PRIM_TILE:
                    case PRIM_SPRT:
                        prim->x0 += D_801375B4;
                        prim->y0 += D_801375B8;
                    case PRIM_NONE:
                    case PRIM_ENV:
                        break;
                    }
                } else if (prim->drawMode & DRAW_UNK_200) {
                    switch (prim->type & 0xf) {
                    case PRIM_G4:
                    case PRIM_GT4:
                        prim->x3 -= D_801375A4;
                        prim->y3 -= D_801375A8;
                    case PRIM_GT3:
                        prim->x2 -= D_801375A4;
                        prim->y2 -= D_801375A8;
                    case PRIM_LINE_G2:
                        prim->x1 -= D_801375A4;
                        prim->y1 -= D_801375A8;
                    case PRIM_TILE:
                    case PRIM_SPRT:
                        prim->x0 -= D_801375A4;
                        prim->y0 -= D_801375A8;
                    case PRIM_NONE:
                    case PRIM_ENV:
                        break;
                    }
                }
            }
            func_80102D70();
            func_801028AC(0);
            DrawHudSubweapon();
            func_800E414C();
            if (D_80137598) {
                func_80105428();
            }
            if (g_Player.status & PLAYER_STATUS_UNK80000) {
                g_GameEngineStep = Engine_10;
                g_MenuStep = MENU_STEP_INIT;
            }
            if (g_unkGraphicsStruct.D_800973FC != 0 && D_8006BB00 == 0) {
                D_8006BB00 = 1;
                MuteCd();
            } else if (g_unkGraphicsStruct.D_800973FC == 0 && D_8006BB00 != 0) {
                if (g_unkGraphicsStruct.pauseEnemies != 0) {
                    D_80097928 = 0;
                    D_8006BB00 = 0;
                    UnMuteCd();
                } else if (D_80097928 == 0) {
                    D_8006BB00 = 0;
                    UnMuteCd();
                } else {
                    UnMuteCd();
                    if (!(D_8003C708.flags & (FLAG_UNK_40 | FLAG_UNK_20))) {
                        PlaySfx(D_80097910);
                        if (D_80097910 != 0) {
                            D_80097928 = 0;
                        }
                    }
                    D_8006BB00 = 0;
                }
            }
            D_psp_091CE570 = 0;
            if (!(g_Player.status & PLAYER_STATUS_DEAD)) {
                if ((g_pads[0].tapped & PAD_START) && g_PauseAllowed &&
                    D_psp_091CE578) {
                    func_801027A4();
                    if ((g_StageId == STAGE_ST0) ||
                        (g_PlayableCharacter != PLAYER_ALUCARD)) {
                        D_800974A4 = 1;
                        g_GameEngineStep = Engine_0x70;
                        g_MenuStep = MENU_STEP_INIT;
                        PlaySfx(SET_RELEASE_RATE_LOW_22_23);
                        PlaySfx(SET_RELEASE_RATE_LOW_20_21);
                        PlaySfx(SET_PAUSE_SFX_SCRIPTS);
                        return;
                    }
                    PlaySfx(SET_RELEASE_RATE_LOW_22_23);
                    PlaySfx(SET_RELEASE_RATE_LOW_20_21);
                    PlaySfx(SET_PAUSE_SFX_SCRIPTS);
                    func_801027C4(1);
                    g_GameEngineStep++; // Goes from 1 to 2, into Engine_Menu
                    g_MenuStep = MENU_STEP_INIT;
                    D_psp_091CE570 = 1;
                } else if ((g_pads[0].tapped & PAD_SELECT) &&
                           (g_StageId != STAGE_ST0) && g_PauseAllowed &&
                           D_psp_091CE578) {
                    func_801027C4(6);
                    D_800974A4 = 1;
                    g_GameEngineStep = Engine_Map;
                }
                break;
            }
            break;
        case Engine_0x70:
            DrawHudSubweapon2();
            func_801028AC(1);
            break;
        case Engine_Menu:
            MenuHandle();
            func_801028AC(1);
            break;
        case Engine_Map:
            if (g_canRevealMap) {
                DrawMapCursor();
            }
            if (g_pads[0].tapped & (PAD_START | PAD_SELECT)) {
                func_801027C4(7);
                D_800974A4 = 0;
                g_GameEngineStep = Engine_Normal;
            }
            g_api.o.UpdateStageEntities();
            func_80102D70();
            func_801028AC(1);
            break;
        case Engine_3:
            switch (g_MenuStep) {
            case 0:
                if (D_80097C98 == 2) {
                    func_800EA5AC(0xFF, 0xFF, 0xFF, 0xFF);
                    g_MenuStep = MENU_STEP_EXIT_BEGIN;
                } else {
                    func_801027C4(1);
                    g_MenuStep++;
                }
                break;
            case 1:
                if (func_801025F4() != 0) {
                    g_MenuStep++;
                }
                break;
            case 2:
                g_MenuStep++;
                break;
            case 3:
                if (g_IsUsingCd) {
                    if (D_80097C98 == 2) {
                        func_800EA5AC(0xFF, 0xFF, 0xFF, 0xFF);
                    }
                    break;
                } else if (D_80097928 != 0) {
                    D_80097910 = g_StagesLba[g_StageId].unk18;
                    if (g_unkGraphicsStruct.D_800973FC != 1) {
                        PlaySfx(SET_STOP_MUSIC);
                        if (func_80131F68() == false) {
                            PlaySfx(D_80097910);
                            D_80097928 = 0;
                        } else {
                            break;
                        }
                    }
                }
                if (D_80137598) {
                    func_8010427C();
                    D_80137598 = false;
                }
                layer = g_api.o.tileLayers[D_801375BC.def->tileLayoutId].fg;
                if (layer->rect.params & 0x80) {
                    D_801375BC.def =
                        &g_api.o.rooms[layer->rect.params & 0x7F].load;
                    // TODO: !FAKE
                    // D_8009791C is probably part of a struct. see also
                    // (&g_Tilemap.scrollX)->i.hi seen elsewhere
                    // in this function. do-while prevents instruction
                    // reordering
                    do {
                        D_8009791C = layer->zPriority;
                    } while (0);
                    D_80097920 = layer->flags;
                } else {
                    D_8009791C = g_Tilemap.left + (g_PlayerX >> 8);
                    D_80097920 = g_Tilemap.top + (g_PlayerY >> 8);
                }
                D_8013759C = PLAYER.posX.val;
                D_801375A0 = PLAYER.posY.val;
                PLAYER.posX.i.hi = D_801375C0 + g_Tilemap.scrollX.i.hi;
                PLAYER.posY.i.hi = D_801375C4 + g_Tilemap.scrollY.i.hi;
                if (D_8003C708.flags & (FLAG_UNK_40 | FLAG_UNK_20)) {
                    LoadGfxAsync(ANIMSET_DRA(1));
                }
                func_800EA538(2);
                if (D_801375BC.def->tilesetId != 0) {
                    func_800EA5E4(
                        ((D_801375BC.def->tilesetId & 0xFF) + 0x7FFF) | 0x4000);
                }
                if (D_801375BC.def->objGfxId != 0) {
                    LoadGfxAsync((D_801375BC.def->objGfxId & 0xFF) + 0x7FFF);
                    D_80097904 = D_801375BC.def->objGfxId + 0x7FFF;
                } else {
                    D_80097904 = 0;
                }
                func_800F2404(1);
                PLAYER.posY.i.hi = (u8)PLAYER.posY.i.hi;
                PLAYER.posX.i.hi = (u8)PLAYER.posX.i.hi;
                LoadRoomLayer(D_801375BC.def->tileLayoutId);
                if (D_8003C708.flags & FLAG_UNK_20) {
                    LoadGfxAsync(ANIMSET_DRA(3));
                }
                if (D_8003C708.flags & FLAG_UNK_40) {
                    LoadGfxAsync(ANIMSET_DRA(4));
                }
                g_Tilemap.x =
                    ((D_801375BC.def - 1)->tileLayoutId - g_Tilemap.left) << 8;
                g_Tilemap.y =
                    ((D_801375BC.def - 1)->tilesetId - g_Tilemap.top) << 8;
                g_Tilemap.width =
                    (((D_801375BC.def - 1)->objGfxId - g_Tilemap.left) + 1)
                    << 8;
                g_Tilemap.height =
                    (((D_801375BC.def - 1)->objLayoutId - g_Tilemap.top) + 1)
                    << 8;
                // permuter found this weird & -> thing, I don't know man
                g_Tilemap.scrollX.i.hi = (D_8009791C - g_Tilemap.left) << 8;
                g_Tilemap.scrollY.i.hi = (D_80097920 - g_Tilemap.top) << 8;
                g_PlayerX = PLAYER.posX.i.hi + g_Tilemap.scrollX.i.hi;
                g_PlayerY = PLAYER.posY.i.hi + g_Tilemap.scrollY.i.hi;
                func_8011A9D8();
                PLAYER.zPriority = g_unkGraphicsStruct.g_zEntityCenter;
                func_800F0CD8(0);
                func_8010BFFC();
                g_PlayerX = PLAYER.posX.i.hi + g_Tilemap.scrollX.i.hi;
                g_PlayerY = PLAYER.posY.i.hi + g_Tilemap.scrollY.i.hi;
                func_800F0CD8(0);
                if (g_StageId == STAGE_RTOP) {
                    DestroyEntitiesFromIndex(0x40);
                    for (i = 0; i < LEN(g_unkGraphicsStruct.D_80097428); i++) {
                        g_unkGraphicsStruct.D_80097428[i] = 0;
                    }
                    g_PrevScrollX = (s32)g_Tilemap.scrollX.i.hi;
                    g_PrevScrollY = (s32)g_Tilemap.scrollY.i.hi;
                    g_api.o.InitRoomEntities(D_801375BC.def->objLayoutId);
                    g_api.o.Update();
                    func_800F0CD8(0);
                    func_800F0CD8(0);
                    DestroyEntitiesFromIndex(0x40);
                    for (i = 0; i < LEN(g_unkGraphicsStruct.D_80097428); i++) {
                        g_unkGraphicsStruct.D_80097428[i] = 0;
                    }
                }
                D_801375A4 = D_8013759C - PLAYER.posX.val;
                D_801375A8 = D_801375A0 - PLAYER.posY.val;
                for (i = 0, ent = &g_Entities[0]; i < LEN(g_Entities); i++,
                    ent++) {
                    if (ent->flags & FLAG_UNK_20000) {
                        ent->posX.val -= D_801375A4;
                        ent->posY.val -= D_801375A8;
                    }
                }
                i = 0;
                func_80121F14(-D_801375A4, -D_801375A8);
                D_801375A4 = D_801375A4 >> 16;
                D_801375A8 = D_801375A8 >> 16;
                // Note: g_PrimBuf is MAX_PRIM_COUNT=1280 total in size.
                for (i = 0, prim = &g_PrimBuf[0]; i < 1024; i++, prim++) {
                    if (prim->drawMode & DRAW_UNK_100) {
                        switch (prim->type & 0xf) {
                        case PRIM_G4:
                        case PRIM_GT4:
                            prim->x3 -= D_801375A4;
                            prim->y3 -= D_801375A8;
                        case PRIM_GT3:
                            prim->x2 -= D_801375A4;
                            prim->y2 -= D_801375A8;
                        case PRIM_LINE_G2:
                            prim->x1 -= D_801375A4;
                            prim->y1 -= D_801375A8;
                        case PRIM_TILE:
                        case PRIM_SPRT:
                            prim->x0 -= D_801375A4;
                            prim->y0 -= D_801375A8;
                        case PRIM_NONE:
                        case PRIM_ENV:
                            break;
                        }
                    }
                }
                if (g_StageId != STAGE_RTOP) {
                    DestroyEntitiesFromIndex(0x40);
                    for (i = 0; i < LEN(g_unkGraphicsStruct.D_80097428); i++) {
                        g_unkGraphicsStruct.D_80097428[i] = 0;
                    }
                    g_PrevScrollX = g_Tilemap.scrollX.i.hi;
                    g_PrevScrollY = g_Tilemap.scrollY.i.hi;
                    g_api.o.InitRoomEntities(D_801375BC.def->objLayoutId);
                    g_api.o.Update();
                    func_800F0CD8(0);
                    func_800F0CD8(0);
                    DestroyEntitiesFromIndex(0x40);
                    for (i = 0; i < LEN(g_unkGraphicsStruct.D_80097428); i++) {
                        g_unkGraphicsStruct.D_80097428[i] = 0;
                    }
                }
                g_PrevScrollX = g_Tilemap.scrollX.i.hi;
                g_PrevScrollY = g_Tilemap.scrollY.i.hi;
                if (D_80097C98 == 2) {
                    D_80097C98 = 3;
                    func_800EA5AC(0x40, 0xFF, 0xFF, 0xFF);
                } else {
                    D_80097C98 = 0;
                }
                g_api.o.InitRoomEntities(D_801375BC.def->objLayoutId);
                g_api.o.Update();
                g_api.o.Update();
                func_800F0940();
                func_800E414C();
                func_800F24F4();
                if (D_80097C98 == 3) {
                    g_GameEngineStep = Engine_Normal;
                }
                g_MenuStep++;

                break;
            case 4:
                if (func_800EB720() == 0) {
                    func_801027C4(2);
                    g_MenuStep++;
                }
                break;
            case 5:
                if (func_801025F4() != 0) {
                    g_GameEngineStep = Engine_Normal;
                }
                break;
            }
            func_801028AC(1);
            func_801028AC(1);
            break;
        case 0x5:
            if (g_unkGraphicsStruct.unk20 != 0) {
                if (g_StageId != STAGE_ST0) {
                    if (g_PlayableCharacter == PLAYER_ALUCARD) {
                        if (g_unkGraphicsStruct.unk20 == 0xFFF) {
                            EntityAlucard();
                            func_8011A870();
                            g_api.o.UpdateStageEntities();
                            if (g_pads[1].pressed & PAD_DOWN) {
                                g_unkGraphicsStruct.unk20 = 0;
                            }
                        } else {
                            if (g_unkGraphicsStruct.unk20 != 0xFF) {
                                func_8010DF70(g_unkGraphicsStruct.unk20);
                                UpdatePlayerEntities();
                            }
                            g_api.o.UpdateStageEntities();
                            func_80102D70();
                        }
                    } else if (g_PlayableCharacter == PLAYER_RICHTER) {
                        RichterUpdater = g_api.o.UpdateStageEntities;
                        RichterUpdater();
                        func_80102D70();
                    } else if (g_unkGraphicsStruct.unk20 == 0x100) {
                        RichterUpdater = g_PlOvl.D_8013C000;
                        RichterUpdater();
                        RichterUpdater = D_8CE9C48;
                        RichterUpdater();
                        RichterUpdater = g_api.o.UpdateStageEntities;
                        RichterUpdater();
                        func_80102D70();
                    } else {
                        RichterUpdater = g_api.o.UpdateStageEntities;
                        RichterUpdater();
                        func_80102D70();
                    }
                } else {
                    D_8013759C = PLAYER.posX.i.hi;
                    D_801375A0 = PLAYER.posY.i.hi;
                    RichterUpdater = g_PlOvl.D_8013C000;
                    RichterUpdater();
                    RichterUpdater = g_PlOvl.D_8013C008;
                    RichterUpdater();
                    D_801375A4 = D_8013759C - PLAYER.posX.i.hi;
                    D_801375A8 = D_801375A0 - PLAYER.posY.i.hi;
                    g_PlayerX -= D_801375A4;
                    g_PlayerY -= D_801375A8;
                }
            } else {
                func_8010E168(1, 0x30);
                g_GameEngineStep = Engine_Normal;
                PlaySfx(SET_UNPAUSE_SFX_SCRIPTS);
            }
            DrawHudSubweapon();
            return;
        case 0xA:
            switch (g_MenuStep) {
            case 0:
                if (g_IsUsingCd) {
                    break;
                }
                PlaySfx(0x81);
                D_80097910 = 0;
                if (g_StageId == STAGE_ST0) {
                    SetGameState(Game_GameOver);
                    ClearImage(&g_Vram.D_800ACDA0, 0xFF, 0xFF, 0xFF);
                    SetGPUBuffRGB(-1);
                    DestroyEntitiesFromIndex(0);
                    DestroyAllPrimitives();
                    func_800EDAE4();
                    return;
                }
                SetGameState(Game_GameOver);
                func_800E5498();
                return;
            case 1:
                if (func_801025F4() != 0) {
                    g_MenuStep++;
                }
                break;
            case 2:
                SetGameState(Game_GameOver);
                SetGPUBuffRGBZero();
                break;
            }
            func_801028AC(0);
            break;
        }
    }
}
