// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../rno4/rno4.h"

INCLUDE_ASM("st/rno4_psp/nonmatchings/rno4_psp/unk_161A0", TryShoot);

INCLUDE_ASM("st/rno4_psp/nonmatchings/rno4_psp/unk_161A0", DrawLaserRing);

INCLUDE_ASM("st/rno4_psp/nonmatchings/rno4_psp/unk_161A0", EntityNovaSkeleton);

void EntityBladeSoldierDeathParts(Entity* self) {
    extern EInit g_EInitNovaSkeleton;
    extern u16 g_BladeSoldierDeathPartsRotSpeeds[];
    if (self->step) {
        if (--self->ext.bladeSoldierDeathParts.lifetime) {
            self->rotate += g_BladeSoldierDeathPartsRotSpeeds[self->params];
            FallEntity();
            MoveEntity();
            return;
        }
        self->entityId = E_EXPLOSION;
        self->pfnUpdate = EntityExplosion;
        self->params = 0;
        self->step = 0;
        return;
    }
    InitializeEntity(g_EInitNovaSkeleton);
    self->hitboxState = 0;
    self->flags |=
        FLAG_DESTROY_IF_OUT_OF_CAMERA | FLAG_DESTROY_IF_BARELY_OUT_OF_CAMERA |
        FLAG_UNK_00200000 | FLAG_UNK_2000;
    self->animCurFrame = self->params + 29;
    self->drawFlags = ENTITY_ROTATE;
    if (self->facingLeft) {
        self->velocityX = -self->velocityX;
    }
}

extern u16 D_us_80180C20;
extern Entity g_Entities_224;
extern u8 g_NovaLaserPrimData[];
extern Entity g_Entities[];

void EntityNovaLaser(Entity* self) {
    s32 centerX;
    s32 primIndex;
    s32 centerY;
    Entity* other;
    s32 primX;
    s32 var_s2;
    u8* var_s1;
    Primitive* prim;

    switch (self->step) {
    case 0:
        InitializeEntity(&D_us_80180C20);
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 3);
        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }

        self->flags |= FLAG_HAS_PRIMS;
        self->primIndex = primIndex;
        prim = &g_PrimBuf[primIndex];
        self->ext.nova.prim = prim;
        var_s1 = g_NovaLaserPrimData;
        for (var_s2 = 0; var_s2 < 3; prim = prim->next, var_s2++) {
            prim->tpage = 0x12;
            prim->clut = 0x216;
            prim->u0 = prim->u2 = *var_s1++ + 0x80;
            prim->u1 = prim->u3 = *var_s1++ + 0x80;
            prim->v0 = prim->v1 = 0x40;
            prim->v2 = prim->v3 = 0x5F;
            prim->r0 = prim->g0 = prim->b0 = *var_s1++;
            LOW(prim->r2) = LOW(prim->r0);
            prim->r1 = prim->g1 = prim->b1 = *var_s1++;
            LOW(prim->r3) = LOW(prim->r1);
            prim->priority = self->zPriority + 2;
            prim->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS |
                             DRAW_UNK02 | DRAW_TRANSP;
        }
        self->ext.nova.laserTimer = 0x60;
        self->ext.nova.laserLength = 0;

    case 1:
        self->ext.nova.laserFadeTimer = 0x10;
        if (self->ext.nova.laserLength < 0x80) {
            self->ext.nova.laserLength += 0x10;
        } else {
            self->ext.nova.laserLength = 0x80;
            self->hitboxState = 1;
            self->step++;
        }

    case 2:
        if (!(self->ext.nova.laserTimer & 3)) {
            other = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (other != NULL) {
                CreateEntityFromEntity(E_NOVA_PULSE, self, other);
                other->zPriority = self->zPriority - 1;
                other->ext.nova.laserLength = self->ext.nova.laserLength;
                other->facingLeft = self->facingLeft;
            }
        }
        if (!(self->ext.nova.laserTimer & 0xF)) {
            PlaySfxPositional(SFX_BAT_ECHO_A);
        }
        if (self->ext.nova.laserTimer < 0x10) {
            PlaySfxPositional(SFX_BAT_ECHO_D);
            self->step++;
        }

    case 3:
        if (Random() & 1) {
            if (self->ext.nova.laserLength < 0x88) {
                self->ext.nova.laserLength++;
            } else if (self->ext.nova.laserLength > 0x78) {
                self->ext.nova.laserLength--;
            }
        }
        self->hitboxWidth = self->ext.nova.laserLength / 2 + 0x10;
        self->hitboxOffX = -self->ext.nova.laserLength / 2 - 0x10;
        self->hitboxHeight = 8;
        other = self - 1;
        if (other->entityId != 0x56) {
            self->ext.nova.laserTimer = 1;
        }
        if (!--self->ext.nova.laserTimer) {
            self->hitboxState = 0;
            self->step++;
        }
        break;

    case 4:
        self->ext.nova.laserFadeTimer--;
        if (!self->ext.nova.laserFadeTimer) {
            DestroyEntity(self);
            return;
        }
        break;
    }

    centerX = self->posX.i.hi;
    centerY = self->posY.i.hi;
    prim = self->ext.nova.prim;
    for (var_s2 = 0; var_s2 < 3; prim = prim->next, var_s2++) {
        prim->y0 = prim->y1 = centerY - self->ext.nova.laserFadeTimer;
        prim->y2 = prim->y3 = centerY + self->ext.nova.laserFadeTimer;
        if (g_Timer & 1) {
            prim->clut = 0x216;
        } else {
            prim->clut = 0x217;
        }
    }

    prim = self->ext.nova.prim;
    primX = centerX;
    if (self->facingLeft) {
        primX -= 0x10;
    } else {
        primX += 0x10;
    }

    prim->x1 = prim->x3 = primX;
    if (self->facingLeft) {
        primX += 0x20;
    } else {
        primX -= 0x20;
    }
    prim->x0 = prim->x2 = primX;

    prim = prim->next;
    prim->x1 = prim->x3 = primX;
    if (self->facingLeft) {
        primX += self->ext.nova.laserLength;
    } else {
        primX -= self->ext.nova.laserLength;
    }
    prim->x0 = prim->x2 = primX;

    prim = prim->next;
    prim->x1 = prim->x3 = primX;
    if (self->facingLeft) {
        primX += 0x20;
    } else {
        primX -= 0x20;
    }
    prim->x0 = prim->x2 = primX;
    prim = prim->next;
}

INCLUDE_ASM("st/rno4_psp/nonmatchings/rno4_psp/unk_161A0", EntityNovaLaserPulse);
