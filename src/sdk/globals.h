#pragma once

class CBaseEntity;

namespace globals {
	void Setup() noexcept;
	void UpdateLocalPlayer() noexcept;

	inline CBasePlayer* localPlayer = nullptr;
}