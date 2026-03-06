// SPDX-License-Identifier: AGPL-3.0-or-later
#ifndef RNZ0_H
#define RNZ0_H

#include <stage.h>

#define OVL_EXPORT(x) RNZ0_##x
#define STAGE_FLAG OVL_EXPORT(STAGE_FLAG)

typedef enum EntityIDs {
} EntityIDs;

#endif // RNZ0_H