// SPDX-License-Identifier: MIT
#include "libcd_internal.h"
#include "common.h"

extern int CD_nopen;
extern int D_80032AB0;
extern int D_80032DB4;
extern CdlFILE file[CdlMAXFILE];

CdlFILE* CdSearchFile(CdlFILE* fp, char* name) {
    char buf[32];
    int var_a0;
    int i;
    char* namePtr;
    char* bufPtr;

    if (D_80032DB4 != CD_nopen) {
        if (CD_newmedia() == 0) {
            return NULL;
        }
        D_80032DB4 = CD_nopen;
    }
    var_a0 = 1;
    if (name[0] != '\\') {
        return NULL;
    }
    buf[0] = 0;
    namePtr = name;
    for (i = 0; i < CdlMAXLEVEL; i++) {
        bufPtr = &buf;
        while (*namePtr != '\\') {
            if (*namePtr == 0) {
                goto out;
            }
            *bufPtr++ = *namePtr++;
        }
        if (*namePtr == 0) {
            goto out;
        }
        namePtr++;
        *bufPtr = 0;
        var_a0 = CD_searchdir(var_a0, buf);
        if (var_a0 == -1) {
            buf[0] = 0;
            break;
        }
    }
out:
    if (i >= CdlMAXLEVEL) {
        if (D_80032AB0 > 0) {
            printf("%s: path level (%d) error\n", name, i);
        }
        return NULL;
    }
    if (buf[0] == 0) {
        if (D_80032AB0 > 0) {
            printf("%s: dir was not found\n", name);
        }
        return NULL;
    }
    *bufPtr = 0;
    if (CD_cachefile(var_a0) == 0) {
        if (D_80032AB0 > 0) {
            printf("CdSearchFile: disc error\n");
        }
        return NULL;
    }
    if (D_80032AB0 > 1) {
        printf("CdSearchFile: searching %s...\n", buf);
    }
    for (i = 0; i < CdlMAXFILE; i++) {
        if (file[i].name[0] == 0) {
            break;
        }
        if (_cmp(file[i].name, buf)) {
            if (D_80032AB0 > 1) {
                printf("%s:  found\n", buf);
            }
            *fp = file[i];
            return &file[i];
        }
    }
    if (D_80032AB0 > 0) {
        printf("%s: not found\n", buf);
    }
    return NULL;
}

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
