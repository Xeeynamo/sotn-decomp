// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rbo4.h"

#ifdef VERSION_PC
s32 D_us_801807EC;
void func_us_80192B38_from_rbo3(Entity* self) { NOT_IMPLEMENTED; }
#else
INCLUDE_ASM("boss/rbo4/nonmatchings/unk_1879C", func_us_80192B38_from_rbo3);
#endif
