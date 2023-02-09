#include "common.h"
#include "dra.h"
#include "objects.h"
#include "sfx.h"

void func_80113AAC(void) {
    s32 var_s1 = 0;
    s32 temp;

    D_80072F6A[0]++;
    if (func_8010FDF8(2) != 0) {
        return;
    }

    switch (PLAYER.unk2E) {
    case 0:
        if (D_80072F20[0] & 2) {
            func_801139CC(3);
            if ((D_80072F6A[0]) >= 5) {
                PLAYER.unk2E = 2;
                PLAYER.unk1E = 0x800;
                PLAYER.unk22 = 2;
                PLAYER.unk20 = 0;
                PLAYER.unk19 |= 4;
                PLAYER.facing = (PLAYER.facing + 1) & 1;
                func_8010DA48(0x2B);
            } else {
                PLAYER.unk2E = 3;
            }
        } else if (D_80072F6A[0] > 28) {
            PLAYER.unk2E = 1;
            PLAYER.accelerationY = -0x60000;
            func_8010DA48(0x1B);
        }
        break;

    case 1:
        if (D_80072F20[0] & 2) {
            PLAYER.unk2E = 2;
            func_801139CC(3);
        } else {
            PLAYER.accelerationY += 0x6000;
            if (PLAYER.accelerationY > 0x8000) {
                var_s1 = 1;
            }
        }
        break;

    case 2:
        D_800733F8 = 0;    // TODO: !FAKE: symbol should be PLAYER.unk20
        D_800733FA = 2;    // TODO: !FAKE: symbol should be PLAYER.unk22
        PLAYER.unk19 |= 4; // But it doesn't match with them for some reason
        if (D_80072F6A[0] >= 0x39) {
            func_8010DA48(0x2D);
            PLAYER.unk1E = 0;
            PLAYER.unk2E = 4;
            PLAYER.unk19 &= 0xFB;
            PLAYER.facing = (PLAYER.facing + 1) & 1;
        }
        break;

    case 3:
        if (D_80072F6A[0] > 20) {
            var_s1 = 1;
        }
        break;

    case 4:
        PLAYER.accelerationY += 0x1000;
        if (D_8007342A < 0) {
            var_s1 = 2;
        }
        break;
    }

    if (var_s1 != 0) {
        temp = 0; // TODO: !FAKE
        if ((var_s1 - 1) != temp) {
            func_8010DA48(0x1C);
        }
        PLAYER.palette = 0x8100;
        PLAYER.unk2E = 1;
        PLAYER.step = 4;
    }
}

s32 func_80113D7C(s16 arg0) {
    s32 sp10[3];
    s32 sfx;
    s32 temp_s0 = func_800FE97C(&sp10[0], 2, arg0 / 2, 1);
    s16 step;
    u16 temp_s1;

    func_80118C84(sp10[2], 0);
    func_800FE8F0();
    if (temp_s0 != 4) {
        D_80072F04 = 4;
        *D_80072F60 = 0x8166;
        sfx = D_800ACF8A[(rand() & 1)];
        PlaySfx(sfx);
        if (step && step) // TODO: !FAKE
            ;
        return 0;
    }
    step = PLAYER.step;
    temp_s1 = PLAYER.unk2E;
    sp10[0] = 0;
    sp10[1] = 0;
    func_8010D584(0x10);
    func_80115394(&sp10[0], step, temp_s1);
    return -1;
}

// !FAKE: too many temps
s16 func_80113E68(void) {
    s16 rnd = rand();
    s32 temp_v0;
    s32 var_a1;

    temp_v0 = rnd;
    PLAYER.unkAC = (rnd % 3) + 0x2E;
    var_a1 = rnd;
    if (rnd < 0) {
        var_a1 = rnd + 0xF;
    }
    return (temp_v0 - ((var_a1 >> 4) * 0x10));
}

void func_80113EE0(void) {
    PLAYER.animationSet = 1;
    PLAYER.unk19 &= 0xF3;
    PLAYER.animationFrameDuration = 0;
    PLAYER.animationFrameIndex = 0;
    PLAYER.objectId = 0;
    PLAYER.blendMode = 0;
    D_80072F64 = 0;
    D_80072F66 = 0;
    PLAYER.unk1E = 0;
    PLAYER.zPriority = g_zEntityCenter.S16.unk0;
    if (g_EntityArray[UNK_ENTITY_10].objectId == 0x22) {
        func_8010FAF4();
    }
}

void func_80113F7C(void) {
    Entity* entity = PLAYER.unkB8.entityPtr;
    s16 posX;
    s32 var_a0;
    s32 var_a2;

    if (entity->facing != 0) {
        var_a2 = -entity->unk10;
    } else {
        var_a2 = entity->unk10;
    }

    if (PLAYER.facing != 0) {
        var_a0 = -PLAYER.unk10;
    } else {
        var_a0 = PLAYER.unk10;
    }

    posX = var_a0 + PLAYER.posX.i.hi - entity->posX.i.hi - var_a2;

    if (ABS(posX) < 16) {
        if (entity->accelerationX != 0) {
            if (entity->accelerationX >= 0) {
                PLAYER.objectRoomIndex = 1;
                return;
            }
            goto block_14;
        }
        goto block_13;
    }
    // TODO: labels are !FAKE
block_13:
    if (posX < 0) {
    block_14:
        PLAYER.objectRoomIndex = 0;
        return;
    }

    PLAYER.objectRoomIndex = 1;
}

INCLUDE_ASM("asm/dra/nonmatchings/73AAC", func_8011405C);

INCLUDE_ASM("asm/dra/nonmatchings/73AAC", func_80114DF4);

INCLUDE_ASM("asm/dra/nonmatchings/73AAC", func_80115394);

void func_80115BB0(void) {
    PLAYER.unk19 = 4;
    PLAYER.accelerationY = 0;
    PLAYER.accelerationX = 0;
    PLAYER.animationFrameDuration = 4;

    if (D_80097420[0] == 0) {
        if (D_80072F20[0] & 1) {
            func_8010E570(0);
        } else {
            func_8010E7AC();
        }
        func_8011AAFC(g_CurrentEntity, 0x4A0000 | 0x2C, 0);
        D_80097D37 = 0;
    }
}

// same as RIC/func_8015BB80
void func_80115C50(void) {
    s32 dist;

    if (g_StageId == STAGE_TOP) {
        dist = (g_CurrentRoom.left * 256) + playerX;
        dist = ABS(dist);

        if (dist - 8000 > 0) {
            PLAYER.posX.i.hi--;
        }

        dist = (g_CurrentRoom.left * 256) + playerX;
        dist = ABS(dist);

        if (dist - 8000 < 0) {
            PLAYER.posX.i.hi++;
        }
    }

    if (g_StageId == (STAGE_TOP | STAGE_INVERTEDCASTLE_FLAG)) {
        dist = (g_CurrentRoom.left * 256) + playerX;
        dist = ABS(dist);

        if (dist - 8384 > 0) {
            PLAYER.posX.i.hi--;
        }

        dist = (g_CurrentRoom.left * 256) + playerX;
        dist = ABS(dist);

        if (dist - 8384 < 0) {
            PLAYER.posX.i.hi++;
        }
    }
}