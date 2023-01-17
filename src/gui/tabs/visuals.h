#pragma once

#include "includes.h"

inline void DrawTabVisuals() noexcept {
	ImGui::BeginTabItem("Visuals");

	ImGui::Checkbox("Chams", toggles::visuals::chams);

	ImGui::EndTabItem();
}