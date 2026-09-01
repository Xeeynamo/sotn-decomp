// SPDX-License-Identifier: AGPL-3.0-or-later
#ifndef STAGE_02_H
#define STAGE_02_H

// Overlays run on top of the resident zero and game modules.
#include "game.h"

#include "sattypes.h"
#include <saturn_sprite.h>
#include "shared_sprite_banks.h"
#include "inc_asm.h"
#include "stage_data.h"

// E_PRIZE_DROP (3), E_SOUL_STEAL_ORB (7), E_EQUIP_ITEM_DROP (10) and
// E_ENEMY_BLOOD (13) come from game.h.
typedef enum {
    E_NONE,
    E_BREAKABLE,
    E_STAGE_EXPLOSION,
    E_NUMERIC_DAMAGE = 4,
    E_RED_DOOR,
    E_INTENSE_EXPLOSION,
    E_ROOM_FOREGROUND = 8,
    E_STAGE_NAME_POPUP,
    E_RELIC_ORB = 11,
    E_PERSISTENT_ITEM_DROP,
    E_MESSAGE_BOX = 14,
    E_DUMMY_0F,
    E_DUMMY_10,

    E_AXE_KNIGHT_AXE = 0x2A,
    E_BONE_SCIMITAR_PARTS = 0x28,
    E_FIRE = 0x38,
    E_SLOGRA_SPEAR = 0x41,
    E_SLOGRA_SPEAR_PROJECTILE = 0x42,
    E_GAIBON = 0x43,
    E_GAIBON_SMALL_FIREBALL = 0x45,
    E_GAIBON_BIG_FIREBALL = 0x46,
} EntityID;

s16 Random(void);
s32 AnimateEntityWithSpriteData(
    Entity* entity, const u8 frames[], const s16* spriteFrames[]);
Entity* AllocEntity(Entity*, Entity*);
void InitializeEntity(u16 arg0[]);
void PlaySfxPositional(s32 sfxId);
void CreateEntityFromEntity(u16 entityId, Entity* source, Entity* entity);
void SetStep(u8 step);
void PlaySfx(s32 sfxId);
void FreePrimitives(s32 primIndex);
void SyncSpriteObjectPosUnchecked(Entity* self, s16* offset);
void DestroyEntity(Entity* entity);

void func_0600B004(SpriteObject*, s16*);
void MoveEntity(Entity*);
void func_0600FB0C(s32);
SpriteObject* CreateSpriteObject(
    u16 charBase, u16 clutBase, SaturnSpriteImage* images, s32 maxParts);
void SyncSpriteObjectPos(Entity*);

extern SaturnSpriteFrameHeader* entityRedEyeBustData2[22];
extern SaturnSpriteResource entityRedEyeBustData;
extern SaturnSpriteResource g_Stage02TableWithGlobeResource;
extern u8 g_Stage02TableWithGlobeBreakAnim[];
extern u16 D_80180CC4[];
extern SaturnSpriteFrameHeader* g_Stage02TableWithGlobeFrames[19];
extern u16 g_Stage02TableWithGlobeDropParams[];
extern u8 g_Stage02TableWithGlobeIdleAnim[];
extern s16* g_Stage02SpittleBoneFrames[];
extern s16* g_Stage02Entity38Frames[];
extern s16* g_Stage02BoneScimitarFrames[];

/* Declarations moved here by tools/saturn/move_declarations.py */
extern struct SpriteParts g_Stage02Entity37SpriteParts1;
extern struct SpriteParts g_Stage02Entity37SpriteParts0;
extern struct SpriteParts g_Stage02BoneScimitarSpriteParts1;
extern struct SpriteParts g_Stage02BoneScimitarSpriteParts0;
extern struct SpriteParts g_Stage02AxeKnightSpriteParts1;
extern struct SpriteParts g_Stage02AxeKnightSpriteParts0;
extern struct SpriteParts g_Stage02BloodyZombieSpriteParts1;
extern struct SpriteParts g_Stage02BloodyZombieSpriteParts0;
extern struct SpriteParts g_Stage02SkeletonSpriteParts1;
extern struct SpriteParts g_Stage02SkeletonSpriteParts0;
extern struct SpriteParts g_Stage02SpittleBoneSpriteParts1;
extern struct SpriteParts g_Stage02SpittleBoneSpriteParts0;
void func_060DDB80(Entity* self);
void func_060DD8D8(Entity* self);
void func_060DD790(Entity* self);
void func_060DD690(Entity* self);
void func_060DD3E8(Entity* self);
void func_060DD20C(Entity* self);
void func_060DCFA4(Entity* self);
void func_060DCCD4(Entity* self);
void func_060DCA54(Entity* self);
void func_060DC7B4(Entity* self);
void func_060DC510(Entity* self);
void func_060DC4EC(Entity* self);
void EntityRedEyeBust(Entity* self);
void func_060DC040(Entity* self);
extern SaturnSpriteResource g_Stage02SubweaponContainerResource;
void func_060DF664(Entity* self);
void func_060DF52C(Entity* self);
void func_060DF3B8(Entity* self);
void func_060DF264(Entity* self);
void func_060DEE20(Entity* self);
void func_060DE970(Entity* self);
void func_060DE6CC(Entity* self);
void func_060DE348(Entity* self);
void func_060E0B7C(Entity* self);
void func_060E093C(Entity* self);
void func_060E0684(Entity* self);
void func_060E0304(Entity* self);
extern SaturnSpriteResource g_Stage02MariaNpcResource;
void func_060E2420(Entity* self);
void func_060E22FC(Entity* self);
extern char g_Stage02ObtainedText[];
void func_060E43F4(Entity* self);
void func_060E42FC(Entity* self);
void func_060E37C8(Entity* self);
void func_060E32DC(Entity* self);
void func_060E2A80(Entity* self);
void func_060E600C(Entity* self);
void EntityDestructAnim(Entity* self);
void func_060E5DB4(Entity* self);
void func_060E5C4C(Entity* self);
void func_060E5AE4(Entity* self);
void func_060E6628(Entity* self);
void func_060E633C(Entity* self);
void func_060E6C0C(Entity* self);
void func_060E6B00(Entity* self);
extern SaturnSpriteResource g_Stage02BlueFlameTableResource;
void func_060DE178(Entity* self);
void func_060DDF64(Entity* self);
void EntityTableWithGlobe(Entity* self);
void func_060E5410(Entity* self);
void func_060E4908(Entity* self);
extern struct SpriteParts* g_Stage02SpriteBank33[];
void func_060EC888(Entity* self);
void func_060EC730(Entity* self);
void func_060EC278(Entity* self);
extern struct SpriteParts* g_Stage02SpriteBank29[];
void func_060EA058(Entity* self);
void func_060E9828(Entity* self);
extern struct SpriteParts* g_Stage02SpriteBank32[];
void func_060EC030(Entity* self);
void func_060EBEB0(Entity* self);
void func_060EB9EC(Entity* self);
extern struct SpriteParts* g_Stage02SpriteBank31[];
void func_060EB6E4(Entity* self);
void func_060EB5C4(Entity* self);
void func_060EAFAC(Entity* self);
extern struct SpriteParts* g_Stage02SpriteBank30[];
void func_060EACC0(Entity* self);
void func_060EA264(Entity* self);
extern SaturnSpriteResource g_Stage02ElevatorResource;
void func_060DFAE4(Entity* self);
extern SaturnSpriteResource g_Stage02LifeMaxTankResource;
void func_060E0DC8(Entity* self);
void func_060E0F70(Entity* self);
void func_060E7508(Entity* self);
extern struct SpriteParts* g_Stage02SpriteBank28[];
void func_060E92D8(Entity* self);
extern SaturnIndexed4Texture64x16 g_Stage02Entity74Texture1;
extern SaturnIndexed4Texture64x16 g_Stage02Entity74Texture0;
extern SaturnSpriteResource g_Stage02Entity74Resource1;
extern SaturnSpriteResource g_Stage02Entity74Resource0;
extern s16 g_Stage02BoneScimitarFrameData[327];
extern s16 g_Stage02AxeKnightFrameData[1296];
extern s16 g_Stage02BloodyZombieFrameData[915];
extern s16 g_Stage02SkeletonFrameData[367];
extern s16 g_Stage02SpittleBoneFrameData[715];
extern char g_Stage02GoldText5000[];
extern char g_Stage02GoldText2000[];
extern char g_Stage02GoldText1000[];
extern char g_Stage02GoldText700[];
extern char g_Stage02GoldText400[];
extern char g_Stage02GoldText250[];
extern char g_Stage02GoldText100[];
extern char g_Stage02GoldText50[];
extern char g_Stage02GoldText25[];
extern char g_Stage02GoldText1[];
extern LayoutEntity g_Stage02HorizontalLayout52[];
extern LayoutEntity g_Stage02HorizontalLayout51[];
extern LayoutEntity g_Stage02HorizontalLayout50[];
extern LayoutEntity g_Stage02HorizontalLayout49[];
extern LayoutEntity g_Stage02HorizontalLayout48[];
extern LayoutEntity g_Stage02HorizontalLayout24[];
extern LayoutEntity g_Stage02HorizontalLayout23[];
extern LayoutEntity g_Stage02HorizontalLayout22[];
extern LayoutEntity g_Stage02HorizontalLayout21[];
extern LayoutEntity g_Stage02HorizontalLayout20[];
extern LayoutEntity g_Stage02HorizontalLayout19[];
extern LayoutEntity g_Stage02HorizontalLayout18[];
extern LayoutEntity g_Stage02HorizontalLayout17[];
extern LayoutEntity g_Stage02HorizontalLayout16[];
extern LayoutEntity g_Stage02HorizontalLayout15[];
extern LayoutEntity g_Stage02HorizontalLayout14[];
extern LayoutEntity g_Stage02HorizontalLayout13[];
extern LayoutEntity g_Stage02HorizontalLayout12[];
extern LayoutEntity g_Stage02HorizontalLayout11[];
extern LayoutEntity g_Stage02HorizontalLayout10[];
extern LayoutEntity g_Stage02HorizontalLayout09[];
extern LayoutEntity g_Stage02HorizontalLayout08[];
extern LayoutEntity g_Stage02HorizontalLayout07[];
extern LayoutEntity g_Stage02HorizontalLayout06[];
extern LayoutEntity g_Stage02HorizontalLayout05[];
extern LayoutEntity g_Stage02HorizontalLayout03[];
extern LayoutEntity g_Stage02HorizontalLayout02[];
extern LayoutEntity g_Stage02HorizontalLayout01[];
extern LayoutEntity g_Stage02LayoutEmpty[];
extern SaturnSpriteResource g_Stage02SpriteBank17Resource;
extern SaturnSpriteResource g_Stage02ElevatorPaletteResource;
extern SaturnSpriteResource g_Stage02SubweaponContainerPaletteResource;
extern LayoutEntity g_Stage02VerticalLayout52[];
extern LayoutEntity g_Stage02VerticalLayout51[];
extern LayoutEntity g_Stage02VerticalLayout50[];
extern LayoutEntity g_Stage02VerticalLayout49[];
extern LayoutEntity g_Stage02VerticalLayout48[];
extern LayoutEntity g_Stage02VerticalLayout24[];
extern LayoutEntity g_Stage02VerticalLayout23[];
extern LayoutEntity g_Stage02VerticalLayout22[];
extern LayoutEntity g_Stage02VerticalLayout21[];
extern LayoutEntity g_Stage02VerticalLayout20[];
extern LayoutEntity g_Stage02VerticalLayout19[];
extern LayoutEntity g_Stage02VerticalLayout18[];
extern LayoutEntity g_Stage02VerticalLayout17[];
extern LayoutEntity g_Stage02VerticalLayout16[];
extern LayoutEntity g_Stage02VerticalLayout15[];
extern LayoutEntity g_Stage02VerticalLayout14[];
extern LayoutEntity g_Stage02VerticalLayout13[];
extern LayoutEntity g_Stage02VerticalLayout12[];
extern LayoutEntity g_Stage02VerticalLayout11[];
extern LayoutEntity g_Stage02VerticalLayout10[];
extern LayoutEntity g_Stage02VerticalLayout09[];
extern LayoutEntity g_Stage02VerticalLayout08[];
extern LayoutEntity g_Stage02VerticalLayout07[];
extern LayoutEntity g_Stage02VerticalLayout06[];
extern LayoutEntity g_Stage02VerticalLayout05[];
extern LayoutEntity g_Stage02VerticalLayout03[];
extern LayoutEntity g_Stage02VerticalLayout02[];
extern LayoutEntity g_Stage02VerticalLayout01[];
extern LayoutEntity g_Stage02VerticalLayoutEmpty[];
void func_060E8EEC(s32, s32, s32);
void func_060E8E1C(s32, s32);
void func_060E8990(s32, s32, s32);
void func_060E87D0(s32, s32);
void func_060E8350(Entity*);
void SaveDeviceProbe(Entity*);
void func_060E837C(Entity*, s32);
void func_060e8330(void);
void func_060E8DE0(s32, s32, s32);
void func_060E8780(s32, s32, s32, s32);
extern s32 DAT_060F1D90;
extern s32 DAT_060F5088[2];
extern struct Unk DAT_060e2014; // 060F5044h
extern SaturnRoomPriorities g_Stage02RoomPriorities[32];
extern SaturnRoomGraphics g_Stage02RoomGraphics[26];
extern SaturnLayerMapOffsets g_Stage02LayerMapOffsets[26];
extern SaturnLayerCompressedSizes g_Stage02LayerCompressedSizes[26];
extern SaturnRoomHeader g_Stage02Rooms[33];
extern LayoutEntity* g_Stage02LayoutVertical[];
extern LayoutEntity* g_Stage02LayoutHorizontal[];
extern void* g_Stage02SpriteBanks[];
extern EntityEntry* g_Stage02EntityUpdates[78];
/* End moved declarations */

extern s16 g_ExplosionVariantSizes[];
extern s16* g_Stage02BloodyZombieFrames[];
extern u8 DAT_060F3960[];
extern s16 DAT_060F3824[];
extern s16* g_Stage02SkeletonFrames[];
extern u8 DAT_060F4378[];
extern s16 DAT_060F42C0[];

#endif
