#include "interfaces.h"

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <stdexcept>

void interfaces::Setup() noexcept
{
	// capture the interfaces
	interfaces::client = Capture<IBaseClientDll>("client.dll", CLIENT_DLL_INTERFACE_VERSION);
	interfaces::entityList = Capture<IClientEntityList>("client.dll", VCLIENTENTITYLIST_INTERFACE_VERSION);
	do {
		auto address = (uintptr_t)memory::PatternScan("client.dll", "48 8B 0D ? ? ? ? 48 8B 01 48 FF 60 50 CC CC 48 83 EC 28");
		auto address_of_next = address + 7;
		auto relative = *(int*)(address + 3);
		auto absolute = address_of_next + relative;
		interfaces::clientMode = *(IClientModeShared**)(absolute);
	} while (!clientMode);
	/*void* engineTrace = Capture<IEngineTrace>("engine.dll", "EngineTraceClient003");
	void* engineVGui = Capture<IEngineVGui>("engine.dll", "VEngineVGui001");*/
	/*void* globals = **reinterpret_cast<IGlobalVars***>((*reinterpret_cast<uintptr_t**>(client))[11] + 10);
	void* glow = *reinterpret_cast<IGlowManager**>(memory::glowManager);*/
	interfaces::materialSystem = Capture<IMaterialSystem>("materialsystem.dll", MATERIAL_SYSTEM_INTERFACE_VERSION);
	interfaces::studioRender = Capture<IStudioRender>("studiorender.dll", STUDIO_RENDER_INTERFACE_VERSION);
	//void* surface = Capture<ISurface>("vguimatsurface.dll", "VGUI_Surface031=0");
	//void* debugOverlay = Capture<IVDebugOverlay>("engine.dll", "VDebugOverlay003");
	interfaces::engine = Capture<IVEngineClient>("engine.dll", VENGINE_CLIENT_INTERFACE_VERSION);
	//void* modelInfo = Capture<IVModelInfo>("engine.dll", "VModelInfoClient006");
	//void* panel = Capture<IVPanel>("vgui2.dll", "VGUI_Panel009");*/
	interfaces::lua_shared = Capture<LUA::Shared>("lua_shared.dll", "LUASHARED003");

	// get the exported KeyValuesSystem function
	if (const HINSTANCE handle = GetModuleHandle("vstdlib.dll"))
		// set our pointer by calling the function
		keyValuesSystem = reinterpret_cast<void* (__cdecl*)()>(GetProcAddress(handle, "KeyValuesSystem"))();
}

template <typename Interface>
Interface* interfaces::Capture(const char* moduleName, const char* interfaceName) noexcept
{
	const HINSTANCE handle = GetModuleHandle(moduleName);

	if (!handle)
		return nullptr;

	// get the exported Createinterface function
	using CreateInterfaceFn = Interface * (__cdecl*)(const char*, int*);
	const CreateInterfaceFn createInterface =
		reinterpret_cast<CreateInterfaceFn>(GetProcAddress(handle, "CreateInterface"));

	// return the interface pointer by calling the function
	return createInterface(interfaceName, nullptr);
}
