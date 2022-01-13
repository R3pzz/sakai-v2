#pragma once
// Includ CALL_VIRTUAL
#include "../platform.h"
// Include EOverrideType
#include "modelrender.h"

class IMaterial;

class IStudioRender
{
public:
	CALL_VIRTUAL(28U,	SetBlend(float Blend),				void(__thiscall*)(void*, float), Blend);
	CALL_VIRTUAL(27U,	SetCC(float* CC),					void(__thiscall*)(void*, float*), CC);

	CALL_VIRTUAL(33U,	ForcedMaterialOverride(IMaterial* Mat, EOverrideType Override), void(__thiscall*)(void*, IMaterial*, int), Mat, Override);
};