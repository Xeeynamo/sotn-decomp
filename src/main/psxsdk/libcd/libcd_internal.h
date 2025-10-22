// SPDX-License-Identifier: MIT
#include <psxsdk/libcd.h>

int CD_sync(int mode, u_char* result);
int CD_ready(int mode, u_char* result);
int CD_flush(void);
void CD_initintr(void);
int CD_init(void);
int CD_initvol(void);
int CD_getsector(void* buffer, size_t size);
int CD_vol(CdlATV* vol);
