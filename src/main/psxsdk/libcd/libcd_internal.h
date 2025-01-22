#include <common.h>

typedef int (*CDCallback)(char, char*);

extern CDCallback CD_cbready;
extern CDCallback CD_cbsync;

void CD_initintr(void);
int CD_init(void);
int CD_initvol(void);
