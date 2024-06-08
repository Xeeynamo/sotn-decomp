#include "../wrp/wrp.h"

void EntityNumericDamage(Entity*);
void func_80186FD0(Entity*);
void func_801870B0(Entity*);
void EntityUnkId13(Entity*);
void EntityWarpRoom(Entity*);
void EntityWarpSmallRocks(Entity*);

// not sure what to do about *[] vs ** typing issue
PfnEntityUpdate D_psp_09246E30[] = {
    /* 3E4 */ (PfnEntityUpdate)EntityBreakable,
    /* 3E8 */ (PfnEntityUpdate)EntityExplosion,
    /* 3EC */ (PfnEntityUpdate)EntityPrizeDrop,
    /* 3F0 */ (PfnEntityUpdate)EntityNumericDamage, // EntityDamageDisplay
    /* 3F4 */ (PfnEntityUpdate)EntityRedDoor,
    /* 3F8 */ (PfnEntityUpdate)EntityIntenseExplosion,
    /* 3FC */ (PfnEntityUpdate)EntitySoulStealOrb,
    /* 400 */ (PfnEntityUpdate)EntityRoomForeground,
    /* 404 */ (PfnEntityUpdate)EntityStageNamePopup,
    /* 408 */ (PfnEntityUpdate)EntityEquipItemDrop,
    /* 40C */ (PfnEntityUpdate)EntityRelicOrb,
    /* 410 */ (PfnEntityUpdate)EntityHeartDrop,
    /* 414 */ (PfnEntityUpdate)EntityEnemyBlood,
    /* 418 */ (PfnEntityUpdate)EntityMessageBox,
    /* 41C */ (PfnEntityUpdate)EntityDummy,
    /* 420 */ (PfnEntityUpdate)EntityDummy,
    /* 424 */ (PfnEntityUpdate)func_80186FD0, // unused
    /* 428 */ (PfnEntityUpdate)func_801870B0, // unused? looks debugging stuff
    /* 42C */ (PfnEntityUpdate)EntityUnkId13,
    /* 430 */ (PfnEntityUpdate)EntityUnkId14,
    /* 434 */ (PfnEntityUpdate)EntityUnkId15,
    /* 438 */ (PfnEntityUpdate)EntityWarpRoom,
    /* 43C */ (PfnEntityUpdate)EntityWarpSmallRocks,
};
