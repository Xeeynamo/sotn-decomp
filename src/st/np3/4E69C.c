#include "np3.h"
#include "sfx.h"

void EntityHammer(Entity* self) {
    Collider collider;
    Entity* otherEnt;
    // These are two different ents using var_s3. I dunno.
    Entity* var_s3_1;
    Entity* var_s3_2;
    s16* var_s2;
    s16* var_s4;
    u16 zPriority;

    if ((self->step & 1) && (self->hitFlags & 3)) {
        func_801CE1E8(0xC);
    }
    if ((self->flags & FLAG_DEAD) && (self->step < 24)) {
        func_801916C4(0x745);
        func_801CE1E8(0x18);
    }
    switch (self->step) {
    case 0:
        InitializeEntity(D_80180B8C);
        self->animCurFrame = 3;
        self->hitboxWidth = 6;
        self->hitboxHeight = 6;
        /* fallthrough */
    case 1:
        if (func_801BC8E4(D_80182978) & 1) {
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
            self->step++;
        }
        break;
    case 2:
        var_s3_1 = self;
        for (var_s4 = &D_80182988; *var_s4 != 0; var_s4 += 5) {
            otherEnt = self + var_s4[0];
            CreateEntityFromCurrentEntity(E_GURKHA_BODY_PARTS, otherEnt);
            otherEnt->ext.GH_Props.unk9E = var_s4[2];
            otherEnt->ext.GH_Props.parent = self + var_s4[1];
            otherEnt->params = var_s4[3];
            zPriority = self->zPriority + var_s4[4];
            otherEnt->unk60 = var_s3_1;
            var_s3_1 = otherEnt;
            var_s3_1->unk5C = self;
            var_s3_1->zPriority = zPriority;
        }
        self->unk60 = var_s3_1;
        self->unk5C = NULL;
        CreateEntityFromCurrentEntity(E_HAMMER_WEAPON, self + 15);
        (self + 15)->ext.GH_Props.unk9E = 12;
        (self + 15)->ext.GH_Props.parent = self + 5;
        (self + 15)->params = 0x12;
        (self + 15)->zPriority = self->zPriority + 3;
        self->step++;
        /* fallthrough */
    case 3:
        func_801CE228();
        (self + 4)->ext.GH_Props.rotZ = 0x100;
        (self + 5)->ext.GH_Props.rotZ = 0x680;
        (self + 15)->ext.GH_Props.rotZ = 0x2C0;
        func_801CE1E8(5);
    case 5:
        if (self->ext.GH_Props.unk84 == 1) {
            var_s2 = D_80182AB8;
        } else {
            var_s2 = D_80182AD0;
        }
        func_801CDF1C(var_s2, &D_80182BB4, 0);
        func_801CDE10(var_s2);
        func_801CE2CC(var_s2);
        func_801CE258(&D_80182A20);
        if (self->ext.GH_Props.unkB0[0] > 1) {
            collider.unk18 = 9;
            otherEnt = &self[var_s2[3]];
            func_801CE04C(otherEnt, &collider);
            if (otherEnt->ext.GH_Props.unk88 != 0) {
                otherEnt->posY.i.hi += collider.unk18;
                self->ext.GH_Props.unk84 ^= 1;
                func_801CE228();
                func_801CE4CC(otherEnt);
            } else if (self->ext.GH_Props.unkB0[0] == 2 &&
                       self->ext.GH_Props.unkB0[2] == 1) {
                func_801CE1E8(8);
            }
        }
        break;
    case 7:
        if (self->ext.GH_Props.unk84 == 1) {
            var_s2 = D_80182AB8;
        } else {
            var_s2 = D_80182AD0;
        }
        func_801CDF1C(var_s2, &D_80182BEC, 0);
        func_801CDE10(var_s2);
        func_801CE2CC(var_s2);
        func_801CE258(&D_80182A20);
        if (self->ext.GH_Props.unkB0[0] > 1) {
            collider.unk18 = 9;
            otherEnt = &self[var_s2[3]];
            func_801CE04C(otherEnt, &collider);
            if (otherEnt->ext.GH_Props.unk88 != 0) {
                otherEnt->posY.i.hi += collider.unk18;
                self->ext.GH_Props.unk84 ^= 1;
                func_801CE228();
                if (func_801CE120(otherEnt, self->facingLeft ^ 1) != 0) {
                    func_801CE1E8(5);
                } else {
                    func_801CE4CC(self);
                }
            }
        }
        break;
    case 8:
        if (self->ext.GH_Props.unk84 == 1) {
            var_s2 = D_80182AB8;
        } else {
            var_s2 = D_80182AD0;
        }
        switch (self->step_s) {
        case 0:
            if (self->ext.GH_Props.unk84 == 1) {
                var_s2 = D_80182A40;
            } else {
                var_s2 = D_80182A5C;
            }
            func_801CDF1C(var_s2, &D_80182B54, 0);
            func_801CDE10(var_s2);
            func_801CE2CC(var_s2);
            if (self->ext.GH_Props.unkB0[0] == 0 &&
                self->ext.GH_Props.unkB0[2] == 0) {
                self->step_s++;
            }
            break;
        case 1:
            func_801CDF1C(var_s2, &D_80182C9C, 0);
            func_801CDE10(var_s2);
            func_801CE2CC(var_s2);
            if (self->ext.GH_Props.unkB0[2] == 0 &&
                self->ext.GH_Props.unkB0[0] == 0) {
                self->step_s++;
            }
            break;
        case 2:
            if (self->facingLeft) {
                self->velocityX = FIX(2);
            } else {
                self->velocityX = FIX(-2);
            }
            self->velocityY = FIX(-0.75);
            func_801CE228();
            self->step_s++;
            /* fallthrough */
        case 3:
            MoveEntity();
            self->velocityY += FIX(48.0 / 128);
            func_801CDF1C(var_s2, &D_80182CC4, 0);
            func_801CDE10(var_s2);
            func_801CE3FC(var_s2);
            otherEnt = &self[var_s2[3]];
            collider.unk18 = 10;
            func_801CE04C(otherEnt, &collider);
            if (otherEnt->ext.GH_Props.unk88 != 0) {
                func_801916C4(SFX_STOMP_HARD_C);
                otherEnt->posY.i.hi += collider.unk18 + 1;
                self->ext.GH_Props.unk84 ^= 1;
                func_801CE228();
                self->step_s = 1;
                func_801CE4CC(otherEnt);
            }
            break;
        }
        func_801CE258(&D_80182A20);
        break;
    case 6:
        switch (self->step_s) {
        case 0:
            self->step_s++;
        case 1:
            var_s3_2 = self + 8;
            if (self->ext.GH_Props.unk84 == 1) {
                var_s2 = D_80182AE8;
            } else {
                var_s2 = D_80182B00;
            }
            func_801CDF1C(var_s2, &D_80182E38, 0);
            func_801CDE10(var_s2);
            func_801CE2CC(var_s2);
            otherEnt = self + 7;
            (self + 8)->posX.val = (self + 15)->posX.val;
            (self + 8)->posY.val = (self + 15)->posY.val;
            func_801CDAC8(otherEnt, var_s3_2);
            func_801CDFD8(otherEnt, 0x10);
            func_801CDFD8(var_s3_2, 0x10);
            func_801CE258(&D_80182A20);
            if ((self->ext.GH_Props.unkB0[0] == 0) &&
                (self->ext.GH_Props.unkB0[2] == 0)) {
                func_801916C4(0x743);
                self->step_s++;
            }
            break;
        case 2:
            var_s3_2 = self + 8;
            if (self->ext.GH_Props.unk84 == 1) {
                var_s2 = D_80182AE8;
            } else {
                var_s2 = D_80182B00;
            }
            func_801CDF1C(var_s2, &D_80182E48, 0);
            func_801CDE10(var_s2);
            func_801CE2CC(var_s2);
            otherEnt = self + 7;
            (self + 8)->posX.val = (self + 15)->posX.val;
            (self + 8)->posY.val = (self + 15)->posY.val;
            func_801CDAC8(otherEnt, var_s3_2);
            func_801CDFD8(otherEnt, 2);
            func_801CDFD8(var_s3_2, 2);
            func_801CE258(&D_80182A20);
            if ((self->ext.GH_Props.unkB0[0] == 4) &&
                (self->ext.GH_Props.unkB0[2] == 0)) {
                self->ext.GH_Props.unk84 ^= 1;
            }
            if ((self->ext.GH_Props.unkB0[0] == 6) &&
                (self->ext.GH_Props.unkB0[2] == 0)) {
                func_801916C4(SFX_FM_EXPLODE_D);
                g_api_func_80102CD8(1);
            }
            if ((self->ext.GH_Props.unkB0[0] == 0) &&
                (self->ext.GH_Props.unkB0[2] == 0)) {
                self->ext.GH_Props.unk84 ^= 1;
                self->step_s++;
            }
            break;
        case 3:
            if (self->ext.GH_Props.unk84 == 1) {
                var_s2 = D_80182AE8;
            } else {
                var_s2 = D_80182B00;
            }
            func_801CDF1C(var_s2, &D_80182E38, 0);
            func_801CDE10(var_s2);
            func_801CE2CC(var_s2);
            func_801CE258(&D_80182A20);
            if ((self->ext.GH_Props.unkB0[0] == 0) &&
                (self->ext.GH_Props.unkB0[2] == 0)) {
                self->step_s++;
            }
            break;
        case 4:
            func_801CE4CC(self);
            break;
        }
        break;
    case 10:
        if (self->ext.GH_Props.unk84 == 1) {
            var_s2 = D_80182AB8;
        } else {
            var_s2 = D_80182AD0;
        }
        func_801CDF1C(var_s2, &D_80182CFC, 0);
        func_801CDE10(var_s2);
        func_801CE2CC(var_s2);
        func_801CE258(&D_80182A20);
        if (self->ext.GH_Props.unkB0[2] == 0) {
            self->facingLeft ^= 1;
            func_801CE4CC(self);
        }
        break;
    case 12:
        if (self->step_s == 0) {
            func_801916C4(0x744);
            self->step_s++;
        }
        if (self->ext.GH_Props.unk84 == 1) {
            var_s2 = D_80182A40;
        } else {
            var_s2 = D_80182A5C;
        }
        func_801CDF1C(var_s2, &D_80182EDC, 0);
        func_801CDE10(var_s2);
        func_801CE2CC(var_s2);
        func_801CE258(&D_80182A20);
        if (self->ext.GH_Props.unkB0[0] == 0 &&
            self->ext.GH_Props.unkB0[2] == 0) {
            func_801CE4CC(self);
        }
        break;
    case 24:
        switch (self->step_s) {
        case 0:
            for (var_s2 = &D_80182A20; *var_s2 != 0; var_s2++) {
                otherEnt = self + *var_s2;
                otherEnt->hitboxState = 0;
                otherEnt->step = 0x18;
                otherEnt->step_s = 0;
            }
            self->velocityY = FIX(-2);
            self->hitboxState = 0;
            self->flags |= FLAG_DESTROY_IF_OUT_OF_CAMERA;
            self->step_s++;
            /* fallthrough */
        case 1:
            MoveEntity();
            self->velocityY += FIX(0.1875);
            if (!(g_Timer & 7)) {
                if (Random() & 1) {
                    func_801916C4(SFX_FM_EXPLODE_B);
                } else {
                    func_801916C4(SFX_EXPLODE_D);
                }
            }
            return;
        }
        break;
    }
    for (var_s2 = &D_80182A20; *var_s2 != 0; var_s2++) {
        otherEnt = self + *var_s2;
        otherEnt->facingLeft = self->facingLeft;
        otherEnt->ext.GH_Props.unkA8 = 0;
    }
    D_8006C384.y = self->ext.GH_Props.unkB0[0];
    D_8006C38C.y = self->ext.GH_Props.unkB0[2];
    return;
}

void EntityGurkhaBodyParts(Entity* self) {
    Entity* parent;
    Collider collider;
    s16 angle;
    s32 speed;
    u16 unk88;

    switch (self->step) {
    case 0:
        switch (self->params >> 8) {
        case 0:
            InitializeEntity(D_80180B8C);
            break;
        case 1:
            InitializeEntity(D_80180BA4);
            break;
        case 2:
            InitializeEntity(D_80180BBC);
            break;
        }
        self->hitboxWidth = 6;
        self->hitboxHeight = 6;
        self->params = (u8)self->params;
        self->animCurFrame = self->params;
        self->drawFlags |= DRAW_COLORS;
        break;
    case 1:
        self->rotZ = self->ext.GH_Props.rotZ;
        break;
    case 24:
        switch (self->step_s) {
        case 0:
            speed = (Random() & 0x1F) + 0x10;
            angle = (Random() * 6) + 0x900;
            self->velocityX = (speed * rcos(angle)) / 2;
            self->velocityY = speed * rsin(angle);
            self->ext.GH_Props.unk80 = (Random() & 0x1F) + 0x20;
            self->flags |= FLAG_DESTROY_IF_OUT_OF_CAMERA;
            self->hitboxState = 0;
            self->step_s++;
            break;
        case 1:
            MoveEntity();
            self->velocityY += FIX(0.125);
            self->rotZ += self->ext.GH_Props.unkA6;
            if (--self->ext.GH_Props.unk80 == 0) {
                self->step = 0;
                self->pfnUpdate = EntityExplosion;
                self->params = 0;
                self->drawFlags = 0;
            }
            return;
        }
        break;
    }
    // Careful following control flow here, this is completely after
    // the previous switch.
    switch (self->params) {
    case 8:
    case 14:
        collider.unk18 = 9;
        func_801CE04C(self, &collider);
        break;
    case 9:
    case 15:
        parent = self->ext.GH_Props.parent;
        unk88 = parent->ext.GH_Props.unk88;
        if (unk88 == 2) {
            self->ext.GH_Props.rotZ = 0x200;
        } else if (unk88 == 4) {
            self->ext.GH_Props.rotZ = -0x200;
        } else if (unk88 == 1) {
            self->ext.GH_Props.rotZ = 0;
        }
        if (self->ext.GH_Props.unk8D != 0) {
            angle = self->rotZ;
            self->hitboxOffX = (-(rsin(angle) * 8) >> 0xC);
            self->hitboxOffY = (u32)rcos(angle) / 512;
            self->attack = g_api.enemyDefs[192].attack;
            self->attackElement = g_api.enemyDefs[192].attackElement;
        } else {
            self->hitboxOffX = 0;
            self->hitboxOffY = 0;
            self->attack = g_api.enemyDefs[190].attack;
            self->attackElement = g_api.enemyDefs[190].attackElement;
        }
        break;
    case 5:
    case 11:
        parent = self->ext.GH_Props.parent;
        parent->ext.GH_Props.rotZ = self->ext.GH_Props.rotZ;
        break;
    }
}
