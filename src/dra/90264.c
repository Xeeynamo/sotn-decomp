#include "dra.h"
#include "objects.h"
#include "sfx.h"

s16 D_800B0A3C[] = {1, 2, 1, 0, 1, 2, 1, 0};
s16 D_800B0A4C[] = {0, 1, 2, 3, 4, 3, 2, 1};
s16 D_800B0A5C[] = {0, 1, 0, -1, 0, 1, 0, -1};
s16 D_800B0A6C[] = {0, 1, 2, 3, 4, 3, 2, 1};
s16 D_800B0A7C[] = {0, 0, 1, 1, 2, 2, 3, 3};
s16 D_800B0A8C[] = {0, 1, 0, -1, 0, 1, 0, -1};
s16 D_800B0A9C[] = {0, 1, 1, 0, 0, 1, 1, 0};
s16 D_800B0AAC[] = {0, 0, 0, 1, 1, 1, 2, 2};

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
    if (ABS(PLAYER.velocityX) > FIX(3) &&
        (PLAYER.step_s != 2 || D_800B0914 != 4)) {
        func_8011A328(self, 13);
        self->enemyId = 3;
        if (self->hitFlags && !CastSpell(13)) {
            D_800B0914 = 3;
            PLAYER.ext.player.unkAC = 0xE0;
            D_800B091C = 0x18;
        }
    }
    self->hitFlags = 0;
}
static const u32 rodata_func_80130264_padding = 0;

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
    if (ABS(PLAYER.velocityX) > FIX(3)) {
        self->drawFlags |= DRAW_HIDE;
        self->drawMode = FLAG_DRAW_UNK10 | FLAG_DRAW_UNK20 | FLAG_DRAW_UNK40;
        self->unk6C = ~MIN((ABS(PLAYER.velocityX) - FIX(3)) >> 12, 160);
    }
}
static const u32 rodata_func_80130618_padding = 0;

INCLUDE_ASM("dra/nonmatchings/90264", func_801309B4);

INCLUDE_ASM("dra/nonmatchings/90264", func_80130E94);

// DECOMP_ME_WIP func_8013136C https://decomp.me/scratch/cu30D
// TODO: branching is wrong jpt_ needs a file split
#ifndef NON_EQUIVALENT
INCLUDE_ASM("dra/nonmatchings/90264", func_8013136C);
#else
void func_8012C600(void);
extern u16 D_8007412E;
extern s32 D_800741CC;
extern s32 D_800741D0;

void func_8013136C(Entity* entity) {
    if (!(g_Player.unk0C & PLAYER_STATUS_WOLF_FORM)) {
        DestroyEntity(entity);
        return;
    }
    if (entity->step == 0) {
        entity->animSet = ANIMSET_DRA(15);
        entity->unk5A = 0x7E;
        entity->palette = PLAYER.palette;
        entity->flags = FLAG_UNK_20000 | FLAG_UNK_40000 | FLAG_UNK_04000000;
        entity->drawFlags = FLAG_DRAW_ROTZ;
        entity->unk20 = -8;
        entity->step++;
    }
    entity->animCurFrame = 80;
    entity->facingLeft = PLAYER.facingLeft;
    entity->posX.val = g_Entities[UNK_ENTITY_13].posX.val; // D_800741CC
    entity->posY.val = g_Entities[UNK_ENTITY_13].posY.val; // D_800741D0
    if (PLAYER.facingLeft == 0) {
        entity->zPriority = PLAYER.zPriority - 5;
        entity->posX.i.hi += 8;
    } else {
        entity->zPriority = PLAYER.zPriority + 5;
        entity->posX.i.hi -= 8;
    }
    entity->posY.i.hi += 3;
    entity->unk1E = g_Entities[UNK_ENTITY_13].unk1E;
    switch (PLAYER.step_s - 1) {
    case 1:
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
        break;

    case 0:
        if (D_800B0914 == 1) {
            entity->posY.i.hi -= 2;
            if (PLAYER.facingLeft == 0) {
                entity->posX.i.hi -= 8;
            } else {
                entity->posX.i.hi += 8;
            }
        }
        break;

    case 2:
        switch (D_800B0914) {
        case 1:
            break;

        case 0:
            if (PLAYER.animCurFrame == 33) {
                entity->animCurFrame = 81;
                if (PLAYER.facingLeft == 0) {
                    entity->posX.i.hi += 3;
                } else {
                    entity->posX.i.hi += 6;
                }
            }
            if (PLAYER.animCurFrame == 34) {
                if (PLAYER.facingLeft == 0) {
                    entity->posX.i.hi += 3;
                } else {
                    entity->posX.i.hi += 13;
                }
                entity->animCurFrame = 82;
            }
        case 2:
            break;
        }
        break;
    }
    entity->palette = PLAYER.palette;
    func_8012C600();
}
#endif

// When Alucard uses the cross subweapon for 100 hearts.
// Entity ID 7, blueprint #7 (this is a coincidence)
void EntityGiantSpinningCross(Entity* self) {
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
