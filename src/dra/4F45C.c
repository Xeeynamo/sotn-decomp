#include "dra.h"

enum CollisionTypes {
    // most common block type
    COLLISION_TYPE_SOLID = 0x03,

    // right slanting 45* angle (/)
    COLLISION_TYPE_RIGHT_45_ANGLE = 0x80,

    // left slanting 45* angle (\)
    COLLISION_TYPE_LEFT_45_ANGLE = 0x83,

    // right slanting 45* angle on ceiling (\)
    COLLISION_TYPE_RIGHT_CEILING_45_ANGLE = 0x84,

    // left slanting 45* angle on ceiling (/)
    COLLISION_TYPE_LEFT_CEILING_45_ANGLE = 0x87,

    // 22.5* angle sloping left (/) takes two tiles to go up one tile
    COLLISION_TYPE_LEFT_225_ANGLE_1 = 0x88,

    // tile #2 of previous
    COLLISION_TYPE_LEFT_225_ANGLE_2 = 0x89,

    // flat tile you can press down + jump to drop through
    COLLISION_TYPE_FLAT_DROP_THROUGH = 0xE7,

    // water
    COLLISION_TYPE_WATER = 0xED
};

void CheckCollision(s32 x, s32 y, Collider* res, s32 unk) {
    Collider sp10;
    Collider sp38;
    s32 temp_a0_2;
    int new_var3;
    s32 temp_a0_3;
    s32 absX;
    s32 absY;
    s32 temp_v0_10;
    s32 temp_v0_11;
    int new_var;
    s32 temp_v0_6;
    s32 temp_v0_8;
    s32 temp_v0_9;
    s32 temp_v1;
    s32 temp_v1_2;
    int new_var2;
    s32 temp_v1_5;
    s32 temp_v1_8;
    u32 var_a1;
    s32 var_v0_2;
    s32 temp_a0;
    u32 temp_a0_4;
    u32 temp_a0_5;
    u32 temp_a0_6;
    u32 temp_v0_3;
    u32 temp_v1_10;
    u32 temp_v1_3;
    u32 temp_v1_4;
    u32 temp_v1_6;
    u32 temp_v1_7;
    u32 temp_v1_9;
    u32 var_v0;
    u8 colType;

    absX = x + g_Camera.posX.i.hi;
    absY = y + g_Camera.posY.i.hi;
    new_var = 0x10;
    if ((((absX < 0) || (((u32)absX) >= (g_CurrentRoom.hSize << 8))) ||
         (absY < 0)) ||
        (((u32)absY) >= (g_CurrentRoomVSize << 8))) {
        colType = 0;
    } else {
        u16 colTile = g_CurrentRoomTileLayout
                          .fg[(absX >> 4) +
                              (((absY >> 4) * g_CurrentRoom.hSize) * new_var)];
        colType = D_80073088->collision[colTile];
    }
    res->unk14 = -(absX & 0xF);
    res->unk4 = -(absX & 0xF);
    res->unk18 = -(absY & 0xF);
    res->unk8 = -(absY & 0xF);
    res->unk0 = 0;
    temp_v0_3 = res->unk14 + 0xF;
    res->unk1C = temp_v0_3;
    res->unkC = temp_v0_3;
    temp_v1 = res->unk18 + 0xF;
    res->unk20 = temp_v1;
    res->unk10 = temp_v1;
    if (!(colType & 0x80)) {
        res->unk0 = colType & 3;
        return;
    }

    var_a1 = 0;
    switch (colType) {
    case 0x81:
    case 0x82:
    case 0x8A:
    case 0x8B:
    case 0x98:
    case 0x99:
        if (unk == 0) {
            CheckCollision(x, y + res->unk18 - 1, &sp10, 1);
            if (0x8000 & sp10.unk0) {
                if (sp10.unk0 & 1) {
                    new_var3 = res->unk18 - 1;
                    res->unk18 = new_var3 + sp10.unk18;
                }
                sp10.unk0 |= 3;
                res->unk0 = sp10.unk0;
            } else {
                res->unk0 = 0x8003;
            }
        } else {
            res->unk0 = 1;
        }
        break;
    case COLLISION_TYPE_RIGHT_45_ANGLE:
        temp_v1_2 = res->unk1C + res->unk20;
        if (temp_v1_2 < 0x10) {
            res->unk18 = temp_v1_2 - 0xF;
            res->unk14 = temp_v1_2 - 0xF;
            res->unk0 = 0x8001;
        } else {
            res->unk0 = 0x8000;
        }
        break;
    case COLLISION_TYPE_LEFT_225_ANGLE_1:
        var_a1 = 0x10;
    case COLLISION_TYPE_LEFT_225_ANGLE_2:
        temp_v1_3 = var_a1 + res->unk1C + res->unk20 * 2;
        if (temp_v1_3 < 0x20) {
            res->unk14 = temp_v1_3 - 0x1F;
            res->unk0 = 0x9001;
            res->unk18 = ((var_a1 + res->unk1C) >> 1) + res->unk20 - 0xF;
        } else {
            res->unk0 = 0x9000;
        }
        break;
    case 0x94:
        var_a1 = 0x10;
    case 0x95:
        var_a1 += 0x10;
    case 0x96:
        var_a1 += 0x10;
    case 0x97:
        temp_v1_4 = var_a1 + res->unk1C + res->unk20 * 4;
        if (temp_v1_4 < 0x40) {
            res->unk14 = temp_v1_4 - 0x3F;
            res->unk0 = 0xA001;
            var_v0 = (var_a1 + res->unk1C) >> 2;
            res->unk18 = var_v0 + res->unk20 - 0xF;
        } else {
            res->unk0 = 0xA000;
        }
        break;
    case COLLISION_TYPE_LEFT_45_ANGLE:
        temp_a0 = res->unk1C;
        temp_v1_5 = res->unk20;
        if (temp_a0 >= temp_v1_5) {
            temp_v0_6 = temp_v1_5 - temp_a0;
            res->unk18 = temp_v0_6;
            res->unk1C = (-temp_v0_6);
            res->unk0 = 0xC001;
        } else {
            res->unk0 = 0xC000;
        }
        break;
    case 0x8C:
        var_a1 = 0x10;
    case 0x8D:
        temp_a0_2 = res->unk20;
        temp_v1_6 = var_a1 + res->unk1C;
        if (temp_v1_6 >= ((temp_a0_2 * 2))) {
            res->unk18 = (temp_a0_2 - (temp_v1_6 >> 1));
            res->unk0 = 0xD001;
        } else {
            res->unk0 = 0xD000;
        }
        break;
    case 0x9A:
        var_a1 = 0x10;
    case 0x9B:
        var_a1 += 0x10;
    case 0x9C:
        var_a1 += 0x10;
    case 0x9D:
        temp_a0_3 = res->unk20;
        temp_v1_7 = var_a1 + res->unk1C;
        if (temp_v1_7 >= temp_a0_3 * 4) {
            res->unk18 = temp_a0_3 - (temp_v1_7 >> 2);
            res->unk0 = 0xE001;
        } else {
            res->unk0 = 0xE000;
        }
        break;
    case 0x85:
    case 0x86:
    case 0x90:
    case 0x91:
    case 0xA2:
    case 0xA3:
        if (unk == 0) {
            CheckCollision(x, (y + res->unk20) + 1, &sp38, 1);
            if (0x800 & sp38.unk0) {
                if (sp38.unk0 & 1) {
                    temp_a0_2 = 1;
                    res->unk20 = res->unk20 + temp_a0_2 + sp38.unk20;
                }
                sp38.unk0 = sp38.unk0 | 3;
                res->unk0 = sp38.unk0 | 3;
            } else {
                res->unk0 = 0x803;
            }
        } else {
            res->unk0 = 1;
        }
        break;
    case COLLISION_TYPE_RIGHT_CEILING_45_ANGLE:
        temp_a0_4 = res->unk1C;
        temp_v1_8 = res->unk20;
        if (temp_v1_8 >= (s32)temp_a0_4) {
            temp_v0_8 = temp_a0_4 - temp_v1_8;
            res->unk14 = temp_v0_8;
            res->unk20 = -temp_v0_8;
            res->unk0 = 0x801;
        } else {
            res->unk0 = 0x800;
        }
        break;
    case 0x8E:
        var_a1 = 0x10;
    case 0x8F:
        temp_a0_5 = var_a1 + res->unk1C;
        temp_v1_9 = res->unk20 * 2;
        if (temp_v1_9 >= temp_a0_5) {
            temp_v0_9 = temp_a0_5 - temp_v1_9;
            res->unk14 = temp_v0_9;
            res->unk20 = -temp_v0_9 / 2;
            res->unk0 = 0x1801;
        } else {
            res->unk0 = 0x1800;
        }
        break;
    case 0x9E:
        var_a1 = 0x10;
    case 0x9F:
        var_a1 += 0x10;
    case 0xA0:
        var_a1 += 0x10;
    case 0xA1:
        temp_a0_6 = var_a1 + res->unk1C;
        temp_v1_10 = res->unk20 * 4;
        if (temp_v1_10 >= temp_a0_6) {
            temp_v0_10 = temp_a0_6 - temp_v1_10;
            res->unk14 = temp_v0_10;
            var_v0_2 = -temp_v0_10;
            if (var_v0_2 < 0) {
                var_v0_2 += 3;
            }
            res->unk20 = (s32)(var_v0_2 >> 2);
            res->unk0 = 0x2801;
        } else {
            res->unk0 = 0x2800;
        }
        break;
    case COLLISION_TYPE_LEFT_CEILING_45_ANGLE:
        if ((res->unk1C + res->unk20) >= 0xF) {
            res->unk0 = 0x4801;
            temp_v0_11 = res->unk18 + 0xF;
            temp_v0_11 = temp_v0_11 + res->unk14;
            res->unk20 = temp_v0_11;
            res->unk1C = (u32)temp_v0_11;
        } else {
            res->unk0 = 0x4800;
        }
        break;
    case 0x92:
        var_a1 = 0x10;
    case 0x93:
        if (((var_a1 + res->unk1C) + (res->unk20 * 2)) >= 0x1E) {
            temp_a0_5 = 0xF;
            res->unk0 = 0x5801;
            res->unk20 = (((var_a1 + res->unk14) - temp_a0_5) >> 1) +
                         (res->unk18 + temp_a0_5);
            ;
        } else {
            res->unk0 = 0x5800;
        }
        break;
    case 0xA4:
        var_a1 = 0x10;
    case 0xA5:
        var_a1 = var_a1 + 0x10;
    case 0xA6:
        var_a1 += 0x10;
    case 0xA7:
        new_var2 = 0xF;
        if (var_a1 + res->unk1C + res->unk20 * 4 >= 0x3C) {
            res->unk0 = 0x6801;
            res->unk20 =
                (((var_a1 + res->unk14) - 0x2D) >> 2) + (res->unk18 + new_var2);
        } else {
            res->unk0 = 0x6800;
        }
        break;
    case 0xFF:
        if (res->unk20 < 8) {
            res->unk0 = 3;
            res->unk18 = res->unk18 + 8;
        }
        break;
    case 0xFE:
        if (res->unk20 >= 8) {
            res->unk0 = 3;
            res->unk20 -= 8;
        }
        break;
    case 0xFD:
        if (res->unk20 < 8) {
            res->unk0 = 1;
            res->unk18 += 8;
        }
        break;
    case 0xFC:
        if (res->unk20 >= 8) {
            res->unk0 = 1;
            res->unk20 -= 8;
        }
        break;
    case 0xFB:
        res->unk0 = 4;
        break;
    case 0xFA:
        if (res->unk20 < 8) {
            if (1) {
                res->unk0 = 4;
            }
            res->unk18 += 8;
        }
        break;
    case 0xF9:
        if (res->unk20 < 8) {
            res->unk0 = 8;
            res->unk18 += 8;
        }
        break;
    case 0xF8:
        res->unk0 = 0x13;
        break;
    case 0xF4:
    case 0xF5:
    case 0xF6:
    case 0xF7:
        res->unk0 = 0x20;
        break;
    case 0xEE:
    case 0xEF:
    case 0xF0:
    case 0xF1:
    case 0xF2:
    case 0xF3:
        res->unk0 = 3;
        break;
    case COLLISION_TYPE_WATER:
        res->unk0 = 8;
        break;
    case 0xEA:
        if (res->unk20 >= 8) {
            res->unk0 = 8;
            res->unk20 -= 8;
        }
        break;
    case 0xE9:
        if (res->unk20 >= 8) {
            res->unk0 = 4;
            res->unk20 -= 8;
        }
        break;
    case 0xE8:
        if (res->unk20 < 8) {
            res->unk0 = 0x41;
            res->unk18 += 8;
        }
        break;
    case COLLISION_TYPE_FLAT_DROP_THROUGH:
        if (res->unk20 >= 8) {
            res->unk0 = 0x41;
            res->unk20 -= 8;
        }
        break;
    case 0xE6:
        if (res->unk20 < 8) {
            res->unk0 = 0x81;
            res->unk18 += 8;
        }
        break;
    case 0xE5:
        if (res->unk20 >= 8) {
            res->unk0 = 0x81;
            res->unk20 -= 8;
        }
        break;
    }
}

INCLUDE_ASM("asm/us/dra/nonmatchings/4F45C", func_800EFBF8);

INCLUDE_ASM("asm/us/dra/nonmatchings/4F45C", func_800F0334);

extern Unkstruct_aSimCBinDemoKey aSimCBinDemoKey;

void func_800F04A4(void) {
    Unkstruct_aSimCBinDemoKey sp10[10];
    char pad[12]; // !FAKE: Intentional padding to fix the stack pointer
    s32 temp;
    s32 device;

    sp10[0] = aSimCBinDemoKey;

    device = open((char*)&sp10, 0x200);

    if (device >= 0) {
        if (write(device, (void*)0x801E8000, 0x2000) < 0) {
            close(device);
            return;
        } else if (close(device) >= 0) {
            // !FAKE:
            sp10[0].unk0 = D_800DC4C0;
            sp10[0].unk4 = (temp = D_800DC4C4);
            do {
                func_800E2438((const char*)&sp10);
            } while (0);
        }
    }
}

void func_800F0578(s32 arg0) {
    D_80137590 = (s32*)0x801E8000;
    *((s32*)0x801E8000) = 0;

    func_800EFBF8(arg0);

    switch (arg0) {
    case 0:
    case 2:
        func_800F0334(arg0);
        D_80097914 = arg0 == 0 ? 1 : 4;
        break;

    case 1:
        D_80097914 = 2;

    default:
        break;
    }
}

INCLUDE_ASM("asm/us/dra/nonmatchings/4F45C", func_800F0608);

s32 func_800F087C(u32 chunkX, u32 chunkY) {
    RoomBossTeleport* phi_s1;
    s32 res;

    for (phi_s1 = D_800A297C; true; phi_s1++) {
        if (phi_s1->x == 0x80) {
            return 0;
        }

        res = phi_s1->x == chunkX;
        if (res && phi_s1->y == chunkY && phi_s1->stageId == g_StageId &&
            (phi_s1->bossId == 0xFF || func_800FD4C0(phi_s1->bossId, 0) == 0)) {
            return phi_s1->unk10 + 2;
        }
    }
}

INCLUDE_ASM("asm/us/dra/nonmatchings/4F45C", func_800F0940);

#ifndef NON_EQUIVALENT
INCLUDE_ASM("asm/us/dra/nonmatchings/4F45C", SetNextRoomToLoad);
#else
bool SetNextRoomToLoad(u32 chunkX, u32 chunkY) {
    s32 res;
    RoomHeader* room;

    if (D_80072F2C & 0x40000) {
        return false;
    }

    res = func_800F087C(chunkX, chunkY);
    if (res) {
        return res;
    }

    room = g_api.o.unk30;
loop_3:
    while (room->left != 0x40) {
        if (chunkX >= room->left && chunkY >= room->top &&
            room->right >= chunkX && room->bottom >= chunkY) {
            if (room->load.tilesetId == 0xFF &&
                D_800A245C[room->load.tileLayoutId].stageId == STAGE_ST0) {
                return false;
            }
            D_801375BC = &room->load;
            return true;
        }
        room++;
        goto loop_3;
    }
    return false;
}
#endif

#ifndef NON_EQUIVALENT
INCLUDE_ASM("asm/us/dra/nonmatchings/4F45C", func_800F0CD8);
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
                (g_EntityArray[0].posX.i.hi >> 8) + g_CurrentRoom.left,
                (g_EntityArray[0].posY.i.hi >> 8) + g_CurrentRoom.top);
            D_801375C0 = (u8)g_EntityArray[0].posX.i.hi;
            D_801375C4 = (u8)g_EntityArray[0].posY.i.hi;
            return var_v0;
        }
        if (arg0 == 0) {
            goto block_25;
        }
        if (playerX < g_CurrentRoom.x) {
            var_v0 = SetNextRoomToLoad(g_CurrentRoom.left - 1,
                                       (playerY >> 8) + g_CurrentRoom.top);
            if (var_v0) {
                D_80072F98 = 1;
                D_801375C0 = g_EntityArray[0].posX.i.hi + 0x100;
                D_801375C4 = g_EntityArray[0].posY.i.hi;
                return var_v0;
            }
            g_EntityArray[0].posX.i.hi = 0;
            playerX = g_CurrentRoom.x;
        }
        if (playerX >= g_CurrentRoom.width) {
            var_v0 = SetNextRoomToLoad(g_CurrentRoom.right + 1,
                                       (playerY >> 8) + g_CurrentRoom.top);
            if (var_v0) {
                D_80072F98 = 1;
                D_801375C0 = g_EntityArray[0].posX.i.hi - 0x100;
                D_801375C4 = g_EntityArray[0].posY.i.hi;
                return var_v0;
            }
            g_EntityArray[0].posX.i.hi = 0xFF;
            playerX = g_CurrentRoom.width - 1;
        }
    }
    if (D_80097424 == 0) {
        if (playerY < g_CurrentRoom.y + 4) {
            temp_v0 = SetNextRoomToLoad((playerX >> 8) + g_CurrentRoom.left,
                                        g_CurrentRoom.top - 1);
            if (temp_v0 != false) {
                D_80072F98 = 2;
                D_801375C0 = g_EntityArray[0].posX.i.hi;
                D_801375C4 = g_EntityArray[0].posY.i.hi + 0xD0;
                playerY -= 0x80;
                return temp_v0;
            }
            g_EntityArray[0].posY.i.hi = 0;
            playerY = g_CurrentRoom.y + 4;
        }
        var_s0 = 0x30;
        if ((!(*D_80072F20 & 1)) && !(D_80072F2C & 3)) {
            var_s0 = 0x18;
        }
        if (playerY >= ((g_CurrentRoom.height - var_s0) + 0x14)) {
            temp_v0 = SetNextRoomToLoad((playerX >> 8) + g_CurrentRoom.left,
                                        g_CurrentRoom.bottom + 1);
            if (temp_v0 != false) {
                D_80072F98 = 2;
                D_801375C0 = g_EntityArray[0].posX.i.hi;
                D_801375C4 = g_EntityArray[0].posY.i.hi - 0x100;
                D_801375C4 = D_801375C4 + var_s0;
                playerY += 0x80;
                return temp_v0;
            }
            g_EntityArray[0].posY.i.hi = 0x10F - var_s0;
            playerY = g_CurrentRoom.height - var_s0 + 0x13;
        }
    }
block_25:
    temp_a1 = g_CurrentRoom.x + *D_8009740C;

    if (playerX < temp_a1) {
        if (arg0 != 0 && g_CurrentRoom.hSize != 1 &&
            temp_a1 < playerX + D_801375A4) {
            g_EntityArray[0].posX.i.hi =
                (u16)g_EntityArray[0].posX.i.hi +
                (playerX + D_801375A4 - (g_CurrentRoom.x + *D_8009740C));
        }
        g_Camera.posX.i.hi = g_CurrentRoom.x;
    } else {
        temp_a1_2 = g_CurrentRoom.width + *D_8009740C - 0x100;
        if (temp_a1_2 < playerX) {
            if (arg0 != 0 && g_CurrentRoom.hSize != 1 &&
                playerX + D_801375A4 < temp_a1_2) {
                g_EntityArray[0].posX.i.hi =
                    ((u16)g_EntityArray[0].posX.i.hi) +
                    (((playerX + D_801375A4) + 0x100) -
                     (g_CurrentRoom.width + (*D_8009740C)));
            }
            g_Camera.posX.i.hi = g_CurrentRoom.width - 0x100;
        } else {
            g_Camera.posX.i.hi = playerX - (*D_8009740C);
            g_EntityArray[0].posX.i.hi = *D_8009740C;
        }
    }
    if (D_8009741C != 0) {
        if (playerY < g_CurrentRoom.y + 0x8C) {
            g_Camera.posY.i.hi = g_CurrentRoom.y + 4;
            g_EntityArray[0].posY.i.hi = playerY - g_Camera.posY.i.hi;
        } else if (g_CurrentRoom.height - 0x74 < playerY) {
            g_Camera.posY.i.hi = g_CurrentRoom.height - 0xFC;
            g_EntityArray[0].posY.i.hi = playerY - g_Camera.posY.i.hi;
        } else {
            g_EntityArray[0].posY.i.hi = 0x88;
            g_Camera.posY.i.hi = playerY - 0x88;
        }
    } else {
        new_var2 = 0x88;
        if (playerY < g_CurrentRoom.y + 0x8C) {
            if (g_Camera.posY.i.hi + new_var2 - playerY >= 4 &&
                g_CurrentRoom.y + 8 < g_Camera.posY.i.hi) {
                g_Camera.posY.i.hi -= 4;
                g_EntityArray[0].posY.i.hi += 4;
            } else if (g_Camera.posY.i.hi < g_CurrentRoom.y &&
                       g_CurrentRoom.y != 0) {
                g_Camera.posY.i.hi += 4;
                g_EntityArray[0].posY.i.hi -= 4;
            } else {
                g_Camera.posY.i.hi = g_CurrentRoom.y + 4;
                g_EntityArray[0].posY.i.hi = playerY - g_Camera.posY.i.hi;
            }
        } else {
            g_EntityArray[0].posY.i.hi = g_Camera.posY.i.hi;
            if (g_CurrentRoom.height - 0x74 < playerY) {
                g_Camera.posY.i.hi = g_CurrentRoom.height - 0xFC;
                g_EntityArray[0].posY.i.hi = playerY - g_Camera.posY.i.hi;
            } else if (g_Camera.posY.i.hi + new_var2 - playerY >= 4) {
                g_Camera.posY.i.hi -= 4;
                g_EntityArray[0].posY.i.hi += 4;
            } else {
                g_EntityArray[0].posY.i.hi = 0x88;
                g_Camera.posY.i.hi = playerY - 0x88;
            }
        }
    }
    return false;
}
#endif

void func_800F1424(void) {
    if (g_pads[1].tapped & PAD_R1) {
        D_800730A0.unk00 ^= 2;
    }
    if (g_pads[1].tapped & PAD_L1) {
        D_800730A0.unk00 ^= 1;
    }
    if ((g_pads[1].tapped & PAD_L2) && (D_800730A0.unk3C != 0)) {
        D_800730A0.unk54[0].unk00[0] ^= 1;
    }
}

INCLUDE_ASM("asm/us/dra/nonmatchings/4F45C", func_800F14CC);

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

void func_800F1770(s8 arg0[], s32 arg1, s32 arg2, s32 arg3) {
    s32 temp_v0 = (arg1 / 2) + (arg2 * 4);

    if (!(arg1 & 1)) {
        arg0[temp_v0] = (arg0[temp_v0] & 0xF0) + arg3;
    } else {
        arg0[temp_v0] = (arg0[temp_v0] & 0xF) + (arg3 * 0x10);
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

INCLUDE_ASM("asm/us/dra/nonmatchings/4F45C", func_800F180C);

INCLUDE_ASM("asm/us/dra/nonmatchings/4F45C", func_800F1868);

void func_800F18C4(s32 arg0, s32 arg1) {
    s8 sp10[20];
    s32 i;
    s32 j;

    func_800F180C(arg0, arg1, &sp10);

    for (i = 0; i < 4; i++) {
        for (j = 0; j < 5; j++) {
            func_800F1770(sp10, j, i, 0);
        }
    }
    func_800F1868(arg0, arg1, &sp10);
}

INCLUDE_ASM("asm/us/dra/nonmatchings/4F45C", func_800F1954);

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

INCLUDE_ASM("asm/us/dra/nonmatchings/4F45C", func_800F1B08);

INCLUDE_ASM("asm/us/dra/nonmatchings/4F45C", func_800F1D54);

INCLUDE_ASM("asm/us/dra/nonmatchings/4F45C", func_800F1EB0);

void func_800F1FC4(s32 arg0) {
    func_800F1EB0((playerX >> 8) + g_CurrentRoom.left,
                  (playerY >> 8) + g_CurrentRoom.top, arg0);
}

INCLUDE_ASM("asm/us/dra/nonmatchings/4F45C", func_800F2014);

INCLUDE_ASM("asm/us/dra/nonmatchings/4F45C", func_800F2120);

void func_800F223C(void) {
    g_StageId ^= 0x20;
    func_800F2120();
    g_StageId ^= 0x20;
}

INCLUDE_ASM("asm/us/dra/nonmatchings/4F45C", func_800F2288);

void func_800F2404(s32 arg0) {
    s32* temp;
    s32* ptr;
    s32 count;

    if (arg0 == 0) {
        D_80097410 = 0;
        D_800973F8 = 0;
        D_800973FC = 0;
    }

    temp = D_80097400;
    *temp = 0;
    D_8003C704 = 0;
    D_80097418 = 0;
    D_8009741C = 0;
    D_8009740C[0] = 0x80;

    if (D_80097410 != 0) {
        FreePolygons(D_80097414);
    }

    D_80097410 = 0;
    D_80097414 = 0;
    g_zEntityCenter.unk = 148;
    count = 7;

    ptr = &D_80097400[17];

    while (count >= 0) {
        *ptr = 0;
        count -= 1;
        ptr -= 1;
    }

    D_80097420[0] = 0;
    D_80097424 = 0;
    D_80097448 = 0;
    D_8009744C = 0;
    D_80097450 = 0;
    func_800E346C();
}

#ifndef NON_EQUIVALENT
INCLUDE_ASM("asm/us/dra/nonmatchings/4F45C", func_800F24F4);
#else
void func_801042C4(s32);
void func_80105428();
extern s32 D_80137598;

void func_800F24F4(void) {
    s32 castleX;
    s32 castleY;
    s32 phi_v1;
    s32 phi_a0;

    castleX = ((s32)playerX >> 8) + g_CurrentRoom.left;
    castleY = ((s32)playerY >> 8) + g_CurrentRoom.top;
    if (D_8003C708 & 0x20) {
        phi_v1 = g_StageId;
        if (phi_v1 == (STAGE_NO0 | STAGE_INVERTEDCASTLE_FLAG)) {
            if ((castleX == phi_v1) && (castleY == 0x24)) {
                if (func_800FD4C0(22, 0) == 0) {
                    func_800FD4C0(22, 1);
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
                    if (func_800FD4C0(1, 0)) {
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

INCLUDE_ASM("asm/us/dra/nonmatchings/4F45C", func_800F2658);

bool func_800F27F4(s32 arg0) {
    if (arg0 == 0) {
        if (D_800973FC != 0 || D_8006BB00 != 0 || D_8003C708 & 0x60) {
            return false;
        }
        D_801375C8 = 1;
        return true;
    }
    D_801375C8 = 8;
}
