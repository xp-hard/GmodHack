#pragma once

#include "netvars.h"

#include "sdk/cusercmd.h"
#include "sdk/cvector.h"
#include "sdk/cmatrix.h"

#include "sdk/iclient.h"
#include "sdk/icliententity.h"
#include "sdk/icliententitylist.h"
#include "sdk/iappsystem.h"
#include "sdk/imaterialsystem.h"
#include "sdk/istudiorender.h"
#include "sdk/iclientmodeshared.h"
#include "sdk/ibaseclientdll.h"
#include "sdk/iclientunknown.h"
#include "sdk/iclientrenderable.h"
#include "sdk/ihandleentity.h"

namespace interfaces
{
	// call once to capture all interface pointers
	void Setup() noexcept;

	// capture an individual interface by name & module
	template <typename Interface>
	Interface* Capture(const char* moduleName, const char* interfaceName) noexcept;

	// interface pointers
	IBaseClientDll* client = nullptr;
	IClientEntityList* entityList = nullptr;
	IClientModeShared* clientMode = nullptr;
	/*IEngineTrace* engineTrace = nullptr;
	IEngineVGui* engineVGui = nullptr;
	IGlobalVars* globals = nullptr;
	IGlowManager* glow = nullptr;*/
	IMaterialSystem* materialSystem = nullptr;
	IStudioRender* studioRender = nullptr;
	/*ISurface* surface = nullptr;
	IVDebugOverlay* debugOverlay = nullptr;
	IVEngineClient* engine = nullptr;
	IVModelInfo* modelInfo = nullptr;
	IVPanel* panel = nullptr;*/

	// other
	void* keyValuesSystem = nullptr;
}