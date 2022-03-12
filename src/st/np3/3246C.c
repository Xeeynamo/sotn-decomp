#include "stage.h"

extern u16 D_80180A3C[];
extern u8* D_80180E28[];
extern u8 D_80180E48[];
extern u8 D_80180E50[];
extern u16 D_80180E58[];
extern u8 D_80180E68[];
extern PfnEntityUpdate PfnEntityUpdates[];
extern s16 D_80181A50[];

void SpawnExplosionEntity(u16, Entity *);
void ReplaceCandleWithDrop(Entity *);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801B246C);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801B2540);

#ifndef NON_MATCHING
INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", EntityCandle);
#else
void EntityCandle(Entity *entity) {
    u16 temp_s0 = entity->subId >> 0xC;
    if (entity->initState) {
        AnimateEntity(D_80180E28[temp_s0], entity);
        if (entity->unk44) { // If the candle is destroyed
            Entity *entityDropItem;
            g_pfnPlaySfx(0x634);
            entityDropItem = AllocEntity(D_8007D858, D_8007D858 + MaxEntityCount);
            if (entityDropItem != NULL) {
                SpawnExplosionEntity(EntityExplosionID, entityDropItem);
                entityDropItem->subId = D_80180E50[temp_s0];
            }
            ReplaceCandleWithDrop(entity);
        }
    } else {
        InitializeEntity(D_80180A3C);
        entity->zPriority = D_80097408 - 0x14;
        entity->unk18 = D_80180E68[temp_s0];
        entity->hitboxHeight = D_80180E48[temp_s0];
        entity->animationSet = D_80180E58[temp_s0];
    }
}
#endif

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801B2830);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801B28E4);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801B2C20);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801B2F30);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801B32A8);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801B3704);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801B39CC);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801B3D24);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801B3E84);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801B4004);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801B40F8);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801B44B4);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801B4558);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801B4680);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801B4940);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801B4BE8);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801B4D60);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801B5108);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801B5488);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801B560C);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801B5790);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801B5C5C);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801B5DE8);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801B5E98);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801B5F60);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801B6084);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801B644C);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801B653C);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801B65FC);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801B6990);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801B75EC);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801B7798);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801B78BC);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801B8CC0);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801B8D84);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801B8E94);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801B90BC);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", UpdateStageEntities);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801B93E8);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801B94F0);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", EntityDamage);

#ifndef NON_MATCHING
INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", CreateEntity);
#else
void CreateEntity(Entity* entity, ObjectInit* initDesc) {
    DestroyEntity(entity);
    entity->objectId = initDesc->flags & 0x3FF;
    entity->pfnUpdate = PfnEntityUpdates[entity->objectId];
    entity->posX.Data.high = initDesc->posX - D_8007308E;
    entity->posY.Data.high = initDesc->posY - D_80073092;
    entity->subId = initDesc->unk8;
    entity->unk32 = initDesc->unk6 >> 8;
    entity->unk68 = initDesc->flags >> 0xA & 7;
}
#endif

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801BAD70);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801BAE88);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801BAFA0);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801BAFEC);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801BB044);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801BB140);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801BB254);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801BB2A0);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801BB2F8);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801BB3F4);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", LoadObjLayout);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801BB680);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", SpawnExplosionEntity);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801BB7A8);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801BB824);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801BB89C);

void DestroyEntity(Entity* item) {
    int i, length;
    u32* ptr;

    if (item->unk34 & 0x800000) {
        g_pfnFreePolygons(item->firstPolygonIndex);
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

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801BC5BC);

#include "st/AnimateEntity.h"

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801BC6BC);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801BC7D4);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801BC810);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801BC844);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801BC888);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801BC8B8);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801BC8E4);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801BCB5C);

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

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801BCDA4);

#ifndef NON_MATCHING
INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801BCDD0);
#else
s16 func_801BCDD0(s32 arg0) {
    return D_80181A50[arg0 & 0xFF];
}
#endif

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801BCDEC);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801BCE58);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801BCE90);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801BCED8);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801BCF20);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801BCF78);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801BD004);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801BD034);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801BD06C);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801BD0B4);

void func_801BD114(s32 arg0) {
    D_8006C3B8->initState = (s16) (arg0 & 0xFF);
    D_8006C3B8->unk2E = 0;
    D_8006C3B8->animationFrameIndex = 0;
    D_8006C3B8->animationFrameDuration = 0;
}

void func_801BD134(s32 arg0) {
    D_8006C3B8->unk2E = (s16) (arg0 & 0xFF);
    D_8006C3B8->animationFrameIndex = 0;
    D_8006C3B8->animationFrameDuration = 0;
}

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801BD150);

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
    D_8006C3B8->initState++;
    if (D_8006C3B8->zPriority == 0) {
        D_8006C3B8->zPriority = D_80097408 - 0xC;
    }
}

void func_801BD2E0(Entity* arg0) {
    if (arg0->initState == 0) {
        arg0->initState++;
    }
}

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801BD308);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801BD430);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801BD588);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", ReplaceCandleWithDrop);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801BD984);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801BDA08);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801BDB64);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801BDBE4);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801BDCC0);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801BDDD8);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801BDE7C);

void func_801BDECC(void) {
    DestroyEntity(D_8006C3B8);
}

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", EntityCandleDrop);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801BE768);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801BE864);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801BE908);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801BEEF0);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801BF1A0);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801BFC70);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801BFD98);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801C02F4);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801C03E4);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801C04F4);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801C0624);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801C070C);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801C07FC);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801C08F0);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801C0B20);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801C0C1C);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801C119C);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801C129C);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801C1368);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801C1430);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801C14E8);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801C16C0);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801C1CA0);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801C23A0);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801C2598);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801C2690);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", EntityAreaTitlePopup);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", EntityAbsorbOrb);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801C3878);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801C3D28);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801C3E14);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801C4144);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801C424C);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801C4DCC);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801C56D8);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801C5BC4);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801C5F58);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801C61B4);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801C6458);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801C6564);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801C7650);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801C7880);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801C7954);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801C7D80);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801C7E18);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801C8010);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", EntityMerman2);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", EntityMerman);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801C8DF0);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801C8F54);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801C8FEC);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801C90E8);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", EntityBoneScimitar);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801C9874);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", EntityBat);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", EntityZombie);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801C9E28);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801C9F98);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801CA498);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801CA654);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801CAE0C);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801CB018);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801CBF18);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801CC2E0);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801CD540);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801CD620);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801CD658);

void func_801CD734() {
    while (PadRead(0))
        func_801CD658();
    while (PadRead(0) == 0)
        func_801CD658();
}

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801CD78C);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801CD83C);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801CD91C);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801CDA14);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801CDA6C);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801CDAC8);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801CDC80);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801CDD00);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801CDD80);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801CDE10);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801CDE88);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801CDF1C);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801CDFD8);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801CE04C);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801CE120);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801CE1E8);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801CE228);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801CE258);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801CE2CC);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801CE3FC);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801CE4CC);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801CE69C);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801CF254);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801CF5B8);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801CF778);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801CF7A0);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801CF94C);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801D0730);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801D0A00);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801D0B40);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801D0B78);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801D0D40);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801D1BB8);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801D1F38);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801D2320);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801D2470);

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801D24A0);

POLY_GT4* func_801D251C(POLY_GT4* startPoly, s32 count) {
    POLY_GT4* poly;
    s8 unk;
    s32 i;

    if (startPoly->p3) {
        startPoly->p3 = 0;
    } else {
        startPoly->p3 = 1;
    }

    poly = startPoly;
    for (i = 0; i < count; i++) {
        if (poly->p3) {
            poly->pad3 &= ~8;
            unk = 0;
        } else {
            poly->pad3 |= 8;
            unk = 1;
        }

        poly = poly->tag;
        if (poly == 0)
            return 0;
        poly->p3 = unk;
    }
    
    return poly;
}

void func_801D25A4(POLY_GT4* arg0) {
    arg0->p1 = 0;
    arg0->p2 = 0;
    arg0->p3 = 0;
    ((POLY_GT4*)arg0->tag)->x1 = 0;
    ((POLY_GT4*)arg0->tag)->y1 = 0;
    ((POLY_GT4*)arg0->tag)->y0 = 0;
    ((POLY_GT4*)arg0->tag)->x0 = 0;
    ((POLY_GT4*)arg0->tag)->clut = 0;
    *(u16*)&((POLY_GT4*)arg0->tag)->u0 = 0;
    *(u16*)&((POLY_GT4*)arg0->tag)->b1 = 0;
    *(u16*)&((POLY_GT4*)arg0->tag)->r1 = 0;
    *(u16*)&((POLY_GT4*)arg0->tag)->u1 = 0;
    ((POLY_GT4*)arg0->tag)->tpage = 0;
    *(u16*)&((POLY_GT4*)arg0->tag)->r2 = 0;
    *(u16*)&((POLY_GT4*)arg0->tag)->b2 = 0;
    ((POLY_GT4*)arg0->tag)->u2 = 0;
    ((POLY_GT4*)arg0->tag)->v2 = 0;
    ((POLY_GT4*)arg0->tag)->r3 = 0;
    ((POLY_GT4*)arg0->tag)->b3 = 0;
    ((POLY_GT4*)arg0->tag)->x2 = 0;
    ((POLY_GT4*)arg0->tag)->y2 = 0;
}

void func_801D2684(POLY_GT4* arg0) {
    func_801D25A4(arg0);
    arg0->p3 = 8;
    ((POLY_GT4*)arg0->tag)->p3 = 1;
    ((POLY_GT4*)arg0->tag)->code = 2;
    ((POLY_GT4*)arg0->tag)->pad3 = 0xA;
}

void func_801D26D8(POLY_GT4* arg0) {
    arg0->p3 = 0;
    arg0->pad3 = 8;
    ((POLY_GT4*)arg0->tag)->p3 = 0;
    ((POLY_GT4*)arg0->tag)->code = 4;
    ((POLY_GT4*)arg0->tag)->pad3 = 8;
}

INCLUDE_ASM("asm/st/np3/nonmatchings/3246C", func_801D2704);
