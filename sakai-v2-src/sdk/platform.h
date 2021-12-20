#pragma once
// Include memory system for netvars defs etc...
#include "../core/memory.h"
// Include logging system for seh
#include "../core/logs.h"

#define MATH_PI			3.14159265358979323846
#define DEG2RAD(Val)	(Val * (MATH_PI / 180.f))
#define RAD2DEG(Val)	(Val * (180.f / MATH_PI))

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
FORCEINLINE Type& Name { \
	static const Type Ptr = *reinterpret_cast<Type*>(reinterpret_cast<std::uint8_t>(this) + MEM::NETMGR::m_NetvarTree[FNV(Name)]. __VA_ARGS__); \
	return Ptr; \
}

/*
* Netvar wrapper but returns pointer to a value.
*/
#define PTR_NETVAR_FLD(Fn, Type, Name, ...) \
FORCEINLINE Type* Name { \
	static const Type* Ptr = reinterpret_cast<Type*>(reinterpret_cast<std::uint8_t>(this) + MEM::NETMGR::m_NetvarTree[FNV(Name)]. __VA_ARGS__); \
	return Ptr; \
}

/*
* Netvar wrapper but returns double pointer to a value (usually for arrays).
*/
#define DBL_PTR_NETVAR_FLD(Fn, Type, Name, ...) \
FORCEINLINE Type** Name { \
	static const Type** Ptr = reinterpret_cast<Type**>(reinterpret_cast<std::uint8_t>(this) + MEM::NETMGR::m_NetvarTree[FNV(Name)]. __VA_ARGS__); \
	return Ptr; \
}

/*
* Netvar wrapper but returns an array.
*/
#define ARR_NETVAR_FLD(Fn, Type, Num, Name, ...) \
FORCEINLINE std::array<Type, Num>& Name { \
	static const std::array<Type, Num> Ptr = *reinterpret_cast<std::array<Type, Num>*>(reinterpret_cast<std::uint8_t>(this) + MEM::NETMGR::m_NetvarTree[FNV(Name)]. __VA_ARGS__); \
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
FORCEINLINE auto Fn { \
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
		L::LogEvent(XOR("Failed to exec function"), L::EEventType::LOG_EVENT_FAILURE); \
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

enum EAngleType : int {
	PITCH = 0,
	YAW,
	ROLL
};

using Color3_t = float[3];
using Color4_t = float[4];

// Special type for padding:
using pad_t = std::int8_t;