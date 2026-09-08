// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../rno2/rno2.h"

INCLUDE_ASM("st/rno2_psp/nonmatchings/rno2_psp/unk_C0F0", func_us_801C39A4);

INCLUDE_ASM("st/rno2_psp/nonmatchings/rno2_psp/unk_C0F0", func_us_801C4960);

INCLUDE_ASM("st/rno2_psp/nonmatchings/rno2_psp/unk_C0F0", func_us_801C4C0C);

void func_us_801C4EA8(Entity* self) {
    extern u8 g_Unk2EAnim;
#ifdef VERSION_PSP
    s16 angle;
#else
    s32 angle;
#endif

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitParticle);
#ifndef VERSION_PSP
        angle = self->rotate;
#endif
        self->animSet = 0xE;
        self->unk5A = 0x5C;
        self->palette = 0x2EE;
        self->drawFlags = ENTITY_ROTATE | ENTITY_SCALEX;
        self->scaleX = 0x60;
        self->scaleY = 0xC0;
        self->blendMode = BLEND_QUARTER | BLEND_TRANSP;
#ifdef VERSION_PSP
        angle = self->rotate;
        self->velocityX = rsin(angle) << 4;
        self->velocityY = (-rcos(angle)) << 4;
#else
        self->velocityX = rsin(angle) << 4;
        self->velocityY = -(rcos(angle) << 4);
#endif
    case 1:
        MoveEntity();
        if (AnimateEntity(&g_Unk2EAnim, self) == 0) {
            DestroyEntity(self);
        }
        break;
    }
}

INCLUDE_ASM("st/rno2_psp/nonmatchings/rno2_psp/unk_C0F0", EntityFlyingZombie2);

INCLUDE_ASM("st/rno2_psp/nonmatchings/rno2_psp/unk_C0F0", EntityFlyingZombie1);

void func_psp_0923AD68(Entity* self) {
    extern u16 D_pspeu_09258E80[];
    extern u8 D_pspeu_09258EF0[];
    extern s16 D_pspeu_09258E90[];
    u16 angle;
    Primitive* prim;
    s32 primIndex;
    s16* spr;
    u16 direction;
    Entity* pl;

    if (g_Player.unk5C && g_Player.unk20) {
        pl = (Entity*)g_Player.unk20;
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
            self->animSet = ANIMSET_DRA(0);
            angle = GetAngleBetweenEntities(self, pl);
            direction = 0;
            if (self->posY.i.hi > 112) {
                direction = 1;
            }
            if (self->posX.i.hi < PLAYER.posX.i.hi) {
                direction ^= 1;
            }
            if (direction) {
                angle -= D_pspeu_09258E80[Random() & 7];
            } else {
                angle += D_pspeu_09258E80[Random() & 7];
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
        self->ext.soulStealOrb.unk82++;
        if (self->ext.soulStealOrb.unk82 == 16) {
            self->hitboxState = 1;
        }
        if (abs(pl->posX.i.hi - self->posX.i.hi) < 8 &&
            abs(pl->posY.i.hi - self->posY.i.hi) < 8) {
            g_Player.unk24 += 4;
            DestroyEntity(self);
            return;
        }
        if (self->scaleX < 0x100) {
            self->scaleX = self->scaleY += 0x10;
        }
        if (self->ext.soulStealOrb.unk7E < 0x200) {
            self->ext.soulStealOrb.unk7E += 4;
        }
        if (self->ext.soulStealOrb.unk80 < 0x800) {
            self->ext.soulStealOrb.unk80 += 0x10;
        }
        angle = GetAngleBetweenEntities(self, pl);
        self->ext.soulStealOrb.angle = angle = LimitAngleChange(
            self->ext.soulStealOrb.unk7E, self->ext.soulStealOrb.angle, angle);
        UnkEntityFunc0(angle, self->ext.soulStealOrb.unk80);
        MoveEntity(self);
        prim = &g_PrimBuf[self->primIndex];
        AnimateEntity(D_pspeu_09258EF0, self);
        prim->tpage = 0x18;
        prim->clut = PAL_UNK_194;
        angle = self->animCurFrame;
        angle = (angle - 1) << 3;

        spr = &D_pspeu_09258E90[angle];
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

extern AnimateEntityFrame D_pspeu_09258EF0[];
extern s16 D_pspeu_09258E90[];

void func_psp_0923B2F0(Entity* self) {
    Primitive* prim;
    s32 primIndex;
    u16 angle;
    s16* spr;
    u16 direction;
    Entity* pl;

    pl = &PLAYER;
    switch (self->step) {
    default:
        return;
    case 0:
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 1);
        if (primIndex != -1) {
            InitializeEntity(g_EInitObtainable);
            prim = &g_PrimBuf[primIndex];
            prim->drawMode = DRAW_HIDE;
            self->flags |= FLAG_HAS_PRIMS;
            self->primIndex = primIndex;
            self->animSet = ANIMSET_DRA(0);
            self->ext.soulStealOrb.angle = rand() % ROT(360);
            self->ext.soulStealOrb.unk80 = 0x200;
            self->ext.soulStealOrb.unk7E = 0;
            self->hitboxState = 0;
            return;
        }
        break;

    case 1:
        self->ext.soulStealOrb.unk82++;
        if (self->ext.soulStealOrb.unk82 == 16) {
            self->hitboxState = 1;
        }
        if (abs(pl->posX.i.hi - self->posX.i.hi) < 8 &&
            abs(pl->posY.i.hi - self->posY.i.hi) < 8) {
            break;
        }
        if (self->scaleX < 0x100) {
            self->scaleX = self->scaleY += 0x10;
        }
        if (self->ext.soulStealOrb.unk7E < 0x200) {
            self->ext.soulStealOrb.unk7E += 4;
        }
        if (self->ext.soulStealOrb.unk80 < 0x800) {
            self->ext.soulStealOrb.unk80 += 0x10;
        }
        angle = GetAngleBetweenEntities(self, pl);
        self->ext.soulStealOrb.angle = angle = LimitAngleChange(
            self->ext.soulStealOrb.unk7E, self->ext.soulStealOrb.angle, angle);
        UnkEntityFunc0(angle, self->ext.soulStealOrb.unk80);
        MoveEntity(self);
        prim = &g_PrimBuf[self->primIndex];
        AnimateEntity(D_pspeu_09258EF0, self);
        prim->tpage = 0x18;
        prim->clut = PAL_UNK_194;
        angle = self->animCurFrame;
        angle = (angle - 1) << 3;

        spr = &D_pspeu_09258E90[angle];
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
        return;
    }
    g_Player.unk2C = 0;
    DestroyEntity(self);
}
