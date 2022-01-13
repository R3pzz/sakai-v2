#pragma once
// Include pad_t, std stuff
#include "../platform.h"
// Include CVector3
#include "../types/vector.h"
// Include CUtlVector<>
#include "../types/utlvector.h"

class CBaseEntity;

enum class EGlowRenderStyle : int
{
	GLOWRENDERSTYLE_DEFAULT = 0,
	GLOWRENDERSTYLE_RIMGLOW3D,
	GLOWRENDERSTYLE_EDGE_HIGHLIGHT,
	GLOWRENDERSTYLE_EDGE_HIGHLIGHT_PULSE,
	GLOWRENDERSTYLE_COUNT,
};

class IGlowObjectManager
{
public:
	struct GlowObject_t
	{
		 void	Set(Color4_t& Color, EGlowRenderStyle Style = EGlowRenderStyle::GLOWRENDERSTYLE_DEFAULT)
		{
			CopyColor4(Color, m_Color);
			m_BloomAmount = 1.0f;
			m_RenderWhenOccluded = true;
			m_RenderWhenUnoccluded = false;
			m_RenderStyle = Style;
		}

		 bool			IsEmpty() const
		{
			return m_NextFreeSlot != -2;
		}

		int						m_NextFreeSlot;					// 0x00
		CBaseEntity*			m_Entity;						// 0x04
		Color4_t				m_Color;						// 0x08
		bool					m_AlphaCappedByRenderAlpha;		// 0x18
		pad_t					_0[0x3];						// 0x19
		float					m_AlphaFunctionOfMaxVelocity;	// 0x1C
		float					m_BloomAmount;					// 0x20
		float					m_PulseOverdrive;				// 0x24
		bool					m_RenderWhenOccluded;			// 0x28
		bool					m_RenderWhenUnoccluded;			// 0x29
		bool					m_FullBloomRender;				// 0x2A
		pad_t					_1[0x1];						// 0x2B
		int						m_FullBloomStencilTestValue;	// 0x2C
		EGlowRenderStyle		m_RenderStyle;					// 0x30
		int						m_SplitScreenSlot;				// 0x34
	};

	CUtlVector<GlowObject_t>	m_GlowObjectDefinitions;
	int							m_FirstFreeSlot;
};