#include "dra.h"

#define CH(x) ((x)-0x20)

void func_800F298C(void) {
    Entity* ent;
    Primitive* prim;
    LayerDef* layer;
    s32 i;
    s32 ent_unk68;
    void (*RichterInitializer)();
    void (*RichterUpdater)();
    s32 tempX;
    s32 tempY;
    s32* ptr_791c;
    // This function is a state machine, this variable is some kind of
    // overall state of the game engine
    switch (D_8003C9A4) {
    case 0:
        if (g_IsUsingCd) {
            return;
        }
        D_8006BB00 = 0;
        D_801375C8 = 0;
        D_8003C8B8 = 1;
        g_StageId = func_800F16D0();
        DestroyEntities(0);
        DestroyAllPrimitives();
        func_800EDAE4();
        func_800EAD7C();
        func_8010189C();
        func_800F2404(0);
        if ((g_StageId == STAGE_ST0) ||
            (g_PlayableCharacter != PLAYER_ALUCARD)) {
            RichterInitializer = D_8013C004;
            if (g_StageId == STAGE_ST0) {
                RichterInitializer(1);
            } else {
                RichterInitializer(0);
            }
        } else {
            func_80109594();
        }
        if (g_StageId == STAGE_MAD) {
            g_api.o.unk3C();
        }
        g_backbufferX = 0;
        g_backbufferY = 0;
        func_800F14CC();
        LoadRoomLayer(D_801375BC.def->tileLayoutId);
        if (D_8003C708.flags & 0x20) {
            LoadGfxAsync(ANIMSET_DRA(3));
        }
        if (D_8003C708.flags & 0x40) {
            LoadGfxAsync(ANIMSET_DRA(4));
        }
        D_80097910 = g_StagesLba[g_StageId].unk18;
        if (g_StageId == STAGE_NO3 && D_8003C730 == 0) {
#if defined(VERSION_US)
            D_80097910 = 0x32A;
#elif defined(VERSION_HD)
            D_80097910 = 0x327;
#endif
        }
        if ((D_8003C730 == 0) && !(D_8003C708.flags & 0x20)) {
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
        playerX = tempX;
        playerY = tempY;
        PLAYER.posX.i.hi = (u8)tempX;
        PLAYER.posY.i.hi = (u8)tempY;
        if (PLAYER.posX.i.hi < 0x80) {
            PLAYER.facingLeft = 0;
        } else {
            PLAYER.facingLeft = 1;
        }
        ptr_791c = &D_8009791C;
        g_CurrentRoom.x =
            ((D_801375BC.def - 1)->tileLayoutId - g_CurrentRoom.left) << 8;
        g_CurrentRoom.y =
            ((D_801375BC.def - 1)->tilesetId - g_CurrentRoom.top) << 8;
        g_CurrentRoom.width =
            (((D_801375BC.def - 1)->objGfxId - g_CurrentRoom.left) + 1) << 8;
        g_CurrentRoom.height =
            (((D_801375BC.def - 1)->objLayoutId - g_CurrentRoom.top) + 1) << 8;

        *ptr_791c = (playerX >> 8) + g_CurrentRoom.left;
        D_80097920 = (playerY >> 8) + g_CurrentRoom.top;

        g_Camera.posX.i.hi = (*ptr_791c - g_CurrentRoom.left) << 8;
        g_Camera.posY.i.hi = (D_80097920 - g_CurrentRoom.top) << 8;

        if (D_8003C730 == 2) {
            g_CurrentRoom.height -= 0x100;
            PLAYER.facingLeft = 1;
            g_CurrentRoom.bottom -= 1;
        }
        if (D_8006C374 == 0x2C) {
            g_CurrentRoom.y = 0x2FB;
            g_CurrentRoom.height = 0x3FB;
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
        D_80073074 = (s32)g_Camera.posX.i.hi;
        D_8007307C = (s32)g_Camera.posY.i.hi;
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
            func_800E6218(2);
        } else {
            func_800E6218(0);
        }
        if (D_8003C730 == 3) {
            D_8003C730 = 0;
        }
        func_800F24F4();
        D_800973F8 = AllocPrimitives(PRIM_GT4, 16);
        if (D_800973F8 != 0) {
            prim = &g_PrimBuf[D_800973F8];
            while (prim != NULL) {
                prim->tpage = 0x1A;
                prim->clut = 0x120;
                prim->blendMode = BLEND_VISIBLE;
                prim = prim->next;
            }
        }
        func_800FF6C4();
        D_8003C9A4++;
        return;
    case 1:
        g_GameTimer++;
#if defined(VERSION_HD)
        func_800F1424();
#endif
        func_800F2014();
        D_80097908 = g_Camera.posX.i.hi - D_80073074;
        D_8009790C = g_Camera.posY.i.hi - D_8007307C;
        D_80073074 = g_Camera.posX.i.hi;
        D_8007307C = g_Camera.posY.i.hi;

        g_api.o.TestCollisions();
        D_8013759C = PLAYER.posX.i.hi;
        g_Player.unk7C = PLAYER.posX.i.hi;
        D_80097488 = 0;
        D_8009748C = 0;
        D_801375A0 = PLAYER.posY.i.hi;
        g_Player.unk7E = PLAYER.posY.i.hi;
        if ((g_StageId == STAGE_ST0) ||
            (g_PlayableCharacter != PLAYER_ALUCARD)) {
            D_8013C000();
            D_8013C008();
        } else {
            EntityAlucard();
            func_8011A4D0();
        }
        g_api.o.unk08();
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
                PlaySfx(7);
                StoreSaveData(0x801EA000, 0, 0);
                g_GameStep = Play_PrepareNextStage;
                return;
            }
            if ((D_80097C98 == 4) || (D_80097C98 == 5) || (D_80097C98 == 6)) {
                PlaySfx(7);
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
            playerX -= D_801375A4;
            playerY -= D_801375A8;
            D_8013759C = PLAYER.posX.val;
            D_801375A0 = PLAYER.posY.val;
            D_801375AC = g_Camera.posX.i.hi;
            D_801375B0 = g_Camera.posY.i.hi;

            if (*D_80097420 != 0) {
                func_8010E0D0(*D_80097420);
                PlaySfx(0xE);
                D_8003C9A4 = 5;
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
                D_8003C9A4 = 3;
                D_800978F8 = 0;
                return;
            }
            D_801375B4 = D_801375AC - g_Camera.posX.i.hi;
            D_801375B8 = D_801375B0 - g_Camera.posY.i.hi;
            D_801375A4 = D_8013759C - PLAYER.posX.val;
            D_801375A8 = D_801375A0 - PLAYER.posY.val;
            D_801375A4 -= D_80097488;
            D_801375A8 -= D_8009748C;
            func_800F0940();

            for (i = 0, ent = &g_Entities[0]; i < LEN(g_Entities); i++, ent++) {
                ent_unk68 = ent->unk68;
                if (ent_unk68 != 0) {
                    ent->posX.val += ent_unk68 * D_801375B4 * 0x100;
                    ent->posY.val += ent_unk68 * D_801375B8 * 0x100;
                } else {
                    if (ent->flags & FLAG_UNK_08000000) {
                        ent->posX.i.hi += D_801375B4;
                        ent->posY.i.hi += D_801375B8;
                    }
                    if ((ent->flags & FLAG_UNK_40000) != 0) {
                        ent->posX.val -= D_801375A4;
                        ent->posY.val -= D_801375A8;
                    }
                }
            }
            func_80121F14(D_801375B4 << 0x10, D_801375B8 << 0x10);
            D_801375A4 = D_801375A6;
            D_801375A8 = D_801375AA;
            // Note: g_PrimBuf is MAX_PRIM_COUNT=1280 total in size.
            for (i = 0, prim = &g_PrimBuf[0]; i < 1024; i++, prim++) {
                if (prim->blendMode & 2) {
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
                } else if (prim->blendMode & 0x200) {
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
            DrawHudAlucard();
            func_800E414C();
            if (D_80137598 != 0) {
                func_80105428();
            }
            if (g_Player.unk0C & 0x80000) {
                D_8003C9A4 = 10;
                D_800978F8 = 0;
            }
            if (D_800973FC != 0) {
                if (D_8006BB00 == 0) {
                    D_8006BB00 = 1;
                    func_80131EE8();
                }
            } else if (D_8006BB00 != 0) {
                if (*D_80097400 != 0) {
                    D_80097928 = 0;
                    D_8006BB00 = 0;
                    func_80131F04();
                } else if (D_80097928 == 0) {
                    D_8006BB00 = 0;
                    func_80131F04();
                } else {
                    func_80131F04();
                    if (!(D_8003C708.flags & 0x60)) {
                        PlaySfx(D_80097910);
                        if (D_80097910 != 0) {
                            D_80097928 = 0;
                        }
                    }
                    D_8006BB00 = 0;
                }
            }
            if (!(g_Player.unk0C & 0x40000)) {
                if ((g_pads[0].tapped & PAD_START) && (D_8003C8B8 != 0)) {
                    func_801027A4();
                    if ((g_StageId == STAGE_ST0) ||
                        (g_PlayableCharacter != PLAYER_ALUCARD)) {
                        if (func_8010183C(0) == 0) {
                            return;
                        }
                        D_800974A4 = 1;
                        D_8003C9A4 = 0x70;
                        PlaySfx(0xa7);
                        PlaySfx(0xa3);
                        PlaySfx(0xe);
#if defined(VERSION_US)
                        if (g_StageId == STAGE_ST0) {
                            func_80131EE8();
                        }
#endif
                        return;
                    }
                    PlaySfx(0xa7);
                    PlaySfx(0xa3);
                    PlaySfx(0xe);
                    func_801027C4(1);
                    D_8003C9A4++;
                    D_800978F8 = 0;
                } else if ((g_pads[0].tapped & PAD_SELECT) &&
                           (g_StageId != STAGE_ST0) && (D_8003C8B8 != 0)) {
                    func_801027C4(6);
                    D_800974A4 = 1;
                    D_8003C9A4 = 20;
                }
                break;
            }
            break;
        case 0x70:
            DrawHudAlucard();
            if (g_pads[0].tapped & PAD_START) {
                if (func_8010183C(1) != 0) {
                    D_800974A4 = 0;
                    D_8003C9A4 = 1;
                    PlaySfx(0xF);
                    PlaySfx(0xA4);
                    PlaySfx(0xA8);
#if defined(VERSION_US)
                    if (g_StageId == STAGE_ST0) {
                        func_80131F04();
                    }
#endif
                }
            }
            func_801028AC(1);
            break;
        case 0x2:
            func_800FBC24();
            func_801028AC(1);
            break;
        case 0x14:
            if (D_8013AED0 != 0) {
                func_800F2658();
            }
            if (g_pads[0].tapped & (PAD_START | PAD_SELECT)) {
                func_801027C4(7);
                D_800974A4 = 0;
                D_8003C9A4 = 1;
            }
            g_api.o.unk28();
            func_80102D70();
            func_801028AC(1);
            break;
        case 0x3:
            switch (D_800978F8) {
            case 0:
                if (D_80097C98 == 2) {
                    func_800EA5AC(0xFF, 0xFF, 0xFF, 0xFF);
                    D_800978F8 = 3;
                } else {
                    func_801027C4(1);
                case 2:
                    D_800978F8++;
                }
                break;
            case 1:
                if (func_801025F4() != 0) {
                    D_800978F8++;
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
                    if (D_800973FC != 1) {
                        PlaySfx(0xA);
                        if (func_80131F68() == false) {
                            PlaySfx(D_80097910);
                            D_80097928 = 0;
                        } else {
                            break;
                        }
                    }
                }
                if (D_80137598 != 0) {
                    func_8010427C();
                    D_80137598 = 0;
                }
                layer = g_api.o.tileLayers[D_801375BC.def->tileLayoutId].fg;
                if (layer->bottom & 0x80) {
                    D_801375BC.def = &g_api.o.rooms[layer->bottom & 0x7F].load;
                    // TODO: !FAKE
                    // D_8009791C is probably part of a struct. see also
                    // (&g_Camera.posX)->i.hi seen elsewhere in this function.
                    // do-while prevents instruction reordering
                    do {
                        D_8009791C = layer->zPriority;
                    } while (0);
                    D_80097920 = layer->unkE;
                } else {
                    D_8009791C = (playerX >> 8) + g_CurrentRoom.left;
                    D_80097920 = (playerY >> 8) + g_CurrentRoom.top;
                }
                D_8013759C = PLAYER.posX.val;
                D_801375A0 = PLAYER.posY.val;
                PLAYER.posX.i.hi = D_801375C0 + g_Camera.posX.i.hi;
                PLAYER.posY.i.hi = D_801375C4 + g_Camera.posY.i.hi;
                if (D_8003C708.flags & 0x60) {
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
                if (D_8003C708.flags & 0x20) {
                    LoadGfxAsync(ANIMSET_DRA(3));
                }
                if (D_8003C708.flags & 0x40) {
                    LoadGfxAsync(ANIMSET_DRA(4));
                }
                g_CurrentRoom.x =
                    ((D_801375BC.def - 1)->tileLayoutId - g_CurrentRoom.left)
                    << 8;
                g_CurrentRoom.y =
                    ((D_801375BC.def - 1)->tilesetId - g_CurrentRoom.top) << 8;
                g_CurrentRoom.width =
                    (((D_801375BC.def - 1)->objGfxId - g_CurrentRoom.left) + 1)
                    << 8;
                g_CurrentRoom.height =
                    (((D_801375BC.def - 1)->objLayoutId - g_CurrentRoom.top) +
                     1)
                    << 8;
                // permuter found this weird & -> thing, I don't know man
                (&g_Camera.posX)->i.hi = (D_8009791C - g_CurrentRoom.left) << 8;
                g_Camera.posY.i.hi = (D_80097920 - g_CurrentRoom.top) << 8;
                playerX = PLAYER.posX.i.hi + g_Camera.posX.i.hi;
                playerY = PLAYER.posY.i.hi + g_Camera.posY.i.hi;
                func_8011A9D8();
                PLAYER.zPriority = g_unkGraphicsStruct.g_zEntityCenter.S16.unk0;
                func_800F0CD8(0);
                func_8010BFFC();
                playerX = PLAYER.posX.i.hi + g_Camera.posX.i.hi;
                playerY = PLAYER.posY.i.hi + g_Camera.posY.i.hi;
                func_800F0CD8(0);
                if (g_StageId == STAGE_RTOP) {
                    DestroyEntities(0x40);
                    for (i = 0; i < LEN(g_unkGraphicsStruct.D_8009742C); i++) {
                        g_unkGraphicsStruct.D_8009742C[i] = 0;
                    }
                    D_80073074 = (s32)g_Camera.posX.i.hi;
                    D_8007307C = (s32)g_Camera.posY.i.hi;
                    g_api.o.InitRoomEntities(D_801375BC.def->objLayoutId);
                    g_api.o.Update();
                    func_800F0CD8(0);
                    func_800F0CD8(0);
                    DestroyEntities(0x40);
                    for (i = 0; i < LEN(g_unkGraphicsStruct.D_8009742C); i++) {
                        g_unkGraphicsStruct.D_8009742C[i] = 0;
                    }
                }
                D_801375A4 = D_8013759C - PLAYER.posX.val;
                D_801375A8 = D_801375A0 - PLAYER.posY.val;
                for (i = 0, ent = &g_Entities[0]; i < LEN(g_Entities); i++,
                    ent++) {
                    if (ent->flags & 0x20000) {
                        ent->posX.val -= D_801375A4;
                        ent->posY.val -= D_801375A8;
                    }
                }
                i = 0;
                func_80121F14(-D_801375A4, -D_801375A8);
                D_801375A4 = D_801375A6;
                D_801375A8 = D_801375AA;
                // Note: g_PrimBuf is MAX_PRIM_COUNT=1280 total in size.
                for (i = 0, prim = &g_PrimBuf[0]; i < 1024; i++, prim++) {
                    if (prim->blendMode & 0x100) {
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
                    DestroyEntities(0x40);
                    for (i = 0; i < LEN(g_unkGraphicsStruct.D_8009742C); i++) {
                        g_unkGraphicsStruct.D_8009742C[i] = 0;
                    }
                    D_80073074 = g_Camera.posX.i.hi;
                    D_8007307C = g_Camera.posY.i.hi;
                    g_api.o.InitRoomEntities(D_801375BC.def->objLayoutId);
                    g_api.o.Update();
                    func_800F0CD8(0);
                    func_800F0CD8(0);
                    DestroyEntities(0x40);
                    for (i = 0; i < LEN(g_unkGraphicsStruct.D_8009742C); i++) {
                        g_unkGraphicsStruct.D_8009742C[i] = 0;
                    }
                }
                D_80073074 = g_Camera.posX.i.hi;
                D_8007307C = g_Camera.posY.i.hi;
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
                    D_8003C9A4 = 1;
                }
#if defined(VERSION_US)
                func_8011A9D8();
#endif
                D_800978F8++;

                break;
            case 4:
                if (func_800EB720() == 0) {
                    func_801027C4(2);
                    D_800978F8++;
                }
                break;
            case 5:
                if (func_801025F4() != 0) {
                    D_8003C9A4 = 1;
                }
                break;
            }
            func_801028AC(1);
            func_801028AC(1);
            break;
        case 0x5:
            if (*D_80097420 != 0) {
                if (g_StageId != STAGE_ST0) {
                    if (g_PlayableCharacter == PLAYER_ALUCARD) {
                        if (*D_80097420 == 0xFFF) {
                            EntityAlucard();
                            func_8011A870();
                            g_api.o.unk28();
                            if (g_pads[1].pressed & PAD_DOWN) {
                                *D_80097420 = 0;
                            }
                        } else {
                            if (*D_80097420 != 0xFF) {
                                func_8010DF70(*D_80097420);
                                func_8011A4D0();
                            }
                            g_api.o.unk28();
                            func_80102D70();
                        }
                    } else {
                        g_api.o.unk28();
                        func_80102D70();
                    }
                } else {
                    D_8013759C = PLAYER.posX.i.hi;
                    D_801375A0 = PLAYER.posY.i.hi;
                    RichterUpdater = D_8013C000;
                    RichterUpdater();
                    RichterUpdater = D_8013C008;
                    RichterUpdater();
                    D_801375A4 = D_8013759C - PLAYER.posX.i.hi;
                    D_801375A8 = D_801375A0 - PLAYER.posY.i.hi;
                    playerX -= D_801375A4;
                    playerY -= D_801375A8;
                }
            } else {
                func_8010E168(1, 0x30);
                D_8003C9A4 = 1;
                PlaySfx(0xF);
            }
            DrawHudAlucard();
            return;
        case 0xA:
            switch (D_800978F8) {
            case 0:
                if (g_IsUsingCd) {
                    break;
                }
                PlaySfx(0x81);
                D_80097910 = 0;
                if (g_StageId == STAGE_ST0) {
                    SetGameState(Game_GameOver);
                    ClearImage(&g_Vram.D_800ACDA0, 0xFF, 0xFF, 0xFF);
                    func_800E34A4(-1);
                    DestroyEntities(0);
                    DestroyAllPrimitives();
                    func_800EDAE4();
                    return;
                }
                SetGameState(Game_GameOver);
                func_800E5498();
                return;
            case 1:
                if (func_801025F4() != 0) {
                    D_800978F8++;
                }
                break;
            case 2:
                SetGameState(Game_GameOver);
                func_800E346C();
                break;
            }
            func_801028AC(0);
            break;
        }
    }
}

// menu.c
const char* D_800A2D48[] = {
#if defined(VERSION_US)
    "？？？？？",
    "Button set−up",
    "Select front／back of reversible cloak",
    "Custom cloak settings",
    "Window color settings",
    "Sound settings",
    "Time from game start",
#elif defined(VERSION_HD)
    "？？？？？",
    "ボタン割当変更",
    "リバーシブルマントの表\裏の選択",
    "オーダーメイドのカラーの設定",
    "ウィンドウカラーの設定",
    "サウンドの設定",
    "ゲームスタートからの経過時間",
#endif
};

#if defined(VERSION_US)
const char* D_800A2D64[] = {
    "ＡＴＤＥＦ",
};
#elif defined(VERSION_HD)
const char* D_800A2D10[] = {
    "装備技システム短剣必殺使攻撃力防",
};

const char* D_800A2D14[] = {
    "御魔導器拳こ一覧棒両手食物爆弾盾",
};

const char* D_800A2D18[] = {
    "投射薬ん右左武兜鎧マントその他い",
};
#endif

#if defined(VERSION_US)
const char* D_800A2D68[] = {
    "\x00\x01\x01\xFF",
    "\x02\x03\x04\xFF",
};
#elif defined(VERSION_HD)
extern const char* D_800A2D68[];
#endif

bool func_800F483C(void) {
    s32 buf[BUTTON_COUNT];
    s32 i;
    s32 var_a1;
    s32* buttonConfig;

    for (i = 0; i < 8; i++) {
        buf[i] = 0;
    }

    for (i = 0; i < 7; i++) {
        buf[g_Settings.buttonConfig[i]] = 1;
    }

    for (i = 0; i < 8; i++) {
        if (buf[i] == 0) {
            g_Settings.buttonConfig[7] = i;
            break;
        }
    }

    for (i = 0; i < 8; i++) {
        g_Settings.buttonMask[i] = D_800A0160[g_Settings.buttonConfig[i]];
    }

    var_a1 = 0;
    buttonConfig = g_Settings.buttonConfig;
    for (i = 0; i < 8; i++) {
        var_a1 |= 1 << *buttonConfig++;
    }

    return var_a1 == 0xFF;
}

bool IsAlucart(void) {
    if (CheckEquipmentItemCount(ITEM_ALUCART_SWORD, HAND_TYPE) &&
        CheckEquipmentItemCount(ITEM_ALUCART_SHIELD, HAND_TYPE) &&
        CheckEquipmentItemCount(ITEM_ALUCART_MAIL, ARMOR_TYPE))
        return true;
    return false;
}

void func_800F4994(void) {
    s32* statsPtr = &g_Status.statsEquip;
    s32 correctStonesEquipped;
    s32 statBonus;
    u32 hourOfDay;
    s32 i, j;

    for (i = 0; i < 4; i++, statsPtr++) {
        *statsPtr = 0;
    }

    // Iterate through each Item Slot
    for (i = 0; i < 5; i++) {
        // Iterate through the 4 stats (STR, CON, INT, LCK)
        for (j = 0; j < 4; j++) {
            statBonus = g_AccessoryDefs[g_Status.equipment[HEAD_SLOT + i]]
                            .statsBonus[j];
            if (statBonus > 128) {
                statBonus -= 256;
            }
            g_Status.statsEquip[j] += statBonus;
        }
    }
    hourOfDay = g_Status.timerHours % 24;

    // Hours of sunstone effectiveness
    if (6 <= hourOfDay && hourOfDay < 18) {
        // Sunstone check
        correctStonesEquipped =
            CheckEquipmentItemCount(ITEM_SUNSTONE, ACCESSORY_TYPE);
        statsPtr = &g_Status.statsEquip;
        for (i = 0; i < 4; i++, statsPtr++) {
            *statsPtr += correctStonesEquipped * 5;
        }
    } else {
        // Moonstone check
        correctStonesEquipped =
            CheckEquipmentItemCount(ITEM_MOONSTONE, ACCESSORY_TYPE);
        statsPtr = &g_Status.statsEquip;
        for (i = 0; i < 4; i++, statsPtr++) {
            *statsPtr += correctStonesEquipped * 5;
        }
    }

    if (D_80139830[2] != 0) {
        g_Status.statsEquip[STAT_STR] += 20;
    }
    if (D_80139830[1] != 0) {
        g_Status.statsEquip[STAT_INT] += 20;
    }
    if (D_80139830[0] != 0) {
        g_Status.statsEquip[STAT_LCK] += 20;
    }
    if (g_Status.relics[RELIC_RIB_OF_VLAD] & 2) {
        g_Status.statsEquip[STAT_CON] += 10;
    }
    if (g_Status.relics[RELIC_EYE_OF_VLAD] & 2) {
        g_Status.statsEquip[STAT_LCK] += 10;
    }
    if (g_Status.relics[RELIC_TOOTH_OF_VLAD] & 2) {
        g_Status.statsEquip[STAT_STR] += 10;
    }
    if (g_Status.relics[RELIC_RING_OF_VLAD] & 2) {
        g_Status.statsEquip[STAT_INT] += 10;
    }
    if (IsAlucart() != false) {
        g_Status.statsEquip[STAT_LCK] += 30;
    }

    for (i = 0; i < 4; i++) {
        if (g_Status.statsEquip[i] > 99) {
            g_Status.statsEquip[i] = 99;
        }
        g_Status.statsTotal[i] = g_Status.statsBase[i] + g_Status.statsEquip[i];
    }

    g_Status.statsTotal[1] =
        (g_Status.statsEquip[1] * 8) + g_Status.statsBase[1];
    g_Status.statsTotal[2] =
        (g_Status.statsEquip[2] * 4) + g_Status.statsBase[2];
    for (i = 0; i < 4; i++) {
        if (g_Status.statsTotal[i] < 0) {
            g_Status.statsTotal[i] = 0;
        }
    }
}

s32 CalcAttack(s32 equipId, s32 otherEquipId) {
    s32 i;
    u16 equipmentAttackBonus;
    s16 totalAttack;
    s16 strengthStat;

    if (g_EquipDefs[equipId].itemCategory == ITEM_FOOD ||
        g_EquipDefs[equipId].itemCategory == ITEM_MEDICINE ||
        (g_EquipDefs[equipId].itemCategory == ITEM_SHIELD &&
         g_EquipDefs[equipId].attack == 1)) {
        return 0;
    }

    if (equipId == ITEM_ALUCARD_SHIELD) {
        return 0;
    }

    equipmentAttackBonus = 0;

    for (i = 0; i < 5; i++) {
        equipmentAttackBonus +=
            (u16)g_AccessoryDefs[g_Status.equipment[2 + i]].attBonus;
    }

    totalAttack = g_EquipDefs[equipId].attack;
    strengthStat = g_Status.statsTotal[0];

    if (strengthStat >= totalAttack) {
        totalAttack += strengthStat;
    } else {
        totalAttack += strengthStat / 2;
    }

    totalAttack += equipmentAttackBonus;

    if (equipId == ITEM_BADELAIRE) {
        totalAttack += g_Status.timerHours;
    }
    if (equipId == ITEM_MURAMASA) {
        totalAttack += SquareRoot0(g_Status.D_80097C40);
    }
    if (equipId == 4 && g_EquipDefs[otherEquipId].itemCategory == ITEM_SHIELD) {
        totalAttack += 5;
    }
    if (equipId == ITEM_SWORD_FAMILIAR) {
        totalAttack += g_Status.statsFamiliars[FAM_STATS_SWORD].level;
    }
    if (D_8013982C != 0) {
        totalAttack += 20;
    }
    if (totalAttack < 0) {
        totalAttack = 0;
    }
    if (totalAttack > 999) {
        totalAttack = 999;
    }
    return totalAttack;
}

void func_800F4F48(void) {
    s32 i;

    for (i = 0; i < 2; i++) {
        g_Status.attackHands[i] =
            CalcAttack(g_Status.equipment[i], g_Status.equipment[1 - i]);
    }
}

void CalcDefense(void) {
    Accessory* acc;
    s32 thisHandItem;
    s32 i;
    s16 totalDefense;

    totalDefense = 0;
    g_Status.defenseElement = 0;
    g_Status.D_80097C2A = 0;
    g_Status.D_80097C2C = 0;
    g_Status.D_80097C2E = 0;

    // Iterate over player's hands, hand 0 and hand 1.
    for (i = 0; i < 2; i++) {
        thisHandItem = g_Status.equipment[i];
        totalDefense += g_EquipDefs[thisHandItem].defense;
        // If this hand is shield rod and other hand is a shield, defense bonus
        // of 2.
        if ((thisHandItem == 4) &&
            g_EquipDefs[g_Status.equipment[1 - i]].itemCategory == 9) {
            totalDefense += 2;
        }
    }
    // Iterate over accessories worn by player
    for (i = 0; i < 5; i++) {
        acc = &g_AccessoryDefs[g_Status.equipment[i + 2]];
        totalDefense += acc->defBonus;
        g_Status.defenseElement |= acc->unk10;
        g_Status.D_80097C2A |= acc->unk12;
        g_Status.D_80097C2C |= acc->unk14;
        g_Status.D_80097C2E |= acc->unk16;
    }

    if (CheckEquipmentItemCount(ITEM_MIRROR_CUIRASS, HAND_TYPE) != 0) {
        g_Status.D_80097C2C |= 0x200;
    }
    if (CheckEquipmentItemCount(ITEM_ALUCARD_MAIL, HAND_TYPE) != 0) {
        g_Status.D_80097C2C |= 0x8000;
    }
    if (g_Status.relics[RELIC_HEART_OF_VLAD] & 2) {
        g_Status.D_80097C2C |= 0x100;
    }
    if (D_8013983C != 0) {
        g_Status.D_80097C2A |= 0x8000;
    }
    if (D_80139840 != 0) {
        g_Status.D_80097C2A |= 0x2000;
    }
    if (D_80139844 != 0) {
        g_Status.D_80097C2A |= 0x4000;
    }
    if (D_80139848 != 0) {
        g_Status.D_80097C2A |= 0x100;
    }
    if (D_8013984C != 0) {
        g_Status.D_80097C2A |= 0x1000;
    }
    if (D_80139850 != 0) {
#if defined(VERSION_US)
        g_Status.D_80097C2C |= 0x200;
#elif defined(VERSION_HD)
        g_Status.D_80097C2A |= 0x200;
#endif
    }
    if (D_80139854 != 0) {
        g_Status.D_80097C2A |= 0x800;
    }

    totalDefense += (SquareRoot0(g_Status.statsTotal[STAT_CON]) - 2);

    if (CheckEquipmentItemCount(ITEM_WALK_ARMOR, ARMOR_TYPE) != 0) {
        totalDefense += g_RoomCount / 60;
    }

    if (*D_80139828 != 0) {
        totalDefense += 20;
    }
    if (totalDefense < 0) {
        totalDefense = 0;
    }
    if (totalDefense > 999) {
        totalDefense = 999;
    }
    g_Status.defenseEquip = totalDefense;
}

void func_800F53A4(void) {
    func_800F4994();
    func_800F4F48();
    CalcDefense();
}

void func_800F53D4(s32 tpage, s32 otIdx) {
    u32* ot = g_CurrentBuffer->ot;
    DR_MODE* drawMode = &g_CurrentBuffer->drawModes[g_GpuUsage.drawModes];

    if (D_80137614 != 0) {
        SetDrawMode(drawMode, 0, 0, tpage, &g_Vram.D_800ACD80);
        AddPrim(&ot[otIdx], drawMode);
        g_GpuUsage.drawModes++;
    }
}

u8 func_800F548C(u8 arg0) {
    u16 temp = arg0;

    if (arg0 & 0x80) {
        arg0 &= 0x7F;
        return func_800F548C(arg0 + 3);
    }
    return temp << 4;
}

bool IsOutsideDrawArea(s32 x0, s32 x1, s32 y0, s32 y1, MenuContext* context) {
    if (!(x1 > context->unk1.x)) {
        return true;
    }
    if (!(context->unk1.y < y1)) {
        return true;
    }
    if (x0 < (context->unk1.x + context->unk1.w)) {
        return (y0 < (context->unk1.y + context->unk1.h)) ^ 1;
    }
    return true;
}

bool ScissorPolyG4(POLY_G4* poly, MenuContext* context) {
    s32 scissorX;
    s32 scissorY;
    s32 diff;

    if (IsOutsideDrawArea(poly->x0, poly->x1, poly->y0, poly->y2, context))
        return true;

    if (poly->x0 < context->unk1.x) {
        diff = context->unk1.x - poly->x0;
        poly->x0 += diff;
        poly->x2 += diff;
    }

    if (poly->y0 < context->unk1.y) {
        diff = context->unk1.y - poly->y0;
        poly->y0 += diff;
        poly->y1 += diff;
    }

    scissorX = context->unk1.x + context->unk1.w;
    if (scissorX < poly->x1) {
        diff = poly->x1 - scissorX;
        poly->x1 -= diff;
        poly->x3 -= diff;
    }

    scissorY = context->unk1.y + context->unk1.h;
    if (scissorY < poly->y2) {
        diff = poly->y2 - scissorY;
        poly->y2 -= diff;
        poly->y3 -= diff;
    }

    return false;
}

bool ScissorPolyGT4(POLY_GT4* poly, MenuContext* context) {
    s32 scissorX;
    s32 scissorY;

    if (IsOutsideDrawArea(poly->x0, poly->x1, poly->y0, poly->y2, context))
        return true;

    if (poly->x0 < context->unk1.x) {
        s32 diff = context->unk1.x - poly->x0;
        poly->x0 += diff;
        poly->x2 += diff;
        poly->u0 += diff;
        poly->u2 += diff;
    }

    if (poly->y0 < context->unk1.y) {
        s32 diff = context->unk1.y - poly->y0;
        poly->y0 += diff;
        poly->y1 += diff;
        poly->v0 += diff;
        poly->v1 += diff;
    }

    scissorX = context->unk1.x + context->unk1.w;
    if (scissorX < poly->x1) {
        s32 diff = poly->x1 - scissorX;
        poly->x1 -= diff;
        poly->x3 -= diff;
        poly->u1 -= diff;
        poly->u3 -= diff;
    }

    scissorY = context->unk1.y + context->unk1.h;
    if (scissorY < poly->y2) {
        s32 diff = poly->y2 - scissorY;
        poly->y2 -= diff;
        poly->y3 -= diff;
        poly->v2 -= diff;
        poly->v3 -= diff;
    }

    return false;
}

bool ScissorSprite(SPRT* sprite, MenuContext* context) {
    s32 scissorY;
    s32 scissorX;
    s32 spriteX;
    s32 spriteY;

    if (IsOutsideDrawArea(sprite->x0, sprite->x0 + sprite->w, sprite->y0,
                          sprite->y0 + sprite->h, context))
        return true;

    if (sprite->x0 < context->unk1.x) {
        scissorX = context->unk1.x - sprite->x0;
        sprite->x0 += scissorX;
        sprite->u0 = sprite->u0 + scissorX;
        sprite->w = sprite->w - scissorX;
    }

    if (sprite->y0 < context->unk1.y) {
        scissorY = context->unk1.y - sprite->y0;
        sprite->y0 = sprite->y0 + scissorY;
        sprite->v0 = sprite->v0 + scissorY;
        sprite->h = sprite->h - scissorY;
    }

    scissorX = context->unk1.x + context->unk1.w;
    spriteX = sprite->x0 + sprite->w;
    if (scissorX < spriteX) {
        scissorY = spriteX - scissorX;
        sprite->w = sprite->w - scissorY;
    }

    scissorY = context->unk1.y + context->unk1.h;
    spriteY = sprite->y0 + sprite->h;
    if (scissorY < spriteY) {
        scissorX = spriteY - scissorY;
        sprite->h = sprite->h - scissorX;
    }

    return false;
}

void DrawMenuImg(MenuContext* menu, s32 x, s32 y, s32 w, u32 h, s32 u, s32 v,
                 s32 clut, s32 tpage, bool disableTexShade, s32 c) {
    SPRT* sp;
    s32 otIdx;
    u32* ot;

    ot = g_CurrentBuffer->ot;
    sp = &g_CurrentBuffer->sprite[g_GpuUsage.sp];
#if defined(VERSION_US)
    if (D_8013784C == 1) {
        clut = 0x15E;
    }
    if (D_8013784C == 2) {
        clut = 0x15D;
    }
#endif
    if (menu == NULL) {
        otIdx = 0x1FF;
    } else {
        otIdx = menu->otIdx + 2;
    }
    SetSemiTrans(sp, 0);
    SetShadeTex(sp, disableTexShade);
    sp->x0 = x;
    sp->y0 = y;
    sp->w = w;
    sp->h = h;
    sp->u0 = u;
    sp->v0 = v;
    if (menu == NULL || ScissorSprite(sp, menu) == false) {
        sp->r0 = c;
        sp->g0 = c;
        sp->b0 = c;
        sp->clut = D_8003C104[clut];
        AddPrim(&ot[otIdx], sp);
        g_GpuUsage.sp++;
        func_800F53D4(tpage, otIdx);
    }
}

void func_800F5A90(void) {
    DrawMenuImg(NULL, 96, 96, 64, 64, 0, 0, 0, 0x114, 1, 0);
}

void func_800F5AE4(MenuContext* menu) {
    s32 i, x;

    for (i = 0, x = 72; i < 3; i++, x += 128)
        DrawMenuImg(menu, x, 201, 128, 16, (i & 1) << 7,
                    func_800F548C(2) & 0xFF, 0x1A1, (i / 2) + 6, 1, 0);
}
void DrawMenuSprite(
    MenuContext* context, s32 x, s32 y, s32 width, s32 height, s32 u, s32 v,
    s32 clut, s32 tpage, s32 arg9, s32 colorIntensity, s32 argB) {
    u32* ot = g_CurrentBuffer->ot;
    POLY_GT4* poly = &g_CurrentBuffer->polyGT4[g_GpuUsage.gt4];
    s32 otIdx = context->otIdx + 2;
    u32 polyColorIntensity;
    s32 temp_polyx0;

    if (context == &g_MenuData.menus[1]) {
        otIdx--;
    }

    poly->code &= 0xFD;

    if (arg9 != 0) {
        poly->code |= 1;
    } else {
        poly->code &= 0xFC;
    }

    SetTexturedPrimRect(poly, x, y, width, height, u, v);

    if (ScissorPolyGT4(poly, context) == false) {
        poly->tpage = tpage;
        poly->clut = D_8003C104[clut];
        func_80107250(poly, colorIntensity);
        if (argB == 1) {
            polyColorIntensity = (poly->y2 - poly->y0) * 4;
            func_801071CC(poly, polyColorIntensity, 0);
            func_801071CC(poly, polyColorIntensity, 1);
        }
        if (argB == 2) {
            temp_polyx0 = poly->x0;
            poly->x0 = poly->x2 = poly->x1;
            poly->x1 = poly->x3 = temp_polyx0;
        }
        AddPrim(&ot[otIdx], poly);
        g_GpuUsage.gt4++;
        func_800F53D4(tpage, otIdx);
    }
}

// NOTE: used to draw the menu cursor
void DrawMenuRect(MenuContext* context, s32 posX, s32 posY, s32 width,
                  s32 height, s32 r, s32 g, s32 b) {
    u32* ot = g_CurrentBuffer->ot;
    POLY_G4* poly = &g_CurrentBuffer->polyG4[g_GpuUsage.g4];
    s32 otIdx = context->otIdx + 1;
    u32 temp;

    poly->x0 = posX;
    poly->y0 = posY;

    temp = (poly->x1 = posX + width);
    poly->y1 = posY;
    poly->x2 = posX;
    poly->x3 = temp;

    temp = (poly->y2 = posY + height);
    poly->y3 = temp;

    poly->code &= 0xFC;
    if (!ScissorPolyG4(poly, context)) {
        poly->r0 = poly->r1 = poly->r2 = poly->r3 = r;
        poly->g0 = poly->g1 = poly->g2 = poly->g3 = g;
        poly->b0 = poly->b1 = poly->b2 = poly->b3 = b;
        AddPrim(&ot[otIdx], poly);
        g_GpuUsage.g4++;
        func_800F53D4(0, otIdx);
    }
}

void func_800F5E68(MenuContext* context, s32 cursorIdx, s32 x, s32 y, s32 w,
                   s32 h, s32 yGap, s32 bColorMode) {
    s32 r;

    if (bColorMode) {
        if (g_Timer & 0x20) {
            r = (g_Timer & 0x1F) + 0x60;
        } else {
            r = 0x7F - (g_Timer & 0x1F);
        }
    } else {
        r = 0x80;
    }
    DrawMenuRect(context, x, y + (cursorIdx * (h + yGap)), w, h, r, 0, 0);
}

void DrawRelicsMenu(MenuContext* ctx) {
    s32 ctx_h;
    s32 switchFadeLevel;
    s32 spriteY;
    s32 spriteX;
    s32 var_a0;
    s32 i;
    s32 offsetY;
    s32 baseY;
    s32 var_s3;
    s32 u_OnOff;
    u8* relic;

    ctx_h = ctx->h;
    relic = &g_Status.relics[RELIC_SOUL_OF_BAT];
#if defined(VERSION_US)
    for (i = 0, var_s3 = 0; i < 30; i++, var_s3++, relic++) {
        // This if-statement only exists in US. This is to skip over
        // rendering the JP-exclusive familiars (sprite and nosedevil)
        if (i == 23) {
            i = 25;
            relic += 2;
        }

// Declare this as the var to use for the two comparisons later
#define INDEXER var_s3
#else
    for (i = 0; i < 30; i++, relic++) {
#define INDEXER i
#endif
        offsetY = (INDEXER / 2) * 0x13;
        baseY = ctx_h + 0x22;
        spriteY = offsetY + baseY;
        spriteX = (i & 1) * 0xB0;
        if (*relic & RELIC_FLAG_FOUND) {
            if (spriteY < 0) {
                continue;
            }
            if (spriteY >= 193) {
                continue;
            }
            if (!(i & 2)) {
                if (i < 0) {
                    var_a0 = i + 3;
                } else {
                    var_a0 = i;
                }
                DrawMenuSprite(
                    ctx, spriteX + 0x38, spriteY, 0x78, 0x10, (i & 1) * 0x78,
                    func_800F548C((var_a0 >> 2) - 0x80), 0x1A1, 6, 1, 0, 0);
            } else {
                if (i < 0) {
                    var_a0 = i + 3;
                } else {
                    var_a0 = i;
                }
                DrawMenuSprite(
                    ctx, spriteX + 0x38, spriteY, 0x78, 0x10, (i & 1) * 0x78,
                    func_800F548C((var_a0 >> 2) + 3), 0x1A1, 7, 1, 0, 0);
            }
        }
        switchFadeLevel = 0;
        // Determine the U value for the texture to use for the switch
        u_OnOff = -(!(*relic & RELIC_FLAG_ACTIVE)) & 0x30;
        if (INDEXER == g_MenuNavigation.cursorRelic) {
            // This routine handles the fade in/fade out of the ON/OFF switch
            // when hovering
            if (++g_RelicMenuFadeTimer >= 0x48) {
                g_RelicMenuFadeTimer = 0;
            }
            if (g_RelicMenuFadeTimer < 0x24) {
                // Fade up
                switchFadeLevel = g_RelicMenuFadeTimer / 6;
            } else {
                // Fade down
                switchFadeLevel = 6 - ((g_RelicMenuFadeTimer - 0x24) / 6);
            }
        }
        DrawMenuSprite(ctx, spriteX | 8, spriteY, 0x2F, 0xF, u_OnOff, 0x70,
                       switchFadeLevel + 0x1C8, 0x1F,
                       INDEXER == g_MenuNavigation.cursorRelic, 0x40, 0);
    }
    spriteY = ctx_h + ((g_MenuNavigation.cursorRelic / 2) * 0x13);
    DrawMenuRect(ctx, ((g_MenuNavigation.cursorRelic & 1) * 0xB0) | 8,
                 spriteY + 0x21, 0xA8, 0x12, 0x60, 0, 0);
#undef INDEXER
}

void DrawMenuAlucardPortrait(MenuContext* ctx) {
    DrawMenuSprite(ctx, 0x10, 0x24, 0x40, 0x40, 0, 0x80, 0x150, 0x9C, 1, 0, 0);
    DrawMenuSprite(ctx, 0x10, 0x64, 0x40, 0x20, 0, 0xC0, 0x150, 0x9C, 0, 0, 1);
}

// Equivalent of floor(number * .75)
// Cloak color components are 5 bit.
// Examples: 31->23, 15->11
s32 DarkenCloakColor(s32 color) { return color * 3 / 4; }

// Creates light and dark versions of cloak colors in BGR555 format
void ApplyJosephsCloakPalette(void) {
    g_JosephsCloak.liningDark =
        DarkenCloakColor(g_Settings.cloakColors[3]) +
        ((DarkenCloakColor(g_Settings.cloakColors[4]) << 5) - 0x8000) +
        (DarkenCloakColor(g_Settings.cloakColors[5]) << 0xA);
    g_JosephsCloak.liningLight =
        (g_Settings.cloakColors[3] +
         ((g_Settings.cloakColors[4] << 5) - 0x8000)) +
        ((u32)g_Settings.cloakColors[5] << 0xA);
    g_JosephsCloak.exteriorDark =
        DarkenCloakColor(g_Settings.cloakColors[0]) +
        ((DarkenCloakColor(g_Settings.cloakColors[1]) << 5) - 0x8000) +
        (DarkenCloakColor(g_Settings.cloakColors[2]) << 0xA);
    g_JosephsCloak.exteriorLight =
        g_Settings.cloakColors[0] +
        ((g_Settings.cloakColors[1] << 5) - 0x8000) +
        ((u32)g_Settings.cloakColors[2] << 0xA);
}

void DrawMenuAlucardCloakPreview(MenuContext* ctx) {
    DrawMenuSprite(ctx, 0xC0, 0x80, 0x20, 0x40, 0, 0xB0, 0x100, 7, 1, 0, 2);
    DrawMenuSprite(ctx, 0x100, 0x80, 0x40, 0x40, 0x80, 0xB0, 0x100, 7, 1, 0, 0);
}

void func_800F6508(MenuContext* context, s32 x, s32 y) {
    s32 yellow;

    if (g_Timer & 0x10) {
        yellow = ((g_Timer & 0xF) * 2) + 0x60;
    } else {
        yellow = 0x7F - (g_Timer & 0xF);
    }
    DrawMenuRect(context, x, y, 0x70, 0xB, yellow, yellow, 0);
}

// Draw main menu cursor
void func_800F6568(MenuContext* context) {
    s32 height;
    s32 r;

    height = context->cursorH / 5;
    if (g_Timer & 0x20) {
        r = (g_Timer & 0x1F) + 0x40;
    } else {
        r = 0x5F - (g_Timer & 0x1F);
    }
    DrawMenuRect(context, context->cursorX,
                 context->cursorY + (height * g_MenuNavigation.cursorMain),
                 context->cursorW, height, r, 0, 0);
}

// Draw equip menu cursor
void func_800F6618(s32 menuContextIndex, s32 bColorMode) {
    s32 r;
    MenuContext* context = &g_MenuData.menus[menuContextIndex];

    if (bColorMode != 0) {
        r = 0x80;
    } else {
        if (g_Timer & 0x20) {
            r = (g_Timer & 0x1F) + 0x40;
        } else {
            r = 0x5F - (g_Timer & 0x1F);
        }
    }
    DrawMenuRect(context, 0x70, g_MenuNavigation.cursorEquip * 13 + 0x1C, 0x71,
                 0xB, r, 0, 0);
}

void func_800F66BC(
    const char* str, s32 x, s32 y, MenuContext* menu, bool disableTexShade) {
    u16 temp;
    const int ChWidth = 12;
    const int ChHeight = 16;
    u8 ch;
    s32 unk;
loop_1:
    ch = *(str++);

    if (ch == 0xFF) {
        return;
    }
    unk = (u16)(ch & 0x10);
    unk = unk != 0;
    temp = ch;
    temp = temp >> 5;
    DrawMenuImg(menu, x, y, ChWidth, ChHeight, (ch & 0xF) * ChWidth,
                temp * ChHeight, 0x1A1, unk + 6, disableTexShade, 0x40);
    x += ChWidth;
    goto loop_1;
}

void DrawMenuChar(u8 ch, int x, int y, MenuContext* menu) {
    DrawMenuImg(menu, x, y, 8, 8, (ch & 0xF) * 8, (u32)(ch & 0xF0) >> 1, 0x196,
                0x1E, 1, 0);
}

void DrawMenuStr(const u8* str, s32 x, s32 y, MenuContext* context) {
    const int ChWidth = 8;
    const int ChHeight = 8;
    u8 ch;
    s32 xcopy;
    s32 ycopy;

    s32 s4 = D_8013784C; // FAKE can be removed in HD but not in US

    D_80137614 = 0;
    while (1) {
        xcopy = x;
        ycopy = y;
        ch = *str++;
#if defined(VERSION_US)
        if (*str == 0xC0 && *(str + 1) == 0xD2) {
            D_8013784C = 2;
            str += 2;
        } else {
            D_8013784C = s4;
        }
#endif

        if (ch == 0xFF) {
            ch = *str++;
            if (ch == 0) {
                break;
            }
            if (ch != 0xFF) {
                xcopy -= ChWidth;
                ycopy -= ChHeight;
                x -= ChWidth;
            }
        }
        DrawMenuChar(ch, xcopy, ycopy, context);
        x += ChWidth;
    }
    D_80137614 = 1;
    func_800F53D4(0x1E, context->otIdx + 2);
}

void DrawMenuInt(s32 digit, s32 x, s32 y, MenuContext* context) {
    do {
        DrawMenuChar((digit % 10) + 16, x, y, context);
        digit /= 10;
        x += -8;
    } while (digit != 0);
}

// Draw a number with a limit of N digits
void DrawMenuTime(s32 number, s32 x, s32 y, MenuContext* context, s32 digits) {
    do {
        DrawMenuChar(((number % 10) + 0x10), x, y, context);
        number /= 10;
        x -= 8;
        digits -= 1;
    } while (digits != 0);
}

void func_800F6A48(void) {
    func_800EA538(6);
    func_800EA5E4(0x411);
}

void DrawJosephsCloakMenu(MenuContext* context) {
    s32 row1Ypos;
    s32 row2Ypos;
    s32 i;
    u8* letter_RGB;
    s32 x_RGB;
    const char** exteriorInterior;

    MenuContext* ctx = &g_JosephsCloakContext;
#if defined(VERSION_US)
    s32 x_Start = 0xB0;
    s32 number_spacing = 0x28;
    const s32 xRGBVal = 0xF8;
#elif defined(VERSION_HD)
    s32 x_Start = 0x80;
    const s32 number_spacing = 0;
    const s32 xRGBVal = 0xA0;
#endif
    i = 0;
    exteriorInterior = &c_strExterior;
    x_RGB = xRGBVal;
    letter_RGB = &D_800A2D7C; // will be R, then G, then B
    row2Ypos = 0x4C;
    row1Ypos = 0x28;
    // 3 iterations, each iteration does Exterior and Lining for one letter
    for (; i < 3; row1Ypos += 0xC, letter_RGB++, row2Ypos += 0xC, i++) {
        // Write "Exterior"
        DrawMenuStr(exteriorInterior[0], x_Start, row1Ypos, ctx);
        // Write R, G, or B
        DrawMenuChar(*letter_RGB, x_RGB, row1Ypos, ctx);
        // Write "Lining"
        DrawMenuStr(exteriorInterior[1], x_Start, row2Ypos, ctx);
        // Write R, G, or B
        DrawMenuChar(*letter_RGB, x_RGB, row2Ypos, ctx);
    }
    for (i = 0; i < 6; i++) {
        DrawMenuInt(g_Settings.cloakColors[i], x_Start + number_spacing + 0x48,
                    0x28 + 0xC * i, ctx);
    }
    func_800F5E68(ctx, g_MenuNavigation.cursorCloak, x_Start - 2, 0x26,
                  number_spacing + 0x58, 0xC, 0, 1);
    ApplyJosephsCloakPalette();
    func_800F6A48();
}

void func_800F6BEC(MenuContext* context) {
#if defined(VERSION_HD)
    s32 x = 128;
#else
    s32 x = 176;
#endif
    s32 y;
    s32 i;

    for (i = 0; i < 3; i++) {
        DrawMenuChar(D_800A2D7C[i], x + 32, (i * 12) + 80, context);
        DrawMenuInt(g_Settings.windowColors[i], x + 72, 80 + i * 12, context);
    }
    func_800F5E68(
        context, g_MenuNavigation.cursorWindowColors, x - 2, 78, 120, 12, 0, 1);
}

void SortTimeAttackEntries(void) {
    s32 i;
    s32 isLooping;
    s32 swapTime;
    s32 swapName;

    // All the uninitialised time attack timers needs to be set to a large
    // value, so their record can be beat.
    for (i = 0; i < NUM_TIMEATTACK_EVENTS; i++) {
        g_TimeAttackEntryTimes[i] =
            TimeAttackController(i, TIMEATTACK_GET_RECORD);
        if (g_TimeAttackEntryTimes[i] == 0) {
            g_TimeAttackEntryTimes[i] = 1000000;
        }
        c_strTimeAttackEntry[i] = i;
    }

    // Ensure the time attacks are sequentially ordered by their timer
    do {
        isLooping = false;
        for (i = 0; i < NUM_TIMEATTACK_EVENTS - 1; i++) {
            swapTime = g_TimeAttackEntryTimes[i];
            if (g_TimeAttackEntryTimes[i + 1] < g_TimeAttackEntryTimes[i]) {
                g_TimeAttackEntryTimes[i] = g_TimeAttackEntryTimes[i + 1];
                g_TimeAttackEntryTimes[i + 1] = swapTime;
                swapName = c_strTimeAttackEntry[i];
                c_strTimeAttackEntry[i] = c_strTimeAttackEntry[i + 1];
                c_strTimeAttackEntry[i + 1] = swapName;
                isLooping++;
            }
        }
    } while (isLooping);
}

void DrawTimeAttackMenu(MenuContext* ctx) {
    s16 padX;
    s16 cursorX;
    s32 cursorY;
    s32 entryIdx;
    s32 offsetY;
    s32 i;
    s32 hours;
    s32 seconds;

    for (i = 0, offsetY = 8; i < 12; i++, offsetY += 12) {
        cursorX = ctx->cursorX;
        entryIdx = i + g_MenuNavigation.cursorTimeAttack;
        cursorY = ctx->cursorY + offsetY;
        DrawMenuInt(entryIdx + 1, cursorX + 16, cursorY, ctx);
        seconds = g_TimeAttackEntryTimes[entryIdx];
        if (seconds == 1000000) {
            DrawMenuStr(c_strTimeAttackHiddenEntry, cursorX + 29, cursorY, ctx);
        } else {
            DrawMenuStr(c_strTimeAttackEntries[c_strTimeAttackEntry[entryIdx]],
                        cursorX + 29, cursorY, ctx);
            hours = seconds / 10000;
#if defined(VERSION_HD)
            padX = -100;
#elif defined(VERSION_US)
            padX = 0;
#endif
            DrawMenuInt(hours, cursorX + 276 + padX, cursorY, ctx);
            DrawMenuChar(0x1A, cursorX + 284 + padX, cursorY, ctx);
            DrawMenuTime((seconds / 100) - (hours * 100), cursorX + 300 + padX,
                         cursorY, ctx, 2);
            DrawMenuChar(0x1A, cursorX + 308 + padX, cursorY, ctx);
            DrawMenuTime(seconds % 100, cursorX + 324 + padX, cursorY, ctx, 2);
        }
    }
}

void DrawSettingsButton(MenuContext* ctx) {
    s32 i;
    s32 x;
    s32 buttonId;
    s32 btn1_x;
    s32 btn2_x;
#if defined(VERSION_HD)
    const s32 InitCursorX = 0x80;
    const s32 W = 0x28;
#define XVAR cursorX
#elif defined(VERSION_US)
    const s32 InitCursorX = 0x98;
    const s32 W = 0x54;
#define XVAR x
#endif
    s32 cursorX = InitCursorX;

    for (i = 0, x = 0xC0; i < 7; i++) {
        DrawMenuStr(c_strButtonRightHand[i], cursorX, 0x30 + (i * 0x10), ctx);
        buttonId = g_Settings.buttonConfig[i];
        btn1_x = (buttonId * 12) + 0x30;
        DrawMenuChar(c_chPlaystationButtons[buttonId], XVAR + btn1_x,
                     0x30 + (i * 0x10), ctx);
        if (buttonId >= 4) {
            btn2_x = btn1_x + 8;
            DrawMenuChar(c_chShoulderButtons[buttonId], XVAR + btn2_x,
                         0x30 + (i * 0x10), ctx);
        }
    }

    func_800F5E68(
        ctx, g_MenuNavigation.cursorButtons, cursorX - 2, 46, W, 12, 4, 1);
#undef XVAR
}

void DrawSettingsReverseCloak(MenuContext* context) {
#if defined(VERSION_US)
    const int StrX = 176;
    const int ImgW = 64;
#elif defined(VERSION_HD)
    const int StrX = 128;
    const int ImgW = 40;
#endif

    DrawMenuStr(c_strNormal, StrX, 48, context);
    DrawMenuStr(c_strReversal, StrX, 64, context);
    func_800F5E68(context, g_Settings.isCloakLiningReversed, StrX - 2, 46, ImgW,
                  12, 4, 1);
}

void DrawSettingsSound(MenuContext* context) {
#if defined(VERSION_US)
    const int ImgW = 53;
#elif defined(VERSION_HD)
    const int ImgW = 37;
#endif

    s16 cursorX = context->cursorX;
    s16 cursorY = context->cursorY;
    s32 subMenuX = cursorX + 4;
    DrawMenuStr(c_strStereo, subMenuX, cursorY + 4, context);
    DrawMenuStr(c_strMono, subMenuX, cursorY + 0x14, context);
    func_800F5E68(context, g_Settings.isSoundMono, cursorX + 2, cursorY + 2,
                  ImgW, 12, 4, 1);
}

u8 StatChangeArrow(u16 arg0, u16 arg1) {
    if (arg0 == arg1) {
        return 0xE4; // Right arrow
    }
    if (arg0 < arg1) {
        return 0xE3; // Right-Up arrow

    } else {
        return 0xE5; // Right-Down arrow
    }
}

void func_800F7244(void) {
    s32 i;

    g_NewAttackRightHand = g_Status.attackHands[0];
    g_NewAttackLeftHand = g_Status.attackHands[1];
    g_NewDefenseEquip = g_Status.defenseEquip;

    for (i = 0; i < 4; i++) {
        g_NewPlayerStatsTotal[i] =
            g_Status.statsBase[i] + g_Status.statsEquip[i];
    }
}

extern s32 D_80137948;

void DrawStatChanges(void) {
    s32 xcoord;
    s32 ycoord;
    s32 i;
    MenuContext* ctx;
    s32 arrow;

    if ((g_MenuData.D_80137692 != 0) || (D_80137948 == 0)) {
        return;
    }
    ctx = &g_MenuData.menus[2];
    // Print the destination value for the square attack item
    DrawMenuInt(g_NewAttackRightHand, 0x154, 0x50, ctx);
    // Show arrow icon for increasing, decreasing, or staying the same
    arrow = StatChangeArrow(g_Status.attackHands[0], g_NewAttackRightHand);
    DrawMenuChar(arrow, 0x13C, 0x50, ctx);

    // Same but for the circle attack item
    DrawMenuInt(g_NewAttackLeftHand, 0x154, 0x5A, ctx);
    arrow = StatChangeArrow(g_Status.attackHands[1], g_NewAttackLeftHand);
    DrawMenuChar(arrow, 0x13C, 0x5A, ctx);
    // And repeat for defense.
    DrawMenuInt(g_NewDefenseEquip, 0x154, 0x6A, ctx);
    arrow = StatChangeArrow(g_Status.defenseEquip, g_NewDefenseEquip);
    DrawMenuChar(arrow, 0x13C, 0x6A, ctx);

    // Iterate through the 4 stats (STR CON INT LCK) doing the same.
    xcoord = 0x108;
    for (i = 0; i < 4; i++) {
        ycoord = 0x22 + i * 10;
        // Name of the stat
        DrawMenuStr((&c_strSTR)[i], xcoord, ycoord, ctx);
        // Current value for the stat
        DrawMenuInt(g_Status.statsBase[i] + g_Status.statsEquip[i],
                    xcoord + 0x2C, ycoord, ctx);
        // Indication of change
        arrow =
            StatChangeArrow((g_Status.statsBase[i] + g_Status.statsEquip[i]),
                            g_NewPlayerStatsTotal[i]);
        DrawMenuChar(arrow, xcoord + 0x34, ycoord, ctx);
        // Final value for the stat
        DrawMenuInt(g_NewPlayerStatsTotal[i], xcoord + 0x4C, ycoord, ctx);
    }
}

void DrawPauseMenu(s32 arg0) {
    MenuContext* ctx;
    s32 temp_s1;
    s32 temp_var;
    s32 x;
    s32 y;
    s32 i;
    s32 temp_y;
    s32 phi_a0_5;

    ctx = &g_MenuData.menus[arg0];
    func_800F53A4();
    if (arg0 == 1) {
        DrawMenuAlucardPortrait(ctx);
        DrawMenuStr(
            IsAlucart() ? c_strALUCARD[42] : c_strALUCARD[0], 128, 40, ctx);
        DrawMenuStr(c_strHP, 96, 56, ctx);
        DrawMenuInt(g_Status.hp, 168, 56, ctx);
        DrawMenuChar(CH('/'), 176, 56, ctx);
        DrawMenuInt(g_Status.hpMax, 208, 56, ctx);
        DrawMenuStr(c_strMP, 96, 68, ctx);
        DrawMenuInt(g_Status.mp, 168, 68, ctx);
        DrawMenuChar(CH('/'), 176, 68, ctx);
        DrawMenuInt(g_Status.mpMax, 208, 68, ctx);
        DrawMenuStr(c_strHEART, 96, 80, ctx);
        DrawMenuInt(g_Status.hearts, 168, 80, ctx);
        DrawMenuChar(CH('/'), 176, 80, ctx);
        DrawMenuInt(g_Status.heartsMax, 208, 80, ctx);
        DrawMenuStr(c_strEXP, 32, 176, ctx);
        DrawMenuInt(g_Status.exp, 144, 176, ctx);
        DrawMenuStr(c_strNEXT, 32, 188, ctx);
        DrawMenuInt(
            g_Status.level != 99 ? g_ExpNext[g_Status.level] - g_Status.exp : 0,
            144, 188, ctx);
        DrawMenuStr(c_strGOLD[0], 32, 200, ctx);
        DrawMenuInt(g_Status.gold, 144, 200, ctx);
        DrawMenuStr(c_strLEVEL, 248, 40, ctx);
        DrawMenuInt(g_Status.level, 304, 40, ctx);
        DrawMenuStr(c_strSTATUS, 248, 56, ctx);
        i = 37;
        if (g_Player.unk0C & PLAYER_STATUS_CURSE) {
            i = 40;
        }
        if (g_Player.unk0C & PLAYER_STATUS_POISON) {
            i = 38;
        }
        if (g_Player.unk0C & PLAYER_STATUS_STONE) {
            i = 39;
        }
        if (IsAlucart()) {
            i = 45;
        }
        DrawMenuStr(c_strGOLD[i - 7], 260, 68, ctx);
        DrawMenuStr(c_strROOMS, 240, 150, ctx);
        DrawMenuInt(g_RoomCount, 328, 150, ctx);
        DrawMenuStr(c_strKILLS, 240, 164, ctx);
        DrawMenuInt(g_Status.killCount, 328, 164, ctx);
        DrawMenuStr(c_strTIME, 208, 192, ctx);
        DrawMenuInt(g_Status.timerHours, 264, 192, ctx);
        DrawMenuChar(CH(':'), 272, 192, ctx);
        DrawMenuTime(g_Status.timerMinutes, 288, 192, ctx, 2);
        DrawMenuChar(CH(':'), 296, 192, ctx);
        DrawMenuTime(g_Status.timerSeconds, 312, 192, ctx, 2);
    }

    if (ctx == &g_MenuData.menus[1]) {
        x = 248;
        y = 88;
    } else {
        x = 232;
        y = 80;
    }
    func_800F66BC(D_800A2D68[0], x, y, ctx, 1);

    temp_var = g_Settings.buttonConfig[0];
    temp_s1 = temp_var;
    if (temp_s1 < 4) {
        DrawMenuChar(c_chPlaystationButtons[temp_s1], x + 44, y, ctx);
    } else {
        DrawMenuChar(c_chPlaystationButtons[temp_s1], x + 40, y, ctx);
        DrawMenuChar(c_chShoulderButtons[temp_s1], x + 48, y, ctx);
    }
    DrawMenuInt(g_Status.attackHands[0], x + 76, y, ctx);

    temp_var = g_Settings.buttonConfig[1];
    temp_s1 = temp_var;
    if (temp_s1 < 4) {
        DrawMenuChar(c_chPlaystationButtons[temp_s1], x + 44, y + 10, ctx);
    } else {
        DrawMenuChar(c_chPlaystationButtons[temp_s1], x + 40, y + 10, ctx);
        DrawMenuChar(c_chShoulderButtons[temp_s1], x + 48, y + 10, ctx);
    }

    DrawMenuInt(g_Status.attackHands[1], x + 76, y + 10, ctx);
#if defined(VERSION_US)
    func_800F66BC(D_800A2D68[1], x, y + 20, ctx, 1);
#elif defined(VERSION_HD)
    func_800F66BC(D_800A83AC[0], x, y + 20, ctx, 1);
#endif
    DrawMenuInt(g_Status.defenseEquip, x + 76, y + 26, ctx);
    if (ctx == (&g_MenuData.menus[1])) {
        x = 32;
        y = 120;
    } else {
#if defined(VERSION_US)
        DrawMenuStr(D_800A83AC[g_MenuNavigation.cursorEquip], 8, 40, ctx);
#elif defined(VERSION_HD)
        func_800F66BC(
            D_800A83AC[g_MenuNavigation.cursorEquip + 0x11], 24, 40, ctx, true);
#endif
        x = 12;
        y = 70;
    }

    for (i = 0, temp_y = y; i < 4; temp_y += 12, i++) {
        s32* statsBase = &g_Status.statsBase[i];
        DrawMenuStr((&c_strSTR)[i], x, temp_y, ctx);
        DrawMenuInt(*statsBase, x + 44, temp_y, ctx);
        if (g_Status.statsEquip[i] != 0) {
            if (g_Status.statsEquip[i] > 0) {
                DrawMenuChar(CH('+'), x + 52, temp_y, ctx);
                phi_a0_5 = g_Status.statsEquip[i];
            } else {
                DrawMenuChar(CH('-'), x + 52, temp_y, ctx);
                phi_a0_5 = -g_Status.statsEquip[i];
            }
            DrawMenuInt(phi_a0_5, x + 68, temp_y, ctx);
        }
    }
}

void DrawSpellMenu(MenuContext* ctx) {
    s32 buttonCFG;
    s32 spell;
    s32 charNum;
    s32 i;
    s32 colorIntensity;
    s32 yCoord;
    const u8* comboPointer;
#if defined(VERSION_US)
    s32 startXCoord = 176;
    DrawMenuStr(c_strSpecial2, 104, 40, ctx);
#elif defined(VERSION_HD)
    const s32 startXCoord = 172;
    func_800F66BC(D_800A2D24, 136, 36, ctx, 1);
#endif
    for (i = 0; i < NUM_SPELLS; i++) {
        spell = g_Status.spells[i];
        if (!(spell & 0x80)) {
            continue;
        }
        spell ^= 0x80;
        comboPointer = g_SpellDefs[spell].combo;
        charNum = 0;
        yCoord = 64 + i * 16;
        // Count up how many characters are in the combo
        while (*comboPointer != 0) {
            comboPointer++;
            charNum++;
        }
        charNum--;
#if defined(VERSION_US)
        // These spells start with an up-arrow colored red.
        if ((spell == SPELL_TETRA_SPIRIT) || (spell == SPELL_SWORD_BROTHERS)) {
            charNum -= 2;
        }
#endif
        if (spell != SPELL_WING_SMASH) {
            DrawMenuStr(g_SpellDefs[spell].combo, startXCoord, yCoord, ctx);
            DrawMenuChar(CH('+'), startXCoord + (charNum * 8), yCoord, ctx);
            buttonCFG = g_Settings.buttonConfig[0];
            charNum++;
            if (buttonCFG < 4) {
                DrawMenuChar(c_chPlaystationButtons[buttonCFG],
                             startXCoord + (charNum * 8), yCoord, ctx);
            } else {
                DrawMenuChar(c_chPlaystationButtons[buttonCFG],
                             startXCoord + (charNum * 8), yCoord, ctx);
                charNum++;
                DrawMenuChar(c_chShoulderButtons[buttonCFG],
                             startXCoord + (charNum * 8), yCoord, ctx);
            }
            // This writes the word "or", because spells say '{Square} or
            // {Circle}'
            charNum++;
            DrawMenuChar(CH('o'), startXCoord + (charNum * 8), yCoord, ctx);
            charNum++;
            DrawMenuChar(CH('r'), startXCoord + (charNum * 8), yCoord, ctx);
            buttonCFG = g_Settings.buttonConfig[1];
            charNum++;
            if (buttonCFG < 4) {
                DrawMenuChar(c_chPlaystationButtons[buttonCFG],
                             startXCoord + (charNum * 8), yCoord, ctx);
            } else {
                DrawMenuChar(c_chPlaystationButtons[buttonCFG],
                             startXCoord + (charNum * 8), yCoord, ctx);
                charNum++;
                DrawMenuChar(c_chShoulderButtons[buttonCFG],
                             startXCoord + (charNum * 8), yCoord, ctx);
            }
        } else {
            DrawMenuChar(CH('?'), startXCoord, yCoord, ctx);
            DrawMenuChar(CH('+'), startXCoord + 8, yCoord, ctx);
            DrawMenuStr(g_WingSmashComboStr, startXCoord + 16, yCoord, ctx);
            DrawMenuChar(
                CH('+'), startXCoord + 16 + (charNum * 8), yCoord, ctx);
            DrawMenuChar(
                CH('?'), startXCoord + 24 + (charNum * 8), yCoord, ctx);
        }
        DrawMenuStr(c_strMP, 292, yCoord, ctx);
        DrawMenuInt(g_SpellDefs[spell].mpUsage, 316, yCoord, ctx);
    }
    for (i = 0; i < 8; i++) {
        if (g_Status.spells[i] & 0x80) {
            DrawMenuImg(ctx, 0x1C, 0x3C + 0x10 * i, 0xF0, 0x10U, 0,
                        func_800F548C(-0x80 + i) & 0xFF, 0x1A1, 6, true, 0);
        }
    }
#if defined(VERSION_US)
    // The highlighted spell glows yellow, increasing and decreasing.
    if (g_Timer & 0x20) {
        colorIntensity = (g_Timer & 0x1F) + 0x60;
    } else {
        colorIntensity = 0x7F - (g_Timer & 0x1F);
    }
    // The colorIntensity gets passed to the MenuRect's R and G values, making
    // it a brighter or dimmer yellow.
    DrawMenuRect(ctx, 26, (g_MenuNavigation.cursorSpells * 0x10) + 0x3B, 300,
                 17, colorIntensity, colorIntensity, 0);
#elif defined(VERSION_HD)
    func_800F5E68(
        ctx, (g_MenuNavigation.cursorSpells), 0x1A, 0x3B, 0x12C, 0x11, -1, 1);
#endif
}

#if defined(VERSION_HD)
// TODO import 0x3C658 rodata first
INCLUDE_ASM("dra/nonmatchings/5298C", DrawMenuFamiliars);
#else
void DrawMenuFamiliars(MenuContext* menu) {
    s32 i;
    s32 baseX;
    s32 x;
    s32 y;
    s32 strId;
    s32 new_var;

    DrawMenuStr(c_strALUCARD[97], 120, 40, menu);
    for (i = 0; i < NUM_FAMILIARS; i++) {
        if (D_801375E0[i] == 0) {
            continue;
        }
        baseX = (i & 1) * 172;
        y = new_var = (i / 2) * 40;
        new_var = y + 68;
        x = baseX + 48;
        if (i == FAM_STATS_NOSE_DEMON) {
            x = baseX + 220;
        }
        strId = i + 46;
        DrawMenuStr(c_strALUCARD[strId], x, y + 68, menu);
        strId = 43;
        if (i < FAM_STATS_YOUSEI) {
            if (1) {
                strId = 8;
            }
        }
        DrawMenuStr(c_strALUCARD[strId], x + 56, y + 68, menu);
        DrawMenuInt(g_Status.statsFamiliars[i].level, x + 112, y + 68, menu);
        strId = 44;
        if (i < FAM_STATS_YOUSEI) {
            strId = 5;
        }
        DrawMenuStr(c_strALUCARD[strId], x + 56, y + 84, menu);
        DrawMenuInt(
            g_Status.statsFamiliars[i].exp % 100, x + 112, y + 84, menu);
        switch (i) {
        case FAM_STATS_BAT:
            DrawMenuImg(menu, 16, 64, 24, 30, 104, 129, 0x1D2, 0x1E, 1, 0);
            break;
        case FAM_STATS_GHOST:
            DrawMenuImg(menu, 176, 64, 40, 30, 32, 161, 0x1D1, 0x1E, 1, 0);
            break;
        case FAM_STATS_FAERIE:
            DrawMenuImg(menu, 12, 104, 32, 30, 72, 129, 0x1D4, 0x1E, 1, 0);
            break;
        case FAM_STATS_DEMON:
            DrawMenuImg(menu, 180, 104, 32, 30, 0, 225, 0x1D6, 0x1E, 1, 0);
            break;
        case FAM_STATS_SWORD:
            DrawMenuImg(menu, 12, 144, 32, 54, 0, 129, 0x1D0, 0x1E, 1, 0);
            break;
        case FAM_STATS_YOUSEI:
            DrawMenuImg(menu, 176, 144, 40, 30, 32, 129, 0x1D3, 0x1E, 1, 0);
            break;
        case FAM_STATS_NOSE_DEMON:
            DrawMenuImg(menu, 180, 184, 32, 38, 0, 185, 0x1D5, 0x1E, 1, 0);
            break;
        }
    }
}
const u32 rodataPadding_DrawMenuFamiliars_jtbl = 0;
#endif

void func_800F82F4(void) {
    RECT dstRect;

    dstRect.x = 448;
    dstRect.y = 176;
    dstRect.w = g_imgUnk8013C200->width >> 2;
    dstRect.h = g_imgUnk8013C200->height;
    LoadImage(&dstRect, (u_long*)g_imgUnk8013C200->data);

    dstRect.x = 480;
    dstRect.w = g_imgUnk8013C270->width >> 2;
    dstRect.h = g_imgUnk8013C270->height;
    LoadImage(&dstRect, (u_long*)g_imgUnk8013C270->data);
}

void DrawSystemMenu(MenuContext* ctx) {
#if defined(VERSION_US)
    const int Width = 128;
#else
    const int Width = 80;
#endif

    const char** new_var;
    s32 strIdx;
    s8** menuOptions;

    func_800F5E68(ctx, g_MenuNavigation.cursorSettings, 30, 46, Width, 12, 4,
                  D_800978F8 == 0x101);

    new_var = &c_strButton;
    DrawMenuStr(*new_var, 0x20, 0x30, ctx);

    strIdx = g_IsCloakLiningUnlocked ? 0x11 : 0x13;
    menuOptions = (&c_strButton) - 0x10;
    DrawMenuStr(menuOptions[strIdx], 32, 64, ctx);

    strIdx = g_IsCloakColorUnlocked ? 0x12 : 0x13;
    DrawMenuStr(menuOptions[strIdx], 32, 80, ctx);
    DrawMenuStr(c_strWindow, 32, 96, ctx);
    DrawMenuStr(c_strSound, 32, 112, ctx);

    strIdx = g_IsTimeAttackUnlocked ? 0x24 : 0x13;
    DrawMenuStr(menuOptions[strIdx], 32, 128, ctx);
}

void func_800F84CC(void) {
    Primitive* prim;
    s32 i;
    s32 primIndex;

    for (i = 0; i < LEN(D_801377FC); i++) {
        D_801377FC[i] = func_800EDD9C(PRIM_G4, 1);
        prim = &g_PrimBuf[D_801377FC[i]];
        prim->blendMode = BLEND_VISIBLE;
    }

    D_8013783C = func_800EDD9C(PRIM_GT4, 1);
    prim = &g_PrimBuf[D_8013783C];
    SetPrimRect(prim, 20, 195, 42, 28);
    prim->u0 = 113;
    prim->v0 = 177;
    prim->u1 = 127;
    prim->v1 = 177;
    prim->u2 = 113;
    prim->v2 = 191;
    prim->u3 = 127;
    prim->v3 = 191;
    prim->tpage = 0x1A;
    prim->clut = 0x1EF;
    prim->priority = 0x40;
    prim->blendMode = 0x80 | BLEND_VISIBLE;

    D_80137840 = func_800EDD9C(PRIM_GT4, 2);
    prim = &g_PrimBuf[D_80137840];
    for (i = 0; prim; i++) {
        prim->x0 = prim->x2 = 7;
        prim->x1 = prim->x3 = 23;
        prim->v0 = prim->v1 = 48;
        prim->v2 = prim->v3 = 64;
        if (i == 0) {
            prim->y0 = prim->y1 = 124;
            prim->u0 = prim->u2 = 80;
        } else {
            prim->y0 = prim->y1 = 174;
            prim->u0 = prim->u2 = 96;
        }
        prim->y2 = prim->y3 = prim->y0 + 0x10;
        prim->u1 = prim->u3 = prim->u0 + 0x10;
        func_80107250(prim, 64);
        prim->tpage = 0x1A;
        prim->priority = 0x40;
        prim->blendMode = BLEND_VISIBLE;
        prim = prim->next;
    }
}

void func_800F86E4(void) {
    s32 i;

    for (i = 0; i < 16; i++) {
        FreePrimitives(D_801377FC[i]);
    }

    FreePrimitives(D_8013783C);
    FreePrimitives(D_80137840);
}

#if defined(VERSION_US)
void func_800F8754(MenuContext* menu, s32 x, s32 y) {
    if (D_801375DC == 0) {
        D_8013784C = 1;
    }

    DrawMenuStr(c_strSpells, x + 14, y + 20, menu);
    if (D_801375FC == 0) {
        D_8013784C = 1;
    } else {
        D_8013784C = 0;
    }

    DrawMenuStr(c_strFamiliars, x + 2, y + 68, menu);
    D_8013784C = 0;
    DrawMenuStr(c_strEquip, x + 18, y + 4, menu);
    DrawMenuStr(c_strRelics, x + 14, y + 36, menu);
    DrawMenuStr(c_strSystem, x + 14, y + 52, menu);
}
#elif defined(VERSION_HD)
void func_800F8754(MenuContext* menu, s32 x, s32 y) {
    func_800F66BC(c_strSpells, x + 0xC, y, menu, true);
    func_800F66BC(c_strFamiliars, x + 6, y + 0x10, menu, D_801375DC != 0);
    func_800F66BC(c_strEquip, x + 6, y + 0x20, menu, true);
    func_800F66BC(c_strRelics, x, y + 0x30, menu, true);
    func_800F66BC(c_strSystem, x + 6, y + 0x40, menu, D_801375FC != 0);
}
#endif

void func_800F8858(MenuContext* context) {
#if defined(VERSION_US)
    const int TextY = 8;
    const int UnkX = 72;
#elif defined(VERSION_HD)
    const int TextY = 4;
    const int UnkX = 40;
#endif
    s32 i = 0;
    const char** pStrEquipTypes = &c_strSSword;
    s32 y = TextY;

    for (; i < ITEM_END; i++) {
#if defined(VERSION_US)
        DrawMenuStr(pStrEquipTypes[g_Settings.equipOrderTypes[i]],
                    context->cursorX + 4, context->cursorY + y, context);
#elif defined(VERSION_HD)
        func_800F66BC(
            pStrEquipTypes[g_Settings.equipOrderTypes[i]], context->cursorX + 4,
            context->cursorY + y, context, true);
#endif
        y += 16;
    }
    func_800F5E68(context, D_80137618, context->cursorX + 2,
                  context->cursorY + 4, UnkX, 16, 0, true);
}

void func_800F892C(s32 index, s32 x, s32 y, MenuContext* menu) {
    DrawMenuImg(menu, x, y, 16, 16, (index & 7) * 16,
                ((index & 0xF8) * 2) | 0x80, index + 0x1D0, 0x1A, 1, 0);
}

void func_800F8990(MenuContext* ctx, s32 x, s32 y) {
    const s32 Cols = 2;
    const s32 Width = 168;
    const s32 Height = 12;

    u8* sp20;
    s32 itemsPerPage;
    s32* new_var;
    s32 totalItemCount;
    s32 curX;
    s32 curY;
    s32 myX;
    s32 myY;
    s32 itemIndex;
    s32 i;
    s8* strEquipName;
    u16 icon;
    u16 palette;
    u8 equipId;
    u8* equipsAmount;
    s32 idx;

    new_var = &D_801375CC.equipTypeFilter;
    sp20 = GetEquipOrder(*new_var);
    equipsAmount = GetEquipCount(*new_var);
    totalItemCount = func_800FD6C4(*new_var);
    curX = 0;
    curY = 0;
    itemsPerPage = Cols + ctx->cursorH / Height * Cols;
    for (i = 0; i < itemsPerPage; i++) {
        itemIndex = i + -ctx->h / Height * Cols;
        if (itemIndex >= totalItemCount) {
            break;
        }

        myX = 40 + x + (itemIndex & 1) * Width;
        myY = 4 + y + itemIndex / 2 * Height;
        if (g_IsSelectingEquipment && itemIndex == g_EquipmentCursor) {
            curX = myX + 1;
            curY = myY - 2;
        }

        equipId = sp20[D_801375D8[itemIndex]];
        if (equipsAmount[equipId] == 0)
            continue;

        strEquipName = GetEquipmentName(*new_var, equipId);
        if (D_801375CC.equipTypeFilter == 0) {
            icon = g_EquipDefs[equipId].icon;
            palette = g_EquipDefs[equipId].iconPalette;
        } else {
            icon = g_AccessoryDefs[equipId].icon;
            palette = g_AccessoryDefs[equipId].iconPalette;
        }

        LoadEquipIcon(icon, palette, i);
        func_800F892C(i, myX - 16, myY - 4, ctx);
        DrawMenuStr(strEquipName, myX, myY, ctx);

        if (D_801375CC.equipTypeFilter == 0 && equipId != 0 ||
            D_801375CC.equipTypeFilter != 0 && equipId != 0x1A &&
                equipId != 0 && equipId != 0x30 && equipId != 0x39) {
            DrawMenuInt(equipsAmount[equipId], myX + 128, myY, ctx);
        }
    }

    if (g_IsSelectingEquipment) {
        func_800F6508(ctx, curX, curY);
    }
}

void BlinkMenuCursor(s32 left, s32 top, s32 right, s32 bottom, s32 arg4) {

    s32 var_s2;
    u8 blink_value;

    u32* ot = g_CurrentBuffer->ot;
    LINE_G2* temp_s0 = &g_CurrentBuffer->lineG2[g_GpuUsage.line];

    if (arg4 != 0) {
        var_s2 = g_MenuData.menus[arg4 - 1].otIdx + 4;
    } else {
        var_s2 = 0x80;
    }

    SetSemiTrans(temp_s0, 0);
    SetShadeTex(temp_s0, 1);

    if (g_Timer & 0x20) {
        blink_value = g_Timer & 0x1F;
    } else {
        blink_value = 0x1F - (g_Timer & 0x1F);
    }
    blink_value *= 4;
    blink_value -= 0x80;

    if (arg4 != 0) {
        blink_value = 0xFF;
    }

    temp_s0->r0 = blink_value;
    temp_s0->g0 = blink_value;
    temp_s0->b0 = blink_value;
    temp_s0->r1 = blink_value;
    temp_s0->g1 = blink_value;
    temp_s0->b1 = blink_value;
    temp_s0->x0 = left;
    temp_s0->y0 = top;
    temp_s0->x1 = right;
    temp_s0->y1 = bottom;
    AddPrim(&ot[var_s2], temp_s0);
    g_GpuUsage.line++;
}

void DrawConsumableCount(s32 itemId, s32 hand, MenuContext* ctx) {
    u8 outstring[16];
    u8* str_idx;
    s32 displayCount;
    u8 equipCount;

    if (g_EquipDefs[itemId].isConsumable != 0) {
        // This holds one less than how many you have.
        equipCount = g_Status.equipHandCount[itemId];
        str_idx = &outstring;
        // First character in the string is the (
        *str_idx++ = MENUCHAR('(');
        // This is now how many you have.
        displayCount = equipCount + 1;
        if (displayCount < 10) {
            // Get the character code for the count.
            *str_idx++ = equipCount + 1 + MENUCHAR('0');
        } else {
            if (displayCount == 100) {
                *str_idx++ = MENUCHAR('1');
                // Neat trick, set this to 0 so following two steps draw
                // 00
                displayCount = 0;
            }
            *str_idx++ = (displayCount / 10) + MENUCHAR('0');
            *str_idx++ = (displayCount % 10) + MENUCHAR('0');
        }
        // Finish off with a ) and string terminator
        *str_idx++ = MENUCHAR(')');
        *str_idx++ = 0xFF;
        *str_idx++ = 0;
        // Draw it after the item name. X=224, Y = 30 + 13*hand
        DrawMenuStr(&outstring, 224, (hand * 13) + 30, ctx);
    }
}

#if defined(VERSION_HD)
INCLUDE_ASM("dra/nonmatchings/5298C", DrawMenu);
#elif defined(VERSION_US)
void DrawMenu(void) {
    u8 padding[32];
    s32 x;
    s32 y;
    Accessory* acc;
    Equipment* equip;
    MenuContext* menu;
    Primitive* prim;
    s16 swap;
    s32 ch;
    s32 cy;
    s32 cx;
    s32 cw;
    s16 r0;
    s16 g0;
    s16 b0;
    s16 r1;
    s16 g1;
    s16 b1;
    s32 var_a1;
    s32 cursorXMovement;
    s32 equipIndex;
    s32 flag;
    s32 i;
    s32 j;
    s32 new_var2;
    s32 stuff;
    s32 stuffed;

    for (i = 0; i < 0x10; i++) {
        prim = &g_PrimBuf[D_801377FC[i]];
        menu = &g_MenuData.menus[i];
        if (menu->unk1C == 2) {
            prim->blendMode = 8;
            continue;
        }
        cx = menu->cursorX;
        cy = menu->cursorY;
        cw = menu->cursorW;
        ch = menu->cursorH;
        var_a1 = menu->unk14 - menu->w;
        if (var_a1 == 1) {
            var_a1 = 2;
        }
        new_var2 = -1;
        if (var_a1 == new_var2) {
            var_a1 = -2;
        }
        menu->w += var_a1 / 2;

        var_a1 = menu->unk16 - menu->h;
        if (var_a1 == 1) {
            var_a1 = 2;
        }
        if (var_a1 == -1) {
            var_a1 = -2;
        }
        menu->h += var_a1 / 2;

        x = cx + menu->w;
        y = cy + menu->h;

        if (menu->unk1C == 1) {
            menu->unk1D++;
            j = menu->unk1D; // FAKE?
            if (menu->unk1D == 16) {
                menu->unk1C = 2;
                prim->blendMode = 8;
                continue;
            }
            cy += ch / 16 * menu->unk1D;
            ch -= ch / 16 * menu->unk1D;
            j = 16 - menu->unk1D;

            cursorXMovement = cw / 2 * (128 - D_800A2D80[j]) / 128;
            cx += cursorXMovement;
            cw -= cursorXMovement * 2;
        }
        if (menu->unk1C == 3) {
            menu->unk1D++;
            j = menu->unk1D; // FAKE?
            if (menu->unk1D == 16) {
                menu->unk1C = 0;
            } else {
                cursorXMovement =
                    cw / 2 * (128 - D_800A2D80[menu->unk1D]) / 128;
                cx += cursorXMovement;
                cw -= cursorXMovement * 2;
                j = 16 - menu->unk1D; // FAKE?
                var_a1 = ch / 16 * j;
                ch -= var_a1;
            }
        }
        menu->unk1.x = cx;
        menu->unk1.y = cy;
        menu->unk1.w = cw;
        menu->unk1.h = ch;
        SetPrimRect(prim, cx, cy, cw, ch);

        r0 = g_Settings.windowColors[0] * 8 - 0x20;
        if (r0 < 0) {
            r0 = 0;
        }
        g0 = g_Settings.windowColors[1] * 8 - 0x20;
        if (g0 < 0) {
            g0 = 0;
        }
        b0 = g_Settings.windowColors[2] * 8 - 0x20;
        if (b0 < 0) {
            b0 = 0;
        }
        r1 = g_Settings.windowColors[0] * 8 + 0x20;
        if (r1 >= 0x100) {
            r1 = 0xFF;
        }
        g1 = g_Settings.windowColors[1] * 8 + 0x20;
        if (g1 >= 0x100) {
            g1 = 0xFF;
        }
        b1 = g_Settings.windowColors[2] * 8 + 0x20;
        if (b1 >= 0x100) {
            b1 = 0xFF;
        }
        if (g_StageId >= 0x20 && g_StageId < 0x40) {
            swap = r0;
            r0 = r1;
            r1 = swap;
            swap = g0;
            g0 = g1;
            g1 = swap;
            swap = b0;
            b0 = b1;
            b1 = swap;
        }
        prim->r0 = r0;
        prim->g0 = g0;
        prim->b0 = b0;
        prim->r1 = r0;
        prim->g1 = g0;
        prim->b1 = b0;
        prim->r2 = r1;
        prim->g2 = g1;
        prim->b2 = b1;
        prim->r3 = r1;
        prim->g3 = g1;
        prim->b3 = b1;
        prim->priority = menu->otIdx;
        prim->blendMode = 0x480;

        BlinkMenuCursor(cx, cy, cx, cy + ch - 1, i + 1);
        BlinkMenuCursor(cx, cy, cx + cw - 1, cy, i + 1);
        BlinkMenuCursor(cx + cw - 1, cy, cx + cw - 1, cy + ch - 1, i + 1);
        BlinkMenuCursor(cx, cy + ch - 1, cx + cw - 1, cy + ch - 1, i + 1);

        switch (i) {
        case 0:
            func_800F6568(menu);
            func_800F8754(menu, x, y);
            break;
        case 1:
            DrawPauseMenu(1);
            break;
        case 2:
            DrawPauseMenu(2);
            equipIndex = g_Status.equipment[0];
            equip = &g_EquipDefs[equipIndex];
            DrawMenuStr(equip->name, 112, 30, menu);
            DrawConsumableCount(equipIndex, 0, menu);
            LoadEquipIcon(equip->icon, equip->iconPalette, 0x10);

            equipIndex = g_Status.equipment[1];
            equip = &g_EquipDefs[equipIndex];
            DrawMenuStr(equip->name, 112, 43, menu);
            DrawConsumableCount(equipIndex, 1, menu);
            flag = equip->itemCategory == 5;
            LoadEquipIcon(equip->icon, equip->iconPalette, 0x11);

            for (j = 0; j < 5; j++) {
                acc = &g_AccessoryDefs[g_Status.equipment[j + 2]];
                DrawMenuStr(acc->name, 112, 56 + j * 13, menu);
                LoadEquipIcon(acc->icon, acc->iconPalette, j + 0x12);
            }

            for (j = 0; j < 7; j++) {
                if (j >= 0 && j < 2 && flag) {
                    if (j == 0) {
                        func_800F892C(0x10, 0x5E, 0x20, menu);
                    }
                } else {
                    func_800F892C(j + 0x10, 0x5E, 0x1a + j * 13, menu);
                }
            }
            func_800F6618(i, D_800978F8 != 0x40);
            break;
        case 3:
            func_800F8990(menu, x, y);
            DrawStatChanges();
            break;
        case 4:
            func_800F5AE4(menu);
            break;
        case 5:
            DrawRelicsMenu(menu);
            break;
        case 6:
            DrawSpellMenu(menu);
            break;
        case 7:
            DrawSystemMenu(menu);
            break;
        case 8:
            DrawMenuAlucardCloakPreview(menu);
            DrawJosephsCloakMenu(menu);
            break;
        case 9:
            DrawSettingsButton(menu);
            break;
        case 10:
            DrawSettingsReverseCloak(menu);
            break;
        case 11:
            DrawSettingsSound(menu);
            break;
        case 12:
            func_800F6BEC(menu);
            break;
        case 13:
            DrawTimeAttackMenu(menu);
            break;
        case 14:
            func_800F8858(menu);
            break;
        case 15:
            DrawMenuFamiliars(menu);
            break;
        }
    }
}
#endif

void func_800F9690(void) {
    POLY_GT4* poly = &g_PrimBuf[D_8013783C];

    if (D_80137608 != 0) {
        poly->pad3 = 0x80;
    } else {
        poly->pad3 = 0x8;
    }
    if (D_801376B0 != 0) {
        poly->pad3 = 0x8;
    }
}

void func_800F96F4(void) { // !Fake:
    s32 new_var2;
    POLY_GT4* poly;
    s32 temp_a2;
    s32* temp;
    s32* new_var;

    new_var = D_80137848;
    poly = &g_PrimBuf[D_80137840];
    temp_a2 = g_MenuData.D_80137692 == 0;
    temp = D_80137844;

    if ((D_80137844[0] != 0) && (temp_a2 != 0)) {
        (&g_PrimBuf[D_80137840])->blendMode = 0x80;
        if (D_80137844[0] == 1) {
            (&g_PrimBuf[D_80137840])->clut = 0x188;
        } else {
            D_80137844[0] -= 1;
            (&g_PrimBuf[D_80137840])->clut = 0x181;
        }
    } else {
        poly->pad3 = 0x8;
    }

    poly = (POLY_GT4*)poly->tag;
    temp = new_var;

    if (((*temp) != 0) && (temp_a2 != 0)) {
        poly->pad3 = 0x80;
        new_var2 = *temp;
        if (new_var2 == 1) {
            do {
                poly->clut = 0x188;
            } while (0);
            return;
        }
        *temp -= 1;
        poly->clut = 0x181;
        return;
    }
    poly->pad3 = 8;
}

void func_800F97DC(void) {
    D_8013794C = g_Pix[0];
    D_80137950 = 0x180;
    D_80137954 = 0;
}

void func_800F9808(u32 arg0) {
    s32 temp_s0;
    s32 i;
    u8* oldPos;

    temp_s0 = (arg0 == 2) ? 32 : 0;
    arg0 = func_800F548C(arg0);
    oldPos = D_8013794C;

    for (i = 0; i < ((temp_s0 + 0x100) * 8); i++) {
        *D_8013794C++ = 0;
    }

    LoadTPage(oldPos, 0, 0, 0x180, arg0, temp_s0 + 256, 16);
}

void func_800F98AC(u8* arg0, u32 arg1) {
    u32 temp_s2;
    s32 i;
    u8* data_ptr;
    s32 var_s1;
    u8* var_a1;
    u32 loaded_data;

    temp_s2 = arg1;
    var_s1 = (temp_s2 >> 2) & 0x40;
    temp_s2 = func_800F548C(temp_s2);

    for (data_ptr = arg0; *data_ptr != 0;) {
        // Loads a big-endian u16 from data_ptr.
        // This is connected to shift-jis.
        loaded_data = *data_ptr++ << 8;
        loaded_data += *data_ptr++;
        var_a1 = func_80106A28(loaded_data, 0);
        for (i = 0; i < 0x60; i++) {
            D_8013794C[i] = *var_a1++;
        }
        LoadTPage((PixPattern*)D_8013794C, 0, 0, var_s1 + D_80137950,
                  temp_s2 + D_80137954, 0xC, 0x10);
        D_8013794C += 0x60;
        var_s1 += 3;
    }
}

#if defined(VERSION_US)
void func_800F99B8(u8* str, s32 arg1, s32 arg2) {
    // See src/st/blit_char.h
    const u16 MINSCODE = 0x8140;
    const u16 RIGHT_DOUBLE_QUOTATION_MARK = 0x8168;

    const int FontWidth = 12;
    const int FontHeight = 16;
    const int FontStride = FontWidth / 2;

    s32 var_a0;
    u8* var_a2;
    s32 var_a3;
    u8 var_s0;
    u8* var_s1;
    s32 var_s2;
    s32 var_s3;
    s32 var_s4;
    s32 var_s5;
    s32 var_s6;
    s32 i;
    s32 j;
    u8* dest_addr;

    var_s1 = str;
    var_s5 = arg1;
    if (arg2 == 0) {
        var_s4 = 0x90;
    } else {
        var_s4 = 0x3C;
    }
    for (i = 0; i < var_s4 * FontHeight; i++) {
        D_8013794C[i] = 0;
    }
    var_s6 = ((u32)var_s5 >> 2) & 0x40;
    var_s3 = 0;
    if (var_s5 & 0x200) {
        var_s6 += 0x20;
        var_s5 &= ~0x200;
    }
    var_s5 = func_800F548C(var_s5 & 0xFF) & 0xFF;
    while (*var_s1 != 0) {
        var_s2 = 0;
        var_s0 = *var_s1++;
        if ('a' <= var_s0 && var_s0 <= 'z') {
            var_a0 = var_s0 + 0x8220;
        } else if ('A' <= var_s0 && var_s0 <= 'Z') {
            var_a0 = var_s0 + 0x821F;
        } else if (var_s0 == ' ') {
            var_a0 = MINSCODE;
            var_s2 = 2;
        } else {
            // load var_a0 as a big-endian value corresponding with shift-jis
            var_a0 = (var_s0 << 8);
            var_a0 += *var_s1++;
            if (var_a0 == RIGHT_DOUBLE_QUOTATION_MARK) {
                var_s1 += 2;
            }
            if (var_a0 == MINSCODE) {
                var_s0 = ' ';
                var_s2 = 2;
            }
        }
        var_a2 = func_80106A28(var_a0, 0);
        while (1) {
            if (var_s0 == ' ') {
                break;
            }
            for (i = 0; i < FontHeight; i++) {
                // probably fake, i think var_a2 is a 2d array like [6][??]
                if (var_a2[i * FontStride] != 0) {
                    break;
                }
            }
            if (i != FontHeight) {
                break;
            }
            for (i = 0; i < FontHeight; i++) {
                dest_addr = &var_a2[i * FontStride];
                // Effectively shift everything down an index
                for (j = 0; j < 5; j++) {
                    dest_addr[0] = dest_addr[1];
                    dest_addr += 1;
                }
                // Set last index to 0
                *dest_addr = 0;
            }
        }
        for (i = 0, var_a3 = 0; i < FontHeight; i++) {
            for (j = 0; j < FontStride; j++) {
                // similar to above comment, this could be var_a2[i][j]
                if ((var_a2[i * FontStride + j] != 0) && (var_a3 < j)) {
                    var_a3 = j;
                }
            }
        }
        for (i = 0; i < FontHeight; i++) {
            if ((var_a2[i * FontStride + var_a3] & 0xF0)) {
                break;
            }
        }
        if (i != FontHeight) {
            var_a3 += 1;
        }
        if (var_a3 < FontStride) {
            var_a3 += 1;
        }
        for (i = 0; i < FontHeight; i++) {
            dest_addr = &D_8013794C[var_s3 + var_s4 * i];
            *dest_addr++ = *var_a2++;
            *dest_addr++ = *var_a2++;
            *dest_addr++ = *var_a2++;
            *dest_addr++ = *var_a2++;
            *dest_addr++ = *var_a2++;
            *dest_addr++ = *var_a2++;
        }
        var_s3 += var_a3 + var_s2;
        if (var_s3 >= var_s4) {
            break;
        }
    }

    LoadTPage((PixPattern*)D_8013794C, 0, 0, var_s6 + D_80137950,
              var_s5 + D_80137954, var_s4 * 2, 0x10);
    D_8013794C += var_s4 * 0x10;
}
#endif

void func_800F9D40(s32 arg0, s32 arg1, s32 arg2) {
    if (arg2 != 0) {
        D_8013794C = g_Pix[2];
    }

    D_80137950 = 0;
    D_80137954 = 0x100;
    func_800F98AC(arg0, arg1);
}

#if defined(VERSION_US)
void func_800F9D88(s32 arg0, s32 arg1, s32 arg2) {
    if (arg2 != 0) {
        D_8013794C = g_Pix[2];
    }
    D_80137950 = 0;
    D_80137954 = 0x100;
    func_800F99B8(arg0, arg1, 0);
}
#endif

void func_800F9DD0(u8* arg0, u8* arg1) {
    s32 i;

    for (i = 0; i < 16; i++) {
        if (*arg0 == 0)
            break;
        *arg1++ = *arg0++;
        *arg1++ = *arg0++;
    }
}

#if defined(VERSION_HD)
INCLUDE_ASM("dra/nonmatchings/5298C", func_800F9E18);
#else
void func_800F9E18(s32 arg0) {
    const int ItemsPerRow = 2;
    char buffer[38];
    s32 nHalfScreenSize = arg0 * 5;
    s32 i = (arg0 * 5) + 5;
    s32 nItems = i;

    if (arg0 == 0) {
        ClearImage(&D_800A2D90, 0, 0, 0);
        DrawSync(0);
    }

    for (i = nHalfScreenSize; i < nItems; i++, nHalfScreenSize++) {
        strcpy(buffer, g_RelicDefs[i * ItemsPerRow + 0].name);
        if ((nHalfScreenSize % ItemsPerRow) == 0) {
            func_800F99B8(buffer, (nHalfScreenSize / ItemsPerRow) + 128, 1);
        } else {
            func_800F99B8(buffer, (nHalfScreenSize / ItemsPerRow) + 259, 1);
        }

        strcpy(buffer, g_RelicDefs[i * ItemsPerRow + 1].name);
        if ((nHalfScreenSize % ItemsPerRow) == 0) {
            func_800F99B8(buffer, (nHalfScreenSize / ItemsPerRow) + 640, 1);
        } else {
            func_800F99B8(buffer, (nHalfScreenSize / ItemsPerRow) + 771, 1);
        }
    }
}
#endif

void func_800F9F40(void) {
    Unkstruct_800F9F40* var_a2;
    Unkstruct_800F9F40* var_a3;
    Unkstruct_800F9F40* ptr;
    char buffer[38];
    s32 idx;
    u8 spellId;
    s32 i;

    for (i = 0, ptr = D_800DC70C, idx = 0x80; i < 8; i++) {
        spellId = D_80097902[idx];
        if (spellId & 0x80) {
            spellId ^= 0x80;
            var_a3 = (Unkstruct_800F9F40*)buffer;
            var_a2 = (Unkstruct_800F9F40*)&D_800DC6EC;
            do {
                __builtin_memcpy(var_a3++, var_a2++, 0x10);
            } while (var_a2 != ptr);
            __builtin_memcpy(var_a3++, var_a2++, 0xB);
            func_800F9DD0(g_SpellDefs[spellId].name, buffer);
#if defined(VERSION_US)
            func_800F99B8(&buffer, idx, 0);
#elif defined(VERSION_HD)
            func_800F98AC(&buffer, idx);
#endif
        }
        idx++;
    }
}

INCLUDE_ASM("dra/nonmatchings/5298C", func_800FA034);

void func_800FA3C4(s32 arg0, s32 arg1, s32 arg2) {
    // FAKE: Should figure out how this actually works.
    // Could be that 7676 is the start of another struct within MenuData.
    s16* menuitem = &g_MenuData.D_80137676;
    s32 limit;
    s32 top_offset;
    s32 arg0_lowbit;
    s32 left;
    s32 top;
    s32 half_arg0;

    if (g_MenuData.D_80137692 != 0) {
        return;
    }
    arg0_lowbit = arg0 & 1;
    half_arg0 = (arg0 / 2);

    left = (arg0_lowbit * 0xA8) + 0x28;
    limit = -(g_MenuData.D_8013768C / 12);

    // Below some limit
    if (half_arg0 < limit) {
        g_MenuData.D_8013768C += 12;
        top = g_MenuData.D_80137678[0] + 1;
        // Beyond that limit, on the other side
    } else if (half_arg0 >= (limit + g_MenuData.D_80137678[2] / 12)) {
        g_MenuData.D_8013768C -= 12;
        top_offset = ((g_MenuData.D_80137678[2] / 12 - 1) * 12) + 1;
        top = g_MenuData.D_80137678[0] + top_offset;
        // Somewhere in between
    } else {
        top = ((half_arg0 - limit) * 12) + g_MenuData.D_80137678[0] + 1;
    }

    // Here is where we use the menuitem, again, FAKE.
    if (D_801375CC.equipTypeFilter == 0) {
        g_MenuNavigation.scrollEquipHand = menuitem[11];
    } else {
        g_MenuNavigation.scrollEquipAccessories[D_801375D4] = menuitem[11];
    }
    if (arg2 != 0) {
        if (arg1 == 0) {
            BlinkMenuCursor(left, top, left + 0x70, top, 0);
            BlinkMenuCursor(left, top, left, top + 0xB, 0);
            BlinkMenuCursor(left + 0x70, top, left + 0x70, top + 0xB, 0);
            BlinkMenuCursor(left, top + 0xB, left + 0x70, top + 0xB, 0);
        } else {
            BlinkMenuCursor(left, top, left + 0x70, top + 0xB, 0);
            BlinkMenuCursor(left, top + 0xB, left + 0x70, top, 0);
        }
    }
}

INCLUDE_ASM("dra/nonmatchings/5298C", func_800FA60C);

// If you use both attack buttons at once, see if something special
// happens. Applies to Shield Rod + Shield, or dual Heaven Swords
void CheckWeaponCombo(void) {
    s32 weapon0;
    s32 weapon1;
    s32 combo1;
    s32 combo2;
    s32 comboBits;
    s32 i;
    s32 oddComboCheck;

    weapon0 = g_Status.equipment[LEFT_HAND_SLOT];
    weapon1 = g_Status.equipment[RIGHT_HAND_SLOT];

    combo1 = g_EquipDefs[weapon0].comboSub & g_EquipDefs[weapon1].comboMain;
    oddComboCheck = 0x80000000;
    oddComboCheck &= -(combo1 == 0);

    combo2 = g_EquipDefs[weapon0].comboMain & g_EquipDefs[weapon1].comboSub;
    comboBits = combo1 | combo2;

    if (comboBits != 0) {
        for (i = 0xAA; i < 0xD9; i++) {
            if (comboBits & g_EquipDefs[i].comboSub) {
                D_8013AEE4 = oddComboCheck + i;
                return;
            }
        }
    }
    D_8013AEE4 = 0;
}

bool LoadWeaponPrg(s32 equipIndex) {
    s32 equipId;
    s32 weaponId;

    equipId = g_Status.equipment[equipIndex];
    if (g_Status.equipment[ARMOR_SLOT] == ITEM_AXE_LORD_ARMOR) {
        equipId = 0xD8;
    }

    weaponId = g_EquipDefs[equipId].weaponId;
    if (weaponId == D_8003C90C[equipIndex] || weaponId == 0xFF) {
        return 1;
    }

    if (g_UseDisk) {
        if (g_IsUsingCd) {
            return 0;
        }
        g_CdStep = CdStep_LoadInit;
        g_LoadFile = CdFile_Weapon0 + equipIndex;
    } else {
        if (LoadFileSim(weaponId, SimFileType_Weapon0Prg + equipIndex) < 0 ||
            LoadFileSim(weaponId, SimFileType_Weapon0Chr + equipIndex) < 0) {
            return 0;
        }
    }
    D_8003C90C[equipIndex] = weaponId;
    return 1;
}

void InitWeapon(s32 itemSlot) {
    // Called twice every time the in-game menu is closed.
    // It will be called twice, with LEFT_HAND_SLOT and then RIGHT_HAND_SLOT

    void (*loadWeaponPalette)(u8 clutIndex);
    s32 equipId;
    Entity* entity;
    u16 entityId;
    s32 i;

    equipId = g_Status.equipment[itemSlot];

    // Having the Axe Lord Armor equipped will not load any normal weapon
    if (g_Status.equipment[ARMOR_SLOT] == ITEM_AXE_LORD_ARMOR) {
        equipId = 0xD8;
    }

    // Do not re-load the same weapon
    if (equipId == g_PrevEquippedWeapons[itemSlot]) {
        return;
    }

    // Assign the right palette to the weapon graphics
    if (itemSlot == LEFT_HAND_SLOT) {
        loadWeaponPalette = D_8017A000.LoadWeaponPalette;
    } else {
        loadWeaponPalette = D_8017D000.LoadWeaponPalette;
    }
    loadWeaponPalette(g_EquipDefs[equipId].palette);

    // Destroy any entity spawned by the previously equipped weapon.
    // 0xE0-0xEF: weapon0 (left hand) entities
    // 0xF0-0xFF: weapon1 (right hand) entities
    entity = g_Entities;
    for (i = 0; i < STAGE_ENTITY_START; i++) {
        entityId = entity->entityId;
        if (entityId >= itemSlot * 0x10 + WEAPON_0_START &&
            entityId <= itemSlot * 0x10 + WEAPON_0_END) {
            DestroyEntity(entity);
        }
        if (entityId >= WEAPON_0_START + 8 && entityId < WEAPON_0_START + 14) {
            DestroyEntity(entity);
        }
        if (entityId >= WEAPON_1_START + 8 && entityId < WEAPON_1_START + 14) {
            DestroyEntity(entity);
        }
        entity++;
    }
}

void func_800FAB1C(void) {
    const int START = 4;
    Entity* entity;
    s32 i;

    for (entity = g_Entities + START, i = START; i < 64; i++) {
        if (entity->entityId >= 208 && entity->entityId < 224) {
            DestroyEntity(entity);
        }
        entity++;
    }
}

void func_800FAB8C(s32 menuIndex) {
    g_MenuData.menus[menuIndex].unk1C = 1;
    g_MenuData.menus[menuIndex].unk1D = 0;
}

void func_800FABBC(s32 menuIndex) {
    g_MenuData.menus[menuIndex].unk1C = 3;
    g_MenuData.menus[menuIndex].unk1D = 0;
}

void func_800FABEC(s32 menuIndex) { g_MenuData.menus[menuIndex].unk1C = 0; }

void func_800FAC0C(s32 menuIndex) { g_MenuData.menus[menuIndex].unk1C = 2; }

void func_800FAC30(void) {
    D_80137844[0] = 0;
    D_80137848[0] = 0;
}

void func_800FAC48(void) {
    ClearImage(&g_Vram.D_800ACD90, 0, 0, 0);
    ClearImage(&g_Vram.D_800ACDC8, 0, 0, 0);
}

void func_800FAC98(void) { func_800F9808(2); }

bool func_800FACB8(void) {
    if (g_pads[0].tapped & 2) {
        g_MenuNavigation.cursorEquip++;
        if (g_MenuNavigation.cursorEquip == 7) {
            g_MenuNavigation.cursorEquip = 0;
        }
        return true;
    }
    if (g_pads[0].tapped & 1) {
        g_MenuNavigation.cursorEquip--;
        if (g_MenuNavigation.cursorEquip == -1) {
            g_MenuNavigation.cursorEquip = 6;
        }
        return true;
    }
    return false;
}

void func_800FAD34(s32 arg0, u8 arg1, u16 equipIcon, u16 palette) {
    D_80137608 = 0;
    func_800F9808(2);

    if (arg1) {
        D_80137608 = 1;
#if defined(VERSION_US)
        func_800F99B8(arg0, 2, 0);
#elif defined(VERSION_HD)
        func_800F98AC(arg0, 2);
#endif
        LoadEquipIcon(equipIcon, palette, 0x1F);
    }
}

void func_800FADC0(void) {
    const char* description;
    s32 cursorEquip;
    u16 equipIcon;
    u16 palette;

    if (g_MenuNavigation.cursorEquip < 2) {
        cursorEquip = g_Status.equipment[g_MenuNavigation.cursorEquip];
        description = g_EquipDefs[cursorEquip].description;
        equipIcon = g_EquipDefs[cursorEquip].icon;
        palette = g_EquipDefs[cursorEquip].iconPalette;
    } else {
        cursorEquip = g_Status.equipment[g_MenuNavigation.cursorEquip];
        description = g_AccessoryDefs[cursorEquip].description;
        equipIcon = g_AccessoryDefs[cursorEquip].icon;
        palette = g_AccessoryDefs[cursorEquip].iconPalette;
    }
    func_800FAD34(description, 0x1, equipIcon, palette);
}

void func_800FAE98(void) {
    func_800FADC0();
    D_800978F8 = 0x40;
}

void func_800FAEC4(u16 pad, u16 arg1, s32 arg2, s16 arg3, u16 arg4) {
    g_IsSelectingEquipment = 0;
    func_800FAC98();
    func_800FAD34(arg2, arg1, arg3, arg4);
    D_800978F8++;
}

void func_800FAF44(s32 arg0) {
    s32 var_a0;
    s32 i;
    s32 j;
    s32* var_a1;

    D_801375D8 = g_Pix[3];
    var_a1 = g_Pix[3];

    if (arg0 == 0) {
        for (i = 0; i < 169; i++) {
            *var_a1 = i;
            var_a1++;
        }

        g_MenuData.D_80137688 = g_MenuData.D_8013768C =
            g_MenuNavigation.scrollEquipHand;
        return;
    }
    g_MenuData.D_80137688 = g_MenuData.D_8013768C =
        ((s32*)g_MenuNavigation.scrollEquipAccessories)[D_801375D4];

    for (i = 0; i < 90; i++) {
        if (g_AccessoryDefs[i].equipType == D_801375D4) {
            *var_a1 = i;
            var_a1++;
        }
    }
}

void func_800FB004(void) {
    s32 temp_a1 = func_800FD6C4(D_801375CC.equipTypeFilter);
    s32 temp_v0;

    if (((-g_MenuData.D_80137688) / 12) != 0) {
        if (*D_80137844 == 0) {
            *D_80137844 = 1;
        }
    } else {
        *D_80137844 = 0;
    }

    temp_v0 = -g_MenuData.D_80137688 + g_MenuData.D_80137678[2];

    if ((temp_v0 / 12) < (temp_a1 / 2)) {
        if (D_80137848[0] == 0) {
            D_80137848[0] = 1;
        }
    } else {
        D_80137848[0] = 0;
    }
}

void func_800FB0FC(void) {
    Unkstruct_800A2D98* temp = &D_800A2D98[g_MenuNavigation.cursorEquip];
    s32 temp_a1 = temp->unk4;
    s32 new_var2 = temp->unk8;

    D_801375CC.equipTypeFilter = temp->equipTypeFilter;
    D_801375CC.unk8 = temp_a1;
    func_800FAF44(new_var2);
    func_800FB004();
}

void func_800FB160(s32 arg0, s32 arg1, s32 equipType) {
    u8 swap;
    u8* equipOrder;

    equipOrder = GetEquipOrder(equipType);
    swap = equipOrder[D_801375D8[arg0]];
    equipOrder[D_801375D8[arg0]] = equipOrder[D_801375D8[arg1]];
    equipOrder[D_801375D8[arg1]] = swap;
}

bool func_800FB1EC(s32 arg0) {
    if (D_801375CC.equipTypeFilter == 0) {
        if (arg0 == 0) {
            return true;
        }
    } else if (
        (arg0 == 0x1A) || (arg0 == 0) || (arg0 == 0x30) || (arg0 == 0x39)) {
        return true;
    }

    return false;
}

INCLUDE_ASM("dra/nonmatchings/5298C", func_800FB23C);

void func_800FB9BC(void) {
    const int ItemsPerRow = 2;
#if defined(VERSION_US)
    const int VertScrollWindow = 120;
    const int YScrollPerElement = 14;
#elif defined(VERSION_HD)
    const int VertScrollWindow = 140;
    const int YScrollPerElement = 15;
#endif

    s32 i;
    MenuContext* context;

    context = &g_MenuData.menus[0];
    for (i = 0; i < 16; i++, context++) {
        context->cursorX = context->unk1.x = MenuContextData[i].cursorX;
        context->cursorY = context->unk1.y = MenuContextData[i].cursorY;
        context->cursorW = context->unk1.w = MenuContextData[i].cursorW;
        context->cursorH = context->unk1.h = MenuContextData[i].cursorH;
        context->unk14 = 0;
        context->w = 0;
        context->unk16 = 0;
        context->h = 0;
        context->otIdx = MenuContextData[i].otIdx;
        context->unk1C = 2;
    }
    D_801376C4 = D_801376C8 =
        -((g_MenuNavigation.cursorRelic / ItemsPerRow) * VertScrollWindow) /
        YScrollPerElement;
}

INCLUDE_ASM("dra/nonmatchings/5298C", func_800FBAC4);

INCLUDE_ASM("dra/nonmatchings/5298C", func_800FBC24);

#if defined(VERSION_US)
void func_800FD39C(s32 x, s32 y, s32 w, s32 h, s32 u, s32 v, s32 pal, s32 _,
                   s32 blend, s32 color) {
    GpuBuffer* gpuBuffer;
    SPRT* sprt;

    sprt = &g_CurrentBuffer->sprite[g_GpuUsage.sp];
    gpuBuffer = g_CurrentBuffer;
    SetSemiTrans(sprt, 0);
    SetShadeTex(sprt, blend);
    sprt->x0 = x;
    sprt->y0 = y;
    sprt->w = w;
    sprt->h = h;
    sprt->u0 = u;
    sprt->v0 = v;
    sprt->b0 = sprt->g0 = sprt->r0 = color;
    sprt->clut = D_8003C104[pal];
    AddPrim(&gpuBuffer->ot[0x1FF], sprt);
    g_GpuUsage.sp++;
}
#endif

s32 TimeAttackController(TimeAttackEvents eventId, TimeAttackActions action) {
    s32 temp_v0;
    s32 temp_v1;
    s32 seconds;
    s32 timer;

    switch (action) {
    case TIMEATTACK_GET_RECORD:
        // get the time attack for a specific defeated boss. this is
        // also responsible to check if the player should teleport into
        // a boss room
        return g_Settings.timeAttackRecords[eventId];

    case TIMEATTACK_SET_RECORD:
        // set new time attack record if the boss was not previously
        // defeated
        timer = g_Settings.timeAttackRecords[eventId];
        if (timer = timer != 0) {
            return g_Settings.timeAttackRecords[eventId];
        }

        seconds = g_Status.timerSeconds;
        g_Settings.timeAttackRecords[eventId] = seconds;
        temp_v1 = (g_Status.timerMinutes * 100) + seconds;
        g_Settings.timeAttackRecords[eventId] = temp_v1;
        temp_v0 = (g_Status.timerHours * 10000) + temp_v1;
        g_Settings.timeAttackRecords[eventId] = temp_v0;
        return temp_v0;

    case TIMEATTACK_SET_VISITED:
        // not exactly sure yet why this flag is needed
        g_Settings.D_8003CB00 |= 1 << eventId;
    }
}

bool func_800FD5BC(Unkstruct_800FD5BC* arg0) {
    s32 temp;

    if (arg0->unk4 != 5) {
        if (((u32)arg0->unk4) >= 0x10U) {
            temp = g_Status.hpMax;
            if (g_Status.hpMax < 0) {
                temp += 7;
            }
            arg0->unk8 = temp >> 3;
        } else if (g_Status.hpMax >= (arg0->unk8 * 0x14)) {
            arg0->unk4 = 3;
        } else {
            arg0->unk4 = 2;
        }
    }
    if (g_Status.hp <= arg0->unk8) {
        g_Status.hp = 0;
        return true;
    } else {
        g_Status.hp -= arg0->unk8;
        return false;
    }
}

s32 func_800FD664(s32 arg0) {
    return g_StageId & STAGE_INVERTEDCASTLE_FLAG ? arg0 << 1 : arg0;
}

ItemCategory GetEquipItemCategory(s32 equipId) {
    return g_EquipDefs[g_Status.equipment[equipId]].itemCategory;
}
