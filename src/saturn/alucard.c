// SPDX-License-Identifier: AGPL-3.0-or-later
#include "inc_asm.h"
#include "sattypes.h"

#include "alucard.h"

// CheckMoveDirection
s32 func_060A5060(void) {
    s32 result = 0;

    if (g_Player.unk44 & 2) {
        return 0;
    }

    if (!PLAYER.facingLeft) {
        if (g_Player.padPressed & PAD_LEFT) {
            PLAYER.facingLeft = 1;
            g_Player.unk4C = 1;
            result = -1;
        } else if (g_Player.padPressed & PAD_RIGHT) {
            result = 1;
        }
    } else {
        if (g_Player.padPressed & PAD_LEFT) {
            result = 1;
        } else if (g_Player.padPressed & PAD_RIGHT) {
            PLAYER.facingLeft = 0;
            g_Player.unk4C = 1;
            result = -1;
        }
    }

    return result;
}
// func_8010FDF8 on PSX
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60A50E0, func_060A50E0);

// SAT: func_060A5558
void SetPlayerStep(PlayerSteps step) {
    PLAYER.step = step;
    PLAYER.step_s = 0;
}

// SetSpeedX
void func_060A5574(s32 param_1) {
    if (PLAYER.facingLeft == 1) {
        param_1 = -param_1;
    }
    PLAYER.velocityX = param_1;
}
// func_8010E3B8 on PSX
void func_060A5594(s32 param_1) {
    if (PLAYER.entityRoomIndex == 1) {
        param_1 = -param_1;
    }
    PLAYER.velocityX = param_1;
}
// DecelerateX (PLAYER-specialized Saturn version)
void func_060A55B4(s32 arg0) {
    if (PLAYER.velocityX < 0) {
        PLAYER.velocityX += arg0;
        if (PLAYER.velocityX > 0) {
            PLAYER.velocityX = 0;
        }
    } else {
        PLAYER.velocityX -= arg0;
        if (PLAYER.velocityX < 0) {
            PLAYER.velocityX = 0;
        }
    }
}
// DecelerateY (PLAYER-specialized Saturn version)
void func_060A55E4(s32 arg0) {
    if (PLAYER.velocityY < 0) {
        PLAYER.velocityY += arg0;
        if (PLAYER.velocityY > 0) {
            PLAYER.velocityY = 0;
        }
    } else {
        PLAYER.velocityY -= arg0;
        if (PLAYER.velocityY < 0) {
            PLAYER.velocityY = 0;
        }
    }
}
// DecelerateX (g_CurrentEntity version)
void func_060A5614(s32 arg0) {
    if (g_CurrentEntity->velocityX < 0) {
        g_CurrentEntity->velocityX += arg0;
        if (g_CurrentEntity->velocityX > 0) {
            g_CurrentEntity->velocityX = 0;
        }
    } else {
        g_CurrentEntity->velocityX -= arg0;
        if (g_CurrentEntity->velocityX < 0) {
            g_CurrentEntity->velocityX = 0;
        }
    }
}
// DecelerateY (g_CurrentEntity version)
void func_060A5644(s32 arg0) {
    if (g_CurrentEntity->velocityY < 0) {
        g_CurrentEntity->velocityY += arg0;
        if (g_CurrentEntity->velocityY > 0) {
            g_CurrentEntity->velocityY = 0;
        }
    } else {
        g_CurrentEntity->velocityY -= arg0;
        if (g_CurrentEntity->velocityY < 0) {
            g_CurrentEntity->velocityY = 0;
        }
    }
}
// SetPlayerAnim
void func_060A5674(s32 anim) {
    g_Player.unk39D = (g_Player.unk39D & 0x9F) | 0x10;
    g_Player.anim = anim;
    g_Player.poseTimer = 0;
    g_Player.pose = 0;
}
// func_8010DA2C on PSX
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60A56AC, func_060A56AC);

void func_060A56D8() {}

// func_8010E470 on PSX
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60A56E4, func_060A56E4);
// CheckPlayerStuck
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60A5738, func_060A5738);
// func_8010E570 on PSX
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60A580C, func_060A580C);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60A5938, func_060A5938);
// func_8010E6AC on PSX
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60A59E0, func_060A59E0);
// func_8010E7AC on PSX
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60A5AF0, func_060A5AF0);
// func_8010E83C on PSX
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60A5B94, func_060A5B94);
// func_8010E940 on PSX
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60A5CD8, func_060A5CD8);
// DoGravityJump
void func_060A5D50(void) {
    // SetSpeedX
    if (func_060A5060() != 0) {
        func_060A5574(FIX(3.75));
    } else {
        PLAYER.velocityX = 0;
    }

    if (PLAYER.step == Player_Jump) {
        g_Player.unk44 |= 1;
    } else {
        g_Player.unk44 = 0;
    }

    // creates the gravity boot beam
    func_060BAF44(g_CurrentEntity, 2, 0);

    SetPlayerStep(Player_HighJump);
    PLAYER.velocityY = FIX(-12);

    // SetPlayerAnim
    func_060A5674(17);
    g_Player.unk4A = 0;
}

// func_8010FD88 on PSX
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60A5E14, func_060A5E14);
// PerformDarkMetamorphosis
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60A5EA8, func_060A5EA8);
// PerformSummonSpirit
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60A5F9C, func_060A5F9C);
// PerformHellfire
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60A605C, func_060A605C);
// PerformTetraSpirit
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60A60EC, func_060A60EC);
// PerformSoulSteal
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60A61B0, func_060A61B0);
// PerformSwordBrothers
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60A6248, func_060A6248);
void func_060A62E4(void) {
    s32 velocityX;

    PLAYER.step_s = 3;
    velocityX = 0x60000;
    if (PLAYER.facingLeft == 1) {
        velocityX = -velocityX;
    }
    PLAYER.velocityX = velocityX;
}
// CheckSubwpnChainLimit
s32 func_060A6314(s16 subwpnId, s16 limit) {
    Entity* entity;
    s32 i;
    s32 nFound;
    s32 nEmpty;

    entity = &g_Entities[32];
    for (i = 0, nFound = 0, nEmpty = 0; i < 16; i++, entity++) {
        if (!entity->entityId) {
            nEmpty++;
        }
        if (entity->ext.subweapon.subweaponId &&
            entity->ext.subweapon.subweaponId == subwpnId) {
            nFound++;
        }
        if (nFound >= limit) {
            return -1;
        }
    }
    if (nEmpty) {
        return 0;
    }
    return -1;
}
// CheckChainLimit
s32 func_060A637C(s32 itemId, s32 handId) {
    Entity* entity;
    s32 existing_count;
    s32 i;
    s32 chainLimit;

    chainLimit = DAT_0607C266[itemId * 0x34];
    if (chainLimit & 0x80) {
        if (!(g_Player.unk46 & 0x8000)) {
            return 0;
        }
        return -1;
    }

    entity = &g_Entities[16];
    for (i = 16, existing_count = 0; i < 64; i++, entity++) {
        if (entity->ext.ILLEGAL.s16[0x19] != itemId) {
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
// func_8010EB5C on PSX
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60A6420, func_060A6420);
// func_8010ED54 on PSX
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60A6618, func_060A6618);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60A6688, func_060A6688);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60A66FC, func_060A66FC);
// func_8010EDB8 on PSX
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60A67B8, func_060A67B8);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60A6A94, func_060A6A94);
// func_8010FAF4 on PSX
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60A7D3C, func_060A7D3C);
// func_8010DFF0 on PSX
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60A7D68, func_060A7D68);
// EnableAfterImage
void func_060A7DD0() { g_Player.unk39C = 6; }
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60A7DE8, func_060A7DE8);
s32 func_060A7E90(void) {
    Collider collider;
    s32 x;
    s32 y;
    s32 left;
    s32 right;
    s32 result;
    s32 speed = 0xC000;

    x = PLAYER.posX.val;
    y = PLAYER.posY.val;

    CheckCollision(x - 0x70000, y, &collider, 0);
    left = collider.effects & 0x10;

    CheckCollision(x + 0x70000, y, &collider, 0);
    right = collider.effects & 0x10;

    if (right & left) {
        register void (*call_func)();
        call_func = (void (*)())func_060A5574;
        call_func(speed);
        result = 1;
    } else if (right) {
        PLAYER.velocityX = -speed;
        result = 1;
    } else {
        result = 0;
        if (left) {
            PLAYER.velocityX = speed;
            result = 1;
        }
    }

    return result;
}
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60A7F28, func_060A7F28);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60A80E0, func_060A80E0);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60A81DC, func_060A81DC);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60A8D78, func_060A8D78);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60A8DF4, func_060A8DF4);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60A9658, func_060A9658);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60A96A0, func_060A96A0);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60A972C, func_060A972C);
void func_060A9D90(u16 arg0) {
    s32 xOffset;

    xOffset = 4;
    if (PLAYER.facingLeft) {
        xOffset = -4;
    }
    PLAYER.posY.val -= FIX(22);
    PLAYER.posX.i.hi += xOffset;
    func_060BAF44(g_CurrentEntity, 0x10004U, 0);
    PLAYER.posY.val += FIX(22);
    PLAYER.posX.i.hi -= xOffset;
    if (arg0 & 1) {
        func_0600FB0C(3);
        PlaySfx(0x644);
    }
    if (arg0 & 2) {
        PLAYER.velocityX = 0;
        PLAYER.velocityY = 0;
    }
}
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60A9E3C, func_060A9E3C);
void func_060AA0FC(void) {
    if (g_Player.timers[1] != 0) {
        func_060BAF44(g_CurrentEntity, 0x17002CU, 0);
    }
    if (g_Player.timers[0] != 0) {
        func_060BAF44(g_CurrentEntity, 0x16002CU, 0);
    }
}
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60AA150, func_060AA150);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60AA23C, func_060AA23C);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60AADE4, func_060AADE4);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60AB090, func_060AB090);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60AB0BC, func_060AB0BC);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60AB0E8, func_060AB0E8);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60AB308, func_060AB308);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60AB37C, func_060AB37C);
// func_8010E0D0 on PSX
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60AB3A8, func_060AB3A8);
// func_8010E168 on PSX
void func_060AB44C(s32 kind, s16 invincibilityFrames) {
    if (kind == 0) {
        func_060BAF44(g_CurrentEntity, 0x15002CU, 0);
        if (g_Player.timers[0xD] <= invincibilityFrames) {
            g_Player.timers[0xD] = invincibilityFrames;
        }
    } else if (g_Player.timers[0xE] <= invincibilityFrames) {
        g_Player.timers[0xE] = invincibilityFrames;
    }
}
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60AB4A4, func_060AB4A4);
void func_060AB558(void) {
    PLAYER.velocityY = 0;
    PLAYER.velocityX = 0;
    if ((g_Player.padSim >> 16) != 2) {
        func_060A580C(0);
    }
}
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60AB590, func_060AB590);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60AB5E0, func_060AB5E0);
s32 func_060AB78C(void) {
    register void (*set_player_step)(PlayerSteps);

    if (PLAYER.step_s != 0) {
        if (g_unkGraphicsStruct.D_8009744C == 0 &&
            (g_Player.padTapped & 0x40) == 0 && func_06070410(1, 1) >= 0) {
            if (func_0606FC60(8) != 0) {
                return 0;
            }
            if (DAT_060CE490 != 0) {
                DAT_060CE490--;
            }
            if (DAT_060CE490 != 0) {
                return 0;
            }
        }
        func_060A5060();
        set_player_step = SetPlayerStep;
        set_player_step(Player_UnmorphMist);
        return 1;
    }
    return 0;
}
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60AB814, func_060AB814);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60ABCF0, func_060ABCF0);
void func_060ABFA4(void) {
    if (PLAYER.step_s == 0) {
        if (g_Entities[0x10].entityId == 0) {
            DAT_060CE494 = 0x10;
            func_060BAF44(g_CurrentEntity, 0x15003D, 0);
            PLAYER.step_s++;
        }
    } else if (--DAT_060CE494 == 0) {
        PLAYER.palette = 0;
        func_060A580C(0);
    }
}
// Nudges the player towards a fixed X position, one pixel per frame.
void func_060AC018(void) {
    s32 distance;

    if (g_CurrentRoom.stageID == 0x0B) {
        distance = (g_Tilemap.left << 8) + g_PlayerX;
        if (distance < 0) {
            distance = -distance;
        }
        if ((distance - 0x1F8F) > 0) {
            PLAYER.posX.i.hi--;
        }

        distance = (g_Tilemap.left << 8) + g_PlayerX;
        if (distance < 0) {
            distance = -distance;
        }
        if ((distance - 0x1F8F) < 0) {
            PLAYER.posX.i.hi++;
        }
    }

    if (g_CurrentRoom.stageID == 0x2B) {
        distance = (g_Tilemap.left << 8) + g_PlayerX;
        if (distance < 0) {
            distance = -distance;
        }
        if ((distance - 0x20EE) > 0) {
            PLAYER.posX.i.hi--;
        }

        distance = (g_Tilemap.left << 8) + g_PlayerX;
        if (distance < 0) {
            distance = -distance;
        }
        if ((distance - 0x20EE) < 0) {
            PLAYER.posX.i.hi++;
        }
    }
}
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60AC0C8, func_060AC0C8);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60AC20C, func_060AC20C);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60AC2F0, func_060AC2F0);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60AC574, func_060AC574);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60AC8F4, func_060AC8F4);
void func_060ACACC(void* unused, SpriteObject* sprite, s32 count) {
    s32 i;

    sprite->flags &= ~0x40;
    if (PLAYER.drawFlags & ENTITY_ROTATE) {
        sprite->flags |= 0x40;
        sprite->rotate = PLAYER.rotate;
    } else {
        sprite->rotate = 0;
    }

    sprite->scaleX = sprite->scaleY = 0x40;
    if (PLAYER.drawFlags & ENTITY_SCALEX) {
        sprite->scaleX = (u32)PLAYER.scaleX >> 2;
        sprite->flags |= 0x40;
    }
    if (PLAYER.drawFlags & ENTITY_SCALEY) {
        sprite->scaleY = (u32)PLAYER.scaleY >> 2;
        sprite->flags |= 0x40;
    }

    for (i = 0; i < count; i++) {
        sprite->parts->attributes &= ~0x2000;
        sprite++;
    }
}
// PlayAnimation (Saturn player-specialized version)
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60ACB6C, func_060ACB6C);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60ACF00, func_060ACF00);
void func_060AD44C(s32 arg0, s32 arg1) {
    s16 steps[6];
    u16 index;
    u16 buttons;

    index = 0xFFFF;
    buttons = g_Player.padTapped;
    steps[0] = 7;
    steps[1] = 5;
    steps[2] = 0x18;
    steps[3] = 0xE;
    steps[4] = 9;
    steps[5] = 0x19;

    if (buttons & 0x40) {
        index = 0;
    } else if (buttons & 0x20) {
        index = 1;
    } else if (buttons & 0x10) {
        index = 2;
    }

    if (index != 0xFFFF) {
        if ((u16)steps[index] == PLAYER.step) {
            index += 3;
        }
        PLAYER.step = steps[index];
        PLAYER.step_s = 0;
        g_Player.unk39C = 0xFF;
        PLAYER.rotate = 0;
    }

    if ((u16)((s16)PLAYER.step - 0x18) > 1) {
        func_060B7994();
    }
}
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60AD524, func_060AD524);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60AD714, func_060AD714);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60ADACC, func_060ADACC);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60ADB80, func_060ADB80);

void func_060ADD50() {}

void func_060ADD5C() {}

void func_060ADD68() {}

// func_8010DF70 on PSX
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60ADD74, func_060ADD74);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60ADDDC, func_060ADDDC);
// AluInit
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60ADF3C, func_060ADF3C);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60AE048, func_060AE048);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60AE184, func_060AE184);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60AE284, func_060AE284);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60AE36C, func_060AE36C);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60AE544, func_060AE544);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60AE6F4, func_060AE6F4);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60AE8E4, func_060AE8E4);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60AEAE8, func_060AEAE8);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60AECC4, func_060AECC4);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60AEEE4, func_060AEEE4);
void func_060AEFBC(void) {
    if (DAT_060C84F8 == 0) {
        if (g_Status.mp == g_Status.mpMax && !(g_Player.status & 0x100000)) {
            if (g_Player.demo_timer == 0) {
                func_060BAF44(g_CurrentEntity, 0x28U, 0);
                PlaySfx(0x67D);
            }
            DAT_060C84F8++;
        }
    } else if (g_Status.mp != g_Status.mpMax) {
        DAT_060C84F8 = 0;
    }
}
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60AF050, func_060AF050);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60AF124, func_060AF124);

INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60AF1BC, func_060AF1BC);

void func_060AF4A0(void) { func_060AF1BC(1); }

INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60AF4B8, func_060AF4B8);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60AF550, func_060AF550);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60AF654, func_060AF654);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60AF7F0, func_060AF7F0);
typedef enum {
    TELEPORT_CHECK_NONE = 0,
    TELEPORT_CHECK_TO_RTOP = 2,
    TELEPORT_CHECK_TO_TOP = 4
} TeleportCheck;

extern s32 g_PlayerX;
extern s32 g_PlayerY;

// GetTeleportToOtherCastle
TeleportCheck func_060AF8E0(void) {
    if (PLAYER.step != Player_Stand || PLAYER.step_s != 1) {
        return TELEPORT_CHECK_NONE;
    }
    if (g_CurrentRoom.stageID == STAGE_TOP) {
        if (ABS((g_Tilemap.left << 8) + g_PlayerX - 8079) < 4 &&
            ABS((g_Tilemap.top << 8) + g_PlayerY - 2127) < 4) {
            return TELEPORT_CHECK_TO_RTOP;
        }
    }
    if (g_CurrentRoom.stageID == (STAGE_TOP | STAGE_INVERTEDCASTLE_FLAG)) {
        if (ABS((g_Tilemap.left << 8) + g_PlayerX - 8430) < 4 &&
            ABS((g_Tilemap.top << 8) + g_PlayerY - 14407) < 4) {
            return TELEPORT_CHECK_TO_TOP;
        }
    }
    return TELEPORT_CHECK_NONE;
}
s32 func_060AF9D4(void) {
    u32 pressed;
    s32 result;
    u32 i;

    pressed = g_pads->pressed;
    result = pressed & 0x0000F800u;
    for (i = 0; i < 8; i++) {
        if (g_Settings.buttonMask[i] & pressed) {
            result |= g_ButtonMask[i];
        }
    }
    return result;
}
// EntityAlucard
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60AFA20, func_060AFA20);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60B0310, func_060B0310);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60B0584, func_060B0584);
s32 func_060B9610(u16 arg0, s32 arg1);

void func_060B0638(s32 arg0, s32 arg1, s32 arg2) {
    if (g_Player.healKind != 0) {
        g_Status.hp += g_Player.healAmount;
        func_0606FFC8(arg0, arg1, arg2, 0x250);
        func_060B9610(g_Player.healAmount, 1);

        if (g_Player.healKind == 1) {
            PlaySfx(0x68E);
            if (!(g_Player.status & 0x80)) {
                func_060BAF44(g_CurrentEntity, 0x44002C, 0);
            }
        }

        if (g_Player.healKind == 2 && !(g_Player.status & 0x80)) {
            func_060BAF44(g_CurrentEntity, 0x48002C, 0);
        }

        if (g_Status.hpMax < g_Status.hp) {
            g_Status.hp = g_Status.hpMax;
        }
        g_Player.healKind = 0;
    }
}
void func_060B071C(void) {
    if (g_pads->previous & 0x80) {
        DAT_060CE4B0++;
    } else if (g_pads->previous & 0x08) {
        DAT_060CE4B0--;
    }
}
