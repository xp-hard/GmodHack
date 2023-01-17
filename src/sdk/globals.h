#pragma once

class CBasePlayer;

namespace globals {
	void Setup() noexcept;
	void UpdateLocalPlayer() noexcept;

	inline CBasePlayer* localPlayer = nullptr;
}