#include "np3.h"

INCLUDE_ASM("asm/us/st/np3/nonmatchings/4B018", func_801CB018);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/4B018", func_801CBF18);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/4B018", func_801CC2E0);

void func_801CD540(Entity* self) {
    s8* hitbox;
    s32 diff;

    if (self->step == 0) {
        InitializeEntity(D_80180B20);
    }

    self->facing = self[-1].facing;
    self->posX.i.hi = self[-1].posX.i.hi;
    self->posY.i.hi = self[-1].posY.i.hi;
    hitbox = D_80182914;
    diff = D_80182935[self[-1].animCurFrame];

    diff -= 4;
    if (diff < 0) {
        diff = 0;
    }

    hitbox += diff * 4;
    self->hitboxOffX = *hitbox++;
    self->hitboxOffY = *hitbox++;
    self->hitboxWidth = hitbox[0];
    self->hitboxHeight = hitbox[1];
    if (self[-1].entityId != 0x44) {
        DestroyEntity(self);
    }
}

void func_801CD620(Entity* self) {
    if (self->step == 0) {
        InitializeEntity(D_80180A6C);
    }
}

INCLUDE_ASM("asm/us/st/np3/nonmatchings/4B018", func_801CD658);

void func_801CD734() {
    while (PadRead(0))
        func_801CD658();
    while (!PadRead(0))
        func_801CD658();
}

INCLUDE_ASM("asm/us/st/np3/nonmatchings/4B018", func_801CD78C);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/4B018", func_801CD83C);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/4B018", func_801CD91C);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/4B018", func_801CDA14);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/4B018", func_801CDA6C);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/4B018", func_801CDAC8);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/4B018", func_801CDC80);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/4B018", func_801CDD00);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/4B018", func_801CDD80);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/4B018", func_801CDE10);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/4B018", func_801CDE88);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/4B018", func_801CDF1C);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/4B018", func_801CDFD8);

void func_801CE04C(Entity* entity, Collider* collider) {
    s16 var_s0 = 0;

    g_api.CheckCollision(
        entity->posX.i.hi, (s16)(entity->posY.i.hi + collider->unk18), collider,
        0);
    if (collider->effects & 1) {
        var_s0 = 1;
        if (collider->effects & 0x8000) {
            if (collider->effects & 0x4000) {
                if (g_CurrentEntity->facing != 0) {
                    var_s0 = 4;
                } else {
                    var_s0 = 2;
                }
            } else {
                if (g_CurrentEntity->facing != 0) {
                    var_s0 = 2;
                } else {
                    var_s0 = 4;
                }
            }
        }
    }
    entity->ext.generic.unk88.S16.unk0 = var_s0;
}

INCLUDE_ASM("asm/us/st/np3/nonmatchings/4B018", func_801CE120);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/4B018", func_801CE1E8);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/4B018", func_801CE228);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/4B018", func_801CE258);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/4B018", func_801CE2CC);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/4B018", func_801CE3FC);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/4B018", func_801CE4CC);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/4B018", EntityHammer);

// DECOMP_ME_WIP func_801CF254 https://decomp.me/scratch/EpZEL
// minor regalloc
// has jumptable
#ifndef NON_MATCHING
INCLUDE_ASM("asm/us/st/np3/nonmatchings/4B018", func_801CF254);
#else
extern u16 D_80180B8C[];
extern u16 D_80180BA4[];
extern u16 D_80180BBC[];

void func_801CF254(Entity* self) {
    Collider collider;
    s32 aaaa;
    s32 sp28;
    s16 temp_s0;
    s16 temp_s0_2;
    s16 temp_v0_3;
    s32 temp_s1;
    u16 temp_v0;
    u16 temp_v0_2;
    u16 temp_v1;
    u16 temp_v1_3;
    u16* var_a0;
    u32 temp_v1_2;
    u16 temp_a0;

    switch (self->step) {
    case 0:
        switch (self->params >> 8) {
        case 0:
            InitializeEntity(D_80180B8C);
            break;
        case 1:
            InitializeEntity(D_80180BA4);
            break;
        case 2:
            InitializeEntity(D_80180BBC);
            break;
        }
        self->hitboxWidth = 6;
        self->hitboxHeight = 6;
        self->params = (u8)self->params;
        self->animCurFrame = self->params;
        self->unk19 |= 4;
        break;

    case 1:
        self->unk1E = self->ext.et_801CF254.unk9C;
        break;

    case 24:
        switch (self->step_s) {
        case 0:
            temp_s1 = (Random() & 0x1F) + 0x10;
            temp_s0_2 = (Random() * 6) + 0x900;
            self->velocityX = (s32)(temp_s1 * rcos((s32)temp_s0_2)) / 2;
            self->velocityY = temp_s1 * rsin((s32)temp_s0_2);
            self->ext.generic.unk80.modeS16.unk0 = (Random() & 0x1F) + 0x20;
            self->unk3C = 0;
            self->flags |= FLAG_DESTROY_IF_OUT_OF_CAMERA;
            self->step_s++;
            break;

        case 1:
            MoveEntity();
            self->velocityY += 0x2000;
            self->unk1E += self->ext.generic.unkA6;
            if (--self->ext.generic.unk80.modeS16.unk0 == 0) {
                self->step = 0;
                self->pfnUpdate = EntityExplosion;
                self->params = 0;
                self->unk19 = 0;
                return;
            }
        }
        break;
    }

    switch (self->params) {
    case 8:
    case 14:
        collider.unk18 = 9;
        func_801CE04C(self, &collider);
        break;

    case 9:
    case 15:
        aaaa = self->ext.et_801CF254.next->ext.et_801CF254.unk88;
        if (aaaa == 2) {
            self->ext.et_801CF254.unk9C = 0x200;
        } else if (aaaa == 4) {
            self->ext.et_801CF254.unk9C = -0x200;
        } else if (aaaa == 1) {
            self->ext.et_801CF254.unk9C = 0;
        }

        if (self->ext.et_801CF254.unk8D != 0) {
            temp_s0 = self->unk1E;
            self->unk10 = -(rsin(temp_s0) * 8) >> 0xC;
            self->unk12 = (u32)rcos(temp_s0) >> 9;
            self->attack = g_api.enemyDefs[192].attack;
            self->attackElement = g_api.enemyDefs[192].attackElement;
            break;
        }
        self->unk10 = 0;
        self->unk12 = 0;
        self->attack = g_api.enemyDefs[190].attack;
        self->attackElement = g_api.enemyDefs[190].attackElement;
        break;

    case 5:
    case 11:
        self->ext.et_801CF254.next->ext.et_801CF254.unk9C =
            self->ext.et_801CF254.unk9C;
    }
}
#endif

void EntityHammerWeapon(Entity* self) {
    s16 temp_s0;
    s32 velY;
    s32 temp_s1;
    s16 angle;

    switch (self->step) {
    case 0:
        InitializeEntity(D_80180B98);
        self->hitboxWidth = 10;
        self->hitboxHeight = 10;
        self->unk19 |= 4;

    case 1:
        angle = *(u16*)&self->ext.stub[0x20];
        self->rotAngle = angle;
        self->hitboxOffX = ((u32)(rsin(angle) * 0xD) >> 0xA);
        self->hitboxOffY = (-(rcos(angle) * 0x34) >> 0xC);
        break;

    case 24:
        switch (self->step_s) {
        case 0:
            temp_s1 = (Random() & 0x1F) + 0x10;
            temp_s0 = (Random() * 6) + 0x900;
            self->velocityX = (temp_s1 * rcos(temp_s0)) / 2;
            velY = temp_s1 * rsin(temp_s0);
            self->hitboxState = 0;
            self->flags |= FLAG_DESTROY_IF_OUT_OF_CAMERA;
            self->step_s++;
            self->velocityY = velY;
            break;

        case 1:
            MoveEntity();
            self->velocityY += 0x2000;
            func_801CDC80(&self->rotAngle, 0x800, 0x20);
            break;
        }
    }
}

INCLUDE_ASM("asm/us/st/np3/nonmatchings/4B018", func_801CF778);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/4B018", func_801CF7A0);

// DECOMP_ME_WIP EntityGurkha https://decomp.me/scratch/51iIJ
INCLUDE_ASM("asm/us/st/np3/nonmatchings/4B018", EntityGurkha);

void EntityGurkhaSword(Entity* self) {
    s16 angle;
    s32 rnd;

    switch (self->step) {
    case 0:
        InitializeEntity(D_80180BB0);
        self->hitboxWidth = 8;
        self->hitboxHeight = 8;
        self->unk19 |= 4;
        break;

    case 1:
        angle = self->ext.gurkhaSword.unk9C;
        self->rotAngle = angle;
        self->hitboxOffX = (u32)rsin(angle) >> 8;
        self->hitboxOffY = -(rcos(angle) * 16) >> 0xC;
        if (self->ext.gurkhaSword.unk8C) {
            self->step++;
        }
        break;

    case 2:
        if (self->facing == 0) {
            self->velocityX = -0x80000;
        } else {
            self->velocityX = 0x80000;
        }
        self->step++;

    case 3:
        MoveEntity();
        self->rotAngle -= 0x100;
        self->ext.gurkhaSword.unk9C = self->rotAngle;
        self->ext.gurkhaSword.unkA6 = -0xC0;
        angle = self->rotAngle;
        self->hitboxOffX = (u32)rsin(self->rotAngle) >> 8;
        self->hitboxOffY = -(rcos(angle) * 16) >> 0xC;

        if (self->facing != 0) {
            self->velocityX -= 0x4000;
        } else {
            self->velocityX += 0x4000;
        }

        if ((g_blinkTimer % 16) == 0) {
            func_801C2598(0x625);
        }

        if (ABS(self->velocityX) == 0x80000) {
            self->ext.gurkhaSword.unk8C = 0;
            self->step = 1;
        }
        break;

    case 24:
        switch (self->step_s) {
        case 0:
            rnd = (Random() & 0x1F) + 0x10;
            angle = (Random() * 6) + 0x900;
            self->velocityX = (rnd * rcos(angle)) / 2;
            self->velocityY = rnd * rsin(angle);
            self->ext.gurkhaSword.unk80 = (Random() & 0x1F) + 0x20;
            self->hitboxState = 0;
            self->flags |= FLAG_DESTROY_IF_OUT_OF_CAMERA;
            self->step_s++;
            break;

        case 1:
            MoveEntity();
            self->velocityY += 0x2000;
            self->rotAngle += self->ext.gurkhaSword.unkA6;
            if (--self->ext.gurkhaSword.unk80 == 0) {
                self->step = 0;
                self->pfnUpdate = EntityExplosion;
                self->params = 0;
                self->unk19 = 0;
            }
        }
        break;
    }
}

INCLUDE_ASM("asm/us/st/np3/nonmatchings/4B018", func_801D0A00);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/4B018", func_801D0B40);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/4B018", func_801D0B78);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/4B018", func_801D0D40);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/4B018", func_801D1BB8);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/4B018", func_801D1F38);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/4B018", func_801D2320);

Primitive* func_801D2470(Primitive* poly) {
    while (poly != NULL) {
        if (poly->p3 != 0) {
            poly = poly->next;
        } else {
            return poly;
        }
    }
    return NULL;
}

Primitive* func_801D24A0(Primitive* prim, u8 index) {
    if (prim) {
        s32 index_ = index;
    loop_2:
        if (prim->p3 == 0) {
            Primitive* var_v0 = NULL;
            Primitive* firstPrim = prim;
            s32 i = 1;
            if (i < index_) {
                do {
                    prim = prim->next;
                    if (!prim)
                        return NULL;
                } while (prim->p3 == 0 && ++i < index);
            }
            var_v0 = firstPrim;
            if (i == index_)
                return var_v0;
        }
        prim = prim->next;
        if (prim) {
            goto loop_2;
        }
    }
    return NULL;
}

POLY_GT4* func_801D251C(POLY_GT4* startPoly, s32 count) {
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

void func_801D25A4(POLY_GT4* arg0) {
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

void func_801D2684(POLY_GT4* arg0) {
    func_801D25A4(arg0);
    arg0->p3 = 8;
    ((POLY_GT4*)arg0->tag)->p3 = 1;
    ((POLY_GT4*)arg0->tag)->code = 2;
    ((POLY_GT4*)arg0->tag)->pad3 = 0xA;
}

void func_801D26D8(POLY_GT4* arg0) {
    arg0->p3 = 0;
    arg0->pad3 = 8;
    ((POLY_GT4*)arg0->tag)->p3 = 0;
    ((POLY_GT4*)arg0->tag)->code = 4;
    ((POLY_GT4*)arg0->tag)->pad3 = 8;
}

s32 func_801D2704(s32 arg0, u8 arg1) {
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
        } while (((s32)var_v1 < ((s32)var_a0 + 3)));

        var_a0 += 0xC;
    }

    return ret;
}