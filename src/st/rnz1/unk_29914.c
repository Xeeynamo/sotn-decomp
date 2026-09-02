// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rnz1.h"

INCLUDE_ASM("st/rnz1/nonmatchings/unk_29914", func_801CDC80);

s32 func_pspeu_092508B8(s32 arg0) {
#ifdef VERSION_PSP
    Collider sp2C;
#endif
    Entity* other;
    s32 var_s5;
    s32 xVar, yVar;
    s32 var_s2;
    s32 var_s1;

    for (var_s1 = 0; var_s1 < 0x10; var_s1++) {
        if (!(Random() & 7) && (arg0 || !(g_Timer & 7))) {
            other = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (other != NULL) {
                CreateEntityFromEntity(E_ID(UNK_31), g_CurrentEntity, other);
                other->posY.i.hi = 0xC8;
                if (g_CurrentEntity->facingLeft) {
                    other->posX.i.hi += (var_s1 * 8);
                } else {
                    other->posX.i.hi -= (var_s1 * 8);
                }
                other->scaleX = other->scaleY = 0x140 - (var_s1 * 8);
                other->facingLeft = g_CurrentEntity->facingLeft;
            }
        }
    }
    FntPrint("damage:%x\n", g_CurrentEntity->ext.ILLEGAL.u8[0xF]);
    if ((g_Player.unk60) == 2) {
        other = &PLAYER;
        other->velocityY -= 0x2000;
        if (g_CurrentEntity->facingLeft) {
            other->velocityX += 0x2000;
        } else {
            other->velocityX -= 0x2000;
        }
        var_s5 = g_Player.vram_flag & ~TOUCHING_GROUND;
#ifdef VERSION_PSP
        xVar = other->posX.i.hi;
        yVar = F(other->posY).i.hi + F(other->velocityY).i.hi;
        g_api.CheckCollision(xVar, yVar, &sp2C, 0);
        if (sp2C.effects & (EFFECT_UNK_0002 | EFFECT_SOLID)) {
            var_s5 = 1;
        }
        xVar = F(other->posX).i.hi + F(other->velocityX).i.hi;
        yVar = other->posY.i.hi;
        g_api.CheckCollision(xVar, yVar, &sp2C, 0);
        if (sp2C.effects & (EFFECT_UNK_0002 | EFFECT_SOLID)) {
            var_s5 = 1;
        }
        if (var_s5 == 0) {
#else
        if (var_s5 == 0 && g_PlayableCharacter == PLAYER_ALUCARD) {
#endif
            other->posX.val += other->velocityX;
            other->posY.val += other->velocityY;
        }
        if (other->velocityY > FIX(-4)) {
            return 1;
        }
        var_s2 = g_CurrentEntity->ext.ILLEGAL.u8[0xF];
        g_Player.unk64 = (g_api.enemyDefs[275].attack / var_s2);
        g_Player.unk60 = 4;
        if (var_s2 > 2) {
            g_Player.unk60 = 0;
        }
        if (g_CurrentEntity->facingLeft) {
            other->velocityX = FIX(10) / var_s2;
        } else {
            other->velocityX = FIX(-10) / var_s2;
        }
        other->velocityY = FIX(-3) / var_s2;
        return 1;
    }
    if ((g_Player.unk60) || (arg0 == 0)) {
        return 0;
    }
    other = &PLAYER;
    var_s2 = g_CurrentEntity->posX.i.hi - other->posX.i.hi;
    if (g_CurrentEntity->facingLeft) {
        var_s2 = -var_s2;
    }
    if (var_s2 > 0x80U) {
        return 0;
    }
    var_s2 = other->velocityX;
    if (g_CurrentEntity->facingLeft) {
        var_s2 = -var_s2;
    }
    if ((g_Player.status & PLAYER_STATUS_UNK4000000) && (var_s2 > 0)) {
        other->posX.val -= other->velocityX / 2;
        return 0;
    }
    if (!(g_Player.status & (PLAYER_STATUS_AXEARMOR | PLAYER_STATUS_DEAD | PLAYER_STATUS_UNK10000 | PLAYER_STATUS_INVINCIBLE | PLAYER_STATUS_STONE | PLAYER_STATUS_CROUCH | PLAYER_STATUS_MIST_FORM))) {
        g_Player.unk60 = 1;
        g_Player.unk64 = 0;
        g_Player.unk62 = 0;
        var_s2 = GetDistanceToPlayerX();
        var_s2 = (var_s2 - 0x30) / 24;
        if (var_s2 <= 0) {
            var_s2 = 1;
        }
        g_CurrentEntity->ext.ILLEGAL.u8[0xF] = var_s2;
        return 1;
    }
    return 0;
}

INCLUDE_ASM("st/rnz1/nonmatchings/unk_29914", func_us_801A9DB8);

INCLUDE_ASM("st/rnz1/nonmatchings/unk_29914", EntityFrozenShadeCrystal);

INCLUDE_ASM("st/rnz1/nonmatchings/unk_29914", func_us_801AAF00);

INCLUDE_ASM("st/rnz1/nonmatchings/unk_29914", func_us_801AB04C);
