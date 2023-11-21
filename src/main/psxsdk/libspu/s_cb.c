#include "common.h"

void InterruptCallback(s32, s32);

void _SpuCallback(s32 arg0) { InterruptCallback(9, arg0); }
