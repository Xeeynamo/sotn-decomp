/*
 * File: 1AC60.c
 * Overlay: RIC
 * Description: Overlay for the character Richter.
 */

#include "common.h"
#include "game.h"
#include "objects.h"
#include "sfx.h"

void func_8015C908(s32 step);
void func_8015C920(s32* unk0);
void func_8015D020(void);
bool func_8015DBB0(s32);
void func_8015C93C(s32 speed);
s32 func_8015C9CC(void);
void func_8015CA84(s32 speed);
void func_8015CD98(s32 accelerationX);
void func_8015CDE0(s32);
void func_8015CE7C(void);
s32 func_8015CF08(void);
s32 func_8015E380(s32);
void func_8015F9F0(Entity* entity);
void func_8015FAB8(Entity*);
Entity* func_801606BC(Entity* entity, u32 arg1, s32 arg2);

extern u16 D_80072F9A; // main.h?
extern s16 D_801545EA[];
extern s16 D_80154604;
extern s16 D_80154606;
extern s8 D_80154688;
extern s32 D_80155368[];
extern s32 D_80155488;
extern s32 D_801554B0;
extern s32 D_801553BC;
extern s32 D_801554C0;
extern s32 D_801554C8;
extern s32 D_801554D0;
extern s32 D_80155528;
extern s32 D_80155670;
extern s32 D_80155750;
extern /*?*/ s32 D_8015591C;
extern /*?*/ s32 D_80155950;
extern s32 D_80174F74;
extern u8 D_80174FAC;
extern u8 D_80174FB0;
extern u8 D_80174FB4;
extern u8 D_80174FB8;
extern u16 D_80175950;
extern u16 D_80175952;
extern u16 D_80175954;
extern s16 D_80175956;
extern s16 D_80175956;

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
