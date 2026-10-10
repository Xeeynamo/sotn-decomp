// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rno2.h"

extern EInit g_EInitKarasuman;

static s16 D_us_8018115C[] = {
    0, 32, 0, 4, 4, -4, -8, 0,
};

static s16 D_us_8018116C[] UNUSED = {
    0,
    32,
    4,
    0,
};

static AnimateEntityFrame anim_breathing[] = {
    {30, 1}, {30, 2}, POSE_LOOP(0)
};

static AnimateEntityFrame anim_unfurl_wings[] = {
    {8, 1}, {6, 3}, {4, 4}, {4, 47}, {1, 10}, {1, 48}, {16, 10}, {6, 9}, {6, 47}, {4, 4}, POSE_END
};

static AnimateEntityFrame anim_begin_jump[] = {
    {2, 4}, {8, 5}, {8, 6}, {3, 5}, POSE_END
};

static AnimateEntityFrame anim_rising[] = {
    {8, 7}, {8, 8}, {2, 15}, POSE_END
};

static AnimateEntityFrame anim_flapping[] = {
    {8, 15}, {8, 16}, {8, 17}, {8, 18}, {8, 19}, {8, 20}, {8, 21}, POSE_LOOP(0)
};

static AnimateEntityFrame anim_relax_wings_flying[] = {
    {8, 15}, {8, 7}, POSE_END
};

static AnimateEntityFrame anim_landing[] = {
    {8, 5}, {8, 6}, {8, 5}, {8, 4}, POSE_END
};

static AnimateEntityFrame anim_4wings_featherattack[] = {
    {4, 11}, {2, 12}, {1, 13}, {1, 12}, POSE_END
};

static AnimateEntityFrame anim_end_featherattack[] = {
    {4, 11}, {4, 7}, POSE_END
};

static AnimateEntityFrame anim_prep_orbs[] = {
    {16, 15}, {4, 22}, {2, 23}, POSE_END
};

static AnimateEntityFrame anim_flashing_make_orbs[] = {
    {1, 23}, {1, 24}, {1, 25}, POSE_LOOP(0)
};

static AnimateEntityFrame anim_wings_low[] = {
    {4, 23}, {4, 26}, {4, 27}, {6, 28}, {16, 29}, {8, 21}, POSE_END
};

static AnimateEntityFrame anim_orb[] = {
    {10, 30}, {1, 31}, {1, 32}, {1, 33}, {1, 34}, {1, 30}, {1, 35}, {1, 36}, {1, 37}, {1, 38}, {1, 30}, {1, 39}, {1, 40}, {1, 41}, {1, 42}, {1, 30}, {1, 43}, {1, 44}, {1, 45}, {1, 46}, POSE_LOOP(0)
};

static AnimateEntityFrame anim_prep_ravens[] = {
    {24, 4}, {8, 47}, {1, 10}, {1, 48}, {1, 10}, POSE_END
};

static AnimateEntityFrame anim_relax_wings_ground[] = {
    {8, 9}, {8, 47}, POSE_END
};

static AnimateEntityFrame anim_turn_ravens[] = {
    {16, 15}, {8, 14}, {32, 49}, {2, 50}, {2, 51}, POSE_END
};

static AnimateEntityFrame anim_finish_ravens[] = {
    {8, 52}, {8, 53}, {8, 14}, POSE_END
};

static AnimateEntityFrame anim_raven[] = {
    {4, 54}, {4, 55}, {4, 56}, {4, 57}, {4, 58}, {4, 56}, POSE_LOOP(0)
};

static AnimateEntityFrame anim_flinch[] = {
    {1, 53}, {3, 49}, {2, 52}, {1, 50}, {1, 51}, {24, 60}, POSE_END
};

static AnimateEntityFrame anim_death[] = {
    {4, 51}, {24, 60}, POSE_END
};

static FrameProperty D_us_8018127C[] = {
    {0x00, 0x00, 0x00, 0x00}, {0x00, 0x08, 0x04, 0x17},
    {0x00, 0x0C, 0x04, 0x13}, {0x00, 0x0D, 0x04, 0x12},
    {0x00, 0x07, 0x04, 0x12}, {0x00, 0x04, 0x04, 0x13},
    {0x00, 0x07, 0x04, 0x17}, {0x00, 0x05, 0x04, 0x13},
    {0x00, 0x00, 0x08, 0x08}, {0xFF, 0x01, 0x08, 0x08},
    {0x02, 0x03, 0x04, 0x13}, {0x00, 0x00, 0x04, 0x06},
    {0x00, 0x00, 0x0E, 0x02}, {0xC0, 0xB8, 0x00, 0x00},
    {0xF8, 0xF8, 0x00, 0x00},
};

static u8 D_us_801812B8[] = {
    0, 1, 1, 1, 1, 2,  3, 1, 4, 1, 1,  1,  1,  1,  5,  6,  7,  7,  7,  7,  7, 7,
    7, 7, 7, 7, 7, 7,  7, 7, 8, 8, 8,  8,  8,  8,  8,  8,  8,  8,  9,  8,  8, 8,
    8, 8, 8, 1, 1, 10, 7, 7, 7, 5, 11, 11, 11, 11, 11, 12, 10, 13, 13, 14,
};

typedef enum {
    KARA_INIT,
    KARA_WAIT,
    KARA_WAKEUP,
    KARA_3,
    KARA_4,
    KARA_5,
    KARA_6,
    KARA_7,
    KARA_8,
    KARA_9,
    KARA_10,
    KARA_11,
    KARA_FLINCH,
    KARA_13,
    KARA_DEATH,
    KARA_15,
    KARA_16
} KaraSteps;

void EntityKarasuman(Entity* self) {
    Entity* entity;
    s32 i;
    s32 offsetX;
    s32 offsetY;
    s8* frameProperty;

    // If the step is odd, karasuman is vulnerable to flinching
    if (self->hitFlags & 3 && self->step & 1) {
        SetStep(KARA_FLINCH);
    }
    if (self->flags & FLAG_DEAD && self->step < 14) {
        SetStep(KARA_DEATH);
    }

    switch (self->step) {
    case KARA_INIT:
        InitializeEntity(g_EInitKarasuman);
        self->animCurFrame = 1;
        // fallthrough

    case KARA_WAIT:
        if (UnkCollisionFunc3(D_us_8018115C) & 1) {
            SetStep(KARA_WAKEUP);
        }
        break;

    case KARA_WAKEUP:
        switch (self->step_s) {
        case 0:
            AnimateEntity(anim_breathing, self);
            if (GetDistanceToPlayerX() < 0x50) {
                SetSubStep(1);
            }
            break;
        case 1:
            if (AnimateEntity(anim_unfurl_wings, self) == 0) {
                SetStep(KARA_5);
            }
            break;
        }
        break;
    case KARA_5:
        switch (self->step_s) {
        case 0:
            if (AnimateEntity(anim_begin_jump, self) == 0) {
                self->velocityX = 0;
                self->velocityY = FIX(-4);
                SetSubStep(1);
            }
            break;
        case 1:
            MoveEntity();
            self->velocityY += FIX(0.125);
            if (AnimateEntity(anim_rising, self) == 0) {
                SetStep(KARA_3);
                if (self->ext.karasuman.flag2) {
                    SetStep(KARA_10);
                }
            }
            break;
        }
        break;

    case KARA_3:
        if (!self->step_s) {
            self->ext.karasuman.timer = 0x80;
            self->velocityY = 0;
            self->step_s++;
        }
        AnimateEntity(anim_flapping, self);
        if (GetSideToPlayer() & 1) {
            self->velocityX -= FIX(1.0 / 64.0);
            if (self->velocityX < FIX(-0.75)) {
                self->velocityX = FIX(-0.75);
            }
        } else {
            self->velocityX += FIX(1.0 / 64.0);
            if (self->velocityX > FIX(0.75)) {
                self->velocityX = FIX(0.75);
            }
        }
        if (!self->poseTimer && self->pose == 1) {
            PlaySfxPositional(SFX_UNK_NZ1_722);
        }

        if (!--self->ext.karasuman.timer) {
            if (self->ext.karasuman.flag0) {
                SetStep(KARA_6);
            } else {
                SetStep(KARA_4);
            }
            self->ext.karasuman.flag0 ^= 1;
        }
        break;
    case KARA_4:
        switch (self->step_s) {
        case 0:
            if (AnimateEntity(anim_4wings_featherattack, self) == 0) {
                self->ext.karasuman.timer = 48;
                SetSubStep(1);
            }
            break;
        case 1:
            if (!(g_Timer & 7)) {
                PlaySfxPositional(SFX_BAT_ECHO_C);
                for (i = 0; i < 8; i++) {
                    entity = AllocEntity(&g_Entities[160], &g_Entities[192]);
                    if (entity != NULL) {
                        CreateEntityFromEntity(
                            E_KARASUMAN_FEATHER_ATTACK, self, entity);
                        entity->posY.i.hi -= 28;
                    }
                }
            }
            if (!--self->ext.karasuman.timer) {
                self->step_s++;
            }
            break;
        case 2:
            if (AnimateEntity(anim_end_featherattack, self) == 0) {
                SetStep(KARA_7);
                self->step_s = 2;
            }
            break;
        }
        break;
    case KARA_7:
        switch (self->step_s) {
        case 0:
            self->velocityX = 0;
            self->velocityY = 0;
            self->step_s++;
            // fallthrough
        case 1:
            if (AnimateEntity(anim_relax_wings_flying, self) == 0) {
                SetSubStep(2);
            }
            break;
        case 2:
            if (UnkCollisionFunc3(D_us_8018115C) & 1) {
                self->step_s++;
            } else {
                self->velocityY -= FIX(0.09375);
            }
            break;
        case 3:
            if (AnimateEntity(anim_landing, self) == 0) {
                SetStep(KARA_5); // This is dumb, we override it immediately
                SetStep(KARA_8);
            }
            break;
        }
        break;
    case KARA_6:
        switch (self->step_s) {
        case 0:
            self->ext.karasuman.flag1 = 0;
            if (AnimateEntity(anim_prep_orbs, self) == 0) {
                SetSubStep(1);
            }
            break;
        case 1:
            for (i = 0; i < 4; i++) {
                entity = AllocEntity(&g_Entities[160], &g_Entities[192]);
                if (entity != NULL) {
                    CreateEntityFromEntity(
                        E_KARASUMAN_ORB_ATTACK, self, entity);
                    entity->params = i;
                    entity->ext.karasuman.parent = self;
                    entity->zPriority = self->zPriority + 1;
                }
            }
            PlaySfxPositional(SFX_RNO2_ANIME_SWORD);
            self->ext.karasuman.timer = 128;
            self->step_s++;
            // fallthrough
        case 2:
            AnimateEntity(anim_flashing_make_orbs, self);
            if (!(self->ext.karasuman.timer & 7)) {
                PlaySfxPositional(SFX_RAPID_SYNTH_BUBBLE_SHORT);
            }
            if (!--self->ext.karasuman.timer) {
                PlaySfxPositional(SFX_TELEPORT_BANG_A);
                self->ext.karasuman.flag1 = 1;
                self->drawFlags = ENTITY_SCALEY | ENTITY_SCALEX;
                self->scaleX = self->scaleY = 256;
                self->velocityY = FIX(-6.0);
                self->velocityX = 0;
                SetSubStep(3);
            }
            break;
        case 3:
            if (AnimateEntity(anim_wings_low, self) == 0) {
                self->step_s++;
            }
            // fallthrough
        case 4:
            MoveEntity();
            self->velocityY -= self->velocityY / 8;
            if (self->scaleX > 224) {
                self->scaleX = self->scaleY -= 4;
            } else if (self->step_s == 4) {
                self->step_s++;
            }
            break;
        case 5:
            self->scaleX = self->scaleY += 8;
            if (self->scaleX > 256) {
                self->drawFlags = ENTITY_DEFAULT;
                SetStep(KARA_7);
            }
            break;
        }
        break;
    case KARA_8:
        switch (self->step_s) {
        case 0:
            if (AnimateEntity(anim_prep_ravens, self) == 0) {
                SetSubStep(1);
            }
            break;
        case 1:
            self->ext.karasuman.timer = 128;
            self->ext.karasuman.flag2 = 1;
            self->step_s++;
            // fallthrough
        case 2:
            if (!(self->ext.karasuman.timer & 3)) {
                entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
                if (entity != NULL) {
                    CreateEntityFromEntity(
                        E_KARASUMAN_RAVEN_ATTACK, self, entity);
                    entity->ext.karasuman.parent = self;
                    entity->params = 1;
                }
            }
            if (!(self->ext.karasuman.timer & 7)) {
                g_api.PlaySfx(SFX_WING_FLAP_A);
            }

            if (!--self->ext.karasuman.timer) {
                self->ext.karasuman.timer = 64;
                self->step_s++;
            }
            break;
        case 3:
            if (AnimateEntity(anim_relax_wings_ground, self) == 0) {
                SetStep(KARA_5);
            }
        }
        break;
    case KARA_10:
        switch (self->step_s) {
        case 0:
            self->ext.karasuman.flag2 = 0;
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
            self->step_s++;
            // fallthrough
        case 1:
            if (AnimateEntity(anim_turn_ravens, self) == 0) {
                self->ext.karasuman.timer = 96;
                if (self->facingLeft) {
                    self->velocityX = FIX(-2.0);
                } else {
                    self->velocityX = FIX(2.0);
                }
                self->velocityY = FIX(-2.0);
                self->step_s++;
            }
            break;
        case 2:
            if (self->ext.karasuman.timer > 0x48) {
                MoveEntity();
                self->velocityX -= self->velocityX / 8;
                self->velocityY -= self->velocityY / 8;
            }
            if (!(self->ext.karasuman.timer & 7)) {
                g_api.PlaySfx(SFX_WING_FLAP_A);
                entity = AllocEntity(&g_Entities[160], &g_Entities[192]);
                if (entity != NULL) {
                    CreateEntityFromEntity(
                        E_KARASUMAN_RAVEN_ATTACK, self, entity);
                    entity->facingLeft = self->facingLeft;
                    entity->ext.karasuman.parent = self;
                }
            }

            if (!--self->ext.karasuman.timer) {
                SetSubStep(3);
            }
            break;
        case 3:
            if (AnimateEntity(anim_finish_ravens, self) == 0) {
                SetStep(KARA_3);
            }
            break;
        }
        break;
    case KARA_FLINCH:
        if (!self->step_s) {
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
            if (self->facingLeft) {
                self->velocityX = FIX(-4.0);
            } else {
                self->velocityX = FIX(4.0);
            }
            self->velocityY = FIX(-2.0);
            for (i = 0; i < 8; i++) {
                entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
                if (entity != NULL) {
                    CreateEntityFromEntity(
                        E_KARASUMAN_FEATHER, self, entity);
                    if (Random() & 1) {
                        entity->zPriority = self->zPriority + 1;
                    } else {
                        entity->zPriority = self->zPriority - 1;
                    }
                }
            };
            self->step_s++;
        }
        MoveEntity();

        self->velocityX -= self->velocityX / 16;
        self->velocityY -= self->velocityY / 16;

        if (AnimateEntity(anim_flinch, self) == 0) {
            SetStep(KARA_7);
        }
        break;
    case KARA_DEATH:
        switch (self->step_s) {
        case 0:
            self->hitboxState = 0;
            for (i = 0; i < 32; i++) {
                entity = AllocEntity(&g_Entities[160], &g_Entities[256]);
                if (entity != NULL) {
                    CreateEntityFromEntity(
                        E_KARASUMAN_FEATHER, self, entity);
                    if (Random() & 1) {
                        entity->zPriority = self->zPriority + 1;
                    } else {
                        entity->zPriority = self->zPriority - 1;
                    }
                }
            }
            PlaySfxPositional(SFX_UNK_NZ1_723);
            self->step_s++;
            // fallthrough
        case 1:
            if ((AnimateEntity(anim_death, self) == 0) &&
                (UnkCollisionFunc3(D_us_8018115C) & 1)) {
                self->step_s++;
            }
            break;
        case 2:
            entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (entity != NULL) {
                CreateEntityFromEntity(
                    E_KARASUMAN_RAVEN_ABSORB, self, entity);
                entity->params = 1;
                entity->zPriority = self->zPriority + 1;
            }
            self->ext.karasuman.timer = 64;
            self->step_s++;
            // fallthrough
        case 3:
            if ((self->ext.karasuman.timer & 0x1)) {
                entity = AllocEntity(&g_Entities[160], &g_Entities[256]);
                if (entity != NULL) {
                    CreateEntityFromEntity(
                        E_KARASUMAN_RAVEN_ABSORB, self, entity);
                    entity->facingLeft = Random() & 1;
                    entity->params = 0;
                    entity->zPriority = self->zPriority + 1;
                }
            }

            if (!(self->ext.karasuman.timer & 0xF)) {
                PlaySfxPositional(SFX_WING_FLAP_A);
            }

            if (!--self->ext.karasuman.timer) {
                self->palette = PAL_FLAG(0x2E4);
                self->blendMode = BLEND_TRANSP | BLEND_ADD;
                self->drawFlags |= ENTITY_OPACITY;
                self->opacity = 0x80;
                self->ext.karasuman.timer = 32;
                self->step_s++;
            }
            break;
        case 4:
            if((g_Timer & 0xF) == 0){
                PlaySfxPositional(SFX_FIREBALL_SHOT_B);
                entity = AllocEntity(&g_Entities[160], &g_Entities[256]);
                if (entity != NULL) {
                    CreateEntityFromEntity(
                        E_EXPLOSION, self, entity);
                    entity->facingLeft = Random() & 1;
                    entity->zPriority = self->zPriority + 1;
                    entity->posY.i.hi += 32;
                    entity->params = 3;
                }
            }
            if (self->opacity) {
                self->opacity -= 3;
            }

            if (!--self->ext.karasuman.timer) {
                DestroyEntity(self);
                return;
            }
            break;
        }
        break;
    case 0xFF:
#include "../pad2_anim_debug.h"
        break;
    }

    frameProperty = (s8*)D_us_8018127C;
    frameProperty += D_us_801812B8[self->animCurFrame] * sizeof(FrameProperty);
    self->hitboxOffX = *frameProperty++;
    self->hitboxOffY = *frameProperty++;
    self->hitboxWidth = *frameProperty++;
    self->hitboxHeight = *frameProperty++;
}

extern EInit D_us_80180928;

void EntityKarasumanFeatherAttack(Entity* self) {
    Entity* entity;
    s16 angle;

    switch (self->step) {
    case 0:
        InitializeEntity(D_us_80180928);
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
        self->posX.i.hi += FLT_TO_I(32 * rcos(angle));
        self->posY.i.hi += FLT_TO_I(-32 * rsin(angle));
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

extern EInit g_EInitKarasumanOrbAttack;

void EntityKarasumanOrbAttack(Entity* self) {
    Entity* entity;
    s16 angle;
    s16 angleBetweenEntities;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitKarasumanOrbAttack);
        self->drawFlags = ENTITY_SCALEY | ENTITY_SCALEX;
        self->scaleX = self->scaleY = 0;
        self->blendMode = BLEND_TRANSP | BLEND_ADD;
        // fallthrough

    case 1:
        self->scaleX = self->scaleY += 6;
        if (self->scaleX > 0xA0) {
            self->step++;
        }
        // fallthrough

    case 2:
        AnimateEntity(anim_orb, self);
        entity = self->ext.karasuman.parent;
        if (entity->ext.karasuman.flag1) {
            self->step++;
        }
        #ifndef VERSION_PSP
        if(entity->entityId != E_KARASUMAN || entity->flags & FLAG_DEAD){
            DestroyEntity(self);
            return;
        }
        #endif
        break;

    case 3:
        angle = (self->params << 9) + ROT(22.5);
        self->velocityX = rcos(angle) << 6;
        self->velocityY = rsin(angle) << 6;
        self->ext.karasuman.angle = angle;
        self->ext.karasuman.timer = 128;
        self->step++;
        // fallthrough

    case 4:
        entity = &PLAYER;
        angle = GetAngleBetweenEntities(self, entity);
        angle = LimitAngleChange(24, self->ext.karasuman.angle, angle);
        self->velocityX = 64 * rcos(angle);
        self->velocityY = 64 * rsin(angle);
        self->ext.karasuman.angle = angle;
        if (self->hitFlags & 0x80) {
            self->ext.karasuman.timer = 16;
            self->step = 6;
        }

        if (!--self->ext.karasuman.timer) {
            self->step++;
        }
        // fallthrough

    case 5:
        self->flags |= FLAG_DESTROY_IF_OUT_OF_CAMERA;
        AnimateEntity(anim_orb, self);
        MoveEntity();
        break;

    case 6:
        AnimateEntity(anim_orb, self);
        entity = &PLAYER;
        self->posX.i.hi = entity->posX.i.hi;
        self->posY.i.hi = entity->posY.i.hi;
        if (!--self->ext.karasuman.timer) {
            self->step = 5;
        }
        break;
    }
}

extern EInit g_EInitKarasumanRavenAttack;

void EntityKarasumanRavenAttack(Entity* self) {
    Entity* entity;
    s32 offsetX;
    s32 offsetY;
    s32 opacity;
    s16 angle;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitKarasumanRavenAttack);
        if (self->params) {
            self->hitboxState = 0;
            self->step = 8;
            return;
        }
        self->flags |= FLAG_DESTROY_IF_OUT_OF_CAMERA;
        angle = ((Random() & 0x1F) * 0x10) + ROT(22.5);
        self->rotate = -angle;
        if (!self->facingLeft) {
            angle = FLT(0.5) - angle;
        }
        self->velocityX = rcos(angle) * 0x38;
        self->velocityY = rsin(angle) * 0x38;
        // fallthrough

    case 1:
        MoveEntity();
        AnimateEntity(anim_raven, self);
        entity = &PLAYER;
        if (entity->posY.i.hi < self->posY.i.hi) {
            self->velocityY -= FIX(1.0 / 32.0);
        }
        if (self->flags & FLAG_DEAD) {
            entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (entity != NULL) {
                CreateEntityFromEntity(E_EXPLOSION, self, entity);
                entity->params = 1;
            }
            DestroyEntity(self);
        }
        break;

    case 8:
        self->palette = PAL_FLAG(PAL_FILL_WHITE);
        self->drawFlags = ENTITY_OPACITY;
        self->opacity = 0;
        self->blendMode = BLEND_TRANSP | BLEND_SUB;
        entity = self->ext.karasuman.parent;
        angle = Random() * 16;
        self->posX.i.hi += FLT_TO_I(128 * rcos(angle));
        self->posY.i.hi += FLT_TO_I(128 * rsin(angle));
        self->step++;
        // fallthrough

    case 9:
        if (self->opacity < 32) {
            self->opacity += 2;
        } else {
            self->step++;
        }
        break;

    case 10:
        entity = self->ext.karasuman.parent;
        if (entity->entityId != E_KARASUMAN) {
            DestroyEntity(self);
            return;
        }
        angle = GetAngleBetweenEntities(self, entity);
        angle = LimitAngleChange(64, self->ext.karasuman.angle, angle);
        self->velocityX = 64 * rcos(angle);
        self->velocityY = 64 * rsin(angle);
        self->ext.karasuman.angle = angle;
        if (self->velocityX > 0) {
            self->facingLeft = 1;
        } else {
            self->facingLeft = 0;
        }
        MoveEntity();
        AnimateEntity(anim_raven, self);
        offsetX = entity->posX.i.hi - self->posX.i.hi;
        offsetY = entity->posY.i.hi - self->posY.i.hi;
        opacity = SquareRoot0(SQ(offsetX) + SQ(offsetY));

        self->opacity = opacity / 4;
        if (opacity < 16) {
            DestroyEntity(self);
            return;
        }

        if (!entity->ext.karasuman.flag2) {
            self->step++;
        }
        break;

    case 11:
        self->opacity -= 8;
        if (self->opacity > 240) {
            DestroyEntity(self);
        }
        break;
    }
}

extern EInit D_us_8018094C;

void EntityKarasumanFeather(Entity* self) {
    s16 angle;
    s32 scale;

    switch (self->step) {
    case 0:
        InitializeEntity(D_us_8018094C);
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

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitKarasumanRavenAttack);
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
        AnimateEntity(anim_raven, self);
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
