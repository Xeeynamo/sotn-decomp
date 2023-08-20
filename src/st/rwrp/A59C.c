#include "rwrp.h"
INCLUDE_ASM("asm/us/st/rwrp/nonmatchings/A59C", TestCollisions);

INCLUDE_ASM("asm/us/st/rwrp/nonmatchings/A59C", func_8018B6B4);

#include "../create_entity_from_layout.h"

void CreateEntityWhenInVerticalRange(LayoutEntity* layoutObj) {
    s16 yClose;
    s16 yFar;
    s16 posY;
    Entity* entity;

    posY = g_Camera.posY.i.hi;
    yClose = posY - 0x40;
    yFar = posY + 0x120;
    if (yClose < 0) {
        yClose = 0;
    }

    posY = layoutObj->posY;
    if (posY < yClose) {
        return;
    }

    if (yFar < posY) {
        return;
    }

    switch (layoutObj->entityId & 0xE000) {
    case 0x0:
        entity =
            &g_Entities[STAGE_ENTITY_START + (u8)layoutObj->entityRoomIndex];
        if (entity->entityId == 0) {
            CreateEntityFromLayout(entity, layoutObj);
        }
        break;
    case 0x8000:
        break;
    case 0xA000:
        entity =
            &g_Entities[STAGE_ENTITY_START + (u8)layoutObj->entityRoomIndex];
        CreateEntityFromLayout(entity, layoutObj);
        break;
    }
}

void CreateEntityWhenInHorizontalRange(LayoutEntity* layoutObj) {
    s16 xClose;
    s16 xFar;
    s16 posX;
    Entity* entity;

    posX = g_Camera.posX.i.hi;
    xClose = posX - 0x40;
    xFar = posX + 0x140;
    if (xClose < 0) {
        xClose = 0;
    }

    posX = layoutObj->posX;
    if (posX < xClose) {
        return;
    }

    if (xFar < posX) {
        return;
    }

    switch (layoutObj->entityId & 0xE000) {
    case 0x0:
        entity =
            &g_Entities[STAGE_ENTITY_START + (u8)layoutObj->entityRoomIndex];
        if (entity->entityId == 0) {
            CreateEntityFromLayout(entity, layoutObj);
        }
        break;
    case 0x8000:
        break;
    case 0xA000:
        entity =
            &g_Entities[STAGE_ENTITY_START + (u8)layoutObj->entityRoomIndex];
        CreateEntityFromLayout(entity, layoutObj);
        break;
    }
}

void func_8018C04C(s16 arg0) {
    while (true) {
        if (D_80195A30->posX != 0xFFFE && (s32)D_80195A30->posX >= arg0) {
            break;
        }
        D_80195A30++;
    }
}

void func_8018C098(s16 arg0) {
    while (true) {
        if ((D_80195A30->posX != 0xFFFF) &&
            ((arg0 >= D_80195A30->posX) || (D_80195A30->posX == 0xFFFE))) {
            break;
        }
        D_80195A30--;
    }
}

INCLUDE_ASM("asm/us/st/rwrp/nonmatchings/A59C", func_8018C0F0);

INCLUDE_ASM("asm/us/st/rwrp/nonmatchings/A59C", func_8018C1EC);

void func_8018C300(s16 arg0) {
    while (true) {
        if (D_80195A34->posY != 0xFFFE && (s32)D_80195A34->posY >= arg0) {
            break;
        }
        D_80195A34++;
    }
}

void func_8018C34C(s16 arg0) {
    while (true) {
        if ((D_80195A34->posY != 0xFFFF) &&
            ((arg0 >= D_80195A34->posY) || (D_80195A34->posY == 0xFFFE))) {
            break;
        }
        D_80195A34--;
    }
}

INCLUDE_ASM("asm/us/st/rwrp/nonmatchings/A59C", func_8018C3A4);

INCLUDE_ASM("asm/us/st/rwrp/nonmatchings/A59C", func_8018C4A0);

INCLUDE_ASM("asm/us/st/rwrp/nonmatchings/A59C", func_8018C5B4);

INCLUDE_ASM("asm/us/st/rwrp/nonmatchings/A59C", func_8018C72C);

INCLUDE_ASM("asm/us/st/rwrp/nonmatchings/A59C", func_8018C7E0);

void func_8018C854(u16 entityId, Entity* source, Entity* entity) {
    DestroyEntity(entity);
    entity->entityId = entityId;
    entity->pfnUpdate = D_801803E0[entityId];
    entity->posX.i.hi = source->posX.i.hi;
    entity->posY.i.hi = source->posY.i.hi;
}

INCLUDE_ASM("asm/us/st/rwrp/nonmatchings/A59C", func_8018C8D0);

INCLUDE_ASM("asm/us/st/rwrp/nonmatchings/A59C", func_8018C948);

INCLUDE_ASM("asm/us/st/rwrp/nonmatchings/A59C", DestroyEntity);

INCLUDE_ASM("asm/us/st/rwrp/nonmatchings/A59C", func_8018D5EC);

INCLUDE_ASM("asm/us/st/rwrp/nonmatchings/A59C", PreventEntityFromRespawning);

INCLUDE_ASM("asm/us/st/rwrp/nonmatchings/A59C", func_8018D6B0);

u8 func_8018D768(u8 frames[], Entity* self, u8 arg2) {
    u16 animFrameStart = self->animFrameIdx * 2;
    u8* var_s1 = &frames[animFrameStart];
    s16 var_a1 = 0;

    if (self->animFrameDuration == 0) {
        if (*var_s1 != 0) {
            if (*var_s1 == 0xFF) {
                return 0;
            }
            self->animFrameDuration = *var_s1++ + (u8)self->ext.stub[0x3F];
            self->animCurFrame = *var_s1++;
            self->animFrameIdx++;
            var_a1 = 128;
        } else {
            var_s1 = frames;
            self->animFrameIdx = 0;
            self->animFrameDuration = 0;
            self->ext.stub[0x3F] = (arg2 * Random()) >> 8;
            self->animFrameDuration = *var_s1++ + (u8)self->ext.stub[0x3F];
            self->animCurFrame = *var_s1;
            self->animFrameIdx++;
            return 0;
        }
    }
    self->animFrameDuration--;
    self->animCurFrame = var_s1[-1];
    var_a1 |= 1;
    return var_a1;
}

s32 func_8018D880(void) {
    s16 temp_v1 = g_CurrentEntity->posX.i.hi - PLAYER.posX.i.hi;

    if (temp_v1 >> 16) {
        temp_v1 = -temp_v1;
    }
    return temp_v1;
}

INCLUDE_ASM("asm/us/st/rwrp/nonmatchings/A59C", func_8018D8BC);

INCLUDE_ASM("asm/us/st/rwrp/nonmatchings/A59C", func_8018D8F0);

void MoveEntity() {
    g_CurrentEntity->posX.val += g_CurrentEntity->velocityX;
    g_CurrentEntity->posY.val += g_CurrentEntity->velocityY;
}

void FallEntity(void) {
    if (g_CurrentEntity->velocityY < FALL_TERMINAL_VELOCITY) {
        g_CurrentEntity->velocityY += FALL_GRAVITY;
    }
}
INCLUDE_ASM("asm/us/st/rwrp/nonmatchings/A59C", func_8018D990);

s32 func_8018DC08(s16* posX) {
    Collider collider;
    s16 temp2;
    s16 temp4;
    s16 x, y;

    g_CurrentEntity->posX.val += g_CurrentEntity->velocityX;
    temp2 = g_CurrentEntity->posY.i.hi + 3;
    g_CurrentEntity->posY.i.hi = temp2;
    x = g_CurrentEntity->posX.i.hi + *posX;
    posX++;
    y = temp2 + *posX;
    g_api.CheckCollision(x, y, &collider, 0);
    if (!(collider.effects & EFFECT_SOLID)) {
        return 0;
    }
    posX++;

    g_CurrentEntity->posY.i.hi = g_CurrentEntity->posY.i.hi + collider.unk18;
    if (g_CurrentEntity->velocityX != 0) {
        if (g_CurrentEntity->velocityX < 0) {
            temp4 = x - *posX;
            posX++;
        } else {
            temp4 = x + *posX;
            posX++;
        }
        y = y + *posX - 7;
        g_api.CheckCollision(temp4, y, &collider, 0);
        if (collider.effects & EFFECT_SOLID) {
            if ((collider.effects & (EFFECT_UNK_8000 | EFFECT_UNK_0002)) ==
                EFFECT_UNK_0002) {
                g_CurrentEntity->posX.val =
                    g_CurrentEntity->posX.val - g_CurrentEntity->velocityX;
                g_CurrentEntity->velocityX = 0;
                return 0xFF;
            }
            return 0x61;
        }
        y += 15;
        g_api.CheckCollision(temp4, y, &collider, 0);
        if (collider.effects & EFFECT_SOLID) {
            if (collider.effects & EFFECT_UNK_8000) {
                return 0x61;
            }
            return 1;
        }
        g_CurrentEntity->posX.val -= g_CurrentEntity->velocityX;
        g_CurrentEntity->velocityX = 0;

        return 0x80;
    }
    return 1;
}

INCLUDE_ASM("asm/us/st/rwrp/nonmatchings/A59C", func_8018DDF0);

s32 func_8018DE50(u8 arg0, s16 arg1) { return D_80180A94[arg0] * arg1; }

s16 func_8018DE7C(u8 arg0) { return D_80180A94[arg0]; }

INCLUDE_ASM("asm/us/st/rwrp/nonmatchings/A59C", func_8018DE98);

INCLUDE_ASM("asm/us/st/rwrp/nonmatchings/A59C", func_8018DF04);

INCLUDE_ASM("asm/us/st/rwrp/nonmatchings/A59C", func_8018DF3C);

INCLUDE_ASM("asm/us/st/rwrp/nonmatchings/A59C", func_8018DF84);

INCLUDE_ASM("asm/us/st/rwrp/nonmatchings/A59C", func_8018DFCC);

INCLUDE_ASM("asm/us/st/rwrp/nonmatchings/A59C", func_8018E024);

INCLUDE_ASM("asm/us/st/rwrp/nonmatchings/A59C", func_8018E0B0);

INCLUDE_ASM("asm/us/st/rwrp/nonmatchings/A59C", func_8018E0E0);

INCLUDE_ASM("asm/us/st/rwrp/nonmatchings/A59C", func_8018E118);

INCLUDE_ASM("asm/us/st/rwrp/nonmatchings/A59C", func_8018E160);

void SetStep(u8 step) {
    g_CurrentEntity->step = step;
    g_CurrentEntity->step_s = 0;
    g_CurrentEntity->animFrameIdx = 0;
    g_CurrentEntity->animFrameDuration = 0;
}

void func_8018E1E0(u8 step_s) {
    g_CurrentEntity->step_s = step_s;
    g_CurrentEntity->animFrameIdx = 0;
    g_CurrentEntity->animFrameDuration = 0;
}

INCLUDE_ASM("asm/us/st/rwrp/nonmatchings/A59C", func_8018E1FC);

INCLUDE_ASM("asm/us/st/rwrp/nonmatchings/A59C", InitializeEntity);

INCLUDE_ASM("asm/us/st/rwrp/nonmatchings/A59C", func_8018E38C);

INCLUDE_ASM("asm/us/st/rwrp/nonmatchings/A59C", func_8018E3B4);

INCLUDE_ASM("asm/us/st/rwrp/nonmatchings/A59C", func_8018E4DC);

INCLUDE_ASM("asm/us/st/rwrp/nonmatchings/A59C", func_8018E634);

#include "../replace_breakable_with_item_drop.h"

void func_8018EA30(void) {
    s32 temp_v1;
    Entity* entity;

    entity = g_CurrentEntity;
    if (entity->velocityY >= 0) {
        temp_v1 =
            entity->ext.generic.unk88.S16.unk0 + entity->ext.generic.unk84.unk;
        entity->ext.generic.unk84.unk = temp_v1;
        entity->velocityX = temp_v1;
        if (temp_v1 == 0x10000 || temp_v1 == -0x10000) {
            entity->ext.generic.unk88.S16.unk0 =
                -entity->ext.generic.unk88.S16.unk0;
        }
        entity = g_CurrentEntity;
    }

    if (entity->velocityY < FIX(0.25)) {
        entity->velocityY += FIX(0.125);
    }
}

INCLUDE_ASM("asm/us/st/rwrp/nonmatchings/A59C", func_8018EAB4);

INCLUDE_ASM("asm/us/st/rwrp/nonmatchings/A59C", func_8018EC10);

INCLUDE_ASM("asm/us/st/rwrp/nonmatchings/A59C", func_8018EC90);

void CollectSubweapon(u16 subWeaponIdx) {
    Entity* player = &PLAYER;
    u16 subWeapon;

    g_api.PlaySfx(NA_SE_PL_IT_PICKUP);
    subWeapon = g_Status.subWeapon;
    g_Status.subWeapon = D_80180DC4[subWeaponIdx];

    if (subWeapon == g_Status.subWeapon) {
        subWeapon = 1;
        g_CurrentEntity->unk6D = 0x10;
    } else {
        subWeapon = D_80180DF4[subWeapon];
        g_CurrentEntity->unk6D = 0x60;
    }

    if (subWeapon != 0) {
        g_CurrentEntity->params = subWeapon;
        g_CurrentEntity->posY.i.hi = player->posY.i.hi + 12;
        SetStep(7);
        g_CurrentEntity->velocityY = FIX(-2.5);
        g_CurrentEntity->animCurFrame = 0;
        g_CurrentEntity->ext.generic.unk88.S16.unk2 = 5;
        if (player->facing != 1) {
            g_CurrentEntity->velocityX = FIX(-2);
            return;
        }
        g_CurrentEntity->velocityX = FIX(2);
        return;
    }
    DestroyEntity(g_CurrentEntity);
}

INCLUDE_ASM("asm/us/st/rwrp/nonmatchings/A59C", func_8018EE84);

INCLUDE_ASM("asm/us/st/rwrp/nonmatchings/A59C", func_8018EF28);

void func_8018EF78(void) { DestroyEntity(g_CurrentEntity); }

INCLUDE_ASM("asm/us/st/rwrp/nonmatchings/A59C", EntityPrizeDrop);

INCLUDE_ASM("asm/us/st/rwrp/nonmatchings/A59C", func_8018F814);

INCLUDE_ASM("asm/us/st/rwrp/nonmatchings/A59C", func_8018F910);

INCLUDE_ASM("asm/us/st/rwrp/nonmatchings/A59C", EntityEquipItemDrop);

INCLUDE_ASM("asm/us/st/rwrp/nonmatchings/A59C", func_8018FF9C);

INCLUDE_ASM("asm/us/st/rwrp/nonmatchings/A59C", func_8019024C);

INCLUDE_ASM("asm/us/st/rwrp/nonmatchings/A59C", func_80190D1C);

INCLUDE_ASM("asm/us/st/rwrp/nonmatchings/A59C", func_80190E44);

INCLUDE_ASM("asm/us/st/rwrp/nonmatchings/A59C", func_801913A0);

INCLUDE_ASM("asm/us/st/rwrp/nonmatchings/A59C", func_80191490);

INCLUDE_ASM("asm/us/st/rwrp/nonmatchings/A59C", func_801915A0);

INCLUDE_ASM("asm/us/st/rwrp/nonmatchings/A59C", func_801916D0);

INCLUDE_ASM("asm/us/st/rwrp/nonmatchings/A59C", func_801917B8);

INCLUDE_ASM("asm/us/st/rwrp/nonmatchings/A59C", func_801918A8);

INCLUDE_ASM("asm/us/st/rwrp/nonmatchings/A59C", func_8019199C);

INCLUDE_ASM("asm/us/st/rwrp/nonmatchings/A59C", func_80191BCC);

u8 func_80191CC8(s32 arg0) {
    Collider collider;
    u32 bits_67;
    u32 bits_45;
    u32 bits_23;
    u8 bits_01;
    u16 collEff;

    MoveEntity();
    bits_67 = 0;
    bits_23 = 0;
    bits_45 = 0;
    bits_01 = arg0 & 3;
    collEff = 0;
    switch (bits_01) {
    case 0:
        g_CurrentEntity->posY.i.hi += 3;
        g_api.CheckCollision(g_CurrentEntity->posX.i.hi,
                             g_CurrentEntity->posY.i.hi, &collider, 0);
        if (collider.effects != 0) {
            collEff = collider.effects;
            g_CurrentEntity->posY.i.hi += collider.unk18;
            g_api.CheckCollision(
                g_CurrentEntity->posX.i.hi,
                (s16)(g_CurrentEntity->posY.i.hi - 4), &collider, 0);
            if (collider.effects & EFFECT_UNK_0002) {
                bits_67 = 0x40;
                if (g_CurrentEntity->velocityX > 0) {
                    bits_01 = 2;
                } else {
                    bits_01 = 3;
                    g_CurrentEntity->velocityX = -g_CurrentEntity->velocityX;
                }
                g_CurrentEntity->velocityY = -g_CurrentEntity->velocityX;
                g_CurrentEntity->velocityX = 0;
            }
        } else {
            bits_67 = 0x80;
            g_CurrentEntity->posX.val -= g_CurrentEntity->velocityX;
            if (g_CurrentEntity->velocityX > 0) {
                bits_01 = 3;
            } else {
                bits_01 = 2;
                g_CurrentEntity->velocityX = -g_CurrentEntity->velocityX;
            }
            g_CurrentEntity->velocityY = g_CurrentEntity->velocityX;
            g_CurrentEntity->velocityX = 0;
        }
        break;

    case 1:
        g_CurrentEntity->posY.i.hi -= 3;
        g_api.CheckCollision(g_CurrentEntity->posX.i.hi,
                             g_CurrentEntity->posY.i.hi, &collider, 0);
        if (collider.effects != 0) {
            collEff = collider.effects;
            g_CurrentEntity->posY.i.hi += collider.unk20;
            g_api.CheckCollision(
                g_CurrentEntity->posX.i.hi,
                (s16)(g_CurrentEntity->posY.i.hi + 4), &collider, 0);
            if (collider.effects & EFFECT_UNK_0002) {
                bits_67 = 0x40;
                if (g_CurrentEntity->velocityX > 0) {
                    bits_01 = 2;
                } else {
                    bits_01 = 3;
                    g_CurrentEntity->velocityX = -g_CurrentEntity->velocityX;
                }
                g_CurrentEntity->velocityY = g_CurrentEntity->velocityX;
                g_CurrentEntity->velocityX = 0;
            }
        } else {
            bits_67 = 0x80;
            g_CurrentEntity->posX.val -= g_CurrentEntity->velocityX;
            if (g_CurrentEntity->velocityX > 0) {
                bits_01 = 3;
            } else {
                bits_01 = 2;
                g_CurrentEntity->velocityX = -g_CurrentEntity->velocityX;
            }
            g_CurrentEntity->velocityY = -g_CurrentEntity->velocityX;
            g_CurrentEntity->velocityX = 0;
        }
        break;

    case 2:
        g_CurrentEntity->posX.i.hi += 3;
        g_api.CheckCollision(g_CurrentEntity->posX.i.hi,
                             g_CurrentEntity->posY.i.hi, &collider, 0);
        if (collider.effects != 0) {
            collEff = collider.effects;
            g_CurrentEntity->posX.i.hi += collider.unk14;
            g_api.CheckCollision((s16)(g_CurrentEntity->posX.i.hi - 4),
                                 g_CurrentEntity->posY.i.hi, &collider, 0);
            if (collider.effects & EFFECT_SOLID) {
                bits_67 = 0x40;
                if (g_CurrentEntity->velocityY > 0) {
                    bits_01 = 0;
                } else {
                    bits_01 = 1;
                    g_CurrentEntity->velocityY = -g_CurrentEntity->velocityY;
                }
                g_CurrentEntity->velocityX = -g_CurrentEntity->velocityY;
                g_CurrentEntity->velocityY = 0;
            }
        } else {
            bits_67 = 0x80;
            g_CurrentEntity->posY.val -= g_CurrentEntity->velocityY;
            if (g_CurrentEntity->velocityY > 0) {
                bits_01 = 1;
            } else {
                bits_01 = 0;
                g_CurrentEntity->velocityY = -g_CurrentEntity->velocityY;
            }
            g_CurrentEntity->velocityX = g_CurrentEntity->velocityY;
            g_CurrentEntity->velocityY = 0;
        }
        break;

    case 3:
        g_CurrentEntity->posX.i.hi -= 3;
        g_api.CheckCollision(g_CurrentEntity->posX.i.hi,
                             g_CurrentEntity->posY.i.hi, &collider, 0);
        if (collider.effects != 0) {
            collEff = collider.effects;
            g_CurrentEntity->posX.i.hi += collider.unk1C;
            g_api.CheckCollision((s16)(g_CurrentEntity->posX.i.hi + 4),
                                 g_CurrentEntity->posY.i.hi, &collider, 0);
            if (collider.effects & EFFECT_SOLID) {
                bits_67 = 0x40;
                if (g_CurrentEntity->velocityY > 0) {
                    bits_01 = 0;
                } else {
                    bits_01 = 1;
                    g_CurrentEntity->velocityY = -g_CurrentEntity->velocityY;
                }
                g_CurrentEntity->velocityX = g_CurrentEntity->velocityY;
                g_CurrentEntity->velocityY = 0;
            }
        } else {
            bits_67 = 0x80;
            g_CurrentEntity->posY.val -= g_CurrentEntity->velocityY;
            if (g_CurrentEntity->velocityY > 0) {
                bits_01 = 1;
            } else {
                bits_01 = 0;
                g_CurrentEntity->velocityY = -g_CurrentEntity->velocityY;
            }
            g_CurrentEntity->velocityX = -g_CurrentEntity->velocityY;
            g_CurrentEntity->velocityY = 0;
        }
    }

    if (collEff & EFFECT_UNK_8000) {
        bits_23 = 4;
    }
    if (collEff & EFFECT_UNK_1000) {
        bits_23 = 8;
    }
    if (collEff & EFFECT_UNK_2000) {
        bits_23 = 0xC;
    }
    if (collEff & EFFECT_UNK_0800) {
        bits_45 = 0x20;
    }
    if (collEff & EFFECT_UNK_4000) {
        bits_45 = 0x10;
    }
    bits_01 = (bits_45 + (bits_23 + (bits_67 + bits_01)));
    return bits_01;
}

#include "../entity_intense_explosion.h"

INCLUDE_ASM("asm/us/st/rwrp/nonmatchings/A59C", func_80192348);

INCLUDE_ASM("asm/us/st/rwrp/nonmatchings/A59C", func_80192414);

INCLUDE_ASM("asm/us/st/rwrp/nonmatchings/A59C", func_801924DC);

INCLUDE_ASM("asm/us/st/rwrp/nonmatchings/A59C", func_80192594);

INCLUDE_ASM("asm/us/st/rwrp/nonmatchings/A59C", func_8019276C);

INCLUDE_ASM("asm/us/st/rwrp/nonmatchings/A59C", func_80192D4C);

void ClutLerp(RECT* rect, u16 palIdxA, u16 palIdxB, s32 steps, u16 offset) {
    u16 buf[COLORS_PER_PAL];
    RECT bufRect;
    s32 factor;
    u32 t;
    u32 r, g, b;
    s32 i, j;
    u16 *palA, *palB;

    bufRect.x = rect->x;
    bufRect.w = COLORS_PER_PAL;
    bufRect.h = 1;

    palA = g_Clut + palIdxA * COLORS_PER_PAL;
    palB = g_Clut + palIdxB * COLORS_PER_PAL;

    for (i = 0; i < steps; i++) {
        factor = i * 4096 / steps;
        for (j = 0; j < COLORS_PER_PAL; j++) {
            r = (palA[j] & 0x1F) * (4096 - factor) + (palB[j] & 0x1F) * factor;
            g = ((palA[j] >> 5) & 0x1F) * (4096 - factor) +
                ((palB[j] >> 5) & 0x1F) * factor;
            b = ((palA[j] >> 10) & 0x1F) * (4096 - factor) +
                ((palB[j] >> 10) & 0x1F) * factor;

            t = palA[j] & 0x8000;
            t |= palB[j] & 0x8000;

            buf[j] = t | (r >> 12) | ((g >> 12) << 5) | ((b >> 12) << 10);
        }

        bufRect.y = rect->y + i;
        LoadImage(&bufRect, buf);
        D_8003C104[offset + i] = GetClut(bufRect.x, bufRect.y);
    }
}

INCLUDE_ASM("asm/us/st/rwrp/nonmatchings/A59C", func_80193644);

INCLUDE_ASM("asm/us/st/rwrp/nonmatchings/A59C", func_8019373C);

INCLUDE_ASM("asm/us/st/rwrp/nonmatchings/A59C", func_8019390C);

// The white flying orbs of energy that Alucard summons as part of the Soul
// Steal spell
void EntitySoulStealOrb(Entity* self) {
    Primitive* prim;
    s32 primIndex;
    u16 *temp_d, temp_e;
    s32 temp_a, temp_b;
    u16 angle;

    switch (self->step) {
    case 0:
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 1);
        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        InitializeEntity(D_8018044C);
        D_8008701E[primIndex * 0x1a] = 8;
        self->primIndex = primIndex;
        self->animSet = ANIMSET_DRA(0);
        self->flags |= FLAG_HAS_PRIMS;
        angle = func_8018E0E0(self, &PLAYER);
        temp_a = self->posY.i.hi < 113;
        temp_b = temp_a ^ 1;
        if (self->posX.i.hi < PLAYER.posX.i.hi) {
            temp_b = temp_a;
        }
        if (temp_b & 0xFFFF) {
            self->ext.soulStealOrb.angle = angle - D_801810A0[Random() & 7];
        } else {
            angle += D_801810A0[Random() & 7];
            self->ext.soulStealOrb.angle = angle;
        }
        self->ext.soulStealOrb.unk80 = 0x400;
        self->ext.soulStealOrb.unk7E = 0;
        self->hitboxState = 0;
        break;

    case 1:
        self->ext.soulStealOrb.unk82++;
        if (self->ext.soulStealOrb.unk82 == 16) {
            self->hitboxState = 1;
        }
        if (self->hitFlags != 0) {
            if (g_Player.unk56 == 0) {
                g_Player.unk56 = 1;
                g_Player.unk58 = 8;
            }
            DestroyEntity(self);
            return;
        }
        if (self->unk1A < 0x100) {
            self->unk1A = self->unk1C += 0x10;
        }
        if (self->ext.soulStealOrb.unk7E < 0x200) {
            self->ext.soulStealOrb.unk7E += 2;
        }
        if (self->ext.soulStealOrb.unk80 < 0x800) {
            self->ext.soulStealOrb.unk80 += 4;
        }
        self->ext.soulStealOrb.angle = func_8018E160(
            self->ext.soulStealOrb.unk7E, (u16)self->ext.soulStealOrb.angle,
            0xffff & func_8018E0E0(self, &PLAYER));
        func_8018E024(self->ext.soulStealOrb.angle & 0xFFFF,
                      self->ext.soulStealOrb.unk80);
        MoveEntity(self); // argument pass necessary to match
        prim = &g_PrimBuf[self->primIndex];
        func_8018D6B0(&D_80181110, self);
        angle = (float)(u32)self; // !FAKE
        prim->tpage = 0x18;
        prim->clut = 0x194;
        temp_d = &D_801810B0[(u16)((8 * (u16)self->animCurFrame) - 8)];
        prim->x0 = prim->x2 = self->posX.i.hi + *(temp_d++);
        prim->y0 = prim->y1 = self->posY.i.hi + *(temp_d++);
        prim->x1 = prim->x3 = prim->x0 + *(temp_d++);
        prim->y2 = prim->y3 = prim->y0 + *(temp_d++);
        prim->u0 = prim->u2 = *(temp_d++);
        prim->v0 = prim->v1 = *(temp_d++);
        prim->u1 = prim->u3 = *(temp_d++);
        prim->v2 = prim->v3 = *(temp_d++);
        prim->priority = self->zPriority;
        prim->blendMode = 0;
        break;
    }
}

INCLUDE_ASM("asm/us/st/rwrp/nonmatchings/A59C", func_80194924);

void func_80194DD4(Entity* entity) {
    ObjInit2* objInit = &D_80181134[entity->params];

    if (entity->step == 0) {
        InitializeEntity(D_80180494);
        entity->animSet = objInit->animSet;
        entity->zPriority = objInit->zPriority;
        entity->unk5A = objInit->unk4.s;
        entity->palette = objInit->palette;
        entity->unk19 = objInit->unk8;
        entity->blendMode = objInit->blendMode;
        if (objInit->unkC != 0) {
            entity->flags = objInit->unkC;
        }
        if (entity->params >= 5) {
            entity->rotAngle = 0x800;
            entity->unk19 = (u8)(entity->unk19 | 4);
        }
    }
    func_8018D6B0(objInit->unk10, entity);
}

INCLUDE_ASM("asm/us/st/rwrp/nonmatchings/A59C", func_80194EC0);

INCLUDE_ASM("asm/us/st/rwrp/nonmatchings/A59C", func_801951F0);

INCLUDE_ASM("asm/us/st/rwrp/nonmatchings/A59C", func_801955D8);

INCLUDE_ASM("asm/us/st/rwrp/nonmatchings/A59C", func_80195728);

INCLUDE_ASM("asm/us/st/rwrp/nonmatchings/A59C", func_80195758);

INCLUDE_ASM("asm/us/st/rwrp/nonmatchings/A59C", func_801957D4);

INCLUDE_ASM("asm/us/st/rwrp/nonmatchings/A59C", func_8019585C);

INCLUDE_ASM("asm/us/st/rwrp/nonmatchings/A59C", func_8019593C);

INCLUDE_ASM("asm/us/st/rwrp/nonmatchings/A59C", func_80195990);

#include "../unk_loop_func.h"
