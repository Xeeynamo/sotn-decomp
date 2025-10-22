// SPDX-License-Identifier: AGPL-3.0-or-later
#include "dra.h"

static s32 g_MemcardPortMask[] = {-2, -3};
static s32 g_MemcardRetryCount;
static s32 g_MemcardFd;

u16 g_saveIconPal[] = {
#include "gen/g_saveIconPal.h"
};

static u8 g_saveIcon0[] = {
#include "gen/g_saveIcon0.h"
};

static u8 g_saveIcon1[] = {
#include "gen/g_saveIcon1.h"
};

static u8 g_saveIcon2[] = {
#include "gen/g_saveIcon2.h"
};

static u8 g_saveIcon3[] = {
#include "gen/g_saveIcon3.h"
};

static u8 g_saveIcon4[] = {
#include "gen/g_saveIcon4.h"
};

static u8 g_saveIcon5[] = {
#include "gen/g_saveIcon5.h"
};

static u8 g_saveIcon6[] = {
#include "gen/g_saveIcon6.h"
};

static u8 g_saveIcon7[] = {
#include "gen/g_saveIcon7.h"
};

static u8 g_saveIcon8[] = {
#include "gen/g_saveIcon8.h"
};

static u8 g_saveIcon9[] = {
#include "gen/g_saveIcon9.h"
};

static u8 g_saveIcon10[] = {
#include "gen/g_saveIcon10.h"
};

static u8 g_saveIcon11[] = {
#include "gen/g_saveIcon11.h"
};

static u8 g_saveIcon12[] = {
#include "gen/g_saveIcon12.h"
};

static u8 g_saveIcon13[] = {
#include "gen/g_saveIcon13.h"
};

static u8 g_saveIcon14[] = {
#include "gen/g_saveIcon14.h"
};

static u8 g_saveIcon15[] = {
#include "gen/g_saveIcon15.h"
};

#include "../save_mgr.h"
