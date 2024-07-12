#ifndef CASTLE_H
#define CASTLE_H

#include <common.h>
#include <types.h>

#define CASTLE_MAP_PTR 0x801E0000

// Holds flags that checks if certain switches are enabled to allow to have
// shortcuts around the castle. One typical example is the wood column that
// prevents the player to enter in the warp room. When g_CastleFlags[0x32] the
// column will disappear.
extern u8 g_CastleFlags[0x300]; // starts at 0x8003BDEC
extern u8 D_8003BEEC[];         // g_CastleFlags[x + 0x100]
extern u8 D_8003BF9C[];         // not sure if it is part of D_8003BEEC?

extern u8 g_CastleMap[0x800];

#ifdef VERSION_PC
extern u8 g_BmpCastleMap[0x20000];
#endif

#endif // CASTLE_H
