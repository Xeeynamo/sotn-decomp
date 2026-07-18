// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../cen/cen.h"

static s32 func_pspeu_092A6958(s32 x, s32 y, s32 horizPixelCount) {
    Collider collider;
    g_api.CheckCollision(x, y, &collider, 0);

    while (collider.effects & EFFECT_UNK_0002) {
        if (horizPixelCount-- < 0) {
            return -1;
        }

        y--;
        g_api.CheckCollision(x, y, &collider, 0);
    }

    return y;
}

static s32 CheckFieldCollisionForCat(
    Entity* self, s32 x, s32 y, Collider* collider) {
    s32 origPosX, origPosY;
    s32 posX, posY;
    s32 var_s5;
    s32 var_s4;
    s32 var_s3;
    s32 var_s2;
    s32 i, j;

    var_s3 = abs(x) >> 0x10;
    var_s2 = abs(y) >> 0x10;
    if (x < 0) {
        x = -var_s3;
    } else {
        x = var_s3;
    }

    if (y < 0) {
        y = -var_s2;
    } else {
        y = var_s2;
    }

    posX = self->posX.i.hi;
    origPosX = posX;
    posY = self->posY.i.hi;
    origPosY = posY;

    if (var_s2 < var_s3) {
        if (var_s3 == 0) {
            return 0;
        }

        for (i = 0; i <= var_s3; i++) {
            if (x < 0) {
                var_s5 = -i;
            } else {
                var_s5 = i;
            }
            self->posX.i.hi = origPosX + var_s5;
            self->posY.i.hi = origPosY + ((y * i) / var_s3);
            g_api.CheckCollision(self->posX.i.hi, self->posY.i.hi, collider, 0);
            if (collider->effects & (EFFECT_UNK_0002 | EFFECT_SOLID)) {
                if (var_s2 == 0) {
                    collider->effects = EFFECT_SOLID;
                }
                self->posX.i.hi = posX;
                self->posY.i.hi = posY;
                if (i != 0 && y > 0) {
                    g_api.CheckCollision(
                        self->posX.i.hi, self->posY.i.hi + 1, collider, 0);
                    if (collider->effects & (EFFECT_UNK_0002 | EFFECT_SOLID)) {
                        collider->effects = EFFECT_UNK_0002;
                    } else {
                        collider->effects = EFFECT_SOLID;
                    }
                }
                return 1;
            }
            posX = self->posX.i.hi;
            posY = self->posY.i.hi;
        }
    } else {
        if (var_s2 == 0) {
            return 0;
        }

        for (j = 0; j <= var_s2; j++) {
            self->posX.i.hi = origPosX + ((x * j) / var_s2);
            if (y < 0) {
                var_s4 = -j;
            } else {
                var_s4 = j;
            }
            self->posY.i.hi = origPosY + var_s4;
            g_api.CheckCollision(self->posX.i.hi, self->posY.i.hi, collider, 0);
            if (collider->effects & (EFFECT_UNK_0002 | EFFECT_SOLID)) {
                if (var_s3 == 0) {
                    collider->effects = EFFECT_UNK_0002;
                }
                self->posX.i.hi = posX;
                self->posY.i.hi = posY;
                if (j != 0 && y > 0) {
                    g_api.CheckCollision(
                        self->posX.i.hi, self->posY.i.hi + 1, collider, 0);
                    if (collider->effects & (EFFECT_UNK_0002 | EFFECT_SOLID)) {
                        collider->effects = EFFECT_UNK_0002;
                    } else {
                        collider->effects = EFFECT_SOLID;
                    }
                }
                return 1;
            }
            posX = self->posX.i.hi;
            posY = self->posY.i.hi;
        }
    }

    return 0;
}

static AnimationFrame anim_cat[] = {
    POSE(11, 1, 0), POSE(4, 2, 0), POSE(6, 3, 0),
    POSE(4, 4, 0),  POSE(7, 5, 0), POSE_LOOP(0)};
void EntityMariaCatAttack(Entity* self) {
    Collider collider;
    s32 newY;

    switch (self->step) {
    case 0:
        self->flags = FLAG_POS_CAMERA_LOCKED | FLAG_KEEP_ALIVE_OFFCAMERA |
                      FLAG_UNK_100000;
        self->unk5A = 0x54;
        self->zPriority = MARIA.zPriority - 8;
        self->palette = PAL_WPN_CAT;
        self->animSet = ANIMSET_WPN_CAT;
        MarSetAnimation(anim_cat);
        self->facingLeft = MARIA.facingLeft;
        self->velocityX = FIX(3.0);
        self->posX.i.hi = MARIA.posX.i.hi;
        self->posY.i.hi = MARIA.posY.i.hi;
        self->hitboxWidth = 0x12;
        self->hitboxHeight = 0x1E;
        self->hitboxOffX = 0;
        self->hitboxOffY = -8;
        self->ext.mariaCat.unkB0 = 0;
        MarSetWeaponParams(self, 36, ELEMENT_HOLY, 8, 16, 16, 1, 0);
        self->ext.mariaCat.timer = 0;
        g_Maria.unk7A = 1;
        self->ext.mariaCat.nBounce = 3;
        self->step = 2;
        self->ext.mariaCat.opacity = 128;
        break;
    case 1:
        self->velocityX += FIX(1.0);
        if (self->velocityX > FIX(3.0)) {
            self->velocityX = FIX(3.0);
        }

        if ((self->ext.mariaCat.timer % 10) == 0) {
            g_api.PlaySfx(SFX_QUIET_STEPS);
        }
        self->ext.mariaCat.timer++;

        CheckFieldCollisionForCat(
            self, self->facingLeft ? -self->velocityX : self->velocityX, 0,
            &collider);
        if (collider.effects & EFFECT_SOLID || self->hitFlags == 0x80) {
            self->velocityX = FIX(-3.0);
            self->velocityY = FIX(-8.0);
            self->ext.mariaCat.nBounce = 0;
            if (collider.effects & EFFECT_SOLID) {
                self->ext.mariaCat.nBounce = 0;
            }

            if (self->ext.mariaCat.nBounce > 0) {
                self->ext.mariaCat.nBounce--;
                self->step = 3;
            } else {
                self->step = 4;
            }

            self->ext.mariaCat.timer = 0;
        } else {
            g_api.CheckCollision(
                self->posX.i.hi, self->posY.i.hi + 1, &collider, 0);
            if (!(collider.effects & EFFECT_UNK_0002)) {
                self->velocityY = FIX(-8.0);
                self->step = 2;
                self->ext.mariaCat.timer = 0;
            }
        }
        break;
    case 2:
    case 3:
        if (self->step == 2) {
            self->velocityX += FIX(1.0);
            if (self->velocityX > FIX(3.0)) {
                self->velocityX = FIX(3.0);
            }
        }

        self->velocityY += FIX(1.0);
        if (self->velocityY > FIX(4.0)) {
            self->velocityY = FIX(4.0);
        }

        CheckFieldCollisionForCat(
            self, self->facingLeft ? -self->velocityX : self->velocityX,
            self->velocityY, &collider);
        if (collider.effects & EFFECT_UNK_0002) {
            newY = func_pspeu_092A6958(
                self->posX.i.hi, self->posY.i.hi, self->velocityY >> 0x10);
            if (newY != -1) {
                self->velocityX = FIX(3.0);
                self->posY.i.hi = newY;
                self->posY.i.lo = 0;
                self->step = 1;
                collider.effects = EFFECT_NONE;
                self->hitFlags = 0;
            }
        }

        if (collider.effects & EFFECT_SOLID || self->hitFlags == 0x80) {
            self->velocityX = FIX(-3.0);
            self->velocityY = FIX(-8.0);
            self->ext.mariaCat.nBounce = 0;
            if (collider.effects & EFFECT_SOLID) {
                self->ext.mariaCat.nBounce = 0;
            }

            if (self->ext.mariaCat.nBounce > 0) {
                self->ext.mariaCat.nBounce--;
                self->step = 3;
            } else {
                self->step = 4;
            }
        }
        break;
    case 4:
        self->hitboxState = 0;
        self->velocityY += FIX(1.0);
        if (self->velocityY > FIX(4.0)) {
            self->velocityY = FIX(4.0);
        }

        self->posX.val += self->facingLeft ? -self->velocityX : self->velocityX;
        self->posY.val += self->velocityY;
        self->ext.mariaCat.opacity -= 8;
        if (self->ext.mariaCat.opacity <= 0) {
            SetOpacity(self, 0);
            self->step = 5;
        } else {
            SetOpacity(self, self->ext.mariaCat.opacity);
        }
        break;
    case 5:
        g_Maria.unk7A = 0;
        DestroyEntity(self);
        break;
    }
    if (self->step != 5) {
        if (self->posX.i.hi < -8 || self->posX.i.hi > 264 ||
            self->posY.i.hi > 264) {
            self->step = 5;
        }
    }
    self->hitFlags = 0;
}

static AnimationFrame anim_cat_crash_stand[] = {
    POSE(13, 6, 0), POSE(8, 7, 0), POSE(11, 8, 0), POSE(8, 7, 0), POSE_LOOP(0)};
void EntityMariaCatCrash(Entity* self) {
    switch (self->step) {
    case 0:
        self->flags = FLAG_POS_CAMERA_LOCKED | FLAG_KEEP_ALIVE_OFFCAMERA |
                      FLAG_UNK_100000;
        self->unk5A = 0x54;
        self->zPriority = MARIA.zPriority - 8;
        self->palette = PAL_WPN_CAT_CRASH;
        self->animSet = ANIMSET_WPN_CAT;
        MarSetAnimation(anim_cat_crash_stand);
        self->ext.mariaCat.timer = 0;
        self->ext.mariaCat.opacity = 0;
        self->ext.mariaCat.unk46 = g_Maria.unk46;
        self->step = 1;
        SpawnCrashSummon(2);
        SetOpacity(self, 0);
        break;
    case 1:
        if (g_Maria.unk5C == 1) {
            g_api.PlaySfx(SFX_VO_MAR_8F1 + MAR_SFX_OFFSET);
            self->step = 3;
        }
        break;
    case 3:
        self->facingLeft = MARIA.facingLeft;
        self->posX.i.hi = MARIA.posX.i.hi;
        self->posY.i.hi = MARIA.posY.i.hi + 0x18;
        self->ext.mariaCat.opacity += 16;

        if (self->ext.mariaCat.opacity >= 128) {
            SetOpacity(self, 128);
            self->ext.mariaCat.opacity = 0;
            self->step = 2;
        } else {
            SetOpacity(self, self->ext.mariaCat.opacity);
        }

        break;
    case 4:
        self->posX.i.hi += self->facingLeft ? -4 : 4;
        self->ext.mariaCat.opacity -= 16;
        if (self->ext.mariaCat.opacity <= 0) {
            SetOpacity(self, 0);
            self->ext.mariaCat.opacity = 0;
            self->step = self->ext.mariaCat.timer > 300 ? 5 : 3;
        } else {
            SetOpacity(self, self->ext.mariaCat.opacity);
        }
        break;
    case 2:
        if (self->facingLeft != MARIA.facingLeft) {
            self->ext.mariaCat.opacity = 128;
            self->step = 4;
        } else {
            self->facingLeft = MARIA.facingLeft;
            self->posX.i.hi = MARIA.posX.i.hi;
            self->posY.i.hi = MARIA.posY.i.hi + 0x18;

            if (self->ext.mariaCat.timer > 300) {
                self->ext.mariaCat.opacity = 128;
                self->step = 4;
            }
        }
        break;
    case 5:
        g_Maria.unk5C = 0;
        DestroyEntity(self);
        break;
    }

    self->ext.mariaCat.timer++;
    if (self->step != 5 && (g_Maria.padTapped & PAD_SQUARE)) {
        // while the big cat is on screen, pressing the Attack button will
        // unleash its power
        MarCreateEntFactoryFromEntity(self, BP_CAT_CRASH_ATTACK, 0);
    }
    self->ext.mariaCat.unk46 = g_Maria.unk46;
}

static AnimationFrame anim_cat_crash_attack[] = {
    POSE(1, 10, 0), POSE(1, 11, 0), POSE(1, 12, 0),
    POSE(3, 13, 0), POSE(1, 14, 0), POSE(1, 15, 0),
    POSE(1, 16, 0), POSE(25, 9, 0), POSE_END};
void EntityMariaCatCrashAttack(Entity* self) {
    switch (self->step) {
    case 0:
        self->flags = FLAG_POS_CAMERA_LOCKED | FLAG_KEEP_ALIVE_OFFCAMERA |
                      FLAG_UNK_100000;
        self->unk5A = 0x54;
        self->zPriority = MARIA.zPriority - 8;
        self->palette = PAL_WPN_CAT;
        self->animSet = ANIMSET_WPN_CAT;
        MarSetAnimation(anim_cat_crash_attack);
        self->facingLeft = MARIA.facingLeft;
        self->velocityX = FIX(4.0);
        self->posX.i.hi = MARIA.posX.i.hi;
        self->posY.i.hi = MARIA.posY.i.hi + 0x18;
        self->hitboxWidth = 0x10;
        self->hitboxHeight = 0x20;
        self->hitboxOffX = 0;
        self->hitboxOffY = 0;
        self->ext.mariaCat.unkB0 = 0;
        MarSetWeaponParams(
            self, 16, ELEMENT_CUT | ELEMENT_HOLY, 2, 16, 16, 1, 0);
        g_api.PlaySfx(SFX_ALUCARD_SWORD_SWISH);
        self->step = 1;
        break;
    case 1:
        self->posX.val += self->facingLeft ? -self->velocityX : self->velocityX;
        if (self->poseTimer < 0) {
            self->step = 2;
        }

        if (self->posX.i.hi < -16 || self->posX.i.hi > 272) {
            self->step = 2;
        }

        break;
    case 2:
        DestroyEntity(self);
        break;
    }
}

static AnimationFrame anim_doll_prepare[] = {
    POSE(3, 7, 0), POSE(3, 8, 0), POSE_LOOP(0)};
static AnimationFrame anim_doll_attack[] = {
    POSE(2, 1, 0), POSE(2, 2, 0), POSE(2, 3, 0), POSE(1, 4, 0), POSE(1, 5, 0),
    POSE(2, 6, 0), POSE(1, 5, 0), POSE(2, 4, 0), POSE_LOOP(0)};
static AnimationFrame anim_doll_stand[] = {POSE(1, 9, 0), POSE_LOOP(0)};
void EntityMariaDollAttack(Entity* self) {
    switch (self->step) {
    case 0:
        self->flags = FLAG_POS_CAMERA_LOCKED | FLAG_KEEP_ALIVE_OFFCAMERA |
                      FLAG_UNK_100000;
        self->unk5A = 0x59;
        self->zPriority = MARIA.zPriority - 8;
        self->palette = PAL_WPN_DOLL;
        self->animSet = ANIMSET_WPN_DOLL;
        MarSetAnimation(anim_doll_stand);
        self->facingLeft = MARIA.facingLeft;
        self->velocityX = 0;
        self->posX.i.hi = MARIA.posX.i.hi + (self->facingLeft ? -24 : 24);
        self->posY.i.hi = MARIA.posY.i.hi + 0x18;
        self->hitboxWidth = 0;
        self->hitboxHeight = 0;
        self->hitboxOffX = 0x20;
        self->hitboxOffY = 8;
        self->ext.mariaDoll.unkB0 = 0;
        MarSetWeaponParams(self, 64, ELEMENT_HOLY, 0, 16, 16, 1, 0);
        g_Maria.unk5C = 1;
        self->ext.mariaDoll.timer = 0;
        self->step = 1;
        MarCreateEntFactoryFromEntity(self, BP_DOLL_ACTIVATE, 0);
        break;
    case 1:
        if (self->ext.mariaDoll.timer > 10) {
            MarSetAnimation(anim_doll_prepare);
            self->step = 2;
            self->velocityX = FIX(3.25);
            self->ext.mariaDoll.timer = 0;
        }
        self->ext.mariaDoll.timer++;
        break;
    case 2:
        if (self->hitboxWidth < 0x10) {
            self->hitboxWidth += 2;
        } else {
            self->hitboxWidth = 0x10;
        }

        if (self->hitboxHeight < 0x20) {
            self->hitboxHeight += 4;
        } else {
            self->hitboxHeight = 0x20;
        }

        if (self->ext.mariaDoll.timer < 5) {
            self->posX.val +=
                self->facingLeft ? -self->velocityX : self->velocityX;
        }

        if (self->ext.mariaDoll.timer == 5) {
            self->velocityX = 0;
            MarSetAnimation(anim_doll_attack);
        }

        if ((self->ext.mariaDoll.timer % 6) == 0) {
            g_api.PlaySfx(SFX_WEAPON_SWISH_A);
        }

        self->ext.mariaDoll.timer++;
        if (self->ext.mariaDoll.timer > 65) {
            MarSetAnimation(anim_doll_stand);
            self->ext.mariaDoll.opacity = 128;
            self->ext.mariaDoll.ttl = 15;
            self->step = 3;
            self->hitboxState = 0;
        }
        break;
    case 3:
        if (self->ext.mariaDoll.ttl > 0) {
            self->ext.mariaDoll.ttl--;
        } else {
            self->ext.mariaDoll.opacity -= 8;
        }
        if (self->ext.mariaDoll.opacity <= 0) {
            SetOpacity(self, 0);
            self->step = 4;
            break;
        }
        SetOpacity(self, self->ext.mariaDoll.opacity);
        break;
    case 4:
        g_Maria.unk5C = 0;
        DestroyEntity(self);
        break;
    }
}

void EntityMariaDollActivate(Entity* self) {
    switch (self->step) {
    case 0:
        self->flags = FLAG_POS_CAMERA_LOCKED | FLAG_KEEP_ALIVE_OFFCAMERA |
                      FLAG_UNK_100000;
        self->unk5A = 0x59;
        self->zPriority = MARIA.zPriority - 8;
        self->palette = PAL_WPN_DOLL;
        self->animSet = ANIMSET_WPN_DOLL;
        MarSetAnimation(anim_doll_stand);
        self->ext.mariaDoll.timer = 0;
        self->ext.mariaDoll.opacity = 0;
        self->step = 2;
        self->posX.val = self->ext.mariaDoll.parent->posX.val;
        self->posY.val = self->ext.mariaDoll.parent->posY.val;
        self->ext.mariaDoll.opacity = 64;
        self->ext.mariaDoll.scale = 0x100;
        self->scaleX = self->ext.mariaDoll.scale;
        self->scaleY = self->ext.mariaDoll.scale;
        SetOpacity(self, 64);
        self->drawFlags |= ENTITY_SCALEX | ENTITY_SCALEY;
        break;
    case 2:
        self->ext.mariaDoll.timer++;
        if (self->ext.mariaDoll.timer > 10) {
            self->ext.mariaDoll.opacity = 128;
            self->step = 4;
            return;
        }
        self->ext.mariaDoll.opacity -= 2;
        self->ext.mariaDoll.scale += 8;
        SetOpacity(self, self->ext.mariaDoll.opacity);
        self->drawFlags |= ENTITY_SCALEX | ENTITY_SCALEY;
        // scaleX and scaleY are also used to scale horizontally and vertically
        self->scaleX = self->ext.mariaDoll.scale;
        self->scaleY = self->ext.mariaDoll.scale;
        break;
    case 4:
        DestroyEntity(self);
        break;
    }
}

static AnimationFrame anim_turtle[] = {POSE(1, 1, 0), POSE_LOOP(0)};
void EntityMariaTurtleAttack(Entity* self) {
    switch (self->step) {
    case 0:
        self->flags = FLAG_POS_CAMERA_LOCKED | FLAG_KEEP_ALIVE_OFFCAMERA |
                      FLAG_UNK_100000;
        self->unk5A = 0x50;
        self->zPriority = MARIA.zPriority - 8;
        self->palette = PAL_WPN_TURTLE;
        self->animSet = ANIMSET_WPN_TURTLE;
        MarSetAnimation(anim_turtle);
        self->facingLeft = MARIA.facingLeft;
        self->velocityX = 0;
        self->ext.mariaTurtleAttack.x = 0;
        self->posX.i.hi = MARIA.posX.i.hi + self->ext.mariaTurtleAttack.x;
        self->posY.i.hi = MARIA.posY.i.hi + 24;
        self->hitboxWidth = 24;
        self->hitboxHeight = 48;
        self->hitboxOffX = 0;
        self->hitboxOffY = 0;
        self->attack = 255;
        self->attackElement = ELEMENT_NONE;
        self->hitboxState = 5;
        self->flags |= FLAG_NOT_AN_ENEMY;
        self->nFramesInvincibility = 6;
        self->stunFrames = 0;
        self->hitEffect = 1;
        self->entityRoomIndex = 1;
        g_Maria.unk7A = 1;
        self->ext.mariaTurtleAttack.timer = 0;
        self->step++;
        break;
    case 1:
        self->posX.i.hi = MARIA.posX.i.hi + self->ext.mariaTurtleAttack.x;
        self->posY.i.hi = MARIA.posY.i.hi + 24;
        self->ext.mariaTurtleAttack.timer++;
        if (self->ext.mariaTurtleAttack.timer >= 180) {
            self->step++;
        }
        break;
    case 2:
        g_Maria.unk7A = 0;
        DestroyEntity(self);
        break;
    }
}

static AnimationFrame anim_turtle_crash_vortex[] = {
    POSE(1, 2, 0), POSE_LOOP(0)};
static AnimationFrame anim_turtle_crash[] = {
    POSE(19, 3, 0), POSE(19, 4, 0), POSE(19, 5, 0), POSE(19, 6, 0),
    POSE_LOOP(0)};
void EntityMariaTurtleCrash(Entity* self) {
    s32 x;

    switch (self->step) {
    case 0:
        self->flags = FLAG_UNK_100000 | FLAG_KEEP_ALIVE_OFFCAMERA |
                      FLAG_POS_CAMERA_LOCKED;
        self->unk5A = 0x50;
        self->zPriority = MARIA.zPriority - 6;
        self->palette = PAL_WPN_TURTLE;
        self->animSet = ANIMSET_WPN_TURTLE;
        MarSetAnimation(anim_turtle_crash);

        self->facingLeft = MARIA.facingLeft;
        if (MARIA.facingLeft) {
            x = -74;
        } else {
            x = 74;
        }

        self->posX.i.hi = MARIA.posX.i.hi + x;
        self->posY.i.hi = MARIA.posY.i.hi - 16;
        self->scaleX = 0;
        self->scaleY = 0;
        self->drawFlags |= ENTITY_SCALEX | ENTITY_SCALEY;
        g_Maria.unk28 = NULL;
#if defined(VERSION_PC)
        g_Maria.unk20 = (signed long long)self;
#else
        g_Maria.unk20 = (s32)self;
#endif
        g_Maria.unk24 = 0;
        self->ext.mariaTurtleCrash.timer = 0;
        self->ext.mariaTurtleCrash.timer2 = 0;
        g_Maria.unk2C = -1;
        self->step = 1;
        SpawnCrashSummon(3);
        SetOpacity(self, 0);
        break;
    case 1:
        if (g_Maria.unk5C == 1) {
            g_api.PlaySfx(SFX_VO_MAR_8F1 + MAR_SFX_OFFSET);
            MarCreateEntFactoryFromEntity(self, BP_TURTLE_CRASH_VORTEX, 0);
            self->step = 3;
        }
        break;
    case 3:
        self->ext.mariaTurtleCrash.timer2 += 16;
        if (self->ext.mariaTurtleCrash.timer2 >= 128) {
            SetOpacity(self, 0x80);
            self->step = 2;
            break;
        }

        SetOpacity(self, self->ext.mariaTurtleCrash.timer2);
        break;
    case 2:
        if (self->scaleX < 256) {
            self->scaleX += 16;
            self->scaleY += 16;
        } else {
            self->drawFlags &= ~(ENTITY_SCALEX | ENTITY_SCALEY);
        }

        if ((self->ext.mariaTurtleCrash.timer % 60) == 0) {
            g_api.PlaySfx(SFX_MAGIC_NOISE_SWEEP);
        }

        self->ext.mariaTurtleCrash.timer++;
        if (self->ext.mariaTurtleCrash.timer >= 0xFF) {
            self->step = 5;
        }
        break;
    case 5:
        if (self->scaleX > 0x80) {
            self->drawFlags |= ENTITY_SCALEX | ENTITY_SCALEY | ENTITY_ROTATE;
            self->scaleX -= 0x20;
            self->scaleY -= 0x20;
            self->rotate += 0xF78;
            break;
        }

        self->ext.mariaTurtleCrash.timer2 = 0x80;
        self->step = 4;
        break;
    case 4:
        self->ext.mariaTurtleCrash.timer2 -= 0x10;
        if (self->ext.mariaTurtleCrash.timer2 <= 0) {
            SetOpacity(self, 0);
            self->drawFlags |= ENTITY_ROTATE | ENTITY_SCALEY | ENTITY_SCALEX;
            self->step = 6;
            func_pspeu_092BFEB0(g_Maria.unk20);
            g_Maria.unk2C = 0xB4;
            break;
        }
        SetOpacity(self, self->ext.mariaTurtleCrash.timer2);
        self->drawFlags |= ENTITY_SCALEX | ENTITY_SCALEY | ENTITY_ROTATE;
        break;
    case 6:
        if (g_Maria.unk28 == NULL) {
            self->step = 7;
            self->ext.mariaTurtleCrash.timer3 = 0;
            break;
        }

        if (g_Maria.unk2C == 0) {
            g_api.PlaySfx(SFX_HEALTH_PICKUP);
            g_Maria.unk56 = 1;
            g_Maria.unk58 = g_Maria.unk24;
            self->step = 7;
            self->ext.mariaTurtleCrash.timer3 = 0;
            break;
        }

        g_Maria.unk2C--;
        break;
    case 7:
        self->ext.mariaTurtleCrash.timer3++;
        if (self->ext.mariaTurtleCrash.timer3 > 60) {
            g_Maria.unk28 = NULL;
            g_Maria.unk20 = 0;
            g_Maria.unk5C = 0;
            DestroyEntity(self);
        }
        break;
    }
}

void EntityMariaTurtleCrashVortex(Entity* self) {
    Entity* entity;
    s32 x;

    entity = (Entity*)g_Maria.unk20;
    switch (self->step) {
    case 0:
        self->flags = FLAG_UNK_100000 | FLAG_KEEP_ALIVE_OFFCAMERA |
                      FLAG_POS_CAMERA_LOCKED;
        self->unk5A = 0x50;
        self->zPriority = MARIA.zPriority - 7;
        self->palette = PAL_WPN_TURTLE;
        self->animSet = ANIMSET_WPN_TURTLE;
        MarSetAnimation(anim_turtle_crash_vortex);
        self->facingLeft = 0;
        self->velocityX = 0;
        self->ext.mariaTurtleVortex.rotation = 0xF0;
        if (entity == NULL) {
            if (MARIA.facingLeft) {
                x = -74;
            } else {
                x = 74;
            }
            self->posX.i.hi = MARIA.posX.i.hi + x;
            self->posY.i.hi = MARIA.posY.i.hi - 0x10;
        } else {
            self->posX.i.hi = entity->posX.i.hi;
            self->posY.i.hi = entity->posY.i.hi;
        }
        self->scaleX = 0;
        self->scaleY = 0;
        self->drawFlags |= ENTITY_SCALEX | ENTITY_SCALEY;
        self->blendMode |= BLEND_TRANSP;
        self->drawFlags |= ENTITY_ROTATE | ENTITY_OPACITY;
        self->rotate = 0;
        self->opacity = 0x80;
        self->hitboxWidth = 48;
        self->hitboxHeight = 48;
        self->hitboxOffX = 0;
        self->hitboxOffY = 0;
        self->ext.mariaTurtleVortex.unkB0 = 0;
        MarSetWeaponParams(
            self, 5, ELEMENT_WATER | ELEMENT_HOLY, 2, 32, 0, 2, 0);
        self->ext.mariaTurtleVortex.hitboxState = self->hitboxState;
        self->hitboxState = 0;
        self->ext.mariaTurtleVortex.timer = 0;
        self->step = 1;
        self->rotate +=
            0x1000 - (0x1000 / self->ext.mariaTurtleVortex.rotation);
        break;
    case 1:
        if (self->scaleX < 256) {
            self->scaleX += 16;
            self->scaleY += 16;
        } else {
            self->hitboxState = self->ext.mariaTurtleVortex.hitboxState;
            self->drawFlags &= ~(ENTITY_SCALEX | ENTITY_SCALEY);
        }
        self->ext.mariaTurtleVortex.timer++;
        if (self->ext.mariaTurtleVortex.timer >= 240) {
            self->hitboxState = 0;
            self->step = 2;
        }

        if (self->ext.mariaTurtleVortex.timer % 8 == 0) {
            self->ext.mariaTurtleVortex.rotation -= 5;
        }
        self->rotate +=
            0x1000 - (0x1000 / self->ext.mariaTurtleVortex.rotation);
        break;
    case 2:
        if (self->ext.mariaTurtleVortex.rotation >= 65) {
            self->ext.mariaTurtleVortex.rotation -= 5;
        } else {
            self->step = 3;
        }
        self->rotate +=
            0x1000 - (0x1000 / self->ext.mariaTurtleVortex.rotation);
        break;
    case 3:
        if (self->scaleX > 0) {
            self->scaleX -= 8;
            self->scaleY -= 8;
            self->drawFlags |= ENTITY_SCALEX | ENTITY_SCALEY;
        } else {
            self->step = 4;
        }
        self->rotate +=
            0x1000 - (0x1000 / self->ext.mariaTurtleVortex.rotation);
        break;
    case 4:
        DestroyEntity(self);
        break;
    }
}
