#include "no3.h"

void EntityZombie(Entity* self) {
    Entity* newEntity;
    s32 temp_a0;

    if ((self->flags & 0x100) && (self->step < 4)) {
        func_801CAD28(NA_SE_EN_ZOMBIE_EXPLODE);
        self->hitboxState = 0;
        // Spawn Zombie explosion
        newEntity = AllocEntity(D_8007D858, &D_8007D858[32]);
        if (newEntity != NULL) {
            CreateEntityFromEntity(0x62, self, newEntity);
            newEntity->zPriority = self->zPriority + 1;
            newEntity->params = 3;
            newEntity->posY.i.hi += 12;
        }
        DestroyEntity(self);
        return;
    }

    switch (self->step) {
    case 0:
        InitializeEntity(D_80180BA8);
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
        if (func_801C5074(&D_80183CAC) & 1) {
            self->facing = (GetSideToPlayer() & 1) ^ 1;
            self->step++;
        }
        break;

    case 2:
        if (AnimateEntity(D_80183C84, self) == 0) {
            SetStep(3);
        }
        if (self->animFrameDuration == 0) {
            self->hitboxOffY -= 2;
            self->hitboxHeight += 2;
        }
        break;

    case 3:
        AnimateEntity(D_80183C7C, self);
        temp_a0 = func_801C52EC(&D_80183CBC);
        if (self->facing != 0) {
            self->velocityX = 0x8000;
        } else {
            self->velocityX = -0x8000;
        }

        if (temp_a0 & 0xC0) {
            self->hitboxState = 0;
            SetStep(4);
        }
        break;

    case 4:
        if (AnimateEntity(D_80183C98, self) == 0) {
            DestroyEntity(self);
        }
        break;
    }
}

const u32 rodataPadding_377CC[] = {0, 0};

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
        InitializeEntity(D_80180AD0);
        self->ext.generic.unk80.modeS16.unk0 = 1;
        self->flags &= FLAG_UNK_2000;
    }

    if (D_8003BE23 != 0) {
        self->posX.i.hi = 128;
        if (--self->ext.generic.unk80.modeS16.unk0 == 0) {
            newEntity = AllocEntity(D_8007A958, &D_8007A958[8]);
            if (newEntity != NULL) {
                CreateEntityFromEntity(0x4C, self, newEntity);
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

INCLUDE_ASM("asm/us/st/no3/nonmatchings/564B0", func_801D6880);

INCLUDE_ASM("asm/us/st/no3/nonmatchings/564B0", func_801D6C68);

POLY_GT4* func_801D6DB8(POLY_GT4* poly) {
    while (poly != NULL) {
        if (poly->p3 != 0) {
            poly = (POLY_GT4*)poly->tag;
        } else {
            return poly;
        }
    }
    return NULL;
}

POLY_GT4* func_8019C43C(POLY_GT4* poly, u8 index) {
    if (poly) {
        s32 index_ = index;
    loop_2:
        if (poly->p3 == 0) {
            POLY_GT4* var_v0 = NULL;
            POLY_GT4* firstPoly = poly;
            s32 i = 1;
            if (i < index_) {
                do {
                    poly = (POLY_GT4*)poly->tag;
                    if (!poly)
                        return NULL;
                } while (poly->p3 == 0 && ++i < index);
            }
            var_v0 = firstPoly;
            if (i == index_)
                return var_v0;
        }
        poly = (POLY_GT4*)poly->tag;
        if (poly) {
            goto loop_2;
        }
    }
    return NULL;
}

POLY_GT4* func_801D6E64(POLY_GT4* startPoly, s32 count) {
    POLY_GT4* poly;
    s8 unk;
    s32 i;

    if (startPoly->p3) {
        startPoly->p3 = 0;
    } else {
        startPoly->p3 = 1;
    }

    poly = startPoly;
    for (i = 0; i < count; i++) {
        if (poly->p3) {
            poly->pad3 &= ~8;
            unk = 0;
        } else {
            poly->pad3 |= 8;
            unk = 1;
        }

        poly = (POLY_GT4*)poly->tag;
        if (poly == 0)
            return 0;
        poly->p3 = unk;
    }

    return poly;
}

void func_801D6EEC(POLY_GT4* arg0) {
    arg0->p1 = 0;
    arg0->p2 = 0;
    arg0->p3 = 0;
    ((POLY_GT4*)arg0->tag)->x1 = 0;
    ((POLY_GT4*)arg0->tag)->y1 = 0;
    ((POLY_GT4*)arg0->tag)->y0 = 0;
    ((POLY_GT4*)arg0->tag)->x0 = 0;
    ((POLY_GT4*)arg0->tag)->clut = 0;
    *(u16*)&((POLY_GT4*)arg0->tag)->u0 = 0;
    *(u16*)&((POLY_GT4*)arg0->tag)->b1 = 0;
    *(u16*)&((POLY_GT4*)arg0->tag)->r1 = 0;
    *(u16*)&((POLY_GT4*)arg0->tag)->u1 = 0;
    ((POLY_GT4*)arg0->tag)->tpage = 0;
    *(u16*)&((POLY_GT4*)arg0->tag)->r2 = 0;
    *(u16*)&((POLY_GT4*)arg0->tag)->b2 = 0;
    ((POLY_GT4*)arg0->tag)->u2 = 0;
    ((POLY_GT4*)arg0->tag)->v2 = 0;
    ((POLY_GT4*)arg0->tag)->r3 = 0;
    ((POLY_GT4*)arg0->tag)->b3 = 0;
    ((POLY_GT4*)arg0->tag)->x2 = 0;
    ((POLY_GT4*)arg0->tag)->y2 = 0;
}

void func_801D6FCC(POLY_GT4* arg0) {
    func_801D6EEC(arg0);
    arg0->p3 = 8;
    ((POLY_GT4*)arg0->tag)->p3 = 1;
    ((POLY_GT4*)arg0->tag)->code = 2;
    ((POLY_GT4*)arg0->tag)->pad3 = 0xA;
}

void func_801D7020(POLY_GT4* arg0) {
    arg0->p3 = 0;
    arg0->pad3 = 8;
    ((POLY_GT4*)arg0->tag)->p3 = 0;
    ((POLY_GT4*)arg0->tag)->code = 4;
    ((POLY_GT4*)arg0->tag)->pad3 = 8;
}

s32 func_801D704C(s32 arg0, u8 arg1) {
    s32 var_v0;
    s32 ret = 0;
    u8* var_a0 = arg0 + 4;
    u8* var_v1;
    s32 i;

    for (i = 0; i < 4; i++) {
        var_v1 = var_a0;
        do {
            var_v0 = *var_v1 - arg1;

            if (var_v0 < 0) {
                var_v0 = 0;
            } else {
                ret |= 1;
            }

            *var_v1 = var_v0;
            var_v1++;
        } while ((s32)var_v1 < ((s32)var_a0 + 3));

        var_a0 += 0xC;
    }

    return ret;
}