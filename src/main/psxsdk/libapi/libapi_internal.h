#ifndef LIBAPI_INTERNAL_H
#define LIBAPI_INTERNAL_H

#include <types.h>

void ResetEntryInt(s32*);
void HookEntryInt(u16*);
long long startIntrDMA();
s32 startIntrVSync();

#endif
