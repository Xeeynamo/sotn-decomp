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
INCLUDE_ASM("st/chi/nonmatchings/entity_damage_display", func_801A291C);    // CollectHeart()
INCLUDE_ASM("st/chi/nonmatchings/entity_damage_display", func_801A299C);    // CollectGold()
INCLUDE_ASM("st/chi/nonmatchings/entity_damage_display", func_801A2A78);    // CollectSubweapon()
INCLUDE_ASM("st/chi/nonmatchings/entity_damage_display", func_801A2B90);    // CollectHeartVessel()
INCLUDE_ASM("st/chi/nonmatchings/entity_damage_display", func_801A2C34);    // CollectLifeVessel()
INCLUDE_ASM("st/chi/nonmatchings/entity_damage_display", func_801A2C84);    // DestroyCurrentEntity()

// POSSIBLE FILE BREAK

INCLUDE_ASM("st/chi/nonmatchings/entity_damage_display", func_801A2CAC);    // EntityPrizeDrop()
INCLUDE_ASM("st/chi/nonmatchings/entity_damage_display", func_801A3520);    // EntityExplosion()
//#include "../entity_explosion.h"
#include "../blink_item.h"
INCLUDE_ASM("st/chi/nonmatchings/entity_damage_display", func_801A36C0);    // EntityEquipItemDrop()
//#include "../e_collect.h"

#include "../blit_char.h"

INCLUDE_ASM("st/chi/nonmatchings/entity_damage_display", func_801A3F58);    // EntityRelicOrb()
//#include "../entity_relic_orb.h"

INCLUDE_ASM("st/chi/nonmatchings/entity_damage_display", func_801A4A28);    // EntityHeartDrop()

INCLUDE_ASM("st/chi/nonmatchings/entity_damage_display", func_801A4B50);    // EntityMessageBox()
//#include "../entity_message_box.h"

#include "../check_coll_offsets.h"

INCLUDE_ASM("st/chi/nonmatchings/entity_damage_display", func_801A519C);    // EntityUnkId13()
//#include "../entity_unkId13.h"

INCLUDE_ASM("st/chi/nonmatchings/entity_damage_display", func_801A52AC);    // EntityUnkId14Spawner()
//#include "../entity_unkId14_spawner.h"

INCLUDE_ASM("st/chi/nonmatchings/entity_damage_display", func_801A53DC);    // EntityUnkId15Spawner()
//#include "../entity_unkId15_spawner.h"

INCLUDE_ASM("st/chi/nonmatchings/entity_damage_display", func_801A54C4);    // EntityUnkId14()
//#include "../entity_unkId14.h"

INCLUDE_ASM("st/chi/nonmatchings/entity_damage_display", func_801A55B4);    // EntityUnkId15()
//#include "../entity_unkId15.h"

INCLUDE_ASM("st/chi/nonmatchings/entity_damage_display", func_801A56A8);    // EntityOlroxDrool()
//#include "../entity_olrox_drool.h"

INCLUDE_ASM("st/chi/nonmatchings/entity_damage_display", func_801A58D8);    // [Duplicate]

INCLUDE_ASM("st/chi/nonmatchings/entity_damage_display", func_801A59D4);    // [Duplicate]

INCLUDE_ASM("st/chi/nonmatchings/entity_damage_display", func_801A5F54);    // EntityIntenseExplosion()
//#include "../entity_intense_explosion.h"

INCLUDE_ASM("st/chi/nonmatchings/entity_damage_display", func_801A6054);    // [Duplicate]

// [Duplicate]
void func_801A6120(u16 entityId, Entity* src, Entity* dst)
{
    DestroyEntity(dst);
    dst->entityId = entityId;
    dst->pfnUpdate = PfnEntityUpdates[entityId - 1];
    dst->posX.i.hi = src->posX.i.hi;
    dst->posY.i.hi = src->posY.i.hi;
    dst->unk5A = src->unk5A;
    dst->zPriority = src->zPriority;
    dst->animSet = src->animSet;
    dst->flags = FLAG_UNK_2000 | FLAG_UNK_01000000 | FLAG_UNK_04000000 |
                 FLAG_UNK_08000000 | FLAG_DESTROY_IF_BARELY_OUT_OF_CAMERA |
                 FLAG_DESTROY_IF_OUT_OF_CAMERA;

    if (src->palette & 0x8000) {
        dst->palette = src->hitEffect;
    } else {
        dst->palette = src->palette;
    }
}

INCLUDE_ASM("st/chi/nonmatchings/entity_damage_display", func_801A61E8);    // [Duplicate]

INCLUDE_ASM("st/chi/nonmatchings/entity_damage_display", func_801A62A0);    // EntityBigRedFireball()
//#include "../entity_big_red_fireball.h"

INCLUDE_ASM("st/chi/nonmatchings/entity_damage_display", func_801A6478);    // UnkRecursivePrimFunc1()
//#include "../unk_recursive_primfunc_1.h"

INCLUDE_ASM("st/chi/nonmatchings/entity_damage_display", func_801A6A58);    // UnkRecursivePrimFunc2()
//#include "../unk_recursive_primfunc_2.h"

#include "../clut_lerp.h"

#include "../play_sfx_with_pos_args.h"

INCLUDE_ASM("st/chi/nonmatchings/entity_damage_display", func_801A7448);    // EntitySoulStealOrb()
//#include "../entity_soul_steal_orb.h"

INCLUDE_ASM("st/chi/nonmatchings/entity_damage_display", func_801A77DC);    // EntityEnemyBlood()
//#include "../entity_enemy_blood.h"

INCLUDE_ASM("st/chi/nonmatchings/entity_damage_display", func_801A7C8C);    // EntityRoomForeground()
//#include "../e_room_fg.h"

#include "../bottom_corner_text.h"

INCLUDE_ASM("st/chi/nonmatchings/entity_damage_display", func_801A80A8);

// POSSIBLE FILE BREAK

INCLUDE_ASM("st/chi/nonmatchings/entity_damage_display", func_801A813C);    // [Entity]

INCLUDE_ASM("st/chi/nonmatchings/entity_damage_display", func_801A8DE8);    // [Entity]

INCLUDE_ASM("st/chi/nonmatchings/entity_damage_display", func_801A8EAC);    // [Entity]

INCLUDE_ASM("st/chi/nonmatchings/entity_damage_display", func_801A93D4);    // [Entity]

INCLUDE_ASM("st/chi/nonmatchings/entity_damage_display", func_801A9588);    // [Entity]

INCLUDE_ASM("st/chi/nonmatchings/entity_damage_display", func_801A97C8);    // [Entity]

INCLUDE_ASM("st/chi/nonmatchings/entity_damage_display", func_801A9D40);    // [Entity]

INCLUDE_ASM("st/chi/nonmatchings/entity_damage_display", func_801A9E94);    // [Entity]

INCLUDE_ASM("st/chi/nonmatchings/entity_damage_display", func_801AA020);    // [Entity]

INCLUDE_ASM("st/chi/nonmatchings/entity_damage_display", func_801AA390);    // [Entity]

INCLUDE_ASM("st/chi/nonmatchings/entity_damage_display", func_801AB0C0);    // [Entity]

INCLUDE_ASM("st/chi/nonmatchings/entity_damage_display", func_801AB548);

// POSSIBLE FILE BREAK

INCLUDE_ASM("st/chi/nonmatchings/entity_damage_display", func_801AB7CC);    // [Entity]

INCLUDE_ASM("st/chi/nonmatchings/entity_damage_display", func_801AC074);    // [Entity]

INCLUDE_ASM("st/chi/nonmatchings/entity_damage_display", func_801AC730);    // [Entity]

INCLUDE_ASM("st/chi/nonmatchings/entity_damage_display", func_801ACB6C);    // [Entity]

INCLUDE_ASM("st/chi/nonmatchings/entity_damage_display", func_801ACEF4);    // [Entity]

s32 func_801AE70C(Primitive* prim, u8 arg1);
void StageNamePopupHelper(Primitive* prim)  // [Duplicate]
{
    u8 xPos;
    s32 i;
    s32 j;

    switch (prim->p3) {
    case 0:
        if (prim->p1 < 0x80) {
            if (--prim->p1 == 0) {
                prim->p3 = 1;
            }
        } else {
            if (++prim->p1 == 0) {
                prim->p3 = 2;
            }
        }

        if (prim->p3 != 0) {
            u8* dst = prim->p3 == 1 ? &prim->r1 : &prim->r0;
            for (i = 0; i < 2; i++) {
                for (j = 0; j < 3; j++) {
                    dst[j] = 0x50;
                }
                dst += 0x18;
            }
            prim->p2 = 0;
        }
        break;
    case 1:
        if (prim->p2 < 0x14) {
            prim->p2++;
        }
        xPos = prim->p2 / 5;
        prim->x2 = prim->x0 = prim->x0 + xPos;
        prim->x1 = prim->x1 + xPos;
        prim->x3 = prim->x0;
        func_801AE70C(prim, 4);
        break;
    case 2:
        if (prim->p2 < 0x14) {
            prim->p2++;
        }
        xPos = prim->p2 / 5;
        prim->x2 = prim->x0 = prim->x0 - xPos;
        prim->x1 = prim->x1 - xPos;
        prim->x3 = prim->x0;
        func_801AE70C(prim, 4);
        break;
    }
}

// POSSIBLE FILE BREAK

//#ifndef NON_MATCHING
INCLUDE_ASM("st/chi/nonmatchings/entity_damage_display", func_801AD2BC);    // EntityStageNamePopup()
//#else
// /*?*/ void func_801AD0EC(?*);                                // extern
// extern u8 D_8003BE40;
// extern s8 D_8019B3C0;
// extern s8 D_8019B3D0;
// extern u16 EntityInit_80180640;

// void func_801AD2BC(Entity* arg0)
// {
//     Primitive* temp_s0;
//     Primitive* temp_s0_2;
//     Primitive* temp_s0_3;
//     Primitive* temp_s0_6;
//     Primitive* var_s0;
//     Primitive* var_s0_10;
//     Primitive* var_s0_11;
//     Primitive* var_s0_2;
//     Primitive* var_s0_3;
//     Primitive* var_s0_6;
//     Primitive* var_s0_7;
//     Primitive* var_s0_8;
//     Primitive* var_s0_9;
//     s16 temp_a0_2;
//     s16 temp_a0_3;
//     s16 temp_v0;
//     s16 temp_v0_10;
//     s16 temp_v0_12;
//     s16 temp_v0_17;
//     s16 temp_v0_18;
//     s16 temp_v0_19;
//     s16 temp_v0_4;
//     s16 temp_v0_5;
//     s16 temp_v0_6;
//     s16 temp_v0_7;
//     s16 temp_v0_8;
//     s16 temp_v1_2;
//     s16 temp_v1_3;
//     s16 var_v0_2;
//     s16 var_v1;
//     s16 var_v1_2;
//     s32 temp_s0_4;
//     s32 temp_s0_5;
//     s32 temp_v0_15;
//     s32 temp_v0_20;
//     s32 temp_v0_21;
//     s32 temp_v0_22;
//     s32 temp_v0_3;
//     s32 var_a0;
//     s32 var_s0_4;
//     s32 var_s0_5;
//     s32 var_s1;
//     s32 var_s1_10;
//     s32 var_s1_11;
//     s32 var_s1_12;
//     s32 var_s1_13;
//     s32 var_s1_3;
//     s32 var_s1_4;
//     s32 var_s1_5;
//     s32 var_s1_6;
//     s32 var_s1_7;
//     s32 var_s1_8;
//     s32 var_s1_9;
//     s32 var_v0;
//     u16 temp_a0;
//     u16 temp_v0_2;
//     u16 temp_v1;
//     u16 temp_v1_4;
//     u8 temp_a1;
//     u8 temp_a1_2;
//     u8 temp_a2;
//     u8 temp_v0_11;
//     u8 temp_v0_13;
//     u8 temp_v0_14;
//     u8 temp_v0_16;
//     u8 temp_v0_9;
//     u8 var_a1;
//     u8 var_a1_2;
//     u8 var_s1_2;

//     temp_a0 = arg0->step;
//     switch (temp_a0) {                              // switch 1; irregular
//         case 0:                                     // switch 1
//             if ((g_DemoMode == Demo_None) && (D_8003BE40 == 0)) {
//                 InitializeEntity(&EntityInit_80180640);
//                 temp_v0 = g_api_AllocPrimitives(PRIM_GT4, 0x57);
//                 if (temp_v0 != -1) {
//                     var_s0 = &g_PrimBuf[temp_v0];
//                     arg0->primIndex = (s32) temp_v0;
//                     arg0->ext.prim = var_s0;
//                     arg0->flags |= 0x800000;
//                     if (var_s0 != NULL) {
//                         do {
//                             var_s0->drawMode = 8;
//                             var_s0 = var_s0->next;
//                         } while (var_s0 != NULL);
//                     }
//                     var_s0_2 = arg0->ext.prim;
//                     var_s1 = 0;
//                     do {
//                         temp_v0_2 = 0xC0 - var_s1;
//                         var_s1 += 1;
//                         var_s0_2->tpage = 0x11;
//                         var_s0_2->clut = 0x19F;
//                         var_s0_2->u2 = 4;
//                         var_s0_2->u0 = 4;
//                         var_s0_2->u3 = 0x78;
//                         var_s0_2->u1 = 0x78;
//                         var_s0_2->v1 = 0;
//                         var_s0_2->v0 = 0;
//                         var_s0_2->v3 = 0x28;
//                         var_s0_2->v2 = 0x28;
//                         var_s0_2->x0 = 0xC;
//                         var_s0_2->x2 = 0xC;
//                         var_s0_2->y0 = 0x9D;
//                         var_s0_2->y1 = 0x9D;
//                         var_s0_2->x1 = 0x80;
//                         var_s0_2->x3 = 0x80;
//                         var_s0_2->y2 = 0xC5;
//                         var_s0_2->y3 = 0xC5;
//                         var_s0_2->priority = temp_v0_2;
//                         var_s0_2->drawMode = 8;
//                         temp_s0 = var_s0_2->next;
//                         temp_s0->tpage = 0x11;
//                         temp_s0->clut = 0x19F;
//                         temp_s0->u2 = 8;
//                         temp_s0->u0 = 8;
//                         temp_s0->u3 = 0x7C;
//                         temp_s0->u1 = 0x7C;
//                         temp_s0->v1 = 0x40;
//                         temp_s0->v0 = 0x40;
//                         temp_s0->v3 = 0x68;
//                         temp_s0->v2 = 0x68;
//                         temp_s0->x0 = 0x80;
//                         temp_s0->x2 = 0x80;
//                         temp_s0->y0 = 0x9D;
//                         temp_s0->priority = temp_v0_2;
//                         temp_s0->y1 = 0x9D;
//                         temp_s0->x1 = 0xF4;
//                         temp_s0->x3 = 0xF4;
//                         temp_s0->y2 = 0xC5;
//                         temp_s0->y3 = 0xC5;
//                         temp_s0->drawMode = 8;
//                         var_s0_2 = temp_s0->next;
//                     } while (var_s1 < 2);
//                     var_s1_2 = 0;
//                     arg0->ext.generic.unk88.unk = var_s0_2;
//                     var_s0_2->u2 = 4;
//                     var_s0_2->u0 = 4;
//                     var_s0_2->u3 = 0x78;
//                     var_s0_2->u1 = 0x78;
//                     var_s0_2->tpage = 0x11;
//                     var_s0_2->clut = 0x19D;
//                     var_s0_2->v1 = 0;
//                     var_s0_2->v0 = 0;
//                     var_s0_2->v3 = 0x28;
//                     var_s0_2->v2 = 0x28;
//                     var_s0_2->x0 = 0xC;
//                     var_s0_2->x2 = 0xC;
//                     var_s0_2->y0 = 0x9D;
//                     var_s0_2->y1 = 0x9D;
//                     var_s0_2->x1 = 0x80;
//                     var_s0_2->x3 = 0x80;
//                     var_s0_2->y2 = 0xC5;
//                     var_s0_2->y3 = 0xC5;
//                     var_s0_2->priority = 0xBF;
//                     var_s0_2->drawMode = 8;
//                     temp_s0_2 = var_s0_2->next;
//                     temp_s0_2->clut = 0x19D;
//                     temp_s0_2->tpage = 0x11;
//                     temp_s0_2->u2 = 8;
//                     temp_s0_2->u0 = 8;
//                     temp_s0_2->u3 = 0x7C;
//                     temp_s0_2->u1 = 0x7C;
//                     temp_s0_2->v1 = 0x40;
//                     temp_s0_2->v0 = 0x40;
//                     temp_s0_2->v3 = 0x68;
//                     temp_s0_2->v2 = 0x68;
//                     temp_s0_2->x0 = 0x80;
//                     temp_s0_2->x2 = 0x80;
//                     temp_s0_2->y0 = 0x9D;
//                     temp_s0_2->y1 = 0x9D;
//                     temp_s0_2->x1 = 0xF4;
//                     temp_s0_2->x3 = 0xF4;
//                     temp_s0_2->y2 = 0xC5;
//                     temp_s0_2->y3 = 0xC5;
//                     temp_s0_2->priority = 0xBF;
//                     temp_s0_2->drawMode = 8;
//                     temp_s0_3 = temp_s0_2->next;
//                     arg0->ext.generic.unk84.unk = temp_s0_3;
//                     temp_s0_3->u0 = 0;
//                     temp_s0_3->u1 = 0x40;
//                     temp_s0_3->type = 3;
//                     temp_s0_3->tpage = 0x1A;
//                     temp_s0_3->clut = 0x15F;
//                     temp_s0_3->v0 = 0xC0;
//                     temp_s0_3->v1 = 0xC0;
//                     temp_s0_3->v2 = 0xFF;
//                     temp_s0_3->v3 = 0xFF;
//                     temp_s0_3->y0 = 0x9B;
//                     temp_s0_3->y1 = 0x9B;
//                     temp_s0_3->y2 = 0xC7;
//                     temp_s0_3->y3 = 0xC7;
//                     temp_s0_3->x0 = 0xC;
//                     temp_s0_3->x2 = 0xC;
//                     temp_s0_3->x1 = 0xF4;
//                     temp_s0_3->x3 = 0xF4;
//                     temp_s0_3->r0 = 0x10;
//                     temp_s0_3->g0 = 0x28;
//                     temp_s0_3->u2 = temp_s0_3->u0;
//                     temp_s0_3->u3 = temp_s0_3->u1;
//                     temp_s0_3->b0 = 0;
//                     temp_s0_3->r2 = 8;
//                     temp_s0_3->g2 = 0;
//                     temp_s0_3->b2 = 0x38;
//                     temp_s0_3->priority = 0xB0;
//                     temp_s0_3->drawMode = 0x1D;
//                     temp_s0_3->unk10 = (s32) temp_s0_3->unk4;
//                     temp_s0_3->unk28 = (s32) temp_s0_3->unk1C;
//                     var_s0_3 = temp_s0_3->next;
//                     arg0->ext.factory.parent = var_s0_3;
//                     var_v1 = 0x9D;
//                     do {
//                         temp_a0_2 = var_s1_2 + 0x9E;
//                         temp_a1 = var_s1_2;
//                         var_s1_2 += 1;
//                         var_s0_3->v3 = var_s1_2;
//                         var_s0_3->v2 = var_s1_2;
//                         var_s0_3->y0 = var_v1;
//                         var_s0_3->y1 = var_v1;
//                         var_s0_3->r0 = 0x78;
//                         var_s0_3->g0 = 0x78;
//                         var_s0_3->b0 = 0xA8;
//                         var_s0_3->y2 = temp_a0_2;
//                         var_s0_3->y3 = temp_a0_2;
//                         var_s0_3->v1 = temp_a1;
//                         var_s0_3->v0 = temp_a1;
//                         var_s0_3->priority = 0xC0;
//                         var_s0_3->tpage = 0x11;
//                         var_s0_3->clut = 0x19F;
//                         var_s0_3->x0 = 0xC;
//                         var_s0_3->x2 = 0xC;
//                         var_s0_3->x1 = 0x80;
//                         var_s0_3->x3 = 0x80;
//                         var_s0_3->u0 = 4;
//                         var_s0_3->u2 = 4;
//                         var_s0_3->u3 = 0x78;
//                         var_s0_3->u1 = 0x78;
//                         var_s0_3->drawMode = 0xC;
//                         var_s0_3->unk10 = (s32) var_s0_3->unk4;
//                         var_s0_3->unk1C = (s32) var_s0_3->unk4;
//                         var_s0_3->unk28 = (s32) var_s0_3->unk4;
//                         var_s0_3 = var_s0_3->next;
//                         var_v1 = var_s1_2 + 0x9D;
//                     } while ((s32) var_s1_2 < 0x28);
//                     var_s1_3 = 0;
//                     var_v1_2 = 0x9D;
//                     do {
//                         temp_a0_3 = var_s1_3 + 0x9E;
//                         temp_a1_2 = var_s1_3 + 0x40;
//                         var_s0_3->clut = 0x19F;
//                         var_s0_3->y0 = var_v1_2;
//                         var_s0_3->y1 = var_v1_2;
//                         var_s0_3->r0 = 0x78;
//                         var_s0_3->g0 = 0x78;
//                         var_s0_3->b0 = 0xA8;
//                         temp_a2 = var_s1_3 + 0x41;
//                         var_s0_3->y2 = temp_a0_3;
//                         var_s0_3->y3 = temp_a0_3;
//                         var_s1_3 += 1;
//                         var_s0_3->v1 = temp_a1_2;
//                         var_s0_3->v0 = temp_a1_2;
//                         var_s0_3->priority = 0xC0;
//                         var_s0_3->drawMode = 0xC;
//                         var_s0_3->tpage = 0x11;
//                         var_s0_3->x0 = 0x80;
//                         var_s0_3->x2 = 0x80;
//                         var_s0_3->x1 = 0xF4;
//                         var_s0_3->x3 = 0xF4;
//                         var_s0_3->u0 = 8;
//                         var_s0_3->u2 = 8;
//                         var_s0_3->u3 = 0x7C;
//                         var_s0_3->u1 = 0x7C;
//                         var_s0_3->v3 = temp_a2;
//                         var_s0_3->v2 = temp_a2;
//                         var_s0_3->unk10 = (s32) var_s0_3->unk4;
//                         var_s0_3->unk1C = (s32) var_s0_3->unk4;
//                         var_s0_3->unk28 = (s32) var_s0_3->unk4;
//                         var_s0_3 = var_s0_3->next;
//                         var_v1_2 = var_s1_3 + 0x9D;
//                     } while (var_s1_3 < 0x28);
//                     arg0->ext.generic.unk80.modeS32 = 0x20;
//                 case 1:                             // switch 1
//                     temp_v1 = arg0->step_s;
//                     switch (temp_v1) {
//                         case 0:
//                             temp_v0_3 = arg0->ext.generic.unk80.modeS32;
//                             if (temp_v0_3 != 0) {
//                                 arg0->ext.generic.unk80.modeS32 = temp_v0_3 - 1;
//                             } else {
//                                 temp_s0_4 = arg0->ext.generic.unk84.unk;
//                                 temp_s0_4->unk20 = 0x80;
//                                 temp_s0_4->unk8 = 0x80;
//                                 temp_s0_4->unk2C = 0x80;
//                                 temp_s0_4->unk14 = 0x80;
//                                 temp_s0_4->unk16 = 0xB1;
//                                 temp_s0_4->unkA = 0xB1;
//                                 temp_s0_4->unk2E = 0xB1;
//                                 temp_s0_4->unk22 = 0xB1;
//                                 temp_s0_4->unk32 = 0x15;
// block_78:
// block_79:
//                                 arg0->step_s += 1;
//                             }
//                             break;
//                         case 1:
//                             temp_s0_5 = arg0->ext.generic.unk84.unk;
//                             temp_v0_4 = temp_s0_5->unkA;
//                             var_a0 = 0;
//                             if (temp_v0_4 >= 0x9C) {
//                                 var_a0 = 1;
//                                 temp_v1_2 = temp_v0_4 - 4;
//                                 temp_s0_5->unkA = temp_v1_2;
//                                 temp_s0_5->unk16 = temp_v1_2;
//                                 temp_v0_5 = (u16) temp_s0_5->unk22 + 4;
//                                 temp_s0_5->unk22 = temp_v0_5;
//                                 temp_s0_5->unk2E = temp_v0_5;
//                             }
//                             temp_v0_6 = temp_s0_5->unk8;
//                             var_v0 = var_a0 & 0xFF;
//                             if (temp_v0_6 >= 0xD) {
//                                 temp_v1_3 = temp_v0_6 - 8;
//                                 temp_s0_5->unk8 = temp_v1_3;
//                                 temp_s0_5->unk20 = temp_v1_3;
//                                 temp_v0_7 = (u16) temp_s0_5->unk14 + 8;
//                                 temp_s0_5->unk14 = temp_v0_7;
//                                 temp_s0_5->unk2C = temp_v0_7;
//                                 var_v0 = (var_a0 | 1) & 0xFF;
//                             }
//                             if (var_v0 == 0) {
//                                 arg0->ext.generic.unk80.modeS32 = 0;
//                                 arg0->ext.factory.childId = 0;
//                                 arg0->ext.factory.unk92 = 0;
//                                 goto block_79;
//                             }
//                             break;
//                         case 2:
//                             temp_v0_8 = (u16) arg0->ext.factory.childId + 3;
//                             arg0->ext.factory.childId = temp_v0_8;
//                             var_s1_4 = 0;
//                             if (temp_v0_8 >= 0x80) {
//                                 arg0->step_s += 1;
//                             }
//                             var_s0_4 = arg0->ext.generic.unk88.unk;
//                             var_s0_4->unk32 = 0x75;
// loop_34:
//                             temp_v0_9 = (u8) arg0->ext.stub[0x14];
//                             var_s1_4 += 1;
//                             var_s0_4->unk2A = temp_v0_9;
//                             var_s0_4->unk29 = temp_v0_9;
//                             var_s0_4->unk28 = temp_v0_9;
//                             var_s0_4->unk1E = temp_v0_9;
//                             var_s0_4->unk1D = temp_v0_9;
//                             var_s0_4->unk1C = temp_v0_9;
//                             var_s0_4->unk12 = temp_v0_9;
//                             var_s0_4->unk11 = temp_v0_9;
//                             var_s0_4->unk10 = temp_v0_9;
//                             var_s0_4->unk6 = temp_v0_9;
//                             var_s0_4->unk5 = temp_v0_9;
//                             var_s0_4->unk4 = temp_v0_9;
//                             var_s0_4 = var_s0_4->unk0;
//                             if (var_s1_4 < 2) {
//                                 var_s0_4->unk32 = 0x75;
//                                 goto loop_34;
//                             }
//                             break;
//                         case 3:
//                             temp_v0_10 = (u16) arg0->ext.factory.childId - 2;
//                             arg0->ext.factory.childId = temp_v0_10;
//                             var_s1_5 = 0;
//                             if (temp_v0_10 & 0x8000) {
//                                 arg0->ext.factory.childId = 0;
//                             }
//                             var_s0_5 = arg0->ext.generic.unk88.unk;
//                             do {
//                                 var_s0_5->unk32 = 0x35;
//                                 temp_v0_11 = (u8) arg0->ext.stub[0x14];
//                                 var_s1_5 += 1;
//                                 var_s0_5->unk2A = temp_v0_11;
//                                 var_s0_5->unk29 = temp_v0_11;
//                                 var_s0_5->unk28 = temp_v0_11;
//                                 var_s0_5->unk1E = temp_v0_11;
//                                 var_s0_5->unk1D = temp_v0_11;
//                                 var_s0_5->unk1C = temp_v0_11;
//                                 var_s0_5->unk12 = temp_v0_11;
//                                 var_s0_5->unk11 = temp_v0_11;
//                                 var_s0_5->unk10 = temp_v0_11;
//                                 var_s0_5->unk6 = temp_v0_11;
//                                 var_s0_5->unk5 = temp_v0_11;
//                                 var_s0_5->unk4 = temp_v0_11;
//                                 var_s0_5 = var_s0_5->unk0;
//                             } while (var_s1_5 < 2);
//                             temp_v0_12 = arg0->ext.factory.childId;
//                             if (temp_v0_12 != 0) {
//                                 var_v0_2 = 0x80 - temp_v0_12;
//                             } else {
//                                 var_v0_2 = (u16) arg0->ext.factory.unk92 + 4;
//                             }
//                             arg0->ext.factory.unk92 = var_v0_2;
//                             var_s1_6 = 0;
//                             if (arg0->ext.factory.unk92 >= 0x80) {
//                                 arg0->ext.factory.unk92 = 0x80;
//                                 arg0->step_s += 1;
//                             }
//                             var_s0_6 = arg0->ext.prim;
//                             do {
//                                 var_s0_6->drawMode = 0x35;
//                                 temp_v0_13 = (u8) arg0->ext.stub[0x16];
//                                 var_s1_6 += 1;
//                                 var_s0_6->b3 = temp_v0_13;
//                                 var_s0_6->g3 = temp_v0_13;
//                                 var_s0_6->r3 = temp_v0_13;
//                                 var_s0_6->b2 = temp_v0_13;
//                                 var_s0_6->g2 = temp_v0_13;
//                                 var_s0_6->r2 = temp_v0_13;
//                                 var_s0_6->b1 = temp_v0_13;
//                                 var_s0_6->g1 = temp_v0_13;
//                                 var_s0_6->r1 = temp_v0_13;
//                                 var_s0_6->b0 = temp_v0_13;
//                                 var_s0_6->g0 = temp_v0_13;
//                                 var_s0_6->r0 = temp_v0_13;
//                                 var_s0_6 = var_s0_6->next;
//                             } while (var_s1_6 < 2);
//                             var_s1_7 = 0;
//                             var_s0_6->drawMode = 0x15;
// loop_48:
//                             temp_v0_14 = (u8) arg0->ext.stub[0x16];
//                             var_s1_7 += 1;
//                             var_s0_6->b3 = temp_v0_14;
//                             var_s0_6->g3 = temp_v0_14;
//                             var_s0_6->r3 = temp_v0_14;
//                             var_s0_6->b2 = temp_v0_14;
//                             var_s0_6->g2 = temp_v0_14;
//                             var_s0_6->r2 = temp_v0_14;
//                             var_s0_6->b1 = temp_v0_14;
//                             var_s0_6->g1 = temp_v0_14;
//                             var_s0_6->r1 = temp_v0_14;
//                             var_s0_6->b0 = temp_v0_14;
//                             var_s0_6->g0 = temp_v0_14;
//                             var_s0_6->r0 = temp_v0_14;
//                             var_s0_6 = var_s0_6->next;
//                             if (var_s1_7 < 2) {
//                                 var_s0_6->drawMode = 0x15;
//                                 goto loop_48;
//                             }
//                             break;
//                         case 4:
//                             arg0->ext.generic.unk88.unk->unk32 = 8;
//                             arg0->ext.generic.unk80.modeS32 = 0x40;
//                             arg0->step = 2;
//                             arg0->step_s = 0;
//                             D_8003BE40 = 1;
//                             break;
//                     }
//                 default:                            // switch 1
// block_84:
//                     FntPrint(&D_8019B3C0, arg0->step);
//                     FntPrint(&D_8019B3D0, arg0->step_s);
//                     return;
//                 }
//             }
// block_83:
//             DestroyEntity(arg0);
//             return;
//         case 2:                                     // switch 1
//             temp_v0_15 = arg0->ext.generic.unk80.modeS32 - 1;
//             arg0->ext.generic.unk80.modeS32 = temp_v0_15;
//             if (temp_v0_15 == 0) {
//                 arg0->step_s = 0;
//                 arg0->step = 3;
//             }
//             goto block_84;
//         case 3:                                     // switch 1
//             temp_v1_4 = arg0->step_s;
//             if (temp_v1_4 != 1) {
//                 if ((s32) temp_v1_4 < 2) {
//                     var_s1_8 = 0;
//                     if (temp_v1_4 != 0) {

//                     } else {
//                         var_s0_7 = arg0->ext.prim->next->next;
//                         do {
//                             var_s0_7->drawMode = 0x15;
//                             temp_v0_16 = arg0->ext.stub[0x16];
//                             var_s1_8 += 1;
//                             var_s0_7->b3 = temp_v0_16;
//                             var_s0_7->g3 = temp_v0_16;
//                             var_s0_7->r3 = temp_v0_16;
//                             var_s0_7->b2 = temp_v0_16;
//                             var_s0_7->g2 = temp_v0_16;
//                             var_s0_7->r2 = temp_v0_16;
//                             var_s0_7->b1 = temp_v0_16;
//                             var_s0_7->g1 = temp_v0_16;
//                             var_s0_7->r1 = temp_v0_16;
//                             var_s0_7->b0 = temp_v0_16;
//                             var_s0_7->g0 = temp_v0_16;
//                             var_s0_7->r0 = temp_v0_16;
//                             var_s0_7 = var_s0_7->next;
//                         } while (var_s1_8 < 2);
//                         temp_v0_17 = (u16) arg0->ext.factory.unk92 - 4;
//                         arg0->ext.factory.unk92 = temp_v0_17;
//                         if (temp_v0_17 & 0x8000) {
//                             arg0->ext.factory.unk92 = 0;
//                             goto block_79;
//                         }
//                     }
//                     goto block_84;
//                 }
//                 if (temp_v1_4 != 2) {
//                     if (temp_v1_4 != temp_a0) {
//                         goto block_84;
//                     }
//                     var_s0_8 = arg0->ext.factory.parent;
//                     if (var_s0_8 != NULL) {
//                         do {
//                             func_801AD0EC((?* ) var_s0_8);
//                             var_s0_8 = var_s0_8->next;
//                         } while (var_s0_8 != NULL);
//                     }
//                     temp_s0_6 = arg0->ext.generic.unk84.unk;
//                     temp_v0_18 = (u16) temp_s0_6->y0 + 2;
//                     temp_s0_6->y0 = temp_v0_18;
//                     temp_s0_6->y1 = temp_v0_18;
//                     temp_s0_6->x0 = (u16) temp_s0_6->x0 - 2;
//                     temp_v0_19 = (u16) temp_s0_6->y2 - 2;
//                     temp_s0_6->y2 = temp_v0_19;
//                     temp_s0_6->y3 = temp_v0_19;
//                     temp_s0_6->x2 = (u16) temp_s0_6->x2 - 2;
//                     temp_s0_6->x1 = (u16) temp_s0_6->x1 + 2;
//                     temp_s0_6->x3 = (u16) temp_s0_6->x3 + 2;
//                     if (temp_s0_6->y2 < temp_s0_6->y0) {
//                         goto block_83;
//                     }
//                     goto block_84;
//                 }
//                 var_s0_9 = arg0->ext.factory.parent;
//                 if (var_s0_9 != NULL) {
//                     do {
//                         func_801AD0EC((?* ) var_s0_9);
//                         var_s0_9 = var_s0_9->next;
//                     } while (var_s0_9 != NULL);
//                 }
//                 temp_v0_20 = arg0->ext.generic.unk80.modeS32 - 1;
//                 arg0->ext.generic.unk80.modeS32 = temp_v0_20;
//                 if (temp_v0_20 == 0) {
//                     goto block_78;
//                 }
//                 goto block_84;
//             }
//             var_s0_10 = arg0->ext.prim;
//             var_s1_9 = 1;
//             do {
//                 var_s0_10->drawMode = 8;
//                 var_s0_10 = var_s0_10->next;
//                 var_s1_9 += 1;
//             } while (var_s1_9 < 4);
//             var_s0_11 = arg0->ext.factory.parent;
//             var_s1_10 = 0;
//             var_a1 = 0 * 4;
//             do {
//                 var_s0_11->r0 = 0x80;
//                 var_s0_11->g0 = 0x80;
//                 var_s0_11->b0 = 0x80;
//                 var_s1_10 += 1;
//                 var_s0_11->unk10 = (s32) var_s0_11->unk4;
//                 var_s0_11->unk1C = (s32) var_s0_11->unk4;
//                 var_s0_11->unk28 = (s32) var_s0_11->unk4;
//                 var_s0_11->p1 = var_a1;
//                 var_s0_11->p2 = Random() & 3;
//                 var_s0_11->p3 = 0;
//                 var_s0_11->drawMode = 0x35;
//                 var_s0_11 = var_s0_11->next;
//                 var_a1 = var_s1_10 * 4;
//             } while (var_s1_10 < 0x14);
//             var_s1_11 = 0;
//             do {
//                 temp_v0_21 = 0x14 - var_s1_11;
//                 var_s1_11 += 1;
//                 var_s0_11->r0 = 0x80;
//                 var_s0_11->g0 = 0x80;
//                 var_s0_11->b0 = 0x80;
//                 var_s0_11->unk10 = (s32) var_s0_11->unk4;
//                 var_s0_11->unk1C = (s32) var_s0_11->unk4;
//                 var_s0_11->unk28 = (s32) var_s0_11->unk4;
//                 var_s0_11->p1 = (u8) -(temp_v0_21 * 4);
//                 var_s0_11->p2 = Random() & 3;
//                 var_s0_11->drawMode = 0x35;
//                 var_s0_11->p3 = 0;
//                 var_s0_11 = var_s0_11->next;
//             } while (var_s1_11 < 0x14);
//             var_s1_12 = 0;
//             var_a1_2 = 0 * 4;
//             do {
//                 var_s0_11->r0 = 0x80;
//                 var_s0_11->g0 = 0x80;
//                 var_s0_11->b0 = 0x80;
//                 var_s1_12 += 1;
//                 var_s0_11->unk10 = (s32) var_s0_11->unk4;
//                 var_s0_11->unk1C = (s32) var_s0_11->unk4;
//                 var_s0_11->unk28 = (s32) var_s0_11->unk4;
//                 var_s0_11->p1 = var_a1_2;
//                 var_s0_11->p2 = Random() & 3;
//                 var_s0_11->p3 = 0;
//                 var_s0_11->drawMode = 0x35;
//                 var_s0_11 = var_s0_11->next;
//                 var_a1_2 = var_s1_12 * 4;
//             } while (var_s1_12 < 0x14);
//             var_s1_13 = 0;
//             do {
//                 temp_v0_22 = 0x14 - var_s1_13;
//                 var_s1_13 += 1;
//                 var_s0_11->r0 = 0x80;
//                 var_s0_11->g0 = 0x80;
//                 var_s0_11->b0 = 0x80;
//                 var_s0_11->unk10 = (s32) var_s0_11->unk4;
//                 var_s0_11->unk1C = (s32) var_s0_11->unk4;
//                 var_s0_11->unk28 = (s32) var_s0_11->unk4;
//                 var_s0_11->p1 = (u8) -(temp_v0_22 * 4);
//                 var_s0_11->p2 = Random() & 3;
//                 var_s0_11->drawMode = 0x35;
//                 var_s0_11->p3 = 0;
//                 var_s0_11 = var_s0_11->next;
//             } while (var_s1_13 < 0x14);
//             arg0->ext.generic.unk80.modeS32 = 0x70;
//             goto block_79;
//     }
// }
// Warning: struct draculaPrimitive is not defined (only forward-declared)
//#endif
//#include "../e_stage_name.h"

//NOTE: The remaining functions are all contained in "../prim_helpers.h" but
//      UnkPrimHelper and PrimDecreaseBrightness don't match.
INCLUDE_ASM("st/chi/nonmatchings/entity_damage_display", func_801ADF40);    // UnkPrimHelper()
//INCLUDE_ASM("st/chi/nonmatchings/entity_damage_display", func_801AE328);    // UpdateAnimation()
s32 UpdateAnimation(u8* texAnimations, Primitive* prim) {
    s16 sp0;
    s16 tempUv;
    u8 new_var;
    u8* nextAnimation = texAnimations + ((prim->p1 * 5) & 0xFF);
    u8 new_var2;
    s32 retVal = 0;

    if (prim->p2 == 0) {
        if (*nextAnimation) {
            if (*nextAnimation == 0xFF) {
                return 0;
            }
            retVal = 0x80;
            prim->p2 = nextAnimation[0];
            ++nextAnimation;
            tempUv = nextAnimation[0] + (nextAnimation[1] << 8);
            nextAnimation += 2;
            sp0 = nextAnimation[0] + (nextAnimation[1] << 8);
            LOH(prim->u0) = tempUv;
            LOH(prim->u1) = tempUv + *((u8*)(&sp0));
            new_var = *((u8*)&sp0 + 1);
            LOH(prim->u3) = tempUv + sp0;
            LOH(prim->u2) = tempUv + (new_var << 8);
            ++prim->p1;
        } else {
            prim->p1 = 0;
            prim->p2 = 0;
            prim->p2 = texAnimations[0];
            tempUv = texAnimations[1] + (texAnimations[2] << 8);
            sp0 = texAnimations[3] + (texAnimations[4] << 8);
            LOH(prim->u0) = tempUv;
            LOH(prim->u1) = tempUv + (*(u8*)&sp0);
            new_var2 = *((u8*)&sp0 + 1);
            LOH(prim->u3) = tempUv + sp0;
            LOH(prim->u2) = tempUv + (new_var2 << 8);
            ++prim->p1;
            return 0;
        }
    }

    retVal |= 1;
    --prim->p2;
    return (retVal | 1) & 0xFF;
}
//INCLUDE_ASM("st/chi/nonmatchings/entity_damage_display", func_801AE478);    // FindFirstUnkPrim()
Primitive* FindFirstUnkPrim(Primitive* poly) {
    while (poly != NULL) {
        if (poly->p3 != 0) {
            poly = poly->next;
        } else {
            return poly;
        }
    }
    return NULL;
}
//INCLUDE_ASM("st/chi/nonmatchings/entity_damage_display", func_801AE4A8);    // FindFirstUnkPrim2()
Primitive* FindFirstUnkPrim2(Primitive* prim, u8 index) {

    Primitive* ret;
    int i;

    for (; prim; prim = prim->next) {
        if (!prim->p3) {
            ret = prim;
            for (i = 1; i < index; ++i) {
                prim = prim->next;
                if (!prim) {
                    return NULL;
                }
                if (prim->p3) {
                    break;
                }
            }
            if (i == index) {
                return ret;
            }
        }
    }
    return NULL;
}
//INCLUDE_ASM("st/chi/nonmatchings/entity_damage_display", func_801AE524);    // PrimToggleVisibility()
Primitive* PrimToggleVisibility(Primitive* firstPrim, s32 count) {
    Primitive* prim;
    s8 isVisible;
    s32 i;

    if (firstPrim->p3) {
        firstPrim->p3 = 0;
    } else {
        firstPrim->p3 = 1;
    }

    prim = firstPrim;
    for (i = 0; i < count; i++) {
        if (prim->p3) {
            prim->drawMode &= ~DRAW_HIDE;
            isVisible = false;
        } else {
            prim->drawMode |= DRAW_HIDE;
            isVisible = true;
        }

        prim = prim->next;
        if (prim == NULL)
            return 0;
        prim->p3 = isVisible;
    }

    return prim;
}
//INCLUDE_ASM("st/chi/nonmatchings/entity_damage_display", func_801AE5AC);    // PrimResetNext()
void PrimResetNext(Primitive* prim) {
    prim->p1 = 0;
    prim->p2 = 0;
    prim->p3 = 0;
    prim->next->x1 = 0;
    prim->next->y1 = 0;
    prim->next->y0 = 0;
    prim->next->x0 = 0;
    prim->next->clut = 0;
    LOHU(prim->next->u0) = 0;
    LOHU(prim->next->b1) = 0;
    LOHU(prim->next->r1) = 0;
    LOHU(prim->next->u1) = 0;
    prim->next->tpage = 0;
    LOHU(prim->next->r2) = 0;
    LOHU(prim->next->b2) = 0;
    prim->next->u2 = 0;
    prim->next->v2 = 0;
    prim->next->r3 = 0;
    prim->next->b3 = 0;
    prim->next->x2 = 0;
    prim->next->y2 = 0;
}
//TODO: Find first "init not started" prim?
//INCLUDE_ASM("st/chi/nonmatchings/entity_damage_display", func_801AE68C);    // UnkPolyFunc2()
void UnkPolyFunc2(Primitive* prim) {
    PrimResetNext(prim);
    prim->p3 = 8;
    prim->next->p3 = 1;
    prim->next->type = PRIM_LINE_G2;
    prim->next->drawMode = 0xA;
}
//INCLUDE_ASM("st/chi/nonmatchings/entity_damage_display", func_801AE6E0);    // UnkPolyFunc0()
void UnkPolyFunc0(Primitive* prim) {
    prim->p3 = 0;
    prim->drawMode = DRAW_HIDE;
    prim->next->p3 = 0;
    prim->next->type = PRIM_GT4;
    prim->next->drawMode = DRAW_HIDE;
}
INCLUDE_ASM("st/chi/nonmatchings/entity_damage_display", func_801AE70C);    // PrimDecreaseBrightness()
//#include "../prim_helpers.h"
