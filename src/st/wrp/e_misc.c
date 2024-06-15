#include "wrp.h"

extern u16 D_80180608[];

#include "../entity_relic_orb.h"

void EntityHeartDrop(Entity* self) {
    u16 index;
    u8 value;
    PfnEntityUpdate update;

    if (!self->step) {
        index = self->ext.heartDrop.unkB4 = self->params + 0x118;
        value = g_CastleFlags[(index >> 3) + 0x100] >> (index & 7);
        if (value & 1) {
            DestroyEntity(self);
            return;
        }

        index -= 0x118;
        index = D_80180608[index];
        if (index < 128) {
            self->ext.heartDrop.update = EntityPrizeDrop;
        } else {
            self->ext.heartDrop.update = EntityEquipItemDrop;
            index -= 128;
        }
        self->params = index + 0x8000;
    } else {
        index = self->ext.heartDrop.unkB4;
        if (self->step < 5) {
            if (self->hitFlags) {
                g_CastleFlags[(index >> 3) + 0x100] |= 1 << (index & 7);
                self->step = 5;
            }
        }
    }
    update = self->ext.heartDrop.update;
    update(self);
}

#include "../entity_message_box.h"

#include "../check_coll_offsets.h"

#include "../entity_unkId13.h"

u16 g_eUnk14SpawnRots[] = {
    /* FE8 */ 0x0010,
    /* FEA */ 0x0020,
    /* FEC */ 0x0030,
    /* FEE */ 0x0040,
    /* FF0 */ 0x0050,
    /* FF2 */ 0x0060,
    /* FF4 */ 0x0070,
    /* FF6 */ 0x0000,
};
#include "../entity_unkId14_spawner.h"

#include "../entity_unkId15_spawner.h"

static s16 unk15_rot[] = {
    /* FF8 */ 0x0030,
    /* FFA */ 0x0050,
    /* FFC */ 0x0080,
    /* FFE */ 0x00B0,
    /* 1000 */ 0x00D0,
    /* 1002 */ 0x0100,
    /* 1004 */ 0x0100,
    /* 1006 */ 0x0000,
};

static s32 unk15_yVel[] = {
    /* 1008 */ 0x00000400,
    /* 100C */ 0x00002400,
    /* 1010 */ 0x00003C00,
    /* 1014 */ 0x00006000,
    /* 1018 */ 0x00007800,
    /* 101C */ 0x0000C000,
};

s32 unk14_yVel[] = {
    /* 1020 */ 0x00000800,
    /* 1024 */ 0x00002800,
    /* 1028 */ 0x00004800,
    /* 102C */ 0x00007000,
    /* 1030 */ 0x0000E000,
    /* 1034 */ 0x00012000,
};

u8 unk14_startFrame[] = {
    /* 1038 */ 0x01,
    /* 1039 */ 0x09,
    /* 103A */ 0x15,
    /* 103B */ 0x2B,
};

u16 unk14_lifetime[] = {
    /* 103C */ 0x0010,
    /* 103E */ 0x0018,
    /* 1040 */ 0x002A,
    /* 1042 */ 0x002F,
};

#include "../entity_unkId14.h"

#include "../entity_unkId15.h"

u32 g_olroxDroolCollOffsets[] = {
    /* 1044 */ 0x00000000,
    /* 1048 */ 0x000000FF,
};
#include "../entity_olrox_drool.h"

bool func_8018FC4C(Point16* unk) {
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

u8 func_8018FD48(s32 arg0) {
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

void EntityIntenseExplosion(Entity* self) {
    if (!self->step) {
        InitializeEntity(g_InitializeEntityData0);
        self->palette = PAL_OVL(0x170);
        self->animSet = ANIMSET_DRA(5);
        self->animCurFrame = 1;
        self->drawMode = 0x30;
        if (self->params & 0xF0) {
            self->palette = PAL_OVL(0x195);
            self->drawMode = DRAW_TPAGE;
        }

        if (self->params & 0xFF00) {
            self->zPriority = (self->params & 0xFF00) >> 8;
        }
        self->zPriority += 8;
    } else {
        self->animFrameDuration++;
        self->posY.val -= FIX(0.25);
        if ((self->animFrameDuration & 1) == 0) {
            self->animCurFrame++;
        }

        if (self->animFrameDuration >= 37) {
            DestroyEntity(self);
        }
    }
}

u8 D_8018104C[] = {
    2, 1, 2, 2, 2, 3, 2, 4, 2, 5, 4, 6, -1,
};
void func_801903C8(Entity* self) {
    if (!self->step) {
        InitializeEntity(g_InitializeEntityData0);
        self->unk6C = 0xF0;
        self->rotX = 0x01A0;
        self->rotY = 0x01A0;
        self->animSet = ANIMSET_DRA(8);
        self->animCurFrame = 1;
        self->zPriority += 16;

        if (self->params) {
            self->palette = self->params;
        } else {
            self->palette = PAL_OVL(0x160);
        }

        self->step++;
    } else {
        MoveEntity();
        if (!AnimateEntity(D_8018104C, self)) {
            DestroyEntity(self);
        }
    }
}

extern PfnEntityUpdate PfnEntityUpdates[];
void func_80190494(u16 entityId, Entity* src, Entity* dst) {
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

    if (src->palette & PAL_OVL_FLAG) {
        dst->palette = src->hitEffect;
    } else {
        dst->palette = src->palette;
    }
}

void func_8019055C(void) {
    s32 temp_s3;
    s8 temp_s4;
    Entity* entity;
    s32 i;

    temp_s4 = Random() & 3;
    temp_s3 = ((Random() & 0xF) << 8) - 0x800;

    for (i = 0; i < 6; i++) {
        entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
        if (entity != NULL) {
            CreateEntityFromEntity(E_EXPLOSION, g_CurrentEntity, entity);
            entity->ext.generic.unk84.U8.unk1 = 6 - i;
            entity->ext.generic.unk80.modeS16.unk0 = temp_s3;
            entity->ext.generic.unk84.U8.unk0 = temp_s4;
        }
    }
}

extern u8 g_bigRedFireballAnim[];
u16 g_UnkRecursPrimVecOrder[] = {
    0, 1, 3, 4, 1, 2, 4, 5, 3, 4, 6, 7, 4, 5, 7, 8};
#include "../entity_big_red_fireball.h"

#include "../unk_recursive_primfunc_1.h"

u16 D_8018107C[] = {0, 1, 3, 4, 1, 2, 4, 5, 3, 4, 6, 7, 4, 5, 7, 8, 0, 0};

// arg3 holds, in order:
// A Primitive, an array of 9 rgb_sets, an array of 10 Point16s, an array of 10 uvPairs, and
// a pointer to another of arg3. Pointer type on arg3 is fake, but needed for Windows.
Primitive* func_80190DCC(Primitive* arg0, s32 arg1, Primitive* arg2, u8* arg3) {
    s32 i;
    Primitive* prim1;
    Primitive* prim2;
    Primitive* nextArg2;
    s32 Idx1;
    s32 Idx2;
    s32 Idx3;
    s32 Idx4;
    s16* Indices;
    Point16* points;
    rgb_set* colors;
    uvPair* uv_values;

    
    if (arg2 == NULL) {
        return NULL;
    }
    prim2 = arg3;
    arg3 += 0x34;
    colors = arg3;
    arg3 = arg3 + 0x24;
    
    colors[0] = *(rgb_set*)&arg0->r0;
    colors[2] = *(rgb_set*)&arg0->r1;
    colors[6] = *(rgb_set*)&arg0->r2;
    colors[8] = *(rgb_set*)&arg0->r3;

    points = arg3;
    arg3 += 0x24;
    uv_values = arg3;
    arg3 += 0x14;
    prim1 = arg2;
    
    colors[1].r = ((colors[0].r + colors[2].r + 1) >> 1);
    colors[1].g = ((colors[0].g + colors[2].g + 1) >> 1);
    colors[1].b = ((colors[0].b + colors[2].b + 1) >> 1);
    
    colors[7].r = ((colors[6].r + colors[8].r + 1) >> 1);
    colors[7].g = ((colors[6].g + colors[8].g + 1) >> 1);
    colors[7].b = ((colors[6].b + colors[8].b + 1) >> 1);

    colors[3].r = ((colors[0].r + colors[6].r + 1) >> 1);
    colors[3].g = ((colors[0].g + colors[6].g + 1) >> 1);
    colors[3].b = ((colors[0].b + colors[6].b + 1) >> 1);

    colors[5].r = ((colors[2].r + colors[8].r + 1) >> 1);
    colors[5].g = ((colors[2].g + colors[8].g + 1) >> 1);
    colors[5].b = ((colors[2].b + colors[8].b + 1) >> 1);

    colors[4].r = ((colors[3].r + colors[5].r + 1) >> 1);
    colors[4].g = ((colors[3].g + colors[5].g + 1) >> 1);
    colors[4].b = ((colors[3].b + colors[5].b + 1) >> 1);

    
    uv_values[0] = *(uvPair*)&arg0->u0;
    uv_values[2] = *(uvPair*)&arg0->u1;
    uv_values[6] = *(uvPair*)&arg0->u2;
    uv_values[8] = *(uvPair*)&arg0->u3;
    uv_values[1].u = (uv_values[0].u + uv_values[2].u + 1) >> 1;
    uv_values[1].v = (uv_values[0].v + uv_values[2].v + 1) >> 1;
    uv_values[7].u = (uv_values[6].u + uv_values[8].u + 1) >> 1;
    uv_values[7].v = (uv_values[6].v + uv_values[8].v + 1) >> 1;
    uv_values[3].u = (uv_values[0].u + uv_values[6].u + 1) >> 1;
    uv_values[3].v = (uv_values[0].v + uv_values[6].v + 1) >> 1;
    uv_values[5].u = (uv_values[2].u + uv_values[8].u + 1) >> 1;
    uv_values[5].v = (uv_values[2].v + uv_values[8].v + 1) >> 1;
    uv_values[4].u = (uv_values[3].u + uv_values[5].u + 1) >> 1;
    uv_values[4].v = (uv_values[3].v + uv_values[5].v + 1) >> 1;

    points[0] = *(Point16*)&arg0->x0;
    points[2] = *(Point16*)&arg0->x1;
    points[6] = *(Point16*)&arg0->x2;
    points[8] = *(Point16*)&arg0->x3;
    points[1].x = ((points[0].x + points[2].x + 1) >> 1);
    points[1].y = ((points[0].y + points[2].y + 1) >> 1);
    points[7].x = ((points[6].x + points[8].x + 1) >> 1);
    points[7].y = ((points[6].y + points[8].y + 1) >> 1);
    points[3].x = ((points[0].x + points[6].x + 1) >> 1);
    points[3].y = ((points[0].y + points[6].y + 1) >> 1);
    points[5].x = ((points[2].x + points[8].x + 1) >> 1);
    points[5].y = ((points[2].y + points[8].y + 1) >> 1);
    points[4].x = ((points[3].x + points[5].x + 1) >> 1);
    points[4].y = ((points[3].y + points[5].y + 1) >> 1);

    *prim2 = *arg0;
    Indices = &D_8018107C;
    for(i = 0; i < 4; i++){
        Idx1 = *Indices++;
        Idx2 = *Indices++;
        Idx3 = *Indices++;
        Idx4 = *Indices++;
        *(uvPair*)&prim2->u0 = uv_values[Idx1];
        *(uvPair*)&prim2->u1 = uv_values[Idx2];
        *(uvPair*)&prim2->u2 = uv_values[Idx3];
        *(uvPair*)&prim2->u3 = uv_values[Idx4];
        *(Point16*)&prim2->x0 = points[Idx1];
        *(Point16*)&prim2->x1 = points[Idx2];
        *(Point16*)&prim2->x2 = points[Idx3];
        *(Point16*)&prim2->x3 = points[Idx4];
        *(rgb_set*)&prim2->r0 = colors[Idx1];
        *(rgb_set*)&prim2->r1 = colors[Idx2];
        *(rgb_set*)&prim2->r2 = colors[Idx3];
        *(rgb_set*)&prim2->r3 = colors[Idx4];

        prim2->type = arg0->type;
        if (arg1 == 1) {
            nextArg2 = arg2->next;
            *arg2 = *prim2;
            arg2->next = nextArg2;
            arg2 = nextArg2;
            if (arg2 == NULL) {
                return NULL;
            }
        } else {
            arg2 = func_80190DCC(prim2, arg1 - 1, arg2, arg3);
        }
    }
    return arg2;
}

#include "../clut_lerp.h"

void func_801916C4(s16 sfxId) {
    s32 posX;
    s32 posY;
    s16 arg2;
    s16 arg1;

    posX = g_CurrentEntity->posX.i.hi - 128;
    arg2 = (abs(posX) - 32) >> 5;
    if (arg2 > 8) {
        arg2 = 8;
    } else if (arg2 < 0) {
        arg2 = 0;
    }
    if (posX < 0) {
        arg2 = -arg2;
    }
    arg1 = abs(posX) - 96;
    posY = abs(g_CurrentEntity->posY.i.hi - 128) - 112;
    if (posY > 0) {
        arg1 += posY;
    }
    if (arg1 < 0) {
        arg1 = 0;
    }
    arg1 = 127 - (arg1 >> 1);
    if (arg1 > 0) {
        g_api.func_80134714(sfxId, arg1, arg2);
    }
}
