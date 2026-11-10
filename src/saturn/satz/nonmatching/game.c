// SPDX-License-Identifier: AGPL-3.0-or-later
#include <stdint.h>
#include "../../zero.h"
#include "../../game.h"
#include "../../zero/overlay.h"

extern u8 g_RandomHighBitVariants[];
extern s32 D_801375B4;
extern s32 D_801375B8;

void func_0606D554(s32);
void DestroyEntitiesFrom(s32);
void func_0600C1A0(void);
void func_0606D3FC(void);
void StatusDispInit(void);
s32 func_800F0CD8(u16);
void InitServant(s32 mode);
void func_06074BF4(void);
void PlaySfx(s32 sfxId);

extern s32 DAT_0608550C;
extern s16 g_AlternateStatusHudSpriteOffsets[];
extern u16 g_AlternateStatusHudPrimitiveLayout[16];
s32 func_06012F7C(void);
s32 func_0607284C(void);

s32 GetEnemyPlayerCharaAddr(void);
void func_060097B4(Unk0605CD90* arg0, s32 arg1);
void SCL_DisplayFrame(void);

extern s32 g_GameDataEnd;

#define _SPR2_
#include "../../lib/spr/spr.h"

extern s32 (*DAT_0606467C)();

void func_06071C3C(void);

static u16 LookupTblNoToVram_b2(u16 arg0);

void func_0606C774(u16 layoutId) {
    SaturnLayerCompressedSizes* sizes = &DAT_060645F4[layoutId];
    SaturnLayerMapOffsets* offsets = &DAT_06064654[layoutId];
    SaturnRoomLayerSetup* setup = &DAT_0606466C[layoutId];
    Unk0605CD90* layer = DAT_0605CD90;
    s32 extra = 0;
    s32 i, k, size;
    u16* map;
    u8* base;

    Scl_s_reg.dispenbl = 0;
    SclProcess = 1;
    if (g_CurrentRoom.stageID == 0x1A || g_CurrentRoom.stageID == 0x18 ||
        g_CurrentRoom.stageID == 0x39) {
        extra = GetEnemyPlayerCharaAddr();
    }
    base = (u8*)&DAT_00252000 + extra;
    for (i = 0; i < 3; i++, layer++) {
        layer->unk18 = sizes->layers[i].characterGraphics;
        layer->unk1C = sizes->layers[i].palettes;
        layer->unk20 = sizes->layers[i].tilemap;
        layer->unkC = base + offsets->layers[i].characterGraphics;
        layer->unk10 = base + offsets->layers[i].palettes;
        layer->unk14 = base + offsets->layers[i].tilemap;
        layer->divisorX = setup->layers[i].scrollDivisorX;
        layer->divisorY = setup->layers[i].scrollDivisorY;
        layer->flags = setup->layers[i].wrapFlags;
        func_060097B4(layer, i);
        if (layer->unk18 != 0) {
            Scl_s_reg.dispenbl |= 2 << i;
            SclProcess = 1;
            DAT_0605D6C0[i].tileFlags = 7;
            map = (u16*)DAT_0605D7DC;
            DAT_0605C120[i] = (s16*)map;
            size = DecompressLZSS((u8*)layer->unk14, (u8*)map, layer->unk20);
            for (k = 0; k < size / 2; k++) {
                map[k] = (u16)((map[k] >> 8) | (map[k] << 8));
            }
            DAT_0605D7DC += size;
            if ((uptr)DAT_0605D7DC & 1) {
                DAT_0605D7DC++;
            }
            layer->width = map[0];
            layer->height = map[1];
        } else {
            Scl_s_reg.dispenbl &= ~(2 << i);
            SclProcess = 1;
        }
    }
    SCL_DisplayFrame();
    DAT_0605c680.unk24 = 0;
    DAT_0605c680.unk28 =
        (s32)((double)(DAT_0605CD90[0].width * 8 - 320) * 65536.0);
    DAT_0605c680.unk2C = 0x000A0000;
    DAT_0605c680.unk30 =
        (s32)((double)(DAT_0605CD90[0].height * 8 - 256) * 65536.0);
    size = DAT_060645C8[layoutId].dataSize;
    DecompressLZSS(
        base + DAT_060645C8[layoutId].dataOffset, DAT_0608FFF8, size);
}

void func_06071C3C(void) {
    RoomLoadDef* def;
    Primitive* prim;
    s32 x, y, primIndex;

    ClearDebugPrintTilemap();
    func_0606D554(0);
    SetCanRevealMap();
    DAT_0605C668 = 1;
    DAT_0605ceb0 = 0;
    if (D_8003C730 == 0) {
        def = D_801375BC.def - 1;
        g_Tilemap.left = def->tileLayoutId;
        g_Tilemap.top = def->tilesetId;
        g_Tilemap.right = def->objGfxId;
        g_Tilemap.bottom = def->objLayoutId;
        g_Tilemap.hSize = g_Tilemap.right - g_Tilemap.left + 1;
        g_Tilemap.vSize = g_Tilemap.bottom - g_Tilemap.top + 1;
        g_Tilemap.x = (def->tileLayoutId - g_Tilemap.left) * 0x140;
        g_Tilemap.y = (def->tilesetId - g_Tilemap.top) << 8;
        g_Tilemap.width = (def->objGfxId - g_Tilemap.left + 1) * 0x140;
        g_Tilemap.height = (def->objLayoutId - g_Tilemap.top + 1) << 8;
        D_8003C708.flags = 0;
    }
    func_800F2404(0);
    DestroyEntitiesFrom(0);
    func_0600B254();
    InitPrimBuf();
    func_0600C1A0();
    SetLocalPalData();
    if (DAT_0605cd70.unk4 == 1 || DAT_0605cd70.unk4 == 4) {
        if (g_CurrentRoom.stageID == 0x41 && g_CurrentRoom.unk6 == 0x12) {
            g_CurrentRoom.unkC = 2;
            g_CurrentRoom.unk10 = 40;
        }
        if (g_Tilemap.scrollY.i.hi != 0) {
            g_Tilemap.scrollY.i.hi += 4;
        }
    } else {
        if (g_PlayableCharacter == 1 && g_CurrentRoom.stageID == 0x1F) {
            ((void (*)(s32))DAT_06064610)(g_PlayableCharacter);
        } else {
            ((void (*)(s32))DAT_06064610)(0);
        }
        func_0606D3FC();
        x = PLAYER.posX.i.hi;
        y = PLAYER.posY.i.hi;
        g_PlayerX = x;
        g_PlayerY = y;
        g_CurrentRoom.unkC = g_Tilemap.left + x / 0x140;
        g_CurrentRoom.unk10 = g_Tilemap.top + y / 0x100;
    }
    StatusDispInit();
    g_Tilemap.scrollX.i.hi = (g_CurrentRoom.unkC - g_Tilemap.left) * 0x140;
    g_Tilemap.scrollY.i.hi = (g_CurrentRoom.unk10 - g_Tilemap.top) << 8;
    PLAYER.posX.i.hi = PLAYER.posX.i.hi % 0x140;
    PLAYER.posY.i.hi = PLAYER.posY.i.hi % 0x100;
    func_800F0CD8(0);
    func_800F0CD8(0);
    DAT_0605c680.unk4 = DAT_0605c680.unk8 = g_Tilemap.scrollX.i.hi << 16;
    DAT_0605c680.unkC = DAT_0605c680.unk10 = g_Tilemap.scrollY.i.hi << 16;
    DAT_0605c680.g_ScrollDeltaX = 0;
    DAT_0605c680.g_ScrollDeltaY = 0;
    DAT_0605c680.unk3C = DAT_0605c680.unk34 = g_Tilemap.scrollX.i.hi << 16;
    DAT_0605c680.unk40 = DAT_0605c680.unk38 = g_Tilemap.scrollY.i.hi << 16;
    SetDefaultSCLPriority(0);
    func_06009510(g_CurrentRoom.unk4);
    if (g_CurrentRoom.stageID == 0x38) {
        DAT_0605CD90[0].width = 40;
        DAT_0605CD90[0].height = 32;
    }
    D_801375B4 = 0;
    D_801375B8 = 0;
    func_06064604();
    g_PlayerX = g_Tilemap.scrollX.i.hi + PLAYER.posX.i.hi;
    g_PlayerY = g_Tilemap.scrollY.i.hi + PLAYER.posY.i.hi;
    PLAYER.facingLeft = PLAYER.posX.i.hi > 0x9F;
    if ((u32)(D_80097C98 - 6) <= 1) {
        PLAYER.facingLeft = 1;
    } else if (D_80097C98 == 5) {
        PLAYER.facingLeft = 0;
    }
    func_800F0CD8(0);
    func_800F0CD8(0);
    InitServant(0);
    if (g_CastleFlags[0x13] & 0x80) {
        g_CastleFlags[0x13] = g_RandomHighBitVariants[rand() & 0xF] + 0x80;
    }
    g_CurrentRoom.unkA = g_CurrentRoom.unk8;
    InitRoomEntities(g_CurrentRoom.unk4);
    Update();
    Update();
    primIndex = AllocPrimitives(0, 16);
    g_unkGraphicsStruct.primIndex = primIndex;
    if (primIndex != -1) {
        for (prim = &g_PrimBuf[primIndex]; prim != NULL; prim = prim->next) {
            prim->drawMode = DRAW_HIDE;
        }
    }
    func_06074BF4();
    g_CurrentRoom.unk2 = g_CurrentRoom.stageID;
    func_06009F10();
    currentMusicId = func_060727DC(
        g_PlayableCharacter, g_CurrentRoom.stageID, g_CurrentRoom.unk4);
    stopMusicFlag = 0;
    if (g_CurrentRoom.stageID == 0x41 && D_8003C730 == 0) {
        currentMusicId = 0xE000011B;
    }
    if (D_8003C730 == 0 && !(D_8003C708.flags & FLAG_UNK_20)) {
        PlaySfx(currentMusicId);
    } else {
        stopMusicFlag = 1;
    }
}

s32 func_0607284C(void) {
    switch ((u32)DAT_0608550C) {
    case 0:
    case 1:
        break;
    case 2:
        if (CdSoundCommandQueueEmpty() == 0) {
            return 1;
        }
        break;
    case 3:
        if (func_06012F7C() == 0) {
            return 1;
        }
        DAT_0608550C = 0;
        return 0;
    default:
        DAT_0608550C = 0;
        return 0;
    }
    DAT_0608550C++;
    return 1;
}

static u16 LookupTblNoToVram_b2(u16 arg0) {
    if (arg0 & 0x4000) {
        return LocalLookupTblNoToVram(arg0 & 0xFFF);
    }
    return SPR_2LookupTblNoToVram(arg0 & 0xFFF);
}

void func_0607672C(void) {
    Primitive* prim;
    s16* ofs;
    s16* t;
    s32 i;

    D_801397FC = 0;
    D_80139008 = 0;
    g_PlayerHud.unk28 = 0;
    D_8003C744 = 0;
    g_PlayerHud.unk0C = 0x190;
    g_PlayerHud.unk10 = 0x190;
    g_PlayerHud.unk14 = 0x40;
    g_PlayerHud.unk18 = 0;
    g_PlayerHud.unk20 = 0x64;
    g_PlayerHud.unk1C = 0x64;
    g_PlayerHud.unk24 = 0;
    g_PlayerHud.primIndex1 = AllocPrimitives(0, 8);
    ofs = g_AlternateStatusHudSpriteOffsets;
    for (prim = &g_PrimBuf[g_PlayerHud.primIndex1]; prim != NULL;
         prim = prim->next) {
        u16* ptr = DAT_0605AEC0[(u16)DAT_06086388->allocationIndex + *ofs++];
        prim->unk8 = ptr[0];
        prim->unkA = ptr[1];
        prim->unk6 =
            (LookupTblNoToVram_b2(DAT_06086388->flags + *ofs++) & 0x8FFF) |
            0x4000;
    }

    t = (s16*)g_AlternateStatusHudPrimitiveLayout;
    prim = &g_PrimBuf[g_PlayerHud.primIndex1];
    prim->x0 = t[0];
    prim->y0 = t[1];
    t += 2;
    prim->priority = 0x1BF;
    prim->drawMode = 0x2000;
    prim = prim->next;

    prim->type = 0x1001;
    prim->unk4 = 0x1480;
    prim->x0 = t[0];
    prim->y0 = t[1];
    t += 2;
    prim->y2 = prim->y0 - 0x20;
    prim->x2 = prim->x0 + 8;
    prim->priority = 0x1C0;
    prim->drawMode = 0x2000;
    prim = prim->next;

    prim->type = 0x1004;
    prim->unk4 = 0x04C0;
    prim->x0 = t[0];
    prim->y0 = t[1];
    t += 2;
    prim->y2 = prim->y0 - 0x20;
    prim->x1 = prim->x2 = prim->x0 + 4;
    prim->y1 = prim->y0;
    prim->x3 = prim->x0;
    prim->y3 = prim->y2;
    prim->priority = 0x1BE;
    prim->drawMode = 0x2000;

    for (i = 0; i < 4; i++) {
        prim = prim->next;
        prim->x0 = t[0];
        prim->y0 = t[1];
        t += 2;
        prim->priority = 0x1C0;
        prim->drawMode = 0x2000;
    }

    prim = prim->next;
    prim->x0 = t[0];
    prim->y0 = t[1];
    prim->priority = 0x1BF;
    prim->drawMode = 0x2000;

    for (prim = &g_PrimBuf[g_PlayerHud.primIndex1]; prim != NULL;
         prim = prim->next) {
        prim->unk4 &= 0xFFC7;
    }
}

Uint32 MTH_GetRand(void) {
    g_GameDataEnd = g_GameDataEnd * 5 + 0x3573;
    return g_GameDataEnd;
}
