/*
 * File: 297C8.c
 * Overlay: CHI
 * Description: Abandoned Mine
 */

#include "chi.h"

// D_801816EC
static u8 AnimFrames_Running[] = {
    0x06, 0x01, 0x03, 0x02, 0x02, 0x03, 0x02, 0x04, 0x03, 0x05, 0x06, 0x06, 0x03, 0x05, 0x02, 0x04,
    0x02, 0x03, 0x03, 0x02, 0x00, 0x00, 0x00, 0x00
};

extern EntityInit EntityInit_801806AC;

// E_GREMLIN
// func_801A97C8
// https://decomp.me/scratch/kNQO9
// PSP:func_psp_09248BD0:Match
// https://decomp.me/scratch/bmBPH
void EntityGremlin(Entity* self)
{
    const int MovementSpeed = 0x10;
    const int HurtDuration = 0x20;
    const int DecelerateSpeed = 16;
    const int AnimFrameDeath = 0x13;

    enum Step {
        Init = 0,
        Idle = 1,
        HurtDeath = 2,
        Debug = 0xFF,
    };

    Collider collider;
    Entity* entity;
    s32 xPos;
    s32 yPos;

    // Check for being hurt
    if ((self->hitFlags & 3) && (self->step != HurtDeath)) {
        PlaySfxWithPosArgs(NA_SE_EN_GREMLIN_HURT);
        SetStep(HurtDeath);
    }
    // Check for being dead
    if (self->flags & FLAG_DEAD) {
        if (self->step != HurtDeath) {
            self->hitboxState = 0;
            SetStep(HurtDeath);
        }
    }
    switch (self->step) {
        case Init:
            InitializeEntity(&EntityInit_801806AC);
            self->animCurFrame = 1;
            self->hitboxOffX = 6;
            self->facingLeft = self->params;

            entity = self + 1;
            CreateEntityFromCurrentEntity(E_GREMLIN_EFFECT, entity);
            entity->params = 0; // Glow effect
            entity->zPriority = self->zPriority - 2;

            entity = self + 2;
            CreateEntityFromCurrentEntity(E_GREMLIN_EFFECT, entity);
            entity->params = 1; // Fire (in spoon) effect
            entity->zPriority = self->zPriority - 1;
            // fallthrough
        case Idle:
            if (!self->step_s) {
                if (self->facingLeft) {
                    self->velocityX = FIX(1);
                } else {
                    self->velocityX = FIX(-1);
                }
                self->velocityY = FIX(1);
                self->step_s += 1;
            }

            AnimateEntity(&AnimFrames_Running, self);
            MoveEntity();

            // Update to correct facing based on movement
            if (self->velocityX > 0) {
                self->facingLeft = true;
            } else {
                self->facingLeft = false;
            }

            // Horizontal Movement
            xPos = self->posX.i.hi;
            yPos = self->posY.i.hi;
            if (self->velocityX > 0) {
                xPos += MovementSpeed;
                g_api.CheckCollision(xPos, yPos, &collider, 0);
                if (collider.effects & 1) {
                    // Collided with tile
                    self->posX.i.hi += collider.unk14;
                    self->velocityX = FIX(-1);
                } else {
                    // Collided with right edge of room
                    xPos += g_Tilemap.scrollX.i.hi;
                    if (g_Tilemap.width < xPos) {
                        self->velocityX = FIX(-1);
                    }
                }
            } else {
                xPos -= MovementSpeed;
                g_api.CheckCollision(xPos, yPos, &collider, 0);
                if (collider.effects & 1) {
                    // Collided with tile
                    self->posX.i.hi += collider.unk1C;
                    self->velocityX = FIX(1);
                } else {
                    // Collided with left edge of room
                    xPos += g_Tilemap.scrollX.i.hi;
                    if (xPos < g_Tilemap.x) {
                        self->velocityX = FIX(1);
                    }
                }
            }

            // Vertical Movement
            xPos = self->posX.i.hi;
            yPos = self->posY.i.hi;
            if (self->velocityY > 0) {
                yPos += MovementSpeed;
                g_api.CheckCollision(xPos, yPos, &collider, 0);
                if (collider.effects & 1) {
                    // Collided with tile
                    self->posX.i.hi += collider.unk18;
                    self->velocityY = FIX(-1);
                } else {
                    // Collided with bottom edge of room
                    yPos += g_Tilemap.scrollY.i.hi;
                    if (g_Tilemap.height < yPos) {
                        self->velocityY = FIX(-1);
                    }
                }
            } else {
                yPos -= MovementSpeed;
                g_api.CheckCollision(xPos, yPos, &collider, 0);
                if (collider.effects & 1) {
                    // Collided with tile
                    self->posX.i.hi += collider.unk20;
                    self->velocityY = FIX(1);
                } else {
                    // Collided with top edge of room
                    yPos += g_Tilemap.scrollY.i.hi;
                    if (yPos < g_Tilemap.y) {
                        self->velocityY = FIX(1);
                    }
                }
            }

            // Check to drop flame
            if (!self->ext.gremlin.timer) {
                PlaySfxWithPosArgs(NA_SE_EN_GREMLIN_FLAME);

                // Set next time
                self->ext.gremlin.timer = (Random() & 0x1F) + 0x28;

                // Spawn
                entity = AllocEntity(&g_Entities[160], &g_Entities[192]);
                if (entity != NULL) {
                    CreateEntityFromEntity(E_GREMLIN_FIRE, self, entity);
                }
            } else {
                self->ext.gremlin.timer--;
            }
            break;

        case HurtDeath:
            // Wait for a time (after which, check for death)
            if (!self->step_s) {
                self->ext.gremlin.timer = HurtDuration;
                self->step_s += 1;
            }

            self->animCurFrame = AnimFrameDeath;
            MoveEntity();

            // Slow movement
            self->velocityX -= self->velocityX / DecelerateSpeed;
            self->velocityY -= self->velocityY / DecelerateSpeed;

            // If wait time is over, check for death
            if (!--self->ext.gremlin.timer) {
                SetStep(Idle);

                // Check if dead
                if (self->flags & FLAG_DEAD) {
                    PlaySfxWithPosArgs(NA_SE_EN_GREMLIN_DEATH);

                    // Spawn fire particles
                    entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
                    if (entity != NULL) {
                        CreateEntityFromEntity(E_EXPLOSION, self, entity);
                        entity->params = 1;
                    }
                    DestroyEntity(self);
                    return;
                }
            }
            break;

        case Debug:
            FntPrint("charal %x\n", self->animCurFrame);
            if (g_pads[1].pressed & PAD_SQUARE) {
                if (self->params) {
                    break;
                }
                self->animCurFrame++;
                self->params |= true;
            } else {
                self->params = false;
            }
            if (g_pads[1].pressed & PAD_CIRCLE) {
                if (self->step_s) {
                    break;
                }
                self->animCurFrame--;
                self->step_s |= true;
            } else {
                self->step_s = false;
            }
            break;
    }
}

// D_80181704
static u8 AnimFrames_Fire[] = {
    0x01, 0x07, 0x01, 0x08, 0x01, 0x09, 0x01, 0x0A, 0x01, 0x0B, 0x01, 0x0C, 0x01, 0x0D, 0x01, 0x0E,
    0x01, 0x0F, 0x01, 0x10, 0x00, 0x00, 0x00, 0x00
};

// D_8018171C
static u8 AnimFrames_Glow[] = {
    0x01, 0x11, 0x01, 0x12, 0x00, 0x00, 0x00, 0x00
};

// E_GREMLIN_EFFECT
// func_801A9D40
void EntityGremlinEffect(Entity* self)
{
    const int AnimFrameGremlinHurt = 0x13;
    const int GremlinHurtFrameOffsetY = -0x10;

    enum Step {
        Init = 0,
        Glow = 1,
        Fire = 2,
    };

    Entity* entityGremlin;

    switch (self->step) {
        case Init:
            InitializeEntity(&EntityInit_801806AC);
            self->hitboxState = 0;
            self->flags |= FLAG_UNK_2000;

            // Check whether to be fire or glow
            if (self->params != 0) {
                // Fire init
                self->step = Fire;
                break;
            }
            // Glow init
            self->step = Glow;
            self->drawMode = DRAW_TPAGE | DRAW_TPAGE2;
            self->unk6C = 0xC0;
            self->drawFlags = FLAG_DRAW_UNK8;
            break;

        case Glow:
            AnimateEntity(&AnimFrames_Glow, self);

            entityGremlin = self - 1;
            self->facingLeft = entityGremlin->facingLeft;
            self->posX.i.hi = entityGremlin->posX.i.hi;
            self->posY.i.hi = entityGremlin->posY.i.hi;
            if (entityGremlin->animCurFrame == AnimFrameGremlinHurt) {
                self->posY.i.hi += GremlinHurtFrameOffsetY;
            }
            if (entityGremlin->entityId != E_GREMLIN) {
                DestroyEntity(self);
            }
            break;

        case Fire:
            AnimateEntity(&AnimFrames_Fire, self);

            entityGremlin = self - 2;
            self->facingLeft = entityGremlin->facingLeft;
            self->posX.i.hi = entityGremlin->posX.i.hi;
            self->posY.i.hi = entityGremlin->posY.i.hi;
            if (entityGremlin->animCurFrame == AnimFrameGremlinHurt) {
                self->posY.i.hi += GremlinHurtFrameOffsetY;
            }
            if (entityGremlin->entityId != E_GREMLIN) {
                DestroyEntity(self);
            }
    }
}

// D_80181724
static u8 AnimFrames_FireIdle[] = {
    0x02, 0x14, 0x02, 0x15, 0x02, 0x16, 0x02, 0x17, 0x02, 0x18, 0x02, 0x19, 0x02, 0x1A, 0x02, 0x1B,
    0x02, 0x1C, 0x02, 0x1D, 0x00, 0x00, 0x00, 0x00
};

extern EntityInit EntityInit_801806C4;

// E_GREMLIN_FIRE
// func_801A9E94
void EntityGremlinFire(Entity* self)
{
    const int FireDuration = 0x400;
    const int BounceSpeed = 0x40;

    enum Step {
        Init = 0,
        Idle = 1,
        Death = 2,
    };

    enum Death_Substep {
        Death_Init = 0,
        Death_Shrink = 1,
    };

    if (self->flags & FLAG_DEAD) {
        if (self->step != Death) {
            self->hitboxState = 0;
            SetStep(Death);
        }
    }

    switch (self->step) {
        case Init:
            InitializeEntity(&EntityInit_801806C4);
            self->ext.gremlinFire.timer = FireDuration;
            // fallthrough
        case Idle:
            AnimateEntity(&AnimFrames_FireIdle, self);
            MoveEntity();

            // Bounce up and down slightly
            self->velocityY = rcos(self->rotZ);
            self->rotZ += BounceSpeed;
            self->ext.gremlinFire.timer--;
            if (self->ext.gremlinFire.timer == 0) {
                self->hitboxState = 0;
                SetStep(Death);
            }
            break;

        case Death:
            switch (self->step_s) {
                case Death_Init:
                    self->drawFlags = FLAG_DRAW_ROTX | FLAG_DRAW_ROTY;
                    self->rotX = 0x100;
                    self->rotY = 0x100;
                    self->flags |= FLAG_DESTROY_IF_OUT_OF_CAMERA;
                    self->step_s++;
                    // fallthrough
                case Death_Shrink:
                    AnimateEntity(&AnimFrames_FireIdle, self);
                    self->rotX -= 8;
                    self->rotY -= 6;
                    if (self->rotX == 0) {
                        DestroyEntity(self);
                    }
                    break;
            }
            break;
    }
}