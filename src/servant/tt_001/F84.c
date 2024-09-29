// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include <sfx.h>
#include <servant.h>

extern s32 g_IsServantDestroyed;
extern s32 D_us_801704A8;
extern s32 D_us_80170500;
extern s32 D_us_80170508[];
extern s32 D_us_8017050C[];
extern s16 D_us_801737C4;
extern s16 D_us_801737C8;
extern s32 D_us_801737CC;
extern s32 D_us_801737D8;
extern s32 D_us_801737DC;
extern FamiliarStats D_us_80173810;

s32 ServantUnk0();
void ProcessEvent(Entity* self, bool resetEvent);

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
ServantDesc g_ServantDesc = {
    func_us_80171624, func_us_80171864, func_us_801720A4, func_us_801720AC,
    func_us_801720B4, func_us_801720BC, func_us_801720C4, func_us_801720CC,
    func_us_801720D4, func_us_801720DC, func_us_801720E4, func_us_8017246C,
    func_us_801728EC, func_us_801728F4, func_us_801728FC, DestroyServantEntity};

#include "../set_entity_animation.h"

s32 UpdateEntityVelocityTowardsTarget(s32 unused, s32 targetX, s32 targetY) {
    // AngleToTarget
    D_us_801735B8 = CalculateAngleToEntity(g_CurrentEntity, targetX, targetY);
    // BufferedTargetPosition
    D_us_801735BC = GetTargetPositionWithDistanceBuffer(
        D_us_801735B8, g_CurrentEntity->ext.factory.unk82,
        g_CurrentEntity->ext.factory.unk84);
    g_CurrentEntity->ext.factory.unk82 = D_us_801735BC;
    // DeltaX
    D_us_801735B0 = targetX - g_CurrentEntity->posX.i.hi;
    // DeltaY
    D_us_801735B4 = targetY - g_CurrentEntity->posY.i.hi;
    // DistanceToTarget
    D_us_801735C0 =
        SquareRoot12(
            ((D_us_801735B0 * D_us_801735B0) + (D_us_801735B4 * D_us_801735B4))
            << 0xC) >>
        0xC;

    switch (g_CurrentEntity->step) {
    case 2:
        g_CurrentEntity->velocityX = rcos(D_us_801735BC) * D_us_801735C0 * 2;
        g_CurrentEntity->velocityY = -(rsin(D_us_801735BC) * D_us_801735C0 * 2);
        break;
    case 3:
        g_CurrentEntity->velocityX = rcos(D_us_801735BC) * D_us_801735C0 * 8;
        g_CurrentEntity->velocityY = -(rsin(D_us_801735BC) * D_us_801735C0 * 8);
        break;
    default:
        g_CurrentEntity->velocityX = (rcos(D_us_801735BC) * D_us_801735C0) >> 2;
        g_CurrentEntity->velocityY =
            -((rsin(D_us_801735BC) * D_us_801735C0) >> 2);
        break;
    }

    // Clamp velocity so it cannot go too low/high
    if (g_CurrentEntity->velocityX > 0 &&
        g_CurrentEntity->velocityX < FIX(0.25)) {
        g_CurrentEntity->velocityX = FIX(0.25);
    } else if (g_CurrentEntity->velocityX < 0 &&
               g_CurrentEntity->velocityX > FIX(-0.25)) {
        g_CurrentEntity->velocityX = FIX(-0.25);
    }

    if (g_CurrentEntity->velocityY > 0 &&
        g_CurrentEntity->velocityY < FIX(0.25)) {
        g_CurrentEntity->velocityY = FIX(0.25);
    } else if (g_CurrentEntity->velocityY < 0 &&
               g_CurrentEntity->velocityY > FIX(-0.25)) {
        g_CurrentEntity->velocityY = FIX(-0.25);
    }

    if (D_us_801735C0 > 0x100) {
        g_CurrentEntity->velocityX =
            (targetX - g_CurrentEntity->posX.i.hi) << 0xE;
        g_CurrentEntity->velocityY =
            (targetY - g_CurrentEntity->posY.i.hi) << 0xE;
    }

    // Return the distance between entity and target
    return D_us_801735C0;
}

INCLUDE_ASM("servant/tt_001/nonmatchings/F84", func_us_80171284);

#include "../check_entity_valid.h"

void func_us_80171560(Entity* self) {}

#if defined(VERSION_PSP)
void func_psp_092EA460(Entity* self, s32 entityId, s32 params) {
#else
Entity* func_us_80171568(Entity* self, s32 entityId) {
#endif
    Entity* entity;
    s32 i;

    for (i = 0; i < 3; i++) {
        entity = &g_Entities[i + 5];
        if (!entity->entityId) {
            break;
        }
    }

    if (!entity->entityId) {
        DestroyEntity(entity);
#if defined(VERSION_PSP)
        entity->entityId = entityId;
#else
        if (entityId == 0) {
            entity->entityId = 0xDA;
        } else {
            entity->entityId = 0xDB;
        }
#endif
        entity->zPriority = self->zPriority;
        entity->facingLeft = self->facingLeft;
        entity->flags = FLAG_KEEP_ALIVE_OFFCAMERA;
        entity->posX.val = self->posX.val;
        entity->posY.val = self->posY.val;
        entity->ext.factory.parent = self;
#if defined(VERSION_PSP)
        entity->params = params;
#else
        return entity;
#endif
    }
    // BUG? There is a fall-through case here with no return value on PSX
}

INCLUDE_ASM("servant/tt_001/nonmatchings/F84", func_us_80171624);

void func_us_80171864(Entity* self) {
    s32 temp_v1;
    s32 temp_v0;

    g_api.func_8011A3AC(self, 0, 0, &D_us_80173810);
    if (g_IsServantDestroyed) {
        self->zPriority = PLAYER.zPriority - 2;
    }
    self->hitboxWidth = 0;
    self->hitboxHeight = 0;
    if (self->step < 2) {
        if (D_8003C708.flags & 0x20) {
            switch (ServantUnk0()) {
            case 0:
                D_us_801737D8 = 0x40;
                break;
            case 1:
                D_us_801737D8 = 0xC0;
                break;
            case 2:
                if (self->posX.i.hi >= 0x81) {
                    temp_v1 = 0xC0;
                } else {
                    temp_v1 = 0x40;
                }
                D_us_801737D8 = temp_v1;
                break;
            }
            D_us_801737DC = 0xA0;
        } else {
            if (PLAYER.facingLeft) {
                D_us_801737D8 = PLAYER.posX.i.hi + 0x12;
            } else {
                D_us_801737D8 = PLAYER.posX.i.hi - 0x12;
            }
            D_us_801737DC = PLAYER.posY.i.hi - 0x20;
        }
    }
    D_us_801737C4 = D_us_801737D8;
    D_us_801737C8 = D_us_801737DC + (rsin(self->ext.ghost.unk80) >> 0xA);
    self->ext.ghost.unk80 = ((u16)self->ext.ghost.unk80 + 0x20) & 0xFFF;
    switch (self->step) {
    case 0:
        self->ext.ghost.unk7E = (s16)self->params;
        self->flags =
            FLAG_POS_CAMERA_LOCKED | FLAG_KEEP_ALIVE_OFFCAMERA | FLAG_UNK_20000;
        self->drawMode = DRAW_TPAGE2 | DRAW_TPAGE;
        self->drawFlags = FLAG_DRAW_UNK8;
        SetEntityAnimation(self, &D_us_801704A8);
        self->ext.ghost.unk84 = 0x200;
        self->ext.ghost.unk88 = 0x80;
        self->ext.ghost.unk8A = -1;
        self->step++;
        break;
    case 1:
        if (g_Player.unk0C &
            (PLAYER_STATUS_BAT_FORM | PLAYER_STATUS_AXEARMOR)) {
            self->step = 4;
            self->ext.ghost.unk8C = 0;
            break;
        }
        if (D_8003C708.flags & 0x20) {
            if (PLAYER.posX.i.hi >= self->posX.i.hi)
                self->facingLeft = 1;
            else
                self->facingLeft = 0;
        } else {
            if (PLAYER.facingLeft == self->facingLeft) {
                if (abs((s32)D_us_801737C4 - self->posX.i.hi) <= 0) {
                    self->facingLeft = !PLAYER.facingLeft;

                } else { // 3e0
                    if (self->facingLeft && D_us_801737C4 < self->posX.i.hi) {
                        if (PLAYER.facingLeft)
                            temp_v0 = 0;
                        else
                            temp_v0 = 1;
                        self->facingLeft = (u16)temp_v0;
                    } else if (!self->facingLeft) {
                        if (D_us_801737C4 > self->posX.i.hi) {
                            if (PLAYER.facingLeft)
                                temp_v0 = 0;
                            else
                                temp_v0 = 1;
                            self->facingLeft = (u16)temp_v0;
                        }
                    }
                }
            } else {
                if (self->facingLeft &&
                    self->posX.i.hi - D_us_801737C4 >= 0x20) {
                    self->facingLeft = PLAYER.facingLeft;
                } else if (!self->facingLeft) {
                    if (D_us_801737C4 - self->posX.i.hi >= 0x20) {
                        self->facingLeft = PLAYER.facingLeft;
                    }
                }
            }
        }
        UpdateEntityVelocityTowardsTarget(self, D_us_801737C4, D_us_801737C8);
        self->posX.val += self->velocityX;
        self->posY.val += self->velocityY;
        if (D_8003C704 == 0) {
            self->ext.ghost.unkA2 = func_us_80171284(self);
            if (self->ext.ghost.unkA2) {
                self->step++;
                break;
            }
        }
        break;
    case 2:
    case 3:
        if (g_Player.unk0C &
            (PLAYER_STATUS_BAT_FORM | PLAYER_STATUS_AXEARMOR)) {
            self->step = 4;
            self->ext.ghost.unk8C = 0;
            break;
        }
        if (D_8003C704) {
            self->step = 1;
        }
        if (!CheckEntityValid(self->ext.ghost.unkA2)) {
            self->step = 1;
            break;
        }

        D_us_801737C4 = self->ext.ghost.unkA2->posX.i.hi;
        D_us_801737C8 = self->ext.ghost.unkA2->posY.i.hi;
        if (self->velocityX > 0) {
            self->facingLeft = 1;
        }
        if (self->velocityX < 0) {
            self->facingLeft = 0;
        }
        D_us_801737CC = UpdateEntityVelocityTowardsTarget(
            self, (s16)D_us_801737C4, D_us_801737C8);
        if (self->step == 2) {
            if (D_us_801737CC < 8) {
                self->ext.ghost.unk86 = 0;
                self->step += 1;
            }
        } else if (D_us_801737CC < 8) {
            self->ext.ghost.unk86++;
            temp_v1 = D_us_80170508[((D_us_80173810.level / 10) * 3)];
            if (self->ext.ghost.unk86 == (temp_v1 - 0x1E)) {
                self->ext.ghost.unk92 = func_us_80171568(self, 0);
            } else if (temp_v1 < self->ext.ghost.unk86) {
                self->ext.ghost.unk86 = 0;
                g_api.func_8011A3AC(
                    self, D_us_8017050C[((D_us_80173810.level / 10) * 3)], 1,
                    &D_us_80173810);
                self->hitboxWidth = 8;
                self->hitboxHeight = 8;
            }
        } else {
            self->ext.ghost.unk86 = 0;
            if (self->ext.ghost.unk92->entityId == 0xDA) {
                self->ext.ghost.unk92->params = 1;
                g_ServantDesc.Unk28(self->ext.ghost.unk92);
            }
        }
        self->posX.val += self->velocityX;
        self->posY.val += self->velocityY;
        break;
    case 4:
        if (!(g_Player.unk0C &
              (PLAYER_STATUS_BAT_FORM | PLAYER_STATUS_AXEARMOR))) {
            if (self->ext.ghost.unk96->entityId == 0xDB) {
                self->ext.ghost.unk96->params = 1;
                g_ServantDesc.Unk2C(self->ext.ghost.unk96);
            }
            self->step = 1;
            break;
        }
        UpdateEntityVelocityTowardsTarget(self, D_us_801737C4, D_us_801737C8);
        self->posY.val += self->velocityY;
        switch (self->ext.ghost.unk8C) {
        case 0:
            self->ext.ghost.unk86 = 0;
            self->ext.ghost.unk8C++;
            break;
        case 1:
            if (++self->ext.ghost.unk86 >= 0x3D) {
                self->ext.ghost.unk86 = 0;
                self->ext.ghost.unk8C++;
            }
            break;
        case 2:
        case 3:
        case 4:
        case 5:
            self->ext.ghost.unk86++;
            if (self->ext.ghost.unk86 == 1) {
                self->facingLeft = self->facingLeft == 0;
            } else if (self->ext.ghost.unk86 >= 0x10) {
                self->ext.ghost.unk86 = 0;
                self->ext.ghost.unk8C++;
            }
            break;
        case 6:
            if (++self->ext.ghost.unk86 >= 0x3D) {
                self->ext.ghost.unk86 = 0;
                self->ext.ghost.unk8C++;
            }
            break;
        case 7:
            self->ext.ghost.unk86++;
            if (self->ext.ghost.unk86 == 1) {
                self->ext.ghost.unk96 = func_us_80171568(self, 1);
            } else if (self->ext.ghost.unk86 >= 0x3D) {
                self->ext.ghost.unk86 = 0;
                self->step++;
            }
            break;
        }
        break;
    case 5:
        if (g_Player.unk0C &
            (PLAYER_STATUS_BAT_FORM | PLAYER_STATUS_AXEARMOR)) {
            if (self->velocityY > FIX(-1.5)) {
                self->velocityY -= FIX(0.25);
            }
            self->posY.val += self->velocityY;
            if (self->posY.i.hi < -0x10) {
                self->velocityY = 0;
                self->posX.val = FIX(128.0);
                self->posY.val = FIX(-16.0);
                self->step++;
            }
        } else {
            self->step = 1;
        }
        break;
    case 6:
        if (!(g_Player.unk0C &
              (PLAYER_STATUS_BAT_FORM | PLAYER_STATUS_AXEARMOR))) {
            self->step = 1;
        } else {
            self->posX.val = FIX(128.0);
            self->posY.val = FIX(-16.0);
        }
        break;
    }
    self->ext.ghost.unk88 += self->ext.ghost.unk8A;
    if ((s16)(self->ext.ghost.unk88 - 0x21) >= 0x5Fu) {
        temp_v0 = self->ext.ghost.unk8A;
        self->ext.ghost.unk8A = -temp_v0;
    }
    self->unk6C = (u8)self->ext.ghost.unk88;
    ProcessEvent(self, 0);
    func_us_80171560(self);
    g_api.UpdateAnim(NULL, &D_us_80170500);
}

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

#include "../calculate_angle_to_entity.h"

#include "../get_target_position_with_distance_buffer.h"

#ifndef VERSION_PSP
#include "../calculate_distance.h"
#include "../play_sfx.h"
#endif

#include "../process_event.h"

#include "../create_event_entity.h"

#include "../is_movement_allowed.h"

#ifndef VERSION_PSP
#include "../check_all_entities_valid.h"
#endif

#include "../servant_unk0.h"
