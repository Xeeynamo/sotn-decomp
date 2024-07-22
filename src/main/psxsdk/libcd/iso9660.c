#include "common.h"

INCLUDE_ASM("main/nonmatchings/psxsdk/libcd/iso9660", CdSearchFile);

s32 strncmp(const char* str1, const char* str2, size_t num);

s32 _cmp(const char* str1, const char* str2) {
    return strncmp(str1, str2, 0xC) == 0;
}

INCLUDE_ASM("main/nonmatchings/psxsdk/libcd/iso9660", CD_newmedia);

INCLUDE_ASM("main/nonmatchings/psxsdk/libcd/iso9660", CD_searchdir);

INCLUDE_ASM("main/nonmatchings/psxsdk/libcd/iso9660", CD_cachefile);

INCLUDE_ASM("main/nonmatchings/psxsdk/libcd/iso9660", cd_read);

void cd_memcpy(unsigned char* dst, unsigned char* src, int size) {
    int i;

    for (i = size - 1; i != -1; i--) {
        *dst++ = *src++;
    }
}
