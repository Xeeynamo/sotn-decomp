#include <game.h>

void Init();
void Update();
void Dummy();

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

ServantDesc g_ServantDesc = {
    Init,  Update, Dummy, Dummy, Dummy, Dummy, Dummy, Dummy,
    Dummy, Dummy,  Dummy, Dummy, Dummy, Dummy, Dummy, Dummy,

};
