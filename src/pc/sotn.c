#include "pc.h"
#include "dra.h"
#include "servant.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char g_DummyName[] = "DUMMY\xFF";

u16 g_RawVram[VRAM_W * VRAM_H];
GameApi g_ApiInit = {0};
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

int g_Frame = 0;
void MyDrawSyncCallback(int mode) {
    DEBUGF("-------------------- frame %d --------------------", g_Frame);
    DEBUGF("state: %d, game step: %d", g_GameState, g_GameStep);

    g_Frame++;
}

// called before MainGame
bool InitPlatform(void);
void InitStrings(void);
bool InitEquipDefs(const char* jsonContent);
bool InitAccessoryDefs(const char* jsonContent);
void InitRelicDefs(void);
void InitEnemyDefs(void);
void InitSubwpnDefs(void);
void InitVbVh(void);
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
    memset(&g_ApiInit.o, 0, sizeof(Overlay));

    memcpy(&g_ApiInit, &api, sizeof(g_ApiInit));

    D_8017A000.LoadWeaponPalette = WeaponLoadPaletteStub;
    D_8017D000.LoadWeaponPalette = WeaponLoadPaletteStub;

    InitStrings();

    D_80137590 = g_DemoRecordingBuffer;

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

    InitVbVh();

    return true;
}

void ResetPlatform(void);
void ResetGame(void) { ResetPlatform(); }

MyRenderPrimitives();
void RenderPrimitives(void) {
    DEBUGF("dr  :%03x, gt4 :%03x", g_GpuUsage.drawModes, g_GpuUsage.gt4);
    DEBUGF("g4  :%03x, gt3 :%03x", g_GpuUsage.g4, g_GpuUsage.gt3);
    DEBUGF("line:%03x, sp16:%03x", g_GpuUsage.line, g_GpuUsage.sp16);
    DEBUGF("sp  :%03x, tile:%03x", g_GpuUsage.sp, g_GpuUsage.tile);
    DEBUGF("env :%03x, prim :%03x", g_GpuUsage.env, g_GpuUsage.env);
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
bool FileStringify(bool (*cb)(const char* content), const char* path) {
    INFOF("open '%s'", path);
    FILE* f = fopen(path, "rb");
    if (f == NULL) {
        ERRORF("unable to open '%s'", path);
        return false;
    }

    fseek(f, 0, SEEK_END);
    size_t len = ftell(f);
    fseek(f, 0, SEEK_SET);

    void* content = malloc(len + 1);
    if (!content) {
        ERRORF("unable to allocate %d bytes for '%s'", len, path);
        fclose(f);
        return false;
    }

    size_t bytesread = fread(content, 1, len, f);
    if (bytesread != len) {
        ERRORF("unable to read %d bytes for '%s'", len, path);
        fclose(f);
        free(content);
        return false;
    }

    ((char*)content)[len] = '\0';

    bool r = cb(content);
    free(content);
    fclose(f);
    return r;
}
bool FileUseContent(bool (*cb)(void* content), const char* path) {
    INFOF("open '%s'", path);
    FILE* f = fopen(path, "rb");
    if (f == NULL) {
        ERRORF("unable to open '%s'", path);
        return false;
    }

    fseek(f, 0, SEEK_END);
    size_t len = ftell(f);
    fseek(f, 0, SEEK_SET);

    void* content = malloc(len);
    if (!content) {
        ERRORF("unable to allocate %d bytes for '%s'", len, path);
        fclose(f);
        return false;
    }

    size_t bytesread = fread(content, 1, len, f);
    if (bytesread != len) {
        ERRORF("unable to read %d bytes for '%s'", len, path);
        fclose(f);
        free(content);
        return false;
    }

    bool r = cb(content);
    free(content);
    fclose(f);
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

int MyLoadImage(RECT* rect, u_long* p) {
    DEBUGF("(%X, %X, %X, %X): %p", rect->x, rect->y, rect->w, rect->h, p);
    u16* mem = (u16*)p;
    u16* vram = g_RawVram;
    vram += rect->x + rect->y * VRAM_W;

    for (int i = 0; i < rect->h; i++) {
        for (int j = 0; j < rect->w; j++) {
            vram[j] = *mem++;
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
        for (int j = 0; j < rect->w; j++) {
            *mem++ = vram[j];
        }
        vram += VRAM_W;
    }
    return 0;
}

void ReadToArray(const char* path, char* content) {
    INFOF("open '%s'", path);
    FILE* f = fopen(path, "rb");
    if (f == NULL) {
        ERRORF("unable to open '%s'", path);
        exit(0);
    }

    fseek(f, 0, SEEK_END);
    size_t len = ftell(f);
    fseek(f, 0, SEEK_SET);

    printf("len %d\n", len);

    size_t bytesread = fread(content, 1, len, f);
    if (bytesread != len) {
        ERRORF("unable to read %d bytes for '%s'", len, path);
        fclose(f);
        exit(0);
    }

    fclose(f);
}

void InitVbVh()
{
    ReadToArray("assets/dra/vh_0.bin", aPbav);
    ReadToArray("assets/dra/vh_1.bin", aPbav_0);
    ReadToArray("assets/dra/vh_2.bin", aPbav_2);
    ReadToArray("assets/dra/vh_3.bin", aPbav_1);

    ReadToArray("assets/dra/vb_0.bin", D_8013B6A0);
    ReadToArray("assets/dra/vb_1.bin", D_8017D350);
    ReadToArray("assets/dra/vb_2.bin", D_8018B4E0);
    ReadToArray("assets/dra/vb_3.bin", D_801A9C80);
}
