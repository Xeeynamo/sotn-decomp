// SPDX-License-Identifier: AGPL-3.0-or-later
#include "nz0.h"

typedef struct SubWpnContDebris {
    s16 velX;
    s16 velY;
    s16 params;
    s16 facingLeft;
} SubWpnContDebris;

extern u8* g_MariaSubweaponAnimPrizeDrop[];
extern u8* g_SubweaponAnimPrizeDrop[];

static SubWpnContDebris D_80182584[] = {
    {0, -87, 3, false}, {-10, -70, 7, true}, {-11, -55, 6, false},
    {7, -74, 7, true},  {10, -60, 6, true},  {-9, -39, 5, false},
    {8, -41, 4, false}, {2, -49, 5, true},   {0, -66, 7, true},
};
static s32 D_801825CC[] = {22, 20, 16, 14, 19, 21, 15, 17, 18};

// SubWeapons floating in the breakable container
typedef enum {
    SUBWPNCONT_INIT,
    SUBWPNCONT_IDLE,
    SUBWPNCONT_BREAK,
    SUBWPNCONT_DEBUG = 255
} SUBWPNCONT_STEPS;

void EntitySubWeaponContainer(Entity* self) {
    SubWpnContDebris* glassPieceTBL;
    Entity* newEntity;
    Primitive* prim;
    s32 primIndex;
    s32 rnd;
    s32 rndPosX;
    s32 rndPosY;
    s32 i;
    s32 pad[23];

    switch (self->step) {
    case SUBWPNCONT_INIT:
        InitializeEntity(g_EInitSubwpnCloche);
        self->blendMode = BLEND_TRANSP;
        self->animCurFrame = 1;
        self->zPriority = 0x70;
        self->hitboxWidth = 14;
        self->hitboxHeight = 32;
        self->hitboxOffY = -0x38;
        self->hitboxOffX = 0;
        self->hitboxState = 2;
        self->palette += self->params;
        newEntity = self + 1;
        CreateEntityFromEntity(
            E_func_801C7884, self, newEntity); // Create SubWeapon
        newEntity->posY.i.hi -= 72;
        newEntity->params = D_801825CC[self->params];
        newEntity->zPriority = self->zPriority - 2;

        primIndex = g_api.AllocPrimitives(PRIM_GT4, 2);
        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags |= FLAG_HAS_PRIMS;
        self->primIndex = primIndex;
        prim = &g_PrimBuf[primIndex];
        self->ext.subwpnContGlass.unk7C = prim;

        while (prim != NULL) {
            prim->priority = self->zPriority - 1;
            prim->drawMode = DRAW_HIDE;
            prim = prim->next;
        }
        break;

    case SUBWPNCONT_IDLE: // Spawn Liquid bubbles
        if (!(g_Timer & 0xF)) {
            newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (newEntity != NULL) {
                CreateEntityFromEntity(E_LIQUID_BUBBLES, self, newEntity);
                rnd = (Random() & 0x18) - 12;
                newEntity->posX.i.hi += rnd;
                newEntity->posY.i.hi -= 30;
                newEntity->params = Random() & 3;
                if (!newEntity->params && abs(rnd) > 8) {
                    newEntity->params = 1;
                }
                newEntity->zPriority = self->zPriority - 1;
            }
        }
        if (self->hitFlags) { // container got hit!
            self->step++;
        }
        break;

    case SUBWPNCONT_BREAK: // Break container into pieces
        // Spawn falling glass pieces

        g_api.FreePrimitives(self->primIndex);
        self->flags &= ~FLAG_HAS_PRIMS;
        g_api.PlaySfx(SFX_SUBWEAPON_CONTAINER_BREAK);
        glassPieceTBL = D_80182584;
        for (i = 0; i < LEN(D_80182584); i++, glassPieceTBL++) {
            newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (newEntity != NULL) {
                CreateEntityFromEntity(E_FALLING_GLASS, self, newEntity);
                newEntity->posX.i.hi += glassPieceTBL->velX;
                newEntity->posY.i.hi += glassPieceTBL->velY;
                newEntity->ext.subwpnContGlass.velX = glassPieceTBL->velX;
                newEntity->params = glassPieceTBL->params;
                newEntity->facingLeft = glassPieceTBL->facingLeft;
                newEntity->ext.subwpnContGlass.palette = self->params;
            }
        }

        for (i = 0; i < 0x60; i++) { // Spawn falling liquid
            newEntity =
                AllocEntity(&g_Entities[UNK_ENTITY_51], &g_Entities[256]);
            if (newEntity != NULL) {
                CreateEntityFromEntity(E_FALLING_LIQUID, self, newEntity);
                rndPosX = (Random() & 0x1F) - 16;
                rndPosY = -(Random() & 0x3F) - 16;
                newEntity->posX.i.hi += rndPosX;
                newEntity->posY.i.hi += rndPosY;
                newEntity->rotate = ratan2(rndPosY, rndPosX);
                newEntity->zPriority = self->zPriority + 1;
            }
        }
        PlaySfxPositional(SFX_GLASS_BREAK_E);
        self->hitboxState = 0;
        self->animCurFrame = 2;
        self->step++;
        break;

    case SUBWPNCONT_DEBUG:
        /**
         * Debug: Press SQUARE / CIRCLE on the second controller
         * to advance/rewind current animation frame
         * NOTE: THIS IS DIFFERENT FROM NORMAL CASES OF THIS
         * We are incrementing newEntity's animationFrame, not self's!
         */
        FntPrint("charal %x\n", self->animCurFrame);
        if (g_pads[1].pressed & PAD_SQUARE) {
            if (self->params) {
                break;
            }
            newEntity->animCurFrame++;
            self->params |= 1;
        } else {
            self->params = 0;
        }
        if (g_pads[1].pressed & PAD_CIRCLE) {
            if (self->step_s) {
                break;
            }
            newEntity->animCurFrame--;
            self->step_s |= 1;
        } else {
            self->step_s = 0;
        }
        break;
    }
}

// Subweapon container falling glass pieces
void EntitySubWpnContGlass(Entity* self) {
    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitSubwpnClochePieces);
        self->animCurFrame = self->params;
        self->palette += self->ext.subwpnContGlass.palette;
        self->drawFlags = ENTITY_ROTATE;
        self->velocityX = self->ext.subwpnContGlass.velX * 0x1000;
        self->velocityX -= (Random() * 0x100) - FIX(0.5);
        self->velocityY -= (Random() & 0x1F) * 0x1000;
        break;

    case 1:
        MoveEntity();
        self->velocityY += FIX(0.125);
        if (self->velocityX != 0) {
            if (self->facingLeft) {
                self->rotate += 0x10;
            } else {
                self->rotate -= 0x10;
            }
        } else {
            if (self->facingLeft) {
                self->rotate -= 0x10;
            } else {
                self->rotate += 0x10;
            }
        }
        break;
    }
}

static u8 D_801825F0[] = {1, 1, 4, 1, 2, 1, 5, 1, 2, 1, 3, 1, 0, 0};
static s32 D_80182600[] = {FIX(-1), FIX(-1), FIX(-0.5), FIX(-0.25)};

// falling liquid from subweapons container
void func_801C7654(Entity* self) {
    Collider collider;
    s32 x, y;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitParticle);
        self->animSet = ANIMSET_DRA(2);
        self->palette = PAL_FLAG(PAL_CC_RED_EFFECT_B);
        self->blendMode = BLEND_TRANSP | BLEND_QUARTER;
        self->velocityX = rcos(self->rotate) * 0x10;
        self->velocityY = rsin(self->rotate) * 0x10;
        break;

    case 1:
        AnimateEntity(D_801825F0, self);
        MoveEntity();
        self->velocityY += FIX(0.125);
        x = self->posX.i.hi;
        y = self->posY.i.hi + 8;
        g_api.CheckCollision(x, y, &collider, 0);
        if (collider.effects & EFFECT_SOLID) {
            self->drawFlags = ENTITY_SCALEY;
            self->scaleY = 0x100;
            self->velocityX *= 8;
            self->velocityY = FIX(0.25);
            self->step++;
        }
        break;

    case 2:
        MoveEntity();
        self->scaleY -= 8;
        if (!self->scaleY) {
            DestroyEntity(self);
        }
        break;
    }
}

// Liquid bubbles from the Subweapon container
void func_801C77B8(Entity* self) {
    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitSubwpnClochePieces);
        self->animCurFrame = self->params + 8;
        self->drawFlags = ENTITY_SCALEX | ENTITY_SCALEY;
        self->scaleX = self->scaleY = 0x100;
        self->velocityX = 0;
        self->velocityY = D_80182600[self->params];
        break;

    case 1:
        MoveEntity();
        self->velocityY -= 0x400;
        self->scaleX = self->scaleY -= 8;
        if (!self->scaleX) {
            DestroyEntity(self);
        }
        break;
    }
}

void func_801C7884(Entity* self) {
    Entity* tempEntity;
    s32 params = self->params;

#ifdef VERSION_US
#define g_PlayableCharacter PLAYER_ALUCARD
#endif

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitObtainable);
        self->hitboxState = 0;
        /* fallthrough */
    case 1:
        if (g_PlayableCharacter == PLAYER_MARIA) {
            if (params >= 14 && params < 23) {
                switch (params) {
                case 14:
                    params = 0xF;
                    break;
                case 15:
                    params = 0xE;
                    break;
                case 21:
                    params = 0x10;
                    break;
                case 17:
                    params = 0x11;
                    break;
                case 19:
                    params = 0x13;
                    break;
                default:
                    params = 0;
                    break;
                }
            }
        }
        MoveEntity();
        if (g_PlayableCharacter == PLAYER_MARIA) {
            AnimateEntity(g_MariaSubweaponAnimPrizeDrop[params], self);
        } else {
            AnimateEntity(g_SubweaponAnimPrizeDrop[params], self);
        }
        self->velocityY = rsin(self->rotate) * 2;
        self->rotate += 0x20;

        tempEntity = self - 1;
        if (tempEntity->step != 1) {
            self->entityId = E_PRIZE_DROP;
            self->pfnUpdate = EntityPrizeDrop;
            self->poseTimer = 0;
            self->pose = 0;
            self->step = 0;
            self->hitboxState = 1;
        }
    }
}
