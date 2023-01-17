#pragma once

#include "cbaseflex.h"

class C_BaseCombatWeapon;
class C_WeaponCombatShield;

#define BCC_DEFAULT_LOOK_TOWARDS_TOLERANCE 0.9f

class C_BaseCombatCharacter : public C_BaseFlex
{
public:

	virtual			~C_BaseCombatCharacter(void);

	virtual void	OnPreDataChanged(DataUpdateType_t updateType);
	virtual void	OnDataChanged(DataUpdateType_t updateType);

	virtual bool	IsBaseCombatCharacter(void) { return true; };
	virtual C_BaseCombatCharacter* MyCombatCharacterPointer(void) { return this; }

	enum FieldOfViewCheckType { USE_FOV, DISREGARD_FOV };

	virtual bool IsLookingTowards(const CBaseEntity* target, float cosTolerance = BCC_DEFAULT_LOOK_TOWARDS_TOLERANCE) const;	// return true if our view direction is pointing at the given target, within the cosine of the angular tolerance. LINE OF SIGHT IS NOT CHECKED.
	virtual bool IsLookingTowards(const Vector& target, float cosTolerance = BCC_DEFAULT_LOOK_TOWARDS_TOLERANCE) const;	// return true if our view direction is pointing at the given target, within the cosine of the angular tolerance. LINE OF SIGHT IS NOT CHECKED.

	virtual bool IsInFieldOfView(CBaseEntity* entity) const;	// Calls IsLookingAt with the current field of view.  
	virtual bool IsInFieldOfView(const Vector& pos) const;

	enum LineOfSightCheckType
	{
		IGNORE_NOTHING,
		IGNORE_ACTORS
	};
	virtual bool IsLineOfSightClear(CBaseEntity* entity, LineOfSightCheckType checkType = IGNORE_NOTHING) const;// strictly LOS check with no other considerations
	virtual bool IsLineOfSightClear(const Vector& pos, LineOfSightCheckType checkType = IGNORE_NOTHING, CBaseEntity* entityToIgnore = NULL) const;



	virtual	bool		Weapon_Switch(C_BaseCombatWeapon* pWeapon, int viewmodelindex = 0);
	virtual bool		Weapon_CanSwitchTo(C_BaseCombatWeapon* pWeapon);

	virtual C_BaseCombatWeapon* GetActiveWeapon(void) const;



	virtual int			BloodColor();


	virtual void		DoMuzzleFlash();

#ifdef GLOWS_ENABLE
	virtual void		GetGlowEffectColor(float* r, float* g, float* b);
#endif // GLOWS_ENABLE

#ifdef GLOWS_ENABLE	
	virtual void		UpdateGlowEffect(void);
	virtual void		DestroyGlowEffect(void);
#endif // GLOWS_ENABLE



#ifdef GLOWS_ENABLE
#endif // 

#ifdef INVASION_CLIENT_DLL
public:
	virtual void	Release(void);
	virtual void	SetDormant(bool bDormant);
	virtual void	OnPreDataChanged(DataUpdateType_t updateType);
	virtual void	OnDataChanged(DataUpdateType_t updateType);
	virtual void	ClientThink(void);

	virtual bool	CanBePoweredUp(void) { return true; }
	virtual void	PowerupStart(int iPowerup, bool bInitial);
	virtual void	PowerupEnd(int iPowerup);

#endif

};

typedef C_BaseCombatCharacter CBaseCombatCharacter;