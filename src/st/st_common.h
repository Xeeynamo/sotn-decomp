// SPDX-License-Identifier: AGPL-3.0-or-later

/*
sine table. can be generated like:

#define TABLE_SIZE 256
#define PI 3.14159265358979323846

static short D_80180A94[TABLE_SIZE];

for (int i = 0; i < TABLE_SIZE; i++) {
    double angle = (2 * PI * i) / (double)(TABLE_SIZE);
    D_80180A94[i] = round((0x1000 * sin(angle)));
}
*/
static s16 g_SineTable[] = {
    0x0000, 0x0065, 0x00C9, 0x012D, 0x0191, 0x01F5, 0x0259, 0x02BC, 0x031F,
    0x0381, 0x03E3, 0x0444, 0x04A5, 0x0505, 0x0564, 0x05C2, 0x061F, 0x067C,
    0x06D7, 0x0732, 0x078B, 0x07E3, 0x083A, 0x088F, 0x08E4, 0x0937, 0x0988,
    0x09D8, 0x0A26, 0x0A73, 0x0ABF, 0x0B08, 0x0B50, 0x0B97, 0x0BDB, 0x0C1E,
    0x0C5E, 0x0C9D, 0x0CDA, 0x0D15, 0x0D4E, 0x0D85, 0x0DB9, 0x0DEC, 0x0E1C,
    0x0E4B, 0x0E77, 0x0EA1, 0x0EC8, 0x0EEE, 0x0F11, 0x0F31, 0x0F50, 0x0F6C,
    0x0F85, 0x0F9C, 0x0FB1, 0x0FC4, 0x0FD4, 0x0FE1, 0x0FEC, 0x0FF5, 0x0FFB,
    0x0FFF, 0x1000, 0x0FFF, 0x0FFB, 0x0FF5, 0x0FEC, 0x0FE1, 0x0FD4, 0x0FC4,
    0x0FB1, 0x0F9C, 0x0F85, 0x0F6C, 0x0F50, 0x0F31, 0x0F11, 0x0EEE, 0x0EC8,
    0x0EA1, 0x0E77, 0x0E4B, 0x0E1C, 0x0DEC, 0x0DB9, 0x0D85, 0x0D4E, 0x0D15,
    0x0CDA, 0x0C9D, 0x0C5E, 0x0C1E, 0x0BDB, 0x0B97, 0x0B50, 0x0B08, 0x0ABF,
    0x0A73, 0x0A26, 0x09D8, 0x0988, 0x0937, 0x08E4, 0x088F, 0x083A, 0x07E3,
    0x078B, 0x0732, 0x06D7, 0x067C, 0x061F, 0x05C2, 0x0564, 0x0505, 0x04A5,
    0x0444, 0x03E3, 0x0381, 0x031F, 0x02BC, 0x0259, 0x01F5, 0x0191, 0x012D,
    0x00C9, 0x0065, 0x0000, 0xFF9B, 0xFF37, 0xFED3, 0xFE6F, 0xFE0B, 0xFDA7,
    0xFD44, 0xFCE1, 0xFC7F, 0xFC1D, 0xFBBC, 0xFB5B, 0xFAFB, 0xFA9C, 0xFA3E,
    0xF9E1, 0xF984, 0xF929, 0xF8CE, 0xF875, 0xF81D, 0xF7C6, 0xF771, 0xF71C,
    0xF6C9, 0xF678, 0xF628, 0xF5DA, 0xF58D, 0xF541, 0xF4F8, 0xF4B0, 0xF469,
    0xF425, 0xF3E2, 0xF3A2, 0xF363, 0xF326, 0xF2EB, 0xF2B2, 0xF27B, 0xF247,
    0xF214, 0xF1E4, 0xF1B5, 0xF189, 0xF15F, 0xF138, 0xF112, 0xF0EF, 0xF0CF,
    0xF0B0, 0xF094, 0xF07B, 0xF064, 0xF04F, 0xF03C, 0xF02C, 0xF01F, 0xF014,
    0xF00B, 0xF005, 0xF001, 0xF000, 0xF001, 0xF005, 0xF00B, 0xF014, 0xF01F,
    0xF02C, 0xF03C, 0xF04F, 0xF064, 0xF07B, 0xF094, 0xF0B0, 0xF0CF, 0xF0EF,
    0xF112, 0xF138, 0xF15F, 0xF189, 0xF1B5, 0xF1E4, 0xF214, 0xF247, 0xF27B,
    0xF2B2, 0xF2EB, 0xF326, 0xF363, 0xF3A2, 0xF3E2, 0xF425, 0xF469, 0xF4B0,
    0xF4F8, 0xF541, 0xF58D, 0xF5DA, 0xF628, 0xF678, 0xF6C9, 0xF71C, 0xF771,
    0xF7C6, 0xF81D, 0xF875, 0xF8CE, 0xF929, 0xF984, 0xF9E1, 0xFA3E, 0xFA9C,
    0xFAFB, 0xFB5B, 0xFBBC, 0xFC1D, 0xFC7F, 0xFCE1, 0xFD44, 0xFDA7, 0xFE0B,
    0xFE6F, 0xFED3, 0xFF37, 0xFF9B,
};

#include "../destroy_entity.h"

#ifndef HARD_LINK
void DestroyEntitiesFromIndex(s16 index) {
    Entity* entity = &g_Entities[index];

    while (entity < &g_Entities[TOTAL_ENTITY_COUNT - 1]) {
        DestroyEntity(entity);
        entity++;
    }
}
#endif

void PreventEntityFromRespawning(Entity* entity) {
    if (entity->entityRoomIndex) {
        u16 index = entity->entityRoomIndex - 1 >> 5;
        g_unkGraphicsStruct.D_80097428[index] |=
            1 << ((entity->entityRoomIndex - 1) & 0x1F);
    }
}

#include "animate_entity.h"

// Notably, this is completely unused.
// The use of the 0xBB offset in the entity, which does not match the current
// entity struct, suggests that this was for an older form of Entity.
// When the Entity was changed, this function was already unused, so was never
// updated. This is just a theory though.

#define SELF_BB (*((u8*)&self->unkB8 + 3))

u8 UnkAnimFunc(u8 frames[], Entity* self, u8 arg2) {
    u16 animFrameStart = self->pose * 2;
    u8* var_s1 = &frames[animFrameStart];
    s16 var_a1 = 0;

    if (self->poseTimer == 0) {
        if (*var_s1 != 0) {
            if (*var_s1 == 0xFF) {
                return 0;
            }
            self->poseTimer = *var_s1++ + SELF_BB;
            self->animCurFrame = *var_s1++;
            self->pose++;
            var_a1 = 128;
        } else {
            var_s1 = frames;
            self->pose = 0;
            self->poseTimer = 0;
            SELF_BB = (arg2 * Random()) >> 8;
            self->poseTimer = *var_s1++ + SELF_BB;
            self->animCurFrame = *var_s1;
            self->pose++;
            return 0;
        }
    }
    self->poseTimer--;
    self->animCurFrame = var_s1[-1];
    var_a1 |= 1;
    return var_a1;
}

// Absolute distance from g_CurrentEntity to the player in the X Axis
s16 GetDistanceToPlayerX(void) {
    Entity* player = &PLAYER;
    s16 xDistance = g_CurrentEntity->posX.i.hi - player->posX.i.hi;

    if (xDistance < 0) {
        xDistance = -xDistance;
    }
    return xDistance;
}

// Absolute distance from g_CurrentEntity to the player in the Y Axis
s32 GetDistanceToPlayerY(void) {
    Entity* player = &PLAYER;
    s32 yDistance = g_CurrentEntity->posY.i.hi - player->posY.i.hi;

    if (yDistance < 0) {
        yDistance = -yDistance;
    }
    return yDistance;
}

/**
 * Returns the player's side position relative to g_CurrentEntity
 * 0 = Player is on the right side
 * 1 = Player is on the left side
 * 2 = Player is above
 */
u8 GetSideToPlayer() {
    u8 side = 0;
    Entity* player = &PLAYER;

    if (g_CurrentEntity->posX.i.hi > player->posX.i.hi) {
        side |= 1;
    }

    if (g_CurrentEntity->posY.i.hi > player->posY.i.hi) {
        side |= 2;
    }
    return side;
}

void MoveEntity(void) {
    g_CurrentEntity->posX.val += g_CurrentEntity->velocityX;
    g_CurrentEntity->posY.val += g_CurrentEntity->velocityY;
}

void FallEntity(void) {
    if (g_CurrentEntity->velocityY < FALL_TERMINAL_VELOCITY) {
        g_CurrentEntity->velocityY += FALL_GRAVITY;
    }
}

#if defined(VERSION_BETA) || (STAGE == STAGE_ST0 && !defined(VERSION_PSP))
u8 func_8019214C(void) {
    u8 unkState;
    Entity* entity;

    MoveEntity();
    FallEntity();

    entity = g_CurrentEntity;

    if (unkState & 1) {
        entity->velocityY = 0;
    }

    return unkState;
}
#endif

s32 UnkCollisionFunc3(s16* sensors) {
    Collider col;
    Collider colBack;
    s16 x;
    s16 y;
    s16 i;

    MoveEntity();
    FallEntity();
    if (g_CurrentEntity->velocityY >= 0) {
        x = g_CurrentEntity->posX.i.hi;
        y = g_CurrentEntity->posY.i.hi;
        for (i = 0; i < 4; i++) {
            x += *sensors++;
            y += *sensors++;
            g_api.CheckCollision(x, y, &col, 0);
            if (col.effects & EFFECT_UNK_8000) {
                if (i == 1) {
                    if (col.effects & EFFECT_SOLID) {
                        g_api.CheckCollision(x, y - 8, &colBack, 0);
                        if (!(colBack.effects & EFFECT_SOLID)) {
                            g_CurrentEntity->posY.i.hi += 4 + col.unk18;
                            g_CurrentEntity->velocityX = 0;
                            g_CurrentEntity->velocityY = 0;
                            g_CurrentEntity->flags &= ~FLAG_UNK_10000000;
                            return 1;
                        }
                    }
                    continue;
                }
            }
            if (col.effects & EFFECT_NOTHROUGH && i != 1) {
                if (col.effects & EFFECT_QUICKSAND) {
                    g_CurrentEntity->flags &= ~FLAG_UNK_10000000;
                    return 4;
                }
                g_api.CheckCollision(x, y - 8, &colBack, 0);
                if (!(colBack.effects & EFFECT_SOLID)) {
                    g_CurrentEntity->posY.i.hi += col.unk18;
                    g_CurrentEntity->velocityX = 0;
                    g_CurrentEntity->velocityY = 0;
                    g_CurrentEntity->flags &= ~FLAG_UNK_10000000;
                    return 1;
                }
            }
        }
    }
    g_CurrentEntity->flags |= FLAG_UNK_10000000;
    return 0;
}

#if defined(VERSION_BETA) || STAGE == STAGE_ST0
s32 func_80192408(u16* sensors, u16 arg1) {
    Collider col[5];
    s16 i;
    u16 var_a0;
    s16 x;
    s16 y;
    Collider* c;

    MoveEntity();
    FallEntity();
    if (g_CurrentEntity->velocityY >= 0) {
        x = g_CurrentEntity->posX.i.hi;
        y = i = g_CurrentEntity->posY.i.hi; // FAKE, no reason to set i.
        c = col;
        i = 0;
        while (true) {
            x += *sensors++;
            y += *sensors++;
            g_api.CheckCollision(x, y, c, 0);
            if (++i >= 4) {
                break;
            }
            c++;
        }

        var_a0 = true;
        for (i = 0, c = col; i < 4; i++, c++) {
            if (c->effects & EFFECT_UNK_8000) {
                // i in [0, 1]
                if (!(i >> 1)) {
                    break;
                }
            } else if (c->effects & EFFECT_SOLID) {
                if (i == 1 && !var_a0) {
                    c = col; // fake?
                    break;
                }
            } else if (i != 1) {
                var_a0 = false;
            }
        }

        for (i = 0; i < 4; i++) {
            c = &col[i];
            if (c->effects & EFFECT_SOLID) {
                if (i == 1) {
                    g_CurrentEntity->posY.i.hi += 4;
                }
                g_CurrentEntity->posY.i.hi += c->unk18;
                g_CurrentEntity->velocityY = 0;
                if (arg1) {
                    g_CurrentEntity->velocityX = 0;
                }
                return 1;
            }
        }
    }
    return 0;
}
#endif

s32 UnkCollisionFunc2(s16* posX) {
    Collider collider;
    s16 x, y;

    g_CurrentEntity->posX.val += g_CurrentEntity->velocityX;
    g_CurrentEntity->posY.i.hi += 3;
    x = g_CurrentEntity->posX.i.hi + *posX++;
    y = g_CurrentEntity->posY.i.hi + *posX++;
    g_api.CheckCollision(x, y, &collider, 0);

    if (collider.effects & EFFECT_SOLID) {
        g_CurrentEntity->posY.i.hi += collider.unk18;
    } else {
        return 0;
    }

    if (g_CurrentEntity->velocityX != 0) {
        if (g_CurrentEntity->velocityX < 0) {
            x -= *posX++;
        } else {
            x += *posX++;
        }
        y += *posX;
        y -= 7;
        g_api.CheckCollision(x, y, &collider, 0);
        if (collider.effects & EFFECT_SOLID) {
            if (collider.effects & EFFECT_UNK_8000 ||
                !(collider.effects & EFFECT_UNK_0002)) {
                return 0x61;
            }
            g_CurrentEntity->posX.val -= g_CurrentEntity->velocityX;
            g_CurrentEntity->velocityX = 0;
            return 0xFF;
        }
        y += 15;
        g_api.CheckCollision(x, y, &collider, 0);
        if (collider.effects & EFFECT_SOLID) {
            if (collider.effects & EFFECT_UNK_8000) {
                return 0x61;
            }
            return 1;
        }
        g_CurrentEntity->posX.val -= g_CurrentEntity->velocityX;
        g_CurrentEntity->velocityX = 0;

        return 0x80;
    }
    return 1;
}

Entity* AllocEntity(Entity* start, Entity* end) {
    Entity* current = start;

    while (current < end) {
        if (!current->entityId) {
            DestroyEntity(current);
            return current;
        }
        current++;
    }
    return NULL;
}

s32 GetSineScaled(u8 arg0, s16 arg1) {
    s32 sine = g_SineTable[arg0];
    return sine * arg1;
}

s16 GetSine(u8 arg0) { return g_SineTable[arg0]; }

void SetEntityVelocityFromAngle(u8 arg0, s16 arg1) {
    g_CurrentEntity->velocityX = GetSineScaled(arg0, arg1);
    g_CurrentEntity->velocityY = GetSineScaled(arg0 - 0x40, arg1);
}

u8 Ratan2Shifted(s16 x, s16 y) {
    u8 angle = ratan2(y, x) >> 4;
    return angle + 0x40;
}

u8 GetAngleBetweenEntitiesShifted(Entity* a, Entity* b) {
    s16 diffX = b->posX.i.hi - a->posX.i.hi;
    s16 diffY = b->posY.i.hi - a->posY.i.hi;
    return Ratan2Shifted(diffX, diffY);
}

u8 GetAnglePointToEntityShifted(s32 x, s32 y) {
    s32 diffX = x - (u16)g_CurrentEntity->posX.i.hi;
    s32 diffY = y - (u16)g_CurrentEntity->posY.i.hi;
    return Ratan2Shifted(diffX, diffY);
}

u8 AdjustValueWithinThreshold(u8 threshold, u8 currentValue, u8 targetValue) {
    u8 absoluteDifference;
    s8 relativeDifference = targetValue - currentValue;

    if (relativeDifference < 0) {
        absoluteDifference = -relativeDifference;
    } else {
        absoluteDifference = relativeDifference;
    }

    if (absoluteDifference > threshold) {
        if (relativeDifference < 0) {
            absoluteDifference = currentValue - threshold;
        } else {
            absoluteDifference = currentValue + threshold;
        }

        return absoluteDifference;
    }

    return targetValue;
}

void UnkEntityFunc0(u16 slope, s16 speed) {
    g_CurrentEntity->velocityX = rcos(slope) * speed / 16;
    g_CurrentEntity->velocityY = rsin(slope) * speed / 16;
}

u16 Ratan2(s16 x, s16 y) { return ratan2(y, x); }

u16 GetAngleBetweenEntities(Entity* a, Entity* b) {
    s32 diffX = b->posX.i.hi - a->posX.i.hi;
    s32 diffY = b->posY.i.hi - a->posY.i.hi;
    return ratan2(diffY, diffX);
}

u16 GetAnglePointToEntity(s32 x, s32 y) {
    s16 diffX = x - (u16)g_CurrentEntity->posX.i.hi;
    s16 diffY = y - (u16)g_CurrentEntity->posY.i.hi;
    return ratan2(diffY, diffX);
}

u16 GetNormalizedAngle(u16 arg0, u16 arg1, u16 arg2) {
    u16 temp_a2 = (s16)(arg2 - arg1);
    u16 ret;

    if (temp_a2 & 0x800) {
#if STAGE == STAGE_ST0
        ret = temp_a2 & 0x7FF;
#else
        ret = (0x800 - temp_a2) & 0x7FF;
#endif
    } else {
        ret = temp_a2;
    }

    if (ret > arg0) {
        if (temp_a2 & 0x800) {
            ret = arg1 - arg0;
        } else {
            ret = arg1 + arg0;
        }

        return ret;
    }
    return arg2;
}

void SetStep(u8 step) {
    g_CurrentEntity->step = step;
    g_CurrentEntity->step_s = 0;
    g_CurrentEntity->pose = 0;
    g_CurrentEntity->poseTimer = 0;
}

void SetSubStep(u8 step_s) {
    g_CurrentEntity->step_s = step_s;
    g_CurrentEntity->pose = 0;
    g_CurrentEntity->poseTimer = 0;
}

void EntityExplosionSpawn(u16 params, u16 arg1) {
#if STAGE != STAGE_ST0
    if (arg1) {
#if defined VERSION_BETA
        g_api.PlaySfx(arg1);
#else
        PlaySfxPositional(arg1);
#endif
    }
#endif
    if (params == 0xFF) {
        DestroyEntity(g_CurrentEntity);
        return;
    }

    g_CurrentEntity->entityId = E_EXPLOSION;
    g_CurrentEntity->pfnUpdate = (PfnEntityUpdate)EntityExplosion;
    g_CurrentEntity->params = params;
    g_CurrentEntity->animCurFrame = 0;
    g_CurrentEntity->drawFlags = FLAG_DRAW_DEFAULT;
    g_CurrentEntity->step = 0;
    g_CurrentEntity->step_s = 0;
}

void InitializeEntity(u16 arg0[]) {
    u16 enemyId;
    EnemyDef* enemyDef;

    g_CurrentEntity->animSet = *arg0++;
    g_CurrentEntity->animCurFrame = *arg0++;
    g_CurrentEntity->unk5A = *arg0++;
    g_CurrentEntity->palette = *arg0++;

    // n.b.! the post increment of arg0 is optimized out
    // on the PS1 version, but not on the PSP version.
    enemyId = g_CurrentEntity->enemyId = *arg0++;
    enemyDef = &g_api.enemyDefs[enemyId];
    g_CurrentEntity->hitPoints = enemyDef->hitPoints;
    g_CurrentEntity->attack = enemyDef->attack;
    g_CurrentEntity->attackElement = enemyDef->attackElement;
    g_CurrentEntity->hitboxState = enemyDef->hitboxState;
    g_CurrentEntity->hitboxWidth = enemyDef->hitboxWidth;
    g_CurrentEntity->hitboxHeight = enemyDef->hitboxHeight;
    g_CurrentEntity->flags = enemyDef->flags;
    g_CurrentEntity->hitboxOffX = 0;
    g_CurrentEntity->hitboxOffY = 0;
    g_CurrentEntity->step++;
    g_CurrentEntity->step_s = 0;
    if (!g_CurrentEntity->zPriority) {
        g_CurrentEntity->zPriority = g_unkGraphicsStruct.g_zEntityCenter - 0xC;
    }
}

void EntityDummy(Entity* arg0) {
    if (!arg0->step) {
        arg0->step++;
    }
}

s32 UnkCollisionFunc(s16* hitSensors, s16 sensorCount) {
    Collider collider;
    s32 velocityX;
    s16 i;
    s16 x;
    s16 y;

    velocityX = g_CurrentEntity->velocityX;
    if (velocityX != 0) {
        x = g_CurrentEntity->posX.i.hi;
        y = g_CurrentEntity->posY.i.hi;
        for (i = 0; i < sensorCount; i++) {
            if (velocityX < 0) {
                x += *hitSensors++;
            } else {
                x -= *hitSensors++;
            }

            y += *hitSensors++;
            g_api.CheckCollision(x, y, &collider, 0);
            if (collider.effects & EFFECT_UNK_0002 &&
                ((!(collider.effects & EFFECT_UNK_8000)) || i)) {
                return 2;
            }
        }
        return 0;
    }

    // implicit return
}

void CheckFieldCollision(s16* hitSensors, s16 sensorCount) {
    Collider collider;
    s32 velocityX;
    s16 i;
    s16 x;
    s16 y;

    velocityX = g_CurrentEntity->velocityX;
    if (velocityX == 0) {
        return;
    }

    x = g_CurrentEntity->posX.i.hi;
    y = g_CurrentEntity->posY.i.hi;
    for (i = 0; i < sensorCount; i++) {
        if (velocityX < 0) {
            x += *hitSensors++;
        } else {
            x -= *hitSensors++;
        }

        y += *hitSensors++;
        g_api.CheckCollision(x, y, &collider, 0);
        if (collider.effects & EFFECT_UNK_0002 &&
            (!(collider.effects & EFFECT_UNK_8000) || i)) {
            if (velocityX < 0) {
                g_CurrentEntity->posX.i.hi += collider.unk1C;
            } else {
                g_CurrentEntity->posX.i.hi += collider.unk14;
            }
            break;
        }
    }
}

// This function checks if the player collides with the specified entity
// and from which direction.
// w and h holds the collider size of the entity
// while flags stores which sides are solid
s32 GetPlayerCollisionWith(Entity* self, u16 w, u16 h, u16 flags) {
    Entity* pl = &PLAYER;
    s16 x;
    s16 y;
    u16 checks;

#if STAGE != STAGE_ST0
    s32 plStatus = g_Player.status;
    Collider col;

    x = self->posX.i.hi;
    y = self->posY.i.hi;
    if (x > 0x120 || x < -0x20 || y < -0x180 || y > 0x180) {
        return 0;
    }

    x = pl->posX.i.hi - x;
    y = pl->posY.i.hi - y;
#else
    if (self->posX.i.hi & 0x100) {
        return 0;
    }
    if (self->posY.i.hi & 0x100) {
        return 0;
    }

    x = pl->posX.i.hi - self->posX.i.hi;
    y = pl->posY.i.hi - self->posY.i.hi;
#endif

    if (self->facingLeft) {
        x += self->hitboxOffX;
    } else {
        x -= self->hitboxOffX;
    }
    y -= self->hitboxOffY;

#if STAGE != STAGE_ST0
    g_api.GetPlayerSensor(&col); // get player collision size
    w += col.unk14;
    h += col.unk18;
#endif

    if (x > 0) {
        checks = 1;
    } else {
        checks = 0;
    }
    if (y > 0) {
        checks |= 2;
    }

#if STAGE == STAGE_ST0
    w += 8;
    h += 24;
#endif

    x += w;
    y += h;
    w += w;
    h += h;

    if ((u16)x <= w && (u16)y <= h) {

        if (x && x != w) {
            // check collision from top
            if (flags & 4 && checks ^ 2 && pl->velocityY >= 0 && y < 8) {
                pl->posY.i.hi -= y;
#if STAGE == STAGE_ST0
                g_Player.vram_flag |= VRAM_FLAG_UNK40 | TOUCHING_GROUND;
#else
                D_80097488.y.i.hi -= y;
                g_Player.vram_flag |= VRAM_FLAG_UNK40 | TOUCHING_GROUND;
                if (plStatus &
                    (PLAYER_STATUS_BAT_FORM | PLAYER_STATUS_MIST_FORM)) {
                    return 0;
                }
#endif

                return 4;
            }

            // check collision from bottom
            if (flags & 2 && checks & 2 &&
                (pl->velocityY <= 0 || flags & 0x10)) {
                y = (s16)h - y;
                if (y < 0x10) {
                    pl->posY.i.hi += y;
#if STAGE == STAGE_ST0
                    g_Player.vram_flag |= VRAM_FLAG_UNK40 | TOUCHING_CEILING;
#else
                    D_80097488.y.i.hi += y;
                    g_Player.vram_flag |= VRAM_FLAG_UNK40 | TOUCHING_CEILING;
                    if (plStatus &
                        (PLAYER_STATUS_BAT_FORM | PLAYER_STATUS_MIST_FORM)) {
                        return 0;
                    }
#endif
                    return 2;
                }
            }
        }

        // check collision from the sides
        if (y && y != h && flags & 1) {
            if (checks & 1) {
                x = (s16)w - x;
                if (flags & 8 && x > 2) {
                    x = 2;
                }
                pl->posX.i.hi += x;
#if STAGE != STAGE_ST0
                D_80097488.x.i.hi += x;
                g_Player.vram_flag |= VRAM_FLAG_UNK40 | TOUCHING_L_WALL;
#endif
                return 1;
            } else {
                if (flags & 8 && x > 2) {
                    x = 2;
                }
                pl->posX.i.hi -= x;
#if STAGE != STAGE_ST0

                D_80097488.x.i.hi -= x;
                g_Player.vram_flag |= VRAM_FLAG_UNK40 | TOUCHING_R_WALL;
#endif
                return 1;
            }
        }
    }
    return 0;
}

void ReplaceBreakableWithItemDrop(Entity* self) {
    u16 params;

    PreventEntityFromRespawning(self);

#if STAGE != STAGE_ST0
    if (!(g_Status.relics[RELIC_CUBE_OF_ZOE] & 2)) {
        DestroyEntity(self);
        return;
    }
#endif

    params = self->params &= 0xFFF;

    if (params < 0x80) {
        self->entityId = E_PRIZE_DROP;
        self->pfnUpdate = (PfnEntityUpdate)EntityPrizeDrop;
        self->poseTimer = 0;
        self->pose = 0;
    } else {
        self->entityId = E_EQUIP_ITEM_DROP;
        self->pfnUpdate = (PfnEntityUpdate)EntityEquipItemDrop;
        params -= 0x80;
    }

    self->params = params;
    self->unk6D[0] = 0x10;
    self->step = 0;
}
