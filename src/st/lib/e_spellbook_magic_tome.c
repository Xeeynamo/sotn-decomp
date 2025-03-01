// SPDX-License-Identifier: AGPL-3.0-or-later
#include "lib.h"

// Spellbook helper
INCLUDE_ASM("st/lib/nonmatchings/e_spellbook_magic_tome", func_us_801D1BCC);

// Spellbook helper
INCLUDE_ASM("st/lib/nonmatchings/e_spellbook_magic_tome", func_us_801D1F50);

// Spellbook helper
INCLUDE_ASM("st/lib/nonmatchings/e_spellbook_magic_tome", func_us_801D2108);

// Spellbook helper
INCLUDE_ASM("st/lib/nonmatchings/e_spellbook_magic_tome", func_us_801D2148);

// Spellbook helper
INCLUDE_ASM("st/lib/nonmatchings/e_spellbook_magic_tome", func_801CDC80);

extern u8* D_us_801830DC[];

void EntitySpellbook(Entity* self) {
    s32 dx, dy;
    RECT rect;
    Entity* tempEntity;
    Primitive* prim;
    s32 primIndex;
    s32 i;
    u8* ptr;
    u32 palette;
    s16 angle;
    s32 mag;

    if ((self->flags & FLAG_DEAD) && self->step < 8) {
        SetStep(8);
    }
    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitSpellbook);
        self->hitboxState = 0;
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 0xC);
        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags |= FLAG_HAS_PRIMS;
        self->primIndex = primIndex;
        prim = &g_PrimBuf[primIndex];
        self->ext.spellbookMagicTome.unk7C = prim;
        palette = PAL_DRA(0x25A);
        self->palette = palette;
        for (i = 0; i < 12; i++) {
            ptr = D_us_801830DC[i];
            if (i % 6 < 2) {
                prim->clut = palette + 0;
            } else {
                prim->clut = palette + 1;
            }
            prim->tpage = 0x15;
            prim->u0 = prim->u2 = ptr[0];
            prim->u1 = prim->u3 = ptr[2];
            prim->v0 = prim->v1 = ptr[1];
            prim->v2 = prim->v3 = ptr[3];
            prim->priority = self->zPriority;
            prim->drawMode = DRAW_HIDE;
            prim = prim->next;
            ptr += 4;
        }
        tempEntity = self + 1;
        CreateEntityFromCurrentEntity(E_ID_3E, tempEntity);
        tempEntity->params = 0;
        self->ext.spellbookMagicTome.unk9C = 0x400;
        self->ext.spellbookMagicTome.unk8A = 0x300;
        SetStep(2);
        break;

    case 2:
        if (GetDistanceToPlayerX() < 0x40 && GetDistanceToPlayerY() < 0x40) {
            SetStep(3);
        }
        break;

    case 3:
        self->ext.spellbookMagicTome.unk8A -= 0x10;
        if (self->ext.spellbookMagicTome.unk8A < 0) {
            self->ext.spellbookMagicTome.unk8A = 0;
            self->hitboxState = 3;
            SetStep(4);
        }
        break;

    case 4:
        if (!self->step_s) {
            self->ext.spellbookMagicTome.unk8E = 0x200;
            self->step_s++;
        }
        MoveEntity();
        tempEntity = &PLAYER;
        angle = GetAngleBetweenEntities(self, tempEntity);
        angle =
            GetNormalizedAngle(0x10, self->ext.spellbookMagicTome.unk8C, angle);
        mag = self->ext.spellbookMagicTome.unk90;
        self->velocityX = (mag * rcos(angle)) >> 0xC;
        self->velocityY = (mag * rsin(angle)) >> 0xC;
        self->ext.spellbookMagicTome.unk8C = angle;
        mag += 0x400;
        if (mag > FIX(0.75)) {
            mag = FIX(0.75);
        }
        if (self->hitFlags & 3) {
            mag = FIX(-0.75);
        }
        self->ext.spellbookMagicTome.unk90 = mag;
        if (!self->ext.spellbookMagicTome.unk80) {
            self->ext.spellbookMagicTome.unk80 = 0x40;
            self->ext.spellbookMagicTome.unkA4 = (Random() & 0x1F) - 0x10;
            self->ext.spellbookMagicTome.unkA6 = (Random() & 0x1F) - 0x10;
            self->ext.spellbookMagicTome.unkA8 = (Random() & 0x1F) - 0x10;
        } else {
            self->ext.spellbookMagicTome.unk80--;
        }
        func_us_801D2108();
        if (!--self->ext.spellbookMagicTome.unk8E) {
            SetStep(5);
        }
        break;

    case 5:
        switch (self->step_s) {
        case 0:
            tempEntity = &PLAYER;
            angle = GetAngleBetweenEntities(self, tempEntity);
            rect.x = 0x280;
            rect.y = angle + 0x800;
            rect.w = 0x440;
            rect.h = 0x20;
            func_us_801D1F50(&rect);
            self->ext.spellbookMagicTome.unk80 = 0x20;
            self->step_s++;
            /* fallthrough */
        case 1:
            func_us_801D2108();
            if (!--self->ext.spellbookMagicTome.unk80) {
                self->step_s++;
            }
            break;

        case 2:
            if (func_801CDC80(
                    &self->ext.spellbookMagicTome.unk82, 0x300, 0x20)) {
                self->step_s++;
            }
            break;

        case 3:
            tempEntity = self + 1;
            tempEntity->ext.spellbookMagicTome.unk94 = 1;
            self->step_s++;
            break;

        case 4:
            tempEntity = self + 1;
            if (!tempEntity->ext.spellbookMagicTome.unk94) {
                self->step_s++;
            }
            break;

        case 5:
            if (func_801CDC80(&self->ext.spellbookMagicTome.unk82, 0, 0x10)) {
                SetStep(4);
            }
            break;
        }
        break;

    case 8:
        if ((Random() & 0xF) == 0) {
            tempEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (tempEntity != NULL) {
                CreateEntityFromEntity(E_EXPLOSION, self, tempEntity);
                tempEntity->params = 1;
                tempEntity->posX.i.hi += self->ext.spellbookMagicTome.unk84 / 2;
                tempEntity->posY.i.hi += self->ext.spellbookMagicTome.unk86 / 2;
                tempEntity->posX.i.hi += (Random() & 0x1F) - 0x10;
                tempEntity->posY.i.hi += (Random() & 0x1F) - 0x10;
                tempEntity->zPriority = 0xD0;
            }
        }
        if ((g_Timer & 0xF) == 0) {
            PlaySfxPositional(SFX_EXPLODE_B);
        }
        switch (self->step_s) {
        case 0:
            self->ext.spellbookMagicTome.unkA4 = 0x40;
            self->ext.spellbookMagicTome.unkA6 = 0x40;
            self->ext.spellbookMagicTome.unkA8 = 0x40;
            self->ext.spellbookMagicTome.unk80 = 0x80;
            self->hitboxState = 0;
            self->step_s++;
            /* fallthrough */
        case 1:
            func_801CDC80(&self->ext.spellbookMagicTome.unk82, 0x200, 0x10);
            func_us_801D2108();
            if (g_Timer & 1) {
                tempEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
                if (tempEntity != NULL) {
                    CreateEntityFromEntity(E_ID_31, self, tempEntity);
                    tempEntity->posX.i.hi +=
                        self->ext.spellbookMagicTome.unk84 / 2;
                    tempEntity->posY.i.hi +=
                        self->ext.spellbookMagicTome.unk86 / 2;
                    dx = self->ext.spellbookMagicTome.unk84;
                    dy = self->ext.spellbookMagicTome.unk86;
                    angle = ratan2(dy, dx);
                    tempEntity->rotZ = angle;
                    tempEntity->zPriority = self->ext.spellbookMagicTome.unk88;
                    dx = (Random() & 0x1F) - 0x10;
                    tempEntity->posX.i.hi += (dx * rcos(angle + 0x400)) >> 0xC;
                    tempEntity->posY.i.hi += (dx * rsin(angle + 0x400)) >> 0xC;
                }
            }
            if ((self->ext.spellbookMagicTome.unk80 & 7) == 0) {
                PlaySfxPositional(0x78D);
            }
            if (!--self->ext.spellbookMagicTome.unk80) {
                self->flags |= FLAG_DESTROY_IF_OUT_OF_CAMERA;
                self->step_s++;
            }
            break;

        case 2:
            MoveEntity();
            func_801CDC80(&self->ext.spellbookMagicTome.unk82, 0x700, 8);
            self->velocityY += FIX(0.0625);
            break;
        }
        break;

    case 32:
        if ((g_Timer & 0xF) == 0) {
            tempEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (tempEntity != NULL) {
                CreateEntityFromEntity(E_ID_31, self, tempEntity);
                tempEntity->posX.i.hi += self->ext.spellbookMagicTome.unk84;
                tempEntity->posY.i.hi += self->ext.spellbookMagicTome.unk86;
            }
        }
        if (g_pads[1].pressed & PAD_TRIANGLE) {
            self->ext.spellbookMagicTome.unk9C += 0x10;
        }
        if (g_pads[1].pressed & PAD_CROSS) {
            self->ext.spellbookMagicTome.unk9C -= 0x10;
        }
        if (g_pads[1].pressed & PAD_CIRCLE) {
            self->ext.spellbookMagicTome.unk9E += 0x10;
        }
        if (g_pads[1].pressed & PAD_SQUARE) {
            self->ext.spellbookMagicTome.unk9E -= 0x10;
        }
        if (g_pads[1].pressed & PAD_RIGHT) {
            self->ext.spellbookMagicTome.unkA0 += 0x10;
        }
        if (g_pads[1].pressed & PAD_LEFT) {
            self->ext.spellbookMagicTome.unkA0 -= 0x10;
        }
        if (g_pads[1].pressed & PAD_UP) {
            self->ext.spellbookMagicTome.unk82 += 0x10;
        }
        if (g_pads[1].pressed & PAD_DOWN) {
            self->ext.spellbookMagicTome.unk82 -= 0x10;
        }
        if (g_pads[0].pressed & PAD_UP) {
            self->ext.spellbookMagicTome.unk8A += 0x10;
        }
        if (g_pads[0].pressed & PAD_DOWN) {
            self->ext.spellbookMagicTome.unk8A -= 0x10;
        }
        if (g_pads[1].pressed & PAD_SELECT) {
            self->ext.spellbookMagicTome.unk9C = 0;
            self->ext.spellbookMagicTome.unk9E = 0;
            self->ext.spellbookMagicTome.unkA0 = 0;
            self->ext.spellbookMagicTome.unk82 = 0;
        }
        FntPrint("x:%4x\n", self->ext.spellbookMagicTome.unk9C);
        FntPrint("y:%4x\n", self->ext.spellbookMagicTome.unk9E);
        FntPrint("z:%4x\n", self->ext.spellbookMagicTome.unkA0);
        FntPrint("hz:%4x\n", self->ext.spellbookMagicTome.unk8A);
        FntPrint("w:%4x\n", self->ext.spellbookMagicTome.unk82);
        break;
    }
    func_us_801D1BCC();
    self->hitboxOffX = self->ext.spellbookMagicTome.unk84 / 2;
    self->hitboxOffY = self->ext.spellbookMagicTome.unk86 / 2;
}

// Possibly Magic Tome + Spellbook death spawner for letters
INCLUDE_ASM("st/lib/nonmatchings/e_spellbook_magic_tome", func_us_801D2CE0);

extern u8* D_us_8018310C[];

void EntityMagicTome(Entity* self) {
    RECT rect;
    Entity* tempEntity;
    Primitive* prim;
    s32 primIndex;
    s16 angle;
    s32 dx, dy;
    s32 i;
    s32 palette;
    u8* ptr;

    if ((self->flags & FLAG_DEAD) && self->step < 8) {
        SetStep(8);
    }
    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitMagicTome);
        self->hitboxState = 0;
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 0xC);
        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags |= FLAG_HAS_PRIMS;
        self->primIndex = primIndex;
        prim = &g_PrimBuf[primIndex];
        self->ext.spellbookMagicTome.unk7C = prim;
        palette = PAL_DRA(0x25E);
        self->palette = palette;
        for (i = 0; i < 12; i++) {
            ptr = D_us_8018310C[i];
            if (i % 6 < 2) {
                prim->clut = palette + 0;
            } else {
                prim->clut = palette + 1;
            }
            prim->tpage = 0x15;
            prim->u0 = prim->u2 = ptr[0];
            prim->u1 = prim->u3 = ptr[2];
            prim->v0 = prim->v1 = ptr[1];
            prim->v2 = prim->v3 = ptr[3];
            prim->priority = self->zPriority;
            prim->drawMode = DRAW_HIDE;
            prim = prim->next;
            ptr += 4;
        }
        tempEntity = self + 1;
        CreateEntityFromCurrentEntity(E_ID_3E, tempEntity);
        tempEntity->params = 2;
        self->ext.spellbookMagicTome.unk9C = 0x400;
        self->ext.spellbookMagicTome.unk8A = 0x300;
        SetStep(2);
        break;

    case 2:
        if (GetDistanceToPlayerX() < 0x68 && GetDistanceToPlayerY() < 0x60) {
            SetStep(3);
        }
        break;

    case 3:
        self->ext.spellbookMagicTome.unk8A -= 0x10;
        if (self->ext.spellbookMagicTome.unk8A < 0) {
            self->ext.spellbookMagicTome.unk8A = 0;
            self->hitboxState = 3;
            SetStep(4);
        }
        break;

    case 4:
        switch (self->step_s) {
        case 0:
            self->ext.spellbookMagicTome.unk8E = 0x60;
            self->step_s++;
            /* fallthrough */
        case 1:
            tempEntity = &PLAYER;
            dx = tempEntity->posX.i.hi - self->posX.i.hi;
            dy = tempEntity->posY.i.hi - self->posY.i.hi;
            if (abs(dx) > abs(dy)) {
                self->velocityY = 0;
                if (dx > 0) {
                    self->velocityX = FIX(2.0);
                } else {
                    self->velocityX = FIX(-2.0);
                }
            } else {
                self->velocityX = 0;
                if (dy > 0) {
                    self->velocityY = FIX(2.0);
                } else {
                    self->velocityY = FIX(-2.0);
                }
            }
            self->ext.spellbookMagicTome.unkA4 = (Random() & 0x1F) - 0x10;
            self->ext.spellbookMagicTome.unkA6 = (Random() & 0x1F) - 0x10;
            self->ext.spellbookMagicTome.unkA8 = (Random() & 0x1F) - 0x10;
            self->ext.spellbookMagicTome.unk80 = 0x40;
            self->step_s++;
            /* fallthrough */
        case 2:
            MoveEntity();
            func_us_801D2108();
            if (!--self->ext.spellbookMagicTome.unk8E) {
                SetStep(5);
            }
            break;
        }
        break;

    case 5:
        switch (self->step_s) {
        case 0:
            tempEntity = &PLAYER;
            angle = GetAngleBetweenEntities(self, tempEntity);
            rect.x = 0x280;
            rect.y = angle + 0x800;
            rect.w = 0x440;
            rect.h = 0x20;
            func_us_801D1F50(&rect);
            self->ext.spellbookMagicTome.unk80 = 0x20;
            self->step_s++;
            /* fallthrough */
        case 1:
            func_us_801D2108();
            if (!--self->ext.spellbookMagicTome.unk80) {
                self->step_s++;
            }
            break;

        case 2:
            if (func_801CDC80(
                    &self->ext.spellbookMagicTome.unk82, 0x300, 0x10) != 0) {
                self->step_s++;
            }
            break;

        case 3:
            tempEntity = self + 1;
            tempEntity->ext.spellbookMagicTome.unk94 = 1;
            self->step_s++;
            break;

        case 4:
            tempEntity = self + 1;
            if (!tempEntity->ext.spellbookMagicTome.unk94) {
                self->step_s++;
            }
            break;

        case 5:
            if (func_801CDC80(&self->ext.spellbookMagicTome.unk82, 0, 0x10)) {
                SetStep(4);
            }
            break;
        }
        break;

    case 8:
        if ((Random() & 0xF) == 0) {
            tempEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (tempEntity != NULL) {
                CreateEntityFromEntity(E_EXPLOSION, self, tempEntity);
                tempEntity->params = 1;
                tempEntity->posX.i.hi += self->ext.spellbookMagicTome.unk84 / 2;
                tempEntity->posY.i.hi += self->ext.spellbookMagicTome.unk86 / 2;
                tempEntity->posX.i.hi += (Random() & 0x1F) - 0x10;
                tempEntity->posY.i.hi += (Random() & 0x1F) - 0x10;
                tempEntity->zPriority = 0xC0;
            }
        }
        if ((g_Timer & 0xF) == 0) {
            PlaySfxPositional(SFX_EXPLODE_B);
        }
        switch (self->step_s) {
        case 0:
            self->ext.spellbookMagicTome.unkA4 = 0x40;
            self->ext.spellbookMagicTome.unkA6 = 0x40;
            self->ext.spellbookMagicTome.unkA8 = 0x40;
            self->ext.spellbookMagicTome.unk80 = 0x80;
            self->hitboxState = 0;
            self->step_s++;
            /* fallthrough */
        case 1:
            func_801CDC80(&self->ext.spellbookMagicTome.unk82, 0x200, 0x10);
            func_us_801D2108();
            if (g_Timer & 1) {
                tempEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
                if (tempEntity != NULL) {
                    CreateEntityFromEntity(E_ID_31, self, tempEntity);
                    tempEntity->posX.i.hi +=
                        self->ext.spellbookMagicTome.unk84 / 2;
                    tempEntity->posY.i.hi +=
                        self->ext.spellbookMagicTome.unk86 / 2;
                    dx = self->ext.spellbookMagicTome.unk84;
                    dy = self->ext.spellbookMagicTome.unk86;
                    angle = ratan2(dy, dx);
                    tempEntity->rotZ = angle;
                    tempEntity->zPriority = self->ext.spellbookMagicTome.unk88;
                    dx = (Random() & 0x1F) - 0x10;
                    tempEntity->posX.i.hi += (dx * rcos(angle + 0x400)) >> 0xC;
                    tempEntity->posY.i.hi += (dx * rsin(angle + 0x400)) >> 0xC;
                }
            }
            if ((self->ext.spellbookMagicTome.unk80 & 7) == 0) {
                g_api.PlaySfx(0x78D);
            }
            if (!--self->ext.spellbookMagicTome.unk80) {
                self->flags |= FLAG_DESTROY_IF_OUT_OF_CAMERA;
                self->step_s++;
            }
            break;

        case 2:
            MoveEntity();
            func_801CDC80(&self->ext.spellbookMagicTome.unk82, 0x700, 8);
            self->velocityY += FIX(0.0625);
            break;
        }
        break;
    }
    func_us_801D1BCC();
    self->hitboxOffX = self->ext.spellbookMagicTome.unk84 / 2;
    self->hitboxOffY = self->ext.spellbookMagicTome.unk86 / 2;
}

// Unk related function for Magic Tome and Spellbook
INCLUDE_ASM("st/lib/nonmatchings/e_spellbook_magic_tome", func_us_801D35B8);
