#include "np3.h"

INCLUDE_ASM("asm/us/st/np3/nonmatchings/4E69C", EntityHammer);

// DECOMP_ME_WIP func_801CF254 https://decomp.me/scratch/EpZEL
// minor regalloc
// has jumptable
#ifndef NON_MATCHING
INCLUDE_ASM("asm/us/st/np3/nonmatchings/4E69C", EntityGurkhaBodyParts);
#else
extern u16 D_80180B8C[];
extern u16 D_80180BA4[];
extern u16 D_80180BBC[];

void EntityGurkhaBodyParts(Entity* self) {
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
        self->drawFlags |= 4;
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
            self->velocityY += FIX(0.125);
            self->unk1E += self->ext.generic.unkA6;
            if (--self->ext.generic.unk80.modeS16.unk0 == 0) {
                self->step = 0;
                self->pfnUpdate = EntityExplosion;
                self->params = 0;
                self->drawFlags = 0;
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
        self->drawFlags |= 4;

    case 1:
        angle = *(u16*)&self->ext.stub[0x20];
        self->rotZ = angle;
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
            self->velocityY += FIX(0.125);
            func_801CDC80(&self->rotZ, 0x800, 0x20);
            break;
        }
    }
}

void func_801CF778(void) {
    ET_801CF254* et = &g_CurrentEntity[15].ext.et_801CF254;
    et->unk9C = et->next->ext.et_801CF254.unk9C + 0x300;
}

INCLUDE_ASM("asm/us/st/np3/nonmatchings/4E69C", func_801CF7A0);

// DECOMP_ME_WIP EntityGurkha https://decomp.me/scratch/51iIJ
INCLUDE_ASM("asm/us/st/np3/nonmatchings/4E69C", EntityGurkha);

void EntityGurkhaSword(Entity* self) {
    s16 angle;
    s32 rnd;

    switch (self->step) {
    case 0:
        InitializeEntity(D_80180BB0);
        self->hitboxWidth = 8;
        self->hitboxHeight = 8;
        self->drawFlags |= 4;
        break;

    case 1:
        angle = self->ext.gurkhaSword.unk9C;
        self->rotZ = angle;
        self->hitboxOffX = (u32)rsin(angle) >> 8;
        self->hitboxOffY = -(rcos(angle) * 16) >> 0xC;
        if (self->ext.gurkhaSword.unk8C) {
            self->step++;
        }
        break;

    case 2:
        if (self->facingLeft == 0) {
            self->velocityX = FIX(-8);
        } else {
            self->velocityX = FIX(8);
        }
        self->step++;

    case 3:
        MoveEntity();
        self->rotZ -= 0x100;
        self->ext.gurkhaSword.unk9C = self->rotZ;
        self->ext.gurkhaSword.unkA6 = -0xC0;
        angle = self->rotZ;
        self->hitboxOffX = (u32)rsin(self->rotZ) >> 8;
        self->hitboxOffY = -(rcos(angle) * 16) >> 0xC;

        if (self->facingLeft != 0) {
            self->velocityX -= FIX(0.25);
        } else {
            self->velocityX += FIX(0.25);
        }

        if ((g_Timer % 16) == 0) {
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
            self->velocityY += FIX(0.125);
            self->rotZ += self->ext.gurkhaSword.unkA6;
            if (--self->ext.gurkhaSword.unk80 == 0) {
                self->step = 0;
                self->pfnUpdate = EntityExplosion;
                self->params = 0;
                self->drawFlags = 0;
            }
        }
        break;
    }
}

void func_801D0A00(s16* arg0) {
    func_801CD91C(&g_CurrentEntity[arg0[1]]);
    func_801CD91C(&g_CurrentEntity[arg0[0]]);
    func_801CD91C(&g_CurrentEntity[18]);
    func_801CD83C(&g_CurrentEntity[arg0[2]]);
    func_801CD83C(&g_CurrentEntity[arg0[3]]);

    for (arg0 += 4; *arg0 != 0; arg0++) {
        if (*arg0 != 0xFF) {
            func_801CD83C(&g_CurrentEntity[*arg0]);
        }
    }
}

void func_801D0B40(void) {
    s16* unk88 = g_CurrentEntity[15].ext.et_801D0B40.unk88;
    g_CurrentEntity[15].ext.et_801D0B40.unk84 = unk88[0x4E] - 0x600;

    unk88 = g_CurrentEntity[16].ext.et_801D0B40.unk88;
    g_CurrentEntity[16].ext.et_801D0B40.unk84 = unk88[0x4E] - 0x600;
}

s32 func_801D0B78(void) {
    s32 ret;

    //! FAKE:
    do {
    } while (0);

    ret = 0;

    switch (g_CurrentEntity->step) {
    case 8:
        if (GetDistanceToPlayerX() < 64) {
            ret = 10;
        }
        if (GetDistanceToPlayerX() > 80) {
            ret = 6;
        }
        if (g_CurrentEntity->ext.et_801D0B78.unk88 != 0) {
            ret = 7;
        }
        break;

    case 10:
        if (GetDistanceToPlayerX() < 88) {
            ret = 8;
        }
        if (GetDistanceToPlayerX() < 56) {
            ret = 7;
        }
        if (GetDistanceToPlayerX() > 80) {
            ret = 6;
        }
        if (g_CurrentEntity->ext.et_801D0B78.unk88 != 0) {
            ret = 7;
        }
        break;

    case 12:
        if (GetDistanceToPlayerX() < 64) {
            ret = 10;
        }
        break;

    case 6:
        if (g_CurrentEntity->ext.et_801D0B78.unk88 != 0) {
            ret = 7;
        }
        if (GetDistanceToPlayerX() < 48) {
            ret = 10;
        }
        if (GetDistanceToPlayerX() < 80) {
            ret = 8;
        }
        break;

    default:
        if (GetDistanceToPlayerX() > 80) {
            ret = 6;
        }
        if (GetDistanceToPlayerX() < 64) {
            ret = 10;
        }
        if (g_CurrentEntity->ext.et_801D0B78.unk88 != 0) {
            ret = 7;
        }
        break;
    }

    if (g_CurrentEntity->facingLeft != ((GetSideToPlayer() & 1) ^ 1)) {
        ret = 12;
    }
    return ret;
}

INCLUDE_ASM("asm/us/st/np3/nonmatchings/4E69C", EntityBlade);

void EntityBladeSword(Entity* self) {
    Primitive *prim, *prim2;
    s32 x0, x1, y0, y1;
    s16 primIndex;
    s16 angle;
    s32 i;

    if (self->ext.et_801D1BB8.unk8C != 0) {
        self->step = 8;
    }

    switch (self->step) {
    case 0:
        InitializeEntity(D_80180BC8);
        self->hitboxWidth = 6;
        self->hitboxHeight = 6;
        self->drawFlags |= 4;
        primIndex = g_api.AllocPrimitives(PRIM_G4, 6);
        if (primIndex == -1) {
            self->ext.et_801D1BB8.prim = NULL;
            break;
        }
        prim = &g_PrimBuf[primIndex];
        self->primIndex = primIndex;
        self->ext.et_801D1BB8.prim = prim;
        self->flags |= FLAG_HAS_PRIMS;

        for (i = 0; prim != NULL; prim = prim->next) {
            prim->r0 = i;
            prim->g0 = i;
            prim->b0 = i;
            i += 10;
            prim->r2 = i;
            prim->g2 = i;
            prim->b2 = i;
            LOW(prim->r1) = LOW(prim->r0);
            LOW(prim->r3) = LOW(prim->r2);
            prim->x0 = self->posX.i.hi;
            prim->y0 = self->posY.i.hi;
            LOW(prim->x1) = LOW(prim->x0);
            LOW(prim->x2) = LOW(prim->x0);
            LOW(prim->x3) = LOW(prim->x0);
            prim->priority = self->zPriority;
            prim->blendMode = 0x33;
        }

    case 1:
        self->rotZ = self->ext.et_801D1BB8.unk9C;
        break;

    case 24:
        self->hitboxState = 0;
        self->flags |= FLAG_DESTROY_IF_BARELY_OUT_OF_CAMERA;
        break;

    case 8:
        if (self->facingLeft == 0) {
            self->velocityX = FIX(-8.0);
        } else {
            self->velocityX = FIX(8.0);
        }
        MoveEntity();
        self->flags |= FLAG_DESTROY_IF_OUT_OF_CAMERA;
    }

    angle = self->rotZ;
    self->hitboxOffX = -1 * (rsin(angle) * 13) >> 12;
    self->hitboxOffY = +1 * (rcos(angle) * 13) >> 12;

    prim = self->ext.et_801D1BB8.prim;
    if (prim != NULL) {
        for (i = 0; i < 5; i++) {
            prim2 = prim->next;
            LOW(prim->x0) = LOW(prim2->x0);
            LOW(prim->x1) = LOW(prim2->x1);
            LOW(prim->x2) = LOW(prim2->x2);
            LOW(prim->x3) = LOW(prim2->x3);
            if (self->ext.et_801D1BB8.unk8D) {
                prim->blendMode = 0x33;
            } else {
                prim->blendMode = 0xA;
            }
            prim = prim2;
        }
    }

    angle = self->rotZ;
    if (self->facingLeft != 0) {
        angle = -angle;
    }

    x0 = (-1 * (rsin(angle) * 20) >> 12) + self->posX.i.hi;
    y0 = (+1 * (rcos(angle) * 20) >> 12) + self->posY.i.hi;
    x1 = (+1 * (rsin(angle) * 4) >> 12) + self->posX.i.hi;
    y1 = (-1 * (rcos(angle) * 4) >> 12) + self->posY.i.hi;

    LOW(prim->x2) = LOW(prim->x0);
    LOW(prim->x3) = LOW(prim->x1);

    prim->x0 = x0;
    prim->y0 = y0;
    prim->y1 = y1;
    prim->x1 = x1;

    if (self->ext.et_801D1BB8.unk8D) {
        prim->blendMode = 0x33;
    } else {
        prim->blendMode = 0xA;
    }
}

#include "../unk_prim_helper.h"

INCLUDE_ASM("asm/us/st/np3/nonmatchings/4E69C", func_801D2320);

#include "../find_first_unk_prim.h"

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

#include "../unk_poly_func_0.h"

#include "../unk_loop_func.h"
