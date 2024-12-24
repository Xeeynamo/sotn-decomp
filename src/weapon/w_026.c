// SPDX-License-Identifier: AGPL-3.0-or-later
// Weapon ID #26. Used by weapons:
// Shaman shield, Unknown#210
#include "weapon_private.h"
extern u16* g_WeaponCluts[];
extern s32 g_HandId;
#include "w_026_1.h"
#include "w_026_2.h"
#define g_Animset w_026_1
#define g_Animset2 w_026_2
#include "shared.h"
#include "sfx.h"

extern SpriteParts D_BA000_8017A040[];
extern s8 D_BA000_8017AA18;
extern AnimationFrame* D_BA000_8017AA60;
extern s16 D_BA000_8017AA98;
extern s16 D_BA000_8017AA9A;
extern s32 D_BA000_8017AA9C[];
extern u8 D_BA000_8017AADC[];

extern s32 D_BA000_8017CC3C;

static void EntityWeaponAttack(Entity* self) {
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
    if ((g_Player.status & PLAYER_STATUS_UNK10000) && (self->step != 4)) {
        self->zPriority = PLAYER.zPriority + 2;
        self->step = 4;
        if (g_Player.pl_vram_flag & 1) {
            self->velocityX = PLAYER.velocityX;
        } else {
            self->velocityX = PLAYER.velocityX * 2;
        }
        self->velocityY = FIX(-3.5);
        self->ext.timer.t = 0x80;
        self->flags = FLAG_POS_CAMERA_LOCKED;
        self->animCurFrame = 0x3E;
    }
    if ((PLAYER.step == Player_Crouch) && (PLAYER.step_s != 2)) {
        anim2++;
    }
    switch (self->step) {
    case 0:
        SetSpriteBank1(D_BA000_8017A040);
        if (g_HandId != 0) {
            self->animSet = ANIMSET_OVL(0x12);
            self->palette = 0x128;
            self->unk5A = 0x66;
        } else {
            self->animSet = ANIMSET_OVL(0x10);
            self->palette = 0x110;
            self->unk5A = 0x64;
        }
        self->flags = FLAG_POS_PLAYER_LOCKED | FLAG_UNK_20000;
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
            self->drawFlags |= FLAG_BLINK;
        }
        if (--self->ext.timer.t == 0) {
            DestroyEntity(self);
            return;
        }
        break;
    }
    if (self->step != 4) {
        g_api.PlayAnimation(&D_BA000_8017AA18, &D_BA000_8017AA60);
    }
    self->drawFlags = PLAYER.drawFlags;
    self->rotY = PLAYER.rotY;
    self->rotPivotY = PLAYER.rotPivotY;
}

s32 func_ptr_80170004(Entity* self) {}

static void func_ptr_80170008(Entity* self) {}

static void func_ptr_8017000C(Entity* self) {}

static s32 func_ptr_80170010(Entity* self) {}

static s32 func_ptr_80170014(Entity* self) {}

static int GetWeaponId(void) { return 26; }

void func_BA000_8017B37C(void) {
    RECT rect;
    s16 temp;

    if (D_BA000_8017AA9A & 1) {
        if (++D_BA000_8017AA98 >= 0x20) {
            D_BA000_8017AA9A++;
            D_BA000_8017AA98 = 0x1F;
        }
    } else {
        if (--D_BA000_8017AA98 < 0) {
            D_BA000_8017AA9A++;
            D_BA000_8017AA98 = 0;
        }
    }

    temp = g_Clut[0x112D + g_HandId * 0x180];
    temp &= 0xFC1F;
    temp += D_BA000_8017AA98 << 5;
    g_Clut[0x112D + g_HandId * 0x180] = temp;

    rect.x = 0;
    rect.y = 0xF1;
    rect.w = 0x100;
    rect.h = 3;
    LoadImage(&rect, &g_Clut[0x1100]);
}

static void EntityWeaponShieldSpell(Entity* self) {
    s16 back;
    s16 front;
    s16 top;
    s16 bottom;

    Entity* unusedEnt;
    Primitive* prim;
    Primitive* prevPrim;
    Primitive* nextPrim;
    s32 i;
    s16 selfY;
    s16 baseCoord; // used for multiple stuff. Sometimes selfX, but not always

    s16 angle;

    switch (self->step) {
    case 0:
        self->primIndex = g_api.AllocPrimitives(PRIM_GT4, 0xE);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        SetSpriteBank1(D_BA000_8017A040);
        if (g_HandId != 0) {
            self->animSet = ANIMSET_OVL(0x12);
            self->palette = 0x128;
            self->ext.shield.childPalette = 0x129;
            self->unk5A = 0x66;
            self->ext.shield.unk7C = 0;
            self->ext.shield.unk7D = 0x80;
        } else {
            self->animSet = ANIMSET_OVL(0x10);
            self->palette = 0x110;
            self->ext.shield.childPalette = 0x111;
            self->unk5A = 0x64;
            self->ext.shield.unk7C = 0x80;
            self->ext.shield.unk7D = 0;
        }
        self->posY.i.hi -= 8;
        self->flags =
            FLAG_KEEP_ALIVE_OFFCAMERA | FLAG_HAS_PRIMS | FLAG_UNK_10000;
        self->zPriority = PLAYER.zPriority - 2;
        self->facingLeft = PLAYER.facingLeft;
        self->animCurFrame = 0x3E;
        self->drawFlags = FLAG_DRAW_ROTX | FLAG_DRAW_ROTY;

        self->rotX = self->rotY = 0;
        prim = &g_PrimBuf[self->primIndex];
        prim->clut = 0x19F;
        prim->tpage = 0x19;

        prim->u0 = prim->u2 = 0x80;
        prim->u1 = prim->u3 = 0x80 + 0x4F;
        prim->v0 = prim->v1 = self->ext.shield.unk7C + 0;
        prim->v2 = prim->v3 = self->ext.shield.unk7C + 0x4F;

        self->ext.shield.unk82 = 0;
        prim->r0 = prim->g0 = prim->b0 = prim->r1 = prim->g1 = prim->b1 =
            prim->r2 = prim->g2 = prim->b2 = prim->r3 = prim->g3 = prim->b3 =
                0x80;
        prim->priority = self->zPriority - 10;
        prim->drawMode =
            DRAW_UNK_40 | DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS | DRAW_TRANSP;
        prim = prim->next;
        prim->clut = self->ext.shield.childPalette;
        prim->tpage = 0x19;
        prim->u0 = prim->u1 = 0;
        prim->u2 = prim->u3 = 0x5F;
        prim->v3 = prim->v1 = self->ext.shield.unk7D + 0x48;
        prim->v2 = prim->v0 = self->ext.shield.unk7D + 0x7F;
        prim->r0 = prim->g0 = prim->b0 = prim->r1 = prim->g1 = prim->b1 =
            prim->r2 = prim->g2 = prim->b2 = prim->r3 = prim->g3 = prim->b3 =
                0x80;
        prim->priority = 0x1B8;
        prim->drawMode = DRAW_HIDE;
        for (i = 0; i < 12; i++) {
            prevPrim = prim;
            prim = prim->next;
            nextPrim = prim->next;
            *prim = *prevPrim;
            prim->next = nextPrim;
            prim->u1 = prim->u0 = i * 96 / 12;
            prim->u2 = prim->u3 = (i + 1) * 96 / 12 - 1;
            prim->clut = 0x15F;
            prim->priority = 0x1BA;
            prim->drawMode |=
                (DRAW_TPAGE2 + DRAW_TPAGE + DRAW_COLORS + DRAW_TRANSP);
        }
        self->ext.shield.unk8A = 0x80;
        self->ext.shield.unk90 = 0x100;
        self->ext.shield.unk92 = self->ext.shield.unk94 = 0;
        self->ext.shield.unk84 = self->ext.shield.unk86 = 0;
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

        self->ext.shield.unk82 = self->rotX * 0x28 / 256;
        if (self->rotX >= 0x100) {
            self->ext.shield.unk82 = 0x28;
            self->rotY = self->rotX = 0x100;
            self->ext.shield.unk80 = 8;
            self->step++;
        }
        break;
    case 2:
        if (--self->ext.shield.unk80 == 0) {
            self->ext.shield.unk80 = 0x10;
            self->step++;
        }
        break;
    case 3:
        prim = &g_PrimBuf[self->primIndex];
        if (!(self->ext.shield.unk80 & 1)) {
            prim->priority = 0x1B8;
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
            prim = prim->next;
            prim->drawMode &= ~DRAW_HIDE;
            prim = prim->next;
            for (i = 0; i < 12; i++) {
                prim->drawMode &= ~DRAW_HIDE;
                prim = prim->next;
            }
            // Blueprint 92 spawns weapon function #9, the Shaman Shield Star
            unusedEnt = g_api.CreateEntFactoryFromEntity(
                self, ((g_HandId + 1) << 0xE) + 92, 0);
            self->ext.shield.unk80 = 0;
            g_api.PlaySfx(SFX_GLASS_SHARDS);
            D_BA000_8017CC3C = 0;
            self->step++;
        }
        break;
    case 4:
        if (D_BA000_8017CC3C % 22 == 0) {
            g_api.PlaySfx(SFX_GLASS_SHARDS);
        }
        D_BA000_8017CC3C++;
        self->ext.shield.unk82 += 8;
        self->rotX += 12;
        if (self->rotX >= 0x100) {
            self->rotX = 0x100;
        }
        self->ext.shield.unk84 = self->rotX * 28 / 256;
        self->ext.shield.unk86 = self->rotX * 48 / 256;
        prim = &g_PrimBuf[self->primIndex];
        if (prim->b3 > 8) {
            prim->b3 -= 4;
        }
        prim->r0 = prim->g0 = prim->b0 = prim->r1 = prim->g1 = prim->b1 =
            prim->r2 = prim->g2 = prim->b2 = prim->r3 = prim->g3 = prim->b3;
        if (self->rotX == 0x100) {
            prim->b3 = 6;
            prim = &g_PrimBuf[self->primIndex];
            prim->drawMode |= DRAW_HIDE;
            prim->b3 = 4;
            prim = prim->next;
            prim->drawMode &= ~DRAW_HIDE;
            self->step++;
        }
        self->ext.shield.unk80++;
        break;
    case 5:
        if (D_BA000_8017CC3C % 22 == 0) {
            g_api.PlaySfx(SFX_GLASS_SHARDS);
        }
        D_BA000_8017CC3C++;
        self->ext.shield.unk90 -= 10;
        if (self->ext.shield.unk90 < 0) {
            self->ext.shield.unk90 = 0;
            self->step++;
            self->ext.shield.unk80 = 0;
        }
        break;
    case 6:
        if (D_BA000_8017CC3C % 22 == 0) {
            g_api.PlaySfx(SFX_GLASS_SHARDS);
        }
        D_BA000_8017CC3C++;
        if (++self->ext.shield.unk80 == 0x30) {
            self->step++;
        }
        break;
    case 7:
        if (D_BA000_8017CC3C % 22 == 0) {
            g_api.PlaySfx(SFX_GLASS_SHARDS);
        }
        D_BA000_8017CC3C++;
        self->ext.shield.unk90 += 4;
        if (self->ext.shield.unk90 > 0x120) {
            prim = g_PrimBuf[self->primIndex].next;
            prim->drawMode |= DRAW_HIDE;
            // Blueprint 55 has child 39, EntityPlayerPinkEffect
            g_api.CreateEntFactoryFromEntity(self, FACTORY(55, 6), 0);
            self->step++;
        }
        break;
    case 8:
        D_BA000_8017CC3C++;
        self->ext.shield.unk90 -= 8;
        self->ext.shield.unk92 += 2;
        self->ext.shield.unk94 += 2;
        if (self->ext.shield.unk90 < 0) {
            g_unkGraphicsStruct.unk20 = 0;
            DestroyEntity(self);
            return;
        }
        break;
    }
    baseCoord = self->posX.i.hi;
    selfY = self->posY.i.hi;
    prim = &g_PrimBuf[self->primIndex];
    if (prim->b3 > 8) {
        if (g_Timer & 1) {
            prim->drawMode |= DRAW_HIDE;
        } else {
            prim->drawMode &= ~DRAW_HIDE;
        }
    }
    prim->x0 = prim->x2 = baseCoord - self->ext.shield.unk82;
    prim->x1 = prim->x3 = (baseCoord + self->ext.shield.unk82) - 1;
    prim->y0 = prim->y1 = selfY - self->ext.shield.unk82;
    prim->y2 = prim->y3 = (selfY + self->ext.shield.unk82) - 1;
    prim = prim->next;
    top = prim->y0 = prim->y1 = selfY - self->ext.shield.unk86;
    bottom = prim->y2 = prim->y3 = (selfY + self->ext.shield.unk86) - 1;
    if (!self->facingLeft) {
        back = prim->x0 = prim->x2 = baseCoord - self->ext.shield.unk84;
        front = prim->x1 = prim->x3 = (baseCoord + self->ext.shield.unk84) - 1;
    } else {
        front = prim->x1 = prim->x3 = baseCoord - self->ext.shield.unk84;
        back = prim->x0 = prim->x2 = (baseCoord + self->ext.shield.unk84) - 1;
    }

    front++;
    bottom++;
    prim = prim->next;
    for (i = 0; i < 12; i++) {
        angle = D_BA000_8017AA9C[i];
        baseCoord = (rsin(angle) >> 5) * self->ext.shield.unk92 / 256;
        prim->x0 = back + baseCoord;
        prim->x1 = (front + baseCoord) - 1;
        angle = D_BA000_8017AA9C[(i + 1) % 12];
        baseCoord = (rsin(angle) >> 5) * self->ext.shield.unk92 / 256;
        prim->x2 = back + baseCoord;
        prim->x3 = (front + baseCoord) - 1;
        angle = D_BA000_8017AA9C[(i + 6) % 12];
        baseCoord = (rsin(angle) >> 5) * self->ext.shield.unk94 / 256;
        prim->y0 = top + (((bottom - top) * i) / 12) - baseCoord;
        prim->y2 = top + (((bottom - top) * (i + 1)) / 12) - baseCoord;
        angle = D_BA000_8017AA9C[(i + 1) % 12];
        baseCoord = (rsin(angle) >> 5) * self->ext.shield.unk94 / 256;
        prim->y1 = top + ((i * (bottom - top)) / 12) - baseCoord;
        prim->y3 = top + (((bottom - top) * (i + 1)) / 12) - baseCoord;
        angle = D_BA000_8017AA9C[i];
        prim->r0 = prim->r1 =
            ((rsin(angle) + 0x1000) >> 6) * self->ext.shield.unk90 / 256;
        angle = D_BA000_8017AA9C[(i + 4) % 12];
        prim->g0 = prim->g1 =
            ((rsin(angle) + 0x1000) >> 6) * self->ext.shield.unk90 / 256;
        angle = D_BA000_8017AA9C[(i + 8) % 12];
        prim->b0 = prim->b1 =
            ((rsin(angle) + 0x1000) >> 6) * self->ext.shield.unk90 / 256;
        angle = D_BA000_8017AA9C[(i + 1) % 12];
        prim->r2 = prim->r3 =
            ((rsin(angle) + 0x1000) >> 6) * self->ext.shield.unk90 / 256;
        angle = D_BA000_8017AA9C[(i + 5) % 12];
        prim->g2 = prim->g3 =
            ((rsin(angle) + 0x1000) >> 6) * self->ext.shield.unk90 / 256;
        angle = D_BA000_8017AA9C[(i + 9) % 12];
        prim->b2 = prim->b3 =
            ((rsin(angle) + 0x1000) >> 6) * self->ext.shield.unk90 / 256;
        D_BA000_8017AA9C[i] += self->ext.shield.unk8A;
        prim = prim->next;
    }
    func_BA000_8017B37C();
}

const SVECTOR D_BA000_8017AB7C = {8, -28, 0};
const SVECTOR D_BA000_8017AB84 = {56, -28, 0};
const SVECTOR D_BA000_8017AB8C = {8, 28, 0};
const SVECTOR D_BA000_8017AB94 = {56, 28, 0};

// When casting the Shaman Shield spell with the Shield Rod, an animation plays
// where several stars rotate in 3D around Alucard. This handles that rotation.
static void func_ptr_80170024(Entity* self) {
    SVECTOR rotation_axis;
    VECTOR transfer_vector;
    MATRIX m;
    SVECTOR vectors[4] = {D_BA000_8017AB7C, D_BA000_8017AB84, D_BA000_8017AB8C,
                          D_BA000_8017AB94};
    SVECTOR* vecs[2][4];
    s32 spA0;
    s32 spA4;
    Primitive* prim;
    Primitive* nextPrim;
    Primitive* primSrc;
    Primitive* primDest;
    Primitive* parentPrim;

    u16 uvOffset;
    s32 i;
    u16 clut;
    s32 rotTransResult;

    // This whole block might be fake.
    vecs[1][0] = &vectors[0];
    vecs[1][1] = &vectors[1];
    vecs[1][2] = &vectors[3];
    vecs[1][3] = &vectors[2];
    __builtin_memcpy(vecs[0], vecs[1], 4 * sizeof(SVECTOR*));

    if (g_HandId != 0) {
        clut = 0x12A;
        uvOffset = 0x80;
    } else {
        clut = 0x112;
        uvOffset = 0;
    }
    if ((self->params & 0x7F00) &&
        (self->ext.shamanshieldstar.parent->entityId == 0)) {
        DestroyEntity(self);
        return;
    }
    switch (self->step) {
    case 0:
        if (self->params & 0x7F00) {
            self->primIndex = g_api.AllocPrimitives(PRIM_GT4, 4);
            if (self->primIndex == -1) {
                DestroyEntity(self);
                return;
            }
            self->flags |= FLAG_KEEP_ALIVE_OFFCAMERA | FLAG_HAS_PRIMS;
            for (prim = &g_PrimBuf[self->primIndex]; prim != NULL;
                 prim = prim->next) {
                prim->drawMode = DRAW_HIDE;
            }
            self->step++;
            return;
        }
        self->primIndex = g_api.AllocPrimitives(PRIM_GT4, 1);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags |= FLAG_KEEP_ALIVE_OFFCAMERA | FLAG_HAS_PRIMS;
        self->ext.shamanshieldstar.unk9C = 0xA0;
        self->ext.shamanshieldstar.unk9E = 0x60;
        self->ext.shamanshieldstar.unk80 = rand() % 15;
        self->ext.shamanshieldstar.unk82 = 0;
        self->ext.shamanshieldstar.unk7C = -0x100;
        self->ext.shamanshieldstar.unk7E = (self->params & 0xFF) << 9;
        self->ext.shamanshieldstar.unk96 = 0x28;
        self->ext.shamanshieldstar.unk9A = 0x180;
        prim = &g_PrimBuf[self->primIndex];
        prim->tpage = 0x19;
        prim->clut = clut;
        // Careful here - uvOffset is either 0 or 0x80. But since the V values
        // in the array are all 0 or 0x80, this just ends up flipping the
        // image vertically. Doesn't matter since it's symmetric though.
        prim->u0 = D_BA000_8017AADC[0];
        prim->v0 = D_BA000_8017AADC[1] + uvOffset;
        prim->u1 = D_BA000_8017AADC[2];
        prim->v1 = D_BA000_8017AADC[3] + uvOffset;
        prim->u2 = D_BA000_8017AADC[4];
        prim->v2 = D_BA000_8017AADC[5] + uvOffset;
        prim->u3 = D_BA000_8017AADC[6];
        prim->v3 = D_BA000_8017AADC[7] + uvOffset;

        prim->priority = 0;
        prim->drawMode = DRAW_UNK_40 | DRAW_TPAGE2 | DRAW_TPAGE | DRAW_TRANSP;
        // Factory 90 has child 9 which, for weapons, is func_ptr_80170024, so
        // I think this spawns another copy of the star? Not totally clear.
        g_api.CreateEntFactoryFromEntity(
            self, ((g_HandId + 1) << 0xE) + FACTORY(90, 1), 0);
        self->step++;
        break;
    case 1:
        if (self->params & 0x7F00) {
            self->ext.shamanshieldstar.unk80++;
            parentPrim =
                &g_PrimBuf[self->ext.shamanshieldstar.parent->primIndex];
            prim = &g_PrimBuf[self->primIndex];
            for (i = 0; i < 4; i++) {
                if (i == ((self->ext.shamanshieldstar.unk80 >> 1) % 4)) {
                    primDest = prim;
                    if (self->ext.shamanshieldstar.parent->ext.shamanshieldstar
                            .unk9C > 0) {
                        nextPrim = prim->next;
                        primSrc = parentPrim;
                        *primDest = *primSrc;
                        prim->next = nextPrim;
                        prim = prim->next;
                        // Note: In this case, we do i++ but not prim =
                        // prim->next
                    } else {
                        prim->drawMode |= DRAW_HIDE;
                        prim = prim->next;
                    }
                } else {
                    prim = prim->next;
                }
            }
            return;
        } else {
            self->ext.shamanshieldstar.unk7E +=
                self->ext.shamanshieldstar.unk96;
            if (self->ext.shamanshieldstar.unk80 == 0) {
                self->ext.shamanshieldstar.unk9C -= 6;
                if (self->ext.shamanshieldstar.unk9C <= 0) {
                    self->ext.shamanshieldstar.unk9C = 0;
                }
                self->ext.shamanshieldstar.unk9E -= 6;
                if (self->ext.shamanshieldstar.unk9E <= 0) {
                    self->ext.shamanshieldstar.unk9E = 0;
                }
            } else {
                self->ext.shamanshieldstar.unk80--;
            }
            if (self->ext.shamanshieldstar.parent->step == 8) {
                self->step++;
                self->ext.shamanshieldstar.unk80 = rand() & 0xF;
            }
        }
        break;
    case 2:
        self->ext.shamanshieldstar.unk7E += self->ext.shamanshieldstar.unk96;
        if (self->ext.shamanshieldstar.unk80 == 0) {
            self->ext.shamanshieldstar.unk9C += 6;
            self->ext.shamanshieldstar.unk9E -= 6;
            if (self->ext.shamanshieldstar.unk9E < -0x80) {
                DestroyEntity(self);
                return;
            }
            break;
        }
        self->ext.shamanshieldstar.unk80--;
    }

    vectors[0].vx += self->ext.shamanshieldstar.unk9C;
    vectors[1].vx += self->ext.shamanshieldstar.unk9C;
    vectors[2].vx += self->ext.shamanshieldstar.unk9C;
    vectors[3].vx += self->ext.shamanshieldstar.unk9C;

    vectors[0].vy += self->ext.shamanshieldstar.unk9E;
    vectors[1].vy += self->ext.shamanshieldstar.unk9E;
    vectors[2].vy += self->ext.shamanshieldstar.unk9E;
    vectors[3].vy += self->ext.shamanshieldstar.unk9E;

    rotation_axis.vx = self->ext.shamanshieldstar.unk7C;
    rotation_axis.vy = self->ext.shamanshieldstar.unk7E;
    rotation_axis.vz = self->ext.shamanshieldstar.unk82;

    transfer_vector.vz = self->ext.shamanshieldstar.unk9A;
    transfer_vector.vx = 0;
    transfer_vector.vy = 0x10;

    SetGeomScreen(0x280);
    SetGeomOffset(self->posX.i.hi, self->posY.i.hi);
    RotMatrix(&rotation_axis, &m);
    TransMatrix(&m, &transfer_vector);
    SetRotMatrix(&m);
    SetTransMatrix(&m);
    prim = &g_PrimBuf[self->primIndex];

    rotTransResult = RotTransPers4(
        vecs[0][0], vecs[0][1], vecs[0][2], vecs[0][3], (long*)&prim->x0,
        (long*)&prim->x1, (long*)&prim->x3, (long*)&prim->x2, &spA0, &spA4);
    prim->drawMode |= DRAW_HIDE;
    if (0 < rotTransResult && rotTransResult <= 0x1BE) {
        prim->priority = 0x1B4;
        if (0x900 < (self->ext.shamanshieldstar.unk7E & 0xFFF) &&
            (self->ext.shamanshieldstar.unk7E & 0xFFF) < 0xF00) {
            prim->priority = 0x1BE;
        }
        prim->drawMode &= ~DRAW_HIDE;
        prim->type = PRIM_GT4;
    }
}

static void func_ptr_80170028(Entity* self) {}

static void WeaponUnused2C(void) {}

static void WeaponUnused30(void) {}

static void WeaponUnused34(void) {}

static void WeaponUnused38(void) {}

static void WeaponUnused3C(void) {}
