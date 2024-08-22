// SPDX-License-Identifier: AGPL-3.0-or-later
#include "sel.h"

void func_801B4B9C(Entity* entity, s16 step);
extern u8 D_80180538[]; // animation frames
extern u8 D_80180554[]; // more animation frames

void func_801B585C(u16 arg0) {
    Entity* e = &g_Entities[UNK_ENTITY_5];

    switch (e->step) {
    case 0:
        e->animSet = ANIMSET_DRA(1);
        e->posY.i.hi = 159;
        e->zPriority = 0xC0;
        e->animCurFrame = 0;
        e->unk5A = 0;
        e->ext.generic.unk80.entityPtr = NULL;
        e->palette = 0x8100;
        e->step++;
        break;

    case 1:
        AnimateEntity(D_80180504, e);
        if (D_801BC3E8 & 4) {
            e->step++;
        }
        break;

    case 2:
        AnimateEntity(D_80180504, e);
        e->ext.generic.unk80.modeS32 += 0x18000;
        if (e->ext.generic.unk80.modeS16.unk2 >= 0x49) {
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
        e->facingLeft = 1;
        if (!(AnimateEntity(D_80180528, e) & 0xFF)) {
            func_801B4B9C(e, 6);
        }
        e->ext.generic.unk80.modeS32 += 0xFFFE8000;
        break;

    case 6:
        AnimateEntity(D_80180504, e);
        e->ext.generic.unk80.modeS32 += 0xFFFE8000;
        if (arg0 && e->ext.generic.unk80.modeS16.unk2 < 0x20 ||
            !arg0 && e->ext.generic.unk80.modeS16.unk2 < -0x10) {
            e->step = 255;
        }
        break;
    }
}

void func_801B5350(void);
void func_801B54C8(void);
void func_801B5548(void);
void func_801B55C8(void);
void func_801B585C(u16);
extern s8 D_8018BC4A;
extern s8 D_8018BC50;

void func_801B5A7C(void) {
    // Not sure where this entity is initialized...
    Entity* e = &g_Entities[8];

    switch (e->params) {
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
            g_Entities[5].step = 2;
            g_Entities[5].animFrameIdx = 0;
            g_Entities[5].animFrameDuration = 0;
            g_Entities[5].facingLeft = 1;
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
            e->ext.unkSelEnts.unk8C = 0x80;
            e->step++;
            break;

        case 4:
            e->ext.unkSelEnts.unk8C--;
            if (e->ext.unkSelEnts.unk8C == 0) {
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

    switch (g_GameEngineStep) {
    case 0:
        if (!g_IsUsingCd) {
            D_8003C728 = 1;
            if (D_800978B4 == 0) {
                g_CurrentStream = 2;
            } else {
                g_CurrentStream = 3;
            }
            g_GameEngineStep++;
        }
        break;

    case 1:
        func_801B9C80();
        if (D_8003C728 == 0) {
            g_CurrentStream = 0;
            func_801B18F4();
        }
        if (D_800978B4 != 0) {
            g_GameStep++;
        } else {
            g_GameStep = 0x100;
        }
        g_GameEngineStep++;
        break;

    case 2:
        ent = g_Entities;
        for (i = 0; i < 9; i++) {
            DestroyEntity(ent);
            ent++;
        }

        D_801D6B24 = 0;
        D_801BD030 = 0;
        g_Entities[8].params = D_800978B4 - 1;
        g_api.func_800EA5E4(ANIMSET_DRA(0x16));
        g_api.func_800EA5E4(ANIMSET_DRA(0));
        g_api.func_800EA5E4(ANIMSET_OVL(5));
        g_api.LoadGfxAsync(ANIMSET_OVL(0));
        g_GameEngineStep++;
        break;

    case 3:
        ent4 = &g_Entities[4];
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
            ent->posX.i.hi =
                (s16)(var_v1 >> 0x10) + ent->ext.generic.unk80.modeS16.unk2;
            ent++;
        }

        if (D_801BD030 != 0) {
            ent = g_Entities;
            for (i = 0; i < 9; i++) {
                DestroyEntity(ent);
                ent++;
            }

            for (i = 0; i < 9; i++) {
                DestroyEntity(ent);
                ent++;
            }

            g_GameEngineStep++;
        }
        break;

    case 4:
        ClearImage(&D_8018258C, 0, 0, 0);
        g_GameEngineStep++;
        break;

    case 5:
        SetTitleDisplayBuffer256();
        g_GameEngineStep++;
        break;

    case 6:
        g_api.func_800EA5E4(ANIMSET_DRA(0));
        g_GameEngineStep++;
        break;

    case 7:
        ent4 = &g_Entities[4];
        if (func_801B79D4(ent4) != 0) {
            g_Entities[1].step = 0;
            D_801BC3E4 = 1;
            g_GameEngineStep++;
        }
        break;

    case 8:
        func_801B4FFC();
        if (D_801BC3E4 == 0) {
            g_GameStep++;
        }
        break;
    }
}
