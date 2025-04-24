// SPDX-License-Identifier: AGPL-3.0-or-later
/*
 * File: ut_blit_char.c
 * Overlay: CHI
 * Description: UTILITIY - Blit text character
 */
#include "chi.h"

#ifdef VERSION_PSP
#include "../blit_char_psp.h"
#else
// func_801A3CA8: BlitChar
#include "../blit_char.h"
#endif
