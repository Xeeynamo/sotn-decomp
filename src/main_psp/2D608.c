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

extern s32 D_psp_089AD784[];
extern s32 D_psp_089AD790[];
extern s32 D_psp_089AD79C[];
extern s32 D_psp_08DADCC4;
extern s32 D_psp_08DAE780;
extern s32 D_psp_08DAE784;
extern s32 D_psp_08DAE7A0;

void func_psp_0892CB10(s32*);
void func_psp_0892C168(s32*);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2D608", func_psp_0892BF14);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2D608", func_psp_0892BF48);

void func_psp_0892BFD0(s32* arg0) { func_psp_0892C168(arg0); }

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2D608", func_psp_0892BFD8);

void func_psp_0892C168(s32* arg0) {
    D_psp_08DAE784 = 0;
    func_psp_0892CB10(arg0);
}

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2D608", func_psp_0892C174);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2D608", func_psp_0892C188);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2D608", func_psp_0892C214);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2D608", func_psp_0892C3D4);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2D608", func_psp_0892C4F8);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2D608", func_psp_0892C524);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2D608", func_psp_0892C540);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2D608", func_psp_0892C62C);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2D608", func_psp_0892C660);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2D608", func_psp_0892C860);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2D608", func_psp_0892CA28);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2D608", func_psp_0892CA90);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2D608", func_psp_0892CAD8);

void func_psp_0892CB10(s32* arg0) { sceKernelDeleteSema(D_psp_08DAE780); }

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2D608", func_psp_0892CB1C);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2D608", func_psp_0892CB30);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2D608", func_psp_0892CB40);

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

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2D608", func_psp_0892CF7C);

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

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2D608", func_psp_0892EB04);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2D608", func_psp_0892EBE8);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2D608", func_psp_0892EC7C);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2D608", SpuGetAllKeysStatus);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2D608", SsUtKeyOnV);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2D608", SsUtSetVVol);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2D608", SpuSetKey);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2D608", SpuSetVoiceAttr);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2D608", func_psp_0892F83C);
