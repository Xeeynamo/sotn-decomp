// SPDX-License-Identifier: AGPL-3.0-or-later
typedef enum { WEIGHT_SMALL, WEIGHT_TALL } WeightSelect;

// To the right of Cube of Zoe is the weight system.
// The two weights hang from chains. The chains are prims
// that are 32 px in height. This function places them
// all at the right locations to stack up above the weight.
static void UpdateWeightChains(WeightSelect weight) {
    s32 posX = g_CurrentEntity->posX.i.hi;
    s32 posY = g_CurrentEntity->posY.i.hi;
    Primitive* prim;

    if (weight != WEIGHT_SMALL) {
        posY -= 64;
    } else {
        posY -= 16;
    }

    for (prim = g_CurrentEntity->ext.prim; posY > 0; prim = prim->next) {
        prim->x0 = prim->x2 = posX - 8;
        prim->x1 = prim->x3 = posX + 8;
        prim->y2 = prim->y3 = posY;
        posY -= 32;
        prim->y0 = prim->y1 = posY;
        prim->drawMode = DRAW_UNK02;
    }

    for (; prim != NULL; prim = prim->next) {
        prim->drawMode = DRAW_HIDE;
    }
}

// switch to lower the weights to the right of Cube of Zoe
void EntityWeightsSwitch(Entity* self) {
    s32 collision = GetPlayerCollisionWith(self, 8, 4, 4);
    s32 worldPos;
    Entity* player;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitStInteractable);
        self->animCurFrame = 9;
        self->zPriority = 0x5E;
        if (g_CastleFlags[NO0_TO_NP3_SHORTCUT]) {
            self->posY.i.hi += 4;
            self->step = 2;
        }
        break;

    case 1:
        if (collision) {
            player = &PLAYER;
            player->posY.i.hi++;
            self->posY.val += FIX(0.75);
            worldPos = g_Tilemap.scrollY.i.hi + self->posY.i.hi;
            if (worldPos > 160) {
                self->posY.i.hi = 160 - g_Tilemap.scrollY.i.hi;
                g_api.PlaySfx(SFX_SWITCH_CLICK);
                g_CastleFlags[NO0_TO_NP3_SHORTCUT] = 1;
                self->step++;
            }
        }
        break;
    }
}

// smaller weight blocking path near cube of zoe
void EntityPathBlockSmallWeight(Entity* self) {
    s32 worldPos;
    s32 collision;
    s32 primIndex;
    Primitive* prim;
    s32 var_a1;
    s32 i;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitStInteractable);
        self->animCurFrame = 8;
        self->zPriority = 0x5E;
        // All the prims below here are for the chain.
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 8);
        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags |= FLAG_HAS_PRIMS;
        self->primIndex = primIndex;
        prim = &g_PrimBuf[primIndex];
        self->ext.prim = prim;

        while (prim != NULL) {
            prim->tpage = 0xF;
            prim->clut = 0x22;
            prim->u0 = prim->u2 = 0xE0;
            prim->u1 = prim->u3 = 0xE0 + 0x10;
            prim->v0 = prim->v1 = 0x54;
            prim->v2 = prim->v3 = 0x54 + 0x20;
            prim->priority = self->zPriority + 1;
            prim->drawMode = DRAW_HIDE;
            prim = prim->next;
        }
#if !defined(STAGE_IS_NO3)
        self->posX.i.hi = 416 - g_Tilemap.scrollX.i.hi;
        self->posY.i.hi = 64 - g_Tilemap.scrollY.i.hi;
#endif
        if (g_CastleFlags[NO0_TO_NP3_SHORTCUT]) {
            self->posY.i.hi += 111;
            self->step = 3;
        }
        break;

    case 1:
        if (g_CastleFlags[NO0_TO_NP3_SHORTCUT]) {
            self->step++;
        }
        break;

    case 2:
        self->posY.val += FIX(0.5);
        worldPos = self->posY.i.hi + g_Tilemap.scrollY.i.hi;
        if (worldPos >= 175) {
#if !defined(STAGE_IS_NO3)
            PlaySfxPositional(SFX_START_SLAM_B);
#endif
            self->posY.i.hi = 175 - g_Tilemap.scrollY.i.hi;
            self->step++;
        }
        break;

    case 3:
        for (var_a1 = 0x179, i = 0; i < 2; var_a1 -= 0x20, i++) {
            g_Tilemap.fg[var_a1] = 0x4FA;
            *(&g_Tilemap.fg[var_a1] + 1) = 0x4FA;
        }
        self->step++;
        break;
    }

    if (self->step < 3) {
        collision = GetPlayerCollisionWith(self, 16, 16, 5);
        if (collision & 4) {
            Entity* player = &PLAYER;

            player->posY.i.hi++;
        }
    }
    UpdateWeightChains(WEIGHT_SMALL);
}

// taller weight blocking path near cube of zoe
void EntityPathBlockTallWeight(Entity* self) {
    Primitive* prim;
    s32 primIndex;
    s32 steps_covered;
    s32 tilemap_idx;
    s32 yPos;
    s32 i;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitStInteractable);
        self->animCurFrame = 7;
        self->zPriority = 0x5E;

        // All the prims below here are for the chain.
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 8);
        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags |= FLAG_HAS_PRIMS;
        self->primIndex = primIndex;
        prim = &g_PrimBuf[primIndex];
        self->ext.prim = prim;

        while (prim != NULL) {
            prim->tpage = 0xF;
            prim->clut = 0x22;
            prim->u0 = prim->u2 = 0xE0;
            prim->u1 = prim->u3 = 0xE0 + 0x10;
            prim->v0 = prim->v1 = 0x54;
            prim->v2 = prim->v3 = 0x54 + 0x20;
            prim->priority = self->zPriority + 1;
            prim->drawMode = DRAW_HIDE;
            prim = prim->next;
        }

        if (g_CastleFlags[NO0_TO_NP3_SHORTCUT]) {
            self->posY.i.hi -= 128;
            self->step = 3;
        }
        break;

    case 1:
        if (g_CastleFlags[NO0_TO_NP3_SHORTCUT]) {
            self->step++;
        }
        break;

    case 2:
        self->posY.val -= FIX(0.5);
        yPos = self->posY.i.hi + g_Tilemap.scrollY.i.hi;
        if (yPos <= -16) {
            self->posY.i.hi = -16 - g_Tilemap.scrollY.i.hi;
            self->step++;
        }
        break;
    }

    UpdateWeightChains(WEIGHT_TALL);
    yPos = self->posY.i.hi + g_Tilemap.scrollY.i.hi;
    yPos = 112 - yPos;
    steps_covered = yPos / 16;

    for (tilemap_idx = 0x20 * 10 + 0x17, i = 0; i < steps_covered;
         tilemap_idx -= 0x20, i++) {
        g_Tilemap.fg[tilemap_idx] = 0;
        // This should be g_Tilemap.fg[tilemap_idx + 1] but psp fails
        *(&g_Tilemap.fg[tilemap_idx] + 1) = 0;
    }

    for (steps_covered = 8 - steps_covered, i = 0; i < steps_covered;
         tilemap_idx -= 0x20, i++) {
        g_Tilemap.fg[tilemap_idx] = 0x4FA;
        *(&g_Tilemap.fg[tilemap_idx] + 1) = 0x4FA;
    }
}
