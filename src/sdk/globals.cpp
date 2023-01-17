#include "globals.h"
#include "../interfaces.h"

void globals::Setup() noexcept {
	globals::UpdateLocalPlayer();
}

void globals::UpdateLocalPlayer() noexcept {
	auto localPlayerIndex = interfaces::engine->GetLocalPlayer();
	globals::localPlayer = (CBasePlayer*)interfaces::entityList->GetClientEntity(localPlayerIndex);
}