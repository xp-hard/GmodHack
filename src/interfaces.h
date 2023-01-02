#pragma once

#include "sdk/cusercmd.h"
#include "sdk/cvector.h"
#include "sdk/cmatrix.h"
#include "sdk/cbaseentity.h"
#include "sdk/const.h"

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
#include "sdk/ivengineclient.h"

namespace interfaces
{
	// call once to capture all interface pointers
	void Setup() noexcept;

	// capture an individual interface by name & module
	template <typename Interface>
	Interface* Capture(const char* moduleName, const char* interfaceName) noexcept;

	// interface pointers
	inline IBaseClientDll* client = nullptr;
	inline IClientEntityList* entityList = nullptr;
	inline IClientModeShared* clientMode = nullptr;
	/*IEngineTrace* engineTrace = nullptr;
	IEngineVGui* engineVGui = nullptr;
	IGlobalVars* globals = nullptr;
	IGlowManager* glow = nullptr;*/
	inline IMaterialSystem* materialSystem = nullptr;
	inline IStudioRender* studioRender = nullptr;
	//ISurface* surface = nullptr;
	//IVDebugOverlay* debugOverlay = nullptr;
	inline IVEngineClient* engine = nullptr;
	//IVModelInfo* modelInfo = nullptr;
	//IVPanel* panel = nullptr;

	// other
	inline void* keyValuesSystem = nullptr;
}