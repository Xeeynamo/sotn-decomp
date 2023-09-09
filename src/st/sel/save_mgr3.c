#include "sel.h"
#include "../../save_mgr3.h"

void MakeMemcardPath(char* dstSaveName, s32 saveSlot) {
    STRCPY(dstSaveName, "BASLUS-00067DRAX00");
    dstSaveName[0x10] += saveSlot / 10;
    dstSaveName[0x11] += saveSlot % 10;
}
