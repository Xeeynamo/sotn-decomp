// SPDX-License-Identifier: AGPL-3.0-or-later

// This seems like a totally unused entity. Not created in any way, not in
// e_layout.c.
void EntityUnkId16(Entity* self) {
    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitSpawner);
        self->ext.entrance16.r = 16;
        self->ext.entrance16.g = 8;
        self->ext.entrance16.b = 56;

    case 1:
        g_GpuBuffers[0].draw.r0 = self->ext.entrance16.r;
        g_GpuBuffers[0].draw.g0 = self->ext.entrance16.g;
        g_GpuBuffers[0].draw.b0 = self->ext.entrance16.b;
        g_GpuBuffers[1].draw.r0 = self->ext.entrance16.r;
        g_GpuBuffers[1].draw.g0 = self->ext.entrance16.g;
        g_GpuBuffers[1].draw.b0 = self->ext.entrance16.b;
        break;
    }
}
