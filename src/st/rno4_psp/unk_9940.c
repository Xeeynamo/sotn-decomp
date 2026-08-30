// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../rno4/rno4.h"

void TryThrow(void) {
    s32 collisionResult;
    u16 collisionFlags;

    collisionResult = UnkCollisionFunc2(g_JackOBonesSensors2);
    collisionFlags = UnkCollisionFunc(g_JackOBonesSensors3, 3);
    if (collisionResult == 0x80 || (collisionFlags & 2)) {
        SetStep(5);
        return;
    }
    if (!g_CurrentEntity->ext.jackoBones.throwTimer) {
        SetStep(4);
        return;
    }
    g_CurrentEntity->ext.jackoBones.throwTimer--;
}

INCLUDE_ASM("st/rno4_psp/nonmatchings/rno4_psp/unk_9940", EntityJackOBones);

void EntityJackOBonesDeathParts(Entity* self) {
    if (self->step) {
        if (--self->ext.jackoBones.deathPartLife) {
            self->rotate += g_JackOBonesDeathPartsRotSpeeds[self->params];
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
    InitializeEntity(g_EInitJackOBones2);
    self->animCurFrame = (self->params & 0xFF) + 15;
    if (self->params & 0x100) {
        self->palette++;
    }
    self->drawFlags = ENTITY_ROTATE;
    if (self->facingLeft) {
        self->velocityX = -self->velocityX;
    }
}

INCLUDE_ASM("st/rno4_psp/nonmatchings/rno4_psp/unk_9940", EntityJackOBonesJack);

extern u16 g_SoulStealOrbAngleOffsets[];
extern s16 g_SoulStealOrbSpriteData[];
extern AnimateEntityFrame g_SoulStealOrbAnim[];

void func_psp_0923AD68(Entity* self) {
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
                angle -= g_SoulStealOrbAngleOffsets[Random() & 7];
            } else {
                angle += g_SoulStealOrbAngleOffsets[Random() & 7];
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
        AnimateEntity(g_SoulStealOrbAnim, self);
        prim->tpage = 0x18;
        prim->clut = PAL_UNK_194;
        angle = self->animCurFrame;
        angle = (angle - 1) << 3;

        spr = &g_SoulStealOrbSpriteData[angle];
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

INCLUDE_ASM("st/rno4_psp/nonmatchings/rno4_psp/unk_9940", func_psp_0923B2F0);
