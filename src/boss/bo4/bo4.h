// SPDX-License-Identifier: AGPL-3.0-or-later
#ifndef BO4_H
#define BO4_H

#include <stage.h>

#define OVL_EXPORT(x) BO4_##x

#include "../doppleganger.h"

#ifdef VERSION_PSP
extern s32 D_pspeu_0926BCC8;
extern s32 D_pspeu_0926BCB8;
extern s32 D_pspeu_0926BCB0;
extern s32 D_pspeu_0926BCA0;
extern s32 D_pspeu_0926BCA8;
extern s32 D_pspeu_0926BC98;
extern s32 D_pspeu_0926BCD0;
#define E_ID(ID_16) D_pspeu_0926BCD0
#define E_ID(ID_17) D_pspeu_0926BCC8
#define E_ID(ID_19) D_pspeu_0926BCB8
#define E_ID(ID_1A) D_pspeu_0926BCB0
#define E_ID(ID_1B) D_pspeu_0926BCA8
#define E_ID(ID_1C) D_pspeu_0926BCA0
#define E_ID(ID_1D) D_pspeu_0926BC98
#endif

extern EInit g_EInitParticle;
extern EInit g_EInitLockCamera;

#endif // BO4_H
