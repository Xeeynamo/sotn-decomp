// SPDX-License-Identifier: AGPL-3.0-or-later
// Weapon ID #17. Used by weapons:
// Pentagram, Bat Pentagram
#include "weapon_private.h"
extern u16* g_WeaponCluts[];
extern s32 g_HandId;
#include "shared.h"
#include "w_017_1.h"
#include "w_017_2.h"
#define g_Animset w_017_1
#define g_Animset2 w_017_2

typedef struct {
    /* 0x00 */ s32 x0;
    /* 0x04 */ s32 y0;
    /* 0x08 */ s32 x1;
    /* 0x0C */ s32 y1;
    /* 0x10 */ s32 x2;
    /* 0x14 */ s32 y2;
    /* 0x18 */ s16 u0;
    /* 0x1A */ s16 v0;
    /* 0x1C */ s16 u1;
    /* 0x1E */ s16 v1;
    /* 0x20 */ s16 u2;
    /* 0x22 */ s16 v2;
    /* 0x24 */ u8 pad[8];
} PrimWeapon017; /* size = 0x2C */

extern Point16 D_7B000_8017A260[]; // sizeof(Point16) * 3 * (PrimCount - 1)
extern SVECTOR D_7B000_8017B0F4[]; // sizeof(SVECTOR) * 4 * (PrimCount - 1)
extern SVECTOR D_7B000_8017B10C[]; // sizeof(SVECTOR) * 4 * (PrimCount - 1)
extern PrimWeapon017 D_7B000_8017B3F4[]; // sizeof(PrimWeapon017) * (PrimCount - 1)

void EntityWeaponAttack(Entity* self) {
    const int PrimCount = 25;
    PrimWeapon017* dest;
    Point16* coords;
    SVECTOR* vectors;
    Primitive* prim;

    s32 i, j;
    s16 x, y;
    u16 clut;
    u16 vOffset, uOffset;

    SVECTOR vector;
    VECTOR vec32;
    MATRIX matrix;

    s32 flag;
    long inter;
    long otz;
    long flags;
    s32 result;

    if (g_HandId != 0) {
        clut = 0x128;
        vOffset = 0x80;
    } else {
        clut = 0x110;
        vOffset = 0;
    }
    if (self->params & 0x7F00) {
        uOffset = 0x80;
        clut = 0x19F;
    } else {
        uOffset = 0;
    }

    flag = 0;
    switch (self->step) {
    case 0:
        self->primIndex = g_api.AllocPrimitives(PRIM_GT3, PrimCount);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }

        g_api.func_80118C28(4);
        g_api.PlaySfx(SE_WPN_PENTAGRAM);
        g_api.func_80102CD8(3);
        SetWeaponProperties(self, 0);
        self->ext.weapon.lifetime = 24;

        vectors = D_7B000_8017B0F4;
        coords = D_7B000_8017A260;

        for (i = 0; i < (PrimCount - 1); i++) {
            x = (coords[0].x + coords[1].x + coords[2].x) / 3;
            y = (coords[0].y + coords[1].y + coords[2].y) / 3;

            for (j = 0; j < 3; j++) {
                vectors->vx = coords->x - x;
                vectors->vy = coords->y - y;
                vectors->vz = 0;

                vectors++;
                coords++;
            }

            vectors->vx = x - 0x40;
            vectors->vy = y - 0x40;
            vectors->vz = 0x280;
            vectors++;
        }

        x = self->posX.i.hi = 0x80;
        y = self->posY.i.hi = 0x68;

        self->flags = FLAG_KEEP_ALIVE_OFFCAMERA | FLAG_HAS_PRIMS;

        prim = &g_PrimBuf[self->primIndex];
        prim->tpage = 0x19;
        prim->clut = clut;
        prim->u0 = prim->u2 = (s32)uOffset;
        prim->u1 = prim->u3 = uOffset + 0x7F;
        prim->v0 = prim->v1 = (s32)vOffset;
        prim->v2 = prim->v3 = vOffset + 0x7F;
        prim->x0 = prim->x2 = 0x40;
        prim->x1 = prim->x3 = 0xC0;
        prim->y0 = prim->y1 = 0x28;
        prim->y2 = prim->y3 = 0xA8;
        prim->priority = 0x1BA;
        prim->drawMode = DRAW_TPAGE | DRAW_TRANSP;

        if (self->params & 0x7F00) {
            prim->drawMode = DRAW_DEFAULT;
        }

        prim->type = PRIM_GT4;
        prim = prim->next;

        vectors = D_7B000_8017B0F4;
        coords = D_7B000_8017A260;

        for (i = 0; i < (PrimCount - 1); i++) {
            prim->u0 = coords[0].x + uOffset;
            prim->v0 = coords[0].y + vOffset;
            prim->u1 = coords[1].x + uOffset;
            prim->v1 = coords[1].y + vOffset;
            prim->u2 = coords[2].x + uOffset;
            prim->v2 = coords[2].y + vOffset;

            vectors += 4;
            coords += 3;

            prim->clut = clut;
            prim->tpage = 0x19;
            prim->priority = 0x1B6;
            prim->drawMode = DRAW_TPAGE | DRAW_TRANSP;

            if (self->params & 0x7F00) {
                prim->drawMode = DRAW_DEFAULT;
            }
            prim = prim->next;
        }

        g_Player.timers[12] = 4;
        self->step++;
        break;

    case 1:
        if (--self->ext.weapon.lifetime == 0) {
            self->hitboxState = 0;

            vectors = D_7B000_8017B10C;
            dest = D_7B000_8017B3F4;

            for (i = 0; i < (PrimCount - 1); i++) {
                s16 angle;
                dest->x0 = vectors->vx << 0x10;
                dest->x1 = vectors->vy << 0x10;
                dest->x2 = vectors->vz << 0x10;

                angle = ((rand() % 0x2AA) + ((i / 4) * 0x2AA));
                dest->y0 = rcos(angle) * 0x10;
                dest->y1 = -rsin(angle) * 0x10;
                dest->y2 = rcos(angle + 0x600) * 0x40;

                if (i & 1) {
                    dest->y2 = -dest->y2;
                }

                dest->u0 = dest->u1 = dest->u2 = 0;

                dest->v0 = (rand() % 160) - 0x50;
                dest->v1 = (rand() % 160) - 0x50;
                dest->v2 = (rand() % 160) - 0x50;

                vectors += 4;
                dest++;
            }

            self->ext.weapon.lifetime = 128;
            self->step++;
        }
        break;
    case 2:
        flag = 1;
        dest = D_7B000_8017B3F4;
        for (i = 0; i < (PrimCount - 1); i++) {
            dest->x0 += dest->y0;
            dest->x1 += dest->y1;
            dest->x2 += dest->y2;

            dest->u0 += dest->v0;
            dest->u1 += dest->v1;
            dest->u2 += dest->v2;

            dest++;
        }
        if (--self->ext.timer.t == 0) {
            DestroyEntity(self);
            return;
        }
        break;
    }

    SetGeomScreen(0x200);

    prim = &g_PrimBuf[self->primIndex];
    if ((self->params & 0x7F00) == 0) {
        prim->clut = clut + ((g_GameTimer >> 1) & 1);
    }

    if (flag == 0) {
        return;
    }

    prim->drawMode |= DRAW_HIDE;
    prim = prim->next;

    for (j = 0; j < (PrimCount - 1); j++) {
        vectors = &D_7B000_8017B0F4[j * 4];
        dest = &D_7B000_8017B3F4[j];

        vector.vx = dest->u0;
        vector.vz = dest->u2;
        vector.vy = dest->u1;
        vec32.vx = 0;
        vec32.vy = 0;
        vec32.vz = dest->x2 >> 16;

        SetGeomOffset((dest->x0 >> 16) + 0x80, (dest->x1 >> 16) + 0x68);

        RotMatrix(&vector, &matrix);
        TransMatrix(&matrix, &vec32);
        SetRotMatrix(&matrix);
        SetTransMatrix(&matrix);
        SetRotMatrix(&matrix);
        SetTransMatrix(&matrix);
        
        otz = 0;
        result = RotAverageNclip3(
            &vectors[0], &vectors[1], &vectors[2], (long*)&prim->x0,
            (long*)&prim->x1, (long*)&prim->x2, &inter, &otz, &flags);

        if (result < 0) {
            otz = 0;
            RotAverageNclip3(
                &vectors[0], &vectors[2], &vectors[1], (long*)&prim->x0,
                (long*)&prim->x2, (long*)&prim->x1, &inter, &otz, &flags);
        }

        prim->drawMode |= DRAW_HIDE;
        if (otz > 0 && otz <= FIX(446.0 / 65536.0)) {
            if ((self->params & 0x7F00) == 0) {
                prim->clut = clut + ((g_GameTimer >> 1) & 1);
                if (result < 0) {
                    prim->clut += 2;
                }
            }

            prim->priority = 0x1BA;
            prim->drawMode &= ~DRAW_HIDE;
            prim->type = PRIM_GT3;
        }
        prim = prim->next;
    }
}

s32 func_ptr_80170004(Entity* self) {}

static void func_ptr_80170008(Entity* self) {}

static void func_ptr_8017000C(Entity* self) {}

static s32 func_ptr_80170010(Entity* self) {}

static s32 func_ptr_80170014(Entity* self) {}

static int GetWeaponId(void) { return 17; }

static void EntityWeaponShieldSpell(Entity* self) {}

static void func_ptr_80170024(Entity* self) {}

static void func_ptr_80170028(Entity* self) {}

static void WeaponUnused2C(void) {}

static void WeaponUnused30(void) {}

static void WeaponUnused34(void) {}

static void WeaponUnused38(void) {}

static void WeaponUnused3C(void) {}
