/*
 * File: 23F58.c
 * Overlay: CHI
 * Description: Abandoned Mine
 */

#include "chi.h"

extern u16 g_InitializeData0[];

// D_80181314: g_RelicOrbTexts
// D_80181318: g_RelicOrbTextBg1EY
// D_80181328: g_RelicOrbTextBg1SY
// D_80181338: g_RelicOrbTextBg2SY
// D_80181348: g_RelicOrbTextBg2EY
// D_80181358: g_RelicOrbSparkleX
// D_80181368: g_RelicOrbSparkleY
// [Duplicate]
// func_801A3F58: [E_RELIC_ORB] EntityRelicOrb
#include "../entity_relic_orb.h"

extern u16 D_801809E4[];

// [Duplicate]
// [Almost duplicate of CEN.EntityHeartDrop -- 0xC0 immediate is 0xB0 here]
// E_HEART_DROP
// func_801A4A28
void EntityHeartDrop(Entity* self) {
    u16 temp_a0;
    u16 temp_a0_2;
    u16 var_a0;

    if (self->step == 0) {
        temp_a0 = self->params + 0xB0;
        self->ext.generic.unkB4 = temp_a0;
        if ((D_8003BEEC[temp_a0 >> 3] >> (temp_a0 & 7)) & 1) {
            DestroyEntity(self);
            return;
        }
        temp_a0_2 = temp_a0 - 0xB0;
        var_a0 = D_801809E4[temp_a0_2];
        if (var_a0 < 128) {
            self->ext.generic.unkB8.unkFuncB8 = EntityPrizeDrop;
        } else {
            self->ext.generic.unkB8.unkFuncB8 = EntityEquipItemDrop;
            var_a0 -= 128;
        }
        self->params = var_a0 + 0x8000;
    } else {
        temp_a0_2 = self->ext.generic.unkB4;
        if (self->step < 5) {
            if (self->hitFlags != 0) {
                var_a0 = self->ext.generic.unkB4;
                D_8003BEEC[temp_a0_2 >> 3] |= 1 << (var_a0 & 7);
                self->step = 5;
            }
        }
    }
    self->ext.generic.unkB8.unkFuncB8(self);
}

// [Duplicate]
// func_801A4B50: [E_SAVE_GAME_POPUP] EntityMessageBox
#include "../entity_message_box.h"

// func_801A50AC: CheckColliderOffsets
#include "../check_coll_offsets.h"

// [Duplicate]
// [Rename in repo]
// func_801A519C: [E_FLAME_TRAIL] EntityUnkId13 (EntityFlameTrail)
#include "../entity_unkId13.h"

//D_80181378
static u16 g_eUnk14SpawnRots[] = {
    0x0010, 0x0020, 0x0030, 0x0040, 0x0050, 0x0060, 0x0070, 0x0000
};
void EntityUnkId14(Entity*);

// [Duplicate]
// func_801A52AC: EntityUnkId14Spawner
#include "../entity_unkId14_spawner.h"

void EntityUnkId15(Entity*);

// [Duplicate]
// func_801A53DC: EntityUnkId15Spawner
#include "../entity_unkId15_spawner.h"

// D_80181388
static s16 unk15_rot[] = {
    0x0030, 0x0050, 0x0080, 0x00B0, 0x00D0, 0x0100, 0x0100, 0x0000
};

// D_80181398
static s32 unk15_yVel[] = {
    0x00000400, 0x00002400, 0x00003C00, 0x00006000,
    0x00007800, 0x0000C000
};

// D_801813B0
static s32 unk14_yVel[] = {
    0x00000800, 0x00002800, 0x00004800, 0x00007000,
    0x0000E000, 0x00012000
};

// D_801813C8
static u8 unk14_startFrame[] = {
    0x01, 0x09, 0x15, 0x2B
};

// D_801813CC
static u16 unk14_lifetime[] = {
    0x0010, 0x0018, 0x002A, 0x002F
};

// [Duplicate]
// [Rename in shared file]
// func_801A54C4: [E_ID_14] EntityUnkId14
#include "../entity_unkId14.h"

// [Duplicate]
// [Rename in shared files]
// func_801A55B4: [E_ID_15 (E_GREY_PUFF)] EntityUnkId15 (EntityDustPuff)
#include "../entity_unkId15.h"

extern u16 g_InitializeEntityData0[];

// D_801813D4
static u32 g_olroxDroolCollOffsets[] = {
    0x00000000, 0x000000FF
};

// [Duplicate]
// [Almost duplicate of ../entity_olrox_drool.h, but this one checks the return of CheckColliderOffsets with & 0xFF]
// func_801A56A8
void EntityOlroxDrool(Entity* self) {
    s16 primIndex;
    Primitive* prim;

    switch (self->step) {
    case 0:
        InitializeEntity(g_InitializeEntityData0);
        primIndex = g_api.AllocPrimitives(PRIM_LINE_G2, 1);
        if (primIndex == -1) {
            return;
        }
        prim = &g_PrimBuf[primIndex];
        self->primIndex = primIndex;
        self->hitboxState = 0;
        self->ext.prim = prim;
        self->flags |= FLAG_HAS_PRIMS;
        while (prim != NULL) {
            prim->x0 = prim->x1 = self->posX.i.hi;
            prim->y0 = prim->y1 = self->posY.i.hi;
            prim->r0 = 64;
            prim->r1 = 0;
            prim->g0 = 64;
            prim->g1 = 0;
            prim->b0 = 255;
            prim->b1 = 16;
            prim->priority = self->zPriority + 1;
            prim->drawMode |= (DRAW_TPAGE2 + DRAW_TPAGE + DRAW_COLORS +
                               DRAW_UNK02 + DRAW_TRANSP);
            prim = prim->next;
        }
        break;

    case 1:
        prim = self->ext.prim;
        if (CheckColliderOffsets(g_olroxDroolCollOffsets, 0) & 0xFF) {
            prim->y1 += 2;
            if (self->step_s == 0) {
                // When hitting the ground, a sizzling effect is made
                EntityUnkId14Spawner(self, 1, 2, 0, 0, 3, 0);
                self->step_s = 1;
            }
        } else {
            self->velocityY += FIX(0.015625);
            self->posY.val += self->velocityY;
            if ((prim->y0 - prim->y1) > 8) {
                prim->y1 = prim->y0 - 8;
            }
        }

        prim->x0 = self->posX.i.hi;
        prim->x1 = self->posX.i.hi;
        prim->y0 = self->posY.i.hi;

        if (prim->y0 < prim->y1) {
            g_api.FreePrimitives(self->primIndex);
            DestroyEntity(self);
        }
        break;
    }
}
//TODO: Can't quite use this include due to tiny difference
//#include "../entity_olrox_drool.h"

// [Duplicate]
// func_801A58D8
bool func_801A58D8(Point16* unk) {
    Collider collider;

    FallEntity();
    g_CurrentEntity->posX.val += g_CurrentEntity->velocityX;
    g_CurrentEntity->posY.val += g_CurrentEntity->velocityY;

    if (g_CurrentEntity->velocityY >= 0) {
        s16 posX = g_CurrentEntity->posX.i.hi;
        s16 posY = g_CurrentEntity->posY.i.hi;
        posX += unk->x;
        posY += unk->y;
        g_api.CheckCollision(posX, posY, &collider, 0);
        if (collider.effects & EFFECT_SOLID) {
            g_CurrentEntity->posY.i.hi += collider.unk18;
            g_CurrentEntity->velocityY = -g_CurrentEntity->velocityY / 2;
            if (g_CurrentEntity->velocityY > FIX(-1.0)) {
                return true;
            }
        }
    }
    return false;
}

// [Duplicate]
// func_801A59D4
u8 func_801A59D4(s32 arg0) {
    Collider collider;
    u32 bits_67;
    u32 bits_45;
    u32 bits_23;
    u8 bits_01;
    u16 collEff;

    MoveEntity();
    bits_67 = 0;
    bits_23 = 0;
    bits_45 = 0;
    bits_01 = arg0 & 3;
    collEff = 0;
    switch (bits_01) {
    case 0:
        g_CurrentEntity->posY.i.hi += 3;
        g_api.CheckCollision(g_CurrentEntity->posX.i.hi,
                             g_CurrentEntity->posY.i.hi, &collider, 0);
        if (collider.effects != 0) {
            collEff = collider.effects;
            g_CurrentEntity->posY.i.hi += collider.unk18;
            g_api.CheckCollision(
                g_CurrentEntity->posX.i.hi,
                (s16)(g_CurrentEntity->posY.i.hi - 4), &collider, 0);
            if (collider.effects & EFFECT_UNK_0002) {
                bits_67 = 0x40;
                if (g_CurrentEntity->velocityX > 0) {
                    bits_01 = 2;
                } else {
                    bits_01 = 3;
                    g_CurrentEntity->velocityX = -g_CurrentEntity->velocityX;
                }
                g_CurrentEntity->velocityY = -g_CurrentEntity->velocityX;
                g_CurrentEntity->velocityX = 0;
            }
        } else {
            bits_67 = 0x80;
            g_CurrentEntity->posX.val -= g_CurrentEntity->velocityX;
            if (g_CurrentEntity->velocityX > 0) {
                bits_01 = 3;
            } else {
                bits_01 = 2;
                g_CurrentEntity->velocityX = -g_CurrentEntity->velocityX;
            }
            g_CurrentEntity->velocityY = g_CurrentEntity->velocityX;
            g_CurrentEntity->velocityX = 0;
        }
        break;

    case 1:
        g_CurrentEntity->posY.i.hi -= 3;
        g_api.CheckCollision(g_CurrentEntity->posX.i.hi,
                             g_CurrentEntity->posY.i.hi, &collider, 0);
        if (collider.effects != 0) {
            collEff = collider.effects;
            g_CurrentEntity->posY.i.hi += collider.unk20;
            g_api.CheckCollision(
                g_CurrentEntity->posX.i.hi,
                (s16)(g_CurrentEntity->posY.i.hi + 4), &collider, 0);
            if (collider.effects & EFFECT_UNK_0002) {
                bits_67 = 0x40;
                if (g_CurrentEntity->velocityX > 0) {
                    bits_01 = 2;
                } else {
                    bits_01 = 3;
                    g_CurrentEntity->velocityX = -g_CurrentEntity->velocityX;
                }
                g_CurrentEntity->velocityY = g_CurrentEntity->velocityX;
                g_CurrentEntity->velocityX = 0;
            }
        } else {
            bits_67 = 0x80;
            g_CurrentEntity->posX.val -= g_CurrentEntity->velocityX;
            if (g_CurrentEntity->velocityX > 0) {
                bits_01 = 3;
            } else {
                bits_01 = 2;
                g_CurrentEntity->velocityX = -g_CurrentEntity->velocityX;
            }
            g_CurrentEntity->velocityY = -g_CurrentEntity->velocityX;
            g_CurrentEntity->velocityX = 0;
        }
        break;

    case 2:
        g_CurrentEntity->posX.i.hi += 3;
        g_api.CheckCollision(g_CurrentEntity->posX.i.hi,
                             g_CurrentEntity->posY.i.hi, &collider, 0);
        if (collider.effects != 0) {
            collEff = collider.effects;
            g_CurrentEntity->posX.i.hi += collider.unk14;
            g_api.CheckCollision((s16)(g_CurrentEntity->posX.i.hi - 4),
                                 g_CurrentEntity->posY.i.hi, &collider, 0);
            if (collider.effects & EFFECT_SOLID) {
                bits_67 = 0x40;
                if (g_CurrentEntity->velocityY > 0) {
                    bits_01 = 0;
                } else {
                    bits_01 = 1;
                    g_CurrentEntity->velocityY = -g_CurrentEntity->velocityY;
                }
                g_CurrentEntity->velocityX = -g_CurrentEntity->velocityY;
                g_CurrentEntity->velocityY = 0;
            }
        } else {
            bits_67 = 0x80;
            g_CurrentEntity->posY.val -= g_CurrentEntity->velocityY;
            if (g_CurrentEntity->velocityY > 0) {
                bits_01 = 1;
            } else {
                bits_01 = 0;
                g_CurrentEntity->velocityY = -g_CurrentEntity->velocityY;
            }
            g_CurrentEntity->velocityX = g_CurrentEntity->velocityY;
            g_CurrentEntity->velocityY = 0;
        }
        break;

    case 3:
        g_CurrentEntity->posX.i.hi -= 3;
        g_api.CheckCollision(g_CurrentEntity->posX.i.hi,
                             g_CurrentEntity->posY.i.hi, &collider, 0);
        if (collider.effects != 0) {
            collEff = collider.effects;
            g_CurrentEntity->posX.i.hi += collider.unk1C;
            g_api.CheckCollision((s16)(g_CurrentEntity->posX.i.hi + 4),
                                 g_CurrentEntity->posY.i.hi, &collider, 0);
            if (collider.effects & EFFECT_SOLID) {
                bits_67 = 0x40;
                if (g_CurrentEntity->velocityY > 0) {
                    bits_01 = 0;
                } else {
                    bits_01 = 1;
                    g_CurrentEntity->velocityY = -g_CurrentEntity->velocityY;
                }
                g_CurrentEntity->velocityX = g_CurrentEntity->velocityY;
                g_CurrentEntity->velocityY = 0;
            }
        } else {
            bits_67 = 0x80;
            g_CurrentEntity->posY.val -= g_CurrentEntity->velocityY;
            if (g_CurrentEntity->velocityY > 0) {
                bits_01 = 1;
            } else {
                bits_01 = 0;
                g_CurrentEntity->velocityY = -g_CurrentEntity->velocityY;
            }
            g_CurrentEntity->velocityX = -g_CurrentEntity->velocityY;
            g_CurrentEntity->velocityY = 0;
        }
    }

    if (collEff & EFFECT_UNK_8000) {
        bits_23 = 4;
    }
    if (collEff & EFFECT_UNK_1000) {
        bits_23 = 8;
    }
    if (collEff & EFFECT_UNK_2000) {
        bits_23 = 0xC;
    }
    if (collEff & EFFECT_UNK_0800) {
        bits_45 = 0x20;
    }
    if (collEff & EFFECT_UNK_4000) {
        bits_45 = 0x10;
    }
    bits_01 = (bits_45 + (bits_23 + (bits_67 + bits_01)));
    return bits_01;
}

// [Duplicate]
// func_801A5F54: [E_INTENSE_EXPLOSION] EntityIntenseExplosion
#include "../entity_intense_explosion.h"

// D_801813DC
static u8 D_801813DC[] = {
    0x02, 0x01, 0x02, 0x02, 0x02, 0x03, 0x02, 0x04, 0x02, 0x05, 0x04, 0x06, 0xFF, 0x00, 0x00, 0x00
};

// [Duplicate]
// func_801A6054
void func_801A6054(Entity* entity) {
    if (!entity->step) {
        InitializeEntity(g_InitializeEntityData0);
        entity->unk6C = 0xF0;
        entity->rotX = 0x1A0;
        entity->rotY = 0x1A0;
        entity->animSet = ANIMSET_DRA(8);
        entity->animCurFrame = 1;
        entity->zPriority += 0x10;

        if (entity->params != 0) {
            entity->palette = entity->params;
        } else {
            entity->palette = 0x8160;
        }

        entity->step++;
        return;
    }

    MoveEntity();

    if (!AnimateEntity(D_801813DC, entity)) {
        DestroyEntity(entity);
    }
}

// [Duplicate]
// func_801A6120
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

// [Duplicate]
// func_801A61E8
void func_801A61E8(void) {
    Entity* entity;
    s8 temp_s4 = Random() & 3;
    s16 temp_s3 = ((Random() & 0xF) << 8) - 0x800;
    s32 i;

    for (i = 0; i < 6; i++) {
        entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
        if (entity != NULL) {
            CreateEntityFromEntity(2, g_CurrentEntity, entity);
            entity->ext.generic.unk84.U8.unk1 = 6 - i;
            entity->ext.generic.unk80.modeS16.unk0 = temp_s3;
            entity->ext.generic.unk84.U8.unk0 = temp_s4;
        }
    }
}

extern u8 g_bigRedFireballAnim[];

// [Duplicate]
// func_801A62A0: EntityBigRedFireball
#include "../entity_big_red_fireball.h"

// D_801813EC
static u16 g_UnkRecursPrimVecOrder[] = {
    0x0000, 0x0001, 0x0003, 0x0004, 0x0001, 0x0002, 0x0004, 0x0005,
    0x0003, 0x0004, 0x0006, 0x0007, 0x0004, 0x0005, 0x0007, 0x0008
};

// [Duplicate]
// func_801A6478: UnkRecursivePrimFunc1
#include "../unk_recursive_primfunc_1.h"

// D_8018140C
static u16 g_UnkRecursPrim2Inds[] = {
    0x0000, 0x0001, 0x0003, 0x0004, 0x0001, 0x0002, 0x0004, 0x0005,
    0x0003, 0x0004, 0x0006, 0x0007, 0x0004, 0x0005, 0x0007, 0x0008
};

// [Duplicate]
// func_801A6A58: UnkRecursivePrimFunc2
#include "../unk_recursive_primfunc_2.h"

// func_801A7158: ClutLerp
#include "../clut_lerp.h"

// func_801A7350: PlaySfxWithPosArgs
#include "../play_sfx_with_pos_args.h"