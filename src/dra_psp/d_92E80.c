// SPDX-License-Identifier: AGPL-3.0-or-later
#include <game.h>

typedef struct {
    u16 frame;
    s16 pivotX;
    s16 pivotY;
    u16 clut;
} AluFrame;

static AluFrame D_psp_0916FC28;
static AluFrame D_psp_0916FC30;
static AluFrame D_psp_0916FC38;
static AluFrame D_psp_0916FC40;
static AluFrame D_psp_0916FC48;
static AluFrame D_psp_0916FC50;
static AluFrame D_psp_0916FC58;
static AluFrame D_psp_0916FC60;
static AluFrame D_psp_0916FC68;
static AluFrame D_psp_0916FC70;
static AluFrame D_psp_0916FC78;
static AluFrame D_psp_0916FC80;
static AluFrame D_psp_0916FC88;
static AluFrame D_psp_0916FC90;
static AluFrame D_psp_0916FC98;
static AluFrame D_psp_0916FCA0;
static AluFrame D_psp_0916FCA8;
static AluFrame D_psp_0916FCB0;
static AluFrame D_psp_0916FCB8;
static AluFrame D_psp_0916FCC0;
static AluFrame D_psp_0916FCC8;
static AluFrame D_psp_0916FCD0;
static AluFrame D_psp_0916FCD8;
static AluFrame D_psp_0916FCE0;
static AluFrame D_psp_0916FCE8;
static AluFrame D_psp_0916FCF0;
static AluFrame D_psp_0916FCF8;
static AluFrame D_psp_0916FD00;
static AluFrame D_psp_0916FD08;
static AluFrame D_psp_0916FD10;
static AluFrame D_psp_0916FD18;
static AluFrame D_psp_0916FD20;
static AluFrame D_psp_0916FD28;
static AluFrame D_psp_0916FD30;
static AluFrame D_psp_0916FD38;
static AluFrame D_psp_0916FD40;
static AluFrame D_psp_0916FD48;
static AluFrame D_psp_0916FD50;
static AluFrame D_psp_0916FD58;
static AluFrame D_psp_0916FD60;
static AluFrame D_psp_0916FD68;
static AluFrame D_psp_0916FD70;
static AluFrame D_psp_0916FD78;
static AluFrame D_psp_0916FD80;
static AluFrame D_psp_0916FD88;
static AluFrame D_psp_0916FD90;
static AluFrame D_psp_0916FD98;
static AluFrame D_psp_0916FDA0;
static AluFrame D_psp_0916FDA8;
static AluFrame D_psp_0916FDB0;
static AluFrame D_psp_0916FDB8;
static AluFrame D_psp_0916FDC0;
static AluFrame D_psp_0916FDC8;
static AluFrame D_psp_0916FDD0;
static AluFrame D_psp_0916FDD8;
static AluFrame D_psp_0916FDE0;
static AluFrame D_psp_0916FDE8;
static AluFrame D_psp_0916FDF0;
static AluFrame D_psp_0916FDF8;
static AluFrame D_psp_0916FE00;
static AluFrame D_psp_0916FE08;
static AluFrame D_psp_0916FE10;
static AluFrame D_psp_0916FE18;
static AluFrame D_psp_0916FE20;
static AluFrame D_psp_0916FE28;
static AluFrame D_psp_0916FE30;
static AluFrame D_psp_0916FE38;
static AluFrame D_psp_0916FE40;
static AluFrame D_psp_0916FE48;
static AluFrame D_psp_0916FE50;
static AluFrame D_psp_0916FE58;
static AluFrame D_psp_0916FE60;
static AluFrame D_psp_0916FE68;
static AluFrame D_psp_0916FE70;
static AluFrame D_psp_0916FE78;
static AluFrame D_psp_0916FE80;
static AluFrame D_psp_0916FE88;
static AluFrame D_psp_0916FE90;
static AluFrame D_psp_0916FE98;
static AluFrame D_psp_0916FEA0;
static AluFrame D_psp_0916FEA8;
static AluFrame D_psp_0916FEB0;
static AluFrame D_psp_0916FEB8;
static AluFrame D_psp_0916FEC0;
static AluFrame D_psp_0916FEC8;
static AluFrame D_psp_0916FED0;
static AluFrame D_psp_0916FED8;
static AluFrame D_psp_0916FEE0;
static AluFrame D_psp_0916FEE8;
static AluFrame D_psp_0916FEF0;
static AluFrame D_psp_0916FEF8;
static AluFrame D_psp_0916FF00;
static AluFrame D_psp_0916FF08;
static AluFrame D_psp_0916FF10;
static AluFrame D_psp_0916FF18;
static AluFrame D_psp_0916FF20;
static AluFrame D_psp_0916FF28;
static AluFrame D_psp_0916FF30;
static AluFrame D_psp_0916FF38;
static AluFrame D_psp_0916FF40;
static AluFrame D_psp_0916FF48;
static AluFrame D_psp_0916FF50;
static AluFrame D_psp_0916FF58;
static AluFrame D_psp_0916FF60;
static AluFrame D_psp_0916FF68;
static AluFrame D_psp_0916FF70;
static AluFrame D_psp_0916FF78;
static AluFrame D_psp_0916FF80;
static AluFrame D_psp_0916FF88;
static AluFrame D_psp_0916FF90;
static AluFrame D_psp_0916FF98;
static AluFrame D_psp_0916FFA0;
static AluFrame D_psp_0916FFA8;
static AluFrame D_psp_0916FFB0;
static AluFrame D_psp_0916FFB8;
static AluFrame D_psp_0916FFC0;
static AluFrame D_psp_0916FFC8;
static AluFrame D_psp_0916FFD0;
static AluFrame D_psp_0916FFD8;
static AluFrame D_psp_0916FFE0;
static AluFrame D_psp_0916FFE8;
static AluFrame D_psp_0916FFF0;
static AluFrame D_psp_0916FFF8;
static AluFrame D_psp_09170000;
static AluFrame D_psp_09170008;
static AluFrame D_psp_09170010;
static AluFrame D_psp_09170018;
static AluFrame D_psp_09170020;
static AluFrame D_psp_09170028;
static AluFrame D_psp_09170030;
static AluFrame D_psp_09170038;
static AluFrame D_psp_09170040;
static AluFrame D_psp_09170048;
static AluFrame D_psp_09170050;
static AluFrame D_psp_09170058;
static AluFrame D_psp_09170060;
static AluFrame D_psp_09170068;
static AluFrame D_psp_09170070;
static AluFrame D_psp_09170078;
static AluFrame D_psp_09170080;
static AluFrame D_psp_09170088;
static AluFrame D_psp_09170090;
static AluFrame D_psp_09170098;
static AluFrame D_psp_091700A0;
static AluFrame D_psp_091700A8;
static AluFrame D_psp_091700B0;
static AluFrame D_psp_091700B8;
static AluFrame D_psp_091700C0;
static AluFrame D_psp_091700C8;
static AluFrame D_psp_091700D0;
static AluFrame D_psp_091700D8;
static AluFrame D_psp_091700E0;
static AluFrame D_psp_091700E8;
static AluFrame D_psp_091700F0;
static AluFrame D_psp_091700F8;
static AluFrame D_psp_09170100;
static AluFrame D_psp_09170108;
static AluFrame D_psp_09170110;
static AluFrame D_psp_09170118;
static AluFrame D_psp_09170120;
static AluFrame D_psp_09170128;
static AluFrame D_psp_09170130;
static AluFrame D_psp_09170138;
static AluFrame D_psp_09170140;
static AluFrame D_psp_09170148;
static AluFrame D_psp_09170150;
static AluFrame D_psp_09170158;
static AluFrame D_psp_09170160;
static AluFrame D_psp_09170168;
static AluFrame D_psp_09170170;
static AluFrame D_psp_09170178;
static AluFrame D_psp_09170180;
static AluFrame D_psp_09170188;
static AluFrame D_psp_09170190;
static AluFrame D_psp_09170198;
static AluFrame D_psp_091701A0;
static AluFrame D_psp_091701A8;
static AluFrame D_psp_091701B0;
static AluFrame D_psp_091701B8;
static AluFrame D_psp_091701C0;
static AluFrame D_psp_091701C8;
static AluFrame D_psp_091701D0;
static AluFrame D_psp_091701D8;
static AluFrame D_psp_091701E0;
static AluFrame D_psp_091701E8;
static AluFrame D_psp_091701F0;
static AluFrame D_psp_091701F8;
static AluFrame D_psp_09170200;
static AluFrame D_psp_09170208;
static AluFrame D_psp_09170210;
static AluFrame D_psp_09170218;
static AluFrame D_psp_09170220;
static AluFrame D_psp_09170228;
static AluFrame D_psp_09170230;
static AluFrame D_psp_09170238;
static AluFrame D_psp_09170240;
static AluFrame D_psp_09170248;
static AluFrame D_psp_09170250;
static AluFrame D_psp_09170258;
static AluFrame D_psp_09170260;
static AluFrame D_psp_09170268;
static AluFrame D_psp_09170270;
static AluFrame D_psp_09170278;
static AluFrame D_psp_09170280;
static AluFrame D_psp_09170288;
static AluFrame D_psp_09170290;
static AluFrame D_psp_09170298;
static AluFrame D_psp_091702A0;
static AluFrame D_psp_091702A8;
static AluFrame D_psp_091702B0;
static AluFrame D_psp_091702B8;
static AluFrame D_psp_091702C0;
static AluFrame D_psp_091702C8;
static AluFrame D_psp_091702D0;
static AluFrame D_psp_091702D8;
static AluFrame D_psp_091702E0;
static AluFrame D_psp_091702E8;
static AluFrame D_psp_091702F0;
static AluFrame D_psp_091702F8;
static AluFrame D_psp_09170300;
static AluFrame D_psp_09170308;
static AluFrame D_psp_09170310;
static AluFrame D_psp_09170318;
static AluFrame D_psp_09170320;
extern AluFrame D_psp_09234A30;
extern AluFrame D_psp_09234A38;
extern AluFrame D_psp_09234A40;
extern AluFrame D_psp_09234A48;
extern AluFrame D_psp_09234A50;
extern AluFrame D_psp_09234A58;
extern AluFrame D_psp_09234A60;
extern AluFrame D_psp_09234A68;
extern AluFrame D_psp_09234A70;
extern AluFrame D_psp_09234A78;
extern AluFrame D_psp_09234A80;
extern AluFrame D_psp_09234A88;
extern AluFrame D_psp_09234A90;
extern AluFrame D_psp_09234A98;
extern AluFrame D_psp_09234AA0;
extern AluFrame D_psp_09234AA8;
extern AluFrame D_psp_09234AB0;
extern AluFrame D_psp_09234AB8;
extern AluFrame D_psp_09234AC0;
extern AluFrame D_psp_09234AC8;
extern AluFrame D_psp_09234AD0;
extern AluFrame D_psp_09234AD8;
extern AluFrame D_psp_09234AE0;
extern AluFrame D_psp_09234AE8;
extern AluFrame D_psp_09234AF0;
extern AluFrame D_psp_09234AF8;
extern AluFrame D_psp_09234B00;
extern AluFrame D_psp_09234B08;
extern AluFrame D_psp_09234B10;
extern AluFrame D_psp_09234B18;
extern AluFrame D_psp_09234B20;
extern AluFrame D_psp_09234B28;
extern AluFrame D_psp_09234B30;
extern AluFrame D_psp_09234B38;
extern AluFrame D_psp_09234B40;
extern AluFrame D_psp_09234B48;
extern AluFrame D_psp_09234B50;
extern AluFrame D_psp_09234B58;
extern AluFrame D_psp_09234B60;

AluFrame* D_800CF324[] = {
    NULL,
    &D_psp_0916FC28,
    &D_psp_0916FC30,
    &D_psp_0916FC38,
    &D_psp_0916FC40,
    &D_psp_0916FC48,
    &D_psp_0916FC50,
    &D_psp_0916FC58,
    &D_psp_0916FC60,
    &D_psp_0916FC68,
    &D_psp_0916FC70,
    &D_psp_0916FC78,
    &D_psp_0916FC80,
    &D_psp_0916FC88,
    &D_psp_0916FC90,
    &D_psp_0916FC98,
    &D_psp_0916FCA0,
    &D_psp_0916FCA8,
    &D_psp_0916FCB0,
    &D_psp_0916FCB8,
    &D_psp_0916FCC0,
    &D_psp_0916FCC8,
    &D_psp_0916FCD0,
    &D_psp_0916FCD8,
    &D_psp_0916FCE0,
    &D_psp_0916FCE8,
    &D_psp_0916FCF0,
    &D_psp_0916FCF8,
    &D_psp_0916FD00,
    &D_psp_0916FD08,
    &D_psp_0916FD10,
    &D_psp_0916FD18,
    &D_psp_0916FD20,
    &D_psp_0916FD28,
    &D_psp_0916FD30,
    &D_psp_0916FD38,
    &D_psp_0916FD40,
    &D_psp_0916FD48,
    &D_psp_0916FD50,
    &D_psp_0916FD58,
    &D_psp_0916FD60,
    &D_psp_0916FD68,
    &D_psp_0916FD70,
    &D_psp_0916FD78,
    &D_psp_0916FD80,
    &D_psp_0916FD88,
    &D_psp_0916FD90,
    &D_psp_0916FD98,
    &D_psp_0916FDA0,
    &D_psp_0916FDA8,
    &D_psp_0916FDB0,
    &D_psp_0916FDB8,
    &D_psp_0916FDC0,
    &D_psp_0916FDC8,
    &D_psp_0916FDD0,
    &D_psp_0916FDD8,
    &D_psp_0916FDE0,
    &D_psp_0916FDE8,
    &D_psp_0916FDF0,
    &D_psp_0916FDF8,
    &D_psp_0916FE00,
    &D_psp_0916FE08,
    &D_psp_0916FE10,
    &D_psp_0916FE18,
    &D_psp_0916FE20,
    &D_psp_0916FE28,
    &D_psp_0916FE30,
    &D_psp_0916FE38,
    &D_psp_0916FE40,
    &D_psp_0916FE48,
    &D_psp_0916FE50,
    &D_psp_0916FE58,
    &D_psp_0916FE60,
    &D_psp_0916FE68,
    &D_psp_0916FE70,
    &D_psp_0916FE78,
    &D_psp_0916FE80,
    &D_psp_0916FE88,
    &D_psp_0916FE90,
    &D_psp_0916FE98,
    &D_psp_0916FEA0,
    &D_psp_0916FEA8,
    &D_psp_0916FEB0,
    &D_psp_0916FEB8,
    &D_psp_0916FEC0,
    &D_psp_0916FEC8,
    &D_psp_0916FED0,
    &D_psp_0916FED8,
    &D_psp_0916FEE0,
    &D_psp_0916FEE8,
    &D_psp_0916FEF0,
    &D_psp_0916FEF8,
    &D_psp_0916FF00,
    &D_psp_0916FF08,
    &D_psp_0916FF10,
    &D_psp_0916FF18,
    &D_psp_0916FF20,
    &D_psp_0916FF28,
    &D_psp_0916FF30,
    &D_psp_0916FF38,
    &D_psp_0916FF40,
    &D_psp_0916FF48,
    &D_psp_0916FF50,
    &D_psp_0916FF58,
    &D_psp_0916FF60,
    &D_psp_0916FF68,
    &D_psp_0916FF70,
    &D_psp_0916FF78,
    &D_psp_0916FF80,
    &D_psp_0916FF88,
    &D_psp_0916FF90,
    &D_psp_0916FF98,
    &D_psp_0916FFA0,
    &D_psp_0916FFA8,
    &D_psp_0916FFB0,
    &D_psp_0916FFB8,
    &D_psp_0916FFC0,
    &D_psp_0916FFC8,
    &D_psp_0916FFD0,
    &D_psp_0916FFD8,
    &D_psp_0916FFE0,
    &D_psp_0916FFE8,
    &D_psp_0916FFF0,
    &D_psp_0916FFF8,
    &D_psp_09170000,
    &D_psp_09170008,
    &D_psp_09170010,
    &D_psp_09170018,
    &D_psp_09170020,
    &D_psp_09170028,
    &D_psp_09170030,
    &D_psp_09170038,
    &D_psp_09170040,
    &D_psp_09170048,
    &D_psp_09170050,
    &D_psp_09170058,
    &D_psp_09170060,
    &D_psp_09170068,
    &D_psp_09170070,
    &D_psp_09170078,
    &D_psp_09170080,
    &D_psp_09170088,
    &D_psp_09170090,
    &D_psp_09170098,
    &D_psp_091700A0,
    &D_psp_091700A8,
    &D_psp_091700B0,
    &D_psp_091700B8,
    &D_psp_091700C0,
    &D_psp_091700C8,
    &D_psp_091700D0,
    &D_psp_091700D8,
    &D_psp_091700E0,
    &D_psp_091700E8,
    &D_psp_091700F0,
    &D_psp_091700F8,
    &D_psp_09170100,
    &D_psp_09170108,
    &D_psp_09170110,
    &D_psp_09170118,
    &D_psp_09170120,
    &D_psp_09170128,
    &D_psp_09170130,
    &D_psp_09170138,
    &D_psp_09170140,
    &D_psp_09170148,
    &D_psp_09170150,
    &D_psp_09170158,
    &D_psp_09170160,
    &D_psp_09170168,
    &D_psp_09170170,
    &D_psp_09170178,
    &D_psp_09170180,
    &D_psp_09170188,
    &D_psp_09170190,
    &D_psp_09170198,
    &D_psp_091701A0,
    &D_psp_091701A8,
    &D_psp_091701B0,
    &D_psp_091701B8,
    &D_psp_091701C0,
    &D_psp_091701C8,
    &D_psp_091701D0,
    &D_psp_091701D8,
    &D_psp_091701E0,
    &D_psp_091701E8,
    &D_psp_091701F0,
    &D_psp_091701F8,
    &D_psp_09170200,
    &D_psp_09170208,
    &D_psp_09170210,
    &D_psp_09170218,
    &D_psp_09170220,
    &D_psp_09170228,
    &D_psp_09170230,
    &D_psp_09170238,
    &D_psp_09170240,
    &D_psp_09170248,
    &D_psp_09170250,
    &D_psp_09170258,
    &D_psp_09170260,
    &D_psp_09170268,
    &D_psp_09170270,
    &D_psp_09170278,
    &D_psp_09170280,
    &D_psp_09170288,
    &D_psp_09170290,
    &D_psp_09170298,
    &D_psp_091702A0,
    &D_psp_091702A8,
    &D_psp_091702B0,
    &D_psp_091702B8,
    &D_psp_091702C0,
    &D_psp_091702C8,
    &D_psp_091702D0,
    &D_psp_091702D8,
    &D_psp_091702E0,
    &D_psp_091702E8,
    &D_psp_091702F0,
    &D_psp_091702F8,
    &D_psp_09170300,
    &D_psp_09170308,
    &D_psp_09170310,
    &D_psp_09170318,
    &D_psp_09170320,
    &D_psp_09234A30,
    &D_psp_09234A38,
    &D_psp_09234A40,
    &D_psp_09234A48,
    &D_psp_09234A50,
    &D_psp_09234A58,
    &D_psp_09234A60,
    &D_psp_09234A68,
    &D_psp_09234A70,
    &D_psp_09234A78,
    &D_psp_09234A80,
    &D_psp_09234A88,
    &D_psp_09234A90,
    &D_psp_09234A98,
    &D_psp_09234AA0,
    &D_psp_09234AA8,
    &D_psp_09234AB0,
    &D_psp_09234AB8,
    &D_psp_09234AC0,
    &D_psp_09234AC8,
    &D_psp_09234AD0,
    &D_psp_09234AD8,
    &D_psp_09234AE0,
    &D_psp_09234AE8,
    &D_psp_09234AF0,
    &D_psp_09234AF8,
    &D_psp_09234B00,
    &D_psp_09234B08,
    &D_psp_09234B10,
    &D_psp_09234B18,
    &D_psp_09234B20,
    &D_psp_09234B28,
    &D_psp_09234B30,
    &D_psp_09234B38,
    &D_psp_09234B40,
    &D_psp_09234B48,
    &D_psp_09234B50,
    &D_psp_09234B58,
    &D_psp_09234B60,
    NULL,
};

static AluFrame D_psp_0916FC28 = {0x8000, 0xFFF0, 0xFFE9, 0x0000};
static AluFrame D_psp_0916FC30 = {0x8001, 0xFFD8, 0xFFE1, 0x0000};
static AluFrame D_psp_0916FC38 = {0x8002, 0xFFD8, 0xFFE1, 0x0000};
static AluFrame D_psp_0916FC40 = {0x8003, 0xFFD8, 0xFFE1, 0x0000};
static AluFrame D_psp_0916FC48 = {0x8004, 0xFFD8, 0xFFE1, 0x0000};
static AluFrame D_psp_0916FC50 = {0x8005, 0xFFD8, 0xFFE1, 0x0000};
static AluFrame D_psp_0916FC58 = {0x8006, 0xFFD8, 0xFFE1, 0x0000};
static AluFrame D_psp_0916FC60 = {0x8007, 0xFFD8, 0xFFE1, 0x0000};
static AluFrame D_psp_0916FC68 = {0x8008, 0xFFE0, 0xFFF1, 0x0000};
static AluFrame D_psp_0916FC70 = {0x8009, 0xFFE0, 0xFFF9, 0x0000};
static AluFrame D_psp_0916FC78 = {0x800A, 0xFFE0, 0xFFF9, 0x0000};
static AluFrame D_psp_0916FC80 = {0x800B, 0xFFE0, 0xFFF9, 0x0000};
static AluFrame D_psp_0916FC88 = {0x800C, 0xFFE0, 0xFFF9, 0x0000};
static AluFrame D_psp_0916FC90 = {0x800D, 0xFFE8, 0xFFF9, 0x0000};
static AluFrame D_psp_0916FC98 = {0x800E, 0xFFE8, 0xFFF9, 0x0000};
static AluFrame D_psp_0916FCA0 = {0x800F, 0xFFF0, 0xFFF1, 0x0000};
static AluFrame D_psp_0916FCA8 = {0x8010, 0xFFF0, 0xFFE9, 0x0000};
static AluFrame D_psp_0916FCB0 = {0x8011, 0xFFF0, 0xFFE9, 0x0000};
static AluFrame D_psp_0916FCB8 = {0x8012, 0xFFF0, 0xFFE9, 0x0000};
static AluFrame D_psp_0916FCC0 = {0x8013, 0xFFF0, 0xFFE9, 0x0000};
static AluFrame D_psp_0916FCC8 = {0x8014, 0xFFF0, 0xFFE9, 0x0000};
static AluFrame D_psp_0916FCD0 = {0x8015, 0xFFF0, 0xFFE9, 0x0000};
static AluFrame D_psp_0916FCD8 = {0x8016, 0xFFF0, 0xFFE9, 0x0000};
static AluFrame D_psp_0916FCE0 = {0x8017, 0xFFF0, 0xFFE9, 0x0000};
static AluFrame D_psp_0916FCE8 = {0x8018, 0xFFF0, 0xFFE9, 0x0000};
static AluFrame D_psp_0916FCF0 = {0x8019, 0xFFF0, 0xFFE9, 0x0000};
static AluFrame D_psp_0916FCF8 = {0x801A, 0xFFF0, 0xFFE9, 0x0000};
static AluFrame D_psp_0916FD00 = {0x801B, 0xFFF0, 0xFFE9, 0x0000};
static AluFrame D_psp_0916FD08 = {0x801C, 0xFFF0, 0xFFE9, 0x0000};
static AluFrame D_psp_0916FD10 = {0x801D, 0xFFE0, 0xFFE1, 0x0000};
static AluFrame D_psp_0916FD18 = {0x801E, 0xFFE0, 0xFFE1, 0x0000};
static AluFrame D_psp_0916FD20 = {0x801F, 0xFFE0, 0xFFE1, 0x0000};
static AluFrame D_psp_0916FD28 = {0x8020, 0xFFE0, 0xFFE1, 0x0000};
static AluFrame D_psp_0916FD30 = {0x8021, 0xFFE0, 0xFFE1, 0x0000};
static AluFrame D_psp_0916FD38 = {0x8022, 0xFFE0, 0xFFE1, 0x0000};
static AluFrame D_psp_0916FD40 = {0x8023, 0xFFE0, 0xFFE1, 0x0000};
static AluFrame D_psp_0916FD48 = {0x8024, 0xFFE0, 0xFFE1, 0x0000};
static AluFrame D_psp_0916FD50 = {0x8025, 0xFFE0, 0xFFE1, 0x0000};
static AluFrame D_psp_0916FD58 = {0x8026, 0xFFE0, 0xFFE1, 0x0000};
static AluFrame D_psp_0916FD60 = {0x8027, 0xFFE0, 0xFFE1, 0x0000};
static AluFrame D_psp_0916FD68 = {0x8028, 0xFFE8, 0xFFE9, 0x0000};
static AluFrame D_psp_0916FD70 = {0x8029, 0xFFE0, 0xFFE1, 0x0000};
static AluFrame D_psp_0916FD78 = {0x802A, 0xFFE0, 0xFFE1, 0x0000};
static AluFrame D_psp_0916FD80 = {0x802B, 0xFFE0, 0xFFE1, 0x0000};
static AluFrame D_psp_0916FD88 = {0x802C, 0xFFE0, 0xFFE1, 0x0000};
static AluFrame D_psp_0916FD90 = {0x802D, 0xFFE0, 0xFFE1, 0x0000};
static AluFrame D_psp_0916FD98 = {0x802E, 0xFFE0, 0xFFE1, 0x0000};
static AluFrame D_psp_0916FDA0 = {0x802F, 0xFFE0, 0xFFE1, 0x0000};
static AluFrame D_psp_0916FDA8 = {0x8030, 0xFFE0, 0xFFE1, 0x0000};
static AluFrame D_psp_0916FDB0 = {0x8031, 0xFFE0, 0xFFE1, 0x0000};
static AluFrame D_psp_0916FDB8 = {0x8032, 0xFFE0, 0xFFE1, 0x0000};
static AluFrame D_psp_0916FDC0 = {0x8033, 0xFFE0, 0xFFE1, 0x0000};
static AluFrame D_psp_0916FDC8 = {0x8034, 0xFFE0, 0xFFE1, 0x0000};
static AluFrame D_psp_0916FDD0 = {0x8035, 0xFFE0, 0xFFE1, 0x0000};
static AluFrame D_psp_0916FDD8 = {0x8036, 0xFFE0, 0xFFE1, 0x0000};
static AluFrame D_psp_0916FDE0 = {0x8037, 0xFFE0, 0xFFE1, 0x0000};
static AluFrame D_psp_0916FDE8 = {0x8038, 0xFFE0, 0xFFE1, 0x0000};
static AluFrame D_psp_0916FDF0 = {0x8039, 0xFFE0, 0xFFE1, 0x0000};
static AluFrame D_psp_0916FDF8 = {0x803A, 0xFFE0, 0xFFE1, 0x0000};
static AluFrame D_psp_0916FE00 = {0x803B, 0xFFE0, 0xFFE1, 0x0000};
static AluFrame D_psp_0916FE08 = {0x803C, 0xFFE0, 0xFFE1, 0x0000};
static AluFrame D_psp_0916FE10 = {0x803D, 0xFFE0, 0xFFE1, 0x0000};
static AluFrame D_psp_0916FE18 = {0x803E, 0xFFE0, 0xFFE1, 0x0000};
static AluFrame D_psp_0916FE20 = {0x803F, 0xFFE0, 0xFFE1, 0x0000};
static AluFrame D_psp_0916FE28 = {0x8040, 0xFFE0, 0xFFE1, 0x0000};
static AluFrame D_psp_0916FE30 = {0x8041, 0xFFE0, 0xFFE1, 0x0000};
static AluFrame D_psp_0916FE38 = {0x8042, 0xFFE0, 0xFFE9, 0x0000};
static AluFrame D_psp_0916FE40 = {0x8043, 0xFFE0, 0xFFE1, 0x0000};
static AluFrame D_psp_0916FE48 = {0x8044, 0xFFE0, 0xFFE1, 0x0000};
static AluFrame D_psp_0916FE50 = {0x8045, 0xFFE0, 0xFFE1, 0x0000};
static AluFrame D_psp_0916FE58 = {0x8046, 0xFFE0, 0xFFE1, 0x0000};
static AluFrame D_psp_0916FE60 = {0x8047, 0xFFE0, 0xFFE1, 0x0000};
static AluFrame D_psp_0916FE68 = {0x8048, 0xFFE0, 0xFFE1, 0x0000};
static AluFrame D_psp_0916FE70 = {0x8049, 0xFFE0, 0xFFE1, 0x0000};
static AluFrame D_psp_0916FE78 = {0x804A, 0xFFE0, 0xFFE1, 0x0000};
static AluFrame D_psp_0916FE80 = {0x804B, 0xFFE0, 0xFFE1, 0x0000};
static AluFrame D_psp_0916FE88 = {0x804C, 0xFFE0, 0xFFE1, 0x0000};
static AluFrame D_psp_0916FE90 = {0x804D, 0xFFE0, 0xFFE1, 0x0000};
static AluFrame D_psp_0916FE98 = {0x804E, 0xFFE0, 0xFFE1, 0x0000};
static AluFrame D_psp_0916FEA0 = {0x804F, 0xFFE0, 0xFFE9, 0x0000};
static AluFrame D_psp_0916FEA8 = {0x8050, 0xFFE0, 0xFFE1, 0x0000};
static AluFrame D_psp_0916FEB0 = {0x8051, 0xFFE0, 0xFFE1, 0x0000};
static AluFrame D_psp_0916FEB8 = {0x8052, 0xFFE0, 0xFFE1, 0x0000};
static AluFrame D_psp_0916FEC0 = {0x8053, 0xFFE0, 0xFFE1, 0x0000};
static AluFrame D_psp_0916FEC8 = {0x8054, 0xFFE0, 0xFFE1, 0x0000};
static AluFrame D_psp_0916FED0 = {0x8055, 0xFFE0, 0xFFE9, 0x0000};
static AluFrame D_psp_0916FED8 = {0x8056, 0xFFE0, 0xFFE1, 0x0000};
static AluFrame D_psp_0916FEE0 = {0x8057, 0xFFE0, 0xFFE1, 0x0000};
static AluFrame D_psp_0916FEE8 = {0x8058, 0xFFE0, 0xFFE1, 0x0000};
static AluFrame D_psp_0916FEF0 = {0x8059, 0xFFE0, 0xFFE1, 0x0000};
static AluFrame D_psp_0916FEF8 = {0x805A, 0xFFE0, 0xFFE1, 0x0000};
static AluFrame D_psp_0916FF00 = {0x805B, 0xFFE0, 0xFFE1, 0x0000};
static AluFrame D_psp_0916FF08 = {0x805C, 0xFFE0, 0xFFE1, 0x0000};
static AluFrame D_psp_0916FF10 = {0x805D, 0xFFE0, 0xFFE1, 0x0000};
static AluFrame D_psp_0916FF18 = {0x805E, 0xFFF0, 0xFFE1, 0x0000};
static AluFrame D_psp_0916FF20 = {0x805F, 0xFFF0, 0xFFE1, 0x0000};
static AluFrame D_psp_0916FF28 = {0x8060, 0xFFF0, 0xFFE1, 0x0000};
static AluFrame D_psp_0916FF30 = {0x8061, 0xFFF0, 0xFFE1, 0x0000};
static AluFrame D_psp_0916FF38 = {0x8062, 0xFFE0, 0xFFE1, 0x0000};
static AluFrame D_psp_0916FF40 = {0x8063, 0xFFE0, 0xFFE1, 0x0000};
static AluFrame D_psp_0916FF48 = {0x8064, 0xFFE0, 0xFFE1, 0x0000};
static AluFrame D_psp_0916FF50 = {0x8065, 0xFFE0, 0xFFE1, 0x0000};
static AluFrame D_psp_0916FF58 = {0x8066, 0xFFF0, 0xFFE1, 0x0000};
static AluFrame D_psp_0916FF60 = {0x8067, 0xFFF0, 0xFFE1, 0x0000};
static AluFrame D_psp_0916FF68 = {0x8068, 0xFFF0, 0xFFE1, 0x0000};
static AluFrame D_psp_0916FF70 = {0x8069, 0xFFD8, 0xFFE1, 0x0000};
static AluFrame D_psp_0916FF78 = {0x806A, 0xFFD8, 0xFFE1, 0x0000};
static AluFrame D_psp_0916FF80 = {0x806B, 0xFFD8, 0xFFE1, 0x0000};
static AluFrame D_psp_0916FF88 = {0x806C, 0xFFD8, 0xFFE1, 0x0000};
static AluFrame D_psp_0916FF90 = {0x806D, 0xFFD8, 0xFFE1, 0x0000};
static AluFrame D_psp_0916FF98 = {0x806E, 0xFFD8, 0xFFE1, 0x0000};
static AluFrame D_psp_0916FFA0 = {0x806F, 0xFFD8, 0xFFE1, 0x0000};
static AluFrame D_psp_0916FFA8 = {0x8070, 0xFFD8, 0xFFD9, 0x0000};
static AluFrame D_psp_0916FFB0 = {0x8071, 0xFFD8, 0xFFD9, 0x0000};
static AluFrame D_psp_0916FFB8 = {0x8072, 0xFFD8, 0xFFD9, 0x0000};
static AluFrame D_psp_0916FFC0 = {0x8073, 0xFFE0, 0xFFE1, 0x0000};
static AluFrame D_psp_0916FFC8 = {0x8074, 0xFFE0, 0xFFE1, 0x0000};
static AluFrame D_psp_0916FFD0 = {0x8075, 0xFFE0, 0xFFE1, 0x0000};
static AluFrame D_psp_0916FFD8 = {0x8076, 0xFFE0, 0xFFE1, 0x0000};
static AluFrame D_psp_0916FFE0 = {0x8077, 0xFFE0, 0xFFE1, 0x0000};
static AluFrame D_psp_0916FFE8 = {0x8078, 0xFFF0, 0xFFE9, 0x0000};
static AluFrame D_psp_0916FFF0 = {0x8079, 0xFFF0, 0xFFE9, 0x0000};
static AluFrame D_psp_0916FFF8 = {0x807A, 0xFFF0, 0xFFE9, 0x0000};
static AluFrame D_psp_09170000 = {0x807B, 0xFFF8, 0xFFE1, 0x0000};
static AluFrame D_psp_09170008 = {0x807C, 0xFFF8, 0xFFE1, 0x0000};
static AluFrame D_psp_09170010 = {0x807D, 0xFFF8, 0xFFE1, 0x0000};
static AluFrame D_psp_09170018 = {0x807E, 0xFFF8, 0xFFE1, 0x0000};
static AluFrame D_psp_09170020 = {0x807F, 0xFFF8, 0xFFE1, 0x0000};
static AluFrame D_psp_09170028 = {0x8080, 0xFFF0, 0xFFF9, 0x0000};
static AluFrame D_psp_09170030 = {0x8081, 0xFFF0, 0xFFF9, 0x0000};
static AluFrame D_psp_09170038 = {0x8082, 0xFFE8, 0xFFFB, 0x0000};
static AluFrame D_psp_09170040 = {0x8083, 0xFFE8, 0xFFFB, 0x0000};
static AluFrame D_psp_09170048 = {0x8084, 0xFFD8, 0xFFE1, 0x0000};
static AluFrame D_psp_09170050 = {0x8085, 0xFFD8, 0xFFE1, 0x0000};
static AluFrame D_psp_09170058 = {0x8086, 0xFFD8, 0xFFE1, 0x0000};
static AluFrame D_psp_09170060 = {0x8087, 0xFFD8, 0xFFD9, 0x0000};
static AluFrame D_psp_09170068 = {0x8088, 0xFFE0, 0xFFD9, 0x0000};
static AluFrame D_psp_09170070 = {0x8089, 0xFFE0, 0xFFD9, 0x0000};
static AluFrame D_psp_09170078 = {0x808A, 0xFFD8, 0xFFD9, 0x0000};
static AluFrame D_psp_09170080 = {0x808B, 0xFFF0, 0xFFE1, 0x0000};
static AluFrame D_psp_09170088 = {0x808C, 0xFFE8, 0xFFD9, 0x0000};
static AluFrame D_psp_09170090 = {0x808D, 0xFFF0, 0xFFE1, 0x0000};
static AluFrame D_psp_09170098 = {0x808E, 0xFFF0, 0xFFE1, 0x0000};
static AluFrame D_psp_091700A0 = {0x808F, 0xFFF0, 0xFFE1, 0x0000};
static AluFrame D_psp_091700A8 = {0x8090, 0xFFF0, 0xFFE1, 0x0000};
static AluFrame D_psp_091700B0 = {0x8091, 0xFFF0, 0xFFE1, 0x0000};
static AluFrame D_psp_091700B8 = {0x8092, 0xFFE8, 0xFFE9, 0x0000};
static AluFrame D_psp_091700C0 = {0x8093, 0xFFE8, 0xFFE9, 0x0000};
static AluFrame D_psp_091700C8 = {0x8094, 0xFFE8, 0xFFE9, 0x0000};
static AluFrame D_psp_091700D0 = {0x8095, 0xFFE8, 0xFFE9, 0x0000};
static AluFrame D_psp_091700D8 = {0x8096, 0xFFE0, 0xFFE1, 0x0000};
static AluFrame D_psp_091700E0 = {0x8097, 0xFFE0, 0xFFB1, 0x0000};
static AluFrame D_psp_091700E8 = {0x8098, 0xFFE8, 0xFFE1, 0x0000};
static AluFrame D_psp_091700F0 = {0x8099, 0xFFE0, 0xFFE9, 0x0000};
static AluFrame D_psp_091700F8 = {0x809A, 0xFFE0, 0xFFE9, 0x0000};
static AluFrame D_psp_09170100 = {0x809B, 0xFFE8, 0xFFE9, 0x0000};
static AluFrame D_psp_09170108 = {0x809C, 0xFFF0, 0xFFE9, 0x0000};
static AluFrame D_psp_09170110 = {0x809D, 0xFFE5, 0xFFE5, 0x0000};
static AluFrame D_psp_09170118 = {0x809E, 0xFFF0, 0xFFE1, 0x0000};
static AluFrame D_psp_09170120 = {0x809E, 0xFFF0, 0xFFE0, 0x0000};
static AluFrame D_psp_09170128 = {0x809F, 0xFFF0, 0xFFE1, 0x0000};
static AluFrame D_psp_09170130 = {0x80A0, 0xFFF0, 0xFFE1, 0x0000};
static AluFrame D_psp_09170138 = {0x80A1, 0xFFF0, 0xFFE1, 0x0000};
static AluFrame D_psp_09170140 = {0x80A1, 0xFFF0, 0xFFE0, 0x0000};
static AluFrame D_psp_09170148 = {0x80A2, 0xFFE0, 0xFFE1, 0x0000};
static AluFrame D_psp_09170150 = {0x80A2, 0xFFDF, 0xFFE1, 0x0000};
static AluFrame D_psp_09170158 = {0x80A3, 0xFFE0, 0xFFE1, 0x0000};
static AluFrame D_psp_09170160 = {0x80A3, 0xFFDF, 0xFFE1, 0x0000};
static AluFrame D_psp_09170168 = {0x80A4, 0xFFE0, 0xFFE1, 0x0000};
static AluFrame D_psp_09170170 = {0x80A4, 0xFFE1, 0xFFE1, 0x0000};
static AluFrame D_psp_09170178 = {0x80A5, 0xFFE0, 0xFFE1, 0x0000};
static AluFrame D_psp_09170180 = {0x80A5, 0xFFE1, 0xFFE1, 0x0000};
static AluFrame D_psp_09170188 = {0x80A6, 0xFFE8, 0xFFE9, 0x009E};
static AluFrame D_psp_09170190 = {0x80A7, 0xFFF5, 0xFFE9, 0x009F};
static AluFrame D_psp_09170198 = {0x80A8, 0xFFB7, 0xFFD1, 0x009E};
static AluFrame D_psp_091701A0 = {0x80A9, 0xFFE0, 0xFFE1, 0x0000};
static AluFrame D_psp_091701A8 = {0x80AA, 0xFFD8, 0xFFE1, 0x0000};
static AluFrame D_psp_091701B0 = {0x80AB, 0xFFD8, 0xFFE1, 0x0000};
static AluFrame D_psp_091701B8 = {0x80AC, 0xFFD8, 0xFFE1, 0x0000};
static AluFrame D_psp_091701C0 = {0x80AD, 0xFFE0, 0xFFE1, 0x0000};
static AluFrame D_psp_091701C8 = {0x80AE, 0xFFE0, 0xFFE1, 0x0000};
static AluFrame D_psp_091701D0 = {0x80AF, 0xFFE0, 0xFFE1, 0x0000};
static AluFrame D_psp_091701D8 = {0x80B0, 0xFFE0, 0xFFE1, 0x0000};
static AluFrame D_psp_091701E0 = {0x80B1, 0xFFE0, 0xFFE1, 0x0000};
static AluFrame D_psp_091701E8 = {0x80B2, 0xFFE8, 0xFFE1, 0x0000};
static AluFrame D_psp_091701F0 = {0x80B3, 0xFFE0, 0xFFE9, 0x0000};
static AluFrame D_psp_091701F8 = {0x80B4, 0xFFE8, 0xFFE9, 0x0000};
static AluFrame D_psp_09170200 = {0x80B5, 0xFFE8, 0xFFE1, 0x0000};
static AluFrame D_psp_09170208 = {0x80B6, 0xFFE8, 0xFFE1, 0x0000};
static AluFrame D_psp_09170210 = {0x80B7, 0xFFF0, 0xFFE9, 0x0000};
static AluFrame D_psp_09170218 = {0x80B8, 0xFFF0, 0xFFE9, 0x0000};
static AluFrame D_psp_09170220 = {0x80B9, 0xFFF8, 0xFFE9, 0x0000};
static AluFrame D_psp_09170228 = {0x80BA, 0xFFF8, 0xFFE9, 0x0000};
static AluFrame D_psp_09170230 = {0x80BB, 0xFFF0, 0xFFE9, 0x0000};
static AluFrame D_psp_09170238 = {0x80BC, 0xFFF0, 0xFFE9, 0x0000};
static AluFrame D_psp_09170240 = {0x80BD, 0xFFE8, 0xFFF9, 0x0000};
static AluFrame D_psp_09170248 = {0x80BE, 0xFFE0, 0xFFF9, 0x0000};
static AluFrame D_psp_09170250 = {0x80BF, 0xFFE0, 0xFFF9, 0x0000};
static AluFrame D_psp_09170258 = {0x80C0, 0xFFE0, 0xFFF9, 0x0000};
static AluFrame D_psp_09170260 = {0x80C1, 0xFFE0, 0xFFF1, 0x0000};
static AluFrame D_psp_09170268 = {0x80C2, 0xFFE8, 0xFFF9, 0x0000};
static AluFrame D_psp_09170270 = {0x80C3, 0xFFE8, 0xFFF9, 0x0000};
static AluFrame D_psp_09170278 = {0x80C4, 0xFFE8, 0xFFF9, 0x0000};
static AluFrame D_psp_09170280 = {0x80C5, 0xFFF0, 0xFFF9, 0x0000};
static AluFrame D_psp_09170288 = {0x80C6, 0xFFF0, 0xFFF9, 0x0000};
static AluFrame D_psp_09170290 = {0x80C7, 0xFFF0, 0xFFF9, 0x0000};
static AluFrame D_psp_09170298 = {0x80C8, 0xFFF0, 0xFFF9, 0x0000};
static AluFrame D_psp_091702A0 = {0x80C9, 0xFFE0, 0xFFE1, 0x0000};
static AluFrame D_psp_091702A8 = {0x80CA, 0xFFD8, 0xFFE1, 0x0000};
static AluFrame D_psp_091702B0 = {0x80CB, 0xFFE0, 0xFFE9, 0x0000};
static AluFrame D_psp_091702B8 = {0x80CC, 0xFFE0, 0xFFE9, 0x0000};
static AluFrame D_psp_091702C0 = {0x80CD, 0xFFD8, 0xFFD9, 0x0000};
static AluFrame D_psp_091702C8 = {0x80CE, 0xFFE0, 0xFFD9, 0x0000};
static AluFrame D_psp_091702D0 = {0x80CF, 0xFFE0, 0xFFD9, 0x0000};
static AluFrame D_psp_091702D8 = {0x80D0, 0xFFE0, 0xFFD1, 0x0000};
static AluFrame D_psp_091702E0 = {0x80D1, 0xFFE0, 0xFFD1, 0x0000};
static AluFrame D_psp_091702E8 = {0x80D2, 0xFFE8, 0xFFF1, 0x0000};
static AluFrame D_psp_091702F0 = {0x80D3, 0xFFEE, 0xFFEA, 0x0000};
static AluFrame D_psp_091702F8 = {0x80D4, 0xFFF0, 0xFFEA, 0x0000};
static AluFrame D_psp_09170300 = {0x80D5, 0xFFF2, 0xFFEA, 0x0000};
static AluFrame D_psp_09170308 = {0x80D6, 0xFFEB, 0xFFEB, 0x0000};
static AluFrame D_psp_09170310 = {0x80D7, 0xFFED, 0xFFEB, 0x0000};
static AluFrame D_psp_09170318 = {0x80D8, 0xFFED, 0xFFEB, 0x0000};
static AluFrame D_psp_09170320 = {0x80D9, 0xFFF4, 0xFFEC, 0x0000};

u8 D_800C4CEC[] = {
    16,
    16,
    0,
    0,
#include "../dra/gen/D_800C4CEC.h"
};

u8 D_800C4D70[] = {
    16,
    16,
    0,
    0,
#include "../dra/gen/D_800C4D70.h"
};

u8 D_800C4DF4[] = {
    16,
    16,
    0,
    0,
#include "../dra/gen/D_800C4DF4.h"
};

u8 D_800C4E78[] = {
    16,
    16,
    0,
    0,
#include "../dra/gen/D_800C4E78.h"
};

u8 D_800C4EFC[] = {
    16,
    16,
    0,
    0,
#include "../dra/gen/D_800C4EFC.h"
};

u8 D_800C4F80[] = {
    16,
    16,
    0,
    0,
#include "../dra/gen/D_800C4F80.h"
};

u8 D_800C5004[] = {
    16,
    16,
    0,
    0,
#include "../dra/gen/D_800C5004.h"
};

u8 D_800C5088[] = {
    16,
    16,
    0,
    0,
#include "../dra/gen/D_800C5088.h"
};

u8 D_800C510C[] = {
    16,
    16,
    0,
    0,
#include "../dra/gen/D_800C510C.h"
};

u8 D_800C5190[] = {
    16,
    16,
    0,
    0,
#include "../dra/gen/D_800C5190.h"
};

u8 D_800C5214[] = {
    8,
    56,
    0,
    0,
#include "../dra/gen/D_800C5214.h"
};

u8* D_800C52F8[] = {
    D_800C4CEC, D_800C4D70, D_800C4DF4, D_800C4E78, D_800C4EFC, D_800C4F80,
    D_800C5004, D_800C5088, D_800C510C, D_800C5190, D_800C5214,
};

u8 g_GfxEquipIcon[] = {
#include "../dra/gen/g_GfxEquipIcon.h"
};
