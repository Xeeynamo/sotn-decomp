// SPDX-License-Identifier: AGPL-3.0-or-later
#include "sel.h"
#include "sfx.h"

s32 D_801804D0 = 0;
u8 D_801804D4[] = {STAGE_MEMORYCARD, STAGE_CAT};
const char* D_801804D8[] = {
    "NORMAL      ",
    "SPECIAL     ",
};
const char D_801A7B80[] = "SELECT ！！";

void HandleTitleScreen(void) {
    Primitive* prim;
    Primitive* prim15;
    s16 primIndex;
    s32 i;

    func_801B1F34();
    switch (g_GameEngineStep) {
    case 0:
        if (g_UseDisk != 0) {
            g_CdStep = 1;
            g_LoadFile = 0x8003;
            g_LoadOvlIdx = 0xFF;
        }
        primIndex = g_api.AllocPrimitives(PRIM_SPRT, 0x11);
        prim = &g_PrimBuf[primIndex];

        D_801BB010 = primIndex;
        for (i = 0; i < 3; i++) {
            prim->x0 = 0x70 + i * 0x80;
            prim->y0 = 0xA8;
            prim->u0 = 0x80;
            prim->v0 = i * 0x10 - 0x50;
            prim->u1 = 0x80;
            if (i == 2) {
                prim->u1 = 0x20;
            }
            prim->v1 = 0x10;
            prim->tpage = 0x18;
            prim->clut = 0x20;
            prim->priority = 1;
            prim->drawMode = DRAW_HIDE;
            prim = prim->next;
        }
        for (i = 0; i < 4; i++) {
            prim->x0 = 12 + i * 0x80;
            prim->y0 = 0xD6;
            prim->u0 = 0x80;
            prim->v0 = i * 8 - 0x70;
            prim->u1 = 0x80;
            if (i == 3) {
                prim->u1 = 0x64;
            }
            prim->v1 = 8;
            prim->tpage = 0x18;
            prim->clut = 0x21;
            prim->priority = 1;
            prim->drawMode = DRAW_HIDE;
            prim = prim->next;
        }
        for (i = 0; i < 4; i++) {
            prim->x0 = i << 7;
            prim->u1 = 0x80;
            prim->v1 = 0xF0;
            prim->tpage = i + 0x88;
            prim->clut = 0x10;
            prim->drawMode = DRAW_HIDE;
            prim = prim->next;
        }
        for (i = 0; i < 4; i++) {
            prim->x0 = i << 7;
            prim->u1 = 0x80;
            prim->y0 = 0x18;
            prim->v1 = 0x88;
            prim->tpage = i + 0x8C;
            prim->priority = 2;
            prim->drawMode = DRAW_HIDE;
            prim = prim->next;
        }
        prim->x0 = 0x101;
        prim->y0 = 0x60;
        prim->u1 = 0xFF;
        prim->v1 = 0x90;
        prim->tpage = 0x18;
        prim->clut = 0x22;
        prim->priority = 1;
        prim->drawMode = DRAW_HIDE;
        prim = prim->next;

        prim->v0 = 0x90;
        prim->u1 = 0x78;
        prim->v1 = 0x40;
        prim->tpage = 0x18;
        prim->clut = 0x22;
        prim->priority = 1;
        prim->drawMode = DRAW_HIDE;
        func_801B18F4();
        D_801BB014 = 0;
        g_GameEngineStep++;
        return;
    case 1:
        SetTitleDisplayBuffer();
        D_801BB014 += 8;
        for (i = 0, prim = &g_PrimBuf[D_801BB010]; prim != NULL;
             prim = prim->next, i++) {
            prim->drawMode = DRAW_COLORS;
            SetPrimGrey(prim, D_801BB014);
            if (i == 7 || i == 8 || i == 9 || i == 10) {
                prim->r0 = D_801BB014 * 3 / 4;
                prim->g0 = D_801BB014 * 7 / 8;
                prim->b0 = D_801BB014 * 3 / 4;
            }
            if (i == 15 || i == 16) {
                prim->drawMode = DRAW_TPAGE | DRAW_COLORS | DRAW_TRANSP;
            }
        }
        if (D_801BB014 == 0x80) {
            D_801804D0 = 0x800;
            g_GameEngineStep++;
        }
        return;
    case 2:
        for (i = 0, prim = &g_PrimBuf[D_801BB010]; prim != NULL;
             prim = prim->next, i++) {
            if (i < 3) {
                prim->drawMode = DRAW_HIDE;
                if (g_Timer & 0x30) {
                    prim->drawMode = DRAW_DEFAULT;
                }
            }
            if (i < 15 || i > 16) {
                continue;
            }
            if (i == 15) {
                prim15 = prim;
            }
            switch (prim->p1) {
            case 0:
                if (i == 0xF) {
                    if (!(rand() & 0x7F)) {
                        prim->p2 = 6;
                        prim->tpage = 0x19;
                        prim->p1 += 1;
                    }
                } else {
                    if ((prim15->p1 >= 2U) ||
                        ((prim15->p1 != 0) && ((u8)prim15->p2 < 3U))) {
                        prim->p2 = (rand() & 3) + 6;
                        prim->tpage = 0x19;
                        prim->p1 += 1;
                    }
                }
                break;
            case 1:
                if (!(--prim->p2 & 0xFF)) {
                    prim->p2 = 6;
                    prim->tpage = 0x1A;
                    prim->p1 += 1;
                }
                break;
            case 2:
                if (!(--prim->p2 & 0xFF)) {
                    prim->p2 = (rand() & 7) + 6;
                    prim->tpage = 0x1B;
                    prim->p1 += 1;
                }
                break;
            case 3:
                if (!(--prim->p2 & 0xFF)) {
                    prim->p2 = 5;
                    prim->tpage = 0x1A;
                    prim->p1 += 1;
                }
                break;
            case 4:
                if (!(--prim->p2 & 0xFF)) {
                    prim->p2 = 5;
                    prim->tpage = 0x19;
                    prim->p1 += 1;
                }
                break;
            case 5:
                if (!(--prim->p2 & 0xFF)) {
                    prim->p2 = 6;
                    prim->tpage = 0x18;
                    prim->p1 += 1;
                }
                break;
            case 6:
                if (!(--prim->p2 & 0xFF)) {
                    if (i != 0x10) {
                        prim->p2 = 6;
                        prim->p1 += 1;
                        if (rand() & 3) {
                            prim->p1 = 1;
                            prim->tpage = 0x19;
                        }
                    } else {
                        prim->p1 = 0;
                    }
                }
                break;
            case 7:
                if (!(--prim->p2 & 0xFF)) {
                    prim->p1 = 0;
                }
                break;
            }

            if (i != 0x10) {
                continue;
            }
            if (prim->tpage == 0x18) {
                prim->u1 = 0x78;
            } else {
                prim->u1 = 0x70;
            }
        }
        if (g_pads[0].tapped & PAD_START) {
            g_api.PlaySfx(SFX_START_SLAM_B);
            g_GameEngineStep++;
        }
        return;
    case 3:
        g_GameEngineStep = 6;
        return;
    case 4:
        if (g_pads[0].tapped & (PAD_RIGHT | PAD_DOWN)) {
            g_api.PlaySfx(SFX_DEBUG_SELECT);
            if (++D_800987B4 >= 2) {
                D_800987B4 = 0;
            }
        }
        if (g_pads[0].tapped & (PAD_UP | PAD_LEFT)) {
            g_api.PlaySfx(SFX_DEBUG_SELECT);
            if (--D_800987B4 < 0) {
                D_800987B4 = 1;
            }
        }
        prim = &g_PrimBuf[D_801BB010];
        if (g_Timer & 0x1C) {
            prim->drawMode = DRAW_DEFAULT;
        } else {
            prim->drawMode = DRAW_HIDE;
        }
        g_StageId = D_801804D4[D_800987B4];
        func_801B1F4C(1);
        func_801B259C(D_801804D8[D_800987B4], 1);
        if (g_pads[0].tapped & (PAD_START | PAD_CIRCLE)) {
            g_api.PlaySfx(SFX_START_SLAM_B);
            g_GameEngineStep++;
        }
        return;
    case 5:
        func_801B18F4();
        func_801B19F4();
        func_801B1DA8();
        g_api.FreePrimitives(D_801BB010);
        STRCPY(g_Status.saveName, "alucard");
        if (g_StageId == STAGE_ST0) {
            SetGameState(Game_VideoPlayback);
        } else if (g_StageId == STAGE_MEMORYCARD) {
            SetGameState(Game_MainMenu);
        } else {
            SetGameState(Game_NowLoading);
            g_GameStep = 2;
        }
        return;
    case 6:
        D_801BB014 -= 8;
        for (i = 0, prim = &g_PrimBuf[D_801BB010]; prim != NULL;
             prim = prim->next, i++) {
            prim->drawMode = DRAW_COLORS;
            SetPrimGrey(prim, D_801BB014);
            if (i == 15 || i == 16) {
                prim->drawMode = DRAW_TPAGE | DRAW_COLORS | DRAW_TRANSP;
            }
        }
        if (D_801BB014 == 0) {
            g_StageId = STAGE_MEMORYCARD;
            g_GameEngineStep = 5;
        }
        return;
    }
}

#ifndef HARD_LINK
#include "../../destroy_entity.h"
#endif

void SEL_SetStep(Entity* entity, s16 step) {
    entity->step = step;
    entity->step_s = 0;
    entity->animFrameIdx = 0;
    entity->animFrameDuration = 0;
}

#ifndef HARD_LINK
#include "../animate_entity.h"
#endif

// Note: SEL uses entities weirdly. This probably shouldn't be PLAYER.
// g_Entities[0] is probably its own thing.
void func_801B4C68(void) {
    Entity* player;
    s16 primIndex;
    Primitive* prim;

    player = &PLAYER;
    if (player->step != 0) {
        return;
    }

    primIndex = g_api.AllocPrimitives(PRIM_GT4, 1);
    if (primIndex == -1) {
        return;
    }

    PLAYER.primIndex = primIndex;
    prim = &g_PrimBuf[primIndex];
    PLAYER.ext.player.prim = prim;
    PLAYER.flags |= FLAG_HAS_PRIMS;
    prim->tpage = 0x8A;
    prim->u1 = prim->u3 = 0xFF;
    prim->v2 = prim->v3 = 0xE0;
    prim->x1 = prim->x3 = 0xFF;
    prim->y2 = prim->y3 = 0xE0;
    prim->clut = 0;
    prim->v0 = prim->v1 = 0;
    prim->u0 = prim->u2 = 0;
    prim->x0 = prim->x2 = 0;
    prim->y0 = prim->y1 = 0;
    prim->priority = 0x40;
    prim->drawMode = DRAW_DEFAULT;
    PLAYER.step++;
}

void func_801B4D78(void) {
    Entity* self = &g_Entities[UNK_ENTITY_3];

    if (self->step == 0) {
        self->animSet = ANIMSET_OVL(1);
        self->animCurFrame = 1;
        self->palette = 0x200;
        self->ext.unkSelEnts.unk80.val = FIX(92);
        self->posY.i.hi = 208;
        self->zPriority = 0x80;
        self->step = 1;
    }
}

void func_801B4DE0(void) {
    Entity* self = &g_Entities[UNK_ENTITY_2];
    s16 primIndex;
    Primitive* prim;

    switch (self->step) {
    case 0:
        primIndex = g_api.AllocPrimitives(PRIM_G4, 1);
        if (primIndex != -1) {
            prim = &g_PrimBuf[primIndex];
            self->primIndex = primIndex;
            self->flags |= FLAG_HAS_PRIMS;
            self->ext.unkSelEnts.prim = prim;

            prim->x1 = prim->x3 = 255;
            prim->y0 = prim->y1 = 4;
            prim->y2 = prim->y3 = 228;

            PCOL(prim) = 255;

            prim->priority = 0xC8;
            prim->x0 = prim->x2 = 0;
            prim->drawMode = DRAW_UNK_40 | DRAW_TPAGE | DRAW_TRANSP;
            D_801BC3E4 = 0;
            self->step++;
        }
        break;

    case 1:
        prim = self->ext.unkSelEnts.prim;
        if (D_801BC3E4 != 0) {
            PCOL(prim) = prim->b3 - 2;
            if (prim->r0 < 5) {
                D_801BC3E4 = 0;
                self->step++;
            }
        }
        break;

    case 2:
        prim = self->ext.unkSelEnts.prim;
        if (D_801BC3E4 != 0) {
            PCOL(prim) = prim->b3 + 1;
            if (prim->r0 >= 254) {
                D_801BC3E4 = 0;
                self->step++;
            }
        }
    }
}

void func_801B4FFC(void) {
    Entity* self = &g_Entities[UNK_ENTITY_2];
    s16 primIndex;
    Primitive* prim;

    switch (self->step) {
    case 0:
        primIndex = g_api.AllocPrimitives(PRIM_G4, 1);
        if (primIndex != -1) {
            prim = &g_PrimBuf[primIndex];
            self->primIndex = primIndex;
            self->flags |= FLAG_HAS_PRIMS;
            self->ext.unkSelEnts.prim = prim;

            prim->x0 = prim->x2 = 0;
            prim->x1 = prim->x3 = 384;
            prim->y0 = prim->y1 = 4;
            prim->y2 = prim->y3 = 228;

            PCOL(prim) = 0;

            prim->priority = 0xC8;
            prim->drawMode = DRAW_UNK_40 | DRAW_TPAGE | DRAW_TRANSP;

            self->step++;
        }
        break;

    case 1:
        prim = self->ext.unkSelEnts.prim;
        if (D_801BC3E4 != 0) {
            PCOL(prim) = prim->b3 + 2;
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
    Entity* self;
    Primitive* prim;
    s16 angle;
    s16 y;
    s32 angle2;
    s32 uvOfst;
    s16 primBufIndex;
    s32 v01;

    self = &g_Entities[1];
    switch (self->step) {
    case 0:
        primBufIndex = g_api.AllocPrimitives(PRIM_GT4, 0x18);
        if (primBufIndex == -1) {
            return;
        }
        prim = &g_PrimBuf[primBufIndex];
        self->primIndex = primBufIndex;
        self->ext.prim = prim;
        self->flags |= FLAG_HAS_PRIMS;
        uvOfst = 0;
        while (prim) {
            v01 = 0x38 + uvOfst;
            uvOfst++;
            prim->tpage = 8;
            prim->clut = 0x201;
            prim->u0 = prim->u2 = 0x38;
            prim->u1 = prim->u3 = 0x80;
            prim->v0 = prim->v1 = v01;
            prim->v2 = prim->v3 = 0x38 + uvOfst;
            prim->priority = 0x41;
            prim->drawMode =
                DRAW_UNK_40 | DRAW_TPAGE2 | DRAW_TPAGE | DRAW_TRANSP;
            prim = prim->next;
        }
        self->step++;
    case 1:
        y = 0xA2;
        prim = self->ext.prim;
        angle = self->ext.unkSelEnts.unk88 + 0x40;
        angle2 = angle;
        self->ext.unkSelEnts.unk88 = angle2;
        while (prim) {
            s16 xBase;
            s32 sin;
            angle &= 0xFFF;
            sin = rsin(angle);
            if (sin < 0) {
                sin += 0x7FF;
            }
            xBase = sin >> 0xB;
            prim->x0 = prim->x2 = xBase + 0x40;
            prim->x1 = prim->x3 = xBase + 0x88;
            prim->y0 = prim->y1 = y;
            y++;
            prim->y2 = prim->y3 = y;
            prim = prim->next;
            angle += 0x100;
        }
        break;
    }
}

// Compare to func_801B585C
void func_801B5350(void) {
    Entity* self = &g_Entities[UNK_ENTITY_5];

    switch (self->step) {
    case 0:
        self->animSet = ANIMSET_DRA(1);
        self->animCurFrame = 142;
        self->ext.unkSelEnts.unk80.val = FIX(0x80);
        self->posY.i.hi = 159;
        self->zPriority = 0xC0;
        self->unk5A = 0;
        self->palette = PAL_OVL(0x100);
        self->step = 1;
        break;

    case 1:
        self->animCurFrame = 142;
        break;

    case 2:
        if (!(AnimateEntity(D_80180528, self) & 0xFF)) {
            SEL_SetStep(self, 3);
        }
        self->ext.unkSelEnts.unk80.val -= FIX(1.5);
        break;

    case 3:
        AnimateEntity(D_80180504, self);
        self->ext.unkSelEnts.unk80.val -= FIX(1.5);
        if (self->ext.unkSelEnts.unk80.i.hi < 0x40) {
            self->step = 255;
        }
        break;
    }
}

void func_801B54C8(void) {
    Entity* self = &g_Entities[UNK_ENTITY_7];

    if (self->step == 0) {
        self->animSet = ANIMSET_OVL(2);
        self->animCurFrame = 38;
        self->facingLeft = 1;
        self->unk5A = 0xF;
        self->ext.unkSelEnts.unk80.val = FIX(120);
        self->posY.i.hi = 158;
        self->zPriority = 0xC0;
        self->palette = PAL_OVL(0x210);
        self->step = 1;
    }
}

void func_801B5548(void) {
    Entity* self = &g_Entities[UNK_ENTITY_7];

    if (self->step == 0) {
        self->animSet = ANIMSET_OVL(2);
        self->animCurFrame = 7;
        self->unk5A = 0xF;
        self->ext.unkSelEnts.unk80.val = FIX(120);
        self->posY.i.hi = 158;
        self->zPriority = 0xC0;
        self->palette = PAL_OVL(0x210);
        self->facingLeft = 0;
        self->step = 1;
    }
}

void func_801B55C8(void) {
    Entity* self = &g_Entities[6];

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
            SEL_SetStep(self, 2);
        }
        break;
    case 2:
        self->ext.unkSelEnts.unk80.val -= FIX(0.75);
        if (!(AnimateEntity(D_80180580, self) & 0xFF)) {
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
            SEL_SetStep(self, 4);
        }
        break;
    case 4:
        if (!(AnimateEntity(D_80180578, self) & 0xFF)) {
            self->animSet = ANIMSET_OVL(3);
            self->unk5A = 0x46;
            self->animCurFrame = 0xC;
            SEL_SetStep(self, 5);
        }
        break;
    case 5:
        if (D_801BC3E8 & 0x40) {
            self->animSet = ANIMSET_OVL(4);
            self->unk5A = 0x48;
            self->facingLeft = 1;
            self->animCurFrame = 0x2C;
            SEL_SetStep(self, 6);
        }
        break;
    case 6:
        if (!(AnimateEntity(D_80180578, self) & 0xFF)) {
            self->animSet = ANIMSET_OVL(3);
            self->unk5A = 0x46;
            self->animCurFrame = 0x20;
            SEL_SetStep(self, 7);
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
