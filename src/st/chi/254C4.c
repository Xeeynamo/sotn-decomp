#include "chi.h"

/*
 * File: 254C4.c
 * Overlay: CHI
 * Description: Abandoned Mine
 */

// D_80181388
s16 unk15_rot[] = {
    0x0030, 0x0050, 0x0080, 0x00B0, 0x00D0, 0x0100, 0x0100, 0x0000
};

// D_80181398
s32 unk15_yVel[] = {
    0x00000400, 0x00002400, 0x00003C00, 0x00006000,
    0x00007800, 0x0000C000
};

// D_801813B0
s32 unk14_yVel[] = {
    0x00000800, 0x00002800, 0x00004800, 0x00007000,
    0x0000E000, 0x00012000
};

// D_801813C8
u8 unk14_startFrame[] = {
    0x01, 0x09, 0x15, 0x2B
};

// D_801813CC
u16 unk14_lifetime[] = {
    0x0010, 0x0018, 0x002A, 0x002F
};

// [Duplicate]
// func_801A54C4
#include "../entity_unkId14.h"

// [Duplicate]
// func_801A55B4
#include "../entity_unkId15.h"

extern u16 g_InitializeEntityData0[];

// D_801813D4
u32 g_olroxDroolCollOffsets[] = {
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
// func_801A5F54
#include "../entity_intense_explosion.h"

u8 D_801813DC[] = {
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
// func_801A62A0
#include "../entity_big_red_fireball.h"

// D_801813EC
u16 g_UnkRecursPrimVecOrder[] = {
    0x0000, 0x0001, 0x0003, 0x0004, 0x0001, 0x0002, 0x0004, 0x0005,
    0x0003, 0x0004, 0x0006, 0x0007, 0x0004, 0x0005, 0x0007, 0x0008
};

// [Duplicate]
// func_801A6478
#include "../unk_recursive_primfunc_1.h"

// D_8018140C
u16 g_UnkRecursPrim2Inds[] = {
    0x0000, 0x0001, 0x0003, 0x0004, 0x0001, 0x0002, 0x0004, 0x0005,
    0x0003, 0x0004, 0x0006, 0x0007, 0x0004, 0x0005, 0x0007, 0x0008
};

// [Duplicate]
// func_801A6A58
#include "../unk_recursive_primfunc_2.h"

#include "../clut_lerp.h"

#include "../play_sfx_with_pos_args.h"

extern u16 g_InitializeData0[];

// D_8018142C
u16 g_ESoulStealOrbAngles[] = {
    0x0820, 0x0840, 0x0860, 0x0880, 0x08C0, 0x0900, 0x0940, 0x0A00
};

// D_8018143C
s16 g_ESoulStealOrbSprt[] = {
    0xFFFD, 0xFFFD, 0x0008, 0x0008, 0x00D0, 0x0068, 0x00D8, 0x0070,
    0xFFFD, 0xFFFD, 0x0008, 0x0008, 0x00C8, 0x0068, 0x00D0, 0x0070,
    0xFFF9, 0xFFF9, 0x0010, 0x000F, 0x00C8, 0x0070, 0x00D8, 0x007F,
    0xFFF5, 0xFFF5, 0x0018, 0x0017, 0x0080, 0x0068, 0x0098, 0x007F,
    0xFFF5, 0xFFF5, 0x0018, 0x0017, 0x0098, 0x0068, 0x00B0, 0x007F,
    0xFFF5, 0xFFF5, 0x0018, 0x0017, 0x00B0, 0x0068, 0x00C8, 0x007F
};

// D_8018149C
u8 g_ESoulStealOrbAnim[] = {
    0x04, 0x02, 0x03, 0x03, 0x03, 0x04, 0x03, 0x05, 0x03, 0x06, 0x03, 0x03, 0x00, 0x00, 0x00, 0x00
};

// [Duplicate]
// func_801A7448
#include "../entity_soul_steal_orb.h"

// [Duplicate]
// func_801A77DC
#include "../entity_enemy_blood.h"

#if !defined(VERSION_PSP)
static u8 D_801814AC[] = {0x40, 0x01, 0xFF, 0x00};
static u8 D_801814B0[] = {0x40, 0x02, 0xFF, 0x00};
static u8 D_801814B4[] = {0x40, 0x02, 0xFF, 0x00};
static u8 D_801814B8[] = {0x40, 0x01, 0xFF, 0x00};
static u8 D_801814BC[] = {0x40, 0x03, 0xFF, 0x00};
static ObjInit2 D_801814C0[] = {
    {0x0006, 0x01EC, 0x0000, 0x0000, 0x00, 0x10, 0, D_801814AC},
    {0x000C, 0x01EC, 0x0000, 0x0000, 0x00, 0x10, 0, D_801814B4},
    {0x000C, 0x0080, 0x0000, 0x0000, 0x00, 0x10, 0, D_801814B8},
    {0x0006, 0x01EC, 0x0000, 0x0000, 0x00, 0x10, 0, D_801814B0},
    {0x000C, 0x01EC, 0x0000, 0x0000, 0x00, 0x10, 0, D_801814BC},
    {0x000C, 0x0080, 0x0000, 0x0000, 0x00, 0x10, 0, D_801814B8},
};

#else
extern ObjInit2 D_801814C0[];

#endif

extern u16 g_eInitGeneric2[];

// [Duplicate]
// [Need to remove D_######## symbol names before using common include]
// func_801A7C8C
void EntityRoomForeground(Entity* entity) {
    ObjInit2* objInit = &D_801814C0[entity->params];

    if (!entity->step) {
        InitializeEntity(g_eInitGeneric2);
        entity->animSet = objInit->animSet;
        entity->zPriority = objInit->zPriority;
        entity->unk5A = objInit->unk4.u;
        entity->palette = objInit->palette;
        entity->drawFlags = objInit->drawFlags;
        entity->drawMode = objInit->drawMode;
        if (objInit->unkC != 0) {
            entity->flags = objInit->unkC;
        }
        if (entity->params > 4) {
            entity->drawFlags |= DRAW_COLORS;
            entity->rotZ = 0x800;
        }
    }
    AnimateEntity(objInit->unk10, entity);
}
//TODO: Can't use this include yet, as it still contains D_######## symbol names
//#include "../e_room_fg.h"

#include "../bottom_corner_text.h"

// func_801A80A8
void func_801A80A8()
{
    Entity* entity;

    if (!(g_Timer & 0xF)) {
        entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
        if (entity != NULL) {
            CreateEntityFromEntity(E_ID_21, g_CurrentEntity, entity);
            entity->facingLeft = g_CurrentEntity->facingLeft;
            entity->zPriority = g_CurrentEntity->zPriority - 1;
            entity->params = g_CurrentEntity->animCurFrame;
            entity->step = 0x20;
        }
    }
}