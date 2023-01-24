#include "sel.h"

void func_801B4B9C(Entity* entity, s16 step);
extern u16 D_800737B0;  // g_EntityArray[5].step
extern u16 D_800737D4;  // g_EntityArray[5].animationFrameIndex
extern u8 D_80180538[]; // animation frames
extern u8 D_80180554[]; // more animation frames
extern s32 D_801BC3E8;

// almost matching but there is an inverted condition
#ifndef NON_EQUIVALENT
INCLUDE_ASM("config/../asm/st/sel/nonmatchings/3585C", func_801B585C);
#else
void func_801B585C(u16 arg0) {
    int new_var;
    Entity* e = &g_EntityArray[5];
    Entity* new_var2;
    u16 var_v0;
    switch (D_800737B0) {
    case 0:
        e->animationSet = 1;
        e->posY.i.hi = 0x9F;
        e->zPriority = 0xC0;
        e->animationFrame = 0;
        e->unk5A = 0;
        (*e).unk80.entityPtr = 0;
        e->palette = 0x8100;
        var_v0 = (e->step = e->step + 1);
        break;

    case 1:
        AnimateEntity(D_80180504, e);
        if (D_801BC3E8 & 4) {
            var_v0 = e->step + 1;
            e->step = var_v0;
            break;
        }
        break;

    case 2:
        AnimateEntity(D_80180504, e);
        *((s32*)(&e->unk80.modeS32)) += 0x18000;
        if (e->unk80.modeS16.unk2 >= 0x49) {
            func_801B4B9C(e, 3);
        }
        break;

    case 3:
        if (!(AnimateEntity(D_80180538, e) & 0xFF)) {
            func_801B4B9C(e, 4);
        }
        break;

    case 4:
        AnimateEntity(D_80180554, e);
        if (D_801BC3E8 & 8) {
            func_801B4B9C(e, 5);
        }
        break;

    case 5:
        new_var2 = e;
        e->facing = 1;
        if (!(AnimateEntity(D_80180528, new_var2) & 0xFF)) {
            func_801B4B9C(e, 6);
        }
        new_var = 0xFFFE8000;
        *((s32*)(&e->unk80.modeS32)) += new_var;
        return;

    case 6:
        AnimateEntity(D_80180504, e);
        *((s32*)(&e->unk80.modeS32)) += 0xFFFE8000;
        if (arg0) {
            new_var = e->unk80.modeS16.unk2 < 0x20;
            if (new_var) {
                e->step = 0xFF;
            }
        } else {
            if (e->unk80.modeS16.unk2 < (-0x10)) {
                e->step = 0xFF;
            }
        }
        break;
    }
}
#endif

void func_801B5350(void);
void func_801B54C8(void);
void func_801B5548(void);
void func_801B55C8(void);
void func_801B585C(u16);
extern s8 D_8018BC4A;
extern s8 D_8018BC50;

void func_801B5A7C(void) {
    Entity* e = &g_EntityArray[8];

    switch (e->subId) {
    case 0:
        switch (e->step) {
        case 0:
            D_8018BC4A = 0;
            e->step++;
            break;

        case 1:
            D_801BC3E4 = 1;
            D_801D6B24 = -0x400000;
            e->step++;
            break;

        case 2:
            if (D_801BC3E4 == 0) {
                D_801BC3E8 |= 1;
            }
            if (D_801D6B24 != 0) {
                D_801D6B24 += 0x2000;
            }
            if (D_801BC3E8 & 2) {
                D_801BC3E4 = 1;
                e->step++;
            }
            break;

        case 3:
            do {
                D_800737B0 = 2;
                D_800737D4 = 0;
            } while (0);
            g_EntityArray[5].animationFrameDuration = 0;
            g_EntityArray[5].facing = 1;
            e->step++;
            break;

        case 4:
            if (D_801BC3E4 == 0) {
                D_801BD030 = 1;
            }
            break;
        }

        func_801B5350();
        break;

    case 1:
        switch (e->step) {
        case 0:
            D_8018BC4A = 1;
            e->step++;
            break;

        case 1:
            D_801BC3E4 = 1;
            D_801D6B24 = -0x400000;
            e->step++;
            break;

        case 2:
            if (D_801BC3E4 == 0) {
                D_801BC3E8 |= 5;
                e->step++;
            }
            if (D_801D6B24 != 0) {
                D_801D6B24 += 0x4000;
            }
            break;

        case 3:
            if (D_801D6B24 != 0) {
                D_801D6B24 += 0x4000;
            }
            if (D_801BC3E8 & 2) {
                D_801BC3E4 = 1;
                e->step++;
            }
            break;

        case 4:
            e->step++;
            break;

        case 5:
            if (D_801BC3E4 == 0) {
                D_801BD030 = 1;
            }
            break;
        }

        func_801B585C(1);
        func_801B55C8();
        break;

    case 2:
        switch (e->step) {
        case 0:
            D_8018BC4A = 2;
            D_8018BC50 = 0;
            e->step++;
            break;

        case 1:
            D_801BC3E4 = 1;
            D_801D6B24 = -0x400000;
            e->step++;
            break;

        case 3:
            if (D_801D6B24 != 0) {
                D_801D6B24 += 0x4000;
            }
            if (D_801BC3E8 & 2) {
                D_801BC3E4 = 1;
                e->step++;
            }
            break;

        case 2:
            if (D_801BC3E4 == 0) {
                D_801BC3E8 |= 5;
                e->step++;
            }
            if (D_801D6B24 != 0) {
                D_801D6B24 += 0x4000;
            }
            break;

        case 4:
            e->step++;
            break;

        case 5:
            if (D_801BC3E4 == 0) {
                D_801BD030 = 1;
            }
            break;
        }

        func_801B585C(0);
        func_801B54C8();
        func_801B55C8();
        break;

    case 3:
        switch (e->step) {
        case 0:
            D_8018BC4A = 3;
            e->step++;
            break;

        case 1:
            D_801BC3E4 = 1;
            D_801D6B24 = -0x400000;
            e->step++;
            break;

        case 2:
            if (D_801BC3E4 == 0) {
                e->step++;
            }
            if (D_801D6B24 != 0) {
                D_801D6B24 += 0x4000;
            }
            break;

        case 3:
            if (D_801D6B24 != 0) {
                D_801D6B24 += 0x4000;
                break;
            }
            *(s32*)&e->unk8C.entityPtr = 0x80;
            e->step++;
            break;

        case 4:
            (*((s32*)&e->unk8C.entityPtr))--;
            if (*(s32*)&e->unk8C.entityPtr == 0) {
                D_801BC3E8 |= 1;
                e->step++;
            }
            break;

        case 5:
            if (D_801BC3E8 & 2) {
                D_801BC3E4 = 1;
                e->step++;
            }
            break;

        case 6:
            if (D_801BC3E4 == 0) {
                D_801BD030 = 1;
            }
            break;
        }

        func_801B5548();
        break;

    case 4:
        switch (e->step) {
        case 0:
            D_8018BC4A = 2;
            D_8018BC50 = 1;
            e->step++;
            break;

        case 1:
            D_801BC3E4 = 1;
            D_801D6B24 = -0x400000;
            e->step++;
            break;

        case 2:
            if (D_801BC3E4 == 0) {
                D_801BC3E8 |= 5;
                e->step++;
            }
            if (D_801D6B24 != 0) {
                D_801D6B24 += 0x4000;
            }
            break;

        case 3:
            if (D_801D6B24 != 0) {
                D_801D6B24 += 0x4000;
            }
            if (D_801BC3E8 & 2) {
                D_801BC3E4 = 1;
                e->step++;
            }
            break;

        case 4:
            e->step++;
            break;

        case 5:
            if (D_801BC3E4 == 0) {
                D_801BD030 = 1;
            }
            break;
        }

        func_801B585C(0);
        func_801B54C8();
        func_801B55C8();
        break;
    }
}

void func_801B60D4(void) {
    Entity* ent;
    Entity* ent4;
    s32 i;
    s32 var_v1;

    switch (D_8003C9A4) {
    case 0:
        if (D_8006C3B0 == 0) {
            D_8003C728 = 1;
            if (D_800978B4 == 0) {
                D_8003C100 = 2;
            } else {
                D_8003C100 = 3;
            }
            D_8003C9A4++;
        }
        break;

    case 1:
        func_801B9C80();
        if (D_8003C728 == 0) {
            D_8003C100 = 0;
            func_801B18F4();
        }
        if (D_800978B4 != 0) {
            D_80073060++;
        } else {
            D_80073060 = 0x100;
        }
        D_8003C9A4++;
        break;

    case 2:
        ent = g_EntityArray;
        for (i = 0; i < 9; i++) {
            func_801B4B30(ent);
            ent++;
        }

        D_801D6B24 = 0;
        D_801BD030 = 0;
        g_EntityArray[8].subId = *(u16*)&D_800978B4 - 1;
        g_api.func_800EA5E4(0x16);
        g_api.func_800EA5E4(0);
        g_api.func_800EA5E4(0x8005);
        g_api.func_800EAF28(0x8000);
        D_8003C9A4++;
        break;

    case 3:
        ent4 = &g_EntityArray[4];
        func_801B5A7C();
        func_801B69F8(ent4);
        func_801B4C68();
        func_801B519C();
        func_801B4D78();
        func_801B4DE0();
        ent = ent4 - 1;
        for (i = 3; i < 8; i++) {
            var_v1 = D_801D6B24;
            if (var_v1 < 0) {
                var_v1 += 0xFFFF;
            }
            ent->posX.i.hi = (s16)(var_v1 >> 0x10) + ent->unk80.modeS16.unk2;
            ent++;
        }

        if (D_801BD030 != 0) {
            ent = g_EntityArray;
            for (i = 0; i < 9; i++) {
                func_801B4B30(ent);
                ent++;
            }

            for (i = 0; i < 9; i++) {
                func_801B4B30(ent);
                ent++;
            }

            D_8003C9A4++;
        }
        break;

    case 4:
        ClearImage(&D_8018258C, 0, 0, 0);
        D_8003C9A4++;
        break;

    case 5:
        func_801B1B88();
        D_8003C9A4++;
        break;

    case 6:
        g_api.func_800EA5E4(0);
        D_8003C9A4++;
        break;

    case 7:
        ent4 = &g_EntityArray[4];
        if (func_801B79D4(ent4) != 0) {
            g_EntityArray[1].step = 0;
            D_801BC3E4 = 1;
            D_8003C9A4++;
        }
        break;

    case 8:
        func_801B4FFC();
        if (D_801BC3E4 == 0) {
            D_80073060 += 1;
        }
        break;
    }
}
