// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rare.h"

extern u16 UNK_Invincibility0[];
extern EInit g_EInitSpawner;
extern EInit D_us_801807F0;

static s16 z_priorities[] = {8, 7, 6, 5, 4, 3, 2, 1, 0, 1, 2, 3, 4, 5, 6, 7};
static s16 attack_timers[] = {
    0x0180, 0x0140, 0x0200, 0x0100, 0x00E0, 0x0150, 0x0120, 0x00C0};

#define WHITE_DRAGON_ID 0x2B
#define SEGMENT_COUNT 24

static void func_us_801B4F00(void) {
    s16 i;
    s16 dy;
    u16 palette;
    s32 baseSine;
    s32 sineX;
    s32 sineY;
    Entity* currentEntity;
    Primitive* prim;
    s32 var_s2;
    u8 angle;
    Entity* var_s4;
    s16 dx;
    s16 var_s7;
    s32 var_s6;
    s32 var_s5;

    currentEntity = g_CurrentEntity;
    var_s4 = g_CurrentEntity;
    palette = (var_s4 + SEGMENT_COUNT)->palette & 0x7FFF;
    prim = var_s4->ext.whiteDragon.prim;
    for (i = SEGMENT_COUNT - 1; i >= 0; i--) {
        dx = (currentEntity + 1)->ext.whiteDragon.unk84;
        baseSine = GetSineScaled(currentEntity->ext.whiteDragon.unk80, dx);
        var_s7 = (((0x100 - dx) * var_s4->ext.whiteDragon.unk88) / 0xA0000);
        if (!var_s4->facingLeft) {
            var_s7 = -var_s7;
        }
        sineX =
            GetSineScaled(currentEntity->ext.whiteDragon.unk83 + 0x40, var_s7);
        sineY = GetSineScaled(currentEntity->ext.whiteDragon.unk83, var_s7);
        (currentEntity + 1)->ext.whiteDragon.posY.val =
            currentEntity->ext.whiteDragon.posY.val + baseSine + sineY;
        (currentEntity + 1)->ext.whiteDragon.posX.val =
            currentEntity->ext.whiteDragon.posX.val + sineX;
        currentEntity++;

        currentEntity->posY.val =
            currentEntity->ext.whiteDragon.posY.val - ((baseSine + sineY) / 2);
        currentEntity->posX.val =
            currentEntity->ext.whiteDragon.posX.val - (sineX / 2);
        if (i) {
            if ((i ^ g_GameTimer) & 1) {
                currentEntity->hitboxState =
                    g_api.enemyDefs[WHITE_DRAGON_ID].hitboxState;
            } else {
                currentEntity->hitboxState = 0;
            }

            dx = (currentEntity->ext.whiteDragon.posX.i.hi -
                  (currentEntity - 1)->ext.whiteDragon.posX.i.hi);
            dy = currentEntity->ext.whiteDragon.posY.i.hi -
                 (currentEntity - 1)->ext.whiteDragon.posY.i.hi;
            angle = Ratan2Shifted(dx, dy);
            var_s6 = GetSineScaled(angle + 0x20, 0xB5);
            var_s5 = GetSineScaled(angle - 0x20, 0xB5);

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

            prim->clut = palette;
            prim->drawMode = DRAW_COLORS | DRAW_UNK02;
            prim->priority =
                var_s4->zPriority +
                z_priorities[((currentEntity->ext.whiteDragon.unk80 + 8) / 16) &
                             0xF];
            prim = prim->next;
        } else {
            if (var_s4->facingLeft) {
                currentEntity->posX.i.hi += 8;
            } else {
                currentEntity->posX.i.hi -= 8;
            }
            angle = currentEntity->ext.whiteDragon.angle;
            if (currentEntity->facingLeft) {
                angle ^= 0xFF;
                angle += 0x41;
            } else {
                angle += 0x40;
            }
            currentEntity->rotate = (angle & 0xFFFF) * 0x10;
            currentEntity->zPriority =
                var_s4->zPriority +
                z_priorities[((currentEntity->ext.whiteDragon.unk80 + 8) / 16) &
                             0xF];
        }

        currentEntity->hitParams = 0;
        currentEntity->hitFlags = 0;
    }
}

static void func_us_801B5250(void) {
    u8 x[] = {0x00, 0x10, 0xE8, 0x18, 0xF0, 0x10, 0xE8, 0x08};
    Entity* var_s0;
    Entity* currentEntity;
    u8 var_s2;
    s16 j;
    s32 i;

    currentEntity = g_CurrentEntity;
    if (LOHU(currentEntity->ext.whiteDragon.unk98) != 0x300) {
        if (LOHU(currentEntity->ext.whiteDragon.unk98) < 0x300) {
            LOHU(currentEntity->ext.whiteDragon.unk98) += 0x18;
        } else {
            LOHU(currentEntity->ext.whiteDragon.unk98) -= 0x18;
        }
    }
    if (currentEntity->facingLeft) {
        currentEntity->ext.whiteDragon.unk80 -=
            currentEntity->ext.whiteDragon.unk99;
    } else {
        currentEntity->ext.whiteDragon.unk80 +=
            currentEntity->ext.whiteDragon.unk99;
    }
    if (currentEntity->ext.whiteDragon.unk88 < 0x60000) {
        currentEntity->ext.whiteDragon.unk88 += 0x400;
    }

    var_s0 = currentEntity;
    for (j = SEGMENT_COUNT - 1; j >= 0; j--) {
        var_s0++;
        if (var_s0->ext.whiteDragon.unk84 < var_s0->ext.whiteDragon.unk86) {
            var_s0->ext.whiteDragon.unk84 += 2;
        }
        var_s0->ext.whiteDragon.unk80 = (var_s0 - 1)->ext.whiteDragon.unk80 -
                                        currentEntity->ext.whiteDragon.unk81;
        if (j) {
            var_s0->ext.whiteDragon.unk83 = (var_s0 + 1)->ext.whiteDragon.unk83;
        } else {
            var_s2 = var_s0->ext.whiteDragon.unk83 -
                     currentEntity->ext.whiteDragon.unk9C;
            if (var_s2) {
                if (!(var_s2 & 0x80) &&
                    (((var_s0->ext.whiteDragon.unk80) - 0x40) & 0x80)) {
                    var_s0->ext.whiteDragon.unk83--;
                }
                if ((var_s2 & 0x80) &&
                    (((var_s0->ext.whiteDragon.unk80) + 0x40) & 0x80)) {
                    var_s0->ext.whiteDragon.unk83++;
                }
            } else {
                currentEntity->ext.whiteDragon.unk9D++;
                currentEntity->ext.whiteDragon.unk9C =
                    x[currentEntity->ext.whiteDragon.unk9D & 7];
            }
        }
    }
}

static void func_us_801B5408(void) {
    Entity* headEntity;
    u8 var_s1;

    headEntity = g_CurrentEntity + SEGMENT_COUNT;
    var_s1 =
        headEntity->ext.whiteDragon.angle - headEntity->ext.whiteDragon.unk9E;
    if (var_s1) {
        if (var_s1 & 0x80) {
            headEntity->ext.whiteDragon.angle++;
        } else {
            headEntity->ext.whiteDragon.angle--;
        }
    }
}

enum WhiteDragonSteps {
    INIT = 0,
    IDLE_MOVE = 1,
    CHARGE_PLAYER = 2,
    HIT_BY_PLAYER = 3,
    FLAME_BREATH = 4,
    DEATH = 5
};

void EntityWhiteDragon(Entity* self) {

    s8 anim_mouth_open[] = {0x05, 0x02, 0x05, 0x03, 0x05, 0x04, 0xFF};
    s8 anim_breathe_fire[] = {0x05, 0x03, 0x05, 0x02, 0x05, 0x01, 0xFF};
    u16 iFramePalette;
    u16 unused;
    Entity* entity;
    Primitive* prim;
    s16 i;
    u8 angle;
    s16 j;
    u8 segmentColor;
    Entity* var_s7;
    EnemyDef* enemyDef;
    s32 primIndex;

    self->ext.whiteDragon.posX.val = self->posX.val;
    self->ext.whiteDragon.posY.val = self->posY.val;
    entity = self;

    for (i = SEGMENT_COUNT - 1; i >= 0; i--) {
        entity++;
        if (entity->flags & FLAG_NOT_AN_ENEMY) {
            entity = self;
            for (j = SEGMENT_COUNT - 1; j >= 0; j--) {
                entity++;
                entity->flags |= FLAG_NOT_AN_ENEMY;
            }
            break;
        }
    }

    entity = self + SEGMENT_COUNT;
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

    if ((entity->hitFlags & 0xF) && self->step == IDLE_MOVE) {
        self->step = HIT_BY_PLAYER;
        self->ext.whiteDragon.unk96 = 8;
        g_api.PlaySfx(SFX_WHITE_DRAGON_HIT);
    }

    if ((entity->flags & FLAG_DEAD) && self->step != 5) {
        self->step = DEATH;
        self->ext.whiteDragon.unk96 = 0x80;
        self->ext.whiteDragon.unkA0 = 0x400;

        entity = self;
        for (i = SEGMENT_COUNT - 1; i >= 0; i--) {
            entity++;
            entity->flags |= FLAG_DEAD;
        }
    }

    switch (self->step) {
    case INIT:
        if (!self->step_s) {
            InitializeEntity(g_EInitSpawner);
            self->step = INIT;
            self->step_s++;
            self->flags |=
                FLAG_POS_CAMERA_LOCKED | FLAG_UNK_400000 | FLAG_UNK_10;
            self->facingLeft = self->params & 1;
            enemyDef = &g_api.enemyDefs[WHITE_DRAGON_ID];

            entity = self;
            for (i = SEGMENT_COUNT - 1; i >= 0; i--) {
                entity->unk60 = entity + 1;
                entity++;
                DestroyEntity(entity);

                entity->entityId = E_WHITE_DRAGON;
                // Interestingly this enemy does not use the standard method of
                // EInit to initialise the enemy and instead uses a
                // g_EInitSpawner and manually sets up the properties.
                entity->enemyId = WHITE_DRAGON_ID;
                entity->ext.whiteDragon.posX.val = self->posX.val;
                entity->ext.whiteDragon.posY.val = self->posY.val;
                entity->params = i;
                entity->ext.whiteDragon.entity = self;
                entity->ext.whiteDragon.unk84 =
                    ((SEGMENT_COUNT - i) * 256) / SEGMENT_COUNT;
                entity->ext.whiteDragon.unk86 = entity->ext.whiteDragon.unk84;
                entity->facingLeft = self->facingLeft;
                entity->attackElement = ELEMENT_UNK_1;
                entity->attack = 1;
                if (!i) {
                    entity->drawFlags = FLAG_DRAW_ROTATE;
                    entity->animSet = ANIMSET_OVL(1);
                    entity->animCurFrame = 1;
                    entity->unk5A = 0x57;
                    entity->palette = PAL_WHITE_DRAGON_A;

                    // BUG: This immediately overwrites the values set above?
                    entity->animSet = ANIMSET_OVL(6);
                    entity->unk5A = 0x4B;
                    entity->palette = PAL_WHITE_DRAGON_B;

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

            self->ext.whiteDragon.attackTimer = 0x200;
            self->ext.whiteDragon.unk9A = 0x280;
            LOHU(self->ext.whiteDragon.unk98) = 0x400;
            self->ext.whiteDragon.unk88 = 0x20000;

            entity = self + SEGMENT_COUNT;
            if (self->facingLeft) {
                entity->ext.whiteDragon.angle = 0x40;
                entity->ext.whiteDragon.unk9E = 0x40;
                self->ext.whiteDragon.unk81 = 0x10;
            } else {
                entity->ext.whiteDragon.angle = 0xC0;
                entity->ext.whiteDragon.unk9E = 0xC0;
                self->ext.whiteDragon.unk81 = 0xF0;
            }
        }

        primIndex = g_api.AllocPrimitives(PRIM_GT4, SEGMENT_COUNT - 1);
        if (primIndex != -1) {
            self->primIndex = primIndex;
            prim = &g_PrimBuf[primIndex];
            self->ext.whiteDragon.prim = prim;
            self->flags |= FLAG_HAS_PRIMS;

            segmentColor = 0x38;
            while (prim != NULL) {
                prim->tpage = 0x12;
                prim->clut = PAL_WHITE_DRAGON_B;
                prim->u0 = 0xA0;
                prim->u1 = 0xB0;
                prim->u2 = 0xA0;
                prim->u3 = 0xB0;
                PRED(prim) = segmentColor;
                PGRN(prim) = segmentColor;
                PBLU(prim) = segmentColor;
                // Bone segment gets slightly lighter as it approaches the head
                segmentColor += 3;
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
    case IDLE_MOVE:
        func_us_801B5408();
        func_us_801B5250();
        func_us_801B4F00();
        if (self->posX.i.hi >= -0xC0 && self->posX.i.hi < 0x1C1 &&
            self->posY.i.hi >= -0x80 && self->posY.i.hi < 0x161) {
            if (self->ext.whiteDragon.attackTimer) {
                self->ext.whiteDragon.attackTimer--;
            } else {
                angle = GetAngleBetweenEntitiesShifted(self, &PLAYER);
                if (self->facingLeft) {
                    angle -= 0x20;
                } else {
                    angle -= 0xA0;
                }

                if (angle < 0x41) {
                    self->step = FLAME_BREATH;
                    self->step_s = 0;
                    self->ext.whiteDragon.unk96 = 0x10;
                    self->ext.whiteDragon.unk9F = Random() & 1;
                    self->ext.whiteDragon.unkA4 = 0;
                }
                self->ext.whiteDragon.attackTimer = attack_timers[Random() & 7];
            }

            if (self->ext.whiteDragon.unk9A) {
                self->ext.whiteDragon.unk9A--;
                return;
            }

            angle = GetAngleBetweenEntitiesShifted(self, &PLAYER);
            if (self->facingLeft) {
                angle -= 0x20;
            } else {
                angle -= 0xA0;
            }

            if (angle < 0x41) {
                // CHARGE_PLAYER
                self->step++;
                self->step_s = 0;
                self->ext.whiteDragon.unk96 = 0x60;
            }
            self->ext.whiteDragon.unk9A = 0x200;
        }
        break;
    case CHARGE_PLAYER:
        switch (self->step_s) {
        case 0:
            if (LOHU(self->ext.whiteDragon.unk98) < 0x600) {
                LOHU(self->ext.whiteDragon.unk98) += 0x18;
            }

            if (self->facingLeft) {
                self->ext.whiteDragon.unk80 -= self->ext.whiteDragon.unk99;
            } else {
                self->ext.whiteDragon.unk80 += self->ext.whiteDragon.unk99;
            }

            if (self->ext.whiteDragon.unk88 > 0x28000) {
                self->ext.whiteDragon.unk88 -= 0x1000;
            }

            entity = self;
            for (i = SEGMENT_COUNT - 1; i >= 0; i--) {
                entity++;
                if (entity->ext.whiteDragon.unk84 > 0xA0) {
                    entity->ext.whiteDragon.unk84 -= 8;
                }

                entity->ext.whiteDragon.unk80 =
                    (entity - 1)->ext.whiteDragon.unk80 -
                    self->ext.whiteDragon.unk81;
                if (i) {
                    entity->ext.whiteDragon.unk83 =
                        (entity + 1)->ext.whiteDragon.unk83;
                } else {
                    angle = entity->ext.whiteDragon.unk83;
                    if (angle) {
                        if (!(angle & 0x80) &&
                            (((entity->ext.whiteDragon.unk80) - 0x40) & 0x80)) {
                            entity->ext.whiteDragon.unk83--;
                        }

                        if ((angle & 0x80) &&
                            (((entity->ext.whiteDragon.unk80) + 0x40) & 0x80)) {
                            entity->ext.whiteDragon.unk83++;
                        }
                    }
                }
            }

            if (self->ext.whiteDragon.unk96) {
                self->ext.whiteDragon.unk96--;
            } else {
                angle = GetAngleBetweenEntitiesShifted(self, &PLAYER);
                if (self->facingLeft) {
                    self->ext.whiteDragon.angle = angle - 0x40;
                } else {
                    self->ext.whiteDragon.angle = angle + 0x40;
                }
                entity->ext.whiteDragon.unk9E = angle;
                self->step_s++;
            }
            break;
        case 1:
            func_us_801B5408();
            if (self->facingLeft) {
                self->ext.whiteDragon.unk80 -= self->ext.whiteDragon.unk99;
            } else {
                self->ext.whiteDragon.unk80 += self->ext.whiteDragon.unk99;
            }

            entity = self;
            var_s7 = self + SEGMENT_COUNT;
            for (i = SEGMENT_COUNT - 1; i >= 0; i--) {
                entity++;
                entity->ext.whiteDragon.unk80 =
                    (entity - 1)->ext.whiteDragon.unk80 -
                    self->ext.whiteDragon.unk81;
                angle =
                    entity->ext.whiteDragon.unk83 - self->ext.whiteDragon.angle;
                if (angle) {
                    if (angle & 0x80) {
                        if ((var_s7->ext.whiteDragon.unk80 + 0x40) & 0x80) {
                            if (angle > 0xFC) {
                                entity->ext.whiteDragon.unk83 -= angle;
                            } else {
                                entity->ext.whiteDragon.unk83 += 4;
                            }
                        }
                    } else {
                        if ((var_s7->ext.whiteDragon.unk80 - 0x40) & 0x80) {
                            if (angle < 4) {
                                entity->ext.whiteDragon.unk83 -= angle;
                            } else {
                                entity->ext.whiteDragon.unk83 -= 4;
                            }
                        }
                    }
                } else {
                    g_api.PlaySfx(SFX_SCRAPE_B);
                    self->step_s++;
                    self->ext.whiteDragon.unk96 = 0x40;
                    entity = (self + SEGMENT_COUNT);
                    entity->attackElement = ELEMENT_UNK_1;
                    entity->attack = 8;
                    break;
                }
            }

            break;
        case 2:
            func_us_801B5408();
            if (LOHU(self->ext.whiteDragon.unk98) > 0x400) {
                LOHU(self->ext.whiteDragon.unk98) -= 0x40;
            }

            if (self->facingLeft) {
                self->ext.whiteDragon.unk80 -= self->ext.whiteDragon.unk99;
            } else {
                self->ext.whiteDragon.unk80 += self->ext.whiteDragon.unk99;
            }

            entity = self;
            for (i = SEGMENT_COUNT - 1; i >= 0; i--) {
                entity++;
                entity->ext.whiteDragon.unk80 =
                    (entity - 1)->ext.whiteDragon.unk80 -
                    self->ext.whiteDragon.unk81;
                if (entity->ext.whiteDragon.unk84 > 0x20) {
                    entity->ext.whiteDragon.unk84 -= 0x10;
                }
            }

            if (self->ext.whiteDragon.unk88 < 0x60000) {
                self->ext.whiteDragon.unk88 += 0x4650;
            } else {
                entity = self + SEGMENT_COUNT;
                entity->attackElement = ELEMENT_UNK_1;
                entity->attack = 1;
            }

            if (self->ext.whiteDragon.unk96) {
                self->ext.whiteDragon.unk96--;
            } else {
                // Back to IDLE_MOVE
                self->step--;
                self->step_s = 0;
                if (self->facingLeft) {
                    entity->ext.whiteDragon.unk9E = 0x40;
                } else {
                    entity->ext.whiteDragon.unk9E = 0xC0;
                }
            }
            break;
        }
        func_us_801B4F00();
        return;
    case HIT_BY_PLAYER:
        if (self->ext.whiteDragon.unk88 < 0x38001) {
            self->ext.whiteDragon.unk88 = 0x38000;
            if (self->ext.whiteDragon.unk96) {
                self->ext.whiteDragon.unk96--;
            } else {
                self->step = IDLE_MOVE;
                LOH(self->ext.whiteDragon.unk98) = 0;
            }
        } else {
            self->ext.whiteDragon.unk88 -= 0x4000;
        }
        func_us_801B4F00();
        break;
    case FLAME_BREATH:
        if (self->ext.whiteDragon.unk9F) {
            entity = self + SEGMENT_COUNT;
            angle =
                entity->ext.whiteDragon.angle - entity->ext.whiteDragon.unk9E;
            if (angle) {
                if (angle & 0x80) {
                    entity->ext.whiteDragon.angle += 2;
                } else {
                    entity->ext.whiteDragon.angle -= 2;
                }
            }
        } else {
            func_us_801B5408();
        }

        switch (self->step_s) {
        case 0:
            LOHU(self->ext.whiteDragon.unk98) -= 0xA0;
            if (LOHU(self->ext.whiteDragon.unk98) & 0x8000) {
                LOHU(self->ext.whiteDragon.unk98) = 0;
                self->step_s++;
                entity = self + SEGMENT_COUNT;
                angle = GetAngleBetweenEntitiesShifted(entity, &PLAYER);
                if (!self->ext.whiteDragon.unk9F) {
                    entity->ext.whiteDragon.unk9E = angle;
                } else {
                    self->ext.whiteDragon.unk9E = angle;
                }
                entity->pose = 0;
                entity->poseTimer = 0;
            } else {
                func_us_801B5250();
            }
            break;
        case 1:
            AnimateEntity(&anim_mouth_open, self + SEGMENT_COUNT);
            entity = AllocEntity(&g_Entities[160], &g_Entities[192]);
            if (entity != NULL && self->ext.whiteDragon.unk96) {
                self->ext.whiteDragon.unk96--;
                DestroyEntity(entity);
                CreateEntityFromEntity(
                    E_WHITE_DRAGON_FLAME_BREATH, self + SEGMENT_COUNT, entity);
                entity->ext.whiteDragon.entity = self + SEGMENT_COUNT;
                entity->facingLeft = self->facingLeft;
                if (self->ext.whiteDragon.unk9F) {
                    entity->params = self->ext.whiteDragon.unkA4 + 0x80;
                    self->ext.whiteDragon.unkA4++;
                } else if (self->ext.whiteDragon.unk96 == 0xF) {
                    entity->params = 1;
                }
                entity->zPriority = self->zPriority + 9;
            } else {
                self->step_s += 1;
                self->ext.whiteDragon.unk96 = 0x30;
                entity = self + SEGMENT_COUNT;
                entity->pose = 0;
                entity->poseTimer = 0;
            }
            break;
        case 2:
            entity = self + SEGMENT_COUNT;
            if (self->ext.whiteDragon.unk96) {
                if (self->ext.whiteDragon.unk96 == SEGMENT_COUNT) {
                    g_api.PlaySfx(SFX_EXPLODE_B);
                    if (self->ext.whiteDragon.unk9F) {
                        if ((entity->ext.whiteDragon.unk9E -
                             self->ext.whiteDragon.unk9E) &
                            0x80) {
                            entity->ext.whiteDragon.unk9E += 0x20;
                        } else {
                            entity->ext.whiteDragon.unk9E -= 0x20;
                        }
                    }
                }

                if (self->ext.whiteDragon.unk96 < 0x19) {
                    AnimateEntity(&anim_breathe_fire, self + SEGMENT_COUNT);
                }
                self->ext.whiteDragon.unk96--;
            } else {
                self->step = IDLE_MOVE;
                self->step_s = 0;
                if (self->facingLeft) {
                    entity->ext.whiteDragon.unk9E = 0x40;
                } else {
                    entity->ext.whiteDragon.unk9E = 0xC0;
                }
            }
            break;
        }
        func_us_801B4F00();
        break;
    case DEATH:
        if (self->ext.whiteDragon.unk88 < 0x50000) {
            self->ext.whiteDragon.unkA0 = 0x4000;
        }

        if (self->ext.whiteDragon.unk88 > 0x60000) {
            self->ext.whiteDragon.unkA0 = -0x4000;
        }

        self->ext.whiteDragon.unk88 += self->ext.whiteDragon.unkA0;
        if (LOHU(self->ext.whiteDragon.unk98) < 0x1000) {
            LOHU(self->ext.whiteDragon.unk98) += 0x20;
        }

        if (self->facingLeft) {
            self->ext.whiteDragon.unk80 -= self->ext.whiteDragon.unk99;
        } else {
            self->ext.whiteDragon.unk80 += self->ext.whiteDragon.unk99;
        }

        entity = self;
        for (i = SEGMENT_COUNT - 1; i >= 0; i--) {
            entity++;
            if (entity->ext.whiteDragon.unk84 < entity->ext.whiteDragon.unk86) {
                entity->ext.whiteDragon.unk84 += 2;
            }
            entity->ext.whiteDragon.unk80 =
                (entity - 1)->ext.whiteDragon.unk80 -
                self->ext.whiteDragon.unk81;
            if (i) {
                entity->ext.whiteDragon.unk83 =
                    (entity + 1)->ext.whiteDragon.unk83;
            } else {
                angle = entity->ext.whiteDragon.unk83;
                if (angle) {
                    if (!(angle & 0x80) &&
                        ((entity->ext.whiteDragon.unk80 - 0x40) & 0x80)) {
                        entity->ext.whiteDragon.unk83--;
                    }

                    if ((angle & 0x80) &&
                        ((entity->ext.whiteDragon.unk80 + 0x40) & 0x80)) {
                        entity->ext.whiteDragon.unk83++;
                    }
                }
            }
        }

        func_us_801B4F00();
        if (self->ext.whiteDragon.unk96) {
            self->ext.whiteDragon.unk96--;

            if (!(self->ext.whiteDragon.unk96 & 7)) {
                g_api.PlaySfx(SFX_EXPLODE_FAST_B);
            }

            if (!(self->ext.whiteDragon.unk96 & 1)) {
                entity = AllocEntity(
                    &g_Entities[224], &g_Entities[TOTAL_ENTITY_COUNT]);
                if (entity != NULL) {
                    CreateEntityFromEntity(
                        E_EXPLOSION, self + SEGMENT_COUNT, entity);
                    entity->params = EXPLOSION_FIREBALL;
                    entity->posX.i.hi += (s16)(Random() & 0x1F) - 0x10;
                    entity->zPriority = self->zPriority + 9;
                }
            }
        } else {
            entity = self;
            for (i = SEGMENT_COUNT - 1; i >= 0; i--) {
                entity++;
                entity->drawFlags = FLAG_DRAW_DEFAULT;
                if (i & 1) {
                    entity->entityId = E_EXPLOSION;
                    entity->pfnUpdate = EntityExplosion;
                    entity->params = EXPLOSION_FIREBALL;
                } else {
                    j = self->params >> 1;
                    if (j) {
                        entity->entityId = E_PRIZE_DROP;
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

static void func_us_801B6578(Entity* self) {
    Entity* entity;

    entity = self->ext.whiteDragon.entity;
    SetEntityVelocityFromAngle(entity->ext.whiteDragon.angle, 0x60);
    self->posX.val = entity->posX.val + self->velocityX;
    self->posY.val = entity->posY.val + self->velocityY;

    entity = entity - SEGMENT_COUNT;
    if (entity->step == DEATH) {
        DestroyEntity(self);
    }
}

// nb. This data must be defined down here since the inline data inside funcs
// goes into data on PSP but rodata on PSX.

// This indexes into g_SineTable with an angle value from 0-255
static u8 flame_sine_indices[] = {
    64, 96, 32, 80, 48, 16, 80, 112, 64, 48, 96, 32, 112, 16, 48, 80,
};
static AnimateEntityFrame anim_flame_breathe[] = {
    {.duration = 1, .pose = 0x01},
    {.duration = 1, .pose = 0x02},
    {.duration = 1, .pose = 0x01},
    {.duration = 1, .pose = 0x02},
    {.duration = 1, .pose = 0x01},
    {.duration = 1, .pose = 0x02},
    {.duration = 1, .pose = 0x01},
    {.duration = 1, .pose = 0x02},
    {.duration = 1, .pose = 0x01},
    {.duration = 1, .pose = 0x02},
    {.duration = 1, .pose = 0x01},
    {.duration = 1, .pose = 0x02},
    {.duration = 1, .pose = 0x01},
    {.duration = 1, .pose = 0x02},
    {.duration = 1, .pose = 0x03},
    {.duration = 1, .pose = 0x04},
    {.duration = 1, .pose = 0x05},
    {.duration = 1, .pose = 0x06},
    {.duration = 1, .pose = 0x07},
    {.duration = 1, .pose = 0x08},
    POSE_END};
static AnimateEntityFrame anim_flame_inhale[] = {
    {.duration = 2, .pose = 0x01},
    {.duration = 2, .pose = 0x02},
    {.duration = 2, .pose = 0x03},
    {.duration = 2, .pose = 0x04},
    {.duration = 2, .pose = 0x05},
    {.duration = 2, .pose = 0x06},
    {.duration = 2, .pose = 0x07},
    {.duration = 2, .pose = 0x08},
    POSE_LOOP(0),
};

void EntityWhiteDragonFlameBreath(Entity* self) {
    s16 size;
    Entity* entity;
    s32 prevVelocityX;
    s32 prevVelocityY;
    u8 params;

    switch (self->step) {
    case 0:
        InitializeEntity(D_us_801807F0);
        self->zPriority += 1;
        self->hitboxState = 0;
        self->drawMode = DRAW_TPAGE2 | DRAW_TPAGE;
        entity = self->ext.whiteDragon.entity;
        SetEntityVelocityFromAngle(entity->ext.whiteDragon.angle, 0x60);
        LOWU(self->ext.whiteDragon.unk80) = 0x28;
        return;
    case 1:
        if (self->params == 1) {
            AnimateEntity(anim_flame_inhale, self);
        }

        if (!--LOWU(self->ext.whiteDragon.unk80)) {
            SetStep(2);
            self->zPriority = g_unkGraphicsStruct.g_zEntityCenter - 0xC;
            self->hitboxState = 1;
            self->ext.whiteDragon.unk84 = 0;
            self->drawFlags = FLAG_DRAW_SCALEY | FLAG_DRAW_SCALEX;
        }

        func_us_801B6578(self);
        if (self->params & 0x80) {
            if (LOWU(self->ext.whiteDragon.unk80) < 0x10) {
                self->animCurFrame = 0;
                return;
            }

            AnimateEntity(anim_flame_inhale, self);
            // HACK: bit ugly, can this be rewritten?
            size = (s16)(LOWU(self->ext.whiteDragon.unk80) - 0x10) * 32;
            params = self->params & 0x7F;
            prevVelocityX = self->velocityX;
            prevVelocityY = self->velocityY;
            SetEntityVelocityFromAngle(flame_sine_indices[params], size);
            if (!self->facingLeft) {
                self->velocityX = -self->velocityX;
            }
            MoveEntity();
            self->velocityX = prevVelocityX;
            self->velocityY = prevVelocityY;
        }
        break;
    case 2:
        if (!AnimateEntity(anim_flame_breathe, self)) {
            DestroyEntity(self);
        }

        MoveEntity();
        if (self->animCurFrame > 6) {
            self->hitboxState = 0;
        }

        size = self->ext.whiteDragon.unk84 * 32;
        self->scaleX = size;
        self->scaleY = size;

        size = self->ext.whiteDragon.unk84;
        self->hitboxHeight = size;
        self->ext.whiteDragon.unk84++;
        break;
    }
}
