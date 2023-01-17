#pragma once

#include "icliententity.h"
#include "../netvars.h"
#include "const.h"

class CBaseEntity : IClientEntity {
public: // enums
	
public: // netvars
	NETVAR(m_iHealth, "CBaseEntity->m_iHealth", int32_t);
	NETVAR(m_lifeState, "CBasePlayer->m_lifeState", char);

public: // Functions
	inline bool IsAlive() {
		return m_lifeState() == LIFE_ALIVE;
	}
};

typedef CBaseEntity C_BaseEntity;