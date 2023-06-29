#include "np3.h"

void EntityZombie(Entity* self) {
    Entity* newEntity;
    s32 temp_a0;

    if ((self->flags & 0x100) && (self->step < 4)) {
        func_801C2598(NA_SE_EN_ZOMBIE_EXPLODE);
        self->hitboxState = 0;
        // Spawn Zombie explosion
        newEntity = AllocEntity(D_8007D858, &D_8007D858[32]);
        if (newEntity != NULL) {
            CreateEntityFromEntity(0x4D, self, newEntity);
            newEntity->zPriority = self->zPriority + 1;
            newEntity->subId = 3;
            newEntity->posY.i.hi += 12;
        }
        DestroyEntity(self);
        return;
    }

    switch (self->step) {
    case 0:
        InitializeEntity(D_80180B08);
        self->hitboxWidth = 8;
        self->hitboxOffY = 0x10;
        self->hitboxHeight = 0;
        self->zPriority += 4;
        if (g_blinkTimer & 1) {
            self->palette++;
        }
        if (Random() & 1) {
            self->palette++;
        }
        self->animCurFrame = 0;
        break;

    case 1:
        if (func_801BC8E4(D_801825BC) & 1) {
            self->facing = (GetPlayerSide() & 1) ^ 1;
            self->step++;
        }
        break;

    case 2:
        if (AnimateEntity(D_80182594, self) == 0) {
            SetStep(3);
        }
        if (self->animFrameDuration == 0) {
            self->hitboxOffY -= 2;
            self->hitboxHeight += 2;
        }
        break;

    case 3:
        AnimateEntity(D_8018258C, self);
        temp_a0 = func_801BCB5C(&D_801825CC);
        if (self->facing != 0) {
            self->accelerationX = 0x8000;
        } else {
            self->accelerationX = -0x8000;
        }

        if (temp_a0 & 0xC0) {
            self->hitboxState = 0;
            SetStep(4);
        }
        break;

    case 4:
        if (AnimateEntity(D_801825A8, self) == 0) {
            DestroyEntity(self);
        }
        break;
    }
}

/*
 * An invisible entity that is responsible for spawning the "floor
 * zombies" that come up from the ground and swarm the player.
 * Every 32 to 95 frames, it will alternate spawning a zombie
 * on the right side or left side of the screen.
 * The exact position a zombie is spawned in is also randomized.
 */
void EntityZombieSpawner(Entity* self) {
    s32 distCameraEntity;
    Entity* newEntity;
    s32 rnd;

    if (self->step == 0) {
        InitializeEntity(D_80180A60);
        self->ext.generic.unk80.modeS16.unk0 = 1;
        self->flags &= 0x2000;
    }

    if (D_8003BE23 != 0) {
        self->posX.i.hi = 128;
        if (--self->ext.generic.unk80.modeS16.unk0 == 0) {
            newEntity = AllocEntity(D_8007A958, &D_8007A958[8]);
            if (newEntity != NULL) {
                CreateEntityFromEntity(0x42, self, newEntity);
                rnd = (Random() & 0x3F) + 96;

                if (self->ext.generic.unk88.unk != 0) {
                    newEntity->posX.i.hi += rnd;
                } else {
                    newEntity->posX.i.hi -= rnd;
                }
                newEntity->posY.i.hi -= 48;
                self->ext.generic.unk88.unk ^= 1;

                // Zombies are prevented from spawning too close to the
                // edges of the room.
                distCameraEntity = g_Camera.posX.i.hi + newEntity->posX.i.hi;
                if ((distCameraEntity < (g_CurrentRoom.x + 128)) ||
                    ((g_CurrentRoom.width - 128) < distCameraEntity)) {
                    DestroyEntity(newEntity);
                }
            }
            self->ext.generic.unk80.modeS16.unk0 = (Random() & 0x3F) + 32;
        }
    }
}
