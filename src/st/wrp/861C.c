#include "wrp.h"

extern s8 c_HeartPrizes[];
extern s32 c_GoldPrizes[];
extern u8* D_80180E08[];
extern u16 D_80180DC4[];
extern u16 D_80180DF4[];
extern u16 g_ItemIconSlots[];
extern u16 UNK_Invincibility0[];
extern PfnEntityUpdate PfnEntityUpdates[];
extern s16 D_80180A94[];
extern LayoutEntity* D_80180310[];

INCLUDE_ASM("st/wrp/nonmatchings/861C", TestCollisions);

#include "../entity_damage_display.h"

#include "../libstage.h"

void EntityRedDoor(Entity* self) {
    Primitive* prim;
    s32 i;
    s16 angle;
    u8* uv;
    s16 x;
    s16 y;
    u8 sp3F;
    s16 endX;
    s16 scrollX;
    s16 scrollY;
    s32 tileIdx;

    switch (self->step) {
    case 0:
        InitializeEntity(g_eInitGeneric2);
        self->animSet = 7;
        self->animCurFrame = 1;
        self->zPriority = PLAYER.zPriority - 0x20;
        self->facingLeft = 0;
        self->posY.i.hi += 0x1F;

        if (self->params & 0x100) {
            self->ext.door.unk86 = -4;
        } else {
            self->ext.door.unk86 = 4;
        }
        self->posX.i.hi += self->ext.door.unk86;
        self->primIndex = g_api.AllocPrimitives(PRIM_GT4, LEN(g_eRedDoorUV));
        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags |= FLAG_HAS_PRIMS;
        uv = g_eRedDoorUV;
        prim = &g_PrimBuf[self->primIndex];
        i = 0;
        y = self->posY.i.hi - 0x1F;
        while (prim != NULL) {
            prim->u0 = uv[0];
            prim->u1 = uv[1];
            prim->u2 = uv[2];
            prim->u3 = uv[3];
            prim->v0 = uv[4];
            prim->v1 = uv[5];
            prim->v2 = uv[6];
            prim->v3 = uv[7];
            prim->tpage = 0x1F;
            prim->clut = 0x198;
            prim->priority = PLAYER.zPriority - 0x20;
            prim->y0 = prim->y1 = y;
            prim->y2 = prim->y3 = y + 62;
            if (i == 0) {
                prim->y0 = prim->y1 = y;
                prim->y2 = prim->y3 = y + 62;
            }
            prim->drawMode = 6;
            prim->r0 = prim->b0 = prim->g0 = 0x7F;
            prim->r1 = prim->b1 = prim->g1 = 0x7F;
            prim->r2 = prim->b2 = prim->g2 = 0x7F;
            prim->r3 = prim->b3 = prim->g3 = 0x7F;
            if (i == 2 && !(self->params & 0x100)) {
                prim->drawMode |= 8;
            }
            if (i == 1 && (self->params & 0x100)) {
                prim->drawMode |= 8;
            }
            i++;
            uv += 8;
            prim = prim->next;
        }
        if (EntityIsNearPlayer(self)) {
            if (!(self->params & 0x100)) {
                g_api.func_80134714(SFX_OPEN_DOOR, 0x60, -6);
                self->ext.door.angle = 0x1000;
            }
            if (self->params & 0x100) {
                g_api.func_80134714(SFX_OPEN_DOOR, 0x60, 6);
                self->ext.door.angle = 0x800;
            }
            self->animCurFrame = 0;
            self->step = 4;
            PLAYER.velocityY = 0;
            g_Player.D_80072EF4 = 0;
            g_Player.D_80072EFC = 0x18;
        } else {
            self->ext.door.angle = 0xC00;
            prim = &g_PrimBuf[self->primIndex];
            i = 0;
            while (prim != NULL) {
                prim->drawMode |= 8;
                i++;
                if (i == 3) {
                    break;
                }
                prim = prim->next;
            }
        }
        break;
    case 1:
        if (!(((PLAYER.facingLeft != GetSideToPlayer()) & 1) ^ 1) &&
            ((PLAYER.step == 0x19 && g_PlayableCharacter) ||
             PLAYER.step == 1) &&
            EntityIsNearPlayer(self)) {
            if (!(self->params & 0x100)) {
                g_api.func_80134714(SFX_OPEN_DOOR, 0x60, -6);
            }
            if (self->params & 0x100) {
                g_api.func_80134714(SFX_OPEN_DOOR, 0x60, 6);
            }
            prim = &g_PrimBuf[self->primIndex];
            i = 0;
            while (prim != NULL) {
                if (i == 1 && !(self->params & 0x100)) {
                    prim->drawMode &= ~DRAW_HIDE;
                }
                if (i == 2 && (self->params & 0x100)) {
                    prim->drawMode &= ~DRAW_HIDE;
                }
                if (i == 0) {
                    prim->drawMode &= ~DRAW_HIDE;
                }
                i++;
                prim = prim->next;
            }
            self->animCurFrame = 0;
            g_Player.D_80072EF4 = 0;
            g_Player.D_80072EFC = 2;
            self->step++;
        }
        break;
    case 2:
        g_Player.D_80072EF4 = 0;
        g_Player.D_80072EFC = 0x18;
        if (!(self->params & 0x100)) {
            self->ext.door.angle += 0x20;
            if (self->ext.door.angle >= 0x1000) {
                self->ext.door.angle = 0x1000;
            }
            if (self->ext.door.angle == 0x1000) {
                self->step++;
            }
        } else {
            self->ext.door.angle -= 0x20;
            if (self->ext.door.angle <= 0x800) {
                self->ext.door.angle = 0x800;
            }
            if (self->ext.door.angle == 0x800) {
                self->step++;
            }
        }
        break;
    case 3:
        if (g_Player.D_80072EFC >= 4) {
            return;
        }
        if (!(self->params & 0x100)) {
            g_Player.D_80072EF4 = PAD_LEFT;
        } else {
            g_Player.D_80072EF4 = PAD_RIGHT;
        }
        g_Player.D_80072EFC = 3;
        break;
    case 4:
        if (!(self->params & 0x100)) {
            g_Player.D_80072EF4 = PAD_RIGHT;
        } else {
            g_Player.D_80072EF4 = PAD_LEFT;
        }
        g_Player.D_80072EFC = 4;
        if (EntityIsNearPlayer(self) == 0) {
            self->step++;
        }
        break;
    case 5:
        g_Player.D_80072EF4 = 0;
        g_Player.D_80072EFC = 4;
        if (!(self->params & 0x100)) {
            self->ext.door.angle -= 0x20;
            if (self->ext.door.angle <= 0xC00) {
                self->ext.door.angle = 0xC00;
            }
        } else {
            self->ext.door.angle += 0x20;
            if (self->ext.door.angle >= 0xC00) {
                self->ext.door.angle = 0xC00;
            }
        }
        if (self->ext.door.angle == 0xC00) {
            prim = &g_PrimBuf[self->primIndex];
            for (i = 0; prim != NULL; i++, prim = prim->next) {
                prim->drawMode |= 8;
            }
            if (!(self->params & 0x100)) {
                g_api.func_80134714(0x64F, 0x60, -6);
            }
            if (self->params & 0x100) {
                g_api.func_80134714(0x64F, 0x60, 6);
            }
            self->animCurFrame = 1;
            self->step = 1;
        }
        break;
    }

    if (self->step != 1) {
        g_api.func_8010E168(1, 0x20);
        g_api.func_8010DFF0(1, 1);
    }

    x = self->posX.i.hi - self->ext.door.unk86;
    if (self->params & 0x100) {
        x--;
    } else {
        x++;
    }

    i = 0;
    angle = self->ext.door.angle;
    prim = &g_PrimBuf[self->primIndex];
    for (; prim != NULL; i++, prim = prim->next) {
        if (!(prim->drawMode & 8)) {
            if (!(self->params & 0x100)) {
                if (i == 0) {
                    endX = prim->x0 = prim->x2 =
                        x + ((rcos(angle) >> 8) * 32 >> 4);
                    prim->x1 = prim->x3 =
                        prim->x0 - ((rsin(angle) >> 4) * 6 >> 8);
                    if (angle > 0xF80) {
                        prim->x1 = prim->x3 = prim->x0 + 1;
                    }
                    if (angle > 0xE00) {
                        prim->u0 = prim->u2 = 178;
                        prim->u1 = prim->u3 = 182;
                    }
                    if (angle <= 0xE00) {
                        prim->u0 = prim->u2 = 177;
                        prim->u1 = prim->u3 = 183;
                    }
                    if (angle == 0x1000) {
                        prim->r1 = prim->b1 = prim->g1 = 63;
                        prim->r3 = prim->b3 = prim->g3 = 63;
                    } else {
                        prim->r1 = prim->b1 = prim->g1 =
                            0x7F - ((angle & 0x3FF) >> 4);
                        prim->r3 = prim->b3 = prim->g3 =
                            0x7F - ((angle & 0x3FF) >> 4);
                    }
                } else {
                    prim->x0 = prim->x2 = x;
                    prim->x1 = prim->x3 = endX;
                    if (angle == 0x1000) {
                        prim->r0 = prim->b0 = prim->g0 = 63;
                        prim->r2 = prim->b2 = prim->g2 = 63;
                    } else {
                        prim->r0 = prim->b0 = prim->g0 = (angle & 0x3FF) >> 4;
                        prim->r2 = prim->b2 = prim->g2 = (angle & 0x3FF) >> 4;
                    }
                }
            } else {
                if (i == 0) {
                    endX = prim->x1 = prim->x3 =
                        x + ((rcos(angle) >> 8) * 32 >> 4);
                    prim->x0 = prim->x2 =
                        prim->x1 + (((rsin(angle) >> 4) * 6) >> 8);
                    if (angle < 0x880) {
                        prim->x0 = prim->x2 = prim->x1 - 1;
                    }
                    if (angle < 0xA00) {
                        prim->u0 = prim->u2 = 178;
                        prim->u1 = prim->u3 = 182;
                    }
                    if (angle > 0xA00) {
                        prim->u0 = prim->u2 = 177;
                        prim->u1 = prim->u3 = 183;
                    }
                    if (angle == 0x800) {
                        prim->r0 = prim->b0 = prim->g0 = 127;
                        prim->r2 = prim->b2 = prim->g2 = 127;
                    } else {
                        prim->r0 = prim->b0 = prim->g0 =
                            63 + ((angle & 0x3FF) >> 4);
                        prim->r2 = prim->b2 = prim->g2 =
                            63 + ((angle & 0x3FF) >> 4);
                    }
                } else {
                    prim->x0 = prim->x2 = endX - 1;
                    prim->x1 = prim->x3 = x;
                    if (angle == 0x800) {
                        prim->r1 = prim->b1 = prim->g1 = 63;
                        prim->r3 = prim->b3 = prim->g3 = 63;
                    } else {
                        prim->r1 = prim->b1 = prim->g1 =
                            63 - ((angle & 0x3FF) >> 4);
                        prim->r3 = prim->b3 = prim->g3 =
                            63 - ((angle & 0x3FF) >> 4);
                    }
                }
            }
        }
    }

    sp3F = self->params & 0xFF;
    if (self->animCurFrame) {
        for (i = 0; i < 4; i++) {
            x = self->posX.i.hi;
            y = self->posY.i.hi - 24 + i * 0x10;
            scrollX = x + g_Tilemap.scrollX.i.hi;
            scrollY = y + g_Tilemap.scrollY.i.hi;
            tileIdx = (scrollX >> 4) + (scrollY >> 4) * g_Tilemap.hSize * 0x10;
            g_Tilemap.fg[tileIdx] = g_eRedDoorTiles[sp3F][i];
        }
    } else {
        for (i = 0; i < 4; i++) {
            x = self->posX.i.hi;
            y = self->posY.i.hi - 24 + i * 0x10;
            scrollX = x + g_Tilemap.scrollX.i.hi;
            scrollY = y + g_Tilemap.scrollY.i.hi;
            tileIdx = (scrollX >> 4) + (scrollY >> 4) * g_Tilemap.hSize * 0x10;
            g_Tilemap.fg[tileIdx] = g_eRedDoorTiles[sp3F][i + 4];
        }
    }
}

#include "../../destroy_entity.h"

#include "../../destroy_entities_from_index.h"

void PreventEntityFromRespawning(Entity* entity) {
    if (entity->entityRoomIndex) {
        u32 value = (entity->entityRoomIndex - 1);
        u16 index = value / 32;
        u16 bit = value % 32;
        g_entityDestroyed[index] |= 1 << bit;
    }
}

#include "../animate_entity.h"

u8 func_8018B7E8(u8 frames[], Entity* self, u8 arg2) {
    u16 animFrameStart = self->animFrameIdx * 2;
    u8* var_s1 = &frames[animFrameStart];
    s16 var_a1 = 0;

    if (self->animFrameDuration == 0) {
        if (*var_s1 != 0) {
            if (*var_s1 == 0xFF) {
                return 0;
            }
            self->animFrameDuration = *var_s1++ + (u8)self->ext.stub[0x3F];
            self->animCurFrame = *var_s1++;
            self->animFrameIdx++;
            var_a1 = 128;
        } else {
            var_s1 = frames;
            self->animFrameIdx = 0;
            self->animFrameDuration = 0;
            self->ext.stub[0x3F] = (arg2 * Random()) >> 8;
            self->animFrameDuration = *var_s1++ + (u8)self->ext.stub[0x3F];
            self->animCurFrame = *var_s1;
            self->animFrameIdx++;
            return 0;
        }
    }
    self->animFrameDuration--;
    self->animCurFrame = var_s1[-1];
    var_a1 |= 1;
    return var_a1;
}

// Absolute distance from g_CurrentEntity to the player in the X Axis
s16 GetDistanceToPlayerX(void) {
    s16 xDistance = g_CurrentEntity->posX.i.hi - PLAYER.posX.i.hi;

    if (xDistance < 0) {
        xDistance = -xDistance;
    }
    return xDistance;
}

// Absolute distance from g_CurrentEntity to the player in the Y Axis
s32 GetDistanceToPlayerY(void) {
    s32 yDistance = g_CurrentEntity->posY.i.hi - PLAYER.posY.i.hi;

    if (yDistance < 0) {
        yDistance = -yDistance;
    }
    return yDistance;
}

#include "../get_side_to_player.h"

void MoveEntity(void) {
    g_CurrentEntity->posX.val += g_CurrentEntity->velocityX;
    g_CurrentEntity->posY.val += g_CurrentEntity->velocityY;
}

void FallEntity(void) {
    if (g_CurrentEntity->velocityY < FALL_TERMINAL_VELOCITY) {
        g_CurrentEntity->velocityY += FALL_GRAVITY;
    }
}

s32 func_8018BA10(u16* sensors) {
    Collider col;
    Collider colBack;
    s16 x;
    s16 y;
    s16 i;

    MoveEntity();
    FallEntity();
    if (g_CurrentEntity->velocityY >= 0) {
        x = g_CurrentEntity->posX.i.hi;
        y = g_CurrentEntity->posY.i.hi;
        for (i = 0; i < 4; i++) {
            x += *sensors++;
            y += *sensors++;
            g_api.CheckCollision(x, y, &col, 0);
            if (col.effects & EFFECT_UNK_8000) {
                if (i == 1) {
                    if (col.effects & EFFECT_SOLID) {
                        g_api.CheckCollision(x, y - 8, &colBack, 0);
                        if (!(colBack.effects & EFFECT_SOLID)) {
                            g_CurrentEntity->posY.i.hi =
                                (u16)g_CurrentEntity->posY.i.hi + 4 + col.unk18;
                            g_CurrentEntity->velocityX = 0;
                            g_CurrentEntity->velocityY = 0;
                            g_CurrentEntity->flags &= ~FLAG_UNK_10000000;
                            return 1;
                        }
                    }
                    continue;
                }
            }
            if (col.effects & EFFECT_NOTHROUGH && i != 1) {
                if (col.effects & EFFECT_QUICKSAND) {
                    g_CurrentEntity->flags &= ~FLAG_UNK_10000000;
                    return 4;
                }
                g_api.CheckCollision(x, y - 8, &colBack, 0);
                if (!(colBack.effects & EFFECT_SOLID)) {
                    g_CurrentEntity->posY.i.hi =
                        g_CurrentEntity->posY.i.hi + col.unk18;
                    g_CurrentEntity->velocityX = 0;
                    g_CurrentEntity->velocityY = 0;
                    g_CurrentEntity->flags &= ~FLAG_UNK_10000000;
                    return 1;
                }
            }
        }
    }
    g_CurrentEntity->flags |= FLAG_UNK_10000000;
    return 0;
}

s32 func_8018BC88(s16* posX) {
    Collider collider;
    s16 temp2;
    s16 temp4;
    s16 x, y;

    g_CurrentEntity->posX.val += g_CurrentEntity->velocityX;
    temp2 = g_CurrentEntity->posY.i.hi + 3;
    g_CurrentEntity->posY.i.hi = temp2;
    x = g_CurrentEntity->posX.i.hi + *posX;
    posX++;
    y = temp2 + *posX;
    g_api.CheckCollision(x, y, &collider, 0);
    if (!(collider.effects & EFFECT_SOLID)) {
        return 0;
    }
    posX++;

    g_CurrentEntity->posY.i.hi = g_CurrentEntity->posY.i.hi + collider.unk18;
    if (g_CurrentEntity->velocityX != 0) {
        if (g_CurrentEntity->velocityX < 0) {
            temp4 = x - *posX;
            posX++;
        } else {
            temp4 = x + *posX;
            posX++;
        }
        y = y + *posX - 7;
        g_api.CheckCollision(temp4, y, &collider, 0);
        if (collider.effects & EFFECT_SOLID) {
            if ((collider.effects & (EFFECT_UNK_8000 | EFFECT_UNK_0002)) ==
                EFFECT_UNK_0002) {
                g_CurrentEntity->posX.val =
                    g_CurrentEntity->posX.val - g_CurrentEntity->velocityX;
                g_CurrentEntity->velocityX = 0;
                return 0xFF;
            }
            return 0x61;
        }
        y += 15;
        g_api.CheckCollision(temp4, y, &collider, 0);
        if (collider.effects & EFFECT_SOLID) {
            if (collider.effects & EFFECT_UNK_8000) {
                return 0x61;
            }
            return 1;
        }
        g_CurrentEntity->posX.val -= g_CurrentEntity->velocityX;
        g_CurrentEntity->velocityX = 0;

        return 0x80;
    }
    return 1;
}

Entity* AllocEntity(Entity* start, Entity* end) {
    Entity* current = start;
    while (current < end) {
        if (current->entityId == E_NONE) {
            DestroyEntity(current);
            return current;
        }

        current++;
    }
    return NULL;
}

s32 func_8018BED0(u8 arg0, s16 arg1) { return D_80180A94[arg0] * arg1; }

s16 func_8018BEFC(u8 arg0) { return D_80180A94[arg0]; }

void func_8018BF18(s32 arg0, s16 arg1) {
    g_CurrentEntity->velocityX = func_8018BED0(arg0, arg1);
    g_CurrentEntity->velocityY = func_8018BED0(arg0 - 0x40, arg1);
}

u8 func_8018BF84(s16 x, s16 y) { return ((ratan2(y, x) >> 4) + 0x40); }

u8 func_8018BFBC(Entity* a, Entity* b) {
    s32 diffX = (u16)b->posX.i.hi - (u16)a->posX.i.hi;
    s32 diffY = (u16)b->posY.i.hi - (u16)a->posY.i.hi;
    return func_8018BF84(diffX, diffY);
}

u8 func_8018C004(s32 x, s32 y) {
    s32 diffX = x - (u16)g_CurrentEntity->posX.i.hi;
    s32 diffY = y - (u16)g_CurrentEntity->posY.i.hi;
    return func_8018BF84(diffX, diffY);
}

#include "../adjust_value_within_threshold.h"

#include "../unk_entity_func0.h"

u16 func_8018C130(s16 x, s16 y) { return ratan2(y, x); }

u16 func_8018C160(Entity* a, Entity* b) {
    s32 diffX = b->posX.i.hi - a->posX.i.hi;
    s32 diffY = b->posY.i.hi - a->posY.i.hi;
    return ratan2(diffY, diffX);
}

u16 func_8018C198(s32 x, s32 y) {
    s16 diffX = x - (u16)g_CurrentEntity->posX.i.hi;
    s16 diffY = y - (u16)g_CurrentEntity->posY.i.hi;
    return ratan2(diffY, diffX);
}

u16 func_8018C1E0(u16 arg0, s16 arg1, s16 arg2) {
    u16 var_v0 = arg1;
    u16 temp_a2 = arg2 - arg1;
    u16 var_v0_2;

    if (temp_a2 & 0x800) {
        var_v0_2 = (0x800 - temp_a2) & 0x7FF;
    } else {
        var_v0_2 = temp_a2;
    }

    if (var_v0_2 > arg0) {
        if (temp_a2 & 0x800) {
            var_v0 = arg1 - arg0;
        } else {
            var_v0 = arg1 + arg0;
        }

        return var_v0;
    }

    return arg2;
}

void SetStep(u8 step) {
    g_CurrentEntity->step = step;
    g_CurrentEntity->step_s = 0;
    g_CurrentEntity->animFrameIdx = 0;
    g_CurrentEntity->animFrameDuration = 0;
}

void func_8018C260(u8 step_s) {
    g_CurrentEntity->step_s = step_s;
    g_CurrentEntity->animFrameIdx = 0;
    g_CurrentEntity->animFrameDuration = 0;
}

void EntityExplosionSpawn(u16 arg0, u16 arg1) {
    Entity* entity;

    if (arg1 != 0) {
        func_801916C4(arg1);
    }
    if (arg0 == 0xFF) {
        DestroyEntity(g_CurrentEntity);
        return;
    }

    entity = g_CurrentEntity;
    entity->drawFlags = 0;
    entity->entityId = E_EXPLOSION;
    entity->pfnUpdate = (PfnEntityUpdate)EntityExplosion;
    entity->params = arg0;
    entity->animCurFrame = 0;
    g_CurrentEntity->step = 0;
    g_CurrentEntity->step_s = 0;
}

void InitializeEntity(u16 arg0[]) {
    u16 enemyId;
    EnemyDef* enemyDef;

    g_CurrentEntity->animSet = *arg0++;
    g_CurrentEntity->animCurFrame = *arg0++;
    g_CurrentEntity->unk5A = *arg0++;
    g_CurrentEntity->palette = *arg0++;

    enemyId = *arg0++;
    g_CurrentEntity->enemyId = enemyId;
    enemyDef = &g_api.enemyDefs[enemyId];
    g_CurrentEntity->hitPoints = enemyDef->hitPoints;
    g_CurrentEntity->attack = enemyDef->attack;
    g_CurrentEntity->attackElement = enemyDef->attackElement;
    g_CurrentEntity->hitboxState = enemyDef->hitboxState;
    g_CurrentEntity->hitboxWidth = enemyDef->hitboxWidth;
    g_CurrentEntity->hitboxHeight = enemyDef->hitboxHeight;
    g_CurrentEntity->flags = enemyDef->flags;
    g_CurrentEntity->hitboxOffX = 0;
    g_CurrentEntity->hitboxOffY = 0;
    g_CurrentEntity->step_s = 0;
    g_CurrentEntity->step++;
    if (g_CurrentEntity->zPriority == 0) {
        g_CurrentEntity->zPriority =
            g_unkGraphicsStruct.g_zEntityCenter.S16.unk0 - 0xC;
    }
}

void EntityDummy(Entity* arg0) {
    if (arg0->step == 0) {
        arg0->step++;
    }
}

s32 func_8018C434(u16* hitSensors, s16 sensorCount) {
    Collider collider;
    s16 i;
    s32 velocityX;
    u16 temp_a1;
    s16 x;
    s16 y;

    velocityX = g_CurrentEntity->velocityX;
    if (velocityX != 0) {
        x = g_CurrentEntity->posX.i.hi;
        y = g_CurrentEntity->posY.i.hi;
        for (i = 0; i < sensorCount; i++) {
            if (velocityX < 0) {
                s16 newX = x + *hitSensors++;
                x = newX;
            } else {
                s16 newX = x - *hitSensors++;
                x = newX;
            }

            y += *hitSensors++;
            g_api.CheckCollision(x, y, &collider, 0);
            if (collider.effects & EFFECT_UNK_0002 &&
                ((!(collider.effects & EFFECT_UNK_8000)) || (i != 0))) {
                return 2;
            }
        }
        return 0;
    }
}

void func_8018C55C(u16* hitSensors, s16 sensorCount) {
    Collider collider;
    s16 i;
    s32 velocityX;
    s16 x;
    s16 y;

    velocityX = g_CurrentEntity->velocityX;
    if (velocityX == 0)
        return;
    x = g_CurrentEntity->posX.i.hi;
    y = g_CurrentEntity->posY.i.hi;
    for (i = 0; i < sensorCount; i++) {
        if (velocityX < 0) {
            x = x + *hitSensors++;
        } else {
            x = x - *hitSensors++;
        }

        y += *hitSensors++;
        g_api.CheckCollision(x, y, &collider, 0);
        if (collider.effects & EFFECT_UNK_0002 &&
            (!(collider.effects & EFFECT_UNK_8000) || i != 0)) {
            if (velocityX < 0) {
                g_CurrentEntity->posX.i.hi += collider.unk1C;
            } else {
                g_CurrentEntity->posX.i.hi += collider.unk14;
            }
            return;
        }
    }
}

INCLUDE_ASM("st/wrp/nonmatchings/861C", func_8018C6B4);

#include "../replace_breakable_with_item_drop.h"

void func_8018CAB0(void) {
    s32 temp_v1;
    Entity* entity;

    entity = g_CurrentEntity;
    if (entity->velocityY >= 0) {
        temp_v1 =
            entity->ext.generic.unk88.S16.unk0 + entity->ext.generic.unk84.unk;
        entity->ext.generic.unk84.unk = temp_v1;
        entity->velocityX = temp_v1;
        if (temp_v1 == 0x10000 || temp_v1 == -0x10000) {
            entity->ext.generic.unk88.S16.unk0 =
                -entity->ext.generic.unk88.S16.unk0;
        }
        entity = g_CurrentEntity;
    }

    if (entity->velocityY < FIX(0.25)) {
        entity->velocityY += FIX(0.125);
    }
}

void func_8018CB34(u16 arg0) {
    Collider collider;

    if (g_CurrentEntity->velocityX < 0) {
        g_api.CheckCollision(g_CurrentEntity->posX.i.hi,
                             g_CurrentEntity->posY.i.hi - 7, &collider, 0);
        if (collider.effects & EFFECT_NOTHROUGH) {
            g_CurrentEntity->velocityY = 0;
        }
    }

    g_api.CheckCollision(g_CurrentEntity->posX.i.hi,
                         g_CurrentEntity->posY.i.hi + 7, &collider, 0);

    if (arg0) {
        if (!(collider.effects & EFFECT_NOTHROUGH)) {
            MoveEntity();
            FallEntity();
            return;
        }

        g_CurrentEntity->velocityX = 0;
        g_CurrentEntity->velocityY = 0;

        if (collider.effects & EFFECT_QUICKSAND) {
            g_CurrentEntity->posY.val += FIX(0.125);
            return;
        }

        g_CurrentEntity->posY.i.hi += collider.unk18;
        return;
    }

    if (!(collider.effects & EFFECT_NOTHROUGH)) {
        MoveEntity();
        func_8018CAB0();
    }
}

#include "../collect_heart.h"

void CollectGold(u16 goldSize) {
    s32 *gold, *unk;
    u16 goldSizeIndex;

    g_api.PlaySfx(NA_SE_PL_COLLECT_GOLD);
    gold = &g_Status.gold;
    goldSizeIndex = goldSize - 2;
    *gold += c_GoldPrizes[goldSizeIndex];
    if (*gold > MAX_GOLD) {
        *gold = MAX_GOLD;
    }

    unk = &g_BottomCornerTextTimer;
    if (*unk) {
        g_api.FreePrimitives(g_BottomCornerTextPrims);
        *unk = 0;
    }

    BottomCornerText(D_80180E08[goldSizeIndex], 1);
    DestroyEntity(g_CurrentEntity);
}

void CollectSubweapon(u16 subWeaponIdx) {
    Entity* player = &PLAYER;
    u16 subWeapon;

    g_api.PlaySfx(NA_SE_PL_IT_PICKUP);
    subWeapon = g_Status.subWeapon;
    g_Status.subWeapon = D_80180DC4[subWeaponIdx];

    if (subWeapon == g_Status.subWeapon) {
        subWeapon = 1;
        g_CurrentEntity->unk6D[0] = 0x10;
    } else {
        subWeapon = D_80180DF4[subWeapon];
        g_CurrentEntity->unk6D[0] = 0x60;
    }

    if (subWeapon != 0) {
        g_CurrentEntity->params = subWeapon;
        g_CurrentEntity->posY.i.hi = player->posY.i.hi + 12;
        SetStep(7);
        g_CurrentEntity->velocityY = FIX(-2.5);
        g_CurrentEntity->animCurFrame = 0;
        g_CurrentEntity->ext.generic.unk88.S16.unk2 = 5;
        if (player->facingLeft != 1) {
            g_CurrentEntity->velocityX = FIX(-2);
            return;
        }
        g_CurrentEntity->velocityX = FIX(2);
        return;
    }
    DestroyEntity(g_CurrentEntity);
}

#include "../collect_heart_vessel.h"

void CollectLifeVessel(void) {
    g_api.PlaySfx(NA_SE_PL_COLLECT_HEART);
    g_api.func_800FE044(LIFE_VESSEL_INCREASE, 0x8000);
    DestroyEntity(g_CurrentEntity);
}

void DestroyCurrentEntity(void) { DestroyEntity(g_CurrentEntity); }
