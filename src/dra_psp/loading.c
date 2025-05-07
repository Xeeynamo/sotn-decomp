// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../dra/dra.h"
#include "../dra/dra_bss.h"
#include "servant.h"

void func_8932CEC(bool, s8);

extern NowLoadingModel g_NowLoadingModel;
extern Weapon D_8017A000;
extern Weapon D_8017D000;
extern s32 D_8C630D4;
extern u8 D_8D2FC40;
extern u8 D_8D3FC40;
extern u8 D_8D41C40;
extern u8 D_psp_091463F8;
extern u8 D_psp_09146400;
extern u8 D_psp_09146401;
extern char D_psp_0914C3A8[];
extern char D_psp_0914C3B8[];
extern char D_psp_0914C3C8[];
extern RECT D_psp_09156F40;
extern u32 D_psp_09156F48;
extern s32 D_psp_0915AF48;

static u8 loading_fr[] = {
#include "../dra/gen_loading_fr.h"
};

static u8 loading_it[] = {
#include "../dra/gen_loading_it.h"
};

static u8 loading_ge[] = {
#include "../dra/gen_loading_ge.h"
};

static u8 loading_sp[] = {
#include "../dra/gen_loading_sp.h"
};

static u_long* D_psp_0915E4E8[] = {
    (u_long*)GFX_BANK_COMPRESSED,
    GFX_ENTRY(0x180, 0x2A0, 128, 128, loading_sp),
    GFX_TERMINATE(),
};

static char* D_psp_0915E500[] = {
    D_psp_0914C3A8, D_psp_0914C3B8, D_psp_0914C3C8};

void AnimateNowLoading(NowLoadingModel* self, s16 x, s16 y, bool isDone) {
    RECT sp48;
    s32 horizontalWave;
    s16 sy;
    s16 sx;
    s16 ey;
    Primitive* prim;
    s16 verticalWave;
    s16 posY;
    s16 posX;
    s16 angle;
    s32 primIndex;
    s32 i;
    s16 ex;
    s32 baseY;

    sp48.x = 0x740;
    sp48.y = 0x80;
    sp48.w = 0x40;
    sp48.h = 0x40;

    LoadImage(&sp48, (u_long*)&D_psp_09156F48);
    func_89264CC(0x81D0, &D_psp_0915AF48, 1);
    D_psp_0915E4E8[3] = (u_long*)func_psp_090F6368(
        NULL, loading_fr, loading_sp, loading_ge, loading_it);
    if (D_psp_0915E4E8[3] != NULL) {
        func_psp_091040A0(D_psp_0915E4E8);
    }
    switch (self->step) {
    case 0:
        self->primIndex =
            (s16)AllocPrimitives(PRIM_GT4, NOW_LOADING_PRIM_COUNT + 1);
        if (self->primIndex == -1) {
            return;
        }
        prim = &g_PrimBuf[self->primIndex];
        for (i = 0; i < NOW_LOADING_PRIM_COUNT; i++) {
            self->waveTable[i] = i << 8;
            prim->v0 = prim->v1 = 0xE8;
            prim->v2 = prim->v3 = 0xFF;
            prim->u0 = (i * 8) + 0x80;
            prim->u1 = ((i + 1) * 8) + 0x80;
            if (i == NOW_LOADING_PRIM_COUNT - 1) {
                prim->u1 = 0xFF;
            }
            prim->u2 = prim->u0;
            prim->u3 = prim->u1;
            prim->tpage = 0x1A;
            prim->clut = 0x19F;
            prim->priority = 0x1FE;
            prim->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_TRANSP;
            prim = prim->next;
        }
        prim->v0 = prim->v1 = 0x80;
        prim->v2 = prim->v3 = 0xBF;
        prim->u2 = prim->u0 = 0;
        prim->u3 = prim->u1 = 0x7F;
        prim->y0 = prim->y1 = 0xA0;
        prim->y2 = prim->y3 = 0xDF;
        prim->x2 = prim->x0 = 0x70;
        prim->x3 = prim->x1 = 0xEF;
        prim->tpage = 0x9D;
        prim->clut = 0x1D0;
        prim->priority = 0x1FE;
        prim->drawMode = DRAW_DEFAULT;
        self->x = x;
        self->y = y;
        self->unkC = 0;
        self->verticalWave = 4;
        self->horizontalWave = 4;
        self->unk12 = 0;
        self->speed = 0x20;
        self->step++;
        break;
    case 1:
        if (isDone) {
            FreePrimitives(self->primIndex);
            self->step = 0;
            ClearImage(&D_psp_09156F40, 0, 0, 0);
            return;
        }
        if (g_pads[0].pressed & PAD_UP) {
            self->verticalWave++;
            if (self->verticalWave > 0x40) {
                self->verticalWave = 0x40;
            }
        }
        if (g_pads[0].pressed & PAD_DOWN) {
            self->verticalWave--;
            if (self->verticalWave < -0x40) {
                self->verticalWave = -0x40;
            }
        }
        if (g_pads[0].pressed & PAD_RIGHT) {
            self->horizontalWave++;
            if (self->horizontalWave > 0x40) {
                self->horizontalWave = 0x40;
            }
        }
        if (g_pads[0].pressed & PAD_LEFT) {
            self->horizontalWave--;
            if (self->horizontalWave < -0x40) {
                self->horizontalWave = -0x40;
            }
        }
        break;
    case 2:
    case 3:
        break;
    }
    posX = self->x;
    posY = self->y;
    prim = &g_PrimBuf[self->primIndex];
    verticalWave = self->verticalWave;
    horizontalWave = self->horizontalWave;
    baseY = posY + 0x18;
    for (i = 0; i < NOW_LOADING_PRIM_COUNT; i++) {
        angle = self->waveTable[i];
        sy = -(rsin(angle) >> 5) * verticalWave / 0x100;
        sx = (rcos(angle) >> 5) * horizontalWave / 0x100;
        angle = self->waveTable[(i + 1) % NOW_LOADING_PRIM_COUNT];
        ey = -(rsin(angle) >> 5) * verticalWave / 0x100;
        ex = (rcos(angle) >> 5) * horizontalWave / 0x100;
        prim->x0 = sx + (posX + prim->u0) - 0x80;
        prim->x1 = ex + (posX + prim->u1) - 0x80;
        prim->x2 = sx + (posX + prim->u2) - 0x80;
        prim->x3 = ex + (posX + prim->u3) - 0x80;
        prim->y0 = posY + sy;
        prim->y1 = posY + ey;
        prim->y2 = baseY + sy;
        prim->y3 = baseY + ey;
        self->waveTable[i] += self->speed;
        prim = prim->next;
    }
}

void InitializeServant(InitializeMode mode) {
    if (g_Servant != 0) {
        g_ServantDesc.Init(mode);
    }
}

void func_800E6250(void) {
    if (g_Servant != 0) {
        while (func_psp_090FAB30(g_Servant - 1, SimFileType_FamiliarPrg, true))
            ;
        while (func_psp_090FAB30(g_Servant - 1, SimFileType_FamiliarChr, true))
            ;
        while (func_psp_090FAB30(
            ((g_Servant + 2) * 2) + 0x8000, SimFileType_Vh, true))
            ;
        while (func_psp_090FAB30(
            ((g_Servant + 2) * 2) + 0x8001, SimFileType_Vb, true))
            ;
    }
}

s32 func_800E6300(void) {
    s32 i;

    for (i = 0; i < LEN(g_Status.relics); i++) {
        s32 servantId = g_RelicDefs[i].unk0C;
        if (servantId > 0 && g_Status.relics[i] & RELIC_FLAG_ACTIVE) {
            return servantId;
        }
    }
    return 0;
}

void HandleNowLoading(void) {
    void (*pfnWeapon)(s32);
    s32 weaponId, weaponId1, weaponId2;

    NowLoadingModel* nowLoadingModel = &g_NowLoadingModel;

    if (g_GameStep >= 4 && g_GameStep < 16) {
        AnimateNowLoading(nowLoadingModel, 0x40, 0x70, false);
    }
    switch (g_GameStep) {
    case 0:
        D_8003C730 = 0;
        D_80097924 = -1;
        D_8006C378 = -1;
        ClearBackbuffer();
        SetStageDisplayBuffer();
        g_GameStep++;
        g_GameEngineStep = Engine_Init;
        break;
    case 1:
        if (g_pads[0].repeat & PAD_RIGHT) {
            PlaySfx(SFX_DEBUG_SELECT);
            D_800987B4 += 1;
        }
        if (g_pads[0].repeat & PAD_DOWN) {
            PlaySfx(SFX_DEBUG_SELECT);
            D_800987B4 += 8;
        }
        if (g_pads[0].repeat & PAD_LEFT) {
            PlaySfx(SFX_DEBUG_SELECT);
            D_800987B4 -= 1;
        }
        if (g_pads[0].repeat & PAD_UP) {
            PlaySfx(SFX_DEBUG_SELECT);
            D_800987B4 -= 8;
        }
        if (g_pads[0].repeat & PAD_SELECT) {
            g_PlayableCharacter++;
            g_PlayableCharacter %= 3;
        }
        if (D_800987B4 < 0) {
            D_800987B4 = 0x39;
        }
        if (D_800987B4 >= 0x3AU) {
            D_800987B4 = 0;
        }
        g_StageId = g_StageSelectOrder[D_800987B4];
        FntPrint("Player:%s\n", D_psp_0915E500[g_PlayableCharacter]);
        FntPrint("%02x (%02x)\n", D_800987B4, g_StageId);
        if (g_StageId == STAGE_MEMORYCARD) {
            FntPrint("memory card load\n");
        } else if ((g_StageId >= 0xF0) && (g_StageId < 0xFF)) {
            FntPrint("ending(type%d)\n", g_StageId - 0xF0);
        } else if (g_StageId == STAGE_IWA_LOAD) {
            FntPrint("iwa load\n");
        } else if (g_StageId == STAGE_IGA_LOAD) {
            FntPrint("iga load\n");
        } else if (g_StageId == STAGE_HAGI_LOAD) {
            FntPrint("hagi load\n");
        } else {
            FntPrint("load:c:\\bin\\%s.bin\n", g_StagesLba[g_StageId].ovlName);
        }
        if (g_pads[0].tapped & PAD_START) {
            PlaySfx(SFX_START_SLAM_B);
            if (g_StageId == STAGE_MEMORYCARD) {
                SetGameState(Game_MainMenu);
            } else if ((g_StageId >= 0xF0) && (g_StageId < 0xFF)) {
                D_800978B4 = g_StageId - 0xF0;
                SetGameState(Game_Ending);
            } else {
                STRCPY(g_Status.saveName, D_psp_0914C3A8);
                g_DemoMode = Demo_None;
                if (g_DebugPlayer != 0) {
                    STRCPY(
                        g_Status.saveName, D_psp_0915E500[g_PlayableCharacter]);
                    g_IsTimeAttackUnlocked = true;
                    if (g_PlayableCharacter == PLAYER_RICHTER) {
                        STRCPY(g_Status.saveName, D_psp_0914C3B8);
                        g_PlayableCharacter = PLAYER_RICHTER;
                        g_IsTimeAttackUnlocked = true;
                    } else if (g_PlayableCharacter == PLAYER_MARIA) {
                        STRCPY(g_Status.saveName, D_psp_0914C3C8);
                        g_PlayableCharacter = PLAYER_MARIA;
                        g_IsTimeAttackUnlocked = true;
                    } else {
                        g_PlayableCharacter = PLAYER_ALUCARD;
                        g_IsTimeAttackUnlocked = false;
                    }
                    if (D_8C630D4 == 1) {
                        DemoInit(1);
                    } else if (D_8C630D4 == 2) {
                        DemoInit(0);
                    }
                }
                g_GameStep++;
            }
        }
        break;
    case 2:
        if (g_StageId == STAGE_ST0 || g_PlayableCharacter != PLAYER_ALUCARD) {
            if (g_PlayableCharacter == PLAYER_MARIA) {
                func_8932FD4(2);
            } else if (g_StageId == STAGE_ST0) {
                func_8932FD4(3);
            } else {
                func_8932FD4(1);
            }
        } else {
            func_8932FD4(0);
        }
        g_GameStep = 0x64;
        break;

    case 0x64:
        if (!func_8933000()) {
            break;
        }
        D_800978C4 = 0;
        if (g_IsUsingCd) {
            break;
        }
        if (g_UseDisk) {
            g_CdStep = CdStep_LoadInit;
            g_LoadFile = CdFile_GameChr;
        } else {
            if (g_StageId == STAGE_ST0 ||
                g_PlayableCharacter != PLAYER_ALUCARD) {
                if (g_PlayableCharacter == PLAYER_MARIA) {
                    if (func_psp_090FAB30(5, SimFileType_System, true) < 0) {
                        break;
                    }
                    if (func_psp_090FAB30(0x8014, SimFileType_Vh, true) < 0) {
                        break;
                    }
                    if (func_psp_090FAB30(0x8015, SimFileType_Vb, true) < 0) {
                        break;
                    }
                } else {
                    if (func_psp_090FAB30(5, SimFileType_System, true) < 0) {
                        break;
                    }
                    if (func_psp_090FAB30(0x8002, SimFileType_Vh, true) < 0) {
                        break;
                    }
                    if (func_psp_090FAB30(0x8003, SimFileType_Vb, true) < 0) {
                        break;
                    }
                    if (g_StageId == STAGE_ST0) {
                        // BUGS: wrong signature
                        if (LoadFileSim(0x8004, SimFileType_Vh, true) < 0) {
                            break;
                        }
                        if (LoadFileSim(0x8005, SimFileType_Vb, true) < 0) {
                            break;
                        }
                    }
                }
            } else {
                if (func_psp_090FAB30(4, SimFileType_System, true) < 0) {
                    break;
                }
                if (func_psp_090FAB30(0x8000, SimFileType_Vh, true) < 0) {
                    break;
                }
                if (func_psp_090FAB30(0x8001, SimFileType_Vb, true) < 0) {
                    break;
                }
            }
        }
        g_GameStep = 3;
        break;
    case 3:
        if (g_StageId == STAGE_ST0 || g_PlayableCharacter != PLAYER_ALUCARD) {
            func_8933130(1);
        } else {
            func_8933130(0);
        }
        g_GameStep = 0x65;
        break;

    case 0x65:
        if (!func_893315C()) {
            break;
        }
        if (g_UseDisk) {
            if (g_IsUsingCd) {
                break;
            }
        } else {
            if (g_StageId == STAGE_ST0 ||
                g_PlayableCharacter != PLAYER_ALUCARD) {
                if (func_psp_090FAB30(13, SimFileType_System, true) < 0) {
                    break;
                }
            } else {
                if (func_psp_090FAB30(1, SimFileType_System, true) < 0) {
                    break;
                }
            }
            func_891CEB8(0, 0xFD);
        }
        func_8932AD4(g_StageId);
        g_GameStep = 4;
        break;
    case 4:
        if (!func_8932B74(g_GameStep, 5)) {
            break;
        }
        if (g_UseDisk) {
            g_CdStep = CdStep_LoadInit;
            g_LoadFile = CdFile_StageChr;
            g_LoadOvlIdx = g_StageId;
        }
        g_GameStep++;
        break;
    case 5:
        if (g_UseDisk) {
            if (g_IsUsingCd) {
                break;
            }
        } else {
            if (func_psp_090FAB30(0, SimFileType_StageChr, true) < 0) {
                break;
            }
        }
        g_GameStep++;
        break;
    case 6:
        if (g_UseDisk) {
            g_CdStep = CdStep_LoadInit;
            g_LoadFile = CdFile_StageSfx;
        }
        g_GameStep++;
        break;
    case 7:
        if (g_UseDisk) {
            if (g_IsUsingCd) {
                break;
            }
        } else {
            if (func_psp_090FAB30(0, SimFileType_Vh, true) < 0) {
                break;
            }
            if (func_psp_090FAB30(0, SimFileType_Vb, true) < 0) {
                break;
            }
        }
        g_GameStep++;
        break;
    case 8:
        if (g_UseDisk) {
            g_CdStep = CdStep_LoadInit;
            g_LoadFile = CdFile_StagePrg;
        }
        g_GameStep++;
        break;
    case 9:
        if (g_UseDisk) {
            if (g_IsUsingCd) {
                break;
            }
        } else {
            if (func_psp_090FAB30(0, SimFileType_StagePrg, true) < 0) {
                break;
            }
            if (g_StagesLba[g_StageId].seqIdx >= 0 &&
                LoadFileSim(g_StagesLba[g_StageId].seqIdx, 4) < 0) {
                break;
            }
        }
        g_GameStep++;
        break;
    case 10:
        if (g_DemoMode == Demo_None) {
            InitStatsAndGear(0);
        }
        g_Servant = 0;
        g_ServantLoaded = 0;
        g_EquippedWeaponIds[0] = -1;
        g_EquippedWeaponIds[1] = -1;
        if (g_StageId == STAGE_ST0 || g_PlayableCharacter != PLAYER_ALUCARD) {
            g_GameStep = 0x10;
        } else {
            g_CdStep = CdStep_LoadInit;
            g_LoadFile = CdFile_Weapon0;
            weaponId = g_EquipDefs[g_Status.equipment[LEFT_HAND_SLOT]].weaponId;
            if (weaponId == 0xFF) {
                weaponId = 1;
            }
            if (g_Status.equipment[ARMOR_SLOT] == ITEM_AXE_LORD_ARMOR) {
                weaponId = g_EquipDefs[0xD8].weaponId;
                weaponId1 = weaponId;
                weaponId2 = weaponId;
            } else {
                weaponId1 =
                    g_EquipDefs[g_Status.equipment[LEFT_HAND_SLOT]].weaponId;
                if (weaponId1 == 0xFF) {
                    weaponId1 = 1;
                }
                weaponId2 =
                    g_EquipDefs[g_Status.equipment[RIGHT_HAND_SLOT]].weaponId;
                weaponId2 = weaponId2 == 0xFF ? 1 : weaponId2;
            }
            g_EquippedWeaponIds[0] = weaponId;
            func_8932CEC(0, weaponId1);
            func_8932CEC(1, weaponId2);
            g_GameStep++;
        }
        break;
    case 11:
        if (!func_8932D34(0)) {
            break;
        }
        if (!func_8932D34(1)) {
            break;
        }
        if (g_UseDisk) {
            if (g_IsUsingCd) {
                break;
            }
            pfnWeapon = D_8017A000.LoadWeaponPalette;
            pfnWeapon(g_EquipDefs[g_EquippedWeaponIds[0]].palette);
        } else {
            weaponId = g_EquipDefs[g_Status.equipment[LEFT_HAND_SLOT]].weaponId;
            if (weaponId == 0xFF) {
                weaponId = 1;
            }
            if (g_Status.equipment[ARMOR_SLOT] == ITEM_AXE_LORD_ARMOR) {
                weaponId = g_EquipDefs[0xD8].weaponId;
            }
            if (func_psp_090FAB30(weaponId, SimFileType_Weapon0Prg, true) < 0) {
                break;
            }
            g_EquippedWeaponIds[0] = weaponId;
            pfnWeapon = D_8017A000.LoadWeaponPalette;
            pfnWeapon(g_EquipDefs[g_EquippedWeaponIds[0]].palette);
            weaponId =
                g_EquipDefs[g_Status.equipment[RIGHT_HAND_SLOT]].weaponId;
            if (weaponId == 0xFF) {
                weaponId = 1;
            }
            if (g_Status.equipment[ARMOR_SLOT] == ITEM_AXE_LORD_ARMOR) {
                weaponId = g_EquipDefs[0xD8].weaponId;
            }
            if (func_psp_090FAB30(weaponId, SimFileType_Weapon1Prg, true) < 0) {
                break;
            }
            g_EquippedWeaponIds[1] = weaponId;
            pfnWeapon = D_8017D000.LoadWeaponPalette;
            pfnWeapon(g_EquipDefs[g_EquippedWeaponIds[1]].palette);
        }
        g_GameStep++;
        break;
    case 12:
        if (g_UseDisk) {
            g_CdStep = CdStep_LoadInit;
            g_LoadFile = CdFile_Weapon1;
            weaponId =
                g_EquipDefs[g_Status.equipment[RIGHT_HAND_SLOT]].weaponId;
            if (weaponId == 0xFF) {
                weaponId = 1;
            }
            if (g_Status.equipment[ARMOR_SLOT] == ITEM_AXE_LORD_ARMOR) {
                weaponId = g_EquipDefs[0xD8].weaponId;
            }
            g_EquippedWeaponIds[1] = weaponId;
        }
        g_GameStep++;
        break;
    case 13:
        if (g_UseDisk) {
            if (g_IsUsingCd) {
                break;
            }
            pfnWeapon = D_8017D000.LoadWeaponPalette;
            pfnWeapon(g_EquipDefs[g_EquippedWeaponIds[1]].palette);
        } else {
            if (func_psp_090FAB30(
                    g_EquippedWeaponIds[0], SimFileType_Weapon0Chr, true) < 0) {
                break;
            }
            if (func_psp_090FAB30(
                    g_EquippedWeaponIds[1], SimFileType_Weapon1Chr, true) < 0) {
                break;
            }
        }
        CheckWeaponCombo();
        g_GameStep++;
        break;
    case 14:
        g_Servant = func_800E6300();
        if (g_Servant == 0) {
            g_GameStep += 2;
            break;
        }
        if (g_UseDisk) {
            g_CdStep = CdStep_LoadInit;
            g_LoadFile = CdFile_ServantChr;
            g_LoadOvlIdx = g_Servant - 1;
        }
        func_8932E78(g_Servant - 1);
        g_GameStep++;
        break;
    case 15:
        if (!func_8932EA4()) {
            break;
        }
        if (g_UseDisk) {
            if (g_IsUsingCd) {
                break;
            }
        } else {
            func_800E6250();
        }
        g_ServantLoaded = g_Servant;
        g_GameStep++;
        break;
    case 16:
        AnimateNowLoading(nowLoadingModel, 64, 112, true);
        if (D_8003C730 != 4) {
            if (g_StageId > 0x34) {
                D_8006C374 = g_StagesLba[g_StageId].unk28;
            } else {
                D_8006C374 =
                    g_StagesLba[g_StageId & (u8)~STAGE_INVERTEDCASTLE_FLAG]
                        .unk28;
            }
        }
        if (g_StageId == STAGE_NO3 && g_PlayableCharacter != PLAYER_ALUCARD) {
            D_8006C374 = 0x11;
            g_CastleFlags[PROLOGUE_COMPLETE] = 1;
        }
        D_800978C4 = 1;
        SetGameState(Game_Play);
        break;
    }
}

static u8 intro_left_sp[] = {
#include "../dra/gen_intro_left_sp.h"
};

static u8 intro_left_it[] = {
#include "../dra/gen_intro_left_it.h"
};

static u8 intro_left_ge[] = {
#include "../dra/gen_intro_left_ge.h"
};

static u8 intro_left_fr[] = {
#include "../dra/gen_intro_left_fr.h"
};

static u8 intro_right_sp[] = {
#include "../dra/gen_intro_right_sp.h"
};

static u8 intro_right_it[] = {
#include "../dra/gen_intro_right_it.h"
};

static u8 intro_right_ge[] = {
#include "../dra/gen_intro_right_ge.h"
};

static u8 intro_right_fr[] = {
#include "../dra/gen_intro_right_fr.h"
};

static u_long* D_psp_0915FBF8[] = {
    (u_long*)GFX_BANK_COMPRESSED,
    GFX_ENTRY(0x100, 0x300, 128, 128, intro_left_sp),
    GFX_TERMINATE(),
};
static u_long* D_psp_0915FC10[] = {
    (u_long*)GFX_BANK_COMPRESSED,
    GFX_ENTRY(0x100, 0x320, 128, 128, intro_right_sp),
    GFX_TERMINATE(),
};

void HandleVideoPlayback(void) {
    Primitive* prim;
    Primitive* prim2;
    u8 temp;

    if (!(g_pads[0].tapped & PAD_START) || !g_IsTimeAttackUnlocked) {
        switch (g_GameStep) {
        case 0:
            if (!g_IsUsingCd) {
                func_800EA538(0);
                func_800EA5E4(0x1A);
                D_psp_0915FBF8[3] = (u_long*)func_psp_090F6368(
                    NULL, intro_left_fr, intro_left_sp, intro_left_ge,
                    intro_left_it);
                if (D_psp_0915FBF8[3] != NULL) {
                    func_psp_091040A0(D_psp_0915FBF8);
                }
                D_psp_0915FC10[3] = (u_long*)func_psp_090F6368(
                    NULL, intro_right_fr, intro_right_sp, intro_right_ge,
                    intro_right_it);
                if (D_psp_0915FC10[3] != NULL) {
                    func_psp_091040A0(D_psp_0915FC10);
                }
                g_CdStep = CdStep_LoadInit;
                g_LoadFile = CdFile_24;
                SetCgiDisplayBuffer(0x140);
                D_8013640C = (s16)AllocPrimitives(PRIM_GT4, 2);
                prim = &g_PrimBuf[D_8013640C];
                SetTexturedPrimRect(prim, 44, 96, 232, 32, 0, 0);
                func_801072BC(prim);
                prim->tpage = 0x1C;
                prim->drawMode = DRAW_COLORS;
                prim->p1 = 0x40;
                prim = prim->next;
                SetTexturedPrimRect(prim, 60, 208, 192, 16, 0, 32);
                func_801072DC(prim);
                prim->tpage = 0x1C;
                prim->drawMode = DRAW_HIDE;
                g_GameStep++;
            }
            break;

        case 1:
            prim = &g_PrimBuf[D_8013640C];
            prim->p1--;
            if (prim->p1 == 0) {
                g_GameStep++;
            }
            break;

        case 2:
            prim = &g_PrimBuf[D_8013640C];
            temp = prim->r0 + 1;
            func_80107250(prim, temp);
            if (temp == 128) {
                prim->p1 = 128;
                g_GameStep++;
            }
            break;

        case 3:
            prim = &g_PrimBuf[D_8013640C];
            prim->p1--;
            if (prim->p1 == 0) {
                g_GameStep++;
            }
            break;

        case 4:
            prim = &g_PrimBuf[D_8013640C];
            temp = prim->r0 - 1;
            func_80107250(prim, temp);
            if (temp == 64) {
                prim2 = prim->next;
                prim2->drawMode = DRAW_HIDE;
            }
            if (temp == 0) {
                FreePrimitives(D_8013640C);
                g_GameStep++;
            }
            break;

        case 5:
            if (!g_UseDisk || !g_IsUsingCd) {
                D_8003C728 = 1;
                g_CurrentStream = 1;
                g_GameStep++;
            }
            break;

        case 6:
            g_api.o.UpdateRoomPosition();
            if (!D_8003C728) {
                goto hack;
            }
            break;
        }
    } else {
    hack:
        func_800E4970();
    }
}

void nullsub_9(void) {}

void HandlePrologueEnd(void) {
    switch (g_GameStep) {
    case 1:
        if (g_UseDisk) {
            if (g_IsUsingCd) {
                break;
            }
        } else {
            if (LoadFileSim(6, SimFileType_System) < 0 ||
                LoadFileSim(7, SimFileType_System) < 0) {
                break;
            }
        }
        if (func_80131F68()) {
            PlaySfx(0x80);
        }
        SetGPUBuffRGBZero();
        g_GameStep++;
        return;
    }
    g_api.o.StageEndCutScene();
}

void MainMenuHandler(void) {
    switch (g_GameStep) {
    case 0:
        g_StageId = STAGE_SEL;
        if (g_UseDisk) {
            g_CdStep = CdStep_LoadInit;
            g_LoadFile = CdFile_StageChr;
            g_LoadOvlIdx = STAGE_SEL;
        }
        g_GameStep++;
        break;
    case 1:
        if (g_UseDisk) {
            if (g_IsUsingCd) {
                break;
            }
        } else {
            if (LoadFileSim(12, SimFileType_System) < 0) {
                break;
            }
        }
        g_GameStep++;
        break;
    case 2:
        if (g_UseDisk) {
            g_CdStep = CdStep_LoadInit;
            g_LoadFile = CdFile_StageSfx;
        }
        g_GameStep++;
        break;
    case 3:
        if (g_UseDisk) {
            if (g_IsUsingCd) {
                break;
            }
        } else {
            if (LoadFileSim(0, SimFileType_Vh) < 0 ||
                LoadFileSim(0, SimFileType_Vb) < 0) {
                break;
            }
        }
        g_GameStep++;
        break;
    case 4:
        if (g_UseDisk) {
            g_CdStep = CdStep_LoadInit;
            g_LoadFile = CdFile_StagePrg;
        }
        g_GameStep++;
        break;
    case 5:
        if (g_UseDisk) {
            if (g_IsUsingCd) {
                break;
            }
        } else {
            if (LoadFileSim(0, SimFileType_StagePrg) < 0) {
                break;
            }
        }
        g_GameStep++;
        g_GameEngineStep = Engine_Init;
        break;
    case 6:
        g_api.o.Update();
        break;
    case 7:
        func_800E4970();
        break;
    }
}

void HandleEnding(void) {
    switch (g_GameStep) {
    case 0:
        DestroyEntitiesFromIndex(0);
        func_800EA538(0);
        ResetPendingGfxLoad();
        DestroyAllPrimitives();
        func_800EDAE4();
        HideAllBackgroundLayers();
        func_800EAD7C();
        ClearBackbuffer();
        SetStageDisplayBuffer();
        g_StageId = STAGE_SEL;
        if (g_UseDisk) {
            if (g_IsUsingCd) {
                break;
            }
            g_CdStep = CdStep_LoadInit;
            g_LoadFile = CdFile_31;
        }
        g_GameStep++;
        break;
    case 1:
        if (g_UseDisk) {
            if (g_IsUsingCd) {
                break;
            }
            LoadImage(&g_Vram.D_800ACDE0, (u_long*)STAGE_PRG_PTR);
            LoadImage(&g_Vram.D_800ACDD8, (u_long*)&D_8D2FC40);
            LoadImage(&g_Vram.D_800ACDB8, (u_long*)&D_8D3FC40);
            StoreImage(&g_Vram.D_800ACDB8, (u_long*)&g_Clut[0x2000]);
            LoadImage(&g_Vram.D_800ACDA8, (u_long*)&D_8D41C40);
            StoreImage(&g_Vram.D_800ACDA8, (u_long*)g_Clut);
        } else {
            if (LoadFileSim(14, SimFileType_System) < 0) {
                break;
            }
            if (LoadFileSim(15, SimFileType_System) < 0) {
                break;
            }
            if (LoadFileSim(16, SimFileType_System) < 0) {
                break;
            }
            if (LoadFileSim(17, SimFileType_System) < 0) {
                break;
            }
            if (LoadFileSim(4, SimFileType_System) < 0) {
                break;
            }
        }
        LoadClut((u_long*)g_Clut, 0x200, 0xF0);
        g_GameStep++;
        break;
    case 2:
        if (g_UseDisk) {
            g_CdStep = CdStep_LoadInit;
            g_LoadFile = CdFile_StagePrg;
        }
        g_GameStep++;
        break;
    case 3:
        if (g_UseDisk) {
            if (g_IsUsingCd) {
                break;
            }
        } else {
            if (LoadFileSim(0, SimFileType_StagePrg) < 0) {
                break;
            }
        }
        g_GameStep++;
        g_GameEngineStep = Engine_Init;
        break;
    case 4:
        g_api.o.UpdateStageEntities();
        break;
    case 5:
        g_GameStep++;
        g_MenuStep = 0;
        break;
    case 6:
        if (g_UseDisk) {
            g_CdStep = CdStep_LoadInit;
            g_LoadFile = CdFile_AlucardPrg;
        }
        g_GameStep++;
        if (D_800978B4 != 3 && D_800978B4 != 5) {
            g_GameStep++;
        }
        break;
    case 7:
        g_api.o.StageEndCutScene();
        break;
    case 8:
        if (g_UseDisk) {
            if (g_IsUsingCd) {
                break;
            }
        } else {
            if (LoadFileSim(4, SimFileType_System) < 0) {
                break;
            }
        }
        g_GameStep++;
        break;
    case 9:
        g_api.o.UpdateStageEntities();
        break;
    case 10:
        SetGameState(Game_Init);
        break;
    case 256:
        g_StageId = STAGE_TOP_ALT;
        D_8003C730 = 3;
        func_800E4970();
        break;
    }
}

void UpdateGame(void) {
    switch (g_GameState) {
    case Game_Init:
        HandleTitle();
        break;
    case Game_Title:
        HandleTitle();
        break;
    case Game_Play:
        HandlePlay();
        break;
    case Game_GameOver:
        HandleGameOver();
        break;
    case Game_NowLoading:
        HandleNowLoading();
        break;
    case Game_VideoPlayback:
        HandleVideoPlayback();
        break;
    case Game_Unk6:
        nullsub_9();
        break;
    case Game_PrologueEnd:
        HandlePrologueEnd();
        break;
    case Game_MainMenu:
        MainMenuHandler();
        break;
    case Game_Ending:
        HandleEnding();
        break;
    }
}
