/*
 * File: 1AC60.c
 * Overlay: RIC
 * Description: Overlay for the character Richter.
 */

#include "ric.h"
#include "player.h"

void DestroyEntity(Entity* entity) {
    s32 i;
    s32 length;
    u32* ptr;

    if (entity->flags & FLAG_HAS_PRIMS) {
        g_api.FreePrimitives(entity->primIndex);
    }

    ptr = (u32*)entity;
    length = sizeof(Entity) / sizeof(u32);
    for (i = 0; i < length; i++)
        *ptr++ = 0;
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
        xCheckTop = (g_Tilemap.left << 8) + playerX - 8000;
        if (ABS(xCheckTop) < 4) {
            yCheckTop = (g_Tilemap.top << 8) + playerY - 2127;
            if (ABS(yCheckTop) < 4) {
                return TELEPORT_CHECK_TO_RTOP;
            }
        }
    }

    // Check for X/Y boundaries in RTOP
    if (g_StageId == STAGE_RTOP) {
        xCheckRTop = (g_Tilemap.left << 8) + playerX - 8384;
        if (ABS(xCheckRTop) < 4) {
            yCheckRTop = (g_Tilemap.top << 8) + playerY;
            if (ABS(yCheckRTop) - 14407 < 4) {
                return TELEPORT_CHECK_TO_TOP;
            }
        }
    }

    return TELEPORT_CHECK_NONE;
}

s16 func_80156DE4(void) {
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

    for (i = 0; i < 3; i++) {
        yvar = PLAYER.posY.i.hi + D_80154568[i];
        g_api.CheckCollision(xpos, yvar, &collider, 0);
        collisions = 0;
        if ((collider.effects & coll_flags) == EFFECT_SOLID) {
            collisions += 1;
        }
        g_api.CheckCollision(xp4, yvar, &collider, 0);
        if ((collider.effects & coll_flags) == EFFECT_SOLID) {
            collisions += 1;
        }
        g_api.CheckCollision(xm4, yvar, &collider, 0);
        if ((collider.effects & coll_flags) == EFFECT_SOLID) {
            collisions += 1;
        }
        if (collisions != 0) {
            return i + 1;
        }
    }
    return 0;
}
// Duplicate of DRA func_80109594
void func_80156F40(s16 arg0) {
    Entity* e;
    s32 radius;
    s32 intensity;
    s32 primIndex;
    Primitive* prim;
    s32 i;
    s32 val;
    s32 memset_len;
    s32* memset_ptr;
    SpriteParts** spriteptr;
    Entity* playerPtr = &PLAYER;

    DestroyEntity(&PLAYER);
    PLAYER.posX.val = FIX(32);
    PLAYER.posY.val = FIX(32);
    PLAYER.animSet = ANIMSET_OVL(0x10);
    PLAYER.palette = 0x8120;
    PLAYER.rotX = PLAYER.rotY = 0x100;
    PLAYER.facingLeft = 0;
    PLAYER.rotPivotY = 0x18;
    PLAYER.zPriority = g_unkGraphicsStruct.g_zEntityCenter.S16.unk0;
    memset_len = sizeof(PlayerState) / sizeof(s32);
    memset_ptr = &g_Player;
    for (i = 0; i < memset_len; i++) {
        *memset_ptr++ = 0;
    }
    g_Player.unk04 = 1;
    g_Player.pl_vram_flag = 1;
    func_8015CD98(0);
    PLAYER.unk4C = D_80155480;
    g_Player.unk5C = arg0;
    if (g_StageId == STAGE_ST0) {
        D_80154570 = 1;
    } else {
        D_80154570 = 0;
    }
    D_80097D37 = 0;
    func_801587C0();
    for (i = 0; i < 0x20; i++) {
        radius = (rand() & 0x3FF) + 0x100;
        intensity = (rand() & 0xFF) + 0x100;
        val = rcos(radius) * 0x10;
        D_80175958[i] = +((val * intensity) >> 8);
        val = rsin(radius) * 0x10;
        D_801759D8[i] = -((val * intensity) >> 7);
    }
    spriteptr = g_api.o.spriteBanks;
    spriteptr += 0x10;
    *spriteptr++ = D_801530AC;
    *spriteptr++ = D_80153AA0;
    *spriteptr++ = D_80153D24;
    *spriteptr++ = D_801541A8;
    for (e = &g_Entities[1], i = 0; i < 3; i++, e++) {
        DestroyEntity(e);
        e->animSet = ANIMSET_OVL(0x10);
        e->unk5A = i + 1;
        e->palette = 0x8120;
        e->flags = FLAG_UNK_20000 | FLAG_UNK_08000000;
    }
    primIndex = g_api.AllocPrimitives(PRIM_TILE, 6);

    g_Entities[1].primIndex = primIndex;
    g_Entities[1].flags |= FLAG_HAS_PRIMS;
    for (prim = &g_PrimBuf[primIndex]; prim != NULL; prim = prim->next) {
        prim->blendMode = 0x102 | BLEND_VISIBLE;
    }
    if (D_80097C98 == 6) {
        CreateEntFactoryFromEntity(playerPtr, 0x1004D, 0);
        func_8015CC70(1);
    }
    if (D_80097C98 == 4) {
        CreateEntFactoryFromEntity(playerPtr, 0x3004D, 0);
        func_8015CC70(3);
    }
    if (D_80097C98 == 5) {
        CreateEntFactoryFromEntity(playerPtr, 0x5004D, 0);
        func_8015CC70(5);
    }
}

INCLUDE_ASM("asm/us/ric/nonmatchings/1AC60", func_801572A8);

INCLUDE_ASM("asm/us/ric/nonmatchings/1AC60", func_80157894);

// DECOMP_ME_WIP func_80157A50 https://decomp.me/scratch/hk5zb
// Almost matched, just a jump issue
INCLUDE_ASM("asm/us/ric/nonmatchings/1AC60", func_80157A50);

INCLUDE_ASM("asm/us/ric/nonmatchings/1AC60", UpdateEntityRichter);

void func_801587C0() { D_80175956 = 0; }

void func_801587D0(void) {
    D_80175956 = 1;
    D_80175950 = PLAYER.animCurFrame;
    D_80175952 = PLAYER.drawFlags;
    D_80175954 = PLAYER.palette;
}

void func_80158814(void) {
    D_80175956 = 0;
    PLAYER.unk44 = 0;
    PLAYER.animCurFrame = D_80175950;
    PLAYER.drawFlags = *(u8*)&D_80175952;
    PLAYER.palette = D_80175954;
}

bool func_8015885C(void) {
    if (D_80175956 == 0) {
        if (g_Player.padTapped & PAD_L2) {
            if (g_Player.D_80072EFC == 0) {
                func_801587D0();
                return true;
            }
        }
        return false;
    }

    if ((g_Player.D_80072EFC != 0) || (g_Player.padTapped & PAD_L2)) {
        func_80158814();
        return false;
    }

    if (g_Player.padPressed & PAD_CROSS) {
        if (g_Player.padPressed & PAD_RIGHT) {
            g_Entities->posX.val += FIX(16.0);
        }
        if (g_Player.padPressed & PAD_LEFT) {
            g_Entities->posX.val -= FIX(16.0);
        }
        if (g_Player.padPressed & PAD_UP) {
            PLAYER.posY.val -= FIX(16.0);
        }
        if (g_Player.padPressed & PAD_DOWN) {
            PLAYER.posY.val += FIX(16.0);
        }

    } else {
        if (g_Player.padTapped & PAD_RIGHT) {
            g_Entities->posX.val += FIX(16.0);
        }
        if (g_Player.padTapped & PAD_LEFT) {
            g_Entities->posX.val -= FIX(16.0);
        }
        if (g_Player.padTapped & PAD_UP) {
            PLAYER.posY.val -= FIX(16.0);
        }
        if (g_Player.padTapped & PAD_DOWN) {
            PLAYER.posY.val += FIX(16.0);
        }
    }

    if (g_Player.padTapped & PAD_CIRCLE) {
        PLAYER.animCurFrame--;
    }
    if (g_Player.padTapped & PAD_SQUARE) {
        PLAYER.animCurFrame++;
    }

    if (PLAYER.animCurFrame <= 0) {
        PLAYER.animCurFrame = 1;
    }
    if (PLAYER.animCurFrame < 212 == 0) {
        PLAYER.animCurFrame = 211;
    }
    FntPrint("charal:%02x\n", PLAYER.animCurFrame);
    return true;
}

void func_80158B04(s32 arg0) {
    s32 var_s0;

    if (PLAYER.facingLeft != 0) {
        var_s0 = -3;
    } else {
        var_s0 = 3;
    }

    PLAYER.posY.i.hi -= 16;
    PLAYER.posX.i.hi = var_s0 + PLAYER.posX.i.hi;
    CreateEntFactoryFromEntity(g_CurrentEntity, 0x10004, 0);
    PLAYER.posY.i.hi += 16;
    PLAYER.posX.i.hi = PLAYER.posX.i.hi - var_s0;

    if (arg0 & 1) {
        g_api.func_80102CD8(3);
        g_api.PlaySfx(NA_SE_SECRET_STAIRS);
    }

    if (arg0 & 2) {
        PLAYER.velocityX = 0;
        PLAYER.velocityY = 0;
    }
}

void func_80158BFC(void) {
    s32 var_s0;

    if (PLAYER.step < 64) {
        if (D_8015459C != 0) {
            D_8015459C--;
        } else if (D_80097448[0] >= 49) {
            if (PLAYER.facingLeft != 0) {
                var_s0 = -4;
            } else {
                var_s0 = 4;
            }
            PLAYER.posX.i.hi = var_s0 + PLAYER.posX.i.hi;
            PLAYER.posY.i.hi -= 16;
            CreateEntFactoryFromEntity(g_CurrentEntity, 0x80004, 0);
            D_8015459C = 0x60;
            PLAYER.posY.i.hi += 16;
            PLAYER.posX.i.hi = PLAYER.posX.i.hi - var_s0;
        }
    }

    if (func_8015DBB0(0x40000 | 0x305C) == false) {
        func_8015C93C(0x2000);
        switch (PLAYER.step_s) {
        case 0:
            if (func_8015C9CC() == 0) {
                if (g_Player.padPressed & PAD_UP) {
                    func_8015C920(&D_80155394);
                    PLAYER.step_s = 1;
                    break;
                }
            } else {
                func_8015CDE0(0);
            }
            break;

        case 1:
            if (func_8015C9CC() != 0) {
                func_8015CDE0(0);
                break;
            } else if (g_Player.padPressed & PAD_UP) {
                break;
            } else {
                func_8015CD98(0);
                break;
            }

        case 64:
            func_8015CB58(1, 1);
            if (PLAYER.animFrameIdx < 3) {
                func_8015C9CC();
                if (g_Player.padPressed & PAD_DOWN) {
                    PLAYER.step = 2;
                    PLAYER.unk4C = &D_801555A8;
                    break;
                }
            }

            if (PLAYER.animFrameDuration < 0) {
                if (g_Player.padPressed & PAD_SQUARE) {
                    g_Player.unk46 = 2;
                    PLAYER.step_s++;
                    func_8015C920(&D_80155730);
                    CreateEntFactoryFromEntity(g_CurrentEntity, 0x11, 0);
                    break;
                }
                g_Player.unk46 = 0;
                func_8015CD98(0);
            }
            break;

        case 65:
            func_8015CB58(1, 1);
            if (g_Player.padPressed & PAD_SQUARE) {
                break;
            }
            g_Player.unk46 = 0;
            func_8015CD98(0);
            break;

        case 66:
            func_8015CB58(1, 1);
            if (PLAYER.animFrameIdx < 3) {
                func_8015C9CC();
            }
            if (PLAYER.animFrameDuration < 0) {
                g_Player.unk46 = 0;
                func_8015CD98(0);
            }
        }
    }
}

void func_80158F38(void) {
    if (func_8015DBB0(0x305C) == 0) {
        func_8015C93C(0x2000);
        if (func_8015C9CC() == 0) {
            func_8015CD98(0);
            return;
        }

        if (PLAYER.step_s == 0) {
            SetSpeedX(0x14000);
        }
    }
}

void func_80158FA4(void) {
    if (g_Player.unk7A != 0) {
        func_8015CDE0(0);
        return;
    }
    g_Player.D_80072F10 = 8;
    g_Player.D_80072F02 = 8;

    if (!func_8015DBB0(0x305C)) {
        func_8015C93C(0x2000);
        if (func_8015C9CC() == 0) {
            func_8015CD98(0);
            if (g_Player.D_80072F16 == 0) {
                if (!(g_Player.pl_vram_flag & 0xC)) {
                    func_8015C920(&D_8015539C);
                    CreateEntFactoryFromEntity(g_CurrentEntity, 0x0, 0);
                }
            } else {
                PLAYER.velocityX = 0;
            }
        } else if (PLAYER.step_s == 0) {
            SetSpeedX(0x24000);
        }
    }
}

void func_801590A0(void) {
    if ((D_80154570 == 0) && (PLAYER.velocityY < FIX(-1)) &&
        !(g_Player.unk44 & 0x40) && !(g_Player.padPressed & PAD_CROSS)) {
        PLAYER.velocityY = FIX(-1);
    }
    if ((g_Player.pl_vram_flag & 2) && (PLAYER.velocityY < FIX(-1))) {
        PLAYER.velocityY = FIX(-0.25);
        g_Player.unk44 |= 0x20;
    }
    if (func_8015DBB0(0x11009)) {
        return;
    }
    switch (PLAYER.step_s) {
    // Need at least one fake case to make the switch match
    case 1:
        return;
    case 0:
        func_8015C93C(0x1000);
        if (func_8015C9CC()) {
            if (g_Player.unk44 & 0x10) {
                SetSpeedX(FIX(2.25));
            } else {
                SetSpeedX(FIX(1.25));
            }
            g_Player.unk44 &= ~4;
        } else {
            g_Player.unk44 &= ~0x10;
            if ((PLAYER.animFrameIdx < 2) &&
                ((LOW(g_Player.unk44) & 0xC) == 4) &&
                (g_Player.padTapped & PAD_CROSS)) {
                func_8015C920(D_8015555C);
                SetSpeedX(FIX(-1.5));
                PLAYER.velocityY = FIX(-2.625);
                if (g_Player.unk72 != 0) {
                    PLAYER.velocityY = 0;
                }
                PLAYER.step_s = 2;
                g_Player.unk44 |= 0xA;
                g_Player.unk44 &= ~4;
            }
        }
        return;
    case 0x40:
        func_8015CB58(1, 1);
        if (PLAYER.animFrameIdx < 3) {
            if (func_8015C9CC() != 0) {
                if (g_Player.unk44 & 0x10) {
                    SetSpeedX(FIX(2.25));
                } else {
                    SetSpeedX(FIX(1.25));
                }
                g_Player.unk44 &= ~4;
            } else {
                g_Player.unk44 &= ~0x10;
            }
        } else {
            if (((g_Player.padPressed & PAD_RIGHT) && !PLAYER.facingLeft) ||
                ((g_Player.padPressed & PAD_LEFT) && PLAYER.facingLeft)) {
                if (g_Player.unk44 & 0x10) {
                    SetSpeedX(FIX(2.25));
                } else {
                    SetSpeedX(FIX(1.25));
                }
                SetSpeedX(FIX(1.25));
                g_Player.unk44 &= ~4;
            } else {
                g_Player.unk44 &= ~0x10;
            }
        }
        if (PLAYER.animFrameDuration < 0) {
            if (g_Player.padPressed & PAD_SQUARE) {
                g_Player.unk46 = 2;
                PLAYER.step_s += 1;
                func_8015C920(D_80155740);
                CreateEntFactoryFromEntity(g_CurrentEntity, 0x11U, 0);
            } else {
                g_Player.unk46 = 0;
                PLAYER.step_s = 0;
                func_8015C920(D_80155528);
            }
        }
        return;
    case 0x41:
        func_8015CB58(1, 1);
        if (!(g_Player.padPressed & PAD_SQUARE)) {
            g_Player.unk46 = 0;
            PLAYER.step_s = 0;
            func_8015C920(D_80155528);
        }
        return;
    case 0x42:
        func_8015CB58(1, 1);
        if (PLAYER.animFrameIdx < 3) {
            if (func_8015C9CC() != 0) {
                if (g_Player.unk44 & 0x10) {
                    SetSpeedX(FIX(2.25));
                } else {
                    SetSpeedX(FIX(1.25));
                }
                g_Player.unk44 &= ~4;
            } else {
                g_Player.unk44 &= ~0x10;
            }
        } else {
            if (((g_Player.padPressed & PAD_RIGHT) && !PLAYER.facingLeft) ||
                ((g_Player.padPressed & PAD_LEFT) && PLAYER.facingLeft)) {
                if (g_Player.unk44 & 0x10) {
                    SetSpeedX(FIX(2.25));
                } else {
                    SetSpeedX(FIX(1.25));
                }
                SetSpeedX(FIX(1.25));
                g_Player.unk44 &= ~4;
            } else {
                g_Player.unk44 &= ~0x10;
            }
        }
        if (PLAYER.animFrameDuration < 0) {
            g_Player.unk46 = 0;
            PLAYER.step_s = 0;
            func_8015C920(D_80155528);
        }
    }
}

void func_801595D8(void) {
    if (func_8015DBB0(0x9009)) {
        return;
    }
    func_8015C93C(0x1000);
    if (PLAYER.step_s != 0) {
        return;
    }
    if (g_Player.D_80072F0A != 0 && g_Player.padTapped & PAD_CROSS) {
        func_8015D020();
    } else if (func_8015C9CC() != 0) {
        SetSpeedX(0xC000);
    }
}

INCLUDE_ASM("asm/us/ric/nonmatchings/1AC60", func_80159670);

void func_80159BC8(void) {
    PLAYER.animFrameDuration = 0;
    PLAYER.animFrameIdx = 0;
    g_Player.unk44 = 0;
    g_Player.unk46 = 0;
    PLAYER.drawFlags &= 0xFB;
}

void func_80159C04(void) {
    Entity* entity = PLAYER.ext.generic.unkB8.entityPtr;
    s16 temp_v0;
    s32 var_a0;
    s32 var_a2;

    if (entity->facingLeft != 0) {
        var_a2 = -entity->hitboxOffX;
    } else {
        var_a2 = entity->hitboxOffX;
    }

    if (PLAYER.facingLeft != 0) {
        var_a0 = -PLAYER.hitboxOffX;
    } else {
        var_a0 = PLAYER.hitboxOffX;
    }

    temp_v0 = var_a0 + PLAYER.posX.i.hi - entity->posX.i.hi - var_a2;

    if (ABS(temp_v0) < 16) {
        if (entity->velocityX != 0) {
            if (entity->velocityX < 0) {
                PLAYER.entityRoomIndex = 0;
                return;
            } else {
                PLAYER.entityRoomIndex = 1;
                return;
            }
        }
    }

    if (temp_v0 < 0) {
        PLAYER.entityRoomIndex = 0;
    } else {
        PLAYER.entityRoomIndex = 1;
    }
}

INCLUDE_ASM("asm/us/ric/nonmatchings/1AC60", func_80159CE4);

// DECOMP_ME_WIP func_8015A7D0 https://decomp.me/scratch/1JWA0
INCLUDE_ASM("asm/us/ric/nonmatchings/1AC60", func_8015A7D0);

INCLUDE_ASM("asm/us/ric/nonmatchings/1AC60", func_8015A9B0);

void func_8015AFE0(void) {
    if (PLAYER.step_s == 0) {
        PLAYER.velocityY += 0x3800;
        if (PLAYER.velocityY > 0) {
            PLAYER.velocityY = 0;
            PLAYER.step_s = 1;
        }
    } else if (g_Player.unk4E != 0) {
        g_Player.unk46 = 0;
        SetPlayerStep(4);
        func_8015C920(&D_80155528);
        g_Player.unk44 = 0;
    }
    if (g_Player.unk72 != 0) {
        PLAYER.velocityY = 0;
    }
}

void func_8015B098(void) {
    if ((PLAYER.animCurFrame == 0xB5) && (PLAYER.animFrameDuration == 1)) {
        CreateEntFactoryFromEntity(g_CurrentEntity, 0x23, 0);
        g_api.PlaySfx(NA_SE_UNK_62F);
    }

    if (PLAYER.animFrameDuration < 0) {
        func_8015CD98(0);
        g_Player.unk46 = 0;
        CreateEntFactoryFromEntity(g_CurrentEntity, 0x450021, 0);
        g_Player.D_80072F00 = 0x800;
    }

    if (!(g_Player.pl_vram_flag & 1)) {
        func_8015CF08();
        g_Player.unk46 = 0;
        CreateEntFactoryFromEntity(g_CurrentEntity, 0x450021, 0);
        g_Player.D_80072F00 = 0x800;
    }
}

void func_8015B18C(void) {
    if (PLAYER.animFrameDuration < 0) {
        func_8015CD98(0);
        g_Player.unk46 = 0;
    }

    if ((g_Player.pl_vram_flag & 1) == 0) {
        func_8015CF08();
        g_Player.unk46 = 0;
    }
}

void func_8015B1E8(void) {
    if (g_Player.unk4E) {
        func_8015CD98(0);
        g_Player.unk46 = 0;
    }

    if ((g_Player.pl_vram_flag & 1) == 0) {
        func_8015CF08();
        g_Player.unk46 = 0;
    }
}

void func_8015B244(void) {
    if (PLAYER.step_s == 0) {
        D_80174F74 = 0x200;
        PLAYER.step_s++;
    } else {
        func_8015C9CC();
        D_80174F74--;
        if (D_80174F74 == 0) {
            g_Player.unk46 = 0;
            func_8015CD98(0);
            g_Player.unk4E = 1;
        }
    }
    if (g_Player.padTapped & PAD_CROSS) {
        func_8015D020();
        g_Player.unk46 = 0;
        g_Player.unk4E = 1;
        D_80174F74 = 0;
    }
    if (!(g_Player.pl_vram_flag & 1)) {
        func_8015CF08();
        g_Player.unk46 = 0;
        g_Player.unk4E = 1;
        D_80174F74 = 0;
    }
}
