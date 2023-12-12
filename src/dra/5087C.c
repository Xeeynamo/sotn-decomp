#include "dra.h"
#include "menu.h"
#include "sfx.h"

RoomTeleport D_800A245C[] = {
    {496, 392, 0x00A0, 0x0000, STAGE_NZ0},
    {240, 648, 0x0000, 0x0000, STAGE_NO2},
    {16, 132, 0x0038, 0x0000, STAGE_NO1},
    {496, 132, 0x0078, 0x0000, STAGE_NP3},
    {240, 132, 0x0000, 0x0000, STAGE_NO4},
    {128, 36, 0x0000, 0x0000, STAGE_CEN},
    {16, 1672, 0x0068, 0x0002, STAGE_NO1},
    {128, 212, 0x00A8, 0x0008, STAGE_NO0},
    {128, 77, 16, 0x0028, STAGE_BO6},
    {240, 388, 0x0030, 0x000D, STAGE_TOP},
    {16, 132, 16, 0x000D, STAGE_NO1},
    {16, 644, 0x0000, 0x0041, STAGE_NO0},
    {16, 132, 0x00A0, 0x0041, STAGE_NO4},
    {752, 132, 0x0050, 0x0041, STAGE_NZ0},
    {240, 132, 0x0018, 0x0041, STAGE_WRP},
    {16, 180, 0x0000, 0x0012, STAGE_DRE},
    {16, 388, 0x0050, 0x0003, STAGE_CHI},
    {112, 644, 0x0000, 0x0041, STAGE_NO3},
    {240, 132, 0x0088, 0x0005, STAGE_CAT},
    {16, 132, 128, 0x0005, STAGE_NO4},
    {16, 132, 0x0020, 0x0005, STAGE_WRP},
    {16, 132, 0x0078, 0x000C, STAGE_NP3},
    {16, 132, 0x0030, 0x000C, STAGE_NO0},
    {240, 132, 0x0060, 0x000C, STAGE_DAI},
    {16, 132, 0x0068, 0x0004, STAGE_NO0},
    {240, 132, 0x0030, 0x0004, STAGE_DAI},
    {1264, 132, 0x0030, 0x0004, STAGE_ARE},
    {16, 132, 0x0008, 0x0004, STAGE_WRP},
    {240, 388, 0x0038, 0x000E, STAGE_TOP},
    {272, 644, 0x0068, 0x000E, STAGE_NO1},
    {240, 1412, 0x0030, 0x000E, STAGE_NO2},
    {16, 132, 128, 0x000E, STAGE_NP3},
    {752, 132, 0x0038, 0x000E, STAGE_CHI},
    {16, 132, 0x0078, 0x0006, STAGE_NO2},
    {16, 132, 0x0020, 0x0006, STAGE_ARE},
    {16, 132, 0x0008, 0x0006, STAGE_NZ0},
    {16, 1924, 16, 0x0006, STAGE_TOP},
    {320, 696, 16, 0x000B, STAGE_RTOP},
    {320, 847, 16, 0x002B, STAGE_TOP},
    {16, 132, 0x0028, 0x001F, STAGE_LIB},
    {3824, 132, 0x0040, 0x0001, STAGE_NO0},
    {752, 132, 0x0060, 0x0001, STAGE_LIB},
    {240, 132, 16, 0x0001, STAGE_WRP},
    {240, 132, 0x0058, 0x0001, STAGE_NZ1},
    {896, 952, 16, 0x000B, STAGE_TOP},
    {16, 132, 0x0000, 0x000B, STAGE_NZ1},
    {16, 132, 0x0000, 0x000B, STAGE_WRP},
    {752, 648, 0x0088, 0x000B, STAGE_DAI},
    {240, 132, 0x0050, 0x0009, STAGE_NP3},
    {16, 388, 0x0088, 0x0009, STAGE_NO0},
    {240, 132, 0x0000, 0x0009, STAGE_CHI},
    {16, 180, 0x0000, 0x0009, STAGE_DRE},
    {496, 388, 0x0048, 0x000A, STAGE_DAI},
    {16, 388, 16, 0x000A, STAGE_NO2},
    {16, 132, 0x0090, 0x0041, STAGE_NO3},
    {16, 132, 0x0000, 0x0040, STAGE_MAD},
    {16, 644, 0x0000, 0x0007, STAGE_NO0},
    {16, 132, 0x00A0, 0x0007, STAGE_NO4},
    {752, 132, 0x0050, 0x0007, STAGE_NZ0},
    {240, 132, 0x0018, 0x0007, STAGE_WRP},
    {128, 164, 0x0128, 0x0012, STAGE_NO4},
    {448, 1716, 0x0058, 0x0000, STAGE_DAI},
    {16, 132, 0x0028, 0x0000, STAGE_LIB},
    {16, 132, 0x0038, 0x0000, STAGE_NO1},
    {16, 132, 128, 0x000C, STAGE_NZ0},
    {240, 132, 16, 0x0036, STAGE_CAT},
    {16, 132, 0x0020, 0x0036, STAGE_CAT},
    {496, 132, 0x0000, 0x0023, STAGE_BO7},
    {16, 132, 0x0058, 0x0037, STAGE_NO2},
    {752, 132, 0x0068, 0x0037, STAGE_NO2},
    {496, 132, 0x0000, 36, STAGE_MAR},
    {128, 388, 0x0000, 0x0038, STAGE_CEN},
#if defined(VERSION_US)
    {496, 132, 0x0000, 0x0001, STAGE_BO4},
#elif defined(VERSION_HD)
    {128, 77, 0x0010, 0x0028, STAGE_BO6},
#endif
    {240, 644, 0x0008, 0x0039, STAGE_NO4},
    {16, 132, 0x00E8, 0x0039, STAGE_NO4},
    {16, 132, 0x0000, 0x0029, STAGE_BO5},
    {240, 132, 0x0000, 0x0029, STAGE_BO5},
    {240, 132, 0x0050, 0x003A, STAGE_NO1},
    {16, 132, 0x0060, 0x003A, STAGE_NO1},
    {16, 132, 0x0000, 0x0021, STAGE_BO4},
    {496, 132, 0x0000, 0x0021, STAGE_BO4},
    {752, 132, 0x0018, 0x003B, STAGE_DAI},
    {16, 132, 0x0028, 0x003B, STAGE_DAI},
    {16, 132, 0x0000, 0x0026, STAGE_BO3},
    {496, 132, 0x0000, 0x0026, STAGE_BO3},
    {496, 132, 0x0008, 0x0016, STAGE_CHI},
    {16, 132, 0x0018, 0x0016, STAGE_CHI},
    {16, 132, 0x0000, 0x0005, STAGE_BO7},
    {496, 132, 0x0000, 0x0005, STAGE_BO7},
    {16, 132, 0x0018, 0x003C, STAGE_CHI},
    {496, 132, 0x0008, 0x003C, STAGE_CHI},
    {16, 132, 0x0000, 0x0025, STAGE_BO2},
    {496, 132, 0x0000, 0x0025, STAGE_BO2},
    {240, 132, 0x0058, 0x003D, STAGE_NZ0},
    {16, 644, 0x0098, 0x003D, STAGE_NZ0},
    {16, 132, 0x0000, 0x003D, STAGE_NZ0},
    {1008, 388, 0x0000, 0x002C, STAGE_BO1},
    {16, 132, 0x0000, 0x002C, STAGE_BO1},
    {752, 132, 0x0050, 0x0017, STAGE_NO0},
    {16, 132, 0x0098, 0x0017, STAGE_NO0},
    {16, 132, 0x0000, 0x0000, STAGE_MAR},
    {240, 179, 0x0000, 0x000B, STAGE_BO6},
    {752, 132, 0x0018, 0x0019, STAGE_DAI},
    {16, 132, 0x0028, 0x0019, STAGE_DAI},
    {16, 132, 0x0000, 0x0006, STAGE_BO5},
    {496, 132, 0x0000, 0x0006, STAGE_BO5},
    {240, 132, 0x0050, 0x001A, STAGE_NO1},
    {16, 132, 0x0060, 0x001A, STAGE_NO1},
    {16, 132, 0x0000, 0x0001, STAGE_BO4},
    {240, 132, 0x00C0, 0x001B, STAGE_NO4},
    {240, 644, 0x0008, 0x001B, STAGE_NO4},
    {16, 132, 0x0008, 0x0009, STAGE_BO3},
    {1264, 132, 0x0020, 0x001C, STAGE_ARE},
    {16, 132, 0x0030, 0x001C, STAGE_ARE},
    {16, 132, 0x0000, 0x000A, STAGE_BO2},
    {496, 132, 0x0000, 0x000A, STAGE_BO2},
    {240, 132, 16, 0x001D, STAGE_CAT},
    {16, 132, 0x0020, 0x001D, STAGE_CAT},
    {496, 132, 0x0000, 0x0003, STAGE_BO1},
    {16, 132, 0x0030, 0x003E, STAGE_ARE},
    {1264, 132, 0x0020, 0x003E, STAGE_ARE},
    {496, 132, 0x0000, 0x002A, STAGE_BO0},
    {16, 132, 0x0000, 0x002A, STAGE_BO0},
    {16, 132, 0x0058, 0x001E, STAGE_NO2},
    {752, 132, 0x0068, 0x001E, STAGE_NO2},
    {496, 132, 0x0000, 0x0004, STAGE_BO0},
    {16, 132, 0x0000, 0x0000, STAGE_TE1},
    {1248, 396, 0x0000, 0x0000, STAGE_ST0},
    {240, 132, 0x0000, 0x000D, STAGE_NZ1},
    {1264, 392, 0x0000, 0x0002, STAGE_LIB},
    {16, 132, 0x0000, 0x002D, STAGE_NZ1},
};

RoomBossTeleport D_800A297C[] = {
    {0x20, 0x1A, STAGE_NO0, TIMEATTACK_EVENT_FIRST_MARIA_MEET, 0x64},
    {0x00, 0x01, STAGE_DRE, 0xFF, 0x3C},
    {0x01, 0x01, STAGE_DRE, 0xFF, 0x3C},
    {0x14, 0x10, STAGE_NO2, TIMEATTACK_EVENT_ORLOX_DEFEAT, 0x7D},
    {0x13, 0x32, STAGE_CAT, TIMEATTACK_EVENT_GRANFALOON_DEFEAT, 0x76},
    {0x13, 0x16, STAGE_ARE, TIMEATTACK_EVENT_MINOTAUR_WEREWOLF_DEFEAT, 0x72},
    {0x14, 0x16, STAGE_ARE, TIMEATTACK_EVENT_MINOTAUR_WEREWOLF_DEFEAT, 0x73},
    {0x28, 0x27, STAGE_NO4, TIMEATTACK_EVENT_SCYLLA_DEFEAT, 0x6F},
    {0x39, 0x17, STAGE_NO1, TIMEATTACK_EVENT_DOPPLEGANGER_10_DEFEAT, 0x6C},
#if defined(VERSION_US)
    {0x3A, 0x17, STAGE_NO1, TIMEATTACK_EVENT_DOPPLEGANGER_10_DEFEAT, 0x48},
#endif
    {0x17, 0x0D, STAGE_DAI, TIMEATTACK_EVENT_HYPPOGRYPH_DEFEAT, 0x68},
    {0x18, 0x0D, STAGE_DAI, TIMEATTACK_EVENT_HYPPOGRYPH_DEFEAT, 0x69},
    {0x21, 0x08, STAGE_TOP, TIMEATTACK_EVENT_SAVE_RICHTER, 0x65},
    {0x1E, 0x28, STAGE_CHI, TIMEATTACK_EVENT_CERBERUS_DEFEAT, 0x57},
    {0x1F, 0x28, STAGE_CHI, TIMEATTACK_EVENT_CERBERUS_DEFEAT, 0x58},
    {0x2B, 0x29, STAGE_RARE, TIMEATTACK_EVENT_RALPH_GRANT_SYPHA_DEFEAT, 0x79},
    {0x2C, 0x29, STAGE_RARE, TIMEATTACK_EVENT_RALPH_GRANT_SYPHA_DEFEAT, 0x7A},
    {0x33, 0x23, STAGE_RNZ0, TIMEATTACK_EVENT_BEELZEBUB_DEFEAT, 0x60},
    {0x36, 0x24, STAGE_RNZ0, TIMEATTACK_EVENT_BEELZEBUB_DEFEAT, 0x61},
    {0x21, 0x17, STAGE_RCHI, TIMEATTACK_EVENT_DEATH_DEFEAT, 0x5B},
    {0x20, 0x17, STAGE_RCHI, TIMEATTACK_EVENT_DEATH_DEFEAT, 0x5C},
    {0x28, 0x32, STAGE_RDAI, TIMEATTACK_EVENT_MEDUSA_DEFEAT, 0x53},
    {0x27, 0x32, STAGE_RDAI, TIMEATTACK_EVENT_MEDUSA_DEFEAT, 0x54},
    {0x06, 0x28, STAGE_RNO1, TIMEATTACK_EVENT_THE_CREATURE_DEFEAT, 0x4F},
    {0x05, 0x28, STAGE_RNO1, TIMEATTACK_EVENT_THE_CREATURE_DEFEAT, 0x50},
    {0x17, 0x18, STAGE_RNO4, TIMEATTACK_EVENT_DOPPLEGANGER_40_DEFEAT, 0x4B},
    {0x2B, 0x2F, STAGE_RNO2, TIMEATTACK_EVENT_AKMODAN_II_DEFEAT, 0x46},
    {0x2C, 0x0D, STAGE_RCAT, TIMEATTACK_EVENT_GALAMOTH_DEFEAT, 0x43},
    {0x80, 0x00, 0x00, 0x00, 0x00},
};

u8 D_800A2BC0[] = {
    0x0C, 0x22, 0x02, 0x81, 0x88, //
    0x0C, 0x22, 0x03, 0x82, 0x89, //
    0x20, 0x28, 0x04, 0x50, 0x58, //
    0x25, 0x29, 0x02, 0x51, 0x59, //
    0x2B, 0x0B, 0x02, 0xA1, 0xA9, //
    0x32, 0x0B, 0x04, 0xA2, 0xAA, //
    0x0B, 0x29, 0x02, 0x3A, 0x3D, //
    0x15, 0x16, 0x03, 0xB2, 0xB9, //
    0x14, 0x15, 0x01, 0xB3, 0xB8, //
    0x1D, 0x16, 0x04, 0x20, 0x28, //
    0x13, 0x13, 0x01, 0x21, 0x29, //
    0x23, 0x08, 0x01, 0x94, 0x9B, //
    0x27, 0x27, 0x03, 0xC4, 0xCA, //
    0x24, 0x1B, 0x02, 0xC6, 0xCB, //
    0x20, 0x1A, 0x03, 0x00, 0xE4, //
    0x00,                         // terminator
};

u32 D_800A2C0C[] = {
    0x26080600, 0x00000000, 0x00000030, 0x80000000, 0x00000030, 0x80000000,
    0x0000007F, 0x80000000, 0x000000FF, 0x98000000, 0x0003FFFF, 0x98180000,
    0x07E7F8FF, 0xF818C000, 0x07FC01FF, 0x3FF8C000, 0x37FC0000, 0x001FC000,
    0x3FFC0000, 0x0000FF00, 0x3FE00000, 0x0000C000, 0x30000000, 0x0000C000,
    0x38000000, 0x0000C000, 0x3FE00000, 0x0000C000, 0x3FE00000, 0x0000C400,
    0x3FFE0000, 0x0001FF00, 0x3FFE0000, 0x00003F80, 0x30000000, 0x000003C0,
    0x3F000000, 0x000000E0, 0x3F807FE0, 0x00180070, 0x3FFFFF60, 0xFFFFC038,
    0x380003FF, 0x3818DF1C, 0x30000180, 0x0E03FFFC, 0x30000080, 0x06020100,
    0x30000080, 0x06020780, 0x00000080, 0x06030F00, 0x00000080, 0x0E021800,
    0x00000080, 0x08021000, 0x00000080, 0x0FE3F000, 0x00000080, 0x07E1E000,
    0x00000080, 0x07FFC000, 0x00000080, 0xFF8E0000, 0x000001FF, 0xC1BF800C,
    0x00003FFE, 0x01B0000C, 0x00003F80, 0x01BFFFFC, 0x00000000, 0x01807800,
    0x00000000, 0x01FFFF00, 0x00000000, 0x00003E00, 0x00000000, 0x000000FF,
};

u32** D_800A2D44 = &D_800A2C0C;

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

void func_800F1EB0(s32 playerX, s32 playerY, s32 arg2) {
    s32 x;
    s32 y;
    s32 data_2;
    s32 data_3;
    s32 data_4;
    u8* ptr;

    if (g_StageId & STAGE_INVERTEDCASTLE_FLAG) {
        playerX = 0x3F - playerX;
        playerY = 0x3F - playerY;
    }
    ptr = D_800A2BC0;
    while (*ptr != 0) {
        x = *ptr++;
        y = *ptr++;
        data_2 = *ptr++;
        data_3 = *ptr++;
        data_4 = *ptr++;
        if (g_StageId & STAGE_INVERTEDCASTLE_FLAG) {
            data_3 = data_4;
        }
        if (data_3 != 0xFF) {
            if (arg2 != 0xFFFF) {
                if (arg2 == data_3) {
                    func_800F1D54(x, y, data_2, data_4);
                }
            } else {
                if (x == playerX && y == playerY && g_CastleFlags[data_3]) {
                    func_800F1D54(x, y, data_2, data_4);
                }
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

// Needs PlaySfx to have a signature of
// void PlaySfx(s32 sfxId); but changing it causes other parts
// of binary to mismatch. Removing it from the header seems
// to make it match everywhere
void func_800F2860(void) {
    s32 var_v0;

    switch (D_801375C8) {
    case 1:
        PlaySfx(0x80);
        D_801375C8++;
        break;
    case 0:
    default:
        return;
    case 2:
        if (func_80131F68() == false) {
            D_801375C8++;
            break;
        }
        break;
    case 3:
#if defined(VERSION_US)
        PlaySfx(0x33F);
#elif defined(VERSION_HD)
        PlaySfx(0x33C);
#endif
        D_801375C8++;
        break;
    case 4:
        if (func_80131F68() != false) {
            D_801375C8++;
            break;
        }
        break;
    case 5:
        if (func_80131F68() == false) {
            D_801375C8++;
            break;
        }
        break;
    case 6:
        PlaySfx(D_80097910);
        D_801375C8 = 0;
        return;
    case 7:
        if (func_80131F68() != 0) {
            return;
        }
        D_801375C8--;
        break;
    case 8:
        PlaySfx(0x80);
        D_801375C8--;
        break;
    }
}

void func_800F298C(void) {
    Entity* ent;
    Primitive* prim;
    LayerDef* layer;
    s32 i;
    s32 ent_unk68;
    void (*RichterInitializer)();
    void (*RichterUpdater)();
    s32 tempX;
    s32 tempY;
    s32* ptr_791c;
    // This function is a state machine, this variable is some kind of
    // overall state of the game engine
    switch (D_8003C9A4) {
    case 0:
        if (g_IsUsingCd) {
            return;
        }
        D_8006BB00 = 0;
        D_801375C8 = 0;
        D_8003C8B8 = 1;
        g_StageId = func_800F16D0();
        DestroyEntities(0);
        DestroyAllPrimitives();
        func_800EDAE4();
        func_800EAD7C();
        func_8010189C();
        func_800F2404(0);
        if ((g_StageId == STAGE_ST0) ||
            (g_PlayableCharacter != PLAYER_ALUCARD)) {
            RichterInitializer = D_8013C004;
            if (g_StageId == STAGE_ST0) {
                RichterInitializer(1);
            } else {
                RichterInitializer(0);
            }
        } else {
            func_80109594();
        }
        if (g_StageId == STAGE_MAD) {
            g_api.o.unk3C();
        }
        g_backbufferX = 0;
        g_backbufferY = 0;
        func_800F14CC();
        LoadRoomLayer(D_801375BC.def->tileLayoutId);
        if (D_8003C708.flags & 0x20) {
            LoadGfxAsync(ANIMSET_DRA(3));
        }
        if (D_8003C708.flags & 0x40) {
            LoadGfxAsync(ANIMSET_DRA(4));
        }
        D_80097910 = g_StagesLba[g_StageId].unk18;
        if (g_StageId == STAGE_NO3 && D_8003C730 == 0) {
#if defined(VERSION_US)
            D_80097910 = 0x32A;
#elif defined(VERSION_HD)
            D_80097910 = 0x327;
#endif
        }
        if ((D_8003C730 == 0) && !(D_8003C708.flags & 0x20)) {
            PlaySfx(D_80097910);
        }
        D_80097928 = 0;
        func_800EA538(2);
        if (D_801375BC.def->tilesetId != 0) {
            func_800EA5E4(D_801375BC.def->tilesetId + 0x7fff | 0x4000);
        }
        if (D_801375BC.def->objGfxId != 0) {
            LoadGfxAsync(D_801375BC.def->objGfxId + 0x7fff);
            D_80097904 = D_801375BC.def->objGfxId + 0x7fff;
        } else {
            D_80097904 = 0;
        }
        tempX = PLAYER.posX.i.hi;
        tempY = PLAYER.posY.i.hi;
        playerX = tempX;
        playerY = tempY;
        PLAYER.posX.i.hi = (u8)tempX;
        PLAYER.posY.i.hi = (u8)tempY;
        if (PLAYER.posX.i.hi < 0x80) {
            PLAYER.facingLeft = 0;
        } else {
            PLAYER.facingLeft = 1;
        }
        ptr_791c = &D_8009791C;
        g_Tilemap.x =
            ((D_801375BC.def - 1)->tileLayoutId - g_Tilemap.left) << 8;
        g_Tilemap.y = ((D_801375BC.def - 1)->tilesetId - g_Tilemap.top) << 8;
        g_Tilemap.width =
            (((D_801375BC.def - 1)->objGfxId - g_Tilemap.left) + 1) << 8;
        g_Tilemap.height =
            (((D_801375BC.def - 1)->objLayoutId - g_Tilemap.top) + 1) << 8;

        *ptr_791c = (playerX >> 8) + g_Tilemap.left;
        D_80097920 = (playerY >> 8) + g_Tilemap.top;

        g_Tilemap.cameraX.i.hi = (*ptr_791c - g_Tilemap.left) << 8;
        g_Tilemap.cameraY.i.hi = (D_80097920 - g_Tilemap.top) << 8;

        if (D_8003C730 == 2) {
            g_Tilemap.height -= 0x100;
            PLAYER.facingLeft = 1;
            g_Tilemap.bottom -= 1;
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
        D_80073074 = (s32)g_Tilemap.cameraX.i.hi;
        D_8007307C = (s32)g_Tilemap.cameraY.i.hi;
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
            func_800E6218(2);
        } else {
            func_800E6218(0);
        }
        if (D_8003C730 == 3) {
            D_8003C730 = 0;
        }
        func_800F24F4();
        D_800973F8 = AllocPrimitives(PRIM_GT4, 16);
        if (D_800973F8 != 0) {
            prim = &g_PrimBuf[D_800973F8];
            while (prim != NULL) {
                prim->tpage = 0x1A;
                prim->clut = 0x120;
                prim->blendMode = BLEND_VISIBLE;
                prim = prim->next;
            }
        }
        func_800FF6C4();
        D_8003C9A4++;
        return;
    case 1:
        g_GameTimer++;
#if defined(VERSION_HD)
        func_800F1424();
#endif
        func_800F2014();
        D_80097908 = g_Tilemap.cameraX.i.hi - D_80073074;
        D_8009790C = g_Tilemap.cameraY.i.hi - D_8007307C;
        D_80073074 = g_Tilemap.cameraX.i.hi;
        D_8007307C = g_Tilemap.cameraY.i.hi;

        g_api.o.TestCollisions();
        D_8013759C = PLAYER.posX.i.hi;
        g_Player.unk7C = PLAYER.posX.i.hi;
        D_80097488 = 0;
        D_8009748C = 0;
        D_801375A0 = PLAYER.posY.i.hi;
        g_Player.unk7E = PLAYER.posY.i.hi;
        if ((g_StageId == STAGE_ST0) ||
            (g_PlayableCharacter != PLAYER_ALUCARD)) {
            D_8013C000();
            D_8013C008();
        } else {
            EntityAlucard();
            func_8011A4D0();
        }
        g_api.o.unk08();
        g_api.o.Update();

#if defined(VERSION_US)
        if (g_GameState == Game_Ending) {
            if (D_80097C98 == 6) {
                D_80097C98 = 0;
                return;
            }
#elif defined(VERSION_HD)
        if (0) {
#endif

        } else {
            func_800F2860();
            if (g_DemoMode == Demo_End) {
                g_DemoMode = Demo_None;
                D_80097C98 = 0x08000000;
                LoadSaveData(0x801EA000);
                D_8003C730 = 2;
                g_GameStep = Play_PrepareNextStage;
                return;
            }
            if (D_80097C98 < 0) {
                PlaySfx(SET_STOP_SEQ);
                StoreSaveData(0x801EA000, 0, 0);
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
            playerX -= D_801375A4;
            playerY -= D_801375A8;
            D_8013759C = PLAYER.posX.val;
            D_801375A0 = PLAYER.posY.val;
            D_801375AC = g_Tilemap.cameraX.i.hi;
            D_801375B0 = g_Tilemap.cameraY.i.hi;

            if (*D_80097420 != 0) {
                func_8010E0D0(*D_80097420);
                PlaySfx(SET_UNK_0E);
                D_8003C9A4 = 5;
                return;
            }
            i = func_800F0CD8(1);
            if (i != 0) {
                func_801027A4();
                if (i >= 2) {
                    D_8006C374 = i - 2;
                    g_GameStep = Play_PrepareNextStage;
                    return;
                }
                if (D_801375BC.def->tilesetId == 0xFF) {
                    D_8006C374 = D_801375BC.def->tileLayoutId;
                    g_GameStep = Play_PrepareNextStage;
                    return;
                }
                D_8003C9A4 = 3;
                g_MenuStep = MENU_STEP_INIT;
                return;
            }
            D_801375B4 = D_801375AC - g_Tilemap.cameraX.i.hi;
            D_801375B8 = D_801375B0 - g_Tilemap.cameraY.i.hi;
            D_801375A4 = D_8013759C - PLAYER.posX.val;
            D_801375A8 = D_801375A0 - PLAYER.posY.val;
            D_801375A4 -= D_80097488;
            D_801375A8 -= D_8009748C;
            func_800F0940();

            for (i = 0, ent = &g_Entities[0]; i < LEN(g_Entities); i++, ent++) {
                ent_unk68 = ent->unk68;
                if (ent_unk68 != 0) {
                    ent->posX.val += ent_unk68 * D_801375B4 * 0x100;
                    ent->posY.val += ent_unk68 * D_801375B8 * 0x100;
                } else {
                    if (ent->flags & FLAG_UNK_08000000) {
                        ent->posX.i.hi += D_801375B4;
                        ent->posY.i.hi += D_801375B8;
                    }
                    if ((ent->flags & FLAG_UNK_40000) != 0) {
                        ent->posX.val -= D_801375A4;
                        ent->posY.val -= D_801375A8;
                    }
                }
            }
            func_80121F14(D_801375B4 << 0x10, D_801375B8 << 0x10);
            D_801375A4 = D_801375A6;
            D_801375A8 = D_801375AA;
            // Note: g_PrimBuf is MAX_PRIM_COUNT=1280 total in size.
            for (i = 0, prim = &g_PrimBuf[0]; i < 1024; i++, prim++) {
                if (prim->blendMode & 2) {
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
                } else if (prim->blendMode & 0x200) {
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
            DrawHudAlucard();
            func_800E414C();
            if (D_80137598 != 0) {
                func_80105428();
            }
            if (g_Player.unk0C & 0x80000) {
                D_8003C9A4 = 10;
                g_MenuStep = MENU_STEP_INIT;
            }
            if (D_800973FC != 0) {
                if (D_8006BB00 == 0) {
                    D_8006BB00 = 1;
                    MuteCd();
                }
            } else if (D_8006BB00 != 0) {
                if (*D_80097400 != 0) {
                    D_80097928 = 0;
                    D_8006BB00 = 0;
                    UnMuteCd();
                } else if (D_80097928 == 0) {
                    D_8006BB00 = 0;
                    UnMuteCd();
                } else {
                    UnMuteCd();
                    if (!(D_8003C708.flags & 0x60)) {
                        PlaySfx(D_80097910);
                        if (D_80097910 != 0) {
                            D_80097928 = 0;
                        }
                    }
                    D_8006BB00 = 0;
                }
            }
            if (!(g_Player.unk0C & 0x40000)) {
                if ((g_pads[0].tapped & PAD_START) && (D_8003C8B8 != 0)) {
                    func_801027A4();
                    if ((g_StageId == STAGE_ST0) ||
                        (g_PlayableCharacter != PLAYER_ALUCARD)) {
                        if (func_8010183C(0) == 0) {
                            return;
                        }
                        D_800974A4 = 1;
                        D_8003C9A4 = 0x70;
                        PlaySfx(0xa7);
                        PlaySfx(0xa3);
                        PlaySfx(SET_UNK_0E);
#if defined(VERSION_US)
                        if (g_StageId == STAGE_ST0) {
                            MuteCd();
                        }
#endif
                        return;
                    }
                    PlaySfx(0xa7);
                    PlaySfx(0xa3);
                    PlaySfx(SET_UNK_0E);
                    func_801027C4(1);
                    D_8003C9A4++;
                    g_MenuStep = MENU_STEP_INIT;
                } else if ((g_pads[0].tapped & PAD_SELECT) &&
                           (g_StageId != STAGE_ST0) && (D_8003C8B8 != 0)) {
                    func_801027C4(6);
                    D_800974A4 = 1;
                    D_8003C9A4 = 20;
                }
                break;
            }
            break;
        case 0x70:
            DrawHudAlucard();
            if (g_pads[0].tapped & PAD_START) {
                if (func_8010183C(1) != 0) {
                    D_800974A4 = 0;
                    D_8003C9A4 = 1;
                    PlaySfx(SET_UNK_0F);
                    PlaySfx(0xA4);
                    PlaySfx(0xA8);
#if defined(VERSION_US)
                    if (g_StageId == STAGE_ST0) {
                        UnMuteCd();
                    }
#endif
                }
            }
            func_801028AC(1);
            break;
        case 0x2:
            HandleMenu();
            func_801028AC(1);
            break;
        case 0x14:
            if (D_8013AED0 != 0) {
                func_800F2658();
            }
            if (g_pads[0].tapped & (PAD_START | PAD_SELECT)) {
                func_801027C4(7);
                D_800974A4 = 0;
                D_8003C9A4 = 1;
            }
            g_api.o.unk28();
            func_80102D70();
            func_801028AC(1);
            break;
        case 0x3:
            switch (g_MenuStep) {
            case 0:
                if (D_80097C98 == 2) {
                    func_800EA5AC(0xFF, 0xFF, 0xFF, 0xFF);
                    g_MenuStep = MENU_STEP_EXIT_BEGIN;
                } else {
                    func_801027C4(1);
                case 2:
                    g_MenuStep++;
                }
                break;
            case 1:
                if (func_801025F4() != 0) {
                    g_MenuStep++;
                }
                break;
            case 3:
                if (g_IsUsingCd) {
                    if (D_80097C98 == 2) {
                        func_800EA5AC(0xFF, 0xFF, 0xFF, 0xFF);
                    }
                    break;
                } else if (D_80097928 != 0) {
                    D_80097910 = g_StagesLba[g_StageId].unk18;
                    if (D_800973FC != 1) {
                        PlaySfx(SET_STOP_MUSIC);
                        if (func_80131F68() == false) {
                            PlaySfx(D_80097910);
                            D_80097928 = 0;
                        } else {
                            break;
                        }
                    }
                }
                if (D_80137598 != 0) {
                    func_8010427C();
                    D_80137598 = 0;
                }
                layer = g_api.o.tileLayers[D_801375BC.def->tileLayoutId].fg;
                if (layer->rect.params & 0x80) {
                    D_801375BC.def =
                        &g_api.o.rooms[layer->rect.params & 0x7F].load;
                    // TODO: !FAKE
                    // D_8009791C is probably part of a struct. see also
                    // (&g_Tilemap.cameraX)->i.hi seen elsewhere
                    // in this function. do-while prevents instruction
                    // reordering
                    do {
                        D_8009791C = layer->zPriority;
                    } while (0);
                    D_80097920 = layer->flags;
                } else {
                    D_8009791C = (playerX >> 8) + g_Tilemap.left;
                    D_80097920 = (playerY >> 8) + g_Tilemap.top;
                }
                D_8013759C = PLAYER.posX.val;
                D_801375A0 = PLAYER.posY.val;
                PLAYER.posX.i.hi = D_801375C0 + g_Tilemap.cameraX.i.hi;
                PLAYER.posY.i.hi = D_801375C4 + g_Tilemap.cameraY.i.hi;
                if (D_8003C708.flags & 0x60) {
                    LoadGfxAsync(ANIMSET_DRA(1));
                }
                func_800EA538(2);
                if (D_801375BC.def->tilesetId != 0) {
                    func_800EA5E4(
                        (D_801375BC.def->tilesetId + 0x7FFF) | 0x4000);
                }
                if (D_801375BC.def->objGfxId != 0) {
                    LoadGfxAsync(D_801375BC.def->objGfxId + 0x7FFF);
                    D_80097904 = D_801375BC.def->objGfxId + 0x7FFF;
                } else {
                    D_80097904 = 0;
                }
                func_800F2404(1);
                PLAYER.posY.i.hi = (u8)PLAYER.posY.i.hi;
                PLAYER.posX.i.hi = (u8)PLAYER.posX.i.hi;
                LoadRoomLayer(D_801375BC.def->tileLayoutId);
                if (D_8003C708.flags & 0x20) {
                    LoadGfxAsync(ANIMSET_DRA(3));
                }
                if (D_8003C708.flags & 0x40) {
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
                (&g_Tilemap.cameraX)->i.hi = (D_8009791C - g_Tilemap.left) << 8;
                g_Tilemap.cameraY.i.hi = (D_80097920 - g_Tilemap.top) << 8;
                playerX = PLAYER.posX.i.hi + g_Tilemap.cameraX.i.hi;
                playerY = PLAYER.posY.i.hi + g_Tilemap.cameraY.i.hi;
                func_8011A9D8();
                PLAYER.zPriority = g_unkGraphicsStruct.g_zEntityCenter.S16.unk0;
                func_800F0CD8(0);
                func_8010BFFC();
                playerX = PLAYER.posX.i.hi + g_Tilemap.cameraX.i.hi;
                playerY = PLAYER.posY.i.hi + g_Tilemap.cameraY.i.hi;
                func_800F0CD8(0);
                if (g_StageId == STAGE_RTOP) {
                    DestroyEntities(0x40);
                    for (i = 0; i < LEN(g_unkGraphicsStruct.D_8009742C); i++) {
                        g_unkGraphicsStruct.D_8009742C[i] = 0;
                    }
                    D_80073074 = (s32)g_Tilemap.cameraX.i.hi;
                    D_8007307C = (s32)g_Tilemap.cameraY.i.hi;
                    g_api.o.InitRoomEntities(D_801375BC.def->objLayoutId);
                    g_api.o.Update();
                    func_800F0CD8(0);
                    func_800F0CD8(0);
                    DestroyEntities(0x40);
                    for (i = 0; i < LEN(g_unkGraphicsStruct.D_8009742C); i++) {
                        g_unkGraphicsStruct.D_8009742C[i] = 0;
                    }
                }
                D_801375A4 = D_8013759C - PLAYER.posX.val;
                D_801375A8 = D_801375A0 - PLAYER.posY.val;
                for (i = 0, ent = &g_Entities[0]; i < LEN(g_Entities); i++,
                    ent++) {
                    if (ent->flags & 0x20000) {
                        ent->posX.val -= D_801375A4;
                        ent->posY.val -= D_801375A8;
                    }
                }
                i = 0;
                func_80121F14(-D_801375A4, -D_801375A8);
                D_801375A4 = D_801375A6;
                D_801375A8 = D_801375AA;
                // Note: g_PrimBuf is MAX_PRIM_COUNT=1280 total in size.
                for (i = 0, prim = &g_PrimBuf[0]; i < 1024; i++, prim++) {
                    if (prim->blendMode & 0x100) {
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
                    DestroyEntities(0x40);
                    for (i = 0; i < LEN(g_unkGraphicsStruct.D_8009742C); i++) {
                        g_unkGraphicsStruct.D_8009742C[i] = 0;
                    }
                    D_80073074 = g_Tilemap.cameraX.i.hi;
                    D_8007307C = g_Tilemap.cameraY.i.hi;
                    g_api.o.InitRoomEntities(D_801375BC.def->objLayoutId);
                    g_api.o.Update();
                    func_800F0CD8(0);
                    func_800F0CD8(0);
                    DestroyEntities(0x40);
                    for (i = 0; i < LEN(g_unkGraphicsStruct.D_8009742C); i++) {
                        g_unkGraphicsStruct.D_8009742C[i] = 0;
                    }
                }
                D_80073074 = g_Tilemap.cameraX.i.hi;
                D_8007307C = g_Tilemap.cameraY.i.hi;
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
                    D_8003C9A4 = 1;
                }
#if defined(VERSION_US)
                func_8011A9D8();
#endif
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
                    D_8003C9A4 = 1;
                }
                break;
            }
            func_801028AC(1);
            func_801028AC(1);
            break;
        case 0x5:
            if (*D_80097420 != 0) {
                if (g_StageId != STAGE_ST0) {
                    if (g_PlayableCharacter == PLAYER_ALUCARD) {
                        if (*D_80097420 == 0xFFF) {
                            EntityAlucard();
                            func_8011A870();
                            g_api.o.unk28();
                            if (g_pads[1].pressed & PAD_DOWN) {
                                *D_80097420 = 0;
                            }
                        } else {
                            if (*D_80097420 != 0xFF) {
                                func_8010DF70(*D_80097420);
                                func_8011A4D0();
                            }
                            g_api.o.unk28();
                            func_80102D70();
                        }
                    } else {
                        g_api.o.unk28();
                        func_80102D70();
                    }
                } else {
                    D_8013759C = PLAYER.posX.i.hi;
                    D_801375A0 = PLAYER.posY.i.hi;
                    RichterUpdater = D_8013C000;
                    RichterUpdater();
                    RichterUpdater = D_8013C008;
                    RichterUpdater();
                    D_801375A4 = D_8013759C - PLAYER.posX.i.hi;
                    D_801375A8 = D_801375A0 - PLAYER.posY.i.hi;
                    playerX -= D_801375A4;
                    playerY -= D_801375A8;
                }
            } else {
                func_8010E168(1, 0x30);
                D_8003C9A4 = 1;
                PlaySfx(SET_UNK_0F);
            }
            DrawHudAlucard();
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
                    func_800E34A4(-1);
                    DestroyEntities(0);
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
                func_800E346C();
                break;
            }
            func_801028AC(0);
            break;
        }
    }
}
