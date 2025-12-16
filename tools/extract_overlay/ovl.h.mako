// SPDX-License-Identifier: AGPL-3.0-or-later
#ifndef ${ovl_name.upper()}_H
#define ${ovl_name.upper()}_H

#include <stage.h>

#define OVL_EXPORT(x) ${ovl_name.upper()}_##x
#define STAGE_IS_${ovl_name.upper()}

enum Palettes {
    PAL_NONE,
};
% if entity_updates:
<%
maxlen = max(len(e_id) for function, e_id in entity_updates) + 1
%>
enum Entities {
    E_NONE,
% for function, e_id in entity_updates:
    ${(e_id + ",").ljust(maxlen)} // ${function}
% endfor
    NUM_ENTITIES,
};
% endif

#endif // ${ovl_name.upper()}_H