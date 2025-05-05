// SPDX-License-Identifier: AGPL-3.0-or-later
extern s32 D_8013759C;
extern s32 D_801375A0;
extern s32 D_801375A8;
extern s32 D_801375AC;
extern s32 D_801375B0;
extern s32 D_801375B4;
extern s32 D_801375B8;
extern RoomLoadDefHolder D_801375BC;

extern bool D_8C630C8;
extern s32 D_psp_091CE578;
extern s32* D_8D97C40;
extern void (*D_8CE9C48)();
extern s32 D_psp_091CE570;

void RunMainEngine(void) {
    Entity* ent;
    Primitive* prim;
    LayerDef* layer;
    s32 i;
    s32 ent_unk68;
    void (*playerInit)(int isPrologue);
    void (*RichterUpdater)(void);
    s32 tempX;
    s32 tempY;
    s32* ptr_791c;
    // This function is a state machine, this variable is some kind of
    // overall state of the game engine
    switch (g_GameEngineStep) {
    case Engine_Init:
        if (g_IsUsingCd) {
            return;
        }
        D_8006BB00 = 0;
        D_801375C8 = 0;
        g_PauseAllowed = true;
        g_StageId = func_800F16D0();
        DestroyEntitiesFromIndex(0);
        DestroyAllPrimitives();
        func_800EDAE4();
        func_800EAD7C();
        DrawHud();
        func_800F2404(0);
        if (g_StageId == STAGE_ST0 || g_PlayableCharacter != PLAYER_ALUCARD) {
            playerInit = g_PlOvl.D_8013C004;
            if (g_StageId == STAGE_ST0) {
                playerInit(1);
            } else {
                playerInit(0);
            }
        } else {
            func_80109594();
        }
        if (g_StageId == STAGE_MAD) {
            g_api.o.StageEndCutScene();
        }
        g_backbufferX = 0;
        g_backbufferY = 0;
        func_800F14CC();
        LoadRoomLayer(D_801375BC.def->tileLayoutId);
        if (D_8003C708.flags & FLAG_UNK_20) {
            LoadGfxAsync(ANIMSET_DRA(3));
        }
        if (D_8003C708.flags & FLAG_UNK_40) {
            LoadGfxAsync(ANIMSET_DRA(4));
        }
        D_80097910 = g_StagesLba[g_StageId].unk18;
        if (g_StageId == STAGE_NO3 && D_8003C730 == 0) {
#if defined(VERSION_US)
            D_80097910 = SE_INTRO_WIND;
#elif defined(VERSION_HD)
            D_80097910 = MU_METAMORPHOSIS;
#endif
        }
        if ((D_8003C730 == 0) && !(D_8003C708.flags & FLAG_UNK_20)) {
            PlaySfx(D_80097910);
        }
        D_80097928 = 0;
        func_800EA538(2);
        if (D_801375BC.def->tilesetId != 0) {
            func_800EA5E4(D_801375BC.def->tilesetId + 0x7fff | 0x4000);
        }
        if (D_801375BC.def->objGfxId != 0) {
            LoadGfxAsync(D_801375BC.def->objGfxId + 0x7fff);
            D_80097904 = D_801375BC.def->objGfxId + 0x7fff;
        } else {
            D_80097904 = 0;
        }
        tempX = PLAYER.posX.i.hi;
        tempY = PLAYER.posY.i.hi;
        g_PlayerX = tempX;
        g_PlayerY = tempY;
        PLAYER.posX.i.hi = (u8)tempX;
        PLAYER.posY.i.hi = (u8)tempY;
        if (PLAYER.posX.i.hi < 0x80) {
            PLAYER.facingLeft = 0;
        } else {
            PLAYER.facingLeft = 1;
        }
        ptr_791c = &D_8009791C;
        g_Tilemap.x =
            ((D_801375BC.def - 1)->tileLayoutId - g_Tilemap.left) << 8;
        g_Tilemap.y = ((D_801375BC.def - 1)->tilesetId - g_Tilemap.top) << 8;
        g_Tilemap.width =
            (((D_801375BC.def - 1)->objGfxId - g_Tilemap.left) + 1) << 8;
        g_Tilemap.height =
            (((D_801375BC.def - 1)->objLayoutId - g_Tilemap.top) + 1) << 8;

        *ptr_791c = (g_PlayerX >> 8) + g_Tilemap.left;
        D_80097920 = (g_PlayerY >> 8) + g_Tilemap.top;

        g_Tilemap.scrollX.i.hi = (*ptr_791c - g_Tilemap.left) << 8;
        g_Tilemap.scrollY.i.hi = (D_80097920 - g_Tilemap.top) << 8;

        if (D_8003C730 == 2) {
            g_Tilemap.height -= 0x100;
            PLAYER.facingLeft = 1;
            g_Tilemap.bottom -= 1;
        }
        if (D_8006C374 == 0x2C) {
            g_Tilemap.y = 0x2FB;
            g_Tilemap.height = 0x3FB;
            g_StageId = STAGE_TOP;
        }
        if (D_80097C98 == 6) {
            PLAYER.facingLeft = 1;
        }
        if ((D_80097C98 == 4) || (D_80097C98 == 5) || (D_80097C98 == 6)) {
            func_800EA5AC(2, 0xFF, 0xFF, 0xFF);
        }
        func_800F0CD8(0);
        func_800F0CD8(0);
        g_PrevScrollX = (s32)g_Tilemap.scrollX.i.hi;
        g_PrevScrollY = (s32)g_Tilemap.scrollY.i.hi;
        g_api.o.InitRoomEntities(D_801375BC.def->objLayoutId);
        g_api.o.Update();
        g_api.o.Update();
        func_800F0940();
        func_801024DC();
        if ((D_80097C98 != 4) && (D_80097C98 != 5) && (D_80097C98 != 6)) {
            func_801027C4(4);
            func_801027C4(2);
        }
        D_80097C98 = 0;
        if (D_8003C730 == 1) {
            InitializeServant(ENGINE_INIT_SERVANT_2);
        } else {
            InitializeServant(ENGINE_INIT_SERVANT_0);
        }
        if (D_8003C730 == 3) {
            D_8003C730 = 0;
        }
        func_800F24F4();
        g_unkGraphicsStruct.D_800973F8 = AllocPrimitives(PRIM_GT4, 16);
        if (g_unkGraphicsStruct.D_800973F8 != 0) {
            prim = &g_PrimBuf[g_unkGraphicsStruct.D_800973F8];
            while (prim != NULL) {
                prim->tpage = 0x1A;
                prim->clut = 0x120;
                prim->drawMode = DRAW_HIDE;
                prim = prim->next;
            }
        }
        RefreshCapePalette();
        g_GameEngineStep++; // Move to Engine_Normal
        return;
    case Engine_Normal:
        g_GameTimer++;
#if defined(VERSION_HD)
        func_800F1424();
#endif
        func_800F2014();
        g_ScrollDeltaX = g_Tilemap.scrollX.i.hi - g_PrevScrollX;
        g_ScrollDeltaY = g_Tilemap.scrollY.i.hi - g_PrevScrollY;
        g_PrevScrollX = g_Tilemap.scrollX.i.hi;
        g_PrevScrollY = g_Tilemap.scrollY.i.hi;

        g_api.o.HitDetection();
        D_8013759C = PLAYER.posX.i.hi;
        g_Player.unk7C = PLAYER.posX.i.hi;
        D_80097488.x.val = 0;
        D_80097488.y.val = 0;
        D_801375A0 = PLAYER.posY.i.hi;
        g_Player.unk7E = PLAYER.posY.i.hi;
        if (g_StageId == STAGE_ST0 || g_PlayableCharacter != PLAYER_ALUCARD) {
            g_PlOvl.D_8013C000();
            g_PlOvl.D_8013C008();
        } else {
            EntityAlucard();
            UpdatePlayerEntities();
        }
        g_api.o.UpdateRoomPosition();
        g_api.o.Update();

#if defined(VERSION_US)
        if (g_GameState == Game_Ending) {
            if (D_80097C98 == 6) {
                D_80097C98 = 0;
                return;
            }
#elif defined(VERSION_HD)
        if (0) {
#endif

        } else {
            func_800F2860();
            if (g_DemoMode == Demo_End) {
                g_DemoMode = Demo_None;
                D_80097C98 = 0x08000000;
                LoadSaveData(0x801EA000);
                D_8003C730 = 2;
                g_GameStep = Play_PrepareNextStage;
                return;
            }
            if (D_80097C98 < 0) {
                PlaySfx(SET_STOP_SEQ);
                StoreSaveData(0x801EA000, 0, 0);
                g_GameStep = Play_PrepareNextStage;
                return;
            }
            if ((D_80097C98 == 4) || (D_80097C98 == 5) || (D_80097C98 == 6)) {
                PlaySfx(SET_STOP_SEQ);
                func_800EA5AC(0xFFFF, 0xFF, 0xFF, 0xFF);
            }
            if (D_80097C98 == 4) {
                func_800F223C();
                D_8006C374 = 0x25;
                g_GameStep = Play_PrepareNextStage;
                return;
            } else if (D_80097C98 == 5) {
                func_800F223C();
                D_8006C374 = 0x26;
                g_GameStep = Play_PrepareNextStage;
                return;
            } else if (D_80097C98 == 6) {
                g_StageId = 0x22;
                func_800F223C();
                D_8006C374 = 0x27;
                g_GameStep = Play_PrepareNextStage;
                return;
            } else if (D_80097C98 == 1) {
                PLAYER.posX.i.hi += 0x100;
            }
            D_801375A4 = D_8013759C - PLAYER.posX.i.hi;
            D_801375A8 = D_801375A0 - PLAYER.posY.i.hi;
            g_PlayerX -= D_801375A4;
            g_PlayerY -= D_801375A8;
            D_8013759C = PLAYER.posX.val;
            D_801375A0 = PLAYER.posY.val;
            D_801375AC = g_Tilemap.scrollX.i.hi;
            D_801375B0 = g_Tilemap.scrollY.i.hi;

            if (g_unkGraphicsStruct.unk20 != 0) {
                func_8010E0D0(g_unkGraphicsStruct.unk20);
                PlaySfx(SET_PAUSE_SFX_SCRIPTS);
                g_GameEngineStep = Engine_5;
                return;
            }
            i = func_800F0CD8(1);
            if (i != 0) {
                func_801027A4();
                if (i >= 2) {
                    D_8006C374 = i - 2;
                    g_GameStep = Play_PrepareNextStage;
                    return;
                }
                if (D_801375BC.def->tilesetId == 0xFF) {
                    D_8006C374 = D_801375BC.def->tileLayoutId;
                    g_GameStep = Play_PrepareNextStage;
                    return;
                }
                g_GameEngineStep = Engine_3;
                g_MenuStep = MENU_STEP_INIT;
                return;
            }
            D_801375B4 = D_801375AC - g_Tilemap.scrollX.i.hi;
            D_801375B8 = D_801375B0 - g_Tilemap.scrollY.i.hi;
            D_801375A4 = D_8013759C - PLAYER.posX.val;
            D_801375A8 = D_801375A0 - PLAYER.posY.val;
            D_801375A4 -= D_80097488.x.val;
            D_801375A8 -= D_80097488.y.val;
            func_800F0940();

            for (i = 0, ent = &g_Entities[0]; i < LEN(g_Entities); i++, ent++) {
                ent_unk68 = ent->unk68;
                if (ent_unk68) {
                    ent->posX.val += ent_unk68 * D_801375B4 * 0x100;
                    ent->posY.val += ent_unk68 * D_801375B8 * 0x100;
                } else {
                    if (ent->flags & FLAG_POS_CAMERA_LOCKED) {
                        ent->posX.i.hi += D_801375B4;
                        ent->posY.i.hi += D_801375B8;
                    }
                    if (ent->flags & FLAG_POS_PLAYER_LOCKED) {
                        ent->posX.val -= D_801375A4;
                        ent->posY.val -= D_801375A8;
                    }
                }
            }
            func_80121F14(D_801375B4 << 0x10, D_801375B8 << 0x10);
            D_801375A4 = D_801375A4 >> 16;
            D_801375A8 = D_801375A8 >> 16;
            // Note: g_PrimBuf is MAX_PRIM_COUNT=1280 total in size.
            for (i = 0, prim = &g_PrimBuf[0]; i < 1024; i++, prim++) {
                if (prim->drawMode & DRAW_UNK02) {
                    switch (prim->type & 0xf) {
                    case PRIM_G4:
                    case PRIM_GT4:
                        prim->x3 += D_801375B4;
                        prim->y3 += D_801375B8;
                    case PRIM_GT3:
                        prim->x2 += D_801375B4;
                        prim->y2 += D_801375B8;
                    case PRIM_LINE_G2:
                        prim->x1 += D_801375B4;
                        prim->y1 += D_801375B8;
                    case PRIM_TILE:
                    case PRIM_SPRT:
                        prim->x0 += D_801375B4;
                        prim->y0 += D_801375B8;
                    case PRIM_NONE:
                    case PRIM_ENV:
                        break;
                    }
                } else if (prim->drawMode & DRAW_UNK_200) {
                    switch (prim->type & 0xf) {
                    case PRIM_G4:
                    case PRIM_GT4:
                        prim->x3 -= D_801375A4;
                        prim->y3 -= D_801375A8;
                    case PRIM_GT3:
                        prim->x2 -= D_801375A4;
                        prim->y2 -= D_801375A8;
                    case PRIM_LINE_G2:
                        prim->x1 -= D_801375A4;
                        prim->y1 -= D_801375A8;
                    case PRIM_TILE:
                    case PRIM_SPRT:
                        prim->x0 -= D_801375A4;
                        prim->y0 -= D_801375A8;
                    case PRIM_NONE:
                    case PRIM_ENV:
                        break;
                    }
                }
            }
            func_80102D70();
            func_801028AC(0);
            DrawHudSubweapon();
            func_800E414C();
            if (D_80137598) {
                func_80105428();
            }
            if (g_Player.status & PLAYER_STATUS_UNK80000) {
                g_GameEngineStep = Engine_10;
                g_MenuStep = MENU_STEP_INIT;
            }
            if (g_unkGraphicsStruct.D_800973FC != 0) {
                if (D_8006BB00 == 0) {
                    D_8006BB00 = 1;
                    MuteCd();
                }
            } else if (D_8006BB00 != 0) {
                if (g_unkGraphicsStruct.pauseEnemies != 0) {
                    D_80097928 = 0;
                    D_8006BB00 = 0;
                    UnMuteCd();
                } else if (D_80097928 == 0) {
                    D_8006BB00 = 0;
                    UnMuteCd();
                } else {
                    UnMuteCd();
                    if (!(D_8003C708.flags & (FLAG_UNK_40 | FLAG_UNK_20))) {
                        PlaySfx(D_80097910);
                        if (D_80097910 != 0) {
                            D_80097928 = 0;
                        }
                    }
                    D_8006BB00 = 0;
                }
            }
            if (!(g_Player.status & PLAYER_STATUS_DEAD)) {
                if ((g_pads[0].tapped & PAD_START) && g_PauseAllowed) {
                    func_801027A4();
                    if ((g_StageId == STAGE_ST0) ||
                        (g_PlayableCharacter != PLAYER_ALUCARD)) {
                        if (func_8010183C(0) == 0) {
                            return;
                        }
                        D_800974A4 = 1;
                        g_GameEngineStep = Engine_0x70;
                        PlaySfx(SET_RELEASE_RATE_LOW_22_23);
                        PlaySfx(SET_RELEASE_RATE_LOW_20_21);
                        PlaySfx(SET_PAUSE_SFX_SCRIPTS);
#if defined(VERSION_US)
                        if (g_StageId == STAGE_ST0) {
                            MuteCd();
                        }
#endif
                        return;
                    }
                    PlaySfx(SET_RELEASE_RATE_LOW_22_23);
                    PlaySfx(SET_RELEASE_RATE_LOW_20_21);
                    PlaySfx(SET_PAUSE_SFX_SCRIPTS);
                    func_801027C4(1);
                    g_GameEngineStep++; // Goes from 1 to 2, into Engine_Menu
                    g_MenuStep = MENU_STEP_INIT;
                } else if ((g_pads[0].tapped & PAD_SELECT) &&
                           (g_StageId != STAGE_ST0) && g_PauseAllowed) {
                    func_801027C4(6);
                    D_800974A4 = 1;
                    g_GameEngineStep = Engine_Map;
                }
                break;
            }
            break;
        case Engine_0x70:
            DrawHudSubweapon();
            if (g_pads[0].tapped & PAD_START) {
                if (func_8010183C(1) != 0) {
                    D_800974A4 = 0;
                    g_GameEngineStep = Engine_Normal;
                    PlaySfx(SET_UNPAUSE_SFX_SCRIPTS);
                    PlaySfx(SET_KEY_ON_20_21);
                    PlaySfx(SET_KEY_ON_22_23);
#if defined(VERSION_US)
                    if (g_StageId == STAGE_ST0) {
                        UnMuteCd();
                    }
#endif
                }
            }
            func_801028AC(1);
            break;
        case Engine_Menu:
            MenuHandle();
            func_801028AC(1);
            break;
        case Engine_Map:
            if (g_canRevealMap) {
                DrawMapCursor();
            }
            if (g_pads[0].tapped & (PAD_START | PAD_SELECT)) {
                func_801027C4(7);
                D_800974A4 = 0;
                g_GameEngineStep = Engine_Normal;
            }
            g_api.o.UpdateStageEntities();
            func_80102D70();
            func_801028AC(1);
            break;
        case Engine_3:
            switch (g_MenuStep) {
            case 0:
                if (D_80097C98 == 2) {
                    func_800EA5AC(0xFF, 0xFF, 0xFF, 0xFF);
                    g_MenuStep = MENU_STEP_EXIT_BEGIN;
                } else {
                    func_801027C4(1);
                case 2:
                    g_MenuStep++;
                }
                break;
            case 1:
                if (func_801025F4() != 0) {
                    g_MenuStep++;
                }
                break;
            case 3:
                if (g_IsUsingCd) {
                    if (D_80097C98 == 2) {
                        func_800EA5AC(0xFF, 0xFF, 0xFF, 0xFF);
                    }
                    break;
                } else if (D_80097928 != 0) {
                    D_80097910 = g_StagesLba[g_StageId].unk18;
                    if (g_unkGraphicsStruct.D_800973FC != 1) {
                        PlaySfx(SET_STOP_MUSIC);
                        if (func_80131F68() == false) {
                            PlaySfx(D_80097910);
                            D_80097928 = 0;
                        } else {
                            break;
                        }
                    }
                }
                if (D_80137598) {
                    func_8010427C();
                    D_80137598 = false;
                }
                layer = g_api.o.tileLayers[D_801375BC.def->tileLayoutId].fg;
                if (layer->rect.params & 0x80) {
                    D_801375BC.def =
                        &g_api.o.rooms[layer->rect.params & 0x7F].load;
                    // TODO: !FAKE
                    // D_8009791C is probably part of a struct. see also
                    // (&g_Tilemap.scrollX)->i.hi seen elsewhere
                    // in this function. do-while prevents instruction
                    // reordering
                    do {
                        D_8009791C = layer->zPriority;
                    } while (0);
                    D_80097920 = layer->flags;
                } else {
                    D_8009791C = (g_PlayerX >> 8) + g_Tilemap.left;
                    D_80097920 = (g_PlayerY >> 8) + g_Tilemap.top;
                }
                D_8013759C = PLAYER.posX.val;
                D_801375A0 = PLAYER.posY.val;
                PLAYER.posX.i.hi = D_801375C0 + g_Tilemap.scrollX.i.hi;
                PLAYER.posY.i.hi = D_801375C4 + g_Tilemap.scrollY.i.hi;
                if (D_8003C708.flags & (FLAG_UNK_40 | FLAG_UNK_20)) {
                    LoadGfxAsync(ANIMSET_DRA(1));
                }
                func_800EA538(2);
                if (D_801375BC.def->tilesetId != 0) {
                    func_800EA5E4(
                        (D_801375BC.def->tilesetId + 0x7FFF) | 0x4000);
                }
                if (D_801375BC.def->objGfxId != 0) {
                    LoadGfxAsync(D_801375BC.def->objGfxId + 0x7FFF);
                    D_80097904 = D_801375BC.def->objGfxId + 0x7FFF;
                } else {
                    D_80097904 = 0;
                }
                func_800F2404(1);
                PLAYER.posY.i.hi = (u8)PLAYER.posY.i.hi;
                PLAYER.posX.i.hi = (u8)PLAYER.posX.i.hi;
                LoadRoomLayer(D_801375BC.def->tileLayoutId);
                if (D_8003C708.flags & FLAG_UNK_20) {
                    LoadGfxAsync(ANIMSET_DRA(3));
                }
                if (D_8003C708.flags & FLAG_UNK_40) {
                    LoadGfxAsync(ANIMSET_DRA(4));
                }
                g_Tilemap.x =
                    ((D_801375BC.def - 1)->tileLayoutId - g_Tilemap.left) << 8;
                g_Tilemap.y =
                    ((D_801375BC.def - 1)->tilesetId - g_Tilemap.top) << 8;
                g_Tilemap.width =
                    (((D_801375BC.def - 1)->objGfxId - g_Tilemap.left) + 1)
                    << 8;
                g_Tilemap.height =
                    (((D_801375BC.def - 1)->objLayoutId - g_Tilemap.top) + 1)
                    << 8;
                // permuter found this weird & -> thing, I don't know man
                (&g_Tilemap.scrollX)->i.hi = (D_8009791C - g_Tilemap.left) << 8;
                g_Tilemap.scrollY.i.hi = (D_80097920 - g_Tilemap.top) << 8;
                g_PlayerX = PLAYER.posX.i.hi + g_Tilemap.scrollX.i.hi;
                g_PlayerY = PLAYER.posY.i.hi + g_Tilemap.scrollY.i.hi;
                func_8011A9D8();
                PLAYER.zPriority = g_unkGraphicsStruct.g_zEntityCenter;
                func_800F0CD8(0);
                func_8010BFFC();
                g_PlayerX = PLAYER.posX.i.hi + g_Tilemap.scrollX.i.hi;
                g_PlayerY = PLAYER.posY.i.hi + g_Tilemap.scrollY.i.hi;
                func_800F0CD8(0);
                if (g_StageId == STAGE_RTOP) {
                    DestroyEntitiesFromIndex(0x40);
                    for (i = 0; i < LEN(g_unkGraphicsStruct.D_80097428); i++) {
                        g_unkGraphicsStruct.D_80097428[i] = 0;
                    }
                    g_PrevScrollX = (s32)g_Tilemap.scrollX.i.hi;
                    g_PrevScrollY = (s32)g_Tilemap.scrollY.i.hi;
                    g_api.o.InitRoomEntities(D_801375BC.def->objLayoutId);
                    g_api.o.Update();
                    func_800F0CD8(0);
                    func_800F0CD8(0);
                    DestroyEntitiesFromIndex(0x40);
                    for (i = 0; i < LEN(g_unkGraphicsStruct.D_80097428); i++) {
                        g_unkGraphicsStruct.D_80097428[i] = 0;
                    }
                }
                D_801375A4 = D_8013759C - PLAYER.posX.val;
                D_801375A8 = D_801375A0 - PLAYER.posY.val;
                for (i = 0, ent = &g_Entities[0]; i < LEN(g_Entities); i++,
                    ent++) {
                    if (ent->flags & FLAG_UNK_20000) {
                        ent->posX.val -= D_801375A4;
                        ent->posY.val -= D_801375A8;
                    }
                }
                i = 0;
                func_80121F14(-D_801375A4, -D_801375A8);
                D_801375A4 = D_801375A4 >> 16;
                D_801375A8 = D_801375A8 >> 16;
                // Note: g_PrimBuf is MAX_PRIM_COUNT=1280 total in size.
                for (i = 0, prim = &g_PrimBuf[0]; i < 1024; i++, prim++) {
                    if (prim->drawMode & DRAW_UNK_100) {
                        switch (prim->type & 0xf) {
                        case PRIM_G4:
                        case PRIM_GT4:
                            prim->x3 -= D_801375A4;
                            prim->y3 -= D_801375A8;
                        case PRIM_GT3:
                            prim->x2 -= D_801375A4;
                            prim->y2 -= D_801375A8;
                        case PRIM_LINE_G2:
                            prim->x1 -= D_801375A4;
                            prim->y1 -= D_801375A8;
                        case PRIM_TILE:
                        case PRIM_SPRT:
                            prim->x0 -= D_801375A4;
                            prim->y0 -= D_801375A8;
                        case PRIM_NONE:
                        case PRIM_ENV:
                            break;
                        }
                    }
                }
                if (g_StageId != STAGE_RTOP) {
                    DestroyEntitiesFromIndex(0x40);
                    for (i = 0; i < LEN(g_unkGraphicsStruct.D_80097428); i++) {
                        g_unkGraphicsStruct.D_80097428[i] = 0;
                    }
                    g_PrevScrollX = g_Tilemap.scrollX.i.hi;
                    g_PrevScrollY = g_Tilemap.scrollY.i.hi;
                    g_api.o.InitRoomEntities(D_801375BC.def->objLayoutId);
                    g_api.o.Update();
                    func_800F0CD8(0);
                    func_800F0CD8(0);
                    DestroyEntitiesFromIndex(0x40);
                    for (i = 0; i < LEN(g_unkGraphicsStruct.D_80097428); i++) {
                        g_unkGraphicsStruct.D_80097428[i] = 0;
                    }
                }
                g_PrevScrollX = g_Tilemap.scrollX.i.hi;
                g_PrevScrollY = g_Tilemap.scrollY.i.hi;
                if (D_80097C98 == 2) {
                    D_80097C98 = 3;
                    func_800EA5AC(0x40, 0xFF, 0xFF, 0xFF);
                } else {
                    D_80097C98 = 0;
                }
                g_api.o.InitRoomEntities(D_801375BC.def->objLayoutId);
                g_api.o.Update();
                g_api.o.Update();
                func_800F0940();
                func_800E414C();
                func_800F24F4();
                if (D_80097C98 == 3) {
                    g_GameEngineStep = Engine_Normal;
                }
#if defined(VERSION_US)
                func_8011A9D8();
#endif
                g_MenuStep++;

                break;
            case 4:
                if (func_800EB720() == 0) {
                    func_801027C4(2);
                    g_MenuStep++;
                }
                break;
            case 5:
                if (func_801025F4() != 0) {
                    g_GameEngineStep = Engine_Normal;
                }
                break;
            }
            func_801028AC(1);
            func_801028AC(1);
            break;
        case 0x5:
            if (g_unkGraphicsStruct.unk20 != 0) {
                if (g_StageId != STAGE_ST0) {
                    if (g_PlayableCharacter == PLAYER_ALUCARD) {
                        if (g_unkGraphicsStruct.unk20 == 0xFFF) {
                            EntityAlucard();
                            func_8011A870();
                            g_api.o.UpdateStageEntities();
                            if (g_pads[1].pressed & PAD_DOWN) {
                                g_unkGraphicsStruct.unk20 = 0;
                            }
                        } else {
                            if (g_unkGraphicsStruct.unk20 != 0xFF) {
                                func_8010DF70(g_unkGraphicsStruct.unk20);
                                UpdatePlayerEntities();
                            }
                            g_api.o.UpdateStageEntities();
                            func_80102D70();
                        }
                    } else {
                        g_api.o.UpdateStageEntities();
                        func_80102D70();
                    }
                } else {
                    D_8013759C = PLAYER.posX.i.hi;
                    D_801375A0 = PLAYER.posY.i.hi;
                    RichterUpdater = g_PlOvl.D_8013C000;
                    RichterUpdater();
                    RichterUpdater = g_PlOvl.D_8013C008;
                    RichterUpdater();
                    D_801375A4 = D_8013759C - PLAYER.posX.i.hi;
                    D_801375A8 = D_801375A0 - PLAYER.posY.i.hi;
                    g_PlayerX -= D_801375A4;
                    g_PlayerY -= D_801375A8;
                }
            } else {
                func_8010E168(1, 0x30);
                g_GameEngineStep = Engine_Normal;
                PlaySfx(SET_UNPAUSE_SFX_SCRIPTS);
            }
            DrawHudSubweapon();
            return;
        case 0xA:
            switch (g_MenuStep) {
            case 0:
                if (g_IsUsingCd) {
                    break;
                }
                PlaySfx(0x81);
                D_80097910 = 0;
                if (g_StageId == STAGE_ST0) {
                    SetGameState(Game_GameOver);
                    ClearImage(&g_Vram.D_800ACDA0, 0xFF, 0xFF, 0xFF);
                    SetGPUBuffRGB(-1);
                    DestroyEntitiesFromIndex(0);
                    DestroyAllPrimitives();
                    func_800EDAE4();
                    return;
                }
                SetGameState(Game_GameOver);
                func_800E5498();
                return;
            case 1:
                if (func_801025F4() != 0) {
                    g_MenuStep++;
                }
                break;
            case 2:
                SetGameState(Game_GameOver);
                SetGPUBuffRGBZero();
                break;
            }
            func_801028AC(0);
            break;
        }
    }
}
