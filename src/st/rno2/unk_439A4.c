// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rno2.h"

INCLUDE_ASM("st/rno2/nonmatchings/unk_439A4", func_us_801C39A4);

INCLUDE_ASM("st/rno2/nonmatchings/unk_439A4", func_us_801C4960);

INCLUDE_ASM("st/rno2/nonmatchings/unk_439A4", func_us_801C4C0C);

void func_us_801C4EA8(Entity* self) {
    extern u16 g_EInitParticle;
    extern u8 g_Unk2EAnim;
#ifdef VERSION_PSP
    s16 angle;
#else
    s32 angle;
#endif

    switch (self->step) {
    case 0:
        InitializeEntity(&g_EInitParticle);
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

INCLUDE_ASM("st/rno2/nonmatchings/unk_439A4", EntityKarasuman);

extern u16 D_us_80180928;

void EntityKarasumanFeatherAttack(Entity* self) {
    Entity* entity;
    s16 angle;

    switch (self->step) {
    case 0:
        InitializeEntity(&D_us_80180928);
        self->animCurFrame = 0x3B;
        self->drawFlags |= ENTITY_ROTATE;

        if (Random() & 1) {
            self->facingLeft = 1;
        }

        angle = (Random() * 4) - 0x200;
        self->rotate = angle;
        angle = self->rotate;
        if (!self->facingLeft) {
            angle = ROT(180) - angle;
        }

        self->velocityX = rcos(angle) * 0x60;
        self->velocityY = rsin(angle) * -0x60;
        self->posX.i.hi += (rcos(angle) << 5) >> 0xC;
#ifdef VERSION_PSP
        self->posY.i.hi += (-rsin(angle) << 5) >> 0xC;
#else
        self->posY.i.hi += -(rsin(angle) << 5) >> 0xC;
#endif
        /* fall through */

    case 1:
        MoveEntity();
        if (self->flags & FLAG_DEAD) {
            entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (entity != NULL) {
                CreateEntityFromEntity(E_EXPLOSION, self, entity);
                entity->params = 1;
            }
            DestroyEntity(self);
        }
    }
}

INCLUDE_ASM("st/rno2/nonmatchings/unk_439A4", EntityKarasumanOrbAttack);

INCLUDE_ASM("st/rno2/nonmatchings/unk_439A4", EntityKarasumanRavenAttack);

void EntityKarasumanFeather(Entity* self) {
    extern u16 D_us_8018094C;
    s16 angle;
    s32 scale;

    switch (self->step) {
    case 0:
        InitializeEntity(&D_us_8018094C);
        self->animCurFrame = 63;
        self->drawFlags = ENTITY_ROTATE;
        self->facingLeft = Random() & 1;
        scale = (Random() & 0x1F) + 0x10;
        angle = (Random() * 6) + FLT(9.0 / 16.0);

        self->velocityX = scale * rcos(angle);
        self->velocityY = scale * rsin(angle);
        self->posX.val += 16 * self->velocityX;
        self->posY.val += 16 * self->velocityY;

        self->rotate = angle;
        self->ext.karasuman.timer = 64;
        /* fallthrough */

    case 1:
        MoveEntity();
        self->velocityX -= self->velocityX / 16;
        self->velocityY -= self->velocityY / 16;

        self->rotate += 64;
        if (!--self->ext.karasuman.timer) {
            self->velocityX = 0;
            self->step++;
        }
        break;

    case 2:
        MoveEntity();
        self->rotate += 32;
        if (self->velocityY < FIX(1.5)) {
            self->velocityY += FIX(1.0 / 32.0);
        }
        break;
    }
}

void EntityKarasumanRavenAbsorb(Entity* self) {
    s16 angle;
    extern u16 D_us_80180940;

    extern AnimationFrame g_KarasumanRavenAbsorbAnim[];

    switch (self->step) {
    case 0:
        InitializeEntity(&D_us_80180940);
        self->blendMode = BLEND_TRANSP;
        self->drawFlags = ENTITY_ROTATE;
        self->hitboxState = 0;

        self->flags |= FLAG_DESTROY_IF_OUT_OF_CAMERA | FLAG_UNK_2000;
        if (self->params) {
            self->animCurFrame = 0;
            self->step = 4;
            break;
        }

        angle = ROT(-22.5) - ((Random() & 0x3F) * 16);
        self->rotate = -angle;
        if (!self->facingLeft) {
            angle = FLT(0.5) - angle;
        }
        self->velocityX = 56 * rcos(angle);
        self->velocityY = 56 * rsin(angle);
        /* fallthrough */

    case 1:
        MoveEntity();
        AnimateEntity(g_KarasumanRavenAbsorbAnim, self);
        break;

    case 4:
        switch (self->step_s) {
        case 0:
            self->ext.karasuman.timer = 96;
            self->step_s++;
            /* fallthrough */

        case 1:
            if (self->ext.karasuman.timer & 1) {
                self->animCurFrame = 0x3D;
            } else {
                self->animCurFrame = 0;
            }

            if (!--self->ext.karasuman.timer) {
                DestroyEntity(self);
            }
            break;
        }
        break;
    }
}
