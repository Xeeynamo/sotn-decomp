#include "common.h"
#include "dra.h"

int func_8015DBB0();
void func_8015C93C();
int func_8015C9CC();
void func_8015CD98();
void func_8015CA84();
int func_8015CF08();
int func_8015E380();
void func_8015CDE0(s32);
void func_801606BC(Entity *, s32, s32);

extern s16 D_80072F16; // main.h?
extern u16 D_80072F9A; // main.h?
extern s32 D_801554B0;
extern s32 D_801553BC;
extern s32 D_801554C0;
extern s32 D_801554C8;
extern s32 D_801554D0;
extern s32 D_80155670;
extern /*?*/ s32 D_8015591C;
extern /*?*/ s32 D_80155950;
extern u8 D_80174FAC;
extern u8 D_80174FB0;
extern u8 D_80174FB4;
extern u8 D_80174FB8;
extern u16 D_80175950;
extern u16 D_80175952;
extern u16 D_80175954;
extern s16 D_80175956;
extern s16 D_80175956;

void func_80156C60(Entity *entity) {
    int i, length;
    u32 *ptr;

    if (entity->unk34 & 0x800000) {
        g_pfnFreePolygons(entity->firstPolygonIndex);
    }

    ptr = (u32 *)entity;
    length = sizeof(Entity) / sizeof(u32);
    for (i = 0; i < length; i++)
        *ptr++ = 0;
}

INCLUDE_ASM("asm/ric/nonmatchings/1AC60", func_80156CCC);

INCLUDE_ASM("asm/ric/nonmatchings/1AC60", func_80156DE4);

INCLUDE_ASM("asm/ric/nonmatchings/1AC60", func_80156F40);

INCLUDE_ASM("asm/ric/nonmatchings/1AC60", func_801572A8);

INCLUDE_ASM("asm/ric/nonmatchings/1AC60", func_80157894);

INCLUDE_ASM("asm/ric/nonmatchings/1AC60", func_80157A50);

INCLUDE_ASM("asm/ric/nonmatchings/1AC60", UpdateEntityRichter);

void func_801587C0() { D_80175956 = 0; }

void func_801587D0(void) {
    D_80175956 = 1;
    D_80175950 = D_8007342E;
    D_80175952 = D_800733F1;
    D_80175954 = D_800733EE;
}

void func_80158814(void) {
    D_80175956 = 0;
    D_8007341C = 0;
    D_8007342E = D_80175950;
    D_800733F1 = *(u8 *)&D_80175952;
    D_800733EE = D_80175954;
}

INCLUDE_ASM("asm/ric/nonmatchings/1AC60", func_8015885C);

INCLUDE_ASM("asm/ric/nonmatchings/1AC60", func_80158B04);

INCLUDE_ASM("asm/ric/nonmatchings/1AC60", func_80158BFC);

void func_80158F38(void) {
    if (func_8015DBB0(0x305C) == 0) {
        func_8015C93C(0x2000);
        if (func_8015C9CC() == 0) {
            func_8015CD98(0);
            return;
        }

        if (D_80073406 == 0) {
            func_8015CA84(0x14000);
        }
    }
}

INCLUDE_ASM("asm/ric/nonmatchings/1AC60", func_80158FA4);

INCLUDE_ASM("asm/ric/nonmatchings/1AC60", func_801590A0);

INCLUDE_ASM("asm/ric/nonmatchings/1AC60", func_801595D8);

INCLUDE_ASM("asm/ric/nonmatchings/1AC60", func_80159670);

void func_80159BC8(void) {
    D_8007342A = 0;
    D_80073428 = 0;
    D_80072F64 = 0;
    D_80072F66 = 0;
    D_800733F1 = D_800733F1 & 0xFB;
}

INCLUDE_ASM("asm/ric/nonmatchings/1AC60", func_80159C04);

INCLUDE_ASM("asm/ric/nonmatchings/1AC60", func_80159CE4);

INCLUDE_ASM("asm/ric/nonmatchings/1AC60", func_8015A7D0);

INCLUDE_ASM("asm/ric/nonmatchings/1AC60", func_8015A9B0);

INCLUDE_ASM("asm/ric/nonmatchings/1AC60", func_8015AFE0);

INCLUDE_ASM("asm/ric/nonmatchings/1AC60", func_8015B098);

void func_8015B18C(void) {
    if (D_8007342A < 0) {
        func_8015CD98(0);
        D_80072F66 = 0;
    }

    if ((D_80072F20 & 1) == 0) {
        func_8015CF08();
        D_80072F66 = 0;
    }
}

void func_8015B1E8(void) {
    if (D_80072F6E) {
        func_8015CD98(0);
        D_80072F66 = 0;
    }

    if ((D_80072F20 & 1) == 0) {
        func_8015CF08();
        D_80072F66 = 0;
    }
}

INCLUDE_ASM("asm/ric/nonmatchings/1AC60", func_8015B244);

INCLUDE_ASM("asm/ric/nonmatchings/1AC60", func_8015B348);

INCLUDE_ASM("asm/ric/nonmatchings/1AC60", func_8015B898);

INCLUDE_ASM("asm/ric/nonmatchings/1AC60", func_8015BB80);

INCLUDE_ASM("asm/ric/nonmatchings/1AC60", func_8015BCD0);

INCLUDE_ASM("asm/ric/nonmatchings/1AC60", func_8015BE84);

INCLUDE_ASM("asm/ric/nonmatchings/1AC60", func_8015C178);

INCLUDE_ASM("asm/ric/nonmatchings/1AC60", func_8015C2A8);

INCLUDE_ASM("asm/ric/nonmatchings/1AC60", func_8015C4AC);

INCLUDE_ASM("asm/ric/nonmatchings/1AC60", func_8015C6D4);

void func_8015C908(s32 unk0) {
    D_80073404 = unk0;
    D_80073406 = 0;
}

void func_8015C920(s32 *unk0) {
    D_8006C3B8->unk4C = unk0;
    D_8006C3B8->animationFrameDuration = 0;
    D_8006C3B8->animationFrameIndex = 0;
}

void func_8015C93C(s32 speed) {
    if (D_8006C3B8->accelerationX < 0) {
        D_8006C3B8->accelerationX += speed;
        if (D_8006C3B8->accelerationX > 0) {
            D_8006C3B8->accelerationX = 0;
        }
    } else {
        D_8006C3B8->accelerationX -= speed;
        if (D_8006C3B8->accelerationX < 0)
            D_8006C3B8->accelerationX = 0;
    }
}

void func_8015C984(s32 speed) {
    if (D_8006C3B8->accelerationY < 0) {
        D_8006C3B8->accelerationY += speed;
        if (D_8006C3B8->accelerationY > 0) {
            D_8006C3B8->accelerationY = 0;
        }
    } else {
        D_8006C3B8->accelerationY -= speed;
        if (D_8006C3B8->accelerationY < 0) {
            D_8006C3B8->accelerationY = 0;
        }
    }
}

INCLUDE_ASM("asm/ric/nonmatchings/1AC60", func_8015C9CC);

void func_8015CA84(s32 speed) {
    Entity *entity = D_8006C3B8;
    s32 modX = speed;
    if (entity->unk14 == 1)
        modX = -speed;
    entity->accelerationX = modX;
}

void func_8015CAAC(s32 speed) {
    s32 phi_a0 = speed;
    if (D_8007340A == 1)
        phi_a0 = -speed;
    D_800733E0 = phi_a0;
}

INCLUDE_ASM("asm/ric/nonmatchings/1AC60", func_8015CAD4);

INCLUDE_ASM("asm/ric/nonmatchings/1AC60", func_8015CB58);

void func_8015CC28(void) {
    D_80073513 = 0;
    D_80073512 = 0;
    D_80073511 = 0;
    D_80073510 = 0;
}

void func_8015CC50() { func_8015C908(0xF0); }

void func_8015CC70(s16 arg0) {
    D_80073406 = arg0;
    D_80073404 = 0x0020;
    D_8007342A = 0;
    D_80073428 = 0;
    if (arg0 & 1) {
        D_80073424 = &D_80155950;
    } else {
        D_80073424 = &D_8015591C;
    }
}

void func_8015CCC8(s32 arg0, s32 arg1) {
    func_8015C908(2);
    func_8015C920(&D_801554C0);
    D_800733E0 = arg1;
    D_800733E4 = 0;
    if (arg0 == 1) {
        D_80073424 = &D_801554B0;
        D_80073406 = 4;
    }
    if (arg0 == 2) {
        D_80073424 = &D_801554D0;
        D_80073406 = 1;
    }
    if (arg0 == 3) {
        D_80073424 = &D_801554C8;
        D_80073406 = 4;
    }
}

void func_8015CD98(s32 arg0) {
    D_800733E0 = arg0;
    D_800733E4 = 0;
    D_80072F64 = 0;
    func_8015C908(0);
    func_8015C920(&D_801553BC);
}

INCLUDE_ASM("asm/ric/nonmatchings/1AC60", func_8015CDE0);

void func_8015CE7C(void) {
    if (D_80072F9A != 0) {
        func_8015CDE0(0);
    } else {
        D_80072F64 = 0;
        func_8015C908(0x19);
        func_8015C920(&D_80155670);
        func_8015CA84(0x24000);
        D_80072F16 = 0x28;
        D_800733E4 = 0;
        func_801606BC(D_8006C3B8, 0x50001, 0);
    }
}

INCLUDE_ASM("asm/ric/nonmatchings/1AC60", func_8015CF08);

INCLUDE_ASM("asm/ric/nonmatchings/1AC60", func_8015D020);

INCLUDE_ASM("asm/ric/nonmatchings/1AC60", func_8015D120);

INCLUDE_ASM("asm/ric/nonmatchings/1AC60", func_8015D1D0);

INCLUDE_ASM("asm/ric/nonmatchings/1AC60", func_8015D250);

INCLUDE_ASM("asm/ric/nonmatchings/1AC60", func_8015D3CC);

INCLUDE_ASM("asm/ric/nonmatchings/1AC60", func_8015D678);

void func_8015D9B4() { func_8015C908(0x16); }

INCLUDE_ASM("asm/ric/nonmatchings/1AC60", func_8015D9D4);

INCLUDE_ASM("asm/ric/nonmatchings/1AC60", func_8015DA60);

INCLUDE_ASM("asm/ric/nonmatchings/1AC60", func_8015DB04);

INCLUDE_ASM("asm/ric/nonmatchings/1AC60", func_8015DBB0);

INCLUDE_ASM("asm/ric/nonmatchings/1AC60", func_8015E380);
// same as func_800E2398

void func_8015E420(s32 arg0) {
    while (PadRead(0))
        func_8015E380(arg0);
    while (PadRead(0) == 0)
        func_8015E380(arg0);
}

INCLUDE_ASM("asm/ric/nonmatchings/1AC60", func_8015E484);

INCLUDE_ASM("asm/ric/nonmatchings/1AC60", func_8015E7B4);

INCLUDE_ASM("asm/ric/nonmatchings/1AC60", func_8015E800);

INCLUDE_ASM("asm/ric/nonmatchings/1AC60", func_8015EE28);

INCLUDE_ASM("asm/ric/nonmatchings/1AC60", func_8015F414);

INCLUDE_ASM("asm/ric/nonmatchings/1AC60", func_8015F680);

INCLUDE_ASM("asm/ric/nonmatchings/1AC60", func_8015F8F8);

INCLUDE_ASM("asm/ric/nonmatchings/1AC60", func_8015F96C);

INCLUDE_ASM("asm/ric/nonmatchings/1AC60", func_8015F9F0);

// This function matches with GCC 2.7.2 using -01 Compilation flags
// https://decomp.me/scratch/VaPMV
#ifndef NON_MATCHING
INCLUDE_ASM("asm/ric/nonmatchings/1AC60", func_8015FA5C);
#else
extern s32 D_80154674[];
extern s32 D_80154675[];
extern s32 D_80154676[];
extern s32 D_80154677[];

extern u8 D_80174FAC;
extern u8 D_80174FB0;
extern u8 D_80174FB4;
extern u8 D_80174FB8;

void func_8015FA5C(s32 arg0) {

    D_80174FAC = D_80154674[arg0];
    D_80174FB0 = D_80154675[arg0];
    D_80174FB4 = D_80154676[arg0];
    D_80174FB8 = D_80154677[arg0];
}
#endif

INCLUDE_ASM("asm/ric/nonmatchings/1AC60", func_8015FAB8);

INCLUDE_ASM("asm/ric/nonmatchings/1AC60", func_8015FB84);

INCLUDE_ASM("asm/ric/nonmatchings/1AC60", func_8015FDB0);

INCLUDE_ASM("asm/ric/nonmatchings/1AC60", func_8015FEA8);

INCLUDE_ASM("asm/ric/nonmatchings/1AC60", func_801601DC);

void func_801603B4(void) {}

void func_801603BC(void) {}

INCLUDE_ASM("asm/ric/nonmatchings/1AC60", func_801603C4);

INCLUDE_ASM("asm/ric/nonmatchings/1AC60", func_801606BC);

INCLUDE_ASM("asm/ric/nonmatchings/1AC60", func_80160788);

INCLUDE_ASM("asm/ric/nonmatchings/1AC60", func_80160C38);

INCLUDE_ASM("asm/ric/nonmatchings/1AC60", func_80160D2C);

INCLUDE_ASM("asm/ric/nonmatchings/1AC60", func_80160E4C);

INCLUDE_ASM("asm/ric/nonmatchings/1AC60", func_80160F0C);

INCLUDE_ASM("asm/ric/nonmatchings/1AC60", func_80160FC4);

INCLUDE_ASM("asm/ric/nonmatchings/1AC60", func_8016147C);

INCLUDE_ASM("asm/ric/nonmatchings/1AC60", func_80161C2C);

INCLUDE_ASM("asm/ric/nonmatchings/1AC60", func_80161EF8);

INCLUDE_ASM("asm/ric/nonmatchings/1AC60", func_80161FF0);

INCLUDE_ASM("asm/ric/nonmatchings/1AC60", func_801623E0);

INCLUDE_ASM("asm/ric/nonmatchings/1AC60", func_80162604);

INCLUDE_ASM("asm/ric/nonmatchings/1AC60", func_80162870);

void func_80162C7C(void) {}

INCLUDE_ASM("asm/ric/nonmatchings/1AC60", func_80162C84);

INCLUDE_ASM("asm/ric/nonmatchings/1AC60", func_80162E9C);

INCLUDE_ASM("asm/ric/nonmatchings/1AC60", func_80162EF8);

INCLUDE_ASM("asm/ric/nonmatchings/1AC60", func_801641A0);

INCLUDE_ASM("asm/ric/nonmatchings/1AC60", func_80164444);

INCLUDE_ASM("asm/ric/nonmatchings/1AC60", func_80164DF8);

INCLUDE_ASM("asm/ric/nonmatchings/1AC60", func_801656B0);

INCLUDE_ASM("asm/ric/nonmatchings/1AC60", func_80165DD8);

void func_80166024() {
    D_800733EE = 0x815E;
    D_800733F0 = 0x70;
}

void func_80166044() {
    D_800733EE = 0x8120;
    D_800733F0 = 0;
}

INCLUDE_ASM("asm/ric/nonmatchings/1AC60", func_80166060);

INCLUDE_ASM("asm/ric/nonmatchings/1AC60", func_80166784);

INCLUDE_ASM("asm/ric/nonmatchings/1AC60", func_8016779C);

INCLUDE_ASM("asm/ric/nonmatchings/1AC60", func_80167964);

void func_80167A58(void) {}

void func_80167A60(void) {}

void func_80167A68(void) {}

INCLUDE_ASM("asm/ric/nonmatchings/1AC60", func_80167A70);

INCLUDE_ASM("asm/ric/nonmatchings/1AC60", func_80167EC4);

INCLUDE_ASM("asm/ric/nonmatchings/1AC60", func_801682B4);

INCLUDE_ASM("asm/ric/nonmatchings/1AC60", func_8016840C);

INCLUDE_ASM("asm/ric/nonmatchings/1AC60", func_801684D8);

INCLUDE_ASM("asm/ric/nonmatchings/1AC60", func_80168A20);

INCLUDE_ASM("asm/ric/nonmatchings/1AC60", func_8016902C);

INCLUDE_ASM("asm/ric/nonmatchings/1AC60", func_80169470);

INCLUDE_ASM("asm/ric/nonmatchings/1AC60", func_80169704);

INCLUDE_ASM("asm/ric/nonmatchings/1AC60", func_80169C10);

INCLUDE_ASM("asm/ric/nonmatchings/1AC60", func_80169D74);

INCLUDE_ASM("asm/ric/nonmatchings/1AC60", func_80169F04);

INCLUDE_ASM("asm/ric/nonmatchings/1AC60", func_8016A26C);

INCLUDE_ASM("asm/ric/nonmatchings/1AC60", func_8016A974);

INCLUDE_ASM("asm/ric/nonmatchings/1AC60", func_8016B0C0);

void func_8016B8E8(s32 arg0) {
    D_8006C3B8->unk7C.modeU16 =
        (arg0 << 0x10 >> 0xF) - D_8006C3B8->unk7C.modeU16;
    if (D_8006C3B8->unk82 == 0) {
        D_8006C3B8->unk80++;
        D_8006C3B8->unk82++;
    }
}

void func_8016B92C(s32 arg0) {
    if (D_8006C3B8->unk82 == 0) {
        D_8006C3B8->unk7C.modeU16 =
            (arg0 << 0x10 >> 0xF) - D_8006C3B8->unk7C.modeU16;
        D_8006C3B8->unk80++;
        D_8006C3B8->unk82++;
    }
}

INCLUDE_ASM("asm/ric/nonmatchings/1AC60", func_8016B97C);

INCLUDE_ASM("asm/ric/nonmatchings/1AC60", func_8016C1BC);

INCLUDE_ASM("asm/ric/nonmatchings/1AC60", func_8016C6C4);

INCLUDE_ASM("asm/ric/nonmatchings/1AC60", func_8016C734);

INCLUDE_ASM("asm/ric/nonmatchings/1AC60", func_8016CC74);

INCLUDE_ASM("asm/ric/nonmatchings/1AC60", func_8016D328);

INCLUDE_ASM("asm/ric/nonmatchings/1AC60", func_8016D4D8);

INCLUDE_ASM("asm/ric/nonmatchings/1AC60", func_8016D920);

INCLUDE_ASM("asm/ric/nonmatchings/1AC60", func_8016D9C4);

INCLUDE_ASM("asm/ric/nonmatchings/1AC60", func_8016DF74);

INCLUDE_ASM("asm/ric/nonmatchings/1AC60", func_8016E324);

INCLUDE_ASM("asm/ric/nonmatchings/1AC60", func_8016E46C);

INCLUDE_ASM("asm/ric/nonmatchings/1AC60", func_8016E9E4);

INCLUDE_ASM("asm/ric/nonmatchings/1AC60", func_8016F198);

INCLUDE_ASM("asm/ric/nonmatchings/1AC60", func_8016F6F0);

INCLUDE_ASM("asm/ric/nonmatchings/1AC60", func_80170548);

INCLUDE_ASM("asm/ric/nonmatchings/1AC60", func_801705EC);

INCLUDE_ASM("asm/ric/nonmatchings/1AC60", func_801706C0);

INCLUDE_ASM("asm/ric/nonmatchings/1AC60", func_80170874);

INCLUDE_ASM("asm/ric/nonmatchings/1AC60", func_8017091C);

INCLUDE_ASM("asm/ric/nonmatchings/1AC60", func_80170F64);

INCLUDE_ASM("asm/ric/nonmatchings/1AC60", func_8017161C);

INCLUDE_ASM("asm/ric/nonmatchings/1AC60", func_801719A4);

INCLUDE_ASM("asm/ric/nonmatchings/1AC60", func_80172AE8);

INCLUDE_ASM("asm/ric/nonmatchings/1AC60", func_80172D00);

INCLUDE_ASM("asm/ric/nonmatchings/1AC60", func_8017328C);
