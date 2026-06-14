// SPDX-License-Identifier: AGPL-3.0-or-later
#include "no1.h"

#ifdef VERSION_PSP
extern s32 E_ID(ID_33);
extern s32 E_ID(ID_5E);
extern s32 D_psp_091CE570;
#endif

#include "../../get_lang.h"

static s16 D_us_80181454[] = {-64, -32, -16, 0, 16, 32, 64};

static s16 D_us_80181464[] = {0x50, 0x60, 0x70, 0x80, 0x90, 0xA0, 0xB0};

u8 func_us_801B9184(Primitive* prim) {
    UnkPrimHelper(prim);

    switch (prim->next->u2) {
    case 0:
        prim->drawMode = DRAW_HIDE;
        break;

    case 1:
        prim->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS | DRAW_TRANSP;
        LOW(prim->next->u0) = -(D_us_80181454[prim->next->r3] << 0x10) / 16;
        prim->next->u2++;
        /* fallthrough */
    case 2:
        prim->next->b3 += 8;
        LOH(prim->next->u1) -= 64;
        if (LOH(prim->next->u1) <= 0) {
            LOH(prim->next->u1) = 0;
            LOW(prim->next->u0) = 0;
            prim->next->x1 = D_us_80181464[prim->next->r3];
            prim->next->u2++;

            prim->priority = 0xB0;
            prim->drawMode = DRAW_DEFAULT;
        }
        break;

    case 3:
        return 1;
    }
    return 0;
}

#ifdef VERSION_PSP
static u8 D_pspeu_09297E48[] = {
#include "gen/D_pspeu_09297E48.h"
};
static u8 D_pspeu_09298448[] = {
#include "gen/D_pspeu_09298448.h"
};
static u8 D_pspeu_09298A38[] = {
#include "gen/D_pspeu_09298A38.h"
};
static u8 D_pspeu_09299018[] = {
#include "gen/D_pspeu_09299018.h"
};
static u8 D_pspeu_09299608[] = {
#include "gen/D_pspeu_09299608.h"
};
static u_long* D_pspeu_09299BB0[] = {
    (u_long*)GFX_BANK_COMPRESSED,
    GFX_ENTRY(0x100, 0x40, 128, 128, D_pspeu_09297E48),
    GFX_TERMINATE(),
};

void func_pspeu_0925F440(void) {
    D_pspeu_09299BB0[3] =
        GetLang(D_pspeu_09297E48, D_pspeu_09299608, D_pspeu_09298448,
                D_pspeu_09299018, D_pspeu_09298A38);
    func_91040A0(D_pspeu_09299BB0);
}
#endif

void func_us_801B9304(Entity* self) {
    Primitive* prim;
    s32 primIndex;
    s32 i;
    s16 angle;
    u8 count;

#ifdef VERSION_PSP
    if (D_psp_091CE570) {
        func_pspeu_0925F440();
    }
#endif
    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitInteractable);
#ifdef VERSION_PSP
        func_pspeu_0925F440();
#endif
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 0xE);
        if (primIndex != -1) {
            self->flags |= FLAG_HAS_PRIMS;
            self->primIndex = primIndex;
            prim = &g_PrimBuf[primIndex];
            self->ext.et_801B9304.unk7C = prim;
            self->ext.et_801B9304.unk84 = prim;
            for (i = 0; prim != NULL; i++, prim = prim->next,
                prim->drawMode &= ~DRAW_UNK02, prim = prim->next) {
                UnkPolyFunc2(prim);
                prim->tpage = 0x11;
                prim->clut = PAL_UNK_19C;
#ifdef VERSION_PSP
                prim->u0 = prim->u2 = i * 18;
                prim->u1 = prim->u3 = prim->u0 + 0x12;
#else
                prim->u0 = prim->u2 = i * 16 + 8;
                prim->u1 = prim->u3 = prim->u0 + 0x10;
#endif
                prim->v0 = prim->v1 = 0x6C;
                prim->v2 = prim->v3 = prim->v0 + 0x10;
                prim->next->x1 = D_us_80181464[i];
                prim->next->x1 += D_us_80181454[i];
                prim->next->y0 = 0xA8;
                prim->next->r3 = i;
                LOH(prim->next->r2) = LOH(prim->next->b2) = 0x10;
                prim->next->b3 = 0;
                LOH(prim->next->u1) = 0x400;
                prim->priority = 0xB1;
                prim->drawMode = DRAW_HIDE;
            }
        } else {
            DestroyEntity(self);
            return;
        }
        self->ext.et_801B9304.unk80 = 1;
        break;

    case 1:
        if (!--self->ext.et_801B9304.unk80) {
            self->ext.et_801B9304.unk80 = 8;
            prim = self->ext.et_801B9304.unk84;
            prim->next->u2 = 1;
            prim = prim->next;
            prim = prim->next;
            if (prim == NULL) {
                self->step++;
            } else {
                self->ext.et_801B9304.unk84 = prim;
            }
        }
        prim = self->ext.et_801B9304.unk7C;
        while (prim != NULL) {
            if (prim->p3 == 8) {
                func_us_801B9184(prim);
            }
            prim = prim->next;
        }
        break;

    case 2:
        count = 0;
        prim = self->ext.et_801B9304.unk7C;
        while (prim != NULL) {
            if (prim->p3 == 8) {
                count += func_us_801B9184(prim);
            }
            prim = prim->next;
        }
        if (count == 7) {
            self->step++;
        }
        break;

    case 3:
        prim = self->ext.et_801B9304.unk7C;
        while (prim != NULL) {
            UnkPolyFunc0(prim);
            prim = prim->next;
            prim = prim->next;
        }
        prim = self->ext.et_801B9304.unk7C;
        prim->tpage = 0x11;
        prim->clut = PAL_UNK_19C;
#ifdef VERSION_PSP
        prim->u0 = prim->u2 = 0;
        prim->u1 = prim->u3 = prim->u0 + 0x7E;
#else
        prim->u0 = prim->u2 = 8;
        prim->u1 = prim->u3 = prim->u0 + 0x70;
#endif
        prim->v0 = prim->v1 = 0x6C;
        prim->v2 = prim->v3 = prim->v0 + 0x10;
        prim->x0 = prim->x2 = D_us_80181464[0] - 8;
        prim->x1 = prim->x3 = prim->x0 + 0x70;
        prim->y0 = prim->y1 = 0xA0;
        prim->y2 = prim->y3 = 0xB0;
        prim->priority = 0xB0;
        prim->drawMode = DRAW_DEFAULT;
        prim = prim->next;
        self->ext.et_801B9304.unk84 = prim;
        for (i = 0; i < 3; i++) {
            UnkPolyFunc2(prim);
            prim->tpage = 0x11;
            prim->clut = PAL_UNK_19C;
            prim->u0 = prim->u2 = 0;
            prim->u1 = prim->u3 = prim->u0 + 0x10;
            prim->v0 = prim->v1 = 0x6C;
            prim->v2 = prim->v3 = prim->v0 + 0x10;
            prim->x0 = prim->x1 = prim->x2 = prim->x3 = 0;
            prim->y0 = prim->y1 = prim->y2 = prim->y3 = 0;
            prim->next->x1 = D_us_80181464[0] - 8;
            prim->next->y0 = 0xA8;
            prim->next->r3 = i * 2;
            LOH(prim->next->r2) = 0x12;
            LOH(prim->next->b2) = 0x12;
            prim->next->b3 = 0x48;
            LOH(prim->next->u1) = 0;
            prim->priority = 0xB1;
            prim->drawMode =
                DRAW_UNK_40 | DRAW_TPAGE2 | DRAW_TPAGE | DRAW_TRANSP;
            prim = prim->next;
            prim->drawMode &= ~DRAW_UNK02;
            prim = prim->next;
        }
        self->step++;
        /* fallthrough */
    case 4:
        count = 0;
        prim = self->ext.et_801B9304.unk84;
        for (i = 0; i < 3; i++) {
            if (prim->next->r3) {
                prim->next->r3 -= 1;
            } else {
                prim->next->x1 += 2;
                prim->u0 = prim->u2 += 2;
                prim->u1 = prim->u3 += 2;
                UnkPrimHelper(prim);
            }
            if (prim->u3 > 0x80) {
                prim->drawMode = DRAW_HIDE;
                count++;
            }
            prim = prim->next;
            prim = prim->next;
        }
        if (count == 3) {
            self->step++;
        }
        break;

    case 5:
        prim = self->ext.et_801B9304.unk84;
        for (i = 0; i < 3; i++) {
            UnkPolyFunc0(prim);
            prim = prim->next;
            prim = prim->next;
        }
        prim = self->ext.et_801B9304.unk84;
        prim->tpage = 0x1A;
        prim->clut = PAL_UNK_19E;
        prim->u0 = prim->u2 = 0xA8;
        prim->u1 = prim->u3 = prim->u0 + 0x10;
        prim->v0 = prim->v1 = 0x60;
        prim->v2 = prim->v3 = prim->v0 + 0x10;
        prim->x0 = prim->x2 = 0x80;
        prim->x1 = prim->x3 = prim->x0;
        prim->y0 = prim->y1 = 0xA8;
        prim->y2 = prim->y3 = prim->y0;
        prim->x0 -= 6;
        prim->x1 += 4;
        prim->x2 -= 7;
        prim->x3 += 24;
        prim->y0 -= 9;
        prim->y1 -= 4;
        prim->y2 += 6;
        prim->y3 += 48;
        prim->r0 = prim->g0 = prim->b0 = 0x80;
        LOW(prim->r1) = LOW(prim->r0);
        LOW(prim->r2) = LOW(prim->r0);
        LOW(prim->r3) = LOW(prim->r0);
        prim->priority = 0xB1;
        prim->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS | DRAW_TRANSP;
        self->ext.et_801B9304.unk88 = 8;
        prim = self->ext.et_801B9304.unk7C;
        prim->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS | DRAW_TRANSP;
        prim->r0 = prim->g0 = prim->b0 = 0x80;
        LOW(prim->r1) = LOW(prim->r0);
        LOW(prim->r2) = LOW(prim->r0);
        LOW(prim->r3) = LOW(prim->r0);
        self->step++;
        break;

    case 7:
        prim = self->ext.et_801B9304.unk7C;
        prim->x0 = prim->x2 -= 6;
        prim->x1 = prim->x3 += 6;
        PrimDecreaseBrightness(prim, 7);
        count = PrimDecreaseBrightness(self->ext.et_801B9304.unk84, 7);
        if (!count) {
            DestroyEntity(self);
            return;
        }
        /* fallthrough */
    case 6:
        prim = self->ext.et_801B9304.unk7C;
        if (prim->y0 < (prim->y2 - 2)) {
            prim->y0 = ++prim->y1;
            prim->y2 = --prim->y3;
        } else {
            prim->y0 = prim->y1 = prim->y2 - 1;
            self->step = 7;
        }
        self->ext.et_801B9304.unk88 += 0x40;
        prim = self->ext.et_801B9304.unk84;
        angle = self->ext.et_801B9304.unk88 + ROT(135);
        prim->u0 = FLT_TO_I(rcos(angle) * 12) + 0xB0;
        prim->v0 = FLT_TO_I(rsin(angle) * 12) + 0x68;
        angle = self->ext.et_801B9304.unk88 + ROT(45);
        prim->u1 = FLT_TO_I(rcos(angle) * 12) + 0xB0;
        prim->v1 = FLT_TO_I(rsin(angle) * 12) + 0x68;
        angle = self->ext.et_801B9304.unk88 + ROT(225);
        prim->u2 = FLT_TO_I(rcos(angle) * 12) + 0xB0;
        prim->v2 = FLT_TO_I(rsin(angle) * 12) + 0x68;
        angle = self->ext.et_801B9304.unk88 + ROT(315);
        prim->u3 = FLT_TO_I(rcos(angle) * 12) + 0xB0;
        prim->v3 = FLT_TO_I(rsin(angle) * 12) + 0x68;
        break;
    }
}

void func_us_801B9BE4(Entity* self) {
    Entity* tempEntity;
    s16 volume;
    s16 distance;
    s32 xOffset, yOffset;
    s32 dx, dy;

    switch (self->step) {
    case 0:
        InitializeEntity(D_us_80180A1C);
        self->animCurFrame = 28;
        self->zPriority = 0x6C;
        if (!self->params) {
            CreateEntityFromEntity(E_ID(ID_33), self, self + 1);
            (self + 1)->params = 1;
            (self + 1)->posY.i.hi += 0x10;
            self->step = 3;
        } else {
            self->palette = PAL_FLAG(0x41);
            self->hitboxState = 3;
            self->hitboxWidth = 6;
            self->hitboxHeight = 18;
            self->hitboxOffY = -4;
            self->drawFlags = ENTITY_ROTATE;
            self->rotate = ROT(-11.25);
            self->animCurFrame = 29;
            self->step = 1;
            if (g_CastleFlags[NO1_ELEVATOR_ACTIVATED]) {
                g_api.func_800EA5E4(ANIMSET_OVL(3));
                g_api.PlaySfxVolPan(SFX_ELEVATOR_GEARS_LOOP, 0, 0);
                self->hitboxState = 0;
                self->step = 2;
            }
        }
        break;

    case 1:
        self->hitboxOffX = -FLT_TO_I(rsin(self->rotate) * 32);
        self->hitboxOffY = FLT_TO_I(rcos(self->rotate) * 32);
        xOffset = FLT_TO_I(rsin(self->rotate) * 18);
        yOffset = -FLT_TO_I(rcos(self->rotate) * 18);
        tempEntity = self - 1;
        tempEntity->posX.i.hi = self->posX.i.hi + xOffset;
        tempEntity->posY.i.hi = self->posY.i.hi + yOffset;
        switch (self->step_s) {
        case 0:
            if (self->hitFlags) {
                g_api.PlaySfx(SFX_DOOR_OPEN);
                self->ext.et_801B9BE4.unk80 = 16;
                self->step_s++;
            }
            break;

        case 1:
            self->rotate += 4;
            if (!--self->ext.et_801B9BE4.unk80) {
                self->step_s--;
            }
            if (self->rotate >= 0x20) {
                self->hitboxState = 0;
                tempEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
                if (tempEntity != NULL) {
                    CreateEntityFromEntity(E_ID(ID_5E), self, tempEntity);
                }
                g_api.func_80102CD8(1);
                g_api.func_800EA5E4(ANIMSET_OVL(3));
                g_api.PlaySfx(SFX_WEAPON_APPEAR);
                g_api.PlaySfxVolPan(SFX_ELEVATOR_GEARS_LOOP, 0x7F, 0);
                g_CastleFlags[NO1_ELEVATOR_ACTIVATED] = 1;
                self->step = 2;
            }
            break;
        }
        break;

    case 2:
        self->rotate = 0x20;
        xOffset = FLT_TO_I(rsin(self->rotate) * 18);
        yOffset = -FLT_TO_I(rcos(self->rotate) * 18);
        tempEntity = self - 1;
        tempEntity->posX.i.hi = self->posX.i.hi + xOffset;
        tempEntity->posY.i.hi = self->posY.i.hi + yOffset;
        dx = self->posX.i.hi - 0x80;
        distance = (abs(dx) - 0x20) >> 5;
        if (distance > 8) {
            distance = 8;
        } else if (distance < 0) {
            distance = 0;
        }
        if (dx < 0) {
            distance = -distance;
        }
        dx = GetDistanceToPlayerX() / 2;
        dy = GetDistanceToPlayerY();
        dx = dx * dx + dy * dy;
        dx = SquareRoot0(dx);
        volume = 0xA0 - dx;
        if (volume > 0x7F) {
            volume = 0x7F;
        }
        if (volume < 0) {
            volume = 0;
        }
        g_api.SetVolumeCommand22_23(volume, distance);
        FntPrint("vol:%x\n", volume);
        break;
    }
}

void func_us_801BA034(Entity* self) {
    Entity* entity;
    u8 collision;

    switch (self->step) {
    case 0:
        InitializeEntity(D_us_80180A04);
        if (g_CastleFlags[NO1_UNKNOWN_FLAG]) {
            self->posY.i.hi = 0xC3;
            self->step = 3;
        }
        break;

    case 1:
        self->posY.i.hi = 0xC0;
        collision = GetPlayerCollisionWith(self, 16, 7, 4);
        if (collision) {
            self->step++;
        }
        break;

    case 2:
        collision = GetPlayerCollisionWith(self, 16, 7, 4);
        if ((g_Timer % 16) == 0) {
            self->posY.i.hi++;
        }
        if (self->posY.i.hi > 0xC2) {
            g_api.func_80102CD8(1);
            g_CastleFlags[NO1_UNKNOWN_FLAG] = 1;
            self->step++;
        }
        if ((g_Timer % 10) == 0) {
            entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (entity != NULL) {
                CreateEntityFromEntity(E_INTENSE_EXPLOSION, self, entity);
                entity->params = 0x10;
                entity->posY.i.hi = 0xBC;
                entity->posX.i.hi -= 11;
                entity->drawFlags |= ENTITY_ROTATE;
                entity->rotate = ROT(-67.5);
            }
            entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (entity != NULL) {
                CreateEntityFromEntity(E_INTENSE_EXPLOSION, self, entity);
                entity->params = 0x10;
                entity->posY.i.hi = 0xBC;
                entity->posX.i.hi += 11;
                entity->drawFlags |= ENTITY_ROTATE;
                entity->rotate = ROT(67.5);
            }
        }
        break;

    case 3:
        self->posY.i.hi = 0xC3;
        break;
    }
}
