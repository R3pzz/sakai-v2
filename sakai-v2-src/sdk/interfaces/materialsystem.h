#pragma once
// Include CALL_VIRTUAL macro, std stuff...
#include "../platform.h"
// Include EMaterialVarFlags
#include "../classes.h"
// Include CVector3
#include "../types/vector.h"

class CKeyValues;
class ITexture;
class IMaterialVar;
class IMatRenderContext;

class IMaterial {
public:
	// Name:
	virtual const char* GetName() const = 0;
	virtual const char* GetTexGroupName() const = 0;
	// Finds a specific key value in material desc:
	CALL_VIRTUAL(11U,	FindVar(const char* Var, bool* Found = NULL, bool Complain = true), IMaterialVar* (__thiscall*)(void*, const char*, bool*, bool), Var, Found, Complain);
	// Reference count:
	CALL_VIRTUAL(12U,	IncrementRefCount(),					void(__thiscall*)(void*));
	CALL_VIRTUAL(13U,	DecrementRefCount(),					void(__thiscall*)(void*));
	// Color stuff:
	CALL_VIRTUAL(27U,	ColorModulate(Color3_t Color),			void(__thiscall*)(void*, float, float, float),		Color[1], Color[2], Color[3]);
	CALL_VIRTUAL(28U,	AlphaModulate(float Alpha),				void(__thiscall*)(void*, float),					Alpha);
	// Set key value flag state:
	CALL_VIRTUAL(29U,	SetFlag(EMaterialVarFlags Flag, bool State), void(__thiscall*)(void*, int, bool),			Flag, State);

	CALL_VIRTUAL(42U,	IsErrorMaterial(),						bool(__thiscall*)(void*));
};

class IMaterialVar {
public:
	CALL_VIRTUAL(4U,	SetFloat(float Value),					void(__thiscall*)(void*, float),					Value);
	CALL_VIRTUAL(5U,	SetInt(int Value),						void(__thiscall*)(void*, int),						Value);
	CALL_VIRTUAL(6U,	SetString(char const* Value),			void(__thiscall*)(void*, char const*),				Value);
	CALL_VIRTUAL(11U,	SetVector(const CVector3& Value),		void(__thiscall*)(void*, float, float, float),		Value.m_X, Value.m_Y, Value.m_Z);
	CALL_VIRTUAL(27U,	SetVectorComponent(float Value, int I),	void(__thiscall*)(void*, float, int),				Value, I);
};

class IMaterialSystem {
public:
	// Material operations:
	CALL_VIRTUAL(83U,	CreateMaterial(const char* Name, CKeyValues* Kvals), IMaterial* (__thiscall*)(void*, const char*, CKeyValues*), Name, Kvals);
	CALL_VIRTUAL(84U,	FindMaterial(const char* Name, const char* Group = "Model textures"), IMaterial* (__thiscall*)(void*, const char*, const char*, bool, const char*), Name, Group, true, nullptr);
	CALL_VIRTUAL(86U,	GetFirstMaterial(),						std::uint16_t(__thiscall*)(void*));
	CALL_VIRTUAL(87U,	GetNextMaterial(std::uint16_t Handle),	std::uint16_t(__thiscall*)(void*, uint16_t),		Handle);
	// Get an invalid material:
	CALL_VIRTUAL(88U,	InvalidMaterial(),						std::uint16_t(__thiscall*)(void*));
	// Get a material by its index:
	CALL_VIRTUAL(89U,	GetMaterial(std::uint16_t Handle),		IMaterial* (__thiscall*)(void*, std::uint16_t),		Handle);
	CALL_VIRTUAL(90U,	GetMaterialsCount(),					int(__thiscall*)(void*));
	// Find a texture:
	CALL_VIRTUAL(91U,	FindTexture(const char* Name, const char* GroupName), ITexture* (__thiscall*)(void*, const char*, const char*, bool, int), Name, GroupName, true, 0);
	// Get render context (used for setting up the scene):
	CALL_VIRTUAL(115U,	GetRenderContext(),						IMatRenderContext* (__thiscall*)(void*));
};