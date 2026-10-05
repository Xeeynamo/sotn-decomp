// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../rno2/rno2.h"

extern AnimateEntityFrame D_pspeu_09258C88[];
extern AnimateEntityFrame D_pspeu_09258C90[];
extern AnimateEntityFrame D_pspeu_09258CA0[];
extern AnimateEntityFrame D_pspeu_09258CD0[];
extern AnimateEntityFrame D_pspeu_09258CE8[];
extern AnimateEntityFrame D_pspeu_09258CF8[];
extern AnimateEntityFrame D_pspeu_09258D00[];
extern AnimateEntityFrame D_pspeu_09258D10[];
extern AnimateEntityFrame D_pspeu_09258D20[];
extern EInit g_EInitMalachi;

void EntityMalachi(Entity* self) {
    RECT sp78;
    DRAWENV sp34; // appears at sp3c

    s32 var_s6;
    s32 primIndex;
    u32 var_s4;
    DR_ENV* dr_env;
    s32 var_s2;
    Entity* other;
    Primitive* prim;

    if ((g_Player.status & PLAYER_STATUS_DEAD) && (self->step < 9)) {
        SetStep(9);
    }
    if ((self->flags & FLAG_DEAD) && (self->step < 10)) {
        self->hitboxState = 0;
        SetStep(10);
    }
    if (self->ext.ILLEGAL.s16[3]) {
        self->ext.ILLEGAL.s16[3]--;
    }
    switch (self->step) {
    case 0x0:            
        InitializeEntity(g_EInitMalachi);
        other = self + 1;
        CreateEntityFromCurrentEntity(E_UNK_2C, other);
        self->ext.ILLEGAL.s16[6] = self->hitPoints;
        self->ext.ILLEGAL.s16[6] /= 2;
        /* fallthrough */
    case 0x1:
        if (UnkCollisionFunc3(&D_pspeu_09258C90) & 1) {
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
            SetStep(2);
        }
        break;
    case 0x2:
        if (!self->step_s) {
            self->ext.ILLEGAL.s16[2] = 0x40;
            self->step_s += 1;
            if (self->hitPoints < self->ext.ILLEGAL.s16[6]) {
                self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
                self->ext.ILLEGAL.s16[2] = 0x20;
            }
        }
        AnimateEntity(&D_pspeu_09258CD0, self);
        self->ext.ILLEGAL.s16[2]--;
        if (self->hitPoints < self->ext.ILLEGAL.s16[6]) {
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
            if (!self->ext.ILLEGAL.s16[2]) {
                SetStep(5);
            }
        } else {
            if (self->ext.ILLEGAL.s16[2] == 0x20) {
                self->facingLeft ^= 1;
            }
            if (self->facingLeft == ((GetSideToPlayer() & 1) ^ 1)) {
                SetStep(3);
            }
            if (!self->ext.ILLEGAL.s16[2]) {
                self->step_s = 0;
            }
        }
        break;
    case 0x3:                  
        switch (self->step_s) {
        case 0:                
            if (AnimateEntity(&D_pspeu_09258D10, self) == 0) {
                self->ext.ILLEGAL.s32[8] =
                    (self->posY.i.hi + g_Tilemap.scrollY.i.hi) - 0x20;
                SetSubStep(1);
            }
            break;
        case 1:
            self->velocityX = 0;
            self->velocityY = FIX(-4.0);
            self->animCurFrame = 0x1A;
            self->step_s += 1;
            /* fallthrough */
        case 2:
            MoveEntity();
            self->velocityY += FIX(0.1875);
            var_s2 = self->posY.i.hi + g_Tilemap.scrollY.i.hi;
            var_s2 -= self->ext.ILLEGAL.s32[8];
            if ((var_s2 <= 0) || (self->velocityY > 0)) {
                self->step_s++;
            }
            break;
        case 3:
            AnimateEntity(&D_pspeu_09258D00, self);
            if (!self->poseTimer && self->pose == 1) {
                PlaySfxPositional(SFX_WING_FLAP_A);
            }
            var_s2 = self->posY.i.hi + g_Tilemap.scrollY.i.hi;
            var_s2 -= self->ext.ILLEGAL.s32[8];
            if (var_s2 == 0) {
                self->ext.ILLEGAL.s16[2] = 0x80;
                self->velocityY = 0;
                self->step_s += 1;
            } else if (var_s2 < 0) {
                self->posY.i.hi++;
            } else {
                self->posY.i.hi--;
            }
            break;
        case 4:
            AnimateEntity(&D_pspeu_09258D00, self);
            if (!self->poseTimer && self->pose == 1) {
                PlaySfxPositional(SFX_WING_FLAP_A);
            }
            var_s4 = UnkCollisionFunc2(&D_pspeu_09258C88);
            if (var_s4 & 0x80) {
                self->facingLeft ^= 1;
            }
            if (self->facingLeft) {
                self->velocityX = FIX(0.75);
            } else {
                self->velocityX = FIX(-0.75);
            }
            if (!self->ext.ILLEGAL.s16[3]) {
                SetStep(7);
                self->ext.ILLEGAL.u8[9] = 1;
            }
            if (!self->ext.ILLEGAL.s16[2]) {
                if (var_s4 == 1) {
                    SetSubStep(5);
                }
            } else {
                self->ext.ILLEGAL.s16[2]--;
            }
            break;
        case 5:
            self->animCurFrame = 0x1C;
            if (UnkCollisionFunc3(&D_pspeu_09258C90) & 1) {
                SetSubStep(6);
            }
            break;
        case 6:
            if (AnimateEntity(&D_pspeu_09258D20, self) == 0) {
                if (!self->ext.ILLEGAL.s16[3]) {
                    SetStep(7);
                    self->ext.ILLEGAL.u8[9] = 0;
                } else {
                    SetStep(2);
                }
            }
            break;
        }
        break;
    case 0x5:                  
        switch (self->step_s) {
        case 0:                
            if (self->facingLeft) {
                self->velocityX = FIX(1.75);
            } else {
                self->velocityX = FIX(-1.75);
            }
            self->velocityY = FIX(-5.0);
            self->animCurFrame = 0x1A;
            self->step_s += 1;
            /* fallthrough */
        case 1:
            MoveEntity();
            self->velocityY += FIX(0.1875);
            if (self->velocityY > 0) {
                self->step_s += 1;
                if (!self->ext.ILLEGAL.u8[8]) {
                    self->ext.ILLEGAL.u8[8] = 2;
                } else {
                    self->ext.ILLEGAL.u8[8] -= 1;
                }
            }
            break;
        case 2:
            self->animCurFrame = 0x1C;
            if (UnkCollisionFunc3(&D_pspeu_09258C90) & 1) {
                SetSubStep(3);
            }
            break;
        case 3:
            if (AnimateEntity(&D_pspeu_09258D20, self) == 0) {
                self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
                SetSubStep(0);
                if (!self->ext.ILLEGAL.s16[3]) {
                    SetStep(7);
                    self->ext.ILLEGAL.u8[9] = 0;
                }
                if (GetDistanceToPlayerX() < 0x48) {
                    SetStep(6);
                }
            }
            break;
        }
        break;
    case 0x6:
        if (AnimateEntity(&D_pspeu_09258CA0, self) == 0) {
            SetStep(2);
        }
        break;
    case 0x7:                  
        switch (self->step_s) {
        case 0:                
            other = self + 1;
            other->step_s = 0;
            other->step = 2;
            other->pose = 0;
            other->poseTimer = 0;
            self->ext.ILLEGAL.s16[2] = 0x80;
            PlaySfxPositional(SFX_MAGIC_NOISE_SWEEP);
            self->step_s += 1;
            /* fallthrough */
        case 1:
            if (self->ext.ILLEGAL.u8[9]) {
                AnimateEntity(&D_pspeu_09258D00, self);
                if (!self->poseTimer && self->pose == 1) {
                    PlaySfxPositional(SFX_WING_FLAP_A);
                }
            }
            if (!--self->ext.ILLEGAL.s16[2]) {
                self->ext.ILLEGAL.s16[3] = 0x180;
                SetStep(2);
                if (self->ext.ILLEGAL.u8[9]) {
                    SetStep(3);
                    self->step_s = 5;
                }
            }
            break;
        }
        break;
    case 0x9:                  
        switch (self->step_s) {
        case 0:                
            if (UnkCollisionFunc3(&D_pspeu_09258C90) & 1) {
                self->step_s++;
            }
            break;
        case 1:
            if (AnimateEntity(&D_pspeu_09258CE8, self) == 0) {
                SetSubStep(2);
            }
            break;
        case 2:
            AnimateEntity(&D_pspeu_09258CF8, self);
            if ((g_Player.status & PLAYER_STATUS_DEAD) == 0) {
                SetStep(2);
            }
            break;
        }
        break;
    case 0xA:                  
        switch (self->step_s) {
        case 0:                
            other = self + 1;
            DestroyEntity(other);
            if (self->animCurFrame > 12 && self->animCurFrame < 23) {
                self->animCurFrame = 1;
            }
            primIndex = g_api.AllocPrimitives(PRIM_GT4, 8);
            if (primIndex == -1) {
                self->step = 0;
                return;
            }
            self->flags |= FLAG_HAS_PRIMS;
            self->primIndex = primIndex;
            prim = &g_PrimBuf[primIndex];
            self->ext.prim = prim;
            dr_env = g_api.func_800EDB08((POLY_GT4*)prim);
            if (dr_env == NULL) {
                DestroyEntity(self);
                return;
            }
            prim->type = PRIM_ENV;
            prim->priority = 0xF;
            if (self->params) {
                prim->priority += 4;
            }
            prim->drawMode = DRAW_DEFAULT;
            sp34 = g_CurrentBuffer->draw;
            sp34.isbg = 1;
            sp34.r0 = sp34.g0 = sp34.b0 = 0;
            if (self->params) {
                var_s2 = 0x180;
            } else {
                var_s2 = 0x100;
            }
            sp78.x = 0;
            sp78.y = var_s2;
            sp78.w = 0x80;
            sp78.h = 0x80;
            sp34.clip = sp78;
            sp34.ofs[0] = 0;
            sp34.ofs[1] = 0x100;
            SetDrawEnv(dr_env, &sp34);
            prim = prim->next;
            dr_env = g_api.func_800EDB08((POLY_GT4*)prim);
            if (dr_env == NULL) {
                DestroyEntity(self);
                return;
            }
            prim->type = PRIM_ENV;
            prim->priority = 0x12;
            if (self->params) {
                prim->priority += 4;
            }
            prim->drawMode = DRAW_UNK_800;
            prim = prim->next;
            self->ext.malachi.primA4 = prim;
            if (self->params) {
                var_s2 = 0xFF;
            } else {
                var_s2 = 0x7F;
            }
            prim->type = PRIM_GT4;
            prim->tpage = 0x110;
            prim->u0 = prim->u2 = 0;
            prim->u1 = prim->u3 = 0x3F;
            prim->v0 = prim->v1 = var_s2 - 0x70;
            prim->v2 = prim->v3 = var_s2;
            prim->x0 = prim->x2 = self->posX.i.hi - 0x20;
            prim->x1 = prim->x3 = prim->x0 + 0x40;
            prim->y2 = prim->y3 = self->posY.i.hi + 0x28;
            prim->y0 = prim->y1 = prim->y2 - 0x70;
            prim->priority = self->zPriority;
            prim->drawMode = DRAW_UNK02;
            prim = prim->next;
            prim->type = PRIM_TILE;
            if (self->params) {
                var_s2 = 0x80;
            } else {
                var_s2 = 0;
            }
            prim->x0 = 0;
            prim->y0 = var_s2;
            prim->u0 = 0x80;
            prim->v0 = 0x80;
            prim->r0 = prim->g0 = prim->b0 = 0;
            prim->priority = 0x11;
            if (self->params) {
                prim->priority += 4;
            }
            prim->drawMode = DRAW_UNK_40 | DRAW_TPAGE | DRAW_TRANSP;
            prim = prim->next;
            while (prim != NULL) {
                prim->drawMode = DRAW_HIDE;
                prim = prim->next;
            }
            self->zPriority = 0x10;
            if (self->params) {
                self->zPriority += 4;
            }
            if (self->params) {
                var_s2 = 0x100;
            } else {
                var_s2 = 0x80;
            }
            self->posX.i.hi = 0x20;
            self->posY.i.hi = var_s2 - 0x28;
            self->palette = g_EInitMalachi[3];
            self->flags &= ~FLAG_POS_CAMERA_LOCKED;
            self->step_s += 1;
            break;

        case 1:
            self->animCurFrame = 0;
            prim = self->ext.prim;
            prim->type = PRIM_ENV;
            dr_env = *(DR_ENV**)&prim->r1;
            sp34 = g_CurrentBuffer->draw;
            sp34.isbg = 0;
            sp34.dtd = 0;
            if (self->params) {
                var_s2 = 0x180;
            } else {
                var_s2 = 0x100;
            }
            sp78.x = 0;
            sp78.y = var_s2;
            sp78.w = 0x80;
            sp78.h = 0x80;
            sp34.clip = sp78;
            sp34.ofs[0] = 0;
            sp34.ofs[1] = 0x100;
            SetDrawEnv(dr_env, &sp34);
            prim->priority = 0xF;
            if (self->params) {
                prim->priority += 4;
            }
            prim->drawMode = DRAW_DEFAULT;
            prim = prim->next; // pointless since we never access it after this
            self->ext.ILLEGAL.s32[8] = 0x28;
            self->ext.ILLEGAL.s16[2] = 0x10;
            self->step_s += 1;
            /* fallthrough */
        case 2:
            prim = self->ext.malachi.primA4;
            var_s6 = Random() & 0x3F;
            var_s2 = self->ext.ILLEGAL.s32[8];
            if (!(g_Timer & 0xF)) {
                PlaySfxPositional(SFX_EXPLODE_B);
                other = AllocEntity(&g_Entities[64], &g_Entities[256]);
                if (other != NULL) {
                    CreateEntityFromCurrentEntity(2, other);
                    other->posX.i.hi = prim->x0 + var_s6;
                    other->posY.i.hi = (prim->y2 - 0x30) + var_s2;
                    other->params = 3;
                }
            }
            other = AllocEntity(&g_Entities[64], &g_Entities[256]);
            if (other != NULL) {
                CreateEntityFromCurrentEntity(E_CTULHU_DEATH, other);
                other->posX.i.hi = (self->posX.i.hi - 0x20) + var_s6;
                other->posY.i.hi = self->posY.i.hi + var_s2 + 4;
                other->facingLeft = var_s4;
                other->params = 1;
                other->zPriority = 0x10;
                if (self->params) {
                    other->zPriority += 4;
                }
            }
            if (!--self->ext.ILLEGAL.s16[2]) {
                self->ext.ILLEGAL.s16[2] = 2;
                self->ext.ILLEGAL.s32[8] -= 2;
                if (self->ext.ILLEGAL.s32[8] < -0x28) {
                    self->ext.ILLEGAL.s16[2] = 0x40;
                    self->step_s++;
                }
            }
            break;
        case 3:
            if (!--self->ext.ILLEGAL.s16[2]) {
                DestroyEntity(self);
                return;
            }
            break;
        }
        break;
    case 0xFF:
        #include "../pad2_anim_debug.h"
    }
    if (self->animCurFrame >= 15 && self->animCurFrame < 19) {
        self->hitboxOffX = -0x12;
        self->hitboxOffY = 0x11;
        self->hitboxWidth = 0x16;
        self->hitboxHeight = 0x16;
    } else {
        self->hitboxOffX = -1;
        self->hitboxOffY = 1;
        self->hitboxWidth = 0x13;
        self->hitboxHeight = 0x26;
    }
}

INCLUDE_ASM("st/rno2_psp/nonmatchings/rno2_psp/unk_C0F0", func_us_801C4960);

INCLUDE_ASM("st/rno2_psp/nonmatchings/rno2_psp/unk_C0F0", func_us_801C4C0C);

extern EInit g_EInitParticle;
extern AnimateEntityFrame g_Unk2EAnim[];

void func_us_801C4EA8(Entity* self) {
    s16 angle;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitParticle);
        self->animSet = 0xE;
        self->unk5A = 0x5C;
        self->palette = 0x2EE;
        self->drawFlags = ENTITY_ROTATE | ENTITY_SCALEX;
        self->scaleX = 0x60;
        self->scaleY = 0xC0;
        self->blendMode = BLEND_QUARTER | BLEND_TRANSP;
        angle = self->rotate;
        self->velocityX = rsin(angle) * 0x10;
        self->velocityY = rcos(angle) * -0x10;
        /* fallthrough */
    case 1:
        MoveEntity();
        if (AnimateEntity(g_Unk2EAnim, self) == 0) {
            DestroyEntity(self);
        }
    }
}
