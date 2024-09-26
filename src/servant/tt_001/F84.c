// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include <servant.h>

extern s32 g_IsServantDestroyed;

#ifndef VERSION_PSP
/* func_us_80171864 uses pointers by a different naming scheme forcing
 * a breakout of ServantDesc.  Once that function is decompiled,
 * these structs should be able to be removed and the declaration
 * set to a  ServantDesc */
typedef struct {
    void (*Init)(s32 arg0);
    void (*Update)(Entity* self);
    void (*Unk08)(Entity* self);
    void (*Unk0C)(/*?*/);
    void (*Unk10)(/*?*/);
    void (*Unk14)(/*?*/);
    void (*Unk18)(/*?*/);
    void (*Unk1C)(/*?*/);
    void (*Unk20)(/*?*/);
    void (*Unk24)(/*?*/);
} ServantDesc_Brk1;

typedef struct {
    
    void (*Unk30)(/*?*/);
    void (*Unk34)(/*?*/);
    void (*Unk38)(/*?*/);
    void (*Unk3C)(Entity* self);
} ServantDesc_Brk2;

void func_us_80171624(s32 arg0);
void func_us_80171864(Entity* self);
void func_us_801720A4(Entity* self);
void func_us_801720AC(void);
void func_us_801720B4(void);
void func_us_801720BC(void);
void func_us_801720C4(void);
void func_us_801720CC(void);
void func_us_801720D4(void);
void func_us_801720DC(void);
void func_us_801720E4(Entity* self);
void func_us_8017246C(void);
void func_us_801728EC(void);
void func_us_801728F4(void);
void func_us_801728FC(void);
void DestroyServantEntity(Entity* self);

ServantDesc_Brk1 g_ServantDesc_Brk1 = {
    func_us_80171624, func_us_80171864, func_us_801720A4, func_us_801720AC,
    func_us_801720B4, func_us_801720BC, func_us_801720C4, func_us_801720CC,
    func_us_801720D4, func_us_801720DC};

void (*Unk28)(Entity* self) = &func_us_801720E4;
void (*Unk2C)(/*?*/) = &func_us_8017246C;

ServantDesc_Brk2 g_ServantDesc_Brk2 = {
    func_us_801728EC, func_us_801728F4, func_us_801728FC,
    DestroyServantEntity};
#endif

INCLUDE_ASM("servant/tt_001/nonmatchings/F84", func_us_80170F84);

INCLUDE_ASM("servant/tt_001/nonmatchings/F84", func_us_80171284);

#include "../check_entity_valid.h"

void func_us_80171560(void) {}

INCLUDE_ASM("servant/tt_001/nonmatchings/F84", func_us_80171568);

INCLUDE_ASM("servant/tt_001/nonmatchings/F84", func_us_80171624);

INCLUDE_ASM("servant/tt_001/nonmatchings/F84", func_us_80171864);

void func_us_801720A4(Entity* self) {}

void func_us_801720AC(void) {}

void func_us_801720B4(void) {}

void func_us_801720BC(void) {}

void func_us_801720C4(void) {}

void func_us_801720CC(void) {}

void func_us_801720D4(void) {}

void func_us_801720DC(void) {}

INCLUDE_ASM("servant/tt_001/nonmatchings/F84", func_us_801720E4);

INCLUDE_ASM("servant/tt_001/nonmatchings/F84", func_us_8017246C);

void func_us_801728EC(void) {}

void func_us_801728F4(void) {}

void func_us_801728FC(void) {}

#include "../destroy_servant_entity.h"

#ifndef VERSION_PSP
#include "../servant_update_anim.h"
#endif

#include "../../destroy_entity.h"

#ifndef VERSION_PSP
#include "../accumulate_toward_zero.h"
#include "../search_for_entity_in_range.h"
#endif

INCLUDE_ASM("servant/tt_001/nonmatchings/F84", func_us_80172C08);

INCLUDE_ASM("servant/tt_001/nonmatchings/F84", func_us_80172C4C);

INCLUDE_ASM("servant/tt_001/nonmatchings/F84", func_us_80172CC0);

INCLUDE_ASM("servant/tt_001/nonmatchings/F84", func_us_80172D10);

INCLUDE_ASM("servant/tt_001/nonmatchings/F84", func_us_80172EE8);

INCLUDE_ASM("servant/tt_001/nonmatchings/F84", func_us_801732BC);

INCLUDE_ASM("servant/tt_001/nonmatchings/F84", func_us_80173378);

INCLUDE_ASM("servant/tt_001/nonmatchings/F84", func_us_80173490);

INCLUDE_ASM("servant/tt_001/nonmatchings/F84", func_us_8017353C);

INCLUDE_RODATA("servant/tt_001/nonmatchings/F84", func_us_80170F60);
