#include "common.h"

INCLUDE_ASM("main/nonmatchings/psxsdk/libcd/event", CdInit);

extern void DeliverEvent(unsigned long, unsigned long);

void def_cbsync(void) { DeliverEvent(0xF0000003, 0x20); }

void def_cbready(void) { DeliverEvent(0xF0000003, 0x40); }

void def_cbread(void) { DeliverEvent(0xF0000003, 0x40); }
