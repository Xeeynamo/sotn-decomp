#include "common.h"

extern u16 *g_InterruptMask;

u16 GetIntrMask(void) { return *g_InterruptMask; }
