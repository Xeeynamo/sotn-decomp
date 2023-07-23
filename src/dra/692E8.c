#include "dra.h"
#include "sfx.h"
#if defined(VERSION_US)

void func_801092E8(s32 arg0) {
    D_800A37D8.D_800A37D8 = D_800ACE48[arg0 * 2];
    D_800A37D8.D_800A37DA = D_800ACE48[arg0 * 2 + 1];
    D_8006EBE0 = D_800ACE48[arg0 * 2];
}

void func_80109328(void) {
    s16* player_unk1E = &PLAYER.rotAngle;

    g_Player.unk66 = 0;
    if (*player_unk1E == 0x800 && PLAYER.step == 8) {
        PLAYER.rotAngle = 0;
        PLAYER.animCurFrame = 0x9D;
        PLAYER.facing = (PLAYER.facing + 1) & 1;
    }

    if (g_Player.D_80072F16 != 0) {
        g_Player.D_80072F16 = 0;
        func_801092E8(0);
    }
    PLAYER.blendMode = 0;
}

void func_801093C4(Primitive*);
INCLUDE_ASM("asm/us/dra/nonmatchings/692E8", func_801093C4);

void func_80109594(void) {
    Entity* e;
    Primitive* prim;
    s32 radius;
    s32 intensity;
    s32 primIndex;
    s32 i;
    s32 val;
    s32 memset_len;
    s32* memset_ptr;
    s32 (*weapon)(void);

    g_Player.unk6A = 0;
    g_CurrentEntity = g_Entities;
    DestroyEntity(g_CurrentEntity);
    PLAYER.posX.val = 0x200000;
    PLAYER.posY.val = 0x200000;
    PLAYER.animSet = ANIMSET_DRA(1);
    PLAYER.palette = 0x8100;
    PLAYER.facing = 0;
    PLAYER.unk1A = 0x100;
    PLAYER.unk1C = 0x100;
    PLAYER.zPriority = (u16)g_zEntityCenter.S16.unk0;

    memset_len = sizeof(PlayerState) / sizeof(s32);
    memset_ptr = &g_Player;
    for (i = 0; i < memset_len; i++) {
        *memset_ptr++ = 0;
    }

    for (i = 0; i < 0x10; i++) {
        D_80138FC0[i].x = 0;
        D_80138FC0[i].y = 0;
    }

    g_Player.unk04 = 1;
    g_Player.pl_vram_flag = 1;
    func_8010E570(0);

    for (e = &g_Entities[1], i = 0; i < 3; i++, e++) {
        DestroyEntity(e);
        e->animSet = ANIMSET_DRA(1);
        e->unk5A = i + 1;
        e->palette = 0x8100;
        e->flags = FLAG_UNK_20000 | FLAG_UNK_08000000;
    }

    primIndex = AllocPrimitives(PRIM_TILE, 8);
    prim = &g_PrimBuf[primIndex];
    g_Entities[1].primIndex = primIndex;
    g_Entities[1].flags |= 0x800000;
    for (i = 0; i < 6; i++) {
        prim->blendMode = 0x10A;
        prim = prim->next;
    }
    func_801093C4(prim);
    g_Player.unk20[0] = 0x10;
    g_Player.D_80072EFC = 0x10;
    g_Player.D_80072EF4 = 0;
    D_80137FB8 = 0;
    D_80137FBC = 1;
    if (g_Status.mp != g_Status.mpMax) {
        D_80137FB4 = 0;
    } else {
        D_80137FB4 = 1;
    }
    D_80097D37 = 0;
    func_800EA5E4(0x16);
    func_801092E8(0);
    for (i = 0; i < 0x20; i++) {
        radius = (rand() & 0x3FF) + 0x100;
        intensity = (rand() & 0xFF) + 0x100;
        val = rcos(radius) * 0x10;
        D_801396F8[i] = +((val * intensity) >> 8);
        val = rsin(radius) * 0x10;
        D_80139778[i] = -((val * intensity) >> 7);
    }
    func_80111928();
    if (D_80097C98 == 6) {
        func_8011AAFC(g_CurrentEntity, 0x10079, 0);
        func_8010E42C(1);
    }
    if (D_80097C98 == 4) {
        func_8011AAFC(g_CurrentEntity, 0x30079, 0);
        func_8010E42C(3);
    }
    if (D_80097C98 == 5) {
        func_8011AAFC(g_CurrentEntity, 0x50079, 0);
        func_8010E42C(5);
    }

    g_CurrentEntity = g_Entities;
    weapon = D_8017A000.func_8017A018;
    if (weapon() != 0x2D) {
        return;
    }
    if (CheckEquipmentItemCount(0x19, 2) == 0) {
        return;
    }
    func_8010FAF4();

    weapon = D_8017A000.func_8017A000;
    weapon();
    g_Player.unk0C |= 0x01000000;
    func_8010DFF0(1, 10);
    func_80109328();
}

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

void func_80109A44(s32 arg0);
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
            g_Entities[PLAYER_CHARACTER].animSet = ANIMSET_DRA(1);
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

s32 func_8010A4A4(void);
INCLUDE_ASM("asm/us/dra/nonmatchings/692E8", func_8010A4A4);

INCLUDE_ASM("asm/us/dra/nonmatchings/692E8", EntityAlucard);

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

u32 UpdateUnarmedAnim(s8* frameProps, u16** frames) {
    u16* frameIndex;

    frameIndex =
        frames[g_CurrentEntity->ext.generic.unkAC] + PLAYER.animFrameIdx;
    if (*frameIndex == 0xFFFF) {
        return -1;
    }
    if (frameProps != NULL) {
        frameProps = &frameProps[(*frameIndex >> 9) << 2];
        g_CurrentEntity->hitboxOffX = *frameProps++;
        g_CurrentEntity->hitboxOffY = *frameProps++;
        g_CurrentEntity->hitboxWidth = *frameProps++;
        g_CurrentEntity->hitboxHeight = *frameProps++;
    }
    g_CurrentEntity->animCurFrame = *frameIndex & 0x1FF;
    return PLAYER.animFrameDuration >= 0 ? 0 : -1;
}
INCLUDE_ASM("asm/us/dra/nonmatchings/692E8", func_8010DBFC);

u32 UpdateAnim(s8* frameProps, s32* frames) {
    AnimationFrame* animFrame;
    s32 ret;

    if (g_CurrentEntity->animFrameDuration == -1) {
        ret = -1;
    } else if (g_CurrentEntity->animFrameDuration == 0) {
        g_CurrentEntity->animFrameDuration =
            g_CurrentEntity->unk4C[g_CurrentEntity->animFrameIdx].duration;
        ret = 0;
    } else if ((--g_CurrentEntity->animFrameDuration) == 0) {
        g_CurrentEntity->animFrameIdx++;
        animFrame = &g_CurrentEntity->unk4C[g_CurrentEntity->animFrameIdx];
        // Effectively a switch statement, but breaks if I actually use one.
        if (animFrame->duration == 0) {
            g_CurrentEntity->animFrameIdx = animFrame->unk2;
            g_CurrentEntity->animFrameDuration =
                g_CurrentEntity->unk4C[g_CurrentEntity->animFrameIdx].duration;
            ret = 0;
        } else if (animFrame->duration == 0xFFFF) {
            g_CurrentEntity->animFrameIdx--;
            g_CurrentEntity->animFrameDuration = -1;
            ret = -1;
        } else if (animFrame->duration == 0xFFFE) {
            g_CurrentEntity->unk4C = frames[animFrame->unk2];
            g_CurrentEntity->animFrameIdx = 0;
            ret = -2;
            g_CurrentEntity->animFrameDuration =
                g_CurrentEntity->unk4C->duration;
        } else {
            g_CurrentEntity->animFrameDuration = animFrame->duration;
        }
    }
    if (frameProps != NULL) {
        // This is ugly - theoretically the type for frameProps should be
        // FrameProperty* but anything besides this where we assign this big
        // expression fails.
        frameProps =
            &frameProps[(g_CurrentEntity->unk4C[g_CurrentEntity->animFrameIdx]
                             .unk2 >>
                         9)
                        << 2];
        g_CurrentEntity->hitboxOffX = *frameProps++;
        g_CurrentEntity->hitboxOffY = *frameProps++;
        g_CurrentEntity->hitboxWidth = *frameProps++;
        g_CurrentEntity->hitboxHeight = *frameProps++;
    }
    g_CurrentEntity->animCurFrame =
        g_CurrentEntity->unk4C[g_CurrentEntity->animFrameIdx].unk2 & 0x1FF;
    return ret;
}

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
        poly = &g_PrimBuf[g_Entities[UNK_ENTITY_1].primIndex];

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
    if (g_CurrentEntity->velocityX < 0) {
        g_CurrentEntity->velocityX += speed;
        if (g_CurrentEntity->velocityX > 0) {
            g_CurrentEntity->velocityX = 0;
        }
    } else {
        g_CurrentEntity->velocityX -= speed;
        if (g_CurrentEntity->velocityX < 0)
            g_CurrentEntity->velocityX = 0;
    }
}

void func_8010E234(s32 speed) {
    if (g_CurrentEntity->velocityY < 0) {
        g_CurrentEntity->velocityY += speed;
        if (g_CurrentEntity->velocityY > 0) {
            g_CurrentEntity->velocityY = 0;
        }
    } else {
        g_CurrentEntity->velocityY -= speed;
        if (g_CurrentEntity->velocityY < 0) {
            g_CurrentEntity->velocityY = 0;
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
        if (g_Player.padPressed & PAD_RIGHT) {
            *facing = 0;
            g_Player.unk4C = 1;
            return -1;
        } else if (g_Player.padPressed & PAD_LEFT) {
            return 1;
        }
    } else {
        if (!(g_Player.padPressed & PAD_RIGHT)) {
            if (g_Player.padPressed & PAD_LEFT) {
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

s32 func_8010E334(s32 xStart, s32 xEnd) {
    Entity* e = &PLAYER;

    g_Player.unk7A = 1;
    if (e->step == 0 && PLAYER.step_s == 1 && e->posX.i.hi >= xStart &&
        e->posX.i.hi <= xEnd) {
        return 1;
    }
    return 0;
}

// Sets velocity based on an input speed, and the existing facing value
void SetSpeedX(s32 speed) {
    if (g_CurrentEntity->facing == 1) {
        speed = -speed;
    }
    g_CurrentEntity->velocityX = speed;
}

// Updates the Player velocity in the X Axis
void func_8010E3B8(s32 velocityX) {
    if (PLAYER.entityRoomIndex == 1) {
        velocityX = -velocityX;
    }
    PLAYER.velocityX = velocityX;
}

void func_8010E3E0(void) {
    if (g_Player.unk48 != 0) {
        DestroyEntity(&g_Entities[16]);
        g_Player.unk48 = 0;
    }
}

void func_8010E42C(u16 arg0) {
    PLAYER.step_s = arg0;
    PLAYER.step = Player_Unk18;

    if (!(arg0 & 1)) {
        func_8010DA48(0xF4);
    } else {
        func_8010DA48(0xF5);
    }
}

void func_8010E470(s32 arg0, s32 arg1) {
    PLAYER.velocityX = arg1;
    PLAYER.velocityY = 0;
    PLAYER.step = Player_Crouch;
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
        PLAYER.velocityY = 0;
        PLAYER.velocityX = 0;
        SetPlayerStep(Player_Unk_6);
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
    SetSpeedX(0x18000);
    PLAYER.velocityY = 0;
    SetPlayerStep(Player_Walk);

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
    SetPlayerStep(Player_Unk3);

    if (g_Player.unk50 != 1) {
        func_8010DA48(0x1C);
    }

    PLAYER.velocityY = 0x20000;
    PLAYER.velocityX = 0;
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
        SetSpeedX(0x18000);
        g_Player.unk44 = 0;
    } else {
        func_8010DA48(0x16);
        PLAYER.velocityX = 0;
        g_Player.unk44 = 4;
    }

    PLAYER.velocityY = 0xFFFB0000 | 0x2000;
    SetPlayerStep(Player_Jump);

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
    PLAYER.velocityY = -0x44000;
    if (g_Player.unk72 != 0) {
        PLAYER.velocityY = 0;
    }
}

void func_8010E9A4(void) {
    if (func_8010E27C() != 0) {
        SetSpeedX(0x30000);
    } else {
        PLAYER.velocityX = 0;
    }

    if (PLAYER.step == 4) {
        g_Player.unk44 |= 1;
    } else {
        g_Player.unk44 = 0;
    }

    func_8011AAFC(g_CurrentEntity, 2, 0);
    SetPlayerStep(Player_Unk8);
    PLAYER.velocityY = -0xC0000;
    func_8010DA48(0x21);
    g_Player.unk4A = 0;
}

void func_8010EA54(s32 arg0) {
    s16 temp_hi;

    if (arg0 != 0) {
        temp_hi = rand() % arg0;
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
        if (entity->entityId == E_NONE) {
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

extern s32 D_80097400;

s32 func_8010EB5C(void) {
    SubweaponDef subWpn;
    s16 subWpnId;
    s32 var_s0;
    s32 faker;

    var_s0 = 0;
    if (!(g_Player.padPressed & PAD_UP)) {
        return 1;
    }
    if (g_Player.pl_vram_flag & 0x20) {
        var_s0 = 1;
    }
    subWpnId = func_800FE3C4(&subWpn, 0, false);

    if (subWpnId == 0) {
        return 1;
    }
    if (subWpnId == 6 && D_80097400 != 0) {
        return 4;
    }
    if (func_8010EADC(subWpnId, subWpn.unk6) < 0) {
        return 2;
    }
    subWpnId = func_800FE3C4(&subWpn, 0, true);
    if (subWpnId == 0) {
        return 3;
    }
    func_8011AAFC(g_CurrentEntity, (u32)subWpn.unkB, subWpnId << 9);
    g_Player.D_80072F14 = 4;
    if (PLAYER.step_s < 64) {
        faker = subWpn.unkA;
        if (PLAYER.step == 0) {
            func_8010DA48(faker + var_s0);
        }
        func_8010EA54(8);
    }
    return 0;
}

s32 CheckChainLimit(s32 itemId, s32 handId) {
    Entity* entity;
    s32 existing_count;
    s32 i;
    s32 chainLimit;

    chainLimit = D_800A4B04[itemId].chainLimit;
    if (chainLimit & 0x80) {
        return -(s32)((u16)g_Player.unk46 >> 0xF);
    }
    entity = &g_Entities[16];
    for (i = 16, existing_count = 0; i < 64; i++, entity++) {
        // Hack to load unkAE as an s16 (struct has s8)
        // Longer term, figure out what g_Entites[16-64] are
        // and make dedicated ent extension.
        if (LOH(entity->ext.generic.unkAE) != itemId) {
            continue;
        }

        if (handId != 0) {
            if (entity->params & 0x8000) {
                existing_count++;
            }
        } else {
            if (!(entity->params & 0x8000)) {
                existing_count++;
            }
        }

        if (!(existing_count < chainLimit)) {
            return -1;
        }
    }
    return 0;
}

void func_8010ED54(u8 arg0) {
    PLAYER.velocityY = 0;
    PLAYER.velocityX = 0;
    SetPlayerStep(Player_Unk15);
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
    PLAYER.velocityY = 0;
    PLAYER.velocityX = 0;
    SetPlayerStep(Player_SpellHellfire);
    func_8010E168(1, 0x10);
    func_8010E3E0();
}

void func_8010FB68(void) { // Related to Dark Methamorphosis
    PLAYER.velocityY = 0;
    PLAYER.velocityX = 0;
    SetPlayerStep(Player_SpellDarkMetamorphosis);
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
    PLAYER.velocityY = 0;
    PLAYER.velocityX = 0;
    SetPlayerStep(Player_SpellSoulSteal);
    func_8010E3E0();
    func_8010DA48(0xDA);
    PlaySfx(NA_SE_VO_AL_SOUL_STEAL);
    func_80118C28(0xC);
    g_Player.D_80072F18 = 4;
}

void func_8010FC50(void) {
    PLAYER.velocityY = 0;
    PLAYER.velocityX = 0;
    SetPlayerStep(Player_SpellSummonSpirit);
    func_8010E3E0();
    func_8011AAFC(g_CurrentEntity, 0x75, 0);
    func_8010DA48(0xF0);
    PlaySfx(NA_SE_VO_AL_PUNCH);
    g_Player.D_80072F18 = 4;
}

void func_8010FCB8(void) {
    PLAYER.velocityY = 0;
    PLAYER.velocityX = 0;
    SetPlayerStep(Player_SpellTetraSpirit);
    func_8010E3E0();
    func_8011AAFC(g_CurrentEntity, 0x10075, 0);
    func_8010DA48(0xF1);
    PlaySfx(NA_SE_VO_AL_PUNCH);
    g_Player.D_80072F18 = 4;
}

void func_8010FD24(void) {
    PLAYER.velocityY = 0;
    PLAYER.velocityX = 0;
    SetPlayerStep(Player_Unk39);
    func_8010E3E0();
    func_8010DA48(0xF1);
    func_8011AAFC(g_CurrentEntity, 0x170028, 0);
    g_Player.D_80072F18 = 4;
}

void func_8010FD88(void) {
    PLAYER.step = Player_Stand;
    PLAYER.step_s = 3;
    SetSpeedX(0xFFFC8000);
    g_CurrentEntity->velocityY = 0;
    func_8010DA48(0xDB);
    func_8011AAFC(g_CurrentEntity, 0, 0);
    g_Player.unk46 = 0;
    PlaySfx(NA_SE_AL_BACKSLIDE);
}

bool func_8010FDF8(s32 branchFlags) {
    u8 stackpad[0x28];
    s32 tempYAccel;
    s32 tempTriangle;
    s32 YAccel;

    if (branchFlags & 8 && g_Player.unk46 == 0) {
        func_8010E27C();
    }
    YAccel = -((branchFlags & 0x8000) != 0) & 0x2C00;
    if (branchFlags & 0x10000) {
        if (-0x2000 < PLAYER.velocityY && PLAYER.velocityY < 0x6000 &&
            !(g_Player.unk44 & 0x20) && g_Player.padPressed & PAD_CROSS) {
            YAccel = 0x08CC;
        } else {
            YAccel = 0x2C00;
        }
    }

    if (branchFlags & 0x200) {
        if (-0x2000 < PLAYER.velocityY && PLAYER.velocityY < 0x6000) {
            YAccel = 0x1600;
        } else {
            YAccel = 0x2C00;
        }
    }

    if (D_80097448 >= 0x29) {
        if (YAccel < 0) {
            tempYAccel = YAccel + 3;
        } else {
            tempYAccel = YAccel;
        }
        YAccel = (tempYAccel) >> 2;
    }

    PLAYER.velocityY += YAccel;

    if (PLAYER.velocityY > 0x70000) {
        PLAYER.velocityY = 0x70000;
    }
    if ((branchFlags & 0x80) && (g_Player.pl_vram_flag & 2) &&
        (PLAYER.velocityY < -0x10000)) {
        PLAYER.velocityY = -0x10000;
    }

    if (PLAYER.velocityY >= 0) {
        if (branchFlags & 1 && g_Player.pl_vram_flag & 1) {
            if (g_Player.unk46 != 0) {
                if ((g_Player.unk46 & 0x7FFF) == 0xFF) {
                    func_8010E570(0);
                    func_8010FAF4();
                label:
                    PlaySfx(0x64C, 0x30, 0);
                    return 1;
                }

                if (PLAYER.velocityY > 0x6E000) {
                    func_8010E470(1, 0);
                    func_80134714(0x647);
                    func_8011AAFC(g_CurrentEntity, 0, 0);
                } else {
                    if (g_Player.unk44 & 0x10) {
                        func_8010E6AC(1);
                    } else {
                        func_8010E570(0);
                    }
                    PlaySfx(0x64C, 0x30, 0);
                }

                func_8010FAF4();
                return 1;
            }

            if (PLAYER.velocityY > 0x6E000) {
                if ((PLAYER.step_s == 112) || (PLAYER.step == 4)) {
                    func_8010E470(3, PLAYER.velocityX / 2);
                } else {
                    func_8010E470(1, 0);
                }
                PlaySfx(0x647);
                func_8011AAFC(g_CurrentEntity, 0, 0);
                return 1;
            }

            if (g_Player.unk44 & 0x10) {
                func_8010E6AC(1);
                goto label;
            }

            if (ABS(PLAYER.velocityX) > 0x20000) {
                PlaySfx(0x647);
                func_8011AAFC(g_CurrentEntity, 0, 0);
                func_8010E570(PLAYER.velocityX);
            } else {
                PlaySfx(0x64C, 0x30, 0);
                func_8010E570(0);
            }
            return 1;
        }
        if (branchFlags & 0x20000 && g_Player.pl_vram_flag & 1) {
            func_8010E470(3, PLAYER.velocityX);
            PlaySfx(0x647);
            func_8011AAFC(g_CurrentEntity, 0, 0);
            return 1;
        }
    }
    if (branchFlags & 4 && !(g_Player.pl_vram_flag & 1)) {
        func_8010E7AC();
        return 1;
    }

    if (branchFlags & 0x1000 &&
        g_Player.padPressed & (PAD_SQUARE | PAD_CIRCLE) &&
        func_8010EDB8() != 0) {
        return 1;
    }

    if (g_Player.unk46 & 0x8000) {
        return 0;
    }

    if (branchFlags & 0x10 && g_Player.padTapped & PAD_CROSS) {
        func_8010E83C(1);
        return 1;
    }

    if (branchFlags & 0x20 && func_800FE3A8(0xD) &&
        g_Player.padTapped & PAD_CROSS && !(g_Player.unk44 & 1)) {
        func_8010E940();
        return 1;
    }

    if (branchFlags & 0x2000 && g_Player.padPressed & PAD_DOWN) {
        func_8010E470(2, 0);
        return 1;
    }

    if (branchFlags & 0x40000 && PLAYER.ext.generic.unkAC != 0xDB) {
        if (g_Player.unk46 & 0x7FFF) {
            tempTriangle = g_Player.padPressed & PAD_TRIANGLE;
        } else {
            tempTriangle = g_Player.padTapped & PAD_TRIANGLE;
        }
        if (tempTriangle != 0) {
            func_8010FD88();
            return 1;
        }
    }
    return 0;
}

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
#endif