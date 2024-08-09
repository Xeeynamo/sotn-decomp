// Weapon ID #29. Used by weapons:
// Fire shield, Unknown#213
#include "weapon_private.h"
#include "shared.h"
#include "items.h"
#include "sfx.h"

extern s32 D_CF000_8017AC78;
extern s32 D_CF000_8017ACC0;
extern u16 D_CF000_8017ACF8[];
extern u16 D_CF000_8017AD04[];
extern u16 D_CF000_8017AD10[];

extern AnimationFrame D_CF000_8017AD24[];

typedef struct {
    f32 posX;
    f32 posY;
    s16 unk8;
    u16 unkA;
    s16 unkC;
    s16 unkE;
    s16 unk10;
    s16 spawnDelay;
    s16 unk14;
    s16 state;
} FireShieldDragon;
extern FireShieldDragon D_CF000_8017C9A0[][20];

void EntityWeaponAttack(Entity* self) {
    s32 anim;
    s32 handButton;
    s32 unkAC_offset;

    anim = 0;
    unkAC_offset = 0;
    if (g_HandId != 0) {
        handButton = PAD_CIRCLE;
    } else {
        handButton = PAD_SQUARE;
    }
    if (!(handButton & g_Player.padPressed) && (self->step < 3)) {
        self->animFrameDuration = 0;
        self->animFrameIdx = 0;
        self->step = 3;
    }
    if (self->step != 4) {
        self->posX.val = PLAYER.posX.val;
        self->posY.val = PLAYER.posY.val;
        self->facingLeft = PLAYER.facingLeft;
    }
    if ((g_Player.unk0C & 0x10000) && (self->step != 4)) {
        self->zPriority = PLAYER.zPriority + 2;
        self->step = 4;
        if (g_Player.pl_vram_flag & 1) {
            self->velocityX = PLAYER.velocityX;
        } else {
            self->velocityX = PLAYER.velocityX * 2;
        }
        self->velocityY = FIX(-3.5);
        self->ext.weapon.lifetime = 128;
        self->flags = FLAG_UNK_08000000;
        self->animCurFrame = 0x3E;
    }
    if ((PLAYER.step == 2) && (PLAYER.step_s != 2)) {
        unkAC_offset++;
    }
    switch (self->step) {
    case 0:
        SetSpriteBank1(g_Animset);
        if (self->params & ANIMSET_OVL_FLAG) {
            self->animSet = ANIMSET_OVL(18);
            self->ext.weapon.unk80 = 0x128;
            self->unk5A = 0x66;
        } else {
            self->animSet = ANIMSET_OVL(16);
            self->ext.weapon.unk80 = 0x110;
            self->unk5A = 0x64;
        }
        self->flags = FLAG_UNK_40000 + FLAG_UNK_20000;
        self->zPriority = PLAYER.zPriority - 2;
        g_Player.unk48 = 1;
        SetWeaponProperties(self, 0);
        self->step++;
    case 1:
        self->ext.weapon.anim = unkAC_offset + 10;
        if (self->animFrameDuration < 0) {
            self->step++;
        }
        break;
    case 2:
        switch (PLAYER.ext.player.anim) {
        case 9:
        case 10:
        case 11:
            anim++;
        case 7:
            anim++;
        case 8:
            anim++;
        case 12:
            anim++;
        case 13:
            anim++;
        case 24:
        case 25:
            anim++;
        case 14:
        case 15:
            anim++;
        case 26:
            anim += 2;
            self->animFrameIdx = PLAYER.animFrameIdx;
            break;
        default:
            self->animFrameIdx = 0;
            anim = anim + unkAC_offset;
            break;
        }
        self->ext.weapon.anim = anim;
        self->animFrameDuration = 2;
        break;
    case 3:
        g_Player.unk48 = 0;
        self->ext.weapon.anim = unkAC_offset + 12;
        if (self->animFrameDuration < 0) {
            DestroyEntity(self);
            return;
        }
        break;
    case 4:
        self->hitboxState = 0;
        g_Player.unk48 = 0;
        self->drawFlags |= 4;
        self->posY.val += self->velocityY;
        self->posX.val += self->velocityX;
        self->velocityY += FIX(20.0 / 128);
        self->rotZ = self->rotZ + 0x80;
        if (--self->ext.weapon.lifetime < 16) {
            self->drawFlags |= 0x80;
        }
        if (--self->ext.weapon.lifetime == 0) {
            DestroyEntity(self);
            return;
        }
        break;
    }
    if (self->step != 4) {
        g_api.PlayAnimation(&D_CF000_8017AC78, &D_CF000_8017ACC0);
        if (g_GameTimer % 5 == 0) {
            // Need to enable FACTORY() in weapon overlay
            // TODO: FACTORY()
            g_api.CreateEntFactoryFromEntity(
                self, ((g_HandId + 1) << 12) + 0x38, 0);
        }
    }
    self->palette =
        self->ext.weapon.unk80 + D_CF000_8017ACF8[g_GameTimer / 2 % 5];
    self->drawFlags = PLAYER.drawFlags;
    self->rotY = PLAYER.rotY;
    self->rotPivotY = PLAYER.rotPivotY;
    return;
}

s32 func_ptr_80170004(Entity* self) {
    if (self->ext.weapon.parent->ext.weapon.equipId != ITEM_FIRE_SHIELD) {
        DestroyEntity(self);
        return;
    }
    if (self->step == 0) {
        self->animSet = self->ext.weapon.parent->animSet;
        self->zPriority = self->ext.weapon.parent->zPriority + 4;
        self->unk5A = self->ext.weapon.parent->unk5A;
        self->ext.weapon.unk80 = self->ext.weapon.parent->ext.weapon.unk80;
        self->animCurFrame = self->ext.weapon.parent->animCurFrame;
        self->flags = 0x08000000;
        self->drawFlags = FLAG_DRAW_UNK8 | FLAG_DRAW_UNK10;
        self->unk6C = 0x80;
        self->ext.weapon.unk7E = 0x14;
        self->step++;
    } else {
        if (self->unk6C >= 7) {
            self->unk6C -= 7;
        }

        if (--self->ext.weapon.unk7E == 0) {
            DestroyEntity(self);
            return;
        }
    }
    self->palette =
        self->ext.weapon.unk80 + D_CF000_8017AD04[g_GameTimer / 2 % 5];
}

void func_ptr_80170008(Entity* self) {}

void func_ptr_8017000C(Entity* self) {}

s32 func_ptr_80170010(Entity* self) {}

s32 func_ptr_80170014(Entity* self) {}

int GetWeaponId(void) { return 29; }

void EntityWeaponShieldSpell(Entity* self) {
    Primitive* prim;
    s32 var_v0;
    u16 selfX;
    u16 selfY;

    switch (self->step) {
    case 0:
        self->primIndex = g_api.AllocPrimitives(PRIM_GT4, 1);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        SetSpriteBank1(g_Animset);
        if (g_HandId != 0) {
            self->animSet = -0x7FEE;
            self->ext.weapon.childPalette = 0x128;
            self->unk5A = 0x66;
            self->ext.shield.unk7C = 0;
            self->ext.shield.unk7D = 0x80;
        } else {
            self->animSet = -0x7FF0;
            self->ext.weapon.childPalette = 0x110;
            self->unk5A = 0x64;
            self->ext.shield.unk7C = 0x80;
            self->ext.shield.unk7D = 0;
        }
        self->posY.i.hi -= 8;
        self->flags = 0x04810000;
        self->zPriority = PLAYER.zPriority - 2;
        self->facingLeft = PLAYER.facingLeft;
        self->animCurFrame = 0x3E;
        self->drawFlags = FLAG_DRAW_ROTX | FLAG_DRAW_ROTY;
        self->rotY = 0;
        self->rotX = 0;
        prim = &g_PrimBuf[self->primIndex];
        prim->clut = 0x19F;
        prim->tpage = 0x19;
        prim->u0 = prim->u2 = 0x80;
        prim->u1 = prim->u3 = 0xCF;
        prim->v0 = prim->v1 = self->ext.shield.unk7C;
        prim->v2 = prim->v3 = self->ext.shield.unk7C + 0x4F;
        self->ext.weapon.unk82 = 0;
        prim->r0 = prim->g0 = prim->b0 = prim->r1 = prim->g1 = prim->b1 =
            prim->r2 = prim->g2 = prim->b2 = prim->r3 = prim->g3 = prim->b3 =
                0x80;
        prim->priority = self->zPriority - 4;
        prim->drawMode = 0x75;
        SetSpeedX(FIX(-2));
        self->velocityY = 0;
        DestroyEntityWeapon(1);
        g_api.PlaySfx(SFX_ANIME_SWORD_C);
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
        self->ext.weapon.unk82 = self->rotX * 40 / 256;

        if (self->rotX >= 0x100) {
            self->ext.weapon.unk82 = 0x28;
            self->rotX = 0x100;
            self->rotY = 0x100;
            self->ext.weapon.unk80 = 8;
            self->step++;
        }
        self->palette =
            self->ext.weapon.childPalette + D_CF000_8017ACF8[g_Timer / 2 % 5];
        break;
    case 2:
        if (--self->ext.weapon.unk80 == 0) {
            self->step++;
        }
        self->palette =
            self->ext.weapon.childPalette + D_CF000_8017ACF8[g_Timer / 2 % 5];
        break;
    case 3:
        self->palette = self->ext.weapon.childPalette +
                        D_CF000_8017ACF8[g_GameTimer / 2 % 5];
        self->rotX -= 0x10;
        self->rotY = self->rotX;
        if (self->rotX <= 0) {
            self->rotX = 0;
            self->unk4C = D_CF000_8017AD24;
            self->animFrameIdx = 0;
            self->animFrameDuration = 0;
            self->flags |= 0x100000;
            self->ext.weapon.unk80 = 0x20;
            self->palette = self->ext.weapon.childPalette;
            self->zPriority = 0x1B6;
            g_api.PlaySfx(SFX_TRANSFORM);
            self->step++;
        }
        break;
    case 4:
        self->ext.weapon.unk82 += 8;
        self->rotX += 0x10;
        if (self->rotX >= 0x100) {
            self->rotX = 0x100;
        }
        self->rotY = self->rotX;
        prim = &g_PrimBuf[self->primIndex];
        if (prim->b3 >= 9) {
            prim->b3 -= 4;
        }
        prim->r0 = prim->g0 = prim->b0 = prim->r1 = prim->g1 = prim->b1 =
            prim->r2 = prim->g2 = prim->b2 = prim->r3 = prim->g3 = prim->b3;
        if (--self->ext.weapon.unk80 == 0) {
            prim->drawMode |= 8;
            g_api.PlaySfx(0x660);
            // TODO: FACTORY()
            g_api.CreateEntFactoryFromEntity(
                self, ((g_HandId + 1) << 14) + 102, 0);
            self->ext.weapon.unk80 = 0x18;
            g_unkGraphicsStruct.unk20 = 0;
            self->step++;
        }
        break;
    case 5:
        if (--self->ext.weapon.unk80 == 0) {
            self->step++;
        }
        break;
    case 6:
        self->rotX -= 0x10;
        self->rotY = self->rotX;
        if (self->rotX <= 0) {
            DestroyEntity(self);
            return;
        }
        break;
    }
    selfX = self->posX.i.hi;
    selfY = self->posY.i.hi;
    prim = &g_PrimBuf[self->primIndex];
    prim->x0 = prim->x2 = selfX - self->ext.weapon.unk82;
    prim->x1 = prim->x3 = (selfX + self->ext.weapon.unk82) - 1;
    prim->y0 = prim->y1 = selfY - self->ext.weapon.unk82;
    prim->y2 = prim->y3 = (selfY + self->ext.weapon.unk82) - 1;
    return;
}

void func_ptr_80170024(Entity* self) {
    // All these variables are kind of guessing names, behavior of this
    // function is a little unclear.
    Primitive* firstPrim;
    s16 prev_x2;
    s16 prev_y2;
    s16 dragonNumber;
    Primitive* prim;
    s16 angle1;
    s16 temp_s1;
    s16 angle2;
    s32 centerX;
    s32 nextX;
    s32 centerY;
    s32 nextY;
    s16 prev_x3;
    s16 prev_x4;
    s32 unkCosine;
    s32 unkSine;
    s16 size;
    s32 i;
    s16 facingLeft;
    s16 nextX_copy;
    s16 nextY_copy;

    FireShieldDragon* var_s7;

    dragonNumber = (u8)self->params;
    facingLeft = self->facingLeft;
    switch (self->step) {
    case 0:
        self->primIndex = g_api.AllocPrimitives(PRIM_GT4, 0x13);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        if (g_HandId != 0) {
            self->ext.weapon.childPalette = 0x128;
            self->ext.shield.unk7D = 0x80;
        } else {
            self->ext.weapon.childPalette = 0x110;
            self->ext.shield.unk7D = 0;
        }
        self->flags |= 0x04800000;
        self->ext.shield.unk9C = 0x40;

        for (i = 0, prim = &g_PrimBuf[self->primIndex]; prim != NULL; i++,
            prim = prim->next) {
            prim->tpage = 0x19;
            prim->clut = self->ext.weapon.childPalette;
            prim->priority = 0x1BC;
            prim->drawMode = DRAW_DEFAULT;
            prim->u0 = prim->u2 = 0x50;
            prim->v0 = prim->v1 = self->ext.shield.unk7D + 8;
            prim->u1 = prim->u3 = 0x7F;
            prim->v2 = prim->v3 = self->ext.shield.unk7D + 0x2F;
            if (i == 0) { // for the first prim. Maybe this is the dragon head
                          // or something?
                prim->u0 = prim->u1 = 0;
                prim->u2 = prim->u3 = 0x57;
                prim->v0 = prim->v2 = self->ext.shield.unk7D + 0x30;
                prim->v1 = prim->v3 = self->ext.shield.unk7D + 0x6F;
            }
            prim->priority = 0x1BA;
        }
        var_s7 = &D_CF000_8017C9A0[dragonNumber][0];
        for (i = 0; i < 20; i++) {
            var_s7->unk8 = 0;
            if (facingLeft) {
                var_s7->unk8 = 0x800;
            }
            var_s7->unk8 += (dragonNumber * 0x540);
            var_s7->unkA = 0xC00;
            var_s7->posX.val = self->posX.val;
            var_s7->posY.val = self->posY.val;
            var_s7->unkC = 0x70;
            var_s7->unk10 = 20;
            if (i == 19) {
                var_s7->unk10 = 0;
            }
            if (i == 18) {
                var_s7->unk10 = 10;
            }
            var_s7->spawnDelay = i * 2 + 1;
            var_s7->unkE = 0xC00;
            var_s7->unk14 = 256;
            var_s7->state = 0;
            var_s7++;
        }
        self->ext.weapon.equipId = self->ext.weapon.parent->ext.weapon.equipId;
        SetWeaponProperties(self, 0);
        self->hitboxHeight = 20;
        self->hitboxWidth = 20;
        self->step += 1;
        break;
    case 1:
        var_s7 = &D_CF000_8017C9A0[dragonNumber][0];
        for (i = 0; i < 20; var_s7++, i++) {
            if (var_s7->state != 0) {
                var_s7->unkE += 0x80;
                var_s7->unk14 -= 4;
                temp_s1 = rsin(var_s7->unkE) / 2 + 0x1000;
                if (var_s7->unk14 < 0) {
                    var_s7->unk14 = 0;
                }
                unkCosine =
                    ((rcos(var_s7->unk8) * var_s7->unkC) >> 0xC) * temp_s1;
                unkSine =
                    -((rsin(var_s7->unk8) * var_s7->unkC) >> 0xC) * temp_s1;
                var_s7->posX.val += unkCosine;
                var_s7->posY.val += unkSine;
                if (!facingLeft) {
                    var_s7->unk8 += ((s16)var_s7->unkA >> 4);
                } else {
                    var_s7->unk8 -= ((s16)var_s7->unkA >> 4);
                }
            }
            switch (var_s7->state) {
            case 0:
                if (--var_s7->spawnDelay == 0) {
                    var_s7->state++;
                }
                break;
            case 1:
                var_s7->unkA -= 40;
                if (var_s7->unkE > 0x1400) {
                    var_s7->state++;
                }
                break;
            case 2:
                var_s7->unkA -= 80;
                var_s7->unkC -= 4;
                if (var_s7->unkC < 0x40) {
                    if (!(self->params & 0x7F)) {
                        g_api.PlaySfx(0x660);
                    }
                    var_s7->state++;
                }
                break;
            case 3:
                var_s7->unkE -= 0x60;
                var_s7->unkA -= 48;

                if ((var_s7->posX.val < FIX(-288) ||
                     var_s7->posX.val > FIX(288)) ||
                    (var_s7->posY.val < FIX(0) ||
                     var_s7->posY.val > FIX(256))) {
                    var_s7->unkA = 0;
                }
                var_s7->unkC += 2;
                if (var_s7->unkC > 0x100) {
                    DestroyEntity(self);
                    return;
                }
                break;
            }
        }
        self->ext.shield.unk9C += 2;
        if (self->ext.shield.unk9C > 0x100) {
            self->ext.shield.unk9C = 0x100;
        }
    }
    firstPrim = prim = &g_PrimBuf[self->primIndex];
    var_s7 = &D_CF000_8017C9A0[dragonNumber][0];
    for (i = 0; i < 19; i++, prim = prim->next) {
        prim->clut =
            self->ext.weapon.childPalette + D_CF000_8017AD10[g_Timer / 2 % 10];
        prim->x0 = prev_x2;
        prim->y0 = prev_y2;
        prim->x1 = prev_x3;
        prim->y1 = prev_x4;
        var_s7++;
        size = var_s7->unk10 *
               (rsin(var_s7->unkE) * var_s7->unk14 / 256 + 4096) / 4096;
        centerX = var_s7->posX.i.hi;
        centerY = var_s7->posY.i.hi;
        angle1 = var_s7->unk8 - 0x400;
        angle2 = var_s7->unk8 + 0x400;
        prev_x2 = prim->x2 = centerX + (((rcos(angle1) >> 4) * size) >> 8);
        prev_y2 = prim->y2 = centerY - (((rsin(angle1) >> 4) * size) >> 8);
        prim->x3 = prev_x3 = centerX + (((rcos(angle2) >> 4) * size) >> 8);
        prim->y3 = prev_x4 = centerY - (((rsin(angle2) >> 4) * size) >> 8);
    }

    var_s7 = &D_CF000_8017C9A0[dragonNumber][0];
    size = ((self->ext.shield.unk9C * 54 / 256) *
            (rsin(var_s7->unkE) * var_s7->unk14 / 256 + 4096)) /
           4096;
    nextX = (var_s7 + 1)->posX.i.hi;
    nextX_copy = nextX;
    nextY = (var_s7 + 1)->posY.i.hi;
    nextY_copy = nextY;
    angle1 = var_s7->unk8 - 0x199;
    angle2 = var_s7->unk8 + 0x199;
    firstPrim->x0 = nextX + (((rcos(angle1) >> 4) * size) >> 8);
    firstPrim->y0 = nextY - (((rsin(angle1) >> 4) * size) >> 8);
    firstPrim->x1 = nextX + (((rcos(angle2) >> 4) * size) >> 8);
    firstPrim->y1 = nextY - (((rsin(angle2) >> 4) * size) >> 8);
    angle1 = var_s7->unk8 + 0x999;
    angle2 = var_s7->unk8 + 0x667;
    firstPrim->x2 = nextX + (((rcos(angle1) >> 4) * size) >> 8);
    firstPrim->y2 = nextY - (((rsin(angle1) >> 4) * size) >> 8);
    firstPrim->x3 = nextX + (((rcos(angle2) >> 4) * size) >> 8);
    firstPrim->y3 = nextY - (((rsin(angle2) >> 4) * size) >> 8);
    self->posX.i.hi = nextX_copy;
    self->posY.i.hi = nextY_copy;
    // TODO: FACTORY()
    g_api.CreateEntFactoryFromEntity(self, ((g_HandId + 1) << 14) + 100, 0);
}

void func_ptr_80170028(Entity* self) {
    if (self->ext.weapon.parent->entityId == 0) {
        DestroyEntity(self);
        return;
    }
    if (self->step == 0) {
        self->ext.weapon.equipId = self->ext.weapon.parent->ext.weapon.equipId;
        SetWeaponProperties(self, 0);
        self->hitboxHeight = 14;
        self->hitboxWidth = 14;
        self->ext.weapon.unk80 = 10;
        self->step++;
        return;
    }
    if (--self->ext.weapon.unk80 == 0) {
        DestroyEntity(self);
    }
}

void WeaponUnused2C(void) {}

void WeaponUnused30(void) {}

void WeaponUnused34(void) {}

void WeaponUnused38(void) {}

void WeaponUnused3C(void) {}
