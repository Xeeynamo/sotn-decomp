// SPDX-License-Identifier: AGPL-3.0-or-later
#ifndef RBO3_H
#define RBO3_H

#include <stage.h>

#define OVL_EXPORT(x) RBO3_##x

typedef enum {
    /* 0x00 */ E_NONE,
    /* 0x01 */ E_BREAKABLE,
    /* 0x02 */ E_EXPLOSION,
} EntityIDs;

#endif // RBO3_H
