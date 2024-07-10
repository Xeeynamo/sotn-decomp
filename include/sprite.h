#ifndef SPRITE_H
#define SPRITE_H

#include "types.h"

typedef struct {
    /* 0x00 */ s16 x;
    /* 0x02 */ s16 y;
    /* 0x04 */ s16 width;
    /* 0x06 */ s16 height;
    /* 0x08 */ s16 clut;
    /* 0x0A */ s16 tpage;
    /* 0x0C */ s16 texLeft;
    /* 0x0E */ s16 texTop;
    /* 0x10 */ s16 texRight;
    /* 0x12 */ s16 texBottom;
} Sprite; /* size=0x14 */

typedef struct {
    /* 00 */ s16 flags;
    /* 02 */ s16 offsetx;
    /* 04 */ s16 offsety;
    /* 06 */ s16 width;
    /* 08 */ s16 height;
    /* 0A */ s16 clut;
    /* 0C */ s16 tileset;
    /* 0E */ s16 left;
    /* 10 */ s16 top;
    /* 12 */ s16 right;
    /* 14 */ s16 bottom;
} SpritePart; /* size=0x16 */

typedef struct {
    /* 00 */ u16 count;
    /* 02 */ SpritePart parts[0];
} SpriteParts; // size = 4 + count*sizeof(SpritePart)


#endif // SPRITE_H
