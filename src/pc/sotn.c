#include "pc.h"
#include "dra.h"
#include "dra_bss.h"
#include "servant.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cJSON/cJSON.h>

u16 g_RawVram[VRAM_W * VRAM_H];
GameApi g_ApiInit = {0};
u8 g_DemoRecordingBuffer[DEMO_MAX_LEN];
extern bool g_IsQuitRequested;

ServantDesc D_80170000;

GfxBank* g_FakeGfxBank = NULL;
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
extern u_long* D_800A3BB8[];

FactoryBlueprint g_FactoryBlueprints[0xC0] = {0};
u8 g_BmpCastleMap[0x20000];

#define MAX_SIZE_FOR_COMPRESSED_GFX 8192
u8 D_800C217C[MAX_SIZE_FOR_COMPRESSED_GFX];
u8 D_800C27B0[MAX_SIZE_FOR_COMPRESSED_GFX];
u8 D_800C3560[MAX_SIZE_FOR_COMPRESSED_GFX];
u8 D_800C4864[MAX_SIZE_FOR_COMPRESSED_GFX];
u8 D_800C4A90[MAX_SIZE_FOR_COMPRESSED_GFX];

// list of exposed API
void FreePrimitives(s32 index);
s32 AllocPrimitives(u8 primType, s32 count);
s32 func_800EA5E4(u32);
void LoadGfxAsync(s32 gfxId);
void PlaySfx(s16 sfxId);
void func_800EA538(s32 arg0);
void func_800EA5AC(u16 arg0, u8 arg1, u8 arg2, u8 arg3);
bool func_80131F68(void);
u16* func_80106A28(u32 arg0, u16 kind);
void PlayAnimation(s8* frameProps, AnimationFrame** frames);
void func_8010E168(s32 arg0, s16 arg1);
void func_8010DFF0(s32 arg0, s32 arg1);
void LoadEquipIcon(s32 equipIcon, s32 palette, s32 index);
void AddToInventory(u16 itemId, s32 itemCategory);
u32 func_80134714(s16 sfxId, s32 arg1, u16 arg2);
u32 CheckEquipmentItemCount(u32 itemId, u32 equipType);
void func_800F2288(s32 arg0);
void DebugInputWait(const char* msg);

int g_Frame = 0;
void MyDrawSyncCallback(int mode) {
    DEBUGF("state: %d, game step: %d", g_GameState, g_GameStep);

    // force loaded map to always be visible
    if (g_Tilemap.tileDef) {
        g_Tilemap.flags |= LAYER_SHOW;
    }

    g_Frame++;
}

// called before MainGame
bool InitPlatform(void);
void InitStrings(void);
static void InitAssets(void);
bool InitEquipDefs(const char* jsonContent);
bool InitAccessoryDefs(const char* jsonContent);
void InitRelicDefs(void);
void InitEnemyDefs(void);
void InitSubwpnDefs(void);
bool InitGfxEquipIcons(const struct FileOpenRead* r);
bool InitPalEquipIcons(const struct FileOpenRead* r);
void InitVbVh(void);
static bool InitSfxData(struct FileAsString* file);
static bool InitXaData(struct FileAsString* file);
static bool InitBlueprintData(struct FileAsString* file);

s32 func_800EDB58(u8 primType, s32 count);

extern FactoryBlueprint g_RicFactoryBlueprints[78];

void func_801027C4(u32 arg0);

bool InitGame(void) {
    if (!InitPlatform()) {
        return false;
    }

    // These two are necessary to make HandleTitle working
    GameApi api;
    api.FreePrimitives = FreePrimitives;
    api.AllocPrimitives = AllocPrimitives;
    api.CheckCollision = CheckCollision;
    api.func_80102CD8 = NULL;
    api.UpdateAnim = UpdateAnim;
    api.SetSpeedX = NULL;
    api.GetFreeEntity = NULL;
    api.GetEquipProperties = NULL;
    api.func_800EA5E4 = func_800EA5E4;
    api.LoadGfxAsync = LoadGfxAsync;
    api.PlaySfx = PlaySfx;
    api.func_800EDB58 = func_800EDB58;
    api.func_800EA538 = func_800EA538;
    api.g_pfn_800EA5AC = func_800EA5AC;
    api.func_801027C4 = func_801027C4;
    api.func_800EB758 = NULL;
    api.CreateEntFactoryFromEntity = CreateEntFactoryFromEntity;
    api.func_80131F68 = func_80131F68;
    api.func_800EDB08 = NULL;
    api.func_80106A28 = func_80106A28;
    api.func_80118894 = NULL;
    api.enemyDefs = g_EnemyDefs;
    api.func_80118970 = NULL;
    api.func_80118B18 = NULL;
    api.UpdateUnarmedAnim = NULL;
    api.PlayAnimation = PlayAnimation;
    api.func_80118C28 = NULL;
    api.func_8010E168 = func_8010E168;
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
    api.func_80134714 = func_80134714;
    api.func_80134678 = NULL;
    api.func_800F53A4 = NULL;
    api.CheckEquipmentItemCount = CheckEquipmentItemCount;
    api.func_8010BF64 = NULL;
    api.func_800F1FC4 = NULL;
    api.func_800F2288 = func_800F2288;
    api.func_8011A3AC = func_8011A3AC;
    api.func_800FF460 = NULL;
    api.func_800FF494 = NULL;
    api.CdSoundCommandQueueEmpty = NULL;
    api.func_80133950 = NULL;
    api.func_800F27F4 = NULL;
    api.func_800FF110 = NULL;
    api.func_800FD664 = func_800FD664;
    api.func_800FD5BC = NULL;
    api.LearnSpell = NULL;
    api.DebugInputWait = DebugInputWait;
    api.unused12C = NULL;
    api.unused130 = NULL;
    api.unused134 = NULL;
    api.unused138 = NULL;
    api.unused13C = NULL;
    memset(&g_ApiInit.o, 0, sizeof(Overlay));

    memcpy(&g_ApiInit, &api, sizeof(g_ApiInit));

    InitStrings();
    InitAssets();

    g_DemoPtr = g_DemoRecordingBuffer;

    // forcing g_Vram values while waiting to import the data
    g_Vram.D_800ACD98.x = 0x0380;
    g_Vram.D_800ACD98.y = 0x0180;
    g_Vram.D_800ACD98.w = 0x0010;
    g_Vram.D_800ACD98.h = 0x0001;
    g_Vram.D_800ACDA0.x = 0;
    g_Vram.D_800ACDA0.y = 0;
    g_Vram.D_800ACDA0.w = 0x0200;
    g_Vram.D_800ACDA0.h = 0x0200;
    g_Vram.D_800ACDA8.x = 0;
    g_Vram.D_800ACDA8.y = 0x00F0;
    g_Vram.D_800ACDA8.w = 0x0100;
    g_Vram.D_800ACDA8.h = 0x0010;

    FileOpenRead(InitGfxEquipIcons, "assets/dra/g_GfxEquipIcon.bin", NULL);
    FileOpenRead(InitPalEquipIcons, "assets/dra/g_PalEquipIcon.bin", NULL);
    InitVbVh();

    if (!FileAsString(InitSfxData, "assets/dra/sfx.json", NULL)) {
        ERRORF("failed to init sfx");
        return false;
    }

    if (!FileAsString(InitXaData, "assets/dra/music_xa.json", NULL)) {
        ERRORF("failed to init xa data");
        return false;
    }

    if (!FileAsString(InitBlueprintData, "assets/dra/factory_blueprint.json",
                      g_FactoryBlueprints)) {
        ERRORF("failed to init dra blueprint data");
        return false;
    }

    if (!FileAsString(InitBlueprintData, "assets/ric/factory_blueprint.json",
                      g_RicFactoryBlueprints)) {
        ERRORF("failed to init ric blueprint data");
        return false;
    }

    return true;
}

void ResetPlatform(void);
void ResetGame(void) { ResetPlatform(); }

void InitSotnMenuTable(void);
void InitStrings(void) {
    InitSotnMenuTable();
    for (int i = 0; i < LEN(g_EquipDefs); i++) {
        g_EquipDefs[i].name = AnsiToSotnMenuString(g_EquipDefs[i].name);
    }
    for (int i = 0; i < LEN(g_AccessoryDefs); i++) {
        g_AccessoryDefs[i].name = AnsiToSotnMenuString(g_AccessoryDefs[i].name);
    }
    for (int i = 0; i < LEN(g_MenuStr); i++) {
        g_MenuStr[i] = AnsiToSotnMenuString(g_MenuStr[i]);
    }
    for (int i = 0; i < LEN(g_EnemyDefs); i++) {
        g_EnemyDefs[i].name = AnsiToSotnMenuString(g_EnemyDefs[i].name);
    }
}

static bool ReadCmpGfx(const struct FileOpenRead* f) {
    if (f->length > MAX_SIZE_FOR_COMPRESSED_GFX) {
        ERRORF("file '%s' too big, max size is %d ", f->filename,
               MAX_SIZE_FOR_COMPRESSED_GFX);
        return false;
    }
    fread(f->param, f->length, 1, f->file);
    return true;
}

static void InitAssets() {
    FileOpenRead(ReadCmpGfx, "assets/dra/D_800C217C.bin", D_800C217C);
    FileOpenRead(ReadCmpGfx, "assets/dra/D_800C27B0.bin", D_800C27B0);
    FileOpenRead(ReadCmpGfx, "assets/dra/D_800C3560.bin", D_800C3560);
    FileOpenRead(ReadCmpGfx, "assets/dra/D_800C4864.bin", D_800C4864);
    FileOpenRead(ReadCmpGfx, "assets/dra/D_800C4A90.bin", D_800C4A90);
}

void (*g_VsyncCallback)() = NULL;
int MyVSyncCallback(void (*f)()) { g_VsyncCallback = f; }

int MyVSync(int mode) {
    if (g_VsyncCallback) {
        g_VsyncCallback();
    }
    return 0;
}

int MyClearImage(RECT* rect, u_char r, u_char g, u_char b) {
    u16* vram = g_RawVram;
    vram += rect->x + rect->y * VRAM_W;

    for (int i = 0; i < rect->h; i++) {
        for (int j = 0; j < rect->w; j++) {
            vram[j] = (r >> 3 << 5) | (g >> 3 << 10) | (b >> 3 << 15) | 0x8000;
        }
        vram += VRAM_W;
    }
    return 0;
}

int MyStoreImage(RECT* rect, u_long* p) {
    DEBUGF("(%X, %X, %X, %X): %p", rect->x, rect->y, rect->w, rect->h, p);
    u16* mem = (u16*)p;
    u16* vram = g_RawVram;
    vram += rect->x + rect->y * VRAM_W;

    for (int i = 0; i < rect->h; i++) {
        memcpy(mem, vram, rect->w * 2);
        mem += rect->w;
        vram += VRAM_W;
    }
    return 0;
}

void ReadToArray(const char* filename, char* content, size_t targetlen) {
    int readlen = FileReadToBuf(filename, content, 0, targetlen);
    if (readlen != targetlen) {
        ERRORF(
            "file read for '%s' failed (%d/%d)", filename, readlen, targetlen);
    }
}

bool InitGfxEquipIcons(const struct FileOpenRead* r) {
    size_t n = fread(g_GfxEquipIcon, 1, sizeof(g_GfxEquipIcon), r->file);
    if (n != sizeof(g_GfxEquipIcon)) {
        WARNF("unable to read all bytes: %d/%d", n, sizeof(g_GfxEquipIcon));
    }
    return true;
}

bool InitPalEquipIcons(const struct FileOpenRead* r) {
    size_t n = fread(g_PalEquipIcon, 1, sizeof(g_PalEquipIcon), r->file);
    if (n != sizeof(g_PalEquipIcon)) {
        WARNF("unable to read all bytes: %d/%d", n, sizeof(g_PalEquipIcon));
    }
    return true;
}

void InitVbVh() {
    ReadToArray("assets/dra/vh_0.bin", aPbav, LEN(aPbav));
    ReadToArray("assets/dra/vh_1.bin", aPbav_0, LEN(aPbav_0));
    ReadToArray("assets/dra/vh_2.bin", aPbav_2, LEN(aPbav_2));
    ReadToArray("assets/dra/vh_3.bin", aPbav_1, LEN(aPbav_1));

    ReadToArray("assets/dra/vb_0.bin", D_8013B6A0, LEN(D_8013B6A0));
    ReadToArray("assets/dra/vb_1.bin", D_8017D350, LEN(D_8017D350));
    ReadToArray("assets/dra/vb_2.bin", D_8018B4E0, LEN(D_8018B4E0));
    ReadToArray("assets/dra/vb_3.bin", D_801A9C80, LEN(D_801A9C80));
}

#define DO_ITEM(field_str, jitem, item, to_set)                                \
    {                                                                          \
        cJSON* field = NULL;                                                   \
        field = cJSON_GetObjectItemCaseSensitive(jitem, field_str);            \
                                                                               \
        if (cJSON_IsNumber(field)) {                                           \
            to_set = field->valueint;                                          \
        } else if (cJSON_IsBool(field)) {                                      \
            if (cJSON_IsTrue(field)) {                                         \
                to_set = 1;                                                    \
            } else if (cJSON_IsFalse(field)) {                                 \
                to_set = 0;                                                    \
            } else {                                                           \
                ERRORF("undefined behaviour for %s", field_str);               \
                exit(1);                                                       \
            }                                                                  \
        } else {                                                               \
            ERRORF("Wrong field %s", field_str);                               \
            exit(1);                                                           \
        }                                                                      \
    }

static bool InitSfxData(struct FileAsString* file) {
    cJSON* json = cJSON_Parse(file->content);
    if (!json) {
        ERRORF("failed to parse '%s': %s", file->param, cJSON_GetErrorPtr());
        return false;
    }
    cJSON* array = cJSON_GetObjectItemCaseSensitive(json, "asset_data");
    if (!cJSON_IsArray(array)) {
        cJSON_Delete(json);
        ERRORF("data malformed in '%s'", file->param);
        return false;
    }

    int len = cJSON_GetArraySize(array);
    for (int i = 0; i < len; i++) {
        Unkstruct_800BF554* item = &g_SfxData[i];
        cJSON* jitem = cJSON_GetArrayItem(array, i);
        DO_ITEM("vabid", jitem, item, item->vabid);
        DO_ITEM("prog", jitem, item, item->prog);
        DO_ITEM("note", jitem, item, item->note);
        DO_ITEM("volume", jitem, item, item->volume);
        DO_ITEM("unk4", jitem, item, item->unk4);
        DO_ITEM("tone", jitem, item, item->tone);
        DO_ITEM("unk6", jitem, item, item->unk6);
    }
    cJSON_Delete(json);
    return true;
}

static bool InitXaData(struct FileAsString* file) {
    cJSON* json = cJSON_Parse(file->content);
    if (!json) {
        ERRORF("failed to parse '%s': %s", file->param, cJSON_GetErrorPtr());
        return false;
    }

    cJSON* array = cJSON_GetObjectItemCaseSensitive(json, "asset_data");
    if (!cJSON_IsArray(array)) {
        cJSON_Delete(json);
        ERRORF("data malformed in '%s'", file->param);
        return false;
    }

    int len = cJSON_GetArraySize(array);
    for (int i = 0; i < len; i++) {
        struct XaMusicConfig* item = &g_XaMusicConfigs[i];
        cJSON* jitem = cJSON_GetArrayItem(array, i);
        DO_ITEM("cd_addr", jitem, item, item->cd_addr);
        DO_ITEM("unk228", jitem, item, item->unk228);
        DO_ITEM("filter_file", jitem, item, item->filter_file);
        DO_ITEM("filter_channel_id", jitem, item, item->filter_channel_id);
        DO_ITEM("volume", jitem, item, item->volume);
        DO_ITEM("unk22f", jitem, item, item->unk22f);
        DO_ITEM("unk230", jitem, item, item->unk230);
        // ignore pad for now
    }
    cJSON_Delete(json);
    return true;
}

static bool InitBlueprintData(struct FileAsString* file) {
    cJSON* json = cJSON_Parse(file->content);
    if (!json) {
        ERRORF("failed to parse '%s': %s", file->param, cJSON_GetErrorPtr());
        return false;
    }

    cJSON* array = cJSON_GetObjectItemCaseSensitive(json, "asset_data");
    if (!cJSON_IsArray(array)) {
        cJSON_Delete(json);
        ERRORF("data malformed in '%s'", file->param);
        return false;
    }

    int len = cJSON_GetArraySize(array);

    FactoryBlueprint* blueprints = (FactoryBlueprint*)file->param;

    for (int i = 0; i < len; i++) {
        u32 bits = 0;
        FactoryBlueprint* item = &blueprints[i];
        cJSON* jitem = cJSON_GetArrayItem(array, i);
        DO_ITEM("childId", jitem, item, item->childId);
        DO_ITEM("unk1", jitem, item, item->unk1);
        DO_ITEM("unk3", jitem, item, item->unk3);
        DO_ITEM("unk5", jitem, item, item->unk5);

        cJSON* jUnk2 = cJSON_GetObjectItem(jitem, "unk2");
        DO_ITEM("bottom6", jUnk2, item, item->unk2);
        DO_ITEM("bit6", jUnk2, item, bits);
        item->unk2 |= !!bits << 6;
        DO_ITEM("bit7", jUnk2, item, bits);
        item->unk2 |= !!bits << 7;

        cJSON* jUnk4 = cJSON_GetObjectItem(jitem, "unk4");
        DO_ITEM("bottomHalf", jUnk4, item, item->unk4);
        DO_ITEM("topHalf", jUnk4, item, bits);
        item->unk4 |= bits << 4;
    }
    cJSON_Delete(json);
    return true;
}
