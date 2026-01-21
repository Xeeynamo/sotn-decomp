// SPDX-License-Identifier: AGPL-3.0-or-later
#include <game_psp.h>

// https://pspdev.github.io/pspsdk/
#define PSP_LEGACY_TYPES_DEFINED // avoid processing psptypes.h

typedef struct {
    s8 unk0[0xF][0x15];
    u8 unk1[0xF][0x2000];
    s32 unk2;
    u8 unk3[0x2000];
} Unk08B21DEC;

extern s32 D_psp_089464E8;
extern Unk08B21DEC* D_psp_08B21DE8;
extern Unk08B21DEC D_psp_08B21DEC;
extern Unk08B21DEC* D_psp_08B41F2C;
extern s32 D_psp_08C62A3C;
extern u8 D_psp_08DED03C[0x20AD0];

void func_psp_089190A0(Unk08B21DEC* arg0, s32 len) {
    memmove(arg0, D_psp_08B21DE8, len);
    (u8*)D_psp_08B21DE8 += len;
}

void func_psp_089190F0(Unk08B21DEC* arg0, s32 len) {
    memmove(D_psp_08B21DE8, arg0, len);
    (u8*)D_psp_08B21DE8 += len;
}

void func_psp_08919140(void) {
    memset(&D_psp_08B21DEC, 0, sizeof(Unk08B21DEC));
    D_psp_08B21DEC.unk2 = -2;
    func_psp_08919570();
}

s32 func_psp_08919188(char* name) {
    s32 i;

    for (i = 0; i < 0xF; i++) {
        if (strcmp(name, D_psp_08B21DEC.unk0[i]) == 0) {
            return i;
        }
    }
    return -1;
}

s32 func_psp_08919208(void) {
    s32 i;

    for (i = 0; i < 0xF; i++) {
        if (D_psp_08B21DEC.unk0[i][0] == 0) {
            return i;
        }
    }
    return -1;
}

s32 func_psp_08919278(void) {
    s32 i;
    s32 var_s1;

    var_s1 = 0;
    for (i = 0; i < 0xF; i++) {
        if (D_psp_08B21DEC.unk0[i][0] == 0) {
            var_s1++;
        }
    }
    return var_s1;
}

s32 func_psp_089192EC(char* name, s32 arg1) {
    s32 temp_v0;

    temp_v0 = func_psp_08919188(name);
    if (temp_v0 == -1) {
        return -1;
    }
    D_psp_08B21DEC.unk0[temp_v0][0] = 0;
    memset(D_psp_08B21DEC.unk1[temp_v0], 0, 0x2000);
    if (arg1 && (temp_v0 == func_psp_08919560())) {
        func_psp_08919570();
    }
    if (func_psp_08919770(3) == 0) {
        func_psp_08919770(4);
        return -1;
    }
    return 0;
}

s32 func_psp_089193D4(u8* data, char* name, u32 len, s32 arg3) {
    s32 var_s0;

    var_s0 = func_psp_08919188(name);
    if (var_s0 == -1) {
        var_s0 = func_psp_08919208();
        if (var_s0 == -1) {
            return -1;
        }
    }
    strcpy(D_psp_08B21DEC.unk0[var_s0], name);
    memcpy(D_psp_08B21DEC.unk1[var_s0], data, (s32)len);
    if (arg3 && func_psp_08919560() >= 0) {
        func_psp_08919570();
    }
    if (func_psp_08919770(3) == 0) {
        func_psp_08919770(4);
        return -1;
    }
    return len;
}

s32 func_psp_089194E4(u8* data, char* name, u32 len) {
    s32 temp_v0;

    temp_v0 = func_psp_08919188(name);
    if (temp_v0 == -1) {
        return -1;
    }
    memcpy(data, D_psp_08B21DEC.unk1[temp_v0], (s32)len);
    return len;
}

s32 func_psp_08919560(void) { return D_psp_08B21DEC.unk2; }

s32 func_psp_08919570(void) {
    s32 temp_s0;

    temp_s0 = D_psp_08B21DEC.unk2;
    D_psp_08B21DEC.unk2 = -2;
    return temp_s0;
}

void func_psp_089195A0(s32 arg0) { D_psp_08B21DEC.unk2 = arg0; }

s32 func_psp_089195C0(u8* data, u32 len, s32 arg2) {
    D_psp_08B21DEC.unk2 = arg2;
    memcpy(D_psp_08B21DEC.unk3, data, (s32)len);
    if (func_psp_08919770(3) == 0) {
        func_psp_08919770(4);
        return -1;
    }
    return len;
}

s32 func_psp_08919638(u8* data, u32 len) {
    memcpy(data, D_psp_08B21DEC.unk3, (s32)len);
    return len;
}

void func_psp_08919674(void) {
    func_psp_089190F0(&D_psp_08B21DEC, sizeof(Unk08B21DEC));
}

s32 func_psp_089196A4(void) {
    func_psp_089190A0(&D_psp_08B21DEC, sizeof(Unk08B21DEC));
    return 1;
}

s32 func_psp_089196D8(s32 arg0, s32 arg1) {

    s32 ret = 0;

    D_psp_08B41F2C = (Unk08B21DEC*)&D_psp_08DED03C[0x990];

    switch (arg0) {
    case 3:
        ret = func_psp_0891985C(arg1);
        break;
    case 4:
        ret = func_psp_08919928(arg1);
        break;
    default:
        ret = -1;
    }
    return ret;
}

s32 func_psp_08919770(s32 arg0) { return func_psp_089196D8(arg0, 1); }

void func_psp_0891979C(s32 arg0) { func_psp_089196D8(arg0, 0); }

void func_psp_089197C8(s32 arg0) {
    if (arg0 != 0) {
        D_psp_089464E8 = 2;
    } else {
        D_psp_089464E8 = 0;
        D_psp_08C62A3C = 2;
    }
    DrawSync(0);
    VSync(0);
    EndFrame();
    func_psp_0891FC64();
    DrawSync(0);
    func_psp_0893116C();
    func_psp_08930A1C();
}

s32 func_psp_0891985C(s32 arg0) {
    s32 var_s0;

    memset(D_psp_08B41F2C, 0, sizeof(Unk08B21DEC));
    D_psp_08B21DE8 = D_psp_08B41F2C;
    func_psp_08919674();
    func_psp_08931D3C();
    func_psp_0893116C();
    func_psp_08930A1C();
    var_s0 = 0;
    while (var_s0 == 0) {
        PadReadPSP();
        var_s0 = func_psp_08931D64();
        func_psp_089197C8(arg0);
    }
    return (var_s0 == 1) ? 1 : 0;
}

s32 func_psp_08919928(s32 arg0) {
    s32 var_s0;

    func_psp_08930AE4(1);
    func_psp_0893116C();
    func_psp_08930A1C();
    var_s0 = 0;
    while (var_s0 == 0) {
        PadReadPSP();
        var_s0 = func_psp_08930B34();
        func_psp_089197C8(arg0);
    }
    if (var_s0 == 1) {
        D_psp_08B21DE8 = D_psp_08B41F2C;
        if (func_psp_089196A4() == 0) {
            return 0;
        }
    }

    return (var_s0 == 1) ? 1 : 0;
}
