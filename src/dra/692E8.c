// SPDX-License-Identifier: AGPL-3.0-or-later
#include "dra.h"
#include "dra_bss.h"
#include "sfx.h"
#include "player.h"

// data order is slightly different between US and HD
// maybe this suggests a file split

#if defined(VERSION_US)
s32 D_800ACDF8 = 0;
s32 D_800ACDFC = 0;
s32 D_800ACE00[] = {
    PAD_SQUARE, PAD_CIRCLE, PAD_CROSS, PAD_TRIANGLE,
    PAD_R2,     PAD_L1,     PAD_R1,    PAD_L2,
};

u16 D_800ACE20[] = {
    0xFFD0, 0xFFD0, 0xFFD1, 0xFFD8, 0xFFD7, 0xFFE2, 0xFFE1, 0xFFE2, 0xFFD7,
    0xFFD7, 0xFFCF, 0xFFCD, 0xFFCD, 0xFFD6, 0xFFD7, 0xFFE3, 0xFFE3, 0x0000,
};

s32 D_800ACE44 = 0;

s32 D_800ACE48[] = {
    0x0000, 0x0000, 0x8000, 0x801F, 0x01FF, 0x81FF,
};

RECT D_800ACE60 = {0x0200, 0x01C0, 0x003F, 0x003F};

#elif defined(VERSION_HD)
u16 D_800ACE20[] = {
    0xFFD0, 0xFFD0, 0xFFD1, 0xFFD8, 0xFFD7, 0xFFE2, 0xFFE1, 0xFFE2, 0xFFD7,
    0xFFD7, 0xFFCF, 0xFFCD, 0xFFCD, 0xFFD6, 0xFFD7, 0xFFE3, 0xFFE3, 0x0000,
};

#if defined(VERSION_HD)
s32 D_800ACEDC_hd = 0;
#endif

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

#endif

// Bat sensors are also use by the Mist form
// Crouch sensors are also used by the Wolf form
// Default sensors are a copy of Alucard sensors to reset modified sensors
s16 g_SensorsCeilingBat[NUM_HORIZONTAL_SENSORS] = {-8, -8, -8, -8};
s16 g_SensorsFloorBat[NUM_HORIZONTAL_SENSORS] = {8, 8, 8, 8};
s16 g_SensorsWallBat[NUM_VERTICAL_SENSORS] = {7, 0, 0, 0, 0, 0, -7};
s16 g_SensorsCeilingDefault[NUM_HORIZONTAL_SENSORS] = {-22, -22, -22, -22};
s16 g_SensorsFloorDefault[NUM_HORIZONTAL_SENSORS] = {29, 25, 25, 25};
s16 g_SensorsWallDefault[NUM_VERTICAL_SENSORS] = {24, 17, 9, 1, -7, -14, -21};
s16 g_SensorsCeilingCrouch[NUM_HORIZONTAL_SENSORS] = {0, 0, 0, 0};
s16 g_SensorsWallCrouch[NUM_VERTICAL_SENSORS] = {24, 17, 9, 5, 5, 1, 1};

Point16 g_SensorsCeiling[NUM_HORIZONTAL_SENSORS] = {
    {0, -22},
    {0, -22},
    {4, -22},
    {-4, -22},
};
Point16 g_SensorsFloor[NUM_HORIZONTAL_SENSORS] = {
    {0, 29},
    {0, 25},
    {4, 25},
    {-4, 25},
};
Point16 g_SensorsWall[NUM_VERTICAL_SENSORS * 2] = {
    // sensors from bottom-right to top-right
    {7, 24},
    {7, 17},
    {7, 9},
    {7, 1},
    {7, -7},
    {7, -14},
    {7, -21},
    // sensors from bottom-left to top-left
    {-7, 24},
    {-7, 17},
    {-7, 9},
    {-7, 1},
    {-7, -7},
    {-7, -14},
    {-7, -21},
};

// BSS
extern s32 D_80137FB4;
extern s32 D_80137FB8;
#if defined(VERSION_US)
extern s32 D_80137FBC;
#endif

void func_801092E8(s32 arg0) {
    D_800A37D8[0] = D_800ACE48[arg0 * 2];
    D_800A37D8[1] = D_800ACE48[arg0 * 2 + 1];
    D_8006EBE0 = D_800ACE48[arg0 * 2];
}

void func_80109328(void) {
    s16* player_unk1E = &PLAYER.rotZ;

    g_Player.unk66 = 0;
    if (*player_unk1E == 0x800 && PLAYER.step == 8) {
        PLAYER.rotZ = 0;
        PLAYER.animCurFrame = 0x9D;
        PLAYER.facingLeft = (PLAYER.facingLeft + 1) & 1;
    }

    if (g_Player.timers[ALU_T_DARKMETAMORPH]) {
        g_Player.timers[ALU_T_DARKMETAMORPH] = 0;
        func_801092E8(0);
    }
    PLAYER.drawMode = DRAW_DEFAULT;
}

void func_801093C4(void) {
    DRAWENV drawEnv;
    Primitive* prim;
    s32 i;

    prim = &g_PrimBuf[g_Entities[1].primIndex];
    for (i = 0; i < 6; i++) {
        prim = prim->next;
    }
    switch (g_Player.unk6A) {
    case 0:
        if (func_800EDB08(prim) != 0) {
            prim->type = PRIM_ENV;
            prim->drawMode = DRAW_HIDE;
            prim = prim->next;
            func_800EDB08(prim);
            if (prim != NULL) {
                prim->type = PRIM_ENV;
                prim->drawMode = DRAW_HIDE;
                g_Player.unk6A++;
            }
        }
        break;
    case 1:
        if (g_Player.unk6A != 1) {
            return;
        }
        drawEnv = g_CurrentBuffer->draw;
        drawEnv.isbg = false;
        if (g_Player.status & PLAYER_STATUS_UNK4000000) {
            drawEnv.isbg = true;
        }
        drawEnv.r0 = drawEnv.g0 = drawEnv.b0 = 0;
        drawEnv.ofs[0] = 0x200;
        drawEnv.clip = D_800ACE60;
        drawEnv.ofs[1] = 0x1C0;
        SetDrawEnv(*(DR_ENV**)&prim->r1, &drawEnv);
        prim->priority = 0x190;
        prim->drawMode = DRAW_DEFAULT;
        prim = prim->next;
        prim->priority = 0x1B0;
        prim->drawMode = DRAW_UNK_800;
    }
}

// Duplicate of RIC func_80156F40
void func_80109594() {
    Entity* e;
    Primitive* prim;
    s32 radius;
    s32 intensity;
    s32 primIndex;
    s32 i;
    s32 val;
    s32 memset_len;
    s32* memset_ptr;
    s32 (*weapon)(void);

    g_Player.unk6A = 0;
    g_CurrentEntity = g_Entities;
    DestroyEntity(g_CurrentEntity);
    PLAYER.posX.val = 0x200000;
    PLAYER.posY.val = 0x200000;
    PLAYER.animSet = ANIMSET_DRA(1);
    PLAYER.palette = 0x8100;
    PLAYER.facingLeft = 0;
    PLAYER.rotX = 0x100;
    PLAYER.rotY = 0x100;
    PLAYER.zPriority = (u16)g_unkGraphicsStruct.g_zEntityCenter;

    memset_len = sizeof(PlayerState) / sizeof(s32);
    memset_ptr = &g_Player;
    for (i = 0; i < memset_len; i++) {
        *memset_ptr++ = 0;
    }

    for (i = 0; i < LEN(g_ButtonCombo); i++) {
        g_ButtonCombo[i].buttonsCorrect = 0;
        g_ButtonCombo[i].timer = 0;
    }

    g_Player.unk04 = 1;
    g_Player.pl_vram_flag = 1;
    func_8010E570(0);

    for (e = &g_Entities[1], i = 0; i < 3; i++, e++) {
        DestroyEntity(e);
        e->animSet = ANIMSET_DRA(1);
        e->unk5A = i + 1;
        e->palette = 0x8100;
        e->flags = FLAG_UNK_20000 | FLAG_POS_CAMERA_LOCKED;
    }

    primIndex = AllocPrimitives(PRIM_TILE, 8);
    prim = &g_PrimBuf[primIndex];
    g_Entities[1].primIndex = primIndex;
    g_Entities[1].flags |= FLAG_HAS_PRIMS;
    for (i = 0; i < 6; i++) {
        prim->drawMode = DRAW_UNK_100 | DRAW_HIDE | DRAW_UNK02;
        prim = prim->next;
    }
    func_801093C4();

#if defined(VERSION_US)
    g_Player.unk20 = 0x10;
    g_Player.D_80072EFC = 0x10;
    g_Player.padSim = 0;
    D_80137FB8 = 0;
    D_80137FBC = 1;
#elif defined(VERSION_HD)
    D_80137FB8 = 0;
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
        val = rcos(radius) * 0x10;
        D_801396F8[i] = +((val * intensity) >> 8);
        val = rsin(radius) * 0x10;
        D_80139778[i] = -((val * intensity) >> 7);
    }
    func_80111928();
    if (D_80097C98 == 6) {
        CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(121, 1), 0);
        func_8010E42C(1);
    }
    if (D_80097C98 == 4) {
        CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(121, 3), 0);
        func_8010E42C(3);
    }
    if (D_80097C98 == 5) {
        CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(121, 5), 0);
        func_8010E42C(5);
    }

    g_CurrentEntity = g_Entities;
    weapon = D_8017A000.GetWeaponId;
    if (weapon() != 0x2D) {
        return;
    }
    if (CheckEquipmentItemCount(ITEM_AXE_LORD_ARMOR, EQUIP_ARMOR) == 0) {
        return;
    }
    func_8010FAF4();

    weapon = D_8017A000.EntityWeaponAttack;
    weapon();
    g_Player.status |= PLAYER_STATUS_AXEARMOR;
    func_8010DFF0(1, 10);
    func_80109328();
}

void func_80109990(void) {
    if (D_80137FB4 == 0) {
        if (g_Status.mp == g_Status.mpMax &&
            !(g_Player.status & PLAYER_STATUS_UNK100000)) {
            CreateEntFactoryFromEntity(g_CurrentEntity, 40, 0);
            PlaySfx(SFX_UI_MP_FULL);
            D_80137FB4++;
        }
    } else if (g_Status.mp != g_Status.mpMax) {
        D_80137FB4 = 0;
    }
}

static void CheckFloor(void);
static void CheckCeiling(void);
static void CheckWallRight(void);
static void CheckWallLeft(void);
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
    pl_vram = &g_Player.pl_vram_flag;
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
            g_Player.pl_vram_flag = 3;
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
    s32 (*weapon)(void);

    g_CurrentEntity = &PLAYER;
    weapon = D_8017A000.GetWeaponId;
    // Wearing Axe Lord Armor! This is probably when you initially put it on.
    if ((weapon() == 0x2D) &&
        CheckEquipmentItemCount(ITEM_AXE_LORD_ARMOR, EQUIP_ARMOR)) {
        if (!(g_Player.status & PLAYER_STATUS_AXEARMOR)) {
            // Alucard says "WHAT?!" when first putting on Axe Lord Armor
            PlaySfx(SFX_VO_ALU_WHAT);
            g_Player.padSim = 0;
            g_Player.D_80072EFC = 0x20;
            func_8010FAF4();
            weapon = D_8017A000.EntityWeaponAttack;
            weapon();
            g_Player.status |= PLAYER_STATUS_AXEARMOR;
            func_8010DFF0(1, 0xA);
            func_80109328();
            if (arg0 != 0) {
                PlayAnimation(D_800B0130, D_800B01B8);
            }
        }
    } else if (g_Player.status & PLAYER_STATUS_AXEARMOR) {
        PLAYER.palette = 0x8100;
        PLAYER.animSet = 1;
        PLAYER.unk5A = 0;
        PLAYER.rotZ = 0;
        PLAYER.drawFlags &=
            (FLAG_DRAW_UNK10 | FLAG_DRAW_UNK20 | FLAG_DRAW_UNK40 | FLAG_BLINK |
             FLAG_DRAW_ROTY | FLAG_DRAW_ROTX);
        func_8010FAF4();
        PLAYER.rotPivotY = 0;
        PLAYER.rotPivotX = 0;
        if (g_Player.pl_vram_flag & 1) {
            func_8010E570(0);
        } else {
            func_8010E7AC();
        }
        g_Player.status &= ~PLAYER_STATUS_AXEARMOR;
        func_80111CC0();
        if (arg0 != 0) {
            PlayAnimation(D_800B0130, D_800B01B8);
        }
    }
}

void func_8010A3F0(void) {
    s32 temp = 0x38;

    if (D_8017A000.GetWeaponId() == temp && D_8017D000.GetWeaponId() == temp) {
        if (!g_Player.timers[ALU_T_DARKMETAMORPH]) {
            func_801092E8(1);
        }
        g_Player.timers[ALU_T_DARKMETAMORPH] = 0x20;
        temp = g_Player.unk10 != 0;
        if (temp && g_Status.D_80097C40 < -1) {
            g_Status.D_80097C40++;
        }
    }
    g_Player.unk10 = 0;
}

TeleportCheck GetTeleportToOtherCastle(void) {
    // Is player in the pose when pressing UP?
    if (PLAYER.step != 0 || PLAYER.step_s != 1) {
        return TELEPORT_CHECK_NONE;
    }

    // Check for X/Y boundaries in TOP
    if (g_StageId == STAGE_TOP) {
        if (abs(g_Tilemap.left * 256 + g_PlayerX - 8000) < 4 &&
            abs(g_Tilemap.top * 256 + g_PlayerY - 2127) < 4) {
            return TELEPORT_CHECK_TO_RTOP;
        }
    }

    // Check for X/Y boundaries in RTOP
    if (g_StageId == STAGE_RTOP) {
        if (abs(g_Tilemap.left * 256 + g_PlayerX - 8384) < 4 &&
#if defined(VERSION_US)
            abs(g_Tilemap.top * 256 + g_PlayerY - 14407) < 4) {
#elif defined(VERSION_HD)
            abs(g_Tilemap.top * 256 + g_PlayerY) - 14407 < 4) {
#endif
            return TELEPORT_CHECK_TO_TOP;
        }
    }

    return TELEPORT_CHECK_NONE;
}

void EntityAlucard(void) {
    DamageParam damage;
    s32 (*weapon_func)(void);
    s32 var_fp;
    PlayerDraw* draw;

    s32 temp_v0;
    u16 temp_v0_2;
    s32 temp_s1;
    s32 temp_a0;
    s32 temp_v1;
    s32 newStatus;
    s16 var_s6;
    s16 var_s7;

    g_CurrentEntity = &PLAYER;
    if (D_800ACE44 != 0) {
        D_800ACE44--;
    }
    if (g_unkGraphicsStruct.D_800973FC != 0 && D_80137FB8 == 0) {
        CreateEntFactoryFromEntity(g_Entities, 0x78, 0);
    }
    var_fp = 0;
    var_s6 = 0;
    g_Player.unk70 = g_Player.unk18 = PLAYER.drawFlags = g_Player.unk4C =
        FLAG_DRAW_DEFAULT;
    D_80137FB8 = g_unkGraphicsStruct.D_800973FC;
    var_s7 = 0;
    g_Player.unk72 = func_80110394();
    if (!(g_Player.status & PLAYER_STATUS_DEAD)) {
        newStatus = GetTeleportToOtherCastle();
        if (newStatus != 0) {
            func_8010E42C(newStatus);
        }
        if (PLAYER.step != 0x12) {
            func_8010A234(0);
            func_8010A3F0();
            func_80109990();
            if (g_Player.unk56 != 0) {
                g_Status.hp += g_Player.unk58;
                func_800FE8F0();
                CreateHPNumMove(g_Player.unk58, 1);
                if (g_Player.unk56 == 1) {
                    PlaySfx(SFX_HEALTH_PICKUP);
                    if (!(g_Player.status & PLAYER_STATUS_STONE)) {
                        CreateEntFactoryFromEntity(
                            g_CurrentEntity, FACTORY(0x2C, 0x48), 0);
                        CreateEntFactoryFromEntity(
                            g_CurrentEntity, FACTORY(0x2C, 0x44), 0);
                    }
                }
                if ((g_Player.unk56 == 2) &&
                    !(g_Player.status & PLAYER_STATUS_STONE)) {
                    CreateEntFactoryFromEntity(
                        g_CurrentEntity, FACTORY(0x2C, 0x48), 0);
                }
                if (g_Status.hpMax < g_Status.hp) {
                    g_Status.hp = g_Status.hpMax;
                }
                g_Player.unk56 = 0;
            }
            newStatus = CheckAndDoLevelUp();
            if (newStatus != 0) {
                CreateEntFactoryFromEntity(
                    g_CurrentEntity, FACTORY(0x19, newStatus - 1), 0);
            }
            for (newStatus = 0; newStatus < 16; newStatus++) {
                if (g_Player.timers[newStatus]) {
                    switch (newStatus) {
                    case 2:
                        PLAYER.palette = g_Player.unk40;
                        break;
                    case 3:
                        PLAYER.palette = g_Player.pl_high_jump_timer;
                        g_Player.timers[15] = 12;
                        break;
                    case 4: {
                        s32 temp_s1 = ((g_GameTimer & 0xF) << 8);
                        draw = g_PlayerDraw;
                        draw->r0 = draw->b0 = draw->g0 =
                            (rsin((s16)temp_s1) + 0x1000) / 64 + 0x60;
                        draw->r1 = draw->b1 = draw->g1 =
                            (rsin(temp_s1 + 0x200) + 0x1000) / 64 + 0x60;
                        draw->r3 = draw->b3 = draw->g3 =
                            (rsin(temp_s1 + 0x400) + 0x1000) / 64 + 0x60;
                        draw->r2 = draw->b2 = draw->g2 =
                            (rsin(temp_s1 + 0x600) + 0x1000) / 64 + 0x60;
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
                    case 0:
                        break;
                    }
                    if (!--g_Player.timers[newStatus]) {
                        switch (newStatus) {
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
            if (g_Player.D_80072EFC != 0) {
                g_Player.D_80072EFC--;
#ifdef VERSION_US
                if (g_Player.D_80072EFC == 0) {
                    D_80137FBC = 1;
                }
#endif
                g_Player.padPressed = g_Player.padSim & 0xFFFF;
                switch (g_Player.padSim >> 0x10) { /* switch 6; irregular */
                case 1:                            /* switch 6 */
                    if (PLAYER.step != Player_Unk48) {
                        func_8010E168(1, 4);
                        SetPlayerStep(Player_Unk48);
                        g_unkGraphicsStruct.pauseEnemies = 1;
                    }
                    break;
                case 2: /* switch 6 */
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
                g_Player.padPressed = g_pads[0].pressed;
                g_Player.padPressed = g_Player.padPressed & 0xFF00;
                for (newStatus = 0; newStatus < 8; newStatus++) {
                    if (g_pads[0].pressed & g_Settings.buttonMask[newStatus]) {
                        g_Player.padPressed |= D_800ACE00[newStatus];
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

// HD and US test this in slightly different places leading to this and the
// following ifdef.
#if defined(VERSION_HD)
            if (g_Player.timers[13] | g_Player.timers[14]) {
                goto specialmove;
            }
#endif
            if (g_Player.unk60 < 2) {
                if (g_Player.unk60 == 1) {
                    var_s6 = PLAYER.step;
                    var_s7 = PLAYER.step_s;
                    SetPlayerStep(Player_BossGrab);
                } else {
#if defined(VERSION_US)
                    if (!(g_Player.timers[13] | g_Player.timers[14])) {
#elif defined(VERSION_HD)
                    if (1) { // to make curly braces match
#endif
                        if (PLAYER.hitParams) {
                            var_s6 = PLAYER.step;
                            var_s7 = PLAYER.step_s;
                            newStatus = HandleDamage(
                                &damage, PLAYER.hitParams, PLAYER.hitPoints, 0);
                            if ((g_Player.status & PLAYER_STATUS_AXEARMOR) &&
                                ((newStatus == 1) || (newStatus == 7) ||
                                 (newStatus == 8))) {
                                newStatus = 3;
                                damage.damageKind = DAMAGEKIND_1;
                            }
                            switch (newStatus) {
                            case 0:
                                CreateEntFactoryFromEntity(
                                    g_CurrentEntity, FACTORY(0x2F, 0), 0);
                                CreateEntFactoryFromEntity(
                                    g_CurrentEntity, FACTORY(0x2C, 0x43), 0);
                                CreateEntFactoryFromEntity(
                                    g_CurrentEntity, FACTORY(0x2C, 0x51), 0);
                                CreateHPNumMove(0, 0);
                                func_8010E168(1, 0xC);
                                break;
                            case 1:
                                g_Player.pl_high_jump_timer = 0x8166;
                                g_Player.unk18 = damage.effects;
                                func_8010E168(1, 0xC);
                                g_Player.timers[3] = 6;
                                PlaySfx(SFX_VO_ALU_PAIN_A);
                                CreateHPNumMove(1, 0);
                                break;
                            case 2:
                                g_Player.unk18 = damage.effects;
                                CreateEntFactoryFromEntity(
                                    g_CurrentEntity, FACTORY(0x73, 0), 0);
                                CreateEntFactoryFromEntity(
                                    g_CurrentEntity, FACTORY(0x2C, 0x58), 0);
                                g_Player.pl_high_jump_timer = 0x8166;
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
                                    g_CurrentEntity, FACTORY(0x2C, 0x44), 0);
                                CreateEntFactoryFromEntity(
                                    g_CurrentEntity, FACTORY(0x2C, 0x48), 0);
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
                                var_fp = 1;
                                break;
                            case 9:
                                CreateEntFactoryFromEntity(
                                    g_CurrentEntity, FACTORY(0x2C, 0x4E), 0);
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
#if defined(VERSION_US)
                    if (g_Player.unk20 == 0 || --g_Player.unk20 == 0) {
#elif defined(VERSION_HD)
                    if (D_800ACEDC_hd == 0 || --D_800ACEDC_hd == 0) {
#endif
                        if (D_80097448[1] == 0) {
                            if ((g_Player.padTapped & PAD_L1) &&
                                (HandleTransformationMP(
                                     FORM_MIST, CHECK_ONLY) == 0) &&
                                ((PLAYER.step == 0) || (PLAYER.step == 1) ||
                                 (PLAYER.step == 2) || (PLAYER.step == 3) ||
                                 (PLAYER.step == 4) || (PLAYER.step == 6) ||
                                 (PLAYER.step == 8) ||
                                 ((PLAYER.step == Player_MorphBat) &&
                                  (PLAYER.step_s != 0)) ||
                                 ((PLAYER.step == 0x18) &&
                                  (PLAYER.step_s != 0) &&
                                  (PLAYER.step_s != 8)))) {
                                func_80109328();
                                SetPlayerStep(Player_MorphMist);
                                PlaySfx(SFX_TRANSFORM_LOW);
                                goto block_159;
                            }
                            if ((g_Player.padTapped & PAD_R1) &&
                                (HandleTransformationMP(FORM_BAT, CHECK_ONLY) ==
                                 0)) {
                                if (PLAYER.step == 0 || (PLAYER.step == 1) ||
                                    (PLAYER.step == 2) || (PLAYER.step == 3) ||
                                    (PLAYER.step == 4) || (PLAYER.step == 6)) {
                                    goto block_62check;
                                }
                                if ((PLAYER.step == Player_MorphMist) ||
                                    (PLAYER.step == 8) ||
                                    (PLAYER.step == 24 &&
                                     (PLAYER.step_s != 0 &&
                                      PLAYER.step_s != 8))) {
                                block_62check:
                                    if (PLAYER.step == 6 || PLAYER.step == 2) {
                                        D_8013AECC = 0xC;
                                    }
                                    func_80109328();
                                    SetPlayerStep(Player_MorphBat);
                                    PlaySfx(SFX_TRANSFORM_LOW);
                                    goto block_160;
                                }
                            }
                        }
                        if ((g_Player.padTapped & PAD_R2) &&
                            (HandleTransformationMP(FORM_WOLF, CHECK_ONLY) ==
                             0) &&
                            ((D_80097448[1] == 0) ||
                             IsRelicActive(RELIC_HOLY_SYMBOL)) &&
                            (PLAYER.step == 0 || (PLAYER.step == 1) ||
                             (PLAYER.step == 2) || (PLAYER.step == 3) ||
                             (PLAYER.step == 4) || (PLAYER.step == 6) ||
                             ((PLAYER.step == Player_MorphMist) ||
                              (PLAYER.step == 8)) ||
                             ((PLAYER.step == Player_MorphBat) &&
                              (PLAYER.step_s != 0)))) {
                            func_80109328();
                            SetPlayerStep(0x18);
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
        func_801120B4();
        break;
    case Player_Walk:
        func_80112B64();
        break;
    case Player_Crouch:
        func_801131C4();
        break;
    case Player_Fall:
        func_80113148();
        break;
    case Player_Jump:
        PlayerStepJump();
        break;
    case Player_MorphBat:
        ControlBatForm();
        break;
    case Player_UnmorphBat:
        func_801177A0();
        break;
    case Player_MorphMist:
        ControlMistForm();
        break;
    case Player_UnmorphMist:
        func_801182F8();
        break;
    case Player_MorphWolf:
        func_8012EF2C();
        break;
    case Player_UnmorphWolf:
        func_8012EAD0();
        break;
    case Player_HighJump:
        func_80113AAC();
        break;
    case Player_SwordWarp:
        func_801186EC();
        break;
    case Player_Hit:
        AlucardHandleDamage(&damage, var_s6, var_s7);
        break;
    case Player_StatusStone:
        func_80114DF4(var_fp);
        break;
    case Player_BossGrab:
        func_80116208();
        break;
    case Player_Kill:
        func_80115394(&damage, var_s6, var_s7);
        break;
    case Player_Unk17:
        func_80115BB0();
        break;
    case Player_Teleport:
        func_80115DA0();
        break;
    case Player_SpellDarkMetamorphosis:
        func_80118614();
        break;
    case Player_SpellHellfire:
        PlayerStepHellfire();
        break;
    case Player_SpellSoulSteal:
        func_80118670();
        break;
    case Player_SpellSummonSpirit:
    case Player_SpellTetraSpirit:
    case Player_SpellSwordBrothers:
        func_80118640();
        break;
    case Player_Unk48:
        func_801166A4();
        break;
    case Player_Unk49:
        func_8011678C();
        break;
    case Player_Unk50:
        func_801167D0();
        break;
    case Player_KillWater:
        func_80115F54();
        break;
    case Player_AlucardStuck:
        func_80117AC0();
        break;
    case Player_AxearmorStand:
        weapon_func = D_8017A000.func_ptr_80170004;
        goto runweapon;
    case Player_AxearmorWalk:
        weapon_func = D_8017A000.func_ptr_80170008;
        goto runweapon;
    case Player_AxearmorJump:
        weapon_func = D_8017A000.func_ptr_8017000C;
        goto runweapon;
    case Player_AxearmorHit:
        weapon_func = D_8017A000.func_ptr_80170010;
    runweapon:
        weapon_func();
    }
    newStatus = 0;
    g_unkGraphicsStruct.unk1C &= ~2;
    g_Player.status &= ~PLAYER_STATUS_UNK8;
    g_Player.unk08 = g_Player.status;
    g_Status.D_80097BF8 &= ~1;
    switch (PLAYER.step) { /* switch 5 */
    case 2:                /* switch 5 */
        if (PLAYER.step_s != 2) {
            newStatus = PLAYER_STATUS_CROUCH;
        }
        newStatus |= 0x10000000;
        break;
    case 1: /* switch 5 */
        newStatus = 0x04000000;
        /* fallthrough */
    case 0: /* switch 5 */
        newStatus |= 0x10000000;
        if (PLAYER.step_s == 4) {
            newStatus |= 0x08100000;
        }
        break;
    case 3: /* switch 5 */
    case 4: /* switch 5 */
        newStatus = 0x10002000;
        break;
    case 5: /* switch 5 */
        if (PLAYER.step_s == 3) {
            func_8010E168(1, 4);
            g_unkGraphicsStruct.unk1C |= 2;
        }
        newStatus = 0x28100001;
        break;
    case 7: /* switch 5 */
        func_8010E168(1, 4);
        newStatus = 0x28100002;
        PLAYER.palette = 0x810D;
        break;
    case 14:
        newStatus = 0x28900002;
        PLAYER.palette = 0x810D;
        func_8010E168(1, 4);
        break;
    case 6: /* switch 5 */
        func_8010E168(1, 4);
        newStatus = 0x18100010 | PLAYER_STATUS_CROUCH;
        break;
    case 9: /* switch 5 */
        newStatus = 0x28500001;
        if (PLAYER.step_s == 0) {
            PLAYER.animSet = 0xD;
            PLAYER.unk5A = 0;
        }
        func_8010E168(1, 4);
        break;
    case 8: /* switch 5 */
        func_8010E168(1, 4);
        newStatus = 0x38000000;
        break;
    case 10: /* switch 5 */
    case 48: /* switch 5 */
    case 49: /* switch 5 */
        newStatus = 0x38110000;
        func_8010E168(1, 12);
        break;
    case 11: /* switch 5 */
        newStatus = 0x38110080;
        break;
    case 12: /* switch 5 */
        newStatus = 0x38110040;
        func_8010E168(1, 12);
        break;
    case 13: /* switch 5 */
    case 16: /* switch 5 */
        newStatus = 0x18150000;
        if (PLAYER.step_s == 0x80) {
            newStatus = 0x181D0000;
        }
        func_8010E168(1, 12);
        break;
    case 17: /* switch 5 */
        newStatus = 0x18150000;
        func_8010E168(1, 12);
        break;
    case 18: /* switch 5 */
        newStatus = 0x18100000;
        func_8010E168(1, 12);
        break;
    case 33: /* switch 5 */
    case 35: /* switch 5 */
    case 39: /* switch 5 */
        func_8010E168(1, 0x10);
        newStatus = 0x38000200 | PLAYER_STATUS_CROUCH;
        break;
    case 32: /* switch 5 */
    case 34: /* switch 5 */
    case 37: /* switch 5 */
        func_8010E168(1, 0x10);
        newStatus = 0x38000200;
        break;
    case 43: /* switch 5 */
        func_8010E168(1, 0x14);
        /* fallthrough */
    case 40: /* switch 5 */
    case 41: /* switch 5 */
    case 42: /* switch 5 */
    case 50: /* switch 5 */
        PLAYER.unk5A = 0x64;
        newStatus = 0x29100000;
        break;
    case 15: /* switch 5 */
        newStatus = 0x18100000;
        func_8010E168(4, 0xC);
        PLAYER.palette = 0x810D;
        break;
    case 24: /* switch 5 */
        g_unkGraphicsStruct.unk1C |= 2;
        if (abs(PLAYER.velocityX) > FIX(3)) {
            func_8010E168(1, 4);
        }
        newStatus = 0x2C100204;
        if ((PLAYER.step_s == 0) || (PLAYER.step_s == 8)) {
            newStatus = 0x6C100204;
        }
        if (PLAYER.step_s == 3) {
            newStatus |= PLAYER_STATUS_CROUCH;
        }
        break;
    case 25: /* switch 5 */
        newStatus = 0x68100000;
        func_8010E168(1, 4);
        break;
    }
    if (g_Player.timers[9]) {
        newStatus |= 0x400;
    }
    if (g_Player.timers[10]) {
        newStatus |= 0x800;
    }
    if (g_Player.timers[12]) {
        newStatus |= 0x1000;
    }
    if (g_Player.timers[0]) {
        newStatus |= 0x28104000;
    }
    if (g_Player.timers[1]) {
        newStatus |= 0x28108000;
    }
    if (*D_80097448 != 0) {
        newStatus |= 0x08020000;
    }
    if (g_Player.timers[ALU_T_DARKMETAMORPH]) {
        newStatus |= 0x02000000;
    }
    g_Player.status = newStatus;
    if ((newStatus & 0x08000000) || (g_unkGraphicsStruct.D_800973FC != 0)) {
        func_8010DFF0(1, 1);
    }
    if (newStatus & 0x10000000) {
        PLAYER.animSet = 1;
        PLAYER.unk5A = 0;
    }
    if (newStatus & 0x20000000) {
        g_Status.D_80097BF8 |= 1;
    }
    if (g_Player.timers[13] | g_Player.timers[14]) {
        g_Player.status |= PLAYER_STATUS_UNK100;
    }
    if ((g_Player.unk08 & 0x10000) &&
        !(g_Player.status & (PLAYER_STATUS_UNK10000 | PLAYER_STATUS_DEAD))) {
        func_8010E168(1, 0xC);
        if (!(g_Player.status & (PLAYER_STATUS_POISON | PLAYER_STATUS_CURSE))) {
            g_Player.timers[4] = 0xC;
            g_Player.timers[15] = 4;
            PLAYER.palette = 0x8100;
        }
    }
    PlayAnimation(D_800B0130, D_800B01B8);
    if (g_Player.status & PLAYER_STATUS_DEAD) {
        if (PLAYER.animFrameDuration < 0) {
            PLAYER.animCurFrame |= ANIM_FRAME_LOAD;
        }
        PLAYER.hitParams = 0;
        PLAYER.hitboxState = 0;
    } else {
        PLAYER.hitboxState = 1;
        PLAYER.hitParams = 0;
        PLAYER.hitPoints = 0;
    }
    g_Player.unk14 = 0;
    g_Player.unk7A = 0;
    func_801093C4();
    if (!(g_Player.status & (PLAYER_STATUS_UNK10 | PLAYER_STATUS_UNK40))) {
        if ((CheckEquipmentItemCount(0x58U, 4U) != 0) &&
            !(g_Player.status & (PLAYER_STATUS_TRANSFORM | PLAYER_STATUS_UNK10 |
                                 PLAYER_STATUS_UNK10000 | PLAYER_STATUS_DEAD |
                                 PLAYER_STATUS_AXEARMOR)) &&
            !(PLAYER.drawFlags & (FLAG_DRAW_ROTY | FLAG_DRAW_ROTZ))) {
            PLAYER.drawFlags |= FLAG_DRAW_ROTY;
            PLAYER.rotY = 0x110;
            PLAYER.rotPivotY = 0x18;
        }
        func_8010D59C();
        if ((*D_80097448 >= 0x29 ||
             ((g_Player.status & PLAYER_STATUS_WOLF_FORM) &&
              *D_80097448 >= 0xD)) &&
            (g_CurrentEntity->nFramesInvincibility == 0)) {
            PLAYER.velocityY = PLAYER.velocityY * 3 / 4;
            PLAYER.velocityX = PLAYER.velocityX * 3 / 4;
        }
        temp_s1 = g_Player.pl_vram_flag;
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
            for (newStatus = 0; newStatus < 7; newStatus++) {
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
        g_Player.unk04 = temp_s1;
        if (((*D_80097448 >= 0x29) ||
             ((g_Player.status & PLAYER_STATUS_WOLF_FORM) &&
              (*D_80097448 >= 0xD))) &&
            (g_CurrentEntity->nFramesInvincibility == 0)) {
            PLAYER.velocityY = PLAYER.velocityY * 4 / 3;
            PLAYER.velocityX = PLAYER.velocityX * 4 / 3;
        }
        g_CurrentEntity->nFramesInvincibility = 0;
        func_8010D800();
        if (PLAYER.animSet == 0xD) {
            D_800CFE48[PLAYER.animCurFrame & 0x7FFF]->unk4 =
                D_8013AECC + D_800ACE20[PLAYER.animCurFrame];
        }
#ifdef VERSION_US
        FntPrint("step:%04x\n", PLAYER.step);
        FntPrint("bat_i_step:%04x\n", g_Player.unk66);
#endif
    }
}

void GetPlayerSensor(Collider* col) {
    if (g_PlayableCharacter == PLAYER_ALUCARD) {
        u32 mod = (g_Player.status >> 1) & 2;
        col->unk14 = g_SensorsWall[0].x - mod;
        col->unk1C = g_SensorsWall[0].y + mod;
        col->unk18 = g_SensorsFloor[1].y - 1;
        col->unk20 = g_SensorsCeiling[1].y + 1;
    } else {
        g_PlOvl.GetPlayerSensor(col);
    }
}

void func_8010BFFC(void) {
    s16 x;
    s16 y;
    s32 i;
    bool collided = false;
    u16 original_Y = PLAYER.posY.i.hi;

    if ((g_Player.pl_vram_flag & 1) || (D_801396EA != 0) ||
#if defined(VERSION_US)
        (g_Player.status &
         (PLAYER_STATUS_TRANSFORM | PLAYER_STATUS_UNK40000000)) ||
        ((g_PlayableCharacter != 0) && (PLAYER.step == 0x18)) ||
#elif defined(VERSION_HD)
        (g_Player.status & PLAYER_STATUS_TRANSFORM) ||
#endif
        (g_Player.unk78 == 1)) {
        return;
    }
    if (PLAYER.posY.i.hi < 48) {
        PLAYER.posY.i.hi -= 16;
        while (true) {
            for (i = 0; i < 4; i++) {
                x = PLAYER.posX.i.hi + g_SensorsFloor[i].x;
                y = PLAYER.posY.i.hi + g_SensorsFloor[i].y;
                CheckCollision(x, y, &g_Player.colFloor[i], 0);
            }
            if ((g_Player.colFloor[1].effects &
                 (EFFECT_SOLID_FROM_BELOW + EFFECT_SOLID)) == EFFECT_SOLID ||
                (g_Player.colFloor[2].effects &
                 (EFFECT_SOLID_FROM_BELOW + EFFECT_SOLID)) == EFFECT_SOLID ||
                (g_Player.colFloor[3].effects &
                 (EFFECT_SOLID_FROM_BELOW + EFFECT_SOLID)) == EFFECT_SOLID) {
                // I don't know man
                (*(&PLAYER)).posY.i.hi--;
                PLAYER.velocityY = 0;
                collided = true;
                continue;
            }
            if (collided) {
                return;
            }
            PLAYER.posY.i.hi += 8;
            if (PLAYER.posY.i.hi >= 48) {
                PLAYER.posY.i.hi = original_Y;
                return;
            }
        }
    } else if (PLAYER.posY.i.hi > 176) {
        PLAYER.posY.i.hi += 32;
        while (true) {
            for (i = 0; i < 4; i++) {
                x = PLAYER.posX.i.hi + g_SensorsCeiling[i].x;
                y = PLAYER.posY.i.hi + g_SensorsCeiling[i].y;
#if defined(VERSION_US)
                if (g_PlayableCharacter != PLAYER_ALUCARD) {
                    y += 6;
                }
#endif
                CheckCollision(x, y, &g_Player.colFloor[4 + i], 0);
            }
            if ((g_Player.colCeiling[1].effects &
                 (EFFECT_SOLID_FROM_ABOVE + EFFECT_SOLID)) == EFFECT_SOLID ||
                (g_Player.colCeiling[2].effects &
                 (EFFECT_SOLID_FROM_ABOVE + EFFECT_SOLID)) == EFFECT_SOLID ||
                (g_Player.colCeiling[3].effects &
                 (EFFECT_SOLID_FROM_ABOVE + EFFECT_SOLID)) == EFFECT_SOLID) {
                // I don't know man
                (*(&PLAYER)).posY.i.hi++;
                PLAYER.velocityY = 0;
                collided = true;
                continue;
            }
            if (collided) {
                PLAYER.posY.i.hi--;
                return;
            }
            PLAYER.posY.i.hi -= 8;
            if (PLAYER.posY.i.hi <= 176) {
                PLAYER.posY.i.hi = original_Y;
                return;
            }
        }
    }
}

static void CheckFloor(void) {
    Collider sp10;
    byte stackpad[40];
    s32 var_s1;
    s32 var_a0;
    s32 var_s2;
    s32 sp30;
    s32 var_s8;
    s16 var_s6;
    s16 argX;
    s16 argY;

    s16 var_s5 = 0;
    s32 i = 0;
    s16* yPosPtr = &PLAYER.posY.i.hi;
    s16* xPosPtr = &PLAYER.posX.i.hi;
    s32* vram_ptr = &g_Player.pl_vram_flag;

    if (g_unkGraphicsStruct.unk18) {
        *vram_ptr = 1;
        return;
    }
    if ((PLAYER.velocityY == 0) && (g_Player.unk04 & 1) &&
        !(g_Player.status &
          (PLAYER_STATUS_BAT_FORM | PLAYER_STATUS_MIST_FORM))) {
        var_s5 = 4;
    } else {
        i = 1;
    }
    for (; i < NUM_HORIZONTAL_SENSORS; i++, var_s5 = 0) {
        if (g_Player.colFloor[i].effects & EFFECT_SOLID_FROM_BELOW) {
            continue;
        }
        if (!((g_Player.colFloor[i].effects & EFFECT_UNK_0002) ||
              (PLAYER.velocityY >= 0) ||
              (g_Player.status & PLAYER_STATUS_TRANSFORM) ||
              (abs(PLAYER.velocityX) >= FIX(2)))) {
            continue;
        }
        var_s2 = g_Player.colFloor[i].effects &
                 (EFFECT_UNK_8000 | EFFECT_UNK_0800 | EFFECT_SOLID);
        if ((var_s2 == EFFECT_SOLID) || (var_s2 & EFFECT_UNK_0800)) {
            if ((g_Player.status &
                 (PLAYER_STATUS_BAT_FORM | PLAYER_STATUS_MIST_FORM)) &&
                !(var_s2 & 1)) {
                continue;
            }
            argX = *xPosPtr + g_SensorsFloor[i].x;
            argY = *yPosPtr + g_SensorsFloor[i].y;
            argY += (g_Player.colFloor[i].unk18 - 1);
            CheckCollision(argX, argY, &sp10, 0);
            if ((g_Player.status & PLAYER_STATUS_MIST_FORM) &&
                (sp10.effects & EFFECT_MIST_ONLY)) {
                sp10.effects &= ~(EFFECT_UNK_0002 | EFFECT_SOLID);
            }
            var_s1 = sp10.effects;
            if (!(sp10.effects & EFFECT_SOLID)) {
                if (((g_Player.colFloor[i].effects != EFFECT_SOLID) &&
                     (g_Player.colFloor[i].effects !=
                      (EFFECT_SOLID_FROM_ABOVE | EFFECT_SOLID))) ||
                    (PLAYER.velocityY >= 0)) {
                    if (var_s2 & EFFECT_UNK_0800) {
                        *yPosPtr += var_s5 + g_Player.colFloor[i].unk8;
                    } else {
                        *yPosPtr += var_s5 + g_Player.colFloor[i].unk18;
                    }
                    *vram_ptr |= 1;
                    return;
                }
                continue;
            } else {
                var_a0 =
                    var_s1 & (EFFECT_UNK_8000 | EFFECT_UNK_0002 | EFFECT_SOLID);
                if (var_a0 == (EFFECT_UNK_8000 | EFFECT_SOLID)) {
                    if (i < 2) {
                        *vram_ptr |=
                            ((var_s1 & (EFFECT_UNK_4000 | EFFECT_UNK_2000 |
                                        EFFECT_UNK_1000)) +
                             0x7FFF + 2);
                        *yPosPtr +=
                            g_Player.colFloor[i].unk8 + sp10.unk18 - 1 + var_s5;
                        return;
                    }
                    if ((i == 2) &&
                        ((var_s1 &
                          (EFFECT_UNK_8000 | EFFECT_UNK_4000 | EFFECT_SOLID)) ==
                         (EFFECT_UNK_8000 | EFFECT_SOLID))) {
                        g_Player.colFloor[2].effects = var_s1;
                        g_Player.colFloor[2].unk10 = g_Player.colFloor[2].unk8;
                    }
                    if ((i == 3) &&
                        ((var_s1 &
                          (EFFECT_UNK_8000 | EFFECT_UNK_4000 | EFFECT_SOLID)) ==
                         (EFFECT_UNK_8000 | EFFECT_UNK_4000 | EFFECT_SOLID))) {
                        g_Player.colFloor[3].effects = var_s1;
                        g_Player.colFloor[3].unk10 = g_Player.colFloor[3].unk8;
                    }
                }
            }
        }
        if ((var_s2 != (EFFECT_UNK_8000 | EFFECT_SOLID)) || (i >= 2)) {
            continue;
        }
        *vram_ptr |= g_Player.colFloor[i].effects &
                     (EFFECT_UNK_8000 | EFFECT_UNK_4000 | EFFECT_UNK_2000 |
                      EFFECT_UNK_1000 | EFFECT_SOLID);
        *yPosPtr += var_s5 + g_Player.colFloor[i].unk18;
        return;
    }
    if (g_Player.colFloor[1].effects & EFFECT_QUICKSAND) {
        *vram_ptr |= 0x11;
        if ((g_Timer & 3) == 0) {
            (*yPosPtr)++;
        }
        return;
    }
    if (g_Player.colFloor[1].effects & EFFECT_WATER) {
        *vram_ptr |= 0x80;
    }
    if (PLAYER.velocityY < 0) {
        return;
    }
    argX = *xPosPtr + g_SensorsFloor[0].x;
    argY = *yPosPtr + g_SensorsFloor[0].y + 10;
    CheckCollision(argX, argY, &sp10, 0);
    if ((sp10.effects & (EFFECT_UNK_8000 | EFFECT_SOLID)) != EFFECT_NONE) {
        return;
    }

    for (i = 2; i < NUM_HORIZONTAL_SENSORS; i++) {
        if ((g_Player.colFloor[3].effects & EFFECT_UNK_8000) &&
            (g_Player.colFloor[2].effects & EFFECT_UNK_8000)) {
            return;
        }
        var_s2 = g_Player.colFloor[i].effects;
        sp30 =
            ((var_s2 & (EFFECT_UNK_4000 | EFFECT_UNK_2000 | EFFECT_UNK_1000)) +
             0x7FFF + 2);
        if (!(var_s2 & EFFECT_UNK_8000)) {
            continue;
        }
        if (i == 2) {
            var_s1 = EFFECT_UNK_4000;
            var_s6 = g_Player.colFloor[2].unk4;
            var_s8 = var_s6 + 8;
        } else {
            var_s1 = 0;
            var_s6 = g_Player.colFloor[3].unkC;
            var_s8 = 8 - var_s6;
        }
        if ((var_s2 & EFFECT_UNK_4000) == var_s1) {
            argX = var_s6 + (*xPosPtr + g_SensorsFloor[i].x);
            argY = *yPosPtr + g_SensorsFloor[i].y;
            CheckCollision(argX, argY, &sp10, 0);
            if (sp10.effects & EFFECT_SOLID) {
                *yPosPtr += sp10.unk18;
                *vram_ptr |= sp30;
                return;
            }
            continue;
        }
        if (var_s8 <= 0) {
            continue;
        }
        if (!(var_s2 & 1)) {
            continue;
        }
        argX = var_s6 + (*xPosPtr + g_SensorsFloor[i].x);
        argY = *yPosPtr + g_SensorsFloor[i].y + g_Player.colFloor[i].unk10;
        CheckCollision(argX, argY, &sp10, 0);
        if (sp10.effects & EFFECT_SOLID) {
            *yPosPtr += (sp10.unk18 + g_Player.colFloor[i].unk10);
            *vram_ptr |= sp30;
            return;
        }
    }
}

static void CheckCeiling(void) {
    Collider collider;
    s32 temp_fp;
    u32 temp_s0;
    s32 temp_v1;
    s32 var_a0;
    s16 var_a1;

    s16 argX;
    s16 argY;

    u32 collidereffects;

    s32 i = 1;

    s16* yPosPtr = &PLAYER.posY.i.hi;
    s16* xPosPtr = &PLAYER.posX.i.hi;
    s32* vram_ptr = &g_Player.pl_vram_flag;

    if (g_unkGraphicsStruct.unk18) {
        return;
    }
    for (; i < NUM_HORIZONTAL_SENSORS; i++) {
        if (g_Player.colCeiling[i].effects & EFFECT_SOLID_FROM_ABOVE) {
            continue;
        }
        if ((g_Player.status & PLAYER_STATUS_MIST_FORM) &&
            (collider.effects & EFFECT_MIST_ONLY)) {
            collider.effects &= ~(EFFECT_UNK_0002 | EFFECT_SOLID);
        }
        temp_s0 = g_Player.colCeiling[i].effects &
                  (EFFECT_UNK_8000 | EFFECT_UNK_0800 | EFFECT_SOLID);
        if ((temp_s0 == EFFECT_SOLID) || (temp_s0 & EFFECT_UNK_8000)) {
            if ((g_Player.status &
                 (PLAYER_STATUS_BAT_FORM | PLAYER_STATUS_MIST_FORM)) &&
                !(temp_s0 & EFFECT_SOLID)) {
                continue;
            }

            argX = *xPosPtr + g_SensorsCeiling[i].x;
            argY = *yPosPtr + g_SensorsCeiling[i].y +
                   g_Player.colCeiling[i].unk10 + 1;
            CheckCollision(argX, argY, &collider, 0);
            // If in mist form, and collider is mist, then disable collision on
            // that collider!
            if (g_Player.status & PLAYER_STATUS_MIST_FORM &&
                collider.effects & EFFECT_MIST_ONLY) {
                collider.effects &= ~(EFFECT_UNK_0002 | EFFECT_SOLID);
            }
            collidereffects = collider.effects;
            if (!(collidereffects & 1)) {
                if ((g_Player.colCeiling[i].effects != EFFECT_SOLID) ||
                    (PLAYER.velocityY <= 0)) {
                    *vram_ptr |= 2;
                    if (!(*vram_ptr & 1) &&
                        ((g_Player.unk04 &
                          (EFFECT_SOLID_FROM_ABOVE | EFFECT_SOLID)) !=
                         (EFFECT_SOLID_FROM_ABOVE | EFFECT_SOLID))) {
                        if (g_Player.colCeiling[i].effects & EFFECT_UNK_8000) {
                            *yPosPtr += g_Player.colCeiling[i].unk10;
                        } else {
                            *yPosPtr += g_Player.colCeiling[i].unk20;
                        }
                    }
                    return;
                }
                continue;
            }
            if ((collidereffects &
                 (EFFECT_UNK_0800 | EFFECT_UNK_0002 | EFFECT_SOLID)) ==
                (EFFECT_UNK_0800 | EFFECT_SOLID)) {
                if (i < 2) {
                    *vram_ptr |= (EFFECT_UNK_0800 | EFFECT_UNK_0002 |
                                  ((collidereffects >> 4) &
                                   (EFFECT_UNK_0400 | EFFECT_UNK_0200 |
                                    EFFECT_UNK_0100)));
                    if (!(*vram_ptr & 1)) {
                        *yPosPtr +=
                            g_Player.colCeiling[i].unk10 + collider.unk20 + 1;
                    }
                    return;
                }
                if ((i == 2) &&
                    ((collidereffects &
                      (EFFECT_UNK_4000 | EFFECT_UNK_0800 | EFFECT_SOLID)) ==
                     (EFFECT_UNK_0800 | EFFECT_SOLID))) {
                    g_Player.colFloor[2].effects = collidereffects;
                    g_Player.colFloor[2].unk8 = g_Player.colFloor[2].unk10;
                }
                if ((i == 3) &&
                    ((collidereffects &
                      (EFFECT_UNK_4000 | EFFECT_UNK_0800 | EFFECT_SOLID)) ==
                     (EFFECT_UNK_4000 | EFFECT_UNK_0800 | EFFECT_SOLID))) {
                    g_Player.colFloor[3].effects = collidereffects;
                    g_Player.colFloor[3].unk8 = g_Player.colFloor[3].unk10;
                }
            }
            if ((collidereffects & EFFECT_UNK_0800) == EFFECT_NONE) {
                *vram_ptr |=
                    (EFFECT_UNK_0800 | EFFECT_UNK_0002 |
                     ((collidereffects >> 4) &
                      (EFFECT_UNK_0400 | EFFECT_UNK_0200 | EFFECT_UNK_0100)));
                if (!(*vram_ptr & 1)) {
                    *yPosPtr +=
                        g_Player.colCeiling[i].unk10 + collider.unk20 + 1;
                }
                return;
            }
        }
        if ((temp_s0 == (EFFECT_UNK_0800 | EFFECT_SOLID)) && (i < 2)) {
            *vram_ptr |=
                (EFFECT_UNK_0800 | EFFECT_UNK_0002 |
                 ((g_Player.colCeiling[i].effects >> 4) &
                  (EFFECT_UNK_0400 | EFFECT_UNK_0200 | EFFECT_UNK_0100)));
            if (!(*vram_ptr & 1)) {
                *yPosPtr += g_Player.colCeiling[i].unk20;
            }
            return;
        }
    }
    if (PLAYER.velocityY > 0) {
        return;
    }
    argX = *xPosPtr + g_SensorsCeiling[0].x;
    argY = (*yPosPtr + g_SensorsCeiling[0].y) - 10;
    CheckCollision(argX, argY, &collider, 0);
    if ((collider.effects & EFFECT_SOLID) != EFFECT_NONE) {
        return;
    }
    for (i = 2; i < NUM_HORIZONTAL_SENSORS; i++) {
        if ((g_Player.colCeiling[3].effects & EFFECT_UNK_0800) &&
            (g_Player.colCeiling[2].effects & EFFECT_UNK_0800)) {
            return;
        }
        temp_s0 = g_Player.colCeiling[i].effects;
        temp_fp = ((temp_s0 >> 4) &
                   (EFFECT_UNK_0400 | EFFECT_UNK_0200 | EFFECT_UNK_0100)) +
                  (EFFECT_UNK_0800 | EFFECT_UNK_0002);
        if (temp_s0 & EFFECT_UNK_0800) {
            if (i == 2) {
                var_a0 = EFFECT_UNK_4000;
                var_a1 = g_Player.colCeiling[2].unk4;
                temp_v1 = var_a1 + 8;
            } else {
                var_a0 = 0;
                var_a1 = g_Player.colCeiling[3].unkC;
                temp_v1 = 8 - var_a1;
            }
            if ((temp_s0 & EFFECT_UNK_4000) == var_a0) {
                argX = var_a1 + (*xPosPtr + g_SensorsCeiling[i].x);
                argY = *yPosPtr + g_SensorsCeiling[i].y;
                CheckCollision(argX, argY, &collider, 0);
                if (collider.effects & EFFECT_SOLID) {
                    *vram_ptr |= temp_fp;
                    if (!(*vram_ptr & 1)) {
                        *yPosPtr += collider.unk20;
                    }
                    return;
                }
            } else if ((temp_v1 > 0) && (temp_s0 & 1)) {
                argX = var_a1 + (*xPosPtr + g_SensorsCeiling[i].x);
                argY = *yPosPtr + g_SensorsCeiling[i].y +
                       g_Player.colCeiling[i].unk8;
                CheckCollision(argX, argY, &collider, 0);
                if (collider.effects & EFFECT_SOLID) {
                    if (!(*vram_ptr & 1)) {
                        *yPosPtr +=
                            collider.unk20 + g_Player.colCeiling[i].unk8;
                    }
                    *vram_ptr |= temp_fp;
                    return;
                }
            }
        }
    }
}

static void CheckWallRight(void) {
    Collider collider;
    s32 temp_s0;
    s32 i;

    s16 argX;
    s16 argY;

    s16* yPosPtr = &PLAYER.posY.i.hi;
    s16* xPosPtr = &PLAYER.posX.i.hi;
    s32* vram_ptr = &g_Player.pl_vram_flag;

    if (((g_StageId == STAGE_BO6) || (g_StageId == STAGE_RBO6) ||
         (g_StageId == STAGE_DRE)) &&
        (*xPosPtr >= 0xF8)) {
        *xPosPtr = 0xF8;
        *vram_ptr |= 4;
        return;
    }

    if (g_unkGraphicsStruct.unk18) {
        return;
    }
    temp_s0 =
        g_Player.unk04 & (EFFECT_UNK_8000 | EFFECT_UNK_4000 | EFFECT_UNK_0800 |
                          EFFECT_UNK_0400 | EFFECT_UNK_0002 | EFFECT_SOLID);
    if ((temp_s0 == (EFFECT_UNK_8000 | EFFECT_UNK_0002 | EFFECT_SOLID)) ||
        (temp_s0 == (EFFECT_UNK_0800 | EFFECT_UNK_0002 | EFFECT_SOLID)) ||
        (temp_s0 == (EFFECT_UNK_8000 | EFFECT_UNK_0800 | EFFECT_UNK_0002 |
                     EFFECT_SOLID))) {
        *vram_ptr |= 4;
        return;
    }

    for (i = 0; i < NUM_VERTICAL_SENSORS; i++) {
        temp_s0 = g_Player.colWall[i].effects &
                  (EFFECT_UNK_8000 | EFFECT_UNK_4000 | EFFECT_UNK_0800 |
                   EFFECT_UNK_0002 | EFFECT_SOLID);
        if ((temp_s0 == (EFFECT_UNK_8000 | EFFECT_UNK_4000 | EFFECT_SOLID)) ||
            (temp_s0 == (EFFECT_UNK_8000 | EFFECT_UNK_4000 | EFFECT_UNK_0002 |
                         EFFECT_SOLID)) ||
            (temp_s0 == (EFFECT_UNK_4000 | EFFECT_UNK_0800 | EFFECT_SOLID)) ||
            (temp_s0 == (EFFECT_UNK_4000 | EFFECT_UNK_0800 | EFFECT_UNK_0002 |
                         EFFECT_SOLID)) ||
            (temp_s0 == (EFFECT_UNK_8000 | EFFECT_UNK_0002 | EFFECT_SOLID)) ||
            (temp_s0 == (EFFECT_UNK_0800 | EFFECT_UNK_0002 | EFFECT_SOLID)) ||
            (temp_s0 == (EFFECT_UNK_0002 | EFFECT_SOLID))) {
            argX = *xPosPtr + g_SensorsWall[i].x + g_Player.colWall[i].unk4 - 1;
            argY = *yPosPtr + g_SensorsWall[i].y;
            CheckCollision(argX, argY, &collider, 0);
            if ((collider.effects & EFFECT_SOLID) == EFFECT_NONE) {
                *vram_ptr |= 4;
                *xPosPtr += g_Player.colWall[i].unk4;
                return;
            }
        }

        if (!(*vram_ptr & 1)) {
            if ((temp_s0 & (EFFECT_UNK_8000 | EFFECT_UNK_4000 |
                            EFFECT_UNK_0800)) == EFFECT_UNK_8000 &&
                (i != 0) &&
                ((g_Player.colWall[0].effects & EFFECT_UNK_0800) ||
                 !(g_Player.colWall[0].effects &
                   (EFFECT_UNK_8000 | EFFECT_UNK_0800 | EFFECT_UNK_0002)))) {
                *vram_ptr |= 4;
                *xPosPtr += g_Player.colWall[i].unk4;
                return;
            }
            if (((temp_s0 & (EFFECT_UNK_8000 | EFFECT_UNK_4000 |
                             EFFECT_UNK_0800)) == EFFECT_UNK_0800) &&
                (i != 6) &&
                ((g_Player.colWall[6].effects & EFFECT_UNK_8000) ||
                 !(g_Player.colWall[6].effects &
                   (EFFECT_UNK_8000 | EFFECT_UNK_0800 | EFFECT_UNK_0002)))) {
                *vram_ptr |= 4;
                *xPosPtr += g_Player.colWall[i].unk4;
                return;
            }
        }
    }
}

static void CheckWallLeft(void) {
    Collider collider;
    s32 temp_s0;
    s32 i;
    s16 argX;
    s16 argY;

    s16* yPosPtr = &PLAYER.posY.i.hi;
    s16* xPosPtr = &PLAYER.posX.i.hi;
    s32* vram_ptr = &g_Player.pl_vram_flag;

    if (((g_StageId == STAGE_BO6) || (g_StageId == STAGE_RBO6) ||
         (g_StageId == STAGE_DRE)) &&
        (*xPosPtr <= 8)) {
        *xPosPtr = 8;
        *vram_ptr |= 8;
        return;
    }

    if (g_unkGraphicsStruct.unk18) {
        return;
    }
    temp_s0 =
        g_Player.unk04 & (EFFECT_UNK_8000 | EFFECT_UNK_4000 | EFFECT_UNK_0800 |
                          EFFECT_UNK_0400 | EFFECT_UNK_0002 | EFFECT_SOLID);
    if ((temp_s0 == (EFFECT_UNK_8000 | EFFECT_UNK_4000 | EFFECT_UNK_0002 |
                     EFFECT_SOLID)) ||
        (temp_s0 == (EFFECT_UNK_0800 | EFFECT_UNK_0400 | EFFECT_UNK_0002 |
                     EFFECT_SOLID)) ||
        (temp_s0 == (EFFECT_UNK_8000 | EFFECT_UNK_4000 | EFFECT_UNK_0800 |
                     EFFECT_UNK_0400 | EFFECT_UNK_0002 | EFFECT_SOLID))) {
        *vram_ptr |= 8;
        return;
    }
    for (i = NUM_VERTICAL_SENSORS; i < NUM_VERTICAL_SENSORS * 2; i++) {
        temp_s0 = g_Player.colWall[i].effects &
                  (EFFECT_UNK_8000 | EFFECT_UNK_4000 | EFFECT_UNK_0800 |
                   EFFECT_UNK_0002 | EFFECT_SOLID);
        if ((temp_s0 == (EFFECT_UNK_8000 | EFFECT_SOLID)) ||
            (temp_s0 == (EFFECT_UNK_8000 | EFFECT_UNK_0002 | EFFECT_SOLID)) ||
            (temp_s0 == (EFFECT_UNK_0800 | EFFECT_SOLID)) ||
            (temp_s0 == (EFFECT_UNK_0800 | EFFECT_UNK_0002 | EFFECT_SOLID)) ||
            (temp_s0 == (EFFECT_UNK_8000 | EFFECT_UNK_4000 | EFFECT_UNK_0002 |
                         EFFECT_SOLID)) ||
            (temp_s0 == (EFFECT_UNK_4000 | EFFECT_UNK_0800 | EFFECT_UNK_0002 |
                         EFFECT_SOLID)) ||
            (temp_s0 == (EFFECT_UNK_0002 | EFFECT_SOLID))) {
            argX = *xPosPtr + g_SensorsWall[i].x + g_Player.colWall[i].unkC + 1;
            argY = *yPosPtr + g_SensorsWall[i].y;
            CheckCollision(argX, argY, &collider, 0);
            if ((collider.effects & EFFECT_SOLID) == EFFECT_NONE) {
                *vram_ptr |= 8;
                *xPosPtr += g_Player.colWall[i].unkC;
                return;
            }
        }
        if (!(*vram_ptr & 1)) {
            if (((temp_s0 &
                  (EFFECT_UNK_8000 | EFFECT_UNK_4000 | EFFECT_UNK_0800)) ==
                 (EFFECT_UNK_8000 | EFFECT_UNK_4000)) &&
                (i != 7) &&
                ((g_Player.colWall[NUM_VERTICAL_SENSORS].effects &
                  EFFECT_UNK_0800) ||
                 !(g_Player.colWall[NUM_VERTICAL_SENSORS].effects &
                   (EFFECT_UNK_8000 | EFFECT_UNK_0800 | EFFECT_UNK_0002)))) {
                *vram_ptr |= 8;
                *xPosPtr += g_Player.colWall[i].unkC;
                return;
            }
            if (((temp_s0 &
                  (EFFECT_UNK_8000 | EFFECT_UNK_4000 | EFFECT_UNK_0800)) ==
                 (EFFECT_UNK_4000 | EFFECT_UNK_0800)) &&
                (i != 13) &&
                ((g_Player.colWall[NUM_VERTICAL_SENSORS + 6].effects &
                  EFFECT_UNK_8000) ||
                 !(g_Player.colWall[NUM_VERTICAL_SENSORS + 6].effects &
                   (EFFECT_UNK_8000 | EFFECT_UNK_0800 | EFFECT_UNK_0002)))) {
                *vram_ptr |= 8;
                *xPosPtr += g_Player.colWall[i].unkC;
                return;
            }
        }
    }
}

void SetPlayerStep(PlayerSteps step) {
    PLAYER.step = step;
    PLAYER.step_s = 0;
}
