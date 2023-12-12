#include "dra.h"
#include "sfx.h"
#include "player.h"

void func_801092E8(s32 arg0) {
    D_800A37D8.D_800A37D8 = D_800ACE48[arg0 * 2];
    D_800A37D8.D_800A37DA = D_800ACE48[arg0 * 2 + 1];
    D_8006EBE0 = D_800ACE48[arg0 * 2];
}

void func_80109328(void) {
    s16* player_unk1E = &PLAYER.rotZ;

    g_Player.unk66 = 0;
    if (*player_unk1E == 0x800 && PLAYER.step == 8) {
        PLAYER.rotZ = 0;
        PLAYER.animCurFrame = 0x9D;
        PLAYER.facingLeft = (PLAYER.facingLeft + 1) & 1;
    }

    if (g_Player.D_80072F16 != 0) {
        g_Player.D_80072F16 = 0;
        func_801092E8(0);
    }
    PLAYER.blendMode = 0;
}

void func_801093C4(void) {
    DRAWENV sp10;
    Primitive* prim;
    s32 i;

    prim = &g_PrimBuf[g_Entities[1].primIndex];
    for (i = 0; i < 6; i++) {
        prim = prim->next;
    }
    switch (g_Player.unk6A) {
    case 0:
        if (func_800EDB08(prim) != 0) {
            prim->type = 7;
            prim->blendMode = BLEND_VISIBLE;
            prim = prim->next;
            func_800EDB08(prim);
            if (prim != NULL) {
                prim->type = 7;
                prim->blendMode = BLEND_VISIBLE;
                g_Player.unk6A++;
            }
        }
        break;
    case 1:
        if (g_Player.unk6A != 1) {
            return;
        }
        sp10 = g_CurrentBuffer->draw;
        sp10.isbg = 0;
        if (g_Player.unk0C & 0x04000000) {
            sp10.isbg = 1;
        }
        sp10.r0 = sp10.g0 = sp10.b0 = 0;
        sp10.ofs[0] = 0x200;
        sp10.clip = D_800ACE60;
        sp10.ofs[1] = 0x1C0;
        SetDrawEnv(*(s32*)&prim->r1, &sp10);
        prim->priority = 0x190;
        prim->blendMode = 0;
        prim = prim->next;
        prim->priority = 0x1B0;
        prim->blendMode = 0x800;
    }
}

// Duplicate of RIC func_80156F40
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
    PLAYER.facingLeft = 0;
    PLAYER.rotX = 0x100;
    PLAYER.rotY = 0x100;
    PLAYER.zPriority = (u16)g_unkGraphicsStruct.g_zEntityCenter.S16.unk0;

    memset_len = sizeof(PlayerState) / sizeof(s32);
    memset_ptr = &g_Player;
    for (i = 0; i < memset_len; i++) {
        *memset_ptr++ = 0;
    }

    for (i = 0; i < 0x10; i++) {
        g_ButtonCombo[i].buttonsCorrect = 0;
        g_ButtonCombo[i].timer = 0;
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
    func_801093C4();

#if defined(VERSION_US)
    g_Player.unk20[0] = 0x10;
    g_Player.D_80072EFC = 0x10;
    g_Player.D_80072EF4 = 0;
    D_80137FB8 = 0;
    D_80137FBC = 1;
#elif defined(VERSION_HD)
    D_80137FB8 = 0;
#endif

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
        CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(0x100, 121), 0);
        func_8010E42C(1);
    }
    if (D_80097C98 == 4) {
        CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(0x300, 121), 0);
        func_8010E42C(3);
    }
    if (D_80097C98 == 5) {
        CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(0x500, 121), 0);
        func_8010E42C(5);
    }

    g_CurrentEntity = g_Entities;
    weapon = D_8017A000.GetWeaponId;
    if (weapon() != 0x2D) {
        return;
    }
    if (CheckEquipmentItemCount(ITEM_AXE_LORD_ARMOR, ARMOR_TYPE) == 0) {
        return;
    }
    func_8010FAF4();

    weapon = D_8017A000.EntityWeaponAttack;
    weapon();
    g_Player.unk0C |= 0x01000000;
    func_8010DFF0(1, 10);
    func_80109328();
}

void func_80109990(void) {
    if (D_80137FB4 == 0) {
        if (g_Status.mp == g_Status.mpMax && !(g_Player.unk0C & 0x100000)) {
            CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(0, 40), 0);
            PlaySfx(NA_SE_PL_MP_GAUGE);
            D_80137FB4++;
        }
    } else if (g_Status.mp != g_Status.mpMax) {
        D_80137FB4 = 0;
    }
}

void func_80109A44(s32 arg0);
INCLUDE_ASM("dra/nonmatchings/692E8", func_80109A44);

void func_8010A234(s32 arg0) {
    s32 (*weapon)(void);

    g_CurrentEntity = &PLAYER;
    weapon = D_8017A000.GetWeaponId;
    // Wearing Axe Lord Armor! This is probably when you initially put it on.
    if ((weapon() == 0x2D) &&
        CheckEquipmentItemCount(ITEM_AXE_LORD_ARMOR, ARMOR_TYPE)) {
        if (!(g_Player.unk0C & 0x01000000)) {
            // Alucard says "WHAT?!" when first putting on Axe Lord Armor
            PlaySfx(NA_SE_VO_AL_WHAT);
            g_Player.D_80072EF4 = 0;
            g_Player.D_80072EFC = 0x20;
            func_8010FAF4();
            weapon = D_8017A000.EntityWeaponAttack;
            weapon();
            g_Player.unk0C |= 0x01000000;
            func_8010DFF0(1, 0xA);
            func_80109328();
            if (arg0 != 0) {
                func_8010DBFC(D_800B0130, D_800B01B8);
            }
        }
    } else if (g_Player.unk0C & 0x01000000) {
        PLAYER.palette = 0x8100;
        PLAYER.animSet = 1;
        PLAYER.unk5A = 0;
        PLAYER.rotZ = 0;
        PLAYER.drawFlags &= 0xF3;
        func_8010FAF4();
        PLAYER.rotPivotY = 0;
        PLAYER.rotPivotX = 0;
        if (g_Player.pl_vram_flag & 1) {
            func_8010E570(0);
        } else {
            func_8010E7AC();
        }
        g_Player.unk0C &= ~0x01000000;
        func_80111CC0();
        if (arg0 != 0) {
            func_8010DBFC(D_800B0130, D_800B01B8);
        }
    }
}

void func_8010A3F0(void) {
    s32 temp = 0x38;

    if (D_8017A000.GetWeaponId() == temp && D_8017D000.GetWeaponId() == temp) {
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

TeleportCheck GetTeleportToOtherCastle(void) {
    s32 xCheckTop;
    s32 yCheckTop;
    s32 xCheckRTop;
    s32 yCheckRTop;

    // Is player in the pose when pressing UP?
    if (PLAYER.step != 0 || PLAYER.step_s != 1) {
        return TELEPORT_CHECK_NONE;
    }

    // Check for X/Y boundaries in TOP
    if (g_StageId == STAGE_TOP) {
        xCheckTop = g_Tilemap.left * 256 + playerX - 8000;
        if (ABS(xCheckTop) < 4) {
            yCheckTop = g_Tilemap.top * 256 + playerY - 2127;
            if (ABS(yCheckTop) < 4) {
                return TELEPORT_CHECK_TO_RTOP;
            }
        }
    }

    // Check for X/Y boundaries in RTOP
    if (g_StageId == STAGE_RTOP) {
        xCheckRTop = g_Tilemap.left * 256 + playerX - 8384;
        if (ABS(xCheckRTop) < 4) {
#if defined(VERSION_US)
            yCheckRTop = g_Tilemap.top * 256 + playerY - 14407;
            if (ABS(yCheckRTop) < 4) {
                return TELEPORT_CHECK_TO_TOP;
            }
#elif defined(VERSION_HD)
            yCheckRTop = g_Tilemap.top * 256 + playerY;
            if (ABS(yCheckRTop) - 14407 < 4) {
                return TELEPORT_CHECK_TO_TOP;
            }
#endif
        }
    }

    return TELEPORT_CHECK_NONE;
}

INCLUDE_ASM("dra/nonmatchings/692E8", EntityAlucard);

void func_8010BF64(Unkstruct_8010BF64* arg0) {
    if (g_PlayableCharacter == PLAYER_ALUCARD) {
        u32 unk0C_var = (g_Player.unk0C / 2) & 2;
        arg0->unk14 = D_800ACED0.pairs[4].unk0 - unk0C_var;
        arg0->unk1C = D_800ACED0.pairs[4].unk2 + unk0C_var;
        arg0->unk18 = D_800ACED0.pairs[1].unk2 - 1;
        arg0->unk20 = D_800ACEC0[1].unk2 + 1;
    } else {
        D_8013C00C();
    }
}

void func_8010BFFC(void) {
    s16 x;
    s16 y;
    s32 i;
    bool collided = false;
    u16 original_Y = PLAYER.posY.i.hi;

    if ((g_Player.pl_vram_flag & 1) || (D_801396EA != 0) ||
#if defined(VERSION_US)
        (g_Player.unk0C & 0x40000007) ||
        ((g_PlayableCharacter != 0) && (PLAYER.step == 0x18)) ||
#elif defined(VERSION_HD)
        (g_Player.unk0C & PLAYER_STATUS_TRANSFORM) ||
#endif
        (g_Player.unk78 == 1)) {
        return;
    }
    if (PLAYER.posY.i.hi < 48) {
        PLAYER.posY.i.hi -= 16;
        while (true) {
            for (i = 0; i < 4; i++) {
                x = PLAYER.posX.i.hi + D_800ACED0.pairs[i].unk0;
                y = PLAYER.posY.i.hi + D_800ACED0.pairs[i].unk2;
                CheckCollision(x, y, &g_Player.colliders[i], 0);
            }
            if ((g_Player.colliders[1].effects &
                 (EFFECT_SOLID_FROM_BELOW + EFFECT_SOLID)) == EFFECT_SOLID ||
                (g_Player.colliders[2].effects &
                 (EFFECT_SOLID_FROM_BELOW + EFFECT_SOLID)) == EFFECT_SOLID ||
                (g_Player.colliders[3].effects &
                 (EFFECT_SOLID_FROM_BELOW + EFFECT_SOLID)) == EFFECT_SOLID) {
                // I don't know man
                (*(&PLAYER)).posY.i.hi--;
                PLAYER.velocityY = 0;
                collided = true;
                continue;
            }
            if (collided) {
                return;
            }
            PLAYER.posY.i.hi += 8;
            if (PLAYER.posY.i.hi >= 48) {
                PLAYER.posY.i.hi = original_Y;
                return;
            }
        }
    } else if (PLAYER.posY.i.hi > 176) {
        PLAYER.posY.i.hi += 32;
        while (true) {
            for (i = 0; i < 4; i++) {
                x = PLAYER.posX.i.hi + D_800ACEC0[i].unk0;
                y = PLAYER.posY.i.hi + D_800ACEC0[i].unk2;
#if defined(VERSION_US)
                if (g_PlayableCharacter != PLAYER_ALUCARD) {
                    y += 6;
                }
#endif
                CheckCollision(x, y, &g_Player.colliders[4 + i], 0);
            }
            if ((g_Player.colliders[5].effects &
                 (EFFECT_SOLID_FROM_ABOVE + EFFECT_SOLID)) == EFFECT_SOLID ||
                (g_Player.colliders[6].effects &
                 (EFFECT_SOLID_FROM_ABOVE + EFFECT_SOLID)) == EFFECT_SOLID ||
                (g_Player.colliders[7].effects &
                 (EFFECT_SOLID_FROM_ABOVE + EFFECT_SOLID)) == EFFECT_SOLID) {
                // I don't know man
                (*(&PLAYER)).posY.i.hi++;
                PLAYER.velocityY = 0;
                collided = true;
                continue;
            }
            if (collided) {
                PLAYER.posY.i.hi--;
                return;
            }
            PLAYER.posY.i.hi -= 8;
            if (PLAYER.posY.i.hi <= 176) {
                PLAYER.posY.i.hi = original_Y;
                return;
            }
        }
    }
}

INCLUDE_ASM("dra/nonmatchings/692E8", func_8010C36C);

INCLUDE_ASM("dra/nonmatchings/692E8", func_8010C9F4);

INCLUDE_ASM("dra/nonmatchings/692E8", func_8010D010);

INCLUDE_ASM("dra/nonmatchings/692E8", func_8010D2C8);

void SetPlayerStep(PlayerSteps step) {
    PLAYER.step = step;
    PLAYER.step_s = 0;
}
