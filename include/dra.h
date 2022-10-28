#ifndef DRA_H
#define DRA_H
#include "main.h"

struct Entity;

typedef void (*PfnEntityUpdate)(struct Entity*);
typedef void (*UnkFunctionUpdate1)(struct Entity*, u32, struct Entity*);

typedef struct {
    unsigned char width;
    unsigned char height;
    unsigned short unk2;
    unsigned char data[0];
} ImgSrc;

typedef struct {
    /* 0x00 */ s16 cursorX;
    /* 0x02 */ s16 cursorY;
    /* 0x04 */ s16 unk4;
    /* 0x06 */ s16 unk6;
    /* 0x08 */ RECT unk1;
    /* 0x10 */ int w;
    /* 0x14 */ int unk14;
    /* 0x18 */ s16 unk18;
    /* 0x1A */ s16 unk1A;
    /* 0x1C */ s16 unk1C;
} MenuContext; // size = 0x1E

typedef struct {
    /* 0x0 */ u8 tileLayoutId;
    /* 0x1 */ u8 tilesetId;
    /* 0x2 */ u8 objGfxId;
    /* 0x3 */ u8 objLayoutId;
} RoomLoadDef; // size = 0x4

typedef struct {
    /* 0x0 */ u8 left;
    /* 0x1 */ u8 top;
    /* 0x2 */ u8 right;
    /* 0x3 */ u8 bottom;
    /* 0x4 */ RoomLoadDef load;
} RoomHeader; // size = 0x8

typedef struct {
    /* 0x0 */ s16 pressed;
    /* 0x2 */ s16 previous;
    /* 0x4 */ s16 tapped;
    /* 0x6 */ s16 repeat;
} Pad; // size = 0x8

typedef union { // Big assumption here...
    s32 value;  // size = 0x4
    struct {
        s16 low;
        s16 high;
    } Data; // size = 0x4
    struct {
        u8 unk0;
        u8 unk1;
        s16 unk2;
    } Data1; // size = 0x4

} UnkUnion1; // side = 0x4

typedef union {
    s16 data;
    struct {
        u8 unk0;
        u8 unk1;
    } data1;
} UnkUnion2; // size = 0x2

typedef union {
    u16 modeU16;
    struct {
        u8 unk0;
        u8 unk1;
    } modeU8;
} unkUnion3;

typedef struct {
    /* 0x00 */ UnkUnion1 posX;
    /* 0x04 */ UnkUnion1 posY;
    /* 0x08 */ s32 accelerationX;
    /* 0x0C */ s32 accelerationY;
    /* 0x10 */ s16 unk10;
    /* 0x12 */ s16 unk12;
    /* 0x14 */ u16 unk14;
    /* 0x16 */ s16 palette;
    /* 0x18 */ s8 unk18;
    /* 0x19 */ s8 unk19;
    /* 0x1A */ s16 unk1A;
    /* 0x1C */ s16 unk1C;
    /* 0x1E */ s16 unk1E;
    /* 0x20 */ s16 unk20;
    /* 0x22 */ s16 unk22;
    /* 0x24 */ u16 zPriority;
    /* 0x26 */ u16 objectId;
    /* 0x28 */ PfnEntityUpdate pfnUpdate;
    /* 0x2C */ u16 initState;
    /* 0x2E */ s16 unk2E;
    /* 0x30 */ u16 subId;
    /* 0x32 */ u16 unk32;
    /* 0x34 */ s32 unk34;
    /* 0x38 */ s16 unk38;
    /* 0x3A */ s16 unk3A;
    /* 0x3C */ s16 unk3C;
    /* 0x3E */ s16 unk3E;
    /* 0x40 */ s16 unk40;
    /* 0x42 */ s16 unk42;
    /* 0x44 */ u16 unk44;
    /* 0x46 */ u8 hitboxWidth;
    /* 0x47 */ u8 hitboxHeight;
    /* 0x48 */ u8 unk48;
    /* 0x49 */ u8 unk49;
    /* 0x4A */ s16 unk4A;
    /* 0x4C */ s32* unk4C;
    /* 0x50 */ u16 animationFrameIndex;
    /* 0x52 */ s16 animationFrameDuration;
    /* 0x54 */ s16 animationSet;
    /* 0x56 */ s16 animationFrame;
    /* 0x58 */ s16 unk58;
    /* 0x5A */ s16 unk5A;
    /* 0x5C */ s32 unk5C;
    /* 0x60 */ s32 unk60;
    /* 0x64 */ s32 firstPolygonIndex;
    /* 0x68 */ s16 unk68;
    /* 0x6A */ s16 unk6A;
    /* 0x6C */ u8 unk6C;
    /* 0x6D */ s8 unk6D;
    /* 0x6E */ s16 unk6E;
    /* 0x70 */ s32 unk70;
    /* 0x74 */ s32 unk74;
    /* 0x78 */ s32 unk78;
    /* 0x7C */ unkUnion3 unk7C;
    /* 0x7E */ u8 unk7E;
    /* 0x80 */ UnkUnion2 unk80;
    /* 0x82 */ s16 unk82;
    /* 0x84 */ UnkUnion1 unk84;
    /* 0x88 */ s16 unk88;
    /* 0x8A */ s16 unk8A;
    /* 0x8C */ u16 unk8C;
    /* 0x8E */ u16 unk8E;
    /* 0x90 */ s32 unk90;
    /* 0x94 */ u8 unk94;
    /* 0x95 */ u8 unk95;
    /* 0x96 */ s16 unk96;
    /* 0x98 */ s32 unk98;
    /* 0x9C */ s32 unk9C;
    /* 0xA0 */ s32 unkA0;
    /* 0xA4 */ s32 unkA4;
    /* 0xA8 */ s32 unkA8;
    /* 0xAC */ s32 unkAC;
    /* 0xB0 */ s32 unkB0;
    /* 0xB4 */ s16 unkB4;
    /* 0xB6 */ s16 unk86;
    /* 0xB8 */ UnkFunctionUpdate1 unkFuncB8;
    ///* 0xBA */ u8 unkBA;
    ///* 0xBB */ u8 unkBB;
} Entity; // size = 0xBC

typedef struct playerHeart {
    s32 current;
    s32 max;
} playerHeart;

typedef struct {
    /* 0x0 */ u16 posX;
    /* 0x2 */ u16 posY;
    /* 0x4 */ u16 flags; // maybe misnamed
    /* 0x6 */ u16 unk6;
    /* 0x8 */ u16 unk8;
} ObjectInit; // size = 0xA

typedef struct unkStruct3 {
    /* 0x00 */ struct unkStruct3* unk0;
    /* 0x04 */ char pad4[0x3];
    /* 0x07 */ s8 unk7;
    /* 0x08 */ s16 unk8;
    /* 0x0A */ s16 unkA;
    /* 0x0C */ s16 unkC;
    /* 0x0E */ s16 unkE;
    /* 0x10 */ s16 unk10;
    /* 0x12 */ UnkUnion2 unk12;
    /* 0x14 */ s16 unk14;
    /* 0x16 */ s16 unk16;
    /* 0x18 */ s16 unk18;
    /* 0x1A */ s16 unk1A;
    /* 0x1C */ s16 unk1C;
    /* 0x1E */ UnkUnion2 unk1E;
    /* 0x20 */ s16 unk20;
    /* 0x22 */ s16 unk22;
    /* 0x24 */ s8 unk24;
    /* 0x25 */ s8 unk25;
    /* 0x26 */ char pad26[0x2];
    /* 0x28 */ s8 unk28;
    /* 0x29 */ char pad[0x1];
    /* 0x2A */ s8 unk2A;
    /* 0x2B */ u8 unk2B;
    /* 0x2C */ u16 unk2C;
    /* 0x2E */ char pad2E[4];
    /* 0x32 */ u16 unk32;
} unkStruct3;

typedef struct {
    /* 0x0 */ char pad0[0xA];
    /* 0xA */ s16 unkA;
    /* 0xC */ s16 unkC;
    /* 0xE */ s16 unkE;
} Unkstruct4; // size = 0x10

typedef struct {
    /* 0x00 */ s16 unk0;
    /* 0x02 */ s16 unk2;
    /* 0x04 */ u16 unk4;
    /* 0x06 */ u16 unk6;
    /* 0x08 */ u16 unk8;
    /* 0x0A */ s16 unkA;
    /* 0x0C */ u16 unkC;
    /* 0x0E */ s16 unkE;
    /* 0x10 */ s16 unk10;
    /* 0x12 */ s16 unk12;
    /* 0x14 */ s16 unk14;
    /* 0x16 */ s16 unk16;
    /* 0x18 */ s16 unk18;
    /* 0x1A */ s16 unk1A;
    /* 0x1C */ s16 unk1C;
    /* 0x1E */ s16 unk1E;
    /* 0x20 */ s16 unk20;
    /* 0x22 */ u8 hitboxWidth;
    /* 0x23 */ u8 hitboxHeight;
    /* 0x24 */ s32 unk24;
} Unkstruct5; // size = 0x28

typedef struct {
    /* 0x0 */ s16 x;
    /* 0x2 */ s16 y;
} Unkstruct6; // size = 0x4

typedef struct {
    /* 0x00 */ s32 sp10;
    /* 0x04 */ s32 sp14;
    /* 0x08 */ s32 sp18;
    /* 0x0C */ s32 sp1C;
    /* 0x10 */ s32 sp20;
    /* 0x14 */ s16 sp24;
    /* 0x18 */ s16 sp26;
    /* 0x1C */ s16 sp28;
    /* 0x20 */ s16 sp2A;
    /* 0x24 */ s32 sp2C;
    /* 0x28 */ s32 sp30;
} Unkstruct7; // size = 0x2C

typedef struct {
    /* 0x0 */ void* addr1;
    /* 0x4 */ void* addr2;
    /* 0x8 */ u16 unk8;
    /* 0xA */ u16 unkA;
    /* 0xC */ u16 unkC;
    /* 0xE */ u16 unkE;
} Unkstruct8; // size = 0x10

typedef struct {
    /* 0x00 */ u16 animationSet;
    /* 0x02 */ u16 zPriority;
    /* 0x04 */ UnkUnion2 unk4;
    /* 0x06 */ u16 palette;
    /* 0x08 */ u8 unk8;
    /* 0x09 */ u8 unk9;
    /* 0x0A */ u8 unkA;
    /* 0x0B */ u8 unkB;
    /* 0x0C */ u32 unkC;
    /* 0x10 */ u8* unk10;
} ObjInit2; // size = 0x14

typedef struct {
    /* 0x0 */ u16 programId;
    /* 0x2 */ u16 unk2;
    /* 0x4 */ u16 unk4;
    /* 0x6 */ u16 unk6;
    /* 0x8 */ u16 unk8;
} Unkstruct10; // size = 0xA

typedef struct {
    /* 0x0000 */ char unk_00[0x474];
    /* 0x0474 */ u32 unk_0474[0]; // unk length, unk elem size
    char _unk_0474[0x800];
    /* 0x0C74 */ DR_MODE drawModes[0]; // unk length
    u8 _unk_0C74[0xCC00];
    /* 0xD874 */ POLY_G4 unk_D874[0]; // unk length
} GpuBufferUnk;

typedef enum {
    ENTITY_INITSTATE_0,
    ENTITY_INITSTATE_1,
    ENTITY_INITSTATE_2,
    ENTITY_INITSTATE_3,
    ENTITY_INITSTATE_4,
    ENTITY_INITSTATE_5,
    ENTITY_INITSTATE_6,
    ENTITY_INITSTATE_7
} EntityInitStates;

// main
extern Unkstruct5* D_8003C704;
extern u16 D_8003C708;
extern s32 D_8003C730;
extern s32 D_8003C734;
extern void (*D_8003C744)(s32, s32);
extern void (*g_pfnUpdateStageEntities)(void);
extern RoomHeader* D_8003C784;
extern void (*D_8003C7BC)(s32 posX, s32 posY, Unkstruct7*, s32);
extern void (*g_pfnPlaySfx)(s32);
extern void (*g_pfnFreePolygons)(s32);
extern Unkstruct5* D_8003C808;
extern void (*D_8003C848)(s32, s32);
extern s32 D_8003C8C4;
extern s32 g_roomCount;
extern s32 g_CurrentPlayableCharacter;
extern s32 g_blinkTimer;
extern s32 g_menuMainCursorIndex;
extern s32 g_menuRelicsCursorIndex;
extern s32 g_SettingsCloakMode;
extern s32 g_SettingsSoundMode;
extern s32 D_8003CACC;
extern s16 D_8003CB0E;
extern s16 D_8003CB12;
extern s8 D_8003CB22;
extern s8 D_8003CB24;
extern s8 D_8003CB25;
extern s8 D_8003CB26;
extern s8 D_8003CB27;
extern s8 D_8003CB79;
extern s16 D_80054302;
extern s16 D_80054306;
extern s8 D_80054316;
extern s8 D_80054318;
extern s8 D_80054319;
extern s8 D_8005431A;
extern s8 D_8005431B;
extern s8 D_8005436D;

// dra
#define PAD_COUNT 2
#define PAD_L2 0x0001
#define PAD_R2 0x0002
#define PAD_L1 0x0004
#define PAD_R1 0x0008
#define PAD_TRIANGLE 0x0010
#define PAD_CIRCLE 0x0020
#define PAD_CROSS 0x0040
#define PAD_SQUARE 0x0080
#define PAD_SELECT 0x0100
#define PAD_L3 0x0200
#define PAD_R3 0x0400
#define PAD_START 0x0800
#define PAD_UP 0x1000
#define PAD_RIGHT 0x2000
#define PAD_DOWN 0x4000
#define PAD_LEFT 0x8000

#define RENDERFLAGS_NOSHADOW 2
#define PLAYER_ALUCARD 0
#define PLAYER_RICHTER 1
#define MAX_GOLD 999999
#define HEART_VESSEL_INCREASE 5
#define HEART_VESSEL_RICHTER 30
#define LIFE_VESSEL_INCREASE 5
#define FALL_GRAVITY 0x4000
#define FALL_TERMINAL_VELOCITY 0x60000

#define TOTAL_ENTITY_COUNT 256
#define MaxEntityCount 32

#define PROGRAM_NO0 0x00
#define PROGRAM_NO1 0x01
#define PROGRAM_LIB 0x02
#define PROGRAM_CAT 0x03
#define PROGRAM_NO2 0x04
#define PROGRAM_CHI 0x05
#define PROGRAM_DAI 0x06
#define PROGRAM_NP3 0x07
#define PROGRAM_CEN 0x08
#define PROGRAM_NO4 0x09
#define PROGRAM_ARE 0x0A
#define PROGRAM_TOP 0x0B
#define PROGRAM_NZ0 0x0C
#define PROGRAM_NZ1 0x0D
#define PROGRAM_WRP 0x0E
#define PROGRAM_NO1_ 0x0F
#define PROGRAM_NO0_ 0x10
#define PROGRAM_DRE 0x12
#define PROGRAM_BO6 0x18
#define PROGRAM_ST0 0x1F
#define PROGRAM_MAD 0x40
#define PROGRAM_NO3 0x41
#define PROGRAM_INVERTEDCASTLE_FLAG 0x20

#define LBA_BIN_F_GAME 0x61CE
#define LBA_BIN_F_GAME2 0x6252
#define LBA_STAGE_MAD_ART 0x7D6F
#define LBA_STAGE_MAD_VH 0x7DEF
#define LBA_STAGE_MAD_BIN 0x7E28
#define LBA_STAGE_NO0_ART 0x7E5D
#define LBA_STAGE_NO0_VH 0x7EDD
#define LBA_STAGE_NO0_BIN 0x7F16
#define LBA_STAGE_NO3_ART 0x8297
#define LBA_STAGE_NO3_VH 0x8317
#define LBA_STAGE_NO3_BIN 0x834F
#define LBA_STAGE_ST0_ART 0x9044
#define LBA_STAGE_ST0_VH 0x90C4
#define LBA_STAGE_ST0_BIN 0x90F9
#define LBA_STAGE_NP3_ART 0x917F
#define LBA_STAGE_NP3_VH 0x91FF
#define LBA_STAGE_NP3_BIN 0x9235

extern s32 D_8006BAFC;
extern s32 D_8006BB00;
extern s32 D_8006C374;
extern GpuBufferUnk* D_8006C37C;
extern s32 D_8006C398;
extern s32 g_backbufferX;
extern s32 g_backbufferY;
extern Entity* D_8006C3B8;
extern Unkstruct4 D_80072B34;
extern s32 D_80072F20;
extern s32 D_80072F2C;
extern s32 D_80072EE8;
extern u16 D_80072F64;
extern s16 D_80072F66;
extern u16 D_80072F6C;
extern u16 D_80072F6E;
extern s32 D_80073060;
extern s32 D_80073080;
extern u16 D_8007308E;
extern s16 D_80073092;
extern u16 g_CurrentRoomHSize;
extern u16 g_CurrentRoomVSize;
extern s32 D_800730AC;
extern s32 g_CurrentRoomLeft;
extern s32 g_CurrentRoomTop;
extern s32 g_CurrentRoomRight;
extern s32 g_CurrentRoomBottom;
extern s32 g_CurrentRoomX;
extern s32 g_CurrentRoomY;
extern s32 g_CurrentRoomWidth;
extern s32 g_CurrentRoomHeight;
extern Entity D_800733D8[TOTAL_ENTITY_COUNT];
extern Entity D_800733D8[TOTAL_ENTITY_COUNT];
extern s16 D_800733DA;
extern s16 D_800733DE;
extern s32 D_800733E0;
extern s32 D_800733E4;
extern u16 D_800733EC;
extern u16 D_800733EE;
extern s8 D_800733F0;
extern u8 D_800733F1;
extern s16 D_80073404;
extern u16 D_80073406;
extern u16 D_8007340A;
extern u16 D_8007341C;
extern /*?*/ s32* D_80073424;
extern s16 D_80073428;
extern s16 D_8007342A;
extern u16 D_8007342E;
extern s8 D_80073510;
extern s8 D_80073511;
extern s8 D_80073512;
extern s8 D_80073513;
extern Entity D_800762D8[]; // D_800733D8 + 0x40
extern Unkstruct8 g_CurrentRoomTileLayout;
extern Entity D_8007A958[];
extern Entity D_8007D858[];
extern u16 D_80097408;
extern s32 D_80097428[];
extern Entity D_8007EF1C;
extern void* D_8007EFD8;
extern POLY_GT4 D_80086FEC[];
extern s32 playerX;
extern s32 playerY;
extern u32 g_randomNext;
extern s32 D_80096ED8[];
extern u32 D_80097364;
extern s32 D_800973B4;
extern POLY_GT4 D_800973B8[];
extern s32 D_800973FC;
extern s32 D_80097410;
extern s32 D_80097414;
extern Pad g_pads[];
extern s16 D_80097496;
extern s32 g_mapProgramId;
extern s32 D_800974AC;
extern s32 D_80097908;
extern s32 D_8009790C;
extern s32 D_8009792C;
extern s32 D_80097934;
extern u8 D_8009796E;
extern u8 D_8009798A;
extern u8 D_80097A8D;
extern s32 g_playerLevel;
extern s32 g_playerExp;
extern s32 g_playerGold;
extern s32 g_killCount;
extern playerHeart g_playerHeart[];
extern s32 g_playerHeartMax;
extern s32 g_playerHp;
extern s32 g_playerHpMax;
extern s32 g_playerMp;
extern s32 g_playerMpMax;
extern s32 D_80097C20;
extern s32 D_80097C24;
extern s32 g_timeHours;
extern s32 g_timeMinutes;
extern s32 g_timeSeconds;
extern s32 D_80097C98;

extern s32 D_800A2438;
extern Unkstruct10 D_800A2464[];
extern const char* c_strALUCARD;
extern const char* c_strSTR;
extern const char* c_strCON;
extern const char* c_strINT;
extern const char* c_strLCK;
extern const char* c_strEXP;
extern const char* c_strNEXT;
extern const char* c_strGOLD;
extern const char* c_strLEVEL;
extern const char* c_strTIME;
extern const char* c_strROOMS;
extern const char* c_strKILLS;
extern const char* c_strHP;
extern const char* c_strMP;
extern const char* c_strHEART;
extern const char* c_strSTATUS;
extern const char* c_strButton;
extern const char* c_strCloak;
extern const char* c_strCloak2;
extern const char* c_strExterior;
extern const char* c_strLining;
extern const char* c_strButtonRightHand;
extern const char* c_strButtonLeftHand;
extern const char* c_strButtonJump;
extern const char* c_strButtonSpecial;
extern const char* c_strButtonWolf;
extern const char* c_strButtonMist;
extern const char* c_strButtonBat;
extern const char* c_strNormal;
extern const char* c_strReversal;
extern const char* c_strSound;
extern const char* c_strStereo;
extern const char* c_strMono;
extern const char* c_strWindow;
extern const char* c_strTime;
extern const char* c_strALUCART;
extern const char* c_strSSword;
extern s32 D_800A4B04;
extern s32 D_800A7718;
extern u16 D_800A7734;
extern const char* c_strEquip;
extern const char* c_strSpells;
extern const char* c_strRelics;
extern const char* c_strSystem;
extern const char* c_strFamiliars;
extern const char* c_strFamiliar;
extern const char* c_strSpecial2;
extern s32 D_800ACC64;
extern RECT D_800ACD80;
extern RECT c_backbufferClear;
extern s16 D_800BD07C[];
extern u8 D_80137460;
extern RoomLoadDef* D_801375BC;
extern s32 D_801375C8;
extern s32 D_801375DC;
extern s32 D_801375FC;
extern s32 D_80137614;
extern s32 D_80137618;
extern u8 D_8013761C[]; // can't use `extern MenuContext D_8013761C[];` as it's
                        // 2-byte aligned
extern s8 D_80137638;
extern s32 D_80137844;
extern s32 D_80137848;
extern s32 D_8013784C;
extern s32 D_80137960;
extern s32 D_80137964;
extern s32 D_80137968;
extern s32 D_80137970;
extern s32 D_80137974;
extern u32 D_80137978;
extern u32 D_8013797C;
extern s32 D_80137980;
extern s32 D_80137984;
extern u32 D_80137988;
extern u32 D_8013798C;
extern s32 D_80137990;
extern s32 D_80137994;
extern s32 D_80137E4C;
extern s32 D_80137E64;
extern s32 D_80137E68;
extern s32 D_80138F20;
extern s32 D_80138F28;
extern s32 D_80138F7C;
extern s16 D_80139000;
extern s16 D_80139008;
extern s16 D_8013901C;
extern u8 D_80139020;
extern s8 D_801390C4;
extern u8 D_801390D8;
extern s16 D_801390DC;
extern s16 D_801390DE;
extern s16 D_801390E0;
extern s16 D_801396EA;
extern u16 D_801396F4;
extern s32 D_801397FC;
extern s32 D_8013980C;
extern u8 D_80139810;
extern s32 D_80139828;
extern s32 D_80139834[];
extern s16 D_80139868;
extern s16 D_80139A70;
extern s32 D_8013AE9C;
extern u8 D_8013AEEC;
extern s32 D_8013B158;
extern s32 D_8013B3D0;
extern s16 D_8013B3E8[];
extern s32 D_8013B5E8;
extern s32 D_8013B61C;
extern s16 D_8013B658;
extern s32 D_8013B660;
extern s16 D_8013B668;
extern u8 D_8013B680;
extern s8 D_8013B684;
extern s32 D_8013B694;
extern const char* D_80138784[487];
extern ImgSrc* g_imgUnk8013C200;
extern ImgSrc* g_imgUnk8013C270;

void func_800E346C();
void func_800E34A4(s8 arg0);
void func_800E34DC(s32 arg0);
void func_800E4124(s32 arg0);
void func_800E8D24(void);
void func_800E8DF0(void);
void func_800E92E4(void);
void func_800E92F4(void);
void func_800EA5E4(s32);
void func_800EDA70(s32* arg0);
void func_800EDAE4(void);
s16 func_800EDC80(u8 arg0, s32 arg1);
s32 func_800EDD9C(u8 arg0, s32 arg1);
void FreePolygons(s32 index);
s32 func_800F087C(u32, u32);
bool SetNextRoomToLoad(u32 chunkX, u32 chunkY);
void func_800F1EB0(s32, s32, s32);
void func_800F2120();
void func_800F223C(void);
void func_800F4994(void);
void func_800F4F48(void);
void func_800F4FD0(void);
bool IsAlucart();
void func_800F53A4(void);
bool ScissorSprite(SPRT* arg0, MenuContext* arg1);
void func_800F5904(void*, s32 x, s32 y, s32 w, u32 h, s32 u, s32 v, s32 unk1,
                   s32 unk2, bool disableTexShade, s32 unk4);
s32 func_800F62E8(s32 arg0);
void DrawMenuChar(char ch, int x, int y, MenuContext* context);
void DrawMenuStr(const char* str, s32 x, s32 y, MenuContext* context);
void DrawMenuInt(s32 value, s32 x, s32 y, MenuContext*);
void DrawSettingsReverseCloak(MenuContext* context);
void DrawSettingsSound(MenuContext* context);
void DrawPauseMenu(s32 arg0);
void func_800F82F4(void);
void func_800F8858(MenuContext* context);
void func_800FABEC(s32 arg0);
void func_800FAC30(void);
s32 func_800FD4C0(s32, s32);
s32 func_800FD664(s32 arg0);
u8* func_800FD744(s32 arg0);
u8* func_800FD760(s32 arg0);
s32 func_800FD77C(s32 arg0, s32 arg1);
bool func_800FD7C0(s32, s32);
;
void func_800FD874(u16 arg0, s32 arg1);
void func_800FDE00(void);
void func_800FF0A0(s32 arg0);
void func_80102DEC(s32 arg0);
void func_80103EAC(void);
void func_80106590(Entity*);
void func_801065F4(s16 startIndex);
void func_801071CC(POLY_GT4* poly, u8, s32);
void func_80107250(POLY_GT4* poly, s32 arg1);
void func_80107360(POLY_GT4* poly, s32 x, s32 y, s32 width, s32 height, u8 u,
                   u8 v);
void SetPolyRect(POLY_GT4* poly, s32 x, s32 y, s32 width, s32 height);
void func_8010D584(s16 arg0);
void func_8010E0A8(void);
void func_8010E0B8(void);
void func_80111928(void);
void func_80131EBC(const char* str, s16 arg1);
void func_80131ED8(s32 value);
void func_80131EE8(void);
void func_80131F04(void);
s32 func_80131F28(void);
s32 func_80131F38(void);
bool func_80131F68(void);
s16 func_80131F94(void);
s32 func_80132134();
s32 func_80132264();
s32 func_801326D8();
void func_8013271C(void);
void func_80132760(void);
void func_801337B4(void);
s32 func_80133940(void);
s32 func_80133950(void);
void func_8013415C();
void func_801361F8();

#endif
