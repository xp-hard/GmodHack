#pragma once

#include "includes.h"

inline void DrawTabAimbot() noexcept {
	ImGui::BeginTabItem("Visuals");

	ImGui::Checkbox("Chams", toggles::visuals::chams);

	ImGui::EndTabItem();
}