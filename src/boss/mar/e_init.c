// SPDX-License-Identifier: AGPL-3.0-or-later
#include <stage.h>

void EntityBreakable(Entity* self);
void EntityExplosion(Entity* self);
void EntityPrizeDrop(Entity* self);
void EntityDamageDisplay(Entity* self);
void EntityRedDoor(Entity* self);
void EntityIntenseExplosion(Entity* self);
void EntitySoulStealOrb(Entity* self);
void EntityRoomForeground(Entity* self);
void EntityStageNamePopup(Entity* self);
void EntityEquipItemDrop(Entity* self);
void EntityRelicOrb(Entity* self);
void EntityHeartDrop(Entity* self);
void EntityEnemyBlood(Entity* self);
void EntityMessageBox(Entity* self);
void EntityDummy(Entity* self);
void EntityDummy(Entity* self);
void func_us_8018AC0C(Entity* self);
void EntityUnkId12(Entity* self);
void EntityUnkId13(Entity* self);
void EntityUnkId14(Entity* self);
void EntityUnkId15(Entity* self);
void EntityClockRoomController(Entity* self);
void EntityClockHands(Entity* self);
void EntityBirdcageDoor(Entity* self);
void EntityStatue(Entity* self);
void EntityStatueGear(Entity* self);
void EntityStoneDoor(Entity* self);
void func_us_80199114(Entity* self);
void EntityDummy(Entity* self);
void EntityMariaCutscene(Entity* self);
void func_us_8018C90C(Entity* self);
void func_us_8018CA94(Entity* self);

PfnEntityUpdate PfnEntityUpdates[] = {
    EntityBreakable,      EntityExplosion,
    EntityPrizeDrop,      EntityDamageDisplay,
    EntityRedDoor,        EntityIntenseExplosion,
    EntitySoulStealOrb,   EntityRoomForeground,
    EntityStageNamePopup, EntityEquipItemDrop,
    EntityRelicOrb,       EntityHeartDrop,
    EntityEnemyBlood,     EntityMessageBox,
    EntityDummy,          EntityDummy,
    func_us_8018AC0C,     EntityUnkId12,
    EntityUnkId13,        EntityUnkId14,
    EntityUnkId15,        EntityClockRoomController,
    EntityClockHands,     EntityBirdcageDoor,
    EntityStatue,         EntityStatueGear,
    EntityStoneDoor,      func_us_80199114,
    EntityDummy,          EntityMariaCutscene,
    func_us_8018C90C,     func_us_8018CA94,
};

u16 g_eBreakableInit[] = {0x0003, 0x0000, 0x0000, 0x0000, 0x0000};
u16 g_InitializeData0[] = {0x0003, 0x0000, 0x0000, 0x0000, 0x0001};
u16 g_InitializeEntityData0[] = {0x0003, 0x0000, 0x0000, 0x0000, 0x0002};
u16 D_80180A60[] = {0x0000, 0x0000, 0x0000, 0x0000, 0x0004};
u16 g_EInitGeneric[] = {0x0000, 0x0000, 0x0000, 0x0000, 0x0005};
u16 g_InitDataEnt13[] = {0x0000, 0x0000, 0x0000, 0x0000, 0x0002};
u16 g_EntityUnkId12Init[] = {0x0000, 0x0000, 0x0000, 0x0000, 0x0001};
u16 g_eInitGeneric2[] = {0x0000, 0x0000, 0x0000, 0x0000, 0x0003};
u16 g_eDamageDisplayInit[] = {0x0000, 0x0000, 0x0000, 0x0000, 0x0003};

static u16 unused[][6] = {
    {0x0000, 0x0000, 0x0000, 0x0000, 0x0133, 0x0000},
    {0x0000, 0x0000, 0x0000, 0x0000, 0x0134, 0x0000},
    {0x0000, 0x0000, 0x0000, 0x0000, 0x0135, 0x0000},
    {0x0000, 0x0000, 0x0000, 0x0000, 0x0136, 0x0000},
    {0x0000, 0x0000, 0x0000, 0x0000, 0x0137, 0x0000},
    {0x0000, 0x0000, 0x0000, 0x0000, 0x0138, 0x0000},
    {0x0000, 0x0000, 0x0000, 0x0000, 0x0139, 0x0000},
    {0x0000, 0x0000, 0x0000, 0x0000, 0x013A, 0x0000},
    {0x0000, 0x0000, 0x0000, 0x0000, 0x013B, 0x0000},
    {0x0000, 0x0000, 0x0000, 0x0000, 0x013C, 0x0000},
    {0x0000, 0x0000, 0x0000, 0x0000, 0x013D, 0x0000},
    {0x0000, 0x0000, 0x0000, 0x0000, 0x013E, 0x0000},
    {0x0000, 0x0000, 0x0000, 0x0000, 0x013F, 0x0000},
    {0x0000, 0x0000, 0x0000, 0x0000, 0x0140, 0x0000},
    {0x0000, 0x0000, 0x0000, 0x0000, 0x0141, 0x0000},
};

static u8 D_us_801804B0[] = {0x40, 0x2F, 0xFF, 0x00};
ObjInit2 D_80180C10[] = {
    {0x8001, 0x007F, 0, 0, 0x0000, 0x00, 0x30, 0x00000000, D_us_801804B0},
};

u16 g_eRedDoorTiles[][8] = {
    {0x0001, 0x0001, 0x0001, 0x0001, 0x0000, 0x0000, 0x0000, 0x0000},
    {0x04FA, 0x04FA, 0x04FA, 0x04FA, 0x0000, 0x0000, 0x0000, 0x0000},
};
