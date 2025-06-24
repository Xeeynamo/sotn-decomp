// SPDX-License-Identifier: AGPL-3.0-or-later
#include "dai.h"
#include <cutscene.h>

#ifdef VERSION_PSP
u8 OVL_EXPORT(cutscene_script_it)[] = {
#include "gen/cutscene_script_it.h"
    0x08, 0x80, 0x00, 0x00, 0x00, 0x85, 0x47,
    0x11, 0x10, 0x0A, 0xA7, 0xFF, 0xFF};

u8 OVL_EXPORT(cutscene_script_sp)[] = {
#include "gen/cutscene_script_sp.h"
    0x11, 0x10, 0x0A, 0xA7, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

u8 OVL_EXPORT(cutscene_script_fr)[] = {
#include "gen/cutscene_script_fr.h"
    0x0A, 0xA7, 0xFF, 0xFF};

u8 OVL_EXPORT(cutscene_script_ge)[] = {
#include "gen/cutscene_script_ge.h"
    0xA7, 0xFF, 0xFF, 0x00};

u8 OVL_EXPORT(cutscene_script_en)[] = {
#include "gen/cutscene_script_en.h"
    0x0A, 0xA7, 0xFF, 0xFF, 0x00, 0x00, 0x00};
#else
u8 OVL_EXPORT(cutscene_script)[] = {
#include "gen/cutscene_script_psx.h"
};
#endif
