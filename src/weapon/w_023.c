// Weapon ID #23. Used by weapons:
// Herald shield, Unknown#207
#include "weapon_private.h"
#include "shared.h"

extern SpriteParts D_A5000_8017A040[];
extern s8 D_A5000_8017AAD8;
extern AnimationFrame* D_A5000_8017AB20;

extern u8 D_A5000_8017ABB0[];
extern s32 D_A5000_8017AC50[];
extern SVECTOR* D_A5000_8017AC90[];
extern VECTOR D_A5000_8017ACD8;

void EntityWeaponAttack(Entity* self) {
    s32 anim1;
    s32 anim2;
    s32 attackButton;

    anim1 = 0;
    anim2 = 0;
    if (g_HandId) {
        attackButton = PAD_CIRCLE;
    } else {
        attackButton = PAD_SQUARE;
    }
    if (!(attackButton & g_Player.padPressed) && (self->step < 3)) {
        self->animFrameDuration = 0;
        self->animFrameIdx = 0;
        self->step = 3;
    }
    if (self->step != 4) {
        self->posX.val = PLAYER.posX.val;
        self->posY.val = PLAYER.posY.val;
        self->facingLeft = PLAYER.facingLeft;
    }
    if ((g_Player.unk0C & PLAYER_STATUS_UNK10000) && (self->step != 4)) {
        self->zPriority = PLAYER.zPriority + 2;
        self->step = 4;
        if (g_Player.pl_vram_flag & 1) {
            self->velocityX = PLAYER.velocityX;
        } else {
            self->velocityX = PLAYER.velocityX * 2;
        }
        self->velocityY = FIX(-3.5);
        self->ext.timer.t = 0x80;
        self->flags = FLAG_UNK_08000000;
        self->animCurFrame = 0x3E;
    }
    if ((PLAYER.step == Player_Crouch) && (PLAYER.step_s != 2)) {
        anim2++;
    }
    if (self->step == 1 || self->step == 2) {
        if (self->ext.shield.unk84 == 0) {
            if (self->hitFlags == 3) {
                g_api.AddHearts(1);
                self->hitFlags = 0;
                self->ext.shield.unk84 = 0x20;
            }
        }
    }
    if (self->ext.shield.unk84 != 0) {
        self->ext.shield.unk84--;
    }
    switch (self->step) {
    case 0:
        SetSpriteBank1(D_A5000_8017A040);
        if (g_HandId != 0) {
            self->animSet = ANIMSET_OVL(0x12);
            self->palette = 0x128;
            self->unk5A = 0x66;
        } else {
            self->animSet = ANIMSET_OVL(0x10);
            self->palette = 0x110;
            self->unk5A = 0x64;
        }
        self->flags = FLAG_UNK_40000 | FLAG_UNK_20000;
        self->zPriority = PLAYER.zPriority - 2;
        g_Player.unk48 = 1;
        SetWeaponProperties(self, 0);
        self->step++;
        /* fallthrough */
    case 1:
        self->ext.shield.anim = anim2 + 10;
        if (self->animFrameDuration < 0) {
            self->step++;
        }
        break;
    case 2:
        switch (PLAYER.ext.player.anim) {
        case 9:
        case 10:
        case 11:
            anim1++;
            /* fallthrough */
        case 7:
            anim1++;
            /* fallthrough */
        case 8:
            anim1++;
            /* fallthrough */
        case 12:
            anim1++;
            /* fallthrough */
        case 13:
            anim1++;
            /* fallthrough */
        case 24:
        case 25:
            anim1++;
            /* fallthrough */
        case 14:
        case 15:
            anim1++;
            /* fallthrough */
        case 26:
            anim1 += 2;
            self->animFrameIdx = PLAYER.animFrameIdx;
            break;
        default:
            self->animFrameIdx = 0;
            anim1 += anim2;
            break;
        }
        self->ext.shield.anim = anim1;
        self->animFrameDuration = 2;
        break;
    case 3:
        g_Player.unk48 = 0;
        self->ext.shield.anim = anim2 + 12;
        if (self->animFrameDuration < 0) {
            DestroyEntity(self);
            return;
        }
        break;
    case 4:
        self->hitboxState = 0;
        g_Player.unk48 = 0;
        self->drawFlags |= FLAG_DRAW_ROTZ;
        self->posY.val += self->velocityY;
        self->posX.val += self->velocityX;
        self->velocityY += FIX(20.0 / 128);
        self->rotZ += 0x80;
        if (--self->ext.timer.t < 0x10) {
            self->drawFlags |= FLAG_DRAW_UNK80;
        }
        if (--self->ext.timer.t == 0) {
            DestroyEntity(self);
            return;
        }
        break;
    }
    if (self->step != 4) {
        g_api.PlayAnimation(&D_A5000_8017AAD8, &D_A5000_8017AB20);
    }
    self->drawFlags = PLAYER.drawFlags;
    self->rotY = PLAYER.rotY;
    self->rotPivotY = PLAYER.rotPivotY;
}

s32 func_ptr_80170004(Entity* self) {}

void func_ptr_80170008(Entity* self) {}

void func_ptr_8017000C(Entity* self) {}

s32 func_ptr_80170010(Entity* self) {}

s32 func_ptr_80170014(Entity* self) {}

int GetWeaponId(void) { return 23; }

INCLUDE_ASM("weapon/nonmatchings/w_023", EntityWeaponShieldSpell);

void func_ptr_80170024(Entity* self) {
    s32 unused1;
    s32 unusedFlag;
    SVECTOR rotation_axis;
    VECTOR transfer_vector;
    MATRIX m2;
    MATRIX m1;
    VECTOR rotTransOutput;

    Primitive* prim;
    s32 i;
    u16 clut;
    SVECTOR* arrayVec;
    SVECTOR** vecs;
    u16 uvOffset;
    s32 rotTransResult;

    if (g_HandId != 0) {
        clut = 0x12B;
        uvOffset = 0x80;
    } else {
        clut = 0x113;
        uvOffset = 0;
    }
    switch (self->step) {
    case 0:
        self->primIndex = g_api.AllocPrimitives(PRIM_GT4, 4);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags |= FLAG_UNK_04000000 | FLAG_HAS_PRIMS;
        self->ext.heraldSwirl.unk82 = 0;
        self->ext.timer.t = 0;
        self->ext.heraldSwirl.unk7E = 0;
        self->ext.heraldSwirl.unk9A = 0x140;
        self->posY.i.hi += 0x48;
        self->velocityY = FIX(-7.0 / 8);
        prim = &g_PrimBuf[self->primIndex];
        for (i = 0; prim != NULL; i++, prim = prim->next) {
            prim->tpage = 0x19;
            prim->clut = clut;
            prim->u0 = D_A5000_8017ABB0[i * 8];
            prim->v0 = D_A5000_8017ABB0[i * 8 + 1] + uvOffset;
            prim->u1 = D_A5000_8017ABB0[i * 8 + 2];
            prim->v1 = D_A5000_8017ABB0[i * 8 + 3] + uvOffset;
            prim->u2 = D_A5000_8017ABB0[i * 8 + 4];
            prim->v2 = D_A5000_8017ABB0[i * 8 + 5] + uvOffset;
            prim->u3 = D_A5000_8017ABB0[i * 8 + 6];
            prim->v3 = D_A5000_8017ABB0[i * 8 + 7] + uvOffset;
            prim->priority = 0;
            prim->drawMode =
                DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS | DRAW_TRANSP;
        }
        rotation_axis.vx = 0x80;
        rotation_axis.vy = 0;
        rotation_axis.vz = 0xC0;
        self->ext.heraldSwirl.unk9C = 0;
        RotMatrix(&rotation_axis, &m1);
        TransMatrix(&m1, &D_A5000_8017ACD8);
        SetRotMatrix(&m1);
        SetTransMatrix(&m1);
        for (i = 0; i < 16; i++) {
            RotTrans(D_A5000_8017AC50[i], &rotTransOutput, &unusedFlag);
            arrayVec = D_A5000_8017AC90[i];
            arrayVec->vx = rotTransOutput.vx;
            arrayVec->vy = rotTransOutput.vy - 0x18;
            arrayVec->vz = rotTransOutput.vz - D_A5000_8017ACD8.vz;
        }
        self->step++;
        break;

    case 1:
        if (self->posY.i.hi < 0x10) {
            DestroyEntity(self);
            return;
        }
        self->posY.val += self->velocityY;
        self->ext.heraldSwirl.unk9C += 10;
        if (self->ext.heraldSwirl.unk9C >= 0xF8) {
            self->ext.heraldSwirl.unk80 = 0x20;
            self->step++;
        }
        break;

    case 2:
        self->posY.val += self->velocityY;
        if (--self->ext.heraldSwirl.unk80 == 0) {
            self->step++;
        }
        break;
    case 3:
        self->posY.val += self->velocityY;
        self->ext.heraldSwirl.unk9C -= 10;
        if (self->ext.heraldSwirl.unk9C < 9) {
            DestroyEntity(self);
            return;
        }
        break;
    }
    self->ext.heraldSwirl.unk7E += 0x40;
    rotation_axis.vx = 0;
    rotation_axis.vy = self->ext.heraldSwirl.unk7E;
    rotation_axis.vz = 0;
    transfer_vector.vz = self->ext.heraldSwirl.unk9A;
    transfer_vector.vx = 0;
    transfer_vector.vy = 0;
    SetGeomScreen(0x200);
    SetGeomOffset(self->posX.i.hi, self->posY.i.hi);
    RotMatrix(&rotation_axis, &m2);
    TransMatrix(&m2, &transfer_vector);
    SetRotMatrix(&m2);
    SetTransMatrix(&m2);
    vecs = &D_A5000_8017AC90[0];
    prim = &g_PrimBuf[self->primIndex];
    for (i = 0; i < 4; i++, prim = prim->next, vecs += 4) {
        rotTransResult = RotTransPers4(
            vecs[0], vecs[1], vecs[2], vecs[3], &prim->x0, &prim->x1, &prim->x3,
            &prim->x2, &unused1, &unusedFlag);
        prim->drawMode |= 8;
        if (0 < rotTransResult && rotTransResult <= 0x1BE) {
            prim->r0 = prim->g0 = prim->b0 = prim->r1 = prim->g1 = prim->b1 =
                prim->r2 = prim->g2 = prim->b2 = prim->r3 = prim->g3 =
                    prim->b3 = self->ext.heraldSwirl.unk9C;
            prim->priority = 0x1BC;
            prim->drawMode &= ~DRAW_HIDE;
            prim->type = PRIM_GT4;
        }
    }
}

extern AnimationFrame D_A5000_8017AB58[];

void func_ptr_80170028(Entity* self) {

    switch (self->step) {
    case 0:
        self->palette = self->ext.weapon.parent->palette;
        self->unk5A = self->ext.weapon.parent->unk5A;
        self->unk4C = D_A5000_8017AB58;
        self->flags |= (FLAG_UNK_04000000 | FLAG_UNK_100000);
        self->drawFlags = FLAG_DRAW_ROTX | FLAG_DRAW_ROTY;

        self->rotX = self->rotY = 0;
        self->posY.i.hi += 40;
        self->velocityY = FIX(-1.5);
        self->ext.weapon.unk7E = 0;
        // Note: This is a weird use of the lifetime, it's not a lifetime! It's
        // just caching the initial X position.
        self->ext.weapon.lifetime = self->posX.i.hi;
        self->animFrameIdx = rand() % 5;
        self->animFrameDuration = 2;
        self->ext.weapon.unk7E = 0x400;
        self->ext.weapon.unk80 = (self->params & 0xFF) * 4;
        self->step++;
        return;
    case 1:
        // Actually, looks like it's using unk80 as the life timer.
        if (--self->ext.weapon.unk80 == 0) {
            self->animSet = self->ext.weapon.parent->animSet;
            self->ext.weapon.unk80 = 0x40;
            self->step++;
        }
        return;
    case 2:
        if (--self->ext.weapon.unk80 == 0) {
            DestroyEntity(self);
            return;
        }
        self->posY.val += self->velocityY;
        self->ext.weapon.unk7E = (self->ext.weapon.unk7E + 0x80) & 0xFFF;
        self->posX.i.hi = self->ext.weapon.lifetime +
                          ((rcos(self->ext.weapon.unk7E) * 2) >> 8);
        if (self->ext.weapon.unk7E < 0x800) {
            self->zPriority = 0x1B4;
        } else {
            self->zPriority = 0x1BC;
        }
        self->rotX = self->rotY = -(rsin(self->ext.weapon.unk7E) >> 5) + 0xC0;
        break;
    }
}
void WeaponUnused2C(void) {}

void WeaponUnused30(void) {}

void WeaponUnused34(void) {}

void WeaponUnused38(void) {}

void WeaponUnused3C(void) {}
