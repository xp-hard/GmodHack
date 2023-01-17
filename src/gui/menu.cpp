#include "gui.h"

#include "../../ext/imgui/imgui.h"
#include "../../ext/imgui/backends/imgui_impl_dx9.h"
#include "../../ext/imgui/backends/imgui_impl_win32.h"

#include "../features/toggles.h"

#include <stdexcept>

#include <unordered_map>
#include <vector>

#include "tabs/include_tabs.h"

void gui::Render() noexcept {
	ImGui_ImplDX9_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	ImGui::Begin("Menu", &open,
		ImGuiWindowFlags_NoCollapse |
		ImGuiWindowFlags_NoTitleBar
	);

	if (*toggles::system::panic) {
		goto menu_end;
	}

	if (ImGui::BeginTabBar("Menu tabs", ImGuiTabBarFlags_NoTooltip)) {
		
		DrawTabVisuals();

		DrawTabAimbot();

		DrawTabMisc();

		ImGui::EndTabBar();
	}

menu_end:;

	ImGui::End();


	ImGui::EndFrame();
	ImGui::Render();
	ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
}
