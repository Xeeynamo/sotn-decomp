// SPDX-License-Identifier: AGPL-3.0-or-later
#include "game.h"
#include "libgpu.h"
#include "sel.h"

enum {
    ENT_BACKGROUND,
    ENT_WATER_RIPPLES,
    ENT_FADEOUT,
    ENT_ROCK_CLIFF_EDGE,
    ENT_CREDITS_ROLL,
    ENT_ALUCARD,
    ENT_MARIA,
    ENT_RICHTER,
    ENT_CUTSCENE_MANAGER,
};

enum {
    PAL_ACTOR_RICHTER = 0x210,
    PAL_ACTOR_MARIA = 0x258,
};

enum {
    ENDING_VARIANT_WORST = ENDING_WORST - 1,
    ENDING_VARIANT_BAD = ENDING_BAD - 1,
    ENDING_VARIANT_GOOD = ENDING_GOOD - 1,
    ENDING_VARIANT_RICHTER = ENDING_RICHTER - 1,
    ENDING_VARIANT_BEST = ENDING_BEST - 1,
};

extern RECT D_8018258C;
extern u32 D_801BC3E8;
extern u32 is_ending_sequence_done;
extern s8 D_8018BC4A;
extern s8 D_8018BC50;

// DATA
static AnimateEntityFrame D_801804E0[] = {
    POSE(2, 0x19, 0), POSE(2, 0x1A, 0), POSE(2, 0x1B, 0), POSE(2, 0x1C, 0),
    POSE(2, 0x1D, 0), POSE(2, 0x1E, 0), POSE(2, 0x1F, 0), POSE(2, 0x20, 0),
    POSE(2, 0x21, 0), POSE(2, 0x22, 0), POSE(2, 0x23, 0), POSE(2, 0x24, 0),
    POSE(2, 0x25, 0), POSE(2, 0x26, 0), POSE(2, 0x27, 0), POSE(2, 0x28, 0),
    POSE_END};
static AnimateEntityFrame anim_alucard_run[] = {
    POSE(4, 0x29, 0), POSE(4, 0x2A, 0), POSE(4, 0x2B, 0), POSE(4, 0x2C, 0),
    POSE(4, 0x2D, 0), POSE(4, 0x2E, 0), POSE(4, 0x2F, 0), POSE(4, 0x30, 0),
    POSE(4, 0x31, 0), POSE(4, 0x32, 0), POSE(4, 0x33, 0), POSE(4, 0x34, 0),
    POSE(4, 0x35, 0), POSE(4, 0x36, 0), POSE(4, 0x37, 0), POSE(4, 0x38, 0),
    POSE_LOOP(0)};
static AnimateEntityFrame anim_alucard_turn[] = {
    POSE(4, 0x39, 0), POSE(4, 0x3A, 0), POSE(4, 0x3B, 0), POSE(4, 0x3C, 0),
    POSE(4, 0x3D, 0), POSE(4, 0x3E, 0), POSE(4, 0x3F, 0), POSE_END};
static AnimateEntityFrame anim_alucard_stop_from_run[] = {
    POSE(4, 0x43, 0), POSE(4, 0x44, 0), POSE(4, 0x45, 0), POSE(4, 0x46, 0),
    POSE(4, 0x47, 0), POSE(4, 0x48, 0), POSE(4, 0x49, 0), POSE(4, 0x4A, 0),
    POSE(4, 0x4B, 0), POSE(4, 0x4C, 0), POSE(4, 0x4D, 0), POSE(4, 0x4E, 0),
    POSE(4, 0x4F, 0), POSE_END};
static AnimateEntityFrame anim_alucard_idle_with_wind[] = {
    POSE(4, 0x4E, 0), POSE(4, 0x4D, 0), POSE(4, 0x4C, 0), POSE(4, 0x4D, 0),
    POSE(4, 0x4E, 0), POSE(4, 0x4F, 0), POSE_LOOP(0)};
static AnimateEntityFrame D_80180564[] = {
    POSE(2, 0x20, 0), POSE(4, 0x21, 0), POSE(4, 0x22, 0), POSE(4, 0x23, 0),
    POSE(4, 0x24, 0), POSE(4, 0x25, 0), POSE(4, 0x26, 0), POSE(4, 0x27, 0),
    POSE(2, 0x20, 0), POSE_LOOP(0)};
static AnimateEntityFrame D_80180578[] = {
    POSE(1, 0x2A, 0), POSE(8, 0x2B, 0), POSE_END};
static AnimateEntityFrame D_80180580[] = {
    POSE(2, 0x2C, 0), POSE(4, 0x2D, 0), POSE(5, 0x2E, 0), POSE(4, 0x2F, 0),
    POSE(4, 0x30, 0), POSE(4, 0x31, 0), POSE(4, 0x32, 0), POSE(4, 0x33, 0),
    POSE(5, 0x34, 0), POSE(4, 0x35, 0), POSE(4, 0x36, 0), POSE(4, 0x37, 0),
    POSE(2, 0x2C, 0), POSE_END};

#ifndef HARD_LINK
#include "../../destroy_entity.h"
#endif

static void SetStep(Entity* entity, u16 step) {
    entity->step = step;
    entity->step_s = 0;
    entity->pose = 0;
    entity->poseTimer = 0;
}

#include "../animate_entity.h"

void ActorBackgroundWithCastle(void) {
    Entity* self;
    s32 primIndex;
    Primitive* prim;

    self = &g_Entities[ENT_BACKGROUND];
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

void ActorRockCliffEdge(void) {
    Entity* self = &g_Entities[ENT_ROCK_CLIFF_EDGE];

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

void ActorFadein(void) {
    Entity* self = &g_Entities[ENT_FADEOUT];
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

static void ActorFadeout(void) {
    Entity* self = &g_Entities[ENT_FADEOUT];
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
        break;
    case 2:
        break;
    }
}

void ActorWaterRipples(void) {
    Entity* self = &g_Entities[ENT_WATER_RIPPLES];
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
        // fallthrough
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

static void ActorAlucardWorstEnding(void) {
    Entity* self = &g_Entities[ENT_ALUCARD];

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
        if (!AnimateEntity(anim_alucard_turn, self)) {
            SetStep(self, 3);
        }
        self->ext.unkSelEnts.unk80.val -= FIX(1.5);
        break;
    case 3:
        AnimateEntity(anim_alucard_run, self);
        self->ext.unkSelEnts.unk80.val -= FIX(1.5);
        if (self->ext.unkSelEnts.unk80.i.hi < 0x40) {
            self->step = 0xFF;
        }
        break;
    }
}

void ActorRichter(void) {
    Entity* self = &g_Entities[ENT_RICHTER];

    switch (self->step) {
    case 0:
        self->animSet = ANIMSET_OVL(2);
        self->animCurFrame = 0x26;
        self->facingLeft = 1;
        self->unk5A = 0xF;
        self->ext.unkSelEnts.unk80.val = FIX(0x78);
        self->posY.i.hi = 0x9E;
        self->zPriority = 0xC0;
        self->palette = PAL_FLAG(PAL_ACTOR_RICHTER);
        self->step++;
        break;
    case 1:
        break;
    }
}

static void ActorRichterSolo(void) {
    Entity* self = &g_Entities[ENT_RICHTER];

    switch (self->step) {
    case 0:
        self->animSet = ANIMSET_OVL(2);
        self->animCurFrame = 7;
        self->facingLeft = 0;
        self->unk5A = 0xF;
        self->ext.unkSelEnts.unk80.val = FIX(0x78);
        self->posY.i.hi = 0x9E;
        self->zPriority = 0xC0;
        self->palette = PAL_FLAG(PAL_ACTOR_RICHTER);
        self->step++;
        break;
    case 1:
        break;
    }
}

void ActorMaria(void) {
    Entity* self = &g_Entities[ENT_MARIA];

    switch (self->step) {
    case 0:
        self->animSet = ANIMSET_OVL(3);
        self->animCurFrame = 0xC;
        self->unk5A = 0x46;
        self->palette = PAL_ACTOR_MARIA;
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

void ActorAlucard(u16 isBadEnding) {
    Entity* self = &g_Entities[ENT_ALUCARD];

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
        AnimateEntity(anim_alucard_run, self);
        if (D_801BC3E8 & 4) {
            self->step++;
        }
        break;
    case 2:
        AnimateEntity(anim_alucard_run, self);
        self->ext.unkSelEnts.unk80.val += FIX(1.5);
        if (self->ext.unkSelEnts.unk80.i.hi > 0x48) {
            SetStep(self, 3);
        }
        break;
    case 3:
        if (!AnimateEntity(anim_alucard_stop_from_run, self)) {
            SetStep(self, 4);
        }
        break;
    case 4:
        AnimateEntity(anim_alucard_idle_with_wind, self);
        if (D_801BC3E8 & 8) {
            SetStep(self, 5);
        }
        break;
    case 5:
        self->facingLeft = 1;
        if (!AnimateEntity(anim_alucard_turn, self)) {
            SetStep(self, 6);
        }
        self->ext.unkSelEnts.unk80.val -= FIX(1.5);
        break;
    case 6:
        AnimateEntity(anim_alucard_run, self);
        self->ext.unkSelEnts.unk80.val -= FIX(1.5);
        if ((isBadEnding && self->ext.unkSelEnts.unk80.i.hi < 0x20) ||
            (!isBadEnding && self->ext.unkSelEnts.unk80.i.hi < -0x10)) {
            self->step = 0xFF;
        }
        break;
    }
}

void CutsceneManager(void) {
    // entity initialized in STEP_CUTSCENE_INIT
    Entity* self;
    Entity* e;

    self = &g_Entities[ENT_CUTSCENE_MANAGER];
    switch (self->params) {
    case ENDING_VARIANT_WORST:
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
            e = &g_Entities[ENT_ALUCARD];
            e->step = 2;
            e->pose = 0;
            e->poseTimer = 0;
            e->facingLeft = 1;
            self->step++;
            break;
        case 4:
            if (D_801BC3E4 == 0) {
                is_ending_sequence_done = 1;
            }
            break;
        }
        ActorAlucardWorstEnding();
        break;
    case ENDING_VARIANT_BAD:
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
                is_ending_sequence_done = 1;
            }
            break;
        }
        ActorAlucard(1);
        ActorMaria();
        break;
    case ENDING_VARIANT_GOOD:
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
                is_ending_sequence_done = 1;
            }
            break;
        }
        ActorAlucard(0);
        ActorRichter();
        ActorMaria();
        break;
    case ENDING_VARIANT_RICHTER:
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
                is_ending_sequence_done = 1;
            }
            break;
        }
        ActorRichterSolo();
        break;
    case ENDING_VARIANT_BEST:
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
                is_ending_sequence_done = 1;
            }
            break;
        }
        ActorAlucard(0);
        ActorRichter();
        ActorMaria();
        break;
    }
}

void HandleEndingSequence(void) {
    enum {
        STEP_MOVIE_INIT,
        STEP_MOVIE_RUN,
        STEP_CUTSCENE_INIT = 2,
        STEP_CUTSCENE_RUN,
        STEP_CLEAR_SCREEN,
        STEP_CHANGE_RESOLUTION,
        STEP_CREDITS_INIT,
        STEP_CREDITS_RUN,
        STEP_FADEOUT,
    };
    Entity* ent;
    s32 i;

    switch (g_GameEngineStep) {
    case STEP_MOVIE_INIT:
        if (!g_IsUsingCd) {
            g_IsMoviePlaying = 1;
            if (g_EndingVariant != ENDING_NONE) {
                g_CurrentStream = 3;
            } else {
                g_CurrentStream = 2;
            }
            g_GameEngineStep++;
        }
        break;
    case STEP_MOVIE_RUN:
        func_801B9C80();
        if (g_IsMoviePlaying == 0) {
            g_CurrentStream = 0;
            func_801B18F4();
        }
        if (g_EndingVariant != ENDING_NONE) {
            g_GameStep++;
        } else {
            g_GameStep = 0x100;
        }
        g_GameEngineStep++;
        break;
    case STEP_CUTSCENE_INIT:
        // Important! This loop confirms that SEL uses the first 8
        // entities for its internal uses.
        ent = &g_Entities[ENT_BACKGROUND];
        for (i = 0; i < 9; i++, ent++) {
            DestroyEntity(ent);
        }
        D_801D6B24 = 0;
        is_ending_sequence_done = 0;
        ent = &g_Entities[ENT_CUTSCENE_MANAGER];
        ent->params = g_EndingVariant - ENDING_WORST;
        g_api.func_800EA5E4(ANIMSET_DRA(0x16));
        g_api.func_800EA5E4(ANIMSET_DRA(0));
        g_api.func_800EA5E4(ANIMSET_OVL(5));
        g_api.LoadGfxAsync(ANIMSET_OVL(0));
        g_GameEngineStep++;
        break;
    case STEP_CUTSCENE_RUN:
        CutsceneManager();
        ent = &g_Entities[ENT_CREDITS_ROLL];
        EntityCutscene(ent);
        ActorBackgroundWithCastle();
        ActorWaterRipples();
        ActorRockCliffEdge();
        ActorFadein();
        ent = &g_Entities[ENT_ROCK_CLIFF_EDGE];
        for (i = 3; i < 8; i++, ent++) {
            ent->posX.i.hi =
                (D_801D6B24 / 0x10000) + ent->ext.unkSelEnts.unk80.i.hi;
        }

        if (is_ending_sequence_done) {
            // This is kind of weird, we destroy the first 9...
            ent = &g_Entities[ENT_BACKGROUND];
            for (i = 0; i <= ENT_CUTSCENE_MANAGER; i++, ent++) {
                DestroyEntity(ent);
            }
            // and then the same loop is copied over? must not be intentional
            for (i = 0; i <= ENT_CUTSCENE_MANAGER; i++, ent++) {
                DestroyEntity(ent);
            }
            g_GameEngineStep++;
        }
        break;
    case STEP_CLEAR_SCREEN:
        ClearImage(&D_8018258C, 0, 0, 0);
        g_GameEngineStep++;
        break;
    case STEP_CHANGE_RESOLUTION:
        SetMenuDisplayBuffer();
        g_GameEngineStep++;
        break;
    case STEP_CREDITS_INIT:
        g_api.func_800EA5E4(ANIMSET_DRA(0));
        g_GameEngineStep++;
        break;
    case STEP_CREDITS_RUN:
        ent = &g_Entities[ENT_CREDITS_ROLL];
        if (EntityCutsceneCredits(ent)) {
            ent = &g_Entities[ENT_WATER_RIPPLES];
            ent->step = 0;
            D_801BC3E4 = 1;
            g_GameEngineStep++;
        }
        break;
    case STEP_FADEOUT:
        ActorFadeout();
        if (D_801BC3E4 == 0) {
            g_GameStep++;
        }
        break;
    }
}
