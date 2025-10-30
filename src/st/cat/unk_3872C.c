// SPDX-License-Identifier: AGPL-3.0-or-later
#include "cat.h"

INCLUDE_ASM("st/cat/nonmatchings/unk_3872C", func_us_801B872C);

void func_us_801B87E8(Entity *self)
{
  Primitive *prim;
  s32 primIndex;
  s16 base_x;
  s32 cntr;

  for (base_x = -g_Tilemap.scrollX.i.hi; base_x < (-0x3E); base_x += 0x3E);

  if (self->step == 0)
  {
    self->step += 1;
    do
    {
      primIndex = (self->primIndex = g_api_AllocPrimitives(PRIM_GT4, 0x10));
    }
    while (0);
    if (primIndex == (-1))
    {
      DestroyEntity(self);
      return;
    }
    self->flags = 0x04800000;
    prim = &g_PrimBuf[self->primIndex];
    cntr = 0;
    while (prim != 0)
    {
      prim->x0 = prim->x2 = base_x + ((cntr & 0x7) * 0x3E);
      prim->x1 = prim->x3 = prim->x0 + 0x3E;
      prim->y1 = prim->y0 = ((cntr >> 3) * 0x5F) + 0x1C;
      prim->tpage = 0xF;
      prim->clut = 0x8F;
      prim->priority = 0x20;
      prim->u0 = 1;
      prim->v0 = 0x81;
      prim->u1 = 0x3F;
      prim->v1 = 0x81;
      prim->u2 = 1;
      prim->v2 = 0xDE;
      prim->u3 = 0x3F;
      prim->v3 = 0xDE;
      prim->drawMode = 2;
      prim->y3 = prim->y2 = ((u16) prim->y0) - (-0x5F);
      if (g_CastleFlags[0x42] == 0)
      {
        prim->drawMode = 0xE;
      }
      prim = prim->next;
      cntr++;
    }

  }
  else
  {
    cntr = 0;
    if (self->ext.ILLEGAL.u8[4] != g_CastleFlags[0x42])
    {
      self->ext.ILLEGAL.u8[5] = 01;
    }
    prim = &g_PrimBuf[self->primIndex];
    while (prim != 0)
    {
      if (g_CastleFlags[0x42] != 0)
      {
        prim->drawMode &= 0xFFF7;
      }
      if (self->ext.ILLEGAL.u8[5] != 0)
      {
        if (prim->r0 > 0x7f)
        {
          self->ext.ILLEGAL.u8[5] = 0;
        }
        else
        {
          prim->r0 = prim->r0 + 2;
          prim->g0 = (prim->b0 = prim->r0);
          *(u32 *)&prim->r1 = *(u32 *)&prim->r0;
          *(u32 *)&prim->r2 = *(u32 *)&prim->r0;
          *(u32 *)&prim->r3 = *(u32 *)&prim->r0;
        }
      }
      prim->x0 = prim->x2 = base_x + (2 * ((cntr & 7) * 31));
      prim->x1 = prim->x3 = prim->x0 + 0x3E;
      prim = prim->next;
      cntr++;
    }

    self->ext.ILLEGAL.u8[4] = g_CastleFlags[0x42];
  }
  FntPrint("base_x:%04x\n", base_x);
}

INCLUDE_ASM("st/cat/nonmatchings/unk_3872C", func_us_801B8AD0);

INCLUDE_ASM("st/cat/nonmatchings/unk_3872C", func_us_801B8D2C);

INCLUDE_ASM("st/cat/nonmatchings/unk_3872C", func_us_801B907C);

INCLUDE_ASM("st/cat/nonmatchings/unk_3872C", func_us_801B951C);

INCLUDE_RODATA("st/cat/nonmatchings/unk_3872C", D_us_801B673C);

INCLUDE_RODATA("st/cat/nonmatchings/unk_3872C", D_us_801B674C);

INCLUDE_ASM("st/cat/nonmatchings/unk_3872C", func_us_801B972C);

INCLUDE_ASM("st/cat/nonmatchings/unk_3872C", func_us_801B9A74);

INCLUDE_ASM("st/cat/nonmatchings/unk_3872C", func_us_801B9D1C);

INCLUDE_ASM("st/cat/nonmatchings/unk_3872C", func_us_801BA164);

INCLUDE_ASM("st/cat/nonmatchings/unk_3872C", func_us_801BA388);

INCLUDE_ASM("st/cat/nonmatchings/unk_3872C", func_us_801BA7FC);

INCLUDE_ASM("st/cat/nonmatchings/unk_3872C", func_us_801BACF4);

INCLUDE_ASM("st/cat/nonmatchings/unk_3872C", func_us_801BB4CC);
