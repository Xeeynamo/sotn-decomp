#ifndef LIBAPI_INTERNAL_H
#define LIBAPI_INTERNAL_H

#include <types.h>

void ResetEntryInt();
void HookEntryInt(u16*);
long long startIntrDMA();
void* startIntrVSync();
void ReturnFromException();
void ChangeClearRCnt(s32, s32);

#endif
