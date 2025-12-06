// SPDX-License-Identifier: AGPL-3.0-or-later
//! PSYQ=3.3 O=1
#define VERSION_SD
#include <game.h>
#include <sfx.h>

extern s32 D_8005150C;
extern u16 D_800828B8;
extern u32 D_80088FE8;

void func_80180954();
void* D_80180000[] = {(void*)func_80180954};
static s16 D_80180004 = 0;
static s16 D_80180006 = 0;

static s16 D_80180008[];
static const char* D_801800D8[];
static s16 D_80180278[];
static const char* D_80180298[];
static s16 D_801802D4[];
static const char* D_801802D8[];

extern Primitive D_8009CE78[];
void func_800149C0(const char* fmt, ...);
void func_80180FA0();
void func_80180FD4();
extern s16 D_80181210;
extern s16 D_80181214;
extern s16 D_80181218;
extern s16 D_8018121C;

static void SetDisplayBuffer(s16 width);
void func_80180954(void) {
    Primitive* prim;

    if (D_80088FE8) {
        func_80180FD4();
    }
    switch (D_80088FE8) {
    case 0:
        if (func_8018106C() == 0) {
            func_80180FA0();
            SetDisplayBuffer(256);
            D_80088FE8++;
        }
        break;
    case 1:
        D_80181210 = g_api.AllocPrimitives(PRIM_GT4, 1);
        prim = &D_8009CE78[D_80181210];
        prim->x0 = 0;
        prim->y0 = 0;
        prim->x1 = 0xFF;
        prim->y1 = 0;
        prim->x2 = 0;
        prim->y2 = 0xDF;
        prim->x3 = 0xFF;
        prim->y3 = 0xDF;
        prim->u0 = 0;
        prim->v0 = 0;
        prim->u1 = 0xFF;
        prim->v1 = 0;
        prim->u2 = 0;
        prim->v2 = 0xDF;
        prim->u3 = 0xFF;
        prim->v3 = 0xDF;
        prim->tpage = 0x108;
        prim->priority = 0;
        prim->drawMode = 0x11;
        D_80088FE8++;
        break;
    case 2:
        if (g_pads[0].tapped & PAD_START) {
            if (func_8018106C() == 0) {
                g_api.PlaySfx(SET_UNK_13);
                D_80180006 = 0;
                D_80180004 = 0;
                D_80088FE8++;
                return;
            }
            break;
        }
        func_800149C0("sound test mode vx010\n");
        func_800149C0("\n");
        func_800149C0("up   down  key : gion select\n");
        func_800149C0("left right key : xa   select\n");
        func_800149C0("maru    button : sd   call\n");
        func_800149C0("batsu   button : xa   call\n");
        func_800149C0("shikaku button : seq  call\n");
        func_800149C0("sankaku button : off\n");
        func_800149C0("start      key : exit\n");
        func_800149C0("\n");
        func_800149C0("sd  code :%s\n", D_801800D8[D_80181214]);
        func_800149C0("xa  code :%s\n", D_80180298[D_80181218]);
        func_800149C0("seq code :%s\n", D_801802D8[D_8018121C]);
        if (g_pads[0].repeat & PAD_UP) {
            D_80181214++;
            if (D_80181214 > 102) {
                D_80181214 = 102;
            }
        }
        if (g_pads[0].repeat & PAD_DOWN) {
            D_80181214--;
            if (D_80181214 < 0) {
                D_80181214 = 0;
            }
        }
        if (g_pads[0].tapped & PAD_CIRCLE) {
            g_api.PlaySfx(D_80180008[D_80181214]);
        }
        if (g_pads[0].repeat & PAD_RIGHT) {
            D_80181218++;
            if (D_80181218 > 15) {
                D_80181218 = 15;
            }
        }
        if (g_pads[0].repeat & PAD_LEFT) {
            D_80181218--;
            if (D_80181218 < 0) {
                D_80181218 = 0;
            }
        }
        if (g_pads[0].tapped & PAD_CROSS) {
            D_80180006 = D_80180278[D_80181218];
            g_api.PlaySfx(D_80180006);
        }
        if (g_pads[0].tapped & PAD_SQUARE) {
            g_api.PlaySfx(D_801802D4[D_8018121C]);
        }
        if (g_pads[0].tapped & PAD_TRIANGLE) {
            g_api.PlaySfx(SET_UNK_13);
            D_80180006 = 0;
            D_80180004 = 0;
            return;
        }
        break;
    case 3:
        if (g_api.func_80131F68() != 1) {
            g_api.FreePrimitives(D_80181210);
            func_801811B8();
            func_801811F8(1);
        }
        break;
    }
}

INCLUDE_ASM("sd/nonmatchings/sd", func_80180ECC);

INCLUDE_ASM("sd/nonmatchings/sd", func_80180F14);

INCLUDE_ASM("sd/nonmatchings/sd", func_80180FA0);

INCLUDE_ASM("sd/nonmatchings/sd", func_80180FD4);

s32 func_8018106C(void) { return D_800828B8 != 0; }

void func_8018107C(s32 arg0) {
    g_GpuBuffers[0].draw.clip.y = 0x0014;
    g_GpuBuffers[0].draw.clip.h = 0x00CF;
    if (!arg0) {
        g_GpuBuffers[1].draw.clip.y = 0x0014;
    } else {
        g_GpuBuffers[1].draw.clip.y = 0x0114;
    }
    g_GpuBuffers[1].draw.clip.h = 0x00CF;
    g_GpuBuffers[0].draw.isbg = g_GpuBuffers[1].draw.isbg = 1;
    g_GpuBuffers[0].draw.r0 = 0;
    g_GpuBuffers[0].draw.g0 = 0;
    g_GpuBuffers[0].draw.b0 = 0;
    g_GpuBuffers[1].draw.r0 = 0;
    g_GpuBuffers[1].draw.g0 = 0;
    g_GpuBuffers[1].draw.b0 = 0;
    g_GpuBuffers[0].disp.isrgb24 = g_GpuBuffers[1].disp.isrgb24 = 0;
}

static void SetDisplayBuffer(s16 width) {
    SetDefDrawEnv(&g_GpuBuffers[0].draw, 0, 0, width, 240);
    SetDefDrawEnv(&g_GpuBuffers[1].draw, 0, 256, width, 240);
    SetDefDispEnv(&g_GpuBuffers[0].disp, 0, 256, width, 240);
    SetDefDispEnv(&g_GpuBuffers[1].disp, 0, 0, width, 240);
    func_8018107C(1);
}

static void func_801811B8(void) {
    RECT rect;

    rect.x = 0;
    rect.y = 0;
    rect.w = 0x200;
    rect.h = 0x200;
    func_80011628(&rect, 0, 0, 0);
}

static void func_801811F8(s32 arg0) {
    D_8005150C = arg0;
    D_80088FE8 = 0;
}

static s16 D_80180008[] = {
    0x501, // SD_IDO
    0x502, // SD_KETT
    0x529, // SD_ATARI_1
    0x52A, // SD_ATARI_2
    0x52B, // SD_ATARI_3
    0x52C, // SD_ATARI_4
    0x52D, // SD_CRY_F
    0x52E, // SD_CRY_FL
    0x52F, // SD_CRY_M
    0x530, // SD_CRY_ML
    0x531, // SD_HONE_OUT
    0x532, // SD_ZOUT_FIRE
    0x533, // SD_Z_OUT1
    0x534, // SD_Z_OUT2
    0x535, // SD_Z_OUT3
    0x536, // SD_Z_SHOT1
    0x537, // SD_BAKU_1
    0x538, // SD_BAKU_2
    0x539, // SD_BAKU_3
    0x53A, // SD_BAKU_4
    0x53B, // SD_BAKU_5
    0x53C, // SD_BAKU_6
    0x520, // SD_KAIFUKU
    0x521, // SD_KEN_1
    0x522, // SD_KEN_2
    0x523, // SD_KEN_HOU
    0x524, // SD_KEN_KEN
    0x525, // SD_KEN_SOU
    0x526, // SD_KEN_THUN
    0x50F, // SD_TYAKU1
    0x527, // SD_TYAKU2
    0x510, // SD_AL_DM1
    0x511, // SD_AL_DM2
    0x512, // SD_AL_DM3
    0x513, // SD_AL_DM4
    0x514, // SD_AL_DM5
    0x515, // SD_AL_DM6
    0x516, // SD_AL_DM7
    0x517, // SD_AL_FUN
    0x518, // SD_AL_HA
    0x519, // SD_AL_TEI
    0x51A, // SD_AL_TOU
    0x51B, // SD_AL_OUT
    0x528, // SD_NAGE
    0x503, // SD_CANDLE
    0x504, // SD_HART_GET
    0x505, // SD_ITEMGET
    0x506, // SD_MENZAI
    0x507, // SD_MOZE
    0x508, // SD_NOA
    0x509, // SD_PENTA_A
    0x50A, // SD_PENTA_B
    0x50B, // SD_ROZARIO
    0x50C, // SD_SEISUI
    0x50D, // SD_DOOR
    0x50E, // SD_IWA
    0x55A, // SD_ELA02A
    0x55B, // SD_ELA02B
    0x55C, // SD_ELA02C
    0x55D, // SD_ELA02D
    0x55E, // SD_ELA02E
    0x55F, // SD_ELA02F
    0x560, // SD_ELA02G
    0x561, // SD_ELA02H
    0x562, // SD_ELA02I
    0x563, // SD_ELA02J
    0x564, // SD_ELA02K
    0x565, // SD_ELA02L
    0x566, // SD_ELA02M
    0x567, // SD_ELA02N
    0x568, // SD_ELA02O
    0x569, // SD_ELA02P
    0x56A, // SD_ELA02S
    0x56B, // SD_ELA02T
    0x56C, // SD_ELA02U
    0x56D, // SD_ELA02V
    0x56E, // SD_ELA02W
    0x56F, // SD_ELA02X
    0x570, // SD_ELA02Y
    0x571, // SD_ELA02Z
    0x572, // SD_ELA02XA
    0x573, // SD_ELA02XB
    0x662, // SD_BOSYA5A
    0x663, // SD_BOSYA5C
    0x664, // SD_BOSYA5D
    0x665, // SD_BOSYA5E
    0x666, // SD_BOSYA5F
    0x667, // SD_BOSYA5G
    0x668, // SD_BOSYA5H
    0x669, // SD_BOSYA5J
    0x66A, // SD_BOSYA5K
    0x66B, // SD_BOSYA5L
    0x66C, // SD_BOSYA5M
    0x66D, // SD_BOSYA5N
    0x5C0, // SD_MAK2A
    0x5C1, // SD_MAK2B
    0x5C2, // SD_MAK2C
    0x5C3, // SD_MAK2D
    0x5C4, // SD_MAK2E
    0x5C5, // SD_MAK2F
    0x5C6, // SD_MAK2G
    0x5C7, // SD_MAK2H2
    0x5C8, // SD_MAK2I
    0x5C9, // SD_MAK2J
};
static const char* D_801800D8[] = {
    "SD_IDO",      "SD_KETT",      "SD_ATARI_1", "SD_ATARI_2",  "SD_ATARI_3",
    "SD_ATARI_4",  "SD_CRY_F",     "SD_CRY_FL",  "SD_CRY_M",    "SD_CRY_ML",
    "SD_HONE_OUT", "SD_ZOUT_FIRE", "SD_Z_OUT1",  "SD_Z_OUT2",   "SD_Z_OUT3",
    "SD_Z_SHOT1",  "SD_BAKU_1",    "SD_BAKU_2",  "SD_BAKU_3",   "SD_BAKU_4",
    "SD_BAKU_5",   "SD_BAKU_6",    "SD_KAIFUKU", "SD_KEN_1",    "SD_KEN_2",
    "SD_KEN_HOU",  "SD_KEN_KEN",   "SD_KEN_SOU", "SD_KEN_THUN", "SD_TYAKU1",
    "SD_TYAKU2",   "SD_AL_DM1",    "SD_AL_DM2",  "SD_AL_DM3",   "SD_AL_DM4",
    "SD_AL_DM5",   "SD_AL_DM6",    "SD_AL_DM7",  "SD_AL_FUN",   "SD_AL_HA",
    "SD_AL_TEI",   "SD_AL_TOU",    "SD_AL_OUT",  "SD_NAGE",     "SD_CANDLE",
    "SD_HART_GET", "SD_ITEMGET",   "SD_MENZAI",  "SD_MOZE",     "SD_NOA",
    "SD_PENTA_A",  "SD_PENTA_B",   "SD_ROZARIO", "SD_SEISUI",   "SD_DOOR",
    "SD_IWA",      "SD_ELA02A",    "SD_ELA02B",  "SD_ELA02C",   "SD_ELA02D",
    "SD_ELA02E",   "SD_ELA02F",    "SD_ELA02G",  "SD_ELA02H",   "SD_ELA02I",
    "SD_ELA02J",   "SD_ELA02K",    "SD_ELA02L",  "SD_ELA02M",   "SD_ELA02N",
    "SD_ELA02O",   "SD_ELA02P",    "SD_ELA02S",  "SD_ELA02T",   "SD_ELA02U",
    "SD_ELA02V",   "SD_ELA02W",    "SD_ELA02X",  "SD_ELA02Y",   "SD_ELA02Z",
    "SD_ELA02XA",  "SD_ELA02XB",   "SD_BOSYA5A", "SD_BOSYA5C",  "SD_BOSYA5D",
    "SD_BOSYA5E",  "SD_BOSYA5F",   "SD_BOSYA5G", "SD_BOSYA5H",  "SD_BOSYA5J",
    "SD_BOSYA5K",  "SD_BOSYA5L",   "SD_BOSYA5M", "SD_BOSYA5N",  "SD_MAK2A",
    "SD_MAK2B",    "SD_MAK2C",     "SD_MAK2D",   "SD_MAK2E",    "SD_MAK2F",
    "SD_MAK2G",    "SD_MAK2H2",    "SD_MAK2I",   "SD_MAK2J",
};

static s16 D_80180278[] = {
    MU_LOST_PAINTING,
    MU_CURSE_ZONE,
    MU_RAINBOW_CEMETERY,
    MU_WOOD_CARVING_PARTITA,
    0,
    0,
    MU_LOST_PAINTING,
    MU_CURSE_ZONE,
    MU_RAINBOW_CEMETERY,
    MU_WOOD_CARVING_PARTITA,
    0,
    0,
    0,
    0,
    MU_TOWER_OF_MIST,
};
static const char* D_80180298[] = {
    "SD_XA_ARTBGM1 ", // MU_LOST_PAINTING
    "SD_XA_BFSHITE1", // MU_CURSE_ZONE
    "SD_XA_KATABGM1", // MU_RAINBOW_CEMETERY
    "SD_XA_LIBBGM1 ", // MU_WOOD_CARVING_PARTITA
    "SD_XA_NBOSS1  ", //
    "SD_XA_OPENBGM ", //
    "SD_XA_ARTBGM1 ", // MU_LOST_PAINTING
    "SD_XA_BFSHITE1", // MU_CURSE_ZONE
    "SD_XA_KATABGM1", // MU_RAINBOW_CEMETERY
    "SD_XA_LIBBGM1 ", // MU_WOOD_CARVING_PARTITA
    "SD_XA_NBOSS1  ", //
    "SD_XA_OPENBGM ", //
    "SD_XA_ROUKABG1", //
    "SD_XA_SHIROBG1", //
    "SD_XA_TOUBGM1 ", // MU_TOWER_OF_MIST
};

static s16 D_801802D4[] = {SD_SEQ_LIBRARY};
static const char* D_801802D8[] = {"SD_SEQ_LIBRARY"};
