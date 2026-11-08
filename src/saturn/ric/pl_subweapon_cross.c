// SPDX-License-Identifier: AGPL-3.0-or-later
#include "richter.h"

INCLUDE_ASM_NO_ALIGN("asm/saturn/richter/f_nonmat", f60B8664, func_060B8664);

// RicEntityRevivalColumn
INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60B8B1C, func_060B8B1C);

// RicEntitySubwpnCross
INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60B8DF8, func_060B8DF8);

void func_80169C10(Entity* self) {
    RicPrimitive* prim;

    if (self->step == 0) {
        self->primIndex = AllocPrimitives(1, 1);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags = FLAG_POS_CAMERA_LOCKED | FLAG_HAS_PRIMS;
        self->velocityY = FIX(0.5);
        self->posX.i.hi += (MTH_GetRand() & 0xF) - 8;
        self->posY.i.hi += (MTH_GetRand() & 0xF) - 4;
        prim = (RicPrimitive*)&g_PrimBuf[self->primIndex];
        prim->unk6 = LookupTblNoToVram(g_RichterSpriteResources[1].flags + 12);
        prim->frame = 0;
        prim->timer = 0;
        prim->priority = self->zPriority + 4;
        prim->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_TRANSP;
        func_8015FDB0(prim, self->posX.i.hi, self->posY.i.hi);
        self->step++;
    } else {
        prim = (RicPrimitive*)&g_PrimBuf[self->primIndex];
        self->posY.val += self->velocityY;
        if (func_8015FDB0(prim, self->posX.i.hi, self->posY.i.hi)) {
            DestroyEntity(self);
        }
    }
}

// Saturn replacement of RicEntitySubwpnCrossTrail
void func_060B9300(Entity* self) {
    switch (self->step) {
    case 0:
        self->unk0 = CreateSpriteObject(
            g_RichterSpritePackage7Resource.allocationIndex,
            g_RichterSpritePackage7Resource.flags,
            g_RichterSpritePackage7Images, 1);
        if (self->unk0 == NULL) {
            DestroyEntity(self);
            return;
        }
        self->ext.spriteEntity.frames = g_RichterSpritePackage7Frames;
        self->unk0->zPriority =
            PLAYER.zPriority - (s16)((self->params & 7) + 2);
        self->flags = FLAG_POS_CAMERA_LOCKED;
        self->animSet = 0x8011;
        self->unk56 = 0x66;
        self->palette = 0x81B0;
        self->unk1C = 0x10;
        self->facingLeft = PLAYER.facingLeft;
        self->zPriority = PLAYER.zPriority;
        self->drawFlags = ENTITY_ROTATE;
        self->rotate = (self->params & 0xFF00) >> 4;
        self->step++;
        break;
    default:
        self->step++;
        break;
    }
    self->animCurFrame = (self->step / 4) + 9;
    if (self->animCurFrame > 12) {
        DestroyEntity(self);
    } else {
        UpdateEntitySprite(self);
    }
}

// RicEntitySubwpnCrashCrossParticles
INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60B940C, func_060B940C);
