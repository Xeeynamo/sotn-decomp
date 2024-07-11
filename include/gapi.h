#ifndef GAPI_H
#define GAPI_H

#include "types.h"

#include "collider.h"
#include "entity.h"
#include "item.h"
#include "memcard.h"
#include "primitive.h"
#include "relic.h"
#include "stageoverlay.h"
#include "timeattack.h"
#include "unkstruct.h"

typedef struct {
    s8 unk0; // Entity::unk10
    s8 unk2; // Entity::unk12
    s8 hitboxWidth;
    s8 hitboxHeight;
} FrameProperty;

typedef struct {
    /* 0x00 */ const char* name;
    /* 0x04 */ s16 hitPoints;
    /* 0x06 */ s16 attack;
    /* 0x08 */ u16 attackElement;
    /* 0x0A */ s16 defense;
    /* 0x0C */ u16 hitboxState;
    /* 0x0E */ u16 weaknesses;
    /* 0x10 */ u16 strengths;
    /* 0x12 */ u16 immunes;
    /* 0x14 */ u16 absorbs;
    /* 0x16 */ u16 level;
    /* 0x18 */ u16 exp;
    /* 0x1A */ u16 rareItemId;
    /* 0x1C */ u16 uncommonItemId;
    /* 0x1E */ u16 rareItemDropRate;
    /* 0x20 */ u16 uncommonItemDropRate;
    /* 0x22 */ u8 hitboxWidth;
    /* 0x23 */ u8 hitboxHeight;
    /* 0x24 */ s32 flags;
} EnemyDef; /* size=0x28 */

typedef struct {
    /* 0x00 */ s16 attack;
    /* 0x02 */ s16 heartCost;
    /* 0x04 */ u16 attackElement;
    /* 0x06 */ u8 unk6;
    /* 0x07 */ u8 nFramesInvincibility;
    /* 0x08 */ u16 stunFrames;
    /* 0x0A */ u8 anim;
    /* 0x0B */ u8 blueprintNum; // Blueprint for entity factory spawning subwpn
    /* 0x0C */ u16 hitboxState;
    /* 0x0E */ u16 hitEffect;
    /* 0x10 */ u8 crashId; // the ID for the crash version of this subweapon
    /* 0x11 */ u8 unk11;
    /* 0x12 */ u16 entityRoomIndex;
} SubweaponDef; /* size=0x14 */

// Defines the equipment that can be set on left and right hand
// This includes weapons, throw weapons, consumable and restoration items.
// g_EquipDefs it is assumed the equip data starts from here
// https://github.com/3snowp7im/SotN-Randomizer/blob/master/src/stats.js
typedef struct {
    /* 0x00 */ const char* name;
    /* 0x04 */ const char* description;
    /* 0x08 */ s16 attack;
    /* 0x0A */ s16 defense;
    /* 0x0C */ u16 element;
    /* 0x0E */ u8 itemCategory;
    /* 0x0F */ u8 weaponId;
    /* 0x10 */ u8 palette;
    /* 0x11 */ u8 unk11;
    /* 0x12 */ u8 playerAnim;
    /* 0x13 */ u8 unk13;
    /* 0x14 */ u8 unk14;
    /* 0x15 */ u8 lockDuration;
    /* 0x16 */ u8 chainLimit;
    /* 0x17 */ u8 unk17;
    /* 0x18 */ u8 specialMove;
    /* 0x19 */ u8 isConsumable;
    /* 0x1A */ u8 enemyInvincibilityFrames;
    /* 0x1B */ u8 unk1B;
    /* 0x1C */ u32 comboSub;
    /* 0x20 */ u32 comboMain;
    /* 0x24 */ u16 mpUsage;
    /* 0x26 */ u16 stunFrames;
    /* 0x28 */ u16 hitType;
    /* 0x2A */ u16 hitEffect;
    /* 0x2C */ u16 icon;
    /* 0x2E */ u16 iconPalette;
    /* 0x30 */ u16 criticalRate;
    /* 0x32 */ u16 unk32;
} Equipment; /* size=0x34 */

// Defines armor, cloak and rings
typedef struct {
    /* 00 */ const char* name;
    /* 04 */ const char* description;
    /* 08 */ s16 attBonus;
    /* 0A */ s16 defBonus;
    /* 0C */ u8 statsBonus[4];
    /* 10 */ u16 unk10;
    /* 10 */ u16 unk12;
    /* 14 */ u16 unk14;
    /* 10 */ u16 unk16;
    /* 18 */ u16 icon;
    /* 1A */ u16 iconPalette;
    /* 1C */ u16 equipType;
    /* 1E */ u16 unk1E;
} Accessory; /* size=0x20 */

typedef struct {
    u32 effects; // Curse, poison, etc; needs an enum.
    u32 damageKind;
    s32 damageTaken;
    s32 unkC;
} DamageParam;

typedef struct {
    /* 8003C774 */ Overlay o;
    /* 8003C7B4 */ void (*FreePrimitives)(s32);
    /* 8003C7B8 */ s16 (*AllocPrimitives)(PrimitiveType type, s32 count);
    /* 8003C7BC */ void (*CheckCollision)(s32 x, s32 y, Collider* res, s32 unk);
    /* 8003C7C0 */ void (*func_80102CD8)(s32 arg0);
    /* 8003C7C4 */ void (*UpdateAnim)(
        FrameProperty* frameProps, AnimationFrame** anims);
    /* 8003C7C8 */ void (*SetSpeedX)(s32 value);
    /* 8003C7CC */ Entity* (*GetFreeEntity)(s16 start, s16 end);
    /* 8003C7D0 */ void (*GetEquipProperties)(
        s32 handId, Equipment* res, s32 equipId);
    /* 8003C7D4 */ s32 (*func_800EA5E4)(u32);
    /* 8003C7D8 */ void (*LoadGfxAsync)(s32 gfxId);
    /* 8003C7DC */ void (*PlaySfx)(s32 sfxId);
    /* 8003C7E0 */ s16 (*func_800EDB58)(s32, s32);
    /* 8003C7E4 */ void (*func_800EA538)(s32 arg0);
    /* 8003C7E8 */ void (*g_pfn_800EA5AC)(u16 arg0, u8 arg1, u8 arg2, u8 arg3);
    /* 8003C7EC */ void (*func_801027C4)(u32 arg0);
    /* 8003C7F0 */ void (*func_800EB758)(
        s16 pivotX, s16 pivotY, Entity* e, u16 flags, POLY_GT4* p, u8 flipX);
    /* 8003C7F4 */ Entity* (*CreateEntFactoryFromEntity)(
        Entity* self, u32 flags, s32 arg2);
    /* 8003C7F8 */ bool (*func_80131F68)(void);
    /* 8003C7FC */ DR_ENV* (*func_800EDB08)(POLY_GT4* poly);
    /* 8003C800 */ u16* (*func_80106A28)(u32 arg0, u16 kind);
    /* 8003C804 */ void (*func_80118894)(Entity*);
    /* 8003C808 */ EnemyDef* enemyDefs;
    /* 8003C80C */ Entity* (*func_80118970)(void);
    // Note type of facingLeft is different from in the C for this function.
    // Needs s16 to match the code for this, but callers treat it as s32.
    /* 8003C810 */ s16 (*func_80118B18)(
        Entity* ent1, Entity* ent2, s32 facingLeft);
    /* 8003C814 */ s32 (*UpdateUnarmedAnim)(s8* frameProps, u16** frames);
    /* 8003C818 */ void (*PlayAnimation)(s8*, AnimationFrame** frames);
    /* 8003C81C */ void (*func_80118C28)(s32 arg0);
    /* 8003C820 */ void (*func_8010E168)(s32 arg0, s16 arg1);
    /* 8003C824 */ void (*func_8010DFF0)(s32 arg0, s32 arg1);
    /* 8003C828 */ u16 (*DealDamage)(
        Entity* enemyEntity, Entity* attackerEntity);
    /* 8003C82C */ void (*LoadEquipIcon)(s32 equipIcon, s32 palette, s32 index);
    /* 8003C830 */ Equipment* equipDefs;
    /* 8003C834 */ Accessory* accessoryDefs;
    /* 8003C838 */ void (*AddHearts)(s32 value);
    /* 8003C83C */ bool (*LoadMonsterLibrarianPreview)(s32 monsterId);
    /* 8003C840 */ s32 (*TimeAttackController)(
        TimeAttackEvents eventId, TimeAttackActions action);
    /* 8003C844 */ void* (*func_8010E0A8)(void);
    /* 8003C848 */ void (*func_800FE044)(s32, s32);
    /* 8003C84C */ void (*AddToInventory)(u16 id, EquipKind kind);
    /* 8003C850 */ RelicOrb* relicDefs;
    /* 8003C854 */ void (*InitStatsAndGear)(bool debugMode);
    /* 8003C858 */ s32 (*func_80134714)(s32 arg0, s32 arg1, s32 arg2);
    /* 8003C85C */ s32 (*func_80134678)(s16 arg0, u16 arg1);
    /* 8003C860 */ void (*func_800F53A4)(void);
    /* 8003C864 */ u32 (*CheckEquipmentItemCount)(u32 itemId, u32 equipType);
    /* 8003C868 */ void (*func_8010BF64)(Unkstruct_8010BF64* arg0);
    /* 8003C86C */ void (*func_800F1FC4)(s32 arg0);
    /* 8003C870 */ void (*func_800F2288)(s32 arg0);
    /* 8003C874 */ void (*func_8011A3AC)(
        Entity* entity, s32 spellId, s32 arg2, FamiliarStats* out);
    /* 8003C878 */ s32 (*func_800FF460)(s32 arg0);
    /* 8003C87C */ s32 (*func_800FF494)(EnemyDef* arg0);
    /* 8003C880 */ bool (*CdSoundCommandQueueEmpty)(void);
    /* 8003C884 */ bool (*func_80133950)(void);
    /* 8003C888 */ bool (*func_800F27F4)(s32 arg0);
    /* 8003C88C */ s32 (*func_800FF110)(s32 arg0);
    /* 8003C890 */ s32 (*func_800FD664)(s32 arg0);
    /* 8003C894 */ s32 (*func_800FD5BC)(DamageParam* arg0);
    /* 8003C898 */ void (*LearnSpell)(s32 spellId);
    /* 8003C89C */ void (*DebugInputWait)(const char* str);
    /* 8003C8A0 */ void* unused12C;
    /* 8003C8A4 */ void* unused130;
    // this matches on both versions but doing this to show the difference
#if defined(VERSION_PSP)
    /* 8003C8A8 */ u16* (*func_ptr_91CF86C)(u32 arg0, u16 kind);
    /* 8003C8AC */ u16 (*func_ptr_91CF870)(char*, u8* ch);
#else
    /* 8003C8A8 */ void* unused134;
    /* 8003C8AC */ void* unused138;
#endif
    /* 8003C8B4 */ void* unused13C;
} GameApi; /* size=0x140 */

extern GameApi g_api;

/**** Helper signatures ****/
extern void (*g_api_FreePrimitives)(s32);
extern s16 (*g_api_AllocPrimitives)(PrimitiveType type, s32 count);
extern void (*g_api_CheckCollision)(s32 x, s32 y, Collider* res, s32 unk);
extern void (*g_api_func_80102CD8)(s32 arg0);
extern void (*g_api_UpdateAnim)(FrameProperty* frameProps, s32* arg1);
extern void (*g_api_SetSpeedX)(s32 value);
extern Entity* (*g_api_GetFreeEntity)(s16 start, s16 end);
extern void (*g_api_GetEquipProperties)(
    s32 handId, Equipment* res, s32 equipId);
extern s32 (*g_api_func_800EA5E4)(u32);
extern void (*g_api_LoadGfxAsync)(s32);
extern void (*g_api_PlaySfx)(s32 sfxId);
extern s16 (*g_api_func_800EDB58)(s32, s32);
extern void (*g_api_func_800EA538)(s32 arg0);
extern void (*g_api_g_pfn_800EA5AC)(u16 arg0, u8 arg1, u8 arg2, u8 arg3);
extern Entity* (*g_api_CreateEntFactoryFromEntity)(
    Entity* self, u32 flags, s32 arg2);
extern bool (*g_api_func_80131F68)(void);
extern DR_ENV* (*g_api_func_800EDB08)(POLY_GT4* poly);
extern u16* (*g_api_func_80106A28)(u16 arg0, u16 kind);
extern void (*g_api_func_80118894)(Entity*);
extern EnemyDef* g_api_enemyDefs;
extern u32 (*g_api_UpdateUnarmedAnim)(s8* frameProps, u16** frames);
extern void (*g_api_PlayAnimation)(s8*, AnimationFrame** frames);
extern void (*g_api_func_8010E168)(s32 arg0, s16 arg1);
extern void (*g_api_func_8010DFF0)(s32 arg0, s32 arg1);
extern u16 (*g_api_DealDamage)(Entity* enemyEntity, Entity* attackerEntity);
extern void (*g_api_LoadEquipIcon)(s32 equipIcon, s32 palette, s32 index);
extern Equipment* g_api_equipDefs;
extern Accessory* g_api_g_AccessoryDefs;
extern void (*g_api_AddHearts)(s32 value);
extern s32 (*g_api_TimeAttackController)(
    TimeAttackEvents eventId, TimeAttackActions action);
extern void* (*g_api_func_8010E0A8)(void);
extern void (*g_api_func_800FE044)(s32, s32);
extern void (*g_api_AddToInventory)(u16 id, EquipKind kind);
extern RelicOrb* g_api_relicDefs;
extern s32 (*g_api_func_80134714)(s32 arg0, s32 arg1, s32 arg2);
extern s32 (*g_api_func_80134678)(s16 arg0, u16 arg1);
extern void (*g_api_func_800F53A4)(void);
extern u32 (*g_api_CheckEquipmentItemCount)(u32 itemId, u32 equipType);
extern void (*g_api_func_8010BF64)(Unkstruct_8010BF64* arg0);
extern void (*g_api_func_800F1FC4)(s32 arg0);
extern void (*g_api_func_800F2288)(s32 arg0);
extern void (*g_api_func_8011A3AC)(
    Entity* entity, s32 spellId, s32 arg2, FamiliarStats* out);
extern s32 (*g_api_func_800FF460)(s32 arg0);
extern s32 (*g_api_func_800FF494)(EnemyDef* arg0);
extern bool (*g_api_CdSoundCommandQueueEmpty)(void);
extern bool (*g_api_func_80133950)(void);
extern bool (*g_api_func_800F27F4)(s32 arg0);
extern s32 (*g_api_func_800FF110)(s32 arg0);
extern s32 (*g_api_func_800FD664)(s32 arg0);
extern s32 (*g_api_func_800FD5BC)(DamageParam* arg0);
extern void (*g_api_LearnSpell)(s32 spellId);
extern void (*g_api_func_800E2438)(const char* str);
/***************************/

#endif // GAPI_H
