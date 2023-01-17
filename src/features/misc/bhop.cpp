#include "../../sdk/globals.h"
#include "../toggles.h"
#include "../../sdk/const.h"
#include "../features.h"
#include <iostream>

static int jump_cnt = 0;

void features::misc::RunBunnyHop(CUserCmd* cmd) {
	if (!(*toggles::misc::bhop)) {
		return;
	}

	globals::UpdateLocalPlayer();

	

	if (!globals::localPlayer || !globals::localPlayer->IsAlive() || globals::localPlayer->GetMoveType() == MOVETYPE_LADDER) {
		return;
	}

	if (cmd->buttons & CUserCmd::IN_JUMP) {
		if (!(globals::localPlayer->m_fFlags() & FL_ONGROUND)) {
			cmd->buttons &= ~CUserCmd::IN_JUMP;
		}
	}
}