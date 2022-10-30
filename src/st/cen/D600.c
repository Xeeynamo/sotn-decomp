/*
 * File: D600.c
 * Overlay: CEN
 * Description: Center Cube Area (Final Boss)
 */

#include "common.h"
/*
#include "dra.h"


void func_80190E7C(void);
void func_80191280(void);
void func_80193410(void);

s32 g_pStOverlay[] = {
    (void*)func_80190E7C,
    (void*)func_80191280,
    (void*)func_80193410,
};*/

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_8018D600);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_8018D6E0);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_8018D89C);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_8018DB18);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_8018DF0C);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_8018DF60);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_8018E124);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_8018E180);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_8018E238);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_8018E3BC);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_8018E3E8);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_8018E6C4);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_8018E7C8);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_8018F890);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_8018F8EC);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_8018F95C);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_8019007C);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_80190374);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_8019040C);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_801904B8);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_80190540);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_80190A78);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_80190B64);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_80190E4C);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_80190E7C);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_80191178);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_80191280);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_80192398);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_80192A3C);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_80192B00);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_80192C18);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_80192D30);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_80192D7C);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_80192DD4);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_80192ED0);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_80192FE4);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_80193030);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_80193088);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_80193184);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_80193298);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_80193410);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_801934C4);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_80193538);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_801935B4);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_8019362C);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_80194264);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_801942D0);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_8019434C);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_80194394);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_8019444C);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_80194564);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_801945A0);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_801945D4);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_80194618);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_80194648);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_80194674);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_801948EC);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_80194AD4);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_80194B34);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_80194B60);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_80194B7C);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_80194BE8);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_80194C20);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_80194C68);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_80194CB0);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_80194D08);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_80194D94);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_80194DC4);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_80194DFC);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_80194E44);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_80194EA4);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_80194EC4);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_80194EE0);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_80194F74);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_80195070);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_80195098);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_801951C0);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_80195318);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_8019565C);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_80195714);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_80195798);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_801958F4);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_80195974);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_80195A50);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_80195B68);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_80195C0C);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_80195C5C);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_80195C84);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_801964F8);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_801965F4);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_80196698);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_80196C80);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_80196F30);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_80197A00);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_80197B28);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_80198084);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_80198174);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_80198284);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_801983B4);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_8019849C);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_8019858C);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_80198680);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_801988B0);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_801989AC);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_80198F2C);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_8019902C);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_801990F8);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_801991C0);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_80199278);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_80199450);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_80199A30);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_8019A130);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_8019A328);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_8019A420);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_8019A5F0);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_8019B274);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_8019B608);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_8019BAB8);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_8019BBA4);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_8019BED4);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_8019C2BC);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_8019C40C);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_8019C43C);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_8019C4B8);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_8019C540);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_8019C620);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_8019C674);

INCLUDE_ASM("config/../asm/st/cen/nonmatchings/D600", func_8019C6A0);
