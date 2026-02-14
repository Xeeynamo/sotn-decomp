// SPDX-License-Identifier: AGPL-3.0-or-later
#include <game_psp.h>

typedef void (*LoadFunc)(void);

typedef struct {
    s32 type;
    char* ovlName;
    void* dst;
    LoadFunc load;
} unkStruct;

// clang-format off
static unkStruct D_psp_089622C8[] = {
    {1, "dra", NULL, (LoadFunc)0x00000000},
    {2, "sel", NULL, (LoadFunc)0x09237868},
    {2, "st0", NULL, (LoadFunc)0x09246B10},
    {2, "are", NULL, (LoadFunc)0x092379E8},
    {2, "cat", NULL, (LoadFunc)0x0925E600},
    {2, "cen", NULL, (LoadFunc)0x09260988},
    {2, "chi", NULL, (LoadFunc)0x0924BCA8},
    {2, "dai", NULL, (LoadFunc)0x09251430},
    {2, "dre", NULL, (LoadFunc)0x09244A50},
    {2, "lib", NULL, (LoadFunc)0x09254120},
    {2, "no0", NULL, (LoadFunc)0x0925D048},
    {2, "no1", NULL, (LoadFunc)0x09255C38},
    {2, "no2", NULL, (LoadFunc)0x09256C90},
    {2, "no3", NULL, (LoadFunc)0x09238360},
    {2, "no4", NULL, (LoadFunc)0x09237FB0},
    {2, "np3", NULL, (LoadFunc)0x09237A90},
    {2, "nz0", NULL, (LoadFunc)0x09237AB0},
    {2, "nz1", NULL, (LoadFunc)0x09253460},
    {2, "top", NULL, (LoadFunc)0x09248480},
    {2, "wrp", NULL, (LoadFunc)0x092447C0},
    {2, "rare", NULL, (LoadFunc)0x09237840},
    {2, "rcat", NULL, (LoadFunc)0x0924C6D8},
    {2, "rcen", NULL, (LoadFunc)0x09244F30},
    {2, "rchi", NULL, (LoadFunc)0x0924A488},
    {2, "rdai", NULL, (LoadFunc)0x0924F318},
    {2, "rlib", NULL, (LoadFunc)0x09249828},
    {2, "rno0", NULL, (LoadFunc)0x0925D410},
    {2, "rno1", NULL, (LoadFunc)0x092497F8},
    {2, "rno2", NULL, (LoadFunc)0x09253588},
    {2, "rno3", NULL, (LoadFunc)0x09255FB0},
    {2, "rno4", NULL, (LoadFunc)0x09251F90},
    {2, "rnz0", NULL, (LoadFunc)0x09256B38},
    {2, "rnz1", NULL, (LoadFunc)0x09252CD8},
    {2, "rtop", NULL, (LoadFunc)0x09247898},
    {2, "rwrp", NULL, (LoadFunc)0x09244D08},
    {2, "mar", NULL, (LoadFunc)0x092465C8},
    {2, "bo0", NULL, (LoadFunc)0x09251368},
    {2, "bo1", NULL, (LoadFunc)0x09245870},
    {2, "bo2", NULL, (LoadFunc)0x09245D30},
    {2, "bo3", NULL, (LoadFunc)0x09246198},
    {2, "bo4", NULL, (LoadFunc)0x092478E8},
    {2, "bo5", NULL, (LoadFunc)0x092473A0},
    {2, "bo6", NULL, (LoadFunc)0x09244758},
    {2, "bo7", NULL, (LoadFunc)0x09245D08},
    {2, "rbo0", NULL, (LoadFunc)0x09237858},
    {2, "rbo1", NULL, (LoadFunc)0x09248780},
    {2, "rbo2", NULL, (LoadFunc)0x09245DF0},
    {2, "rbo3", NULL, (LoadFunc)0x09245800},
    {2, "rbo4", NULL, (LoadFunc)0x09245F70},
    {2, "rbo5", NULL, (LoadFunc)0x0925F690},
    {2, "rbo6", NULL, (LoadFunc)0x09244A00},
    {2, "rbo7", NULL, (LoadFunc)0x09245D40},
    {2, "rbo8", NULL, (LoadFunc)0x09245C58},
    {3, "ric", NULL, (LoadFunc)0x092C8D48},
    {3, "arc_f", NULL, (LoadFunc)0x092A6280},
    {3, "maria", NULL, (LoadFunc)0x092C0280},
    {4, "tt_000", NULL, (LoadFunc)0x092EC220},
    {4, "tt_001", NULL, (LoadFunc)0x092EA620},
    {4, "tt_002", NULL, (LoadFunc)0x092EF290},
    {4, "tt_003", NULL, (LoadFunc)0x092EF908},
    {4, "tt_004", NULL, (LoadFunc)0x092EF780},
    {4, "tt_005", NULL, (LoadFunc)0x092EF290},
    {4, "tt_006", NULL, (LoadFunc)0x092EF908},
    {5, "w0_000", NULL, (LoadFunc)0x092F3498},
    {5, "w0_001", NULL, (LoadFunc)0x092F48A0},
    {5, "w0_002", NULL, (LoadFunc)0x092F3490},
    {5, "w0_003", NULL, (LoadFunc)0x092F3498},
    {5, "w0_004", NULL, (LoadFunc)0x092F34A8},
    {5, "w0_005", NULL, (LoadFunc)0x092F3500},
    {5, "w0_006", NULL, (LoadFunc)0x092F40F8},
    {5, "w0_007", NULL, (LoadFunc)0x092F4020},
    {5, "w0_008", NULL, (LoadFunc)0x092F4B80},
    {5, "w0_009", NULL, (LoadFunc)0x092F4D98},
    {5, "w0_010", NULL, (LoadFunc)0x092F59D0},
    {5, "w0_011", NULL, (LoadFunc)0x092F5740},
    {5, "w0_012", NULL, (LoadFunc)0x092F4650},
    {5, "w0_013", NULL, (LoadFunc)0x092F4AB0},
    {5, "w0_014", NULL, (LoadFunc)0x092F4418},
    {5, "w0_015", NULL, (LoadFunc)0x092F4D88},
    {5, "w0_016", NULL, (LoadFunc)0x092F4E68},
    {5, "w0_017", NULL, (LoadFunc)0x092F3C30},
    {5, "w0_018", NULL, (LoadFunc)0x092F3900},
    {5, "w0_019", NULL, (LoadFunc)0x092F3818},
    {5, "w0_020", NULL, (LoadFunc)0x092F4E18},
    {5, "w0_021", NULL, (LoadFunc)0x092F4D08},
    {5, "w0_022", NULL, (LoadFunc)0x092F3740},
    {5, "w0_023", NULL, (LoadFunc)0x092F5798},
    {5, "w0_024", NULL, (LoadFunc)0x092F59F8},
    {5, "w0_025", NULL, (LoadFunc)0x092F5880},
    {5, "w0_026", NULL, (LoadFunc)0x092F5A70},
    {5, "w0_027", NULL, (LoadFunc)0x092F5140},
    {5, "w0_028", NULL, (LoadFunc)0x092F5A10},
    {5, "w0_029", NULL, (LoadFunc)0x092F5300},
    {5, "w0_030", NULL, (LoadFunc)0x092F6378},
    {5, "w0_031", NULL, (LoadFunc)0x092F3508},
    {5, "w0_032", NULL, (LoadFunc)0x092F35B8},
    {5, "w0_033", NULL, (LoadFunc)0x092F34E8},
    {5, "w0_034", NULL, (LoadFunc)0x092F3C28},
    {5, "w0_035", NULL, (LoadFunc)0x092F3498},
    {5, "w0_036", NULL, (LoadFunc)0x092F3498},
    {5, "w0_037", NULL, (LoadFunc)0x092F4670},
    {5, "w0_038", NULL, (LoadFunc)0x092F39F0},
    {5, "w0_039", NULL, (LoadFunc)0x092F3CC0},
    {5, "w0_040", NULL, (LoadFunc)0x092F3ED0},
    {5, "w0_041", NULL, (LoadFunc)0x092F3E18},
    {5, "w0_042", NULL, (LoadFunc)0x092F4010},
    {5, "w0_043", NULL, (LoadFunc)0x092F3F10},
    {5, "w0_044", NULL, (LoadFunc)0x092F3EE8},
    {5, "w0_045", NULL, (LoadFunc)0x092F4058},
    {5, "w0_046", NULL, (LoadFunc)0x092F4738},
    {5, "w0_047", NULL, (LoadFunc)0x092F4500},
    {5, "w0_048", NULL, (LoadFunc)0x092F47C8},
    {5, "w0_049", NULL, (LoadFunc)0x092F4E58},
    {5, "w0_050", NULL, (LoadFunc)0x092F5358},
    {5, "w0_051", NULL, (LoadFunc)0x092F47C0},
    {5, "w0_052", NULL, (LoadFunc)0x092F58C0},
    {5, "w0_053", NULL, (LoadFunc)0x092F4BC8},
    {5, "w0_054", NULL, (LoadFunc)0x092F39E8},
    {5, "w0_055", NULL, (LoadFunc)0x092F3AE0},
    {5, "w0_056", NULL, (LoadFunc)0x092F4368},
    {5, "w0_057", NULL, (LoadFunc)0x092F3498},
    {5, "w0_058", NULL, (LoadFunc)0x092F43C0},
    {6, "w1_000", NULL, (LoadFunc)0x092F7298},
    {6, "w1_001", NULL, (LoadFunc)0x092F86A0},
    {6, "w1_002", NULL, (LoadFunc)0x092F7290},
    {6, "w1_003", NULL, (LoadFunc)0x092F7298},
    {6, "w1_004", NULL, (LoadFunc)0x092F72A8},
    {6, "w1_005", NULL, (LoadFunc)0x092F7300},
    {6, "w1_006", NULL, (LoadFunc)0x092F7EF8},
    {6, "w1_007", NULL, (LoadFunc)0x092F7E20},
    {6, "w1_008", NULL, (LoadFunc)0x092F8980},
    {6, "w1_009", NULL, (LoadFunc)0x092F8B98},
    {6, "w1_010", NULL, (LoadFunc)0x092F97D0},
    {6, "w1_011", NULL, (LoadFunc)0x092F9540},
    {6, "w1_012", NULL, (LoadFunc)0x092F8450},
    {6, "w1_013", NULL, (LoadFunc)0x092F88B0},
    {6, "w1_014", NULL, (LoadFunc)0x092F8218},
    {6, "w1_015", NULL, (LoadFunc)0x092F8B88},
    {6, "w1_016", NULL, (LoadFunc)0x092F8C68},
    {6, "w1_017", NULL, (LoadFunc)0x092F7A30},
    {6, "w1_018", NULL, (LoadFunc)0x092F7700},
    {6, "w1_019", NULL, (LoadFunc)0x092F7618},
    {6, "w1_020", NULL, (LoadFunc)0x092F8C10},
    {6, "w1_021", NULL, (LoadFunc)0x092F8B08},
    {6, "w1_022", NULL, (LoadFunc)0x092F7540},
    {6, "w1_023", NULL, (LoadFunc)0x092F9598},
    {6, "w1_024", NULL, (LoadFunc)0x092F97F8},
    {6, "w1_025", NULL, (LoadFunc)0x092F9680},
    {6, "w1_026", NULL, (LoadFunc)0x092F9870},
    {6, "w1_027", NULL, (LoadFunc)0x092F8F40},
    {6, "w1_028", NULL, (LoadFunc)0x092F9810},
    {6, "w1_029", NULL, (LoadFunc)0x092F9100},
    {6, "w1_030", NULL, (LoadFunc)0x092FA178},
    {6, "w1_031", NULL, (LoadFunc)0x092F7308},
    {6, "w1_032", NULL, (LoadFunc)0x092F73B8},
    {6, "w1_033", NULL, (LoadFunc)0x092F72E8},
    {6, "w1_034", NULL, (LoadFunc)0x092F7A28},
    {6, "w1_035", NULL, (LoadFunc)0x092F7298},
    {6, "w1_036", NULL, (LoadFunc)0x092F7298},
    {6, "w1_037", NULL, (LoadFunc)0x092F8470},
    {6, "w1_038", NULL, (LoadFunc)0x092F77F0},
    {6, "w1_039", NULL, (LoadFunc)0x092F7AC0},
    {6, "w1_040", NULL, (LoadFunc)0x092F7CD0},
    {6, "w1_041", NULL, (LoadFunc)0x092F7C18},
    {6, "w1_042", NULL, (LoadFunc)0x092F7E10},
    {6, "w1_043", NULL, (LoadFunc)0x092F7D10},
    {6, "w1_044", NULL, (LoadFunc)0x092F7CE8},
    {6, "w1_045", NULL, (LoadFunc)0x092F7E58},
    {6, "w1_046", NULL, (LoadFunc)0x092F8538},
    {6, "w1_047", NULL, (LoadFunc)0x092F8300},
    {6, "w1_048", NULL, (LoadFunc)0x092F85C8},
    {6, "w1_049", NULL, (LoadFunc)0x092F8C58},
    {6, "w1_050", NULL, (LoadFunc)0x092F9158},
    {6, "w1_051", NULL, (LoadFunc)0x092F85C0},
    {6, "w1_052", NULL, (LoadFunc)0x092F96C0},
    {6, "w1_053", NULL, (LoadFunc)0x092F89C8},
    {6, "w1_054", NULL, (LoadFunc)0x092F77E8},
    {6, "w1_055", NULL, (LoadFunc)0x092F78E0},
    {6, "w1_056", NULL, (LoadFunc)0x092F8168},
    {6, "w1_057", NULL, (LoadFunc)0x092F7298},
    {6, "w1_058", NULL, (LoadFunc)0x092F81C0},
};
// clang-format on

extern s32* D_psp_089AD810[];
extern u8 D_psp_08CADC40[];
extern s32* g_pStObjLayoutHorizontal;
extern s32* g_pStObjLayoutVertical;

void func_psp_089375C0(s32*, u32);

void func_psp_08929FA8(s32* arg0, s32 count) {
    s32 i;

    for (i = 0; i < count; i++) {
        *arg0 = (s32)&D_psp_08CADC40[*arg0 & 0x000FFFFF];
        arg0++;
    }
}

void func_psp_0892A018(void) {
    s32 i;

    for (i = 0; i <= 52; i++) {
        g_pStObjLayoutHorizontal[i] =
            (s32)&D_psp_08CADC40[g_pStObjLayoutHorizontal[i] & 0x000FFFFF];
        g_pStObjLayoutVertical[i] =
            (s32)&D_psp_08CADC40[g_pStObjLayoutVertical[i] & 0x000FFFFF];
    }
}

void* GetOverlayDst(s32 arg0) { return D_psp_089AD810[arg0]; }

void LoadOverlay(s32 ovlIndex, void* data, s32 size) {
    char ovlPath[0x100];
    unkStruct* ptr;

    ptr = &D_psp_089622C8[ovlIndex];
    sprintf(
        ovlPath, "disc0:/PSP_GAME/USRDIR/res/ps/PSPBIN/%s.bin", ptr->ovlName);
    if (ptr->dst == NULL) {
        ptr->dst = GetOverlayDst(ptr->type);
    }
    if (data != NULL) {
        memcpy(ptr->dst, data, size);
        func_psp_089375C0(ptr->dst, size);
    } else {
        while (true) {
            bool done = func_psp_08937740(ovlPath, ptr->dst);
            if (done) {
                break;
            }
            sceKernelDelayThreadCB(166);
        }
    }
    if (ptr->load != NULL) {
        ptr->load();
    }
}

void func_psp_0892A1EC(s32 ovlIndex) { LoadOverlay(ovlIndex, NULL, 0); }
