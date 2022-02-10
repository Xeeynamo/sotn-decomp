#include "common.h"
#include "dra.h"

extern u16 D_80180AAC[];
extern u8* D_80180E50[];
extern u8 D_80180E70[];
extern u8 D_80180E78[];
extern u16 D_80180E80[];
extern u8 D_80180E90[];
extern PfnEntityUpdate PfnEntityUpdates[];
extern s16 D_801820C4[];

void SpawnExplosionEntity(u16, Entity *);
u8 AnimateEntity(u8 *arg0, Entity *entity);
Entity* AllocEntity(Entity* arg0, Entity* arg1);
void InitializeEntity(u16 *arg0);
void ReplaceCandleWithDrop(Entity *);
void EntityCandleDrop(Entity*);
void EntityCandleHeartDrop(Entity*);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801B77D4);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801B78A8);

#ifndef NON_MATCHING
INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", EntityCandle);
#else
void EntityCandle(Entity *entity) {
    u16 temp_s0 = entity->subId >> 0xC;
    if (entity->unk2C) { // Is initialised?
        AnimateEntity(D_80180E50[temp_s0], entity);
        if (entity->unk44) { // If the candle is destroyed
            Entity *entityDropItem;
            D_8003C7DC(0x634);
            entityDropItem = AllocEntity(D_8007D858, D_8007D858 + MaxEntityCount);
            if (entityDropItem != NULL) {
                SpawnExplosionEntity(EntityExplosionID, entityDropItem);
                entityDropItem->subId = D_80180E78[temp_s0];
            }
            ReplaceCandleWithDrop(entity);
        }
    } else {
        InitializeEntity(D_80180AAC);
        entity->zPriority = D_80097408 - 0x14;
        entity->unk18 = D_80180E90[temp_s0];
        entity->hitboxHeight = D_80180E70[temp_s0];
        entity->animationSet = D_80180E80[temp_s0];
    }
}
#endif

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801B7B98);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801B7C4C);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801B8254);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801B8564);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801B8A74);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801B8ED0);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801B9198);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801B94F0);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801B9650);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801B97D0);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801B989C);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801B9C44);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801B9CE8);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801B9E10);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801BA0A0);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801BA348);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801BA4C0);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801BA868);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801BABE8);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801BAD6C);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801BAEF0);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801BB3BC);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801BB548);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801BBB8C);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801BBDC0);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801BBE70);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801BBF38);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801BC05C);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801BC3FC);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801BC4EC);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801BC780);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801BC93C);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801BCC4C);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801BCE08);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801BD564);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801BD71C);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801BDEB0);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801BE080);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801BE134);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801BE444);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801BE544);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801BE598);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801BE75C);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801BE7BC);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801BE870);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801BE9F4);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801BEA20);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801BECCC);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801BEDAC);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801BEEB0);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801BFF00);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801C033C);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801C083C);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801C11A4);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801C12E8);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801C13F8);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801C14B8);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801C184C);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801C187C);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801C1B78);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801C1C80);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", EntityDamage);

#ifndef NON_MATCHING
INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", CreateEntity);
#else
void CreateEntity(Entity* entity, ObjectInit* initDesc) {
    DestroyEntity(entity);
    entity->objectId = initDesc->unk4 & 0x3FF;
    entity->pfnUpdate = PfnEntityUpdates[entity->objectId];
    entity->posX.Data.high = initDesc->posX - D_8007308E;
    entity->posY.Data.high = initDesc->posY - D_80073092;
    entity->subId = initDesc->unk8;
    entity->unk32 = initDesc->unk6 >> 8;
    entity->unk68 = initDesc->unk4 >> 0xA & 7;
}
#endif

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801C3500);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801C3618);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801C3730);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801C377C);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801C37D4);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801C38D0);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801C39E4);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801C3A30);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801C3A88);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801C3B84);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", LoadObjLayout);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801C3E10);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", SpawnExplosionEntity);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801C3F38);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801C3FB4);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801C402C);

void DestroyEntity(Entity* item) {
    int i, length;
    u32* ptr;

    if (item->unk34 & 0x800000) {
        D_8003C7B4(item->unk64);
    }

    ptr = item;
    length = sizeof(Entity) / sizeof(s32);
    for (i = 0; i < length; i++)
        *ptr++ = 0;
}

void DestroyEntityFromIndex(s16 index) {
    Entity *entity = &D_800733D8[index];
    while (entity < &D_8007EF1C) {
        DestroyEntity(entity);
        entity++;
    }
}

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801C4D4C);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", AnimateEntity);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801C4E4C);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801C4F64);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801C4FA0);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801C4FD4);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801C5018);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801C5048);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801C5074);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801C52EC);

Entity* AllocEntity(Entity* start, Entity* end) {
    Entity* current = start;
    while (current < end)
    {
        if (current->objectId == 0)
        {
            DestroyEntity(current);
            return current;
        }

        current++;
    }
    return NULL;
}

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801C5534);

#ifndef NON_MATCHING
INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801C5560);
#else
s16 func_801C5560(s32 arg0) {
    return D_801820C4[arg0 & 0xFF];
}
#endif

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801C557C);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801C55E8);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801C5620);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801C5668);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801C56B0);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801C5708);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801C5794);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801C57C4);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801C57FC);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801C5844);

void func_801C58A4(s32 arg0) {
    D_8006C3B8->unk2C = (s16) (arg0 & 0xFF);
    D_8006C3B8->unk2E = 0;
    D_8006C3B8->animationFrameIndex = 0;
    D_8006C3B8->animationFrameDuration = 0;
}

void func_801C58C4(s32 arg0) {
    D_8006C3B8->unk2E = (s16) (arg0 & 0xFF);
    D_8006C3B8->animationFrameIndex = 0;
    D_8006C3B8->animationFrameDuration = 0;
}

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801C58E0);

void InitializeEntity(u16 *arg0) {
    u16 temp_v1;
    Unkstruct5 *temp_v0;

    D_8006C3B8->animationSet = *arg0++;
    D_8006C3B8->animationFrame = *arg0++;
    D_8006C3B8->unk5A = *arg0++;
    D_8006C3B8->palette = *arg0++;
    temp_v1 = *arg0++;
    D_8006C3B8->unk3A = temp_v1;
    temp_v0 = temp_v1 * sizeof(Unkstruct5) + (u32)D_8003C808;
    D_8006C3B8->unk3E = temp_v0->unk4;
    D_8006C3B8->unk40 = temp_v0->unk6;
    D_8006C3B8->unk42 = temp_v0->unk8;
    D_8006C3B8->unk3C = temp_v0->unkC;
    D_8006C3B8->hitboxWidth = temp_v0->hitboxWidth;
    D_8006C3B8->hitboxHeight = temp_v0->hitboxHeight;
    D_8006C3B8->unk34 = temp_v0->unk24;
    D_8006C3B8->unk10 = 0;
    D_8006C3B8->unk12 = 0;
    D_8006C3B8->unk2E = 0;
    D_8006C3B8->unk2C++;
    if (D_8006C3B8->zPriority == 0) {
        D_8006C3B8->zPriority = D_80097408 - 0xC;
    }
}

void func_801C5A70(Entity* arg0) {
    if (arg0->unk2C == 0) {
        arg0->unk2C++;
    }
}

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801C5A98);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801C5BC0);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801C5D18);

#ifndef NON_MATCHING
INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", ReplaceCandleWithDrop);
#else
extern u8 D_8009796E;
void ReplaceCandleWithDrop(Entity *entity) {
    u16 prevSubId;
    u16 subId;
    u16 newSubId;

    func_801C4D4C(entity);
    if ((D_8009796E & 2) == 0) {
        DestroyEntity(entity);
        return;
    }

    prevSubId = entity->subId;
    subId = prevSubId & 0xFFF;
    entity->subId = subId;
    if (prevSubId < 0x80) {
        entity->objectId = EntityCandleDropID;
        entity->pfnUpdate = EntityCandleDrop;
        entity->animationFrameDuration = 0;
        entity->animationFrameIndex = 0;
        newSubId = subId;
    } else {
        entity->objectId = EntityCandleHeartDropID;
        entity->pfnUpdate = EntityCandleHeartDrop;
        newSubId = subId - 0x80;
    }
    entity->subId = newSubId;
    entity->unk6D = 0x10;
    entity->unk2C = 0;
}
#endif

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801C6114);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801C6198);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801C62F4);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801C6374);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801C6450);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801C6568);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801C660C);

void func_801C665C(void) {
    DestroyEntity(D_8006C3B8);
}

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", EntityCandleDrop);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801C6EF8);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801C6FF4);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", EntityCandleHeartDrop);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801C7680);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801C7930);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801C8400);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801C8528);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801C8A84);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801C8B74);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801C8C84);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801C8DB4);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801C8E9C);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801C8F8C);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801C9080);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801C92B0);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801C93AC);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801C992C);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801C9A2C);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801C9AF8);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801C9BC0);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801C9C78);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801C9E50);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801CA430);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801CAB30);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801CAD28);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801CAE20);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", EntityAreaTitlePopup);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", EntityAbsorbOrb);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801CC008);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801CC4B8);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801CC5A4);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801CC6F8);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801CC820);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801CC90C);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801CC974);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801CDD80);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801CDF10);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801CE2F4);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801CE740);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801CE98C);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801CED60);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801CEF88);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801CF438);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801CF58C);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801CF5E0);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801CF6D8);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", EntityWarg);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801D04A4);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801D0624);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801D06FC);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801D0A2C);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801D0B34);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801D16B4);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801D1FC0);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801D24AC);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801D2840);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801D2A9C);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801D2D40);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801D2E4C);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801D3F38);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801D4168);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801D423C);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801D4668);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801D4700);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801D48F8);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", EntityMerman2);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", EntityMerman);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801D56D8);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801D583C);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801D58D4);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801D59D0);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", EntityBoneScimitar);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801D615C);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", EntityBat);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", EntityZombie);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801D6710);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801D6880);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801D6C68);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801D6DB8);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801D6DE8);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801D6E64);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801D6EEC);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801D6FCC);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801D7020);

INCLUDE_ASM("asm/st/no3/nonmatchings/377D4", func_801D704C);
