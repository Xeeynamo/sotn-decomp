#include "game.h"
#include "rwrp.h"

extern u16 D_801804B8[];
extern u32 D_80180648;

#define SE_WARP_DEBRIS 0x644

INCLUDE_ASM("st/rwrp/nonmatchings/rwrp/warp", EntityRWarpRoom);

void EntityWarpSmallRocks(Entity* entity) {
    s32 x;
    s32 y;
    s32 rotation;
    s16 angle;

    switch (entity->step) {
    case 0:
        InitializeEntity(D_801804B8);
        entity->drawFlags = FLAG_DRAW_ROTZ;
        entity->rotZ = Random() * 0x10;
        entity->animCurFrame = (Random() % 5) + 1;
        if (D_80180648) {
            entity->posY.i.hi = (Random() & 0x1F) + 0x90;
            entity->step = 4;
            break;
        }
    case 1:
        if (D_80180648) {
            entity->ext.warpRoom.unk88 = Random() & 0x3F;
            entity->velocityY = FIX(-4);
            entity->step++;
        }
        break;
    case 2:
        if (entity->ext.warpRoom.unk88) {
            entity->ext.warpRoom.unk88--;
        } else {
            MoveEntity();
            entity->velocityY += FIX(0.25);
            if (entity->velocityY > FIX(-1.0f)) {
                entity->drawFlags = FLAG_DRAW_ROTX | FLAG_DRAW_ROTY;
                entity->rotX = entity->rotY = 0x100;
                entity->step++;
            }
        }
        break;
    case 3:
        x = 0x80 - entity->posX.i.hi;
        y = 0x80 - entity->posY.i.hi;
        angle = ratan2(y, x);
        entity->velocityX = rcos(angle) << 5;
        entity->velocityY = rsin(angle) << 5;
        MoveEntity();
        rotation = x * x + y * y;
        rotation = SquareRoot0(rotation);
        rotation *= 2;
        if (rotation > 0x100) {
            rotation = 0x100;
        }
        entity->rotX = entity->rotY = rotation;
        if (rotation < 8) {
            DestroyEntity(entity);
        }
        break;
    case 4:
        angle = entity->rotZ += 0x20;
        entity->velocityY = rsin(angle) * 4;
        if (D_80180648 == 0) {
            entity->ext.warpRoom.unk88 = 0x10;
            entity->step++;
        }
        break;
    case 5:
        if (--entity->ext.warpRoom.unk88 == 0) {
            func_801916C4(SE_WARP_DEBRIS);
        }
        MoveEntity();
        entity->velocityY += FIX(0.1875);
        y = entity->posY.i.hi + g_Tilemap.scrollY.i.hi + 5;
        if (y > 208) {
            entity->posY.i.hi = 203 - g_Tilemap.scrollY.i.hi;
            entity->step = 1;
        }
        break;
    }
}
