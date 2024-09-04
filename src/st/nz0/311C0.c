#include "nz0.h"

// bust with red eyes that can have a candle on it
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
        if (g_pads[1].pressed & PAD_SQUARE) {
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
        if (g_pads[1].pressed & PAD_CIRCLE) {
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED

// A purplish-red brick background that scrolls behind the foreground layer
void EntityPurpleBrickScrollingBackground(Entity* self) {
    Primitive* prim;
    s32 primIndex;
    s32 tempPosX;
    s32 tempPosY;
    s32 x, y;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitGeneric);
        self->posX.i.hi = 0;
        self->posY.i.hi = 0;
        self->unk68 = 0x80;
        // Composed of 15 primitives
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 15);
        if (primIndex == -1) {
REDACTED
REDACTED
REDACTED
        prim = &g_PrimBuf[primIndex];
        self->primIndex = primIndex;
        self->ext.prim = prim;
        self->flags |= FLAG_HAS_PRIMS;
        while (prim != NULL) {
            prim->tpage = 0xF;
            prim->clut = 4;
            prim->u0 = prim->u2 = 0x80;
            prim->u1 = prim->u3 = 0xFF;
            prim->v0 = prim->v1 = 0x80;
            prim->v2 = prim->v3 = 0xBF;
            prim->priority = 0x20;
            prim->drawMode = DRAW_UNK02;
            prim = prim->next;
        }

    case 1:
        // Add a scrolling effect
        tempPosX = self->posX.i.hi;
        tempPosX = tempPosX & 0x7F;
        tempPosX = tempPosX - 0x80;
        tempPosY = self->posY.i.hi;
        tempPosY = (tempPosY & 0x3F) - 0x40;
        prim = self->ext.prim;
        // Primitives are laid out in a 5-tall by 3-wide grid
        for (y = 0; y < 5; y++) {
            for (x = 0; x < 3; x++) {
                prim->x0 = prim->x2 = tempPosX + (x * 0x80);
                prim->x1 = prim->x3 = prim->x0 + 0x80;
                prim->y0 = prim->y1 = tempPosY + (y * 0x40);
                prim->y2 = prim->y3 = prim->y0 + 0x40;
                prim->drawMode = DRAW_DEFAULT;
                prim = prim->next;
            }
        }

        while (prim != NULL) {
            prim->drawMode = DRAW_HIDE;
            prim = prim->next;
        }
    }
}

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
        self->hitboxState = 2;
REDACTED
        cond = g_CastleFlags[129] != 0;
REDACTED
REDACTED
REDACTED
REDACTED
            g_Tilemap.fg[tilePos] = *tileLayoutPtr;
            g_Tilemap.fg[tilePos + 1] = *(tileLayoutPtr + 1);
REDACTED
REDACTED
REDACTED
REDACTED
        if (g_CastleFlags[129] != 0) {
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
        if (self->hitFlags != 0) {
            PlaySfxPositional(SFX_WALL_DEBRIS_B);
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
        self->ext.nz0311c0.unk84++;
        tileLayoutPtr = &D_80180E54 + (self->ext.nz0311c0.unk84 * 4);

REDACTED
REDACTED
            g_Tilemap.fg[tilePos] = *tileLayoutPtr;
            g_Tilemap.fg[tilePos + 1] = *(tileLayoutPtr + 1);
REDACTED
REDACTED
REDACTED
REDACTED
        newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
REDACTED
            CreateEntityFromEntity(E_EXPLOSION, self, newEntity);
REDACTED
REDACTED
        self->ext.nz0311c0.unk80 = 32;
        self->step++;

        if (self->ext.nz0311c0.unk84 == 3) {
            g_CastleFlags[129] = 1;
REDACTED
REDACTED
REDACTED
                newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
REDACTED
                    CreateEntityFromEntity(E_WALL_DEBRIS, self, newEntity);
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
        if (--self->ext.nz0311c0.unk80 == 0) {
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
void EntityBottomSecretRoomFloor(
    Entity* self, u16* tileLayoutPtr, s32 tilePos) {
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
        InitializeEntity(g_EInitGeneric);
REDACTED
REDACTED
        self->hitboxState = 2;
        flag = (g_CastleFlags[130] != 0);
REDACTED
REDACTED
REDACTED
REDACTED
            g_Tilemap.fg[tilePos] = *tileLayoutPtr;
            g_Tilemap.fg[tilePos + 1] = *(tileLayoutPtr + 1);
REDACTED
REDACTED
REDACTED
REDACTED
        if (g_CastleFlags[130] != 0) {
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
        if (self->hitFlags != 0) {
            PlaySfxPositional(SFX_WALL_DEBRIS_B);
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
        self->ext.nz0311c0.unk84++;
        tileLayoutPtr = &D_80180E94 + (self->ext.nz0311c0.unk84 * 2);
REDACTED
REDACTED
REDACTED
            g_Tilemap.fg[tilePos] = *tileLayoutPtr;
            g_Tilemap.fg[tilePos + 1] = *(tileLayoutPtr + 1);
REDACTED
REDACTED
REDACTED
REDACTED
        newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
REDACTED
            CreateEntityFromEntity(E_EXPLOSION, self, newEntity);
REDACTED
REDACTED
        self->ext.nz0311c0.unk80 = 32;
        self->step++;

        if (self->ext.nz0311c0.unk84 == 3) {
            g_CastleFlags[130] = 1;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
        if (--self->ext.nz0311c0.unk80 == 0) {
            self->step = BOTTOM_SECRET_ROOM_FLOOR_IDLE;
        }
        break;
    }
}

// Debris produced when left wall is destroyed
void EntitySecretWallDebris(Entity* self) {
    Collider collider;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
        self->drawFlags = FLAG_DRAW_ROTZ;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
        self->velocityX = rnd * rcos(rnd2);
        self->velocityY = rnd * rsin(rnd2);
        if (self->velocityX < 0) {
            self->facingLeft = 1;
REDACTED
REDACTED
REDACTED
REDACTED
        self->rotZ += 0x20;
REDACTED
            self->rotZ += 0x20;
REDACTED
REDACTED
        self->velocityY += FIX(0.125);
        g_api.CheckCollision(
            self->posX.i.hi, self->posY.i.hi + 6, &collider, 0);
        if (collider.effects & EFFECT_SOLID) {
            self->posY.i.hi += collider.unk18;
REDACTED
                PlaySfxPositional(SFX_WALL_DEBRIS_B);
REDACTED
REDACTED
REDACTED
                        CreateEntityFromEntity(E_WALL_DEBRIS, self, newEntity);
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
            if (self->velocityY < FIX(0.5)) {
                newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
REDACTED
                    CreateEntityFromEntity(
                        E_INTENSE_EXPLOSION, self, newEntity);
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
            self->velocityY = -self->velocityY;
            self->velocityY *= 2;
            self->velocityY /= 3;
REDACTED
REDACTED
REDACTED

void BoxPuzzleFloorButton(Entity* self) {
    s32 temp_s1 = GetPlayerCollisionWith(self, 8, 8, 4);
    s16 primIndex;
    Primitive* prim;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
        InitializeEntity(g_EInitGeneric);
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 1);
        if (primIndex == -1) {
REDACTED
REDACTED
REDACTED
        prim = &g_PrimBuf[primIndex];
        self->primIndex = primIndex;
        self->ext.prim = prim;
        self->flags |= FLAG_HAS_PRIMS;
        prim->type = PRIM_SPRT;
        prim->tpage = 0xF;
        prim->clut = 9;
        prim->u0 = 72;
        prim->v0 = 200;
        prim->u1 = 16;
        prim->v1 = 16;
        prim->priority = 0x5F;
        prim->drawMode = DRAW_UNK02;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
            self->posY.val += FIX(1.0);
            temp = g_Tilemap.scrollY.i.hi + self->posY.i.hi;
REDACTED
                self->posY.i.hi = 468 - g_Tilemap.scrollY.i.hi;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
        self->posY.val -= FIX(1);
        temp = g_Tilemap.scrollY.i.hi + self->posY.i.hi;
REDACTED
            self->posY.i.hi = 464 - g_Tilemap.scrollY.i.hi;
REDACTED
REDACTED
REDACTED
REDACTED
    prim = self->ext.prim;
    prim->x0 = self->posX.i.hi - 8;
    prim->y0 = self->posY.i.hi - 8;
}

// Spikes which go up and down when pressing the buttons
void BoxPuzzleSpikes(Entity* self, s16 primIndex) {
    Primitive* prim;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
        InitializeEntity(g_EInitGeneric);
REDACTED
REDACTED
        self->attackElement = 1;
        self->attack = 7;
        self->hitboxState = 1;
REDACTED
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 1);
        if (primIndex == -1) {
REDACTED
REDACTED
REDACTED
        prim = &g_PrimBuf[primIndex];
        self->primIndex = primIndex;
        self->ext.prim = prim;
        self->flags |= FLAG_HAS_PRIMS;
        prim->type = PRIM_SPRT;
        prim->tpage = 0xF;
        prim->clut = 9;
        prim->u0 = 40;
        prim->v0 = 200;
        prim->u1 = 32;
        prim->v1 = 32;
        prim->priority = 0x5F;
        prim->drawMode = DRAW_UNK02;
REDACTED
REDACTED
            self->posY.i.hi = 480 - g_Tilemap.scrollY.i.hi;
            self->ext.nz0311c0.unk88 = 1;
        } else {
            self->posY.i.hi = 452 - g_Tilemap.scrollY.i.hi;
            self->ext.nz0311c0.unk88 = 0;
REDACTED
REDACTED
REDACTED
REDACTED
            self->posY.val += FIX(1.0);
            temp = g_Tilemap.scrollY.i.hi + self->posY.i.hi;
REDACTED
                self->posY.i.hi = 480 - g_Tilemap.scrollY.i.hi;
REDACTED
REDACTED
REDACTED
            self->posY.val -= FIX(1);
            temp = g_Tilemap.scrollY.i.hi + self->posY.i.hi;
REDACTED
                self->posY.i.hi = 452 - g_Tilemap.scrollY.i.hi;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
        if (self->ext.nz0311c0.unk88 != var_v1) {
            self->ext.nz0311c0.unk88 = var_v1;
            PlaySfxPositional(0x69D);
        }
    }

    prim = self->ext.prim;
    prim->x0 = self->posX.i.hi - 16;
    prim->y0 = self->posY.i.hi - 16;
    temp = 480 - (g_Tilemap.scrollY.i.hi + self->posY.i.hi);
REDACTED
REDACTED

// moveable box for spike/switch areas
REDACTED
REDACTED
    Primitive* prim;
    s32 temp_s1 = GetPlayerCollisionWith(self, 0x10, 0x10, 5);
REDACTED
    s16 primIndex;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
        InitializeEntity(g_EInitGeneric);
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 1);
        if (primIndex == -1) {
REDACTED
REDACTED
REDACTED
        prim = &g_PrimBuf[primIndex];
        self->primIndex = primIndex;
        self->ext.prim = prim;
        self->flags |= FLAG_HAS_PRIMS;
REDACTED
REDACTED
REDACTED
REDACTED
        prim->v0 = 200;
        prim->u1 = 32;
        prim->v1 = 32;
        prim->priority = 112;
        prim->drawMode = DRAW_UNK02;
REDACTED
REDACTED
REDACTED
        self->velocityX = 0;
        self->velocityY = 0;
REDACTED
REDACTED
            temp_s1 = GetSideToPlayer();
            if (temp_s1 & 1 && player->velocityX > 0) {
                if (!(g_Timer & 7)) {
                    g_api.PlaySfx(SFX_STONE_MOVE_B);
REDACTED
                self->velocityX = FIX(0.5);
REDACTED
            temp_s1 = GetSideToPlayer();
            if (!(primIndex = (temp_s1 & 1)) && (player->velocityX < 0)) {
                if (!(g_Timer & 7)) {
                    g_api.PlaySfx(SFX_STONE_MOVE_B);
REDACTED
                self->velocityX = FIX(-0.5);
REDACTED
REDACTED
REDACTED
        UnkCollisionFunc2(&D_80180EB8);
REDACTED
REDACTED
            temp_v0_2 = self->posX.i.hi + g_Tilemap.scrollX.i.hi;
            if (abs(temp_v0_2 - 192) < 24) {
                var_s1 = 1;
            } else {
                var_s1 = 0;
            }
            if (abs(temp_v0_2 - 256) < 24) {
REDACTED
REDACTED
            if ((self->ext.nz0311c0.unk84 == 0) &&
REDACTED
REDACTED
                self->posX.val -= self->velocityX;
REDACTED
            self->ext.nz0311c0.unk84 = var_s1;
REDACTED
REDACTED
                    (448 - D_801CB736[var_s1]) - g_Tilemap.scrollY.i.hi;
REDACTED
REDACTED
REDACTED
REDACTED
    prim = self->ext.prim;
    new_var = ((u16)self->posX.i.hi) - 16;
    prim->x0 = new_var;
    prim->y0 = ((u16)self->posY.i.hi) - 16;
REDACTED

// lever to operate cannon
REDACTED
    Primitive* prim;
    s16 primIndex;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
        InitializeEntity(g_EInitGeneric);
REDACTED
REDACTED
        self->hitboxState = 2;
REDACTED
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 1);
        if (primIndex == -1) {
REDACTED
REDACTED
REDACTED
        prim = &g_PrimBuf[primIndex];
        self->primIndex = primIndex;
        self->ext.prim = prim;

        self->flags |= FLAG_HAS_PRIMS;
        prim->type = PRIM_SPRT;
        prim->tpage = 0xF;
        prim->clut = 9;
        prim->u0 = 0x68;
        prim->v0 = 0x80;
        prim->u1 = 8;
        prim->v1 = 0x28;
        prim->priority = 0x70;
        prim->drawMode = DRAW_UNK02;
REDACTED
REDACTED
            self->hitboxState = 0;
REDACTED
REDACTED
REDACTED
REDACTED
        if (self->hitFlags != 0) {
            self->velocityX = FIX(-4);
REDACTED
REDACTED
        break;
REDACTED
REDACTED
REDACTED
        temp_v1_2 = self->velocityX;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
        self->velocityX = temp_v0_2;
REDACTED
REDACTED
REDACTED
        break;
REDACTED
REDACTED
        D_80180ED0[0] = 1;
REDACTED
REDACTED
REDACTED
    if (D_8003BE6F[0] != 0) {
        self->hitboxState = 0;
REDACTED
    prim = self->ext.prim;
    prim->x0 = self->posX.i.hi - 4;
    prim->y0 = self->posY.i.hi - 20;
REDACTED

// cannon for shortcut
REDACTED
    s16 primIndex;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
        InitializeEntity(g_EInitGeneric);
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 2);
        if (primIndex == -1) {
REDACTED
REDACTED
REDACTED
REDACTED
        self->primIndex = primIndex;
        prim = &g_PrimBuf[primIndex];
        self->ext.prim = prim;
        self->flags |= FLAG_HAS_PRIMS;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
        prim->drawMode = DRAW_UNK02;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
        prim->y0 = 120 - g_Tilemap.scrollY.i.hi;
REDACTED
        prim->drawMode = DRAW_UNK02;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
            self->velocityX = FIX(8);
REDACTED
REDACTED
                CreateEntityFromEntity(E_EXPLOSION, self, newEntity);
REDACTED
REDACTED
            CreateEntityFromEntity(E_CANNON_SHOT, self, &self[1]);
            self->step++;
        }
        break;

    case 2:
        prim = self->ext.prim;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
        temp = self->velocityX;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
        self->velocityX = temp - (var_v0 >> 3);
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
    prim = self->ext.prim;
REDACTED
REDACTED
REDACTED

// projectile shot by cannon
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
        InitializeEntity(g_EInitGeneric);
        self->animSet = ANIMSET_DRA(2);
REDACTED
REDACTED
REDACTED
        self->velocityX = FIX(-8);
REDACTED
REDACTED
REDACTED
        if ((self->posX.i.hi + g_Tilemap.scrollX.i.hi) < 112) {
REDACTED
REDACTED
REDACTED
                CreateEntityFromEntity(E_EXPLOSION, self, newEntity);
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
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
        cond = g_CastleFlags[131] != 0;
REDACTED
REDACTED
            g_Tilemap.fg[tilePos] = *tileLayoutPtr;
REDACTED
REDACTED
REDACTED
        if (g_CastleFlags[131] != 0) {
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
        i = g_CastleFlags[131] != 0; // TODO: !FAKE:
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
        g_api.PlaySfx(SFX_WALL_DEBRIS_B);
REDACTED
REDACTED
REDACTED
            g_Tilemap.fg[tilePos] = *tileLayoutPtr;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED

// Floor button which you kill the blood skeleton to lift the small elevator
void EntityBloodSkeleElevButton(Entity* self) {
    Primitive* prim;
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
        self->hitboxState = 1;
        CreateEntityFromEntity(E_BLOOD_SKELETON, self, &self[-1]);
        self[-1].posY.i.hi = 344 - g_Tilemap.scrollY.i.hi;
REDACTED
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 1);
        if (primIndex == -1) {
REDACTED
REDACTED
REDACTED
        prim = &g_PrimBuf[primIndex];
        self->primIndex = primIndex;
        self->ext.prim = prim;
        self->flags |= FLAG_HAS_PRIMS;
        prim->tpage = 0xF;
        prim->clut = 9;
        prim->u0 = 72;
        prim->v0 = 200;
        prim->u1 = 16;
        prim->v1 = 16;
        prim->priority = 0x5F;
        prim->type = PRIM_SPRT;
        prim->drawMode = DRAW_UNK02;
REDACTED
REDACTED
        var_a0 = self->hitFlags;
REDACTED
        if (abs(self->posX.i.hi - self[-1].posX.i.hi) < 8) {
REDACTED
REDACTED
REDACTED
        if (var_a0) {
            self->posY.val += FIX(1.0);
            temp = g_Tilemap.scrollY.i.hi + self->posY.i.hi;
REDACTED
                self->posY.i.hi = 376 - g_Tilemap.scrollY.i.hi;
REDACTED
REDACTED
REDACTED
            self->posY.val -= FIX(1);
            temp = g_Tilemap.scrollY.i.hi + self->posY.i.hi;
REDACTED
                self->posY.i.hi = 372 - g_Tilemap.scrollY.i.hi;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
        prim = self->ext.prim;
        prim->x0 = self->posX.i.hi - 8;
        prim->y0 = self->posY.i.hi - 8;
REDACTED
REDACTED

REDACTED
    s32 temp = GetPlayerCollisionWith(self, 16, 5, 4);
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
REDACTED
        if (primIndex == -1) {
REDACTED
REDACTED
REDACTED
        prim = &g_PrimBuf[primIndex];
        self->primIndex = primIndex;
        self->ext.prim = prim;
        self->flags |= FLAG_HAS_PRIMS;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
        prim->drawMode = DRAW_UNK02;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
            prim->drawMode = DRAW_UNK02;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
            camY = g_Tilemap.scrollY.i.hi;
REDACTED
REDACTED
REDACTED
REDACTED
                D_80097488.y.i.hi--;
REDACTED
REDACTED
REDACTED
            camY = g_Tilemap.scrollY.i.hi;
REDACTED
REDACTED
REDACTED
REDACTED
                D_80097488.y.i.hi++;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED

// First floor button encountered
void EntityFloorButton(Entity* self) {
    s32 temp = GetPlayerCollisionWith(self, 8, 8, 4);
    Primitive* prim;
    Entity* player;
    s16 primIndex;
    s32 posX, posY;
    s32 camY;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitGeneric);
        self->ext.nz0311c0.unk80 = self->posY.i.hi + g_Tilemap.scrollY.i.hi;
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 1);
        if (primIndex == -1) {
REDACTED
REDACTED
REDACTED
        prim = &g_PrimBuf[primIndex];
        self->primIndex = primIndex;
        self->ext.prim = prim;
        self->flags |= FLAG_HAS_PRIMS;
REDACTED
REDACTED
REDACTED
        prim->u0 = 72;
        prim->v0 = 200;
        prim->v1 = prim->u1 = 0x10;
        prim->priority = 0x5F;
        prim->drawMode = DRAW_UNK02;

        posX = self->posX.i.hi;
        posX += g_Tilemap.scrollX.i.hi;
        posX >>= 4;

        // TODO: !FAKE
        camY = self->posY.i.hi;
        posY = camY += 4;
        posY = camY += g_Tilemap.scrollY.i.hi;

        camY = (camY >> 4) * g_Tilemap.hSize * 16;
        g_Tilemap.fg[posX + camY] = 0x5AF;

    case 1:
        if (temp != 0) {
REDACTED
REDACTED
            self->posY.val += FIX(1.0);
            posY = g_Tilemap.scrollY.i.hi + self->posY.i.hi;
            if ((self->ext.nz0311c0.unk80 + 4) < posY) {
                self->posY.i.hi =
                    (self->ext.nz0311c0.unk80 + 4) - g_Tilemap.scrollY.i.hi;
                self[1].ext.stub[0xC] = 1;
                self->step++;
                LOW(self[1].ext.stub[0x8]) ^= 1;
            }
        }

    default:
        prim = self->ext.prim;
        prim->x0 = self->posX.i.hi - 8;
        prim->y0 = self->posY.i.hi - 8;
        break;

    case 2:
        if (temp == 0) {
            self->posY.val -= FIX(1);
            posY = g_Tilemap.scrollY.i.hi + self->posY.i.hi;
            if (posY < self->ext.nz0311c0.unk80) {
                self->posY.i.hi =
                    self->ext.nz0311c0.unk80 - g_Tilemap.scrollY.i.hi;
                self->step = 1;
            }
        }
        prim = self->ext.prim;
        prim->x0 = self->posX.i.hi - 8;
        prim->y0 = self->posY.i.hi - 8;
        break;
    }
}

REDACTED
REDACTED
    s16 primIndex;
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
        self->attackElement = 1;
        self->attack = 7;
        self->hitboxState = 1;
        self->ext.nz0311c0.unk80 = self->posY.i.hi + g_Tilemap.scrollY.i.hi;
REDACTED
REDACTED
REDACTED
        new_var += g_Tilemap.scrollY.i.hi;
        tilePos = ((self->posX.i.hi - temp + g_Tilemap.scrollX.i.hi) >> 4) +
                  (((new_var >> 4) * g_Tilemap.hSize) * 16);
REDACTED
        g_Tilemap.fg[tilePos] = 0x102;
        g_Tilemap.fg[tilePos + 1] = 0x103;
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 1);
        if (primIndex == -1) {
REDACTED
REDACTED
REDACTED
        prim = &g_PrimBuf[primIndex];
        self->primIndex = primIndex;
        self->ext.prim = prim;
        self->flags |= FLAG_HAS_PRIMS;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
        prim->drawMode = DRAW_UNK02;
        self->posY.i.hi -= 28;

    case 1:
        self->hitboxState = 1;
        if (self->ext.nz0311c0.unk84 != 0) {
            self->posY.val += FIX(1.0);
            new_var = g_Tilemap.scrollY.i.hi + self->posY.i.hi;
            var_v1 = g_Tilemap.scrollY.i.hi;
            if (new_var > self->ext.nz0311c0.unk80) {
                self->hitboxState = 0;
                self->posY.i.hi = self->ext.nz0311c0.unk80 - var_v1;
            }
        } else {
            self->posY.val -= FIX(1);
            new_var = g_Tilemap.scrollY.i.hi + self->posY.i.hi;
            var_v1 = g_Tilemap.scrollY.i.hi;
            if (new_var < (self->ext.nz0311c0.unk80 - 28)) {
                self->posY.i.hi = self->ext.nz0311c0.unk80 - 28 - var_v1;
            }
        }
    }
    if (self->ext.nz0311c0.unk88 != 0) {
        PlaySfxPositional(0x69D);
        self->ext.nz0311c0.unk88 = 0;
    }
    prim = self->ext.prim;
REDACTED
REDACTED
REDACTED

// table with globe on it that can be broken
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
        self->hitboxOffY = -0xA;
        self->hitboxOffX = 0;
        self->hitboxState = 2;
REDACTED
REDACTED
REDACTED
        if (self->hitFlags != 0) {
            PlaySfxPositional(SFX_GLASS_BREAK_E);
            self->hitboxState = 0;
            CreateEntityFromEntity(E_HEART_DROP, self, &self[1]);
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED

// Tank (and decoration) at bottom of secret floor room. When broken,
// provides a Life Max Up
void EntityLifeMaxTank(Entity* self) {
REDACTED

REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
        self->hitboxOffY = -0xA;
        self->hitboxOffX = 0;
        self->hitboxState = 2;
REDACTED
REDACTED
REDACTED
        if (self->hitFlags) {
            PlaySfxPositional(SFX_GLASS_BREAK_A);
            self->hitboxState = 0;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
        if (AnimateEntity(D_80180F30, self) == 0) {
            CreateEntityFromEntity(E_HEART_DROP, self, &self[1]);
REDACTED
REDACTED
REDACTED
                CreateEntityFromEntity(E_EXPLOSION, self, newEntity);
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
// Breakable container holding Skill of Wolf, Bat Card, maybe others
void EntityRelicContainer(Entity* self) {
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
            self->drawMode = 0x30;
REDACTED
REDACTED
REDACTED
REDACTED
            self->hitboxOffY = -0xA;
            self->hitboxOffX = 0;
            self->hitboxState = 2;
            CreateEntityFromEntity(E_RELIC_CONTAINER, self, self + 1);
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
        if (self->hitFlags != 0) {
            self->hitboxState = 0;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
            CreateEntityFromEntity(E_RELIC_ORB, self, self + 1);
        } else {
            CreateEntityFromEntity(E_HEART_DROP, self, self + 1);
        }

        (self + 1)->params = D_80180F9C[self->params];
REDACTED
REDACTED
        newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
REDACTED
            CreateEntityFromEntity(E_EXPLOSION, self, newEntity);
REDACTED
REDACTED
REDACTED
        PlaySfxPositional(SFX_GLASS_BREAK_E);
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
        if (g_pads[1].pressed & PAD_SQUARE) {
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
        if (g_pads[1].pressed & PAD_CIRCLE) {
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED

// Table in room with bone-throwing skeleton. Drops a Resist Thunder.
void EntityBlueFlameTable(Entity* self) {
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
        self->hitboxOffY = -0xA;
        self->hitboxOffX = 0;
        self->hitboxState = 2;
REDACTED
REDACTED
REDACTED
        if (self->hitFlags != 0) {
            g_api.PlaySfx(SFX_CANDLE_HIT);
            self->hitboxState = 0;
REDACTED
REDACTED
REDACTED

REDACTED
        CreateEntityFromEntity(E_HEART_DROP, self, &self[1]);
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
void AxeKnightDeath() {
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
            CreateEntityFromEntity(E_WARG_EXP_OPAQUE, g_CurrentEntity, entity);
            entity->params = 2;
            entity->ext.wargpuff.unk89 = 6 - i;
            entity->ext.wargpuff.unk84 = temp_s3;
            entity->ext.wargpuff.unk88 = temp_s4;
REDACTED
REDACTED
REDACTED

REDACTED
REDACTED
    Unkstruct_80180FE0* obj;
    s32 velocityX;
    s32 velocityY;
    s32 params;
    s32 temp_s0;
    s32 adjVelocityX;
    s32 adjVelocityY;
    u32 temp_v0;
    s32 rnd;

    switch (self->step) {
    case 0:
        InitializeEntity(g_InitializeEntityData0);
        params = self->params & 0xF;
        obj = &D_80180FE0[params];
        self->palette = obj->palette + 0x2E0;
        self->drawMode = obj->drawMode;
        self->animSet = obj->animSet;
        self->unk5A = obj->unk2;
        self->ext.wargpuff.unk80 = obj->unk8;
        self->step = params + 1;

        temp_v0 = self->params & 0xFF00;
        if (temp_v0 != 0) {
            self->zPriority = temp_v0 >> 8;
        }

        if (self->params & 0xF0) {
            self->palette = 0x819F;
            self->drawMode = DRAW_TPAGE;
            self->facingLeft = 1;
        }
        break;

    case 1:
        MoveEntity();
        self->velocityY = FIX(-1);
        if (AnimateEntity((u8*)self->ext.wargpuff.unk80, self) == 0) {
            DestroyEntity(self);
        }
        break;

    case 2:
        if (AnimateEntity((u8*)self->ext.wargpuff.unk80, self) != 0) {
            switch (self->step_s) {
            case 0:
                self->drawFlags = FLAG_DRAW_UNK8;
                self->unk6C = 0x80;
                self->step_s++;
                break;

            case 1:
                if (self->animFrameIdx == 5) {
                    self->step_s++;
                }
                break;

            case 2:
                self->unk6C += 0xFC;
                return;
            }
        } else {
REDACTED
REDACTED
REDACTED

    case 3:
        if (self->step_s == 0) {
            self->drawFlags |= 4;
            switch (self->ext.wargpuff.unk88) {
            case 1:
                if (self->ext.wargpuff.unk89 >= 0x4) {
                    self->ext.wargpuff.unk89 += 0xFD;
                    self->ext.wargpuff.unk84 -= 0x800;
                }
                break;

            case 2:
                self->ext.wargpuff.unk84 =
                    (u16)self->ext.wargpuff.unk84 +
                    ((u8)self->ext.wargpuff.unk89 * 0xC0);
                break;
            }
            self->ext.wargpuff.unk84 = self->ext.wargpuff.unk84 & 0xFFF;
            self->rotZ = self->ext.wargpuff.unk84 & 0xFFF;
            temp_s0 = self->ext.wargpuff.unk89 * 0x140;
            temp_s0 /= 28;
            self->velocityX = temp_s0 * rsin(self->ext.wargpuff.unk84);
            self->velocityY = -(temp_s0 * rcos(self->ext.wargpuff.unk84));
            self->step_s++;
        }

        if (self->animFrameIdx >= 13) {
            velocityX = self->velocityX;
            if (velocityX < 0) {
                adjVelocityX = velocityX + 3;
            } else {
                adjVelocityX = velocityX;
            }
            self->velocityX = velocityX - (adjVelocityX >> 2);

            velocityY = self->velocityY;
            if (velocityY < 0) {
                adjVelocityY = velocityY + 3;
            } else {
                adjVelocityY = velocityY;
            }
            self->velocityY = velocityY - (adjVelocityY >> 2);
        }
        MoveEntity();
        if (AnimateEntity((u8*)self->ext.wargpuff.unk80, self) == 0) {
REDACTED
REDACTED
REDACTED
REDACTED
    case 4:
        if (self->step_s == 0) {
            rnd = Random();
            self->velocityY = FIX(-0.75);
            self->facingLeft = rnd & 1;
            self->rotX = 0xC0;
            self->drawFlags |= 1;
            self->step_s++;
        }
        MoveEntity();
        if (AnimateEntity((u8*)self->ext.wargpuff.unk80, self) == 0) {
            DestroyEntity(self);
        }
        break;
    }
}
