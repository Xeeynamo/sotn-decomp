#include "sel.h"
#include "../../save_mgr2.h"

void MakeMemcardPath(char* dstSaveName, s32 block) {
    STRCPY(dstSaveName, "BASLUS-00067DRAX00");
    dstSaveName[0x10] += block / 10;
    dstSaveName[0x11] += block % 10;
}
