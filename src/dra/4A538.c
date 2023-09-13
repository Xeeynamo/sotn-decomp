#include "dra.h"

void func_800EA538(s32 arg0) {
    Unkstruct_8006C3C4* var_v0;
    s32 temp;
    s32 v1;
    s32 i;

    // !FAKE: 0x8000 inside a temp is weird
    temp = 0x8000;
    v1 = (temp >> (arg0 - 1));

    if (arg0 != 0) {
        for (i = 0; i < 32; i++) {
            if (v1 & D_8006C3C4[i].unk8) {
                D_8006C3C4[i].unk8 = 0;
            }
        }
        return;
    }

    D_8003C0F8 = 0;
    var_v0 = &D_8006C3C4;

    for (i = 0; i < 32; i++) {
        var_v0->unk8 = 0;
        var_v0++;
    }
}

void func_800EA5AC(u16 arg0, u8 arg1, u8 arg2, u8 arg3) {
    D_8003C0EC[3] = arg0;
    D_8003C0EC[0] = arg1;
    D_8003C0EC[1] = arg2;
    D_8003C0EC[2] = arg3;
}

s32 func_800EA5E4(u32 arg0) {
    u16 temp_v0;
    s32 i;
    s32 j;
    u32 ones_start;
    u32 ones_end;
    UnkStructClut* clut;
    Unkstruct_8006C3C4* unkStruct;

    temp_v0 = arg0 & 0xFF00;
    arg0 = arg0 & 0xFF;

    if (temp_v0 & 0x8000) {
        clut = g_api.o.cluts[arg0];
    } else {
        clut = D_800A3BB8[arg0];
    }

    if (clut->unk0 == 0) {
        return 1;
    }
    if (clut->unk0 == -1) {
        return 1;
    }
    unkStruct = &D_8006C3C4;
    for (j = 0; j < LEN(D_8006C3C4); unkStruct++) {
        j++;
        if (unkStruct->unk8 != 0) {
            continue;
        }
        unkStruct->struct1 = clut;
        unkStruct->struct2 = &clut->unkC;
        unkStruct->unk8 = (temp_v0 | clut->unk0);
        unkStruct->unkA = 0;
        unkStruct->unkC = 0;

        // Set unkStruct's array to all zeros, except within this range
        ones_start = clut->unk4;
        ones_end = (clut->unk4 + clut->unk8) - 1;
        ones_start >>= 8;
        ones_end >>= 8;
        for (i = 0; i < LEN(unkStruct->unkArray); i++) {
            unkStruct->unkArray[i] = 0;
        }
        for (i = ones_start; ones_end >= i; i++) {
            unkStruct->unkArray[i] = 1;
        }

        if ((u8)unkStruct->unk8 == 2 || (u8)unkStruct->unk8 == 16) {
            unkStruct->unkE = 0x1F;
        }
        return 0;
    }
    return -1;
}

INCLUDE_ASM("dra/nonmatchings/4A538", func_800EA720);

INCLUDE_ASM("dra/nonmatchings/4A538", func_800EA7CC);

s32 func_800EAD0C(void) { // the return type is needed for matching
    func_800EA5E4(4);
    func_800EA5E4(5);
    func_800EA5E4(6);
    func_800EA5E4(7);
    func_800EA5E4(8);

    if (g_CurrentPlayableCharacter == PLAYER_ALUCARD &&
        g_StageId != STAGE_ST0) {
        func_800EA5E4(0x17);
    }
}

void func_800EAD7C(void) {
    s32 index = 0;
    s32 i;
    s32 j;

    for (i = 0xF0; i < 0x100; i++) {
        for (j = 0x200; j < 0x300; j += 0x10) {
            D_8003C104[index++] = GetClut(j, i);
        }
    }

    for (i = 0xF0; i < 0x100; i++) {
        for (j = 0; j < 0x100; j += 0x10) {
            D_8003C104[index++] = GetClut(j, i);
        }
    }

    for (i = 0xF0; i < 0x100; i++) {
        for (j = 0x100; j < 0x200; j += 0x10) {
            D_8003C104[index++] = GetClut(j, i);
        }
    }
}

void func_800EAEA4(void) {
    u16* ptr;
    s32 i;

    for (ptr = D_801374F8, i = 0; i < 32; i++) {
        *ptr++ = ~0;
    }

    for (ptr = D_80137538, i = 0; i < 32; i++) {
        *ptr++ = ~0;
    }
}

void func_800EAEEC(void) {
    unkstruct_80072FA0* ptr = D_80072FA0;
    s32 i;

    for (i = 0; i < 16; i++, ptr++) {
        ptr->unk4 = 0;
    }

    func_800EAEA4();
}

void func_800EAF28(s32 arg0) {
    s32 temp_v1;
    s32 i;
    s32 new_var;
    Unsktruct_800EAF28* var_a1;
    unkstruct_80072FA0* var_a0;

    if (arg0 & ANIMSET_OVL_FLAG) {
        var_a1 = g_api.o.entityGfxs[arg0 & 0x7FFF];
    } else {
        var_a1 = D_800A3B5C[arg0];
    }

    temp_v1 = *(s32*)var_a1;
    if (temp_v1 != 0 && temp_v1 != (new_var = -1)) {
        for (i = 0; i < 0x10; i++) {
            var_a0 = &D_80072FA0[i];
            if (var_a0->unk4 == 0) {
                var_a0->unk4 = var_a1->unk0;
                var_a0->unk6 = 0;
                var_a0->unk8 = 0;
                var_a0->unk0 = var_a1 + 1;
                break;
            }
        }
    }
}

void DecompressWriteNibble(s32 ch) {
    u8 temp = ch;

    if (g_DecWriteNibbleFlag == 0) {
        g_DecWriteNibbleFlag = 1;
        *g_DecDstPtr = temp;
    } else {
        g_DecWriteNibbleFlag = 0;
        *g_DecDstPtr += ch * 16;
        g_DecDstPtr++;
    }
}

u32 DecompressReadNibble(void) {
    u8 ret;

    if (g_DecReadNibbleFlag != 0) {
        g_DecReadNibbleFlag = 0;
        ret = *g_DecSrcPtr;
        g_DecSrcPtr++;
        return (ret >> 0) & 0xF;
    } else {
        g_DecReadNibbleFlag = 1;
        ret = *g_DecSrcPtr;
        return (ret >> 4) & 0xF;
    }
}

// reg swap + fake stuff
#ifndef NON_MATCHING
INCLUDE_ASM("dra/nonmatchings/4A538", DecompressData);
#else
s32 DecompressData(u8* dst, u8* src) {
    u32 buf[8];
    s32 temp_s0;
    s32 ch;
    s32 temp_s1_3;
    s32 temp_s2;
    s32 temp_s2_2;
    s32 temp_s2_3;
    s32 temp_s2_4;
    s32 count;
    s32 i;
    s32 var_v1;
    s32* var_a0;
    u8* new_var;
    u8* srcptr;
    s32 op;
    srcptr = src;
    var_a0 = &buf;

    for (var_v1 = 0; var_v1 < 8; var_v1++) {
        *var_a0++ = *srcptr++;
    }

    g_DecReadNibbleFlag = 0;
    g_DecWriteNibbleFlag = 0;
    g_DecSrcPtr = srcptr;
    g_DecDstPtr = dst;
    while (count = true /*fake??*/) {
        op = DecompressReadNibble();
        switch (op) {
        case 0:
            do {
                temp_s2 = DecompressReadNibble();
                temp_s2_2 = DecompressReadNibble();
            } while (0);
            temp_s2_4 = temp_s2;
            temp_s2_3 = temp_s2_2;
            temp_s2_3 = temp_s2_4 * 0x10 + temp_s2_3 + 0x13;
            for (i = 0; i < temp_s2_3; i++) {
                DecompressWriteNibble(0);
            }
            break;
        case 2:
            temp_s0 = DecompressReadNibble();
            DecompressWriteNibble(temp_s0);
            DecompressWriteNibble(temp_s0);
            break;
        case 4:
            DecompressWriteNibble(DecompressReadNibble());
        case 3:
            DecompressWriteNibble(DecompressReadNibble());
        case 1:
            DecompressWriteNibble(DecompressReadNibble());
            break;
        case 5:
            temp_s1_3 = (ch = DecompressReadNibble());
            count = (op = DecompressReadNibble()) + 3;
            for (i = 0; i < count; i++) {
                temp_s2 = ch;
                DecompressWriteNibble(temp_s2 & 0xFF);
            }
            break;
        case 6:
            temp_s2 = DecompressReadNibble();
            count = temp_s2 + 3;
            for (i = 0; i < count; i++) {
                DecompressWriteNibble(0);
            }
            break;
        case 7:
        case 8:
        case 9:
        case 10:
        case 11:
        case 12:
        case 13:
        case 14:
            temp_s1_3 = (buf + op)[-7];
            switch (temp_s1_3 & 0xF0) {
            case 0x20:
                DecompressWriteNibble(temp_s1_3 & 0xF);
            case 0x10:
                DecompressWriteNibble(temp_s1_3 & 0xF);
                break;
            case 0x60:
                count = (temp_s1_3 & 0xF) + 3;
                for (i = 0; i < count; i++) {
                    DecompressWriteNibble(0);
                }
                break;
            }
            break;
        case 15:
            if ((dst + 0x2000) >= ((u32)g_DecDstPtr)) {
                return 0;
            }
            new_var = dst;
            return (g_DecDstPtr - new_var) + 0x2000;
        }
    }
}
#endif

INCLUDE_ASM("dra/nonmatchings/4A538", func_800EB314);

void func_800EB4F8(PixPattern* pix, s32 bitDepth, s32 x, s32 y) {
    LoadTPage(pix + 1, bitDepth, 0, x, y, (int)pix->w, (int)pix->h);
}

void LoadEquipIcon(s32 equipIcon, s32 palette, s32 index) {
    u8* iconGfx;
    s32 vramX;
    s32 var_t0;
    s32 i;

    if (D_801374F8[index] != equipIcon) {
        iconGfx = g_GfxEquipIcon[equipIcon];
        vramX = ((index & 7) * 4) + 0x280;
        var_t0 = index;
        if (index < 0) {
            var_t0 = index + 7;
        }

        LoadTPage(iconGfx, 0, 0, vramX, (var_t0 >> 3) * 0x10 + 0x180, 16, 16);
    }

    if (D_80137538[index] != palette) {
        for (i = 0; i < 16; i++) {
            if (D_800705CC) { // FAKE
            }
            D_800705CC[index * 0x10 + i] = g_PalEquipIcon[palette * 0x10 + i];
        }

        LoadClut2(D_800705CC, 0, 0xFD);
        LoadClut2(D_800705CC + 0x100, 0, 0xFE);
    }
    if (D_800973EC == 0) {
        D_80137478[index] = equipIcon;
        D_801374B8[index] = palette;
    }
    D_801374F8[index] = equipIcon;
    D_80137538[index] = palette;
}

void func_800EB6B4(void) {
    s32 i;

    for (i = 0; i < 32; i++) {
        LoadEquipIcon(D_80137478[i], D_801374B8[i], i);
    }
}

bool func_800EB720(void) {
    unkstruct_80072FA0* temp = D_80072FA0;
    s32 i;

    for (i = 0; i < 16; i++) {
        if (temp[i].unk4 != 0) {
            return true;
        }
    }

    return false;
}

INCLUDE_ASM("dra/nonmatchings/4A538", func_800EB758);

void ResetEntityArray(void) {
    Entity* entity;
    u8* ch;
    s32 i;
    u32 j;

    entity = &g_Entities[0];
    for (i = 0; i < ARRAY_COUNT(g_Entities); i++) {
        ch = (s8*)entity;
        for (j = 0; j < sizeof(Entity); j++) {
            *ch++ = 0;
        }
        entity++;
    }
}

INCLUDE_ASM("dra/nonmatchings/4A538", RenderEntities);

// The loop at the end is weird, the rest is matching
#ifndef NON_MATCHING
INCLUDE_ASM("dra/nonmatchings/4A538", func_800ECBF8);
#else
typedef struct {
    s16 unk0, unk2;
} Unkstruct_800ECBF8_2; /* size = 0x4 */

extern POLY_GT4 D_8004077C[0x300]; // TODO D_8003CB08.polyGT4
extern POLY_G4 D_8004A37C[0x100];  // TODO D_8003CB08.polyG4
extern POLY_GT3 D_8004C77C[0x30];  // TODO D_8003CB08.polyGT3
extern LINE_G2 D_8004CEFC[0x100];  // TODO D_8003CB08.lineG2
extern SPRT_16 D_8004E2FC[0x280];  // TODO D_8003CB08.sprite16
extern TILE D_80050AFC[0x100];     // TODO D_8003CB08.tiles
extern SPRT D_80051AFC[0x200];     // TODO D_8003CB08.sprite
extern POLY_GT4 D_80057F70[0x300]; // TODO D_800542FC.polyGT4
extern POLY_G4 D_80061B70[0x100];  // TODO D_80542FC8.polyG4
extern POLY_GT3 D_80063F70[0x30];  // TODO D_800542FC.polyGT3
extern LINE_G2 D_800646F0[0x100];  // TODO D_80542FC8.lineG2
extern SPRT_16 D_80065AF0[0x280];  // TODO D_8003542FCsprite16
extern TILE D_800682F0[0x100];     // TODO D_8542FC08.tiles
extern SPRT D_800692F0[0x200];     // TODO D_80542FC8.sprite
extern Unkstruct_800ECBF8_1 D_80097D1C[0x10];
extern Unkstruct_800ECBF8_2 D_800A21B8[0x10];

void func_800ECBF8(void) {
    int i;
    POLY_GT4 *a1, *a2;
    SPRT_16 *b1, *b2;
    TILE *c1, *c2;
    LINE_G2 *d1, *d2;
    POLY_G4 *e1, *e2;
    SPRT *f1, *f2;
    POLY_GT3 *g1, *g2;

    s16* new_var4;
    int new_var5;
    int new_var2;
    Unkstruct_800ECBF8_1* var_v1;
    s16* new_var;
    s16* var_a2;
    s16* var_a0;

    a1 = g_GpuBuffers[0].polyGT4;
    a2 = g_GpuBuffers[1].polyGT4;
    for (i = 0; i < 0x300; i++, a1++, a2++) {
        SetPolyGT4(a1);
        SetPolyGT4(a2);
    }

    b1 = g_GpuBuffers[0].sprite16;
    b2 = g_GpuBuffers[1].sprite16;
    for (i = 0; i < 0x280; i++, b1++, b2++) {
        SetSprt16(b1);
        SetSprt16(b2);
    }

    c1 = g_GpuBuffers[0].tiles;
    c2 = g_GpuBuffers[1].tiles;
    for (i = 0; i < 0x100; i++, c1++, c2++) {
        SetTile(c1);
        SetTile(c2);
    }

    d1 = g_GpuBuffers[0].lineG2;
    d2 = g_GpuBuffers[1].lineG2;
    for (i = 0; i < 0x100; i++, d1++, d2++) {
        SetLineG2(d1);
        SetLineG2(d2);
    }

    e1 = g_GpuBuffers[0].polyG4;
    e2 = g_GpuBuffers[1].polyG4;
    for (i = 0; i < 0x100; i++, e1++, e2++) {
        SetPolyG4(e1);
        SetPolyG4(e2);
    }

    f1 = g_GpuBuffers[0].sprite;
    f2 = g_GpuBuffers[1].sprite;
    for (i = 0; i < 0x200; i++, f1++, f2++) {
        SetSprt(f1);
        SetSprt(f2);
    }

    g1 = g_GpuBuffers[0].polyGT3;
    g2 = g_GpuBuffers[1].polyGT3;
    for (i = 0; i < 0x30; i++, g1++, g2++) {
        SetPolyGT3(g1);
        SetPolyGT3(g2);
    }

    var_v1 = &D_80097D1C;
    i = 0;
    new_var5 = -2;
    new_var4 = &D_800A21B8->unk0;
    var_a0 = &D_800A21B8->unk0 + 1;
    var_a2 = new_var4;
    for (; i < 16;) {
        var_v1->unk00 = *var_a2;
        var_v1->unk02 = (*var_a0) & 0x1FF;
        var_v1->unk23 = ((*var_a0) >> 8) & new_var5;
        var_v1->unk1F = (var_v1->unk00 >> 6) - (-0x10);
        var_a2 += 2;
        i++;
        var_a0 += 2;
        var_v1++;
    }
}

#endif

void HideAllBackgroundLayers(void) {
    s32 i;

    g_CurrentRoom.unk00 = 0;
    for (i = 0; i < MAX_BG_LAYER_COUNT; i++) {
        g_CurrentRoom.bg[i].D_800730F4 = 0;
    }
}

INCLUDE_ASM("dra/nonmatchings/4A538", RenderTilemap);

void SetRoomForegroundLayer(LayerDef2* layerDef) {
    D_8003C708.flags = 0;
    D_8013AED0 = 1;
    D_80073088 = layerDef->tileDef;
    if (g_CurrentRoom.hSize && g_CurrentRoom.vSize) {
    }
    g_CurrentRoom.unk00 = 0;
    if (D_80073088 == 0) {
        return;
    }

    g_CurrentRoomTileLayout.fg = layerDef->layout;
    D_8007309C = layerDef->zPriority;
    if (layerDef->rect.flags & 0x40) {
        D_8007309C = 0x60;
        D_8003C708.flags = layerDef->rect.flags;
        D_8003C708.unk2 = 0;
        D_8003C708.unk4 = 0;
        D_8003C708.zPriority = layerDef->zPriority;
    }
    if (layerDef->rect.flags & 0x20) {
        D_8007309C = 0x60;
        D_8003C708.flags = layerDef->rect.flags;
    }
    if (layerDef->rect.flags & 0x10) {
        D_8007309C = 0x60;
        D_8013AED0 = 0;
    };
    g_CurrentRoom.unk00 = layerDef->unkE;
    g_CurrentRoom.left = layerDef->rect.left;
    g_CurrentRoom.top = layerDef->rect.top;
    g_CurrentRoom.right = layerDef->rect.right;
    g_CurrentRoom.bottom = layerDef->rect.bottom;
    g_CurrentRoom.hSize = g_CurrentRoom.right - g_CurrentRoom.left + 1;
    g_CurrentRoom.vSize = g_CurrentRoom.bottom - g_CurrentRoom.top + 1;
    g_CurrentRoom.y = 0;
    g_CurrentRoom.x = 0;
    g_CurrentRoom.width = g_CurrentRoom.hSize << 8;
    g_CurrentRoom.height = g_CurrentRoom.vSize << 8;
    g_CurrentRoom.unk8 = 1;
}

void SetRoomBackgroundLayer(s32 index, LayerDef2* layerDef) {
    g_CurrentRoom.bg[index].D_800730F4 = 0;
    g_CurrentRoom.bg[index].tileDef = layerDef->tileDef;
    g_CurrentRoom.bg[index].layout = layerDef->layout;
    if (g_CurrentRoom.bg[index].tileDef != 0) {
        g_CurrentRoom.bg[index].zPriority = layerDef->zPriority;
        g_CurrentRoom.bg[index].D_800730F4 = layerDef->unkE;
        g_CurrentRoom.bg[index].w =
            layerDef->rect.right - layerDef->rect.left + 1;
        g_CurrentRoom.bg[index].h =
            layerDef->rect.bottom - layerDef->rect.top + 1;
        g_CurrentRoom.bg[index].flags = layerDef->rect.flags;
        g_CurrentRoom.bg[index].D_80073100 = 1;
    }
}

void LoadRoomLayer(s32 layerIndex) {
    s32 i;

    SetRoomForegroundLayer(g_api.o.tileLayers[layerIndex].fg);
    SetRoomBackgroundLayer(0, g_api.o.tileLayers[layerIndex].bg);

    for (i = 1; i < MAX_BG_LAYER_COUNT; i++) {
        g_CurrentRoom.bg[i].D_800730F4 = 0;
    }
}

void DestroyPrimitive(Primitive* prim) {
    s32 i;
    s32 n;
    u32* primData = (u32*)prim;

    for (n = sizeof(Primitive) / sizeof(*primData), i = 0; i < n; i++) {
        *primData++ = 0;
    }
}

void DestroyAllPrimitives(void) {
    Primitive* prim;
    s32 i;

    for (i = 0, prim = g_PrimBuf; i < MAX_PRIM_COUNT; i++) {
        DestroyPrimitive(prim);
        prim->type = PRIM_NONE;
        prim++;
    }
}

void func_800EDAE4(void) {
    s32 i;
    DR_ENV* ptr = &D_800974AC;

    for (i = 0; i < 16; i++, ptr++) {
        ptr->tag = 0;
    }
}

DR_ENV* func_800EDB08(POLY_GT4* poly) {
    DR_ENV* ptr = &D_800974AC;
    s32 i = 0;

    for (; i < 0x10; i++, ptr++) {
        if (ptr->tag == 0) {
            ptr->tag = 1;
            setcode(poly, 7);
            *(u32*)&poly->r1 = (u32)ptr; // similar issue as FreePrimitives
            return ptr;
        }
    }

    return NULL;
}

s16 func_800EDB58(u8 primType, s32 count) {
    Primitive* prim;
    Primitive* temp_v0;
    bool isLooping;
    s32 primStartIdx;
    s32 var_s1;
    s32 i;
    s32 var_v1;

    var_v1 = count;
    primStartIdx = 0;
    i = 0;
    prim = g_PrimBuf;
    isLooping = 1;
    while (isLooping) {
        var_v1--;
        if (prim->type != 0) {
            var_v1 = i;
            primStartIdx = var_v1 + 1;
            var_v1 = count;
        } else if (var_v1 == 0) {
            break;
        }
        var_s1 = i + 1;
        prim++;
        i++;
        isLooping = i < 0x400;
        if (isLooping) {
            continue;
        }
        if (var_v1 != 0) {
            return -1;
        }
    }

    for (i = 0, prim = &g_PrimBuf[primStartIdx]; i < count; i++, prim++) {
        DestroyPrimitive(prim);
        var_s1 = 0;
        temp_v0 = &g_PrimBuf[i];
        prim->type = primType;
        prim->next = temp_v0;
        prim->next = prim->next + primStartIdx + 1;
    }
    prim[-1].next = NULL;
    prim[-1].type &= 0xEF;

    return primStartIdx;
}

s32 AllocPrimitives(u8 primType, s32 count) {
    s32 primIndex = 0;
    Primitive* prim = g_PrimBuf;
    u8* dstPrimType = &g_PrimBuf->type;
    s16 index;

    while (primIndex < MAX_PRIM_ALLOC_COUNT) {
        if (*dstPrimType == 0) {
            DestroyPrimitive(prim);
            if (count == 1) {
                *dstPrimType = primType;
                prim->next = NULL;
                if (D_800A2438 < primIndex) {
                    D_800A2438 = primIndex;
                }
            } else {
                *dstPrimType = primType;
                index = AllocPrimitives(primType, count - 1);
                if (index == -1) {
                    *dstPrimType = 0;
                    return -1;
                }
                prim->next = &g_PrimBuf[index];
            }
            return (s16)primIndex;
        }

        primIndex++;
        dstPrimType += sizeof(Primitive);
        prim++;
        if (primIndex >= 0x400) {
            return -1;
        }
    }
    return -1;
}

s32 func_800EDD9C(u8 primitives, s32 count) {
    u8* pCode;
    u8 temp_v0;
    u8* polyCode;
    POLY_GT4* poly;
    s32 polyIndex;
    s16 foundPolyIndex;
    poly = D_800973B8;
    polyIndex = 0x4FF;
    polyCode = &D_800973B8->code;

    while (polyIndex >= 0) {
        pCode = &poly->code;
        temp_v0 = *polyCode;
        if (temp_v0 == 0) {
            DestroyPrimitive(poly);
            if (count == 1) {
                *polyCode = primitives;
                poly->tag = 0;
            } else {
                *polyCode = primitives;
                foundPolyIndex = func_800EDD9C(primitives, count - 1);
                poly->tag = &g_PrimBuf[foundPolyIndex];
            }
            foundPolyIndex = polyIndex;
            return foundPolyIndex;
        }
        polyIndex--;
        polyCode -= sizeof(POLY_GT4);
        poly--;
        if (polyIndex < 0) {
            return (s16)temp_v0;
        }
    }
    return (s16)temp_v0;
}

void FreePrimitives(s32 primitiveIndex) {
    Primitive* prim = &g_PrimBuf[primitiveIndex];

    if (prim) {
        do {
            if (prim->type == PRIM_ENV) {
                *(*(s32**)&prim->r1) = 0;
                prim->type = PRIM_NONE;
            } else
                prim->type = PRIM_NONE;
            prim = prim->next;
        } while (prim);
    }
}

INCLUDE_ASM("dra/nonmatchings/4A538", RenderPrimitives);
