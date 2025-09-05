// SPDX-License-Identifier: AGPL-3.0-or-later
#include "dai.h"

#ifdef VERSION_PSP
extern s32 E_ID(CONFESSIONAL_BLADES);
extern s32 E_ID(CONFESSIONAL_BLADE_DEBRIS);
#endif

typedef struct {
    /* 0x00 */ u8* anim1;
    /* 0x04 */ u8* anim2;
    /* 0x08 */ u8* anim3;
    /* 0x0C */ u8* anim4;
} ConfessionalGhostAnimSet;
typedef struct {
    /* 0x00 */ s16 x0;
    /* 0x02 */ s16 x1;
    /* 0x04 */ s16 x2;
    /* 0x06 */ s16 xVal;
    /* 0x08 */ s16 xHi;
    /* 0x0A */ s16 x3;
    /* 0x0C */ ConfessionalGhostAnimSet* animations;
} ConfessionalGhostParams;

extern bool g_confessionalChimeActive;

static u8 anim_a_1[] = {
    9, 12, 15, 13, 15, 14, 9, 15, 15, 14, 15, 13, 0, 0, 0, 0};
static u8 anim_a_2[] = {64, 1, 22, 2, 0, 0, 0, 0};
static u8 anim_a_3[] = {34, 1, 11, 3, 11, 4, 11, 5,  11, 6,  11, 7,
                        11, 8, 11, 7, 11, 9, 41, 10, 11, 11, -1, 0};
static u8 anim_a_4[] = {
    9, 16, 5, 17, 24, 18, 12, 19, 12, 18, 12, 19, 12, 18, 60, 19, -1, 0, 0, 0};
static u8 anim_b_1[] = {12, 29, 15, 30, 12, 31, 15, 30, 0, 0, 0, 0};
static u8 anim_b_2[] = {11, 20, 16, 21, 16, 22, 16, 21, 16, 20, 16, 21, 16, 22,
                        11, 23, 11, 22, 11, 23, 11, 22, 11, 23, 0,  0,  0,  0};
static u8 anim_b_3[] = {
    27, 22, 13, 24, 23, 25, 16, 26, 11, 27, 11, 28, 11, 27, 102, 26, -1};
static u8 anim_b_4[] = {
    60, 29, 12, 32, 12, 33, 9, 34, 9, 35, 9, 34, 9, 35, 9, 34, 25, 35, -1};
static s16 sensors_1[] = {0, 19, 8, 0};
static s16 sensors_2[] = {0, 19, 0, 4, 8, -4, -16, 0};
static s16 xyx_vals[][3] = {
    {120, 140, 104},
    {120, 172, 104},
    {118, 152, 110},
    {118, 180, 110},
    {104, 160, 136}};
static ConfessionalGhostAnimSet animset_a = {
    anim_a_1, anim_a_2, anim_a_3, anim_a_4};
static ConfessionalGhostAnimSet animset_b = {
    anim_b_1, anim_b_2, anim_b_3, anim_b_4};
static ConfessionalGhostParams params[] = {
    {120, 132, 160, FIX(0.75), 144, 4, &animset_a},
    {119, 108, 64, FIX(0.25), 100, -4, &animset_b}};
static s16 unused[] = {
    8, 1, 8, 2, 16, 3, 8, 4, 23, 5, 4, 6, -1, 0, 8, 1, 8, 2, 4, 7, -1, 0};

void EntityConfessionalGhost(Entity* self) {
    Entity* entity;
    Primitive* prim;
    s32 primIndex;
    ConfessionalGhostParams* paramsPtr;
    u8* animPtr;

    g_unkGraphicsStruct.pauseEnemies = true;
    paramsPtr = &params[self->params & 1];
    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitConfessionalGhost);
        if (self->params & 0x100) {
            self->palette = PAL_CONFESSIONAL_CE;
        } else {
            self->palette = PAL_CONFESSIONAL_C9;
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
        prim->clut = PAL_CONFESSIONAL_CC;
        prim->u0 = prim->u2 = 0;
        prim->u1 = prim->u3 = 39;
        prim->v0 = prim->v1 = 0;
        prim->v2 = prim->v3 = 64;
        prim->x0 = prim->x2 = paramsPtr->x0;
        prim->x1 = prim->x3 = paramsPtr->x1;
        prim->y0 = prim->y1 = 122;
        prim->y3 = prim->y2 = 186;
        prim->priority = 159;
        prim->drawMode = DRAW_DEFAULT;
#ifdef VERSION_PSP
        self->ext.confessionalGhost.unk88 = 0;
        if (self->params & 1) {
            func_892A620(0, 1);
        }
        break;
    case 1:
        self->ext.confessionalGhost.unk88++;
        if ((self->ext.confessionalGhost.unk88 == 1) && (self->params & 1)) {
            g_api.PlaySfx(SFX_UNK_PSP_304);
            g_confessionalChimeActive = true;
            D_80097928 = 0;
        }
        break;
#else
        if (self->params & 1) {
            g_api.PlaySfx(SET_UNK_90);
            g_api.PlaySfx(SFX_UNK_204);
            D_80097928 = 0;
            g_confessionalChimeActive = true;
        }
        break;
    case 1:
        break;
#endif
    case 2:
        if (UnkCollisionFunc3(sensors_2) & 1) {
            self->step++;
        }
        break;
    case 3:
        self->opacity += 4;
        if (self->opacity > 192) {
            self->opacity = 192;
        }
        animPtr = paramsPtr->animations->anim1;
        AnimateEntity(animPtr, self);
        UnkCollisionFunc2(sensors_1);
        self->posX.val += paramsPtr->xVal;
        if (self->posX.i.hi == paramsPtr->xHi) {
            self->posX.i.hi = paramsPtr->xHi;
            if (self->params & 0x100) {
                SetStep(6);
            } else {
                SetStep(4);
#ifdef VERSION_PSP
                if (!(self->params & 1)) {
                    g_api.PlaySfx(SFX_UNK_4E5);
                }
#endif
            }
        }
        if ((PLAYER.step != 0) || (PLAYER.step_s != 4)) {
            SetStep(13);
        }
        break;
    case 4:
        animPtr = paramsPtr->animations->anim2;
        AnimateEntity(animPtr, self);
        if (!(self->params & 1)) {
            switch (self->step_s) {
            case 0:
#ifdef VERSION_PSP
                if (g_api.func_80131F68() == 1) {
                    self->ext.confessionalGhost.unk80 = 288;
                    self->step_s++;
                }
#else
                self->ext.confessionalGhost.unk80 = 256;
                self->step_s++;
#endif
                break;
            case 1:
                FntPrint("timer %x\n", self->ext.confessionalGhost.unk80);
                if (!--self->ext.confessionalGhost.unk80) {
                    SetStep(5);
                }
                break;
            }
            if ((PLAYER.step != 0) || ((PLAYER.step_s) != 4)) {
                self->ext.confessionalGhost.unk80 = 1;
#ifdef VERSION_PSP
                if (g_api.func_80131F68()) {
                    g_api.PlaySfx(SET_UNK_90);
                }
#endif
                SetStep(5);
            }
        } else if ((PLAYER.step != 0) || (PLAYER.step_s != 4)) {
#ifdef VERSION_PSP
            if (g_api.func_80131F68()) {
                g_api.PlaySfx(SET_UNK_90);
            }
#endif
            SetStep(5);
        }
        break;
    case 5:
        animPtr = paramsPtr->animations->anim3;
        AnimateEntity(animPtr, self);
#ifdef VERSION_PSP
        if ((self->ext.confessionalGhost.unk80) && (g_api.func_80131F68())) {
            g_api.PlaySfx(SET_UNK_90);
        }
#endif
        if (!(--self->opacity)) {
            if (!(self->params & 1) && (!self->ext.confessionalGhost.unk80) &&
                !(Random() & 3)) {
                entity = AllocEntity(&g_Entities[160], &g_Entities[192]);
                if (entity != NULL) {
                    CreateEntityFromEntity(E_EQUIP_ITEM_DROP, self, entity);
                    entity->params = 56;
                }
            }
            SetStep(128);
        }
        break;
    case 6:
        animPtr = paramsPtr->animations->anim4;
        if (!AnimateEntity(animPtr, self)) {
            // Curtain closing
            g_api.PlaySfx(SFX_UNK_7BB);
            self->step++;
        }
        break;
    case 7:
        prim = self->ext.confessionalGhost.prim;
        prim->x1 = prim->x3 += paramsPtr->x3;
        if (prim->x1 == paramsPtr->x2) {
            prim->x1 = prim->x3 = paramsPtr->x2;
            self->ext.confessionalGhost.unk80 = 16;
            self->step++;
        }
        break;
    case 8:
        if (!--self->ext.confessionalGhost.unk80) {
            if (self->params & 1) {
                SetStep(10);
            } else {
                SetStep(9);
            }
        }
        if (self->ext.confessionalGhost.unk80 & 2) {
            self->ext.confessionalGhost.unk86 = -1;
        } else {
            self->ext.confessionalGhost.unk86 = 1;
        }
        prim = self->ext.confessionalGhost.prim;
        prim->x2 = paramsPtr->x0 + self->ext.confessionalGhost.unk86;
        prim->x3 = paramsPtr->x2 + self->ext.confessionalGhost.unk86;
        return;
    case 9:
        switch (self->step_s) {
        case 0:
            self->ext.confessionalGhost.unk80 = 32;
            self->ext.confessionalGhost.unk84 = 0;
            self->step_s++;
            // fallthrough
        case 1:
            if (!--self->ext.confessionalGhost.unk80) {
                entity = AllocEntity(&g_Entities[160], &g_Entities[192]);
                if (entity != NULL) {
                    CreateEntityFromCurrentEntity(
                        E_ID(CONFESSIONAL_BLADES), entity);
                    entity->params = self->ext.confessionalGhost.unk84;
                }
                self->ext.confessionalGhost.unk84++;
                self->ext.confessionalGhost.unk80 = 16;
                if (self->ext.confessionalGhost.unk84 > 3) {
                    self->ext.confessionalGhost.unk80 = 128;
                    self->step_s++;
                }
            }
            break;
        case 2:
            if (!--self->ext.confessionalGhost.unk80) {
                SetStep(11);
            }
            break;
        }
        break;
    case 10:
        switch (self->step_s) {
        case 0:
            self->ext.confessionalGhost.unk80 = 32;
            self->step_s++;
            // fallthrough
        case 1:
            if (!--self->ext.confessionalGhost.unk80) {
                entity = AllocEntity(&g_Entities[160], &g_Entities[192]);
                if (entity != NULL) {
                    CreateEntityFromCurrentEntity(
                        E_ID(CONFESSIONAL_BLADES), entity);
                    entity->params = 4;
                }
                self->ext.confessionalGhost.unk80 = 128;
                self->step_s++;
            }
            break;
        case 2:
            if (!--self->ext.confessionalGhost.unk80) {
                SetStep(11);
            }
            break;
        }
        break;
    case 11:
        self->opacity -= 32;
        if ((self->opacity) > 192) {
            self->animCurFrame = 0;
        }
        prim = self->ext.confessionalGhost.prim;
        prim->x3 = prim->x1 -= paramsPtr->x3;
        if (prim->x1 == paramsPtr->x1) {
            prim->x1 = prim->x3 = paramsPtr->x1;
            SetStep(14);
        }
        break;
    case 13:
        self->opacity -= 4;
        if ((self->opacity) > 192) {
            self->animCurFrame = 0;
            SetStep(14);
        }
        break;
    case 14:
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
            entity->params = 1;
        }
        DestroyEntity(self);
        return;
    }
    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitConfessionalBlades);
        self->zPriority = 158;
        params = self->params;
        self->animCurFrame += params;
        self->posX.i.hi = xyx_vals[params][0];
        self->posY.i.hi = xyx_vals[params][1];
        if (params == 4) {
            self->step = 3;
        } else {
            self->step = 1;
        }
        self->ext.confessionalGhost.unk80 = 128;
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
    case 1:
        params = self->params;
        self->posX.val += FIX(-2.5);
        if (self->posX.i.hi < xyx_vals[params][2]) {
            self->posX.i.hi = xyx_vals[params][2];
            self->ext.confessionalGhost.unk80 = 96;
            SetStep(2);
        }
        break;
    case 2:
        if (self->ext.confessionalGhost.unk80) {
            self->ext.confessionalGhost.unk80--;
            return;
        }
        params = self->params;
        self->posX.val += FIX(2.5);
        if (self->posX.i.hi > xyx_vals[params][0]) {
            DestroyEntity(self);
        }
        break;
    case 3:
        params = self->params;
        self->posX.val += FIX(3.5);
        if (self->posX.i.hi > xyx_vals[params][2]) {
            self->posX.i.hi = xyx_vals[params][2];
            self->ext.confessionalGhost.unk80 = 96;
            SetStep(4);
        }
        break;
    case 4:
        if (self->ext.confessionalGhost.unk80) {
            self->ext.confessionalGhost.unk80--;
            return;
        }
        params = self->params;
        self->posX.val += FIX(-3.5);
        if (self->posX.i.hi < xyx_vals[params][0]) {
            DestroyEntity(self);
        }
        break;
    case 5:
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
        self->ext.confessionalGhost.unk80 = ((Random() & 0x3F) + 16);
    }
    MoveEntity();
    self->velocityY += FIX(0.125);
    if (self->params) {
        self->rotate += 32;
    } else {
        self->rotate -= 32;
    }
    if (!--self->ext.confessionalGhost.unk80) {
        DestroyEntity(self);
    }
}
