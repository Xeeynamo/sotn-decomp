// SPDX-License-Identifier: AGPL-3.0-or-later
#include "inc_asm.h"
#include "sattypes.h"

INCLUDE_ASM("asm/saturn/maria/data", d60A5000, d_060A5000);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60A5060, func_060A5060);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60A5154, func_060A5154);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60A5208, func_060A5208);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60A54F0, func_060A54F0);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60A5884, func_060A5884);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60A59A8, func_060A59A8);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60A5AD4, func_060A5AD4);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60A5BE8, func_060A5BE8);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60A6624, func_060A6624);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60A66C8, func_060A66C8);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60A6A1C, func_060A6A1C);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60A6A94, func_060A6A94);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60A6B90, func_060A6B90);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60A70B4, func_060A70B4);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60A714C, func_060A714C);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60A7508, func_060A7508);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60A75AC, func_060A75AC);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60A7DF4, func_060A7DF4);
// function, splitter bugs
INCLUDE_ASM("asm/saturn/maria/data", d60A7F70, d_060A7F70);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60A8248, func_060A8248);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60A8308, func_060A8308);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60A83C8, func_060A83C8);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60A841C, func_060A841C);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60A8470, func_060A8470);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60A8534, func_060A8534);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60A8860, func_060A8860);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60A8A38, func_060A8A38);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60A8AE8, func_060A8AE8);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60A8C14, func_060A8C14);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60A8E34, func_060A8E34);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60A8F2C, func_060A8F2C);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60A9064, func_060A9064);

void func_060A9130(void) { func_060AA4BC(); }

INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60A914C, func_060A914C);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60A9194, func_060A9194);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60A9210, func_060A9210);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60A926C, func_060A926C);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60A9304, func_060A9304);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60A939C, func_060A939C);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60A9474, func_060A9474);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60A955C, func_060A955C);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60A9608, func_060A9608);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60A96D4, func_060A96D4);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60A973C, func_060A973C);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60A9958, func_060A9958);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60A9990, func_060A9990);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60A9BC4, func_060A9BC4);

s32 func_060A9CE8(void) {
    s32 pad[5];
    return 1;
}

void func_060AF4A0(void) { func_060AA4BC(1); }

INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60A9D10, func_060A9D10);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60A9DA4, func_060A9DA4);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60A9E40, func_060A9E40);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60A9EC4, func_060A9EC4);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60A9F84, func_060A9F84);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60AA0A0, func_060AA0A0);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60AA260, func_060AA260);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60AA4BC, func_060AA4BC);

void RicSetStep(s16 step) {
    PLAYER.step = step;
    PLAYER.step_s = 0;
}

INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60AA4D8, func_060AA4D8);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60AA4FC, func_060AA4FC);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60AA608, func_060AA608);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60AA754, func_060AA754);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60AA784, func_060AA784);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60AA7B4, func_060AA7B4);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60AA830, func_060AA830);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60AA854, func_060AA854);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60AA8AC, func_060AA8AC);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60AA948, func_060AA948);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60AA974, func_060AA974);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60AA9EC, func_060AA9EC);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60AAA2C, func_060AAA2C);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60AAA68, func_060AAA68);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60AB088, func_060AB088);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60AB258, func_060AB258);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60AB294, func_060AB294);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60AB6C4, func_060AB6C4);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60ABAA4, func_060ABAA4);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60ABC54, func_060ABC54);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60ABE0C, func_060ABE0C);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60ABE4C, func_060ABE4C);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60ABE94, func_060ABE94);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60ABEF8, func_060ABEF8);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60ABF40, func_060ABF40);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60ABFF0, func_060ABFF0);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60AC09C, func_060AC09C);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60AC148, func_060AC148);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60AC1FC, func_060AC1FC);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60AC458, func_060AC458);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60AC604, func_060AC604);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60AC850, func_060AC850);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60AC90C, func_060AC90C);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60AC9E0, func_060AC9E0);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60ACD98, func_060ACD98);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60ACE84, func_060ACE84);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60ACF8C, func_060ACF8C);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60AD048, func_060AD048);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60AD0E8, func_060AD0E8);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60AD248, func_060AD248);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60AD3A8, func_060AD3A8);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60AD7D8, func_060AD7D8);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60AE014, func_060AE014);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60AE2C8, func_060AE2C8);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60AE3C0, func_060AE3C0);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60AE730, func_060AE730);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60AE8D8, func_060AE8D8);

void func_060AEAB8() {}

INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60AEAC4, func_060AEAC4);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60AEB18, func_060AEB18);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60AEFB4, func_060AEFB4);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60AF17C, func_060AF17C);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60AF444, func_060AF444);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60AFAB4, func_060AFAB4);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60AFBA4, func_060AFBA4);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60B0220, func_060B0220);
// function, bugs
INCLUDE_ASM("asm/saturn/maria/data", d60B0474, d_060B0474);
// function, splitter bugs
INCLUDE_ASM_NO_ALIGN("asm/saturn/maria/data", d60B08DA, d_060B08DA);

void func_060B099C(Entity* self) { DestroyEntity(self); }

void func_060B09B4() {}

s32 func_060B09C0() { return 0; }

INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60B09CC, func_060B09CC);
// function, splitter bugs
INCLUDE_ASM_NO_ALIGN("asm/saturn/maria/data", d60B1872, d_060B1872);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60B18C8, func_060B18C8);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60B199C, func_060B199C);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60B1A58, func_060B1A58);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60B1E78, func_060B1E78);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60B2474, func_060B2474);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60B2604, func_060B2604);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60B295C, func_060B295C);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60B29D4, func_060B29D4);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60B2F8C, func_060B2F8C);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60B2FC8, func_060B2FC8);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60B30BC, func_060B30BC);

void func_060B3678() {}

INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60B3684, func_060B3684);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60B382C, func_060B382C);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60B4470, func_060B4470);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60B44E8, func_060B44E8);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60B4598, func_060B4598);

void func_060B46A0(Entity* self) { DestroyEntity(self); }

INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60B46BC, func_060B46BC);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60B4B80, func_060B4B80);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60B4CF4, func_060B4CF4);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60B5C3C, func_060B5C3C);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60B5E28, func_060B5E28);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60B626C, func_060B626C);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60B668C, func_060B668C);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60B6C94, func_060B6C94);
// function, splitter bugs
INCLUDE_ASM_NO_ALIGN("asm/saturn/maria/data", d60B761E, d_060B761E);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60B776C, func_060B776C);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60B7A48, func_060B7A48);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60B7E08, func_060B7E08);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60B7F50, func_060B7F50);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60B805C, func_060B805C);

void func_060B82AC() {}

INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60B82B8, func_060B82B8);
// function, splitter bugs
INCLUDE_ASM_NO_ALIGN("asm/saturn/maria/data", d60B8666, d_060B8666);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60B868C, func_060B868C);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60B89F0, func_060B89F0);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60B8AC4, func_060B8AC4);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60B8B24, func_060B8B24);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60B9048, func_060B9048);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60B9404, func_060B9404);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60B96C0, func_060B96C0);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60B99A8, func_060B99A8);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60B9B88, func_060B9B88);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60B9D88, func_060B9D88);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60B9FE0, func_060B9FE0);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60BA148, func_060BA148);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60BA32C, func_060BA32C);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60BA4BC, func_060BA4BC);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60BA6E8, func_060BA6E8);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60BA914, func_060BA914);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60BABE0, func_060BABE0);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60BAC78, func_060BAC78);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60BADA8, func_060BADA8);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60BAFF0, func_060BAFF0);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60BB334, func_060BB334);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60BB6E8, func_060BB6E8);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60BB724, func_060BB724);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60BB868, func_060BB868);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60BBEF8, func_060BBEF8);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60BC024, func_060BC024);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60BC0F4, func_060BC0F4);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60BC23C, func_060BC23C);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60BC320, func_060BC320);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60BCBD8, func_060BCBD8);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60BCCE8, func_060BCCE8);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60BCFF4, func_060BCFF4);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60BD0D0, func_060BD0D0);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60BD150, func_060BD150);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60BD244, func_060BD244);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60BD474, func_060BD474);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60BD5F0, func_060BD5F0);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60BD638, func_060BD638);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60BD81C, func_060BD81C);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60BD9E8, func_060BD9E8);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60BDAD0, func_060BDAD0);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60BDC7C, func_060BDC7C);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60BDDA0, func_060BDDA0);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60BDED8, func_060BDED8);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60BE064, func_060BE064);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60BE258, func_060BE258);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60BE308, func_060BE308);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60BE3D4, func_060BE3D4);

// same sequence of funcs as in richter

s32 d_06086390;
void func_060BE414(void) {
    s32* iVar2;
    d_06086390 = 0;
    iVar2 = func_060784A8();
    iVar2[0x4500] = 0xffffffff;
}

INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60BE440, func_060BE440);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60BE54C, func_060BE54C);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60BE618, func_060BE618);

void func_060BE6D4(void) {
    int* iVar2;
    d_06086390 = 4;
    iVar2 = func_060784A8();
    iVar2[0x4500] = 0xffffffff;
}

void func_060BE700(void) {
    int* iVar2;
    d_06086390 = 5;
    iVar2 = func_060784A8();
    iVar2[0x4500] = 0xffffffff;
}

INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60BE72C, func_060BE72C);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60BE854, func_060BE854);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60BE994, func_060BE994);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60BEA54, func_060BEA54);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60BEB74, func_060BEB74);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60BEE30, func_060BEE30);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60BF0F4, func_060BF0F4);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60BF180, func_060BF180);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60BF35C, func_060BF35C);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60BF3D0, func_060BF3D0);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60BF704, func_060BF704);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60BF7B0, func_060BF7B0);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60BFA68, func_060BFA68);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60BFBF8, func_060BFBF8);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60BFD24, func_060BFD24);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60BFE38, func_060BFE38);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60BFECC, func_060BFECC);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60C00B4, func_060C00B4);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60C0428, func_060C0428);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60C0920, func_060C0920);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60C0A5C, func_060C0A5C);
INCLUDE_ASM("asm/saturn/maria/f_nonmat", f60C0AE4, func_060C0AE4);
INCLUDE_ASM("asm/saturn/maria/data", d60C16B8, d_060C16B8);
