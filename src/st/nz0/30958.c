/*
 * File: 394D4.c
 * Overlay: NZ0
 * Description: Alchemy Laboratory
 */

#include "nz0.h"

void func_801B0958(Entity* self) {
    ObjInit2* temp_s0 = &D_80180D64[self->subId];

    if (self->step == 0) {
        InitializeEntity(&D_80180C1C);
        self->animSet = temp_s0->animSet;
        self->zPriority = temp_s0->zPriority;
        self->unk5A = temp_s0->unk4.u;
        self->palette = temp_s0->palette;
        self->unk19 = temp_s0->unk8;
        self->blendMode = temp_s0->blendMode;
        if (temp_s0->unkC != 0) {
            self->flags = temp_s0->unkC;
        }
    }
    AnimateEntity(temp_s0->unk10, self);
}

bool func_801B0A20(Entity* self) {
    s16 diffX = PLAYER.posX.i.hi - self->posX.i.hi;

    diffX = ABS(diffX);
    if (self->hitboxWidth >= diffX) {
        diffX = PLAYER.posY.i.hi - self->posY.i.hi;
        diffX = ABS(diffX);
        return (self->hitboxHeight >= diffX);
    } else {
        return false;
    }
}

INCLUDE_ASM("asm/us/st/nz0/nonmatchings/30958", func_801B0AA4);

// https://decomp.me/scratch/0tv5m 92.76 %
INCLUDE_ASM("asm/us/st/nz0/nonmatchings/30958", EntityBreakable);

// bust with red eyes that can have a candle on it
void EntityRedEyeBust(Entity* self) {
    switch (self->step) {
    case 0:
        InitializeEntity(&D_80180C34);
        self->animCurFrame = 7;
        self->zPriority = 0x70;
        break;

    case 1:
        break;

    case 2:
        FntPrint(&D_801B058C, self->animCurFrame); // "charal %x\n"
        if (g_pads[1].pressed & PAD_SQUARE) {
            if (self->subId == 0) {
                self->animCurFrame++;
                self->subId |= 1;
            } else
                break;
        } else {
            self->subId = 0;
        }

        if (g_pads[1].pressed & PAD_CIRCLE) {
            if (self->unk2E == 0) {
                self->animCurFrame--;
                self->unk2E |= 1;
            }
        } else {
            self->unk2E = 0;
        }
        break;
    }
}

INCLUDE_ASM("asm/us/st/nz0/nonmatchings/30958", func_801B12E8);

INCLUDE_ASM("asm/us/st/nz0/nonmatchings/30958", func_801B14C4);

INCLUDE_ASM("asm/us/st/nz0/nonmatchings/30958", func_801B1770);

void func_801B19A0(Entity* self) {
    Collider collider;
    Entity* newEntity;
    s32 rnd;
    s16 rnd2;
    s32 i;

    switch (self->step) {
    case 0:
        InitializeEntity(D_80180C34);
        self->unk19 = 4;

        if (Random() & 1) {
            self->animCurFrame = 1;
        } else {
            self->animCurFrame = 2;
        }

        rnd = (Random() & 0x1F) + 16;
        rnd2 = ((Random() & 0x3F) * 16) | 0xC00;
        if (self->subId != 0) {
            self->animCurFrame = 3;
            rnd = (Random() & 0x1F) + 16;
            rnd2 = (Random() * 6) + 0x900;
        }

        self->accelerationX = rnd * rcos(rnd2);
        self->accelerationY = rnd * rsin(rnd2);
        if (self->accelerationX < 0) {
            self->facing = 1;
        }

    case 1:
        MoveEntity();
        self->unk1E += 0x20;
        if (self->subId != 0) {
            self->unk1E += 0x20;
        }

        self->accelerationY += 0x2000;
        g_api.CheckCollision(self->posX.i.hi, self->posY.i.hi + 6, &collider,
                             0);
        if (collider.unk0 & 1) {
            self->posY.i.hi += LOH(collider.unk18);
            if (self->subId == 0) {
                func_801C29B0(0x644);
                for (i = 0; i < 2; i++) {
                    newEntity =
                        AllocEntity(D_8007D858, &D_8007D858[MaxEntityCount]);
                    if (newEntity != NULL) {
                        CreateEntityFromEntity(0x22, self, newEntity);
                        newEntity->subId = 0x1;
                    }
                }
                DestroyEntity(self);
                break;
            }
            if (self->accelerationY < 0x8000) {
                newEntity =
                    AllocEntity(D_8007D858, &D_8007D858[MaxEntityCount]);
                if (newEntity != NULL) {
                    CreateEntityFromEntity(ENTITY_INTENSE_EXPLOSION, self,
                                           newEntity);
                    newEntity->subId = 0x10;
                }
                DestroyEntity(self);
                break;
            }
            self->accelerationY = -self->accelerationY;
            self->accelerationY *= 2;
            self->accelerationY /= 3;
        }
    }
}

void func_801B1C18(Entity* self) {
    s32 temp_s1 = func_801BD9A0(self, 8, 8, 4);
    s16 firstPolygonIndex;
    POLY_GT4* poly;
    Entity* player;
    s32 temp;

    switch (self->step) {
    case 0:
        InitializeEntity(D_80180BF8);
        firstPolygonIndex = g_api.AllocPolygons(4, 1);
        if (firstPolygonIndex == (-1)) {
            DestroyEntity(self);
            return;
        }
        poly = &D_80086FEC[firstPolygonIndex];
        self->firstPolygonIndex = firstPolygonIndex;
        *((s32*)(&self->unk7C)) = poly;
        self->flags |= FLAG_FREE_POLYGONS;
        poly->code = 6;
        poly->tpage = 0xF;
        poly->clut = 9;
        poly->u0 = 72;
        poly->v0 = 200;
        poly->u1 = 16;
        poly->v1 = 16;
        poly->pad2 = 0x5F;
        poly->pad3 = 2;

    case 1:
        if (temp_s1 != 0) {
            player = &PLAYER;
            player->posY.i.hi++;
            self->posY.val += 0x10000;
            temp = g_Camera.posY.i.hi + self->posY.i.hi;
            if (temp > 468) {
                self->posY.i.hi = 468 - g_Camera.posY.i.hi;
                D_80180EB4 ^= self->subId;
                self->step++;
            }
        }
        break;

    case 2:
        if (temp_s1 == 0) {
            self->step++;
        }
        break;

    case 3:
        self->posY.val += 0xFFFF0000;
        temp = g_Camera.posY.i.hi + self->posY.i.hi;
        if (temp < 464) {
            self->posY.i.hi = 464 - g_Camera.posY.i.hi;
            self->step = 1;
        }
        break;
    }
    poly = (POLY_GT4*)(*((s32*)(&self->unk7C)));
    poly->x0 = self->posX.i.hi - 8;
    poly->y0 = self->posY.i.hi - 8;
}

void func_801B1E54(Entity* self, s16 firstPolygonIndex) {
    POLY_GT4* poly;
    s8 var_v1;
    s32 temp;

    switch (self->step) {
    case 0:
        InitializeEntity(&D_80180BF8);
        self->hitboxWidth = 12;
        self->hitboxHeight = 12;
        self->attackElement = 1;
        self->attack = 7;
        self->unk3C = 1;

        firstPolygonIndex = g_api.AllocPolygons(4, 1);
        if (firstPolygonIndex == -1) {
            DestroyEntity(self);
            return;
        }
        poly = &D_80086FEC[firstPolygonIndex];
        self->firstPolygonIndex = firstPolygonIndex;
        *((s32*)(&self->unk7C)) = poly;
        self->flags |= FLAG_FREE_POLYGONS;
        poly->code = 6;
        poly->tpage = 0xF;
        poly->clut = 9;
        poly->u0 = 40;
        poly->v0 = 200;
        poly->u1 = 32;
        poly->v1 = 32;
        poly->pad2 = 0x5F;
        poly->pad3 = 2;

        if (self->subId & D_80180EB4) {
            self->posY.i.hi = 480 - g_Camera.posY.i.hi;
            self->unk88.S8.unk0 = 1;
        } else {
            self->posY.i.hi = 452 - g_Camera.posY.i.hi;
            self->unk88.S8.unk0 = 0;
        }

    case 1:
        if (self->subId & D_80180EB4) {
            self->posY.val += 0x10000;
            temp = g_Camera.posY.i.hi + self->posY.i.hi;
            if (temp > 480) {
                self->posY.i.hi = 480 - g_Camera.posY.i.hi;
            }
            var_v1 = 1;
        } else {
            self->posY.val += 0xFFFF0000;
            temp = g_Camera.posY.i.hi + self->posY.i.hi;
            if (temp < 452) {
                self->posY.i.hi = 452 - g_Camera.posY.i.hi;
                self->step = 1;
            }
            var_v1 = 0;
        }

        if (self->unk88.U8.unk0 != var_v1) {
            self->unk88.U8.unk0 = var_v1;
            func_801C29B0(0x69D);
        }
    }

    poly = (POLY_GT4*)(*((s32*)(&self->unk7C)));
    poly->x0 = self->posX.i.hi - 16;
    poly->y0 = self->posY.i.hi - 16;
    temp = 480 - (g_Camera.posY.i.hi + self->posY.i.hi);
    D_801CB736[self->subId] = temp;
}

// moveable box for spike/switch areas
void EntityMoveableBox(Entity* self) {
    Entity* player;
    POLY_GT4* poly;
    s32 temp_s1 = func_801BD9A0(self, 0x10, 0x10, 5);
    s32 var_s1 = temp_s1;
    s16 firstPolygonIndex;
    s32 temp_v0_2;
    s32 var_v0;
    s32 var_v1;
    s32 new_var;

    switch (self->step) {
    case 0:
        InitializeEntity(&D_80180BF8);
        firstPolygonIndex = g_api.AllocPolygons(4, 1);
        if (firstPolygonIndex == (-1)) {
            DestroyEntity(self);
            return;
        }
        poly = &D_80086FEC[firstPolygonIndex];
        self->firstPolygonIndex = firstPolygonIndex;
        *((s32*)(&self->unk7C.s)) = poly;
        self->flags |= FLAG_FREE_POLYGONS;
        poly->code = 6;
        poly->tpage = 0xF;
        poly->clut = 9;
        poly->u0 = 8;
        poly->v0 = 200;
        poly->u1 = 32;
        poly->v1 = 32;
        poly->pad2 = 112;
        poly->pad3 = 2;

    case 1:
        player = &PLAYER;
        self->accelerationX = 0;
        self->accelerationY = 0;

        if (var_s1 & 1) {
            temp_s1 = func_801BCC5C();
            if (temp_s1 & 1 && player->accelerationX > 0) {
                if (!(g_blinkTimer & 7)) {
                    g_api.PlaySfx(0x608);
                }
                self->accelerationX = 0x8000;
            }
            temp_s1 = func_801BCC5C();
            if (!(firstPolygonIndex = (temp_s1 & 1)) &&
                (player->accelerationX < 0)) {
                if (!(g_blinkTimer & 7)) {
                    g_api.PlaySfx(0x608);
                }
                self->accelerationX = -0x8000;
            }
        }

        func_801BCF74(&D_80180EB8);

        if (self->subId == 0) {
            temp_v0_2 = self->posX.i.hi + g_Camera.posX.i.hi;
            var_v1 = temp_v0_2 - 192;
            var_v1 = ABS(var_v1);
            var_v0 = temp_v0_2 - 256;
            var_v0 = ABS(var_v0);
            var_s1 = 24 > var_v1;
            if (var_v0 < 24) {
                var_s1 = 2;
            }
            if ((self->unk84.unk == 0) && (*(s16*)&D_801CB736[var_s1] != 0)) {
                var_s1 = 0;
                self->posX.val -= self->accelerationX;
            }
            self->unk84.unk = var_s1;
            if (var_s1 != 0) {
                self->posY.i.hi =
                    (448 - D_801CB736[var_s1]) - g_Camera.posY.i.hi;
            }
        }
        break;
    }
    poly = (POLY_GT4*)(*(s32*)(&self->unk7C.s));
    new_var = ((u16)self->posX.i.hi) - 16;
    poly->x0 = new_var;
    poly->y0 = ((u16)self->posY.i.hi) - 16;
}

// lever to operate cannon
// https://decomp.me/scratch/7ce8a
// Matching in PSY-Q 3.5, assembler skips a nop
#ifndef NON_MATCHING
INCLUDE_ASM("asm/us/st/nz0/nonmatchings/30958", EntityCannonLever);
#else
void EntityCannonLever(Entity* self) {
    /** TODO: !FAKE
     * self->unk7C should be a POLY_G4*
     */
    POLY_GT4* poly;
    s16 firstPolygonIndex;
    s32 temp_v0_2;
    s32 temp_v1_2;
    s32 var_v0;

    switch (self->step) {
    case 0:
        InitializeEntity(&D_80180BF8);
        self->hitboxWidth = 4;
        self->hitboxHeight = 20;
        self->unk3C = 2;

        firstPolygonIndex = g_api.AllocPolygons(4, 1);
        if (firstPolygonIndex == -1) {
            DestroyEntity(self);
            return;
        }
        poly = &D_80086FEC[firstPolygonIndex];
        self->firstPolygonIndex = firstPolygonIndex;
        *(s32*)&self->unk7C = poly;

        self->flags |= FLAG_FREE_POLYGONS;
        poly->code = 6;
        poly->tpage = 0xF;
        poly->clut = 9;
        poly->u0 = 0x68;
        poly->v0 = 0x80;
        poly->u1 = 8;
        poly->v1 = 0x28;
        poly->pad2 = 0x70;
        poly->pad3 = 2;

        if (PLAYER.posX.i.hi < 128) {
            self->unk3C = 0;
        }
        break;

    case 1:
        if (self->unk48 != 0) {
            self->accelerationX = -0x40000;
            self->step++;
        }
        break;

    case 2:
        MoveEntity();
        temp_v1_2 = self->accelerationX;
        if (temp_v1_2 < 0) {
            var_v0 = temp_v1_2 + 0xF;
        } else {
            var_v0 = temp_v1_2;
        }
        temp_v0_2 = temp_v1_2 - (var_v0 >> 4);
        self->accelerationX = temp_v0_2;
        if (temp_v0_2 < 0x2000) {
            self->step++;
        }
        break;

    case 3:
        D_80180ED0 = 1;
        break;
    }

    if (D_8003BE6F != 0) {
        self->unk3C = 0;
    }
    poly = (POLY_GT4*)*(s32*)&self->unk7C.s;
    poly->x0 = self->posX.i.hi - 4;
    poly->y0 = self->posY.i.hi - 20;
}
#endif

// cannon for shortcut
INCLUDE_ASM("asm/us/st/nz0/nonmatchings/30958", EntityCannon);

// projectile shot by cannon
void EntityCannonShot(Entity* self) {
    Entity* newEntity;

    switch (self->step) {
    case 0:
        InitializeEntity(&D_80180BF8);
        self->animSet = 2;
        self->animCurFrame = 1;
        self->palette = 0x81AF;
        self->zPriority = 0x6F;
        self->accelerationX = -0x80000;

    case 1:
        MoveEntity();
        if ((self->posX.i.hi + g_Camera.posX.i.hi) < 112) {
            g_api.func_80102CD8(1);
            newEntity = AllocEntity(D_8007D858, &D_8007D858[32]);
            if (newEntity != NULL) {
                CreateEntityFromEntity(2, self, newEntity);
                newEntity->subId = 3;
            }
            D_8003BE6F = 1;
            DestroyEntity(self);
        }
        break;
    }
}

INCLUDE_ASM("asm/us/st/nz0/nonmatchings/30958", func_801B2978);

void func_801B2AD8(Entity* self) {
    s16 firstPolygonIndex;
    POLY_GT4* poly;
    s32 var_v0;
    s32 var_a0;
    s32 temp;

    switch (self->step) {
    case 0:
        InitializeEntity(D_80180BF8);
        self->hitboxHeight = 8;
        self->unk12 = -0x16;
        self->hitboxWidth = 6;
        self->unk3C = 1;
        CreateEntityFromEntity(0x26, self, &self[-1]);
        self[-1].posY.i.hi = 344 - g_Camera.posY.i.hi;

        firstPolygonIndex = g_api.AllocPolygons(4, 1);
        if (firstPolygonIndex == -1) {
            DestroyEntity(self);
            return;
        }
        poly = &D_80086FEC[firstPolygonIndex];
        self->firstPolygonIndex = firstPolygonIndex;
        *((s32*)(&self->unk7C)) = poly;
        self->flags |= FLAG_FREE_POLYGONS;
        poly->tpage = 0xF;
        poly->clut = 9;
        poly->u0 = 72;
        poly->v0 = 200;
        poly->u1 = 16;
        poly->v1 = 16;
        poly->pad2 = 0x5F;
        poly->code = 6;
        poly->pad3 = 2;

    case 1:
        var_a0 = self->unk48;
        var_v0 = self->posX.i.hi - self[-1].posX.i.hi;

        if (ABS(var_v0) < 8) {
            var_a0 |= 0x8000;
        }

        if (var_a0 != 0) {
            self->posY.val += 0x10000;
            temp = g_Camera.posY.i.hi + self->posY.i.hi;
            if (temp > 376) {
                self->posY.i.hi = 376 - g_Camera.posY.i.hi;
            }
            D_80180EEC = 1;
        } else {
            self->posY.val += 0xFFFF0000;
            temp = g_Camera.posY.i.hi + self->posY.i.hi;
            if (temp < 372) {
                self->posY.i.hi = 372 - g_Camera.posY.i.hi;
            }
            D_80180EEC = 0;
        }

    default:
        poly = (POLY_GT4*)(*((s32*)(&self->unk7C)));
        poly->x0 = self->posX.i.hi - 8;
        poly->y0 = self->posY.i.hi - 8;
    }
}

// https://decomp.me/scratch/ixW6j 93.06%
INCLUDE_ASM("asm/us/st/nz0/nonmatchings/30958", func_801B2D08);

INCLUDE_ASM("asm/us/st/nz0/nonmatchings/30958", func_801B2FD8);

INCLUDE_ASM("asm/us/st/nz0/nonmatchings/30958", func_801B3294);

// table with globe on it that can be broken
void EntityTableWithGlobe(Entity* self) {
    switch (self->step) {
    case 0:
        InitializeEntity(D_80180CC4);
        self->zPriority = 0x6A;
        self->hitboxWidth = 8;
        self->hitboxHeight = 12;
        self->unk12 = -0xA;
        self->unk10 = 0;
        self->unk3C = 2;

    case 1:
        AnimateEntity(D_80180EF0, self);
        if (self->unk48 != 0) {
            func_801C29B0(0x61D);
            self->unk3C = 0;
            CreateEntityFromEntity(ENTITY_HEART_DROP, self, &self[1]);
            self[1].subId = D_80180F10[self->subId];
            func_801BD52C(2);
        }
        break;

    case 2:
        AnimateEntity(D_80180EF8, self);
        break;
    }
}

void func_801B3648(Entity* self) {
    Entity* newEntity;

    switch (self->step) {
    case 0:
        InitializeEntity(D_80180CD0);
        self->zPriority = 0x6A;
        self->hitboxWidth = 8;
        self->hitboxHeight = 12;
        self->unk12 = -0xA;
        self->unk10 = 0;
        self->unk3C = 2;

    case 1:
        AnimateEntity(D_80180F1C, self);
        if (self->unk48 != 0) {
            func_801C29B0(0x619);
            self->unk3C = 0;
            func_801BD52C(2);
        }
        break;

    case 2:
        if (AnimateEntity(&D_80180F30, self) == 0) {
            CreateEntityFromEntity(ENTITY_HEART_DROP, self, &self[1]);
            self[1].subId = D_80180F4C[self->subId];
            newEntity = AllocEntity(D_8007D858, &D_8007D858[MaxEntityCount]);
            if (newEntity != NULL) {
                CreateEntityFromEntity(ENTITY_EXPLOSION, self, newEntity);
                newEntity->subId = 2;
                newEntity->posY.i.hi -= 8;
            }
            self->step++;
        }
        break;

    case 3:
        newEntity = self;
        newEntity->animCurFrame = 20;
        break;
    }
}

void func_801B37C0(Entity* self) {
    Entity* newEntity;

    switch (self->step) {
    case 0:
        InitializeEntity(D_80180CDC);
        if (self->subId & 0x100) {
            self->blendMode = 0x30;
        } else {
            self->zPriority = 0x6A;
            self->hitboxWidth = 8;
            self->hitboxHeight = 12;
            self->unk12 = -0xA;
            self->unk10 = 0;
            self->unk3C = 2;
            CreateEntityFromEntity(0x37, self, &self[1]);
            self[1].subId = 0x100;
        }

    case 1:
        if (self->subId & 0x100) {
            AnimateEntity(D_80180F74, self);
            break;
        }
        AnimateEntity(D_80180F50, self);
        if (self->unk48 != 0) {
            self->unk3C = 0;
            func_801BD52C(2);
        }
        break;

    case 2:
        if (self->subId > 0x1) {
            CreateEntityFromEntity(ENTITY_RELIC_ORB, self, &self[1]);
        } else {
            CreateEntityFromEntity(ENTITY_HEART_DROP, self, &self[1]);
        }

        self[1].subId = D_80180F9C[self->subId];
        do { // !FAKE
        } while (0);
        newEntity = AllocEntity(D_8007D858, &D_8007D858[32]);
        if (newEntity != NULL) {
            CreateEntityFromEntity(2, self, newEntity);
            newEntity->subId = 2;
            newEntity->posY.i.hi -= 8;
        }
        func_801C29B0(0x61D);
        self->step++;

    case 3:
        self->animCurFrame = 4;
        break;

    case 255:
        FntPrint(&D_801B0598, self->animCurFrame); // "charal %x\n"
        if (g_pads[1].pressed & PAD_SQUARE) {
            if (self->subId != 0) {
                break;
            }
            self->animCurFrame++;
            self->subId |= 1;
        } else {
            self->subId = 0;
        }
        if (g_pads[1].pressed & PAD_CIRCLE) {
            if (self->unk2E == 0) {
                self->animCurFrame--;
                self->unk2E |= 1;
            }
        } else {
            newEntity = self;
            newEntity->unk2E = 0;
        }
        break;
    }
}

void func_801B3A50(Entity* self) {
    switch (self->step) {
    case 0:
        InitializeEntity(D_80180CDC);
        self->zPriority = 0x6A;
        self->hitboxWidth = 8;
        self->hitboxHeight = 16;
        self->unk12 = -0xA;
        self->unk10 = 0;
        self->unk3C = 2;

    case 1:
        AnimateEntity(D_80180F88, self);
        if (self->unk48 != 0) {
            g_api.PlaySfx(NA_SE_BREAK_CANDLE);
            self->unk3C = 0;
            func_801BD52C(2);
        }
        break;

    case 2:
        CreateEntityFromEntity(ENTITY_HEART_DROP, self, &self[1]);
        self[1].subId = D_80180F9C[self->subId];
        self->step++;

    case 3:
        self->animCurFrame = 18;
        break;
    }
}

void func_801B3B78() {
    Entity* entity;
    s8 temp_s4 = Random() & 3;
    s16 temp_s3 = ((Random() & 0xF) << 8) - 0x800;
    s32 i;

    for (i = 0; i < 6; i++) {
        entity = AllocEntity(D_8007D858, &D_8007D858[MaxEntityCount]);
        if (entity != NULL) {
            CreateEntityFromEntity(0x38, g_CurrentEntity, entity);
            entity->subId = 2;
            entity->unk88.S8.unk1 = 6 - i;
            entity->unk84.S16.unk0 = temp_s3;
            entity->unk88.S8.unk0 = temp_s4;
        }
    }
}

INCLUDE_ASM("asm/us/st/nz0/nonmatchings/30958", func_801B3C38);

// https://decomp.me/scratch/bqgN9 95.04 %
// figuring out D_80181014 struct might help
// trigger to stop music and close slogra/gaibon room
INCLUDE_ASM("asm/us/st/nz0/nonmatchings/30958", EntityCloseBossRoom);

// blocks that move to close slogra/gaibon room
// assembler skips a nop
#ifndef NON_MATCHING
INCLUDE_ASM("asm/us/st/nz0/nonmatchings/30958", EntityBossRoomBlock);
#else
void EntityBossRoomBlock(Entity* self) {
    switch (self->step) {
    case 0:
        InitializeEntity(D_80180D00);
        self->animCurFrame = 8;

    case 1:
        if (D_80181010 & 1) {
            self->unk80.modeS16.unk0 = 0x10;
            self->step++;
        }
        break;

    case 2:
        if (self->subId == 0) {
            self->accelerationX = 0x10000;
        } else {
            self->accelerationX = -0x10000;
        }
        MoveEntity();
        func_801BD9A0(self, 8, 8, 5);
        if (!(g_blinkTimer & 3)) {
            g_api.PlaySfx(0x608);
        }
        if (--self->unk80.modeS16.unk0) {
            break;
        }
        self->step++;
        break;

    case 3:
        func_801BD9A0(self, 8, 8, 5);
        if (D_80181010 & 2) {
            self->step++;
        }
        break;

    case 4:
        self->flags |= FLAG_DESTROY_IF_OUT_OF_CAMERA;
        if (self->subId != 0) {
            self->accelerationX = 0x10000;
        } else {
            self->accelerationX = -0x10000;
        }
        MoveEntity();
        break;
    }
}
#endif

s32 func_801B4690(void) {
    s32 ret = 0;
    s32 temp;

    MoveEntity();
    g_CurrentEntity->accelerationY += 0x4000;
    temp = g_CurrentEntity->posX.i.hi + g_Camera.posX.i.hi;

    if ((g_CurrentEntity->accelerationX > 0) && (temp > 896)) {
        g_CurrentEntity->posX.i.hi = 896 - g_Camera.posX.i.hi;
    }

    if ((g_CurrentEntity->accelerationX < 0) && (temp < 64)) {
        g_CurrentEntity->posX.i.hi = 64 - g_Camera.posX.i.hi;
    }

    if ((g_CurrentEntity->posY.i.hi + g_Camera.posY.i.hi) > 416) {
        ret = 1;
        g_CurrentEntity->posY.i.hi = 416 - g_Camera.posY.i.hi;
        g_CurrentEntity->accelerationX = 0;
        g_CurrentEntity->accelerationY = 0;
    }

    return ret;
}

// slogra boss
INCLUDE_ASM("asm/us/st/nz0/nonmatchings/30958", EntitySlogra);

void func_801B54A8(Entity* self) {
    s8* hitbox;

    switch (self->step) {
    case 0:
        InitializeEntity(D_80180D18);

    case 1:
        self->facing = self[-1].facing;
        self->posX.i.hi = self[-1].posX.i.hi;
        self->posY.i.hi = self[-1].posY.i.hi;
        hitbox = D_801811E0;
        hitbox += 4 * D_80181218[self[-1].animCurFrame];
        self->unk10 = *hitbox++;
        self->unk12 = *hitbox++;
        self->hitboxWidth = *hitbox++;
        self->hitboxHeight = *hitbox++;
        if (self[-1].unk84.U8.unk2 != 0) {
            self->step++;
        }
        break;

    case 2:
        switch (self->unk2E) {
        case 0:
            self->unk19 = 4;
            self->unk3C = 0;
            if (self->facing != 0) {
                self->accelerationX = -0x24000;
            } else {
                self->accelerationX = 0x24000;
            }
            self->accelerationY = -0x40000;
            self->animCurFrame = 0x23;
            self->flags |= FLAG_DESTROY_IF_OUT_OF_CAMERA;
            self->unk2E++;

        case 1:
            MoveEntity();
            self->accelerationY += 0x2800;
            self->unk1E += 0x80;
            if (!(self->unk1E & 0xFFF)) {
                func_801C29B0(0x625);
            }
        }
    }
}

// projectile fired from slogra's spear
void EntitySlograSpearProjectile(Entity* self) {
    Entity* entity;

    if (self->flags & 0x100) {
        entity = AllocEntity(D_8007D858, &D_8007D858[32]);
        if (entity != NULL) {
            CreateEntityFromEntity(2, self, entity);
            entity->subId = 1;
        }
        DestroyEntity(self);
        return;
    }

    switch (self->step) {
    case 0:
        InitializeEntity(D_80180D24);
        if (self->facing == 0) {
            self->accelerationX = -0x40000;
        } else {
            self->accelerationX = 0x40000;
        }

    case 1:
        if (AnimateEntity(D_80181160, self) == 0) {
            func_801BD52C(2);
        }
        break;

    case 2:
        MoveEntity();
        AnimateEntity(D_80181170, self);
        break;
    }
}

// gaibon boss
INCLUDE_ASM("asm/us/st/nz0/nonmatchings/30958", EntityGaibon);

INCLUDE_ASM("asm/us/st/nz0/nonmatchings/30958", func_801B69E8);

// small red projectile from gaibon
void EntitySmallGaibonProjectile(Entity* self) {
    if (self->flags & 0x100) {
        self->pfnUpdate = EntityExplosion;
        self->unk19 = 0;
        self->step = 0;
        self->objectId = 2;
        self->subId = 0;
        return;
    }

    switch (self->step) {
    case 0:
        InitializeEntity(D_80180D3C);
        self->animSet = 2;
        self->animCurFrame = 1;
        self->unk19 = 5;
        self->unk1A = 0xC0;
        self->accelerationX = (rcos(self->unk1E) * 0x28000) >> 0xC;
        self->accelerationY = (rsin(self->unk1E) * 0x28000) >> 0xC;
        self->palette = 0x81B6;
        self->unk1E -= 0x400;

    case 1:
        MoveEntity();
        AnimateEntity(D_8018136C, self);
        break;
    }
}

// large red projectile from gaibon
void EntityLargeGaibonProjectile(Entity* self) {
    Entity* newEntity;

    if (self->flags & 0x100) {
        self->pfnUpdate = EntityExplosion;
        self->objectId = 2;
        self->unk19 = 0;
        self->step = 0;
        self->subId = 1;
        return;
    }

    switch (self->step) {
    case 0:
        InitializeEntity(&D_80180D48);
        if (self->subId == 0) {
            self->animSet = 2;
            self->unk19 = 4;
            self->accelerationX = (rcos(self->unk1E) * 0x38000) >> 0xC;
            self->accelerationY = (rsin(self->unk1E) * 0x38000) >> 0xC;
            self->palette = 0x81B6;
            self->unk1E -= 0x400;
        } else {
            self->animSet = 14;
            self->unk5A = 0x79;
            self->unk19 = 0xD;
            self->unk1A = 0x100;
            self->unk6C = 0x80;
            self->palette = 0x81F3;
            self->blendMode = 0x30;
            self->step = 2;
            self->unk3C = 0;
            self->flags |= 0x2000;
        }
        break;

    case 1:
        MoveEntity();
        AnimateEntity(D_80181378, self);
        if (!(g_blinkTimer & 3)) {
            newEntity = AllocEntity(D_8007D858, &D_8007D858[32]);
            if (newEntity != NULL) {
                CreateEntityFromEntity(0x46, self, newEntity);
                newEntity->subId = 1;
                newEntity->unk1E = self->unk1E;
                newEntity->zPriority = self->zPriority + 1;
            }
        }
        break;

    case 2:
        self->unk6C += 0xFE;
        self->unk1A -= 4;
        if (AnimateEntity(D_80181388, self) == 0) {
            DestroyEntity(self);
        }
        break;
    }
}

void func_801B6DE4(Entity* self) {
    s32 temp_s1 = self->unk48;
    s16 firstPolygonIndex;
    POLY_GT4* poly;
    s32 temp;

    switch (self->step) {
    case 0:
        InitializeEntity(D_80180BF8);
        self->unk80.modeS32 = self->posY.i.hi + g_Camera.posY.i.hi;
        self->hitboxHeight = 8;
        self->unk12 = -0x16;
        self->hitboxWidth = 6;
        self->unk3C = 1;

        firstPolygonIndex = g_api.AllocPolygons(4, 1);
        if (firstPolygonIndex == (-1)) {
            DestroyEntity(self);
            return;
        }
        poly = &D_80086FEC[firstPolygonIndex];
        self->firstPolygonIndex = firstPolygonIndex;
        *((s32*)(&self->unk7C)) = poly;

        self->flags |= FLAG_FREE_POLYGONS;
        poly->tpage = 0xF;
        poly->clut = 9;
        poly->u0 = 72;
        poly->v0 = 200;
        poly->u1 = 16;
        poly->v1 = 16;
        poly->pad2 = 0x5F;
        poly->code = 6;
        poly->pad3 = 2;

    case 1:
        if (temp_s1 != 0) {
            self->posY.val += 0x10000;
            temp = g_Camera.posY.i.hi + self->posY.i.hi;
            if ((self->unk80.modeS32 + 4) < temp) {
                self->posY.i.hi =
                    (u16)(self->unk80.modeS16.unk0 - (g_Camera.posY.i.hi - 4));
                self->step++;
                func_801C29B0(0x676);
                D_801813A4 = self->subId;
            }
        }
        break;

    case 2:
        if (temp_s1 == 0) {
            self->posY.val += 0xFFFF0000;
            temp = g_Camera.posY.i.hi + self->posY.i.hi;
            if (temp < self->unk80.modeS32) {
                self->posY.i.hi =
                    (u16)(self->unk80.modeS16.unk0) - g_Camera.posY.i.hi;
                self->step = 1;
            }
        }
        break;
    }

    poly = (POLY_GT4*)(*((s32*)(&self->unk7C)));
    poly->x0 = self->posX.i.hi - 8;
    poly->y0 = self->posY.i.hi;
    poly->y0 = poly->y0 - 8;
}

INCLUDE_ASM("asm/us/st/nz0/nonmatchings/30958", func_801B7034);

void func_801B74CC(void) {
    D_801CB694 = 2;
    D_801CB692 = 2;
    D_801CB696 = 0;
    D_801CB69A = 0;
    D_801CB69E = 0;
    D_801CB69F = 8;
    D_801CB68E = D_801CB690 + 0x14;
}

INCLUDE_ASM("asm/us/st/nz0/nonmatchings/30958", func_801B7520);

void func_801B76E4(s16 arg0) {
    RECT rect;

    rect.y = (arg0 * 12) + 384;
    rect.w = 64;
    rect.x = 0;
    rect.h = 12;
    ClearImage(&rect, 0, 0, 0);
}

INCLUDE_ASM("asm/us/st/nz0/nonmatchings/30958", func_801B7740);

INCLUDE_ASM("asm/us/st/nz0/nonmatchings/30958", func_801B77F8);

void func_801B797C(s32 arg0) {
    D_801CB6C8 = arg0 + 0x100000;
    D_801CB6C6 = 0;
    D_801CB6C4 = 1;
}

INCLUDE_ASM("asm/us/st/nz0/nonmatchings/30958", func_801B79A8);

INCLUDE_ASM("asm/us/st/nz0/nonmatchings/30958", func_801B7C54);

// cutscene where alucard and maria discuss castle changing
INCLUDE_ASM("asm/us/st/nz0/nonmatchings/30958", EntityMariaCutscene);

void func_801B8E0C(Entity* self) {
    switch (self->step) {
    case 0:
        InitializeEntity(D_80180BEC);
        D_8003C8B8 = 0;
        *D_80097400 = 1;
        *D_80072EF4 = 0x8000;
        if (D_80072F2C & 4) {
            *D_80072EF4 = 2;
        }
        D_80072EFC = 1;
        break;

    case 1:
        if (PLAYER.posX.i.hi < 176) {
            *D_80072EF4 = 0;
            self->step++;
        } else {
            *D_80072EF4 = 0;
            if (D_80072F2C & 4) {
                if (g_blinkTimer & 1) {
                    *D_80072EF4 = 2;
                }
            } else {
                *D_80072EF4 = 0x8000;
            }
        }
        D_80072EFC = 1;
        break;

    case 2:
        if (D_801CB734 & 0x2000) {
            D_8003C8B8 = 1;
            if (*D_80097400 != 0) {
                *D_80097400 = 0;
            }
            DestroyEntity(self);
        }
        *D_80072EF4 = 0;
        D_80072EFC = 1;
        break;
    }
}

INCLUDE_ASM("asm/us/st/nz0/nonmatchings/30958", func_801B8F94);

s32 Random(void) {
    // Linear congruential generator algorithm

    g_randomNext = (g_randomNext * 0x01010101) + 1;
    return g_randomNext >> 0x18;
}

u16 D_80181574[];
u16 D_801CB740[];
void Update(void) {
    s16 i;
    Entity* entity;
    s32* unk;

    for (i = 0; i < 0x20; i++) {
        if (D_801CB740[i]) {
            D_801CB740[i]--;
        }
    }

    unk = &D_80097410;
    if (*unk) {
        if (!--*unk) {
            g_api.FreePolygons(D_80097414);
        }
    }

    for (entity = D_800762D8; entity < &D_8007EFD8; entity++) {
        if (!entity->pfnUpdate)
            continue;

        if (entity->step) {
            s32 unk34 = entity->flags;
            if (unk34 & FLAG_DESTROY_IF_OUT_OF_CAMERA) {
                s16 posX = i = entity->posX.i.hi;
                s16 posY = entity->posY.i.hi;
                if (unk34 & FLAG_DESTROY_IF_BARELY_OUT_OF_CAMERA) {
                    if ((u16)(posX + 64) > 384 || (u16)(posY + 64) > 352) {
                        DestroyEntity(entity);
                        continue;
                    }
                } else {
                    if ((u16)(posX + 128) > 512 || (u16)(posY + 128) > 480) {
                        DestroyEntity(entity);
                        continue;
                    }
                }
            }

            if ((unk34 & 0x02000000)) {
                s16 posY = entity->posY.i.hi + g_Camera.posY.i.hi;
                s16 test = (g_CurrentRoom.vSize * 256) + 128;
                if (posY > test) {
                    DestroyEntity(entity);
                    continue;
                }
            }

            if (unk34 & 0xF) {
                entity->palette =
                    D_80181574[(entity->unk49 << 1) | (unk34 & 1)];
                entity->flags--;
                if ((entity->flags & 0xF) == 0) {
                    entity->palette = entity->unk6A;
                    entity->unk6A = 0;
                }
            }

            if (!(unk34 & 0x20000000) || (unk34 & 0x10000000) ||
                ((u16)(entity->posX.i.hi + 64) <= 384) &&
                    ((u16)(entity->posY.i.hi + 64) <= 352)) {
                if (!entity->unk58 || (entity->unk58--, unk34 & 0x100000)) {
                    if (!D_800973FC || unk34 & 0x2100 ||
                        (unk34 & 0x200 && !(D_8003C8C4 & 3))) {
                        g_CurrentEntity = entity;
                        entity->pfnUpdate(entity);
                        entity->unk44 = 0;
                        entity->unk48 = 0;
                    }
                }
            }
        } else {
            g_CurrentEntity = entity;
            entity->pfnUpdate(entity);
            entity->unk44 = 0;
            entity->unk48 = 0;
        }
    }
}

INCLUDE_ASM("asm/us/st/nz0/nonmatchings/30958", func_801B9800);

INCLUDE_ASM("asm/us/st/nz0/nonmatchings/30958", TestCollisions);

INCLUDE_ASM("asm/us/st/nz0/nonmatchings/30958", EntityNumericDamage);

void CreateEntityFromLayout(Entity* entity, LayoutObject* initDesc) {
    DestroyEntity(entity);
    entity->objectId = initDesc->objectId & 0x3FF;
    entity->pfnUpdate = D_80180A90[entity->objectId];
    entity->posX.i.hi = initDesc->posX - g_Camera.posX.i.hi;
    entity->posY.i.hi = initDesc->posY - g_Camera.posY.i.hi;
    entity->subId = initDesc->subId;
    entity->objectRoomIndex = initDesc->objectRoomIndex >> 8;
    entity->unk68 = (initDesc->objectId >> 0xA) & 7;
}

INCLUDE_ASM("asm/us/st/nz0/nonmatchings/30958", func_801BB188);

INCLUDE_ASM("asm/us/st/nz0/nonmatchings/30958", func_801BB2A0);

void func_801BB3B8(s16 arg0) {
    while (true) {
        if ((D_801CAA74->posX != 0xFFFE) && (D_801CAA74->posX >= (s32)arg0)) {
            break;
        }
        D_801CAA74++;
    }
}

void func_801BB404(s16 arg0) {
    while (true) {
        if (!(D_801CAA74->posX == 0xFFFF) &&
            (((s32)arg0 >= D_801CAA74->posX) || (D_801CAA74->posX == 0xFFFE))) {
            break;
        }
        D_801CAA74--;
    }
}

INCLUDE_ASM("asm/us/st/nz0/nonmatchings/30958", func_801BB45C);

INCLUDE_ASM("asm/us/st/nz0/nonmatchings/30958", func_801BB558);

void func_801BB66C(s16 arg0) {
    while (true) {
        if ((D_801CAA78->posY != 0xFFFE) && (D_801CAA78->posY >= (s32)arg0)) {
            break;
        }
        D_801CAA78++;
    }
}

void func_801BB6B8(s16 arg0) {
    while (true) {
        if (!(D_801CAA78->posY == 0xFFFF) &&
            (((s32)arg0 >= D_801CAA78->posY) || (D_801CAA78->posY == 0xFFFE))) {
            break;
        }
        D_801CAA78--;
    }
}

INCLUDE_ASM("asm/us/st/nz0/nonmatchings/30958", func_801BB710);

INCLUDE_ASM("asm/us/st/nz0/nonmatchings/30958", func_801BB80C);

INCLUDE_ASM("asm/us/st/nz0/nonmatchings/30958", func_801BB920);

void func_801BBA98(void) {
    Unkstruct8* currentRoomTileLayout = &g_CurrentRoomTileLayout;

    if (D_80097908 != 0) {
        s16 tmp = g_Camera.posX.i.hi;
        if (D_80097908 > 0)
            func_801BB45C(tmp + 320);
        else
            func_801BB558(tmp - 64);
    }

    if (D_8009790C != 0) {
        s16 tmp = currentRoomTileLayout->unkE;
        if (D_8009790C > 0)
            func_801BB710(currentRoomTileLayout->unkE + 288);
        else
            func_801BB80C(tmp - 64);
    }
}

void CreateEntityFromCurrentEntity(u16 objectId, Entity* entity) {
    DestroyEntity(entity);
    entity->objectId = objectId;
    entity->pfnUpdate = D_80180A90[objectId];
    entity->posX.i.hi = g_CurrentEntity->posX.i.hi;
    entity->posY.i.hi = g_CurrentEntity->posY.i.hi;
}

void CreateEntityFromEntity(u16 objectId, Entity* ent1, Entity* ent2) {
    DestroyEntity(ent2);
    ent2->objectId = objectId;
    ent2->pfnUpdate = D_80180A90[objectId];
    ent2->posX.i.hi = ent1->posX.i.hi;
    ent2->posY.i.hi = ent1->posY.i.hi;
}

s32 func_801BBC3C(Entity* e) {
    s16 diff;

    diff = PLAYER.posX.i.hi - e->posX.i.hi;
    diff = ABS(diff);

    if (diff >= 17) {
        diff = 0;
    } else {
        diff = PLAYER.posY.i.hi - e->posY.i.hi;
        diff = ABS(diff);
        diff = diff < 33;
    }

    return diff;
}

INCLUDE_ASM("asm/us/st/nz0/nonmatchings/30958", EntityRedDoor);

void DestroyEntity(Entity* item) {
    s32 i;
    s32 length;
    u32* ptr;

    if (item->flags & FLAG_FREE_POLYGONS) {
        g_api.FreePolygons(item->firstPolygonIndex);
    }

    ptr = (u32*)item;
    length = sizeof(Entity) / sizeof(s32);
    for (i = 0; i < length; i++)
        *ptr++ = 0;
}

void DestroyEntityFromIndex(s16 index) {
    Entity* entity = &g_EntityArray[index];

    while (entity < &D_8007EF1C) {
        DestroyEntity(entity);
        entity++;
    }
}

void PreventEntityFromRespawning(Entity* entity) {
    if (entity->objectRoomIndex) {
        u32 value = (entity->objectRoomIndex - 1);
        u16 index = value / 32;
        u16 bit = value % 32;
        g_entityDestroyed[index] |= 1 << bit;
    }
}

#include "st/AnimateEntity.h"

INCLUDE_ASM("asm/us/st/nz0/nonmatchings/30958", func_801BCAD4);

/*
 * Returns the absolute distance from g_CurrentEntity to player in the X Axis
 */
s32 func_801BCBEC(void) {
    s16 xDistance = g_CurrentEntity->posX.i.hi - PLAYER.posX.i.hi;

    if (xDistance < 0) {
        xDistance = -xDistance;
    }
    return xDistance;
}

/*
 * Returns the absolute distance from g_CurrentEntity to player in the Y Axis
 */
s32 func_801BCC28(void) {
    s32 yDistance = g_CurrentEntity->posY.i.hi - PLAYER.posY.i.hi;

    if (yDistance < 0) {
        yDistance = -yDistance;
    }
    return yDistance;
}

s16 func_801BCC5C(void) {
    s16 var_a0 = g_CurrentEntity->posX.i.hi > PLAYER.posX.i.hi;

    if (g_CurrentEntity->posY.i.hi > PLAYER.posY.i.hi) {
        var_a0 |= 2;
    }
    return var_a0;
}

void MoveEntity(void) {
    g_CurrentEntity->posX.val += g_CurrentEntity->accelerationX;
    g_CurrentEntity->posY.val += g_CurrentEntity->accelerationY;
}

void FallEntity(void) {
    if (g_CurrentEntity->accelerationY < FALL_TERMINAL_VELOCITY) {
        g_CurrentEntity->accelerationY += FALL_GRAVITY;
    }
}

INCLUDE_ASM("asm/us/st/nz0/nonmatchings/30958", func_801BCCFC);

INCLUDE_ASM("asm/us/st/nz0/nonmatchings/30958", func_801BCF74);

Entity* AllocEntity(Entity* start, Entity* end) {
    Entity* current = start;

    while (current < end) {
        if (current->objectId == 0) {
            DestroyEntity(current);
            return current;
        }

        current++;
    }
    return NULL;
}

s32 func_801BD1BC(u8 arg0, s16 arg1) { return D_80181978[arg0] * arg1; }

s16 func_801BD1E8(u8 arg0) { return D_80181978[arg0]; } // Unique

void func_801BD204(s32 arg0, s16 arg1) {
    g_CurrentEntity->accelerationX = func_801BD1BC(arg0, arg1);
    g_CurrentEntity->accelerationY = func_801BD1BC(arg0 - 0x40, arg1);
}

u8 func_801BD270(s16 x, s16 y) { return ((ratan2(y, x) >> 4) + 0x40); }

u8 func_8019AD64(ObjInit2* arg0, ObjInit2* arg1) {
    u16 x, y;

    x = arg1->zPriority - arg0->zPriority;
    y = arg1->palette - arg0->palette;

    return func_801BD270(x, y);
}

u8 func_801BD2F0(s16 arg0, s16 arg1) {
    s16 x, y;

    x = arg0 - g_CurrentEntity->posX.i.hi;
    y = arg1 - g_CurrentEntity->posY.i.hi;

    return func_801BD270(x, y);
}

u8 func_801BD338(u8 arg0, u8 arg1, u8 arg2) {
    u8 var_v0;
    s8 temp_a2 = arg2 - arg1;

    if (temp_a2 < 0) {
        var_v0 = -temp_a2;
    } else {
        var_v0 = temp_a2;
    }

    if (var_v0 > arg0) {
        if (temp_a2 < 0) {
            var_v0 = arg1 - arg0;
        } else {
            var_v0 = arg1 + arg0;
        }

        return var_v0;
    }

    return arg2;
}

void func_801BD390(u16 slope, s16 speed) {
    Entity* entity;
    s32 moveX;
    s32 moveY;

    moveX = rcos(slope) * speed;
    entity = g_CurrentEntity;

    if (moveX < 0) {
        moveX += 15;
    }

    entity->accelerationX = moveX >> 4;

    moveY = rsin(slope) * speed;
    entity = g_CurrentEntity;

    if (moveY < 0) {
        moveY += 15;
    }

    entity->accelerationY = moveY >> 4;
}

u16 func_801BD41C(s16 x, s16 y) { return ratan2(y, x); }

u16 func_801BD44C(Entity* a, Entity* b) {
    s32 diffX = b->posX.i.hi - a->posX.i.hi;
    s32 diffY = b->posY.i.hi - a->posY.i.hi;
    return ratan2(diffY, diffX);
}

u16 func_801BD484(s32 x, s32 y) {
    s16 diffX = x - (u16)g_CurrentEntity->posX.i.hi;
    s16 diffY = y - (u16)g_CurrentEntity->posY.i.hi;
    return ratan2(diffY, diffX);
}

u16 func_801BD4CC(u16 arg0, s16 arg1, s16 arg2) {
    u16 var_v0 = arg1;
    u16 temp_a2 = arg2 - arg1;
    u16 var_v0_2;

    if (temp_a2 & 0x800) {
        var_v0_2 = (0x800 - temp_a2) & 0x7FF;
    } else {
        var_v0_2 = temp_a2;
    }

    if (var_v0_2 > arg0) {
        if (temp_a2 & 0x800) {
            var_v0 = arg1 - arg0;
        } else {
            var_v0 = arg1 + arg0;
        }

        return var_v0;
    }

    return arg2;
}

void func_801BD52C(u8 step) {
    Entity* entity;

    entity = g_CurrentEntity;
    entity->step = step;
    entity->unk2E = 0;
    entity->animFrameIdx = 0;
    entity->animFrameDuration = 0;
}

void func_801BD54C(u8 arg0) {
    Entity* entity;

    entity = g_CurrentEntity;
    entity->unk2E = arg0;
    entity->animFrameIdx = 0;
    entity->animFrameDuration = 0;
}

void func_801BD568(u16 arg0, u16 arg1) {
    if (arg1 != 0) {
        func_801C29B0(arg1);
    }

    if (arg0 == 0xFF) {
        DestroyEntity(g_CurrentEntity);
        return;
    }

    g_CurrentEntity->objectId = ENTITY_EXPLOSION;
    g_CurrentEntity->pfnUpdate = (PfnEntityUpdate)EntityExplosion;
    g_CurrentEntity->subId = arg0;
    g_CurrentEntity->animCurFrame = 0;
    g_CurrentEntity->unk19 = 0;
    g_CurrentEntity->step = 0;
    g_CurrentEntity->unk2E = 0;
}

void InitializeEntity(u16 arg0[]) {
    u16 enemyId;
    EnemyDef* enemyDef;

    g_CurrentEntity->animSet = *arg0++;
    g_CurrentEntity->animCurFrame = *arg0++;
    g_CurrentEntity->unk5A = *arg0++;
    g_CurrentEntity->palette = *arg0++;

    enemyId = *arg0++;
    g_CurrentEntity->enemyId = enemyId;
    enemyDef = &g_api.enemyDefs[enemyId];
    g_CurrentEntity->hitPoints = enemyDef->hitPoints;
    g_CurrentEntity->attack = enemyDef->attack;
    g_CurrentEntity->attackElement = enemyDef->attackElement;
    g_CurrentEntity->unk3C = enemyDef->unkC;
    g_CurrentEntity->hitboxWidth = enemyDef->hitboxWidth;
    g_CurrentEntity->hitboxHeight = enemyDef->hitboxHeight;
    g_CurrentEntity->flags = enemyDef->unk24;
    g_CurrentEntity->unk10 = 0;
    g_CurrentEntity->unk12 = 0;
    g_CurrentEntity->unk2E = 0;
    g_CurrentEntity->step++;
    if (g_CurrentEntity->zPriority == 0) {
        g_CurrentEntity->zPriority = g_zEntityCenter.S16.unk0 - 0xC;
    }
}

void EntityDummy(Entity* arg0) {
    if (arg0->step == 0) {
        arg0->step++;
    }
}

INCLUDE_ASM("asm/us/st/nz0/nonmatchings/30958", func_801BD720);

INCLUDE_ASM("asm/us/st/nz0/nonmatchings/30958", func_801BD848);

INCLUDE_ASM("asm/us/st/nz0/nonmatchings/30958", func_801BD9A0);

void ReplaceBreakableWithItemDrop(Entity* entity) {
    u16 subId;

    PreventEntityFromRespawning(entity);

    if (!(D_8009796E & 2)) {
        DestroyEntity(entity);
        return;
    }

    subId = entity->subId &= 0xFFF;

    if (subId < 0x80) {
        entity->objectId = ENTITY_PRICE_DROP;
        entity->pfnUpdate = EntityPriceDrop;
        entity->animFrameDuration = 0;
        entity->animFrameIdx = 0;
    } else {
        subId -= 0x80;
        entity->objectId = ENTITY_INVENTORY_DROP;
        entity->pfnUpdate = (PfnEntityUpdate)EntityInventoryDrop;
    }

    entity->subId = subId;
    entity->unk6D = 0x10;
    entity->step = 0;
}

// aspatch skips a nop, ASPSX
#ifndef NON_MATCHING
INCLUDE_ASM("asm/us/st/nz0/nonmatchings/30958", func_801BDD9C);
#else
void func_801BDD9C(void) {
    if (g_CurrentEntity->accelerationY >= 0) {
        g_CurrentEntity->unk84.unk += g_CurrentEntity->unk88.S16.unk0;
        g_CurrentEntity->accelerationX = g_CurrentEntity->unk84.unk;

        if ((g_CurrentEntity->accelerationX == 0x10000) ||
            (g_CurrentEntity->accelerationX == -0x10000)) {
            g_CurrentEntity->unk88.U16.unk0 = -g_CurrentEntity->unk88.U16.unk0;
        }
    }

    if (g_CurrentEntity->accelerationY < 0x4000) {
        g_CurrentEntity->accelerationY += 0x2000;
    }
}
#endif

void func_801BDE20(u16 arg0) {
    Collider res;

    if (g_CurrentEntity->accelerationX < 0) {
        g_api.CheckCollision(g_CurrentEntity->posX.i.hi,
                             g_CurrentEntity->posY.i.hi - 7, &res, 0);
        if (res.unk0 & 5) {
            g_CurrentEntity->accelerationY = 0;
        }
    }

    g_api.CheckCollision(g_CurrentEntity->posX.i.hi,
                         g_CurrentEntity->posY.i.hi + 7, &res, 0);

    if (arg0) {
        if (!(res.unk0 & 5)) {
            MoveEntity();
            FallEntity();
            return;
        }

        g_CurrentEntity->accelerationX = 0;
        g_CurrentEntity->accelerationY = 0;

        if (res.unk0 & 4) {
            g_CurrentEntity->posY.val += 0x2000;
        } else {
            g_CurrentEntity->posY.i.hi += LOH(res.unk18);
        }
    } else {
        if (!(res.unk0 & 5)) {
            MoveEntity();
            func_801BDD9C();
        }
    }
}

void CollectHeart(u16 heartSize) {
    s32* hearts;

    g_api.PlaySfx(NA_SE_PL_COLLECT_HEART);
    hearts = &D_80097BA0.hearts;
    *hearts += c_HeartPrizes[heartSize];

    if (D_80097BA0.heartsMax < *hearts) {
        *hearts = D_80097BA0.heartsMax;
    }

    DestroyEntity(g_CurrentEntity);
}

void CollectGold(u16 goldSize) {
    s32 *gold, *unk;
    u16 goldSizeIndex;

    g_api.PlaySfx(NA_SE_PL_COLLECT_GOLD);
    gold = &g_playerGold;
    goldSizeIndex = goldSize - 2;
    *gold += c_GoldPrizes[goldSizeIndex];
    if (*gold > MAX_GOLD) {
        *gold = MAX_GOLD;
    }

    unk = &D_80097410;
    if (*unk) {
        g_api.FreePolygons(D_80097414);
        *unk = 0;
    }

    func_801C33D8(D_80181CEC[goldSizeIndex], 1);
    DestroyEntity(g_CurrentEntity);
}

// https://decomp.me/scratch/gto6i
INCLUDE_ASM("asm/us/st/nz0/nonmatchings/30958", func_801BE0D8);

void CollectHeartVessel(void) {
    if (g_CurrentPlayableCharacter != PLAYER_ALUCARD) {
        g_api.PlaySfx(NA_SE_PL_COLLECT_HEART);
        D_80097BA0.hearts += HEART_VESSEL_RICHTER;

        if (D_80097BA0.heartsMax < D_80097BA0.hearts) {
            D_80097BA0.hearts = D_80097BA0.heartsMax;
        }
    } else {
        g_api.PlaySfx(NA_SE_PL_COLLECT_HEART);
        g_api.func_800FE044(HEART_VESSEL_INCREASE, 0x4000);
    }
    DestroyEntity(g_CurrentEntity);
}

void CollectLifeVessel(void) {
    g_api.PlaySfx(NA_SE_PL_COLLECT_HEART);
    g_api.func_800FE044(5, 0x8000);
    DestroyEntity(g_CurrentEntity);
}

void DestroyCurrentEntity(void) { DestroyEntity(g_CurrentEntity); }

INCLUDE_ASM("asm/us/st/nz0/nonmatchings/30958", EntityPriceDrop);

void EntityExplosion(Entity* entity) {
    u32 temp_v0;

    if (entity->step == 0) {
        InitializeEntity(D_80180BE0);
        entity->animSet = 2;
        entity->animFrameIdx = 0;
        entity->animFrameDuration = 0;
        entity->blendMode = 0x30;

        if (entity->subId & 0xF0) {
            entity->palette = 0x8195;
            entity->blendMode = 0x10;
        }

        temp_v0 = entity->subId & 0xFF00;
        if (temp_v0) {
            entity->zPriority = temp_v0 >> 8;
        }

        entity->subId = entity->subId & 0xF;
        entity->accelerationY = D_80181DA8[entity->subId];
        return;
    }

    entity->posY.val += entity->accelerationY;
    if (!AnimateEntity(D_80181E54[entity->subId], entity)) {
        DestroyEntity(entity);
    }
}

void func_801BEC7C(Entity* entity, s32 arg1) {
    POLY_GT4* poly;
    s16 left, top, right, bottom;

    poly = &D_80086FEC[entity->firstPolygonIndex];

    left = entity->posX.i.hi - 7;
    right = entity->posX.i.hi + 7;
    poly->x2 = left;
    poly->x0 = left;
    poly->x3 = right;
    poly->x1 = right;

    top = entity->posY.i.hi - 7;
    bottom = entity->posY.i.hi + 7;
    poly->y1 = top;
    poly->y0 = top;
    poly->y3 = bottom;
    poly->y2 = bottom;

    if (arg1 & RENDERFLAGS_NOSHADOW) {
        poly->r0 = poly->r1 = poly->r2 = poly->r3 = poly->g0 = poly->g1 =
            poly->g2 = poly->g3 = poly->b0 = poly->b1 = poly->b2 = poly->b3 =
                255;
    } else {
        poly->r0 = poly->r1 = poly->r2 = poly->r3 = poly->g0 = poly->g1 =
            poly->g2 = poly->g3 = poly->b0 = poly->b1 = poly->b2 = poly->b3 =
                128;
    }
}

INCLUDE_ASM("asm/us/st/nz0/nonmatchings/30958", EntityInventoryDrop);

INCLUDE_ASM("asm/us/st/nz0/nonmatchings/30958", func_801BF308);

INCLUDE_ASM("asm/us/st/nz0/nonmatchings/30958", EntityRelicOrb);

INCLUDE_ASM("asm/us/st/nz0/nonmatchings/30958", EntityHeartDrop);

INCLUDE_ASM("asm/us/st/nz0/nonmatchings/30958", EntityUnkId0E);

u8 func_801C070C(s16* arg0, u8 facing) {
    u8 ret = 0;
    Collider res;
    s16 posX, posY;

    while (*arg0 != 0xFF) {
        ret <<= 1;

        posX = facing ? (g_CurrentEntity->posX.i.hi + *arg0++)
                      : (g_CurrentEntity->posX.i.hi - *arg0++);
        posY = g_CurrentEntity->posY.i.hi + *arg0++;

        g_api.CheckCollision(posX, posY, &res, 0);

        if (res.unk0 & 1) {
            ret |= 1;
        }
    }

    return ret;
}

void func_801C07FC(Entity* entity) {
    switch (entity->step) {
    case 0:
        InitializeEntity(D_80180C04);
        entity->unk8C.modeU16.unk0 = entity->unk80.entityPtr->objectId;
    case 1:
        if (entity->unk7C.U8.unk0++ >= 5) {
            Entity* newEntity =
                AllocEntity(D_8007D858, &D_8007D858[MaxEntityCount]);
            if (newEntity != NULL) {
                CreateEntityFromEntity(ENTITY_EXPLOSION, entity, newEntity);
                newEntity->objectId = ENTITY_EXPLOSION;
                newEntity->pfnUpdate = EntityExplosion;
                newEntity->subId = entity->subId;
            }
            entity->unk7C.U8.unk0 = 0;
        }
        entity->posX.i.hi = entity->unk80.entityPtr->posX.i.hi;
        entity->posY.i.hi = entity->unk80.entityPtr->posY.i.hi;
        if (entity->unk80.entityPtr->objectId != entity->unk8C.modeU16.unk0) {
            DestroyEntity(entity);
        }
        break;
    }
}

// https://decomp.me/scratch/0VI4v
INCLUDE_ASM("asm/us/st/nz0/nonmatchings/30958", func_801C090C);

INCLUDE_ASM("asm/us/st/nz0/nonmatchings/30958", func_801C0A3C);

void func_801C0B24(Entity* entity) {
    if (entity->step == 0) {
        entity->accelerationY = D_80181F04[entity->unk94];
        entity->flags = 0x2000 | FLAG_UNK_04000000 | FLAG_UNK_08000000;
        entity->palette = 0x8195;
        entity->animSet = 2;
        entity->animCurFrame = D_80181F1C[entity->subId];
        entity->blendMode = 0x10;
        entity->step++;
    } else {
        entity->animFrameDuration++;
        entity->posY.val -= entity->accelerationY;

        if (!(entity->animFrameDuration & 1)) {
            entity->animCurFrame++;
        }

        if (D_80181F20[entity->subId] < (s32)entity->animFrameDuration) {
            DestroyEntity(entity);
        }
    }
}

void func_801C0C14(Entity* entity) {
    u16 temp_v0;
    u32 temp2;

    if (entity->step == 0) {
        entity->flags = 0x2000 | FLAG_UNK_04000000 | FLAG_UNK_08000000;
        entity->palette = 0x8195;
        entity->animSet = 5;
        entity->animCurFrame = 1;
        entity->blendMode = 0x10;
        entity->unk19 = 3;
        temp_v0 = D_80181EDC[entity->subId];
        entity->unk1A = temp_v0;
        entity->unk1C = temp_v0;
        temp2 = D_80181EEC[entity->subId];
        entity->step += 1;
        entity->accelerationY = temp2;
    } else {
        entity->animFrameDuration++;
        entity->posY.val -= entity->accelerationY;

        if (!(entity->animFrameDuration & 1)) {
            entity->animCurFrame++;
        }

        if (entity->animFrameDuration >= 0x25) {
            DestroyEntity(entity);
        }
    }
}

INCLUDE_ASM("asm/us/st/nz0/nonmatchings/30958", func_801C0D08);

bool func_801C0F38(Unkstruct6* unk) {
    Collider res;

    FallEntity();
    g_CurrentEntity->posX.val += g_CurrentEntity->accelerationX;
    g_CurrentEntity->posY.val += g_CurrentEntity->accelerationY;

    if (g_CurrentEntity->accelerationY >= 0) {
        s16 posX = g_CurrentEntity->posX.i.hi;
        s16 posY = g_CurrentEntity->posY.i.hi;
        posX += unk->x;
        posY += unk->y;
        g_api.CheckCollision(posX, posY, &res, 0);
        if (res.unk0 & 1) {
            g_CurrentEntity->posY.i.hi += LOH(res.unk18);
            g_CurrentEntity->accelerationY =
                -g_CurrentEntity->accelerationY / 2;
            if (g_CurrentEntity->accelerationY > -0x10000) {
                return true;
            }
        }
    }
    return false;
}

INCLUDE_ASM("asm/us/st/nz0/nonmatchings/30958", func_801C1034);

void EntityIntenseExplosion(Entity* entity) {
    u32 temp_v0;

    if (entity->step == 0) {
        InitializeEntity(D_80180BE0);
        entity->palette = 0x8170;
        entity->animSet = 5;
        entity->animCurFrame = 1;
        entity->blendMode = 0x30;

        if (entity->subId & 0xF0) {
            entity->palette = 0x8195;
            entity->blendMode = 0x10;
        }

        temp_v0 = entity->subId & 0xFF00;
        if (temp_v0 != 0) {
            entity->zPriority = temp_v0 >> 8;
        }

        entity->zPriority += 8;
        return;
    }

    entity->animFrameDuration++;
    entity->posY.val -= 0x4000;

    if (!(entity->animFrameDuration & 1)) {
        entity->animCurFrame++;
    }

    if (entity->animFrameDuration >= 0x25) {
        DestroyEntity(entity);
    }
}

void func_801C16B4(Entity* entity) {
    if (entity->step == 0) {
        InitializeEntity(D_80180BE0);
        entity->unk6C = 0xF0;
        entity->unk1A = 0x1A0;
        entity->unk1C = 0x1A0;
        entity->animSet = 8;
        entity->animCurFrame = 1;
        entity->zPriority += 0x10;

        if (entity->subId != 0) {
            entity->palette = entity->subId;
        } else {
            entity->palette = 0x8160;
        }

        entity->step++;
    } else {
        MoveEntity();
        if (!AnimateEntity(&D_80181F30, entity)) {
            DestroyEntity(entity);
        }
    }
}

void func_801C1780(u16 objectId, Entity* src, Entity* dst) {
    DestroyEntity(dst);
    dst->objectId = objectId;
    dst->pfnUpdate = D_80180A90[objectId];
    dst->posX.i.hi = src->posX.i.hi;
    dst->posY.i.hi = src->posY.i.hi;
    dst->unk5A = src->unk5A;
    dst->zPriority = src->zPriority;
    dst->animSet = src->animSet;
    dst->flags = 0x1002000 | FLAG_UNK_04000000 | FLAG_UNK_08000000 |
                 FLAG_DESTROY_IF_BARELY_OUT_OF_CAMERA |
                 FLAG_DESTROY_IF_OUT_OF_CAMERA;

    if (src->palette & 0x8000) {
        dst->palette = src->unk6A;
    } else {
        dst->palette = (s16)src->palette;
    }
}

void func_801C1848(void) {
    s32 temp_s3;
    s8 temp_s4;
    Entity* entity;
    s32 i;

    temp_s4 = Random() & 3;
    temp_s3 = ((Random() & 0xF) << 8) - 0x800;

    for (i = 0; i < 6; i++) {
        entity = AllocEntity(D_8007D858, &D_8007D858[MaxEntityCount]);
        if (entity != NULL) {
            CreateEntityFromEntity(ENTITY_EXPLOSION, g_CurrentEntity, entity);
            entity->unk84.U8.unk1 = 6 - i;
            entity->unk80.modeS16.unk0 = temp_s3;
            entity->unk84.U8.unk0 = temp_s4;
        }
    }
}

void func_801C1900(Entity* self) {
    s32 accelerationX;
    s32 accelerationY;
    s32 temp;

    if (self->step == 0) {
        InitializeEntity(D_80180BE0);
        self->animSet = 2;
        self->palette = 0x81B6;
        self->unk6C = 0x70;
        self->zPriority = 192;
        self->unk19 |= 0xC;
        self->blendMode |= 0x30;

        switch (self->unk84.U8.unk0) {
        case 1:
            if (self->unk84.U8.unk1 >= 4) {
                self->unk84.U8.unk1 += 253;
                self->unk80.modeS16.unk0 -= 0x800;
            }
            break;

        case 2:
            self->unk80.modeS16.unk0 += self->unk84.U8.unk1 * 192;
            break;
        }

        self->unk1E = self->unk80.modeS16.unk0 &= 0xFFF;
        temp = (self->unk84.U8.unk1 * 320) / 24;
        self->accelerationX = temp * rsin(self->unk80.modeS16.unk0);
        self->accelerationY = -(temp * rcos(self->unk80.modeS16.unk0));
    }

    if (self->animFrameIdx >= 13) {
        accelerationX = self->accelerationX;
        if (accelerationX < 0) {
            accelerationX += 3;
        }

        accelerationY = self->accelerationY;
        self->accelerationX = (accelerationX >> 2) * 3;
        if (accelerationY < 0) {
            accelerationY += 3;
        }
        self->accelerationY = (accelerationY >> 2) * 3;
    }

    MoveEntity();

    if (AnimateEntity(&D_80181DD0, self) == 0) {
        DestroyEntity(self);
    }
}

INCLUDE_ASM("asm/us/st/nz0/nonmatchings/30958", func_801C1AD8);

INCLUDE_ASM("asm/us/st/nz0/nonmatchings/30958", func_801C20B8);

INCLUDE_ASM("asm/us/st/nz0/nonmatchings/30958", func_801C27B8);

// https://decomp.me/scratch/Cxlhx 93.39 % 4 missing instructions
INCLUDE_ASM("asm/us/st/nz0/nonmatchings/30958", func_801C29B0);

INCLUDE_ASM("asm/us/st/nz0/nonmatchings/30958", EntityAbsorbOrb);

INCLUDE_ASM("asm/us/st/nz0/nonmatchings/30958", EntityEnemyBlood);

void EntityRoomForeground(Entity* entity) {
    ObjInit2* objInit = &D_80182014[entity->subId];

    if (entity->step == 0) {
        InitializeEntity(D_80180C1C);
        entity->animSet = objInit->animSet;
        entity->zPriority = objInit->zPriority;
        entity->unk5A = objInit->unk4.s;
        entity->palette = objInit->palette;
        entity->unk19 = objInit->unk8;
        entity->blendMode = objInit->blendMode;

        if (objInit->unkC != 0) {
            entity->flags = objInit->unkC;
        }

        if (entity->subId >= 5) {
            entity->unk1E = 0x800;
            entity->unk19 |= 4;
        }
    }
    AnimateEntity(objInit->unk10, entity);
}

INCLUDE_ASM("asm/us/st/nz0/nonmatchings/30958", func_801C33D8);

void func_801C3708(void) {
    s32 temp = func_801BCF74(&D_8018216C);
    s32 temp2 = func_801BD720(&D_80182174, 3);

    if ((temp == 128) || (temp2 & 2)) {
        func_801BD52C(5);
        return;
    }

    if (g_CurrentEntity->unk7C.U8.unk0 == 0) {
        if (func_801BCBEC() < 64) {
            if (g_CurrentEntity->facing != (func_801BCC5C() & 1)) {
                func_801BD52C(4);
            }
        }
    } else {
        g_CurrentEntity->unk7C.U8.unk0--;
    }
}

INCLUDE_ASM("asm/us/st/nz0/nonmatchings/30958", EntityBoneScimitar);

// debris that rotates and falls down
void EntityFallingDebris(Entity* entity) {
    if (entity->step) {
        entity->unk88.S8.unk0--;
        if (entity->unk88.S8.unk0 & 0xFF) {
            entity->unk1E += D_801820E4[entity->subId];
            FallEntity();
            MoveEntity();
            return;
        }
        entity->objectId = ENTITY_EXPLOSION;
        entity->pfnUpdate = EntityExplosion;
        entity->subId = 0;
        entity->step = 0;
        return;
    }
    InitializeEntity(&D_80180C58);
    entity->unk19 = 4;
    entity->animCurFrame = *(u8*)&entity->subId + 16;

    if (entity->facing != 0) {
        entity->accelerationX = -entity->accelerationX;
    }

    if (entity->subId & 0xF00) {
        entity->palette += entity->subId / 256;
    }
}

// Unique
INCLUDE_ASM("asm/us/st/nz0/nonmatchings/30958", func_801C3F9C);

// Unique
INCLUDE_ASM("asm/us/st/nz0/nonmatchings/30958", func_801C4198);

void func_801C4550(void) {
    if (g_CurrentEntity->unk80.modeS16.unk2 > 0) {
        g_CurrentEntity->unk80.modeS16.unk2 -= 3;
    } else {
        func_801BD52C(D_801822B4[(Random() & 7)]);
        g_CurrentEntity->unk80.modeS16.unk2 = 0x100;
    }
}

// green knight that throws axes
// Unique
INCLUDE_ASM("asm/us/st/nz0/nonmatchings/30958", EntityAxeKnight);

void func_801C4CC0(void) {
    if (g_CurrentEntity->subId != 0) {
        g_CurrentEntity->unk1E += 0x80;
    } else {
        g_CurrentEntity->unk1E -= 0x80;
    }

    g_CurrentEntity->unk1E &= 0xFFF;
}

void EntityAxeKnightThrowingAxe(Entity* entity) {
    s32 var_v0;

    if (entity->flags & 0x100) {
        func_801C29B0(0x66B);
        func_801BD568(0, 0);
        return;
    }

    switch (entity->step) {
    case 0:
        InitializeEntity(D_80180C70);
        entity->unk19 = 4;
        entity->accelerationY = D_801822C8[entity->subId];
        var_v0 = D_801822BC[entity->subId];

        if (entity->facing == 0) {
            entity->accelerationX = -var_v0;
        } else {
            entity->accelerationX = var_v0;
        }

        entity->unk7C.s = -0x40;

        if (entity->subId == 2) {
            entity->step++;
            return;
        }
        break;

    case 1:
        func_801C4CC0();
        if ((u16)entity->unk7C.s < 0x20) {
            if (entity->facing != 0) {
                var_v0 = entity->accelerationX - 0x2000;
            } else {
                var_v0 = entity->accelerationX + 0x2000;
            }
            entity->accelerationX = var_v0;
        }

        entity->unk7C.s++;
        MoveEntity();
        break;

    case 2:
        func_801C4CC0();
        entity->accelerationY += 0x2000;
        MoveEntity();
        break;
    }
}

INCLUDE_ASM("asm/us/st/nz0/nonmatchings/30958", EntityBloodSplatter);

INCLUDE_ASM("asm/us/st/nz0/nonmatchings/30958", func_801C53AC);

// Unique
INCLUDE_ASM("asm/us/st/nz0/nonmatchings/30958", EntityBloodDrips);

INCLUDE_ASM("asm/us/st/nz0/nonmatchings/30958", func_801C5D20);

void func_801C5F2C(Entity* arg0) {
    if ((func_801BCF74(&D_801824B8) & 0x60) == 0x60) {
        arg0->posX.val -= arg0->accelerationX;
    }

    if (!(func_801BD720(&D_801824C0, 3) & 2)) {
        if ((--arg0->unk7C.U8.unk0) == 0) {
            func_801BD52C(4);
        }
    } else {
        func_801BD52C(5);
    }
}

// throws bones at you
// Unique
INCLUDE_ASM("asm/us/st/nz0/nonmatchings/30958", EntitySkeleton);

void func_801C6494(Entity* entity) {
    if (entity->step) {
        entity->unk88.S8.unk0--;
        if (entity->unk88.S8.unk0 & 0xFF) {
            entity->unk1E += D_80182424[entity->subId];
            FallEntity();
            MoveEntity();
            return;
        }

        entity->objectId = ENTITY_EXPLOSION;
        entity->pfnUpdate = (PfnEntityUpdate)EntityExplosion;
        entity->subId = 0;
        entity->step = 0;
        return;
    }

    InitializeEntity(&D_80180C94);
    entity->unk19 = 4;
    entity->animCurFrame = entity->subId + 15;

    if (entity->facing != 0) {
        entity->accelerationX = -entity->accelerationX;
    }
}

void func_801C6574(Entity* entity) {
    s32 var_a0;
    u32 value;

    if (entity->step) {
        if (entity->flags & 0x100) {
            func_801BD568(0, 0);
            return;
        }

        entity->unk1E += 0x80;
        entity->accelerationY += 0x2400;
        MoveEntity();

        if (entity->posY.i.hi > 240) {
            DestroyEntity(entity);
        }
    } else {
        InitializeEntity(&D_80180CA0);
        entity->posY.val -= 0x1000;
        value = func_801BCBEC();
        value /= 32;
        value = CLAMP_MAX(value, 7);
        var_a0 = D_80182488[value];
        value = entity->facing;

        if (value > 0) {
            var_a0 = -var_a0;
        }

        entity->accelerationY = -0x48000;
        entity->accelerationX = var_a0;
        entity->unk19 = 4;
    }
}

void func_801C6678(Entity* entity) {
    if (entity->step == 0) {
        InitializeEntity(D_80180C88);
        entity->unk1A = 0x120;
        entity->unk1C = 0x200;
        entity->unk6C = 0;
        entity->unk3C = 0;
        entity->unk19 = entity->unk19 | 0xB;
        return;
    }

    entity->facing = entity[-1].facing;
    entity->zPriority = entity[-1].zPriority - 1;
    entity->animCurFrame = entity[-1].animCurFrame;
    entity->posX.i.hi = entity[-1].posX.i.hi;
    entity->posY.i.hi = entity[-1].posY.val - 0x14;

    if (entity[-1].objectId != 0x2E) {
        DestroyEntity(entity);
    }
}
