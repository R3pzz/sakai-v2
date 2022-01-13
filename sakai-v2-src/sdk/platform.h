#pragma once
// Include memory system for netvars defs etc...
#include "../core/memory.h"
// Include logging system for seh
#include "../core/logs.h"
// Include recv prop
#include "types/recv.h"
// Include findindt()
#include "types/datamap.h"

#define MATH_PI			3.14159265358979323846
#define DEG2RAD(Val)	(Val * (MATH_PI / 180.f))
#define RAD2DEG(Val)	(Val * (180.f / MATH_PI))
#define	MAX_OSPATH		260

/*
* Align wrappers.
*/
#define ALIGN4			__declspec(align(4))
#define ALIGN8			__declspec(align(8))
#define ALIGN16			__declspec(align(16))
#define ALIGN32			__declspec(align(32))

/*
* Netvar wrapper.
*/
#define NETVAR_FLD(Fn, Type, Name, ...) \
FORCEINLINE Type& Fn const \
{ \
	static Type Ptr = *reinterpret_cast<Type*>(reinterpret_cast<std::uintptr_t>(this) + MEM::NETMGR::m_mapNetvarTree[FNV(Name)]->m_iOffset __VA_ARGS__); \
	return Ptr; \
}

/*
* Netvar wrapper but returns pointer to a value.
*/
#define P_NETVAR_FLD(Fn, Type, Name, ...) \
FORCEINLINE Type* Fn const \
{ \
	static Type* Ptr = reinterpret_cast<Type*>(reinterpret_cast<std::uintptr_t>(this) + MEM::NETMGR::m_mapNetvarTree[FNV(Name)]->m_iOffset __VA_ARGS__); \
	return Ptr; \
}

/*
* Netvar wrapper but returns double pointer to a value (usually for arrays).
*/
#define PP_NETVAR_FLD(Fn, Type, Name, ...) \
FORCEINLINE Type** Fn const \
{ \
	static Type** Ptr = reinterpret_cast<Type**>(reinterpret_cast<std::uintptr_t>(this) + MEM::NETMGR::m_mapNetvarTree[FNV(Name)]->m_iOffset __VA_ARGS__); \
	return Ptr; \
}

/*
* Netvar wrapper but returns an array.
*/
#define ARR_NETVAR_FLD(Fn, Type, Num, Name, ...) \
FORCEINLINE std::array<Type, Num>& Fn const \
{ \
	static std::array<Type, Num> Ptr = *reinterpret_cast<std::array<Type, Num>*>(reinterpret_cast<std::uintptr_t>(this) + MEM::NETMGR::m_mapNetvarTree[FNV(Name)]->m_iOffset __VA_ARGS__); \
	return Ptr; \
}

/*
* Ref to some variable in class.
*/
#define OFFSET_FLD(Fn, Type, Offset) \
FORCEINLINE Type& Fn const \
{ \
	static Type Ptr = *reinterpret_cast<Type*>(reinterpret_cast<std::uintptr_t>(this) + Offset); \
	return Ptr; \
}

/*
* Pointer to some variable in class.
*/
#define P_OFFSET_FLD(Fn, Type, Offset) \
FORCEINLINE Type* Fn const \
{ \
	static Type* Ptr = reinterpret_cast<Type*>(reinterpret_cast<std::uintptr_t>(this) + Offset); \
	return Ptr; \
}

/*
* Double pointer to some variable in class.
*/
#define PP_OFFSET_FLD(Fn, Type, Offset) \
FORCEINLINE Type** Fn const \
{ \
	static Type** Ptr = reinterpret_cast<Type**>(reinterpret_cast<std::uintptr_t>(this) + Offset); \
	return Ptr; \
}

/*
* Parse given datamap.
*/
#define DATAMAP_FLD(Fn, Type, Name, Table) \
FORCEINLINE Type& Fn \
{ \
	const auto Offset = FindInDT(FNV(Name), Table)->m_FieldOffset; \
	static Type Ptr = *reinterpret_cast<Type*>(reinterpret_cast<std::uintptr_t>(this) + Offset); \
	return Ptr; \
}

/*
* Find signature wrapper.
*/
#define SIG(Module, Pat) \
MEM::FindSignature(Module, Pat)

/*
* Call function by signature wrapper.
*/
#define CALL_SIG(Fn, Module, Pat, Type, ...) \
FORCEINLINE auto Fn \
{ \
	static const auto Ptr = SIG(Module, Pat).Get<Type>(); \
	return Ptr(this, __VA_ARGS__); \
}

#define DECLARE_BYTEPAT_FN_INSERT(Module, Sig, Convention) \
using LocConv = Convention; \
static LocConv Fn; \
{ \
	static std::uint8_t* s_Ptr = SIG(Module, Sig).m_Ptr; \
	\
	if (!s_Ptr) \
		L::LogEvent(XOR("Failed to exec function"), true); \
	Fn = reinterpret_cast<LocConv>(s_Ptr); \
}

#define DECLARE_BYTEPAT_ASM_INSERT() \

/*
* Call a function by its address in a VMT.
* @Note: VMT stands for 'Virtual Method Table'.
*	All VMT classes should be linked to in-game classes
*	so we can get a correct VMT.
*/
#define CALL_VIRTUAL(Index, Fn, Type, ...) \
FORCEINLINE auto Fn { \
	return MEM::CallVirtual<Type>(this, Index)(this, __VA_ARGS__); \
}

/*
* Emit message wrapper.
*/
#define EMIT_MSG(Buf, Fmt, ...) \
std::vsprintf(XOR(Buf), Fmt, __VA_ARGS__)

enum EAngleType : int
{
	PITCH = 0,
	YAW,
	ROLL
};

using Color3_t = float[3];
using Color4_t = float[4];

void CopyColor3(const Color3_t Src, void* Dst);
void CopyColor4(const Color4_t Src, void* Dst);

// Special type for padding:
using pad_t = std::int8_t;

/*
* IAppSystem class for VMT alignment.
*/
class IAppSystem
{
public:
	virtual void _0() { }
	virtual void _1() { }
	virtual void _2() { }
	virtual void _3() { }
	virtual void _4() { }
	virtual void _5() { }
	virtual void _6() { }
	virtual void _7() { }
	virtual void _8() { }
};