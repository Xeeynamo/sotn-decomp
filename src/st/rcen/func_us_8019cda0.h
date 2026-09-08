// SPDX-License-Identifier: AGPL-3.0-or-later
void func_us_8019CDA0(Entity* self) {
    if (g_RcenShaftFlags & 4) {
        DestroyEntity(self);
    } else if (!self->step) {
        InitializeEntity(D_us_80180594);
    } else {
        DestroyEntity(self);
    }
}
