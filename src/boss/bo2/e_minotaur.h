// SPDX-License-Identifier: AGPL-3.0-or-later

extern EInit g_EInitMinotaurAttackHitbox;
extern EInit g_EInitMinotaurFireball;
extern EInit g_EInitMinotaurSpitLiquid;
extern EInit g_EInitParticle;
extern s8 minotaur_attack_hitboxes[][4];
extern u8 minotaur_attack_hitbox_indices[];
extern s32 fireball_config[][2];
extern u8 anim_spit[];
extern u8 anim_death_puff[];
#ifdef VERSION_PSP
extern s32 E_ID(MINOTAUR);
#endif

void EntityMinotaurAttackHitbox(Entity* self) {
    Entity* parent;
    s8* hitbox;
    s32 animFrame;
    s32 delta;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitMinotaurAttackHitbox);
        self->animCurFrame = 0;
        /* fall through */
    case 1:
        parent = self - 1;
        if (parent->entityId != E_ID(MINOTAUR)) {
            DestroyEntity(self);
            return;
        }

        animFrame = parent->animCurFrame;
        self->facingLeft = parent->facingLeft;
        self->posX.val = parent->posX.val;
        self->posY.val = parent->posY.val;
        self->hitboxState = 1;
        hitbox = *minotaur_attack_hitboxes;
        hitbox += minotaur_attack_hitbox_indices[animFrame] * 4;
        self->hitboxOffX = *hitbox++;
        self->hitboxOffY = *hitbox++;
        self->hitboxWidth = *hitbox++;
        self->hitboxHeight = *hitbox++;

        if (!self->ext.minotaur.axeThrown) {
            return;
        }
        SetStep(2);
        return;

    case 2:
        switch (self->step_s) {
        case 0:
            parent = self - 1;
            self->facingLeft = parent->facingLeft;
            self->hitboxState = 0;
            self->animCurFrame = 0x42;
            self->drawFlags = ENTITY_ROTATE;
            self->velocityY = FIX(-8.0);
            if (self->facingLeft) {
                self->velocityX = FIX(0.25);
            } else {
                self->velocityX = FIX(-0.25);
            }
            self->step_s++;
            /* fall through */
        case 1:
            MoveEntity();
            self->rotate += 0x100;
            self->velocityY += FIX(0.0625);
            if (!(g_Timer & 0xF)) {
                PlaySfxPositional(SFX_ARROW_SHOT_A);
            }
            if (self->posY.i.hi < -0x40) {
                self->step_s++;
            }
            break;

        case 2:
            if (!self->ext.minotaur.axeThrown) {
                SetStep(3);
            }
            break;
        }
        break;

    case 3:
        switch (self->step_s) {
        case 0:
            parent = self - 1;
            self->posX.i.hi = parent->posX.i.hi;
            self->velocityY = FIX(4.0);
            self->velocityX = 0;
            self->step_s++;
            /* fall through */
        case 1:
            MoveEntity();
            self->rotate += 0x100;
            self->velocityY += FIX(0.25);
            parent = self - 1;
            delta = parent->posY.i.hi - self->posY.i.hi;
            if (delta < 0x20) {
                parent->ext.minotaur.axeThrown = 1;
                self->animCurFrame = 0;
                self->drawFlags = ENTITY_DEFAULT;
                SetStep(1);
            }
            break;
        }
        break;
    }
}

void EntityMinotaurFireball(Entity* self) {
    s32 angle;
    s32 speed;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitMinotaurFireball);
        speed = fireball_config[self->params][0];
        angle = fireball_config[self->params][1];
        self->velocityX = (-speed * rcos(angle)) >> 0xC;
        self->velocityY = (-speed * rsin(angle)) >> 0xC;
        if (self->facingLeft) {
            self->velocityX = -self->velocityX;
        }
        /* fall through */
    case 1:
        MoveEntity();
        self->velocityY += FIX(0.125);
        break;
    }
}

void EntityMinotaurSpitLiquid(Entity* self) {
    s16 angle;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitMinotaurSpitLiquid);
        self->palette = PAL_FLAG(PAL_CC_TURQUOISE_EFFECT);
        if (self->facingLeft) {
            self->rotate = -self->rotate;
        }
        self->facingLeft = 0;
        self->rotate += ROT(11.25) - Random();
        angle = self->rotate;
        self->velocityX = rsin(angle) << 5;
#ifdef VERSION_PSP
        self->velocityY = (-rcos(angle)) << 5;
#else
        self->velocityY = -(rcos(angle) << 5);
#endif
        self->blendMode = BLEND_ADD | BLEND_TRANSP;
        self->drawFlags =
            ENTITY_OPACITY | ENTITY_ROTATE | ENTITY_SCALEY | ENTITY_SCALEX;
        self->scaleX = 0x40;
        self->scaleY = 0x80;
        self->opacity = 0x80;
        break;
    case 1:
        MoveEntity();
        self->scaleX += 0x10;
        self->scaleY += 0xE;
        self->opacity -= 1;
        if (!AnimateEntity(anim_spit, self)) {
            DestroyEntity(self);
        }
        break;
    }
}

void EntityMinotaurDeathPuff(Entity* self) {
    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitParticle);
        self->animSet = ANIMSET_OVL(4);
        self->unk5A = 0x5C;
        self->palette = 0x21E;
        self->blendMode = BLEND_ADD | BLEND_TRANSP;
        self->drawFlags = ENTITY_OPACITY | ENTITY_SCALEY | ENTITY_SCALEX;
        self->scaleY = 0x180;
        self->scaleX = 0xA0;
        self->opacity = 0x80 - (self->params * 2);
        self->velocityY = FIX(-3.0);
        self->facingLeft = Random() & 1;
        /* fall through */
    case 1:
        MoveEntity();
        self->velocityY -= FIX(0.0625);
        self->opacity -= 2;
        self->scaleX += 8;
        self->scaleY -= 4;
        if (!self->opacity) {
            DestroyEntity(self);
        } else if (!AnimateEntity(anim_death_puff, self)) {
            DestroyEntity(self);
        }
        break;
    }
}
