REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
#include "sfx.h"

// vase in the room with the door to the caverns
void EntityCavernDoorVase(Entity* self) {
    ObjInit2* objInit = &D_80180BFC[self->params];

    if (self->step == 0) {
        InitializeEntity(g_eInitGeneric2);
        self->animSet = objInit->animSet;
        self->zPriority = objInit->zPriority;
        self->facingLeft = objInit->facingLeft;
        self->unk5A = objInit->unk5A;
        self->palette = objInit->palette;
        self->drawFlags = objInit->drawFlags;
        self->drawMode = objInit->drawMode;
        if (objInit->unkC != 0) {
            self->flags = objInit->unkC;
        }
    }

    AnimateEntity(objInit->unk10, self);
}

REDACTED
REDACTED
    u16* temp_v0_2;
REDACTED
    u16 phi_v1;
    u16 unk;
REDACTED
    entity->unk6D[0] = 0;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
            if (g_Tilemap.x != 0) {
                return;
            }
            break;
REDACTED
        case 6:
            if (g_pads->pressed & PAD_TRIANGLE) {
                g_Tilemap.x = 0;
                g_Tilemap.width = 1280;
REDACTED
                return;
            }
            break;
        }

        if (entity->unk44 != 0) {
            ret = GetSideToPlayer();
REDACTED
            if (phi_v1 != 0) {
REDACTED
            } else {
REDACTED
            }
REDACTED
REDACTED
REDACTED
            g_Tilemap.x = *(temp_v0_2++);
            g_Tilemap.y = *(temp_v0_2++);
            g_Tilemap.width = *(temp_v0_2++);
            g_Tilemap.height = *(temp_v0_2++);
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
            entity->hitboxHeight = 16;
        } else {
            entity->hitboxWidth = 16;
REDACTED
REDACTED
REDACTED
REDACTED

extern u16 g_eBreakableInit[];
extern u8* g_eBreakableAnimations[8];
extern u8 g_eBreakableHitboxes[];
extern u8 g_eBreakableExplosionTypes[];
extern u16 g_eBreakableanimSets[];
extern u8 g_eBreakableDrawModes[];
void EntityBreakable(Entity* entity) {
REDACTED
REDACTED
        AnimateEntity(g_eBreakableAnimations[breakableType], entity);
        if (entity->unk44) { // If the candle is destroyed
REDACTED
            g_api.PlaySfx(SFX_CANDLE_HIT);
            entityDropItem = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (entityDropItem != NULL) {
                CreateEntityFromCurrentEntity(E_EXPLOSION, entityDropItem);
REDACTED
                    g_eBreakableExplosionTypes[breakableType];
            }
            ReplaceBreakableWithItemDrop(entity);
        }
    } else {
        InitializeEntity(g_eBreakableInit);
        entity->zPriority = g_unkGraphicsStruct.g_zEntityCenter - 0x14;
        entity->drawMode = g_eBreakableDrawModes[breakableType];
        entity->hitboxHeight = g_eBreakableHitboxes[breakableType];
        entity->animSet = g_eBreakableanimSets[breakableType];
    }
}

REDACTED
REDACTED
    case 0:
        InitializeEntity(D_80180AD0);
REDACTED
REDACTED
REDACTED
REDACTED
    case 1:
        g_GpuBuffers[0].draw.r0 = self->ext.generic.unk7C.S8.unk0;
        g_GpuBuffers[0].draw.g0 = self->ext.generic.unk7C.S8.unk1;
        g_GpuBuffers[0].draw.b0 = self->ext.generic.unk7E.modeU8.unk0;
        g_GpuBuffers[1].draw.r0 = self->ext.generic.unk7C.S8.unk0;
        g_GpuBuffers[1].draw.g0 = self->ext.generic.unk7C.S8.unk1;
        g_GpuBuffers[1].draw.b0 = self->ext.generic.unk7E.modeU8.unk0;
        break;
    }
}

// lightning and sound for background
INCLUDE_ASM("st/no3/nonmatchings/377D4", EntityBackgroundLightning);

// window that opens and shuts in the background
REDACTED
REDACTED
REDACTED
REDACTED
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
REDACTED
        if (primIndex == -1) {
REDACTED
REDACTED
REDACTED
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
            prim->drawMode = 2;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
            PlaySfxPositional(SE_NO3_WINDOW_CLOSE);
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED

// main door to the castle that closes during intro
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
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
        if (primIndex == -1) {
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
        self->primIndex = primIndex;
REDACTED
        self->flags |= FLAG_HAS_PRIMS;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
            prim->drawMode = 2;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
        if (g_CastleFlags[52] != 0) {
            self->ext.castleDoor.rotZ = 0;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
            g_Tilemap.fg[tilePos] = *tilePtr;
REDACTED
REDACTED
        self->ext.castleDoor.rotZ = -0x380;
REDACTED
REDACTED
        g_CastleFlags[52] = 1;
REDACTED
REDACTED
REDACTED
        self->ext.castleDoor.rotZ -= 8;
        if (self->ext.castleDoor.rotZ < -0x380) {
            self->ext.castleDoor.rotZ = -0x380;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
        self->ext.castleDoor.rotZ += 0x10;
        if (self->ext.castleDoor.rotZ > 0) {
            self->ext.castleDoor.rotZ = 0;
REDACTED
            g_api.PlaySfx(SFX_START_SLAM_B);
REDACTED
REDACTED
                g_Tilemap.fg[tilePos] = *tilePtr;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
            g_Tilemap.fg[tilePos] = *tilePtr;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
    sVec1.vy = self->ext.castleDoor.rotZ;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
        LOW(prim->r1) = LOW(prim->r0);
        LOW(prim->r2) = LOW(prim->r0);
        LOW(prim->r3) = LOW(prim->r0);
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
            prim->drawMode = DRAW_HIDE;
REDACTED
            prim->drawMode = 6;
REDACTED
REDACTED
REDACTED
REDACTED

extern u16 D_80180B18[];
extern SVECTOR D_801811E8;
extern s16 D_801811A0;
extern s16* D_801811C0;
extern u8 D_80181140[];
extern u8 D_80181158[];

// bushes in parallax background
void EntityBackgroundBushes(Entity* self) {
    byte stackpad[8];

    // Lots of ugly pointers
    u8* var_s1;
    s16* var_s4;
    s16* var_s5;
    s16** var_s8;
    Primitive* prim;
    s32 primIndex;
    s32 i;
    s32 yOffset;
    s16 xPos;
    s16 yPos;
    s32 rotTransXYResult;
    s32 unused1; // return args for rottranspers
    s32 unused2; // we don't use them.
    VECTOR trans;
    MATRIX m;

    if (!self->step) {
        InitializeEntity(D_80180B18);
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 0x48);
        if (primIndex == -1) {
REDACTED
REDACTED
REDACTED
        self->flags |= FLAG_HAS_PRIMS;
        self->primIndex = primIndex;
REDACTED
        self->ext.prim = prim;
REDACTED
REDACTED
            prim->drawMode = DRAW_HIDE;
REDACTED
REDACTED
REDACTED
    SetGeomScreen(0x400);
    SetGeomOffset(0x80, self->posY.i.hi);
    RotMatrix(&D_801811E8, &m);
    SetRotMatrix(&m);
    if (self->params) {
        trans.vx = self->posX.i.hi - 0x200;
    } else {
        trans.vx = self->posX.i.hi + 0x200;
    }
    trans.vy = 0;
    var_s5 = &D_801811A0;
    var_s8 = &D_801811C0;
    prim = self->ext.prim;
    for (i = 0; i < 4; i++, var_s8++, var_s5 += 4) {
        trans.vz = *var_s5 + 0x400;
        TransMatrix(&m, &trans);
        SetTransMatrix(&m);
        RotTransPers(&D_801811E8, &rotTransXYResult, &unused1, &unused2);
        // Split out the upper and lower halfword of rotTransXYResult
        xPos = rotTransXYResult & 0xFFFF;
        yPos = rotTransXYResult >> 16;
        xPos = xPos % var_s5[3];
        xPos -= var_s5[3];
        yPos = self->posY.i.hi;
        var_s4 = *var_s8;
        while (xPos < 0x140) {
            var_s1 = &D_80181140[0];
            var_s1 += ((*var_s4++) * 4);
            prim->u0 = prim->u2 = var_s1[0];
            prim->u1 = prim->u3 = prim->u0 + var_s1[2];
            prim->v0 = prim->v1 = var_s1[1];
            prim->v2 = prim->v3 = prim->v0 + var_s1[3];
            prim->x0 = prim->x2 = xPos - var_s1[2] / 2;
            prim->x1 = prim->x3 = xPos + var_s1[2] / 2;
            prim->y0 = prim->y1 = yPos - var_s1[3];
            prim->y2 = prim->y3 = yPos;
            prim->clut = var_s5[2];
            prim->priority = var_s5[1];
            prim->drawMode = DRAW_UNK02;
            prim = prim->next;

            if (prim == NULL) {
                return;
            }
            if (i > 1) {
                yOffset = var_s1[3];
                var_s1 = &D_80181158[0];
                prim->u0 = prim->u2 = var_s1[0];
                prim->u1 = prim->u3 = prim->u0 + var_s1[2];
                prim->v0 = prim->v1 = var_s1[1];
                prim->v2 = prim->v3 = prim->v0 + var_s1[3];
                var_s1 += (i - 2) * 4;
                prim->x0 = prim->x2 = xPos - var_s1[2] / 2;
                prim->x1 = prim->x3 = xPos + var_s1[2] / 2;
                prim->y0 = prim->y1 = (yPos - yOffset) - var_s1[3];
                prim->y2 = prim->y3 = (yPos - yOffset);
                prim->clut = 0x17;
                if (i > 2) {
                    prim->clut = 0x49;
                }
                prim->priority = var_s5[1];
                prim->drawMode = DRAW_UNK02;
                prim = prim->next;
                if (prim == NULL) {
                    return;
                }
            }
            xPos += *var_s4++;
            if (*var_s4 == -1) {
                var_s4 = *var_s8;
            }
        }
    }
    while (prim != NULL) {
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
        InitializeEntity(D_80180B18);
REDACTED
        if (primIndex == -1) {
REDACTED
REDACTED
REDACTED
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
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
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
REDACTED
REDACTED
        prim->drawMode = DRAW_HIDE;
REDACTED
REDACTED
REDACTED

// transparent water "plane" seen in the merman room
REDACTED
REDACTED
REDACTED
REDACTED
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
        if (primIndex == -1) {
REDACTED
REDACTED
REDACTED
REDACTED
        self->primIndex = primIndex;
REDACTED
        self->flags |= FLAG_HAS_PRIMS;
REDACTED
REDACTED
REDACTED
REDACTED
            prim->drawMode = 8;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
            g_ClutIds[var_a0[0]] = g_ClutIds[var_a0[2] + 0x200];
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
            g_ClutIds[var_a0[0]] = g_ClutIds[var_a0[3] + 0x200];
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
    var_a3 = -1 * g_Tilemap.scrollX.i.hi % 38;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
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
        prim->drawMode = 8;
REDACTED
REDACTED
REDACTED

void func_801B94F0(Primitive* prim) {
    s32 xVar;
    s32 yVar;

    switch (prim->p3) {
    case 1:
        xVar = (Random() & 0xF) - 8;
        prim->x0 = g_CurrentEntity->posX.i.hi + xVar;
        prim->y0 = 0x9C;
        prim->x1 = 0;
        prim->y1 = 0;
        if (xVar > 0) {
            LOW(prim->x3) = Random() << 6;
        } else {
            LOW(prim->x3) = -Random() * 0x40;
        }
        LOW(prim->x2) = (Random() << 8) + FIX(-4);
        prim->blendMode = 2;
        prim->p3++;
        /* fallthrough */
    case 2:
        xVar = (prim->x0 << 0x10) + (u16)prim->x1;
        yVar = (prim->y0 << 0x10) + (u16)prim->y1;
        xVar += LOW(prim->x3);
        yVar += LOW(prim->x2);
        prim->x0 = (xVar >> 0x10);
        prim->x1 = xVar & 0xFFFF;
        prim->y0 = (yVar >> 0x10);
        prim->y1 = yVar & 0xFFFF;

        LOW(prim->x2) += FIX(1.0 / 4.0);
        if (LOW(prim->x2) <= 0x60000) {
            return;
        }
        prim->p3++;
        break;
    case 3:
        prim->blendMode = 8;
        prim->p3 = 0;
        break;
    }
}

// lever and platform to open caverns door
REDACTED
REDACTED
REDACTED
REDACTED
    switch (entity->step) {
    case 0:
        InitializeEntity(D_80180B18);
REDACTED
        entity->rotZ = -0x200;
        entity->drawFlags |= 4;
REDACTED
        if (g_CastleFlags[0x30] != 0) {
            entity->rotZ = 0;
REDACTED
REDACTED
REDACTED
REDACTED
            entity->rotZ += 4;
            if (entity->rotZ > 0) {
                entity->rotZ = 0;
                if (g_CastleFlags[0x30] == 0) {
                    g_api.PlaySfx(SFX_LEVER_METAL_BANG);
REDACTED
                g_CastleFlags[0x30] = 1;
            } else if (!(g_Timer & 0xF)) {
                g_api.PlaySfx(SFX_LEVER_METAL_BANG);
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
    posX += rcos(entity->rotZ) * 0x280;
    posY += rsin(entity->rotZ) * 0x280;
REDACTED
REDACTED
REDACTED

// platform attached to lever at cavern door
REDACTED
REDACTED
    s32 xDiff;
    s32 collision;

REDACTED
REDACTED
        InitializeEntity(D_80180B18);
REDACTED
        self->ext.cavernDoor.xCoord.val = self->posX.val;
        self->ext.cavernDoor.xCoord.val = self->posX.val; // ? WTF
REDACTED
REDACTED
        collision = GetPlayerCollisionWith(self, 6, 5, 4);
        self->ext.cavernDoor.collision = collision;

        if (collision != 0) {
            xDiff = self->posX.i.hi - FIX_TO_I(self->ext.cavernDoor.xCoord.val);
            player = &PLAYER;
            player->posX.i.hi += xDiff;
            player->posY.i.hi += 1;
        }
        self->ext.cavernDoor.xCoord.val = self->posX.val;
        self->ext.cavernDoor.yCoord.val = self->posY.val;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
    s32 primIndex;
    s16* tileLayoutPtr;
REDACTED
    Primitive* prim;
REDACTED
    s32 tilePos;
    s32 tileSteps;
REDACTED
REDACTED
REDACTED
        InitializeEntity(D_80180B18);
REDACTED
REDACTED
REDACTED
REDACTED
        if (g_CastleFlags[48]) {
REDACTED
REDACTED
            tileLayoutPtr += 3;
REDACTED
            primIndex = g_api.AllocPrimitives(PRIM_TILE, 64);
            if (primIndex == -1) {
REDACTED
REDACTED
REDACTED
            self->flags |= FLAG_HAS_PRIMS;
            self->primIndex = primIndex;
            prim = &g_PrimBuf[primIndex];
            self->ext.cavernDoor.prim = prim;
            while (prim != NULL) {
                prim->u0 = prim->v0 = 1;
                prim->r0 = 64;
                prim->b0 = 128;
                prim->g0 = 96;
                prim->priority = self->zPriority + 0x18;
                prim->drawMode = DRAW_HIDE;
                prim->p3 = 0;
                prim = prim->next;
REDACTED
REDACTED
REDACTED
REDACTED
            g_Tilemap.fg[tilePos] = *tileLayoutPtr++;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
        if (g_CastleFlags[48]) {
            g_api.PlaySfx(SFX_SWITCH_CLICK);
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
        self->posY.val += FIX(0.375);
        self->ext.cavernDoor.jiggler++;
        // While the door opens, it jiggles left and right by repeatedly
        // incrementing and decrementing its x position.
        if (self->ext.cavernDoor.jiggler & 1) {
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
        tileSteps = (self->posY.i.hi - 136);
        tileSteps /= 16;
        if (tileSteps > 3) {
            tileSteps = 3;
REDACTED
REDACTED
        tilePos = 0x76;
REDACTED
        tileLayoutPtr += 3;
        for (i = 0; i < tileSteps; tilePos += 0x10, i++) {
            g_Tilemap.fg[tilePos] = *tileLayoutPtr++;
REDACTED
REDACTED
        if (g_Timer & 1) {
            break;
        }
        prim = self->ext.cavernDoor.prim;
        prim = FindFirstUnkPrim(prim);
        if (prim != NULL) {
            prim->p3 = 1;
        }
REDACTED
        if (g_Timer & 15) {
            break;
        }
REDACTED
        if (entity == NULL) {
            break;
REDACTED
        CreateEntityFromEntity(6, self, entity);
        entity->posY.i.hi = 156;
        entity->posX.i.hi += -8 + (Random() & 15);
        entity->zPriority = self->zPriority + 2;
        entity->params = 0x10;
        entity->drawFlags |= (FLAG_DRAW_ROTX + FLAG_DRAW_ROTY);
        entity->rotX = entity->rotY = 192;
REDACTED
REDACTED
REDACTED
    if (self->flags & FLAG_HAS_PRIMS) {
        for (prim = self->ext.cavernDoor.prim; prim != NULL;
             prim = prim->next) {
            if (prim->p3) {
                func_801B94F0(prim);
REDACTED
REDACTED
REDACTED
REDACTED

REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
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
REDACTED
REDACTED
        prim->drawMode = DRAW_HIDE;
REDACTED
REDACTED
REDACTED

// switch that clicks when you step on it
REDACTED
    s32 temp_a0 = GetPlayerCollisionWith(entity, 8, 4, 4);
REDACTED
REDACTED
    switch (entity->step) {
    case 0:
        InitializeEntity(D_80180B18);
REDACTED
REDACTED
        if (g_CastleFlags[0x31] != 0) {
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
            entity->posY.val += FIX(0.75);
            if ((g_Tilemap.scrollY.i.hi + entity->posY.i.hi) > 160) {
                entity->posY.i.hi = 160 - g_Tilemap.scrollY.i.hi;
                g_api.PlaySfx(SFX_SWITCH_CLICK);
                g_CastleFlags[0x31] = 1;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED

// smaller weight blocking path near cube of zoe
REDACTED
    s16 primIndex;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
        InitializeEntity(D_80180B18);
REDACTED
REDACTED
REDACTED
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 8);
        if (primIndex == -1) {
REDACTED
REDACTED
REDACTED
REDACTED
        poly = &g_PrimBuf[primIndex];
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
        if (g_CastleFlags[49] != 0) {
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
        if (g_CastleFlags[49] != 0) {
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
        self->posY.val += FIX(0.5);
        if ((self->posY.i.hi + g_Tilemap.scrollY.i.hi) >= 175) {
            self->posY.i.hi = 175 - g_Tilemap.scrollY.i.hi;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
            g_Tilemap.fg[var_a1] = 0x4FA;
            g_Tilemap.fg[var_a1 + 1] = 0x4FA;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
    if (self->step < 3 && GetPlayerCollisionWith(self, 16, 16, 5) & 4) {
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED

// taller weight blocking path near cube of zoe
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
        InitializeEntity(D_80180B18);
REDACTED
REDACTED
REDACTED
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 8);
        if (primIndex == -1) {
REDACTED
REDACTED
REDACTED
        poly = &g_PrimBuf[primIndex];
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
        if (g_CastleFlags[49] != 0) {
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
        if (g_CastleFlags[49] != 0) {
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
        self->posY.val -= FIX(0.5);
        temp = self->posY.i.hi + g_Tilemap.scrollY.i.hi;
REDACTED
            self->posY.i.hi = -16 - g_Tilemap.scrollY.i.hi;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
        temp = self->posY.i.hi + g_Tilemap.scrollY.i.hi;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
        g_Tilemap.fg[var_a1] = 0;
        g_Tilemap.fg[var_a1 + 1] = 0;
REDACTED
REDACTED
REDACTED
        g_Tilemap.fg[var_a1] = 0x4FA;
        g_Tilemap.fg[var_a1 + 1] = 0x4FA;
REDACTED
REDACTED

// trap door that leads to underground garden in saturn version.
// also opens the one leading to the save room
REDACTED
    switch (entity->step) {
    case 0:
        InitializeEntity(D_80180B18);
REDACTED
REDACTED
REDACTED
REDACTED
        entity->hitboxState = 1;
REDACTED
REDACTED
REDACTED
                g_Tilemap.fg[0xA8E / 2] = 0x129;
                g_Tilemap.fg[0xA90 / 2] = 0x132;
REDACTED
REDACTED
REDACTED
            g_Tilemap.fg[0xA8E / 2] = 0x6C8;
            g_Tilemap.fg[0xA90 / 2] = 0x6C9;
REDACTED
REDACTED
            g_Tilemap.fg[0xA8E / 2] = 0x6C8;
            g_Tilemap.fg[0xA90 / 2] = 0x6C9;
REDACTED
REDACTED
REDACTED
REDACTED
        if (entity->hitFlags != 0) {
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
        AnimateEntity(D_80181240, entity);
REDACTED
REDACTED

// left side of the breakable rock, drops pot roast
REDACTED
REDACTED
REDACTED
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
        self->hitboxState = 2;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
            g_BgLayers[0].layout[tilePos] = *tileLayoutPtr;
            g_BgLayers[0].layout[tilePos + 1] = *(tileLayoutPtr + 3);
REDACTED
REDACTED
REDACTED
REDACTED
        if (g_CastleFlags[jewelSwordRoomUnlock] & rockBroken) {
REDACTED
REDACTED
REDACTED
                g_Tilemap.fg[tilePos] = *tileLayoutPtr;
                g_Tilemap.fg[tilePos + 1] = *(tileLayoutPtr + 3);
REDACTED
REDACTED
REDACTED
            self->hitboxState = 1;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
        if (self->hitFlags != 0) {
REDACTED
REDACTED
REDACTED
                g_Tilemap.fg[tilePos] = *tileLayoutPtr;
                g_Tilemap.fg[tilePos + 1] = *(tileLayoutPtr + 3);
REDACTED
REDACTED
REDACTED
REDACTED
            g_api.PlaySfx(SFX_WALL_DEBRIS_B);
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
                newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
REDACTED
REDACTED
REDACTED
                    newEntity->velocityX = -0x8000 - (Random() << 8);
                    newEntity->velocityY = -Random() * 0x100;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
            newEntity = AllocEntity(g_Entities + 160, g_Entities + 192);
REDACTED
REDACTED
REDACTED
REDACTED
            g_CastleFlags[jewelSwordRoomUnlock] |= rockBroken;
            self->hitboxState = 1;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
            g_CastleFlags[jewelSwordRoomUnlock] |= wolfFlag;
REDACTED
REDACTED
REDACTED
REDACTED

// right side of the merman room rock, breaks when hit
REDACTED
REDACTED
REDACTED
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
        self->hitboxState = 2;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
            g_BgLayers[0].layout[tilePos] = *tileLayoutPtr;
            g_BgLayers[0].layout[tilePos + 1] = *(tileLayoutPtr + 3);
REDACTED
REDACTED
REDACTED
REDACTED
        if (g_CastleFlags[jewelSwordRoomUnlock] & rockBroken) {
REDACTED
REDACTED
REDACTED
                g_Tilemap.fg[tilePos] = *tileLayoutPtr;
                g_Tilemap.fg[tilePos + 1] = *(tileLayoutPtr + 3);
REDACTED
REDACTED
REDACTED
            self->hitboxState = 1;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
        if (self->hitFlags != 0) {
REDACTED
REDACTED
REDACTED
                g_Tilemap.fg[tilePos] = *tileLayoutPtr;
                g_Tilemap.fg[tilePos + 1] = *(tileLayoutPtr + 3);
REDACTED
REDACTED
REDACTED
REDACTED
            g_api.PlaySfx(SFX_WALL_DEBRIS_B);
REDACTED
REDACTED
REDACTED
REDACTED
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
REDACTED
REDACTED
                    newEntity->velocityX = (Random() << 8) + 0x8000;
                    newEntity->velocityY = -Random() * 0x100;
                    newEntity->facingLeft = 1;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
            g_CastleFlags[jewelSwordRoomUnlock] |= rockBroken;
            self->hitboxState = 1;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
            g_CastleFlags[jewelSwordRoomUnlock] |= batFlag;
REDACTED
REDACTED
REDACTED
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
        if (g_CastleFlags[58] != 0) {
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
        if ((g_CastleFlags[51] & 12) == 12) {
            PlaySfxPositional(SFX_WALL_DEBRIS_B);
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
                g_Tilemap.fg[tileLayoutPos] = *tileLayoutPtr;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
                g_BgLayers[0].layout[tileLayoutPos] = *tileLayoutPtr;
REDACTED
REDACTED
REDACTED
REDACTED
        g_CastleFlags[58] |= 1;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED

// falling rock that breaks into dust
REDACTED
REDACTED
    Collider collider;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
        InitializeEntity(D_80180B18);
REDACTED
REDACTED
REDACTED
        self->drawFlags |= 4;
REDACTED
REDACTED
REDACTED
REDACTED
        self->velocityY += FIX(0.25);
        self->rotZ -= 0x20;
REDACTED
REDACTED
REDACTED
REDACTED
        if (collider.effects & EFFECT_SOLID) {
            if (self->velocityY > FIX(4.0)) {
                newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
            self->posY.i.hi = self->posY.i.hi + collider.unk18;
            temp_a0 = -self->velocityY;
            self->velocityY = -self->velocityY;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
            self->velocityY = temp_a0 - (var_a1 >> 3);
REDACTED
REDACTED
REDACTED
REDACTED

REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
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
        self->posX.i.hi = 1432 - g_Tilemap.scrollX.i.hi;
        self->posY.i.hi = 200 - g_Tilemap.scrollY.i.hi;
REDACTED
        if (g_CastleFlags[stairwayPieceBroken]) {
REDACTED
            g_Tilemap.fg[0x4D9] = 0x3EE;
            g_Tilemap.fg[0x539] = 0x3D2;
REDACTED
REDACTED
REDACTED
REDACTED
        g_Tilemap.fg[0x4D9] = 0x408;
        g_Tilemap.fg[0x539] = 0x40D;
REDACTED
REDACTED
REDACTED
        if (self->hitFlags != 0) {
            g_api.PlaySfx(SFX_STOMP_SOFT_A);
REDACTED
REDACTED
        if (self->flags & FLAG_DEAD) {
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
        g_api.PlaySfx(SFX_WALL_DEBRIS_B);
        g_Tilemap.fg[0x4D9] = 0x3EE;
        g_Tilemap.fg[0x539] = 0x3D2;
        g_CastleFlags[stairwayPieceBroken] = true;
REDACTED
REDACTED
REDACTED
            CreateEntityFromEntity(E_EQUIP_ITEM_DROP, self, newEntity);
REDACTED
REDACTED
REDACTED
        newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
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
        self->flags |= FLAG_HAS_PRIMS;
        UnkPolyFunc2(prim);
        v1 = g_Tilemap.tileDef->gfxIndex[0x409];
REDACTED
        temp = g_Tilemap.tileDef->gfxPage[0x409];
        prim->clut = g_Tilemap.tileDef->clut[0x409];
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
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
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
        UnkPrimHelper(prim);
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
        g_api.PlaySfx(SFX_WALL_DEBRIS_B);
        newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
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
REDACTED

// falling rock with puff of smoke when it disappears. I think part of the
// merman room breakable rock
REDACTED
REDACTED
    Collider collider;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
        InitializeEntity(D_80180B18);
REDACTED
        self->rotY = 0x60;
        self->rotX = 0x60;
        self->drawFlags |= 7;
REDACTED
REDACTED
        self->velocityX = rnd * rcos(rndAngle);
        self->velocityY = rnd * rsin(rndAngle);
        if (self->velocityX > 0) {
            self->facingLeft = 1;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
        self->velocityY += FIX(0.125);
        self->rotZ -= 0x20;
REDACTED
        g_api.CheckCollision(
            self->posX.i.hi, self->posY.i.hi + 8, &collider, 0);
        if (collider.effects & EFFECT_SOLID) {
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED

INCLUDE_ASM("st/no3/nonmatchings/377D4", func_801BB548);

// sky animation during death cutscene
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
        if (g_CastleFlags[53]) {
REDACTED
REDACTED
REDACTED
        InitializeEntity(g_EInitGeneric);
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
        prim->drawMode = DRAW_DEFAULT;
REDACTED
    g_BgLayers[0].flags &= 0xFFFE;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
    prim->drawMode = DRAW_COLORS;
REDACTED
REDACTED
REDACTED
REDACTED
    prim->drawMode = 8;
REDACTED
        prim2->drawMode = DRAW_HIDE;
REDACTED
REDACTED
REDACTED

REDACTED
REDACTED
        InitializeEntity(D_80180B18);
REDACTED
        self->flags &= ~FLAG_UNK_08000000;
        self->facingLeft = Random() & 1;
        g_api.PlaySfxVolPan(SFX_THUNDER_B, 0x40, (self->posX.i.hi >> 0x4) - 8);
    }
REDACTED
REDACTED
    }
}

void EntityUnkId2A(Entity* entity) {
    if (entity->step == 0) {
        InitializeEntity(D_80180B18);
        entity->zPriority = 0x29;
        entity->flags &= ~FLAG_UNK_08000000;
REDACTED
REDACTED
REDACTED
REDACTED
    }
REDACTED
REDACTED
        DestroyEntity(entity);
    }
}

// switch that goes downwards when you stand on it
REDACTED
    s32 temp_a0 = GetPlayerCollisionWith(entity, 8, 4, 4);
REDACTED

    switch (entity->step) {
    case 0:
        InitializeEntity(D_80180B18);
REDACTED
REDACTED
        if (g_CastleFlags[0x32] != 0) {
REDACTED
REDACTED
        }
REDACTED

REDACTED
REDACTED
REDACTED
            entity->posY.val += FIX(0.25);
            if ((g_Tilemap.scrollY.i.hi + entity->posY.i.hi) > 193) {
                entity->posY.i.hi = 193 - g_Tilemap.scrollY.i.hi;
                g_CastleFlags[0x32] = 1;
                g_api.PlaySfx(SFX_STONE_MOVE_B);
REDACTED
REDACTED
        }
REDACTED
    }
}

// door preventing access to warp room / heart
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
REDACTED
        InitializeEntity(D_80180B18);
REDACTED
REDACTED
REDACTED
        if (g_CastleFlags[50] != 0) {
            for (
                tilePos = 0x48, i = 7, self->step = 128, self->animCurFrame = 0;
                i >= 0; tilePos += 0x10, i--) {
                g_Tilemap.fg[tilePos] = 0;
REDACTED
REDACTED
REDACTED
REDACTED
        primIndex = g_api.AllocPrimitives(PRIM_TILE, 64);
        if (primIndex == -1) {
REDACTED
REDACTED
REDACTED
REDACTED
        poly = &g_PrimBuf[primIndex];
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
        for (tilePos = 0x48, temp = 0x4FA, i = 7; i >= 0; tilePos += 0x10,
            i--) {
            g_Tilemap.fg[tilePos] = temp;
REDACTED
REDACTED
REDACTED
REDACTED
        if (g_CastleFlags[50] != 0) {
            g_api.PlaySfx(SFX_STONE_MOVE_A);
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
        self->posY.val += FIX(0.375);
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
            g_Tilemap.fg[tilePos] = 0;
REDACTED
REDACTED
        if (!(g_Timer & 1)) {
            poly =
                FindFirstUnkPrim((POLY_GT4*)(*(s32*)&self->ext.generic.unk7C));
REDACTED
REDACTED
REDACTED
REDACTED
            if (!(g_Timer & 0xF)) {
                newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
                    newEntity->rotX = newEntity->rotY = 192;
                    newEntity->drawFlags |= 3;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
    if (self->flags & FLAG_HAS_PRIMS) {
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED

REDACTED
REDACTED
REDACTED
    switch (entity->step) {
    case 0:
        InitializeEntity(g_EInitGeneric);
REDACTED
REDACTED
        temp = g_Tilemap.fg[9];
        g_Tilemap.fg[6] = temp;
        temp = g_Tilemap.fg[10];
        g_Tilemap.fg[7] = temp;
        temp = g_Tilemap.fg[0x39];
        g_Tilemap.fg[0x36] = temp;
        temp = g_Tilemap.fg[0x3A];
        g_Tilemap.fg[0x37] = temp;
        temp = g_Tilemap.fg[0x69];
        g_Tilemap.fg[0x66] = temp;
        temp = g_Tilemap.fg[0x6A];
        g_Tilemap.fg[0x67] = temp;
REDACTED
REDACTED
REDACTED
REDACTED
