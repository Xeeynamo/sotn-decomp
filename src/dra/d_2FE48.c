// SPDX-License-Identifier: AGPL-3.0-or-later
#include <game.h>

static AluFrame D_800CFE90;
static AluFrame D_800CFE98;
static AluFrame D_800CFEA0;
static AluFrame D_800CFEA8;
static AluFrame D_800CFEB0;
static AluFrame D_800CFEB8;
static AluFrame D_800CFEC0;
static AluFrame D_800CFEC8;
static AluFrame D_800CFED0;
static AluFrame D_800CFED8;
static AluFrame D_800CFEE0;
static AluFrame D_800CFEE8;
static AluFrame D_800CFEF0;
static AluFrame D_800CFEF8;
static AluFrame D_800CFF00;
static AluFrame D_800CFF08;

AluFrame* D_800CFE48[] = {
    NULL,        &D_800CFE90, &D_800CFE98, &D_800CFEA0, &D_800CFEA8,
    &D_800CFEB0, &D_800CFEB8, &D_800CFEC0, &D_800CFEC8, &D_800CFED0,
    &D_800CFED8, &D_800CFEE0, &D_800CFEE8, &D_800CFEF0, &D_800CFEF8,
    &D_800CFF00, &D_800CFF08, NULL,
};

static AluFrame D_800CFE90 = {0x8000, -22, -48, 0};
static AluFrame D_800CFE98 = {0x8001, -22, -47, 0};
static AluFrame D_800CFEA0 = {0x8002, -22, -40, 0};
static AluFrame D_800CFEA8 = {0x8003, -22, -41, 0};
static AluFrame D_800CFEB0 = {0x8004, -22, -30, 0};
static AluFrame D_800CFEB8 = {0x8004, -22, -31, 0};
static AluFrame D_800CFEC0 = {0x8005, -22, -30, 0};
static AluFrame D_800CFEC8 = {0x8003, -22, -41, 0};
static AluFrame D_800CFED0 = {0x8002, -22, -41, 0};
static AluFrame D_800CFED8 = {0x8001, -22, -49, 0};
static AluFrame D_800CFEE0 = {0x8000, -22, -51, 0};
static AluFrame D_800CFEE8 = {0x8001, -22, -51, 0};
static AluFrame D_800CFEF0 = {0x8002, -22, -42, 0};
static AluFrame D_800CFEF8 = {0x8003, -22, -41, 0};
static AluFrame D_800CFF00 = {0x8004, -22, -29, 0};
static AluFrame D_800CFF08 = {0x8005, -22, -29, 0};

#include GEN_VERSION(D_800CFF10.h)

#include GEN_VERSION(D_800D0F68.h)

#include GEN_VERSION(D_800D2BF4.h)

#include GEN_VERSION(D_800D2CF8.h)

#include GEN_VERSION(D_800D2FFC.h)

#include GEN_VERSION(D_800D327C.h)

#include GEN_VERSION(D_800D3428.h)

#include GEN_VERSION(D_800D34B8.h)

#include GEN_VERSION(D_800D372C.h)

#include GEN_VERSION(D_800D3B88.h)

#include GEN_VERSION(D_800D5628.h)

#include GEN_VERSION(D_800D56AC.h)

#include GEN_VERSION(D_800D5868.h)

#include GEN_VERSION(D_800D684C.h)

u16 D_800D68D4[] = {
#include "gen/D_800D68D4.h"
};

u16 D_800D68F4[] = {
#include "gen/D_800D68F4.h"
};

u16 D_800D6914[] = {
#include "gen/D_800D6914.h"
};

u16 D_800D6934[] = {
#include "gen/D_800D6934.h"
};

u16 D_800D6954[] = {
#include "gen/D_800D6954.h"
};

u16 D_800D6974[] = {
#include "gen/D_800D6974.h"
};

u16 D_800D6994[] = {
#include "gen/D_800D6994.h"
};

u16 D_800D69B4[] = {
#include "gen/D_800D69B4.h"
};

u16 D_800D69D4[] = {
#include "gen/D_800D69D4.h"
};

u16 D_800D69F4[] = {
#include "gen/D_800D69F4.h"
};

u16 D_800D6A14[] = {
#include "gen/D_800D6A14.h"
};

u16 D_800D6A34[] = {
#include "gen/D_800D6A34.h"
};

u16 D_800D6AD4[] = {
#include "gen/D_800D6AD4.h"
};

u16 D_800D6CD4[] = {
#include "gen/D_800D6CD4.h"
};

u16 D_800D6ED4[] = {
#include "gen/D_800D6ED4.h"
};

u16 D_800D70D4[] = {
#include "gen/D_800D70D4.h"
};

u16 D_800D72D4[] = {
#include "gen/D_800D72D4.h"
};
