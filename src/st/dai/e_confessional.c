// SPDX-License-Identifier: AGPL-3.0-or-later
#include "dai.h"

enum ConfessionalSteps {
    CONFESSIONAL_INIT,
    CONFESSIONAL_CHIME_ACTIVATE,
    CONFESSIONAL_CHECK_SEATED,
    CONFESSIONAL_GHOST_MOVE,
    CONFESSIONAL_GHOST_GOOD_SIT,
    CONFESSIONAL_GHOST_GOOD_DEPART,
    CONFESSIONAL_GHOST_BAD_SIT,
    CONFESSIONAL_GHOST_CLOSE_CURTAIN,
    CONFESSIONAL_GHOST_PREPARE_BLADES,
    CONFESSIONAL_GHOST_BLADES_PRIEST,
    CONFESSIONAL_GHOST_BLADES_PARISHIONER,
    CONFESSIONAL_GHOST_BAD_DEPART,
    CONFESSIONAL_GHOST_UNUSED_12,
    CONFESSIONAL_GHOST_BREAK,
    CONFESSIONAL_GHOST_COMPLETE,
};

enum ConfessionalGhostSubsteps {
    CONFESSIONAL_GHOST_GOOD_INIT,
    CONFESSIONAL_GHOST_GOOD_PRAY,
};

enum ConfessionalGhostBladesSubsteps {
    CONFESSIONAL_GHOST_BLADES_INIT,
    CONFESSIONAL_GHOST_BLADES_ATTACK,
    CONFESSIONAL_GHOST_BLADES_RETRACT,
};

enum ConfessionalBladesSteps {
    CONFESSIONAL_BLADES_INIT,
    CONFESSIONAL_BLADES_PRIEST_INIT,
    CONFESSIONAL_BLADES_PRIEST_ATTACK,
    CONFESSIONAL_BLADES_PARISHIONER_INIT,
    CONFESSIONAL_BLADES_PARISHIONER_ATTACK,
    CONFESSIONAL_BLADES_NOP,
};

typedef struct {
    AnimateEntityFrame* anim_move;
    AnimateEntityFrame* anim_sit_good;
    AnimateEntityFrame* anim_depart;
    AnimateEntityFrame* anim_sit_bad;
} ConfessionalGhostAnimSet;

typedef struct {
    s16 x0;
    s16 x1;
    s16 x2;
    s16 xVal;
    s16 xHi;
    s16 x3;
    ConfessionalGhostAnimSet* animations;
} ConfessionalGhost;

#ifdef VERSION_PSP
extern s32 E_ID(CONFESSIONAL_BLADES);
extern s32 E_ID(CONFESSIONAL_BLADE_DEBRIS);
#endif

extern bool g_confessionalChimeActive;

static AnimateEntityFrame anim_priest_move[] = {
    {9, 12}, {15, 13}, {15, 14}, {9, 15}, {15, 14}, {15, 13}, POSE_LOOP(0)};
static AnimateEntityFrame anim_priest_sit_good[] = {
    {64, 1}, {22, 2}, POSE_LOOP(0)};
static AnimateEntityFrame anim_priest_depart[] = {
    {34, 1}, {11, 3}, {11, 4}, {11, 5},  {11, 6},  {11, 7},
    {11, 8}, {11, 7}, {11, 9}, {41, 10}, {11, 11}, POSE_END};
static AnimateEntityFrame anim_priest_sit_bad[] = {
    {9, 16},  {5, 17},  {24, 18}, {12, 19}, {12, 18},
    {12, 19}, {12, 18}, {60, 19}, POSE_END};
static AnimateEntityFrame anim_parishioner_move[] = {
    {12, 29}, {15, 30}, {12, 31}, {15, 30}, POSE_LOOP(0)};
static AnimateEntityFrame anim_parishioner_sit_good[] = {
    {11, 20}, {16, 21}, {16, 22}, {16, 21}, {16, 20}, {16, 21},    {16, 22},
    {11, 23}, {11, 22}, {11, 23}, {11, 22}, {11, 23}, POSE_LOOP(0)};
static AnimateEntityFrame anim_parishioner_depart[] = {
    {27, 22}, {13, 24}, {23, 25},  {16, 26}, {11, 27},
    {11, 28}, {11, 27}, {102, 26}, POSE_END};
static AnimateEntityFrame anim_parishioner_sit_bad[] = {
    {60, 29}, {12, 32}, {12, 33}, {9, 34},  {9, 35},
    {9, 34},  {9, 35},  {9, 34},  {25, 35}, POSE_END};
static s16 sensors_ghost[] = {0, 19, 8, 0};
static s16 sensors_seated[] = {0, 19, 0, 4, 8, -4, -16, 0};
static s16 xyx_vals[][3] = {
    {120, 140, 104},
    {120, 172, 104},
    {118, 152, 110},
    {118, 180, 110},
    {104, 160, 136}};
static ConfessionalGhostAnimSet animset_priest = {
    anim_priest_move, anim_priest_sit_good, anim_priest_depart,
    anim_priest_sit_bad};
static ConfessionalGhostAnimSet animset_parishioner = {
    anim_parishioner_move, anim_parishioner_sit_good, anim_parishioner_depart,
    anim_parishioner_sit_bad};
static ConfessionalGhost confessional_ghosts[] = {
    {120, 132, 160, FIX(0.75), 144, 4, &animset_priest},
    {119, 108, 64, FIX(0.25), 100, -4, &animset_parishioner}};
static s16 unused[] = {
    8, 1, 8, 2, 16, 3, 8, 4, 23, 5, 4, 6, -1, 0, 8, 1, 8, 2, 4, 7, -1, 0};

void EntityConfessionalGhost(Entity* self) {
    Entity* entity;
    Primitive* prim;
    s32 primIndex;
    ConfessionalGhost* ghost;
    AnimateEntityFrame* animPtr;

    g_unkGraphicsStruct.pauseEnemies = true;
    ghost = &confessional_ghosts[self->params & CONFESSIONAL_GHOST_PARISHIONER];
    switch (self->step) {
    case CONFESSIONAL_INIT:
        InitializeEntity(g_EInitConfessionalGhost);
        // Default palette is the good ghost
        if (self->params & CONFESSIONAL_GHOST_BAD) {
            self->palette = PAL_CONFESSIONAL_GHOST_BAD;
        } else {
            self->palette = PAL_CONFESSIONAL_GHOST;
        }
        self->opacity = 0;
        self->drawMode = DRAW_TPAGE2 | DRAW_TPAGE;
        self->drawFlags |= FLAG_DRAW_OPACITY;
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 1);
        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags |= FLAG_HAS_PRIMS;
        self->primIndex = primIndex;
        prim = &g_PrimBuf[primIndex];
        self->ext.confessionalGhost.prim = prim;
        prim->tpage = 18;
        prim->clut = PAL_CONFESSIONAL_CLUT;
        prim->u0 = prim->u2 = 0;
        prim->u1 = prim->u3 = 39;
        prim->v0 = prim->v1 = 0;
        prim->v2 = prim->v3 = 64;
        prim->x0 = prim->x2 = ghost->x0;
        prim->x1 = prim->x3 = ghost->x1;
        prim->y0 = prim->y1 = 122;
        prim->y3 = prim->y2 = 186;
        prim->priority = 159;
        prim->drawMode = DRAW_DEFAULT;
#ifdef VERSION_PSP
        self->ext.confessionalGhost.activateChime = false;
        if (self->params & CONFESSIONAL_GHOST_PARISHIONER) {
            func_892A620(0, 1);
        }
        break;
    case CONFESSIONAL_CHIME_ACTIVATE:
        self->ext.confessionalGhost.activateChime++;
        if ((self->ext.confessionalGhost.activateChime == true) &&
            (self->params & CONFESSIONAL_GHOST_PARISHIONER)) {
            g_api.PlaySfx(SFX_UNK_PSP_304);
            g_confessionalChimeActive = true;
            D_80097928 = 0;
        }
        break;
#else
        if (self->params & CONFESSIONAL_GHOST_PARISHIONER) {
            g_api.PlaySfx(SET_UNK_90);
            g_api.PlaySfx(SFX_UNK_204);
            D_80097928 = 0;
            g_confessionalChimeActive = true;
        }
        break;
    case CONFESSIONAL_CHIME_ACTIVATE:
        break;
#endif
    case CONFESSIONAL_CHECK_SEATED: // This step is set by EntityChair
        if (UnkCollisionFunc3(sensors_seated) & 1) {
            self->step++;
        }
        break;
    case CONFESSIONAL_GHOST_MOVE:
        self->opacity += 4;
        if (self->opacity > 192) {
            self->opacity = 192;
        }
        animPtr = ghost->animations->anim_move;
        AnimateEntity(animPtr, self);
        UnkCollisionFunc2(sensors_ghost);
        self->posX.val += ghost->xVal;
        if (self->posX.i.hi == ghost->xHi) {
            self->posX.i.hi = ghost->xHi;
            if (self->params & CONFESSIONAL_GHOST_BAD) {
                SetStep(CONFESSIONAL_GHOST_BAD_SIT);
            } else {
                SetStep(CONFESSIONAL_GHOST_GOOD_SIT);
#ifdef VERSION_PSP
                if (!(self->params & CONFESSIONAL_GHOST_PARISHIONER)) {
                    g_api.PlaySfx(SFX_UNK_4E5);
                }
#endif
            }
        }
        if ((PLAYER.step != Player_Stand) ||
            (PLAYER.step_s != Player_Stand_ChairSit)) {
            SetStep(CONFESSIONAL_GHOST_BREAK);
        }
        break;
    case CONFESSIONAL_GHOST_GOOD_SIT:
        animPtr = ghost->animations->anim_sit_good;
        AnimateEntity(animPtr, self);
        if (!(self->params & CONFESSIONAL_GHOST_PARISHIONER)) {
            switch (self->step_s) {
            case CONFESSIONAL_GHOST_GOOD_INIT:
#ifdef VERSION_PSP
                if (g_api.func_80131F68() == 1) {
                    self->ext.confessionalGhost.timer = 288;
                    self->step_s++;
                }
#else
                self->ext.confessionalGhost.timer = 256;
                self->step_s++;
#endif
                break;
            case CONFESSIONAL_GHOST_GOOD_PRAY:
                FntPrint("timer %x\n", self->ext.confessionalGhost.timer);
                if (!--self->ext.confessionalGhost.timer) {
                    SetStep(CONFESSIONAL_GHOST_GOOD_DEPART);
                }
                break;
            }
            if ((PLAYER.step != Player_Stand) ||
                ((PLAYER.step_s) != Player_Stand_ChairSit)) {
                self->ext.confessionalGhost.timer = 1;
#ifdef VERSION_PSP
                if (g_api.func_80131F68()) {
                    g_api.PlaySfx(SET_UNK_90);
                }
#endif
                SetStep(CONFESSIONAL_GHOST_GOOD_DEPART);
            }
        } else if ((PLAYER.step != Player_Stand) ||
                   (PLAYER.step_s != Player_Stand_ChairSit)) {
#ifdef VERSION_PSP
            if (g_api.func_80131F68()) {
                g_api.PlaySfx(SET_UNK_90);
            }
#endif
            SetStep(CONFESSIONAL_GHOST_GOOD_DEPART);
        }
        break;
    case CONFESSIONAL_GHOST_GOOD_DEPART:
        animPtr = ghost->animations->anim_depart;
        AnimateEntity(animPtr, self);
#ifdef VERSION_PSP
        if ((self->ext.confessionalGhost.timer) && (g_api.func_80131F68())) {
            g_api.PlaySfx(SET_UNK_90);
        }
#endif
        if (!(--self->opacity)) {
            if (!(self->params & CONFESSIONAL_GHOST_PARISHIONER) &&
                (!self->ext.confessionalGhost.timer) && !(Random() & 3)) {
                entity = AllocEntity(&g_Entities[160], &g_Entities[192]);
                if (entity != NULL) {
                    CreateEntityFromEntity(E_EQUIP_ITEM_DROP, self, entity);
                    entity->params = ITEM_GRAPE_JUICE;
                }
            }
            SetStep(128); // No case defined, resulting in nop
        }
        break;
    case CONFESSIONAL_GHOST_BAD_SIT:
        animPtr = ghost->animations->anim_sit_bad;
        if (!AnimateEntity(animPtr, self)) {
            // Curtain closing sound
            g_api.PlaySfx(SFX_UNK_7BB);
            self->step++;
        }
        break;
    case CONFESSIONAL_GHOST_CLOSE_CURTAIN:
        prim = self->ext.confessionalGhost.prim;
        prim->x1 = prim->x3 += ghost->x3;
        if (prim->x1 == ghost->x2) {
            prim->x1 = prim->x3 = ghost->x2;
            self->ext.confessionalGhost.timer = 16;
            self->step++;
        }
        break;
    case CONFESSIONAL_GHOST_PREPARE_BLADES:
        if (!--self->ext.confessionalGhost.timer) {
            if (self->params & CONFESSIONAL_GHOST_PARISHIONER) {
                SetStep(CONFESSIONAL_GHOST_BLADES_PARISHIONER);
            } else {
                SetStep(CONFESSIONAL_GHOST_BLADES_PRIEST);
            }
        }
        if (self->ext.confessionalGhost.timer & 2) {
            self->ext.confessionalGhost.curtainShake = -1;
        } else {
            self->ext.confessionalGhost.curtainShake = 1;
        }
        prim = self->ext.confessionalGhost.prim;
        prim->x2 = ghost->x0 + self->ext.confessionalGhost.curtainShake;
        prim->x3 = ghost->x2 + self->ext.confessionalGhost.curtainShake;
        return;
    case CONFESSIONAL_GHOST_BLADES_PRIEST:
        switch (self->step_s) {
        case CONFESSIONAL_GHOST_BLADES_INIT:
            self->ext.confessionalGhost.timer = 32;
            self->ext.confessionalGhost.numBlades = 0;
            self->step_s++;
            // fallthrough
        case CONFESSIONAL_GHOST_BLADES_ATTACK:
            if (!--self->ext.confessionalGhost.timer) {
                entity = AllocEntity(&g_Entities[160], &g_Entities[192]);
                if (entity != NULL) {
                    CreateEntityFromCurrentEntity(
                        E_ID(CONFESSIONAL_BLADES), entity);
                    entity->params = self->ext.confessionalGhost.numBlades;
                }
                self->ext.confessionalGhost.numBlades++;
                self->ext.confessionalGhost.timer = 16;
                if (self->ext.confessionalGhost.numBlades > 3) {
                    self->ext.confessionalGhost.timer = 128;
                    self->step_s++;
                }
            }
            break;
        case CONFESSIONAL_GHOST_BLADES_RETRACT:
            if (!--self->ext.confessionalGhost.timer) {
                SetStep(CONFESSIONAL_GHOST_BAD_DEPART);
            }
            break;
        }
        break;
    case CONFESSIONAL_GHOST_BLADES_PARISHIONER:
        switch (self->step_s) {
        case CONFESSIONAL_GHOST_BLADES_INIT:
            self->ext.confessionalGhost.timer = 32;
            self->step_s++;
            // fallthrough
        case CONFESSIONAL_GHOST_BLADES_ATTACK:
            if (!--self->ext.confessionalGhost.timer) {
                entity = AllocEntity(&g_Entities[160], &g_Entities[192]);
                if (entity != NULL) {
                    CreateEntityFromCurrentEntity(
                        E_ID(CONFESSIONAL_BLADES), entity);
                    entity->params = 4;
                }
                self->ext.confessionalGhost.timer = 128;
                self->step_s++;
            }
            break;
        case CONFESSIONAL_GHOST_BLADES_RETRACT:
            if (!--self->ext.confessionalGhost.timer) {
                SetStep(CONFESSIONAL_GHOST_BAD_DEPART);
            }
            break;
        }
        break;
    case CONFESSIONAL_GHOST_BAD_DEPART:
        self->opacity -= 32;
        if ((self->opacity) > 192) {
            self->animCurFrame = 0;
        }
        prim = self->ext.confessionalGhost.prim;
        prim->x3 = prim->x1 -= ghost->x3;
        if (prim->x1 == ghost->x1) {
            prim->x1 = prim->x3 = ghost->x1;
            SetStep(CONFESSIONAL_GHOST_COMPLETE);
        }
        break;
    case CONFESSIONAL_GHOST_BREAK:
        self->opacity -= 4;
        if ((self->opacity) > 192) {
            self->animCurFrame = 0;
            SetStep(CONFESSIONAL_GHOST_COMPLETE);
        }
        break;
    case CONFESSIONAL_GHOST_COMPLETE:
    default:
        self->animCurFrame = 0;
        break;
    }
}

void EntityConfessionalBlades(Entity* self) {
    Entity* entity;
    u32 params;
    s32 count;

    if (self->flags & FLAG_DEAD) {
        entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
        if (entity != NULL) {
            CreateEntityFromEntity(E_EXPLOSION, self, entity);
            entity->params = EXPLOSION_FIREBALL;
        }
        DestroyEntity(self);
        return;
    }
    switch (self->step) {
    case CONFESSIONAL_BLADES_INIT:
        InitializeEntity(g_EInitConfessionalBlades);
        self->zPriority = 158;
        params = self->params;
        self->animCurFrame += params;
        self->posX.i.hi = xyx_vals[params][0];
        self->posY.i.hi = xyx_vals[params][1];
        if (params == 4) {
            self->step = CONFESSIONAL_BLADES_PARISHIONER_INIT;
        } else {
            self->step = CONFESSIONAL_BLADES_PRIEST_INIT;
        }
        self->ext.confessionalGhost.timer = 128;
        for (count = 0; count < 4; count++) {
            entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (entity != NULL) {
                CreateEntityFromEntity(
                    E_ID(CONFESSIONAL_BLADE_DEBRIS), self, entity);
                if (params == 4) {
                    entity->params = 1;
                }
            }
        }
        g_api.PlaySfx(SFX_EXPLODE_B);
        break;
    case CONFESSIONAL_BLADES_PRIEST_INIT:
        params = self->params;
        self->posX.val += FIX(-2.5);
        if (self->posX.i.hi < xyx_vals[params][2]) {
            self->posX.i.hi = xyx_vals[params][2];
            self->ext.confessionalGhost.timer = 96;
            SetStep(CONFESSIONAL_BLADES_PRIEST_ATTACK);
        }
        break;
    case CONFESSIONAL_BLADES_PRIEST_ATTACK:
        if (self->ext.confessionalGhost.timer) {
            self->ext.confessionalGhost.timer--;
            return;
        }
        params = self->params;
        self->posX.val += FIX(2.5);
        if (self->posX.i.hi > xyx_vals[params][0]) {
            DestroyEntity(self);
        }
        break;
    case CONFESSIONAL_BLADES_PARISHIONER_INIT:
        params = self->params;
        self->posX.val += FIX(3.5);
        if (self->posX.i.hi > xyx_vals[params][2]) {
            self->posX.i.hi = xyx_vals[params][2];
            self->ext.confessionalGhost.timer = 96;
            SetStep(CONFESSIONAL_BLADES_PARISHIONER_ATTACK);
        }
        break;
    case CONFESSIONAL_BLADES_PARISHIONER_ATTACK:
        if (self->ext.confessionalGhost.timer) {
            self->ext.confessionalGhost.timer--;
            return;
        }
        params = self->params;
        self->posX.val += FIX(-3.5);
        if (self->posX.i.hi < xyx_vals[params][0]) {
            DestroyEntity(self);
        }
        break;
    case CONFESSIONAL_BLADES_NOP: // doesn't seem to be used anywhere
        break;
    }
}

void EntityConfessionalBladeDebris(Entity* self) {
    if (!self->step) {
        InitializeEntity(g_EInitConfessionalBlades);
        self->animCurFrame = 42;
        self->drawFlags |= FLAG_DRAW_ROTATE;
        self->zPriority = 158;
        if (self->params) {
            self->velocityX = (Random() << 8) + FIX(0.25);
        } else {
            self->velocityX = -((Random() << 8) + FIX(0.25));
        }
        self->velocityY = ((Random() * -256) - FIX(0.5)) - FIX(0.5);
        self->ext.confessionalGhost.timer = ((Random() & 0x3F) + 16);
    }
    MoveEntity();
    self->velocityY += FIX(0.125);
    if (self->params) {
        self->rotate += ROT(2.8125);
    } else {
        self->rotate -= ROT(2.8125);
    }
    if (!--self->ext.confessionalGhost.timer) {
        DestroyEntity(self);
    }
}
