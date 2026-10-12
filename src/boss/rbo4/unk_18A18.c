// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rbo4.h"

#ifdef VERSION_PC
void func_us_80198A18(Entity* self) { NOT_IMPLEMENTED; }
#else
INCLUDE_ASM("boss/rbo4/nonmatchings/unk_18A18", func_us_80198A18);
#endif
