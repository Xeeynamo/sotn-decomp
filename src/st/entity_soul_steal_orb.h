// SPDX-License-Identifier: AGPL-3.0-or-later
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
        D_psp_091CF3A8 = &func_psp_0923B2F0;
        func_psp_0923AD68(self);
        return;
    }
#endif

    player = &PLAYER;
    switch (self->step) {
    case 0:
        primIndex = g_api.AllocPrimBuffers(PRIM_GT4, 1);
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
        if (self->rotX < 0x100) {
            self->rotX = self->rotY += 0x10;
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
        prim->clut = 0x194;
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
