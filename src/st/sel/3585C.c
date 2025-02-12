// SPDX-License-Identifier: AGPL-3.0-or-later
#include "sel.h"

void SEL_SetStep(Entity* entity, s16 step);
extern u8 D_80180538[]; // animation frames
extern u8 D_80180554[]; // more animation frames

// Compare to func_801B5350
void func_801B585C(u16 arg0) {
    Entity* self = &g_Entities[UNK_ENTITY_5];

    switch (self->step) {
    case 0:
        self->animSet = ANIMSET_DRA(1);
        self->posY.i.hi = 159;
        self->zPriority = 0xC0;
        self->animCurFrame = 0;
        self->unk5A = 0;
        self->ext.unkSelEnts.unk80.val = 0;
        self->palette = 0x8100;
        self->step++;
        break;

    case 1:
        AnimateEntity(D_80180504, self);
        if (D_801BC3E8 & 4) {
            self->step++;
        }
        break;

    case 2:
        AnimateEntity(D_80180504, self);
        self->ext.unkSelEnts.unk80.val += FIX(1.5);
        if (self->ext.unkSelEnts.unk80.i.hi > 72) {
            SEL_SetStep(self, 3);
        }
        break;

    case 3:
        if (!(AnimateEntity(D_80180538, self) & 0xFF)) {
            SEL_SetStep(self, 4);
        }
        break;

    case 4:
        AnimateEntity(D_80180554, self);
        if (D_801BC3E8 & 8) {
            SEL_SetStep(self, 5);
        }
        break;

    case 5:
        self->facingLeft = 1;
        if (!(AnimateEntity(D_80180528, self) & 0xFF)) {
            SEL_SetStep(self, 6);
        }
        self->ext.unkSelEnts.unk80.val -= FIX(1.5);
        break;

    case 6:
        AnimateEntity(D_80180504, self);
        self->ext.unkSelEnts.unk80.val -= FIX(1.5);
        if (arg0 && self->ext.unkSelEnts.unk80.i.hi < 0x20 ||
            !arg0 && self->ext.unkSelEnts.unk80.i.hi < -0x10) {
            self->step = 255;
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
    s32 i;

    switch (g_GameEngineStep) {
    case 0:
        if (!g_IsUsingCd) {
            D_8003C728 = 1;
            if (D_800978B4 != 0) {
                g_CurrentStream = 3;
            } else {
                g_CurrentStream = 2;
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
        // Important! This loop confirms that SEL uses the first 8
        // entities for its internal uses.
        for (ent = g_Entities, i = 0; i <= 8; i++, ent++) {
            DestroyEntity(ent);
        }

        D_801D6B24 = 0;
        D_801BD030 = 0;
        ent = &g_Entities[8];
        ent->params = D_800978B4 - 1;
        g_api.InitClutAnimation(ANIMSET_DRA(0x16));
        g_api.InitClutAnimation(ANIMSET_DRA(0));
        g_api.InitClutAnimation(ANIMSET_OVL(5));
        g_api.LoadGfxAsync(ANIMSET_OVL(0));
        g_GameEngineStep++;
        break;

    case 3:
        func_801B5A7C();
        ent = &g_Entities[4];
        SEL_EntityCutscene(ent);
        func_801B4C68();
        func_801B519C();
        func_801B4D78();
        func_801B4DE0();
        ent = &g_Entities[3];
        for (i = 3; i < 8; i++, ent++) {
            // This FIX(1) is 0x10000, not sure if it should be FIX(1) since
            // dividing FIX() doesn't make sense.
            ent->posX.i.hi =
                (D_801D6B24 / FIX(1)) + ent->ext.unkSelEnts.unk80.i.hi;
        }

        if (D_801BD030 != 0) {
            // This is kind of weird, we destroy the first 8...
            for (ent = g_Entities, i = 0; i <= 8; i++, ent++) {
                DestroyEntity(ent);
            }
            /// ... and then another 8. Why not just 16 all at once?
            for (i = 0; i <= 8; i++, ent++) {
                DestroyEntity(ent);
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
        g_api.InitClutAnimation(ANIMSET_DRA(0));
        g_GameEngineStep++;
        break;

    case 7:
        ent = &g_Entities[4];
        if (func_801B79D4(ent) != 0) {
            ent = &g_Entities[1];
            ent->step = 0;
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
