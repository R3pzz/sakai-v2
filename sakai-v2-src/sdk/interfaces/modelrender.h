#pragma once
// Include CALL_VIRTUAL
#include "../platform.h"

class IMaterial;

enum EOverrideType : int
{
	OVERRIDE_NORMAL = 0,
	OVERRIDE_BUILD_SHADOWS,
	OVERRIDE_DEPTH_WRITE,
	OVERRIDE_SELECTIVE,
	OVERRIDE_SSAO_DEPTH_WRITE,
};

class IVModelRender
{
public:
	// Override current material:
	CALL_VIRTUAL(1U,	ForcedMaterialOverride(IMaterial* Mat, EOverrideType Override), void(__thiscall*)(void*, IMaterial*, int), Mat, Override);
	// Can we override current mat?:
	CALL_VIRTUAL(2U,	IsForcedMaterialOverride(),			bool(__thiscall*)(void*));
};

class IVRenderView
{
public:
	// How rough will be transition between textures:
	CALL_VIRTUAL(4U,	GetBlend(),							float(__thiscall*)(void*));
	CALL_VIRTUAL(5U,	SetBlend(float Blend),				void(__thiscall*)(void*, float), Blend);
	// Color correction:
	CALL_VIRTUAL(6U,	GetCC(const float* Out),			void(__thiscall*)(void*, const float*), Out);
	CALL_VIRTUAL(7U,	SetCC(float* CC),					void(__thiscall*)(void*, float*), CC);
};