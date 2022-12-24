#pragma once

#include <Windows.h>
#include <unordered_map>
#include <map>
#include <format>

enum class SendPropType : int
{
	INT = 0,
	FLOAT,
	VECTOR,
	VECTOR2D,
	STRING,
	ARRAY,
	DATATABLE,
	INT64,
	SENDPROPTYPEMAX
};

class RecvTable;

class RecvProp
{
	// This info comes from the receive data table.
public:
	const char* m_pVarName;
	SendPropType m_RecvType;
	int						m_Flags;
	int						m_StringBufferSize;

	bool					m_bInsideArray;		// Set to true by the engine if this property sits inside an array.

	// Extra data that certain special property types bind to the property here.
	const void* m_pExtraData;

	// If this is an array (DPT_Array).
	RecvProp* m_pArrayProp;
	void* m_ArrayLengthProxy;

	void* m_ProxyFn;
	void* m_DataTableProxyFn;	// For RDT_DataTable.

	RecvTable* m_pDataTable;		// For RDT_DataTable.
	int						m_Offset;

	int						m_ElementStride;
	int						m_nElements;

	// If it's one of the numbered "000", "001", etc properties in an array, then
	// these can be used to get its array property name for debugging.
	const char* m_pParentArrayPropName;
};


class RecvTable
{
public:

	typedef RecvProp	PropType;
	// Properties described in a table.
	RecvProp* m_pProps;
	int				m_nProps;

	// The decoder. NOTE: this covers each RecvTable AND all its children (ie: its children
	// will have their own decoders that include props for all their children).
	void* m_pDecoder;

	const char* m_pNetTableName;	// The name matched between client and server

	bool			m_bInitialized;
	bool			m_bInMainList;
};

class ClientClass
{
public:
	void*		m_pCreateFn;
	void*			m_pCreateEventFn;	// Only called for event objects.
	char* m_pNetworkName;
	RecvTable* m_pRecvTable;
	ClientClass* m_pNext;
	int						m_ClassID;	// Managed by the engine.
	const char* mapClassname;
};

std::map<const char*, intptr_t> netvars;

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


void Dump(const char* baseClass, RecvTable* table, intptr_t offset = 0);

void SetupNetvars(IBaseClientDll *client) {
	for (auto node = client->GetAllClasses(); node; node = node->m_pNext) {
		if (node->m_pRecvTable) {
			Dump(node->m_pNetworkName, node->m_pRecvTable, 0);
		}
	}

	123;
}

void Dump(const char* baseClass, RecvTable* table, intptr_t offset) {
	for (int i = 0; i < table->m_nProps; ++i) {
		const auto prop = &table->m_pProps[i];

		if (!prop || isdigit(prop->m_pVarName[0])) {
			continue;
		}

		if (prop->m_pVarName == "baseclass") {
			continue;
		}

		if (
			prop->m_RecvType == SendPropType::DATATABLE &&
			prop->m_pDataTable &&
			prop->m_pDataTable->m_pNetTableName[0] == 'D'
		) {

			Dump(baseClass, prop->m_pDataTable, offset + prop->m_Offset);
		}

		const auto netvarName = std::format("{}->{}", baseClass, prop->m_pVarName);

		netvars[netvarName.c_str()] = offset + prop->m_Offset;
	}
}

#define NETVAR(func_name, netvar, type) type& func_name()\
{\
	static auto offset = netvars[netvar];\
	return *reinterpret_cast<type*>(uintptr_t(this) + offset);\
}

#define CLIENT_DLL_INTERFACE_VERSION		"VClient017"