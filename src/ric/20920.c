#include "ric.h"

void func_8015C920(AnimationFrame* unk0) {
    g_CurrentEntity->unk4C = unk0;
    g_CurrentEntity->animFrameDuration = 0;
    g_CurrentEntity->animFrameIdx = 0;
}

void func_8015C93C(s32 speed) {
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

void func_8015C984(s32 speed) {
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

s32 func_8015C9CC(void) {
    if (g_Player.unk44 & 2) {
        return 0;
    }

    if (PLAYER.facingLeft == 1) {
        if (g_Player.padPressed & PAD_RIGHT) {
            PLAYER.facingLeft = 0;
            g_Player.unk4C = 1;
            return -1;
        } else if (g_Player.padPressed & PAD_LEFT) {
            return 1;
        }
    } else {
        if (g_Player.padPressed & PAD_RIGHT) {
            return 1;
        }
        if (g_Player.padPressed & PAD_LEFT) {
            PLAYER.facingLeft = 1;
            g_Player.unk4C = 1;
            return -1;
        }
    }
    return 0;
}

void SetSpeedX(s32 speed) {
    if (g_CurrentEntity->facingLeft == 1)
        speed = -speed;
    g_CurrentEntity->velocityX = speed;
}

void func_8015CAAC(s32 speed) {
    if (PLAYER.entityRoomIndex == 1)
        speed = -speed;
    PLAYER.velocityX = speed;
}

void func_8015CAD4(s32 arg0, s16 arg1) {
    if (arg0 == 0) {
        CreateEntFactoryFromEntity(g_CurrentEntity, 0x15002C, 0);
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

        poly = &g_PrimBuf[g_Entities[UNK_ENTITY_1].primIndex];
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

void func_8015CCC8(s32 arg0, s32 velocityX) {
    SetPlayerStep(2);
    func_8015C920(&D_801554C0);
    PLAYER.velocityX = velocityX;
    PLAYER.velocityY = 0;
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

void func_8015CD98(s32 velocityX) {
    PLAYER.velocityX = velocityX;
    PLAYER.velocityY = 0;
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
    SetSpeedX(0x14000);
    PLAYER.velocityY = 0;
}

void func_8015CE7C(void) {
    if (g_Player.unk7A != 0) {
        func_8015CDE0(0);
    } else {
        g_Player.unk44 = 0;
        SetPlayerStep(0x19);
        func_8015C920(&D_80155670);
        SetSpeedX(0x24000);
        g_Player.D_80072F16 = 0x28;
        PLAYER.velocityY = 0;
        CreateEntFactoryFromEntity(g_CurrentEntity, 0x50001, 0);
    }
}

void func_8015CF08(void) {
    /**
     * TODO: labels are !FAKE
     */
    if ((g_Player.unk50 != 0x19) && (g_Player.unk50 != 0x17)) {
        PLAYER.velocityX = 0;
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
    PLAYER.velocityY = 0x20000;
    g_Player.D_80072F0A = 8;
    g_Player.D_80072F0C = 8;
    g_Player.D_80072F02 = 0;
    g_Player.D_80072F10 = 0;
    if (g_Player.unk50 == 0x17) {
        g_Player.D_80072F0C = 0;
        g_Player.D_80072F0A = 0;
        PLAYER.animFrameIdx = 2;
        PLAYER.animFrameDuration = 0x10;
        PLAYER.velocityX /= 2;
    }
}

void func_8015D020(void) {
    if (g_Player.unk72 != 0) {
        func_8015CF08();
        return;
    }
    if (func_8015C9CC() != 0 || PLAYER.step == Player_Slide) {
        func_8015C920(&D_8015550C);
        if (PLAYER.step == Player_Unk25) {
            SetSpeedX(FIX(2.25));
            g_Player.unk44 = 0x10;
        } else {
            SetSpeedX(FIX(1.25));
            g_Player.unk44 = 0;
        }
    } else {
        func_8015C920(&D_801554F0);
        PLAYER.velocityX = 0;
        g_Player.unk44 = 4;
    }
    SetPlayerStep(Player_Jump);
    if (D_80154570 != 0) {
        PLAYER.velocityY = -FIX(4.6875);
    } else {
        PLAYER.velocityY = -FIX(5.4375);
    }
}

void func_8015D120(void) {
    SetPlayerStep(8);
    PLAYER.velocityX = 0;
    SetSpeedX(0x14000);
    PLAYER.velocityY = -0x78000;
    g_Player.pl_high_jump_timer = 0;
    func_8015C920(&D_8015579C);
    func_8015CC28();
    CreateEntFactoryFromEntity(g_CurrentEntity, 0x2DU, 0);
    g_api.PlaySfx(0x6FB);
    g_Player.D_80072F18 = 4;
    if (g_Player.unk72 != 0) {
        PLAYER.velocityY = 0;
    }
}

s32 func_8015D1D0(s16 subWpnId, s16 subWpnUnk6) {
    Entity* entity;
    s32 b0MatchCount;
    s32 nullObjCount;
    s32 i;

    entity = &g_Entities[32];
    for (i = 0, b0MatchCount = 0, nullObjCount = 0; i < 0x10; i++, entity++) {
        if (entity->entityId == E_NONE) {
            nullObjCount++;
        }
        if (entity->ext.generic.unkB0 != 0 &&
            entity->ext.generic.unkB0 == subWpnId) {
            b0MatchCount++;
        }
        if (b0MatchCount >= subWpnUnk6) {
            return -1;
        }
    }
    if (nullObjCount == 0) {
        return -1;
    }
    return 0;
}
