// SPDX-License-Identifier: AGPL-3.0-or-later
#include "bo5.h"

static void CutsceneCameraPan(s16 target) {
    s16 pan;
    s16 delta;

    pan = 128 - (target - 256);
    delta = pan - g_unkGraphicsStruct.unk14;
    if (delta > 1) {
        g_unkGraphicsStruct.unk14++;
    } else if (delta < -1) {
        g_unkGraphicsStruct.unk14--;
    } else {
        g_unkGraphicsStruct.unk14 = pan;
    }
}

extern EInit g_EInitSpawner;
extern EInit g_EInitObtainable;
extern u32 g_CutsceneFlags;
extern s32 g_SkipCutscene;

void EntityCutsceneStage(Entity* self) {
    Entity* entity;
    s16 posScrollX;
    Tilemap* tilemap;

    tilemap = &g_Tilemap;
    entity = &PLAYER;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitSpawner);
        break;
    case 1:
        switch (self->step_s) {
        case 0:
            for (entity = &g_Entities[160]; entity < &g_Entities[192];
                 entity++) {
                if (entity->entityId == E_PRIZE_DROP) {
                    self->ext.cutsceneStage.target = entity;
                    self->step_s++;
                }
            }
            break;
        case 1:
            entity = self->ext.cutsceneStage.target;
            if (entity->entityId != E_PRIZE_DROP) {
                self->step_s++;
                D_us_801806DC = 0;
                g_CutsceneFlags |= 0x8000;
            }
            break;
        case 2:
            SetStep(2);
            break;
        }
        break;
    case 2:
        g_PauseAllowed = false;
        g_unkGraphicsStruct.pauseEnemies = true;
        g_Player.padSim = PAD_RIGHT;
        if (g_Player.status & PLAYER_STATUS_WOLF_FORM) {
            g_Player.padSim = PAD_WOLF;
        }
        g_Player.demo_timer = 1;
        self->step++;
        break;
    case 3:
#ifndef VERSION_PSP
        g_Player.padSim = PAD_NONE;
#endif
        if (g_Player.status & PLAYER_STATUS_WOLF_FORM) {
            if (g_Timer & 1) {
                g_Player.padSim = PAD_R2;
            }
        } else {
            g_Player.padSim = PAD_RIGHT;
            posScrollX = entity->posX.i.hi + tilemap->scrollX.i.hi;
            if (posScrollX > 288 && !(g_CutsceneFlags & 1)) {
                g_CutsceneFlags |= 1;
            }
            if (posScrollX > 320) {
                g_Player.padSim = PAD_NONE;
                entity->posX.i.hi = 320 - tilemap->scrollX.i.hi;
                self->step++;
            }
            if (posScrollX < 256) {
                posScrollX = 256;
            }
#ifndef VERSION_PSP
            CutsceneCameraPan(posScrollX);
#endif
        }
#ifdef VERSION_PSP
        CutsceneCameraPan(posScrollX);
#endif
        g_Player.demo_timer = 1;
        break;
    case 4:
        CutsceneCameraPan(320);
        if (g_CutsceneFlags & 2) {
            self->step++;
        }
        g_Player.padSim = PAD_NONE;
        g_Player.demo_timer = 1;
        break;
    case 5:
        CutsceneCameraPan(256);
        if (g_unkGraphicsStruct.unk14 == 128) {
            g_PauseAllowed = true;
            if (g_unkGraphicsStruct.pauseEnemies) {
                g_unkGraphicsStruct.pauseEnemies = false;
            }
            DestroyEntity(self);
        }
        g_Player.padSim = PAD_NONE;
        g_Player.demo_timer = 1;
        break;
    }
}

static AnimateEntityFrame anim_step3[] = {
    {48, 2}, {8, 3}, {8, 4},  {8, 5},   {8, 6},    {32, 7},
    {4, 8},  {4, 9}, {4, 10}, {32, 11}, {112, 10}, {5, 9},
    {5, 8},  {5, 7}, {16, 6}, {8, 5},   {80, 4},   POSE_END};
static AnimateEntityFrame anim_step4[] = {
    {8, 4},  {11, 12}, {8, 13},  {8, 14}, {8, 15},
    {8, 16}, {8, 17},  {16, 18}, POSE_END};
static AnimateEntityFrame anim_step5[] = {
    {1, 18}, {2, 19}, {2, 20}, {6, 32}, {6, 33}, {80, 32}, POSE_END};
static AnimateEntityFrame anim_step6[] = {{8, 20}, {64, 27}, POSE_END};
static AnimateEntityFrame anim_step7[] = {
    {128, 28}, {48, 29}, {7, 30},  {7, 31},
    {7, 20},   {7, 19},  {32, 18}, POSE_END};
static AnimateEntityFrame anim_step8[] = {
    {7, 18}, {7, 19}, {20, 20}, {7, 21}, {64, 22}, POSE_END};
static AnimateEntityFrame anim_step9[] = {{7, 23}, {7, 24}, {62, 25}, POSE_END};
static AnimateEntityFrame anim_step10[] = {
    {5, 25}, {5, 24}, {80, 23}, {5, 24}, {48, 25}, {48, 26}, POSE_END};
static AnimateEntityFrame anim_step11[] = {
    {7, 18}, {7, 36}, {7, 37}, {7, 38}, {7, 39}, {7, 40},
    {7, 12}, {7, 6},  {7, 5},  {7, 4},  {64, 3}, POSE_END};
static AnimateEntityFrame anim_step12[] = {
    {128, 2}, {80, 3}, {8, 41}, {96, 42}, POSE_END};
static AnimateEntityFrame anim_step13[] = {{1, 42}, {8, 43}, POSE_END};
static AnimateEntityFrame anim_step14[] = {
    {2, 44}, {4, 45}, {5, 46}, {4, 47}, {4, 48}, {4, 49}, {4, 50},
    {4, 51}, {5, 52}, {4, 53}, {4, 54}, {4, 55}, {2, 44}, POSE_LOOP(0)};
static s16 icon_richter_pos[] = {
    0xAC, 0x78, 0xA8, 0x78, 0xA2, 0x7A, 0x92, 0x80};
static s16 icon_trevor_pos[] = {0x50, 0xA0, 0x54, 0x9C, 0x5A, 0x9A, 0x6A, 0x9A};
static u8 icon_richter_uv[] = {0x58, 0x40, 0x60, 0x48, 0x50, 0x40, 0x58, 0x48,
                               0x50, 0x30, 0x60, 0x40, 0x60, 0x58, 0x80, 0x80};
static u8 icon_trevor_uv[] = {0x58, 0x40, 0x60, 0x48, 0x50, 0x40, 0x58, 0x48,
                              0x50, 0x30, 0x60, 0x40, 0x60, 0x30, 0x80, 0x58};
static u16 icon_clut[] = {
    PAL_ICON_RICHTER, PAL_ICON_RICHTER, PAL_ICON_RICHTER, PAL_ICON_TREVOR,
    PAL_ICON_RICHTER, PAL_ICON_RICHTER, PAL_ICON_RICHTER, PAL_ICON_RICHTER};

void EntityActorMaria(Entity* self) {
    Tilemap* tilemap = &g_Tilemap;

    if (g_SkipCutscene && self->step < 13) {
        SetStep(13);
    }
    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitObtainable);
        self->animSet = ANIMSET_OVL(4);
        self->animCurFrame = 1;
        self->unk5A = 0x50;
        self->palette = PAL_ACTOR_MARIA;
        self->hitboxState = 0;
        self->posX.i.hi = 448 - tilemap->scrollX.i.hi;
        break;
    case 1:
        if (g_CutsceneFlags & 4) {
            self->step++;
        }
        break;
    case 2:
        self->animCurFrame = 2;
        if (g_CutsceneFlags & 8) {
            self->step++;
        }
        break;
    case 3:
        AnimateEntity(anim_step3, self);
        if (g_CutsceneFlags & 0x10) {
            SetStep(4);
        }
        break;
    case 4:
        AnimateEntity(anim_step4, self);
        if (g_CutsceneFlags & 0x20) {
            SetStep(5);
        }
        break;
    case 5:
        AnimateEntity(anim_step5, self);
        if (g_CutsceneFlags & 0x40) {
            SetStep(6);
        }
        break;
    case 6:
        AnimateEntity(anim_step6, self);
        if (g_CutsceneFlags & 0x80) {
            SetStep(7);
        }
        break;
    case 7:
        AnimateEntity(anim_step7, self);
        if (g_CutsceneFlags & 0x100) {
            SetStep(8);
        }
        break;
    case 8:
        AnimateEntity(anim_step8, self);
        if (g_CutsceneFlags & 0x200) {
            SetStep(9);
        }
        break;
    case 9:
        AnimateEntity(anim_step9, self);
        if (g_CutsceneFlags & 0x400) {
            SetStep(10);
        }
        break;
    case 10:
        AnimateEntity(anim_step10, self);
        if (g_CutsceneFlags & 0x800) {
            SetStep(11);
        }
        break;
    case 11:
        AnimateEntity(anim_step11, self);
        if (g_CutsceneFlags & 0x1000) {
            SetStep(12);
        }
        break;
    case 12:
        AnimateEntity(anim_step12, self);
        if (g_CutsceneFlags & 0x2000) {
            SetStep(13);
        }
        break;
    case 13:
        if (!AnimateEntity(anim_step13, self)) {
            self->velocityX = FIX(0.75);
            SetStep(14);
        }
        break;
    case 14:
        AnimateEntity(anim_step14, self);
        MoveEntity();
        if (self->posX.i.hi > 272) {
            g_CutsceneFlags |= 2;
            DestroyEntity(self);
        }
        break;
    }
}

static void ModifyPolySize(Primitive* prim, s16 mod) {
    prim->x0 = prim->x2 -= mod;
    prim->x1 = prim->x3 += mod;
    prim->y0 = prim->y1 -= mod;
    prim->y2 = prim->y3 += mod;
}

static void SpeechBalloonBelmont(Entity* self, u16 isTrevor) {
    Primitive* prim;
    s16* pos;
    u8* uv;
    s32 primIndex;
    s32 i;

    if (g_SkipCutscene) {
        DestroyEntity(self);
    }
    switch (self->step) {
    case 0:
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 4);
        if (primIndex == -1) {
            break;
        }
        InitializeEntity(g_EInitSpawner);
        self->flags |= FLAG_HAS_PRIMS;
        self->primIndex = primIndex;
        self->animSet = ANIMSET_OVL(0);
        prim = &g_PrimBuf[primIndex];
        if (!isTrevor) {
            pos = icon_richter_pos;
            uv = icon_richter_uv;
        } else {
            pos = icon_trevor_pos;
            uv = icon_trevor_uv;
        }
        for (i = 0; i < 4; i++) {
            prim->tpage = 0x14;
            prim->clut = icon_clut[isTrevor * 4 + i];
            prim->x0 = prim->x1 = prim->x2 = prim->x3 = *pos++;
            prim->y0 = prim->y1 = prim->y2 = prim->y3 = *pos++;
            prim->u0 = prim->u2 = *uv++;
            prim->v0 = prim->v1 = *uv++;
            prim->u1 = prim->u3 = *uv++;
            prim->v2 = prim->v3 = *uv++;
            prim->priority = self->zPriority;
            prim->drawMode = DRAW_DEFAULT;
            prim = prim->next;
        }
        self->ext.cutscenePrims.timer = 0;
        break;
    case 1:
        prim = &g_PrimBuf[self->primIndex];
        if (self->ext.cutscenePrims.timer & 1) {
            ModifyPolySize(prim, 1);
        }
        if (++self->ext.cutscenePrims.timer >= 8) {
            self->ext.cutscenePrims.timer = 0;
            self->step++;
        }
        break;
    case 2:
        prim = &g_PrimBuf[self->primIndex];
        prim = prim->next;
        if (self->ext.cutscenePrims.timer & 1) {
            ModifyPolySize(prim, 1);
        }
        if (++self->ext.cutscenePrims.timer >= 8) {
            self->ext.cutscenePrims.timer = 0;
            self->step++;
        }
        break;
    case 3:
        prim = &g_PrimBuf[self->primIndex];
        prim = prim->next;
        prim = prim->next;
        ModifyPolySize(prim, 1);
        if (++self->ext.cutscenePrims.timer >= 8) {
            self->ext.cutscenePrims.timer = 0;
            self->step++;
        }
        break;
    case 4:
        prim = &g_PrimBuf[self->primIndex];
        prim = prim->next;
        prim = prim->next;
        prim = prim->next;
        ModifyPolySize(prim, 2);
        if (self->ext.cutscenePrims.timer & 1) {
            prim->y0 = prim->y1 -= 1;
            prim->y2 = prim->y3 += 1;
        }
        if (++self->ext.cutscenePrims.timer >= 8) {
            self->ext.cutscenePrims.timer = 0;
            self->step++;
        }
        break;
    case 5:
        if (++self->ext.cutscenePrims.timer >= 0xC0) {
            self->ext.cutscenePrims.timer = 0;
            self->step++;
        }
        break;
    case 6:
        prim = &g_PrimBuf[self->primIndex];
        prim = prim->next;
        prim = prim->next;
        prim = prim->next;
        ModifyPolySize(prim, -2);
        if (self->ext.cutscenePrims.timer & 1) {
            prim->y0 = prim->y1 += 1;
            prim->y2 = prim->y3 -= 1;
        }
        if (++self->ext.cutscenePrims.timer >= 8) {
            self->ext.cutscenePrims.timer = 0;
            self->step++;
        }
        break;
    case 7:
        prim = &g_PrimBuf[self->primIndex];
        prim = prim->next;
        prim = prim->next;
        ModifyPolySize(prim, -1);
        if (++self->ext.cutscenePrims.timer >= 8) {
            self->ext.cutscenePrims.timer = 0;
            self->step++;
        }
        break;
    case 8:
        prim = &g_PrimBuf[self->primIndex];
        prim = prim->next;
        if (self->ext.cutscenePrims.timer & 1) {
            ModifyPolySize(prim, -1);
        }
        if (++self->ext.cutscenePrims.timer >= 8) {
            self->ext.cutscenePrims.timer = 0;
            self->step++;
        }
        break;
    case 9:
        prim = &g_PrimBuf[self->primIndex];
        if (self->ext.cutscenePrims.timer & 1) {
            ModifyPolySize(prim, -1);
        }
        if (++self->ext.cutscenePrims.timer >= 8) {
            DestroyEntity(self);
        }
        break;
    }
}

void EntitySpeechBalloonRichter(Entity* self) { SpeechBalloonBelmont(self, 0); }

void EntitySpeechBalloonTrevor(Entity* self) { SpeechBalloonBelmont(self, 1); }
