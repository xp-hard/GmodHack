#pragma once

#include "cbaseentity.h"
#include "cvector.h"
#include "imodelloadcallback.h"
#include "const.h"
#include "icliententity.h"
#include "ivphysics.h"

#define LIPSYNC_POSEPARAM_NAME "mouth"
#define NUM_HITBOX_FIRES	10
/*
class C_BaseClientShader
{
	virtual void RenderMaterial(C_BaseEntity* pEntity, int count, const vec4_t* verts, const vec4_t* normals, const vec2_t* texcoords, vec4_t* lightvalues);
};*/

class IRagdoll;
class CIKContext;
class CIKState;
class ConVar;
class C_RopeKeyframe;
class CBoneBitList;
class CBoneList;
class KeyValues;
class CJiggleBones;
class IBoneSetup;


struct ClientModelRenderInfo_t : public ModelRenderInfo_t {};
struct RagdollInfo_t;


class CAttachmentData;
typedef unsigned short MDLHandle_t;



#define		INVALID_CLIENTSIDEANIMATION_LIST_HANDLE	(ClientSideAnimationListHandle_t)~0


class C_BaseAnimating : public C_BaseEntity, private IModelLoadCallback
{
public:

	enum
	{
		NUM_POSEPAREMETERS = 24,
		NUM_BONECTRLS = 4
	};


	virtual C_BaseAnimating* GetBaseAnimating() { return this; }


	virtual bool	Interpolate(float currentTime);
	virtual void	Simulate();
	virtual void	Release();


	virtual unsigned char	GetClientSideFade(void);

	virtual void	GetBoneControllers(float controllers[MAXSTUDIOBONECTRLS]);
	virtual float	SetBoneController(int iController, float flValue);


	virtual void	GetAimEntOrigin(IClientEntity* pAttachedTo, Vector* pAbsOrigin, QAngle* pAbsAngles);



	virtual void GetPoseParameters(CStudioHdr* pStudioHdr, float poseParameter[MAXSTUDIOPOSEPARAM]);
	virtual void BuildTransformations(CStudioHdr* pStudioHdr, Vector* pos, Quaternion q[], const matrix3x4_t& cameraTransform, int boneMask, CBoneBitList& boneComputed);
	virtual void ApplyBoneMatrixTransform(matrix3x4_t& transform);
	virtual int	VPhysicsGetObjectList(IPhysicsObject** pList, int listMax);

	virtual bool SetupBones(matrix3x4_t* pBoneToWorldOut, int nMaxBones, int boneMask, float currentTime);
	virtual void UpdateIKLocks(float currentTime);
	virtual void CalculateIKLocks(float currentTime);
	virtual bool ShouldDraw();
	virtual int DrawModel(int flags);
	virtual int	InternalDrawModel(int flags);
	virtual bool OnInternalDrawModel(ClientModelRenderInfo_t* pInfo);
	virtual bool OnPostInternalDrawModel(ClientModelRenderInfo_t* pInfo);

	virtual CMouthInfo* GetMouth();
	virtual void	ControlMouth(CStudioHdr* pStudioHdr);
	virtual void DoAnimationEvents(CStudioHdr* pStudio);
	virtual void FireEvent(const Vector& origin, const QAngle& angles, int event, const char* options);
	virtual void FireObsoleteEvent(const Vector& origin, const QAngle& angles, int event, const char* options);
	virtual const char* ModifyEventParticles(const char* token) { return token; }

	virtual bool DispatchMuzzleEffect(const char* options, bool isFirstPerson);


	virtual void ValidateModelIndex(void);
	virtual CStudioHdr* OnNewModel(void);
	virtual void SetPredictable(bool state);


	virtual	void StandardBlendingRules(CStudioHdr* pStudioHdr, Vector pos[], Quaternion q[], float currentTime, int boneMask);

	virtual void AccumulateLayers(IBoneSetup& boneSetup, Vector pos[], Quaternion q[], float currentTime);

	virtual void ChildLayerBlend(Vector pos[], Quaternion q[], float currentTime, int boneMask);

	virtual void		AttachEntityToBone(C_BaseAnimating* attachTarget, int boneIndexAttached = -1, Vector bonePosition = Vector(0, 0, 0), QAngle boneAngles = QAngle(0, 0, 0));
	virtual void		NotifyBoneAttached(C_BaseAnimating* attachTarget);
	virtual void		UpdateBoneAttachments(void);


	virtual void					PreDataUpdate(DataUpdateType_t updateType);
	virtual void					PostDataUpdate(DataUpdateType_t updateType);
	virtual int						RestoreData(const char* context, int slot, int type);

	virtual void					NotifyShouldTransmit(ShouldTransmitState_t state);
	virtual void					OnPreDataChanged(DataUpdateType_t updateType);
	virtual void					OnDataChanged(DataUpdateType_t updateType);
	virtual void					AddEntity(void);


	virtual bool					IsSelfAnimating();
	virtual void					ResetLatched();

	virtual void					GetRenderBounds(Vector& theMins, Vector& theMaxs);
	virtual const Vector& GetRenderOrigin(void);
	virtual const QAngle& GetRenderAngles(void);

	virtual bool					GetSoundSpatialization(SpatializationInfo_t& info);


	virtual bool					GetAttachment(int number, Vector& origin);
	virtual bool					GetAttachment(int number, Vector& origin, QAngle& angles);
	virtual bool					GetAttachment(int number, matrix3x4_t& matrix);
	virtual bool					GetAttachmentVelocity(int number, Vector& originVel, Quaternion& angleVel);


	virtual ShadowType_t			ShadowCastType();

	virtual CollideType_t			GetCollideType(void);

	virtual bool					TestCollision(const Ray_t& ray, unsigned int fContentsMask, trace_t& tr);
	virtual bool					TestHitboxes(const Ray_t& ray, unsigned int fContentsMask, trace_t& tr);

	virtual C_BaseAnimating* BecomeRagdollOnClient();
	virtual void					SaveRagdollInfo(int numbones, const matrix3x4_t& cameraTransform, CBoneAccessor& pBoneToWorld);
	virtual bool					RetrieveRagdollInfo(Vector* pos, Quaternion* q);
	virtual void					Clear(void);
	virtual void					GetRagdollInitBoneArrays(matrix3x4_t* pDeltaBones0, matrix3x4_t* pDeltaBones1, matrix3x4_t* pCurrentBones, float boneDt);

	virtual int GetBody() { return m_nBody; }
	virtual int GetSkin() { return m_nSkin; }



	virtual	void					RefreshCollisionBounds(void);

	virtual void					SetSequence(int nSequence);
	virtual void					StudioFrameAdvance(); // advance animation frame to some time in the future

	virtual float					FrameAdvance(float flInterval = 0.0f);
	virtual float					GetSequenceCycleRate(CStudioHdr* pStudioHdr, int iSequence);
	virtual void					UpdateClientSideAnimation();
	virtual unsigned int			ComputeClientSideAnimationFlags();

	virtual void ResetClientsideFrame(void) { SetCycle(0); }




	class CBoneCache* GetBoneCache(CStudioHdr* pStudioHdr);


	virtual bool					IsActivityFinished(void) { return m_bSequenceFinished; }

	virtual void					UncorrectViewModelAttachment(Vector& vOrigin) {}



	struct AutoAllowBoneAccess
	{
	};


	virtual void					VPhysicsUpdate(IPhysicsObject* pPhysics);

	virtual void DoMuzzleFlash();	// Force a muzzle flash event. Note: this only QUEUES an event, so

	virtual void ProcessMuzzleFlashEvent();


	virtual void SetServerIntendedCycle(float intended) { (void)intended; }
	virtual float GetServerIntendedCycle(void) { return -1.0f; }



	virtual void					GetToolRecordingState(KeyValues* msg);
	virtual void					CleanupToolRecordingState(KeyValues* msg);

	virtual bool					ShouldResetSequenceOnNewModel(void);

	virtual bool					IsViewModel() const;

	virtual void					FormatViewModelAttachment(int nAttachment, matrix3x4_t& attachmentToWorld) {}


	virtual bool					IsMenuModel() const;

	virtual int						GetStudioBody(void) { return m_nBody; }

	virtual bool					CalcAttachments();

	virtual float					LastBoneChangedTime() { return FLT_MAX; }


public:
	virtual void					OnModelLoadComplete(const model_t* pModel);

};

enum
{
	RAGDOLL_FRICTION_OFF = -2,
	RAGDOLL_FRICTION_NONE,
	RAGDOLL_FRICTION_IN,
	RAGDOLL_FRICTION_HOLD,
	RAGDOLL_FRICTION_OUT,
};

class C_ClientRagdoll : public C_BaseAnimating, public IPVSNotify
{
public:

	virtual void OnPVSStatusChanged(bool bInPVS);

	virtual void Release(void);
	virtual void SetupWeights(const matrix3x4_t* pBoneToWorld, int nFlexWeightCount, float* pFlexWeights, float* pFlexDelayedWeights);
	virtual void ImpactTrace(trace_t* pTrace, int iDamageType, const char* pCustomImpactName);
	virtual void	OnSave();
	virtual void	OnRestore();
	virtual int ObjectCaps(void) { return BaseClass::ObjectCaps() | FCAP_SAVE_NON_NETWORKABLE; }
	virtual IPVSNotify* GetPVSNotifyInterface() { return this; }

	virtual void SUB_Remove(void);

	virtual float LastBoneChangedTime();





};

typedef C_BaseAnimating CBaseAnimating;