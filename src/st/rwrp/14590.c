#include "rwrp.h"

#define g_ESoulStealOrbAngles D_801810A0
#define GetNormalizedAngle func_8018E160
#define g_ESoulStealOrbAnim D_80181110
#define g_ESouldStelOrbSprt D_801810B0
#include "../entity_soul_steal_orb.h"

#include "../entity_enemy_blood.h"

void func_80194DD4(Entity* entity) {
    ObjInit2* objInit = &D_80181134[entity->params];

    if (entity->step == 0) {
        InitializeEntity(D_80180494);
        entity->animSet = objInit->animSet;
        entity->zPriority = objInit->zPriority;
        entity->unk5A = objInit->unk4.s;
        entity->palette = objInit->palette;
        entity->drawFlags = objInit->drawFlags;
        entity->drawMode = objInit->drawMode;
        if (objInit->unkC != 0) {
            entity->flags = objInit->unkC;
        }
        if (entity->params >= 5) {
            entity->rotZ = 0x800;
            entity->drawFlags = (u8)(entity->drawFlags | FLAG_DRAW_ROTZ);
        }
    }
    AnimateEntity(objInit->unk10, entity);
}

INCLUDE_ASM("st/rwrp/nonmatchings/14590", BottomCornerText);
