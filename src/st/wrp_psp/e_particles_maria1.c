// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../wrp/wrp.h"

extern u16 g_ESoulStealOrbAngles[];
extern s16 g_ESoulStealOrbSprt[];
extern u8 g_ESoulStealOrbAnim[];
void func_psp_0923AD68(Entity* self) {
    u16 angle;
    Primitive* prim;
    s32 primIndex;
    s16* spr;
    u16 direction;
    Entity* pl;

    if (D_psp_091CF3DC && D_psp_091CF3A0) {
        pl = D_psp_091CF3A0;
    } else {
        pl = &PLAYER;
    }
    switch (self->step) {
    case 0:
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 1);
        if (primIndex != -1) {
            InitializeEntity(g_EInitObtainable);
            prim = &g_PrimBuf[primIndex];
            prim->drawMode = DRAW_HIDE;
            self->flags |= FLAG_HAS_PRIMS;
            self->primIndex = primIndex;
            self->animSet = 0;
            angle = GetAngleBetweenEntities(self, pl);
            direction = 0;
            if (self->posY.i.hi > 0x70) {
                direction = 1;
            }
            if (self->posX.i.hi < PLAYER.posX.i.hi) {
                direction ^= 1;
            }
            if (direction) {
                angle -= g_ESoulStealOrbAngles[Random() & 7];
            } else {
                angle += g_ESoulStealOrbAngles[Random() & 7];
            }
            self->ext.soulStealOrb.angle = angle;
            self->ext.soulStealOrb.unk80 = 0x200;
            self->ext.soulStealOrb.unk7E = 0;
            self->hitboxState = 0;
        } else {
            DestroyEntity(self);
        }
        break;
    case 1:
        self->ext.soulStealOrb.unk82 += 1;
        if (self->ext.soulStealOrb.unk82 == 0x10) {
            self->hitboxState = 1;
        }
        if (abs(pl->posX.i.hi - self->posX.i.hi) < 8 &&
            abs(pl->posY.i.hi - self->posY.i.hi) < 8) {
            D_psp_091CF3A4 += 4;
            DestroyEntity(self);
            return;
        }
        if (self->rotX < 0x100) {
            self->rotX = self->rotY += 0x10;
        }
        if (self->ext.soulStealOrb.unk7E < 0x200) {
            self->ext.soulStealOrb.unk7E += 4;
        }
        if (self->ext.soulStealOrb.unk80 < 0x800) {
            self->ext.soulStealOrb.unk80 += 0x10;
        }
        angle = GetAngleBetweenEntities(self, pl);
        self->ext.soulStealOrb.angle = angle = GetNormalizedAngle(
            self->ext.soulStealOrb.unk7E, self->ext.soulStealOrb.angle, angle);
        UnkEntityFunc0(angle, self->ext.soulStealOrb.unk80);
        MoveEntity(self);
        prim = &g_PrimBuf[self->primIndex];
        AnimateEntity(g_ESoulStealOrbAnim, self);
        prim->tpage = 0x18;
        prim->clut = 0x194;
        angle = self->animCurFrame;
        angle = (angle - 1) * 8;
        spr = &g_ESoulStealOrbSprt[angle];
        prim->x0 = prim->x2 = self->posX.i.hi + *spr++;
        prim->y0 = prim->y1 = self->posY.i.hi + *spr++;
        prim->x1 = prim->x3 = prim->x0 + *spr++;
        prim->y2 = prim->y3 = prim->y0 + *spr++;
        prim->u0 = prim->u2 = *spr++;
        prim->v0 = prim->v1 = *spr++;
        prim->u1 = prim->u3 = *spr++;
        prim->v2 = prim->v3 = *spr;
        prim->priority = self->zPriority;
        prim->drawMode = DRAW_DEFAULT;
        break;
    }
}
