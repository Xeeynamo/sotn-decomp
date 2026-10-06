// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rcen.h"

extern EInit g_EInitInteractable;
extern EInit g_EInitShaft;
extern EInit g_EInitShaftCrystalBall;
extern EInit g_EInitShaftOrb;
extern EInit g_EInitShaftFlame;
extern EInit g_EInitShaftLightningHitbox;
extern s32 g_CutsceneFlags;

#ifdef VERSION_PSP
extern s32 E_ID(CUTSCENE_DIALOGUE);
extern s32 E_ID(SHAFT_MERIDIAN_RINGS);
extern s32 E_ID(SHAFT_CRYSTAL_BALL);
extern s32 E_ID(CUTSCENE_SHAFT);
extern s32 E_ID(SHAFT_ATTACK_ORB);
extern s32 E_ID(SHAFT_FLAME_TRAIL);
extern s32 E_ID(SHAFT_FLAME_PILLAR);
extern s32 E_ID(SHAFT_LIGHTNING);
extern s32 E_ID(SHAFT_LIGHTNING_HITBOX);
extern s32 E_ID(SHAFT_ORBIT_ORB);
extern s32 E_ID(SHAFT_DEATH_FLAMES);
#endif

// Flags to control when cutscenes begin/end and fight begins/ends
s32 g_RcenShaftFlags = 0;
static s32 attack_step = 0;

// A subtle pulse overlayed on the orb
static AnimateEntityFrame anim_unused_orb_pulse[] = {
    {0x09, 0x24}, {0x08, 0x25}, {0x07, 0x26}, {0x06, 0x27}, {0x05, 0x28},
    {0x04, 0x29}, {0x03, 0x2A}, {0x15, 0x2B}, POSE_END};
static AnimateEntityFrame anim_electric_charge_orb[] = {
    {0x23, 0x2B}, {0x02, 0x2C}, {0x02, 0x2D}, {0x02, 0x2E}, {0x02, 0x2F},
    {0x02, 0x30}, {0x02, 0x31}, {0x02, 0x32}, {0x02, 0x33}, {0x04, 0x34},
    {0x04, 0x35}, {0x03, 0x36}, {0x03, 0x37}, {0x02, 0x38}, {0x02, 0x39},
    {0x02, 0x3A}, {0x02, 0x3B}, {0x01, 0x3C}, {0x06, 0x2B}, {0x01, 0x3D},
    POSE_END,
};
// An intense vertical beam of electricity eminating from the orb
// This looks much like one of Shaft's attacks in Rondo of Blood.
static AnimateEntityFrame anim_unused_electric_orb_beam[] = {
    {0x01, 0x44}, {0x01, 0x45}, {0x01, 0x46},
    {0x01, 0x47}, {0x00, 0x00}, POSE_LOOP(0),
};
static AnimateEntityFrame anim_flame_charge_orb[] = {
    {0x22, 0x2B}, {0x04, 0x48}, {0x03, 0x49}, {0x02, 0x4A},
    {0x02, 0x4B}, {0x02, 0x4C}, POSE_END};
// A fully animated flaming orb - note this differs from the final build which
// uses a flame trail entity overlayed over the orb.
// This looks much like Shaft's orbs in Rondo of Blood.
static AnimateEntityFrame anim_unused_flaming_orb_lg[] = {
    {0x02, 0x4D}, {0x02, 0x4E}, {0x02, 0x4F}, {0x02, 0x50}, {0x02, 0x51},
    {0x02, 0x52}, {0x02, 0x53}, {0x02, 0x54}, POSE_LOOP(0),
};
static AnimateEntityFrame anim_unused_flaming_orb_sm[] = {
    {0x02, 0x55}, {0x02, 0x56}, {0x02, 0x57}, {0x02, 0x58}, {0x02, 0x59},
    {0x02, 0x5A}, {0x02, 0x5B}, {0x02, 0x5C}, POSE_LOOP(0),
};
static AnimateEntityFrame anim_spawn_orb_red[] = {
    {0x01, 0x5D}, {0x01, 0x5E}, {0x01, 0x5F}, {0x01, 0x60}, {0x01, 0x5D},
    {0x01, 0x5E}, {0x01, 0x5F}, {0x01, 0x60}, {0x01, 0x5D}, {0x01, 0x5E},
    {0x01, 0x5F}, {0x01, 0x60}, {0x01, 0x5D}, {0x01, 0x5E}, {0x01, 0x5F},
    {0x01, 0x60}, {0x04, 0x61}, {0x03, 0x62}, {0x03, 0x63}, {0x02, 0x64},
    {0x02, 0x65}, {0x02, 0x66}, {0x01, 0x67}, {0x24, 0x2B}, POSE_END,
};
static AnimateEntityFrame anim_spawn_orb_blue[] = {
    {0x01, 0x68}, {0x01, 0x69}, {0x01, 0x6A}, {0x01, 0x6B}, {0x01, 0x68},
    {0x01, 0x69}, {0x01, 0x6A}, {0x01, 0x6B}, {0x01, 0x68}, {0x01, 0x69},
    {0x01, 0x6A}, {0x01, 0x6B}, {0x01, 0x68}, {0x01, 0x69}, {0x01, 0x6A},
    {0x01, 0x6B}, {0x04, 0x6C}, {0x03, 0x6D}, {0x03, 0x6E}, {0x02, 0x6F},
    {0x02, 0x70}, {0x02, 0x71}, {0x01, 0x72}, {0x24, 0x2B}, POSE_END,
};
static AnimateEntityFrame anim_bouncy_charge_red[] = {
    {0x02, 0x67}, {0x02, 0x66}, {0x02, 0x65}, {0x02, 0x64},
    {0x02, 0x63}, {0x02, 0x62}, {0x02, 0x61}, POSE_END,
};
// Similar to the bouncy / spawn charge animation but teardrop shaped
static AnimateEntityFrame anim_unused_orb_teardrop_red[] = {
    {0x01, 0x73}, {0x01, 0x74}, {0x01, 0x75}, {0x01, 0x76}, POSE_LOOP(0),
};
static AnimateEntityFrame anim_bouncy_charge_blue[] = {
    {0x02, 0x72}, {0x02, 0x71}, {0x02, 0x70}, {0x02, 0x6F},
    {0x02, 0x6E}, {0x02, 0x6D}, {0x02, 0x6C}, POSE_END,
};
// Similar to the bouncy / spawn charge animation but teardrop shaped
static AnimateEntityFrame anim_unused_orb_teardrop_blue[] = {
    {0x01, 0x77}, {0x01, 0x78}, {0x01, 0x79}, {0x01, 0x7A}, POSE_LOOP(0),
};
static AnimateEntityFrame anim_bouncy_orb[] = {
    {0x01, 0x7F}, {0x01, 0x80}, {0x01, 0x81}, {0x01, 0x82}, POSE_LOOP(0),
};
// A subtle sparkle effect - note, nothing else visible here (orb/crystal ball)
static AnimateEntityFrame anim_unused_sparkle[] = {
    {0x03, 0x7E}, {0x03, 0x7D}, {0x03, 0x7C}, {0x03, 0x7D}, POSE_END,
};
static AnimateEntityFrame anim_crystal_ball_color_cycle[] = {
    {0x04, 0x01}, {0x04, 0x02}, {0x04, 0x03}, {0x04, 0x04}, {0x04, 0x05},
    {0x04, 0x06}, {0x04, 0x07}, {0x04, 0x08}, {0x04, 0x09}, {0x04, 0x0A},
    {0x04, 0x0B}, {0x04, 0x0C}, {0x04, 0x0B}, {0x04, 0x0A}, {0x04, 0x09},
    {0x04, 0x08}, {0x04, 0x07}, {0x04, 0x06}, {0x04, 0x05}, {0x04, 0x04},
    {0x04, 0x03}, {0x04, 0x02}, {0x04, 0x01}, POSE_LOOP(0),
};
static AnimateEntityFrame anim_crystal_ball_crack[] = {
    {0x03, 0x0C}, {0x03, 0x08}, {0x03, 0x0D}, {0x03, 0x0E}, {0x03, 0x0F},
    {0x03, 0x10}, {0x03, 0x11}, {0x03, 0x12}, {0x03, 0x13}, {0x03, 0x14},
    {0x03, 0x15}, {0x03, 0x16}, {0x03, 0x17}, {0x03, 0x18}, {0x03, 0x19},
    {0x03, 0x1A}, {0x03, 0x1B}, {0x03, 0x1C}, {0x03, 0x1D}, {0x03, 0x1E},
    {0x03, 0x1F}, {0x03, 0x20}, {0x03, 0x21}, {0x03, 0x22}, {0x03, 0x21},
    {0x03, 0x22}, {0x03, 0x21}, {0x03, 0x22}, {0x03, 0x21}, {0x03, 0x22},
    {0x03, 0x21}, {0x03, 0x22}, POSE_END,
};
static AnimateEntityFrame anim_shaft_float[] = {
    {0x24, 0x23}, {0x06, 0x7B}, {0x05, 0x83}, {0x05, 0x84}, {0x04, 0x85},
    {0x03, 0x86}, {0x02, 0x87}, {0x02, 0x88}, {0x02, 0x89}, {0x02, 0x8A},
    {0x02, 0x87}, {0x02, 0x88}, {0x02, 0x89}, {0x02, 0x8A}, {0x02, 0x87},
    {0x02, 0x88}, {0x02, 0x89}, {0x02, 0x8A}, {0x02, 0x87}, {0x02, 0x88},
    {0x02, 0x89}, {0x02, 0x8A}, POSE_END,
};
static AnimateEntityFrame anim_flame_pillar[] = {
    {0x03, 0x01}, {0x03, 0x02}, {0x03, 0x03}, {0x03, 0x04}, {0x03, 0x05},
    {0x03, 0x06}, {0x03, 0x07}, {0x03, 0x08}, {0x03, 0x09}, {0x03, 0x0A},
    {0x03, 0x0B}, {0x03, 0x0C}, {0x03, 0x0D}, POSE_END,
};
static AnimateEntityFrame anim_flame_trail[] = {
    {0x02, 0x01}, {0x02, 0x02}, {0x02, 0x03}, {0x02, 0x04}, {0x02, 0x05},
    {0x02, 0x06}, {0x02, 0x07}, {0x02, 0x08}, {0x02, 0x09}, {0x02, 0x0A},
    {0x02, 0x0B}, {0x02, 0x0C}, {0x02, 0x0D}, POSE_END,
};

typedef enum {
    ATTACK_END = 0,
    SPAWN = 1,
    ATTACK_IDLE = 2,
    ATTACK_FLAME = 3,
    ATTACK_ELECTRIC = 4,
    ATTACK_BOUNCE = 5,
    DEATH = 6
} ShaftAttackOrbStep;

// nb. unclear why there's 6 elements here.
// Code checks if it's > 2 and resets back to 0th element so [3],[4],[5] never
// get used.
static s32 attack_steps[] = {
    ATTACK_FLAME, ATTACK_BOUNCE, ATTACK_ELECTRIC,
    ATTACK_FLAME, ATTACK_FLAME,  ATTACK_FLAME,
};

// Similar to the one in st_common
static s16 _LimitAngleChange(s16 delta, s16 base, s16 target) {
    s16 diff;
    s16 ret;

    base &= 0xFFF;
    diff = target - base;
    ret = diff;

    if (diff > ROT(180)) {
        ret = diff - ROT(360);
    }

    if (diff < ROT(-180)) {
        ret = diff + ROT(360);
    }

    // If we exceed the delta, then return a value which differs in the right
    // direction by precisely that delta.
    if (abs(ret) > delta) {
        if (diff < 0) {
            ret = base - delta;
        } else {
            ret = base + delta;
        }
        return ret;
    }

    // If we're not over the delta, then we can directly adopt the target angle.
    return target;
}

// Handles the volume and pan of the "bubbling" effect
// which plays as you approach the inner chamber.
static void PlayProximitySfx(s16 sfxId) {
    s32 yOffset;
    s16 vol;
    s16 pan;
    s32 xOffset;

    xOffset = g_CurrentEntity->posX.i.hi - 128;
    pan = (abs(xOffset) - 0x20) >> 5;
    if (pan > 8) {
        pan = 8;
    } else if (pan < 0) {
        pan = 0;
    }
    if (xOffset < 0) {
        pan = -pan;
    }

    vol = abs(xOffset) - 0x60;
    yOffset = abs(g_CurrentEntity->posY.i.hi - 128) - 112;
    if (yOffset > 0) {
        vol += yOffset;
    }
    if (vol < 0) {
        vol = 0;
    }
    vol = 0x40 - (vol >> 1);
    if (vol > 0) {
        g_api.PlaySfxVolPan(sfxId, vol, pan);
    }
}

void EntityShaft(Entity* self) {
    typedef enum {
        INIT = 0,
        SETUP = 1,
        MOVE = 2,
        ATTACK = 3,
        DEATH = 4,
    } ShaftStep;

    Entity* entity;
    s32 i;
    s16 angle;
    s32 posX;
    s32 posY;
    s32 var_s5;
    s32 arrivedAtCenter;

    if (self->flags & FLAG_DEAD) {
        if (self->step != DEATH) {
            SetStep(DEATH);
        }
    }

    switch (self->step) {
    case INIT:
        InitializeEntity(g_EInitShaft);
        self->drawFlags = ENTITY_OPACITY;
        self->opacity = 0;
        self->animCurFrame = 0x8B;
        self->ext.rcenShaft.angle = ROT(-90);
        self->hitboxState = 0;

        entity = self + 1;
        CreateEntityFromCurrentEntity(E_ID(SHAFT_CRYSTAL_BALL), entity);
        entity->zPriority = self->zPriority + 1;

        // The orbiting rings which surround the ball
        // nb. these sit in another segment later on in the overlay, unclear
        // why.
        entity = self + 2;
        CreateEntityFromCurrentEntity(E_ID(SHAFT_MERIDIAN_RINGS), entity);
        entity->zPriority = self->zPriority;

        entity = self + 14;
        CreateEntityFromCurrentEntity(E_ID(CUTSCENE_SHAFT), entity);
        entity->zPriority = self->zPriority + 2;
        // Cutscene Shaft spawns in the bottom right of the chamber
        entity->posX.i.hi = 0x1C0 - g_Tilemap.scrollX.i.hi;
        entity->posY.i.hi = 0x1C0 - g_Tilemap.scrollY.i.hi;

        SetStep(SETUP);
        // fallthrough
    case SETUP:
        switch (self->step_s) {
        case 0:
            if (g_CastleFlags[SHAFT_FIGHT_CS_UNK1] ||
                g_PlayableCharacter != PLAYER_ALUCARD ||
                g_DemoMode != Demo_None) {
                if (!(GetDistanceToPlayerX() < 0x30 &&
                      GetDistanceToPlayerY() < 0x40)) {
                    break;
                }
            } else if (!(g_CutsceneFlags & 2)) {
                break;
            }

            // Cutscene begins
            g_RcenShaftFlags |= 1;
            self->step_s++;
            break;
        case 1:
            if (g_RcenShaftFlags & 2) {
                // Fight begins
                stopMusicFlag = 1;
                currentMusicId = MU_DEATH_BALLAD;
                self->step_s++;
            }
            break;
        case 2:
            if (g_api.func_80131F68() == 0) {
                stopMusicFlag = 0;
                g_api.PlaySfx(currentMusicId);
                self->step_s++;
            }
            break;
        case 3:
            // Fade in from silhouette
            self->opacity += 4;
            if (self->opacity > 0x80) {
                self->drawFlags = ENTITY_DEFAULT;
                self->hitboxState = 3;

                // Spawn in the two "attack" orbs. These are capable of
                // launching a few different types of attacks such as the flame
                // columns or electricity.

                // Red attack orb
                entity = self + 3;
                CreateEntityFromCurrentEntity(E_ID(SHAFT_ATTACK_ORB), entity);
                entity->zPriority = self->zPriority + 8;
                entity->params = 0;
                entity->posX.i.hi = 0x140 - g_Tilemap.scrollX.i.hi;
                entity->posY.i.hi = 0x140;
                entity->ext.rcenShaft.shaftEntity = self;

                // Blue attack orb
                entity = self + 4;
                CreateEntityFromCurrentEntity(E_ID(SHAFT_ATTACK_ORB), entity);
                entity->zPriority = self->zPriority + 8;
                entity->params = 1;
                entity->posX.i.hi = 0x1C0 - g_Tilemap.scrollX.i.hi;
                entity->posY.i.hi = 0x140;
                entity->ext.rcenShaft.shaftEntity = self;

                // Spawn in 4 orbs which orbit the main crystal ball
                // These function as both an obstacle to dodge, and also
                // block attack damge that hit them (though they are not very
                // wide so longer weapons will still penetrate)
                for (entity = self + 5, i = 0; i < 4; i++, entity++) {
                    CreateEntityFromCurrentEntity(
                        E_ID(SHAFT_ORBIT_ORB), entity);
                    entity->zPriority = self->zPriority - 4;
                    entity->ext.rcenShaft.shaftEntity = self;
                    // Spawn in off the bottom of the screen at a random X-coord
                    // After the initialisation timer finishes, they fly up from
                    // the bottom
                    entity->posY.i.hi = 0x140;
                    entity->posX.i.hi += (0x40 - (Random() & 0x7F));
                }

                self->hitboxState = 3;
                g_api.PlaySfx(SFX_SHAFT_ATTACK_DEMONIC_BLESSING);
                SetStep(MOVE);
            }
            break;
        }
        break;
    case MOVE:
        if (!self->step_s) {
            self->ext.rcenShaft.timer = 0x100;
            self->step_s++;
        }
        MoveEntity();
        entity = &PLAYER;
        angle = -(entity->posX.i.hi / 2) * 0x10;
        posX = (rcos(angle) * 0x90) >> 0xC;
        posY = (rsin(angle) * 0x90) >> 0xC;
        posX += entity->posX.i.hi;
        posY += entity->posY.i.hi;
        posX -= self->posX.i.hi;
        posY -= self->posY.i.hi;
        angle = ratan2(posY, posX);
        angle = _LimitAngleChange(0x20, self->ext.rcenShaft.angle, angle);
        self->velocityX = (rcos(angle) * FIX(1.75)) >> 0xC;
        self->velocityY = (rsin(angle) * FIX(1.75)) >> 0xC;
        self->ext.rcenShaft.angle = angle;
        if (!--self->ext.rcenShaft.timer) {
            SetStep(ATTACK);
        }
        break;
    case ATTACK:
        switch (self->step_s) {
        case 0:
            self->ext.rcenShaft.timer = 0x20;
            self->step_s++;
            // fallthrough
        case 1:
            MoveEntity();
            self->velocityX -= self->velocityX >> 4;
            self->velocityY -= self->velocityY >> 4;
            if (!--self->ext.rcenShaft.timer) {
                self->step_s++;
            }
            break;
        case 2:
            attack_step = attack_steps[self->ext.rcenShaft.attackIdx];
            self->ext.rcenShaft.attackIdx++;
            if (self->ext.rcenShaft.attackIdx > 2) {
                self->ext.rcenShaft.attackIdx = 0;
            }

            self->ext.rcenShaft.timer = 8;
            if (attack_step == ATTACK_ELECTRIC) {
                self->ext.rcenShaft.timer = 0x200;
            }
            self->step_s++;
            // fallthrough
        case 3:
            if (!--self->ext.rcenShaft.timer) {
                attack_step = ATTACK_END;
                SetStep(MOVE);
            }
            break;
        }
        break;
    case DEATH:
        switch (self->step_s) {
        case 0:
            // Play the post-fight cutscene
            entity = &g_Entities[200];
            CreateEntityFromCurrentEntity(E_ID(CUTSCENE_DIALOGUE), entity);
            entity->params = 1;
            entity->flags = FLAG_UNK_10000;
            self->palette = 0x200;
            self->step_s++;
            break;
        case 1:
            if (g_CastleFlags[SHAFT_FIGHT_CS_UNK1] ||
                g_PlayableCharacter != PLAYER_ALUCARD ||
                g_DemoMode != Demo_None || (g_CutsceneFlags & 0x100)) {
                g_RcenShaftFlags |= 4;
                self->hitboxState = 0;
                self->drawFlags = ENTITY_OPACITY;
                self->opacity = 0x80;
                self->step_s++;
            } else {
                self->palette = 0x200;
                break;
            }
            // Fallthrough
        case 2:
            // Return to the centre of the room
            MoveEntity();
            posX = 0x80 - self->posX.i.hi;
            posY = 0x80 - self->posY.i.hi;
            angle = ratan2(posY, posX);
            self->velocityX = rcos(angle) * 0xC;
            self->velocityY = rsin(angle) * 0xC;
            var_s5 = SquareRoot0((posX * posX) + (posY * posY));
            if (var_s5 < 4) {
                self->velocityX = 0;
                self->velocityY = 0;
                arrivedAtCenter = true;
            } else {
                arrivedAtCenter = false;
            }

            var_s5 = self->opacity;
            var_s5--;
            if (var_s5 < 0) {
                var_s5 = 0;
            }
            self->opacity = var_s5;

            if (var_s5 == 0 && arrivedAtCenter) {
                self->ext.rcenShaft.timer = 0x60;
                g_api.PlaySfx(SFX_SHAFT_DEATH);
                self->step_s++;
            }
            break;
        case 3:
            for (i = 0; i < 2; i++) {
                entity = AllocEntity(&g_Entities[96], &g_Entities[256]);
                if (entity != NULL) {
                    CreateEntityFromEntity(
                        E_ID(SHAFT_DEATH_FLAMES), self, entity);
                    entity->params = 2;
                    entity->zPriority = self->zPriority + 0x10;
                }
            }

            if (!--self->ext.rcenShaft.timer) {
                self->ext.rcenShaft.timer = 0x20;
                self->animCurFrame = 0;
                g_api.PlaySfx(SFX_FIREBALL_SHOT_A);
                g_RcenShaftFlags |= 8;
                self->step_s++;
            }
            break;
        case 4:
            if (!(self->ext.rcenShaft.timer & 1)) {
                entity = AllocEntity(&g_Entities[96], &g_Entities[256]);
                if (entity != NULL) {
                    CreateEntityFromEntity(
                        E_ID(SHAFT_DEATH_FLAMES), self, entity);
                    entity->params = 3;
                    entity->zPriority = self->zPriority + 0x10;
                }
            }

            if (!--self->ext.rcenShaft.timer) {
                self->step_s++;
            }
            break;
        }

        break;
    case 0xFF:
#include "../pad2_anim_debug.h"
    }

    posX = self->posX.i.hi + g_Tilemap.scrollX.i.hi;
    posY = self->posY.i.hi + g_Tilemap.scrollY.i.hi;
    if (self->velocityX < 0) {
        if (posX < 0x128) {
            self->posX.i.hi = 0x128 - g_Tilemap.scrollX.i.hi;
        }
    } else if (posX > 0x1D8) {
        self->posX.i.hi = 0x1D8 - g_Tilemap.scrollX.i.hi;
    }

    if (self->velocityY < 0) {
        if (posY < 0x138) {
            self->posY.i.hi = 0x138 - g_Tilemap.scrollY.i.hi;
        }
    } else if (posY > 0x1CB) {
        self->posY.i.hi = 0x1CB - g_Tilemap.scrollY.i.hi;
    }
}

void EntityShaftCrystalBall(Entity* self) {
    Entity* shaftEntity;

    // When the fight is over, crack the crystal ball and start the death
    // sequence
    if (g_RcenShaftFlags & 4) {
        if (self->step != 2) {
            SetStep(2);
        }
    }

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitShaftCrystalBall);
        self->blendMode = BLEND_ADD | BLEND_TRANSP;
        // fallthrough
    case 1:
        AnimateEntity(anim_crystal_ball_color_cycle, self);
        shaftEntity = self - 1;
        self->posX.i.hi = shaftEntity->posX.i.hi;
        self->posY.i.hi = shaftEntity->posY.i.hi;
        if (!(g_Timer & 0x7F)) {
            PlayProximitySfx(SFX_LOW_SYNTH_BUBBLES);
        }
        break;

    case 2:
        AnimateEntity(anim_crystal_ball_crack, self);
        if (!self->poseTimer && self->pose == 0xA) {
            PlaySfxPositional(SFX_SHAFT_ORB_BREAK);
        }
        shaftEntity = self - 1;
        self->posX.i.hi = shaftEntity->posX.i.hi;
        self->posY.i.hi = shaftEntity->posY.i.hi;
        if (g_RcenShaftFlags & 8) {
            DestroyEntity(self);
        }
        break;
    }
}

// The little talking guy that appears in the bottom right during the cutscene.
// After the cutscene he floats up into his crystal ball and the fight begins
void EntityCutsceneShaft(Entity* self) {
    Entity* shaftEntity;
    s32 var_s1;
    s32 posX;
    s32 posY;
    s16 angle;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitShaftCrystalBall);
        self->blendMode = BLEND_ADD | BLEND_TRANSP;
        self->drawFlags = ENTITY_OPACITY;
        self->opacity = 0x60;
        self->animCurFrame = 0x23;
        // fallthrough
    case 1:
        if (g_RcenShaftFlags & 1) {
            // Once the cutscene is done float up into your ball
            self->step++;
        }
        break;
    case 2:
        if (!AnimateEntity(anim_shaft_float, self)) {
            SetStep(3);
        }
        break;
    case 3:
        // Target the main Shaft entity in the centre of
        // the room and float towards it
        MoveEntity();
        shaftEntity = self - 14;
        posX = shaftEntity->posX.i.hi - self->posX.i.hi;
        posY = shaftEntity->posY.i.hi - self->posY.i.hi;
        angle = ratan2(posY, posX);
        self->velocityX = (rcos(angle) << 0x10) >> 0xC;
        self->velocityY = (rsin(angle) << 0x10) >> 0xC;
        var_s1 = SquareRoot0((posX * posX) + (posY * posY));
        if (var_s1 < 2) {
            self->posX.i.hi = shaftEntity->posX.i.hi;
            self->posY.i.hi = shaftEntity->posY.i.hi;
            self->step++;
        }
        break;
    case 4:
        // Fade out, and commence the fight
        var_s1 = self->opacity;
        var_s1 -= 8;
        if (var_s1 < 0) {
            g_RcenShaftFlags |= 2;
            DestroyEntity(self);
            break;
        }

        self->opacity = var_s1;
        break;
    }
}

// Params
// 0 = Red attack orb
// 1 = Blue attack orb
void EntityShaftAttackOrb(Entity* self) {
    Entity* entity;
    EnemyDef* enemyDef;
    s32 posX;
    s32 posY;
    s32 result;
    s16 angle;
    s32 i;

    if (g_RcenShaftFlags & 4) {
        if (self->step != DEATH) {
            SetStep(DEATH);
        }
    }

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitShaftOrb);
        self->hitboxState = 0;
        SetStep(SPAWN);
        // fallthrough
    case SPAWN:
        switch (self->step_s) {
        case 0:
            self->velocityY = FIX(-6.0);
            if (self->params) {
                self->animCurFrame = 0x68;
            } else {
                self->animCurFrame = 0x5D;
            }
            PlaySfxPositional(SFX_VENUS_WEED_CHARGE_ATTACK);
            self->step_s++;
            // fallthrough
        case 1:
            MoveEntity();
            if (self->posY.i.hi < 0xC0) {
                self->step_s++;
            }
            break;
        case 2:
            MoveEntity();
            self->velocityY -= (self->velocityY >> 4);
            if (self->params) {
                result = AnimateEntity(anim_spawn_orb_blue, self);
            } else {
                result = AnimateEntity(anim_spawn_orb_red, self);
            }

            if (!result) {
                self->hitboxState = 2;
                SetStep(ATTACK_IDLE);
            }
            break;
        }

        break;
    case ATTACK_IDLE:
        if (!self->step_s) {
            self->ext.rcenShaft.swayAngle = 0;
            if (self->params) {
                self->ext.rcenShaft.angle = ROT(180);
            } else {
                self->ext.rcenShaft.angle = 0;
            }
            self->animCurFrame = 0x2B;
            self->step_s++;
        }
        entity = self->ext.rcenShaft.shaftEntity;
        posX = entity->posX.i.hi;
        posY = entity->posY.i.hi - 0x20;
        // The blue and red orbs add/subtract the sway to mirror each other's
        // movement
        if (self->params) {
            posX += ((rcos(self->ext.rcenShaft.swayAngle) * 0x30) >> 0xC);
        } else {
            posX -= ((rcos(self->ext.rcenShaft.swayAngle) * 0x30) >> 0xC);
        }
        posX -= self->posX.i.hi;
        posY -= self->posY.i.hi;
        angle = ratan2(posY, posX);
        angle = _LimitAngleChange(0x30, self->ext.rcenShaft.angle, angle);
        self->velocityX = (rcos(angle) * FIX(2.5)) >> 0xC;
        self->velocityY = (rsin(angle) * FIX(2.5)) >> 0xC;
        self->ext.rcenShaft.angle = angle;
        MoveEntity();
        self->ext.rcenShaft.swayAngle += 0x40;
        if (attack_step != ATTACK_END) {
            SetStep(attack_step);
        }
        break;
    case ATTACK_FLAME:
        // Flame orbs
        switch (self->step_s) {
        case 0:
            if (!AnimateEntity(anim_flame_charge_orb, self)) {
                g_api.PlaySfx(SFX_SHAFT_ATTACK_A);
                self->step_s++;
            }
            break;
        case 1:
            if (self->params) {
                entity = self - 1;
            } else {
                entity = self + 1;
            }

            if (self->posY.i.hi > entity->posY.i.hi) {
                result = true;
            } else {
                result = false;
            }

            entity = &PLAYER;
            posX = entity->posX.i.hi;
            posY = entity->posY.i.hi;
            if (result) {
                posY -= 0x28;
            } else {
                posY += 0x28;
            }

            posX -= self->posX.i.hi;
            posY -= self->posY.i.hi;
            angle = ratan2(posY, posX);
            self->ext.rcenShaft.angle = angle;
            self->velocityX = (rcos(angle) * FIX(6)) >> 0xC;
            self->velocityY = (rsin(angle) * FIX(6)) >> 0xC;
            self->hitboxState = 3;
            self->step_s++;
            // fallthrough
        case 2:
            if (!(g_Timer & 7)) {
                entity = AllocEntity(&g_Entities[96], &g_Entities[112]);
                if (entity != NULL) {
                    CreateEntityFromEntity(
                        E_ID(SHAFT_FLAME_TRAIL), self, entity);
                    entity->ext.rcenShaft.angle =
                        self->ext.rcenShaft.angle + ROT(180);
                    entity->ext.rcenShaft.shaftEntity = self;
                    entity->zPriority = self->zPriority + 1;
                }
            }

            MoveEntity();
            posX = self->posX.i.hi + g_Tilemap.scrollX.i.hi;
            posY = self->posY.i.hi + g_Tilemap.scrollY.i.hi;
            result = 0;
            if (self->velocityX > 0) {
                if (posX > 0x1E8) {
                    self->posX.i.hi = 0x1E8 - g_Tilemap.scrollX.i.hi;
                    self->ext.rcenShaft.angle = ROT(180);
                    result = true;
                }
            } else if (posX < 0x118) {
                self->posX.i.hi = 0x118 - g_Tilemap.scrollX.i.hi;
                self->ext.rcenShaft.angle = 0;
                result = true;
            }

            if (self->velocityY > 0) {
                if (posY > 0x1D8) {
                    self->posY.i.hi = 0x1D8 - g_Tilemap.scrollY.i.hi;
                    self->ext.rcenShaft.angle = ROT(270);
                    result = true;
                }
            } else if (posY < 0x128) {
                self->posY.i.hi = 0x128 - g_Tilemap.scrollY.i.hi;
                self->ext.rcenShaft.angle = ROT(90);
                result = true;
            }

            if (result) {
                self->step_s++;
            }
            break;
        case 3:
            self->ext.rcenShaft.timer = 0x28;
            PlaySfxPositional(SFX_SHAFT_FIRE_ATTACK);
            self->step_s++;
            // fallthrough
        case 4:
            if (!(self->ext.rcenShaft.timer & 3)) {
                entity = AllocEntity(&g_Entities[112], &g_Entities[192]);
                if (entity != NULL) {
                    CreateEntityFromEntity(
                        E_ID(SHAFT_FLAME_PILLAR), self, entity);
                    entity->ext.rcenShaft.angle = self->ext.rcenShaft.angle;
                    entity->params = 12;
                    entity->zPriority = self->zPriority + 1;
                }
            }

            if (!--self->ext.rcenShaft.timer) {
                self->hitboxState = 2;
                SetStep(ATTACK_IDLE);
            }
            break;
        }
        break;
    case ATTACK_ELECTRIC:
        // Electric orbs
        switch (self->step_s) {
        case 0:
            if (self->params) {
                entity = self - 1;
            } else {
                entity = self + 1;
            }

            if (self->posX.i.hi > entity->posX.i.hi) {
                result = true;
            } else {
                result = false;
            }

            if (result) {
                self->velocityX = FIX(2.0);
            } else {
                self->velocityX = FIX(-2.0);
            }

            self->velocityY = 0;
            g_api.PlaySfx(SFX_RIC_SUC_REVIVE);
            self->step_s++;
            // fallthrough
        case 1:
            if (!AnimateEntity(anim_electric_charge_orb, self)) {
                self->step_s++;
            }
            // fallthrough
        case 2:
            MoveEntity();
            posX = self->posX.i.hi + g_Tilemap.scrollX.i.hi;
            if (self->velocityX > 0) {
                if (posX > 0x1C0) {
                    self->velocityX -= (self->velocityX >> 4);
                }
            } else if (posX < 0x140) {
                self->velocityX -= (self->velocityX >> 4);
            }

            if (abs(self->velocityX) < FIX(0.5) && self->step_s == 2) {
                self->velocityY = 0;
                self->step_s++;
            }

            break;
        case 3:
            for (i = 0; i < 2; i++) {
                entity = AllocEntity(&g_Entities[112], &g_Entities[128]);
                if (entity != NULL) {
                    CreateEntityFromEntity(E_ID(SHAFT_LIGHTNING), self, entity);
                    entity->zPriority = self->zPriority + 1;
                    entity->ext.shaftLightning.sourceOrb = self;
                    if (self->params) {
                        entity->ext.shaftLightning.targetOrb = self - 1;
                    } else {
                        entity->ext.shaftLightning.targetOrb = self + 1;
                    }
                }
            }
            self->velocityX = 0;
            self->ext.rcenShaft.movingUp = false;
            self->velocityY = FIX(1.25);
            self->hitboxState = 3;
            self->step_s++;
            // fallthrough
        case 4:
            MoveEntity();
            posY = self->posY.i.hi + g_Tilemap.scrollY.i.hi;
            if (self->velocityY > 0) {
                if (posY > 0x1B0) {
                    self->ext.rcenShaft.movingUp = true;
                }
            } else if (posY < 0x138) {
                self->ext.rcenShaft.movingUp = false;
            }

            // Once the orbs hit the top of the chamber, flip directions and
            // move back down, or vice-versa
            if (self->ext.rcenShaft.movingUp) {
                self->velocityY -= FIX(0.03125);
                if (self->velocityY < FIX(-1.25)) {
                    self->velocityY = FIX(-1.25);
                }
            } else {
                self->velocityY += FIX(0.03125);
                if (self->velocityY > FIX(1.25)) {
                    self->velocityY = FIX(1.25);
                }
            }

            if (!(g_Timer & 0x1F)) {
                g_api.PlaySfx(SFX_GALAMOTH_ELECTRICITY);
            }

            if (attack_step != ATTACK_ELECTRIC) {
                self->hitboxState = 2;
                SetStep(ATTACK_IDLE);
            }

            break;
        }
        break;
    case ATTACK_BOUNCE:
        // Bouncy orbs
        switch (self->step_s) {
        case 0:
            if (self->params) {
                result = AnimateEntity(anim_bouncy_charge_blue, self);
            } else {
                result = AnimateEntity(anim_bouncy_charge_red, self);
            }

            if (!result) {
                enemyDef = &g_api.enemyDefs[0x163];
                self->attack = enemyDef->attack;
                self->hitboxWidth = enemyDef->hitboxWidth;
                self->hitboxHeight = enemyDef->hitboxHeight;
                self->hitboxState = 3;
                self->step_s++;
            }

            break;
        case 1:
            angle = (((Random() & 3) << 8) * 4) + ROT(45);
            self->velocityX = (rcos(angle) * FIX(3)) >> 0xC;
            self->velocityY = (rsin(angle) * FIX(3)) >> 0xC;
            self->ext.rcenShaft.timer = 0xC0;
            SetSubStep(2);
            // fallthrough
        case 2:
            AnimateEntity(anim_bouncy_orb, self);
            MoveEntity();
            posX = self->posX.i.hi + g_Tilemap.scrollX.i.hi;
            posY = self->posY.i.hi + g_Tilemap.scrollY.i.hi;
            if (self->velocityX > 0) {
                if (posX > 0x1E0) {
                    self->velocityX = FIX(-3.0);
                    PlaySfxPositional(SFX_SHAFT_ORB_BOUNCE);
                }
            } else if (posX < 0x120) {
                self->velocityX = FIX(3.0);
                PlaySfxPositional(SFX_SHAFT_ORB_BOUNCE);
            }

            if (self->velocityY > 0) {
                if (posY > 0x1D4) {
                    self->velocityY = FIX(-3.0);
                    PlaySfxPositional(SFX_SHAFT_ORB_BOUNCE);
                }
            } else if (posY < 0x12C) {
                self->velocityY = FIX(3.0);
                PlaySfxPositional(SFX_SHAFT_ORB_BOUNCE);
            }

            if (!--self->ext.rcenShaft.timer) {
                enemyDef = &g_api.enemyDefs[0x160];
                self->attack = enemyDef->attack;
                self->hitboxWidth = enemyDef->hitboxWidth;
                self->hitboxHeight = enemyDef->hitboxHeight;
                self->hitboxState = 2;
                SetStep(ATTACK_IDLE);
            }
            break;
        }
        break;
    case DEATH:
        switch (self->step_s) {
        case 0:
            self->hitboxState = 0;
            self->animCurFrame = 0x2B;
            self->velocityX = 0;
            self->velocityY = 0;
            self->step_s++;
            // fallthrough
        case 1:
            posX = self->posX.i.hi + g_Tilemap.scrollX.i.hi;
            posY = self->posY.i.hi + g_Tilemap.scrollY.i.hi;
            if (posY > 0x1D8 || posX > 0x1EA || posX < 0x114) {
                self->flags |= FLAG_DESTROY_IF_OUT_OF_CAMERA;
                self->step_s = 2;
            } else {
                self->step_s = 3;
            }
            break;
        case 2:
            MoveEntity();
            self->velocityY += FIX(0.25);
            break;
        case 3:
            MoveEntity();
            self->velocityY += FIX(0.25);
            posY = self->posY.i.hi + g_Tilemap.scrollY.i.hi;
            if (posY > 0x1D8) {
                self->posY.i.hi = 0x1D8 - g_Tilemap.scrollY.i.hi;
                self->ext.rcenShaft.timer = 0x40;
                self->step_s++;
            }
            break;
        case 4:
            if (!(self->ext.rcenShaft.timer & 3)) {
                entity = AllocEntity(&g_Entities[96], &g_Entities[256]);
                if (entity != NULL) {
                    CreateEntityFromEntity(
                        E_ID(SHAFT_DEATH_FLAMES), self, entity);
                    entity->params = 1;
                    entity->zPriority = self->zPriority + 1;
                }
            }

            if (!--self->ext.rcenShaft.timer) {
                DestroyEntity(self);
                return;
            }
            break;
        }

        if (g_RcenShaftFlags & 8) {
            DestroyEntity(self);
        }
        break;
    }
}

void EntityShaftFlameTrail(Entity* self) {
    Entity* shaftEntity;
    s16 angle;

    if (g_RcenShaftFlags & 4) {
        DestroyEntity(self);
        return;
    }

    if (!self->step) {
        InitializeEntity(g_EInitShaftFlame);
        self->palette = PAL_SHAFT_ORB_FLAME_TRAIL;
        self->velocityX = 0;
        self->drawFlags = ENTITY_ROTATE;
        self->rotate = self->ext.rcenShaft.angle + ROT(90);
        self->blendMode = BLEND_ADD | BLEND_TRANSP;
    }

    self->velocityX += FIX(1.0);
    shaftEntity = self->ext.rcenShaft.shaftEntity;
    angle = self->ext.rcenShaft.angle;
    self->posX.i.hi = shaftEntity->posX.i.hi;
    self->posY.i.hi = shaftEntity->posY.i.hi;
    self->posX.val += (self->velocityX >> 12) * rcos(angle);
    self->posY.val += (self->velocityX >> 12) * rsin(angle);

    if (!AnimateEntity(anim_flame_trail, self)) {
        DestroyEntity(self);
    }
}

void EntityShaftFlamePillar(Entity* self) {
    Entity* entity;
    s16 angle;

    if (g_RcenShaftFlags & 4) {
        DestroyEntity(self);
        return;
    }

    if (!self->step) {
        InitializeEntity(g_EInitShaftFlame);
        self->palette = PAL_SHAFT_ORB_FLAME_PILLAR;
        self->drawFlags = ENTITY_OPACITY | ENTITY_ROTATE;
        self->rotate = self->ext.rcenShaft.angle + ROT(90);
        angle = self->ext.rcenShaft.angle;
        self->velocityX = (rcos(angle) * FIX(3)) >> 0xC;
        self->velocityY = (rsin(angle) * FIX(3)) >> 0xC;
        self->blendMode = BLEND_ADD | BLEND_TRANSP;
    }

    MoveEntity();
    angle = self->ext.rcenShaft.angle;
    self->velocityX += (rcos(angle) << 0xA) >> 0xC;
    self->velocityY += (rsin(angle) << 0xA) >> 0xC;

    if (self->params && self->pose == 7 && !self->poseTimer) {
        entity = AllocEntity(&g_Entities[112], &g_Entities[192]);
        if (entity != NULL) {
            CreateEntityFromEntity(E_ID(SHAFT_FLAME_PILLAR), self, entity);
            entity->zPriority = self->zPriority;
            entity->params = self->params - 1;
            entity->ext.rcenShaft.angle = self->ext.rcenShaft.angle;
        }
    }

    self->opacity -= 2;
    if (!self->opacity) {
        DestroyEntity(self);
        return;
    }
    if (!AnimateEntity(anim_flame_pillar, self)) {
        DestroyEntity(self);
    }
}

void EntityShaftLightning(Entity* self) {
    Primitive* prim;
    Primitive* primTwo;
    s32 posX;
    Entity* entity;
    s32 posY;
    s16 tempAngle;
    s16 boltAngle;
    s32 i;
    u8 closeToTarget;
    s16 angle;
    s32 primIndex;
    s32 sp34;

    if (g_RcenShaftFlags & 4) {
        DestroyEntity(self);
        return;
    }

    entity = self->ext.shaftLightning.sourceOrb;
    self->posX.i.hi = entity->posX.i.hi;
    self->posY.i.hi = entity->posY.i.hi;
    if (entity->entityId != E_ID(SHAFT_ATTACK_ORB) || entity->step != 4) {
        DestroyEntity(self);
        return;
    }

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitInteractable);
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 0x14);
        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags |= FLAG_HAS_PRIMS;
        self->primIndex = primIndex;
        prim = &g_PrimBuf[primIndex];
        self->ext.shaftLightning.prim = prim;
        self->ext.shaftLightning.primTwo = prim;

        i = 0;
        while (prim != NULL) {
            prim->tpage = 0x1A;
            prim->clut = 0x194;
            prim->u0 = prim->u1 = (i * 0x10) + 0x90;
            prim->u2 = prim->u3 = prim->u0 + 0x10;
            prim->v0 = prim->v2 = 0xD0;
            prim->v1 = prim->v3 = 0xC0;
            PGREY(prim, 0) = 0x50;
            LOW(prim->r1) = LOW(prim->r0);
            LOW(prim->r2) = LOW(prim->r0);
            LOW(prim->r3) = LOW(prim->r0);
            prim->priority = self->zPriority;
            prim->drawMode = DRAW_HIDE;
            prim = prim->next;

            if (++i > 5) {
                i = 0;
            }
        }
    case 1:
        prim = self->ext.shaftLightning.prim;
        prim->x0 = self->posX.i.hi;
        prim->y0 = self->posY.i.hi;
        prim->x1 = prim->x0;
        prim->y1 = prim->y1 - 0x10;
        prim->x2 = self->posX.i.hi;
        prim->y2 = self->posY.i.hi;
        prim->x3 = prim->x2;
        prim->y3 = prim->y2 - 0x10;
        self->ext.shaftLightning.primTwo = prim;

        entity = self->ext.shaftLightning.sourceOrb;
        posX = entity->posX.i.hi;
        entity = self->ext.shaftLightning.targetOrb;
        posX = entity->posX.i.hi - posX;
        if (posX > 0) {
            self->ext.shaftLightning.boltAngle = ((rand() & 0x7FF) - ROT(90));
        } else {
            self->ext.shaftLightning.boltAngle = ((rand() & 0x7FF) + ROT(90));
        }

        while (prim != NULL) {
            PGREY(prim, 0) = 0x50;
            LOW(prim->r1) = LOW(prim->r0);
            LOW(prim->r2) = LOW(prim->r0);
            LOW(prim->r3) = LOW(prim->r0);
            prim->drawMode = DRAW_HIDE;
            prim = prim->next;
        }
        self->ext.shaftLightning.segmentsBeforeAim = 0;
        self->step++;
        // fallthrough
    case 2:
        // nb. loop indefinitely until break
        for (i = 0;; i = i + 1) {
            prim = self->ext.shaftLightning.primTwo;
            boltAngle = self->ext.shaftLightning.boltAngle;
            entity = self->ext.shaftLightning.targetOrb;
            posX = entity->posX.i.hi;
            posY = entity->posY.i.hi;
            posX = posX - prim->x2;
            posY = posY - prim->y2;

            if (abs(posX) < 0x10 && abs(posY) < 0x10) {
                self->step = 1;
                return;
            }

            if (abs(posX) < 0x20 && abs(posY) < 0x20) {
                closeToTarget = true;
            } else {
                closeToTarget = false;
            }

            if (!self->ext.shaftLightning.segmentsBeforeAim) {
                self->ext.shaftLightning.segmentsBeforeAim = 4;

                if (closeToTarget) {
                    self->ext.shaftLightning.segmentsBeforeAim = 2;
                }

                angle = ratan2(-posY, posX);
                tempAngle = angle - boltAngle;
                if (tempAngle > ROT(180)) {
                    tempAngle = tempAngle - ROT(360);
                }

                if (tempAngle < ROT(-180)) {
                    tempAngle = tempAngle + ROT(360);
                }

                // If the bolt is getting close to the target orb we turn more
                // sharply to hit it
                if (!closeToTarget) {
                    tempAngle /= 4;
                } else {
                    tempAngle /= 2;
                }
                self->ext.shaftLightning.angleStep = tempAngle;
            }

            boltAngle += self->ext.shaftLightning.angleStep;
            if (!closeToTarget) {
                // Add some jitter to the bolt if we're not close to our target
                // orb yet
                boltAngle += (0x60 - ((Random() & 3) << 6));
            }
            boltAngle &= 0xFFF;

            primTwo = prim->next;
            if (primTwo == NULL) {
                self->step = 1;
                return;
            }

            LOW(primTwo->x0) = LOW(prim->x2);
            LOW(primTwo->x1) = LOW(prim->x3);
            self->ext.shaftLightning.boltAngle = boltAngle;
            self->ext.shaftLightning.primTwo = primTwo;
            posX = (rcos(boltAngle) * 0xC) >> 0xC;
            posY = -((rsin(boltAngle) * 0xC) >> 0xC);
            primTwo->x2 = primTwo->x0 + posX;
            primTwo->y2 = primTwo->y0 + posY;

            tempAngle = boltAngle - ROT(90);
            sp34 = 0x10;
            posX = (sp34 * rcos(tempAngle)) >> 0xC;
            posY = -((sp34 * rsin(tempAngle)) >> 0xC);
            posX = primTwo->x3 = primTwo->x2 + posX;
            posY = primTwo->y3 = primTwo->y2 + posY;

            entity = &PLAYER;
            posX = posX - entity->posX.i.hi;
            posY = posY - entity->posY.i.hi;

            // If the player comes within 12px of the lightning, spawn a
            // damaging hitbox entity
            if (abs(posX) < 12 && abs(posY) < 12) {
                entity = AllocEntity(&g_Entities[160], &g_Entities[192]);
                if (entity != NULL) {
                    CreateEntityFromCurrentEntity(
                        E_ID(SHAFT_LIGHTNING_HITBOX), entity);
                    entity->posX.i.hi = primTwo->x3;
                    entity->posY.i.hi = primTwo->y3;
                }
            }
            primTwo->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS |
                                DRAW_UNK02 | DRAW_TRANSP;
            self->ext.shaftLightning.segmentsBeforeAim--;
        }
        // fallthrough
    case 3:
        prim = self->ext.shaftLightning.prim;
        while (prim != NULL) {
            prim->drawMode = DRAW_HIDE;
            prim = prim->next;
        }
        self->step = 1;
        break;
    }
}

// Lightning is made up of Primitives which have no collision.
// As such, the game spawns in an Entity with a hitbox for a single frame
// of the lightning attack, so it can damage the player.
void EntityShaftLightningHitbox(Entity* self) {
    if (g_RcenShaftFlags & 4) {
        DestroyEntity(self);
    } else if (!self->step) {
        InitializeEntity(g_EInitShaftLightningHitbox);
    } else {
        DestroyEntity(self);
    }
}

void EntityShaftOrbitOrb(Entity* self) {
    Entity* entity;
    s32 posX;
    s32 posY;
    s16 angle;

    if (g_RcenShaftFlags & 4 && self->step != 4) {
        SetStep(4);
    }

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitShaftOrb);
        self->hitboxState = 0;
        self->ext.rcenShaft.timer = ((Random() & 0x1F) * 4) + 0x10;
        // fallthrough
    case 1:
        // Once the random timer expires, fly in from the bottom of the screen
        if (!--self->ext.rcenShaft.timer) {
            SetStep(2);
        }
        break;
    case 2:
        switch (self->step_s) {
        case 0:
            self->velocityY = FIX(-6) - ((rand() & PSP_RANDMASK) * 0x10);
            self->animCurFrame = 0x2B;
            PlaySfxPositional(SFX_TELEPORT_BANG_SHORT_B);
            self->step_s++;
            // fallthrough
        case 1:
            MoveEntity();
            if (self->posY.i.hi < 0xC0) {
                self->ext.rcenShaft.timer = 0x60;
                self->step_s++;
            }
            break;
        case 2:
            MoveEntity();
            self->velocityY -= self->velocityY >> 4;
            if (!--self->ext.rcenShaft.timer) {
                self->hitboxState = 2;
                SetStep(3);
            }
            break;
        }
        break;
    case 3:
        if (!self->step_s) {
            self->ext.rcenShaft.swayAngle = rand() & 0xFFF;
            self->ext.rcenShaft.angle = rand() & 0xFFF;
            self->animCurFrame = 0x2B;
            self->step_s++;
        }

        entity = self->ext.rcenShaft.shaftEntity;
        posX = entity->posX.i.hi;
        posY = entity->posY.i.hi - 4;

        posX += ((rcos(self->ext.rcenShaft.swayAngle) * 0x30) >> 0xC);
        posX -= self->posX.i.hi;
        posY -= self->posY.i.hi;

        angle = ratan2(posY, posX);
        angle = _LimitAngleChange(0x40, self->ext.rcenShaft.angle, angle);
        self->velocityX = (rcos(angle) * FIX(2.5)) >> 0xC;
        self->velocityY = (rsin(angle) * FIX(2.5)) >> 0xC;
        self->ext.rcenShaft.angle = angle;
        MoveEntity();
        // The orbiting orbs sway at half speed to the red and blue attack orbs
        self->ext.rcenShaft.swayAngle += 0x20;
        return;
    case 4:
        switch (self->step_s) {
        case 0:
            self->hitboxState = 0;
            self->animCurFrame = 0x2B;
            self->velocityX = 0;
            self->velocityY = 0;
            self->step_s++;
            // fallthrough
        case 1:
            posX = self->posX.i.hi + g_Tilemap.scrollX.i.hi;
            posY = self->posY.i.hi + g_Tilemap.scrollY.i.hi;
            if (posY >= 0x1D9 || posX >= 0x1EB || posX < 0x114) {
                self->flags |= FLAG_DESTROY_IF_OUT_OF_CAMERA;
                self->step_s = 2;
            } else {
                self->step_s = 3;
            }
            break;
        case 2:
            MoveEntity();
            self->velocityY += FIX(0.25);
            break;
        case 3:
            // Fall to the floor
            MoveEntity();
            self->velocityY += FIX(0.25);
            posY = self->posY.i.hi + g_Tilemap.scrollY.i.hi;
            if (posY > 0x1D8) {
                self->posY.i.hi = 0x1D8 - g_Tilemap.scrollY.i.hi;
                self->ext.rcenShaft.timer = 0x40;
                self->step_s++;
            }
            break;
        case 4:
            // Burst into flames
            if (!(self->ext.rcenShaft.timer & 3)) {
                entity = AllocEntity(&g_Entities[96], &g_Entities[256]);
                if (entity != NULL) {
                    CreateEntityFromEntity(
                        E_ID(SHAFT_DEATH_FLAMES), self, entity);
                    entity->params = 1;
                    entity->zPriority = self->zPriority + 1;
                }
            }

            // And finally, despawn
            if (!--self->ext.rcenShaft.timer) {
                DestroyEntity(self);
                return;
            }

            break;
        }

        if (g_RcenShaftFlags & 8) {
            DestroyEntity(self);
        }

        break;
    }
}
