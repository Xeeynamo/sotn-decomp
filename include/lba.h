// SPDX-License-Identifier: AGPL-3.0-or-later

#define OFF_WARNING_TIM 24545
#define LEN_WARNING_TIM 327700

#if defined(VERSION_US)
#define OFF_BIN_FGAME2 25170
#define OFF_BIN_FGAME 25038
#elif defined(VERSION_HD)
#define OFF_BIN_FGAME2 25248
#define OFF_BIN_FGAME 25116
#endif

#define vab0Len 269488
#define SD_ALK_VH_LEN 4128
#define SD_RIH_VH_LEN 4128
#define SD_TUKA2_VH_LEN 4128
#define SD_TUKA2_VB_LEN 63904
#define SD_TUKA1_VH_LEN 4128
#define SD_MAR_VH_LEN 3616
#define SD_MAK_VH_LEN 3104
#define SD_KOA1_VH_LEN 3616
#define SD_KOA2_VH_LEN 3616
#define SD_KOA2_VB_LEN 60992

#if defined(VERSION_US)
#define SD_ALK_VB_LEN 57696
#define SD_RIH_VB_LEN 57744
#define SD_MAR_VB_LEN 52896
#define SD_TUKA1_VB_LEN 63552
#define SD_KOA1_VB_LEN 59392
#define SD_MAK_VB_LEN 64496
#define vab1Len SD_RIH_VB_LEN
#define vab2Len SD_MAK_VB_LEN
#define vab3Len 108048

#elif defined(VERSION_HD)
#define SD_ALK_VB_LEN 57808
#define SD_RIH_VB_LEN 52256
#define SD_MAR_VB_LEN 58000
#define SD_TUKA1_VB_LEN 65200
#define SD_KOA1_VB_LEN 59488
#define SD_MAK_VB_LEN 51024
#define vab1Len SD_ALK_VB_LEN
#define vab2Len SD_TUKA1_VB_LEN
#define vab3Len 107792

#endif
