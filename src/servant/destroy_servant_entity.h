// SPDX-License-Identifier: AGPL-3.0-or-later
void DestroyServantEntity(Entity* self) {
    switch (self->params) {
    case 15:
        g_IsServantDestroyed = 1;
        break;
    }
    DestroyEntity(self);
}
