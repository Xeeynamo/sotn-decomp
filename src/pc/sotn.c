#include "pc.h"
#include "dra.h"
#include "servant.h"
#include "sfx.h"
#ifdef _MSC_VER
#include <SDL.h>
#else
#include <SDL2/SDL.h>
#endif
#include <cJSON/cJSON.h>

#include <stdio.h>

const char g_DummyName[] = "DUMMY\xFF";
const char g_DummyDesc[] = "dummy description";
RelicDesc g_RelicDummy = {g_DummyName, g_DummyDesc, 0, 0, 0};

GameApi g_ApiInit = {0};
Equipment g_EquipDefs[0x100] = {0};
Accessory g_AccessoryDefs[0x100] = {0};
RelicDesc g_RelicDefs[NUM_RELICS] = {0};
SpellDef g_SpellDefs[0x100] = {0};
SubweaponDef g_SubwpnDefs[0x10] = {0};
EnemyDef g_EnemyDefs[0x100] = {0};
void (*D_80170000)(s32 arg0); // ServantDesc D_80170000 = {0};
Weapon D_8017A000 = {0};
Weapon D_8017D000 = {0};
u8 g_DemoRecordingBuffer[DEMO_MAX_LEN];
extern bool g_IsQuitRequested;

extern GfxBank g_FakeGfxBank;
GfxBank** g_GfxStageBank[0x40] = {
    &g_FakeGfxBank, &g_FakeGfxBank, &g_FakeGfxBank, &g_FakeGfxBank,
    &g_FakeGfxBank, &g_FakeGfxBank, &g_FakeGfxBank, &g_FakeGfxBank,
    &g_FakeGfxBank, &g_FakeGfxBank, &g_FakeGfxBank, &g_FakeGfxBank,
    &g_FakeGfxBank, &g_FakeGfxBank, &g_FakeGfxBank, &g_FakeGfxBank,
    &g_FakeGfxBank, &g_FakeGfxBank, &g_FakeGfxBank, &g_FakeGfxBank,
    &g_FakeGfxBank, &g_FakeGfxBank, &g_FakeGfxBank, &g_FakeGfxBank,
    &g_FakeGfxBank, &g_FakeGfxBank, &g_FakeGfxBank, &g_FakeGfxBank,
    &g_FakeGfxBank, &g_FakeGfxBank, &g_FakeGfxBank, &g_FakeGfxBank,
    &g_FakeGfxBank, &g_FakeGfxBank, &g_FakeGfxBank, &g_FakeGfxBank,
    &g_FakeGfxBank, &g_FakeGfxBank, &g_FakeGfxBank, &g_FakeGfxBank,
    &g_FakeGfxBank, &g_FakeGfxBank, &g_FakeGfxBank, &g_FakeGfxBank,
    &g_FakeGfxBank, &g_FakeGfxBank, &g_FakeGfxBank, &g_FakeGfxBank,
    &g_FakeGfxBank, &g_FakeGfxBank, &g_FakeGfxBank, &g_FakeGfxBank,
    &g_FakeGfxBank, &g_FakeGfxBank, &g_FakeGfxBank, &g_FakeGfxBank,
    &g_FakeGfxBank, &g_FakeGfxBank, &g_FakeGfxBank, &g_FakeGfxBank,
    &g_FakeGfxBank, &g_FakeGfxBank, &g_FakeGfxBank, &g_FakeGfxBank,
};
extern UnkStructClut* D_800A3BB8[];

void StageOvlCb() {
    SetGameState(Game_NowLoading);
    g_GameStep = NowLoading_2;
}

void WeaponLoadPaletteStub(s32 arg0) { NOT_IMPLEMENTED; }

// list of exposed API
void FreePrimitives(s32 index);
s32 AllocPrimitives(u8 primType, s32 count);
s32 func_800EA5E4(u32);
void LoadGfxAsync(s32 gfxId);
void func_800EA538(s32 arg0);
u16* func_80106A28(u32 arg0, u16 kind);
void func_8010DFF0(s32 arg0, s32 arg1);
void LoadEquipIcon(s32 equipIcon, s32 palette, s32 index);
void AddToInventory(u16 itemId, s32 itemCategory);
u32 CheckEquipmentItemCount(u32 itemId, u32 equipType);
void DebugInputWait(const char* msg);

// stub to the original UpdateGame
void MenuHandle(void);
void func_800F298C() {
    g_PrimBuf[D_8013799C].clut = 1;
    MenuHandle();
    PlaySfx(MU_REQUIEM_FOR_THE_GODS);
}

int g_Frame = 0;
void MyDrawSyncCallback(int mode) {
    DEBUGF("-------------------- frame %d --------------------", g_Frame);
    DEBUGF("state: %d, game step: %d", g_GameState, g_GameStep);

    g_Frame++;
}

// called before MainGame
bool InitPlatform(void);
void InitStrings(void);
bool InitEquipDefs(FILE* f);
bool InitAccessoryDefs(FILE* f);
void InitRelicDefs(void);
void InitEnemyDefs(void);
void InitSubwpnDefs(void);
bool InitGame(void) {
    if (!InitPlatform()) {
        return false;
    }

    // These two are necessary to make HandleTitle working
    GameApi api;
    api.FreePrimitives = FreePrimitives;
    api.AllocPrimitives = AllocPrimitives;
    api.CheckCollision = NULL;
    api.func_80102CD8 = NULL;
    api.UpdateAnim = NULL;
    api.SetSpeedX = NULL;
    api.GetFreeEntity = NULL;
    api.GetEquipProperties = NULL;
    api.func_800EA5E4 = func_800EA5E4;
    api.LoadGfxAsync = LoadGfxAsync;
    api.PlaySfx = NULL;
    api.func_800EDB58 = NULL;
    api.func_800EA538 = func_800EA538;
    api.g_pfn_800EA5AC = NULL;
    api.func_801027C4 = NULL;
    api.func_800EB758 = NULL;
    api.CreateEntFactoryFromEntity = NULL;
    api.func_80131F68 = NULL;
    api.func_800EDB08 = NULL;
    api.func_80106A28 = func_80106A28;
    api.func_80118894 = NULL;
    api.enemyDefs = NULL;
    api.func_80118970 = NULL;
    api.func_80118B18 = NULL;
    api.UpdateUnarmedAnim = NULL;
    api.func_8010DBFC = NULL;
    api.func_80118C28 = NULL;
    api.func_8010E168 = NULL;
    api.func_8010DFF0 = func_8010DFF0;
    api.DealDamage = NULL;
    api.LoadEquipIcon = LoadEquipIcon;
    api.equipDefs = g_EquipDefs;
    api.accessoryDefs = g_AccessoryDefs;
    api.AddHearts = NULL;
    api.LoadMonsterLibrarianPreview = NULL;
    api.TimeAttackController = NULL;
    api.func_8010E0A8 = NULL;
    api.func_800FE044 = NULL;
    api.AddToInventory = AddToInventory;
    api.relicDefs = g_RelicDefs;
    api.InitStatsAndGear = NULL;
    api.func_80134714 = NULL;
    api.func_80134678 = NULL;
    api.func_800F53A4 = NULL;
    api.CheckEquipmentItemCount = CheckEquipmentItemCount;
    api.func_8010BF64 = NULL;
    api.func_800F1FC4 = NULL;
    api.func_800F2288 = NULL;
    api.func_8011A3AC = NULL;
    api.func_800FF460 = NULL;
    api.func_800FF494 = NULL;
    api.CdSoundCommandQueueEmpty = NULL;
    api.func_80133950 = NULL;
    api.func_800F27F4 = NULL;
    api.func_800FF110 = NULL;
    api.func_800FD664 = NULL;
    api.func_800FD5BC = NULL;
    api.LearnSpell = NULL;
    api.DebugInputWait = DebugInputWait;
    api.unused12C = NULL;
    api.unused130 = NULL;
    api.unused134 = NULL;
    api.unused138 = NULL;
    api.unused13C = NULL;
    api.o.Update = NULL;
    api.o.TestCollisions = StageOvlCb;
    api.o.unk08 = NULL;
    api.o.InitRoomEntities = StageOvlCb;
    api.o.rooms = NULL;
    api.o.spriteBanks = NULL;
    api.o.cluts = D_800A3BB8;
    api.o.unk1C = NULL;
    api.o.tileLayers = NULL;
    api.o.gfxBanks = g_GfxStageBank;
    api.o.unk28 = NULL;
    api.o.unk2c = NULL;
    api.o.unk30 = NULL;
    api.o.unk34 = NULL;
    api.o.unk38 = NULL;
    api.o.unk3C = NULL;
    memcpy(&g_ApiInit, &api, sizeof(g_ApiInit));

    D_8017A000.LoadWeaponPalette = WeaponLoadPaletteStub;
    D_8017D000.LoadWeaponPalette = WeaponLoadPaletteStub;

    InitStrings();
    FileRead(InitEquipDefs, "assets/dra/equipment.json");
    FileRead(InitAccessoryDefs, "assets/dra/accessory.json");
    InitRelicDefs();
    InitEnemyDefs();
    InitSubwpnDefs();

    D_80137590 = g_DemoRecordingBuffer;

    return true;
}

void ResetPlatform(void);
void ResetGame(void) { ResetPlatform(); }

MyRenderPrimitives();
void RenderPrimitives(void) {
    INFOF("dr  :%03x, gt4 :%03x", g_GpuUsage.drawModes, g_GpuUsage.gt4);
    INFOF("g4  :%03x, gt3 :%03x", g_GpuUsage.g4, g_GpuUsage.gt3);
    INFOF("line:%03x, sp16:%03x", g_GpuUsage.line, g_GpuUsage.sp16);
    INFOF("sp  :%03x, tile:%03x", g_GpuUsage.sp, g_GpuUsage.tile);
    INFOF("env :%03x, prim :%03x", g_GpuUsage.env, g_GpuUsage.env);
    MyRenderPrimitives();
}

bool FileRead(bool (*cb)(FILE* file), const char* path) {
    INFOF("open '%s'", path);
    FILE* f = fopen(path, "rb");
    if (f == NULL) {
        ERRORF("unable to open '%s'", path);
        return false;
    }

    bool r = cb(f);
    fclose(f);
    return r;
}
bool FileStringify(bool (*cb)(const char* content), FILE* f) {
    fseek(f, 0, SEEK_END);
    size_t len = ftell(f);
    fseek(f, 0, SEEK_SET);

    void* content = malloc(len + 1);
    if (!content) {
        ERRORF("unable to allocate %d bytes", len);
        return false;
    }

    size_t bytesread = fread(content, 1, len, f);
    if (bytesread != len) {
        ERRORF("unable to read %d bytes", len);
        free(content);
        return false;
    }

    ((char*)content)[len] = '\0';

    bool r = cb(content);
    free(content);
    return r;
}
bool FileUseContent(bool (*cb)(void* content), FILE* f) {
    fseek(f, 0, SEEK_END);
    size_t len = ftell(f);
    fseek(f, 0, SEEK_SET);

    void* content = malloc(len);
    if (!content) {
        ERRORF("unable to allocate %d bytes", len);
        return false;
    }

    size_t bytesread = fread(content, 1, len, f);
    if (bytesread != len) {
        ERRORF("unable to read %d bytes", len);
        free(content);
        return false;
    }

    bool r = cb(content);
    free(content);
    return r;
}

char g_MegaMenuStrBuffer[0x1800];
size_t g_MegaMenuStrIndex = 0;
char MyEncodeChar(char ch) {
    if (ch == '\0') {
        return 0xFF;
    }
    if (ch >= ' ' && ch <= 'z') {
        return ch - 0x20;
    }

    return ch;
}
const char* AnsiToSotnMenuString(const char* str) {
    DEBUGF("%s", str);
    size_t end = strlen(str) + 2 + g_MegaMenuStrIndex;
    if (end >= LEN(g_MegaMenuStrBuffer)) {
        ERRORF(
            "buffer full for '%s' (%d/%d)", str, end, LEN(g_MegaMenuStrBuffer));
        return g_DummyName;
    }

    char* start = g_MegaMenuStrBuffer + g_MegaMenuStrIndex;
    char* dst = start;
    for (const char* ch = str; *ch != '\0'; ch++) {
        *dst++ = MyEncodeChar(*ch);
    }
    *dst++ = MyEncodeChar('\0');
    *dst++ = '\0';
    g_MegaMenuStrIndex = end;
    return start;
}

void InitStrings(void) {
    for (int i = 0; i < LEN(g_MenuStr); i++) {
        g_MenuStr[i] = AnsiToSotnMenuString(g_MenuStr[i]);
    }
}

#define JITEM(x) cJSON_GetObjectItemCaseSensitive(jitem, x)
bool ParseEquipDefs(const char* content) {
    INFOF("load");
    cJSON* json = cJSON_Parse(content);
    if (!json) {
        ERRORF("json error: %s", cJSON_GetErrorPtr());
        WARNF("failed to parse, will use dummy data");
        for (int i = 0; i < LEN(g_EquipDefs); i++) {
            Equipment item = {g_DummyName, g_DummyDesc};
            memcpy(&g_EquipDefs[i], &item, sizeof(item));
        }
        return false;
    }

    // from here, assume the JSON is valid and well structured
    cJSON* array = cJSON_GetObjectItemCaseSensitive(json, "asset_data");
    if (cJSON_IsArray(array)) {
        int len = cJSON_GetArraySize(array);
        if (len > LEN(g_EquipDefs)) {
            WARNF("data too big, will truncate (cur: %d, max: %d)", len,
                  LEN(g_EquipDefs));
            len = LEN(g_EquipDefs);
        }
        for (int i = 0; i < len; i++) {
            Equipment* item = &g_EquipDefs[i];
            cJSON* jitem = cJSON_GetArrayItem(array, i);
            item->name = JITEM("name_resolved")->valuestring;
            item->description = JITEM("desc_resolved")->valuestring;
            item->attack = JITEM("attack")->valueint;
            item->defense = JITEM("defense")->valueint;
            item->element = JITEM("element")->valueint;
            item->itemCategory = JITEM("itemCategory")->valueint;
            item->weaponId = JITEM("weaponId")->valueint;
            item->palette = JITEM("palette")->valueint;
            item->unk11 = JITEM("unk11")->valueint;
            item->playerAnim = JITEM("playerAnim")->valueint;
            item->unk13 = JITEM("unk13")->valueint;
            item->unk14 = JITEM("unk14")->valueint;
            item->lockDuration = JITEM("lockDuration")->valueint;
            item->chainLimit = JITEM("chainLimit")->valueint;
            item->unk17 = JITEM("unk17")->valueint;
            item->specialMove = JITEM("specialMove")->valueint;
            item->isConsumable = JITEM("isConsumable")->valueint;
            item->enemyInvincibilityFrames =
                JITEM("enemyInvincibilityFrames")->valueint;
            item->unk1B = JITEM("unk1B")->valueint;
            item->comboSub = JITEM("comboSub")->valueint;
            item->comboMain = JITEM("comboMain")->valueint;
            item->mpUsage = JITEM("mpUsage")->valueint;
            item->stunFrames = JITEM("stunFrames")->valueint;
            item->hitType = JITEM("hitType")->valueint;
            item->hitEffect = JITEM("hitEffect")->valueint;
            item->icon = JITEM("icon")->valueint;
            item->iconPalette = JITEM("iconPalette")->valueint;
            item->criticalRate = JITEM("criticalRate")->valueint;
            item->unk32 = JITEM("unk32")->valueint;
            item->name = AnsiToSotnMenuString(item->name);
        }
    }
    cJSON_Delete(json);
    return true;
}
bool InitEquipDefs(FILE* f) { FileStringify(ParseEquipDefs, f); }
void ParseAccessoryDefs(const char* content) {
    INFOF("load");
    cJSON* json = cJSON_Parse(content);
    if (!json) {
        ERRORF("json error: %s", cJSON_GetErrorPtr());
        WARNF("failed to parse, will use dummy data");
        for (int i = 0; i < LEN(g_AccessoryDefs); i++) {
            Accessory dummy = {0};
            dummy.name = g_RelicDummy.name;
            dummy.description = g_RelicDummy.desc;
            memcpy(&g_AccessoryDefs[i], &dummy, sizeof(dummy));
        }
        return false;
    }

    // from here, assume the JSON is valid and well structured
    cJSON* array = cJSON_GetObjectItemCaseSensitive(json, "asset_data");
    if (cJSON_IsArray(array)) {
        int len = cJSON_GetArraySize(array);
        if (len > LEN(g_AccessoryDefs)) {
            WARNF("data too big, will truncate (cur: %d, max: %d)", len,
                  LEN(g_AccessoryDefs));
            len = LEN(g_AccessoryDefs);
        }
        for (int i = 0; i < len; i++) {
            Accessory* item = &g_AccessoryDefs[i];
            cJSON* jitem = cJSON_GetArrayItem(array, i);
            item->name = JITEM("name_resolved")->valuestring;
            item->description = JITEM("desc_resolved")->valuestring;
            item->attBonus = JITEM("attBonus")->valueint;
            item->defBonus = JITEM("defBonus")->valueint;
            item->statsBonus[0] = JITEM("strBonus")->valueint;
            item->statsBonus[1] = JITEM("conBonus")->valueint;
            item->statsBonus[2] = JITEM("intBonus")->valueint;
            item->statsBonus[3] = JITEM("lckBonus")->valueint;
            item->unk10 = JITEM("unk10")->valueint;
            item->unk14 = JITEM("unk14")->valueint;
            item->icon = JITEM("icon")->valueint;
            item->iconPalette = JITEM("iconPalette")->valueint;
            item->equipType = JITEM("equipType")->valueint;
            item->name = AnsiToSotnMenuString(item->name);
        }
    }
    cJSON_Delete(json);
    return true;
}
bool InitAccessoryDefs(FILE* f) { FileStringify(ParseAccessoryDefs, f); }
void InitRelicDefs(void) {
    for (int i = 0; i < LEN(g_RelicDefs); i++) {
        memcpy(&g_RelicDefs[i], &g_RelicDummy, sizeof(g_RelicDummy));
    }
}
void InitEnemyDefs(void) {
    for (int i = 0; i < LEN(g_EnemyDefs); i++) {
        EnemyDef dummy = {0};
        dummy.name = g_RelicDummy.name;
        memcpy(&g_EnemyDefs[i], &dummy, sizeof(dummy));
    }
}
void InitSubwpnDefs(void) {
    //
}
