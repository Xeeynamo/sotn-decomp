// SPDX-License-Identifier: AGPL-3.0-or-later
#ifndef LBA_H
#define LBA_H

#ifdef VERSION_US
#include "lba_us.h"

#elif defined(VERSION_HD) || defined(VERSION_PSP)
#include "lba_hd.h"

#endif

#endif
