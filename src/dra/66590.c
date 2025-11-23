// SPDX-License-Identifier: AGPL-3.0-or-later
//! PSPO=4,p
#include "dra.h"

void DestroyEntity(Entity* entity) {
    s32 i;
    s32 length;
    u32* ptr;

    if (entity->flags & FLAG_HAS_PRIMS) {
        FreePrimitives(entity->primIndex);
    }

    ptr = (u32*)entity;
    length = sizeof(Entity) / sizeof(u32);
    for (i = 0; i < length; i++)
        *ptr++ = NULL;
}

void DestroyEntitiesFromIndex(s16 startIndex) {
    Entity* pItem;

    for (pItem = &g_Entities[startIndex];
         pItem < &g_Entities[TOTAL_ENTITY_COUNT]; pItem++)
        DestroyEntity(pItem);
}

void DrawEntitiesHitbox(s32 drawMode) {
    s32 polyCount;
    Entity* entity;
    OT_TYPE* ot;
    TILE* tile;
    DR_MODE* drMode;
    u32 otIdx;
    s16 x, y;

    ot = g_CurrentBuffer->ot;
    tile = &g_CurrentBuffer->tiles[g_GpuUsage.tile];
    drMode = &g_CurrentBuffer->drawModes[g_GpuUsage.drawModes];
    otIdx = 0x1F0;
    for (polyCount = 0, entity = g_Entities; polyCount < 0x40; polyCount++,
        entity++) {
        if (entity->hitboxState == 0)
            continue;
        if (g_GpuUsage.tile >= MAX_TILE_COUNT) {
            break;
        }

        x = entity->posX.i.hi + g_backbufferX;
        y = entity->posY.i.hi + g_backbufferY;
        if (entity->facingLeft) {
            x -= entity->hitboxOffX;
        } else {
            x += entity->hitboxOffX;
        }
        y += entity->hitboxOffY;

        tile->r0 = 0xFF;
        tile->g0 = 0xFF;
        tile->b0 = 0xFF;
        if (entity->hitboxState == 2) {
            tile->r0 = 0;
            tile->g0 = 0xFF;
            tile->b0 = 0;
        }
        tile->x0 = x - entity->hitboxWidth;
        tile->y0 = y - entity->hitboxHeight;
        tile->w = entity->hitboxWidth * 2;
        tile->h = entity->hitboxHeight * 2;
        SetSemiTrans(tile, 1);
        AddPrim(&ot[otIdx], tile);
        tile++;
        g_GpuUsage.tile++;
    }

    for (; polyCount < MAX_TILE_COUNT; polyCount++, entity++) {
        if (entity->hitboxState == 0)
            continue;
        if (g_GpuUsage.tile >= MAX_TILE_COUNT) {
            break;
        }

        x = entity->posX.i.hi + g_backbufferX;
        y = entity->posY.i.hi + g_backbufferY;
        if (entity->facingLeft) {
            x -= entity->hitboxOffX;
        } else {
            x += entity->hitboxOffX;
        }
        y += entity->hitboxOffY;

        tile->r0 = 0xFF;
        tile->g0 = 0xFF;
        tile->b0 = 0xFF;
        if (entity->hitboxState == 1) {
            tile->r0 = 0xFF;
            tile->g0 = 0;
            tile->b0 = 0;
        }
        if (entity->hitboxState == 2) {
            tile->r0 = 0;
            tile->g0 = 0;
            tile->b0 = 0xFF;
        }
        if (entity->hitboxState == 3) {
            tile->r0 = 0xFF;
            tile->g0 = 0;
            tile->b0 = 0xFF;
        }
        tile->x0 = x - entity->hitboxWidth;
        tile->y0 = y - entity->hitboxHeight;
        tile->w = entity->hitboxWidth * 2;
        tile->h = entity->hitboxHeight * 2;
        SetSemiTrans(tile, 1);
        AddPrim(&ot[otIdx], tile);
        tile++;
        g_GpuUsage.tile++;
    }

    if (g_GpuUsage.drawModes < MAX_DRAW_MODES) {
        SetDrawMode(drMode, 0, 0, (drawMode - 1) << 5, &g_Vram.D_800ACD80);
        AddPrim(&ot[otIdx], drMode);
        g_GpuUsage.drawModes++;
    }
}

#ifndef VERSION_PC

u16 D_800AC910[] = {
#ifndef VERSION_US
    '踪', '眷', '翔', '彷', '徨', '苺', '獰', '賤', '贄',
#endif
    '鬱', // last one should be a copyright symbol
};

u8 D_800AC914[][30] = {
#ifndef VERSION_US
    {
        0x00, 0x20, // □□□□□□□□□□■□□□□□
        0x7C, 0x20, // □■■■■■□□□□■□□□□□
        0x45, 0xFE, // □■□□□■□■■■■■■■■□
        0x45, 0x02, // □■□□□■□■□□□□□□■□
        0x45, 0x02, // □■□□□■□■□□□□□□■□
        0x7C, 0x78, // □■■■■■□□□■■■■□□□
        0x10, 0x00, // □□□■□□□□□□□□□□□□
        0x10, 0x00, // □□□■□□□□□□□□□□□□
        0x51, 0xFE, // □■□■□□□■■■■■■■■□
        0x5C, 0x20, // □■□■■■□□□□■□□□□□
        0x50, 0xA4, // □■□■□□□□■□■□□■□□
        0x50, 0xA2, // □■□■□□□□■□■□□□■□
        0x51, 0x22, // □■□■□□□■□□■□□□■□
        0x5C, 0x20, // □■□■■■□□□□■□□□□□
        0xE0, 0x60, // ■■■□□□□□□■■□□□□□
    },
    {
        0x01, 0x00, // □□□□□□□■□□□□□□□□
        0x11, 0x10, // □□□■□□□■□□□■□□□□
        0x2F, 0xE8, // □□■□■■■■■■■□■□□□
        0x42, 0x84, // □■□□□□■□■□□□□■□□
        0x04, 0x40, // □□□□□■□□□■□□□□□□
        0xFF, 0xFE, // ■■■■■■■■■■■■■■■□
        0x08, 0x20, // □□□□■□□□□□■□□□□□
        0x10, 0x10, // □□□■□□□□□□□■□□□□
        0x3F, 0xF8, // □□■■■■■■■■■■■□□□
        0xD0, 0x16, // ■■□■□□□□□□□■□■■□
        0x1F, 0xF0, // □□□■■■■■■■■■□□□□
        0x10, 0x10, // □□□■□□□□□□□■□□□□
        0x1F, 0xF0, // □□□■■■■■■■■■□□□□
        0x10, 0x10, // □□□■□□□□□□□■□□□□
        0x1F, 0xF0, // □□□■■■■■■■■■□□□□
    },
    {
        0x88, 0x00, // ■□□□■□□□□□□□□□□□
        0x4B, 0xBC, // □■□□■□■■■□■■■■□□
        0x10, 0x84, // □□□■□□□□■□□□□■□□
        0xF8, 0x84, // ■■■■■□□□■□□□□■□□
        0x24, 0xA4, // □□■□□■□□■□■□□■□□
        0x22, 0x94, // □□■□□□■□■□□■□■□□
        0xF8, 0x84, // ■■■■■□□□■□□□□■□□
        0x20, 0x84, // □□■□□□□□■□□□□■□□
        0x21, 0x8C, // □□■□□□□■■□□□■■□□
        0x3A, 0x94, // □□■■■□■□■□□■□■□□
        0xE4, 0xA4, // ■■■□□■□□■□■□□■□□
        0x28, 0x84, // □□■□■□□□■□□□□■□□
        0x40, 0x84, // □■□□□□□□■□□□□■□□
        0x40, 0x84, // □■□□□□□□■□□□□■□□
        0x83, 0x9C, // ■□□□□□■■■□□■■■□□
    },
    {
        0x10, 0x40, // □□□■□□□□□■□□□□□□
        0x10, 0x40, // □□□■□□□□□■□□□□□□
        0x20, 0x40, // □□■□□□□□□■□□□□□□
        0x47, 0xFE, // □■□□□■■■■■■■■■■□
        0x90, 0x80, // ■□□■□□□□■□□□□□□□
        0x10, 0x80, // □□□■□□□□■□□□□□□□
        0x20, 0x80, // □□■□□□□□■□□□□□□□
        0x20, 0xFC, // □□■□□□□□■■■■■■□□
        0x60, 0x84, // □■■□□□□□■□□□□■□□
        0xA1, 0x04, // ■□■□□□□■□□□□□■□□
        0x21, 0x04, // □□■□□□□■□□□□□■□□
        0x21, 0x04, // □□■□□□□■□□□□□■□□
        0x22, 0x08, // □□■□□□■□□□□□■□□□
        0x22, 0x08, // □□■□□□■□□□□□■□□□
        0x24, 0x70, // □□■□□■□□□■■■□□□□
    },
    {
        0x10, 0x40, // □□□■□□□□□■□□□□□□
        0x10, 0x80, // □□□■□□□□■□□□□□□□
        0x23, 0xF8, // □□■□□□■■■■■■■□□□
        0x42, 0x08, // □■□□□□■□□□□□■□□□
        0x93, 0xF8, // ■□□■□□■■■■■■■□□□
        0x12, 0x08, // □□□■□□■□□□□□■□□□
        0x23, 0xF8, // □□■□□□■■■■■■■□□□
        0x20, 0x00, // □□■□□□□□□□□□□□□□
        0x67, 0xFC, // □■■□□■■■■■■■■■□□
        0xA0, 0x40, // ■□■□□□□□□■□□□□□□
        0x20, 0x40, // □□■□□□□□□■□□□□□□
        0x23, 0xFC, // □□■□□□■■■■■■■■□□
        0x20, 0x40, // □□■□□□□□□■□□□□□□
        0x20, 0x40, // □□■□□□□□□■□□□□□□
        0x2F, 0xFE, // □□■□■■■■■■■■■■■□
    },
    {
        0x08, 0x40, // □□□□■□□□□■□□□□□□
        0xFF, 0xFE, // ■■■■■■■■■■■■■■■□
        0x08, 0x40, // □□□□■□□□□■□□□□□□
        0x00, 0x00, // □□□□□□□□□□□□□□□□
        0x1F, 0xF0, // □□□■■■■■■■■■□□□□
        0x11, 0x10, // □□□■□□□■□□□■□□□□
        0x10, 0x90, // □□□■□□□□■□□■□□□□
        0x10, 0x10, // □□□■□□□□□□□■□□□□
        0xFF, 0xFE, // ■■■■■■■■■■■■■■■□
        0x22, 0x10, // □□■□□□■□□□□■□□□□
        0x21, 0x10, // □□■□□□□■□□□■□□□□
        0x20, 0x10, // □□■□□□□□□□□■□□□□
        0x7F, 0xFC, // □■■■■■■■■■■■■■□□
        0x40, 0x20, // □■□□□□□□□□■□□□□□
        0x01, 0xC0, // □□□□□□□■■■□□□□□□
    },
    {
        0x08, 0x40, // □□□□■□□□□■□□□□□□
        0x8F, 0xFE, // ■□□□■■■■■■■■■■■□
        0x54, 0x02, // □■□■□■□□□□□□□□■□
        0x25, 0x42, // □□■□□■□■□■□□□□■□
        0x63, 0x14, // □■■□□□■■□□□■□■□□
        0xA5, 0xF2, // ■□■□□■□■■■■■□□■□
        0x10, 0x00, // □□□■□□□□□□□□□□□□
        0x13, 0xFC, // □□□■□□■■■■■■■■□□
        0x32, 0xA4, // □□■■□□■□■□■□□■□□
        0x57, 0xFE, // □■□■□■■■■■■■■■■□
        0x90, 0x00, // ■□□■□□□□□□□□□□□□
        0x17, 0xFE, // □□□■□■■■■■■■■■■□
        0x10, 0x40, // □□□■□□□□□■□□□□□□
        0x10, 0x40, // □□□■□□□□□■□□□□□□
        0x61, 0xC0, // □■■□□□□■■■□□□□□□
    },
    {
        0x00, 0x48, // □□□□□□□□□■□□■□□□
        0x7C, 0x4E, // □■■■■■□□□■□□■■■□
        0x45, 0xF0, // □■□□□■□■■■■■□□□□
        0x44, 0x24, // □■□□□■□□□□■□□■□□
        0x7C, 0x18, // □■■■■■□□□□□■■□□□
        0x44, 0x6A, // □■□□□■□□□■■□■□■□
        0x45, 0x86, // □■□□□■□■■□□□□■■□
        0x7C, 0x50, // □■■■■■□□□■□■□□□□
        0x44, 0x48, // □■□□□■□□□■□□■□□□
        0x44, 0x5E, // □■□□□■□□□■□■■■■□
        0x45, 0xE0, // □■□□□■□■■■■□□□□□
        0x7C, 0x24, // □■■■■■□□□□■□□■□□
        0x00, 0x18, // □□□□□□□□□□□■■□□□
        0x48, 0x6A, // □■□□■□□□□■■□■□■□
        0x85, 0x86, // ■□□□□■□■■□□□□■■□
    },
    {
        0x10, 0x20, // □□□■□□□□□□■□□□□□
        0x7C, 0x20, // □■■■■■□□□□■□□□□□
        0x10, 0xF8, // □□□■□□□□■■■■■□□□
        0xFE, 0x28, // ■■■■■■■□□□■□■□□□
        0x28, 0x6A, // □□■□■□□□□■■□■□■□
        0x7C, 0x5A, // □■■■■■□□□■□■■□■□
        0x10, 0x8E, // □□□■□□□□■□□□■■■□
        0x1F, 0xF0, // □□□■■■■■■■■■□□□□
        0x10, 0x10, // □□□■□□□□□□□■□□□□
        0x1F, 0xF0, // □□□■■■■■■■■■□□□□
        0x10, 0x10, // □□□■□□□□□□□■□□□□
        0x1F, 0xF0, // □□□■■■■■■■■■□□□□
        0x10, 0x10, // □□□■□□□□□□□■□□□□
        0x1F, 0xF0, // □□□■■■■■■■■■□□□□
        0x70, 0x1C, // □■■■□□□□□□□■■■□□
    },
#endif
    {
        0x07, 0xC0, // □□□□□■■■■■□□□□□□
        0x18, 0x30, // □□□■■□□□□□■■□□□□
        0x20, 0x08, // □□■□□□□□□□□□■□□□
        0x47, 0xC4, // □■□□□■■■■■□□□■□□
        0x48, 0x44, // □■□□■□□□□■□□□■□□
        0x90, 0x12, // ■□□■□□□□□□□■□□■□
        0x90, 0x02, // ■□□■□□□□□□□□□□■□
        0x90, 0x02, // ■□□■□□□□□□□□□□■□
        0x90, 0x02, // ■□□■□□□□□□□□□□■□
        0x90, 0x12, // ■□□■□□□□□□□■□□■□
        0x48, 0x44, // □■□□■□□□□■□□□■□□
        0x47, 0xC4, // □■□□□■■■■■□□□■□□
        0x20, 0x08, // □□■□□□□□□□□□■□□□
        0x18, 0x30, // □□□■■□□□□□■■□□□□
        0x07, 0xC0, // □□□□□■■■■■□□□□□□
    },
};
// LUT of ceil(index / 2)
u16 D_800AC934[] = {0, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 7, 8, 8};

#ifdef VERSION_US
u16 D_800AC956 = 0x0D09;
#endif

extern u16 D_80137EF8[];

#define ExtractBit(x)                                                          \
    x & 1;                                                                     \
    x >>= 1

u16* func_80106A28(u16 ch, u16 kind) {
    u8* bitmap;
    u16* srcPtr;
    u16* destPtr;
    u16 i, j, k;
    u16 val0, val1, val2;
    u16 b0, b1, b2, b3;
    u16 dest, dest2;
    u8 row;

    // Krom2RawAdd returns a pointer to 30 bytes: 15 rows of 2 bytes for a
    // bitmap of size 16x15.
    bitmap = (u8*)Krom2RawAdd(ch);
    if (bitmap == (u8*)-1) {
        srcPtr = D_800AC910;
        for (i = 0; i < LEN(D_800AC914); i++) {
            if (ch == *srcPtr++) {
                bitmap = D_800AC914[i];
            }
        }
        if (bitmap == (u8*)-1) {
            ch = 0x819A;
            bitmap = (u8*)Krom2RawAdd(ch);
        }
    }

    srcPtr = D_80137EF8;
    for (i = 0; i < 15; i++) {
        val0 = val2 = val1 = 0;

        row = *bitmap;

        b0 = ExtractBit(row);
        b1 = ExtractBit(row);
        b2 = ExtractBit(row);
        b3 = ExtractBit(row);

        val1 |= (b0 * 3 + b1) << 0x4;
        val1 |= (b1 * 2 + b2 * 2);
        val0 |= (b2 + b3 * 3) << 0xC;

        b0 = ExtractBit(row);
        b1 = ExtractBit(row);
        b2 = ExtractBit(row);
        b3 = ExtractBit(row);

        val0 |= (b0 * 3 + b1) << 0x8;
        val0 |= (b1 * 2 + b2 * 2) << 0x4;
        val0 |= b2 + b3 * 3;

        bitmap++;

        row = *bitmap;

        b0 = ExtractBit(row);
        b1 = ExtractBit(row);
        b2 = ExtractBit(row);
        b3 = ExtractBit(row);

        val2 |= (b0 * 3 + b1) << 0xC;
        val2 |= (b1 * 2 + b2 * 2) << 0x8;
        val2 |= (b2 + b3 * 3) << 0x4;

        b0 = ExtractBit(row);
        b1 = ExtractBit(row);
        b2 = ExtractBit(row);
        b3 = ExtractBit(row);

        val2 |= b0 * 3 + b1;
        val1 |= (b1 * 2 + b2 * 2) << 0xC;
        val1 |= (b2 + b3 * 3) << 0x8;
        dest = val1; // fake

        *srcPtr++ = val0;
        *srcPtr++ = val1;
        *srcPtr++ = val2;
        bitmap++;
    }

    destPtr = D_80137EF8;
    srcPtr = D_80137EF8;
    switch (kind) {
    case 0:
    case 3:
        for (i = 0; i < 45; i++) {
            val0 = *srcPtr++;
            dest = D_800AC934[(val0 >> 0xC & 0xF) * 4] << 0xC;
            dest |= D_800AC934[(val0 >> 0x8 & 0xF) * 4] << 0x8;
            dest |= D_800AC934[(val0 >> 0x4 & 0xF) * 4] << 0x4;
            dest |= D_800AC934[(val0 >> 0x0 & 0xF) * 4] << 0x0;
            *destPtr++ = dest;
        }
        for (i = 0; i < 3; i++) {
            *destPtr++ = 0;
        }
        break;

    case 1:
        for (i = 0; i < 2; i++) {
            for (j = 0; j < 3; j++) {
                for (k = 7; k > 0; k--) {
                    val0 = *srcPtr;
                    srcPtr += 3;
                    val2 = *srcPtr;
                    dest = D_800AC934[((val0 >> 0xC & 0xF) * k +
                                       (val2 >> 0xC & 0xF) * (8 - k)) /
                                      2]
                           << 0xC;
                    dest |= D_800AC934[((val0 >> 0x8 & 0xF) * k +
                                        (val2 >> 0x8 & 0xF) * (8 - k)) /
                                       2]
                            << 0x8;
                    dest |= D_800AC934[((val0 >> 0x4 & 0xF) * k +
                                        (val2 >> 0x4 & 0xF) * (8 - k)) /
                                       2]
                            << 0x4;
                    dest |= D_800AC934[((val0 >> 0x0 & 0xF) * k +
                                        (val2 >> 0x0 & 0xF) * (8 - k)) /
                                       2]
                            << 0x0;
                    *destPtr = dest;
                    destPtr += 3;
                }
                srcPtr -= 20;
                destPtr -= 20;
            }
            srcPtr += 21;
            destPtr += 18;
        }
        for (i = 0; i < 6; i++) {
            *destPtr++ = 0;
        }
        break;

    case 2:
        for (i = 0; i < 4; i++) {
            for (j = 0; j < 3; j++) {
                for (k = 3; k > 0; k--) {
                    val0 = *srcPtr;
                    srcPtr += 3;
                    val2 = *srcPtr;
                    dest = D_800AC934[(val0 >> 0xC & 0xF) * k +
                                      (val2 >> 0xC & 0xF) * (4 - k)]
                           << 0xC;
                    dest |= D_800AC934[(val0 >> 0x8 & 0xF) * k +
                                       (val2 >> 0x8 & 0xF) * (4 - k)]
                            << 0x8;
                    dest |= D_800AC934[(val0 >> 0x4 & 0xF) * k +
                                       (val2 >> 0x4 & 0xF) * (4 - k)]
                            << 0x4;
                    dest |= D_800AC934[(val0 >> 0x0 & 0xF) * k +
                                       (val2 >> 0x0 & 0xF) * (4 - k)]
                            << 0x0;
                    *destPtr = dest;
                    destPtr += 3;
                }
                srcPtr -= 8;
                destPtr -= 8;
            }
            srcPtr += 9;
            destPtr += 6;
        }
        for (i = 0; i < 12; i++) {
            *destPtr++ = 0;
        }
        break;
    }
    if (kind == 3) {
        for (i = 0; i < 0x42; i++) {
            dest2 = D_80137EF8[i];
            if (dest2 & 4) {
                if ((D_80137EF8[i] & 0xF0) == 0) {
                    D_80137EF8[i] |= 0x10;
                }
            }
            if (dest2 & 0x40) {
                if ((D_80137EF8[i] & 0xF00) == 0) {
                    D_80137EF8[i] |= 0x100;
                }
            }
            if (dest2 & 0x400) {
                if ((D_80137EF8[i] & 0xF000) == 0) {
                    D_80137EF8[i] |= 0x1000;
                }
            }
            if ((dest2 & 0x4000) && (i < 0x41)) {
                if ((D_80137EF8[i + 1] & 0xF) == 0) {
                    D_80137EF8[i + 1] |= 1;
                }
            }
        }
    }
    return D_80137EF8;
}

#endif

bool LoadMonsterLibrarianPreview(s32 monsterId) {
    if (g_IsUsingCd)
        return false;

    if (g_UseDisk) {
        g_CdStep = CdStep_LoadInit;
        g_LoadFile = CdFile_Monster;
        g_LoadOvlIdx = monsterId;
    } else if (LoadFileSim(monsterId, SimFileType_Monster) < 0) {
        return false;
    }
    return true;
}

void func_801071CC(Primitive* prim, u8 colorIntensity, s32 vertexIndex) {
    switch (vertexIndex) {
    case 0:
        prim->b0 = colorIntensity;
        prim->g0 = colorIntensity;
        prim->r0 = colorIntensity;
        break;
    case 1:
        prim->b1 = colorIntensity;
        prim->g1 = colorIntensity;
        prim->r1 = colorIntensity;
        break;
    case 2:
        prim->b2 = colorIntensity;
        prim->g2 = colorIntensity;
        prim->r2 = colorIntensity;
        break;
    case 3:
        prim->b3 = colorIntensity;
        prim->g3 = colorIntensity;
        prim->r3 = colorIntensity;
        break;
    }
}

void func_80107250(Primitive* prim, u8 colorIntensity) {
    func_801071CC(prim, colorIntensity, 0);
    func_801071CC(prim, colorIntensity, 1);
    func_801071CC(prim, colorIntensity, 2);
    func_801071CC(prim, colorIntensity, 3);
}

void func_801072BC(Primitive* prim) { func_80107250(prim, 0); }

void func_801072DC(Primitive* prim) { func_80107250(prim, 0x80); }

void func_801072FC(POLY_G4* poly) {
    setRGB0(poly, 0, 0, 0);
    setRGB1(poly, 0, 0, 0);
    setRGB2(poly, 0, 0, 0);
    setRGB3(poly, 0, 0, 0);
}

#include "../set_prim_rect.h"
