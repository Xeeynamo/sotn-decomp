// SPDX-License-Identifier: AGPL-3.0-or-later
# include "chi.h"

#ifdef VERSION_PSP
#define GOLD_COLLECT_TEXT                                                      \
    _S("$1"), _S("$25"), _S("$50"), _S("$100"), _S("$250"), _S("$400"),        \
        _S("$700"), _S("$1000"), _S("$2000"), _S("$5000"),
#include "../e_collect_psp.h"

#define HEART_DROP_CASTLE_FLAG 0xB0
#include "../entity_heart_drop.h"

#include "../entity_message_box.h"

#else
#include "../e_collect.h"
#endif
