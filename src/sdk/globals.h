#pragma once

class CBaseEntity;

namespace globals {
	inline void Setup() noexcept;
	inline void UpdateLocalPlayer() noexcept;

	inline CBaseEntity* localPlayer = nullptr;
}