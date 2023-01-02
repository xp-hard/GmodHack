#include "globals.h"
#include "../interfaces.h"

void globals::Setup() noexcept {
	globals::UpdateLocalPlayer();
}

void globals::UpdateLocalPlayer() noexcept {
	auto localPlayerIndex = interfaces::engine->GetLocalPlayer();
	globals::localPlayer = interfaces::entityList->GetClientEntity(localPlayerIndex);
}