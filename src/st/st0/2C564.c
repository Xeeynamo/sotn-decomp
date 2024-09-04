REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
#include "sfx.h"
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
REDACTED
REDACTED
REDACTED
REDACTED
    if ((self->flags & FLAG_DEAD) && (self->step < 8)) {
        self->hitboxState = 0;
        self[1].hitboxState = 0;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
    if (self->hitFlags == 1) {
REDACTED
REDACTED
REDACTED
    if (self->hitFlags == 2) {
REDACTED
REDACTED
REDACTED
    if (self->hitFlags == 3) {
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
        self->hitboxState = 0;
        self->facingLeft = 1;
REDACTED
REDACTED
REDACTED
        primIndex = g_api.func_800EDB58(PRIM_GT4, 128);
        if (primIndex == -1) {
REDACTED
REDACTED
REDACTED
REDACTED
        prim = &g_PrimBuf[primIndex];
        self->primIndex = primIndex;
REDACTED
        self->flags |= FLAG_HAS_PRIMS;
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
            if (self->animFrameIdx == 2 && self->animFrameDuration == 0) {
                newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
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
                g_api.TimeAttackController(
                    TIMEATTACK_EVENT_DRACULA_DEFEAT, TIMEATTACK_SET_VISITED);
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
            self->hitboxState = 0;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
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
REDACTED
REDACTED
REDACTED
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
REDACTED
            self->hitboxState = 3;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
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
                g_api.PlaySfx(SFX_FIREBALL_SHOT_A);
REDACTED
REDACTED
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
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
            self->hitboxState = 0;
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
            if (self->animFrameIdx == 5 && self->animFrameDuration == 0) {
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
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
            prim->drawMode = 0x31;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
            prim->drawMode = 0x31;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
            prim->drawMode = 0x31;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
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
            self[2].facingLeft = self->facingLeft;
REDACTED
            self[5].facingLeft = self->facingLeft;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
            if (PrimDecreaseBrightness(self->ext.dracula.prim, 7) == 0) {
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
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
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
        self->hitboxState = 1;
REDACTED
        self->hitboxOffX = 3;
        self->hitboxOffY = 0x27;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
        self->facingLeft = self[-1].facingLeft;
REDACTED
REDACTED
        self->hitboxState = self[-1].hitboxState & 0xFFFD;
REDACTED
REDACTED
        self->hitboxState = 0;
REDACTED
REDACTED
REDACTED
REDACTED
        self->hitboxState = 0;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
        self->flags |= FLAG_DEAD;
REDACTED
REDACTED
    if (self->flags & FLAG_DEAD) {
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
        if (self->facingLeft == 0) {
            self->velocityX = FIX(-2);
REDACTED
            self->velocityX = FIX(2);
REDACTED
REDACTED
REDACTED
            self->velocityY = FIX(-0.5);
REDACTED
REDACTED
REDACTED
            self->velocityY = FIX(0.5);
REDACTED
        self->ext.dracula.unk8C = 0x28;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
        if (--self->ext.dracula.unk8C == 0) {
            self->velocityY = 0;
        }
        return;
    }
}

extern u16 D_801805F8[];
extern u8 D_80180990[];
extern u8 D_801809B0[];
extern s16 D_80180A60[];
extern s16 D_80180A62[];
REDACTED
    s32 speedX;

    if (g_isDraculaFirstFormDefeated) {
        entity->entityId = E_EXPLOSION;
        entity->pfnUpdate = EntityExplosion;
REDACTED
REDACTED
REDACTED
        return;
    }

REDACTED
    case 0:
        InitializeEntity(D_801805F8);
        entity->hitboxState = 0;
        entity->drawFlags |= 4;
        break;
    case 1:
        if (AnimateEntity(D_801809B0, entity) == 0) {
            entity->hitboxState = 1;
REDACTED
        }
        break;
    case 2:
        AnimateEntity(D_80180990, entity);
        MoveEntity();
        entity->rotZ += 4;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
        if (entity->facingLeft != 0) {
            entity->velocityX += speedX;
REDACTED
            entity->velocityX -= speedX;
REDACTED
REDACTED
        if (!(g_Timer & 3)) {
REDACTED
            if (newEntity != 0) {
                s32 randomPosXYIndex;
                CreateEntityFromEntity(0x1E, entity, newEntity);
                newEntity->zPriority = entity->zPriority + 1;
                randomPosXYIndex = (Random() & 3) * 2;
                newEntity->posX.i.hi =
                    newEntity->posX.i.hi + D_80180A60[randomPosXYIndex];
                newEntity->posY.i.hi =
                    newEntity->posY.i.hi + D_80180A62[randomPosXYIndex];
            }
        }
        break;
    }
}

extern u16 D_801805EC[];
extern u8 D_801809E0[];
REDACTED
    if (g_isDraculaFirstFormDefeated) {
        DestroyEntity(entity);
        return;
    }

REDACTED
        InitializeEntity(D_801805EC);
        entity->animCurFrame = 0;
        entity->hitboxState = 0;
        entity->velocityY = FIX(-1);
    }
    MoveEntity();

    if (AnimateEntity(D_801809E0, entity) == 0) {
        DestroyEntity(entity);
    }
}

extern u16 D_801805EC[];
extern u8 D_80180A40[];
REDACTED
REDACTED
    case 0:
        InitializeEntity(D_801805EC);
        entity->animCurFrame = 0x59;
        entity->drawFlags = FLAG_DRAW_ROTZ;
        entity->hitboxState = 0;
        entity->velocityX = FIX(-1);
        entity->velocityY = 0;
REDACTED
            s16 radians;
            s32 speed;
            entity->animCurFrame = 0x5C;
            speed = (Random() & 0x1F) + 0x10;
            radians = (Random() * 6) + 0x900;
            entity->velocityX = speed * rcos(radians);
            entity->velocityY = speed * rsin(radians);
REDACTED
REDACTED
REDACTED
REDACTED
        entity->rotZ += 0x20;
        entity->velocityY += FIX(0.125);
        if (entity->posY.i.hi >= 205) {
            g_api.PlaySfx(NA_SE_BREAK_GLASS);
            entity->posY.i.hi = 204;
REDACTED
REDACTED
REDACTED
REDACTED
        entity->drawFlags = 0;
        if (AnimateEntity(D_80180A40, entity) == 0) {
            s32 i;
            for (i = 0; i < 8; i++) {
REDACTED
REDACTED
                if (glassShardEntity != 0) {
                    CreateEntityFromEntity(31, entity, glassShardEntity);
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
        entity->velocityY += FIX(0.125);
        if (entity->posY.i.hi >= 205) {
            DestroyEntity(entity);
        }
        break;
    }
}
