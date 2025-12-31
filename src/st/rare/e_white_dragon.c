// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rare.h"

extern u16 UNK_Invincibility0[];
extern EInit g_EInitSpawner;
extern EInit D_us_801807F0;

static s16 D_us_80181B64[] = {
    0x0008, 0x0007, 0x0006, 0x0005, 0x0004, 0x0003, 0x0002, 0x0001,
    0x0000, 0x0001, 0x0002, 0x0003, 0x0004, 0x0005, 0x0006, 0x0007};
static s16 D_us_80181B84[] = {
    0x0180, 0x0140, 0x0200, 0x0100, 0x00E0, 0x0150, 0x0120, 0x00C0};

void func_us_801B4F00(void) {
    s16 sp4E;              // sp4E
    s16 sp4C;              // sp4C
    u16 sp4A;              // sp4A
    s32 sp44;              // sp44
    s32 sp40;              // sp40
    s32 sp3C;              // sp3C
    Entity* currentEntity; // s0
    Primitive* prim;       // s1
    s32 var_s2;            // s2
    u8 var_s3;             // s3
    Entity* var_s4;        // s4
    s16 var_s8;            // s8
    s16 var_s7;            // s7
    s32 var_s6;            // s6
    s32 var_s5;            // s5

    currentEntity = g_CurrentEntity;
    var_s4 = g_CurrentEntity;
    sp4A = (var_s4 + 24)->palette & 0x7FFF;
    prim = var_s4->ext.et_801B4F00.prim;
    for (sp4E = 0x17; sp4E >= 0; sp4E--) {
        var_s8 = (currentEntity + 1)->ext.et_801B4F00.unk84;
        sp44 = GetSineScaled(currentEntity->ext.et_801B4F00.unk80, var_s8);
        var_s7 = (((0x100 - var_s8) * var_s4->ext.et_801B4F00.unk88) / 0xA0000);
        if (!var_s4->facingLeft) {
            var_s7 = -var_s7;
        }
        sp40 =
            GetSineScaled(currentEntity->ext.et_801B4F00.unk83 + 0x40, var_s7);
        sp3C = GetSineScaled(currentEntity->ext.et_801B4F00.unk83, var_s7);
        (currentEntity + 1)->ext.et_801B4F00.posY.val =
            currentEntity->ext.et_801B4F00.posY.val + sp44 + sp3C;
        (currentEntity + 1)->ext.et_801B4F00.posX.val =
            currentEntity->ext.et_801B4F00.posX.val + sp40;
        currentEntity++;

        currentEntity->posY.val =
            currentEntity->ext.et_801B4F00.posY.val - ((sp44 + sp3C) / 2);
        currentEntity->posX.val =
            currentEntity->ext.et_801B4F00.posX.val - (sp40 / 2);
        if (sp4E) {
            if ((sp4E ^ g_GameTimer) & 1) {
                currentEntity->hitboxState = g_api.enemyDefs[0x2B].hitboxState;
            } else {
                currentEntity->hitboxState = 0;
            }

            var_s8 = (currentEntity->ext.et_801B4F00.posX.i.hi -
                      (currentEntity - 1)->ext.et_801B4F00.posX.i.hi);
            sp4C = currentEntity->ext.et_801B4F00.posY.i.hi -
                   (currentEntity - 1)->ext.et_801B4F00.posY.i.hi;
            var_s3 = Ratan2Shifted(var_s8, sp4C);
            var_s6 = GetSineScaled(var_s3 + 0x20, 0xB5);
            var_s5 = GetSineScaled(var_s3 - 0x20, 0xB5);

            var_s2 = currentEntity->posX.val;
            prim->x0 = ((var_s2 + var_s6) >> 0x10);
            prim->x1 = ((var_s2 - var_s5) >> 0x10);
            prim->x2 = ((var_s2 + var_s5) >> 0x10);
            prim->x3 = ((var_s2 - var_s6) >> 0x10);

            var_s2 = currentEntity->posY.val;
            prim->y0 = ((var_s2 + var_s5) >> 0x10);
            prim->y1 = ((var_s2 + var_s6) >> 0x10);
            prim->y2 = ((var_s2 - var_s6) >> 0x10);
            prim->y3 = ((var_s2 - var_s5) >> 0x10);

            prim->clut = sp4A;
            prim->drawMode = DRAW_COLORS | DRAW_UNK02;
            prim->priority =
                var_s4->zPriority +
                D_us_80181B64
                    [((currentEntity->ext.et_801B4F00.unk80 + 8) / 16) & 0xF];
            prim = prim->next;
        } else {
            if (var_s4->facingLeft) {
                currentEntity->posX.i.hi += 8;
            } else {
                currentEntity->posX.i.hi -= 8;
            }
            var_s3 = currentEntity->ext.et_801B4F00.unk82;
            if (currentEntity->facingLeft) {
                var_s3 ^= 0xFF;
                var_s3 += 0x41;
            } else {
                var_s3 += 0x40;
            }
            currentEntity->rotate = (var_s3 & 0xFFFF) * 0x10;
            currentEntity->zPriority =
                var_s4->zPriority +
                D_us_80181B64
                    [((currentEntity->ext.et_801B4F00.unk80 + 8) / 16) & 0xF];
        }

        currentEntity->hitParams = 0;
        currentEntity->hitFlags = 0;
    }
}

void func_us_801B5250(void) {
    u8 x[] = {0x00, 0x10, 0xE8, 0x18, 0xF0, 0x10, 0xE8, 0x08};
    Entity* var_s0;
    Entity* currentEntity; // s1
    u8 var_s2;
    s16 j; // s3
    s32 i; // s4

    currentEntity = g_CurrentEntity;
    if (LOHU(currentEntity->ext.et_801B4F00.unk98) != 0x300) {
        if (LOHU(currentEntity->ext.et_801B4F00.unk98) < 0x300) {
            LOHU(currentEntity->ext.et_801B4F00.unk98) += 0x18;
        } else {
            LOHU(currentEntity->ext.et_801B4F00.unk98) -= 0x18;
        }
    }
    if (currentEntity->facingLeft) {
        currentEntity->ext.et_801B4F00.unk80 -=
            currentEntity->ext.et_801B4F00.unk99;
    } else {
        currentEntity->ext.et_801B4F00.unk80 +=
            currentEntity->ext.et_801B4F00.unk99;
    }
    if (currentEntity->ext.et_801B4F00.unk88 < 0x60000) {
        currentEntity->ext.et_801B4F00.unk88 += 0x400;
    }

    var_s0 = currentEntity;
    for (j = 0x17; j >= 0; j--) {
        var_s0++;
        if (var_s0->ext.et_801B4F00.unk84 < var_s0->ext.et_801B4F00.unk86) {
            var_s0->ext.et_801B4F00.unk84 += 2;
        }
        var_s0->ext.et_801B4F00.unk80 = (var_s0 - 1)->ext.et_801B4F00.unk80 -
                                        currentEntity->ext.et_801B4F00.unk81;
        if (j) {
            var_s0->ext.et_801B4F00.unk83 = (var_s0 + 1)->ext.et_801B4F00.unk83;
        } else {
            var_s2 = var_s0->ext.et_801B4F00.unk83 -
                     currentEntity->ext.et_801B4F00.unk9C;
            if (var_s2) {
                if (!(var_s2 & 0x80) &&
                    (((var_s0->ext.et_801B4F00.unk80) - 0x40) & 0x80)) {
                    var_s0->ext.et_801B4F00.unk83--;
                }
                if ((var_s2 & 0x80) &&
                    (((var_s0->ext.et_801B4F00.unk80) + 0x40) & 0x80)) {
                    var_s0->ext.et_801B4F00.unk83++;
                }
            } else {
                currentEntity->ext.et_801B4F00.unk9D++;
                currentEntity->ext.et_801B4F00.unk9C =
                    x[currentEntity->ext.et_801B4F00.unk9D & 7];
            }
        }
    }
}

void func_us_801B5408(void) {
    Entity* entity;
    u8 var_s1;

    entity = g_CurrentEntity + 24;
    var_s1 = entity->ext.et_801B4F00.unk82 - entity->ext.et_801B4F00.unk9E;
    if (var_s1) {
        if (var_s1 & 0x80) {
            entity->ext.et_801B4F00.unk82++;
        } else {
            entity->ext.et_801B4F00.unk82--;
        }
    }
}

void func_us_801B5448(Entity* self) {
    u16 iFramePalette;
    u16 unused;
    s8 anim_one[] = {0x05, 0x02, 0x05, 0x03, 0x05, 0x04, 0xFF};
    s8 anim_two[] = {0x05, 0x03, 0x05, 0x02, 0x05, 0x01, 0xFF};
    Entity* entity;     // s0
    Primitive* prim;    // s1
    s16 i;              // s2
    u8 angle;           // s3
    s16 j;              // s4
    u8 color;           // s5
    Entity* var_s7;     // s7
    EnemyDef* enemyDef; // s6
    s32 primIndex;      // s8

    self->ext.et_801B4F00.posX.val = self->posX.val;
    self->ext.et_801B4F00.posY.val = self->posY.val;
    entity = self;

    for (i = 0x17; i >= 0; i--) {
        entity++;
        if (entity->flags & FLAG_NOT_AN_ENEMY) {
            entity = self;
            for (j = 0x17; j >= 0; j--) {
                entity++;
                entity->flags |= FLAG_NOT_AN_ENEMY;
            }
            break;
        }
    }

    entity = self + 24;
    if (entity->flags & 0xF) {
        iFramePalette = entity->nFramesInvincibility << 1;
        iFramePalette += entity->flags & 1;
        entity->palette = UNK_Invincibility0[iFramePalette];
        if (!(--entity->flags & 0xF)) {
            entity->palette = entity->hitEffect;
            entity->hitEffect = 0;
        }
    }

    if (g_unkGraphicsStruct.D_800973FC && !(entity->flags & FLAG_DEAD) &&
        self->step && (g_GameTimer & 3)) {
        func_us_801B5408();
        func_us_801B4F00();
        return;
    }

    if ((entity->hitFlags & 0xF) && self->step == 1) {
        self->step = 3;
        self->ext.et_801B4F00.unk96 = 8;
        g_api.PlaySfx(SFX_RARE_FM_IMPACT);
    }

    if ((entity->flags & FLAG_DEAD) && self->step != 5) {
        self->step = 5;
        self->ext.et_801B4F00.unk96 = 0x80;
        self->ext.et_801B4F00.unkA0 = 0x400;

        entity = self;
        for (i = 0x17; i >= 0; i--) {
            entity++;
            entity->flags |= FLAG_DEAD;
        }
    }

    switch (self->step) {
    case 0:
        if (!self->step_s) {
            InitializeEntity(g_EInitSpawner);
            self->step = 0;
            self->step_s++;
            self->flags |=
                FLAG_POS_CAMERA_LOCKED | FLAG_UNK_400000 | FLAG_UNK_10;
            self->facingLeft = self->params & 1;
            enemyDef = &g_api.enemyDefs[0x2B];

            entity = self;
            for (i = 0x17; i >= 0; i--) {
                entity->unk60 = entity + 1;
                entity++;
                DestroyEntity(entity);

                entity->entityId = 0x28;
                entity->enemyId = 0x2B;
                entity->ext.et_801B4F00.posX.val = self->posX.val;
                entity->ext.et_801B4F00.posY.val = self->posY.val;
                entity->params = i;
                entity->ext.et_801B4F00.entity = self;
                entity->ext.et_801B4F00.unk84 = ((0x18 - i) * 256) / 24;
                entity->ext.et_801B4F00.unk86 = entity->ext.et_801B4F00.unk84;
                entity->facingLeft = self->facingLeft;
                entity->attackElement = 1;
                entity->attack = 1;
                if (!i) {
                    entity->drawFlags = FLAG_DRAW_ROTATE;
                    entity->animSet = -0x7FFF;
                    entity->animCurFrame = 1;
                    entity->unk5A = 0x57;
                    entity->palette = 0x216;
                    entity->animSet = -0x7FFA;
                    entity->unk5A = 0x4B;
                    entity->palette = 0x217;
                    entity->hitboxWidth = 8;
                    entity->hitboxHeight = 8;
                    entity->hitPoints = enemyDef->hitPoints;
                    entity->hitboxState = enemyDef->hitboxState;
                    entity->entityRoomIndex = self->entityRoomIndex;
                    entity->flags |= FLAG_POS_CAMERA_LOCKED | FLAG_UNK_400000;
                    entity->unk60 = self;
                } else {
                    entity->hitPoints = 0x7FFF;
                    entity->hitboxWidth = 4;
                    entity->hitboxHeight = 4;
                }
            }

            self->ext.et_801B4F00.unk94 = 0x200;
            self->ext.et_801B4F00.unk9A = 0x280;
            LOHU(self->ext.et_801B4F00.unk98) = 0x400;
            self->ext.et_801B4F00.unk88 = 0x20000;

            entity = self + 24;
            if (self->facingLeft) {
                entity->ext.et_801B4F00.unk82 = 0x40;
                entity->ext.et_801B4F00.unk9E = 0x40;
                self->ext.et_801B4F00.unk81 = 0x10;
            } else {
                entity->ext.et_801B4F00.unk82 = 0xC0;
                entity->ext.et_801B4F00.unk9E = 0xC0;
                self->ext.et_801B4F00.unk81 = 0xF0;
            }
        }

        primIndex = g_api.AllocPrimitives(PRIM_GT4, 0x17);
        if (primIndex != -1) {
            self->primIndex = primIndex;
            prim = &g_PrimBuf[primIndex];
            self->ext.et_801B4F00.prim = prim;
            self->flags |= FLAG_HAS_PRIMS;

            color = 0x38;
            while (prim != NULL) {
                prim->tpage = 0x12;
                prim->clut = 0x217;
                prim->u0 = 0xA0;
                prim->u1 = 0xB0;
                prim->u2 = 0xA0;
                prim->u3 = 0xB0;
                PRED(prim) = color;
                PGRN(prim) = color;
                PBLU(prim) = color;
                color += 3;
                if (self->facingLeft) {
                    prim->v0 = 0xAF;
                    prim->v1 = 0xAF;
                    prim->v2 = 0x9F;
                    prim->v3 = 0x9F;
                } else {
                    prim->v0 = 0xA0;
                    prim->v1 = 0xA0;
                    prim->v2 = 0xB0;
                    prim->v3 = 0xB0;
                }
                prim->drawMode = DRAW_HIDE;
                prim = prim->next;
            }
            self->step++;
            self->step_s = 0;
        }
        break;
    case 1:
        func_us_801B5408();
        func_us_801B5250();
        func_us_801B4F00();
        if (self->posX.i.hi >= -0xC0 && self->posX.i.hi < 0x1C1 &&
            self->posY.i.hi >= -0x80 && self->posY.i.hi < 0x161) {
            if (self->ext.et_801B4F00.unk94) {
                self->ext.et_801B4F00.unk94--;
            } else {
                angle = GetAngleBetweenEntitiesShifted(self, &PLAYER);
                if (self->facingLeft) {
                    angle -= 0x20;
                } else {
                    angle -= 0xA0;
                }

                if (angle < 0x41) {
                    self->step = 4;
                    self->step_s = 0;
                    self->ext.et_801B4F00.unk96 = 0x10;
                    self->ext.et_801B4F00.unk9F = Random() & 1;
                    self->ext.et_801B4F00.unkA4 = 0;
                }
                self->ext.et_801B4F00.unk94 = D_us_80181B84[Random() & 7];
            }

            if (self->ext.et_801B4F00.unk9A) {
                self->ext.et_801B4F00.unk9A--;
                return;
            }

            angle = GetAngleBetweenEntitiesShifted(self, &PLAYER);
            if (self->facingLeft) {
                angle -= 0x20;
            } else {
                angle -= 0xA0;
            }

            if (angle < 0x41) {
                self->step++;
                self->step_s = 0;
                self->ext.et_801B4F00.unk96 = 0x60;
            }
            self->ext.et_801B4F00.unk9A = 0x200;
        }
        break;
    case 2:
        switch (self->step_s) {
        case 0:
            if (LOHU(self->ext.et_801B4F00.unk98) < 0x600) {
                LOHU(self->ext.et_801B4F00.unk98) += 0x18;
            }

            if (self->facingLeft) {
                self->ext.et_801B4F00.unk80 -= self->ext.et_801B4F00.unk99;
            } else {
                self->ext.et_801B4F00.unk80 += self->ext.et_801B4F00.unk99;
            }

            if (self->ext.et_801B4F00.unk88 > 0x28000) {
                self->ext.et_801B4F00.unk88 -= 0x1000;
            }

            entity = self;
            for (i = 0x17; i >= 0; i--) {
                entity++;
                if (entity->ext.et_801B4F00.unk84 > 0xA0) {
                    entity->ext.et_801B4F00.unk84 -= 8;
                }

                entity->ext.et_801B4F00.unk80 =
                    (entity - 1)->ext.et_801B4F00.unk80 -
                    self->ext.et_801B4F00.unk81;
                if (i) {
                    entity->ext.et_801B4F00.unk83 =
                        (entity + 1)->ext.et_801B4F00.unk83;
                } else {
                    angle = entity->ext.et_801B4F00.unk83;
                    if (angle) {
                        if (!(angle & 0x80) &&
                            (((entity->ext.et_801B4F00.unk80) - 0x40) & 0x80)) {
                            entity->ext.et_801B4F00.unk83--;
                        }

                        if ((angle & 0x80) &&
                            (((entity->ext.et_801B4F00.unk80) + 0x40) & 0x80)) {
                            entity->ext.et_801B4F00.unk83++;
                        }
                    }
                }
            }

            if (self->ext.et_801B4F00.unk96) {
                self->ext.et_801B4F00.unk96--;
            } else {
                angle = GetAngleBetweenEntitiesShifted(self, &PLAYER);
                if (self->facingLeft) {
                    self->ext.et_801B4F00.unk82 = angle - 0x40;
                } else {
                    self->ext.et_801B4F00.unk82 = angle + 0x40;
                }
                entity->ext.et_801B4F00.unk9E = angle;
                self->step_s++;
            }
            break;
        case 1:
            func_us_801B5408();
            if (self->facingLeft) {
                self->ext.et_801B4F00.unk80 -= self->ext.et_801B4F00.unk99;
            } else {
                self->ext.et_801B4F00.unk80 += self->ext.et_801B4F00.unk99;
            }

            entity = self;
            var_s7 = self + 24;
            for (i = 0x17; i >= 0; i--) {
                entity++;
                entity->ext.et_801B4F00.unk80 =
                    (entity - 1)->ext.et_801B4F00.unk80 -
                    self->ext.et_801B4F00.unk81;
                angle =
                    entity->ext.et_801B4F00.unk83 - self->ext.et_801B4F00.unk82;
                if (angle) {
                    if (angle & 0x80) {
                        if ((var_s7->ext.et_801B4F00.unk80 + 0x40) & 0x80) {
                            if (angle > 0xFC) {
                                entity->ext.et_801B4F00.unk83 -= angle;
                            } else {
                                entity->ext.et_801B4F00.unk83 += 4;
                            }
                        }
                    } else {
                        if ((var_s7->ext.et_801B4F00.unk80 - 0x40) & 0x80) {
                            if (angle < 4) {
                                entity->ext.et_801B4F00.unk83 -= angle;
                            } else {
                                entity->ext.et_801B4F00.unk83 -= 4;
                            }
                        }
                    }
                } else {
                    g_api.PlaySfx(SFX_SCRAPE_B);
                    self->step_s++;
                    self->ext.et_801B4F00.unk96 = 0x40;
                    entity = (self + 24);
                    entity->attackElement = 1;
                    entity->attack = 8;
                    break;
                }
            }

            break;
        case 2:
            func_us_801B5408();
            if (LOHU(self->ext.et_801B4F00.unk98) > 0x400) {
                LOHU(self->ext.et_801B4F00.unk98) -= 0x40;
            }

            if (self->facingLeft) {
                self->ext.et_801B4F00.unk80 -= self->ext.et_801B4F00.unk99;
            } else {
                self->ext.et_801B4F00.unk80 += self->ext.et_801B4F00.unk99;
            }

            entity = self;
            for (i = 0x17; i >= 0; i--) {
                entity++;
                entity->ext.et_801B4F00.unk80 =
                    (entity - 1)->ext.et_801B4F00.unk80 -
                    self->ext.et_801B4F00.unk81;
                if (entity->ext.et_801B4F00.unk84 > 0x20) {
                    entity->ext.et_801B4F00.unk84 -= 0x10;
                }
            }

            if (self->ext.et_801B4F00.unk88 < 0x60000) {
                self->ext.et_801B4F00.unk88 += 0x4650;
            } else {
                entity = self + 24;
                entity->attackElement = 1;
                entity->attack = 1;
            }

            if (self->ext.et_801B4F00.unk96) {
                self->ext.et_801B4F00.unk96--;
            } else {
                self->step -= 1;
                self->step_s = 0;
                if (self->facingLeft) {
                    entity->ext.et_801B4F00.unk9E = 0x40;
                } else {
                    entity->ext.et_801B4F00.unk9E = 0xC0;
                }
            }
            break;
        }
        func_us_801B4F00();
        return;
    case 3:
        if (self->ext.et_801B4F00.unk88 < 0x38001) {
            self->ext.et_801B4F00.unk88 = 0x38000;
            if (self->ext.et_801B4F00.unk96) {
                self->ext.et_801B4F00.unk96--;
            } else {
                self->step = 1;
                LOH(self->ext.et_801B4F00.unk98) = 0;
            }
        } else {
            self->ext.et_801B4F00.unk88 -= 0x4000;
        }
        func_us_801B4F00();
        break;
    case 4:
        if (self->ext.et_801B4F00.unk9F) {
            entity = self + 24;
            angle =
                entity->ext.et_801B4F00.unk82 - entity->ext.et_801B4F00.unk9E;
            if (angle) {
                if (angle & 0x80) {
                    entity->ext.et_801B4F00.unk82 += 2;
                } else {
                    entity->ext.et_801B4F00.unk82 -= 2;
                }
            }
        } else {
            func_us_801B5408();
        }

        switch (self->step_s) {
        case 0:
            LOHU(self->ext.et_801B4F00.unk98) -= 0xA0;
            if (LOHU(self->ext.et_801B4F00.unk98) & 0x8000) {
                LOHU(self->ext.et_801B4F00.unk98) = 0;
                self->step_s++;
                entity = self + 24;
                angle = GetAngleBetweenEntitiesShifted(entity, &PLAYER);
                if (!self->ext.et_801B4F00.unk9F) {
                    entity->ext.et_801B4F00.unk9E = angle;
                } else {
                    self->ext.et_801B4F00.unk9E = angle;
                }
                entity->pose = 0;
                entity->poseTimer = 0;
            } else {
                func_us_801B5250();
            }
            break;
        case 1:
            AnimateEntity(&anim_one, self + 24);
            entity = AllocEntity(&g_Entities[160], &g_Entities[192]);
            if (entity != NULL && self->ext.et_801B4F00.unk96) {
                self->ext.et_801B4F00.unk96--;
                DestroyEntity(entity);
                CreateEntityFromEntity(E_UNK_29, self + 24, entity);
                entity->ext.et_801B4F00.entity = self + 24;
                entity->facingLeft = self->facingLeft;
                if (self->ext.et_801B4F00.unk9F) {
                    entity->params = self->ext.et_801B4F00.unkA4 + 0x80;
                    self->ext.et_801B4F00.unkA4++;
                } else if (self->ext.et_801B4F00.unk96 == 0xF) {
                    entity->params = 1;
                }
                entity->zPriority = self->zPriority + 9;
            } else {
                self->step_s += 1;
                self->ext.et_801B4F00.unk96 = 0x30;
                entity = self + 24;
                entity->pose = 0;
                entity->poseTimer = 0;
            }
            break;
        case 2:
            entity = self + 24;
            if (self->ext.et_801B4F00.unk96) {
                if (self->ext.et_801B4F00.unk96 == 0x18) {
                    g_api.PlaySfx(SFX_EXPLODE_B);
                    if (self->ext.et_801B4F00.unk9F) {
                        if ((entity->ext.et_801B4F00.unk9E -
                             self->ext.et_801B4F00.unk9E) &
                            0x80) {
                            entity->ext.et_801B4F00.unk9E += 0x20;
                        } else {
                            entity->ext.et_801B4F00.unk9E -= 0x20;
                        }
                    }
                }

                if (self->ext.et_801B4F00.unk96 < 0x19) {
                    AnimateEntity(&anim_two, self + 24);
                }
                self->ext.et_801B4F00.unk96--;
            } else {
                self->step = 1;
                self->step_s = 0;
                if (self->facingLeft) {
                    entity->ext.et_801B4F00.unk9E = 0x40;
                } else {
                    entity->ext.et_801B4F00.unk9E = 0xC0;
                }
            }
            break;
        }
        func_us_801B4F00();
        break;
    case 5:
        if (self->ext.et_801B4F00.unk88 < 0x50000) {
            self->ext.et_801B4F00.unkA0 = 0x4000;
        }

        if (self->ext.et_801B4F00.unk88 > 0x60000) {
            self->ext.et_801B4F00.unkA0 = -0x4000;
        }

        self->ext.et_801B4F00.unk88 += self->ext.et_801B4F00.unkA0;
        if (LOHU(self->ext.et_801B4F00.unk98) < 0x1000) {
            LOHU(self->ext.et_801B4F00.unk98) += 0x20;
        }

        if (self->facingLeft) {
            self->ext.et_801B4F00.unk80 -= self->ext.et_801B4F00.unk99;
        } else {
            self->ext.et_801B4F00.unk80 += self->ext.et_801B4F00.unk99;
        }

        entity = self;
        for (i = 0x17; i >= 0; i--) {
            entity++;
            if (entity->ext.et_801B4F00.unk84 < entity->ext.et_801B4F00.unk86) {
                entity->ext.et_801B4F00.unk84 += 2;
            }
            entity->ext.et_801B4F00.unk80 =
                (entity - 1)->ext.et_801B4F00.unk80 -
                self->ext.et_801B4F00.unk81;
            if (i) {
                entity->ext.et_801B4F00.unk83 =
                    (entity + 1)->ext.et_801B4F00.unk83;
            } else {
                angle = entity->ext.et_801B4F00.unk83;
                if (angle) {
                    if (!(angle & 0x80) &&
                        ((entity->ext.et_801B4F00.unk80 - 0x40) & 0x80)) {
                        entity->ext.et_801B4F00.unk83--;
                    }

                    if ((angle & 0x80) &&
                        ((entity->ext.et_801B4F00.unk80 + 0x40) & 0x80)) {
                        entity->ext.et_801B4F00.unk83++;
                    }
                }
            }
        }

        func_us_801B4F00();
        if (self->ext.et_801B4F00.unk96) {
            self->ext.et_801B4F00.unk96--;

            if (!(self->ext.et_801B4F00.unk96 & 7)) {
                g_api.PlaySfx(SFX_EXPLODE_FAST_B);
            }

            if (!(self->ext.et_801B4F00.unk96 & 1)) {
                entity = AllocEntity(
                    &g_Entities[224], &g_Entities[TOTAL_ENTITY_COUNT]);
                if (entity != NULL) {
                    CreateEntityFromEntity(E_EXPLOSION, self + 24, entity);
                    entity->params = EXPLOSION_FIREBALL;
                    entity->posX.i.hi += (s16)(Random() & 0x1F) - 0x10;
                    entity->zPriority = self->zPriority + 9;
                }
            }
        } else {
            entity = self;
            for (i = 0x17; i >= 0; i--) {
                entity++;
                entity->drawFlags = FLAG_DRAW_DEFAULT;
                if (i & 1) {
                    entity->entityId = 2;
                    entity->pfnUpdate = EntityExplosion;
                    entity->params = 1;
                } else {
                    j = self->params >> 1;
                    if (j) {
                        entity->entityId = 3;
                        entity->pfnUpdate = EntityPrizeDrop;
                        entity->params = j;
                        entity->zPriority = 0;
                        entity->animCurFrame = 0;
                    } else {
                        DestroyEntity(entity);
                    }
                }
            }
            DestroyEntity(self);
            g_api.PlaySfx(SFX_FIREBALL_SHOT_A);
            g_api.func_80102CD8(1);
        }
        break;
    }
}

void func_us_801B6578(Entity* self) {
    Entity* entity;

    entity = self->ext.et_801B4F00.entity;
    SetEntityVelocityFromAngle(entity->ext.et_801B4F00.unk82, 0x60);
    self->posX.val = entity->posX.val + self->velocityX;
    self->posY.val = entity->posY.val + self->velocityY;

    entity = entity - 24;
    if (entity->step == 5) {
        DestroyEntity(self);
    }
}

// nb. This data must be defined down here since the inline data inside funcs
// goes into data on PSP but rodata on PSX.
static u8 D_us_80181B94[] = {0x40, 0x60, 0x20, 0x50, 0x30, 0x10, 0x50, 0x70,
                             0x40, 0x30, 0x60, 0x20, 0x70, 0x10, 0x30, 0x50};
static u8 D_us_80181BA4[] = {
    0x01, 0x01, 0x01, 0x02, 0x01, 0x01, 0x01, 0x02, 0x01, 0x01, 0x01,
    0x02, 0x01, 0x01, 0x01, 0x02, 0x01, 0x01, 0x01, 0x02, 0x01, 0x01,
    0x01, 0x02, 0x01, 0x01, 0x01, 0x02, 0x01, 0x03, 0x01, 0x04, 0x01,
    0x05, 0x01, 0x06, 0x01, 0x07, 0x01, 0x08, 0xFF, 0x00, 0x00, 0x00};
static u8 D_us_80181BD0[] = {
    0x02, 0x01, 0x02, 0x02, 0x02, 0x03, 0x02, 0x04, 0x02, 0x05,
    0x02, 0x06, 0x02, 0x07, 0x02, 0x08, 0x00, 0x00, 0x00, 0x00,
};

void func_us_801B65F8(Entity* self) {
    s16 var_s0;        // s0
    Entity* entity;    // s1
    s32 prevVelocityX; // s4
    s32 prevVelocityY; // s3
    u8 var_s2;         // s2

    switch (self->step) {
    case 0:
        InitializeEntity(D_us_801807F0);
        self->zPriority += 1;
        self->hitboxState = 0;
        self->drawMode = DRAW_TPAGE2 | DRAW_TPAGE;
        entity = self->ext.et_801B4F00.entity;
        SetEntityVelocityFromAngle(entity->ext.et_801B4F00.unk82, 0x60);
        LOWU(self->ext.et_801B4F00.unk80) = 0x28;
        return;
    case 1:
        if (self->params == 1) {
            AnimateEntity(D_us_80181BD0, self);
        }

        if (!--LOWU(self->ext.et_801B4F00.unk80)) {
            SetStep(2);
            self->zPriority = g_unkGraphicsStruct.g_zEntityCenter - 0xC;
            self->hitboxState = 1;
            self->ext.et_801B4F00.unk84 = 0;
            self->drawFlags = FLAG_DRAW_SCALEY | FLAG_DRAW_SCALEX;
        }

        func_us_801B6578(self);
        if (self->params & 0x80) {
            if (LOWU(self->ext.et_801B4F00.unk80) < 0x10) {
                self->animCurFrame = 0;
                return;
            }

            AnimateEntity(D_us_80181BD0, self);
            // HACK: bit ugly, can this be rewritten?
            var_s0 = (s16)(LOWU(self->ext.et_801B4F00.unk80) - 0x10) * 32;
            var_s2 = self->params & 0x7F;
            prevVelocityX = self->velocityX;
            prevVelocityY = self->velocityY;
            SetEntityVelocityFromAngle(D_us_80181B94[var_s2], var_s0);
            if (!self->facingLeft) {
                self->velocityX = -self->velocityX;
            }
            MoveEntity();
            self->velocityX = prevVelocityX;
            self->velocityY = prevVelocityY;
        }
        break;
    case 2:
        if (!AnimateEntity(D_us_80181BA4, self)) {
            DestroyEntity(self);
        }

        MoveEntity();
        if (self->animCurFrame > 6) {
            self->hitboxState = 0;
        }

        var_s0 = self->ext.et_801B4F00.unk84 * 32;
        self->scaleX = var_s0;
        self->scaleY = var_s0;

        var_s0 = self->ext.et_801B4F00.unk84;
        self->hitboxHeight = var_s0;
        self->ext.et_801B4F00.unk84++;
        break;
    }
}
