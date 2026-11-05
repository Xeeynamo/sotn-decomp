// SPDX-License-Identifier: AGPL-3.0-or-later
#ifndef SATZ_PROTOTYPES_H
#define SATZ_PROTOTYPES_H

char* func_06005E3C(s32, u16);
s32 func_0600607C(u16);
char num2char(u32);
s32 func_0606C088(u16);
u16 DealDamage(Entity*, Entity*);
u32 func_060727DC(s32, u16, u16);
u32* GetStageTextGlyphData(s32, u16);
u32* GetEventTextGlyphData(s32, s32);
Entity* AllocEntity(Entity*, Entity*);
u32 AnimateEntity(u8*, Entity*);
s16 CalcWaveOffset(s32, s32, s32);
u16 LocalLookupTblNoToVram(u16);
u16* func_0600CB04(s32, s32);
void MariaSetSubweaponParams(Entity*);
s32* func_060784A8();

#endif
