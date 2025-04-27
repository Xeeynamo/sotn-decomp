// SPDX-License-Identifier: AGPL-3.0-or-later
#include "maria.h"

#include "../destroy_entity.h"

typedef enum {
    TELEPORT_CHECK_NONE = 0,
    TELEPORT_CHECK_TO_RTOP = 2,
    TELEPORT_CHECK_TO_TOP = 4
} TeleportCheck;
static TeleportCheck GetTeleportToOtherCastle(void) {
    // Is player in the pose when pressing UP?
    if (PLAYER.step != PL_S_STAND || PLAYER.step_s != 1) {
        return TELEPORT_CHECK_NONE;
    }

    // Check for X/Y boundaries in TOP
    if (g_StageId == STAGE_TOP) {
        if (abs((g_Tilemap.left << 8) + g_PlayerX - 8000) < 4 &&
            abs((g_Tilemap.top << 8) + g_PlayerY - 2127) < 4) {
            return TELEPORT_CHECK_TO_RTOP;
        }
    }

    // Check for X/Y boundaries in RTOP
    if (g_StageId == STAGE_RTOP) {
        if (abs((g_Tilemap.left << 8) + g_PlayerX - 8384) < 4 &&
#if defined(VERSION_PSP)
            abs((g_Tilemap.top << 8) + g_PlayerY - 14407) < 4) {
#else
            abs((g_Tilemap.top << 8) + g_PlayerY) - 14407 < 4) {
#endif
            return TELEPORT_CHECK_TO_TOP;
        }
    }

    return TELEPORT_CHECK_NONE;
}

static s16 func_80156DE4(void) {
    // Variables that change during execution
    Collider collider;
    s32 yvar;
    s32 collisions;
    s32 i;
    s32 xCenter;
    s32 xRight;
    s32 xLeft;
    s32 filter;

    // Values that are set once and never again (but not const for some reason)
    filter = EFFECT_SOLID_FROM_ABOVE | EFFECT_SOLID;
    xCenter = PLAYER.posX.i.hi;
    xRight = PLAYER.posX.i.hi + 4;
    xLeft = PLAYER.posX.i.hi - 4;

    for (i = 0; i < 3; i++) {
        yvar = PLAYER.posY.i.hi + mar_80154568[i];
        collisions = 0;
        g_api.CheckCollision(xCenter, yvar, &collider, 0);
        if ((collider.effects & filter) == EFFECT_SOLID) {
            collisions += 1;
        }
        g_api.CheckCollision(xRight, yvar, &collider, 0);
        if ((collider.effects & filter) == EFFECT_SOLID) {
            collisions += 1;
        }
        g_api.CheckCollision(xLeft, yvar, &collider, 0);
        if ((collider.effects & filter) == EFFECT_SOLID) {
            collisions += 1;
        }
        if (collisions != 0) {
            return i + 1;
        }
    }
    return 0;
}

// Similar to of DRA func_80109594
extern s32 D_pspeu_092E5F20;
extern u8 hud_fr[];
extern u8 hud_sp[];
extern u8 hud_ge[];
extern u8 hud_it[];
extern LangImg g_FontImage;
extern LangImg g_HudImage;
void MarInit(s16 initParam) {
    Entity* e;
    s16 radius;
    s16 intensity;
    Primitive* prim;
    s32 i;
    SpriteParts** spriteptr;
    s32* memset_ptr;
    s32 memset_len;
#ifndef VERSION_PSP
    Entity* g_CurrentEntity;
#endif

    g_CurrentEntity = &PLAYER;
    DestroyEntity(g_CurrentEntity);
    PLAYER.posX.val = FIX(32);
    PLAYER.posY.val = FIX(32);
    PLAYER.animSet = ANIMSET_OVL(0x10);
    PLAYER.zPriority = g_unkGraphicsStruct.g_zEntityCenter;
    PLAYER.facingLeft = 0;
    PLAYER.palette = 0x8114;
    PLAYER.rotY = 0x100;
    PLAYER.rotX = 0x100;
    PLAYER.hitboxOffX = 0;
    PLAYER.hitboxOffY = 0;
    PLAYER.rotPivotY = 0x18;
    memset_len = sizeof(PlayerState) / sizeof(s32);
    memset_ptr = (s32*)&g_Player;
    for (i = 0; i < memset_len; i++) {
        *memset_ptr++ = 0;
    }
    g_Player.vram_flag = g_Player.unk04 = 1;
    MarSetStand(0);
    PLAYER.anim = mar_anim_stand_relax;
    g_PlayerDraw->enableColorBlend = 0;
    MarDebugOff();
    for (i = 0; i < LEN(mar_80175958); i++) {
        radius = (rand() & 0x3FF) + 0x100;
        intensity = (rand() & 0xFF) + 0x100;
        mar_80175958[i] = +(((rcos(radius) << 4) * intensity) >> 8);
        mar_801759D8[i] = -(((rsin(radius) << 4) * intensity) >> 7);
    }
    spriteptr = g_api.o.spriteBanks;
    spriteptr += 0x10;
    *spriteptr = (SpriteParts*)mar_801530AC;
    spriteptr++;
    *spriteptr = (SpriteParts*)D_pspeu_092C6A50;
    spriteptr++;
    *spriteptr = (SpriteParts*)D_pspeu_092C8CE0;
    spriteptr++;
    *spriteptr = (SpriteParts*)D_pspeu_092CC558;
    spriteptr++;
    *spriteptr = (SpriteParts*)D_pspeu_092CA590;
    spriteptr++;
    *spriteptr = (SpriteParts*)D_pspeu_092CDC48;
    spriteptr++;
    *spriteptr = (SpriteParts*)D_pspeu_092C7AA0;
    for (e = &g_Entities[1], i = 0; i < 3; i++, e++) {
        DestroyEntity(e);
        e->animSet = ANIMSET_OVL(0x10);
        e->unk5A = i + 1;
        e->palette = PAL_OVL(0x114);
        e->flags = FLAG_UNK_20000 | FLAG_POS_CAMERA_LOCKED;
    }
    g_Entities[1].primIndex = g_api.AllocPrimitives(PRIM_TILE, 6);
    g_Entities[1].flags |= FLAG_HAS_PRIMS;
    for (prim = &g_PrimBuf[g_Entities[1].primIndex], i = 0; prim != NULL; i++,
        prim = prim->next) {
        prim->drawMode = DRAW_UNK_100 | DRAW_UNK02 | DRAW_HIDE;
    }
    if (D_80097C98 == 6) {
        MarCreateEntFactoryFromEntity(
            g_CurrentEntity, FACTORY(BP_TELEPORT, 1), 0);
        MarSetInit(1);
    }
    if (D_80097C98 == 4) {
        MarCreateEntFactoryFromEntity(
            g_CurrentEntity, FACTORY(BP_TELEPORT, 3), 0);
        MarSetInit(3);
    }
    if (D_80097C98 == 5) {
        MarCreateEntFactoryFromEntity(
            g_CurrentEntity, FACTORY(BP_TELEPORT, 5), 0);
        MarSetInit(5);
    }
    func_pspeu_092C0040();
    func_pspeu_092C0248();
#ifdef VERSION_PSP
    // ifdef'fed for the same reason in RicInit
    D_pspeu_092E5F20 = 30;

    func_91040A0(&g_FontImage);
    g_HudImage.imgData = GetLang(NULL, hud_fr, hud_sp, hud_ge, hud_it);
    if (g_HudImage.imgData) {
        func_91040A0(&g_HudImage);
    }
#endif
    func_90E4C68();
}

INCLUDE_ASM("maria_psp/nonmatchings/pl_main", CheckStageCollision);

static void CheckBladeDashInput(void) {
    s32 pressed;
    s32 up;
    s32 down;
    s32 forward;
    s32 down_forward;

    pressed = g_Player.padPressed & (PAD_UP | PAD_RIGHT | PAD_DOWN | PAD_LEFT);
    if (PLAYER.facingLeft == 0) {
        down_forward = PAD_DOWN | PAD_RIGHT;
        forward = PAD_RIGHT;
    } else {
        down_forward = PAD_DOWN | PAD_LEFT;
        forward = PAD_LEFT;
    }
    up = PAD_UP;
    down = PAD_DOWN;

    switch (g_MarBladeDashButtons.buttonsCorrect) {
    case 0:
        if (g_Player.padTapped == up) {
            g_MarBladeDashButtons.timer = 20;
            g_MarBladeDashButtons.buttonsCorrect++;
        }
        break;
    case 1:
        if (pressed == down) {
            g_MarBladeDashButtons.timer = 20;
            g_MarBladeDashButtons.buttonsCorrect++;
            break;
        }
        if (--g_MarBladeDashButtons.timer == 0) {
            g_MarBladeDashButtons.buttonsCorrect = 0;
        }
        break;
    case 2:
        if (pressed == down_forward) {
            g_MarBladeDashButtons.timer = 20;
            g_MarBladeDashButtons.buttonsCorrect++;
            break;
        }
        if (--g_MarBladeDashButtons.timer == 0) {
            g_MarBladeDashButtons.buttonsCorrect = 0;
        }
        break;
    case 3:
        if (--g_MarBladeDashButtons.timer == 0) {
            g_MarBladeDashButtons.buttonsCorrect = 0;
        }
        if (PLAYER.step == PL_S_STAND || PLAYER.step == PL_S_WALK ||
            PLAYER.step == PL_S_CROUCH || PLAYER.step == PL_S_JUMP ||
            PLAYER.step == PL_S_FALL) {
            if (g_Player.unk72) {
                g_MarBladeDashButtons.buttonsCorrect = 0;
            } else if (!g_Player.unk46 && (g_Player.padTapped & PAD_SQUARE)) {
                MarSetBladeDash();
            }
        }
        break;
    }
}

INCLUDE_ASM("maria_psp/nonmatchings/pl_main", CheckHighJumpInput);

INCLUDE_ASM("maria_psp/nonmatchings/pl_main", MarMain);
