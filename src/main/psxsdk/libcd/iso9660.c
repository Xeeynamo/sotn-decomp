// SPDX-License-Identifier: MIT
#include "libcd_internal.h"
#include "common.h"

typedef union {
    s32 addr;
    struct {
        u8 unk0;
        u8 unk1;
        u8 unk2;
        u8 unk3;
    } i;
} LBA;

typedef struct {
    s32 unk0;
    s32 unk4;
    LBA unk8;
    char unkC[0x20];
} CdlDIR;

static CdlFILE file[CdlMAXFILE];
static CdlDIR D_80039884[CdlMAXDIR];
static u8 load_buf[0x800];

extern int CD_nopen;
extern int D_80032AB0;

static int D_80032DB0 = 0;
static int D_80032DB4 = -1;

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

s32 CD_newmedia(void) {
    LBA pathTableLBA;
    u8* pathTablePtr;
    s32 i;

    if (cd_read(1, 0x10, load_buf) != 1) {
        if (D_80032AB0 > 0) {
            printf("CD_newmedia: Read error in cd_read(PVD)\n");
        }
        return 0;
    }
    if (strncmp(&load_buf[1], "CD001", 5) != 0) {
        if (D_80032AB0 > 0) {
            printf("CD_newmedia: Disc format error in cd_read(PVD)\n");
        }
        return 0;
    }

    (&pathTableLBA)->i = ((LBA*)(&load_buf[0x8C]))->i;
    if (cd_read(1, pathTableLBA.addr, load_buf) != 1) {
        if (D_80032AB0 > 0) {
            printf("CD_newmedia: Read error (PT:%08x)\n", pathTableLBA.addr);
        }
        return 0;
    }
    if (D_80032AB0 > 1) {
        printf("CD_newmedia: sarching dir..\n");
    }
    do {
        i = 0;
        pathTablePtr = load_buf;
        while (pathTablePtr < load_buf + 0x800) {
            if (pathTablePtr[0] == 0) {
                break;
            }
            D_80039884[i].unk8.i = ((LBA*)(&pathTablePtr[2]))->i;
            D_80039884[i].unk4 = pathTablePtr[6];
            D_80039884[i].unk0 = i + 1;

            cd_memcpy(D_80039884[i].unkC, &pathTablePtr[8], pathTablePtr[0]);
            D_80039884[i].unkC[pathTablePtr[0]] = '\0';
            pathTablePtr += 8 + pathTablePtr[0] + pathTablePtr[0] % 2;
            if (D_80032AB0 > 1) {
                printf("\t%08x,%04x,%04x,%s\n", D_80039884[i].unk8.addr,
                       D_80039884[i].unk0, D_80039884[i].unk4,
                       D_80039884[i].unkC);
            }
            if (++i >= CdlMAXDIR) {
                break;
            }
        }
        if (i < CdlMAXDIR) {
            D_80039884[i].unk4 = 0;
        }
    } while (0);

    D_80032DB0 = 0;
    if (D_80032AB0 > 1) {
        printf("CD_newmedia: %d dir entries found\n", i);
    }
    return 1;
}

s32 CD_searchdir(s32 arg0, char* arg1) {
    s32 i;

    for (i = 0; i < CdlMAXDIR; i++) {
        if (D_80039884[i].unk4 == 0) {
            return -1;
        }
        if (D_80039884[i].unk4 != arg0) {
            continue;
        }
        if (strcmp(arg1, D_80039884[i].unkC) == 0) {
            return i + 1;
        }
    }
    return -1;
}

s32 CD_cachefile(s32 arg0) {
    LBA sp18;
    u8* ptr;
    s32 i;
    short* namePtr;

    if (arg0 == D_80032DB0) {
        return 1;
    }

    if (cd_read(1, (D_80039884 - 1)[arg0].unk8.addr, load_buf) != 1) {
        if (D_80032AB0 > 0) {
            printf("CD_cachefile: dir not found\n");
        }
        return -1;
    }
    if (D_80032AB0 > 1) {
        printf("CD_cachefile: searching...\n");
    }
    i = 0;
    ptr = load_buf;
    while (ptr < load_buf + 0x800) {
        if (ptr[0] == 0) {
            break;
        }
        sp18.i = ((LBA*)&ptr[2])->i;
        CdIntToPos(sp18.addr, &file[i].pos);
        ((LBA*)&file[i].size)->i = ((LBA*)&ptr[0xA])->i;
        switch (i) {
        case 0:
            namePtr = file[i].name;
            strcpy(namePtr, ".");
            break;
        case 1:
            namePtr = file[i].name;
            strcpy(namePtr, "..");
            break;
        default:
            cd_memcpy(file[i].name, &ptr[0x21], ptr[0x20]);
            file[i].name[ptr[0x20]] = '\0';
            break;
        }
        if (D_80032AB0 > 1) {
            printf("\t(%02x:%02x:%02x) %8d %s\n", file[i].pos.minute,
                   file[i].pos.second, file[i].pos.sector, file[i].size,
                   file[i].name);
        }
        ptr += ptr[0];
        if (++i >= CdlMAXFILE) {
            break;
        }
    }
    D_80032DB0 = arg0;
    if (i < CdlMAXFILE) {
        file[i].name[0] = '\0';
    }
    if (D_80032AB0 > 1) {
        printf("CD_cachefile: %d files found\n", i);
    }
    return 1;
}

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
