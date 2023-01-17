#pragma once

#include "cvector.h"
#include "cbaseentity.h"
#include "cbasecombatcharacter.h"
#include "cgameeventlistener.h"

class C_BaseCombatWeapon;
class C_BaseViewModel;
class C_FuncLadder;
class CFlashlightEffect;
class C_EconWearable;

class C_CommandContext
{
public:
	bool			needsprocessing;

	CUserCmd		cmd;
	int				command_number;
};

class C_PredictionError
{
public:
	float	time;
	Vector	error;
};

#define CHASE_CAM_DISTANCE_MIN	16.0f
#define CHASE_CAM_DISTANCE_MAX	96.0f
#define WALL_OFFSET				6.0f


class C_BasePlayer : public C_BaseCombatCharacter, public CGameEventListener
{
public: // virtual functions
	virtual			~C_BasePlayer();
	virtual void	Spawn(void);
	virtual void	SharedSpawn(); // Shared between client and server.
	virtual bool	GetSteamID(CSteamID* pID);
	virtual void	OnPreDataChanged(DataUpdateType_t updateType);
	virtual void	OnDataChanged(DataUpdateType_t updateType);
	virtual void	PreDataUpdate(DataUpdateType_t updateType);
	virtual void	PostDataUpdate(DataUpdateType_t updateType);
	virtual void	ReceiveMessage(int classID, bf_read& msg);
	virtual void	OnRestore();
	virtual void	AddEntity(void);
	virtual void	MakeTracer(const Vector& vecTracerSrc, const trace_t& tr, int iTracerType);
	virtual void	GetToolRecordingState(KeyValues* msg);
	virtual float GetPlayerMaxSpeed();
	virtual void		CalcView(Vector& eyeOrigin, QAngle& eyeAngles, float& zNear, float& zFar, float& fov);
	virtual void		CalcViewModelView(const Vector& eyeOrigin, const QAngle& eyeAngles);
	virtual float		CalcRoll(const QAngle& angles, const Vector& velocity, float rollangle, float rollspeed);
	virtual void			SetPlayerUnderwater(bool state);
	virtual Vector			Weapon_ShootPosition();
	virtual void			Weapon_DropPrimary(void) {}
	virtual Vector			GetAutoaimVector(float flScale);
	virtual bool	CreateMove(float flInputSampleTime, CUserCmd* pCmd);
	virtual void	AvoidPhysicsProps(CUserCmd* pCmd);
	virtual void	PlayerUse(void);
	virtual bool	IsUseableEntity(CBaseEntity* pEntity, unsigned int requiredCaps);
	virtual bool	IsPlayer(void) const { return true; }
	virtual int		GetHealth() const { return m_iHealth; }
	virtual int			GetObserverMode() const;
	virtual CBaseEntity* GetObserverTarget() const;
	virtual Vector		 EyePosition();
	virtual const QAngle& EyeAngles();		// Direction of eyes
	virtual const QAngle& LocalEyeAngles();		// Direction of eyes
	virtual IRagdoll* GetRepresentativeRagdoll() const;
	virtual void GetRagdollInitBoneArrays(matrix3x4_t* pDeltaBones0, matrix3x4_t* pDeltaBones1, matrix3x4_t* pCurrentBones, float boneDt);
	virtual void	TeamChange(int iNewTeam);
	virtual bool				IsAllowedToSwitchWeapons(void) { return !IsObserver(); }
	virtual C_BaseCombatWeapon* GetActiveWeaponForSelection(void);
	virtual C_BaseAnimating* GetRenderedWeaponModel();
	virtual bool				IsOverridingViewmodel(void) { return false; };
	virtual int					DrawOverriddenViewmodel(C_BaseViewModel* pViewmodel, int flags) { return 0; };
	virtual float				GetDefaultAnimSpeed(void) { return 1.0; }
	virtual ShadowType_t		ShadowCastType() { return SHADOWS_NONE; }
	virtual bool				ShouldReceiveProjectedTextures(int flags)
	{
		return false;
	}
	virtual void				ThirdPersonSwitch(bool bThirdperson);
	virtual bool				CanSetSoundMixer(void);
	virtual int					GetVisionFilterFlags(bool bWeaponsCheck = false) { return 0x00; }
	virtual void				CalculateVisionUsingCurrentFlags(void) {}
	virtual bool				ViewModel_IsTransparent(void);
	virtual bool				ViewModel_IsUsingFBTexture(void);
	virtual void				PhysicsSimulate(void);
	virtual unsigned int	PhysicsSolidMaskForEntity(void) const { return MASK_PLAYERSOLID; }
	virtual bool				ShouldPredict(void);
	virtual void				PreThink(void);
	virtual void				PostThink(void);
	virtual void				ItemPreFrame(void);
	virtual void				ItemPostFrame(void);
	virtual void				AbortReload(void);
	virtual void				SelectLastItem(void);
	virtual void				Weapon_SetLast(C_BaseCombatWeapon* pWeapon);
	virtual bool				Weapon_ShouldSetLast(C_BaseCombatWeapon* pOldWeapon, C_BaseCombatWeapon* pNewWeapon) { return true; }
	virtual bool				Weapon_ShouldSelectItem(C_BaseCombatWeapon* pWeapon);
	virtual	bool				Weapon_Switch(C_BaseCombatWeapon* pWeapon, int viewmodelindex = 0);		// Switch to given weapon if has ammo (false if failed)
	virtual C_BaseCombatWeapon* GetLastWeapon(void) { return m_hLastWeapon.Get(); }
	virtual void 				SelectItem(const char* pstr, int iSubType = 0);
	virtual void				UpdateClientData(void);
	virtual float				GetFOV(void);
	virtual bool				IsZoomed(void) { return false; }
	virtual void				ViewPunch(const QAngle& angleOffset);
	virtual void				Simulate();
	virtual bool				ShouldInterpolate();
	virtual bool				ShouldDraw();
	virtual int					DrawModel(int flags);
	virtual void				OverrideView(CViewSetup* pSetup);
	virtual const Vector		GetPlayerMins(void) const; // uses local player
	virtual const Vector		GetPlayerMaxs(void) const; // uses local player
	virtual void	SetVehicleRole(int nRole);
	virtual void			SetAnimation(PLAYER_ANIM playerAnim);
	virtual float GetMinFOV() const;
	virtual void DoMuzzleFlash();
	virtual void PlayPlayerJingle();
	virtual void UpdateStepSound(surfacedata_t* psurface, const Vector& vecOrigin, const Vector& vecVelocity);
	virtual void PlayStepSound(Vector& vecOrigin, surfacedata_t* psurface, float fvol, bool force);
	virtual surfacedata_t* GetFootstepSurface(const Vector& origin, const char* surfaceName);
	virtual void GetStepSoundVelocities(float* velwalk, float* velrun);
	virtual void SetStepSoundTime(stepsoundtimes_t iStepSoundTime, bool bWalking);
	virtual const char* GetOverrideStepSound(const char* pszBaseStepSoundName) { return pszBaseStepSoundName; }
	virtual void OnEmitFootstepSound(const CSoundParameters& params, const Vector& vecOrigin, float fVolume) {}
	virtual void ExitLadder() {}
	virtual CHintSystem* Hints(void) { return NULL; }
	virtual	IMaterial* GetHeadLabelMaterial(void);
	virtual void			OnAchievementAchieved(int iAchievement) {}
	virtual bool			CanUseFirstPersonCommand(void) { return true; }
	virtual void		CalcObserverView(Vector& eyeOrigin, QAngle& eyeAngles, float& fov);
	virtual Vector		GetChaseCamViewOffset(CBaseEntity* target);
	virtual void		CalcInEyeCamView(Vector& eyeOrigin, QAngle& eyeAngles, float& fov);
	virtual float		GetDeathCamInterpolationTime();
	virtual void		CalcDeathCamView(Vector& eyeOrigin, QAngle& eyeAngles, float& fov);
	virtual void		CalcFreezeCamView(Vector& eyeOrigin, QAngle& eyeAngles, float& fov);
	virtual void SetLocalViewAngles(const QAngle& viewAngles);
	virtual void SetViewAngles(const QAngle& ang);
	virtual void	FireGameEvent(IGameEvent* event);
	virtual bool IsDucked(void) const { return m_Local.m_bDucked; }
	virtual bool IsDucking(void) const { return m_Local.m_bDucking; }
	virtual float GetFallVelocity(void) { return m_Local.m_flFallVelocity; }
	struct StepSoundCache_t
	{
		StepSoundCache_t() : m_usSoundNameIndex(0) {}
		CSoundParameters	m_SoundParameters;
		unsigned short		m_usSoundNameIndex;
	};
};

typedef C_BasePlayer CBasePlayer;