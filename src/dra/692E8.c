#include "dra.h"
#include "sfx.h"

void func_801092E8(s32 arg0) {
    D_800A37D8.D_800A37D8 = D_800ACE48[arg0 * 2];
    D_800A37D8.D_800A37DA = D_800ACE48[arg0 * 2 + 1];
    D_8006EBE0 = D_800ACE48[arg0 * 2];
}

void func_80109328(void) {
    s16* player_unk1E = &PLAYER.unk1E;

    g_Player.unk66 = 0;
    if (*player_unk1E == 0x800 && PLAYER.step == 8) {
        PLAYER.unk1E = 0;
        PLAYER.animCurFrame = 0x9D;
        PLAYER.facing = (PLAYER.facing + 1) & 1;
    }

    if (g_Player.D_80072F16 != 0) {
        g_Player.D_80072F16 = 0;
        func_801092E8(0);
    }
    PLAYER.blendMode = 0;
}

INCLUDE_ASM("asm/us/dra/nonmatchings/692E8", func_801093C4);

INCLUDE_ASM("asm/us/dra/nonmatchings/692E8", func_80109594);

void func_80109990(void) {
    if (D_80137FB4 == 0) {
        if (g_Status.mp == g_Status.mpMax && !(g_Player.unk0C & 0x100000)) {
            func_8011AAFC(g_CurrentEntity, 0x28, 0);
            PlaySfx(NA_SE_PL_MP_GAUGE);
            D_80137FB4++;
        }
    } else if (g_Status.mp != g_Status.mpMax) {
        D_80137FB4 = 0;
    }
}

INCLUDE_ASM("asm/us/dra/nonmatchings/692E8", func_80109A44);

// regalloc
// DECOMP_ME_WIP func_8010A234 https://decomp.me/scratch/rdeqb
#ifndef NON_MATCHING
INCLUDE_ASM("asm/us/dra/nonmatchings/692E8", func_8010A234);
#else
void func_8010A234(s32 arg0) {
    s32 temp;
    g_CurrentEntity = g_Entities;
    temp = D_8017A000.func_8017A018();

    do { // !FAKE
        if ((temp == 0x2D) && (CheckEquipmentItemCount(0x19, 2) != 0)) {
            if (!(*(s32*)&g_Player.unk0C & 0x01000000)) {
                PlaySfx(NA_SE_VO_AL_WHAT);
                g_Player.D_80072EF4 = 0;
                g_Player.D_80072EFC = 0x20;
                func_8010FAF4();
                D_8017A000();
                *(s32*)&g_Player.unk0C |= 0x01000000;
                func_8010DFF0(1, 10);
                func_80109328();
                if (arg0 != 0) {
                    func_8010DBFC(&D_800B0130, &D_800B01B8);
                }
            }
        } else if (*(s32*)&g_Player.unk0C & 0x01000000) {
            g_Entities[PLAYER_CHARACTER].palette = 0x8100;
            g_Entities[PLAYER_CHARACTER].animSet = 1;
            g_Entities[PLAYER_CHARACTER].unk5A = 0;
            g_Entities[PLAYER_CHARACTER].unk1E = 0;
            g_Entities[PLAYER_CHARACTER].unk19 &= 0xF3;
            func_8010FAF4();
            g_Entities[PLAYER_CHARACTER].unk22 = 0;
            g_Entities[PLAYER_CHARACTER].unk20 = 0;
            if (g_Player.pl_vram_flag & 1) {
                func_8010E570(0);
            } else {
                func_8010E7AC();
            }
            *(s32*)&g_Player.unk0C &= 0xFEFF0000 | 0xFFFF;
            func_80111CC0();
            if (arg0 != 0) {
                func_8010DBFC(&D_800B0130, &D_800B01B8);
            }
        }
    } while (0);
}
#endif

// Matching in gcc 2.6.0 + aspsx 2.3.4
// Matching in gcc 2.7.2 + aspsx (the one in decomp.me)
// DECOMP_ME_WIP func_8010A3F0 https://decomp.me/scratch/oKHMJ
#ifndef NON_MATCHING
INCLUDE_ASM("asm/us/dra/nonmatchings/692E8", func_8010A3F0);
#else
void func_8010A3F0(void) {
    s32 temp = 0x38;

    if (D_8017A000.func_8017A018() == temp &&
        D_8017D000.func_8017A018() == temp) {
        if (g_Player.D_80072F16 == 0) {
            func_801092E8(1);
        }
        g_Player.D_80072F16 = 0x20;
        temp = g_Player.unk10 != 0;
        if (temp && g_Status.D_80097C40 < -1) {
            g_Status.D_80097C40++;
        }
    }
    g_Player.unk10 = 0;
}
#endif

INCLUDE_ASM("asm/us/dra/nonmatchings/692E8", func_8010A4A4);

INCLUDE_ASM("asm/us/dra/nonmatchings/692E8", UpdateEntityAlucard);

void func_8010BF64(Unkstruct_8010BF64* arg0) {
    if (g_CurrentPlayableCharacter == PLAYER_ALUCARD) {
        arg0->unk14 = D_800ACEC6.unk1A - ((g_Player_unk0C / 2) & 2);
        arg0->unk1C = D_800ACEC6.unk1C + ((g_Player_unk0C / 2) & 2);
        arg0->unk18 = D_800ACEC6.unk10 - 1;
        arg0->unk20 = D_800ACEC6.unk0 + 1;
    } else {
        D_8013C00C();
    }
}

INCLUDE_ASM("asm/us/dra/nonmatchings/692E8", func_8010BFFC);

INCLUDE_ASM("asm/us/dra/nonmatchings/692E8", func_8010C36C);

INCLUDE_ASM("asm/us/dra/nonmatchings/692E8", func_8010C9F4);

INCLUDE_ASM("asm/us/dra/nonmatchings/692E8", func_8010D010);

INCLUDE_ASM("asm/us/dra/nonmatchings/692E8", func_8010D2C8);

void SetPlayerStep(PlayerSteps step) {
    PLAYER.step = step;
    PLAYER.step_s = 0;
}

INCLUDE_ASM("asm/us/dra/nonmatchings/692E8", func_8010D59C);

INCLUDE_ASM("asm/us/dra/nonmatchings/692E8", func_8010D800);

void func_8010DA2C(s32* arg0) {
    g_CurrentEntity->unk4C = arg0;
    g_CurrentEntity->animFrameDuration = 0;
    g_CurrentEntity->animFrameIdx = 0;
}

void func_8010DA48(u32 arg0) {
    g_CurrentEntity->ext.generic.unkAC = arg0;
    g_CurrentEntity->animFrameDuration = 0;
    g_CurrentEntity->animFrameIdx = 0;
}

INCLUDE_ASM("asm/us/dra/nonmatchings/692E8", func_8010DA70);

INCLUDE_ASM("asm/us/dra/nonmatchings/692E8", func_8010DB38);

INCLUDE_ASM("asm/us/dra/nonmatchings/692E8", func_8010DBFC);

#ifndef NON_EQUIVALENT
INCLUDE_ASM("asm/us/dra/nonmatchings/692E8", UpdateAnim);
#else
void UpdateAnim(FrameProperty* frameProps, s32* arg1) {
    AnimationFrame* animFrame;
    s8* frameProp;
    if (g_CurrentEntity->animFrameDuration == -1) {
    } else if (g_CurrentEntity->animFrameDuration == 0) {
        g_CurrentEntity->animFrameDuration =
            g_CurrentEntity->unk4C[g_CurrentEntity->animFrameIdx].duration;
    } else if (--g_CurrentEntity->animFrameDuration == 0) {
        g_CurrentEntity->animFrameIdx++;
        animFrame = &g_CurrentEntity->unk4C[g_CurrentEntity->animFrameIdx];
        switch ((u32)animFrame->duration) {
        case 0:
            g_CurrentEntity->animFrameIdx = animFrame->unk2;
            g_CurrentEntity->animFrameDuration =
                g_CurrentEntity->unk4C[g_CurrentEntity->animFrameIdx].duration;
            break;

        case 0xFFFF:
            g_CurrentEntity->animFrameIdx =
                g_CurrentEntity->animFrameIdx + 1 + animFrame->duration;
            g_CurrentEntity->animFrameDuration = -1;
            break;

        case 0xFFFE:
            g_CurrentEntity->unk4C = (s32*)arg1[animFrame->unk2];
            g_CurrentEntity->animFrameIdx = 0;
            g_CurrentEntity->animFrameDuration =
                g_CurrentEntity->unk4C[0].duration;
            break;

        default:
            g_CurrentEntity->animFrameDuration = animFrame->duration;
            break;
        }
    }
    if (frameProps != 0) {
        frameProp =
            frameProps +
            (g_CurrentEntity->unk4C[g_CurrentEntity->animFrameIdx].unk2 >> 9);
        g_CurrentEntity->unk10 = *(frameProp++);
        g_CurrentEntity->unk12 = *(frameProp++);
        g_CurrentEntity->hitboxWidth = frameProp[0];
        g_CurrentEntity->hitboxHeight = frameProp[1];
    }
    g_CurrentEntity->animCurFrame =
        g_CurrentEntity->unk4C[g_CurrentEntity->animFrameIdx].unk2 & 0x1FF;
}
#endif

void func_8010DF70(void) {
    g_CurrentEntity = &PLAYER;

    switch (PLAYER.ext.generic.unkAC) {
    case 0xBA:
    case 0xBB:
    case 0xBE:
    case 0xF0:
    case 0xF1:
        func_8010DBFC(D_800B0130, D_800B01B8);
    }
}

void func_8010DFF0(s32 arg0, s32 arg1) {
    POLY_GT4* poly;
    s32 i;

    if (arg0 != 0) {
        g_Entities[UNK_ENTITY_1].ext.generic.unk7C.U8.unk1 = 1;
        g_Entities[UNK_ENTITY_3].animCurFrame = 0;
        g_Entities[UNK_ENTITY_2].animCurFrame = 0;
        g_Entities[UNK_ENTITY_1].animCurFrame = 0;
        poly = &g_PrimBuf[g_Entities[UNK_ENTITY_1].firstPolygonIndex];

        for (i = 0; i < 6; i++) {
            poly->x1 = 0;
            poly = (POLY_GT4*)poly->tag;
        }
    }

    g_Entities[UNK_ENTITY_1].ext.generic.unk7C.U8.unk0 = 1;
    g_Entities[UNK_ENTITY_1].ext.generic.unk7E.modeU8.unk0 = 10;

    if (arg1 != 0) {
        if (arg1 < 4) {
            g_Player.D_80072F1E = 4;
        } else {
            g_Player.D_80072F1E = arg1;
        }
    }
}

void func_8010E0A8(void) {
    Entity* entity = &g_Entities[UNK_ENTITY_1];

    entity->ext.generic.unk7E.modeU8.unk0 = 0;
}

void func_8010E0B8(void) {
    Entity* entity = &g_Entities[UNK_ENTITY_1];

    entity->ext.generic.unk7C.U8.unk1 = 0;
    entity->ext.generic.unk7C.U8.unk0 = 0;
}

void func_8010E0D0(s32 arg0) {
    Entity* entity;

    if (arg0 == 1) {
        entity = func_8011AAFC(g_Entities, 0x47002C, 0);

        if (entity != NULL) {
            entity->flags |= FLAG_UNK_10000;
        }

        entity = func_8011AAFC(g_Entities, 0x40002C, 0);

        if (entity != NULL) {
            entity->flags |= FLAG_UNK_10000;
        }
    }
    func_8010DFF0(1, 1);
}

void func_8010E168(s32 arg0, s16 arg1) {
    if (arg0 == 0) {
        func_8011AAFC(g_CurrentEntity, 0x15002C, 0);
        if (arg1 >= g_Player.D_80072F1A) {
            g_Player.D_80072F1A = arg1;
        }
    } else if (g_Player.D_80072F1C <= arg1) {
        g_Player.D_80072F1C = arg1;
    }
}

void func_8010E1EC(s32 speed) {
    if (g_CurrentEntity->accelerationX < 0) {
        g_CurrentEntity->accelerationX += speed;
        if (g_CurrentEntity->accelerationX > 0) {
            g_CurrentEntity->accelerationX = 0;
        }
    } else {
        g_CurrentEntity->accelerationX -= speed;
        if (g_CurrentEntity->accelerationX < 0)
            g_CurrentEntity->accelerationX = 0;
    }
}

void func_8010E234(s32 speed) {
    if (g_CurrentEntity->accelerationY < 0) {
        g_CurrentEntity->accelerationY += speed;
        if (g_CurrentEntity->accelerationY > 0) {
            g_CurrentEntity->accelerationY = 0;
        }
    } else {
        g_CurrentEntity->accelerationY -= speed;
        if (g_CurrentEntity->accelerationY < 0) {
            g_CurrentEntity->accelerationY = 0;
        }
    }
}

s32 func_8010E27C(void) {
    u16* facing;

    if (g_Player.unk44 & 2) {
        return 0;
    }

    facing = &PLAYER.facing;
    if (*facing == 1) {
        if (g_Player.g_Player & 0x2000) {
            *facing = 0;
            g_Player.unk4C = 1;
            return -1;
        } else if (g_Player.g_Player & 0x8000) {
            return 1;
        }
    } else {
        if (!(g_Player.g_Player & 0x2000)) {
            if (g_Player.g_Player & 0x8000) {
                *facing = 1;
                g_Player.unk4C = 1;
                return -1;
            }
            return 0;
        }
        return 1;
    }
    return 0;
}

// DECOMP_ME_WIP func_8010E334 https://decomp.me/scratch/YvoMU
INCLUDE_ASM("asm/us/dra/nonmatchings/692E8", func_8010E334);

/*
 * Updates the Entity acceleration in the X Axis
 */
void AccelerateX(s32 accelerationX) {
    if (g_CurrentEntity->facing == 1) {
        accelerationX = -accelerationX;
    }
    g_CurrentEntity->accelerationX = accelerationX;
}

/*
 * Updates the Player acceleration in the X Axis
 */
void func_8010E3B8(s32 accelerationX) {
    if (PLAYER.objectRoomIndex == 1) {
        accelerationX = -accelerationX;
    }
    PLAYER.accelerationX = accelerationX;
}

void func_8010E3E0(void) {
    if (g_Player.unk48 != 0) {
        DestroyEntity(&g_Entities[16]);
        g_Player.unk48 = 0;
    }
}

void func_8010E42C(u16 arg0) {
    PLAYER.step_s = arg0;
    PLAYER.step = 18;

    if (!(arg0 & 1)) {
        func_8010DA48(0xF4);
    } else {
        func_8010DA48(0xF5);
    }
}

void func_8010E470(s32 arg0, s32 arg1) {
    PLAYER.accelerationX = arg1;
    PLAYER.accelerationY = 0;
    PLAYER.step = 2;
    PLAYER.step_s = D_800ACF4C[arg0 * 2 + 0];
    func_8010DA48(D_800ACF4C[arg0 * 2 + 1]);
}

// This may be the function that turns Alucard into stone
void func_8010E4D0(void) {
    func_80111CC0();

    PLAYER.palette = 0x8100;
    PLAYER.zPriority = g_zEntityCenter.S16.unk0;

    if ((u32)(g_Player.unk72 - 1) < 2U) {
        func_8010DA48(0xC7);
        PLAYER.accelerationY = 0;
        PLAYER.accelerationX = 0;
        SetPlayerStep(6);
        func_80111CC0();
        PlaySfx(NA_SE_VO_AL_WHAT);
        return;
    }
    func_80111CC0();
    func_8010E470(0, 0);
}

INCLUDE_ASM("asm/us/dra/nonmatchings/692E8", func_8010E570);
void func_8010E570(/*?*/ s32);

void func_8010E6AC(s32 arg0) {
    bool condition = false;

    condition = ((g_Player.pl_vram_flag & 0x20) != condition);
    AccelerateX(0x18000);
    PLAYER.accelerationY = 0;
    SetPlayerStep(1);

    if (arg0 != 0) {
        if (PLAYER.ext.generic.unkAC != 0xD) {
            func_8010DA48(0xD);
        }
    } else {
        func_8010DA48(7);
        func_8011AAFC(g_CurrentEntity, 0x50001, 0);
    }

    if (g_Player.unk4C != 0) {
        PLAYER.ext.generic.unkAC = 9;
    }

    if ((PLAYER.ext.generic.unkAC == 7) && (condition)) {
        PLAYER.animFrameIdx = 1;
    }

    if (g_Player.unk50 == 2) {
        PLAYER.animFrameIdx = 4;
    }
}

void func_8010E7AC(void) {
    SetPlayerStep(3);

    if (g_Player.unk50 != 1) {
        func_8010DA48(0x1C);
    }

    PLAYER.accelerationY = 0x20000;
    PLAYER.accelerationX = 0;
    g_Player.D_80072F0C = 8;

    if (g_Player.unk04 & 1) {
        g_Player.D_80072F0A = 8;
    } else {
        g_Player.D_80072F0A = 0;
    }

    g_Player.unk44 = 0x10;
}

void func_8010E83C(s32 arg0) {
    if (g_Player.unk72 != 0) {
        func_8010E7AC();
        return;
    } else if (func_8010E27C() != 0) {
        func_8010DA48(0x1A);
        AccelerateX(0x18000);
        g_Player.unk44 = 0;
    } else {
        func_8010DA48(0x16);
        PLAYER.accelerationX = 0;
        g_Player.unk44 = 4;
    }

    PLAYER.accelerationY = 0xFFFB0000 | 0x2000;
    SetPlayerStep(4);

    if (g_Player.unk50 == 1) {
        g_Player.unk44 |= 0x10;
    }

    if (arg0 != 0) {
        g_Player.unk44 &= ~1;
    } else {
        g_Player.unk44 |= 1;
    }
}

void func_8010E940(void) {
    g_Player.unk44 |= 0x21;
    func_8010DA48(0x20);
    PLAYER.step_s = 0;
    PLAYER.accelerationY = -0x44000;
    if (g_Player.unk72 != 0) {
        PLAYER.accelerationY = 0;
    }
}

void func_8010E9A4(void) {
    if (func_8010E27C() != 0) {
        AccelerateX(0x30000);
    } else {
        PLAYER.accelerationX = 0;
    }

    if (PLAYER.step == 4) {
        g_Player.unk44 |= 1;
    } else {
        g_Player.unk44 = 0;
    }

    func_8011AAFC(g_CurrentEntity, 2, 0);
    SetPlayerStep(8);
    PLAYER.accelerationY = -0xC0000;
    func_8010DA48(0x21);
    g_Player.unk4A = 0;
}

void func_8010EA54(s32 arg0) {
    s16 temp_hi;

    if (arg0 != 0) {
        temp_hi = rand() % arg0;
        NOP;

        if (temp_hi < 4) {
            PlaySfx(D_800ACF60[temp_hi]);
        }
    }
}

s32 func_8010EADC(s16 arg0, s16 arg1) {
    Entity* entity = &g_Entities[0x20];
    s32 i;
    s32 var_a2;
    s32 ret;

    for (i = 0, var_a2 = 0, ret = 0; i < 16; i++) {
        if (entity->objectId == 0) {
            ret++;
        }

        if (entity->ext.generic.unkB0 != 0) {
            if (entity->ext.generic.unkB0 == arg0) {
                var_a2++;
            }
        }

        if (var_a2 >= arg1) {
            return -1;
        }
        entity++;
    }

    return (ret == 0) ? -1 : 0;
}

INCLUDE_ASM("asm/us/dra/nonmatchings/692E8", func_8010EB5C);

// DECOMP_ME_WIP func_8010EC8C https://decomp.me/scratch/N8Srk
INCLUDE_ASM("asm/us/dra/nonmatchings/692E8", func_8010EC8C);

void func_8010ED54(u8 arg0) {
    PLAYER.accelerationY = 0;
    PLAYER.accelerationX = 0;
    SetPlayerStep(0xF);
    func_8010DA48(arg0);
    func_8011AAFC(g_CurrentEntity, 0x14003D, 0);
    g_Player.unk48 = 0;
}

INCLUDE_ASM("asm/us/dra/nonmatchings/692E8", func_8010EDB8);

void func_8010FAF4(void) {
    DestroyEntity(&g_Entities[UNK_ENTITY_10]);
    g_Player.unk46 = 0;
}

void func_8010FB24(void) {
    PLAYER.accelerationY = 0;
    PLAYER.accelerationX = 0;
    SetPlayerStep(0x22);
    func_8010E168(1, 0x10);
    func_8010E3E0();
}

void func_8010FB68(void) { // Related to Dark Methamorphosis
    PLAYER.accelerationY = 0;
    PLAYER.accelerationX = 0;
    SetPlayerStep(0x20);
    func_8010E3E0();
    func_8010DA48(0xBA);
    PlaySfx(NA_SE_VO_AL_DARK_METAMORPHOSIS);
    PlaySfx(NA_SE_PL_MP_GAUGE);
    g_Player.D_80072F16 = func_800FDB18(3, 0x400);
    func_801092E8(1);
    func_8011AAFC(g_CurrentEntity, 0x110028, 0);
    func_80118C28(0xB);
}

void func_8010FBF4(void) { // Related to Soul Steal spell
    PLAYER.accelerationY = 0;
    PLAYER.accelerationX = 0;
    SetPlayerStep(0x25);
    func_8010E3E0();
    func_8010DA48(0xDA);
    PlaySfx(NA_SE_VO_AL_SOUL_STEAL);
    func_80118C28(0xC);
    g_Player.D_80072F18 = 4;
}

void func_8010FC50(void) {
    PLAYER.accelerationY = 0;
    PLAYER.accelerationX = 0;
    SetPlayerStep(0x21);
    func_8010E3E0();
    func_8011AAFC(g_CurrentEntity, 0x75, 0);
    func_8010DA48(0xF0);
    PlaySfx(NA_SE_VO_AL_PUNCH);
    g_Player.D_80072F18 = 4;
}

void func_8010FCB8(void) {
    PLAYER.accelerationY = 0;
    PLAYER.accelerationX = 0;
    SetPlayerStep(0x23);
    func_8010E3E0();
    func_8011AAFC(g_CurrentEntity, 0x10075, 0);
    func_8010DA48(0xF1);
    PlaySfx(NA_SE_VO_AL_PUNCH);
    g_Player.D_80072F18 = 4;
}

void func_8010FD24(void) {
    PLAYER.accelerationY = 0;
    PLAYER.accelerationX = 0;
    SetPlayerStep(0x27);
    func_8010E3E0();
    func_8010DA48(0xF1);
    func_8011AAFC(g_CurrentEntity, 0x170028, 0);
    g_Player.D_80072F18 = 4;
}

void func_8010FD88(void) {
    PLAYER.step = 0;
    PLAYER.step_s = 3;
    AccelerateX(0xFFFC8000);
    g_CurrentEntity->accelerationY = 0;
    func_8010DA48(0xDB);
    func_8011AAFC(g_CurrentEntity, 0, 0);
    g_Player.unk46 = 0;
    PlaySfx(NA_SE_AL_BACKSLIDE);
}

INCLUDE_ASM("asm/us/dra/nonmatchings/692E8", func_8010FDF8);
s32 func_8010FDF8(/*?*/ s32);

// DECOMP_ME_WIP func_80110394 https://decomp.me/scratch/Akstc 94.80%
INCLUDE_ASM("asm/us/dra/nonmatchings/692E8", func_80110394);

INCLUDE_ASM("asm/us/dra/nonmatchings/692E8", func_801104D0);

INCLUDE_ASM("asm/us/dra/nonmatchings/692E8", func_801106A4);

INCLUDE_ASM("asm/us/dra/nonmatchings/692E8", func_8011081C);

INCLUDE_ASM("asm/us/dra/nonmatchings/692E8", func_80110968);

INCLUDE_ASM("asm/us/dra/nonmatchings/692E8", func_80110BC8);

INCLUDE_ASM("asm/us/dra/nonmatchings/692E8", func_80110DF8);

INCLUDE_ASM("asm/us/dra/nonmatchings/692E8", func_80111018);

INCLUDE_ASM("asm/us/dra/nonmatchings/692E8", func_801112AC);

INCLUDE_ASM("asm/us/dra/nonmatchings/692E8", func_8011151C);
