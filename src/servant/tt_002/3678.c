// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include <servant.h>

extern s32 D_us_801792DC;
extern u16 D_us_801722E8[];
extern Entity thisFamiliar;
extern s32 D_us_801792E0;
extern FamiliarStats s_FaerieStats;
extern s32 D_us_8017931C;
extern s32 D_us_80179320;

INCLUDE_ASM("servant/tt_002/nonmatchings/3678", func_us_801739D0);

// This is a duplicate CreateEventEntity which is lower in the file, but we need
// both to match the binary for PSX
void CreateEventEntity_Dupe(Entity* entityParent, s32 entityId, s32 params) {
    Entity* entity;
    s32 i;

    for (i = 0; i < 3; i++) {
        entity = &g_Entities[5 + i];
        if (!entity->entityId) {
            break;
        }
    }

    if (!entity->entityId) {
        DestroyEntity(entity);
        entity->entityId = entityId;
        entity->zPriority = entityParent->zPriority;
        entity->facingLeft = entityParent->facingLeft;
        entity->flags = FLAG_KEEP_ALIVE_OFFCAMERA;
        entity->posX.val = entityParent->posX.val;
        entity->posY.val = entityParent->posY.val;
        // Not necessarily making batFamBlueTrail here, but
        // that's an Ext that works. Just needs parent at 0x8C.
        entity->ext.batFamBlueTrail.parent = entityParent;
        entity->params = params;
    }
}

INCLUDE_ASM("servant/tt_002/nonmatchings/3678", func_us_80173BD0);

INCLUDE_ASM("servant/tt_002/nonmatchings/3678", func_us_80173D60);

void func_us_801746E8(InitializeMode mode)
{
    u16* src;
    u16* dst;
    RECT rect;
    s32 i;
    SpriteParts** spriteBanks;
    Entity* entity;  

    D_us_801792DC = g_Servant;

    if ((mode == MENU_SWITCH_SERVANT) || (mode == MENU_SAME_SERVANT)) {
        ProcessEvent(NULL, true);
        if (mode == MENU_SAME_SERVANT) {
            return;
        }
    }
    
    dst = &g_Clut[0x1400];
    src = D_us_801722E8;
    for (i = 0; i < 0x100; i++) {
        *dst++ = *src++;
    }

    rect.x = 0;
    rect.w = 0x100;
    rect.h = 1;
    rect.y = 0xF4;

    dst = &g_Clut[0x1400];
    LoadImage(&rect, (u_long*)dst);
    
    spriteBanks = g_api.o.spriteBanks;
    spriteBanks += 20;
    *spriteBanks = (SpriteParts*)g_ServantSpriteParts;

    entity = &thisFamiliar;
    
    DestroyEntity(entity);
    entity->unk5A = 0x6C;
    entity->palette = 0x140;
    entity->animSet = ANIMSET_OVL(20);
    entity->zPriority = PLAYER.zPriority - 2;
    entity->facingLeft = PLAYER.facingLeft;
    entity->params = 0;
    
    if (mode == MENU_SWITCH_SERVANT) {
        if (D_8003C708.flags & 0x20 || D_8003C708.flags & 0x40) {
            entity->entityId = 0xD1;
        } else {
            entity->entityId = 0xD8;
        }
        entity->posX.val = FIX(128);
        entity->posY.val = FIX(-32);
    } else {
        entity->entityId = 0xD1;
        if (D_8003C708.flags & 0x20) {
            if(ServantUnk0())
            {
                entity->posX.val = FIX(192);
            }
            else
            {
               entity->posX.val = FIX(64);
            }
            entity->posY.val = FIX(160);
        } else {
            entity->posX.val = PLAYER.posX.val + (PLAYER.facingLeft ? FIX(24) : FIX(-24));
            entity->posY.val = PLAYER.posY.val + FIX(-32);
        }
    } 
     
    D_us_801792E0 = (s32) entity->zPriority;
    g_api.GetServantStats(entity, 0, 0, &s_FaerieStats);
    // There is a better way to do this, but I don't know what it is
    entity = (Entity*)((int*)entity + 0x2F);
    DestroyEntity(entity);
    entity->entityId = 0xD9;
    entity->unk5A = 0x6C;
    entity->palette = 0x140;
    entity->animSet = -0x7FEC;
    entity->zPriority = PLAYER.zPriority - 3;
    entity->facingLeft = PLAYER.facingLeft;
    entity->params = 0;
    
    D_us_8017931C = 0;
    D_us_80179320 = 0;
    g_api.GetServantStats(entity, 0, 0, &s_FaerieStats);
}

INCLUDE_ASM("servant/tt_002/nonmatchings/3678", func_us_80174998);

INCLUDE_ASM("servant/tt_002/nonmatchings/3678", func_us_80174F0C);

INCLUDE_ASM("servant/tt_002/nonmatchings/3678", func_us_801753E4);

INCLUDE_ASM("servant/tt_002/nonmatchings/3678", func_us_80175730);

INCLUDE_ASM("servant/tt_002/nonmatchings/3678", func_us_80175A78);

INCLUDE_ASM("servant/tt_002/nonmatchings/3678", func_us_80175DBC);

INCLUDE_ASM("servant/tt_002/nonmatchings/3678", func_us_80176178);

INCLUDE_ASM("servant/tt_002/nonmatchings/3678", func_us_80176504);

INCLUDE_ASM("servant/tt_002/nonmatchings/3678", func_us_80176B6C);

INCLUDE_ASM("servant/tt_002/nonmatchings/3678", func_us_80176C98);

INCLUDE_ASM("servant/tt_002/nonmatchings/3678", func_us_80177380);

INCLUDE_ASM("servant/tt_002/nonmatchings/3678", func_us_80177958);

INCLUDE_ASM("servant/tt_002/nonmatchings/3678", func_us_80177AC4);

INCLUDE_ASM("servant/tt_002/nonmatchings/3678", func_us_80177F64);

INCLUDE_ASM("servant/tt_002/nonmatchings/3678", func_us_80177F84);

#ifndef VERSION_PSP
#include "../servant_update_anim.h"
#endif

#include "../../destroy_entity.h"

#ifndef VERSION_PSP
#include "../accumulate_toward_zero.h"
#include "../search_for_entity_in_range.h"
#endif

#include "../calculate_angle_to_entity.h"

#include "../get_target_position_with_distance_buffer.h"

#ifndef VERSION_PSP
#include "../calculate_distance.h"

// There is some .rodata jumptable stuff going on with ProcessSfxState
// where the table is in the middle of the .rodata function
INCLUDE_ASM("servant/tt_002/nonmatchings/3678", func_us_80178A30);
// #include "../play_sfx.h"
#endif

#include "../process_event.h"

#include "../create_event_entity.h"

#include "../is_movement_allowed.h"

#ifndef VERSION_PSP
#include "../check_all_entities_valid.h"
#endif

#include "../servant_unk0.h"

INCLUDE_RODATA("servant/tt_002/nonmatchings/3678", func_us_80173994);

INCLUDE_RODATA("servant/tt_002/nonmatchings/3678", func_us_801739C8);
