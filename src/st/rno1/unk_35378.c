// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rno1.h"

typedef enum {
    JACKO_INIT,
    JACKO_1,
    JACKO_WALK_FWD,
    JACKO_WALK_BACK,
    JACKO_THROW,
    JACKO_JUMP,
    JACKO_DEAD
} JackOBonesSteps;

extern s16 D_us_80181CFC[];
extern s16 D_us_80181D04[];

static void TryThrow(void) {
    s32 collisionResult;
    u16 collisionFlags;

    collisionResult = UnkCollisionFunc2(D_us_80181CFC);
    collisionFlags = UnkCollisionFunc(D_us_80181D04, 3);
    if (collisionResult == 0x80 || (collisionFlags & 2)) {
        SetStep(JACKO_JUMP);
        return;
    }
    if (!g_CurrentEntity->ext.jackoBones.throwTimer) {
        SetStep(JACKO_THROW);
        return;
    }
    g_CurrentEntity->ext.jackoBones.throwTimer--;
}

INCLUDE_ASM("st/rno1/nonmatchings/unk_35378", EntityJackOBones);

extern EInit D_us_8018070C;
extern u16 D_us_80181C74[];

void EntityJackOBonesDeathParts(Entity* self) {
    if (self->step) {
        if (--self->ext.jackoBones.deathPartLife) {
            self->rotate += D_us_80181C74[self->params];
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

    InitializeEntity(D_us_8018070C);
    self->animCurFrame = (self->params & 0xFF) + 15;
    if (self->params & 0x100) {
        self->palette += 1;
    }
    self->drawFlags = ENTITY_ROTATE;
    if (self->facingLeft) {
        self->velocityX = -self->velocityX;
    }
}

INCLUDE_ASM("st/rno1/nonmatchings/unk_35378", EntityJackOBonesJack);

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

INCLUDE_ASM("st/rno1/nonmatchings/unk_35378", DrawLaserRing);

INCLUDE_RODATA("st/rno1/nonmatchings/unk_35378", D_us_801A5DDC);

INCLUDE_ASM("st/rno1/nonmatchings/unk_35378", EntityNovaSkeleton);

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

INCLUDE_ASM("st/rno1/nonmatchings/unk_35378", EntityNovaLaser);

INCLUDE_ASM("st/rno1/nonmatchings/unk_35378", EntityNovaLaserPulse);
