// SPDX-License-Identifier: AGPL-3.0-or-later
#include "sattypes.h"

#define STAGE_02_ENTRY(id) extern EntityEntry g_Stage02EntityEntry##id

extern EntityEntry g_EntityNoopEntry;
STAGE_02_ENTRY(00);
STAGE_02_ENTRY(01);
STAGE_02_ENTRY(02);
STAGE_02_ENTRY(03);
STAGE_02_ENTRY(04);
STAGE_02_ENTRY(05);
STAGE_02_ENTRY(06);
STAGE_02_ENTRY(08);
STAGE_02_ENTRY(09);
STAGE_02_ENTRY(10);
STAGE_02_ENTRY(11);
STAGE_02_ENTRY(12);
STAGE_02_ENTRY(13);
STAGE_02_ENTRY(14);
STAGE_02_ENTRY(15);
STAGE_02_ENTRY(16);
STAGE_02_ENTRY(17);
STAGE_02_ENTRY(18);
STAGE_02_ENTRY(19);
STAGE_02_ENTRY(20);
STAGE_02_ENTRY(22);
STAGE_02_ENTRY(23);
STAGE_02_ENTRY(24);
STAGE_02_ENTRY(25);
STAGE_02_ENTRY(26);
STAGE_02_ENTRY(27);
STAGE_02_ENTRY(28);
STAGE_02_ENTRY(29);
STAGE_02_ENTRY(30);
STAGE_02_ENTRY(31);
STAGE_02_ENTRY(32);
STAGE_02_ENTRY(33);
STAGE_02_ENTRY(34);
STAGE_02_ENTRY(35);
STAGE_02_ENTRY(36);
STAGE_02_ENTRY(37);
STAGE_02_ENTRY(38);
STAGE_02_ENTRY(39);
STAGE_02_ENTRY(40);
STAGE_02_ENTRY(41);
STAGE_02_ENTRY(42);
STAGE_02_ENTRY(43);
STAGE_02_ENTRY(44);
STAGE_02_ENTRY(45);
STAGE_02_ENTRY(46);
STAGE_02_ENTRY(47);
STAGE_02_ENTRY(48);
STAGE_02_ENTRY(49);
STAGE_02_ENTRY(50);
STAGE_02_ENTRY(51);
STAGE_02_ENTRY(52);
STAGE_02_ENTRY(53);
STAGE_02_ENTRY(54);
STAGE_02_ENTRY(55);
STAGE_02_ENTRY(56);
STAGE_02_ENTRY(57);
STAGE_02_ENTRY(58);
STAGE_02_ENTRY(59);
STAGE_02_ENTRY(60);
STAGE_02_ENTRY(70);
STAGE_02_ENTRY(71);
STAGE_02_ENTRY(73);
STAGE_02_ENTRY(74);
STAGE_02_ENTRY(75);
STAGE_02_ENTRY(76);

#undef STAGE_02_ENTRY

EntityEntry* g_Stage02EntityUpdates[78] = {
    &g_Stage02EntityEntry00, &g_Stage02EntityEntry01,
    &g_Stage02EntityEntry02, &g_Stage02EntityEntry03,
    &g_Stage02EntityEntry04, &g_Stage02EntityEntry05,
    &g_Stage02EntityEntry06, &g_EntityNoopEntry,
    &g_Stage02EntityEntry08, &g_Stage02EntityEntry09,
    &g_Stage02EntityEntry10, &g_Stage02EntityEntry11,
    &g_Stage02EntityEntry12, &g_Stage02EntityEntry13,
    &g_Stage02EntityEntry14, &g_Stage02EntityEntry15,
    &g_Stage02EntityEntry16, &g_Stage02EntityEntry17,
    &g_Stage02EntityEntry18, &g_Stage02EntityEntry19,
    &g_Stage02EntityEntry20, &g_EntityNoopEntry,
    &g_Stage02EntityEntry22, &g_Stage02EntityEntry23,
    &g_Stage02EntityEntry24, &g_Stage02EntityEntry25,
    &g_Stage02EntityEntry26, &g_Stage02EntityEntry27,
    &g_Stage02EntityEntry28, &g_Stage02EntityEntry29,
    &g_Stage02EntityEntry30, &g_Stage02EntityEntry31,
    &g_Stage02EntityEntry32, &g_Stage02EntityEntry33,
    &g_Stage02EntityEntry34, &g_Stage02EntityEntry35,
    &g_Stage02EntityEntry36, &g_Stage02EntityEntry37,
    &g_Stage02EntityEntry38, &g_Stage02EntityEntry39,
    &g_Stage02EntityEntry40, &g_Stage02EntityEntry41,
    &g_Stage02EntityEntry42, &g_Stage02EntityEntry43,
    &g_Stage02EntityEntry44, &g_Stage02EntityEntry45,
    &g_Stage02EntityEntry46, &g_Stage02EntityEntry47,
    &g_Stage02EntityEntry48, &g_Stage02EntityEntry49,
    &g_Stage02EntityEntry50, &g_Stage02EntityEntry51,
    &g_Stage02EntityEntry52, &g_Stage02EntityEntry53,
    &g_Stage02EntityEntry54, &g_Stage02EntityEntry55,
    &g_Stage02EntityEntry56, &g_Stage02EntityEntry57,
    &g_Stage02EntityEntry58, &g_Stage02EntityEntry59,
    &g_Stage02EntityEntry60, &g_EntityNoopEntry,
    &g_EntityNoopEntry, &g_EntityNoopEntry,
    &g_EntityNoopEntry, &g_EntityNoopEntry,
    &g_EntityNoopEntry, &g_EntityNoopEntry,
    &g_EntityNoopEntry, &g_EntityNoopEntry,
    &g_Stage02EntityEntry70, &g_Stage02EntityEntry71,
    &g_EntityNoopEntry, &g_Stage02EntityEntry73,
    &g_Stage02EntityEntry74, &g_Stage02EntityEntry75,
    &g_Stage02EntityEntry76, NULL,
};
