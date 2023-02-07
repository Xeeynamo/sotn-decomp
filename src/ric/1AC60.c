/*
 * File: 1AC60.c
 * Overlay: RIC
 * Description: Overlay for the character Richter.
 */

#include "ric.h"

void func_80156C60(Entity* entity) {
    s32 i;
    s32 length;
    u32* ptr;

    if (entity->unk34 & 0x800000) {
        g_api.FreePolygons(entity->firstPolygonIndex);
    }

    ptr = (u32*)entity;
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
    D_80175950 = PLAYER.animationFrame;
    D_80175952 = PLAYER.unk19;
    D_80175954 = PLAYER.palette;
}

void func_80158814(void) {
    D_80175956 = 0;
    PLAYER.unk44 = 0;
    PLAYER.animationFrame = D_80175950;
    PLAYER.unk19 = *(u8*)&D_80175952;
    PLAYER.palette = D_80175954;
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

        if (PLAYER.unk2E == 0) {
            func_8015CA84(0x14000);
        }
    }
}

INCLUDE_ASM("asm/ric/nonmatchings/1AC60", func_80158FA4);

INCLUDE_ASM("asm/ric/nonmatchings/1AC60", func_801590A0);

void func_801595D8(void) {
    if (!func_8015DBB0(0x9009)) {
        func_8015C93C(0x1000);
        if (PLAYER.unk2E == 0) {
            if ((D_80072F0A != 0) && (D_80072EEC & 0x40)) {
                func_8015D020();
                return;
            }
            if (func_8015C9CC() != 0) {
                func_8015CA84(0xC000);
            }
        }
    }
}

INCLUDE_ASM("asm/ric/nonmatchings/1AC60", func_80159670);

void func_80159BC8(void) {
    PLAYER.animationFrameDuration = 0;
    PLAYER.animationFrameIndex = 0;
    D_80072F64 = 0;
    D_80072F66 = 0;
    PLAYER.unk19 &= 0xFB;
}

INCLUDE_ASM("asm/ric/nonmatchings/1AC60", func_80159C04);

INCLUDE_ASM("asm/ric/nonmatchings/1AC60", func_80159CE4);

INCLUDE_ASM("asm/ric/nonmatchings/1AC60", func_8015A7D0);

INCLUDE_ASM("asm/ric/nonmatchings/1AC60", func_8015A9B0);

void func_8015AFE0(void) {
    if (PLAYER.unk2E == 0) {
        PLAYER.accelerationY += 0x3800;
        if (PLAYER.accelerationY > 0) {
            PLAYER.accelerationY = 0;
            PLAYER.unk2E = 1;
        }
    } else if (D_80072F6E != 0) {
        D_80072F66 = 0;
        func_8015C908(4);
        func_8015C920(&D_80155528);
        D_80072F64 = 0;
    }
    if (D_80072F92 != 0) {
        PLAYER.accelerationY = 0;
    }
}

void func_8015B098(void) {
    if ((PLAYER.animationFrame == 0xB5) &&
        (PLAYER.animationFrameDuration == 1)) {
        func_801606BC(g_CurrentEntity, 0x23, 0);
        g_api.PlaySfx(NA_SE_UNK_62F);
    }

    if (PLAYER.animationFrameDuration < 0) {
        func_8015CD98(0);
        D_80072F66 = 0;
        func_801606BC(g_CurrentEntity, 0x450021, 0);
        *D_80072F00 = 0x800;
    }

    if (!(D_80072F20 & 1)) {
        func_8015CF08();
        D_80072F66 = 0;
        func_801606BC(g_CurrentEntity, 0x450021, 0);
        *D_80072F00 = 0x800;
    }
}

void func_8015B18C(void) {
    if (PLAYER.animationFrameDuration < 0) {
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

void func_8015B244(void) {
    if (PLAYER.unk2E == 0) {
        D_80174F74 = 0x200;
        PLAYER.unk2E++;
    } else {
        func_8015C9CC();
        D_80174F74--;
        if (D_80174F74 == 0) {
            D_80072F66 = 0;
            func_8015CD98(0);
            D_80072F6E = 1;
        }
    }
    if (D_80072EEC & 0x40) {
        func_8015D020();
        D_80072F66 = 0;
        D_80072F6E = 1;
        D_80174F74 = 0;
    }
    if (!(D_80072F20 & 1)) {
        func_8015CF08();
        D_80072F66 = 0;
        D_80072F6E = 1;
        D_80174F74 = 0;
    }
}
