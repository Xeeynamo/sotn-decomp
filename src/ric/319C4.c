#include "ric.h"

// RIC Entity # 49. Comes from blueprint 57. Factory call in func_8016E324.
// func_8016E324 is RIC Entity #48. Comes from blueprint 56. Blueprint 56 is
// subweapon 25. And subweapon 25 is the crash of subweapon 7.
// And subweapon 7 is the rebound stone. This is an entity spawned from the
// rebound stone crash.
void func_8016D9C4(Entity* self) {
    Primitive* prim;
    PrimLineG2* primLine;
    s32 i;
    s32 angleChange;
    s32 brightness;

    switch (self->step) { /* switch 1; irregular */
    case 0:               /* switch 1 */
        self->primIndex = g_api.AllocPrimitives(PRIM_LINE_G2, 20);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags = FLAG_UNK_04000000 | FLAG_HAS_PRIMS;
        primLine = (PrimLineG2*)&g_PrimBuf[self->primIndex];
        for (i = 0; i < 4; i++) {
            primLine->preciseX.val = PLAYER.posX.val;
            primLine->preciseY.val = PLAYER.posY.val - FIX(40);
            primLine->priority = 194;
            primLine->drawMode = DRAW_HIDE;
            primLine->x0 = primLine->x1 = PLAYER.posX.i.hi;
            primLine->y0 = primLine->y1 = PLAYER.posY.i.hi - 0x1C;
            primLine->r0 = primLine->g0 = primLine->b0 = 0x80;
            primLine->r1 = primLine->g1 = primLine->b1 = 0x70;
            primLine->angle = D_80155EE0[i];
            primLine->delay = 1;
            primLine = (PrimLineG2*)primLine->next;
        }
        for (brightness = 0x80; i < 20; i++) {
            if ((i & 3) == 0) {
                brightness -= 0x10;
                switch (i / 4) {
                case 1:
                    self->ext.et_8016D9C4.lines[0] = primLine;
                    break;
                case 2:
                    self->ext.et_8016D9C4.lines[1] = primLine;
                    break;
                case 3:
                    self->ext.et_8016D9C4.lines[2] = primLine;
                    break;
                case 4:
                    self->ext.et_8016D9C4.lines[3] = primLine;
                    break;
                }
            }
            primLine->priority = 0xC2;
            primLine->drawMode = 8;
            primLine->x0 = primLine->x1 = PLAYER.posX.i.hi;
            primLine->y0 = primLine->y1 = PLAYER.posY.i.hi - 0x1C;
            primLine->r0 = primLine->g0 = primLine->b0 = brightness;
            primLine->r1 = primLine->g1 = primLine->b1 = brightness - 0x10;
            primLine = (PrimLineG2*)primLine->next;
        }
        self->ext.et_8016D9C4.unk90 = 4;
        self->ext.et_8016D9C4.unk8E = 0;
        self->ext.et_8016D9C4.unk8C = 0;
        g_api.PlaySfx(0x623);
        self->step++;
        break;
    case 1: /* switch 1 */
        self->ext.et_8016D9C4.unk8E = 1;
        switch (self->ext.et_8016D9C4.unk8C) {
        case 0:
            primLine = (PrimLineG2*)&g_PrimBuf[self->primIndex];
            break;
        case 1:
            primLine = self->ext.et_8016D9C4.lines[0];
            break;
        case 2:
            primLine = self->ext.et_8016D9C4.lines[1];
            break;
        case 3:
            primLine = self->ext.et_8016D9C4.lines[2];
            break;
        case 4:
            primLine = self->ext.et_8016D9C4.lines[3];
            break;
        }
        for (i = 0; i < 4; i++) {
            primLine->drawMode &= ~DRAW_HIDE;
            primLine = (PrimLineG2*)primLine->next;
        }
        if (++self->ext.et_8016D9C4.unk8C >= 5) {
            self->step++;
        }
        break;
    case 2: /* switch 1 */
        if (self->ext.et_8016D9C4.unk90 == 0) {
            self->step++;
            break;
        }
        break;
    case 3: /* switch 1 */
        if (++self->ext.et_8016D9C4.unk90 >= 5) {
            DestroyEntity(self);
            return;
        }
        break;
    }
    if (self->ext.et_8016D9C4.unk8E == 0) {
        return;
    }
    primLine = (PrimLineG2*)&g_PrimBuf[self->primIndex];
    for (i = 0; i < 4; i++) {
        if (primLine->delay != 0) {
            primLine->x1 = primLine->x0;
            primLine->y1 = primLine->y0;
            primLine->x0 = primLine->preciseX.i.hi;
            primLine->y0 = primLine->preciseY.i.hi;
            angleChange =
                primLine->angle - (ratan2(primLine->preciseY.val,
                                          FIX(128) - primLine->preciseX.val) &
                                   0xFFF);
            if (ABS(angleChange) > 0x800) {
                if (angleChange < 0) {
                    angleChange += 0x1000;
                } else {
                    angleChange -= 0x1000;
                }
            }
            if (angleChange >= 0) {
                if (angleChange >= 0x81) {
                    angleChange = 0x80;
                }
            } else if (angleChange < -0x80) {
                angleChange = -0x80;
            }
            primLine->angle = (primLine->angle - angleChange) & 0xFFF;
            primLine->velocityX = (rcos(primLine->angle) << 8);
            primLine->velocityY = -(rsin(primLine->angle) << 8);
            primLine->preciseX.val += primLine->velocityX.val;
            primLine->preciseY.val += primLine->velocityY.val;
            self->posX.i.hi = primLine->preciseX.i.hi;
            self->posY.i.hi = primLine->preciseY.i.hi;
            CreateEntFactoryFromEntity(self, FACTORY(0, 69), 0);
            if (primLine->preciseY.val < 0) {
                primLine->delay = 0;
                primLine->drawMode |= 8;
                self->ext.et_8016D9C4.unk90--;
            }
        }
        primLine = (PrimLineG2*)primLine->next;
    }
    primLine = self->ext.et_8016D9C4.lines[0];
    prim = &g_PrimBuf[self->primIndex];
    for (i = 0; i < 16; i++) {
        primLine->x1 = primLine->x0;
        primLine->y1 = primLine->y0;
        primLine->x0 = prim->x1;
        primLine->y0 = prim->y1;
        primLine = (PrimLineG2*)primLine->next;
        prim = prim->next;
    }
}

const s32 rodata_pad_1ab4c = 0;
INCLUDE_ASM("ric/nonmatchings/319C4", func_8016DF74);
