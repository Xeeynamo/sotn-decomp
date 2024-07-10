#ifndef DRAWMODE_H
#define DRAWMODE_H

#define DRAW_DEFAULT 0x00
#define DRAW_TRANSP 0x01 // make it semi transparent
#define DRAW_UNK02 0x02  // unknown
#define DRAW_COLORS 0x04 // use color blending
#define DRAW_HIDE 0x08   // do not render the primitive
#define DRAW_TPAGE 0x10  // use custom tpage
#define DRAW_TPAGE2 0x20 // use custom tpage
#define DRAW_UNK_40 0x40
#define DRAW_MENU 0x80       // render only if D_800973EC is set
#define DRAW_UNK_100 0x100   // unknown
#define DRAW_UNK_200 0x200   // unknown
#define DRAW_UNK_400 0x400   // unknown
#define DRAW_UNK_800 0x800   // unknown
#define DRAW_UNK_1000 0x1000 // unknown
#define DRAW_ABSPOS 0x2000   // use absolute coordinates with DRAW_MENU

#endif // DRAWMODE_H
