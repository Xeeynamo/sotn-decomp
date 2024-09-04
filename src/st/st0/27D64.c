#include "st0.h"
#include "sfx.h"

REDACTED
    s32 temp_v0;
    ObjInit* obj = &D_80180638[self->params];

REDACTED
        InitializeEntity(g_eInitGeneric2);
        self->animSet = obj->animSet;
        self->zPriority = obj->zPriority;
        self->unk5A = obj->unk5A;
REDACTED
        self->drawFlags = obj->drawFlags;
        self->drawMode = obj->drawMode;
REDACTED
REDACTED
        }
    }
REDACTED
}

REDACTED
REDACTED

    diffX = abs(diffX);
REDACTED
REDACTED
        diffX = abs(diffX);
        return self->hitboxHeight >= diffX;
REDACTED
REDACTED
    }
}

extern u16 D_801805B0[];
extern u8 D_8018065C[];
extern u8 D_80180660[];
extern u16 D_80180664[];

void EntityLockCamera(Entity* self) {
    s32 facingLeft;
    u16 offset;
    u16* rect16;
    u16 params;
    u8 flag;

    params = ((u8)self->params);
    if (self->step == 0) {
        InitializeEntity(D_801805B0);

        self->hitboxState = 1;

        flag = D_80180660[params];
        self->ext.lockCamera.unk7C = flag;

        if (flag) {
            self->hitboxWidth = D_8018065C[params];
            self->hitboxHeight = 20;
        } else {
            self->hitboxWidth = 20;
            self->hitboxHeight = D_8018065C[params];
        }
    }

    if (self->params & 0x100) {
        params *= 4;
        rect16 = &D_80180664[params];
        g_Tilemap.x = *rect16++;
        g_Tilemap.y = *rect16++;
        g_Tilemap.width = *rect16++;
        g_Tilemap.height = *rect16++;
        DestroyEntity(self);
        return;
    }

    if (func_801A7E2C(self) != 0) {
        facingLeft = GetSideToPlayer();
        if (self->ext.lockCamera.unk7C) {
            facingLeft &= 2;
            offset = facingLeft * 2;
        } else {
            facingLeft &= 1;
            offset = facingLeft * 4;
        }
        params <<= 3;
        params += offset;
        rect16 = &D_80180664[params];
        g_Tilemap.x = *rect16++;
        g_Tilemap.y = *rect16++;
        g_Tilemap.width = *rect16++;
        g_Tilemap.height = *rect16++;
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
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
                self->facingLeft = GetSideToPlayer() & 1;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
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
REDACTED
REDACTED
REDACTED
REDACTED
                g_api.PlaySfx(SFX_CANDLE_HIT_WHOOSH_B);
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
                g_api.PlaySfx(SFX_GLASS_BREAK_E);
REDACTED
REDACTED
REDACTED
                CreateEntityFromCurrentEntity(E_EXPLOSION, newEntity);
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
        InitializeEntity(g_eBreakableInit);
        self->zPriority = g_unkGraphicsStruct.g_zEntityCenter - 0x14;
        self->drawMode = D_8018074C[params];
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED

REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
    s32 velX;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
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
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
            UnkPolyFunc2(prim);
REDACTED
REDACTED
REDACTED
REDACTED
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
            velX = ((Random() & 7) << 0xC) + 0x8000;
            self->velocityX = velX;
            if (self->facingLeft == 0) {
                self->velocityX = -velX;
REDACTED
            self->velocityY = ((Random() & 7) << 0xC) - 0x8000;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
        self->velocityY += FIX(0.125);
REDACTED
REDACTED
REDACTED
        if (self->facingLeft != 0) {
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
        UnkPrimHelper(prim);
REDACTED
        g_api.CheckCollision(
            self->posX.i.hi, (s16)(self->posY.i.hi + 8), &collider, 0);
REDACTED
REDACTED
REDACTED
REDACTED
                CreateEntityFromCurrentEntity(E_EXPLOSION, newEntity);
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED

REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
    FntPrint("sx:%04x\n", g_Tilemap.left);
    FntPrint("ex:%04x\n", g_Tilemap.right);
REDACTED
REDACTED
    case 0:
        InitializeEntity(g_eInitGeneric2);
        entity->animSet = ANIMSET_DRA(2);
        entity->animCurFrame = 1;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
        dist = abs(dist);
REDACTED
REDACTED
REDACTED
REDACTED
                if (g_PlayerX > 0x280) {
                    g_Tilemap.width = 0x280;
                    g_Tilemap.right--;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
                if (g_PlayerX < 0x180) {
                    g_Tilemap.x = 0x180;
                    g_Tilemap.left++;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
                if (g_PlayerX < 0x100) {
                    g_Tilemap.x = 0x100;
                    g_Tilemap.left++;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
                if (g_PlayerX < 0x80) {
                    g_Tilemap.x = 0x80;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
                if (g_PlayerX > 0x480) {
                    g_Tilemap.width = 0x480;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
                if (g_PlayerX > 0x480) {
                    g_Tilemap.width = 0x480;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
                if (g_PlayerX < 0x80) {
                    g_Tilemap.x = 0x80;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
                if (g_PlayerX > 0x280) {
                    g_Tilemap.width = 0x280;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
                if (g_PlayerX < 0x180) {
                    g_Tilemap.x = 0x180;
                    g_Tilemap.left++;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
                if (g_PlayerX > 0x280) {
                    g_Tilemap.width = 0x280;
                    g_Tilemap.right--;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
                if (g_PlayerX < 0x180) {
                    g_Tilemap.x = 0x180;
                    g_Tilemap.left++;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
                if (g_PlayerX > 0x300) {
                    g_Tilemap.width = 0x300;
                    g_Tilemap.right--;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
