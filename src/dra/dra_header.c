#include <game.h>

typedef void (*Entrypoint)(void);

extern EnemyDef g_EnemyDefs[];
extern Equipment g_EquipDefs[];
extern Accessory g_AccessoryDefs[];
extern RelicDesc g_RelicDefs[];

void MainGame(void);
void FreePrimitives(s32 primitiveIndex);
s32 AllocPrimitives(u8 primType, s32 count);
void CheckCollision(s32 x, s32 y, Collider* res, s32 unk);
void func_80102CD8(s32 start);
u32 UpdateAnim(s8* frameProps, s32* frames);
void SetSpeedX(s32 speed);
Entity* GetFreeEntity(s16 start, s16 end);
void GetEquipProperties(s32 handId, Equipment* res, s32 equipId);
s32 func_800EA5E4(u32 arg0);
void LoadGfxAsync(s32 gfxId);
void PlaySfx(s16 sfxId);
s32 func_800EDB58(u8 primType, s32 count);
void func_800EA538(s32 arg0);
void func_800EA5AC(u16 arg0, u8 arg1, u8 arg2, u8 arg3);
void func_801027C4(u32 arg0);
void func_800EB758(
    s16 pivotX, s16 pivotY, Entity* e, u16 flags, POLY_GT4* p, u8 flipX);
Entity* CreateEntFactoryFromEntity(Entity* source, u32 flags, s16 arg2);
bool func_80131F68(void);
DR_ENV* func_800EDB08(POLY_GT4* poly);
u16* func_80106A28(u32 arg0, u16 kind);
void func_80118894(Entity* self);
Entity* func_80118970(void);
s32 func_80118B18(Entity* ent1, Entity* ent2, s32 arg2);
u32 UpdateUnarmedAnim(s8* frameProps, u16** frames);
void func_8010DBFC(s32*, s32*);
void func_80118C28(s32 arg0);
void func_8010E168(s32 arg0, s16 arg1);
void func_8010DFF0(s32 arg0, s32 arg1);
u16 DealDamage(Entity* enemyEntity, Entity* attackerEntity);
void LoadEquipIcon(s32 equipIcon, s32 palette, s32 index);
void AddHearts(s32 value);
bool LoadMonsterLibrarianPreview(s32 monsterId);
s32 TimeAttackController(TimeAttackEvents eventId, TimeAttackActions action);
void func_8010E0A8(void);
s32 func_800FE044(s32 amount, s32 type);
void AddToInventory(u16 itemId, s32 itemCategory);
void InitStatsAndGear(bool isDeathTakingItems);
u32 func_80134714(s16 sfxId, s32 arg1, u16 arg2);
s32 func_80134678(s16 arg0, u16 arg1);
void func_800F53A4(void);
u32 CheckEquipmentItemCount(u32 itemId, u32 equipType);
void func_8010BF64(Unkstruct_8010BF64* arg0);
void func_800F1FC4(s32 arg0);
void func_800F2288(void); // unknown signature
void func_8011A3AC(Entity* arg0, s32 arg1, s32 arg2, Unkstruct_8011A3AC* arg3);
s32 func_800FF460(s32 arg0);
s32 func_800FF494(EnemyDef* arg0);
bool CdSoundCommandQueueEmpty(void);
bool func_80133950(void);
bool func_800F27F4(s32 arg0);
s32 func_800FF110(s32 arg0);
s32 func_800FD664(s32 arg0);
bool func_800FD5BC(Unkstruct_800FD5BC* arg0);
void LearnSpell(s32 spellId);
void DebugInputWait(const char* msg);

Entrypoint g_MainGame = MainGame;
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
    g_EnemyDefs,
    func_80118970,
    func_80118B18,
    UpdateUnarmedAnim,
    func_8010DBFC,
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
    func_8010E0A8,
    func_800FE044,
    AddToInventory,
    g_RelicDefs,
    InitStatsAndGear,
    func_80134714,
    func_80134678,
    func_800F53A4,
    CheckEquipmentItemCount,
    func_8010BF64,
    func_800F1FC4,
    func_800F2288,
    func_8011A3AC,
    func_800FF460,
    func_800FF494,
    CdSoundCommandQueueEmpty,
    func_80133950,
    func_800F27F4,
    func_800FF110,
    func_800FD664,
    func_800FD5BC,
    LearnSpell,
    DebugInputWait,
};
