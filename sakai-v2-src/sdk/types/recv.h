#pragma once
// Include std::int64_t
#include <cstdint>

class CRecvProxyData;
class CRecvTable;
class CRecvProp;

namespace U
{
	/*
	* Transfer data from recv proxy to your own structure.
	*/
	using RecvVarProxyFn = void(*)(const CRecvProxyData* Data, void* Struct, void* Out);

	/*
	* Set the array length on change.
	*/
	using ArrayLengthRecvProxyFn = void(*)(void* Struct, int ObjectID, int Length);

	/*
	* Unpack the datatable into a special object.
	*/
	using DataTableRecvVarProxyFn = void(*)(const CRecvProp* Prop, void** Out, void* Data, int ObjectID);
}

enum ESendProp : std::uint8_t
{
	DPT_INT = 0,
	DPT_FLT,
	DPT_VEC,
	DPT_VEC2D,
	DPT_STR,
	DPT_ARR,
	DPT_DT,
	DPT_I64,
	DPT_NUM_SEND_PROP_TYPES
};

class CStandardRecvProxies
{
public:
	CStandardRecvProxies() {}

public:
	U::RecvVarProxyFn m_Int32ToInt8;
	U::RecvVarProxyFn m_Int32ToInt16;
	U::RecvVarProxyFn m_Int32ToInt32;
	U::RecvVarProxyFn m_Int64ToInt64;
	U::RecvVarProxyFn m_FloatToFloat;
	U::RecvVarProxyFn m_VectorToVector;
};

class CRecvProxyData
{
public:
	const CRecvProp* m_pProperty;
	float			m_flValue;
	long			m_iValue;
	char*			m_szValue;
	void*			m_pData;
	float			m_vecValue[3];
	std::int64_t	m_i64Value;
	ESendProp		m_iType;
	std::int32_t	m_nElement;
	std::int32_t	m_nID;
};

class CRecvProp
{
public:
	char*			m_szVarName;
	ESendProp		m_nRecvType;
	int				m_Flags;
	int				m_StringBufferSize;
	bool			m_bInsideArray;
	const void*		m_pExtraData;
	CRecvProp*		m_pArrayProp;
	U::ArrayLengthRecvProxyFn m_fnArrayLengthProxy;
	U::RecvVarProxyFn m_fnProxyFn;
	U::DataTableRecvVarProxyFn m_fnDataTableProxyFn;
	CRecvTable*		m_pDataTable;
	int				m_iOffset;
	int				m_iElementStride;
	int				m_nElements;
	const char*		m_szParentArrayPropName;
};

class CRecvTable
{
public:
	CRecvProp*		m_pProps;
	int				m_nProps;
	void*			m_pDecoder;
	char*			m_szNetTableName;
	bool			m_bInitialized;
	bool			m_bInMainList;
};