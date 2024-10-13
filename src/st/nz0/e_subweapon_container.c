// SPDX-License-Identifier: AGPL-3.0-or-later
#include "nz0.h"
#include "sfx.h"

typedef struct SubWpnContDebris {
    s16 posX;
    s16 posY;
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
    s16 primIndex;
    s32 rnd;
    s32 rndPosX;
    s32 rndPosY;
    s32 absRnd;
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
        CreateEntityFromEntity(
            E_func_801C7884, self, &self[1]); // Create SubWeapon
        self[1].posY.i.hi -= 72;
        self[1].params = D_801825CC[self->params];
        self[1].zPriority = self->zPriority - 2;

        primIndex = g_api.AllocPrimitives(PRIM_GT4, 2);
        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->primIndex = primIndex;
        prim = &g_PrimBuf[primIndex];
        *(s32*)&self->ext.generic.unk7C = prim;
        self->flags |= FLAG_HAS_PRIMS;
        while (prim != NULL) {
            prim->priority = self->zPriority + 0xFFFF;
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
                if (newEntity->params == 0) {
                    absRnd = abs(rnd);
                    if (absRnd >= 9) {
                        newEntity->params = 1;
                    }
                }
                newEntity->zPriority = self->zPriority - 1;
            }
        }

        if (self->hitFlags != 0) { // container got hit!
            self->step++;
        }
        break;

    case SUBWPNCONT_BREAK: // Break container into pieces
        // Spawn falling glass pieces
        glassPieceTBL = D_80182584;
        i = 0;
        g_api.FreePrimitives(self->primIndex);
        self->flags &= ~FLAG_HAS_PRIMS;
        g_api.PlaySfx(SFX_MAGIC_GLASS_BREAK);
        while (i < LEN(D_80182584)) {
            newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (newEntity != NULL) {
                CreateEntityFromEntity(E_FALLING_GLASS, self, newEntity);
                newEntity->posX.i.hi += glassPieceTBL->posX;
                newEntity->posY.i.hi += glassPieceTBL->posY;
                newEntity->ext.generic.unk84.S16.unk0 = glassPieceTBL->posX;
                newEntity->params = glassPieceTBL->params;
                newEntity->facingLeft = glassPieceTBL->facingLeft;
                newEntity->ext.generic.unk84.S16.unk2 = self->params;
            }
            glassPieceTBL++;
            i++;
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
void func_801C7538(Entity* entity) {
    s32 new_var;
    s16 var_v0;

    switch (entity->step) {
    case 0:
        InitializeEntity(g_EInitSubwpnClochePieces);
        entity->drawFlags = FLAG_DRAW_ROTZ;
        entity->animCurFrame = entity->params;
        entity->palette += entity->ext.generic.unk84.S16.unk2;
        entity->velocityX = entity->ext.generic.unk84.S16.unk0 << 12;
        entity->velocityX += 0x8000 - (Random() << 8);
        entity->velocityY -= (Random() & 0x1F) << 12;
        break;

    case 1:
        MoveEntity();
        entity->velocityY += FIX(0.125);

        if (entity->velocityX != 0) {
            if (entity->facingLeft == 0) {
                new_var = (u16)entity->rotZ - 16;
                var_v0 = new_var;
            } else {
                var_v0 = entity->rotZ + 16;
            }
        } else if (entity->facingLeft != 0) {
            var_v0 = entity->rotZ - 16;
        } else {
            var_v0 = entity->rotZ + 16;
        }

        entity->rotZ = var_v0;
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
