// SPDX-License-Identifier: AGPL-3.0-or-later
#include "nz1.h"

extern u16 D_us_80192DD8[];
extern u16 D_us_80193098[];
extern u16 D_us_80193158[];
extern u16 D_us_801931D8[];
extern u16 D_us_80193278[];
extern u16 D_us_80193498[];
extern u16 D_us_801934F8[];
extern u16 D_us_80193558[];
extern u16 D_us_801935D8[];
extern u16 D_us_801936D8[];
extern u16 D_us_80193798[];

static u_long* pal_def_0[] = {
    MAKE_PAL_OP(PAL_BULK_COPY, 0),
    PAL_BULK_(0x2000, D_us_80193098, 0x60),
    PAL_BULK_(0x2060, D_us_80193158, 0x40),
    PAL_BULK_(0x20A0, D_us_801931D8, 0x50),
    PAL_BULK_(0x20F0, D_us_80193278, 0x110),
    PAL_BULK_(0x2200, D_us_80193498, 0x30),
    PAL_BULK_(0x2230, D_us_801934F8, 0x30),
    PAL_BULK_(0x2260, D_us_80193558, 0x40),
    PAL_BULK_(0x22A0, D_us_801935D8, 0x80),
    PAL_BULK_(0x2320, D_us_801936D8, 0x60),
    PAL_BULK_(0x2380, D_us_80193798, 0x20),
    PAL_BULK_(0x2E00, D_us_80192DD8, 0x100),
    PAL_TERMINATE(),
};
u16 D_us_8018012C[] = {
#include "gen/D_us_8018012C.h"
};
u16 D_us_8018014C[] = {
#include "gen/D_us_8018014C.h"
};
u16 D_us_8018016C[] = {
#include "gen/D_us_8018016C.h"
};
u16 D_us_8018018C[] = {
#include "gen/D_us_8018018C.h"
};
u16 D_us_801801AC[] = {
#include "gen/D_us_801801AC.h"
};
u16 D_us_801801CC[] = {
#include "gen/D_us_801801CC.h"
};
u16 D_us_801801EC[] = {
#include "gen/D_us_801801EC.h"
};
u16 D_us_8018020C[] = {
#include "gen/D_us_8018020C.h"
};
u16 D_us_8018022C[] = {
#include "gen/D_us_8018022C.h"
};
u16 D_us_8018024C[] = {
#include "gen/D_us_8018024C.h"
};
u16 D_us_8018026C[] = {
#include "gen/D_us_8018026C.h"
};
u16 D_us_8018028C[] = {
#include "gen/D_us_8018028C.h"
};
u16 D_us_801802AC[] = {
#include "gen/D_us_801802AC.h"
};
u16 D_us_801802CC[] = {
#include "gen/D_us_801802CC.h"
};
u16 D_us_801802EC[] = {
#include "gen/D_us_801802EC.h"
};
static u_long* pal_def_1[] = {
    MAKE_PAL_OP(PAL_UNK_OP3, 1),
    (u_long*)0x00B0, // scrapped MAKE_PAL params?
    (u_long*)0x10,   // scrapped MAKE_PAL params?
    (u_long*)(D_us_8018012C),
    (u_long*)(D_us_8018014C),
    (u_long*)(D_us_8018016C),
    (u_long*)(D_us_8018018C),
    (u_long*)(D_us_801801AC),
    (u_long*)(D_us_801801CC),
    (u_long*)(D_us_801801EC),
    (u_long*)(D_us_8018020C),
    (u_long*)(D_us_8018022C),
    (u_long*)(D_us_8018024C),
    (u_long*)(D_us_8018026C),
    (u_long*)(D_us_8018028C),
    (u_long*)(D_us_801802AC),
    (u_long*)(D_us_801802CC),
    (u_long*)(D_us_801802EC),
    PAL_TERMINATE(),
};
u_long* cluts[] = {
    (u_long*)&pal_def_0,
    (u_long*)&pal_def_1,
};
