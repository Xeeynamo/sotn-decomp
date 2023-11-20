#include "no3.h"

void EntityZombie(Entity* self) {
    Entity* newEntity;
    s32 temp_a0;

    if ((self->flags & 0x100) && (self->step < 4)) {
        func_801CAD28(SE_ZOMBIE_EXPLODE);
        self->hitboxState = 0;
        // Spawn Zombie explosion
        newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
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
        if (g_Timer & 1) {
            self->palette++;
        }
        if (Random() & 1) {
            self->palette++;
        }
        self->animCurFrame = 0;
        break;

    case 1:
        if (func_801C5074(&D_80183CAC) & 1) {
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
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
        if (self->facingLeft != 0) {
            self->velocityX = FIX(0.5);
        } else {
            self->velocityX = FIX(-0.5);
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
                distCameraEntity =
                    g_Tilemap.cameraX.i.hi + newEntity->posX.i.hi;
                if ((distCameraEntity < (g_Tilemap.x + 128)) ||
                    ((g_Tilemap.width - 128) < distCameraEntity)) {
                    DestroyEntity(newEntity);
                }
            }
            self->ext.generic.unk80.modeS16.unk0 = (Random() & 0x3F) + 32;
        }
    }
}

void func_801D6880(Primitive* arg0) {
    SVECTOR sp10; //FAKE, not really an svector
    SVECTOR stackpad;
    SVECTOR sp20;
    VECTOR sp28;
    SVECTOR sp38;
    SVECTOR sp40;
    SVECTOR sp48;
    SVECTOR sp50;
    MATRIX sp58;
    SVECTOR sp78;
    u16 temp_a0;
    u8 temp_v1_2;

    sp78 = D_801B77CC;
    if (arg0->p3 & 8) {
        // Fake logic here, sp10 is not an SVECTOR but it matches.
        // tried using an f32 but couldn't get it to work.
        sp10.vy = arg0->next->x1;
        sp10.vx = arg0->next->y1;
        LOW(sp10.vx) += LOW(arg0->next->u0);
        arg0->next->x1 = sp10.vy;
        arg0->next->y1 = sp10.vx;
        LOW(arg0->next->x0) += LOW(arg0->next->r1);
    }
    temp_v1_2 = arg0->next->b3;
    LOH(arg0->r0) = LOH(arg0->r1) = LOH(arg0->r2) = LOH(arg0->r3) = temp_v1_2 | (temp_v1_2 << 8);
    arg0->b0 = arg0->b1 = arg0->b2 = arg0->b3 = temp_v1_2;
    sp28.vx = 0;
    sp28.vy = 0;
    sp28.vz = 0x400 - LOH(arg0->next->u1);
    RotMatrix(&sp78, &sp58);
    if (arg0->p3 & 0x20) {
        sp20.vx = arg0->next->x3;
        sp20.vy = arg0->next->y3;
        RotMatrixX(sp20.vx, &sp58);
        RotMatrixY(sp20.vy, &sp58);
    }
    sp20.vz = arg0->next->tpage;
    RotMatrixZ(sp20.vz, &sp58);
    TransMatrix(&sp58, &sp28);
    if (arg0->p3 & 0x10) {
        sp28.vx = (s32) arg0->next->x2;
        sp28.vy = (s32) arg0->next->y2;
        sp28.vz = 0x1000;
        ScaleMatrix(&sp58, &sp28.vx);
    }
    SetRotMatrix(&sp58);
    SetTransMatrix(&sp58);
    SetGeomScreen(0x400);
    SetGeomOffset(arg0->next->x1, arg0->next->y0);
    sp38.vx = -LOH(arg0->next->r2) / 2;
    sp38.vy = -LOH(arg0->next->b2) / 2;
    sp38.vz = 0;
    sp40.vx = LOH(arg0->next->r2) / 2;
    sp40.vy = -LOH(arg0->next->b2) / 2;
    sp40.vz = 0;
    sp48.vx = -LOH(arg0->next->r2) / 2;
    sp48.vy = LOH(arg0->next->b2) / 2;
    sp48.vz = 0;
    sp50.vx = LOH(arg0->next->r2) / 2;
    sp50.vy = LOH(arg0->next->b2) / 2;
    sp50.vz = 0;
    gte_ldv0(&sp38);
    gte_rtps();
    gte_stsxy(&arg0->x0); 
    gte_ldv0(&sp40);
    gte_rtps();
    gte_stsxy(&arg0->x1);
    gte_ldv0(&sp48);
    gte_rtps();
    gte_stsxy(&arg0->x2);
    gte_ldv0(&sp50);
    gte_rtps();
    gte_stsxy(&arg0->x3);
}

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

#include "../unk_poly_func_0.h"

#include "../unk_loop_func.h"
