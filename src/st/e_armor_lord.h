// SPDX-License-Identifier: AGPL-3.0-or-later

// It turns out that the Armor Lord and Guardian enemies share the
// vast majority of their code. Armor Lord was decompiled first.
// Simply #define GUARDIAN prior to #include on this file and it will
// load up as a Guardian instead of Armor Lord.

extern EInit g_EInitInteractable;
extern EInit g_EInitArmorLord;
extern EInit g_EInitArmorLordSwordShadow;
extern EInit g_EInitArmorLordTemp;

// The Armor Lord in the Outer Wall has perma-death.
#ifdef STAGE_IS_NO1
static s32 hasBeenKilled = false;
#endif

typedef enum {
    AL_INIT,
    AL_1,
    AL_WAIT_PLAYER_CLOSE,
    AL_WALK,
    AL_FIREBALLS,
    AL_SWORD_HIGH,
    AL_FIREWAVE_ATTACK,
    AL_SHIELD,
    AL_DIE,
    AL_FADEAWAY
} ArmorLordSteps;

static u8 randomSteps[] = {
    AL_SWORD_HIGH, AL_FIREBALLS, AL_FIREWAVE_ATTACK, AL_FIREWAVE_ATTACK,
    AL_SWORD_HIGH, AL_FIREBALLS, AL_FIREWAVE_ATTACK, AL_SWORD_HIGH};
static s16 sensors1[] = {0, 40, 0, 4, 8, -4, -16, 0};
static s16 sensors2[] = {0, 40, 8, 0};
static s16 attackTimers[] =
#ifdef GUARDIAN
    {16, 8, 32, 24};
#else
    {32, 24, 48, 40};
#endif

// animations
// Animation to take a single step
static AnimateEntityFrame anim_walk_cycle[] = {
    {16, 1}, {24, 2}, {16, 1}, {24, 3}, POSE_LOOP(0)};
// Windup for the attack with 3 fireballs repeatedly blasting out end of sword
static AnimateEntityFrame anim_charge_fireball[] =
#ifdef GUARDIAN
    {{4, 1}, {8, 4},  {38, 5}, {6, 6},  {6, 7},  {6, 8},
     {2, 9}, {2, 10}, {2, 11}, {1, 12}, {1, 13}, POSE_END};
#else
    {{32, 1}, {8, 4},  {70, 5}, {6, 6},  {6, 7},  {6, 8},
     {2, 9},  {2, 10}, {2, 11}, {1, 12}, {1, 13}, POSE_END};
#endif
// Rapidly twitching while fireballs float in the air in front of him
static AnimateEntityFrame anim_fireball[] = {{1, 12}, {1, 13}, POSE_LOOP(0)};
// Goes from kneeling pose back to standing
static AnimateEntityFrame anim_end_fireball[] = {
    {8, 14}, {8, 15}, {16, 1}, POSE_END};
#ifdef GUARDIAN
static AnimateEntityFrame anim_overhead_slice[] = {
    {4, 1},  {8, 4},  {2, 17},  {40, 16}, {1, 17}, {1, 18},
    {1, 19}, {1, 20}, {33, 21}, {6, 22},  {6, 15}, POSE_END};
static AnimateEntityFrame anim_launch_flametrail[] = {
    {4, 1},  {6, 15}, {6, 23},  {6, 24}, {24, 25}, {1, 26}, {1, 27},
    {1, 28}, {1, 29}, {32, 16}, {6, 17}, {8, 4},   POSE_END};
#else
static AnimateEntityFrame anim_overhead_slice[] = {
    {40, 1}, {8, 4},  {2, 17},  {72, 16}, {1, 17}, {1, 18},
    {1, 19}, {1, 20}, {33, 21}, {6, 22},  {6, 15}, POSE_LOOP(0)};
static AnimateEntityFrame anim_launch_flametrail[] = {
    {32, 1}, {6, 15}, {6, 23},  {6, 24}, {40, 25}, {1, 26},     {1, 27},
    {1, 28}, {1, 29}, {64, 16}, {6, 17}, {32, 4},  POSE_LOOP(0)};
#endif
static AnimateEntityFrame anim_create_shield[] = {
    {8, 1}, {6, 4}, {97, 30}, {4, 4}, POSE_END};
static AnimateEntityFrame anim_death[] = {{24, 34}, {24, 35}, POSE_END};

static MATRIX armorLordColorMatrix = {{{FLT(0.0), FLT(0.0), FLT(1.0)},
                                       {FLT(0.0), FLT(0.0), FLT(0.5)},
                                       {FLT(0.0), FLT(0.0), FLT(1.0)}}};

static SVECTOR armorLordColNormVec1 = {FLT(0.0), FLT(0.0), FLT(1.0)};
static SVECTOR armorLordColNormVec2 = {FLT(0.0), FLT(0.5), FLT(0.5)};
static SVECTOR armorLordRotVec = {FLT(0.0), FLT(0.0), FLT(0.0)};

// BUG! These data types seem backwards but PSP does actually appear
// to load them as s16 and u16 respectively.
static s16 hitboxWidthHeights[][2] = {
    {0, 0},  {11, 11}, {11, 11}, {13, 6},  {18, 4},  {18, 4}, {21, 4},
    {30, 4}, {35, 9},  {35, 9},  {31, 4},  {15, 12}, {23, 4}, {17, 9},
    {10, 9}, {10, 21}, {29, 4},  {24, 6},  {29, 4},  {22, 7}, {15, 10},
    {9, 11}, {29, 4},  {10, 10}, {12, 10}, {24, 4},  {4, 32}};

static u16 hitboxOffXYs[][2] = {
    {0, 0},    {16, -18}, {12, -17}, {-8, -10},  {-9, 5},  {-17, 2},
    {-23, 5},  {-36, 6},  {-45, 6},  {-45, 6},   {-36, 6}, {-22, -6},
    {54, 6},   {39, -13}, {21, -35}, {-18, -34}, {-38, 5}, {-36, 30},
    {-29, 19}, {-14, 21}, {-20, 29}, {-7, 27},   {-36, 7}, {-11, -6},
    {21, -3},  {47, 3},   {-22, -4},
// This could be an error in the splat or something
#ifdef GUARDIAN
    {0, 0}
#endif
};

// Armor Lord fire wave helper
static void FireWavePrimHelper1(Primitive* prim) {
    switch (prim->next->u2) {
    case 0:
        prim->tpage = 0x1A;
        prim->clut = PAL_CC_FIRE_EFFECT;
        prim->u0 = 0xF0;
        prim->u1 = 0xFF;
        prim->u2 = prim->u0;
        prim->u3 = prim->u1;
        if (prim->next->r3) {
            prim->v0 = 0;
            prim->v1 = prim->v0;
            prim->v2 = 0xF;
            prim->v3 = prim->v2;
        } else {
            prim->v0 = 0x28;
            prim->v1 = prim->v0;
            prim->v2 = 0x37;
            prim->v3 = prim->v2;
        }
        prim->priority = g_CurrentEntity->zPriority + 2;
        prim->drawMode =
            DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS | DRAW_UNK02 | DRAW_TRANSP;
        prim->x0 -= 8;
        prim->x1 = prim->x0 + 16;
        prim->x2 = prim->x0;
        prim->x3 = prim->x1;
        prim->y0 -= 8;
        prim->y1 = prim->y0;
        prim->y2 = prim->y0 + 0x10;
        prim->y3 = prim->y2;
        PGREY(prim, 0) = 0xA0;
        PGREY(prim, 1) = 0xA0;
        PGREY(prim, 2) = 0xA0;
        PGREY(prim, 3) = 0xA0;
        prim->next->u2++;
        break;

    case 1:
        if (g_Timer % 4 == 0) {
            prim->y0++;
            prim->y1 = prim->y0;
            prim->y2 = prim->y0 + 0x10;
            prim->y3 = prim->y2;
        }
        prim->r0 -= 2;
        prim->g0 = prim->b0 = prim->r0;
        prim->r1 = prim->g1 = prim->b1 = prim->r0;
        prim->r2 = prim->g2 = prim->b2 = prim->r0;
        prim->r3 = prim->g3 = prim->b3 = prim->r0;
        if (prim->r0 < 0x10) {
            UnkPolyFunc0(prim);
            prim->next->u2 = 0;
        }
        break;
    }
}

extern Primitive* FindFirstUnkPrim2(Primitive* prim, u8 index);
// Armor Lord
static void FireWavePrimHelper2(Primitive* prim) {
    Collider collider;
    Primitive* otherPrim;
    Entity* tempEntity;
    s16 dx;
    s16 posX, posY;

    if (g_Timer % 3 == 0) {
        u8 temp = prim->u0;
        prim->u0 = prim->u1;
        prim->u1 = temp;
        prim->u2 = prim->u0;
        prim->u3 = prim->u1;
    }
    switch (prim->next->u2) {
    case 0:
        prim->x0 = prim->x2;
        prim->x1 = prim->x3;
        prim->y0 = prim->y2;
        prim->y1 = prim->y3;
        prim->tpage = 0x14;
        prim->clut = PAL_ARMOR_LORD_UNK;
        prim->u0 = 0xE0;
        prim->u1 = 0xEF;
        prim->u2 = prim->u0;
        prim->u3 = prim->u1;
        prim->v0 = 0xD0;
        prim->v1 = prim->v0;
        prim->v2 = 0xD0;
        prim->v3 = prim->v2;
        PGREY(prim, 0) = 0x70;
        PGREY(prim, 1) = 0x70;
        PGREY(prim, 2) = 0x70;
        PGREY(prim, 3) = 0x70;
        prim->priority = g_CurrentEntity->zPriority + 2;
        prim->drawMode =
            DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS | DRAW_UNK02 | DRAW_TRANSP;
        prim->next->u2++;
        break;

    case 1:
        prim->v2 += 2;
        prim->v3 = prim->v2;
        prim->y0 -= 2;
        prim->y1 -= 2;
        if (g_CurrentEntity->facingLeft) {
            prim->x3++;
        } else {
            prim->x3--;
        }
        prim->x1 = prim->x3;
        posX = prim->x3;
        posY = prim->y3 + 1;
        g_api.CheckCollision(posX, posY, &collider, 0);
        if ((collider.effects & EFFECT_SOLID) == 0) {
            prim->next->r3 = 0;
            prim->next->u2 += 1;
            break;
        }
        if ((prim->v2 == 0xE0) && prim->next->r3) {
            otherPrim = g_CurrentEntity->ext.armorLord.prim;
            otherPrim = FindFirstUnkPrim2(otherPrim, 2);
            if (otherPrim != NULL) {
                UnkPolyFunc2(otherPrim);
                otherPrim->next->r3 = prim->next->r3 - 1;
                if (g_CurrentEntity->facingLeft) {
                    otherPrim->x2 = prim->x3 - 8;
                    otherPrim->x3 = otherPrim->x2 + 16;
                } else {
                    otherPrim->x2 = prim->x3 + 8;
                    otherPrim->x3 = otherPrim->x2 - 16;
                }
                otherPrim->y2 = prim->y3;
                otherPrim->y3 = otherPrim->y2;
            }
        }
        if (prim->v2 > 0xFD) {
            otherPrim = g_CurrentEntity->ext.armorLord.prim;
            otherPrim = FindFirstUnkPrim2(otherPrim, 2);
            if (otherPrim != NULL) {
                UnkPolyFunc2(otherPrim);
                otherPrim->next->g3 = 1;
                otherPrim->next->r3 = Random() & 1;
                if (g_CurrentEntity->facingLeft) {
                    otherPrim->x0 = prim->x1 - 0x10;
                } else {
                    otherPrim->x0 = prim->x1 + 0x10;
                }
                otherPrim->y0 = prim->y1 + 0x10;
            }
            prim->next->u2++;
        }
        break;

    case 2:
        prim->v2--;
        prim->v3 = prim->v2;
        prim->y0++;
        prim->y1++;
        prim->g0 -= 4;
        prim->b0 -= 2;
        prim->r1 = prim->r2 = prim->r3 = prim->r0;
        prim->g1 = prim->g2 = prim->g3 = prim->g0;
        prim->b1 = prim->b2 = prim->b3 = prim->b0;
        if (prim->v2 < 0xD2) {
            UnkPolyFunc0(prim);
            prim->next->u2 = 0;
        }
        break;
    }
    tempEntity = &PLAYER;
    if (g_CurrentEntity->facingLeft) {
        dx = prim->x3 - tempEntity->posX.i.hi;
    } else {
        dx = tempEntity->posX.i.hi - prim->x3;
    }
    if ((dx > 0) && !prim->next->v2 && (dx < 0x10)) {
        tempEntity = AllocEntity(&g_Entities[160], &g_Entities[192]);
        if (tempEntity != NULL) {
            CreateEntityFromCurrentEntity(E_ARMOR_LORD_UNK2, tempEntity);
            tempEntity->posX.i.hi = prim->x3;
            tempEntity->posY.i.hi = prim->y0;
            tempEntity->facingLeft = g_CurrentEntity->facingLeft;
            tempEntity->hitboxHeight = (prim->y2 - prim->y0) / 2;
            tempEntity->hitboxOffY = tempEntity->hitboxHeight + 8;
            tempEntity->ext.armorLord.prim = prim;
            prim->next->v2 = 1;
        }
    }
}

void EntityArmorLordFireWave(Entity* self) {
    Primitive* prim;
    s32 primIndex;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitInteractable);
        self->ext.armorLord.timer = 0;
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 0x1A);
        if (primIndex != -1) {
            self->flags |= FLAG_HAS_PRIMS;
            self->primIndex = primIndex;
            prim = &g_PrimBuf[primIndex];
            self->ext.armorLord.prim = prim;
            while (prim != NULL) {
                prim->drawMode = DRAW_HIDE;
                prim->p3 = 0;
                prim = prim->next;
            }
        } else {
            DestroyEntity(self);
            return;
        }
        prim = self->ext.armorLord.prim;
        prim = FindFirstUnkPrim2(prim, 2);
        if (prim != NULL) {
            UnkPolyFunc2(prim);
            prim->x2 = self->posX.i.hi;
            if (self->facingLeft) {
                prim->x3 = prim->x2 + 0x20;
            } else {
                prim->x3 = prim->x2 - 0x20;
            }
            prim->y2 = self->posY.i.hi + 0x28;
            prim->y3 = prim->y2;
            prim->next->r3 = 5;
            prim->next->g3 = 0;
        }

    case 1:
        prim = self->ext.armorLord.prim;
        while (prim != NULL) {
            if (prim->p3 & 8) {
                if (prim->next->g3) {
                    FireWavePrimHelper1(prim);
                } else {
                    FireWavePrimHelper2(prim);
                }
            }
            prim = prim->next;
        }
        if (self->ext.armorLord.timer++ > 0x100) {
            DestroyEntity(self);
            return;
        }
    }
}

void EntityArmorLordUnused(Entity* self) {}

static void ArmorLordShieldHelper(void) {
    Primitive* prim;
    s32 primIndex;

    switch (g_CurrentEntity->step_s) {
    case 0:
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 2);
        if (primIndex != -1) {
            g_CurrentEntity->flags |= FLAG_HAS_PRIMS;
            g_CurrentEntity->primIndex = primIndex;
            prim = &g_PrimBuf[primIndex];
            g_CurrentEntity->ext.armorLord.prim = prim;
            UnkPolyFunc2(prim);
            prim->tpage = 0x1A;
            prim->clut = PAL_CC_STONE_EFFECT;
            prim->u0 = 0x14;
            prim->u1 = 0x2C;
            prim->u2 = prim->u0;
            prim->u3 = prim->u1;
            prim->v0 = 0xC0;
            prim->v1 = prim->v0;
            prim->v2 = 0xFF;
            prim->v3 = prim->v2;
            prim->priority = g_CurrentEntity->zPriority + 2;
            prim->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS |
                             DRAW_UNK02 | DRAW_TRANSP;
            prim->p3 = 8;
            if (g_CurrentEntity->facingLeft) {
                prim->next->x1 = g_CurrentEntity->posX.i.hi + 0x16;
            } else {
                prim->next->x1 = g_CurrentEntity->posX.i.hi - 0x16;
            }
            prim->next->y0 = g_CurrentEntity->posY.i.hi - 4;
            LOH(prim->next->r2) = 0;
            LOH(prim->next->b2) = 0;
            prim->next->b3 = 0x80;
        } else {
            g_CurrentEntity->step_s = 4;
            break;
        }
        g_CurrentEntity->hitboxState = 1;
        g_CurrentEntity->ext.armorLord.timer2 = 0;
        PlaySfxPositional(SFX_MAGIC_NOISE_SWEEP);
        g_CurrentEntity->step_s++;
        break;

    case 1:
        prim = g_CurrentEntity->ext.armorLord.prim;
        LOH(prim->next->r2)++;
        LOH(prim->next->b2) += 8;
        UnkPrimHelper(prim);
        if (g_CurrentEntity->ext.armorLord.timer2++ > 8) {
            g_CurrentEntity->ext.armorLord.timer2 = 0;
            g_CurrentEntity->step_s++;
        }
        break;

    case 2:
        break;

    case 3:
        prim = g_CurrentEntity->ext.armorLord.prim;
        prim->next->b3 -= 8;
        UnkPrimHelper(prim);
        if (g_CurrentEntity->ext.armorLord.timer2++ > 15) {
            primIndex = g_CurrentEntity->primIndex;
            g_api.FreePrimitives(primIndex);
            g_CurrentEntity->flags &= ~FLAG_HAS_PRIMS;
        }
        break;
    }
}

static s32 FadeArmorLordDeath(void) {
    long unusedA, unusedB;
    SVECTOR rotA, rotB, rotC;
    VECTOR trans;
    MATRIX m;
    MATRIX lightMatrix;
    CVECTOR color;

    s16 posX, posY;
    Primitive* prim;
    Primitive* prim2;
    s16 z;
    s32 primIndex;
    s32 i;
    u8 temp;
    s32 unused;

    switch (g_CurrentEntity->step_s) {
    case 0:
        g_CurrentEntity->ext.armorLord.timer3 = 0;
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 0xE);
        if (primIndex != -1) {
            g_CurrentEntity->flags |= FLAG_HAS_PRIMS;
            g_CurrentEntity->primIndex = primIndex;
            prim = &g_PrimBuf[primIndex];
            g_CurrentEntity->ext.armorLord.prim = prim;
            prim = g_CurrentEntity->ext.armorLord.prim;
            if (g_CurrentEntity->facingLeft) {
                prim->u0 = 0xFF;
                prim->u1 = 0xD8;
                prim->x0 = g_CurrentEntity->posX.i.hi - 0x1A;
            } else {
                prim->u0 = 0xD8;
                prim->u1 = 0xFF;
                prim->x0 = g_CurrentEntity->posX.i.hi - 0xD;
            }
            prim->x1 = prim->x0 + 0x28;
            prim->r0 = prim->g0 = prim->b0 = 0;
            LOW(prim->r1) = LOW(prim->r0);
            LOW(prim->r2) = LOW(prim->r0);
            LOW(prim->r3) = LOW(prim->r0);
            prim->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS |
                             DRAW_UNK02 | DRAW_TRANSP;

            prim2 = prim;
            prim = prim->next;
            prim->u0 = prim2->u0;
            prim->u1 = prim->u0;
            prim->x0 = prim2->x0;
            prim->x1 = prim->x0;
            prim->r0 = prim->g0 = prim->b0 = 0x20;
            LOW(prim->r2) = LOW(prim->r0);
            prim->r1 = prim->g1 = prim->b1 = 0x80;
            LOW(prim->r3) = LOW(prim->r1);
            prim->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS |
                             DRAW_UNK02 | DRAW_TRANSP;

            prim = prim->next;
            prim->u0 = prim2->u1;
            prim->u1 = prim->u0;
            prim->x0 = prim2->x1;
            prim->x1 = prim->x0;
            prim->r0 = prim->g0 = prim->b0 = 0x80;
            LOW(prim->r2) = LOW(prim->r0);
            prim->r1 = prim->g1 = prim->b1 = 0x20;
            LOW(prim->r3) = LOW(prim->r1);
            prim->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS |
                             DRAW_UNK02 | DRAW_TRANSP;
            prim = g_CurrentEntity->ext.armorLord.prim;
            for (i = 0; i < 3; i++) {
                prim->tpage = 0x15;
                prim->clut = PAL_CC_FIRE_EFFECT;
                prim->u2 = prim->u0;
                prim->u3 = prim->u1;
                prim->v0 = 0;
                prim->v1 = prim->v0;
                prim->v2 = 0x37;
                prim->v3 = prim->v2;
                prim->x2 = prim->x0;
                prim->x3 = prim->x1;
                prim->y0 = g_CurrentEntity->posY.i.hi - 0x10;
                prim->y1 = prim->y0;
                prim->y2 = prim->y1 + 0x38;
                prim->y3 = prim->y2;
                prim->priority = g_CurrentEntity->zPriority + 1;
                prim = prim->next;
            }
            g_CurrentEntity->ext.armorLord.deathPrim = prim;
            while (prim != NULL) {
                prim->tpage = 0x14;
                prim->clut = PAL_ARMOR_LORD_UNK;
                prim->u0 = 0xE2;
                prim->u1 = 0xEC;
                prim->u2 = prim->u0;
                prim->u3 = prim->u1;
                prim->v0 = 0xD0;
                prim->v1 = prim->v0;
                prim->v2 = 0xD0;
                prim->v3 = prim->v2;
                prim->r0 = prim->g0 = prim->b0 = 0x40;
                LOW(prim->r1) = LOW(prim->r0);
                LOW(prim->r2) = LOW(prim->r0);
                LOW(prim->r3) = LOW(prim->r0);
                prim->priority = g_CurrentEntity->zPriority + 2;
                prim->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS |
                                 DRAW_UNK02 | DRAW_TRANSP;
                prim = prim->next;
            }
        } else {
            return 1;
        }

        g_CurrentEntity->ext.armorLord.fadeOutZ = 0x20;
        g_CurrentEntity->ext.armorLord.fadeOutY2 = 0;
        g_CurrentEntity->ext.armorLord.fadeOutY = 0;
        g_CurrentEntity->ext.armorLord.timer2 = 0;
        g_CurrentEntity->drawFlags |= ENTITY_OPACITY;
        g_CurrentEntity->opacity = 0x80;
        g_CurrentEntity->step_s++;
        break;

    case 1:
        prim = g_CurrentEntity->ext.armorLord.prim;
        prim->r0 += 2;
        prim->g0 = prim->b0 = prim->r0;
        LOW(prim->r1) = LOW(prim->r0);
        LOW(prim->r2) = LOW(prim->r0);
        LOW(prim->r3) = LOW(prim->r0);
        g_CurrentEntity->opacity -= 2;
        if (!g_CurrentEntity->opacity) {
            g_CurrentEntity->animCurFrame = 0;
            prim->drawMode = DRAW_COLORS | DRAW_UNK02;
            g_CurrentEntity->ext.armorLord.timer3 += 1;
            PlaySfxPositional(SFX_FIREBALL_SHOT_A);
            g_CurrentEntity->step_s++;
        }
        break;

    case 2:
        g_CurrentEntity->step_s++;
        break;

    case 3:
        if (g_Timer % 8 == 0) {
            prim = g_CurrentEntity->ext.armorLord.prim;
            if (g_CurrentEntity->facingLeft) {
                prim->u0--;
                prim->u1++;
            } else {
                prim->u0++;
                prim->u1--;
            }
            prim->u2 = prim->u0;
            prim->u3 = prim->u1;
            prim->x0++;
            prim->x2 = prim->x0;
            prim->x1--;
            prim->x3 = prim->x1;

            prim = prim->next;
            if (g_CurrentEntity->facingLeft) {
                prim->u1--;
            } else {
                prim->u1++;
            }
            prim->u3 = prim->u1;
            prim->x1++;
            prim->x3 = prim->x1;
            prim->y0 -= 3;
            prim->y2 -= 1;

            prim = prim->next;
            if (g_CurrentEntity->facingLeft) {
                prim->u0++;
            } else {
                prim->u0--;
            }
            prim->u2 = prim->u0;
            prim->x0--;
            prim->x2 = prim->x0;
            prim->y1 -= 3;
            prim->y3 -= 1;
            g_CurrentEntity->ext.armorLord.timer2 += 1;
            if (g_CurrentEntity->ext.armorLord.timer2 > 5) {
                g_CurrentEntity->step_s++;
            }
        }
        break;

    case 5:
        if (g_Timer % 4 == 0) {
            prim = g_CurrentEntity->ext.armorLord.prim;
            if (g_CurrentEntity->facingLeft) {
                prim->u0--;
                prim->u1++;
            } else {
                prim->u0++;
                prim->u1--;
            }
            prim->u2 = prim->u0;
            prim->u3 = prim->u1;
            prim->x0++;
            prim->x2 = prim->x0;
            prim->x1--;
            prim->x3 = prim->x1;

            prim = prim->next;
            if (g_CurrentEntity->facingLeft) {
                prim->u0--;
                prim->u1--;
            } else {
                prim->u0++;
                prim->u1++;
            }
            prim->u2 = prim->u0;
            prim->u3 = prim->u1;
            prim->x0++;
            prim->x2 = prim->x0;
            prim->x1++;
            prim->x3 = prim->x1;

            prim = prim->next;
            if (g_CurrentEntity->facingLeft) {
                prim->u1++;
                prim->u0++;
            } else {
                prim->u1--;
                prim->u0--;
            }
            prim->u3 = prim->u1;
            prim->u2 = prim->u0;
            prim->x0--;
            prim->x2 = prim->x0;
            prim->x1--;
            prim->x3 = prim->x1;
            g_CurrentEntity->ext.armorLord.timer2++;
            if (g_CurrentEntity->ext.armorLord.timer2 > 0x14) {
                g_CurrentEntity->ext.armorLord.timer3 = 2;
                g_CurrentEntity->step_s++;
            }
        }
        break;

    case 6:
        if (g_Timer % 2 == 0) {
            prim = g_CurrentEntity->ext.armorLord.prim;
            prim = prim->next;
            if (g_CurrentEntity->facingLeft) {
                prim->u0--;
            } else {
                prim->u0++;
            }
            prim->u2 = prim->u0;
            prim->x0++;
            prim->x2 = prim->x0;

            prim = prim->next;
            if (g_CurrentEntity->facingLeft) {
                prim->u1++;
            } else {
                prim->u1--;
            }
            prim->u3 = prim->u1;
            prim->x1--;
            prim->x3 = prim->x1;
            g_CurrentEntity->ext.armorLord.timer2++;
            if (g_CurrentEntity->ext.armorLord.timer2 > 0x18) {
                g_CurrentEntity->step_s++;
            }
        }
        break;

    case 8:
        prim = g_CurrentEntity->ext.armorLord.prim;
        while (prim != NULL) {
            if (g_Timer % prim->p2 == 0) {
                prim->y0--;
            }
            prim->r0 -= 2;
            prim->g0 -= 2;
            prim->b0 -= 2;
            prim = prim->next;
        }
        if (g_CurrentEntity->ext.armorLord.timer2++ > 0x40) {
            return 1;
        }
        break;
    }

    if (g_CurrentEntity->ext.armorLord.timer3) {
        prim = g_CurrentEntity->ext.armorLord.deathPrim;
        prim2 = prim;
        unused = g_CurrentEntity->ext.armorLord.fadeOutY2;
        for (i = 0; i < 8; i++) {
            if (g_CurrentEntity->ext.armorLord.fadeOutY < 0x5C) {
                prim->v2++;
                prim->v3 = prim->v2;
            }
            if (g_Timer % 3 == 0) {
                temp = prim->u0;
                prim->u0 = prim->u1;
                prim->u1 = temp;
                prim->u2 = prim->u0;
                prim->u3 = prim->u1;
            }
            SetGeomScreen(0x400);
            rotC.vx = 0;
            rotC.vy = (i * 512) + g_CurrentEntity->ext.armorLord.fadeOutY2;
            rotC.vz = 0;
            RotMatrix(&armorLordRotVec, &m);
            RotMatrixY(rotC.vy, &m);
            SetRotMatrix(&m);
            trans.vx = 0;
            trans.vy = 0;
            trans.vz = 0x400;
            TransMatrix(&m, &trans);
            SetTransMatrix(&m);
            SetBackColor(0x20, 0x20, 0x20);
            color.r = 0x80;
            color.g = 0x60;
            color.b = 0x60;
            color.cd = prim->type;
            RotMatrix(&rotC, &lightMatrix);
            SetColorMatrix(&armorLordColorMatrix);
            SetLightMatrix(&lightMatrix);
            if (g_CurrentEntity->facingLeft) {
                posX = g_CurrentEntity->posX.i.hi - 5;
            } else {
                posX = g_CurrentEntity->posX.i.hi + 8;
            }
            posY = g_CurrentEntity->posY.i.hi + 0x29;
            SetGeomOffset(posX, posY);
            rotA.vx = 0;
            rotA.vy = 0;
            rotA.vz = -g_CurrentEntity->ext.armorLord.fadeOutZ;
            rotB.vx = 0;
            rotB.vy = -g_CurrentEntity->ext.armorLord.fadeOutY;
            rotB.vz = -g_CurrentEntity->ext.armorLord.fadeOutZ;
            prim->x0 = prim2->x1;
            prim->y0 = prim2->y1;
            prim->x2 = prim2->x3;
            prim->y2 = prim2->y3;
            prim->r0 = prim2->r1;
            prim->g0 = prim2->g1;
            prim->b0 = prim2->b1;
            prim->r2 = prim2->r3;
            prim->g2 = prim2->g3;
            prim->b2 = prim2->b3;
            z = RotTransPers(&rotA, (long*)(&prim->x3), &unusedA, &unusedB);
            z += RotTransPers(&rotB, (long*)(&prim->x1), &unusedA, &unusedB);
            z /= 2;
            NormalColorCol(
                &armorLordColNormVec1, &color, (CVECTOR*)(&prim->r3));
            NormalColorCol(
                &armorLordColNormVec2, &color, (CVECTOR*)(&prim->r1));
            prim->priority = g_CurrentEntity->zPriority + (0x101 - z);
            prim2 = prim;
            prim = prim->next;
        }
        prim = g_CurrentEntity->ext.armorLord.deathPrim;
        prim->x0 = prim2->x1;
        prim->y0 = prim2->y1;
        prim->x2 = prim2->x3;
        prim->y2 = prim2->y3;
        prim->r0 = prim2->r1;
        prim->g0 = prim2->g1;
        prim->b0 = prim2->b1;
        prim->r2 = prim2->r3;
        prim->g2 = prim2->g3;
        prim->b2 = prim2->b3;
        g_CurrentEntity->ext.armorLord.fadeOutY2 += 4;
        if (g_CurrentEntity->ext.armorLord.fadeOutY < 0x68) {
            g_CurrentEntity->ext.armorLord.fadeOutY += 2;
        } else if (g_Timer % 4 == 0) {
            g_CurrentEntity->ext.armorLord.fadeOutZ -= 1;
            if (g_CurrentEntity->ext.armorLord.fadeOutZ == 0x19) {
                g_CurrentEntity->step_s++;
            }
        }
        if (g_CurrentEntity->ext.armorLord.timer3 == 2) {
            g_CurrentEntity->ext.armorLord.fadeOutY += 8;
        }
        if (!g_CurrentEntity->ext.armorLord.fadeOutZ) {
            primIndex = g_CurrentEntity->primIndex;
            g_api.FreePrimitives(primIndex);
            primIndex = g_api.AllocPrimitives(PRIM_TILE, 0x14);
            if (primIndex != -1) {
                g_CurrentEntity->primIndex = primIndex;
                prim = &g_PrimBuf[primIndex];
                g_CurrentEntity->ext.armorLord.prim = prim;
                while (prim != NULL) {
                    prim->x0 = (posX + (Random() & 3)) - 2;
                    prim->y0 = posY - 0x48 + (Random() & 0x3F);
                    prim->u0 = 1;
                    prim->v0 = 1;
                    prim->r0 = 0xE0;
                    prim->b0 = 0x88;
                    prim->g0 = 0xA0;
                    prim->p2 = (Random() & 7) + 1;
                    prim->priority = g_CurrentEntity->zPriority + 1;
                    prim->drawMode =
                        DRAW_TPAGE2 | DRAW_TPAGE | DRAW_UNK02 | DRAW_TRANSP;
                    prim = prim->next;
                }
            }
            g_CurrentEntity->ext.armorLord.timer3 = 0;
            g_CurrentEntity->ext.armorLord.timer2 = 0;
            g_CurrentEntity->step_s++;
        }
    }
    return 0;
}

void EntityArmorLord(Entity* self) {
    Entity* player;
    u32 tempSide;
    Entity* tempEntity;
    s16 xDistance;
    s32 posX;
    s32 primIndex;

    if ((self->flags & FLAG_DEAD) && (self->step < AL_DIE)) {
        tempEntity = self + 1;
        DestroyEntity(tempEntity);
        PlaySfxPositional(SFX_ARMOR_LORD_DEATH);
        if (self->flags & FLAG_HAS_PRIMS) {
            primIndex = self->primIndex;
            g_api.FreePrimitives(primIndex);
            self->flags &= ~FLAG_HAS_PRIMS;
        }
        self->flags &= ~FLAG_UNK_20000000;
        self->zPriority -= 4;
        self->hitboxState = 0;
#ifdef STAGE_IS_NO1
        hasBeenKilled = true;
#endif
        SetStep(AL_DIE);
    }
    switch (self->step) {
    case AL_INIT:
#ifdef STAGE_IS_NO1
        if (hasBeenKilled != false) {
            DestroyEntity(self);
            return;
        }
#endif
        InitializeEntity(g_EInitArmorLord);
        tempEntity = self + 1;
        CreateEntityFromEntity(E_ARMOR_LORD_SWORD_SHADOW, self, tempEntity);
        self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
        break;
    // Probably something about spawning in and making sure it's on solid
    // ground?
    case AL_1:
        if (UnkCollisionFunc3(sensors1) & 1) {
            SetStep(AL_WAIT_PLAYER_CLOSE);
        }
        break;
    case AL_WAIT_PLAYER_CLOSE:
#ifdef GUARDIAN
        if (GetDistanceToPlayerX() < 0xC0) {
#else
        if (GetDistanceToPlayerX() < 0xA0) {
#endif
            SetStep(AL_WALK);
        }
        break;
    case AL_WALK:
        if (!self->step_s) {
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
            self->ext.armorLord.facingLeft = self->facingLeft;
            self->ext.armorLord.timer = attackTimers[Random() & 3];
            self->step_s++;
        }
        if (!AnimateEntity(anim_walk_cycle, self)) {
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
        }
        UnkCollisionFunc2(sensors2);
        if (self->ext.armorLord.facingLeft) {
            self->velocityX = FIX(0.25);
        } else {
            self->velocityX = FIX(-0.25);
        }
        xDistance = GetDistanceToPlayerX();
#ifdef GUARDIAN
        if (xDistance < 0x40) {
#else
        if (xDistance < 0x50) {
#endif
            self->ext.armorLord.facingLeft = self->facingLeft ^ 1;
        }
        if (xDistance > 0x70) {
            self->ext.armorLord.facingLeft = self->facingLeft;
        }
#ifdef GUARDIAN
        tempSide = (GetSideToPlayer() & 1) ^ 1;
        if ((self->facingLeft == tempSide) &&
            g_Player.status & (PLAYER_STATUS_SPELLCAST | PLAYER_STATUS_SUBWPN |
                               PLAYER_STATUS_UNK400)) {
            if (!self->ext.armorLord.didShield) {
                self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
                SetStep(AL_SHIELD);
            }
            self->ext.armorLord.didShield = true;
        } else {
            self->ext.armorLord.didShield = false;
        }
#endif
        if (!--self->ext.armorLord.timer) {
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
            SetStep(randomSteps[Random() & 7]);
#ifdef GUARDIAN
            player = &PLAYER;
            if (g_Player.status & PLAYER_STATUS_BAT_FORM) {
                SetStep(AL_SWORD_HIGH);
            }
            if (g_Player.status & PLAYER_STATUS_UNK2000) {
                SetStep(AL_FIREWAVE_ATTACK);
            }
            if (g_Player.status & PLAYER_STATUS_CROUCH) {
                SetStep(AL_FIREWAVE_ATTACK);
            }
            if (g_Player.status & PLAYER_STATUS_UNK400) {
                SetStep(AL_FIREBALLS);
            }
        }
        break;
#else
        }
#endif
        // Guardian has a `break` statement so never touches this!
        if (g_Player.status & PLAYER_STATUS_UNK400) {
            if (!self->ext.armorLord.didShield && (Random() & 1)) {
                self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
                SetStep(AL_SHIELD);
            }
            self->ext.armorLord.didShield = true;
        } else {
            self->ext.armorLord.didShield = false;
        }
        break;

    case AL_FIREBALLS:
        switch (self->step_s) {
        case 0:
            if (!AnimateEntity(anim_charge_fireball, self)) {
                self->pose = 0;
                self->poseTimer = 0;
                self->step_s++;
                self->ext.armorLord.timer = 0x80;
            }
            break;

        case 1:
            AnimateEntity(anim_fireball, self);
            if (!--self->ext.armorLord.timer) {
                self->pose = 0;
                self->poseTimer = 0;
                self->step_s++;
            }
            if (self->ext.armorLord.timer % 7 == 0) {
                PlaySfxPositional(SFX_WEAPON_SWISH_A);
            }
            break;

        case 2:
            if (!AnimateEntity(anim_end_fireball, self)) {
                SetStep(AL_WALK);
            }
            break;
        }
        break;
    // Attack where he swings his head in an arc high over his head
    case AL_SWORD_HIGH:
        if (!self->step_s) {
            self->velocityX = 0;
            self->velocityY = 0;
            self->step_s++;
        }
        if (!self->poseTimer && self->animCurFrame == 0x14) {
            PlaySfxPositional(SFX_WHIP_TWIRL_SWISH);
            PlaySfxPositional(SFX_ARMOR_LORD_ATTACK);
            g_api.func_80102CD8(4);
        }
        // This is the part where he slides sideways as the swing happens
        if (!self->poseTimer && self->pose == 5) {
            if (self->facingLeft) {
                self->velocityX = FIX(4.0);
            } else {
                self->velocityX = FIX(-4.0);
            }
        }
        UnkCollisionFunc2(sensors2);
        self->velocityX -= self->velocityX / 8;
        if (!AnimateEntity(anim_overhead_slice, self)) {
            SetStep(AL_WALK);
        }
        break;

    case AL_FIREWAVE_ATTACK:
        if (self->pose > 5 && !self->step_s) {
            PlaySfxPositional(SFX_FIREBALL_SHOT_A);
            PlaySfxPositional(SFX_ARMOR_LORD_FIRE_ATTACK);
            tempEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (tempEntity != NULL) {
                CreateEntityFromEntity(
                    E_ARMOR_LORD_FIRE_WAVE, self, tempEntity);
                tempEntity->facingLeft = self->facingLeft;
                tempEntity->pfnUpdate = EntityArmorLordFireWave;
                tempEntity->step = 0;
            }
            self->step_s++;
        }
        if (!AnimateEntity(anim_launch_flametrail, self)) {
            SetStep(AL_WALK);
        }
        break;

    case AL_SHIELD:
        if (!AnimateEntity(anim_create_shield, self)) {
            self->hitboxState = 3;
            self->step_s = 3;
        }
        if (self->pose > 1) {
            ArmorLordShieldHelper();
            if ((self->flags & FLAG_HAS_PRIMS) == 0) {
                SetStep(AL_WALK);
            }
        }
        break;

    case AL_DIE:
        if (!AnimateEntity(anim_death, self)) {
            SetStep(AL_FADEAWAY);
        }
        if (g_Timer % 8 == 0) {
            PlaySfxPositional(SFX_EXPLODE_FAST_B);
            tempEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (tempEntity != NULL) {
                CreateEntityFromEntity(E_INTENSE_EXPLOSION, self, tempEntity);
                tempEntity->posX.i.hi += (Random() & 0x1F) - 0x10;
                tempEntity->posY.i.hi += (Random() & 0x3F) - 0x10;
            }
        }
        break;

    case AL_FADEAWAY:
        if (FadeArmorLordDeath()) {
            DestroyEntity(self);
            return;
        }
        break;
    }
    self->hitboxHeight = 0x1C;
    self->hitboxOffX = 0;
    self->hitboxOffY = 0xC;
    switch (self->animCurFrame) {
    case 5:
    case 16:
    case 17:
    case 29:
        self->hitboxOffX = 0x10;
        break;
    case 12:
    case 13:
    case 21:
    case 25:
        self->hitboxOffX = -2;
        self->hitboxHeight = 0x1A;
        break;
    case 4:
    case 6:
    case 7:
    case 30:
        self->hitboxOffX = 7;
        break;
    }

#ifdef STAGE_IS_NO1
    posX = g_Tilemap.scrollX.i.hi + self->posX.i.hi;
    if (posX > 0x90) {
        self->posX.i.hi = 0x90 - g_Tilemap.scrollX.i.hi;
    }
#endif
}

// Faint blue effect when Armor Lord swings his sword.
// Animframe 0x20 is a horizontal slice, 0x21 is vertical
void EntityArmorLordSwordShadow(Entity* self) {
    Entity* parent;
    u8 animCurFrame;

    parent = self - 1;

    self->facingLeft = parent->facingLeft;
    self->posX.i.hi = parent->posX.i.hi;
    self->posY.i.hi = parent->posY.i.hi;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitArmorLordSwordShadow);
        self->blendMode |= BLEND_TRANSP | BLEND_ADD;
        self->drawFlags |= ENTITY_OPACITY;
        self->animCurFrame = 0;
        break;
    case 1:
        if (parent->animCurFrame == 0x10 && parent->step == 6) {
            self->step = 2;
            self->animCurFrame = 0x20;
            self->opacity = 0x60;
            self->drawFlags = ENTITY_OPACITY | ENTITY_SCALEY | ENTITY_SCALEX;
            self->scaleX = 0x1C8;
            self->scaleY = 0x1C8;
        }
        if (parent->animCurFrame == 0x15) {
            self->step = 3;
            self->animCurFrame = 0x21;
            self->opacity = 0x60;
            self->drawFlags = ENTITY_OPACITY | ENTITY_SCALEY | ENTITY_SCALEX;
            self->scaleX = 0x1B8;
            self->scaleY = 0x1B8;
        }
        self->ext.armorLord.timer = 3;
        break;
    case 2:
        if (!--self->ext.armorLord.timer) {
            self->animCurFrame = 0;
        } else {
            self->opacity -= 0x20;
        }
        if (parent->animCurFrame != 0x10) {
            self->step = 1;
        }
        break;
    case 3:
        if (!--self->ext.armorLord.timer) {
            self->animCurFrame = 0;
        } else {
            self->opacity -= 0x20;
        }
        if (parent->animCurFrame != 0x15) {
            self->step = 1;
        }
        break;
    }

    animCurFrame = parent->animCurFrame;
    if (animCurFrame == 0x1E) {
        self->hitboxState = 3;
    } else {
        self->hitboxState = 1;
    }

    if (animCurFrame < 5 || animCurFrame > 30) {
        animCurFrame = 0;
    } else {
        animCurFrame -= 4;
    }

    self->hitboxOffX = hitboxOffXYs[animCurFrame][0];
    self->hitboxOffY = hitboxOffXYs[animCurFrame][1];
    self->hitboxWidth = hitboxWidthHeights[animCurFrame][0];
    self->hitboxHeight = hitboxWidthHeights[animCurFrame][1];

    if (parent->entityId != E_ARMOR_LORD) {
        DestroyEntity(self);
    }
}

// Another wave attack helper
void EntityArmorLordUnk2(Entity* self) {
    Primitive* prim;
    s32 height;
    s32 offsetY;

    if (!self->step) {
        height = self->hitboxHeight;
        offsetY = self->hitboxOffY;
        InitializeEntity(g_EInitArmorLordTemp);
        self->hitboxWidth = 8;
        self->hitboxOffX = 8;
        self->hitboxHeight = height;
        self->hitboxOffY = offsetY;
    }

    if (self->step++ > 5) {
        prim = self->ext.armorLord.prim;
        prim->next->v2 = 0;
        DestroyEntity(self);
    }
}
