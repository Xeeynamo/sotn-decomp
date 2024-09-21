#include "chi.h"

/*
 * File: entity_damage_display.c
 * Overlay: CHI
 * Description: Abandoned Mine
 */

u16 g_eDamageDisplayClut[] = {
    PAL_DRA(0x1B2), PAL_DRA(0x1B3), PAL_DRA(0x1B6), PAL_DRA(0x1B7),
    PAL_DRA(0x1B4), PAL_DRA(0x1B5), PAL_DRA(0x1B0), PAL_DRA(0x1B1),
};

//TODO: Centralize this instead of what's in ../entity_damage_display.h? (it's missing data?)
#include "../entity_damage_display.h"

#include "../create_entity.h"

#include "../e_red_door.h"

#include "../entity.h"

// [Duplicate]
u8 func_801A1474(u8 frames[], Entity* self, u8 arg2) {
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

// "Current entity" functions?
#include "../get_distance_to_player_x.h"
#include "../get_distance_to_player_y.h"
#include "../get_side_to_player.h"
#include "../move_entity.h"
#include "../fall_entity.h"

// [Duplicate]
s32 func_801A169C(u16* sensors) {
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

// [Duplicate]
s32 func_801A1914(s16* posX) {
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

#include "../../alloc_entity.h"

s16 D_80180E24[] = {
    0x0000, 0x0065, 0x00C9, 0x012D, 0x0191, 0x01F5, 0x0259, 0x02BC,
    0x031F, 0x0381, 0x03E3, 0x0444, 0x04A5, 0x0505, 0x0564, 0x05C2,
    0x061F, 0x067C, 0x06D7, 0x0732, 0x078B, 0x07E3, 0x083A, 0x088F,
    0x08E4, 0x0937, 0x0988, 0x09D8, 0x0A26, 0x0A73, 0x0ABF, 0x0B08,
    0x0B50, 0x0B97, 0x0BDB, 0x0C1E, 0x0C5E, 0x0C9D, 0x0CDA, 0x0D15,
    0x0D4E, 0x0D85, 0x0DB9, 0x0DEC, 0x0E1C, 0x0E4B, 0x0E77, 0x0EA1,
    0x0EC8, 0x0EEE, 0x0F11, 0x0F31, 0x0F50, 0x0F6C, 0x0F85, 0x0F9C,
    0x0FB1, 0x0FC4, 0x0FD4, 0x0FE1, 0x0FEC, 0x0FF5, 0x0FFB, 0x0FFF,
    0x1000, 0x0FFF, 0x0FFB, 0x0FF5, 0x0FEC, 0x0FE1, 0x0FD4, 0x0FC4,
    0x0FB1, 0x0F9C, 0x0F85, 0x0F6C, 0x0F50, 0x0F31, 0x0F11, 0x0EEE,
    0x0EC8, 0x0EA1, 0x0E77, 0x0E4B, 0x0E1C, 0x0DEC, 0x0DB9, 0x0D85,
    0x0D4E, 0x0D15, 0x0CDA, 0x0C9D, 0x0C5E, 0x0C1E, 0x0BDB, 0x0B97,
    0x0B50, 0x0B08, 0x0ABF, 0x0A73, 0x0A26, 0x09D8, 0x0988, 0x0937,
    0x08E4, 0x088F, 0x083A, 0x07E3, 0x078B, 0x0732, 0x06D7, 0x067C,
    0x061F, 0x05C2, 0x0564, 0x0505, 0x04A5, 0x0444, 0x03E3, 0x0381,
    0x031F, 0x02BC, 0x0259, 0x01F5, 0x0191, 0x012D, 0x00C9, 0x0065,
    0x0000, 0xFF9B, 0xFF37, 0xFED3, 0xFE6F, 0xFE0B, 0xFDA7, 0xFD44,
    0xFCE1, 0xFC7F, 0xFC1D, 0xFBBC, 0xFB5B, 0xFAFB, 0xFA9C, 0xFA3E,
    0xF9E1, 0xF984, 0xF929, 0xF8CE, 0xF875, 0xF81D, 0xF7C6, 0xF771,
    0xF71C, 0xF6C9, 0xF678, 0xF628, 0xF5DA, 0xF58D, 0xF541, 0xF4F8,
    0xF4B0, 0xF469, 0xF425, 0xF3E2, 0xF3A2, 0xF363, 0xF326, 0xF2EB,
    0xF2B2, 0xF27B, 0xF247, 0xF214, 0xF1E4, 0xF1B5, 0xF189, 0xF15F,
    0xF138, 0xF112, 0xF0EF, 0xF0CF, 0xF0B0, 0xF094, 0xF07B, 0xF064,
    0xF04F, 0xF03C, 0xF02C, 0xF01F, 0xF014, 0xF00B, 0xF005, 0xF001,
    0xF000, 0xF001, 0xF005, 0xF00B, 0xF014, 0xF01F, 0xF02C, 0xF03C,
    0xF04F, 0xF064, 0xF07B, 0xF094, 0xF0B0, 0xF0CF, 0xF0EF, 0xF112,
    0xF138, 0xF15F, 0xF189, 0xF1B5, 0xF1E4, 0xF214, 0xF247, 0xF27B,
    0xF2B2, 0xF2EB, 0xF326, 0xF363, 0xF3A2, 0xF3E2, 0xF425, 0xF469,
    0xF4B0, 0xF4F8, 0xF541, 0xF58D, 0xF5DA, 0xF628, 0xF678, 0xF6C9,
    0xF71C, 0xF771, 0xF7C6, 0xF81D, 0xF875, 0xF8CE, 0xF929, 0xF984,
    0xF9E1, 0xFA3E, 0xFA9C, 0xFAFB, 0xFB5B, 0xFBBC, 0xFC1D, 0xFC7F,
    0xFCE1, 0xFD44, 0xFDA7, 0xFE0B, 0xFE6F, 0xFED3, 0xFF37, 0xFF9B,
    0x0E01, 0x0000, 0x0302, 0x0406, 0x0505, 0x0605, 0x0704, 0x0803,
    0x0904, 0x0A05, 0x0B05, 0x0C06, 0x0307, 0x0406, 0x0505, 0x0605,
    0x0704, 0x0803, 0x0904, 0x0A05, 0x0B05, 0x0C06, 0x0D02, 0x0000,
    0x1404, 0x1507, 0x1606, 0x1703, 0x1803, 0x1906, 0x1502, 0x0000,
    0x1A01, 0x0000, 0x1B01, 0x0000, 0x1C01, 0x0000, 0x1D01, 0x0000,
    0x1E01, 0x0000, 0x1F01, 0x0000, 0x2001, 0x0000, 0x2101, 0x0000,
    0x2202, 0x2302, 0x2402, 0x2502, 0x2602, 0x2702, 0x2802, 0x2902,
    0x0000, 0x0000, 0x0F1A, 0x1006, 0x1104, 0x1202, 0x1104, 0x1006,
    0x0000, 0x0000, 0x1301, 0x0000, 0x2A05, 0x2B05, 0x2C05, 0x2D05,
    0x2E05, 0x2F05, 0x3005, 0x3105, 0x0000, 0x0000, 0x3205, 0x3305,
    0x3405, 0x3505, 0x3605, 0x3705, 0x3805, 0x3905, 0x0000, 0x0000,
    0x3A05, 0x3B05, 0x3C05, 0x3D05, 0x3E05, 0x3F05, 0x4005, 0x4105,
    0x0000, 0x0000, 0x4205, 0x4305, 0x4405, 0x4505, 0x4605, 0x4705,
    0x4805, 0x4905, 0x0000, 0x0000, 0x4A05, 0x4B05, 0x4C05, 0x4D05,
    0x4E05, 0x4F05, 0x5005, 0x5105, 0x0000, 0x0000, 0x5205, 0x5305,
    0x5405, 0x5505, 0x5605, 0x5705, 0x5805, 0x5905, 0x0000, 0x0000,
    0x5A05, 0x5B05, 0x5C05, 0x5D05, 0x5E05, 0x5F05, 0x6005, 0x6105,
    0x0000, 0x0000, 0x6205, 0x6305, 0x6405, 0x6505, 0x6605, 0x6705,
    0x6805, 0x6905, 0x0000, 0x0000, 0x6A05, 0x6B05, 0x6C05, 0x6D05 
};
// [Duplicate]
s32 func_801A1B5C(u8 arg0, s16 arg1) { return D_80180E24[arg0] * arg1; }
// [Duplicate]
s16 func_801A1B88(u8 arg0) { return D_80180E24[arg0]; }
// [Duplicate]
void func_801A1BA4(s32 arg0, s16 arg1) {
    g_CurrentEntity->velocityX = func_801A1B5C(arg0 & 0xFF, arg1);
    g_CurrentEntity->velocityY = func_801A1B5C((arg0 - 0x40) & 0xFF, arg1);
}

// [Duplicate]
u8 func_801A1C10(s16 x, s16 y) { return (ratan2(y, x) >> 4) + 0x40; }

// [Duplicate]
u8 func_801A1C48(Entity* arg0, Entity* arg1) {
    u16 x;
    u16 y;

    x = arg1->posX.i.hi - arg0->posX.i.hi;
    y = arg1->posY.i.hi - arg0->posY.i.hi;

    return func_801A1C10(x, y);
}

// [Duplicate]
// [Almost duplicate of func_801A1E24 - x/y are swapped]
u16 func_801A1C90(s16 x, s16 y) {
    x -= g_CurrentEntity->posX.i.hi;
    y -= g_CurrentEntity->posY.i.hi;

    return func_801A1C10(x, y);
}

#include "../adjust_value_within_threshold.h"
#include "../unk_entity_func0.h"

// [Duplicate]
u16 func_801A1DBC(s16 arg0, s16 arg1) { return ratan2(arg1, arg0); }

#include "../get_angle_between_entities.h"
// [Duplicate]
// [Almost duplicate of func_801A1C90 - x/y are swapped]
u16 func_801A1E24(s16 x, s16 y) {
    x -= g_CurrentEntity->posX.i.hi;
    y -= g_CurrentEntity->posY.i.hi;

    return ratan2(y, x);
}
#include "../get_normalized_angle.h"

#include "../set_step.h"
#include "../set_sub_step.h"

// [Duplicate]
// [Migrate to common file once func_801A3520 is EntityExplosion?]
// func_801A1F08
void func_801A3520(void);
void EntityExplosionSpawn(u16 arg0, u16 arg1) {
    Entity* entity;

    if (arg1 != 0) {
        PlaySfxWithPosArgs(arg1);
    }
    if (arg0 == 0xFF) {
        DestroyEntity(g_CurrentEntity);
        return;
    }
    entity = g_CurrentEntity;
    entity->drawFlags = 0;
    entity->entityId = 2;
    //entity->pfnUpdate = EntityExplosion;
    entity->pfnUpdate = func_801A3520;
    entity->params = arg0;
    entity->animCurFrame = 0;
    g_CurrentEntity->step = 0;
    g_CurrentEntity->step_s = 0;
}
//#include "../entity_explosion_spawn.h"

#include "../init_entity.h"
#include "../entity_dummy.h"

// [Duplicate]
// func_801A20C0
s32 func_801A20C0(u16* hitSensors, s16 sensorCount) {
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

// [Duplicate]
// [Migrate to common file once func_801A2CAC is EntityPrizeDrop and func_801A36C0 is EntityEquipItemDrop?]
// func_801A2684
void func_801A2CAC(void);
void func_801A36C0(void);

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
        //self->pfnUpdate = (PfnEntityUpdate)EntityPrizeDrop;
        self->pfnUpdate = (PfnEntityUpdate)func_801A2CAC;
        self->animFrameDuration = 0;
        self->animFrameIdx = 0;
    } else {
        self->entityId = E_EQUIP_ITEM_DROP;
        //self->pfnUpdate = (PfnEntityUpdate)EntityEquipItemDrop;
        self->pfnUpdate = (PfnEntityUpdate)func_801A36C0;
        params -= 0x80;
    }

    self->params = params;
    self->unk6D[0] = 0x10;
    self->step = 0;
}
//#include "../replace_breakable_with_item_drop.h"

// [Duplicate]
// func_801A273C
void func_801A273C(void) {
    s32 temp_v1;
    Entity* entity;

    entity = g_CurrentEntity;
    if (entity->velocityY >= 0) {
        temp_v1 =
            entity->ext.generic.unk88.S16.unk0 + entity->ext.generic.unk84.unk;
        entity->ext.generic.unk84.unk = temp_v1;
        entity->velocityX = temp_v1;
        if (temp_v1 == 0x10000 || temp_v1 == -0x10000) {
            entity->ext.generic.unk88.S16.unk0 =
                -entity->ext.generic.unk88.S16.unk0;
        }
        entity = g_CurrentEntity;
    }

    if (entity->velocityY < FIX(0.25)) {
        entity->velocityY += FIX(0.125);
    }
}
// [Duplicate]
// func_801A27C0
void func_801A27C0(u16 arg0) {
    Collider collider;

    if (g_CurrentEntity->velocityX < 0) {
        g_api.CheckCollision(g_CurrentEntity->posX.i.hi,
                             g_CurrentEntity->posY.i.hi - 7, &collider, 0);
        if (collider.effects & EFFECT_NOTHROUGH) {
            g_CurrentEntity->velocityY = 0;
        }
    }

    g_api.CheckCollision(g_CurrentEntity->posX.i.hi,
                         g_CurrentEntity->posY.i.hi + 7, &collider, 0);

    if (arg0) {
        if (!(collider.effects & EFFECT_NOTHROUGH)) {
            MoveEntity();
            FallEntity();
            return;
        }

        g_CurrentEntity->velocityX = 0;
        g_CurrentEntity->velocityY = 0;

        if (collider.effects & EFFECT_QUICKSAND) {
            g_CurrentEntity->posY.val += FIX(0.125);
            return;
        }

        g_CurrentEntity->posY.i.hi += collider.unk18;
        return;
    }

    if (!(collider.effects & EFFECT_NOTHROUGH)) {
        MoveEntity();
        func_801A273C();
    }
}