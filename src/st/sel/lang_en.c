#include "sel.h"

extern const char D_801A75A0[]; // "…選択決定取消入力未初期化確認"
extern const char D_801A75C0[]; // "はいえ不良"

extern const char D_801A7618[]; // _S("Select")
extern const char D_801A7610[]; // _S("Decide")
extern const char D_801A7608[]; // _S("Cancel")
extern const char D_801A7600[]; // _S("Input")
extern const char D_801A75F4[]; // _S("Not for-")
extern const char D_801A75EC[]; // _S("Yes")
extern const char D_801A75E8[]; // _S("No")
extern const char D_801A75DC[]; // _S("Confirm")
extern const char D_801A75D4[]; // _S("Error")
extern const char D_801A75CC[]; // _S("matted")
const char* D_801803A8[] = {
    D_801A7618, D_801A7610, D_801A7608, D_801A7600, D_801A75F4,
    D_801A75EC, D_801A75E8, D_801A75DC, D_801A75D4, D_801A75CC,
};

extern const char D_801A76A0[]; // "Ａ"
extern const char D_801A769C[]; // "Ｂ"
extern const char D_801A7698[]; // "Ｃ"
extern const char D_801A7694[]; // "Ｄ"
extern const char D_801A7690[]; // "Ｅ"
extern const char D_801A768C[]; // "Ｆ"
extern const char D_801A7688[]; // "Ｇ"
extern const char D_801A7684[]; // "Ｈ"
extern const char D_801A7680[]; // "Ｉ"
extern const char D_801A767C[]; // "Ｊ"
extern const char D_801A7678[]; // "Ｋ"
extern const char D_801A7674[]; // "Ｌ"
extern const char D_801A7670[]; // "Ｍ"
extern const char D_801A766C[]; // "Ｎ"
extern const char D_801A7668[]; // "Ｏ"
extern const char D_801A7664[]; // "Ｐ"
extern const char D_801A7660[]; // "Ｑ"
extern const char D_801A765C[]; // "Ｒ"
extern const char D_801A7658[]; // "Ｓ"
extern const char D_801A7654[]; // "Ｔ"
extern const char D_801A7650[]; // "Ｕ"
extern const char D_801A764C[]; // "Ｖ"
extern const char D_801A7648[]; // "Ｗ"
extern const char D_801A7644[]; // "Ｘ"
extern const char D_801A7640[]; // "Ｙ"
extern const char D_801A763C[]; // "Ｚ"
extern const char D_801A7638[]; // "＆"
extern const char D_801A7634[]; // "！"
extern const char D_801A7630[]; // "－"
extern const char D_801A762C[]; // "．"
extern const char D_801A7628[]; // "’"
extern const char D_801A7624[]; // "？"
extern const char D_801A7620[]; // "　"
const char* D_801803D0[] = {
    D_801A76A0, D_801A769C, D_801A7698, D_801A7694, D_801A7690, D_801A768C,
    D_801A7688, D_801A7684, D_801A7680, D_801A767C, D_801A7678, D_801A7674,
    D_801A7670, D_801A766C, D_801A7668, D_801A7664, D_801A7660, D_801A765C,
    D_801A7658, D_801A7654, D_801A7650, D_801A764C, D_801A7648, D_801A7644,
    D_801A7640, D_801A763C, D_801A7638, D_801A7634, D_801A7630, D_801A762C,
    D_801A7628, D_801A7624, D_801A7620,
};

const char* D_80180454[] = {
    "−＊＊＊＊＊−",  "− New Game −",   "− Change Name −",
    "− Copy File −", "− Erase File −",
};

const char* D_80180468[] = {
    "richter ",
};
