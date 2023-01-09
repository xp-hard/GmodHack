#pragma once

#include "gui/gui.h"
#include "interfaces.h"

namespace hooks {
	void Setup();
	void Destroy() noexcept;

	using EndScenceFn = long(__thiscall*)(void*, IDirect3DDevice9*) noexcept;
	inline EndScenceFn EndScenceOriginal = nullptr;
	long __stdcall EndScence(IDirect3DDevice9* device) noexcept;

	using ResetFn = HRESULT(__thiscall*)(void*, IDirect3DDevice9*, D3DPRESENT_PARAMETERS*) noexcept;
	inline ResetFn ResetOriginal = nullptr;
	HRESULT __stdcall Reset(IDirect3DDevice9* device, D3DPRESENT_PARAMETERS* params) noexcept;

	using AllocateVirtualMemoryFn = void* (__thiscall*)(void*, const int32_t) noexcept;
	inline AllocateVirtualMemoryFn AllocKeyValuesMemoryOriginal;
	void* __stdcall AllocKeyValuesMemory(const int32_t size) noexcept;

	using CreateMoveFn = bool(__thiscall*)(IClientModeShared*, float, CUserCmd* cmd);
	inline CreateMoveFn CreateMoveOriginal = nullptr;
	bool __fastcall CreateMove(IClientModeShared* self, float frameTime, CUserCmd* cmd);

	using DrawModelFn = void(__thiscall*)(
		void*,
		DrawModelResults_t*,
		const DrawModelInfo_t&,
		CMatrix3x4*,
		float*,
		float*,
		const CVector&,
		const int32_t
	) noexcept;

	inline DrawModelFn DrawModelOriginal = nullptr;

	void __stdcall DrawModel(
		DrawModelResults_t* results,
		const DrawModelInfo_t& info,
		CMatrix3x4* bones,
		float* flexWeights,
		float* flexDelayedWeights,
		const CVector& modelOrigin,
		const int32_t flags
	) noexcept;
}

