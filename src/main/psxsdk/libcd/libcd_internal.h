#include <psxsdk/libcd.h>

extern CdlCB CD_cbready;
extern CdlCB CD_cbsync;
extern unsigned char CD_mode;
extern unsigned char CD_com;

int CD_sync(int mode, unsigned char* result);
int CD_ready(int mode, unsigned char* result);
int CD_flush(void);
void CD_initintr(void);
int CD_init(void);
int CD_initvol(void);
int CD_getsector(void* buffer, size_t size);
int CD_vol(CdlATV* vol);
