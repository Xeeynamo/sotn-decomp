// SPDX-License-Identifier: AGPL-3.0-or-later
#include "stage_02.h"
#include "inc_asm.h"
#include "sattypes.h"

// Alchemy Laboratory

// EntityBreakable (candles)
INCLUDE_ASM("asm/saturn/stage_02/f_nonmat", f60DC040, func_060DC040);

// SAT: func_060DC460
// bust with red eyes that can have a candle on it
void EntityRedEyeBust(Entity* self) {
    SpriteObject* result;
    switch (self->step) {
    case 0:
        TekiInit(self, 3);
        result = CreateSpriteObject(
            entityRedEyeBustData.allocationIndex, entityRedEyeBustData.flags,
            entityRedEyeBustData.images, 1);
        self->unk0 = result;
        func_0600AFA8(result, entityRedEyeBustData2[7]);
        result->zPriority = 0x70;
        result->posX = self->posX.val;
        result->posY = self->posY.val;
        self->step++;
        break;
    case 1:
        break;
    case 2:
        break;
    }
}

void func_060DC4EC(Entity* self) {
    if (self->step == 0) {
        DestroyEntity(self);
    }
}

INCLUDE_ASM("asm/saturn/stage_02/f_nonmat", f60DC510, func_060DC510);
INCLUDE_ASM("asm/saturn/stage_02/f_nonmat", f60DC7B4, func_060DC7B4);
INCLUDE_ASM("asm/saturn/stage_02/f_nonmat", f60DCA54, func_060DCA54);
INCLUDE_ASM("asm/saturn/stage_02/f_nonmat", f60DCCD4, func_060DCCD4);
INCLUDE_ASM("asm/saturn/stage_02/f_nonmat", f60DCFA4, func_060DCFA4);

// EntityCannonLever
INCLUDE_ASM("asm/saturn/stage_02/f_nonmat", f60DD20C, func_060DD20C);

// EntityCannon
INCLUDE_ASM("asm/saturn/stage_02/f_nonmat", f60DD3E8, func_060DD3E8);

// EntityCannonShot
void func_060DD690(Entity* self) {
    Entity* newEntity;
    SpriteObject* sprite;
    s32 posX;

    switch (self->step) {
    case 0:
        TekiInit(self, 5);
        self->step++;
        self->unk0 = CreateSpriteObject(
            g_EntitySpriteBank01.allocationIndex, g_EntitySpriteBank01.flags,
            g_EntitySpriteBank01.images, 1);
        sprite = self->unk0;
        func_0600AFA8(sprite, DAT_06045E14[1]);
        sprite->zPriority = 0x6F;
        self->velocityX = -FIX(10);
        /* fall through */

    case 1:
        MoveEntity(self);
        posX = self->posX.i.hi + g_Tilemap.scrollX.i.hi;
        if (posX < 140) {
            func_0600FB0C(1);
            newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (newEntity != NULL) {
                CreateEntityFromEntity(2, self, newEntity);
                newEntity->params = 3;
            }
            g_CastleFlags[0x83] = 1;
            DestroyEntity(self);
        }
        break;
    }
    func_06079BB4(self);
}

// EntityCannonWall
INCLUDE_ASM("asm/saturn/stage_02/f_nonmat", f60DD790, func_060DD790);

INCLUDE_ASM("asm/saturn/stage_02/f_nonmat", f60DD8D8, func_060DD8D8);
INCLUDE_ASM("asm/saturn/stage_02/f_nonmat", f60DDB80, func_060DDB80);

// SAT: func_060DDE40
// table with globe on it that can be broken
void EntityTableWithGlobe(Entity* self) {
    switch (self->step) {
    case 0:
        TekiInit(self, 5);
        self->step++;
        self->unk0 = CreateSpriteObject(
            g_Stage02TableWithGlobeResource.allocationIndex,
            g_Stage02TableWithGlobeResource.flags,
            g_Stage02TableWithGlobeResource.images, 7);
        self->unk0->zPriority = 0x6A;
        self->hitboxWidth = 10;
        self->hitboxHeight = 12;
        self->hitboxOffX = 0;
        self->hitboxOffY = -0xA;
        self->hitboxState = 2;
    case 1:
        AnimateEntityWithSpriteData(self, g_Stage02TableWithGlobeIdleAnim,
                                    g_Stage02TableWithGlobeFrames);
        if (self->hitFlags != 0) {
            PlaySfxPositional(0x61D); // sotn-lint-ignore
            self->hitboxState = 0;
            CreateEntityFromEntity(E_PERSISTENT_ITEM_DROP, self, &self[1]);
            self[1].params = g_Stage02TableWithGlobeDropParams[self->params];
            SetStep(2);
        }
        break;

    case 2:
        AnimateEntityWithSpriteData(self, g_Stage02TableWithGlobeBreakAnim,
                                    g_Stage02TableWithGlobeFrames);
        break;
    }
    SyncSpriteObjectPos(self);
}

INCLUDE_ASM("asm/saturn/stage_02/f_nonmat", f60DDF64, func_060DDF64);
INCLUDE_ASM("asm/saturn/stage_02/f_nonmat", f60DE178, func_060DE178);

// SAT func_060DE2B0
void CreateExplosionPuff() {
    Entity* entity;
    s8 rand3 = Random() & 3;
    s16 initAngle = ((Random() & 0xF) << 8) - 0x800;
    s32 i;

    for (i = 0; i < 6; i++) {
        entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
        if (entity != NULL) {
            CreateEntityFromEntity(E_FIRE, g_CurrentEntity, entity);
            entity->params = 2;
            entity->ext.opaquePuff.speed = 6 - i;
            entity->ext.opaquePuff.angle = initAngle;
            entity->ext.opaquePuff.puffStyle = rand3;
        }
    }
}

INCLUDE_ASM("asm/saturn/stage_02/f_nonmat", f60DE348, func_060DE348);
INCLUDE_ASM("asm/saturn/stage_02/f_nonmat", f60DE6CC, func_060DE6CC);
INCLUDE_ASM("asm/saturn/stage_02/f_nonmat", f60DE970, func_060DE970);

// EntitySubWeaponContainer
INCLUDE_ASM("asm/saturn/stage_02/f_nonmat", f60DEE20, func_060DEE20);

INCLUDE_ASM("asm/saturn/stage_02/f_nonmat", f60DF264, func_060DF264);
INCLUDE_ASM("asm/saturn/stage_02/f_nonmat", f60DF3B8, func_060DF3B8);
INCLUDE_ASM("asm/saturn/stage_02/f_nonmat", f60DF52C, func_060DF52C);
INCLUDE_ASM("asm/saturn/stage_02/f_nonmat", f60DF664, func_060DF664);
INCLUDE_ASM("asm/saturn/stage_02/f_nonmat", f60DF798, func_060DF798);
INCLUDE_ASM("asm/saturn/stage_02/f_nonmat", f60DFAE4, func_060DFAE4);
INCLUDE_ASM("asm/saturn/stage_02/f_nonmat", f60E0304, func_060E0304);
INCLUDE_ASM("asm/saturn/stage_02/f_nonmat", f60E0684, func_060E0684);
void func_060E08B0(s32 arg0) {
    u8 value;
    s32 offset;
    s32 i;
    s32 limit;
    u8* tiles;
    u8* tilesOdd;

    value = arg0 == 0 ? 3 : 0;
    offset = 0x260;
    i = 0;
    limit = 3;
    tiles = DAT_0608FFF8;
    tilesOdd = tiles + 1;

    for (; i <= limit; i++) {
        tiles[offset] = value;
        tilesOdd[offset] = value;
        offset += 0x10;
    }
}
extern u16 g_Stage02PurpleBrickTilemap0[];
extern u16 g_Stage02PurpleBrickTilemap1[];
extern u16 g_Stage02PurpleBrickTilemap2[];

void func_060E08E4(s32 arg0, s32 arg1) {
    u16* tilemap;

    switch (arg1) {
    case 1:
        tilemap = g_Stage02PurpleBrickTilemap0;
        break;
    case 2:
        tilemap = g_Stage02PurpleBrickTilemap1;
        break;
    case 3:
        tilemap = g_Stage02PurpleBrickTilemap2;
        break;
    default:
        return;
    }

    func_060E9058(tilemap, 0, 0, 76);
}
INCLUDE_ASM("asm/saturn/stage_02/f_nonmat", f60E093C, func_060E093C);
void func_060E0AF0(Entity* self) {
    u8 value;
    s32 offset;
    s32 i;
    s32 limit;
    u8* tiles;
    u8* tilesOdd;

    value = self == NULL ? 3 : 0;
    offset = 0x2E7;
    i = 0;
    limit = 1;
    tiles = DAT_0608FFF8;
    tilesOdd = tiles + 1;

    for (; i <= limit; i++) {
        tiles[offset] = value;
        tilesOdd[offset] = value;
        offset += 0x10;
    }
}
extern u16 g_Stage02SecretWallTilemap0[];
extern u16 g_Stage02SecretWallTilemap1[];
extern u16 g_Stage02SecretWallTilemap2[];

void func_060E0B24(s32 unused, s32 arg0) {
    u16* tilemap;

    switch (arg0) {
    case 1:
        tilemap = g_Stage02SecretWallTilemap0;
        break;
    case 2:
        tilemap = g_Stage02SecretWallTilemap1;
        break;
    case 3:
        tilemap = g_Stage02SecretWallTilemap2;
        break;
    default:
        return;
    }

    func_060E9058(tilemap, 0, 17, 92);
}
INCLUDE_ASM("asm/saturn/stage_02/f_nonmat", f60E0B7C, func_060E0B7C);
INCLUDE_ASM("asm/saturn/stage_02/f_nonmat", f60E0DC8, func_060E0DC8);

void func_60E0F58() {}

void func_60E0F64() {}

INCLUDE_ASM("asm/saturn/stage_02/f_nonmat", f60E0F70, func_060E0F70);
INCLUDE_ASM("asm/saturn/stage_02/f_nonmat", f60E1A00, func_060E1A00);
struct Unk {
    /* 0x00 */ u8 pad0[0x2C];
    /* 0x2C */ s32 primIndex2C;
    /* 0x30 */ s32 primIndex30;
    /* 0x34 */ u32 pad34;
    /* 0x38 */ u16 unk_38;
    /* 0x3A */ u16 unk_3a;
    /* 0x3C */ u32 unk_3c;
};

extern s32 DAT_060F50AC;

void func_060E1C08(Entity* self) {
    if (g_pads[0].previous == 0x0800) {
        DAT_060F50AC = 1;

        if (self->flags & FLAG_HAS_PRIMS) {
            FreePrimitives(self->primIndex);
            self->flags ^= FLAG_HAS_PRIMS;
        }

        if (DAT_060e2014.primIndex30 != -1) {
            FreePrimitives(DAT_060e2014.primIndex30);
        }

        if (DAT_060e2014.primIndex2C != -1) {
            FreePrimitives(DAT_060e2014.primIndex2C);
        }

        PlaySfx(0xF0000090);
        self->step = 1;
        self->step_s = 0;
        func_060100B8();
    }
}
INCLUDE_ASM("asm/saturn/stage_02/f_nonmat", f60E1CA8, func_060E1CA8);
INCLUDE_ASM("asm/saturn/stage_02/f_nonmat", f60E1D48, func_060E1D48);

// maybe func_801B797C?
void func_060e1ff8(s32 param_1) {
    DAT_060e2014.unk_3c = param_1;
    DAT_060e2014.unk_3a = 0;
    DAT_060e2014.unk_38 = 1;
}

INCLUDE_ASM("asm/saturn/stage_02/f_nonmat", f60E2018, func_060E2018);
INCLUDE_ASM("asm/saturn/stage_02/f_nonmat", f60E21B8, func_060E21B8);
INCLUDE_ASM("asm/saturn/stage_02/f_nonmat", f60E22FC, func_060E22FC);
INCLUDE_ASM("asm/saturn/stage_02/f_nonmat", f60E2420, func_060E2420);
void CheckCollision(s32 x, s32 y, Collider* res, u16 unk);
void func_06079BE4(Entity* self);

void func_060E2898(u16 arg0) {
    Entity* self = g_CurrentEntity;
    Collider col;

    if (self->velocityY < 0) {
        CheckCollision(self->posX.val, self->posY.val - FIX(7), &col, 0);
        if (col.effects & EFFECT_NOTHROUGH) {
            self->velocityY = 0;
        }
    }

    CheckCollision(self->posX.val, self->posY.val + FIX(8), &col, 0);

    if (arg0 != 0) {
        if (!(col.effects & EFFECT_NOTHROUGH)) {
            MoveEntity(self);
            func_06079BE4(self);
            return;
        }

        self->velocityX = 0;
        self->velocityY = 0;
        if (col.effects & EFFECT_QUICKSAND) {
            self->posY.val += FIX(0.125);
        } else {
            self->posY.val += col.unk18;
        }
        self->posY.i.hi++;
        self->posY.i.lo = 0;
    } else {
        Entity* current;

        if (col.effects & EFFECT_NOTHROUGH) {
            return;
        }

        MoveEntity(self);
        current = g_CurrentEntity;
        if (current->velocityY >= 0) {
            current->ext.equipItemDrop.fallSpeed +=
                current->ext.equipItemDrop.gravity;
            current->velocityX = current->ext.equipItemDrop.fallSpeed;
            if (current->velocityX == FIX(1) || current->velocityX == FIX(-1)) {
                current->ext.equipItemDrop.gravity =
                    -current->ext.equipItemDrop.gravity;
            }
        }

        if (current->velocityY < FIX(0.25)) {
            current->velocityY += FIX(0.125);
        }
    }
}

const volatile u16 DAT_060E2982 = 9;
extern s16 DAT_060F1AE8[];
extern u16 g_Stage02AlucardSubweaponIds[];

void func_060E29A4(u16 cardIndex) {
    Entity* self;
    Entity* player;
    u16 params;
    s16 subWeaponId;
    s8 timer;
    u8* timerPtr;

    self = g_CurrentEntity;
    PlaySfx(0x67C);
    params = g_Status.subWeapon;
    player = g_Entities;
    subWeaponId = DAT_060F1AE8[cardIndex];
    g_Status.subWeapon = subWeaponId;

    if (params == subWeaponId) {
        params = 1;
        timerPtr = self->unk6D;
        timer = 0x10;
    } else {
        params = g_Stage02AlucardSubweaponIds[params];
        timerPtr = self->unk6D;
        timer = 0x60;
    }
    *timerPtr = timer;

    if (params != 0) {
        self->params = params;
        self->posY.i.hi = player->posY.i.hi + 0xC;
        SetStep(7);
        self->unk0->flags |= 8;
        self->ext.subweaponCard.unk86 = 5;
        self->velocityY = -FIX(2.5);
        if (player->facingLeft != 1) {
            self->velocityX = -FIX(2.5);
            return;
        }
        self->velocityX = FIX(2.5);
    } else {
        DestroyEntity(self);
    }
}

// EntityPersistentItemDrop
INCLUDE_ASM("asm/saturn/stage_02/f_nonmat", f60E2A80, func_060E2A80);

INCLUDE_ASM("asm/saturn/stage_02/f_nonmat", f60E32DC, func_060E32DC);
INCLUDE_ASM("asm/saturn/stage_02/f_nonmat", f60E37C8, func_060E37C8);
INCLUDE_ASM("asm/saturn/stage_02/f_nonmat", f60E3FBC, func_060E3FBC);
extern u16 g_Stage02PrizeDrops[];

void func_060E42FC(Entity* self) {
    u16 item;
    PfnEntityUpdate update;

    if (self->step == 0) {
        self->ext.prizeDrop.itemFlagIndex = self->params + 0x20;
        item = self->ext.prizeDrop.itemFlagIndex;
        if (((g_CastleFlags + 0x100)[item >> 3] >> (item & 7)) & 1) {
            DestroyEntity(self);
            return;
        }

        item -= 0x20;
        item = g_Stage02PrizeDrops[item];
        if (item < 0x80) {
            self->unkB4 = (Entity*)func_060E2A80;
        } else {
            self->unkB4 = (Entity*)func_060E32DC;
            item -= 0x80;
        }
        self->params = item + 0x8000;
    } else {
        item = self->ext.prizeDrop.itemFlagIndex;
        if (self->step < 5 && self->hitFlags) {
            (g_CastleFlags + 0x100)[item >> 3] |= 1 << (item & 7);
            self->step = 5;
        }
    }

    update = (PfnEntityUpdate)self->unkB4;
    update(self);
}
INCLUDE_ASM("asm/saturn/stage_02/f_nonmat", f60E43F4, func_060E43F4);
INCLUDE_ASM("asm/saturn/stage_02/f_nonmat", f60E4908, func_060E4908);

// SAT func_060E4F78
// PSX func_801BBC3C
// Different from PSX version but same idea
s32 func_801BBC3C(Entity* e) {
    s16 diff;

    diff = PLAYER.posX.i.hi - e->posX.i.hi;
    diff = ABS(diff);

    if (diff >= 23) {
        return 0;
    } else {
        diff = PLAYER.posY.i.hi - e->posY.i.hi;
        diff = ABS(diff);
        if (diff > 32) {
            return 0;
        }
    }

    return 1;
}

INCLUDE_ASM("asm/saturn/stage_02/f_nonmat", f60E4FD0, func_060E4FD0);
void func_060E5388(Entity* arg0) {
    Tilemap* map;
    u8* dest;
    s16 scroll_y;
    s32 index;
    s32 i;
    s32 offset;
    s32 x;
    s32 y;

    map = &g_Tilemap;
    i = 0;
    dest = DAT_0608FFF8;
    offset = -0x18;
    do {
        x = arg0->posX.i.hi;
        y = arg0->posY.i.hi;
        index = ((x + map->scrollX.i.hi) << 2) / 5;
        scroll_y = map->scrollY.i.hi;
        index =
            (index >> 4) + (((y + offset + scroll_y) >> 4) * map->hSize * 0x10);
        dest[index] = arg0->animCurFrame != 0 ? 3 : 0;
        i += 1;
        offset += 0x10;
    } while (i <= 3);
}

const u16 pad_060E540C[] = {0xCCCC, 0xCCCD};
INCLUDE_ASM("asm/saturn/stage_02/f_nonmat", f60E5410, func_060E5410);

// EntityExplosion
INCLUDE_ASM("asm/saturn/stage_02/f_nonmat", f60E5AE4, func_060E5AE4);

INCLUDE_ASM("asm/saturn/stage_02/f_nonmat", f60E5C4C, func_060E5C4C);
void func_060E5DB4(Entity* self) {
    Entity* entity;

    switch (self->step) {
    case 0:
        TekiInit(self, 2);
        self->step++;
        self->ext.explosionEmitter.parentId =
            self->ext.explosionEmitter.parent->entityId;
        /* fall through */
    case 1:
        if (self->ext.explosionEmitter.timer++ > 4) {
            entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (entity != NULL) {
                CreateEntityFromEntity(E_STAGE_EXPLOSION, self, entity);
                entity->entityId = E_STAGE_EXPLOSION;
                entity->pfnUpdate = func_060E5AE4;
                entity->params = self->params;
            }
            self->ext.explosionEmitter.timer = 0;
        }
        self->posX.i.hi = self->ext.explosionEmitter.parent->posX.i.hi;
        self->posY.i.hi = self->ext.explosionEmitter.parent->posY.i.hi;
        if (self->ext.explosionEmitter.parent->entityId !=
            self->ext.explosionEmitter.parentId) {
            DestroyEntity(self);
        }
        break;
    default:
        return;
    }
}
INCLUDE_ASM("asm/saturn/stage_02/f_nonmat", f60E5EA0, func_060E5EA0);
INCLUDE_ASM("asm/saturn/stage_02/f_nonmat", f60E600C, func_060E600C);
INCLUDE_ASM("asm/saturn/stage_02/f_nonmat", f60E6140, func_060E6140);
INCLUDE_ASM("asm/saturn/stage_02/f_nonmat", f60E625C, func_060E625C);
INCLUDE_ASM("asm/saturn/stage_02/f_nonmat", f60E633C, func_060E633C);
INCLUDE_ASM("asm/saturn/stage_02/f_nonmat", f60E6628, func_060E6628);
void func_060E6B00(Entity* self) {
    SpriteObject* sprite;
    SaturnSpriteFrameHeader** frame;
    s16 params;
    u16 flags;
    u32 spriteFlags;
    s32 maxParts;
    s32 offset;
    s32 count;
    s32 i;

    if (self->step == 0) {
        params = self->params;
        spriteFlags = params & (s16)0xff00;
        flags = params & 3;
        if (flags & 2) {
            maxParts = 18;
        } else {
            maxParts = 6;
        }

        sprite = CreateSpriteObject(
            g_EntitySpriteBank08.allocationIndex, g_EntitySpriteBank08.flags,
            g_EntitySpriteBank08.images, maxParts);
        self->unk0 = sprite;
        TekiInit(self, 3);
        self->step++;
        frame = DAT_06046CD0;
        if (flags & 2) {
            frame += 2;
        } else {
            frame += 1;
        }
        func_0600AFA8(sprite, *frame);

        if (spriteFlags != 0) {
            sprite->flags |= 0x30;
        }
        sprite->flags = (sprite->flags & 0xfff8) | 3;
        sprite->posX = self->posX.val;
        sprite->posY = self->posY.val;

        offset = 0xb0;
        if (flags & 1) {
            offset = 0xbd;
        }
        flags &= 2;
        count = 2;
        if (flags != 0) {
            count = 6;
        }

        for (i = 0; i < count; i++) {
            DAT_0608FFF8[offset] = 3;
            DAT_0608FFF8[offset + 1] = 3;
            DAT_0608FFF8[offset + 2] = 3;
            offset -= 0x10;
        }
    }
}

static const volatile u16 DAT_060E6BF2 = 0x0009;
INCLUDE_ASM("asm/saturn/stage_02/f_nonmat", f60E6C0C, func_060E6C0C);
INCLUDE_ASM("asm/saturn/stage_02/f_nonmat", f60E7014, func_060E7014);
INCLUDE_ASM("asm/saturn/stage_02/f_nonmat", f60E73CC, func_060E73CC);

void PlaySfx(s32);
void DestroyEntity(Entity*);

static inline SetGeomScreen(u32 h) { DAT_06061DE0[0] = DAT_06061DE0[1] = h; }

static inline void SetGeomOffset(u16 ofx, u16 ofy) {
    DAT_06061DE8[0] = ofx;
    DAT_06061DE8[1] = ofy;
}

void func_060E7508(Entity* self) {
    s32 orig;
    s32 iVar6;
    s32 uVar13;
    Entity* player;
    s32 primIndex;

    player = &PLAYER;
    orig = DAT_060F5088[1];
    switch (self->step) {
    case 0:
        TekiInit(self, 5);
        self->step++;
        primIndex = AllocPrimitives(2, 0x3B);
        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->primIndex = primIndex;
        self->flags |= FLAG_HAS_PRIMS;
        DAT_060F1D90 = 0;
        func_060E837C(self, 0);
        self->ext.save.unk0 = 0;
        self->ext.save.unk38 = 0;
        self->ext.save.unk4 = 0;
        if (DAT_0605DD60 != 0) {
            DAT_0605C668 = 0;
            self->ext.save.unk4 = 0x28;
            self->ext.save.unk24 = 0x100;
            self->ext.save.unk0 = 7;
            DAT_0605DD60 = 0;
        }
        break;
    case 1:
        break;
    default:
        return;
    }

    SetGeomScreen(0x10000);
    SetGeomOffset(0xA0, self->ext.save.unk30 + 0x80);

    switch (self->ext.save.unk0) {
    case 0:
        DAT_060F5088[1] += 6;
        uVar13 = g_GameTimer & 0x7F;
        if (uVar13 == 0) {
            PlaySfx(SFX_SAVE_HEARTBEAT);
        }
        if (uVar13 & 0x40) {
            uVar13 = 0x7F - uVar13;
        }
        if (uVar13 >= 8) {
            uVar13 = 0xC0;
        } else {
            uVar13 = uVar13 * 4 + 0xA0;
        }
        func_060E8780(self->ext.save.unk8, 0, uVar13, 0);
        self->ext.save.unk24 = uVar13;
        if (func_060E82EC(0x78, 0xC8) != 0) {
            self->ext.save.unk28 = DAT_060485C0.unk4;
            self->ext.save.unk2C = DAT_060485C0.unk5;
            DAT_0605C668 = 0;
            if (DAT_060F1D90 == 0) {
                DAT_0605C658 = 0;
            }
            D_8013B5E8 = 0x10;
            g_Status.hp = g_Status.hpMax;
            g_Status.mp = g_Status.mpMax;
            self->ext.save.unk0++;
        }
        break;

    case 1:
        DAT_060F5088[1] += 7;
        if (self->ext.save.unk24 < 0xC0) {
            self->ext.save.unk24 += 4;
        }
        func_060E8780(self->ext.save.unk8, 0, self->ext.save.unk24, 0);
        if ((self->ext.save.unk30 < (g_CurrentRoom.stageID >> 1 & 0x10) + 8) &&
            (g_GameTimer != 0)) {
            self->ext.save.unk30++;
        }
        if (player->posX.i.hi < 0x9E) {
            g_Player.padSim = PAD_RIGHT;
            g_Player.demo_timer = 1;
        } else if (player->posX.i.hi > 0xA0) {
            g_Player.padSim = PAD_LEFT;
            g_Player.demo_timer = 1;
        } else {
            if (self->ext.save.unk30 ==
                (g_CurrentRoom.stageID >> 1 & 0x10) + 8) {
                func_060e8330();
                self->ext.save.unk34 = 8;
                if ((DAT_060485C0.unk4 >= 0) && (DAT_060485C0.unk5 != 0)) {
                    func_060E8350(self);
                    self->ext.save.unk0 = 0x80;
                    if (DAT_060485C0.unk5 < 0) {
                        self->ext.save.unk2C = 0;
                        self->ext.save.unk38 = 1;
                        self->ext.save.unk0 = 2;
                        self->ext.save.unk4 = 10;
                    }
                } else {
                    DAT_060485C0.unk4 = 0;
                    func_060E8350(self);
                    self->ext.save.unk0 = 0x81;
                }
            } else {
                func_060e8330();
            }
        }
        break;

    case 0x80:
        func_060e8330();
        DAT_060F5088[1] += self->ext.save.unk34;
        func_060E8780(self->ext.save.unk8, 0, self->ext.save.unk24, 0);
        if (func_06066B30(self, 3) != 0) {
            if (self->ext.save.unk1C == 0) {
                self->ext.save.unk38 = 2;
                self->ext.save.unk0 = 2;
                self->ext.save.unk4 = 0x1E;
            } else {
                func_060E8350(self);
                self->ext.save.unk0++;
            }
        }
        break;

    case 0x81:
        func_060e8330();
        DAT_060F5088[1] += self->ext.save.unk34;
        func_060E8780(self->ext.save.unk8, 0, self->ext.save.unk24, 0);
        if (func_06066B30(self, 4) != 0) {
            if (self->ext.save.unk1C == 0) {
                DAT_060485C0.unk4 = 0;
                func_060E8350(self);
                self->ext.save.unk0 = 0x100;
            } else {
                DAT_060485C0.unk4 = self->ext.save.unk28;
                DAT_060485C0.unk5 = self->ext.save.unk2C;
                self->ext.save.unk0 = 0x101;
            }
        }
        break;

    case 0x100:
        func_060e8330();
        DAT_060F5088[1] += self->ext.save.unk34;
        func_060E8780(self->ext.save.unk8, 0, self->ext.save.unk24, 0);
        if (DAT_0605DD94 != 0) {
            iVar6 = func_06066B30(self, 1);
            if (iVar6 == 0) {
                break;
            }
            if (iVar6 == 2) {
                self->ext.save.unk0++;
                break;
            }
            self->ext.save.unk38 = 1;
            self->ext.save.unk0 = 2;
            self->ext.save.unk4 = 10;
        } else {
            self->ext.save.unk38 = 1;
            self->ext.save.unk0 = 2;
            self->ext.save.unk4 = 10;
        }
        break;

    case 0x101:
        DAT_060F5088[1] += self->ext.save.unk34;
        func_060E8780(self->ext.save.unk8, 0, self->ext.save.unk24, 0);
        if (g_pads[0].pressed & 0x700) {
            DAT_060485C0.unk4 = self->ext.save.unk28;
            DAT_060485C0.unk5 = self->ext.save.unk2C;
            g_Player.padSim = 0;
            g_Player.demo_timer = 1;
        } else {
            DAT_0605C668 = 1;
            DAT_0605C658 = 1;
            self->ext.save.unk0 = 0;
        }
        break;

    case 2:
        func_060e8330();
        DAT_060F5088[1] += self->ext.save.unk34;
        self->ext.save.unk24 += 4;
        if (self->ext.save.unk24 > 0x100) {
            self->ext.save.unk24 = 0x100;
        }
        func_060E8780(self->ext.save.unk8, 0, self->ext.save.unk24, 0);
        if (self->ext.save.unk24 == 0x100) {
            if ((self->ext.save.unk4 > 0x1D) || (DAT_060F1D90 != 0)) {
                self->ext.save.unk0++;
            } else {
                self->ext.save.unk34++;
                if (self->ext.save.unk34 > 0x80) {
                    self->ext.save.unk34 = 0x80;
                }
            }
        }
        break;

    case 3:
        func_060e8330();
        DAT_060F5088[1] += self->ext.save.unk34;
        self->ext.save.unk34++;
        if (self->ext.save.unk34 > 0x80) {
            self->ext.save.unk34 = 0x80;
        }
        func_060E8780(self->ext.save.unk8, 0, self->ext.save.unk24, 0);
        if (self->ext.save.unk34 == 0x80) {
            self->ext.save.unk0++;
            self->ext.save.unk20 = 0;
        }
        break;

    case 4:
        func_060e8330();
        DAT_060F5088[1] += self->ext.save.unk34;
        self->ext.save.unk20 += 2;
        if (self->ext.save.unk20 > 0x7F) {
            self->ext.save.unk20 = 0x7F;
        }
        func_060E8780(
            self->ext.save.unk8, 0, self->ext.save.unk24, self->ext.save.unk20);
        if (self->ext.save.unk20 >= 0x10) {
            uVar13 = (self->ext.save.unk20 - 0x10) * 0x10;
            if (uVar13 > 0x100) {
                uVar13 = 0x100;
            }
            func_060E8DE0(self->ext.save.unkC, uVar13, 0);
        }
        if (self->ext.save.unk20 != 0x7F) {
            break;
        }
        if (self->ext.save.unk4 > 0x27 || DAT_060F1D90 != 0) {
            if ((DAT_060F5088[1] & 0xFFF) >= 0x100 &&
                (DAT_060F5088[1] & 0xFFF) < 0x180) {
                self->ext.save.unk0++;
            }
        }
        break;

    case 5:
        func_060e8330();
        if (self->ext.save.unk34 > 0x40) {
            self->ext.save.unk34--;
        } else {
            if ((DAT_060F5088[1] & 0x7FF) >= 0x400) {
                self->ext.save.unk34 = (0x800 - (DAT_060F5088[1] & 0x7FF)) / 16;
            }
        }
        if (self->ext.save.unk34 < 0x10) {
            self->ext.save.unk34 = 0x10;
        }
        DAT_060F5088[1] += self->ext.save.unk34;
        self->ext.save.unk20 -= 2;
        if (self->ext.save.unk20 < 0) {
            self->ext.save.unk20 = 0;
        }
        func_060E8780(
            self->ext.save.unk8, 1, self->ext.save.unk24, self->ext.save.unk20);
        if (self->ext.save.unk20 != 0) {
            func_060E8DE0(self->ext.save.unkC, self->ext.save.unk24, 0);
        } else {
            func_060E8DE0(self->ext.save.unkC, 0, 0);
        }

        if (self->ext.save.unk34 == 0x10 &&
            (DAT_060F5088[1] & 0x7FF) >= 0x7F0) {
            DAT_060F5088[1] = 0;
            func_060E8780(self->ext.save.unk8, 1, self->ext.save.unk24, 0);
            func_060E8350(self);
            self->ext.save.unk0++;
        }
        break;

    case 6:
        func_060e8330();
        if (self->ext.save.unk4 > 0x27 && func_06066B30(self, 0)) {
            if (self->ext.save.unk4 == 0x2B) {
                func_060E8350(self);
                self->ext.save.unk0 = 0x200;
            } else if (self->ext.save.unk4 != 0x28) {
                self->ext.save.unk0 = 0x20;
                self->ext.save.unk20 = 0x60;
            } else {
                self->ext.save.unk0++;
            }
        }
        break;

    case 0x200:
        func_060e8330();
        if (func_06066B30(self, 2) != 0) {
            if (self->ext.save.unk1C == 0) {
                DAT_060485C0.unk5 = 0;
                PlaySfx(SFX_UI_CONFIRM);
                self->ext.save.unk0++;
            } else {
                self->ext.save.unk0 = 0x20;
                self->ext.save.unk20 = 0x60;
            }
        }
        break;

    case 0x201:
        func_060e8330();
        if (func_06030640(DAT_060485C0.unk4) == 0) {
            self->ext.save.unk0 = 0x30;
            self->ext.save.unk20 = 0x60;
        } else {
            self->ext.save.unk4 = 0x2A;
            func_060E8350(self);
            self->ext.save.unk0++;
        }
        break;

    case 0x202:
        func_060e8330();
        if (func_06066B30(self, 0) != 0) {
            self->ext.save.unk0 = 0x20;
            self->ext.save.unk20 = 0x60;
        }
        break;

    case 7:
        func_060e8330();
        func_060E8780(self->ext.save.unk8, 1, self->ext.save.unk24, 0);
        self->ext.save.unk0++;
        break;

    case 8:
        func_060e8330();
        DAT_060F5088[1] += self->ext.save.unk34;
        self->ext.save.unk34 += 2;
        if (self->ext.save.unk34 > 0x40) {
            self->ext.save.unk34 = 0x40;
        }
        func_060E8780(self->ext.save.unk8, 1, self->ext.save.unk24, 0);
        if (self->ext.save.unk34 == 0x40) {
            self->ext.save.unk0++;
            self->ext.save.unk20 = 0;
        }
        break;

    case 9:
        DAT_060F5088[1] += self->ext.save.unk34;
        self->ext.save.unk20++;
        if (self->ext.save.unk20 > 0x7F) {
            self->ext.save.unk20 = 0x7F;
        }
        func_060E8780(
            self->ext.save.unk8, 2, self->ext.save.unk24, self->ext.save.unk20);
        if (self->ext.save.unk20 >= 0x40) {
            func_060E8DE0(self->ext.save.unkC, self->ext.save.unk24, 0);
            DAT_0605C668 = 1;
            DAT_0605C658 = 1;
        } else {
            func_060E8DE0(self->ext.save.unkC, self->ext.save.unk24,
                          self->ext.save.unk20 * 2 + 0x80);
            func_060e8330();
        }
        if (self->ext.save.unk20 == 0x7F) {
            self->ext.save.unk0++;
            self->ext.save.unk20 = 0;
        }
        break;

    case 10:
        DAT_060F5088[1] += self->ext.save.unk34;
        self->ext.save.unk20++;
        if (self->ext.save.unk20 > 0x22) {
            self->ext.save.unk20 = 0x22;
        }
        func_060E8DE0(
            self->ext.save.unkC, self->ext.save.unk24, self->ext.save.unk20);
        if (self->ext.save.unk34 == 0) {
            self->ext.save.unk0++;
        }
        break;

    case 11:
        break;

    case 12:
        DAT_060F5088[1] = 0;
        self->ext.save.unk24 = 0x180;
        func_060E8780(self->ext.save.unk8, 1, self->ext.save.unk24, 0);
        self->ext.save.unk20 = 0;
        self->ext.save.unk0++;
        break;

    case 13:
        DAT_060F5088[1] += 9;
        func_060E8780(
            self->ext.save.unk8, 3, self->ext.save.unk24, self->ext.save.unk20);
        self->ext.save.unk20++;
        if (self->ext.save.unk20 == 0x60) {
            self->ext.save.unk0++;
        }
        break;

    case 14:
        DAT_060F5088[1] += 9;
        func_060E8780(
            self->ext.save.unk8, 3, self->ext.save.unk24, self->ext.save.unk20);
        self->ext.save.unk20--;
        if (self->ext.save.unk20 == 0) {
            self->ext.save.unk0--;
        }
        break;

    case 0x20:
    case 0x30:
        if (self->ext.save.unk0 == 0x30) {
            func_060e8330();
        }
        if (self->ext.save.unk20 > 0x30) {
            func_060e8330();
        }
        DAT_060F5088[1] += 6;
        if (self->ext.save.unk24 > 0xC0) {
            self->ext.save.unk24 -= 2;
        }
        func_060E8780(
            self->ext.save.unk8, 3, self->ext.save.unk24, self->ext.save.unk20);
        self->ext.save.unk20 -= 2;
        if ((g_Player.demo_timer == 0) && (g_pads[0].pressed & 0x700)) {
            g_Player.padSim = 0;
            g_Player.demo_timer = 1;
            if (self->ext.save.unk20 < 1) {
                self->ext.save.unk20 = 0;
            }
        } else if (self->ext.save.unk20 < 1) {
            if (self->ext.save.unk0 == 0x30) {
                self->ext.save.unk38 = 0;
                self->ext.save.unk4 = 0;
                self->ext.save.unk0 = 1;
            } else {
                DAT_060485C0.unk4 = self->ext.save.unk28;
                DAT_060485C0.unk5 = self->ext.save.unk2C;
                self->ext.save.unk38 = 0;
                self->ext.save.unk4 = 0;
                self->ext.save.unk0 = 0;
                DAT_0605C668 = 1;
                DAT_0605C658 = 1;
            }
        }
        break;

    default:
        func_060E8780(self->ext.save.unk8, 1, self->ext.save.unk24, 0);
        break;
    }

    if (((orig + 0x400) ^ (DAT_060F5088[1] + 0x400)) & 0x800) {
        if (self->ext.save.unk0 >= 3 && self->ext.save.unk0 < 10) {
            PlaySfx(SFX_SAVE_COFFIN_SWISH);
        }
    }
    func_060E81D4(self);
}

INCLUDE_ASM("asm/saturn/stage_02/f_nonmat", f60E81D4, func_060E81D4);
u16 func_060E82EC(s32 minX, s32 maxX) {
    u16 standing;

    g_Player.unk7A = 1;
    if (PLAYER.step != 0 || (standing = PLAYER.step_s) != 1 ||
        PLAYER.posX.i.hi < minX || PLAYER.posX.i.hi > maxX) {
        standing = 0;
    }
    return standing;
}

// not seeing an obvious PSX equivalent
void func_060e8330(void) {
    g_Player.padSim = PAD_UP;
    g_Player.demo_timer = 1;
}

void func_060E8350(Entity* self) {
    Primitive* prim = self->ext.save.unk10;
    s32 i;

    for (i = 0; i < 9; i++) {
        prim->x3 = 0;
        prim->drawMode = DRAW_HIDE;
        prim = prim->next;
    }
}

INCLUDE_ASM("asm/saturn/stage_02/f_nonmat", f60E837C, func_060E837C);

void func_060E8ADC(s32, s32, s32);

void func_060E8780(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    func_060E87D0(arg1, arg3);
    func_060E8990(arg1, arg2, arg3);
    func_060E8ADC(arg0, arg1, arg3);
}

INCLUDE_ASM("asm/saturn/stage_02/f_nonmat", f60E87D0, func_060E87D0);
INCLUDE_ASM("asm/saturn/stage_02/f_nonmat", f60E8990, func_060E8990);
INCLUDE_ASM("asm/saturn/stage_02/f_nonmat", f60E8ADC, func_060E8ADC);

void func_060E8DE0(s32 arg0, s32 arg1, s32 arg2) {
    func_060E8E1C(arg1, arg2);
    func_060E8EEC(arg0, arg1, arg2);
}

extern s32 DAT_060485e0[];
extern s32 DAT_060F5098;
extern MthMatrixTbl DAT_06061DF0;
extern s32 g_Stage02Entity08ModelVertices14[];

void SetCurrentMatrixBinAngle(s32 angle, s32* axis);
void TransformAndProjectPoints(s32* src, s32* dst, s32 count);

void func_060E8E1C(s32 arg0, s32 arg1) {
    s32* dst_base;
    s32* dst;
    s32* src;
    s32* src1;
    s32* dst1;
    s32 i;
    s32 limit;

    dst_base = DAT_060485e0;
    src = g_Stage02Entity08ModelVertices14;
    dst = dst_base;
    arg0 <<= 8;
    i = 0;
    limit = 13;
    src1 = src + 1;
    dst1 = dst_base + 1;

    for (; i <= limit; i++) {
        dst[0] = src[0] * arg0;
        dst1[0] = src1[0] * arg0;
        dst1[1] = src1[1] * arg0;
        src += 3;
        dst += 3;
        src1 += 3;
        dst1 += 3;
    }

    SetCurrentMatrixBinAngle(DAT_060F5088, &DAT_060F5098);

    DAT_06061DF0.current->val[0][0] = DAT_06061DF0.current->val[0][0] * 5 / 4;
    DAT_06061DF0.current->val[0][1] = DAT_06061DF0.current->val[0][1] * 5 / 4;
    DAT_06061DF0.current->val[0][2] = DAT_06061DF0.current->val[0][2] * 5 / 4;

    TransformAndProjectPoints(dst_base, dst_base + 0x102, 14);
}
INCLUDE_ASM("asm/saturn/stage_02/f_nonmat", f60E8EEC, func_060E8EEC);
INCLUDE_ASM("asm/saturn/stage_02/f_nonmat", f60E9058, func_060E9058);
extern s16 DAT_060F212E[];

void func_060E9220(Entity* entity) {
    struct SpriteParts* parts = &g_Stage02Entity37SpriteParts0;
    SaturnSpriteResource* bank = (SaturnSpriteResource*)g_Stage02SpriteBank28;

    entity->unk0 =
        CreateSpriteObject(bank->allocationIndex, bank->flags, parts, 2);
    SyncSpriteObjectPosUnchecked(entity, DAT_060F212E);
    entity->step = 1;
}

void func_060E9270(Entity* self) {
    SyncSpriteObjectPos(self);
    func_0600B004(self->unk0, g_Stage02Entity38Frames[self->animCurFrame]);
}

// dupe of func_060e97c4
void func_060E92A8(u16** param_1) {
    if (*(u16*)(param_1 + 6) != 0) {
        **param_1 |= 0x10;
    } else {
        **param_1 &= ~0x10;
    }
}

// not sure what these are
const u16 pad_060e92d4 = 0xAAAA;
const u16 pad_060e92d6 = 0xAAAB;

// EntityBloodSkeleton
INCLUDE_ASM("asm/saturn/stage_02/f_nonmat", f60E92D8, func_060E92D8);

extern s16 g_Stage02BoneScimitarInitOffset[];

void func_060E9770(Entity* self) {
    struct SpriteParts* parts = &g_Stage02BoneScimitarSpriteParts0;
    SaturnSpriteResource* bank = (SaturnSpriteResource*)g_Stage02SpriteBank29;

    self->unk0 =
        CreateSpriteObject(bank->allocationIndex, bank->flags, parts, 5);
    SyncSpriteObjectPosUnchecked(self, g_Stage02BoneScimitarInitOffset);
    self->step++;
}

// seems to saturn-only. param_1 is probably a struct?
void func_060e97c4(u16** param_1) {
    if (*(u16*)(param_1 + 6) != 0) {
        **param_1 |= 0x10;
    } else {
        **param_1 &= ~0x10;
    }
}

void func_060E97F0(Entity* self) {
    SyncSpriteObjectPos(self);
    func_0600B004(self->unk0, g_Stage02BoneScimitarFrames[self->animCurFrame]);
}

// EntityBoneScimitar
INCLUDE_ASM("asm/saturn/stage_02/f_nonmat", f60E9828, func_060E9828);

INCLUDE_ASM("asm/saturn/stage_02/f_nonmat", f60EA058, func_060EA058);
INCLUDE_ASM("asm/saturn/stage_02/f_nonmat", f60EA1E0, func_060EA1E0);

// dupe of func_060e97c4
void func_060EA234(u16** param_1) {
    if (*(u16*)(param_1 + 6) != 0) {
        **param_1 |= 0x10;
    } else {
        **param_1 &= ~0x10;
    }
}

// not sure what these are
const u16 pad_060EA260 = 0xCCCC;
const u16 pad_060EA262 = 0xCCCD;

// EntityAxeKnight
INCLUDE_ASM("asm/saturn/stage_02/f_nonmat", f60EA264, func_060EA264);

// EntityAxeKnightThrowingAxe
// SAT: func_060EAC54
void EntityAxeKnightRotateAxe(Entity* self) {
    self->unk0->flags |= FLAG_UNK_40;

    if (self->params != 0) {
        self->unk0->rotate += 0x80;
    } else {
        self->unk0->rotate -= 0x80;
    }
    if (self->params != 0) {
        self->rotate += 0x80;
    } else {
        self->rotate -= 0x80;
    }

    self->rotate &= 0xFFF;
}

INCLUDE_ASM("asm/saturn/stage_02/f_nonmat", f60EACC0, func_060EACC0);

INCLUDE_ASM("asm/saturn/stage_02/f_nonmat", f60EAF2C, func_060EAF2C);

// EntityBloodyZombie
INCLUDE_ASM("asm/saturn/stage_02/f_nonmat", f60EAFAC, func_060EAFAC);

INCLUDE_ASM("asm/saturn/stage_02/f_nonmat", f60EB5C4, func_060EB5C4);
INCLUDE_ASM("asm/saturn/stage_02/f_nonmat", f60EB6E4, func_060EB6E4);
extern u8 g_Stage02SkeletonFrames[];
extern u8 DAT_060F4378[];
extern s16 DAT_060F42C0[];

void func_060EB8D0(Entity* self) {
    struct SpriteParts* parts = &g_Stage02SkeletonSpriteParts0;
    SaturnSpriteResource* bank = (SaturnSpriteResource*)g_Stage02SpriteBank32;

    self->unk0 =
        CreateSpriteObject(bank->allocationIndex, bank->flags, parts, 4);

    self->ext.spriteAnimEnemy.frames = g_Stage02SkeletonFrames;
    self->ext.spriteAnimEnemy.animations = DAT_060F4378;
    self->ext.spriteAnimEnemy.unk80 = 0;
    self->ext.spriteAnimEnemy.unk81 = 0;
    self->ext.spriteAnimEnemy.unk82 = 0;

    SyncSpriteObjectPosUnchecked(self, DAT_060F42C0);
    self->step++;
}
extern s16 DAT_060F42D0[];
extern s16 DAT_060F42D8[];

extern void func_06079BCC(Entity* self);
extern s32 func_06079DEC(Entity* self, s16* sensors);
extern s32 func_06079F60(Entity* self, s16* sensors, s16 count);
extern void func_0607AA40(Entity* self, s32 arg1, s32 arg2, s32 arg3);

void func_060EB950(Entity* self) {
    u8 result;
    u16 flags;

    func_06079BCC(self);
    result = func_06079DEC(self, DAT_060F42D0);
    if (result == 0x60) {
        self->posX.val -= self->velocityX;
    }

    flags = func_06079F60(self, DAT_060F42D8, 3);
    if (result == 0x80 || (flags & 2)) {
        func_0607AA40(self, 5, 4, 0);
        self->ext.bloodyZombie.unk84 = 10;
    } else if (--self->ext.bloodyZombie.unk98 == 0) {
        func_0607AA40(self, 4, 3, 0);
        self->ext.bloodyZombie.unk84 = 31;
    }
}

// EntitySkeleton
INCLUDE_ASM("asm/saturn/stage_02/f_nonmat", f60EB9EC, func_060EB9EC);

INCLUDE_ASM("asm/saturn/stage_02/f_nonmat", f60EBEB0, func_060EBEB0);
INCLUDE_ASM("asm/saturn/stage_02/f_nonmat", f60EC030, func_060EC030);
INCLUDE_ASM("asm/saturn/stage_02/f_nonmat", f60EC1F0, func_060EC1F0);

void func_060EC240(Entity* self) {
    SyncSpriteObjectPos(self);
    func_0600B004(self->unk0, g_Stage02SpittleBoneFrames[self->animCurFrame]);
}

// EntitySpittleBone
INCLUDE_ASM("asm/saturn/stage_02/f_nonmat", f60EC278, func_060EC278);

INCLUDE_ASM("asm/saturn/stage_02/f_nonmat", f60EC730, func_060EC730);
INCLUDE_ASM("asm/saturn/stage_02/f_nonmat", f60EC888, func_060EC888);
