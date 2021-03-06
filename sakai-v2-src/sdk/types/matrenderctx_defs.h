#pragma once
// Include std sutff
#include "../platform.h"
// Include vectors
#include "vector.h"

#define MATERIAL_MAX_LIGHT_COUNT 4
#define PIX_VALVE_ORANGE	0xFFF5940F

using AmbientCube_t = CVector4[6];

enum EImageFormat : std::uint_fast16_t
{
	IMAGE_FORMAT_DEFAULT = -2,
	IMAGE_FORMAT_UNKNOWN = -1,
	IMAGE_FORMAT_RGBA8888 = 0,
	IMAGE_FORMAT_ABGR8888,
	IMAGE_FORMAT_RGB888,
	IMAGE_FORMAT_BGR888,
	IMAGE_FORMAT_RGB565,
	IMAGE_FORMAT_I8,
	IMAGE_FORMAT_IA88,
	IMAGE_FORMAT_P8,
	IMAGE_FORMAT_A8,
	IMAGE_FORMAT_RGB888_BLUESCREEN,
	IMAGE_FORMAT_BGR888_BLUESCREEN,
	IMAGE_FORMAT_ARGB8888,
	IMAGE_FORMAT_BGRA8888,
	IMAGE_FORMAT_DXT1,
	IMAGE_FORMAT_DXT3,
	IMAGE_FORMAT_DXT5,
	IMAGE_FORMAT_BGRX8888,
	IMAGE_FORMAT_BGR565,
	IMAGE_FORMAT_BGRX5551,
	IMAGE_FORMAT_BGRA4444,
	IMAGE_FORMAT_DXT1_ONEBITALPHA,
	IMAGE_FORMAT_BGRA5551,
	IMAGE_FORMAT_UV88,
	IMAGE_FORMAT_UVWQ8888,
	IMAGE_FORMAT_RGBA16161616F,
	IMAGE_FORMAT_RGBA16161616,
	IMAGE_FORMAT_UVLX8888,
	IMAGE_FORMAT_R32F,
	IMAGE_FORMAT_RGB323232F,
	IMAGE_FORMAT_RGBA32323232F,
	IMAGE_FORMAT_RG1616F,
	IMAGE_FORMAT_RG3232F,
	IMAGE_FORMAT_RGBX8888,
	IMAGE_FORMAT_NULL,
	IMAGE_FORMAT_ATI2N,
	IMAGE_FORMAT_ATI1N,
	IMAGE_FORMAT_RGBA1010102,
	IMAGE_FORMAT_BGRA1010102,
	IMAGE_FORMAT_R16F,
	IMAGE_FORMAT_D16,
	IMAGE_FORMAT_D15S1,
	IMAGE_FORMAT_D32,
	IMAGE_FORMAT_D24S8,
	IMAGE_FORMAT_LINEAR_D24S8,
	IMAGE_FORMAT_D24X8,
	IMAGE_FORMAT_D24X4S4,
	IMAGE_FORMAT_D24FS8,
	IMAGE_FORMAT_D16_SHADOW,
	IMAGE_FORMAT_D24X8_SHADOW,
	IMAGE_FORMAT_LINEAR_BGRX8888,
	IMAGE_FORMAT_LINEAR_RGBA8888,
	IMAGE_FORMAT_LINEAR_ABGR8888,
	IMAGE_FORMAT_LINEAR_ARGB8888,
	IMAGE_FORMAT_LINEAR_BGRA8888,
	IMAGE_FORMAT_LINEAR_RGB888,
	IMAGE_FORMAT_LINEAR_BGR888,
	IMAGE_FORMAT_LINEAR_BGRX5551,
	IMAGE_FORMAT_LINEAR_I8,
	IMAGE_FORMAT_LINEAR_RGBA16161616,
	IMAGE_FORMAT_LINEAR_A8,
	IMAGE_FORMAT_LINEAR_DXT1,
	IMAGE_FORMAT_LINEAR_DXT3,
	IMAGE_FORMAT_LINEAR_DXT5,
	IMAGE_FORMAT_LE_BGRX8888,
	IMAGE_FORMAT_LE_BGRA8888,
	IMAGE_FORMAT_DXT1_RUNTIME,
	IMAGE_FORMAT_DXT5_RUNTIME,
	IMAGE_FORMAT_INTZ,
	NUM_IMAGE_FORMATS
};

enum EMatCullMode : std::uint_fast8_t
{
	MATERIAL_CULLMODE_CCW,
	MATERIAL_CULLMODE_CW,
	MATERIAL_CULLMODE_NONE
};

enum EMatFogMode : std::uint_fast8_t
{
	MATERIAL_FOG_NONE,
	MATERIAL_FOG_LINEAR,
	MATERIAL_FOG_LINEAR_BELOW_FOG_Z,
};

enum EMatrixMode : std::uint_fast8_t
{
	MATERIAL_VIEW = 0,
	MATERIAL_PROJECTION = 1,
	MATERIAL_MODEL = 9,
	NUM_MATRIX_MODES = MATERIAL_MODEL + 1,
};

enum ELightType : std::uint_fast8_t
{
	MATERIAL_LIGHT_DISABLE = 0,
	MATERIAL_LIGHT_POINT,
	MATERIAL_LIGHT_DIRECTIONAL,
	MATERIAL_LIGHT_SPOT,
};

enum EMorphWeightType
{
	MORPH_WEIGHT = 0,
	MORPH_WEIGHT_LAGGED,
	MORPH_WEIGHT_STEREO,
	MORPH_WEIGHT_STEREO_LAGGED,
	MORPH_WEIGHT_COUNT,
};

struct MorphWeight_t
{
	float				m_Weight[MORPH_WEIGHT_COUNT];
};

struct LightDesc_t
{
	ELightType			m_Type;
	CVector3			m_Color;
	CVector3			m_Position;
	CVector3			m_Direction;
	float				m_Range;
	float				m_Falloff;
	float				m_Attenuation0;
	float				m_Attenuation1;
	float				m_Attenuation2;
	float				m_Theta;
	float				m_Phi;
	float				m_ThetaCos;
	float				m_PhiCos;
	float				m_OneOverThetaCosMinusPhiCos;
	std::uint32_t		m_Flags;
	float				m_RangeSquared;
};

struct MaterialLightingState_t
{
	AmbientCube_t			m_AmbientCube;
	CVector3				m_LightingOrigin;
	int						m_LocalLightCount;
	LightDesc_t				m_LocalLightDesc[MATERIAL_MAX_LIGHT_COUNT];
};