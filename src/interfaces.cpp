#include "interfaces.h"

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

void interfaces::Setup() noexcept
{
	// capture the interfaces
	void* client = Capture<IBaseClientDll>("client.dll", CLIENT_DLL_INTERFACE_VERSION);
	void* entityList = Capture<IClientEntityList>("client.dll", VCLIENTENTITYLIST_INTERFACE_VERSION);
	void* clientMode = **reinterpret_cast<IClientModeShared***>((*reinterpret_cast<unsigned int**>(client))[10] + 5);
	/*void* engineTrace = Capture<IEngineTrace>("engine.dll", "EngineTraceClient003");
	void* engineVGui = Capture<IEngineVGui>("engine.dll", "VEngineVGui001");*/
	/*void* globals = **reinterpret_cast<IGlobalVars***>((*reinterpret_cast<uintptr_t**>(client))[11] + 10);
	void* glow = *reinterpret_cast<IGlowManager**>(memory::glowManager);*/
	void* materialSystem = Capture<IMaterialSystem>("materialsystem.dll", "VMaterialSystem080");
	void* studioRender = Capture<IStudioRender>("studiorender.dll", "VStudioRender025");
	/*void* surface = Capture<ISurface>("vguimatsurface.dll", "VGUI_Surface031=0");
	void* debugOverlay = Capture<IVDebugOverlay>("engine.dll", "VDebugOverlay003");
	void* engine = Capture<IVEngineClient>("engine.dll", "VEngineClient014");
	void* modelInfo = Capture<IVModelInfo>("engine.dll", "VModelInfoClient006");
	void* panel = Capture<IVPanel>("vgui2.dll", "VGUI_Panel009");*/

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
