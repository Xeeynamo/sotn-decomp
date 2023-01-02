#ifndef DRA_H
#define DRA_H
#include "main.h"
#include "unkstruct.h"

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
    s16 modeS16;
    struct {
        u8 unk0;
        u8 unk1;
    } modeU8;
} unkUnion3;

typedef union {
    byte typeByte;
    short typeShort;
    int typeInt;
} MultiType;

typedef struct Entity {
    /* 0x00 */ UnkUnion1 posX;
    /* 0x04 */ UnkUnion1 posY;
    /* 0x08 */ s32 accelerationX;
    /* 0x0C */ s32 accelerationY;
    /* 0x10 */ s16 unk10;
    /* 0x12 */ s16 unk12;
    /* 0x14 */ u16 facing;
    /* 0x16 */ u16 palette;
    /* 0x18 */ s8 blendMode;
    /* 0x19 */ u8 unk19;
    /* 0x1A */ s16 unk1A;
    /* 0x1C */ s16 unk1C;
    /* 0x1E */ s16 unk1E;
    /* 0x20 */ s16 unk20;
    /* 0x22 */ s16 unk22;
    /* 0x24 */ u16 zPriority;
    /* 0x26 */ u16 objectId;
    /* 0x28 */ PfnEntityUpdate pfnUpdate;
    /* 0x2C */ u16 step;
    /* 0x2E */ u16 unk2E;
    /* 0x30 */ u16 subId;
    /* 0x32 */ u16 objectRoomIndex;
    /* 0x34 */ s32 unk34;
    /* 0x38 */ s16 unk38;
    /* 0x3A */ s16 unk3A;
    /* 0x3C */ s16 unk3C;
    /* 0x3E */ s16 hitPoints;
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
    /* 0x6A */ u16 unk6A;
    /* 0x6C */ u8 unk6C;
    /* 0x6D */ s8 unk6D;
    /* 0x6E */ s16 unk6E;
    /* 0x70 */ s32 unk70;
    /* 0x74 */ s32 unk74;
    /* 0x78 */ s32 unk78;
    /* 0x7C */ unkUnion3 unk7C;
    /* 0x7E */ u8 unk7E;
    /* 0x7F */ u8 unk7F;
    union {
        /* 0x80 */ struct Entity* entityPtr;
        s32 modeS32;
        struct {
            /* 0x80 */ s16 unk0;
            /* 0x82 */ s16 unk2;
        } modeS16;
        struct {
            /* 0x80 */ u8 unk0;
            /* 0x81 */ u8 unk1;
        } modeS8;
    } unk80; // size = 0x4
    /* 0x84 */ UnkUnion1 unk84;
    /* 0x88 */ s8 unk88;
    /* 0x89 */ s8 unk89;
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
    /* 0xAC */ u8 unkAC;
    /* 0xAD */ s8 unkAD;
    /* 0xAE */ s8 unkAE;
    /* 0xAF */ s8 unkAF;
    /* 0xB0 */ s16 unkB0;
    /* 0xB2 */ s16 unkB2;
    /* 0xB4 */ s16 unkB4;
    /* 0xB6 */ s16 unkB6;
    union {
        /* 0xB8 */ UnkFunctionUpdate1 unkFuncB8;
        struct {
            /* 0xB8 */ u8 unk0;
            /* 0xB9 */ u8 unk1;
            /* 0xBA */ u8 unk2;
            /* 0xBB */ u8 unk3;
        } modeU8;
    } unkB8;
} Entity; // size = 0xBC

typedef struct {
    /* 0x00 */ u16 animationSet;
    /* 0x02 */ u16 zPriority;
    /* 0x04 */ UnkUnion2 unk4;
    /* 0x06 */ u16 palette;
    /* 0x08 */ u8 unk8;
    /* 0x09 */ u8 unk9;
    /* 0x0A */ u8 blendMode;
    /* 0x0B */ u8 unkB;
    /* 0x0C */ u32 unkC;
    /* 0x10 */ const u8* unk10;
} ObjInit2; // size = 0x14

typedef struct unkStruct3 {
    /* 0x00 */ struct unkStruct3* unk0;
    /* 0x04 */ s8 unk4;
    /* 0x04 */ char pad4[0x1];
    /* 0x05 */ s8 unk6;
    /* 0x07 */ s8 unk7;
    /* 0x08 */ s16 unk8;
    /* 0x0A */ s16 unkA;
    /* 0x0C */ s16 unkC;
    /* 0x0E */ s16 unkE;
    /* 0x10 */ UnkUnion2 unk10;
    /* 0x12 */ UnkUnion2 unk12;
    /* 0x14 */ s16 unk14;
    /* 0x16 */ s16 unk16;
    /* 0x18 */ s16 unk18;
    /* 0x1A */ s16 unk1A;
    /* 0x1C */ UnkUnion2 unk1C;
    /* 0x1E */ UnkUnion2 unk1E;
    /* 0x20 */ s16 unk20;
    /* 0x22 */ s16 unk22;
    /* 0x24 */ s8 unk24;
    /* 0x25 */ s8 unk25;
    /* 0x26 */ char pad26[0x2];
    /* 0x28 */ s8 unk28;
    /* 0x29 */ char pad[0x1];
    /* 0x2A */ u8 unk2A;
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
    /* 0x02 */ s16 unk2; // compared to Entity posX
    /* 0x04 */ u16 unk4;
    /* 0x06 */ u16 unk6; // compared to Entity posY
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
    /* 0x0 */ void* addr1;
    /* 0x4 */ void* addr2;
    /* 0x8 */ u16 unk8;
    /* 0xA */ u16 unkA;
    /* 0xC */ u16 unkC;
    /* 0xE */ u16 unkE;
} Unkstruct8; // size = 0x10

typedef struct {
    /* 0x0 */ u16 programId;
    /* 0x2 */ u16 unk2;
    /* 0x4 */ u16 unk4;
    /* 0x6 */ u16 unk6;
    /* 0x8 */ u16 unk8;
} Unkstruct10; // size = 0xA

typedef enum {
    ENTITY_STEP_0,
    ENTITY_STEP_1,
    ENTITY_STEP_2,
    ENTITY_STEP_3,
    ENTITY_STEP_4,
    ENTITY_STEP_5,
    ENTITY_STEP_6,
    ENTITY_STEP_7,
    ENTITY_STEP_19 = 0x19
} EntitySteps;

typedef enum { MONO, STEREO } SoundMode;

typedef struct {
    /* 0x00 */ DRAWENV draw; // drawing environment
    /* 0x58 */ DISPENV disp; // display environment
} DisplayBuffer;

typedef struct {
    /* 0x00000 */ void* unk0;
    /* 0x00004 */ DisplayBuffer buf;
    /* 0x00074 */ char pad74[0x400];
    /* 0x00474 */ u32 _unk_0474[0x200];
    /* 0x00474 */ DR_MODE drawModes[0x400];
    /* 0x03C74 */ POLY_GT4 polyGT4[0x300];
    /* 0x0D874 */ POLY_G4 polyG4[0x100];
    /* 0x0FC74 */ POLY_GT3 polyGT3[0x30];
    /* 0x103F4 */ LINE_G2 lineG2[0x100];
    /* 0x117F4 */ SPRT_16 sprite16[0x280];
    /* 0x13FF4 */ TILE tiles[0x100];
    /* 0x14FF4 */ SPRT sprite[0x200];
} GpuBuffer; /* size = 0x177F4 */

typedef struct PlayerHeart {
    s32 current;
    s32 max;
} PlayerHeart;

typedef struct PlayerHP {
    s32 current;
    s32 max;
} PlayerHP;

typedef struct PlayerMp {
    s32 current;
    s32 max;
} PlayerMp;

typedef struct {
    s32 hours;
    s32 minutes;
    s32 seconds;
    s32 frames;
} GameTimer;

// main
extern s32 D_8003C0EC[4];
extern s32 D_8003C0F8;
extern u16 D_8003C104[];
extern Unkstruct5* D_8003C704;
extern u16 D_8003C708;
extern s32 D_8003C730;
extern s32 D_8003C734;
extern s32 D_8003C73C;
extern void (*D_8003C744)(s32, s32);
extern void (*g_pfnUpdateStageEntities)(void); // TODO to 0x50 array of funcs
extern void (*g_pfnTestStageEntities)(void);
#ifndef STAGE_MAD
extern void (*g_pfnLoadObjLayout)(void);
#endif
extern RoomHeader* D_8003C784;
extern void (*D_8003C7B0)();
extern void (*D_8003C7BC)(s32 posX, s32 posY, Unkstruct7*, s32);
extern void (*g_pfnPlaySfx)(s32);
extern void (*g_pfnFreePolygons)(s32);
extern Unkstruct5* D_8003C808;
extern void (*D_8003C848)(s32, s32);
extern s32 D_8003C8C4;
extern s32 g_roomCount;
extern s32 D_8003C99C;
extern s32 g_CurrentPlayableCharacter;
extern s32 D_8003C9A4;
extern s32 g_blinkTimer;
extern s32 g_menuMainCursorIndex;
extern s32 g_menuRelicsCursorIndex[];
extern s32 g_SettingsCloakMode;
extern s32 g_SettingsSoundMode;
extern s32 D_8003CACC;
extern s32 D_8003CB00[];
extern s32 D_8003CB04;
extern GpuBuffer D_8003CB08;
extern GpuBuffer D_800542FC;
extern s16 D_80054302;     // TODO overlap, hard to remove
extern DISPENV D_8005435C; // TODO overlap, hard to remove

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
#define PROGRAM_NO1_ALT 0x0F
#define PROGRAM_NO0_ALT 0x10
#define PROGRAM_DRE 0x12
#define PROGRAM_BO7 0x16
#define PROGRAM_MAR 0x17
#define PROGRAM_BO6 0x18
#define PROGRAM_BO5 0x19
#define PROGRAM_BO4 0x1A
#define PROGRAM_BO3 0x1B
#define PROGRAM_BO2 0x1C
#define PROGRAM_BO1 0x1D
#define PROGRAM_BO0 0x1E
#define PROGRAM_ST0 0x1F
#define PROGRAM_MAD 0x40
#define PROGRAM_NO3 0x41
#define PROGRAM_IWA_LOAD 0x42
#define PROGRAM_IGA_LOAD 0x43
#define PROGRAM_HAGI_LOAD 0x44
#define PROGRAM_TE1 0x46
#define PROGRAM_TE2 0x47
#define PROGRAM_TE3 0x48
#define PROGRAM_TE4 0x49
#define PROGRAM_TE5 0x4A
#define PROGRAM_TOP_ALT 0x4B
#define PROGRAM_INVERTEDCASTLE_FLAG 0x20
#define PROGRAM_ENDING 0xFE
#define PROGRAM_MEMORYCARD 0xFF

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

extern const char g_strMemcardSavePath[];
extern const char g_strMemcardRootPath[];
extern s32 D_8006BAFC;
extern s32 D_8006BB00;
extern s32 D_8006C374;
extern GpuBuffer* D_8006C37C;
extern s32 D_8006C398;
extern s32 D_8006C3AC;
extern u16 D_8006C3C4;
extern s32 g_backbufferX;
extern s32 g_backbufferY;
extern s32 D_8006C3B0;
extern Entity* g_CurrentEntity;
extern s32 D_8006CBC4;
extern Unkstruct4 D_80072B34;
extern s32 D_80072EE8;
extern s32 D_80072EEC;
extern s32 D_80072EF4;
extern u16 D_80072EF6;
extern s32 D_80072EFC;
extern s16 D_80072F00[];
extern s16 D_80072F04;
extern s16 D_80072F0A;
extern s16 D_80072F0C;
extern s16 D_80072F16[2];
extern s16 D_80072F18;
extern s16 D_80072F1A[];
extern s16 D_80072F1C[];
extern s16 D_80072F1E;
extern s32 D_80072F20;
extern s32 D_80072F24;
extern u32 D_80072F2C;
extern u16 D_80072F70;
extern u16 D_80072F92;

// Probably part of the same array / struct
extern u16 D_80072F60;
extern u16 D_80072F64[];
extern s16 D_80072F66;
extern u16 D_80072F68[];
extern u16 D_80072F6C;
extern u16 D_80072F6E;
extern s16 D_80072F86;
extern s16 D_80072F88;
extern unkstruct_80072FA0 D_80072FA0[];
extern u32 D_80073060;
extern s32 D_80073080;
extern u16 D_8007308E;
extern u32 D_80073068;
extern u32 D_8007306C;
extern u32 D_80073070;
extern u32 D_80073078;
extern u16 D_80073092;
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

// Entity* player = GET_PLAYER(g_EntityArray);
// player->
// Beginning of Player Character offset = 0x800733D8
extern Entity g_EntityArray[TOTAL_ENTITY_COUNT];
extern s16 D_800733DA;       // player->posX.Data.high
extern s16 D_800733DE;       // player->posY.Data.high
extern s32 D_800733E0;       // player->accelerationX
extern s32 D_800733E4;       // player->accelerationY
extern s32 D_800733E8;       // player->unk10
extern u16 D_800733EC;       // player->facing
extern u16 D_800733EE;       // player->palette
extern s8 D_800733F0;        // player->blendMode
extern u8 D_800733F1;        // player->unk19
extern s16 D_800733F6;       // player->unk1E
extern u16 D_800733FC;       // player->zPriority
extern s16 D_800733FE;       // player->objectId
extern u16 D_80073404;       // player->step
extern u16 D_80073406;       // player->unk2E
extern u16 D_8007340A;       // player->objectRoomIndex
extern u16 D_8007341C;       // player->unk44
extern s32* D_80073424;      // player->unk4C
extern MultiType D_80073428; // player->animationFrameIndex
extern s16 D_8007342A;       // player->animationFrameDuration
extern s16 D_8007342C;       // player->animationSet
extern u16 D_8007342E;       // player->animationFrame
extern u8 D_80073484;        // player->unkAC
// End of Player Character offset = 0x80073494

// Beginning of g_EntityArray[1] offset = 0x80073494

extern s16 D_800734EA; // entity->animationFrame
extern s32 D_800734F8; // entity->firstPolygonIndex
extern s8 D_80073510;  // entity->unk7C.modeU8.unk0
extern s8 D_80073511;  // entity->unk7C.modeU8.unk1
extern s8 D_80073512;  // entity->unk7E
extern s8 D_80073513;  // entity->unk7F

// End of g_EntityArray[1] offset = 0x80073550

// Beginning of g_EntityArray[2] offset = 0x80073550

extern s16 D_800735A6; // entity->animationFrame

// End of g_EntityArray[2] offset = 0x8007360C

// Beginning of g_EntityArray[3] offset = 0x8007360C

extern s16 D_80073662; // entity->animationFrame

// End of g_EntityArray[3] offset = 0x800736C8

extern Entity D_800736C8; // g_EntityArray[4]
extern Entity D_80073F98; // g_EntityArray[16]
extern u16 D_80073FBE;    // g_EntityArray[16].objectId
extern Entity D_80073FC4; // g_EntityArray[16].step
extern Entity D_80074C08[];
extern Entity D_800762D8[]; // g_EntityArray[64]
extern Unkstruct8 g_CurrentRoomTileLayout;
extern Entity D_8007A958[];
extern Entity D_8007D858[];
extern u16 g_zEntityCenter;
extern s32 g_entityDestroyed[];
extern Entity D_8007EF1C;
extern s32 D_8007EFDC;
extern s32 D_8007EFE0;
extern s32 D_8007EFE4;
extern unsigned long D_8007EFD8;
extern s8 D_80082FE4;
extern s32 D_80086FE4;
extern POLY_GT4 D_80086FEC[];
extern s32 playerX;
extern s32 playerY;
extern u32 g_randomNext;
extern s32 D_80096ED8[];
extern u32 D_80097364;
extern s32 D_800973B4;
extern POLY_GT4 D_800973B8[];
extern s32 D_800973EC; // flag to check if the menu is shown
extern s32 D_800973FC;
extern s32 D_80097410;
extern s32 D_80097414;
extern s32 D_80097420;
extern s32 D_8009744C;
extern Pad g_pads[];
extern u16 D_80097494; // related to g_menuRelicsCursorIndex
extern u16 D_80097496;
extern u16 D_8009749C[];
extern s32 g_mapProgramId;
extern s32 D_800974A4;
extern s32 D_800974AC;
extern s32 D_800978AC;
extern s32 D_800978C4;
extern s32 D_800978F8;
extern s32 D_80097904;
extern s32 D_80097908;
extern s32 D_8009790C;
extern s32 D_80097910;
extern s32 D_80097914;
extern s32 D_80097928;
extern Unkstruct_Entrypoint D_8009792C;
extern s32 D_80097934;
extern u8 D_80097964[];
extern u8 D_8009796E;
extern u8 D_8009798A;
extern u8 D_80097A8D;
extern u32 D_80097BE4;
extern s32 g_playerLevel;
extern s32 g_playerExp;
extern s32 g_playerGold;
extern s32 g_killCount;
extern PlayerHeart g_playerHeart[];
extern s32 g_playerHeartMax;
extern PlayerHP g_playerHp;
extern s32 g_playerHpMax;
extern PlayerMp g_playerMp;
extern s32 g_playerMpMax;
extern s32 D_80097C1C[];
extern s32 D_80097C20;
extern s32 D_80097C24;
extern GameTimer g_GameTimer;
extern s32 D_80097C98;
extern s8 D_80097D37;
extern s32 D_800987B4;
extern s32 D_80098850;
extern void (*D_800A0004)(); // TODO pointer to 0x50 array of functions
extern s32 D_800A04EC;
extern s32 D_800A0510[];
extern u16 g_saveIconPalette[0x10][0x10];
extern u8* g_saveIconTexture[0x10];
extern s32 D_800A2438;
extern u8 D_800A2EE8[];
extern u8 D_800A2EED;
extern u8 D_800A2EF8[];
extern u8 D_800A2EFD;
extern u8 D_800A2F08[];
extern u8 D_800A2F18[];
extern u8 D_800A2F28[];
extern u8 D_800A2F2D;
extern u8 D_800A2F38[];
extern u8 D_800A2F3D;
extern u16 D_800A2F48[];
extern u16 D_800A2F64[];
extern s32 D_800A2FBC[];
extern s32 D_800A2FC0[];
extern s32 player_equip_ring2;
extern s32 player_equip_head[];
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
extern u16 D_800A7734[];
extern s8 D_800A841C[];  // related to player MP
extern s32 D_800ACC64[]; // probably a struct
extern RECT D_800ACD80;
extern RECT D_800ACD88[2];
extern RECT D_800ACD90;
extern RECT D_800ACDF0;
extern Unkstruct_800ACEC6 D_800ACEC6;
extern u8 D_800ACF4C[];
extern s16 D_800ACF60[];
extern s32* D_800AE294; // might not really be a pointer
extern s16 D_800AFDA6;
extern const char* c_strEquip;
extern const char* c_strSpells;
extern const char* c_strRelics;
extern const char* c_strSystem;
extern const char* c_strFamiliars;
extern const char* c_strFamiliar;
extern const char* c_strSpecial2;
extern RECT c_backbufferClear;
extern s32 D_800B0914;
extern s16 D_800BD07C[];
extern s32 D_800BD1C0;
extern s32 D_800DC4C0;
extern s8 D_800DC4C4;
extern s32 D_801362AC;
extern s32 D_801362B0;
extern s32 D_801362B4;
extern s32 D_801362B8;
extern s32 D_801362BC;
extern s32 D_801362C0;
extern s32 D_801362C4;
extern s32 D_801362C8;
extern u32* D_801362CC;
extern s32 D_801362D4;
extern s32 D_801362D8;
extern Unkstruct_Entrypoint D_801362DC;
extern s32 D_801362E0;
extern s32 D_801362E4;
extern s32 D_801362E8;
extern s32 D_801362EC;
extern s32 D_801362F0;
extern s32 D_801362F4;
extern s32 D_801362F8;
extern s32 D_801362FC;
extern s32 g_softResetTimer;
extern s32 D_8013640C;
extern s16 D_80136460[];
extern s16 D_80136C60[];
extern u8 D_80137460;
extern s32 D_80137470;
extern s32 D_80137474;
extern u16 D_80137478[];
extern u16 D_801374B8[];
extern s16 D_801374F8;
extern u8* D_80137578;
extern u8* D_8013757C;
extern s32 D_80137580;
extern s32 D_80137584;
extern s32* D_80137590;
extern RoomLoadDef* D_801375BC;
extern s16 D_80137538;
extern s32 D_801375C8;
extern s32 D_801375CC;
extern s32 D_801375DC;
extern s32 D_801375FC;
extern s32 D_80137608;
extern s32 D_80137614;
extern s32 D_80137618;
extern u8 D_8013761C[]; // can't use `extern MenuContext D_8013761C[];` as it's
                        // 2-byte aligned
// extern u8 D_80137638[2];
// extern u8 D_80137639[];
extern u8 D_80137692;
extern u8 D_801376B0;
extern s32 D_8013783C;
extern s32 D_801377FC[];
extern s32 D_80137840;
extern s32 D_80137844[];
extern s32 D_80137848;
extern s32 D_8013784C;
extern s32 g_someValue;
extern s32 D_80137930;
extern s32 D_80137934;
extern s32 D_80137938[];
extern s8* D_8013794C; // Pointer to texture pattern
extern s32 D_80137950;
extern s32 D_80137954;
extern s32 D_80137960;
extern s32 D_80137964;
extern s32 D_80137968;
extern s32 D_8013796C;
extern s32 D_80137970;
extern s32 D_80137974;
extern u32 D_80137978;
extern u32 D_8013797C;
extern s32 D_80137980;
extern s32 D_80137984;
extern u32 D_80137988;
extern u32 D_8013798C;
extern s32 D_80137994;
extern s32 D_80137998;
extern u32 D_8013799C;
extern s32 D_801379A0;
extern s32 D_80137E40;
extern s32 D_80137E44;
extern s32 D_80137E48;
extern s32 D_80137E4C;
extern s32 D_80137E64;
extern s32 D_80137E68;
extern s32 D_80137F6C;
extern void* D_80137F7C;
extern s32 D_80137F9C;
extern s32 D_80138430;
extern s32 D_80138438;
extern s32 D_80138460;
extern const char* D_80138784[487];
extern s32 D_80138F20;
extern u8 D_80138F24[]; // Confirmed part of an array / struct
extern s32 D_80138F28;
extern s32 D_80138F7C;
extern s32 D_80138FB0;
extern s16 D_80139000;
extern s16 D_80139008;
extern s32 D_8013900C;
extern s16 D_8013901C;
extern u8 D_80139020;
extern u8 D_801390A8;
extern s8 D_801390C4;
extern GpuBuffer* D_801390D4;
extern u8 D_801390D8;
extern Unkstruct_801390DC D_801390DC[];
extern u16 D_801396E4;
extern MultiType D_801396E6;
extern u16 D_801396E8;
extern s16 D_801396EA;
extern u16 D_801396F4;
extern s32 D_801397FC;
extern s16 D_80139804;
extern s32 D_8013980C;
extern u8 D_80139810;
extern s32 D_80139828[];
extern s32 D_80139834[];
extern s16 D_80139A70;
extern s16 D_8013AE7C;
extern s16 D_8013AE8C;
extern s16 D_8013AE84[];
extern s16 D_8013AEA0[];
extern s16 D_8013AE94;
extern s32 D_8013AE9C;
extern s16 D_8013AED4[];
extern s16 g_volumeL;
extern s16 g_volumeR;
extern s16 D_8013B698;
extern s16 D_8013AEE0;
extern u8 D_8013AEEC;
extern s32 D_8013B158;
extern s32 D_8013B3D0;
extern s16 D_8013B3E8[];
extern s32 D_8013B5E8;
extern s8 D_8013B5EC[];
extern s8 D_8013B614[];
extern s32 D_8013B61C;
extern s16 D_8013B620[];
extern s32 D_8013B628[];
extern s16 D_8013B648[];
extern s16 D_8013B650[];
extern s16 D_8013B658;
extern s32 D_8013B660;
extern s16 D_8013B664;
extern s16 D_8013B668;
extern s16 D_8013B66C[];
extern u8 D_8013B680;
extern s8 D_8013B684;
extern s8 D_8013B690;
extern s32 D_8013B694;
extern void (*D_8013C00C)(void);
extern void (*D_80170000)(void);
extern ImgSrc* g_imgUnk8013C200;
extern ImgSrc* g_imgUnk8013C270;
extern s32 D_801EC000[];

void InitializePads(void);
void ReadPads(void);
void ClearBackbuffer(void);
void SetRoomForegroundLayer(s32 /* ? */);
void SetRoomBackgroundLayer(s32 /* ? */, s32 /* ? */);
s32 CheckCollision(s32, s16, s32*, s32);
void PlaySfx(s16 sfxId);
s32 func_80019444(void);
void func_800209B4(s32*, s32, s32);
void func_80021E38(s32);
void func_80021EEC(void);
void func_80028D3C(s32, s32);
void func_80029FBC(s32);
void func_8002A09C(void*);
void func_8002ABF4(s32);
void func_800E346C(void);
void func_800E34A4(s8 arg0);
void func_800E34DC(s32 arg0);
void func_800E4124(s32 arg0);
void func_800E8D24(void);
void func_800E8DF0(void);
s32 func_800E912C(void);
s32 func_800E9208(void);
void func_800E928C(void);
void func_800E92E4(void);
void func_800E92F4(void);
void func_800EA5E4(s32);
void func_800EA538(s32);
void func_800EAD7C(void);
void func_800EAEEC(void);
void func_800EB534(u16, u16, s32);
void func_800ECE2C(void);
void func_800EDA70(s32* arg0);
void func_800EDA94(void);
void func_800EDAE4(void);
s16 func_800EDC80(u8 arg0, s32 arg1);
s32 func_800EDD9C(u8 arg0, s32 arg1);
void func_800EFBF8(void);
void FreePolygons(s32 index);
void func_800F0334(s32);
s32 func_800F087C(u32, u32);
bool SetNextRoomToLoad(u32 chunkX, u32 chunkY);
void func_800F180C(s32, s32, void*);
void func_800F1868(s32, s32, void*);
void func_800F18C4(s32, s32);
void func_800F1954(s32, s32, s32);
void func_800F1EB0(s32, s32, s32);
void func_800F2120(void);
void func_800F223C(void);
void func_800F4994(void);
s32 func_800F4D38(s32, s32);
void func_800F4F48(void);
void func_800F4FD0(void);
bool IsAlucart(void);
s32 SquareRoot12(s32, s32);
void func_800F53A4(void);
bool ScissorSprite(SPRT* arg0, MenuContext* arg1);
void func_800F5904(void*, s32 x, s32 y, s32 w, u32 h, s32 u, s32 v, s32 unk1,
                   s32 unk2, bool disableTexShade, s32 unk4);
s32 func_800F62E8(s32 arg0);
void func_800F98AC(s32 arg0, s32 arg1);
void func_800F99B8(s32 arg0, s32 arg1, s32 arg2);
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
// s32 func_800FD4C0(s32, s32);
s32 func_800FD664(s32 arg0);
u8* func_800FD744(s32 arg0);
u8* func_800FD760(s32 arg0);
s32 func_800FD77C(s32 arg0, s32 arg1);
bool func_800FD7C0(s32, s32);
void func_800FD874(u16 arg0, s32 arg1);
s16 func_800FDB18(s32, s32);
void func_800FDE00(void);
void func_800FE3C4(Unkstruct_8011A290*, s32, s32);
s32 func_800FEEA4(s32, s32);
void func_800FF0A0(s32 arg0);
void func_80102DEC(s32 arg0);
void func_80103EAC(void);
void func_80106590(Entity*);
void func_801065F4(s16 startIndex);
void func_801071CC(POLY_GT4* poly, u8, s32);
void func_80107250(POLY_GT4* poly, s32 arg1);
void func_80107360(POLY_GT4* poly, s32 x, s32 y, s32 width, s32 height, s32 u,
                   s32 v);
void func_801073C0(void);
void func_801092E8(s32);
void SetPolyRect(POLY_GT4* poly, s32 x, s32 y, s32 width, s32 height);
void func_8010D584(s16 arg0);
void func_8010DFF0(s32, s32);
void func_8010E0A8(void);
void func_8010E0B8(void);
void func_8010E470(s32, s32);
void func_8010E83C(s32 arg0);
void func_80111928(void);
void func_80111CC0(void);
void func_80118894(Entity*);
void func_80118C28(s32 arg0);
bool func_80111D24(void);
Entity* func_8011AAFC(Entity* entity, s32, s32);
void func_80131EBC(const char* str, s16 arg1);
void func_80131ED8(s32 value);
void func_80131EE8(void);
void func_80131F04(void);
s32 func_80131F28(void);
u16 func_80131F38(void);
bool func_80131F68(void);
s16 func_80131F94(void);
void func_8013216C(void);
void func_801321FC(void);
void func_80132134(void);
s32 func_80132264(void);
s32 func_801326D8(void);
void func_80132028(s32, s8*, s32);
void func_8013271C(void);
void func_80132760(void);
void func_801337B4(void);
s32 func_80133940(void);
s32 func_80133950(void);
void func_80133FCC(void);
void func_8013415C(void);
void func_801361F8(void);

#endif
