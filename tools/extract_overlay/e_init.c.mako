// SPDX-License-Identifier: AGPL-3.0-or-later
#include "${ovl_name}.h"

% for function in entity_funcs:
void ${function}(Entity* self);
% endfor

PfnEntityUpdate OVL_EXPORT(EntityUpdates)[] = {
% for function in entity_funcs:
    ${function},
% endfor
};

// clang-format off
// animSet, animCurFrame, unk5A, palette, enemyID
% for name, animSet, animCurFrame, unk5A, palette, enemyID in e_inits:
EInit ${name} = {${animSet}, ${animCurFrame}, ${unk5A}, ${palette}, ${enemyID}};
% endfor
// clang-format on
