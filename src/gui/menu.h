#pragma once

#include "gui.h"
#include "../../ext/imgui/backends/imgui_impl_dx9.h"
#include "../../ext/imgui/backends/imgui_impl_win32.h"

//void gui::Render() noexcept {
//	ImGui_ImplDX9_NewFrame();
//	ImGui_ImplWin32_NewFrame();
//	ImGui::NewFrame();
//
//	ImGui::Begin("Menu", &open,
//		ImGuiWindowFlags_NoCollapse |
//		ImGuiWindowFlags_NoTitleBar
//	);
//
//
//	if (ImGui::BeginTabBar("Menu groups", ImGuiTabBarFlags_NoTooltip)) {
//		if (ImGui::BeginTabItem("Visuals")) {
//			ImGui::Button("Button", { 50, 25 });
//
//			ImGui::EndTabItem();
//		}
//		if (ImGui::BeginTabItem("Aimbot")) {
//
//			ImGui::EndTabItem();
//		}
//		ImGui::EndTabBar();
//	}
//
//	ImGui::End();
//
//
//	ImGui::EndFrame();
//	ImGui::Render();
//	ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
//}
