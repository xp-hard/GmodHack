#include "hooks.h"
#include <stdexcept>
#include <intrin.h>
#include "../../ext/minhook/include/MinHook.h"
#include "../../ext/imgui/imgui.h"
#include "../../ext/imgui/backends/imgui_impl_dx9.h"
#include "../../ext/imgui/backends/imgui_impl_win32.h"
#include "../utl/memory.h"

#include "sdk/globals.h"
#include "features/features.h"

void hooks::Setup() {
	if (MH_Initialize()) {
		throw std::runtime_error("Failed to initialize minhook!");
	}

	if (MH_CreateHook(
		memory::Get(gui::device, 42),
		&EndScence,
		reinterpret_cast<void**>(&EndScenceOriginal)
	)) {
		throw std::runtime_error("Unable to hook EndScence()!");
	}

	if (MH_CreateHook(
		memory::Get(gui::device, 16),
		&EndScence,
		reinterpret_cast<void**>(&ResetOriginal)
	)) {
		throw std::runtime_error("Unable to hook Reset()!");
	}

	if (MH_CreateHook(
		memory::Get(interfaces::studioRender, 29),
		&DrawModel,
		reinterpret_cast<void**>(&DrawModelOriginal)
	)) {
		throw std::runtime_error("Unable to hook DrawModel()");
	}

	if (MH_CreateHook(
		memory::Get(interfaces::clientMode, 21),
		&hooks::CreateMove,
		reinterpret_cast<void**>(&hooks::CreateMoveOriginal)
	)) {
		throw std::runtime_error("Unable to hook CreateMove()");
	}

	if (MH_EnableHook(MH_ALL_HOOKS)) {
		throw std::runtime_error("Failed to enable hooks!");
	}

	gui::DestroyDirectx();
}
void hooks::Destroy() noexcept {
	MH_DisableHook(MH_ALL_HOOKS);
	MH_RemoveHook(MH_ALL_HOOKS);
	MH_Uninitialize();
}

long __stdcall hooks::EndScence(IDirect3DDevice9* device) noexcept {
	static const auto returnAddres = _ReturnAddress();

	const auto result = EndScenceOriginal(device, device);
	
	if (_ReturnAddress() == returnAddres) {
		return result;
	}

	if (!gui::setup) {
		gui::SetupMenu(device);
	}

	if (gui::open) {
		gui::Render();
	}

	return result;
}
HRESULT __stdcall hooks::Reset(IDirect3DDevice9* device, D3DPRESENT_PARAMETERS* params) noexcept {
	ImGui_ImplDX9_InvalidateDeviceObjects();
	const auto result = ResetOriginal(device, device, params);
	ImGui_ImplDX9_CreateDeviceObjects();
	return result;
}

bool __stdcall hooks::CreateMove(float frameTime, CUserCmd* cmd) {
	const bool result = hooks::CreateMoveOriginal(interfaces::clientMode, frameTime, cmd);

	if (!cmd || !cmd->command_number) {
		return result;
	}

	globals::UpdateLocalPlayer();

	if (globals::localPlayer && globals::localPlayer->IsAlive()) {
		features::RunBunnyHop(cmd);
	}

	return result;
}