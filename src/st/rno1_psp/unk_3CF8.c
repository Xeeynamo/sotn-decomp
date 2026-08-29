// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../rno1/rno1.h"

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

INCLUDE_ASM("st/rno1_psp/nonmatchings/rno1_psp/unk_3CF8", EntityJackOBones);

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

INCLUDE_ASM("st/rno1_psp/nonmatchings/rno1_psp/unk_3CF8", EntityJackOBonesJack);

INCLUDE_ASM("st/rno1_psp/nonmatchings/rno1_psp/unk_3CF8", func_psp_0923AD68);

INCLUDE_ASM("st/rno1_psp/nonmatchings/rno1_psp/unk_3CF8", func_psp_0923B2F0);
