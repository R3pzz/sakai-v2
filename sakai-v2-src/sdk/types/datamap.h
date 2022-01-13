#pragma once
// Include basic std types
#include "../../includes.h"
// Include FNV()
#include "../../core/security.h"

class CDatamap;
struct TypeDesc_t;

enum class EFieldType
{
	FIELD_VOID = 0,
	FIELD_FLOAT,
	FIELD_STRING,
	FIELD_VECTOR,
	FIELD_QUATERNION,
	FIELD_INTEGER,
	FIELD_BOOLEAN,
	FIELD_SHORT,
	FIELD_CHARACTER,
	FIELD_COLOR32,
	FIELD_EMBEDDED,
	FIELD_CUSTOM,
	FIELD_CLASSPTR,
	FIELD_EHANDLE,
	FIELD_EDICT,
	FIELD_POSITION_VECTOR,
	FIELD_TIME,
	FIELD_TICK,
	FIELD_MODELNAME,
	FIELD_SOUNDNAME,
	FIELD_INPUT,
	FIELD_FUNCTION,
	FIELD_VMATRIX,
	FIELD_VMATRIX_WORLDSPACE,
	FIELD_MATRIX3X4_WORLDSPACE,
	FIELD_INTERVAL,
	FIELD_MODELINDEX,
	FIELD_MATERIALINDEX,
	FIELD_VECTOR2D,
	FIELD_INTEGER64,
	FIELD_VECTOR4D,
	FIELD_TYPECOUNT,
};

struct TypeDesc_t
{
	EFieldType			m_FieldType;
	const char*			m_FieldName;
	std::uint32_t		m_FieldOffset;
	std::uint16_t		m_FieldSize;
	short				m_Flags;
	const char*			m_ExternalName;
	void*				m_SaveRestoreOps;
	void*				m_InputFunc;
	CDatamap*			m_Map;
	int					m_FieldSizeInBytes;
	TypeDesc_t*			m_OverrideField;
	int					m_OverrideCount;
	float				m_FieldTolerance;
	int					m_FlatOffset[2];
	std::uint16_t		m_FlatGroup;
};

struct CDatamap
{
	TypeDesc_t*			m_ArrNodes;
	int					m_NumNodes;
	char const*			m_ClassName;
	CDatamap*			m_Parent;
	int					m_PackedSize;
	void*				m_OptimizedDataMap;
};

FORCEINLINE TypeDesc_t* FindInDT(std::uint32_t Name, CDatamap Table)
{
	for (auto it = 0U; it != Table.m_NumNodes; it++)
	{
		auto* CurNode = &Table.m_ArrNodes[it];

		if (!CurNode
			|| FNV(CurNode->m_FieldName) == Name)
			return CurNode;

		if (CurNode->m_FieldType == EFieldType::FIELD_EMBEDDED
			&& CurNode->m_Map)
		{
			auto* NewDT = CurNode->m_Map;
			FindInDT(Name, *NewDT);
		}
	}

	return NULL;
}