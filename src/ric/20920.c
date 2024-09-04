#include "ric.h"

void RicSetAnimation(AnimationFrame* anim) {
    g_CurrentEntity->anim = anim;
    g_CurrentEntity->animFrameDuration = 0;
    g_CurrentEntity->animFrameIdx = 0;
}

void RicDecelerateX(s32 speed) {
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

static void DecelerateY(s32 speed) {
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

s32 RicCheckFacing(void) {
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

void RicSetSpeedX(s32 speed) {
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
        RicCreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(0x1500, 44), 0);
        if (arg1 >= g_Player.D_80072F00[PL_T_INVINCIBLE]) {
            g_Player.D_80072F00[PL_T_INVINCIBLE] = arg1;
        }
    } else if (g_Player.D_80072F00[PL_T_INVINCIBILITY_CONSUMABLE] <= arg1) {
        g_Player.D_80072F00[PL_T_INVINCIBILITY_CONSUMABLE] = arg1;
    }
}

void func_8015CB58(s32 arg0, s32 arg1) {
    Primitive* prim;

    FntPrint("op disable\n");
    if (arg0 != 0) {
        g_Entities[UNK_ENTITY_1].ext.generic.unk7C.S8.unk1 = 1;
        g_Entities[UNK_ENTITY_3].animCurFrame = 0;
        g_Entities[UNK_ENTITY_2].animCurFrame = 0;
        g_Entities[UNK_ENTITY_1].animCurFrame = 0;

        prim = &g_PrimBuf[g_Entities[UNK_ENTITY_1].primIndex];
        while (prim != NULL) {
            prim->x1 = 0;
            prim = prim->next;
        }
    }
    g_Entities[UNK_ENTITY_1].ext.generic.unk7C.S8.unk0 = 1;
    g_Entities[UNK_ENTITY_1].ext.generic.unk7E.modeU8.unk0 = 0xA;
    if (arg1 != 0) {
        g_Player.D_80072F00[PL_T_15] = 4;
    }
}

void func_8015CC28(void) {
    Entity* entity = &g_Entities[UNK_ENTITY_1];

REDACTED
REDACTED
REDACTED
REDACTED
}

void RicSetDebug() { RicSetStep(PL_S_DEBUG); }

void func_8015CC70(s16 arg0) {
REDACTED
    PLAYER.step = PL_S_INIT;
    PLAYER.animFrameDuration = 0;
    PLAYER.animFrameIdx = 0;
    if (arg0 & 1) {
        PLAYER.anim = D_80155950;
    } else {
        PLAYER.anim = D_8015591C;
    }
}

void RicSetCrouch(s32 kind, s32 velocityX) {
    RicSetStep(PL_S_CROUCH);
    RicSetAnimation(ric_anim_crouch);
    PLAYER.velocityX = velocityX;
    PLAYER.velocityY = 0;
    if (kind == 1) {
        PLAYER.anim = ric_anim_crouch_from_stand2;
REDACTED
    }
    if (kind == 2) {
        PLAYER.anim = ric_anim_crouch_from_stand;
REDACTED
    }
    if (kind == 3) {
        PLAYER.anim = ric_anim_land_from_air_run;
REDACTED
    }
}

// Corresponding DRA function is func_8010E570 (much more complex)
void RicSetStand(s32 velocityX) {
    PLAYER.velocityX = velocityX;
    PLAYER.velocityY = 0;
    g_Player.unk44 = 0;
    RicSetStep(PL_S_STAND);
    RicSetAnimation(ric_anim_stand);
}

void RicSetWalk(s32 arg0) {
    if ((g_Player.D_80072F00[PL_T_8] != 0) && (g_Player.unk7A == 0)) {
        RicSetRun();
        return;
    }
    g_Player.D_80072F00[PL_T_CURSE] = 8;
    g_Player.D_80072F00[PL_T_8] = 12;
    g_Player.D_80072F00[PL_T_CURSE] = 12;
    g_Player.unk44 = 0;
    RicSetStep(PL_S_WALK);
    RicSetAnimation(ric_anim_walk);
    RicSetSpeedX(FIX(1.25));
    PLAYER.velocityY = 0;
}

void RicSetRun(void) {
    if (g_Player.unk7A != 0) {
        RicSetWalk(0);
    } else {
        g_Player.unk44 = 0;
        RicSetStep(PL_S_RUN);
        RicSetAnimation(ric_anim_run);
        RicSetSpeedX(FIX(2.25));
        g_Player.D_80072F00[PL_T_RUN] = 40;
        PLAYER.velocityY = 0;
        RicCreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(0x500, 1), 0);
    }
}

void RicSetFall(void) {
REDACTED
REDACTED
REDACTED
    if (g_Player.prev_step != PL_S_RUN && g_Player.prev_step != PL_S_SLIDE) {
        PLAYER.velocityX = 0;
REDACTED
    if (g_Player.prev_step != PL_S_WALK) {
        if (g_Player.prev_step != PL_S_RUN) {
            RicSetAnimation(D_80155534);
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
    if (g_Player.prev_step == PL_S_RUN) {
REDACTED
        g_Player.unk44 = 0x10;
REDACTED
    RicSetStep(PL_S_FALL);
    PLAYER.velocityY = 0x20000;
    g_Player.D_80072F00[PL_T_5] = 8;
    g_Player.D_80072F00[PL_T_6] = 8;
    g_Player.D_80072F00[PL_T_CURSE] = 0;
    g_Player.D_80072F00[PL_T_8] = 0;
    if (g_Player.prev_step == PL_S_SLIDE) {
        g_Player.D_80072F00[PL_T_6] = 0;
        g_Player.D_80072F00[PL_T_5] = 0;
REDACTED
REDACTED
        PLAYER.velocityX /= 2;
REDACTED
REDACTED
REDACTED
void RicSetJump(void) {
    if (g_Player.unk72) {
        RicSetFall();
REDACTED
REDACTED
    if (RicCheckFacing() != 0 || PLAYER.step == Player_Slide) {
        RicSetAnimation(D_8015550C);
        if (PLAYER.step == PL_S_RUN) {
            RicSetSpeedX(FIX(2.25));
            g_Player.unk44 = 0x10;
        } else {
            RicSetSpeedX(FIX(1.25));
            g_Player.unk44 = 0;
REDACTED
REDACTED
        RicSetAnimation(D_801554F0);
        PLAYER.velocityX = 0;
        g_Player.unk44 = 4;
REDACTED
    RicSetStep(PL_S_JUMP);
    if (g_IsPrologueStage) {
        PLAYER.velocityY = -FIX(4.6875);
REDACTED
        PLAYER.velocityY = -FIX(5.4375);
REDACTED
REDACTED

void RicSetHighJump(void) {
    RicSetStep(PL_S_HIGHJUMP);
    PLAYER.velocityX = 0;
    RicSetSpeedX(FIX(1.25));
    PLAYER.velocityY = FIX(-7.5);
    g_Player.pl_high_jump_timer = 0;
    RicSetAnimation(ric_anim_high_jump);
REDACTED
    RicCreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(0, 45), 0);
    g_api.PlaySfx(SFX_GRUNT_C);
    g_Player.D_80072F00[PL_T_12] = 4;
    if (g_Player.unk72) {
        PLAYER.velocityY = 0;
REDACTED
REDACTED

s32 func_8015D1D0(s16 subWpnId, s16 maxParticles) {
    Entity* entity;
    s32 nFound;
    s32 nEmpty;
    s32 i;

    entity = &g_Entities[32];
    for (i = 0, nFound = 0, nEmpty = 0; i < 16; i++, entity++) {
        if (entity->entityId == E_NONE) {
            nEmpty++;
        }
        if (entity->ext.generic.unkB0 != 0 &&
            entity->ext.generic.unkB0 == subWpnId) {
            nFound++;
        }
        if (nFound >= maxParticles) {
            return -1;
        }
    }
    if (nEmpty == 0) {
        return -1;
    }
    return 0;
}
