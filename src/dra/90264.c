#include "dra.h"
#include "objects.h"
#include "sfx.h"

s16 D_800B0A3C[] = {1, 2, 1, 0, 1, 2, 1, 0};
s16 D_800B0A4C[] = {0, 1, 2, 3, 4, 3, 2, 1};

static s16 D_800B0A5C[] = {0, 1, 0, -1, 0, 1, 0, -1};
static s16 D_800B0A6C[] = {0, 1, 2, 3, 4, 3, 2, 1};
static s16 D_800B0A7C[] = {0, 0, 1, 1, 2, 2, 3, 3};
void func_80130264(Entity* self) {
    s32 var_v1;

    if (!(g_Player.unk0C & PLAYER_STATUS_WOLF_FORM)) {
        DestroyEntity(self);
        return;
    }
    if (self->step == 0) {
        self->animSet = ANIMSET_DRA(15);
        self->animCurFrame = 1;
        self->unk5A = 0x7E;
        self->palette = PLAYER.palette;
#if defined(VERSION_HD)
        self->zPriority = PLAYER.zPriority;
#endif
        self->flags = FLAG_UNK_04000000 | FLAG_UNK_20000 | FLAG_UNK_40000;
        self->drawFlags = DRAW_COLORS;
        self->rotPivotX = 0;
        self->rotPivotY = 9;
        LOH(self->hitboxOffX) = -4;
        self->hitboxOffY = 10;
        self->hitboxWidth = 20;
        self->hitboxHeight = 6;
        self->step++;
    }
#if !defined(VERSION_HD)
    self->zPriority = PLAYER.zPriority;
#endif
    self->facingLeft = PLAYER.facingLeft;
    self->posX.val = g_Entities->posX.val;
    self->posY.val = PLAYER.posY.val;
    self->rotZ = 0x800 - D_80138430;

    switch (PLAYER.step_s) {
    case 1:
        if (D_800B0914 == 1) {
            self->rotZ -= 0x180;
        }
        break;
    case 2:
        switch (D_800B0914) {
        case 0:
            if (PLAYER.animCurFrame == 33) {
                self->animCurFrame = 31;
            }
            if (PLAYER.animCurFrame == 34) {
                self->animCurFrame = 32;
            }
            break;
        case 1:
        case 3:
            var_v1 = D_800B0A5C[PLAYER.animFrameIdx];
            self->posY.i.hi += var_v1;
            self->rotZ -= var_v1 << 5;
            break;
        case 2:
            var_v1 = D_800B0A6C[PLAYER.animFrameIdx];
            self->posY.i.hi += var_v1;
            self->rotZ -= var_v1 << 5;
            break;
        case 4:
            var_v1 = D_800B0A7C[PLAYER.animFrameIdx];
            self->posY.i.hi += var_v1;
            break;
        }
        if (g_Player.pl_vram_flag & 0x8000) {
            self->posY.i.hi += 2;
        }
        break;
    case 3:
        if (PLAYER.animCurFrame == 18) {
            self->posY.i.hi += 4;
        }
        if (PLAYER.animCurFrame == 19) {
            self->posY.i.hi += 8;
        }
        if (PLAYER.animCurFrame == 20) {
            self->posY.i.hi += 8;
        }
        break;
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
        break;
    }
    if (D_80138430 == 0xA00) {
        self->posY.i.hi += 2;
    }
    self->palette = PLAYER.palette;
    self->hitboxState = 0;
    if (abs(PLAYER.velocityX) > FIX(3) &&
        (PLAYER.step_s != 2 || D_800B0914 != 4)) {
        func_8011A328(self, 13);
        self->enemyId = 3;
        if (self->hitFlags && !CastSpell(13)) {
            D_800B0914 = 3;
            PLAYER.ext.player.anim = 0xE0;
            D_800B091C = 0x18;
        }
    }
    self->hitFlags = 0;
}
static const u32 rodata_func_80130264_padding = 0;

static s16 D_800B0A8C[] = {0, 1, 0, -1, 0, 1, 0, -1};
static s16 D_800B0A9C[] = {0, 1, 1, 0, 0, 1, 1, 0};
static s16 D_800B0AAC[] = {0, 0, 0, 1, 1, 1, 2, 2};
void func_80130618(Entity* self) {
    s32 var_v1;

    if (!(g_Player.unk0C & PLAYER_STATUS_WOLF_FORM)) {
        DestroyEntity(self);
        return;
    }

    if (self->step == 0) {
        self->animSet = 0xF;
        self->animCurFrame = 0x23;
        self->unk5A = 0x7E;
        self->palette = PLAYER.palette;
#if defined(VERSION_HD)
        self->zPriority = PLAYER.zPriority - 2;
#endif
        self->flags = FLAG_UNK_04000000 | FLAG_UNK_20000 | FLAG_UNK_40000;
        self->drawFlags = DRAW_COLORS;
        self->rotPivotX = 1;
        self->rotPivotY = 8;
        self->step++;
    }
#if !defined(VERSION_HD)
    self->zPriority = PLAYER.zPriority - 2;
#endif
    self->facingLeft = PLAYER.facingLeft;
    self->posX.val = g_Entities[UNK_ENTITY_11].posX.val;
    self->posY.val = g_Entities[UNK_ENTITY_11].posY.val;
    self->rotZ = -((D_80138430 - 0x800) / 2);

    switch (PLAYER.step_s) {
    case 1:
        if (D_800B0914 == 1) {
            self->rotZ -= 0x100;
            self->posY.i.hi += 8;
        }
        if (D_80138430 < 0x601) {
            self->posY.i.hi += 2;
        }
        break;
    case 2:
        switch (D_800B0914) {
        case 0:
            if (PLAYER.animCurFrame == 33) {
                self->animCurFrame = 65;
            }
            if (PLAYER.animCurFrame == 34) {
                self->animCurFrame = 66;
            }
            break;
        case 1:
        case 3:
            var_v1 = D_800B0A8C[PLAYER.animFrameIdx];
            self->posY.i.hi += var_v1;
            break;
        case 2:
            var_v1 = D_800B0A9C[PLAYER.animFrameIdx];
            self->posY.i.hi += var_v1;
            break;
        case 4:
            var_v1 = D_800B0AAC[PLAYER.animFrameIdx];
            self->posY.i.hi += var_v1;
            break;
        }
        if (D_80138430 < 0x701) {
            self->posY.i.hi += 1;
        }
        if (D_80138430 < 0x601) {
            self->posY.i.hi += 2;
        }
        break;
    case 3:
        if (PLAYER.animCurFrame == 0x12) {
            self->posY.i.hi += 4;
        }
        if (PLAYER.animCurFrame == 0x13) {
            self->posY.i.hi += 8;
        }
        if (PLAYER.animCurFrame == 0x14) {
            self->posY.i.hi += 8;
        }
        if (D_80138430 <= 0x600) {
            self->posY.i.hi += 2;
        }
        break;
    case 4:
        if (D_800B0914 == 0) {
            self->posY.i.hi += 1;
            self->rotZ -= 0x180;
        }
        break;
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
        break;
    }
    self->palette = PLAYER.palette;
    self->drawMode = 0;
    self->drawFlags &= ~DRAW_HIDE;
    if (abs(PLAYER.velocityX) > FIX(3)) {
        self->drawFlags |= DRAW_HIDE;
        self->drawMode = FLAG_DRAW_UNK10 | FLAG_DRAW_UNK20 | FLAG_DRAW_UNK40;
        self->unk6C = ~MIN((abs(PLAYER.velocityX) - FIX(3)) >> 12, 160);
    }
}
static const u32 rodata_func_80130618_padding = 0;

static AnimationFrame D_800B0ABC[] = {
    {0x0002, 0x0048}, {0x0004, 0x004B}, {0x0010, 0x004C},
    {0x0004, 0x004B}, {0x0008, 0x0048}, {0xFFFF, 0x0000},
};
static s32 D_800B0AD4[] = {0, 1, 2, 1, 0, 0};
static s32 D_800B0AEC[] = {0, 1, 1, 2, 2, 1, 1, 0};
extern s32 D_80138448;

void func_801309B4(Entity* self) {
    s32 var_s2;
    s32 var_a1;
    s32 var_s0;
    s32 var_s0_2;
    s32 var_v0;
    s32 var_v0_2;

    if (!(g_Player.unk0C & PLAYER_STATUS_WOLF_FORM)) {
        DestroyEntity(self);
        return;
    }
    if (self->step == 0) {
        self->animSet = ANIMSET_DRA(15);
        self->unk5A = 0x7E;
#if defined(VERSION_HD)
        self->zPriority = PLAYER.zPriority + 2;
#endif
        self->flags = FLAG_UNK_04000000 | FLAG_UNK_100000 | FLAG_UNK_20000 |
                      FLAG_UNK_40000;
        self->animFrameDuration = 1;
        self->animFrameIdx = 4;
        self->unk4C = D_800B0ABC;
        self->hitboxWidth = 10;
        self->hitboxHeight = 8;
        self->animCurFrame = 72;
        self->step++;
    }
#if !defined(VERSION_HD)
    self->zPriority = PLAYER.zPriority + 2;
#endif
    self->facingLeft = PLAYER.facingLeft;
    self->posX.val = g_Entities[UNK_ENTITY_12].posX.val;
    self->posY.val = g_Entities[UNK_ENTITY_12].posY.val + FIX(4);
    self->flags =
        FLAG_UNK_04000000 | FLAG_UNK_100000 | FLAG_UNK_20000 | FLAG_UNK_40000;

    var_a1 = D_80138430 - 0x800;
    if (D_80138430 > 0x980) {
        var_a1 = 0x180;
    }
    if (D_80138430 < 0x680) {
        var_a1 = -0x180;
    }
    self->palette = PLAYER.palette;
    var_s2 = 11;
    var_s0 = var_a1;
    switch (PLAYER.step_s) {
    case 1:
        var_s0 = var_a1;
        if (D_800B0914 == 1) {
            var_s0 += 0x100;
        }
        break;
    case 2:
        switch (D_800B0914) {
        case 0:
            if (PLAYER.animCurFrame == 33) {
                var_s0 = !PLAYER.facingLeft;
                self->posX.i.hi =
                    var_s0 ? self->posX.i.hi + 4 : self->posX.i.hi - 4;
                self->animCurFrame = 73;
                self->flags &= ~FLAG_UNK_100000;
                return;
            }
            if (PLAYER.animCurFrame == 34) {
                self->animCurFrame = 74;
                self->flags &= ~FLAG_UNK_100000;
                return;
            }
            break;
        case 1:
            break;
        case 2:
            var_s2 += D_800B0AEC[PLAYER.animFrameIdx];
            var_s0 -= 0x80;
            if (D_80138430 == 0xA00) {
                var_s0 += 0x80;
            }
            if (D_80138430 == 0x600) {
                var_s0 += 0x80;
            }
            break;
        }
        break;
    case 3:
        var_s0 -= 0x100;
        if (var_s0 < -0x180) {
            var_s0 = -0x180;
            break;
        }
        break;
    case 4:
        if (D_800B0914 == 2) {
            var_s0 -= 0x40;
        }
        break;
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
        break;
    }

    var_s2 = var_s2 - (var_s0 >> 7);
    if (PLAYER.facingLeft) {
        var_s0 = 0x800 - var_s0;
    }
    self->posX.i.hi += ((rcos(var_s0) >> 4) * var_s2) >> 8;
    self->posY.i.hi -= ((rsin(var_s0) >> 4) * var_s2) >> 8;
    if (PLAYER.step_s != 8 && PLAYER.step_s != 0 && D_80138444 != 0 &&
        self->animFrameDuration == -1) {
        PlaySfx(0x6F7);
        self->animFrameDuration = 0;
        self->animFrameIdx = 0;
    }
    var_s2 = D_800B0AD4[self->animFrameIdx];
    if (PLAYER.facingLeft) {
        var_s2 = -var_s2;
    }
    self->posX.i.hi += var_s2;
    if (PLAYER.step_s == 2 && D_800B0914 == 4) {
        func_8011A328(self, 4);
        self->enemyId = 3;
    } else if (self->animCurFrame != 72 && self->animCurFrame != 73 &&
               self->animCurFrame != 74) {
        func_8011A328(self, 14);
        self->enemyId = 3;
    } else {
        self->hitboxState = 0;
    }
    if (self->animFrameDuration < 0) {
        if (D_80138448 != 0) {
            D_80138448 -= 1;
        } else if (*D_80097448 >= 0x19) {
            var_s0_2 = PLAYER.facingLeft ? -4 : 4;
            self->posX.i.hi = var_s0_2 + self->posX.i.hi;
            self->posY.i.hi += 2;
            CreateEntFactoryFromEntity(self, FACTORY(0xD00, 4), 0);
            D_80138448 = 0x40;
            self->posY.i.hi -= 2;
            self->posX.i.hi -= var_s0_2;
        }
    }
}
static const u32 rodata_func_801309B4_padding = 0;

static s16 D_800B0B0C[] = {87, 88, 89, 89, 90, 90, 89, 88, 87};
static s16 D_800B0B20[] = {
    0x000, 0x040, 0x080, 0x0C0, 0x100, 0x140, 0x180, 0x1C0, 0x200};
extern s32 D_8013844C;
extern s32 D_80138450;

void func_80130E94(Entity* self) {
    s32 temp_v1;
    s32 var_s1;
    s32 var_s2;
    s32 var_s3;
    s32 var_s4;
    u16 params;
    s32 var_s6;
    s32 var_s7;

    if (!(g_Player.unk0C & PLAYER_STATUS_WOLF_FORM)) {
        DestroyEntity(self);
        return;
    }
    params = self->params;
    var_s1 = 0;
    var_s2 = 0;
    if (self->step == 0) {
        self->animSet = 15;
        self->animCurFrame = D_800B0B0C[params];
        self->unk5A = 0x7E;
        D_8013844C = 0;
        self->palette = PLAYER.palette;
#if defined(VERSION_HD)
        self->zPriority = PLAYER.zPriority - 3;
#endif
        self->flags = FLAG_UNK_04000000 | FLAG_UNK_20000 | FLAG_UNK_40000;
        self->ext.timer.t = 0x20;
        self->rotZ = D_80138430;
        self->step++;
    }
    self->facingLeft = PLAYER.facingLeft;
#if !defined(VERSION_HD)
    self->zPriority = PLAYER.zPriority - 3;
#endif
    var_s6 = 2;
    if (params == 0) {
        var_s4 = g_Entities[19].posX.val;
        var_s4 += PLAYER.facingLeft ? FIX(3) : -FIX(3);
        var_s7 = g_Entities[19].posY.val + FIX(7);
    } else {
        var_s4 = self[-1].posX.val;
        var_s7 = self[-1].posY.val;
    }
    if (PLAYER.animCurFrame == 33) {
        var_s6 = 1;
    }
    if (PLAYER.animCurFrame == 34) {
        var_s6 = 0;
    }
    if (params == 0) {
        var_s3 = D_8013844C;
        switch (PLAYER.step_s) {
        case 1:
            var_s2 = 0x100;
            var_s1 = 0x80;
            D_8013844C += 0x18;
            if (D_800B0914 == 1) {
                var_s1 = -0x80;
            }
            break;
        case 2:
            switch (D_800B0914) {
            case 0:
                var_s1 = -0x300;
                break;
            case 1:
            case 3:
                var_s2 = 0x40;
                var_s1 = -0x200;
                D_8013844C += 0x100;
                break;
            case 2:
                var_s2 = 0x40;
                D_8013844C += 0x100;
                var_s1 =
                    MIN((abs(PLAYER.velocityX) + -FIX(3)) >> 10, 0x100) - 0x100;
                break;
            }
            break;
        case 3:
            var_s2 = 0x40;
            var_s1 = 0x80;
            D_8013844C += 0x10;
            break;
        case 4:
            if (D_800B0914 == 0) {
                var_s1 = -0x200;
                if (PLAYER.velocityY < 0) {
                    var_s1 = 0x600;
                }
            } else {
                var_s2 = 0x20;
                var_s1 = -0x100;
                if (PLAYER.velocityY < 0) {
                    var_s1 = 0x100;
                }
            }
            break;
        case 7:
            var_s1 = -0x80;
            break;
        case 5:
        case 6:
        case 8:
            var_s1 = -0x200;
            break;
        case 9:
            var_s2 = 0x100;
            var_s1 = 0x80;
            D_8013844C += 0x18;
            break;
        }
        D_80138450 =
            var_s1 + D_80138430 + (((rsin(var_s3) >> 8) * var_s2) >> 4);
    }
    temp_v1 = (D_80138450 - D_80138430) * D_800B0B20[params] / 256 + D_80138430;
    if (temp_v1 < self->rotZ) {
        self->rotZ -= self->ext.timer.t;
    }
    if (self->rotZ < temp_v1) {
        self->rotZ += self->ext.timer.t;
    }
    if (PLAYER.facingLeft == 0) {
        var_s3 = self->rotZ;
    } else {
        var_s3 = 0x800 - self->rotZ;
    }
    self->posX.val = var_s4 + rcos(var_s3) * var_s6 * 0x10;
    self->posY.val = var_s7 - rsin(var_s3) * var_s6 * 0x10;
    self->palette = PLAYER.palette;
    self->drawMode = 0;
    self->drawFlags &= ~DRAW_HIDE;
    if (abs(PLAYER.velocityX) > FIX(3)) {
        self->drawFlags |= DRAW_HIDE;
        self->drawMode = FLAG_DRAW_UNK10 | FLAG_DRAW_UNK20 | FLAG_DRAW_UNK40;
        self->unk6C = ~MIN((abs(PLAYER.velocityX) - FIX(3)) >> 12, 128);
    }
}
// Entity #60. This is created manually at g_Entities[30].
// Creation is in func_8012E7A4.
void func_8013136C(Entity* self) {
    if (!(g_Player.unk0C & PLAYER_STATUS_WOLF_FORM)) {
        DestroyEntity(self);
        return;
    }
    if (!self->step) {
        self->animSet = 0xF;
        self->unk5A = 0x7E;
        self->palette = PLAYER.palette;
        self->flags = FLAG_UNK_04000000 | FLAG_UNK_20000 | FLAG_UNK_40000;
        self->drawFlags = DRAW_COLORS;
        self->rotPivotX = -8;
        self->step++;
    }
    self->animCurFrame = 80;
    self->facingLeft = PLAYER.facingLeft;
    self->posX.val = g_Entities[UNK_ENTITY_13].posX.val;
    self->posY.val = g_Entities[UNK_ENTITY_13].posY.val;
    if (!PLAYER.facingLeft) {
        self->zPriority = PLAYER.zPriority - 5;
        self->posX.i.hi += 8;
    } else {
        self->zPriority = PLAYER.zPriority + 5;
        self->posX.i.hi -= 8;
    }
    self->posY.i.hi += 3;
    self->rotZ = g_Entities[UNK_ENTITY_12].rotZ;
    switch (PLAYER.step_s) {
    case 1:
        if (D_800B0914 == 1) {
            self->posY.i.hi -= 2;
            if (!PLAYER.facingLeft) {
                self->posX.i.hi -= 8;
            } else {
                self->posX.i.hi += 8;
            }
        }
        break;
    case 2:
        switch (D_800B0914) {
        case 0:
            if (PLAYER.animCurFrame == 33) {
                self->animCurFrame = 81;
                if (!PLAYER.facingLeft) {
                    self->posX.i.hi += 3;
                } else {
                    self->posX.i.hi += 6;
                }
            }
            if (PLAYER.animCurFrame == 34) {
                if (!PLAYER.facingLeft) {
                    self->posX.i.hi += 3;
                } else {
                    self->posX.i.hi += 13;
                }
                self->animCurFrame = 82;
            }
            break;
        case 1:
            break;
        case 3:
        case 2:
        default:
            break;
        }
        break;
    case 3:
        break;
    case 4:
        D_800B0914 == 0;
        break;
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
        break;
    }
    self->palette = PLAYER.palette;
    func_8012C600();
}

// When Alucard uses the cross subweapon for 100 hearts.
// Entity ID 7, blueprint #7 (this is a coincidence)
void EntityGiantSpinningCross(Entity* self) {
    static const SVECTOR D_800E2024 = {0, 0, 0};
    static const SVECTOR D_800E202C = {0xFFA0, 0, 0};
    MATRIX m;
    SVECTOR rot;
    VECTOR trans1;
    SVECTOR pos;
    SVECTOR sp50;
    s32 z;
    s32 nclip;
    Primitive* prim;
    s32 i;
    u8* primUVCoords;
    SVECTOR* temp_a3;
    SVECTOR** vectors_ptr;
    u16 priority;

    pos = D_800E2024;
    sp50 = D_800E202C;

    if (self->step == 0) {
        self->primIndex = g_api.func_800EDB58(PRIM_GT4, 46);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        prim = &g_PrimBuf[self->primIndex];
        while (prim != NULL) {
            prim->tpage = 0x1C;
            prim->drawMode = 0x100 | DRAW_HIDE;
            prim = prim->next;
        }
        func_8011A290(self);
        self->hitboxHeight = 0x50;
        self->hitboxWidth = 0xC;
        self->posY.i.hi = 0x160;
        self->velocityY = FIX(-6);
        self->flags = FLAG_UNK_04000000 | FLAG_HAS_PRIMS;
        self->facingLeft = 0;
        self->ext.giantcross.unk7C = 0;
        self->ext.giantcross.unk7E = 0x400;
        PlaySfx(0x661);
        self->step++;
        primUVCoords = &D_800B0F94[0][0];
        prim = &g_PrimBuf[self->primIndex];
        for (i = 0; i < 46; i++, prim = prim->next, primUVCoords += 5) {
            prim->clut = (primUVCoords[4] & 0xF) | 0x1A0;
            switch (primUVCoords[4] & 0xF0) {
            case 0x10:
                prim->u0 = primUVCoords[0] + primUVCoords[2];
                prim->v0 = primUVCoords[1];
                prim->u1 = primUVCoords[0];
                prim->v1 = primUVCoords[1];
                prim->u2 = primUVCoords[0] + primUVCoords[2];
                prim->v2 = primUVCoords[1] + primUVCoords[3];
                prim->u3 = primUVCoords[0];
                prim->v3 = primUVCoords[1] + primUVCoords[3];
                break;
            case 0x20:
                prim->u0 = primUVCoords[0];
                prim->v0 = primUVCoords[1] + primUVCoords[3];
                prim->u1 = primUVCoords[0] + primUVCoords[2];
                prim->v1 = primUVCoords[1] + primUVCoords[3];
                prim->u2 = primUVCoords[0];
                prim->v2 = primUVCoords[1];
                prim->u3 = primUVCoords[0] + primUVCoords[2];
                prim->v3 = primUVCoords[1];
                break;
            case 0x30:
                prim->u0 = primUVCoords[0] + primUVCoords[2];
                prim->v0 = primUVCoords[1] + primUVCoords[3];
                prim->u1 = primUVCoords[0];
                prim->v1 = primUVCoords[1] + primUVCoords[3];
                prim->u2 = primUVCoords[0] + primUVCoords[2];
                prim->v2 = primUVCoords[1];
                prim->u3 = primUVCoords[0];
                prim->v3 = primUVCoords[1];
                break;
            case 0x40:
                prim->u3 = primUVCoords[0];
                prim->v3 = primUVCoords[1];
                prim->u1 = primUVCoords[0] + primUVCoords[2];
                prim->v1 = primUVCoords[1];
                prim->u2 = primUVCoords[0];
                prim->v2 = primUVCoords[1] + primUVCoords[3];
                prim->u0 = primUVCoords[0] + primUVCoords[2];
                prim->v0 = primUVCoords[1] + primUVCoords[3];
                break;
            case 0x50:
                prim->u3 = primUVCoords[0] + primUVCoords[2];
                prim->v3 = primUVCoords[1];
                prim->u1 = primUVCoords[0];
                prim->v1 = primUVCoords[1];
                prim->u2 = primUVCoords[0] + primUVCoords[2];
                prim->v2 = primUVCoords[1] + primUVCoords[3];
                prim->u0 = primUVCoords[0];
                prim->v0 = primUVCoords[1] + primUVCoords[3];
                break;
            case 0x60:
                prim->u3 = primUVCoords[0];
                prim->v3 = primUVCoords[1] + primUVCoords[3];
                prim->u1 = primUVCoords[0] + primUVCoords[2];
                prim->v1 = primUVCoords[1] + primUVCoords[3];
                prim->u2 = primUVCoords[0];
                prim->v2 = primUVCoords[1];
                prim->u0 = primUVCoords[0] + primUVCoords[2];
                prim->v0 = primUVCoords[1];
                break;
            case 0x70:
                prim->u3 = primUVCoords[0] + primUVCoords[2];
                prim->v3 = primUVCoords[1] + primUVCoords[3];
                prim->u1 = primUVCoords[0];
                prim->v1 = primUVCoords[1] + primUVCoords[3];
                prim->u2 = primUVCoords[0] + primUVCoords[2];
                prim->v2 = primUVCoords[1];
                prim->u0 = primUVCoords[0];
                prim->v0 = primUVCoords[1];
                break;
            default:
                prim->u0 = primUVCoords[0];
                prim->v0 = primUVCoords[1];
                prim->u1 = primUVCoords[0] + primUVCoords[2];
                prim->v1 = primUVCoords[1];
                prim->u2 = primUVCoords[0];
                prim->v2 = primUVCoords[1] + primUVCoords[3];
                prim->u3 = primUVCoords[0] + primUVCoords[2];
                prim->v3 = primUVCoords[1] + primUVCoords[3];
                break;
            }
        }
        return;
    }
    if (self->posY.i.hi < -0x40) {
        DestroyEntity(self);
        return;
    }
    if (self->posY.i.hi < 0) {
        self->velocityY -= FIX(0.5);
    }
    self->posY.val += self->velocityY;
    self->ext.giantcross.unk7C += 0x60;
    self->ext.giantcross.unk7E += 0x60;
    trans1.vx = -(rcos(self->ext.giantcross.unk7C) * 0x60) >> 0xC;
    trans1.vy = self->posY.i.hi - 0x80;
    trans1.vz = ((rsin(self->ext.giantcross.unk7C) * 0x60) >> 0xC) + 0x180;
    rot.vy = self->ext.giantcross.unk7E;
    rot.vz = 0x40;
    rot.vx = 0;

    SetGeomOffset(self->posX.i.hi, 120);
    gte_SetGeomScreen(320);
    RotMatrix(&rot, &m);
    TransMatrix(&m, &trans1);
    gte_SetRotMatrix(&m);
    gte_SetTransMatrix(&m);
    gte_ldv0(&pos);
    gte_rtps();
    prim = &g_PrimBuf[self->primIndex];
    vectors_ptr = &D_800B0CB4;
    gte_stsxy2(&prim->x0);
    gte_stszotz(&z);
    self->hitboxOffX = prim->x0 - self->posX.i.hi;
    self->hitboxOffY = prim->y0 - self->posY.i.hi;
    for (i = 0; i < 46; i++, prim = prim->next, vectors_ptr += 4) {
        gte_ldv3(vectors_ptr[0], vectors_ptr[1], vectors_ptr[3]);
        gte_rtpt();
        temp_a3 = vectors_ptr[2];
        prim->type = 4;
        gte_nclip();
        prim->drawMode = DRAW_HIDE;
        gte_stopz(&nclip);
        if (nclip < 0) {
            continue;
        }
        gte_stsxy3(&prim->x0, &prim->x1, &prim->x2);
        gte_ldv0(temp_a3);
        gte_rtps();
        prim->drawMode = DRAW_DEFAULT;
        if (z < 16) {
            priority = 0x1B6;
        } else if (z >= 999) {
            priority = 0x10;
        } else {
            priority = 0x120;
            priority -= z;
        }
        prim->priority = priority;
        gte_stsxy(&prim->x3);
    }
}
