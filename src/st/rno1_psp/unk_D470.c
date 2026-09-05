// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../rno1/rno1.h"

typedef enum {
    NOVA_INIT,
    NOVA_1,
    NOVA_IDLE,
    NOVA_WALK_FWD,
    NOVA_WALK_BACK,
    NOVA_5,
    NOVA_CHARGE,
    NOVA_SHOOT,
    NOVA_DEAD
} NovaSkeletonSteps;

extern s16 D_us_80181D20[];

void TryShoot(void) {
    // return value not used, but function has side effects
    s32 unused = UnkCollisionFunc2(D_us_80181D20);

    // if cooldown has expired...
    if (!g_CurrentEntity->ext.nova.cooldown) {
        if (GetDistanceToPlayerX() >= 0x80) {
            return;
        }
        if (g_CurrentEntity->facingLeft ^ (GetSideToPlayer() & 1)) {
            SetStep(NOVA_CHARGE);
        }
    } else {
        g_CurrentEntity->ext.nova.cooldown--;
    }
}

INCLUDE_ASM("st/rno1_psp/nonmatchings/rno1_psp/unk_D470", DrawLaserRing);

INCLUDE_ASM("st/rno1_psp/nonmatchings/rno1_psp/unk_D470", EntityNovaSkeleton);

extern EInit g_EInitNovaSkeleton;
extern u16 D_us_80181DE0[];

void EntityBladeSoldierDeathParts(Entity* self) {
    if (self->step) {
        if (--self->ext.nova.deathPartLife) {
            self->rotate += D_us_80181DE0[self->params];
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
    self->animCurFrame = self->params + 0x1D;
    self->drawFlags = ENTITY_ROTATE;

    if (self->facingLeft) {
        self->velocityX = -self->velocityX;
    }
}

INCLUDE_ASM("st/rno1_psp/nonmatchings/rno1_psp/unk_D470", EntityNovaLaser);

INCLUDE_ASM("st/rno1_psp/nonmatchings/rno1_psp/unk_D470", EntityNovaLaserPulse);

INCLUDE_ASM("st/rno1_psp/nonmatchings/rno1_psp/unk_D470", func_us_801C7F24_from_rno0);
