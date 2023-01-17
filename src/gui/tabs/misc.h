#pragma once

#include "includes.h"

inline void DrawTabMisc() noexcept {
	ImGui::BeginTabItem("Misc");
	
	ImGui::Checkbox("Bunny hop", toggles::misc::bhop);

	ImGui::EndTabItem();
}