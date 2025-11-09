// SPDX-License-Identifier: AGPL-3.0-or-later
#include "sel.h"

extern RECT D_8018258C;
extern u32 D_801BC3E8;
extern u32 D_801BD030;
extern s8 D_8018BC4A;
extern s8 D_8018BC50;

// DATA
static u8 D_801804E0[] = {
    0x02, 0x19, 0x02, 0x1A, 0x02, 0x1B, 0x02, 0x1C, 0x02, 0x1D, 0x02, 0x1E,
    0x02, 0x1F, 0x02, 0x20, 0x02, 0x21, 0x02, 0x22, 0x02, 0x23, 0x02, 0x24,
    0x02, 0x25, 0x02, 0x26, 0x02, 0x27, 0x02, 0x28, 0xFF, 0x00};
static u8 D_80180504[] = {
    0x04, 0x29, 0x04, 0x2A, 0x04, 0x2B, 0x04, 0x2C, 0x04, 0x2D, 0x04, 0x2E,
    0x04, 0x2F, 0x04, 0x30, 0x04, 0x31, 0x04, 0x32, 0x04, 0x33, 0x04, 0x34,
    0x04, 0x35, 0x04, 0x36, 0x04, 0x37, 0x04, 0x38, 0x00, 0x00};
static u8 D_80180528[] = {0x04, 0x39, 0x04, 0x3A, 0x04, 0x3B, 0x04, 0x3C,
                          0x04, 0x3D, 0x04, 0x3E, 0x04, 0x3F, 0xFF, 0x00};
static u8 D_80180538[] = {
    0x04, 0x43, 0x04, 0x44, 0x04, 0x45, 0x04, 0x46, 0x04, 0x47,
    0x04, 0x48, 0x04, 0x49, 0x04, 0x4A, 0x04, 0x4B, 0x04, 0x4C,
    0x04, 0x4D, 0x04, 0x4E, 0x04, 0x4F, 0xFF, 0x00};
static u8 D_80180554[] = {0x04, 0x4E, 0x04, 0x4D, 0x04, 0x4C, 0x04,
                          0x4D, 0x04, 0x4E, 0x04, 0x4F, 0x00, 0x00};
static u8 D_80180564[] = {
    0x02, 0x20, 0x04, 0x21, 0x04, 0x22, 0x04, 0x23, 0x04, 0x24,
    0x04, 0x25, 0x04, 0x26, 0x04, 0x27, 0x02, 0x20, 0x00, 0x00};
static u8 D_80180578[] = {0x01, 0x2A, 0x08, 0x2B, 0xFF, 0x00};
static u8 D_80180580[] = {
    0x02, 0x2C, 0x04, 0x2D, 0x05, 0x2E, 0x04, 0x2F, 0x04, 0x30,
    0x04, 0x31, 0x04, 0x32, 0x04, 0x33, 0x05, 0x34, 0x04, 0x35,
    0x04, 0x36, 0x04, 0x37, 0x02, 0x2C, 0xFF, 0x00};

#ifndef HARD_LINK
#include "../../destroy_entity.h"
#endif

static void SetStep(Entity* entity, u16 step) {
    entity->step = step;
    entity->step_s = 0;
    entity->pose = 0;
    entity->poseTimer = 0;
}

#ifndef HARD_LINK
#include "../animate_entity.h"
#endif

// Note: SEL uses entities weirdly. This probably shouldn't be PLAYER.
// g_Entities[0] is probably its own thing.
void func_801B4C68(void) {
    Entity* self = &g_Entities[0];
    s32 primIndex;
    Primitive* prim;

    switch (self->step) {
    case 0:
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 1);
        if (primIndex != -1) {
            prim = &g_PrimBuf[primIndex];

            self->flags |= FLAG_HAS_PRIMS;
            self->primIndex = primIndex;
            self->ext.unkSelEnts.prim = prim;
            prim->tpage = 0x8A;
            prim->clut = 0;

            prim->u0 = prim->u2 = prim->v0 = prim->v1 = 0;
            prim->u1 = prim->u3 = 0xFF;
            prim->v2 = prim->v3 = 0xE0;

            prim->x0 = prim->x2 = 0;
            prim->x1 = prim->x3 = 0xFF;
            prim->y0 = prim->y1 = 0;
            prim->y2 = prim->y3 = 0xE0;

            prim->priority = 0x40;
            prim->drawMode = DRAW_DEFAULT;
            self->step++;
        }
        break;

    case 1:
        break;
    }
}

void func_801B4D78(void) {
    Entity* self = &g_Entities[3];

    switch (self->step) {
    case 0:
        self->animSet = ANIMSET_OVL(1);
        self->animCurFrame = 1;
        self->palette = 0x200;
        self->ext.unkSelEnts.unk80.val = FIX(92);
        self->posY.i.hi = 0xD0;
        self->zPriority = 0x80;
        self->step++;
        break;

    case 1:
        break;
    }
}

void func_801B4DE0(void) {
    Entity* self = &g_Entities[2];
    s32 primIndex;
    Primitive* prim;

    switch (self->step) {
    case 0:
        primIndex = g_api.AllocPrimitives(PRIM_G4, 1);
        if (primIndex != -1) {
            prim = &g_PrimBuf[primIndex];
            self->flags |= FLAG_HAS_PRIMS;
            self->primIndex = primIndex;
            self->ext.unkSelEnts.prim = prim;

            prim->x0 = prim->x2 = 0;
            prim->x1 = prim->x3 = 0xFF;
            prim->y0 = prim->y1 = 4;
            prim->y2 = prim->y3 = 0xE4;

            PCOL(prim) = 0xFF;

            prim->priority = 0xC8;
            prim->drawMode = DRAW_UNK_40 | DRAW_TPAGE | DRAW_TRANSP;
            D_801BC3E4 = 0;
            self->step++;
        }
        break;

    case 1:
        prim = self->ext.unkSelEnts.prim;
        if (D_801BC3E4 != 0) {
            PCOL(prim) -= 2;
            if (prim->r0 < 5) {
                D_801BC3E4 = 0;
                self->step++;
            }
        }
        break;

    case 2:
        prim = self->ext.unkSelEnts.prim;
        if (D_801BC3E4 != 0) {
            PCOL(prim) += 1;
            if (prim->r0 >= 0xFE) {
                D_801BC3E4 = 0;
                self->step++;
            }
        }
        break;

    case 3:
        break;
    }
}

void func_801B4FFC(void) {
    Entity* self = &g_Entities[2];
    s32 primIndex;
    Primitive* prim;

    switch (self->step) {
    case 0:
        primIndex = g_api.AllocPrimitives(PRIM_G4, 1);
        if (primIndex != -1) {
            prim = &g_PrimBuf[primIndex];
            self->flags |= FLAG_HAS_PRIMS;
            self->primIndex = primIndex;
            self->ext.unkSelEnts.prim = prim;

            prim->x0 = prim->x2 = 0;
            prim->x1 = prim->x3 = 0x180;
            prim->y0 = prim->y1 = 4;
            prim->y2 = prim->y3 = 0xE4;

            PCOL(prim) = 0;

            prim->priority = 0xC8;
            prim->drawMode = DRAW_UNK_40 | DRAW_TPAGE | DRAW_TRANSP;

            self->step++;
        }
        break;

    case 1:
        prim = self->ext.unkSelEnts.prim;
        if (D_801BC3E4 != 0) {
            PCOL(prim) += 2;
            if (prim->r0 >= 254) {
                D_801BC3E4 = 0;
                self->step++;
            }
        }

    case 2:
        break;
    }
}

void func_801B519C(void) {
    Entity* self = &g_Entities[1];
    s32 primIndex;
    Primitive* prim;
    u16 angle;
    u16 v;
    s16 x, y;

    switch (self->step) {
    case 0:
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 0x18);
        if (primIndex == -1) {
            break;
        }
        self->flags |= FLAG_HAS_PRIMS;
        self->primIndex = primIndex;
        prim = &g_PrimBuf[primIndex];
        self->ext.unkSelEnts.prim = prim;

        v = 0;
        while (prim != NULL) {
            prim->tpage = 8;
            prim->clut = 0x201;
            prim->u0 = prim->u2 = 0x38;
            prim->u1 = prim->u3 = 0x80;
            prim->v0 = prim->v1 = 0x38 + v;
            v++;
            prim->v2 = prim->v3 = 0x38 + v;
            prim->priority = 0x41;
            prim->drawMode =
                DRAW_UNK_40 | DRAW_TPAGE2 | DRAW_TPAGE | DRAW_TRANSP;
            prim = prim->next;
        }
        self->step++;

    case 1:
        self->ext.unkSelEnts.unk88 += 0x40;
        angle = self->ext.unkSelEnts.unk88;
        y = 0xA2;
        prim = self->ext.unkSelEnts.prim;
        while (prim != NULL) {
            angle &= 0xFFF;
            x = rsin(angle) / 0x800 + 0x40;
            angle += 0x100;
            prim->x0 = prim->x2 = x;
            prim->x1 = prim->x3 = x + 0x48;
            prim->y0 = prim->y1 = y;
            y++;
            prim->y2 = prim->y3 = y;
            prim = prim->next;
        }
        break;
    }
}

// Compare to func_801B585C
// Probably handles Alucard sprite in the ending, did not confirm but uses his
// palette.
void func_801B5350(void) {
    Entity* self = &g_Entities[UNK_ENTITY_5];

    switch (self->step) {
    case 0:
        self->animSet = ANIMSET_DRA(1);
        self->animCurFrame = 0x8E;
        self->unk5A = 0;
        self->ext.unkSelEnts.unk80.val = FIX(0x80);
        self->posY.i.hi = 0x9F;
        self->zPriority = 0xC0;
        self->palette = PAL_FLAG(PAL_ALUCARD);
        self->step++;
        break;

    case 1:
        self->animCurFrame = 0x8E;
        break;

    case 2:
        if (!AnimateEntity(D_80180528, self)) {
            SetStep(self, 3);
        }
        self->ext.unkSelEnts.unk80.val -= FIX(1.5);
        break;

    case 3:
        AnimateEntity(D_80180504, self);
        self->ext.unkSelEnts.unk80.val -= FIX(1.5);
        if (self->ext.unkSelEnts.unk80.i.hi < 0x40) {
            self->step = 0xFF;
        }
        break;
    }
}

// func_801B54C8 sets up the Richter sprite in the Alucard Mode ending scenes
// where he was saved.
void func_801B54C8(void) {
    Entity* self = &g_Entities[UNK_ENTITY_7];

    switch (self->step) {
    case 0:
        self->animSet = ANIMSET_OVL(2);
        self->animCurFrame = 0x26;
        self->facingLeft = 1;
        self->unk5A = 0xF;
        self->ext.unkSelEnts.unk80.val = FIX(0x78);
        self->posY.i.hi = 0x9E;
        self->zPriority = 0xC0;
        self->palette = PAL_FLAG(0x210);
        self->step++;
        break;

    case 1:
        break;
    }
}

// func_801B5548 sets up the Richter sprite in the Richter Mode ending scene.
static void func_801B5548(void) {
    Entity* self = &g_Entities[UNK_ENTITY_7];

    switch (self->step) {
    case 0:
        self->animSet = ANIMSET_OVL(2);
        self->animCurFrame = 7;
        self->facingLeft = 0;
        self->unk5A = 0xF;
        self->ext.unkSelEnts.unk80.val = FIX(0x78);
        self->posY.i.hi = 0x9E;
        self->zPriority = 0xC0;
        self->palette = PAL_FLAG(0x210);
        self->step++;
        break;

    case 1:
        break;
    }
}

// func_801B55C8 handles Maria's sprite in the ending scene.
void func_801B55C8(void) {
    Entity* self = &g_Entities[UNK_ENTITY_6];

    switch (self->step) {
    case 0:
        self->animSet = ANIMSET_OVL(3);
        self->animCurFrame = 0xC;
        self->unk5A = 0x46;
        self->palette = 0x258;
        self->facingLeft = 1;
        self->ext.unkSelEnts.unk80.val = FIX(0x80);
        self->posY.i.hi = 0xA0;
        self->zPriority = 0xC0;
        self->step++;
        break;

    case 1:
        if (D_801BC3E8 & 0x10) {
            self->animSet = ANIMSET_OVL(4);
            self->unk5A = 0x48;
            self->animCurFrame = 0x2C;
            self->velocityX = FIX(-0.75);
            SetStep(self, 2);
        }
        break;

    case 2:
        self->ext.unkSelEnts.unk80.val -= FIX(0.75);
        if (!AnimateEntity(D_80180580, self)) {
            self->animSet = ANIMSET_OVL(3);
            self->animCurFrame = 0xC;
            self->unk5A = 0x46;
            self->step++;
        }
        break;

    case 3:
        if (D_801BC3E8 & 0x20) {
            self->animSet = ANIMSET_OVL(4);
            self->unk5A = 0x48;
            self->animCurFrame = 0x2C;
            self->facingLeft = 0;
            SetStep(self, 4);
        }
        break;

    case 4:
        if (!AnimateEntity(D_80180578, self)) {
            self->animSet = ANIMSET_OVL(3);
            self->unk5A = 0x46;
            self->animCurFrame = 0xC;
            SetStep(self, 5);
        }
        break;

    case 5:
        if (D_801BC3E8 & 0x40) {
            self->animSet = ANIMSET_OVL(4);
            self->unk5A = 0x48;
            self->facingLeft = 1;
            self->animCurFrame = 0x2C;
            SetStep(self, 6);
        }
        break;

    case 6:
        if (!AnimateEntity(D_80180578, self)) {
            self->animSet = ANIMSET_OVL(3);
            self->unk5A = 0x46;
            self->animCurFrame = 0x20;
            SetStep(self, 7);
        }
        self->ext.unkSelEnts.unk80.val -= FIX(0.75);
        break;

    case 7:
        AnimateEntity(D_80180564, self);
        self->ext.unkSelEnts.unk80.val -= FIX(1.5);
        if (self->ext.unkSelEnts.unk80.i.hi < 0x20) {
            self->step = 0xFF;
        }
        break;
    }
}

// Compare to func_801B5350
void func_801B585C(u16 arg0) {
    Entity* self = &g_Entities[UNK_ENTITY_5];

    switch (self->step) {
    case 0:
        self->animSet = ANIMSET_DRA(1);
        self->animCurFrame = 0;
        self->unk5A = 0;
        self->ext.unkSelEnts.unk80.val = 0;
        self->posY.i.hi = 0x9F;
        self->zPriority = 0xC0;
        self->palette = PAL_FLAG(PAL_ALUCARD);
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
        if (self->ext.unkSelEnts.unk80.i.hi > 0x48) {
            SetStep(self, 3);
        }
        break;

    case 3:
        if (!AnimateEntity(D_80180538, self)) {
            SetStep(self, 4);
        }
        break;

    case 4:
        AnimateEntity(D_80180554, self);
        if (D_801BC3E8 & 8) {
            SetStep(self, 5);
        }
        break;

    case 5:
        self->facingLeft = 1;
        if (!AnimateEntity(D_80180528, self)) {
            SetStep(self, 6);
        }
        self->ext.unkSelEnts.unk80.val -= FIX(1.5);
        break;

    case 6:
        AnimateEntity(D_80180504, self);
        self->ext.unkSelEnts.unk80.val -= FIX(1.5);
        if ((arg0 && self->ext.unkSelEnts.unk80.i.hi < 0x20) ||
            (!arg0 && self->ext.unkSelEnts.unk80.i.hi < -0x10)) {
            self->step = 0xFF;
        }
        break;
    }
}

void func_801B5A7C(void) {
    // Not sure where this entity is initialized...
    Entity* self = &g_Entities[UNK_ENTITY_8];
    Entity* e;

    switch (self->params) {
    case 0:
        switch (self->step) {
        case 0:
            D_8018BC4A = 0;
            self->step++;
            break;

        case 1:
            D_801BC3E4 = 1;
            D_801D6B24 = -0x400000;
            self->step++;
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
                self->step++;
            }
            break;

        case 3:
            e = &g_Entities[UNK_ENTITY_5];
            e->step = 2;
            e->pose = 0;
            e->poseTimer = 0;
            e->facingLeft = 1;
            self->step++;
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
        switch (self->step) {
        case 0:
            D_8018BC4A = 1;
            self->step++;
            break;

        case 1:
            D_801BC3E4 = 1;
            D_801D6B24 = -0x400000;
            self->step++;
            break;

        case 2:
            if (D_801BC3E4 == 0) {
                D_801BC3E8 |= 1;
                D_801BC3E8 |= 4;
                self->step++;
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
                self->step++;
            }
            break;

        case 4:
            self->step++;
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
        switch (self->step) {
        case 0:
            D_8018BC4A = 2;
            D_8018BC50 = 0;
            self->step++;
            break;

        case 1:
            D_801BC3E4 = 1;
            D_801D6B24 = -0x400000;
            self->step++;
            break;

        case 2:
            if (D_801BC3E4 == 0) {
                D_801BC3E8 |= 1;
                D_801BC3E8 |= 4;
                self->step++;
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
                self->step++;
            }
            break;

        case 4:
            self->step++;
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
        switch (self->step) {
        case 0:
            D_8018BC4A = 3;
            self->step++;
            break;

        case 1:
            D_801BC3E4 = 1;
            D_801D6B24 = -0x400000;
            self->step++;
            break;

        case 2:
            if (D_801BC3E4 == 0) {
                self->step++;
            }
            if (D_801D6B24 != 0) {
                D_801D6B24 += 0x4000;
            }
            break;

        case 3:
            if (D_801D6B24 != 0) {
                D_801D6B24 += 0x4000;
            } else {
                self->step++;
                self->ext.unkSelEnts.unk8C = 0x80;
            }
            break;

        case 4:
            if (!--self->ext.unkSelEnts.unk8C) {
                D_801BC3E8 |= 1;
                self->step++;
            }
            break;

        case 5:
            if (D_801BC3E8 & 2) {
                D_801BC3E4 = 1;
                self->step++;
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
        switch (self->step) {
        case 0:
            D_8018BC4A = 2;
            D_8018BC50 = 1;
            self->step++;
            break;

        case 1:
            D_801BC3E4 = 1;
            D_801D6B24 = -0x400000;
            self->step++;
            break;

        case 2:
            if (D_801BC3E4 == 0) {
                D_801BC3E8 |= 1;
                D_801BC3E8 |= 4;
                self->step++;
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
                self->step++;
            }
            break;

        case 4:
            self->step++;
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
        ent = &g_Entities[0];
        for (i = 0; i <= 8; i++, ent++) {
            DestroyEntity(ent);
        }
        D_801D6B24 = 0;
        D_801BD030 = 0;
        ent = &g_Entities[UNK_ENTITY_8];
        ent->params = D_800978B4 - 1;
        g_api.func_800EA5E4(ANIMSET_DRA(0x16));
        g_api.func_800EA5E4(ANIMSET_DRA(0));
        g_api.func_800EA5E4(ANIMSET_OVL(5));
        g_api.LoadGfxAsync(ANIMSET_OVL(0));
        g_GameEngineStep++;
        break;

    case 3:
        func_801B5A7C();
        ent = &g_Entities[UNK_ENTITY_4];
        OVL_EXPORT(EntityCutscene)(ent);
        func_801B4C68();
        func_801B519C();
        func_801B4D78();
        func_801B4DE0();
        ent = &g_Entities[3];
        for (i = 3; i < 8; i++, ent++) {
            ent->posX.i.hi =
                (D_801D6B24 / 0x10000) + ent->ext.unkSelEnts.unk80.i.hi;
        }

        if (D_801BD030 != 0) {
            // This is kind of weird, we destroy the first 8...
            ent = &g_Entities[0];
            for (i = 0; i <= 8; i++, ent++) {
                DestroyEntity(ent);
            }
            // ... and then another 8. Why not just 16 all at once?
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
        g_api.func_800EA5E4(ANIMSET_DRA(0));
        g_GameEngineStep++;
        break;

    case 7:
        ent = &g_Entities[UNK_ENTITY_4];
        if (func_801B79D4(ent)) {
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
