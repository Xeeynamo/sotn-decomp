// SPDX-License-Identifier: AGPL-3.0-or-later

#include "rbo3.h"

#ifdef VERSION_PSP
extern s32 E_ID(LIFE_UP_SPAWN);
#endif

extern EInit g_EInitInteractable;
s32 D_us_80180728 = 0;
extern s32 D_us_8018072C;

void func_us_80192B38(Entity *self) {
  Entity *entity;
  s32 x;
  s32 y;

  switch (self->step) {
  case 0:
    InitializeEntity(g_EInitInteractable);
    // fallthrough
  case 1:
    entity = &PLAYER;
    x = entity->posX.i.hi + g_Tilemap.scrollX.i.hi;
    if (x > 128 && x < 384) {
      D_us_8018072C = 1;
      D_us_80180728 = 1;
      g_api.TimeAttackController(TIMEATTACK_EVENT_MEDUSA_DEFEAT,
                                 TIMEATTACK_SET_VISITED);
      stopMusicFlag = true;
      currentMusicId = MU_ENCHANTED_BANQUET;
      self->step++;
    }
    break;
  case 2:
    if (g_api.func_80131F68() == false) {
      stopMusicFlag = false;
      g_api.PlaySfx(currentMusicId);
      self->step++;
    }
    break;

  case 3:
    if (D_us_80180728 & 2) {
      g_api.TimeAttackController(TIMEATTACK_EVENT_MEDUSA_DEFEAT,
                                 TIMEATTACK_SET_RECORD);
      g_api.PlaySfx(SET_UNK_90);
      currentMusicId = MU_LOST_PAINTING;
      self->step++;
    }
    break;

  case 4:
    if (D_us_80180728 & 4) {
      self->step++;
    }
    break;

  case 5:
    x = 256 - g_Tilemap.scrollX.i.hi;
    y = 128 - g_Tilemap.scrollY.i.hi;
    entity = AllocEntity(&g_Entities[0xA0], &g_Entities[0xC0]);
    if (entity == NULL) {
      break;
    }
    CreateEntityFromEntity(E_ID(LIFE_UP_SPAWN), self, entity);
    entity->posX.i.hi = x;
    entity->posY.i.hi = y;
    entity->params = 0x11;
    D_us_8018072C = 0;
    stopMusicFlag = true;
    currentMusicId = MU_LOST_PAINTING;
    self->step++;
    break;

  case 6:
    if (g_api.func_80131F68() == false) {
      stopMusicFlag = false;
      g_api.PlaySfx(currentMusicId);
      self->step++;
    }
    break;
  }
}
