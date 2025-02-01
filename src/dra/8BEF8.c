// SPDX-License-Identifier: AGPL-3.0-or-later
#include "dra.h"
#include "dra_bss.h"
#include "sfx.h"

// echo of bat effect
void EntityBatEcho(Entity* self) {
#ifdef VERSION_PC
    u8 sp[SP_LEN];
#endif
    Primitive* prim;
    Primitive* temp;
    Unkstruct_8012BEF8* unkstruct;
    s32 i;
    s16 temp_unk7E;
    s32 var_s5;
    s32 var_s6;
    s32 temp_s7;
    s32 posX, posY;

    self->posX.i.hi = PLAYER.posX.i.hi;
    self->posY.i.hi = PLAYER.posY.i.hi;
    if ((self->ext.batEcho.unk8A % 384) == 0) {
        PlaySfx(SFX_BAT_ECHO_B);
    }
    self->ext.batEcho.unk8A += 1;
    if (self->ext.batEcho.unk88) {
        self->step = 3;
    }

    switch (self->step) {
    case 0:
        self->primIndex = g_api.AllocPrimitives(PRIM_G4, 0x31);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags = FLAG_HAS_PRIMS | FLAG_POS_PLAYER_LOCKED;
        prim = (Primitive*)&g_PrimBuf[self->primIndex];
        self->ext.batEcho.unk84 = prim;
        for (i = 0; i < 0x11; i++) {
            prim->type = PRIM_TILE;
            prim->drawMode = DRAW_HIDE;
            prim->y2 = D_800B0884[i];
            prim->x2 = (i * 3) + 1;
            prim->y3 = D_800B08A8[i];
            prim->x3 = (i << 0xA) & 0xFFF;
            prim->x1 = (i << 7) & 0xFFF;
            prim = prim->next;
        }
        for (i = 0; i < 0x20; i++) {
            prim->drawMode = DRAW_UNK_200 | DRAW_TPAGE2 | DRAW_TPAGE |
                             DRAW_COLORS | DRAW_TRANSP;
            prim->priority = PLAYER.zPriority - 2;
            prim = prim->next;
        }
        self->ext.batEcho.unk80 = 0xA0;
        if (IsRelicActive(RELIC_FORCE_OF_ECHO)) {
            self->ext.batEcho.unk80 = 0x100;
            self->hitboxOffX = 0x40;
            self->hitboxOffY = -4;
            self->hitboxWidth = 0x28;
            self->hitboxHeight = 0xC;
            func_8011A328(self, 0xA);
        }
        self->step += 1;
        break;
    case 1:
        self->ext.batEcho.unk7E += 0xA;
        if (self->ext.batEcho.unk7E > self->ext.batEcho.unk80) {
            self->ext.batEcho.unk7E = self->ext.batEcho.unk80;
            self->hitboxState = 0;
            self->step += 1;
        }
        break;
    case 2:
        self->ext.batEcho.unk7E -= 0xA;
        if (self->ext.batEcho.unk7E < 0) {
            self->ext.batEcho.unk7E = 0;
            DestroyEntity(self);
            return;
        }
        break;
    case 3:
        prim = self->ext.batEcho.unk84;
        while (prim != NULL) {
            prim->drawMode = DRAW_HIDE;
            prim = prim->next;
        }
        if (!--self->ext.batEcho.unk88) {
            DestroyEntity(self);
        }
        return;
    }

    prim = self->ext.batEcho.unk84;
    posX = PLAYER.posX.i.hi;
    posY = PLAYER.posY.i.hi;
    unkstruct = (Unkstruct_8012BEF8*)SP(sizeof(Primitive));
    for (i = 0; i < 0x11; i++, unkstruct++) {
        prim->x3 += 0x100;
        unkstruct->unk4 = prim->x3;
        prim->x1 -= 0x40;
        unkstruct->unk6 = prim->x1;
        unkstruct->unk8 = prim->x2;
        unkstruct->unkA = prim->y2;
        unkstruct->unkC = prim->y3;
        unkstruct->unk10 = rcos(unkstruct->unk6) >> 6;
        unkstruct->unk14 = rcos(unkstruct->unk6 + 0x100) >> 6;
        unkstruct->unk18 = rsin(unkstruct->unk4) >> 4;
        prim = prim->next;
    }

    temp = (Primitive*)SP(0);
    posX = PLAYER.posX.i.hi;
    posY = PLAYER.posY.i.hi;
    if (self->facingLeft) {
        var_s5 = posX - 16;
    } else {
        var_s5 = posX + 16;
    }

    temp_s7 = (((rsin(PLAYER.rotZ) >> 4) * 0xA) >> 8) - 6;
    temp_s7 = posY + temp_s7;
    temp_unk7E = self->ext.batEcho.unk7E;
    unkstruct = (Unkstruct_8012BEF8*)SP(sizeof(Primitive));

    temp->x3 = temp->x1 = var_s5;
    temp->y1 = temp_s7 + ((unkstruct->unk18 * unkstruct->unkA) >> 9);
    temp->y3 = temp->y1 - unkstruct->unk8;

    temp->r1 =
        (unkstruct->unk10 + 0x41) * unkstruct->unkC * temp_unk7E / FIX(1);
    temp->g1 =
        (unkstruct->unk14 + 0x41) * unkstruct->unkC * temp_unk7E / FIX(1);
    temp->b1 =
        (-unkstruct->unk10 + 0x41) * unkstruct->unkC * temp_unk7E / FIX(1);

    var_s6 = temp->y1 + unkstruct->unk8;
    unkstruct++;
    for (i = 0; i < 0x10; i++, unkstruct++) {
        if (self->facingLeft) {
            var_s5 -= 8;
        } else {
            var_s5 += 8;
        }
        *(s32*)&prim->x0 = *(s32*)&temp->x0 = *(s32*)&temp->x1;
        *(s32*)&prim->x2 = *(s32*)&temp->x2 = *(s32*)&temp->x3;
        prim->x3 = prim->x1 = temp->x3 = temp->x1 = var_s5;
        prim->y1 = temp->y1 =
            temp_s7 + ((unkstruct->unk18 * unkstruct->unkA) >> 9);
        prim->y3 = temp->y3 = temp->y1 - unkstruct->unk8;

        *(s32*)&prim->r0 = *(s32*)&temp->r0 = *(s32*)&temp->r1;

        prim->r1 = temp->r1 =
            (unkstruct->unk10 + 0x41) * unkstruct->unkC * temp_unk7E / FIX(1);
        prim->g1 = temp->g1 =
            (unkstruct->unk14 + 0x41) * unkstruct->unkC * temp_unk7E / FIX(1);
        prim->b1 = temp->b1 =
            (-unkstruct->unk10 + 0x41) * unkstruct->unkC * temp_unk7E / FIX(1);

        prim->type = PRIM_G4;
        prim = prim->next;
        *(s32*)&prim->x0 = *(s32*)&temp->x0;
        *(s32*)&prim->x1 = *(s32*)&temp->x1;
        *(s32*)&prim->x2 = *(s32*)&temp->x2;
        *(s32*)&prim->x3 = *(s32*)&temp->x3;
        *(s32*)&prim->r0 = *(s32*)&temp->r0;
        *(s32*)&prim->r1 = *(s32*)&temp->r1;
        prim->y2 = var_s6;
        var_s6 = temp->y1 + unkstruct->unk8;
        prim->y3 = var_s6;
        prim->type = PRIM_G4;
        prim = prim->next;
    }
}

void func_8012C600(void) {
    s32 x, y;
    s32 i;
    s32 t0 = PLAYER.posX.i.hi;
    s32 t1 = PLAYER.posY.i.hi;

    x = g_Entities[20].posX.i.hi + 8;
    for (i = 0; i < 9; i++) {
        if (x <= g_Entities[i + 21].posX.i.hi + 4) {
            x = g_Entities[i + 21].posX.i.hi + 4;
        }
    }
    D_8013AEBC[0] = x - t0;

    x = g_Entities[20].posX.i.hi - 8;
    for (i = 0; i < 9; i++) {
        if (x >= g_Entities[i + 21].posX.i.hi - 4) {
            x = g_Entities[i + 21].posX.i.hi - 4;
        }
    }
    D_8013AEBC[2] = x - t0;

    y = g_Entities[21].posY.i.hi;
    for (i = 0; i < 9; i++) {
        if (y >= g_Entities[i + 21].posY.i.hi) {
            y = g_Entities[i + 21].posY.i.hi;
        }
    }
    y = y - 4;
    if (y >= g_Entities[30].posY.i.hi - 12) {
        y = g_Entities[30].posY.i.hi - 12;
    }
    if (y >= g_Entities[20].posY.i.hi - 8) {
        y = g_Entities[20].posY.i.hi - 8;
    }
    D_8013AEBC[3] = y - t1;
    if (D_8013AEBC[3] < -24) {
        D_8013AEBC[3] = -24;
    }

    y = g_Entities[21].posY.i.hi;
    for (i = 0; i < 9; i++) {
        if (y <= g_Entities[i + 21].posY.i.hi) {
            y = g_Entities[i + 21].posY.i.hi;
        }
    }
    y = y + 4;

    if (y <= PLAYER.posY.i.hi + 28) {
        y = PLAYER.posY.i.hi + 28;
    }
    if (y <= g_Entities[17].posY.i.hi + 28) {
        y = g_Entities[17].posY.i.hi + 28;
    }
    D_8013AEBC[1] = y - t1;
    if (D_8013AEBC[1] > 0x27) {
        D_8013AEBC[1] = 0x27;
    }

    if (!PLAYER.facingLeft) {
        if (D_8013AEBC[2] < -0x2C) {
            D_8013AEBC[2] = -0x2C;
        }
        if (D_8013AEBC[0] > 0x14) {
            D_8013AEBC[0] = 0x14;
        }
    } else {
        if (D_8013AEBC[2] < -0x14) {
            D_8013AEBC[2] = -0x14;
        }
        if (D_8013AEBC[0] > 0x2C) {
            D_8013AEBC[0] = 0x2C;
        }
    }
}

bool WolfFormFinished(void) {
    if (PLAYER.step_s == 0) {
        return false;
    }
    if (PLAYER.step_s == 8) {
        return false;
    }
    if (D_80097448[1] != 0 && !IsRelicActive(RELIC_HOLY_SYMBOL) ||
        g_Player.padTapped & PAD_R2 ||
        HandleTransformationMP(FORM_WOLF, REDUCE) < 0) {
        SetPlayerStep(Player_UnmorphWolf);
        SetPlayerAnim(0xCA);
        D_800AFDA4[1] = 1;
        PLAYER.palette = 0x810D;
        g_Player.unk66 = 0;
        g_Player.unk68 = 0;
        // Create factory for EntityPlayerBlinkWhite
        CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(44, 0x24), 0);
        PLAYER.velocityY >>= 1;
        return true;
    }
    return false;
}

void func_8012C97C(void) {
    if (g_Entities[PLAYER_CHARACTER].step_s == 0) {
        return;
    }
    if (g_Entities[PLAYER_CHARACTER].step_s >= 8 &&
        g_Entities[PLAYER_CHARACTER].step_s < 10) {
        return;
    }
    if (D_80097448[1] < 13) {
        return;
    }
    if (!IsRelicActive(RELIC_HOLY_SYMBOL)) {
        return;
    }
    if (!IsRelicActive(RELIC_SKILL_OF_WOLF)) {
        return;
    }
    if (g_Player.pl_vram_flag & 1) {
        return;
    }
    if (!(g_Player.padPressed & PAD_TRIANGLE)) {
        return;
    }
    if (D_80138440 != 0) {
        return;
    }

    PLAYER.step_s = 9;
    D_800B0914 = 0;
    SetPlayerAnim(0xEC);
    PLAYER.velocityY = 0;
}

void func_8012CA64(void) {
    u8 anim;

    PLAYER.step_s = 1;
    D_800B0914 = 0;

    anim = 0xDE;
    if (g_Player.pl_vram_flag & 0x20) {
        anim = 0xDF;
    }
    SetPlayerAnim(anim);

    PLAYER.velocityY = 0;
    PLAYER.velocityX /= 2;

    D_800B0918 = 0x200;
    if (g_Player.pl_vram_flag & 0x40) {
        D_800B0914 = 1;
        SetPlayerAnim(0xE9);
    }
}

void func_8012CB0C(void) {
    PLAYER.ext.player.anim = 0xDE;
    PLAYER.velocityY = 0;
    D_800B0914 = 0;
    PLAYER.animFrameIdx = 0;
    PLAYER.animFrameDuration = 0;
    PLAYER.step_s = 7;
}

void func_8012CB4C(void) {
    PLAYER.step_s = 2;
    if ((PLAYER.facingLeft != 0 && g_Player.padPressed & PAD_RIGHT) ||
        (PLAYER.facingLeft == 0 && g_Player.padPressed & PAD_LEFT)) {
        SetPlayerAnim(0xE1);
        D_800B0914 = 0;
        D_8013842C = 0;
        return;
    } else if (D_8013842C != 0) {
        SetPlayerAnim(0xE2);
        D_800B0914 = 2;
        SetSpeedX(0x20000);
        return;
    } else {
        SetPlayerAnim(0xE0);
        D_800B0914 = 1;
        D_8013842C = 0xC;
    }
}

void func_8012CC30(s32 arg0) {
    if (arg0 == 0) {
        D_80138444 = 1;
        if (g_ButtonCombo[COMBO_QCF].buttonsCorrect == COMBO_COMPLETE &&
            IsRelicActive(RELIC_SKILL_OF_WOLF) &&
            CastSpell(SPELL_WOLF_CHARGE)) {
            CheckMoveDirection();
            PLAYER.step_s = 2;
            D_800B0914 = 4;
            SetSpeedX(0x50000);
            g_CurrentEntity->velocityY = 0;
            SetPlayerAnim(0xED);
            LearnSpell(4);
        }
    } else {
        D_80138444 = 1;
    }
}

void func_8012CCE4(void) {
    PLAYER.velocityY = FIX(-3.5);
    if ((PLAYER.step_s == 2) & (D_800B0914 == 2)) {
        SetPlayerAnim(0xE7);
        // Might be possible to rewrite this block to reduce duplication with
        // some clever && and ||
        if (PLAYER.facingLeft) {
            if ((g_Player.pl_vram_flag & 0xF000) == 0xC000) {
                PLAYER.velocityY = -(abs(PLAYER.velocityX) + FIX(3.5));
            }
            if ((g_Player.pl_vram_flag & 0xF000) == 0x8000) {
                PLAYER.velocityY = FIX(-0.5);
            }
        } else {
            if ((g_Player.pl_vram_flag & 0xF000) == 0x8000) {
                PLAYER.velocityY = -(abs(PLAYER.velocityX) + FIX(3.5));
            }
            if ((g_Player.pl_vram_flag & 0xF000) == 0xC000) {
                PLAYER.velocityY = FIX(-0.5);
            }
        }
        D_800B0914 = 2;
    } else if (
        (g_Player.padPressed & (PAD_RIGHT | PAD_LEFT)) &&
        ((PLAYER.step_s != 2) || (D_800B0914 != 0)) && (PLAYER.step_s != 9)) {
        SetPlayerAnim(0xE7);
        D_800B0914 = 1;
        if (g_Player.padPressed & PAD_UP) {
            PLAYER.velocityY = FIX(-4.875);
        }
    } else {
        SetPlayerAnim(0xE6);
        D_800B0914 = 0;
        if (g_Player.padPressed & PAD_UP) {
            PLAYER.velocityY = FIX(-4.875);
        }
    }
    PLAYER.step_s = 4;
    D_80138430 += 0x80;
}

void func_8012CED4(void) {
    if (PLAYER.step_s == 2 && D_800B0914 == PLAYER.step_s) {
        SetPlayerAnim(0xE7);
        D_800B0914 = 1;
    } else {
        SetPlayerAnim(0xE8);
        SetSpeedX(0x10000);
        D_800B0914 = 0;
        if (D_80138438 & 0x40) {
            PLAYER.animFrameIdx = 4;
            PLAYER.velocityX = 0;
            PLAYER.animFrameDuration = 1;
        }
    }
    PLAYER.step_s = 5;
    g_Player.timers[5] = 8;
    PLAYER.velocityY = 0;
    D_80138430 -= 0x100;
}

void func_8012CFA8(void) {
    SetPlayerAnim(0xEA);
    PLAYER.step_s = 6;
    D_800B0914 = 0;
    PLAYER.velocityX = 0;
    g_Player.timers[5] = 8;
}

void func_8012CFF0(void) {
    PLAYER.step_s = 3;
    SetPlayerAnim(0xE3);
    D_800B0914 = 0;
}

void func_8012D024(void) {
    DecelerateX(0x2000);
    if (g_Player.padTapped & PAD_CROSS) {
        func_8012CCE4();
        return;
    }
    if (!(g_Player.pl_vram_flag & 1)) {
        func_8012CED4();
        return;
    }
    if (g_Player.padTapped & PAD_SQUARE) {
        func_8012CC30(0);
        return;
    }
    if (g_Player.padPressed & (PAD_RIGHT | PAD_LEFT)) {
        func_8012CB4C();
        return;
    }
    if (g_Player.padPressed & PAD_DOWN) {
        func_8012CFF0();
        return;
    }
    if (D_800B0914 != 0) {
        return;
    }
    if (abs(PLAYER.posY.i.hi - g_Entities[17].posY.i.hi) < 4 &&
        --D_800B0918 == 0) {
        D_800B0914 = 1;
        SetPlayerAnim(0xE9);
        return;
    }
    if (g_Player.pl_vram_flag & 0x40) {
        D_800B0914 = 1;
        SetPlayerAnim(0xE9);
    }
}

void func_8012D178(void) {
    s32 var_v0;

    if (g_Player.padTapped & PAD_CROSS) {
        func_8012CCE4();
    } else if (!(g_Player.pl_vram_flag & 1)) {
        func_8012CFA8();
    } else {
#if defined(VERSION_US)
        if (PLAYER.facingLeft != 0) {
            var_v0 = g_Player.padPressed & PAD_LEFT;
        } else {
            var_v0 = g_Player.padPressed & PAD_RIGHT;
        }
#elif defined(VERSION_HD)
        var_v0 = g_Player.padPressed & (PAD_LEFT | PAD_RIGHT);
#endif
        if (var_v0 != 0) {
            func_8012CB4C();
        } else if (g_Player.unk04 & 0x40) {
            func_8012CA64();
        } else if (g_GameTimer % 6 == 0) {
            CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(69, 1), 0);
        }
    }
}

void func_8012D28C(bool exitEarly) {
    bool bitNotFound;
    s32 i;

    func_80102CD8(2);
    PlaySfx(SFX_WALL_DEBRIS_B);
    PLAYER.velocityX = 0;
    g_Player.D_80072EFC = 0x20;
    g_Player.padSim = 0;
    // Odd logic, if we exit early, we force an R2-tap. Strange!
    if (exitEarly) {
        g_Player.padTapped = PAD_R2;
        WolfFormFinished();
        return;
    }
    // Start a routine where we look through this array for a value.
    bitNotFound = 0;
    for (i = 3; i < NUM_VERTICAL_SENSORS; i++) {
        if (g_Player.colWall[i].effects & EFFECT_UNK_0002) {
            break;
        }
    }
    // If we made it through that loop without finding one, skip i=7,8,9
    // and keep searching.
    if (i == 7) {
        for (i = NUM_VERTICAL_SENSORS + 3; i < NUM_VERTICAL_SENSORS * 2; i++) {
            if (g_Player.colWall[i].effects & EFFECT_UNK_0002) {
                break;
            }
        }
    }
    // If we even made it through that one, then conclude the bit was not found.
    if (i == 14) {
        bitNotFound++;
    }

    SetSpeedX(FIX(1));
    CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(4, 9), 0);
    D_800B0914 = 0;
    // Finally make use of that bit to control if X is positive or negative.
    if (bitNotFound) {
        func_8012CED4();
        SetSpeedX(FIX(1));
    } else {
        func_8012CFA8();
        SetSpeedX(FIX(-1));
    }
    PLAYER.velocityY = FIX(-3.5);
}
