#pragma once

class ClientClass
{
public:
	void* m_pCreateFn;
	void* m_pCreateEventFn;	// Only called for event objects.
	char* m_pNetworkName;
	RecvTable* m_pRecvTable;
	ClientClass* m_pNext;
	int						m_ClassID;	// Managed by the engine.
	const char* mapClassname;
};

class IBaseClientDll {
private:
	virtual void fn0() = 0;
	virtual void fn1() = 0;
	virtual void fn2() = 0;
	virtual void fn3() = 0;
	virtual void fn4() = 0;
	virtual void fn5() = 0;
	virtual void fn6() = 0;
	virtual void fn7() = 0;

public:
	virtual ClientClass* GetAllClasses(void) = 0;
};

#define CLIENT_DLL_INTERFACE_VERSION		"VClient017"