// SPDX-License-Identifier: AGPL-3.0-or-later
#ifndef SATURN_ZERO_OVERLAY_H
#define SATURN_ZERO_OVERLAY_H

#include "sattypes.h"

typedef struct {
    void (*Init)(void);
} BatServantHeader;

extern BatServantHeader g_BatServantDesc;

extern s32 DAT_06064588;
extern s32 DAT_06064598;
extern s32 DAT_060645CC;
extern s32 DAT_060645DC;
extern s32 DAT_060645EC[];
extern s32 DAT_060645e4[];
extern s32 DAT_060645f8[];
extern s32 DAT_060645F0;
extern s32* DAT_06064610;
extern s32 DAT_0606462C;
extern s32 DAT_06064640;
extern s32 DAT_06064668;
extern s32 DAT_06064680;

extern void (*DAT_060A5004)();
extern void (*DAT_060A5008)();
extern void (*DAT_060A500C)();
extern void (*DAT_060A5010)();
extern void (*DAT_060A5014)(Collider*);
extern s32 DAT_060A5018;
extern void (*DAT_060A501C)(s32, s32);
extern void (*DAT_060A5020)();
extern void (*DAT_060A5024)(s32);
extern Entity* (*DAT_060A5028)(Entity*, u32, s32);
extern void (*DAT_060A502C)();
extern s32 DAT_060A5030;
extern void (*DAT_060A5034)();
extern void (*DAT_060A5038)();
extern s32 DAT_060A503C;
extern s32 DAT_060A5040;

extern s32 DAT_060D6040;
extern s32 DAT_060D9040;

typedef s32 (*OverlayHandler)(void);

#define PLAYER_SERVANT_HANDLERS ((OverlayHandler*)0x060D9000)
#define MARIA_SERVANT_HANDLERS ((OverlayHandler*)0x060D6000)

s32 func_0601AE9C(void);
s32 func_0601AEA8(void);

extern void (*DAT_06066004)();
extern s32 DAT_06066008;
extern s32 DAT_0606600C;
extern s32 DAT_06066010;
extern s32 DAT_06066014;
extern s32 DAT_06066018;
extern s32 DAT_0606601C;
extern s32 DAT_06066020;
extern s32 DAT_06066024;
extern s32 DAT_06066028;
extern s32 DAT_0606602C;

#endif
