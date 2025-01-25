#ifndef LIBAPI_INTERNAL_H
#define LIBAPI_INTERNAL_H

#include <types.h>

#define JB_PC 0
#define JB_SP 1
#define JB_FP 2
#define JB_S0 3
#define JB_S1 4
#define JB_S2 5
#define JB_S3 6
#define JB_S4 7
#define JB_S5 8
#define JB_S6 9
#define JB_S7 10
#define JB_GP 11
#define JB_SIZE 12

typedef int jmp_buf[JB_SIZE];

s32 setjmp(jmp_buf*);
void ResetEntryInt();
void HookEntryInt(jmp_buf*);
long long startIntrDMA();
void* startIntrVSync();
void ReturnFromException();
void ChangeClearRCnt(s32, s32);

#endif
