// SPDX-License-Identifier: AGPL-3.0-or-later
//! PSYQ=3.3 O=1
// Sound Data testing overlay
#define VERSION_SD
#include <game.h>
#include <sfx.h>

extern u16 D_800828B8;

void Entrypoint();
static void InputRepeatInit();
static void InputRepeatUpdate();
static void SetDisplayBuffer(s16 width);

void* header[] = {(void*)Entrypoint};
static s16 D_80180004 = 0;
static s16 D_80180006 = 0;
static s16 prim_index;
STATIC_PAD_BSS(2);
static s16 gion_idx; // gion = 擬音 = imitated sound = sound effect
STATIC_PAD_BSS(2);
static s16 xa_idx;
STATIC_PAD_BSS(2);
static s16 seq_idx;
STATIC_PAD_BSS(2);
s8 D_80181220[0x10];

static s16 sd_id[];
static const char* sd_codes[];
static s16 xa_ids[];
static const char* xa_codes[];
static s16 seq_ids[];
static const char* seq_codes[];

void Entrypoint(void) {
    Primitive* prim;

    if (g_GameStep) {
        InputRepeatUpdate();
    }
    switch (g_GameStep) {
    case 0:
        if (IsInit() == 0) {
            InputRepeatInit();
            SetDisplayBuffer(256);
            g_GameStep++;
        }
        break;
    case 1:
        prim_index = g_api.AllocPrimitives(PRIM_GT4, 1);
        prim = &g_PrimBuf[prim_index];
        prim->x0 = 0;
        prim->y0 = 0;
        prim->x1 = 255;
        prim->y1 = 0;
        prim->x2 = 0;
        prim->y2 = 223;
        prim->x3 = 255;
        prim->y3 = 223;
        prim->u0 = 0;
        prim->v0 = 0;
        prim->u1 = 255;
        prim->v1 = 0;
        prim->u2 = 0;
        prim->v2 = 223;
        prim->u3 = 255;
        prim->v3 = 223;
        prim->tpage = 0x100 | 8;
        prim->priority = 0;
        prim->drawMode = DRAW_TRANSP | DRAW_TPAGE;
        g_GameStep++;
        break;
    case 2:
        if (g_pads[0].tapped & PAD_START) {
            if (IsInit() == 0) {
                g_api.PlaySfx(SET_UNK_13);
                D_80180006 = 0;
                D_80180004 = 0;
                g_GameStep++;
            }
            break;
        }
        FntPrint("sound test mode vx010\n");
        FntPrint("\n");
        FntPrint("up   down  key : gion select\n");
        FntPrint("left right key : xa   select\n");
        FntPrint("maru    button : sd   call\n");
        FntPrint("batsu   button : xa   call\n");
        FntPrint("shikaku button : seq  call\n");
        FntPrint("sankaku button : off\n");
        FntPrint("start      key : exit\n");
        FntPrint("\n");
        FntPrint("sd  code :%s\n", sd_codes[gion_idx]);
        FntPrint("xa  code :%s\n", xa_codes[xa_idx]);
        FntPrint("seq code :%s\n", seq_codes[seq_idx]);
        if (g_pads[0].repeat & PAD_UP) {
            gion_idx++;
            if (gion_idx > 102) {
                gion_idx = 102;
            }
        }
        if (g_pads[0].repeat & PAD_DOWN) {
            gion_idx--;
            if (gion_idx < 0) {
                gion_idx = 0;
            }
        }
        if (g_pads[0].tapped & PAD_CIRCLE) {
            g_api.PlaySfx(sd_id[gion_idx]);
        }
        if (g_pads[0].repeat & PAD_RIGHT) {
            xa_idx++;
            if (xa_idx > 15) {
                xa_idx = 15;
            }
        }
        if (g_pads[0].repeat & PAD_LEFT) {
            xa_idx--;
            if (xa_idx < 0) {
                xa_idx = 0;
            }
        }
        if (g_pads[0].tapped & PAD_CROSS) {
            D_80180006 = xa_ids[xa_idx];
            g_api.PlaySfx(D_80180006);
        }
        if (g_pads[0].tapped & PAD_SQUARE) {
            g_api.PlaySfx(seq_ids[seq_idx]);
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
            g_api.FreePrimitives(prim_index);
            ClearScreen();
            SetGameState(Game_Title);
        }
        break;
    }
}

static void InputInit(void) {
    s32 i;
    Pad* pad;

    PadInit(0);
    pad = g_pads;
    for (i = 0; i < LEN(g_pads); i++) {
        pad->tapped = 0;
        pad->previous = 0;
        pad->pressed = 0;
        pad++;
    }
}

static void InputUpdate(void) {
    s32 i;
    Pad* pad;
    u32 buttons;

    pad = g_pads;
    i = 0;
    while (i < LEN(g_pads)) {
        pad->previous = pad->pressed;
        buttons = PadRead(i >> 1);
        if (!(i & 1)) {
            pad->pressed = buttons;
        } else {
            pad->pressed = buttons >> 0x10;
        }
        pad->tapped = (pad->pressed ^ pad->previous) & pad->pressed;
        i++;
        pad++;
    }
}

#define PAD_REPEAT_TIMER 24
static void InputRepeatInit(void) {
    s32 i;
    s8* ptr;

    g_pads[0].repeat = 0;
    ptr = D_80181220;
    for (i = 0; i < LEN(D_80181220); i++) {
        *ptr++ = PAD_REPEAT_TIMER;
    }
}

static void InputRepeatUpdate(void) {
    s8* timer;
    u16 mask;
    u16 bits;
    s32 i;
    u16 pressed;
    u16 tapped;

    mask = 1;
    tapped = g_pads[0].tapped;
    pressed = g_pads[0].pressed;
    bits = 0;
    timer = D_80181220;
    i = 0;
    while (i < LEN(D_80181220)) {
        if (pressed & mask) {
            if (tapped & mask) {
                bits |= mask;
                *timer = 24;
            } else {
                *timer = *timer - 1;
                if ((*timer & 0xFF) == 0xFF) {
                    bits |= mask;
                    *timer = 5;
                }
            }
        }
        i++;
        timer++;
        mask <<= 1;
    }
    g_pads[0].repeat = bits;
}

static s32 IsInit(void) { return D_800828B8 != 0; }

static void SetDrawBuffer(s32 arg0) {
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
    SetDrawBuffer(1);
}

static void ClearScreen(void) {
    RECT rect;

    rect.x = 0;
    rect.y = 0;
    rect.w = 512;
    rect.h = 512;
    ClearImage(&rect, 0, 0, 0);
}

static void SetGameState(GameState gameState) {
    g_GameState = gameState;
    g_GameStep = 0;
}

static s16 sd_id[] = {
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
static const char* sd_codes[] = {
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

static s16 xa_ids[] = {
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
static const char* xa_codes[] = {
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

static s16 seq_ids[] = {SD_SEQ_LIBRARY};
static const char* seq_codes[] = {"SD_SEQ_LIBRARY"};
