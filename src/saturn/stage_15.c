// SPDX-License-Identifier: AGPL-3.0-or-later
#include "inc_asm.h"
#include "sattypes.h"

#include "stage_15.h"
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60DC040, func_060DC040);
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60DC1A8, func_060DC1A8);
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60DC328, func_060DC328);
typedef struct {
    u32 unk0;
    u32 unk4;
    u16 unk8;
    u16 unkA;
} Stage15SpriteBank16;

extern Stage15SpriteBank16 g_Stage15SpriteBank16;
extern u32 g_Stage15SpriteBank16Frames[];
extern void TekiInit(Entity* self, s32 arg);
extern void func_0600AFA8(SpriteObject*, SaturnSpriteFrameHeader*);

void func_060DC428(Entity* self) {
    SpriteObject* sprite;
    register u32 frameOffset;

    if (self->step == 0) {
        TekiInit(self, 5);
        self->step++;
        sprite = CreateSpriteObject(
            (u16)g_Stage15SpriteBank16.unk8, (u16)g_Stage15SpriteBank16.unkA,
            g_Stage15SpriteBank16.unk0, 1);
        self->unk0 = sprite;
        self->animCurFrame = 0x2A;
        frameOffset = 0xA8;
        func_0600AFA8(
            sprite,
            *(SaturnSpriteFrameHeader**)((u8*)g_Stage15SpriteBank16Frames +
                                         frameOffset));
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
extern s32 AllocPrimitives();
extern void TekiInit(Entity*, s32);
extern void MoveEntity(Entity*);
extern void func_060DDB74();
extern void func_060DDA10();
extern void DestroyEntity(Entity*);

void func_060DDCE8(Entity* self) {
    s32 primIndex;

    switch (self->step) {
    case 0:
        TekiInit(self, 3);
        self->step++;
        primIndex = AllocPrimitives(0x8002, 1);
        if (primIndex == -1) {
            ((void (*)(Entity*))DestroyEntity)(self);
            return;
        }
        self->flags |= 0x800000;
        self->primIndex = primIndex;
        func_060DDB74(self);
        break;
    case 1:
        MoveEntity(self);
        self->velocityY += self->ext.ILLEGAL.u32[0];
        break;
    }

    func_060DDA10(self);
    if (self->ext.ILLEGAL.s16[8] <= 0x82) {
        ((void (*)(Entity*))DestroyEntity)(self);
    }
}
typedef struct {
    u8 pad0[4];
    s16 posX;
    u8 pad6[2];
    s16 posY;
    u8 padA[0x56];
    s16 primIndex;
    u8 pad62[0x1E];
    u8 unk80;
    u8 unk81;
    u8 unk82;
} Func060DDD94Arg;

void func_060DDD94(Func060DDD94Arg* arg0) {
    Primitive* prim;
    s16 x;
    s16 y;

    x = arg0->posX;
    y = arg0->posY;
    prim = &g_PrimBuf[arg0->primIndex];

    prim->x0 = prim->x3 = x;
    prim->x1 = prim->x2 = x + 1;
    prim->y0 = prim->y1 = y;
    prim->y2 = prim->y3 = y + 1;

    if (arg0->unk82 > 7) {
        arg0->unk80 -= 6;
        arg0->unk81 -= 6;
        arg0->unk82 -= 8;
        prim->unk6 =
            ((arg0->unk82 << 10) + (arg0->unk81 << 5) + arg0->unk80) - 0x8000;
    }
}
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60DDE44, func_060DDE44);
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60DDFB0, func_060DDFB0);
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60DE058, func_060DE058);
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60DE140, func_060DE140);
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60DE264, func_060DE264);
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60DE2F4, func_060DE2F4);
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60DE464, func_060DE464);
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60DE500, func_060DE500);
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60DE58C, func_060DE58C);
void SetVdp2BackgroundColorRgb(s32, s32, s32);
void TekiInit(Entity*, s32);

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
extern void func_06079BB4(Entity* self);
extern void func_0600B004(SpriteObject* sprite, u32 imageIndex);
extern u32 g_Stage15SpriteBank16Frames[];

void func_060DE6CC(Entity* self) {
    func_06079BB4(self);
    func_0600B004(self->unk0, g_Stage15SpriteBank16Frames[self->animCurFrame]);
}
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60DE704, func_060DE704);
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60DE964, func_060DE964);
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60DEC48, func_060DEC48);
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60DECE0, func_060DECE0);
extern u32 g_Stage15Entity30SpawnPositions[];
void TekiInit(Entity*, s32);

void func_060DF160(Entity* self) {
    Entity* entity;

    switch (self->step) {
    case 0:
        TekiInit(self, 5);
        self->step++;
        break;
    case 1:
        self->ext.ILLEGAL.u32[0] =
            g_Stage15Entity30SpawnPositions[self->params];
        self->step++;
        break;
    case 2:
        if (--self->ext.ILLEGAL.u32[0] == 0) {
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
typedef struct Func060DF938Params {
    Fixed32 unk0;
    Fixed32 unk4;
    Fixed32 unk8;
    Fixed32 unkC;
    Fixed32 unk10;
    Fixed32 unk14;
    Fixed32 unk18;
    Fixed32 unk1C;
    Fixed32 unk20;
    Fixed32 unk24;
    Fixed32 unk28;
    Fixed32 unk2C;
} Func060DF938Params;

typedef struct Func060DF938State {
    s32 unk0;
    Func060DF938Params* unk4;
} Func060DF938State;

extern Func060DF938State DAT_06061DF0;

s32 func_060DF938(s32* arg0, XyInt* arg1) {
    Fixed32 point[3];
    Fixed32 value;

    value = *arg0;
    point[0] = MTH_Mul(DAT_06061DF0.unk4->unk0, value);
    point[1] = MTH_Mul(DAT_06061DF0.unk4->unk10, value);
    point[2] =
        (MTH_Mul(DAT_06061DF0.unk4->unk20, value) + DAT_06061DF0.unk4->unk2C) >>
        8;
    MTH_Pers2D((MthXyz*)point, (MthXy*)DAT_06061DE0, arg1);
    return point[2] << 8;
}
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60DF9B0, func_060DF9B0);
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60DFA1C, func_060DFA1C);
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60DFA98, func_060DFA98);
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60DFB74, func_060DFB74);
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60DFC08, func_060DFC08);
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60DFCE8, func_060DFCE8);
extern void PlaySfx(s32 sfxId);
extern void SetStep(u8 step);
extern void DestroyEntity(Entity* entity);
extern s16 DAT_060F24D4[];
extern u16 g_Stage15AlucardSubweaponIds[];

void func_060DFDF4(u16 arg0) {
    Entity* entity;
    Entity* entities;
    u16 subWeaponId;
    s16 subWeapon;
    s8 timer;
    u8* timerPtr;

    entity = g_CurrentEntity;
    PlaySfx(0x067C);
    subWeaponId = (u16)g_Status.subWeapon;
    entities = g_Entities;
    subWeapon = DAT_060F24D4[arg0];
    g_Status.subWeapon = (u32)subWeapon;

    if (subWeaponId == subWeapon) {
        subWeaponId = 1;
        timerPtr = entity->unk6D;
        timer = 0x10;
    } else {
        subWeaponId = g_Stage15AlucardSubweaponIds[subWeaponId];
        timerPtr = entity->unk6D;
        timer = 0x60;
    }
    *timerPtr = timer;

    if (subWeaponId != 0) {
        entity->params = subWeaponId;
        entity->posY.i.hi = entities->posY.i.hi + 0x0C;
        SetStep(7);
        entity->unk0->flags |= 8;
        entity->ext.ILLEGAL.u16[7] = 5;
        entity->velocityY = -0x28000;
        if (entities->facingLeft != 1) {
            entity->velocityX = -0x28000;
            return;
        }
        entity->velocityX = 0x28000;
    } else {
        DestroyEntity(entity);
    }
}
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60DFED0, func_060DFED0);
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60E072C, func_060E072C);
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60E140C, func_060E140C);
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60E174C, func_060E174C);
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60E1D60, func_060E1D60);
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60E23D0, func_060E23D0);
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60E2428, func_060E2428);
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60E27E0, func_060E27E0);
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60E2868, func_060E2868);
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60E2F3C, func_060E2F3C);
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60E30A4, func_060E30A4);
void func_060E320C(Entity* self) {
    extern void TekiInit(Entity*, s32);
    extern void DestroyEntity(Entity*);
    Entity* entity;

    switch (self->step) {
    case 0:
        TekiInit(self, 2);
        self->step++;
        self->ext.ILLEGAL.u16[8] =
            ((Entity*)self->ext.ILLEGAL.u32[1])->entityId;
        /* fall through */
    case 1:
        if (self->ext.ILLEGAL.u8[0]++ > 4U) {
            entity = AllocEntity(&g_Entities[0xE0], &g_Entities[0x100]);
            if (entity != NULL) {
                CreateEntityFromEntity(2, self, entity);
                entity->entityId = 2;
                entity->pfnUpdate = func_060E2F3C;
                entity->params = self->params;
            }
            self->ext.ILLEGAL.u8[0] = 0;
        }

        self->posX.i.hi = ((Entity*)self->ext.ILLEGAL.u32[1])->posX.i.hi;
        self->posY.i.hi = ((Entity*)self->ext.ILLEGAL.u32[1])->posY.i.hi;
        if (((Entity*)self->ext.ILLEGAL.u32[1])->entityId !=
            self->ext.ILLEGAL.u16[8]) {
            DestroyEntity(self);
        }
        break;
    }
}
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60E32F8, func_060E32F8);
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60E3464, func_060E3464);
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60E3598, func_060E3598);
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60E36B4, func_060E36B4);
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60E3794, func_060E3794);
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60E3A80, func_060E3A80);
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60E3F58, func_060E3F58);
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60E4064, func_060E4064);
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60E458C, func_060E458C);
typedef struct Func060E4918Primitive {
    char pad0[0x0C];
    s16 x0;
    s16 y0;
    s16 x1;
    s16 y1;
    s16 x2;
    s16 y2;
    s16 x3;
    s16 y3;
    s16 pad1C;
    s16 unk1E;
    struct Func060E4918Primitive* next;
} Func060E4918Primitive;

typedef struct {
    char pad0[0x84];
    Func060E4918Primitive* prim;
} Func060E4918Entity;

extern void rsincos(s16 angle, s32* sin, s32* cos);

void func_060E4918(Func060E4918Entity* arg0, s32 arg1, s32 arg2) {
    s32 sp0;
    s32 sp4;
    s32 temp_r7;
    s32 temp_r3;
    Func060E4918Primitive* temp_r8;
    Func060E4918Primitive* temp_r2;

    temp_r8 = arg0->prim;
    temp_r2 = temp_r8->next;
    temp_r2->x2 -= 0x80;
    rsincos(temp_r2->x2, &sp0, &sp4);
    sp0 *= 0x50;
    sp4 *= 0x50;
    temp_r7 = (sp0 - sp4) >> 0x10;
    temp_r3 = (sp0 + sp4) >> 0x10;
    temp_r8->x0 = arg1 + temp_r7;
    temp_r8->y0 = arg2 - temp_r3;
    temp_r8->x1 = arg1 + temp_r3;
    temp_r8->y1 = arg2 + temp_r7;
    temp_r8->x2 = arg1 - temp_r7;
    temp_r8->y2 = arg2 + temp_r3;
    temp_r8->x3 = arg1 - temp_r3;
    temp_r8->y3 = arg2 - temp_r7;
    temp_r8->unk1E = 0;
}
typedef struct SubStruct060E49D4 {
    char pad0[0x02];
    s16 unk2;
} SubStruct060E49D4;

typedef struct MainStruct060E49D4 {
    char pad0[0x1E];
    s16 unk1E;
    SubStruct060E49D4* unk20;
} MainStruct060E49D4;

typedef struct Arg0Struct060E49D4 {
    char pad0[0x84];
    MainStruct060E49D4* unk84;
} Arg0Struct060E49D4;

void func_060E49D4(Arg0Struct060E49D4* arg0, s32 arg1) {
    MainStruct060E49D4* temp_r2;
    s16* temp_r3;
    s32 var_r1;

    temp_r2 = arg0->unk84;
    temp_r3 = &temp_r2->unk20->unk2;
    var_r1 = *temp_r3 - arg1;
    if (var_r1 < 0) {
        temp_r2->unk1E = 8;
        var_r1 = 0;
    }
    *temp_r3 = var_r1;
}

const u16 DAT_060E49FA = 0;
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60E49FC, func_060E49FC);
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60E56C8, func_060E56C8);
u16 func_060E57E0(s32 arg0, s32 arg1) {
    u16 var_r0;

    g_Player.unk7A = 1;
    if (((u16)(s16)g_Entities->step != 0) ||
        (var_r0 = (u16)(s16)g_Entities->step_s, var_r0 != 1) ||
        (g_Entities->posX.i.hi < arg0) || (g_Entities->posX.i.hi > arg1)) {
        var_r0 = 0;
    }
    return var_r0;
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
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60E6310, func_060E6310);
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60E63E0, func_060E63E0);
extern u8 g_Stage15SpriteBank23Frames[];
extern u8 g_Stage15SkeletonBeastAnimations[];
extern u8 g_Stage15BoneScimitarGroundSensors[];
extern void SyncSpriteObjectPosUnchecked(Entity* entity);

typedef void (*SyncSpriteObjectPosUncheckedProc)(Entity*, void*);

void func_060E654C(Entity* self) {
    SaturnSpriteImage* images = g_Stage15SpriteBank23Images;
    u8* spriteBank = g_Stage15SpriteBankSkeletonBeast;

    self->unk0 = CreateSpriteObject(
        *(u16*)(spriteBank + 8), *(u16*)(spriteBank + 10), images, 5);

    *(u8**)((u8*)self + 0x78) = g_Stage15SpriteBank23Frames;
    *(u8**)((u8*)self + 0x7C) = g_Stage15SkeletonBeastAnimations;
    ((u8*)self)[0x80] = 0;
    ((u8*)self)[0x81] = 0;
    ((u8*)self)[0x82] = 0;

    ((SyncSpriteObjectPosUncheckedProc)SyncSpriteObjectPosUnchecked)(
        self, g_Stage15BoneScimitarGroundSensors);
    self->step++;
}
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60E65CC, func_060E65CC);
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60E6B30, func_060E6B30);
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60E6CB8, func_060E6CB8);
extern void func_06079BB4(Entity* self);
extern void func_0600B004(SpriteObject* sprite, u32 imageIndex);
extern u32 DAT_060F4018[];

void func_060E6E64(Entity* self) {
    func_06079BB4(self);
    func_0600B004(self->unk0, DAT_060F4018[self->animCurFrame]);
}

const u16 DAT_060E6E9C = 0xAAAA;
const u16 DAT_060E6E9E = 0xAAAB;
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60E6EA0, func_060E6EA0);
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60E7564, func_060E7564);
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60E7780, func_060E7780);
void func_060E7888(u8 arg0) {
    g_CurrentEntity->velocityX = 0;
    g_CurrentEntity->ext.ILLEGAL.u8[1] = 0;
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
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60E991C, func_060E991C);
extern void func_06079BB4(Entity* self);
extern void func_0600B004(SpriteObject* sprite, u32 imageIndex);
extern u32 DAT_060F7EFC[];

void func_060E996C(Entity* self) {
    func_06079BB4(self);
    func_0600B004(self->unk0, DAT_060F7EFC[self->animCurFrame]);
}
extern s16 DAT_060F6D4C;
extern s8 DAT_060F6D98;

s16 func_060E99A4(Entity* arg0) {
    s16* var_r3;
    s8* var_r7;
    s16 var_r0;

    var_r3 = &DAT_060F6D4C;
    var_r0 = g_Entities[0].posX.i.hi - arg0->posX.i.hi;
    var_r7 = &DAT_060F6D98;
    if (var_r0 > *var_r3) {
        do {
            var_r3 += 2;
            var_r7 += 4;
        } while (var_r0 > *var_r3);
    }
    arg0->animCurFrame = *++var_r3;
    arg0->hitboxOffX = var_r7[0];
    arg0->hitboxOffY = var_r7[1];
    arg0->hitboxWidth = var_r7[2];
    arg0->hitboxHeight = var_r7[3];
    if (var_r0 < 0) {
        var_r0 = -var_r0;
    }
    return var_r0;
}
extern Point16 DAT_060F6D78[];
extern s32 rsin(s32);
extern s32 rcos(s32);

void func_060E9A14(Entity* arg0, Entity* arg1) {
    s16* table0;
    Point16* table1;
    s16* sp0;
    s16 temp_r8;
    s16 temp_r9;
    s32 var_r10;
    s32 var_r12;
    Entity* var_r11;

    var_r11 = arg1;
    var_r12 = 0;
    sp0 = &arg0->rotate;
    var_r10 = 0;
    do {
        table0 = (s16*)DAT_060F6D78;
        table1 = DAT_060F6D78;
        temp_r9 = *(s16*)((char*)table0 + var_r10);
        table1 = (Point16*)((char*)table1 + var_r10);
        temp_r8 = table1->y;
        var_r11->posX.val =
            arg0->posX.val + temp_r9 * rsin(*sp0 + temp_r8) * 0x10;
        var_r12 += 1;
        var_r11->posY.val =
            arg0->posY.val - temp_r9 * rcos(temp_r8 + *sp0) * 0x10;
        var_r11 += 1;
        var_r10 += 4;
    } while (var_r12 <= 7);
}
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60E9AAC, func_060E9AAC);
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60E9AEC, func_060E9AEC);
extern u8 DAT_060FB0EC[];

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
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60E9D38, func_060E9D38);
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60E9E44, func_060E9E44);
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60EAA68, func_060EAA68);
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60EAAA8, func_060EAAA8);
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60EACDC, func_060EACDC);
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60EB2B8, func_060EB2B8);
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60EB728, func_060EB728);
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60EB7EC, func_060EB7EC);
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60EB824, func_060EB824);
void func_060EB9AC(Entity* self) {
    SpriteObject* sprite;
    SaturnSpriteImage* images;
    u16* tree;

    images = g_Stage15SpriteBank26Images;
    tree = (u16*)g_Stage15SpriteBankHumanFaceTree;
    sprite = CreateSpriteObject(tree[4], tree[5], images, 4);
    self->unk0 = sprite;
    sprite->zPriority -= 8;
    self->posY.i.hi += 0x1E;
    self->step = 1;
}
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60EBA00, func_060EBA00);
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60EBA98, func_060EBA98);
extern void func_06079BB4(Entity* self);
extern void func_0600B004(SpriteObject* sprite, u32 imageIndex);
extern u32 DAT_060F86CC[];

void func_060EBAF4(Entity* self) {
    func_06079BB4(self);
    func_0600B004(self->unk0, DAT_060F86CC[self->animCurFrame]);
}
extern Entity* AllocEntity(Entity*, Entity*);
extern void CreateEntityFromCurrentEntity(u16, Entity*);
extern void PlaySfx(s32);
extern void SetStep(u8);
extern void func_06079BCC(void);
extern s16 DAT_060F8246;

s32 func_060EBB2C(Entity* arg0, s16 arg1) {
    s32 result = 0;
    s32 temp_r2;
    Entity* temp_r0;
    volatile s32 stack_temp[9];

    func_06079BCC();
    temp_r2 = (DAT_060F8246 - g_Tilemap.scrollY.i.hi) - arg1;
    if (arg0->posY.i.hi >= temp_r2 && arg0->ext.ILLEGAL.s32[4] < temp_r2) {
        if (arg0->ext.ILLEGAL.u8[0x24] == 0) {
            temp_r0 = AllocEntity(&g_Entities[0xE0], &g_Entities[0x100]);
            if (temp_r0 != NULL) {
                CreateEntityFromCurrentEntity(0x18, temp_r0);
                temp_r0->posY.i.hi = DAT_060F8246 - g_Tilemap.scrollY.i.hi;
                temp_r0->velocityY = arg0->velocityY;
            }
            PlaySfx(0x913);
            arg0->ext.ILLEGAL.u8[0x24] = 1;
        }
        arg0->ext.ILLEGAL.u8[0x2A] = 0;
        arg0->rotate &= 0x0FFF;
        arg0->ext.ILLEGAL.u16[0xE] = 0;
        SetStep(8);
    }
    func_06079BB4(arg0);
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
extern void func_06079BB4(Entity* self);
extern void func_0600B004(SpriteObject* sprite, u32 imageIndex);
extern u32 DAT_060F8B10[];

void func_060ECD14(Entity* self) {
    func_06079BB4(self);
    func_0600B004(self->unk0, DAT_060F8B10[self->animCurFrame]);
}
typedef struct {
    u8 pad[0x91];
    u8 unk91;
} Func060ECD4CUnk170;

typedef struct {
    u8 pad0[4];
    s32 posX;
    s32 posY;
    u8 padC[0x0C];
    u16 facingLeft;
    u8 pad1A[0x156];
    Func060ECD4CUnk170 unk170;
} Func060ECD4CArg;

void func_060ECD4C(Func060ECD4CArg* arg0) {
    s32 var_r2;

    if (((Func060ECD4CUnk170*)((u8*)arg0 + 0x170))->unk91 == 0) {
        if (*(u16*)((u8*)arg0 + 0x18) == 0) {
            arg0->posX -= 0x4000;
            arg0->posY -= 0x6000;
        } else {
            arg0->posX += 0x4000;
            arg0->posY -= 0x6000;
        }
    } else {
        var_r2 = arg0->posX;
        if (*(u16*)((u8*)arg0 + 0x18) == 0) {
            var_r2 += 0x4000;
        } else {
            var_r2 -= 0x4000;
        }
        arg0->posX = var_r2;
        arg0->posY += 0x6000;
    }
}

const u16 DAT_060ECDBA = 0x0009;
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60ECDBC, func_060ECDBC);
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60ECE0C, func_060ECE0C);
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60ED1C0, func_060ED1C0);
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60ED848, func_060ED848);
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60EDA88, func_060EDA88);
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60EDD10, func_060EDD10);
extern void func_06079BB4(Entity* self);
extern void func_0600B004(SpriteObject* sprite, u32 imageIndex);
extern u32 DAT_060F9470[];

void func_060EDF48(Entity* self) {
    func_06079BB4(self);
    func_0600B004(self->unk0, DAT_060F9470[self->animCurFrame]);
}
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60EDF80, func_060EDF80);
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60EE4B8, func_060EE4B8);
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60EE5F4, func_060EE5F4);
extern void func_0600B004(SpriteObject* sprite, u32 imageIndex);

void func_060EE644(Entity* self) {
    func_06079BB4(self);
    func_0600B004(self->unk0, DAT_060FA59C[self->animCurFrame]);
}
s32 GetSideToPlayer(Entity* self);

void func_060EE67C(Entity* self) {
    self->facingLeft = (u8)((GetSideToPlayer(self) & 1) ^ 1);
    if (self->facingLeft == 0) {
        (*(u16*)(*(u32*)self)) &= ~0x10;
    } else {
        (*(u16*)(*(u32*)self)) |= 0x10;
    }
}

const u16 DAT_060EE6C0[2] = {0xAAAA, 0xAAAB};
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60EE6C4, func_060EE6C4);
extern void TekiInit(Entity*, s32);
extern void DestroyEntity(Entity*);

void func_060EEE20(Entity* self) {
    Entity* parent;

    switch (self->step) {
    case 0:
        TekiInit(self, 0x23);
        self->step = 1;
        self->ext.ILLEGAL.u16[4] = self->hitboxState;
        /* fall through */
    case 1:
        parent = (Entity*)self->ext.ILLEGAL.u32[0];
        switch (parent->step) {
        case 4:
            self->hitboxState = self->ext.ILLEGAL.u16[4];
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
    s32 var_r0;

    var_r0 = 0;
    if (arg0[1] > arg1[1]) {
        var_r0 = 1;
    }
    if (arg0[2] > arg1[2]) {
        var_r0 |= 2;
    }
    return var_r0;
}

const unsigned short DAT_060EF0BC = 0x8888;
const unsigned short DAT_060EF0BE = 0x8889;
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60EF0C0, func_060EF0C0);
extern s8 DAT_060FA794[];
extern void TekiInit(Entity*, s32);
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
