#include "no3.h"
#include "../e_merman.h"

extern u8 D_80183AC0[];
extern Point32 D_80183A28[];
extern u8 D_80183AAC[];
extern s16 D_80183A4C;
extern s32 D_80183B08[];
extern u8 D_80183ACC[]; // animation
extern u8 D_80183A48[];
extern u8 D_80183A84[]; // animation
extern s16 D_80183A7C;
extern u8 D_80183A9C[]; // animation
extern s16 D_80183A5C;
extern s16 D_80183A6C;
extern u8 D_80183ADC[]; // animation
extern s16 D_801813AC[];
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
    if ((self->flags & FLAG_DEAD) && (self->step < MERMAN_DYING)) {
        PlaySfxPositional(0x71D);
        self->hitboxState = 0;
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
        InitializeEntity(D_80180B60);
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
REDACTED
REDACTED
REDACTED
REDACTED
        AnimateEntity(D_80183AC0, self);
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
REDACTED
            self->velocityX = D_80183A28[rnd].x;
            self->velocityY = D_80183A28[rnd].y;
            self->step_s++;
        }
        if (AnimateEntity(D_80183AC0, self) == 0) {
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
REDACTED
REDACTED
        camY = g_Tilemap.scrollY.i.hi;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
        if (!(collider.effects & EFFECT_WATER)) {
            self->velocityY = FIX(0.5);
REDACTED
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
REDACTED
REDACTED
REDACTED
REDACTED
            pos = D_801813AC;
REDACTED
            camY = g_Tilemap.scrollY.i.hi;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
                newEntity = AllocEntity(&g_Entities[232], &g_Entities[256]);
                if (newEntity != NULL) {
                    CreateEntityFromEntity(E_MERMAN_UNK0, self, newEntity);
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
            AnimateEntity(D_80183AAC, self);
            if (!self->ext.merman.isUnderwater) {
                if (UnkCollisionFunc3(&D_80183A4C) & 1) {
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
            if (self->velocityY < 0) {
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
                newEntity = AllocEntity(&g_Entities[232], &g_Entities[256]);
                if (newEntity != NULL) {
                    CreateEntityFromEntity(E_MERMAN_UNK1, self, newEntity);
                    newEntity->posX.i.hi -= 6 - ((Random() & 3) * 4);
                    newEntity->velocityX = D_80183B08[self->animFrameIdx];
                }
            } else {
                self->palette = PAL_DRA(0x2B2);
                if (self->velocityY > 0) {
                    func_801D2D40(0x15);
                }
            }
            break;

        case MERMAN_JUMPING_LANDING:
            if (AnimateEntity(D_80183ACC, self) != 0) {
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
            if (self->facingLeft == 0) {
                self->velocityX = FIX(-0.375);
REDACTED
                self->velocityX = FIX(0.375);
REDACTED
            self->ext.merman.timer2 = D_80183A48[Random() & 3];
REDACTED
REDACTED
REDACTED
REDACTED
            AnimateEntity(D_80183A84, self);
            colRet = UnkCollisionFunc2(&D_80183A7C);
REDACTED
                self->facingLeft ^= 1;
REDACTED
            if (self->facingLeft == 0) {
                self->velocityX = FIX(-0.375);
REDACTED
                self->velocityX = FIX(0.375);
REDACTED
REDACTED
                self->posX.val += self->velocityX;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
            if (func_801D2D40(0x15)) {
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
            if (AnimateEntity(D_80183A9C, self) == 0) {
REDACTED
REDACTED
            if (self->animFrameIdx == 4 && self->animFrameDuration == 0) {
                PlaySfxPositional(SFX_FIREBALL_SHOT_C);
REDACTED
REDACTED
                    CreateEntityFromEntity(E_MERMAN_UNK2, self, newEntity);
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
REDACTED
REDACTED
            if (AnimateEntity(D_80183ACC, self) == 0) {
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
            if (self->facingLeft == 0) {
                self->velocityX = FIX(-5.0 / 2.0);
REDACTED
                self->velocityX = FIX(2.5);
REDACTED
REDACTED
            self->velocityY = FIX(-2);
REDACTED
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
            UnkCollisionFunc5(&D_80183A5C);
            if (self->facingLeft != 0) {
                self->velocityX -= FIX(0.03125);
REDACTED
                self->velocityX += FIX(0.03125);
REDACTED
REDACTED
REDACTED
                self->velocityX = 0;
                self->velocityY = FIX(2);
REDACTED
                UnkCollisionFunc3(&D_80183A4C);
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
            func_801D2D40(11);
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
            UnkCollisionFunc3(&D_80183A4C);
            if (AnimateEntity(D_80183ACC, self) == 0) {
                self->velocityY = 0;
REDACTED
REDACTED
            func_801D2D40(11);
REDACTED
REDACTED
REDACTED
REDACTED
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
        if (!(func_801D2D40(21)) && !(self->ext.merman.isUnderwater)) {
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
            self->ext.merman.palette = PAL_DRA(0x2BC);
            self->velocityY = 0;
REDACTED
REDACTED
REDACTED
            if (UnkCollisionFunc3(&D_80183A6C) & 1) {
                if (!(GetSideToPlayer() & 1)) {
                    self->velocityX = FIX(-0.5);
REDACTED
                    self->velocityX = FIX(0.5);
REDACTED
REDACTED
REDACTED
            // fallthrough

        case MERMAN_DYING_END:
            AnimateEntity(D_80183ADC, self); // spinning
REDACTED
REDACTED
            if (!(g_Timer % 8)) {
REDACTED
                if (self->ext.merman.palette == PAL_DRA(0x2C0)) {
                    PlaySfxPositional(SFX_FM_EXPLODE_B);
REDACTED
REDACTED
                        CreateEntityFromEntity(E_MERMAN_UNK3, self, newEntity);
                        newEntity->params = 2;
                    }
                }
            }
            if (self->ext.merman.palette >= PAL_DRA(0x2C5)) {
                DestroyEntity(self);
            }
            break;
        }
        break;
    }
}

REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
        InitializeEntity(D_80180B6C);
REDACTED
REDACTED
REDACTED
REDACTED
        if (self->facingLeft != 0) {
            self->velocityX = 0x10000 | 0x8000; // LINT_IGNORE
        } else {
            self->velocityX = 0xFFFE0000 | 0x8000; // LINT_IGNORE
        }

        self->drawFlags = FLAG_DRAW_ROTX | FLAG_DRAW_ROTY;
        self->rotY = self->rotX = 0x80;

REDACTED
REDACTED
REDACTED
REDACTED
            entity->drawFlags = FLAG_DRAW_ROTX | FLAG_DRAW_ROTY;
            entity->zPriority = self->zPriority + 8;
            entity->rotY = entity->rotX = 192;
        }
    } else {
        AnimateEntity(D_80183AF0, self);
        MoveEntity();

        if (self->rotX < 0x100) {
            self->rotY = self->rotX += 8;
        }

        if (self->flags & FLAG_DEAD) {
            entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
REDACTED
REDACTED
REDACTED
            }
            DestroyEntity(self);
        }
    }
}

// some sort of falling object
void EntityFallingObject(Entity* arg0) {
    if (arg0->step == 0) {
        InitializeEntity(D_80180B60);
        arg0->animCurFrame = 0;
        arg0->hitboxState = 0;
        arg0->zPriority += 4;
        arg0->flags |= FLAG_UNK_2000;
    }
    MoveEntity();
    arg0->velocityY += FIX(5.0 / 32.0);
    if (AnimateEntity(D_80183B04, arg0) == 0) {
        DestroyEntity(arg0);
    }
}

extern u8 D_80183B44[];
extern s32 D_80183B30[];
extern u16 D_80183B48[];

// part of explosion when merman dies
REDACTED
REDACTED
        InitializeEntity(g_InitializeEntityData0);
        self->palette = PAL_OVL(0x2BB);
        self->animSet = ANIMSET_DRA(2);
        self->animCurFrame = D_80183B44[self->params];
        self->velocityY = D_80183B30[self->params];
REDACTED
REDACTED
REDACTED
REDACTED
        self->posY.val += self->velocityY;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
    if (D_80183B48[self->params] < self->animFrameDuration) {
        DestroyEntity(self);
    }
}
