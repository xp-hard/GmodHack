#pragma once

#include <Windows.h>
#include <unordered_map>
#include <map>
#include <string>
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

inline std::map<std::string, intptr_t> netvars;

void Dump(const char* baseClass, RecvTable* table, intptr_t offset = 0);

void SetupNetvars();

#define NETVAR(func_name, netvar, type) type& func_name()\
{\
	static auto offset = netvars[netvar];\
	return *reinterpret_cast<type*>(uintptr_t(this) + offset);\
}