#pragma once
// Include stdlib
#include "../includes.h"
// Include stencil defs
#include "../sdk/types/stencil_defs.h"
// Include render context for stencil ops
#include "../sdk/types/matrenderctx.h"
// Include class id defs
#include "../sdk/types/classid.h"

class CBaseEntity;

enum EGlowStyle : std::int_fast8_t
{
	GLOW_NONE = -1,
	GLOW_BASIC = 0,
	GLOW_RIM3D,
	GLOW_EDGE_STATIC,
	GLOW_EDGE_PULSE
};

class CStencilGlow
{
	struct GlowDef_t
	{
		EGlowStyle			m_Style;
		float				m_Alpha;
		Color3_t			m_Color;
		float				m_Thickness;
		bool				m_FullBloom;
		CBaseEntity*		m_Owner;
		bool				m_Visible;
	};

	using GlowEntity_t = std::pair<GlowDef_t, GlowDef_t>;
public:
	CStencilGlow(IMatRenderContext* Context) : m_Context(Context) { Init(); }

public:
	void		PushEntity(CBaseEntity* Entity, GlowEntity_t& Setup);
	void		PopEntity(CBaseEntity* Owner);
	// Call this on DME pls
	void		OnDME(int W, int H);

	void		Apply();

private:
	// Context to operate on
	IMatRenderContext*		m_Context;
	// Entities to render
	std::vector<GlowEntity_t> m_Entities;
	// Materials for PIXEvent
	std::vector<IMaterial*> m_Materials;
	// Textures for filling glow
	std::vector<ITexture*> m_Textures;
	// Material indexes
	enum EGlowMats : int
	{
		M_FULL_FRAME,
		M_Q_SIZE_0,
		M_Q_SIZE_1,
		M_SHAPE,
		M_RIM_3D,
		M_DOWNSAMPLE,
		M_BLUR_X,
		M_BLUR_Y,
		M_HALO,
		M_EDGE_HIGHLIGHT
	};

private:
	// Initialize materials and check for ctx
	void		Init();
};