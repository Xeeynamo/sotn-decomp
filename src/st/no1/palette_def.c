// SPDX-License-Identifier: AGPL-3.0-or-later
#include "no1.h"

// Written by hand: a 16-colour palette (D_80180158) sits between pal_def_0
// and pal_def_1 and is copied by pal_def_2, which the paldef asset handler
// cannot extract yet (issue #2401).

extern u16 D_80195490[];
extern u16 D_801954B0[];
extern u16 D_801954D0[];
extern u16 D_801954F0[];
extern u16 D_80195510[];
extern u16 D_80195530[];
extern u16 D_80195550[];
extern u16 D_801955D0[];
extern u16 D_80195650[];
extern u16 D_801956B0[];
extern u16 D_801957B0[];
extern u16 D_801957F0[];
extern u16 D_80195810[];
extern u16 D_80195830[];
extern u16 D_801958B0[];
extern u16 D_80195AD0[];
extern u16 D_80195C50[];
extern u16 D_80195CB0[];
extern u16 D_80195D10[];
extern u16 D_80195D70[];
extern u16 D_80195DB0[];
extern u16 D_80195EB0[];

static u_long* pal_def_0[] = {
    MAKE_PAL_OP(PAL_BULK_COPY, 0),        PAL_BULK_(0x2000, D_80195550, 0x30),
    PAL_BULK_(0x2030, D_801955D0, 0x40),  PAL_BULK_(0x2070, D_80195650, 0x30),
    PAL_BULK_(0x20A0, D_801956B0, 0x80),  PAL_BULK_(0x2120, D_801957F0, 0x10),
    PAL_BULK_(0x2130, D_801957B0, 0x20),  PAL_BULK_(0x2150, D_80195810, 0x10),
    PAL_BULK_(0x2160, D_80195830, 0x40),  PAL_BULK_(0x21A0, D_801958B0, 0x20),
    PAL_BULK_(0x21C0, D_80195AD0, 0x60),  PAL_BULK_(0x2220, D_80195C50, 0x30),
    PAL_BULK_(0x2250, D_80195D10, 0x30),  PAL_BULK_(0x2280, D_80195CB0, 0x30),
    PAL_BULK_(0x22B0, D_80195D70, 0x20),  PAL_BULK_(0x22D0, D_80195DB0, 0x80),
    PAL_BULK_(0x2E00, D_80195EB0, 0x100), PAL_TERMINATE(),
};

u16 D_80180158[] = {
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
};

static u_long* pal_def_1[] = {
    MAKE_PAL_OP(PAL_UNK_OP3 | 0xC000, 6),
    (u_long*)0x0470,
    (u_long*)0x10,
    (u_long*)D_80195490,
    (u_long*)D_801954B0,
    (u_long*)D_801954D0,
    (u_long*)D_801954F0,
    PAL_TERMINATE(),
};

static u_long* pal_def_2[] = {
    MAKE_PAL_OP(PAL_BULK_COPY | 0xC000, 0),
    PAL_BULK_(0x0470, D_80180158, 0x10),
    PAL_TERMINATE(),
};

static u_long* pal_def_3[] = {
    MAKE_PAL_OP(PAL_UNK_OP3 | 0xC000, 1),
    (u_long*)0x02F0,
    (u_long*)0x10,
    (u_long*)D_80195510,
    (u_long*)D_80195530,
    PAL_TERMINATE(),
};

u_long* cluts[] = {
    (u_long*)&pal_def_0,
    (u_long*)&pal_def_1,
    (u_long*)&pal_def_2,
    (u_long*)&pal_def_3,
};
