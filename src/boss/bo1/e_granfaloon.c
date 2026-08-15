// SPDX-License-Identifier: AGPL-3.0-or-later
#include "bo1.h"

static s32 D_us_80180CD8 = 0;
static s32 D_us_80180CDC = 0;
static s32 D_us_80180CE0 = 0;
static s32 D_us_80180CE4 = 0; // main boss status, 0x01:dead, 0x08:?
static s16 D_us_80180CE8[] = {0, 18, 8, 0};
static s16 sensors_unused_1[] = {0, 18, 0, 4};
static s16 sensors_unused_2[] = {8, -4, -16, 0};
static s16 D_us_80180D00[] = {
    -1024, 1024, 2048, 0, -1536, -512, 512, 1536, 0, 0};
static s32 D_us_80180D14[] = {3, 6, 1, 7, 2, 4, 0, 5};
static s16 D_us_80180D34[9][5] = {
    {65, 69, 67, 68, 66}, {79, 69, 81, 82, 80}, {72, 69, 74, 75, 73},
    {86, 69, 88, 89, 87}, {69, 68, 70, 71, 0},  {90, 68, 91, 92, 0},
    {83, 68, 84, 85, 0},  {76, 68, 77, 78, 0},  {61, 70, 63, 64, 62},
};
static s16 pad_D34 = 0;
static s16 D_us_80180D90[] = {
    0, -26, 0, 26, -24, 0, 24, 0, -16, -18, 16, -18, 16, 18, -16, 16,
};
static s16 D_us_80180DA0[] = {
    0, -40, 0, 40, -40, 0, 40, 0, -30, -30, 30, -30, 30, 30, -30, 30,
};
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
    POSE(4, 0x3A, 0),
    POSE(8, 0x3B, 0),
    POSE(64, 0x3C, 0),
    POSE_END,
};
static AnimateEntityFrame D_us_80180E18[] = {
    POSE(8, 0x3C, 0),
    POSE(8, 0x3B, 0),
    POSE(4, 0x3A, 0),
    POSE_END,
};
static AnimateEntityFrame D_us_80180E20[] = {
    POSE(4, 0x5D, 0), POSE(4, 0x5E, 0), POSE(4, 0x5F, 0), POSE(4, 0x60, 0),
    POSE_END};
static AnimateEntityFrame D_us_80180E2C[] = {
    POSE(4, 0x61, 0), POSE(4, 0x62, 0), POSE(4, 0x63, 0), POSE_END};

#ifdef VERSION_PSP
// PSP keeps these format strings in .data, between the pose and hitbox tables;
// naming them pins that order, which anonymous literals would not.
static char fmt_y[] = "y %x\n";
static char fmt_charal[] = "charal %x\n";
#define FMT_Y fmt_y
#define FMT_CHARAL fmt_charal
#else
#define FMT_Y "y %x\n"
#define FMT_CHARAL "charal %x\n"
#endif

// hitbox table, indexed through hitbox_lookup[animCurFrame]
// {hitboxOffX, hitboxOffY, hitboxWidth, hitboxHeight}
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

extern EInit D_us_80180B1C;
extern EInit D_us_80180B28;
extern EInit D_us_80180B34;
extern EInit g_EInitGrafaloonZombie;
extern EInit D_us_80180B4C;
extern s32 D_us_80180CD4; // is Granfaloon spawned yet?
extern EInit g_EInitGranfaloon1;
extern EInit g_EInitGranfaloon2;

#ifdef VERSION_PSP
extern s32 E_ID(UNK_19);
extern s32 E_ID(UNK_1A);
extern s32 E_ID(UNK_1B);
extern s32 E_ID(UNK_1D);
extern s32 E_ID(UNK_1E);
extern s32 E_ID(UNK_1F);
extern s32 E_ID(ZOMBIE_FALLING);
extern s32 E_ID(ZOMBIE_ENEMY);
extern s32 E_ID(UNK_22);
extern s32 E_ID(UNK_1C);
extern s32 E_ID(LASER);
extern s32 E_ID(LIFE_UPSPAWN);
#endif

#include "../../st/approach_s16.h"

void EntityGranfaloon(Entity* self) {
    // the actual entity is the core of Granfaloon, which internally spawns 9
    // entities that will act like an armor.
    typedef enum Step {
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
        InitializeEntity(g_EInitGranfaloon1);
        self->zPriority = 0x40;
        self->animCurFrame = 1;
        self->hitboxState = 0;
        D_us_80180CE4 = 0;
        D_us_80180CD8 = 0;
        D_us_80180CE0 = 0;
        self->posX.i.hi = 0x100 - g_Tilemap.scrollX.i.hi;
        self->posY.i.hi = 0x240 - g_Tilemap.scrollY.i.hi;
        ent = self + 10;
        for (i = 0; i < 8; i++, ent += 5) {
            CreateEntityFromEntity(E_ID(UNK_19), self, ent);
            ent->zPriority = self->zPriority + 1;
            ent->params = i;
        }
        ent = self + 1;
        for (i = 0; i < 9; i++, ent++) {
            CreateEntityFromEntity(E_ID(UNK_1C), self, ent);
            ent->ext.et_801A1878.parent = self;
            ent->params = i;
        }
        self->ext.et_801A1878.unk99 = 7;
        self->ext.et_801A1878.unk86 = 0;
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
            D_us_80180CD4 = 1;
            D_us_80180CE4 |= 0x10;
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
                g_api.func_80102CD8(1);
            }
            y = self->posY.i.hi + g_Tilemap.scrollY.i.hi;
            FntPrint(FMT_Y, y);
            if (y < 0x100) {
                SetStep(FLOAT_IDLE);
            }
            if (y < 0x1C0) {
                self->ext.et_801A1878.unk86 = 0x7F;
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
                CreateEntityFromEntity(E_EXPLOSION, self, ent);
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
            self->ext.et_801A1878.unk99 = 0xF;
            self->ext.et_801A1878.unk86 = 0xFF;
            self->ext.et_801A1878.timer = 0x180;
            self->ext.et_801A1878.activeParts = 0;
            self->step_s++;
        }
        MoveEntity();
        x = 0x100 - g_Tilemap.scrollX.i.hi;
        y = 0x120 - g_Tilemap.scrollY.i.hi;
        angle = self->ext.et_801A1878.angle += 0x10;
        angle &= 0xFFF;
        x += (rcos(angle) * 5) << 4 >> 12;
        y += (rsin(angle) * 5) << 4 >> 12;
        x -= self->posX.i.hi;
        y -= self->posY.i.hi;
        angle = ratan2(y, x);
        self->velocityX = (rcos(angle) * 3) << 13 >> 12;
        self->velocityY = (rsin(angle) * 3) << 13 >> 12;
        if (!--self->ext.et_801A1878.timer) {
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
                    self->ext.et_801A1878.partIndex = offsetX;
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
            self->ext.et_801A1878.timer = 0x40;
            self->ext.et_801A1878.unk99 = 3;
            self->ext.et_801A1878.unk86 = 0;
            g_api.PlaySfx(SFX_GRANFALOON_BODIES_FALL);
            self->step_s++;
        case 1:
            if (!--self->ext.et_801A1878.timer) {
                self->ext.et_801A1878.timer = 0x100;
                self->ext.et_801A1878.unk99 = 3;
                self->ext.et_801A1878.unk86 = 0x1F;
                self->step_s++;
                if (Random() & 1) {
                    g_api.PlaySfx(SFX_GRANFALOON_SCREAMS_A);
                } else {
                    g_api.PlaySfx(SFX_GRANFALOON_SCREAMS_B);
                }
            }
            break;
        case 2:
            if (!--self->ext.et_801A1878.timer) {
                SetStep(FLOAT_IDLE);
            }
            break;
        }
        break;
    case UNK_6:
        switch (self->step_s) {
        case 0:
            self->ext.et_801A1878.unk99 = 7;
            self->ext.et_801A1878.unk86 = 0;
            self->velocityX = 0;
            self->velocityY = 0;
            D_us_80180CDC = 0;
            self->ext.et_801A1878.activeParts =
                1 << self->ext.et_801A1878.partIndex;
            self->step_s++;
        case 1:
            if (D_us_80180CDC) {
                self->step_s++;
            }
            break;
        case 2:
            angle = D_us_80180D00[self->ext.et_801A1878.partIndex];
            angle += 0x800;
            self->velocityX = rcos(angle) << 17 >> 12;
            self->velocityY = rsin(angle) << 17 >> 12;
            self->ext.et_801A1878.unk99 = 0xFF;
            self->ext.et_801A1878.unk86 = 0;
            self->step_s++;
        case 3:
            MoveEntity();
            self->velocityX -= self->velocityX >> 4;
            self->velocityY -= self->velocityY >> 4;
            if (D_us_80180CDC == 0) {
                self->ext.et_801A1878.activeParts = 0;
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
            self->ext.et_801A1878.timer = 0x80;
            self->ext.et_801A1878.activeParts = 0;
            self->ext.et_801A1878.angle = Random() << 4;
            self->step_s++;
        }
        if (!(self->ext.et_801A1878.timer & 0x1F)) {
            PlaySfxPositional(SFX_BAT_ECHO_A);
            ent = g_Entities;
            angle = GetAngleBetweenEntities(self, ent);
            angle -= 0x800;
            angle -= 0x300;
            for (i = 0; i < 4; i++) {
                ent = AllocEntity(&g_Entities[144], &g_Entities[192]);
                if (ent != NULL) {
                    CreateEntityFromEntity(E_ID(LASER), self, ent);
                    ent->rotate = angle;
                }
                angle += 0x200;
            }
        }
        MoveEntity();
        x = 0x100 - g_Tilemap.scrollX.i.hi;
        y = 0x120 - g_Tilemap.scrollY.i.hi;
        angle = self->ext.et_801A1878.angle += 0x20;
        angle &= 0xFFF;
        x += rcos(angle) << 6 >> 12;
        y += rsin(angle) << 6 >> 12;
        x -= self->posX.i.hi;
        y -= self->posY.i.hi;
        angle = ratan2(y, x);
        self->velocityX = rcos(angle) << 16 >> 12;
        self->velocityY = rsin(angle) << 16 >> 12;
        if (!--self->ext.et_801A1878.timer) {
            ent = g_Entities;
            x = ent->posX.i.hi - self->posX.i.hi;
            y = ent->posY.i.hi - self->posY.i.hi;
            angle = ratan2(y, x);
            angle += 0x100;
            angle &= 0xFFF;
            angle >>= 9;
            offsetX = D_us_80180D14[angle];
            self->ext.et_801A1878.partIndex = offsetX;
            SetStep(UNK_6);
        }
        break;
    case DEAD:
        self->hitboxState = 0;
        switch (self->step_s) {
        case 0:
            g_api.TimeAttackController(3, 1);
            D_us_80180CE4 |= 1;
            g_api.PlaySfx(SET_UNK_92);
            currentMusicId = MU_RAINBOW_CEMETERY;
            self->velocityY = FIX(-0.75);
            self->velocityX = 0;
            self->step_s++;
        case 1:
            MoveEntity();
            self->velocityY += 0x400;
            if (self->velocityY > 0) {
                D_us_80180CE4 |= 8;
                self->drawFlags = ENTITY_ROTATE;
                self->ext.et_801A1878.timer = 0x80;
                self->drawFlags |= ENTITY_OPACITY;
                self->opacity = 0x80;
                self->step_s++;
            }
            break;
        case 2:
            MoveEntity();
            self->velocityY = FIX(0.5);
            self->rotate -= 0x40;
            if (!(self->ext.et_801A1878.timer & 3)) {
                self->opacity -= 1;
            }
            if (!(self->ext.et_801A1878.timer & 7)) {
                PlaySfxPositional(SFX_FIREBALL_SHOT_B);
            }
            if (!--self->ext.et_801A1878.timer) {
                D_us_80180CE4 |= 4;
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
                    CreateEntityFromEntity(E_ID(UNK_22), self, ent);
                    ent->params = 6;
                    ent->scaleX = self->scaleX;
                    ent->zPriority = self->zPriority;
                }
            }
            self->ext.et_801A1878.timer++;
            self->scaleX--;
            if (!(self->ext.et_801A1878.timer & 0x1F)) {
                PlaySfxPositional(SFX_BOSS_LARGE_FLAMES);
            }
            if (!self->scaleX) {
                self->step_s++;
            }
            break;
        case 5:
            ent = AllocEntity(&g_Entities[160], &g_Entities[192]);
            if (ent != NULL) {
                CreateEntityFromEntity(E_ID(LIFE_UPSPAWN), self, ent);
                ent->posX.i.hi = 0x100 - g_Tilemap.scrollX.i.hi;
                ent->posY.i.hi = 0x150 - g_Tilemap.scrollY.i.hi;
                ent->params = 1;
                D_us_80180CD4 = 0;
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
        FntPrint(FMT_CHARAL, self->animCurFrame);
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
    g_ClutIds[0x201] = g_ClutIds[self->ext.et_801A1878.palIndex + 0x202];
    if (!(g_Timer & self->ext.et_801A1878.unk99)) {
        self->ext.et_801A1878.palIndex++;
        self->ext.et_801A1878.palIndex &= 3;
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

void func_us_801A2774(Entity* self) {
    typedef enum Step {
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

    if (D_us_80180CE4 & 1) {
        self->flags |= FLAG_DEAD;
    }
    if ((self->flags & FLAG_DEAD) && self->step < 3) {
        SetStep(DEAD);
    }
    switch (self->step) {
    case INIT:
        InitializeEntity(g_EInitGranfaloon2);
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
                CreateEntityFromEntity(E_ID(UNK_1E), self, newEntity);
                newEntity->params = self->params;
                newEntity->ext.et_801A2CC4.parent = self;
            }
        }
    case WAIT_SPAWN:
        self->hitboxState = 0;
        if (D_us_80180CD4) {
            self->hitboxState = 3;
            self->step++;
        }
        break;
    case IDLE:
        newEntity = self->ext.et_801A2CC4.parent;
        self->posX.i.hi = newEntity->posX.i.hi;
        self->posY.i.hi = newEntity->posY.i.hi;
        if (!newEntity->ext.et_801A2CC4.hitTimer) {
            break;
        }
        if (Random() & newEntity->ext.et_801A2CC4.hitTimer) {
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
                    CreateEntityFromEntity(E_ID(UNK_1D), self, newEntity);
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

void func_us_801A2BC4(Entity* self) {
    s16 angle;
    s16* row;
    s32 index;

    switch (self->step) {
    case 0:
        InitializeEntity(D_us_80180B4C);
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

void func_us_801A2CC4(Entity* self) {
    s16* row;
    Entity* parent;

    if (D_us_80180CE4 & 1) {
        DestroyEntity(self);
        return;
    }
    switch (self->step) {
    case 0:
        InitializeEntity(D_us_80180B4C);
        self->zPriority = 0x3C;
        row = D_us_80180D34[self->params];
        self->animCurFrame = row[4];

    case 1:
        parent = self->ext.et_801A2CC4.parent;
        self->posX.i.hi = parent->posX.i.hi;
        self->posY.i.hi = parent->posY.i.hi;
        if (D_us_80180CD8 & (1 << self->params)) {
            DestroyEntity(self);
        }
        break;
    }
}

void func_us_801A2D90(Entity* self) {
    s32 var_s0;
    s16 angle;
    s32 posY;

    switch (self->step) {
    case 0:
        InitializeEntity(D_us_80180B4C);
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
        self->ext.et_801A2CC4.unk80 = (Random() & 0x1F) + 0x10;

    case 1:
        MoveEntity();
        self->rotate += 0x40;
        if (self->velocityY < FIX(3.0)) {
            self->velocityY += 0x1400;
        }
        break;
    }
    posY = self->posY.i.hi + g_Tilemap.scrollY.i.hi;
    if (posY > 0x1C8) {
        DestroyEntity(self);
    }
}

INCLUDE_ASM("boss/bo1/nonmatchings/e_granfaloon", func_us_801A2F2C);

#if defined(VERSION_US) && !defined(VERSION_PC)
INCLUDE_ASM("boss/bo1/nonmatchings/e_granfaloon", func_us_801A3480);
#else
#define STUFF() /* TODO please inline this */                                  \
    self->rotate = angle - 0x400;                                              \
    self->posX.i.hi = parent->posX.i.hi;                                       \
    self->posY.i.hi = parent->posY.i.hi;                                       \
    self->posX.i.hi += ((rcos(angle) * 40) >> 12);                             \
    self->posY.i.hi += ((rsin(angle) * 40) >> 12);                             \
    if (0) {                                                                   \
    }
void func_us_801A3480(Entity* self) {
    Entity* parent;
    s16 angle;
    s32 index;

    if ((D_us_80180CE4 & 1) && self->step < 3) {
        SetStep(3);
    }
    switch (self->step) {
    case 0:
        InitializeEntity(D_us_80180B1C);
        self->animCurFrame = 0x3A;
        self->drawFlags = ENTITY_OPACITY;
        self->drawFlags |= ENTITY_ROTATE;
        self->opacity = D_us_80180DD0[self->params];
        self->rotate = D_us_80180D00[self->params] - 0x400;
    case 1:
        index = self->params;
        parent = self - 1;
        angle = parent->rotate + D_us_80180D00[index];
        STUFF();
        if (parent->ext.et_801A2CC4.unk84) {
            SetStep(2);
        }
        break;
    case 2:
        index = self->params;
        parent = self - 1;
        angle = parent->rotate + D_us_80180D00[index];
        STUFF();
        switch (self->step_s) {
        case 0:
            if (!AnimateEntity(D_us_80180E10, self)) {
                SetSubStep(1);
            }
            break;
        case 1:
            parent = self + 1;
            CreateEntityFromEntity(E_ID(UNK_1B), self, parent);
            parent->rotate = self->rotate;
            parent->zPriority = self->zPriority + 1;
            parent->ext.et_801A2CC4.parent = self;
            self->ext.et_801A2CC4.unk80 = 0x100;
            self->step_s++;

        case 2:
            parent = self + 1;
            if (parent->entityId != E_ID(UNK_1B)) {
                self->step_s++;
            }
            break;
        case 3:
            if (!AnimateEntity(D_us_80180E18, self)) {
                SetStep(1);
            }
            break;
        }
        break;
    case 3:
        index = self->params;
        parent = self - 1;
        angle = parent->rotate + D_us_80180D00[index];
        STUFF();
        switch (self->step_s) {
        case 0:
            self->hitboxState = 0;
            self->ext.et_801A2CC4.unk80 = self->params;
            self->step_s++;
            break;
        case 1:
            self->ext.et_801A2CC4.unk80++;
            if (!(self->ext.et_801A2CC4.unk80 & 7)) {
                parent = AllocEntity(&g_Entities[64], &g_Entities[256]);
                if (parent != NULL) {
                    CreateEntityFromEntity(E_ID(UNK_22), self, parent);
                    parent->params = 3;
                    parent->zPriority = 0x70;
                }
            }
            if (D_us_80180CE4 & 8) {
                self->step_s++;
            }
            break;
        case 2:
            self->animCurFrame = 0;
            DestroyEntity(self);
            break;
        }
        break;
    }
}
#endif

INCLUDE_ASM("boss/bo1/nonmatchings/e_granfaloon", func_us_801A38EC);

void EntityZombieFalling(Entity* self) {
    Entity* newEntity;
    s16 angle;
    s32 frame;
    s32 posY;

    if (D_us_80180CE4 & 1) {
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
        self->rotate += 0x18;
        if (self->flags & FLAG_DEAD) {
            self->velocityY = 0;
            self->hitboxState = 0;
            self->animCurFrame++;
            self->ext.et_801A2CC4.unk80 = 0x40;
            PlaySfxPositional(SFX_SMALL_FLAME_IGNITE);
            self->step++;
        }
        break;
    case 2:
        MoveEntity();
        self->velocityY += FIX(0.03125);
        if (!(self->ext.et_801A2CC4.unk80 & 7)) {
            newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (newEntity != NULL) {
                CreateEntityFromEntity(E_ID(UNK_22), self, newEntity);
                newEntity->params = 0;
                newEntity->zPriority = self->zPriority - 1;
                newEntity->posY.i.hi += 0x14;
            }
        }
        if (!--self->ext.et_801A2CC4.unk80) {
            DestroyEntity(self);
            return;
        }
        break;
    }
    posY = self->posY.i.hi + g_Tilemap.scrollY.i.hi;
    if (posY > 0x1C8) {
        DestroyEntity(self);
    }
}

void EntityZombieEnemy(Entity* self) {
    Collider collider;
    Entity* newEntity;
    s32 res;
    s32 posX;
    s32 posY;

    if (D_us_80180CE4 & 1) {
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
            AnimateEntity(D_us_80180DE0, self);
            res = UnkCollisionFunc2(D_us_80180CE8);
            if (res & 0x80) {
                DestroyEntity(self);
            }
            break;
        }
        break;
    case 4:
        switch (self->step_s) {
        case 0:
            self->hitboxState = 0;
            self->ext.et_801A2CC4.unk80 = (Random() & 0xF) + 0x10;
            self->animCurFrame = 0x71;
            PlaySfxPositional(SFX_SMALL_FLAME_IGNITE);
            self->step_s++;
        case 1:
            if (!(self->ext.et_801A2CC4.unk80 & 0xF)) {
                newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
                if (newEntity != NULL) {
                    CreateEntityFromEntity(E_ID(UNK_22), self, newEntity);
                    newEntity->posY.i.hi += 0x18;
                    newEntity->zPriority = self->zPriority + 1;
                    newEntity->params = 1;
                }
            }
            if (!--self->ext.et_801A2CC4.unk80) {
                self->ext.et_801A2CC4.unk80 = 0x10;
                self->animCurFrame = 0x72;
                self->step_s++;
            }
            break;
        case 2:
            if (!(self->ext.et_801A2CC4.unk80 & 7)) {
                newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
                if (newEntity != NULL) {
                    CreateEntityFromEntity(E_ID(UNK_22), self, newEntity);
                    newEntity->posY.i.hi += 0x18;
                    newEntity->zPriority = self->zPriority - 1;
                }
            }
            if (!--self->ext.et_801A2CC4.unk80) {
                DestroyEntity(self);
            }
            break;
        }
        break;
    }
}

void func_us_801A493C(Entity* self) {
    Collider collider;
    Entity* newEntity;
    s32 posX;
    s32 posY;
    s16 angle;

    if (D_us_80180CE4 & 1) {
        DestroyEntity(self);
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
        if (!self->ext.et_801A2CC4.hasHit) {
            posX = self->posX.i.hi;
            posY = self->posY.i.hi;
            g_api.CheckCollision(posX, posY, &collider, 0);
            if (collider.effects & EFFECT_SOLID) {
                self->ext.et_801A2CC4.hasHit = 1;
                newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
                if (newEntity != NULL) {
                    CreateEntityFromCurrentEntity(E_ID(UNK_22), newEntity);
                    newEntity->posX.i.hi += Random() & 0xF;
                    newEntity->posY.i.hi += Random() & 0xF;
                    newEntity->zPriority = 0x70;
                    newEntity->params = 2;
                }
            }
        }
        if (posX < 0 || posY < 0 || posX > 0x200 || posY > 0x200) {
            DestroyEntity(self);
        }
        break;
    }
}

void func_us_801A4AF4(Entity* self) {
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

    if (D_us_80180CE4 & 1) {
        DestroyEntity(self);
        return;
    }
    switch (self->step) {
    case 0:
        InitializeEntity(D_us_80180B28);
        self->hitboxWidth = self->hitboxHeight = 4;
        self->zPriority = 0x38;
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 13);
        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags |= FLAG_HAS_PRIMS;
        self->primIndex = primIndex;
        prim = &g_PrimBuf[primIndex];
        self->ext.et_801A4AF4.prim = prim;
        prim->tpage = 0x14;
        prim->clut = 0x200;
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
            prim->clut = 0x200;
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
        prim->clut = 0x200;
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
        pt = self->ext.et_801A4AF4.trail;
        for (i = 0; i < 0xE; i++) {
            pt->x = self->posX.i.hi;
            pt->y = self->posY.i.hi;
            pt++;
        }
        angle = self->rotate;
        self->velocityX = rcos(angle) << 7;
        self->velocityY = rsin(angle) << 7;
        self->ext.et_801A4AF4.angle = angle;
        self->ext.et_801A4AF4.timer = 0xC;
    case 1:
        MoveEntity();
        player = &g_Entities[0];
        angle = GetAngleBetweenEntities(self, player);
        angle = LimitAngleChange(0x80, self->ext.et_801A4AF4.angle, angle);
        self->velocityX = rcos(angle) << 7;
        self->velocityY = rsin(angle) << 7;
        self->ext.et_801A4AF4.angle = angle;
        if (!--self->ext.et_801A4AF4.timer) {
            self->zPriority = 0x50;
            self->step++;
        }
        break;
    case 2:
        MoveEntity();
        offX = self->posX.i.hi + g_Tilemap.scrollX.i.hi;
        offY = self->posY.i.hi + g_Tilemap.scrollY.i.hi;
        if (offX < -0x40 || offY < -0x40 || offX > 0x240 || offY > 0x200) {
            DestroyEntity(self);
            return;
        }
        break;
    }
    pt = &self->ext.et_801A4AF4.trail[13];
    for (i = 0; i < 0xD; i++) {
        pt->x = pt[-1].x - g_ScrollDeltaX;
        pt->y = pt[-1].y - g_ScrollDeltaY;
        pt--;
    }
    pt = self->ext.et_801A4AF4.trail;
    pt->x = self->posX.i.hi;
    pt->y = self->posY.i.hi;
    pt = self->ext.et_801A4AF4.trail;
    prim = self->ext.et_801A4AF4.prim;
    baseX = pt->x;
    baseY = pt->y;
    prim = self->ext.et_801A4AF4.prim;
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
