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

extern SpriteParts* D_80170040[];
extern u16 D_80170448[];
extern s32 D_801704A8[];
extern s32 D_8017054C[];
extern s32 D_801705EC[];
extern s32* D_801705F4[];
extern Sprite D_80170608[];
extern s32 D_80170658[][5];
extern u16 D_80170720[];
extern s32 D_80171090;
extern EntitySearch D_80171094[];

extern ServantDesc g_ServantDesc;
