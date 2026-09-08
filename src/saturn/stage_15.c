// SPDX-License-Identifier: AGPL-3.0-or-later
#include "inc_asm.h"
#include "sattypes.h"
#include "stage_15.h"
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60DC040, func_060DC040);
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60DC1A8, func_060DC1A8);
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60DC328, func_060DC328);
extern SaturnSpriteResource g_Stage15SpriteBank16;
extern u32 g_Stage15SpriteBank16Frames[];

void func_060DC428(Entity* self) {
    SpriteObject* sprite;

    if (self->step == 0) {
        TekiInit(self, 5);
        self->step++;
        sprite = CreateSpriteObject(
            g_Stage15SpriteBank16.allocationIndex, g_Stage15SpriteBank16.flags,
            g_Stage15SpriteBank16.images, 1);
        self->unk0 = sprite;
        self->animCurFrame = 0x2A;
        func_0600AFA8(sprite,
                      (SaturnSpriteFrameHeader*)
                          g_Stage15SpriteBank16Frames[self->animCurFrame]);
        sprite->zPriority = 0x6A;
        self->step = 0x100;
        func_06079BB4(self);
    }
}
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60DC4B8, func_060DC4B8);
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60DC604, func_060DC604);
void func_060DC7E4(s32 arg0, s16* arg1, s16* arg2) {
    if (arg0 & 0x27) {
        if (arg0 & 0x20) {
            *arg1 = 0x14;
            *arg2 = 0x19;
            if (arg0 & 4) {
                *arg1 = 0x0A;
            }
        } else if (arg0 & 3) {
            *arg1 = 0x0C;
            *arg2 = 5;
        } else if (arg0 & 4) {
            *arg1 = 0x14;
            *arg2 = 0x19;
        }
    } else {
        *arg1 = 0x28;
        *arg2 = 0x19;
    }
}
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60DC838, func_060DC838);
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60DCDF8, func_060DCDF8);
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60DCF90, func_060DCF90);
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60DD37C, func_060DD37C);
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60DD524, func_060DD524);
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60DD698, func_060DD698);
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60DD898, func_060DD898);
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60DDA10, func_060DDA10);
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60DDB74, func_060DDB74);
s32 AllocPrimitives(s32 type, s32 count);
void MoveEntity(Entity* self);
void DestroyEntity(Entity* self);
void func_060DDB74(Entity* self);
void func_060DDA10(Entity* self);

void func_060DDCE8(Entity* self) {
    s32 primIndex;

    switch (self->step) {
    case 0:
        TekiInit(self, 3);
        self->step++;
        primIndex = AllocPrimitives(0x8002, 1);
        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags |= FLAG_HAS_PRIMS;
        self->primIndex = primIndex;
        func_060DDB74(self);
        break;
    case 1:
        MoveEntity(self);
        self->velocityY += self->ext.glowParticle.gravity;
        break;
    }

    func_060DDA10(self);
    if (self->ext.glowParticle.unk88 <= 0x82) {
        DestroyEntity(self);
    }
}
void func_060DDD94(Entity* self) {
    Primitive* prim;
    s16 x;
    s16 y;

    x = self->posX.i.hi;
    y = self->posY.i.hi;
    prim = &g_PrimBuf[self->primIndex];

    prim->x0 = prim->x3 = x;
    prim->x1 = prim->x2 = x + 1;
    prim->y0 = prim->y1 = y;
    prim->y2 = prim->y3 = y + 1;

    if (self->ext.glowParticle.b > 7) {
        self->ext.glowParticle.r -= 6;
        self->ext.glowParticle.g -= 6;
        self->ext.glowParticle.b -= 8;
        prim->unk6 =
            ((self->ext.glowParticle.b << 10) +
             (self->ext.glowParticle.g << 5) + self->ext.glowParticle.r) -
            0x8000;
    }
}
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60DDE44, func_060DDE44);
void func_060DDFB0(Entity* self) {
    s32 primIndex;

    switch (self->step) {
    case 0:
        TekiInit(self, 3);
        self->step++;
        primIndex = AllocPrimitives(3, 1);
        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags |= FLAG_HAS_PRIMS;
        self->primIndex = primIndex;
        func_060DDE44(self);
        break;
    case 1:
        MoveEntity(self);
        self->velocityY += self->ext.et_060DDFB0.gravity;
        break;
    }

    func_060DDD94(self);
    if (self->ext.et_060DDFB0.unk82 <= 7) {
        DestroyEntity(self);
    }
}
void func_060DE058(Entity* self) {
    Primitive* prim;
    char* base;
    Stage15GouraudState* state;
    s16* topLeftY;
    s16* topRightY;
    s16* bottomLeftY;
    s32 offset;
    u16 shade;
    s16 y;

    prim = &g_PrimBuf[self->primIndex];
    if (prim != NULL) {
        do {
            offset = (u16)prim->unk1C * sizeof(Stage15GouraudState);
            base = (char*)SpGourTbl;
            state = (Stage15GouraudState*)(base + offset);
            prim->unk8--;
            if (prim->unk8 < 0) {
                prim->drawMode |= 8;
            }
            state->posY.i.hi = prim->y0;
            state->posY.val += state->velocityY;
            if (state->velocityY > FIX(0.5)) {
                if (prim->unkA > 3) {
                    prim->unkA -= 4;
                }
                shade = prim->unkA / 8;
                prim->unk6 =
                    ((shade << 8) << 2) + (shade << 5) + shade - 0x8000;
            } else {
                state->velocityY += FIX(0.21875);
            }
            topLeftY = &prim->y0;
            topRightY = &prim->y1;
            y = state->posY.i.hi;
            *topLeftY = *topRightY = y;
            bottomLeftY = &prim->y2;
            *bottomLeftY = prim->y3 = y;
            prim = prim->next;
        } while (prim != NULL);
    }
}
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60DE140, func_060DE140);

void func_060DE264(Entity* self) {
    s32 primIndex;

    if (self->step == 0) {
        TekiInit(self, 3);
        self->step++;
        primIndex = AllocPrimitives(3, 0x21);
        if (primIndex == -1) {
            DestroyEntity(self);
        } else {
            self->flags |= FLAG_HAS_PRIMS;
            self->primIndex = primIndex;
            func_060DE140(self);
        }
    } else {
        --self->ext.effectTimer.timer;
        if (self->ext.effectTimer.timer == 0) {
            DestroyEntity(self);
        } else {
            func_060DE058(self);
        }
    }
}
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60DE2F4, func_060DE2F4);
void func_060DE464(Entity* self) {
    switch (self->step) {
    case 0:
        TekiInit(self, 5);
        self->step++;
        self->primIndex = AllocPrimitives(0, 5);
        if (self->primIndex == -1) {
            DestroyEntity(self);
        } else {
            self->flags |= FLAG_HAS_PRIMS;
            func_060DE500(self);
            self->ext.et_060DE40C.path = &DAT_060F2044[self->params * 0x10];
        }
        return;
    case 1:
        func_060DE58C(self);
        return;
    }
}
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60DE500, func_060DE500);
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60DE58C, func_060DE58C);
void SetVdp2BackgroundColorRgb(s32, s32, s32);

void func_060DE670(Entity* self) {
    if (DAT_0605cd70.unk0 == 3) {
        SetVdp2BackgroundColorRgb(6, 0, 5);
    }
    if (self->step == 0) {
        TekiInit(self, 4);
        self->step++;
        SetVdp2BackgroundColorRgb(6, 0, 5);
    }
}

void func_060DE6CC(Entity* self) {
    func_06079BB4(self);
    func_0600B004(self->unk0, g_Stage15SpriteBank16Frames[self->animCurFrame]);
}
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60DE704, func_060DE704);
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60DE964, func_060DE964);
void func_060DEC48(void) {
    Entity* entity;
    s16 randomAngle;
    s32 count;
    s8 randomFlags;

    randomFlags = 3 & Random();
    randomAngle = ((Random() & 0xF) << 8) - 0x800;
    for (count = 0; count <= 5; count++) {
        entity = AllocEntity(&g_Entities[0xE0], &g_Entities[0x100]);
        if (entity != NULL) {
            CreateEntityFromEntity(0x46U, g_CurrentEntity, entity);
            entity->params = 2;
            entity->ext.et_060DEC48.delay = 6 - count;
            entity->ext.et_060DEC48.angle = randomAngle;
            entity->ext.et_060DEC48.flags = randomFlags;
        }
    }
}
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60DECE0, func_060DECE0);
extern u32 g_Stage15Entity30SpawnPositions[];

void func_060DF160(Entity* self) {
    Entity* entity;

    switch (self->step) {
    case 0:
        TekiInit(self, 5);
        self->step++;
        break;
    case 1:
        self->ext.spawnerTimer.timer =
            g_Stage15Entity30SpawnPositions[self->params];
        self->step++;
        break;
    case 2:
        if (--self->ext.spawnerTimer.timer == 0) {
            entity = AllocEntity(&g_Entities[0xA0], &g_Entities[0xC0]);
            if (entity != NULL) {
                CreateEntityFromEntity(0x1F, self, entity);
            }
            self->step = 1;
        }
        break;
    }
}
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60DF204, func_060DF204);
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60DF354, func_060DF354);
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60DF62C, func_060DF62C);
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60DF77C, func_060DF77C);
extern MthMatrixTbl DAT_06061DF0;

s32 func_060DF938(s32* arg0, XyInt* arg1) {
    Fixed32 point[3];
    Fixed32 value;

    value = *arg0;
    point[0] = MTH_Mul(DAT_06061DF0.current->val[0][0], value);
    point[1] = MTH_Mul(DAT_06061DF0.current->val[1][0], value);
    point[2] = (MTH_Mul(DAT_06061DF0.current->val[2][0], value) +
                DAT_06061DF0.current->val[2][3]) >>
               8;
    MTH_Pers2D((MthXyz*)point, (MthXy*)DAT_06061DE0, arg1);
    return point[2] << 8;
}
void func_060DF9B0(s32* arg0, XyInt* arg1) {
    s32 point[3];

    point[0] = arg0[0] + DAT_06061DF0.current->val[0][3];
    point[1] = arg0[1] + DAT_06061DF0.current->val[1][3];
    point[2] = (arg0[2] + DAT_06061DF0.current->val[2][3]) >> 8;
    MTH_Pers2D((MthXyz*)point, (MthXy*)DAT_06061DE0, arg1);
    arg1->x += DAT_06061DE8[0];
    arg1->y += DAT_06061DE8[1];
}
void func_060DFA1C(MthXyz* angles, MthXyz* translation) {
    s32 angle;

    MTH_ClearMatrix(&DAT_06061DF0);
    DAT_06061DF0.current->val[0][3] = translation->x;
    DAT_06061DF0.current->val[1][3] = translation->y;
    DAT_06061DF0.current->val[2][3] = translation->z;

    angle = angles->x & 0x0FFF;
    if (angle != 0) {
        func_060DFA98(&DAT_06061DF0, angle);
    }

    angle = angles->y & 0x0FFF;
    if (angle != 0) {
        func_060DFB74(&DAT_06061DF0, angle);
    }

    angle = angles->z & 0x0FFF;
    if (angle != 0) {
        func_060DFC08(&DAT_06061DF0, angle);
    }
}
void func_060DFA98(MthMatrixTbl* unused, s32 angle) {
    Fixed32 sine;
    Fixed32 cosine;
    Fixed32 y;
    Fixed32 z;

    rsincos(angle, &sine, &cosine);
    sine *= 0x10;
    cosine *= 0x10;

    y = DAT_06061DF0.current->val[0][1];
    z = DAT_06061DF0.current->val[0][2];
    DAT_06061DF0.current->val[0][1] = MTH_Mul(y, cosine) + MTH_Mul(z, sine);
    y = MTH_Mul(y, sine);
    DAT_06061DF0.current->val[0][2] = MTH_Mul(z, cosine) - y;

    y = DAT_06061DF0.current->val[1][1];
    z = DAT_06061DF0.current->val[1][2];
    DAT_06061DF0.current->val[1][1] = MTH_Mul(y, cosine) + MTH_Mul(z, sine);
    y = MTH_Mul(y, sine);
    DAT_06061DF0.current->val[1][2] = MTH_Mul(z, cosine) - y;

    y = DAT_06061DF0.current->val[2][1];
    z = DAT_06061DF0.current->val[2][2];
    DAT_06061DF0.current->val[2][1] = MTH_Mul(y, cosine) + MTH_Mul(z, sine);
    y = MTH_Mul(y, sine);
    DAT_06061DF0.current->val[2][2] = MTH_Mul(z, cosine) - y;
}
void func_060DFB74(MthMatrixTbl* unused, s32 angle) {
    Fixed32 sine;
    Fixed32 cosine;
    Fixed32 x;
    Fixed32 z;

    rsincos(angle, &sine, &cosine);
    sine *= 0x10;
    cosine *= 0x10;

    z = DAT_06061DF0.current->val[0][2];
    x = DAT_06061DF0.current->val[0][0];
    {
        Fixed32 product;
        product = MTH_Mul(z, sine);
        DAT_06061DF0.current->val[0][0] = MTH_Mul(x, cosine) - product;
    }

    z = DAT_06061DF0.current->val[1][2];
    x = DAT_06061DF0.current->val[1][0];
    {
        Fixed32 product;
        product = MTH_Mul(z, sine);
        DAT_06061DF0.current->val[1][0] = MTH_Mul(x, cosine) - product;
    }

    z = DAT_06061DF0.current->val[2][2];
    x = DAT_06061DF0.current->val[2][0];
    {
        Fixed32 product;
        product = MTH_Mul(z, sine);
        DAT_06061DF0.current->val[2][0] = MTH_Mul(x, cosine) - product;
    }
}

void func_060DFC08(MthMatrixTbl* unused, s32 angle) {
    Fixed32 sine;
    Fixed32 cosine;
    Fixed32 x;
    Fixed32 y;

    rsincos(angle, &sine, &cosine);
    sine *= 0x10;
    cosine *= 0x10;

    x = DAT_06061DF0.current->val[0][0];
    y = DAT_06061DF0.current->val[0][1];
    DAT_06061DF0.current->val[0][0] = MTH_Mul(x, cosine) + MTH_Mul(y, sine);

    x = DAT_06061DF0.current->val[1][0];
    y = DAT_06061DF0.current->val[1][1];
    DAT_06061DF0.current->val[1][0] = MTH_Mul(x, cosine) + MTH_Mul(y, sine);

    x = DAT_06061DF0.current->val[2][0];
    y = DAT_06061DF0.current->val[2][1];
    DAT_06061DF0.current->val[2][0] = MTH_Mul(x, cosine) + MTH_Mul(y, sine);
}

const u16 DAT_060DFC9C[38] = {
    0x0415, 0x1010, 0x10FF, 0x0000, 0x0412, 0x1010, 0x10FF, 0x0000,
    0x0411, 0x1010, 0x10FF, 0x0000, 0x0417, 0x1010, 0xFF00, 0x0009,
    0x0414, 0x1010, 0xFF00, 0x0009, 0x0412, 0x1510, 0xFF00, 0x0009,
    0x0411, 0x1010, 0xFF00, 0x0009, 0x0415, 0x10FF, 0x0000, 0x0009,
    0x0412, 0x15FF, 0x0000, 0x0009, 0x0411, 0xFF00,
};
void func_060DFCE8(u16 arg0) {
    Collider collider;
    Entity* self = g_CurrentEntity;
    Entity* current;

    if (self->velocityY < 0) {
        CheckCollision(self->posX.val, self->posY.val - FIX(7), &collider, 0);
        if (collider.effects & 5) {
            self->velocityY = 0;
        }
    }

    CheckCollision(self->posX.val, self->posY.val + FIX(8), &collider, 0);

    if (arg0) {
        if (!(collider.effects & 5)) {
            MoveEntity(self);
            func_06079BE4(self);
            return;
        }

        self->velocityX = 0;
        self->velocityY = 0;
        if (collider.effects & 4) {
            self->posY.val += FIX(0.125);
        } else {
            self->posY.val += collider.unk18;
        }
        self->posY.i.hi++;
        self->posY.i.lo = 0;
    } else if (!(collider.effects & 5)) {
        MoveEntity(self);
        current = g_CurrentEntity;

        if (current->velocityY >= 0) {
            current->ext.equipItemDrop.fallSpeed +=
                current->ext.equipItemDrop.gravity;
            current->velocityX = current->ext.equipItemDrop.fallSpeed;
            if (current->velocityX == FIX(1) || current->velocityX == FIX(-1)) {
                current->ext.equipItemDrop.gravity =
                    -current->ext.equipItemDrop.gravity;
            }
        }

        if (current->velocityY < FIX(0.25)) {
            current->velocityY += FIX(0.125);
        }
    }
}

extern s16 DAT_060F24D4[];
extern u16 g_Stage15AlucardSubweaponIds[];
void PlaySfx(s32 sfxId);
void SetStep(u8 step);

void func_060DFDF4(u16 cardIndex) {
    Entity* self;
    Entity* player;
    u16 params;
    s16 subWeaponId;
    s8 timer;
    u8* timerPtr;

    self = g_CurrentEntity;
    PlaySfx(0x67C);
    params = g_Status.subWeapon;
    player = g_Entities;
    subWeaponId = DAT_060F24D4[cardIndex];
    g_Status.subWeapon = subWeaponId;

    if (params == subWeaponId) {
        params = 1;
        timerPtr = self->unk6D;
        timer = 0x10;
    } else {
        params = g_Stage15AlucardSubweaponIds[params];
        timerPtr = self->unk6D;
        timer = 0x60;
    }
    *timerPtr = timer;

    if (params != 0) {
        self->params = params;
        self->posY.i.hi = player->posY.i.hi + 0xC;
        SetStep(7);
        self->unk0->flags |= 8;
        self->ext.subweaponCard.unk86 = 5;
        self->velocityY = -FIX(2.5);
        if (player->facingLeft != 1) {
            self->velocityX = -FIX(2.5);
            return;
        }
        self->velocityX = FIX(2.5);
    } else {
        DestroyEntity(self);
    }
}
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60DFED0, func_060DFED0);
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60E072C, func_060E072C);
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60E140C, func_060E140C);
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60E174C, func_060E174C);
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60E1D60, func_060E1D60);
s32 func_060E23D0(Entity* entity) {
    Entity* player = &g_Entities[0];
    s16 distance;

    distance = (s16)(player->posX.i.hi - entity->posX.i.hi);
    distance = ABS(distance);
    if (distance > 22) {
        return 0;
    }

    distance = (s16)(player->posY.i.hi - entity->posY.i.hi);
    distance = ABS(distance);
    if (distance > 32) {
        return 0;
    }

    return 1;
}
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60E2428, func_060E2428);
#include "set_entity_collision_tiles.h"

const u16 DAT_060E2864[2] = {0xCCCC, 0xCCCD};
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60E2868, func_060E2868);
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60E2F3C, func_060E2F3C);
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60E30A4, func_060E30A4);
void func_060E320C(Entity* self) {
    Entity* entity;

    switch (self->step) {
    case 0:
        TekiInit(self, 2);
        self->step++;
        self->ext.explosionEmitter.parentId =
            self->ext.explosionEmitter.parent->entityId;
        /* fall through */
    case 1:
        if (self->ext.explosionEmitter.timer++ > 4U) {
            entity = AllocEntity(&g_Entities[0xE0], &g_Entities[0x100]);
            if (entity != NULL) {
                CreateEntityFromEntity(E_EXPLOSION, self, entity);
                entity->entityId = E_EXPLOSION;
                entity->pfnUpdate = func_060E2F3C;
                entity->params = self->params;
            }
            self->ext.explosionEmitter.timer = 0;
        }

        self->posX.i.hi = self->ext.explosionEmitter.parent->posX.i.hi;
        self->posY.i.hi = self->ext.explosionEmitter.parent->posY.i.hi;
        if (self->ext.explosionEmitter.parent->entityId !=
            self->ext.explosionEmitter.parentId) {
            DestroyEntity(self);
        }
        break;
    }
}
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60E32F8, func_060E32F8);
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60E3464, func_060E3464);
#define SPAWN_DESTRUCT_ANIM_ID 19
#include "spawn_destruct_anim.h"
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60E36B4, func_060E36B4);
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60E3794, func_060E3794);
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60E3A80, func_060E3A80);
void func_060E3F58(Entity* self) {
    s32 sp0;
    s32 spriteSize;
    SpriteObject* sprite;
    s16 params;
    SaturnSpriteFrameHeader** frame;
    s32 flags;
    s32 frameType;
    s32 offset;
    s32 i;
    s32 count;

    if (self->step == 0) {
        params = (s16)self->params;
        sp0 = -0x100 & params;
        flags = 3 & params;
        frameType = 2 & flags;
        spriteSize = 6;
        if (frameType != 0) {
            spriteSize = 0x12;
        }

        sprite = CreateSpriteObject(
            g_EntitySpriteBank08.allocationIndex, g_EntitySpriteBank08.flags,
            g_EntitySpriteBank08.images, spriteSize);
        self->unk0 = sprite;
        TekiInit(self, 3);

        self->step++;
        frame = DAT_06046CD0;
        if (frameType != 0) {
            frame += 2;
        } else {
            frame += 1;
        }
        func_0600AFA8(sprite, *frame);

        if (sp0 != 0) {
            sprite->flags = (s16)sprite->flags | 0x30;
        }
        sprite->flags = (sprite->flags & 0xFFF8) | 3;
        sprite->posX = self->posX.val;
        sprite->posY = self->posY.val;

        offset = 0xB0;
        if ((1 & flags) != 0) {
            offset = 0xBD;
        }
        if ((flags & 2) != 0) {
            count = 6;
        } else {
            count = 2;
        }

        i = 0;
        for (; i < count; i++) {
            DAT_0608FFF8[offset] = 3;
            DAT_0608FFF8[offset + 1] = 3;
            DAT_0608FFF8[offset + 2] = 3;
            offset -= 0x10;
        }
    }
}
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60E4064, func_060E4064);
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60E458C, func_060E458C);

void func_060E4918(Entity* self, s32 x, s32 y) {
    s32 sin;
    s32 cos;
    s32 xOffset;
    s32 yOffset;
    Primitive* prim;
    Primitive* next;

    prim = self->ext.primHolder.prim;
    next = prim->next;
    next->x2 -= 0x80;
    rsincos(next->x2, &sin, &cos);
    sin *= 0x50;
    cos *= 0x50;
    xOffset = (sin - cos) >> 0x10;
    yOffset = (sin + cos) >> 0x10;
    prim->x0 = x + xOffset;
    prim->y0 = y - yOffset;
    prim->x1 = x + yOffset;
    prim->y1 = y + xOffset;
    prim->x2 = x - xOffset;
    prim->y2 = y + yOffset;
    prim->x3 = x - yOffset;
    prim->y3 = y - xOffset;
    prim->drawMode = 0;
}

void func_060E49D4(Entity* self, s32 arg1) {
    Primitive* prim;
    s16* priority;
    s32 newPriority;

    prim = self->ext.primHolder.prim;
    priority = &prim->next->priority;
    newPriority = *priority - arg1;
    if (newPriority < 0) {
        prim->drawMode = 8;
        newPriority = 0;
    }
    *priority = newPriority;
}

const u16 DAT_060E49FA = 0;
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60E49FC, func_060E49FC);
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60E56C8, func_060E56C8);
u16 func_060E57E0(s32 minX, s32 maxX) {
    u16 standing;

    g_Player.unk7A = 1;
    if (PLAYER.step != 0 || (standing = PLAYER.step_s) != 1 ||
        PLAYER.posX.i.hi < minX || PLAYER.posX.i.hi > maxX) {
        standing = 0;
    }
    return standing;
}
void func_060E5824(void) {
    g_Player.padSim = PAD_UP;
    g_Player.demo_timer = 1;
}
void func_060E5844(Entity* self) {
    Primitive* prim = self->ext.save.unk10;
    s32 i;

    for (i = 0; i < 9; i++) {
        prim->x3 = 0;
        prim->drawMode = DRAW_HIDE;
        prim = prim->next;
    }
}
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60E5870, func_060E5870);
extern void func_060E5CC4(s32 arg0, s32 arg1);
extern void func_060E5E84(s32 arg0, s32 arg1, s32 arg2);
extern void func_060E5FD0(s32 arg0, s32 arg1, s32 arg2);

void func_060E5C74(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    func_060E5CC4(arg1, arg3);
    func_060E5E84(arg1, arg2, arg3);
    func_060E5FD0(arg0, arg1, arg3);
}
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60E5CC4, func_060E5CC4);
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60E5E84, func_060E5E84);
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60E5FD0, func_060E5FD0);
extern void func_060E6310(s32 arg0, s32 arg1);
extern void func_060E63E0(s32 arg0, s32 arg1, s32 arg2);

void func_060E62D4(s32 arg0, s32 arg1, s32 arg2) {
    func_060E6310(arg1, arg2);
    func_060E63E0(arg0, arg1, arg2);
}
void func_060E6310(s32 scale, s32 unused) {
    s32* dst_base;
    s32* dst;
    s32* dst1;
    s32* src;
    s32* src1;
    s32 factor;
    s32 i;
    s32 limit;

    dst_base = DAT_060485e0;
    src = g_Stage15Entity08ModelVertices14[0];
    dst = dst_base;
    factor = scale << 8;
    i = 0;
    limit = 13;
    src1 = src + 1;
    dst1 = dst_base + 1;

    for (; i <= limit; i++) {
        dst[0] = src[0] * factor;
        dst1[0] = src1[0] * factor;
        dst1[1] = src1[1] * factor;
        src += 3;
        dst += 3;
        src1 += 3;
        dst1 += 3;
    }

    SetCurrentMatrixBinAngle(&DAT_060FB0D0, &DAT_060FB0E0);

    DAT_06061DF0.current->val[0][0] = DAT_06061DF0.current->val[0][0] * 5 / 4;
    DAT_06061DF0.current->val[0][1] = DAT_06061DF0.current->val[0][1] * 5 / 4;
    DAT_06061DF0.current->val[0][2] = DAT_06061DF0.current->val[0][2] * 5 / 4;

    TransformAndProjectPoints(dst_base, dst_base + 0x102, 14, &DAT_06061DF0);
}
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60E63E0, func_060E63E0);
extern u8 g_Stage15SpriteBank23Frames[];
extern u8 g_Stage15SkeletonBeastAnimations[];
extern s16 g_Stage15BoneScimitarGroundSensors[];
void SyncSpriteObjectPosUnchecked(Entity* self, s16* offset);

void func_060E654C(Entity* self) {
    SaturnSpriteImage* images = g_Stage15SpriteBank23Images;
    SaturnSpriteResource* bank = &g_Stage15SpriteBankSkeletonBeast;

    self->unk0 =
        CreateSpriteObject(bank->allocationIndex, bank->flags, images, 5);

    self->ext.spriteAnimEnemy.frames = g_Stage15SpriteBank23Frames;
    self->ext.spriteAnimEnemy.animations = g_Stage15SkeletonBeastAnimations;
    self->ext.spriteAnimEnemy.unk80 = 0;
    self->ext.spriteAnimEnemy.unk81 = 0;
    self->ext.spriteAnimEnemy.unk82 = 0;

    SyncSpriteObjectPosUnchecked(self, g_Stage15BoneScimitarGroundSensors);
    self->step++;
}
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60E65CC, func_060E65CC);
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60E6B30, func_060E6B30);
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60E6CB8, func_060E6CB8);
extern u32 DAT_060F4018[];

void func_060E6E64(Entity* self) {
    func_06079BB4(self);
    func_0600B004(self->unk0, DAT_060F4018[self->animCurFrame]);
}

const u16 DAT_060E6E9C = 0xAAAA;
const u16 DAT_060E6E9E = 0xAAAB;
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60E6EA0, func_060E6EA0);
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60E7564, func_060E7564);
void func_060E7780(Entity* self) {
    if (self->step == 0) {
        self->unk0 = CreateSpriteObject(
            g_Stage15SpriteBankRedGargoyle[0].allocationIndex,
            g_Stage15SpriteBankRedGargoyle[0].flags,
            g_Stage15SpriteBank24Images, 1);
        SyncSpriteObjectPosUnchecked(self, &DAT_060F2F04);
        self->step = 1;
        TekiInit(self, 5);
        self->ext.gargoyle.clutBase = self->unk0->clutBase;

        switch (self->ext.gargoyle.variant) {
        case 1:
            self->animCurFrame = 1;
            self->unk0->clutBase = self->ext.gargoyle.clutBase;
            break;
        case 2:
            self->animCurFrame = 0x3A;
            self->unk0->clutBase = self->ext.gargoyle.clutBase + 9;
            break;
        case 0:
            self->animCurFrame = 0x3B;
            self->unk0->clutBase = self->ext.gargoyle.clutBase + 0x12;
            break;
        }

        self->unk0->zPriority -= 2;
        func_06079BB4(self);
        func_0600B004(
            self->unk0, g_Stage15SpriteBank24Frames[self->animCurFrame]);
    }
}
void func_060E7888(u8 arg0) {
    g_CurrentEntity->velocityX = 0;
    g_CurrentEntity->ext.et_060E7888.unk79 = 0;
    g_CurrentEntity->pose = 0;
    g_CurrentEntity->poseTimer = 0;
    g_CurrentEntity->step = arg0;
}
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60E78B8, func_060E78B8);
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60E8A7C, func_060E8A7C);
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60E8BBC, func_060E8BBC);
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60E8D50, func_060E8D50);
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60E8FD4, func_060E8FD4);
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60E9144, func_060E9144);
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60E94A0, func_060E94A0);
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60E95E8, func_060E95E8);
void func_060E991C(Entity* entity) {
    entity->unk0 = CreateSpriteObject(
        g_Stage15SpriteBankHumanFaceTree.allocationIndex,
        g_Stage15SpriteBankHumanFaceTree.flags, g_Stage15SpriteBank26Images, 5);
    SyncSpriteObjectPosUnchecked(
        entity, g_Stage15SpriteBank25PackedSpriteParts);
    entity->step = 1;
}
extern u32 DAT_060F7EFC[];

void func_060E996C(Entity* self) {
    func_06079BB4(self);
    func_0600B004(self->unk0, DAT_060F7EFC[self->animCurFrame]);
}
extern s16 DAT_060F6D4C[];
extern s8 DAT_060F6D98[];

s16 func_060E99A4(Entity* self) {
    s16* frames;
    s8* hitbox;
    s16 distance;

    frames = DAT_060F6D4C;
    distance = PLAYER.posX.i.hi - self->posX.i.hi;
    hitbox = DAT_060F6D98;
    if (distance > *frames) {
        do {
            frames += 2;
            hitbox += 4;
        } while (distance > *frames);
    }
    self->animCurFrame = *++frames;
    self->hitboxOffX = hitbox[0];
    self->hitboxOffY = hitbox[1];
    self->hitboxWidth = hitbox[2];
    self->hitboxHeight = hitbox[3];
    if (distance < 0) {
        distance = -distance;
    }
    return distance;
}
extern Point16 DAT_060F6D78[];
extern s32 rsin(s32);
extern s32 rcos(s32);

void func_060E9A14(Entity* self, Entity* parts) {
    s16* table0;
    Point16* table1;
    s16* rotate;
    s16 angle;
    s16 distance;
    s32 index;
    s32 i;
    Entity* part;

    part = parts;
    i = 0;
    rotate = &self->rotate;
    index = 0;
    do {
        table0 = (s16*)DAT_060F6D78;
        table1 = DAT_060F6D78;
        distance = *(s16*)((char*)table0 + index);
        table1 = (Point16*)((char*)table1 + index);
        angle = table1->y;
        part->posX.val =
            self->posX.val + distance * rsin(*rotate + angle) * 0x10;
        i += 1;
        part->posY.val =
            self->posY.val - distance * rcos(angle + *rotate) * 0x10;
        part += 1;
        index += 4;
    } while (i <= 7);
}
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60E9AAC, func_060E9AAC);
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60E9AEC, func_060E9AEC);
void func_060E9CA0(void) {
    u8 values[8];
    s32 i;
    s32 init_index;
    u8 random_value;
    s32 index;

    i = 0;
    init_index = 0;
    do {
        values[init_index] = init_index;
        init_index += 1;
    } while (init_index <= 7);

    if (i != 8) {
        do {
            random_value = Random();
            index = (u8)(random_value % (8 - i));
            DAT_060FB0EC[i] = values[index];
            if (index <= 7) {
                do {
                    values[index] = values[index + 1];
                    index += 1;
                } while (index <= 7);
            }
            i += 1;
        } while (i != 8);
    }
}
void func_060E9D38(Entity* self) {
    if (self->ext.et_060E9D38.nextSlot == 0 &&
        self->ext.et_060E9D38.running == 0) {
        u8 values[8];
        s32 i;
        s32 init_index;
        u8 random_value;
        s32 index;

        i = 0;
        for (init_index = 0; init_index <= 7; init_index++) {
            values[init_index] = init_index;
        }
        while (i != 8) {
            random_value = Random();
            index = (u8)(random_value % (8 - i));
            DAT_060FB0EC[i] = values[index];
            while (index <= 7) {
                values[index] = values[index + 1];
                index++;
            }
            i++;
        }
        self->ext.et_060E9D38.running = 1;
        self->ext.et_060E9D38.delay = 0;
    }
    if (self->ext.et_060E9D38.running != 0) {
        self->ext.et_060E9D38.delay++;
        if (self->ext.et_060E9D38.delay == 0x20) {
            s32 offset =
                DAT_060FB0EC[self->ext.et_060E9D38.nextSlot] * sizeof(Entity) +
                2 * sizeof(Entity);

            ((Entity*)((u8*)self + offset))->step = 3;
            self->ext.et_060E9D38.delay = 0;
            self->ext.et_060E9D38.nextSlot++;
            if (self->ext.et_060E9D38.nextSlot == 8) {
                self->ext.et_060E9D38.running = 0;
            }
        }
    }
}
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60E9E44, func_060E9E44);
void func_060EAA68(Entity* entity) {
    entity->unk0 = CreateSpriteObject(
        g_Stage15SpriteBankHumanFaceTree.allocationIndex,
        g_Stage15SpriteBankHumanFaceTree.flags, g_Stage15SpriteBank26Images, 2);
    entity->step = 1;
}
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60EAAA8, func_060EAAA8);
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60EACDC, func_060EACDC);
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60EB2B8, func_060EB2B8);
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60EB728, func_060EB728);
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60EB7EC, func_060EB7EC);
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60EB824, func_060EB824);
void func_060EB9AC(Entity* self) {
    SpriteObject* sprite;
    SaturnSpriteImage* images;
    SaturnSpriteResource* bank;

    images = g_Stage15SpriteBank26Images;
    bank = &g_Stage15SpriteBankHumanFaceTree;
    sprite = CreateSpriteObject(bank->allocationIndex, bank->flags, images, 4);
    self->unk0 = sprite;
    sprite->zPriority -= 8;
    self->posY.i.hi += 0x1E;
    self->step = 1;
}
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60EBA00, func_060EBA00);
void func_060EBA98(Entity* entity) {
    entity->unk0 = CreateSpriteObject(
        g_Stage15SpriteBankWaterLeaper.allocationIndex,
        g_Stage15SpriteBankWaterLeaper.flags, g_Stage15SpriteBank27Images, 5);
    SyncSpriteObjectPosUnchecked(entity, g_Stage15WaterLeaperInitOffset);
    entity->unk0->flags |= 0x40;
    entity->step++;
}
extern u32 DAT_060F86CC[];

void func_060EBAF4(Entity* self) {
    func_06079BB4(self);
    func_0600B004(self->unk0, DAT_060F86CC[self->animCurFrame]);
}
void CreateEntityFromCurrentEntity(u16 entityId, Entity* entity);
void func_06079BCC(void);
extern s16 DAT_060F8246;

s32 func_060EBB2C(Entity* self, s16 arg1) {
    s32 result = 0;
    s32 splashY;
    Entity* splash;
    volatile s32 stack_temp[9];

    func_06079BCC();
    splashY = (DAT_060F8246 - g_Tilemap.scrollY.i.hi) - arg1;
    if (self->posY.i.hi >= splashY && self->ext.et_060EBB2C.unk88 < splashY) {
        if (self->ext.et_060EBB2C.unk9C == 0) {
            splash = AllocEntity(&g_Entities[0xE0], &g_Entities[0x100]);
            if (splash != NULL) {
                CreateEntityFromCurrentEntity(0x18, splash);
                splash->posY.i.hi = DAT_060F8246 - g_Tilemap.scrollY.i.hi;
                splash->velocityY = self->velocityY;
            }
            PlaySfx(0x913);
            self->ext.et_060EBB2C.unk9C = 1;
        }
        self->ext.et_060EBB2C.unkA2 = 0;
        self->rotate &= 0xFFF;
        self->ext.et_060EBB2C.unk94 = 0;
        SetStep(8);
    }
    func_06079BB4(self);
    return result;
}

const u16 DAT_060EBC1C = 0xAAAA;
const u16 DAT_060EBC1E = 0xAAAB;
const u16 DAT_060EBC20 = 0xCCCC;
const u16 DAT_060EBC22 = 0xCCCD;
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60EBC24, func_060EBC24);
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60ECB7C, func_060ECB7C);
void func_060ECCE8(StatusFlagContext* context) {
    if (context->enabled != 0) {
        *context->flags |= FLAG_UNK_10;
    } else {
        *context->flags &= ~FLAG_UNK_10;
    }
}
extern u32 DAT_060F8B10[];

void func_060ECD14(Entity* self) {
    func_06079BB4(self);
    func_0600B004(self->unk0, DAT_060F8B10[self->animCurFrame]);
}
void func_060ECD4C(Entity* self) {
    s32 posX;

    if (self[2].ext.et_060ECD4C.unk91 == 0) {
        if (self->facingLeft == 0) {
            self->posX.val -= FIX(0.25);
            self->posY.val -= FIX(0.375);
        } else {
            self->posX.val += FIX(0.25);
            self->posY.val -= FIX(0.375);
        }
    } else {
        posX = self->posX.val;
        if (self->facingLeft == 0) {
            posX += FIX(0.25);
        } else {
            posX -= FIX(0.25);
        }
        self->posX.val = posX;
        self->posY.val += FIX(0.375);
    }
}

void func_060ECDBC(Entity* entity) {
    entity->unk0 = CreateSpriteObject(
        g_Stage15SpriteBankVenusManTrap.allocationIndex,
        g_Stage15SpriteBankVenusManTrap.flags, g_Stage15SpriteBank28Images, 2);
    SyncSpriteObjectPosUnchecked(entity, DAT_060F87AC);
    entity->step = 1;
}
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60ECE0C, func_060ECE0C);
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60ED1C0, func_060ED1C0);
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60ED848, func_060ED848);
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60EDA88, func_060EDA88);
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60EDD10, func_060EDD10);
extern u32 DAT_060F9470[];

void func_060EDF48(Entity* self) {
    func_06079BB4(self);
    func_0600B004(self->unk0, DAT_060F9470[self->animCurFrame]);
}
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60EDF80, func_060EDF80);
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60EE4B8, func_060EE4B8);
void func_060EE5F4(Entity* entity) {
    entity->unk0 = CreateSpriteObject(
        g_Stage15SpriteBankGardener.allocationIndex,
        g_Stage15SpriteBankGardener.flags, g_Stage15SpriteBank30Images, 11);
    SyncSpriteObjectPosUnchecked(entity, DAT_060F96D4);
    entity->step = 1;
}
void func_060EE644(Entity* self) {
    func_06079BB4(self);
    func_0600B004(self->unk0, DAT_060FA59C[self->animCurFrame]);
}
s32 GetSideToPlayer(Entity* self);

void func_060EE67C(Entity* self) {
    self->facingLeft = (u8)((GetSideToPlayer(self) & 1) ^ 1);
    if (self->facingLeft == 0) {
        self->unk0->flags &= ~0x10;
    } else {
        self->unk0->flags |= 0x10;
    }
}

const u16 DAT_060EE6C0[2] = {0xAAAA, 0xAAAB};
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60EE6C4, func_060EE6C4);
void func_060EEE20(Entity* self) {
    Entity* parent;

    switch (self->step) {
    case 0:
        TekiInit(self, 0x23);
        self->step = 1;
        self->ext.et_060EEE20.savedHitboxState = self->hitboxState;
        /* fall through */
    case 1:
        parent = self->ext.et_060EEE20.parent;
        switch (parent->step) {
        case 4:
            self->hitboxState = self->ext.et_060EEE20.savedHitboxState;
            self->posX.i.hi = parent->posX.i.hi;
            self->posY.i.hi = parent->posY.i.hi - 5;
            self->facingLeft = parent->facingLeft;
            if (self->facingLeft != 0) {
                self->posX.i.hi += 0x30;
            } else {
                self->posX.i.hi -= 0x30;
            }
            self->hitboxWidth = 0x18;
            self->hitboxHeight = 4;
            return;
        case 6:
            DestroyEntity(self);
            return;
        default:
            self->hitboxState = 0;
            break;
        }
        break;
    }
}
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60EEEE4, func_060EEEE4);
void func_060EF074(Entity* entity, s16 step) {
    entity->velocityX = 0;
    entity->velocityY = 0;
    entity->pose = 0;
    entity->poseTimer = 0;
    entity->step = step;
    entity->step_s = 0;
}
s32 func_060EF09C(s32* arg0, s32* arg1) {
    s32 result;

    result = 0;
    if (arg0[1] > arg1[1]) {
        result = 1;
    }
    if (arg0[2] > arg1[2]) {
        result |= 2;
    }
    return result;
}

const unsigned short DAT_060EF0BC = 0x8888;
const unsigned short DAT_060EF0BE = 0x8889;
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60EF0C0, func_060EF0C0);
extern s8 DAT_060FA794[];
extern void DestroyEntity(Entity*);

void func_060EF5E0(Entity* self) {
    Entity* entity = self - 1;
    s32 index;
    s8* data;

    switch (self->step) {
    case 0:
        TekiInit(self, 0x1A6);
        self->step++;
        /* fall through */
    case 1:
        if ((u16)(entity->animCurFrame - 0x14) <= 10) {
            index = entity->animCurFrame * 4;
            data = DAT_060FA794 + index;
            self->hitboxWidth = DAT_060FA794[index];
            self->hitboxHeight = data[1];
            self->hitboxOffX = data[2];
            self->hitboxOffY = data[3];
        } else {
            self->hitboxWidth = 0;
            self->hitboxHeight = 0;
            self->hitboxOffX = 0;
            self->hitboxOffY = 0;
        }
        self->facingLeft = entity->facingLeft;
        self->hitboxState = entity->hitboxState;
        self->posX.i.hi = entity->posX.i.hi;
        self->posY.i.hi = entity->posY.i.hi;
        if (entity->entityId != 0x40) {
            DestroyEntity(self);
        }
        break;
    }
}

const u16 DAT_060EF6D8[4] = {
    0x8888,
    0x8889,
    0xCCCC,
    0xCCCD,
};
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60EF6E0, func_060EF6E0);
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60EFF44, func_060EFF44);
