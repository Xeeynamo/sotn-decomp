#include "common.h"
#include "game.h"

typedef struct {
    void (*Init)(s32 arg0);
    void (*Update)(Entity_*self);
    void (*Unk08)(Entity_*self);
    void (*Unk0C)(/*?*/);
    void (*Unk10)(/*?*/);
    void (*Unk14)(/*?*/);
    void (*Unk18)(/*?*/);
    void (*Unk1C)(/*?*/);
    void (*Unk20)(/*?*/);
    void (*Unk24)(/*?*/);
    void (*Unk28)(Entity_*self);
    void (*Unk2C)(/*?*/);
    void (*Unk30)(/*?*/);
    void (*Unk34)(/*?*/);
    void (*Unk38)(/*?*/);
    void (*Unk3C)(Entity_*self);
} ServantDesc;

typedef struct {
    u16 start, end;
} EntitySearch;
EntitySearch D_80171094[];

ServantDesc g_ServantDesc;
