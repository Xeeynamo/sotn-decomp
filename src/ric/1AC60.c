#include "common.h"
#include "dra.h"
#include "objects.h"
#include "sfx.h"

extern s16 (*D_8003C890)(s16);
void func_8015D020();
bool func_8015DBB0();
void func_8015C93C();
s32 func_8015C9CC();
void func_8015CA84();
void func_8015CD98();
void func_8015CDE0(s32);
s32 func_8015CF08();
s32 func_8015E380();
void func_8015F9F0(Entity* entity);
Entity* func_801606BC(Entity* entity, u32 arg1, s32 arg2);

extern u16 D_80072F9A; // main.h?
extern s16 D_801545EA[];
extern s16 D_80154604;
extern s16 D_80154606;
extern s8 D_80154688;
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

void func_80156C60(Entity* entity) {
    s32 i;
    s32 length;
    u32* ptr;

    if (entity->unk34 & 0x800000) {
        g_pfnFreePolygons(entity->firstPolygonIndex);
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

INCLUDE_ASM("asm/ric/nonmatchings/1AC60", func_8015AFE0);

void func_8015B098(void) {
    if ((g_EntityArray[PLAYER_CHARACTER].animationFrame == 0xB5) &&
        (g_EntityArray[PLAYER_CHARACTER].animationFrameDuration == 1)) {
        func_801606BC(g_CurrentEntity, 0x23, 0);
        g_pfnPlaySfx(NA_SE_UNK_62F);
    }

    if (g_EntityArray[PLAYER_CHARACTER].animationFrameDuration < 0) {
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
    PLAYER.step = unk0;
    PLAYER.unk2E = 0;
}

void func_8015C920(s32* unk0) {
    g_CurrentEntity->unk4C = unk0;
    g_CurrentEntity->animationFrameDuration = 0;
    g_CurrentEntity->animationFrameIndex = 0;
}

void func_8015C93C(s32 speed) {
    if (g_CurrentEntity->accelerationX < 0) {
        g_CurrentEntity->accelerationX += speed;
        if (g_CurrentEntity->accelerationX > 0) {
            g_CurrentEntity->accelerationX = 0;
        }
    } else {
        g_CurrentEntity->accelerationX -= speed;
        if (g_CurrentEntity->accelerationX < 0)
            g_CurrentEntity->accelerationX = 0;
    }
}

void func_8015C984(s32 speed) {
    if (g_CurrentEntity->accelerationY < 0) {
        g_CurrentEntity->accelerationY += speed;
        if (g_CurrentEntity->accelerationY > 0) {
            g_CurrentEntity->accelerationY = 0;
        }
    } else {
        g_CurrentEntity->accelerationY -= speed;
        if (g_CurrentEntity->accelerationY < 0) {
            g_CurrentEntity->accelerationY = 0;
        }
    }
}

INCLUDE_ASM("asm/ric/nonmatchings/1AC60", func_8015C9CC);

void func_8015CA84(s32 speed) {
    s32 speed;

    if (g_CurrentEntity->facing == 1)
        speed = -speed;
    g_CurrentEntity->accelerationX = speed;
}

void func_8015CAAC(s32 speed) {
    s32 speed;

    if (PLAYER.objectRoomIndex == 1)
        speed = -speed;
    PLAYER.accelerationX = speed;
}

void func_8015CAD4(s32 arg0, s16 arg1) {
    if (arg0 == 0) {
        func_801606BC(g_CurrentEntity, 0x15002C, 0);
        if (arg1 >= D_80072F1A[0]) {
            D_80072F1A[0] = arg1;
        }
    } else if (D_80072F1C[0] <= arg1) {
        D_80072F1C[0] = arg1;
    }
}

INCLUDE_ASM("asm/ric/nonmatchings/1AC60", func_8015CB58);

void func_8015CC28(void) {
    Entity* entity = &g_EntityArray[UNK_ENTITY_1];

    entity->unk7E.modeU8.unk1 = 0;
    entity->unk7E.modeU8.unk0 = 0;
    entity->unk7C.modeU8.unk1 = 0;
    entity->unk7C.modeU8.unk0 = 0;
}

void func_8015CC50() { func_8015C908(0xF0); }

void func_8015CC70(s16 arg0) {
    PLAYER.unk2E = arg0;
    PLAYER.step = 0x0020;
    PLAYER.animationFrameDuration = 0;
    PLAYER.animationFrameIndex = 0;
    if (arg0 & 1) {
        PLAYER.unk4C = &D_80155950;
    } else {
        PLAYER.unk4C = &D_8015591C;
    }
}

void func_8015CCC8(s32 arg0, s32 arg1) {
    func_8015C908(2);
    func_8015C920(&D_801554C0);
    PLAYER.accelerationX = arg1;
    PLAYER.accelerationY = 0;
    if (arg0 == 1) {
        PLAYER.unk4C = &D_801554B0;
        PLAYER.unk2E = 4;
    }
    if (arg0 == 2) {
        PLAYER.unk4C = &D_801554D0;
        PLAYER.unk2E = 1;
    }
    if (arg0 == 3) {
        PLAYER.unk4C = &D_801554C8;
        PLAYER.unk2E = 4;
    }
}

void func_8015CD98(s32 accelerationX) {
    PLAYER.accelerationX = accelerationX;
    PLAYER.accelerationY = 0;
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
        D_80072F16[0] = 0x28;
        PLAYER.accelerationY = 0;
        func_801606BC(g_CurrentEntity, 0x50001, 0);
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

// same as func_800E2398
INCLUDE_ASM("asm/ric/nonmatchings/1AC60", func_8015E380);

void func_8015E420(s32 arg0) {
    while (PadRead(0))
        func_8015E380(arg0);
    while (PadRead(0) == 0)
        func_8015E380(arg0);
}

INCLUDE_ASM("asm/ric/nonmatchings/1AC60", func_8015E484);

void func_8015E7B4(Unkstruct_8010BF64* arg0) { // !FAKE:
    s32 temp = D_80154604;

    arg0->unk14 = temp;
    arg0->unk1C = temp = D_80154606;
    arg0->unk18 = D_801545EA[8] - 1;
    arg0->unk20 = D_801545EA[0] + 1;
}

INCLUDE_ASM("asm/ric/nonmatchings/1AC60", func_8015E800);

INCLUDE_ASM("asm/ric/nonmatchings/1AC60", func_8015EE28);

INCLUDE_ASM("asm/ric/nonmatchings/1AC60", func_8015F414);

INCLUDE_ASM("asm/ric/nonmatchings/1AC60", func_8015F680);

Entity* func_8015F8F8(s16 entityIndex, s16 arg1) {
    Entity* entity = &g_EntityArray[entityIndex];
    s16 var_a0 = entityIndex;

    if (entityIndex < arg1) {
        while (var_a0 < arg1) {
            if (entity->objectId == ENTITY_UNALLOCATED) {
                return entity;
            }
            var_a0++;
            entity++;
        }
    }
    return NULL;
}

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

// aspsx
// https://decomp.me/scratch/bRvg6
#ifndef NON_MATCHING
INCLUDE_ASM("asm/ric/nonmatchings/1AC60", func_8015FAB8);
#else
void func_8015FAB8(Entity* entity) {
    u16 var_v0;
    s32 temp;
    Unkstruct_8011A290* temp_v1 = (entity->unkB0 * 0x14) + (&D_80154688);

    if ((*D_80072F1A) != NULL) {
        var_v0 = temp_v1->sp10 * 2;
    } else {
        var_v0 = temp_v1->sp10;
    }

    entity->unk40 = var_v0;
    entity->unk42 = temp_v1->sp14;
    entity->unk3C = temp_v1->sp1C;
    temp = entity->unk40;
    entity->unk49 = temp_v1->sp17;
    entity->unk58 = temp_v1->sp18;
    entity->unk6A = temp_v1->sp1E;
    entity->objectRoomIndex = temp_v1->sp22;
    do {
    } while (0);
    entity->unk40 = D_8003C890(temp);
    func_8015F9F0(entity);
}
#endif

INCLUDE_ASM("asm/ric/nonmatchings/1AC60", func_8015FB84);

INCLUDE_ASM("asm/ric/nonmatchings/1AC60", func_8015FDB0);

INCLUDE_ASM("asm/ric/nonmatchings/1AC60", func_8015FEA8);

INCLUDE_ASM("asm/ric/nonmatchings/1AC60", func_801601DC);

void func_801603B4(void) {}

void func_801603BC(void) {}

INCLUDE_ASM("asm/ric/nonmatchings/1AC60", func_801603C4);

Entity* func_801606BC(Entity* srcEntity, u32 arg1, s32 arg2) {
    /**
     * arg2 is unused, but needed to match other functions that call
     * this function, probably part of the code for a debug build
     */
    Entity* entity = func_8015F8F8(8, 0x10);

    if (entity != NULL) {
        func_80156C60(entity);
        entity->objectId = ENTITY_BREAKABLE;
        entity->unk8C.entityPtr = srcEntity;
        entity->posX.value = srcEntity->posX.value;
        entity->posY.value = srcEntity->posY.value;
        entity->facing = srcEntity->facing;
        entity->zPriority = srcEntity->zPriority;
        entity->subId = arg1 & 0xFFF;
        entity->unkA0 = (arg1 >> 8) & 0xFF00;

        if (srcEntity->unk34 & 0x10000) {
            entity->unk34 |= 0x10000;
        }
    } else {
        return NULL;
    }
    return entity;
}

INCLUDE_ASM("asm/ric/nonmatchings/1AC60", func_80160788);

// move a0,s0
#ifndef NON_MATCHING
INCLUDE_ASM("asm/ric/nonmatchings/1AC60", func_80160C38);
#else
void func_80160C38(Entity* entity) {
    if (PLAYER.step == ENTITY_STEP_17) {
        entity->posX.Data.high = PLAYER.posX.Data.high;
        entity->posY.Data.high = PLAYER.posY.Data.high;
        entity->facing = PLAYER.facing;
        if (entity->step == ENTITY_STEP_0) {
            entity->unk34 = 0x04060000;
            entity->unk10 = 0x14;
            entity->unk12 = 0xC;
            entity->hitboxHeight = 9;
            entity->hitboxWidth = 9;
            entity->unkB0 = 0x12;
            func_8015FAB8(entity);
            entity->unk7C.modeS16 = entity->unk3C;
            entity->step++;
        }
        entity->unk3C = entity->unk7C.modeS16;
        if (PLAYER.animationFrameIndex < 2) {
            entity->unk3C = 0;
        }
        if (PLAYER.animationFrameIndex >= 8) {
            func_80156C60(entity);
        }
    } else {
        func_80156C60(entity);
    }
}
#endif

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
    PLAYER.palette = 0x815E;
    PLAYER.blendMode = 0x70;
}

void func_80166044() {
    PLAYER.palette = 0x8120;
    PLAYER.blendMode = 0;
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
    g_CurrentEntity->unk7C.modeS16 =
        (arg0 << 0x10 >> 0xF) - g_CurrentEntity->unk7C.modeS16;
    if (g_CurrentEntity->unk80.modeS16.unk2 == 0) {
        g_CurrentEntity->unk80.modeS16.unk0++;
        g_CurrentEntity->unk80.modeS16.unk2++;
    }
}

void func_8016B92C(s16 arg0) {
    if (g_CurrentEntity->unk80.modeS16.unk2 == 0) {
        g_CurrentEntity->unk7C.modeS16 =
            (arg0 * 2) - g_CurrentEntity->unk7C.modeS16;
        g_CurrentEntity->unk80.modeS16.unk0++;
        g_CurrentEntity->unk80.modeS16.unk2++;
    }
}

INCLUDE_ASM("asm/ric/nonmatchings/1AC60", func_8016B97C);

INCLUDE_ASM("asm/ric/nonmatchings/1AC60", func_8016C1BC);

s32 func_8016C6C4(Unkstruct_80128BBC* arg0, u8 value) {
    u8 ret = 0;
    s32 i;
    s32 j;
    Unkstruct_80128BBC_Sub* temp = arg0->unk04;

    for (i = 0; i < 4; i++, temp++) {
        for (j = 0; j < 3; j++) {
            temp->unk00[j] -= value;

            if (temp->unk00[j] < 16) {
                temp->unk00[j] = 16;
            } else {
                ret |= 1;
            }
        }
    }
    return ret;
}

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

void func_80172AE8(Entity* entity) {
    POLY_GT4* poly;
    s32 ret;

    switch (entity->step) {
    case ENTITY_STEP_0:
        ret = D_8003C7B8(4, 1);
        entity->firstPolygonIndex = ret;
        if (entity->firstPolygonIndex != -1) {
            entity->unk34 = 0x04820000;
            poly = &D_80086FEC[entity->firstPolygonIndex];
            poly->tpage = 0x1C;
            poly->clut = 0x19D;
            poly->u2 = 0x20;
            poly->u0 = 0x20;
            poly->u3 = 0x30;
            poly->u1 = 0x30;
            poly->v1 = 0;
            poly->v0 = 0;
            poly->v3 = 0x10;
            poly->v2 = 0x10;
            poly->x0 = poly->x2 = entity->posX.Data.high - 8;
            poly->x1 = poly->x3 = entity->posX.Data.high + 8;
            poly->y0 = poly->y1 = entity->posY.Data.high - 8;
            poly->y2 = poly->y3 = entity->posY.Data.high + 8;
            poly->pad2 = entity->zPriority;
            poly->pad3 = 0x115;
            entity->unk7E.modeU16 = 0x60U;
            entity->step++;
        } else {
            func_80156C60(entity);
            return;
        }
        break;

    case ENTITY_STEP_1:
        if (++entity->unk7C.modeS16 > 5) {
            entity->step++;
        }
        entity->unk7E.modeU16 -= 8;
        break;

    case ENTITY_STEP_2:
        func_80156C60(entity);
        return;

    default:
        break;
    }
    poly = &D_80086FEC[entity->firstPolygonIndex];
    poly->r0 = poly->r1 = poly->r2 = poly->r3 = poly->g0 = poly->g1 = poly->g2 =
        poly->g3 = poly->b0 = poly->b1 = poly->b2 = poly->b3 =
            entity->unk7E.modeU8.unk0;
}

INCLUDE_ASM("asm/ric/nonmatchings/1AC60", func_80172D00);

INCLUDE_ASM("asm/ric/nonmatchings/1AC60", func_8017328C);
