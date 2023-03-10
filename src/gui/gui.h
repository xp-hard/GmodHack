#pragma once

#include <d3d9.h>
#include <d3dx9.h>
#include "../../ext/imgui/imgui.h"

namespace gui {
	inline bool open = true;

	inline bool setup = false;

	inline ImVec2 gameWindowSize;

	inline HWND window = nullptr;
	inline WNDCLASSEX windowClass = {};
	inline WNDPROC originalWindowProcess = nullptr;

	inline LPDIRECT3DDEVICE9 device = nullptr;
	inline LPDIRECT3D9 d3d9 = nullptr;

	bool SetupWindowClass(const char* windowClassName) noexcept;
	void DestroyWindowClass() noexcept;

	bool SetupWindow(const char* windowName) noexcept;
	void DestoyWindow() noexcept;

	bool SetupDirectx() noexcept;
	void DestroyDirectx() noexcept;

	void Setup();

	void SetupMenu(LPDIRECT3DDEVICE9 device) noexcept;
	void Destroy() noexcept;

	void Render() noexcept;
}