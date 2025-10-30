// SPDX-License-Identifier: AGPL-3.0-or-later
#include "cat.h"

INCLUDE_ASM("st/cat/nonmatchings/unk_3872C", func_us_801B872C);

void func_us_801B87E8(Entity *arg0)
{
  Primitive *prim_1;

  s16 prim_id;
  s16 base_x;
  s32 cntr;

  u16 temp_1;
  u16 temp_2;
  u16 temp_3;
  u16 temp_4;
  u16 temp_5;
  u16 temp_6;

  for (base_x = -g_Tilemap.scrollX.i.hi; base_x < (-0x3E); base_x += 0x3E);

  if (arg0->step == 0)
  {
      arg0->step += 1;
      do
      {
          prim_id = (arg0->primIndex = g_api_AllocPrimitives(PRIM_GT4, 0x10));
      }
      while (0);

      if (prim_id == -1)
      {
          DestroyEntity(arg0);
          return;
      }
      arg0->flags = 0x04800000;
      prim_1 = &g_PrimBuf[arg0->primIndex];
      cntr = 0;
      while (prim_1 != 0)
      {
          temp_5 = base_x + ((cntr & 0x7) * 0x3E);
          prim_1->x2 = temp_5;
          prim_1->x0 = temp_5;
          temp_6 = temp_5 + 0x3E;
          prim_1->x3 = temp_6;
          prim_1->x1 = temp_6;
          temp_4 = ((cntr >> 3) * 0x5F) + 0x1C;
          prim_1->y0 = temp_4;
          prim_1->y1 = temp_4;
          prim_1->tpage = 0xF;
          prim_1->clut = 0x8F;
          prim_1->priority = 0x20;
          prim_1->u0 = 1;
          prim_1->v0 = 0x81;
          prim_1->u1 = 0x3F;
          prim_1->v1 = 0x81;
          prim_1->u2 = 1;
          prim_1->v2 = 0xDE;
          prim_1->u3 = 0x3F;
          prim_1->v3 = 0xDE;
          prim_1->drawMode = 2;
          temp_2 = ((u16) prim_1->y0) - (-0x5F);
          prim_1->y2 = temp_2;
          prim_1->y3 = temp_2;
          if (g_CastleFlags[0x42] == 0)
          {
              prim_1->drawMode = 0xE;
          }
          prim_1 = prim_1->next;
          cntr++;
      }
      do { goto block_end; } while (0);
  }
  cntr = 0;
  if (arg0->ext.ILLEGAL.u8[4] != g_CastleFlags[0x42])
  {
      arg0->ext.ILLEGAL.u8[5] = 01;
  }
  prim_1 = &g_PrimBuf[arg0->primIndex];
  do
  {
      while (prim_1 != 0)
      {
          if (g_CastleFlags[0x42] != 0)
          {
              prim_1->drawMode &= 0xFFF7;
          }
          if (arg0->ext.ILLEGAL.u8[5] != 0)
          {
              if (prim_1->r0 > 0x7f)
              {
                  arg0->ext.ILLEGAL.u8[5] = 0;
              }
              else
              {
                  prim_1->r0 = prim_1->r0 + 2;
                  prim_1->g0 = (prim_1->b0 = prim_1->r0);
                  *((u32 *) (((char *) prim_1) + 0x10)) = *((u32 *) (((char *) prim_1) + 4));
                  *((u32 *) (((char *) prim_1) + 0x1c)) = *((u32 *) (((char *) prim_1) + 4));
                  *((u32 *) (((char *) prim_1) + 0x28)) = *((u32 *) (((char *) prim_1) + 4));
              }
          }
          temp_1 = base_x + (2 * ((cntr & 7) * 31));
          prim_1->x2 = temp_1;
          prim_1->x0 = temp_1;
          temp_3 = temp_1 + 0x3E;
          prim_1->x3 = temp_3;
          prim_1->x1 = temp_3;
          prim_1 = prim_1->next;
          cntr++;
      }

      block_end:
      arg0->ext.ILLEGAL.u8[4] = g_CastleFlags[0x42];

  }
  while (0);
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
