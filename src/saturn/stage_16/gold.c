// SPDX-License-Identifier: AGPL-3.0-or-later
#include "sattypes.h"

extern char g_Stage16GoldText1[];
extern char g_Stage16GoldText25[];
extern char g_Stage16GoldText50[];
extern char g_Stage16GoldText100[];
extern char g_Stage16GoldText250[];
extern char g_Stage16GoldText400[];
extern char g_Stage16GoldText700[];
extern char g_Stage16GoldText1000[];
extern char g_Stage16GoldText2000[];
extern char g_Stage16GoldText5000[];

char* g_Stage16GoldCollectTexts[10] = {
    g_Stage16GoldText1,    g_Stage16GoldText25,   g_Stage16GoldText50,
    g_Stage16GoldText100,  g_Stage16GoldText250,  g_Stage16GoldText400,
    g_Stage16GoldText700,  g_Stage16GoldText1000, g_Stage16GoldText2000,
    g_Stage16GoldText5000,
};
