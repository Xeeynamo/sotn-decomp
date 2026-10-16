// SPDX-License-Identifier: AGPL-3.0-or-later
#include "no4.h"

#ifdef VERSION_PSP
extern s32 E_ID(SKELETON_APE);
extern s32 E_ID(SKELETON_APE_BARREL);
extern s32 E_ID(ID_5C);
extern s32 E_ID(ID_54);
extern s32 E_ID(ID_27);
extern s32 E_ID(ID_26);
#endif

#ifdef VERSION_PSP
void* func_pspeu_0923D4A0(
    s32 idx, void* en, void* fr, void* sp, void* ge, void* it) {
    switch (g_UserLanguage) {
    default:
    case LANG_EN:
        return (void*)((u32)en + idx);
    case LANG_FR:
        return (void*)((u32)fr + idx);
    case LANG_SP:
        return (void*)((u32)sp + idx);
    case LANG_GE:
        return (void*)((u32)ge + idx);
    case LANG_IT:
        return (void*)((u32)it + idx);
    }
}
#endif

static bool D_us_80181108 = false;

#include "../cavern_bg_effects.h"

// Water flow animation that needs to be blocked by the crate
static u8 D_us_80181588[] = {1, 7, 1, 8, 1, 9, 0, 0};

/**
 * Does something with the water level that kills the 4 spear guards in the
 * alcove
 */
void EntityWaterSpray(Entity* self) {
    Entity* newEnt;
    s16* var_s2;
    s16* var_s1;

    if (!self->step) {
        InitializeEntity(g_EInitInteractable);
        self->animSet = ANIMSET_OVL(1);
        self->palette = 0x44;
        self->drawFlags = ENTITY_MASK_R;
        self->posX.i.hi = 0x711 - g_Tilemap.scrollX.i.hi;
        if (g_CastleFlags[NO4_WATER_BLOCKED]) {
            self->ext.et_waterAlcove.waterHeight = 0x40;
        } else {
            newEnt = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (newEnt != NULL) {
                CreateEntityFromCurrentEntity(E_ID(ID_27), newEnt);
                newEnt->params = 1;
            }
            self->ext.et_waterAlcove.entity7E = newEnt;

            newEnt = AllocEntity(newEnt, &g_Entities[256]);
            if (newEnt != NULL) {
                CreateEntityFromCurrentEntity(E_ID(ID_26), newEnt);
                newEnt->params = 1;
            }
            self->ext.et_waterAlcove.entity82 = newEnt;
            self->ext.et_waterAlcove.waterHeight = 0;
        }
    }

    // Animates the small flow of water that needs to be blocked by the crate
    AnimateEntity(D_us_80181588, self);

    if (g_CastleFlags[NO4_WATER_BLOCKED]) {
        if (self->ext.et_waterAlcove.waterHeight < 0x40) {
            if (!(self->ext.et_waterAlcove.unk8E & 0x7)) {
                if (!self->ext.et_waterAlcove.waterHeight) {
                    g_api.PlaySfx(SFX_WATER_BUBBLE);
                }
                self->ext.et_waterAlcove.waterHeight++;
                if (self->ext.et_waterAlcove.waterHeight == 0x14) {
                    g_CastleFlags[NO4_WATER_BLOCKED]++;
                }
                if (self->ext.et_waterAlcove.waterHeight == 0x34) {
                    g_CastleFlags[NO4_WATER_BLOCKED]++;
                }
            }
            self->ext.et_waterAlcove.unk8E++;
        }

        if (self->ext.et_waterAlcove.entity7E) {
            DestroyEntity(self->ext.et_waterAlcove.entity7E);
            self->ext.et_waterAlcove.entity7E = NULL;
        }

        if (self->ext.et_waterAlcove.entity82) {
            DestroyEntity(self->ext.et_waterAlcove.entity82);
            self->ext.et_waterAlcove.entity82 = NULL;
        }
        self->animCurFrame = 0;
    }

    var_s2 = water_tile_rects;
    var_s1 = water_surface_lines;
    var_s2 += 0x36;
    var_s1 += 0x43;

    *var_s2 = 0xB1 - self->ext.et_waterAlcove.waterHeight;
    *var_s1 = 0xB0 - self->ext.et_waterAlcove.waterHeight;

    if (self->ext.et_waterAlcove.waterHeight >= 0x40) {
        DestroyEntity(self);
    }
}

static u16 D_us_80181590[] = {0x30, 0x0F, 0x28, 0x0F, 0x18, 0x0F};

void EntityFloatingIcePlatform(Entity* self) {
    u16* hitboxPtr;
    u16 collision;
    Entity* player;
    s16 prevPosY;
    s16 dx, dy;
    u16 hitboxIndex;

    player = &PLAYER;
    hitboxIndex = self->params;

    if (!self->step) {
        InitializeEntity(g_EInitCommon);
        self->animSet = ANIMSET_OVL(1);
        self->animCurFrame = hitboxIndex + 25;
        self->drawFlags = ENTITY_ROTATE;
        self->ext.et_801C4980.posY = self->posY.i.hi + g_Tilemap.scrollY.i.hi;
    }

    hitboxPtr = &D_us_80181590[hitboxIndex * 2];

    prevPosY = self->posY.i.hi;
    self->posY.i.hi = self->ext.et_801C4980.posY - g_Tilemap.scrollY.i.hi +
                      self->ext.et_801C4980.timer;
#ifdef VERSION_PSP
    collision = GetPlayerCollisionWith(self, hitboxPtr[0], hitboxPtr[1], 4);
#else
    collision = GetPlayerCollisionWith(self, *hitboxPtr++, *hitboxPtr, 4);
#endif
    self->posY.i.hi = prevPosY;
    self->ext.et_801C4980.prevTimer = self->ext.et_801C4980.timer;

    dx = self->posX.i.hi - player->posX.i.hi;

    if (collision) {
        if (self->ext.et_801C4980.timer < 4) {
            self->ext.et_801C4980.timer++;
        }
    } else {
        if (self->ext.et_801C4980.timer) {
            self->ext.et_801C4980.timer--;
        }
    }

    dy = self->ext.et_801C4980.timer;
    if (dx < 0) {
        prevPosY = (dx * dy * -0x100) / 56;
    } else {
        prevPosY = (dx * dy * 0x100) / 56;
    }

    self->posY.i.hi = (self->ext.et_801C4980.posY - g_Tilemap.scrollY.i.hi) +
                      (dy - prevPosY / 256);

    if (collision) {
        dy = dy - self->ext.et_801C4980.prevTimer;
        player->posY.i.hi += dy;
        g_unkGraphicsStruct.shoveX.i.hi += dy;
    }

    prevPosY = -prevPosY;
    if (collision || dy) {
        if (dx < 0) {
            self->rotate = ratan2(prevPosY, -0x3800);
            self->rotate = (self->rotate - 0x800) & 0xFFF;
            return;
        }
        self->rotate = ratan2(prevPosY, 0x3800);
    } else {
        self->rotate = 0;
    }
}

static s16 D_us_8018159C[] = {
    0, -2048, 77, -8, 0, -2048, 127, -8, 256, 2048, 77, 8, 256, 2048, 127, 8,
};

void func_us_801C4BD8(Entity* self) {
    Entity* player;
    s16* dataPtr;
    s32 volume;

    if (!self->step) {
        InitializeEntity(g_EInitInteractable);
        self->animSet = 0;
    }

    player = &PLAYER;
    dataPtr = &D_us_8018159C[self->params * 4];

    volume = player->posX.i.hi + g_Tilemap.scrollX.i.hi - *dataPtr++;
    volume = (volume * *dataPtr++) / 0x1000;
    volume += *dataPtr++;

    if (volume < 0) {
        volume = 0;
    } else if (volume > 0x7F) {
        volume = 0x7F;
    }

    if (!volume) {
        if (D_us_80181108) {
            D_us_80181108 = false;
            g_api.PlaySfx(SET_UNK_A6);
            return;
        }
    }
    if (D_us_80181108) {
        g_api.SetVolumeCommand22_23(volume, *dataPtr++);
        return;
    }

    g_api.PlaySfxVolPan(SFX_WATERFALL_LOOP, volume, *dataPtr++);
    D_us_80181108 = true;
}

void func_us_801C4D2C(Entity* self) {
    s16 minX, maxX;
    s16 x, y;
    u16 playerInRange;
    u16* tilePtr;
    Entity* newEntity;
    Tilemap* tilemap;
    Entity* player;
    u16 tile;

    if (!self->step) {
        InitializeEntity(g_EInitInteractable);
        self->animSet = 0;
    }

    player = &PLAYER;
    tilemap = &g_Tilemap;

    // Another P2 controller triangle secret ?
    if (g_pads[1].tapped & PAD_TRIANGLE) {
        g_api.PlaySfx(SFX_WOODEN_BRIDGE_EXPLODE);
    }

    playerInRange = false;
    if (!(g_Player.status &
          (PLAYER_STATUS_BAT_FORM | PLAYER_STATUS_MIST_FORM))) {
        y = player->posY.i.hi + tilemap->scrollY.i.hi;
        if (g_Player.status & PLAYER_STATUS_WOLF_FORM) {
            if (y > 0x97 && y < 0xAB) {
                playerInRange = true;
                minX = player->posX.i.hi + tilemap->scrollX.i.hi - 12;
                maxX = minX + 24;
            }
        } else {
            if (y > 0x97 && y < 0xC7) {
                playerInRange = true;
                minX = player->posX.i.hi + tilemap->scrollX.i.hi - 8;
                maxX = minX + 16;
            }
        }
    }

    if (!playerInRange) {
        return;
    }
    for (x = minX; x <= maxX; x += 8) {
        playerInRange = false;
        if ((x >= 0xA40 && x < 0xAE0) || (x >= 0xB80 && x < 0xBE0)) {
            playerInRange = true;
        }

        if (!playerInRange) {
            continue;
        }
        tilePtr = &tilemap->fg[x / 16] + 0x8F0;
        tile = *tilePtr;

        if (tile == 0x701 || tile == 0x705) {
            newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (newEntity) {
                CreateEntityFromCurrentEntity(E_ID(ID_54), newEntity);
                newEntity->posX.i.hi =
                    ((x & 0xFFF0) + 8) - tilemap->scrollX.i.hi;
                newEntity->posY.i.hi = 0xB2 - tilemap->scrollY.i.hi;
                if (player->posX.i.hi > newEntity->posX.i.hi) {
                    newEntity->params = 1;
                }
            }
            *tilePtr = 0xAC7;
        } else if (tile == 0x70C) {
            newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (newEntity) {
                CreateEntityFromCurrentEntity(E_ID(ID_54), newEntity);
                newEntity->posX.i.hi =
                    ((x & 0xFFF0) + 8) - tilemap->scrollX.i.hi;
                newEntity->posY.i.hi = 0xB2 - tilemap->scrollY.i.hi;
                if (player->posX.i.hi > newEntity->posX.i.hi) {
                    newEntity->params = 1;
                }
            }
            *tilePtr = 0x59D;
        }
    }
}

void func_us_801C5020(Entity* self) {
    if (!self->step) {
        InitializeEntity(g_EInitCommon);
        self->animSet = ANIMSET_OVL(1);
        self->animCurFrame = 12;
        self->drawFlags = ENTITY_OPACITY | ENTITY_ROTATE;
        self->blendMode = BLEND_TRANSP | BLEND_ADD;
        self->opacity = 0x80;
        self->rotate = 0;
        self->zPriority = 0x9F;
        PlaySfxPositional(SFX_UNK_NO4_7BE);
    }

    if (self->params) {
        self->rotate += ROT(2.8125);
    } else {
        self->rotate -= ROT(2.8125);
    }

    self->posY.val += FIX(0.5);
    self->opacity -= 4;

    if (self->opacity < 8) {
        DestroyEntity(self);
    }
}

static void RemoveBridgeTiles(void) {
    u16* tile;
    s16 i;

    tile = &g_Tilemap.fg[691];

    for (i = 0; i < 10; i++) {
        *tile++ = 0;
    }
}

static s16 D_us_801815BC[] = {-72, -32, 32, 72, -72, -32, 32, 72};
static s16 D_us_801815CC[] = {7, 4, 4, 7, 7, 4, 4, 7};

void func_us_801C5134(void) {
    Entity* newEntity;
    s16 offsetX;
    s32 i;

    PlaySfxPositional(SFX_WOODEN_BRIDGE_EXPLODE);

    for (i = 1; i < 4; i++) {
        newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
        if (newEntity == NULL) {
            break;
        }
        CreateEntityFromCurrentEntity(E_ID(ID_5C), newEntity);
        newEntity->posX.i.hi += D_us_801815BC[i];
        newEntity->posY.i.hi += D_us_801815CC[i];
        newEntity->params = i;
    }

    offsetX = -72;
    for (i = 0; i < 10; i++) {
        newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
        if (newEntity == NULL) {
            break;
        }
        CreateEntityFromCurrentEntity(E_EXPLOSION, newEntity);
        newEntity->params = 17;
        newEntity->posX.i.hi += ((rand() & 7) * 2) + offsetX - 7;
        newEntity->posY.i.hi += ((rand() & 7) * 4) - 7;
        offsetX += 16;
    }
}

// Function that updates the bridge state in underground caverns
void func_us_801C5268(Entity* self) {
    Entity* entity;
    s16 offsetX;

    if (!self->step) {
        InitializeEntity(g_EInitInteractable);
        self->animSet = ANIMSET_OVL(0);
        self->posX.i.hi = 0x380 - g_Tilemap.scrollX.i.hi;
        if (g_CastleFlags[NO4_SKELETON_APE_AND_BRIDGE] > 1) {
            RemoveBridgeTiles();
            DestroyEntity(self);
            return;
        }
    }
    if (g_CastleFlags[NO4_SKELETON_APE_AND_BRIDGE] == 1) {
        if (!self->step_s) {
            entity = &g_Entities[88];
            if (entity->entityId == E_ID(SKELETON_APE)) {
                entity = entity->ext.et_801C5268.unk80;
                if (entity) {
                    self->ext.et_801C5268.unk7C = entity;
                    self->step_s++;
                }
            }
        } else {
            entity = self->ext.et_801C5268.unk7C;
            if (entity->entityId != E_ID(SKELETON_APE_BARREL)) {
                self->step_s = 0;
            } else if (entity->step == 4 &&
                       entity->posY.i.hi + g_Tilemap.scrollY.i.hi > 128) {
                offsetX = entity->posX.i.hi + g_Tilemap.scrollX.i.hi;
                if (offsetX > 0x328 && offsetX < 0x3D8) {
                    g_CastleFlags[NO4_SKELETON_APE_AND_BRIDGE] = 2;
                }
            }
        }
    }
    if (g_CastleFlags[NO4_SKELETON_APE_AND_BRIDGE] == 2 ||
        g_pads[1].tapped & PAD_TRIANGLE) {
        PlaySfxPositional(SFX_WOODEN_BRIDGE_EXPLODE);
        g_CastleFlags[NO4_SKELETON_APE_AND_BRIDGE]++;
        RemoveBridgeTiles();
        func_us_801C5134();
    }
}

static u16 D_us_801815DC[] = {11, 10, 10, 11, 11, 10, 10, 11};
static u16 D_us_801815EC[] = {0, 0, 1, 1, 0, 0, 1, 1};
static s16 D_us_801815FC[] = {
    -0x100, -0x40, -0x28, -0x120, -0x100, -0x40, -0x28, -0x120,
};
static s32 D_us_8018160C[] = {
    FIX(-3), FIX(-2.5), FIX(-3.125), FIX(-2.25),
    FIX(-3), FIX(-2.5), FIX(-3.125), FIX(-2.25),
};

void func_us_801C542C(Entity* self) {
    u16 params = self->params;
    if (!self->step) {
        InitializeEntity(g_EInitCommon);
        self->animSet = ANIMSET_OVL(1);
        self->animCurFrame = D_us_801815DC[params];
        self->facingLeft = D_us_801815EC[params];
        self->velocityY = D_us_8018160C[params];
        self->drawFlags = ENTITY_ROTATE;
        self->rotate = false;
    }
    if (F(self->velocityY).i.hi < 8) {
        self->velocityY += FIX(0.25);
    }
    MoveEntity();
    self->rotate += D_us_801815FC[params];
}

static s16 water_slow_zones[] = {
    0x260, 0x020, 0x0D0, 0x080, 0x470, 0x020,
    0x0D0, 0x080, 0x0C0, 0x02C, 0x0E0, 0x500,
};

#include "../water_slow_zone.h"

#ifdef VERSION_PSP
static char* D_us_80181644;

static char D_pspeu_0929D7F0[] =
    "\xB4\x24Something appeared\001by the wooden bridge.";
static char D_pspeu_0929D820[] =
    "\xB4\x24Hay algo junto al\001puente de madera.";
static char D_pspeu_0929D848[] =
    "\xB4\x24" _SE("È apparso qualcosa\001vicino al ponte.");
static char D_pspeu_0929D870[] =
    "\xB4\x24" _SE("Une chose est apparue\001près du pont en bois.");
static char D_pspeu_0929D8A0[] =
    "\xB4\x24" _SE("Etwas ist bei der\001Holzbrücke erschienen.");
#elif defined(VERSION_PC) // source is UTF-8, not Shift-JIS
static char D_us_80181644[] =
    "\xB8\x1ESomething appeared near\001to the wooden bridge\x81\x44";
#else
static char D_us_80181644[] =
    "\xB8\x1ESomething appeared near\001to the wooden bridge．";
#endif

/**
 * Function that runs when the player is in the switch room to activate the
 * skeleton ape that can destroy the bridge in underground caverns.
 * Location (X: 21, Y: 33)
 * https://guides.gamercorner.net/sotn/areas/underground-caverns
 */
void func_us_801C5628(Entity* self) {
    Entity* player;
    u16 collision;

    if (!self->step) {
        InitializeEntity(g_EInitInteractable);
        self->animSet = ANIMSET_OVL(1);
        self->animCurFrame = 40;
        if (!g_CastleFlags[NO4_SKELETON_APE_AND_BRIDGE]) {
            self->posX.i.hi = 52;
        } else {
            self->posX.i.hi = 44;
        }
    }

    player = &PLAYER;

    collision = GetPlayerCollisionWith(self, 8, 16, 5);

    if (collision & 1 && g_Player.vram_flag & TOUCHING_GROUND) {
        if (g_pads[0].pressed & PAD_LEFT && PLAYER.step == 1) {
            if (self->ext.et_801C4520.unk7C) {
                self->ext.et_801C4520.unk7C--;
            } else {
                if (self->posX.i.hi > 44) {
                    self->posX.i.hi--;
                    player->posX.i.hi--;
                    if (self->posX.i.hi == 44) {
                        g_CastleFlags[NO4_SKELETON_APE_AND_BRIDGE] = 1;
                        PlaySfxPositional(SFX_SWITCH_CLICK);
                        self->step++;
                    }
                }
                self->ext.et_801C4520.unk7C = 2;
            }
        }
    }

#ifdef VERSION_PSP
    D_us_80181644 = func_pspeu_0923D4A0(
        0, D_pspeu_0929D7F0, D_pspeu_0929D870, D_pspeu_0929D820,
        D_pspeu_0929D8A0, D_pspeu_0929D848);
#endif

    if (self->step == 2 && player->posX.i.hi > 0x80) {
        g_api.PlaySfxVolPan(SFX_WALL_DEBRIS_A, 0x7F, 8);
        player = AllocEntity(&g_Entities[224], &g_Entities[256]);
        if (player != NULL) {
            CreateEntityFromCurrentEntity(E_MESSAGE_BOX, player);
            player->posX.i.hi = 0x80;
            player->posY.i.hi = 0xB0;
            player->ext.messageBox.label = D_us_80181644;
            player->params = 0x100;
        }
        self->step++;
    }
}

void func_us_801C582C(Entity* self) {
    if (g_CastleFlags[NO4_SKELETON_APE_AND_BRIDGE]) {
        self->entityId = E_ID(SKELETON_APE);
        self->pfnUpdate = EntitySkeletonApe;
        EntitySkeletonApe(self);
    }
}

void func_us_801C5868(void) {
    u16* tile;
    s16 i;

    tile = &g_Tilemap.fg[163];

    for (i = 0; i < 10; i++) {
        *tile++ = 0;
    }
}

void func_us_801C58A0(Entity* self) {
    Entity* newEnt;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitCommon);
        if (g_CastleFlags[NO4_SKELETON_APE_AND_BRIDGE]) {
            func_us_801C5868();
            DestroyEntity(self);
        }
        break;

    case 1:
        if (g_CastleFlags[NO4_SKELETON_APE_AND_BRIDGE]) {
            newEnt = AllocEntity(&g_Entities[160], &g_Entities[192]);
            if (newEnt != NULL) {
                CreateEntityFromCurrentEntity(E_ID(SKELETON_APE), newEnt);
                newEnt->params = 2;
                newEnt->posY.i.hi -= 0x60;
                newEnt->posX.i.hi += 0x60;
                self->ext.et_801C5268.unk7C = newEnt + 2;
            }
            self->step++;
        }
        break;

    case 2:
        if (self->ext.et_801C5268.unk7C->step == 4) {
            func_us_801C5868();
            func_us_801C5134();
            DestroyEntity(self);
        }
        break;
    }
}
