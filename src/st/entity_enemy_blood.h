// SPDX-License-Identifier: AGPL-3.0-or-later
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
            InitializeEntity(g_InitializeData0);
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
        if (!(--self->ext.bloodDroplets.timer)) {
            DestroyEntity(self);
            break;
        }

        if (self->hitboxState) {
            if (!(g_Player.unk0C & PLAYER_STATUS_ABSORB_BLOOD)) {
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
