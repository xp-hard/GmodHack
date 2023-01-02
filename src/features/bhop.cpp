#include "../sdk/globals.h"
#include "toggles.h"
#include "../sdk/const.h"
#include "features.h"

void features::RunBunnyHop(CUserCmd* cmd) {
	if (!toggles::bhop) {
		return;
	}

	if (!GetAsyncKeyState(VK_SPACE)) {
		return;
	}

	if (!(globals::localPlayer->m_fFlags() & FL_ONGROUND)) {
		cmd->buttons &= ~CUserCmd::IN_JUMP;
	}
}