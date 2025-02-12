// SPDX-License-Identifier: AGPL-3.0-or-later
#include "nz0.h"
#include "sfx.h"

typedef struct SubWpnContDebris {
    s16 velX;
    s16 velY;
    u16 params;
    u16 facingLeft;
} SubWpnContDebris;
static SubWpnContDebris D_80182584[] = {
    {0x0000, 0xFFA9, 0x0003, 0x0000}, {0xFFF6, 0xFFBA, 0x0007, 0x0001},
    {0xFFF5, 0xFFC9, 0x0006, 0x0000}, {0x0007, 0xFFB6, 0x0007, 0x0001},
    {0x000A, 0xFFC4, 0x0006, 0x0001}, {0xFFF7, 0xFFD9, 0x0005, 0x0000},
    {0x0008, 0xFFD7, 0x0004, 0x0000}, {0x0002, 0xFFCF, 0x0005, 0x0001},
    {0x0000, 0xFFBE, 0x0007, 0x0001}};
static s32 D_801825CC[] = {
    0x0016, 0x0014, 0x0010, 0x000E, 0x0013, 0x0015, 0x000F, 0x0011, 0x0012};
static u8 D_801825F0[] = {0x01, 0x01, 0x04, 0x01, 0x02, 0x01, 0x05, 0x01,
                          0x02, 0x01, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00};
static s32 D_80182600[] = {FIX(-1), FIX(-1), FIX(-0.5), FIX(-0.25)};

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
        self->drawMode = DRAW_TPAGE;
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

        primIndex = g_api.AllocPrimBuffers(PRIM_GT4, 2);
        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags |= FLAG_HAS_PRIMS;
        self->primIndex = primIndex;
        prim = &g_PrimBuf[primIndex];
        self->ext.prim = prim;

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
                if (!newEntity->params) {
                    if (abs(rnd) > 8) {
                        newEntity->params = 1;
                    }
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
        g_api.PlaySfx(SFX_MAGIC_GLASS_BREAK);
        for (glassPieceTBL = D_80182584, i = 0; i < LEN(D_80182584); i++,
            glassPieceTBL++) {
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

        for (i = 0; i < 96; i++) { // Spawn falling liquid
            newEntity = AllocEntity(
                &g_Entities[UNK_ENTITY_51], &g_Entities[UNK_ENTITY_100]);
            if (newEntity != NULL) {
                CreateEntityFromEntity(E_FALLING_LIQUID, self, newEntity);
                rndPosX = (Random() & 0x1F) - 16;
                rndPosY = -(Random() & 0x3F) - 16;
                newEntity->posX.i.hi += rndPosX;
                newEntity->posY.i.hi += rndPosY;
                newEntity->rotZ = ratan2(rndPosY, rndPosX);
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
            if (self->params == 0) {
                newEntity->animCurFrame++;
                self->params |= 1;
            } else {
                break;
            }
        } else {
            self->params = 0;
        }
        if (g_pads[1].pressed & PAD_CIRCLE) {
            if (self->step_s == 0) {
                newEntity->animCurFrame--;
                self->step_s |= 1;
                break;
            }
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
        self->drawFlags = FLAG_DRAW_ROTZ;
        self->velocityX = self->ext.subwpnContGlass.velX * 0x1000;
        self->velocityX -= (Random() * 0x100) + FIX(-0.5);
        self->velocityY -= (Random() & 0x1F) * 0x1000;
        break;

    case 1:
        MoveEntity();
        self->velocityY += FIX(0.125);

        if (self->velocityX != 0) {
            if (self->facingLeft) {
                self->rotZ += 0x10;
            } else {
                self->rotZ -= 0x10;
            }
        } else {
            if (self->facingLeft) {
                self->rotZ -= 0x10;
            } else {
                self->rotZ += 0x10;
            }
        }
        break;
    }
}

// falling liquid from subweapons container
void func_801C7654(Entity* entity) {
    Collider collider;

    switch (entity->step) {
    case 0:
        InitializeEntity(g_EInitParticle);
        entity->animSet = ANIMSET_DRA(2);
        entity->palette = 0x816D;
        entity->drawMode = DRAW_UNK_40 | DRAW_TPAGE2 | DRAW_TPAGE;
        entity->velocityX = rcos(entity->rotZ) * 0x10;
        entity->velocityY = rsin(entity->rotZ) * 0x10;
        break;

    case 1:
        AnimateEntity(D_801825F0, entity);
        MoveEntity();
        entity->velocityY += FIX(0.125);

        g_api.CheckCollision(
            entity->posX.i.hi, entity->posY.i.hi + 8, &collider.effects, 0);

        if (collider.effects & EFFECT_SOLID) {
            entity->drawFlags = FLAG_DRAW_ROTY;
            entity->rotY = 0x100;
            entity->velocityY = FIX(0.25);
            entity->velocityX *= 8;
            entity->step++;
        }
        break;

    case 2:
        MoveEntity();
        entity->rotY -= 8;
        if (!(entity->rotY << 0x10)) {
            DestroyEntity(entity);
        }
        break;
    }
}

// Liquid bubbles from the Subweapon container
void func_801C77B8(Entity* entity) {
    s16 temp_v1_2;

    switch (entity->step) {
    case 0:
        InitializeEntity(g_EInitSubwpnClochePieces);
        entity->drawFlags = FLAG_DRAW_ROTX | FLAG_DRAW_ROTY;
        entity->rotY = 0x100;
        entity->rotX = 0x100;
        entity->velocityX = 0;
        entity->animCurFrame = entity->params + 8;
        entity->velocityY = D_80182600[entity->params];
        break;

    case 1:
        MoveEntity();
        temp_v1_2 = entity->rotY - 8;
        entity->velocityY -= 0x400;
        entity->rotY = temp_v1_2;
        entity->rotX = temp_v1_2;

        if ((temp_v1_2 << 0x10) == 0) {
            DestroyEntity(entity);
        }
        break;
    }
}

void func_801C7884(Entity* entity) {
    u16 params = entity->params;

    switch (entity->step) {
    case 0:
        InitializeEntity(g_EInitObtainable);
        entity->hitboxState = 0;

    case 1:
        MoveEntity();
        AnimateEntity(g_SubweaponAnimPrizeDrop[params], entity);

        entity->velocityY = rsin(entity->rotZ) * 2;
        entity->rotZ += 0x20;

        if (entity[-1].step != 1) {
            entity->entityId = E_PRIZE_DROP;
            entity->pfnUpdate = EntityPrizeDrop;
            entity->animFrameDuration = 0;
            entity->animFrameIdx = 0;
            entity->step = 0;
            entity->hitboxState = 1;
        }
    }
}
