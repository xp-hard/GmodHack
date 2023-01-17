#include "../toggles.h"
#include "../../sdk/globals.h"
#include "../../hooks.h"
#include "../colors.h"

void __fastcall hooks::DrawModel(
	IStudioRender* self,
	DrawModelResults_t* results,
	const DrawModelInfo_t& info,
	CMatrix3x4* bones,
	float* flexWeights,
	float* flexDelayedWeights,
	const CVector& modelOrigin,
	const int32_t flags
) noexcept {
	if (toggles::visuals::chams && globals::localPlayer && info.m_pClientEntity) {
		C_BaseEntity* entity = info.m_pClientEntity->GetIClientUnknown()->GetBaseEntity();

		if (entity && entity->IsPlayer()) {
			static IMaterial* material = interfaces::materialSystem->FindMaterial("debug/debugambientcube", nullptr, true, nullptr);

			interfaces::studioRender->SetAlphaModulation(1.0f);

			material->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, true);
			interfaces::studioRender->SetColorModulation(colors::chams::hidden);
			interfaces::studioRender->ForcedMaterialOverride(material);
			hooks::DrawModelOriginal(interfaces::studioRender, results, info, bones, flexWeights, flexDelayedWeights, modelOrigin, flags);

			material->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, false);
			interfaces::studioRender->SetColorModulation(colors::chams::visible);
			interfaces::studioRender->ForcedMaterialOverride(material);
			hooks::DrawModelOriginal(interfaces::studioRender, results, info, bones, flexWeights, flexDelayedWeights, modelOrigin, flags);

			return interfaces::studioRender->ForcedMaterialOverride(nullptr);
		}
	}

	hooks::DrawModelOriginal(interfaces::studioRender, results, info, bones, flexWeights, flexDelayedWeights, modelOrigin, flags);
}