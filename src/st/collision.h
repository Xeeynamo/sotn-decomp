// SPDX-License-Identifier: AGPL-3.0-or-later
#include <stage.h>
#include <scratchpad.h>

#if defined(VERSION_US)
static u16 g_testCollEnemyLookup[] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1E, 0x00, 0x00, 0x2B, 0x00, 0x10,
    0x00, 0x0D, 0x68, 0x68, 0x16, 0x00, 0x00, 0x00, 0x3E, 0x00, 0x23, 0x50,
    0x00, 0x00, 0x00, 0x06, 0x00, 0x0A, 0x00, 0x7D, 0x00, 0x00, 0x2D, 0x00,
    0x00, 0x6D, 0x7B, 0x00, 0x17, 0x41, 0x00, 0x73, 0x00, 0x4C, 0x00, 0x00,
    0x38, 0x14, 0x5C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x46, 0x00, 0x00, 0x03, 0x58, 0x44, 0x24, 0x37, 0x00, 0x02, 0x59,
    0x00, 0x00, 0x00, 0x07, 0x00, 0x56, 0x00, 0x7C, 0x00, 0x0B, 0x00, 0x26,
    0x00, 0x1D, 0x00, 0x00, 0x2A, 0x00, 0x00, 0x00, 0x00, 0x27, 0x00, 0x00,
    0x00, 0x1C, 0x00, 0x31, 0x00, 0x00, 0x1A, 0x00, 0x8D, 0x09, 0x2C, 0x30,
    0x20, 0x00, 0x05, 0x47, 0x00, 0x5E, 0x35, 0x34, 0x6A, 0x00, 0x3A, 0x00,
    0x66, 0x00, 0x45, 0x00, 0x19, 0x00, 0x71, 0x00, 0x29, 0x39, 0x00, 0x51,
    0x00, 0x4D, 0x00, 0x00, 0x3F, 0x00, 0x77, 0x00, 0x00, 0x72, 0x00, 0x00,
    0x6F, 0x00, 0x2F, 0x00, 0x74, 0x00, 0x00, 0x79, 0x00, 0x7A, 0x00, 0x00,
    0x13, 0x11, 0x36, 0x36, 0x00, 0x5F, 0x5F, 0x00, 0x00, 0x67, 0x00, 0x75,
    0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x0E, 0x00,
    0x2E, 0x00, 0x69, 0x21, 0x00, 0x00, 0x55, 0x00, 0x54, 0x00, 0x53, 0x00,
    0x00, 0x0F, 0x00, 0x76, 0x00, 0x00, 0x8E, 0x00, 0x00, 0x00, 0x00, 0x4A,
    0x00, 0x00, 0x4B, 0x00, 0x00, 0x00, 0x00, 0x43, 0x00, 0x00, 0x3D, 0x00,
    0x78, 0x8A, 0x00, 0x00, 0x00, 0x52, 0x00, 0x00, 0x89, 0x48, 0x00, 0x3C,
    0x40, 0x8B, 0x00, 0x00, 0x00, 0x1F, 0x00, 0x00, 0x7E, 0x00, 0x00, 0x49,
    0x00, 0x00, 0x00, 0x15, 0x00, 0x00, 0x0C, 0x28, 0x00, 0x00, 0x00, 0x32,
    0x00, 0x22, 0x12, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x33, 0x60, 0x00,
    0x64, 0x00, 0x00, 0x7F, 0x00, 0x00, 0x00, 0x4E, 0x00, 0x6E, 0x00, 0x00,
    0x00, 0x4F, 0x00, 0x00, 0x57, 0x00, 0x00, 0x00, 0x86, 0x65, 0x00, 0x3B,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x25, 0x62, 0x62, 0x00, 0x00, 0x00,
    0x42, 0x00, 0x00, 0x18, 0x1B, 0x6B, 0x00, 0x8C, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x61, 0x63,
    0x88, 0x00, 0x00, 0x00, 0x85, 0x00, 0x00, 0x00, 0x00, 0x00, 0x84, 0x00,
    0x00, 0x87, 0x00, 0x00, 0x00, 0x00, 0x5D, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x5B, 0x91, 0x00, 0x00, 0x00, 0x00, 0x90, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x5A, 0x00, 0x00, 0x82, 0x00, 0x00, 0x00, 0x83, 0x00,
    0x81, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x92, 0x00, 0x00, 0x00, 0x00,
    0x04, 0x00, 0x70, 0x00, 0x00, 0x6C, 0x00, 0x00, 0x80, 0x80, 0x00, 0x00,
    0x8F, 0x00, 0x00, 0x00,
};
#elif defined(VERSION_PSP)
static u16 g_testCollEnemyLookup[] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1E, 0x00, 0x00, 0x2A, 0x00, 0x11,
    0x00, 0x0E, 0x68, 0x68, 0x16, 0x00, 0x00, 0x00, 0x3D, 0x00, 0x28, 0x52,
    0x00, 0x00, 0x00, 0x08, 0x00, 0x0B, 0x00, 0x7B, 0x00, 0x00, 0x2D, 0x00,
    0x00, 0x6F, 0x7A, 0x00, 0x18, 0x41, 0x00, 0x70, 0x00, 0x4D, 0x00, 0x00,
    0x35, 0x15, 0x5C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x46, 0x00, 0x00, 0x05, 0x56, 0x42, 0x25, 0x34, 0x00, 0x02, 0x59,
    0x00, 0x00, 0x00, 0x07, 0x00, 0x57, 0x00, 0x7D, 0x00, 0x09, 0x00, 0x23,
    0x00, 0x1D, 0x00, 0x00, 0x2B, 0x00, 0x00, 0x00, 0x00, 0x21, 0x00, 0x00,
    0x00, 0x1B, 0x00, 0x31, 0x00, 0x00, 0x19, 0x00, 0x8E, 0x0A, 0x2C, 0x30,
    0x20, 0x00, 0x04, 0x48, 0x00, 0x5E, 0x37, 0x36, 0x69, 0x00, 0x3B, 0x00,
    0x65, 0x00, 0x45, 0x00, 0x1A, 0x00, 0x6E, 0x00, 0x26, 0x38, 0x00, 0x4F,
    0x00, 0x4C, 0x00, 0x00, 0x40, 0x00, 0x76, 0x00, 0x00, 0x6D, 0x00, 0x00,
    0x71, 0x00, 0x2F, 0x00, 0x75, 0x00, 0x00, 0x79, 0x00, 0x7C, 0x00, 0x00,
    0x13, 0x0F, 0x39, 0x39, 0x00, 0x5B, 0x5B, 0x00, 0x00, 0x67, 0x00, 0x77,
    0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x0D, 0x00,
    0x2E, 0x00, 0x6A, 0x29, 0x00, 0x00, 0x54, 0x00, 0x53, 0x00, 0x55, 0x00,
    0x00, 0x10, 0x00, 0x74, 0x00, 0x00, 0x8F, 0x00, 0x00, 0x00, 0x00, 0x4A,
    0x00, 0x00, 0x47, 0x00, 0x00, 0x00, 0x00, 0x43, 0x00, 0x00, 0x3F, 0x00,
    0x78, 0x8B, 0x00, 0x00, 0x00, 0x4E, 0x00, 0x00, 0x8A, 0x4B, 0x00, 0x3E,
    0x3C, 0x89, 0x00, 0x00, 0x00, 0x1F, 0x00, 0x00, 0x7E, 0x00, 0x00, 0x49,
    0x00, 0x00, 0x00, 0x14, 0x00, 0x00, 0x0C, 0x27, 0x00, 0x00, 0x00, 0x33,
    0x00, 0x24, 0x12, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x32, 0x61, 0x00,
    0x63, 0x00, 0x00, 0x82, 0x00, 0x00, 0x00, 0x51, 0x00, 0x73, 0x00, 0x00,
    0x00, 0x50, 0x00, 0x00, 0x58, 0x00, 0x00, 0x00, 0x84, 0x66, 0x00, 0x3A,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x22, 0x64, 0x64, 0x00, 0x00, 0x00,
    0x44, 0x00, 0x00, 0x17, 0x1C, 0x6B, 0x00, 0x8D, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0x62,
    0x88, 0x00, 0x00, 0x00, 0x86, 0x00, 0x00, 0x00, 0x00, 0x00, 0x85, 0x00,
    0x00, 0x87, 0x00, 0x00, 0x00, 0x00, 0x5F, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x5D, 0x92, 0x00, 0x00, 0x00, 0x00, 0x91, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x5A, 0x00, 0x00, 0x83, 0x00, 0x00, 0x00, 0x80, 0x00,
    0x7F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x93, 0x00, 0x00, 0x00, 0x00,
    0x03, 0x00, 0x72, 0x00, 0x00, 0x6C, 0x00, 0x00, 0x81, 0x81, 0x00, 0x00,
    0x90, 0x00, 0x00, 0x00, 0x8C, 0x00, 0x00, 0x00};
#elif defined(VERSION_HD)
static u16 g_testCollEnemyLookup[] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1E, 0x00, 0x00, 0x2A, 0x00, 0x11,
    0x00, 0x0E, 0x68, 0x68, 0x16, 0x00, 0x00, 0x00, 0x3D, 0x00, 0x28, 0x52,
    0x00, 0x00, 0x00, 0x08, 0x00, 0x0B, 0x00, 0x7B, 0x00, 0x00, 0x2D, 0x00,
    0x00, 0x6F, 0x7A, 0x00, 0x18, 0x41, 0x00, 0x70, 0x00, 0x4D, 0x00, 0x00,
    0x35, 0x15, 0x5C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x46, 0x00, 0x00, 0x05, 0x56, 0x42, 0x25, 0x34, 0x00, 0x02, 0x59,
    0x00, 0x00, 0x00, 0x07, 0x00, 0x57, 0x00, 0x7D, 0x00, 0x09, 0x00, 0x23,
    0x00, 0x1D, 0x00, 0x00, 0x2B, 0x00, 0x00, 0x00, 0x00, 0x21, 0x00, 0x00,
    0x00, 0x1B, 0x00, 0x31, 0x00, 0x00, 0x19, 0x00, 0x8D, 0x0A, 0x2C, 0x30,
    0x20, 0x00, 0x04, 0x48, 0x00, 0x5E, 0x37, 0x36, 0x69, 0x00, 0x3B, 0x00,
    0x65, 0x00, 0x45, 0x00, 0x1A, 0x00, 0x6E, 0x00, 0x26, 0x38, 0x00, 0x4F,
    0x00, 0x4C, 0x00, 0x00, 0x40, 0x00, 0x76, 0x00, 0x00, 0x6D, 0x00, 0x00,
    0x71, 0x00, 0x2F, 0x00, 0x75, 0x00, 0x00, 0x79, 0x00, 0x7C, 0x00, 0x00,
    0x13, 0x0F, 0x39, 0x39, 0x00, 0x5B, 0x5B, 0x00, 0x00, 0x67, 0x00, 0x77,
    0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x0D, 0x00,
    0x2E, 0x00, 0x6A, 0x29, 0x00, 0x00, 0x54, 0x00, 0x53, 0x00, 0x55, 0x00,
    0x00, 0x10, 0x00, 0x74, 0x00, 0x00, 0x8E, 0x00, 0x00, 0x00, 0x00, 0x4A,
    0x00, 0x00, 0x47, 0x00, 0x00, 0x00, 0x00, 0x43, 0x00, 0x00, 0x3F, 0x00,
    0x78, 0x8B, 0x00, 0x00, 0x00, 0x4E, 0x00, 0x00, 0x8A, 0x4B, 0x00, 0x3E,
    0x3C, 0x89, 0x00, 0x00, 0x00, 0x1F, 0x00, 0x00, 0x7E, 0x00, 0x00, 0x49,
    0x00, 0x00, 0x00, 0x14, 0x00, 0x00, 0x0C, 0x27, 0x00, 0x00, 0x00, 0x33,
    0x00, 0x24, 0x12, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x32, 0x61, 0x00,
    0x63, 0x00, 0x00, 0x82, 0x00, 0x00, 0x00, 0x51, 0x00, 0x73, 0x00, 0x00,
    0x00, 0x50, 0x00, 0x00, 0x58, 0x00, 0x00, 0x00, 0x84, 0x66, 0x00, 0x3A,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x22, 0x64, 0x64, 0x00, 0x00, 0x00,
    0x44, 0x00, 0x00, 0x17, 0x1C, 0x6B, 0x00, 0x8C, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0x62,
    0x88, 0x00, 0x00, 0x00, 0x86, 0x00, 0x00, 0x00, 0x00, 0x00, 0x85, 0x00,
    0x00, 0x87, 0x00, 0x00, 0x00, 0x00, 0x5F, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x5D, 0x91, 0x00, 0x00, 0x00, 0x00, 0x90, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x5A, 0x00, 0x00, 0x83, 0x00, 0x00, 0x00, 0x80, 0x00,
    0x7F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x92, 0x00, 0x00, 0x00, 0x00,
    0x03, 0x00, 0x72, 0x00, 0x00, 0x6C, 0x00, 0x00, 0x81, 0x81, 0x00, 0x00,
    0x8F, 0x00, 0x00, 0x00,
};

#endif

static u8 g_testCollLuckCutoff[] = {0x00, 0x40, 0x20, 0x10};

static u8 g_testColluCoords[] = {
    0x80, 0x80, 0xA0, 0xA0, 0xC0, 0xC0, 0x00, 0x00,
};

static u8 g_testCollvCoords[] = {
    0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x00, 0x00,
};

static u16 g_testCollElementLookup[] = {
    ELEMENT_FIRE,  ELEMENT_THUNDER, ELEMENT_ICE,    ELEMENT_HOLY,  ELEMENT_DARK,
    ELEMENT_STONE, ELEMENT_CURSE,   ELEMENT_POISON, ELEMENT_WATER, ELEMENT_CUT,
};

static u8 g_testColliFrames[] = {2, 4, 3, 5, 6, 7, 8, 10, 2, 1};

static u16 g_testCollPrizeTable[] = {
    0x0003, 0x0000, 0x0002, 0x0003, 0x0003, 0x0003, 0x0003, 0x0003,
    0x0003, 0x0004, 0x0004, 0x0004, 0x0004, 0x0005, 0x0005, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0001, 0x0001, 0x0002, 0x0006, 0x0007, 0x00C6,
};

// The Jewel Sword drop table below consists of pairs of numbers
// The first value of each pair is the threshold (out of 0xFFF)
// The second value of each pair is the dropped item ID

static u16 g_jewelSwordDropTable[] = {
    // clang-format off
    0xC00, DROP_ZIRCON,
    0xF00, DROP_AQUAMARINE,
    0xFD0, DROP_TURQUOISE,
    0xFF0, DROP_ONYX,
    0xFF8, DROP_GARNET,
    0xFFD, DROP_OPAL,
    0xFFF, DROP_DIAMOND,
    // clang-format on
};

// To determine the ratio for a given drop, you subtract the threshold that came
// before it in the list (0 for the first entry) from its threshold.

// For example, Turquoise has a threshold of 0x0FD0 (4048 in decimal), and
// Aquamarine (the entry before it) has a threshold of 0x0F00 (3840 in decimal).
// Therefore, Turquoise has a drop ratio of 208 (4048 - 3840 = 208). That means
// that out of 4096 drops from a Jewel Sword, 208 Turquoises are expected, on
// average.

// The table above equates to the following drop ratios for all gems
// Item       | Ratio
// -----------+------
// Zircon     |  3073 (This number is 1 larger than expected due to >=)
// Aquamarine |   768
// Turquoise  |   208
// Onyx       |    32
// Garnet     |     8
// Opal       |     5
// Diamond    |     2

static u16 g_eDamageDisplayClut[] = {
    PAL_UNK_1B2, PAL_UNK_1B3, PAL_UNK_1B6, PAL_UNK_1B7,
    PAL_UNK_1B4, PAL_UNK_1B5, PAL_UNK_1B0, PAL_UNK_1B1,
};

void HitDetection(void) {
#ifdef VERSION_PC
    u8 sp[SP_LEN];
#endif
    Entity* otherEntity;
    Primitive* prim;
    Entity* entityHit;
    s32* spHitbox;
    Entity* iterEnt;
    s32* spHitboxState;
    u16* dropTable;
    s16 x, y;
    u16 miscVar1;
    u16 hitboxCheck2;
    s32 hitboxWidth;
    s32 yCoord1;
    u32 hitboxCheck1;
    EnemyDef* enemyDef;
    u16 i;
    Entity* entity;
    u8 miscVar2;
    u16 miscVar3;
    u8 uselessVar;

    spHitboxState = SPAD(0);
    spHitbox = SPAD(0x30);
    for (entity = &g_Entities[0]; entity < &g_Entities[48]; spHitboxState++,
        entity++) {
        *spHitboxState = entity->hitboxState;
        if ((*spHitboxState != 0) && !(*spHitboxState & 0x80)) {
            *spHitbox = entity->posX.i.hi;
            if (entity->facingLeft) {
                *spHitbox -= entity->hitboxOffX;
            } else {
                *spHitbox += entity->hitboxOffX;
            }
            yCoord1 = entity->posY.i.hi + entity->hitboxOffY;
            if ((*spHitbox < -32) || (*spHitbox > 288) || (yCoord1 < -32) ||
                (yCoord1 > 256) || !entity->hitboxWidth ||
                !entity->hitboxHeight) {
                *spHitboxState = 0;
                spHitbox += 4;
            } else {
                spHitbox++;
                *spHitbox++ = entity->hitboxWidth;
                *spHitbox++ = yCoord1;
                *spHitbox++ = entity->hitboxHeight;
            }
        } else {
            spHitbox += 4;
        }
    }
    for (entity = &g_Entities[64]; entity < &g_Entities[192]; entity++) {
        miscVar1 = entity->hitboxState;
        if (!miscVar1 || !entity->hitboxWidth || !entity->hitboxHeight ||
            (entity->flags & FLAG_DEAD)) {
            continue;
        }
        for (i = 0; i < 11; i++) {
            if (entity->unk6D[i]) {
                entity->unk6D[i]--;
            }
        }
        x = entity->posX.i.hi;
        if (entity->facingLeft) {
            x -= entity->hitboxOffX;
        } else {
            x += entity->hitboxOffX;
        }
        y = entity->posY.i.hi + entity->hitboxOffY;
        if (x <= -32 || x >= 288 || y <= -32 || y >= 256) {
            continue;
        }
        miscVar2 = 0;
        miscVar3 = (u16)(miscVar1 & 0x3E);
        hitboxWidth = entity->hitboxWidth - 1;
        yCoord1 = entity->hitboxHeight - 1;
        if (miscVar3) {
            spHitboxState = SPAD(1);
            spHitbox = SPAD(0x34);
            for (iterEnt = &g_Entities[1]; iterEnt < &g_Entities[48];
                 iterEnt++) {
                if ((*spHitboxState & miscVar3) &&
                    (!entity->unk6D[iterEnt->enemyId])) {
                    if (*spHitboxState & 0x80) {
                        entity->hitParams = iterEnt->hitEffect & 0x7F;
                        miscVar2 = 0xFF;
                        break;
                    }
                    hitboxCheck2 = (u16)*spHitbox++ - (u16)x;
                    hitboxCheck1 = hitboxWidth + *spHitbox++;
                    hitboxCheck2 += hitboxCheck1;
                    hitboxCheck1 *= 2;
                    if (hitboxCheck2 <= hitboxCheck1) {
                        hitboxCheck2 = (u16)*spHitbox++ - (u16)y;
                        hitboxCheck1 = yCoord1 + *spHitbox++;
                        hitboxCheck2 += hitboxCheck1;
                        hitboxCheck1 *= 2;
                        if (hitboxCheck2 <= hitboxCheck1) {
                            // reusing the i variable here, maybe can be a
                            // different var
                            i = iterEnt->hitEffect & 0x7F;
                            if (!(iterEnt->flags & entity->flags &
                                  FLAG_UNK_100000)) {
                                // Probably has to stay generic since
                                // iterEnt could be any entity?
                                iterEnt->unkB8 = entity;
                                // reminder: iterEnt1->hitboxState
                                if (miscVar1 & 8) {
                                    iterEnt->hitFlags = 3;
                                } else {
                                    iterEnt->hitFlags = 1;
                                }
                                if ((i == 3) &&
                                    (entity->flags & FLAG_UNK_8000)) {
                                    g_api.PlaySfx(SFX_METAL_CLANG_E);
                                    iterEnt->hitFlags = 2;
                                }
                                if ((i == 4) &&
                                    (entity->flags & FLAG_UNK_4000)) {
                                    g_api.PlaySfx(SFX_METAL_CLANG_E);
                                    iterEnt->hitFlags = 2;
                                }
                            }
                            entity->hitParams = i;
                            miscVar2 = 0xFF;
                            break;
                        } else {
                            spHitboxState++;
                            continue;
                        }
                    } else {
                        spHitboxState++;
                        spHitbox += 2;
                        continue;
                    }
                } else {
                    spHitboxState++;
                    spHitbox += 4;
                }
            }
        }

        if ((miscVar1 & 1) && !miscVar2) {
            // Note that in this block, iterEnt is never advanced, so it's
            // always the player.
            iterEnt = &PLAYER;
            spHitboxState = SPAD(0);
            spHitbox = SPAD(0x30);
            if (!entity->unk6D[iterEnt->enemyId] && (*spHitboxState & 1)) {
                hitboxCheck2 = (u16)*spHitbox++ - (u16)x;
                hitboxCheck1 = hitboxWidth + *spHitbox++;
                hitboxCheck2 += hitboxCheck1;
                hitboxCheck1 *= 2;
                if (hitboxCheck2 <= hitboxCheck1) {
                    hitboxCheck2 = (u16)*spHitbox++ - (u16)y;
                    hitboxCheck1 = yCoord1 + *spHitbox++;
                    hitboxCheck2 += hitboxCheck1;
                    hitboxCheck1 *= 2;
                    if (hitboxCheck2 <= hitboxCheck1) {
                        if (entity->attack &&
                            iterEnt->hitPoints < entity->attack) {
                            iterEnt->unkB8 = entity;
                            if (miscVar1 & 8) {
                                iterEnt->hitFlags = 3;
                            } else {
                                iterEnt->hitFlags = 1;
                            }
                            iterEnt->hitParams = entity->attackElement;
                            iterEnt->hitPoints = entity->attack;
                        }
                        entity->hitParams = iterEnt->hitEffect & 0x7F;
                        miscVar2 = 0xFF;
                        entity->hitFlags = 0x80;
                    }
                }
            }
        }
        if (!miscVar2) {
            continue;
        }
        if (entity->parent) {
            entityHit = entity->parent;
            entityHit->hitParams = entity->hitParams;
            entityHit->hitFlags = entity->hitFlags;
        } else {
            entityHit = entity;
        }
        if ((entityHit->flags & FLAG_DEAD) || !miscVar2) {
            continue;
        }
        hitboxCheck2 = iterEnt->hitEffect & 0x7F;
        if (hitboxCheck2 == 2 || (hitboxCheck2 == 6 && (miscVar1 & 0x20))) {
            otherEntity = AllocEntity(&g_Entities[160], &g_Entities[192]);
            if (otherEntity) {
                CreateEntityFromEntity(E_SOUL_STEAL_ORB, entity, otherEntity);
            }
        }
        miscVar1 = g_testCollEnemyLookup[entityHit->enemyId];
        if (miscVar1) {
            miscVar1--;
            miscVar3 = 1 << (miscVar1 & 7);
            g_CastleFlags[(miscVar1 >> 3) + ENEMY_LIST_190] |= miscVar3;
        }
        if ((g_Status.relics[RELIC_FAERIE_SCROLL] & 2) &&
            (entityHit->flags & FLAG_NOT_AN_ENEMY) == 0) {
            if (g_unkGraphicsStruct.BottomCornerTextTimer != 0) {
                g_api.FreePrimitives(g_unkGraphicsStruct.BottomCornerTextPrims);
                g_unkGraphicsStruct.BottomCornerTextTimer = 0;
            }
            BottomCornerText(g_api.enemyDefs[entityHit->enemyId].name, false);
            entityHit->flags |= FLAG_NOT_AN_ENEMY;
        }
        miscVar2 = 0;
        // Odd structure - may be a macro or a fake match,
        // the block is intentionally a no-op to match PSP
        if ((entity->hitboxState & 8) && (iterEnt->hitboxState & 4)) {
            (void)0;
        } else if (entityHit->hitPoints) {
            if (iterEnt->attack) {
                if ((iterEnt->hitboxState & 0x80) == 0) {
                    spHitbox -= 4;
                    x += *spHitbox++;
                    spHitbox++;
                    y += *spHitbox;
                    x /= 2;
                    y /= 2;
                }
                prim = &g_PrimBuf[g_unkGraphicsStruct.D_800973F8];
                while (prim != NULL) {
                    if (prim->drawMode == DRAW_HIDE) {
                        prim->clut = PAL_UNK_199;
                        prim->x0 = prim->x2 = x - 13 + (Random() & 7) - 3;
                        prim->x1 = prim->x3 = prim->x0 + 0x20;
                        prim->y0 = prim->y1 = y - 10 + (Random() & 7) - 3;
                        prim->y2 = prim->y3 = prim->y0 + 0x20;
                        prim->p1 = 0;
                        if (iterEnt->zPriority > entity->zPriority) {
                            prim->priority = iterEnt->zPriority + 1;
                        } else {
                            prim->priority = entity->zPriority + 1;
                        }
                        prim->drawMode = DRAW_UNK02;
                        break;
                    }
                    prim = prim->next;
                }
            }
            if (iterEnt->attack && entityHit->hitPoints != 0x7FFF) {
                miscVar1 = g_api.DealDamage(entity, iterEnt);
                if (iterEnt->hitboxState == 4) {
                    miscVar1 = 0;
                }
                if ((g_Status.relics[RELIC_SPIRIT_ORB] & 2) &&
                    !(entityHit->flags & FLAG_KEEP_ALIVE_OFFCAMERA) &&
                    miscVar1) {
                    otherEntity =
                        AllocEntity(&g_Entities[224], &g_Entities[256]);
                    if (otherEntity != NULL) {
                        DestroyEntity(otherEntity);
                        otherEntity->entityId = 4;
                        otherEntity->pfnUpdate = EntityDamageDisplay;
                        otherEntity->posX.i.hi = x;
                        otherEntity->posY.i.hi = y;
                        otherEntity->params = miscVar1;
                    }
                }
            } else {
                miscVar1 = 0;
            }
            if (miscVar1 != 0xC000) {
                if (miscVar1 & 0x8000) {
                    miscVar2 = 9;
                } else {
                    miscVar3 = (u16)iterEnt->attackElement;
                    // includes all elements 0x40 and up
                    if (miscVar3 & 0xFFC0) {
                        for (i = 0; i < LEN(g_testCollElementLookup); i++) {
                            if (miscVar3 & g_testCollElementLookup[i]) {
                                miscVar2 = g_testColliFrames[i];
                                break;
                            }
                        }
                    }
                }
            } else {
                entityHit->hitFlags |= 0x20;
                miscVar1 = 0;
            }
            if (!miscVar1) {
                goto unusual_spot;
            }
            if (miscVar1 & 0x8000) {
                entityHit->hitPoints += (miscVar1 & 0x3FFF);
                miscVar3 = g_api.enemyDefs[entityHit->enemyId].hitPoints;
                if (entityHit->hitPoints > miscVar3) {
                    entityHit->hitPoints = miscVar3;
                }
            } else {
                miscVar1 &= 0x3FFF;
                if (entityHit->flags & FLAG_UNK_10) {
                    // Different on PSP vs PSX
#ifdef VERSION_PSP
                    if (g_PlayableCharacter == PLAYER_RICHTER) {
#else
                    if (g_PlayableCharacter != PLAYER_ALUCARD) {
#endif
                        // normally this is Alucard shouting "Dark
                        // Metamorphosis" but obviously if not playing
                        // as Alucard, this won't match
                        g_api.PlaySfx(SFX_RIC_WHIP_HIT);
                    } else {
                        if (iterEnt->hitEffect & 0x80) {
                            g_api.PlaySfx(SFX_WEAPON_STAB_B);
                        } else {
                            g_api.PlaySfx(SFX_WEAPON_HIT_A);
                        }
                    }
                }
                if (entityHit->hitPoints != 0x7FFE) {
                    if (entityHit->hitPoints < (miscVar1 * 2)) {
                        entityHit->hitFlags |= 3;
                    } else if (entityHit->hitPoints < (miscVar1 * 4)) {
                        entityHit->hitFlags |= 2;
                    } else {
                        entityHit->hitFlags |= 1;
                    }
                    entityHit->hitPoints -= miscVar1;
                }
                if ((iterEnt->attackElement & ELEMENT_CUT) &&
                    (entityHit->hitboxState & 0x10)) {
                    otherEntity =
                        AllocEntity(&g_Entities[160], &g_Entities[192]);
                    if (otherEntity != NULL) {
                        CreateEntityFromEntity(
                            E_ENEMY_BLOOD, entity, otherEntity);
                        if (x > entity->posX.i.hi) {
                            otherEntity->params = 1;
                        }
                        otherEntity->posX.i.hi = x;
                        otherEntity->posY.i.hi = y;
                        otherEntity->zPriority = 192;
                    }
                }
            }
            if (entityHit->hitPoints > 0) {
                otherEntity = entityHit;
                miscVar3 = iterEnt->enemyId;
                do {
                    otherEntity->unk6D[miscVar3] =
                        iterEnt->nFramesInvincibility;
                    if (entityHit < otherEntity) {
                        otherEntity->unk6D[miscVar3]++;
                    }
                    if (!(entity->flags & FLAG_SUPPRESS_STUN)) {
                        otherEntity->stunFrames = iterEnt->stunFrames;
                    }
                    if (!otherEntity->hitEffect &&
                        !(otherEntity->flags & 0xF)) {
                        otherEntity->hitEffect = otherEntity->palette;
                    }
                    otherEntity->nFramesInvincibility = miscVar2;
                    otherEntity->flags |= 0xF;
                    otherEntity = otherEntity->nextPart;
                } while (otherEntity != NULL && otherEntity != entityHit);
                // I don't understand this; we write to a spot but we
                // never reference it again.
                uselessVar = ((u32)entityHit->flags >> 4) & 7;
                continue;
            }
        }
        PreventEntityFromRespawning(entityHit);
        enemyDef = &g_api.enemyDefs[entityHit->enemyId];
        if ((entityHit->hitFlags & 0x80) == 0) {
            g_api.func_800FE044(enemyDef->exp, enemyDef->level);
            if ((entityHit->flags & FLAG_UNK_1000) &&
                g_Status.killCount < 999999) {
                g_Status.killCount++;
            }
        }
        miscVar3 = entityHit->flags & (FLAG_UNK_800 | FLAG_UNK_400);
        if (miscVar3) {
            if ((rand() & 0xFF) <
                g_api.func_800FF460(g_testCollLuckCutoff[miscVar3 >> 0xA])) {
                otherEntity = AllocEntity(&g_Entities[160], &g_Entities[192]);
                miscVar1 = 0;
                if (otherEntity != NULL) {
                    // Determine which jewel to randomly drop from the
                    // Jewel Sword
                    if (hitboxCheck2 == 5) {
                        dropTable = g_jewelSwordDropTable;
                        miscVar3 = rand() & 0xFFF;
                        while (true) {
                            if (*dropTable++ >= miscVar3) {
                                miscVar3 = *dropTable;
                                break;
                            }
                            dropTable++;
                        }
                    } else {
                        miscVar3 = g_api.func_800FF494(enemyDef);
                        if (miscVar3 & 0x40) {
                            miscVar3 = enemyDef->rareItemId;
                            // Paranthropus check: Drops turquoise if
                            // game not beaten. Otherwise ring of Varda
                            if (miscVar3 == 0x173 && !g_GameClearFlag) {
                                miscVar3 = 0x16A;
                            } else {
                                miscVar1 =
                                    g_testCollEnemyLookup[entityHit->enemyId];
                            }
                        } else if (miscVar3 & 0x20) {
                            miscVar3 = enemyDef->uncommonItemId;
                        } else {
                            // select a prize from the table. This
                            // covers heart, money, etc drops.
                            miscVar3 = g_testCollPrizeTable[miscVar3];
                        }
                    }
                    if (miscVar3 >= 0x80) {
                        miscVar3 -= 0x80;
                        CreateEntityFromEntity(
                            E_EQUIP_ITEM_DROP, entity, otherEntity);
                    } else {
                        CreateEntityFromEntity(
                            E_PRIZE_DROP, entity, otherEntity);
                    }
                    otherEntity->ext.equipItemDrop.castleFlag = miscVar1;
                    otherEntity->params = miscVar3;
                    // item pops up in the air a bit when spawned
                    otherEntity->velocityY = FIX(-3.5);
                }
            }
        }
        otherEntity = entityHit;
        do {
            otherEntity->flags |=
                (FLAG_UNK_100000 | FLAG_UNK_8000 | FLAG_UNK_4000 | FLAG_DEAD);
            otherEntity->flags &= ~FLAG_UNK_20000000;
            if (!otherEntity->hitEffect) {
                otherEntity->hitEffect = otherEntity->palette;
            }
            otherEntity->nFramesInvincibility = miscVar2;
            otherEntity->flags |= 0xF;
            otherEntity = otherEntity->nextPart;
        } while (otherEntity != NULL && otherEntity != entityHit);
        continue;
    // this spot is unusual because of where it appears in the code. I
    // would have expected this to be included in the spot with the
    // goto, since there is no way to reach this without using that one
    // single goto.
    unusual_spot:
        if ((entityHit->hitFlags & 0xF) == 0) {
            entityHit->hitFlags |= 0x10;
        }
        if ((entityHit->flags & FLAG_UNK_10) && iterEnt->attack) {
            if (iterEnt->hitEffect & 0x80) {
                g_api.PlaySfx(SFX_METAL_CLANG_E);
            } else {
                g_api.PlaySfx(SFX_METAL_CLANG_E);
            }
        }
        otherEntity = entityHit;
        miscVar3 = iterEnt->enemyId;
        do {
            if (entity->hitPoints == 0x7FFF) {
                if (otherEntity->hitPoints == 0x7FFF) {
                    otherEntity->unk6D[miscVar3] =
                        iterEnt->nFramesInvincibility;
                    if (entityHit < otherEntity) {
                        otherEntity->unk6D[miscVar3]++;
                    }
                }
            } else {
                otherEntity->unk6D[miscVar3] = iterEnt->nFramesInvincibility;
                if (entityHit < otherEntity) {
                    otherEntity->unk6D[miscVar3]++;
                }
            }
            otherEntity = otherEntity->nextPart;
        } while (otherEntity != NULL && otherEntity != entityHit);
    }
    prim = &g_PrimBuf[g_unkGraphicsStruct.D_800973F8];
    while (prim != NULL) {
        if (prim->drawMode != DRAW_HIDE) {
            miscVar2 = prim->p1;
            prim->u0 = prim->u2 = g_testColluCoords[miscVar2];
            prim->u1 = prim->u3 = prim->u0 + 0x20;
            prim->v0 = prim->v1 = g_testCollvCoords[miscVar2];
            prim->v2 = prim->v3 = prim->v0 + 0x20;
            miscVar2++;
            if (miscVar2 > 6) {
                prim->drawMode = DRAW_HIDE;
            } else {
                prim->p1 = miscVar2;
            }
        }
        prim = prim->next;
    }
}

#include "entity_damage_display.h"
