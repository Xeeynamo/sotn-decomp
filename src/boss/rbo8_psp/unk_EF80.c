// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../rbo8/rbo8.h"

void func_801CE3FC(s16* offsets) {
    Entity* entity;
    s32 i;

    for (i = 0; i < 4; i++) {
        entity = g_CurrentEntity + offsets[i];
        polarPlacePart(entity);
    }
    offsets += 4;

    while (*offsets) {
        if (*offsets != 0xFF) {
            entity = g_CurrentEntity + *offsets;
            polarPlacePart(entity);
        }
        offsets++;
    }
}

INCLUDE_ASM("boss/rbo8_psp/nonmatchings/rbo8_psp/unk_EF80", func_us_80195938);

static void func_801D0B40(void) {
    Entity* ent;
    Entity* parent;

    ent = g_CurrentEntity + 7;
    parent = ent->ext.GH_Props.parent;
    ent->ext.GH_Props.rotate = parent->ext.GH_Props.rotate + 0x100;

    ent = g_CurrentEntity + 11;
    parent = ent->ext.GH_Props.parent;
    ent->ext.GH_Props.rotate = parent->ext.GH_Props.rotate + 0x180;
}

extern s32 abs(s32 value);

#include "../rbo8/func_us_80195ad8.h"

extern EInit g_EInitGalamothLvl50;
extern s32 D_us_80180C0C;
extern s16 D_us_80180C10[];
extern s8 D_us_80180C88[];
extern giantBroBodyPartsInit D_us_80180CD0[];
extern s16 D_us_80180D70[];
extern s16 D_us_80180D90[];
extern s16 D_us_80180DB0[];
extern s16 D_us_80180DD0[];
extern s16 D_us_80180DE8[];
extern s16 D_us_80180E00[];
extern s16 D_us_80180E10[];
extern unkStr_801CDD80 D_us_80180EBC[];
extern unkStr_801CDD80 D_us_80180ECC[];
extern unkStr_801CDD80 D_us_80180F10[];
extern s16 D_us_80180F28[];
extern unkStr_801CDD80 D_us_80180F40[];
extern unkStr_801CDD80 D_us_80181014[];
extern unkStr_801CDD80 D_us_801810E8[];
extern unkStr_801CDD80 D_us_80181120[];
extern unkStr_801CDD80 D_us_801811A8[];
extern s16 D_us_801811D8[];
extern unkStr_801CDD80 D_us_80181208[];
extern unkStr_801CDD80 D_us_80181258[];
extern unkStr_801CDD80 D_us_801812B0[];
extern unkStr_801CDD80 D_us_801812C8[];
extern unkStr_801CDD80 D_us_80181318[];
extern unkStr_801CDD80 D_us_80181378[];
extern unkStr_801CDD80 D_us_801813B0[];
extern unkStr_801CDD80 D_us_801814A8[];
extern unkStr_801CDD80 D_us_801814C8[];
extern unkStr_801CDD80 D_us_80181518[];
extern unkStr_801CDD80 D_us_80181588[];
extern unkStr_801CDD80 D_us_801815DC[];
extern unkStr_801CDD80 D_us_801816D4[];
extern unkStr_801CDD80 D_us_801816EC[];
extern unkStr_801CDD80 D_us_80181714[];
extern unkStr_801CDD80 D_us_80181734[];
extern unkStr_801CDD80 D_us_80181744[];
extern s32 D_us_80181754;

void func_us_80195D80(Entity* self) {
    Entity* ent;
    s16* ptr;
    giantBroBodyPartsInit* parts;
    Primitive* prim;
    Entity* part;
    s16 angle;
    s8* hitbox;
    s32 var;
    s32 primIndex;
    s32 dx;
    s32 dy;
    Collider collider;

    FntPrint("step %x\n", self->step);
    FntPrint("step_s %x\n", self->step_s);
    if ((self->step & 1) && (self->hitFlags & 3)) {
        func_801CE1E8(24);
    }
    if ((self->flags & FLAG_DEAD) && (self->step < 32)) {
        for (ptr = D_us_80180D70; *ptr; ptr++) {
            ent = self + *ptr;
            ent->hitboxState = 0;
        }
        self->hitboxState = 0;
        D_us_80180C0C = 1;
        ent = self + 16;
        part = self + 13;
        if (ent->ext.galamoth.hitFloor || part->ext.galamoth.hitFloor) {
            func_801CE1E8(32);
        }
    }

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitGalamothLvl50);
        self->animCurFrame = 7;
        hitbox = D_us_80180C88;
        hitbox += self->animCurFrame * 4;
        self->hitboxOffX = hitbox[0];
        self->hitboxOffY = hitbox[1];
        self->hitboxWidth = hitbox[2];
        self->hitboxHeight = hitbox[3];
        primIndex = g_api.AllocPrimitives(PRIM_GT3, 1);
        if (primIndex == -1) {
            self->step = 0;
            return;
        }
        self->flags |= FLAG_HAS_PRIMS;
        self->primIndex = primIndex;
        prim = &g_PrimBuf[primIndex];
        self->ext.galamoth.prim = prim;
        prim->tpage = 0x12;
        prim->clut = 0x200;
        prim->u0 = 0xF9;
        prim->v0 = 2;
        prim->u1 = 0xD1;
        prim->v1 = 0x2B;
        prim->u2 = 0xF9;
        prim->v2 = 0x2B;
        prim->r0 = prim->g0 = prim->b0 = 0x10;
        prim->r1 = prim->g1 = prim->b1 = 0x40;
        prim->r2 = prim->g2 = prim->b2 = 0x40;
        prim->priority = self->zPriority;
        prim->drawMode = DRAW_UNK02;
        /* fallthrough */
    case 1:
        if (UnkCollisionFunc3(D_us_80180C10) & 1) {
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
            self->step++;
        }
        break;
    case 2:
        for (parts = D_us_80180CD0, part = self; parts->eArrayOffset; parts++) {
            ent = self + parts->eArrayOffset;
            CreateEntityFromCurrentEntity(E_ID(UNK_17), ent);
            ent->ext.galamoth.length = parts->length;
            ent->ext.galamoth.parent = self + parts->eArrayParentOffset;
            ent->params = parts->params;
            ent->zPriority = self->zPriority + parts->zOffset;
            ent->parent = self;
            ent->nextPart = part;
            part = ent;
        }
        self->nextPart = part;
        self->parent = NULL;
        self->step++;
        /* fallthrough */
    case 3:
        func_801CE228();
        self->ext.galamoth.unk84 = 0;
        func_801CE1E8(4);
        break;
    case 4:
        ptr = D_us_80180DB0;
        self->ext.galamoth.unk8B = 0;
        switch (self->step_s) {
        case 0:
            func_801CDF1C(ptr, D_us_80180EBC, 0);
            func_801CDE10(ptr);
            func_801D0A00(ptr);
            polarPlacePartsList(D_us_80180D70);
            self->step_s++;
            break;
        case 1:
            if (self->hitFlags || (D_us_80181754 & 1)) {
                self->step_s++;
            }
            break;
        case 2:
            D_us_80181754 |= 1;
            self->step_s++;
            break;
        case 3:
            func_801CDF1C(ptr, D_us_80180ECC, 0);
            func_801CDE10(ptr);
            func_801D0A00(ptr);
            polarPlacePartsList(D_us_80180D70);
            if (!self->ext.galamoth.unkB4[0] && !self->ext.galamoth.unkB0[0]) {
                func_us_80195AD8();
            }
            break;
        }
        break;
    case 5:
        self->ext.galamoth.unk8B = 0;
        if (self->ext.galamoth.unk84 == 1) {
            ptr = D_us_80180DD0;
        } else {
            ptr = D_us_80180DE8;
        }
        func_801CDF1C(ptr, D_us_80181378, 0);
        func_801CDE10(ptr);
        func_801D0A00(ptr);
        func_801D0B40();
        polarPlacePartsList(D_us_80180D70);
        if (self->ext.galamoth.unkB0[0] > 1) {
            collider.unk18 = 0x1D;
            ent = self + ptr[3];
            func_us_801955A0(ent, &collider);
            if (ent->ext.galamoth.hitFloor) {
                g_api.PlaySfx(SFX_STOMP_HARD_B);
                ent->posY.i.hi += collider.unk18;
                self->ext.galamoth.unk84 ^= 1;
                func_801CE228();
                var = func_us_801955F8(ent, self->facingLeft);
                if (var) {
                    func_801CE1E8(7);
                } else {
                    func_us_80195AD8();
                }
            }
        }
        break;
    case 18:
        self->ext.galamoth.unk8B = 0;
        if (self->ext.galamoth.unk84 == 1) {
            ptr = D_us_80180D90;
        } else {
            ptr = D_us_80180DB0;
        }
        func_801CDF1C(ptr, D_us_80181014, 0);
        func_801CDE10(ptr);
        func_801D0A00(ptr);
        polarPlacePartsList(D_us_80180D70);
        if (self->ext.galamoth.unkB0[0] == 3 && !self->ext.galamoth.unkB4[0]) {
            self->ext.galamoth.unk84 ^= 1;
        }
        if (self->ext.galamoth.unkB0[0] == 6 && !self->ext.galamoth.unkB4[0]) {
            g_api.ShakeCamera(1);
            g_api.PlaySfx(SFX_START_SLAM_B);
        }
        if (!self->ext.galamoth.unkB0[0] && !self->ext.galamoth.unkB4[0]) {
            func_us_80195AD8();
        }
        break;
    case 7:
        self->ext.galamoth.unk8B = 0;
        if (!self->step_s) {
            self->ext.galamoth.unkB0[0] = 1;
            self->step_s++;
        }
        if (self->ext.galamoth.unk84 == 1) {
            ptr = D_us_80180E00;
        } else {
            ptr = D_us_80180E10;
        }
        func_801CDF1C(ptr, D_us_801813B0, 0);
        func_801CDE10(ptr);
        func_801D0A00(ptr);
        func_801D0B40();
        polarPlacePartsList(D_us_80180D70);
        if (self->ext.galamoth.unkB0[0] > 1) {
            collider.unk18 = 0x1D;
            ent = self + ptr[3];
            func_us_801955A0(ent, &collider);
            if (ent->ext.galamoth.hitFloor) {
                g_api.PlaySfx(SFX_STOMP_HARD_B);
                ent->posY.i.hi += collider.unk18;
                self->ext.galamoth.unk84 ^= 1;
                func_801CE228();
                var = func_us_801955F8(ent, self->facingLeft ^ 1);
                if (var) {
                    func_801CE1E8(5);
                } else {
                    func_us_80195AD8();
                }
            }
        }
        break;
    case 10:
        if (self->ext.galamoth.unk84 == 1) {
            ptr = D_us_80180DD0;
        } else {
            ptr = D_us_80180DE8;
        }
        switch (self->step_s) {
        case 0:
            self->step_s++;
            break;
        case 1:
            func_801CDF1C(ptr, D_us_801814A8, 0);
            func_801CDE10(ptr);
            func_801D0A00(ptr);
            if (!self->ext.galamoth.unkB4[0] && !self->ext.galamoth.unkB0[0]) {
                self->step_s++;
            }
            break;
        case 2:
            if (self->facingLeft) {
                self->velocityX = FIX(3);
            } else {
                self->velocityX = FIX(-3);
            }
            self->velocityY = FIX(-7);
            func_801CE228();
            self->step_s++;
            /* fallthrough */
        case 3:
            MoveEntity();
            self->velocityY += FIX(0.25);
            func_801CDF1C(ptr, D_us_801814C8, 0);
            func_801CDE10(ptr);
            func_801CE3FC(ptr);
            ent = self + ptr[3];
            collider.unk18 = 0x1D;
            func_us_801955A0(ent, &collider);
            if (ent->ext.galamoth.hitFloor) {
                ent->posY.i.hi += collider.unk18;
                self->ext.galamoth.unk84 ^= 1;
                func_801CE228();
                self->step_s = 1;
                var = func_us_801955F8(ent, self->facingLeft);
                if (var) {
                    func_801CE1E8(7);
                } else {
                    func_801CE1E8(7);
                }
            }
            break;
        }
        func_801D0B40();
        polarPlacePartsList(D_us_80180D70);
        break;
    case 26:
        self->ext.galamoth.unk8B = 1;
        if (self->ext.galamoth.unk84 == 1) {
            ptr = D_us_80180D90;
        } else {
            ptr = D_us_80180DB0;
        }
        func_801CDF1C(ptr, D_us_80181588, 0);
        func_801CDE10(ptr);
        func_801D0A00(ptr);
        func_801D0B40();
        polarPlacePartsList(D_us_80180D70);
        ent = self + ptr[5];
        ent->ext.galamoth.unk88 = 1;
        if (!self->ext.galamoth.unkB0[0] && !self->ext.galamoth.unkB4[0]) {
            self->ext.galamoth.unk8B = 0;
            ent = self + ptr[5];
            ent->ext.galamoth.unk88 = 0;
            func_us_80195AD8();
        }
        if (self->ext.galamoth.unkB0[0] == 3 && !self->ext.galamoth.unkB4[0]) {
            g_api.PlaySfx(SFX_MEDUSA_WEAPON_SWING);
        }
        break;
    case 9:
        switch (self->step_s) {
        case 0:
            if (self->ext.galamoth.unk84 == 1) {
                ptr = D_us_80180D90;
            } else {
                ptr = D_us_80180DB0;
            }
            func_801CDF1C(ptr, D_us_80180F10, 0);
            func_801CDE10(ptr);
            func_801D0A00(ptr);
            if (!self->ext.galamoth.unkB0[0] && !self->ext.galamoth.unkB4[0]) {
                self->ext.galamoth.unk8A = 4;
                self->step_s++;
            }
            break;
        case 1:
            ent = self + 3;
            part = &PLAYER;
            dx = part->posX.i.hi - ent->posX.i.hi;
            dy = part->posY.i.hi - ent->posY.i.hi;
            angle = ratan2(-dx, dy);
            if (self->facingLeft) {
                angle = -angle;
            }
            if (angle > ROT(157.5)) {
                angle = ROT(157.5);
            }
            if (angle < ROT(45)) {
                angle = ROT(45);
            }
            ent = self + 8;
            func_801CDD00(ent, angle, 12);
            ent = self + 10;
            func_801CDD00(ent, angle, 12);
            ent = self + 11;
            func_801CDD00(ent, angle, 12);
            ent = self + 2;
            angle -= ROT(90);
            func_801CDD00(ent, angle, 12);
            angle /= 2;
            ent = self + 3;
            func_801CDD00(ent, angle, 12);
            self->ext.galamoth.timer = 12;
            self->step_s++;
            /* fallthrough */
        case 2:
            ptr = D_us_80180F28;
            polarPlacePartsWithAngvel(ptr);
            if (!--self->ext.galamoth.timer) {
                self->step_s++;
            }
            break;
        case 3:
            ptr = D_us_80180F28;
            func_801CDF1C(ptr, D_us_80180F40, 0);
            func_801CDE10(ptr);
            if (!self->ext.galamoth.unkB0[0] && !self->ext.galamoth.unkB4[0]) {
                if (!--self->ext.galamoth.unk8A) {
                    func_us_80195AD8();
                } else {
                    self->step_s = 1;
                }
            }
            break;
        }
        polarPlacePartsList(D_us_80180D70);
        break;
    case 11:
        self->ext.galamoth.unk8B = 0;
        if (self->ext.galamoth.unk84 == 1) {
            ptr = D_us_80180DD0;
        } else {
            ptr = D_us_80180DE8;
        }
        func_801CDF1C(ptr, D_us_80181518, 0);
        func_801CDE10(ptr);
        func_801D0A00(ptr);
        func_801D0B40();
        polarPlacePartsList(D_us_80180D70);
        if (!self->ext.galamoth.unkB4[0]) {
            self->facingLeft ^= 1;
            func_us_80195AD8();
        }
        break;
    case 12:
        if (self->ext.galamoth.unk84 == 1) {
            ptr = D_us_80180D90;
        } else {
            ptr = D_us_80180DB0;
        }
        switch (self->step_s) {
        case 0:
            self->ext.galamoth.unk8B = 0;
            func_801CDF1C(ptr, D_us_801810E8, 0);
            func_801CDE10(ptr);
            func_801D0A00(ptr);
            self->ext.galamoth.timer = 0x20;
            if (!self->ext.galamoth.unkB4[0] && !self->ext.galamoth.unkB0[0]) {
                self->step_s++;
            }
            /* fallthrough */
        case 1:
            if (!(g_Timer % 5)) {
                ent = AllocEntity(&g_Entities[224], &g_Entities[256]);
                if (ent != NULL) {
                    CreateEntityFromCurrentEntity(E_ID(UNK_18), ent);
                    ent->ext.et_801980E4.source = self + 7;
                }
            }
            if (!--self->ext.galamoth.timer) {
                self->ext.galamoth.timer = 0x100;
                self->ext.galamoth.unk8B = 1;
                self->step_s++;
            }
            break;
        case 2:
            if (!(self->ext.galamoth.timer & 0x1F)) {
                g_api.PlaySfx(SFX_EXPLODE_B);
                ent = AllocEntity(&g_Entities[160], &g_Entities[192]);
                if (ent != NULL) {
                    part = self + 7;
                    CreateEntityFromEntity(E_ID(UNK_19), part, ent);
                }
            }
            if (!--self->ext.galamoth.timer) {
                self->ext.galamoth.unk8B = 0;
                self->step_s++;
            }
            break;
        case 3:
            func_801CDF1C(ptr, D_us_80181120, 0);
            func_801CDE10(ptr);
            func_801D0A00(ptr);
            if (!self->ext.galamoth.unkB4[0] && !self->ext.galamoth.unkB0[0]) {
                func_us_80195AD8();
            }
            break;
        }
        polarPlacePartsList(D_us_80180D70);
        break;
    case 14:
        if (self->ext.galamoth.unk84 == 1) {
            ptr = D_us_80180D90;
        } else {
            ptr = D_us_80180DB0;
        }
        switch (self->step_s) {
        case 0:
            self->ext.galamoth.unk8B = 0;
            func_801CDF1C(ptr, D_us_801811A8, 0);
            func_801CDE10(ptr);
            func_801D0A00(ptr);
            self->ext.galamoth.timer = 0x20;
            if (!self->ext.galamoth.unkB4[0] && !self->ext.galamoth.unkB0[0]) {
                self->step_s++;
            }
            if (!self->ext.galamoth.unkB4[0] &&
                self->ext.galamoth.unkB0[0] == 3) {
                g_api.PlaySfx(SFX_BOSS_WING_FLAP);
            }
            /* fallthrough */
        case 1:
            if (!(g_Timer % 5)) {
                ent = AllocEntity(&g_Entities[224], &g_Entities[256]);
                if (ent != NULL) {
                    CreateEntityFromCurrentEntity(E_ID(UNK_18), ent);
                    ent->ext.et_801980E4.source = self + 7;
                }
            }
            if (!--self->ext.galamoth.timer) {
                g_api.PlaySfx(SFX_GALAMOTH_ELECTRICITY);
                self->ext.galamoth.unk8B = 1;
                self->ext.galamoth.timer = 0x100;
                self->step_s++;
            }
            break;
        case 2:
            ptr = D_us_801811D8;
            func_801CDF1C(ptr, D_us_80181208, 0);
            polarPlacePartsWithAngvel(ptr);
            if (!(self->ext.galamoth.timer & 0xF)) {
                ent = AllocEntity(&g_Entities[160], &g_Entities[192]);
                if (ent != NULL) {
                    part = self + 7;
                    CreateEntityFromEntity(E_ID(UNK_1A), part, ent);
                    ent->facingLeft = self->facingLeft;
                }
            }
            if (!(self->ext.galamoth.timer & 0x1F)) {
                g_api.PlaySfx(SFX_GALAMOTH_ELECTRICITY);
            }
            if (!--self->ext.galamoth.timer) {
                func_801CE228();
                self->ext.galamoth.timer = 0x80;
                self->step_s++;
            }
            break;
        case 3:
            ptr = D_us_801811D8;
            func_801CDF1C(ptr, D_us_80181208, 0);
            polarPlacePartsWithAngvel(ptr);
            if (!(self->ext.galamoth.timer & 0x1F)) {
                g_api.PlaySfx(SFX_GALAMOTH_ELECTRICITY);
            }
            if (!--self->ext.galamoth.timer) {
                func_801CE228();
                self->ext.galamoth.unk8B = 0;
                self->step_s++;
            }
            break;
        case 4:
            func_801CDF1C(ptr, D_us_80181258, 0);
            func_801CDE10(ptr);
            func_801D0A00(ptr);
            if (!self->ext.galamoth.unkB4[0] && !self->ext.galamoth.unkB0[0]) {
                func_us_80195AD8();
            }
            break;
        }
        polarPlacePartsList(D_us_80180D70);
        break;
    case 24:
        if (self->ext.galamoth.unk84 == 1) {
            ptr = D_us_80180D90;
        } else {
            ptr = D_us_80180DB0;
        }
        func_801CDF1C(ptr, D_us_801815DC, 0);
        func_801CDE10(ptr);
        func_801D0A00(ptr);
        polarPlacePartsList(D_us_80180D70);
        self->ext.galamoth.unk8B = 1;
        if (!self->ext.galamoth.unkB0[0] && !self->ext.galamoth.unkB4[0]) {
            self->ext.galamoth.unk8B = 0;
            func_us_80195AD8();
        }
        break;
    case 22:
        if (self->ext.galamoth.unk84 == 1) {
            ptr = D_us_80180D90;
        } else {
            ptr = D_us_80180DB0;
        }
        switch (self->step_s) {
        case 0:
            self->ext.galamoth.unk8B = 0;
            func_801CDF1C(ptr, D_us_801812B0, 0);
            func_801CDE10(ptr);
            func_801D0A00(ptr);
            if (!(g_Timer % 5)) {
                ent = AllocEntity(&g_Entities[224], &g_Entities[256]);
                if (ent != NULL) {
                    CreateEntityFromCurrentEntity(E_ID(UNK_18), ent);
                    ent->ext.et_801980E4.source = self + 7;
                }
            }
            if (!self->ext.galamoth.unkB4[0] && !self->ext.galamoth.unkB0[0]) {
                self->step_s++;
            }
            break;
        case 1:
            ent = self + 20;
            DestroyEntity(ent);
            CreateEntityFromCurrentEntity(E_ID(UNK_1C), ent);
            ent->facingLeft = self->facingLeft;
            ent->ext.galamoth.parent = self + 7;
            ent->params = 0;
            ent = self + 21;
            DestroyEntity(ent);
            CreateEntityFromCurrentEntity(E_ID(UNK_1C), ent);
            ent->facingLeft = self->facingLeft;
            ent->ext.galamoth.parent = self + 11;
            ent->params = 1;
            g_api.PlaySfx(SFX_GALAMOTH_ELECTRICITY);
            self->step_s++;
            /* fallthrough */
        case 2:
            if (!(g_Timer % 5)) {
                g_api.PlaySfx(SFX_GALAMOTH_ELECTRICITY);
                ent = AllocEntity(&g_Entities[224], &g_Entities[256]);
                if (ent != NULL) {
                    CreateEntityFromCurrentEntity(E_ID(UNK_18), ent);
                    ent->ext.et_801980E4.source = self + 7;
                }
            }
            func_801CDF1C(ptr, D_us_801812C8, 0);
            func_801CDE10(ptr);
            self->ext.galamoth.timer++;
            ent = self + 1;
            if (self->ext.galamoth.timer & 1) {
                ent->ext.galamoth.rotate += ROT(2.109375);
            } else {
                ent->ext.galamoth.rotate -= ROT(2.109375);
            }
            func_801D0A00(ptr);
            if (!self->ext.galamoth.unkB4[0] && !self->ext.galamoth.unkB0[0]) {
                ent = self + 1;
                ent->ext.galamoth.rotate = 0;
                self->ext.galamoth.unk8B = 1;
                self->step_s++;
            }
            break;
        case 3:
            func_801CDF1C(ptr, D_us_80181318, 0);
            func_801CDE10(ptr);
            func_801D0A00(ptr);
            if (self->ext.galamoth.unkB4[0] &&
                self->ext.galamoth.unkB0[0] == 1) {
                ent = self + 21;
                ent->ext.galamoth.unk88 = 1;
                ent = self + 20;
                ent->ext.galamoth.unk88 = 1;
            }
            if (!(g_Timer & 0x1F)) {
                g_api.PlaySfx(SFX_THUNDER_B);
            }
            if (!self->ext.galamoth.unkB4[0] && !self->ext.galamoth.unkB0[0]) {
                g_api.PlaySfx(SFX_EXPLODE_FAST_B);
                self->step_s++;
            }
            break;
        case 4:
            self->ext.galamoth.unk8B = 0;
            func_us_80195AD8();
            break;
        }
        polarPlacePartsList(D_us_80180D70);
        break;
    case 32:
        self->ext.galamoth.unk8B = 1;
        if (self->ext.galamoth.unk84 == 1) {
            ptr = D_us_80180D90;
        } else {
            ptr = D_us_80180DB0;
        }
        self->ext.galamoth.timer++;
        ent = self + 1;
        if (self->ext.galamoth.timer & 1) {
            ent->ext.galamoth.rotate += ROT(2.109375);
        } else {
            ent->ext.galamoth.rotate -= ROT(2.109375);
        }
        if (!(g_Timer & 0x1F)) {
            g_api.PlaySfx(SFX_EXPLODE_B);
        }
        switch (self->step_s) {
        case 0:
            ent = self + 2;
            ent->step_s = 0;
            ent->step = 32;
            ent->ext.galamoth.unk8D = 1;
            D_us_80181754 |= 2;
            self->step_s = 2;
            break;
        case 1:
            func_801CDF1C(ptr, D_us_801816D4, 0);
            func_801CDE10(ptr);
            func_801D0A00(ptr);
            polarPlacePartsList(D_us_80180D70);
            if (!self->ext.galamoth.unkB4[0] && !self->ext.galamoth.unkB0[0]) {
                self->ext.galamoth.unk84 = 1;
                self->step_s++;
            }
            break;
        case 2:
            func_801CDF1C(ptr, D_us_801816EC, 0);
            func_801CDE10(ptr);
            func_801D0A00(ptr);
            polarPlacePartsList(D_us_80180D70);
            if (!self->ext.galamoth.unkB4[0] && !self->ext.galamoth.unkB0[0]) {
                g_api.PlaySfx(SFX_BOSS_LARGE_FLAMES);
                g_api.PlaySfx(SFX_BO1_UNK_7C7);
                ent = self + 2;
                ent->ext.galamoth.unk8C = 1;
                ent = self + 4;
                ent->step = 32;
                ent->ext.galamoth.unk8D = 1;
                ent = self + 6;
                ent->step = 32;
                ent = self + 7;
                ent->step = 32;
                self->step_s++;
            }
            break;
        case 3:
            func_801CDF1C(ptr, D_us_80181714, 0);
            func_801CDE10(ptr);
            func_801D0A00(ptr);
            polarPlacePartsList(D_us_80180D70);
            if (!self->ext.galamoth.unkB4[0] && !self->ext.galamoth.unkB0[0]) {
                g_api.PlaySfx(SFX_BOSS_LARGE_FLAMES);
                g_api.PlaySfx(SFX_BO1_UNK_7C7);
                ent = self + 4;
                ent->ext.galamoth.unk8C = 1;
                ent = self + 6;
                ent->ext.galamoth.unk8C = 1;
                ent = self + 7;
                ent->ext.galamoth.unk8C = 1;
                ent = self + ptr[2];
                ent->step = 32;
                ent->ext.galamoth.unk8D = 1;
                ent->ext.galamoth.unk8E = 1;
                ent = self + ptr[3];
                ent->step = 32;
                ent = self + ptr[5];
                ent->step = 32;
                self->step_s++;
            }
            break;
        case 4:
            func_801CDF1C(ptr, D_us_80181734, 0);
            func_801CDE10(ptr);
            func_801D0A00(ptr);
            polarPlacePartsList(D_us_80180D70);
            if (!self->ext.galamoth.unkB4[0] && !self->ext.galamoth.unkB0[0]) {
                g_api.PlaySfx(SFX_BOSS_LARGE_FLAMES);
                g_api.PlaySfx(SFX_BO1_UNK_7C7);
                ent = self + ptr[2];
                ent->ext.galamoth.unk8C = 1;
                ent = self + ptr[3];
                ent->ext.galamoth.unk8C = 1;
                ent = self + ptr[5];
                ent->ext.galamoth.unk8C = 1;
                ent = self + 8;
                ent->step = 32;
                ent->ext.galamoth.unk8D = 1;
                ent->ext.galamoth.unk8E = 1;
                ent = self + 10;
                ent->step = 32;
                ent = self + 11;
                ent->step = 32;
                prim = self->ext.galamoth.prim;
                prim->drawMode = DRAW_HIDE;
                self->step_s++;
            }
            break;
        case 5:
            func_801CDF1C(ptr, D_us_80181744, 0);
            func_801CDE10(ptr);
            func_801D0A00(ptr);
            polarPlacePartsList(D_us_80180D70);
            if (!self->ext.galamoth.unkB4[0] && !self->ext.galamoth.unkB0[0]) {
                g_api.PlaySfx(SFX_BOSS_LARGE_FLAMES);
                ent = self + 8;
                ent->ext.galamoth.unk8C = 1;
                ent = self + 10;
                ent->ext.galamoth.unk8C = 1;
                ent = self + 11;
                ent->ext.galamoth.unk8C = 1;
                self->step_s++;
            }
            break;
        case 6:
            for (ptr = D_us_80180D70; *ptr; ptr++) {
                ent = self + *ptr;
                ent->drawFlags |= ENTITY_OPACITY;
            }
            self->drawFlags |= ENTITY_OPACITY;
            self->opacity = 0x80;
            ent = self + 3;
            ent->step = 32;
            ent = self + 1;
            ent->step = 32;
            ent->ext.galamoth.unk8D = 1;
            ent->ext.galamoth.unk8E = 1;
            ent = self + 12;
            ent->step = 32;
            self->step_s++;
            /* fallthrough */
        case 7:
            self->opacity -= 2;
            for (ptr = D_us_80180D70; *ptr; ptr++) {
                ent = self + *ptr;
                ent->opacity = self->opacity;
            }
            if (!self->opacity) {
                self->step_s++;
            }
            break;
        case 8:
            self->palette = PAL_FLAG(0x20A);
            self->step_s++;
            /* fallthrough */
        case 9:
            if (!(self->ext.galamoth.timer & 7)) {
                self->palette++;
            }
            self->posY.i.hi++;
            for (ptr = D_us_80180D70; *ptr; ptr++) {
                ent = self + *ptr;
                ent->palette = self->palette;
                ent->posY.val += FIX(0.25);
            }
            if (self->palette >= PAL_FLAG(0x217)) {
                self->step_s++;
            }
            break;
        case 10:
            for (ptr = D_us_80180D70; *ptr; ptr++) {
                ent = self + *ptr;
                DestroyEntity(ent);
            }
            g_api.PlaySfx(SFX_EXPLODE_A);
            D_us_80181754 |= 4;
            DestroyEntity(self);
            return;
        case 11:
            return;
        }
        break;
    }
    func_us_80195938();
    for (ptr = D_us_80180D70; *ptr; ptr++) {
        ent = self + *ptr;
        ent->facingLeft = self->facingLeft;
        ent->ext.galamoth.unkA8 = 0;
    }
    D_8006C384.y = self->ext.galamoth.unkB0[0];
    D_8006C38C.y = self->ext.galamoth.unkB4[0];
}

INCLUDE_ASM("boss/rbo8_psp/nonmatchings/rbo8_psp/unk_EF80", func_us_80197B1C);

void func_us_801980E4(Entity* self) {
    Entity* source;

    if (D_us_80180C0C != 0) {
        DestroyEntity(self);
        return;
    }

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitGalamothLvl50);
        self->hitboxState = 0;
        self->animCurFrame = 0x10;
        self->blendMode = BLEND_ADD | BLEND_TRANSP;
        self->drawFlags = ENTITY_SCALEY | ENTITY_SCALEX;
        self->scaleX = self->scaleY = 0x100;
        self->drawFlags |= ENTITY_OPACITY;
        self->opacity = 0xC0;
        self->drawFlags |= ENTITY_ROTATE;
        /* fall through */
    case 1:
        if (g_Timer & 1) {
            self->palette = PAL_FLAG(0x206);
        } else {
            self->palette = PAL_FLAG(0x207);
        }
        source = self->ext.et_801980E4.source;
        self->facingLeft = source->facingLeft;
        self->rotate = source->rotate;
        self->posX.i.hi = source->posX.i.hi;
        self->posY.i.hi = source->posY.i.hi;
        self->scaleX = self->scaleY += 0x20;
        self->opacity -= 8;
        if (!self->opacity) {
            DestroyEntity(self);
        }
        break;
    }
}

extern EInit D_us_80180A8C;
extern u8 D_us_80180C20[];

void func_us_80198210(Entity* self) {
    Entity* entities;
    s16 angle;

    if ((self->flags & FLAG_DEAD) || D_us_80180C0C != 0) {
        self->velocityX = 0;
        self->velocityY = 0;
    }

    switch (self->step) {
    case 0:
        InitializeEntity(D_us_80180A8C);
        self->blendMode = BLEND_ADD | BLEND_TRANSP;
        entities = g_Entities;
        angle = GetAngleBetweenEntities(self, entities);
        self->velocityX = rcos(angle) * 0x140;
        self->velocityY = rsin(angle) * 0x140;
        /* fall through */

    case 1:
        AnimateEntity(D_us_80180C20, self);
        MoveEntity();
        self->velocityX -= self->velocityX / 0x10;
        self->velocityY -= self->velocityY / 0x10;
        if (abs(self->velocityX) < FIX(0.25) &&
            abs(self->velocityY) < FIX(0.25)) {
            self->drawFlags = ENTITY_SCALEY | ENTITY_SCALEX;
            self->scaleX = self->scaleY = 0x100;
            self->hitboxState = 0;
            self->step++;
        }
        break;

    case 2:
        AnimateEntity(D_us_80180C20, self);
        self->scaleX = self->scaleY -= 0x10;
        if (!self->scaleX) {
            DestroyEntity(self);
        }
        break;
    }
}

INCLUDE_ASM("boss/rbo8_psp/nonmatchings/rbo8_psp/unk_EF80", func_us_801983EC);

INCLUDE_ASM("boss/rbo8_psp/nonmatchings/rbo8_psp/unk_EF80", func_us_80198964);

INCLUDE_ASM("boss/rbo8_psp/nonmatchings/rbo8_psp/unk_EF80", func_us_8019C7B8_from_rcen);

extern EInit D_us_80180A98;

void func_us_801991D4(Entity* self) {
    if (!self->step) {
        InitializeEntity(D_us_80180A98);
        return;
    }
    DestroyEntity(self);
}

void func_us_8019921C(Entity* self) {
    s32 args[9];

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitGalamothLvl50);
        self->animCurFrame = self->params;
        self->drawFlags = ENTITY_ROTATE;
        /* fall through */
    case 1:
        MoveEntity();
        self->rotate -= ROT(2.8125);
        self->velocityY += FIX(0.125);
        if (self->facingLeft) {
            self->velocityX = FIX(0.5);
        } else {
            self->velocityX = FIX(-0.5);
        }
        args[6] = 0x20;
        func_us_801955A0(self, args);
        if (self->ext.et_8019921C.hitFloor) {
            self->flags |= FLAG_DESTROY_IF_OUT_OF_CAMERA;
            self->zPriority = 0x5F;
        }
        break;
    }
}

extern EInit D_us_80180AA4;
extern AnimationFrame D_us_80180C4C[];

void EntityMinotaurSpitLiquid(Entity* self) {
    s16 angle;

    switch (self->step) {
    case 0:
        InitializeEntity(D_us_80180AA4);
        if (self->facingLeft) {
            self->rotate = -self->rotate;
        }
        self->facingLeft = 0;
        self->rotate += ROT(22.5) - Random() * 2;

        angle = self->rotate;
        self->velocityX = rsin(angle) * 0x28;
        self->velocityY = rcos(angle) * -0x28;
        self->blendMode = BLEND_ADD | BLEND_TRANSP;
        self->drawFlags =
            ENTITY_OPACITY | ENTITY_ROTATE | ENTITY_SCALEY | ENTITY_SCALEX;
        self->scaleX = 0x20;
        self->scaleY = 0x100;
        self->opacity = 0x80;
        /* fall through */

    case 1:
        MoveEntity();
        self->scaleX += 0xC;
        self->scaleY += 2;
        self->opacity -= 1;
        if (!AnimateEntity(D_us_80180C4C, self)) {
            DestroyEntity(self);
        }
        break;
    }
}

extern EInit D_us_80180AB0;
extern u8 D_us_80180C68[];

void func_us_8019943C(Entity* self) {
    s16 angle;

    switch (self->step) {
    case 0:
        InitializeEntity(D_us_80180AB0);
        if (self->facingLeft) {
            self->rotate = -self->rotate;
        }
        self->facingLeft = 0;
        self->rotate += ROT(22.5) - Random() * 2;

        angle = self->rotate;
        self->velocityX = rsin(angle) * 0x20;
        self->velocityY = rcos(angle) * -0x20;
        self->blendMode = BLEND_ADD | BLEND_TRANSP;
        /* fall through */
    case 1:
        MoveEntity();
        self->posY.i.hi--;
        if (AnimateEntity(D_us_80180C68, self) == 0) {
            DestroyEntity(self);
        }
        break;
    }
}

#include "../../st/e_room_bg.h"
