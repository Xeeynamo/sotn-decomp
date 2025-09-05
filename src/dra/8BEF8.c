// SPDX-License-Identifier: AGPL-3.0-or-later
#include "dra.h"
#include "dra_bss.h"

s16 D_800B0884[] = {0, 1, 2, 3, 4, 5, 5, 5, 5, 5, 5, 5, 5, 4, 3, 2, 1};
s16 D_800B08A8[] = {0x00, 0x20, 0x40, 0x60, 0x80, 0xA0, 0xAA, 0xAA, 0xAA,
                    0xAA, 0xAA, 0xA0, 0x80, 0x60, 0x40, 0x20, 0x00};

// echo of bat effect
void EntityBatEcho(Entity* self) {
#ifdef VERSION_PC
    u8 sp[SP_LEN];
#endif
    Primitive* prim;
    Primitive* temp;
    Unkstruct_8012BEF8* unkstruct;
    s32 i;
    s32 var_s5;
    s16 temp_unk7E;
    s32 var_s6;
    s32 temp_s7;
    s32 posX, posY;

    self->posX.i.hi = PLAYER.posX.i.hi;
    self->posY.i.hi = PLAYER.posY.i.hi;
    if ((self->ext.batEcho.unk8A % 384) == 0) {
        PlaySfx(SFX_BAT_ECHO_B);
    }
    self->ext.batEcho.unk8A++;
    if (self->ext.batEcho.unk88) {
        self->step = 3;
    }

    switch (self->step) {
    case 0:
        self->primIndex = g_api.AllocPrimitives(PRIM_G4, 0x31);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags = FLAG_HAS_PRIMS | FLAG_POS_PLAYER_LOCKED;
        prim = &g_PrimBuf[self->primIndex];
        self->ext.batEcho.unk84 = prim;
        for (i = 0; i < 0x11; i++) {
            prim->type = PRIM_TILE;
            prim->drawMode = DRAW_HIDE;
            prim->y2 = D_800B0884[i];
            prim->x2 = (i * 3) + 1;
            prim->y3 = D_800B08A8[i];
            prim->x3 = (i << 0xA) & 0xFFF;
            prim->x1 = (i << 7) & 0xFFF;
            prim = prim->next;
        }
        for (i = 0; i < 0x20; i++) {
            prim->drawMode = DRAW_UNK_200 | DRAW_TPAGE2 | DRAW_TPAGE |
                             DRAW_COLORS | DRAW_TRANSP;
            prim->priority = PLAYER.zPriority - 2;
            prim = prim->next;
        }
        self->ext.batEcho.unk80 = 0xA0;
        if (IsRelicActive(RELIC_FORCE_OF_ECHO)) {
            self->ext.batEcho.unk80 = 0x100;
            self->hitboxOffX = 0x40;
            self->hitboxOffY = -4;
            self->hitboxWidth = 0x28;
            self->hitboxHeight = 0xC;
            func_8011A328(self, 0xA);
        }
        self->step++;
        break;

    case 1:
        self->ext.batEcho.unk7E += 0xA;
        if (self->ext.batEcho.unk7E > self->ext.batEcho.unk80) {
            self->ext.batEcho.unk7E = self->ext.batEcho.unk80;
            self->hitboxState = 0;
            self->step++;
        }
        break;

    case 2:
        self->ext.batEcho.unk7E -= 0xA;
        if (self->ext.batEcho.unk7E < 0) {
            self->ext.batEcho.unk7E = 0;
            DestroyEntity(self);
            return;
        }
        break;

    case 3:
        prim = self->ext.batEcho.unk84;
        while (prim != NULL) {
            prim->drawMode = DRAW_HIDE;
            prim = prim->next;
        }
        if (!--self->ext.batEcho.unk88) {
            DestroyEntity(self);
        }
        return;
    }

    prim = self->ext.batEcho.unk84;
    posX = PLAYER.posX.i.hi;
    posY = PLAYER.posY.i.hi;
    unkstruct = (Unkstruct_8012BEF8*)SP(sizeof(Primitive));
    for (i = 0; i < 0x11; i++, unkstruct++) {
        prim->x3 += 0x100;
        unkstruct->unk4 = prim->x3;
        prim->x1 -= 0x40;
        unkstruct->unk6 = prim->x1;
        unkstruct->unk8 = prim->x2;
        unkstruct->unkA = prim->y2;
        unkstruct->unkC = prim->y3;
        unkstruct->unk10 = rcos(unkstruct->unk6) >> 6;
        unkstruct->unk14 = rcos(unkstruct->unk6 + 0x100) >> 6;
        unkstruct->unk18 = rsin(unkstruct->unk4) >> 4;
        prim = prim->next;
    }

    temp = (Primitive*)SP(0);
    posX = PLAYER.posX.i.hi;
    posY = PLAYER.posY.i.hi;
    if (self->facingLeft) {
        var_s5 = posX - 16;
    } else {
        var_s5 = posX + 16;
    }

    temp_unk7E = PLAYER.rotate;
    temp_s7 = (((rsin(temp_unk7E) >> 4) * 0xA) >> 8) - 6;
    temp_s7 = posY + temp_s7;
    temp_unk7E = self->ext.batEcho.unk7E;
    unkstruct = (Unkstruct_8012BEF8*)SP(sizeof(Primitive));

    temp->x3 = temp->x1 = var_s5;
    temp->y1 = temp_s7 + ((unkstruct->unk18 * unkstruct->unkA) >> 9);
    temp->y3 = temp->y1 - unkstruct->unk8;

    temp->r1 =
        (unkstruct->unk10 + 0x41) * unkstruct->unkC * temp_unk7E / FIX(1);
    temp->g1 =
        (unkstruct->unk14 + 0x41) * unkstruct->unkC * temp_unk7E / FIX(1);
    temp->b1 =
        (-unkstruct->unk10 + 0x41) * unkstruct->unkC * temp_unk7E / FIX(1);

    var_s6 = temp->y1 + unkstruct->unk8;
    unkstruct++;
    for (i = 0; i < 0x10; i++, unkstruct++) {
        if (self->facingLeft) {
            var_s5 -= 8;
        } else {
            var_s5 += 8;
        }
        LOW(prim->x0) = LOW(temp->x0) = LOW(temp->x1);
        LOW(prim->x2) = LOW(temp->x2) = LOW(temp->x3);
        prim->x3 = prim->x1 = temp->x3 = temp->x1 = var_s5;
        prim->y1 = temp->y1 =
            temp_s7 + ((unkstruct->unk18 * unkstruct->unkA) >> 9);
        prim->y3 = temp->y3 = temp->y1 - unkstruct->unk8;

        LOW(prim->r0) = LOW(temp->r0) = LOW(temp->r1);

        prim->r1 = temp->r1 =
            (unkstruct->unk10 + 0x41) * unkstruct->unkC * temp_unk7E / FIX(1);
        prim->g1 = temp->g1 =
            (unkstruct->unk14 + 0x41) * unkstruct->unkC * temp_unk7E / FIX(1);
        prim->b1 = temp->b1 =
            (-unkstruct->unk10 + 0x41) * unkstruct->unkC * temp_unk7E / FIX(1);

        prim->type = PRIM_G4;
        prim = prim->next;
        LOW(prim->x0) = LOW(temp->x0);
        LOW(prim->x1) = LOW(temp->x1);
        LOW(prim->x2) = LOW(temp->x2);
        LOW(prim->x3) = LOW(temp->x3);
        LOW(prim->r0) = LOW(temp->r0);
        LOW(prim->r1) = LOW(temp->r1);
        prim->y2 = var_s6;
        var_s6 = temp->y1 + unkstruct->unk8;
        prim->y3 = var_s6;
        prim->type = PRIM_G4;
        prim = prim->next;
    }
}
