#include "dra.h"
#include "../save_mgr.h"

#if defined(VERSION_HD)
void MakeMemcardPath(char* dstSaveName, s32 block) {
    STRCPY(dstSaveName, "BISLPM-86023DRAX00");
    dstSaveName[0x10] += block / 10;
    dstSaveName[0x11] += block % 10;
}
#elif defined(VERSION_US)
// The US version has an extra 'n' character after the string terminator,
// probably a result of some left-overs from a previous build. Defining the
// string `SaveName` as an array to manually append 'n' at the end was the only
// way to get a match.
const char HACK_SaveName[] = {
    'B', 'A', 'S', 'L', 'U', 'S', '-', '0', '0',  '0',
    '6', '7', 'D', 'R', 'A', 'X', '0', '0', '\0', 'n',
};
void MakeMemcardPath(char* dstSaveName, s32 block) {
    __builtin_memcpy(dstSaveName, HACK_SaveName, sizeof(HACK_SaveName) - 1);
    dstSaveName[0x10] += block / 10;
    dstSaveName[0x11] += block % 10;
}
#endif
