// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "no0.h"

void func_801CD78C(Point32* src, s32 speed, s16 angle, Point32* dst) {
    if (g_CurrentEntity->facingLeft) {
        angle = -angle;
    }
    *dst = *src;

    dst->x -= speed * rsin(angle) * 16;
    dst->y += speed * rcos(angle) * 16;
}

void func_us_801D2424(Point32* arg0, s16 arg1, s16 arg2, Point32* arg3,
                      s16 arg4, s16 arg5, Primitive* prim) {
    prim->x0 = prim->x1 = F(arg0->x).i.hi;
    prim->y0 = prim->y1 = F(arg0->y).i.hi;
    prim->x2 = prim->x3 = F(arg3->x).i.hi;
    prim->y2 = prim->y3 = F(arg3->y).i.hi;
    if (g_CurrentEntity->facingLeft) {
        prim->x0 += (arg2 * rcos(arg1)) >> 0xC;
        prim->x1 -= (arg2 * rcos(arg1)) >> 0xC;
        prim->x2 += (arg5 * rcos(arg4)) >> 0xC;
        prim->x3 -= (arg5 * rcos(arg4)) >> 0xC;
    } else {
        prim->x0 -= (arg2 * rcos(arg1)) >> 0xC;
        prim->x1 += (arg2 * rcos(arg1)) >> 0xC;
        prim->x2 -= (arg5 * rcos(arg4)) >> 0xC;
        prim->x3 += (arg5 * rcos(arg4)) >> 0xC;
    }
    prim->y0 -= (arg2 * rsin(arg1)) >> 0xC;
    prim->y1 += (arg2 * rsin(arg1)) >> 0xC;
    prim->y2 -= (arg5 * rsin(arg4)) >> 0xC;
    prim->y3 += (arg5 * rsin(arg4)) >> 0xC;
}

INCLUDE_ASM("st/no0/nonmatchings/e_plate_lord", func_us_801D26CC);

INCLUDE_ASM("st/no0/nonmatchings/e_plate_lord", func_us_801D274C);

INCLUDE_ASM("st/no0/nonmatchings/e_plate_lord", func_us_801D27C4);

bool func_us_801D29F8(s16* arg0, s32 arg1, s32 arg2) {
    if (abs(*arg0 - arg1) < arg2) {
        *arg0 = arg1;
        return true;
    }

    if (arg1 < *arg0) {
        *arg0 -= arg2;
    }

    if (*arg0 < arg1) {
        *arg0 += arg2;
    }

    return false;
}

extern Entity D_8007D858[];
extern u16 D_us_80180B84[];
extern Point32 D_us_80181F80[];
extern Point16 D_us_80181F90[];

void func_us_801D2A64(Entity* self) {
    Point32 point32;
    Collider collider;
    Primitive* prim;
    s32 posX;
    s32 posY;
    s32 primIndex;
    s32 counter;
    s32 i;

    unk_PlatelordStruct* unkStructA;
    unk_PlatelordStruct* unkStructB;
    unk_PlatelordStruct* unkStructC;
    Point16* tempPoint16A;
    Point16* tempPoint16B;
    Point32* tempPoint32A;
    Point32* tempPoint32B;
    Entity* tempEntity;
    s16 tempS16;

    if (self->ext.plateLord.unkB0 != 0) {
        self->ext.plateLord.unkB0--;
    } else if (
        ((self->step == 5) || (self->step == 6)) && (self->hitFlags & 3)) {
        PlaySfxPositional(0x75F);
        self->step_s = 0;
        self->step = 7;
    }
    if ((self->flags & FLAG_DEAD) && (self->step < 0x10)) {
        if ((self->step == 5) || (self->step == 6)) {
            self->ext.plateLord.unk87 = 0;
        } else {
            self->ext.plateLord.unk87 = 1;
        }
        self->step_s = 0;
        self->step = 0x10;
        PlaySfxPositional(0x760);
    }
    switch (self->step) {
    case 0:
        InitializeEntity(D_us_80180B84);
        self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
        self->animCurFrame = 3;
        self->zPriority = 0xB0;
        self->hitboxWidth = 0xC;
        self->hitboxHeight = 0x14;
        self->hitboxOffY = 0x14;
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 4);
        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags |= FLAG_HAS_PRIMS;
        self->primIndex = primIndex;
        prim = &g_PrimBuf[primIndex];
        self->ext.prim = prim;

        prim->clut = 0x22C;
        prim->priority = 0xAF;
        prim->u0 = 0x7A;
        prim->v0 = 0x19;
        prim->u1 = 0x82;
        prim->v1 = 0x22;
        prim->u2 = 0x6D;
        prim->v2 = 0x25;
        prim->u3 = 0x77;
        prim->v3 = 0x2E;
        prim = prim->next;

        prim->clut = 0x22D;
        prim->priority = 0xAF;
        prim->u0 = prim->u2 = 0x24;
        prim->u1 = prim->u3 = 0x34;
        prim->v0 = prim->v1 = 0x39;
        prim->v2 = prim->v3 = 0x57;
        prim = prim->next;

        prim->clut = 0x22C;
        prim->priority = 0xB1;
        prim->u0 = 0x6B;
        prim->u1 = 0x7A;
        prim->u2 = 0x73;
        prim->u3 = 0x82;
        prim->v0 = prim->v1 = 2;
        prim->v2 = prim->v3 = 0xF;
        prim = prim->next;

        prim->clut = 0x22B;
        prim->priority = 0xB2;
        prim->u0 = 0x36;
        prim->u1 = 0x47;
        prim->u2 = 0x3F;
        prim->u3 = 0x4F;
        prim->v0 = prim->v1 = 0x3B;
        prim->v2 = prim->v3 = 0x59;
        prim = prim->next;

        prim = self->ext.prim;
        while (prim != NULL) {
            prim->tpage = 0x13;
            prim->drawMode = DRAW_UNK02;
            prim = prim->next;
        }
        tempEntity = self + 1;
        self->ext.plateLord.unk88.unk0 = tempEntity;
        self->ext.plateLord.unk88.unk10 = &D_us_80181F80[0];
        CreateEntityFromEntity(E_ID_32, self, tempEntity);
        tempEntity->params = 0;
        tempEntity = self + 2;
        self->ext.plateLord.unk9C.unk0 = tempEntity;
        self->ext.plateLord.unk9C.unk10 = &D_us_80181F80[1];
        CreateEntityFromEntity(E_ID_32, self, tempEntity);
        tempEntity->params = 1;
        tempEntity = self + 3;
        CreateEntityFromEntity(E_ID_33, self, tempEntity);
        tempEntity = self + 4;
        CreateEntityFromEntity(E_ID_34, self, tempEntity);
        tempEntity->params = 0;
        tempEntity = self + 5;
        CreateEntityFromEntity(E_ID_35, self, tempEntity);
        tempEntity = self + 6;
        CreateEntityFromEntity(E_ID_34, self, tempEntity);
        tempEntity->params = 1;
        tempEntity = self + 7;
        CreateEntityFromEntity(E_ID_34, self, tempEntity);
        tempEntity->params = 2;
        tempEntity = self + 8;
        CreateEntityFromEntity(E_ID_34, self, tempEntity);
        tempEntity->params = 3;
        tempEntity = self + 9;
        CreateEntityFromEntity(E_ID_36, self, tempEntity);
        tempEntity = self;
        for (i = 0; i < 8; i++, tempEntity++) {
            tempEntity->unk60 = tempEntity + 1;
            tempEntity->unk5C = self;
        }
        tempEntity->unk60 = self;
        tempEntity->unk5C = self;
        self->unk5C = NULL;
        self->ext.plateLord.unk84 = 0;
        self->ext.plateLord.unk9C.unk4 = -0x100U;
        self->ext.plateLord.unk9C.unk6 = -0xE0U;
        self->ext.plateLord.unk88.unk4 = 0x1C0;
        self->ext.plateLord.unk88.unk6 = -0x40U;
    case 1:
        if (self->ext.plateLord.unk84 == 0) {
            unkStructA = &self->ext.plateLord.unk9C;
            unkStructB = &self->ext.plateLord.unk88;
        } else {
            unkStructA = &self->ext.plateLord.unk88;
            unkStructB = &self->ext.plateLord.unk9C;
        }
        func_us_801D26CC(unkStructA);
        func_us_801D274C(unkStructB);
        self->step = 2;
        break;
    case 2:
    case 3:
        if (self->ext.plateLord.unk84 == 0) {
            unkStructA = &self->ext.plateLord.unk9C;
            unkStructB = &self->ext.plateLord.unk88;
        } else {
            unkStructA = &self->ext.plateLord.unk88;
            unkStructB = &self->ext.plateLord.unk9C;
        }
        switch (self->step_s) {
        case 0:
            tempEntity = unkStructA->unk0;
            counter = tempEntity->posY.i.hi - self->posY.i.hi;
            if (counter < 0x2E) {
                self->posY.val -= FIX(0.125);
            } else {
                self->step_s++;
            }
            break;
        case 1:
            tempEntity = unkStructA->unk0;
            counter = tempEntity->posY.i.hi - self->posY.i.hi;
            if (counter >= 0x2C) {
                self->posY.val += FIX(0.125);
            } else {
                self->step_s--;
            }
            break;
        }
        func_us_801D27C4(&self->ext.plateLord.unk88, false);
        func_us_801D27C4(&self->ext.plateLord.unk9C, true);
        if (self->step == 2) {
            counter = 0x80;
        } else {
            counter = 0x100;
        }
        if (GetDistanceToPlayerY() < 0x40) {
            posX = GetDistanceToPlayerX();
            if (posX < counter) {
                self->ext.plateLord.unk80 = 0x80;
                self->step_s = 0;
                if (posX < 0x60) {
                    self->step = 6;
                } else {
                    self->step = 5;
                }
                if (self->facingLeft == (GetSideToPlayer() & 1)) {
                    self->step_s = 0;
                    self->step = 4;
                }
            }
        }
        break;
    case 5:
        tempEntity = self + 3;
        func_us_801D29F8(&tempEntity->ext.unkPlatelordPlus3.unkB0, 0x7C0, 0x20);
        if (self->ext.plateLord.unk86) {
            tempEntity->ext.unkPlatelordPlus3.unk98 -= 4;
            if (tempEntity->ext.unkPlatelordPlus3.unk98 < 0x200) {
                self->ext.plateLord.unk86 = 0;
            }
        } else {
            tempEntity->ext.unkPlatelordPlus3.unk98 += 4;
            if (tempEntity->ext.unkPlatelordPlus3.unk98 > 0x240) {
                self->ext.plateLord.unk86 = 1;
            }
        }
        posX = g_Tilemap.scrollX.i.hi + self->posX.i.hi;
        tempPoint16B = &D_us_80181F90[self->params];
        if (self->facingLeft) {
            if (tempPoint16B->y < posX) {
                self->step_s = 1;
                self->step = 6;
                break;
            }
        } else {
            if (posX < tempPoint16B->x) {
                self->step_s = 1;
                self->step = 6;
                break;
            }
        }
        switch (self->step_s) {
        case 0:
            self->ext.plateLord.unk80 = 0x40;
            self->step_s++;
            /* fallthrough */
        case 1:
            if (self->ext.plateLord.unk84 == 0) {
                unkStructA = &self->ext.plateLord.unk9C;
                unkStructB = &self->ext.plateLord.unk88;
            } else {
                unkStructA = &self->ext.plateLord.unk88;
                unkStructB = &self->ext.plateLord.unk9C;
            }
            tempEntity = unkStructB->unk0;
            if (tempEntity->ext.plateLord.unk85) {
                tempEntity = unkStructA->unk0;
                if (!tempEntity->ext.plateLord.unk85) {
                    self->ext.plateLord.unk84 ^= 1;
                } else {
                    self->step_s++;
                    break;
                }
            }
            if (self->ext.plateLord.unk84 == 1) {
                func_us_801D29F8(&unkStructA->unk4, 0x200, 8);
                func_us_801D29F8(&unkStructA->unk6, 0x100, 8);
            }
            func_us_801D29F8(&unkStructB->unk4, 0, 0x10);
            func_us_801D29F8(&unkStructB->unk6, 0, 0x10);
            func_us_801D26CC(unkStructA);
            func_us_801D274C(unkStructB);
            break;
        case 2:
            self->ext.plateLord.unk84 = 1;
            unkStructA = &self->ext.plateLord.unk88;
            unkStructB = &self->ext.plateLord.unk9C;
            posX = self->posX.val;
            counter = func_us_801D29F8(&unkStructA->unk4, 0xE0, 0x18);
            counter += func_us_801D29F8(&unkStructA->unk6, -0x100, 0x18);
            func_us_801D26CC(unkStructA);
            posX = self->posX.val - posX;
            tempEntity = unkStructB->unk0;
            tempEntity->posX.val += posX;
            posX = tempEntity->posX.i.hi - self->posX.i.hi;
            if (self->facingLeft) {
                posX = -posX;
            }
            if (posX > 6) {
                if (self->facingLeft) {
                    tempEntity->posX.val += 0x20000;
                } else {
                    tempEntity->posX.val += 0xFFFE0000;
                }
            } else {
                counter++;
            }
            func_us_801D27C4(unkStructB, true);
            if (counter == 3) {
                PlaySfxPositional(0x647);
                self->ext.plateLord.unk84 ^= 1;
                self->step_s++;
            }
            break;
        case 3:
            self->ext.plateLord.unk84 = 0;
            unkStructA = &self->ext.plateLord.unk9C;
            unkStructB = &self->ext.plateLord.unk88;
            posX = self->posX.val;
            counter = func_us_801D29F8(&unkStructA->unk4, -0x140, 0x10);
            counter += func_us_801D29F8(&unkStructA->unk6, -0x80, 0x10);
            func_us_801D26CC(unkStructA);
            posX = self->posX.val - posX;
            tempEntity = unkStructB->unk0;
            tempEntity->posX.val += posX;
            posX = self->posX.i.hi - tempEntity->posX.i.hi;
            if (self->facingLeft) {
                posX = -posX;
            }
            if (posX < 0x16) {
                if (self->facingLeft) {
                    tempEntity->posX.val += FIX(1) + FIX(0.5);
                } else {
                    tempEntity->posX.val += FIX(-2) + FIX(0.5);
                }
            } else {
                counter++;
            }
            func_us_801D27C4(unkStructB, false);
            if (counter == 3) {
                self->ext.plateLord.unk84 ^= 1;
                PlaySfxPositional(0x779);
                self->step_s--;
            }
            break;
        }
        if (self->ext.plateLord.unk80 != 0) {
            self->ext.plateLord.unk80--;
        } else {
            self->step_s = 0;
            if (self->facingLeft == (GetSideToPlayer() & 1)) {
                self->step = 4;
            } else {
                self->step = 9;
            }
        }
        break;
    case 6:
        tempEntity = self + 3;
        func_us_801D29F8(&tempEntity->ext.unkPlatelordPlus3.unkB0, 0x800, 0x20);
        if (self->ext.plateLord.unk86) {
            tempEntity->ext.unkPlatelordPlus3.unk98 -= 8;
            if (tempEntity->ext.unkPlatelordPlus3.unk98 < 0x180) {
                self->ext.plateLord.unk86 = 0;
            }
        } else {
            tempEntity->ext.unkPlatelordPlus3.unk98 += 8;
            if (tempEntity->ext.unkPlatelordPlus3.unk98 > 0x200) {
                self->ext.plateLord.unk86 = 1;
            }
        }
        posX = g_Tilemap.scrollX.i.hi + self->posX.i.hi;
        tempPoint16A = &D_us_80181F90[self->params];
        if (self->facingLeft) {
            if (posX < tempPoint16A->x) {
                self->step_s = 1;
                self->step = 5;
                break;
            }
        } else {
            if (tempPoint16A->y < posX) {
                self->step_s = 1;
                self->step = 5;
                break;
            }
        }
        switch (self->step_s) {
        case 0:
            self->ext.plateLord.unk80 = 0x40;
            self->step_s++;
            /* fallthrough */
        case 1:
            if (self->ext.plateLord.unk84 == 0) {
                unkStructA = &self->ext.plateLord.unk9C;
                unkStructB = &self->ext.plateLord.unk88;
            } else {
                unkStructA = &self->ext.plateLord.unk88;
                unkStructB = &self->ext.plateLord.unk9C;
            }
            tempEntity = unkStructB->unk0;
            if (tempEntity->ext.plateLord.unk85) {
                tempEntity = unkStructA->unk0;
                if (!tempEntity->ext.plateLord.unk85) {
                    self->ext.plateLord.unk84 ^= 1;
                } else {
                    self->step_s++;
                    break;
                }
            }
            if (self->ext.plateLord.unk84 == 1) {
                func_us_801D29F8(&unkStructA->unk4, 0x200, 8);
                func_us_801D29F8(&unkStructA->unk6, 0x100, 8);
            }
            func_us_801D29F8(&unkStructB->unk4, 0, 0x10);
            func_us_801D29F8(&unkStructB->unk6, 0, 0x10);
            func_us_801D26CC(unkStructA);
            func_us_801D274C(unkStructB);
            break;
        case 2:
            self->ext.plateLord.unk84 = 0;
            unkStructA = &self->ext.plateLord.unk9C;
            unkStructB = &self->ext.plateLord.unk88;
            posX = self->posX.val;
            counter = func_us_801D29F8(&unkStructA->unk4, 0, 0x20);
            counter += func_us_801D29F8(&unkStructA->unk6, 0, 0x20);
            func_us_801D26CC(unkStructA);
            posX = self->posX.val - posX;
            tempEntity = unkStructB->unk0;
            tempEntity->posX.val += posX;
            posX = self->posX.i.hi - tempEntity->posX.i.hi;
            if (self->facingLeft) {
                posX = -posX;
            }
            if (posX > 0x10) {
                if (self->facingLeft) {
                    tempEntity->posX.val += FIX(-0.75);
                } else {
                    tempEntity->posX.val += FIX(0.75);
                }
            } else {
                counter++;
            }
            func_us_801D27C4(unkStructB, false);
            if (counter == 3) {
                PlaySfxPositional(0x779);
                self->step_s++;
            }
            break;
        case 3:
            self->ext.plateLord.unk84 = 1;
            unkStructA = &self->ext.plateLord.unk88;
            unkStructB = &self->ext.plateLord.unk9C;
            posX = self->posX.val;
            counter = func_us_801D29F8(&unkStructA->unk4, 0x1C0, 0x18);
            counter += func_us_801D29F8(&unkStructA->unk6, 0x180, 0x18);
            func_us_801D26CC(unkStructA);
            posX = self->posX.val - posX;
            tempEntity = unkStructB->unk0;
            tempEntity->posX.val += posX;
            posX = tempEntity->posX.i.hi - self->posX.i.hi;
            if (self->facingLeft) {
                posX = -posX;
            }
            if (posX < 0xC) {
                if (self->facingLeft) {
                    tempEntity->posX.val += FIX(-1);
                } else {
                    tempEntity->posX.val += FIX(1);
                }
            } else {
                counter++;
            }
            func_us_801D27C4(unkStructB, true);
            if (counter == 3) {
                PlaySfxPositional(0x779);
                self->step_s--;
            }
            break;
        }
        if (self->ext.plateLord.unk80 != 0) {
            self->ext.plateLord.unk80--;
        } else {
            self->step_s = 0;
            if (self->facingLeft == (GetSideToPlayer() & 1)) {
                self->step = 4;
            } else {
                self->step = 9;
            }
        }
        break;
    case 7:
        if (self->ext.plateLord.unk84 == 0) {
            unkStructA = &self->ext.plateLord.unk9C;
            unkStructB = &self->ext.plateLord.unk88;
        } else {
            unkStructA = &self->ext.plateLord.unk88;
            unkStructB = &self->ext.plateLord.unk9C;
        }
        switch (self->step_s) {
        case 0:
            if (self->facingLeft) {
                self->velocityX = FIX(-0.75);
            } else {
                self->velocityX = FIX(0.75);
            }
            self->velocityY = FIX(0.5);
            self->ext.plateLord.unkB0 = 0x50;
            self->step_s++;
            /* fallthrough */
        case 1:
            self->posX.val += self->velocityX;
            self->posY.val += self->velocityY;
            self->velocityY -= self->velocityY >> 8;
            if (self->facingLeft) {
                self->velocityX += FIX(0.125);
            } else {
                self->velocityX -= FIX(0.125);
            }

            if (abs(self->velocityX) == 0xC000) {
                self->step_s = 0;
                self->step = 6;
            }
            func_us_801D27C4(unkStructA, false);
            func_us_801D27C4(unkStructB, false);
        }
        tempEntity = self + 3;
        func_us_801D29F8(&tempEntity->ext.unkPlatelordPlus3.unkB0, 0x8C0, 0x30);
        break;
    case 9:
        if (self->ext.plateLord.unk84 == 0) {
            unkStructA = &self->ext.plateLord.unk9C;
            unkStructB = &self->ext.plateLord.unk88;
        } else {
            unkStructA = &self->ext.plateLord.unk88;
            unkStructB = &self->ext.plateLord.unk9C;
        }
        tempEntity = self + 3;
        switch (self->step_s) {
        case 0:
            tempEntity = unkStructB->unk0;
            if (tempEntity->ext.plateLord.unk85) {
                tempEntity = unkStructA->unk0;
                if (tempEntity->ext.plateLord.unk85) {
                    tempEntity = self + 5;
                    tempEntity->step = 8;
                    self->ext.plateLord.unk84 = 0;
                    self->step_s = 1;
                } else {
                    self->ext.plateLord.unk84 ^= 1;
                    self->step_s = 0;
                }
            } else {
                func_us_801D29F8(&unkStructB->unk4, 0, 0xC);
                func_us_801D29F8(&unkStructB->unk6, 0, 0xC);
                if (self->ext.plateLord.unk84 == 1) {
                    func_us_801D29F8(&unkStructA->unk4, 0x200, 8);
                    func_us_801D29F8(&unkStructA->unk6, 0x100, 8);
                }
            }
            break;
        case 1:
            counter = 0;
            counter += func_us_801D29F8(
                &tempEntity->ext.unkPlatelordPlus3.unk80, 0x880, 0x3C);
            counter += func_us_801D29F8(
                &tempEntity->ext.unkPlatelordPlus3.unk96, 0x900, 0x48);
            counter += func_us_801D29F8(
                &tempEntity->ext.unkPlatelordPlus3.unk94, 0x280, 0x20);
            func_us_801D29F8(
                &tempEntity->ext.unkPlatelordPlus3.unk98, 0x300, 0x20);
            if (counter == 3) {
                self->step_s++;
            }
            break;
        case 2:
            tempEntity->ext.unkPlatelordPlus3.unk82 = 0xC00;
            tempEntity->ext.unkPlatelordPlus3.unk86 = 0xC0;
            tempEntity->step = 9;
            tempEntity = self + 5;
            tempEntity->step = 9;
            self->step_s++;
            break;
        case 3:
            if (self->ext.plateLord.unk86) {
                tempEntity->ext.unkPlatelordPlus3.unk98 -= 2;
                if (tempEntity->ext.unkPlatelordPlus3.unk98 < 0x2F0) {
                    self->ext.plateLord.unk86 = 0;
                }
            } else {
                tempEntity->ext.unkPlatelordPlus3.unk98 += 2;
                if (tempEntity->ext.unkPlatelordPlus3.unk98 > 0x310) {
                    self->ext.plateLord.unk86 = 1;
                }
            }
            tempEntity = self + 3;
            if (tempEntity->ext.unkPlatelordPlus3.unk84 > 0xE8) {
                func_us_801D29F8(&unkStructA->unk4, 0x80, 0x18);
                func_us_801D29F8(&unkStructA->unk6, 0, 0x18);
                func_us_801D26CC(unkStructA);
                func_us_801D29F8(&unkStructB->unk4, 0x340, 0x10);
                func_us_801D29F8(&unkStructB->unk6, 0x40, 0x10);
                func_us_801D274C(unkStructB);
            }
            break;
        }
        if (self->ext.plateLord.unk84 == 0) {
            unkStructA = &self->ext.plateLord.unk9C;
            unkStructB = &self->ext.plateLord.unk88;
        } else {
            unkStructA = &self->ext.plateLord.unk88;
            unkStructB = &self->ext.plateLord.unk9C;
        }
        func_us_801D26CC(unkStructA);
        func_us_801D274C(unkStructB);
        break;
    case 11:
        unkStructA = &self->ext.plateLord.unk9C;
        unkStructB = &self->ext.plateLord.unk88;
        tempEntity = self + 3;
        switch (self->step_s) {
        case 0:
            if (tempEntity->ext.unkPlatelordPlus3.unk96 < 0x500) {
                tempEntity->ext.unkPlatelordPlus3.unk94 -= 0x40;
                if (tempEntity->ext.unkPlatelordPlus3.unk94 <= 0) {
                    tempEntity->ext.unkPlatelordPlus3.unk94 = 0;
                }
            }
            tempEntity->ext.unkPlatelordPlus3.unk96 -= 0xA0;
            if (tempEntity->ext.unkPlatelordPlus3.unk96 < 0x580) {
                tempEntity->animCurFrame = 0x12;
                tempEntity->ext.unkPlatelordPlus3.unk80 -= 0xE8;
            }
            if (tempEntity->ext.unkPlatelordPlus3.unk80 < 0x380) {
                self->step_s++;
            }
            func_us_801D29F8(&unkStructA->unk4, -0x280, 0x40);
            func_us_801D29F8(&unkStructA->unk6, -0x280, 0x40);
            posX = self->posX.val;
            func_us_801D26CC(unkStructA);
            posX = self->posX.val - posX;
            tempEntity = unkStructB->unk0;
            if (tempEntity->ext.plateLord.unk85) {
                if (self->ext.plateLord.unk80 == 0) {
                    self->ext.plateLord.unk80++;
                    if (self->facingLeft) {
                        EntityGreyPuffSpawner(tempEntity, 3, 3, 12, 4, 3, -4);
                    } else {
                        EntityGreyPuffSpawner(tempEntity, 3, 3, -12, 4, 3, 4);
                    }
                }
                tempEntity->posX.val += posX;
                func_us_801D27C4(unkStructB, false);
            } else {
                func_us_801D274C(unkStructB);
                self->ext.plateLord.unk80 = 0;
            }
            tempEntity = self + 3;
            func_us_801D29F8(
                &tempEntity->ext.unkPlatelordPlus3.unkB0, 0x600, 0x30);
            break;
        case 1:
            func_us_801D26CC(unkStructA);
            func_us_801D274C(unkStructB);
            break;
        }
        break;
    case 14:
        unkStructA = &self->ext.plateLord.unk9C;
        unkStructB = &self->ext.plateLord.unk88;
        func_us_801D29F8(&unkStructA->unk4, 0, 0x20);
        func_us_801D29F8(&unkStructA->unk6, -0x40, 0x20);
        func_us_801D29F8(&unkStructB->unk4, 0x100, 0x10);
        func_us_801D29F8(&unkStructB->unk6, 0, 0x10);
        tempEntity = self + 3;
        func_us_801D29F8(&tempEntity->ext.unkPlatelordPlus3.unkB0, 0x7C0, 0x20);
        func_us_801D26CC(unkStructA);
        func_us_801D274C(unkStructB);
        tempEntity = self + 3;
        switch (self->step_s) {
        case 0:
            counter = func_us_801D29F8(
                &tempEntity->ext.unkPlatelordPlus3.unk94, 0x600, 0x40);
            if ((counter != 0) && (tempEntity->animCurFrame != 2)) {

                tempEntity->animCurFrame = 2;
                tempEntity->ext.unkPlatelordPlus3.unk94 = 0x400U;
                counter = 0;
            }
            counter += func_us_801D29F8(
                &tempEntity->ext.unkPlatelordPlus3.unk96, 0x600, 0x20);
            if (counter == 2) {
                tempEntity->ext.unkPlatelordPlus3.unk94 = 0x200;
                tempEntity->ext.unkPlatelordPlus3.unk96 = -0x200U;
                self->step_s++;
            }
            break;
        case 1:
            counter = 0;
            counter = func_us_801D29F8(
                &tempEntity->ext.unkPlatelordPlus3.unk80, 0x180, 0x20);
            counter += func_us_801D29F8(
                &tempEntity->ext.unkPlatelordPlus3.unk94, 0x100, 8);
            counter += func_us_801D29F8(
                &tempEntity->ext.unkPlatelordPlus3.unk96, -0x1C0, 0x10);
            func_us_801D29F8(
                &tempEntity->ext.unkPlatelordPlus3.unk98, 0x180, 0x10);
            if (counter == 3) {
                self->step = 3;
                self->step_s = 0;
                self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
                tempEntity = self + 5;
                tempEntity->step = 3;
            }
            break;
        }
        break;
    case 4:
        if (self->ext.plateLord.unk84 == 0) {
            unkStructA = &self->ext.plateLord.unk9C;
            unkStructB = &self->ext.plateLord.unk88;
        } else {
            unkStructA = &self->ext.plateLord.unk88;
            unkStructB = &self->ext.plateLord.unk9C;
        }
        switch (self->step_s) {
        case 0:
            self->facingLeft ^= 1;
            tempEntity = unkStructA->unk0;
            if (self->facingLeft ^ self->ext.plateLord.unk84) {
                tempEntity->posX.i.hi -= 0x20;
            } else {
                tempEntity->posX.i.hi += 0x20;
            }
            self->ext.plateLord.unk80 = 0x10;
            self->step_s++;
            break;
        case 1:
            self->ext.plateLord.unk80--;
            if (self->ext.plateLord.unk80 == 0) {
                self->step_s = 0;
                self->step = 3;
            }
            break;
        }
        func_us_801D26CC(unkStructA);
        func_us_801D274C(unkStructB);
        break;
    case 16:
        if (self->ext.plateLord.unk84 == 0) {
            unkStructA = &self->ext.plateLord.unk9C;
            unkStructB = &self->ext.plateLord.unk88;
        } else {
            unkStructA = &self->ext.plateLord.unk88;
            unkStructB = &self->ext.plateLord.unk9C;
        }
        switch (self->step_s) {
        case 0:
            tempEntity = self;
            for (i = 0; i < 10; i++, tempEntity++) {
                tempEntity->hitboxState = 0;
            }
            tempEntity = self + 3;
            tempEntity->step = 3;
            tempEntity = self + 5;
            tempEntity->step = 3;
            if (self->ext.plateLord.unk87) {
                self->step_s = 3;
                tempEntity = self + 5;
                tempEntity->step = 0x12;
            } else {
                self->step_s = 3;
                tempEntity = self + 5;
                tempEntity->step = 0x12;
            }

            /* fallthrough */
        case 1:
            tempEntity = self + 3;
            counter = func_us_801D29F8(
                &tempEntity->ext.unkPlatelordPlus3.unk80, 0x800, 0xA0);
            counter += func_us_801D29F8(
                &tempEntity->ext.unkPlatelordPlus3.unk96, 0x800, 0xA0);
            counter += func_us_801D29F8(
                &tempEntity->ext.unkPlatelordPlus3.unk94, 0, 0x80);
            func_us_801D26CC(unkStructA);
            func_us_801D274C(unkStructB);
            if (counter == 3) {
                tempEntity = self + 5;
                tempEntity->step = 0x10;
                self->step_s = 2;
            }
            break;
        case 2:
            if (self->ext.plateLord.unk87) {
                self->step_s++;
            }
            func_us_801D26CC(unkStructA);
            func_us_801D274C(unkStructB);
            break;
        case 3:
            self->posY.val += self->velocityY;
            self->velocityY += 0x400;
            g_api.CheckCollision(
                self->posX.i.hi, self->posY.i.hi + 0x10, &collider, 0);
            if (collider.effects & EFFECT_SOLID) {
                self->step_s++;
            }
            func_us_801D27C4(unkStructA, false);
            func_us_801D27C4(unkStructB, false);
            break;
        case 4:
            prim = self->ext.prim;
            while (prim != NULL) {
                prim->drawMode = DRAW_HIDE;
                prim = prim->next;
            }
            tempEntity = self + 2;
            tempEntity->step = 0x10;
            tempEntity = self + 1;
            tempEntity->step = 0x10;
            self->ext.plateLord.unk80 = 0x30;
            PlaySfxPositional(0x694);
            self->step_s++;
            break;
        case 5:
            if (--self->ext.plateLord.unk80 == 0) {
                tempEntity = self;
                for (i = 0; i < 9; i++, tempEntity++) {
                    DestroyEntity(tempEntity);
                }
                return;
            }
            if (!(self->ext.plateLord.unk80 & 3)) {
                posX = self->posX.i.hi;
                posY = self->posY.i.hi;
                posX += (Random() & 0x1F) - 0x10;
                posY += (Random() & 0x1F) - 0x10;
                tempEntity = AllocEntity(D_8007D858, D_8007D858 + 32);
                if (tempEntity != NULL) {
                    CreateEntityFromCurrentEntity(2, tempEntity);
                    tempEntity->params = 1;
                    tempEntity->zPriority = self->zPriority + 8;
                    tempEntity->posX.i.hi = posX;
                    tempEntity->posY.i.hi = posY;
                }
            }
            break;
        }
        break;
    }
    prim = self->ext.prim;
    unkStructC = &self->ext.plateLord.unk88;
    for (i = 0; i < 2; i++, unkStructC++) {
        tempEntity = unkStructC->unk0;
        tempPoint32A = &unkStructC->unk8;
        tempS16 = unkStructC->unk4;
        tempPoint32B = unkStructC->unk10;
        func_us_801D2424(
            (Point32*)&self->posX, tempS16, F(tempPoint32B->x).i.hi,
            tempPoint32A, tempS16, F(tempPoint32B->x).i.hi, prim);
        if (self->palette & 0x8000) {
            prim->clut = self->palette & 0xFFF;
        } else {
            prim->clut = 0x22C;
        }
        prim = prim->next;
        tempS16 = unkStructC->unk6;
        func_801CD78C(tempPoint32A, -4, tempS16, &point32);
        func_us_801D2424(&point32, tempS16, F(tempPoint32B->y).i.hi,
                         (Point32*)&tempEntity->posX, tempS16,
                         F(tempPoint32B->y).i.hi, prim);
        if (self->palette & 0x8000) {
            prim->clut = self->palette & 0xFFF;
        } else {
            prim->clut = 0x22B;
        }
        prim = prim->next;
    }
}

INCLUDE_ASM("st/no0/nonmatchings/e_plate_lord", func_us_801D4324);

INCLUDE_ASM("st/no0/nonmatchings/e_plate_lord", func_us_801D44A0);

INCLUDE_RODATA("st/no0/nonmatchings/e_plate_lord", D_us_801C1684);

INCLUDE_ASM("st/no0/nonmatchings/e_plate_lord", func_us_801D4AA4);

INCLUDE_ASM("st/no0/nonmatchings/e_plate_lord", func_us_801D4CAC);

void func_us_801D4E30(void) {
    Primitive* prim;
    s32 i;

    prim = g_CurrentEntity->ext.prim;
    for (i = 0; i < 10; i++) {
        prim->x0 = (prim->x0 + prim->x1) / 2;
        prim->y0 = (prim->y0 + prim->y2) / 2;
        prim = prim->next;
    }
}

INCLUDE_ASM("st/no0/nonmatchings/e_plate_lord", func_us_801D4E94);

INCLUDE_ASM("st/no0/nonmatchings/e_plate_lord", func_us_801D4FCC);

INCLUDE_ASM("st/no0/nonmatchings/e_plate_lord", func_us_801D5074);

void func_us_801D51EC(void) {
    Primitive* prim;
    s32 i;

    prim = g_CurrentEntity->ext.prim;
    for (i = 0; i < 10; i++) {
        prim->x0 = prim->x2 = prim->x0 - 3;
        prim->x1 = prim->x3 = prim->x0 + 6;
        prim->y0 = prim->y1 = prim->y0 - 3;
        prim->y2 = prim->y3 = prim->y0 + 6;

        prim = prim->next;
    }
}

void func_us_801D5250(void) {
    Primitive* prim = g_CurrentEntity->ext.prim;
    Collider collider;
    s32 i;

    for (i = 0; i < 10; i++) {
        g_api.CheckCollision(prim->x0, prim->y0 + 3, &collider, 0);
        if (collider.effects & EFFECT_SOLID) {
            prim->y0 += collider.unk18;
        }
        prim = prim->next;
    }
}

INCLUDE_ASM("st/no0/nonmatchings/e_plate_lord", func_us_801D52E0);

INCLUDE_ASM("st/no0/nonmatchings/e_plate_lord", func_us_801D5384);

INCLUDE_ASM("st/no0/nonmatchings/e_plate_lord", func_us_801D542C);
