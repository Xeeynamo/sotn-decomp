// Weapon ID #27. Used by weapons:
// Medusa shield, Unknown#211
#include "weapon_private.h"
#include "shared.h"

extern SpriteParts D_C1000_8017A040[];
extern AnimationFrame D_C1000_8017AC8C[];
extern AnimationFrame D_C1000_8017ACB4[];
extern s32 D_C1000_8017C6EC; // g_DebugWaitInfoTimer

void DebugShowWaitInfo(const char* msg) {
    g_CurrentBuffer = g_CurrentBuffer->next;
    FntPrint(msg);
    if (D_C1000_8017C6EC++ & 4) {
        FntPrint("\no\n\0"); // TODO: remove extra NUL byte padding
    }
    DrawSync(0);
    VSync(0);
    PutDrawEnv(&g_CurrentBuffer->draw);
    PutDispEnv(&g_CurrentBuffer->disp);
    FntFlush(-1);
}

void DebugInputWait(const char* msg) {
    while (PadRead(0))
        DebugShowWaitInfo(msg);
    while (!PadRead(0))
        DebugShowWaitInfo(msg);
}

// jumptable alignment suggests file split here

INCLUDE_ASM("weapon/nonmatchings/w_027", EntityWeaponAttack);

void func_ptr_80170004(Entity* self) {}

void func_ptr_80170008(Entity* self) {}

void func_ptr_8017000C(Entity* self) {}

void func_ptr_80170010(Entity* self) {}

s32 func_ptr_80170014(Entity* self) {}

int GetWeaponId(void) { return 27; }

void EntityWeaponShieldSpell(Entity* self) {
    Primitive* prim;
    s16 selfPosX;
    s16 selfPosY;

    switch (self->step) {
    case 0:
        self->primIndex = g_api.AllocPrimitives(PRIM_GT4, 1);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        SetSpriteBank1(D_C1000_8017A040);
        if (g_HandId != 0) {
            self->animSet = ANIMSET_OVL(0x12);
            self->palette = 0x128;
            self->ext.shield.childPalette = 0x137;
            self->unk5A = 0x66;
            self->ext.shield.unk7C = 0;
            self->ext.shield.unk7D = 0x80;
        } else {
            self->animSet = ANIMSET_OVL(0x10);
            self->palette = 0x110;
            self->ext.shield.childPalette = 0x11F;
            self->unk5A = 0x64;
            self->ext.shield.unk7C = 0x80;
            self->ext.shield.unk7D = 0;
        }
        self->flags = FLAG_UNK_04000000 | FLAG_HAS_PRIMS | FLAG_UNK_10000;
        prim = &g_PrimBuf[self->primIndex];
        self->posY.i.hi -= 8;
        self->zPriority = 0x1B6;
        self->facingLeft = PLAYER.facingLeft;
        self->animCurFrame = 0x3E;
        self->drawFlags = FLAG_DRAW_ROTX | FLAG_DRAW_ROTY;
        self->rotX = self->rotY = 0;
        prim->clut = 0x19F;
        prim->tpage = 0x19;
        prim->u0 = prim->u2 = 0x80;
        prim->u1 = prim->u3 = 0x80 + 0x4F;
        prim->v0 = prim->v1 = self->ext.shield.unk7C; 
        prim->v2 = prim->v3 = self->ext.shield.unk7C + 0x4F;
        self->ext.shield.unk82 = 0;
        prim->r0 = prim->g0 = prim->b0 = prim->r1 = prim->g1 = prim->b1 = prim->r2 = prim->g2 = prim->b2 = prim->r3 = prim->g3 = prim->b3 = 0x80;
        prim->priority = 0x1B4;
        prim->drawMode = 0x75;
        SetSpeedX(FIX(-2));
        self->velocityY = 0;
        DestroyEntityWeapon(1);
        g_api.PlaySfx(0x641);
        g_unkGraphicsStruct.unk20 = 1;
        self->step++;
        break;
    case 1:
        DecelerateX(FIX(1.0 / 16));
        self->velocityY -= FIX(20.0 / 128);
        self->posX.val += self->velocityX;
        self->posY.val += self->velocityY;
        self->rotX += 12;
        self->rotY = self->rotX;
        self->ext.shield.unk82 = self->rotX * 40 / 256;
        if (self->rotX >= 0x100) {
            self->ext.shield.unk82 = 0x28;
            self->rotY = self->rotX = 0x100;
            self->ext.shield.unk80 = 8;
            self->unk4C = D_C1000_8017AC8C;
            self->animFrameDuration = 0;
            self->animFrameIdx = 0;
            self->flags |= FLAG_UNK_100000;
            self->step++;
        }
        break;
    case 2:
        if (--self->ext.shield.unk80 == 0) {
            self->unk4C = D_C1000_8017ACB4;
            self->animFrameDuration = 0;
            self->animFrameIdx = 0;
            self->step++;
        }
        break;
    case 3:
        prim = &g_PrimBuf[self->primIndex];
        self->ext.shield.unk82 += 8;
        if (prim->b3 > 8) {
            prim->b3 -= 4;
        }
        prim->r0 = prim->g0 = prim->b0 = prim->r1 = prim->g1 = prim->b1 = prim->r2 = prim->g2 = prim->b2 = prim->r3 = prim->g3 = prim->b3;
        if (self->ext.shield.unk82 >= 160) {
            prim->b3 = 6;
            prim = &g_PrimBuf[self->primIndex];
            prim->drawMode |= 8;
            self->ext.shield.unk80 = 4;
            //Blueprint 98 has child 9, which makes func_ptr_80170024.
            g_api.CreateEntFactoryFromEntity(self, ((g_HandId + 1) << 0xE) | 98, 0);
            self->ext.shield.unk80 = 80;
            g_unkGraphicsStruct.unk20 = 0;
            self->step++;
        }
        break;
    case 4:
        if (self->ext.shield.unk80 == 64) {
            self->unk4C = D_C1000_8017AC8C;
            self->animFrameDuration = 0;
            self->animFrameIdx = 0;
        }
        if (--self->ext.shield.unk80 == 0) {
            self->step++;
        }
        break;
    case 5:
        self->rotX -= 12;
        self->rotY = self->rotX;
        if (self->rotX < 0) {
            DestroyEntity(self);
            return;
        }
        break;
    }
    prim = &g_PrimBuf[self->primIndex];
    selfPosX = self->posX.i.hi;
    selfPosY = self->posY.i.hi;
    if (prim->b3 > 8) {
        if (g_Timer & 1) {
            prim->drawMode |= DRAW_HIDE;
        } else {
            prim->drawMode &= ~DRAW_HIDE;
        }
    }    
    prim->x0 = prim->x2 = selfPosX - self->ext.shield.unk82;    
    prim->x1 = prim->x3 = selfPosX + self->ext.shield.unk82 - 1;
    prim->y0 = prim->y1 = selfPosY - self->ext.shield.unk82;
    prim->y2 = prim->y3 = selfPosY + self->ext.shield.unk82 - 1;
    return;
}

INCLUDE_ASM("weapon/nonmatchings/w_027", func_ptr_80170024);

void func_ptr_80170028(Entity* self) {
    Entity* parent = self->ext.generic.unk8C.entityPtr;
    if (parent->entityId == 0) {
        DestroyEntity(self);
        return;
    }

    if (self->step == 0) {
        self->ext.weapon.equipId = parent->ext.weapon.equipId;
        SetWeaponProperties(self, 0);
        self->hitboxHeight = 6;
        self->hitboxWidth = 6;
        self->ext.generic.unk80.modeS16.unk0 = 6;
        self->step++;
    } else if (--self->ext.generic.unk80.modeS16.unk0 == 0) {
        DestroyEntity(self);
    }

    if (self->hitFlags != 0) {
        if (++self->ext.generic.unkA2 >= 6) {
            self->ext.generic.unk8C.entityPtr->ext.weapon.unk90 = 0;
        }
        self->hitFlags = 0;
    }
}

void WeaponUnused2C(void) {}

void WeaponUnused30(void) {}

void WeaponUnused34(void) {}

void WeaponUnused38(void) {}

void WeaponUnused3C(void) {}
