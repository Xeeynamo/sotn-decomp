// SPDX-License-Identifier: AGPL-3.0-or-later
#include "dra.h"
#include "dra_bss.h"

static s32 g_MemcardRetryCount;
static s32 g_MemcardFd;

#include "../save_mgr.h"
