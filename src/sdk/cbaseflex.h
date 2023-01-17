#pragma once


#include "cbaseanimating.h"
#include "cbaseanimatingoverlay.h"
#include "cvector.h"
#include "igamesystem.h"

struct flexsettinghdr_t;

class CFlexSceneFile
{
public:
	enum
	{
		MAX_FLEX_FILENAME = 128,
	};

};

struct Emphasized_Phoneme;
class CSentence;

enum
{
	PHONEME_CLASS_WEAK = 0,
	PHONEME_CLASS_NORMAL,
	PHONEME_CLASS_STRONG,

	NUM_PHONEME_CLASSES
};

struct FS_LocalToGlobal_t;


class IHasLocalToGlobalFlexSettings
{
public:
	virtual void		EnsureTranslations(const flexsettinghdr_t* pSettinghdr) = 0;
};

struct Emphasized_Phoneme;

class CSceneEventInfo;
class CChoreoScene;
class CChoreoEvent;
class CChoreoActor;

class C_BaseFlex : public C_BaseAnimatingOverlay, public IHasLocalToGlobalFlexSettings
{
public:

	virtual			~C_BaseFlex();

	virtual void Spawn();

	virtual void InitPhonemeMappings();


	virtual CStudioHdr* OnNewModel(void);

	virtual void	StandardBlendingRules(CStudioHdr* hdr, Vector pos[], Quaternion q[], float currentTime, int boneMask);

	virtual void OnThreadedDrawSetup();

	virtual void BuildTransformations(CStudioHdr* pStudioHdr, Vector* pos, Quaternion q[], const matrix3x4_t& cameraTransform, int boneMask, CBoneBitList& boneComputed);
	virtual	void	SetupWeights(const matrix3x4_t* pBoneToWorld, int nFlexWeightCount, float* pFlexWeights, float* pFlexDelayedWeights);
	virtual	bool	SetupGlobalWeights(const matrix3x4_t* pBoneToWorld, int nFlexWeightCount, float* pFlexWeights, float* pFlexDelayedWeights);
	virtual	void	SetupLocalWeights(const matrix3x4_t* pBoneToWorld, int nFlexWeightCount, float* pFlexWeights, float* pFlexDelayedWeights);
	virtual bool	UsesFlexDelayedWeights();


	virtual Vector	SetViewTarget(CStudioHdr* pStudioHdr);

	virtual bool	GetSoundSpatialization(SpatializationInfo_t& info);

	virtual void	GetToolRecordingState(KeyValues* msg);


	virtual bool		StartSceneEvent(CSceneEventInfo* info, CChoreoScene* scene, CChoreoEvent* event, CChoreoActor* actor, C_BaseEntity* pTarget);

	virtual void		ProcessSceneEvents(bool bFlexEvents);

	virtual	bool		ProcessSceneEvent(bool bFlexEvents, CSceneEventInfo* info, CChoreoScene* scene, CChoreoEvent* event);

	virtual bool		ProcessSequenceSceneEvent(CSceneEventInfo* info, CChoreoScene* scene, CChoreoEvent* event);


	virtual	bool		ClearSceneEvent(CSceneEventInfo* info, bool fastKill, bool canceled);




	virtual bool		CheckSceneEventCompletion(CSceneEventInfo* info, float currenttime, CChoreoScene* scene, CChoreoEvent* event);


	virtual void		EnsureTranslations(const flexsettinghdr_t* pSettinghdr);

};


class CFlexSceneFileManager : CAutoGameSystem
{
public:

virtual bool Init();
virtual void Shutdown();
};

typedef C_BaseFlex CBaseFlex;