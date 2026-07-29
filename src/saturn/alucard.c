// SPDX-License-Identifier: AGPL-3.0-or-later
#include "inc_asm.h"
#include "sattypes.h"

// CheckMoveDirection
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60A5060, func_060A5060);
// func_8010FDF8 on PSX
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60A50E0, func_060A50E0);

// SAT: func_060A5558
void SetPlayerStep(PlayerSteps step) {
    PLAYER.step = step;
    PLAYER.step_s = 0;
}

// SetSpeedX
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60A5574, func_060A5574);
// func_8010E3B8 on PSX
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60A5594, func_060A5594);
// DecelerateX (PLAYER-specialized Saturn version)
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60A55B4, func_060A55B4);
// DecelerateY (PLAYER-specialized Saturn version)
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60A55E4, func_060A55E4);
// DecelerateX (g_CurrentEntity version)
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60A5614, func_060A5614);
// DecelerateY (g_CurrentEntity version)
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60A5644, func_060A5644);
// SetPlayerAnim
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60A5674, func_060A5674);
// func_8010DA2C on PSX
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60A56AC, func_060A56AC);

void func_060A56D8() {}

// func_8010E470 on PSX
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60A56E4, func_060A56E4);
// CheckPlayerStuck
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60A5738, func_060A5738);
// func_8010E570 on PSX
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60A580C, func_060A580C);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60A5938, func_060A5938);
// func_8010E6AC on PSX
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60A59E0, func_060A59E0);
// func_8010E7AC on PSX
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60A5AF0, func_060A5AF0);
// func_8010E83C on PSX
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60A5B94, func_060A5B94);
// func_8010E940 on PSX
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60A5CD8, func_060A5CD8);
// DoGravityJump
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60A5D50, func_060A5D50);
// func_8010FD88 on PSX
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60A5E14, func_060A5E14);
// PerformDarkMetamorphosis
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60A5EA8, func_060A5EA8);
// PerformSummonSpirit
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60A5F9C, func_060A5F9C);
// PerformHellfire
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60A605C, func_060A605C);
// PerformTetraSpirit
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60A60EC, func_060A60EC);
// PerformSoulSteal
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60A61B0, func_060A61B0);
// PerformSwordBrothers
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60A6248, func_060A6248);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60A62E4, func_060A62E4);
// CheckSubwpnChainLimit
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60A6314, func_060A6314);
// CheckChainLimit
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60A6384, func_060A6384);
// func_8010EB5C on PSX
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60A6420, func_060A6420);
// func_8010ED54 on PSX
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60A6618, func_060A6618);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60A6688, func_060A6688);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60A66FC, func_060A66FC);
// func_8010EDB8 on PSX
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60A67B8, func_060A67B8);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60A6A94, func_060A6A94);
// func_8010FAF4 on PSX
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60A7D3C, func_060A7D3C);
// func_8010DFF0 on PSX
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60A7D68, func_060A7D68);
// EnableAfterImage
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60A7DD0, func_060A7DD0);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60A7DE8, func_060A7DE8);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60A7E90, func_060A7E90);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60A7F28, func_060A7F28);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60A80E0, func_060A80E0);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60A81DC, func_060A81DC);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60A8D78, func_060A8D78);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60A8DF4, func_060A8DF4);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60A9658, func_060A9658);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60A96A0, func_060A96A0);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60A972C, func_060A972C);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60A9D90, func_060A9D90);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60A9E3C, func_060A9E3C);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60AA0FC, func_060AA0FC);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60AA150, func_060AA150);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60AA23C, func_060AA23C);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60AADE4, func_060AADE4);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60AB090, func_060AB090);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60AB0BC, func_060AB0BC);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60AB0E8, func_060AB0E8);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60AB308, func_060AB308);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60AB37C, func_060AB37C);
// func_8010E0D0 on PSX
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60AB3A8, func_060AB3A8);
// func_8010E168 on PSX
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60AB44C, func_060AB44C);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60AB4A4, func_060AB4A4);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60AB558, func_060AB558);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60AB590, func_060AB590);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60AB5E0, func_060AB5E0);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60AB78C, func_060AB78C);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60AB814, func_060AB814);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60ABCF0, func_060ABCF0);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60ABFA4, func_060ABFA4);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60AC018, func_060AC018);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60AC0C8, func_060AC0C8);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60AC20C, func_060AC20C);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60AC2F0, func_060AC2F0);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60AC574, func_060AC574);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60AC8F4, func_060AC8F4);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60ACACC, func_060ACACC);
// PlayAnimation (Saturn player-specialized version)
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60ACB6C, func_060ACB6C);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60ACF00, func_060ACF00);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60AD44C, func_060AD44C);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60AD524, func_060AD524);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60AD714, func_060AD714);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60ADACC, func_060ADACC);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60ADB80, func_060ADB80);

void func_060ADD50() {}

void func_060ADD5C() {}

void func_060ADD68() {}

// func_8010DF70 on PSX
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60ADD74, func_060ADD74);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60ADDDC, func_060ADDDC);
// AluInit
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60ADF3C, func_060ADF3C);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60AE048, func_060AE048);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60AE184, func_060AE184);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60AE284, func_060AE284);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60AE36C, func_060AE36C);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60AE544, func_060AE544);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60AE6F4, func_060AE6F4);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60AE8E4, func_060AE8E4);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60AEAE8, func_060AEAE8);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60AECC4, func_060AECC4);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60AEEE4, func_060AEEE4);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60AEFBC, func_060AEFBC);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60AF050, func_060AF050);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60AF124, func_060AF124);

void func_060AF1BC(int);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60AF1BC, func_060AF1BC);

void func_060AF4A0(void) { func_060AF1BC(1); }

INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60AF4B8, func_060AF4B8);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60AF550, func_060AF550);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60AF654, func_060AF654);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60AF7F0, func_060AF7F0);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60AF8E0, func_060AF8E0);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60AF9D4, func_060AF9D4);
// EntityAlucard
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60AFA20, func_060AFA20);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60B0310, func_060B0310);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60B0584, func_060B0584);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60B0638, func_060B0638);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60B071C, func_060B071C);
