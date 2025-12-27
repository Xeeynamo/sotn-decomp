// SPDX-License-Identifier: AGPL-3.0-or-later
#include "${ovl_include_path}"
% if header_syms[7] != "NULL":
% if ovl_type == "stage":
#include "../pfn_entity_update.h"
% elif ovl_type == "boss":
#include "../../st/pfn_entity_update.h"
% endif
% endif
<%
if len(header_syms) <= 12:
    header_type = "AbbreviatedOverlay"
elif len(header_syms) == 13 or len(header_syms) == 14:
    header_type = "AbbreviatedOverlay2"
else:
    header_type = "Overlay"
%>
% if ovl_type == "stage" or ovl_type == "boss":
// common
extern RoomHeader OVL_EXPORT(rooms)[];
extern SpriteParts* OVL_EXPORT(spriteBanks)[];
extern u_long* OVL_EXPORT(cluts)[];
extern RoomDef OVL_EXPORT(rooms_layers)[];
extern GfxBank* OVL_EXPORT(gfxBanks)[];
void UpdateStageEntities(void);
% for header_sym in set(header_syms):
% if header_sym not in common_syms:
// overlay
u8* ${header_sym}[];
%endif
%endfor

${header_type} OVL_EXPORT(Overlay) = {
    .Update = ${header_syms[0]},
    .HitDetection = ${header_syms[1]},
    .UpdateRoomPosition = ${header_syms[2]},
    .InitRoomEntities = ${header_syms[3]},
    .rooms = ${header_syms[4]},
    .spriteBanks = ${header_syms[5]},
    .cluts = ${header_syms[6]},
% if header_syms[7] == "NULL":
    .objLayoutHorizontal = NULL,
% else:
    .objLayoutHorizontal = &OBJ_LAYOUT_HORIZONTAL,
% endif
    .tileLayers = ${header_syms[8]},
    .gfxBanks = ${header_syms[9]},
    .UpdateStageEntities = ${header_syms[10]},
% if len(header_syms) > 12:
    .unk2C = ${header_syms[11]},
    .unk30 = ${header_syms[12]},
% endif
% if len(header_syms) > 15:
    .unk34 = ${header_syms[13]},
    .unk38 = ${header_syms[14]},
    .StageEndCutScene = ${header_syms[15]},
% endif
};
% endif
