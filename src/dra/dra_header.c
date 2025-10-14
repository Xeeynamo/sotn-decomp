// SPDX-License-Identifier: AGPL-3.0-or-later
#include <game.h>

extern EnemyDef g_EnemyDefs[];
extern Equipment g_EquipDefs[];
extern Accessory g_AccessoryDefs[];
extern RelicDesc g_RelicDefs[];

void FreePrimitives(s32 primitiveIndex);
s16 AllocPrimitives(PrimitiveType primType, s32 count);
void CheckCollision(s32 x, s32 y, Collider* res, s32 unk);
void func_80102CD8(s32 start);
u32 UpdateAnim(FrameProperty* frameProps, AnimationFrame** anims);
void SetSpeedX(s32 speed);
Entity* GetFreeEntity(s16 start, s16 end);
void GetEquipProperties(s32 handId, Equipment* res, s32 equipId);
s32 func_800EA5E4(u32 arg0);
void LoadGfxAsync(s32 gfxId);
void PlaySfx(s32 sfxId);
s16 func_800EDB58(u8 primType, s32 count);
void func_800EA538(s32 arg0);
void func_800EA5AC(u32 a, u32 r, u32 g, u32 b);
void func_801027C4(u32 arg0);
void func_800EB758(
    s16 pivotX, s16 pivotY, Entity* e, u16 flags, POLY_GT4* p, u16 flipX);
Entity* CreateEntFactoryFromEntity(Entity* source, u32 flags, s32 arg2);
bool func_80131F68(void);
DR_ENV* func_800EDB08(POLY_GT4* poly);
u16* func_80106A28(u32 arg0, u16 kind);
void func_80118894(Entity* self);
Entity* func_80118970(void);
s16 func_80118B18(Entity* ent1, Entity* ent2, s32 facingLeft);
s32 UpdateUnarmedAnim(s8* frameProps, u16** frames);
void PlayAnimation(s8*, AnimationFrame** frames);
void func_80118C28(s32 arg0);
void func_8010E168(s32 arg0, s16 arg1);
void func_8010DFF0(s32 resetAnims, s32 arg1);
u16 DealDamage(Entity* enemyEntity, Entity* attackerEntity);
void LoadEquipIcon(s32 equipIcon, s32 palette, s32 index);
void AddHearts(s32 value);
bool LoadMonsterLibrarianPreview(s32 monsterId);
s32 TimeAttackController(TimeAttackEvents eventId, TimeAttackActions action);
void ForceAfterImageOn(void);
s32 func_800FE044(s32 amount, s32 type);
void AddToInventory(u32 itemId, EquipKind itemCategory);
void InitStatsAndGear(bool isDeathTakingItems);
s32 PlaySfxVolPan(s32 sfxId, s32 sfxVol, s32 sfxPan);
s32 SetVolumeCommand22_23(s32 vol, s32 distance);
void func_800F53A4(void);
u32 CheckEquipmentItemCount(u32 itemId, u32 equipType);
void GetPlayerSensor(Collider* col);
void RevealSecretPassageAtPlayerPositionOnMap(s32 arg0);
void func_800F2288(s32 arg0);
void GetServantStats(Entity* entity, s32 spellId, s32 arg2, FamiliarStats* out);
s32 func_800FF460(s32 arg0);
s32 func_800FF494(EnemyDef* arg0);
bool CdSoundCommandQueueEmpty(void);
bool func_80133950(void);
bool func_800F27F4(s32 arg0);
s32 GetStatBuffTimer(s32 arg0);
s32 func_800FD664(s32 arg0);
bool CalcPlayerDamage(DamageParam* arg0);
void LearnSpell(s32 spellId);
void DebugInputWait(const char* msg);
#ifdef VERSION_PSP
s32 func_psp_091007E0(s32 baseAttack);
bool CalcPlayerDamageMaria(DamageParam* damageParam);
u16* func_psp_0913FA28(u32 ch, u16 kind);
u16 func_psp_0913F960(char* str, u8* type);
#endif

#ifndef VERSION_PSP
typedef void (*Entrypoint)(void);
void MainGame(void);
Entrypoint g_MainGame = MainGame;
#endif

GameApi g_ApiInit = {
    {},
    FreePrimitives,
    AllocPrimitives,
    CheckCollision,
    func_80102CD8,
    UpdateAnim,
    SetSpeedX,
    GetFreeEntity,
    GetEquipProperties,
    func_800EA5E4,
    LoadGfxAsync,
    PlaySfx,
    func_800EDB58,
    func_800EA538,
    func_800EA5AC,
    func_801027C4,
    func_800EB758,
    CreateEntFactoryFromEntity,
    func_80131F68,
    func_800EDB08,
    func_80106A28,
    func_80118894,
#ifdef VERSION_PSP
    NULL,
#else
    g_EnemyDefs,
#endif
    func_80118970,
    func_80118B18,
    UpdateUnarmedAnim,
    PlayAnimation,
    func_80118C28,
    func_8010E168,
    func_8010DFF0,
    DealDamage,
    LoadEquipIcon,
    g_EquipDefs,
    g_AccessoryDefs,
    AddHearts,
    LoadMonsterLibrarianPreview,
    TimeAttackController,
    ForceAfterImageOn,
    func_800FE044,
    AddToInventory,
    g_RelicDefs,
    InitStatsAndGear,
    PlaySfxVolPan,
    SetVolumeCommand22_23,
    func_800F53A4,
    CheckEquipmentItemCount,
    GetPlayerSensor,
    RevealSecretPassageAtPlayerPositionOnMap,
    func_800F2288,
    GetServantStats,
    func_800FF460,
    func_800FF494,
    CdSoundCommandQueueEmpty,
    func_80133950,
    func_800F27F4,
    GetStatBuffTimer,
    func_800FD664,
    CalcPlayerDamage,
    LearnSpell,
    DebugInputWait,
#ifdef VERSION_PSP
    func_psp_091007E0,
    CalcPlayerDamageMaria,
    func_psp_0913FA28,
    func_psp_0913F960,
#endif
};
