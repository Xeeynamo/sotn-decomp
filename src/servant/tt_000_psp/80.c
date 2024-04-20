#include <servant.h>

extern u8* D_91F85F8;
extern u8* D_092EC280;
extern u8* D_092EC9E8;
extern u8* D_801530AC;
extern u8* D_91E1970;
extern u8* D_8D1DC40;

void DestroyEntity();
void func_80174864();
void func_8909F84();
void ProcessEvent();

void func_801710E8(Entity* entity, AnimationFrame* anim) {
    if (entity->unk4C != anim) {
        entity->unk4C = anim;
        entity->animFrameIdx = 0;
        entity->animFrameDuration = 0;
    }
}

INCLUDE_ASM("servant/tt_000/nonmatchings/80", func_8017110C);

INCLUDE_ASM("servant/tt_000/nonmatchings/80", func_801713C8);

INCLUDE_ASM("servant/tt_000/nonmatchings/80", func_80171560);

INCLUDE_ASM("servant/tt_000/nonmatchings/80", func_80171568);

void func_8017160C(s32 amount, s32 entityId) {
    s32 i;
    Entity* entity;
    u16 facing;

    amount = MIN(amount, 3);
    for (i = 0; i < amount; i++) {
        entity = &g_Entities[5 + i];
        if (entity->entityId == entityId) {
            entity->step = 0;
        } else {
            DestroyEntity(entity);
            entity->entityId = entityId;
            entity->unk5A = 0x6C;
            entity->palette = 0x140;
            entity->animSet = ANIMSET_OVL(20);
            entity->zPriority = g_Entities[0].zPriority - 2;
            entity->facingLeft = (g_Entities[0].facingLeft + 1) & 1;
            entity->params = i + 1;
        }
        entity->ext.bat.cameraX = g_Tilemap.scrollX.i.hi;
        entity->ext.bat.cameraY = g_Tilemap.scrollY.i.hi;
    }
}

INCLUDE_ASM("servant/tt_000/nonmatchings/80", func_8017170C);

INCLUDE_ASM("servant/tt_000/nonmatchings/80", func_801718A0);

INCLUDE_ASM("servant/tt_000/nonmatchings/80", func_801719E0);

INCLUDE_ASM("servant/tt_000/nonmatchings/80", func_80171ED4);

INCLUDE_ASM("servant/tt_000/nonmatchings/80", func_80172120);

INCLUDE_ASM("servant/tt_000/nonmatchings/80", func_80172C30);

void func_8017339C(void) {}

void func_801733A4(void) {}

void func_801733AC(void) {}

void func_801733B4(void) {}

void func_801733BC(void) {}

void func_801733C4(void) {}

void func_801733CC(void) {}

INCLUDE_ASM("servant/tt_000/nonmatchings/80", func_801733D4);

void func_80173C0C(void) {}

void func_80173C14(void) {}

void func_80173C1C(void) {}

void func_80173C24(void) {}

INCLUDE_ASM("servant/tt_000/nonmatchings/80", func_80173C2C);

INCLUDE_ASM("servant/tt_000/nonmatchings/80", DestroyEntity);

INCLUDE_ASM("servant/tt_000/nonmatchings/80", func_80173F30);

INCLUDE_ASM("servant/tt_000/nonmatchings/80", func_80173F74);

INCLUDE_ASM("servant/tt_000/nonmatchings/80", ProcessEvent);

INCLUDE_ASM("servant/tt_000/nonmatchings/80", CreateEventEntity);

INCLUDE_ASM("servant/tt_000/nonmatchings/80", func_801746A0);

INCLUDE_ASM("servant/tt_000/nonmatchings/80", func_80174864);

// new function?!
INCLUDE_ASM("servant/tt_000/nonmatchings/80", func_092EC220);
