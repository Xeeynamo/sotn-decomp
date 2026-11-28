// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rno4.h"

extern s16 D_us_801815DC;
extern s16 D_us_801DCF54;
extern EInit g_EInitCommon;

#if TARGET == TARGET_PSP
static s16 D_us_801815E4[] = {
    0x0000, 0x04D0, 0x00D8, 0x00F0, 0x0068, 0x00B0,
    0x00D8, 0x00F0, 0x0340, 0x0074, 0x00D8, 0x00F0,
};
#else
static s16 D_us_801815E4[] = {0x00D8, 0x00F0, 0x0068, 0x00B0, 0x00D8,
                              0x00F0, 0x0340, 0x0074, 0x00D8, 0x00F0};
#endif
static s16 water_slow_zones[] = {
    0x0260, 0x0020, 0x00D0, 0x0080, 0x0470, 0x0020,
    0x00D0, 0x0080, 0x00C0, 0x002C, 0x00E0, 0x0500,
};
static u16 D_us_80181610[] = {
    0x0373, 0x0000, 0x0000, 0x0000, 0x075E, 0x0001, 0x0001, 0x0001,
};

extern s16 water_surface_lines[]; // 0x63E68
extern s16 water_tile_rects[];    // 0x63F68

static void func_us_801A071C_from_bo3() {
    s16* data;
    s16* tileRects;
    s16* surfaceLines;
    s16 value;

    data = D_us_801815E4;
    tileRects = water_tile_rects;
    surfaceLines = water_surface_lines;

#if TARGET == TARGET_PSP
    data += 2;
    tileRects += 0x6E;
    surfaceLines += 0x70;
#endif

    value = 0xD8 - D_us_801815DC;

    if (value < 0x18) {
        value = 0;
    }

    *data = value;
    *tileRects = value;
    *surfaceLines = value;

    data += 4;
    tileRects += 4;
    surfaceLines += 5;

    if (D_us_801815DC < 0xC0) {
        value = 0xF0;
    } else {
        value = 0x1A8 - D_us_801815DC;
    }

    data[0] = value;
    data += 4;
    data[0] = value;

    if (value > 0xE8) {
        value = 0xE8;
    }

    surfaceLines[0] = value;
    surfaceLines += 5;
    surfaceLines[0] = value;
    value++;

    tileRects[0] = value;
    tileRects += 4;
    tileRects[0] = value;
}

void func_us_801A07CC_from_bo3(Entity* self) {
    Entity* player;
    player = &PLAYER;

    D_us_801DCF54 = 0;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitInteractable);

        if (D_us_801815DC) {
            if (g_CastleFlags[SCYLLA_DEFEATED]) {
                self->step = 5;
            } else {
                self->step = 3;
            }
        } else if (g_CastleFlags[SCYLLA_DEFEATED]) {
            self->step = 6;
        }
        break;

    case 1:
        if (player->posX.i.hi >= 0x38) {
            self->ext.timer.t = 0x10;
            self->step++;
        }
        break;

    case 2:
        if (!--self->ext.timer.t) {
            self->step++;
        }
        break;

    case 3:
        if (self->ext.timer.t) {
            --self->ext.timer.t;
        } else {
            self->ext.timer.t = 3;

            if (D_us_801815DC < 0xD0) {
                D_us_801815DC++;
                D_us_801DCF54 = -1;
            } else {
                self->step++;
                self->ext.timer.t = 0x80;
            }
        }
        func_us_801A071C_from_bo3();
        break;

    case 4:
        if (!(self->ext.timer.t -= 1)) {
            g_CastleFlags[0xC3] = 1;
            self->step++;
        }
        break;

    case 5:
        if (self->ext.timer.t) {
            --self->ext.timer.t;
        } else {
            self->ext.timer.t = 1;

            if (D_us_801815DC > 0) {
                D_us_801815DC--;
                D_us_801DCF54 = 1;
            } else {
                self->step++;
            }
        }
        func_us_801A071C_from_bo3();
        break;

    case 6:
        break;
    }
}

#include "../water_slow_zone.h"

static void func_us_801C9048(s32 arg0) {
    s16 tilePos;
    s32 i;
    u16* tileLayoutPtr;

    Tilemap* tilemap;
    tilemap = &g_Tilemap;

    tilePos = 0x1E0;
    tileLayoutPtr = &(D_us_80181610[arg0 * 4]);

    for (i = 0; i < 4; ++i) {
        tilemap->fg[tilePos] = *(tileLayoutPtr++);
        tilePos += 0x50;
    }
}

void func_us_801C909C(Entity* self) {
    s16 screen_pos;
    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitCommon);
        self->animSet = ANIMSET_OVL(1);
        self->animCurFrame = 0x25;
        if (D_us_801815DC) {
            func_us_801C9048(1);
            self->step = 0x4;
            break;
        }
        func_us_801C9048(0);
        self->posY.i.hi -= 0x40;
        break;

    case 1:
        if (D_us_801815DC) {
            self->step += 1;
            self->velocityY = FIX(4.0);
        }

        break;

    case 2:
        self->posX.i.hi -= 8;
        GetPlayerCollisionWith(self, 0x10, 0x20, 9);
        self->posX.i.hi += 8;
        MoveEntity();
        screen_pos = self->posY.i.hi + g_Tilemap.scrollY.i.hi;
        if (screen_pos >= 0x80) {
            g_api.PlaySfxVolPan(SFX_EXPLODE_B, 0x7F, -6);
            func_us_801C9048(1);
            self->velocityY = FIX(-1.0);
            self->step += 1;
        }
        break;

    case 3:
        self->velocityY += FIX(0.125);
        MoveEntity();
        screen_pos = self->posY.i.hi + g_Tilemap.scrollY.i.hi;
        if (screen_pos >= 0x80) {
            self->posY.i.hi = 0x80 - g_Tilemap.scrollY.i.hi;
            self->step = 6;
        }
        break;

    case 4:
        if (!D_us_801815DC) {
            self->step += 1;
            self->velocityY = FIX(-1.0);
        }
        break;

    case 5:
        self->posX.i.hi -= 8;
        GetPlayerCollisionWith(self, 0x10, 0x20, 0xB);
        self->posX.i.hi += 8;
        MoveEntity();
        screen_pos = self->posY.i.hi + g_Tilemap.scrollY.i.hi;
        if (screen_pos < 0x41) {
            func_us_801C9048(0);
            self->step += 1;
        }
        break;

    case 6:
        break;
    }
}
