REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
#include "sfx.h"
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
extern u16 g_EAxeKnightInit[];
static s16 sensors_move[] = {0, 32, 8, 0};
static s16 sensors_ground[4][2] = {{0, 32}, {0, 4}, {8, -4}, {-16, 0}};
static s16 dead_particle_pos[][2] = {
    {-8, -4}, {8, -6}, {-2, 4}, {-1, -7}, {2, 8}, {11, -7}, {4, 6}, {-3, 0}};
static u16 unused[] = {
    0x0114, 0x020A, 0x030A, 0x0414, 0x030A, 0x020A, 0x0000, 0x0000, 0x0508,
    0x0608, 0x0708, 0x0D08, 0x0E08, 0x0F02, 0x1402, 0x1502, 0x1620, 0x1708,
    0x0000, 0x0000, 0x0508, 0x0608, 0x0708, 0x0808, 0x090A, 0x0A04, 0x0B04,
    0x0C04, 0x0000, 0x0000, 0x0E04, 0x0F04, 0x1004, 0x1104, 0x0000, 0x0000,
    0x0D08, 0x0E08, 0x0F01, 0x1001, 0x1101, 0x1220, 0x1308, 0x0000};
static u8 anim_walk[] = {0x1A, 0x18, 0x0A, 0x19, 0x0A, 0x1A, 0x1A,
                         0x1B, 0x0A, 0x1A, 0x0A, 0x19, 0x00};
static u8 anim_throw_duck[] = {
    0x08, 0x1C, 0x08, 0x1D, 0x08, 0x1E, 0x08, 0x1F, 0x0A, 0x20, 0x04, 0x21,
    0x04, 0x22, 0x04, 0x23, 0x00, 0x00, 0x00, 0x00, 0x08, 0x24, 0x08, 0x25,
    0x02, 0x26, 0x02, 0x27, 0x02, 0x28, 0x20, 0x29, 0x08, 0x2A, 0x00};
static u8 anim_throw_stand[] = {
    0x08, 0x1C, 0x08, 0x1D, 0x08, 0x1E, 0x08, 0x24, 0x08, 0x25, 0x02,
    0x26, 0x02, 0x2B, 0x02, 0x2C, 0x20, 0x2D, 0x08, 0x2E, 0x00, 0x00,
    0x00, 0x00, 0x04, 0x25, 0x04, 0x26, 0x04, 0x27, 0x04, 0x28, 0x00};
static u8 anim_die[] = {
    0x08, 0x20, 0x08, 0x21, 0x08, 0x22, 0x08, 0x23, 0xFF, 0x00};
static u8 hitboxes[][4] = {
    {0, 0, 0, 0},
    {0, 6, 8, 26},
    {0, 11, 8, 21},
    {0, 12, 8, 20},
};
static u8 hitbox_lookup[] = {
    0, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 1, 1, 1, 1, 1, 3, 1, 1, 1, 3, 1,
    1, 1, 1, 1, 1, 1, 1, 3, 3, 3, 3, 3, 1, 1, 1, 1, 1, 3, 1, 1, 1, 3, 1, 0};
static u8 steps[] = {AXE_KNIGHT_STANDING_THROW, AXE_KNIGHT_DUCKING_THROW,
                     AXE_KNIGHT_STANDING_THROW, AXE_KNIGHT_DUCKING_THROW,
                     AXE_KNIGHT_STANDING_THROW, AXE_KNIGHT_DUCKING_THROW,
                     AXE_KNIGHT_STANDING_THROW, AXE_KNIGHT_DUCKING_THROW};
static u32 init_velocity_x[] = {FIX(2), FIX(2), FIX(1)};
static u32 init_velocity_y[] = {FIX(0), FIX(0), FIX(-4)};

// Weirdly, this function ONLY acts on prim->next, it does not act on prim.
// However, it does call functions on prim.
void func_801C3F9C(AxePrim* prim) {
REDACTED
    Entity* newEnt;
    s16 yVar;
REDACTED
    UnkPrimHelper((Primitive*)prim);
    switch (prim->next->step) {
REDACTED
        prim->next->unk0C = 0;
        prim->next->unk10 = -0x10000;
        prim->next->step = 1;
        prim->next->timer = 0x100;
        return;
REDACTED
        yVar = prim->next->y0 + (prim->next->unk1E / 3);
        g_api.CheckCollision(prim->next->x1, yVar, &collider, 0);
        if (collider.effects & EFFECT_SOLID) {
            prim->next->y0 += collider.unk18;
            if (prim->next->unk10 < 0x4000) {
                prim->next->timer = 1;
REDACTED
            prim->next->unk10 = -prim->next->unk10;
            prim->next->unk10 -= prim->next->unk10 / 2;
REDACTED
        prim->next->unk10 += 0x1800;
        prim->next->timer--;
        if (prim->next->timer == 0) {
            newEnt = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (newEnt != NULL) {
                CreateEntityFromCurrentEntity(E_EXPLOSION, newEnt);
                newEnt->posX.i.hi = prim->next->x1;
                newEnt->posY.i.hi = prim->next->y0;
                newEnt->params = 0;
REDACTED
            PlaySfxPositional(SFX_EXPLODE_B);
            UnkPolyFunc0((Primitive*)prim);
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
extern s16* sprites_nz0_3[];
s32 func_801C4198(Entity* axeKnight) {
    Primitive* prim;
    s32 primIndex;
    s16 uCoord;
    s16 vCoord;
    u16 UV_thing;
    u8 flag;
    s16* dataPtr;
    s16 clutBase;

    switch (axeKnight->step_s) {
    case 0:
        clutBase = g_EAxeKnightInit[3];
        dataPtr = sprites_nz0_3[axeKnight->animCurFrame];
        primIndex = g_api.AllocPrimitives(PRIM_GT4, *dataPtr * 2);
        if (primIndex != -1) {
            axeKnight->flags |= FLAG_HAS_PRIMS;
            axeKnight->primIndex = primIndex;
            prim = &g_PrimBuf[primIndex];
            axeKnight->ext.axeknight.prim = prim;
            dataPtr++;
            while (prim != NULL) {
                UnkPolyFunc2(prim);
                dataPtr++;
                prim->next->x1 = axeKnight->posX.i.hi;
                if (axeKnight->facingLeft) {
                    prim->next->x1 -= *dataPtr++;
                } else {
                    prim->next->x1 += *dataPtr++;
                }
                prim->next->y0 = axeKnight->posY.i.hi + *dataPtr++;
                LOH(prim->next->r2) = *dataPtr++;
                if (axeKnight->facingLeft) {
                    prim->next->x1 -= LOH(prim->next->r2) / 2;
                } else {
                    prim->next->x1 += LOH(prim->next->r2) / 2;
                }
                LOH(prim->next->b2) = *dataPtr++;
                prim->next->y0 += LOH(prim->next->b2) / 2;
                prim->clut = clutBase + *dataPtr++;
                if (axeKnight->params) {
                    prim->clut += 2;
                }
                UV_thing = axeKnight->unk5A;
                UV_thing += *dataPtr++;
                prim->tpage = 0x12;         // Leftover line, shows up in PSP
                prim->tpage = UV_thing / 4; // Masks off the lower two bits
                uCoord = (UV_thing & 1);
                uCoord = uCoord * 0x7F;
                vCoord = ((UV_thing & 2) >> 1);
                vCoord = vCoord * 0x7F;
                // uCoord and vCoord are each either 0 or 7F.
                if (axeKnight->facingLeft) {
                    prim->u1 = prim->u3 = uCoord + *dataPtr++;
                    prim->v0 = prim->v1 = vCoord + *dataPtr++;
                    prim->u0 = prim->u2 = uCoord + *dataPtr++;
                    prim->v2 = prim->v3 = vCoord + *dataPtr++;
                } else {
                    prim->u0 = prim->u2 = uCoord + *dataPtr++;
                    prim->v0 = prim->v1 = vCoord + *dataPtr++;
                    prim->u1 = prim->u3 = uCoord + *dataPtr++;
                    prim->v2 = prim->v3 = vCoord + *dataPtr++;
                }
                prim->priority = axeKnight->zPriority + 2;
                prim->drawMode = DRAW_UNK02;
                prim = prim->next;
                prim = prim->next;
            }
        } else {
            return 1;
        }
        PlaySfxPositional(SFX_FM_EXPLODE_B);
        axeKnight->step_s++;
        break;
    case 1:
        flag = 0;
        for (prim = axeKnight->ext.axeknight.prim; prim != NULL;) {
            if (prim->p3 & 8) {
                func_801C3F9C(prim);
                flag = 1;
            }
            prim = prim->next;
            prim = prim->next;
        }
        if (!flag) {
            return 1;
        }
        break;
    }
    return 0;
}
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
        SetStep(steps[(Random() & 7)]);
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
    if (self->flags & FLAG_DEAD) {
REDACTED
            PlaySfxPositional(NA_SE_VO_AXE_KNIGHT_SCREAM);
            AxeKnightDeath();
            self->hitboxState = 0;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
        InitializeEntity(g_EAxeKnightInit);
        self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
        self->hitboxOffY = 10;
REDACTED
REDACTED
REDACTED
REDACTED
        if (UnkCollisionFunc3(sensors_ground) & 1) {
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
            if (self->facingLeft == 0) {
                self->velocityX = FIX(-0.1875);
REDACTED
                self->velocityX = FIX(0.1875);
REDACTED
REDACTED
REDACTED
REDACTED
        animStatus = AnimateEntity(anim_walk, self);
REDACTED
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
REDACTED
REDACTED
REDACTED
            if (self->facingLeft == 0) {
                self->velocityX = FIX(-0.1875);
REDACTED
                self->velocityX = FIX(0.1875);
REDACTED
            if (GetDistanceToPlayerX() < 96) {
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
            if (self->facingLeft == 0) {
                self->velocityX -= 0x300;
REDACTED
                self->velocityX += 0x300;
REDACTED
        } else if (self->facingLeft != 0) {
            self->velocityX -= 0x300;
REDACTED
            self->velocityX += 0x300;
REDACTED
REDACTED
        if (UnkCollisionFunc2(sensors_move) & 0x60) {
            self->posX.val -= self->velocityX;
            self->velocityX = 0;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
            if (self->facingLeft == 0) {
                self->velocityX = FIX(0.1875);
REDACTED
                self->velocityX = FIX(-0.1875);
REDACTED
REDACTED
REDACTED
REDACTED
        animStatus = AnimateEntity(anim_walk, self);
REDACTED
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
REDACTED
REDACTED
            if (self->facingLeft == 0) {
                self->velocityX = FIX(0.1875);
REDACTED
                self->velocityX = FIX(-0.1875);
REDACTED
REDACTED
            if (GetDistanceToPlayerX() > 80) {
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
            if (self->facingLeft == 0) {
                self->velocityX += 0x200;
REDACTED
                self->velocityX -= 0x200;
REDACTED
        } else if (self->facingLeft != 0) {
            self->velocityX += 0x200;
REDACTED
            self->velocityX -= 0x200;
REDACTED
REDACTED
        if (UnkCollisionFunc2(sensors_move) & 0x60) {
            self->posX.val -= self->velocityX;
            self->velocityX = 0;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
        animStatus = AnimateEntity(anim_throw_stand, self);
REDACTED
REDACTED
            if (GetDistanceToPlayerX() < 89) {
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
            PlaySfxPositional(NA_SE_VO_AXE_KNIGHT_THROW);
            newEntity = AllocEntity(g_Entities + 160, g_Entities + 192);
REDACTED
REDACTED
                newEntity->facingLeft = self->facingLeft;
REDACTED
                if (newEntity->facingLeft != 0) {
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
        animStatus = AnimateEntity(anim_throw_duck, self);
REDACTED
REDACTED
                PlaySfxPositional(NA_SE_VO_AXE_KNIGHT_THROW);
                newEntity = AllocEntity(g_Entities + 160, g_Entities + 192);
REDACTED
REDACTED
                    newEntity->facingLeft = self->facingLeft;
REDACTED
REDACTED
                    if (newEntity->facingLeft != 0) {
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
        animStatus = AnimateEntity(anim_throw_stand, self);
REDACTED
            if (GetDistanceToPlayerX() > 88) {
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
            PlaySfxPositional(NA_SE_VO_AXE_KNIGHT_THROW);
            newEntity = AllocEntity(g_Entities + 160, g_Entities + 192);
REDACTED
REDACTED
                newEntity->facingLeft = self->facingLeft;
REDACTED
REDACTED
                if (newEntity->facingLeft != 0) {
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
                newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
REDACTED
                    CreateEntityFromEntity(E_EXPLOSION, self, newEntity);
REDACTED
REDACTED
                    newEntity->posX.i.hi += dead_particle_pos[temp][0];
                    newEntity->posY.i.hi += dead_particle_pos[temp][1];
REDACTED
REDACTED
REDACTED
REDACTED
        if (AnimateEntity(anim_die, self) == 0) {
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
    hitbox = hitboxes;
    hitbox += hitbox_lookup[self->animCurFrame] * 4;
    self->hitboxOffX = *hitbox++;
    self->hitboxOffY = *hitbox++;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
        g_CurrentEntity->rotZ += 0x80;
REDACTED
        g_CurrentEntity->rotZ -= 0x80;
REDACTED
REDACTED
    g_CurrentEntity->rotZ &= 0xFFF;
REDACTED
REDACTED
void EntityAxeKnightThrowingAxe(Entity* entity) {
    s32 velocityX;
REDACTED
    if (entity->flags & FLAG_DEAD) {
        PlaySfxPositional(SFX_WEAPON_BREAK);
        EntityExplosionSpawn(0, 0);
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
        entity->drawFlags = FLAG_DRAW_ROTZ;
        entity->velocityY = init_velocity_y[entity->params];
        velocityX = init_velocity_x[entity->params];
REDACTED
        if (entity->facingLeft == 0) {
            entity->velocityX = -velocityX;
REDACTED
            entity->velocityX = velocityX;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
            if (entity->facingLeft != 0) {
                entity->velocityX -= FIX(0.125);
REDACTED
                entity->velocityX += FIX(0.125);
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
        entity->velocityY += FIX(0.125);
REDACTED
REDACTED
REDACTED
REDACTED
