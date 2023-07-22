#ifndef SCL_H
#define SCL_H

#define SCL_CRM15_1024 0
#define SCL_CRM15_2048 1
#define SCL_CRM24_1024 2
#define SCL_COLRAM_ADDR 0x25F00000 /* Color RAM */

extern void SCL_SetColRamOffset(
    Uint32 Object, Uint32 Offset, Uint8 transparent);
extern Uint32 SCL_GetColRamMode(void);

extern Uint32 SclColRamAlloc256[8];
extern Uint32 SclColRamAlloc2048[1];

#endif