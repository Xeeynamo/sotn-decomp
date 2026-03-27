// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rcat.h"

extern EInit g_EInitSpawner;
extern char D_us_801AF5EC[];

void func_us_801B1F1C(Entity* self) {
    FntPrint(D_us_801AF5EC, self->step); // sotn-lint-ignore
    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitSpawner);
        if (self->params) {
            g_Tilemap.flags &= (u16)~LAYER_SEMI_TRANS;
            DestroyEntity(self);
            break;
        }

        g_Tilemap.flags |= LAYER_SEMI_TRANS;
        g_api.func_800EA5E4(0x8004);
        g_api.func_800EA5E4(0x8006);
        g_api.func_800EA5E4(0x8007);
        g_api.func_800EA5E4(0x8008);
        self->step = 4;
        break;
    case 1:
        g_api.func_800EA5E4(0xA003);
        g_api.func_800EA5E4(0xA005);
        self->step++;
        break;
    case 2:
        if (g_CastleFlags[RCAT_SPIKE_ROOM_LIT]) {
            g_api.func_800EA538(3);
            self->step++;
        }
        break;
    case 3:
        g_Tilemap.flags |= LAYER_SEMI_TRANS;
        g_api.func_800EA5E4(0x8004);
        g_api.func_800EA5E4(0x8006);
        g_api.func_800EA5E4(0x8007);
        g_api.func_800EA5E4(0x8008);
        g_api.func_800EA5E4(0x800B);
        self->step++;
        break;
    case 4:
        g_Tilemap.flags |= LAYER_SEMI_TRANS;
        break;
    }
}

void func_us_801B87E8_from_cat(Entity* self) {
    Primitive* prim;
    u32 primIndex;
    s16 base_x;
    s32 i;

    for (base_x = -g_Tilemap.scrollX.i.hi; base_x < (-0x3E); base_x += 0x3E)
        ;

    g_CastleFlags[RCAT_SPIKE_ROOM_LIT] = 1;
    if (!self->step) {
        self->step++;
        self->primIndex = g_api.AllocPrimitives(PRIM_GT4, 0x10);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags = FLAG_KEEP_ALIVE_OFFCAMERA | FLAG_HAS_PRIMS;

        for (prim = &g_PrimBuf[self->primIndex], i = 0; prim != NULL; i++,
            prim = prim->next) {
            prim->x0 = prim->x2 = base_x + ((i & 0x7) * 0x3E);
            prim->x1 = prim->x3 = prim->x0 + 0x3E;
            prim->y1 = prim->y0 = 0xDC - ((i >> 3) * 0x5F);
            prim->y3 = prim->y2 = prim->y0 - 0x5F;
            prim->u0 = 1;
            prim->v0 = 0x81;
            prim->u1 = 0x3F;
            prim->v1 = 0x81;
            prim->u2 = 1;
            prim->v2 = 0xDE;
            prim->u3 = 0x3F;
            prim->v3 = 0xDE;
            prim->tpage = 0xF;
            prim->clut = 0x8F;
            prim->priority = 0x20;
            prim->drawMode = DRAW_UNK02;
            if (!g_CastleFlags[RCAT_SPIKE_ROOM_LIT]) {
                prim->drawMode |= DRAW_HIDE | DRAW_COLORS;
            }
        }

        self->ext.et_801B87E8.unk80 = 1;
    } else {
        for (prim = &g_PrimBuf[self->primIndex], i = 0; prim != NULL; i++,
            prim = prim->next) {
            prim->drawMode &= ~DRAW_HIDE;
            if (self->ext.et_801B87E8.unk81) {
                if (prim->r0 >= 0x80) {
                    self->ext.et_801B87E8.unk81 = 0;
                } else {
                    prim->r0 += 2;
                    prim->g0 = (prim->b0 = prim->r0);
                    LOWU(prim->r1) = LOWU(prim->r0);
                    LOWU(prim->r2) = LOWU(prim->r0);
                    LOWU(prim->r3) = LOWU(prim->r0);
                }
            }
            prim->x0 = prim->x2 = base_x + (2 * ((i & 7) * 31));
            prim->x1 = prim->x3 = prim->x0 + 0x3E;
        }

        self->ext.et_801B87E8.unk80 = g_CastleFlags[RCAT_SPIKE_ROOM_LIT];
    }
    FntPrint("base_x:%04x\n", base_x);
}

#include <scratchpad.h>

extern EInit g_EInitInteractable;
extern u16 D_us_80181380[];
extern u16 D_us_801813A4[];

typedef struct {
    s16 posX;
    s16 pad02;
    s16 unk4;
    s16 unk6;
    s16 unk8;
    s16 unkA;
    s16 unkC;
    s16 padE;
    s32 unk10;
    s32 unk14;
    s32 unk18;
} EchoBounceStruct; // size = 0x1C

#ifndef NON_MATCHING
INCLUDE_ASM("st/rcat/nonmatchings/unk_31F1C", func_us_801BACF4_from_cat);
#else
void func_us_801BACF4_from_cat(Entity* self) {
    Collider col;
    Primitive* prim;
    Primitive* temp;
    EchoBounceStruct* unkstruct;
    s32 i;
    Entity* player;
    s16 temp_unk7E;
    s32 var_s6;
    s32 temp_s7;
    s32 posX;
    int posY;
    s32 velocity;
    s32 bounced;
    int new_var2;
    s16* new_var;

    self->posX.i.hi = g_Entities[0].posX.i.hi;
    self->posY.i.hi = g_Entities[0].posY.i.hi;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitInteractable);
        self->primIndex = g_api.AllocPrimitives(PRIM_G4, 0x31);
        if (self->primIndex == -1) {
            goto destroy;
        }
        self->flags = FLAG_HAS_PRIMS | FLAG_POS_PLAYER_LOCKED;
        prim = &g_PrimBuf[self->primIndex];
        self->ext.et_801BACF4.unk84 = prim;
        for (i = 0; i < 0x11; i++) {
            prim->type = PRIM_TILE;
            prim->drawMode = DRAW_HIDE;
            prim->y2 = D_us_80181380[i];
            prim->x2 = (i * 3) + 1;
            prim->y3 = D_us_801813A4[i];
            prim->x3 = i;
            prim->x3 = (prim->x3 << 10) & 0xFFF;
            prim->x1 = (i << 7) & 0xFFF;
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
            prim->b0 = 0x40;
            prim->g0 = 0x40;
            prim->r0 = 0x40;
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
        self->ext.et_801BACF4.unk7E += 0x28;
        if ((s16)self->ext.et_801BACF4.unk7E > self->ext.et_801BACF4.unk80) {
            self->ext.et_801BACF4.unk7E = self->ext.et_801BACF4.unk80;
            self->hitboxState = 0;
            self->step++;
        }
        break;

    case 2:
        var_s6 = 0x14;
        self->ext.et_801BACF4.unk7E -= var_s6;
        if ((s16)self->ext.et_801BACF4.unk7E < 0) {
            self->ext.et_801BACF4.unk7E = 0;
        destroy:
            DestroyEntity(self);
            return;
        }
        break;
    }

    player = g_Entities;
    prim = self->ext.et_801BACF4.unk84;
    *(s32*)&self->ext.et_801BACF4.unk88 += 0x2000;

    posX = g_Entities[0].posX.i.hi;
    if (self->facingLeft) {
        posX -= 0x10;
    } else {
        posX += 0x10;
    }
    posX <<= 16;

    unkstruct = (EchoBounceStruct*)SP(sizeof(Primitive));
    bounced = 0;
    velocity = *(s32*)&self->ext.et_801BACF4.unk88;
    posY = player[0].posY.i.hi;
    for (i = 0; i < 0x11; i++, unkstruct++) {
        if (self->facingLeft) {
            posX -= velocity;
        } else {
            posX += velocity;
        }
        if (!bounced) {
            g_api.CheckCollision(posX >> 16, posY, &col, 0);
            if (col.effects & EFFECT_SOLID) {
                velocity = -velocity;
                bounced = 1;
                self->ext.et_801BACF4.unk8E += 0x10;
            }
        }
        unkstruct->posX = posX >> 16;
        prim->x3 += 0x100;
        unkstruct->unk4 = prim->x3;
        prim->x1 -= 0x40;
        unkstruct->unk6 = prim->x1;
        new_var = &prim->x2;
        unkstruct->unk8 = *new_var;
        unkstruct->unk8 =
            ((s16)unkstruct->unk8 * self->ext.et_801BACF4.unk8E) >> 8;
        unkstruct->unkA = prim->y2;
        unkstruct->unkC = prim->y3;
        unkstruct->unk10 = rcos(unkstruct->unk6) >> 6;
        unkstruct->unk14 = rcos(unkstruct->unk6 + 0x100) >> 6;
        unkstruct->unk18 = rsin(unkstruct->unk4) >> 4;
        prim = prim->next;
    }

    player = g_Entities;
    posX = player[0].posX.i.hi;
    if (self->facingLeft) {
        velocity = posX - 16;
    } else {
        velocity = posX + 16;
    }
    var_s6 = player[0].rotate;
    posY = player[0].posY.i.hi;
    temp_s7 = rsin(var_s6);
    {
        s32 unkA = *(s16*)SP(0x3E);
        s32 unk18 = *(s32*)SP(0x4C);
        s32 unk10 = *(s32*)SP(0x44);
        int unkC = *(s16*)SP(0x40);
        u16 unk8 = *(u16*)SP(0x3C);
        s32 calcB;
        s32 negUnk10;

        temp_unk7E = self->ext.et_801BACF4.unk7E;
        temp_s7 = (((temp_s7 >> 4) * 5) >> 7) - 6;
        temp_s7 = posY + temp_s7;

        temp = (Primitive*)SP(0);
        temp->x1 = temp->x3 = velocity;
        velocity = temp_s7 + ((unkA * unk18) >> 9);
        temp->y1 = velocity;
        temp->y3 = temp->y1 - unk8;

        calcB = (unk10 + 0x41) * unkC * temp_unk7E;
        if (calcB < 0) {
            calcB += 0xFFFF;
        }
        var_s6 = (*(s32*)SP(0x48)) + 0x41;
        temp->r1 = calcB >> 16;
        calcB = (unkC * var_s6) * temp_unk7E;
        negUnk10 = (unk10 = -unk10);
        if (calcB < 0) {
            calcB += 0xFFFF;
            negUnk10 = -unk10;
        }
        temp->g1 = calcB >> 16;
        new_var2 = 0xFFFF;

        calcB = (negUnk10 + 0x41) * unkC * temp_unk7E;
        if (calcB < 0) {
            calcB += new_var2;
        }
        unkstruct = (EchoBounceStruct*)SP(sizeof(Primitive));
        temp->b1 = calcB >> 16;

        var_s6 = temp_unk7E + (s16)unk8;
        unkstruct++;
    }
    for (i = 0; i < 0x10; i++, unkstruct++) {
        LOW(prim->x0) = LOW(temp->x0) = LOW(temp->x1);
        do {
            LOW(prim->x2) = LOW(temp->x2) = LOW(temp->x3);
            prim->x3 = prim->x1 = temp->x3 = temp->x1 = unkstruct->posX;
            prim->y1 = temp->y1 =
                temp_s7 + ((unkstruct->unkA * unkstruct->unk18) >> 9);
            prim->y3 = temp->y3 = temp->y1 - unkstruct->unk8;
            LOW(prim->r0) = LOW(temp->r0) = LOW(temp->r1);
        } while (0);

        prim->r1 = temp->r1 =
            (unkstruct->unk10 + 0x41) * unkstruct->unkC * temp_unk7E / 0x10000;
        prim->g1 = temp->g1 =
            (unkstruct->unk14 + 0x41) * unkstruct->unkC * temp_unk7E / 0x10000;
        prim->b1 = temp->b1 =
            (-unkstruct->unk10 + 0x41) * unkstruct->unkC * temp_unk7E / 0x10000;

        if (self->params) {
            LOW(prim->r2) = LOW(temp->r0);
            LOW(prim->r3) = LOW(temp->r1);
        }
        prim->type = PRIM_G4;
        prim = prim->next;
        LOW(prim->x0) = LOW(temp->x0);
        LOW(prim->x1) = LOW(temp->x1);
        LOW(prim->x2) = LOW(temp->x2);
        LOW(prim->x3) = LOW(temp->x3);
        LOW(prim->r0) = LOW(temp->r0);
        LOW(prim->r1) = LOW(temp->r1);
        if (self->params) {
            LOW(prim->r2) = LOW(temp->r0);
            LOW(prim->r3) = LOW(temp->r1);
        }
        prim->y2 = var_s6;
        var_s6 = temp->y1 + unkstruct->unk8;
        prim->y3 = var_s6;
        prim->type = PRIM_G4;
        prim = prim->next;
    }
}
#endif
