// SPDX-License-Identifier: AGPL-3.0-or-later
#include "sattypes.h"

void ModeGame(void);
void func_8011A9D8(void);
void func_0606B6F8(void);
void func_0606B760(void);
void func_0606BB4C(void);
void func_0606BEE4(void);
void func_0606C064(void);
void func_06074470(void);
void func_0606C774(void);
void func_0606C594(void);
void InitStatsAndGear(void);

typedef struct {
    void* equipDefs;
    void* unk04;
    void* destroyStageEntities;
    void* unk0C;
    void* unk10;
    void* unk14;
    void* unk18;
    void* unk1C;
    void* unk20;
    void* unk24;
    void* unk28;
    void* unk2C;
} SaturnGameApi;

SaturnGameApi g_ApiInit = {
    g_EquipDefs,   ModeGame, func_8011A9D8, func_0606B6F8,
    func_0606B760, func_0606BB4C, func_0606BEE4, func_0606C064,
    func_06074470, func_0606C774, func_0606C594, InitStatsAndGear,
};
