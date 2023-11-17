#include "common.h"
#include "game.h"

typedef struct {
    void (*Init)(s32 arg0);
    void (*Update)(Entity* self);
    void (*Unk08)(Entity* self);
    void (*Unk0C)(/*?*/);
    void (*Unk10)(/*?*/);
    void (*Unk14)(/*?*/);
    void (*Unk18)(/*?*/);
    void (*Unk1C)(/*?*/);
    void (*Unk20)(/*?*/);
    void (*Unk24)(/*?*/);
    void (*Unk28)(Entity* self);
    void (*Unk2C)(/*?*/);
    void (*Unk30)(/*?*/);
    void (*Unk34)(/*?*/);
    void (*Unk38)(/*?*/);
    void (*Unk3C)(Entity* self);
} ServantDesc;

typedef struct {
    u16 start, end;
} EntitySearch;
extern s32 D_8017054C;
extern s32 D_801705EC;
extern s32 D_801705F4;
extern s32 D_80170660;
extern EntitySearch D_80171094[];
extern s32 D_80174B30;
extern s32 D_80174B34;
extern s16 D_80174B38;
extern s16 D_80174B3C;
extern s16 D_80174B40;
extern s16 D_80174B44;

extern ServantDesc g_ServantDesc;
