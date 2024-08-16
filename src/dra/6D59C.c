#include "dra.h"
#include "dra_bss.h"
#include "sfx.h"
#include "player.h"

u8 g_D_800ACF18[] = {10, 8, 8, 6, 6, 4, 4,   4,   4, 4,
                     4,  4, 4, 4, 4, 4, 255, 255, 0, 0};

// BSS
extern s16 g_WasFacingLeft;
extern s16 g_WasFacingLeft2;
extern s32 g_WasFacingLeft3;
extern s32 g_WasFacingLeft4;
extern s16 g_WasFacingLeft5;
extern s32 g_WasFacingLeft6;
extern s32 g_WasFacingLeft7;

// Same function in RIC is func_8015C4AC
void func_8010D59C(void) {
    byte stackpad[40];
    Primitive* prim;
    s32 i;

    if (g_Entities[1].ext.entSlot1.unk0 != 0) {
        return;
    }
    switch (PLAYER.ext.player.anim) {
    case 0x5D:
    case 0x5E:
    case 0x60:
    case 0x61:
    case 0x62:
        g_Entities[1].ext.entSlot1.unk2 = 10;
        return;
    }
    if ((g_Player.padTapped & GAMEBUTTONS) ||
        ((g_Player.padHeld ^ g_Player.padPressed) & g_Player.padHeld &
         GAMEBUTTONS) ||
        (PLAYER.velocityY > FIX(0.5))) {
        g_Entities[1].ext.entSlot1.unk2 = 0;
        g_Entities[1].ext.entSlot1.unk3 = 0;
    } else {
        if (g_Entities[1].ext.entSlot1.unk2 >= 10) {
            return;
        }
        if (g_Entities[1].ext.entSlot1.unk3 == 0) {
            g_Entities[1].ext.entSlot1.unk3 =
                g_D_800ACF18[g_Entities[1].ext.entSlot1.unk2];
        }
        if (!(--g_Entities[1].ext.entSlot1.unk3 & 0xFF)) {
            g_Entities[1].ext.entSlot1.unk2++;
            g_Entities[1].ext.entSlot1.unk3 =
                g_D_800ACF18[g_Entities[1].ext.entSlot1.unk2];
        }
    }
    if (g_Entities[1].animFrameIdx != 0) {
        g_Entities[1].animFrameIdx--;
        return;
    }
    prim = &g_PrimBuf[g_Entities[1].primIndex];
    for (i = 0; i < 6; i++) {
        if (i == g_Entities[1].entityId) {
            prim->r0 = prim->g0 = prim->b0 = 0x80;
            prim->x0 = PLAYER.posX.i.hi;
            prim->y0 = PLAYER.posY.i.hi;
            prim->x1 = PLAYER.animCurFrame;
            prim->y1 = 0;
            prim->x2 = PLAYER.facingLeft;
            prim->y2 = PLAYER.palette;
        }
        prim = prim->next;
    }
    g_Entities[1].animFrameIdx = 2;
    g_Entities[1].entityId++;
    if (g_Entities[1].entityId >= 6) {
        g_Entities[1].entityId = 0;
    }
}

u8 g_shadowOpacityReductionTable[] = {
    4, 4, 4, 4, 6, 6, 6, 6, 8, 8, 16, 16, 16, 16, 16, 16};
u8 g_D_800ACF3C[] = {8,  12, 16, 20, 24, 28, 32, 32,
                     32, 32, 32, 32, 32, 32, 32, 32};

// Equivalent in RIC is func_8015C6D4
void func_8010D800(void) {
    byte pad[0x28];
    PlayerDraw* plDraw;
    Primitive* prim;
    s32 entNum;
    s32 i;
    u8 temp_t0;
    u8 temp_t1;
    u8 temp_t2;

    i = 0;
    prim = &g_PrimBuf[g_Entities[1].primIndex];
    temp_t2 = g_Entities[1].ext.entSlot1.unk1;
    temp_t1 = g_shadowOpacityReductionTable[g_Entities[1].ext.entSlot1.unk2];
    temp_t0 = g_D_800ACF3C[g_Entities[1].ext.entSlot1.unk2];

    plDraw = &g_PlayerDraw[1];
    for (i = 0; i < 6; prim = prim->next, i++) {
        if (temp_t0 < prim->r0) {
            prim->r0 -= temp_t1;
        }
        if (prim->r0 < 112 && prim->b0 < 240) {
            prim->b0 += 6;
        }
        if (prim->r0 < 88) {
            prim->y1 = 16;
        } else {
            prim->y1 = 0;
        }
        if (temp_t0 >= prim->r0) {
            prim->x1 = 0;
        }
        if (!((i ^ g_Timer) & 1)) {
            continue;
        }

        entNum = (i / 2) + 1;
        g_Entities[entNum].posX.i.hi = prim->x0;
        g_Entities[entNum].posY.i.hi = prim->y0;
        g_Entities[entNum].animCurFrame = prim->x1;
        g_Entities[entNum].drawMode = prim->y1;
        g_Entities[entNum].facingLeft = prim->x2;
        g_Entities[entNum].palette = prim->y2;
        g_Entities[entNum].zPriority = PLAYER.zPriority - 2;
        if (temp_t2) {
            g_Entities[entNum].animCurFrame = 0;
            prim->x1 = 0;
        }

        plDraw->r0 = plDraw->r1 = plDraw->r2 = plDraw->r3 = plDraw->b0 =
            plDraw->b1 = plDraw->b2 = plDraw->b3 = prim->r0;
        plDraw->g0 = plDraw->g1 = plDraw->g2 = plDraw->g3 = prim->b0;
        plDraw->enableColorBlend = true;
        plDraw++;
    }
}

void func_8010DA2C(AnimationFrame* frames) {
    g_CurrentEntity->anim = frames;
    g_CurrentEntity->animFrameDuration = 0;
    g_CurrentEntity->animFrameIdx = 0;
}

void SetPlayerAnim(s32 anim) {
    g_CurrentEntity->ext.player.anim = anim;
    g_CurrentEntity->animFrameDuration = 0;
    g_CurrentEntity->animFrameIdx = 0;
}

AnimationFrame* func_8010DA70(AnimationFrame** frames) {
    s32 idxSub;
    s32 var_s1;
    s32 idx;
    u16* subanim;
    u16* anim;

    anim = (u16*)frames[g_CurrentEntity->ext.player.anim];
    idx = 0;
    var_s1 = 0;
    while (true) {
        if ((&anim[idx * 2])[0] == 0xFFFD) {
            idxSub = 0;
            while (true) {
                subanim = (u16*)D_800B0594[(&anim[idx * 2])[1] & 0xFF];
                if ((&subanim[idxSub * 2])[0] == 0xFFFF) {
                    idx++;
                    break;
                }
                if (var_s1 == g_CurrentEntity->animFrameIdx) {
                    return (AnimationFrame*)&subanim[idxSub * 2];
                }
                idxSub++;
                var_s1++;
            }
        } else if (var_s1 == g_CurrentEntity->animFrameIdx) {
            return (AnimationFrame*)(anim + idx * 2);
        } else {
            var_s1++;
            idx++;
        }
    }
}

u32 UpdateUnarmedAnim(s8* frameProps, u16** frames) {
    u16* frameIndex;

    frameIndex = frames[g_CurrentEntity->ext.player.anim] + PLAYER.animFrameIdx;
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

void PlayAnimation(s8* frameProps, AnimationFrame** frames) {
    AnimationFrame* animFrame;

    animFrame = func_8010DA70(frames);
    if (g_CurrentEntity->animFrameDuration != -1) {
        if (g_CurrentEntity->animFrameDuration == 0) {
            g_CurrentEntity->animFrameDuration = animFrame->duration;
        } else if (--g_CurrentEntity->animFrameDuration == 0) {
            g_CurrentEntity->animFrameIdx++;
            animFrame = func_8010DA70(frames);
            // Using a switch doesn't work
            if (animFrame->duration == 0x0) {
                g_CurrentEntity->animFrameIdx = animFrame->unk2;
                animFrame = func_8010DA70(frames);
                g_CurrentEntity->animFrameDuration = animFrame->duration;
            } else if (animFrame->duration == 0xFFFF) {
                g_CurrentEntity->animFrameIdx--;
                g_CurrentEntity->animFrameDuration = -1;
                animFrame = func_8010DA70(frames);
            } else if (animFrame->duration == 0xFFFE) {
                g_CurrentEntity->ext.player.anim = animFrame->unk2 & 0xFF;
                g_CurrentEntity->animFrameIdx = animFrame->unk2 >> 8;
                animFrame = func_8010DA70(frames);
                g_CurrentEntity->animFrameDuration = animFrame->duration;
            } else {
                g_CurrentEntity->animFrameDuration = animFrame->duration;
            }
        }
    }

    if (frameProps != NULL) {
        // This is ugly - theoretically the type for frameProps should be
        // FrameProperty* but anything besides this where we assign this big
        // expression fails.

        // Please check function UpdateAnim down below
        frameProps = &frameProps[((animFrame->unk2 >> 9) & 0x7F) * 4];
        g_CurrentEntity->hitboxOffX = *frameProps;
        frameProps++;
        g_CurrentEntity->hitboxOffY = *frameProps;
        frameProps++;
        g_CurrentEntity->hitboxWidth = *frameProps;
        frameProps++;
        g_CurrentEntity->hitboxHeight = *frameProps;
    }
    g_CurrentEntity->animCurFrame = animFrame->unk2 & 0x1FF;
}

u32 UpdateAnim(s8* frameProps, AnimationFrame** anims) {
    AnimationFrame* animFrame;
    s32 ret;

    if (g_CurrentEntity->animFrameDuration == -1) {
        ret = -1;
    } else if (g_CurrentEntity->animFrameDuration == 0) {
        g_CurrentEntity->animFrameDuration =
            g_CurrentEntity->anim[g_CurrentEntity->animFrameIdx].duration;
        ret = 0;
    } else if ((--g_CurrentEntity->animFrameDuration) == 0) {
        g_CurrentEntity->animFrameIdx++;
        animFrame = &g_CurrentEntity->anim[g_CurrentEntity->animFrameIdx];
        // Effectively a switch statement, but breaks if I actually use one.
        if (animFrame->duration == 0) {
            g_CurrentEntity->animFrameIdx = animFrame->unk2;
            g_CurrentEntity->animFrameDuration =
                g_CurrentEntity->anim[g_CurrentEntity->animFrameIdx].duration;
            ret = 0;
        } else if (animFrame->duration == 0xFFFF) {
            g_CurrentEntity->animFrameIdx--;
            g_CurrentEntity->animFrameDuration = -1;
            ret = -1;
        } else if (animFrame->duration == 0xFFFE) {
            g_CurrentEntity->anim = anims[animFrame->unk2];
            g_CurrentEntity->animFrameIdx = 0;
            ret = -2;
            g_CurrentEntity->animFrameDuration =
                g_CurrentEntity->anim[0].duration;
        } else {
            g_CurrentEntity->animFrameDuration = animFrame->duration;
        }
    }
    if (frameProps != NULL) {
        // This is ugly - theoretically the type for frameProps should be
        // FrameProperty* but anything besides this where we assign this big
        // expression fails.
        frameProps =
            &frameProps[(g_CurrentEntity->anim[g_CurrentEntity->animFrameIdx]
                             .unk2 >>
                         9)
                        << 2];
        g_CurrentEntity->hitboxOffX = *frameProps++;
        g_CurrentEntity->hitboxOffY = *frameProps++;
        g_CurrentEntity->hitboxWidth = *frameProps++;
        g_CurrentEntity->hitboxHeight = *frameProps++;
    }
    g_CurrentEntity->animCurFrame =
        g_CurrentEntity->anim[g_CurrentEntity->animFrameIdx].unk2 & 0x1FF;
    return ret;
}

void func_8010DF70(void) {
    g_CurrentEntity = &PLAYER;

    switch (PLAYER.ext.player.anim) {
    case 0xBA:
    case 0xBB:
    case 0xBE:
    case 0xF0:
    case 0xF1:
        PlayAnimation(D_800B0130, D_800B01B8);
    }
}

void func_8010DFF0(s32 arg0, s32 arg1) {
    Primitive* prim;
    s32 i;

    if (arg0 != 0) {
        g_Entities[UNK_ENTITY_1].ext.generic.unk7C.U8.unk1 = 1;
        g_Entities[UNK_ENTITY_3].animCurFrame = 0;
        g_Entities[UNK_ENTITY_2].animCurFrame = 0;
        g_Entities[UNK_ENTITY_1].animCurFrame = 0;
        prim = &g_PrimBuf[g_Entities[UNK_ENTITY_1].primIndex];

        for (i = 0; i < 6; i++) {
            prim->x1 = 0;
            prim = prim->next;
        }
    }

    g_Entities[UNK_ENTITY_1].ext.generic.unk7C.U8.unk0 = 1;
    g_Entities[UNK_ENTITY_1].ext.generic.unk7E.modeU8.unk0 = 10;

    if (arg1 != 0) {
        if (arg1 < 4) {
            g_Player.D_80072F00[15] = 4;
        } else {
            g_Player.D_80072F00[15] = arg1;
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
        entity = CreateEntFactoryFromEntity(g_Entities, FACTORY(0x4700, 44), 0);

        if (entity != NULL) {
            entity->flags |= FLAG_UNK_10000;
        }

        entity = CreateEntFactoryFromEntity(g_Entities, FACTORY(0x4000, 44), 0);

        if (entity != NULL) {
            entity->flags |= FLAG_UNK_10000;
        }
    }
    func_8010DFF0(1, 1);
}
void func_8010E168(s32 arg0, s16 arg1) {
    if (arg0 == 0) {
        // Create factory with unkA0 = 0x1500, blueprint #44.
        // Blueprint 44 is to make child entity #11, or EntityPlayerBlinkWhite
        CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(0x1500, 44), 0);
        if (arg1 >= g_Player.D_80072F00[13]) {
            g_Player.D_80072F00[13] = arg1;
        }
    } else if (g_Player.D_80072F00[14] <= arg1) {
        g_Player.D_80072F00[14] = arg1;
    }
}

void DecelerateX(s32 amount) {
    if (g_CurrentEntity->velocityX < 0) {
        g_CurrentEntity->velocityX += amount;
        if (g_CurrentEntity->velocityX > 0) {
            g_CurrentEntity->velocityX = 0;
        }
    } else {
        g_CurrentEntity->velocityX -= amount;
        if (g_CurrentEntity->velocityX < 0) {
            g_CurrentEntity->velocityX = 0;
        }
    }
}

void DecelerateY(s32 amount) {
    if (g_CurrentEntity->velocityY < 0) {
        g_CurrentEntity->velocityY += amount;
        if (g_CurrentEntity->velocityY > 0) {
            g_CurrentEntity->velocityY = 0;
        }
    } else {
        g_CurrentEntity->velocityY -= amount;
        if (g_CurrentEntity->velocityY < 0) {
            g_CurrentEntity->velocityY = 0;
        }
    }
}

// Checks the player's left/right inputs and compares to the facing direction.
// If the player is pressing the opposite of facing, we change the facing value
// to turn the player around, and return -1.
// If the player is pressing the same direction they are facing, return 1
// If the player is not pressing left or right, return 0
// Note that if the player is pressing both left and right, left is ignored.
s32 CheckMoveDirection(void) {
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
    if (g_CurrentEntity->facingLeft == 1) {
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
    PLAYER.step = Player_Teleport;

    if (!(arg0 & 1)) {
        SetPlayerAnim(0xF4);
    } else {
        SetPlayerAnim(0xF5);
    }
}

u8 D_800ACF4C[] = {0x00, 0x11, 0x04, 0x15, 0x01, 0x10, 0x03, 0x23};

void func_8010E470(s32 arg0, s32 arg1) {
    PLAYER.velocityX = arg1;
    PLAYER.velocityY = 0;
    PLAYER.step = Player_Crouch;
    PLAYER.step_s = D_800ACF4C[arg0 * 2 + 0];
    SetPlayerAnim(D_800ACF4C[arg0 * 2 + 1]);
}

// This may be the function that turns Alucard into stone
void func_8010E4D0(void) {
    func_80111CC0();

    PLAYER.palette = 0x8100;
    PLAYER.zPriority = g_unkGraphicsStruct.g_zEntityCenter;

    if ((u32)(g_Player.unk72 - 1) < 2U) {
        SetPlayerAnim(0xC7);
        PLAYER.velocityY = 0;
        PLAYER.velocityX = 0;
        SetPlayerStep(Player_AlucardStuck);
        func_80111CC0();
        PlaySfx(NA_SE_VO_AL_WHAT);
        return;
    }
    func_80111CC0();
    func_8010E470(0, 0);
}

u8 D_800ACF54[] = {
    0x04, 0x05, 0x0A, 0x0B, 0x0E, 0x0F, 0x1D, 0x1E, 0x04, 0x03, 0x00, 0x00,
};

// Corresponding RIC function is RicLandToTheGround (much simpler)
void func_8010E570(s32 arg0) {
    s32 anim;
    s32 atLedge;

    atLedge = 0;
    if (g_Player.pl_vram_flag & 0x20) {
        atLedge = 1;
    }

    PLAYER.velocityX = arg0;
    PLAYER.velocityY = 0;
    SetPlayerStep(Player_Stand);
    if (g_Player.unk48 != 0) {
        PLAYER.step_s = 2;
        atLedge = 0;
    }
    switch (g_Player.unk50) {

    case 9:
        anim = 4;
        break;
    case 1:
        anim = 4;
        if (PLAYER.ext.player.anim == 9) {
            PLAYER.ext.player.anim = D_800ACF54[2 + atLedge];
            return;
        }
        if (PLAYER.ext.player.anim == 7) {
            anim = 0;
        }
        break;
    case 3:
    case 4:
        anim = 6;
        if (abs(PLAYER.velocityX) > FIX(2.5)) {
            anim = 4;
        }
        break;
    default:
        anim = 8;
        break;
    }
    anim += atLedge;
    SetPlayerAnim(D_800ACF54[anim]);
}

void func_8010E6AC(s32 arg0) {
    bool atLedge;

    atLedge = 0;
    if (g_Player.pl_vram_flag & 0x20) {
        atLedge = 1;
    }

    SetSpeedX(0x18000);
    PLAYER.velocityY = 0;
    SetPlayerStep(Player_Walk);

    if (arg0 != 0) {
        if (PLAYER.ext.player.anim != 0xD) {
            SetPlayerAnim(0xD);
        }
    } else {
        SetPlayerAnim(7);
        CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(0x500, 1), 0);
    }

    if (g_Player.unk4C != 0) {
        PLAYER.ext.player.anim = 9;
    }

    if ((PLAYER.ext.player.anim == 7) && atLedge) {
        PLAYER.animFrameIdx = 1;
    }

    if (g_Player.unk50 == 2) {
        PLAYER.animFrameIdx = 4;
    }
}

void func_8010E7AC(void) {
    SetPlayerStep(Player_Fall);

    if (g_Player.unk50 != 1) {
        SetPlayerAnim(0x1C);
    }

    PLAYER.velocityY = 0x20000;
    PLAYER.velocityX = 0;
    g_Player.D_80072F00[6] = 8;

    if (g_Player.unk04 & 1) {
        g_Player.D_80072F00[5] = 8;
    } else {
        g_Player.D_80072F00[5] = 0;
    }

    g_Player.unk44 = 0x10;
}

void func_8010E83C(s32 arg0) {
    if (g_Player.unk72 != 0) {
        func_8010E7AC();
        return;
    } else if (CheckMoveDirection() != 0) {
        SetPlayerAnim(0x1A);
        SetSpeedX(0x18000);
        g_Player.unk44 = 0;
    } else {
        SetPlayerAnim(0x16);
        PLAYER.velocityX = 0;
        g_Player.unk44 = 4;
    }

    PLAYER.velocityY = FIX(-4.875);
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
    SetPlayerAnim(0x20);
    PLAYER.step_s = 0;
    PLAYER.velocityY = -0x44000;
    if (g_Player.unk72 != 0) {
        PLAYER.velocityY = 0;
    }
}

void DoGravityJump(void) {
    if (CheckMoveDirection() != 0) {
        SetSpeedX(FIX(3));
    } else {
        PLAYER.velocityX = 0;
    }

    if (PLAYER.step == Player_Jump) {
        g_Player.unk44 |= 1;
    } else {
        g_Player.unk44 = 0;
    }
    // Factory with blueprint 2, creates child entity 3 which is
    // EntityGravityBootBeam
    CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(0, 2), 0);
    SetPlayerStep(Player_HighJump);
    PLAYER.velocityY = FIX(-12);
    SetPlayerAnim(0x21);
    g_Player.unk4A = 0;
}

s16 g_SfxAttackGrunts[] = {
    SFX_UNK_6EE, SFX_UNK_6EF, SFX_UNK_6F0, NA_SE_VO_AL_PUNCH, 0x0000, 0x0000};

void func_8010EA54(s32 arg0) {
    s16 temp_hi;

    if (arg0 != 0) {
        temp_hi = rand() % arg0;
        if (temp_hi < 4) {
            PlaySfx(g_SfxAttackGrunts[temp_hi]);
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

s32 func_8010EB5C(void) {
    SubweaponDef subWpn;
    s16 subWpnId;
    s32 atLedge;
    u8 anim;

    atLedge = 0;
    if (!(g_Player.padPressed & PAD_UP)) {
        return 1;
    }
    if (g_Player.pl_vram_flag & 0x20) {
        atLedge = 1;
    }
    subWpnId = func_800FE3C4(&subWpn, 0, false);

    if (subWpnId == 0) {
        return 1;
    }
    if (subWpnId == 6 && g_unkGraphicsStruct.unk0 != 0) {
        return 4;
    }
    if (func_8010EADC(subWpnId, subWpn.unk6) < 0) {
        return 2;
    }
    subWpnId = func_800FE3C4(&subWpn, 0, true);
    if (subWpnId == 0) {
        return 3;
    }
    CreateEntFactoryFromEntity(
        g_CurrentEntity, FACTORY(0, subWpn.blueprintNum), subWpnId << 9);
    g_Player.D_80072F00[10] = 4;
    if (PLAYER.step_s < 64) {
        anim = subWpn.anim;
        if (PLAYER.step == 0) {
            SetPlayerAnim(anim + atLedge);
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

    chainLimit = g_EquipDefs[itemId].chainLimit;
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

void func_8010ED54(u8 anim) {
    PLAYER.velocityY = 0;
    PLAYER.velocityX = 0;
    SetPlayerStep(Player_SwordWarp);
    SetPlayerAnim(anim);
    CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(0x1400, 61), 0);
    g_Player.unk48 = 0;
}

bool func_8010EDB8(void) {
    s32 step;
    Equipment sp10;
    Entity* ent;
    Equipment* equipped_item;
    s16 var_s2; // mixed between anim and equip index
    u16 equipped_id;
    u16 hand;
    s16 animVariant;
    s32 attBtnsPressed;
    bool var_s7; // Triggers on some kind of special move spell
    s32 i;
    s32 atLedge;

    var_s7 = 0;
    attBtnsPressed = g_Player.padTapped & (PAD_SQUARE | PAD_CIRCLE);

    atLedge = 0;
    if (g_Player.pl_vram_flag & 0x20) {
        atLedge = 1;
    }

    if (attBtnsPressed != 0 && func_8010EB5C() == 0) {
        return 1;
    }
    if (g_Player.unk48 == 0) {
        if ((GetEquipItemCategory(0) == ITEM_SHIELD) &&
            (g_Player.padPressed & PAD_SQUARE)) {
            attBtnsPressed |= PAD_SQUARE;
        }
        if ((GetEquipItemCategory(1) == ITEM_SHIELD) &&
            (g_Player.padPressed & PAD_CIRCLE)) {
            attBtnsPressed |= PAD_CIRCLE;
        }
    }
    if (attBtnsPressed == 0) {
        return 0;
    }
    if (attBtnsPressed == PAD_CIRCLE) {
        g_Player.D_80072EF8 = PAD_CIRCLE;
        hand = 1;
    }
    if (attBtnsPressed == PAD_SQUARE) {
        g_Player.D_80072EF8 = PAD_SQUARE;
        hand = 0;
    }
    if (attBtnsPressed == (PAD_SQUARE | PAD_CIRCLE)) {
        if ((g_Player.unk72 == 0) && (D_8013AEE4 != 0)) {
            var_s2 = D_8013AEE4;
            if (var_s2 != 0) {
                equipped_item = &g_EquipDefs[var_s2];
                equipped_id = var_s2;
            }
            g_Player.D_80072EF8 = 0x80;
            hand = ((D_8013AEE4 & (1 << 31)) != 0);
            if (CheckChainLimit(equipped_id, hand) >= 0) {
                if (HasEnoughMp(g_EquipDefs[equipped_id].mpUsage, 0) == 0) {
                    var_s7 = 1;
                    goto block_45;
                }
            }
        }
        g_Player.D_80072EF8 = 0x80;
        hand = 0;
    }

    equipped_id = g_Status.equipment[hand];
    equipped_item = &g_EquipDefs[g_Status.equipment[hand]];

    if (equipped_item->unk17 == equipped_item->specialMove &&
        equipped_item->unk17 != 0) { // Literally just the Combat Knife
        if (g_Entities[16].ext.entSlot16.unkAE == equipped_id) {
            var_s2 = equipped_item->unk17;
            equipped_item = &g_EquipDefs[var_s2];
            equipped_id = var_s2;
            if (CheckChainLimit(equipped_id, hand) < 0) {
                goto block_32;
            }
            goto block_45;
        } else if (g_Entities[16].ext.entSlot16.unkAE == equipped_item->unk17 &&
                   CheckChainLimit(equipped_id, hand) >= 0) {
            goto block_45;
        }
    }

block_32:
    equipped_id = g_Status.equipment[hand];
    equipped_item = &g_EquipDefs[g_Status.equipment[hand]];
    if (g_ButtonCombo[COMBO_QCF].buttonsCorrect != COMBO_COMPLETE) {
        goto block_38c;
    }
    var_s2 = equipped_item->specialMove;
    if (var_s2 == 0 ||
        // Sword of Dawn
        ((equipped_id == 0x11) && ((g_Player.pl_vram_flag & 0x41) != 1)) ||
        !(g_Player.pl_vram_flag & 1)) {
        goto block_38c;
    }
    // Load up the item's special move as the new "virtual" equipped item since
    // we're attacking with the special
    equipped_item = &g_EquipDefs[var_s2];
    equipped_id = var_s2;
    if (CheckChainLimit(equipped_id, hand) < 0 ||
        HasEnoughMp(g_EquipDefs[equipped_id].mpUsage, 0)) {
    block_38c:
        equipped_item = &g_EquipDefs[g_Status.equipment[hand]];
        if (g_ButtonCombo[COMBO_BF].buttonsCorrect == 0xFF) {
            var_s2 = equipped_item->unk17;
            if (var_s2 != 0) {
                equipped_item = &g_EquipDefs[var_s2];
                equipped_id = var_s2;
                if (CheckChainLimit(equipped_id, hand) >= 0) {
                    goto block_45;
                }
            }
        }
        equipped_id = g_Status.equipment[hand];
        equipped_item = &g_EquipDefs[g_Status.equipment[hand]];
        if (CheckChainLimit(equipped_id, hand) < 0) {
            return 0;
        }
    }
block_45:
    if (equipped_id != 0) {
        if (equipped_item->unk13 == 55) {     // Medicines
            if (equipped_item->unk14 == 20) { // Library card!
                if (PLAYER.step == 0 || PLAYER.step == 1 || PLAYER.step == 2) {
                    func_8010E42C(0);
                    func_800FDD44(hand);
                    return 1;
                }
                return 0;
            }
            ent = &g_Entities[32];
            for (i = 32; i < 64; i++) {
                if (ent->entityId == 0x27) {
                    return 0;
                }
                ent++;
            }
            // TODO: FACTORY()
            if (CreateEntFactoryFromEntity(
                    g_CurrentEntity,
                    (((equipped_item->unk14 & 0x7F) + (hand << 7)) << 0x10) |
                        0x37,
                    equipped_id) == NULL) {
                return 0;
            }
        } else {
            if (g_Player.D_80072F00[1] != 0) {
                CreateEntFactoryFromEntity(
                    g_CurrentEntity, FACTORY(0x100, 57), 0);
                goto block_70;
            }
            if (var_s7 == 0) {
                // TODO: FACTORY()
                if (CreateEntFactoryFromEntity(
                        g_CurrentEntity,
                        equipped_item->unk13 + ((hand + 1) << 12) +
                            (((equipped_item->unk14 & 0x7F) + (hand << 7))
                             << 0x10),
                        equipped_id) == NULL) {
                    return 0;
                }
            } else {
                // TODO: FACTORY()
                if (CreateEntFactoryFromEntity(
                        g_CurrentEntity,
                        equipped_item->unk13 + ((hand + 1) << 14) +
                            (((equipped_item->unk14 & 0x7F) + (hand << 7))
                             << 0x10),
                        equipped_id) == NULL) {
                    return 0;
                }
            }
        }
    } else if (
        // TODO: FACTORY()
        CreateEntFactoryFromEntity(
            g_CurrentEntity, (hand + 42) + (hand << 23), 0) == NULL) {
        return 0;
    }
    func_800FDD44(hand);
    if (var_s7 != 0) {
        func_800FDD44((hand + 1) & 1);
    }
    HasEnoughMp(g_EquipDefs[equipped_id].mpUsage, 1);
    // 95 is Estoc
    if ((equipped_id == 95) && (g_Player.unk72 != 0)) {
        return 0;
    }

    var_s2 = equipped_item->playerAnim;
    switch (equipped_item->unk11) {
    case 29: // Muramasa
        GetEquipProperties(hand, &sp10, equipped_id);
        if (sp10.attack < 11) {
        case 13: // Red Rust
            if (!(rand() & 7)) {
            block_70:
                switch (PLAYER.step) {
                case 0:
                case 1:
                    SetPlayerAnim(0xB5);
                    PLAYER.step = 0;
                    break;
                case 2:
                    SetPlayerAnim(0xB6);
                    PLAYER.step = 2;
                    break;
                case 3:
                case 4:
                    SetPlayerAnim(0xB7);
                    PLAYER.step = 4;
                    break;
                }
                g_Player.unk46 = 0x8012;
                g_Player.unk54 = 0xFF;
                PLAYER.step_s = 0x51;
                PlaySfx(SFX_UNK_6E7);
                return 1;
            }
        }
        func_8010EA54(8);
        goto block_98;
    case 12: // Shotel
        // When shotel is thrown away, attempting to attack will make a punch
        if ((CheckChainLimit(equipped_item->specialMove, hand) < 0) ||
            (CheckChainLimit(equipped_item->specialMove, (hand + 1) & 1) < 0)) {
            equipped_item = &g_EquipDefs[0];
            // TODO: FACTORY()
            CreateEntFactoryFromEntity(
                g_CurrentEntity, (hand + 42) + (hand << 23), 0);
            var_s2 = g_EquipDefs[0].playerAnim;
        }
        func_8010EA54(8);
        goto block_98;
    case 19: // Unknown, not a direct equippable item
        D_80139824 = 0x28;
        PLAYER.step = 0;
        g_CurrentEntity->velocityX = 0;
        PlaySfx(SFX_UNK_6EF);
        goto block_98;
    case 20: // Unknown, not a direct equippable item
        PLAYER.step = 0;
        D_80139824 = 0x28;
        g_CurrentEntity->velocityX = 0;
        PlaySfx(SFX_UNK_6EF);
        goto block_98;
    case 21: // Unknown, not a direct equippable item
        PLAYER.step = 0;
        D_80139824 = 0x28;
        g_CurrentEntity->velocityX = 0;
        PlaySfx(SFX_UNK_6EF);
        goto block_98;
    case 22: // Unknown, not a direct equippable item (but there are 4 of them)
        PLAYER.step = 0;
        D_80139824 = 0x28;
        g_CurrentEntity->velocityX = 0;
        PlaySfx(SFX_UNK_6EF);
        goto block_98;
    case 28: // Unknown, not a direct equippable item
        PLAYER.step = 0;
        D_80139824 = 0xA;
        g_CurrentEntity->velocityX = 0;
        PlaySfx(SFX_UNK_6EF);
        goto block_98;
    case 23: // Unknown, not a direct equippable item (but there are 4 of them)
        PLAYER.step = 0;
        CheckMoveDirection();
        SetSpeedX(FIX(5));
        g_CurrentEntity->velocityY = 0;
        PlaySfx(SFX_UNK_6EF);
        goto block_98;
    case 27: // Estoc
        animVariant = atLedge;
        CheckMoveDirection();
        SetSpeedX(FIX(4));
        PLAYER.velocityX >>= 1;
        PlaySfx(SFX_UNK_6EF);
        if (g_Player.pl_vram_flag & 1) {
            PLAYER.step = 0;
            g_CurrentEntity->velocityY = 0;
        } else {
            PLAYER.step = 4;
        }
        SetPlayerAnim(var_s2 + animVariant);
        g_Player.unk46 = equipped_item->unk11 - 0x7FFF;
        g_Player.unk54 = equipped_item->lockDuration;
        PLAYER.step_s = equipped_item->unk11 + 0x40;
        g_Player.D_80072F00[9] = 4;
        break;
    case 24: // Unknown, not a direct equippable item (but there are 2 of them)
        if (2 < PLAYER.step && PLAYER.step < 5) {
            PLAYER.step = 4;
        } else {
            PLAYER.step = 0;
        }
        D_80139824 = 0x80;
        g_CurrentEntity->velocityY = 0;
        g_CurrentEntity->velocityX = 0;
        PlaySfx(SFX_UNK_6EF);
        goto block_98;
    case 26: // Unknown, not a direct equippable item (but there are 2 of them)
        PLAYER.step = 0;
        D_80139824 = 0x28;
        g_CurrentEntity->velocityY = 0;
        g_CurrentEntity->velocityX = 0;
        PlaySfx(SFX_UNK_6EF);
        goto block_98;
    case 0: // Most normal swords come in this range
    case 1:
    case 2:
    case 3:
    case 4:
    case 6:
    case 7:
    case 11:
    case 14:
    case 15:
    case 16:
    case 18:
        func_8010EA54(8);
    case 8:
    case 9: // Combat Knife
    case 10:
    case 25:
    block_98:
        switch (PLAYER.step) {
        case 0:
        case 1:
            g_CurrentEntity->velocityX >>= 1;
            PLAYER.step = 0;
            animVariant = atLedge;
            break;
        case 2:
            animVariant = 2;
            if (g_Player.padPressed & (PAD_RIGHT | PAD_LEFT)) {
                animVariant = 3;
            }
            if (g_Player.unk72 == 0 && PLAYER.step_s == 2) {
                PLAYER.step = 0;
                animVariant = atLedge;
            }
            break;
        case 3:
        case 4:
            animVariant = 4;
            if (PLAYER.velocityY > 0) {
                animVariant = 5;
                if (equipped_item->unk11 == 0) {
                    if (g_Player.padPressed & (PAD_RIGHT | PAD_LEFT) &&
                        g_Player.padPressed & PAD_DOWN) {
                        animVariant = 6;
                    }
                } else if (g_Player.padPressed & PAD_DOWN) {
                    animVariant = 6;
                }
            }
            break;
        }
        SetPlayerAnim(var_s2 + animVariant);
        g_Player.unk46 = equipped_item->unk11 - 0x7FFF;
        g_Player.unk54 = equipped_item->lockDuration;
        PLAYER.step_s = equipped_item->unk11 + 0x40;
        g_Player.D_80072F00[9] = 4;
        break;
    case 5: // Lots of unknown things
        step = PLAYER.step;
        if (step >= 0) {
            if (step < 3) {
                g_CurrentEntity->velocityX >>= 1;
                SetPlayerAnim(var_s2 + atLedge);
                g_Player.unk46 = equipped_item->unk11 - 0x7FFF;
                g_Player.unk54 = equipped_item->lockDuration;
                PLAYER.step = 0;
                PLAYER.step_s = equipped_item->unk11 + 0x40;
                g_CurrentEntity->velocityX = 0;
            }
        }
        func_8010EA54(8);
        break;
    case 128: // Shields
        var_s2 = equipped_item->playerAnim;
        switch (PLAYER.step) {
        case 0:
            PLAYER.step_s = 2;
            SetPlayerAnim(var_s2 + atLedge);
            break;
        case 2:
            PLAYER.step_s = 0;
            SetPlayerAnim(var_s2 + 2);
            break;
        case 1:
        case 3:
        case 4:
            break;
        }
        break;
    case 134: // Holbein Dagger and Blue Knuckles
        func_8010DFF0(1, 0x20);
    case 129: // Consumable weapons (throwing stars, etc)
    case 130:
        func_8010EA54(8);
    case 132: // Food
        if (PLAYER.step_s < 0x40) {
            var_s2 = equipped_item->playerAnim;
            switch (PLAYER.step) {
            case 0:
                SetPlayerAnim(var_s2 + atLedge);
                break;
            case 2:
                animVariant = 2;
                if (g_Player.unk72 == 0 && PLAYER.step_s == 2) {
                    animVariant = atLedge;
                    SetPlayerStep(Player_Stand);
                }
                SetPlayerAnim(var_s2 + animVariant);
            case 1:
            case 3:
            case 4:
                break;
            }
        }
        break;
    case 131: // Medicines
        if (PLAYER.step_s < 0x40) {
            var_s2 = equipped_item->playerAnim;
            if (PLAYER.step == 0) {
                SetPlayerAnim(var_s2 + atLedge);
            }
        }
        break;
    case 135: // Unknown
        PlaySfx(SFX_UNK_6F0);
        g_Player.D_80072F00[9] = 4;
        func_8010ED54(equipped_item->playerAnim);
        break;
    }
    return 1;
}

void func_8010FAF4(void) {
    DestroyEntity(&g_Entities[E_WEAPON]);
    g_Player.unk46 = 0;
}

void PerformHellfire(void) {
    PLAYER.velocityY = 0;
    PLAYER.velocityX = 0;
    SetPlayerStep(Player_SpellHellfire);
    func_8010E168(1, 0x10);
    func_8010E3E0();
}

void func_8010FB68(void) { // Related to Dark Metamorphosis
    PLAYER.velocityY = 0;
    PLAYER.velocityX = 0;
    SetPlayerStep(Player_SpellDarkMetamorphosis);
    func_8010E3E0();
    SetPlayerAnim(0xBA);
    PlaySfx(NA_SE_VO_AL_DARK_METAMORPHOSIS);
    PlaySfx(NA_SE_PL_MP_GAUGE);
    g_Player.D_80072F00[11] =
        GetStatusAilmentTimer(STATUS_AILMENT_DARK_METAMORPHOSIS, 0x400);
    func_801092E8(1);
    CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(0x1100, 40), 0);
    func_80118C28(0xB);
}

void func_8010FBF4(void) { // Related to Soul Steal spell
    PLAYER.velocityY = 0;
    PLAYER.velocityX = 0;
    SetPlayerStep(Player_SpellSoulSteal);
    func_8010E3E0();
    SetPlayerAnim(0xDA);
    PlaySfx(NA_SE_VO_AL_SOUL_STEAL);
    func_80118C28(0xC);
    g_Player.D_80072F00[12] = 4;
}

void func_8010FC50(void) {
    PLAYER.velocityY = 0;
    PLAYER.velocityX = 0;
    SetPlayerStep(Player_SpellSummonSpirit);
    func_8010E3E0();
    CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(0, 117), 0);
    SetPlayerAnim(0xF0);
    PlaySfx(NA_SE_VO_AL_PUNCH);
    g_Player.D_80072F00[12] = 4;
}

void func_8010FCB8(void) {
    PLAYER.velocityY = 0;
    PLAYER.velocityX = 0;
    SetPlayerStep(Player_SpellTetraSpirit);
    func_8010E3E0();
    CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(0x100, 117), 0);
    SetPlayerAnim(0xF1);
    PlaySfx(NA_SE_VO_AL_PUNCH);
    g_Player.D_80072F00[12] = 4;
}

void func_8010FD24(void) {
    PLAYER.velocityY = 0;
    PLAYER.velocityX = 0;
    SetPlayerStep(Player_SpellSwordBrothers);
    func_8010E3E0();
    SetPlayerAnim(0xF1);
    CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(0x1700, 40), 0);
    g_Player.D_80072F00[12] = 4;
}

void func_8010FD88(void) {
    PLAYER.step = Player_Stand;
    PLAYER.step_s = 3;
    SetSpeedX(0xFFFC8000);
    g_CurrentEntity->velocityY = 0;
    SetPlayerAnim(0xDB);
    CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(0, 0), 0);
    g_Player.unk46 = 0;
    PlaySfx(SFX_SCRAPE_C);
}

bool func_8010FDF8(s32 branchFlags) {
    u8 stackpad[0x28];
    s32 tempYAccel;
    s32 tempTriangle;
    s32 YAccel;

    if (branchFlags & 8 && g_Player.unk46 == 0) {
        CheckMoveDirection();
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

    if (D_80097448[0] >= 0x29) {
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
                    PlaySfx(SFX_STOMP_SOFT_B, 0x30, 0);
                    return 1;
                }

                if (PLAYER.velocityY > FIX(6.875)) {
                    func_8010E470(1, 0);
                    PlaySfxVolPan(SFX_STOMP_HARD_B);
                    CreateEntFactoryFromEntity(
                        g_CurrentEntity, FACTORY(0, 0), 0);
                } else {
                    if (g_Player.unk44 & 0x10) {
                        func_8010E6AC(1);
                    } else {
                        func_8010E570(0);
                    }
                    PlaySfx(SFX_STOMP_SOFT_B, 0x30, 0);
                }

                func_8010FAF4();
                return 1;
            }

            if (PLAYER.velocityY > FIX(6.875)) {
                if ((PLAYER.step_s == 112) || (PLAYER.step == 4)) {
                    func_8010E470(3, PLAYER.velocityX / 2);
                } else {
                    func_8010E470(1, 0);
                }
                PlaySfx(SFX_STOMP_HARD_B);
                CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(0, 0), 0);
                return 1;
            }

            if (g_Player.unk44 & 0x10) {
                func_8010E6AC(1);
                goto label;
            }

            if (abs(PLAYER.velocityX) > 0x20000) {
                PlaySfx(SFX_STOMP_HARD_B);
                CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(0, 0), 0);
                func_8010E570(PLAYER.velocityX);
            } else {
                PlaySfx(SFX_STOMP_SOFT_B, 0x30, 0);
                func_8010E570(0);
            }
            return 1;
        }
        if (branchFlags & 0x20000 && g_Player.pl_vram_flag & 1) {
            func_8010E470(3, PLAYER.velocityX);
            PlaySfx(SFX_STOMP_HARD_B);
            CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(0, 0), 0);
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

    if (branchFlags & 0x20 && IsRelicActive(RELIC_LEAP_STONE) &&
        g_Player.padTapped & PAD_CROSS && !(g_Player.unk44 & 1)) {
        func_8010E940();
        return 1;
    }

    if (branchFlags & 0x2000 && g_Player.padPressed & PAD_DOWN) {
        func_8010E470(2, 0);
        return 1;
    }

    if (branchFlags & 0x40000 && PLAYER.ext.player.anim != 0xDB) {
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

s16 D_800ACF6C[] = {0, -8, -16, -22};

s16 func_80110394(void) {
    // Variables that change during execution
    Collider collider;
    s32 yvar;
    s32 collisions;
    s32 i;
    // Values that are set once and never again (but not const for some reason)
    s32 xpos = PLAYER.posX.i.hi;
    s32 xp4 = xpos + 4;
    s32 xm4 = xpos - 4;
    s32 coll_flags = EFFECT_SOLID_FROM_ABOVE | EFFECT_SOLID;

    for (i = 0; i < 4; i++) {
        yvar = PLAYER.posY.i.hi + D_800ACF6C[i];
        CheckCollision(xpos, yvar, &collider, 0);
        collisions = 0;
        if ((collider.effects & coll_flags) == EFFECT_SOLID) {
            collisions += 1;
        }
        CheckCollision(xp4, yvar, &collider, 0);
        if ((collider.effects & coll_flags) == EFFECT_SOLID) {
            collisions += 1;
        }
        CheckCollision(xm4, yvar, &collider, 0);
        if ((collider.effects & coll_flags) == EFFECT_SOLID) {
            collisions += 1;
        }
        if (collisions != 0) {
            return i + 1;
        }
    }
    return 0;
}
