#include "stage.h"

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_80191A64);

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_80191B44);

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_80191D00);

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_80191E34);

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_80192104);

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_80193B3C);

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_80193D7C);

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_80193E18);

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_80194214);

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_80194488);

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_801946C4);

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_80194774);

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_801947C8);

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_8019498C);

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_801949E8);

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_80194AA0);

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_80194C24);

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_80194C50);

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_80194F14);

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_80194FF4);

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_801950F8);

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_801961DC);

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_80196238);

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_80196678);

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_8019697C);

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_80196CC8);

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_80196F90);

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", UpdateStageEntities);

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_801972BC);

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_801973C4);

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_801984DC);

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_80198B80);

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_80198C44);

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_80198D5C);

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_80198E74);

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_80198EC0);

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_80198F18);

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_80199014);

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_80199128);

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_80199174);

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_801991CC);

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_801992C8);

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_801993DC);

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_80199554);

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_80199608);

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_8019967C);

s32 func_801996F8(Unkstruct5* arg0) {
    s16 var_v0_2;

    var_v0_2 = D_800733DA - arg0->unk2;
    var_v0_2 = ABS_ALT(var_v0_2);

    if (var_v0_2 >= 0x11) {
        var_v0_2 = 0;
    } else {
        var_v0_2 = D_800733DE - arg0->unk6;
        var_v0_2 = ABS_ALT(var_v0_2);
        var_v0_2 = var_v0_2 < 0x21;
    }

    return var_v0_2;
}

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_80199770);

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_8019A3A8);

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_8019A414);

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_8019A490);

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_8019A4D8);

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_8019A590);

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_8019A6A8);

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_8019A6E4);

s16 func_8019A718(void) {
    s16 var_a0 = D_8006C3B8->posX.Data.high > D_800733DA;

    if (D_8006C3B8->posY.Data.high > D_800733DE) {
        var_a0 |= 2;
    }
    return var_a0;
}

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_8019A75C);

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_8019A78C);

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_8019A7B8);

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_8019AA30);

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_8019AC18);

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_8019AC78);

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_8019ACA4);

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_8019ACC0);

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_8019AD2C);

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_8019AD64);

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_8019ADAC);

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_8019ADF4);

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_8019AE4C);

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_8019AED8);

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_8019AF08);

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_8019AF40);

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_8019AF88);

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_8019AFE8);

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_8019B008);

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_8019B024);

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_8019B0B8);

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_8019B1B4);

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_8019B1DC);

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_8019B304);

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_8019B45C);

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_8019B7A0);

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_8019B858);

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_8019B8DC);

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_8019BA38);

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_8019BAB8);

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_8019BB94);

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_8019BCAC);

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_8019BD50);

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_8019BDA0);

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_8019BDC8);

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_8019C63C);

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_8019C738);

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_8019C7DC);

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_8019CDC4);

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_8019D074);

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_8019DB44);

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_8019DC6C);

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_8019E1C8);

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_8019E2B8);

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_8019E3C8);

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_8019E4F8);

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_8019E5E0);

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_8019E6D0);

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_8019E7C4);

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_8019E9F4);

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_8019EAF0);

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_8019F070);

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_8019F170);

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_8019F23C);

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_8019F304);

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_8019F3BC);

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_8019F594);

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_8019FB74);

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_801A0274);

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_801A046C);

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_801A0564);

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_801A0734);

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_801A13B8);

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_801A174C);

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_801A1BFC);

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_801A1CE8);

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_801A2018);

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_801A2400);

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_801A2550);

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_801A2580);

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_801A25FC);

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_801A2684);

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_801A2764);

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_801A27B8);

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_801A27E4);

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_801A2848);

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_801A2A58);

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_801A2C9C);

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_801A2E20);

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_801A2F10);
