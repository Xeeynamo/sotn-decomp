// SPDX-License-Identifier: AGPL-3.0-or-later
#ifndef LBA_H
#define LBA_H

#if defined(VERSION_EU)
#include "lba_eu.h"

#elif defined(VERSION_HK)
#include "lba_hk.h"

#elif defined(VERSION_US) || defined(VERSION_EU) || defined(VERSION_HK)
#include "lba_us.h"

#elif defined(VERSION_USPROTO)
#include "lba_usproto.h"

#elif defined(VERSION_JP12)
#include "lba_jp12.h"

#elif defined(VERSION_JP11)
#include "lba_jp11.h"

#elif defined(VERSION_HD) || defined(VERSION_JP10) || defined(VERSION_PSP)
#include "lba_jp10.h"

#endif

#endif
