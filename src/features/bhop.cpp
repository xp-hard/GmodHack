#include "../sdk/globals.h"
#include "toggles.h"
#include "../sdk/const.h"
#include "features.h"
#include <iostream>

void features::RunBunnyHop(CUserCmd* cmd) {
	if (!toggles::bhop) {
		return;
	}

	std::cout << "In jump: " << (cmd->buttons & CUserCmd::IN_JUMP) << "On ground: " << (globals::localPlayer->m_fFlags() & FL_ONGROUND) << "\n";

	if (cmd->buttons & CUserCmd::IN_JUMP) {
		if (!(globals::localPlayer->m_fFlags() & FL_ONGROUND)) {
			cmd->buttons &= ~CUserCmd::IN_JUMP;
		}
	}
}