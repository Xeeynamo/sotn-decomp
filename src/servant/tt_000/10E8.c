#include "servant.h"

u16 D_80170448[];
Sprite D_80170608[];
s32 D_80171090;
EntitySearch D_80171094[];
CollisionResult D_80174AD8;
s32 D_80174D3C;

void func_80171ED4(s32 arg0);
void func_80172120(Entity* self);
void func_80172C30(Entity* self);
void func_8017339C(void);
void func_801733A4(void);
void func_801733AC(void);
void func_801733B4(void);
void func_801733BC(void);
void func_801733C4(void);
void func_801733CC(void);
void func_801733D4(Entity* self);
void func_80173C0C(void);
void func_80173C14(void);
void func_80173C1C(void);
void func_80173C24(void);
void func_80173C2C(Entity* self);

ServantDesc g_ServantDesc = {
    func_80171ED4, func_80172120, func_80172C30, func_8017339C,
    func_801733A4, func_801733AC, func_801733B4, func_801733BC,
    func_801733C4, func_801733CC, func_801733D4, func_80173C0C,
    func_80173C14, func_80173C1C, func_80173C24, func_80173C2C,
};

void func_80174210(Entity* self, s32 arg1);
s32 func_80174864(void);

void func_801710E8(Entity* entity, s32* arg1) {
    if (entity->unk4C != arg1) {
        entity->unk4C = arg1;
        entity->animFrameIdx = 0;
        entity->animFrameDuration = 0;
    }
}

INCLUDE_ASM("config/../asm/servant/tt_000/nonmatchings/10E8", func_8017110C);

s32 func_801713C8(Entity* entity) {
    if (entity->unk3C == 0)
        return 0;
    if (entity->posX.i.hi < -16)
        return 0;
    if (entity->posX.i.hi > 272)
        return 0;
    if (entity->posY.i.hi > 240)
        return 0;
    if (entity->posY.i.hi < 0)
        return 0;
    if (entity->hitPoints >= 0x7000)
        return 0;
    return entity->hitPoints > 0;
}

#ifndef NON_EQUIVALENT
INCLUDE_ASM("config/../asm/servant/tt_000/nonmatchings/10E8", func_80171434);
#else
s32 func_80171434(s16 x, s16 y, s16* outX, s16* outY) {
    s32 curY;

    g_api.CheckCollision(x, y, &D_80174AD8, 0);
    if (D_80174AD8.unk0 & 1) {
        return 0;
    }
    *outX = x;
    *outY = curY + D_80174AD8.unk10;
    curY = y;
    do {
        curY -= 16;
        if (curY <= 0) {
            return 0;
        }
        g_api.CheckCollision(x, curY, &D_80174AD8, 0);
    } while ((D_80174AD8.unk0 & 0x801) == 0);

    if ((D_80174AD8.unk0 & 0x801) == 1) {
        *outX = x;
        *outY = curY + D_80174AD8.unk10;
        return 1;
    }
    return 0;
}
#endif

void func_80171560(void) {}

void func_80171568(Entity* self) {
    Entity* entity;
    s32 i;

    for (i = 0; i < 3; i++) {
        entity = &g_EntityArray[5 + i];
        if (entity->objectId == 0) {
            goto init_entity;
        }
    }
    return;

init_entity:
    DestroyEntity(entity);
    entity->objectId = 0xDA;
    entity->zPriority = self->zPriority;
    entity->facing = self->facing;
    entity->unk34 = 0x04000000;
    entity->posX.val = self->posX.val;
    entity->posY.val = self->posY.val;
    entity->unk8C.entityPtr = self;
}

void func_8017160C(s32 amount, s32 objectId) {
    s32 i;
    Entity* entity;
    s16* camera;
    s16 facing;

    if (amount > 3) {
        amount = 3;
    }

    for (i = 0; i < amount; i++) {
        entity = &g_EntityArray[5 + i];
        camera = &D_8007308E;
        if (entity->objectId == objectId) {
            entity->step = 0;
        } else {
            DestroyEntity(entity);
            entity->unk5A = 0x6C;
            entity->palette = 0x140;
            entity->objectId = objectId;
            entity->animSet = 0x8014;
            entity->zPriority = g_EntityArray[0].zPriority - 2;
            facing = (g_EntityArray[0].facing + 1) & 1;
            entity->subId = i + 1;
            entity->facing = facing;
        }
        *((s16*)(&entity->unkAC)) = camera[0];
        *((s16*)(&entity->unkAE)) = camera[2];
    }
}

void func_8017170C(Entity* entity, s32 frameIndex) {
    POLY_GT4* poly;
    s32 tpage;
    s32 x;
    s32 y;
    s32 index;

    poly = &D_80086FEC[entity->firstPolygonIndex];
    if (frameIndex == 0) {
        poly->pad3 = 8;
        return;
    }
    index = frameIndex - 1;
    if (entity->facing != 0) {
        x = entity->posX.i.hi + 2;
    } else {
        x = entity->posX.i.hi - 16;
    }
    y = entity->posY.i.hi - 16;

    poly->x0 = poly->x2 = x - D_80170608[index].x;
    poly->y0 = poly->y1 = y - D_80170608[index].y;
    poly->x1 = poly->x3 = poly->x0 + D_80170608[index].width;
    poly->y2 = poly->y3 = poly->y0 + D_80170608[index].height;
    poly->clut = D_80170608[index].clut;
    tpage = D_80170608[index].tpage;
    if (tpage < 0) {
        tpage += 3;
    }
    poly->tpage = tpage >> 2;
    poly->u0 = poly->u2 = D_80170608[index].texLeft;
    poly->v0 = poly->v1 = D_80170608[index].texTop;
    poly->u1 = poly->u3 = D_80170608[index].texRight;
    poly->v2 = poly->v3 = D_80170608[index].texBottom;
    poly->pad2 = entity->zPriority + 1;
    poly->pad3 = 0x102;
}

void func_801718A0(Entity* entity) {
    POLY_GT4* poly;
    s32 frame;
    s32 y;
    s32 x;

    frame = 2;
    if (entity->facing != 0) {
        x = entity->posX.i.hi + 2;
    } else {
        x = entity->posX.i.hi - 16;
    }
    y = entity->posY.i.hi - 16;

    x += (rsin(entity->unk8C.modeS16.unk0 << 7) * 8) >> 12;
    y -= entity->unk8C.modeS16.unk0 / 2;

    poly = &D_80086FEC[entity->firstPolygonIndex];
    poly->x0 = poly->x2 = x - D_80170608[frame].x;
    poly->y0 = poly->y1 = y - D_80170608[frame].y;
    poly->x1 = poly->x3 = poly->x0 + D_80170608[frame].width;
    poly->y2 = poly->y3 = poly->y0 + D_80170608[frame].height;
}

INCLUDE_ASM("config/../asm/servant/tt_000/nonmatchings/10E8", func_801719E0);

#ifndef NON_EQUIVALENT
INCLUDE_ASM("config/../asm/servant/tt_000/nonmatchings/10E8", func_80171ED4);
#else
extern void* D_8003C788;
extern u16 D_8006F3CC[];
extern u16 D_8006F42C[];
extern /*?*/ s32 D_80170040;
extern u16 D_80170720[];

void func_80171ED4(s32 arg0) {
    RECT rect;
    s32 i;

    if (arg0 == 1 || arg0 == 3)
        return;

    func_80174210(0, 1);
    if (arg0 == 3)
        return;

    for (i = 0; i < 0x100; i++) {
        D_8006F3CC[i] = D_80170448[i];
    }

    for (i = 0; i < 0x20; i++) {
        D_8006F42C[i] = D_80170720[i];
    }

    rect.w = 0x100;
    rect.h = 1;
    rect.x = 0;
    rect.y = 0xF4;
    LoadImage(&rect, D_8006F3CC);

    g_api.o.spriteBanks[0x14] = D_80170040;

    DestroyEntity(&g_EntityArray[4]);
    g_EntityArray[4].unk5A = 0x6C;
    g_EntityArray[4].palette = 0x140;
    g_EntityArray[4].animSet = 0x8014;
    g_EntityArray[4].subId = 0;
    g_EntityArray[4].zPriority = PLAYER.zPriority - 2;
    g_EntityArray[4].facing = (PLAYER.facing + 1) & 1;
    g_EntityArray[4].posX.val = PLAYER.posX.val;
    g_EntityArray[4].posY.val = PLAYER.posY.val;
    g_EntityArray[4].objectId = 0xD1;
    if (arg0 == 1) {
        g_EntityArray[4].posX.val = 0x800000;
        g_EntityArray[4].posY.val = 0xFFE00000;
    } else {
        if (D_8003C708 & 0x20) {
            if (func_80174864() != 0) {
                g_EntityArray[4].posX.val = PLAYER.posX.val + 0xC00000;
            } else {
                g_EntityArray[4].posX.val = PLAYER.posX.val + 0x400000;
            }
            g_EntityArray[4].posY.val = 0xA00000;
        } else {
            if (D_800733EC == 0) {
                g_EntityArray[4].posX.val = PLAYER.posX.val + 0xFFEE0000;
            } else {
                g_EntityArray[4].posX.val = PLAYER.posX.val + 0x120000;
            }
            g_EntityArray[4].posY.val = PLAYER.posY.val + 0xFFDE0000;
        }
    }
    D_80174D3C = 0;
    g_EntityArray[4].unkAC = (u16)D_8007308E;
    g_EntityArray[4].unkAE = (u16)D_80073092;
}
#endif

INCLUDE_ASM("config/../asm/servant/tt_000/nonmatchings/10E8", func_80172120);

s32 func_801746A0(s32 arg0); /* extern */

INCLUDE_ASM("config/../asm/servant/tt_000/nonmatchings/10E8", func_80172C30);

void func_8017339C(void) {}

void func_801733A4(void) {}

void func_801733AC(void) {}

void func_801733B4(void) {}

void func_801733BC(void) {}

void func_801733C4(void) {}

void func_801733CC(void) {}

INCLUDE_ASM("config/../asm/servant/tt_000/nonmatchings/10E8", func_801733D4);

void func_80173C0C(void) {}

void func_80173C14(void) {}

void func_80173C1C(void) {}

void func_80173C24(void) {}

void func_80173C2C(Entity* entity) {
    if (entity->subId == 0xF) {
        D_80174D3C = 1;
    }
    DestroyEntity(entity);
}

INCLUDE_ASM("config/../asm/servant/tt_000/nonmatchings/10E8", func_80173C64);

void DestroyEntity(Entity* entity) {
    s32 i;
    s32 length;
    u32* ptr;

    if (entity->unk34 & 0x800000) {
        g_api.FreePolygons(entity->firstPolygonIndex);
    }

    ptr = (u32*)entity;
    length = sizeof(Entity) / sizeof(u32);
    for (i = 0; i < length; i++)
        *ptr++ = 0;
}

s32 func_80173E78(s32 arg0, s32 arg1) {
    if (arg0 < 0) {
        arg0 += arg1;
        if (arg0 > 0) {
            arg0 = 0;
        }
    } else {
        arg0 -= arg1;
        if (arg0 < 0) {
            arg0 = 0;
        }
    }

    return arg0;
}

Entity* func_80173EB0(s32 rangeIndex, s32 objectId) {
    volatile u32 pad; // fake?
    Entity* entity;
    s16 start;
    s16 end;
    s32 i;
    start = D_80171094[rangeIndex].start;
    end = D_80171094[rangeIndex].end;
    entity = &g_EntityArray[start];

    for (i = start; end >= i; i++, entity++) {
        if (entity->objectId == objectId) {
            return entity;
        }
    }

    return 0;
}

s32 func_80173F30(Entity* entity, s16 x, s16 y) {
    s16 diffx = x - entity->posX.i.hi;
    return ratan2(-(s16)(y - entity->posY.i.hi), diffx) & 0xFFF;
}

s16 func_80173F74(s16 arg0, s16 arg1, s16 arg2) {
    s32 diffTmp;
    s16 res;
    s16 diff;

    diffTmp = arg1 - arg0;
    diff = ABS(diffTmp);
    if (arg2 > diff) {
        arg2 = diff;
    }

    if (arg1 < arg0) {
        if (diff < 0x800) {
            res = arg1 + arg2;
        } else {
            res = arg1 - arg2;
        }
    } else {
        if (diff < 0x800) {
            res = arg1 - arg2;
        } else {
            res = arg1 + arg2;
        }
    }
    return res & 0xFFF;
}

s32 func_80173FE8(Entity* entity, s32 x, s32 y) {
    s32 diffX = x - entity->posX.i.hi;
    s32 diffY = y - entity->posY.i.hi;

    return SquareRoot12((diffX * diffX + diffY * diffY) << 12, diffX) >> 12;
}

// PSY-Q 3.5 match as in GCC a jump skips a 'nop'
#ifndef NON_MATCHING
INCLUDE_ASM("config/../asm/servant/tt_000/nonmatchings/10E8", func_80174038);
#else
void func_80174038(Entity* entity) {
    switch (entity->step) {
    case 0:
        entity->unk34 = 0x04020000;
        if (D_8003C704 == 0) {
            if (g_api.func_80133940() != 0) {
                g_api.PlaySfx(16);
                entity->step++;
            }
        }
        break;

    case 1:
        if (g_api.func_80133950() != 0) {
            entity->step++;
        }
        break;
    case 2:
        g_api.PlaySfx(entity->subId);
        entity->step++;
        break;

    case 3:
        if (g_api.func_80131F68() != 0) {
            entity->step++;
        }
        break;

    case 4:
        if (g_api.func_80131F68() == 0) {
            entity->step++;
        }
        break;

    case 5:
        if ((D_8003C708 & 0x60) != 0) {
            D_80171090 = 99;
            DestroyEntity(entity);
            return;
        }
        if (g_api.func_80133940() != 0) {
            g_api.PlaySfx(17);
            entity->step++;
        }
        break;

    case 6:
        if (g_api.func_80133950() != 0) {
            D_80171090 = 99;
            DestroyEntity(entity);
            return;
        }
        break;

    case 7:
        g_api.PlaySfx(10);
        entity->step = 4;
        break;

    case 8:
        D_80171090 = 99;
        DestroyEntity(entity);
        return;
    }

    D_80171090 = (s32)entity->step;
}
#endif

// TODO func_80174210
INCLUDE_ASM("config/../asm/servant/tt_000/nonmatchings/10E8", func_80174210);

void func_801745E4(Entity* entityParent, u16 objectId, u16 subId) {
    Entity* entity;
    s32 i;

    for (i = 0; i < 3; i++) {
        entity = &g_EntityArray[5 + i];
        if (entity->objectId == 0) {
            goto init_entity;
        }
    }
    return;

init_entity:
    DestroyEntity(entity);
    entity->objectId = objectId;
    entity->zPriority = entityParent->zPriority;
    entity->facing = entityParent->facing;
    entity->unk34 = 0x04000000;
    entity->posX.val = entityParent->posX.val;
    entity->posY.val = entityParent->posY.val;
    entity->unk8C.entityPtr = entityParent;
    entity->subId = subId;
}

// PSY-Q 3.5 match as in GCC a jump skips a 'nop'
#ifndef NON_MATCHING
INCLUDE_ASM("config/../asm/servant/tt_000/nonmatchings/10E8", func_801746A0);
#else
s32 func_801746A0(s32 arg0) {
    if (D_800733E4 < 0 && !(*D_80072F20 & 1))
        return 1;

    if (D_800733E4 > 0 && !(*D_80072F20 & 2))
        return 1;

    if (D_800733E0 < 0 && !(*D_80072F20 & 8))
        return 1;

    if (D_800733E0 > 0 && !(*D_80072F20 & 4))
        return 1;

    if (arg0 == 0)
        return 0;

    if (D_80072F70 != D_80073404)
        return 1;

    if (D_80072F70 != 0)
        return 1;

    if (D_80072F72 != D_80073406)
        return 1;

    return D_80072F72 != 0 && D_80072F72 != 4;
}
#endif

s32 func_801747B8(void) {
    Entity* entity;
    s32 i;

    entity = &D_800762D8;
    for (i = 0; i < 0x80; i++, entity++) {
        if (entity->objectId == 0)
            continue;
        if (entity->unk3C == 0)
            continue;
        if (entity->unk34 & 0x200000)
            continue;
        if (entity->posX.i.hi < -16)
            continue;
        if (entity->posX.i.hi > 272)
            continue;
        if (entity->posY.i.hi > 240)
            continue;
        if (entity->posY.i.hi < 0)
            continue;
        if (entity->hitPoints < 0x7000)
            return 1;
    }
    return 0;
}

s32 func_80174864(void) {
    int tmp;

    if (g_StageId - 0x20 < 0x15) {
        if (D_8003C708 == 0x22) {
            return 1;
        }

        tmp = (D_8003C708 != 0x20) * 2;
        return tmp;
    }

    if (D_8003C708 == 0x22) {
        return 0;
    }

    tmp = 0x20;
    return D_8003C708 != tmp ? 2 : 1;
}
