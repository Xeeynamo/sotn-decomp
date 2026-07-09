// SPDX-License-Identifier: AGPL-3.0-or-later
#include <stage.h>

#ifndef VERSION_PSP

// This is an unused image that says "Golem Maker". Likely stripped on PSP.
u8 unused_39BC[] = {
#include "gen/unused_39BC.h"
};

#endif

u8 D_801842A4[] = {
#include "gen/D_801842A4.h"
};

u8 D_80185430[] = {
#include "gen/D_80185430.h"
};

u8 D_80186510[] = {
#include "gen/D_80186510.h"
};

u8 D_801876B4[] = {
#include "gen/D_801876B4.h"
};

u8 D_8018879C[] = {
#include "gen/D_8018879C.h"
};

u8 D_801892FC[] = {
#include "gen/D_801892FC.h"
};

u8 D_80189D2C[] = {
#include "gen/D_80189D2C.h"
};

u8 D_8018AB14[] = {
#include "gen/D_8018AB14.h"
};

u8 D_8018B460[] = {
#include "gen/D_8018B460.h"
};

u8 D_8018BBD8[] = {
#include "gen/D_8018BBD8.h"
};

u8 D_8018C860[] = {
#include "gen/D_8018C860.h"
};

u8 D_8018D3EC[] = {
#include "gen/D_8018D3EC.h"
};

u8 D_8018E514[] = {
#include "gen/D_8018E514.h"
};

// Unused. Stripped on PSP. Ifdef here because on PSP the .h file doesn't exist
#ifndef VERSION_PSP
u16 e_skyswirl_p[] = {
#include "gen/e_skyswirl_p.h"
};
#endif

u16 pal_fire_warg[] = {
#include "gen/pal_fire_warg.h"
};
u16 pal_2e0[] = {
#include "gen/pal_2e0.h"
};
u16 pal_jacko_bones[] = {
#include "gen/pal_jacko_bones.h"
};
u16 pal_nova_skeleton[] = {
#include "gen/pal_nova_skeleton.h"
};
u16 pal_dragons[] = {
#include "gen/pal_dragons.h"
};

// Stripped on PSP
#if !defined(VERSION_PSP)
u16 pal_unused[] = {
#include "gen/pal_unused.h"
};
#endif
u16 pal_venus_weed[] = {
#include "gen/pal_venus_weed.h"
};
u16 pal_dodo[] = {
#include "gen/pal_dodo.h"
};
