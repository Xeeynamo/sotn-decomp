// SPDX-License-Identifier: MIT
#include "libcd_internal.h"
#include "common.h"

INCLUDE_ASM("main/nonmatchings/psxsdk/libcd/iso9660", CdSearchFile);

int _cmp(const char* str1, const char* str2) {
    return strncmp(str1, str2, 0xC) == 0;
}

INCLUDE_ASM("main/nonmatchings/psxsdk/libcd/iso9660", CD_newmedia);

INCLUDE_ASM("main/nonmatchings/psxsdk/libcd/iso9660", CD_searchdir);

INCLUDE_ASM("main/nonmatchings/psxsdk/libcd/iso9660", CD_cachefile);

int cd_read(int sectors, int arg1, u_long* buf) {
    CdlLOC p;

    CdIntToPos(arg1, &p);
    CdControl(CdlSetloc, &p, NULL);
    CdRead(sectors, buf, CdlModeSpeed | CdlModeSpeedNormal);
    return CdReadSync(CdlSync, NULL) == 0;
}

void cd_memcpy(char* dst, char* src, size_t size) {
    while (size--) {
        *dst++ = *src++;
    }
}
