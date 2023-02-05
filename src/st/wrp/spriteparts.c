#include "stage.h"

SpriteParts D_80186DA4;
SpriteParts D_80186DC0;
SpriteParts D_80186DDC;
SpriteParts D_80186DF8;
SpriteParts D_80186E14;
SpriteParts* D_80186D88[] = {
    /* 6D88 */ 0x00000000,
    /* 6D8C */ &D_80186DA4,
    /* 6D90 */ &D_80186DC0,
    /* 6D94 */ &D_80186DDC,
    /* 6D98 */ &D_80186DF8,
    /* 6D9C */ &D_80186E14,
    /* 6DA0 */ 0x00000000,
};

SpriteParts D_80186DA4 = {
    1,
    {0, -4, -4, 8, 8, 6, 60, 128, 128, 136, 136},
};

SpriteParts D_80186DC0 = {
    1,
    {0, -4, -4, 8, 8, 6, 60, 128, 136, 136, 144},
};

SpriteParts D_80186DDC = {
    1,
    {0, -4, -8, 8, 16, 6, 60, 128, 144, 136, 160},
};

SpriteParts D_80186DF8 = {
    1,
    {0, -8, -8, 16, 16, 6, 60, 136, 128, 152, 144},
};

SpriteParts D_80186E14 = {
    1,
    {0, -8, -8, 16, 16, 6, 60, 136, 144, 152, 160},
};
