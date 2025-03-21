// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../dra/dra.h"

static char D_psp_09187068[] =
    "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstu"
    "vwxyz0123456789\" .+-=_'?/![]\":;,()";
static char D_psp_091870C0[] =
    "ＡＢＣＤＥＦＧＨＩＪＫＬＭＮＯＰＱＲＳＴＵＶＷＸＹＺａｂｃｄｅｆｇｈｉｊｋ"
    "ｌｍｎｏｐｑｒｓｔｕｖｗｘｙｚ０１２３４５６７８９”　．＋−＝＿’？／！［］”"
    "：；，（）";
static char* D_psp_09187168[] = {D_psp_091870C0};
static char* D_psp_09187170[] = {D_psp_09187068};
static char D_psp_09187178[] =
    "ｱｲｳｴｵｶｷｸｹｺｻｼｽｾｿﾀﾁﾂﾃﾄﾅﾆﾇﾈﾉﾊﾋﾌﾍﾎﾏﾐﾑﾒﾓﾔﾕﾖﾗﾘﾙﾚﾛﾜｦﾝｧｨｩｪｫｬｭｮ";
static u16 D_psp_091871B0[] = {
    0x8146, 0x8634, 0x8635, 0x858A, 0x858B, 0x858D, 0x858C, 0x8597,
    0x859B, 0x859A, 0x859D, 0x859C, 0x85A8, 0x85A7, 0x85AA, 0x85A9,
    0x85B8, 0x85BA, 0x85B9, 0x85BC, 0x85BB, 0x85CB, 0x85CA, 0x85CD,
    0x85CC, 0x83C0, 0x85E1, 0x85E0, 0x85E3, 0x85E2, 0x85ED, 0x85F1,
    0x85F0, 0x85F3, 0x85F2, 0x85FE, 0x85FD, 0x8600, 0x85FF, 0x860D,
    0x860F, 0x860E, 0x8611, 0x8610, 0x8620, 0x861F, 0x8622, 0x8621,
    0x8577, 0x8586, 0x814E, 0x8636, 0x8147, 0x8621, 0x0000};

u16 func_psp_0913F960(char* str, u8* type) {
    u32 i;
    u16 ret;
    char* ptr;

    ptr = D_psp_09187170[0];
    for (i = 0; i < LEN(D_psp_09187068); i++) {
        if (str[0] == *ptr) {
            char* ch = &D_psp_09187168[0][i * 2];
            ret = ch[0] << 8;
            ret |= ch[1];
            *type = 1;
            return ret;
        }
        ptr++;
    }
    ptr = D_psp_09187178;
    for (i = 0; i < LEN(D_psp_091871B0); i++) {
        if (str[0] == *ptr) {
            ret = D_psp_091871B0[i];
            *type = 1;
            return ret;
        }
        ptr++;
    }
    ret = str[0] << 8;
    ret |= str[1];
    *type = 2;
    return ret;
}

INCLUDE_ASM("dra_psp/psp/dra_psp/62FE0", func_psp_0913FA28);

INCLUDE_ASM("dra_psp/psp/dra_psp/62FE0", func_psp_09140588);

INCLUDE_ASM("dra_psp/psp/dra_psp/62FE0", func_psp_091405C8);

INCLUDE_ASM("dra_psp/psp/dra_psp/62FE0", func_psp_091405E0);

INCLUDE_ASM("dra_psp/psp/dra_psp/62FE0", func_psp_09140600);
