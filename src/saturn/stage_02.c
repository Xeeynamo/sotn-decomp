#include "inc_asm.h"
#include "sattypes.h"

// Alchemy Laboratory

INCLUDE_ASM("asm/saturn/stage_02", d60DC000, d_060DC000);
INCLUDE_ASM("asm/saturn/stage_02", f60DC040, func_060DC040);
INCLUDE_ASM("asm/saturn/stage_02", f60DC460, func_060DC460);
INCLUDE_ASM("asm/saturn/stage_02", f60DC4EC, func_060DC4EC);
INCLUDE_ASM("asm/saturn/stage_02", f60DC510, func_060DC510);
INCLUDE_ASM("asm/saturn/stage_02", f60DC7B4, func_060DC7B4);
INCLUDE_ASM("asm/saturn/stage_02", f60DCA54, func_060DCA54);
INCLUDE_ASM("asm/saturn/stage_02", f60DCCD4, func_060DCCD4);
INCLUDE_ASM("asm/saturn/stage_02", f60DCFA4, func_060DCFA4);
INCLUDE_ASM("asm/saturn/stage_02", f60DD20C, func_060DD20C);
INCLUDE_ASM("asm/saturn/stage_02", f60DD3E8, func_060DD3E8);
INCLUDE_ASM("asm/saturn/stage_02", f60DD690, func_060DD690);
INCLUDE_ASM("asm/saturn/stage_02", f60DD790, func_060DD790);
INCLUDE_ASM("asm/saturn/stage_02", f60DD8D8, func_060DD8D8);
INCLUDE_ASM("asm/saturn/stage_02", f60DDB80, func_060DDB80);
INCLUDE_ASM("asm/saturn/stage_02", f60DDE40, func_060DDE40);
INCLUDE_ASM("asm/saturn/stage_02", f60DDF64, func_060DDF64);
INCLUDE_ASM("asm/saturn/stage_02", f60DE178, func_060DE178);
INCLUDE_ASM("asm/saturn/stage_02", f60DE2B0, func_060DE2B0);
INCLUDE_ASM("asm/saturn/stage_02", f60DE348, func_060DE348);
INCLUDE_ASM("asm/saturn/stage_02", f60DE6CC, func_060DE6CC);
INCLUDE_ASM("asm/saturn/stage_02", f60DE970, func_060DE970);
INCLUDE_ASM("asm/saturn/stage_02", f60DEE20, func_060DEE20);
INCLUDE_ASM("asm/saturn/stage_02", f60DF264, func_060DF264);
INCLUDE_ASM("asm/saturn/stage_02", f60DF3B8, func_060DF3B8);
INCLUDE_ASM("asm/saturn/stage_02", f60DF52C, func_060DF52C);
INCLUDE_ASM("asm/saturn/stage_02", f60DF664, func_060DF664);
INCLUDE_ASM("asm/saturn/stage_02", f60DF798, func_060DF798);
INCLUDE_ASM("asm/saturn/stage_02", f60DFAE4, func_060DFAE4);
INCLUDE_ASM("asm/saturn/stage_02", f60E0304, func_060E0304);
INCLUDE_ASM("asm/saturn/stage_02", f60E0684, func_060E0684);
INCLUDE_ASM("asm/saturn/stage_02", f60E08B0, func_060E08B0);
INCLUDE_ASM("asm/saturn/stage_02", f60E08E4, func_060E08E4);
INCLUDE_ASM("asm/saturn/stage_02", f60E093C, func_060E093C);
INCLUDE_ASM("asm/saturn/stage_02", f60E0AF0, func_060E0AF0);
INCLUDE_ASM("asm/saturn/stage_02", f60E0B24, func_060E0B24);
INCLUDE_ASM("asm/saturn/stage_02", f60E0B7C, func_060E0B7C);
INCLUDE_ASM("asm/saturn/stage_02", f60E0DC8, func_060E0DC8);
void f60E0F58() {}
void f60E0F64() {}
INCLUDE_ASM("asm/saturn/stage_02", f60E0F70, func_060E0F70);
INCLUDE_ASM("asm/saturn/stage_02", f60E1A00, func_060E1A00);
INCLUDE_ASM("asm/saturn/stage_02", f60E1C08, func_060E1C08);
INCLUDE_ASM("asm/saturn/stage_02", f60E1CA8, func_060E1CA8);
INCLUDE_ASM("asm/saturn/stage_02", f60E1D48, func_060E1D48);

struct Unk {
    u8 pad[0x38];
    u16 unk_38;
    u16 unk_3a;
    u32 unk_3c;
};

extern struct Unk DAT_060e2014; // 060F5044h

// maybe func_801B797C?
void func_060e1ff8(s32 param_1) {
    DAT_060e2014.unk_3c = param_1;
    DAT_060e2014.unk_3a = 0;
    DAT_060e2014.unk_38 = 1;
}

INCLUDE_ASM("asm/saturn/stage_02", f60E2018, func_060E2018);
INCLUDE_ASM("asm/saturn/stage_02", f60E21B8, func_060E21B8);
INCLUDE_ASM("asm/saturn/stage_02", f60E22FC, func_060E22FC);
INCLUDE_ASM("asm/saturn/stage_02", f60E2420, func_060E2420);
INCLUDE_ASM("asm/saturn/stage_02", f60E2898, func_060E2898);
INCLUDE_ASM("asm/saturn/stage_02", f60E29A4, func_060E29A4);
INCLUDE_ASM("asm/saturn/stage_02", d60E2A80, d_060E2A80);
INCLUDE_ASM("asm/saturn/stage_02", d60E32DC, d_060E32DC);
INCLUDE_ASM("asm/saturn/stage_02", d60E47A4, d_060E47A4);
INCLUDE_ASM("asm/saturn/stage_02", f60E4908, func_060E4908);
INCLUDE_ASM("asm/saturn/stage_02", f60E4F78, func_060E4F78);
INCLUDE_ASM("asm/saturn/stage_02", f60E4FD0, func_060E4FD0);
INCLUDE_ASM("asm/saturn/stage_02", f60E5388, func_060E5388);
INCLUDE_ASM("asm/saturn/stage_02", f60E5410, func_060E5410);
INCLUDE_ASM("asm/saturn/stage_02", f60E5AE4, func_060E5AE4);
INCLUDE_ASM("asm/saturn/stage_02", f60E5C4C, func_060E5C4C);
INCLUDE_ASM("asm/saturn/stage_02", f60E5DB4, func_060E5DB4);
INCLUDE_ASM("asm/saturn/stage_02", f60E5EA0, func_060E5EA0);
INCLUDE_ASM("asm/saturn/stage_02", f60E600C, func_060E600C);
INCLUDE_ASM("asm/saturn/stage_02", f60E6140, func_060E6140);
INCLUDE_ASM("asm/saturn/stage_02", f60E625C, func_060E625C);
INCLUDE_ASM("asm/saturn/stage_02", f60E633C, func_060E633C);
INCLUDE_ASM("asm/saturn/stage_02", f60E6628, func_060E6628);
INCLUDE_ASM("asm/saturn/stage_02", f60E6B00, func_060E6B00);
INCLUDE_ASM("asm/saturn/stage_02", f60E6C0C, func_060E6C0C);
INCLUDE_ASM("asm/saturn/stage_02", f60E7014, func_060E7014);
INCLUDE_ASM("asm/saturn/stage_02", f60E73CC, func_060E73CC);
INCLUDE_ASM("asm/saturn/stage_02", f60E7508, func_060E7508);
INCLUDE_ASM("asm/saturn/stage_02", f60E81D4, func_060E81D4);
INCLUDE_ASM("asm/saturn/stage_02", f60E82EC, func_060E82EC);

s32 arr_0605C140[];

// not seeing an obvious PSX equivalent
void func_060e8330(void) {
    arr_0605C140[0xEF] = 0x1000;
    arr_0605C140[0xF1] = 1;
}

INCLUDE_ASM("asm/saturn/stage_02", f60E8350, func_060E8350);
INCLUDE_ASM("asm/saturn/stage_02", f60E837C, func_060E837C);
INCLUDE_ASM("asm/saturn/stage_02", f60E8780, func_060E8780);
INCLUDE_ASM("asm/saturn/stage_02", f60E87D0, func_060E87D0);
INCLUDE_ASM("asm/saturn/stage_02", f60E8990, func_060E8990);
INCLUDE_ASM("asm/saturn/stage_02", f60E8ADC, func_060E8ADC);

void func_060E8E1C(s32, s32);
void func_060E8EEC(s32, s32, s32);

void func_060E8DE0(s32 arg0, s32 arg1, s32 arg2)
{
    func_060E8E1C(arg1, arg2);
    func_060E8EEC(arg0, arg1, arg2);
}

INCLUDE_ASM("asm/saturn/stage_02", f60E8E1C, func_060E8E1C);
INCLUDE_ASM("asm/saturn/stage_02", f60E8EEC, func_060E8EEC);
INCLUDE_ASM("asm/saturn/stage_02", f60E9058, func_060E9058);
INCLUDE_ASM("asm/saturn/stage_02", f60E9220, func_060E9220);
INCLUDE_ASM("asm/saturn/stage_02", f60E9270, func_060E9270);

// dupe of func_060e97c4
void func_060E92A8(u16** param_1) {

    if (*(u16*)(param_1 + 6) != 0) {
        **param_1 = **param_1 | 0x10;

    } else {
        **param_1 = **param_1 & 0xffef;
    }
}

// not sure what these are
const u16 pad_060e92d4 = 0xAAAA;
const u16 pad_060e92d6 = 0xAAAB;

INCLUDE_ASM("asm/saturn/stage_02", f60E92D8, func_060E92D8);
INCLUDE_ASM("asm/saturn/stage_02", f60E9770, func_060E9770);

// seems to saturn-only. param_1 is probably a struct?
void func_060e97c4(u16** param_1) {

    if (*(u16*)(param_1 + 6) != 0) {
        **param_1 = **param_1 | 0x10;

    } else {
        **param_1 = **param_1 & 0xffef;
    }
}

INCLUDE_ASM("asm/saturn/stage_02", f60E97F0, func_060E97F0);
INCLUDE_ASM("asm/saturn/stage_02", f60E9828, func_060E9828);
INCLUDE_ASM("asm/saturn/stage_02", f60EA058, func_060EA058);
INCLUDE_ASM("asm/saturn/stage_02", f60EA1E0, func_060EA1E0);

// dupe of func_060e97c4
void func_060EA234(u16** param_1) {
    if (*(u16*)(param_1 + 6) != 0) {
        **param_1 = **param_1 | 0x10;
    } else {
        **param_1 = **param_1 & 0xffef;
    }
}

// not sure what these are
const u16 pad_060EA260 = 0xCCCC;
const u16 pad_060EA262 = 0xCCCD;

INCLUDE_ASM("asm/saturn/stage_02", f60EA264, func_060EA264);
INCLUDE_ASM("asm/saturn/stage_02", f60EAC54, func_060EAC54);
INCLUDE_ASM("asm/saturn/stage_02", f60EACC0, func_060EACC0);
INCLUDE_ASM("asm/saturn/stage_02", f60EAF2C, func_060EAF2C);
INCLUDE_ASM("asm/saturn/stage_02", f60EAFAC, func_060EAFAC);
INCLUDE_ASM("asm/saturn/stage_02", f60EB5C4, func_060EB5C4);
INCLUDE_ASM("asm/saturn/stage_02", f60EB6E4, func_060EB6E4);
INCLUDE_ASM("asm/saturn/stage_02", f60EB8D0, func_060EB8D0);
INCLUDE_ASM("asm/saturn/stage_02", f60EB950, func_060EB950);
INCLUDE_ASM("asm/saturn/stage_02", f60EB9EC, func_060EB9EC);
INCLUDE_ASM("asm/saturn/stage_02", f60EBEB0, func_060EBEB0);
INCLUDE_ASM("asm/saturn/stage_02", f60EC030, func_060EC030);
INCLUDE_ASM("asm/saturn/stage_02", f60EC1F0, func_060EC1F0);
INCLUDE_ASM("asm/saturn/stage_02", f60EC240, func_060EC240);
INCLUDE_ASM("asm/saturn/stage_02", f60EC278, func_060EC278);
INCLUDE_ASM("asm/saturn/stage_02", f60EC730, func_060EC730);
INCLUDE_ASM("asm/saturn/stage_02", d60ECA94, d_060ECA94);
INCLUDE_ASM("asm/saturn/stage_02", d60ECC50, d_060ECC50);
