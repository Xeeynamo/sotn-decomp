#include "nz0.h"

static s16 D_80181978[] = {
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

#include "../../destroy_entity.h"
#include "../../destroy_entities_from_index.h"
#include "../prevent_entity_from_respawning.h"
#include "../animate_entity.h"

u8 func_801BCAD4(u8 frames[], Entity* self, u8 arg2) {
    u16 animFrameStart = self->animFrameIdx * 2;
    u8* var_s1 = &frames[animFrameStart];
    s16 var_a1 = 0;

    if (self->animFrameDuration == 0) {
        if (*var_s1 != 0) {
            if (*var_s1 == 0xFF) {
                return 0;
            }
            self->animFrameDuration = *var_s1++ + (u8)self->ext.stub[0x3F];
            self->animCurFrame = *var_s1++;
            self->animFrameIdx++;
            var_a1 = 128;
        } else {
            var_s1 = frames;
            self->animFrameIdx = 0;
            self->animFrameDuration = 0;
            self->ext.stub[0x3F] = (arg2 * Random()) >> 8;
            self->animFrameDuration = *var_s1++ + (u8)self->ext.stub[0x3F];
            self->animCurFrame = *var_s1;
            self->animFrameIdx++;
            return 0;
        }
    }
    self->animFrameDuration--;
    self->animCurFrame = var_s1[-1];
    var_a1 |= 1;
    return var_a1;
}

#include "../get_distance_to_player_x.h"

#include "../get_distance_to_player_y.h"

#include "../get_side_to_player.h"

#include "../move_entity.h"

#include "../fall_entity.h"

s32 func_801BCCFC(u16* sensors) {
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
                            g_CurrentEntity->posY.i.hi =
                                (u16)g_CurrentEntity->posY.i.hi + 4 + col.unk18;
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
                    g_CurrentEntity->posY.i.hi =
                        g_CurrentEntity->posY.i.hi + col.unk18;
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

s32 func_801BCF74(s16* posX) {
    Collider collider;
    s16 temp2;
    s16 temp4;
    s16 x, y;

    g_CurrentEntity->posX.val += g_CurrentEntity->velocityX;
    temp2 = g_CurrentEntity->posY.i.hi + 3;
    g_CurrentEntity->posY.i.hi = temp2;
    x = g_CurrentEntity->posX.i.hi + *posX;
    posX++;
    y = temp2 + *posX;
    g_api.CheckCollision(x, y, &collider, 0);
    if (!(collider.effects & EFFECT_SOLID)) {
        return 0;
    }
    posX++;

    g_CurrentEntity->posY.i.hi = g_CurrentEntity->posY.i.hi + collider.unk18;
    if (g_CurrentEntity->velocityX != 0) {
        if (g_CurrentEntity->velocityX < 0) {
            temp4 = x - *posX;
            posX++;
        } else {
            temp4 = x + *posX;
            posX++;
        }
        y = y + *posX - 7;
        g_api.CheckCollision(temp4, y, &collider, 0);
        if (collider.effects & EFFECT_SOLID) {
            if ((collider.effects & (EFFECT_UNK_8000 | EFFECT_UNK_0002)) ==
                EFFECT_UNK_0002) {
                g_CurrentEntity->posX.val =
                    g_CurrentEntity->posX.val - g_CurrentEntity->velocityX;
                g_CurrentEntity->velocityX = 0;
                return 0xFF;
            }
            return 0x61;
        }
        y += 15;
        g_api.CheckCollision(temp4, y, &collider, 0);
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

#include "../alloc_entity.h"

s32 func_801BD1BC(u8 arg0, s16 arg1) { return D_80181978[arg0] * arg1; }

s16 func_801BD1E8(u8 arg0) { return D_80181978[arg0]; } // Unique

void SetEntityVelocityFromAngle(s32 arg0, s16 arg1) {
    g_CurrentEntity->velocityX = func_801BD1BC(arg0, arg1);
    g_CurrentEntity->velocityY = func_801BD1BC(arg0 - 0x40, arg1);
}

u8 Ratan2Shifted(s16 x, s16 y) { return (ratan2(y, x) >> 4) + 0x40; }

u8 GetAngleBetweenEntitiesShifted(ObjInit* arg0, ObjInit* arg1) {
    u16 x, y;

    x = arg1->zPriority - arg0->zPriority;
    y = arg1->palette - arg0->palette;

    return Ratan2Shifted(x, y);
}

u8 GetAnglePointToEntityShifted(s16 arg0, s16 arg1) {
    s16 x, y;

    x = arg0 - g_CurrentEntity->posX.i.hi;
    y = arg1 - g_CurrentEntity->posY.i.hi;

    return Ratan2Shifted(x, y);
}

#include "../adjust_value_within_threshold.h"

#include "../unk_entity_func0.h"

u16 Ratan2(s16 x, s16 y) { return ratan2(y, x); }

#include "../get_angle_between_entities.h"

u16 GetAnglePointToEntity(s32 x, s32 y) {
    s16 diffX = x - (u16)g_CurrentEntity->posX.i.hi;
    s16 diffY = y - (u16)g_CurrentEntity->posY.i.hi;
    return ratan2(diffY, diffX);
}

#include "../get_normalized_angle.h"

#include "../set_step.h"

#include "../set_sub_step.h"

void EntityExplosionSpawn(u16 arg0, u16 sfxId) {
    if (sfxId != 0) {
        func_801C29B0(sfxId);
    }

    if (arg0 == 0xFF) {
        DestroyEntity(g_CurrentEntity);
        return;
    }

    g_CurrentEntity->entityId = E_EXPLOSION;
    g_CurrentEntity->pfnUpdate = (PfnEntityUpdate)EntityExplosion;
    g_CurrentEntity->params = arg0;
    g_CurrentEntity->animCurFrame = 0;
    g_CurrentEntity->drawFlags = 0;
    g_CurrentEntity->step = 0;
    g_CurrentEntity->step_s = 0;
}

#include "../init_entity.h"

#include "../entity_dummy.h"

s32 func_801BD720(u16* hitSensors, s16 sensorCount) {
    Collider collider;
    s16 i;
    s32 velocityX;
    u16 temp_a1;
    s16 x;
    s16 y;

    velocityX = g_CurrentEntity->velocityX;
    if (velocityX != 0) {
        x = g_CurrentEntity->posX.i.hi;
        y = g_CurrentEntity->posY.i.hi;
        for (i = 0; i < sensorCount; i++) {
            if (velocityX < 0) {
                s16 newX = x + *hitSensors++;
                x = newX;
            } else {
                s16 newX = x - *hitSensors++;
                x = newX;
            }

            y += *hitSensors++;
            g_api.CheckCollision(x, y, &collider, 0);
            if (collider.effects & EFFECT_UNK_0002 &&
                ((!(collider.effects & EFFECT_UNK_8000)) || (i != 0))) {
                return 2;
            }
        }
        return 0;
    }
}

#include "../check_field_collision.h"

#include "../get_player_collision_with.h"

#include "../replace_breakable_with_item_drop.h"
