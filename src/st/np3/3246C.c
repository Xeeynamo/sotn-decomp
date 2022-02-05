#include "common.h"
#include "dra.h"

extern s16 D_80181A50[];

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801B246C);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801B2540);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801B26FC);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801B2830);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801B28E4);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801B2C20);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801B2F30);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801B32A8);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801B3704);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801B39CC);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801B3D24);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801B3E84);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801B4004);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801B40F8);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801B44B4);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801B4558);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801B4680);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801B4940);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801B4BE8);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801B4D60);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801B5108);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801B5488);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801B560C);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801B5790);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801B5C5C);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801B5DE8);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801B5E98);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801B5F60);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801B6084);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801B644C);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801B653C);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801B65FC);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801B6990);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801B75EC);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801B7798);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801B78BC);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801B8CC0);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801B8D84);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801B8E94);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801B90BC);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801B90EC);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801B93E8);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801B94F0);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801BA608);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801BACAC);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801BAD70);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801BAE88);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801BAFA0);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801BAFEC);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801BB044);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801BB140);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801BB254);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801BB2A0);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801BB2F8);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801BB3F4);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", LoadObjLayout);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801BB680);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801BB734);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801BB7A8);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801BB824);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801BB89C);

void func_801BC4D4(Entity* item) {
    int i, length;
    u32* ptr;

    if (item->unk34 & 0x800000) {
        D_8003C7B4(item->unk64);
    }

    ptr = item;
    length = sizeof(Entity) / sizeof(s32);
    for (i = 0; i < length; i++)
        *ptr++ = 0;
}

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801BC540);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801BC5BC);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801BC604);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801BC6BC);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801BC7D4);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801BC810);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801BC844);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801BC888);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801BC8B8);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801BC8E4);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801BCB5C);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801BCD44);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801BCDA4);

#ifndef NON_MATCHING
INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801BCDD0);
#else
s16 func_801BCDD0(s32 arg0) {
    return D_80181A50[arg0 & 0xFF];
}
#endif

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801BCDEC);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801BCE58);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801BCE90);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801BCED8);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801BCF20);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801BCF78);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801BD004);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801BD034);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801BD06C);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801BD0B4);

void func_801BD114(s32 arg0) {
    D_8006C3B8->unk2C = (s16) (arg0 & 0xFF);
    D_8006C3B8->unk2E = 0;
    D_8006C3B8->unk50 = 0;
    D_8006C3B8->unk52 = 0;
}

void func_801BD134(s32 arg0) {
    D_8006C3B8->unk2E = (s16) (arg0 & 0xFF);
    D_8006C3B8->unk50 = 0;
    D_8006C3B8->unk52 = 0;
}

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801BD150);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801BD1E4);

#ifndef NON_MATCHING
INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801BD2E0);
#else
void func_801BD2E0(Entity* arg0) {
    if (arg0->unk2C == 0) {
        arg0->unk2C++;
    }
}
#endif

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801BD308);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801BD430);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801BD588);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801BD8CC);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801BD984);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801BDA08);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801BDB64);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801BDBE4);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801BDCC0);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801BDDD8);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801BDE7C);

void func_801BDECC(void) {
    func_801BC4D4(D_8006C3B8);
}

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801BDEF4);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801BE768);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801BE864);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801BE908);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801BEEF0);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801BF1A0);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801BFC70);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801BFD98);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801C02F4);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801C03E4);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801C04F4);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801C0624);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801C070C);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801C07FC);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801C08F0);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801C0B20);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801C0C1C);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801C119C);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801C129C);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801C1368);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801C1430);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801C14E8);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801C16C0);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801C1CA0);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801C23A0);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801C2598);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801C2690);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801C2860);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801C34E4);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801C3878);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801C3D28);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801C3E14);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801C4144);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801C424C);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801C4DCC);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801C56D8);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801C5BC4);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801C5F58);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801C61B4);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801C6458);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801C6564);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801C7650);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801C7880);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801C7954);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801C7D80);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801C7E18);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801C8010);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801C80DC);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801C8238);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801C8DF0);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801C8F54);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801C8FEC);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801C90E8);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801C91C4);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801C9874);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801C997C);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801C9BC8);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801C9E28);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801C9F98);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801CA498);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801CA654);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801CAE0C);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801CB018);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801CBF18);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801CC2E0);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801CD540);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801CD620);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801CD658);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801CD734);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801CD78C);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801CD83C);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801CD91C);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801CDA14);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801CDA6C);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801CDAC8);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801CDC80);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801CDD00);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801CDD80);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801CDE10);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801CDE88);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801CDF1C);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801CDFD8);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801CE04C);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801CE120);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801CE1E8);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801CE228);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801CE258);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801CE2CC);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801CE3FC);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801CE4CC);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801CE69C);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801CF254);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801CF5B8);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801CF778);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801CF7A0);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801CF94C);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801D0730);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801D0A00);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801D0B40);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801D0B78);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801D0D40);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801D1BB8);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801D1F38);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801D2320);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801D2470);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801D24A0);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801D251C);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801D25A4);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801D2684);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801D26D8);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801D2704);
