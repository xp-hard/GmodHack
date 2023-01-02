#pragma once

#include "ihandleentity.h"
#include "../../utl/memory.h"

class IClientNetworkable;
class C_BaseEntity : public IClientEntity {
public: // Functions
	constexpr bool IsPlayer() noexcept
	{
		return memory::Call<bool>(this, 158);
	}
};
class IClientRenderable;
class ICollideable;
class IClientEntity;
class IClientThinkable;



// This is the client's version of IUnknown. We may want to use a QueryInterface-like
// mechanism if this gets big.
class IClientUnknown : public IHandleEntity
{
public:
	virtual ICollideable * GetCollideable() = 0;
	virtual IClientNetworkable* GetClientNetworkable() = 0;
	virtual IClientRenderable* GetClientRenderable() = 0;
	virtual IClientEntity* GetIClientEntity() = 0;
	virtual C_BaseEntity* GetBaseEntity() = 0;
	virtual IClientThinkable* GetClientThinkable() = 0;
};