// SPDX-License-Identifier: AGPL-3.0-or-later

#ifdef VERSION_PSP
extern s32 D_psp_E_KILLER_FISH_DEATH_PUFF;
#endif

extern u8 g_KillerFishAnimIdle[];
extern u8 g_KillerFishAnimSwim[];
extern u8 g_KillerFishAnimRotate[];
extern s16 g_KillerFishDeathPuffPositions[][2];
extern u8 g_KillerFishDeathPuffAnim[];

void EntityKillerFish(Entity* self) {
    Entity* entity;
    s16* ptr;
    s32 i;
    u16 params;

    if (self->flags & FLAG_DEAD && self->step != 4) {
        SetStep(4);
    }

    params = self->params;
    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitKillerFish);
        self->facingLeft = params & 1;
        break;
    case 1:
        // Idle
        // nb. Interesting this is using the in-built rand() and not Random()
        if (!AnimateEntity(g_KillerFishAnimIdle, self) && !(rand() & 3)) {
            SetStep(2);
            self->ext.killerFish.swimTimer = 0x100;
        }
        break;
    case 2:
        // Swim
        if (AnimateEntity(g_KillerFishAnimSwim, self) & 0x80 &&
            (self->pose == 3 || self->pose == 7)) {
            if (self->facingLeft) {
#ifdef STAGE_IS_NO4
                self->velocityX = FIX(1.5);
#else
                self->velocityX = FIX(-1.5);
#endif
            } else {
#ifdef STAGE_IS_NO4
                self->velocityX = FIX(-1.5);
#else
                self->velocityX = FIX(1.5);
#endif
            }
        }
        if (self->velocityX != 0) {
            if (self->facingLeft) {
#ifdef STAGE_IS_NO4
                self->velocityX -= FIX(0.015625);
#else
                self->velocityX += FIX(0.015625);
#endif
            } else {
#ifdef STAGE_IS_NO4
                self->velocityX += FIX(0.015625);
#else
                self->velocityX -= FIX(0.015625);
#endif
            }
        }
        MoveEntity();
        if (!--self->ext.killerFish.swimTimer) {
            self->velocityX = 0;
            SetStep(3);
        }
        break;
    case 3:
        // Finished swimming one direction
        if (!AnimateEntity(g_KillerFishAnimRotate, self)) {
            if (self->ext.killerFish.swimCount++ & 1) {
                // On even numbered trips (left side), wait idle for a bit
                SetStep(1);
            } else {
                // Otherwise swim back the other direction
                self->ext.killerFish.swimTimer = 0x100;
                SetStep(2);
            }
            self->animCurFrame = 1;
            self->facingLeft ^= 1;
            if (self->facingLeft) {
#ifdef STAGE_IS_NO4
                self->posX.i.hi += 8;
#else
                self->posX.i.hi -= 8;
#endif
            } else {
#ifdef STAGE_IS_NO4
                self->posX.i.hi -= 8;
#else
                self->posX.i.hi += 8;
#endif
            }
        }
        break;
    case 4:
        // Death
        PlaySfxPositional(SFX_EXPLODE_B);
        ptr = g_KillerFishDeathPuffPositions[0];

        for (i = 0; i < 5; i++) {
            entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (entity == NULL) {
                break;
            }
#if defined(STAGE_IS_NO4) || defined(VERSION_PSP)
            CreateEntityFromCurrentEntity(E_ID(KILLER_FISH_DEATH_PUFF), entity);
#else
            CreateEntityFromCurrentEntity(E_KILLER_FISH_DEATH_PUFF, entity);
#endif
            if (self->facingLeft) {
                entity->posX.i.hi += *ptr++;
            } else {
                entity->posX.i.hi -= *ptr++;
            }
            entity->posY.i.hi += *ptr++;
        }

        DestroyEntity(self);
        return;
    }

    params = self->animCurFrame;
    if (params == 9) {
        // Hitbox shrinks slightly in the middle of changing directions
        self->hitboxWidth = 6;
        self->hitboxOffX = -0xA;
    } else {
        self->hitboxWidth = 0x14;
        self->hitboxOffX = 0;
        if (params >= 10 && params < 13) {
            self->hitboxWidth = 0x10;
            self->hitboxOffX = 4;
        }
    }
    self->hitboxOffY = 2;
    self->hitboxHeight = 8;
}

void EntityKillerFishDeathPuff(Entity* self) {
    if (!self->step) {
        InitializeEntity(g_EInitParticle);
        self->pose = 0;
        self->poseTimer = 0;
        self->animSet = 0xE;
        self->unk5A = 0x79;
        self->palette = 0x2E8;
        self->blendMode = BLEND_TRANSP | BLEND_ADD;
        self->drawFlags = ENTITY_OPACITY;
        self->opacity = 0x60;
        if (self->params & 0xFF00) {
            self->zPriority = (self->params & 0xFF00) >> 8;
        }
        self->velocityY += -0x8000 - 0x8000;
        return;
    }

    self->posY.val += self->velocityY;
    if (!AnimateEntity(g_KillerFishDeathPuffAnim, self)) {
        DestroyEntity(self);
    }
}
