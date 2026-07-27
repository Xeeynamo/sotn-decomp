// SPDX-License-Identifier: AGPL-3.0-or-later

void StainedGlassBlendPalette(
    RECT* arg0, u16 srcPalIdx, u16 destPalIdx, s32 steps, CVECTOR* color) {
    u16 buffer[COLORS_PER_PAL];
    RECT rect;
    s32 factor;
    s32 step, index;
    u16* palette;
    u32 r, g, b, mask;

    rect.x = arg0->x;
    rect.w = COLORS_PER_PAL;
    rect.h = 1;

    color->r /= 8;
    color->g /= 8;
    color->b /= 8;
    palette = &g_Clut[0][srcPalIdx * COLORS_PER_PAL];

    for (step = 0; step < steps; destPalIdx++, step++) {
        factor = (step * FLT(1)) / steps;
        for (index = 0; index < COLORS_PER_PAL; index++) {
            if (!(palette[index] & 0x7FFF)) {
                buffer[index] = palette[index];
            } else {
                r = GET_RED(palette[index]);
                g = GET_GREEN(palette[index]);
                b = GET_BLUE(palette[index]);
                mask = palette[index] & ALPHA_MASK;
                r = ((r * (FLT(1) - factor)) + (color->r * factor)) >> 12;
                g = ((g * (FLT(1) - factor)) + (color->g * factor)) >> 12;
                b = ((b * (FLT(1) - factor)) + (color->b * factor)) >> 12;
                buffer[index] = ((mask | r) | (g << 5)) | (b << 10);
                (&g_Clut[0][destPalIdx * COLORS_PER_PAL])[index] =
                    buffer[index];
            }
        }
        rect.y = ((destPalIdx - 512) / COLORS_PER_PAL) + 240;
        rect.x = (((destPalIdx - 512) % COLORS_PER_PAL) * COLORS_PER_PAL) + 256;
        LoadImage(&rect, (u_long*)buffer);
    }
}
