// SPDX-License-Identifier: AGPL-3.0-or-later
#ifndef HAND_H
#define HAND_H
#include <types.h>

#if defined(WEAPON0)
#define HAND_ID 0
#elif defined(WEAPON1)
#define HAND_ID 1
#else
#warning "WEAPON0 or WEAPON1 not specified. Falling back to WEAPON0."
#define HAND_ID 0
#endif

s32 g_HandId = HAND_ID;
#endif // HAND_H
