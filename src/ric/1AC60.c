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

    if (entity->flags & FLAG_FREE_POLYGONS) {
        g_api.FreePolygons(entity->firstPolygonIndex);
    }

    ptr = (u32*)entity;
    length = sizeof(Entity) / sizeof(u32);
    for (i = 0; i < length; i++)
        *ptr++ = 0;
}

INCLUDE_ASM("asm/us/ric/nonmatchings/1AC60", func_80156CCC);

INCLUDE_ASM("asm/us/ric/nonmatchings/1AC60", func_80156DE4);

INCLUDE_ASM("asm/us/ric/nonmatchings/1AC60", func_80156F40);

INCLUDE_ASM("asm/us/ric/nonmatchings/1AC60", func_801572A8);

INCLUDE_ASM("asm/us/ric/nonmatchings/1AC60", func_80157894);

// https://decomp.me/scratch/hk5zb
// Almost matched, just a jump issue
INCLUDE_ASM("asm/us/ric/nonmatchings/1AC60", func_80157A50);

INCLUDE_ASM("asm/us/ric/nonmatchings/1AC60", UpdateEntityRichter);

void func_801587C0() { D_80175956 = 0; }

void func_801587D0(void) {
    D_80175956 = 1;
    D_80175950 = PLAYER.animCurFrame;
    D_80175952 = PLAYER.unk19;
    D_80175954 = PLAYER.palette;
}

void func_80158814(void) {
    D_80175956 = 0;
    PLAYER.unk44 = 0;
    PLAYER.animCurFrame = D_80175950;
    PLAYER.unk19 = *(u8*)&D_80175952;
    PLAYER.palette = D_80175954;
}

INCLUDE_ASM("asm/us/ric/nonmatchings/1AC60", func_8015885C);

void func_80158B04(s32 arg0) {
    s32 var_s0;

    if (PLAYER.facing != 0) {
        var_s0 = -3;
    } else {
        var_s0 = 3;
    }

    PLAYER.posY.i.hi -= 16;
    PLAYER.posX.i.hi = var_s0 + PLAYER.posX.i.hi;
    func_801606BC(g_CurrentEntity, 0x10004, 0);
    PLAYER.posY.i.hi += 16;
    PLAYER.posX.i.hi = PLAYER.posX.i.hi - var_s0;

    if (arg0 & 1) {
        g_api.func_80102CD8(3);
        g_api.PlaySfx(NA_SE_SECRET_STAIRS);
    }

    if (arg0 & 2) {
        PLAYER.accelerationX = 0;
        PLAYER.accelerationY = 0;
    }
}

void func_80158BFC(void) {
    s32 var_s0;

    if (PLAYER.step < 64) {
        if (D_8015459C != 0) {
            D_8015459C--;
        } else if (D_80097448 >= 49) {
            if (PLAYER.facing != 0) {
                var_s0 = -4;
            } else {
                var_s0 = 4;
            }
            PLAYER.posX.i.hi = var_s0 + PLAYER.posX.i.hi;
            PLAYER.posY.i.hi -= 16;
            func_801606BC(g_CurrentEntity, 0x80004, 0);
            D_8015459C = 0x60;
            PLAYER.posY.i.hi += 16;
            PLAYER.posX.i.hi = PLAYER.posX.i.hi - var_s0;
        }
    }

    if (func_8015DBB0(0x40000 | 0x305C) == false) {
        func_8015C93C(0x2000);
        switch (PLAYER.unk2E) {
        case 0:
            if (func_8015C9CC() == 0) {
                if (D_80072EE8 & 0x1000) {
                    func_8015C920(&D_80155394);
                    PLAYER.unk2E = 1;
                    break;
                }
            } else {
                func_8015CDE0(0);
            }
            break;

        case 1:
            if (func_8015C9CC() != 0) {
                func_8015CDE0(0);
                break;
            } else if (D_80072EE8 & 0x1000) {
                break;
            } else {
                func_8015CD98(0);
                break;
            }

        case 64:
            func_8015CB58(1, 1);
            if (PLAYER.animFrameIdx < 3) {
                func_8015C9CC();
                if (D_80072EE8 & 0x4000) {
                    PLAYER.step = 2;
                    PLAYER.unk4C = &D_801555A8;
                    break;
                }
            }

            if (PLAYER.animFrameDuration < 0) {
                if (D_80072EE8 & 0x80) {
                    D_80072F66 = 2;
                    PLAYER.unk2E++;
                    func_8015C920(&D_80155730);
                    func_801606BC(g_CurrentEntity, 0x11, 0);
                    break;
                }
                D_80072F66 = 0;
                func_8015CD98(0);
            }
            break;

        case 65:
            func_8015CB58(1, 1);
            if (D_80072EE8 & 0x80) {
                break;
            }
            D_80072F66 = 0;
            func_8015CD98(0);
            break;

        case 66:
            func_8015CB58(1, 1);
            if (PLAYER.animFrameIdx < 3) {
                func_8015C9CC();
            }
            if (PLAYER.animFrameDuration < 0) {
                D_80072F66 = 0;
                func_8015CD98(0);
            }
        }
    }
}

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

void func_80158FA4(void) {
    if (D_80072F20.unk7A != 0) {
        func_8015CDE0(0);
        return;
    }
    D_80072F10 = 8;
    *D_80072F02 = 8;

    if (!func_8015DBB0(0x305C)) {
        func_8015C93C(0x2000);
        if (func_8015C9CC() == 0) {
            func_8015CD98(0);
            if (*D_80072F16 == 0) {
                if (!(D_80072F20.pl_vram_flag & 0xC)) {
                    func_8015C920(&D_8015539C);
                    func_801606BC(g_CurrentEntity, 0, 0);
                }
            } else {
                PLAYER.accelerationX = 0;
            }
        } else if (PLAYER.unk2E == 0) {
            func_8015CA84(0x24000);
        }
    }
}

INCLUDE_ASM("asm/us/ric/nonmatchings/1AC60", func_801590A0);

void func_801595D8(void) {
    if (!func_8015DBB0(0x9009)) {
        func_8015C93C(0x1000);
        if (PLAYER.unk2E == 0) {
            if ((D_80072F0A[0] != 0) && (D_80072EEC & 0x40)) {
                func_8015D020();
                return;
            }
            if (func_8015C9CC() != 0) {
                func_8015CA84(0xC000);
            }
        }
    }
}

INCLUDE_ASM("asm/us/ric/nonmatchings/1AC60", func_80159670);

void func_80159BC8(void) {
    PLAYER.animFrameDuration = 0;
    PLAYER.animFrameIdx = 0;
    D_80072F64 = 0;
    D_80072F66 = 0;
    PLAYER.unk19 &= 0xFB;
}

void func_80159C04(void) {
    Entity* entity = PLAYER.unkB8.entityPtr;
    s16 temp_v0;
    s32 var_a0;
    s32 var_a2;

    if (entity->facing != 0) {
        var_a2 = -entity->unk10;
    } else {
        var_a2 = entity->unk10;
    }

    if (PLAYER.facing != 0) {
        var_a0 = -PLAYER.unk10;
    } else {
        var_a0 = PLAYER.unk10;
    }

    temp_v0 = var_a0 + PLAYER.posX.i.hi - entity->posX.i.hi - var_a2;

    if (ABS(temp_v0) < 16) {
        if (entity->accelerationX != 0) {
            if (entity->accelerationX < 0) {
                PLAYER.objectRoomIndex = 0;
                return;
            } else {
                PLAYER.objectRoomIndex = 1;
                return;
            }
        }
    }

    if (temp_v0 < 0) {
        PLAYER.objectRoomIndex = 0;
    } else {
        PLAYER.objectRoomIndex = 1;
    }
}

INCLUDE_ASM("asm/us/ric/nonmatchings/1AC60", func_80159CE4);

// https://decomp.me/scratch/1JWA0
INCLUDE_ASM("asm/us/ric/nonmatchings/1AC60", func_8015A7D0);

INCLUDE_ASM("asm/us/ric/nonmatchings/1AC60", func_8015A9B0);

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
    if ((PLAYER.animCurFrame == 0xB5) && (PLAYER.animFrameDuration == 1)) {
        func_801606BC(g_CurrentEntity, 0x23, 0);
        g_api.PlaySfx(NA_SE_UNK_62F);
    }

    if (PLAYER.animFrameDuration < 0) {
        func_8015CD98(0);
        D_80072F66 = 0;
        func_801606BC(g_CurrentEntity, 0x450021, 0);
        *D_80072F00 = 0x800;
    }

    if (!(D_80072F20.pl_vram_flag & 1)) {
        func_8015CF08();
        D_80072F66 = 0;
        func_801606BC(g_CurrentEntity, 0x450021, 0);
        *D_80072F00 = 0x800;
    }
}

void func_8015B18C(void) {
    if (PLAYER.animFrameDuration < 0) {
        func_8015CD98(0);
        D_80072F66 = 0;
    }

    if ((D_80072F20.pl_vram_flag & 1) == 0) {
        func_8015CF08();
        D_80072F66 = 0;
    }
}

void func_8015B1E8(void) {
    if (D_80072F6E) {
        func_8015CD98(0);
        D_80072F66 = 0;
    }

    if ((D_80072F20.pl_vram_flag & 1) == 0) {
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
    if (!(D_80072F20.pl_vram_flag & 1)) {
        func_8015CF08();
        D_80072F66 = 0;
        D_80072F6E = 1;
        D_80174F74 = 0;
    }
}
