#include <Windows.h>
#include <thread>
#include <stdexcept>
#include "src/interfaces.h"
#include "src/hooks.h"
#include <iostream>

// Get pointer to the interface
template<class T>
T* GetInterface(const char* name, const char* library) {
	const auto handle = GetModuleHandle(library);

	if (!handle) {
		throw std::runtime_error("Failed to get library handle!");
	}

	const auto functionAddres = GetProcAddress(handle, "CreateInterface");

	if (!functionAddres) {
		throw std::runtime_error("Failed to get CreateInterface() addres!");
	}

	using Fn = T * (*)(const char*, int*);
	const auto CreateInterface = reinterpret_cast<Fn>(functionAddres);

	return CreateInterface(name, nullptr);
}

void HackThread(HMODULE module) {

	AllocConsole();

	FILE* file;

	freopen_s(&file, "CONOUT$", "w", stdout);

	std::cout << "Setting up ninterfaces\n";
	interfaces::Setup();
	std::cout << "Interfaces setted up!\n";

	std::cout << "Setting up GUI\n";
	gui::Setup();
	std::cout << "GUI setted up!\n";
	hooks::Setup();
	std::cout << "Hooks setted up!\n";

	SetupNetvars();
	std::cout << "Netvars setted up!\n";

	// Main loop
	while (!GetAsyncKeyState(VK_END)) {

		if (GetAsyncKeyState(VK_INSERT) & 1) {
			gui::open = !gui::open;
		}

		Sleep(300);
	}

	FreeConsole();
	FreeLibraryAndExitThread(module, 0);
}

BOOL WINAPI DllMain(HMODULE module, DWORD reason, LPVOID reserved) {
	if (reason == DLL_PROCESS_ATTACH) {
		std::thread(HackThread, module).detach();
	}

	return TRUE;
}