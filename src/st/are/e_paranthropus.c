// SPDX-License-Identifier: AGPL-3.0-or-later
#include "are.h"

extern EInit D_us_80180BF4;
extern EInit D_us_80180C0C;
extern EInit D_us_80180C00;
extern EInit g_EInitInteractable;

static s16 D_us_80182878[] = {
    0x0000, 0x001B, 0x0000, 0x0004, 0x0010, 0xFFFC, 0xFFE0, 0x0000,
};
static s16 D_us_80182888[] = {
    0x0000, 0x0008, 0x0000, 0x0004, 0x0010, 0xFFFC, 0xFFE0, 0x0000,
};
static u8 D_us_80182898[] = {
    0x19, 0x01, 0x09, 0x02, 0x09, 0x03, 0x19, 0x04,
    0x09, 0x03, 0x09, 0x02, 0x00, 0x00, 0x00, 0x00,
};
static u8 D_us_801828A8[] = {
    0x09, 0x07, 0x09, 0x08, 0x09, 0x09, 0x1F, 0x0A, 0x04, 0x0B,
    0x04, 0x0C, 0x02, 0x0D, 0x02, 0x0E, 0x02, 0x0F, 0x02, 0x10,
    0x02, 0x0F, 0x02, 0x10, 0x1F, 0x0F, 0x00, 0x00,
};
static u8 D_us_801828C4[] = {
    0x06, 0x11, 0x07, 0x12, 0x08, 0x13, 0x09, 0x14, 0x06, 0x15,
    0x06, 0x16, 0x06, 0x17, 0x20, 0x18, 0x00, 0x00, 0x00, 0x00,
};
static u8 D_us_801828D8[] = {
    0x06, 0x01, 0x04, 0x19, 0x05, 0x1A, 0x05, 0x1B, 0x08, 0x1C,
    0x06, 0x1D, 0x06, 0x1E, 0x06, 0x1F, 0x01, 0x20, 0x01, 0x1F,
    0x01, 0x20, 0x01, 0x1F, 0x21, 0x20, 0x06, 0x1E, 0x06, 0x1D,
    0x06, 0x1C, 0x06, 0x1B, 0x06, 0x1A, 0x06, 0x19, 0xFF, 0x00,
};
static u8 unused_one[] = {
    0x06, 0x05, 0x14, 0x06, 0x06, 0x01, 0xFF, 0x00,
};
static u8 D_us_80182908[] = {
    0x10, 0x21, 0x06, 0x20, 0x10, 0x21, 0x06, 0x20, 0x10, 0x21, 0x06,
    0x20, 0x06, 0x1F, 0x06, 0x1E, 0x06, 0x1D, 0x06, 0x1C, 0x06, 0x1B,
    0x06, 0x1A, 0x06, 0x19, 0x21, 0x01, 0xFF, 0x00, 0x00, 0x00,
};
static u8 D_us_80182928[] = {
    0x05, 0x22, 0x05, 0x23, 0x05, 0x24, 0x05, 0x25, 0x05,
    0x26, 0x05, 0x27, 0x02, 0x28, 0x02, 0x29, 0x02, 0x28,
    0x02, 0x29, 0x02, 0x28, 0x22, 0x29, 0xFF,
};

static u8 unused[] = {
    0x02, 0x2B, 0x02, 0x2C, 0x02, 0x2D, 0x02, 0x2E, 0x02, 0x2F, 0x02,
    0x30, 0x02, 0x31, 0x02, 0x32, 0x02, 0x33, 0x02, 0x34, 0x02, 0x35,
    0x02, 0x36, 0x00, 0x00, 0x00, 0x00, 0x04, 0x05, 0x06, 0x00,
};

static Point16 D_us_80182964[] = {
    {0xFFE0, 0x001B}, {0x0020, 0x0018}, {0x0008, 0x001D},
    {0xFFF0, 0x001D}, {0x0000, 0x001F}, {0xFFFC, 0x0017},
};
static Point16 D_us_8018297C[] = {
    {0xFFF7, 0xFFFF}, {0xFFF7, 0x0004}, {0xFFF6, 0x000A},
    {0xFFF6, 0x000D}, {0xFFF6, 0x000D},
};
static Point16 D_us_80182990[] = {
    {0x0012, 0x0018}, {0x001A, 0x000B}, {0x001A, 0x000B},
    {0x001B, 0x000B}, {0x001B, 0x000B},
};
static s16 D_us_801829A4[] = {0x0000, 0x0006, 0x0005, 0x0002, 0x0000};

static s16 D_us_801829A4_two[] = {
    0x0000, 0x0006, 0x0005, 0x0002, 0x0000,
    0x0000, 0x0000, 0x0004, 0x0000, 0x0000,
};

static s16 D_us_801829A4_three[] = {0x0000, 0x0006, 0x0005, 0x0002, 0x0000,
                                    0x0000, 0x0004, 0x0000, 0x0000, 0x0000};

static Point16 D_us_801829D8[] = {
    {0x0000, 0x0000}, {0xFFDE, 0x0010}, {0xFFDE, 0x0010}, {0xFFDC, 0x0010},
    {0xFFDB, 0x0010}, {0xFFDE, 0x0010}, {0xFFDE, 0x0010}, {0xFFDF, 0x0010},
    {0x0000, 0x0000}, {0x0000, 0x0000}, {0x001F, 0xFFF7}, {0x001C, 0xFFDF},
    {0x0008, 0xFFDC}, {0xFFE2, 0xFFDA}, {0xFFD8, 0xFFF1}, {0xFFD5, 0x0016},
    {0xFFD5, 0x0019}, {0xFFE2, 0x0010}, {0x0000, 0x0000}, {0x0004, 0xFFE1},
    {0x000E, 0xFFDA}, {0x0009, 0xFFDB}, {0xFFE0, 0xFFD9}, {0x0000, 0x0000},
    {0x0000, 0x0000}, {0xFFE2, 0x0010}, {0xFFE2, 0x000F}, {0xFFE2, 0x000E},
    {0xFFE2, 0x000D}, {0xFFDA, 0x000E}, {0xFFD1, 0x0014}, {0xFFCE, 0x0015},
    {0xFFCB, 0x0018},
};
static u16 D_us_80182A5C[][2] = {
    {0x0000, 0x0000}, {0x0008, 0x0004}, {0x0008, 0x0004}, {0x0008, 0x0004},
    {0x0008, 0x0004}, {0x0008, 0x0004}, {0x0008, 0x0004}, {0x0008, 0x0004},
    {0x0000, 0x0000}, {0x0000, 0x0000}, {0x0008, 0x0004}, {0x0004, 0x0008},
    {0x0004, 0x000C}, {0x0004, 0x000C}, {0x0004, 0x000C}, {0x000C, 0x0004},
    {0x000C, 0x0004}, {0x000C, 0x0004}, {0x0000, 0x0000}, {0x0004, 0x0004},
    {0x0004, 0x000C}, {0x0004, 0x000C}, {0x0004, 0x000C}, {0x0000, 0x0000},
    {0x0000, 0x0000}, {0x000C, 0x0004}, {0x000C, 0x0004}, {0x000C, 0x0004},
    {0x000C, 0x0004}, {0x000C, 0x0004}, {0x000C, 0x0004}, {0x000C, 0x0004},
    {0x000C, 0x0004},
};
static Point16 D_us_80182AE0[] = {
    {0x0000, 0x0000}, {0xFFF3, 0xFFED}, {0xFFF3, 0xFFEC}, {0xFFF3, 0xFFEC},
    {0xFFF3, 0xFFED}, {0xFFF2, 0xFFEF}, {0xFFF3, 0xFFF0}, {0xFFF3, 0xFFED},
    {0xFFF5, 0xFFE8}, {0xFFF6, 0xFFE7}, {0xFFF9, 0xFFE3}, {0xFFF9, 0xFFE3},
    {0xFFF6, 0xFFE7}, {0xFFF5, 0xFFE8}, {0xFFF3, 0xFFED}, {0xFFF1, 0xFFEF},
    {0xFFF1, 0xFFF1}, {0xFFF3, 0xFFED}, {0xFFF5, 0xFFE8}, {0xFFF7, 0xFFE7},
    {0xFFFC, 0xFFE1}, {0xFFF7, 0xFFE6}, {0xFFF5, 0xFFE8}, {0xFFF3, 0xFFED},
    {0xFFF1, 0xFFEF}, {0xFFF2, 0xFFED}, {0xFFF2, 0xFFEC}, {0xFFF2, 0xFFEB},
    {0xFFF2, 0xFFEA}, {0xFFEA, 0xFFED}, {0xFFE3, 0xFFF5}, {0xFFE0, 0xFFFE},
    {0xFFDF, 0x0005}, {0xFFDF, 0x0005},
};

void func_us_801CDCC0(u16 step) {
    g_CurrentEntity->pose = 0;
    g_CurrentEntity->poseTimer = 0;
    g_CurrentEntity->ext.paranthropus.unk7C = 0;
    g_CurrentEntity->ext.paranthropus.unk7E = 0;
    g_CurrentEntity->step = step;
}

void func_us_801CDCF4(Entity* self) {
    Collider collider;
    Primitive* prim;
    Entity* entity;
    s32 i;
    s16 var_s3;
    u8 var_s4;
    s16 var_s6;
    s16 var_s5;
    s32 primIndex;
    s16 posX;
    s16 posY;

    self->ext.paranthropus.unk7D = self->facingLeft;
    if (self->flags & FLAG_DEAD && self->step < 7) {
        func_us_801CDCC0(7);
        self->hitboxState = 0;
        (self + 1)->hitboxState = 0;
        entity = AllocEntity(&g_Entities[160], &g_Entities[192]);
        if (entity != NULL) {
            DestroyEntity(entity);
            CreateEntityFromEntity(E_UNK_3C, self, entity);
            entity->facingLeft = self->facingLeft;
            entity->posY.i.hi -= 0x18;
            if (self->facingLeft) {
                entity->posX.i.hi += 0x10;
            } else {
                entity->posX.i.hi -= 0x10;
            }
            entity->params = 0xB;
        }
    }

    switch (self->step) {
    case 0:
        InitializeEntity(D_us_80180BF4);
        self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
        if (self->params == 0xB) {
            self->zPriority++;
            self->animCurFrame = 0x2A;
            self->hitboxState = 0;
            self->flags |= FLAG_DESTROY_IF_OUT_OF_CAMERA |
                           FLAG_DESTROY_IF_BARELY_OUT_OF_CAMERA |
                           FLAG_UNK_00200000 | FLAG_UNK_2000;
            self->drawFlags = FLAG_DRAW_ROTATE;
            self->step = 0xB;
        } else {
            self->drawFlags |= FLAG_DRAW_SCALEY | FLAG_DRAW_SCALEX;
            self->scaleX = self->scaleY = 0x100;

            entity = self + 1;
            CreateEntityFromEntity(E_UNK_3D, self, entity);

            entity = self + 2;
            CreateEntityFromEntity(E_UNK_3E, self, entity);
        }
        break;
    case 1:
        UnkCollisionFunc3(D_us_80182878);
        self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
        if (GetDistanceToPlayerX() < 0x60) {
            self->step_s = 0;
            self->ext.paranthropus.unk85 = 0;
            func_us_801CDCC0(3);
        }
        break;
    case 2:
        if (!AnimateEntity(D_us_80182908, self)) {
            self->step_s = 0;
            self->ext.paranthropus.unk85 = 0;
            func_us_801CDCC0(3);
        }
        break;
    case 3:
        if (!self->step_s) {
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
            self->step_s++;
        }

        if (self->ext.paranthropus.unk7E) {
            if (self->poseTimer == 0) {
                if (self->facingLeft) {
                    self->posX.i.hi += D_us_801829A4[self->animCurFrame];
                } else {
                    self->posX.i.hi -= D_us_801829A4[self->animCurFrame];
                }

                if (self->pose == 3 || self->pose == 6) {
                    PlaySfxPositional(SFX_STOMP_HARD_B);
                }

                self->posY.i.hi += 4;
                posX = self->posX.i.hi;
                posY = self->posY.i.hi + 0x1B;
                g_api.CheckCollision(posX, posY, &collider, 0);
                if (collider.effects & EFFECT_SOLID) {
                    self->posY.i.hi += collider.unk18;
                }
            }
        } else {
            self->ext.paranthropus.unk7E = 1;
        }

        if (!AnimateEntity(D_us_80182898, self)) {
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
            self->ext.paranthropus.unk7C++;
        }
        if (self->ext.paranthropus.unk7C > 1 && GetDistanceToPlayerX() < 0x60) {
            self->step_s = 0;

            switch (self->ext.paranthropus.unk85) {
            case 0:
                func_us_801CDCC0(4);
                break;
            case 1:
                func_us_801CDCC0(5);
                break;
            case 2:
                if (self->facingLeft) {
                    self->velocityX = FIX(2.0);
                } else {
                    self->velocityX = FIX(-2.0);
                }
                self->velocityY = FIX(-6.25);
                func_us_801CDCC0(6);
                break;
            }
        }
        break;
    case 4:
        if (self->ext.paranthropus.unk7E) {
            if (self->poseTimer == 0) {
                if (self->facingLeft) {
                    self->posX.i.hi +=
                        D_us_801829A4_three[self->animCurFrame - 0x10];
                } else {
                    self->posX.i.hi -=
                        D_us_801829A4_three[self->animCurFrame - 0x10];
                }
            }
        } else {
            self->ext.paranthropus.unk7E = 1;
        }

        if (!AnimateEntity(D_us_801828C4, self)) {
            self->ext.paranthropus.unk85 = 1;
            func_us_801CDCC0(3);
        }

        if (self->animCurFrame == 0x17) {
            if (!self->ext.paranthropus.unk7C) {
                entity = AllocEntity(&g_Entities[160], &g_Entities[192]);
                if (entity != NULL) {
                    PlaySfxPositional(SFX_BONE_THROW);
                    CreateEntityFromEntity(E_UNK_3F, self, entity);
                    entity->facingLeft = self->facingLeft;
                    entity->posY.i.hi -= 0x20;
                    if (self->facingLeft) {
                        entity->posX.i.hi += 0x18;
                    } else {
                        entity->posX.i.hi -= 0x18;
                    }
                }
                self->ext.paranthropus.unk7C = 1;
            }
        } else {
            self->ext.paranthropus.unk7C = 0;
        }
        break;
    case 5:
        if (self->ext.paranthropus.unk7E) {
            if (self->poseTimer == 0) {
                if (self->facingLeft) {
                    self->posX.i.hi +=
                        D_us_801829A4_two[self->animCurFrame - 6];
                } else {
                    self->posX.i.hi -=
                        D_us_801829A4_two[self->animCurFrame - 6];
                }
            }
        } else {
            self->ext.paranthropus.unk7E = 1;
        }

        if (self->pose == 7 && !self->poseTimer) {
            PlaySfxPositional(SFX_EXPLODE_B);
        }

        if (!AnimateEntity(D_us_801828A8, self)) {
            self->ext.paranthropus.unk85 = 2;
            func_us_801CDCC0(3);
        }
        break;
    case 6:
        if (UnkCollisionFunc3(D_us_80182878) & 1) {
            if (self->facingLeft) {
                EntityExplosionVariantsSpawner(self, 5, 3, 0x20, 0x1B, 0, 4);
                EntityExplosionVariantsSpawner(self, 4, 3, 0x18, 0x1B, 0, 4);
                EntityExplosionVariantsSpawner(self, 3, 3, 0x10, 0x1B, 0, 4);
                EntityExplosionVariantsSpawner(self, 2, 3, 8, 0x1B, 0, 4);
                EntityExplosionVariantsSpawner(self, 2, 3, 0, 0x1B, 0, 4);
                EntityExplosionVariantsSpawner(self, 2, 3, 0, 0x1B, 0, -4);
                EntityExplosionVariantsSpawner(self, 5, 3, -8, 0x1B, 0, -4);
            } else {
                EntityExplosionVariantsSpawner(self, 5, 3, 8, 0x1B, 0, 4);
                EntityExplosionVariantsSpawner(self, 2, 3, 0, 0x1B, 0, 4);
                EntityExplosionVariantsSpawner(self, 2, 3, 0, 0x1B, 0, -4);
                EntityExplosionVariantsSpawner(self, 2, 3, -8, 0x1B, 0, -4);
                EntityExplosionVariantsSpawner(self, 3, 3, -0x10, 0x1B, 0, -4);
                EntityExplosionVariantsSpawner(self, 4, 3, -0x18, 0x1B, 0, -4);
                EntityExplosionVariantsSpawner(self, 5, 3, -0x20, 0x1B, 0, -4);
            }
            g_api.func_80102CD8(1);
            PlaySfxPositional(SFX_EXPLODE_D);
            func_us_801CDCC0(2);
        } else {
            AnimateEntity(D_us_801828D8, self);
        }
        break;
    case 7:
#ifdef VERSION_PSP
        if (UnkCollisionFunc3(D_us_80182878) & 1) {
            PlaySfxPositional(SFX_SKELETON_DEATH_A);
            func_us_801CDCC0(8);
        }
#else
        MoveEntity();
        self->velocityY += FIX(0.25);
        posX = self->posX.i.hi;
        posY = self->posY.i.hi;
        g_api.CheckCollision(posX, posY + 0x1B, &collider, 0);
        if (collider.effects & EFFECT_SOLID) {
            self->posY.i.hi += collider.unk18;
            PlaySfxPositional(SFX_SKELETON_DEATH_A);
            func_us_801CDCC0(8);
        }
#endif
        break;
    case 8:
        if (self->facingLeft) {
            var_s3 = 0x1B;
        } else {
            var_s3 = -0x1B;
        }

        if (!AnimateEntity(D_us_80182928, self)) {
            primIndex = g_api.AllocPrimitives(PRIM_GT4, 1);
            if (primIndex != -1) {
                self->flags |= FLAG_HAS_PRIMS;
                self->primIndex = primIndex;
                prim = &g_PrimBuf[primIndex];
                self->ext.paranthropus.prim = prim;
                prim->tpage = 0x1A;
                prim->clut = 0x170;
                prim->u0 = 0;
                prim->u1 = 0x1F;
                prim->u2 = 0;
                prim->u3 = 0x1F;
                prim->v0 = 0;
                prim->v1 = 0;
                prim->v2 = 0x1F;
                prim->v3 = 0x1F;
                prim->x0 = self->posX.i.hi + var_s3;
                prim->y0 = self->posY.i.hi + 0x18;
                LOW(prim->x1) = LOW(prim->x0);
                LOW(prim->x2) = LOW(prim->x0);
                LOW(prim->x3) = LOW(prim->x0);
                PRED(prim) = 0;
                PGRN(prim) = 0;
                PBLU(prim) = 0;
                prim->priority = self->zPriority + 2;
                prim->drawMode |= DRAW_UNK02;
                prim->drawMode |= DRAW_COLORS;
                prim->drawMode |= DRAW_UNK_40 | DRAW_TPAGE | DRAW_TRANSP;
                func_us_801CDCC0(9);
                self->ext.paranthropus.unk7C = 0;
                self->ext.paranthropus.unk7F = 1;
                self->ext.paranthropus.unk84 = 0;
            } else {
                self->zPriority -= 2;
                if (self->facingLeft) {
                    var_s3 = 0x10;
                } else {
                    var_s3 = -0x10;
                }

                for (i = 0; i < 6; i++) {
                    entity = AllocEntity(&g_Entities[160], &g_Entities[192]);
                    if (entity != NULL) {
                        CreateEntityFromEntity(E_EXPLOSION, self, entity);
                        entity->params = EXPLOSION_SMALL_MULTIPLE;
                        entity->posX.i.hi += var_s3 + D_us_80182964[i].x;
                        entity->posY.i.hi += D_us_80182964[i].y;
                    }
                }

                DestroyEntity(self);
            }
        }
        break;
    case 9:
        self->ext.paranthropus.unk7C ^= 1;
        if (!self->ext.paranthropus.unk7C) {
            if (self->ext.paranthropus.unk7E) {
                self->ext.paranthropus.unk7F--;
                if (self->scaleX > 8) {
                    self->scaleX -= 8;
                    self->posY.val += FIX(0.8125);
                    if (self->facingLeft) {
                        self->posX.val += FIX(0.8125);
                    } else {
                        self->posX.val -= FIX(0.8125);
                    }
                }
                self->scaleY = self->scaleX;
            } else {
                if (self->ext.paranthropus.unk7F++ > 0x38) {
                    PlaySfxPositional(SFX_NOISE_SWEEP_DOWN_A);
                    self->ext.paranthropus.unk7E = 1;
                }
            }
            if (self->ext.paranthropus.unk7E) {
                var_s6 = -1;
                var_s5 = -(self->ext.paranthropus.unk7F % 2);
            } else {
                var_s6 = 1;
                var_s5 = self->ext.paranthropus.unk7F % 2;
            }

            // BUG! This looks like a copy paste mistake as this goes unused
            if (self->facingLeft) {
                var_s3 = 0x1B;
            } else {
                var_s3 = -0x1B;
            }

            prim = self->ext.paranthropus.prim;
            prim->x0 -= var_s6;
            prim->x1 += var_s6;
            prim->x2 -= var_s6;
            prim->x3 += var_s6;
            prim->y0 -= var_s5;
            prim->y1 -= var_s5;
            prim->y2 += var_s5;
            prim->y3 += var_s5;

            PRED(prim) = self->ext.paranthropus.unk7F;
            PGRN(prim) = self->ext.paranthropus.unk7F;
            PBLU(prim) = self->ext.paranthropus.unk7F;

            if (self->ext.paranthropus.unk7F == 0) {
                DestroyEntity(self);
            }
        }
        break;
    case 10:
        prim = self->ext.paranthropus.prim;
        var_s4 = self->ext.paranthropus.unk7F;
        PRED(prim) = var_s4;
        PGRN(prim) = var_s4;
        PBLU(prim) = var_s4;
        break;
    case 11:
        if ((!UnkCollisionFunc3(D_us_80182888)) & 1) {
            self->rotate += 0x10;
        }
        break;
    }

    if (self->facingLeft ^ self->ext.paranthropus.unk7D) {
        if (self->facingLeft) {
            self->posX.i.hi -= 0x10;
        } else {
            self->posX.i.hi += 0x10;
        }
    }

    if (self->animCurFrame >= 0x1D && self->animCurFrame < 0x22) {
        var_s4 = self->animCurFrame - 0x1D;
        self->hitboxWidth = D_us_80182990[var_s4].x;
        self->hitboxHeight = D_us_80182990[var_s4].y;
        self->hitboxOffX = D_us_8018297C[var_s4].x;
        self->hitboxOffY = D_us_8018297C[var_s4].y;
        return;
    }

    self->hitboxWidth = 0x12;
    self->hitboxHeight = 0x18;
    self->hitboxOffX = 0;
    self->hitboxOffY = 0;
}

void func_us_801CEB00(Entity* self) {
    if (self->flags & FLAG_DEAD) {
        DestroyEntity(self);
        return;
    }

    switch (self->step) {
    case 0:
        InitializeEntity(D_us_80180C0C);
        self->drawFlags |= FLAG_DRAW_ROTATE;
        if (self->facingLeft) {
            self->velocityX = FIX(2.0);
        } else {
            self->velocityX = FIX(-2.0);
        }
        self->velocityY = FIX(-6.0);
        break;
    case 1:
        MoveEntity();
        self->rotate -= 0x100;
        self->velocityY += FIX(0.25);
        break;
    }
}

void func_us_801CEBC8(Entity* self) {
    Entity* parent;
    u8 parentAnimFrame;

    if (!self->step) {
        InitializeEntity(D_us_80180C00);
    }

    parent = self - 1;

    parentAnimFrame = parent->animCurFrame;
    if (parentAnimFrame > 0x1D) {
        parentAnimFrame = 0;
    }

    self->hitboxOffX = D_us_801829D8[parentAnimFrame].x;
    self->hitboxOffY = D_us_801829D8[parentAnimFrame].y;
    self->hitboxWidth = D_us_80182A5C[parentAnimFrame][0] / 2;
    self->hitboxHeight = D_us_80182A5C[parentAnimFrame][1] / 2;
    self->facingLeft = parent->facingLeft;
    self->hitboxState = parent->hitboxState;
    self->posX.i.hi = parent->posX.i.hi;
    self->posY.i.hi = parent->posY.i.hi;

    if (parent->entityId != 0x3C) {
        DestroyEntity(self);
    }
}

void func_us_801CECAC(Entity* self) {
    u8 parentAnimFrame;
    Entity* parent;

    if (!self->step) {
        InitializeEntity(g_EInitInteractable);
        self->attack = 0;
        self->attackElement = ELEMENT_NONE;
    }

    parent = self - 2;
    parentAnimFrame = parent->animCurFrame;
    if (parentAnimFrame >= 0x21) {
        parentAnimFrame = 0;
    }

    if (parent->facingLeft) {
        self->posX.i.hi =
            (self - 2)->posX.i.hi - D_us_80182AE0[parentAnimFrame].x;
    } else {
        self->posX.i.hi =
            (self - 2)->posX.i.hi + D_us_80182AE0[parentAnimFrame].x;
    }
    self->posY.i.hi = (self - 2)->posY.i.hi + D_us_80182AE0[parentAnimFrame].y;

#ifdef VERSION_US
    parentAnimFrame = 0;
#endif
    if (parent->step < 7) {
        parentAnimFrame = GetPlayerCollisionWith(self, 8, 0xA, 4);
    }

    parent = &PLAYER;
    if (parentAnimFrame) {
        parent->posY.val += 0x20000;
    }

    if ((self - 2)->entityId != 0x3C) {
        DestroyEntity(self);
    }
}
