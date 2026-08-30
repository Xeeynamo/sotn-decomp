// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../rno2/rno2.h"

INCLUDE_ASM("st/rno2_psp/nonmatchings/rno2_psp/unk_1BF80", EntityBreakable);

extern u16 g_EInitInteractable;
extern u16 g_EInitParticle;
extern Entity g_Entities[256];

void EntityBreakableDebris(Entity* self) {
    Collider collider;
    Entity* explosion;
    Primitive* prim;
    s32 primIndex;
    s16 posX, posY;

    switch (self->step) {
    case 0:
        if (self->params & 0x100) {
            InitializeEntity(&g_EInitInteractable);
            self->animSet = -0x7FF7;
            self->unk5A = 0x5B;
            self->palette = 0x226;
            self->animCurFrame = 0x15;
            self->zPriority = 0x6A;
            self->step = 0x100;
            return;
        }

        InitializeEntity(&g_EInitParticle);
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 2);
        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }

        self->flags |= FLAG_HAS_PRIMS;
        self->primIndex = primIndex;
        prim = &g_PrimBuf[primIndex];
        self->ext.breakableDebris.prim = prim;
        UnkPolyFunc2(prim);
        prim->tpage = 0x16;
        prim->clut = 0x22A;
        prim->u0 = prim->u2 = 0x98;
        prim->u1 = prim->u3 = 0xA7;
        posY = 0x84;
        posY += self->params * 16;
        prim->v0 = prim->v1 = posY + 15;
        prim->v2 = prim->v3 = posY;
        prim->next->x1 = self->posX.i.hi;
        prim->next->y0 = self->posY.i.hi;
        LOH(prim->next->r2) = 16;
        LOH(prim->next->b2) = 16;
        prim->next->b3 = 0x80;
        prim->priority = self->zPriority;
        prim->drawMode = DRAW_UNK02;
        self->velocityX = ((Random() & 7) << 12) + FIX(0.5);
        if (!self->facingLeft) {
            self->velocityX = -self->velocityX;
        }
        self->velocityY = ((Random() & 7) << 12) - FIX(0.5);

    case 1:
        MoveEntity();
        self->velocityY += FIX(0.125);
        prim = self->ext.breakableDebris.prim;
        prim->next->x1 = self->posX.i.hi;
        prim->next->y0 = self->posY.i.hi;
        if (self->facingLeft) {
            LOH(prim->next->tpage) += 16;
        } else {
            LOH(prim->next->tpage) -= 16;
        }
        UnkPrimHelper(prim);

        posX = self->posX.i.hi;
        posY = self->posY.i.hi + 8;
        g_api.CheckCollision(posX, posY, &collider, 0);
        if (collider.effects & EFFECT_SOLID) {
            g_api.PlaySfx(SFX_SMALL_FLAME_IGNITE);
            explosion = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (explosion != NULL) {
                CreateEntityFromCurrentEntity(E_EXPLOSION, explosion);
                explosion->params = 0;
            }
            DestroyEntity(self);
        }
        break;
    }
}

INCLUDE_ASM("st/rno2_psp/nonmatchings/rno2_psp/unk_1BF80", func_pspeu_09253F98);

INCLUDE_ASM("st/rno2_psp/nonmatchings/rno2_psp/unk_1BF80", EntitySealedDoor);
