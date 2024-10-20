// SPDX-License-Identifier: AGPL-3.0-or-later
#ifndef MEMCARD_H
#define MEMCARD_H

// save manager
// port: 0 or 1, it is the physical port where you plug the memory card.
// port_s: 0-3, valid only in the context of multi tap, unused in this game.
// channel: the numerical combination of port and port_s
// block: 0-14, a memory card can store up to 15 blocks

#include <game.h>
#include <psxsdk/kernel.h>
#include <psxsdk/libapi.h>

extern MemcardInfo g_MemcardInfo[2];
extern s32 g_MemcardBlockRead;
extern s32 g_MemcardPortMask[];
extern u16 g_saveIconPal0[0x10][0x10];
extern u8* g_saveIconTexture[0x10];

#endif
