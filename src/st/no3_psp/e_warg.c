// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../no3/no3.h"

//func_801CF58C
static void func_pspeu_09252C78(Entity* self) {
    self->velocityX = 0;
    self->ext.warg.unk86 = 0x100;
    SetStep(6);
    g_api.PlaySfx(SFX_WARG_GROWL);
    self->ext.warg.unk80 = 0x20;
}

INCLUDE_ASM("st/no3_psp/psp/no3_psp/e_warg", func_pspeu_09252CD8);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/e_warg", func_pspeu_09252E60);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/e_warg", EntityWarg);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/e_warg", EntityUnkId4B);

// clumsy thing, linter splits the line which breaks INCLUDE_ASM
// clang-format off
INCLUDE_ASM("st/no3_psp/psp/no3_psp/e_warg", EntityWargExplosionPuffTransparent);
// clang-format on
