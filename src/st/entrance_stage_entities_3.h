// SPDX-License-Identifier: AGPL-3.0-or-later
static s32 g_TrapDoorFlag = 0; // 0 = Closed, 1 = Open

static u8 trapdoor_anim[] = {
    1,   27, 6,   28, 6,   29, 129, 30, 255, 0, 0,   0,
    108, 2,  115, 2,  122, 2,  109, 2,  116, 2, 123, 2};

// trap door that leads to underground garden in saturn version.
// also opens the one leading to the save room
void EntityTrapDoor(Entity* entity) {
    switch (entity->step) {
    case 0:
        InitializeEntity(g_EInitStInteractable);
        entity->animCurFrame = 27;
        entity->zPriority = 0x6A;
        entity->hitboxWidth = 16;
        entity->hitboxHeight = 4;
        entity->hitboxState = 1;

        if (g_TrapDoorFlag == 0) {
            if (PLAYER.posY.val < entity->posY.val) {
                g_Tilemap.fg[0xA8E / 2] = 0x129;
                g_Tilemap.fg[0xA90 / 2] = 0x132;
                DestroyEntity(entity);
                break;
            }
            g_Tilemap.fg[0xA8E / 2] = 0x6C8;
            g_Tilemap.fg[0xA90 / 2] = 0x6C9;
        } else {
            entity->animCurFrame = 30;
            g_Tilemap.fg[0xA8E / 2] = 0x6C8;
            g_Tilemap.fg[0xA90 / 2] = 0x6C9;
            entity->step = 128;
        }

    case 1:
        if (entity->hitFlags != 0) {
            g_TrapDoorFlag = 1;
            entity->step++;
        }
        break;

    case 2:
        AnimateEntity(trapdoor_anim, entity);
        break;
    }
}

static u16 leftRockTiles[][6] = {
    {0x06B2, 0x0000, 0x06C5, 0x06B3, 0x06D9, 0x06DA},
    {0x06B2, 0x0000, 0x06C5, 0x06B3, 0x06B4, 0x06B5},
    {0x0332, 0x033A, 0x0351, 0x0000, 0x0000, 0x0000}};

static u16 leftRockInitTiles[][6] = {
    {0x0332, 0x033A, 0x0351, 0x0350, 0x032F, 0x034E},
    {0x02A7, 0x0287, 0x02B4, 0x02A8, 0x02AE, 0x02B5}};
static u16 rightRockTiles[][6] = {
    {0x06DB, 0x06DC, 0x06DD, 0x06B7, 0x0000, 0x06C6},
    {0x06B6, 0x06B8, 0x06B9, 0x06B7, 0x0000, 0x06C6},
    {0x0000, 0x0000, 0x0000, 0x0350, 0x032F, 0x034E}};
// Accesses and offsets are weird, so I'm just making this a big chunk of data.
// This feels like 3 arrays, but if I split them up, they get zero-padded to
// align 4.
static u16 remainingRockTiles[] = {
    0x0332, 0x033A, 0x0351, 0x0350, 0x032F, 0x034E, 0x02D2, 0x02D2, 0x02D2,
    0x02D2, 0x02D2, 0x02D2, 0x02D2, 0x02D2, 0x02D2, 0x02D2, 0x02D6, 0x02D4,
    0x02D6, 0x02D8, 0x02D7,
    // Offset 21 gets used later
    0x06BA, 0x0000, 0x0000, 0x06BD, 0x06BF, 0x06BB, 0x0000, 0x0000, 0x06BE,
    0x06C0, 0x06BC, 0x0000, 0x0000, 0x06BD, 0x06C1, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0350, 0x0000,
    0x034E, 0x0339, 0x0000,
    // Offset 51 is here.
    0x034E, 0x0339, 0x0350, 0x032F, 0x0000, 0x034F, 0x033A, 0x0351, 0x0330,
    0x0000, 0x0350, 0x032F, 0x034E, 0x0339, 0x0000};
static u16 rockYOffsets[] = {12, 6, 7, 0};

static u8 newRockParams[] = {1, 2, 1, 2, 1};

// left side of the breakable rock, drops pot roast
void EntityMermanRockLeftSide(Entity* self) {
    const int rockBroken = (1 << 0);
    const int wolfFlag = (1 << 2);
    u16* tileLayoutPtr;
    Entity* newEntity;
    s32 tilePos;
    u8* params;
    s32 i;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitInteractable);
        self->hitboxState = 2;
        self->hitboxWidth = 16;
        self->hitboxHeight = 24;

        tileLayoutPtr = &leftRockInitTiles;
        tilePos = 0x1F1;
        for (i = 0; i < 3; i++) {
            g_BgLayers[0].layout[tilePos] = *tileLayoutPtr;
            g_BgLayers[0].layout[tilePos + 1] = *(tileLayoutPtr + 3);
            tileLayoutPtr++;
            tilePos += 0x30;
        }

        if (g_CastleFlags[JEWEL_SWORD_ROOM_STEPS] & rockBroken) {
            tileLayoutPtr = &leftRockTiles[1];
            tilePos = 0x1F1;
            for (i = 0; i < 3; i++) {
                g_Tilemap.fg[tilePos] = *tileLayoutPtr;
                g_Tilemap.fg[tilePos + 1] = *(tileLayoutPtr + 3);
                tileLayoutPtr++;
                tilePos += 0x30;
            }
            self->hitboxState = 1;
            self->step = 2;
        }
        break;

    case 1:
        if (self->hitFlags != 0) {
            tileLayoutPtr = &leftRockTiles[self->ext.mermanRock.unk84];
            tilePos = 0x1F1;
            for (i = 0; i < 3; i++) {
                g_Tilemap.fg[tilePos] = *tileLayoutPtr;
                g_Tilemap.fg[tilePos + 1] = *(tileLayoutPtr + 3);
                tileLayoutPtr++;
                tilePos += 0x30;
            }

            g_api.PlaySfx(SFX_WALL_DEBRIS_B);

            newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (newEntity != NULL) {
                CreateEntityFromEntity(E_EXPLOSION, self, newEntity);
                newEntity->params = 0x13;
                newEntity->zPriority = 0xA9;
                newEntity->posX.i.hi += self->ext.mermanRock.unk84 * 16;
                newEntity->posY.i.hi += 16;
            }

            params = &newRockParams[self->ext.mermanRock.unk84 * 3];

            for (i = 0; i < 3; i++) {
                newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
                if (newEntity != NULL) {
                    CreateEntityFromEntity(E_FALLING_ROCK_2, self, newEntity);
                    newEntity->params = *params++;
                    newEntity->velocityX = -0x8000 - (Random() << 8);
                    newEntity->velocityY = -Random() * 0x100;
                    newEntity->posY.i.hi += -16 + (i * 16);
                }
            }
            self->ext.mermanRock.unk84++;
        }

        if (self->ext.mermanRock.unk84 >= 2) {
            newEntity = AllocEntity(g_Entities + 160, g_Entities + 192);
            if (newEntity != NULL) {
                CreateEntityFromEntity(E_EQUIP_ITEM_DROP, self, newEntity);
                newEntity->params = ITEM_POT_ROAST;
            }
            g_CastleFlags[JEWEL_SWORD_ROOM_STEPS] |= rockBroken;
            self->hitboxState = 1;
            self->step++;
        }
        break;

    case 2:
        if ((self->hitFlags != 0) &&
            (g_Player.status & PLAYER_STATUS_WOLF_FORM)) {
            g_CastleFlags[JEWEL_SWORD_ROOM_STEPS] |= wolfFlag;
        }
        break;
    }
}

// right side of the merman room rock, breaks when hit
void EntityMermanRockRightSide(Entity* self) {
    const int rockBroken = (1 << 1);
    const int batFlag = (1 << 3);
    u16* tileLayoutPtr;
    Entity* newEntity;
    s32 tilePos;
    u8* params;
    s32 i;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitInteractable);
        self->hitboxState = 2;
        self->hitboxWidth = 16;
        self->hitboxHeight = 24;

        tileLayoutPtr = &remainingRockTiles[0];
        tilePos = 0x1FD;
        for (i = 0; i < 3; i++) {
            g_BgLayers[0].layout[tilePos] = *tileLayoutPtr;
            g_BgLayers[0].layout[tilePos + 1] = *(tileLayoutPtr + 3);
            tileLayoutPtr++;
            tilePos += 0x30;
        }

        if (g_CastleFlags[JEWEL_SWORD_ROOM_STEPS] & rockBroken) {
            tileLayoutPtr = &rightRockTiles[1];
            tilePos = 0x1FD;
            for (i = 0; i < 3; i++) {
                g_Tilemap.fg[tilePos] = *tileLayoutPtr;
                g_Tilemap.fg[tilePos + 1] = *(tileLayoutPtr + 3);
                tileLayoutPtr++;
                tilePos += 0x30;
            }
            self->hitboxState = 1;
            self->step = 2;
        }
        break;

    case 1:
        if (self->hitFlags != 0) {
            tileLayoutPtr = &rightRockTiles[self->ext.mermanRock.unk84];
            tilePos = 0x1FD;
            for (i = 0; i < 3; i++) {
                g_Tilemap.fg[tilePos] = *tileLayoutPtr;
                g_Tilemap.fg[tilePos + 1] = *(tileLayoutPtr + 3);
                tileLayoutPtr++;
                tilePos += 0x30;
            }

            g_api.PlaySfx(SFX_WALL_DEBRIS_B);

            newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (newEntity != NULL) {
                CreateEntityFromEntity(E_EXPLOSION, self, newEntity);
                newEntity->params = 0x13;
                newEntity->zPriority = 0xA9;
                newEntity->posX.i.hi -= self->ext.mermanRock.unk84 * 16;
                newEntity->posY.i.hi += 16;
            }

            params = &newRockParams[self->ext.mermanRock.unk84 * 3];

            for (i = 0; i < 3; i++) {
                newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
                if (newEntity != NULL) {
                    CreateEntityFromEntity(E_FALLING_ROCK_2, self, newEntity);
                    newEntity->params = *params++;
                    newEntity->velocityX = (Random() << 8) + 0x8000;
                    newEntity->velocityY = -Random() * 0x100;
                    newEntity->facingLeft = 1;
                    newEntity->posY.i.hi += -16 + (i * 16);
                }
            }
            self->ext.mermanRock.unk84++;
        }

        if (self->ext.mermanRock.unk84 >= 2) {
            g_CastleFlags[JEWEL_SWORD_ROOM_STEPS] |= rockBroken;
            self->hitboxState = 1;
            self->step++;
        }
        break;

    case 2:
        if ((self->hitFlags != 0) &&
            (g_Player.status & PLAYER_STATUS_BAT_FORM)) {
            g_CastleFlags[JEWEL_SWORD_ROOM_STEPS] |= batFlag;
        }
        break;
    }
}

void EntityJewelSwordDoor(Entity* self) {
    u16* tileLayoutPtr;
    s32 tileLayoutPos;
    s32 i;
    s32 j;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitInteractable);
        if (g_CastleFlags[JEWEL_SWORD_ROOM_OPEN] != 0) {
            self->step = 2;
        }
        break;

    case 1:
        if ((g_CastleFlags[JEWEL_SWORD_ROOM_STEPS] & 12) == 12) {
            PlaySfxPositional(SFX_WALL_DEBRIS_B);
            self->step++;
        }
        break;

    case 2:
        for (tileLayoutPtr = &remainingRockTiles[21], i = 0; i < 3; i++) {
            tileLayoutPos = 0x420 + i;
            for (j = 0; j < 5; tileLayoutPos += 0x30, j++, tileLayoutPtr++) {
                g_Tilemap.fg[tileLayoutPos] = *tileLayoutPtr;
            }
        }

        for (tileLayoutPtr = &remainingRockTiles[51], i = 0; i < 3; i++) {
            tileLayoutPos = 0x420 + i;
            for (j = 0; j < 5; j++, tileLayoutPtr++) {
                g_BgLayers[0].layout[tileLayoutPos] = *tileLayoutPtr;
                tileLayoutPos += 0x30;
            }
        }

        g_CastleFlags[JEWEL_SWORD_ROOM_OPEN] |= 1;
        g_api.RevealSecretPassageAtPlayerPositionOnMap(JEWEL_SWORD_ROOM_OPEN);
        self->step++;
        break;
    }
}

// falling rock that breaks into dust
void EntityFallingRock2(Entity* self) {
    s32 animFrame = self->params & 0xF;
    Collider collider;
    Entity* newEntity;
    s32 collX;
    s32 collY;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitStInteractable);
        self->animCurFrame = animFrame + 31;
        self->drawFlags |= FLAG_DRAW_ROTZ;
        self->zPriority = 0x9F;
        break;

    case 1:
        MoveEntity();
        self->velocityY += FIX(0.25);
        self->rotZ -= 0x20;
        collX = self->posX.i.hi;
        collY = self->posY.i.hi;
        collY += rockYOffsets[animFrame];
        g_api.CheckCollision(collX, collY, &collider, 0);

        if (collider.effects & EFFECT_SOLID) {
            if (self->velocityY > FIX(4.0)) {
                newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
                if (newEntity != 0) {
                    CreateEntityFromEntity(E_EXPLOSION, self, newEntity);
                    newEntity->params = 0x11;
                    if (animFrame == 0) {
                        newEntity->params = 0x13;
                    }
                }
                DestroyEntity(self);
                return;
            }
            self->posY.i.hi += collider.unk18;
            // Seems to be a bounce effect. Reverse velocity, and lose 1/8 of
            // it.
            self->velocityY = -self->velocityY;
            self->velocityY -= self->velocityY / 8;
        }
        break;
    }
}
