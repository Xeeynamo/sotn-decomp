/*
 * File: 27448.c
 * Overlay: CHI
 * Description: Abandoned Mine
 */

#include "chi.h"

extern u16 g_InitializeData0[];

// D_8018142C
static u16 g_ESoulStealOrbAngles[] = {
    0x0820, 0x0840, 0x0860, 0x0880, 0x08C0, 0x0900, 0x0940, 0x0A00
};

// D_8018143C
static s16 g_ESoulStealOrbSprt[] = {
    0xFFFD, 0xFFFD, 0x0008, 0x0008, 0x00D0, 0x0068, 0x00D8, 0x0070,
    0xFFFD, 0xFFFD, 0x0008, 0x0008, 0x00C8, 0x0068, 0x00D0, 0x0070,
    0xFFF9, 0xFFF9, 0x0010, 0x000F, 0x00C8, 0x0070, 0x00D8, 0x007F,
    0xFFF5, 0xFFF5, 0x0018, 0x0017, 0x0080, 0x0068, 0x0098, 0x007F,
    0xFFF5, 0xFFF5, 0x0018, 0x0017, 0x0098, 0x0068, 0x00B0, 0x007F,
    0xFFF5, 0xFFF5, 0x0018, 0x0017, 0x00B0, 0x0068, 0x00C8, 0x007F
};

// D_8018149C
static u8 g_ESoulStealOrbAnim[] = {
    0x04, 0x02, 0x03, 0x03, 0x03, 0x04, 0x03, 0x05, 0x03, 0x06, 0x03, 0x03, 0x00, 0x00, 0x00, 0x00
};

// [Duplicate]
// func_801A7448: [E_SOUL_STEAL_ORB] EntitySoulStealOrb
#include "../entity_soul_steal_orb.h"

// [Duplicate]
// func_801A77DC: [E_ENEMY_BLOOD] EntityEnemyBlood
#include "../entity_enemy_blood.h"

#if !defined(VERSION_PSP)
// D_801814AC
static u8 D_801814AC[] = {0x40, 0x01, 0xFF, 0x00};
// D_801814B0
static u8 D_801814B0[] = {0x40, 0x02, 0xFF, 0x00};
// D_801814B4
static u8 D_801814B4[] = {0x40, 0x02, 0xFF, 0x00};
// D_801814B8
static u8 D_801814B8[] = {0x40, 0x01, 0xFF, 0x00};
// D_801814BC
static u8 D_801814BC[] = {0x40, 0x03, 0xFF, 0x00};
// D_801814C0
static ObjInit2 D_801814C0[] = {
    {0x0006, 0x01EC, 0x0000, 0x0000, 0x00, 0x10, 0, D_801814AC},
    {0x000C, 0x01EC, 0x0000, 0x0000, 0x00, 0x10, 0, D_801814B4},
    {0x000C, 0x0080, 0x0000, 0x0000, 0x00, 0x10, 0, D_801814B8},
    {0x0006, 0x01EC, 0x0000, 0x0000, 0x00, 0x10, 0, D_801814B0},
    {0x000C, 0x01EC, 0x0000, 0x0000, 0x00, 0x10, 0, D_801814BC},
    {0x000C, 0x0080, 0x0000, 0x0000, 0x00, 0x10, 0, D_801814B8},
};

#else
extern ObjInit2 D_801814C0[];

#endif

extern u16 g_eInitGeneric2[];

// [Duplicate]
// [Need to remove D_######## symbol names before using common include]
// E_ROOM_FOREGROUND
// func_801A7C8C
void EntityRoomForeground(Entity* entity) {
    ObjInit2* objInit = &D_801814C0[entity->params];

    if (!entity->step) {
        InitializeEntity(g_eInitGeneric2);
        entity->animSet = objInit->animSet;
        entity->zPriority = objInit->zPriority;
        entity->unk5A = objInit->unk4.u;
        entity->palette = objInit->palette;
        entity->drawFlags = objInit->drawFlags;
        entity->drawMode = objInit->drawMode;
        if (objInit->unkC != 0) {
            entity->flags = objInit->unkC;
        }
        if (entity->params > 4) {
            entity->drawFlags |= DRAW_COLORS;
            entity->rotZ = 0x800;
        }
    }
    AnimateEntity(objInit->unk10, entity);
}
//TODO: Can't use this include yet, as it still contains D_######## symbol names
//#include "../e_room_fg.h"

// func_801A7D78: BottomCornerText
#include "../bottom_corner_text.h"

// [Move to same file as salem witch]
// func_801A80A8
void SalemWitchTrySpawnShadow()
{
    Entity* entity;

    if (!(g_Timer & 0xF)) {
        entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
        if (entity != NULL) {
            CreateEntityFromEntity(E_SALEM_WITCH, g_CurrentEntity, entity);
            entity->facingLeft = g_CurrentEntity->facingLeft;
            entity->zPriority = g_CurrentEntity->zPriority - 1;
            entity->params = g_CurrentEntity->animCurFrame;
            entity->step = 0x20;    // Shadow_Init
        }
    }
}