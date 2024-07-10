#ifndef CLUT_H
#define CLUT_H

#include "types.h"

extern u16 g_ClutIds[]; // array of palette VRAM offsets
extern u16 g_Clut[0x3000];
extern u16 D_8006EBCC[0x1000]; // part of g_Clut
extern u16 D_8006EBE0;         // part of g_Clut
extern s16 D_800705CC[];       // part of g_Clut
extern u32 D_80070BCC;         // part of g_Clut

#endif // CLUT_H
