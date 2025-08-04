// SPDX-License-Identifier: AGPL-3.0-or-later
#ifndef RTOP_H
#define RTOP_H

#include <stage.h>

#define OVL_EXPORT(x) RTOP_##x
#define STAGE_FLAG OVL_EXPORT(STAGE_FLAG)

typedef enum EntityIDs {
    /* 0x00 */ E_NONE,
} EntityIDs;

#endif // RTOP_H
