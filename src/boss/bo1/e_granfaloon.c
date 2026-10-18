// SPDX-License-Identifier: AGPL-3.0-or-later
#include "bo1.h"

struct EntityGranfaloon {
    ENTITY_SHARED;
    /* 0x7C */ struct Primitive* prim;
    /* 0x80 */ s16 timer;
    /* 0x82 */ s16 angle;
    /* 0x84 */ u8 activeParts;
    /* 0x85 */ u8 partIndex;
    /* 0x86 */ u8 hitTimer;
    /* 0x87 */ u8 unk87;
    /* 0x88 */ s16 hitX;
    /* 0x8A */ s16 hitY;
    /* 0x8C */ u32 : 32;
    /* 0x90 */ u32 : 32;
    /* 0x94 */ u32 : 32;
    /* 0x98 */ u8 palIndex;
    /* 0x99 */ u8 palMask;
    /* 0x9A */ u16 : 16;
    /* 0x9C */ struct Entity* owner;
    /* 0xA0 */ u8 hasHit;
    /* 0xA1 */ u8 : 8;
    /* 0xA2 */ u16 : 16;
    /* 0xA4 */ s32 length;
};
SYNC_STRUCT(EntityGranfaloon);

struct EntityHomingLaser {
    ENTITY_SHARED;
    /* 0x7C */ Primitive* prim;
    /* 0x80 */ s16 timer;
    /* 0x82 */ s16 angle;
    /* 0x84 */ Point16 trail[13];
};
SYNC_STRUCT(EntityHomingLaser);

enum {
    BOSS_STATUS_DEFEATED = 0x01,
    BOSS_UNK_2 = 0x02,
    BOSS_STATUS_DEAD = 0x04,
    BOSS_STATUS_DECAYING = 0x08,
    BOSS_STATUS_SPAWNED = 0x10,
};

static s32 D_us_80180CD8 = 0;
static s32 D_us_80180CDC = 0;
static s32 D_us_80180CE0 = 0;
static s32 boss_status = 0;
static s16 D_us_80180CE8[] = {0, 18, 8, 0};
static s16 sensors_unused_1[] = {0, 18, 0, 4};
static s16 sensors_unused_2[] = {8, -4, -16, 0};
static s16 D_us_80180D00[] = {
    -1024, 1024, 2048, 0, -1536, -512, 512, 1536, 0, 0};
static s32 D_us_80180D14[] = {3, 6, 1, 7, 2, 4, 0, 5};
static s16 D_us_80180D34[9][5] = {
    {65, 69, 67, 68, 66}, {79, 69, 81, 82, 80}, {72, 69, 74, 75, 73},
    {86, 69, 88, 89, 87}, {69, 68, 70, 71, 0},  {90, 68, 91, 92, 0},
    {83, 68, 84, 85, 0},  {76, 68, 77, 78, 0},  {61, 70, 63, 64, 62}};
static s16 pad_D34 = 0;
static s16 D_us_80180D90[][2] = {{0, -26},   {0, 26},   {-24, 0}, {24, 0},
                                 {-16, -18}, {16, -18}, {16, 18}, {-16, 16}};
static s16 D_us_80180DA0[] = {
    0, -40, 0, 40, -40, 0, 40, 0, -30, -30, 30, -30, 30, 30, -30, 30};
static s16 D_us_80180DD0[] = {112, 96, 96, 96, 136, 136, 112, 112};
static AnimateEntityFrame D_us_80180DE0[] = {
    POSE(25, 0x69, 0), POSE(12, 0x6A, 0), POSE(13, 0x6B, 0),
    POSE(8, 0x6C, 0),  POSE(25, 0x6D, 0), POSE(12, 0x6E, 0),
    POSE(13, 0x6F, 0), POSE(8, 0x70, 0),  POSE_LOOP(0)};
static AnimateEntityFrame D_us_80180DF4[] = {
    POSE(6, 0x05, 0), POSE(6, 0x04, 0), POSE(6, 0x03, 0), POSE(6, 0x02, 0),
    POSE(6, 0x03, 0), POSE(6, 0x04, 0), POSE(6, 0x05, 0), POSE(6, 0x06, 0),
    POSE(6, 0x07, 0), POSE(6, 0x08, 0), POSE(6, 0x07, 0), POSE(6, 0x06, 0),
    POSE_LOOP(0)};
static AnimateEntityFrame D_us_80180E10[] = {
    POSE(4, 0x3A, 0), POSE(8, 0x3B, 0), POSE(64, 0x3C, 0), POSE_END};
static AnimateEntityFrame D_us_80180E18[] = {
    POSE(8, 0x3C, 0), POSE(8, 0x3B, 0), POSE(4, 0x3A, 0), POSE_END};
static AnimateEntityFrame D_us_80180E20[] = {
    POSE(4, 0x5D, 0), POSE(4, 0x5E, 0), POSE(4, 0x5F, 0), POSE(4, 0x60, 0),
    POSE_END};
static AnimateEntityFrame D_us_80180E2C[] = {
    POSE(4, 0x61, 0), POSE(4, 0x62, 0), POSE(4, 0x63, 0), POSE_END};

static s8 D_us_80180E34[41][4];
static u8 hitbox_lookup[128];

extern EInit g_EInitTentacle;
extern EInit g_EInitHomingLaser;
extern EInit D_us_80180B34;
extern EInit g_EInitGrafaloonZombie;
extern EInit g_EInitShellDeadPiece;
extern s32 g_BossMgrState;
extern EInit g_EInitGranfaloonCore;
extern EInit g_EInitGranfaloonShell;

#ifdef VERSION_PSP
extern s32 E_ID(GRANFALOON_TENTACLE);
extern s32 E_ID(TENTACLE_HEAD);
extern s32 E_ID(TENTACLE_LASER);
extern s32 E_ID(BODY_PART_DEAD_PIECE);
extern s32 E_ID(UNK_1E);
extern s32 E_ID(UNK_1F);
extern s32 E_ID(ZOMBIE_FALLING);
extern s32 E_ID(ZOMBIE_ENEMY);
extern s32 E_ID(EXPLOSION_FLAME);
extern s32 E_ID(BODY_PART_SHELL);
extern s32 E_ID(HOMING_LASER);
extern s32 E_ID(LIFE_UP_SPAWN);
extern s32 E_ID(UNK_23);
#endif

#include "../../st/approach_s16.h"

void EntityGranfaloon(struct EntityGranfaloon* self) {
    // the actual entity is the core of Granfaloon, which internally spawns 9
    // entities that will act like an armor.
    enum Step {
        INIT,
        UNUSED_1,
        READY_TO_SPAWN,
        SPAWN,
        FLOAT_IDLE,
        SCREAMS_IDLE,
        UNK_6,
        SHOOT_LASERS,
        DEAD,
        DEBUG = 255,
    };
    Entity* ent;
    s32 i;
    s16 angle;
    s32 y;
    s32 x;
    s32 baseX;
    s32 offsetX;
    s8* hitbox;

    if (D_us_80180CD8 & 0x100) {
        self->hitboxState = 3;
    }
    if (self->flags & FLAG_DEAD) {
        if (self->step < 8) {
            SetStep(DEAD);
        }
    }

    switch (self->step) {
    case INIT:
        InitializeEntity(g_EInitGranfaloonCore);
        self->zPriority = 0x40;
        self->animCurFrame = 1;
        self->hitboxState = 0;
        boss_status = 0;
        D_us_80180CD8 = 0;
        D_us_80180CE0 = 0;
        self->posX.i.hi = 0x100 - g_Tilemap.scrollX.i.hi;
        self->posY.i.hi = 0x240 - g_Tilemap.scrollY.i.hi;
        ent = (Entity*)self + 10;
        for (i = 0; i < 8; i++, ent += 5) {
            CreateEntityFromEntity(
                E_ID(GRANFALOON_TENTACLE), (Entity*)self, ent);
            ent->zPriority = self->zPriority + 1;
            ent->params = i;
        }
        ent = (Entity*)self + 1;
        for (i = 0; i < 9; i++, ent++) {
            CreateEntityFromEntity(E_ID(BODY_PART_SHELL), (Entity*)self, ent);
            ((struct EntityGranfaloon*)ent)->owner = (Entity*)self;
            ent->params = i;
        }
        self->palMask = 7;
        self->hitTimer = 0;
        SetStep(READY_TO_SPAWN);
    case READY_TO_SPAWN:
        if (GetDistanceToPlayerX() < 0x80) {
            SetStep(SPAWN);
        }
        break;
    case SPAWN:
        switch (self->step_s) {
        case 0:
            g_api.TimeAttackController(
                TIMEATTACK_EVENT_GRANFALOON_DEFEAT, TIMEATTACK_SET_VISITED);
            g_BossMgrState = BOSS_MGR_FIGHT_ON;
            boss_status |= BOSS_STATUS_SPAWNED;
            stopMusicFlag = 0;
            currentMusicId = MU_DEATH_BALLAD;
            g_api.PlaySfx(currentMusicId);
            self->velocityY = FIX(-1.0);
            self->step_s++;
        case 1:
            // create particle effects when spawning
            MoveEntity();
            if (!(g_Timer & 0xF)) {
                PlaySfxPositional(SFX_GRANFALOON_APPEAR);
                g_api.ShakeCamera(SHAKE_Y_SMALL);
            }
            y = self->posY.i.hi + g_Tilemap.scrollY.i.hi;
            FntPrint("y %x\n", y);
            if (y < 0x100) {
                SetStep(FLOAT_IDLE);
            }
            if (y < 0x1C0) {
                self->hitTimer = 0x7F;
            }
            y += 0x70;
            y -= 0x1B0;
            angle = ratan2(y, 0x70);
            x = (rcos(angle) * 7) << 4 >> 12;
            baseX = self->posX.i.hi - x;
            x *= 2;
            offsetX = (x * Random()) >> 8;
            y = 0x1B0 - g_Tilemap.scrollY.i.hi;
            ent = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (ent != NULL) {
                CreateEntityFromEntity(E_EXPLOSION, (Entity*)self, ent);
                ent->zPriority = 0x70;
                ent->posX.i.hi = baseX + offsetX;
                ent->posY.i.hi = y;
                ent->params = 0x11;
            }
            break;
        }
        break;
    case FLOAT_IDLE:
        if (!self->step_s) {
            self->palMask = 0xF;
            self->hitTimer = 0xFF;
            self->timer = 0x180;
            self->activeParts = 0;
            self->step_s++;
        }
        MoveEntity();
        x = 0x100 - g_Tilemap.scrollX.i.hi;
        y = 0x120 - g_Tilemap.scrollY.i.hi;
        angle = self->angle += 0x10;
        angle &= 0xFFF;
        x += (rcos(angle) * 5) << 4 >> 12;
        y += (rsin(angle) * 5) << 4 >> 12;
        x -= self->posX.i.hi;
        y -= self->posY.i.hi;
        angle = ratan2(y, x);
        self->velocityX = (rcos(angle) * 3) << 13 >> 12;
        self->velocityY = (rsin(angle) * 3) << 13 >> 12;
        if (!--self->timer) {
            SetStep(SCREAMS_IDLE);
            if (D_us_80180CE0 > 2) {
                ent = g_Entities;
                x = ent->posX.i.hi - self->posX.i.hi;
                y = ent->posY.i.hi - self->posY.i.hi;
                angle = ratan2(y, x);
                angle += 0x100;
                angle &= 0xFFF;
                angle >>= 9;
                offsetX = D_us_80180D14[angle];
                if (D_us_80180CD8 & (1 << offsetX)) {
                    self->partIndex = offsetX;
                    SetStep(UNK_6);
                }
            }
        }
        if (D_us_80180CE0 > 8) {
            SetStep(SHOOT_LASERS);
        }
        break;
    case SCREAMS_IDLE:
        switch (self->step_s) {
        case 0:
            self->timer = 0x40;
            self->palMask = 3;
            self->hitTimer = 0;
            g_api.PlaySfx(SFX_GRANFALOON_BODIES_FALL);
            self->step_s++;
        case 1:
            if (!--self->timer) {
                self->timer = 0x100;
                self->palMask = 3;
                self->hitTimer = 0x1F;
                self->step_s++;
                if (Random() & 1) {
                    g_api.PlaySfx(SFX_GRANFALOON_SCREAMS_A);
                } else {
                    g_api.PlaySfx(SFX_GRANFALOON_SCREAMS_B);
                }
            }
            break;
        case 2:
            if (!--self->timer) {
                SetStep(FLOAT_IDLE);
            }
            break;
        }
        break;
    case UNK_6:
        switch (self->step_s) {
        case 0:
            self->palMask = 7;
            self->hitTimer = 0;
            self->velocityX = 0;
            self->velocityY = 0;
            D_us_80180CDC = 0;
            self->activeParts = 1 << self->partIndex;
            self->step_s++;
        case 1:
            if (D_us_80180CDC) {
                self->step_s++;
            }
            break;
        case 2:
            angle = D_us_80180D00[self->partIndex];
            angle += 0x800;
            self->velocityX = rcos(angle) << 17 >> 12;
            self->velocityY = rsin(angle) << 17 >> 12;
            self->palMask = 0xFF;
            self->hitTimer = 0;
            self->step_s++;
        case 3:
            MoveEntity();
            self->velocityX -= self->velocityX >> 4;
            self->velocityY -= self->velocityY >> 4;
            if (D_us_80180CDC == 0) {
                self->activeParts = 0;
                SetStep(FLOAT_IDLE);
                if (D_us_80180CE0 > 8) {
                    SetStep(SHOOT_LASERS);
                }
            }
            break;
        }
        break;
    case SHOOT_LASERS:
        if (!self->step_s) {
            self->timer = 0x80;
            self->activeParts = 0;
            self->angle = Random() << 4;
            self->step_s++;
        }
        if (!(self->timer & 0x1F)) {
            PlaySfxPositional(SFX_BAT_ECHO_A);
            ent = g_Entities;
            angle = GetAngleBetweenEntities((Entity*)self, ent);
            angle -= 0x800;
            angle -= 0x300;
            for (i = 0; i < 4; i++) {
                ent = AllocEntity(&g_Entities[144], &g_Entities[192]);
                if (ent != NULL) {
                    CreateEntityFromEntity(
                        E_ID(HOMING_LASER), (Entity*)self, ent);
                    ent->rotate = angle;
                }
                angle += 0x200;
            }
        }
        MoveEntity();
        x = 0x100 - g_Tilemap.scrollX.i.hi;
        y = 0x120 - g_Tilemap.scrollY.i.hi;
        angle = self->angle += 0x20;
        angle &= 0xFFF;
        x += rcos(angle) << 6 >> 12;
        y += rsin(angle) << 6 >> 12;
        x -= self->posX.i.hi;
        y -= self->posY.i.hi;
        angle = ratan2(y, x);
        self->velocityX = rcos(angle) << 16 >> 12;
        self->velocityY = rsin(angle) << 16 >> 12;
        if (!--self->timer) {
            ent = g_Entities;
            x = ent->posX.i.hi - self->posX.i.hi;
            y = ent->posY.i.hi - self->posY.i.hi;
            angle = ratan2(y, x);
            angle += 0x100;
            angle &= 0xFFF;
            angle >>= 9;
            offsetX = D_us_80180D14[angle];
            self->partIndex = offsetX;
            SetStep(UNK_6);
        }
        break;
    case DEAD:
        self->hitboxState = 0;
        switch (self->step_s) {
        case 0:
            g_api.TimeAttackController(
                TIMEATTACK_EVENT_GRANFALOON_DEFEAT, TIMEATTACK_SET_RECORD);
            boss_status |= BOSS_STATUS_DEFEATED;
            g_api.PlaySfx(SET_UNK_92);
            currentMusicId = MU_RAINBOW_CEMETERY;
            self->velocityY = FIX(-0.75);
            self->velocityX = 0;
            self->step_s++;
        case 1:
            MoveEntity();
            self->velocityY += 0x400;
            if (self->velocityY > 0) {
                boss_status |= BOSS_STATUS_DECAYING;
                self->drawFlags = ENTITY_ROTATE;
                self->timer = 0x80;
                self->drawFlags |= ENTITY_OPACITY;
                self->opacity = 0x80;
                self->step_s++;
            }
            break;
        case 2:
            MoveEntity();
            self->velocityY = FIX(0.5);
            self->rotate -= ROT(5.625);
            if (!(self->timer & 3)) {
                self->opacity -= 1;
            }
            if (!(self->timer & 7)) {
                PlaySfxPositional(SFX_FIREBALL_SHOT_B);
            }
            if (!--self->timer) {
                boss_status |= BOSS_STATUS_DEAD;
                self->step_s++;
            }
            break;
        case 3:
            MoveEntity();
            self->velocityY += FIX(0.125);
            y = self->posY.i.hi + g_Tilemap.scrollY.i.hi;
            if (y > 0x1B0) {
                self->step_s++;
                self->scaleX = 0x100;
                PlaySfxPositional(SFX_BOSS_LARGE_FLAMES);
            }
            break;
        case 4:
            self->animCurFrame = 0;
            for (i = 0; i < 2; i++) {
                ent = AllocEntity(&g_Entities[64], &g_Entities[256]);
                if (ent != NULL) {
                    CreateEntityFromEntity(
                        E_ID(EXPLOSION_FLAME), (Entity*)self, ent);
                    ent->params = 6;
                    ent->scaleX = self->scaleX;
                    ent->zPriority = self->zPriority;
                }
            }
            self->timer++;
            self->scaleX--;
            if (!(self->timer & 0x1F)) {
                PlaySfxPositional(SFX_BOSS_LARGE_FLAMES);
            }
            if (!self->scaleX) {
                self->step_s++;
            }
            break;
        case 5:
            ent = AllocEntity(&g_Entities[160], &g_Entities[192]);
            if (ent != NULL) {
                CreateEntityFromEntity(E_ID(LIFE_UP_SPAWN), (Entity*)self, ent);
                ent->posX.i.hi = 0x100 - g_Tilemap.scrollX.i.hi;
                ent->posY.i.hi = 0x150 - g_Tilemap.scrollY.i.hi;
                ent->params = 1;
                g_BossMgrState = BOSS_MGR_IDLE;
                stopMusicFlag = 1;
                currentMusicId = MU_RAINBOW_CEMETERY;
                self->step_s++;
            }
            break;
        case 6:
            if (!g_api.func_80131F68()) {
                stopMusicFlag = 0;
                g_api.PlaySfx(currentMusicId);
                self->step_s++;
            }
            break;
        case 7:
            break;
        }
        break;
    case DEBUG:
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
        hitbox = D_us_80180E34[0];
        offsetX = hitbox_lookup[self->animCurFrame];
        hitbox += offsetX * 4;
        self->hitboxOffX = *hitbox++;
        self->hitboxOffY = *hitbox++;
        self->hitboxWidth = *hitbox++;
        self->hitboxHeight = *hitbox++;
        break;
    }

    if (self->flags & FLAG_DEAD) {
        return;
    }
    g_ClutIds[0x201] = g_ClutIds[self->palIndex + 0x202];
    if (!(g_Timer & self->palMask)) {
        self->palIndex++;
        self->palIndex &= 3;
    }
    if (self->velocityX > 0) {
        x = 0x160 - g_Tilemap.scrollX.i.hi;
        if (x < self->posX.i.hi) {
            self->posX.i.hi = x;
        }
    } else {
        x = 0xA0 - g_Tilemap.scrollX.i.hi;
        if (self->posX.i.hi < x) {
            self->posX.i.hi = x;
        }
    }
    if (self->velocityY > 0) {
        y = 0x180 - g_Tilemap.scrollY.i.hi;
        if (y < self->posY.i.hi) {
            self->posY.i.hi = y;
        }
    } else {
        y = 0xC0 - g_Tilemap.scrollY.i.hi;
        if (self->posY.i.hi < y) {
            self->posX.i.hi = y;
        }
    }
}

static s8 D_us_80180E34[][4] = {
    {0, 0, 0, 0},       {0, 0, 24, 24},     {1, 29, 0, 0},
    {1, -29, 0, 0},     {24, 1, 0, 0},      {-24, 1, 0, 0},
    {20, 22, 0, 0},     {-20, 22, 0, 0},    {-20, -22, 0, 0},
    {20, -21, 0, 0},    {0, 12, 32, 44},    {12, 12, 28, 44},
    {-24, 8, 16, 40},   {1, -78, 31, 38},   {20, -80, 20, 32},
    {-16, -68, 24, 36}, {-53, -53, 30, 34}, {-56, -70, 28, 20},
    {-56, -44, 40, 20}, {-76, 0, 28, 32},   {-76, 16, 28, 24},
    {-76, -16, 28, 24}, {-51, 46, 25, 34},  {-48, 72, 24, 24},
    {-60, 40, 36, 24},  {0, 76, 40, 28},    {-16, 72, 32, 32},
    {24, 80, 24, 24},   {47, 48, 28, 36},   {80, 0, 24, 32},
    {51, -53, 24, 32},  {0, 2, 8, 16},      {0, 1, 5, 17},
    {1, 0, 7, 16},      {0, 2, 4, 16},      {-4, 1, 8, 16},
    {-3, 2, 6, 16},     {1, 0, 5, 18},      {-5, 2, 8, 16},
    {0, 4, 8, 12},      {-2, -2, 16, 8}};
static u8 hitbox_lookup[] = {
    0,  1,  2,  2,  2,  2,  2,  2,  2,  3, 3,  3,  3,  3,  3,  3,  4,  4,  4,
    4,  4,  4,  4,  5,  5,  5,  5,  5,  5, 5,  6,  6,  6,  6,  6,  6,  6,  7,
    7,  7,  7,  7,  7,  7,  8,  8,  8,  8, 8,  8,  8,  9,  9,  9,  9,  9,  9,
    9,  0,  0,  0,  10, 0,  11, 12, 13, 0, 14, 15, 16, 17, 18, 19, 0,  20, 21,
    22, 23, 24, 25, 0,  26, 27, 28, 0,  0, 29, 0,  0,  0,  30, 0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 31, 32, 33, 34, 35, 36, 37, 38, 0,
    0,  39, 0,  39, 0,  40, 0,  0,  0,  0, 0,  0,  0,  0,
};
void EntityBodyPartShell(struct EntityGranfaloon* self) {
    enum Step {
        INIT,
        WAIT_SPAWN,
        IDLE,
        DEAD,
    };
    Entity* newEntity;
    s32 i;
    s32 posX;
    s32 posY;
    s8* hitbox;
    s16* row;
    s16 angle;
    s32 hitboxIndex;

    if (boss_status & BOSS_STATUS_DEFEATED) {
        self->flags |= FLAG_DEAD;
    }
    if ((self->flags & FLAG_DEAD) && self->step < 3) {
        SetStep(DEAD);
    }
    switch (self->step) {
    case INIT:
        InitializeEntity(g_EInitGranfaloonShell);
        row = D_us_80180D34[self->params];
        self->animCurFrame = row[0];
        self->zPriority = row[1];
        hitbox = D_us_80180E34[0];
        hitboxIndex = hitbox_lookup[self->animCurFrame];
        hitbox += hitboxIndex * 4;
        self->hitboxOffX = *hitbox++;
        self->hitboxOffY = *hitbox++;
        self->hitboxWidth = *hitbox++;
        self->hitboxHeight = *hitbox++;
        if (row[4]) {
            newEntity = AllocEntity(&g_Entities[208], &g_Entities[256]);
            if (newEntity != NULL) {
                CreateEntityFromEntity(E_ID(UNK_1E), (Entity*)self, newEntity);
                newEntity->params = self->params;
                ((struct EntityGranfaloon*)newEntity)->owner = (Entity*)self;
            }
        }
    case WAIT_SPAWN:
        self->hitboxState = 0;
        if (g_BossMgrState) {
            self->hitboxState = 3;
            self->step++;
        }
        break;
    case IDLE:
        newEntity = self->owner;
        self->posX.i.hi = newEntity->posX.i.hi;
        self->posY.i.hi = newEntity->posY.i.hi;
        if (!((struct EntityGranfaloon*)newEntity)->hitTimer) {
            break;
        }
        if (Random() & ((struct EntityGranfaloon*)newEntity)->hitTimer) {
            break;
        }
        posX = self->posX.i.hi;
        posY = self->posY.i.hi;
        if (self->params != 8) {
            angle = D_us_80180D00[self->params];
            posX += ((rcos(angle) * 3) << 5) >> 12;
            posY += ((rsin(angle) * 3) << 5) >> 12;
        }
        newEntity = AllocEntity(&g_Entities[144], &g_Entities[192]);
        if (newEntity != NULL) {
            if (Random() & 1) {
                CreateEntityFromCurrentEntity(E_ID(ZOMBIE_FALLING), newEntity);
            } else {
                CreateEntityFromCurrentEntity(E_ID(ZOMBIE_ENEMY), newEntity);
            }
            newEntity->zPriority = 0x4A;
            newEntity->posX.i.hi = posX;
            newEntity->posY.i.hi = posY;
            newEntity->params = self->params;
        }
        break;
    case DEAD:
        switch (self->step_s) {
        case 0:
            self->hitboxState = 0;
            self->animCurFrame = 0;
            D_us_80180CD8 |= 1 << self->params;
            D_us_80180CE0++;
            row = D_us_80180D34[self->params];
            for (i = 0; i < 2; i++) {
                newEntity = AllocEntity(&g_Entities[192], &g_Entities[256]);
                if (newEntity != NULL) {
                    CreateEntityFromEntity(
                        E_ID(BODY_PART_DEAD_PIECE), (Entity*)self, newEntity);
                    newEntity->params = self->params + (i << 8);
                    newEntity->zPriority = 0x48;
                }
            }
            posX = self->posX.i.hi;
            posY = self->posY.i.hi;
            if (self->params != 8) {
                angle = D_us_80180D00[self->params];
                posX += ((rcos(angle) * 5) << 4) >> 12;
                posY += ((rsin(angle) * 5) << 4) >> 12;
            }
            for (i = 0; i < 0x18; i++) {
                newEntity = AllocEntity(&g_Entities[208], &g_Entities[240]);
                if (newEntity != NULL) {
                    CreateEntityFromCurrentEntity(E_ID(UNK_1F), newEntity);
                    newEntity->zPriority = 0x4A;
                    newEntity->posX.i.hi = posX;
                    newEntity->posY.i.hi = posY;
                }
            }
            PlaySfxPositional(SFX_BO1_UNK_7C7);
            self->step_s++;
            break;
        case 1:
            break;
        }
        break;
    }
}

void EntityBodyPartDeadPiece(Entity* self) {
    s16 angle;
    s16* row;
    s32 index;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitShellDeadPiece);
        self->flags |= FLAG_DESTROY_IF_OUT_OF_CAMERA;
        index = self->params & 0xF;
        row = D_us_80180D34[index];
        angle = D_us_80180D00[index];
        if (self->params & 0x100) {
            angle -= 0x80;
            self->animCurFrame = row[3];
        } else {
            angle += 0x80;
            self->animCurFrame = row[2];
        }
        self->velocityX = rsin(angle) << 4;
        self->velocityY = rcos(angle) << 4;
        break;
    case 1:
        MoveEntity();
        self->velocityY += FIX(0.0625);
        break;
    }
}

void func_us_801A2CC4(struct EntityGranfaloon* self) {
    s16* row;
    Entity* parent;

    if (boss_status & BOSS_STATUS_DEFEATED) {
        DestroyEntity((Entity*)self);
        return;
    }
    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitShellDeadPiece);
        self->zPriority = 0x3C;
        row = D_us_80180D34[self->params];
        self->animCurFrame = row[4];
    case 1:
        parent = self->owner;
        self->posX.i.hi = parent->posX.i.hi;
        self->posY.i.hi = parent->posY.i.hi;
        if (D_us_80180CD8 & (1 << self->params)) {
            DestroyEntity((Entity*)self);
        }
        break;
    }
}

void func_us_801A2D90(struct EntityGranfaloon* self) {
    s32 var_s0;
    s16 angle;
    s32 posY;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitShellDeadPiece);
        self->flags |= FLAG_DESTROY_IF_OUT_OF_CAMERA;
        var_s0 = Random() & 3;
        self->animCurFrame = var_s0 + 0x79;
        self->drawFlags = ENTITY_ROTATE;
        self->facingLeft = Random() & 1;
        var_s0 = (Random() & 0x1F) + 0x10;
        angle = (Random() * 6) + 0x900;
        self->velocityX = (var_s0 * rcos(angle)) >> 1;
        self->velocityY = var_s0 * rsin(angle);
        if (self->params) {
            self->velocityX >>= 1;
            self->velocityY >>= 1;
        }
        self->posX.val += self->velocityX << 4;
        self->posY.val += self->velocityY << 4;
        self->timer = (Random() & 0x1F) + 0x10;
    case 1:
        MoveEntity();
        self->rotate += ROT(5.625);
        if (self->velocityY < FIX(3.0)) {
            self->velocityY += 0x1400;
        }
        break;
    }
    posY = self->posY.i.hi + g_Tilemap.scrollY.i.hi;
    if (posY > 0x1C8) {
        DestroyEntity((Entity*)self);
    }
}

void EntityGranfaloonTentacle(struct EntityGranfaloon* self) {
    enum Step {
        INIT,
        UNK_1,
        DEAD,
    };
    Entity* parent;
    Entity* player;
    s16 angle;
    s32 index;

    if (boss_status & BOSS_STATUS_DEFEATED && self->step < DEAD) {
        SetStep(DEAD);
    }
    switch (self->step) {
    case INIT:
        InitializeEntity(g_EInitTentacle);
        self->drawFlags = ENTITY_OPACITY;
        self->opacity = D_us_80180DD0[self->params];
        self->rotate = 0;
        self->drawFlags |= ENTITY_ROTATE;
        parent = (Entity*)self + 1;
        CreateEntityFromEntity(E_ID(TENTACLE_HEAD), (Entity*)self, parent);
        parent->zPriority = self->zPriority + 1;
        parent->params = self->params;
    case UNK_1:
        index = self->params;
        parent = (Entity*)self - 10 - index * 5;
        self->posX.i.hi = parent->posX.i.hi + D_us_80180D90[index][0];
        self->posY.i.hi = parent->posY.i.hi + D_us_80180D90[index][1];
        self->activeParts =
            ((struct EntityGranfaloon*)parent)->activeParts & (1 << index);
        AnimateEntity(D_us_80180DF4, (Entity*)self);
        self->animCurFrame += index * 7;
        if (D_us_80180CD8 & (1 << index)) {
            if (!self->activeParts) {
                self->drawFlags |= ENTITY_ROTATE;
                angle = (rcos(self->angle) * 128) >> 12;
                func_801CDC80(&self->rotate, angle, 0x10);
                self->angle += 0x30;
            } else {
                player = &PLAYER;
                angle = GetAngleBetweenEntities(parent, player);
                angle -= D_us_80180D00[index];
                if (angle > 0x80) {
                    angle = 0x80;
                }
                if (angle < -0x80) {
                    angle = -0x80;
                }
                func_801CDC80(&self->rotate, angle, 2);
            }
        }
        break;
    case DEAD:
        index = self->params;
        parent = (Entity*)self - 10 - index * 5;
        self->posX.i.hi = parent->posX.i.hi + D_us_80180D90[index][0];
        self->posY.i.hi = parent->posY.i.hi + D_us_80180D90[index][1];
        angle = (rcos(self->angle) * 160) >> 12;
        func_801CDC80(&self->rotate, angle, 0x40);
        self->angle += 0x70;
        switch (self->step_s) {
        case 0:
            self->hitboxState = 0;
            self->timer = self->params;
            self->step_s++;
            break;
        case 1:
            self->timer++;
            if (!(self->timer & 0xF)) {
                PlaySfxPositional(SFX_B07_STOMP);
                parent = AllocEntity(&g_Entities[64], &g_Entities[256]);
                if (parent != NULL) {
                    CreateEntityFromEntity(
                        E_ID(EXPLOSION_FLAME), (Entity*)self, parent);
                    parent->params = 4;
                    parent->rotate = D_us_80180D00[self->params];
                    parent->zPriority = 0x70;
                }
            }
            if (boss_status & BOSS_STATUS_DECAYING) {
                PlaySfxPositional(SFX_FIREBALL_SHOT_C);
                self->step_s++;
            }
            break;
        case 2:
            self->animCurFrame = 0;
            self->timer++;
            index = self->params;
            parent = (Entity*)self - 10 - index * 5;
            self->posX.i.hi = parent->posX.i.hi;
            self->posY.i.hi = parent->posY.i.hi;
            angle = D_us_80180D00[index] + parent->rotate;
            self->posX.i.hi += (rcos(angle) * 24) >> 12;
            self->posY.i.hi += (rsin(angle) * 24) >> 12;
            if (!(self->timer & 3)) {
                parent = AllocEntity(&g_Entities[64], &g_Entities[256]);
                if (parent != NULL) {
                    CreateEntityFromEntity(
                        E_ID(EXPLOSION_FLAME), (Entity*)self, parent);
                    parent->params = 5;
                    parent->rotate = angle + 0x200;
                    parent->zPriority = 0x70;
                }
            }
            if (boss_status & BOSS_STATUS_DEAD) {
                self->step_s++;
            }
            break;
        case 3:
            DestroyEntity((Entity*)self);
            break;
        }
        break;
    }
}

void EntityTentacleHead(struct EntityGranfaloon* self) {
    enum Step {
        INIT,
        IDLE,
        ATTACK,
        DEAD,
    };
    Entity* parent;
    s16 angle;
    s32 index;

    if (boss_status & BOSS_STATUS_DEFEATED && self->step < DEAD) {
        SetStep(DEAD);
    }
    switch (self->step) {
    case INIT:
        InitializeEntity(g_EInitTentacle);
        self->animCurFrame = 0x3A;
        self->drawFlags = ENTITY_OPACITY;
        self->drawFlags |= ENTITY_ROTATE;
        self->opacity = D_us_80180DD0[self->params];
        self->rotate = D_us_80180D00[self->params] - 0x400;
    case IDLE:
        index = self->params;
        parent = (Entity*)self - 1;
        angle = D_us_80180D00[index] + parent->rotate;
        self->rotate = angle - 0x400;
        self->posX.i.hi = parent->posX.i.hi;
        self->posY.i.hi = parent->posY.i.hi;
        self->posX.i.hi += ((rcos(angle) * 40) >> 12);
        self->posY.i.hi += ((rsin(angle) * 40) >> 12);
        if (((struct EntityGranfaloon*)parent)->activeParts) {
            SetStep(ATTACK);
        }
        break;
    case ATTACK:
        index = self->params;
        parent = (Entity*)self - 1;
        angle = D_us_80180D00[index] + parent->rotate;
        self->rotate = angle - 0x400;
        self->posX.i.hi = parent->posX.i.hi;
        self->posY.i.hi = parent->posY.i.hi;
        self->posX.i.hi += ((rcos(angle) * 40) >> 12);
        self->posY.i.hi += ((rsin(angle) * 40) >> 12);
        switch (self->step_s) {
        case 0:
            if (!AnimateEntity(D_us_80180E10, (Entity*)self)) {
                SetSubStep(1);
            }
            break;
        case 1:
            parent = (Entity*)self + 1;
            CreateEntityFromEntity(E_ID(TENTACLE_LASER), (Entity*)self, parent);
            parent->rotate = self->rotate;
            parent->zPriority = self->zPriority + 1;
            ((struct EntityGranfaloon*)parent)->owner = (Entity*)self;
            self->timer = 0x100;
            self->step_s++;

        case 2:
            parent = (Entity*)self + 1;
            if (parent->entityId != E_ID(TENTACLE_LASER)) {
                self->step_s++;
            }
            break;
        case 3:
            if (!AnimateEntity(D_us_80180E18, (Entity*)self)) {
                SetStep(IDLE);
            }
            break;
        }
        break;
    case DEAD:
        index = self->params;
        parent = (Entity*)self - 1;
        angle = D_us_80180D00[index] + parent->rotate;
        self->rotate = angle - 0x400;
        self->posX.i.hi = parent->posX.i.hi;
        self->posY.i.hi = parent->posY.i.hi;
        self->posX.i.hi += ((rcos(angle) * 40) >> 12);
        self->posY.i.hi += ((rsin(angle) * 40) >> 12);
        switch (self->step_s) {
        case 0:
            self->hitboxState = 0;
            self->timer = self->params;
            self->step_s++;
            break;
        case 1:
            self->timer++;
            if (!(self->timer & 7)) {
                parent = AllocEntity(&g_Entities[64], &g_Entities[256]);
                if (parent != NULL) {
                    CreateEntityFromEntity(
                        E_ID(EXPLOSION_FLAME), (Entity*)self, parent);
                    parent->params = 3;
                    parent->zPriority = 0x70;
                }
            }
            if (boss_status & BOSS_STATUS_DECAYING) {
                self->step_s++;
            }
            break;
        case 2:
            self->animCurFrame = 0;
            DestroyEntity((Entity*)self);
            break;
        }
        break;
    }
}

void EntityTentacleLaser(struct EntityGranfaloon* self) {
    Entity* ent;
    Primitive* prim;
    s16 angle;
    s32 offX;
    s32 offY;
    s32 primIndex;
    Collider collider;

    if (boss_status & BOSS_STATUS_DEFEATED) {
        DestroyEntity((Entity*)self);
        return;
    }
    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitHomingLaser);
        self->drawFlags = ENTITY_ROTATE;
        self->hitboxWidth = self->hitboxHeight = 8;
        if (self->params) {
            self->hitboxState = 0;
            if (self->params & 0x100) {
                self->step = 0x20;
                self->hitboxState = 0;
                return;
            }
            self->animCurFrame = 0x64;
            self->step = 0x10;
            return;
        }
        ent = AllocEntity(&g_Entities[208], &g_Entities[256]);
        angle = self->rotate + 0x400;
        if (ent != NULL) {
            CreateEntityFromEntity(E_ID(TENTACLE_LASER), (Entity*)self, ent);
            ent->params = 0x100;
            ent->rotate = self->rotate;
            ent->posX.i.hi += (rcos(angle) * 24) >> 12;
            ent->posY.i.hi += (rsin(angle) * 24) >> 12;
            ent->zPriority = self->zPriority;
            ((struct EntityGranfaloon*)ent)->owner = self->owner;
        }
        self->posX.i.hi += (rcos(angle) * 36) >> 12;
        self->posY.i.hi += (rsin(angle) * 36) >> 12;
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 1);
        if (primIndex == -1) {
            DestroyEntity((Entity*)self);
            return;
        }
        self->flags |= FLAG_HAS_PRIMS;
        self->primIndex = primIndex;
        prim = &g_PrimBuf[primIndex];
        self->prim = prim;
        prim->tpage = 0x12;
        prim->clut = PAL_BASE;
        prim->u0 = prim->u2 = 0xB8;
        prim->u1 = prim->u3 = 0xD0;
        prim->v0 = prim->v1 = 0x42;
        prim->v2 = prim->v3 = 0x46;
        prim->priority = self->zPriority - 1;
        prim->drawMode = DRAW_HIDE;
    case 1:
        ent = self->owner;
        self->rotate = ent->rotate;
        angle = self->rotate + 0x400;
        self->posX.i.hi = ent->posX.i.hi;
        self->posY.i.hi = ent->posY.i.hi;
        self->posX.i.hi += (rcos(angle) * 36) >> 12;
        self->posY.i.hi += (rsin(angle) * 36) >> 12;
        if (!AnimateEntity(D_us_80180E2C, (Entity*)self)) {
            SetStep(2);
        }
        break;
    case 2:
        ent = self->owner;
        self->rotate = ent->rotate;
        angle = self->rotate + 0x400;
        self->posX.i.hi = ent->posX.i.hi;
        self->posY.i.hi = ent->posY.i.hi;
        self->posX.i.hi += (rcos(angle) * 36) >> 12;
        self->posY.i.hi += (rsin(angle) * 36) >> 12;
        ent = (Entity*)self + 1;
        CreateEntityFromEntity(E_ID(TENTACLE_LASER), (Entity*)self, ent);
        ent->params = 1;
        ent->rotate = self->rotate;
        ((struct EntityGranfaloon*)ent)->owner = (Entity*)self;
        angle = self->rotate + 0x400;
        self->posX.i.hi += (rcos(angle) * 40) >> 12;
        self->posY.i.hi += (rsin(angle) * 40) >> 12;
        self->length = FIX(0x4C);
        self->animCurFrame = 0x66;
        prim = self->prim;
        prim->drawMode = DRAW_UNK02;
        D_us_80180CDC = 1;
        PlaySfxPositional(SFX_GRANFALOON_LASER_ATTACK);
        self->step++;
    case 3:
        ent = self->owner;
        self->length += FIX(8);
        self->rotate = ent->rotate;
        angle = self->rotate + 0x400;
        self->posX.i.hi = ent->posX.i.hi;
        self->posY.i.hi = ent->posY.i.hi;
        self->posX.val += (self->length >> 12) * rcos(angle);
        self->posY.val += (self->length >> 12) * rsin(angle);
        if (!self->hasHit) {
            offX = self->posX.i.hi;
            offY = self->posY.i.hi;
            g_api.CheckCollision(offX, offY, &collider, 0);
            if (collider.effects & EFFECT_SOLID) {
                self->hasHit = 1;
                self->hitX = offX + g_Tilemap.scrollX.i.hi;
                self->hitY = offY + g_Tilemap.scrollY.i.hi;
                if (self->hitY > 0x1B0) {
                    self->hitY = 0x1B0;
                }
            }
        } else {
            ent = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (ent != NULL) {
                CreateEntityFromCurrentEntity(E_ID(EXPLOSION_FLAME), ent);
                ent->posX.i.hi = self->hitX - g_Tilemap.scrollX.i.hi;
                ent->posY.i.hi = self->hitY - g_Tilemap.scrollY.i.hi;
                ent->posX.i.hi += Random() & 0xF;
                ent->posY.i.hi += Random() & 0xF;
                ent->zPriority = 0x70;
                ent->params = 2;
            }
        }
        offX = self->posX.i.hi + g_Tilemap.scrollX.i.hi;
        offY = self->posY.i.hi + g_Tilemap.scrollY.i.hi;
        if (offX < -0x20 || offY < -0x20 || offX > 0x220 || offY > 0x220) {
            self->step++;
        }
        angle = self->rotate + 0x400;
        offX = -((rsin(angle) * 12) >> 12);
        offY = (rcos(angle) * 12) >> 12;
        prim = self->prim;
        prim->x0 = self->posX.i.hi + offX;
        prim->x1 = self->posX.i.hi - offX;
        prim->y0 = self->posY.i.hi + offY;
        prim->y1 = self->posY.i.hi - offY;
        ent = (Entity*)self + 1;
        prim->x2 = ent->posX.i.hi + offX;
        prim->x3 = ent->posX.i.hi - offX;
        prim->y2 = ent->posY.i.hi + offY;
        prim->y3 = ent->posY.i.hi - offY;
        break;
    case 4:
        self->drawFlags |= ENTITY_SCALEX;
        self->scaleX = 0x100;
        self->step++;
    case 5:
        ent = self->owner;
        self->rotate = ent->rotate;
        angle = self->rotate + 0x400;
        self->posX.i.hi = ent->posX.i.hi;
        self->posY.i.hi = ent->posY.i.hi;
        self->posX.val += (self->length >> 12) * rcos(angle);
        self->posY.val += (self->length >> 12) * rsin(angle);
        self->scaleX -= 4;
        if (!self->scaleX) {
            D_us_80180CDC = 0;
            DestroyEntity((Entity*)self);
            return;
        }
        angle = self->rotate + 0x400;
        offX = -((rsin(angle) * 12) >> 12);
        offY = (rcos(angle) * 12) >> 12;
        offX = (offX * self->scaleX) >> 8;
        offY = (offY * self->scaleX) >> 8;
        prim = self->prim;
        prim->x0 = self->posX.i.hi + offX;
        prim->x1 = self->posX.i.hi - offX;
        prim->y0 = self->posY.i.hi + offY;
        prim->y1 = self->posY.i.hi - offY;
        ent = (Entity*)self + 1;
        prim->x2 = ent->posX.i.hi + offX;
        prim->x3 = ent->posX.i.hi - offX;
        prim->y2 = ent->posY.i.hi + offY;
        prim->y3 = ent->posY.i.hi - offY;
        break;
    case 0x10:
        ent = self->owner;
        ent--;
        self->rotate = ent->rotate;
        angle = self->rotate + 0x400;
        self->posX.i.hi = ent->posX.i.hi;
        self->posY.i.hi = ent->posY.i.hi;
        self->posX.i.hi += (rcos(angle) * 36) >> 12;
        self->posY.i.hi += (rsin(angle) * 36) >> 12;
        ent = self->owner;
        self->drawFlags = ent->drawFlags;
        self->scaleX = ent->scaleX;
        if (ent->entityId != E_ID(TENTACLE_LASER)) {
            DestroyEntity((Entity*)self);
            return;
        }
        self->timer++;
        if (self->scaleX) {
            break;
        }
        if (self->timer & 3) {
            break;
        }
        ent = AllocEntity(&g_Entities[128], &g_Entities[192]);
        if (ent != NULL) {
            CreateEntityFromEntity(E_ID(UNK_23), (Entity*)self, ent);
            ent->rotate = self->rotate + 0x400;
        }
        break;
    case 0x20:
        ent = self->owner;
        self->rotate = ent->rotate;
        angle = self->rotate + 0x400;
        self->posX.i.hi = ent->posX.i.hi;
        self->posY.i.hi = ent->posY.i.hi;
        self->posX.i.hi += (rcos(angle) * 24) >> 12;
        self->posY.i.hi += (rsin(angle) * 24) >> 12;
        switch (self->step_s) {
        case 0:
            if (!AnimateEntity(D_us_80180E20, (Entity*)self)) {
                self->timer = 0x40;
                self->drawFlags |= ENTITY_SCALEX;
                self->scaleX = 0x100;
                self->step_s++;
            }
            break;
        case 1:
            if (g_Timer & 1) {
                self->animCurFrame = 0;
            } else {
                self->animCurFrame = 0x60;
            }
            self->scaleX = (self->timer & 7) * 3 + 0x100;
            if (!--self->timer) {
                DestroyEntity((Entity*)self);
            }
            break;
        }
        break;
    }
}

void EntityZombieFalling(struct EntityGranfaloon* self) {
    Entity* newEntity;
    s16 angle;
    s32 frame;
    s32 posY;

    if (boss_status & BOSS_STATUS_DEFEATED) {
        self->flags |= FLAG_DEAD;
    }
    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitGrafaloonZombie);
        if (self->params != 8) {
            angle = D_us_80180D00[self->params];
            angle += Random() - 0x80;
            self->velocityX = (rcos(angle) << 15) >> 12;
            self->velocityY = (rsin(angle) << 15) >> 12;
        }
        frame = Random() & 3;
        if (frame == 3) {
            frame = 0;
        }
        self->facingLeft = Random() & 1;
        self->drawFlags = ENTITY_ROTATE;
        self->animCurFrame = (frame << 1) + 0x73;
    case 1:
        MoveEntity();
        self->velocityY += FIX(0.0625);
        self->rotate += ROT(2.109375);
        if (self->flags & FLAG_DEAD) {
            self->velocityY = 0;
            self->hitboxState = 0;
            self->animCurFrame++;
            self->timer = 0x40;
            PlaySfxPositional(SFX_SMALL_FLAME_IGNITE);
            self->step++;
        }
        break;
    case 2:
        MoveEntity();
        self->velocityY += FIX(0.03125);
        if (!(self->timer & 7)) {
            newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (newEntity != NULL) {
                CreateEntityFromEntity(
                    E_ID(EXPLOSION_FLAME), (Entity*)self, newEntity);
                newEntity->params = 0;
                newEntity->zPriority = self->zPriority - 1;
                newEntity->posY.i.hi += 0x14;
            }
        }
        if (!--self->timer) {
            DestroyEntity((Entity*)self);
            return;
        }
        break;
    }
    posY = self->posY.i.hi + g_Tilemap.scrollY.i.hi;
    if (posY > 0x1C8) {
        DestroyEntity((Entity*)self);
    }
}

void EntityZombieEnemy(struct EntityGranfaloon* self) {
    Collider collider;
    Entity* newEntity;
    s32 res;
    s32 posX;
    s32 posY;

    if (boss_status & BOSS_STATUS_DEFEATED) {
        self->flags |= FLAG_DEAD;
    }
    if ((self->flags & FLAG_DEAD) && self->step < 4) {
        SetStep(4);
    }
    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitGrafaloonZombie);
        self->animCurFrame = 0x69;
        self->hitboxWidth = 8;
        self->hitboxHeight = 0x12;
        self->facingLeft = Random() & 1;
    case 1:
        MoveEntity();
        self->velocityY += FIX(0.09375);
        posX = self->posX.i.hi;
        posY = self->posY.i.hi + 0x12;
        g_api.CheckCollision(posX, posY, &collider, 0);
        if (collider.effects & EFFECT_SOLID) {
            self->posY.i.hi += collider.unk18;
            self->step++;
        }
        break;
    case 2:
        switch (self->step_s) {
        case 0:
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
            self->step_s++;

        case 1:
            if (self->facingLeft) {
                self->velocityX = FIX(0.375);
            } else {
                self->velocityX = FIX(-0.375);
            }
            AnimateEntity(D_us_80180DE0, (Entity*)self);
            res = UnkCollisionFunc2(D_us_80180CE8);
            if (res & 0x80) {
                DestroyEntity((Entity*)self);
            }
            break;
        }
        break;
    case 4:
        switch (self->step_s) {
        case 0:
            self->hitboxState = 0;
            self->timer = (Random() & 0xF) + 0x10;
            self->animCurFrame = 0x71;
            PlaySfxPositional(SFX_SMALL_FLAME_IGNITE);
            self->step_s++;
        case 1:
            if (!(self->timer & 0xF)) {
                newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
                if (newEntity != NULL) {
                    CreateEntityFromEntity(
                        E_ID(EXPLOSION_FLAME), (Entity*)self, newEntity);
                    newEntity->posY.i.hi += 0x18;
                    newEntity->zPriority = self->zPriority + 1;
                    newEntity->params = 1;
                }
            }
            if (!--self->timer) {
                self->timer = 0x10;
                self->animCurFrame = 0x72;
                self->step_s++;
            }
            break;
        case 2:
            if (!(self->timer & 7)) {
                newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
                if (newEntity != NULL) {
                    CreateEntityFromEntity(
                        E_ID(EXPLOSION_FLAME), (Entity*)self, newEntity);
                    newEntity->posY.i.hi += 0x18;
                    newEntity->zPriority = self->zPriority - 1;
                }
            }
            if (!--self->timer) {
                DestroyEntity((Entity*)self);
            }
            break;
        }
        break;
    }
}

void func_us_801A493C(struct EntityGranfaloon* self) {
    Collider collider;
    Entity* newEntity;
    s32 posX;
    s32 posY;
    s16 angle;

    if (boss_status & BOSS_STATUS_DEFEATED) {
        DestroyEntity((Entity*)self);
        return;
    }
    switch (self->step) {
    case 0:
        InitializeEntity(D_us_80180B34);
        self->hitboxWidth = 8;
        self->hitboxHeight = 8;
        angle = self->rotate;
        self->velocityX = (rcos(angle) * 3) << 5;
        self->velocityY = (rsin(angle) * 3) << 5;
    case 1:
        MoveEntity();
        posX = self->posX.i.hi + g_Tilemap.scrollX.i.hi;
        posY = self->posY.i.hi + g_Tilemap.scrollY.i.hi;
        if (!self->hasHit) {
            posX = self->posX.i.hi;
            posY = self->posY.i.hi;
            g_api.CheckCollision(posX, posY, &collider, 0);
            if (collider.effects & EFFECT_SOLID) {
                self->hasHit = 1;
                newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
                if (newEntity != NULL) {
                    CreateEntityFromCurrentEntity(
                        E_ID(EXPLOSION_FLAME), newEntity);
                    newEntity->posX.i.hi += Random() & 0xF;
                    newEntity->posY.i.hi += Random() & 0xF;
                    newEntity->zPriority = 0x70;
                    newEntity->params = 2;
                }
            }
        }
        if (posX < 0 || posY < 0 || posX > 0x200 || posY > 0x200) {
            DestroyEntity((Entity*)self);
        }
        break;
    }
}

void EntityHomingLaser(struct EntityHomingLaser* self) {
    Primitive* prim;
    Point16* pt;
    s16 angle;
    s32 i;
    s32 offX;
    s32 offY;
    s32 primIndex;
    Entity* player;
    s32 baseX;
    s32 baseY;

    if (boss_status & BOSS_STATUS_DEFEATED) {
        DestroyEntity((Entity*)self);
        return;
    }
    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitHomingLaser);
        self->hitboxWidth = self->hitboxHeight = 4;
        self->zPriority = 0x38;
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 13);
        if (primIndex == -1) {
            DestroyEntity((Entity*)self);
            return;
        }
        self->flags |= FLAG_HAS_PRIMS;
        self->primIndex = primIndex;
        prim = &g_PrimBuf[primIndex];
        self->prim = prim;
        prim->tpage = 0x14;
        prim->clut = PAL_BASE;
        prim->u0 = prim->u2 = 0x38;
        prim->u1 = prim->u3 = 0x40;
        prim->v0 = prim->v1 = 0x28;
        prim->v2 = prim->v3 = 0x40;
        prim->r0 = prim->g0 = prim->b0 = 0xE0;
        LOW(prim->r1) = LOW(prim->r0);
        LOW(prim->r2) = LOW(prim->r0);
        LOW(prim->r3) = LOW(prim->r0);
        prim->priority = 0x38;
        prim->drawMode =
            DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS | DRAW_UNK02 | DRAW_TRANSP;
        for (i = 0; i < 0xB; i++) {
            prim->tpage = 0x14;
            prim->clut = PAL_BASE;
            prim->u0 = prim->u2 = 0x38;
            prim->u1 = prim->u3 = 0x40;
            prim->v0 = prim->v1 = 0x50;
            prim->v2 = prim->v3 = 0x58;
            prim->r0 = prim->g0 = prim->b0 = 0xC0 - (i << 4);
            LOW(prim->r1) = LOW(prim->r0);
            LOW(prim->r2) = LOW(prim->r0);
            LOW(prim->r3) = LOW(prim->r0);
            prim->priority = 0x38;
            prim->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS |
                             DRAW_UNK02 | DRAW_TRANSP;
            prim = prim->next;
        }
        prim->tpage = 0x14;
        prim->clut = PAL_BASE;
        prim->u0 = prim->u2 = 0x38;
        prim->u1 = prim->u3 = 0x40;
        prim->v0 = prim->v1 = 0x40;
        prim->v2 = prim->v3 = 0x28;
        prim->r0 = prim->g0 = prim->b0 = 0;
        LOW(prim->r1) = LOW(prim->r0);
        LOW(prim->r2) = LOW(prim->r0);
        LOW(prim->r3) = LOW(prim->r0);
        prim->priority = 0x38;
        prim->drawMode =
            DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS | DRAW_UNK02 | DRAW_TRANSP;
        pt = self->trail;
        for (i = 0; i < 0xE; i++) {
            pt->x = self->posX.i.hi;
            pt->y = self->posY.i.hi;
            pt++;
        }
        angle = self->rotate;
        self->velocityX = rcos(angle) << 7;
        self->velocityY = rsin(angle) << 7;
        self->angle = angle;
        self->timer = 12;
    case 1:
        MoveEntity();
        player = &g_Entities[0];
        angle = GetAngleBetweenEntities((Entity*)self, player);
        angle = LimitAngleChange(0x80, self->angle, angle);
        self->velocityX = rcos(angle) << 7;
        self->velocityY = rsin(angle) << 7;
        self->angle = angle;
        if (!--self->timer) {
            self->zPriority = 0x50;
            self->step++;
        }
        break;
    case 2:
        MoveEntity();
        offX = self->posX.i.hi + g_Tilemap.scrollX.i.hi;
        offY = self->posY.i.hi + g_Tilemap.scrollY.i.hi;
        if (offX < -0x40 || offY < -0x40 || offX > 0x240 || offY > 0x200) {
            DestroyEntity((Entity*)self);
            return;
        }
        break;
    }
    pt = &self->trail[13];
    for (i = 0; i < 0xD; i++) {
        pt->x = pt[-1].x - g_ScrollDeltaX;
        pt->y = pt[-1].y - g_ScrollDeltaY;
        pt--;
    }
    pt = self->trail;
    pt->x = self->posX.i.hi;
    pt->y = self->posY.i.hi;
    pt = self->trail;
    prim = self->prim;
    baseX = pt->x;
    baseY = pt->y;
    prim = self->prim;
    offX = pt[1].x - baseX;
    offY = pt[1].y - baseY;
    angle = ratan2(offY, offX);
    angle -= 0x400;
    offX = (rcos(angle) << 1) >> 12;
    offY = (rsin(angle) << 1) >> 12;
    prim->x0 = baseX + offX;
    prim->y0 = baseY + offY;
    prim->x1 = baseX - offX;
    prim->y1 = baseY - offY;
    prim->priority = self->zPriority;
    pt++;
    for (i = 0; i < 11; i++) {
        offX = pt->x - baseX;
        offY = pt->y - baseY;
        angle = ratan2(offY, offX);
        angle -= 0x400;
        baseX = (pt->x + baseX) / 2;
        baseY = (pt->y + baseY) / 2;
        offX = (rcos(angle) << 2) >> 12;
        offY = (rsin(angle) << 2) >> 12;
        prim->x2 = baseX + offX;
        prim->y2 = baseY + offY;
        prim->x3 = baseX - offX;
        prim->y3 = baseY - offY;
        prim->priority = self->zPriority;
        prim = prim->next;
        prim->x0 = baseX + offX;
        prim->y0 = baseY + offY;
        prim->x1 = baseX - offX;
        prim->y1 = baseY - offY;
        baseX = pt->x;
        baseY = pt->y;
        pt++;
    }
    prim->x1 = prim->x3 = pt->x;
    prim->y1 = prim->y3 = pt->y;
    prim->priority = self->zPriority;
}
