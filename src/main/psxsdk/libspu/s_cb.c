// SPDX-License-Identifier: MIT
#include "common.h"
#include "libspu_internal.h"

void _SpuCallback(s32 arg0) { InterruptCallback(9, arg0); }
