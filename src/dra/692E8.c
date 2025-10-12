// SPDX-License-Identifier: AGPL-3.0-or-later
#include "dra.h"
#include "dra_bss.h"
#include "sfx.h"

// data order is slightly different between US and HD
// maybe this suggests a file split

#if defined(VERSION_US)
s32 D_800ACDF8 = 0;
s32 D_800ACDFC = 0;
s32 D_800ACE00[] = {
    PAD_SQUARE, PAD_CIRCLE, PAD_CROSS, PAD_TRIANGLE,
    PAD_R2,     PAD_L1,     PAD_R1,    PAD_L2,
};
s16 D_800ACE20[] = {
    0xFFD0, 0xFFD0, 0xFFD1, 0xFFD8, 0xFFD7, 0xFFE2, 0xFFE1, 0xFFE2, 0xFFD7,
    0xFFD7, 0xFFCF, 0xFFCD, 0xFFCD, 0xFFD6, 0xFFD7, 0xFFE3, 0xFFE3, 0x0000,
};
s32 D_800ACE44 = 0;
s32 D_800ACE48[] = {
    0x0000, 0x0000, 0x8000, 0x801F, 0x01FF, 0x81FF,
};
RECT D_800ACE60 = {0x0200, 0x01C0, 0x003F, 0x003F};

// BSS
extern s32 D_80137FB4;
extern s32 D_80137FB8;
extern s32 D_80137FBC;

#elif defined(VERSION_HD)
s16 D_800ACE20[] = {
    0xFFD0, 0xFFD0, 0xFFD1, 0xFFD8, 0xFFD7, 0xFFE2, 0xFFE1, 0xFFE2, 0xFFD7,
    0xFFD7, 0xFFCF, 0xFFCD, 0xFFCD, 0xFFD6, 0xFFD7, 0xFFE3, 0xFFE3, 0x0000,
};
s32 D_800ACEDC_hd = 0;
s32 D_800ACE44 = 0;
s32 D_800ACE48[] = {
    0x0000, 0x0000, 0x8000, 0x801F, 0x01FF, 0x81FF,
};
RECT D_800ACE60 = {0x0200, 0x01C0, 0x003F, 0x003F};

s32 D_800ACDF8 = 0;
s32 D_800ACDFC = 0;

s32 D_800ACE00[] = {
    PAD_SQUARE, PAD_CIRCLE, PAD_CROSS, PAD_TRIANGLE,
    PAD_R2,     PAD_L1,     PAD_R1,    PAD_L2,
};

extern s32 D_80137FB4;
extern s32 D_80137FB8;

#elif defined(VERSION_PSP)

extern u8 D_psp_09148C10[];
extern u8 D_psp_091490B0[];
extern u8 D_psp_09149550[];
extern u8 D_psp_091499F0[];

s16 D_800ACE20[] = {
    0xFFD0, 0xFFD0, 0xFFD1, 0xFFD8, 0xFFD7, 0xFFE2, 0xFFE1, 0xFFE2, 0xFFD7,
    0xFFD7, 0xFFCF, 0xFFCD, 0xFFCD, 0xFFD6, 0xFFD7, 0xFFE3, 0xFFE3, 0x0000,
};
s32 D_800ACE48[] = {
    0x8000, 0x8000, 0x8000, 0x801F, 0x81FF, 0x81FF,
};
RECT D_800ACE60 = {0x0200, 0x01C0, 0x003F, 0x003F};

static u8 font_eu[] = {
#include "gen/font_eu.h"
};

static u8 D_psp_0917DCA8[] = {
#include "gen/D_psp_0917DCA8.h"
};

static u8 D_psp_0917ED60[] = {
#include "gen/D_psp_0917ED60.h"
};

static u8 D_psp_0917FF10[] = {
#include "gen/D_psp_0917FF10.h"
};

static u8 D_psp_09180EC0[] = {
#include "gen/D_psp_09180EC0.h"
};

static u8 D_psp_09182028[] = {
#include "gen/D_psp_09182028.h"
};

static u_long* g_FontImage[] = {
    (u_long*)GFX_BANK_COMPRESSED,
    GFX_ENTRY(0x100, 0x380, 128, 128, font_eu),
    GFX_TERMINATE(),
};

static u_long* D_psp_09183150[] = {
    (u_long*)GFX_BANK_COMPRESSED,
    GFX_ENTRY(0x100, 0x280, 128, 128, D_psp_0917DCA8),
    GFX_TERMINATE(),
};

static u_long* D_psp_09183168[] = {
    (u_long*)GFX_BANK_COMPRESSED,
    GFX_ENTRY(0x100, 0x3C0, 128, 32, D_psp_09148C10),
    GFX_TERMINATE(),
};

s32 D_800ACE00[] = {
    PAD_SQUARE, PAD_CIRCLE, PAD_CROSS,       PAD_TRIANGLE,
    PAD_L1,     PAD_R1,     PAD_L1 | PAD_R1, 0,
};

// BSS
s32 D_800ACEDC_hd = 0;
s32 D_800ACE44 = 0;
s32 D_800ACDF8 = 0;
s32 D_800ACDFC = 0;
static s32 D_psp_09234B88 = 0;
static s32 D_psp_09234B90 = 0;
extern s32 D_80137FB4;
extern s32 D_80137FB8;
#endif

#include "../get_lang.h"

void func_801092E8(s32 arg0) {
    D_800A37D8[0] = D_800ACE48[arg0 * 2];
    D_800A37D8[1] = D_800ACE48[arg0 * 2 + 1];
    g_Clut[1][10] = D_800ACE48[arg0 * 2];
}

void func_80109328(void) {
    g_Player.unk66 = 0;

    if (PLAYER.rotate == 0x800 && PLAYER.step == Player_HighJump) {
        PLAYER.rotate = 0;
        PLAYER.animCurFrame = 0x9D;
        PLAYER.facingLeft += 1;
        PLAYER.facingLeft &= 1;
    }

    if (g_Player.timers[ALU_T_DARKMETAMORPH]) {
        g_Player.timers[ALU_T_DARKMETAMORPH] = 0;
        func_801092E8(0);
    }
    PLAYER.drawMode = DRAW_DEFAULT;
}

void func_801093C4(void) {
    DR_ENV* dr_env;
    DRAWENV drawEnv;
    Primitive* prim;
    s32 i;

    prim = &g_PrimBuf[g_Entities[1].primIndex];
    for (i = 0; i < 6; i++) {
        prim = prim->next;
    }
    switch (g_Player.unk6A) {
    case 0:
        dr_env = func_800EDB08(prim);
        if (dr_env == NULL) {
            break;
        }
        prim->type = PRIM_ENV;
        prim->drawMode = DRAW_HIDE;
        prim = prim->next;
        dr_env = func_800EDB08(prim);
        if (prim == NULL) {
            break;
        }
        prim->type = PRIM_ENV;
        prim->drawMode = DRAW_HIDE;
        prim = prim->next;
        g_Player.unk6A++;
        break;
    case 1:
        drawEnv = g_CurrentBuffer->draw;
        drawEnv.isbg = false;
        if (g_Player.status & PLAYER_STATUS_UNK4000000) {
            drawEnv.isbg = true;
        }
        drawEnv.r0 = drawEnv.g0 = drawEnv.b0 = 0;
        drawEnv.ofs[0] = 0x200;
        drawEnv.clip = D_800ACE60;
        drawEnv.ofs[1] = 0x1C0;
        dr_env = *(DR_ENV**)&prim->r1;
#if defined(VERSION_PSP)
        if (dr_env == NULL) {
            return;
        }
#endif
        SetDrawEnv(dr_env, &drawEnv);
        prim->priority = 0x190;
        prim->drawMode = DRAW_DEFAULT;
        prim = prim->next;
        prim->priority = 0x1B0;
        prim->drawMode = DRAW_UNK_800;
    }
}

// Corresponding RIC function is RicInit
void AluInit() {
    Entity* e;
    Primitive* prim;
    s16 radius;
    s16 intensity;
    s32 i;
    s32 memset_len;
    s32* memset_ptr;
    s32 (*weapon)();

    g_Player.unk6A = 0;
    g_CurrentEntity = &PLAYER;
    DestroyEntity(g_CurrentEntity);
    PLAYER.posX.val = FIX(32);
    PLAYER.posY.val = FIX(32);
    PLAYER.animSet = ANIMSET_DRA(1);
    PLAYER.zPriority = (u16)g_unkGraphicsStruct.g_zEntityCenter;
    PLAYER.facingLeft = 0;
    PLAYER.palette = 0x8100;

    PLAYER.scaleY = PLAYER.scaleX = 0x100;

    memset_len = sizeof(PlayerState) / sizeof(s32);
    memset_ptr = (s32*)&g_Player;
    for (i = 0; i < memset_len; i++) {
        *memset_ptr++ = 0;
    }

    for (i = 0; i < LEN(g_ButtonCombo); i++) {
        g_ButtonCombo[i].buttonsCorrect = 0;
        g_ButtonCombo[i].timer = 0;
    }

    g_Player.vram_flag = g_Player.unk04 = 1;
    func_8010E570(0);

    for (e = &g_Entities[1], i = 0; i < 3; i++, e++) {
        DestroyEntity(e);
        e->animSet = ANIMSET_DRA(1);
        e->unk5A = i + 1;
        e->palette = PAL_OVL(0x100);
        e->flags = FLAG_UNK_20000 | FLAG_POS_CAMERA_LOCKED;
    }

    g_Entities[1].primIndex = AllocPrimitives(PRIM_TILE, 8);
    g_Entities[1].flags |= FLAG_HAS_PRIMS;
    prim = &g_PrimBuf[g_Entities[1].primIndex];
    for (i = 0; i < 6; i++) {
        prim->drawMode = DRAW_UNK_100 | DRAW_HIDE | DRAW_UNK02;
        prim = prim->next;
    }
    func_801093C4();

#if !defined(VERSION_HD)
    TRANSFORM_LOCKOUT_TIMER = 0x10;
    g_Player.padSim = 0;
    g_Player.demo_timer = 16;
#endif
    D_80137FB8 = 0;

#if defined(VERSION_US)
    D_80137FBC = 1;
#endif

    if (g_Status.mp != g_Status.mpMax) {
        D_80137FB4 = 0;
    } else {
        D_80137FB4 = 1;
    }
    g_PlayerDraw->enableColorBlend = 0;
    func_800EA5E4(0x16);
    func_801092E8(0);
    for (i = 0; i < LEN(D_801396F8); i++) {
        radius = (rand() & 0x3FF) + 0x100;
        intensity = (rand() & 0xFF) + 0x100;
        D_801396F8[i] = +(((rcos(radius) << 4) * intensity) >> 8);
        D_80139778[i] = -(((rsin(radius) << 4) * intensity) >> 7);
    }
    func_80111928();
    if (D_80097C98 == 6) {
        CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(BP_TELEPORT, 1), 0);
        func_8010E42C(1);
    }
    if (D_80097C98 == 4) {
        CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(BP_TELEPORT, 3), 0);
        func_8010E42C(3);
    }
    if (D_80097C98 == 5) {
        CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(BP_TELEPORT, 5), 0);
        func_8010E42C(5);
    }

    g_CurrentEntity = &PLAYER;
    weapon = (int (*)())D_8017A000.GetWeaponId;
    i = weapon();
    if (i == 0x2D) {
        if (CheckEquipmentItemCount(ITEM_AXE_LORD_ARMOR, EQUIP_ARMOR) != 0) {
            func_8010FAF4();
            weapon = (int (*)())D_8017A000.EntityWeaponAttack;
            weapon();
            g_Player.status |= PLAYER_STATUS_AXEARMOR;
            func_8010DFF0(1, 10);
            func_80109328();
        }
    }
#ifdef VERSION_PSP
    func_psp_091040A0(g_FontImage);
    D_psp_09183150[3] = GetLang(D_psp_0917DCA8, D_psp_09180EC0, D_psp_0917ED60,
                                D_psp_09182028, D_psp_0917FF10);
    func_psp_091040A0(D_psp_09183150);
    D_psp_09183168[3] = GetLang(
        NULL, D_psp_09149550, D_psp_09148C10, D_psp_091499F0, D_psp_091490B0);
    if (D_psp_09183168[3] != NULL) {
        func_psp_091040A0(D_psp_09183168);
    }
#endif
}

void func_80109990(void) {
    if (D_80137FB4 == 0) {
        if (g_Status.mp == g_Status.mpMax &&
            !(g_Player.status & PLAYER_STATUS_UNK100000)) {
            CreateEntFactoryFromEntity(g_CurrentEntity, BP_RIPPLE_OUTLINE, 0);
            PlaySfx(SFX_UI_MP_FULL);
            D_80137FB4++;
        }
    } else if (g_Status.mp != g_Status.mpMax) {
        D_80137FB4 = 0;
    }
}

void CheckFloor(void);
void CheckCeiling(void);
void CheckWallRight(void);
void CheckWallLeft(void);

static void CheckStageCollision(s32 isTransformed) {
    s32 i;
    s32 psp_s2;
    s32 status;
    s32 mist;
    s32* pl_vram;
    s32 speed;
    s32 psp_fp;

    Collider sp10;
    s32* pl_04;
    s16 x, y;

    mist = 0;
    if (g_Player.status & PLAYER_STATUS_MIST_FORM ||
        g_Entities[0x10].entityId == 0x22) {
        mist = mist + 1;
    }
    pl_vram = &g_Player.vram_flag;
    pl_04 = &g_Player.unk04;
    *pl_04 = *pl_vram;
    *pl_vram = 0;
    status = g_Player.status;
    if (isTransformed) {
        for (i = 0; i < NUM_HORIZONTAL_SENSORS; i++) {
            if (status & (PLAYER_STATUS_BAT_FORM | PLAYER_STATUS_MIST_FORM)) {
                g_SensorsFloor[i].y = g_SensorsFloorBat[i];
                g_SensorsCeiling[i].y = g_SensorsCeilingBat[i];
            } else if (
                status & (PLAYER_STATUS_WOLF_FORM | PLAYER_STATUS_CROUCH)) {
                g_SensorsFloor[i].y = g_SensorsFloorDefault[i];
                g_SensorsCeiling[i].y = g_SensorsCeilingCrouch[i];
            } else {
                g_SensorsFloor[i].y = g_SensorsFloorDefault[i];
                g_SensorsCeiling[i].y = g_SensorsCeilingDefault[i];
            }
        }
        for (i = 0; i < NUM_VERTICAL_SENSORS; i++) {
            if (status & (PLAYER_STATUS_BAT_FORM | PLAYER_STATUS_MIST_FORM)) {
                g_SensorsWall[i].y = g_SensorsWallBat[i];
                g_SensorsWall[i + NUM_VERTICAL_SENSORS].y = g_SensorsWallBat[i];
            } else if (
                status & (PLAYER_STATUS_WOLF_FORM | PLAYER_STATUS_CROUCH)) {
                g_SensorsWall[i].y = g_SensorsWallCrouch[i];
                g_SensorsWall[i + NUM_VERTICAL_SENSORS].y =
                    g_SensorsWallCrouch[i];
            } else {
                g_SensorsWall[i].y = g_SensorsWallDefault[i];
                g_SensorsWall[i + NUM_VERTICAL_SENSORS].y =
                    g_SensorsWallDefault[i];
            }
        }
    }
    speed = PLAYER.velocityX;
    psp_fp = *pl_04 & 0xF000;
    if (PLAYER.velocityX < 0 && !(*pl_04 & 8)) {
        if (psp_fp == 0xC000) {
            speed = speed * 10 / 16;
        }
        if (psp_fp == 0xD000) {
            speed = speed * 13 / 16;
        }
        PLAYER.posX.val += speed;
    }
    if (PLAYER.velocityX > 0 && !(*pl_04 & 4)) {
        if (psp_fp == 0x8000) {
            speed = speed * 10 / 16;
        }
        if (psp_fp == 0x9000) {
            speed = speed * 13 / 16;
        }
        PLAYER.posX.val += speed;
    }

    PLAYER.posY.val += PLAYER.velocityY;
    for (i = 0; i < NUM_HORIZONTAL_SENSORS; i++) {
        x = PLAYER.posX.i.hi + g_SensorsFloor[i].x;
        y = PLAYER.posY.i.hi + g_SensorsFloor[i].y;
        CheckCollision(x, y, &g_Player.colFloor[i], 0);
        if (g_Player.timers[7] &&
            g_Player.colFloor[i].effects & EFFECT_SOLID_FROM_ABOVE) {
            CheckCollision(x, y + 12, &sp10, 0);
            if (!(sp10.effects & EFFECT_SOLID)) {
                g_Player.colFloor[i].effects = EFFECT_NONE;
            }
        }
        if (mist && g_Player.colFloor[i].effects & EFFECT_MIST_ONLY) {
            g_Player.colFloor[i].effects = EFFECT_NONE;
        }
        if (PLAYER.step == Player_MorphBat || PLAYER.step == Player_MorphMist) {
            if (g_Player.colFloor[i].effects &
                (EFFECT_SOLID_FROM_ABOVE | EFFECT_SOLID_FROM_BELOW)) {
                g_Player.colFloor[i].effects = EFFECT_NONE;
            }
        }
    }
    CheckFloor();
    if (PLAYER.step == Player_UnmorphBat || PLAYER.step == Player_UnmorphMist ||
        PLAYER.step == Player_UnmorphWolf) {
        if (g_Player.colCeiling[1].effects & 1 &&
            !(g_Player.colCeiling[1].effects & EFFECT_SOLID_FROM_ABOVE) &&
            g_Player.colFloor[1].effects & 1 &&
            !(g_Player.colFloor[1].effects & EFFECT_SOLID_FROM_BELOW)) {
            g_Player.vram_flag = TOUCHING_CEILING | TOUCHING_GROUND;
            PLAYER.posX.val -= speed;
            return;
        }
    }

    for (i = 0; i < NUM_HORIZONTAL_SENSORS; i++) {
        x = PLAYER.posX.i.hi + g_SensorsCeiling[i].x;
        y = PLAYER.posY.i.hi + g_SensorsCeiling[i].y;
        CheckCollision(x, y, &g_Player.colCeiling[i], 0);
        if (mist && g_Player.colCeiling[i].effects & EFFECT_MIST_ONLY) {
            g_Player.colCeiling[i].effects = EFFECT_NONE;
        }
        if (PLAYER.step == Player_MorphBat || PLAYER.step == Player_MorphMist) {
            if (g_Player.colCeiling[i].effects &
                (EFFECT_SOLID_FROM_ABOVE | EFFECT_SOLID_FROM_BELOW)) {
                g_Player.colCeiling[i].effects = EFFECT_NONE;
            }
        }
    }
    CheckCeiling();
    if (*pl_vram & 1 && PLAYER.velocityY >= 0) {
        PLAYER.posY.i.lo = 0;
    }
    if (*pl_vram & 2 && PLAYER.velocityY <= 0) {
        PLAYER.posY.i.lo = 0;
    }

    for (i = 0; i < NUM_VERTICAL_SENSORS * 2; i++) {
        x = PLAYER.posX.i.hi + g_SensorsWall[i].x;
        y = PLAYER.posY.i.hi + g_SensorsWall[i].y;
        CheckCollision(x, y, &g_Player.colWall[i], 0);
        if (mist && g_Player.colWall[i].effects & EFFECT_MIST_ONLY) {
            g_Player.colWall[i].effects = EFFECT_NONE;
        }
    }
    CheckWallRight();
    CheckWallLeft();
    if (*pl_vram & 4 && PLAYER.velocityX > 0) {
        PLAYER.posX.i.lo = 0;
    }
    if (*pl_vram & 8 && PLAYER.velocityX < 0) {
        PLAYER.posX.i.lo = 0;
    }

    if (*pl_vram & 0x8000) {
        *pl_vram |= 0x20;
    }
    if (!(g_Player.colFloor[1].effects & EFFECT_SOLID) ||
        !(g_Player.colFloor[2].effects & EFFECT_SOLID) ||
        !(g_Player.colFloor[3].effects & EFFECT_SOLID)) {
        *pl_vram |= 0x20;
    }
}

void func_8010A234(s32 arg0) {
    s32 weaponID;
    s32 (*weapon)(void);
    s32 i;
    Entity* ent;

    g_CurrentEntity = &PLAYER;
    weapon = D_8017A000.GetWeaponId;
    weaponID = weapon();
    // Wearing Axe Lord Armor! This is probably when you initially put it on.
    if ((weaponID == 0x2D) &&
        CheckEquipmentItemCount(ITEM_AXE_LORD_ARMOR, EQUIP_ARMOR)) {
        // If we already have the flag set, exit.
        if (g_Player.status & PLAYER_STATUS_AXEARMOR) {
            return;
        }
        // Alucard says "WHAT?!" when first putting on Axe Lord Armor
        PlaySfx(SFX_VO_ALU_WHAT);
        g_Player.padSim = 0;
        g_Player.demo_timer = 32;
        func_8010FAF4();
        weapon = (int (*)())D_8017A000.EntityWeaponAttack;
        weapon();
        g_Player.status |= PLAYER_STATUS_AXEARMOR;
        func_8010DFF0(1, 0xA);
        func_80109328();
        if (arg0 == 0) {
            return;
        }
        PlayAnimation(D_800B0130, D_800B01B8);
        return;
    }
    // Detect opposite case: If we're not wearing it, but status is set
    // Means we need to run a routine to get back into normal mode.
    if (g_Player.status & PLAYER_STATUS_AXEARMOR) {
        PLAYER.palette = 0x8100;
        PLAYER.animSet = 1;
        PLAYER.unk5A = 0;
        PLAYER.rotate = 0;
        PLAYER.drawFlags &=
            (FLAG_DRAW_UNK10 | FLAG_DRAW_UNK20 | FLAG_DRAW_UNK40 | FLAG_BLINK |
             FLAG_DRAW_SCALEY | FLAG_DRAW_SCALEX);
        func_8010FAF4();
        PLAYER.rotPivotY = 0;
        PLAYER.rotPivotX = 0;
        if (g_Player.vram_flag & TOUCHING_GROUND) {
            func_8010E570(0);
        } else {
            func_8010E7AC();
        }
        g_Player.status &= ~PLAYER_STATUS_AXEARMOR;
        func_80111CC0();
        if (arg0 != 0) {
            PlayAnimation(D_800B0130, D_800B01B8);
        }
#if defined(VERSION_PSP)
        for (i = 0, ent = &g_Entities[0]; i < TOTAL_ENTITY_COUNT; i++, ent++) {
            if (ent->palette == 0x110 && ent->unk5A == 100) {
                ent->animSet = 0;
            }
        }
#endif
    }
}

void func_8010A3F0(void) {
    s32 (*getID)(void);
    s32 id;
    getID = D_8017A000.GetWeaponId;
    id = getID();
    if (id == 0x38) {
        getID = D_8017D000.GetWeaponId;
        id = getID();
        if (id == 0x38) {
            if (g_Player.timers[ALU_T_DARKMETAMORPH] == 0) {
                func_801092E8(1);
            }
            g_Player.timers[ALU_T_DARKMETAMORPH] = 0x20;
            if (g_Player.unk10 && g_Status.D_80097C40 < -1) {
                g_Status.D_80097C40++;
            }
        }
    }
    g_Player.unk10 = 0;
}

typedef enum {
    TELEPORT_CHECK_NONE = 0,
    TELEPORT_CHECK_TO_RTOP = 2,
    TELEPORT_CHECK_TO_TOP = 4
} TeleportCheck;
static TeleportCheck GetTeleportToOtherCastle(void) {
    // Is player in the pose when pressing UP?
    if (PLAYER.step != Player_Stand || PLAYER.step_s != Player_Stand_PressUp) {
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
#ifdef VERSION_HD
            (abs((g_Tilemap.top << 8) + g_PlayerY) - 14407) < 4) {
#else
            abs((g_Tilemap.top << 8) + g_PlayerY - 14407) < 4) {
#endif
            return TELEPORT_CHECK_TO_TOP;
        }
    }

    return TELEPORT_CHECK_NONE;
}

void EntityAlucard() {
#if defined(VERSION_PSP)
#define CHECK_SHOULDER(x) ((g_Player.padTapped & PAD_SHOULDERS) == x)
#else
#define CHECK_SHOULDER(x) (g_Player.padTapped & x)
#endif
    s32 vramFlag;
    s32 posX;
    s32 posY;
    DamageParam damage;
    s32 sp40 = 0;
    AluFrame* sp3c;
    s32 sp38;
    void (*weapon_func)();
    PlayerDraw* draw;

    s32 var_s8;
    s32 var_s7;
    s16 playerStep;
    s16 playerStepS;
    s16 angle;
    u32 newStatus;
    s32 i;
    s16 playerHitPoints;

    g_CurrentEntity = &PLAYER;
    if (D_800ACE44 != 0) {
        D_800ACE44--;
    }
    if (g_unkGraphicsStruct.D_800973FC != 0 && D_80137FB8 == 0) {
        CreateEntFactoryFromEntity(g_CurrentEntity, BP_120, 0);
    }
    D_80137FB8 = g_unkGraphicsStruct.D_800973FC;
    g_Player.unk4C = 0;

    var_s8 = 0;
    playerStep = 0;
    playerStepS = 0;
    var_s8 = 0;
    PLAYER.drawFlags = FLAG_DRAW_DEFAULT;
    g_Player.unk18 = 0;
    g_Player.unk70 = 0;

    g_Player.unk72 = func_80110394();
    if (!(g_Player.status & PLAYER_STATUS_DEAD)) {
        i = GetTeleportToOtherCastle();
        if (i != 0) {
            func_8010E42C(i);
        }
        if (PLAYER.step != Player_Teleport) {
            func_8010A234(0);
            func_8010A3F0();
            func_80109990();
            if (g_Player.unk56) {
                g_Status.hp += g_Player.unk58;
                func_800FE8F0();
                CreateHPNumMove(g_Player.unk58, 1);
                if (g_Player.unk56 == 1) {
                    PlaySfx(SFX_HEALTH_PICKUP);
                    if (!(g_Player.status & PLAYER_STATUS_STONE)) {
                        CreateEntFactoryFromEntity(
                            g_CurrentEntity, FACTORY(BP_BLINK_WHITE, 0x48), 0);
                        CreateEntFactoryFromEntity(
                            g_CurrentEntity, FACTORY(BP_BLINK_WHITE, 0x44), 0);
                    }
                }
                if ((g_Player.unk56 == 2) &&
                    !(g_Player.status & PLAYER_STATUS_STONE)) {
                    CreateEntFactoryFromEntity(
                        g_CurrentEntity, FACTORY(BP_BLINK_WHITE, 0x48), 0);
                }
                if (g_Status.hpMax < g_Status.hp) {
                    g_Status.hp = g_Status.hpMax;
                }
                g_Player.unk56 = 0;
            }
            i = CheckAndDoLevelUp();
            if (i != 0) {
                CreateEntFactoryFromEntity(
                    g_CurrentEntity, FACTORY(BP_25, i - 1), 0);
            }
            for (i = 0; i < 16; i++) {
                if (g_Player.timers[i]) {
                    switch (i) {
                    case 0:
                    case 1:
                    case 5:
                    case 6:
                    case 7:
                    case 8:
                    case 9:
                    case 10:
                    case 12:
                    case 13:
                    case 14:
                        break;
                    case 2:
                        PLAYER.palette = g_Player.unk40;
                        break;
                    case 3:
                        PLAYER.palette = g_Player.high_jump_timer;
                        g_Player.timers[15] = 12;
                        break;
                    case 4: {
                        angle = ((g_GameTimer & 0xF) * 256);
                        draw = g_PlayerDraw;
                        draw->r0 = draw->g0 = draw->b0 =
                            (rsin(angle) + 0x1000) / 64 + 0x60;
                        angle += 0x200;
                        draw->r1 = draw->g1 = draw->b1 =
                            (rsin(angle) + 0x1000) / 64 + 0x60;
                        angle += 0x200;
                        draw->r3 = draw->g3 = draw->b3 =
                            (rsin(angle) + 0x1000) / 64 + 0x60;
                        angle += 0x200;
                        draw->r2 = draw->g2 = draw->b2 =
                            (rsin(angle) + 0x1000) / 64 + 0x60;
                        draw->enableColorBlend = 1;
                        break;
                    }
                    case 15:
                        func_8010DFF0(0, 0);
                        break;
                    case 11:
                        if (D_800ACDF8 == 0) {
                            func_801092E8(1);
                        }
                        break;
                    }
                    if (--g_Player.timers[i] == 0) {
                        switch (i) {
                        case 5:
                        case 7:
                        case 8:
                        case 9:
                        case 10:
                        case 12:
                        case 14:
                            break;
                        case 0:
                            if (!(g_Player.status & (PLAYER_STATUS_STONE |
                                                     PLAYER_STATUS_CURSE))) {
                                g_Player.timers[4] = 0xC;
                                g_Player.timers[15] = 0xC;
                                func_8010E168(1, 0xC);
                            }
                            continue;
                        case 1:
                            if (!(g_Player.status & (PLAYER_STATUS_STONE |
                                                     PLAYER_STATUS_CURSE))) {
                                g_Player.timers[4] = 0xC;
                                g_Player.timers[15] = 0xC;
                                func_8010E168(1, 0xC);
                            }
                            continue;
                        case 2:
                            PLAYER.palette = 0x8100;
                            continue;
                        case 3:
                            PLAYER.palette = 0x8100;
                            if (!(g_Player.status &
                                  (PLAYER_STATUS_STONE | PLAYER_STATUS_POISON |
                                   PLAYER_STATUS_CURSE))) {
                                g_Player.timers[4] = 0xC;
                                g_Player.timers[15] = 0xC;
                                func_8010E168(1, 0xC);
                            }
                            continue;
                        case 4:
                            draw->enableColorBlend = 0;
                            continue;
                        case 6:
                            if ((PLAYER.step == 3) &&
                                (PLAYER.ext.player.anim != 0x1C)) {
                                SetPlayerAnim(0x1C);
                                g_Player.unk44 &= 0xFFEF;
                            }
                            continue;
                        case 13:
                            func_8010E168(1, 0x10);
                            continue;
                        case 15:
                            func_8010E0B8();
                            continue;
                        case 11:
                            func_801092E8(0);
                            continue;
                        }
                    }
                }
            }
            if (D_800ACDFC != 0) {
                D_800ACDFC--;
            }
            g_Player.padHeld = g_Player.padPressed;

#if defined(VERSION_PSP)
            if (g_Player.demo_timer != 0) {
                sp38 = 1;
            } else {
                sp38 = 0;
            }
            sp40 = sp38;
#endif

            if (g_Player.demo_timer != 0) {
                g_Player.demo_timer--;
#ifdef VERSION_US
                if (g_Player.demo_timer == 0) {
                    D_80137FBC = 1;
                }
#endif
                g_Player.padPressed = g_Player.padSim & 0xFFFF;
                switch (g_Player.padSim >> 0x10) {
                case 1:
                    if (PLAYER.step != Player_Unk48) {
                        func_8010E168(1, 4);
                        SetPlayerStep(Player_Unk48);
                        g_unkGraphicsStruct.pauseEnemies = 1;
                    }
                    break;
                case 2:
                    func_8010E168(1, 4);
                    if (g_Player.status & PLAYER_STATUS_AXEARMOR) {
                        SetPlayerStep(Player_Unk50);
                    } else {
                        SetPlayerStep(Player_Unk49);
                    }
                    g_unkGraphicsStruct.pauseEnemies = 1;
                    break;
                }
            } else {
                g_Player.padPressed =
                    g_pads[0].pressed & ~(PAD_SHOULDERS | PAD_SHAPES);
#if defined(VERSION_PSP)
#define TEST_BTN()                                                             \
    (g_Settings.buttonMask[i] == (g_pads[0].pressed & g_Settings.buttonMask[i]))
                for (i = 0; i < 6; i++) {
#else
#define TEST_BTN() (g_pads[0].pressed & g_Settings.buttonMask[i])
                for (i = 0; i < 8; i++) {
#endif
                    if (TEST_BTN()) {
                        g_Player.padPressed |= D_800ACE00[i];
                    }
                }
#ifdef VERSION_US
                if (D_80137FBC != 0) {
                    D_80137FBC = 0;
                    g_Player.padHeld = g_Player.padPressed;
                }
#endif
            }
            g_Player.padTapped =
                (g_Player.padHeld ^ g_Player.padPressed) & g_Player.padPressed;
            if (g_Player.status & PLAYER_STATUS_UNK8) {
                g_Player.padTapped &= ~(PAD_SQUARE | PAD_CIRCLE);
                g_Player.padPressed &= ~(PAD_SQUARE | PAD_CIRCLE);
            }
            if ((g_DebugPlayer != 0) && (func_801119C4() != 0)) {
#ifdef VERSION_US
                FntPrint("step:%04x\n", PLAYER.step);
                FntPrint("bat_i_step:%04x\n", g_Player.unk66);
#endif
                return;
            }
            if ((D_80097448[1] != 0) &&
                (IsRelicActive(RELIC_HOLY_SYMBOL) == 0) &&
                !(PLAYER.hitParams & 0x1F)) {
                PLAYER.hitParams = 6;
            }

// US uses a different ordering than HD/PSP
#if !defined(VERSION_US)
            if (g_Player.timers[13] | g_Player.timers[14]) {
                goto specialmove;
            }
#endif
            if (g_Player.unk60 < 2) {
                if (g_Player.unk60 == 1) {
                    playerStep = PLAYER.step;
                    playerStepS = PLAYER.step_s;
                    SetPlayerStep(Player_BossGrab);
                } else {
#if defined(VERSION_US)
                    if (!(g_Player.timers[13] | g_Player.timers[14])) {
#else
                    if (1) { // to make curly braces match
#endif
                        if (PLAYER.hitParams) {
                            playerStep = PLAYER.step;
                            playerStepS = PLAYER.step_s;
                            i = HandleDamage(
                                &damage, PLAYER.hitParams, PLAYER.hitPoints, 0);
#if defined(VERSION_PSP)
                            if (D_8C630C4) {
                                PLAYER.hitPoints = 0;
                                i = 0;
                            }
#endif
                            if ((g_Player.status & PLAYER_STATUS_AXEARMOR) &&
                                ((i == 1) || (i == 8) || (i == 7))) {
                                i = 3;
                                damage.damageKind = DAMAGEKIND_1;
                            }
                            switch (i) {
                            case 0:
                                CreateEntFactoryFromEntity(
                                    g_CurrentEntity, FACTORY(BP_47, 0), 0);
                                CreateEntFactoryFromEntity(
                                    g_CurrentEntity,
                                    FACTORY(BP_BLINK_WHITE, 0x43), 0);
                                CreateEntFactoryFromEntity(
                                    g_CurrentEntity,
                                    FACTORY(BP_BLINK_WHITE, 0x51), 0);
                                CreateHPNumMove(0, 0);
                                func_8010E168(1, 0xC);
                                break;
                            case 1:
                                g_Player.unk18 = damage.effects;
                                g_Player.high_jump_timer = 0x8166;
                                func_8010E168(1, 0xC);
                                g_Player.timers[3] = 6;
                                PlaySfx(SFX_VO_ALU_PAIN_A);
                                CreateHPNumMove(1, 0);
                                break;
                            case 2:
                                g_Player.unk18 = damage.effects;
                                CreateEntFactoryFromEntity(
                                    g_CurrentEntity, FACTORY(BP_115, 0), 0);
                                CreateEntFactoryFromEntity(
                                    g_CurrentEntity,
                                    FACTORY(BP_BLINK_WHITE, 0x58), 0);
                                g_Player.high_jump_timer = 0x8166;
                                func_8010E168(1, 0xC);
                                g_Player.timers[3] = 6;
                                break;
                            case 3:
                                g_Player.unk18 = damage.effects;
                                SetPlayerStep(Player_Hit);
                                CreateHPNumMove(damage.damageTaken, 0);
                                break;
                            case 4:
                                CreateHPNumMove(damage.damageTaken, 0);
                                SetPlayerStep(Player_Kill);
                                break;
                            case 5:
                                CreateEntFactoryFromEntity(
                                    g_CurrentEntity,
                                    FACTORY(BP_BLINK_WHITE, 0x44), 0);
                                CreateEntFactoryFromEntity(
                                    g_CurrentEntity,
                                    FACTORY(BP_BLINK_WHITE, 0x48), 0);
                                CreateHPNumMove(damage.unkC, 1);
                                func_8010E168(1, 0xC);
                                break;
                            case 6:
                                SetPlayerStep(Player_KillWater);
                                break;
                            case 7:
                                g_Player.unk18 = damage.effects;
                                SetPlayerStep(Player_StatusStone);
                                CreateHPNumMove(damage.damageTaken, 0);
                                break;
                            case 8:
                                g_Player.unk18 = damage.effects;
                                CreateHPNumMove(damage.damageTaken, 0);
                                var_s8 = 1;
                                break;
                            case 9:
                                CreateEntFactoryFromEntity(
                                    g_CurrentEntity,
                                    FACTORY(BP_BLINK_WHITE, 0x4E), 0);
                                if (D_800ACDFC == 0) {
                                    PlaySfx(SFX_VO_ALU_PAIN_E);
                                }
                                D_800ACDFC = 0x20;
                                if (damage.damageTaken != 0) {
                                    PlaySfx(SFX_WATER_DAMAGE_SWISHES);
                                }
                                break;
                            }
                        }
                    }
                specialmove:
                    CheckSpecialMoveInputs();
                    if (TRANSFORM_LOCKOUT_TIMER != 0) {
                        TRANSFORM_LOCKOUT_TIMER--;
                    }
                    if (TRANSFORM_LOCKOUT_TIMER == 0) {

#if defined(VERSION_PSP)
                        var_s7 = g_Player.padPressed;
                        if (sp40 != 0 || PLAYER.step == Player_MorphMist ||
                            PLAYER.step == Player_MorphWolf ||
                            PLAYER.step == Player_MorphBat) {
                            D_psp_09234B88 = 0;
                            D_psp_09234B90 = g_Player.padTapped;
                        } else {
                            if (var_s7 & 0x300) {
                                D_psp_09234B90 |= (var_s7 & 0x300);
                                D_psp_09234B88++;
                                if (D_psp_09234B88 <= 5) {
                                    g_Player.padTapped = var_s7 & ~0x300;
                                }
                                if (D_psp_09234B88 == 6) {
                                    g_Player.padTapped |= D_psp_09234B90;
                                }
                            } else {
                                if (D_psp_09234B88 != 0) {
                                    D_psp_09234B88 = 0;
                                    g_Player.padTapped = D_psp_09234B90;
                                } else {
                                    D_psp_09234B88 = 0;
                                    D_psp_09234B90 = 0;
                                }
                            }
                        }
#endif

                        if (D_80097448[1] == 0) {
                            if (CHECK_SHOULDER(BTN_MIST) &&
                                (HandleTransformationMP(
                                     FORM_MIST, CHECK_ONLY) == 0) &&
                                ((PLAYER.step == Player_Stand) ||
                                 (PLAYER.step == Player_Walk) ||
                                 (PLAYER.step == Player_Crouch) ||
                                 (PLAYER.step == Player_Fall) ||
                                 (PLAYER.step == Player_Jump) ||
                                 (PLAYER.step == Player_AlucardStuck) ||
                                 (PLAYER.step == Player_HighJump) ||
                                 ((PLAYER.step == Player_MorphBat) &&
                                  (PLAYER.step_s)) ||
                                 ((PLAYER.step == Player_MorphWolf) &&
                                  (PLAYER.step_s) && (PLAYER.step_s != 8)))) {
                                func_80109328();
                                SetPlayerStep(Player_MorphMist);
                                PlaySfx(SFX_TRANSFORM_LOW);
                                goto block_159;
                            }
                            if (CHECK_SHOULDER(PAD_R1) &&
                                (HandleTransformationMP(FORM_BAT, CHECK_ONLY) ==
                                 0) &&
                                ((PLAYER.step == Player_Stand) ||
                                 (PLAYER.step == Player_Walk) ||
                                 (PLAYER.step == Player_Crouch) ||
                                 (PLAYER.step == Player_Fall) ||
                                 (PLAYER.step == Player_Jump) ||
                                 (PLAYER.step == Player_AlucardStuck) ||
                                 (PLAYER.step == Player_HighJump) ||
                                 (PLAYER.step == Player_MorphMist) ||
                                 ((PLAYER.step == Player_MorphWolf) &&
                                  (PLAYER.step_s) && (PLAYER.step_s != 8)))) {
                                if (PLAYER.step == 6 || PLAYER.step == 2) {
                                    D_8013AECC = 0xC;
                                }
                                func_80109328();
                                SetPlayerStep(Player_MorphBat);
                                PlaySfx(SFX_TRANSFORM_LOW);
                                goto block_160;
                            }
                        }
                        if (CHECK_SHOULDER(BTN_WOLF) &&
                            (HandleTransformationMP(FORM_WOLF, CHECK_ONLY) ==
                             0) &&
                            ((D_80097448[1] == 0) ||
                             IsRelicActive(RELIC_HOLY_SYMBOL)) &&
                            ((PLAYER.step == Player_Stand) ||
                             (PLAYER.step == Player_Walk) ||
                             (PLAYER.step == Player_Crouch) ||
                             (PLAYER.step == Player_Fall) ||
                             (PLAYER.step == Player_Jump) ||
                             (PLAYER.step == Player_AlucardStuck) ||
                             (PLAYER.step == Player_HighJump) ||
                             (PLAYER.step == Player_MorphMist) ||
                             ((PLAYER.step == Player_MorphBat) &&
                              (PLAYER.step_s)))) {
                            func_80109328();
                            SetPlayerStep(Player_MorphWolf);
                            PlaySfx(SFX_TRANSFORM);
                        }
                    }
                }
            }
        }
    }
block_159:
block_160:
    g_Player.prev_step = PLAYER.step;
    g_Player.prev_step_s = PLAYER.step_s;
    D_800ACDF8 = g_Player.timers[ALU_T_DARKMETAMORPH];
    switch (PLAYER.step) {
    case Player_Stand:
        PlayerStepStand();
        break;
    case Player_Walk:
        PlayerStepWalk();
        break;
    case Player_Crouch:
        PlayerStepCrouch();
        break;
    case Player_Fall:
        PlayerStepFall();
        break;
    case Player_Jump:
        PlayerStepJump();
        break;
    case Player_MorphBat:
        ControlBatForm();
        break;
    case Player_UnmorphBat:
        PlayerStepUnmorphBat();
        break;
    case Player_MorphMist:
        ControlMistForm();
        break;
    case Player_UnmorphMist:
        PlayerStepUnmorphMist();
        break;
    case Player_MorphWolf:
        PlayerStepMorphWolf();
        break;
    case Player_UnmorphWolf:
        PlayerStepUnmorphWolf();
        break;
    case Player_HighJump:
        PlayerStepHighJump();
        break;
    case Player_SwordWarp:
        PlayerStepSwordWarp();
        break;
    case Player_Hit:
        AlucardHandleDamage(&damage, playerStep, playerStepS);
        break;
    case Player_StatusStone:
        PlayerStepStoned(var_s8);
        break;
    case Player_BossGrab:
        PlayerStepBossGrab();
        break;
    case Player_Kill:
        PlayerStepKill(&damage, playerStep, playerStepS);
        break;
    case Player_Unk17:
        PlayerStepUnk17();
        break;
    case Player_Teleport:
        PlayerStepTeleport();
        break;
    case Player_SpellDarkMetamorphosis:
        PlayerStepDarkMetamorphosis();
        break;
    case Player_SpellSummonSpirit:
        PlayerStepSummonSpells();
        break;
    case Player_SpellHellfire:
        PlayerStepHellfire();
        break;
    case Player_SpellTetraSpirit:
        PlayerStepSummonSpells();
        break;
    case Player_SpellSoulSteal:
        PlayerStepSoulSteal();
        break;
    case Player_SpellSwordBrothers:
        PlayerStepSummonSpells();
        break;
    case Player_Unk48:
        PlayerStepUnk48();
        break;
    case Player_Unk49:
        PlayerStepUnk49();
        break;
    case Player_Unk50:
        PlayerStepUnk50();
        break;
    case Player_KillWater:
        PlayerStepKillWater();
        break;
    case Player_AlucardStuck:
        PlayerStepStuck();
        break;
    case Player_AxearmorStand:
        weapon_func = D_8017A000.func_ptr_80170004;
        weapon_func();
        break;
    case Player_AxearmorWalk:
        weapon_func = D_8017A000.func_ptr_80170008;
        weapon_func();
        break;
    case Player_AxearmorJump:
        weapon_func = D_8017A000.func_ptr_8017000C;
        weapon_func();
        break;
    case Player_AxearmorHit:
        weapon_func = D_8017A000.func_ptr_80170010;
        weapon_func();
    }
    g_unkGraphicsStruct.unk1C &= ~2;
    g_Player.status &= ~PLAYER_STATUS_UNK8;
    g_Player.unk08 = g_Player.status;
    newStatus = 0;
    g_Status.D_80097BF8 &= ~1;
    switch (PLAYER.step) {
    case Player_Crouch:
        if (PLAYER.step_s != 2) {
            newStatus = PLAYER_STATUS_CROUCH;
        }
        newStatus |= PLAYER_STATUS_UNK10000000;
        break;
    case Player_Walk:
        newStatus = PLAYER_STATUS_UNK4000000;
        // fallthrough
    case Player_Stand:
        newStatus |= PLAYER_STATUS_UNK10000000;
        if (PLAYER.step_s == 4) {
            newStatus |= NO_AFTERIMAGE | PLAYER_STATUS_UNK100000;
        }
        break;
    case Player_Fall:
    case Player_Jump:
        newStatus = PLAYER_STATUS_UNK10000000 | PLAYER_STATUS_UNK2000;
        break;
    case Player_MorphBat:
        if (PLAYER.step_s == 3) {
            func_8010E168(1, 4);
            g_unkGraphicsStruct.unk1C |= 2;
        }
        newStatus = PLAYER_STATUS_UNK20000000 | NO_AFTERIMAGE |
                    PLAYER_STATUS_UNK100000 | PLAYER_STATUS_BAT_FORM;
        break;
    case Player_MorphMist:
        func_8010E168(1, 4);
        newStatus = PLAYER_STATUS_UNK20000000 | NO_AFTERIMAGE |
                    PLAYER_STATUS_UNK100000 | PLAYER_STATUS_MIST_FORM;
        PLAYER.palette = PAL_OVL(0x10D);
        break;
    case Player_UnmorphMist:
        newStatus = PLAYER_STATUS_UNK20000000 | NO_AFTERIMAGE |
                    PLAYER_STATUS_UNK100000 | PLAYER_STATUS_UNK800000 |
                    PLAYER_STATUS_MIST_FORM;
        PLAYER.palette = PAL_OVL(0x10D);
        func_8010E168(1, 4);
        break;
    case Player_AlucardStuck:
        func_8010E168(1, 4);
        newStatus = PLAYER_STATUS_UNK10000000 | NO_AFTERIMAGE |
                    PLAYER_STATUS_UNK100000 | PLAYER_STATUS_CROUCH |
                    PLAYER_STATUS_UNK10;
        break;
    case Player_UnmorphBat:
        newStatus = PLAYER_STATUS_UNK20000000 | NO_AFTERIMAGE |
                    PLAYER_STATUS_UNK100000 | PLAYER_STATUS_UNK400000 |
                    PLAYER_STATUS_BAT_FORM;
        if (PLAYER.step_s == 0) {
            PLAYER.animSet = 0xD;
            PLAYER.unk5A = 0;
        }
        func_8010E168(1, 4);
        break;
    case Player_HighJump:
        func_8010E168(1, 4);
        newStatus = PLAYER_STATUS_UNK20000000 | PLAYER_STATUS_UNK10000000 |
                    NO_AFTERIMAGE;
        break;
    case Player_Hit:
    case Player_Unk48:
    case Player_Unk49:
        newStatus =
            PLAYER_STATUS_UNK20000000 | PLAYER_STATUS_UNK10000000 |
            NO_AFTERIMAGE | PLAYER_STATUS_UNK100000 | PLAYER_STATUS_UNK10000;
        func_8010E168(1, 12);
        break;
    case Player_StatusStone:
        newStatus = PLAYER_STATUS_UNK20000000 | PLAYER_STATUS_UNK10000000 |
                    NO_AFTERIMAGE | PLAYER_STATUS_UNK100000 |
                    PLAYER_STATUS_UNK10000 | PLAYER_STATUS_STONE;
        break;
    case Player_BossGrab:
        newStatus = PLAYER_STATUS_UNK20000000 | PLAYER_STATUS_UNK10000000 |
                    NO_AFTERIMAGE | PLAYER_STATUS_UNK100000 |
                    PLAYER_STATUS_UNK10000 | PLAYER_STATUS_UNK40;
        func_8010E168(1, 12);
        break;
    case Player_Kill:
    case Player_KillWater:
        newStatus = PLAYER_STATUS_UNK10000000 | NO_AFTERIMAGE |
                    PLAYER_STATUS_UNK100000 | PLAYER_STATUS_DEAD |
                    PLAYER_STATUS_UNK10000;
        if (PLAYER.step_s == 0x80) {
            newStatus |= PLAYER_STATUS_UNK80000;
        }
        func_8010E168(1, 12);
        break;
    case Player_Unk17:
        newStatus = PLAYER_STATUS_UNK10000000 | NO_AFTERIMAGE |
                    PLAYER_STATUS_UNK100000 | PLAYER_STATUS_DEAD |
                    PLAYER_STATUS_UNK10000;
        func_8010E168(1, 12);
        break;
    case Player_Teleport:
        newStatus =
            PLAYER_STATUS_UNK10000000 | NO_AFTERIMAGE | PLAYER_STATUS_UNK100000;
        func_8010E168(1, 12);
        break;
    case Player_SpellSummonSpirit:
    case Player_SpellTetraSpirit:
    case Player_SpellSwordBrothers:
        func_8010E168(1, 0x10);
        newStatus = PLAYER_STATUS_UNK20000000 | PLAYER_STATUS_UNK10000000 |
                    NO_AFTERIMAGE | PLAYER_STATUS_CROUCH | PLAYER_STATUS_UNK200;
        break;
    case Player_SpellSoulSteal:
    case Player_SpellHellfire:
    case Player_SpellDarkMetamorphosis:
        func_8010E168(1, 0x10);
        newStatus = PLAYER_STATUS_UNK20000000 | PLAYER_STATUS_UNK10000000 |
                    NO_AFTERIMAGE | PLAYER_STATUS_UNK200;
        break;
    case Player_AxearmorHit:
        func_8010E168(1, 0x14);
        // fallthrough
    case Player_AxearmorStand:
    case Player_AxearmorWalk:
    case Player_AxearmorJump:
    case Player_Unk50:
        newStatus = PLAYER_STATUS_AXEARMOR | PLAYER_STATUS_UNK20000000 |
                    NO_AFTERIMAGE | PLAYER_STATUS_UNK100000;
        PLAYER.unk5A = 0x64;
        break;
    case Player_SwordWarp:
        newStatus =
            PLAYER_STATUS_UNK10000000 | NO_AFTERIMAGE | PLAYER_STATUS_UNK100000;
        func_8010E168(4, 0xC);
        PLAYER.palette = PAL_OVL(0x10D);
        break;
    case Player_MorphWolf:
        g_unkGraphicsStruct.unk1C |= 2;
        if (abs(PLAYER.velocityX) > FIX(3)) {
            func_8010E168(1, 4);
        }
        newStatus = PLAYER_STATUS_UNK20000000 | NO_AFTERIMAGE |
                    PLAYER_STATUS_UNK4000000 | PLAYER_STATUS_UNK100000 |
                    PLAYER_STATUS_WOLF_FORM | PLAYER_STATUS_UNK200;
        if ((PLAYER.step_s == 0) || (PLAYER.step_s == 8)) {
            newStatus |= PLAYER_STATUS_UNK40000000;
        }
        if (PLAYER.step_s == 3) {
            newStatus |= PLAYER_STATUS_CROUCH;
        }
        break;
    case Player_UnmorphWolf:
        newStatus = PLAYER_STATUS_UNK40000000 | PLAYER_STATUS_UNK20000000 |
                    NO_AFTERIMAGE | PLAYER_STATUS_UNK100000;
        func_8010E168(1, 4);
        break;
    }
    if (g_Player.timers[9]) {
        newStatus |= PLAYER_STATUS_UNK400;
    }
    if (g_Player.timers[10]) {
        newStatus |= PLAYER_STATUS_UNK800;
    }
    if (g_Player.timers[12]) {
        newStatus |= PLAYER_STATUS_UNK1000;
    }
    if (g_Player.timers[0]) {
        newStatus |= PLAYER_STATUS_UNK20000000 | NO_AFTERIMAGE |
                     PLAYER_STATUS_UNK100000 | PLAYER_STATUS_POISON;
    }
    if (g_Player.timers[1]) {
        newStatus |= PLAYER_STATUS_UNK20000000 | NO_AFTERIMAGE |
                     PLAYER_STATUS_UNK100000 | PLAYER_STATUS_CURSE;
    }
    if (*D_80097448 != 0) {
        newStatus |= NO_AFTERIMAGE | PLAYER_STATUS_UNK20000;
    }
    if (g_Player.timers[ALU_T_DARKMETAMORPH]) {
        newStatus |= PLAYER_STATUS_ABSORB_BLOOD;
    }
    g_Player.status = newStatus;
    if ((newStatus & NO_AFTERIMAGE) || g_unkGraphicsStruct.D_800973FC != 0) {
        func_8010DFF0(1, 1);
    }
    if (newStatus & PLAYER_STATUS_UNK10000000) {
        PLAYER.animSet = 1;
        PLAYER.unk5A = 0;
    }
    if (newStatus & PLAYER_STATUS_UNK20000000) {
        g_Status.D_80097BF8 |= 1;
    }
    if (g_Player.timers[13] | g_Player.timers[14]) {
        g_Player.status |= PLAYER_STATUS_UNK100;
    }
    if ((g_Player.unk08 & PLAYER_STATUS_UNK10000) &&
        !(g_Player.status & (PLAYER_STATUS_UNK10000 | PLAYER_STATUS_DEAD))) {
        func_8010E168(1, 0xC);
        if (!(g_Player.status & (PLAYER_STATUS_POISON | PLAYER_STATUS_CURSE))) {
            g_Player.timers[4] = 0xC;
            g_Player.timers[15] = 4;
            PLAYER.palette = PAL_OVL(0x100);
        }
    }
    PlayAnimation(D_800B0130, D_800B01B8);
    if (g_Player.status & PLAYER_STATUS_DEAD) {
        if (PLAYER.poseTimer < 0) {
            PLAYER.animCurFrame |= ANIM_FRAME_LOAD;
        }
        PLAYER.hitboxState = PLAYER.hitParams = 0;
    } else {
        PLAYER.hitboxState = 1;
        PLAYER.hitParams = 0;
        PLAYER.hitPoints = 0;
    }
    g_Player.unk14 = 0;
    g_Player.unk7A = 0;
    func_801093C4();
    if (!(g_Player.status & (PLAYER_STATUS_UNK10 | PLAYER_STATUS_UNK40))) {
        if ((CheckEquipmentItemCount(ITEM_SECRET_BOOTS, EQUIP_ACCESSORY) !=
             0) &&
            !(g_Player.status & (PLAYER_STATUS_TRANSFORM | PLAYER_STATUS_UNK10 |
                                 PLAYER_STATUS_UNK10000 | PLAYER_STATUS_DEAD |
                                 PLAYER_STATUS_AXEARMOR)) &&
            !(PLAYER.drawFlags & (FLAG_DRAW_SCALEY | FLAG_DRAW_ROTATE))) {
            PLAYER.drawFlags |= FLAG_DRAW_SCALEY;
            PLAYER.scaleY = 0x110;
            PLAYER.rotPivotY = 0x18;
        }
        func_8010D59C();
        if ((*D_80097448 >= 0x29 ||
             ((g_Player.status & PLAYER_STATUS_WOLF_FORM) &&
              *D_80097448 > 0xC)) &&
            (!g_CurrentEntity->nFramesInvincibility)) {
            PLAYER.velocityY = PLAYER.velocityY * 3 / 4;
            PLAYER.velocityX = PLAYER.velocityX * 3 / 4;
        }
        posX = PLAYER.posX.val;
        posY = PLAYER.posY.val;
        vramFlag = g_Player.vram_flag;
        if (!(g_Player.status &
              (PLAYER_STATUS_BAT_FORM | PLAYER_STATUS_WOLF_FORM |
               PLAYER_STATUS_UNK400000 | PLAYER_STATUS_UNK40000000))) {
            if ((abs(PLAYER.velocityX) >= FIX(2)) || (PLAYER.step == 8)) {
                goto block_293;
            } else {
                goto oddblock;
            }
        } else {
        block_293:
            PLAYER.velocityX = PLAYER.velocityX >> 3;
            PLAYER.velocityY = PLAYER.velocityY >> 3;
            if (PLAYER.posY.i.hi >= 0) {
                if (g_Player.status &
                    (PLAYER_STATUS_UNK400000 | PLAYER_STATUS_UNK40000000)) {
                    CheckStageCollision(0);
                } else {
                    CheckStageCollision(1);
                }
            }
            for (i = 0; i < 7; i++) {
                if (PLAYER.posY.i.hi >= 0) {
                    CheckStageCollision(0);
                }
            }
            if (PLAYER.posY.i.hi < 0) {
                PLAYER.posY.val = FIX(-1);
            }
            PLAYER.velocityX *= 8;
            PLAYER.velocityY *= 8;
            goto post_oddblock;
        oddblock:
            if (g_Player.status & PLAYER_STATUS_UNK800000) {
                CheckStageCollision(0);
            } else {
                CheckStageCollision(1);
            }
        }
    post_oddblock:
        g_Player.unk04 = vramFlag;
        if (((*D_80097448 >= 0x29) ||
             ((g_Player.status & PLAYER_STATUS_WOLF_FORM) &&
              (*D_80097448 > 0xC))) &&
            (!g_CurrentEntity->nFramesInvincibility)) {
            PLAYER.velocityY = PLAYER.velocityY * 4 / 3;
            PLAYER.velocityX = PLAYER.velocityX * 4 / 3;
        }
        g_CurrentEntity->nFramesInvincibility = 0;
        func_8010D800();
        if (PLAYER.animSet == 0xD) {
            sp3c = (AluFrame*)D_800CFE48[PLAYER.animCurFrame & 0x7FFF];
            sp3c->pivotY = D_8013AECC + D_800ACE20[PLAYER.animCurFrame];
        }
#ifdef VERSION_US
        FntPrint("step:%04x\n", PLAYER.step);
        FntPrint("bat_i_step:%04x\n", g_Player.unk66);
#endif
    }
}
