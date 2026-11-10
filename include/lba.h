// SPDX-License-Identifier: AGPL-3.0-or-later
#ifndef LBA_H
#define LBA_H
#include "version.h"

#if REGION == REGION_EU
#include "lba_eu.h"

#elif REGION == REGION_HK
#include "lba_hk.h"

#elif VERSION == VER_US
#include "lba_us.h"

#elif VERSION == VER_USPROTO
#include "lba_usproto.h"

#elif VERSION == VER_JP12
#include "lba_jp12.h"

#elif VERSION == VER_JP11
#include "lba_jp11.h"

#elif VERSION < VER_JP10
#include "lba_hd.h"

#elif VERSION == VER_JP10 || TARGET == TARGET_PSP
#include "lba_jp10.h"

#endif

#endif
