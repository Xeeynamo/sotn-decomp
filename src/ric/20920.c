#include "ric.h"

void func_8015C920(AnimationFrame* unk0) {
    g_CurrentEntity->unk4C = unk0;
    g_CurrentEntity->animFrameDuration = 0;
    g_CurrentEntity->animFrameIdx = 0;
}

void func_8015C93C(s32 speed) {
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

void func_8015C984(s32 speed) {
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

s32 func_8015C9CC(void) {
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

void func_8015CA84(s32 speed) {
    if (g_CurrentEntity->facing == 1)
        speed = -speed;
    g_CurrentEntity->accelerationX = speed;
}

void func_8015CAAC(s32 speed) {
    if (PLAYER.objectRoomIndex == 1)
        speed = -speed;
    PLAYER.accelerationX = speed;
}

void func_8015CAD4(s32 arg0, s16 arg1) {
    if (arg0 == 0) {
        func_801606BC(g_CurrentEntity, 0x15002C, 0);
        if (arg1 >= g_Player.D_80072F1A) {
            g_Player.D_80072F1A = arg1;
        }
    } else if (g_Player.D_80072F1C <= arg1) {
        g_Player.D_80072F1C = arg1;
    }
}

void func_8015CB58(s32 arg0, s32 arg1) {
    POLY_GT4* poly;

    FntPrint("op disable\n");
    if (arg0 != 0) {
        g_Entities[UNK_ENTITY_1].ext.generic.unk7C.S8.unk1 = 1;
        g_Entities[UNK_ENTITY_3].animCurFrame = 0;
        g_Entities[UNK_ENTITY_2].animCurFrame = 0;
        g_Entities[UNK_ENTITY_1].animCurFrame = 0;

        poly = &g_PrimBuf[g_Entities[UNK_ENTITY_1].firstPolygonIndex];
        while (poly != NULL) {
            poly->x1 = 0;
            poly = (POLY_GT4*)poly->tag;
        }
    }
    g_Entities[UNK_ENTITY_1].ext.generic.unk7C.S8.unk0 = 1;
    g_Entities[UNK_ENTITY_1].ext.generic.unk7E.modeU8.unk0 = 0xA;
    if (arg1 != 0) {
        g_Player.D_80072F1E = 4;
    }
}

void func_8015CC28(void) {
    Entity* entity = &g_Entities[UNK_ENTITY_1];

    entity->ext.generic.unk7E.modeU8.unk1 = 0;
    entity->ext.generic.unk7E.modeU8.unk0 = 0;
    entity->ext.generic.unk7C.U8.unk1 = 0;
    entity->ext.generic.unk7C.U8.unk0 = 0;
}

void func_8015CC50() { SetPlayerStep(0xF0); }

void func_8015CC70(s16 arg0) {
    PLAYER.step_s = arg0;
    PLAYER.step = 0x0020;
    PLAYER.animFrameDuration = 0;
    PLAYER.animFrameIdx = 0;
    if (arg0 & 1) {
        PLAYER.unk4C = &D_80155950;
    } else {
        PLAYER.unk4C = &D_8015591C;
    }
}

void func_8015CCC8(s32 arg0, s32 accelerationX) {
    SetPlayerStep(2);
    func_8015C920(&D_801554C0);
    PLAYER.accelerationX = accelerationX;
    PLAYER.accelerationY = 0;
    if (arg0 == 1) {
        PLAYER.unk4C = &D_801554B0;
        PLAYER.step_s = 4;
    }
    if (arg0 == 2) {
        PLAYER.unk4C = &D_801554D0;
        PLAYER.step_s = 1;
    }
    if (arg0 == 3) {
        PLAYER.unk4C = &D_801554C8;
        PLAYER.step_s = 4;
    }
}

void func_8015CD98(s32 accelerationX) {
    PLAYER.accelerationX = accelerationX;
    PLAYER.accelerationY = 0;
    g_Player.unk44 = 0;
    SetPlayerStep(0);
    func_8015C920(&D_801553BC);
}

void func_8015CDE0(s32 arg0) {
    if ((g_Player.D_80072F10 != 0) && (g_Player.unk7A == 0)) {
        func_8015CE7C();
        return;
    } else {
        g_Player.D_80072F02 = 8;
    }
    g_Player.D_80072F10 = 0xC;
    g_Player.D_80072F02 = 0xC;
    g_Player.unk44 = 0;
    SetPlayerStep(1);
    func_8015C920(&D_80155488);
    func_8015CA84(0x14000);
    PLAYER.accelerationY = 0;
}

void func_8015CE7C(void) {
    if (g_Player.unk7A != 0) {
        func_8015CDE0(0);
    } else {
        g_Player.unk44 = 0;
        SetPlayerStep(0x19);
        func_8015C920(&D_80155670);
        func_8015CA84(0x24000);
        g_Player.D_80072F16 = 0x28;
        PLAYER.accelerationY = 0;
        func_801606BC(g_CurrentEntity, 0x50001, 0);
    }
}

void func_8015CF08(void) {
    /**
     * TODO: labels are !FAKE
     */
    if ((g_Player.unk50 != 0x19) && (g_Player.unk50 != 0x17)) {
        PLAYER.accelerationX = 0;
    }
    if (g_Player.unk50 != 1) {
        if (g_Player.unk50 != 0x19) {
            func_8015C920(&D_80155534);
            goto block_6;
        }
        goto block_7;
    }
block_6:
    if (g_Player.unk50 == 0x19) {
    block_7:
        g_Player.unk44 = 0x10;
    }
    SetPlayerStep(3);
    PLAYER.accelerationY = 0x20000;
    g_Player.D_80072F0A = 8;
    g_Player.D_80072F0C = 8;
    g_Player.D_80072F02 = 0;
    g_Player.D_80072F10 = 0;
    if (g_Player.unk50 == 0x17) {
        g_Player.D_80072F0C = 0;
        g_Player.D_80072F0A = 0;
        PLAYER.animFrameIdx = 2;
        PLAYER.animFrameDuration = 0x10;
        PLAYER.accelerationX /= 2;
    }
}

void func_8015D020(void) {
    u16 temp; // TODO: !FAKE

    if (g_Player.unk72 != 0) {
        func_8015CF08();
        return;
    }

    if ((func_8015C9CC() != 0) || (PLAYER.step == 0x17)) {
        func_8015C920(&D_8015550C);
        if (PLAYER.step == 0x19) {
            func_8015CA84(0x24000);
            temp = 0x10;
            goto block_8;
        }
        func_8015CA84(0x14000);
        g_Player.unk44 = 0;
    } else {
        func_8015C920(&D_801554F0);
        temp = 4;
        PLAYER.accelerationX = 0;
    block_8:
        g_Player.unk44 = temp;
    }

    SetPlayerStep(4);

    if (D_80154570 != 0) {
        PLAYER.accelerationY = -0x4B000;
    } else {
        PLAYER.accelerationY = -0x57000;
    }
}

void func_8015D120(void) {
    SetPlayerStep(8);
    PLAYER.accelerationX = 0;
    func_8015CA84(0x14000);
    PLAYER.accelerationY = -0x78000;
    g_Player.pl_high_jump_timer = 0;
    func_8015C920(&D_8015579C);
    func_8015CC28();
    func_801606BC(g_CurrentEntity, 0x2DU, 0);
    g_api.PlaySfx(0x6FB);
    g_Player.D_80072F18 = 4;
    if (g_Player.unk72 != 0) {
        PLAYER.accelerationY = 0;
    }
}

INCLUDE_ASM("asm/us/ric/nonmatchings/20920", func_8015D1D0);

// decompiling func_8015FB84 first is recommended to discover struct
INCLUDE_ASM("asm/us/ric/nonmatchings/20920", func_8015D250);

INCLUDE_ASM("asm/us/ric/nonmatchings/20920", func_8015D3CC);

INCLUDE_ASM("asm/us/ric/nonmatchings/20920", func_8015D678);

void func_8015D9B4() { SetPlayerStep(22); }

void func_8015D9D4(void) {
    func_8015C9CC();
    SetPlayerStep(0x17);
    func_8015C920(&D_80155750);
    g_CurrentEntity->accelerationY = 0;
    func_8015CA84(0x58000);
    func_8015CC28();
    func_801606BC(g_CurrentEntity, 0x19, 0);
    g_api.PlaySfx(0x707);
    g_Player.D_80072F18 = 4;
}

void func_8015DA60(void) {
    g_Player.unk44 = 0;
    SetPlayerStep(0x1A);
    func_8015C920(&D_8015577C);
    g_CurrentEntity->accelerationY = -0x20000;
    func_8015CA84(0x58000);
    func_8015CC28();
    func_801606BC(g_CurrentEntity, 0x19, 0);
    g_api.PlaySfx(0x6FA);
    g_Player.D_80072F18 = 4;
    func_801606BC(g_CurrentEntity, 0x1F, 0);
}

void func_8015DB04(void) {
    SetPlayerStep(0x18);
    func_8015C920(&D_801557D8);
    g_CurrentEntity->accelerationY = 0;
    func_8015CA84(0x58000);
    g_Player.unk46 = 5;
    g_Player.D_80072F18 = 4;
    func_801606BC(g_CurrentEntity, 0x1A, 0);
    func_8015CC28();
    g_api.PlaySfx(0x6FB);
    g_api.PlaySfx(0x707);
}

INCLUDE_ASM("asm/us/ric/nonmatchings/20920", func_8015DBB0);
