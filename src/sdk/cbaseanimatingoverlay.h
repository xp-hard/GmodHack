#pragma once

#include "cbaseanimating.h"
#include "cvector.h"

#define CBaseAnimatingOverlay C_BaseAnimatingOverlay


class C_BaseAnimatingOverlay : public C_BaseAnimating
{
public:
	virtual CStudioHdr* OnNewModel();


	virtual void	GetRenderBounds(Vector& theMins, Vector& theMaxs);


	virtual void	AccumulateLayers(IBoneSetup& boneSetup, Vector pos[], Quaternion q[], float currentTime);
	virtual void DoAnimationEvents(CStudioHdr* pStudioHdr);

	enum
	{
		MAX_OVERLAYS = 15,
	};
};

typedef C_BaseAnimatingOverlay CBaseAnimatingOverlay;