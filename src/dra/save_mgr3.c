#include "dra.h"
#undef STAGE

#include "../save_mgr3.h"

#if defined(VERSION_HD)
void MakeMemcardPath(char* dstSaveName, s32 saveSlot) {
    STRCPY(dstSaveName, "BISLPM-86023DRAX00");
    dstSaveName[0x10] += saveSlot / 10;
    dstSaveName[0x11] += saveSlot % 10;
}
#elif defined(VERSION_US)
const char HACK_SaveName[] = {
    'B', 'A', 'S', 'L', 'U', 'S', '-', '0', '0',  '0',
    '6', '7', 'D', 'R', 'A', 'X', '0', '0', '\0', 'n',
};
void MakeMemcardPath(char* dstSaveName, s32 saveSlot) {
    __builtin_memcpy(dstSaveName, HACK_SaveName, sizeof(HACK_SaveName) - 1);
    dstSaveName[0x10] += saveSlot / 10;
    dstSaveName[0x11] += saveSlot % 10;
}
#endif
