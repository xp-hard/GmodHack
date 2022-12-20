#pragma once

#include "../netvars.h"

//-----------------------------------------------------------------------------
// Purpose: All client entities must implement this interface.
//-----------------------------------------------------------------------------
class IClientEntity
{
public:
	NETVAR(m_iHealth, "CBasePlayer->m_iHealth", int32_t);
};
