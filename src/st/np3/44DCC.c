REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
#include "sfx.h"
#include "../e_merman2.h"
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
            g_api.PlaySfxVolPan(D_8018122C, 0x7F, temp_a2);
REDACTED
            self->ext.waterEffects.accelY = D_80182188[params].y;
REDACTED
REDACTED
REDACTED
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
            g_api.PlaySfxVolPan(D_8018122E, 0x7F, var_s2);
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
REDACTED
REDACTED
REDACTED
REDACTED
        self->ext.waterEffects.topY.i.hi = D_801821A8[(u8)self->params] + rnd;
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
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
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
    Collider collider;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
    if (expectedResult == (collider.effects & EFFECT_SOLID)) {
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
    if (collider.effects & EFFECT_WATER) {
REDACTED
            newEntity = AllocEntity(g_Entities + 232, g_Entities + 256);
REDACTED
                CreateEntityFromEntity(
                    E_MERMAN_UNK0, g_CurrentEntity, newEntity);
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
    s32 primIndex;
REDACTED
REDACTED
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
REDACTED
        self->hitboxOffY = 8;
REDACTED
REDACTED
REDACTED
REDACTED
        self->velocityY = FIX(-1);
REDACTED
REDACTED
REDACTED
REDACTED
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
            self->velocityX = D_80182224[rnd].x;
            self->velocityY = D_80182224[rnd].y;
REDACTED
REDACTED
REDACTED
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
REDACTED
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
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
            camY = g_Tilemap.scrollY.i.hi + posY;
REDACTED
REDACTED
                newEntity = AllocEntity(g_Entities + 232, g_Entities + 256);
REDACTED
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
                    (u32)(((abs(self->velocityY) >> 0xC) - 10) & 0xFF) >> 1;
REDACTED
                setRGB0(prim, 128 - colorOffset, 128 - colorOffset,
                        colorOffset + 192);
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
            if (self->velocityY < 0) {
                newEntity = AllocEntity(g_Entities + 232, g_Entities + 256);
REDACTED
                    CreateEntityFromEntity(E_MERMAN2_UNK0, self, newEntity);
REDACTED
REDACTED
REDACTED
REDACTED
            if (self->velocityY > 0) {
REDACTED
REDACTED
REDACTED
                if (UnkCollisionFunc3(&D_80182248) & 1) {
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
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
            colRes = UnkCollisionFunc2(&D_80182268);
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
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
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
REDACTED
REDACTED
REDACTED
                PlaySfxPositional(SFX_FIREBALL_SHOT_C);
                newEntity = AllocEntity(g_Entities + 160, g_Entities + 192);
REDACTED
REDACTED
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
            if (UnkCollisionFunc3(&D_80182248) & 1) {
                if (self->facingLeft == 0) {
                    self->velocityX = FIX(2.5);
REDACTED
                    self->velocityX = FIX(-5.0 / 2.0);
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
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
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
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
            UnkCollisionFunc3(&D_80182258);
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
REDACTED
REDACTED
REDACTED
REDACTED
            PlaySfxPositional(SFX_FM_EXPLODE_B);
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
    Primitive* prim;
    s16 primIndex;
REDACTED
REDACTED
REDACTED
REDACTED
        entity->hitboxState = 0;
REDACTED
REDACTED
            primIndex = g_api.AllocPrimitives(PRIM_GT4, 2);
            if (primIndex == -1) {
REDACTED
REDACTED
REDACTED
REDACTED
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
            prim->next->x1 = entity->posX.i.hi;
            prim->next->y0 = entity->posY.i.hi;
            prim->priority = entity->zPriority - 4;
            prim->drawMode = 6;
REDACTED
REDACTED
REDACTED
REDACTED
        prim = *(s32*)&entity->ext.generic.unk7C.s;
        UnkPrimHelper(prim);
        prim->next->b3 += 252;
        LOH(prim->next->u1) -= 128;
        if (prim->next->b3 < 16) {
            prim->drawMode = DRAW_HIDE;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
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
            entity->velocityX = FIX(2);
REDACTED
REDACTED
        entity->velocityX = FIX(-2);
REDACTED
REDACTED
REDACTED
REDACTED
    if (entity->flags & FLAG_DEAD) {
        newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
REDACTED
            CreateEntityFromEntity(E_EXPLOSION, entity, newEntity);
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
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
REDACTED
REDACTED
REDACTED
REDACTED
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
        self->hitboxState = 0;
        self->flags |= FLAG_UNK_2000;
REDACTED
REDACTED
REDACTED
    self->velocityY += FIX(0.15625);
    if (AnimateEntity(D_801822B8, self) == 0) {
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
REDACTED
        self->drawMode = DRAW_TPAGE;
REDACTED
        self->drawMode = 0x30;
REDACTED
        self->rotX = 0x100;
        self->rotY = 0x1A0;
        self->drawFlags |= 3;
REDACTED
REDACTED
        self->drawFlags |= 8;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
        AnimateEntity(D_801822C0, self);
REDACTED
        self->velocityY += FIX(0.25);
        self->rotX += 6;
        self->rotY -= 4;
REDACTED
REDACTED
REDACTED
REDACTED
            self->velocityY = 0;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
        if (AnimateEntity(D_801822C0, self) == 0) {
REDACTED
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
REDACTED
REDACTED
        self->hitboxState = 0;
        self->velocityY = FIX(0.0625);
REDACTED
REDACTED
        self->drawFlags |= 8;
        self->flags |= FLAG_UNK_2000;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
    self->velocityY += FIX(0.0625);
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
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
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
                    newEntity->posX.i.hi = temp_s0_2 - g_Tilemap.scrollX.i.hi;
                    newEntity->posY.i.hi = temp2 - g_Tilemap.scrollY.i.hi;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
