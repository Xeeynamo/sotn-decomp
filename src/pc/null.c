// something is off with the headers in this target
#include "../../include/common.h"
#include "../../include/psxsdk/libgpu.h"

extern bool g_TimedExit;
extern int g_TimeLimit;

bool InitPlatform() {
    g_TimedExit = true;
    g_TimeLimit = 60;
    return true;
}

void ResetPlatform() {}

void MyRenderPrimitives(void) {}

void MyPadInit(int mode) {}

u_long MyPadRead(int id) { return 0; }

int MyDrawSync(int mode) { return 0; }

DISPENV* MyPutDispEnv(DISPENV* env) { return NULL; }

void MySetDrawMode(DR_MODE* p, int dfe, int dtd, int tpage, RECT* tw) {}

int MyResetGraph(int arg0) { return 0; }

void MySsInitHot(void) {}

void MyDrawOTag(OT_TYPE* p) {}

int main(int argc, char* argv[]) {
    const char* filename;

    if (argc < 2) {
        filename = "disks/sotn.us.bin";
    } else {
        filename = argv[1];
    }
    OpenCd(filename);

    if (InitGame()) {
        MainGame();
    }
    ResetGame();
}
