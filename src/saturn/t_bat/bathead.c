// SPDX-License-Identifier: AGPL-3.0-or-later
#include "sattypes.h"

typedef struct {
    void (*Init)(s32 mode);
    PfnEntityUpdate Update;
    PfnEntityUpdate Unk08;
    PfnEntityUpdate Unk0C;
    PfnEntityUpdate Unk10;
    PfnEntityUpdate Unk14;
    PfnEntityUpdate Unk18;
    PfnEntityUpdate Unk1C;
    PfnEntityUpdate Unk20;
    PfnEntityUpdate Unk24;
    PfnEntityUpdate Unk28;
    PfnEntityUpdate Unk2C;
    PfnEntityUpdate Unk30;
    PfnEntityUpdate Unk34;
    PfnEntityUpdate Unk38;
    PfnEntityUpdate Unk3C;
} BatServantDesc;

void ServantInit(s32 mode);
void UpdateServantDefault(Entity* self);
void UpdateBatAttackMode(Entity* self);
void unused_339C(Entity* self);
void unused_33A4(Entity* self);
void unused_33AC(Entity* self);
void unused_33B4(Entity* self);
void func_060D0968(Entity* self);
void unused_33C4(Entity* self);
void unused_33CC(Entity* self);
void func_060D0A64(Entity* self);
void unused_3C0C(Entity* self);
void unused_3C14(Entity* self);
void unused_3C1C(Entity* self);
void unused_3C24(Entity* self);
void DestroyServantEntity(Entity* self);

BatServantDesc g_BatServantDesc = {
    ServantInit,          UpdateServantDefault, UpdateBatAttackMode,
    unused_339C,          unused_33A4,          unused_33AC,
    unused_33B4,          func_060D0968,        unused_33C4,
    unused_33CC,          func_060D0A64,        unused_3C0C,
    unused_3C14,          unused_3C1C,          unused_3C24,
    DestroyServantEntity,
};
