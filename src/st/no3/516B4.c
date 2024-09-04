#include "no3.h"
#include "../e_merman2.h"

// ID 0x35
void EntitySplashWater(Entity* self) {
    Tilemap* tilemap = &g_Tilemap;
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
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
        InitializeEntity(g_eInitGeneric2);
REDACTED
REDACTED
REDACTED
            primIndex = g_api.AllocPrimitives(PRIM_GT4, 2);
REDACTED
REDACTED
REDACTED
            prim = &g_PrimBuf[primIndex];
            self->primIndex = primIndex;
REDACTED
REDACTED
            self->ext.waterEffects.unk82 = temp_t3 + tilemap->scrollY.i.hi;
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
REDACTED
REDACTED
REDACTED
                prim->drawMode = 0x77;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
                    prim->drawMode = 0x37;
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
REDACTED
REDACTED
            g_api.PlaySfxVolPan(D_801813A8, 0x7F, temp_a2);
            self->velocityY = D_80183878[params].x;
            self->ext.waterEffects.accelY = D_80183878[params].y;
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
        self->velocityY += self->ext.waterEffects.accelY;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
        if (g_PrimBuf[self->primIndex].r0 < 9) {
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
    temp_t3 -= tilemap->scrollY.i.hi;
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
REDACTED
    Tilemap* tilemap = &g_Tilemap;
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
REDACTED
REDACTED
        InitializeEntity(g_eInitGeneric2);
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
REDACTED
REDACTED
REDACTED
            g_api.PlaySfxVolPan(D_801813AA, 0x7F, var_s2);
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
        self->ext.waterEffects.unk82 = self->posY.i.hi + g_Tilemap.scrollY.i.hi;
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
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
            prim->drawMode = 0x77;
REDACTED
REDACTED
REDACTED
                prim->drawMode = 0x77;
            }
            prim = prim->next;
        }
        rnd = (rand() & 1) + 12;
        self->ext.waterEffects.topY.i.hi = D_80183898[(u8)self->params] + rnd;
        self->velocityX = self->ext.waterEffects.unk8A * 16;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
        self->ext.waterEffects.topY.val -= FIX(0.25);
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
            x = right - tilemap->scrollX.i.hi;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
            temp3 = tilemap->scrollX.i.hi + 6;
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
REDACTED
    bottom = tempv0 - y - tilemap->scrollY.i.hi;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
        prim->y0 = prim->y2 - self->ext.waterEffects.topY.i.hi;
        prim->y1 = prim->y3 - self->ext.waterEffects.topY.i.hi;
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
    self->ext.waterEffects.unk82 = self->posY.i.hi + tilemap->scrollY.i.hi;
REDACTED

REDACTED
REDACTED
    Primitive* prim;
    s16 primIndex;
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
        InitializeEntity(g_eInitGeneric2);
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 1);
        if (primIndex != -1) {
            prim = &g_PrimBuf[primIndex];
            self->primIndex = primIndex;
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
                prim->drawMode = 0x37;
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
REDACTED
REDACTED
            self->ext.waterEffects.accelY = FIX(22.0 / 128);
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
        self->velocityY += self->ext.waterEffects.accelY;
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
        InitializeEntity(g_eInitGeneric2);
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
REDACTED
REDACTED
REDACTED
            prim->drawMode = 0x33;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
        self->ext.waterEffects.accelY = FIX(0.25);
        break;

    case 1:
        MoveEntity(self);
        self->velocityY += self->ext.waterEffects.accelY;
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
REDACTED
REDACTED
REDACTED

REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
    s16 primIndex;
REDACTED
REDACTED
REDACTED
        InitializeEntity(g_eInitGeneric2);
        primIndex = g_api.func_800EDB58(PRIM_TILE_ALT, 0x21);
        if (primIndex == -1) {
REDACTED
REDACTED
REDACTED
REDACTED
        self->primIndex = primIndex;
REDACTED
REDACTED
REDACTED
REDACTED
            prim->drawMode = 0x73;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
                prim->drawMode &= ~DRAW_HIDE;
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
REDACTED
REDACTED
REDACTED
REDACTED
                prim->drawMode &= ~DRAW_HIDE;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
                prim->drawMode |= DRAW_HIDE;
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
    res = expectedResult == (collider.effects & EFFECT_SOLID);

    if (collider.effects & EFFECT_WATER) {
        if (!g_CurrentEntity->ext.merman.isUnderwater) {
            newEntity = AllocEntity(g_Entities + 232, g_Entities + 256);
REDACTED
                CreateEntityFromEntity(
                    E_MERMAN_UNK0, g_CurrentEntity, newEntity);
REDACTED
REDACTED
REDACTED
            g_api.PlaySfx(SE_WATER_SPLASH);
            g_CurrentEntity->ext.merman.isUnderwater = true;
        }
    }
    return res;
}

extern u16 D_80180B48[];
extern s16 D_801813AC[];     // pos TBL
extern Point32 D_80183914[]; // accel_x TBL
extern s32 D_80183938;       // Collision data
extern u8 D_80183984[];      // Animation
extern u8 D_8018398C[];      // Animation
extern u8 D_80183934[];      // timers
extern s32 D_80183948;       // Collision data
extern u16 D_80183958;       // Collision data
extern u8 D_80183960[];      // Animation
extern u8 D_8018396C[];      // Animation

void EntityMerman2(Entity* self) {
    s32 primIndex;
    Collider collider;
    Entity* newEntity;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
    u32 colorOffset;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
    if ((self->flags & FLAG_DEAD) && (self->step < MERMAN2_DYING)) {
        PlaySfxPositional(0x71D);
        self->drawFlags = 0;
        if (self->flags & FLAG_HAS_PRIMS) {
            g_api.FreePrimitives(self->primIndex);
            self->flags &= ~FLAG_HAS_PRIMS;
REDACTED
        self->hitboxState = 0;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
        InitializeEntity(D_80180B48);
        self->hitboxOffY = 8;
REDACTED
REDACTED
REDACTED
REDACTED
        self->velocityY = FIX(-1);
REDACTED
REDACTED
REDACTED
        AnimateEntity(D_8018398C, self);
REDACTED
REDACTED
REDACTED
        if (!(collider.effects & EFFECT_WATER)) {
REDACTED
REDACTED
        break;
REDACTED
REDACTED
REDACTED
REDACTED
            self->velocityX = D_80183914[rnd].x;
            self->velocityY = D_80183914[rnd].y;
            self->step_s++;
        }
        if (AnimateEntity(D_8018398C, self) == 0) {
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
        if (!(collider.effects & EFFECT_WATER)) {
            self->velocityY = FIX(0.5);
REDACTED
        pos = D_801813AC;
REDACTED
        posY += g_Tilemap.scrollY.i.hi;
REDACTED
            self->posY.i.hi = pos[4] - g_Tilemap.scrollY.i.hi - 24;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
            if ((GetDistanceToPlayerX() >= 48) && !(Random() & 1)) {
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
            self->velocityX = 0;
            self->velocityY = FIX(-8.5);
REDACTED
            primIndex = g_api.AllocPrimitives(PRIM_GT4, 1);
            if (primIndex != -1) {
REDACTED
                prim = &g_PrimBuf[primIndex];
REDACTED
                self->primIndex = primIndex;
REDACTED
                self->flags |= FLAG_HAS_PRIMS;
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
REDACTED
                if (self->facingLeft != 0) {
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
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
                prim->drawMode = 6;
            } else {
                self->animCurFrame = 17;
                DestroyEntity(self);
            }
REDACTED
REDACTED
REDACTED
REDACTED
            pos = D_801813AC;
REDACTED
REDACTED
REDACTED
            camY = g_Tilemap.scrollY.i.hi + posY;
REDACTED
REDACTED
                newEntity = AllocEntity(&g_Entities[232], &g_Entities[256]);
                if (newEntity != NULL) {
                    CreateEntityFromEntity(E_MERMAN_UNK0, self, newEntity);
REDACTED
REDACTED
REDACTED
                self->rotZ = 0;
                self->drawFlags |= 4;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
            if (self->velocityY > ~0xBFFF) {
                prim->drawMode = DRAW_HIDE;
REDACTED
REDACTED
                self->rotZ -= 0x80;
REDACTED
                if (self->facingLeft != 0) {
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
REDACTED
REDACTED
REDACTED
REDACTED
                colorOffset =
                    (u32)(((__builtin_abs(self->velocityY) >> 0xC) - 10) &
                          0xFF) >>
                    1;
REDACTED
                setRGB0(prim, 128 - colorOffset, 128 - colorOffset,
                        colorOffset + 192);
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
            if (self->velocityY < 0) {
                newEntity = AllocEntity(&g_Entities[232], &g_Entities[256]);
                if (newEntity != NULL) {
                    CreateEntityFromEntity(E_MERMAN2_UNK0, self, newEntity);
REDACTED
REDACTED
REDACTED
REDACTED
            if (self->velocityY > 0) {
                func_801D2D40(0x1B);
            }
            if (self->ext.merman2.isUnderwater == 0) {
                if (UnkCollisionFunc3(&D_80183938) & 1) {
                    g_api.FreePrimitives(self->primIndex);
REDACTED
                    self->flags &= ~FLAG_HAS_PRIMS;
                    self->drawFlags &= 0xFB;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
                self->velocityY += FIX(0.25);
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
            if (AnimateEntity(D_80183984, self) == 0) {
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
            self->ext.merman2.timer = D_80183934[Random() & 3];
REDACTED
REDACTED
REDACTED
REDACTED
            AnimateEntity(D_80183960, self);
            colRes = UnkCollisionFunc2(&D_80183958);
REDACTED
                self->facingLeft ^= 1;
REDACTED
            if (self->facingLeft == 0) {
                self->velocityX = FIX(-0.375);
REDACTED
                self->velocityX = FIX(0.375);
REDACTED
REDACTED
REDACTED
                self->posX.val += self->velocityX;
REDACTED
REDACTED
REDACTED
                (self->velocityX *= 2, !(self->params & 1))) {
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
                    if (func_801D2D40(0x1B)) {
                        self->ext.merman2.ignoreCol = 1;
                    }
                }
            } else {
                if (func_801D2D40(0x1B)) {
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
REDACTED
            break;

        case MERMAN2_SPIT_FIRE_ATTACK:
            if (AnimateEntity(D_8018396C, self) == 0) {
                PlaySfxPositional(SFX_FIREBALL_SHOT_C);
REDACTED
                i = 0;
                if (newEntity != NULL) {
                    CreateEntityFromEntity(E_MERMAN2_UNK1, self, newEntity);
REDACTED
                    newEntity->facingLeft = self->facingLeft;
REDACTED
                newEntity2 = g_Entities + 224;
REDACTED
                    newEntity = AllocEntity(newEntity2, newEntity2 + 32);
REDACTED
                        CreateEntityFromEntity(E_MERMAN2_UNK2, self, newEntity);
                        if (self->facingLeft != 0) {
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
                        newEntity->facingLeft = self->facingLeft;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
                self->rotZ = 0;
                self->drawFlags |= 4;
                if (self->facingLeft != 0) {
                    self->velocityX = FIX(-6);
REDACTED
                    self->velocityX = FIX(6);
REDACTED
                self->velocityY = FIX(-0.0625);
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
            if ((self->ext.merman2.rotation < 0x100) && (g_Timer & 1)) {
REDACTED
REDACTED
            if (self->velocityX != 0) {
                if (self->facingLeft != 0) {
                    self->velocityX += FIX(0.1875);
REDACTED
                    self->velocityX -= FIX(0.1875);
REDACTED
REDACTED
REDACTED
REDACTED
            if (self->facingLeft != 0) {
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
            if (collider.effects & EFFECT_SOLID) {
                self->velocityX = 0;
REDACTED
            self->rotZ += self->ext.merman2.rotation;
            self->velocityY -= FIX(0.125);
REDACTED
            if (UnkCollisionFunc3(&D_80183938) & 1) {
                if (self->facingLeft == 0) {
                    self->velocityX = FIX(2.5);
                } else {
                    self->velocityX = FIX(-5.0 / 2.0);
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
            func_801D2D40(0x1B);
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
            if (self->facingLeft != 0) {
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
            if (collider.effects & EFFECT_SOLID) {
                self->velocityX = 0;
REDACTED
REDACTED
            self->rotZ += 0xC0;
            if (self->rotZ > 0x1000) {
REDACTED
                self->drawFlags &= 0xFB;
REDACTED
REDACTED
            if (func_801D2D40(0x1B)) {
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
        MoveEntity();
        self->velocityY += FIX(0.25);
        if (!(func_801D2D40(0x1B)) && !(self->ext.merman2.isUnderwater)) {
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
            if (!(GetSideToPlayer() & 1)) {
                self->velocityX = FIX(-2);
REDACTED
                self->velocityX = FIX(2);
REDACTED
            self->velocityY = FIX(-1);
REDACTED
            primIndex = g_api.AllocPrimitives(PRIM_GT4, 2);
            if (primIndex != -1) {
REDACTED
                prim = &g_PrimBuf[primIndex];
                self->primIndex = primIndex;
REDACTED
REDACTED
                UnkPolyFunc2(prim);
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
                if (self->facingLeft != 0) {
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
REDACTED
REDACTED
REDACTED
                prim->drawMode = 2;
REDACTED
REDACTED
REDACTED
                if (self->facingLeft != 0) {
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
            UnkPrimHelper(prim);
REDACTED
REDACTED
REDACTED
            UnkCollisionFunc3(&D_80183948);
REDACTED
            self->velocityY -= FIX(0.1875);
            if (self->facingLeft != 0) {
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
            UnkPrimHelper(prim);
            if (!(g_Timer % 10)) {
REDACTED
REDACTED
                    prim->drawMode = DRAW_HIDE;
REDACTED
REDACTED
REDACTED
REDACTED
                        CreateEntityFromEntity(E_MERMAN2_UNK3, self, newEntity);
                        newEntity->facingLeft = self->facingLeft;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
            func_801D2D40(0x1B);
            break;

        case 2:
            PlaySfxPositional(SFX_FM_EXPLODE_B);
            func_801C13F8();
            DestroyEntity(self);
        }
        break;
    }
}

REDACTED
REDACTED
    Primitive* prim;
    s16 primIndex;
REDACTED
REDACTED
REDACTED
REDACTED
        entity->hitboxState = 0;
        entity->zPriority += 4;
REDACTED
            primIndex = g_api.AllocPrimitives(PRIM_GT4, 2);
            if (primIndex == -1) {
                DestroyEntity(entity);
                return;
            }
            prim = &g_PrimBuf[primIndex];
            entity->primIndex = primIndex;
            *(s32*)&entity->ext.generic.unk7C.s = prim;
            entity->flags |= FLAG_HAS_PRIMS;
            UnkPolyFunc2(prim);
            prim->u0 = 0;
            prim->u1 = 0x20;
            prim->tpage = 0x1A;
            prim->clut = 0x1FF;
            prim->v3 = prim->v2 = 0x20;
            prim->v1 = prim->v0 = 0;
            prim->u2 = prim->u0;
            prim->u3 = prim->u1;
            LOH(prim->next->r2) = 0x40;
            LOH(prim->next->b2) = 0x40;
            LOH(prim->next->u1) = 0;
            prim->next->b3 = 0x60;
            prim->next->x1 = (u16)entity->posX.i.hi;
            prim->next->y0 = (u16)entity->posY.i.hi;
            prim->priority = entity->zPriority - 4;
            prim->drawMode = 6;
        }
    }

    if (entity->params != 0) {
        prim = *(s32*)&entity->ext.generic.unk7C.s;
        UnkPrimHelper(prim);
        prim->next->b3 += 252;
        LOH(prim->next->u1) -= 128;
        if (prim->next->b3 < 16) {
            prim->drawMode = 8;
        }
    }

REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED

// medium sized water splash used with merman
void EntityMediumWaterSplash(Entity* entity) {
REDACTED
REDACTED
    if (entity->step == 0) {
        InitializeEntity(D_80180B54);
        entity->animCurFrame = 0;
        if (entity->facingLeft != 0) {
            entity->velocityX = FIX(2);
            return;
        }
        entity->velocityX = FIX(-2);
        return;
    }
    AnimateEntity(D_80183994, entity);
    MoveEntity();
    if (entity->flags & FLAG_DEAD) {
        newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
REDACTED
REDACTED
REDACTED
        }
        DestroyEntity(entity);
    }
}

// spawns EntityMediumWaterSplash, part of merman splash
REDACTED
REDACTED
REDACTED
    Primitive* prim;
    s16 primIndex;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
        InitializeEntity(g_EInitGeneric);
REDACTED
REDACTED
REDACTED
REDACTED
        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }
REDACTED
        self->primIndex = primIndex;
REDACTED
        self->flags |= FLAG_HAS_PRIMS;
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
REDACTED
REDACTED
REDACTED
REDACTED
            prim->drawMode = 0x33;
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
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
                    prim->drawMode |= 8;
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
        self->hitboxState = 0;
        self->flags |= 0x2000;
        self->zPriority += 4;
    }
    MoveEntity();
    self->velocityY += FIX(0.15625);
    if (AnimateEntity(D_801839A8, self) == 0) {
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
        InitializeEntity(g_InitializeEntityData0);
        self->animSet = ANIMSET_DRA(2);
        self->velocityY = FIX(-5);
        self->palette = 0x8162;
        self->drawMode = DRAW_TPAGE;
        self->palette = 0x8018;
        self->drawMode = 0x30;
        self->unk6C = 0xA0;
        self->rotX = 0x100;
        self->rotY = 0x1A0;
        self->drawFlags |= 3;
REDACTED
REDACTED
        self->drawFlags |= 8;
        break;

    case 1:
REDACTED
REDACTED
REDACTED
        if (!(temp & 0xFF)) {
            self->step++;
        }
        break;

    case 2:
        AnimateEntity(D_801839B0, self);
        MoveEntity();
        self->velocityY += FIX(0.25);
        self->rotX += 6;
        self->rotY -= 4;
        if (self->posY.i.hi > 256) {
            DestroyEntity(self);
        }
REDACTED
            self->velocityY = 0;
            self->step++;
        }
        break;

    case 3:
        if (AnimateEntity(D_801839B0, self) == 0) {
            MoveEntity();
            self->velocityY += FIX(0.25);
            self->rotX += 6;
            self->rotY -= 4;
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
        InitializeEntity(D_80180B48);
        self->animCurFrame = 13;
REDACTED
        self->hitboxState = 0;
        self->velocityY = FIX(0.0625);
REDACTED
        self->unk6C = 0x80;
        self->drawFlags |= 8;
        self->flags |= 0x2000;
        return;
    }
    MoveEntity();
REDACTED
REDACTED
    self->velocityY += FIX(0.0625);
    self->unk6C += 0xFE;
    if (temp_v0 == 0) {
        DestroyEntity(self);
    }
}

REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
        InitializeEntity(D_80180AD0);
        self->flags |= FLAG_UNK_2000;
REDACTED
REDACTED
    if (!(g_Timer & 0x3F)) {
REDACTED
        temp = g_Tilemap.scrollY.i.hi + player->posY.i.hi;
REDACTED
            temp_s0 = g_Tilemap.scrollX.i.hi + player->posX.i.hi;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
                newEntity = AllocEntity(&g_Entities[160], &g_Entities[170]);
REDACTED
REDACTED
                        CreateEntityFromCurrentEntity(E_ID_3A, newEntity);
                        newEntity->params = Random() & 1;
                    } else {
                        CreateEntityFromCurrentEntity(E_ID_41, newEntity);
REDACTED
                    newEntity->posX.i.hi = temp_s0_2 - g_Tilemap.scrollX.i.hi;
                    newEntity->posY.i.hi = temp2 - g_Tilemap.scrollY.i.hi;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
