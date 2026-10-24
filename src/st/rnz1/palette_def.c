// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rnz1.h"

extern u16 D_us_80192884[];
extern u16 D_us_80192B44[];
extern u16 D_us_80192C04[];
extern u16 D_us_80192CA4[];
extern u16 D_us_80192CE4[];
extern u16 D_us_80192D64[];
extern u16 D_us_80192E64[];
extern u16 D_us_80192EC4[];
extern u16 D_us_80192F84[];

static u_long* pal_def_0[] = {
    MAKE_PAL_OP(PAL_BULK_COPY, 0),
    PAL_BULK_(0x2000, D_us_80192B44, 0x10),
    PAL_BULK_(0x2100, D_us_80192C04, 0x50),
    PAL_BULK_(0x2150, D_us_80192CA4, 0x20),
    PAL_BULK_(0x2260, D_us_80192CE4, 0x40),
    PAL_BULK_(0x22A0, D_us_80192D64, 0x80),
    PAL_BULK_(0x2320, D_us_80192E64, 0x30),
    PAL_BULK_(0x2360, D_us_80192EC4, 0x60),
    PAL_BULK_(0x23C0, D_us_80192F84, 0x80),
    PAL_BULK_(0x2E00, D_us_80192884, 0x100),
    PAL_TERMINATE(),
};
u16 D_us_80180114[] = {
#include "gen/D_us_80180114.h"
};
u16 D_us_80180134[] = {
#include "gen/D_us_80180134.h"
};
u16 D_us_80180154[] = {
#include "gen/D_us_80180154.h"
};
u16 D_us_80180174[] = {
#include "gen/D_us_80180174.h"
};
u16 D_us_80180194[] = {
#include "gen/D_us_80180194.h"
};
u16 D_us_801801B4[] = {
#include "gen/D_us_801801B4.h"
};
u16 D_us_801801D4[] = {
#include "gen/D_us_801801D4.h"
};
u16 D_us_801801F4[] = {
#include "gen/D_us_801801F4.h"
};
u16 D_us_80180214[] = {
#include "gen/D_us_80180214.h"
};
u16 D_us_80180234[] = {
#include "gen/D_us_80180234.h"
};
u16 D_us_80180254[] = {
#include "gen/D_us_80180254.h"
};
u16 D_us_80180274[] = {
#include "gen/D_us_80180274.h"
};
u16 D_us_80180294[] = {
#include "gen/D_us_80180294.h"
};
u16 D_us_801802B4[] = {
#include "gen/D_us_801802B4.h"
};
u16 D_us_801802D4[] = {
#include "gen/D_us_801802D4.h"
};
static u_long* pal_def_1[] = {
    MAKE_PAL_OP(PAL_UNK_OP3, 1),
    (u_long*)0x00B0,
    (u_long*)0x10,
    (u_long*)(D_us_80180114),
    (u_long*)(D_us_80180134),
    (u_long*)(D_us_80180154),
    (u_long*)(D_us_80180174),
    (u_long*)(D_us_80180194),
    (u_long*)(D_us_801801B4),
    (u_long*)(D_us_801801D4),
    (u_long*)(D_us_801801F4),
    (u_long*)(D_us_80180214),
    (u_long*)(D_us_80180234),
    (u_long*)(D_us_80180254),
    (u_long*)(D_us_80180274),
    (u_long*)(D_us_80180294),
    (u_long*)(D_us_801802B4),
    (u_long*)(D_us_801802D4),
    PAL_TERMINATE(),
};
static u_long* pal_def_2[] = {
    MAKE_PAL_OP(PAL_UNK_OP3, 1),
    (u_long*)0x00E0,
    (u_long*)0x10,
    (u_long*)(D_us_80180114),
    (u_long*)(D_us_80180134),
    (u_long*)(D_us_80180154),
    (u_long*)(D_us_80180174),
    (u_long*)(D_us_80180194),
    (u_long*)(D_us_801801B4),
    (u_long*)(D_us_801801D4),
    (u_long*)(D_us_801801F4),
    (u_long*)(D_us_80180214),
    (u_long*)(D_us_80180234),
    (u_long*)(D_us_80180254),
    (u_long*)(D_us_80180274),
    (u_long*)(D_us_80180294),
    (u_long*)(D_us_801802B4),
    (u_long*)(D_us_801802D4),
    PAL_TERMINATE(),
};
u_long* cluts[] = {
    (u_long*)&pal_def_0,
    (u_long*)&pal_def_1,
    (u_long*)&pal_def_2,
};
