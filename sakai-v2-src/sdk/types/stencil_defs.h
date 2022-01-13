#pragma once
// Include std stuff
#include "../platform.h"

#define TEXTURE_GROUP_LIGHTMAP						"Lightmaps"
#define TEXTURE_GROUP_WORLD							"World textures"
#define TEXTURE_GROUP_MODEL							"Model textures"
#define TEXTURE_GROUP_STATIC_PROP					"StaticProp textures"
#define TEXTURE_GROUP_COMBINED						"Combined Textures"
#define TEXTURE_GROUP_COMPOSITE						"Composited Textures"
#define TEXTURE_GROUP_VGUI							"VGUI textures"
#define TEXTURE_GROUP_PARTICLE						"Particle textures"
#define TEXTURE_GROUP_DECAL							"Decal textures"
#define TEXTURE_GROUP_SKYBOX						"SkyBox textures"
#define TEXTURE_GROUP_CLIENT_EFFECTS				"ClientEffect textures"
#define TEXTURE_GROUP_OTHER							"Other textures"
#define TEXTURE_GROUP_PRECACHED						"Precached"
#define TEXTURE_GROUP_CUBE_MAP						"CubeMap textures"
#define TEXTURE_GROUP_RENDER_TARGET					"RenderTargets"
#define TEXTURE_GROUP_UNACCOUNTED					"Unaccounted textures"
#define TEXTURE_GROUP_STATIC_INDEX_BUFFER			"Static Indices"
#define TEXTURE_GROUP_STATIC_VERTEX_BUFFER_DISP		"Displacement Verts"
#define TEXTURE_GROUP_STATIC_VERTEX_BUFFER_COLOR	"Lighting Verts"
#define TEXTURE_GROUP_STATIC_VERTEX_BUFFER_WORLD	"World Verts"
#define TEXTURE_GROUP_STATIC_VERTEX_BUFFER_MODELS	"Model Verts"
#define TEXTURE_GROUP_STATIC_VERTEX_BUFFER_OTHER	"Other Verts"
#define TEXTURE_GROUP_DYNAMIC_INDEX_BUFFER			"Dynamic Indices"
#define TEXTURE_GROUP_DYNAMIC_VERTEX_BUFFER			"Dynamic Verts"
#define TEXTURE_GROUP_DEPTH_BUFFER					"DepthBuffer"
#define TEXTURE_GROUP_VIEW_MODEL					"ViewModel"
#define TEXTURE_GROUP_PIXEL_SHADERS					"Pixel Shaders"
#define TEXTURE_GROUP_VERTEX_SHADERS				"Vertex Shaders"
#define TEXTURE_GROUP_RENDER_TARGET_SURFACE			"RenderTarget Surfaces"
#define TEXTURE_GROUP_MORPH_TARGETS					"Morph Targets"
#define TEXTURE_GROUP_SCALEFORM						"Scaleform textures"

enum EShaderStencilOp : int
{
	SHADER_STENCILOP_KEEP = 1,
	SHADER_STENCILOP_ZERO = 2,
	SHADER_STENCILOP_SET_TO_REFERENCE = 3,
	SHADER_STENCILOP_INCREMENT_CLAMP = 4,
	SHADER_STENCILOP_DECREMENT_CLAMP = 5,
	SHADER_STENCILOP_INVERT = 6,
	SHADER_STENCILOP_INCREMENT_WRAP = 7,
	SHADER_STENCILOP_DECREMENT_WRAP = 8,
	SHADER_STENCILOP_FORCE_DWORD = 0x7fffffff
};

enum EShaderStencilFunc : int
{
	SHADER_STENCILFUNC_NEVER = 1,
	SHADER_STENCILFUNC_LESS = 2,
	SHADER_STENCILFUNC_EQUAL = 3,
	SHADER_STENCILFUNC_LEQUAL = 4,
	SHADER_STENCILFUNC_GREATER = 5,
	SHADER_STENCILFUNC_NOTEQUAL = 6,
	SHADER_STENCILFUNC_GEQUAL = 7,
	SHADER_STENCILFUNC_ALWAYS = 8,
	SHADER_STENCILFUNC_FORCE_DWORD = 0x7fffffff
};

struct ShaderStencilState_t
{
	bool				m_Enable;
	EShaderStencilOp	m_FailOp;
	EShaderStencilOp	m_ZFailOp;
	EShaderStencilOp	m_PassOp;
	EShaderStencilFunc	m_CompareFunc;
	int					m_RefValue;
	std::uint32_t		m_TestMask;
	std::uint32_t		m_WriteMask;
};