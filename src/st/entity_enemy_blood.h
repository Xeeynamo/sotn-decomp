void EntityEnemyBlood(Entity* self) {
    int fakeTemp; // !TODO: !FAKE
    Primitive* prim;
    s32 var_a0_2;
    u16 params;
    s16 posX;
    s32 rnd;
    s32 i;

    switch (self->step) {
    case 0:
        i = g_api.func_800EDB58(17, 12);
        if (i != -1) {
            InitializeEntity(g_InitializeData0);
            prim = &g_PrimBuf[i];
            self->primIndex = i;
            self->animSet = ANIMSET_DRA(0);
            params = self->params;
            self->hitboxState = 1;
            self->ext.generic.unk7C.s = 48;
            self->hitboxHeight = 8;
            self->zPriority = 0xC0;
            self->hitboxWidth = 0;
            self->flags |= FLAG_HAS_PRIMS;

            for (i = 12; i != 0;) {
                prim->x0 = self->posX.i.hi + ((Random() & (fakeTemp = 7)) - 5);
                rnd = (Random() & 7) - 5;
                prim->y0 = self->posY.i.hi + rnd;
                *(s32*)&prim->r1 = 0;
                *(s32*)&prim->x1 = 0;
                prim->u0 = 4;
                prim->v0 = 4;

                if (params != 0) {
                    UnkEntityFunc0(
                        0xCC0 + i * 64, ((Random() & 0xF) * 0x10) + 0x180);
                } else {
                    UnkEntityFunc0(
                        0xB40 - i * 64, ((Random() & 0xF) * 0x10) + 0x180);
                }

                *(s32*)&prim->u1 = self->velocityX;
                *(s32*)&prim->r2 = self->velocityY;

                var_a0_2 = *(s32*)&prim->u1;
                if (var_a0_2 <= -1) {
                    var_a0_2 += 0x3F;
                }

                *(s32*)&prim->r3 = -(var_a0_2 >> 6);
                *(s32*)&prim->x3 = -(*(s32*)&prim->r2 / 48) + 0xC00;

                prim->x2 = prim->y2 = (Random() & 7) + 7;
                prim->r0 = 128;
                prim->b0 = 16;
                prim->g0 = 0;
                prim->priority = self->zPriority;
                prim->blendMode = 2;
                i--;
                if (i != 0) {
                    prim++;
                }
            }

            if (params != 0) {
                self->velocityX = FIX(1.25);
                self->ext.generic.unk80.modeS32 = -0x200;
            } else {
                self->velocityX = FIX(-1.25);
                self->ext.generic.unk80.modeS32 = 0x200;
            }
            self->velocityY = 0;
            break;
        }
        DestroyEntity(self);
        break;

    case 1:
        if (!(--self->ext.generic.unk7C.u)) {
            DestroyEntity(self);
            break;
        }

        if (self->hitboxState != 0) {
            if (g_Player.unk0C & 0x02000000) {
                posX = self->posX.i.hi;
                self->velocityX += self->ext.generic.unk80.modeS32;

                MoveEntity(self); // argument pass necessary to match

                posX -= self->posX.i.hi;
                if (posX < 0) {
                    posX = -posX;
                }

                if (self->ext.generic.unk7C.u > 16) {
                    self->ext.generic.unk7E.modeU16 += posX;
                    self->hitboxWidth = self->ext.generic.unk7E.modeU16 / 2;
                    self->hitboxHeight =
                        (self->ext.generic.unk7E.modeU16 / 4) + 8;
                } else {
                    self->hitboxState = 0;
                }

                if (self->hitFlags != 0) {
                    if (g_Player.unk56 == 0) {
                        g_Player.unk56 = 1;
                        g_Player.unk58 = 8;
                        if (g_api.CheckEquipmentItemCount(
                                ITEM_BLOODSTONE, ACCESSORY_TYPE)) {
                            g_Player.unk58 *= 2;
                        }
                    }
                    g_Player.unk10++;
                    self->hitboxState = 0;
                }
            } else {
                self->hitboxState = 0;
            }
        }

        prim = &g_PrimBuf[self->primIndex];
        for (i = 12; i != 0; i--, prim++) {
            *(u16*)&prim->b1 = prim->x0;
            prim->y1 = prim->y0;
            *(s32*)&prim->u1 += *(s32*)&prim->r3;
            *(s32*)&prim->r2 += *(s32*)&prim->x3;
            *(s32*)&prim->r1 += *(s32*)&prim->u1;
            *(s32*)&prim->x1 += *(s32*)&prim->r2;
            *(s16*)&prim->x0 = *(s16*)&prim->b1;
            prim->y0 = prim->y1;
            prim->x2--;

            if ((prim->x2 == 0) && (prim->u0 != 0)) {
                prim->v0--;
                prim->u0--;
                if (!(prim->u0 & 1)) {
                    prim->x0++;
                    prim->y0++;
                }
                prim->x2 = *(s32*)&prim->y2;
            }
        }
    }
}