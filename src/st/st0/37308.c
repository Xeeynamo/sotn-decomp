// SPDX-License-Identifier: AGPL-3.0-or-later
#include "game.h"
#include "st0.h"
#include "sfx.h"

const char* g_RelicOrbTexts[] = {"を入手した"};
s16 g_RelicOrbTextBg1EY[] = {16, 12, 8, 4, 0, -4, -8, -12};
s16 g_RelicOrbTextBg1SY[] = {-32, -26, -20, -13, -7, -1, 5, 12};
s16 g_RelicOrbTextBg2SY[] = {-16, -12, -8, -4, 0, 4, 8, 12};
s16 g_RelicOrbTextBg2EY[] = {32, 26, 20, 13, 7, 1, -5, -12};

extern u16 D_801C00B0[0x600];

void EntityRelicOrb(Entity* self) {
    // prim 0: green rectangle for Obtained text bg
    // prim 1: blue rectangle for Obtained text bg

    const int MaxItemSlots = LEN(g_ItemIconSlots);

    u16 relicId;
    u16 isObtainedTextStored;

    RECT rect;
    Primitive* prim;
    const char* msg;
    s32 primIndex;
    s16 iconSlot;
    s32 i;
    u8* chPix;
    u16 var_s8;
    u16 msgLen;

    u16 vramX;
    u16* chPixSrc;
    u16* chPixDst;
    u16 ch;
    s16 left, top, right, bottom;

    relicId = self->params & 0x7FFF;
    if (self->step && self->step < 5 && self->hitFlags) {
        self->step = 5;
    }

    switch (self->step) {
    case 0:

        InitializeEntity(g_InitializeData0);
        for (iconSlot = 0; iconSlot < MaxItemSlots; iconSlot++) {
            if (!g_ItemIconSlots[iconSlot]) {
                break;
            }
        }

        if (iconSlot >= MaxItemSlots) {
            self->step = 0;
            return;
        }

        primIndex = g_api.AllocPrimitives(PRIM_GT4, 3);
        if (primIndex == -1) {
            self->step = 0;
            return;
        }
        self->flags |= FLAG_HAS_PRIMS;
        self->primIndex = primIndex;
        g_api.LoadEquipIcon(g_api.equipDefs[relicId].icon,
                            g_api.equipDefs[relicId].iconPalette, iconSlot);
        prim = &g_PrimBuf[primIndex];
        for (i = 0; prim != NULL; i++) {
            if (i != 0) {
                prim->type = PRIM_G4;
                prim->drawMode = DRAW_HIDE;
            } else {
                prim->tpage = 0x1A;
                prim->clut = iconSlot + 0x1D0;
                // Pulls iconSlot & 0b00111
                prim->u0 = prim->u2 = ((iconSlot & 7) << 4) + 1;
                prim->u1 = prim->u3 = prim->u0 + 14;
                // Pulls iconSlot & 0b11000
                prim->v0 = prim->v1 = ((iconSlot & 24) << 1) + 0x81;
                prim->v2 = prim->v3 = prim->v0 + 14;
                prim->drawMode = DRAW_UNK02;
            }
            prim->priority = 0xC0;
            prim = prim->next;
        }

        break;

    case 5:
        g_api.PlaySfx(0x618);

        g_Status.relics[relicId] = 3;

        // Reserve space in the VRAM to store the pre-render texture with the
        // "obtained" relic message
        rect.x = 0;
        rect.y = 256;
        rect.w = 64;
        rect.h = 16;
        ClearImage(&rect, 0, 0, 0);

        prim = &g_PrimBuf[self->primIndex];
        for (i = 0; prim != NULL; prim = prim->next, i++) {
            if (i == 0) {
                prim->type = PRIM_SPRT;
                prim->tpage = 0x10;
                prim->x0 = 0x10;
                prim->y0 = 0xA0;
                prim->u0 = 0;
                prim->v0 = 0;
                prim->u1 = 0xF0;
                prim->v1 = 0x10;
                prim->clut = 0x1F8;
                prim->priority = 0x1FE;

                prim->drawMode = DRAW_HIDE;
            } else {
                prim->x0 = prim->x1 = prim->x2 = prim->x3 = 0x80;
                prim->y0 = prim->y1 = prim->y2 = prim->y3 = 0xA7;
                prim->r0 = prim->r1 = prim->r2 = prim->r3 = 0;
                prim->g0 = prim->g1 = prim->g2 = prim->g3 = 0;
                prim->b0 = prim->b1 = prim->b2 = prim->b3 = 0;

                if (i == 1) {
                    prim->b0 = prim->b1 = prim->b2 = prim->b3 = 0x80;
                } else {
                    prim->g0 = prim->g1 = prim->g2 = prim->g3 = 0x80;
                }
                prim->priority = 0x1FD;
                prim->drawMode = DRAW_TPAGE | DRAW_TRANSP;
            }
        }

        self->step++;
        break;

    case 6:
        msgLen = 0;
        isObtainedTextStored = false;
        vramX = 0;
        msg = g_api.relicDefs[relicId].name;
        while (true) {
            ch = *msg++;
            if (ch == 0) {
                if (isObtainedTextStored) {
                    break;
                }
                isObtainedTextStored = true;
                msg = g_RelicOrbTexts[0];
            } else {
                ch = (ch << 8) | *msg++;
                chPixSrc = g_api_func_80106A28(ch, 1);
                if (chPixSrc != NULL) {
                    chPixDst = &D_801C00B0[msgLen * 0x30];
                    for (i = 0; i < 0x30; i++) {
                        *chPixDst++ = *chPixSrc++;
                    }
                    LoadTPage(&D_801C00B0[msgLen * 0x30], 0, 0, vramX, 0x100,
                              0xC, 0x10);
                    vramX += 3;
                    msgLen++;
                }
            }
        }
        self->ext.relicOrb.unk7E = msgLen;
        self->ext.relicOrb.unk7C = 0;
        self->step++;
        break;
    case 7:
        // Animates the blue/green rectangle for the Obtain text bg
        prim = &g_PrimBuf[self->primIndex];
        prim = prim->next;
        for (i = 0; prim != NULL; prim = prim->next, i++) {
            if (i == 0) {
                prim->x2 -= 3;
                prim->x3 += 3;
                prim->y0 = prim->y1 -= 4;
                prim->y2 = prim->y3 += 2;
            } else {
                prim->x0 -= 3;
                prim->x1 += 3;
                prim->y0 = prim->y1 -= 2;
                prim->y2 = prim->y3 += 4;
            }
        }

        if (++self->ext.relicOrb.unk7C == 8) {
            self->ext.relicOrb.unk7C = 0;
            self->step++;
        }
        break;

    case 8:
        isObtainedTextStored = self->ext.relicOrb.unk7C;
        prim = &g_PrimBuf[self->primIndex];
        prim = prim->next;
        for (i = 0; prim != NULL; prim = prim->next, i++) {
            if (i == 0) {
                prim->x1 = 0x80 - (isObtainedTextStored + 1) * 0xC;
                prim->x0 = 0x80 + (isObtainedTextStored + 1) * 0xC;
                prim->x2 = 0x68 + (isObtainedTextStored * 0x78) / 7;
                prim->x3 = 0x98 - (isObtainedTextStored * 0x78) / 7;
                prim->y0 = prim->y1 =
                    g_RelicOrbTextBg1SY[isObtainedTextStored] + 0xA7;
                prim->y2 = prim->y3 =
                    g_RelicOrbTextBg1EY[isObtainedTextStored] + 0xA7;
                prim->b2 = prim->b3 -= 0x10;
            } else {
                prim->x0 = 0x68 + (isObtainedTextStored * 0x78) / 7;
                prim->x1 = 0x98 - (isObtainedTextStored * 0x78) / 7;
                prim->x3 = 0x80 - (isObtainedTextStored + 1) * 0xC;
                prim->x2 = 0x80 + (isObtainedTextStored + 1) * 0xC;
                prim->y0 = prim->y1 =
                    g_RelicOrbTextBg2SY[isObtainedTextStored] + 0xA7;
                prim->y2 = prim->y3 =
                    g_RelicOrbTextBg2EY[isObtainedTextStored] + 0xA7;
                prim->g0 = prim->g1 -= 0x10;
            }
        }

        if (++self->ext.relicOrb.unk7C == 8) {
            self->step++;
            self->ext.relicOrb.unk7C = 0;
        }
        break;

    case 9:
        prim = &g_PrimBuf[self->primIndex];
        prim->x0 = 0x80 - self->ext.relicOrb.unk7E * 6;
        prim->drawMode = DRAW_DEFAULT;
        self->ext.relicOrb.unk7C++;
        if (self->ext.relicOrb.unk7C > 0x100) {
            DestroyEntity(self);
            return;
        }
        break;
    }

    if (self->step < 2) {
        prim = &g_PrimBuf[self->primIndex];
        prim->x0 = prim->x2 = self->posX.i.hi - 7;
        prim->x1 = prim->x3 = prim->x0 + 14;
        prim->y0 = prim->y1 = self->posY.i.hi - 7;
        prim->y2 = prim->y3 = prim->y0 + 14;
    }
}

#include "../check_coll_offsets.h"

#include "../entity_unkId13.h"

#include "../entity_unkId14_spawner.h"

#include "../entity_unkId15_spawner.h"

#include "../entity_unkId14.h"

#include "../entity_unkId15.h"

#include "../entity_olrox_drool.h"

#include "../unk_collision_func5.h"

#include "../unk_collision_func4.h"

#include "../entity_intense_explosion.h"

#include "../initialize_unk_entity.h"

#include "../make_entity_from_id.h"

#include "../make_explosions.h"

#include "../entity_big_red_fireball.h"

#include "../unk_recursive_primfunc_1.h"

#include "../unk_recursive_primfunc_2.h"

#include "../clut_lerp.h"

#include "../play_sfx_positional.h"

#include "../entity_soul_steal_orb.h"

#include "../entity_enemy_blood.h"

extern ObjInit D_80181FE8[];
void EntityRoomForeground(Entity* entity) {
    ObjInit* objInit = &D_80181FE8[entity->params];

    if (entity->step == 0) {
        InitializeEntity(g_eInitGeneric2);
        entity->animSet = objInit->animSet;
        entity->zPriority = objInit->zPriority;
        entity->unk5A = objInit->unk5A;
        entity->palette = objInit->palette;
        entity->drawFlags = objInit->drawFlags;
        entity->drawMode = objInit->drawMode;
        if (objInit->unkC != 0) {
            entity->flags = objInit->unkC;
        }
        if (entity->params >= 5) {
            entity->rotZ = 0x800;
            entity->drawFlags |= FLAG_DRAW_ROTZ;
        }
    }
    AnimateEntity(objInit->unk10, entity);
}

#include "../popup.h"

INCLUDE_ASM("st/st0/nonmatchings/37308", EntityClouds);

INCLUDE_ASM("st/st0/nonmatchings/37308", EntityClockTower3D);

INCLUDE_ASM("st/st0/nonmatchings/37308", EntityCutscenePhotograph);

void EntityCutscenePhotographFire(Entity* entity) {
    switch (entity->step) {
    case 0:
        InitializeEntity(D_801805D4);
        entity->animSet = ANIMSET_OVL(7);
        entity->unk5A = 0x57;
        entity->palette = 0x8285;
        entity->drawFlags = FLAG_DRAW_UNK8;
        entity->unk6C = 0x40;
        entity->flags &= ~FLAG_POS_CAMERA_LOCKED;
        if (entity->params) {
            entity->unk6C = 0x10;
            entity->zPriority = 0x1FB;
            entity->drawMode = DRAW_UNK_40 | DRAW_TPAGE;
        } else {
            entity->zPriority = 0x1FE;
            entity->drawMode = DRAW_TPAGE2 | DRAW_TPAGE;
        }
    case 1:
        entity->posY.val -= FIX(1.0);
        if (AnimateEntity(D_801824CC, entity) == 0) {
            DestroyEntity(entity);
        }
        break;
    }
}

INCLUDE_ASM("st/st0/nonmatchings/37308", func_801BC5C0);
