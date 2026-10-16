// SPDX-License-Identifier: AGPL-3.0-or-later
#ifndef SATURN_ZERO_OVERLAY_H
#define SATURN_ZERO_OVERLAY_H

#include "sattypes.h"

typedef struct {
    void (*Init)(void);
} BatServantHeader;

extern BatServantHeader g_BatServantDesc;

extern s32 DAT_06064584;
extern s32 DAT_06064588;
extern s32 DAT_06064598;
extern s32 DAT_060645CC;
extern s32 DAT_060645DC;
extern s32 DAT_060645E4[];
extern s32 DAT_060645EC[];
extern s32 DAT_060645F0;
extern s32 DAT_060645F8[];
extern s32 DAT_0606460C;
extern s32* DAT_06064610;
extern s32 DAT_0606462C;
extern s32 DAT_06064668;
extern s32 DAT_06064678;
extern s32 DAT_0606467C;
extern s32 DAT_06064680;

extern s32 (*DAT_06066000)();
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

extern void (*DAT_060A5000)();
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

extern s32 DAT_060D4000;
extern s32 DAT_060D4004;
extern s32 DAT_060D4008;
extern s32 DAT_060D400C;
extern s32 DAT_060D4010;
extern s32 DAT_060D4014;
extern s32 DAT_060D4018;
extern s32 DAT_060D401C;
extern s32 DAT_060D4020;
extern s32 DAT_060D4024;
extern s32 DAT_060D4028;
extern s32 DAT_060D402C;
extern s32 DAT_060D4030;
extern s32 DAT_060D4034;
extern s32 DAT_060D4038;
extern s32 DAT_060D403C;
extern s32 DAT_060D4040;
extern s32 DAT_060D4044;
extern s32 DAT_060D4048;

extern s32 DAT_060D6000;
extern s32 DAT_060D6004;
extern s32 DAT_060D6008;
extern s32 DAT_060D600C;
extern s32 DAT_060D6010;
extern s32 DAT_060D6014;
extern s32 DAT_060D6018;
extern s32 DAT_060D601C;
extern s32 DAT_060D6020;
extern s32 DAT_060D6024;
extern s32 DAT_060D6028;
extern s32 DAT_060D602C;
extern s32 DAT_060D6030;
extern s32 DAT_060D6034;
extern s32 DAT_060D6038;
extern s32 DAT_060D603C;
extern s32 DAT_060D6040;
extern s32 DAT_060D6044;
extern s32 DAT_060D6048;
extern s32 DAT_060D9040;

typedef s32 (*OverlayHandler)(void);

#define PLAYER_SERVANT_HANDLERS ((OverlayHandler*)0x060D9000)
#define MARIA_SERVANT_HANDLERS ((OverlayHandler*)0x060D6000)

s32 func_0601AE9C(void);
s32 func_0601AEA8(void);

#endif
