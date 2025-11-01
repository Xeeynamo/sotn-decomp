// SPDX-License-Identifier: AGPL-3.0-or-later
#include <stage.h>

// the signature is purposely wrong for this file
// this is how the original source code worked
void MoveEntity(Entity*);

#if defined(VERSION_HD)
static u32 padding = 0;
#endif

extern EInit g_EInitObtainable;

u16 g_ESoulStealOrbAngles[] = {
    0x820, 0x840, 0x860, 0x880, 0x8C0, 0x900, 0x940, 0xA00,
};

s16 g_ESoulStealOrbSprt[] = {
    // clang-format off
    -3,  -3,  8,  8,  208, 104, 216, 112,
    -3,  -3,  8,  8,  200, 104, 208, 112,
    -7,  -7,  16, 15, 200, 112, 216, 127,
    -11, -11, 24, 23, 128, 104, 152, 127,
    -11, -11, 24, 23, 152, 104, 176, 127,
    -11, -11, 24, 23, 176, 104, 200, 127,
    // clang-format on
};

u8 g_ESoulStealOrbAnim[] = {4, 2, 3, 3, 3, 4, 3, 5, 3, 6, 3, 3, 0, 0};

#ifdef VERSION_PSP
#include "e_particles_maria.h"
#endif

// The white flying orbs of energy that Alucard summons as part of the Soul
// Steal spell
void EntitySoulStealOrb(Entity* self) {
    u16 angle;
    Primitive* prim;
    s32 primIndex;
    s16* spr;
    u16 direction;
    Entity* player;

#ifdef VERSION_PSP
    if (g_PlayableCharacter == PLAYER_MARIA) {
        g_Player.unk28 = &func_psp_0923B2F0;
        func_psp_0923AD68(self);
        return;
    }
#endif

    player = &PLAYER;
    switch (self->step) {
    case 0:
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 1);
        if (primIndex != -1) {
            InitializeEntity(g_EInitObtainable);
            prim = &g_PrimBuf[primIndex];
            prim->drawMode = DRAW_HIDE;
            self->flags |= FLAG_HAS_PRIMS;
            self->primIndex = primIndex;
            self->animSet = ANIMSET_DRA(0);
            angle = GetAngleBetweenEntities(self, &PLAYER);
            direction = 0;
            if (self->posY.i.hi > 112) {
                direction = 1;
            }
            if (self->posX.i.hi < PLAYER.posX.i.hi) {
                direction ^= 1;
            }
            if (direction) {
                angle -= g_ESoulStealOrbAngles[Random() & 7];
            } else {
                angle += g_ESoulStealOrbAngles[Random() & 7];
            }
            self->ext.soulStealOrb.angle = angle;
            self->ext.soulStealOrb.unk80 = 0x400;
            self->ext.soulStealOrb.unk7E = 0;
            self->hitboxState = 0;
            return;
        }
        DestroyEntity(self);
        break;

    case 1:
        self->ext.soulStealOrb.unk82++;
        if (self->ext.soulStealOrb.unk82 == 16) {
            self->hitboxState = 1;
        }
        if (self->hitFlags) {
            if (!g_Player.unk56) {
                g_Player.unk56 = 1;
                g_Player.unk58 = 8;
            }
            DestroyEntity(self);
            return;
        }
        if (self->scaleX < 0x100) {
            self->scaleX = self->scaleY += 0x10;
        }
        if (self->ext.soulStealOrb.unk7E < 0x200) {
            self->ext.soulStealOrb.unk7E += 2;
        }
        if (self->ext.soulStealOrb.unk80 < 0x800) {
            self->ext.soulStealOrb.unk80 += 4;
        }
        // soulStealOrb.angle changed to u16
        angle = GetAngleBetweenEntities(self, &PLAYER);
        self->ext.soulStealOrb.angle = angle = GetNormalizedAngle(
            self->ext.soulStealOrb.unk7E, self->ext.soulStealOrb.angle, angle);
        UnkEntityFunc0(angle, self->ext.soulStealOrb.unk80);
        MoveEntity(self);
        prim = &g_PrimBuf[self->primIndex];
        AnimateEntity(g_ESoulStealOrbAnim, self);
        prim->tpage = 0x18;
        prim->clut = PAL_UNK_194;
        angle = self->animCurFrame;
#ifdef VERSION_PSP
        angle = (angle - 1) * 8;
#else
        angle = (angle * 8) - 8;
#endif
        spr = &g_ESoulStealOrbSprt[angle];
        prim->x0 = prim->x2 = self->posX.i.hi + *spr++;
        prim->y0 = prim->y1 = self->posY.i.hi + *spr++;
        prim->x1 = prim->x3 = prim->x0 + *spr++;
        prim->y2 = prim->y3 = prim->y0 + *spr++;
        prim->u0 = prim->u2 = *spr++;
        prim->v0 = prim->v1 = *spr++;
        prim->u1 = prim->u3 = *spr++;
        prim->v2 = prim->v3 = *spr;
        prim->priority = self->zPriority;
        prim->drawMode = DRAW_DEFAULT;
        break;
    }
}

// params: True if facing left
void EntityEnemyBlood(Entity* self) {
    const int NParticles = 12;
    FakePrim* prim;
    s32 i;
    s16 x;
    u16 facingLeft;

    switch (self->step) {
    case 0:
        i = g_api.func_800EDB58(PRIM_TILE_ALT, NParticles);
        if (i != -1) {
            InitializeEntity(g_EInitObtainable);
            facingLeft = self->params;
            self->flags |= FLAG_HAS_PRIMS;
            self->primIndex = i;
            self->animSet = ANIMSET_DRA(0);
            self->hitboxState = 1;
            self->ext.bloodDroplets.timer = 48;
            self->hitboxWidth = 0;
            self->hitboxHeight = 8;
            self->zPriority = 0xC0;

            prim = (FakePrim*)&g_PrimBuf[i];
            i = NParticles;
            while (true) {
                prim->x0 = self->posX.i.hi - 5 + (Random() & 7);
                prim->y0 = self->posY.i.hi - 5 + (Random() & 7);
                prim->posX.val = 0;
                prim->posY.val = 0;
                prim->w = 4;
                prim->h = 4;

                if (facingLeft) {
                    UnkEntityFunc0(
                        0xCC0 + i * 64, (Random() & 0xF) * 0x10 + 0x180);
                } else {
                    UnkEntityFunc0(
                        0xB40 - i * 64, (Random() & 0xF) * 0x10 + 0x180);
                }

                prim->velocityX.val = self->velocityX;
                prim->velocityY.val = self->velocityY;
                prim->accelerationX.val = -(prim->velocityX.val / 64);
                prim->accelerationY.val = -(prim->velocityY.val / 48) + 0xC00;

                prim->x2 = prim->y2 = (Random() & 7) + 7;
                prim->r0 = 128;
                prim->b0 = 16;
                prim->g0 = 0;
                prim->priority = self->zPriority;
                prim->drawMode = DRAW_UNK02;
                if (!--i) {
                    break;
                }
                prim++;
            }

            if (facingLeft) {
                self->velocityX = FIX(1.25);
                self->ext.bloodDroplets.speed = -0x200;
            } else {
                self->velocityX = FIX(-1.25);
                self->ext.bloodDroplets.speed = 0x200;
            }
            self->velocityY = 0;
        } else {
            DestroyEntity(self);
        }
        break;

    case 1:
        if (!--self->ext.bloodDroplets.timer) {
            DestroyEntity(self);
            break;
        }

        if (self->hitboxState) {
            if (!(g_Player.status & PLAYER_STATUS_ABSORB_BLOOD)) {
                self->hitboxState = 0;
            } else {
                self->velocityX += self->ext.bloodDroplets.speed;

                x = self->posX.i.hi;
                MoveEntity(self);
                x -= self->posX.i.hi;
                if (x < 0) {
                    x = -x;
                }

                if (self->ext.bloodDroplets.timer > 16) {
                    self->ext.bloodDroplets.size += x;
                    self->hitboxWidth = self->ext.bloodDroplets.size / 2;
                    self->hitboxHeight = self->ext.bloodDroplets.size / 4 + 8;
                } else {
                    self->hitboxState = 0;
                }

                if (self->hitFlags) {
                    if (!g_Player.unk56) {
                        g_Player.unk56 = 1;
                        g_Player.unk58 = 8;
                        if (g_api.CheckEquipmentItemCount(
                                ITEM_BLOODSTONE, EQUIP_ACCESSORY)) {
                            g_Player.unk58 *= 2;
                        }
                    }
                    g_Player.unk10++;
                    self->hitboxState = 0;
                }
            }
        }

        prim = (FakePrim*)&g_PrimBuf[self->primIndex];
        i = NParticles;
        while (true) {
            prim->posX.i.hi = prim->x0;
            prim->posY.i.hi = prim->y0;
            prim->velocityX.val += prim->accelerationX.val;
            prim->velocityY.val += prim->accelerationY.val;
            prim->posX.val += prim->velocityX.val;
            prim->posY.val += prim->velocityY.val;
            prim->x0 = prim->posX.i.hi;
            prim->y0 = prim->posY.i.hi;

            if (!--prim->x2 && prim->w) {
                prim->h--;
                prim->w--;
                if (!(prim->w & 1)) {
                    prim->x0++;
                    prim->y0++;
                }
                prim->x2 = prim->y2;
            }
            if (!--i) {
                break;
            }
            prim++;
        }
    }
}
