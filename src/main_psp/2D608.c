// SPDX-License-Identifier: AGPL-3.0-or-later
//! PSPO=4,p
#include <game_psp.h>

typedef struct Unk08919D98 Unk08919D98;

typedef struct Unk08919D98 {
    s32* unk0;
    Unk08919D98* prev;
    Unk08919D98* next;
    s32 (*unkC)(Unk08919D98*);
    s32 count;
} Unk08919D98;

typedef struct {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    s32 unkC;
    s32 unk10;
    s32 unk14;
    s32 unk18;
    s32 unk1C;
    s32 unk20;
} unkStruct3;

typedef struct unkStruct unkStruct;

typedef struct unkStruct {
    s32 unk0;
    unkStruct* prev;
    unkStruct* next;
    s32 unkC;
    unkStruct3* unk10;
    s32 unk14;
} unkStruct;

typedef struct {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    s32 unkC;
    unkStruct unk10[0x18];
    s32 : 32;
    unkStruct* unk254;
    unkStruct* unk258;
    s32 unk25C;
    s32 unk260;
    s32 : 32;
    unkStruct* unk268;
    unkStruct* unk26C;
    s32 unk270;
    s32 unk274;
    float unk278;
} unkStruct2;

extern s32 D_psp_089632C8;
extern char D_psp_089632CC[];
extern char D_psp_08963300[];
extern s32 D_psp_089AD784[];
extern s32 D_psp_089AD790[];
extern s32 D_psp_089AD79C[];
extern char* D_psp_08B42060;
extern unkStruct2 D_psp_08DADCC4;
extern u8 D_psp_08DADF80[][0x400];
extern s32 D_psp_08DAE780;
extern s32 D_psp_08DAE784;
extern s32 D_psp_08DAE788;
extern s32 D_psp_08DAE78C;
extern s32 D_psp_08DAE7A0;
extern char D_psp_089632D8[];

void func_psp_0892BFD8(unkStruct2*);
void func_psp_0892C174(unkStruct2*, unkStruct*);
void func_psp_0892C4F8(unkStruct2*, s32);
void func_psp_0892C3D4(unkStruct2*, s32);
void func_psp_0892CAD8(void);
void func_psp_0892CB10(void);
void func_psp_0892CB1C(void);
void func_psp_0892CB30(void);
void func_psp_0892C168(void);
s32 func_psp_0892CB40(void);

void func_psp_0892BF14(unkStruct2* arg0) {
    func_psp_08917328();
    func_psp_089172E4();
    func_psp_0892BFD8(arg0);
}

void func_psp_0892BF48(unkStruct2* arg0) {
    s32 temp_s0;
    s32 temp_v0;
    s32 i;

    temp_v0 = func_psp_08916F14();
    if (temp_v0 == arg0->unkC) {
        return;
    }
    temp_s0 = temp_v0 & ~arg0->unkC;
    if (temp_s0 != 0) {
        arg0->unkC = temp_v0;
        for (i = 0; i < 0x18U; i++) {
            if (temp_s0 & (1 << i)) {
                func_psp_0892C3D4(arg0, i);
            }
        }
    } else {
        arg0->unkC = temp_v0;
    }
}

void func_psp_0892BFD0(unkStruct2* arg0) { func_psp_0892C168(); }

void func_psp_0892BFD8(unkStruct2* arg0) {
    s32 i;

    func_psp_0892C4F8(arg0, 0x1000);
    arg0->unk0 = 0;
    arg0->unk4 = 0;
    func_psp_089171CC(-1);
    func_psp_08917250(0, 0);
    func_psp_08917138(arg0->unk0, arg0->unk4);
    func_psp_089170A4(1, 1);
    arg0->unk254 = NULL;
    arg0->unk258 = NULL;
    arg0->unk25C = 0;
    arg0->unk260 = 0;
    arg0->unk268 = NULL;
    arg0->unk26C = NULL;
    arg0->unk270 = 0;
    arg0->unk274 = 0;
    arg0->unk8 = 0;
    arg0->unkC = -1;
    arg0->unk278 = 1;
    for (i = 0; i < 0x18U; i++) {
        func_psp_08916EC0(i, 0, 0);
        func_psp_08916C40(i, 0x1000, 0x1000, arg0->unk0, arg0->unk4);
        func_psp_0892C174(arg0, &arg0->unk10[i]);
        if (arg0->unk26C != NULL) {
            arg0->unk10[i].next = NULL;
            arg0->unk10[i].prev = arg0->unk26C;
            arg0->unk26C->next = &arg0->unk10[i];
            arg0->unk26C = &arg0->unk10[i];
        } else {
            arg0->unk10[i].next = NULL;
            arg0->unk10[i].prev = NULL;
            arg0->unk268 = &arg0->unk10[i];
            arg0->unk26C = &arg0->unk10[i];
        }
        arg0->unk274++;
    }
    sceWaveAudioSetSample(0, 0x100);
    func_psp_0892CAD8();
    D_psp_08DAE784 = 1;
    D_psp_089632C8 = sceKernelCreateThread(
        D_psp_089632CC, func_psp_0892CB40, 0x10, 0x1000, 0, 0);
    sceKernelStartThread(D_psp_089632C8, 0, 0);
}

void func_psp_0892C168(void) {
    D_psp_08DAE784 = 0;
    func_psp_0892CB10();
}

void func_psp_0892C174(unkStruct2* arg0, unkStruct* arg1) {
    arg1->unkC = -1;
    arg1->unk10 = 0;
    arg1->unk14 = 0;
}

s32 func_psp_0892C188(unkStruct2* arg0, u8 arg1) {
    s32 i;
    unkStruct* curr;

    for (i = 0; i < 0x18; i++) {
        if ((arg0->unk8 & (1 << i)) == 0)
            return i;
    }
    curr = arg0->unk254;
    while (curr != NULL) {
        if (curr->unk10 != NULL &&
            ((u8*)(curr->unk10->unk1C + curr->unk14 * 0x20))[8] < arg1) {
            return curr->unkC;
        }
        curr = curr->next;
    }
    return -1;
}

void func_psp_0892C214(unkStruct2* arg0, s32 arg1, unkStruct3* arg2, s32 arg3) {
    s32 temp_s0;
    unkStruct* prev;
    unkStruct* next;
    unkStruct* curr;

    if (arg1 < 0x18) {
        temp_s0 = 1 << arg1;
        if (arg0->unk8 & temp_s0) {
            curr = arg0->unk254;
            while (curr != NULL) {
                if (curr->unk10 != NULL && curr->unkC == arg1) {
                    func_psp_0892C174(arg0, curr);
                    prev = curr->prev;
                    next = curr->next;
                    if (next != NULL) {
                        next->prev = prev;
                    } else {
                        arg0->unk258 = prev;
                    }
                    if (prev != NULL) {
                        prev->next = next;
                    } else {
                        arg0->unk254 = next;
                    }
                    arg0->unk260--;
                    if (arg0->unk26C != NULL) {
                        curr->next = NULL;
                        curr->prev = arg0->unk26C;
                        arg0->unk26C->next = curr;
                        arg0->unk26C = curr;
                    } else {
                        curr->next = NULL;
                        curr->prev = NULL;
                        arg0->unk268 = curr;
                        arg0->unk26C = curr;
                    }
                    arg0->unk274++;
                }
                curr = curr->next;
            }
        }
        arg0->unk8 |= temp_s0;
        curr = arg0->unk268;
        if (curr != NULL) {
            curr->unkC = arg1;
            curr->unk10 = arg2;
            curr->unk14 = arg3;
            arg2->unk20++;
            prev = curr->prev;
            next = curr->next;
            if (next != NULL) {
                next->prev = prev;
            } else {
                arg0->unk26C = prev;
            }
            if (prev != NULL) {
                prev->next = next;
            } else {
                arg0->unk268 = next;
            }
            arg0->unk274--;
            if (arg0->unk258 != NULL) {
                curr->next = NULL;
                curr->prev = arg0->unk258;
                arg0->unk258->next = curr;
                arg0->unk258 = curr;
            } else {
                curr->next = NULL;
                curr->prev = NULL;
                arg0->unk254 = curr;
                arg0->unk258 = curr;
            }
            arg0->unk260++;
        }
    }
}

void func_psp_0892C3D4(unkStruct2* arg0, s32 arg1) {
    s32 temp_s0;
    unkStruct* next;
    unkStruct* prev;
    unkStruct* curr;

    if (arg1 < 0x18) {
        temp_s0 = 1 << arg1;
        if (arg0->unk8 & temp_s0) {
            curr = arg0->unk254;
            while (curr != NULL) {
                if (curr->unk10 != NULL && curr->unkC == arg1) {
                    curr->unk10->unk20--;
                    func_psp_0892C174(arg0, curr);
                    prev = curr->prev;
                    next = curr->next;
                    if (next != NULL) {
                        next->prev = prev;
                    } else {
                        arg0->unk258 = prev;
                    }
                    if (prev != NULL) {
                        prev->next = next;
                    } else {
                        arg0->unk254 = next;
                    }
                    arg0->unk260--;
                    if (arg0->unk26C != NULL) {
                        curr->next = NULL;
                        curr->prev = arg0->unk26C;
                        arg0->unk26C->next = curr;
                        arg0->unk26C = curr;
                    } else {
                        curr->next = NULL;
                        curr->prev = NULL;
                        arg0->unk268 = curr;
                        arg0->unk26C = curr;
                    }
                    arg0->unk274++;
                }
                curr = curr->next;
            }
            arg0->unk8 &= ~temp_s0;
        }
    }
}

void func_psp_0892C4F8(unkStruct2* arg0, s32 arg1) {
    D_psp_08DAE788 = arg1;
    if (arg1 > 0x1000 || arg1 < 0) {
        D_psp_08DAE788 = 0x1000;
    }
}

void func_psp_0892C524(unkStruct2* arg0, s32 arg1, s32 arg2, s32 arg3) {
    func_psp_08916C40(arg1, arg2, arg3, arg0->unk0, arg0->unk4);
}

void func_psp_0892C540(unkStruct2* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4,
                       s32 arg5, s32 arg6, s32 arg7) {
    s32 temp_s7;

    if (arg2 != 0) {
        temp_s7 = arg4 * arg0->unk278;
        func_psp_0892CB1C();
        func_psp_08916B24(arg1);
        func_psp_08916CF4(
            arg1, 0x40000000 | (arg2 + 0x30) & 0x0FFFFFFF, arg3, arg7);
        func_psp_0892C524(arg0, arg1, arg5, arg6);
        func_psp_08916CA4(arg1, temp_s7);
        func_psp_08916AE8(arg1);
        func_psp_0892CB30();
    }
}

void func_psp_0892C62C(s32 arg0, s32 arg1) {
    func_psp_0892CB1C();
    func_psp_08916B24(arg1);
    func_psp_0892CB30();
}

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2D608", func_psp_0892C660);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2D608", func_psp_0892C860);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2D608", func_psp_0892CA28);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2D608", func_psp_0892CA90);

void func_psp_0892CAD8(void) {
    D_psp_08DAE780 = sceKernelCreateSema(D_psp_089632D8, 0, 1, 1, NULL);
}

void func_psp_0892CB10(void) { sceKernelDeleteSema(D_psp_08DAE780); }

void func_psp_0892CB1C(void) { sceKernelWaitSema(D_psp_08DAE780, 1, NULL); }

void func_psp_0892CB30(void) { sceKernelSignalSema(D_psp_08DAE780, 1); }

s32 func_psp_0892CB40(void) {
    volatile s32 i;
    s32 vol;

    i = 0;
    while (D_psp_08DAE784 != 0) {
        func_psp_0892CB1C();
        func_psp_0891692C(D_psp_08DADF80[i]);
        func_psp_0892CB30();
        vol = (D_psp_08DAE788 / 4096.0f) * 32768.0f;
        sceWaveAudioWriteBlocking(0, vol, vol, D_psp_08DADF80[i]);
        i ^= 1;
        if (D_psp_08DAE78C != 0) {
            sceKernelSleepThread();
            D_psp_08DAE78C = 0;
        }
    }
    while (sceWaveAudioGetRestSample(0) > 0) {
        sceKernelDelayThread(1000);
    }
    sceKernelExitThread(0);
    return 0;
}

Unk08919D98* func_psp_0892CC48(Unk08919D98* arg0, s16 arg1) {
    Unk08919D98* curr;

    if (arg0 != NULL) {
        arg0->unk0 = D_psp_089AD784;
        if (arg0->unkC != NULL) {
            curr = arg0->prev;
            while (curr != NULL) {
                Unk08919D98* next = curr->next;
                Unk08919D98* prev = curr->prev;
                if (next != NULL) {
                    next->prev = prev;
                } else {
                    arg0->next = prev;
                }
                if (prev != NULL) {
                    prev->next = next;
                } else {
                    arg0->prev = next;
                }
                arg0->count--;
                arg0->unkC(curr);
                curr = next;
            }
        } else {
            curr = arg0->prev;
            while (curr != NULL) {
                Unk08919D98* next = curr->next;
                Unk08919D98* prev = curr->prev;
                if (next != NULL) {
                    next->prev = prev;
                } else {
                    arg0->next = prev;
                }
                if (prev != NULL) {
                    prev->next = next;
                } else {
                    arg0->prev = next;
                }
                arg0->count--;
                curr = next;
            }
        }
        arg0->count = 0;
        if (arg1 > 0) {
            func_psp_08934D20(arg0);
        }
    }
    return arg0;
}

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2D608", func_psp_0892CD48);

void func_psp_0892CDE0(Unk08919D98* arg0) {
    Unk08919D98* curr;

    if (arg0->unkC != NULL) {
        curr = arg0->prev;
        while (curr != NULL) {
            Unk08919D98* next = curr->next;
            Unk08919D98* prev = curr->prev;
            if (next != NULL) {
                next->prev = prev;
            } else {
                arg0->next = prev;
            }
            if (prev != NULL) {
                prev->next = next;
            } else {
                arg0->prev = next;
            }
            arg0->count--;
            arg0->unkC(curr);
            curr = next;
        }
    } else {
        curr = arg0->prev;
        while (curr != NULL) {
            Unk08919D98* next = curr->next;
            Unk08919D98* prev = curr->prev;
            if (next != NULL) {
                next->prev = prev;
            } else {
                arg0->next = prev;
            }
            if (prev != NULL) {
                prev->next = next;
            } else {
                arg0->prev = next;
            }
            arg0->count--;
            curr = next;
        }
    }
    arg0->count = 0;
}

Unk08919D98* func_psp_0892CEB0(Unk08919D98* arg0, s16 arg1) {
    if (arg0 != NULL) {
        arg0->unk0 = D_psp_089AD79C;
        if (arg0 != NULL) {
            arg0->unk0 = D_psp_089AD790;
        }
        if (arg1 > 0) {
            func_psp_08934D20(arg0);
        }
    }
    return arg0;
}

Unk08919D98* func_psp_0892CF0C(Unk08919D98* arg0) {
    arg0->unk0 = D_psp_089AD790;
    arg0->next = NULL;
    arg0->prev = NULL;
    arg0->unk0 = D_psp_089AD79C;
    return arg0;
}

Unk08919D98* func_psp_0892CF34(Unk08919D98* arg0, s16 arg1) {
    if (arg0 != NULL) {
        arg0->unk0 = D_psp_089AD790;
        if (arg1 > 0) {
            func_psp_08934D20(arg0);
        }
    }
    return arg0;
}

void func_psp_0892CF7C(s32 arg0) { memalign(0x40, arg0); }

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2D608", func_psp_0892CF88);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2D608", func_psp_0892CF90);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2D608", func_psp_0892D030);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2D608", func_psp_0892D130);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2D608", func_psp_0892D154);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2D608", func_psp_0892D1B0);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2D608", func_psp_0892D1D8);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2D608", func_psp_0892D220);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2D608", func_psp_0892D2E8);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2D608", func_psp_0892D3B8);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2D608", func_psp_0892D4A8);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2D608", func_psp_0892D518);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2D608", func_psp_0892D520);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2D608", func_psp_0892D598);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2D608", func_psp_0892D5F0);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2D608", func_psp_0892D674);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2D608", func_psp_0892D818);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2D608", func_psp_0892D844);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2D608", func_psp_0892D96C);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2D608", func_psp_0892DADC);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2D608", func_psp_0892DB90);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2D608", func_psp_0892DBE4);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2D608", func_psp_0892DC40);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2D608", func_psp_0892DCD8);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2D608", func_psp_0892DD54);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2D608", func_psp_0892DDB0);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2D608", func_psp_0892DF08);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2D608", func_psp_0892DF70);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2D608", func_psp_0892DFCC);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2D608", func_psp_0892E498);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2D608", func_psp_0892E6A4);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2D608", func_psp_0892E718);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2D608", func_psp_0892E798);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2D608", func_psp_0892E818);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2D608", func_psp_0892E8B8);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2D608", func_psp_0892E914);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2D608", func_psp_0892E978);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2D608", func_psp_0892E994);

void func_psp_0892E9B0(void) {
    func_psp_0892E914();
    func_psp_0892BF14(&D_psp_08DADCC4);
    func_psp_0892D3B8(&D_psp_08DAE7A0);
}

void func_psp_0892E9E4(void) {
    func_psp_0892E914();
    func_psp_0892BFD0(&D_psp_08DADCC4);
    func_psp_0892D4A8(&D_psp_08DAE7A0);
}

void GsClearVcount(void) { func_psp_0892BF48(&D_psp_08DADCC4); }

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2D608", func_psp_0892EA24);

void func_psp_0892EAFC(char* arg0, s32 arg1) {
    func_psp_0892EA24(arg0, arg1, NULL);
}

void func_psp_0892EB04(s8* path, s32 arg1, s32 arg2) {
    s8 fileName[0x10];
    s8 buf[0x100];
    s8* ptr;
    s32 i;

    i = strlen(path);
    while (--i) {
        if (path[i] == '/' || path[i] == '\\') {
            i++;
            break;
        }
    }
    ptr = &path[i];
    for (i = 0; i < 0x10; i++) {
        fileName[i] = *ptr;
        if (fileName[i] == '.') {
            fileName[i] = '\0';
            break;
        }
        ptr++;
    }
    sprintf(buf, D_psp_08963300, D_psp_08B42060, fileName);
    func_psp_0892EA24(buf, arg1, arg2);
}

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2D608", func_psp_0892EBE8);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2D608", func_psp_0892EC7C);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2D608", SpuGetAllKeysStatus);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2D608", SsUtKeyOnV);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2D608", SsUtSetVVol);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2D608", SpuSetKey);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2D608", SpuSetVoiceAttr);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2D608", func_psp_0892F83C);
