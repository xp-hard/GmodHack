#include "../sdk/globals.h"
#include "toggles.h"
#include "../sdk/const.h"
#include "features.h"
#include <iostream>

static int jump_cnt = 0;

void features::RunBunnyHop(CUserCmd* cmd) {
	if (!toggles::bhop) {
		return;
	}

	if (cmd->buttons & CUserCmd::IN_JUMP) {
		std::cout << "In Jump! " << jump_cnt++ << "\n";
	}

	if (cmd->buttons & CUserCmd::IN_JUMP) {
		if (!(globals::localPlayer->m_fFlags() & FL_ONGROUND)) {
			cmd->buttons &= ~CUserCmd::IN_JUMP;
		}
	}
}