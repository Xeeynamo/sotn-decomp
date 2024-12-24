// SPDX-License-Identifier: AGPL-3.0-or-later
// Weapon ID #30. Used by weapons:
// Sword of Dawn, Unknown#177
#define FUNC_04_VOID
#include "weapon_private.h"
extern u16* g_WeaponCluts[];
extern s32 g_HandId;
#include "shared.h"
#include "w_030_1.h"
#include "w_030_2.h"
#define g_Animset w_030_1
#define g_Animset2 w_030_2
#include "sfx.h"

extern AnimationFrame D_D6000_8017A514[];
extern AnimationFrame D_D6000_8017A548[];
extern AnimationFrame* D_D6000_8017A628[];
extern FrameProperty D_D6000_8017A554[];
extern WeaponAnimation D_D6000_8017A5E4[];
extern u8 D_D6000_8017A640[];
extern s32 D_D6000_8017A648[];
extern u8 D_D6000_8017A650[];
extern u8 D_D6000_8017A658[];
extern u16 D_D6000_8017A660[];
extern s16 D_D6000_8017A66C[16];
extern s32 D_D6000_8017CC44;

static void EntityWeaponAttack(Entity* self) {
    WeaponAnimation* anim;
    WeaponAnimation* anim2;
    s8 animIndex;

    self->posX.val = PLAYER.posX.val;
    self->posY.val = PLAYER.posY.val;
    self->facingLeft = PLAYER.facingLeft;
    animIndex = (self->params >> 8) & 0x7f;
    anim = &D_D6000_8017A5E4[animIndex];

    if (PLAYER.ext.weapon.anim < anim->frameStart ||
        PLAYER.ext.weapon.anim >= (anim->frameStart + 7) ||
        g_Player.unk46 == 0) {
        DestroyEntity(self);
        return;
    }

    if (self->step == 0) {
        self->animSet = 10;
        self->palette = 0x110;
        self->unk5A = 0x64;
        if (g_HandId != 0) {
            self->palette += 0x18;
            self->unk5A += 2;
        }
        self->palette += anim->palette;
        self->flags = FLAG_UNK_20000 | FLAG_POS_PLAYER_LOCKED;
        self->zPriority = PLAYER.zPriority - 2;
        self->drawMode = DRAW_TPAGE | DRAW_TPAGE2 | DRAW_UNK_40;
        SetWeaponProperties(self, 0);
        self->step++;
    }

    self->ext.weapon.anim = PLAYER.ext.weapon.anim - anim->frameStart;

    if ((PLAYER.animFrameDuration == 1) &&
        (PLAYER.animFrameIdx == anim->soundFrame)) {
        g_api.PlaySfx(anim->soundId);
    }

    if (g_api.UpdateUnarmedAnim(anim->frameProps, anim->frames) < 0) {
        DestroyEntity(self);
        return;
    }

    self->drawFlags = PLAYER.drawFlags;
    self->rotY = PLAYER.rotY;
    self->rotPivotY = PLAYER.rotPivotY;
}

extern s16 D_D6000_8017A5F4[10];

#ifdef VERSION_PSP
extern s8 D_D6000_8017A608[15];
extern s8 D_D6000_8017A618[16];
#else
extern u8 D_D6000_8017A608[15];
extern u8 D_D6000_8017A618[16];
#endif

void func_ptr_80170004(Entity* self) {
    Primitive* prim;
    Collider collider;
    s16 x, y;
    s16 t;
    u16 clut;
    u8 v;
    bool flag;
    s32 i, j, k;

    s32 buffer[16];
    s16 xValues[16];
    s16 yValues[16];
    Entity* entity;
    s32 entityID;

    v = 0;
    clut = 0x110;
    if (g_HandId != 0) {
        v += 0x80;
        clut += 0x18;
    }
    flag = false;

    for (i = 0; i < LEN(buffer); i++) {
        buffer[i] = 0;
    }

    switch (self->step) {
    case 0:
        if (rand() & 7) {
            self->ext.weapon.unk90 = 1;
        } else {
            self->ext.weapon.unk90 = 6;
        }

        self->primIndex = g_api.AllocPrimitives(PRIM_GT4, 11);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }

        prim = &g_PrimBuf[self->primIndex];

        prim->u0 = prim->u2 = 0x70;
        prim->u1 = prim->u3 = 0x7F;
        prim->v0 = prim->v1 = v + 0x38;
        prim->v2 = prim->v3 = v + 0x7F;

        prim->g0 = prim->b0 = prim->r0 = prim->g1 = prim->b1 = prim->r1 =
            prim->g2 = prim->b2 = prim->r2 = prim->g3 = prim->b3 = prim->r3 =
                0x80;

        prim->clut = clut;
        prim->tpage = 0x19;
        prim->priority = PLAYER.zPriority + 2;

#ifdef VERSION_PSP
        prim->drawMode = DRAW_COLORS | DRAW_UNK02;
#else
        prim->drawMode = DRAW_UNK_40 | DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS |
                         DRAW_UNK02 | DRAW_TRANSP;
#endif

        for (i = 0; i < 10; i++) {
            prim = prim->next;
            prim->u0 = prim->u2 = 0x70;
            prim->u1 = prim->u3 = 0x7F;

            prim->v0 = prim->v1 = 0x38 + v + (i * 8);
            prim->v2 = prim->v3 = 0x38 + v + ((i + 1) * 8) - 1;

            prim->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS |
                             DRAW_UNK02 | DRAW_TRANSP;
            prim->tpage = 0x19;
            prim->priority = PLAYER.zPriority + 4;
            prim->clut = 0x15F;
        }

        self->facingLeft = PLAYER.facingLeft;
        self->flags = FLAG_POS_CAMERA_LOCKED | FLAG_HAS_PRIMS;
        SetSpeedX(FIX(1.5));
        self->velocityY = FIX(-5.125);
        self->ext.weapon.lifetime = 8;
        self->ext.weapon.unk80 = self->ext.weapon.unk82 = 0;
        self->ext.weapon.unk92 = D_D6000_8017A618[rand() & 0xF];
        self->ext.weapon.unk94 = PLAYER.posY.i.hi;
        self->ext.weapon.unk96 = PLAYER.posX.i.hi;
        g_Player.timers[10] = 4;

        self->step++;
        break;

    case 1:

        self->ext.weapon.unk80++;
        if (self->ext.weapon.unk80 > 8) {
            self->ext.weapon.unk80 = 8;
        }

        // n.b.! BUG: unk82 is incremented but unk80 is clamped
        self->ext.weapon.unk82 += 4;
        if (self->ext.weapon.unk80 > 0x18) {
            self->ext.weapon.unk80 = 0x18;
        }

        self->posX.val += self->velocityX;
        self->posY.val += self->velocityY;

        if (--self->ext.weapon.lifetime == 0) {
            x = self->ext.weapon.unk96;
            y = self->ext.weapon.unk94 + 0x19;

            for (i = 0; i < 8; i++) {
                g_api.CheckCollision(x, y + 7, &collider, 0);
                if (collider.effects & EFFECT_SOLID) {
                    y += 7 + collider.unk18;
                    g_api.CheckCollision(x, y - 1, &collider, 0);

                    if ((collider.effects & (EFFECT_UNK_8000 | EFFECT_SOLID)) ==
                        EFFECT_SOLID) {
                        buffer[i] = 2;
                    } else if (collider.effects & EFFECT_SOLID) {
                        y += collider.unk18 - 1;
                    }
                    xValues[i] = x;
                    yValues[i] = y;
                } else {
                    buffer[i] = 1;
                }
                if (self->facingLeft == 0) {
                    x += 7;
                } else {
                    x -= 7;
                }
            }

            x = self->ext.weapon.unk96;
            y = self->ext.weapon.unk94 + 0x19;
            for (i = 8; i < 15; i++) {
                if (self->facingLeft == 0) {
                    x -= 7;
                } else {
                    x += 7;
                }
                g_api.CheckCollision(x, y + 7, &collider, 0);
                if (collider.effects & EFFECT_SOLID) {
                    y += 7 + collider.unk18;
                    g_api.CheckCollision(x, y - 1, &collider, 0);

                    if ((collider.effects & (EFFECT_UNK_8000 | EFFECT_SOLID)) ==
                        EFFECT_SOLID) {
                        buffer[i] = 2;
                    } else if (collider.effects & EFFECT_SOLID) {
                        y += collider.unk18 - 1;
                    }
                    xValues[i] = x;
                    yValues[i] = y;
                } else {
                    buffer[i] = 1;
                }
            }

            for (j = 0; j < self->ext.weapon.unk90; j++) {
                for (i = 0; i < LEN(D_D6000_8017A608); i++) {
                    if (buffer[D_D6000_8017A608[i]] == 0) {
                        entity = &g_Entities[UNK_ENTITY_11];

                        if (g_HandId) {
                            entityID = 0xF2;
                        } else {
                            entityID = 0xE2;
                        }

                        for (k = 0; k < LEN(D_D6000_8017A608); k++, entity++) {
                            if (entity->entityId == entityID &&
                                abs(entity->posX.i.hi -
                                    xValues[D_D6000_8017A608[i]]) < 3) {
                                break;
                            }
                        }

                        if (k == LEN(D_D6000_8017A608)) {
                            break;
                        }
                    }
                }

                if (self->ext.weapon.unk90 == 6) {
                    k = 0x10;
                } else {
                    k = 0;
                }
                // same weapon factory ID as w_051
                entity = g_api.CreateEntFactoryFromEntity(
                    self, WFACTORY2(0x3E, self->ext.weapon.unk92 + k), 0);

                if (entity) {
                    self->ext.weapon.accelerationX = 1;
                    self->ext.weapon.unk98 = entity->posX.i.hi =
                        xValues[D_D6000_8017A608[i]];
                    self->ext.weapon.unk9A = entity->posY.i.hi =
                        yValues[D_D6000_8017A608[i]] - 0x19;

                    buffer[D_D6000_8017A608[i]] = 1;
                    self->ext.weapon.unk92++;
                    self->ext.weapon.unk92 = self->ext.weapon.unk92 % 6;
                }
            }

            self->ext.weapon.lifetime = 8;
            g_api.PlaySfxVolPan(SFX_TELEPORT_BANG_A, 0x58, 0);
            self->step++;
        }
        break;

    case 2:
        if (--self->ext.weapon.lifetime == 0) {
            for (i = 0; i < 10; i++) {
                D_D6000_8017A5F4[i] = 0x199 * i;
            }
            self->ext.weapon.childPalette = 0xFF;
            self->ext.weapon.unk8A = 0;
            self->step++;
        }
        break;

    case 3:
        self->ext.weapon.unk7E += 4;
        if (self->ext.weapon.unk7E > 0x120) {
            self->ext.weapon.unk7E = 0x120;
        }
        flag = true;

        self->ext.weapon.unk8A++;

        self->ext.weapon.childPalette -= 8;
        if (self->ext.weapon.childPalette < 0) {
            self->ext.weapon.childPalette = 0;
        }

        if (self->ext.weapon.unk8A >= 10) {
            self->ext.weapon_030.unk84 = 1 + (self->ext.weapon.unk8A - 10) / 4;
        }

        if (self->ext.weapon_030.unk84 >= 7 &&
            self->ext.weapon.unk7E == 0x120) {
            self->step++;
        }
        break;

    case 4:
        prim = &g_PrimBuf[self->primIndex];
        prim->g3 -= 6;
        if (prim->g3 < 10) {
            prim->g3 = 10;
        }

        prim->r3 += 6;
        if (prim->r3 > 240) {
            prim->r3 = 240;
        }
        prim->r0 = prim->r1 = prim->r2 = prim->r3;
        prim->b0 = prim->b1 = prim->b2 = prim->b3 = prim->g0 = prim->g1 =
            prim->g2 = prim->g3;

        // Flashing effect
        if (g_GameTimer & 1) {
            prim->drawMode |= DRAW_HIDE;
        } else {
            prim->drawMode &= ~DRAW_HIDE;
        }

        self->ext.weapon.unk7E -= 8;
        if (self->ext.weapon.unk7E < 0) {
            DestroyEntity(self);
            return;
        }
        break;
    }

    x = self->posX.i.hi;
    y = self->posY.i.hi;

    prim = &g_PrimBuf[self->primIndex];

    prim->x0 = prim->x2 = x - self->ext.weapon.unk80;
    prim->x1 = prim->x3 = x + self->ext.weapon.unk80;

    prim->y0 = prim->y1 = y - 4 - self->ext.weapon.unk82;
    prim->y2 = prim->y3 = y + 4 + self->ext.weapon.unk82;
    prim = prim->next;

    for (i = 0; i < LEN(D_D6000_8017A5F4) - 1; i++) {
        prim->x0 = prim->x2 = x - 8;
        prim->x1 = prim->x3 = x + 8;

        prim->y0 = prim->y1 = y + ((i + 0) * 8) - 0x24;
        prim->y2 = prim->y3 = y + ((i + 1) * 8) - 0x24;

        t = D_D6000_8017A5F4[i];
        prim->r0 = prim->r1 =
            (((rcos(t) + 0x1000) >> 6) * self->ext.weapon.unk7E) / 0x100;

        t = D_D6000_8017A5F4[i + 1];
        prim->r2 = prim->r3 =
            (((rcos(t) + 0x1000) >> 6) * self->ext.weapon.unk7E) / 0x100;

        D_D6000_8017A5F4[i] += 0x80;

        prim = prim->next;
    }

    t = self->ext.weapon.unk8A;
    if (t > 10) {
        t = 10;
    }

    // weapon_030.unk9C is possibly weapon.accelerationX
    if (flag && self->ext.weapon_030.unk9C) {
        prim->x0 = x;
        prim->y0 = y;
        prim->x1 = x + ((0 + self->ext.weapon.unk98 - x) * t / 10);
        prim->y1 = y + ((25 + self->ext.weapon.unk9A - y) * t / 10);
        prim->r0 = self->ext.weapon.childPalette / 2;
        prim->r1 = self->ext.weapon.childPalette;
        prim->priority = PLAYER.zPriority + 6;
        prim->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_UNK02 | DRAW_TRANSP;
        prim->type = PRIM_LINE_G2;
    }
}

void func_ptr_80170008(Entity* self) {
    s32 smallOffset;
    s32 largeOffset;
    s32 clut;
    u16 effect;
    s16 offsetY;
    s32 temp_s4;
    u16 s0;
    s32 var_v1;
    u8 left;
    s16 a0;

    Collider collider;
    Primitive* prim;
    s16 posX, posY;
    s16 randRes;
    s32 i;
    s32 velX;
    bool stopAnimationUpdate;
    u32 step;
    s32 temp;

    temp_s4 = (self->params & 0xF00) >> 8;
    temp = self->params & 0x1000;
    stopAnimationUpdate = false;
    step = self->step;

    if (step < 7 && self->hitFlags) {
        self->hitFlags = 0;
        self->ext.weapon_030.unk7E = 0x18;
        self->step = 7;
        if (--self->ext.weapon_030.unkA4 > 0) {
            self->step = 8;
        }
    }

    switch (self->step) {
    case 0:
        s0 = temp_s4;
        if (self->ext.weapon_030.parent->ext.weapon_030.unk84 != (s0 + 1)) {
            return;
        }

        randRes = rand() & 1;
        self->primIndex = g_api.AllocPrimitives(PRIM_GT4, 14);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }

        left = 0;
        clut = 0x110;
        self->palette = D_D6000_8017A640[s0] + ((u16)randRes | 0x8110);
        if (temp) {
            self->palette = D_D6000_8017A660[s0];
        }
        self->unk5A = 0x64;
        if (g_HandId != 0) {
            left = 0x80;
            clut = 0x128;
            self->palette += 0x18;
            self->unk5A += 2;
        }

        prim = &g_PrimBuf[self->primIndex];

        for (i = 0; i < 1; i++) {
            prim->u0 = prim->u2 = 0xE0;
            prim->u1 = prim->u3 = 0xFF;
            prim->v0 = prim->v1 = left;
            prim->v2 = prim->v3 = left + 0x5F;
            prim->x0 = prim->x2 = self->posX.i.hi - 0x10;
            prim->x1 = prim->x3 = self->posX.i.hi + 0x10;
            prim->tpage = 0x19;
            prim->clut = clut + 2;
            prim->priority = PLAYER.zPriority + 10;
            prim->drawMode = DRAW_UNK02;
            prim = prim->next;
        }

        for (i = 0; i < 8; i++) {
            prim->u0 = prim->u2 = 0xE0;
            prim->u1 = prim->u3 = 0xFF;
            prim->v0 = prim->v1 = left + 0x60;
            prim->v2 = prim->v3 = left + 0x7F;
            prim->tpage = 0x19;
            prim->clut = clut + 2;
            prim->priority = PLAYER.zPriority + 12;
            prim->drawMode = DRAW_HIDE;
            prim = prim->next;
        }

        self->flags = FLAG_POS_CAMERA_LOCKED | FLAG_HAS_PRIMS;
        self->animSet = 0xA;
        a0 = temp_s4;
        self->anim = D_D6000_8017A628[a0];
        self->zPriority = PLAYER.zPriority + 2;
        self->facingLeft = (self->ext.weapon_030.parent->facingLeft + 1) & 1;
        self->ext.weapon_030.unk86 = D_D6000_8017A650[a0] + randRes;
        self->ext.weapon_030.unk90 = self->ext.weapon_030.unkA0 = -0x1000;
        self->ext.weapon_030.unk88 = self->ext.weapon_030.unk9C = -0x100;
        if (a0 == 1) {
            self->ext.weapon_030.unkA4 = 3;
        }
        g_api.func_80102CD8(4);
        g_api.PlaySfx(SFX_EXPLODE_A);
        self->step++;
        break;
    case 1:
        stopAnimationUpdate = 1;
        self->ext.weapon_030.unk88 += 0x18;
        self->ext.weapon_030.unk9C += 0x10;
        if (self->ext.weapon_030.unk88 > 0x60) {
            self->ext.weapon_030.unk88 = 0x60;
        }
        if (self->ext.weapon_030.unk9C > 0x80) {
            self->ext.weapon_030.unk9C = 0x80;
        }
        self->ext.weapon_030.unk90 += self->ext.weapon_030.unk88;
        self->ext.weapon_030.unkA0 += self->ext.weapon_030.unk9C;
        if (self->ext.weapon_030.unk90 > 0) {
            self->ext.weapon_030.unk90 = 0;
        }
        if (self->ext.weapon_030.unkA0 > 0) {
            self->ext.weapon_030.unkA0 = 0;
        }
        if ((self->ext.weapon_030.unk90 | self->ext.weapon_030.unkA0) == 0) {
            self->attack = 4;
            self->attackElement = ELEMENT_HIT;
            self->hitboxState = 2;
            self->nFramesInvincibility = 4;
            self->stunFrames = 4;
            self->hitEffect = 1;
            self->entityRoomIndex = 0;
            g_api.func_80118894(self);
            self->posY.i.hi++;
            a0 = temp_s4;
            if (a0 == 5) {
                self->posY.i.hi++;
            }
            self->step = D_D6000_8017A658[a0];
            if (a0 < 2) {
                SetSpeedX(D_D6000_8017A648[a0]);
            }
        }
        break;
    case 2:
        if (self->animFrameDuration == 1 && self->animFrameIdx == 2) {
            g_api.PlaySfx(SFX_CREAK);
        }
        if (self->animFrameDuration == 1 && self->animFrameIdx == 5) {
            g_api.PlaySfx(SFX_ARROW_SHOT_C);
            g_api.CreateEntFactoryFromEntity(
                self, 0x46 + ((g_HandId + 1) << 0xC) + ((temp_s4 - 2) << 0x10),
                0);
        }
        if (self->animFrameDuration < 0) {
            self->animFrameIdx = 0;
            self->animFrameDuration = 0;
            if (--self->ext.weapon_030.unk86 == 0) {
                self->ext.weapon_030.unk7E = 0x18;
                self->step = 7;
            }
        }
        break;
    case 3:
        posX = self->posX.i.hi;

        if (posX + g_Tilemap.scrollX.i.hi < g_Tilemap.x ||
            g_Tilemap.width < posX + g_Tilemap.scrollX.i.hi) {
            self->ext.weapon_030.unk7E = 0x18;
            self->hitFlags = 0;
            self->step = 7;
            return;
        }

        self->posY.i.hi += 4;

        g_api.CheckCollision(posX, (s16)(self->posY.i.hi + 0x18), &collider, 0);

        if (collider.effects & EFFECT_SOLID) {
            self->posY.i.hi = self->posY.i.hi + collider.unk18;
            velX = self->velocityX;
            effect = collider.effects & (EFFECT_UNK_8000 | EFFECT_UNK_4000 |
                                         EFFECT_UNK_2000 | EFFECT_UNK_1000);

            if (velX > 0) {
                if (effect == EFFECT_UNK_8000) {
                    if (velX * 0xA < 0) {
                        velX = (velX * 0xA + 0xF) >> 4;
                    } else {
                        velX = (velX * 0xA) >> 4;
                    }
                }
                if (effect == (EFFECT_UNK_8000 | EFFECT_UNK_1000)) {
                    if (velX * 0xD < 0) {
                        velX = (velX * 0xD + 0xF) >> 4;
                    } else {
                        velX = (velX * 0xD) >> 4;
                    }
                }
            } else {
                if (effect == (EFFECT_UNK_8000 | EFFECT_UNK_4000)) {
                    if (velX * 0xA < 0) {
                        velX = (velX * 0xA + 0xF) >> 4;
                    } else {
                        velX = (velX * 0xA) >> 4;
                    }
                }
                if (effect ==
                    (EFFECT_UNK_8000 | EFFECT_UNK_4000 | EFFECT_UNK_1000)) {
                    if (velX * 0xD < 0) {
                        velX = (velX * 0xD + 0xF) >> 4;
                    } else {
                        velX = (velX * 0xD) >> 4;
                    }
                }
            }

            self->posX.val += velX;
        } else {
            self->step = 4;
            self->velocityY = 0;
        }

        goto label;
    case 4:
        self->posX.val += self->velocityX;
        self->posY.val += self->velocityY;
        self->velocityY += FIX(0.15625);

        if (self->velocityY > FIX(8.0)) {
            self->velocityY = FIX(8.0);
        }

        g_api.CheckCollision(
            self->posX.i.hi, (s16)(self->posY.i.hi + 0x19), &collider, 0);

        if (collider.effects & EFFECT_SOLID) {
            self->ext.weapon_030.unk7E = 0x18;
            self->step = 3;
        }

    label:
        offsetY = 8;
        if (self->velocityX < 0) {
            offsetY = -8;
        }

        posX = self->posX.i.hi + offsetY;
        posY = self->posY.i.hi;

        g_api.CheckCollision(posX, (s16)(posY + 10), &collider, 0);
        if (collider.effects & EFFECT_UNK_0002) {
            self->ext.weapon_030.unk7E = 0x18;
            self->step = 7;
        }
        g_api.CheckCollision(posX, (s16)(posY - 6), &collider, 0);
        if (collider.effects & EFFECT_UNK_0002) {
            self->ext.weapon_030.unk7E = 0x18;
            self->step = 7;
        }
        break;
    case 5:
        if (self->ext.weapon_030.unk7C == 0) {
            if (--self->ext.weapon_030.unk86 < 0) {
                self->ext.weapon_030.unk7E = 0x18;
                self->step = 7;
                break;
            }

            randRes = (rand() & 1);

            for (i = 0; i < randRes + 2; i++) {
                g_api.CreateEntFactoryFromEntity(self, WFACTORY(0x46, 2), 0);
            }

            self->ext.weapon_030.unk7C = (rand() & 0x1F) + 0x50;
            if (self->ext.weapon_030.unk86 == 0) {
                self->ext.weapon_030.unk7C = 0x60;
            }
        }
        self->ext.weapon_030.unk7C--;
        break;
    case 6:
        if (self->animFrameIdx == 4 && self->animFrameDuration == 1) {
            g_api.CreateEntFactoryFromEntity(self, WFACTORY(0x6A, 0), 0);
        }
        if (self->animFrameDuration < 0) {
            self->ext.weapon_030.unk7E = 0x18;
            self->step = 7;
        }
        break;
    case 7:
    case 8:
        stopAnimationUpdate = true;
        self->drawFlags |= FLAG_BLINK;
        if (--self->ext.weapon_030.unk7E == 0) {
            if (self->step == 7) {
                DestroyEntity(self);
                return;
            }
            self->step = 3;
            self->drawFlags &= FLAG_DRAW_UNK40 | FLAG_DRAW_UNK20 |
                               FLAG_DRAW_UNK10 | FLAG_DRAW_UNK8 |
                               FLAG_DRAW_ROTZ | FLAG_DRAW_ROTY | FLAG_DRAW_ROTX;
            break;
        }
        break;
    }

    prim = &g_PrimBuf[self->primIndex];

    for (i = 0; i < 1; i++) {
        if (g_GameTimer & 1) {
            var_v1 = self->ext.weapon_030.unk90;
        } else {
            var_v1 = self->ext.weapon_030.unkA0;
        }
        prim->y0 = prim->y1 = self->posY.i.hi + 0x19 + ((var_v1 * 6) >> 8);
        prim->y2 = prim->y3 = self->posY.i.hi + 0x19;
        prim->x0 = self->posX.i.hi - 0x10 - (rand() & 0xF);
        if (!(g_GameTimer & 7)) {
            prim->x2 = prim->x2 - 1;
            prim->x3 = prim->x3 + 1;
        }
        prim = prim->next;
    }

    for (i = 0; i < 8; i++) {
        if ((g_GameTimer & 7) == i) {
            smallOffset = rand() & 7;
            largeOffset = smallOffset + 0xA;
            prim->x0 = prim->x2 =
                self->posX.i.hi + (rand() % 32) - 0x1A - smallOffset;
            prim->y1 = prim->y0 =
                self->posY.i.hi - (rand() % 24) - largeOffset + 0x19;
            prim->x1 = prim->x3 = prim->x0 + largeOffset * 2;
            prim->y2 = prim->y3 = prim->y0 + largeOffset * 2;
            if (self->ext.weapon_030.unk90 >= -0x480) {
                prim->y0 = prim->y1 = prim->y2 = prim->y3 = 0x180;
            } else {
                prim->drawMode = DRAW_UNK02;
            }
        }

        if (g_GameTimer & 1) {
            prim->y0--;
            prim->y1--;
            prim->y2--;
            prim->y3--;
        }

        if (!((i ^ g_GameTimer) & 1)) {
            prim->drawMode = DRAW_HIDE;
        } else {
            prim->drawMode = DRAW_UNK02;
        }
        prim = prim->next;
    }

    if (!stopAnimationUpdate) {
        g_api.UpdateAnim(D_D6000_8017A554, NULL);
    }
}

void func_ptr_8017000C(Entity* self) {
    s16 result;
    s16 angleDiff;
    s16 maskedParams;
    s32 temp_a2;
    s16 angle;
    s32 temp_lo;

    maskedParams = (self->params >> 8) & 0x7F;
    switch (self->step) {
    case 0:
        self->palette = 0x110;
        self->unk5A = 0x64;
        if (g_HandId != 0) {
            self->palette += 0x18;
            self->unk5A += 2;
        }
        self->flags = FLAG_POS_CAMERA_LOCKED;
        self->animSet = 0xA;
        self->animCurFrame = 0x64;
        self->zPriority = PLAYER.zPriority + 2;
        self->facingLeft = self->ext.weapon.parent->facingLeft;
        if (maskedParams == 1) {
            self->posY.i.hi -= 4;
        }
        if (maskedParams == 0) {
            self->posY.i.hi -= 0x10;
        }
        if (maskedParams == 2) {
            self->posY.i.hi -= 28 + (rand() & 15);
            self->posX.i.hi += D_D6000_8017A66C[D_D6000_8017CC44 % 3];
            self->posX.i.hi += -4 + (rand() & 7);
            self->ext.weapon.unk82 = (self->facingLeft + 1) & 1;
            self->facingLeft = 0;
            self->drawFlags = DRAW_COLORS;
            self->step = 2;
            g_api.PlaySfx(SFX_FAST_SWORD_SWISHES);
            self->ext.weapon.unk80 = rand();
            self->ext.weapon.lifetime = ((u8)self->params * 4) + 0x30;
            D_D6000_8017CC44++;
        } else {
            SetSpeedX(FIX(-5.5));
            self->posX.val += self->velocityX * 5;
        }
        self->attack = 4;
        self->attackElement = ELEMENT_HIT;
        self->hitboxState = 2;
        self->nFramesInvincibility = 4;
        self->stunFrames = 4;
        self->hitEffect = 1;
        self->entityRoomIndex = 0;
        g_api.func_80118894(self);
        self->hitboxWidth = 8;
        self->hitboxHeight = 4;
        self->step++;
        break;
    case 1:
        if (maskedParams == 2) {
            result = g_api.func_80118B18(
                self, self->ext.weapon_030.other, self->ext.weapon.unk82);
            if (result >= 0) {
                temp_a2 = self->ext.weapon.unk80 & 0xFFF;
                angle = temp_a2;
                angleDiff = abs(angle - result);
                if (self->ext.weapon.unk98 > angleDiff) {
                    self->ext.weapon.unk98 = angleDiff;
                }
                if (angle < result) {
                    if (angleDiff < 0x800) {
                        angle += self->ext.weapon.unk98;
                    } else {
                        angle -= self->ext.weapon.unk98;
                    }
                } else {
                    if (angleDiff < 0x800) {
                        angle -= self->ext.weapon.unk98;
                    } else {
                        angle += self->ext.weapon.unk98;
                    }
                }
                self->ext.weapon.unk80 = angle & 0xFFF;
            }
            self->velocityX =
                (rcos(self->ext.weapon.unk80) * self->ext.weapon.unk9A) >> 5;
            temp_lo = rsin(self->ext.weapon.unk80) * self->ext.weapon.unk9A;
            self->ext.weapon.unk98 += 0x18;
            self->rotZ = -self->ext.weapon.unk80 + 0x800;
            self->velocityY = -(temp_lo >> 5);
        }
        if (self->hitFlags != 0) {
            self->ext.weapon.lifetime = 10;
            self->step++;
        }
        self->posX.val += self->velocityX;
        self->posY.val += self->velocityY;
        return;
    case 2:
        self->drawFlags |= FLAG_BLINK;
        if (--self->ext.weapon.lifetime == 0) {
            DestroyEntity(self);
            return;
        }
        return;
    case 3:
        self->ext.weapon.unk80 += 0x100;
        self->rotZ = -self->ext.weapon.unk80 + 0x800;
        if (--self->ext.weapon.lifetime == 0) {
            self->ext.weapon_030.other = g_api.func_80118970();
            self->ext.weapon.unk98 = 0x20;
            self->ext.weapon.unk9A = 0x600;
            g_api.PlaySfx(SFX_ARROW_SHOT_C);
            self->step = 1;
        }
        break;
    }
}

s32 func_ptr_80170010(Entity* self) {
    s32 hitboxSize;

    if (self->ext.weapon.parent->entityId == 0) {
        DestroyEntity(self);
        return;
    }

    switch (self->step) {
    case 0:
        self->animSet = 9;
        self->flags = FLAG_POS_CAMERA_LOCKED | FLAG_UNK_100000;
        self->drawFlags = FLAG_DRAW_ROTX | FLAG_DRAW_ROTY | FLAG_DRAW_ROTZ;
        self->rotX = self->rotY = 0x20;
        self->anim = D_D6000_8017A514;
        if ((u8)self->params != 0) {
            self->anim = D_D6000_8017A548;
        }
        self->zPriority = PLAYER.zPriority + 8;
        self->facingLeft = (self->ext.weapon.parent->facingLeft + 1) & 1;
        SetSpeedX(FIX(3.5));
        self->attack = 0x14;
        self->hitboxState = 2;
        self->nFramesInvincibility = 4;
        self->stunFrames = 4;
        self->attackElement = ELEMENT_HIT;
        self->hitEffect = 1;
        self->entityRoomIndex = 0;
        self->posY.i.hi -= 0x27;
        g_api.func_80118894(self);
        self->ext.weapon.vol = 0x30;
        self->step++;
        break;
    case 1:
        if (!(g_GameTimer & 7)) {
            FntPrint("vol:%02x\n", self->ext.weapon.vol);
            g_api.PlaySfxVolPan(SFX_EXPLODE_FAST_A, self->ext.weapon.vol, 0);
            self->ext.weapon.vol += 8;
            if (self->ext.weapon.vol > 0x7F) {
                self->ext.weapon.vol = 0x7F;
            }
        }
        self->rotZ += 0x100;
        self->rotX += 2;
        if (self->rotX > 0x100) {
            self->rotX = 0x100;
        }
        self->rotY = self->rotX;
        if (self->ext.weapon.parent->animFrameIdx == 0x20 &&
            self->animFrameDuration == 1) {
            g_api.PlaySfx(SFX_EXPLODE_SMALL);
            if ((u8)self->params != 0) {
                self->drawMode = DRAW_UNK_40 | DRAW_TPAGE;
                self->step++;
                break;
            }
            DestroyEntity(self);
            return;
        }
        break;
    case 2:
        self->posX.val += self->velocityX;
        if (!(g_GameTimer & 3)) {
            self->rotZ += 0x400;
        }
        if (!(g_GameTimer & 1) && (rand() & 1)) {
            g_api.CreateEntFactoryFromEntity(self, FACTORY(0x24, 1), 0);
        }
        if (self->hitFlags != 0) {
            self->step++;
        }
        break;
    case 3:
        self->rotX -= 16;
        self->rotY = self->rotX;
        if (self->rotX < 0x40) {
            self->hitboxState = 0;
            self->animSet = 0;
            self->ext.weapon.lifetime = 0x80;
            self->step++;
        }
        /* fallthrough */
    case 4:
        if (--self->ext.weapon.lifetime == 0) {
            DestroyEntity(self);
            return;
        }
        break;
    }

    hitboxSize = (self->rotX >> 0x6) * 3;
    self->hitboxWidth = hitboxSize;
    self->hitboxHeight = hitboxSize;
}

static s32 func_ptr_80170014(Entity* self) {}

static int GetWeaponId(void) { return 30; }

static void EntityWeaponShieldSpell(Entity* self) {}

static void func_ptr_80170024(Entity* self) {}

static void func_ptr_80170028(Entity* self) {}

static void WeaponUnused2C(void) {}

static void WeaponUnused30(void) {}

static void WeaponUnused34(void) {}

static void WeaponUnused38(void) {}

static void WeaponUnused3C(void) {}
