#include <common.h>
#include <psxsdk/libetc.h>
#include <log.h>

void MyPadInit(int mode);
void PadInit(int mode) { MyPadInit(mode); }

u_long MyPadRead(int id);
u_long PadRead(int id) { return MyPadRead(id); }

int MyVSyncCallback(void (*f)());
int VSyncCallback(void (*f)()) { return MyVSyncCallback(f); }

int VSyncCallbacks(int ch, void (*f)()) { NOT_IMPLEMENTED; }

long SetVideoMode(long mode) { NOT_IMPLEMENTED; }
