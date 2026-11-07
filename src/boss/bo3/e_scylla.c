// SPDX-License-Identifier: AGPL-3.0-or-later
#include "bo3.h"

typedef struct {
    AnimateEntityFrame* anim;
    s16 values[4];
} ScyllaPartInit;

struct EntityScylla {
    ENTITY_SHARED;
    /* 0x7C */ struct Primitive* prim;
    /* 0x80 */ s16 timer;
    /* 0x82 */ s16 : 16;
    /* 0x84 */ u8 : 8;
    /* 0x85 */ u8 tailAttack;
    /* 0x86 */ u8 flip;
    /* 0x87 */ u8 : 8;
    /* 0x88 */ s32 : 32;
    /* 0x8C */ s16 orbAngle;
    /* 0x8E */ s16 : 16;
    /* 0x90 */ char pad_90[0xC];
    /* 0x9C */ struct Entity* target;
    /* 0xA0 */ struct Primitive* curPrim;
    /* 0xA4 */ u8 splashed;
};
SYNC_STRUCT(EntityScylla);

s32 g_BossMgrState = BOSS_MGR_IDLE;

static AnimateEntityFrame D_us_80180D4C[] = {
    POSE(18, 1, 0), POSE(18, 2, 0), POSE(18, 3, 0), POSE(18, 2, 0),
    POSE_LOOP(0)};
static AnimateEntityFrame D_us_80180D58[] = {
    POSE(4, 1, 0), POSE(7, 5, 0), POSE(7, 6, 0),  POSE(7, 7, 0),
    POSE(7, 8, 0), POSE(7, 9, 0), POSE(7, 10, 0), POSE_END};
static AnimateEntityFrame D_us_80180D68[] = {
    POSE(8, 7, 0), POSE(8, 8, 0), POSE(8, 9, 0), POSE(8, 10, 0), POSE_LOOP(0)};
static AnimateEntityFrame D_us_80180D74[] = {
    POSE(4, 9, 0),  POSE(4, 10, 0), POSE(2, 7, 0),  POSE(2, 6, 0),
    POSE(1, 11, 0), POSE(1, 12, 0), POSE(1, 13, 0), POSE(48, 14, 0),
    POSE(6, 15, 0), POSE(6, 16, 0), POSE(2, 1, 0),  POSE_END};
static AnimateEntityFrame D_us_80180D8C[] = {
    POSE(2, 1, 0),  POSE(10, 20, 0), POSE(10, 21, 0), POSE(8, 22, 0),
    POSE(8, 23, 0), POSE(8, 24, 0),  POSE(1, 25, 0),  POSE_END};
static AnimateEntityFrame D_us_80180D9C[] = {
    POSE(8, 22, 0), POSE(8, 23, 0), POSE(8, 24, 0), POSE(8, 25, 0),
    POSE_LOOP(0)};
static AnimateEntityFrame D_us_80180DA8[] = {
    POSE(2, 22, 0),  POSE(8, 23, 0), POSE(10, 26, 0),
    POSE(10, 27, 0), POSE(8, 1, 0),  POSE_END};
static AnimateEntityFrame D_us_80180DB4[] = {
    POSE(1, 1, 0),   POSE(3, 17, 0),  POSE(3, 18, 0),
    POSE(16, 19, 0), POSE(16, 19, 0), POSE(6, 18, 0),
    POSE(6, 17, 0),  POSE(1, 1, 0),   POSE_END};
static AnimateEntityFrame D_us_80180DC8[] = {
    POSE(1, 1, 0), POSE(4, 17, 0), POSE(4, 18, 0), POSE(64, 19, 0), POSE_END};
AnimateEntityFrame D_us_80180DD4[] = {
    POSE(20, 28, 0), POSE(20, 29, 0), POSE(20, 30, 0), POSE(20, 29, 0),
    POSE_LOOP(0)};
AnimateEntityFrame D_us_80180DE0[] = {
    POSE(1, 28, 0), POSE(1, 31, 0), POSE_LOOP(0)};
AnimateEntityFrame D_us_80180DE8[] = {
    POSE(1, 28, 0),  POSE(10, 32, 0), POSE(16, 33, 0), POSE(10, 34, 0),
    POSE(16, 35, 0), POSE(10, 36, 0), POSE(16, 37, 0), POSE(8, 38, 0),
    POSE(8, 39, 0),  POSE(8, 40, 0),  POSE(8, 41, 0),  POSE(8, 28, 0),
    POSE_END};
AnimateEntityFrame D_us_80180E04[] = {
    POSE(2, 28, 0), POSE(6, 46, 0), POSE(6, 47, 0),
    POSE(6, 48, 0), POSE(6, 49, 0), POSE(22, 50, 0),
    POSE(8, 32, 0), POSE(1, 33, 0), POSE_END};
AnimateEntityFrame D_us_80180E18[] = {
    POSE(4, 33, 0), POSE(6, 42, 0), POSE(6, 43, 0), POSE(6, 44, 0),
    POSE(6, 45, 0), POSE(2, 28, 0), POSE_END};
static AnimateEntityFrame anim_unused_0[] = {
    POSE(32, 28, 0), POSE(4, 36, 0),  POSE(6, 37, 0),  POSE(4, 51, 0),
    POSE(6, 52, 0),  POSE(4, 53, 0),  POSE(26, 54, 0), POSE(6, 53, 0),
    POSE(6, 52, 0),  POSE(4, 51, 0),  POSE(4, 34, 0),  POSE(6, 35, 0),
    POSE(6, 55, 0),  POSE(4, 56, 0),  POSE(26, 57, 0), POSE(6, 56, 0),
    POSE(6, 55, 0),  POSE(4, 32, 0),  POSE(6, 33, 0),  POSE(6, 58, 0),
    POSE(4, 59, 0),  POSE(26, 60, 0), POSE(6, 59, 0),  POSE(6, 58, 0),
    POSE(2, 28, 0),  POSE_END};
AnimateEntityFrame D_us_80180E5C[] = {
    POSE(16, 28, 0), POSE(4, 36, 0), POSE(6, 37, 0),  POSE(4, 51, 0),
    POSE(6, 52, 0),  POSE(4, 53, 0), POSE(10, 54, 0), POSE_END};
AnimateEntityFrame D_us_80180E6C[] = {
    POSE(16, 54, 0), POSE(6, 53, 0), POSE(6, 52, 0), POSE(4, 51, 0),
    POSE(4, 34, 0),  POSE(6, 35, 0), POSE(6, 55, 0), POSE(4, 56, 0),
    POSE(10, 57, 0), POSE_END};
AnimateEntityFrame D_us_80180E80[] = {
    POSE(16, 57, 0), POSE(6, 56, 0),  POSE(6, 55, 0),
    POSE(4, 32, 0),  POSE(6, 33, 0),  POSE(6, 58, 0),
    POSE(4, 59, 0),  POSE(10, 60, 0), POSE_END};
AnimateEntityFrame D_us_80180E94[] = {
    POSE(16, 60, 0), POSE(6, 59, 0), POSE(6, 58, 0), POSE(2, 28, 0), POSE_END};
static AnimateEntityFrame D_us_80180EA0[] = {
    POSE(20, 61, 0), POSE(20, 62, 0), POSE(20, 63, 0), POSE(20, 62, 0),
    POSE_LOOP(0)};
static AnimateEntityFrame D_us_80180EAC[] = {
    POSE(4, 62, 0),  POSE(20, 63, 0), POSE(20, 62, 0),
    POSE(20, 61, 0), POSE(16, 62, 0), POSE_LOOP(0)};
static AnimateEntityFrame D_us_80180EB8[] = {
    POSE(20, 64, 0), POSE(20, 65, 0), POSE(20, 66, 0), POSE(20, 65, 0),
    POSE_LOOP(0)};
static AnimateEntityFrame D_us_80180EC4[] = {
    POSE(20, 67, 0), POSE(20, 68, 0), POSE(20, 69, 0), POSE_LOOP(0)};
static AnimateEntityFrame D_us_80180ECC[] = {
    POSE(20, 70, 0), POSE(20, 71, 0), POSE(20, 72, 0), POSE(20, 71, 0),
    POSE_LOOP(0)};
AnimateEntityFrame D_us_80180ED8[] = {
    POSE(8, 80, 0), POSE(8, 81, 0), POSE(8, 82, 0), POSE(8, 83, 0),
    POSE_LOOP(0)};
AnimateEntityFrame D_us_80180EE4[] = {
    POSE(1, 85, 0), POSE(1, 88, 0), POSE(1, 86, 0), POSE(1, 89, 0),
    POSE(1, 87, 0), POSE(1, 90, 0), POSE_LOOP(0)};
AnimateEntityFrame D_us_80180EF4[] = {
    POSE(4, 91, 0), POSE(4, 92, 0), POSE(4, 93, 0), POSE(4, 94, 0),
    POSE(1, 85, 0), POSE(1, 88, 0), POSE(1, 86, 0), POSE(1, 89, 0),
    POSE(1, 87, 0), POSE(1, 90, 0), POSE_END};
AnimateEntityFrame D_us_80180F0C[] = {
    POSE(7, 95, 0), POSE(7, 96, 0), POSE(7, 97, 0),
    POSE(7, 98, 0), POSE(7, 99, 0), POSE_END};
AnimateEntityFrame D_us_80180F18[] = {
    POSE(8, 100, 0), POSE(8, 101, 0), POSE(8, 100, 0), POSE(8, 102, 0),
    POSE_LOOP(0)};
AnimateEntityFrame D_us_80180F24[] = {
    POSE(4, 100, 0), POSE(4, 101, 0), POSE(4, 100, 0), POSE(4, 102, 0),
    POSE_LOOP(0)};
AnimateEntityFrame D_us_80180F30[] = {
    POSE(2, 100, 0), POSE(8, 103, 0), POSE(8, 104, 0),  POSE(8, 105, 0),
    POSE(8, 106, 0), POSE(8, 107, 0), POSE(16, 108, 0), POSE_END};
AnimateEntityFrame D_us_80180F40[] = {
    POSE(8, 109, 0), POSE(8, 108, 0), POSE(8, 110, 0),
    POSE(8, 108, 0), POSE_LOOP(0),
};

ScyllaPartInit D_us_80180F4C[] = {
    {D_us_80180EA0, {0x0086, 0x0078, 0x00B0, 0x0000}},
    {D_us_80180EAC, {0x0084, 0x0088, 0x00B0, 0x0000}},
    {D_us_80180EB8, {0x0090, 0x0050, 0x00AC, 0x0000}},
    {D_us_80180EC4, {0x0086, 0x0024, 0x0090, 0x0000}},
    {D_us_80180ECC, {0x0084, 0x0020, 0x0088, 0x0000}},
};

s16 D_us_80180F88[] = {16, 8, 8, 8};
s16 D_us_80180F90[] = {0, 8, 0, 4, 4, -4, -8, 0};
s16 D_us_80180FA0[] = {-16, -16, 0, 0};
s16 D_us_80180FA8[] = {16, -16, 0, 0};
s16 D_us_80180FB0[] = {-16, 16, 0, 0};
s16 D_us_80180FB8[] = {16, 16, 0, 0};

// unused
static AnimateEntityFrame anim_unused_1[] = {
    POSE(16, 73, 0), POSE(16, 74, 0), POSE(16, 73, 0), POSE(16, 75, 0),
    POSE_LOOP(0)};

static s32 func_us_801A2A90(Primitive* prim, s32 amount) {
    s32 isEnd;
    s32 i, j;
    u8* pColor;
    s32 col;

    pColor = &prim->r0;
    isEnd = 0;
    for (i = 0; i < 2; i++) {
        for (j = 0; j < 3; j++, pColor++) {
            col = *pColor;
            col = col - amount;
            if (col <= 0) {
                col = 0;
            } else {
                isEnd = 1;
            }
            *pColor = col;
        }
        pColor += 9;
    }
    return isEnd;
}

extern EInit g_EInitScylla;
extern u16 D_us_80180C66;
void EntityScylla(struct EntityScylla* self) {
    Entity* entity;
    s32 i;
    s32 rand;

    if (g_BossMgrState & BOSS_MGR_TERMINATED) {
        DestroyEntity((Entity*)self);
        return;
    }

    if ((self->flags & FLAG_DEAD) && self->step != 6) {
        SetStep(6);
    }

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitScylla);
        self->zPriority = 0x88;
        self->hitboxOffX = 6;
        self->hitboxOffY = -0x30;
        self->hitboxWidth = 4;
        self->hitboxHeight = 0x1C;
        self->nextPart = (Entity*)self + 1;
        self->parent = NULL;
        entity = (Entity*)self + 1;
        CreateEntityFromEntity(E_ID(SCYLLA_WOLF_HEAD), (Entity*)self, entity);
        entity->zPriority = self->zPriority + 1;
        entity->nextPart = (Entity*)self;
        entity->parent = (Entity*)self;
        SetStep(1);
        /* fall through */
    case 1:
        AnimateEntity(D_us_80180D4C, (Entity*)self);
#ifdef VERSION_PSP
        if (GetDistanceToPlayerX() < 160) {
#else
        if (GetDistanceToPlayerX() < 176 || self->hitFlags) {
#endif
            g_api.TimeAttackController(
                TIMEATTACK_EVENT_SCYLLA_DEFEAT, TIMEATTACK_SET_VISITED);
            D_us_80180C66 |= 0x10;
            D_us_80180C66 |= 0x20;
            entity = (Entity*)self + 2;
            CreateEntityFromEntity(E_ID(WYRM), (Entity*)self, entity);
            entity->zPriority = self->zPriority;
            entity->posX.i.hi = 0x48 - g_Tilemap.scrollX.i.hi;
            entity->posY.i.hi = 0x90 - g_Tilemap.scrollY.i.hi;
            entity->params = 1;
            entity = (Entity*)self + 15;
            CreateEntityFromEntity(E_ID(WYRM), (Entity*)self, entity);
            entity->zPriority = self->zPriority - 2;
            entity->posX.i.hi = 0x48 - g_Tilemap.scrollX.i.hi;
            entity->posY.i.hi = 0x90 - g_Tilemap.scrollY.i.hi;
            entity->params = 2;
            entity = (Entity*)self + 28;
            CreateEntityFromEntity(E_ID(WYRM), (Entity*)self, entity);
            entity->zPriority = self->zPriority - 4;
            entity->posX.i.hi = 0x48 - g_Tilemap.scrollX.i.hi;
            entity->posY.i.hi = 0x90 - g_Tilemap.scrollY.i.hi;
            entity->params = 3;
            g_BossMgrState |= BOSS_MGR_FIGHT_ON;
            SetStep(2);
        }
        break;

    case 2:
        if (!self->step_s) {
            self->timer = 0x50;
            self->step_s++;
        }
        AnimateEntity(D_us_80180D4C, (Entity*)self);
        if (self->hitFlags & 3) {
            SetStep(5);
        }
        if (!--self->timer) {
            if (self->flip) {
                SetStep(4);
            } else {
                SetStep(3);
            }
            self->flip ^= 1;
        }
        break;

    case 5:
        if (!self->step_s) {
            PlaySfxPositional(SFX_SCYLLA_PAIN);
            self->step_s++;
        }
        if (!AnimateEntity(D_us_80180DB4, (Entity*)self)) {
            SetStep(2);
            self->step_s = 1;
        }
        break;

    case 3:
        switch (self->step_s) {
        case 0:
            if (!AnimateEntity(D_us_80180D58, (Entity*)self)) {
                SetSubStep(1);
            }
            break;

        case 1:
            entity = AllocEntity(&g_Entities[160], &g_Entities[192]);
            if (entity != NULL) {
                CreateEntityFromEntity(
                    E_ID(SCYLLA_WATER_BLADE), (Entity*)self, entity);
                entity->posX.i.hi += 0x14;
                entity->posY.i.hi -= 0x34;
                entity->zPriority = self->zPriority - 1;
                ((struct EntityScylla*)entity)->target = (Entity*)self;
            }
            for (i = 0; i < 6; i++) {
                entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
                if (entity != NULL) {
                    CreateEntityFromEntity(
                        E_ID(SCYLLA_WATER_ORB_BEAM), (Entity*)self, entity);
                    entity->posY.i.hi = 0xD8 - g_Tilemap.scrollY.i.hi;
                    entity->posX.i.hi =
                        self->posX.i.hi + 0x30 + (Random() & 0x7F);
                    entity->params = i;
                }
            }
            self->tailAttack = 0;
            self->timer = 0x50;
            PlaySfxPositional(SFX_SCYLLA_ATTACK_YELL);
            self->step_s++;
            /* fall through */
        case 2:
            AnimateEntity(D_us_80180D68, (Entity*)self);
            if (!--self->timer) {
                SetSubStep(3);
            }
            break;

        case 3:
            if (!AnimateEntity(D_us_80180D74, (Entity*)self)) {
                SetStep(2);
            }
            if (!self->poseTimer && self->pose == 4) {
                PlaySfxPositional(SFX_SCYLLA_ATTACK_DIE);
                self->tailAttack = 1;
            }
            break;
        }
        break;

    case 4:
        switch (self->step_s) {
        case 0:
            if (!AnimateEntity(D_us_80180D8C, (Entity*)self)) {
                SetSubStep(1);
            }
            break;

        case 1:
            self->timer = 0x40;
            self->step_s++;
            /* fall through */
        case 2:
            AnimateEntity(D_us_80180D9C, (Entity*)self);
            if (!(self->timer & 7)) {
                entity = AllocEntity(&g_Entities[160], &g_Entities[192]);
                if (entity != NULL) {
                    CreateEntityFromEntity(
                        E_ID(SCYLLA_BUBBLE_SKULL), (Entity*)self, entity);
                    entity->posY.i.hi = 0xBC - g_Tilemap.scrollY.i.hi;
                    entity->posX.i.hi += (Random() & 0x7F) + 0x30;
                }
            }
            if (!--self->timer) {
                SetSubStep(3);
            }
            break;

        case 3:
            if (!AnimateEntity(D_us_80180DA8, (Entity*)self)) {
                SetStep(2);
            }
            break;
        }
        break;

    case 6:
        switch (self->step_s) {
        case 0:
            g_api.TimeAttackController(
                TIMEATTACK_EVENT_SCYLLA_DEFEAT, TIMEATTACK_SET_RECORD);
            g_BossMgrState |= BOSS_MGR_DEFEAT;
            g_CastleFlags[SCYLLA_DEFEATED] = 1;
            PlaySfxPositional(SFX_SCYLLA_DEATH);
            self->hitboxState = 0;
            self->step_s++;
            /* fall through */
        case 1:
            if (!AnimateEntity(D_us_80180DC8, (Entity*)self)) {
                SetSubStep(2);
            }
            break;

        case 2:
            self->timer = 0x80;
            g_api.PlaySfx(SFX_BOSS_LARGE_FLAMES);
            g_BossMgrState |= BOSS_MGR_FLAMES_1_START;
            self->step_s++;
            /* fall through */
        case 3:
            if (!(g_Timer & 0x1F)) {
                g_api.PlaySfx(SFX_FIREBALL_SHOT_A);
            }
            for (i = 0; i < 4; i++) {
                entity = AllocEntity(&g_Entities[64], &g_Entities[256]);
                if (entity != NULL) {
                    CreateEntityFromEntity(
                        E_ID(EXPLODE_PUFF_OPAQUE), (Entity*)self, entity);
                    entity->zPriority = 0x98;
                    entity->params = 1;
                    rand = Random();
                    entity->posX.i.hi += rand - 0x40;
                    entity->posY.i.hi = 0xD8;
                    if (rand < 0x40) {
                        entity->posY.i.hi = 0xB0;
                    }
                }
            }
            if (!--self->timer) {
                g_BossMgrState |= BOSS_MGR_FLAMES_1_END;
                self->step_s++;
            }
            break;

        case 4:
            self->timer = 0x50;
            g_BossMgrState |= BOSS_MGR_FLAMES_2_START;
            PlaySfxPositional(SFX_BOSS_LARGE_FLAMES);
            self->step_s++;
            /* fall through */
        case 5:
            if (!(g_Timer & 0x1F)) {
                g_api.PlaySfx(SFX_FIREBALL_SHOT_B);
            }
            for (i = 0; i < 2; i++) {
                entity = AllocEntity(&g_Entities[64], &g_Entities[256]);
                if (entity != NULL) {
                    CreateEntityFromEntity(
                        E_ID(EXPLODE_PUFF_OPAQUE), (Entity*)self, entity);
                    entity->zPriority = 0x98;
                    entity->params = 2;
                    entity->posX.i.hi += (Random() & 0x3F) - 0x20;
                    entity->posY.i.hi = 0xC0;
                }
            }
            if (!--self->timer) {
                g_BossMgrState |= BOSS_MGR_FLAMES_2_END;
                self->step_s++;
            }
            break;

        case 6:
            self->timer = 0x60;
            PlaySfxPositional(SFX_BOSS_LARGE_FLAMES);
            self->step_s++;
            /* fall through */
        case 7:
            if (!(g_Timer & 0x1F)) {
                g_api.PlaySfx(SFX_FIREBALL_SHOT_C);
            }
            for (i = 0; i < 1; i++) {
                entity = AllocEntity(&g_Entities[64], &g_Entities[256]);
                if (entity != NULL) {
                    CreateEntityFromEntity(
                        E_ID(EXPLODE_PUFF_OPAQUE), (Entity*)self, entity);
                    entity->zPriority = 0x98;
                    entity->params = 3;
                    entity->posX.i.hi += (Random() & 0x1F) - 0x10;
                    entity->posY.i.hi = 0xB0;
                }
            }
            if (!--self->timer) {
                self->step_s++;
            }
            break;

        case 8:
            D_us_80180C66 &= ~0x10;
            D_us_80180C66 &= ~0x20;
            g_BossMgrState |= BOSS_MGR_TERMINATED;
            entity = AllocEntity(&g_Entities[160], &g_Entities[192]);
            if (entity != NULL) {
                CreateEntityFromEntity(
                    E_ID(LIFE_UP_SPAWN), (Entity*)self, entity);
                entity->posX.i.hi = 0xC0 - g_Tilemap.scrollX.i.hi;
                entity->posY.i.hi = 0x80 - g_Tilemap.scrollY.i.hi;
                entity->params = 3;
                DestroyEntity((Entity*)self);
            }
            break;
        }
        break;

    case 0xFF:
        FntPrint("charal %x\n", self->animCurFrame);
        if (g_pads[1].pressed & PAD_SQUARE) {
            if (self->params) {
                break;
            }
            self->animCurFrame++;
            self->params |= 1;
        } else {
            self->params = 0;
        }
        if (g_pads[1].pressed & PAD_CIRCLE) {
            if (self->step_s) {
                break;
            }
            self->animCurFrame--;
            self->step_s |= 1;
        } else {
            self->step_s = 0;
        }
        self->posX.i.hi = 0x80;
        self->posY.i.hi = 0x80;
        break;
    }
}

extern EInit g_EInitScyllaWolfHead;
void EntityScyllaWolfHead(struct EntityScylla* self) {
    Entity* newEntity;
    s32 i;
    s32 animEnd;

    if ((self->flags & FLAG_DEAD) && self->step != 6) {
        SetStep(6);
    }

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitScyllaWolfHead);
        self->hitboxOffX = 0x14;
        self->hitboxOffY = -0xE;
        self->hitboxWidth = 0x18;
        self->hitboxHeight = 0x14;
        SetStep(1);
        /* fall through */
    case 1:
        AnimateEntity(D_us_80180DD4, (Entity*)self);
        if (g_BossMgrState & BOSS_MGR_FIGHT_ON) {
            SetStep(2);
        }
        break;

    case 2:
        switch (self->step_s) {
        case 0:
            self->timer = 0x60;
            self->step_s++;
            /* fall through */
        case 1:
            AnimateEntity(D_us_80180DD4, (Entity*)self);
            if (!(Random() & 0x7F)) {
                SetSubStep(2);
            }
            if (!--self->timer) {
                if (self->flip) {
                    SetStep(4);
                } else {
                    SetStep(3);
                }
                self->flip ^= 1;
            }
            break;

        case 2:
            if (!AnimateEntity(D_us_80180DE8, (Entity*)self)) {
                SetSubStep(1);
            }
            if (!self->pose && self->pose == 6) {
                PlaySfxPositional(SFX_WARG_ATTACK);
            }
            break;
        }
        break;

    case 5:
        switch (self->step_s) {
        case 0:
            self->timer = 0x20;
            PlaySfxPositional(SFX_WARG_GROWL);
            self->step_s++;
            /* fall through */
        case 1:
            AnimateEntity(D_us_80180DE0, (Entity*)self);
            if (!--self->timer) {
                SetSubStep(2);
            }
            break;

        case 2:
            if (!AnimateEntity(D_us_80180DE8, (Entity*)self)) {
                SetStep(2);
            }
            break;
        }
        break;

    case 3:
        switch (self->step_s) {
        case 0:
            self->timer = 0x28;
            PlaySfxPositional(SFX_WARG_GROWL);
            self->step_s++;
            /* fall through */
        case 1:
            AnimateEntity(D_us_80180DE0, (Entity*)self);
            if (!--self->timer) {
                SetSubStep(2);
            }
            break;

        case 2:
            if (!AnimateEntity(D_us_80180E04, (Entity*)self)) {
                SetSubStep(3);
            }
            break;

        case 3:
            newEntity = AllocEntity(&g_Entities[160], &g_Entities[192]);
            if (newEntity != NULL) {
                CreateEntityFromEntity(
                    E_ID(SCYLLA_WATER_ORB), (Entity*)self, newEntity);
                newEntity->posX.i.hi += 0x30;
                newEntity->posY.i.hi -= 8;
                newEntity->zPriority = self->zPriority + 1;
            }
            self->step_s++;
            /* fall through */
        case 4:
            if (!AnimateEntity(D_us_80180E18, (Entity*)self)) {
                SetStep(2);
            }
            break;
        }
        break;

    case 4:
        switch (self->step_s) {
        case 0:
            animEnd = AnimateEntity(D_us_80180E5C, (Entity*)self);
            if (!self->poseTimer && self->pose == 1) {
                g_api.PlaySfx(SFX_WARG_DEATH_HOWL);
            }
            if (!animEnd) {
                SetSubStep(1);
            }
            break;

        case 1:
            animEnd = AnimateEntity(D_us_80180E6C, (Entity*)self);
            if (!self->poseTimer && self->pose == 1) {
                g_api.PlaySfx(SFX_WARG_DEATH_HOWL);
            }
            if (!animEnd) {
                SetSubStep(2);
            }
            break;

        case 2:
            animEnd = AnimateEntity(D_us_80180E80, (Entity*)self);
            if (!self->poseTimer && self->pose == 1) {
                g_api.PlaySfx(SFX_WARG_DEATH_HOWL);
            }
            if (!animEnd) {
                SetSubStep(3);
            }
            break;

        case 3:
            animEnd = 1;
            if (!AnimateEntity(D_us_80180E94, (Entity*)self)) {
                SetStep(2);
                return;
            }
            break;
        }
        if (!animEnd) {
            g_api.PlaySfx(SFX_SCYLLA_WYRM_WALL_DEBRIS);
            g_api.ShakeCamera(1);
            for (i = 0; i < 8; i++) {
                newEntity = AllocEntity(&g_Entities[160], &g_Entities[192]);
                if (newEntity != NULL) {
                    CreateEntityFromEntity(
                        E_ID(SCYLLA_FALLING_ROCK), (Entity*)self, newEntity);
                    newEntity->posY.i.hi = 0;
                    newEntity->posX.i.hi = self->posX.i.hi + (Random() & 0x7F);
                    newEntity->zPriority = self->zPriority + 2;
                }
            }
        }
        break;

    case 6:
        switch (self->step_s) {
        case 0:
            self->hitboxState = 0;
            PlaySfxPositional(SFX_WARG_GROWL);
            self->step_s++;
            /* fall through */
        case 1:
            AnimateEntity(D_us_80180DE0, (Entity*)self);
            if (g_BossMgrState & BOSS_MGR_FLAMES_2_START) {
                self->step_s++;
            }
            break;

        case 2:
            self->drawFlags |= ENTITY_SCALEX | ENTITY_SCALEY;
            self->scaleX = self->scaleY = 0x100;
            self->step_s++;
            /* fall through */
        case 3:
            AnimateEntity(D_us_80180DE0, (Entity*)self);
            if (self->scaleX > 0x80) {
                self->scaleX = --self->scaleY;
            }
            break;
        }
        if (g_BossMgrState & BOSS_MGR_FLAMES_2_END) {
            DestroyEntity((Entity*)self);
        }
        break;
    }
}

extern EInit g_EInitScyllaTentacles;
void EntityScyllaTentacles(Entity* self) {
    ScyllaPartInit* part;

    if (g_BossMgrState & BOSS_MGR_FLAMES_1_END) {
        DestroyEntity(self);
        return;
    }

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitScyllaTentacles);
        part = &D_us_80180F4C[self->params];
        self->zPriority = part->values[0];
        self->posX.i.hi = part->values[1] - g_Tilemap.scrollX.i.hi;
        self->posY.i.hi = part->values[2] - g_Tilemap.scrollY.i.hi;
        /* fall through */
    case 1:
        part = &D_us_80180F4C[self->params];
        AnimateEntity(part->anim, self);
        if (g_BossMgrState & BOSS_MGR_DEFEAT) {
            self->step++;
        }
        break;

    case 2:
        switch (self->step_s) {
        case 0:
            if (g_BossMgrState & BOSS_MGR_FLAMES_1_START) {
                self->step_s++;
            }
            break;

        case 1:
            self->drawFlags |= ENTITY_SCALEX | ENTITY_SCALEY;
            self->scaleX = self->scaleY = 0x100;
            self->step_s++;
            /* fall through */
        case 2:
            if (self->scaleX > 0x80) {
                self->scaleX = --self->scaleY;
            }
            break;
        }
        part = &D_us_80180F4C[self->params];
        AnimateEntity(part->anim, self);
        break;
    }
}

extern EInit g_EInitScyllaWaterBlade;
void EntityScyllaWaterBlade(struct EntityScylla* self) {
    Entity* entity;
    Primitive* prim;
    s32 primIndex;
    s16 angle;
    s32 dx;
    s32 dy;
    long p, flag;
    VECTOR trans;
    MATRIX m;
    SVECTOR rot = {0};

    if (g_BossMgrState & BOSS_MGR_DEFEAT) {
        DestroyEntity((Entity*)self);
        return;
    }

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitScyllaWaterBlade);
        self->timer = 0x20;
        self->drawFlags = ENTITY_SCALEX | ENTITY_SCALEY;
        self->scaleX = self->scaleY = 0;
        /* fall through */
    case 1:
        if (self->timer) {
            self->timer--;
            break;
        }
        AnimateEntity(D_us_80180ED8, (Entity*)self);
        if (self->scaleX < 0x100) {
            self->scaleX = self->scaleY += 8;
        }
        entity = self->target;
        if (((struct EntityScylla*)entity)->tailAttack) {
            SetStep(2);
        }
        break;

    case 2:
        self->animCurFrame = 0;
        self->zPriority = 0x8C;
        entity = &PLAYER;
        dx = entity->posX.i.hi - self->posX.i.hi;
        dy = entity->posY.i.hi - self->posY.i.hi;
        angle = ratan2(dy, dx);
        self->velocityX = rcos(angle) * 9 << 3;
        self->velocityY = rsin(angle) * 9 << 3;
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 2);
        if (primIndex == -1) {
            DestroyEntity((Entity*)self);
            return;
        }
        self->flags |= FLAG_HAS_PRIMS;
        self->primIndex = primIndex;
        prim = &g_PrimBuf[primIndex];
        self->prim = prim;
        UnkPolyFunc2(prim);
        prim->tpage = 0x12;
        prim->clut = 0x203;
        prim->u0 = prim->u2 = 0x60;
        prim->u1 = prim->u3 = 0x7F;
        prim->v0 = prim->v1 = 0xE0;
        prim->v2 = prim->v3 = 0xFF;
        prim->priority = self->zPriority;
        prim->drawMode = DRAW_UNK02;
        self->step++;
        /* fall through */
    case 3:
        MoveEntity();
        self->rotate += ROT(56.25);
        prim = self->prim;
        SetGeomScreen(0x400);
        SetGeomOffset(self->posX.i.hi, self->posY.i.hi);
        RotMatrix(&rot, &m);
        RotMatrixZ(self->rotate, &m);
        RotMatrixX(ROT(61.875), &m);
        SetRotMatrix(&m);
        trans.vx = 0;
        trans.vy = 0;
        trans.vz = 0x400;
        TransMatrix(&m, &trans);
        SetTransMatrix(&m);
        RotAverage4(
            (SVECTOR*)D_us_80180FA0, (SVECTOR*)D_us_80180FA8,
            (SVECTOR*)D_us_80180FB0, (SVECTOR*)D_us_80180FB8, (long*)&prim->x0,
            (long*)&prim->x1, (long*)&prim->x2, (long*)&prim->x3, &p, &flag);
        if (!((g_Timer + 2) & 7)) {
            PlaySfxPositional(SFX_WHIP_TWIRL_SWISH);
        }
        if (self->velocityX > 0) {
            if (self->posX.i.hi > 0x100) {
                DestroyEntity((Entity*)self);
            }
        } else if (self->posX.i.hi < 0) {
            DestroyEntity((Entity*)self);
        }
        break;
    }
}

extern EInit g_EInitInteractable;
void EntityScyllaWaterOrbBeam(struct EntityScylla* self) {
    Primitive* prim;
    s32 dy;
    s32 isDone;
    s32 primIndex;
    s32 dx;

    if (g_BossMgrState & BOSS_MGR_DEFEAT) {
        DestroyEntity((Entity*)self);
        return;
    }

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitInteractable);
        primIndex = g_api.func_800EDB58(PRIM_LINE_G2_ALT, 0x12);
        if (primIndex == -1) {
            DestroyEntity((Entity*)self);
            return;
        }
        self->flags |= FLAG_HAS_PRIMS;
        self->primIndex = primIndex;
        prim = &g_PrimBuf[primIndex];
        self->prim = prim;
        while (prim != NULL) {
            prim->r0 = 0x20;
            prim->g0 = 0x28;
            prim->b0 = 0xC0;
            prim->r1 = 0x10;
            prim->g1 = 0x10;
            prim->b1 = 0x60;
            prim->priority = 0x98;
            prim->drawMode = DRAW_HIDE;
            prim = prim->next;
        }
        self->timer = (Random() & 7) * self->params;
        /* fall through */
    case 1:
        if (self->timer) {
            self->timer--;
            break;
        }
        dx = 0x5C - g_Tilemap.scrollX.i.hi;
        dy = 0x54 - g_Tilemap.scrollY.i.hi;
        dx = (dx - self->posX.i.hi) << 16;
        dy = (dy - self->posY.i.hi) << 16;
        dx /= 32;
        self->velocityX = dx;
        self->velocityY = FIX(-8.25);
        prim = self->prim;
        self->curPrim = prim;
        prim->x0 = prim->x1 = self->posX.i.hi;
        prim->y0 = prim->y1 = self->posY.i.hi;
        prim->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_UNK02 | DRAW_TRANSP;
        self->timer = 0x20;
        self->step++;
        /* fall through */
    case 2:
        switch (self->step_s) {
        case 0:
            MoveEntity();
            self->velocityY += FIX(0.25);
            if (self->velocityY > 0) {
                self->step_s++;
            }
            break;

        case 1:
            dy = 0x54 - g_Tilemap.scrollY.i.hi;
            dy = (dy - self->posY.i.hi) << 16;
            self->velocityY = dy / self->timer;
            self->step_s++;
            /* fall through */
        case 2:
            MoveEntity();
            break;
        }
        prim = self->curPrim;
        prim->x0 = self->posX.i.hi;
        prim->y0 = self->posY.i.hi;
        prim->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_UNK02 | DRAW_TRANSP;
        self->timer--;
        if (!self->timer) {
            self->step++;
        } else if (!(self->timer & 3)) {
            prim = prim->next;
            self->curPrim = prim;
            prim->x0 = prim->x1 = self->posX.i.hi;
            prim->y0 = prim->y1 = self->posY.i.hi;
            prim->drawMode =
                DRAW_TPAGE2 | DRAW_TPAGE | DRAW_UNK02 | DRAW_TRANSP;
        }
        /* fall through */
    case 3:
        isDone = true;
        prim = self->prim;
        while (prim->next != NULL) {
            if (prim->drawMode != DRAW_HIDE) {
                if (!func_us_801A2A90(prim, 1)) {
                    prim->drawMode = DRAW_HIDE;
                } else {
                    isDone = false;
                }
            }
            prim = prim->next;
        }
        prim->x0 = prim->x1 = prim->y0 = prim->y1 = 0;
        prim->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_UNK02 | DRAW_TRANSP;
        if (isDone) {
            DestroyEntity((Entity*)self);
        }
        break;
    }
}

extern EInit D_us_801805D0;
void EntityScyllaBubbleSkull(struct EntityScylla* self) {
    Entity* entity;
    s16 angle;
    s32 i;
    s32 dx;
    s32 dy;

    if (g_BossMgrState & BOSS_MGR_DEFEAT) {
        self->flags |= FLAG_DEAD;
    }
    if (self->flags & FLAG_DEAD) {
        for (i = 0; i < 5; i++) {
            entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (entity != NULL) {
                CreateEntityFromEntity(
                    E_ID(SCYLLA_DROPLET), (Entity*)self, entity);
                entity->zPriority = self->zPriority;
                entity->params = 1;
            }
        }
        DestroyEntity((Entity*)self);
        return;
    }

    switch (self->step) {
    case 0:
        InitializeEntity(D_us_801805D0);
        self->zPriority = 0x8C;
        self->hitboxState = 0;
        /* fall through */
    case 1:
        if (!AnimateEntity(D_us_80180F0C, (Entity*)self)) {
            self->velocityY = FIX(-4);
            self->timer = 0x50;
            self->hitboxState = 2;
            SetStep(2);
        }
        if (!self->poseTimer && self->pose == 3) {
            PlaySfxPositional(SFX_BONE_SWORD_SWISH_C);
        }
        break;

    case 2:
        AnimateEntity(D_us_80180F18, (Entity*)self);
        MoveEntity();
        self->velocityY -= self->velocityY >> 4;
        if (!--self->timer) {
            self->timer = 0x80;
            self->rotate = Random() << 4;
            self->step++;
        }
        break;

    case 3:
        AnimateEntity(D_us_80180F18, (Entity*)self);
        MoveEntity();
        angle = self->rotate += ROT(2.8125);
        self->velocityY = rsin(angle) << 3;
        if (!--self->timer) {
            SetStep(4);
        }
        break;

    case 4:
        if (!AnimateEntity(D_us_80180F30, (Entity*)self)) {
            SetStep(5);
        }
        break;

    case 5:
        entity = &PLAYER;
        dx = entity->posX.i.hi - self->posX.i.hi;
        dy = entity->posY.i.hi - self->posY.i.hi;
        angle = ratan2(dy, dx);
        self->velocityX = rcos(angle) * 7 << 4;
        self->velocityY = rsin(angle) * 7 << 4;
        if (self->velocityX > 0) {
            self->facingLeft = 0;
        } else {
            self->facingLeft = 1;
        }
        self->hitboxState = 3;
        PlaySfxPositional(SFX_ARROW_SHOT_A);
        self->step++;
        /* fall through */
    case 6:
        AnimateEntity(D_us_80180F40, (Entity*)self);
        MoveEntity();
        break;
    }
}

extern EInit D_us_801805DC;
void EntityScyllaWaterOrb(struct EntityScylla* self) {
    Entity* entity;
    s16 angle;
    s32 i;
    s32 dx;
    s32 dy;

    if (g_BossMgrState & BOSS_MGR_DEFEAT) {
        self->flags |= FLAG_DEAD;
    }
    if (self->flags & FLAG_DEAD) {
        for (i = 0; i < 0x10; i++) {
            entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (entity != NULL) {
                CreateEntityFromEntity(
                    E_ID(SCYLLA_DROPLET), (Entity*)self, entity);
                entity->zPriority = self->zPriority;
            }
        }
        PlaySfxPositional(SFX_SCYLLA_BUBBLE_BURST);
        DestroyEntity((Entity*)self);
        return;
    }

    switch (self->step) {
    case 0:
        InitializeEntity(D_us_801805DC);
        self->blendMode = BLEND_TRANSP | BLEND_ADD;
        self->hitPoints = 0;
        /* fall through */
    case 1:
        if (!AnimateEntity(D_us_80180EF4, (Entity*)self)) {
            SetStep(2);
        }
        break;

    case 2:
        entity = &PLAYER;
        dx = entity->posX.i.hi - self->posX.i.hi;
        dy = entity->posY.i.hi - self->posY.i.hi;
        angle = ratan2(dy, dx);
        if (angle > 0x200) {
            angle = 0x200;
        }
        if (angle < -0x180) {
            angle = -0x180;
        }
        self->velocityX = rcos(angle) * 5 << 4;
        self->velocityY = rsin(angle) * 5 << 4;
        self->orbAngle = angle;
        PlaySfxPositional(SFX_EXPLODE_B);
        self->step++;
        /* fall through */
    case 3:
        AnimateEntity(D_us_80180EE4, (Entity*)self);
        MoveEntity();
        entity = &PLAYER;
        angle = GetAngleBetweenEntities((Entity*)self, entity);
        angle = LimitAngleChange(8, self->orbAngle, angle);
        self->velocityX = rcos(angle) * 5 << 4;
        self->velocityY = rsin(angle) * 5 << 4;
        self->orbAngle = angle;
        break;
    }
}

extern EInit D_us_801805E8;
void EntityScyllaFallingRock(struct EntityScylla* self) {
    Entity* newEntity;
    s32 posY;
    s16 posX;
    u32 pad[10];

    if (g_BossMgrState & BOSS_MGR_DEFEAT) {
        self->flags |= FLAG_DEAD;
    }
    if (self->flags & FLAG_DEAD) {
        newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
        if (newEntity != NULL) {
            CreateEntityFromEntity(E_EXPLOSION, (Entity*)self, newEntity);
            newEntity->params = 0x11;
        }
        DestroyEntity((Entity*)self);
        return;
    }

    switch (self->step) {
    case 0:
        InitializeEntity(D_us_801805E8);
        self->drawFlags = ENTITY_ROTATE;
        self->params = Random() & 3;
        self->animCurFrame = self->params + 0x6F;
        self->rotate = rand() & 0xFFF;
        PlaySfxPositional(SFX_WALL_DEBRIS_B);
        /* fall through */
    case 1:
        self->rotate += ROT(11.25);
        if (self->posY.i.hi < 0x80) {
            MoveEntity();
            self->velocityY += FIX(0.125);
            break;
        }
        posX = self->posX.i.hi;
        posY = self->posY.i.hi + D_us_80180F88[self->params];
        posY += g_Tilemap.scrollY.i.hi;
        if (posY > 0xD8 && !self->splashed) {
            self->splashed = true;
            newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (newEntity != NULL) {
                CreateEntityFromEntity(
                    E_ID(SPLASH_WATER), (Entity*)self, newEntity);
                newEntity->params = 0;
                newEntity->posY.i.hi = 0xD8 - g_Tilemap.scrollY.i.hi;
            }
        }
        if (UnkCollisionFunc3(D_us_80180F90) & 1) {
            newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (newEntity != NULL) {
                CreateEntityFromEntity(E_EXPLOSION, (Entity*)self, newEntity);
                newEntity->params = 0x11;
            } else {
                FntPrint("no WORK !!\n");
            }
            DestroyEntity((Entity*)self);
            break;
        }
        self->velocityY -= FIX(0.125);
        break;
    }
}

extern EInit D_us_801805F4;
void EntityScyllaDroplet(struct EntityScylla* self) {
    s32 speed;
    s16 angle;

    switch (self->step) {
    case 0:
        InitializeEntity(D_us_801805F4);
        self->drawFlags = ENTITY_SCALEX | ENTITY_SCALEY;
        if (!self->params) {
            self->scaleX = self->scaleY = (Random() & 0x7F) + 0x40;
        } else {
            self->scaleX = self->scaleY = (Random() & 0x3F) + 0x20;
        }
        self->blendMode = BLEND_TRANSP;
        self->facingLeft = Random() & 1;
        speed = (Random() & 0x1F) + 0x10;
        angle = Random() * 6 + 0x900;
        self->velocityX = (speed * rcos(angle)) >> 1;
        self->velocityY = speed * rsin(angle);
        if (self->params) {
            self->velocityX >>= 1;
            self->velocityY >>= 1;
        }
        self->posX.val += self->velocityX << 2;
        self->posY.val += self->velocityY << 2;
        self->timer = (Random() & 0x1F) + 0x10;
        /* fall through */
    case 1:
        AnimateEntity(D_us_80180F24, (Entity*)self);
        MoveEntity();
        if (self->velocityY < FIX(3)) {
            self->velocityY += FIX(5.0 / 64);
        }
        break;
    }
}
