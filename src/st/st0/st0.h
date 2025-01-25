// SPDX-License-Identifier: AGPL-3.0-or-later
#include "stage.h"

#undef STAGE
#define STAGE STAGE_ST0

#define OVL_EXPORT(x) ST0_##x

typedef enum EntityIDs {
    E_NONE,
    E_BREAKABLE,
    E_EXPLOSION,
    E_PRIZE_DROP,
    E_NUMERIC_DAMAGE,
    E_RED_DOOR,
    E_INTENSE_EXPLOSION,
    E_SOUL_STEAL_ORB,
    E_ROOM_FOREGROUND,
    E_DUMMY_09,
    E_EQUIP_ITEM_DROP,
    E_DUMMY_0B,
    E_DUMMY_0C,
    E_DUMMY_0D,
    E_DUMMY_0E,
    E_DUMMY_0F,
    E_DUMMY_10,
    E_ID_14 = 0x14,
    E_GREY_PUFF,
    E_DRACULA_UNK1B = 0x1B,
    E_DRACULA_UNK1C,
    E_DRACULA_UNK1D,
    E_DRACULA_METEOR,
    E_DRACULA_UNK1F,
    E_DRACULA_UNK20,
    E_DRACULA_UNK21,
    E_DRACULA_FIREBALL,
    E_DRACULA_UNK23,
    E_ID_24,
    E_ID_26 = 0x26,
    E_SECRET_BUTTON = 0x28,
    E_SECRET_STAIRS,
    E_DRACULA_UNK2B = 0x2B,
    E_DRACULA_UNK2C,
    E_ID_2D,
    E_DRACULA_UNK2E,
} EntityIDs;

void MoveEntity();
void SetStep(u8);
void EntityExplosion(Entity*);
void EntityExplosionVariants(Entity* entity);
void EntityGreyPuff(Entity* entity);

extern EInit OVL_EXPORT(EInitBreakable);
extern EInit g_EInitParticle;
extern EInit g_EInitCutscene;
extern EInit g_EInitCommon;
extern EInit g_EInit3DObject;
extern EInit g_EInitDracula;
extern EInit g_EInitDraculaFireball;
extern EInit g_EInitDraculaFinalForm;
extern EInit g_EInitDraculaMegaFireball;
extern EInit g_EInitSecretStairs;

extern Point32 D_801BEB64[];
extern s32 D_801C2578;
extern u16 g_EInitObtainable[];
