#include "../no3/no3.h"

#ifdef VERSION_PSP
extern s32 E_ID(FALLING_ROCK_2);
#endif

#ifdef VERSION_PSP
#define EXTRA_TILES 6
static u16 mermanRockTiles[] = {
    0x026C, 0x0273, 0x027A, 0x026D, 0x0274, 0x027B,
#else
#define EXTRA_TILES 0
static u16 mermanRockTiles[] = {
#endif
    0x06B2, 0x0000, 0x06C5, 0x06B3, 0x06D9, 0x06DA,
    0x06B2, 0x0000, 0x06C5, 0x06B3, 0x06B4, 0x06B5, 0, 0,
    0x0332, 0x033A, 0x0351, 0x0000, 0x0000, 0x0000,
    // Initial tiles. On PSP, starts at 5E664. PSP symbols are 8-aligned,
    // so this must not be its own variable.
    0x0332, 0x033A, 0x0351, 0x0350, 0x032F, 0x034E,
};
static u16 mermanRockTiles2[] = {
    0x02A7, 0x0287, 0x02B4, 0x02A8, 0x02AE, 0x02B5,
    // Same deal, starts at 5E67C
    0x06DB, 0x06DC, 0x06DD, 0x06B7, 0x0000, 0x06C6,
    0x06B6, 0x06B8, 0x06B9, 0x06B7, 0x0000, 0x06C6, 0, 0,
    0x0000, 0x0000, 0x0000, 0x0350, 0x032F, 0x034E,
    // Even more, what a sad day
    0x0332, 0x033A, 0x0351, 0x0350, 0x032F, 0x034E, 0x02D2, 0x02D2, 0x02D2,
    0x02D2, 0x02D2, 0x02D2, 0x02D2, 0x02D2, 0x02D2, 0x02D2, 0x02D6, 0x02D4,
    0x02D6, 0x02D8, 0x02D7,
    // Offset 21 gets used later
    0x06BA, 0x0000, 0x0000, 0x06BD, 0x06BF, 0x06BB, 0x0000, 0x0000, 0x06BE,
    0x06C0, 0x06BC, 0x0000, 0x0000, 0x06BD, 0x06C1, 0x0000, 0x0000, 0x0000, 0, 0,
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

        tileLayoutPtr = &mermanRockTiles[26];
        tilePos = 0x1F1;
        for (i = 0; i < 3; i++, tileLayoutPtr++) {
            g_BgLayers[0].layout[tilePos] = *tileLayoutPtr;
            *(&g_BgLayers[0].layout[tilePos] + 1) = *(tileLayoutPtr + 3);
            tilePos += 0x30;
        }

        if (g_CastleFlags[JEWEL_SWORD_ROOM_STEPS] & rockBroken) {
            tilePos = 0x1F1;
            tileLayoutPtr = &mermanRockTiles[6 + EXTRA_TILES];
            for (i = 0; i < 3; i++, tileLayoutPtr++) {
                g_Tilemap.fg[tilePos] = *tileLayoutPtr;
                *(&g_Tilemap.fg[tilePos] + 1) = *(tileLayoutPtr + 3);
                tilePos += 0x30;
            }
            self->hitboxState = 1;
            self->step = 2;
        }
        break;

    case 1:
        if (self->hitFlags) {
            tileLayoutPtr = &(mermanRockTiles[self->ext.mermanRock.unk84 * 6]) + EXTRA_TILES;
            tilePos = 0x1F1;
            for (i = 0; i < 3; i++, tileLayoutPtr++) {
                g_Tilemap.fg[tilePos] = *tileLayoutPtr;
                *(&g_Tilemap.fg[tilePos] + 1) = *(tileLayoutPtr + 3);
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
                    CreateEntityFromEntity(E_ID(FALLING_ROCK_2), self, newEntity);
                    newEntity->params = *params++;
                    newEntity->velocityX = (-Random() << 8) -0x8000;
                    newEntity->velocityY = -Random() * 0x100;
                    newEntity->posY.i.hi += -16 + (i * 16);
                }
            }
            self->ext.mermanRock.unk84++;
        }

        if (self->ext.mermanRock.unk84 > 1) {
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
        if ((self->hitFlags) &&
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

        tileLayoutPtr = &mermanRockTiles[58];
        tilePos = 0x1FD;
        for (i = 0; i < 3; i++, tileLayoutPtr++) {
            g_BgLayers[0].layout[tilePos] = *tileLayoutPtr;
            *(&g_BgLayers[0].layout[tilePos] + 1) = *(tileLayoutPtr + 3);
            tilePos += 0x30;
        }

        if (g_CastleFlags[JEWEL_SWORD_ROOM_STEPS] & rockBroken) {
            tilePos = 0x1FD;
            tileLayoutPtr = &mermanRockTiles[44];
            for (i = 0; i < 3; i++, tileLayoutPtr++) {
                g_Tilemap.fg[tilePos] = *tileLayoutPtr;
                *(&g_Tilemap.fg[tilePos] + 1) = *(tileLayoutPtr + 3);
                tilePos += 0x30;
            }
            self->hitboxState = 1;
            self->step = 2;
        }
        break;

    case 1:
        if (self->hitFlags) {
            tileLayoutPtr = &mermanRockTiles2[self->ext.mermanRock.unk84 * 6] + 6;
            tilePos = 0x1FD;
            for (i = 0; i < 3; i++, tileLayoutPtr++) {
                g_Tilemap.fg[tilePos] = *tileLayoutPtr;
                *(&g_Tilemap.fg[tilePos] + 1) = *(tileLayoutPtr + 3);
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
                    CreateEntityFromEntity(E_ID(FALLING_ROCK_2), self, newEntity);
                    newEntity->params = *params++;
                    newEntity->velocityX = (Random() << 8) + 0x8000;
                    newEntity->velocityY = -Random() * 0x100;
                    newEntity->posY.i.hi += -16 + (i * 16);
                    newEntity->facingLeft = 1;
                }
            }
            self->ext.mermanRock.unk84++;
        }

        if (self->ext.mermanRock.unk84 > 1) {
            g_CastleFlags[JEWEL_SWORD_ROOM_STEPS] |= rockBroken;
            self->hitboxState = 1;
            self->step++;
        }
        break;

    case 2:
        if ((self->hitFlags) &&
            (g_Player.status & PLAYER_STATUS_BAT_FORM)) {
            g_CastleFlags[JEWEL_SWORD_ROOM_STEPS] |= batFlag;
        }
        break;
    }
}

void EntityJewelSwordDoor(Entity* self) {
    u16* tileLayoutPtr;
    s32 i;
    s32 j;
    s32 tileLayoutPos;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitInteractable);
        if (g_CastleFlags[JEWEL_SWORD_ROOM_OPEN]) {
            self->step = 2;
        }
        break;

    case 1:
        if ((g_CastleFlags[JEWEL_SWORD_ROOM_STEPS] & 4) && 
            (g_CastleFlags[JEWEL_SWORD_ROOM_STEPS] & 8)) {
            PlaySfxPositional(SFX_WALL_DEBRIS_B);
            self->step++;
        }
        break;

    case 2:
        for (tileLayoutPtr = &mermanRockTiles2[47], i = 0; i < 3; i++) {
            tileLayoutPos = 0x420 + i;
            for (j = 0; j < 5; tileLayoutPos += 0x30, j++, tileLayoutPtr++) {
                g_Tilemap.fg[tileLayoutPos] = *tileLayoutPtr;
            }
        }

        for (tileLayoutPtr = &mermanRockTiles2[79], i = 0; i < 3; i++) {
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