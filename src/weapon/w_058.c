// Weapon ID #58. Used by weapons:
// Alucart shield, Unknown#215
#include "weapon_private.h"
#include "shared.h"

extern SpriteParts D_19A000_8017A040[];

INCLUDE_ASM("weapon/nonmatchings/w_058", EntityWeaponAttack);

s32 func_ptr_80170004(Entity* self) {}

void func_ptr_80170008(Entity* self) {}

void func_ptr_8017000C(Entity* self) {}

s32 func_ptr_80170010(Entity* self) {}

s32 func_ptr_80170014(Entity* self) {}

s32 GetWeaponId(void) { return 52; }

void EntityWeaponShieldSpell(Entity* self) {
    Primitive* prim;
    s16 primRight;
    s16 primLeft;
    s16 selfX;
    s16 selfY;
    bool showQuestionMark;

    // This block sets variables that are unused
    s16 temp_s1;
    s16 temp_s5;

    temp_s1 = 0x1C;
    if (PLAYER.facingLeft) {
        temp_s1 = -temp_s1;
    }
    temp_s5 = 0x30;

    showQuestionMark = false;
    switch (self->step) {
    case 0:
        self->primIndex = g_api.AllocPrimitives(PRIM_GT4, 2);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        SetSpriteBank1(D_19A000_8017A040);
        if (g_HandId != 0) {
            self->animSet = ANIMSET_OVL(0x12);
            self->palette = 0x128;
            self->ext.shield.unk86 = 0x129;
            self->unk5A = 0x66;
            self->ext.shield.unk7C = 0;
            self->ext.shield.unk7D = 0x80;
        } else {
            self->animSet = ANIMSET_OVL(0x10);
            self->palette = 0x110;
            self->ext.shield.unk86 = 0x111;
            self->unk5A = 0x64;
            self->ext.shield.unk7C = 0x80;
            self->ext.shield.unk7D = 0;
        }

        self->posY.i.hi -= 8;
        self->flags = FLAG_UNK_04000000 | FLAG_HAS_PRIMS | FLAG_UNK_10000;
        self->zPriority = PLAYER.zPriority - 2;
        self->facingLeft = PLAYER.facingLeft;
        self->animCurFrame = 0x3E;
        self->drawFlags = FLAG_DRAW_ROTX | FLAG_DRAW_ROTY;
        self->rotX = self->rotY = 0;
        // The primitive for the main shield appearing up behind Alucard
        prim = &g_PrimBuf[self->primIndex];
        prim->clut = 0x19F;
        prim->tpage = 0x19;
        prim->u0 = prim->u2 = 0x80;
        prim->u1 = prim->u3 = 0x80 + 0x4F;
        prim->v0 = prim->v1 =
            self->ext.shield.unk7C + 0; // PSP needs +0 which is interesting
        prim->v2 = prim->v3 = self->ext.shield.unk7C + 0x4F;
        self->ext.shield.unk82 = 0;
        prim->r0 = prim->g0 = prim->b0 = prim->r1 = prim->g1 = prim->b1 =
            prim->r2 = prim->g2 = prim->b2 = prim->r3 = prim->g3 = prim->b3 =
                0x80;
        prim->priority = self->zPriority - 4;
        prim->drawMode =
            DRAW_UNK_40 | DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS | DRAW_TRANSP;
        prim = prim->next;
        // The primitive for the little question mark above Alucard
        prim->clut = 0x190;
        prim->tpage = 0x1E;
        prim->u0 = prim->u2 = 0x78;
        prim->u1 = prim->u3 = 0x78 + 7;
        prim->v0 = prim->v1 = 8;
        prim->v2 = prim->v3 = 8 + 7;
        prim->priority = self->zPriority + 4;
        prim->drawMode = DRAW_HIDE;
        SetSpeedX(FIX(-2));
        self->velocityY = 0;
        DestroyEntityWeapon(1);
        g_api.PlaySfx(SFX_UNK_641);
        g_unkGraphicsStruct.unk20 = 1;
        self->step++;
        break;
    case 1:
        DecelerateX(0x1000);
        self->velocityY -= FIX(0.15625);
        self->posX.val += self->velocityX;
        self->posY.val += self->velocityY;
        self->rotX += 12;
        self->rotY = self->rotX;
        self->ext.shield.unk82 = self->rotX * 0x28 / 256;
        if (self->rotX >= 0x100) {
            self->ext.shield.unk82 = 0x28;
            self->rotY = self->rotX = 0x100;
            self->ext.shield.unk80 = 0x40;
            self->step++;
        }
        break;
    case 2:
        if (--self->ext.shield.unk80 == 0) {
            self->ext.shield.unk80 = 0x10;
            g_api.PlaySfx(SFX_UNK_668);
            self->step++;
        }
        break;
    case 3:
        prim = &g_PrimBuf[self->primIndex];
        if (!(self->ext.shield.unk80 & 1)) {
            prim->priority = 0x1FC;
        } else {
            prim->priority = self->zPriority - 2;
        }
        self->rotX -= 0x10;
        if (self->rotX <= 0) {
            self->rotX = 0;
        }
        self->rotY = self->rotX;
        if (--self->ext.shield.unk80 == 0) {
            self->animCurFrame = 0;
            self->ext.shield.unk80 = 0x20;
            self->step++;
        }
        break;
    case 4:
        self->ext.shield.unk82 += 8;
        self->rotX += 0x10;
        if (self->rotX >= 0x100) {
            self->rotX = 0x100;
        }
        self->ext.shield.childPalette = self->rotX * 36 / 256;
        self->ext.shield.unk8A = self->rotX * 28 / 256;
        prim = &g_PrimBuf[self->primIndex];
        if (prim->b3 > 8) {
            prim->b3 -= 4;
        }
        prim->r0 = prim->g0 = prim->b0 = prim->r1 = prim->g1 = prim->b1 =
            prim->r2 = prim->g2 = prim->b2 = prim->r3 = prim->g3 = prim->b3;
        self->ext.shield.unk86 += 4;
        self->ext.shield.unk92 += self->ext.shield.unk86;
        if (--self->ext.shield.unk80 == 0) {
            self->ext.shield.unk80 = 0x28;
            self->step++;
        }
        break;
    case 5:
        showQuestionMark = true;
        if (--self->ext.shield.unk80 == 0) {
            self->step++;
        }
        break;
    case 6:
        g_unkGraphicsStruct.unk20 = 0;
        DestroyEntity(self);
        return;
    }
    selfX = self->posX.i.hi;
    selfY = self->posY.i.hi;
    prim = &g_PrimBuf[self->primIndex];
    if (prim->b3 > 8) {
        if (g_Timer & 1) {
            prim->drawMode |= DRAW_HIDE;
        } else {
            prim->drawMode &= ~DRAW_HIDE;
        }
    }
    prim->x0 = prim->x2 = selfX - self->ext.shield.unk82;
    prim->x1 = prim->x3 = (selfX + self->ext.shield.unk82) - 1;
    prim->y0 = prim->y1 = selfY - self->ext.shield.unk82;
    prim->y2 = prim->y3 = (selfY + self->ext.shield.unk82) - 1;
    prim = prim->next;
    if (PLAYER.facingLeft) {
        prim->x0 = prim->x2 = PLAYER.posX.i.hi + 2;
        prim->x1 = prim->x3 = prim->x0 + 7;

    } else {
        prim->x0 = prim->x2 = PLAYER.posX.i.hi - 6;
        prim->x1 = prim->x3 = prim->x0 + 7;
    }

    prim->y0 = prim->y1 = PLAYER.posY.i.hi - 0x22;
    prim->y2 = prim->y3 = prim->y0 + 7;
    if (showQuestionMark) {
        prim->drawMode = DRAW_DEFAULT;
    } else {
        prim->drawMode = DRAW_HIDE;
    }
}

void func_ptr_80170024(Entity* self) {}

void func_ptr_80170028(Entity* self) {}

void WeaponUnused2C(void) {}

void WeaponUnused30(void) {}

void WeaponUnused34(void) {}

void WeaponUnused38(void) {}

void WeaponUnused3C(void) {}
