// SPDX-License-Identifier: AGPL-3.0-or-later
#include "mad.h"
#include "sfx.h"

extern RoomDef rooms_layers[];
extern RoomHeader rooms[];
extern LayoutEntity* entityLayoutHorizontal[];

// Looks like this builds the randomly jagged floor
void func_8018D8C8(u16* tilemap) {
    s32 heights[15];
    s32 rowOffset;
    u16* tilePtr;
    s32 i;
    s32 x;
    s32 row;
    s32* height;
    u16 tileRight;
    u16 tile;
    u16 tileLeft;
    u16 tileBelow;
    s32 left;
    s32 idx;
    s32 right;

    // zero out the heights array
    for (i = 0; i < LEN(heights); i++) {
        heights[i] = 0;
    }

    // make some kind of mountain pattern?
    for (i = 0; i < 20; i++) {
    loop:

        // pick an offset in range [2, 12]
        idx = 2 + (rand() % 11);
        // 0  1  2  3  4  5  6  7  8  9 10 11 12 13 14
        // [0, 0, x, x, x, x, x, x, x, x, 0, 0, 0, 0, 0]
        height = (s32*)(idx * sizeof(s32) + (size_t)heights);

        left = height[-1];
        if (*height >= left + 2) {
            goto loop;
        }
        right = height[1];
        if (*height >= right + 2) {
            goto loop;
        }

        if (!(*height % 2)) { // if the value is even
            if (left + 1 == *height || right + 1 == *height) {
                goto loop;
            }
        }

        // keep re-picking until we make it through the gauntlet of tests, then:
        *height += 1;
    }

    // Pick the tile for every column of every height band from the step the
    // heights take between column x and column x + 1.
    for (row = 0; row < 4; row++) {
        for (x = 0; x < 14; x++) {
            tile = 3;
            if ((row & 1) == 0) {
                if ((heights[x] == 2 * row) &&
                    (heights[x + 1] == (2 * row + 2))) {
                    tile = 7;
                }
                if ((row & 1) == 0) {
                    if (heights[x] == 2 * (row + 1)) {
                        if (heights[x + 1] == 2 * row) {
                            tile = 4;
                        }
                    }
                }
            }
            if ((heights[x] >= 2 * (row + 1)) &&
                (heights[x + 1] >= 2 * (row + 1))) {
                tile = 0;
            }
            if (heights[x] == 2 * row) {
                if (heights[x + 1] == (2 * row + 1)) {
                    tile = 16;
                }
            }
            if (heights[x] == row * 2 + 1) {
                if (heights[x + 1] == 2 * (row + 1)) {
                    tile = 17;
                }
                if (heights[x + 1] == 2 * row) {
                    tile = 13;
                }
            }
            if ((heights[x] == 2 * (row + 1)) &&
                (heights[x + 1] == 2 * row + 1)) {
                tile = 12;
            }
            if (heights[x] == 2 * row + 1 && heights[x + 1] == heights[x]) {
                tile = 27;
            }
            tilePtr = tilemap + x + 16 * row;
            tilePtr[0xA1] = tile;
        }
    }

    for (row = 0; row < 4; row++) {
        rowOffset = 32 * row;
        for (x = 0; x < 14; x++) {
            tileLeft = LOHU(*((u8*)&tilemap[x] + rowOffset + 0x140));
            tileRight = LOHU(*((u8*)&tilemap[x] + rowOffset + 0x144));
            tileBelow = LOHU(*((u8*)&tilemap[x] + rowOffset + 0x162));
            switch (LOHU(*((u8*)&tilemap[x] + rowOffset + 0x142))) {
            case 7:
                if (tileLeft == 3) {
                    tileLeft = 2;
                }
                if (tileBelow == 3) {
                    tileBelow = 6;
                }
                break;
            case 4:
                if (tileRight == 3) {
                    tileRight = 2;
                }
                if (tileBelow == 3) {
                    tileBelow = 5;
                }
                break;
            case 16:
                if (tileLeft == 3) {
                    tileLeft = 2;
                }
                break;
            case 17:
                if (tileBelow == 3) {
                    tileBelow = 15;
                }
                break;
            case 13:
                if (tileRight == 3) {
                    tileRight = 2;
                }
                break;
            case 12:
                if (tileBelow == 3) {
                    tileBelow = 14;
                }
                break;
            }
            LOHU(*((u8*)&tilemap[x] + 0x140 + rowOffset)) = tileLeft;
            LOHU(*((u8*)&tilemap[x] + 0x144 + rowOffset)) = tileRight;
            LOHU(*((u8*)&tilemap[x] + 0x162 + rowOffset)) = tileBelow;
        }
    }
}

// Looks like this builds the randomly jagged ceiling
void func_8018DC28(u16* tilemap) {
    s32 heights[15];
    s32 i;
    s32 x;
    s32 row;
    s32* height;
    u16 tileRight;
    u16 tile;
    u16 tileLeft;
    u16 tileAbove;
    s32 left;
    s32 idx;
    s32 right;

    // zero out the heights array
    for (i = 0; i < LEN(heights); i++) {
        heights[i] = 0;
    }

    // make some kind of mountain pattern?
    for (i = 0; i < 20; i++) {
    loop:

        // pick an offset in range [1, 14]
        idx = 1 + (rand() % 13);
        // 0  1  2  3  4  5  6  7  8  9 10 11 12 13 14
        // [0, x, x, x, x, x, x, x, x, x, x, x, x, x, x]
        height = (s32*)(idx * sizeof(s32) + (size_t)heights);

        left = height[-1];
        if (*height >= left + 2) {
            goto loop;
        }
        right = height[1];
        if (*height >= right + 2) {
            goto loop;
        }

        // keep re-picking until we make it through the gauntlet of tests, then:
        *height += 2;
    }

    for (row = 0; row < 4; row++) {
        for (x = 0; x < 14; x++) {
            tile = 3;
            if ((heights[x] == 2 * row) && (heights[x + 1] == 2 * row + 2)) {
                tile = 11;
            }
            if ((heights[x] == 2 * (row + 1)) && (heights[x + 1] == 2 * row)) {
                tile = 8;
            }
            if ((heights[x] >= 2 * (row + 1)) &&
                (heights[x + 1] >= 2 * (row + 1))) {
                tile = 0;
            }
            if ((heights[x] >= 2 * (row + 2)) ||
                (heights[x + 1] >= 2 * (row + 2))) {
                tile = 0;
            }
            if ((heights[x] <= 2 * (row - 1)) &&
                (heights[x + 1] == 2 * (row + 1))) {
                tile = 11;
            }
            if ((heights[x] == 2 * (row + 1)) &&
                (heights[x + 1] <= 2 * (row - 1))) {
                tile = 8;
            }
            *(tilemap + x + 16 * (5 - row) + 1) = tile;
        }
    }

    for (row = 0; row < 4; row++) {
        for (x = 0; x < 14; x++) {
            tileLeft = LOHU(*((u8*)&tilemap[x] + 32 * (5 - row) + 0));
            tileRight = LOHU(*((u8*)&tilemap[x] + 32 * (5 - row) + 4));
            tileAbove = LOHU(*((u8*)&tilemap[x] + 32 * (4 - row) + 2));
            switch (LOHU(*((u8*)&tilemap[x] + 32 * (5 - row) + 2))) {
            case 11:
                if (tileLeft == 3) {
                    tileLeft = 2;
                }
                if (tileAbove == 3) {
                    tileAbove = 10;
                }
                break;
            case 8:
                if (tileRight == 3) {
                    tileRight = 2;
                }
                if (tileAbove == 3) {
                    tileAbove = 9;
                }
                break;
            }
            LOHU(*((u8*)&tilemap[x] + 32 * (5 - row) + 0)) = tileLeft;
            LOHU(*((u8*)&tilemap[x] + 32 * (5 - row) + 4)) = tileRight;
            LOHU(*((u8*)&tilemap[x] + 32 * (4 - row) + 2)) = tileAbove;
        }
    }
}

void func_8018DF0C(u16* tilemap, s32 arg1) {
    const int RoomWidth = 32;
    s32 y, x;
    s16 tile;

    for (y = 0; y < 16; y++) {
        for (x = 0; x < 32; x++) {
            if (y < 2 || y > 13) {
                tile = 3;
            } else {
                tile = 0;
            }
            if (x < 2 || x > 29) {
                tile = 3;
            }
            *(tilemap + x + y * RoomWidth) = tile;
        }
    }
    if (arg1 & 4) {
        for (y = 6; y < 10; y++) {
            for (x = 0; x < 2; x++) {
                *(tilemap + x + y * RoomWidth) = 0;
            }
        }
    }
    if (arg1 & 8) {
        for (y = 6; y < 10; y++) {
            for (x = 30; x < 32; x++) {
                *(tilemap + x + y * RoomWidth) = 0;
            }
        }
    }
    if (arg1 & 1) {
        for (y = 0; y < 2; y++) {
            for (x = 6; x < 10; x++) {
                u8 variant = !(arg1 & 8) * RoomWidth;
                *((u16*)((u8*)&tilemap[x] + variant) + y * RoomWidth) = 0;
            }
        }
    }
    if (arg1 & 2) {
        for (y = 14; y < 16; y++) {
            for (x = 6; x < 10; x++) {
                u8 variant = !(arg1 & 8) * RoomWidth;
                *((u16*)((u8*)&tilemap[x] + variant) + y * RoomWidth) = 0;
            }
        }
    }
}

void func_8018E090(u16* tilemap) {
    const int RoomWidth = 32;
    s32 x, y;
    s32 varY;
    s32 varX;

randomize_pos:
    varX = (rand() & 0xF) + 8;
    varY = (rand() & 7) + 4;
    for (y = -2; y < 3; y++) {
        for (x = -1; x < 2; x++) {
            if (*(&tilemap[varX + x] + (varY + y) * RoomWidth)) {
                goto randomize_pos;
            }
        }
    }
    *(tilemap + varX + varY * RoomWidth) = 3;
}

void func_8018E13C(u16* tilemap) {
    const int RoomWidth = 16;
    s32 x, y;

    for (y = 10; y < 16; y++) {
        for (x = 0; x < RoomWidth; x++) {
            if (rand() & 1) {
                *(tilemap + x + y * RoomWidth) = 3;
            }
        }
    }
}

void func_8018E1D4(void) {
    s32 var_a1;
    u16* tilemap;
    LayoutEntity** new_var;
    LayoutEntity** entityLayouts;
    LayoutEntity* entityLayout;
    LayerDef* layer;
    s32 paramLo;
    u16 params;
    s32 i;
    s32 j;
    s32 k;
    RoomHeader* room;
    RoomDef* roomDef;

    new_var = &entityLayoutHorizontal[1];
    layer = rooms_layers[0].fg;
    func_8018E13C(layer->layout);
    entityLayout = *new_var;
    entityLayout[1].posX = (rand() % 160) + 0x30;
    entityLayout[1].posY = (rand() % 112) + 0x30;

    params = entityLayout[1].params;
    params &= 0xFF00;
    params += (rand() % 23);
    entityLayout[1].params = params;

    entityLayouts = new_var + 1;
    for (j = 0; j < 8; j++) {
        entityLayout = entityLayouts[j * 2];
        entityLayout++;
        for (i = 0; i < 15; i++, entityLayout++) {
            entityLayout->posX = (rand() & 0x20) + (i << 5) + 0x10;
            entityLayout->posY = (rand() % 160) + 0x30;
            params = entityLayout->params;
            params &= 0xFF00;
        loop_3:
            paramLo = rand() % 39;
            if (paramLo == 12) {
                goto loop_3;
            }
            params += paramLo;
            entityLayout->params = params;
        }
    }

    for (i = 0; i < 16; i++) {
        room = (RoomHeader*)((i + 1) * sizeof(RoomHeader) + (size_t)rooms);
        roomDef = &rooms_layers[i + 1];
        layer = roomDef->fg;
        if (!(i % 2)) {
            room->right++;
            layer->rect.right++;
        } else {
            layer->rect.left = room->left = 0;
            layer->rect.top = room->top = 0;
            layer->rect.right = room->right = 0;
            layer->rect.bottom = room->bottom = 0;
        }
    }

    for (i = 0, k = 1; i < 16; i++, k++) {
        if (rooms[k].left) {
            roomDef = &rooms_layers[i + 1];
            layer = roomDef->fg;
            tilemap = layer->layout;

            var_a1 = 0;
            if (i == 0) {
                var_a1 = 4;
            }
            if (i == 12) {
                var_a1 = 4;
            }
            if (i & 3) {
                var_a1 |= 4;
            } else {
                var_a1 |= 8;
            }
            if (i == 6) {
                var_a1 |= 1;
            }
            if (i == 8) {
                var_a1 |= 1;
            }
            if (i == 14) {
                var_a1 |= 1;
            }
            if (i == 2) {
                var_a1 |= 2;
            }
            if (i == 4) {
                var_a1 |= 2;
            }
            if (i == 10) {
                var_a1 |= 2;
            }
            func_8018DF0C(tilemap, var_a1);
            func_8018E090(tilemap);
            func_8018E090(tilemap);
            func_8018E090(tilemap);
            func_8018E090(tilemap);
        }
    }

    layer = rooms_layers[0].fg;
    tilemap = layer->layout;
    func_8018D8C8(tilemap);
    func_8018DC28(tilemap);
}
