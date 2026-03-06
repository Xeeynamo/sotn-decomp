// SPDX-License-Identifier: AGPL-3.0-or-later

extern u16 g_EInitInteractable[];

SVECTOR v0 = {-8, -8, 0};
SVECTOR v1 = {8, -8, 0};
SVECTOR v2 = {-8, 8, 0};
SVECTOR v3 = {8, 8, 0};
u16 D_80182850[] = {0x17, 0x17, 0x17, 0x17, 0x17, 0x17, 0x17, 0x17,
                    0x17, 0x17, 0x17, 0x17, 0x17, 0x17, 0x17, 0x17,
                    0x17, 0x19, 0x1A, 0x1B, 0x1C, 0x1D};
SVECTOR clearRotation = {ROT(0), ROT(0), ROT(0)};

void EntityLifeUpSpawn(Entity* self) {
    long p, flag;
    Collider collider;
    Primitive* prim;
    s32 count_low_x1;
    s32 params;
    s32 XY_var;
    s32 primIndex;
    s32 i, j, k;
    s16 xVar, yVar;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitInteractable);
        self->animSet = 2;
        self->animCurFrame = 0;
        // We allocate 385 primitives for this entity!!!
        primIndex = g_api.func_800EDB58(PRIM_GT4, 385);
        if (primIndex == -1) {
            self->step = 6;
            return;
        }
        self->flags |= FLAG_HAS_PRIMS;
        self->primIndex = primIndex;
        prim = &g_PrimBuf[primIndex];
        self->ext.lifeUpSpawn.prim2 = prim;
        prim->tpage = 0x1A;
        prim->clut = PAL_UNK_19F;
        prim->u0 = prim->u2 = 0;
        prim->u1 = prim->u3 = 0x3F;
        prim->v0 = prim->v1 = 0xC0;
        prim->v2 = prim->v3 = 0x3F + 0xC0;
        prim->x0 = prim->x1 = prim->x2 = prim->x3 = self->posX.i.hi;
        prim->y0 = prim->y1 = prim->y2 = prim->y3 = self->posX.i.hi;
        prim->priority = 0xC0;
        prim->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_UNK02 | DRAW_TRANSP;
        prim = prim->next;
        self->ext.lifeUpSpawn.prim1 = prim;
        // This has 8 * 3 * 8 = 192 total cycles. With 2 prims per cycle, that's
        // 384.
        for (i = 0; i < 8; i++) {
            for (j = 0; j < 3; j++) {
                for (k = 0; k < 8; k++) {
                    UnkPolyFunc2(prim);
                    prim->tpage = 0x1A;
                    prim->clut = PAL_UNK_194;
                    prim->u0 = prim->u2 = 0;
                    prim->u1 = prim->u3 = 0x10;
                    prim->v0 = prim->v1 = 0x50;
                    prim->v2 = prim->v3 = 0x50 + 0x10;
                    PRED(prim) = 0x20;
                    PGRN(prim) = 0;
                    PBLU(prim) = 0;
                    prim->next->x2 = prim->next->y2 = FLT(1);
                    LOH(prim->next->tpage) = k * ROT(45);
                    prim->next->x3 = ROT(0);
                    prim->next->y3 = j * ROT(118.125);
                    // Not clear what this prim is using u0 and r1 for.
                    // Note that every-other prim has this. prim is a normal
                    // primitive, while prim->next is being funny.
                    LOW(prim->next->u0) = FIX(-5);
                    LOW(prim->next->r1) = 0;
                    prim->next->x1 = 0x80;
                    prim->next->y0 = 0;
                    prim->priority = 0xC0;
                    prim->drawMode = DRAW_UNK_40 | DRAW_TPAGE2 | DRAW_TPAGE |
                                     DRAW_UNK02 | DRAW_TRANSP;
                    prim = prim->next;
                    prim->drawMode &= ~DRAW_UNK02;
                    prim = prim->next;
                }
            }
        }
        g_api.PlaySfx(SFX_BOSS_DEFEATED);
        break;
    case 1:
        if (!self->ext.lifeUpSpawn.unk86) {
            self->ext.lifeUpSpawn.unk86 = 2;
            self->ext.lifeUpSpawn.unk88++;
        }
        self->ext.lifeUpSpawn.unk86--;
        if (self->ext.lifeUpSpawn.unk88 > 7) {
            self->ext.lifeUpSpawn.unk88 = 7;
            self->step++;
        }
        /* fallthrough */
    case 2:
        SetGeomScreen(0x200);
        SetGeomOffset(self->posX.i.hi, self->posY.i.hi);
        count_low_x1 = 0;
        prim = self->ext.lifeUpSpawn.prim1;
        for (j = 0; j < (self->ext.lifeUpSpawn.unk88 + 1); j++) {
            XY_var = prim->next->y1 + (prim->next->x1 << 0x10);
            XY_var += LOW(prim->next->u0);
            prim->next->y1 = (u16)XY_var;
            XY_var = prim->next->x1 = XY_var >> 0x10;
            if (LOW(prim->next->u0) < FIX(-0.25)) {
                LOW(prim->next->u0) += FIX(3.5 / 16);
            }
            if (prim->next->x1 < 8) {
                count_low_x1++;
                self->ext.lifeUpSpawn.unk84 += 4;
                for (i = 0; i < 48; i++, prim++) {
                    prim->drawMode = DRAW_HIDE;
                }
            } else {
                for (k = 0; k < 24; k++) {
                    Point16 clipPos;
                    s16 clipZ;
                    SVECTOR rotation;
                    VECTOR tempVec;
                    MATRIX matrix;
                    SVECTOR vertex;

                    rotation.vx = prim->next->x3;
                    rotation.vy = prim->next->y3;
                    rotation.vz = LOH(prim->next->tpage);
                    RotMatrix(&rotation, &matrix);

                    tempVec.vx = FLT(0);
                    tempVec.vy = FLT(0);
                    tempVec.vz = FLT(0.125);
                    TransMatrix(&matrix, &tempVec);

                    SetRotMatrix(&matrix);
                    SetTransMatrix(&matrix);

                    vertex.vx = XY_var;
                    vertex.vy = 0;
                    vertex.vz = 0;
                    clipZ = RotTransPers(&vertex, (long*)&clipPos, &p, &flag);

                    RotMatrix(&clearRotation, &matrix);

                    tempVec.vx = clipPos.x - self->posX.i.hi;
                    tempVec.vy = clipPos.y - self->posY.i.hi;
                    tempVec.vz = clipZ * 4;
                    TransMatrix(&matrix, &tempVec);

                    tempVec.vx = prim->next->x2;
                    tempVec.vy = prim->next->y2;
                    tempVec.vz = FLT(1);
                    ScaleMatrix(&matrix, &tempVec);

                    SetRotMatrix(&matrix);
                    SetTransMatrix(&matrix);

                    RotTransPers4(
                        &v0, &v1, &v2, &v3, (long*)&prim->x0, (long*)&prim->x1,
                        (long*)&prim->x2, (long*)&prim->x3, &p, &flag);

                    prim->next->x2 = prim->next->y2 -= 0x10;
                    LOH(prim->next->tpage) += 8;
                    prim->next->x3 += 0x10;
                    prim->next->y3 += 0x20;
                    // Note that we go to next here, but also in the for-loop,
                    // so it goes twice each loop
                    prim = prim->next;
                    prim = prim->next;
                }
            }
        }
        if (count_low_x1 == 8) {
            self->step++;
        }
        prim = self->ext.lifeUpSpawn.prim2;
        XY_var = self->posX.i.hi;
        p = self->ext.lifeUpSpawn.unk84;
        if (p > 0x100) {
            p = 0xE0;
        }

        prim->x0 = prim->x2 = XY_var - p;
        prim->x1 = prim->x3 = XY_var + p;
        XY_var = self->posY.i.hi;
        prim->y0 = prim->y1 = XY_var - p;
        prim->y2 = prim->y3 = XY_var + p;
        break;

    case 4:
        MoveEntity();
        self->velocityY += FIX(1.0 / 8);
        xVar = self->posX.i.hi;
        yVar = self->posY.i.hi + 4;
        g_api.CheckCollision(xVar, yVar, &collider, 0);
        if (collider.effects & EFFECT_SOLID) {
            self->velocityY = 0;
            self->posY.i.hi += collider.unk18;
            if (!--self->ext.lifeUpSpawn.unk84) {
                self->step = 5;
                break;
            }
        }
        /* fallthrough */
    case 3:
        if (self->ext.lifeUpSpawn.unk84 > 0) {
            self->ext.lifeUpSpawn.unk84 -= 0x20;
        } else {
            self->ext.lifeUpSpawn.unk84 = 0x10;
            self->step = 5;
        }
        prim = self->ext.lifeUpSpawn.prim2;
        XY_var = self->posX.i.hi;
        p = self->ext.lifeUpSpawn.unk84;
        if (p > 0xE0) {
            p = 0xE0;
        }
        prim->x0 = prim->x2 = XY_var - p;
        prim->x1 = prim->x3 = XY_var + p;
        XY_var = self->posY.i.hi;
        prim->y0 = prim->y1 = XY_var - p;
        prim->y2 = prim->y3 = XY_var + p;
        break;

    case 5:
        g_api.FreePrimitives(self->primIndex);
        self->posY.i.hi -= 4;
        self->step++;
        /* fallthrough */
    case 6:
        if (self->params > 0x10) {
            if (g_PlayableCharacter != PLAYER_ALUCARD) {
                self->params = 0x17;
                params = self->params & 0xFFF;
                if (params < 0x80) {
                    self->entityId = E_PRIZE_DROP;
                    self->pfnUpdate = EntityPrizeDrop;
                    self->poseTimer = 0;
                    self->pose = 0;
                } else {
                    self->entityId = E_EQUIP_ITEM_DROP;
                    self->pfnUpdate = EntityEquipItemDrop;
                    params -= 0x80;
                }
                self->params = params;
                self->unk6D[0] = 0x10;
                self->params |= 0x8000;
                self->step = 0;
            } else {
                self->entityId = E_RELIC_ORB;
                self->pfnUpdate = EntityRelicOrb;
                self->poseTimer = 0;
                self->pose = 0;
                self->unk6D[0] = 0x10;
                self->params = D_80182850[self->params];
                self->step = 0;
            }
        } else {
            self->params = D_80182850[self->params];
            params = self->params & 0xFFF;
            if (params < 0x80) {
                self->entityId = E_PRIZE_DROP;
                self->pfnUpdate = EntityPrizeDrop;
                self->poseTimer = 0;
                self->pose = 0;
            } else {
                self->entityId = E_EQUIP_ITEM_DROP;
                self->pfnUpdate = EntityEquipItemDrop;
                params -= 0x80;
            }
            self->params = params;
            self->unk6D[0] = 0x10;
            self->params |= 0x8000;
            self->step = 0;
        }
        break;
    }
}
