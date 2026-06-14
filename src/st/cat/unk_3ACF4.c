// SPDX-License-Identifier: AGPL-3.0-or-later
#include "cat.h"
#include <scratchpad.h>

static s16 D_us_801816FC[] = {
    0, 1, 2, 3, 4, 5, 5, 5, 5, 5, 5, 5, 5, 4, 3, 2, 1,
};

static s16 D_us_80181720[] = {
    0x00, 0x20, 0x40, 0x60, 0x80, 0xA0, 0xAA, 0xAA, 0xAA,
    0xAA, 0xAA, 0xA0, 0x80, 0x60, 0x40, 0x20, 0x00,
};

extern s32 echo_flag;

typedef struct {
    s16 unk0;
    s16 : 16;
    s16 unk4;
    s16 unk6;
    s16 unk8;
    s16 unkA;
    s16 unkC;
    s16 : 16;
    s32 unk10;
    s32 unk14;
    s32 unk18;
} unkStruct;

void func_us_801BACF4(Entity* self) {
    s32 temp_t1;
    s32 var_a2_2;
    s32 x0, y0;
    Collider col;
    Primitive* prim;
    unkStruct* ptr;
    s32 i;
    bool var_s7;
    s32 var_s5;
    s16 angle;
    Entity* tempEntity;
    Primitive* prim2;

    tempEntity = &PLAYER;
    self->posX.i.hi = tempEntity->posX.i.hi;
    self->posY.i.hi = tempEntity->posY.i.hi;
    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitInteractable);
        self->primIndex = g_api.AllocPrimitives(PRIM_G4, 0x31);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags = FLAG_HAS_PRIMS | FLAG_POS_PLAYER_LOCKED;
        prim = &g_PrimBuf[self->primIndex];
        self->ext.et_801BACF4.unk84 = prim;
        for (i = 0; i < 0x11; i++) {
            prim->type = PRIM_TILE;
            prim->drawMode = DRAW_HIDE;
            prim->y2 = D_us_801816FC[i];
            prim->x2 = i * 3 + 1;
            prim->y3 = D_us_80181720[i];
            prim->x3 = (i * 0x400) & 0xFFF;
            prim->x1 = (i * 0x80) & 0xFFF;
            prim = prim->next;
        }
        for (i = 0; i < 0x20; i++) {
            prim->drawMode = DRAW_UNK_200 | DRAW_TPAGE2 | DRAW_TPAGE |
                             DRAW_COLORS | DRAW_TRANSP;
            prim->priority = 0xCF;
            if (self->params) {
                prim->priority = 0x5F;
                prim->drawMode = DRAW_UNK_200 | DRAW_COLORS;
            }
            prim->r0 = prim->g0 = prim->b0 = 0x40;
            LOW(prim->r1) = LOW(prim->r0);
            LOW(prim->r2) = LOW(prim->r0);
            LOW(prim->r3) = LOW(prim->r0);
            prim = prim->next;
        }
        self->ext.et_801BACF4.unk80 = 0x300;
        if (self->params) {
            self->ext.et_801BACF4.unk80 = 0x500;
        }
        self->ext.et_801BACF4.unk8A = 1;
        self->ext.et_801BACF4.unk8E = 0x100;
        break;

    case 1:
        self->ext.et_801BACF4.unk7E += 40;
        echo_flag = true;
        if (self->ext.et_801BACF4.unk7E > self->ext.et_801BACF4.unk80) {
            self->ext.et_801BACF4.unk7E = self->ext.et_801BACF4.unk80;
            self->hitboxState = 0;
            self->step++;
        }
        break;

    case 2:
        self->ext.et_801BACF4.unk7E -= 20;
        if (self->ext.et_801BACF4.unk7E < 0) {
            echo_flag = false;
            self->ext.et_801BACF4.unk7E = 0;
            DestroyEntity(self);
            return;
        }
        break;
    }

    LOW(self->ext.et_801BACF4.unk88) += 0x2000;
    tempEntity = &PLAYER;
    prim = self->ext.et_801BACF4.unk84;
    x0 = tempEntity->posX.i.hi;
    if (self->facingLeft) {
        x0 -= 0x10;
    } else {
        x0 += 0x10;
    }
    x0 = x0 << 0x10;
    var_s5 = LOW(self->ext.et_801BACF4.unk88);
    y0 = tempEntity->posY.i.hi;
    ptr = (unkStruct*)SP(sizeof(Primitive));
    var_s7 = false;
    for (i = 0; i < 0x11; i++, ptr++) {
        if (self->facingLeft) {
            x0 -= var_s5;
        } else {
            x0 += var_s5;
        }
        if (!var_s7) {
            g_api.CheckCollision(x0 >> 0x10, y0, &col, 0);
            if (col.effects & EFFECT_SOLID) {
                var_s5 = -var_s5;
                self->ext.et_801BACF4.unk8E += 0x10;
                var_s7 = true;
            }
        }
        ptr->unk0 = x0 >> 0x10;
        prim->x3 += 0x100;
        ptr->unk4 = prim->x3;
        prim->x1 -= 0x40;
        ptr->unk6 = prim->x1;
        ptr->unk8 = prim->x2;
        ptr->unk8 = (ptr->unk8 * self->ext.et_801BACF4.unk8E) >> 8;
        ptr->unkA = prim->y2;
        ptr->unkC = prim->y3;
        ptr->unk10 = rcos(ptr->unk6) >> 6;
        ptr->unk14 = rcos(ptr->unk6 + 0x100) >> 6;
        ptr->unk18 = rsin(ptr->unk4) >> 4;
        prim = prim->next;
    }
    tempEntity = &PLAYER;
    x0 = tempEntity->posX.i.hi;
    if (self->facingLeft) {
        var_s5 = x0 - 0x10;
    } else {
        var_s5 = x0 + 0x10;
    }
    y0 = tempEntity->posY.i.hi;
    angle = tempEntity->rotate;
    temp_t1 = (((rsin(angle) >> 4) * 10) >> 8) - 6;
    temp_t1 = y0 + temp_t1;
    angle = self->ext.et_801BACF4.unk7E;
    prim2 = (Primitive*)SP(0);
    ptr = (unkStruct*)SP(sizeof(Primitive));
    prim2->x3 = prim2->x1 = var_s5;
    prim2->y1 = temp_t1 + ((ptr->unk18 * ptr->unkA) >> 9);
    prim2->y3 = prim2->y1 - ptr->unk8;
    prim2->r1 = ((ptr->unk10 + 0x41) * ptr->unkC * angle) / 0x10000;
    prim2->g1 = ((ptr->unk14 + 0x41) * ptr->unkC * angle) / 0x10000;
    prim2->b1 = ((-ptr->unk10 + 0x41) * ptr->unkC * angle) / 0x10000;
    var_a2_2 = prim2->y1 + ptr->unk8;
    ptr++;

    for (i = 0; i < 0x10; i++, ptr++) {
        LOW(prim->x0) = LOW(prim2->x0) = LOW(prim2->x1);
        LOW(prim->x2) = LOW(prim2->x2) = LOW(prim2->x3);
        prim->x3 = prim->x1 = prim2->x3 = prim2->x1 = ptr->unk0;
        prim->y1 = prim2->y1 = temp_t1 + ((ptr->unk18 * ptr->unkA) >> 9);
        prim->y3 = prim2->y3 = prim2->y1 - ptr->unk8;
        LOW(prim->r0) = LOW(prim2->r0) = LOW(prim2->r1);
        prim->r1 = prim2->r1 =
            ((ptr->unk10 + 0x41) * ptr->unkC * angle) / 0x10000;
        prim->g1 = prim2->g1 =
            ((ptr->unk14 + 0x41) * ptr->unkC * angle) / 0x10000;
        prim->b1 = prim2->b1 =
            ((-ptr->unk10 + 0x41) * ptr->unkC * angle) / 0x10000;
        if (self->params) {
            LOW(prim->r2) = LOW(prim2->r0);
            LOW(prim->r3) = LOW(prim2->r1);
        }
        prim->type = PRIM_G4;
        prim = prim->next;

        LOW(prim->x0) = LOW(prim2->x0);
        LOW(prim->x1) = LOW(prim2->x1);
        LOW(prim->x2) = LOW(prim2->x2);
        LOW(prim->x3) = LOW(prim2->x3);
        LOW(prim->r0) = LOW(prim2->r0);
        LOW(prim->r1) = LOW(prim2->r1);
        if (self->params) {
            LOW(prim->r2) = LOW(prim2->r0);
            LOW(prim->r3) = LOW(prim2->r1);
        }
        prim->y2 = var_a2_2;
        prim->y3 = var_a2_2 = prim2->y1 + ptr->unk8;
        prim->type = PRIM_G4;
        prim = prim->next;
    }
}
