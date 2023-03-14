#include "servant.h"

SpriteParts* D_80170040[];
u16 D_80170448[];
Sprite D_80170608[];
u16 D_80170720[];
s32 D_80171090;
EntitySearch D_80171094[];
Collider D_80174AD8;
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

INCLUDE_ASM("asm/us/servant/tt_000/nonmatchings/10E8", func_8017110C);

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

bool func_80171434(s16 x, s16 y, s16* outX, s16* outY) {
    s32 curY;

    g_api.CheckCollision(x, y, &D_80174AD8, 0);
    if (D_80174AD8.unk0 & 1) {
        return 0;
    }

    for (curY = y - 16; curY > 0; curY -= 16) {
        g_api.CheckCollision(x, curY, &D_80174AD8, 0);
        switch (D_80174AD8.unk0 & 0x801) {
        case 0:
            break;
        case 1:
            *outX = x;
            *outY = curY + LOH(D_80174AD8.unk10);
            return 1;
        default:
            return 0;
        }
    }
    return 0;
}

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
    entity->flags = FLAG_UNK_04000000;
    entity->posX.val = self->posX.val;
    entity->posY.val = self->posY.val;
    entity->unk8C.entityPtr = self;
}

void func_8017160C(s32 amount, s32 objectId) {
    s32 i;
    Entity* entity;
    s16 facing;

    if (amount > 3) {
        amount = 3;
    }

    for (i = 0; i < amount; i++) {
        entity = &g_EntityArray[5 + i];
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
        *((s16*)(&entity->unkAC)) = g_Camera.posX.i.hi;
        *((s16*)(&entity->unkAE)) = g_Camera.posY.i.hi;
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

INCLUDE_ASM("asm/us/servant/tt_000/nonmatchings/10E8", func_801719E0);

void func_80171ED4(s32 arg0) {
    RECT rect;
    s32 i;
    s32 x;
    u16* spriteBanks;
    s16* src;
    s16* dst;
    Entity* e;

    if (arg0 == 1 || arg0 == 3)
        func_80174210(0, 1);

    if (arg0 == 3)
        return;

    dst = D_8006F3CC;
    src = D_80170448;
    for (i = 0; i < 0x100; i++) {
        *dst++ = *src++;
    }

    dst = D_8006F42C;
    spriteBanks = D_80170720;
    src = spriteBanks;
    for (i = 0; i < 0x20; i++) {
        *dst++ = *src++;
    }

    rect.w = 0x100;
    rect.h = 1;
    rect.x = 0;
    rect.y = 0xF4;
    dst = D_8006F3CC;
    LoadImage(&rect, dst);

    spriteBanks = D_80170040;
    g_api.o.spriteBanks[0x14] = spriteBanks;

    e = &g_EntityArray[4];
    DestroyEntity(e);
    e->unk5A = 0x6C;
    e->palette = 0x140;
    e->animSet = 0x8014;
    e->subId = 0;
    e->zPriority = PLAYER.zPriority - 2;
    e->facing = (PLAYER.facing + 1) & 1;
    e->posX.val = PLAYER.posX.val;
    e->posY.val = PLAYER.posY.val;
    if (arg0 == 1) {
        e->objectId = 0xD1;
        e->posX.val = 0x800000;
        e->posY.val = 0xFFE00000;
    } else {
        Entity* p;
        e->objectId = 0xD1;
        if (D_8003C708 & 0x20) {
            if (func_80174864() != 0) {
                x = 0xC00000;
            } else {
                x = 0x400000;
            }
            e->posX.val = x;
            e->posY.val = 0xA00000;
        } else {
            if (D_800733EC == 0) {
                e->posX.val = PLAYER.posX.val - 0x120000;
            } else {
                e->posX.val = PLAYER.posX.val + 0x120000;
            }
            e->posY.val = PLAYER.posY.val - 0x220000;
        }
    }
    D_80174D3C = 0;
    *(u16*)&e->unkAC = g_Camera.posX.i.hi;
    *(u16*)&e->unkAE = g_Camera.posY.i.hi;
}

INCLUDE_ASM("asm/us/servant/tt_000/nonmatchings/10E8", func_80172120);

INCLUDE_ASM("asm/us/servant/tt_000/nonmatchings/10E8", func_80172C30);

void func_8017339C(void) {}

void func_801733A4(void) {}

void func_801733AC(void) {}

void func_801733B4(void) {}

void func_801733BC(void) {}

void func_801733C4(void) {}

void func_801733CC(void) {}

INCLUDE_ASM("asm/us/servant/tt_000/nonmatchings/10E8", func_801733D4);

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

INCLUDE_ASM("asm/us/servant/tt_000/nonmatchings/10E8", func_80173C64);

void DestroyEntity(Entity* entity) {
    s32 i;
    s32 length;
    u32* ptr;

    if (entity->flags & FLAG_FREE_POLYGONS) {
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
    s16 start = D_80171094[rangeIndex].start;
    s16 end = D_80171094[rangeIndex].end;
    Entity* entity = &g_EntityArray[start];
    s32 i;

    for (i = start; end >= i; i++, entity++) {
        if (entity->objectId == objectId) {
            return entity;
        }
    }

    return NULL;
}

s32 func_80173F30(Entity* entity, s16 x, s16 y) {
    s16 diffx = x - entity->posX.i.hi;
    return ratan2(-(s16)(y - entity->posY.i.hi), diffx) & 0xFFF;
}

s16 func_80173F74(s16 arg0, s16 arg1, s16 arg2) {
    s32 diffTmp = arg1 - arg0;
    s16 diff = ABS(diffTmp);
    s16 res;

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
INCLUDE_ASM("asm/us/servant/tt_000/nonmatchings/10E8", func_80174038);
#else
void func_80174038(Entity* entity) {
    switch (entity->step) {
    case 0:
        entity->flags = 0x20000 | FLAG_UNK_04000000;
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

#ifndef NON_MATCHING
INCLUDE_ASM("asm/us/servant/tt_000/nonmatchings/10E8", func_80174210);
#else
typedef struct {
    u32 unk0;
    u32 unk4;
    u32 unk8;
    s32 unkC;
    u32 unk10;
    u32 cameraX;
    u32 cameraY;
    s32 unk1C;
    u32 unk20;
    u32 objectId;
    u32 subId;
    u32 unk2C;
} Unkstruct_80174210;

extern Unkstruct_80174210 D_80170760[];
extern s32* D_8017109C;
extern s32 D_801710A0;
extern s32 D_801710A4;
extern s32 D_801710A8;

void func_80174210(Entity* self, s32 arg1) {
    Unkstruct_80174210* temp_s0;
    Unkstruct_80174210** var_s1_2;
    Unkstruct_80174210* temp_v1_5;
    Unkstruct_80174210* temp_v1_4;
    s32* var_s1;
    s32 cameraY;
    s32 cameraX;
    s32 var_s2;
    s32 var_v0_2;

    if (arg1 != 0) {
        D_801710A8 = 0;
        D_801710A4 = 0;
        D_801710A0 = 0;
        return;
    }
    cameraX = g_Camera.posX.i.hi;
    cameraY = g_Camera.posY.i.hi;
    if (D_801710A0 != D_8006CBC4 || D_801710A4 != g_CurrentRoomLeft ||
        D_801710A8 != g_CurrentRoomTop) {
        var_s1 = D_8017109C;
        D_801710A0 = D_8006CBC4;
        D_801710A4 = g_CurrentRoomLeft;
        D_801710A8 = g_CurrentRoomTop;
        if (D_80170760[1].unkC != -1) {
            var_s2 = 1;
            do {
                temp_s0 = &D_80170760[var_s2];
                if (temp_s0->unk8 == -1 || temp_s0->unk8 == D_801710A0) {
                    if ((temp_s0->unkC < 0 && !(g_StageId & 0x20)) ||
                        !(g_StageId & 0x20)) {
                        if (ABS(temp_s0->unkC) == D_801710A4 &&
                            temp_s0->unk10 == D_801710A8) {
                            if (temp_s0->cameraX == cameraX &&
                                temp_s0->cameraY == cameraY &&
                                (temp_s0->unk1C == -1 ||
                                 (temp_s0->unk1C >= 0 ||
                                  D_8003BDEC[temp_s0->unk1C & 0xFFFF] == 0) &&
                                     (!(temp_s0->unk1C & 0x40000000) ||
                                      !(D_80097964[temp_s0->unk1C & 0xFFFF] &
                                        1)))) {
                                temp_s0->unk4 = 0;
                                if (temp_s0->unk20 == 0) {
                                    func_801745E4(self, temp_s0->objectId,
                                                  temp_s0->subId);
                                    if (temp_s0->unk2C == 0) {
                                        goto block_26;
                                    }
                                } else {
                                    goto block_27;
                                }
                            } else {
                            block_26:
                                if (temp_s0->unk20 != 0) {
                                block_27:
                                    temp_s0->unk4 = (s32)(temp_s0->unk20 - 1);
                                }
                                *var_s1 = temp_s0;
                                var_s1 = temp_s0;
                            }
                        }
                    }
                }
            } while (D_80170760[++var_s2].unkC != -1);
        }
        *var_s1 = NULL;
    } else {
        var_s1_2 = D_8017109C;
        while (*var_s1_2 != NULL) {
            temp_v1_5 = *var_s1_2;
            if (temp_v1_5->cameraX == cameraX &&
                temp_v1_5->cameraY == cameraY &&
                (temp_v1_5->unk1C == -1 ||
                 (temp_v1_5->unk1C >= 0 ||
                  D_8003BDEC[temp_v1_5->unk1C & 0xFFFF] == 0) &&
                     (!(temp_v1_5->unk1C & 0x40000000) ||
                      !(D_80097964[temp_v1_5->unk1C & 0xFFFF] & 1)))) {
                temp_v1_5 = *var_s1_2;
                var_v0_2 = temp_v1_5->unk4 - 1;
                if (temp_v1_5->unk4 == 0) {
                    func_801745E4(self, temp_v1_5->objectId, temp_v1_5->subId);
                    temp_v1_4 = *var_s1_2;
                    if (temp_v1_4->unk2C != 0) {
                        *var_s1_2 = temp_v1_4->unk0;
                        continue;
                    } else {
                        var_v0_2 = temp_v1_4->unk20;
                    }
                }
                temp_v1_5->unk4 = var_v0_2;
            }
            var_s1_2 = *var_s1_2;
        }
    }
}
#endif

void func_801745E4(Entity* entityParent, s32 objectId, s32 subId) {
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
    entity->flags = FLAG_UNK_04000000;
    entity->posX.val = entityParent->posX.val;
    entity->posY.val = entityParent->posY.val;
    entity->unk8C.entityPtr = entityParent;
    entity->subId = subId;
}

s32 func_801746A0(s32 arg0) {
    s32 tmp;

    if (D_800733E4 < 0) {
        if (!(D_80072F20.pl_vram_flag & 1)) {
            return 1;
        }
    }

    tmp = D_800733E4;
    NOP;
    if (tmp > 0) {
        if (!(D_80072F20.pl_vram_flag & 2)) {
            return 1;
        }
    }

    if (D_800733E0 < 0 && !(D_80072F20.pl_vram_flag & 8))
        return 1;

    tmp = D_800733E0;
    NOP;
    if (D_800733E0 > 0 && !(D_80072F20.pl_vram_flag & 4))
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

s32 func_801747B8(void) {
    Entity* entity;
    s32 i;

    entity = &D_800762D8;
    for (i = 0; i < 0x80; i++, entity++) {
        if (entity->objectId == 0)
            continue;
        if (entity->unk3C == 0)
            continue;
        if (entity->flags & 0x200000)
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
