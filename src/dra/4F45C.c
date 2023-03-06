#include "dra.h"

void CheckCollision(s32 x, s32 y, CollisionResult* res, s32 unk) {
    CollisionResult sp10;
    CollisionResult sp38;
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

    absX = x + g_Camera.posX.i.lo;
    absY = y + g_Camera.posY.i.lo;
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
    case 0x80:
        temp_v1_2 = res->unk1C + res->unk20;
        if (temp_v1_2 < 0x10) {
            res->unk18 = temp_v1_2 - 0xF;
            res->unk14 = temp_v1_2 - 0xF;
            res->unk0 = 0x8001;
        } else {
            res->unk0 = 0x8000;
        }
        break;
    case 0x88:
        var_a1 = 0x10;
    case 0x89:
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
    case 0x83:
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
    case 0x84:
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
    case 0x87:
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
    case 0xED:
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
    case 0xE7:
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
        D_8007308E = g_CurrentRoom.x;
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
            D_8007308E = g_CurrentRoom.width - 0x100;
        } else {
            D_8007308E = playerX - (*D_8009740C);
            g_EntityArray[0].posX.i.hi = *D_8009740C;
        }
    }
    if (D_8009741C != 0) {
        if (playerY < g_CurrentRoom.y + 0x8C) {
            D_80073092 = g_CurrentRoom.y + 4;
            g_EntityArray[0].posY.i.hi = playerY - D_80073092;
        } else if (g_CurrentRoom.height - 0x74 < playerY) {
            D_80073092 = g_CurrentRoom.height - 0xFC;
            g_EntityArray[0].posY.i.hi = playerY - D_80073092;
        } else {
            g_EntityArray[0].posY.i.hi = 0x88;
            D_80073092 = playerY - 0x88;
        }
    } else {
        new_var2 = 0x88;
        if (playerY < g_CurrentRoom.y + 0x8C) {
            if (D_80073092 + new_var2 - playerY >= 4 &&
                g_CurrentRoom.y + 8 < D_80073092) {
                D_80073092 -= 4;
                g_EntityArray[0].posY.i.hi += 4;
            } else if (D_80073092 < g_CurrentRoom.y && g_CurrentRoom.y != 0) {
                D_80073092 += 4;
                g_EntityArray[0].posY.i.hi -= 4;
            } else {
                D_80073092 = g_CurrentRoom.y + 4;
                g_EntityArray[0].posY.i.hi = playerY - D_80073092;
            }
        } else {
            g_EntityArray[0].posY.i.hi = D_80073092;
            if (g_CurrentRoom.height - 0x74 < playerY) {
                D_80073092 = g_CurrentRoom.height - 0xFC;
                g_EntityArray[0].posY.i.hi = playerY - D_80073092;
            } else if (D_80073092 + new_var2 - playerY >= 4) {
                D_80073092 -= 4;
                g_EntityArray[0].posY.i.hi += 4;
            } else {
                g_EntityArray[0].posY.i.hi = 0x88;
                D_80073092 = playerY - 0x88;
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

INCLUDE_ASM("asm/us/dra/nonmatchings/4F45C", func_800F2860);

INCLUDE_ASM("asm/us/dra/nonmatchings/4F45C", func_800F298C);

INCLUDE_ASM("asm/us/dra/nonmatchings/4F45C", func_800F483C);

bool IsAlucart(void) {
    if (CheckEquipmentItemCount(0xA8, 0) && CheckEquipmentItemCount(0xA7, 0) &&
        CheckEquipmentItemCount(0x59, 2))
        return true;
    return false;
}

INCLUDE_ASM("asm/us/dra/nonmatchings/4F45C", func_800F4994);

INCLUDE_ASM("asm/us/dra/nonmatchings/4F45C", func_800F4D38);

void func_800F4F48(void) {
    s32 i;

    for (i = 0; i < 2; i++) {
        g_playerEquip[i + 7] =
            func_800F4D38(g_playerEquip[i], g_playerEquip[1 - i]);
    }
}

INCLUDE_ASM("asm/us/dra/nonmatchings/4F45C", func_800F4FD0);

void func_800F53A4(void) {
    func_800F4994();
    func_800F4F48();
    func_800F4FD0();
}

void func_800F53D4(s32 tpage, s32 unkPrimIdx) {
    u32* unkPrim = D_8006C37C->_unk_0474;
    DR_MODE* drawMode = &D_8006C37C->drawModes[g_GpuUsage.drawModes];

    if (D_80137614 != 0) {
        SetDrawMode(drawMode, 0, 0, tpage, &D_800ACD80);
        AddPrim(&unkPrim[unkPrimIdx], drawMode);
        g_GpuUsage.drawModes++;
    }
}

u8 func_800F548C(u8 arg0) {
    u16 temp = arg0;

    if (arg0 & 0x80) {
        arg0 &= 0x7F;
        return func_800F548C(arg0 + 3);
    }
    return temp << 4;
}

bool IsOutsideDrawArea(s32 x0, s32 x1, s32 y0, s32 y1, MenuContext* context) {
    if (!(x1 > context->unk1.x)) {
        return true;
    }
    if (!(context->unk1.y < y1)) {
        return true;
    }
    if (x0 < (context->unk1.x + context->unk1.w)) {
        return (y0 < (context->unk1.y + context->unk1.h)) ^ 1;
    }
    return true;
}

bool ScissorPolyG4(POLY_G4* poly, MenuContext* context) {
    s32 scissorX;
    s32 scissorY;
    s32 diff;

    if (IsOutsideDrawArea(poly->x0, poly->x1, poly->y0, poly->y2, context))
        return true;

    if (poly->x0 < context->unk1.x) {
        diff = context->unk1.x - poly->x0;
        poly->x0 += diff;
        poly->x2 += diff;
    }

    if (poly->y0 < context->unk1.y) {
        diff = context->unk1.y - poly->y0;
        poly->y0 += diff;
        poly->y1 += diff;
    }

    scissorX = context->unk1.x + context->unk1.w;
    if (scissorX < poly->x1) {
        diff = poly->x1 - scissorX;
        poly->x1 -= diff;
        poly->x3 -= diff;
    }

    scissorY = context->unk1.y + context->unk1.h;
    if (scissorY < poly->y2) {
        diff = poly->y2 - scissorY;
        poly->y2 -= diff;
        poly->y3 -= diff;
    }

    return false;
}

bool ScissorPolyGT4(POLY_GT4* poly, MenuContext* context) {
    s32 scissorX;
    s32 scissorY;

    if (IsOutsideDrawArea(poly->x0, poly->x1, poly->y0, poly->y2, context))
        return true;

    if (poly->x0 < context->unk1.x) {
        s32 diff = context->unk1.x - poly->x0;
        poly->x0 += diff;
        poly->x2 += diff;
        poly->u0 += diff;
        poly->u2 += diff;
    }

    if (poly->y0 < context->unk1.y) {
        s32 diff = context->unk1.y - poly->y0;
        poly->y0 += diff;
        poly->y1 += diff;
        poly->v0 += diff;
        poly->v1 += diff;
    }

    scissorX = context->unk1.x + context->unk1.w;
    if (scissorX < poly->x1) {
        s32 diff = poly->x1 - scissorX;
        poly->x1 -= diff;
        poly->x3 -= diff;
        poly->u1 -= diff;
        poly->u3 -= diff;
    }

    scissorY = context->unk1.y + context->unk1.h;
    if (scissorY < poly->y2) {
        s32 diff = poly->y2 - scissorY;
        poly->y2 -= diff;
        poly->y3 -= diff;
        poly->v2 -= diff;
        poly->v3 -= diff;
    }

    return false;
}

bool ScissorSprite(SPRT* sprite, MenuContext* context) {
    s32 scissorY;
    s32 scissorX;
    s32 spriteX;
    s32 spriteY;

    if (IsOutsideDrawArea(sprite->x0, sprite->x0 + sprite->w, sprite->y0,
                          sprite->y0 + sprite->h, context))
        return true;

    if (sprite->x0 < context->unk1.x) {
        scissorX = context->unk1.x - sprite->x0;
        sprite->x0 += scissorX;
        sprite->u0 = sprite->u0 + scissorX;
        sprite->w = sprite->w - scissorX;
    }

    if (sprite->y0 < context->unk1.y) {
        scissorY = context->unk1.y - sprite->y0;
        sprite->y0 = sprite->y0 + scissorY;
        sprite->v0 = sprite->v0 + scissorY;
        sprite->h = sprite->h - scissorY;
    }

    scissorX = context->unk1.x + context->unk1.w;
    spriteX = sprite->x0 + sprite->w;
    if (scissorX < spriteX) {
        scissorY = spriteX - scissorX;
        sprite->w = sprite->w - scissorY;
    }

    scissorY = context->unk1.y + context->unk1.h;
    spriteY = sprite->y0 + sprite->h;
    if (scissorY < spriteY) {
        scissorX = spriteY - scissorY;
        sprite->h = sprite->h - scissorX;
    }

    return false;
}

INCLUDE_ASM("asm/us/dra/nonmatchings/4F45C", func_800F5904);

void func_800F5A90(void) {
    func_800F5904(NULL, 96, 96, 64, 64, 0, 0, 0, 0x114, 1, 0);
}

INCLUDE_ASM("asm/us/dra/nonmatchings/4F45C", func_800F5AE4);

void DrawMenuSprite(MenuContext* context, s32 x, s32 y, s32 width, s32 height,
                    s32 u, s32 v, s32 clut, s32 tpage, s32 arg9,
                    s32 colorIntensity, s32 argB) {
    u32* temp_s5 = D_8006C37C->_unk_0474;
    POLY_GT4* poly = &D_8006C37C->polyGT4[D_80097930[0]];
    s32 var_s2 = context->unk18 + 2;
    u32 polyColorIntensity;
    s32 temp_polyx0;

    if (context == &D_8013763A) {
        var_s2--;
    }

    poly->code &= 0xFD;

    if (arg9 != 0) {
        poly->code |= 1;
    } else {
        poly->code &= 0xFC;
    }

    func_80107360(poly, x, y, width, height, u, v);

    if (ScissorPolyGT4(poly, context) == false) {
        poly->tpage = tpage;
        poly->clut = D_8003C104[clut];
        func_80107250(poly, colorIntensity);
        if (argB == 1) {
            polyColorIntensity = (poly->y2 - poly->y0) * 4;
            func_801071CC(poly, polyColorIntensity, 0);
            func_801071CC(poly, polyColorIntensity, 1);
        }
        if (argB == 2) {
            temp_polyx0 = poly->x0;
            poly->x0 = poly->x2 = poly->x1;
            poly->x1 = poly->x3 = temp_polyx0;
        }
        AddPrim(&temp_s5[var_s2], poly);
        D_80097930[0]++;
        func_800F53D4(tpage, var_s2);
    }
}

// Matches with gcc 2.6.0 + aspsx 2.3.4
#ifndef NON_MATCHING
INCLUDE_ASM("asm/us/dra/nonmatchings/4F45C", DrawMenuRect);
#else
// NOTE: used to draw the menu cursor
void DrawMenuRect(MenuContext* context, s32 posX, s32 posY, s32 width,
                  s32 height, s32 r, s32 g, s32 b) {
    u32* temp_s1 = D_8006C37C->_unk_0474;
    POLY_G4* poly = &D_8006C37C->polyG4[D_80097930[1]];
    s32 temp_s2 = context->unk18 + 1;
    u32 temp;

    poly->x0 = posX;
    poly->y0 = posY;

    temp = (poly->x1 = posX + width);
    poly->y1 = posY;
    poly->x2 = posX;
    poly->x3 = temp;

    temp = (poly->y2 = posY + height);
    poly->y3 = temp;

    poly->code &= 0xFC;
    if (!ScissorPolyG4(poly, context)) {
        poly->r0 = poly->r1 = poly->r2 = poly->r3 = r;
        poly->g0 = poly->g1 = poly->g2 = poly->g3 = g;
        poly->b0 = poly->b1 = poly->b2 = poly->b3 = b;
        AddPrim(&temp_s1[temp_s2], poly);
        D_80097930[1]++;
        func_800F53D4(0, temp_s2);
    }
}
#endif

void func_800F5E68(MenuContext* context, s32 iOption, s32 x, s32 y, s32 w,
                   s32 h, s32 yGap, s32 bColorMode) {
    s32 r;

    if (bColorMode) {
        if (g_blinkTimer & 0x20) {
            r = (g_blinkTimer & 0x1F) + 0x60;
        } else {
            r = 0x7F - (g_blinkTimer & 0x1F);
        }
    } else {
        r = 0x80;
    }
    DrawMenuRect(context, x, y + (iOption * (h + yGap)), w, h, r, 0, 0);
}

INCLUDE_ASM("asm/us/dra/nonmatchings/4F45C", DrawRelicsMenu);

void DrawMenuAlucardPortrait(MenuContext* ctx) {
    DrawMenuSprite(ctx, 0x10, 0x24, 0x40, 0x40, 0, 0x80, 0x150, 0x9C, 1, 0, 0);
    DrawMenuSprite(ctx, 0x10, 0x64, 0x40, 0x20, 0, 0xC0, 0x150, 0x9C, 0, 0, 1);
}

s32 func_800F62E8(s32 context) {
    s32 temp_v0 = context * 3;
    s32 phi_v0 = temp_v0 < 0 ? temp_v0 + 3 : temp_v0;
    return phi_v0 >> 2;
}

// Apply cloak palette
INCLUDE_ASM("asm/us/dra/nonmatchings/4F45C", func_800F6304);

void DrawMenuAlucardCloakPreview(MenuContext* ctx) {
    DrawMenuSprite(ctx, 0xC0, 0x80, 0x20, 0x40, 0, 0xB0, 0x100, 7, 1, 0, 2);
    DrawMenuSprite(ctx, 0x100, 0x80, 0x40, 0x40, 0x80, 0xB0, 0x100, 7, 1, 0, 0);
}

void func_800F6508(MenuContext* context, s32 x, s32 y) {
    s32 yellow;

    if (g_blinkTimer & 0x10) {
        yellow = ((g_blinkTimer & 0xF) * 2) + 0x60;
    } else {
        yellow = 0x7F - (g_blinkTimer & 0xF);
    }
    DrawMenuRect(context, x, y, 0x70, 0xB, yellow, yellow, 0);
}

// Draw main menu cursor
void func_800F6568(MenuContext* arg0) {
    s32 height;
    s32 r;

    height = arg0->unk6 / 5;
    if (g_blinkTimer & 0x20) {
        r = (g_blinkTimer & 0x1F) + 0x40;
    } else {
        r = 0x5F - (g_blinkTimer & 0x1F);
    }
    DrawMenuRect(arg0, arg0->cursorX,
                 arg0->cursorY + (height * g_menuMainCursorIndex), arg0->unk4,
                 height, r, 0, 0);
}

// Draw equip menu cursor
void func_800F6618(s32 menuContextIndex, s32 bColorMode) {
    s32 r;
    MenuContext* context = (MenuContext*)&D_8013761C[menuContextIndex * 0x1E];

    if (bColorMode != 0) {
        r = 0x80;
    } else {
        if (g_blinkTimer & 0x20) {
            r = (g_blinkTimer & 0x1F) + 0x40;
        } else {
            r = 0x5F - (g_blinkTimer & 0x1F);
        }
    }
    DrawMenuRect(context, 0x70, (*g_menuRelicsCursorIndex * 0xD) + 0x1C, 0x71,
                 0xB, r, 0, 0);
}

void func_800F66BC(const char* str, s32 x, s32 y, MenuContext* context,
                   bool disableTexShade) {
    u16 temp;
    const int ChWidth = 12;
    const int ChHeight = 16;
    u8 ch;
    s32 unk;
loop_1:
    ch = *(str++);

    if (ch == 0xFF) {
        return;
    }
    unk = (u16)(ch & 0x10);
    unk = unk != 0;
    temp = ch;
    temp = temp >> 5;
    func_800F5904(context, x, y, ChWidth, ChHeight, (ch & 0xF) * ChWidth,
                  temp * ChHeight, 0x1A1, unk + 6, disableTexShade, 0x40);
    x += ChWidth;
    goto loop_1;
}

void DrawMenuChar(char ch, int x, int y, MenuContext* context) {
    func_800F5904(context, x, y, 8, 8, (ch & 0xF) * 8, (u32)(ch & 0xF0) >> 1,
                  0x196, 0x1E, 1, 0);
}

INCLUDE_ASM("asm/us/dra/nonmatchings/4F45C", DrawMenuStr);
// https://decomp.me/scratch/S4Dzb

void DrawMenuInt(s32 digit, s32 x, s32 y, MenuContext* context) {
    do {
        DrawMenuChar((digit % 10) + 16, x, y, context);
        digit /= 10;
        x += -8;
    } while (digit != 0);
}

INCLUDE_ASM("asm/us/dra/nonmatchings/4F45C", func_800F6998);

void func_800F6A48(void) {
    func_800EA538(6);
    func_800EA5E4(0x411);
}

INCLUDE_ASM("asm/us/dra/nonmatchings/4F45C", func_800F6A70);

INCLUDE_ASM("asm/us/dra/nonmatchings/4F45C", func_800F6BEC);

INCLUDE_ASM("asm/us/dra/nonmatchings/4F45C", func_800F6CC0);

INCLUDE_ASM("asm/us/dra/nonmatchings/4F45C", func_800F6DC8);

#ifndef NON_MATCHING
INCLUDE_ASM("asm/us/dra/nonmatchings/4F45C", DrawSettingsButton);
#else
extern s32 g_menuButtonSettingsCursorPos;
extern s32 g_menuButtonSettingsConfig[];
extern u8 c_chPlaystationButtons[];
extern u8 c_chShoulderButtons[];

void DrawSettingsButton(MenuContext* ctx) {
    s32 cursorX;
    s32 i;
    s32 x;
    s32 y;
    s32 buttonId;
    s32 btn1_x;
    s32 btn2_x;

    cursorX = 0x98;
    i = 0;
    x = 0xC0;
    y = 0x30;
    for (; i < 7; i++) {
        DrawMenuStr(c_strButtonRightHand[i], cursorX, y, ctx);
        buttonId = g_menuButtonSettingsConfig[i];
        btn1_x = (buttonId * 12) + 0x30;
        DrawMenuChar(c_chPlaystationButtons[buttonId], x + btn1_x, y, ctx);
        if (buttonId >= 4) {
            btn2_x = btn1_x + 8;
            DrawMenuChar(c_chShoulderButtons[buttonId], x + btn2_x, y, ctx);
        }
        y += 16;
    }

    func_800F5E68(ctx, g_menuButtonSettingsCursorPos, cursorX - 2, 46, 84, 12,
                  4, 1);
}
#endif

void DrawSettingsReverseCloak(MenuContext* context) {
    DrawMenuStr(c_strNormal, 176, 48, context);
    DrawMenuStr(c_strReversal, 176, 64, context);
    func_800F5E68(context, g_SettingsCloakMode, 174, 46, 64, 12, 4, 1);
}

void DrawSettingsSound(MenuContext* context) {
    s16 cursorX = context->cursorX;
    s16 cursorY = context->cursorY;
    s32 subMenuX = cursorX + 4;
    DrawMenuStr(c_strStereo, subMenuX, cursorY + 4, context);
    DrawMenuStr(c_strMono, subMenuX, cursorY + 0x14, context);
    func_800F5E68(context, g_SettingsSoundMode, cursorX + 2, cursorY + 2, 53,
                  12, 4, 1);
}

u8 func_800F7218(u16 arg0, u16 arg1) {
    if (arg0 == arg1) {
        return 0xE4;
    }

    if (arg0 < arg1) {
        return 0xE3;
    } else {
        return 0xE5;
    }
}

void func_800F7244(void) {
    s32 i;

    g_someValue = D_80097C1C[0];
    D_80137930 = D_80097C20;
    D_80137934 = D_80097C24;

    for (i = 0; i < 4; i++) {
        D_80137938[i] = D_80097C1C[i - 0x19] + D_80097C1C[i - 0x15];
    }
}

INCLUDE_ASM("asm/us/dra/nonmatchings/4F45C", func_800F72BC);

#ifndef NON_EQUIVALENT
INCLUDE_ASM("asm/us/dra/nonmatchings/4F45C", DrawPauseMenu);
#else
void func_800F6998(s32, s32 x, s32 y, MenuContext*, s32);
extern s32 g_menuButtonSettingsCursorPos;
extern s32 g_menuButtonSettingsConfig[];
extern const u8 c_chPlaystationButtons[];
extern const u8 c_chShoulderButtons[];
extern s32 D_8003C9FC;
extern s32 D_800A2D68;
extern s32 D_800A2D6C;
extern const char* D_800A83AC[];
extern s32 c_arrExpNext[];
extern s32 player_stat_str;

void DrawPauseMenu(s32 arg0) {
    MenuContext* context;
    s32 temp_s0;
    s32 temp_s0_2;
    s32 temp_s1;
    s32 temp_s1_2;
    s32 temp_v0;
    s32 playerLevel;
    s32 temp_v1_2;
    const char* strPlayerName;
    s32 expNext;
    s32 phi_s4;
    s32 phi_s3;
    s32 phi_s5;
    char phi_a0_3;
    s32 phi_a1;
    s32 phi_a0_4;
    s32 phi_a1_2;
    s32 phi_a2;
    s32 i;
    s32 phi_s3_2;
    s32 phi_s0;
    s32* phi_s1;
    s32 phi_a0_5;
    s32 phi_a1_3;
    s32 phi_s5_3;

    context = D_8013761C[arg0 * 15];
    func_800F53A4();
    if (arg0 == 1) {
        DrawMenuAlucardPortrait(context);

        if (IsAlucart()) {
            strPlayerName = c_strALUCART;
        } else {
            strPlayerName = c_strALUCARD;
        }
        DrawMenuStr(strPlayerName, 0x80, 0x28, context);
        DrawMenuStr(c_strHP, 0x60, 0x38, context);
        DrawMenuInt(D_80097B9C.hp, 0xA8, 0x38, context);
        DrawMenuChar(0xF, 0xB0, 0x38, context);
        DrawMenuInt(D_80097B9C.hpMax, 0xD0, 0x38, context);
        DrawMenuStr(c_strMP, 0x60, 0x44, context);
        DrawMenuInt(D_80097B9C.mp, 0xA8, 0x44, context);
        DrawMenuChar(0xF, 0xB0, 0x44, context);
        DrawMenuInt(D_80097B9C.mpMax, 0xD0, 0x44, context);
        DrawMenuStr(c_strHEART, 0x60, 0x50, context);
        DrawMenuInt(D_80097B9C.hearts, 0xA8, 0x50, context);
        DrawMenuChar(0xF, 0xB0, 0x50, context);
        DrawMenuInt(D_80097B9C.heartsMax, 0xD0, 0x50, context);
        DrawMenuStr(c_strEXP, 0x20, 0xB0, context);
        DrawMenuInt(g_playerExp, 0x90, 0xB0, context);
        DrawMenuStr(c_strNEXT, 0x20, 0xBC, context);
        playerLevel = g_playerLevel;
        if (playerLevel != 99) {
            expNext = c_arrExpNext[playerLevel] - g_playerExp;
        } else {
            expNext = 0;
        }
        DrawMenuInt(expNext, 0x90, 0xBC, context);
        DrawMenuStr(c_strGOLD[0], 0x20, 0xC8, context);
        DrawMenuInt(g_playerGold, 0x90, 0xC8, context);
        DrawMenuStr(c_strLEVEL, 0xF8, 0x28, context);
        DrawMenuInt(g_playerLevel, 0x130, 0x28, context);
        DrawMenuStr(c_strSTATUS, 0xF8, 0x38, context);

        temp_v1_2 = D_80072F2C;
        phi_s4 = 0x25;
        if (temp_v1_2 & 0x8000) {
            phi_s4 = 0x28;
        }
        if (temp_v1_2 & 0x4000) {
            phi_s4 = 0x26;
        }
        if (temp_v1_2 & 0x80) {
            phi_s4 = 0x27;
        }
        if (IsAlucart()) {
            phi_s4 = 0x2D;
        }
        DrawMenuStr(c_strGOLD[phi_s4], 0x104, 0x44, context);
        DrawMenuStr(c_strROOMS, 0xF0, 0x96, context);
        DrawMenuInt(g_roomCount, 0x148, 0x96, context);
        DrawMenuStr(c_strKILLS, 0xF0, 0xA4, context);
        DrawMenuInt(g_killCount, 0x148, 0xA4, context);
        DrawMenuStr(c_strTIME, 0xD0, 0xC0, context);
        DrawMenuInt(g_GameTimer.hours, 0x108, 0xC0, context);
        DrawMenuChar(0x1A, 0x110, 0xC0, context);
        func_800F6998(g_GameTimer.minutes, 0x120, 0xC0, context, 2);
        DrawMenuChar(0x1A, 0x128, 0xC0, context);
        func_800F6998(g_GameTimer.seconds, 0x138, 0xC0, context, 2);
    }

    phi_s3 = 0xE8;
    if (context == &D_8013763A) {
        phi_s3 = 0xF8;
        phi_s5 = 0x58;
    } else {
        phi_s5 = 0x50;
    }
    func_800F66BC(D_800A2D68, phi_s3, phi_s5, context, 1);

    temp_s1 = g_menuButtonSettingsConfig[0];
    phi_a1 = phi_s3 + 0x2C;
    if (temp_s1 < 4) {
        phi_a0_3 = (s32)c_chPlaystationButtons[temp_s1];
    } else {
        DrawMenuChar((s32)c_chPlaystationButtons[temp_s1], phi_s3 + 0x28,
                     phi_s5, context);
        phi_a0_3 = (s32)c_chShoulderButtons[temp_s1];
        phi_a1 = phi_s3 + 0x30;
    }
    DrawMenuChar(phi_a0_3, phi_a1, phi_s5, context);
    DrawMenuInt(*D_80097C1C, phi_s3 + 0x4C, phi_s5, context);

    temp_s1_2 = D_8003C9FC;
    phi_a1_2 = phi_s3 + 0x2C;
    if (temp_s1_2 < 4) {
        phi_a0_4 = (s32)c_chPlaystationButtons[temp_s1_2];
        phi_a2 = phi_s5 + 0xA;
    } else {
        temp_s0 = phi_s5 + 0xA;
        DrawMenuChar((s32)c_chPlaystationButtons[temp_s1_2], phi_s3 + 0x28,
                     temp_s0, context);
        phi_a0_4 = (s32)c_chShoulderButtons[temp_s1_2];
        phi_a1_2 = phi_s3 + 0x30;
        phi_a2 = temp_s0;
    }
    DrawMenuChar(phi_a0_4, phi_a1_2, phi_a2, context);
    temp_s0_2 = phi_s3 + 0x4C;
    DrawMenuInt(D_80097C20, temp_s0_2, phi_s5 + 0xA, context);
    func_800F66BC(D_800A2D6C, phi_s3, phi_s5 + 0x14, context, 1);
    DrawMenuInt(D_80097C24, temp_s0_2, phi_s5 + 0x1A, context);

    if (context == &D_8013763A) {
        phi_s3_2 = 0x20;
        phi_s5_3 = 0x78;
    } else {
        DrawMenuStr(D_800A83AC[*g_menuRelicsCursorIndex], 8, 0x28, context);
        phi_s3_2 = 0xC;
        phi_s5_3 = 0x46;
    }
    i = 0;
    phi_s0 = phi_s5_3;
    phi_s1 = &player_stat_str + 0x10;
    while (i < 4) {
        DrawMenuStr((&c_strSTR)[i], phi_s5_3, phi_s5_3, context);
        DrawMenuInt((&player_stat_str)[i], phi_s3_2 + 0x2C, phi_s0, context);
        temp_v0 = *phi_s1;
        if (temp_v0 != 0) {
            if (temp_v0 > 0) {
                DrawMenuChar(0xB, phi_s3_2 + 0x34, phi_s0, context);
                phi_a0_5 = *phi_s1;
                phi_a1_3 = phi_s3_2 + 0x44;
            } else {
                DrawMenuChar(0xD, phi_s5_3 + 0x34, phi_s0, context);
                phi_a0_5 = -((s32)(*phi_s1));
                phi_a1_3 = phi_s5_3 + 0x44;
            }
            DrawMenuInt(phi_a0_5, phi_a1_3, phi_s0, context);
        }
        phi_s0 += 0xC;
        i++;
        phi_s1++;
    }
}
#endif

INCLUDE_ASM("asm/us/dra/nonmatchings/4F45C", DrawSpellMenu);

INCLUDE_ASM("asm/us/dra/nonmatchings/4F45C", func_800F7F64);

void func_800F82F4(void) {
    RECT dstRect;

    dstRect.x = 448;
    dstRect.y = 176;
    dstRect.w = g_imgUnk8013C200->width >> 2;
    dstRect.h = g_imgUnk8013C200->height;
    LoadImage(&dstRect, (u_long*)g_imgUnk8013C200->data);

    dstRect.x = 480;
    dstRect.w = g_imgUnk8013C270->width >> 2;
    dstRect.h = g_imgUnk8013C270->height;
    LoadImage(&dstRect, (u_long*)g_imgUnk8013C270->data);
}

INCLUDE_ASM("asm/us/dra/nonmatchings/4F45C", DrawSystemMenu);

INCLUDE_ASM("asm/us/dra/nonmatchings/4F45C", func_800F84CC);

void func_800F86E4(void) {
    s32 i;

    for (i = 0; i < 16; i++) {
        FreePolygons(D_801377FC[i]);
    }

    FreePolygons(D_8013783C);
    FreePolygons(D_80137840);
}

void func_800F8754(MenuContext* context, s32 x, s32 y) {
    s32 curX;
    s32 phi_a1;

    if (D_801375DC == 0) {
        D_8013784C = 1;
    }

    DrawMenuStr(c_strSpells, x + 14, y + 20, context);
    if (D_801375FC == 0) {
        D_8013784C = 1;
    } else {
        D_8013784C = 0;
    }

    phi_a1 = x + 2;
    DrawMenuStr(c_strFamiliars, phi_a1, y + 68, context);
    D_8013784C = 0;
    DrawMenuStr(c_strEquip, x + 18, y + 4, context);
    curX = x + 14;
    DrawMenuStr(c_strRelics, curX, y + 36, context);
    DrawMenuStr(c_strSystem, curX, y + 52, context);
}

void func_800F8858(MenuContext* context) {
    s32 i = 0;
    const char** pStrEquipTypes = &c_strSSword;
    s32 phi_s2 = 8;
    s32* phi_s1 = &D_8003CACC;

    for (; i < 0xB; i++) {
        DrawMenuStr(pStrEquipTypes[*phi_s1], context->cursorX + 4,
                    context->cursorY + phi_s2, context);
        phi_s1++;
        phi_s2 += 0x10;
    }

    func_800F5E68(context, D_80137618, (s16)context->cursorX + 2,
                  (s16)context->cursorY + 4, 0x48, 0x10, 0, 1);
}

void func_800F892C(s32 index, s32 x, s32 y, MenuContext* context) {
    func_800F5904(context, x, y, 16, 16, (index & 7) * 16,
                  ((index & 0xF8) * 2) | 0x80, index + 0x1D0, 0x1A, 1, 0);
}

// Draw inventory in equip menu
// does not match due to stack bigger than expected
// matches in gcc 2.6.0 + aspsx 2.3.4
#ifndef NON_MATCHING
INCLUDE_ASM("asm/us/dra/nonmatchings/4F45C", func_800F8990);
#else
void func_800F8990(MenuContext* ctx, s32 x, s32 y) {
    const s32 Cols = 2;
    const s32 Width = 168;
    const s32 Height = 12;

    u8* sp20;
    s32 itemsPerPage;
    s32* new_var;
    s32 totalItemCount;
    s32 curX;
    s32 curY;
    s32 myX;
    s32 myY;
    s32 itemIndex;
    s32 i;
    s8* strEquipName;
    u16 icon;
    u16 palette;
    u8 equipId;
    u8* equipsAmount;
    s32 idx;

    new_var = &D_801375CC.equipTypeFilter;
    sp20 = func_800FD744(*new_var);
    equipsAmount = func_800FD760(*new_var);
    totalItemCount = func_800FD6C4(*new_var);
    curX = 0;
    curY = 0;
    itemsPerPage = Cols + ctx->unk6 / Height * Cols;
    for (i = 0; i < itemsPerPage; i++) {
        itemIndex = i + -ctx->h / Height * Cols;
        if (itemIndex >= totalItemCount) {
            break;
        }

        myX = 40 + x + (itemIndex & 1) * Width;
        myY = 4 + y + itemIndex / 2 * Height;
        if (g_IsSelectingEquipment && itemIndex == g_EquipmentCursor) {
            curX = myX + 1;
            curY = myY - 2;
        }

        equipId = sp20[D_801375D8[itemIndex]];
        if (equipsAmount[equipId] == 0)
            continue;

        strEquipName = GetEquipmentName(*new_var, equipId);
        if (D_801375CC.equipTypeFilter == 0) {
            icon = D_800A4B04[equipId].icon;
            palette = D_800A4B04[equipId].palette;
        } else {
            icon = D_800A7718[equipId].icon;
            palette = D_800A7718[equipId].palette;
        }

        func_800EB534(icon, palette, i);
        func_800F892C(i, myX - 16, myY - 4, ctx);
        DrawMenuStr(strEquipName, myX, myY, ctx);

        if (D_801375CC.equipTypeFilter == 0 && equipId != 0 ||
            D_801375CC.equipTypeFilter != 0 && equipId != 0x1A &&
                equipId != 0 && equipId != 0x30 && equipId != 0x39) {
            DrawMenuInt(equipsAmount[equipId], myX + 128, myY, ctx);
        }
    }

    if (g_IsSelectingEquipment) {
        func_800F6508(ctx, curX, curY);
    }
}
#endif

INCLUDE_ASM("asm/us/dra/nonmatchings/4F45C", func_800F8C98);

INCLUDE_ASM("asm/us/dra/nonmatchings/4F45C", func_800F8E18);

INCLUDE_ASM("asm/us/dra/nonmatchings/4F45C", func_800F8F28);

void func_800F9690(void) {
    POLY_GT4* poly = &D_80086FEC[D_8013783C];

    if (D_80137608 != 0) {
        poly->pad3 = 0x80;
    } else {
        poly->pad3 = 0x8;
    }
    if (D_801376B0 != 0) {
        poly->pad3 = 0x8;
    }
}

void func_800F96F4(void) { // !Fake:
    s32 new_var2;
    POLY_GT4* poly;
    s32 temp_a2;
    s32* temp;
    s32* new_var;

    new_var = D_80137848;
    poly = &D_80086FEC[D_80137840];
    temp_a2 = D_80137692 == 0;
    temp = D_80137844;

    if ((D_80137844[0] != 0) && (temp_a2 != 0)) {
        (&D_80086FEC[D_80137840])->pad3 = 0x80;
        if (D_80137844[0] == 1) {
            (&D_80086FEC[D_80137840])->clut = 0x188;
        } else {
            D_80137844[0] -= 1;
            (&D_80086FEC[D_80137840])->clut = 0x181;
        }
    } else {
        poly->pad3 = 0x8;
    }

    poly = (POLY_GT4*)poly->tag;
    temp = new_var;

    if (((*temp) != 0) && (temp_a2 != 0)) {
        poly->pad3 = 0x80;
        new_var2 = *temp;
        if (new_var2 == 1) {
            do {
                poly->clut = 0x188;
            } while (0);
            return;
        }
        *temp -= 1;
        poly->clut = 0x181;
        return;
    }
    poly->pad3 = 8;
}

void func_800F97DC(void) {
    D_8013794C = (s8*)&D_8007EFE4;
    D_80137950 = 0x180;
    D_80137954 = 0;
}

void func_800F9808(u32 arg0) {
    s32 temp_s0;
    s32 i;
    PixPattern* oldPos;

    temp_s0 = (arg0 == 2) ? 32 : 0;
    arg0 = func_800F548C(arg0);
    oldPos = (PixPattern*)D_8013794C;

    for (i = 0; i < ((temp_s0 + 0x100) * 8); i++) {
        *D_8013794C++ = 0;
    }

    LoadTPage(oldPos, 0, 0, 0x180, arg0, temp_s0 + 256, 16);
}

INCLUDE_ASM("asm/us/dra/nonmatchings/4F45C", func_800F98AC);

INCLUDE_ASM("asm/us/dra/nonmatchings/4F45C", func_800F99B8);

void func_800F9D40(s32 arg0, s32 arg1, s32 arg2) {
    if (arg2 != 0) {
        D_8013794C = &D_80082FE4;
    }

    D_80137950 = 0;
    D_80137954 = 0x100;
    func_800F98AC(arg0, arg1);
}

void func_800F9D88(s32 arg0, s32 arg1, s32 arg2) {
    if (arg2 != 0) {
        D_8013794C = &D_80082FE4;
    }
    D_80137950 = 0;
    D_80137954 = 0x100;
    func_800F99B8(arg0, arg1, 0);
}

void func_800F9DD0(u8* arg0, u8* arg1) {
    s32 i;

    for (i = 0; i < 16; i++) {
        if (*arg0 == 0)
            break;
        *arg1++ = *arg0++;
        *arg1++ = *arg0++;
    }
}

// https://decomp.me/scratch/VmuNt 99.46%
INCLUDE_ASM("asm/us/dra/nonmatchings/4F45C", func_800F9E18);

INCLUDE_ASM("asm/us/dra/nonmatchings/4F45C", func_800F9F40);

INCLUDE_ASM("asm/us/dra/nonmatchings/4F45C", func_800FA034);

INCLUDE_ASM("asm/us/dra/nonmatchings/4F45C", func_800FA3C4);

INCLUDE_ASM("asm/us/dra/nonmatchings/4F45C", func_800FA60C);

// https://decomp.me/scratch/JL0hI
// has some logic related to the weapon struct
INCLUDE_ASM("asm/us/dra/nonmatchings/4F45C", func_800FA7E8);

INCLUDE_ASM("asm/us/dra/nonmatchings/4F45C", func_800FA8C4);

INCLUDE_ASM("asm/us/dra/nonmatchings/4F45C", func_800FA9DC);

void func_800FAB1C(void) {
    Entity* entity = &g_EntityArray[UNK_ENTITY_4];
    s32 i;

    for (i = 4; i < 64; i++) {
        if ((u32)((entity->objectId + 0xFF30) & 0xFFFF) < 16) {
            DestroyEntity(entity);
        }
        entity++;
    }
}

Unkstruct_80137638 D_80137638[];

void func_800FAB8C(s32 arg0) {
    D_80137638[arg0].unk0 = 1;
    D_80137638[arg0].unk1 = 0;
}

void func_800FABBC(s32 arg0) {
    D_80137638[arg0].unk0 = 3;
    D_80137638[arg0].unk1 = 0;
}

void func_800FABEC(s32 context) { D_80137638[context].unk0 = 0; }

void func_800FAC0C(s32 context) { D_80137638[context].unk0 = 2; }

void func_800FAC30(void) {
    D_80137844[0] = 0;
    D_80137848[0] = 0;
}

void func_800FAC48(void) {
    ClearImage(&D_800ACD90, 0, 0, 0);
    ClearImage(&D_800ACD90 + 7, 0, 0, 0);
}

void func_800FAC98(void) { func_800F9808(2); }

bool func_800FACB8(void) {
    if (g_pads[0].tapped & 2) {
        (*g_menuRelicsCursorIndex)++;
        if (*g_menuRelicsCursorIndex == 7) {
            *g_menuRelicsCursorIndex = 0;
        }
        return true;
    }
    if (g_pads[0].tapped & 1) {
        g_menuRelicsCursorIndex[0]--;
        if (*g_menuRelicsCursorIndex == -1) {
            *g_menuRelicsCursorIndex = 6;
        }
        return true;
    }
    return false;
}

void func_800FAD34(s32 arg0, u8 arg1, u16 equipIcon, u16 palette) {
    D_80137608 = 0;
    func_800F9808(2);

    if (arg1) {
        D_80137608 = 1;
        func_800F99B8(arg0, 2, 0);
        func_800EB534(equipIcon, palette, 0x1F);
    }
}

INCLUDE_ASM("asm/us/dra/nonmatchings/4F45C", func_800FADC0);

void func_800FAE98(void) {
    func_800FADC0();
    D_800978F8 = 0x40;
}

INCLUDE_ASM("asm/us/dra/nonmatchings/4F45C", func_800FAEC4);

void func_800FAF44(s32 arg0) {
    s32 var_a0;
    s32 i;
    s32 j;
    s32* var_a1;

    D_801375D8 = &D_80084FE4;
    var_a1 = &D_80084FE4;

    if (arg0 == 0) {
        for (i = 0; i < 169; i++) {
            *var_a1 = i;
            var_a1++;
        }

        D_80137688 = D_8013768C = D_8003C9C8;
        return;
    }
    D_80137688 = D_8013768C = D_8003C9CC[D_801375D4 * 2];

    for (i = 0; i < 90; i++) {
        if (D_800A7734[i].unk00 == D_801375D4) {
            *var_a1 = i;
            var_a1++;
        }
    }
}

void func_800FB004(void) {
    s32 temp_a1 = func_800FD6C4(D_801375CC.equipTypeFilter);
    s32 temp_v0;

    if (((-D_80137688) / 12) != 0) {
        if (*D_80137844 == 0) {
            *D_80137844 = 1;
        }
    } else {
        *D_80137844 = 0;
    }

    temp_v0 = -D_80137688 + D_8013767C;

    if ((temp_v0 / 12) < (temp_a1 / 2)) {
        if (D_80137848[0] == 0) {
            D_80137848[0] = 1;
        }
    } else {
        D_80137848[0] = 0;
    }
}

void func_800FB0FC(void) {
    Unkstruct_800A2D98* temp = &D_800A2D98[*g_menuRelicsCursorIndex];
    s32 temp_a1 = temp->unk4;
    s32 new_var2 = temp->unk8;

    D_801375CC.equipTypeFilter = temp->equipTypeFilter;
    D_801375CC.unk8 = temp_a1;
    func_800FAF44(new_var2);
    func_800FB004();
}

INCLUDE_ASM("asm/us/dra/nonmatchings/4F45C", func_800FB160);

bool func_800FB1EC(s32 arg0) {
    if (D_801375CC.equipTypeFilter == 0) {
        if (arg0 == 0) {
            return true;
        }
    } else if ((arg0 == 0x1A) || (arg0 == 0) || (arg0 == 0x30) ||
               (arg0 == 0x39)) {
        return true;
    }

    return false;
}

INCLUDE_ASM("asm/us/dra/nonmatchings/4F45C", func_800FB23C);

INCLUDE_ASM("asm/us/dra/nonmatchings/4F45C", func_800FB9BC);

INCLUDE_ASM("asm/us/dra/nonmatchings/4F45C", func_800FBAC4);

INCLUDE_ASM("asm/us/dra/nonmatchings/4F45C", func_800FBC24);

INCLUDE_ASM("asm/us/dra/nonmatchings/4F45C", func_800FD39C);

s32 func_800FD4C0(s32 bossId, s32 action) {
    s32 temp_v0;
    s32 temp_v1;
    s32 seconds;
    s32 timer;

    switch (action) {
    // get the time attack for a specific defeated boss. this is also
    // responsible to check if the player should teleport into a boss room
    case 0:
        return D_8003CA28[bossId];

    // set new time attack record if the boss was not previously defeated
    case 1:
        timer = D_8003CA28[bossId];
        if (timer = timer != 0) {
            return D_8003CA28[bossId];
        }

        seconds = g_GameTimer.seconds;
        D_8003CA28[bossId] = seconds;
        temp_v1 = (g_GameTimer.minutes * 100) + seconds;
        D_8003CA28[bossId] = temp_v1;
        temp_v0 = (g_GameTimer.hours * 10000) + temp_v1;
        D_8003CA28[bossId] = temp_v0;
        return temp_v0;

    // set boss visited
    // not exactly sure yet why this flag is needed
    case 2:
        *D_8003CB00 |= 1 << bossId;
    }
}

bool func_800FD5BC(Unkstruct_800FD5BC* arg0) {
    s32 temp;

    if (arg0->unk4 != 5) {
        if (((u32)arg0->unk4) >= 0x10U) {
            temp = D_80097B9C.hpMax;
            if (D_80097B9C.hpMax < 0) {
                temp += 7;
            }
            arg0->unk8 = temp >> 3;
        } else if (D_80097B9C.hpMax >= (arg0->unk8 * 0x14)) {
            arg0->unk4 = 3;
        } else {
            arg0->unk4 = 2;
        }
    }
    if (D_80097B9C.hp <= arg0->unk8) {
        D_80097B9C.hp = 0;
        return true;
    } else {
        D_80097B9C.hp -= arg0->unk8;
        return false;
    }
}

s32 func_800FD664(s32 arg0) { return g_StageId & 0x20 ? arg0 << 1 : arg0; }

extern Unkstruct_800A4B12 D_800A4B12[];

u8 func_800FD688(s32 arg0) { return D_800A4B12[g_playerEquip[arg0]].unk0; }

INCLUDE_ASM("asm/us/dra/nonmatchings/4F45C", func_800FD6C4);

u8* func_800FD744(s32 equipTypeFilter) {
    u8* begin = g_InventoryOrder;
    if (equipTypeFilter != 0) {
        begin += 0xA9;
    }
    return begin;
}

u8* func_800FD760(s32 equipTypeFilter) {
    s8* begin = &g_Inventory;
    if (equipTypeFilter != 0) {
        begin += 0xA9;
    }
    return begin;
}

const char* GetEquipmentName(s32 equipTypeFilter, s32 equipId) {
    if (!equipTypeFilter) {
        return D_800A4B04[equipId].name;
    } else {
        return D_800A7718[equipId].name;
    }
}
