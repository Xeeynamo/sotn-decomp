// SPDX-License-Identifier: AGPL-3.0-or-later
#include <game.h>

u8 text_item_up[] = {
#include "gen/text_item_up.h"
};
u8 load_room_obj[] = {
#include "gen/load_room_obj.h"
};
u8 save_room_obj[] = {
#include "gen/save_room_obj.h"
};
u8 load_room_tile[] = {
#include "gen/load_room_tile.h"
};
u8 save_room_tile[] = {
#include "gen/save_room_tile.h"
};

u8 D_800C4CEC[] = {
    16,
    16,
    0,
    0,
#include "../dra/gen/D_800C4CEC.h"
};

u8 D_800C4D70[] = {
    16,
    16,
    0,
    0,
#include "../dra/gen/D_800C4D70.h"
};

u8 D_800C4DF4[] = {
    16,
    16,
    0,
    0,
#include "../dra/gen/D_800C4DF4.h"
};

u8 D_800C4E78[] = {
    16,
    16,
    0,
    0,
#include "../dra/gen/D_800C4E78.h"
};

u8 D_800C4EFC[] = {
    16,
    16,
    0,
    0,
#include "../dra/gen/D_800C4EFC.h"
};

u8 D_800C4F80[] = {
    16,
    16,
    0,
    0,
#include "../dra/gen/D_800C4F80.h"
};

u8 D_800C5004[] = {
    16,
    16,
    0,
    0,
#include "../dra/gen/D_800C5004.h"
};

u8 D_800C5088[] = {
    16,
    16,
    0,
    0,
#include "../dra/gen/D_800C5088.h"
};

u8 D_800C510C[] = {
    16,
    16,
    0,
    0,
#include "../dra/gen/D_800C510C.h"
};

u8 D_800C5190[] = {
    16,
    16,
    0,
    0,
#include "../dra/gen/D_800C5190.h"
};

u8 D_800C5214[] = {
    8,
    56,
    0,
    0,
#include "../dra/gen/D_800C5214.h"
};

u8* D_800C52F8[] = {
    // subweapon graphics?
    D_800C4CEC, D_800C4D70, D_800C4DF4, D_800C4E78, D_800C4EFC, D_800C4F80,
    D_800C5004, D_800C5088, D_800C510C, D_800C5190, D_800C5214,
};
